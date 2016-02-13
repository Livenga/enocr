#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "../../include/common.h"
#include "../../include/opencl.h"

#ifdef __PRINT_DEBUG
static void
print_build_log(const int did,
                cl_prop *prop);
#endif


cl_int
cl_set_properties(const int did,
                  cl_prop *prop) {
  cl_int status;

  prop->context = clCreateContext(0,
      prop->num_devices,
      (const cl_device_id *)prop->devices,
      NULL,
      NULL,
      &status);

  prop->queue = clCreateCommandQueueWithProperties(
      prop->context, prop->devices[did],
      0, &status);

  prop->program = clCreateProgramWithSource(
      prop->context,
      prop->kcode.count,
      (const char **)prop->kcode.codes,
      NULL,
      &status);

  const char *options = "-I ./include";
  status = clBuildProgram(prop->program,
      prop->num_devices, (const cl_device_id *)prop->devices,
      (const char *)options, NULL, NULL);

#ifdef __PRINT_DEBUG
  if(status != CL_SUCCESS)
    fprintf(stderr, "[%sBuild Error Log%s]\n", ERR_STR, CLR_STR);
  else
    fprintf(stderr, "[%sBuild Log%s]\n", WHT_STR, CLR_STR);
  print_build_log(did, prop);
#endif

  prop->kernel = clCreateKernel(prop->program,
      (const char *)"hello", &status);

  return status;
}


#ifdef __PRINT_DEBUG
static void
print_build_log(const int did,
                cl_prop *prop) {
  size_t value_size;
  char   *param_value;

  clGetProgramBuildInfo(prop->program, prop->devices[did],
      CL_PROGRAM_BUILD_LOG, 0, (void *)NULL, &value_size);

  param_value = (char *)calloc(value_size, sizeof(char));

  clGetProgramBuildInfo(prop->program, prop->devices[did],
      CL_PROGRAM_BUILD_LOG, value_size, (void *)param_value, (size_t *)NULL);

  fprintf(stderr, "%s\n\n", param_value);

  bzero((void *)param_value, sizeof(char) * value_size);
  free(param_value);
  param_value = NULL;
}
#endif
