#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>
#include <rtthread.h>

typedef rt_int32_t clockid_t;
typedef rt_int32_t key_t;       /* Used for interprocess communication. */
typedef rt_int32_t pid_t;       /* Used for process IDs and process group IDs. */
typedef signed long ssize_t;    /* Used for a count of bytes or an error indication. */

typedef int mode_t;

#endif
