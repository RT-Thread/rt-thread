/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fdcdp_multi_display.h
 * Date: 2023-02-05 18:27:47
 * LastEditTime: 2023-02-10 11:02:47
 * Description:  This file is for defining the dp multidisplay config
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2023/02/10  Modify the format and establish the version
 */

#ifndef FDCDP_MULTI_DISPLAY_H
#define FDCDP_MULTI_DISPLAY_H

#include "ftypes.h"
#include "fparameters.h"

typedef struct
{
    uintptr dp0_framebuffer;/* data */
    uintptr dp1_framebuffer;
    u32     multi_mode;
} FDcDpFrameBuffer;

/*set the frambbuffer of multidisplay*/
FError FDcDpMultiDisplayFrameBufferSet(FDcDp *instance_p, u32 channel_num, u32 multi_mode);

/*return the framebuffer*/
FDcDpFrameBuffer *FDcDpGetFramebuffer(FDcDp *instance_p);

#endif