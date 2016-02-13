#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "../../include/opencl.h"

static cl_int
numof_platforms(cl_prop *prop) {
  return clGetPlatformIDs(0, NULL, &prop->num_platforms);
}

cl_int
get_platforms(cl_prop *prop) {
  cl_int status;

  status = numof_platforms(prop);
  prop->platforms = (cl_platform_id *)calloc(
      prop->num_platforms, sizeof(cl_platform_id));

  status = clGetPlatformIDs(prop->num_platforms,
      prop->platforms, NULL);
  return status;
}

static cl_int
numof_devices(const int pid,
              cl_prop *prop) {
  return clGetDeviceIDs(prop->platforms[pid],
      CL_DEVICE_TYPE_CPU, 0, NULL, &prop->num_devices);
}

cl_int
get_devices(const int pid,
            cl_prop *prop) {
  cl_int status;

  status = numof_devices(pid, prop);
  prop->devices = (cl_device_id *)calloc(
      prop->num_devices, sizeof(cl_device_id));

  status = clGetDeviceIDs(prop->platforms[pid],
      CL_DEVICE_TYPE_CPU, prop->num_devices,
      prop->devices, NULL);

  return status;
}
