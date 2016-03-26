#include <stdio.h>

int main(){

	int a[3], b, c, d;

	scanf("%d %d %d", &a[0], &a[1], &a[2]);
	d = a[0] - a[2];
	c = (a[1] - 8 * d - 2 * a[2]) / 2;
	b = a[2] - c;

	printf("%d\n%d\n%d", b, c, d);

	return 0;
}