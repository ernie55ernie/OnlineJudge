#include "matrix.h"

void* compute_row(void* args){
    arguments* argument = (arguments*)args;
    int starti = argument->starti;
    int endi = argument->endi;
    for(int i = starti; i < endi; i++){
        for (int j = 0; j < NG; j++) {
            unsigned long sum = 0;    // overflow, let it go.
            for (int k = 0; k < NG; k++)
                sum += AG[i][k] * BG[k][j];
            CG[i][j] = sum;
        }
    }
    pthread_exit(NULL);
}
 
void multiply(int N, unsigned long A[][2048], unsigned long B[][2048], unsigned long C[][2048]) {
    printf("before assign");
    NG = N;
    AG = A;
    BG = B;
    CG = C;

    printf("after assign");
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_t thread_pool[NUM_T];
    arguments args_pool[NUM_T];

    int dis = N / NUM_T < 1 ? N : NUM_T;
    int part = (N / NUM_T < 1 ? 1 : N / NUM_T);
    int left = N - part * NUM_T;

    printf("after dis");
    for (int i = 0; i < dis; i++) {
        arguments args;
        args.starti = i * part;
        args.endi = (i + 1) * part + (i <= left ? 1 : 0);
    	int error = pthread_create(&thread_pool[i], &attr, compute_row, (void*) &args_pool[i]);
    	assert(error == 0);
    }
    printf("after create");
    for(int i = 0; i < dis; i++){
    	pthread_join(thread_pool[i], NULL);
    }
    printf("after join");
    pthread_attr_destroy(&attr);
}