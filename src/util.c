#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void
print_used_memory(void) {
  FILE *status_fp;
  long used_memory;
  char index, *p;
  char status_path[4096], buffer[4096];
  pid_t pid;

  pid = getpid();

  bzero((void *)status_path, sizeof(status_path));
  bzero((void *)buffer, sizeof(buffer));

  sprintf(status_path, "/proc/%d/status", pid);

  if((status_fp = fopen(status_path, "r")) != NULL) {
    while(fgets((char *)buffer, sizeof(buffer), status_fp) != NULL) {
      p = strstr(buffer, "VmSize");
      if(p != NULL) {
        p = strchr(buffer, '\t');
        p++;
        strcpy((char *)buffer, (const char *)p);
        p = strchr(buffer, 'B');
        p--;
        index = *p;
        *p = '\0';

        used_memory = atol(buffer);

        switch(index) {
          case 'k': index = 'M'; break;
          case 'M': index = 'G'; break;
        }

        fprintf(stderr, "[Used Memory (PID: %d)] %.2f [%cB]\n",
            pid, (double)used_memory / 1024.0, index);
      }

      bzero((void *)buffer, sizeof(buffer));
    }
  } else {
    perror(status_path);
  }
}
