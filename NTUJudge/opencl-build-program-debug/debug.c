#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#ifdef __APPLE__
  #include <OpenCL/opencl.h>
#else
  #include <CL/cl.h>
#endif
 
#define MAXGPU 16
#define MAXK 2048
#define MAXCODESZ 16777216
int main(int argc, char *argv[]) {
    char filename[MAXK];
    scanf("%s", filename);

    cl_int status;
    cl_platform_id platform_id;
    cl_uint platform_id_got;
    status = clGetPlatformIDs(1, &platform_id, &platform_id_got);
    if(status != CL_SUCCESS && platform_id_got != 1){
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

    cl_command_queue commandQueue = clCreateCommandQueue(context, GPU[0], 0, &status);
    if(status != CL_SUCCESS){
        clReleaseContext(context);
        return 1;
    }

    FILE *kernelfp = fopen(filename, "r");
    assert(kernelfp != NULL);
    char kernelBuffer[MAXCODESZ];
    const char *constKernelSource = kernelBuffer;
    size_t kernelLength = fread(kernelBuffer, 1, MAXK, kernelfp);

    cl_program program = clCreateProgramWithSource(context, 1, &constKernelSource, &kernelLength, &status);
    if(status != CL_SUCCESS){
        clReleaseContext(context);
        clReleaseCommandQueue(commandQueue);
        return 1;
    }

    if (clBuildProgram(program, GPU_id_got, GPU, NULL, NULL, NULL) != CL_SUCCESS) {
        char buffer[10240];
        clGetProgramBuildInfo(program, GPU[0], CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, NULL);
        printf("%s", buffer);

        clReleaseContext(context);
        clReleaseCommandQueue(commandQueue);
        clReleaseProgram(program);
        return 1;
    }

    clReleaseContext(context);
    clReleaseCommandQueue(commandQueue);
    clReleaseProgram(program);
    return 0;
}