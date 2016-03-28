#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define MAX_L 250000

int ah, aw, bh, bw;
int img[2][MAX_L];

int main(){

	int min_x, min_y, min_d, i, j, k, l, d;

	while(scanf("%d %d %d %d", &ah, &aw, &bh, &bw) == 4){
		min_d = INT_MAX;
		for(i = 0; i < ah; i++){
			for(j = 0; j < aw; j++){
				scanf("%d", &img[0][i * aw + j]);
			}
		}
		for(i = 0; i < bh; i++){
			for(j = 0; j < bw; j++){
				scanf("%d", &img[1][i * bw + j]);
			}
		}
		for(i = 0; i < (ah - bh + 1); i++){
			for(j = 0; j < (aw - bw + 1); j++){
				d = 0;
#pragma omp parallel for schedule(static) reduction(+ : d)
				for(k = 0; k < bh;k++){
					for(l = 0; l < bw;l++){
						int dif = img[0][(k + i) * aw + l + j] - img[1][k * bw + l];
						d += dif * dif;
					}
				}
				if(d < min_d){
					min_d = d;
					min_x = i + 1;
					min_y = j + 1;
				}
			}
		}
		printf("%d %d\n", min_x, min_y);
	}
	return 0;
}