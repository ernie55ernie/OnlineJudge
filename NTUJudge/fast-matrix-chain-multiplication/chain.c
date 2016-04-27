#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

uint32_t* rand_gen(uint32_t seed, int R, int C) {
    uint32_t *m = (uint32_t *) malloc(sizeof(uint32_t) * R*C);
    uint32_t x = 2, n = R*C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            x = (x * x + seed + i + j)%n;
            m[i*C + j] = x;
        }
    }
    return m;
}
uint32_t hash(uint32_t x) {
    return (x * 2654435761LU);
}

uint32_t signature(uint32_t *A, int r, int c) {
    uint32_t h = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            h = hash(h + A[i*c + j]);
    }
    return h;
}

uint32_t* multiply(int N, int M, int O, uint32_t* A, uint32_t* B) {
    uint32_t* C = (uint32_t*)malloc(sizeof(uint32_t) * N * O);
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < O; j++) {
            uint32_t sum = 0;
            for (int k = 0; k < M; k++)
                sum += A[i * M + k] * B[k * O + j];
            C[i * O + j] = sum;
        }
    }
    free(A);
    free(B);
    return C;
}

uint32_t* mult(uint32_t* matrix[], int* trace[], int Z[], int i, int j) {
    if (i == j){
        return matrix[i];
    }else{
        int k = trace[i][j];
        uint32_t* Y = mult(matrix, trace, Z, k + 1, j);
        uint32_t* X = mult(matrix, trace, Z, i, k);

        return multiply(Z[i], Z[k + 1], Z[j + 1], X, Y);
    }
}

void matrixchain(int Z[], int* trace[], int N)
{
 
    int i, j, k, L;

    uint64_t table[N][N];

    uint64_t q;

    for (i = 0; i < N; i++)
        for(j = 0; j < N; j++)
        table[i][j] = 0ull;

    for (L = 1; L < N; L++)   
    {
        for (i = 0; i < (N - L); i++)
        {
            j = i + L;
            table[i][j] = UINT64_MAX;
            for (k = i; k < j; k++)
            {
                // q = cost/scalar multiplications
                q = table[i][k] + table[k + 1][j] + (uint64_t)Z[i] * Z[k + 1] * Z[j + 1];
                if (q < table[i][j]){
                    table[i][j] = q, trace[i][j] = k;
                }
            }
        }
    }
    // for(i = 0; i < N; i++){
    //     for(j = 0; j < N; j++){
    //         printf("%10u ", table[i][j]);
    //     }
    //     printf("\n");
    // }
}

void calculate(int Z[], uint32_t* matrix[], int N){
    int i, j;
    int* trace[N];
    for(i = 0; i < N; i++){
        trace[i] = (int*)malloc(sizeof(int) * (N));
        for(j = 0; j < N; j++){
            trace[i][j] = 0;
        }
    }
    matrixchain(Z, trace, N);
    // printf("\n");
    // for(i = 0; i < N; i++){
    //     for(j = 0; j < N; j++){
    //         printf("%10d ", trace[i][j]);
    //     }
    //     printf("\n");
    // }
    matrix[N] = mult(matrix, trace, Z, 0, N - 1);

    for(i = 0; i < N; i++)
        free(trace[i]);
}

int main()
{
    int N, i, S;
    while(scanf("%d", &N) == 1){
        int Z[N + 1];
        uint32_t* matrix[N + 1];
        for(i = 0; i < (N + 1); i++){
            scanf("%d", &Z[i]);
        }
        for(i = 0; i < N; i++){
            scanf("%d", &S);
            matrix[i] = rand_gen(S, Z[i], Z[i + 1]);
        }
        calculate(Z, matrix, N);
        
        printf("%u\n", signature(matrix[N], Z[0], Z[N]));
        free(matrix[N]);
    }
    return 0;
}