#define N 2000
#define alive(p, ind, n, flag) plate[flag][ind - n - 3] \
		+ plate[flag][ind - n - 2] \
		+ plate[flag][ind - n - 1] \
		+ plate[flag][ind - 1] \
		+ plate[flag][ind + 1] \
		+ plate[flag][ind + n + 1] \
		+ plate[flag][ind + n + 2] \
		+ plate[flag][ind + n + 3]

__kernel void iteration(__global int plate[2][(N + 2) * (N + 2)], int n, int flag){
	int row = get_global_id(0) + 1;
	int col = get_global_id(1) + 1;
	if(row > n || col > n)
		return;
	int ind = row * (n + 2) + col;
	int live = alive(plate, ind, n, flag);
	plate[!flag][ind] = plate[flag][ind] ? (live == 2 || live == 3) 
		: (live == 3);
}