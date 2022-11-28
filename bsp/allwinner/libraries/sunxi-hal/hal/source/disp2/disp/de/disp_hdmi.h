/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __DISP_HDMI_H__
#define __DISP_HDMI_H__

#include "disp_private.h"

#define HDMI1440_480I 6
#define HDMI1440_576I 21
#define HDMI480P 2
#define HDMI576P 17
#define HDMI720P_50 19
#define HDMI720P_60 4
#define HDMI1080I_50 20
#define HDMI1080I_60 5
#define HDMI1080P_50 31
#define HDMI1080P_60 16
#define HDMI1080P_24 32
#define HDMI1080P_25 33
#define HDMI1080P_30 34
#define HDMI1080P_24_3D_FP (HDMI1080P_24 + 0x80)
#define HDMI720P_50_3D_FP (HDMI720P_50 + 0x80)
#define HDMI720P_60_3D_FP (HDMI720P_60 + 0x80)
#define HDMI3840_2160P_30 (0x01 + 0x100)
#define HDMI3840_2160P_25 (0x02 + 0x100)
#define HDMI3840_2160P_24 (0x03 + 0x100)
#define HDMI4096_2160P_24 (0x04 + 0x100)

s32 disp_init_hdmi(struct disp_bsp_init_para *para);

struct disp_device *disp_get_hdmi(u32 disp);

#endif
