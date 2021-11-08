#include <mpi.h>
#include <stdio.h>


int main (int argc, char** argv) {
    int nproc; //numero de procesos
    int myrank; //id del proceso
    double start,finish,time;

    MPI_Init (&argc, &argv); //Inicializa la aplicacion
    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();
    MPI_Comm_size (MPI_COMM_WORLD, &nproc); //cuantos procesos participan en la aplicacion?
    MPI_Comm_rank (MPI_COMM_WORLD, &myrank); 
    MPI_Barrier(MPI_COMM_WORLD);
    finish = MPI_Wtime();
    time = finish-start;
    printf("soy el proceso %d de un total de %d. TIME: %f \n", myrank, nproc,time);
    //Para registrar el tiempo
    char *filename = "grafico.csv";
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "%i,%f\n",myrank,(time));
    fclose(fp);
    MPI_Finalize(); //Fin
}