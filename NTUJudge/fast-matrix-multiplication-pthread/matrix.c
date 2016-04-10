#include "matrix.h"
#include <pthread.h>

#define NUM_T 32

int NG;
unsigned long (*AG)[2048];
unsigned long (*CG)[2048];
unsigned long BT[2048][2048];

typedef struct arguments{
    int starti;
    int endi;
}arguments;

void* compute_row(void* args){
    arguments* argument = (arguments*)args;
    int starti = argument->starti;
    int endi = argument->endi;
    printf("%d %d\n", starti, endi);
    unsigned long sum;    // overflow, let it go.
    for(int i = starti; i < endi; i++){
        for (int j = 0; j < NG; j++) {
            sum = 0;
            for (int k = 0; k < NG; k++)
                sum += AG[i][k] * BT[j][k];
                // sum += AG[i][k] * BG[k][i];
            CG[i][j] = sum;
        }
    }
    pthread_exit(NULL);
}
 
void multiply(int N, unsigned long A[][2048], unsigned long B[][2048], unsigned long C[][2048]) {
    NG = N;
    AG = A;
    CG = C;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_t thread_pool[NUM_T];
    arguments args_pool[NUM_T];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            BT[j][i] = B[i][j];
        }
    }
    
    int dis = N * N < NUM_T ? N * N : NUM_T;
    int part = (N * N < NUM_T ? 1 : N * N / NUM_T);
    int part_row = part / N;
    printf("%d %d %d\n", N * N, dis, part);
    for (int i = 0; i < dis; i++) {
        arguments args;
        args.starti = i == 0 ? i * part_row : i * part_row + 1;
        args.endi =  i == dis - 1 ? N : ((i + 1) * part_row + 1);
        args_pool[i] = args;
        pthread_create(&thread_pool[i], &attr, compute_row, (void*) &args_pool[i]);
    }
    for(int i = 0; i < dis; i++){
        pthread_join(thread_pool[i], NULL);
    }
    pthread_attr_destroy(&attr);
}