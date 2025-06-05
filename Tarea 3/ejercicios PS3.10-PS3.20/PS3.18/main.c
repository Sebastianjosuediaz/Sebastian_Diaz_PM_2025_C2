#include <stdio.h>
#define FILAS 3
#define COLUMNAS 4

void main(void)
{
    int mat[FILAS][COLUMNAS];

    printf("Ingrese elementos de la matriz:\n");
    for(int i = 0; i < FILAS; i++)
        for(int j = 0; j < COLUMNAS; j++)
            scanf("%d", &mat[i][j]);

    printf("Recorrido por columnas:\n");
    for(int j = 0; j < COLUMNAS; j++)
    {
        for(int i = 0; i < FILAS; i++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}
