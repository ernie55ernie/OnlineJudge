#include <stdio.h>

int ok(int plate[], int n, int index, int adj){
	if(adj < 0 || adj >= n * n)
		return 0;
	if(index % n == 0 && index == (adj + 1))
		return 0;
	if(index % n == (n - 1) && index == (adj - 1))
		return 0;
	return 1;
}

int live(int plate[], int n, int index){
	int count = 0;
	for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			if(i == 0 && j == 0)
				continue;
			int adj = index + j + i * n;
			if(ok(plate, n, index, adj) &&
				plate[adj])
				count++;
		}
	}
	return count;
}

void place_all(int plate[], int new[], int n){
#pragma omp parallel for
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			plate[i * n + j] = new[i * n + j];
		}
	}
}

void iteration(int plate[], int n){
	int new[n * n];
#pragma omp parallel for
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int index = i * n + j;
			int num = live(plate, n, index);
			if(plate[index]){
				new[index] =  (num == 2 || num == 3) ?
					1 : 0;
			}else{
				new[index] = (num == 3);
			}
		}
	}
	place_all(plate, new, n);
}

void print_plate(int plate[], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d", plate[i * n + j]);
		}
		printf("\n");
	}
}

int main(){
	int N, M;
	scanf("%d %d\n", &N, &M);
	int plate[N * N];
	for(int i = 0; i < N; i++){
		char line[N];
		scanf("%s", &line);
		for(int j = 0; j < N; j++){
			plate[i * N + j] = line[j] - '0';
		}
		scanf("\n");
	}
	for(int i = 0; i < M; i++){
		iteration(plate, N);
	}
	print_plate(plate, N);
	return 0;
}