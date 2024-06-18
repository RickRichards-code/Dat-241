#include <stdio.h>
#include <stdlib.h> // Incluye la biblioteca estándar de C
#include <math.h>
#include <mpi.h>

#define MASTER 0
#define TAG 0

int main(int argc, char *argv[]) {
    int rank, size;
    long long int num_points = 1000000;
    long long int local_points;
    long long int local_inside = 0, global_inside = 0;
    double x, y, pi;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Distribute num_points among processes
    local_points = num_points / size;

    // Seed random number generator differently on each node
    srand(rank); // Semilla diferente para cada proceso

    // Each process performs its part of the calculation
    for (i = 0; i < local_points; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;
        if (x * x + y * y <= 1) {
            local_inside++;
        }
    }

    // Sum up the results from all processes
    MPI_Reduce(&local_inside, &global_inside, 1, MPI_LONG_LONG_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);

    // Master node calculates pi
    if (rank == MASTER) {
        pi = (double) global_inside / num_points * 4;
        printf("valor aproximado de pi: %f\n", pi);
    }

    MPI_Finalize();

    return 0;
}

