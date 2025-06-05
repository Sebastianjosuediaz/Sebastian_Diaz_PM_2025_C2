#include <stdio.h>
#include <math.h>

double factorial(int n)
{
    double res = 1;
    for(int i = 1; i <= n; i++) res *= i;
    return res;
}

void main(void)
{
    double x, seno = 0.0, termino, error = 0.001;
    int signo = 1, exponente = 1, cont = 0;

    printf("Ingrese valor de x (radianes): ");
    scanf("%lf", &x);

    do
    {
        termino = pow(x, exponente) / factorial(exponente);
        seno += signo * termino;
        exponente += 2;
        signo *= -1;
        cont++;
    } while(termino > error);

    printf("sen(x) = %.6f con %d términos\n", seno, cont);
}
