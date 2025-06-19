#include <stdio.h>

/* Búsqueda binaria. */

const int MAX = 100;

void Lectura(int[], int);
int Binaria(int[], int, int);

int main(void)
{
    int RES, ELE, TAM, VEC[MAX];

    do {
        printf("Ingrese el tamaño del arreglo: ");
        scanf("%d", &TAM);
    } while (TAM > MAX || TAM < 1); // Validación del tamaño

    Lectura(VEC, TAM);

    printf("\nIngrese el elemento a buscar: ");
    scanf("%d", &ELE);

    RES = Binaria(VEC, TAM, ELE); // Búsqueda binaria

    if (RES)
        printf("\nEl elemento se encuentra en la posición: %d", RES);
    else
        printf("\nEl elemento no se encuentra en el arreglo");

    return 0;
}

void Lectura(int A[], int T)
/* Lee un arreglo ordenado en forma creciente */
{
    int I;
    for (I = 0; I < T; I++) {
        printf("Ingrese el elemento %d (ordenado en forma creciente): ", I + 1);
        scanf("%d", &A[I]);
    }
}

int Binaria(int A[], int T, int E)
/* Búsqueda binaria de E en A[0...T-1] */
/* Retorna la posición (base 1) si lo encuentra, o 0 si no */
{
    int IZQ = 0, DER = T - 1, CEN;

    while (IZQ <= DER) {
        CEN = (IZQ + DER) / 2;

        if (E == A[CEN])
            return CEN + 1; // Retorna posición (1-based)
        else if (E > A[CEN])
            IZQ = CEN + 1;
        else
            DER = CEN - 1;
    }

    return 0;
}
