#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "../../include/opencl.h"


static size_t
numof_kernel_codes(const char *path) {
  size_t        count = 0;
  DIR           *kernel_dir;
  struct dirent *kernel_stts;

  char *p;

  if((kernel_dir = opendir(path)) == NULL) {
    perror(path);
    return EOF;
  }
  while((kernel_stts = readdir(kernel_dir)) != NULL) {
    p = strstr(kernel_stts->d_name, ".c");
    if(p != NULL) count++;
  }
  closedir(kernel_dir);

  return count;
}


int
read_kernel_codes(const char *path,
                  cl_prop *prop) {
  int   i;
  char *p;
  long full_length;

  FILE          *kernel_fp;
  DIR           *kernel_dir;
  struct dirent *kernel_stts;

  prop->kcode.count = numof_kernel_codes(path);
  prop->kcode.paths = (char **)calloc(prop->kcode.count, sizeof(char *));
  prop->kcode.codes = (char **)calloc(prop->kcode.count, sizeof(char *));

  if((kernel_dir = opendir(path)) == NULL) {
    perror(path);
    return EOF;
  }

  i = 0;
  while((kernel_stts = readdir(kernel_dir)) != NULL) {
    p = strstr(kernel_stts->d_name, ".c");
    if(p != NULL) {
      full_length = strlen(path) + 1 + strlen(kernel_stts->d_name);
      prop->kcode.paths[i] = (char *)calloc(full_length, sizeof(char));
      sprintf(prop->kcode.paths[i], "%s/%s", path, kernel_stts->d_name);
      i += 1;
    }
  }
  closedir(kernel_dir);

  for(i = 0; i < prop->kcode.count; i++) {
    if((kernel_fp = fopen(prop->kcode.paths[i], "r")) == NULL) {
      perror(prop->kcode.paths[i]);
      return EOF;
    }

    fseek(kernel_fp, 0L, SEEK_END);
    full_length = ftell(kernel_fp);
    fseek(kernel_fp, 0L, SEEK_SET);

    prop->kcode.codes[i] = (char *)calloc(full_length, sizeof(char));
    fread((void *)prop->kcode.codes[i], sizeof(char), full_length, kernel_fp);

    fclose(kernel_fp);
    kernel_fp = NULL;
  }

  return 0;
}
