
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size, N = 5;  // ← Asigna directamente el valor de N
    int i, suma_local = 0, suma_total = 0;
    float promedio;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Ya no usamos scanf, N está fijo en 5

    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    srand(time(NULL) + rank);
    for (i = 0; i < N; i++) {
        int num = rand() % 1000;
        suma_local += num;
    }

    MPI_Reduce(&suma_local, &suma_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        promedio = (float)suma_total / (N * size);
    }

    MPI_Bcast(&promedio, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    printf("Proceso %d recibió el promedio: %.2f\n", rank, promedio);
    fflush(stdout);

    MPI_Finalize();
    return 0;
}
