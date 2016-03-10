#include <stdio.h>

int main(){

	int a[5], s, v;

	scanf("%d", &a[0]);
	scanf("%d", &a[1]);
	scanf("%d", &a[2]);
	scanf("%d", &a[3]);
	scanf("%d", &a[4]);

	s = 2 * (a[0] * a[1] + a[1] * a[2] + a[0] * a[2]) + (a[0] + a[1] + a[2] - 6 * a[4]) * a[3] * 8;
	v = a[0] * a[1] * a[2] - 2 * a[3] * ((a[0] - 2 * a[4]) * (a[1] - 2 * a[4]) + (a[0] - 2 * a[4]) * (a[2] - 2 * a[4]) + (a[1] - 2 * a[4]) * (a[2] - 2 * a[4]));

	printf("%d\n", s);
	printf("%d", v);

	return 0;
}