/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-23     Chushicheng  the first version
 */

#include "drv_spi.h"
#include "drv_st7796.h"

#define LOG_TAG             "drv.st7796"
#include <drv_log.h>

#ifndef ST7796_LCD_IPS_PANEL
#define ST7796_LCD_IPS_PANEL 1
#else
#define ST7796_LCD_IPS_PANEL 0
#endif

#define ST7796_INIT_SEQ_NAME(x) st7796_init_seq_##x##_480_320
#if ST7796_LCD_IPS_PANEL
#define ST7796_LCD_INIT_SEQ ST7796_INIT_SEQ_NAME(ips)
#else
#define ST7796_LCD_INIT_SEQ ST7796_INIT_SEQ_NAME(tft)
#endif

static st7796_t lcd_spi_obj;

static rt_err_t _st7796_init_seq(st7796_lcd_t *lcd);
static rt_err_t _st7796_window(st7796_lcd_t *lcd, rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end);
static rt_err_t _st7796_reset(st7796_lcd_t *lcd);
static rt_err_t st7796_lcd_load(st7796_lcd_t *lcd, void *data, rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end);
static rt_err_t st7796_lcd_sleep(st7796_lcd_t *lcd, rt_uint8_t sleep_mode);
static rt_err_t st7796_lcd_display(st7796_lcd_t *lcd, rt_uint8_t display_on);
static rt_err_t st7796_lcd_config(st7796_lcd_t *lcd, st7796_config_t *config);
void lcd_load(rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end, void *data);

static rt_uint8_t st7796_init_seq_tft_480_320[] =
{
    0x01, 0xF0, 0xC3,                                            /* Enable command part 1 */
    0x01, 0xF0, 0x96,                                            /* Enable command part 2*/
    0x08, 0xE8, 0x40, 0x82, 0x07, 0x18, 0x27, 0x0A, 0xB6, 0x33,  /* DOCA */
    0x01, 0xC5, 0x27,                                            /* VCOM control */
    0x01, 0xC2, 0xA7,                                            /* Power control 3 */
    0x0E, 0xE0, 0xF0, 0x01, 0x06, 0x0F, 0x12, 0x1D, 0x36, 0x54, 0x44, 0x0C, 0x18, 0x16, 0x13, 0x15,  /* PGC */
    0x0E, 0xE1, 0xF0, 0x01, 0x05, 0x0A, 0x0B, 0x07, 0x32, 0x44, 0x44, 0x0C, 0x18, 0x17, 0x13, 0x16,  /* NGC */
    0x01, 0xF0, 0x3C,  /* Disable command part 1 */
    0x01, 0xF0, 0x69,  /* Disable command part 2 */
};

static rt_uint8_t st7796_init_seq_ips_480_320[] =
{
    0x01, 0xF0, 0xC3,                                            /* Enable command part 1 */
    0x01, 0xF0, 0x96,                                            /* Enable command part 2 */
    0x01, 0xB4, 0x01,                                            /* Display inversion */
    0x02, 0xB1, 0x80, 0x10,                                      /* Frame rate control 1 */
    0x04, 0xB5, 0x1F, 0x50, 0x00, 0x20,                          /* Blanking porch control */
    0x03, 0xB6, 0x8A, 0x07, 0x3B,                                /* Display function control */
    0x02, 0xC0, 0x80, 0x64,                                      /* Power control 1 */
    0x01, 0xC1, 0x13,                                            /* Power control 2 */
    0x01, 0xC2, 0xA7,                                            /* Power control 3 */
    0x01, 0xC5, 0x09,                                            /* VCOM control */
    0x08, 0xE8, 0x40, 0x8A, 0x00, 0x00, 0x29, 0x19, 0xA5, 0x33,  /* DOCA */
    0x0E, 0xE0, 0xF0, 0x06, 0x0B, 0x07, 0x06, 0x05, 0x2E, 0x33, 0x47, 0x3A, 0x17, 0x16, 0x2E, 0x31,  /* PGC */
    0x0E, 0xE1, 0xF0, 0x09, 0x0D, 0x09, 0x08, 0x23, 0x2E, 0x33, 0x46, 0x38, 0x13, 0x13, 0x2C, 0x32,  /* NGC */
    0x01, 0xF0, 0x3C,  /* Disable command part 1 */
    0x01, 0xF0, 0x69,  /* Disable command part 2 */
};

static rt_err_t _st7796_init_seq(st7796_lcd_t *lcd)
{
    rt_uint16_t i = 0;

    while (i < sizeof(ST7796_LCD_INIT_SEQ))
    {
        if (lcd->cb.write_cmd_cb(lcd->user_data, &ST7796_LCD_INIT_SEQ[i + 1], ST7796_LCD_INIT_SEQ[i] + 1) != RT_EOK)
        {
            return -RT_ERROR;
        };
        i += ST7796_LCD_INIT_SEQ[i] + 2;
    }

    return RT_EOK;
}

static rt_err_t _st7796_window(st7796_lcd_t *lcd, rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end)
{
    rt_uint16_t real_x_start, real_x_end, real_y_start, real_y_end;
    rt_uint16_t x_offset, y_offset;
    switch (lcd->config.direction)
    {
        case ST7796_DIR_0:
            x_offset = 0;
            y_offset = 0;
            break;
        case ST7796_DIR_90:
            x_offset = 0;
            y_offset = 0;
            break;
        case ST7796_DIR_180:
            x_offset = 320;
            y_offset = 480;
            break;
        case ST7796_DIR_270:
            x_offset = 480;
            y_offset = 320;
            break;
        default:
            x_offset = 0;
            y_offset = 0;
    }
    real_x_start = x_start + x_offset;
    real_x_end   = x_end + x_offset;
    real_y_start = y_start + y_offset;
    real_y_end   = y_end + y_offset;

    rt_uint8_t tx_buf[5] = {0x2A, ((rt_uint8_t)(real_x_start >> 0x08U) & 0xFFU), (real_x_start & 0xFFU),
                         ((rt_uint8_t)(real_x_end >> 0x08U) & 0xFFU), (real_x_end & 0xFFU)};

    if (lcd->cb.write_cmd_cb(lcd->user_data, tx_buf, 0x05) != RT_EOK)
    {
        return -RT_ERROR;
    }
    tx_buf[0] = 0x2B;
    tx_buf[1] = ((rt_uint8_t)(real_y_start >> 0x08U) & 0xFFU);
    tx_buf[2] = (real_y_start & 0xFFU);
    tx_buf[3] = ((rt_uint8_t)(real_y_end >> 0x08U) & 0xFFU);
    tx_buf[4] = (real_y_end & 0xFFU);
    if (lcd->cb.write_cmd_cb(lcd->user_data, tx_buf, 0x05) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t _st7796_reset(st7796_lcd_t *lcd)
{
    return lcd->cb.reset_cb(lcd->user_data);
}

static rt_err_t lcd_impl_reset(void *handle)
{
    rt_pin_write(BSP_LCD_RST_PIN, PIN_LOW);
    rt_thread_mdelay(50);
    rt_pin_write(BSP_LCD_RST_PIN, PIN_HIGH);
    rt_thread_mdelay(50);

    return RT_EOK;
}

static rt_err_t st7796_lcd_init(st7796_lcd_t *lcd)
{
    if (_st7796_reset(lcd) != RT_EOK) return -RT_ERROR;
    if (_st7796_init_seq(lcd) != RT_EOK) return -RT_ERROR;
    if (st7796_lcd_config(lcd, &lcd->config) != RT_EOK) return -RT_ERROR;
    if (st7796_lcd_sleep(lcd, 0) != RT_EOK) return -RT_ERROR;
    if (st7796_lcd_display(lcd, 1) != RT_EOK) return -RT_ERROR;

    return RT_EOK;
}

static rt_err_t st7796_lcd_load(st7796_lcd_t *lcd, void *data, rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end)
{
    rt_uint32_t pixel_count = (y_end - y_start + 1) * (x_end - x_start + 1);
    rt_uint32_t data_len = 0;

    switch (lcd->config.pix_fmt)
    {
        case ST7796_RGB444:
            data_len = pixel_count * 3 / 2;
            break;
        case ST7796_RGB565:
            data_len = pixel_count * 2;
            break;
        case ST7796_RGB666:
        case ST7796_RGB888:
            data_len = pixel_count * 3;
            break;
        default:
            data_len = pixel_count;
            break;
    }

    /* Set cursor */
    if (_st7796_window(lcd, x_start, x_end, y_start, y_end) != RT_EOK)
    {
        return -RT_ERROR;
    }

    rt_uint8_t command = 0x2C;  /* Memory Write */
    if (lcd->cb.write_cmd_cb(lcd->user_data, &command, 0x01) != RT_EOK)
    {
        return -RT_ERROR;
    }
    /* Write pixel data */
    if (lcd->cb.write_data_cb(lcd->user_data, data, data_len) != RT_EOK)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

void lcd_load(rt_uint16_t x_start, rt_uint16_t x_end, rt_uint16_t y_start, rt_uint16_t y_end, void *data)
{
    st7796_t *lcd_obj = (st7796_t *)rt_device_find("lcd");
    st7796_lcd_load(&lcd_obj->st7796, data, x_start, x_end, y_start, y_end);
}

static rt_err_t st7796_lcd_sleep(st7796_lcd_t *lcd, rt_uint8_t sleep_mode)
{
    /* Write SLPIN or SLPOUT command */
    rt_uint8_t command = sleep_mode ? 0x10 : 0x11;
    return lcd->cb.write_cmd_cb(lcd->user_data, &command, 0x01);
}

static rt_err_t st7796_lcd_display(st7796_lcd_t *lcd, rt_uint8_t display_on)
{
    /* write display_on command */
    rt_uint8_t command = display_on ? 0x29 : 0x28;
    if (lcd->cb.write_cmd_cb(lcd->user_data, &command, 0x01) != RT_EOK)
    {
        return -RT_ERROR;
    }
    if ((lcd->cb.backlight_cb != NULL) && (lcd->cb.backlight_cb(lcd->user_data, display_on) != RT_EOK))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t st7796_lcd_config(st7796_lcd_t *lcd, st7796_config_t *config)
{
    lcd->config.direction = config->direction;

    /* Write inversion command */
    rt_uint8_t command[2] = {config->inversion ? 0x20 : 0x21, 0x00};
    if (lcd->cb.write_cmd_cb(lcd->user_data, command, 0x01) != RT_EOK)
    {
        return -RT_ERROR;
    }
    lcd->config.inversion = config->inversion;

    command[0] = 0x3A;
    command[1] = config->pix_fmt;
    if (lcd->cb.write_cmd_cb(lcd->user_data, command, 0x02) != RT_EOK)
    {
        return -RT_ERROR;
    }
    lcd->config.pix_fmt = config->pix_fmt;

    command[0] = 0x36;
    command[1] = config->direction;
    if (!config->bgr_mode)
    {
        command[1] &= ~0x08U;
    }

    if (config->mirrored)
    {
        /* Invert X or Y bit */
        if (config->direction == ST7796_DIR_90 || config->direction == ST7796_DIR_270)
        {
            command[1] ^= 0x80U;
        }
        else
        {
            command[1] ^= 0x40U;
        }
    }

    return lcd->cb.write_cmd_cb(lcd->user_data, command, 0x02);
}

static rt_err_t lcd_impl_write_cmd(void *handle, rt_uint8_t *cmd, rt_uint8_t len)
{
    st7796_t *nxp_lcd = (st7796_t*)handle;

    rt_pin_write(BSP_LCD_DC_PIN, PIN_LOW);
    rt_spi_send(nxp_lcd->spi_dev, cmd, 1);
    if (len > 1)
    {
        rt_pin_write(BSP_LCD_DC_PIN, PIN_HIGH);
        rt_spi_send(nxp_lcd->spi_dev, &cmd[1], len-1);
    }

    return RT_EOK;
}

static rt_err_t lcd_impl_write_data(void *handle, void *data, rt_uint32_t len)
{
    st7796_t *nxp_lcd = (st7796_t*)handle;

    rt_pin_write(BSP_LCD_DC_PIN, PIN_HIGH);
    rt_spi_send(nxp_lcd->spi_dev, data, len);

    return RT_EOK;
}

int drv_st7796_init(void)
{
    rt_pin_mode(BSP_LCD_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(BSP_LCD_DC_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(BSP_LCD_RST_PIN, PIN_HIGH);

    lcd_spi_obj.st7796.config.direction = ST7796_DIR_90;
    lcd_spi_obj.st7796.config.pix_fmt = ST7796_RGB565;
    lcd_spi_obj.st7796.config.bgr_mode = 1;
    lcd_spi_obj.st7796.config.inversion = 0;
    lcd_spi_obj.st7796.config.mirrored = 1;
    lcd_spi_obj.st7796.cb.reset_cb = lcd_impl_reset;
    lcd_spi_obj.st7796.cb.write_cmd_cb = lcd_impl_write_cmd;
    lcd_spi_obj.st7796.cb.write_data_cb = lcd_impl_write_data;
    lcd_spi_obj.st7796.user_data = lcd_spi_obj.parent.user_data = &lcd_spi_obj;

    rt_hw_spi_device_attach(BSP_LCD_SPI_BUS, LCD_DEVICE_NAME, BSP_LCD_CS_PIN);
    lcd_spi_obj.spi_dev = (struct rt_spi_device *)rt_device_find(LCD_DEVICE_NAME);
    if (!lcd_spi_obj.spi_dev)
    {
        LOG_E("lcd init run failed! can't find %s device!", LCD_DEVICE_NAME);
        return -RT_ERROR;
    }
    struct rt_spi_configuration cfg;
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB; /* SPI Compatible: Mode 0 and Mode 3 */
    cfg.max_hz = 10 * 1000 * 1000; /* 10M */
    rt_spi_configure(lcd_spi_obj.spi_dev, &cfg);

    st7796_lcd_init(&lcd_spi_obj.st7796);
    rt_device_register(&lcd_spi_obj.parent, "lcd", RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}
INIT_ENV_EXPORT(drv_st7796_init);
