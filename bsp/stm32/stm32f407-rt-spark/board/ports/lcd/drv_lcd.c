/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-28     unknow       copy by STemwin
 * 2021-12-29     xiangxistu   port for lvgl <lcd_fill_array>
 * 2022-6-26      solar        Improve the api required for resistive touch screen calibration
 * 2023-05-17     yuanjie      parallel driver improved
 */

#include <rtdevice.h>
#include <board.h>
#include <string.h>
#include <drv_gpio.h>
#include "drv_lcd.h"
#include "drv_lcd_font.h"

#define DRV_DEBUG
#define LOG_TAG "drv.lcd"
#include <drv_log.h>

_lcd_dev lcddev;
rt_uint16_t BACK_COLOR = WHITE, FORE_COLOR = BLACK;

#define LCD_CLEAR_SEND_NUMBER 5760

#ifdef BSP_USING_ONBOARD_LCD_PWM_BL
    #define PWM_BL_NAME        "pwm14"              /* 背光PWM设备名称 */
    #define PWM_BL_CHANNEL     1                    /* 背光PWM通道 */
    #define PWM_BL_PERIOD      500000               /* 0.5ms = 2000 Hz*/
    struct rt_device_pwm *pwm_bl_dev = RT_NULL;     /* PWM设备句柄 */
#else
    #define LCD_BL  GET_PIN(F, 9)
#endif /* BSP_USING_ONBOARD_LCD_PWM_BL */

#define LCD_RST GET_PIN(D, 3)

#define LCD_DEVICE(dev) (struct drv_lcd_device *)(dev)

struct drv_lcd_device
{
    struct rt_device parent;

    struct rt_device_graphic_info lcd_info;
};

static struct drv_lcd_device _lcd;

// 写寄存器函数
// regval:寄存器值
void LCD_WR_REG(uint8_t regval)
{
    LCD->_u8_REG = regval; // 写入要写的寄存器序号
}
// 写LCD数据
// data:要写入的值
void LCD_WR_DATA16(uint16_t data)
{
    LCD->_u16_RAM = data;
}
void LCD_WR_DATA8(uint8_t data)
{
    LCD->_u8_RAM = data;
}
// 读LCD数据
// 返回值:读到的值
uint8_t LCD_RD_DATA8(void)
{
    return LCD->_u8_RAM;
}
// 写寄存器
// LCD_Reg:寄存器地址
// LCD_RegValue:要写入的数据
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
    LCD->_u8_REG = LCD_Reg;      // 写入要写的寄存器序号
    LCD->_u16_RAM = LCD_RegValue; // 写入数据
}
// 读寄存器
// LCD_Reg:寄存器地址
// 返回值:读到的数据
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
    LCD_WR_REG(LCD_Reg);  // 写入要读的寄存器序号
    return LCD_RD_DATA8(); // 返回读到的值
}
// 开始写GRAM
void LCD_WriteRAM_Prepare(void)
{
    LCD->_u8_REG = lcddev.wramcmd;
}
// LCD写GRAM
// RGB_Code:颜色值
void LCD_WriteRAM(uint16_t RGB_Code)
{
    LCD->_u16_RAM = RGB_Code; // 写十六位GRAM
}

// 从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
// 通过该函数转换
// c:GBR格式的颜色值
// 返回值：RGB格式的颜色值
uint16_t LCD_BGR2RGB(uint16_t c)
{
    uint16_t r, g, b, rgb;
    b = (c >> 0) & 0x1f;
    g = (c >> 5) & 0x3f;
    r = (c >> 11) & 0x1f;
    rgb = (b << 11) + (g << 5) + (r << 0);
    return (rgb);
}

// 设置光标位置(对RGB屏无效)
// Xpos:横坐标
// Ypos:纵坐标
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    if (lcddev.id == 8552) // st7789v3
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA16(Xpos >> 8);
        LCD_WR_DATA16(Xpos & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA16(Ypos >> 8);
        LCD_WR_DATA16(Ypos & 0XFF);
    }
}

// 读取个某点的颜色值
// x,y:坐标
// 返回值:此点的颜色
void LCD_ReadPoint(char *pixel, int x, int y)
{
    uint16_t *color = (uint16_t *)pixel;
    uint16_t r = 0, g = 0, b = 0;
    if (x >= lcddev.width || y >= lcddev.height)
    {
        *color = 0; // 超过了范围,直接返回
        return;
    }
    LCD_SetCursor(x, y);
    if (lcddev.id == 0X81b3)
        LCD_WR_REG(0X2E); // 9341/3510/1963 发送读GRAM指令

    r = LCD_RD_DATA8();      // dummy Read

    r = LCD_RD_DATA8(); // 实际坐标颜色
    b = LCD_RD_DATA8();

    g = r & 0XFF; // 对于9341/5310/5510,第一次读取的是RG的值,R在前,G在后,各占8位
    g <<= 8;
    *color = (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11)); // ILI9341/NT35310/NT35510需要公式转换一下
}
// LCD开启显示
void LCD_DisplayOn(void)
{
    if (lcddev.id == 0X81b3)
        LCD_WR_REG(0X29); // 开启显示
}
// LCD关闭显示
void LCD_DisplayOff(void)
{
    if (lcddev.id == 0X81b3)
        LCD_WR_REG(0X28); // 关闭显示
}


#ifdef BSP_USING_ONBOARD_LCD_PWM_BL

//TODO PWM14 not working

// 初始化LCD背光定时器
void LCD_PWM_BackLightInit()
{
    pwm_bl_dev = (struct rt_device_pwm *)rt_device_find(PWM_BL_NAME);
    if(RT_NULL != pwm_bl_dev)
    {
        /* 设置PWM周期和脉冲宽度默认值 */
        rt_pwm_set(pwm_bl_dev, PWM_BL_CHANNEL, PWM_BL_PERIOD, 0);

    }
    else
    {
        LOG_E("pwm backlight error!");
    }
}

// TODO 反初始化LCD背光定时器
// void LCD_TIM_BackLightDeinit(uint8_t value)
// {

// }

// 设置LCD背光亮度
// pwm:背光等级,0~100.越大越亮.
void LCD_BackLightSet(uint8_t value)
{
    value = value > 100 ? 100 : value;
    if(RT_NULL != pwm_bl_dev)
    {
        /* 设置PWM周期和脉冲宽度默认值 */
        rt_pwm_set(pwm_bl_dev, PWM_BL_CHANNEL, PWM_BL_PERIOD, (PWM_BL_PERIOD/100)*value);
        /* 使能设备 */
        rt_pwm_enable(pwm_bl_dev, PWM_BL_CHANNEL);

        LOG_D("backlight %d percent", value);
    }
    else
    {
        LOG_E("backlight set error!");
    }
}
#endif

// 设置LCD的自动扫描方向(对RGB屏无效)
// 注意:其他函数可能会受到此函数设置的影响(尤其是9341),
// 所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
// dir:0~7,代表8个方向(具体定义见lcd.h)
// 9341/5310/5510/1963等IC已经实际测试
void LCD_Scan_Dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;
    if ((lcddev.dir == 1 && lcddev.id != 0X1963) || (lcddev.dir == 0 && lcddev.id == 0X1963)) // 横屏时，对1963不改变扫描方向！竖屏时1963改变方向
    {
        switch (dir) // 方向转换
        {
        case 0:
            dir = 6;
            break;
        case 1:
            dir = 7;
            break;
        case 2:
            dir = 4;
            break;
        case 3:
            dir = 5;
            break;
        case 4:
            dir = 1;
            break;
        case 5:
            dir = 0;
            break;
        case 6:
            dir = 3;
            break;
        case 7:
            dir = 2;
            break;
        }
    }
    if (lcddev.id == 0x9341 || lcddev.id == 0X5310 || lcddev.id == 0X5510 || lcddev.id == 0X1963) // 9341/5310/5510/1963,特殊处理
    {
        switch (dir)
        {
        case L2R_U2D: // 从左到右,从上到下
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;
        case L2R_D2U: // 从左到右,从下到上
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;
        case R2L_U2D: // 从右到左,从上到下
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;
        case R2L_D2U: // 从右到左,从下到上
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;
        case U2D_L2R: // 从上到下,从左到右
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;
        case U2D_R2L: // 从上到下,从右到左
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;
        case D2U_L2R: // 从下到上,从左到右
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;
        case D2U_R2L: // 从下到上,从右到左
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
        }
        if (lcddev.id == 0X5510)
            dirreg = 0X3600;
        else
            dirreg = 0X36;
        if ((lcddev.id != 0X5310) && (lcddev.id != 0X5510) && (lcddev.id != 0X1963))
            regval |= 0X08; // 5310/5510/1963不需要BGR
        LCD_WriteReg(dirreg, regval);
        if (lcddev.id != 0X1963) // 1963不做坐标处理
        {
            if (regval & 0X20)
            {
                if (lcddev.width < lcddev.height) // 交换X,Y
                {
                    temp = lcddev.width;
                    lcddev.width = lcddev.height;
                    lcddev.height = temp;
                }
            }
            else
            {
                if (lcddev.width > lcddev.height) // 交换X,Y
                {
                    temp = lcddev.width;
                    lcddev.width = lcddev.height;
                    lcddev.height = temp;
                }
            }
        }

    }
}

// 快速画点
// x,y:坐标
// color:颜色
static void LCD_Fast_DrawPoint(const char *pixel, int x, int y)
{
    uint16_t color = *((uint16_t *)pixel);
    if (lcddev.id == 0X81b3)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA16(x >> 8);
        LCD_WR_DATA16(x & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA16(y >> 8);
        LCD_WR_DATA16(y & 0XFF);
    }
    LCD->_u8_REG = lcddev.wramcmd;
    LCD->_u16_RAM = color;
}

// 设置LCD显示方向
// dir:0,竖屏；1,横屏
void LCD_Display_Dir(uint8_t dir)
{
    lcddev.dir = dir; // 竖屏/横屏
    if (dir == 0)     // 竖屏
    {
        lcddev.width = 240;
        lcddev.height = 240;
        if (lcddev.id == 0X81b3)
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }
    }
    else // 横屏
    {
        lcddev.width = 240;
        lcddev.height = 240;
        if (lcddev.id == 0X81b3)
        {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }
    }
    // TODO scan dir settings
    // LCD_Scan_Dir(DFT_SCAN_DIR); //默认扫描方向
}

rt_err_t lcd_write_half_word(const rt_uint16_t da)
{

    LCD_WR_DATA16(change_byte_order(da));
    return RT_EOK;
}

rt_err_t lcd_write_data_buffer(const void *send_buf, rt_size_t length)
{
    uint8_t *pdata = RT_NULL;
    rt_size_t len = 0;

    pdata = (uint8_t*)send_buf;
    len = length;

    if (pdata != RT_NULL)
    {
        while (len -- )
        {
            LCD_WR_DATA8(*pdata);
            pdata ++;
        }
    }
    return RT_EOK;
}

/**
 * Set background color and foreground color
 *
 * @param   back    background color
 * @param   fore    fore color
 *
 * @return  void
 */
void lcd_set_color(rt_uint16_t back, rt_uint16_t fore)
{
    BACK_COLOR = back;
    FORE_COLOR = fore;
}

/**
 * Set drawing area
 *
 * @param   x1      start of x position
 * @param   y1      start of y position
 * @param   x2      end of x position
 * @param   y2      end of y position
 *
 * @return  void
 */
void lcd_address_set(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2)
{
    if (lcddev.id == 0X81b3) // st7789v3
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA8(x1 >> 8);
        LCD_WR_DATA8(x1 & 0xff);
        LCD_WR_DATA8(x2 >> 8);
        LCD_WR_DATA8(x2 & 0xff);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA8(y1 >> 8);
        LCD_WR_DATA8(y1 & 0xff);
        LCD_WR_DATA8(y2 >> 8);
        LCD_WR_DATA8(y2 & 0xff);
    }
    LCD_WriteRAM_Prepare();      // 开始写入GRAM
}

/**
 * clear the lcd.
 *
 * @param   color       Fill color
 *
 * @return  void
 */
void lcd_clear(rt_uint16_t color)
{
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;
    totalpoint *= lcddev.height; // 得到总点数
    LCD_SetCursor(0x00, 0x0000); // 设置光标位置
    LCD_WriteRAM_Prepare();      // 开始写入GRAM
    for (index = 0; index < totalpoint; index++)
    {
        LCD->_u16_RAM = color;
    }
}

/**
 * display a point on the lcd.
 *
 * @param   x   x position
 * @param   y   y position
 *
 * @return  void
 */
void lcd_draw_point(rt_uint16_t x, rt_uint16_t y)
{
    lcd_address_set(x, y, x, y);
    lcd_write_half_word(BLUE);
}

rt_uint16_t change_byte_order(rt_uint16_t word)
{
    return ((word<<8)&0xff00) | ((word>>8)&0x00ff);
}

/**
 * full color on the lcd.
 *
 * @param   x_start     start of x position
 * @param   y_start     start of y position
 * @param   x_end       end of x position
 * @param   y_end       end of y position
 * @param   color       Fill color
 *
 * @return  void
 */
void lcd_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint16_t color)
{
    rt_uint16_t i = 0, j = 0;
    rt_uint32_t size = 0, size_remain = 0;
    rt_uint8_t *fill_buf = RT_NULL;

    size = (x_end - x_start) * (y_end - y_start) * 2;

    if (size > LCD_CLEAR_SEND_NUMBER)
    {
        /* the number of remaining to be filled */
        size_remain = size - LCD_CLEAR_SEND_NUMBER;
        size = LCD_CLEAR_SEND_NUMBER;
    }

    lcd_address_set(x_start, y_start, x_end, y_end);

    fill_buf = (rt_uint8_t *)rt_malloc(size);
    if (fill_buf)
    {
        /* fast fill */
        while (1)
        {
            for (i = 0; i < size / 2; i++)
            {
                fill_buf[2 * i] = color >> 8;
                fill_buf[2 * i + 1] = color;
            }
            lcd_write_data_buffer(fill_buf, size);

            /* Fill completed */
            if (size_remain == 0)
                break;

            /* calculate the number of fill next time */
            if (size_remain > LCD_CLEAR_SEND_NUMBER)
            {
                size_remain = size_remain - LCD_CLEAR_SEND_NUMBER;
            }
            else
            {
                size = size_remain;
                size_remain = 0;
            }
        }
        rt_free(fill_buf);
    }
    else
    {
        for (i = y_start; i <= y_end; i++)
        {
            for (j = x_start; j <= x_end; j++)lcd_write_half_word(color);
        }
    }
}

/**
 * display a line on the lcd.
 *
 * @param   x1      x1 position
 * @param   y1      y1 position
 * @param   x2      x2 position
 * @param   y2      y2 position
 *
 * @return  void
 */
void lcd_draw_line(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2)
{
    rt_uint16_t t;
    rt_uint32_t i = 0;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;

    if (y1 == y2)
    {
        /* fast draw transverse line */
        lcd_address_set(x1, y1, x2, y2);

        rt_uint8_t line_buf[480] = {0};

        for (i = 0; i < x2 - x1; i++)
        {
            line_buf[2 * i] = FORE_COLOR >> 8;
            line_buf[2 * i + 1] = FORE_COLOR;
        }

        lcd_write_data_buffer(line_buf, (x2 - x1) * 2);

        return ;
    }

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    row = x1;
    col = y1;
    if (delta_x > 0)incx = 1;
    else if (delta_x == 0)incx = 0;
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0;
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)distance = delta_x;
    else distance = delta_y;
    for (t = 0; t <= distance + 1; t++)
    {
        lcd_draw_point(row, col);
        xerr += delta_x ;
        yerr += delta_y ;
        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

/**
 * display a rectangle on the lcd.
 *
 * @param   x1      x1 position
 * @param   y1      y1 position
 * @param   x2      x2 position
 * @param   y2      y2 position
 *
 * @return  void
 */
void lcd_draw_rectangle(rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2)
{
    lcd_draw_line(x1, y1, x2, y1);
    lcd_draw_line(x1, y1, x1, y2);
    lcd_draw_line(x1, y2, x2, y2);
    lcd_draw_line(x2, y1, x2, y2);
}

/**
 * display a circle on the lcd.
 *
 * @param   x       x position of Center
 * @param   y       y position of Center
 * @param   r       radius
 *
 * @return  void
 */
void lcd_draw_circle(rt_uint16_t x0, rt_uint16_t y0, rt_uint8_t r)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);
    while (a <= b)
    {
        lcd_draw_point(x0 - b, y0 - a);
        lcd_draw_point(x0 + b, y0 - a);
        lcd_draw_point(x0 - a, y0 + b);
        lcd_draw_point(x0 - b, y0 - a);
        lcd_draw_point(x0 - a, y0 - b);
        lcd_draw_point(x0 + b, y0 + a);
        lcd_draw_point(x0 + a, y0 - b);
        lcd_draw_point(x0 + a, y0 + b);
        lcd_draw_point(x0 - b, y0 + a);
        a++;
        //Bresenham
        if (di < 0)di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
        lcd_draw_point(x0 + a, y0 + b);
    }
}

static void lcd_show_char(rt_uint16_t x, rt_uint16_t y, rt_uint8_t data, rt_uint32_t size)
{
    rt_uint8_t temp;
    rt_uint8_t num = 0;;
    rt_uint8_t pos, t;
    rt_uint16_t colortemp = FORE_COLOR;
    rt_uint8_t *font_buf = RT_NULL;

    if (x > LCD_W - size / 2 || y > LCD_H - size)return;

    data = data - ' ';
#ifdef ASC2_1608
    if (size == 16)
    {
        lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);//(x,y,x+8-1,y+16-1)

        font_buf = (rt_uint8_t *)rt_malloc(size * size);
        if (!font_buf)
        {
            /* fast show char */
            for (pos = 0; pos < size * (size / 2) / 8; pos++)
            {
                temp = asc2_1608[(rt_uint16_t)data * size * (size / 2) / 8 + pos];
                for (t = 0; t < 8; t++)
                {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    lcd_write_half_word(colortemp);
                    temp <<= 1;
                }
            }
        }
        else
        {
            for (pos = 0; pos < size * (size / 2) / 8; pos++)
            {
                temp = asc2_1608[(rt_uint16_t)data * size * (size / 2) / 8 + pos];
                for (t = 0; t < 8; t++)
                {
                    if (temp & 0x80)colortemp = FORE_COLOR;
                    else colortemp = BACK_COLOR;
                    font_buf[2 * (8 * pos + t)] = colortemp >> 8;
                    font_buf[2 * (8 * pos + t) + 1] = colortemp;
                    temp <<= 1;
                }
            }
            lcd_write_data_buffer(font_buf, size * size);
            rt_free(font_buf);
        }
    }
    else
#endif

#ifdef ASC2_2412
        if (size == 24)
        {
            lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);

            font_buf = (rt_uint8_t *)rt_malloc(size * size);
            if (!font_buf)
            {
                /* fast show char */
                for (pos = 0; pos < (size * 16) / 8; pos++)
                {
                    temp = asc2_2412[(rt_uint16_t)data * (size * 16) / 8 + pos];
                    if (pos % 2 == 0)
                    {
                        num = 8;
                    }
                    else
                    {
                        num = 4;
                    }

                    for (t = 0; t < num; t++)
                    {
                        if (temp & 0x80)colortemp = FORE_COLOR;
                        else colortemp = BACK_COLOR;
                        lcd_write_half_word(colortemp);
                        temp <<= 1;
                    }
                }
            }
            else
            {
                for (pos = 0; pos < (size * 16) / 8; pos++)
                {
                    temp = asc2_2412[(rt_uint16_t)data * (size * 16) / 8 + pos];
                    if (pos % 2 == 0)
                    {
                        num = 8;
                    }
                    else
                    {
                        num = 4;
                    }

                    for (t = 0; t < num; t++)
                    {
                        if (temp & 0x80)colortemp = FORE_COLOR;
                        else colortemp = BACK_COLOR;
                        if (num == 8)
                        {
                            font_buf[2 * (12 * (pos / 2) + t)] = colortemp >> 8;
                            font_buf[2 * (12 * (pos / 2) + t) + 1] = colortemp;
                        }
                        else
                        {
                            font_buf[2 * (8 + 12 * (pos / 2) + t)] = colortemp >> 8;
                            font_buf[2 * (8 + 12 * (pos / 2) + t) + 1] = colortemp;
                        }
                        temp <<= 1;
                    }
                }
                lcd_write_data_buffer(font_buf, size * size);
                rt_free(font_buf);
            }
        }
        else
#endif

#ifdef ASC2_3216
            if (size == 32)
            {
                lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);

                font_buf = (rt_uint8_t *)rt_malloc(size * size);
                if (!font_buf)
                {
                    /* fast show char */
                    for (pos = 0; pos < size * (size / 2) / 8; pos++)
                    {
                        temp = asc2_3216[(rt_uint16_t)data * size * (size / 2) / 8 + pos];
                        for (t = 0; t < 8; t++)
                        {
                            if (temp & 0x80)colortemp = FORE_COLOR;
                            else colortemp = BACK_COLOR;
                            lcd_write_half_word(colortemp);
                            temp <<= 1;
                        }
                    }
                }
                else
                {
                    for (pos = 0; pos < size * (size / 2) / 8; pos++)
                    {
                        temp = asc2_3216[(rt_uint16_t)data * size * (size / 2) / 8 + pos];
                        for (t = 0; t < 8; t++)
                        {
                            if (temp & 0x80)colortemp = FORE_COLOR;
                            else colortemp = BACK_COLOR;
                            font_buf[2 * (8 * pos + t)] = colortemp >> 8;
                            font_buf[2 * (8 * pos + t) + 1] = colortemp;
                            temp <<= 1;
                        }
                    }
                    lcd_write_data_buffer(font_buf, size * size);
                    rt_free(font_buf);
                }
            }
            else
#endif
            {
                LOG_E("There is no any define ASC2_1208 && ASC2_2412 && ASC2_2416 && ASC2_3216 !");
            }
}

/**
 * display the number on the lcd.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   num     number
 * @param   len     length of number
 * @param   size    size of font
 *
 * @return  void
 */
void lcd_show_num(rt_uint16_t x, rt_uint16_t y, rt_uint32_t num, rt_uint8_t len, rt_uint32_t size)
{
    lcd_show_string(x, y, size, "%d", num);
}

/**
 * display the string on the lcd.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   size    size of font
 * @param   p       the string to be display
 *
 * @return   0: display success
 *          -1: size of font is not support
 */
rt_err_t lcd_show_string(rt_uint16_t x, rt_uint16_t y, rt_uint32_t size, const char *fmt, ...)
{
#define LCD_STRING_BUF_LEN 128

    va_list args;
    rt_uint8_t buf[LCD_STRING_BUF_LEN] = {0};
    rt_uint8_t *p = RT_NULL;

    if (size != 16 && size != 24 && size != 32)
    {
        LOG_E("font size(%d) is not support!", size);
        return -RT_ERROR;
    }

    va_start(args, fmt);
    rt_vsnprintf((char *)buf, 100, (const char *)fmt, args);
    va_end(args);

    p = buf;
    while (*p != '\0')
    {
        if (x > LCD_W - size / 2)
        {
            x = 0;
            y += size;
        }
        if (y > LCD_H - size)
        {
            y = x = 0;
            lcd_clear(RED);
        }
        lcd_show_char(x, y, *p, size);
        x += size / 2;
        p++;
    }

    return RT_EOK;
}

/**
 * display the image on the lcd.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   length  length of image
 * @param   wide    wide of image
 * @param   p       image
 *
 * @return   0: display success
 *          -1: the image is too large
 */
rt_err_t lcd_show_image(rt_uint16_t x, rt_uint16_t y, rt_uint16_t length, rt_uint16_t wide, const rt_uint8_t *p)
{
    RT_ASSERT(p);

    if (x + length > LCD_W || y + wide > LCD_H)
    {
        return -RT_ERROR;
    }

    lcd_address_set(x, y, x + length - 1, y + wide - 1);

    lcd_write_data_buffer(p, length * wide * 2);

    return RT_EOK;
}

#ifdef PKG_USING_QRCODE
QRCode qrcode;

static rt_uint8_t get_enlargement_factor(rt_uint16_t x, rt_uint16_t y, rt_uint8_t size)
{
    rt_uint8_t enlargement_factor = 1 ;

    if (x + size * 8 <= LCD_W && y + size * 8 <= LCD_H)
    {
        enlargement_factor = 8;
    }
    else if (x + size * 4 <= LCD_W &&y + size * 4 <= LCD_H)
    {
        enlargement_factor = 4;
    }
    else if (x + size * 2 <= LCD_W && y + size * 2 <= LCD_H)
    {
        enlargement_factor = 2;
    }

    return enlargement_factor;
}

static void show_qrcode_by_point(rt_uint16_t x, rt_uint16_t y, rt_uint8_t size, rt_uint8_t enlargement_factor)
{
    rt_uint32_t width = 0, high = 0;
    for (high = 0; high < size; high++)
    {
        for (width = 0; width < size; width++)
        {
            if (qrcode_getModule(&qrcode, width, high))
            {
                /* magnify pixel */
                for (rt_uint32_t offset_y = 0; offset_y < enlargement_factor; offset_y++)
                {
                    for (rt_uint32_t offset_x = 0; offset_x < enlargement_factor; offset_x++)
                    {
                        lcd_draw_point(x + enlargement_factor * width + offset_x, y + enlargement_factor * high + offset_y);
                    }
                }
            }
        }
    }
}

static void show_qrcode_by_line(rt_uint16_t x, rt_uint16_t y, rt_uint8_t size, rt_uint8_t enlargement_factor,rt_uint8_t *qrcode_buf)
{
    rt_uint32_t width = 0, high = 0;
    for (high = 0; high < qrcode.size; high++)
    {
        for (width = 0; width < qrcode.size; width++)
        {
            if (qrcode_getModule(&qrcode, width, high))
            {
                /* magnify pixel */
                for (rt_uint32_t offset_y = 0; offset_y < enlargement_factor; offset_y++)
                {
                    for (rt_uint32_t offset_x = 0; offset_x < enlargement_factor; offset_x++)
                    {
                        /* save the information of modules */
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor)] = FORE_COLOR >> 8;
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor) + 1] = FORE_COLOR;
                    }
                }
            }
            else
            {
                /* magnify pixel */
                for (rt_uint32_t offset_y = 0; offset_y < enlargement_factor; offset_y++)
                {
                    for (rt_uint32_t offset_x = 0; offset_x < enlargement_factor; offset_x++)
                    {
                        /* save the information of blank */
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor)] = BACK_COLOR >> 8;
                        qrcode_buf[2 * (enlargement_factor * width + offset_x + offset_y * qrcode.size * enlargement_factor) + 1] = BACK_COLOR;
                    }
                }
            }
        }
        /* display a line of qrcode */
        lcd_show_image(x, y + high * enlargement_factor, qrcode.size * enlargement_factor, enlargement_factor, qrcode_buf);
    }
}

/**
 * display the qrcode on the lcd.
 * size = (4 * version +17) * enlargement
 *
 * @param   x           x position
 * @param   y           y position
 * @param   version     version of qrcode
 * @param   ecc         level of error correction
 * @param   data        string
 * @param   enlargement enlargement_factor
 *
 * @return   0: display success
 *          -1: generate qrcode failed
*           -5: memory low
 */
rt_err_t lcd_show_qrcode(rt_uint16_t x, rt_uint16_t y, rt_uint8_t version, rt_uint8_t ecc, const char *data, rt_uint8_t enlargement)
{
    RT_ASSERT(data);

    rt_int8_t result = 0;
    rt_uint8_t enlargement_factor = 1;
    rt_uint8_t *qrcode_buf = RT_NULL;

    if (x + version * 4 + 17 > LCD_W || y + version * 4 + 17 > LCD_H)
    {
        LOG_E("The qrcode is too big!");
        return -RT_ERROR;
    }

    rt_uint8_t *qrcodeBytes = (rt_uint8_t *)rt_calloc(1, qrcode_getBufferSize(version));
    if (qrcodeBytes == RT_NULL)
    {
        LOG_E("no memory for qrcode!");
        return -RT_ENOMEM;
    }

    /* generate qrcode */
    result = qrcode_initText(&qrcode, qrcodeBytes, version, ecc, data);
    if (result >= 0)
    {
        /* set enlargement factor */
        if(enlargement == 0)
        {
            enlargement_factor = get_enlargement_factor(x, y, qrcode.size);
        }
        else
        {
            enlargement_factor = enlargement;
        }

        /* malloc memory for quick display of qrcode */
        qrcode_buf = rt_malloc(qrcode.size * 2 * enlargement_factor * enlargement_factor);
        if (qrcode_buf == RT_NULL)
        {
            /* clear lcd */
            lcd_fill(x, y, x + qrcode.size, y + qrcode.size, BACK_COLOR);

            /* draw point to display qrcode */
            show_qrcode_by_point(x, y, qrcode.size, enlargement_factor);
        }
        else
        {
            /* quick display of qrcode */
            show_qrcode_by_line(x, y, qrcode.size, enlargement_factor,qrcode_buf);
        }
        result = RT_EOK;
    }
    else
    {
        LOG_E("QRCODE(%s) generate falied(%d)\n", qrstr, result);
        result = -RT_ENOMEM;
        goto __exit;
    }

__exit:
    if (qrcodeBytes)
    {
        rt_free(qrcodeBytes);
    }

    if (qrcode_buf)
    {
        rt_free(qrcode_buf);
    }

    return result;
}
#endif

void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint16_t *pixel = RT_NULL;
    rt_uint16_t cycle_y, x_offset = 0;

    pixel = (rt_uint16_t *)pcolor;

    lcd_address_set(x_start, y_start, x_end, y_end);
    for (cycle_y = y_start; cycle_y <= y_end;)
    {
        for (x_offset = 0; x_start + x_offset <= x_end; x_offset++)
        {
            LCD->_u8_RAM = (*pixel)>>8;
            LCD->_u8_RAM = *pixel++;
        }
        cycle_y++;
    }
}

void LCD_DrawLine(const char *pixel, rt_uint16_t x1, rt_uint16_t y1, rt_uint16_t x2, rt_uint16_t y2)
{
    rt_uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; // 计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;

    if (delta_x > 0)
        incx = 1; // 设置单步方向
    else if (delta_x == 0)
        incx = 0; // 垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // 水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if (delta_x > delta_y)
        distance = delta_x; // 选取基本增量坐标轴
    else
        distance = delta_y;

    for (t = 0; t <= distance + 1; t++) // 画线输出
    {
        // LCD_DrawPoint(uRow, uCol); //画点
        LCD_Fast_DrawPoint(pixel, uRow, uCol);
        xerr += delta_x;
        yerr += delta_y;

        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}
void LCD_HLine(const char *pixel, int x1, int x2, int y)
{
    LCD_DrawLine(pixel, x1, y, x2, y);
}

void LCD_VLine(const char *pixel, int x, int y1, int y2)
{
    LCD_DrawLine(pixel, x, y1, x, y2);
}

void LCD_BlitLine(const char *pixel, int x, int y, rt_size_t size)
{
    LCD_SetCursor(x, y);
    LCD_WriteRAM_Prepare();
    uint16_t *p = (uint16_t *)pixel;
    for (; size > 0; size--, p++)
        LCD->_u16_RAM = *p;
}

int drv_lcd_init(void)
{

    SRAM_HandleTypeDef hsram1 = {0};
    FSMC_NORSRAM_TimingTypeDef read_timing = {0};
    FSMC_NORSRAM_TimingTypeDef write_timing = {0};

#ifndef BSP_USING_ONBOARD_LCD_PWM_BL
    rt_pin_mode(LCD_BL, PIN_MODE_OUTPUT);
#endif /* BSP_USING_ONBOARD_LCD_PWM_BL */

    rt_pin_mode(LCD_RST, PIN_MODE_OUTPUT);

    rt_pin_write(LCD_RST, PIN_LOW);
    rt_thread_mdelay(100);
    rt_pin_write(LCD_RST, PIN_HIGH);
    rt_thread_mdelay(100);
    // FSMC_NORSRAM_TimingTypeDef Timing = {0};

    /** Perform the SRAM1 memory initialization sequence
     */
    hsram1.Instance = FSMC_NORSRAM_DEVICE;
    hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    /* hsram1.Init */
    hsram1.Init.NSBank = FSMC_NORSRAM_BANK3;
    hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
    hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_8;
    hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
    hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
    hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
    hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
    hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
    hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
    hsram1.Init.PageSize = FSMC_PAGE_SIZE_NONE;
    // /* Timing */

    read_timing.AddressSetupTime = 0XF;  //地址建立时间（ADDSET）为16个HCLK 1/168M=6ns*16=96ns
    read_timing.AddressHoldTime = 0x00;  //地址保持时间（ADDHLD）模式A未用到
    read_timing.DataSetupTime = 60;         //数据保存时间为60个HCLK    =6*60=360ns
    read_timing.BusTurnAroundDuration = 0x00;
    read_timing.CLKDivision = 0x00;
    read_timing.DataLatency = 0x00;
    read_timing.AccessMode = FSMC_ACCESS_MODE_A;     //模式A


    write_timing.AddressSetupTime =9;         //地址建立时间（ADDSET）为9个HCLK =54ns
    write_timing.AddressHoldTime = 0x00;     //地址保持时间（A
    write_timing.DataSetupTime = 8;      //数据保存时间为6ns*9个HCLK=54ns
    write_timing.BusTurnAroundDuration = 0x00;
    write_timing.CLKDivision = 0x00;
    write_timing.DataLatency = 0x00;
    write_timing.AccessMode = FSMC_ACCESS_MODE_A;    //模式A

    if (HAL_SRAM_Init(&hsram1, &read_timing, &write_timing) != HAL_OK)
    {
        Error_Handler( );
    }

    rt_thread_mdelay(100);

    // 尝试st7789v3 ID的读取
    LCD_WR_REG(0X04);
    lcddev.id = LCD_RD_DATA8(); // dummy read
    lcddev.id = LCD_RD_DATA8(); // ID2
    lcddev.id = LCD_RD_DATA8(); // ID3
    lcddev.id <<= 8;
    lcddev.id |= LCD_RD_DATA8();

    LOG_I(" LCD ID:%x", lcddev.id); // 打印LCD ID
    if (lcddev.id == 0X81b3) //st7789v3
    {
        //************* Start Initial Sequence **********//
        /* Memory Data Access Control */
        LCD_WR_REG(0x36);
        LCD_WR_DATA8(0x00);
        /* RGB 5-6-5-bit  */
        LCD_WR_REG(0x3A);
        LCD_WR_DATA8(0x65);
        /* Porch Setting */
        LCD_WR_REG(0xB2);
        LCD_WR_DATA8(0x0C);
        LCD_WR_DATA8(0x0C);
        LCD_WR_DATA8(0x00);
        LCD_WR_DATA8(0x33);
        LCD_WR_DATA8(0x33);
        /*  Gate Control */
        LCD_WR_REG(0xB7);
        LCD_WR_DATA8(0x35);
        /* VCOM Setting */
        LCD_WR_REG(0xBB);
        LCD_WR_DATA8(0x37);
        /* LCM Control */
        LCD_WR_REG(0xC0);
        LCD_WR_DATA8(0x2C);
        /* VDV and VRH Command Enable */
        LCD_WR_REG(0xC2);
        LCD_WR_DATA8(0x01);
        /* VRH Set */
        LCD_WR_REG(0xC3);
        LCD_WR_DATA8(0x12);
        /* VDV Set */
        LCD_WR_REG(0xC4);
        LCD_WR_DATA8(0x20);
        /* Frame Rate Control in Normal Mode */
        LCD_WR_REG(0xC6);
        LCD_WR_DATA8(0x0F);
        /* Power Control 1 */
        LCD_WR_REG(0xD0);
        LCD_WR_DATA8(0xA4);
        LCD_WR_DATA8(0xA1);
        /* Positive Voltage Gamma Control */
        LCD_WR_REG(0xE0);
        LCD_WR_DATA8(0xD0);
        LCD_WR_DATA8(0x04);
        LCD_WR_DATA8(0x0D);
        LCD_WR_DATA8(0x11);
        LCD_WR_DATA8(0x13);
        LCD_WR_DATA8(0x2B);
        LCD_WR_DATA8(0x3F);
        LCD_WR_DATA8(0x54);
        LCD_WR_DATA8(0x4C);
        LCD_WR_DATA8(0x18);
        LCD_WR_DATA8(0x0D);
        LCD_WR_DATA8(0x0B);
        LCD_WR_DATA8(0x1F);
        LCD_WR_DATA8(0x23);
        /* Negative Voltage Gamma Control */
        LCD_WR_REG(0xE1);
        LCD_WR_DATA8(0xD0);
        LCD_WR_DATA8(0x04);
        LCD_WR_DATA8(0x0C);
        LCD_WR_DATA8(0x11);
        LCD_WR_DATA8(0x13);
        LCD_WR_DATA8(0x2C);
        LCD_WR_DATA8(0x3F);
        LCD_WR_DATA8(0x44);
        LCD_WR_DATA8(0x51);
        LCD_WR_DATA8(0x2F);
        LCD_WR_DATA8(0x1F);
        LCD_WR_DATA8(0x1F);
        LCD_WR_DATA8(0x20);
        LCD_WR_DATA8(0x23);
        /* Display Inversion On */
        LCD_WR_REG(0x21);       // 开启反色
        /* TearEffect Sync On */
        LCD_WR_REG(0x35);       // 开启TE
        LCD_WR_DATA8(0x00);     // TE 同步方式：vsync 同步
        /* Sleep Out */
        LCD_WR_REG(0x11);

        rt_thread_mdelay(120);
        /* display on */
        LCD_WR_REG(0x29);       // 开启显示
    }

    // 初始化完成以后,提速
    if (lcddev.id == 0X81b3) //st7789v3可以设置WR时序为最快
    {
        // 重新配置写时序控制寄存器的时序
        FSMC_Bank1E->BWTR[6] &= ~(0XF << 0); // 地址建立时间(ADDSET)清零
        FSMC_Bank1E->BWTR[6] &= ~(0XF << 8); // 数据保存时间清零
        FSMC_Bank1E->BWTR[6] |= 3 << 0;      // 地址建立时间(ADDSET)为3个HCLK =18ns
        FSMC_Bank1E->BWTR[6] |= 2 << 8;      // 数据保存时间(DATAST)为6ns*3个HCLK=18ns
    }
    LCD_Display_Dir(0); // 默认为横屏
#ifdef BSP_USING_ONBOARD_LCD_PWM_BL
    LCD_PWM_BackLightInit();
    LCD_BackLightSet(80);
#else
    rt_pin_write(LCD_BL, PIN_HIGH); // 开启背光
#endif /* BSP_USING_ONBOARD_LCD_PWM_BL */

    lcd_clear(WHITE);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(drv_lcd_init);

struct rt_device_graphic_ops fsmc_lcd_ops =
    {
        LCD_Fast_DrawPoint,
        LCD_ReadPoint,
        LCD_HLine,
        LCD_VLine,
        LCD_BlitLine,
};

static rt_err_t drv_lcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);
    switch (cmd)
    {
    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);

        // this needs to be replaced by the customer
        info->pixel_format = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = lcd->lcd_info.bits_per_pixel;
        info->width = lcddev.width;
        info->height = lcddev.height;
    }
    break;
    }

    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops lcd_ops =
    {
        drv_lcd_init,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        drv_lcd_control};
#endif

int drv_lcd_hw_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_device *device = &_lcd.parent;
    /* memset _lcd to zero */
    memset(&_lcd, 0x00, sizeof(_lcd));

    _lcd.lcd_info.bits_per_pixel = 16;
    _lcd.lcd_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;

    device->type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops = &lcd_ops;
#else
    device->init = NULL;
    device->control = drv_lcd_control;
#endif
    device->user_data = &fsmc_lcd_ops;
    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);

    return result;
}
INIT_DEVICE_EXPORT(drv_lcd_hw_init);

#ifdef BSP_USING_ONBOARD_LCD_TEST
void lcd_auto_fill(void *para)
{
    int num = (int)para;
    do
    {
        lcd_clear(rt_tick_get()%65535);
        rt_thread_mdelay(500);
    } while (--num);
}

#include <stdlib.h> /* atoi */
void lcd_fill_test(int argc, void **argv)
{
    static rt_uint8_t lcd_init = 0;
    rt_device_t lcd = RT_NULL;

    if (lcd_init == 0)
    {
        lcd_init = 1;

        lcd = rt_device_find("lcd");
        rt_device_init(lcd);
    }

    if (argc == 1)
    {
        lcd_auto_fill((void *)1);
    }
    else if (argc == 3)
    {
        if (rt_strcmp(argv[1], "-t") == 0)
        {
            rt_thread_t tid = RT_NULL;
            tid = rt_thread_create("lcd_fill", lcd_auto_fill, (void *)atoi(argv[2]), 512, 23, 10);
            rt_thread_startup(tid);
        }
    }
}
MSH_CMD_EXPORT(lcd_fill_test, lcd fill test for mcu lcd);
#endif
