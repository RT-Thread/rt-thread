#ifndef TYPEDEF_H__
#define TYPEDEF_H__

#include <stdint.h>
#include "os.h"

typedef int8_t      __s8;
typedef int8_t      s8;
typedef uint8_t     __u8;
typedef uint8_t     u8;

typedef int16_t     __s16;
typedef int16_t     s16;
typedef uint16_t    __u16;
typedef uint16_t    u16;

typedef uint32_t    __u32;
typedef uint32_t    u32;
typedef int32_t     __s32;
typedef int32_t     s32;

typedef int64_t     __s64;
typedef int64_t     s64;
typedef uint64_t    __u64;
typedef uint64_t    u64;

#define __packed        __attribute__((packed))
#define __aligned(x)    __attribute__((__aligned__(x)))

#ifndef EPDK_OK
#define EPDK_OK         0
#endif

#ifndef EPDK_FAIL
#define EPDK_FAIL       (-1)
#endif

#ifndef EPDK_TRUE
#define EPDK_TRUE       1
#endif

#ifndef EPDK_FALSE
#define EPDK_FALSE      0
#endif

#ifndef EPDK_DISABLED
#define EPDK_DISABLED   0
#endif

#ifndef EPDK_ENABLED
#define EPDK_ENABLED    1
#endif

#ifndef EPDK_NO
#define EPDK_NO         0
#endif

#ifndef EPDK_YES
#define EPDK_YES        1
#endif

#ifndef EPDK_OFF
#define EPDK_OFF        0
#endif

#ifndef EPDK_ON
#define EPDK_ON         1
#endif

#ifndef EPDK_CLR
#define EPDK_CLR        0
#endif

#ifndef EPDK_SET
#define EPDK_SET        1
#endif

typedef struct
{
    char gpio_name[32];
    int port;
    int port_num;
    int mul_sel;
    int pull;
    int drv_level;
    int data;
} user_gpio_set_t;

#endif
