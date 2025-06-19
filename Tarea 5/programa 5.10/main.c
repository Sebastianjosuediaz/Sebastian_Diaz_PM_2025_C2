#include <stdio.h>

/* B�squeda secuencial en arreglos ordenados en forma creciente. */

const int MAX = 100;

void Lectura(int[], int);
int Busca(int[], int, int);

int main(void)
{
    int RES, ELE, TAM, VEC[MAX];

    do {
        printf("Ingrese el tama�o del arreglo: ");
        scanf("%d", &TAM);
    } while (TAM > MAX || TAM < 1); // Verifica que el tama�o sea v�lido

    Lectura(VEC, TAM);

    printf("\nIngrese el elemento a buscar: ");
    scanf("%d", &ELE);

    RES = Busca(VEC, TAM, ELE); // B�squeda secuencial

    if (RES)
        printf("\nEl elemento se encuentra en la posici�n: %d", RES);
    else
        printf("\nEl elemento no se encuentra en el arreglo");

    return 0;
}

void Lectura(int A[], int T)
/* Lee un arreglo de T elementos. */
{
    int I;
    for (I = 0; I < T; I++) {
        printf("Ingrese el elemento %d (en orden creciente): ", I + 1);
        scanf("%d", &A[I]);
    }
}

int Busca(int A[], int T, int K)
/* B�squeda secuencial optimizada para arreglo ordenado de forma creciente */
{
    int I = 0;
    while (I < T && A[I] < K)
        I++;

    if (I < T && A[I] == K)
        return I + 1;
    else
        return 0;
}
