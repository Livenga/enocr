#ifndef __COMMON_H
#define __COMMON_H

#define ERR_STR "\033[5;31m"
#define WHT_STR "\033[1;37m"
#define GRN_STR "\033[1;32m"
#define CLR_STR "\033[0;39m"

#define __PRINT_DEBUG

#ifdef __PRINT_DEBUG
extern void
print_used_memory(void);
#endif

#endif
