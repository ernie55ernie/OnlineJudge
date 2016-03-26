#include <stdio.h>

int main(){

	int a[3], max = 0, min = 0, mid = 0, i;

	scanf("%d", &a[0]);
	scanf("%d", &a[1]);
	scanf("%d", &a[2]);

	for(i = 0; i < 3; i++){
		if(a[i] > max){
			min = mid;
			mid = max;
			max = a[i];
		}else if(a[i] > mid){
			min = mid;
			mid = a[i];
		}else{
			min = a[i];
		}
	}

	if((mid + min) > max && max >= 0 && min >= 0 && mid >= 0){
		printf("1");
	}else{
		printf("0");
	}

	return 0;
}