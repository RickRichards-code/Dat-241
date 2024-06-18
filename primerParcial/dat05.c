#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void matrix_vector_mult(int *local_matrix, int *vector, int *local_result, int local_n, int n) {
    for (int i = 0; i < local_n; i++) {
        local_result[i] = 0;
        for (int j = 0; j < n; j++) {
            local_result[i] += local_matrix[i * n + j] * vector[j];
        }
    }
}

int main(int argc, char* argv[]) {
    int rank, size;
    int n; // Dimensión de la matriz y el vector
    int *matrix = NULL, *vector = NULL;
    int *local_matrix, *local_result;
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Proceso raíz inicializa la matriz y el vector
    if (rank == 0) {
        printf("Ingrese la dimensión de la matriz y el vector (n): ");
        scanf("%d", &n);

        matrix = (int*) malloc(n * n * sizeof(int));
        vector = (int*) malloc(n * sizeof(int));

        printf("Ingrese los elementos de la matriz %dx%d:\n", n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i * n + j]);
            }
        }

        printf("Ingrese los elementos del vector de dimensión %d:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &vector[i]);
        }
    }

    // Broadcast the dimension n to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_n = n / size; // Asumimos que n es divisible por size

    // Cada proceso recibe una parte de la matriz y el vector completo
    local_matrix = (int*) malloc(local_n * n * sizeof(int));
    local_result = (int*) malloc(local_n * sizeof(int));

    MPI_Scatter(matrix, local_n * n, MPI_INT, local_matrix, local_n * n, MPI_INT, 0, MPI_COMM_WORLD);
    
    // En caso de que no se necesite en otros procesos, podemos liberar esta memoria
    if (rank == 0) {
        free(matrix);
    }

    if (rank != 0) {
        vector = (int*) malloc(n * sizeof(int));
    }
    MPI_Bcast(vector, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada proceso realiza la multiplicación para sus filas
    matrix_vector_mult(local_matrix, vector, local_result, local_n, n);

    // Recoger los resultados en el proceso raíz
    int *result = NULL;
    if (rank == 0) {
        result = (int*) malloc(n * sizeof(int));
    }
    MPI_Gather(local_result, local_n, MPI_INT, result, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Proceso raíz imprime el resultado
    if (rank == 0) {
        printf("Resultado de la multiplicación matriz-vector:\n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", result[i]);
        }
        free(result);
    }

    // Liberar memoria
    free(local_matrix);
    free(local_result);
    free(vector);

    MPI_Finalize();
    return 0;
}

