#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "../../include/common.h"
#include "../../include/opencl.h"

void
cl_prop_destroy(cl_prop *prop) {
  int i;

  clReleaseKernel(prop->kernel);
  clReleaseProgram(prop->program);
  clReleaseCommandQueue(prop->queue);
  clReleaseContext(prop->context);

  free(prop->devices);   prop->devices = NULL;
  free(prop->platforms); prop->platforms = NULL;

  for(i = 0; i < prop->kcode.count; i++) {
    free(prop->kcode.paths[i]); prop->kcode.paths[i] = NULL;
    free(prop->kcode.codes[i]); prop->kcode.codes[i] = NULL;
  }
  free(prop->kcode.paths); prop->kcode.paths = NULL;
  free(prop->kcode.codes); prop->kcode.codes = NULL;
}
