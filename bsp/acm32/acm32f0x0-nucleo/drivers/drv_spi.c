/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-31     AisinoChip   first version
 */

#include "board.h"
#include <rtdevice.h>

#ifdef RT_USING_SPI

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2)

#include "spi_config.h"

enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX,
#endif
    SPI_MAX_INDEX
};

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
struct dma_config
{
    DMA_Channel_TypeDef *Instance;
    rt_uint32_t         dma_rcc;
    IRQn_Type           dma_irq;
    rt_uint32_t         channel;
    rt_uint32_t         request;
};
#endif

struct acm32_hw_spi_cs
{
    enum_GPIOx_t    GPIOx;
    uint16_t        GPIO_Pin;
};

struct acm32_spi_config
{
    SPI_TypeDef         *Instance;
    char                *bus_name;
    IRQn_Type           irq_type;
    enum_Enable_ID_t    enable_id;
#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
    struct dma_config   *dma_rx;
#endif
#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA)
    struct dma_config   *dma_tx;
#endif

    enum_GPIOx_t        cs_port;
    rt_uint32_t         cs_pin;
    rt_uint32_t         cs_alternate;

    enum_GPIOx_t        sck_port;
    rt_uint32_t         sck_pin;
    rt_uint32_t         sck_alternate;

    enum_GPIOx_t        mosi_port;
    rt_uint32_t         mosi_pin;
    rt_uint32_t         mosi_alternate;

    enum_GPIOx_t        miso_port;
    rt_uint32_t         miso_pin;
    rt_uint32_t         miso_alternate;

    enum_GPIOx_t        wp_port;
    rt_uint32_t         wp_pin;
    rt_uint32_t         wp_alternate;

    enum_GPIOx_t        hold_port;
    rt_uint32_t         hold_pin;
    rt_uint32_t         hold_alternate;
};

struct acm32_spi_device
{
    rt_uint32_t         pin;
    char                *bus_name;
    char                *device_name;
};

#define SPI_USING_RX_DMA_FLAG   (1<<0)
#define SPI_USING_TX_DMA_FLAG   (1<<1)

struct acm32_spi
{
    SPI_HandleTypeDef           handle;
    struct acm32_spi_config     *config;
    struct rt_spi_configuration *cfg;

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
    struct
    {
#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
        DMA_HandleTypeDef       handle_rx;
#endif
#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA)
        DMA_HandleTypeDef       handle_tx;
#endif
    } dma;

    rt_uint8_t                  spi_dma_flag;
#endif

    struct rt_spi_bus           spi_bus;
};

static struct acm32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif
};

static struct acm32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

static rt_err_t acm32_spi_init(struct acm32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;

    if (cfg->mode & RT_SPI_SLAVE)
    {
        spi_handle->Init.SPI_Mode = SPI_MODE_SLAVE;
    }
    else
    {
        spi_handle->Init.SPI_Mode = SPI_MODE_MASTER;
    }

    spi_handle->Init.X_Mode = SPI_1X_MODE;
    if (cfg->mode & RT_SPI_3WIRE)
    {
        return -RT_EINVAL;
    }

    if (cfg->data_width != 8)
    {
        return -RT_EINVAL;
    }

    switch (cfg->mode & RT_SPI_MODE_3)
    {
    case RT_SPI_MODE_0:
        spi_handle->Init.SPI_Work_Mode = SPI_WORK_MODE_0;
        break;
    case RT_SPI_MODE_1:
        spi_handle->Init.SPI_Work_Mode = SPI_WORK_MODE_1;
        break;
    case RT_SPI_MODE_2:
        spi_handle->Init.SPI_Work_Mode = SPI_WORK_MODE_2;
        break;
    case RT_SPI_MODE_3:
        spi_handle->Init.SPI_Work_Mode = SPI_WORK_MODE_3;
        break;
    }

    if (cfg->mode & RT_SPI_MSB)
    {
        spi_handle->Init.First_Bit = SPI_FIRSTBIT_MSB;
    }
    else
    {
        spi_handle->Init.First_Bit = SPI_FIRSTBIT_LSB;
    }

    uint32_t SPI_APB_CLOCK;
    SPI_APB_CLOCK = System_Get_SystemClock();

    if (cfg->max_hz >= SPI_APB_CLOCK / 4)
    {
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_4;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 8)
    {
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_8;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 16)
    {
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_16;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 32)
    {
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_32;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 64)
    {
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_64;
    }
    else if (cfg->max_hz >= SPI_APB_CLOCK / 128)
    {
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_128;
    }
    else
    {
        /*  min prescaler 254 */
        spi_handle->Init.BaudRate_Prescaler = SPI_BAUDRATE_PRESCALER_254;
    }

    if (HAL_SPI_Init(spi_handle) != HAL_OK)
    {
        return -RT_EIO;
    }

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
    /* DMA configuration */
    if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
    {
        HAL_DMA_Init(&spi_drv->dma.handle_rx);

        __HAL_LINK_DMA(spi_drv->handle, HDMA_Rx, spi_drv->dma.handle_rx);
    }
#endif

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA)
    if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
    {
        HAL_DMA_Init(&spi_drv->dma.handle_tx);

        __HAL_LINK_DMA(spi_drv->handle, HDMA_Tx, spi_drv->dma.handle_tx);
    }
#endif
#endif

    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    HAL_StatusTypeDef state;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;
    rt_uint32_t  timeout = 1000;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct acm32_spi *spi_drv =  rt_container_of(device->bus, struct acm32_spi, spi_bus);
    SPI_HandleTypeDef *spi_handle = &spi_drv->handle;
    struct acm32_hw_spi_cs *cs = device->parent.user_data;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS))
    {
        HAL_GPIO_WritePin(cs->GPIOx, cs->GPIO_Pin, GPIO_PIN_CLEAR);
    }

    recv_buf = message->recv_buf;
    send_buf = message->send_buf;

    /* start once data exchange in DMA mode */
    if (message->send_buf && message->recv_buf)
    {
#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
        if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG))
        {
            if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
            {
                state = HAL_SPI_Transmit_DMA(spi_handle, (uint8_t *)send_buf, message->length);
                while (HAL_SPI_GetTxState(spi_handle) != SPI_TX_STATE_IDLE);
            }
            else
            {
                state = HAL_SPI_Transmit(spi_handle, (uint8_t *)send_buf, message->length, timeout);
            }

            if (state == HAL_OK)
            {
                if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
                {
                    state = HAL_SPI_Receive_DMA(spi_handle, (uint8_t *)recv_buf, message->length);
                    while (HAL_SPI_GetRxState(spi_handle) != SPI_RX_STATE_IDLE);
                }
                else
                {
                    state = HAL_SPI_Receive_IT(spi_handle, (uint8_t *)recv_buf, message->length);
                    while (HAL_SPI_GetRxState(spi_handle) != SPI_RX_STATE_IDLE);
                }
            }
        }
        else
#endif
        {
            state = HAL_SPI_TransmitReceive(spi_handle, (uint8_t *)send_buf, (uint8_t *)recv_buf, message->length, timeout);
        }

        if (state != HAL_OK)
        {
            message->length = 0;
        }
    }
    else if (message->send_buf)
    {
#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA)
        if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
            state = HAL_SPI_Transmit_DMA(spi_handle, (uint8_t *)send_buf, message->length);
            while (HAL_SPI_GetTxState(spi_handle) != SPI_TX_STATE_IDLE);
        }
        else
#endif
        {
            state = HAL_SPI_Transmit(spi_handle, (uint8_t *)send_buf, message->length, 0);
        }
        if (state != HAL_OK)
        {
            message->length = 0;
        }
    }
    else
    {
        memset((uint8_t *)recv_buf, 0xff, message->length);
#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
        if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
            state = HAL_SPI_Receive_DMA(spi_handle, (uint8_t *)recv_buf, message->length);
            while (HAL_SPI_GetRxState(spi_handle) != SPI_RX_STATE_IDLE);
        }
        else
#endif
        {
            rt_kprintf("expect %d bytes\n", message->length);
            state = HAL_SPI_Receive_IT(spi_handle, (uint8_t *)recv_buf, message->length);
            while (HAL_SPI_GetRxState(spi_handle) != SPI_RX_STATE_IDLE);
            rt_kprintf("recv %d bytes\n", spi_handle->Rx_Count);
        }
        if (state != HAL_OK)
        {
            message->length = 0;
        }
    }

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        HAL_GPIO_WritePin(cs->GPIOx, cs->GPIO_Pin, GPIO_PIN_SET);
    }

    return message->length;
}

static rt_err_t _configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct acm32_spi *spi_drv =  rt_container_of(device->bus, struct acm32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return acm32_spi_init(spi_drv, configuration);
}

static const struct rt_spi_ops acm_spi_ops =
{
    .configure = _configure,
    .xfer = spixfer,
};

static int rt_hw_spi_bus_init(void)
{
    rt_err_t result = RT_EOK;

    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];
        spi_bus_obj[i].handle.Instance = spi_config[i].Instance;

#if defined(BSP_SPI1_RX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
            /* Configure the DMA handler for Transmission process */
            spi_bus_obj[i].dma.handle_rx.Instance               = spi_config[i].dma_rx->Instance;
            spi_bus_obj[i].dma.handle_rx.Init.Data_Flow         = DMA_DATA_FLOW_P2M;
            spi_bus_obj[i].dma.handle_rx.Init.Mode              = DMA_NORMAL;
            spi_bus_obj[i].dma.handle_rx.Init.Source_Inc        = DMA_SOURCE_ADDR_INCREASE_DISABLE;
            spi_bus_obj[i].dma.handle_rx.Init.Desination_Inc    = DMA_DST_ADDR_INCREASE_ENABLE;
            spi_bus_obj[i].dma.handle_rx.Init.Request_ID        = spi_config[i].dma_rx->request;
            spi_bus_obj[i].dma.handle_rx.Init.Source_Width      = DMA_SRC_WIDTH_BYTE;
            spi_bus_obj[i].dma.handle_rx.Init.Desination_Width  = DMA_DST_WIDTH_BYTE;
            spi_bus_obj[i].dma.handle_rx.DMA_ITC_Callback       = NULL;
            spi_bus_obj[i].dma.handle_rx.DMA_IE_Callback        = NULL;
        }
#endif

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA)
        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
            spi_bus_obj[i].dma.handle_tx.Instance               = spi_config[i].dma_tx->Instance;
            spi_bus_obj[i].dma.handle_tx.Init.Data_Flow         = DMA_DATA_FLOW_M2P;
            spi_bus_obj[i].dma.handle_tx.Init.Mode              = DMA_NORMAL;
            spi_bus_obj[i].dma.handle_tx.Init.Source_Inc        = DMA_SOURCE_ADDR_INCREASE_ENABLE;
            spi_bus_obj[i].dma.handle_tx.Init.Desination_Inc    = DMA_DST_ADDR_INCREASE_DISABLE;
            spi_bus_obj[i].dma.handle_tx.Init.Request_ID        = spi_config[i].dma_tx->request;
            spi_bus_obj[i].dma.handle_tx.Init.Source_Width      = DMA_SRC_WIDTH_BYTE;
            spi_bus_obj[i].dma.handle_tx.Init.Desination_Width  = DMA_DST_WIDTH_BYTE;
            spi_bus_obj[i].dma.handle_tx.DMA_ITC_Callback       = NULL;
            spi_bus_obj[i].dma.handle_tx.DMA_IE_Callback        = NULL;
        }
#endif

        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &acm_spi_ops);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

#if defined(BSP_USING_SPI1)
void SPI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI2)
void SPI2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

static void acm32_get_dma_info(void)
{
#ifdef BSP_SPI1_RX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi1_dma_rx = SPI1_RX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_rx = &spi1_dma_rx;
#endif
#ifdef BSP_SPI1_TX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_tx = &spi1_dma_tx;
#endif

#ifdef BSP_SPI2_RX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_rx = &spi2_dma_rx;
#endif
#ifdef BSP_SPI2_TX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_tx = &spi2_dma_tx;
#endif
}

int rt_hw_spi_init(void)
{
    acm32_get_dma_info();
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);

static uint32_t get_gpio_alternate(enum_GPIOx_t gpio_port, uint16_t gpio_pin)
{
    /* SPI1_CS : PA2->AF3 PA4->AF1 PA15->AF1 PB0->AF1 PB11->AF5  */
    /* SPI2_CS : PA8->AF4 PB9->AF4 PB12->AF4 */
    if (gpio_port == GPIOA || gpio_port == GPIOB)
    {
        if (gpio_port == GPIOA)
        {
            switch (gpio_pin)
            {
            case GPIO_PIN_2:
                return GPIO_FUNCTION_3;
            case GPIO_PIN_4:
                return GPIO_FUNCTION_1;
            case GPIO_PIN_8:
                return GPIO_FUNCTION_4;
            case GPIO_PIN_15:
                return GPIO_FUNCTION_1;
            default:
                return RT_UINT32_MAX;
            }
        }
        else
        {
            switch (gpio_pin)
            {
            case GPIO_PIN_0:
                return GPIO_FUNCTION_1;
            case GPIO_PIN_9:
                return GPIO_FUNCTION_4;
            case GPIO_PIN_11:
                return GPIO_FUNCTION_5;
            case GPIO_PIN_12:
                return GPIO_FUNCTION_4;
            default:
                return RT_UINT32_MAX;
            }
        }
    }

    return RT_UINT32_MAX;
}

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, enum_GPIOx_t cs_gpiox, uint16_t cs_gpio_pin)
{
    rt_uint32_t alternate;
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct acm32_hw_spi_cs *cs_pin;

    alternate = get_gpio_alternate(cs_gpiox, cs_gpio_pin);
    if (alternate == RT_UINT32_MAX)
    {
        return -RT_EINVAL;
    }

    /* initialize the cs pin && select the slave*/
    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin = cs_gpio_pin;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Alternate = alternate;
    HAL_GPIO_Init(cs_gpiox, &GPIO_Initure);

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct acm32_hw_spi_cs *)rt_malloc(sizeof(struct acm32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->GPIOx = cs_gpiox;
    cs_pin->GPIO_Pin = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    RT_ASSERT(result == RT_EOK);

    return result;
}

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    GPIO_InitTypeDef GPIO_Handle;
    struct acm32_spi *spi_drv;
    struct acm32_spi_config *spi_config;

    RT_ASSERT(hspi != RT_NULL);

    spi_drv =  rt_container_of(hspi, struct acm32_spi, handle);

    RT_ASSERT(spi_drv->spi_bus.parent.user_data != RT_NULL);

    spi_config = (struct acm32_spi_config *)spi_drv->spi_bus.parent.user_data;

    /* Enable Clock */
    System_Module_Enable(spi_config->enable_id);

    /* SPI CS */
    GPIO_Handle.Pin       = spi_config->cs_pin;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = spi_config->cs_alternate ;
    HAL_GPIO_Init(spi_config->cs_port, &GPIO_Handle);

    /* SPI SCK  */
    GPIO_Handle.Pin       = spi_config->sck_pin;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = spi_config->sck_alternate ;
    HAL_GPIO_Init(spi_config->sck_port, &GPIO_Handle);

    /* SPI MOSI */
    GPIO_Handle.Pin       = spi_config->mosi_pin;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = spi_config->mosi_alternate ;
    HAL_GPIO_Init(spi_config->mosi_port, &GPIO_Handle);

    /* SPI MISO */
    GPIO_Handle.Pin       = spi_config->miso_pin;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = spi_config->miso_alternate ;
    HAL_GPIO_Init(spi_config->miso_port, &GPIO_Handle);

    if (hspi->Init.X_Mode == SPI_4X_MODE)
    {
        /* SPI WP */
        GPIO_Handle.Pin       = spi_config->wp_pin;
        GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull      = GPIO_PULLUP;
        GPIO_Handle.Alternate = spi_config->wp_alternate ;
        HAL_GPIO_Init(spi_config->wp_port, &GPIO_Handle);

        /* SPI HOLD */
        GPIO_Handle.Pin       = spi_config->hold_pin;
        GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
        GPIO_Handle.Pull      = GPIO_PULLUP;
        GPIO_Handle.Alternate = spi_config->hold_alternate ;
        HAL_GPIO_Init(spi_config->hold_port, &GPIO_Handle);
    }

    /* Clear Pending Interrupt */
    NVIC_ClearPendingIRQ(spi_config->irq_type);

    /* Enable External Interrupt */
    NVIC_EnableIRQ(spi_config->irq_type);
}
#endif /* BSP_USING_SPI1 || BSP_USING_SPI2 */
#endif /* RT_USING_SPI */

