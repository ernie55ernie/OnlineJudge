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
        if(status != CL_SUCCESS){
            return 1;
        }

        cl_device_id GPU[MAXGPU];
        cl_uint GPU_id_got;
        status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
        if(status != CL_SUCCESS){
            return 1;
        };

        cl_context context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);
        if(status != CL_SUCCESS){
            return 1;
        }

        FILE *kernelfp = fopen("vecdot.cl", "r");
        assert(kernelfp != NULL);
        char kernelBuffer[MAXK];
        const char *constKernelSource = kernelBuffer;
        size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);

        cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);
        if(status != CL_SUCCESS){
            clReleaseContext(context);
            return 1;
        }

        if (clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL) != CL_SUCCESS) {
            char buffer[10240];
            clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
            fprintf(stderr, "CL Compilation failed:\n%s", buffer);

            clReleaseContext(context);
            clReleaseProgram(program);
            return 1;
        }

        int n_per_device[GPU_id_got];
        cl_command_queue queues[GPU_id_got];
        cl_kernel kernels[GPU_id_got];
        cl_mem bufferAs[GPU_id_got];
        cl_mem bufferBs[GPU_id_got];
        cl_mem bufferCs[GPU_id_got];
        unsigned i;
        unsigned offset = 0;
        for(i = 0; i < GPU_id_got; i++){
            queues[i] = clCreateCommandQueue(context, GPU[i], 0, &status);
            if(status != CL_SUCCESS){
                clReleaseContext(context);
                clReleaseProgram(program);
                return 1;
            }

            n_per_device[i] = N / GPU_id_got;
            if(i < (N % GPU_id_got)){
                n_per_device[i]++;
            }

            kernels[i] = clCreateKernel(program, "vecdot", &status);

            bufferAs[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, n_per_device[i] * sizeof(cl_uint), &A[offset], &status);
            
            bufferBs[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, n_per_device[i] * sizeof(cl_uint), &B[offset], &status);
            
            bufferCs[i] = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, n_per_device[i] * sizeof(cl_uint), &C[offset], &status);
     
            status = clSetKernelArg(kernels[i], 0, sizeof(cl_mem), (void*)&bufferAs[i]);
            
            status = clSetKernelArg(kernels[i], 1, sizeof(cl_mem), (void*)&bufferBs[i]);
            
            status = clSetKernelArg(kernels[i], 2, sizeof(cl_mem), (void*)&bufferCs[i]);

            size_t globalworksize[] = {(size_t)n_per_device[i]};
            //size_t globalworkoffset = (size_t)offset * sizeof(cl_uint);
            size_t localworksize[] = {1};
            status = clEnqueueNDRangeKernel(queues[i], kernels[i], 1, NULL, globalworksize, localworksize, 0, NULL, NULL);

            clEnqueueReadBuffer(queues[i], bufferCs[i], CL_TRUE, 0, n_per_device[i] * sizeof(cl_uint), &C[offset], 0, NULL, NULL);
            offset += n_per_device[i];
        }
        
        uint32_t sum = 0;
        for (i = 0; i < N; i++)
            sum += C[i];
        printf("%" PRIu32 "\n", sum);

        clReleaseContext(context);
        for(i = 0;i < GPU_id_got; i++){
            clReleaseCommandQueue(queues[i]);
            clReleaseKernel(kernels[i]);
            clReleaseMemObject(bufferAs[i]);
            clReleaseMemObject(bufferBs[i]);
            clReleaseMemObject(bufferCs[i]);
        }
        clReleaseProgram(program);
    }
    return 0;
}