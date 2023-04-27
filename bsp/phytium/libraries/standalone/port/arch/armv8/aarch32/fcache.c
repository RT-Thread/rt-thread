/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fcache.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:36:17
 * Description:  This file is for aarch32 cache functions port for driver
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/2/28   first release
 */

/***************************** Include Files *********************************/
#include <cp15.h>
#include "fassert.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
extern void rt_hw_cpu_dcache_invalidate(void *addr, int size);
extern void rt_hw_cpu_dcache_clean(void *addr, int size);

/************************** Function *****************************************/
void FCacheDCacheInvalidate(void)
{
    /* there is no dcache invalidate implmentation for contrex-a aarch32, use flush instead */
    rt_cpu_dcache_clean_flush();
}

void FCacheDCacheInvalidateRange(intptr adr, intptr len)
{
    rt_hw_cpu_dcache_invalidate((void *)adr, (int)len);
}

void FCacheDCacheFlushRange(intptr adr, intptr len)
{
    rt_hw_cpu_dcache_clean((void *)adr, (int)len);
}