#include <stdio.h>
#include <omp.h>

int main() {
    int N = 10; // Número de términos en la serie
    int M = 4;  // Número de vectores (procesadores)

    // Calcula el tamaño de cada vector
    int vector_size = N / M;

    // Inicializa los vectores
    int vectors[M][vector_size];

    // Llena los vectores con la serie
    #pragma omp parallel for
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < vector_size; j++) {
            vectors[i][j] = 2 + i * 2 + j * 2;
        }
    }

    // Imprime los vectores
    for (int i = 0; i < M; i++) {
        printf("Vector %d: ", i);
        for (int j = 0; j < vector_size; j++) {
            printf("%d ", vectors[i][j]);
        }
        printf("\n");
    }

    return 0;
}

