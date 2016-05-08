#define N 2000

__kernel void iteration(__global int plate[2][(N + 2) * (N + 2)], int n, int m){
	int row = get_global_id(0) + 1;
	int col = get_global_id(1) + 1;
	int ind = row * (n + 2) + col;
	int flag = 0;
	for(int i = 0; i < m; i++){
		int live = plate[flag][ind - n - 3] 
			+ plate[flag][ind - n - 2] 
			+ plate[flag][ind - n - 1] 
			+ plate[flag][ind - 1] 
			+ plate[flag][ind + 1] 
			+ plate[flag][ind + n + 1] 
			+ plate[flag][ind + n + 2] 
			+ plate[flag][ind + n + 3];
		plate[!flag][ind] = plate[flag][ind] ? (live == 2 || live == 3 ? 1 : 0) 
			: (live == 3);
		flag = !flag;
		barrier(CLK_GLOBAL_MEM_FENCE);
	}
}