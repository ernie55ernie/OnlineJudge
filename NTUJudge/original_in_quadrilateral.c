#include <stdio.h>
#include <limits.h>

int simple_test(int nvert, float *vertx, float *verty, float testx, float testy){
	int min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX, max_y = INT_MIN;
	for(int i = 0; i < nvert; i++){
		// printf("%f %f\n", vertx[i], verty[i]);
		if(vertx[i] < min_x)
			min_x = vertx[i];
		if(vertx[i] > max_x)
			max_x = vertx[i];
		if(verty[i] < min_y)
			min_y = verty[i];
		if(verty[i] > max_y)
			max_y = verty[i];
	}
	if(testx < min_x || testx > max_x || testy < min_y || testy > max_y)
		return 0;
	return 1;
}

// algorithm from http://www.codeproject.com/Tips/84226/Is-a-Point-inside-a-Polygon
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy){
	int i, j, c = 0;
	for (i = 0, j = nvert-1; i < nvert; j = i++) {
		if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 		(testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
			c = !c;
  	}
  	return c;
}


int main(){
	float vertx[4];
	float verty[4];

	scanf("%f %f %f %f %f %f %f %f", &vertx[0], &verty[0], &vertx[1]
		, &verty[1], &vertx[2], &verty[2], &vertx[3], &verty[3]);
	printf("%c", simple_test(4, vertx, verty, 0, 0) ? pnpoly(4, vertx, verty, 0, 0) + '0' : '0');
}