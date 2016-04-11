#include <stdio.h>
#include <stdlib.h>

#define N 100000000

int not_prime[N] = {0};
 
int main(){
#pragma omp parallel
    for(unsigned long i = 2; i < N; i++){
        if(!not_prime[i]){
#pragma omp for nowait
            for(unsigned long j = 2 * i; j < N; j += i){
                not_prime[j] = 1;
            }
        }
    }
    unsigned long lower, higher;
    while(scanf("%lu %lu", &lower, &higher) == 2){
        unsigned long count;
#pragma omp parallel for reduction(+ : count)
        for(unsigned long i = lower; i <= higher; i++){
            if(!not_prime[i]){
                count++;
            }
        }
        printf("%lu\n", count);
    }
}