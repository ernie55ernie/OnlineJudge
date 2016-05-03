__kernel void vecdot(__global int* A, __global int* B, __global int* C, const unsigned int N)
{
	int idx = get_global_id(0);
	if(idx < N)
		C[idx] = A[idx] * B[idx];
}
