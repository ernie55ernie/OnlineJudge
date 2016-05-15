#define N 1024
__kernel void mul(__global int A[N][N], __global int B[N][N], __global int C[N][N], int n){
	int row = get_global_id(0);
	int col = get_global_id(1);
	int sum = 0;
	for(int i = 0; i < n; i++)
		sum += A[row][i] * B[i][col];
	C[row][col] = sum;
}

__kernel void add(__global int A[N][N], __global int B[N][N], __global int C[N][N], int n){
	int row = get_global_id(0);
	int col = get_global_id(1);
	C[row][col] = A[row][col] + B[row][col];
}