/*
 * File      : drv_lcd.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-08     tanek        first implementation
 */

#include "drv_lcd.h"
#include <finsh.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...)   rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)   
#endif

typedef struct
{
	rt_uint16_t width;			//LCD 宽度
	rt_uint16_t height;			//LCD 高度
	rt_uint16_t id;				//LCD ID
	rt_uint8_t  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	rt_uint16_t	wramcmd;		//开始写gram指令
	rt_uint16_t setxcmd;		//设置x坐标指令
	rt_uint16_t setycmd;		//设置y坐标指令 
} lcd_info_t;

typedef struct
{
	volatile rt_uint16_t reg;
	volatile rt_uint16_t ram;
} lcd_ili9341_t;

//使用NOR/SRAM的 Bank1.sector1,地址位HADDR[27,26]=00 A18作为数据命令区分线 
//注意设置时STM32内部会右移一位对其!
#define LCD_ILI9341_BASE        ((rt_uint32_t)(0x60000000 | 0x0007FFFE))
#define ili9341					((lcd_ili9341_t *) LCD_ILI9341_BASE)
//////////////////////////////////////////////////////////////////////////////////

//扫描方向定义
#define L2R_U2D  0 		//从左到右,从上到下
#define L2R_D2U  1 		//从左到右,从下到上
#define R2L_U2D  2 		//从右到左,从上到下
#define R2L_D2U  3 		//从右到左,从下到上
#define U2D_L2R  4 		//从上到下,从左到右
#define U2D_R2L  5 		//从上到下,从右到左
#define D2U_L2R  6 		//从下到上,从左到右
#define D2U_R2L  7		//从下到上,从右到左	 
#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向

static lcd_info_t lcddev;

void delay_us(rt_uint32_t nus)
{
	//rt_thread_delay(1);
	while (nus--) {
		__NOP();
	}
}

void delay_ms(rt_uint32_t nms)
{
	//rt_thread_delay((RT_TICK_PER_SECOND * nms + 999) / 1000);
	while (nms--)
	{
		int i;
		for (i = 0; i < 10000; i++)
		{
			__NOP();
		}
	}
}

static void ili9341_write_reg(rt_uint16_t regval)
{
	ili9341->reg = regval;
}

static void ili9341_write_data(rt_uint16_t data)
{
	ili9341->ram = data;
}

rt_uint16_t ili9341_read_ram(void)
{
	return ili9341->ram;
}

static void ili9341_write_reg_with_value(rt_uint16_t reg, rt_uint16_t regValue)
{
	ili9341->reg = reg;
	ili9341->ram = regValue;
}

static void ili9341_write_ram_prepare(void)
{
	ili9341->reg = lcddev.wramcmd;
}

rt_uint16_t ili9341_bgr2rgb(rt_uint16_t value)
{
	rt_uint16_t  red, green, blue;

	blue = (value >> 0) & 0x1f;
	green = (value >> 5) & 0x3f;
	red = (value >> 11) & 0x1f;

	return (blue << 11) + (green << 5) + (red << 0);
}

static void ili9341_set_cursor(rt_uint16_t Xpos, rt_uint16_t Ypos)
{
	ili9341_write_reg(lcddev.setxcmd);
	ili9341_write_data(Xpos >> 8); 
	ili9341_write_data(Xpos & 0XFF);

	ili9341_write_reg(lcddev.setycmd);
	ili9341_write_data(Ypos >> 8); 
	ili9341_write_data(Ypos & 0XFF);
}
  	   
static void ili9341_set_scan_direction(rt_uint8_t dir)
{
	rt_uint16_t regval = 0;
	rt_uint16_t dirreg = 0;
	rt_uint16_t temp;

	switch (dir)
	{
	case L2R_U2D://从左到右,从上到下
		regval |= (0 << 7) | (0 << 6) | (0 << 5);
		break;
	case L2R_D2U://从左到右,从下到上
		regval |= (1 << 7) | (0 << 6) | (0 << 5);
		break;
	case R2L_U2D://从右到左,从上到下
		regval |= (0 << 7) | (1 << 6) | (0 << 5);
		break;
	case R2L_D2U://从右到左,从下到上
		regval |= (1 << 7) | (1 << 6) | (0 << 5);
		break;
	case U2D_L2R://从上到下,从左到右
		regval |= (0 << 7) | (0 << 6) | (1 << 5);
		break;
	case U2D_R2L://从上到下,从右到左
		regval |= (0 << 7) | (1 << 6) | (1 << 5);
		break;
	case D2U_L2R://从下到上,从左到右
		regval |= (1 << 7) | (0 << 6) | (1 << 5);
		break;
	case D2U_R2L://从下到上,从右到左
		regval |= (1 << 7) | (1 << 6) | (1 << 5);
		break;
	}

	dirreg = 0X36;
	ili9341_write_reg_with_value(dirreg, regval);

	if (regval & 0X20)
	{
		if (lcddev.width < lcddev.height)//交换X,Y
		{
			temp = lcddev.width;
			lcddev.width = lcddev.height;
			lcddev.height = temp;
		}
	}
	else
	{
		if (lcddev.width > lcddev.height)//交换X,Y
		{
			temp = lcddev.width;
			lcddev.width = lcddev.height;
			lcddev.height = temp;
		}
	}
	
	ili9341_write_reg(lcddev.setxcmd);
	ili9341_write_data(0);
	ili9341_write_data(0);
	ili9341_write_data((lcddev.width - 1) >> 8);
	ili9341_write_data((lcddev.width - 1) & 0XFF);

	ili9341_write_reg(lcddev.setycmd);
	ili9341_write_data(0);
	ili9341_write_data(0);
	ili9341_write_data((lcddev.height - 1) >> 8);
	ili9341_write_data((lcddev.height - 1) & 0XFF);
}

void ili9341_set_backlight(rt_uint8_t pwm)
{
	ili9341_write_reg(0xBE);
	ili9341_write_data(0x05);
	ili9341_write_data(pwm*2.55);
	ili9341_write_data(0x01);
	ili9341_write_data(0xFF);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
}

void ili9341_set_display_direction(rt_uint8_t dir)
{
	lcddev.dir = dir;
	if (dir == 0)
	{
		lcddev.width = 240;
		lcddev.height = 320;
	}
	else
	{
		lcddev.width = 320;
		lcddev.height = 240;
	}

	lcddev.wramcmd = 0X2C;
	lcddev.setxcmd = 0X2A;
	lcddev.setycmd = 0X2B;

	ili9341_set_scan_direction(DFT_SCAN_DIR);
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_FMC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//init PD0,1,4,5,7,8,9,10,13,14,15
	GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | \
		GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	GPIO_Initure.Alternate = GPIO_AF12_FMC;
	HAL_GPIO_Init(GPIOD, &GPIO_Initure);

	//init PE7,8,9,10,11,12,13,14,15
	GPIO_Initure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
		GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &GPIO_Initure);
}

SRAM_HandleTypeDef SRAM_Handler;

void _lcd_low_level_init(void)
{
	GPIO_InitTypeDef GPIO_Initure;

	FMC_NORSRAM_TimingTypeDef FMC_ReadWriteTim;
	FMC_NORSRAM_TimingTypeDef FMC_WriteTim;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_Initure.Pin = GPIO_PIN_5;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_Initure);

	SRAM_Handler.Instance = FMC_NORSRAM_DEVICE;
	SRAM_Handler.Extended = FMC_NORSRAM_EXTENDED_DEVICE;

	SRAM_Handler.Init.NSBank = FMC_NORSRAM_BANK1;
	SRAM_Handler.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
	SRAM_Handler.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
	SRAM_Handler.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
	SRAM_Handler.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
	SRAM_Handler.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
	SRAM_Handler.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
	SRAM_Handler.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
	SRAM_Handler.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
	SRAM_Handler.Init.ExtendedMode = FMC_EXTENDED_MODE_ENABLE;
	SRAM_Handler.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
	SRAM_Handler.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
	SRAM_Handler.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;

	FMC_ReadWriteTim.AddressSetupTime = 0x0F;
	FMC_ReadWriteTim.AddressHoldTime = 0x00;
	FMC_ReadWriteTim.DataSetupTime = 0x46;
	FMC_ReadWriteTim.AccessMode = FMC_ACCESS_MODE_A;

	FMC_WriteTim.AddressSetupTime = 0x0F;
	FMC_WriteTim.AddressHoldTime = 0x00;
	FMC_WriteTim.DataSetupTime = 0x0F;
	FMC_WriteTim.AccessMode = FMC_ACCESS_MODE_A;
	HAL_SRAM_Init(&SRAM_Handler, &FMC_ReadWriteTim, &FMC_WriteTim);
	delay_ms(50);

	ili9341_write_reg(0XD3);
	lcddev.id = ili9341_read_ram();
	lcddev.id = ili9341_read_ram();
	lcddev.id = ili9341_read_ram();
	lcddev.id <<= 8;
	lcddev.id |= ili9341_read_ram();

	DEBUG_PRINTF(" LCD ID:%x\r\n", lcddev.id); //打印LCD ID   

	ili9341_write_reg(0xCF);
	ili9341_write_data(0x00);
	ili9341_write_data(0xC1);
	ili9341_write_data(0X30);
	ili9341_write_reg(0xED);
	ili9341_write_data(0x64);
	ili9341_write_data(0x03);
	ili9341_write_data(0X12);
	ili9341_write_data(0X81);
	ili9341_write_reg(0xE8);
	ili9341_write_data(0x85);
	ili9341_write_data(0x10);
	ili9341_write_data(0x7A);
	ili9341_write_reg(0xCB);
	ili9341_write_data(0x39);
	ili9341_write_data(0x2C);
	ili9341_write_data(0x00);
	ili9341_write_data(0x34);
	ili9341_write_data(0x02);
	ili9341_write_reg(0xF7);
	ili9341_write_data(0x20);
	ili9341_write_reg(0xEA);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_reg(0xC0);    //Power control 
	ili9341_write_data(0x1B);   //VRH[5:0] 
	ili9341_write_reg(0xC1);    //Power control 
	ili9341_write_data(0x01);   //SAP[2:0];BT[3:0] 
	ili9341_write_reg(0xC5);    //VCM control 
	ili9341_write_data(0x30); 	//3F
	ili9341_write_data(0x30);   //3C
	ili9341_write_reg(0xC7);    //VCM control2 
	ili9341_write_data(0XB7);
	ili9341_write_reg(0x36);    // memory access control 
	ili9341_write_data(0x08);   // change here
	ili9341_write_reg(0x3A);
	ili9341_write_data(0x55);
	ili9341_write_reg(0xB1);
	ili9341_write_data(0x00);
	ili9341_write_data(0x1A);
	ili9341_write_reg(0xB6);    //display function control 
	ili9341_write_data(0x0A);
	ili9341_write_data(0xA2);
	ili9341_write_reg(0xF2);    //3gamma function disable 
	ili9341_write_data(0x00);
	ili9341_write_reg(0x26);    //gamma curve selected 
	ili9341_write_data(0x01);
	ili9341_write_reg(0xE0);    //set gamma 
	ili9341_write_data(0x0F);
	ili9341_write_data(0x2A);
	ili9341_write_data(0x28);
	ili9341_write_data(0x08);
	ili9341_write_data(0x0E);
	ili9341_write_data(0x08);
	ili9341_write_data(0x54);
	ili9341_write_data(0XA9);
	ili9341_write_data(0x43);
	ili9341_write_data(0x0A);
	ili9341_write_data(0x0F);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_reg(0XE1);    //set gamma 
	ili9341_write_data(0x00);
	ili9341_write_data(0x15);
	ili9341_write_data(0x17);
	ili9341_write_data(0x07);
	ili9341_write_data(0x11);
	ili9341_write_data(0x06);
	ili9341_write_data(0x2B);
	ili9341_write_data(0x56);
	ili9341_write_data(0x3C);
	ili9341_write_data(0x05);
	ili9341_write_data(0x10);
	ili9341_write_data(0x0F);
	ili9341_write_data(0x3F);
	ili9341_write_data(0x3F);
	ili9341_write_data(0x0F);
	ili9341_write_reg(0x2B);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_data(0x01);
	ili9341_write_data(0x3f);
	ili9341_write_reg(0x2A);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_data(0x00);
	ili9341_write_data(0xef);
	ili9341_write_reg(0x11); //exit sleep
	delay_ms(120);
	ili9341_write_reg(0x29); //display on	

	FMC_Bank1E->BWTR[0] &= ~(0XF << 0);
	FMC_Bank1E->BWTR[0] &= ~(0XF << 8);
	FMC_Bank1E->BWTR[0] |= 4 << 0;
	FMC_Bank1E->BWTR[0] |= 4 << 8;

	ili9341_set_display_direction(0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}


static rt_err_t lcd_init(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t lcd_open(rt_device_t dev, rt_uint16_t oflag)
{
	return RT_EOK;
}

static rt_err_t lcd_close(rt_device_t dev)
{
	return RT_EOK;
}

static rt_err_t lcd_control(rt_device_t dev, int cmd, void *args)
{
	switch (cmd)
	{
	case RTGRAPHIC_CTRL_GET_INFO:
	{
		struct rt_device_graphic_info *info;

		info = (struct rt_device_graphic_info*) args;
		RT_ASSERT(info != RT_NULL);

		info->bits_per_pixel = 16;
		info->pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
		info->framebuffer = RT_NULL;
		info->width = 240;
		info->height = 320;
	}
	break;

	case RTGRAPHIC_CTRL_RECT_UPDATE:
		/* nothong to be done */
		break;

	default:
		break;
	}

	return RT_EOK;
}

static void ili9341_lcd_set_pixel(const char* pixel, int x, int y)
{
	ili9341_set_cursor(x, y);
	ili9341_write_ram_prepare();
	ili9341->ram = *(uint16_t *)pixel;
}
#ifdef RT_USING_FINSH
static void lcd_set_pixel(uint16_t color, int x, int y)
{
	rt_kprintf("lcd set pixel, color: %X, x: %d, y: %d", color, x, y);
	ili9341_lcd_set_pixel((const char *)&color, x, y);
}
FINSH_FUNCTION_EXPORT(lcd_set_pixel, set pixel in lcd display);
#endif

static void ili9341_lcd_get_pixel(char* pixel, int x, int y)
{
	rt_uint16_t red = 0;
	rt_uint16_t green = 0;
	rt_uint16_t blue = 0;

	if (x >= lcddev.width || y >= lcddev.height)
	{
		*(rt_uint16_t*)pixel = 0;
		return;
	}

	ili9341_set_cursor(x, y);

	ili9341_write_reg(0X2E);
	ili9341_read_ram();
	red = ili9341_read_ram();
	delay_us(2);

	blue = ili9341_read_ram();
	green = red & 0XFF;

	*(rt_uint16_t*)pixel = (((red >> 11) << 11) | ((green >> 10) << 5) | (blue >> 11));
}
#ifdef RT_USING_FINSH
static void lcd_get_pixel(int x, int y)
{
	uint16_t pixel;
	ili9341_lcd_get_pixel((char *)&pixel, x, y);
	rt_kprintf("lcd get pixel, pixel: 0x%X, x: %d, y: %d", pixel, x, y);
}
FINSH_FUNCTION_EXPORT(lcd_get_pixel, get pixel in lcd display);
#endif

static void ili9341_lcd_draw_hline(const char* pixel, int x1, int x2, int y)
{
	ili9341_set_cursor(x1, y);
	ili9341_write_ram_prepare();

	for (; x1 < x2; x1++)
	{
		ili9341->ram = *(uint16_t *)pixel;
	}
}
#ifdef RT_USING_FINSH
static void lcd_draw_hline(uint16_t pixel, int x1, int x2, int y)
{
	ili9341_lcd_draw_hline((const char *)&pixel, x1, x2, y);
	rt_kprintf("lcd draw hline, pixel: 0x%X, x1: %d, x2: %d, y: %d", pixel, x1, x2, y);
}
FINSH_FUNCTION_EXPORT(lcd_draw_hline, draw hline in lcd display);
#endif

static void ili9341_lcd_draw_vline(const char* pixel, int x, int y1, int y2)
{
	for (; y1 < y2; y1++)
	{
		ili9341_lcd_set_pixel(pixel, x, y1);  //write red data
	}
}
#ifdef RT_USING_FINSH
static void lcd_draw_vline(uint16_t pixel, int x, int y1, int y2)
{
	ili9341_lcd_draw_vline((const char *)&pixel, x, y1, y2);
	rt_kprintf("lcd draw hline, pixel: 0x%X, x: %d, y: %d", pixel, y1, y2);
}
FINSH_FUNCTION_EXPORT(lcd_draw_vline, draw vline in lcd display);
#endif

static void ili9341_lcd_blit_line(const char* pixels, int x, int y, rt_size_t size)
{
	rt_uint16_t *ptr = (rt_uint16_t*)pixels;

	ili9341_set_cursor(x, y);
	ili9341_write_ram_prepare();

	while (size--)
	{
		ili9341->ram = *ptr++;
	}
}
#ifdef RT_USING_FINSH
#define LINE_LEN 30
static void lcd_blit_line(int x, int y)
{
	uint16_t pixels[LINE_LEN];
	int i;

	for (i = 0; i < LINE_LEN; i++)
	{
		pixels[i] = i * 40 + 50;
	}

	ili9341_lcd_blit_line((const char *)pixels, x, y, LINE_LEN);
	rt_kprintf("lcd blit line, x: %d, y: %d", x, y);
}
FINSH_FUNCTION_EXPORT(lcd_blit_line, draw blit line in lcd display);
#endif

static int rt_hw_lcd_init(void)
{
	_lcd_low_level_init();

	static struct rt_device lcd_device;

	static struct rt_device_graphic_ops ili9341_ops =
	{
		ili9341_lcd_set_pixel,
		ili9341_lcd_get_pixel,
		ili9341_lcd_draw_hline,
		ili9341_lcd_draw_vline,
		ili9341_lcd_blit_line
	};

	/* register lcd device */
	lcd_device.type = RT_Device_Class_Graphic;
	lcd_device.init = lcd_init;
	lcd_device.open = lcd_open;
	lcd_device.close = lcd_close;
	lcd_device.control = lcd_control;
	lcd_device.read = RT_NULL;
	lcd_device.write = RT_NULL;

	lcd_device.user_data = &ili9341_ops;

	/* register graphic device driver */
	rt_device_register(&lcd_device, "lcd",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

	return 0;
}
INIT_BOARD_EXPORT(rt_hw_lcd_init);
