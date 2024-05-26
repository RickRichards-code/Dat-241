#include <stdio.h>
#include <mpi.h>

#define N 100

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Verificar que el número de procesos sea igual a N
    if (size != N) {
        if (rank == 0) {
            printf("Este programa debe ejecutarse con exactamente %d procesos.\n", N);
        }
        MPI_Finalize();
        return 1;
    }

    // Inicializar matriz y vector
    double matrix[N][N];
    double vector[N];
    double result[N];
    // Inicializar valores (omitiendo para brevedad)

    // Dividir filas de la matriz y el vector entre los procesos
    int rows_per_process = N / size;
    double local_matrix[rows_per_process][N];
    double local_vector[N];
    double local_result[rows_per_process];

    // Distribuir datos entre los procesos
    MPI_Scatter(matrix, rows_per_process * N, MPI_DOUBLE, local_matrix, rows_per_process * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector, N, MPI_DOUBLE, local_vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Realizar la multiplicación local
    for (int i = 0; i < rows_per_process; i++) {
        local_result[i] = 0.0;
        for (int j = 0; j < N; j++) {
            local_result[i] += local_matrix[i][j] * local_vector[j];
        }
    }

    // Reunir los resultados parciales
    MPI_Gather(local_result, rows_per_process, MPI_DOUBLE, result, rows_per_process, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // El proceso 0 imprime el resultado
    if (rank == 0) {
        printf("Resultado de la multiplicación:\n");
        for (int i = 0; i < N; i++) {
            printf("%f ", result[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

