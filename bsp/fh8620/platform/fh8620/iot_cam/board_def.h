/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef BOARD_DEF_H_
#define BOARD_DEF_H_


/* ***********************
 * SECTION:	DRIVE
 * ***********************/
// Basic drive..
#define RT_USING_UART1
#define RT_USING_GPIO
#define RT_USING_SDIO
#define RT_USING_FH_DMA
#define RT_USING_FH_ACW
#define RT_USING_I2C
#define RT_USING_PWM
#define RT_USING_WDT
#define RT_USING_SPI
#define RT_USING_SADC

#define RT_USING_DSP
#define RT_USING_ISP

#define CONFIG_PLAT_V2

#ifndef FH_DDR_START
#define	FH_DDR_START		0xA0000000
#define FH_DDR_END		0xA1000000

#define FH_RTT_OS_MEM_SIZE	0x00600000
#define FH_DMA_MEM_SIZE		0x20000 /* 128k */

#define FH_RTT_OS_MEM_END	(FH_DDR_START + FH_RTT_OS_MEM_SIZE)
#define FH_SDK_MEM_START	(FH_RTT_OS_MEM_END + FH_DMA_MEM_SIZE)
#define FH_RTT_OS_HEAP_END	FH_SDK_MEM_START
#define FH_SDK_MEM_SIZE		(FH_DDR_END - FH_SDK_MEM_START)
#endif /* end of FH_DDR_START*/
 
/* ***********************
 * SECTION:	DRIVE COMPONENT
 * ***********************/
#define UART_NAME 						"uart1"
#define RT_USING_DMA_MEM

#define RT_USING_MCI0
#define RT_USING_GD
#define RT_USING_FLASH_DEFAULT
#define RT_USING_FH_FLASH_ADAPT


#ifndef _FH_AUTO_CONFIG_
#define CHANNUM 2
#define CHN0_Height 720
#define CHN0_WIDTH 1280
#define CHN0_Framerate 0x00010019
#define CHN0_Bitrate (2048 *4)


#define CHN1_Framerate 0x00010019
#define CHN1_WIDTH 352
#define CHN1_Height 288
#define CHN1_Bitrate 512


#define VPU_FRAME_CTRL 1
#define CONFIG_IRCUT_OFF 1
#define CONFIG_ISP_25FPS 1
#define NOT_RECORD 1
#define ENABLE_JPEG 1
#define CONFIG_ISP_720P 1
#define ENABLE_COOLVIEW 1
#define ENABLE_OSD 1
#define USE_RC 1
#define OSD_CHN_FONT_USING 1
#endif





#endif /* BOARD_H_ */
