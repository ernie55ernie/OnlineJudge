#include <stdio.h>
#include <assert.h>
#include <omp.h>
#include <inttypes.h>
#include <assert.h>
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
        if(status != CL_SUCCESS && platform_id_got != 1){
            abort();
        }

        cl_device_id GPU[MAXGPU];
        cl_uint GPU_id_got;
        status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
        if(status != CL_SUCCESS){
            abort();
        };

        cl_context context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);
        if(status != CL_SUCCESS){
            abort();
        }

        cl_command_queue commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
        if(status != CL_SUCCESS){
            clReleaseContext(context);
            abort();
        }

        FILE *kernelfp = fopen("vecdot.cl", "r");
        assert(kernelfp != NULL);
        char kernelBuffer[MAXK];
        const char *constKernelSource = kernelBuffer;
        size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);

        cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);
        if(status != CL_SUCCESS){
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            abort();
        }

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
        if(status != CL_SUCCESS){
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }

        cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), A, &status);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }
        cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, N * sizeof(cl_uint), B, &status);
        assert(status == CL_SUCCESS);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferB);
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }
        cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, N * sizeof(cl_uint), C, &status);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferC);
            clReleaseMemObject(bufferB);
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }
 
        status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferC);
            clReleaseMemObject(bufferB);
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }
        status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferC);
            clReleaseMemObject(bufferB);
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }
        status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferC);
            clReleaseMemObject(bufferB);
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }

        size_t globalThreads[] = {(size_t)N};
        size_t localThreads[] = {1};
        status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalThreads, localThreads, 0, NULL, NULL);
        if(status != CL_SUCCESS){
            clReleaseMemObject(bufferC);
            clReleaseMemObject(bufferB);
            clReleaseMemObject(bufferA);
            clReleaseKernel(kernel);
            clReleaseContext(context);
            clReleaseCommandQueue(commandQueue);
            clReleaseProgram(program);
            abort();
        }

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