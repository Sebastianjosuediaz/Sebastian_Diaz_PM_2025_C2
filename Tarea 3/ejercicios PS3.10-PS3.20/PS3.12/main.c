#include <stdio.h>
#define M 5
#define N 4

void intercambiarFilas(float mat[M][N])
{
    for(int i = 0; i < M / 2; i++)
    {
        for(int j = 0; j < N; j++)
        {
            float temp = mat[i][j];
            mat[i][j] = mat[M - 1 - i][j];
            mat[M - 1 - i][j] = temp;
        }
    }
}

void main(void)
{
    float mat[M][N];

    printf("Ingrese los valores de la matriz (%d x %d):\n", M, N);
    for(int i = 0; i < M; i++)
        for(int j = 0; j < N; j++)
            scanf("%f", &mat[i][j]);

    intercambiarFilas(mat);

    printf("Matriz después de intercambiar filas:\n");
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
            printf("%.2f ", mat[i][j]);
        printf("\n");
    }
}
