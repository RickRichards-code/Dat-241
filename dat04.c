#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n;

    // Solicita al usuario que ingrese el valor de N
    printf("Ingresa el valor de N: ");
    scanf("%d", &n);

    // Crea una matriz NxN y un vector de dimensión N
    double *matrix = (double *)malloc(n * n * sizeof(double));
    double *vector = (double *)malloc(n * sizeof(double));
    double *result = (double *)calloc(n, sizeof(double));

    // Solicita al usuario que ingrese los valores de la matriz
    printf("Ingresa los valores de la matriz (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i * n + j]);
        }
    }

    // Solicita al usuario que ingrese los valores del vector
    printf("Ingresa los valores del vector (%d elementos):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vector[i]);
    }

    // Realiza la multiplicación de matriz por vector utilizando OpenMP
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += matrix[i * n + j] * vector[j];
        }
    }

    // Imprime el resultado
    printf("Resultado:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");

    // Libera la memoria
    free(matrix);
    free(vector);
    free(result);

    return 0;
}

