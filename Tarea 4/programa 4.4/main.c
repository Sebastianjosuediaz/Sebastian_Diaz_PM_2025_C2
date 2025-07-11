#include <stdio.h>

/* Prueba de variables globales, locales y est�ticas.
   El programa utiliza funciones que usan diferentes tipos de variables. */

int f1(void);
int f2(void);
int f3(void);  // Prototipos de funciones.
int f4(void);

int K = 3; /* Variable global. */

int main(void)  // main debe devolver int
{
    int I;
    for (I = 1; I <= 3; I++)
    {
        printf("\nEl resultado de la funci�n f1 es: %d", f1());
        printf("\nEl resultado de la funci�n f2 es: %d", f2());
        printf("\nEl resultado de la funci�n f3 es: %d", f3());
        printf("\nEl resultado de la funci�n f4 es: %d", f4());
        printf("\n----------------------------");
    }

    return 0;
}

int f1(void)
/* La funci�n f1 utiliza la variable global. */
{
    K += K;  // Modifica la variable global
    return K;
}

int f2(void)
/* La funci�n f2 utiliza la variable local. */
{
    int K = 1;
    K++;
    return K;  // Retorna siempre 2
}

int f3(void)
/* La funci�n f3 utiliza la variable est�tica. */
{
    static int K = 8;  // Mantiene su valor entre llamadas
    K += 2;
    return K;
}

int f4(void)
/* La funci�n f4 utiliza dos variables con el mismo nombre:
   local y global. */
{
    int k_local = 5;  // Renombramos para evitar conflicto
    k_local = k_local + K;  // Usa K (global)
    return k_local;
}
