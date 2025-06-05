#include <stdio.h>

void main(void)
{
    int N = 10; // Tamaño base de la figura

    for (int i = 1; i <= N; i++)
    {
        // Imprimir espacios iniciales para centrar
        for (int j = 0; j < N - i; j++)
            printf(" ");

        // Parte ascendente: i, i+1, ..., i+i-1
        for (int j = 0; j < i; j++)
            printf("%d ", (i + j) % 10);

        // Parte descendente: i+i-2, i+i-3, ..., i
        for (int j = i - 1; j >= 1; j--)
            printf("%d ", (i + j - 1) % 10);

        printf("\n");
    }

    // Segunda parte de la figura (simétrica inferior)
    for (int i = N - 1; i >= 1; i--)
    {
        // Imprimir espacios iniciales para centrar
        for (int j = 0; j < N - i; j++)
            printf(" ");

        // Parte ascendente
        for (int j = 0; j < i; j++)
            printf("%d ", (i + j) % 10);

        // Parte descendente
        for (int j = i - 1; j >= 1; j--)
            printf("%d ", (i + j - 1) % 10);

        printf("\n");
    }
}
