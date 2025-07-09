#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nombre[50];
    float promedio;
} Alumno;

void guardarAlumnos(Alumno alumnos[], int n, const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "wb");
    if (!file) {
        perror("Error al abrir el archivo");
        return;
    }
    fwrite(alumnos, sizeof(Alumno), n, file);
    fclose(file);
}

int leerAlumnos(Alumno alumnos[], const char* nombreArchivo) {
    FILE* file = fopen(nombreArchivo, "rb");
    if (!file) {
        perror("Error al abrir el archivo");
        return 0;
    }
    int i = 0;
    while (fread(&alumnos[i], sizeof(Alumno), 1, file) == 1) {
        i++;
    }
    fclose(file);
    return i;
}

// bucle pr nombre
void ordenarPorNombre(Alumno alumnos[], int n) {
    Alumno temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(alumnos[j].nombre, alumnos[j+1].nombre) > 0) {
                temp = alumnos[j];
                alumnos[j] = alumnos[j+1];
                alumnos[j+1] = temp;
            }
        }
    }
}

// bucle por promedio
void ordenarPorPromedio(Alumno alumnos[], int n) {
    Alumno temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (alumnos[j].promedio > alumnos[j+1].promedio) {
                temp = alumnos[j];
                alumnos[j] = alumnos[j+1];
                alumnos[j+1] = temp;
            }
        }
    }
}

void imprimirAlumnos(Alumno alumnos[], int n) {
    printf("\nLista de alumnos:\n");
    for (int i = 0; i < n; i++) {
        printf("%s - %.2f\n", alumnos[i].nombre, alumnos[i].promedio);
    }
}

int main() {
    Alumno alumnos[MAX];
    int n, opcion;
    const char* archivo = "alumnos.bin";

    printf("¿Cuantos alumnos quieres ingresar? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nAlumno %d:\n", i + 1);
        printf("Nombre: ");
        getchar();
        fgets(alumnos[i].nombre, sizeof(alumnos[i].nombre), stdin);
        alumnos[i].nombre[strcspn(alumnos[i].nombre, "\n")] = '\0';
        printf("Promedio: ");
        scanf("%f", &alumnos[i].promedio);
    }

    guardarAlumnos(alumnos, n, archivo);

    int total = leerAlumnos(alumnos, archivo);

    printf("\nOpciones de ordenamiento:\n1. Por nombre (A-Z)\n2. Por promedio\nElige una opción: ");
    scanf("%d", &opcion);

    if (opcion == 1) {
        ordenarPorNombre(alumnos, total);
    } else if (opcion == 2) {
        ordenarPorPromedio(alumnos, total);
    } else {
        printf("Opción inválida.\n");
        return 1;
    }

    imprimirAlumnos(alumnos, total);

    return 0;
}
