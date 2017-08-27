// https://judgegirl.csie.org/problem/0/215
// 9 48 5
// 9 48 20
#include <stdio.h>
#include <math.h>

int main(){

	float a[3], b, c, d;

	scanf("%f %f %f", &a[0], &a[1], &a[2]);
	d = a[0] - a[2];
	c = (a[1] - 8 * d - 2 * a[2]) / 2;
	b = a[2] - c;

	if(b >= 0 && c >= 0 && d >= 0 && 
		ceilf(b) == b && ceilf(c) == c && ceilf(d) == d)
		printf("%.0f\n%.0f\n%.0f", b, c, d);
	else
		printf("%.0f", 0);

	return 0;
}