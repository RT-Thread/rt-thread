#ifndef __TYPES_H__
#define __TYPES_H__

#include <rtthread.h>

typedef rt_off_t 	off_t;
typedef rt_size_t 	size_t;

typedef rt_uint8_t 	u_char;
typedef rt_uint16_t u_short;
typedef rt_ubase_t 	u_int;
typedef rt_uint32_t u_long;

typedef rt_uint8_t 	u_int8_t;
typedef rt_uint16_t u_int16_t;
typedef rt_uint32_t u_int32_t;

typedef rt_time_t time_t;

#ifndef NULL
#define NULL RT_NULL
#endif

#endif
