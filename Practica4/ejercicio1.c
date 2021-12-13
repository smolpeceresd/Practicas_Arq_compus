#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int send[4], recv[4];

    if (size == 4)
    {
        for (int i = 0; i < size; i++)
        {
            send[i] = (i + 1) + rank * size;
        }
        printf("El proceso %d envio: %d %d %d %d\n", rank, send[0], send[1], send[2], send[3]);
        MPI_Alltoall(&send, 1, MPI_FLOAT, &recv, 1, MPI_INT, MPI_COMM_WORLD);
        printf("Tras la transposicion el proceso %d recibio: %d %d %d %d\n", rank, recv[0], recv[1], recv[2], recv[3]);
    }
    else
    {
        printf("El numero de procesos debe ser 4.\n");
    }

    MPI_Finalize();
}