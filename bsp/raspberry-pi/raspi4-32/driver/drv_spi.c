/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2020-06-22     bigmagic        first version
 */
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "raspi4.h"
#include "drv_spi.h"

#ifdef RT_USING_SPI

#define RPI_CORE_CLK_HZ        (250000000)
#define BSP_SPI_MAX_HZ         (30* 1000 *1000)
#define SPITIMEOUT             0x0FFF

static rt_uint8_t raspi_byte_reverse_table[] =
{
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff
};

#if defined (BSP_USING_SPI0_BUS)
#define SPI0_BUS_NAME      "spi0"
#define SPI0_DEVICE0_NAME  "spi0.0"
#define SPI0_DEVICE1_NAME  "spi0.1"

struct rt_spi_bus spi0_bus;

#if defined (BSP_USING_SPI0_DEVICE0)
static struct rt_spi_device spi0_device0;
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
static struct rt_spi_device spi0_device1;
#endif
#endif

static rt_err_t raspi_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);
    rt_uint16_t divider;
    struct raspi_spi_device* hw_config = (struct raspi_spi_device *)(device->parent.user_data);
    struct raspi_spi_hw_config *hwcfg = (struct raspi_spi_hw_config *)hw_config->spi_hw_config;
    // spi clear fifo
    SPI_REG_CS(hwcfg->hw_base) = (SPI_CS_CLEAR_TX | SPI_CS_CLEAR_RX);
    if(cfg->mode & RT_SPI_CPOL)
    {
        SPI_REG_CS(hwcfg->hw_base) |= SPI_CS_CPOL;
    }

    if(cfg->mode & RT_SPI_CPHA)
    {
        SPI_REG_CS(hwcfg->hw_base) |= SPI_CS_CPHA;
    }

    if(cfg->mode & RT_SPI_CS_HIGH)
    {
        SPI_REG_CS(hwcfg->hw_base) |= SPI_CS_CSPOL_HIGH;   
    }

    //set clk
    if (cfg->max_hz > BSP_SPI_MAX_HZ)
        cfg->max_hz = BSP_SPI_MAX_HZ;

    divider = (rt_uint16_t) ((rt_uint32_t) RPI_CORE_CLK_HZ / cfg->max_hz);
    divider &= 0xFFFE;

    SPI_REG_CLK(hwcfg->hw_base) = divider;

    return RT_EOK;
}

rt_uint8_t correct_order(rt_uint8_t b, rt_uint8_t flag)
{
    if (flag)
        return raspi_byte_reverse_table[b];//reverse
    else
        return b;
}

static rt_err_t spi_transfernb(struct raspi_spi_hw_config *hwcfg, rt_uint8_t* tbuf, rt_uint8_t* rbuf, rt_uint32_t len, rt_uint8_t flag)
{
    rt_uint32_t TXCnt=0;
    rt_uint32_t RXCnt=0;
    
    /* Clear TX and RX fifos */
    SPI_REG_CS(hwcfg->hw_base) |= (SPI_CS_CLEAR_TX | SPI_CS_CLEAR_RX);

    /* Set TA = 1 */
    SPI_REG_CS(hwcfg->hw_base) |= SPI_CS_TA;

    /* Use the FIFO's to reduce the interbyte times */
    while ((TXCnt < len) || (RXCnt < len))
    {
        /* TX fifo not full, so add some more bytes */
        while (((SPI_REG_CS(hwcfg->hw_base) & SPI_CS_TX_DATA)) && (TXCnt < len))
        {
            SPI_REG_FIFO(hwcfg->hw_base) = correct_order(tbuf[TXCnt],flag);
            TXCnt++;
        }
        /* Rx fifo not empty, so get the next received bytes */
        while (((SPI_REG_CS(hwcfg->hw_base) & SPI_CS_RX_DATA)) && (RXCnt < len))
        {
            rbuf[RXCnt] = correct_order(SPI_REG_FIFO(hwcfg->hw_base), flag);
            RXCnt++;
        }
    }
    /* Wait for DONE to be set */
    while (!(SPI_REG_CS(hwcfg->hw_base) & SPI_CS_DONE));
    /* Set TA = 0, and also set the barrier */
    SPI_REG_CS(hwcfg->hw_base) |= (0 & SPI_CS_TA);

    return RT_EOK;
}

static rt_uint32_t raspi_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_err_t res;
    rt_uint8_t flag;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->parent.user_data != RT_NULL);
    RT_ASSERT(message->send_buf != RT_NULL || message->recv_buf != RT_NULL);

    struct rt_spi_configuration config = device->config;
    struct raspi_spi_device * hw_config = (struct raspi_spi_device *)device->parent.user_data;
    GPIO_PIN cs_pin = (GPIO_PIN)hw_config->cs_pin;
    struct raspi_spi_hw_config *hwcfg = (struct raspi_spi_hw_config *)hw_config->spi_hw_config;

    if (config.mode & RT_SPI_MSB)
    {
        flag = 0;
    }   
    else
    {
        flag = 1;
    }

    if (message->cs_take)
    {
        (config.mode & RT_SPI_CS_HIGH)?prev_raspi_pin_write(cs_pin, 1):prev_raspi_pin_write(cs_pin, 0);
    }

    res = spi_transfernb(hwcfg, (rt_uint8_t *)message->send_buf, (rt_uint8_t *)message->recv_buf, (rt_int32_t)message->length, flag);
    if (message->cs_release)
    {
        (config.mode & RT_SPI_CS_HIGH)?prev_raspi_pin_write(cs_pin, 0):prev_raspi_pin_write(cs_pin, 1);
    }
    if (res != RT_EOK)
           return RT_ERROR;

    return message->length;
}

rt_err_t raspi_spi_bus_attach_device(const char *bus_name, struct raspi_spi_device *device)
{
    rt_err_t ret;
    RT_ASSERT(device != RT_NULL);
    ret = rt_spi_bus_attach_device(device->spi_device, device->device_name, bus_name, (void *)(device));
    return ret;
}

rt_err_t raspi_spi_hw_init(struct raspi_spi_hw_config *hwcfg)
{
    prev_raspi_pin_mode(hwcfg->sclk_pin, hwcfg->sclk_mode);
    prev_raspi_pin_mode(hwcfg->miso_pin, hwcfg->miso_mode);
    prev_raspi_pin_mode(hwcfg->mosi_pin, hwcfg->mosi_mode);
#if defined (BSP_USING_SPI0_DEVICE0)
    prev_raspi_pin_mode(hwcfg->ce0_pin, hwcfg->ce0_mode);
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    prev_raspi_pin_mode(hwcfg->ce1_pin, hwcfg->ce1_mode);
#endif
    //clear rx and tx
    SPI_REG_CS(hwcfg->hw_base) = (SPI_CS_CLEAR_TX | SPI_CS_CLEAR_RX);
    //enable chip select
#if defined (BSP_USING_SPI0_DEVICE0)
    SPI_REG_CS(hwcfg->hw_base) |= SPI_CS_CHIP_SELECT_0;
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    SPI_REG_CS(hwcfg->hw_base) |= SPI_CS_CHIP_SELECT_1;
#endif
    
#if defined (BSP_USING_SPI0_DEVICE0) && defined (BSP_USING_SPI0_DEVICE1)
    HWREG32(SPI_REG_CS(hwcfg->hw_base)) |= (SPI_CS_CHIP_SELECT_0 | SPI_CS_CHIP_SELECT_1);
#endif
    return RT_EOK;
}

static struct rt_spi_ops raspi_spi_ops =
{
    .configure = raspi_spi_configure,
    .xfer = raspi_spi_xfer
};

struct raspi_spi_hw_config raspi_spi0_hw =
{
    .spi_num = 0,
    .sclk_pin = GPIO_PIN_11,
    .sclk_mode = ALT0,
    .mosi_pin = GPIO_PIN_10,
    .mosi_mode = ALT0,
    .miso_pin = GPIO_PIN_9,
    .miso_mode = ALT0,

#if defined (BSP_USING_SPI0_DEVICE0)
    .ce0_pin = GPIO_PIN_8,
    .ce0_mode = ALT0,
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    .ce1_pin = GPIO_PIN_7,
    .ce1_mode = ALT0,
#endif
    .hw_base = SPI_0_BASE,
};
#endif

#if defined (BSP_USING_SPI0_DEVICE0)
struct raspi_spi_device raspi_spi0_device0 =
{
    .device_name = SPI0_DEVICE0_NAME,
    .spi_bus = &spi0_bus,
    .spi_device = &spi0_device0,
    .spi_hw_config = &raspi_spi0_hw,
    .cs_pin = GPIO_PIN_8,
};
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
struct raspi_spi_device raspi_spi0_device1 =
{
    .device_name = SPI0_DEVICE1_NAME,
    .spi_bus = &spi0_bus,
    .spi_device = &spi0_device1,
    .cs_pin = GPIO_PIN_7,
};
#endif

int rt_hw_spi_init(void)
{
#if defined (BSP_USING_SPI0_BUS)
    raspi_spi_hw_init(&raspi_spi0_hw);
    rt_spi_bus_register(&spi0_bus, SPI0_BUS_NAME, &raspi_spi_ops);

#if defined (BSP_USING_SPI0_DEVICE0)
    raspi_spi_bus_attach_device(SPI0_BUS_NAME, &raspi_spi0_device0);
#endif

#if defined (BSP_USING_SPI0_DEVICE1)
    raspi_spi_bus_attach_device(SPI0_BUS_NAME, &raspi_spi0_device1);
#endif
#endif
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);
