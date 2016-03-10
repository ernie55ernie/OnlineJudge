#include <stdio.h>

int main(){

	int a[3], s, v;

	scanf("%d", &a[0]);
	scanf("%d", &a[1]);
	scanf("%d", &a[2]);

	s = (a[0] * a[1] + a[1] * a[2] + a[0] * a[2]) * 2;
	v = a[0] * a[1] * a[2];

	printf("%d\n", s);
	printf("%d", v);

	return 0;
}