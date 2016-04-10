#include <stdio.h>

#define N 9

int placeNumber(int n, int border[N][N]){
	if(n == N * N)
		return 1;
	int row = n / N;
	int col = n % N;
	if(border[row][col] != 0)
		return placeNumber(n + 1, border);
	int block_row = row / 3;
	int block_col = col / 3;
	int numSolution = 0;
	for(int try = 1; try < N + 1; try++){
		int conflict = 0;
		for(int i = 0; i < N && !conflict; i++){
			if(((col != i) && (border[row][i] == try)) || ((row != i) && (border[i][col] == try)))
				conflict = 1;
		}
		if(!conflict){
			for(int i = 0; i < 3 && !conflict; i++)
				for(int j = 0; j < 3 && !conflict; j++)
					if(border[3 * block_row + i][3 * block_col + j] == try
						&& (3 * block_row + i != row || 3 * block_col + j != col))
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
	int firstZero = -1;
	int border[N][N];
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &border[i][j]);
			if(border[i][j] == 0 && firstZero == -1)
				firstZero = i * N + j;
		}
	}
	int numSolution = 0;
	int row = firstZero / N;
	int col = firstZero % N;
	int block_row = row / 3;
	int block_col = col / 3;
#pragma omp parallel for reduction(+ : numSolution) firstprivate(border) schedule(dynamic)
	for(int try = 1; try < N + 1; try++){
		int conflict = 0;
		border[row][col] = try;
		for(int i = 0; i < N && !conflict; i++){
			if(((col != i) && (border[row][i] == try)) || ((row != i) && (border[i][col] == try)))
				conflict = 1;
		}
		if(!conflict){
			for(int i = 0; i < 3 && !conflict; i++)
				for(int j = 0; j < 3 && !conflict; j++)
					if(border[3 * block_row + i][3 * block_col + j] == try
						&& (3 * block_row + i != row || 3 * block_col + j != col))
						conflict = 1;
		}
		if(!conflict){
			numSolution += placeNumber(firstZero + 1, border);	
		}
	}
	printf("%d\n", numSolution);
	return 0;
}