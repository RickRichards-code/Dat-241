#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int n = 10; // numerod de terminos
    printf("ingrese el numero de terminos: \n");
    scanf("%d", &n);
    int m = 4;  // numero de procesadores
    n = n*m;

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_n = n / size;  // Términos por procesador
    int start = rank * local_n * 2 + 2;  // Inicio de la serie para el procesador actual
    int end = start + local_n * 2 - 2;  // Fin de la serie para el procesador actual

    if (rank == size - 1) {
        end += (n % size) * 2;  // Ajuste para el último procesador
    }

    int results[100];  // Suponiendo un límite de 100 términos en total

    int count = 0;
    for (int i = start; i <= end; i += 2) {
        results[count] = i;
        count++;
    }

    // En otro momento del programa, se puede imprimir la matriz de resultados
    if (rank == 0) {
        for (int i = 0; i < count; i++) {
            printf("%d ", results[i]);
        }
    }
    printf("\n");

    MPI_Finalize();

    return 0;
}

