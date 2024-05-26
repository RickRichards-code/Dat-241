#include <stdio.h>
#include <mpi.h>

#define NUM_NUMBERS 20

int main(int argc, char *argv[]) {
    int rank, size;
    int start, end, numbers_per_process;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    numbers_per_process = NUM_NUMBERS / size;
    start = rank * numbers_per_process * 2 + 2;
    end = start + numbers_per_process * 2;

    printf("Proceso %d generando números pares: ", rank);
    for (int i = start; i < end; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

