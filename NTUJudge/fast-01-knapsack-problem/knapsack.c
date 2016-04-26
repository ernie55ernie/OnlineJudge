#include <stdio.h>
#include <stdlib.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

// Returns the maximum value that can be put in a knapsack of capacity W
int knapsack(int W, int wt[], int val[], int n)
{
	int i, w, max, flag;
	flag = 0;
   	int** table = (int**)malloc(sizeof(int*) * 2);
   	table[0] = (int*)malloc(sizeof(int) * (W + 1));
   	table[1] = (int*)malloc(sizeof(int) * (W + 1));
 
   	// Build table table[][] in bottom up manner
   	for (i = 0; i <= n; i++)
   	{
#pragma omp parallel for
       	for (w = 0; w <= W; w++)
       	{
           	if (i == 0 || w == 0)
               	table[flag][w] = 0;
           	else if (wt[i-1] <= w)
            	table[flag][w] = max(val[i - 1] + table[!flag][w - wt[i - 1]], table[!flag][w]);
           	else
                table[flag][w] = table[!flag][w];
       	}
       	flag = !flag;
   	}

   	max = table[flag][W];

   	for(i = 0; i < 2; i++){
   		free(table[i]);
   	}
   	free(table);

   	return max;
}
 
int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	int* val = (int*)malloc(sizeof(int) * N);
	int* wt = (int*)malloc(sizeof(int) * N);
	for(int i = 0 ; i < N ; i++){
		scanf("%d %d", &wt[i], &val[i]);
	}
    printf("%d\n", knapsack(M, wt, val, N));
    free(val);
    free(wt);
    return 0;
}