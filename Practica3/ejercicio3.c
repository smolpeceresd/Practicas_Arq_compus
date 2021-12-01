#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int size, rank;
    int arr[size], recep1[size], envio[size], recep2[size];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = 0; i < size; i++)
    {
        arr[i] = rank + 1;
    }
    MPI_Reduce(&arr, &recep1, size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            envio[i] = rank+1;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            envio[i] = arr[i];
        }
    }
    MPI_Reduce(&envio, &recep2, size, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        int k = 0;
        while (k < size)
        {
            printf("La suma en la posicion %i es: %i \n",k,recep1[k]);
            printf("El producto en la posicion %i es: %i \n",k,recep2[k]);
            k = k + 1;
        };
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
