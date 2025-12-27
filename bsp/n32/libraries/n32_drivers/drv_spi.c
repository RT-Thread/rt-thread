/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 *
 * 202512-03
 *      1.spi 的驱动优化，在G457上spi2可行
 *      2.新增了Kconfig的配置文件，测试spi2的remap=3测试OK
 * 2025-12-04
 *      1.增加了spi1和spi2的Kconfig配置选项，未测试
 * 
 * 2025-12-18
 *  1.添加了注释 信息
 *  2.目前代码支持N32G45x和N32L40x系列的
 *  3.在PGM-11项目测试了N32L40x的spi1，表示可行
 */
#include <rtthread.h>

#define DBG_TAG "SPI"
#define DBG_LVL LOG_LVL_INFO
#include <rtdbg.h>

#include "drv_base.h"
#include "drv_spi.h"
#if defined(RT_USING_SPI) && defined(RT_USING_PIN)
#include <rtdevice.h>

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || \
    defined(BSP_USING_SPI3)

/* private rt-thread spi ops function */

static rt_err_t configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    SPI_InitType SPI_InitStructure;
    RCC_ClocksType RCC_ClockFreq;
    SPI_Module *spi_periph;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    RCC_GetClocksFreqValue(&RCC_ClockFreq);

    spi_periph = (SPI_Module *)device->bus->parent.user_data;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    if (spi_periph != SPI1 && spi_periph != SPI2 && spi_periph != SPI3)
    {
        return -RT_EIO;
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    if (spi_periph != SPI1 && spi_periph != SPI2)
    {
        return -RT_EIO;
    }
#endif

    if (configuration->data_width <= 8)
    {
        SPI_InitStructure.DataLen = SPI_DATA_SIZE_8BITS;
    }
    else if (configuration->data_width <= 16)
    {
        SPI_InitStructure.DataLen = SPI_DATA_SIZE_16BITS;
    }
    else
    {
        return -RT_EIO;
    }

    {
        rt_uint32_t spi_apb_clock;
        rt_uint32_t max_hz;

        max_hz = configuration->max_hz;

        LOG_D("sys   freq: %d\n", RCC_ClockFreq.SysclkFreq);
        LOG_D("CK_APB2 freq: %d\n", RCC_ClockFreq.Pclk2Freq);
        LOG_D("max   freq: %d\n", max_hz);

        if (spi_periph == SPI1)
        {
            spi_apb_clock = RCC_ClockFreq.Pclk2Freq;
        }
        else
        {
            spi_apb_clock = RCC_ClockFreq.Pclk1Freq;
        }

        if (max_hz >= spi_apb_clock / 2)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_2;
        }
        else if (max_hz >= spi_apb_clock / 4)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_4;
        }
        else if (max_hz >= spi_apb_clock / 8)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_8;
        }
        else if (max_hz >= spi_apb_clock / 16)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_16;
        }
        else if (max_hz >= spi_apb_clock / 32)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_32;
        }
        else if (max_hz >= spi_apb_clock / 64)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_64;
        }
        else if (max_hz >= spi_apb_clock / 128)
        {
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_128;
        }
        else
        {
            /*  min prescaler 256 */
            SPI_InitStructure.BaudRatePres = SPI_BR_PRESCALER_256;
        }
    } /* baudrate */

    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        SPI_InitStructure.CLKPOL = SPI_CLKPOL_LOW;
        SPI_InitStructure.CLKPHA = SPI_CLKPHA_FIRST_EDGE;
        break;
    case RT_SPI_MODE_1:
        SPI_InitStructure.CLKPOL = SPI_CLKPOL_LOW;
        SPI_InitStructure.CLKPHA = SPI_CLKPHA_SECOND_EDGE;
        break;
    case RT_SPI_MODE_2:
        SPI_InitStructure.CLKPOL = SPI_CLKPOL_HIGH;
        SPI_InitStructure.CLKPHA = SPI_CLKPHA_FIRST_EDGE;
        break;
    case RT_SPI_MODE_3:
        SPI_InitStructure.CLKPOL = SPI_CLKPOL_HIGH;
        SPI_InitStructure.CLKPHA = SPI_CLKPHA_SECOND_EDGE;
        break;
    }

    /* MSB or LSB */
    if (configuration->mode & RT_SPI_MSB)
    {
        SPI_InitStructure.FirstBit = SPI_FB_MSB;
    }
    else
    {
        SPI_InitStructure.FirstBit = SPI_FB_LSB;
    }
    /* SPI configuration */
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
    SPI_InitStructure.NSS = SPI_NSS_SOFT;
    SPI_InitStructure.CRCPoly = 7;

    SPI_Init(spi_periph, &SPI_InitStructure);

    /* Enable the sFLASH_SPI  */
    SPI_Enable(spi_periph, ENABLE);

    return RT_EOK;
}

static rt_ssize_t xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct n32_spi_cs *cs_pin = device->parent.user_data;
    SPI_Module *spi_periph = (SPI_Module *)device->bus->parent.user_data;
    struct rt_spi_configuration *config = &device->config;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take CS */
    if (message->cs_take)
    {
        rt_pin_write(cs_pin->GPIO_Pin, PIN_LOW);
        LOG_D("spi take cs %d \n", cs_pin->GPIO_Pin);
    }

    if (config->data_width <= 8)
    {
        const rt_uint8_t *send_ptr = message->send_buf;
        rt_uint8_t *recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;

        LOG_D("spi poll transfer start: %d\n", size);

        while (size--)
        {
            rt_uint8_t data = 0xA5;

            if (send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* Loop while DAT register in not emplty */
            while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_TE_FLAG) == RESET)
                ;

            /* Send the byte */
            SPI_I2S_TransmitData(spi_periph, data);

            /* Wait until a data is received */
            while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_RNE_FLAG) == RESET)
                ;

            /* Get the received data */
            data = SPI_I2S_ReceiveData(spi_periph);

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
        LOG_D("spi poll transfer finsh\n");
    }
    else if (config->data_width <= 16)
    {
        const rt_uint16_t *send_ptr = message->send_buf;
        rt_uint16_t *recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;

        while (size--)
        {
            rt_uint16_t data = 0xFF;

            if (send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* Loop while DAT register in not emplty */
            while (SPI_I2S_GetStatus(spi_periph, SPI_I2S_TE_FLAG) == RESET)
                ;

            /* Send the byte */
            SPI_I2S_TransmitData(spi_periph, data);

            /* Wait until a data is received */
            while (RESET == SPI_I2S_GetStatus(spi_periph, SPI_I2S_RNE_FLAG))
                ;

            /* Get the received data */
            data = SPI_I2S_ReceiveData(spi_periph);

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
    }

    /* release CS */
    if (message->cs_release)
    {
        rt_pin_write(cs_pin->GPIO_Pin, PIN_HIGH);
        LOG_D("spi release cs\n");
    }

    return message->length;
}

static struct rt_spi_ops spi_ops =
    {
        configure,
        xfer,
};

static void n32_spi_rcc_enable(const SPI_Module *spi)
{
    if (SPI1 == spi)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1, ENABLE);
    }
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    else if (SPI2 == spi)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI2, ENABLE);
    }
    else if (SPI3 == spi)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_SPI3, ENABLE);
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    else if (SPI2 == spi)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI2, ENABLE);
    }

#endif
}
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)

typedef struct
{
    struct rt_spi_bus spi_bus;
    SPI_Module *spi;
    uint32_t spi_remap;
    uint16_t pin_sclk;
    uint16_t pin_mosi;
    uint16_t pin_miso;
    GPIO_Module *gpio_grp;
    char *name;
    char *info;
} n32_spi_hd_t;
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
typedef struct
{
    struct rt_spi_bus spi_bus;
    SPI_Module *spi;
    uint16_t pin_sclk;
    uint16_t pin_mosi;
    uint16_t pin_miso;
    uint8_t pin_sclk_remap;
    uint8_t pin_mosi_remap;
    uint8_t pin_miso_remap;
    GPIO_Module *gpio_grp;
    char *name;
    char *info;
} n32_spi_hd_t;
#endif
void n32_spi_gpio_init(const n32_spi_hd_t *spi_hd)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    n32_gpio_rcc_enable(spi_hd->gpio_grp);

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    if (spi_hd->spi_remap)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        GPIO_ConfigPinRemap(spi_hd->spi_remap, ENABLE);
    }
    /* Confige SPI1_SCLK and SPI1_MOSI */
    GPIO_InitStructure.Pin = spi_hd->pin_sclk | spi_hd->pin_mosi;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(spi_hd->gpio_grp, &GPIO_InitStructure);

    /* Confige SPI1_MISO */
    GPIO_InitStructure.Pin = spi_hd->pin_miso;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitPeripheral(spi_hd->gpio_grp, &GPIO_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    // afio rcc
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Confige SPI1_SCLK */
    GPIO_InitStructure.Pin = spi_hd->pin_sclk;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = spi_hd->pin_sclk_remap;
    GPIO_InitPeripheral(spi_hd->gpio_grp, &GPIO_InitStructure);
    /*SPI1_MISO()*/
    GPIO_InitStructure.Pin = spi_hd->pin_mosi;
    GPIO_InitStructure.GPIO_Alternate = spi_hd->pin_mosi_remap;
    GPIO_InitPeripheral(spi_hd->gpio_grp, &GPIO_InitStructure);
    /*SPI1_MISO()*/
    GPIO_InitStructure.Pin = spi_hd->pin_miso;
    GPIO_InitStructure.GPIO_Alternate = spi_hd->pin_miso_remap;
    GPIO_InitPeripheral(spi_hd->gpio_grp, &GPIO_InitStructure);
#endif
}

static void n32_spi_init(n32_spi_hd_t *spi_hd)
{
    n32_spi_rcc_enable(spi_hd->spi);//时钟初始化
    n32_spi_gpio_init(spi_hd);//gpio初始化
    spi_hd->spi_bus.parent.user_data = spi_hd->spi;
    //注册spi总线设备
    if (RT_EOK == rt_spi_bus_register(&spi_hd->spi_bus, spi_hd->name, &spi_ops))
    {
        LOG_D("register %s is ok,pin={%s}", spi_hd->name, spi_hd->info);
    }
    else
    {
        LOG_W("register %s is error,pin={%s}", spi_hd->name, spi_hd->info);
    }
}
static n32_spi_hd_t n32_spi_hd[] = {
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
#define SOC_SOC_N32G45X_SPI_CFG_START 
#ifdef BSP_USING_SPI1
    {

        .spi = SPI1,
        .name = "spi1",
#ifdef BSP_SPI1_REMAP_0
        .spi_remap = 0,
        .pin_sclk = GPIO_PIN_5,
        .pin_miso = GPIO_PIN_6,
        .pin_mosi = GPIO_PIN_7,
        .gpio_grp = GPIOA,
        .info = " PA5 PA6 PA7",
#endif /*BSP_SPI_REMAP_0*/
#ifdef BSP_SPI1_REMAP_1
        .spi_remap = GPIO_RMP1_SPI1,
        .pin_sclk = GPIO_PIN_3,
        .pin_miso = GPIO_PIN_4,
        .pin_mosi = GPIO_PIN_5,
        .gpio_grp = GPIOB,
        .info = " PB3 PB4 PB5 (JATG)",
#endif /*BSP_SPI_REMAP_1*/
#ifdef BSP_SPI1_REMAP_3
        .spi_remap = GPIO_RMP3_SPI1,
        .pin_sclk = GPIO_PIN_7,
        .pin_miso = GPIO_PIN_8,
        .pin_mosi = GPIO_PIN_9,
        .gpio_grp = GPIOE,
        .info = " PE7 PE8 PE9",
#endif /*BSP_SPI_REMAP_3*/
    },
#endif /*BSP_USING_SPI1*/

#ifdef BSP_USING_SPI2
    {

        .spi = SPI2,
        .name = "spi2",
#ifdef BSP_SPI2_REMAP_0
        .spi_remap = 0,
        .pin_sclk = GPIO_PIN_13,
        .pin_miso = GPIO_PIN_14,
        .pin_mosi = GPIO_PIN_15,
        .gpio_grp = GPIOB,
        .info = " PB13,PB14,PB15",
#endif /*BSP_SPI_REMAP_0*/
#ifdef BSP_SPI2_REMAP_1
        .spi_remap = GPIO_RMP1_SPI2,
        .pin_sclk = GPIO_PIN_7,
        .pin_miso = GPIO_PIN_8,
        .pin_mosi = GPIO_PIN_9,
        .gpio_grp = GPIOC,
        .info = " PC7 PC8 PC9",
#endif /*BSP_SPI_REMAP_1*/
#ifdef BSP_SPI2_REMAP_3
        .spi_remap = GPIO_RMP2_SPI2,
        .pin_sclk = GPIO_PIN_11,
        .pin_miso = GPIO_PIN_12,
        .pin_mosi = GPIO_PIN_13,
        .gpio_grp = GPIOE,
        .info = " PE11 PE12 PE13",
#endif /*BSP_SPI_REMAP_3*/
    },
#endif /*BSP_USING_SPI2*/

#ifdef BSP_USING_SPI3
    {

        .spi = SPI3,
        .name = "spi3",
#ifdef BSP_SPI3_REMAP_0
        .spi_remap = 0,
        .pin_sclk = GPIO_PIN_3,
        .pin_miso = GPIO_PIN_4,
        .pin_mosi = GPIO_PIN_5,
        .gpio_grp = GPIOB,
        .info = "spi3 PB3 PB4 PB5",
#endif /*BSP_SPI3_REMAP_0*/
#ifdef BSP_SPI3_REMAP_1
        .spi_remap = GPIO_RMP1_SPI3,
        .pin_sclk = GPIO_PIN_10,
        .pin_miso = GPIO_PIN_11,
        .pin_mosi = GPIO_PIN_12,
        .gpio_grp = GPIOC,
        .info = "spi3 PC10 PC11 PC12",
#endif /*BSP_SPI3_REMAP_1*/
#ifdef BSP_SPI3_REMAP2
        .spi_remap = GPIO_RMP2_SPI3,
        .pin_sclk = GPIO_PIN_9,
        .pin_miso = GPIO_PIN_10,
        .pin_mosi = GPIO_PIN_11,
        .gpio_grp = GPIOD,
        .info = "spi2 PD9 PD11 PD12",
#endif /*BSP_SPI3_REMAP_3*/
    },
#endif /*BSP_USING_SPI*/
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#define SOC_N32L43X_SPI_CFG_START //配置开始标记，无实际意义
#ifdef BSP_USING_SPI1
    {

        .spi = SPI1,
        .name = "spi1",
#ifdef BSP_SPI1_REMAP_0
        .pin_sclk = GPIO_PIN_5,
        .pin_sclk_remap = GPIO_AF0_SPI1,
        .pin_miso = GPIO_PIN_6,
        .pin_miso_remap = GPIO_AF0_SPI1,
        .pin_mosi = GPIO_PIN_7,
        .pin_mosi_remap = GPIO_AF0_SPI1,
        .gpio_grp = GPIOA,
        .info = " PA5 PA6 PA7",
#endif /*BSP_SPI_REMAP_0*/
#ifdef BSP_SPI1_REMAP_1
        .pin_sclk = GPIO_PIN_3,
        .pin_sclk_remap = GPIO_AF1_SPI1,
        .pin_miso = GPIO_PIN_4,
        .pin_miso_remap = GPIO_AF1_SPI1,
        .pin_mosi = GPIO_PIN_5,
        .pin_mosi_remap = GPIO_AF0_SPI1,
        .gpio_grp = GPIOB,
        .info = " PB3 PB4 PB5",
#endif /*BSP_SPI_REMAP_1*/
#ifdef BSP_SPI1_REMAP_2
        .pin_sclk = GPIO_PIN_4,
        .pin_sclk_remap = GPIO_AF5_SPI1,
        .pin_miso = GPIO_PIN_5,
        .pin_miso_remap = GPIO_AF5_SPI1,
        .pin_mosi = GPIO_PIN_6,
        .pin_mosi_remap = GPIO_AF5_SPI1,
        .gpio_grp = GPIOD,
        .info = "PD4 PD5 PD6",
#endif /*BSP_SPI_REMAP_2*/
    },
#endif /*BSP_USING_SPI1*/

#ifdef BSP_USING_SPI2
    {

        .spi = SPI2,
        .name = "spi2",
#ifdef BSP_SPI2_REMAP_0
        .pin_sclk = GPIO_PIN_13,
        .pin_sclk_remap = GPIO_AF0_SPI2,
        .pin_miso = GPIO_PIN_14,
        .pin_miso_remap = GPIO_AF0_SPI2,
        .pin_mosi = GPIO_PIN_15,
        .pin_mosi_remap = GPIO_AF0_SPI2,
        .gpio_grp = GPIOB,
        .info = " PB13 PB14 PB15",
#endif /*BSP_SPI_REMAP_0*/
#ifdef BSP_SPI2_REMAP_1
        .pin_sclk = GPIO_PIN_7,
        .pin_sclk_remap = GPIO_AF5_SPI2,
        .pin_miso = GPIO_PIN_8,
        .pin_miso_remap = GPIO_AF5_SPI2,
        .pin_mosi = GPIO_PIN_9,
        .pin_mosi_remap = GPIO_AF5_SPI2,
        .gpio_grp = GPIOC,
        .info = "PC7 PC8 PC9",
#endif /*BSP_SPI_REMAP_1*/
#ifdef BSP_SPI2_REMAP_2
        .pin_sclk = GPIO_PIN_10,
        .pin_sclk_remap = GPIO_AF5_SPI2,
        .pin_miso = GPIO_PIN_11,
        .pin_miso_remap = GPIO_AF0_SPI2,
        .pin_mosi = GPIO_PIN_12,
        .pin_mosi_remap = GPIO_AF0_SPI2,
        .gpio_grp = GPIOA,
        .info = "PA10 PA11 PA12",
#endif /*BSP_SPI_REMAP_2*/
    },
#endif /*BSP_USING_SPI2*/

#endif /*defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)*/
};

int rt_hw_spi_init(void)
{
    for (int i = 0; i < sizeof(n32_spi_hd) / sizeof(n32_spi_hd_t); i++)
    {
        n32_spi_init(n32_spi_hd + i);
    }
    return RT_EOK;


}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif /* defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) */
#endif
