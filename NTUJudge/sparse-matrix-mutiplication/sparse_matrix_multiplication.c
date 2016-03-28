#include <stdio.h>
#include <stdint.h>
#define MAXN 1024

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}
uint32_t A[MAXN][MAXN], B[MAXN][MAXN];
int main() {
    int x, y, v;
    int N, M, R, nA, nB;
    scanf("%d %d %d", &N, &M, &R);
    scanf("%d %d", &nA, &nB);
    for (int i = 0; i < nA; i++)
        scanf("%d %d %d", &x, &y, &v), A[x][y] = v;
    for (int i = 0; i < nB; i++)
        scanf("%d %d %d", &x, &y, &v), B[x][y] = v;
 
    uint32_t hash = 0;
#pragma omp parallel for schedule(static) reduction(+ : hash)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < R; j++) {
            uint32_t sum = 0;
            for (int k = 0; k < M; k++)
                sum += A[i][k] * B[k][j];
            if (sum)
                hash += encrypt((i+1)*(j+1), sum);
        }
    }
    printf("%u\n", hash);
    return 0;
}