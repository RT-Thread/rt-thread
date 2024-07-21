/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include <rtdbg.h>
#include "drv_spi.h"

#ifdef RT_USING_SPI
#if !defined(BSP_USING_SPI0) && !defined(BSP_USING_SPI1)
    #error "Please define at least one BSP_USING_SPIx"
#endif

struct ht32_spi_config
{
    HT_SPI_TypeDef *spi_x;
    const char *spi_name;
    IRQn_Type irq;
};

struct ht32_spi
{
    struct ht32_spi_config *config;
    struct rt_spi_bus spi_bus;
};

struct ht32_spi_cs
{
    HT_GPIO_TypeDef *gpio_x;
    uint32_t gpio_pin;
};

enum
{
#ifdef BSP_USING_SPI0
    SPI0_INDEX,
#endif
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
};

static struct ht32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI0
    {
    .spi_x          = HT_SPI0,
    .spi_name       = BSP_USING_SPI0_NAME,
    .irq            = SPI0_IRQn
    },
#endif
#ifdef BSP_USING_SPI1
    {
    .spi_x          = HT_SPI1,
    .spi_name       = BSP_USING_SPI1_NAME,
    .irq            = SPI1_IRQn
    },
#endif
};

static struct ht32_spi spis[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

/* attach the spi device to spi bus, this function must be used after initialization */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, HT_GPIO_TypeDef *cs_gpiox, uint16_t cs_gpio_pin)
{
    CKCU_PeripClockConfig_TypeDef   CKCUClock = {{0}};

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct ht32_spi_cs *cs_pin;

    if ((cs_gpiox) == HT_GPIOA)
    {
        CKCUClock.Bit.PA         = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);
        AFIO_GPxConfig(GPIO_PA, cs_gpio_pin, AFIO_FUN_GPIO);
    }
    else if ((cs_gpiox) == HT_GPIOB)
    {
        CKCUClock.Bit.PB         = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);
        AFIO_GPxConfig(GPIO_PB, cs_gpio_pin, AFIO_FUN_GPIO);
    }
#if defined(HT_GPIOC)
    else if ((cs_gpiox) == HT_GPIOC)
    {
        CKCUClock.Bit.PC         = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);
        AFIO_GPxConfig(GPIO_PC, cs_gpio_pin, AFIO_FUN_GPIO);
    }
#endif
#if defined(HT_GPIOD)
    else if ((cs_gpiox) == HT_GPIOD)
    {
        CKCUClock.Bit.PD         = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);
        AFIO_GPxConfig(GPIO_PD, cs_gpio_pin, AFIO_FUN_GPIO);
    }
#endif
#if defined(HT_GPIOE)
    else if ((cs_gpiox) == HT_GPIOE)
    {
        CKCUClock.Bit.PE         = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);
        AFIO_GPxConfig(GPIO_PE, cs_gpio_pin, AFIO_FUN_GPIO);
    }
#endif
#if defined(HT_GPIOF)
    else if ((cs_gpiox) == HT_GPIOF)
    {
        CKCUClock.Bit.PF         = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);
        AFIO_GPxConfig(GPIO_PF, cs_gpio_pin, AFIO_FUN_GPIO);
    }
#endif
    GPIO_PullResistorConfig(cs_gpiox, cs_gpio_pin, GPIO_PR_DISABLE);
    GPIO_WriteOutBits(cs_gpiox, cs_gpio_pin, SET);
    GPIO_DirectionConfig(cs_gpiox, cs_gpio_pin, GPIO_DIR_OUT);

    /* attach the device to spi bus */
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct ht32_spi_cs *)rt_malloc(sizeof(struct ht32_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->gpio_x = cs_gpiox;
    cs_pin->gpio_pin = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_D("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

static rt_err_t ht32_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    struct rt_spi_bus *spi_bus = (struct rt_spi_bus *)device->bus;
    struct ht32_spi *spi_instance = (struct ht32_spi *)spi_bus->parent.user_data;

    SPI_InitTypeDef     SPI_InitStructure;
    CKCU_PeripClockConfig_TypeDef   CKCUClock = {{0}};

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);
#ifdef BSP_USING_SPI0
    if (HT_SPI0 == spi_instance->config->spi_x)
    {
        CKCUClock.Bit.SPI0       = 1;
    }
#endif
#ifdef BSP_USING_SPI1
    if (HT_SPI1 == spi_instance->config->spi_x)
    {
        CKCUClock.Bit.SPI1       = 1;
    }
#endif
    CKCUClock.Bit.AFIO       = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    ht32_spi_gpio_init(spi_instance->config->spi_x);

    /* data_width */
    if (configuration->data_width <= 8)
    {
        SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
    }
    else if (configuration->data_width <= 16)
    {
        SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_16;
    }
    else
    {
        return -RT_ERROR;
    }

    /* Set the polarity and phase of the SPI */
    switch (configuration->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        SPI_InitStructure.SPI_CPOL  =   SPI_CPOL_LOW;
        SPI_InitStructure.SPI_CPHA  =   SPI_CPHA_FIRST;
        break;
    case RT_SPI_MODE_1:
        SPI_InitStructure.SPI_CPOL  =   SPI_CPOL_LOW;
        SPI_InitStructure.SPI_CPHA  =   SPI_CPHA_SECOND;
        break;
    case RT_SPI_MODE_2:
        SPI_InitStructure.SPI_CPOL  =   SPI_CPOL_HIGH;
        SPI_InitStructure.SPI_CPHA  =   SPI_CPHA_FIRST;
        break;
    case RT_SPI_MODE_3:
        SPI_InitStructure.SPI_CPOL  =   SPI_CPOL_HIGH;
        SPI_InitStructure.SPI_CPHA  =   SPI_CPHA_SECOND;
        break;
    }

    /* Set the SPI as a master or slave */
    SPI_InitStructure.SPI_Mode = (configuration->mode & RT_SPI_SLAVE) ? (SPI_SLAVE) : (SPI_MASTER);

    /* Set the data high or low first */
    SPI_InitStructure.SPI_FirstBit = (configuration->mode & RT_SPI_MSB) ? (SPI_FIRSTBIT_MSB) : (SPI_FIRSTBIT_LSB);

    /* SEL uses software by default */
    SPI_InitStructure.SPI_SELMode = SPI_SEL_SOFTWARE;

    /* SEL effective level */
    SPI_InitStructure.SPI_SELPolarity = (configuration->mode & RT_SPI_CS_HIGH) ? (SPI_SELPOLARITY_HIGH) : (SPI_SELPOLARITY_LOW);

    /* Configure the SCK clock frequency of the SPI */
    if (configuration->max_hz < 0xFFFF)
    {
        SPI_InitStructure.SPI_ClockPrescaler = ((configuration->max_hz) & 0xFFFF);
    }
    else
    {
        return -RT_ERROR;
    }

    SPI_InitStructure.SPI_FIFO  =   SPI_FIFO_DISABLE;
    SPI_InitStructure.SPI_RxFIFOTriggerLevel    =   0;
    SPI_InitStructure.SPI_TxFIFOTriggerLevel    =   0;
    SPI_Init(spi_instance->config->spi_x, &SPI_InitStructure);
#if (!LIBCFG_SPI_NO_MULTI_MASTER)
    SPI_SELOutputCmd(spi_instance->config->spi_x, ENABLE);
#endif

    SPI_Cmd(spi_instance->config->spi_x, ENABLE);
    return RT_EOK;
}

static rt_ssize_t ht32_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct rt_spi_bus *ht32_spi_bus = (struct rt_spi_bus *)device->bus;
    struct ht32_spi *spi_instance = (struct ht32_spi *)ht32_spi_bus->parent.user_data;
    struct rt_spi_configuration *config = &device->config;
    struct ht32_spi_cs *ht32_spi_cs = device->parent.user_data;

    RT_ASSERT(device != NULL);
    RT_ASSERT(message != NULL);

    /* take cs */
    if (message->cs_take)
    {
        GPIO_ClearOutBits(ht32_spi_cs->gpio_x, ht32_spi_cs->gpio_pin);
        LOG_D("spi take cs\n");
    }

    if (config->data_width <= 8)
    {
        const rt_uint8_t *send_ptr = message->send_buf;
        rt_uint8_t *recv_ptr = message->recv_buf;
        rt_uint32_t size = message->length;

        LOG_D("spi poll transfer start: %d\n", size);

        while (size--)
        {
            rt_uint8_t data = 0xFF;

            if (send_ptr != RT_NULL)
            {
                data = *send_ptr++;
            }

            /* wait until the transmit buffer is empty */
            while (SPI_GetFlagStatus(spi_instance->config->spi_x, SPI_FLAG_TXE) == RESET);
            /* send the byte */
            SPI_SendData(spi_instance->config->spi_x, data);

            /* wait until a data is received */
            while (SPI_GetFlagStatus(spi_instance->config->spi_x, SPI_INT_RXBNE) == RESET);
            /* get the received data */
            data = SPI_ReceiveData(spi_instance->config->spi_x);

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

            /* wait until the transmit buffer is empty */
            while (SPI_GetFlagStatus(spi_instance->config->spi_x, SPI_FLAG_TXE) == RESET);
            /* send the byte */
            SPI_SendData(spi_instance->config->spi_x, data);

            /* wait until a data is received */
            while (SPI_GetFlagStatus(spi_instance->config->spi_x, SPI_INT_RXBNE) == RESET);
            /* get the received data */
            data = SPI_ReceiveData(spi_instance->config->spi_x);

            if (recv_ptr != RT_NULL)
            {
                *recv_ptr++ = data;
            }
        }
    }

    /* release cs */
    if (message->cs_release)
    {
        GPIO_SetOutBits(ht32_spi_cs->gpio_x, ht32_spi_cs->gpio_pin);
        LOG_D("spi release cs\n");
    }

    return message->length;
}

static struct rt_spi_ops ht32_spi_ops =
{
    .configure = ht32_configure,
    .xfer = ht32_xfer
};

int rt_hw_spi_init(void)
{
    int i;
    rt_err_t result;
    rt_size_t obj_num = sizeof(spis) / sizeof(struct ht32_spi);

    for (i = 0; i < obj_num; i++)
    {
        spis[i].config = &spi_config[i];
        spis[i].spi_bus.parent.user_data = (void *)&spis[i];
        result = rt_spi_bus_register(&spis[i].spi_bus, spis[i].config->spi_name, &ht32_spi_ops);
    }
    return result;
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

#endif  /* RT_USING_SPI */
