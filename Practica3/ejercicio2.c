#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int numero;
    int my_value; // donde lo guardo
    int deVuelta;
    int numeros_enviar[size];
    int numeros_recividos[size];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        for (int i = 0; i < size; i++)
        {
            numeros_enviar[i] = i;
        }
        MPI_Scatter(&numeros_enviar, 1, MPI_INT, &my_value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("El proceso 0 envia:\n");
        int k = 0;
        while (k < size)
        {
            printf("Iteracion %i - %i\n", k, numeros_enviar[k]);
            k = k + 1;
        };
        MPI_Gather(&numeros_recividos, 1, MPI_INT, numeros_recividos, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(NULL, 1, MPI_INT, &my_value, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("El proceso %d ha recibido el valor de = %d.\n", rank, my_value);
        deVuelta = my_value + rank;
        MPI_Gather(&deVuelta, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if (rank == 0)
    {
        while (!numeros_recividos[size - 1])
        {
        };

        printf("El proceso 0 ha recibido:\n");
        int j = 0;
        while (j < size)
        {
            printf("Iteracion %i - %i\n", j, numeros_recividos[j]);
            j = j + 1;
        };
    }

    MPI_Finalize();
    return 0;
}