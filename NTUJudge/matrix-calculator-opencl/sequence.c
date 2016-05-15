#include <stdio.h>
#include <stdint.h>
#include <CL/cl.h>
#define UINT uint32_t
#define MAXN 1024

#define MAXCODE 4096
#define MAXDEVICE 8
#define TEMPN 6
#define KERNELN 2
#define DEVICEN 3
#define BUFFERN 6
#define MAXLOG 4096

void rand_gen(UINT c, int N, UINT A[][MAXN]) {
    UINT x = 2, n = N*N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x = (x * x + c + i + j)%n;
            A[i][j] = x;
        }
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
UINT IN[6][MAXN][MAXN], TMP[6][MAXN][MAXN];
int main() {
    int N, S[6];
    scanf("%d", &N);
    for (int i = 0; i < 6; i++) {
        scanf("%d", &S[i]);
        rand_gen(S[i], N, IN[i]);
    }

    cl_int status;
    cl_platform_id platform_id;
    cl_uint num_platform;
    cl_device_id device_ids[MAXDEVICE];
    cl_uint num_device;

    cl_context context;
    cl_command_queue command_queues[DEVICEN];
    cl_program program;
    cl_kernel kernels[KERNELN];
    cl_mem buffers[BUFFERN];
    cl_mem buffer_temp[TEMPN];

    FILE *fp;
    char kb[MAXCODE];
    const char *bp = kb;
    size_t fl;

    size_t global[] = {(size_t)N, (size_t)N};
    size_t local[] = {(size_t)1, (size_t)1};

    status = clGetPlatformIDs(1, &platform_id, &num_platform);
    if(status != CL_SUCCESS){
        printf("%d\n", status);
    }

    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXDEVICE, device_ids, &num_device);
    if(status != CL_SUCCESS){
        printf("%d\n", status);
    }

    context = clCreateContext(NULL, DEVICEN, device_ids, NULL, NULL, &status);
    if(status != CL_SUCCESS){
        printf("%d\n", status);
    }

    for(int i = 0; i < DEVICEN; i++){
        command_queues[i] = clCreateCommandQueue(context, device_ids[i], 0, &status);
        if(status != CL_SUCCESS){
            printf("%d\n", status);
        }
    }

    fp = fopen("matrix-lib.cl", "r");
    fl = fread(kb, 1, MAXCODE, fp);
    program = clCreateProgramWithSource(context, 1, &bp, &fl, &status);
    if(status != CL_SUCCESS){
        printf("%d\n", status);
    }

    status = clBuildProgram(program, DEVICEN, device_ids, NULL, NULL, NULL);
    if(status != CL_SUCCESS){
        char log[MAXLOG];
        size_t log_length;
        clGetProgramBuildInfo(program, device_ids[0], CL_PROGRAM_BUILD_LOG, MAXLOG, log, &log_length);
        puts(log);
    }

    kernels[0] = clCreateKernel(program, "mul", &status);
    if(status != CL_SUCCESS){
        printf("%d\n", status);
    }
    kernels[1] = clCreateKernel(program, "add", &status);
    if(status != CL_SUCCESS){
        printf("%d\n", status);
    }

    for(int i = 0; i < BUFFERN; i++){
        buffers[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), IN[i], &status);
        if(status != CL_SUCCESS){
            printf("%d\n", status);
        }
    }

    for(int i = 0; i < TEMPN; i++){
        buffer_temp[i] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), NULL, &status);
        // buffer_temp[i] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR , MAXN * MAXN * sizeof(cl_uint), TMP[i], &status);
        if(status != CL_SUCCESS){
            printf("%d\n", status);
        }
    }

    // AB
    status = clSetKernelArg(kernels[0], 0, sizeof(cl_mem), (void*)&buffers[0]);
    status = clSetKernelArg(kernels[0], 1, sizeof(cl_mem), (void*)&buffers[1]);
    status = clSetKernelArg(kernels[0], 2, sizeof(cl_mem), (void*)&buffer_temp[0]);
    status = clSetKernelArg(kernels[0], 3, sizeof(int), (void*)&N);
    status = clEnqueueNDRangeKernel(command_queues[0], kernels[0], 2, NULL, global, local, 0, NULL, NULL);
    //multiply(N, IN[0], IN[1], TMP[0]);
    // CD
    status = clSetKernelArg(kernels[0], 0, sizeof(cl_mem), (void*)&buffers[2]);
    status = clSetKernelArg(kernels[0], 1, sizeof(cl_mem), (void*)&buffers[3]);
    status = clSetKernelArg(kernels[0], 2, sizeof(cl_mem), (void*)&buffer_temp[1]);
    status = clSetKernelArg(kernels[0], 3, sizeof(int), (void*)&N);
    status = clEnqueueNDRangeKernel(command_queues[1], kernels[0], 2, NULL, global, local, 0, NULL, NULL);
    //multiply(N, IN[2], IN[3], TMP[1]);
    clEnqueueReadBuffer(command_queues[0], buffer_temp[0], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[0], 0, NULL, NULL);
    clEnqueueReadBuffer(command_queues[1], buffer_temp[1], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[1], 0, NULL, NULL);
    // AB+CD
    status = clSetKernelArg(kernels[1], 0, sizeof(cl_mem), (void*)&buffer_temp[0]);
    status = clSetKernelArg(kernels[1], 1, sizeof(cl_mem), (void*)&buffer_temp[1]);
    status = clSetKernelArg(kernels[1], 2, sizeof(cl_mem), (void*)&buffer_temp[2]);
    status = clSetKernelArg(kernels[1], 3, sizeof(int), (void*)&N);
    status = clEnqueueNDRangeKernel(command_queues[2], kernels[1], 2, NULL, global, local, 0, NULL, NULL);
    clEnqueueReadBuffer(command_queues[2], buffer_temp[2], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[2], 0, NULL, NULL);
    //add(N, TMP[0], TMP[1], TMP[2]);
    printf("%u\n", signature(N, TMP[2]));
 
    // ABE
    status = clSetKernelArg(kernels[0], 0, sizeof(cl_mem), (void*)&buffer_temp[0]);
    status = clSetKernelArg(kernels[0], 1, sizeof(cl_mem), (void*)&buffers[4]);
    status = clSetKernelArg(kernels[0], 2, sizeof(cl_mem), (void*)&buffer_temp[3]);
    status = clSetKernelArg(kernels[0], 3, sizeof(int), (void*)&N);
    status = clEnqueueNDRangeKernel(command_queues[0], kernels[0], 2, NULL, global, local, 0, NULL, NULL);
    //multiply(N, TMP[0], IN[4], TMP[3]);
    // CDF
    status = clSetKernelArg(kernels[0], 0, sizeof(cl_mem), (void*)&buffer_temp[1]);
    status = clSetKernelArg(kernels[0], 1, sizeof(cl_mem), (void*)&buffers[5]);
    status = clSetKernelArg(kernels[0], 2, sizeof(cl_mem), (void*)&buffer_temp[4]);
    status = clSetKernelArg(kernels[0], 3, sizeof(int), (void*)&N);
    status = clEnqueueNDRangeKernel(command_queues[1], kernels[0], 2, NULL, global, local, 0, NULL, NULL);
    //multiply(N, TMP[1], IN[5], TMP[4]);
    clEnqueueReadBuffer(command_queues[0], buffer_temp[3], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[3], 0, NULL, NULL);
    clEnqueueReadBuffer(command_queues[1], buffer_temp[4], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[4], 0, NULL, NULL);
    // ABE+CDF
    status = clSetKernelArg(kernels[1], 0, sizeof(cl_mem), (void*)&buffer_temp[3]);
    status = clSetKernelArg(kernels[1], 1, sizeof(cl_mem), (void*)&buffer_temp[4]);
    status = clSetKernelArg(kernels[1], 2, sizeof(cl_mem), (void*)&buffer_temp[5]);
    status = clSetKernelArg(kernels[1], 3, sizeof(int), (void*)&N);
    status = clEnqueueNDRangeKernel(command_queues[2], kernels[1], 2, NULL, global, local, 0, NULL, NULL);
    clEnqueueReadBuffer(command_queues[2], buffer_temp[5], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[5], 0, NULL, NULL);
    //add(N, TMP[3], TMP[4], TMP[5]);
    printf("%u\n", signature(N, TMP[5]));

    clReleaseContext(context);
    for(int i = 0; i < DEVICEN; i++){
        clReleaseCommandQueue(command_queues[i]);
    }
    clReleaseProgram(program);
    for(int i = 0; i < KERNELN; i++){
        clReleaseKernel(kernels[i]);
    }
    for(int i = 0; i < BUFFERN; i++){
        clReleaseMemObject(buffers[i]);
    }
    for(int i = 0; i < TEMPN; i++){
        clReleaseMemObject(buffer_temp[i]);
    }

    return 0;
}