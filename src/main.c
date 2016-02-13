#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/common.h"
#include "../include/canvas.h"
#include "../include/opencl.h"

int main(int argc, char *argv[])
{
  const int pid = 0, did = 0;
  cl_prop prop;

  canvas cv_eye;
  n_canvas ncv_eye;


  /* OpenCL 設定 */
  read_kernel_codes("./src/kernel", &prop);
  get_platforms(&prop);
  get_devices(pid, &prop);
  cl_set_properties(did, &prop);

#ifdef __PRINT_DEBUG__
  int i;
  printf("[Number of Platforms] %d\n", prop.num_platforms);
  printf("[Number of Devices]   %d\n", prop.num_devices);
  printf("[Number of Codes]     %ld\n", prop.kcode.count);
  for(i = 0; i < prop.kcode.count; i++)
    printf("%s\n%s\n", prop.kcode.paths[i], prop.kcode.codes[i]);

  cl_print_platform(prop);
#endif

  pnread("./images/eye.png", &cv_eye);
  printf("[Canvas Size] %ldx%ld\n",
      cv_eye.width, cv_eye.height);

  cv2normalize(&ncv_eye, cv_eye);


  print_used_memory();
  n_canvas_destroy(&ncv_eye);
  canvas_destroy(&cv_eye);

  cl_prop_destroy(&prop);
  return 0;
}
