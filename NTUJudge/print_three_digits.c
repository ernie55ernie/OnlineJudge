#include <stdio.h>

int main(){

	int a[1], b, c, d;

	scanf("%d", a);

	b = a[0] % 10;

	c = a[0] / 10 % 10;

	d = a[0] / 100 % 10;

	printf("%d\n%d\n%d", d, c, b);

	return 0;
}