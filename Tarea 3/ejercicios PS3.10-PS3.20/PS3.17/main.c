#include <stdio.h>

void main(void)
{
    int N;

    printf("Ingrese un número entero positivo N: ");
    scanf("%d", &N);

    for(int i = 1; i <= N; i++)
    {
        // Imprimir espacios
        for(int j = 0; j < N - i; j++)
            printf(" ");

        // Imprimir parte ascendente
        for(int j = 1; j <= i; j++)
            printf("%d ", j);

        // Imprimir parte descendente
        for(int j = i - 1; j >= 1; j--)
            printf("%d ", j);

        printf("\n");
    }
}
