#include <stdio.h>
#include <mpi.h>
#define TAG_MESSAGE 1
int main(int argc, char** argv)
{
int size;
int rank;
int numero;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(rank==0){
    printf("Con que valor quieres empezar el ciclo:\n");
    scanf("%i",&numero);
    MPI_Send(&numero, 1, MPI_INT, (rank + 1) % size, rank, MPI_COMM_WORLD);
    printf("Proceso %i envia %d\n", rank,numero);
}else if(rank < size-1){
        MPI_Recv(&numero,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Proceso: %i recibe el valor: %i\n",rank,numero);
        MPI_Send(&numero,1,MPI_INT,rank+1,rank,MPI_COMM_WORLD);
}else if(rank == size-1){
    MPI_Recv(&numero,1,MPI_INT,rank-1,rank-1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("Proceso: %i recibe el valor: %i y se acaba el envio\n",rank,numero);
}
MPI_Finalize();
return 0;
}