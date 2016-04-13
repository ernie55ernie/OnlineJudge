#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
int n;
int limit[MAX_N][MAX_N];

void print_board(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%c", limit[i][j]);
		}
		printf("\n");
	}
}

int ok(int position[], int next, int test){
	if(limit[next][test] == '*'){
		return 0;
	}
	for(int i = 0; i < next; i++){
		if(position[i] == test || (abs(test - position[i]) == next - i)){
			return 0;
		}
	}
	return 1;
}

int queen(int position[], int next){
	if(next >= n)
		return 1;
	int sum = 0;
	for(int test = 0; test < n; test++){
		if(ok(position, next, test)){
			position[next] = test;
			sum += queen(position, next + 1);
		}
	}
	return sum;
}

int main(){
	int case_num = 0;
	while(scanf("%d", &n) == 1){
		int position[n];
		int numSolution = 0;
		char line[n];
		for(int i = 0; i < n; i++){
			scanf("%s", &line);
			for(int j = 0; j < n; j++){
				limit[i][j] = line[j];
			}
		}
#pragma omp parallel for private(position) reduction(+ : numSolution) schedule(dynamic)
		for(int test = 0; test < n * n * n * n; test++){
			if(ok(position, 0, test / n / n / n)){
				position[0] = test / n / n / n;
				if(ok(position, 1, test / n / n % n)){
					position[1] = test / n / n % n;
					if(ok(position, 2, test / n % n)){
						position[2] = test / n % n;
						if(ok(position, 3, test % n)){
							position[3] = test % n;
							numSolution += queen(position, 4);
						}
					}
				}
			}
		}
		printf("Case %d: %d\n", ++case_num, numSolution);
	}
	return 0;
}