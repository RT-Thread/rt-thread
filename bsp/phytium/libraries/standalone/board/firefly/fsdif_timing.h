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
 * @FilePath: fsdif_timing.c
 * @Date: 2023-07-25 11:29:44
 * @LastEditTime: 2023-07-25 11:29:44
 * @Description:  This file is for sdif timing function definition
 *
 * @Modify History:
 *  Ver   Who       Date       Changes
 * ----- ------  --------      --------------------------------------
 * 1.0   zhugengyu  2023/9/25   init commit
 *
 */

#ifndef  FSDIF_TIMING_H
#define  FSDIF_TIMING_H

#include "fboard_port.h"
#include "ftypes.h"
#include "fsdif.h"

#ifdef __cplusplus
extern "C"
{
#endif

void FSdifTimingInit(void);
void FSdifTimingDeinit(void);

/* register this function in FSDIF driver to set timing */
const FSdifTiming *FSdifGetTimingSetting(FSdifClkSpeed clock_freq, boolean non_removable);

#ifdef __cplusplus
}
#endif

#endif

