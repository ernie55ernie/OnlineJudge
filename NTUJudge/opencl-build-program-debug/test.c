#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <CL/cl.h>

#define FILELENGTH 1024
#define MAXGPU 8

int main() {

    char fileName[128];
    char filecontent[FILELENGTH];
    assert(scanf("%s", fileName) == 1);
    FILE *fp = fopen(fileName, "r");
    assert(fp != NULL);
    size_t length = fread(filecontent, 1, FILELENGTH, fp);

    const char* contentp = filecontent;
    cl_int status;
    cl_uint platform_id_got, gpu_id_got;
    cl_platform_id platform_id;
    cl_device_id GPUs[MAXGPU];
    
    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);

    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPUs, &gpu_id_got);
    
    cl_context context = clCreateContext(NULL, gpu_id_got, GPUs, NULL, NULL, &status);
    
    cl_program program = clCreateProgramWithSource(context, 1, &contentp, &length, &status);
    
    status = clBuildProgram(program, 1, GPUs, NULL, NULL, NULL);
    if (status != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, GPUs[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        char *program_log = (char*)malloc((log_size + 1) * sizeof(char));
        clGetProgramBuildInfo(program, GPUs[0], CL_PROGRAM_BUILD_LOG, log_size + 1, program_log, NULL);
        printf("%s", program_log);
        free(program_log);
    }

    clReleaseContext(context);
    clReleaseProgram(program);
    return 0;
}