/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-05     lgnq         ZYMG12864C3 LCD driver
 */

#include <rtthread.h>
#include "lcd.h"
#include "font.h"

static struct rt_device_graphic_info _lcd_info;
static rt_uint8_t gui_disp_buf[GUI_LCM_YMAX/8][GUI_LCM_XMAX];
const unsigned char BIT_MASK[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
/* simple font: ' ', '0'~'9','a'~'z','A'~'Z' */
extern const unsigned char  FONTTYPE8_8[][8];

rt_uint32_t x;
rt_uint32_t y;

void power_delay(void)
{
    rt_uint32_t i = 0x4ffff;
    while(i--)
        ;
}

void delay(void)
{
    rt_uint8_t i = 0x8;
    while(i--)
        ;
}

void reset_delay(void)
{
    rt_uint8_t i = 0xff;
    while(i--)
        ;
}

void lcd_write_cmd(unsigned char command)
{
    rt_uint8_t i;

    LCD_PS_LOW();
    LCD_CS_LOW();
    LCD_CD_LOW();
    for (i=0; i<8; i++)
    {
        if (command & (0x80 >> i))
            LCD_DATA_HIGH();
        else
            LCD_DATA_LOW();

        LCD_CLK_LOW();
        delay();
        LCD_CLK_HIGH();
        delay();
    }
    LCD_CS_HIGH();
}

void lcd_write_data(unsigned char data)
{
    rt_uint8_t i;

    LCD_PS_LOW();
    LCD_CS_LOW();
    LCD_CD_HIGH();
    for (i=0; i<8; i++)
    {
        if (data & (0x80 >> i))
            LCD_DATA_HIGH();
        else
            LCD_DATA_LOW();

        LCD_CLK_LOW();
        delay();
        LCD_CLK_HIGH();
        delay();
    }
    LCD_CS_HIGH();
}

#ifdef RT_USING_RTGUI
#include <rtgui/driver.h>
#include <rtgui/color.h>

static void rt_hw_lcd_update(struct rt_device_rect_info *rect_info)
{
    rt_uint8_t i,j = GUI_LCM_XMAX;
    rt_uint8_t* p = (rt_uint8_t*)gui_disp_buf;

    for (i=0; i<GUI_LCM_PAGE; i++)
    {
        lcd_write_cmd(SET_PAGE_ADDR_0|i);
        lcd_write_cmd(SET_COLH_ADDR_0);
        lcd_write_cmd(SET_COLL_ADDR_0);
        j = GUI_LCM_XMAX;
        while (j--)
        {
            lcd_write_data(*p++);
            delay();
        }
    }
}

static rt_uint8_t * rt_hw_lcd_get_framebuffer(void)
{
    return(rt_uint8_t *)gui_disp_buf;
}

static void rt_hw_lcd_set_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint8_t page;
    page = y/8;

    if (*c == rtgui_color_to_565(black))
        gui_disp_buf[page][x] |= 1<<(y%8);
    else
        if (*c == rtgui_color_to_565(white))
            gui_disp_buf[page][x] &= ~(1<<(y%8));
}

static void rt_hw_lcd_get_pixel(rtgui_color_t *c, int x, int y)
{
    rt_uint8_t page;
    page = y/8;

    if (gui_disp_buf[page][x] & (1<<(y%8)))
        *c = black;
    else
        *c = white;
}

static void rt_hw_lcd_draw_hline(rtgui_color_t *c, int x1, int x2, int y)
{
    rt_uint8_t page;
    rt_uint8_t i;
    page = y/8;

    for (i=x1; i<x2; i++)
    {
        if (*c == rtgui_color_to_565(black))
            gui_disp_buf[page][i] |= 1<<(y%8);
        else
            if (*c == rtgui_color_to_565(white))
                gui_disp_buf[page][i] &= ~(1<<(y%8));
    }
}

static void rt_hw_lcd_draw_vline(rtgui_color_t *c, int x, int y1, int y2)
{
    rt_uint8_t y;

    for (y = y1; y < y2; y ++)
    {
        rt_hw_lcd_set_pixel(c, x, y);
    }
}

static void rt_hw_lcd_draw_raw_hline(rt_uint8_t *pixels, int x1, int x2, int y)
{
    rt_uint8_t coll;
    rt_uint8_t colh;
    rt_uint8_t page;
    rt_uint8_t i;

    page = y/8;

    for (i=x1; i<x2; i++)
    {
        gui_disp_buf[page][i] |= 1<<(y%8);
        coll = i & 0x0f;
        colh = i >> 4;
        lcd_write_cmd(SET_PAGE_ADDR_0 | page);
        lcd_write_cmd(SET_COLH_ADDR_0 | colh);
        lcd_write_cmd(SET_COLL_ADDR_0 | coll);
        lcd_write_data(gui_disp_buf[page][i]);
    }
}

const struct rtgui_graphic_driver_ops _lcd_ops =
{
    rt_hw_lcd_set_pixel,
    rt_hw_lcd_get_pixel,
    rt_hw_lcd_draw_hline,
    rt_hw_lcd_draw_vline,
    rt_hw_lcd_draw_raw_hline
};
#endif

void lcd_io_init()
{
    /* Release the analog input function*/
    FM3_GPIO->ADE =0x03;
    /*Select CPIO function*/
    LCD_CS_PFR &= ~LCD_CS;
    /*Make pin output*/
    LCD_CS_DDR |= LCD_CS;
    /*Select CPIO function*/
    LCD_CD_PFR &= ~LCD_CD;
    /*Make pin output*/
    LCD_CD_DDR |= LCD_CD;
    /*Select CPIO function*/
    LCD_PS_PFR &= ~LCD_PS;
    /*Make pin output*/
    LCD_PS_DDR |= LCD_PS;
    /*Select CPIO function*/
    LCD_CLK_PFR &= ~LCD_CLK;
    /*Make pin output*/
    LCD_CLK_DDR |= LCD_CLK;
    /*Select CPIO function*/
    LCD_DATA_PFR &= ~LCD_DATA;
    /*Make pin output*/
    LCD_DATA_DDR |= LCD_DATA;
}

/* RT-Thread Device Interface */
static rt_err_t rt_lcd_init (rt_device_t dev)
{
    lcd_io_init();

    power_delay();
    lcd_write_cmd(DISPLAY_OFF);
    reset_delay();
    // Resetting circuit
    lcd_write_cmd(RESET_LCD);
    reset_delay();
    // LCD bias setting
    lcd_write_cmd(SET_LCD_BIAS_9);
    reset_delay();
    // ADC selection: display from left to right
    lcd_write_cmd(SET_ADC_NORMAL);
    reset_delay();
    // Common output state selection: display from up to down
    lcd_write_cmd(COM_SCAN_DIR_REVERSE);
    reset_delay();

    lcd_write_cmd(POWER_BOOSTER_ON);
    power_delay(); // 50ms requried
    lcd_write_cmd(POWER_REGULATOR_ON);
    power_delay(); // 50ms
    lcd_write_cmd(POWER_FOLLOWER_ON);
    power_delay(); // 50ms

    // Setting the built-in resistance radio for regulation of the V0 voltage
    // Electronic volume control
    // Power control setting
    lcd_write_cmd(SET_ELECVOL_REG|0x05);
    delay();
    lcd_write_cmd(SET_ELECVOL_MODE);
    delay();
    lcd_write_cmd(SET_ELECVOL_REG);
    delay();
    //  LCD_Clear();
    delay();
    lcd_write_cmd(SET_PAGE_ADDR_0);
    delay();
    lcd_write_cmd(SET_COLH_ADDR_0);
    delay();
    lcd_write_cmd(SET_COLL_ADDR_0);
    delay();
    lcd_write_cmd(DISPLAY_ON);
    delay();

    lcd_write_cmd(DISPLAY_ALL_ON);
    delay();
    lcd_write_cmd(DISPLAY_OFF);
    delay();
    lcd_write_cmd(DISPLAY_ON);
    delay();
    lcd_write_cmd(DISPLAY_ALL_NORMAL);
    delay();

    return RT_EOK;
}

/*******************************************************************************
* Function Name  : LCD_FillAll
* Description    : Fill the whole LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_FillAll(unsigned char* buffer)
{
  unsigned char i,j = GUI_LCM_XMAX;
  unsigned char* p = buffer;

  for (i=0; i<GUI_LCM_PAGE; i++)
  {
    lcd_write_cmd(SET_PAGE_ADDR_0|i);
    lcd_write_cmd(SET_COLH_ADDR_0);
    lcd_write_cmd(SET_COLL_ADDR_0);
    j = GUI_LCM_XMAX;
    while (j--)
    {
      lcd_write_data(*p++);
      delay();
    }
  }
}

/*******************************************************************************
* Function Name  : LCD_ClearSCR
* Description    : clean screen
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ClearSCR(void)
{
  unsigned char i, j;

  for(i=0; i<GUI_LCM_PAGE; i++)
  {
    for(j = 0; j < GUI_LCM_XMAX; j++)
      gui_disp_buf[i][j] = 0;
  }
  LCD_FillAll((unsigned char*)gui_disp_buf);
}

/****************************************************************************
* Function Name  : LCD_UpdatePoint
* Description    : refresh the point in screen
* Input          : x      X-coordinate
                   y      Y-coordinate
* Output         : None
* Return         : None
****************************************************************************/

void  LCD_UpdatePoint(unsigned int x, unsigned int y)
{
  unsigned char coll, colh, page;
  page = y / 8;
  coll = x & 0x0f;
  colh = x >> 4;

  lcd_write_cmd(SET_PAGE_ADDR_0 | page);            // page no.
  lcd_write_cmd(SET_COLH_ADDR_0 | colh);        // fixed col first addr
  lcd_write_cmd(SET_COLL_ADDR_0 | coll);
  lcd_write_data(gui_disp_buf[page][x]);
}

/****************************************************************************
* Function Name  : LCD_PutChar
* Description    : output a char to screen
                  (the char only can be ' ','0'~'9','A'~'Z','a'~'z')
* Input          : x      X-coordinate
                   y      Y-coordinate
                   ch     character
* Output         : None
* Return         : 1    Success
                   0    Fail
****************************************************************************/
unsigned char  LCD_PutChar(unsigned long x, unsigned long y, unsigned char ch)
{
   unsigned char data;
   unsigned char i, j;

   if( x >=(GUI_LCM_XMAX-8) ) return(0);
   if( y >=(GUI_LCM_YMAX-8) ) return(0);

   if(ch == 0x20)
     ch -= 0x20;
     else if((ch >= 0x30)&&(ch <= 0x39))
       ch -= 0x2f;
       else if((ch >= 0x41)&&(ch <= 0x5a))
         ch -= 0x36;
         else if((ch >= 0x61)&&(ch <= 0x7a))
          ch -= 0x3C;
          else
            return(0);

   for(i = 0; i < 8; i++)
   {
      data = FONTTYPE8_8[ch][i];

      for(j = 0; j < 8; j++)
      {
         if( (data&BIT_MASK[j]) == 0)
           gui_disp_buf[y / 8][x] &= (~(0x01 << ( y % 8)));
         else
           gui_disp_buf[y / 8][x] |= (0x01 <<( y % 8));
         LCD_UpdatePoint(x, y);
         x ++;
      }
      x -= 8;
      y++;
   }

   return(1);
}

/****************************************************************************
* Function Name  : LCD_PutString
* Description    : output string to screen
* Input          : x      X-coordinate
                   y      Y-coordinate
                  str     pointer to string
* Output         : None
* Return         : None
****************************************************************************/
void  LCD_PutString(unsigned long x, unsigned long y, char *str)
{
  while(1)
  {
    if( (*str)=='\0' ) break;
    if( LCD_PutChar(x, y, *str++) == 0 ) break;
    x += 6;
  }
}

static rt_err_t rt_lcd_control (rt_device_t dev, int cmd, void *args)
{
    switch (cmd)
    {
#ifdef RT_USING_RTGUI
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        rt_hw_lcd_update(args);
        break;
    case RTGRAPHIC_CTRL_POWERON:
        break;
    case RTGRAPHIC_CTRL_POWEROFF:
        break;
    case RTGRAPHIC_CTRL_GET_INFO:
        rt_memcpy(args, &_lcd_info, sizeof(_lcd_info));
        break;
    case RTGRAPHIC_CTRL_SET_MODE:
        break;
#else
    case RT_DEVICE_CTRL_LCD_DISPLAY_ON:
        lcd_write_cmd(DISPLAY_ON);
        break;
    case RT_DEVICE_CTRL_LCD_DISPLAY_OFF:
        lcd_write_cmd(DISPLAY_OFF);
        break;
    case RT_DEVICE_CTRL_LCD_PUT_STRING:
        LCD_PutString(x, y, (char*)args);
        break;
    case RT_DEVICE_CTRL_LCD_CLEAR_SCR:
        LCD_ClearSCR();
        break;
#endif
    }

    return RT_EOK;
}

void rt_hw_lcd_init(void)
{
    rt_device_t lcd = rt_malloc(sizeof(struct rt_device));
    if (lcd == RT_NULL) return; /* no memory yet */

    _lcd_info.bits_per_pixel = 16;
    _lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    _lcd_info.framebuffer = RT_NULL;
    _lcd_info.width = LCD_WIDTH;
    _lcd_info.height = LCD_HEIGHT;

    /* init device structure */
    lcd->type = RT_Device_Class_Unknown;
    lcd->init = rt_lcd_init;
    lcd->open = RT_NULL;
    lcd->close = RT_NULL;
    lcd->control = rt_lcd_control;
#ifdef RT_USING_RTGUI
    lcd->user_data = (void*)&_lcd_ops;
#endif
    /* register lcd device to RT-Thread */
    rt_device_register(lcd, "lcd", RT_DEVICE_FLAG_RDWR);
}
