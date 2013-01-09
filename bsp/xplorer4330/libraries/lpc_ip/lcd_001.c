/*
 * @brief LCD controller Registers and control functions
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

#include "lcd_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize the LCD controller */
void IP_LCD_Init(IP_LCD_001_Type *LCDx, LCD_Config_Type *LCD_ConfigStruct)
{
	uint32_t i, regValue, *pPal;
	uint32_t pcd;

	/* disable the display */
	LCDx->CTRL &= ~CLCDC_LCDCTRL_ENABLE;

	/* Setting LCD_TIMH register */
	regValue = ( ((((LCD_ConfigStruct->PPL / 16) - 1) & 0x3F) << 2)
				 |         (( (LCD_ConfigStruct->HSW - 1)    & 0xFF) << 8)
				 |         (( (LCD_ConfigStruct->HFP - 1)    & 0xFF) << 16)
				 |         (( (LCD_ConfigStruct->HBP - 1)    & 0xFF) << 24) );
	LCDx->TIMH = regValue;

	/* Setting LCD_TIMV register */
	regValue = ((((LCD_ConfigStruct->LPP - 1) & 0x3FF) << 0)
				|        (((LCD_ConfigStruct->VSW - 1) & 0x03F) << 10)
				|        (((LCD_ConfigStruct->VFP - 1) & 0x0FF) << 16)
				|        (((LCD_ConfigStruct->VBP - 1) & 0x0FF) << 24) );
	LCDx->TIMV = regValue;

	/* Generate the clock and signal polarity control word */
	regValue = 0;
	regValue = (((LCD_ConfigStruct->ACB - 1) & 0x1F) << 6);
	regValue |= (LCD_ConfigStruct->IOE & 1) << 14;
	regValue |= (LCD_ConfigStruct->IPC & 1) << 13;
	regValue |= (LCD_ConfigStruct->IHS & 1) << 12;
	regValue |= (LCD_ConfigStruct->IVS & 1) << 11;

	/* Compute clocks per line based on panel type */
	switch (LCD_ConfigStruct->LCD) {
	case LCD_MONO_4:
		regValue |= ((((LCD_ConfigStruct->PPL / 4) - 1) & 0x3FF) << 16);
		break;

	case LCD_MONO_8:
		regValue |= ((((LCD_ConfigStruct->PPL / 8) - 1) & 0x3FF) << 16);
		break;

	case LCD_CSTN:
		regValue |= (((((LCD_ConfigStruct->PPL * 3) / 8) - 1) & 0x3FF) << 16);
		break;

	case LCD_TFT:
	default:
		regValue |=	 /*1<<26 |*/ (((LCD_ConfigStruct->PPL - 1) & 0x3FF) << 16);
	}

	/* panel clock divisor */
	pcd = 5;// LCD_ConfigStruct->pcd;   // TODO: should be calculated from LCDDCLK
	pcd &= 0x3FF;
	regValue |=  ((pcd >> 5) << 27) | ((pcd) & 0x1F);
	LCDx->POL = regValue;

	/* disable interrupts */
	LCDx->INTMSK = 0;

	/* set bits per pixel */
	regValue = LCD_ConfigStruct->BPP << 1;

	/* set color format RGB */
	regValue |= LCD_ConfigStruct->color_format << 8;
	regValue |= LCD_ConfigStruct->LCD << 4;
	if (LCD_ConfigStruct->Dual == 1) {
		regValue |= 1 << 7;
	}
	LCDx->CTRL = regValue;

	/* clear palette */
	pPal = (uint32_t *) (&(LCDx->PAL));
	for (i = 0; i < 128; i++) {
		*pPal = 0;
		pPal++;
	}
}

/* Power the LCD Panel (power pin) */
void IP_LCD_Power(IP_LCD_001_Type *LCDx, FunctionalState OnOff) {
	volatile int i;
	if (OnOff) {
		LCDx->CTRL |= CLCDC_LCDCTRL_PWR;
		for (i = 0; i < 1000000; i++) {}
		LCDx->CTRL |= CLCDC_LCDCTRL_ENABLE;
	}
	else {
		LCDx->CTRL &= ~CLCDC_LCDCTRL_PWR;
		for (i = 0; i < 1000000; i++) {}
		LCDx->CTRL &= ~CLCDC_LCDCTRL_ENABLE;
	}
}

/* Enable/Disable the LCD Controller */
void IP_LCD_Enable(IP_LCD_001_Type *LCDx, FunctionalState EnDis) {
	if (EnDis) {
		LCDx->CTRL |= CLCDC_LCDCTRL_ENABLE;
	}
	else {
		LCDx->CTRL &= ~CLCDC_LCDCTRL_ENABLE;
	}
}

/* Set LCD Upper Panel Frame Buffer for Single Panel or Upper Panel Frame Buffer for Dual Panel */
void IP_LCD_SetUPFrameBuffer(IP_LCD_001_Type *LCDx, void *buffer) {
	LCDx->UPBASE = (uint32_t) buffer;
}

/* Set LCD Lower Panel Frame Buffer for Dual Panel */
void IP_LCD_SetLPFrameBuffer(IP_LCD_001_Type *LCDx, void *buffer) {
	LCDx->LPBASE = (uint32_t) buffer;
}

/* Configure Cursor */
void IP_LCD_Cursor_Config(IP_LCD_001_Type *LCDx, LCD_CURSOR_SIZE_OPT cursor_size, bool sync) {
	LCDx->CRSR_CFG = ((sync ? 1 : 0) << 1) | cursor_size;
}

/* Get Internal Cursor Image Buffer Address */
void *IP_LCD_Cursor_GetImageBufferAddress(IP_LCD_001_Type *LCDx, uint8_t cursor_num) {
	return (void *) &(LCDx->CRSR_IMG[cursor_num * 64]);
}

/* Enable Cursor */
void IP_LCD_Cursor_Enable(IP_LCD_001_Type *LCDx, uint8_t cursor_num, FunctionalState OnOff) {
	if (OnOff) {
		LCDx->CRSR_CTRL = (cursor_num << 4) | 1;
	}
	else {
		LCDx->CRSR_CTRL = (cursor_num << 4);
	}
}

/* Load Cursor Palette 0 */
void IP_LCD_Cursor_LoadPalette0(IP_LCD_001_Type *LCDx, uint32_t palette_color) {
	/* 7:0 - Red
	   15:8 - Green
	   23:16 - Blue
	   31:24 - Not used*/
	LCDx->CRSR_PAL0 = (uint32_t) palette_color;
}

/* Load Cursor Palette 1 */
void IP_LCD_Cursor_LoadPalette1(IP_LCD_001_Type *LCDx, uint32_t palette_color) {
	/* 7:0 - Red
	   15:8 - Green
	   23:16 - Blue
	   31:24 - Not used*/
	LCDx->CRSR_PAL1 = (uint32_t) palette_color;
}

/* Set Cursor Position */
void IP_LCD_Cursor_SetPos(IP_LCD_001_Type *LCDx, uint16_t x, uint16_t y) {
	LCDx->CRSR_XY = (x & 0x3FF) | ((y & 0x3FF) << 16);
}

/* Set Cursor Clipping Position */
void IP_LCD_Cursor_SetClip(IP_LCD_001_Type *LCDx, uint16_t x, uint16_t y) {
	LCDx->CRSR_CLIP = (x & 0x3F) | ((y & 0x3F) << 8);
}

/* Load Color Palette */
void IP_LCD_Color_LoadPalette(IP_LCD_001_Type *LCDx, uint32_t *palette_addr, uint32_t index) {
	LCDx->PAL[index] = *(uint32_t *) palette_addr;
}
