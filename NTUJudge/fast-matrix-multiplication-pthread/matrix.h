#include <pthread.h>
#include <assert.h>
#include <stdio.h>

#define NUM_T 8

int NG;
unsigned long (*AG)[2048];
unsigned long (*BG)[2048];
unsigned long (*CG)[2048];

typedef struct arguments{
    int starti;
    int endi;
}arguments;

void multiply(int N, unsigned long A[][2048], unsigned long B[][2048], unsigned long C[][2048]);