#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
    int rank,count=0,size,lenght=10000,max;
    float a[10000]={};

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  for(int i=0;i<lenght;i++){
      a[i]=(float)rank;
  }
  if(rank==0){
      printf("Introduce cuantas veces el nodo maestro esta dispuesto a enviar\n");
      scanf("%d", &max);
      MPI_Send(&max, 1, MPI_INT, 1, 101, MPI_COMM_WORLD);
      MPI_Send(&a, lenght, MPI_FLOAT, 1, 100, MPI_COMM_WORLD);
      count++;
      printf("Proceso %d envia : A - al proceso %d\n", rank,1);
  }

    if(rank!=0)MPI_Recv(&max, 1, MPI_INT, 0, 101, MPI_COMM_WORLD,&status);
    while (1)
    {
        float b[10000]={};
        int envio_recibo;
        if(rank==0){
            //Analizo los envios
            envio_recibo=1;
            if(count<max){
                //como ya he enviado 1, espero la proxima recepcion
                MPI_Recv(&b,lenght, MPI_INT, envio_recibo, 100, MPI_COMM_WORLD,&status);
                printf("El proceso %d ha recibido\n",rank);
                int j=0;while (j<lenght){printf("Iteracion %i - %0.1f\n",j,b[j]);j=j+1;};
                MPI_Send(&a, lenght, MPI_FLOAT, envio_recibo, 100, MPI_COMM_WORLD);
                printf("Proceso %d envia : A - al proceso %d\n", rank,envio_recibo);
                count++;
            }else{
                MPI_Recv(&b,lenght, MPI_INT, envio_recibo, 100, MPI_COMM_WORLD,&status);
                printf("El proceso %d ha recibido\n",rank);
                int j=0;while (j<lenght){printf("Iteracion %i - %0.1f\n",j,b[j]);j=j+1;};
                break;
            }         
        
        }else if(rank==1){
            //Analizo las recepciones
            envio_recibo=0;
                MPI_Recv(&b,lenght, MPI_INT, envio_recibo, 100, MPI_COMM_WORLD,&status);
                printf("El proceso %d ha recibido\n",rank);
                int j=0;while (j<lenght){printf("Iteracion %i - %0.1f\n",j,b[j]);j=j+1;};
                count++;
                MPI_Send(&a, lenght, MPI_FLOAT, envio_recibo, 100, MPI_COMM_WORLD);
                printf("Proceso %d envia : A - al proceso %d\n", rank,envio_recibo);
                if(count==max){
                    break;
                }
        };

    }
    printf("Proceso %d termina\n", rank);
    MPI_Finalize();
    return 0;
}