#include <stdio.h>

#define N 9

void makeConflict(int conflict[N][N][N + 1], int row, int col, int num, int value){
	int block_row = row / 3;
	int block_col = col / 3;
	for(int i = 0; i < N; i++){
		conflict[row][i][num] = value;
		conflict[i][col][num] = value;
	}
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			conflict[3 * block_row + i][3 * block_col + j][num] = value;
}

int placeNumber(int n, int border[N][N], int conflict[N][N][N + 1]){
	if(n == N * N)
		return 1;
	int row = n / N;
	int col = n % N;
	if(border[row][col] != 0)
		return placeNumber(n + 1, border, conflict);
	int numSolution = 0;
	for(int try = 1; try < N + 1; try++){
		if(conflict[row][col][try]){
			continue;
		}
		makeConflict(conflict, row, col, try, 1);
		border[row][col] = try;
		numSolution += placeNumber(n + 1, border, conflict);
		makeConflict(conflict, row, col, try, 0);
	}
	border[row][col] = 0;
	return numSolution;
}

int main(){
	int firstZero = -1;
	int border[N][N];
	int conflict[N][N][N + 1] = {0};
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &border[i][j]);
			if(border[i][j] == 0 && firstZero == -1)
				firstZero = i * N + j;
			if(border[i][j]){
				makeConflict(conflict, i, j, border[i][j], 1);
			}
		}
	}
	int numSolution = 0;
	int row = firstZero / N;
	int col = firstZero % N;
	int block_row = row / 3;
	int block_col = col / 3;
#pragma omp parallel for reduction(+ : numSolution) firstprivate(border, conflict) schedule(dynamic)
	for(int try = 1; try < N + 1; try++){
		if(conflict[row][col][try]){
			continue;
		}
		makeConflict(conflict, row, col, try, 1);
		border[row][col] = try;
		numSolution += placeNumber(firstZero + 1, border, conflict);
		makeConflict(conflict, row, col, try, 0);
	}
	printf("%d\n", numSolution);
	return 0;
}