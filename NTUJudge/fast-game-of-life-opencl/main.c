#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <stdlib.h>
#include <assert.h>
#include <CL/cl.h>

#define MAXN 2000
#define MAXGPU 8
#define MAXFILE 1024

int plate[2][(MAXN + 2) * (MAXN + 2)];
int n;

void print_plate(int flag){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			printf("%c", plate[flag][i * (n + 2) + j] + '0');
		}
		printf("\n");
	}
}

int main(){
	int M;
	char line[MAXN];
	cl_int status;
	cl_platform_id platform_id;
	cl_uint num_platform_id;
	cl_device_id device_ids[MAXGPU];
	cl_uint num_device_id;
	cl_context context;
	cl_command_queue command_queue;
	cl_program program;
	cl_kernel kernel;
	cl_mem buffer;

	memset(plate[0], 0, sizeof(int) * (MAXN + 2) * (MAXN + 2));
	memset(plate[1], 0, sizeof(int) * (MAXN + 2) * (MAXN + 2));

	status = clGetPlatformIDs(1, &platform_id, &num_platform_id);
	status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, device_ids, &num_device_id);
	context = clCreateContext(NULL, num_device_id, device_ids, NULL, NULL, &status);
	command_queue = clCreateCommandQueue(context, device_ids[0], 0, &status);

	FILE* file_pointer = fopen("game-of-life.cl", "r");
	char file_buffer[MAXFILE];
	const char* buffer_pointer = file_buffer;
	size_t file_length = fread(file_buffer, 1, MAXFILE, file_pointer);
	program = clCreateProgramWithSource(context, 1, &buffer_pointer, &file_length, &status);
	status = clBuildProgram(program, num_device_id, device_ids, NULL, NULL, NULL);
	if (status != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, device_ids[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        char *program_log = (char*)malloc((log_size + 1) * sizeof(char));
        clGetProgramBuildInfo(program, device_ids[0], CL_PROGRAM_BUILD_LOG, log_size + 1, program_log, NULL);
        printf("%s", program_log);
        free(program_log);
    }
	kernel = clCreateKernel(program, "iteration", &status);

	if(scanf("%d %d", &n, &M) == 2){
		for(int i = 1; i <= n; i++){
			scanf("%s", line);
			for(int j = 0; j < n; j++){
				plate[0][i * (n + 2) + j + 1] = line[j] - '0';
			}
		}
		buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 2 * (MAXN + 2) * (MAXN + 2) * sizeof(cl_uint), plate, &status);

		status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&buffer);
		status = clSetKernelArg(kernel, 1, sizeof(int), (void*)&n);
		status = clSetKernelArg(kernel, 2, sizeof(int), (void*)&M);
		size_t global_dim[] = {MAXN, MAXN};
		size_t local_dim[] = {16, 16};
		status = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_dim, local_dim, 0, NULL, NULL);
		clEnqueueReadBuffer(command_queue, buffer, CL_TRUE, 0, 2 * (MAXN + 2) * (MAXN + 2) * sizeof(cl_uint), plate, 0, NULL, NULL);
		
		print_plate(M % 2 != 0);
	}

	clReleaseContext(context);
	clReleaseCommandQueue(command_queue);
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseMemObject(buffer);
	return 0;
}