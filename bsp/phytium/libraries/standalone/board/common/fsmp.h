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
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef BSP_BOARD_COMMON_SMP_H
#define BSP_BOARD_COMMON_SMP_H

#include "ftypes.h"

void SpinLockInit(unsigned long  global_addr);
void SpinLock(void);
void SpinUnlock(void);

#endif // DEBUG