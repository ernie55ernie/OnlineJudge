#include <stdio.h>
#include <inttypes.h>
#include "utils.h"
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif
 
#define MAXGPU 8
#define MAXCODESZ 32767
#define MAXK 1024
#define MAXN 16777216
static cl_uint A[MAXN], B[MAXN], C[MAXN];
int main(int argc, char *argv[]) {
    unsigned int N;
    uint32_t key1, key2;
    while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {

        FILE *kernelfp = fopen("vecdot.cl", "r");
        char kernelBuffer[MAXK];
        const char *constKernelSource = kernelBuffer;
        size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);

        for (int i = 0; i < N; i++) {
            A[i] = encrypt(i, key1);
            B[i] = encrypt(i, key2);
        }

        cl_int status;
        cl_platform_id platform_id;
        cl_uint platform_id_got;
        status = clGetPlatformIDs(1, &platform_id, &platform_id_got);

        cl_device_id GPU[MAXGPU];
        cl_uint GPU_id_got;
        status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);

        cl_ulong number;
        status = clGetDeviceInfo(GPU[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_ulong), &number, NULL);

        cl_context context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);

        cl_command_queue commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);

        cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);

        if (clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL) != CL_SUCCESS) {
            char buffer[10240];
            clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
            fprintf(stderr, "CL Compilation failed:\n%s", buffer);

            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }

        cl_kernel kernel = clCreateKernel(program, "vecdot", &status);

        cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), A, &status);
        
        cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), B, &status);
        
        cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, N * sizeof(cl_uint), C, &status);
 
        status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
        
        status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
        
        status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
        
        status = clSetKernelArg(kernel, 3, sizeof(unsigned int), (void*)&N);
        
        // size_t localThreads = number;
        // size_t globalThreads = (N / number + (N % number != 0)) * number;
        size_t localThreads = 1;
        size_t globalThreads = N;
        status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &globalThreads, &localThreads, 0, NULL, NULL);

        clEnqueueReadBuffer(commandQueue, bufferC, CL_TRUE, 0, N * sizeof(cl_uint), C, 0, NULL, NULL);

        uint32_t sum = 0;
        for (int i = 0; i < N; i++)
            sum += C[i];
        printf("%" PRIu32 "\n", sum);

        clReleaseContext(context);
        clReleaseCommandQueue(commandQueue);
        clReleaseProgram(program);
        clReleaseKernel(kernel);
        clReleaseMemObject(bufferA);
        clReleaseMemObject(bufferB);
        clReleaseMemObject(bufferC);
    }
    return 0;
}