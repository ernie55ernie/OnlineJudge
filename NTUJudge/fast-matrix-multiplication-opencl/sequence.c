#include <stdio.h>
#include <stdint.h>
#include <CL/cl.h>
// #define DEBUG
#define UINT uint32_t
#define MAXN 1024
#define MAXGPU 8
#define MAXK 1024

void rand_gen(UINT c, int N, UINT A[][MAXN]) {
    UINT x = 2, n = N*N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c + i + j)%n;
            A[i][j] = x;
        }
    }
}
void print_matrix(int N, UINT A[][MAXN]) {
    for (int i = 0; i < N; i++) {
        fprintf(stderr, "[");
        for (int j = 0; j < N; j++)
            fprintf(stderr, " %u", A[i][j]);
        fprintf(stderr, " ]\n");
    }
}
UINT signature(int N, UINT A[][MAXN]) {
    UINT h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            h = (h + A[i][j]) * 2654435761LU;
    }
    return h;
}
UINT A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];

int main() {
    int N;
    uint32_t S1, S2;
    scanf("%d %u %u", &N, &S1, &S2);
    rand_gen(S1, N, A);
    rand_gen(S2, N, B);
    cl_int status;
    cl_platform_id platform_id;
    cl_uint platform_id_got;
    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
    if(status == CL_SUCCESS && platform_id_got == 1);
    cl_device_id GPU[MAXGPU];
    cl_uint GPU_id_got;
    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);
    if(status == CL_SUCCESS); 

    cl_context context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);
    if(status == CL_SUCCESS);

    cl_command_queue commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
    if(status == CL_SUCCESS);
    
    FILE *kernelfp = fopen("matrixmul.cl", "r");
    if(kernelfp != NULL);
    char kernelBuffer[MAXK];
    const char *constKernelSource = kernelBuffer;
    size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);
    cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);
    if(status == CL_SUCCESS);
    
    status = clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL);
    if(status == CL_SUCCESS);
    
    cl_kernel kernel = clCreateKernel(program, "multiply", &status);
    if(status == CL_SUCCESS);
    
    cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), A, &status);
    if(status == CL_SUCCESS);
    cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), B, &status);
    if(status == CL_SUCCESS);
    cl_mem bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), C, &status);
    if(status == CL_SUCCESS);
    
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&bufferA);
    if(status == CL_SUCCESS);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&bufferB);
    if(status == CL_SUCCESS);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&bufferC);
    if(status == CL_SUCCESS);
    status = clSetKernelArg(kernel, 3, sizeof(int), (void*)&N);
    if(status == CL_SUCCESS);
    
    size_t globalThreads[] = {(size_t)N, (size_t)N};
    size_t localThreads[] = {4, 4};
    status = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, globalThreads, localThreads, 0, NULL, NULL);
    if(status == CL_SUCCESS);
    
    clEnqueueReadBuffer(commandQueue, bufferC, CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), C, 0, NULL, NULL);

    clReleaseContext(context);
    clReleaseCommandQueue(commandQueue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);
#ifdef DEBUG
    print_matrix(N, A);
    print_matrix(N, B);
    print_matrix(N, C);
#endif
    printf("%u\n", signature(N, C));
    return 0;
}