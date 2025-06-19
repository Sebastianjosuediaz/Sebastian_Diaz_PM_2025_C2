#include <stdio.h>

const int MAX = 100;

void Lectura(int[], int);           // Prototipo de función para leer el arreglo
int Busca(int[], int, int);         // Prototipo de función para buscar un elemento

int main(void)
{
    int RES, ELE, TAM, VEC[MAX];

    do {
        printf("Ingrese el tamaño del arreglo: ");
        scanf("%d", &TAM);
    } while (TAM > MAX || TAM < 1); // Validación del tamaño del arreglo

    Lectura(VEC, TAM);

    printf("\nIngrese el elemento a buscar: ");
    scanf("%d", &ELE);

    RES = Busca(VEC, TAM, ELE); // Se llama a la función que busca el elemento

    if (RES)
        printf("\nEl elemento se encuentra en la posición %d", RES);
    else
        printf("\nEl elemento no se encuentra en el arreglo");

    return 0;
}

void Lectura(int A[], int T)
/* Función que lee un arreglo de T elementos */
{
    int I;
    for (I = 0; I < T; I++) {
        printf("Ingrese el elemento %d: ", I + 1);
        scanf("%d", &A[I]);
    }
}

int Busca(int A[], int T, int K)
/* Función que busca un elemento K en el arreglo A de tamaño T.
   Retorna la posición (1-based) si lo encuentra, o 0 si no lo encuentra. */
{
    int I = 0, BAN = 0, RES;

    while (I < T && !BAN) {
        if (A[I] == K)
            BAN = 1;
        else
            I++;
    }

    if (BAN)
        RES = I + 1; // Se suma 1 para que la posición sea legible (no desde cero)
    else
        RES = 0;

    return RES;
}
