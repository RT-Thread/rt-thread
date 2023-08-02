/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fsmp.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-17 17:58:18
 * Description:  This file is for spinlock function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0   carl       2023-02-28   Use GCC built-in functions to implement spinlock
 */


#ifndef BSP_BOARD_COMMON_SMP_H
#define BSP_BOARD_COMMON_SMP_H

#include "ftypes.h"


#ifdef __cplusplus
extern "C"
{
#endif

void SpinInit(void);
void SpinLock(void);
void SpinUnlock(void);

#ifdef __cplusplus
}
#endif


#endif // DEBUG