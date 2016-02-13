#ifndef __OPENCL_PROPERTIES__
#define __OPENCL_PROPERTIES__

#ifndef __OPENCL_CL_H
#include <CL/cl.h>
#endif

typedef struct _kernel_code {
  size_t count;
  char **paths;
  char **codes;
} k_code;

typedef struct _cl_properties {
  k_code kcode;

  cl_uint        num_platforms;
  cl_platform_id *platforms;
  cl_uint        num_devices;
  cl_device_id   *devices;

  cl_context       context;
  cl_command_queue queue;
  cl_program       program;
  cl_kernel        kernel;
} cl_prop;


/* src/cl/cl_code.c */
extern int
read_kernel_codes(const char *path,
                  cl_prop *prop);


/* src/cl/cl_device.c */
extern cl_int
get_platforms(cl_prop *prop);
extern cl_int
get_devices(const int pid,
            cl_prop *prop);


/* src/cl/cl_kernel.c */
extern cl_int
cl_set_properties(const int did,
                  cl_prop *prop);

/* src/cl/cl_util.c */
extern void
cl_prop_destroy(cl_prop *prop);


/* src/cl/cl_print.c */
extern void
cl_print_platform(const cl_prop prop);
#endif
