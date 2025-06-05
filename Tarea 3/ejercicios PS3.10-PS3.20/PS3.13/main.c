#include <stdio.h>
#include <math.h>

int esPrimo(int n)
{
    if(n < 2) return 0;
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0) return 0;
    return 1;
}

void main(void)
{
    int n1, n2;
    printf("Ingrese rango [n1, n2]: ");
    scanf("%d %d", &n1, &n2);

    printf("Pares de primos gemelos:\n");
    for(int i = n1; i <= n2 - 2; i++)
    {
        if(esPrimo(i) && esPrimo(i + 2))
            printf("(%d, %d)\n", i, i + 2);
    }
}
