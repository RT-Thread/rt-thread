/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fdrivers_port.h
 * Created Date: 2023-10-16 17:02:35
 * Last Modified: Tue Feb 20 2024
 * Description:  This file is for drive layer code decoupling
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 *  1.0     huanghe    2023/10/17    first release
 */

#ifndef FDRIVERS_PORT_H
#define FDRIVERS_PORT_H

#include <rtthread.h>
/***************************** Include Files *********************************/
#include "rtconfig.h"
#include "ftypes.h"
#include "drv_log.h"
#include "fkernel.h"
#include "faarch.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* cache */
void FDriverDCacheRangeFlush(uintptr_t adr, size_t len);

void FDriverDCacheRangeInvalidate(uintptr_t adr, size_t len);

void FDriverICacheRangeInvalidate(uintptr_t adr, size_t len);


/* memory barrier */

#define FDRIVER_DSB() DSB()

#define FDRIVER_DMB() DMB()

#define FDRIVER_ISB() ISB()

/* time delay */

void FDriverUdelay(u32 usec);

void FDriverMdelay(u32 msec);

void FDriverSdelay(u32 sec);

#if (DBG_LEVEL >= DBG_WARNING)
#define FT_DEBUG_PRINT_W(TAG, format, ...) LOG_W(format, ##__VA_ARGS__)
#else
#define FT_DEBUG_PRINT_W(TAG, format, ...) LOG_W(...)
#endif

#if (DBG_LEVEL >= DBG_INFO)
#define FT_DEBUG_PRINT_I(TAG, format, ...) LOG_I(format, ##__VA_ARGS__)
#else
#define FT_DEBUG_PRINT_I(TAG, format, ...) LOG_I(...)
#endif

#if (DBG_LEVEL >= DBG_ERROR)
#define FT_DEBUG_PRINT_E(TAG, format, ...) LOG_E(format, ##__VA_ARGS__)
#else
#define FT_DEBUG_PRINT_E(TAG, format, ...) LOG_E(...)
#endif

#if (DBG_LEVEL >= DBG_LOG)
#define FT_DEBUG_PRINT_D(TAG, format, ...) LOG_D(format, ##__VA_ARGS__)
#else
#define FT_DEBUG_PRINT_D(TAG, format, ...) LOG_D(...)
#endif


#ifdef __cplusplus
}
#endif


#endif
