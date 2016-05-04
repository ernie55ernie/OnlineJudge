#include <stdio.h>
#include <inttypes.h>
#include "utils.h"
#include <CL/cl.h>
 
#define MAXGPU 8
#define MAXF 32767
#define MAXN 16777216
static cl_uint A[MAXN], B[MAXN], C[MAXN];
int main(int argc, char *argv[]) {
    unsigned int N;
    uint32_t key1, key2;

    FILE *fp = fopen("vecdot.cl", "r");
    char kb[MAXF];
    const char *kbuffer = kb;
    size_t klength = fread(kb, 1, MAXF, fp);

    cl_int status;
    cl_platform_id platform_id;
    cl_uint platform_id_got;
    cl_device_id GPU[MAXGPU];
    cl_uint GPU_id_got;
    cl_context context;
    cl_command_queue commandQueue;
    cl_program program;
    cl_kernel kernel;
    cl_mem bufferA;
    cl_mem bufferB;
    cl_mem bufferC;

    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);

    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);

    // cl_ulong number;
    // status = clGetDeviceInfo(GPU[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_ulong), &number, NULL);

    context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);

    commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);

    program = clCreateProgramWithSource(context, 1, &kbuffer, &klength, &status);

    status = clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL);

    kernel = clCreateKernel(program, "vecdot", &status);

    while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {

#pragma omp parallel for
        for (int i = 0; i < N; i++) {
            A[i] = encrypt(i, key1);
            B[i] = encrypt(i, key2);
        }

        bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), A, &status);
        
        bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), B, &status);
        
        bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, N * sizeof(cl_uint), C, &status);
 
        status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
        
        status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
        
        status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
        
        status = clSetKernelArg(kernel, 3, sizeof(int), (void*)&N);
        
        // size_t localThreads = number;
        // size_t globalThreads = (N / number + (N % number != 0)) * number;
        size_t localThreads = 1;
        size_t globalThreads = N;
        status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, &globalThreads, &localThreads, 0, NULL, NULL);

        clFinish(commandQueue);
        clEnqueueReadBuffer(commandQueue, bufferC, CL_TRUE, 0, N * sizeof(cl_uint), C, 0, NULL, NULL);

        uint32_t sum = 0;
#pragma omp parallel for reduction(+ : sum)
        for (int i = 0; i < N; i++)
            sum += C[i];
        printf("%" PRIu32 "\n", sum);
        clReleaseMemObject(bufferA);
        clReleaseMemObject(bufferB);
        clReleaseMemObject(bufferC);
    }

    clReleaseContext(context);
    clReleaseCommandQueue(commandQueue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    
    return 0;
}