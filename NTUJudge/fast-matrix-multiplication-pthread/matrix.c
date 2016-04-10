#include "matrix.h"
#include <pthread.h>

#define NUM_T 32

int NG;
unsigned long (*AG)[2048];
unsigned long (*BG)[2048];
unsigned long (*CG)[2048];

typedef struct arguments{
    int starti;
    int endi;
    int startj;
    int endj;
}arguments;

void* compute_row(void* args){
    arguments* argument = (arguments*)args;
    int starti = argument->starti;
    int endi = argument->endi;
    int startj = argument->startj;
    int endj = argument->endj;
    for (int j = startj; j < NG; j++) {
        unsigned long sum = 0;    // overflow, let it go.
        for (int k = 0; k < NG; k++)
            sum += AG[starti][k] * BG[k][j];
        CG[starti][j] = sum;
    }
    for(int i = starti + 1; i < endi - 1; i++){
        for (int j = 0; j < NG; j++) {
            unsigned long sum = 0;    // overflow, let it go.
            for (int k = 0; k < NG; k++)
                sum += AG[i][k] * BG[k][j];
            CG[i][j] = sum;
        }
    }
    for (int j = 0; j < endj; j++) {
        unsigned long sum = 0;    // overflow, let it go.
        for (int k = 0; k < NG; k++)
            sum += AG[endi - 1][k] * BG[k][j];
        CG[endi - 1][j] = sum;
    }
    pthread_exit(NULL);
}
 
void multiply(int N, unsigned long A[][2048], unsigned long B[][2048], unsigned long C[][2048]) {
    NG = N;
    AG = A;
    BG = B;
    CG = C;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_t thread_pool[NUM_T];
    arguments args_pool[NUM_T];

    int dis = N * N < NUM_T ? N * N : NUM_T;
    int part = (N * N < NUM_T ? 1 : N * N / NUM_T);
    for (int i = 0; i < dis; i++) {
        arguments args;
        args.starti = i * part / N;
        args.endi =  i == dis - 1 ? N : (i + 1) * part / N == args.starti ? args.starti + 1 : (i + 1) * part / N;
        args.startj = i * part % N;
        args.endj = (i + 1) * part % N == 0 ? N : (i + 1) * part % N;
        args_pool[i] = args;
        pthread_create(&thread_pool[i], &attr, compute_row, (void*) &args_pool[i]);
    }
    for(int i = 0; i < dis; i++){
        pthread_join(thread_pool[i], NULL);
    }
    pthread_attr_destroy(&attr);
}