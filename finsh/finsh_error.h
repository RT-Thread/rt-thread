#ifndef __FINSH_ERROR_H__
#define __FINSH_ERROR_H__

#include <finsh.h>

int finsh_error_init(void);

/* get error number */
u_char finsh_errno(void);

int finsh_error_set(u_char type);
const char* finsh_error_string(u_char type);

#endif
