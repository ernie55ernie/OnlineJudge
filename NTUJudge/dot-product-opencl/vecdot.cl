__kernel void dot(__global int* A, __global int* B, __global int* C)
{
	int idx = get_global_id(0);
	c[idx] = A[idx] * B[idx];
}