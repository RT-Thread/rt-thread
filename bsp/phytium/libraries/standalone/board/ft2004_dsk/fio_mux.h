/*
 * @Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * @FilePath: fio_mux.h
 * @Date: 2023-08-01 17:07:54
 * @LastEditTime: 2023-08-01 17:07:55
 * @Description:  This file is for
 *
 * @Modify History:
 *  Ver   Who    Date           Changes
 * ----- ------  --------       --------------------------------------
 * 1.0   liusm   2023/08/01     first release
 */
#ifndef  FIO_MUX_H
#define  FIO_MUX_H

#include "fboard_port.h"
#include "ftypes.h"
#ifdef __cplusplus
extern "C"
{
#endif

void FIOPadSetSpimMux(u32 spim_id);
void FIOPadSetCanMux(u32 can_id);
void FIOPadSetI2cMux(u32 i2c_id);

_WEAK void FIOMuxInit(void);
_WEAK void FIOMuxDeInit(void);
#ifdef __cplusplus
}
#endif

#endif