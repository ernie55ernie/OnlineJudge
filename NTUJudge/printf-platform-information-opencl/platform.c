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

int main(int argc, char *argv[]){
	cl_platform_id platform_id[MAXPLATFORM];
	cl_uint platform_id_got;
	cl_int status = clGetPlatformIDs(MAXPLATFORM, platform_id, &platform_id_got);
	assert(status == CL_SUCCESS && platform_id_got == 1);
	printf("%d platform found\n", platform_id_got);
	for(int i = 0; i < platform_id_got; i++){
		char buffer[MAXB];
		size_t length;
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_NAME, MAXB, buffer, &length);
		printf("Platform Name %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_VENDOR, MAXB, buffer, &length);
		printf("Platform Vendor %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_VERSION, MAXB, buffer, &length);
		printf("Platform Version %s\n", buffer);
		clGetPlatformInfo(platform_id[i], CL_PLATFORM_PROFILE, MAXB, buffer, &length);
		printf("Platform Profile %s\n", buffer);
		// if(buffer[length - 1] == '\0')
		// 	printf("There is a \\0.");

		cl_device_id devices[MAXDEVICE];
		cl_device_id cpus[MAXCPU];
		cl_device_id gpus[MAXGPU];
		cl_uint device_id_got;
		cl_uint cpu_id_got;
		cl_uint gpu_id_got;
		clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_ALL, MAXDEVICE, devices, &device_id_got);
		printf("%u Devices\n", device_id_got);
		clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_CPU, MAXCPU, cpus, &cpu_id_got);
		printf("%u CPU Devices\n", cpu_id_got);
		clGetDeviceIDs(platform_id[i], CL_DEVICE_TYPE_GPU, MAXGPU, gpus, &gpu_id_got);
		printf("%u GPU Devices\n", gpu_id_got);

		for(int j = 0; j < device_id_got; j++){
			clGetDeviceInfo(devices[j], CL_DEVICE_NAME, MAXB, buffer, &length);
			printf("Device name %s\n", buffer);
			// if(buffer[length - 1] == '\0')
			// 	printf("There is a \\0.");
			cl_ulong number;
			clGetDeviceInfo(devices[j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &number, NULL);
			printf("Global memory size %lld\n", (long long)number);
			clGetDeviceInfo(devices[j], CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &number, NULL);
			printf("Local memory size %lld\n", (long long)number);
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_ulong), &number, NULL);
			printf("# of compute units %lld\n", (long long)number);
			clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_ulong), &number, NULL);
			printf("max # of work items in a work group %lld\n", (long long)number);

		}
	}
	return 0;
}	