#include <stdio.h>

void main(void)
{
    int N;
    printf("Ingrese N: ");
    scanf("%d", &N);

    for(int i = 1; i <= N; i++)
    {
        for(int j = 0; j < N - i; j++) printf(" ");
        for(int j = 1; j <= i; j++) printf("%d ", j);
        for(int j = i - 1; j >= 1; j--) printf("%d ", j);
        printf("\n");
    }
}
