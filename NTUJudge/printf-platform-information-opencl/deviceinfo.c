#include <stdio.h>
#include <assert.h>
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif

#define MAXB	256
#define MAXPLATFORM	5
#define MAXDEVICE	20
#define MAXGPU  10
#define MAXCPU 	10
#define MAXFILE 1024

#define MAXN 1024

int plate[2][MAXN][MAXN];

int main(int argc, char *argv[]){
	cl_platform_id platform_id[MAXPLATFORM];
	cl_uint platform_id_got;
	char buffer[MAXB];
	size_t length;
	cl_device_id devices[MAXDEVICE];
	cl_device_id cpus[MAXCPU];
	cl_device_id gpus[MAXGPU];
	cl_uint device_id_got;
	cl_uint cpu_id_got;
	cl_uint gpu_id_got;
	cl_int status;
	cl_context context;
	cl_command_queue command_queue;
	cl_program program;
	cl_kernel kernel;
	cl_mem mem;
	
	status = clGetPlatformIDs(MAXPLATFORM, platform_id, &platform_id_got);
	status = clGetDeviceIDs(platform_id[0], CL_DEVICE_TYPE_ALL, MAXDEVICE, devices, &device_id_got);
	printf("%u Devices\n", device_id_got);
	clGetDeviceIDs(platform_id[0], CL_DEVICE_TYPE_CPU, MAXCPU, cpus, &cpu_id_got);
	printf("%u CPU Devices\n", cpu_id_got);
	clGetDeviceIDs(platform_id[0], CL_DEVICE_TYPE_GPU, MAXGPU, gpus, &gpu_id_got);
	printf("%u GPU Devices\n", gpu_id_got);
	
	clGetDeviceInfo(gpus[0], CL_DEVICE_NAME, MAXB, buffer, &length);
	printf("Device name %s\n", buffer);
	cl_ulong number;
	clGetDeviceInfo(gpus[0], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &number, NULL);
	printf("Global memory size %lld\n", (long long)number);
	clGetDeviceInfo(gpus[0], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &number, NULL);
	printf("Local memory size %lld\n", (long long)number);
	clGetDeviceInfo(gpus[0], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_ulong), &number, NULL);
	printf("# of compute units %lld\n", (long long)number);
	clGetDeviceInfo(gpus[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_ulong), &number, NULL);
	printf("max # of work items in a work group %lld\n", (long long)number);

	context = clCreateContext(NULL, gpu_id_got, gpus, NULL, NULL, &status);
	command_queue = clCreateCommandQueue(context, gpus[0], 0, &status);

	FILE* file_pointer = fopen("kernel.cl", "r");
	char file_buffer[MAXFILE];
	const char* buffer_pointer = file_buffer;
	size_t file_length = fread(file_buffer, 1, MAXFILE, file_pointer);
	program = clCreateProgramWithSource(context, 1, &buffer_pointer, &file_length, &status);
	status = clBuildProgram(program, gpu_id_got, gpus, NULL, NULL, NULL);
	if (status != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, gpus[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        char *program_log = (char*)malloc((log_size + 1) * sizeof(char));
        clGetProgramBuildInfo(program, gpus[0], CL_PROGRAM_BUILD_LOG, log_size + 1, program_log, NULL);
        printf("%s", program_log);
        free(program_log);
    }
	kernel = clCreateKernel(program, "globalindex", &status);
	
	mem = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, 2 * MAXN * MAXN * sizeof(cl_uint), plate, &status);

	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&mem);
	size_t global_dim[] = {MAXN, MAXN};
	size_t local_dim[] = {64, 64};
	status = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_dim, local_dim, 0, NULL, NULL);
	if(status != CL_SUCCESS){
		printf("clEnqueueNDRangeKernel error code: %d\n", status);
		if(status == -54){
			local_dim[0] = 1;
			local_dim[1] = 1;
		}
	}
	status = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, global_dim, local_dim, 0, NULL, NULL);
	
	clEnqueueReadBuffer(command_queue, mem, CL_TRUE, 0, 2 * MAXN * MAXN * sizeof(cl_uint), plate, 0, NULL, NULL);

	clReleaseContext(context);
	clReleaseCommandQueue(command_queue);
	clReleaseMemObject(mem);
	clReleaseKernel(kernel);
	clReleaseProgram(program);

	return 0;
}	