#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int numero;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Dime de que valor quieres calcular su cuadrado, y pasarlo en anillo:\n");
        scanf("%i", &numero);
        numero = numero * numero;
    }
    MPI_Bcast(&numero, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("El proceso %d, envía el valor: %i\n", rank, numero);
    }
    else
    {
        printf("El proceso %d, ha recibido el valor: %i\n", rank, numero);
    }
    MPI_Finalize();
    return 0;
}