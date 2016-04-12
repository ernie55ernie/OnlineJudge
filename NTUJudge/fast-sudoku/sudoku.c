#include <stdio.h>

#define N 9

int check_conflict(int border[N][N], int row, int col, int block_row, int block_col, int try){
	for(int i = 0; i < N; i++){
		if(((col != i) && (border[row][i] == try)) || ((row != i) && (border[i][col] == try)))
			return 1;
	}
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(border[3 * block_row + i][3 * block_col + j] == try
					&& (3 * block_row + i != row || 3 * block_col + j != col))
				return 1;
	return 0;
}

int place_number(int n, int border[N][N]){
	if(n == N * N)
		return 1;
	int row = n / N;
	int col = n % N;
	if(border[row][col] != 0)
		return place_number(n + 1, border);
	int block_row = row / 3;
	int block_col = col / 3;
	int numSolution = 0;
	for(int try = 1; try < N + 1; try++){
		if(!check_conflict(border, row, col, block_row, block_col, try)){
			border[row][col] = try;
			numSolution += place_number(n + 1, border);
		}
	}
	border[row][col] = 0;
	return numSolution;
}

int main(){
	int firstZero = -1;
	int secondZero = -1;
	int border[N][N];
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &border[i][j]);
			if(border[i][j] == 0 && firstZero == -1){
				firstZero = i * N + j;
			}else if(firstZero != -1 && border[i][j] == 0 && secondZero == -1){
				secondZero = i * N + j;
			}
		}
	}
	int numSolution = 0;
	int row = firstZero / N;
	int col = firstZero % N;
	int block_row = row / 3;
	int block_col = col / 3;
	int rows = secondZero / N;
	int cols = secondZero % N;
	int block_rows = rows / 3;
	int block_cols = cols / 3;
#pragma omp parallel for reduction(+ : numSolution) firstprivate(border) schedule(static)
	for(int try = 0; try < 81; try++){
		border[row][col] = try / 9 + 1;
		border[rows][cols] = try % 9 + 1;
		if(!check_conflict(border, row, col, block_row, block_col, try / 9 + 1) &&
			!check_conflict(border, rows, cols, block_rows, block_cols, try % 9 + 1)){
			numSolution += place_number(secondZero + 1, border);
		}
	}
	printf("%d\n", numSolution);
	return 0;
}