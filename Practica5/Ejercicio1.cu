#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 3

/*Funciones*/
__global__ void kernel_suma(float *v1, float *v2, int dim)
{
    int id = threadIdx.x + (blockIdx.x * blockDim.x);
    if (id < dim)
    {
        v1[id] = v1[id] + v2[id];
    }
}

int main()
{
    /*Declaracion de espacios de memoria en host*/
    float *A = (float *)malloc(N * sizeof(float));
    float *B = (float *)malloc(N * sizeof(float));
    float *resolver = (float *)malloc(N * sizeof(float));

    /*Declaración de espacios de memoria en device*/
    float *d_A, *d_B, *d_resolver;
    cudaMalloc((void **)&d_A, sizeof(float) * N);
    cudaMalloc((void **)&d_B, sizeof(float) * N);
    cudaMalloc((void **)&d_resolver, sizeof(float) * N);
    printf("Inicializo el vector A  y B del host\n");
    // Initialize host arrays
    memset(A, 0, sizeof(float) * N);
    memset(B, 0, sizeof(float) * N);
    for (int i = 0; i < N; i++)
    {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }
    printf("Array A: ");
    for (int j = 0; j < N; j++)
    {
        printf("%d,", A[j]);
    }
    printf("\nArray B: ");
    for (int k= 0; k < N; k++)
    {
        printf("%d,", B[k]);
    }

    /*Transferimos los datos del host al device*/
    cudaMemcpy(d_A, A, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, sizeof(float) * N, cudaMemcpyHostToDevice);
    dim3 nthreads(256);
    dim3 nblocks((N / nthreads.x) + (N % nthreads.x ? 1 : 0));
    /*
     *Las variables dim3 son vectores de 3 enteros que se utilizan para especificar dimensiones.
     Componentes x.y.z. si algun componente no se inicializa es 1.  
    */
    /*Función suma*/
    kernel_suma<<<nblocks.x, nthreads.x>>>(A,B, N);
    cudaDeviceSynchronize();
    /*Transfiero los datos de la GPU a la CPU*/
    cudaMemcpy(resolver, A, sizeof(float) * N, cudaMemcpyDeviceToHost);
    
    printf("\nResolver: ");
    for (int z = 0; z < N; z++)
    {
        printf("%d,", resolver[z]);
    }

    free(A);
    free(B);
    free(resolver);
    cudaFree(d_A);
    cudaFree(d_B);

    return 0;
}