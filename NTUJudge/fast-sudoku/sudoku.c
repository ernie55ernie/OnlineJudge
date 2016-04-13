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
	int thirdZero = -1;
	int fourthZero = -1;
	int fifthZero = -1;
	int sixthZero = -1;
	int seventhZero = -1;
	int border[N][N];
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &border[i][j]);
			if(border[i][j] == 0 && firstZero == -1){
				firstZero = i * N + j;
			}else if(firstZero != -1 && border[i][j] == 0 && secondZero == -1){
				secondZero = i * N + j;
			}else if(secondZero != -1 && border[i][j] == 0 && thirdZero == -1){
				thirdZero = i * N + j;
			}else if(thirdZero != -1 && border[i][j] == 0 && fourthZero == -1){
				fourthZero = i * N + j;
			}else if(fourthZero != -1 && border[i][j] == 0 && fifthZero == -1){
				fifthZero = i * N + j;
			}else if(fifthZero != -1 && border[i][j] == 0 && sixthZero == -1){
				sixthZero = i * N + j;
			}else if(sixthZero != -1 && border[i][j] == 0 && seventhZero == -1){
				seventhZero = i * N + j;
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
	int rowt = thirdZero / N;
	int colt = thirdZero % N;
	int block_rowt = rowt / 3;
	int block_colt = colt / 3;
	int rowf = fourthZero / N;
	int colf = fourthZero % N;
	int block_rowf = rowf / 3;
	int block_colf = colf / 3;
	int rowi = fifthZero / N;
	int coli = fifthZero % N;
	int block_rowi = rowi / 3;
	int block_coli = coli / 3;
	int rowx = sixthZero / N;
	int colx = sixthZero % N;
	int block_rowx = rowx / 3;
	int block_colx = colx / 3;
	int rowe = seventhZero / N;
	int cole = seventhZero % N;
	int block_rowe = rowe / 3;
	int block_cole = cole / 3;
#pragma omp parallel for reduction(+ : numSolution) firstprivate(border) schedule(dynamic)
	for(int try = 0; try < 4782969; try++){
		border[row][col] = try / 531441 + 1;
		border[rows][cols] = try / 59049 % 9 + 1;
		border[rowt][colt] = try / 6561 % 9 + 1;
		border[rowf][colf] = try / 729 % 9 + 1;
		border[rowi][coli] = try / 81 % 9 + 1;
		border[rowx][colx] = try / 9 % 9 + 1;
		border[rowe][cole] = try % 9 + 1;
		if(!check_conflict(border, row, col, block_row, block_col, try / 531441 + 1) &&
			!check_conflict(border, rows, cols, block_rows, block_cols, try / 59049 % 9 + 1) &&
			!check_conflict(border, rowt, colt, block_rowt, block_colt, try / 6561 % 9 + 1) &&
			!check_conflict(border, rowf, colf, block_rowf, block_colf, try / 729 % 9 + 1) &&
			!check_conflict(border, rowi, coli, block_rowi, block_coli, try / 81 % 9 + 1) &&
			!check_conflict(border, rowx, colx, block_rowx, block_colx, try / 9 % 9 + 1) &&
			!check_conflict(border, rowe, cole, block_rowe, block_cole, try % 9 + 1)){
			numSolution += place_number(thirdZero + 1, border);
		}
	}
	printf("%d\n", numSolution);
	return 0;
}