#include <stdio.h>

#define N 9

void makeConflict(int conflict[N][N][N + 1], int border[N][N]){
	for(int index = 0; index < N * N; index++){
		int row = index / N;
		int col = index % N;
		int block_row = row / 3;
		int block_col = col / 3;
		for(int i = 0; i < N; i++){
			conflict[row][i][border[row][col]] = 1;
			conflict[i][col][border[row][col]] = 1;
		}
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				conflict[3 * block_row + i][3 * block_col + j][border[row][col]] = 1;
	}
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
		border[row][col] = try;
		makeConflict(conflict, border);
		numSolution += placeNumber(n + 1, border, conflict);
		border[row][col] = 0;
		makeConflict(conflict, border);
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
		border[row][col] = try;
		makeConflict(conflict, border);
		numSolution += placeNumber(firstZero + 1, border, conflict);
		border[row][col] = 0;
		makeConflict(conflict, border);
	}
	printf("%d\n", numSolution);
	return 0;
}