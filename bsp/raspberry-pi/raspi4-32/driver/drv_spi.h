/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-06-16     bigmagic       first version
 */
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include "drv_gpio.h"

#define SPI_REG_CS(BASE)            HWREG32(BASE + 0x00)
#define SPI_REG_FIFO(BASE)          HWREG32(BASE + 0x04)
#define SPI_REG_CLK(BASE)           HWREG32(BASE + 0x08)
#define SPI_REG_DLEN(BASE)          HWREG32(BASE + 0x0C)
#define SPI_REG_LTOH(BASE)          HWREG32(BASE + 0x10)
#define SPI_REG_DC(BASE)            HWREG32(BASE + 0x14)

/* CS Register */
#define SPI_CS_LOSSI_LONG_32BIT         (1 << 25)
#define SPI_CS_LOSSI_DMA_MODE           (1 << 24)
#define SPI_CS_CSPOL2                   (1 << 23)
#define SPI_CS_CSPOL1                   (1 << 22)
#define SPI_CS_CSPOL0                   (1 << 21)
#define SPI_CS_RX_FIFO_FULL             (1 << 20)
#define SPI_CS_RX_FIFO_3_QUARTER        (1 << 19)
#define SPI_CS_TX_DATA                  (1 << 18)
#define SPI_CS_RX_DATA                  (1 << 17)
#define SPI_CS_DONE                     (1 << 16)
#define SPI_CS_LOSSI_EN                 (1 << 13)
#define SPI_CS_READ_EN                  (1 << 12)
#define SPI_CS_AUTO_CS                  (1 << 11)
#define SPI_CS_INTR_RXR                 (1 << 10)
#define SPI_CS_INTR_DONE                (1 << 9)
#define SPI_CS_DMA_EN                   (1 << 8)
#define SPI_CS_TA                       (1 << 7)
#define SPI_CS_CSPOL_HIGH               (1 << 6)
#define SPI_CS_CLEAR_RX                 (2 << 4)
#define SPI_CS_CLEAR_TX                 (1 << 4)
#define SPI_CS_CPOL                     (1 << 3)
#define SPI_CS_CPHA                     (1 << 2)
#define SPI_CS_CHIP_SELECT_2            (2 << 0)
#define SPI_CS_CHIP_SELECT_1            (1 << 0)
#define SPI_CS_CHIP_SELECT_0            (0 << 0)

struct raspi_spi_hw_config
{
    rt_uint8_t spi_num;
    GPIO_PIN   sclk_pin;
    GPIO_FUNC  sclk_mode;
    GPIO_PIN   mosi_pin;
    GPIO_FUNC  mosi_mode;
    GPIO_PIN   miso_pin;
    GPIO_FUNC  miso_mode;
#if defined (BSP_USING_SPI0_DEVICE0) || defined (BSP_USING_SPI1_DEVICE0)
    GPIO_PIN   ce0_pin;
    GPIO_FUNC  ce0_mode;
#endif

#if defined (BSP_USING_SPI0_DEVICE1) || defined (BSP_USING_SPI1_DEVICE1)
    GPIO_PIN   ce1_pin;
    GPIO_FUNC  ce1_mode;
#endif

#if defined (BSP_USING_SPI1_DEVICE2)
    GPIO_PIN   ce2_pin;
    GPIO_FUNC  ce2_mode;
#endif
    rt_ubase_t hw_base;

};

struct raspi_spi_device
{
    char *device_name;
    struct rt_spi_bus *spi_bus;
    struct rt_spi_device *spi_device;
    struct raspi_spi_hw_config *spi_hw_config;
    GPIO_PIN cs_pin;
};

int rt_hw_spi_init(void);

#endif
