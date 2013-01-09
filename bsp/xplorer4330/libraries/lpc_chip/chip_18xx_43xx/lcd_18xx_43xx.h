/*
 * @brief LPC18xx/43xx LCD chip driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __LCD_18XX_43XX_H_
#define __LCD_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup LCD_18XX_43XX CHIP: LPC18xx/43xx LCD driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Initialize the LCD controller
 * @param	LCD_ConfigStruct	: Pointer to LCD configuration
 * @return  LCD_FUNC_OK is executed successfully or LCD_FUNC_ERR on error
 */
STATIC INLINE void Chip_LCD_Init(LCD_Config_Type *LCD_ConfigStruct)
{
	IP_LCD_Init(LPC_LCD, LCD_ConfigStruct);
}

/**
 * @brief	Power the LCD Panel (power pin)
 * @param	OnOff	: true to power on, false to power off
 * @return	None
 */
STATIC INLINE void Chip_LCD_Power(FunctionalState OnOff)
{
	IP_LCD_Power(LPC_LCD, OnOff);
}

/**
 * @brief	Enable/Disable the LCD Controller
 * @param	EnDis	: true to enable, false to disable
 * @return	None
 */
STATIC INLINE void Chip_LCD_Enable(FunctionalState EnDis)
{
	IP_LCD_Enable(LPC_LCD, EnDis);
}

/**
 * @brief	Set LCD Upper Panel Frame Buffer for Single Panel or Upper Panel Frame
 *			Buffer for Dual Panel
 * @param	buffer	: address of buffer
 * @return	None
 */
STATIC INLINE void Chip_LCD_SetUPFrameBuffer(void *buffer)
{
	IP_LCD_SetUPFrameBuffer(LPC_LCD, buffer);
}

/**
 * @brief	Set LCD Lower Panel Frame Buffer for Dual Panel
 * @param	buffer	: address of buffer
 * @return	None
 */
STATIC INLINE void Chip_LCD_SetLPFrameBuffer(void *buffer)
{
	IP_LCD_SetLPFrameBuffer(LPC_LCD, buffer);
}

/**
 * @brief	Configure Cursor
 * @param	cursor_size	: specify size of cursor
 *                  - LCD_CURSOR_32x32	:cursor size is 32x32 pixels
 *                  - LCD_CURSOR_64x64	:cursor size is 64x64 pixels
 * @param	sync		: cursor sync mode
 *                  - TRUE	:cursor sync to the frame sync pulse
 *                  - FALSE	:cursor async mode
 * @return	None
 */
void Chip_LCD_Cursor_Config(LCD_CURSOR_SIZE_OPT cursor_size, bool sync);

/**
 * @brief	Enable Cursor
 * @param	cursor_num	: specify number of cursor is going to be written
 *							this param must < 4
 * @param	OnOff		: true to turn on LCD, false to turn off
 * @return	None
 */
STATIC INLINE void Chip_LCD_Cursor_Enable(uint8_t cursor_num, FunctionalState OnOff)
{
	IP_LCD_Cursor_Enable(LPC_LCD, cursor_num, OnOff);
}

/**
 * @brief	Load Cursor Palette
 * @param	palette_color	: cursor palette 0 value
 * @return	None
 */
STATIC INLINE void Chip_LCD_Cursor_LoadPalette0(uint32_t palette_color)
{
	IP_LCD_Cursor_LoadPalette0(LPC_LCD, palette_color);
}

/**
 * @brief	Load Cursor Palette
 * @param	palette_color	: cursor palette 1 value
 * @return	None
 */
STATIC INLINE void Chip_LCD_Cursor_LoadPalette1(uint32_t palette_color)
{
	IP_LCD_Cursor_LoadPalette1(LPC_LCD, palette_color);
}

/**
 * @brief	Set Cursor Position
 * @param	x	: horizontal position
 * @param	y	: vertical position
 * @return	None
 */
STATIC INLINE void Chip_LCD_Cursor_SetPos(uint16_t x, uint16_t y)
{
	IP_LCD_Cursor_SetPos(LPC_LCD, x, y);
}

/**
 * @brief	Set Cursor Clipping Position
 * @param	x	: horizontal position, should be in range: 0..63
 * @param	y	: vertical position, should be in range: 0..63
 * @return	None
 */
STATIC INLINE void Chip_LCD_Cursor_SetClip(uint16_t x, uint16_t y)
{
	IP_LCD_Cursor_SetClip(LPC_LCD, x, y);
}

/**
 * @brief	Enable Controller Interrupt
 * @param	ints	: OR'ed interrupt bits to enable
 * @return	None
 */
STATIC INLINE void Chip_LCD_EnableInts(uint32_t ints)
{
	IP_LCD_EnableInts(LPC_LCD, ints);
}

/**
 * @brief	Disable Controller Interrupt
 * @param	ints	: OR'ed interrupt bits to disable
 * @return	None
 */
STATIC INLINE void Chip_LCD_DisableInts(uint32_t ints)
{
	IP_LCD_DisableInts(LPC_LCD, ints);
}

/**
 * @brief	Clear Controller Interrupt
 * @param	ints	: OR'ed interrupt bits to clear
 * @return	None
 */
STATIC INLINE void Chip_LCD_ClearInts(uint32_t ints)
{
	IP_LCD_ClearInts(LPC_LCD, ints);
}

/**
 * @brief	Write Cursor Image into Internal Cursor Image Buffer
 * @param	cursor_num	: Cursor index
 * @param	Image		: Pointer to image data
 * @return	None
 */
void Chip_LCD_Cursor_WriteImage(uint8_t cursor_num, void *Image);

/**
 * @brief	Load LCD Palette
 * @param	palette	: Address of palette table to load
 * @return	None
 */
void Chip_LCD_LoadPalette(void *palette);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __LCD_18XX_43XX_H_ */
