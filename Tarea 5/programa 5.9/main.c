#include <stdio.h>

const int MAX = 100;

void Lectura(int[], int);           // Prototipo de funci�n para leer el arreglo
int Busca(int[], int, int);         // Prototipo de funci�n para buscar un elemento

int main(void)
{
    int RES, ELE, TAM, VEC[MAX];

    do {
        printf("Ingrese el tama�o del arreglo: ");
        scanf("%d", &TAM);
    } while (TAM > MAX || TAM < 1); // Validaci�n del tama�o del arreglo

    Lectura(VEC, TAM);

    printf("\nIngrese el elemento a buscar: ");
    scanf("%d", &ELE);

    RES = Busca(VEC, TAM, ELE); // Se llama a la funci�n que busca el elemento

    if (RES)
        printf("\nEl elemento se encuentra en la posici�n %d", RES);
    else
        printf("\nEl elemento no se encuentra en el arreglo");

    return 0;
}

void Lectura(int A[], int T)
/* Funci�n que lee un arreglo de T elementos */
{
    int I;
    for (I = 0; I < T; I++) {
        printf("Ingrese el elemento %d: ", I + 1);
        scanf("%d", &A[I]);
    }
}

int Busca(int A[], int T, int K)
/* Funci�n que busca un elemento K en el arreglo A de tama�o T.
   Retorna la posici�n (1-based) si lo encuentra, o 0 si no lo encuentra. */
{
    int I = 0, BAN = 0, RES;

    while (I < T && !BAN) {
        if (A[I] == K)
            BAN = 1;
        else
            I++;
    }

    if (BAN)
        RES = I + 1; // Se suma 1 para que la posici�n sea legible (no desde cero)
    else
        RES = 0;

    return RES;
}
