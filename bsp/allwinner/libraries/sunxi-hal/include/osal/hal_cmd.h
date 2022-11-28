#ifndef SUNXI_HAL_CMD_H
#define SUNXI_HAL_CMD_H

#ifdef __cplusplus
extern "C"
{
#endif

/* include me to supprot FINSH_FUNCTION_EXPORT_CMD */

#ifdef CONFIG_KERNEL_FREERTOS
#include <console.h>
#else
#include <rtthread.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
