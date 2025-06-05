#include <stdio.h>

int mcd(int a, int b)
{
    while(b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void main(void)
{
    int n1, n2;
    printf("Ingrese dos números enteros positivos: ");
    scanf("%d %d", &n1, &n2);
    printf("MCD = %d\n", mcd(n1, n2));
}
