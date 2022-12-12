/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 */
#include <rtconfig.h>

#ifdef BSP_USING_LCD_QRCODE
#include <qrcode.h>
#include "drv_lcd.h"
#include "lcd_qrcode.h"
#define DBG_TAG    "drv.lcd.qrcode"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

static QRCode qrcode;

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
 * @param   version     version of qrcode (ECC_LOW, ECC_MEDIUM, ECC_QUARTILE or ECC_HIGH)
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
        LOG_E("QRCODE(%s) generate falied(%d)\n", data, result);
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
#endif /* BSP_USING_LCD_QRCODE */
