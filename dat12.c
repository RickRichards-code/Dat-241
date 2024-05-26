#include <stdio.h>
#include <mpi.h>

#define MASTER 0
#define TAG_REQUEST 1
#define TAG_RESULT 2

int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int rank, size;
    int n;
    int result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == MASTER) {
        printf("Ingrese el término de Fibonacci que desea calcular: ");
        scanf("%d", &n);

        // Enviar solicitudes a los esclavos para calcular los términos de Fibonacci
        int term;
        for (term = 0; term < n; term++) {
            MPI_Send(&term, 1, MPI_INT, term % (size - 1) + 1, TAG_REQUEST, MPI_COMM_WORLD);
            MPI_Recv(&result, 1, MPI_INT, term % (size - 1) + 1, TAG_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Término %d de Fibonacci: %d\n", term, result);
        }
        
        // Enviar señal de terminación a los esclavos
        for (int i = 1; i < size; i++) {
            term = -1;
            MPI_Send(&term, 1, MPI_INT, i, TAG_REQUEST, MPI_COMM_WORLD);
        }
    } else {
        // Esperar solicitudes de cálculo de términos de Fibonacci
        int term;
        while (1) {
            MPI_Recv(&term, 1, MPI_INT, MASTER, TAG_REQUEST, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (term == -1)
                break; // Señal de terminación
            result = fibonacci(term);
            MPI_Send(&result, 1, MPI_INT, MASTER, TAG_RESULT, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}

