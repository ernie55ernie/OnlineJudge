#define N 1024

__kernel void globalindex(__global int plate[2][N][N]){
	int row = get_global_id(0);
	int col = get_global_id(1);

	plate[0][row][col] = row;
	plate[1][row][col] = col;
}