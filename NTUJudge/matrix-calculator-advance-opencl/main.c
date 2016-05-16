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
#define MAXEQ 1024
#define MAXM 26

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

UINT IN[MAXM][MAXN][MAXN], TMP[MAXM][MAXN][MAXN];
int main() {
    int M, N, Q, add_stack_size = 0, addstack[MAXM], tmp_size = 0;
    char line[MAXEQ];
    scanf("%d %d", &M, &N);
    int S[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d", &S[i]);
        rand_gen(S[i], N, IN[i]);
    }
    scanf("%d", &Q);

    cl_int status;
    cl_platform_id platform_id;
    cl_uint num_platform;
    cl_device_id device_ids[MAXDEVICE];
    cl_uint num_device;

    cl_context context;
    cl_command_queue command_queues[DEVICEN];
    cl_program program;
    cl_kernel kernels[KERNELN];
    cl_mem buffers[M];
    cl_mem buffer_temp[M];

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

    for(int i = 0; i < M; i++){
        buffers[i] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), IN[i], &status);
        if(status != CL_SUCCESS){
            printf("%d\n", status);
        }
    }

    for(int i = 0; i < M; i++){
        buffer_temp[i] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, MAXN * MAXN * sizeof(cl_uint), NULL, &status);
        // buffer_temp[i] = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR , MAXN * MAXN * sizeof(cl_uint), TMP[i], &status);
        if(status != CL_SUCCESS){
            printf("%d\n", status);
        }
    }

    for(int i = 0; i < Q; i++){
        scanf("%s", line);
        int mul = 0;
        printf("%s\n", line);
        for(int j = 0; line[j] != '\0'; j++){
            printf("%d\n", mul);
            if(line[j] == '+'){
                addstack[add_stack_size++] = mul - 1;
                mul = 0;
            }else{
                int matrix = line[j] - 'A';
                if(mul == 0){
                    mul = matrix + 1;
                }else{
                    status = clSetKernelArg(kernels[0], 0, sizeof(cl_mem), (void*)(mul < 0 ? &buffer_temp[- mul - 1] : &buffers[mul - 1]));
                    status = clSetKernelArg(kernels[0], 1, sizeof(cl_mem), (void*)&buffers[matrix]);
                    status = clSetKernelArg(kernels[0], 2, sizeof(cl_mem), (void*)&buffer_temp[tmp_size + 1]);
                    status = clSetKernelArg(kernels[0], 3, sizeof(int), (void*)&N);
                    status = clEnqueueNDRangeKernel(command_queues[0], kernels[0], 2, NULL, global, local, 0, NULL, NULL);
                    clEnqueueReadBuffer(command_queues[0], buffer_temp[tmp_size + 1], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[tmp_size++], 0, NULL, NULL);
                    mul = - tmp_size - 1;
                }
            }
        }
        for(int j = 0; j < add_stack_size - 1; j++){
            status = clSetKernelArg(kernels[1], 0, sizeof(cl_mem), (void*)&buffer_temp[addstack[j]]);
            status = clSetKernelArg(kernels[1], 1, sizeof(cl_mem), (void*)&buffer_temp[addstack[j + 1]]);
            status = clSetKernelArg(kernels[1], 2, sizeof(cl_mem), (void*)&buffer_temp[tmp_size++]);
            status = clSetKernelArg(kernels[1], 3, sizeof(int), (void*)&N);
            status = clEnqueueNDRangeKernel(command_queues[0], kernels[1], 2, NULL, global, local, 0, NULL, NULL);
            clEnqueueReadBuffer(command_queues[0], buffer_temp[5], CL_TRUE, 0, MAXN * MAXN * sizeof(cl_uint), TMP[tmp_size], 0, NULL, NULL);
        }
        printf("%u\n", signature(N, TMP[tmp_size]));
        add_stack_size = 0;
    }

    clReleaseContext(context);
    for(int i = 0; i < DEVICEN; i++){
        clReleaseCommandQueue(command_queues[i]);
    }
    clReleaseProgram(program);
    for(int i = 0; i < KERNELN; i++){
        clReleaseKernel(kernels[i]);
    }
    for(int i = 0; i < M; i++){
        clReleaseMemObject(buffers[i]);
    }
    for(int i = 0; i < M; i++){
        clReleaseMemObject(buffer_temp[i]);
    }

    return 0;
}