// https://judgegirl.csie.org/problem/0/9
#include <stdio.h>

int main(){
	int i = 0, score = 0;
	scanf("%d", &i);
	if(i <= 0){
		printf("%d", -100);
		return 0;
	}
	if(i % 3 == 0)
		score += 3;
	if(i % 5 == 0)
		score += 5;
	if(i >= 100 && i <= 200){
		score += 50;
	}else{
		score -= 50;
	}
	printf("%d", score);

	return 0;
}