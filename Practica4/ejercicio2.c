#include <mpi.h>
#include <stdio.h>

void transpuesta(int *a, int n)
{
    int i, j;
    int ij, ji, l;
    double tmp;
    ij = 0;
    l = -1;
    for (i = 0; i < n; i++)
    {
        l += n + 1;
        ji = l;
        ij += i + 1;
        for (j = i + 1; j < n; j++)
        {
            tmp = a[ij];
            a[ij] = a[ji];
            a[ji] = tmp;
            ij++;
            ji += n;
        }
    }
}

int main(int argc, char **argv)
{
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int P = size;
    int N = 0;
    for (int i = 1; i % P != 0 || i == P; i++)
    {
        N = i + 1;
    }
    printf("N=%d",N);
    int send[N][P], recv[N][P];

        /* Crear elemento unico */
        for (int i = 0; i < N; i++)
        {
           // printf("\nEl proceso %d ha enviado:", rank);
            for (int j = 0; j < P; j++)
            {
                send[i][j] = 1000 * i + j + N / P * rank;
                printf("%d ", send[i][j]);
            }
        }
            /* Imprimir envio
    for (int i = 0; i < N; i++)
    {
        printf("\nEl proceso %d ha enviado:", rank);
        for (int j = 0; j < P; j++)
        {
            printf("\nRank = %d Fila= %d  Columna=%d  =%i",rank,i,j,send[i][j]);
        }
    }*/

    MPI_Alltoall(&send[0][0], P * P, MPI_INT, &recv[0][0], P * P, MPI_INT, MPI_COMM_WORLD);

    /* Imprimir resultado */
    for (int i = 0; i < N; i++)
    {
        transpuesta(&recv[i * P][0], P);
        printf("\nEl proceso %d ha recibido:", rank);
        for (int j = 0; j < P; j++)
        {
            printf("\nRank = %d Fila= %d  Columna=%d  =%i",rank,i,j,recv[i][j]);
        }
    }

    MPI_Finalize();
}