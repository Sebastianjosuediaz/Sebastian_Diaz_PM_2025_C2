#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definición de la estructura domicilio */
typedef struct {
    char calle[20];
    int numero;
    int cp;
    char localidad[20];
} domicilio;

/* Estructura anidada empleado */
struct empleado {
    char nombre[20];
    char departamento[20];
    float sueldo;
    domicilio direccion;  // Campo de tipo estructura anidada
};

/* Prototipo de función */
void Lectura(struct empleado *a);

int main(void)
{
    /* Inicialización directa de una variable de tipo empleado */
    struct empleado e0 = {"Arturo", "Compras", 15500.75, "San Jerónimo", 120, 3490, "Toluca"};

    /* Declaración de variables y apuntadores */
    struct empleado *e1, *e2, e3, e4;

    /* Asignación dinámica de memoria para e1 */
    e1 = (struct empleado *)malloc(sizeof(struct empleado));
    if (e1 == NULL) {
        printf("Memoria insuficiente.\n");
        return 1;
    }

    /* Lectura de datos para e1 */
    printf("\nIngrese el nombre del empleado 1: ");
    scanf("%s", e1->nombre);
    getchar(); // Limpiar salto de línea residual

    printf("Ingrese el departamento de la empresa: ");
    fgets(e1->departamento, sizeof(e1->departamento), stdin);
    e1->departamento[strcspn(e1->departamento, "\n")] = '\0';

    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &e1->sueldo);

    printf("—-Ingrese la dirección del empleado—-\n");
    printf("\tCalle: ");
    getchar(); // Limpiar salto de línea residual
    fgets(e1->direccion.calle, sizeof(e1->direccion.calle), stdin);
    e1->direccion.calle[strcspn(e1->direccion.calle, "\n")] = '\0';

    printf("\tNúmero: ");
    scanf("%d", &e1->direccion.numero);

    printf("\tCódigo Postal: ");
    scanf("%d", &e1->direccion.cp);

    printf("\tLocalidad: ");
    getchar();
    fgets(e1->direccion.localidad, sizeof(e1->direccion.localidad), stdin);
    e1->direccion.localidad[strcspn(e1->direccion.localidad, "\n")] = '\0';

    /* Lectura de datos para e3 */
    printf("\nIngrese el nombre del empleado 3: ");
    scanf("%s", e3.nombre);
    getchar();

    printf("Ingrese el departamento de la empresa: ");
    fgets(e3.departamento, sizeof(e3.departamento), stdin);
    e3.departamento[strcspn(e3.departamento, "\n")] = '\0';

    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &e3.sueldo);

    printf("—-Ingrese la dirección del empleado—-\n");
    printf("\tCalle: ");
    getchar();
    fgets(e3.direccion.calle, sizeof(e3.direccion.calle), stdin);
    e3.direccion.calle[strcspn(e3.direccion.calle, "\n")] = '\0';

    printf("\tNúmero: ");
    scanf("%d", &e3.direccion.numero);

    printf("\tCódigo Postal: ");
    scanf("%d", &e3.direccion.cp);

    printf("\tLocalidad: ");
    getchar();
    fgets(e3.direccion.localidad, sizeof(e3.direccion.localidad), stdin);
    e3.direccion.localidad[strcspn(e3.direccion.localidad, "\n")] = '\0';

    /* Asignación dinámica para e2 */
    e2 = (struct empleado *)malloc(sizeof(struct empleado));
    if (e2 == NULL) {
        printf("Memoria insuficiente.\n");
        free(e1);
        return 1;
    }

    /* Llamado a la función Lectura */
    Lectura(e2);
    Lectura(&e4);

    /* Impresión de resultados */
    printf("\nDatos del empleado 1\n");
    printf("%s\t%s\t%.2f\t%s\t%d\t%d\t%s\n",
           e1->nombre, e1->departamento, e1->sueldo,
           e1->direccion.calle, e1->direccion.numero, e1->direccion.cp, e1->direccion.localidad);

    printf("\nDatos del empleado 4\n");
    printf("%s\t%s\t%.2f\t%s\t%d\t%d\t%s\n",
           e4.nombre, e4.departamento, e4.sueldo,
           e4.direccion.calle, e4.direccion.numero, e4.direccion.cp, e4.direccion.localidad);

    /* Liberar memoria asignada */
    free(e1);
    free(e2);

    return 0;
}

/* Función para leer los campos de un empleado */
void Lectura(struct empleado *a)
{
    printf("\nIngrese el nombre del empleado: ");
    scanf("%s", a->nombre);
    getchar(); // Limpiar salto de línea residual

    printf("Ingrese el departamento de la empresa: ");
    fgets(a->departamento, sizeof(a->departamento), stdin);
    a->departamento[strcspn(a->departamento, "\n")] = '\0';

    printf("Ingrese el sueldo del empleado: ");
    scanf("%f", &a->sueldo);

    printf("—-Ingrese la dirección del empleado—-\n");
    printf("\tCalle: ");
    getchar(); // Limpiar salto de línea residual
    fgets(a->direccion.calle, sizeof(a->direccion.calle), stdin);
    a->direccion.calle[strcspn(a->direccion.calle, "\n")] = '\0';

    printf("\tNúmero: ");
    scanf("%d", &a->direccion.numero);

    printf("\tCódigo Postal: ");
    scanf("%d", &a->direccion.cp);

    printf("\tLocalidad: ");
    getchar();
    fgets(a->direccion.localidad, sizeof(a->direccion.localidad), stdin);
    a->direccion.localidad[strcspn(a->direccion.localidad, "\n")] = '\0';
}
