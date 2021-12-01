#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int size;
    int rank;
    int numero;
    int my_value; // donde lo guardo
    int deVuelta;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int numeros_enviar[size*2];
        int numeros_recibidos[size*2];
        for (int i = 0; i < size*2; i++)
        {
            numeros_enviar[i] = i;
        }
        MPI_Scatter(&numeros_enviar, ((size*2)/size), MPI_INT, &numeros_recibidos, ((size*2)/size), MPI_INT, 0, MPI_COMM_WORLD);
        printf("El proceso %d ha recibido el valor de :\n", rank);
        int k=0;
        while (k<((size*2)/size))
        {
            printf("Recibido:%d\n",numeros_recibidos[k]);
            k=k+1;
        }
        MPI_Gather(&numeros_recibidos, ((size*2)/size), MPI_INT, numeros_recibidos, ((size*2)/size), MPI_INT, 0, MPI_COMM_WORLD);
        
        while (!numeros_recibidos[(size*2) - 1]){};

        printf("El proceso 0 ha recibido:\n");
        int j = 0;
        while (j < size*2)
        {
            printf("Iteracion %i - %i\n", j, numeros_recibidos[j]);
            j = j + 1;
        };
    }
    else
    {
        int numeros_enviar[((size*2)/size)];
        int numeros_recibidos[((size*2)/size)];
        int deVuelta[((size*2)/size)];
        MPI_Scatter(NULL, 0, MPI_INT, &numeros_recibidos, ((size*2)/size), MPI_INT, 0, MPI_COMM_WORLD);
        printf("El proceso %d ha recibido el valor de :\n", rank);
        int k=0;
        while (k<((size*2)/size))
        {
            printf("Recibido:%d\n",numeros_recibidos[k]);
            k=k+1;
        }
        
        for(int i=0; i<((size*2)/size);i++){
            deVuelta[i]=numeros_recibidos[i]+rank;
        }
        MPI_Gather(&deVuelta, ((size*2)/size), MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
