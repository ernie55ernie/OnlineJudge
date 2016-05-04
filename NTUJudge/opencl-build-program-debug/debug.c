#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <CL/cl.h>
 
#define MAXGPU 8
#define MAXK 1024
int main(int argc, char *argv[]) {
    char filename[128];
    assert(scanf("%s", filename) == 1);

    FILE *kernelfp = fopen(filename, "r");
    assert(kernelfp != NULL);
    char kernelBuffer[MAXK];
    const char *constKernelSource = kernelBuffer;
    size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);

    cl_int status;
    cl_platform_id platform_id;
    cl_uint platform_id_got;
    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);

    cl_device_id GPU[MAXGPU];
    cl_uint GPU_id_got;
    status = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, MAXGPU, GPU, &GPU_id_got);

    cl_context context = clCreateContext(NULL, GPU_id_got, GPU, NULL, NULL, &status);

    cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);

    if (clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL) != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        char* buffer = (char*)calloc(log_size + 1, sizeof(char));
        clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, log_size + 1, buffer, NULL);
        printf("%s", buffer);
        free(buffer);
    }

    clReleaseContext(context);
    clReleaseProgram(program);
    return 0;
}