#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// alumnos.c  ——  Gestión de alumnos con memoria dinámica y archivos binarios //

typedef struct {
    int   matricula;
    char  nombre[50];
    float promedio;
} Alumno;

//ESCRIBIR ALUMNOS A DISCO//
void escribir_alumnos(const char *archivo, Alumno *vec, size_t n)
{
    FILE *f = fopen(archivo, "wb");
    if (!f) { perror("fopen‑write"); exit(EXIT_FAILURE); }

    //Primero guardamos la cantidad para saber luego cuánto leer //
    fwrite(&n, sizeof(size_t), 1, f);

    // Ahora todos los registros juntos //
    fwrite(vec, sizeof(Alumno), n, f);

    fclose(f);
}

// LEER ALUMNOS DESDE DISCO (DINÁMICO) //
Alumno *leer_alumnos(const char *archivo, size_t *n)
{
    FILE *f = fopen(archivo, "rb");
    if (!f) { perror("fopen‑read"); exit(EXIT_FAILURE); }

    // Recuperamos la cantidad de registros //
    if (fread(n, sizeof(size_t), 1, f) != 1)
        { fprintf(stderr, "Error leyendo cantidad\n"); exit(EXIT_FAILURE); }

    // Reservamos memoria dinámica para *n estructuras //
    Alumno *vec = malloc(*n * sizeof(Alumno));
    if (!vec) { perror("malloc"); exit(EXIT_FAILURE); }

    // Leemos la zona de datos completa //
    if (fread(vec, sizeof(Alumno), *n, f) != *n)
        { fprintf(stderr, "Error leyendo datos\n"); exit(EXIT_FAILURE); }

    fclose(f);
    return vec;              //Devolvemos el puntero dinámico //
}

//PROGRAMA PRINCIPAL //
int main(void)
{
    const char *archivo = "alumnos.dat";
    size_t n = 0;

    printf(" Cuantos alumnos desea registrar? ");
    scanf("%zu", &n);
    getchar();                 //Limpia el '\n' pendiente //

    // Reserva dinámica de n alumnos //
    Alumno *grupo = malloc(n * sizeof(Alumno));
    if (!grupo) { perror("malloc"); return EXIT_FAILURE; }

    // Captura de datos//
    Alumno *p = grupo;
    for (size_t i = 0; i < n; ++i, ++p)
    {
        printf("\nAlumno %zu\n", i + 1);
        printf("Matrícula : ");  scanf("%d", &p->matricula); getchar();
        printf("Nombre    : ");  fgets(p->nombre, sizeof p->nombre, stdin);
        p->nombre[strcspn(p->nombre, "\n")] = '\0';
        printf("Promedio  : ");  scanf("%f", &p->promedio);  getchar();
    }

// Escritura a disco//
    escribir_alumnos(archivo, grupo, n);
    free(grupo);               // Liberamos la primera reserva */
// Lectura de disco (memoria dinámica de nuevo) //
    size_t leidos = 0;
    Alumno *copia = leer_alumnos(archivo, &leidos);

//Mostramos lo recuperado usando punteros//
    printf("\n= Datos leidos desde \"%s\" =\n", archivo);
    for (Alumno *q = copia; q < copia + leidos; ++q)   // recorre con puntero //
        printf("%d  %-30s  %.2f\n",
               q->matricula, q->nombre, q->promedio);

    free(copia);               //Siempre liberar lo asignado //
    return 0;
}
