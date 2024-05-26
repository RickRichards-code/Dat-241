#include <stdio.h>
#include <omp.h>

int main() {
    int a, b;
    printf("Ingresa el valor de a: ");
    scanf("%d", &a);

    printf("Ingresa el valor de b: ");
    scanf("%d", &b);
    
    int resultado_multiplicacion = 0;
    int cociente_division = 0;

    #pragma omp parallel for reduction(+:resultado_multiplicacion)
    for (int i = 0; i < b; i++) {
        resultado_multiplicacion += a;
    }

    while (a >= b) {
        a -= b;
        cociente_division++;
    }

    printf("producto: %d\n", resultado_multiplicacion);
    printf("division: %d\n",cociente_division);

    return 0;
}

