#include <stdio.h>
#include <stdint.h>
#define MAXN 1000000

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}
uint32_t A[MAXN][3], B[MAXN][3], C[MAXN][3];
int main() {
    int x, y, v;
    int N, M, R, nA, nB;
    scanf("%d %d %d", &N, &M, &R);
    scanf("%d %d", &nA, &nB);
    for (int i = 0; i < nA; i++)
        scanf("%d %d %d", &x, &y, &v), A[x][0][0] = v, A[x][0][1] = y;
    for (int i = 0; i < nB; i++)
        scanf("%d %d %d", &x, &y, &v), B[y][0][0] = v, B[y][1][1] = x;
 
    uint32_t hash = 0;
#pragma omp parallel for schedule(guided) reduction(+ : hash)
    for (int i = 0; i < nA; i++) {
        for (int j = 0; j < nB; j++) {
            if(A[i][2] != B[i][1])
                continue;
            uint32_t sum = A[i][0] * B[i][0];
            int row = A[i][1];
            int col = B[i][2];
            if (sum)
                hash += encrypt((row+1)*(col+1), sum);
        }
    }
    printf("%u\n", hash);
    return 0;
}