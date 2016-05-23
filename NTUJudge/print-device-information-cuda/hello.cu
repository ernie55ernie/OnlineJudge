#include <stdio.h>

int main(){
	int nDevices;

	cudaGetDeviceCount(&nDevices);

	printf("%d devices found supporting CUDA\n", nDevices);
	for(int i = 0; i < nDevices; i++){
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		printf("----------------------------------\n");
		printf("Device %s\n", prop.name);
		printf("----------------------------------\n");
		printf(" Device memory:     %zu\n", prop.totalGlobalMem);
		printf(" Memory per-block:     %zu\n", prop.sharedMemPerBlock);
		printf(" Register per-block:     %d\n", prop.regsPerBlock);
		printf(" Warp size:         %d\n", prop.warpSize);
		printf(" Memory pitch:         %zu\n", prop.memPitch);
		printf(" Constant Memory:     %zu\n", prop.totalConstMem);
		printf(" Max thread per-block:     %d\n", prop.maxThreadsPerBlock);
		printf(" Max thread dim:     %d / %d / %d\n", prop.maxThreadsDim[0],
			prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
		printf(" Max grid size:     %d / %d / %d\n", prop.maxGridSize[0],
			prop.maxGridSize[1], prop.maxGridSize[2]);
		printf(" Ver:             %d.%d\n", prop.major, prop.minor);
		printf(" Clock:         %d\n", prop.clockRate);
		printf(" Texture Alignment:     %zu\n", prop.textureAlignment);
	}
}