#include <stdio.h>
#include <omp.h>

void seriePares(int *series, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        series[i] = (i + 1) * 2;
    }
}

int main() {
    int N, M;
    
    printf("ingrese el numero de terminos N: ");
    scanf("%d", &N);
    
    printf("ingrese el numero de procesadores M (menor que 8): ");
    scanf("%d", &M);

    // estableecemos el numero de procesadores
    omp_set_num_threads(M);

    int series[N];

    // llamamos a la funcion
    seriePares(series, N);

    // imprime la serie
    printf("La serie es: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", series[i]);
    }
    printf("\n");

    return 0;
}

