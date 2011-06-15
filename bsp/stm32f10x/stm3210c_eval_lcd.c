/*
 * File      : stm3210c_eval_lcd.c
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
#include "stm3210c_eval_lcd.h"
#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_server.h>

#define START_BYTE      0x70
#define SET_INDEX       0x00
#define READ_STATUS     0x01
#define LCD_WRITE_REG   0x02
#define LCD_READ_REG    0x03

void rt_hw_lcd_update(rtgui_rect_t *rect);
rt_uint8_t * rt_hw_lcd_get_framebuffer(void);
void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y);
void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y);
void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y);
void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2);
void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y);

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

static void _delay_(__IO uint32_t nCount)
{
	__IO uint32_t index = 0;
	for(index = (100000 * nCount); index != 0; index--)
	{}
}

/**
  * @brief  Sets or reset LCD control lines.
  * @param  GPIOx: where x can be B or D to select the GPIO peripheral.
  * @param  CtrlPins: the Control line. This parameter can be:
  *     @arg LCD_NCS_PIN: Chip Select pin
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void LCD_CtrlLinesWrite(GPIO_TypeDef* GPIOx, uint16_t CtrlPins, BitAction BitVal)
{
	/* Set or Reset the control line */
	GPIO_WriteBit(GPIOx, CtrlPins, BitVal);
}

/**
  * @brief  Reset LCD control line(/CS) and Send Start-Byte
  * @param  Start_Byte: the Start-Byte to be sent
  * @retval None
  */
void LCD_nCS_StartByte(uint8_t Start_Byte)
{
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_RESET);
	SPI_I2S_SendData(LCD_SPI, Start_Byte);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
}

/**
  * @brief  Configures LCD control lines in Output Push-Pull mode.
  * @param  None
  * @retval None
  */
void LCD_CtrlLinesConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(LCD_NCS_GPIO_CLK, ENABLE);

	/* Configure NCS in Output Push-Pull mode */
	GPIO_InitStructure.GPIO_Pin = LCD_NCS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_NCS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Writes index to select the LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void LCD_WriteRegIndex(uint8_t LCD_Reg)
{
	/* Reset LCD control line(/CS) and Send Start-Byte */
	LCD_nCS_StartByte(START_BYTE | SET_INDEX);
	/* Write 16-bit Reg Index (High Byte is 0) */
	SPI_I2S_SendData(LCD_SPI, 0x00);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	SPI_I2S_SendData(LCD_SPI, LCD_Reg);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  None
  * @retval LCD Register Value.
  */
uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
	uint16_t tmp = 0;
	uint8_t i = 0;

	/* LCD_SPI prescaler: 4 */
	LCD_SPI->CR1 &= 0xFFC7;
	LCD_SPI->CR1 |= 0x0008;
	/* Write 16-bit Index (then Read Reg) */
	LCD_WriteRegIndex(LCD_Reg);
	/* Read 16-bit Reg */
	/* Reset LCD control line(/CS) and Send Start-Byte */
	LCD_nCS_StartByte(START_BYTE | LCD_READ_REG);

	for(i = 0; i < 5; i++)
	{
		SPI_I2S_SendData(LCD_SPI, 0xFF);
		while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
		{}
		/* One byte of invalid dummy data read after the start byte */
		while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
		{}
		SPI_I2S_ReceiveData(LCD_SPI);
	}
	SPI_I2S_SendData(LCD_SPI, 0xFF);
	/* Read upper byte */
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	/* Read lower byte */
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{}
	tmp = SPI_I2S_ReceiveData(LCD_SPI);


	SPI_I2S_SendData(LCD_SPI, 0xFF);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	/* Read lower byte */
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
	{}
	tmp = ((tmp & 0xFF) << 8) | SPI_I2S_ReceiveData(LCD_SPI);
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
	/* LCD_SPI prescaler: 2 */
	LCD_SPI->CR1 &= 0xFFC7;
	return tmp;
}

/**
  * @brief  Writes to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @param  LCD_RegValue: value to write to the selected register.
  * @retval None
  */
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
	/* Write 16-bit Index (then Write Reg) */
	LCD_WriteRegIndex(LCD_Reg);
	/* Write 16-bit Reg */
	/* Reset LCD control line(/CS) and Send Start-Byte */
	LCD_nCS_StartByte(START_BYTE | LCD_WRITE_REG);
	SPI_I2S_SendData(LCD_SPI, LCD_RegValue>>8);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	SPI_I2S_SendData(LCD_SPI, (LCD_RegValue & 0xFF));
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
}

/**
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
void LCD_WriteRAM(uint16_t RGB_Code)
{
	SPI_I2S_SendData(LCD_SPI, RGB_Code >> 8);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
	SPI_I2S_SendData(LCD_SPI, RGB_Code & 0xFF);
	while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_BSY) != RESET)
	{}
}

/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */
void LCD_WriteRAM_Prepare(void)
{
	LCD_WriteRegIndex(R34); /* Select GRAM Reg */
	/* Reset LCD control line(/CS) and Send Start-Byte */
	LCD_nCS_StartByte(START_BYTE | LCD_WRITE_REG);
}

/**
  * @brief  Writes 1 word to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
void LCD_WriteRAMWord(uint16_t RGB_Code)
{
	LCD_WriteRAM_Prepare();
	LCD_WriteRAM(RGB_Code);
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
}

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
void LCD_PowerOn(void)
{
	/* Power On sequence ---------------------------------------------------------*/
	LCD_WriteReg(R16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	LCD_WriteReg(R17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
	LCD_WriteReg(R18, 0x0000); /* VREG1OUT voltage */
	LCD_WriteReg(R19, 0x0000); /* VDV[4:0] for VCOM amplitude */
	_delay_(20);                 /* Dis-charge capacitor power voltage (200ms) */
	LCD_WriteReg(R16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	LCD_WriteReg(R17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
	_delay_(5);                  /* Delay 50 ms */
	LCD_WriteReg(R18, 0x0139); /* VREG1OUT voltage */
	_delay_(5);                  /* delay 50 ms */
	LCD_WriteReg(R19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
	LCD_WriteReg(R41, 0x0013); /* VCM[4:0] for VCOMH */
	_delay_(5);                  /* delay 50 ms */
	LCD_WriteReg(R7, 0x0173);  /* 262K color and display ON */
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOn(void)
{
	/* Display On */
	LCD_WriteReg(R7, 0x0173); /* 262K color and display ON */

}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void LCD_DisplayOff(void)
{
	/* Display Off */
	LCD_WriteReg(R7, 0x0);
}

/**
  * @brief  Configures the LCD_SPI interface.
  * @param  None
  * @retval None
  */
void LCD_SPIConfig(void)
{
	SPI_InitTypeDef    SPI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;

	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(LCD_SPI_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);

	/* Enable SPI clock  */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

	/* Configure SPI pins: SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = LCD_SPI_SCK_PIN | LCD_SPI_MISO_PIN | LCD_SPI_MOSI_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(LCD_SPI_GPIO_PORT, &GPIO_InitStructure);

	SPI_I2S_DeInit(LCD_SPI);

	/* SPI Config */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(LCD_SPI, &SPI_InitStructure);

	/* SPI enable */
	SPI_Cmd(LCD_SPI, ENABLE);
}

/**
  * @brief  Setups the LCD.
  * @param  None
  * @retval None
  */
void LCD_Setup(void)
{
	/* Configure the LCD Control pins --------------------------------------------*/
	LCD_CtrlLinesConfig();

	/* Configure the LCD_SPI interface ----------------------------------------------*/
	LCD_SPIConfig();
	_delay_(5); /* Delay 50 ms */
	/* Start Initial Sequence ------------------------------------------------*/
	LCD_WriteReg(R229, 0x8000); /* Set the internal vcore voltage */
	LCD_WriteReg(R0,  0x0001); /* Start internal OSC. */
	LCD_WriteReg(R1,  0x0100); /* set SS and SM bit */
	LCD_WriteReg(R2,  0x0700); /* set 1 line inversion */
	LCD_WriteReg(R3,  0x1030); /* set GRAM write direction and BGR=1. */
	LCD_WriteReg(R4,  0x0000); /* Resize register */
	LCD_WriteReg(R8,  0x0202); /* set the back porch and front porch */
	LCD_WriteReg(R9,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
	LCD_WriteReg(R10, 0x0000); /* FMARK function */
	LCD_WriteReg(R12, 0x0000); /* RGB interface setting */
	LCD_WriteReg(R13, 0x0000); /* Frame marker Position */
	LCD_WriteReg(R15, 0x0000); /* RGB interface polarity */
	/* Power On sequence -----------------------------------------------------*/
	LCD_WriteReg(R16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	LCD_WriteReg(R17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
	LCD_WriteReg(R18, 0x0000); /* VREG1OUT voltage */
	LCD_WriteReg(R19, 0x0000); /* VDV[4:0] for VCOM amplitude */
	_delay_(20);                 /* Dis-charge capacitor power voltage (200ms) */
	LCD_WriteReg(R16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	LCD_WriteReg(R17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
	_delay_(5);                  /* Delay 50 ms */
	LCD_WriteReg(R18, 0x0139); /* VREG1OUT voltage */
	_delay_(5);                  /* Delay 50 ms */
	LCD_WriteReg(R19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
	LCD_WriteReg(R41, 0x0013); /* VCM[4:0] for VCOMH */
	_delay_(5);                  /* Delay 50 ms */
	LCD_WriteReg(R32, 0x0000); /* GRAM horizontal Address */
	LCD_WriteReg(R33, 0x0000); /* GRAM Vertical Address */
	/* Adjust the Gamma Curve ------------------------------------------------*/
	LCD_WriteReg(R48, 0x0006);
	LCD_WriteReg(R49, 0x0101);
	LCD_WriteReg(R50, 0x0003);
	LCD_WriteReg(R53, 0x0106);
	LCD_WriteReg(R54, 0x0b02);
	LCD_WriteReg(R55, 0x0302);
	LCD_WriteReg(R56, 0x0707);
	LCD_WriteReg(R57, 0x0007);
	LCD_WriteReg(R60, 0x0600);
	LCD_WriteReg(R61, 0x020b);

	/* Set GRAM area ---------------------------------------------------------*/
	LCD_WriteReg(R80, 0x0000); /* Horizontal GRAM Start Address */
	LCD_WriteReg(R81, 0x00EF); /* Horizontal GRAM End Address */
	LCD_WriteReg(R82, 0x0000); /* Vertical GRAM Start Address */
	LCD_WriteReg(R83, 0x013F); /* Vertical GRAM End Address */
	LCD_WriteReg(R96,  0xa700); /* Gate Scan Line */
	LCD_WriteReg(R97,  0x0001); /* NDL,VLE, REV */
	LCD_WriteReg(R106, 0x0000); /* set scrolling line */
	/* Partial Display Control -----------------------------------------------*/
	LCD_WriteReg(R128, 0x0000);
	LCD_WriteReg(R129, 0x0000);
	LCD_WriteReg(R130, 0x0000);
	LCD_WriteReg(R131, 0x0000);
	LCD_WriteReg(R132, 0x0000);
	LCD_WriteReg(R133, 0x0000);
	/* Panel Control ---------------------------------------------------------*/
	LCD_WriteReg(R144, 0x0010);
	LCD_WriteReg(R146, 0x0000);
	LCD_WriteReg(R147, 0x0003);
	LCD_WriteReg(R149, 0x0110);
	LCD_WriteReg(R151, 0x0000);
	LCD_WriteReg(R152, 0x0000);
	/* Set GRAM write direction and BGR = 1 */
	/* I/D=01 (Horizontal : increment, Vertical : decrement) */
	/* AM=1 (address is updated in vertical writing direction) */
	LCD_WriteReg(R3, 0x1018);
	LCD_WriteReg(R7, 0x0173); /* 262K color and display ON */
}

/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position.
  * @retval None
  */
void LCD_SetCursor(uint8_t Xpos, uint16_t Ypos)
{
	LCD_WriteReg(R32, Xpos);
	LCD_WriteReg(R33, Ypos);
}


void rt_hw_lcd_update(rtgui_rect_t *rect)
{
	/* nothing for none-DMA mode driver */
}

rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
	return RT_NULL; /* no framebuffer driver */
}

void rt_hw_lcd_set_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
	unsigned short p;

	/* get color pixel */
	p = rtgui_color_to_565p(*c);

	/* set x and y */
	LCD_SetCursor(y, 319 - x);
	LCD_WriteRAMWord(p);
}

void rt_hw_lcd_get_pixel(rtgui_color_t *c, rt_base_t x, rt_base_t y)
{
	// unsigned short p;

	/* set x and y */
	LCD_SetCursor(y, 319 - x);

	*c = rtgui_color_from_565p(0xffff);
}

void rt_hw_lcd_draw_hline(rtgui_color_t *c, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	unsigned short p;

	/* get color pixel */
	p = rtgui_color_to_565p(*c);

	LCD_SetCursor(y, 319 - x1);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	while (x1 < x2)
	{
		LCD_WriteRAM(p);
		x1 ++;
	}
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
}

void rt_hw_lcd_draw_vline(rtgui_color_t *c, rt_base_t x, rt_base_t y1, rt_base_t y2)
{
	unsigned short p;

	/* get color pixel */
	p = rtgui_color_to_565p(*c);

	LCD_SetCursor(y1, 319 - x);
	while (y1 < y2)
	{
		LCD_WriteRAMWord(p);

		y1++;
		LCD_SetCursor(y1, 319 - x);
	}
}

void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, rt_base_t x1, rt_base_t x2, rt_base_t y)
{
	rt_uint16_t *ptr;

	/* get pixel */
	ptr = (rt_uint16_t*) pixels;

	LCD_SetCursor(y, 319 - x1);
	LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
	while (x1 < x2)
	{
		LCD_WriteRAM(*ptr);
		x1 ++; ptr ++;
	}
	LCD_CtrlLinesWrite(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, Bit_SET);
}

rt_err_t rt_hw_lcd_init(void)
{
	LCD_Setup();

	/* add lcd driver into graphic driver */
	rtgui_graphic_driver_add(&_rtgui_lcd_driver);
	return RT_EOK;
}

void stm3210c_rtgui_init()
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

#include <finsh.h>

void hline(rt_base_t x1, rt_base_t x2, rt_base_t y, rt_uint32_t pixel)
{
	rt_hw_lcd_draw_hline(&pixel, x1, x2, y);
}
FINSH_FUNCTION_EXPORT(hline, draw a hline);

void vline(int x, int y1, int y2, rt_uint32_t pixel)
{
	rt_hw_lcd_draw_vline(&pixel, x, y1, y2);
}
FINSH_FUNCTION_EXPORT(vline, draw a vline);

void cls(rt_uint32_t c)
{
	rt_size_t index;

	for(index = 0; index < 240; index ++)
		rt_hw_lcd_draw_hline(&c, 0, 320, index);
}
FINSH_FUNCTION_EXPORT(cls, clear screen);
