#include <stdio.h>
#include <assert.h>
#include <omp.h>
#include <inttypes.h>
#include <assert.h>
#include "utils.h"
#include <CL/cl.h>
 
#define MAXGPU 8
#define MAXCODESZ 32767
#define MAXN 16777216
static cl_uint A[MAXN], B[MAXN], C[MAXN];
int main(int argc, char *argv[]) {
    omp_set_num_threads(4);
    int N;
    uint32_t key1, key2;
    while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {
        int chunk = N / 4;
        for (int i = 0; i < N; i++) {
            A[i] = encrypt(i, key1);
            B[i] = encrypt(i, key2);
        }

        cl_int status;
        cl_platform_id platform_id;
        cl_uint platform_id_got;
        status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
        assert(status == CL_SUCCESS && platform_id_got == 1);

        cl_device_id GPU[MAXGPU];
        cl_uint GPU_id_got;
        status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
        assert(status == CL_SUCCESS);

        cl_ulong number;
        status = clGetDeviceInfo(GPU[0], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(cl_ulong), &number, NULL);
        if(status != CL_SUCCESS){
            return 1;
        }

        cl_context context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);
        assert(status == CL_SUCCESS);

        cl_command_queue commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
        assert(status == CL_SUCCESS);

        FILE *kernelfp = fopen("vecdot.cl", "r");
        assert(kernelfp != NULL);
        char kernelBuffer[MAXCODESZ];
        const char *constKernelSource = kernelBuffer;
        size_t kernelLength = fread(kernelBuffer, 1, MAXCODESZ, kernelfp);

        cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);
        assert(status == CL_SUCCESS);

        status = clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL);
        assert(status == CL_SUCCESS);

        cl_kernel kernel = clCreateKernel(program, "vecdot", &status);
        assert(status == CL_SUCCESS);

        cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), A, &status);
        assert(status == CL_SUCCESS);
        cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), B, &status);
        assert(status == CL_SUCCESS);
        cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, N * sizeof(cl_uint), C, &status);
        assert(status == CL_SUCCESS);
 
        status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
        assert(status == CL_SUCCESS);
        status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
        assert(status == CL_SUCCESS);
        status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
        assert(status == CL_SUCCESS);

        size_t globalThreads[] = {(size_t)N};
        size_t localThreads[] = {number};
        status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalThreads, localThreads, 0, NULL, NULL);
        assert(status == CL_SUCCESS);

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