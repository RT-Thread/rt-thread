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
 * Description:  This file is for providing some hardware register and function definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */

#ifndef FDC_HW_H
#define FDC_HW_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "ferror_code.h"
#include "fkernel.h"

/**************************** Type Definitions *******************************/

#define FDC_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))
#define FDC_WRITE_REG32(addr, reg_value) FtOut32(addr, (u32)(reg_value))
#define FDC_PHY_ALIGN(data, Offset) ((data + Offset - 1) & ~(Offset - 1))

/************************** Constant Definitions *****************************/

/*
AHB Byte Address
DC Ctrl Register*/
#define FDC_AQ_HI_CLOCK_CONTROL 0x0000
#define FDC_AQ_HI_IDLE 0x0004
#define FDC_AQ_AXI_STATUS 0x000C
#define FDC_AQ_INTR_ENBL 0x0014
#define FDC_AQ_INTR_ACKNOWLEDGE 0x0010
#define FDC_GC_TOTAL_READS 0x0040
#define FDC_GC_TOTAL_CYCLES 0x0078
#define FDC_CTRL_CH0_PIXEL_CLOCK 0x00F0
#define FDC_CTRL_CH1_PIXEL_CLOCK 0x00F4

/* Each Dc Core Register */
#define FDC_GCREG_FRAMEBUFFERADDR_LOW 0x400
#define FDC_GCREG_FRAMEBUFFERADDR_HIGH 0x404
#define FDC_GCREG_FRAMEBUFFERSTRIDE0 0x408
#define FDC_GCREG_DISPLAYDITHERCONFIG0 0x410
#define FDC_GCREG_PANEL_CONFIG0 0x418
#define FDC_GCREG_DISPLAY_DITHERTABLELOW0 0x420
#define FDC_GCREG_DISPLAY_DITHERTABLEHIGH0 0x428
#define FDC_GCREG_HDISPLAY0 0x430
#define FDC_GCREG_HSYNC0 0x438
#define FDC_GCREG_VDISPLAY0 0x440
#define FDC_GCREG_VSYNC0 0x448
#define FDC_GCREG_DISPLAY_CURLOCATION0 0x450
#define FDC_GCREG_GAMMAINDEX0 0x458
#define FDC_GCREG_GAMMADATA0 0x460
#define FDC_GCREG_CURSOR_CONFIG 0x468
#define FDC_GCREG_CURSOR_ADDR_LOW 0x46C
#define FDC_GCREG_CURSOR_ADDR_HIGH 0x490
#define FDC_GCREG_CURSOR_LOCATION 0x470
#define FDC_GCREG_CURSOR_BACKGROUND 0x474
#define FDC_GCREG_CURSOR_FORGEGROUND 0x478
#define FDC_GCREG_DISPLAY_INTR 0x47C
#define FDC_GCREG_DISPLAY_INTR_ENABLE 0x480
#define FDC_GCREG_CURSOR_MODCLKGATECONTROL 0x484
#define FDC_GCREG_DEBUGCOUNTER_SELECT0 0x4D0
#define FDC_GCREG_DEBUGCOUNTER_VALUE0 0x4D8
#define FDC_GCREG_FRAMEBUFFER_COLORKEY0 0x508
#define FDC_GCREG_FRAMEBUFFER_COLORKEYHIGH0 0x510
#define FDC_GCREG_FRAMEBUFFER_CONFIG0 0x518
#define FDC_GCREG_FRAMEBUFFER_SCALECONFIG0 0x520
#define FDC_GCREG_FRAMEBUFFER_BGCOLOR0 0x528
#define FDC_GCREG_FRAMEBUFFER_UPPLANARADDR_LOW 0x530
#define FDC_GCREG_FRAMEBUFFER_UPPLANARADDR_HIGH 0x534
#define FDC_GCREG_FRAMEBUFFER_VPPLANARADDR_LOW 0x538
#define FDC_GCREG_FRAMEBUFFER_VPPLANARADDR_HIGH 0x53C
#define FDC_GCREG_FRAMEBUFFER_USTRIDE0 0x800
#define FDC_GCREG_FRAMEBUFFER_VSTRIDE0 0x808
#define FDC_GCREG_FRAMEBUFFER_SIZE0 0x810
#define FDC_GCREG_FRAMEBUFFER_SCALEFACTORX0 0x828
#define FDC_GCREG_FRAMEBUFFER_SCALEFACTORY0 0x830
#define FDC_GCREG_HORIFILTERKERNEL_INDEX0 0x838
#define FDC_GCREG_HORI_FILTERKERNEL0 0xA00
#define FDC_GCREG_VERTI_FILTERKERNEL_INDEX0 0xA08
#define FDC_GCREG_VERTI_FILTERKERNEL0 0xA10
#define FDC_GCREG_FRAMEBUFFER_CLEARVALUE0 0xA18
#define FDC_GCREG_FRAMEBUFFER_INITOFFSET0 0xA20
#define FDC_GCREG_MODCLKGATE_CONTROL0 0xA28
#define FDC_GCREG_READ_OT 0xCC8
#define FDC_GCREG_DPCONFIG0 0xCD0

/* FDC_GCREG_FRAMEBUFFER_SIZE0 */
#define FDC_GCREG_FRAMEBUFFER_SIZE0_HEIGHT_SET(x) SET_REG32_BITS((x), 29, 15) /* the height of window size of the framebuffer in memory - in pixels*/
#define FDC_GCREG_FRAMEBUFFER_SIZE0_WIDTH_SET(x) SET_REG32_BITS((x), 14, 0)   /* the width of window size of the framebuffer in memory -in pixels*/
/* FDC_GCREG_FRAMEBUFFER_SCALECONFIG0 */
#define FDC_GCREG_FRAMEBUFFER_SCALECONFIG0_H_FILTER_TAP_SET(x) SET_REG32_BITS((x), 7, 4) /* the number of horizontal filter tap*/
#define FDC_GCREG_FRAMEBUFFER_SCALECONFIG0_V_FILTER_TAP_SET(x) SET_REG32_BITS((x), 3, 0) /* the number of vertial filter tap*/
/* FDC_GCREG_FRAMEBUFFER_INITOFFSET0 */
#define FDC_GCREG_FRAMEBUFFER_INITOFFSET0_Y_SET(x) SET_REG32_BITS((x), 31, 16) /* Y location of the framebuffer scalar source offset register */
#define FDC_GCREG_FRAMEBUFFER_INITOFFSET0_X_SET(x) SET_REG32_BITS((x), 15, 0)  /* X  location of the framebuffer scalar source offset register */

/* FDC_GCREG_FRAMEBUFFER_CONFIG0 */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_FORMAT_SET(x) SET_REG32_BITS((x), 31, 26)      /* framebuffer configuration register  can see the struct in the VIDEO_FORMAT*/
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_UV_SWIZZLE BIT(25)                             /* UV swizzle */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_SWIZZLE_SET(x) SET_REG32_BITS((x), 24, 23)     /* swizzle mode ,0:ARGB, 1:RGBA, 2:ABGR, 3:BGRA */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_SCALE BIT(22)                                  /* scale of config, 0:disable, 1:enable */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_TILE_MODE_SET(x) SET_REG32_BITS((x), 21, 17)   /* set the tilemode */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_YUV_SET(x) SET_REG32_BITS((x), 16, 14)         /* yuv standard, 1: 709*bt709, 3:2020*bt2020*/
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_ROT_ANGLE_SET(x) SET_REG32_BITS((x), 13, 11)   /* the angle of the rot, 0:roto, 1:flip_x, 2:flip_y, 3:flip_xy, 5:rot180 */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_TRANSPARENCY_SET(x) SET_REG32_BITS((x), 10, 9) /* transparency of framebuffer */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_CLEAR BIT(8)                                   /* the source of the pixel value ,enable :from dcregframebufferclear value,disable: from memory */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_FLIP_PROGRESS BIT(6)                           /* 0:NO, 1:YES, related to the framebuffer address and the vblank */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_UNDERFLOW BIT(5)                               /* 0:NO, 1:YES, related to the display fifo underflows */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_RESET BIT(4)                                   /*  enable reset for the display controller */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_VALID BIT(3)                                   /* decided if you can copy a set of registers ar the next vblank */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_GAMMA BIT(2)                                   /* gamma is enabled,rgb channel will be routed */
#define FDC_GCREG_FRAMEBUFFER_CONFIG0_OUTPUT BIT(0)                                  /* output is enabled ,pixels will be displayed */

/* FDC_GCREG_CURSOR_CONFIG */
#define FDC_GCREG_CURSOR_CONFIG_HOT_SPOT_X_SET(x) SET_REG32_BITS((x), 20, 16) /* horizontal offset to the cursor hotspot */
#define FDC_GCREG_CURSOR_CONFIG_HOT_SPOT_Y_SET(x) SET_REG32_BITS((x), 12, 8)  /* vertical offset to the cursor hotspot */
#define FDC_GCREG_CURSOR_CONFIG_HOT_FORMAT_SET(x) SET_REG32_BITS((x), 1, 0)   /* format of the cursor,0: disabled, 1:masked, 2:ARGB888   \
                                                                                                                                       \ \
/* FDC_GCREG_CURSOR_LOCATION */
#define FDC_GCREG_CURSOR_LOCATION_Y_SET(x) SET_REG32_BITS((x), 31, 16)        /* Y location of cursor hotspot */
#define FDC_GCREG_CURSOR_LOCATION_X_SET(x) SET_REG32_BITS((x), 15, 0)         /* X location of cursor hotspot */

/* FDC_GCREG_HSYNC0 */
#define FDC_GCREG_HSYNC0_POLARITY BIT(31)                        /* polarity of the horizontal sync pulse */
#define FDC_GCREG_HSYNC0_PULSE BIT(30)                           /* horizontal sync pulse control */
#define FDC_GCREG_HSYNC0_END_SET(x) SET_REG32_BITS((x), 29, 15)  /* end of horizontal sync pulse */
#define FDC_GCREG_HSYNC0_START_SET(x) SET_REG32_BITS((x), 14, 0) /* start of the horizontal sync pulse */

/* FDC_GCREG_VSYNC0 */
#define FDC_GCREG_VSYNC0_POLARITY BIT(31)                        /* polarity of the vertical sync pulse */
#define FDC_GCREG_VSYNC0_PULSE BIT(30)                           /* vertical sync pulse control */
#define FDC_GCREG_VSYNC0_END_SET(x) SET_REG32_BITS((x), 29, 15)  /* end of vertical sync pulse */
#define FDC_GCREG_VSYNC0_START_SET(x) SET_REG32_BITS((x), 14, 0) /* start of the vertical sync pulse */

/* FDC_GCREG_VDISPLAY */
#define FDC_GCREG_VDISPLAY_TOTAL_SET(x) SET_REG32_BITS((x), 30, 16)      /* total number of vertical pixels */
#define FDC_GCREG_VDISPLAY_DISPLAY_END_SET(x) SET_REG32_BITS((x), 14, 0) /* visible number of vertical pixels */

/* FDC_GCREG_HDISPLAY0 */
#define FDC_GCREG_HDISPLAY0_TOTAL_SET(x) SET_REG32_BITS((x), 30, 16)      /* total number of horizontal pixels */
#define FDC_GCREG_HDISPLAY0_DISPLAY_END_SET(x) SET_REG32_BITS((x), 14, 0) /* visible number of vertical pixels */

/* FDC_GCREG_PANEL_CONFIG0 */
#define FDC_GCREG_PANEL_CONFIG0_DATA_CLOCK_POLATITY BIT(9) /* data clock polarity*/
#define FDC_GCREG_PANEL_CONFIG0_DATA_CLOCK_ENABLE BIT(8)   /* data enable enable */
#define FDC_GCREG_PANEL_CONFIG0_DATA_POLARITY BIT(5)       /* data enable polarity */
#define FDC_GCREG_PANEL_CONFIG0_DATA_ENABLE BIT(4)         /* data enable  */
#define FDC_GCREG_PANEL_CONFIG0_DATA_DE_POLATITY BIT(1)    /* data enable polarity */
#define FDC_GCREG_PANEL_CONFIG0_DATA_DE BIT(0)             /* data enable  enabled/disabled */

/* FDC_GCREG_DISPLAYDITHERCONFIG0 */
#define FDC_GCREG_DISPLAYDITHERCONFIG0_ENABLE BIT(31)

/* FDC_GCREG_GAMMAINDEX0 */
#define FDC_GCREG_GAMMAINDEX0_INDEX_SET(x) SET_REG32_BITS((x), 7, 0) /*gamma table index register ,index into gamma table */

/* FDC_GCREG_GAMMADATA0 */
#define FDC_GCREG_GAMMADATA0_RED_SET(x) SET_REG32_BITS((x), 29, 20)   /* red translation value */
#define FDC_GCREG_GAMMADATA0_GREEN_SET(x) SET_REG32_BITS((x), 19, 10) /* green translation value */
#define FDC_GCREG_GAMMADATA0_BLUE_SET(x) SET_REG32_BITS((x), 9, 0)    /* blue translation value */

/*FDC_GCREG_DISPLAY_INTR_ENABLE */
#define FDC_GCREG_DISPLAY_INTR_ENABLE_DC1_UNDERFLOW BIT(5) /* dc1 underflow interrupt enable */
#define FDC_GCREG_DISPLAY_INTR_ENABLE_DC1_INTR BIT(4)      /* dc1 frame complete interrupt enable */
#define FDC_GCREG_DISPLAY_INTR_ENABLE_DC0_UNDERFLOW BIT(1) /* dc0 underflow interrupt enable */
#define FDC_GCREG_DISPLAY_INTR_ENABLE_DC0_INTR BIT(0)      /* dc0 frame complete interrupt enable */

/**************************************************************************************/

/* write the data to the channel of DcDp */
void FDcChannelRegWrite(uintptr addr, uintptr offset, u32 data);

/* read the data from the channel of DcDp */
FError FDcChannelRegRead(uintptr addr, uintptr offset);

/* write Dc control register */
void FDcCtrlRegWrite(uintptr addr, uintptr offset, u32 data);

/* read Dc control register */
FError FDcCtrlRegRead(uintptr addr, uintptr offset);

#endif