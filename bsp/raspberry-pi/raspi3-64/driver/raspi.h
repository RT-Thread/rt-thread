/*
 * File      : rsapi.h
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#ifndef __RASPI_H__
#define __RASPI_H__

#include "bcm283x.h"

#define PIN_MAGIC       (0x5A)
#define PIN_NUM(_N)     (sizeof(_N) / sizeof(_N[0]))

enum gpio_code
{
    GPIO_CODE_PHY = 0,
    GPIO_CODE_BCM,
    GPIO_CODE_WIRING,
    GPIO_CODE_NUM,
};

enum rpi_pin_name
{
    RPI_SDA0 = 0,
    RPI_SCL0,
    RPI_SDA1,
    RPI_SCL1,
    RPI_GPIO_GCLK,
    RPI_CAM_CLK,
    RPI_LAN_RUN,
    RPI_SPI_CE1_N,
    RPI_SPI_CE0_N,
    RPI_SPI_MISO,
    RPI_SPI_MOSI,
    RPI_SPI_SCLK,
    RPI_TXD0,
    RPI_RXD0,
    RPI_STATUS_LED_N,
    RPI_GPIO_GEN0,
    RPI_GPIO_GEN1,
    RPI_CAM_GPIO,
    RPI_GPIO_GEN3,
    RPI_GPIO_GEN4,
    RPI_GPIO_GEN5,
    RPI_GPIO_GEN6,
    RPI_GPIO_GEN2,
    RPI_GPIO_GEN7,
    RPI_GPIO_GEN8,
    RPI_GPIO_GEN9,
    RPI_GPIO_GEN10,
    RPI_PWM0_OUT,
    RPI_PWM1_OUT,
    RPI_HDMI_HPD_P,
    RPI_SD_CARD_DET,
    RPI_SD_CLK_R,
    RPI_SD_CMD_R,
    RPI_SD_DATA0_R,
    RPI_SD_DATA1_R,
    RPI_SD_DATA2_R,
    RPI_SD_DATA3_R,
    RPI_GPIO_PIN_NUM,
};

#define DELAY_MICROS(micros) \
    do{ \
 rt_uint32_t compare = STIMER_CLO + micros * 25; \
 while (STIMER_CLO < compare); \
    } while (0) \

#endif
