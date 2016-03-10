#include <stdio.h>

int main(){

	int a[3];
	int d = 0;

	scanf("%d", &a[0]);
	d += a[0];
	scanf("%d", &a[1]);
	d += a[1];
	scanf("%d", &a[2]);

	d += a[2];

	printf("%d", d);

	return 0;
}