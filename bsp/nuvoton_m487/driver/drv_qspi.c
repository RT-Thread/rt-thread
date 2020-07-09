/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-3-30      bluebear233  first version
 */


#include "NuMicro.h"
#include <rtdevice.h>
#ifdef RT_USING_SPI

/* Private Define ---------------------------------------------------------------*/
#define USEING_QSPI0

/* Private Typedef --------------------------------------------------------------*/
struct m487_qspi
{
    struct rt_spi_bus dev;
    struct rt_spi_configuration configuration;
    QSPI_T *spi_base;
    rt_uint8_t init_gpio:1;
};

/* Private functions ------------------------------------------------------------*/
static rt_err_t m487_qspi_bus_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *configuration);
static rt_uint32_t m487_qspi_bus_xfer(struct rt_spi_device *device,
        struct rt_spi_message *message);

/* Private Variables ------------------------------------------------------------*/
struct rt_spi_ops m487_spi_poll_ops =
{
    .configure = m487_qspi_bus_configure,
    .xfer      = m487_qspi_bus_xfer,
};

#ifdef USEING_QSPI0
static struct m487_qspi qspi0 =
{
    .spi_base = QSPI0,
};
#endif

static rt_err_t m487_qspi_bus_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *configuration) {

    struct m487_qspi *spi;
    uint32_t u32QSPIMode;
    uint32_t u32BusClock;
    rt_uint8_t init_bus;

    spi = (struct m487_qspi *) device->bus;
    init_bus = 0;

    if (!spi->init_gpio)
    {
        spi->init_gpio = 1;
        init_bus = 1;

        if(spi->spi_base == QSPI0)
        {
            /* Select PCLK0 as the clock source of QSPI0 */
            CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PLL,
                    MODULE_NoMsk);

            /* Enable QSPI0 peripheral clock */
            CLK_EnableModuleClock(QSPI0_MODULE);

            /* Setup QSPI0 multi-function pins */
            SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk
                    | SYS_GPC_MFPL_PC2MFP_Msk | SYS_GPC_MFPL_PC3MFP_Msk);
            SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_QSPI0_MOSI0 | SYS_GPC_MFPL_PC1MFP_QSPI0_MISO0
                    | SYS_GPC_MFPL_PC2MFP_QSPI0_CLK | SYS_GPC_MFPL_PC3MFP_QSPI0_SS;

            /* Enable SPI0 clock pin (PC2) schmitt trigger */
            PC->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;
        }
    }

    if(rt_memcmp(configuration, &spi->configuration, sizeof(*configuration)) != 0)
    {
        rt_memcpy(&spi->configuration, configuration, sizeof(*configuration));
        init_bus = 1;
    }

    if(init_bus)
    {
        switch(configuration->mode & RT_SPI_MODE_3)
        {
            case RT_SPI_MODE_0:u32QSPIMode = QSPI_MODE_0;break;
            case RT_SPI_MODE_1:u32QSPIMode = QSPI_MODE_1;break;
            case RT_SPI_MODE_2:u32QSPIMode = QSPI_MODE_2;break;
            case RT_SPI_MODE_3:u32QSPIMode = QSPI_MODE_3;break;
            default:RT_ASSERT(0);
        }

        u32BusClock = configuration->max_hz;
        if(u32BusClock > 50*1000*1000)
        {
            u32BusClock = 50*1000*1000;
        }

        QSPI_Open(spi->spi_base, QSPI_MASTER, u32QSPIMode, configuration->data_width, u32BusClock);

        QSPI_EnableAutoSS(spi->spi_base, QSPI_SS, QSPI_SS_ACTIVE_LOW);

        if(configuration->mode & RT_SPI_MSB)
        {
            QSPI_SET_MSB_FIRST(spi->spi_base);
        }
        else
        {
            QSPI_SET_LSB_FIRST(spi->spi_base);
        }
    }

    return RT_EOK;
}

/**
 * @brief SPI bus 轮询
 * @param dev : SPI总线设备结构体指针
 * @param send_addr : 发送缓冲区地址
 * @param recv_addr : 接收缓冲区地址
 * @param length    : 数据长度
 */
static void qspi_transmission_with_poll(struct m487_qspi *spi_bus,
        const uint8_t *send_addr, uint8_t *recv_addr, int length)
{
    QSPI_T *spi_base = spi_bus->spi_base;

    // 写
    if (send_addr != RT_NULL && recv_addr == RT_NULL)
    {
        while (length--)
        {
            // 等待TX FIFO 为空
            while(QSPI_GET_TX_FIFO_FULL_FLAG(spi_base));

            // 输入数据
            QSPI_WRITE_TX(spi_base, *send_addr++);
        }

        // 等待SPI空闲
        while(QSPI_IS_BUSY(spi_base));
    }
    // 读写
    else if (send_addr != RT_NULL && recv_addr != RT_NULL)
    {
        // 清空读FIFO
        if(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            QSPI_ClearRxFIFO(spi_base);
            while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base));
        }

        while (length--)
        {
            // 等待TX FIFO 为空
            while(QSPI_GET_TX_FIFO_FULL_FLAG(spi_base));

            // 输入数据
            QSPI_WRITE_TX(spi_base, *send_addr++);

            // 读取RX FIFO
            while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }

        // 等待SPI空闲
        while(QSPI_IS_BUSY(spi_base))
        {
            while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }
    }
    //读
    else
    {
        // 清空读FIFO
        if(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            QSPI_ClearRxFIFO(spi_base);
            while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base));
        }

        while (length--)
        {
            // 等待TX FIFO 为空
            while(QSPI_GET_TX_FIFO_FULL_FLAG(spi_base));

            // 输入数据
            QSPI_WRITE_TX(spi_base, 0x00);

            // 读取RX FIFO
            while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }

        // 等待SPI空闲
        while(QSPI_IS_BUSY(spi_base))
        {
            while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
            {
                *recv_addr++ = QSPI_READ_RX(spi_base);
            }
        }

        while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(spi_base))
        {
            *recv_addr++ = QSPI_READ_RX(spi_base);
        }
    }
}

static rt_uint32_t m487_qspi_bus_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct m487_qspi *spi;

    spi = (struct m487_qspi *) device->bus;

    if (message->cs_take)
    {
        QSPI_SET_SS_LOW(spi->spi_base);
    }

    if (message->length > 0)
    {
        qspi_transmission_with_poll(spi, message->send_buf,
                message->recv_buf, message->length);
    }

    if (message->cs_release)
    {
        QSPI_SET_SS_HIGH(spi->spi_base);
    }

    return message->length;
}

static int m487_qspi_register_bus(struct m487_qspi *spi_bus, const char *name)
{
    return rt_spi_bus_register(&spi_bus->dev, name, &m487_spi_poll_ops);
}

/**
 * 硬件QSPI注册
 */
static int rt_hw_qspi_init(void)
{
#ifdef USEING_QSPI0
	m487_qspi_register_bus(&qspi0, "qspi0");
#endif

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_qspi_init);
#endif

