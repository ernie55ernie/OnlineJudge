#include <stdio.h>
#include <omp.h>

#define N 9

int border[N][N];
int firstZero = -1;

int placeNumber(int n, int border[N][N]){
	if(n == N * N)
		return 1;
	int row = n / N;
	int col = n % N;
	int block_row = row / 3;
	int block_col = col / 3;
	if(border[row][col] != 0)
		return placeNumber(n + 1, border);
	int numSolution = 0;
	for(int try = 1; try <= N; try++){
		int conflict = 0;
		for(int i = 0; i < N && !conflict; i++){
			if(((col != i) && (border[row][i] == try)) || ((row != i) && (border[i][col] == try)))
				conflict = 1;
		}
		if(!conflict){
			for(int i = 0; i < 3 && !conflict; i++)
				for(int j = 0; j < 3 && !conflict; j++)
					if(border[3 * block_row + i][3 * block_col + j] == try)
						conflict = 1;
			if(!conflict){
				border[row][col] = try;
				numSolution += placeNumber(n + 1, border);
			}
		}
	}
	border[row][col] = 0;
	return numSolution;
}

int main(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &border[i][j]);
			if(border[i][j] == 0 && firstZero == -1)
				firstZero = i * N + j;
		}
	}
#ifdef _OPEN_MP
	omp_set_num_threads(9);
#endif
	int numSolution = 0;
#pragma omp parallel for reduction(+ : numSolution) firstprivate(border)
	for(int i = 0; i < N; i++){
		border[firstZero / N][firstZero % N] = i;
		numSolution += placeNumber(firstZero, border);
	}
	printf("%d\n", numSolution);
	return 0;
}