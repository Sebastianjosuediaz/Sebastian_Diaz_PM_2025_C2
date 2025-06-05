#include <stdio.h>
#include <math.h>

void main(void)
{
    printf("Valores válidos de T, P, R:\n");
    for(int T = 1; T <= 10; T++)
        for(int P = 1; P <= 10; P++)
            for(int R = 1; R <= 10; R++)
            {
                double expr = 7 * pow(T, 4) - 6 * pow(P, 3) + 12 * pow(R, 5);
                if(expr < 5850)
                    printf("T=%d, P=%d, R=%d -> %.0f\n", T, P, R, expr);
            }
}
