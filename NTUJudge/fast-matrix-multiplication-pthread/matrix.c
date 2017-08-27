#include "matrix.h"
#include <pthread.h>

// Number of thread
#define NUM_T 1

// Global variable for the size of the square matrix
int NG;

// Global variable for the convinence for multiple process
// to access matrix A, B, and C
unsigned long (*AG)[2048];
unsigned long (*BG)[2048];
unsigned long (*CG)[2048];

// Additional B temporary matrix is the tranpose of the B
// matrix created for the faster row-wise access speed
unsigned long BT[2048][2048];

// arguments type created for pthread arguments
typedef struct arguments{
    int start_row;
    int end_row;
}arguments;

// compute the multiplication of matrix rows specified
// by the arguments defined by starting row and ending
// row
void* compute_row(void* args){
    arguments* argument = (arguments*)args;
    int start_row = argument->start_row;
    int end_row = argument->end_row;
    for(int i = start_row; i < end_row + 1; i++){
        for (int j = 0; j < NG; j++) {
            unsigned long sum = 0;    // overflow, let it go.
            for (int k = 0; k < NG; k++)
                sum += AG[i][k] * BT[j][k];
            CG[i][j] = sum;
        }
    }
    pthread_exit(NULL);
}

// multiple two square matrix, A and B, with size N
// and return the value into C
void multiply(int N, unsigned long A[][2048], 
    unsigned long B[][2048], 
    unsigned long C[][2048]) {
    // assign matrix value and matrix size into local variables
    NG = N;
    AG = A;
    BG = B;
    CG = C;

    // initialize pthread attribute value
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_t thread_pool[NUM_T];
    arguments args_pool[NUM_T];

    // assign B matrix value into tranposed B temporary matrix
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            BT[j][i] = BG[i][j];
        }
    }

    // if the number of matrix row is smaller than the total number of thread
    // then use the number of matrix row as the number of spliting the work
    int n_split = N < NUM_T ? N : NUM_T;
    // calculate the number of work row in each split
    int n_work = N < NUM_T ? 1 : N / NUM_T;

    for (int i = 0; i < n_split; i++) {
        arguments args;
        // calculate the starting and ending index of the row
        args.start_row = i * n_work;
        args.end_row = args.start_row + n_work;
        args_pool[i] = args;
        // create a thread, store in the thread pool, and assign its work
        // by argments pool
        pthread_create(&thread_pool[i], &attr, compute_row, (void*) &args_pool[i]);
    }

    for(int i = 0; i < n_split; i++){
        // wait for all threads to finish their jobs
        pthread_join(thread_pool[i], NULL);
    }
    pthread_attr_destroy(&attr);
}