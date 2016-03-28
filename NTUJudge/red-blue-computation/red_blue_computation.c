#include <stdio.h>

#define MAX_N 1000

int board[2][MAX_N * MAX_N];
int N, num, which;

void sync(){
	int i;
#pragma omp parallel for schedule(static)
	for(i = 0; i < N * N; i++){
		board[!which][i] = board[which][i];
	}
}

int main(){
	int i, j, k, c;
	char line[MAX_N];
	which = 0;

	scanf("%d %d", &N, &num);
	for(i = 0; i < N; i++){
		scanf("%s", &line);
		for(j = 0; j < N; j++){
			board[which][i * N + j] = line[j];
		}
	}
	for(i = 0; i < num; i++){
		sync();
#pragma omp parallel for schedule(static)
		for(j = 0; j < N * N; j++){
			if(board[which][j] == 'R'){
				if(j % N == N - 1){
					if(board[which][j - N + 1] == 'W'){
						board[!which][j - N + 1] = 'R';
						board[!which][j] = 'W';
					}
				}else{
					if(board[which][j + 1] == 'W'){
						board[!which][j + 1] = 'R';
						board[!which][j] = 'W';
					}
				}
			}
		}
		which = !which;
		sync();
#pragma omp parallel for schedule(static)
		for(j = 0; j < N * N; j++){
			if(board[which][j] == 'B'){
				if(j >= N * (N - 1)){
					if(board[which][j - N * (N - 1)] == 'W'){
						board[!which][j - N * (N - 1)] = 'B';
						board[!which][j] = 'W';
					}
				}else{
					if(board[which][j + N] == 'W'){
						board[!which][j + N] = 'B';
						board[!which][j] = 'W';
					}
				}
			}
		}
		which = !which;
	}

	for(i = 0; i < N * N; i++){
		putchar(board[which][i]);
		if((i % N) == (N - 1))printf("\n");
	}
}