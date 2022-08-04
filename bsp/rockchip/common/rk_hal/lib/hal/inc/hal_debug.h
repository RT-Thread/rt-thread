/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2018-2021 Rockchip Electronics Co., Ltd.
 */

#ifndef _HAL_DEBUG_H_
#define _HAL_DEBUG_H_

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup DEBUG
 *  @{
 */

/***************************** MACRO Definition ******************************/

/* Run only for debugging, please refer to how-to-use for the definition of the specification. */
//#define HAL_DBG_USING_RTT_SERIAL
//#define HAL_DBG_USING_LIBC_PRINTF
#ifdef HAL_DBG_USING_RTT_SERIAL
#include <rthw.h>
#include <rtthread.h>

#define HAL_SYSLOG rt_kprintf
#elif defined(HAL_DBG_USING_LIBC_PRINTF)
#define HAL_SYSLOG printf
#endif

/** @defgroup DEBUG_Exported_Definition_Group1 Basic Definition
 *  @{
 */

#ifndef HAL_SYSLOG
#define HAL_SYSLOG HAL_DBG_Printf
#endif

#if defined(HAL_DBG_ON) && defined(HAL_DBG_INFO_ON)
#define HAL_DBG(fmt, arg...) HAL_SYSLOG("[HAL INFO] " fmt, ##arg)
#else
#define HAL_DBG(fmt, arg...) do { if (0) HAL_SYSLOG("[HAL INFO] " fmt, ##arg); } while (0)
#endif

#if defined(HAL_DBG_ON) && defined(HAL_DBG_WRN_ON)
#define HAL_DBG_WRN(fmt, arg...) HAL_SYSLOG("[HAL WARNING] " fmt, ##arg)
#else
#define HAL_DBG_WRN(fmt, arg...) do { if (0) HAL_SYSLOG("[HAL WARNING] " fmt, ##arg); } while (0)
#endif

#if defined(HAL_DBG_ON) && defined(HAL_DBG_ERR_ON)
#define HAL_DBG_ERR(fmt, arg...) HAL_SYSLOG("[HAL ERROR] " fmt, ##arg)
#else
#define HAL_DBG_ERR(fmt, arg...) do { if (0) HAL_SYSLOG("[HAL ERROR] " fmt, ##arg); } while (0)
#endif

#if defined(HAL_DBG_ON) && defined(HAL_ASSERT_ON)
#define HAL_ASSERT(expr)                                        \
    do {                                                        \
        if (!(expr))                                            \
            HAL_AssertFailed((const char *)__FILE__, __LINE__); \
    } while (0)
#else
#define HAL_ASSERT(expr)
#endif

/***************************** Structure Definition **************************/

/** @} */
/***************************** Function Declare ******************************/
/** @defgroup DEBUG_Public_Function_Declare Public Function Declare
 *  @{
 */

void HAL_AssertFailed(const char *file, uint32_t line);
HAL_Status HAL_DBG_HEX(char *s, void *buf, uint32_t width, uint32_t len);
#ifdef __GNUC__
__attribute__((__format__(printf, 1, 2)))
#endif
int32_t HAL_DBG_Printf(const char *format, ...);

/** @} */

#endif

/** @} */

/** @} */
