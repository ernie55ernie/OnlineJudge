#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils.h"
#include <omp.h>
 
#define MAXN 10000005
#define MAX_THREAD 4
uint32_t prefix_sum[MAXN];
int main() {
#ifdef _OPENMP
    omp_set_num_threads(MAX_THREAD);
#endif
    int n;
    uint32_t key;
    while (scanf("%d %" PRIu32, &n, &key) == 2) {
#pragma omp parallel for schedule(dynamic)
        for (int i = 1; i <= n; i++) {
            uint32_t sum = 0;
            int lower = i - 1;
            for(; lower >= 0; lower--){
                if(!prefix_sum[lower]){
                    lower--;
                }
            }
            if(lower >= 0)sum += prefix_sum[lower];
            else lower++;
            for(int j = lower + 1; j <= i; j++){
                sum += encrypt(j, key);
            }
            prefix_sum[i] = sum;
        }
        output(prefix_sum, n);
    }
    return 0;
}
