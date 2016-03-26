#include <stdio.h>

int main(){

	int n[1];

	scanf("%d", n);

	if(n[0] % 3 == 0 && n[0] % 5 == 0 && n[0] % 7 != 0){
		printf("0");
	}else{
		printf("1");
	}

	return 0;
}