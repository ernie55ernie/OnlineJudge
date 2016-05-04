#define N 1024
__kernel void multiply(__global int matrixA[N][N], __global int matrixB[N][N], __global int matrixC[N][N], const int n) 
{
  int row = get_global_id(0);
  int col = get_global_id(1);
  int sum = 0;
  for (int i = 0; i < n; i++) 
    sum += matrixA[row][i] * matrixB[i][col];
  matrixC[row][col] = sum;
}