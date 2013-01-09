/*
 * File      : stm3210e_eval_lcd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-11-01     Bernard      the first version
 */

#include <rtthread.h>

#include "stm32f10x.h"
#include "stm32f10x_fsmc.h"
#include "stm3210e_eval_lcd.h"

#ifdef RT_USING_RTGUI

#include <rtgui/driver.h>
#include <rtgui/color.h>

/*
 * LCD Driver
 * RGB mode (5-6-5)
 * 240 x 320 pixel LCD
 */
/* convert rtgui color to hardware color, rgb 5-6-5 */
typedef struct
{
  rt_uint16_t LCD_REG;
  rt_uint16_t LCD_RAM;
} LCD_TypeDef;

/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define LCD_BASE        ((rt_uint32_t)(0x60000000 | 0x0C000000))
#define LCD             ((LCD_TypeDef *) LCD_BASE)

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteReg(rt_uint8_t LCD_Reg, rt_uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
rt_uint16_t LCD_ReadReg(rt_uint8_t LCD_Reg)
{
  /* Write 16-bit Index (then Read Reg) */
  LCD->LCD_REG = LCD_Reg;
  /* Read 16-bit Reg */
  return (LCD->LCD_RAM);
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
* Description    : Prepare to write to the LCD RAM.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAM_Prepare(void)
{
	LCD->LCD_REG = R34;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM
* Description    : Writes to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
rt_inline void LCD_WriteRAM(rt_uint16_t RGB_Code)
{
	/* Write 16-bit GRAM Reg */
	LCD->LCD_RAM = RGB_Code;
}

/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
*******************************************************************************/
rt_inline rt_uint16_t LCD_ReadRAM(void)
{
	/* Write 16-bit Index (then Read Reg) */
	LCD->LCD_REG = R34; /* Select GRAM Reg */
	/* Read 16-bit Reg */
	return LCD->LCD_RAM;
}

/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{
	/* Display On */
	LCD_WriteReg(0x26, 0x3C); /* 262K color and display ON */
}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{
	/* Display Off */
	LCD_WriteReg(0x26, 0x0);
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(rt_uint32_t x, rt_uint32_t y)
{
	LCD_WriteReg(0x06, (x & 0xff00) >> 8);
	LCD_WriteReg(0x07, (x & 0x00ff));

	LCD_WriteReg(0x02, (y & 0xff00) >> 8);
	LCD_WriteReg(0x03, (y & 0x00ff));
}

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD Control lines (FSMC Pins) in alternate function
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable FSMC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |
		RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG |
		RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//±³¹â
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	//·äÃùÆ÷
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_6);

	/* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
	 PD.10(D15), PD.14(D0), PD.15(D1) as alternate
	 function push pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
	                            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	 PE.14(D11), PE.15(D12) as alternate function push pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                            GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// GPIO_WriteBit(GPIOE, GPIO_Pin_6, Bit_SET);
	/* Set PF.00(A0 (RS)) as alternate function push pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - CE3(LCD /CS) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
* Description    : Configures the Parallel interface (FSMC) for LCD(Parallel mode)
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FSMCConfig(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;

	/*-- FSMC Configuration ------------------------------------------------------*/
	/*----------------------- SRAM Bank 4 ----------------------------------------*/
	/* FSMC_Bank1_NORSRAM4 configuration */
	p.FSMC_AddressSetupTime = 0;
	p.FSMC_AddressHoldTime = 0;
	p.FSMC_DataSetupTime = 2;
	p.FSMC_BusTurnAroundDuration = 0;
	p.FSMC_CLKDivision = 0;
	p.FSMC_DataLatency = 0;
	p.FSMC_AccessMode = FSMC_AccessMode_A;

	/* Color LCD configuration ------------------------------------
	 LCD configured as follow:
	    - Data/Address MUX = Disable
	    - Memory Type = SRAM
	    - Data Width = 16bit
	    - Write Operation = Enable
	    - Extended Mode = Enable
	    - Asynchronous Wait = Disable */
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	// FSMC_NORSRAMInitStructure.FSMC_AsyncWait = FSMC_AsyncWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

	/* BANK 4 (of NOR/SRAM Bank 1~4) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);
}

void rt_hw_lcd_update(rtgui_rect_t *rect)
{
	/* nothing */
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
	return RT_NULL;
}

void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
    unsigned short p;

	/* get color pixel */
	p = rtgui_color_to_565p(*c);

	LCD_SetCursor(y, x);

	/* Prepare to write GRAM */
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(p);
}

void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
	rt_uint16_t hc;

	LCD_SetCursor(y, x);
	hc = LCD_ReadRAM();
	*c = rtgui_color_from_565p(hc);
}

void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint16_t hc;

	hc = rtgui_color_to_565p(*c);

	LCD_SetCursor(y, x1);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

	while (x1 < x2)
	{
		LCD_WriteRAM(hc);
		x1 ++;
	}
}

void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
	rt_uint16_t hc;

	hc = rtgui_color_to_565p(*c);

	while (y1 < y2)
	{
		LCD_SetCursor(y1, x); y1 ++;

		/* Prepare to write GRAM */
		LCD_WriteRAM_Prepare();
		LCD_WriteRAM(hc);
	}
}

void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint16_t *ptr;

	/* get pixel */
	ptr = (rt_uint16_t*) pixels;

	LCD_SetCursor(y, x1);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

	while (x1 < x2)
	{
		LCD_WriteRAM(*ptr);
		x1 ++; ptr ++;
	}
}

struct rtgui_graphic_driver _rtgui_lcd_driver =
{
	"lcd",
	2,
	320,
	240,
	rt_hw_lcd_update,
	rt_hw_lcd_get_framebuffer,
	rt_hw_lcd_set_pixel,
	rt_hw_lcd_get_pixel,
	rt_hw_lcd_draw_hline,
	rt_hw_lcd_draw_vline,
	rt_hw_lcd_draw_raw_hline
};

#define Delay(v)									\
	{												\
		volatile  rt_uint32_t index;				\
		for (index = 0; index < v * 100; index ++)	\
			;										\
	}

void rt_hw_lcd_init()
{
	/* Configure the LCD Control pins --------------------------------------------*/
	LCD_CtrlLinesConfig();

	/* Configure the FSMC Parallel interface -------------------------------------*/
	LCD_FSMCConfig();

	Delay(5); /* delay 50 ms */
	// Gamma for CMO 3.2¡±
	LCD_WriteReg(0x46,0x94);
	LCD_WriteReg(0x47,0x41);
	LCD_WriteReg(0x48,0x00);
	LCD_WriteReg(0x49,0x33);
	LCD_WriteReg(0x4a,0x23);
	LCD_WriteReg(0x4b,0x45);
	LCD_WriteReg(0x4c,0x44);
	LCD_WriteReg(0x4d,0x77);
	LCD_WriteReg(0x4e,0x12);
	LCD_WriteReg(0x4f,0xcc);
	LCD_WriteReg(0x50,0x46);
	LCD_WriteReg(0x51,0x82);

	//240x320 window setting
	LCD_WriteReg(0x02,0x00);
	LCD_WriteReg(0x03,0x00);
	LCD_WriteReg(0x04,0x01);
	LCD_WriteReg(0x05,0x3f);
	LCD_WriteReg(0x06,0x00);
	LCD_WriteReg(0x07,0x00);
	LCD_WriteReg(0x08,0x00);
	LCD_WriteReg(0x09,0xef);

	// Display Setting
	LCD_WriteReg(0x01,0x06);
	LCD_WriteReg(0x16,0x68);
	LCD_WriteReg(0x23,0x95);
	LCD_WriteReg(0x24,0x95);
	LCD_WriteReg(0x25,0xff);

	LCD_WriteReg(0x27,0x02);
	LCD_WriteReg(0x28,0x02);
	LCD_WriteReg(0x29,0x02);
	LCD_WriteReg(0x2a,0x02);
	LCD_WriteReg(0x2c,0x02);
	LCD_WriteReg(0x2d,0x02);

	LCD_WriteReg(0x3a,0x01);///*******************
	LCD_WriteReg(0x3b,0x01);
	LCD_WriteReg(0x3c,0xf0);
	LCD_WriteReg(0x3d,0x00);

	Delay(2);

	LCD_WriteReg(0x35,0x38);
	LCD_WriteReg(0x36,0x78);

	LCD_WriteReg(0x3e,0x38);

	LCD_WriteReg(0x40,0x0f);
	LCD_WriteReg(0x41,0xf0);

	// Power Supply Setting
	LCD_WriteReg(0x19,0x49);//********
	LCD_WriteReg(0x93,0x0f);//*******

	Delay(1);

	LCD_WriteReg(0x20,0x30);
	LCD_WriteReg(0x1d,0x07);
	LCD_WriteReg(0x1e,0x00);
	LCD_WriteReg(0x1f,0x07);

	// VCOM Setting for CMO 3.2¡± Panel
	LCD_WriteReg(0x44,0x4d);//4d***************4f
	LCD_WriteReg(0x45,0x13);//0x0a);
	Delay(1);
	LCD_WriteReg(0x1c,0x04);
	Delay(2);
	LCD_WriteReg(0x43,0x80);
	Delay(5);
	LCD_WriteReg(0x1b,0x08);
	Delay(4);
	LCD_WriteReg(0x1b,0x10);
	Delay(4);

	// Display ON Setting
	LCD_WriteReg(0x90,0x7f);
	LCD_WriteReg(0x26,0x04);
	Delay(4);
	LCD_WriteReg(0x26,0x24);
	LCD_WriteReg(0x26,0x2c);
	Delay(4);
	LCD_WriteReg(0x26,0x3c);

	// Set internal VDDD voltage
	LCD_WriteReg(0x57,0x02);
	LCD_WriteReg(0x55,0x00);
	LCD_WriteReg(0x57,0x00);

	/* add lcd driver into graphic driver */
	rtgui_list_init(&_rtgui_lcd_driver.list);
	rtgui_graphic_driver_add(&_rtgui_lcd_driver);
}

#endif

void stm3210e_rtgui_init()
{
	rtgui_rect_t rect;

	rtgui_system_server_init();

	/* register dock panel */
	rect.x1 = 0;
	rect.y1 = 0;
	rect.x2 = 320;
	rect.y2 = 25;
	rtgui_panel_register("info", &rect);

	/* register main panel */
	rect.x1 = 0;
	rect.y1 = 25;
	rect.x2 = 320;
	rect.y2 = 240;
	rtgui_panel_register("main", &rect);
	rtgui_panel_set_default_focused("main");

	rt_hw_lcd_init();

	info_init();
	today_init();
}
