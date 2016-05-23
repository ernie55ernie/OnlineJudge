#include <stdio.h>
#include <assert.h>
#include <omp.h>
#include <inttypes.h>
#include <stdint.h>
// #include "utils.h"
#include <cuda.h>
#include <math.h>
 
#define MAXGPU 8
#define MAXCODESZ 32767
#define MAXN 16777216

static void HandleError( cudaError_t err,
                         const char *file,
                         int line ) {
    if (err != cudaSuccess) {
        printf( "%s in %s at line %d\n", cudaGetErrorString( err ),
                file, line );
        exit( EXIT_FAILURE );
    }
}

#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))
__device__ uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}

__device__ uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

__global__ void dot(uint32_t key1, uint32_t key2, uint32_t C[MAXN], int N){
    int idx = threadIdx.x + blockDim.x * blockIdx.x;
    __shared__ uint32_t local_C[512];    
    int bid = blockDim.x / 2;
    int A, B;
    uint32_t temp = 0;
    while(idx < N){
        A = encrypt(idx, key1);
        B = encrypt(idx, key2);
        temp += A * B;
        idx += gridDim.x * blockDim.x;
    }
    local_C[threadIdx.x] = temp;
    __syncthreads();
    while(bid > 0){
        if(threadIdx.x < bid){
            local_C[threadIdx.x] += local_C[threadIdx.x+bid];
        }
        bid /= 2;
        __syncthreads();
    }
    if(threadIdx.x == 0){
        C[blockIdx.x] = local_C[0];
    }
}


uint32_t A[MAXN], B[MAXN], C[MAXN];
int main(int argc, char *argv[]) {
    uint32_t *device_A, *device_B, *device_C;
    int num_thread = 512;
    int num_block = 1024;
    // printf("declare");
    // HANDLE_ERROR(cudaMalloc((void **)&device_A, sizeof(uint32_t) * MAXN));
    // HANDLE_ERROR(cudaMalloc((void **)&device_B, sizeof(uint32_t) * MAXN));
    HANDLE_ERROR(cudaMalloc((void **)&device_C, sizeof(uint32_t) * ceil(MAXN / num_thread)));
    // printf("error");
    // omp_set_num_threads(4);
    int N;
    uint32_t key1, key2;
    while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {
        // int chunk = N / 4;
        // printf("while %d", N);
// #pragma omp parallel for schedule(static, chunk)
//         for (int i = 0; i < N; i++) {
//             A[i] = encrypt(i, key1);
//             B[i] = encrypt(i, key2);
//         }
 
        // HANDLE_ERROR(cudaMemcpy(device_A, A, sizeof(uint32_t) * MAXN,cudaMemcpyHostToDevice));
        // HANDLE_ERROR(cudaMemcpy(device_B, B, sizeof(uint32_t) * MAXN,cudaMemcpyHostToDevice));
        

        dot <<<min(num_block, int(ceil(N / num_thread))), num_thread>>> (key1, key2, device_C, N);

        HANDLE_ERROR(cudaMemcpy(C, device_C, sizeof(uint32_t) * min(num_block, int(ceil(N / num_thread))), cudaMemcpyDeviceToHost));

        // for (int i = 0; i < N; i++)
        //     C[i] = A[i] * B[i];
 
        uint32_t sum = 0;
#pragma omp parallel for reduction(+ : sum)
        for (int i = 0; i < min(num_block, int(ceil(N / num_thread))); i++)
            sum += C[i];
        printf("%" PRIu32 "\n", sum);
    }

    cudaFree(device_C);

    return 0;
}