#include <stdio.h>
#include <string.h>

// este es un programa que calcula los gastos de un vehiculo en carretera, gastos de combustible, kilometrage, costo de gomas etc...

#define MAX 50

typedef struct {
    char placa[20];
    char marca[20];
    char modelo[20];
    char combustible[15];
    float kmCarretera;
    float kmCiudad;
    float costoGomas;
    int kmGomas;
    float costoSeguro;
    float costoMant;
    int kmMant;
    float costoVeh;
    int vidaUtil;
    int kmAnual;
    float depreciacion;
} Vehiculo;

Vehiculo lista[MAX];
int cant = 0;

float precioGasolina = 300, precioGasoil = 250;

void guardarDatos()
{
    FILE *f = fopen("vehiculos.dat", "wb");
    if (!f) return;
    fwrite(&cant, sizeof(int), 1, f);
    fwrite(lista, sizeof(Vehiculo), cant, f);
    fwrite(&precioGasolina, sizeof(float), 1, f);
    fwrite(&precioGasoil, sizeof(float), 1, f);
    fclose(f);
}

void cargarDatos()
{
    FILE *f = fopen("vehiculos.dat", "rb");
    if (!f) return;
    fread(&cant, sizeof(int), 1, f);
    fread(lista, sizeof(Vehiculo), cant, f);
    fread(&precioGasolina, sizeof(float), 1, f);
    fread(&precioGasoil, sizeof(float), 1, f);
    fclose(f);
}

void agregar() {
    if (cant >= MAX) {
        printf("No se pueden agregar mas.\n");
        return;
    }

    Vehiculo v;
    printf("Placa: "); scanf("%s", v.placa);
    printf("Marca: "); scanf("%s", v.marca);
    printf("Modelo: "); scanf("%s", v.modelo);
    printf("Combustible (Gasolina/Gasoil): "); scanf("%s", v.combustible);
    printf("Km/galon carretera: "); scanf("%f", &v.kmCarretera);
    printf("Km/galon ciudad: "); scanf("%f", &v.kmCiudad);
    printf("Costo gomas (Todas las gomas): "); scanf("%f", &v.costoGomas);
    printf("Km de gomas: "); scanf("%d", &v.kmGomas);
    printf("Costo seguro anual: "); scanf("%f", &v.costoSeguro);
    printf("Costo mantenimiento: "); scanf("%f", &v.costoMant);
    printf("Cada cuantos km mantenimiento: "); scanf("%d", &v.kmMant);
    printf("Costo del vehiculo: "); scanf("%f", &v.costoVeh);
    printf("Vida util en anios: "); scanf("%d", &v.vidaUtil);
    printf("Km promedio anual: "); scanf("%d", &v.kmAnual);

    v.depreciacion = v.costoVeh / (v.vidaUtil * v.kmAnual);

    lista[cant] = v;
    cant++;
    guardarDatos();
    printf("Vehiculo agregado.\n");
}

void mostrar()
 {
    if (cant == 0) {
        printf("No hay vehiculos.\n");
        return;
    }
    for (int i = 0; i < cant; i++) {
        printf("%d) %s - %s - %s\n", i+1, lista[i].placa, lista[i].marca, lista[i].modelo);
    }
}

void borrar()
 {
    mostrar();
    int n;
    printf("Numero a borrar: ");
    scanf("%d", &n);
    if (n < 1 || n > cant) return;
    for (int i = n-1; i < cant-1; i++) {
        lista[i] = lista[i+1];
    }
    cant--;
    guardarDatos();
    printf("Vehiculo borrado.\n");
}

void modificar()
 {
    mostrar();
    int n;
    printf("Numero a modificar: ");
    scanf("%d", &n);
    if (n < 1 || n > cant) return;
    n--;
    printf("Nuevo costo seguro: "); scanf("%f", &lista[n].costoSeguro);
    printf("Nuevo costo mantenimiento: "); scanf("%f", &lista[n].costoMant);
    guardarDatos();
    printf("Datos modificados.\n");
}

void datosGenerales()

 {
    printf("Precio gasolina actual: %.2f\n", precioGasolina);
    printf("Precio gasoil actual: %.2f\n", precioGasoil);
    printf("Nuevo precio gasoil: "); scanf("%f", &precioGasoil);
    guardarDatos();
}

void costoViaje()
 {
    mostrar();
    int n;
    printf("Seleccione vehiculo: ");
    scanf("%d", &n);
    if (n < 1 || n > cant) return;
    n--;
    Vehiculo v = lista[n];

    float km, porcCiudad;
    printf("Km del viaje: "); scanf("%f", &km);
    printf("Porcentaje en ciudad (0-100): "); scanf("%f", &porcCiudad);

    float kmCiudad = km * porcCiudad / 100;
    float kmCarretera = km - kmCiudad;

    float costoComb;
    if (strcmp(v.combustible, "Gasolina") == 0)
        costoComb = (kmCiudad/v.kmCiudad + kmCarretera/v.kmCarretera) * precioGasolina;
    else
        costoComb = (kmCiudad/v.kmCiudad + kmCarretera/v.kmCarretera) * precioGasoil;

    float costoGomas = (v.costoGomas / v.kmGomas) * km;
    float costoSeg = (v.costoSeguro / (v.kmAnual * v.vidaUtil)) * km;
    float costoMant = (v.costoMant / v.kmMant) * km;
    float costoDep = v.depreciacion * km;

    float total = costoComb + costoGomas + costoSeg + costoMant + costoDep;
    float porKm = total / km;

    printf("\n--- CALCULO DEL VIAJE ---\n");
    printf("Combustible:     %.2f\n", costoComb);
    printf("Gomas:           %.2f\n", costoGomas);
    printf("Seguro:          %.2f\n", costoSeg);
    printf("Mantenimiento:   %.2f\n", costoMant);
    printf("Depreciacion:    %.2f\n", costoDep);
    printf("-------------------------\n");
    printf("TOTAL VIAJE:     %.2f\n", total);
    printf("COSTO PROMEDIO POR KM: %.2f\n", porKm);
}

int main()
 {
    cargarDatos();
    int op;
    do {
        printf("\n--- MENU GESTION DE GASTOS---\n");
        printf("1. Agregar vehiculo\n");
        printf("2. Modificar vehiculo\n");
        printf("3. Borrar vehiculo\n");
        printf("4. Datos generales\n");
        printf("5. Calcular costo viaje\n");
        printf("6. Mostrar vehiculos\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1: agregar(); break;
            case 2: modificar(); break;
            case 3: borrar(); break;
            case 4: datosGenerales(); break;
            case 5: costoViaje(); break;
            case 6: mostrar(); break;
        }
    } while (op != 0);

    return 0;
}
