#include <stdio.h>
#include <mpi.h>

#define N 10 // numero de terminos

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char *argv[]) {
    int rank, size;
    int i, termino, resultado;
    int resultados[N][2]; // Array para almacenar los resultados y sus índices

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("se requiere mas de 2 terminos\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        // Proceso maestro
        for (i = 0; i < N; i++) {
            // Enviar término a calcular a cada proceso esclavo
            int destino = (i % (size - 1)) + 1;
            MPI_Send(&i, 1, MPI_INT, destino, 0, MPI_COMM_WORLD);
        }

        // Recibir resultados de los procesos esclavos
        for (i = 0; i < N; i++) {
            int buffer[2]; // Buffer para recibir el índice y el resultado
            MPI_Recv(buffer, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int indice = buffer[0];
            resultado = buffer[1];
            resultados[indice][0] = indice;
            resultados[indice][1] = resultado;
        }

        // Imprimir resultados en orden
        printf("serie de fibonacci:\n");
        for (i = 0; i < N; i++) {
            printf("%d ", resultados[i][1]);
        }
        printf("\n");
    } else {
        // Proceso esclavo
        for (i = rank - 1; i < N; i += (size - 1)) {
            // Recibir término a calcular del proceso maestro
            MPI_Recv(&termino, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            resultado = fibonacci(termino);
            int buffer[2] = {termino, resultado}; // Buffer para enviar el índice y el resultado
            // Enviar resultado al proceso maestro
            MPI_Send(buffer, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

