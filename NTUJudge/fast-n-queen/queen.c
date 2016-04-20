#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20
int n;

int print_limit(int limit[MAX_N][MAX_N], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d ", limit[i][j]);
		}
		printf("\n");
	}
}

int set_limit(int limit[MAX_N][MAX_N], int col, int put, int value){
	for(int i = 0; i < n; i++){
		if(i != col){
			limit[i][put] += value;
			limit[col][i] += value;
			if(put + i - col < n && put + i - col >= 0)limit[i][put + i - col] += value;
			if(put - i + col >= 0 && put - i + col < n)limit[i][put - i + col] += value;
		}
	}
}

int queen(int limit[MAX_N][MAX_N], int next){
	if(next >= n)
		return 1;
	int sum = 0;
	for(int test = 0; test < n; test++){
		if(!limit[next][test]){
			set_limit(limit, next, test, 1);
			sum += queen(limit, next + 1);
			set_limit(limit, next, test, -1);
		}
	}
	return sum;
}

int main(){
	int case_num = 0;
	int limit[MAX_N][MAX_N] = {0};
	while(scanf("%d", &n) == 1){
		int numSolution = 0;
		char line[n];
		for(int i = 0; i < n; i++){
			scanf("%s", &line);
			for(int j = 0; j < n; j++){
				limit[i][j] += line[j] == '*' ? 1 : 0;
			}
		}
		int printed = 0;
#pragma omp parallel for private(limit) reduction(+ : numSolution) schedule(dynamic)
		for(int test = 0; test < n * n * n * n; test++){
			set_limit(limit, 0, test / n / n / n, 1);
			if(printed++ == 0)print_limit(limit, n);
			if(!limit[1][test / n / n % n]){
				set_limit(limit, 1, test / n / n % n, 1);
				if(!limit[2][test / n % n]){
					set_limit(limit, 2, test / n % n, 1);
					if(!limit[3][test % n]){
						set_limit(limit, 3, test % n, 1);
						numSolution += queen(limit, 4);
						set_limit(limit, 3, test % n, -1);
					}
					set_limit(limit, 2, test / n % n, -1);
				}
				set_limit(limit, 1, test / n / n % n, -1);
			}
			set_limit(limit, 0, test / n / n / n, -1);
			if(printed++ == 1)print_limit(limit, n);
		}
		printf("Case %d: %d\n", ++case_num, numSolution);
	}
	return 0;
}