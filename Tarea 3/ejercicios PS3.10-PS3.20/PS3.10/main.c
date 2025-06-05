#include <stdio.h>

void main(void)
{
    float precios[6] = {50.0, 70.0, 90.0, 120.0, 150.0, 200.0};
    int ventasLocalidad[6] = {0};
    float recaudacionTotal = 0.0;
    int cla, can;

    printf("Ingrese tipo de localidad (1-6) y cantidad de boletos (0 para terminar):\n");

    while(1)
    {
        scanf("%d", &cla);
        if(cla == 0) break;
        scanf("%d", &can);

        if(cla >= 1 && cla <= 6)
        {
            float monto = precios[cla - 1] * can;
            printf("Monto de venta: %.2f\n", monto);
            ventasLocalidad[cla - 1] += can;
            recaudacionTotal += monto;
        }
        else
        {
            printf("Tipo de localidad inválido.\n");
        }
    }

    printf("\nBoletos vendidos por localidad:\n");
    for(int i = 0; i < 6; i++)
    {
        printf("Localidad %d: %d boletos\n", i + 1, ventasLocalidad[i]);
    }

    printf("Recaudación total: %.2f\n", recaudacionTotal);
}
