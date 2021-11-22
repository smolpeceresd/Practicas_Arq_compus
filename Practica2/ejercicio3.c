#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define TAG_MESSAGE 1
int main(int argc, char** argv)
{
int size;
int rank,lenght=10000;
float a[10000]={},b[10000]={};
MPI_Status status;;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  for(int i=0;i<lenght;i++){
      a[i]=(float)rank;
  }

if(rank==0){
    MPI_Send(&a, lenght, MPI_FLOAT, (rank + 1) % size, TAG_MESSAGE, MPI_COMM_WORLD);
    printf("Proceso %d envia : A - al proceso %d\n", rank,(rank + 1) % size);
    MPI_Recv(&b, lenght, MPI_FLOAT, (rank + size - 1) % size, TAG_MESSAGE, MPI_COMM_WORLD,&status);
    printf("Proces %d received\n", rank);
    int j=0;while (j<lenght){printf("Iteracion %i - %0.1f\n",j,b[j]);j=j+1;};
}else{
    MPI_Recv(&b, lenght, MPI_FLOAT, (rank + size - 1) % size, TAG_MESSAGE, MPI_COMM_WORLD,&status);
    printf("Proces %d received\n", rank);
    int j=0;while (j<lenght){printf("Iteracion %i - %0.1f\n",j,b[j]);j=j+1;};
    printf("El proceso %d termina\n",rank);
    MPI_Send(&a, lenght, MPI_FLOAT, (rank + 1) % size, TAG_MESSAGE, MPI_COMM_WORLD);
    printf("Proceso %d envia : A - al proceso %d\n", rank,(rank + 1) % size);
}
MPI_Finalize();
return 0;
}