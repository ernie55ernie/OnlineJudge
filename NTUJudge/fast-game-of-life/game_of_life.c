#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 2000

int plate[2][(MAX_N + 2) * (MAX_N + 2)];
int which = 0;
int n;

int live(int index){
	return (plate[which][index - n - 3] 
		+ plate[which][index - n - 2]
		+ plate[which][index - n - 1]
		+ plate[which][index - 1]
		+ plate[which][index + 1]
		+ plate[which][index + n + 1]
		+ plate[which][index + n + 2]
		+ plate[which][index + n + 3]);
}

void iteration(){
#pragma omp parallel for schedule(static)
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			int index = i * (n + 2) + j;
			int num = live(index);
			if(plate[which][index]){
				plate[!which][index] =  (num == 2 || num == 3) ?
					1 : 0;
			}else{
				plate[!which][index] = (num == 3);
			}
		}
	}
	which = !which;
}

void print_plate(){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			printf("%d", plate[which][i * (n + 2) + j]);
		}
		printf("\n");
	}
	printf("\0");
}

int main(){
	int M;
	char line[MAX_N];
	memset(plate[0], 0, sizeof(int) * (n + 2) * (n + 2));
	memset(plate[1], 0, sizeof(int) * (n + 2) * (n + 2));
	if(scanf("%d %d", &n, &M) == 2){
		for(int i = 1; i <= n; i++){
			scanf("%s", &line);
			for(int j = 0; j < n; j++){
				plate[0][i * (n + 2) + j + 1] = line[j] - '0';
			}
		}
		for(int i = 0; i < M; i++){
			iteration();
		}
		print_plate();
	}
	return 0;
}