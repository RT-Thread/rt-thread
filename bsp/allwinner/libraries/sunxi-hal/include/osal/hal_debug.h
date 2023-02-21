#ifndef SUNXI_HAL_DEBUG_H
#define SUNXI_HAL_DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CONFIG_KERNEL_FREERTOS

#include <FreeRTOSConfig.h>
#define hal_soft_break soft_break

#else

#include <debug.h>
#define hal_soft_break software_break

#endif

#define hal_sys_abort()     \
    do {                    \
        hal_soft_break(0);  \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif
