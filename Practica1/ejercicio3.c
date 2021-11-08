#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

  int numero = 999;

int main(int argc, char **argv)
{
    int nprocesos;
    int ID;

    MPI_Init(&argc, &argv); //Inicia el MIP

    MPI_Comm_size(MPI_COMM_WORLD, &nprocesos); //Devuelve en la variable nprocesos, el número de procesos actuales en el comunicador del primer parámetro.
    MPI_Comm_rank(MPI_COMM_WORLD, &ID);        //Devuelve el id del proceso actual dentro del comunicador.

    // Para hacer rebote tiene que haber un máximo de solo dos procesos
    if (nprocesos != 2)
    {
        printf("El numero de procesos debe ser igual a 2");
        exit(0);
    }
    int contador = 0;
    int rebote = (ID + 1) % 2;
    if (ID == 0 && numero == 999)
    {
        printf("Introduce el valor entero que enviaremos a todos los procesos:\n");
        scanf("%i", &numero);
        printf(" ----> %i ha sido introducido.\n", numero);
    }


    while (contador < numero)
    {
        if (ID == contador % 2)
        {
            contador++;
            MPI_Send(&contador, 1, MPI_INT, rebote, 0, MPI_COMM_WORLD);
            printf("PAR: %d enviado y contador suma %d mas %d\n",
                   numero, contador, rebote);
        }
        else
        {
            MPI_Recv(&contador, 1, MPI_INT, rebote, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            printf("IMPAR: %d enviado y contador suma %d mas %d\n",
                   numero, contador, rebote);
        }
        
    }

    MPI_Finalize();
}