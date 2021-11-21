#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
    int rank,count,size;
    char msg[20]="hello word";

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(rank==0){
      printf("Soy el nodo maestro y envio el mensaje : -hello word -.\n\n");
      printf("Introduce cuantas veces el nodo maestro esta dispuesto a escuchar\n");
      scanf("%d", &count);
      MPI_Send(&count, 1, MPI_INT, 1, 101, MPI_COMM_WORLD);
      MPI_Send(&msg, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
      printf("Proceso %d envia : %s  - al proceso %d\n", rank,msg,1);
  }

    if(rank!=0)MPI_Recv(&count, 1, MPI_INT, 0, 101, MPI_COMM_WORLD,&status);
    while (1)
    {
        char msg2[20];
        if(rank==0){
        MPI_Recv(&msg2, 13, MPI_CHAR, 1, 100, MPI_COMM_WORLD,&status);
        printf("Proceso %d ha recibido %s \n", rank, msg);
            --count;
            if(count==0){
                break;
            }else{
                MPI_Send(&msg2,13, MPI_CHAR, 1, 100, MPI_COMM_WORLD);
                printf("Proceso %d envia : %s  - al proceso %d\n", rank,msg,1);
            }
        }else{
            MPI_Recv(&msg2, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD,&status);
            printf("Proceso %d ha recibido %s \n", rank, msg);
            --count;
            if(count==0){
                MPI_Send(&msg2, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD);
                printf("Proceso %d envia : %s  - al proceso %d\n", rank,msg,0);
                break;
            }else{
                MPI_Send(&msg2, 13, MPI_CHAR, 0, 100, MPI_COMM_WORLD);
                printf("Proceso %d envia : %s  - al proceso %d\n", rank,msg,0);
            }
        }
    }
    printf("Proceso %d termina\n", rank);
    MPI_Finalize();
    return 0;
}