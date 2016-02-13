#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CL/cl.h>
#include "../../include/opencl.h"

void
cl_print_platform(const cl_prop prop) {
  int i;
  char buffer[4096];

  for(i = 0; i < prop.num_platforms; i++) {
    printf("[Platform ID] %d\n", i);

    bzero((void *)buffer, sizeof(buffer));
    clGetPlatformInfo(prop.platforms[i], CL_PLATFORM_PROFILE,
        sizeof(buffer), (void *)buffer, NULL);
    printf("[Platform Profile] %s\n", buffer);

    bzero((void *)buffer, sizeof(buffer));
    clGetPlatformInfo(prop.platforms[i], CL_PLATFORM_VERSION,
        sizeof(buffer), (void *)buffer, NULL);
    printf("[Platform Version] %s\n", buffer);
    
    bzero((void *)buffer, sizeof(buffer));
    clGetPlatformInfo(prop.platforms[i], CL_PLATFORM_NAME,
        sizeof(buffer), (void *)buffer, NULL);
    printf("[Platform Name]    %s\n", buffer);
    
    bzero((void *)buffer, sizeof(buffer));
    clGetPlatformInfo(prop.platforms[i], CL_PLATFORM_VENDOR,
        sizeof(buffer), (void *)buffer, NULL);
    printf("[Platform Vendor]  %s\n", buffer);
  }
}
