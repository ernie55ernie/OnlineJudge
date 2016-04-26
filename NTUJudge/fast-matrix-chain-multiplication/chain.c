#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>

// generate matrix, row-major
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
// output
uint32_t signature(uint32_t *A, int r, int c) {
    uint32_t h = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            h = hash(h + A[i*c + j]);
    }
    return h;
}

void multiply(int N, int M, int O, uint32_t A[], uint32_t B[], uint32_t C[]) {
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < O; j++) {
            uint32_t sum = 0;    // overflow, let it go.
            for (int k = 0; k < M; k++)
                sum += A[i * M + k] * B[k * M + j];
            C[i * M + j] = sum;
        }
    }
}

int matrixchain(int Z[], int trace[], int n)
{
    int m[n][n];
 
    int i, j, k, L, q, l;
 
    /*cost is zero when multiplying one matrix.*/
    for (i = 1; i < n; i++)
        m[i][i] = 0;
 
    /*L is chain length. */
    for (L = 2; L < n; L++)   
    {
        for (i = 1; i <= (n - L + 1); i++)
        {
            j = i + L - 1;
            m[i][j] = INT_MAX;
            for (k = i; k<= j - 1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k + 1][j] + Z[i - 1] * Z[k] * Z[j];
                if (q < m[i][j]){
                    m[i][j] = q;
                }
            }
        }
    }
    return m[1][n - 1];
}

void calculate(int Z[], uint32_t* matrix[], int N){
    int i;
    int trace[N];
    int min = matrixchain(Z, trace, N);
    // matrix[N] = (uint32_t *) malloc(sizeof(uint32_t) * Z[0] * Z[N]);
    printf("%d\n", min);
    for(i = 0; i < N; i++){
        // printf("%d ", trace[i]);
    }
}

int main()
{
    int N, i;
    while(scanf("%d", &N) == 1){
        int Z[N + 1];
        int S;
        uint32_t* matrix[N + 1];
        for(i = 0; i < (N + 1); i++){
            scanf("%d", &Z[i]);
        }
        for(i = 0; i < N; i++){
            scanf("%d", &S);
            matrix[i] = rand_gen(S, Z[i], Z[i + 1]);
        }
        calculate(Z, matrix, N);
        printf("%d\n", signature(matrix[N], Z[0], Z[N]));
    }
    return 0;
}