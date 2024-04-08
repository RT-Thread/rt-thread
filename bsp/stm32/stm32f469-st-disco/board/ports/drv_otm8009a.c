/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-05-23     WillianChan    first version
 */

#include <board.h>
#include <drv_gpio.h>

#ifdef BSP_USING_LCD_OTM8009A
extern DSI_HandleTypeDef hdsi;
extern DSI_VidCfgTypeDef hdsi_video;

const rt_uint8_t RDL01[] = {0x80, 0x09, 0x01, 0xFF};
const rt_uint8_t RDL02[] = {0x80, 0x09, 0xFF};
const rt_uint8_t RDL03[] = {0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE1};
const rt_uint8_t RDL04[] = {0x00, 0x09, 0x0F, 0x0E, 0x07, 0x10, 0x0B, 0x0A, 0x04, 0x07, 0x0B, 0x08, 0x0F, 0x10, 0x0A, 0x01, 0xE2};
const rt_uint8_t RDL05[] = {0x79, 0x79, 0xD8};
const rt_uint8_t RDL06[] = {0x00, 0x01, 0xB3};
const rt_uint8_t RDL07[] = {0x85, 0x01, 0x00, 0x84, 0x01, 0x00, 0xCE};
const rt_uint8_t RDL08[] = {0x18, 0x04, 0x03, 0x39, 0x00, 0x00, 0x00, 0x18, 0x03, 0x03, 0x3A, 0x00, 0x00, 0x00, 0xCE};
const rt_uint8_t RDL09[] = {0x18, 0x02, 0x03, 0x3B, 0x00, 0x00, 0x00, 0x18, 0x01, 0x03, 0x3C, 0x00, 0x00, 0x00, 0xCE};
const rt_uint8_t RDL10[] = {0x01, 0x01, 0x20, 0x20, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0xCF};
const rt_uint8_t RDL11[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL12[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL13[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL14[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL15[] = {0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL16[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL17[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCB};
const rt_uint8_t RDL18[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCB};
const rt_uint8_t RDL19[] = {0x00, 0x26, 0x09, 0x0B, 0x01, 0x25, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL20[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x0A, 0x0C, 0x02, 0xCC};
const rt_uint8_t RDL21[] = {0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL22[] = {0x00, 0x25, 0x0C, 0x0A, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL23[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x0B, 0x09, 0x01, 0xCC};
const rt_uint8_t RDL24[] = {0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};
const rt_uint8_t RDL25[] = {0xFF, 0xFF, 0xFF, 0xFF};
const rt_uint8_t RDL27[] = {0x00, 0x00, 0x03, 0x1F, 0x2A};
const rt_uint8_t RDL28[] = {0x00, 0x00, 0x01, 0xDF, 0x2B};

const rt_uint8_t RDS01[] = {0x00, 0x00};
const rt_uint8_t RDS02[] = {0x00, 0x80};
const rt_uint8_t RDS03[] = {0xC4, 0x30};
const rt_uint8_t RDS04[] = {0x00, 0x8A};
const rt_uint8_t RDS05[] = {0xC4, 0x40};
const rt_uint8_t RDS06[] = {0x00, 0xB1};
const rt_uint8_t RDS07[] = {0xC5, 0xA9};
const rt_uint8_t RDS08[] = {0x00, 0x91};
const rt_uint8_t RDS09[] = {0xC5, 0x34};
const rt_uint8_t RDS10[] = {0x00, 0xB4};
const rt_uint8_t RDS11[] = {0xC0, 0x50};
const rt_uint8_t RDS12[] = {0xD9, 0x4E};
const rt_uint8_t RDS13[] = {0x00, 0x81};
const rt_uint8_t RDS14[] = {0xC1, 0x66};
const rt_uint8_t RDS15[] = {0x00, 0xA1};
const rt_uint8_t RDS16[] = {0xC1, 0x08};
const rt_uint8_t RDS17[] = {0x00, 0x92};
const rt_uint8_t RDS18[] = {0xC5, 0x01};
const rt_uint8_t RDS19[] = {0x00, 0x95};
const rt_uint8_t RDS20[] = {0x00, 0x94};
const rt_uint8_t RDS21[] = {0xC5, 0x33};
const rt_uint8_t RDS22[] = {0x00, 0xA3};
const rt_uint8_t RDS23[] = {0xC0, 0x1B};
const rt_uint8_t RDS24[] = {0x00, 0x82};
const rt_uint8_t RDS25[] = {0xC5, 0x83};
const rt_uint8_t RDS26[] = {0xC4, 0x83};
const rt_uint8_t RDS27[] = {0xC1, 0x0E};
const rt_uint8_t RDS28[] = {0x00, 0xA6};
const rt_uint8_t RDS29[] = {0x00, 0xA0};
const rt_uint8_t RDS30[] = {0x00, 0xB0};
const rt_uint8_t RDS31[] = {0x00, 0xC0};
const rt_uint8_t RDS32[] = {0x00, 0xD0};
const rt_uint8_t RDS33[] = {0x00, 0x90};
const rt_uint8_t RDS34[] = {0x00, 0xE0};
const rt_uint8_t RDS35[] = {0x00, 0xF0};
const rt_uint8_t RDS36[] = {0x11, 0x00};
const rt_uint8_t RDS37[] = {0x3A, 0x55};
const rt_uint8_t RDS38[] = {0x3A, 0x77};
const rt_uint8_t RDS39[] = {0x36, 0x60};
const rt_uint8_t RDS40[] = {0x51, 0x7F};
const rt_uint8_t RDS41[] = {0x53, 0x2C};
const rt_uint8_t RDS42[] = {0x55, 0x02};
const rt_uint8_t RDS43[] = {0x5E, 0xFF};
const rt_uint8_t RDS44[] = {0x29, 0x00};
const rt_uint8_t RDS45[] = {0x2C, 0x00};
const rt_uint8_t RDS46[] = {0xCF, 0x00};
const rt_uint8_t RDS47[] = {0xC5, 0x66};
const rt_uint8_t RDS48[] = {0x00, 0xB6};
const rt_uint8_t RDS49[] = {0xF5, 0x06};
const rt_uint8_t RDS50[] = {0x00, 0xB1};
const rt_uint8_t RDS51[] = {0xC6, 0x06};

void otm8009a_reset(void)
{
    rt_pin_mode (GET_PIN(H, 7), PIN_MODE_OUTPUT);
    rt_pin_write(GET_PIN(H, 7), PIN_LOW);
    rt_thread_delay(rt_tick_from_millisecond(20));
    rt_pin_write(GET_PIN(H, 7), PIN_HIGH);
    rt_thread_delay(rt_tick_from_millisecond(20));
}

static void otm8009a_write_cmd(uint8_t *p, uint32_t num)
{
    if (num <= 1)
    {
        HAL_DSI_ShortWrite(&hdsi, hdsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, p[0], p[1]);
    }
    else
    {
        HAL_DSI_LongWrite(&hdsi, hdsi_video.VirtualChannelID, DSI_DCS_LONG_PKT_WRITE, num, p[num], p);
    }
}

static void otm8009a_delay(uint32_t d)
{
    rt_thread_delay(rt_tick_from_millisecond(d));
}

static void otm8009a_config(rt_uint32_t pixel_format)
{
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL01, 3);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL02, 2);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS03, 0);
    otm8009a_delay(10);

    otm8009a_write_cmd((rt_uint8_t *)RDS04, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS05, 0);
    otm8009a_delay(10);

    otm8009a_write_cmd((rt_uint8_t *)RDS06, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS07, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS08, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS09, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS10, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS11, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS12, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS13, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS14, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS15, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS16, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS17, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS18, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS19, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS09, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL05, 2);
    otm8009a_write_cmd((rt_uint8_t *)RDS20, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS21, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS22, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS23, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS24, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS25, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS13, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS26, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS15, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS27, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS28, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL06, 2);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL07, 6);
    otm8009a_write_cmd((rt_uint8_t *)RDS29, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL08, 14);
    otm8009a_write_cmd((rt_uint8_t *)RDS30, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL09, 14);
    otm8009a_write_cmd((rt_uint8_t *)RDS31, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL10, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS32, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS46, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL11, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS33, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL12, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS29, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL13, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS30, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL14, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS31, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL15, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS32, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL16, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS34, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL17, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS35, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL18, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS02, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL19, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS33, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL20, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS29, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL21, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS30, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL22, 10);
    otm8009a_write_cmd((rt_uint8_t *)RDS31, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL23, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS32, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL24, 15);
    otm8009a_write_cmd((rt_uint8_t *)RDS13, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS47, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS48, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS49, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS50, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS51, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL25, 3);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL03, 16);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL04, 16);
    otm8009a_write_cmd((rt_uint8_t *)RDS36, 0);
    otm8009a_delay(120);

    switch (pixel_format)
    {
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        otm8009a_write_cmd((rt_uint8_t *)RDS37, 0);
        break;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        otm8009a_write_cmd((rt_uint8_t *)RDS38, 0);
        break;
    }

    otm8009a_write_cmd((rt_uint8_t *)RDS39, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDL27, 4);
    otm8009a_write_cmd((rt_uint8_t *)RDL28, 4);
    otm8009a_write_cmd((rt_uint8_t *)RDS40, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS41, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS42, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS43, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS44, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS01, 0);
    otm8009a_write_cmd((rt_uint8_t *)RDS45, 0);
}


void stm32_mipi_lcd_init(void)
{
    otm8009a_reset();
}

void stm32_mipi_lcd_config(rt_uint32_t pixel_format)
{
    otm8009a_config(pixel_format);
}

void stm32_mipi_display_on(void)
{
    HAL_DSI_ShortWrite(&hdsi, hdsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, 0x29, 0x00);
}

void stm32_mipi_display_off(void)
{
    HAL_DSI_ShortWrite(&hdsi, hdsi_video.VirtualChannelID, DSI_DCS_SHORT_PKT_WRITE_P1, 0x28, 0x00);
}
#endif
