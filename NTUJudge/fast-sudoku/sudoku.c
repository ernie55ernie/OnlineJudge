#include <stdio.h>

#define N 9

int border[N][N];

int main(){
	char line[N];
	for(int i = 0; i < N; i++){
		scanf("%s", line);
		for(int j = 0; j < N; j++){
			border[i][j] = line[j];
		}
	}

	
}