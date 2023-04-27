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
 * FilePath: fdc_hw.h
 * Date: 2022-09-10 14:53:42
 * LastEditTime: 2022-09-18 08:29:10
 * Description:  This file is for Handling the hardware register and
 *               providing some function interface
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */
#ifndef FDC_COMMON_HW_H
#define FDC_COMMON_HW_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "ferror_code.h"
#include "fdc.h"

/*set pixel clock in kilohertz unit by configurating register */
FError FDcReqChangePixel(FDcCtrl *instance_p, u32 pixel_clk);

/* soft reset DC by configurating register */
void FDcHwFramebufferReset(FDcCtrl *instance_p, u32 num, FDcRestType type);

/* Get mode number by width and height */
FError FDcResToModeNum(u32 width, u32 height);
#endif
