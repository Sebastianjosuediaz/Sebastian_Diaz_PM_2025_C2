#include <stdio.h>

void main(void)
{
    float temp[6][12], promedioRegion[6];
    float maxTemp = -100.0;

    printf("Ingrese temperaturas mensuales por región:\n");
    for(int r = 0; r < 6; r++)
    {
        float suma = 0.0;
        for(int m = 0; m < 12; m++)
        {
            scanf("%f", &temp[r][m]);
            suma += temp[r][m];
            if(temp[r][m] > maxTemp)
                maxTemp = temp[r][m];
        }
        promedioRegion[r] = suma / 12.0;
    }

    printf("Promedios regionales:\n");
    for(int r = 0; r < 6; r++)
        printf("Región %d: %.2f\n", r + 1, promedioRegion[r]);

    printf("Temperatura máxima registrada: %.2f\n", maxTemp);
}
