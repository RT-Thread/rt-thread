/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-08-10     zylx              first version
 * 2022-02-01     Rudy Lo           add lcd_fill_array function
 */

#include <board.h>

#ifdef BSP_USING_SPI_LCD_ILI9488
#include <rtdevice.h>
#include "drv_spi.h"
#include "drv_spi_ili9488.h"
#include <lcd_spi_port.h>
#include "drv_lcd_font.h"
#include <rttlogo.h>
#include <string.h>

#if defined(PKG_USING_GUIENGINE)
#include <rtgui/driver.h>
#endif

#define DRV_DEBUG
#define LOG_TAG             "drv.spi_lcd"
#include <drv_log.h>

#define LCD_DC_PIN            GET_PIN(C, 7)

#define LCD_DEVICE(dev)     (struct drv_lcd_device*)(dev)

#define LCD_CLEAR_SEND_NUMBER (LCD_H * LCD_W *3)

static rt_uint32_t BACK_COLOR = WHITE, FORE_COLOR = BLACK;
static struct rt_spi_device *spi_dev_lcd;

static int rt_hw_lcd_config(void)
{
    spi_dev_lcd = (struct rt_spi_device *)rt_device_find("spi20");

    /* config spi */
    {
        struct rt_spi_configuration cfg;
        cfg.data_width = 8;
        cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
        cfg.max_hz = 50 * 1000 * 1000;

        rt_spi_configure(spi_dev_lcd, &cfg);
    }

    return RT_EOK;
}

static rt_err_t lcd_write_cmd(const rt_uint8_t cmd)
{
    rt_size_t len;

    rt_pin_write(LCD_DC_PIN, PIN_LOW);

    len = rt_spi_send(spi_dev_lcd, &cmd, 1);

    if (len != 1)
    {
        LOG_I("lcd_write_cmd error. %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

static rt_err_t lcd_write_data(const rt_uint8_t data)
{
    rt_size_t len;

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);

    len = rt_spi_send(spi_dev_lcd, &data, 1);

    if (len != 1)
    {
        LOG_I("lcd_write_data error. %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

static rt_err_t lcd_write_half_word(const rt_uint16_t da)
{
    rt_size_t len;
    char data[2] = {0};

    data[0] = da >> 8;
    data[1] = da;

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    len = rt_spi_send(spi_dev_lcd, data, 2);
    if (len != 2)
    {
        LOG_I("lcd_write_half_word error. %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

static rt_err_t lcd_write_three_bytes(const rt_uint32_t da)
{
    rt_size_t len;
    char data[3] = {0};

    data[0] = da >> 16;
    data[1] = da >> 8;
    data[2] = da;

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    len = rt_spi_send(spi_dev_lcd, data, 3);
    if (len != 3)
    {
        LOG_I("lcd_write_half_word error. %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

static void lcd_gpio_init(void)
{
    rt_hw_lcd_config();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    rt_pin_mode(LCD_DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_BL_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LCD_RES_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LCD_BL_PIN, PIN_LOW);
}

int rt_hw_spi_lcd_init(void)
{
    __HAL_RCC_GPIOI_CLK_ENABLE();
    rt_hw_spi_device_attach("spi2", "spi20", GET_PIN(I, 0));
    lcd_gpio_init();

    rt_pin_write(LCD_RES_PIN, PIN_HIGH);
    rt_thread_mdelay(10);
    rt_pin_write(LCD_RES_PIN, PIN_LOW);
    rt_thread_mdelay(50);
    rt_pin_write(LCD_RES_PIN, PIN_HIGH);
    rt_thread_mdelay(200);

    //************* Start Initial Sequence **********//
    lcd_write_cmd(0xE0);
    lcd_write_data(0x00);
    lcd_write_data(0x07);
    lcd_write_data(0x0f);
    lcd_write_data(0x0D);
    lcd_write_data(0x1B);
    lcd_write_data(0x0A);
    lcd_write_data(0x3c);
    lcd_write_data(0x78);
    lcd_write_data(0x4A);
    lcd_write_data(0x07);
    lcd_write_data(0x0E);
    lcd_write_data(0x09);
    lcd_write_data(0x1B);
    lcd_write_data(0x1e);
    lcd_write_data(0x0f);

    lcd_write_cmd(0xE1);
    lcd_write_data(0x00);
    lcd_write_data(0x22);
    lcd_write_data(0x24);
    lcd_write_data(0x06);
    lcd_write_data(0x12);
    lcd_write_data(0x07);
    lcd_write_data(0x36);
    lcd_write_data(0x47);
    lcd_write_data(0x47);
    lcd_write_data(0x06);
    lcd_write_data(0x0a);
    lcd_write_data(0x07);
    lcd_write_data(0x30);
    lcd_write_data(0x37);
    lcd_write_data(0x0f);

    lcd_write_cmd(0xC0);
    lcd_write_data(0x10);
    lcd_write_data(0x10);

    lcd_write_cmd(0xC1);
    lcd_write_data(0x41);

    lcd_write_cmd(0xC5);
    lcd_write_data(0x00);
    lcd_write_data(0x22);
    lcd_write_data(0x80);

    lcd_write_cmd(0x36);
#ifndef LCD_HOR_SCREEN
    lcd_write_data(0x48);
#else
    lcd_write_data(0x28);
#endif

    lcd_write_cmd(0x3A);   //Interface Mode Control
    lcd_write_data(0x66);

    lcd_write_cmd(0XB0);   //Interface Mode Control
    lcd_write_data(0x00);
    lcd_write_cmd(0xB1);   //Frame rate 70HZ
    lcd_write_data(0xB0);
    lcd_write_data(0x11);
    lcd_write_cmd(0xB4);
    lcd_write_data(0x02);
    lcd_write_cmd(0xB6);   //RGB/MCU Interface Control
    lcd_write_data(0x02);
    lcd_write_data(0x02);

    lcd_write_cmd(0xB7);
    lcd_write_data(0xC6);

    lcd_write_cmd(0xE9);
    lcd_write_data(0x00);

    lcd_write_cmd(0XF7);
    lcd_write_data(0xA9);
    lcd_write_data(0x51);
    lcd_write_data(0x2C);
    lcd_write_data(0x82);

    lcd_fill(0, 0, LCD_WIDTH, LCD_HEIGHT, LCD_FULL_COLOR);

    lcd_write_cmd(0x11);
    rt_thread_mdelay(120);
    lcd_write_cmd(0x29);

    rt_thread_mdelay(50);   //delay screen update to prevent screen appears white when the default color is black

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
void lcd_set_color(rt_uint32_t back, rt_uint32_t fore)
{
    BACK_COLOR = back;
    FORE_COLOR = fore;
}

void lcd_display_on(void)
{
    rt_pin_write(LCD_BL_PIN, PIN_HIGH);
}

void lcd_display_off(void)
{
    rt_pin_write(LCD_BL_PIN, PIN_LOW);
}

/* lcd enter the minimum power consumption mode and backlight off. */
void lcd_enter_sleep(void)
{
    lcd_display_off();
    rt_thread_mdelay(5);
    lcd_write_cmd(0x28);
    rt_thread_mdelay(10);
    lcd_write_cmd(0x10);
    rt_thread_mdelay(120);
}
/* lcd turn off sleep mode and backlight on. */
void lcd_exit_sleep(void)
{
    lcd_display_on();
    rt_thread_mdelay(5);
    lcd_write_cmd(0x11);
    rt_thread_mdelay(120);
    lcd_write_cmd(0x29);
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
    lcd_write_cmd(0x2a);
    lcd_write_data(x1 >> 8);
    lcd_write_data(x1);
    lcd_write_data(x2 >> 8);
    lcd_write_data(x2);

    lcd_write_cmd(0x2b);
    lcd_write_data(y1 >> 8);
    lcd_write_data(y1);
    lcd_write_data(y2 >> 8);
    lcd_write_data(y2);

    lcd_write_cmd(0x2C);
}

/**
 * clear the lcd.
 *
 * @param   color       Fill color
 *
 * @return  void
 */
void lcd_clear(rt_uint32_t color)
{
    rt_uint32_t i, j;
    rt_uint8_t data[3] = {0};
    rt_uint8_t *buf = RT_NULL;

    data[0] = color >> 16;
    data[1] = color >> 8;
    data[2] = color;
    lcd_address_set(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    buf = rt_malloc(LCD_BUF_SIZE);
    if (buf)
    {
        /* color is 16 bit */
        for (j = 0; j < LCD_BUF_SIZE / 3; j++)
        {
            buf[j * 3] =  data[0];
            buf[j * 3 + 1] =  data[1];
            buf[j * 3 + 2] =  data[2];
        }

        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        rt_spi_send(spi_dev_lcd, buf, LCD_BUF_SIZE);
        rt_free(buf);
    }
    else
    {
        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        for (i = 0; i < LCD_WIDTH; i++)
        {
            for (j = 0; j < LCD_HEIGHT; j++)
            {
                rt_spi_send(spi_dev_lcd, data, 3);
            }
        }
    }
}

/**
 * display a point on the lcd using the given colour.
 *
 * @param   x       x position
 * @param   y       y position
 * @param   color   color of point
 *
 * @return  void
 */
void lcd_draw_point_color(rt_uint16_t x, rt_uint16_t y, rt_uint32_t color)
{
    lcd_address_set(x, y, x, y);
    lcd_write_three_bytes(color);
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
    lcd_draw_point_color(x, y, FORE_COLOR);
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
void lcd_fill(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, rt_uint32_t color)
{
    rt_uint32_t i = 0, j = 0;
    rt_uint32_t size = 0, size_remain = 0;
    rt_uint8_t *fill_buf = RT_NULL;

    size = (x_end - x_start) * (y_end - y_start) * 3;

    if (size > LCD_CLEAR_SEND_NUMBER)
    {
        /* the number of remaining to be filled */
        size_remain = size - LCD_CLEAR_SEND_NUMBER;
        size = LCD_CLEAR_SEND_NUMBER;
    }

    lcd_address_set(x_start, y_start, x_end, y_end);

    fill_buf = (rt_uint8_t *)rt_malloc(LCD_CLEAR_SEND_NUMBER);
    if (fill_buf)
    {
        /* fast fill */
        while (1)
        {
            for (i = 0; i < size / 3; i++)
            {
                fill_buf[3 * i] = color >> 16;
                fill_buf[3 * i + 1] = color >> 8;
                fill_buf[3 * i + 2] = color;
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, fill_buf, size);

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
            for (j = x_start; j <= x_end; j++)lcd_write_three_bytes(color);
        }
    }
}

/**
 * full color array on the lcd.
 *
 * @param   x_start     start of x position
 * @param   y_start     start of y position
 * @param   x_end       end of x position
 * @param   y_end       end of y position
 * @param   pcolor      Fill color array's pointer
 *
 * @return  void
 */
void lcd_fill_array(rt_uint16_t x_start, rt_uint16_t y_start, rt_uint16_t x_end, rt_uint16_t y_end, void *pcolor)
{
    rt_uint32_t size = 0;
    rt_uint8_t *array = RT_NULL;

    size = (x_end - x_start + 1) * (y_end - y_start + 1) * 3 /* 24bit */;
    array = (rt_uint8_t *)rt_malloc(size);

    if (!array) {
        LOG_E("not enough memory");
        return ;
    }

    rt_uint32_t *color_p = (rt_uint32_t *)pcolor;

    for (rt_uint16_t i = 0; i < size / 3; i++)
    {
        array[3 * i] = *color_p >> 16;
        array[3 * i + 1] = *color_p >> 8;
        array[3 * i + 2] = *color_p;
        color_p++;
    }

    lcd_address_set(x_start, y_start, x_end, y_end);
    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    rt_spi_send(spi_dev_lcd, array, size);

    rt_free(array);
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

        rt_uint8_t line_buf[960] = {0};

        for (i = 0; i < x2 - x1; i++)
        {
            line_buf[3 * i] = FORE_COLOR >> 16;
            line_buf[3 * i + 1] = FORE_COLOR >> 8;
            line_buf[3 * i + 2] = FORE_COLOR;
        }

        rt_pin_write(LCD_DC_PIN, PIN_HIGH);
        rt_spi_send(spi_dev_lcd, line_buf, (x2 - x1) * 3);

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
    rt_uint32_t colortemp = FORE_COLOR;
    rt_uint8_t *font_buf = RT_NULL;

    if (x > LCD_WIDTH - size / 2 || y > LCD_HEIGHT - size)return;

    data = data - ' ';
#ifdef ASC2_1608
    if (size == 16)
    {
        lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);//(x,y,x+8-1,y+16-1)

        font_buf = (rt_uint8_t *)rt_malloc(size * size / 2 * 3);
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
                    lcd_write_three_bytes(colortemp);
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
                    font_buf[3 * (8 * pos + t)] = colortemp >> 16;
                    font_buf[3 * (8 * pos + t) + 1] = colortemp >> 8;
                    font_buf[3 * (8 * pos + t) + 2] = colortemp;
                    temp <<= 1;
                }
            }
            rt_pin_write(LCD_DC_PIN, PIN_HIGH);
            rt_spi_send(spi_dev_lcd, font_buf, size * size / 2 * 3);
            rt_free(font_buf);
        }
    }
    else
#endif

#ifdef ASC2_2412
        if (size == 24)
        {
            lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);

            font_buf = (rt_uint8_t *)rt_malloc(size * size / 2 * 3);
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
                        lcd_write_three_bytes(colortemp);
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
                            font_buf[3 * (12 * (pos / 2) + t)] = colortemp >> 16;
                            font_buf[3 * (12 * (pos / 2) + t) + 1] = colortemp >> 8;
                            font_buf[3 * (12 * (pos / 2) + t) + 2] = colortemp;
                        }
                        else
                        {
                            font_buf[3 * (8 + 12 * (pos / 2) + t)] = colortemp >> 16;
                            font_buf[3 * (8 + 12 * (pos / 2) + t) + 1] = colortemp >> 8;
                            font_buf[3 * (8 + 12 * (pos / 2) + t) + 2] = colortemp;
                        }
                        temp <<= 1;
                    }
                }
                rt_pin_write(LCD_DC_PIN, PIN_HIGH);
                rt_spi_send(spi_dev_lcd, font_buf, size * size / 2 * 3);
                rt_free(font_buf);
            }
        }
        else
#endif

#ifdef ASC2_3216
            if (size == 32)
            {
                lcd_address_set(x, y, x + size / 2 - 1, y + size - 1);

                font_buf = (rt_uint8_t *)rt_malloc(size * size / 2 * 3);
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
                            lcd_write_three_bytes(colortemp);
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
                            font_buf[3 * (8 * pos + t)] = colortemp >> 16;
                            font_buf[3 * (8 * pos + t) + 1] = colortemp >> 8;
                            font_buf[3 * (8 * pos + t) + 2] = colortemp;
                            temp <<= 1;
                        }
                    }
                    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
                    rt_spi_send(spi_dev_lcd, font_buf, size * size / 2 * 3);
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
        if (x > LCD_WIDTH - size / 2)
        {
            x = 0;
            y += size;
        }
        if (y > LCD_HEIGHT - size)
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

    if (x + length > LCD_WIDTH || y + wide > LCD_HEIGHT)
    {
        return -RT_ERROR;
    }

    lcd_address_set(x, y, x + length - 1, y + wide - 1);

    rt_pin_write(LCD_DC_PIN, PIN_HIGH);
    rt_spi_send(spi_dev_lcd, p, length * wide * 3);

    return RT_EOK;
}

struct drv_lcd_device
{
    struct rt_device parent;

    struct rt_device_graphic_info lcd_info;

    struct rt_semaphore lcd_lock;

    /* 0:front_buf is being used 1: back_buf is being used*/
    rt_uint8_t cur_buf;
    rt_uint8_t *front_buf;
    rt_uint8_t *back_buf;
};

struct drv_lcd_device _lcd;

static rt_err_t drv_lcd_init(struct rt_device *device)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);
    /* nothing, right now */
    lcd = lcd;
    return RT_EOK;
}

static rt_err_t drv_lcd_control(struct rt_device *device, int cmd, void *args)
{
    struct drv_lcd_device *lcd = LCD_DEVICE(device);
    struct rt_device_rect_info *rect_info = RT_NULL;
    uint32_t data_start_addr = 0;
    uint32_t i = 0;

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
    {
        /* update */
        rect_info = (struct rt_device_rect_info *)args;
        if(rect_info != NULL)
        {
            data_start_addr = rect_info->y * LCD_BYTES_PER_PIXEL * LCD_WIDTH + rect_info->x * LCD_BYTES_PER_PIXEL;
            for(i = 0; i < rect_info->height; i++)
            {
                memcpy(&_lcd.front_buf[i * LCD_BYTES_PER_PIXEL * rect_info->width], &_lcd.lcd_info.framebuffer[data_start_addr + i * LCD_BYTES_PER_PIXEL * LCD_WIDTH], rect_info->width * LCD_BYTES_PER_PIXEL);
            }
            lcd_show_image(rect_info->x, rect_info->y, rect_info->width, rect_info->height, _lcd.front_buf);
        }
        else
        {
            memcpy(_lcd.front_buf, _lcd.lcd_info.framebuffer, LCD_BUF_SIZE);
            lcd_show_image(0, 0, LCD_WIDTH, LCD_HEIGHT, _lcd.front_buf);
        }
    }
    break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        struct rt_device_graphic_info *info = (struct rt_device_graphic_info *)args;

        RT_ASSERT(info != RT_NULL);
        info->pixel_format   = lcd->lcd_info.pixel_format;
        info->bits_per_pixel = lcd->lcd_info.bits_per_pixel;
        info->width          = lcd->lcd_info.width;
        info->height         = lcd->lcd_info.height;
        info->framebuffer    = lcd->lcd_info.framebuffer;
    }
    break;
    }

    return RT_EOK;
}

#if defined(LCD_BACKLIGHT_USING_GPIO)
void turn_on_lcd_backlight(void)
{
    rt_pin_mode(LCD_BL_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(LCD_BL_PIN, PIN_HIGH);
}
#else
void turn_on_lcd_backlight(void)
{

}
#endif

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops lcd_ops =
{
    drv_lcd_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    drv_lcd_control
};
#endif

int drv_lcd_ili9488_hw_init(void)
{
    rt_err_t result = RT_EOK;
    struct rt_device *device = &_lcd.parent;

    /* memset _lcd to zero */
    memset(&_lcd, 0x00, sizeof(_lcd));

    /* init lcd_lock semaphore */
    result = rt_sem_init(&_lcd.lcd_lock, "lcd_lock", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        LOG_E("init semaphore failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* config LCD dev info */
    _lcd.lcd_info.height = LCD_HEIGHT;
    _lcd.lcd_info.width = LCD_WIDTH;
    _lcd.lcd_info.bits_per_pixel = LCD_BITS_PER_PIXEL;
    _lcd.lcd_info.pixel_format = LCD_PIXEL_FORMAT;

    /* malloc memory for double Buffering */
    _lcd.lcd_info.framebuffer = rt_malloc(LCD_BUF_SIZE);
    _lcd.front_buf = rt_malloc(LCD_BUF_SIZE);
    if (_lcd.lcd_info.framebuffer == RT_NULL || _lcd.front_buf == RT_NULL)
    {
        LOG_E("init frame buffer failed!\n");
        result = -RT_ENOMEM;
        goto __exit;
    }

    /* memset buff to 0xFF */
    memset(_lcd.lcd_info.framebuffer, 0xFF, LCD_BUF_SIZE);
    memset(_lcd.front_buf, 0xFF, LCD_BUF_SIZE);

    device->type    = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    device->ops     = &lcd_ops;
#else
    device->init    = drv_lcd_init;
    device->control = drv_lcd_control;
#endif

    /* register lcd device */
    rt_device_register(device, "lcd", RT_DEVICE_FLAG_RDWR);

    /* init spi lcd */
    if (rt_hw_spi_lcd_init() != RT_EOK)
    {
        result = -RT_ERROR;
        goto __exit;
    }
    else
    {
        turn_on_lcd_backlight();
    }

#if defined(PKG_USING_GUIENGINE)
    rtgui_graphic_set_device(device);
#endif

__exit:
    if (result != RT_EOK)
    {
        rt_sem_detach(&_lcd.lcd_lock);

        if (_lcd.lcd_info.framebuffer)
        {
            rt_free(_lcd.lcd_info.framebuffer);
        }

        if (_lcd.back_buf)
        {
            rt_free(_lcd.back_buf);
        }

        if (_lcd.front_buf)
        {
            rt_free(_lcd.front_buf);
        }
    }
    return result;
}
INIT_COMPONENT_EXPORT(drv_lcd_ili9488_hw_init);

#ifdef DRV_DEBUG
#ifdef FINSH_USING_MSH
int ili9488_test()
{
    struct drv_lcd_device *lcd;
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");
    struct rt_device_rect_info rect_info = {0, 0, LCD_WIDTH, LCD_HEIGHT};
    uint32_t i = 0;

    lcd_clear(WHITE);

    lcd_show_image(0, 0, 240, 69, image_rttlogo);

    lcd_set_color(WHITE, BLACK);

    lcd_show_string(10, 69, 16, "Hello, RT-Thread!");
    lcd_show_string(10, 69+16, 24, "RT-Thread");
    lcd_show_string(10, 69+16+24, 32, "RT-Thread");

    lcd_draw_line(0, 69+16+24+32, LCD_H, 69+16+24+32);

    lcd_draw_point(160, 310);
    for (int i = 0; i < 150; i += 4)
    {
        lcd_draw_circle(160, 310, i);
    }

    rt_thread_mdelay(2000);

    while (1)
    {
        i += 10;
        if(i >= 120)
        {
            i = 0;
        }

        rect_info.x = i;
        rect_info.y = i;
        rect_info.width =LCD_WIDTH - 2 * i;
        rect_info.height =LCD_HEIGHT - 2 * i;

        /* red */
        for (int i = 0; i < LCD_BUF_SIZE / 3; i++)
        {
            lcd->lcd_info.framebuffer[3 * i] = 0xFF;
            lcd->lcd_info.framebuffer[3 * i + 1] = 0x00;
            lcd->lcd_info.framebuffer[3 * i + 2] = 0x00;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        rt_thread_mdelay(1000);
        /* green */
        for (int i = 0; i < LCD_BUF_SIZE / 3; i++)
        {
            lcd->lcd_info.framebuffer[3 * i] = 0x00;
            lcd->lcd_info.framebuffer[3 * i + 1] = 0xFF;
            lcd->lcd_info.framebuffer[3 * i + 2] = 0x00;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        rt_thread_mdelay(1000);
        /* blue */
        for (int i = 0; i < LCD_BUF_SIZE / 3; i++)
        {
            lcd->lcd_info.framebuffer[3 * i] = 0x00;
            lcd->lcd_info.framebuffer[3 * i + 1] = 0x00;
            lcd->lcd_info.framebuffer[3 * i + 2] = 0xFF;
        }
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        rt_thread_mdelay(1000);
    }
}
MSH_CMD_EXPORT(ili9488_test, test ili9488 driver);
#endif /* FINSH_USING_MSH */
#endif /* DRV_DEBUG */
#endif /* BSP_USING_SPI_LCD_ILI9488 */
