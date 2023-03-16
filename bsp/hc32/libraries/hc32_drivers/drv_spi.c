/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */


/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>

#if defined(RT_USING_SPI)

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3) || \
    defined(BSP_USING_SPI4) || defined(BSP_USING_SPI5) || defined(BSP_USING_SPI6)

#include "drv_spi.h"
#include "board_config.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
//#define DRV_DEBUG
#define LOG_TAG                         "drv.spi"
#include <drv_log.h>

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_spi_board_init(CM_SPI_TypeDef *CM_SPIx);

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
    static void spi1_rx_dma_irq_handle(void);
    static void spi1_tx_dma_irq_handle(void);
#endif  /* BSP_USING_SPI1 */

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
    static void spi2_rx_dma_irq_handle(void);
    static void spi2_tx_dma_irq_handle(void);
#endif  /* BSP_USING_SPI2 */

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA)
    static void spi3_rx_dma_irq_handle(void);
    static void spi3_tx_dma_irq_handle(void);
#endif  /* BSP_USING_SPI3 */

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA)
    static void spi4_rx_dma_irq_handle(void);
    static void spi4_tx_dma_irq_handle(void);
#endif  /* BSP_USING_SPI4 */

#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA)
    static void spi5_rx_dma_irq_handle(void);
    static void spi5_tx_dma_irq_handle(void);
#endif  /* BSP_USING_SPI5 */

#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA)
    static void spi6_rx_dma_irq_handle(void);
    static void spi6_tx_dma_irq_handle(void);
#endif  /* BSP_USING_SPI6 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
enum
{
#ifdef BSP_USING_SPI1
    SPI1_INDEX,
#endif
#ifdef BSP_USING_SPI2
    SPI2_INDEX,
#endif
#ifdef BSP_USING_SPI3
    SPI3_INDEX,
#endif
#ifdef BSP_USING_SPI4
    SPI4_INDEX,
#endif
#ifdef BSP_USING_SPI5
    SPI5_INDEX,
#endif
#ifdef BSP_USING_SPI6
    SPI6_INDEX,
#endif
};

static struct hc32_spi_config spi_config[] =
{
#ifdef BSP_USING_SPI1
    SPI1_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI2
    SPI2_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI3
    SPI3_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI4
    SPI4_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI5
    SPI5_BUS_CONFIG,
#endif

#ifdef BSP_USING_SPI6
    SPI6_BUS_CONFIG,
#endif
};

static struct hc32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static rt_err_t hc32_spi_init(struct hc32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    stc_spi_init_t stcSpiInit;
    stc_clock_freq_t stcClkFreq;
    CM_SPI_TypeDef *spi_instance = spi_drv->config->Instance;

    /* Enable spi clock */
    FCG_Fcg1PeriphClockCmd(spi_drv->config->clock, ENABLE);
    /* Init spi struct as default value */
    SPI_StructInit(&stcSpiInit);

    /* Slave or master mode */
    if (cfg->mode & RT_SPI_SLAVE)
    {
        stcSpiInit.u32MasterSlave = SPI_SLAVE;
    }
    else
    {
        stcSpiInit.u32MasterSlave = SPI_MASTER;
    }
    /* SI/SO pin shared */
    if (cfg->mode & RT_SPI_3WIRE)
    {
        return -RT_EINVAL;
    }
    else
    {
        stcSpiInit.u32TransMode = SPI_FULL_DUPLEX;
    }
    /* clock phase & polarity */
    if (RT_SPI_MODE_3 == (cfg->mode & RT_SPI_MODE_3))
    {
        stcSpiInit.u32SpiMode = SPI_MD_3;
    }
    else if (RT_SPI_MODE_2 == (cfg->mode & RT_SPI_MODE_3))
    {
        stcSpiInit.u32SpiMode = SPI_MD_2;
    }
    else if (RT_SPI_MODE_1 == (cfg->mode & RT_SPI_MODE_3))
    {
        stcSpiInit.u32SpiMode = SPI_MD_1;
    }
    else
    {
        stcSpiInit.u32SpiMode = SPI_MD_0;
    }
    /* No chipselect */
    if (cfg->mode & RT_SPI_NO_CS)
    {
        stcSpiInit.u32WireMode = SPI_4_WIRE;
    }
    else
    {
        stcSpiInit.u32WireMode = SPI_3_WIRE;
    }
    /* LSB or MSB */
    if (cfg->mode & RT_SPI_MSB)
    {
        stcSpiInit.u32FirstBit = SPI_FIRST_MSB;
    }
    else
    {
        stcSpiInit.u32FirstBit = SPI_FIRST_LSB;
    }
    /* config data width 8,16,32 */
    if (8 == cfg->data_width)
    {
        stcSpiInit.u32DataBits = SPI_DATA_SIZE_8BIT;
    }
    else if (16 == cfg->data_width)
    {
        stcSpiInit.u32DataBits = SPI_DATA_SIZE_16BIT;
    }
    else if (32 == cfg->data_width)
    {
        stcSpiInit.u32DataBits = SPI_DATA_SIZE_32BIT;
    }
    else
    {
        return -RT_EIO;
    }
    /* Get BUS clock */
    CLK_GetClockFreq(&stcClkFreq);
    if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 2)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV2;
    }
    else if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 4)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV4;
    }
    else if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 8)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV8;
    }
    else if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 16)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV16;
    }
    else if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 32)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV32;
    }
    else if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 64)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV64;
    }
    else if (cfg->max_hz >= stcClkFreq.u32Pclk1Freq / 128)
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV128;
    }
    else
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV256;
    }
    if ((cfg->mode & RT_SPI_SLAVE) && (stcSpiInit.u32BaudRatePrescaler < SPI_BR_CLK_DIV8))
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV8;
    }
    LOG_D("sys freq: %d, SPI freq: %d, BaudRatePrescaler: %d", stcClkFreq.u32HclkFreq, cfg->max_hz, stcSpiInit.u32BaudRatePrescaler);

    /* spi port init */
    rt_hw_spi_board_init(spi_instance);
    if (LL_OK != SPI_Init(spi_instance, &stcSpiInit))
    {
        return -RT_EIO;
    }

    /* DMA configuration */
    if (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        struct dma_config *spi_dma;
        stc_dma_init_t  stcDmaInit;

        /* Get spi dma_rx */
        spi_dma = spi_drv->config->dma_rx;
        /* Enable Dma clock */
        FCG_Fcg0PeriphClockCmd(spi_dma->clock, ENABLE);
        AOS_SetTriggerEventSrc(spi_dma->trigger_select, spi_dma->trigger_event);
        /* Config Dma */
        DMA_StructInit(&stcDmaInit);
        stcDmaInit.u32IntEn         = DMA_INT_ENABLE;
        stcDmaInit.u32BlockSize     = 1UL;
        stcDmaInit.u32TransCount    = 0;
        stcDmaInit.u32DestAddr      = 0;
        stcDmaInit.u32SrcAddr       = (uint32_t)(&spi_instance->DR);
        stcDmaInit.u32SrcAddrInc    = DMA_SRC_ADDR_FIX;
        stcDmaInit.u32DestAddrInc   = DMA_DEST_ADDR_INC;
        if (8 == cfg->data_width)
        {
            stcDmaInit.u32DataWidth = DMA_DATAWIDTH_8BIT;
        }
        else if (16 == cfg->data_width)
        {
            stcDmaInit.u32DataWidth = DMA_DATAWIDTH_16BIT;
        }
        else
        {
            stcDmaInit.u32DataWidth = DMA_DATAWIDTH_32BIT;
        }
        /* Init Dma */
        if (LL_OK != DMA_Init(spi_dma->Instance, spi_dma->channel, &stcDmaInit))
        {
            return -RT_EIO;
        }
        NVIC_EnableIRQ(spi_dma->irq_config.irq_num);
        /* Enable Dma */
        DMA_Cmd(spi_dma->Instance, ENABLE);
    }
    if (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        struct dma_config *spi_dma;
        stc_dma_init_t  stcDmaInit;

        /* Get spi dma_tx */
        spi_dma = spi_drv->config->dma_tx;
        FCG_Fcg0PeriphClockCmd(spi_dma->clock, ENABLE);
        AOS_SetTriggerEventSrc(spi_dma->trigger_select, spi_dma->trigger_event);
        /* Config Dma */
        DMA_StructInit(&stcDmaInit);
        stcDmaInit.u32IntEn         = DMA_INT_ENABLE;
        stcDmaInit.u32BlockSize     = 1UL;
        stcDmaInit.u32TransCount    = 0;
        stcDmaInit.u32DestAddr      = (uint32_t)(&spi_instance->DR);;
        stcDmaInit.u32SrcAddr       = 0;
        stcDmaInit.u32SrcAddrInc    = DMA_SRC_ADDR_INC;
        stcDmaInit.u32DestAddrInc   = DMA_DEST_ADDR_FIX;
        if (8 == cfg->data_width)
        {
            stcDmaInit.u32DataWidth = DMA_DATAWIDTH_8BIT;
        }
        else if (16 == cfg->data_width)
        {
            stcDmaInit.u32DataWidth = DMA_DATAWIDTH_16BIT;
        }
        else
        {
            stcDmaInit.u32DataWidth = DMA_DATAWIDTH_32BIT;
        }
        /* Init Dma */
        if (LL_OK != DMA_Init(spi_dma->Instance, spi_dma->channel, &stcDmaInit))
        {
            return -RT_EIO;
        }
        NVIC_EnableIRQ(spi_dma->irq_config.irq_num);
        /* Enable Dma */
        DMA_Cmd(spi_dma->Instance, ENABLE);
    }

    LOG_D("%s init done", spi_drv->config->bus_name);
    return RT_EOK;
}

static rt_err_t hc32_spi_configure(struct rt_spi_device *device,
                                   struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct hc32_spi *spi_drv =  rt_container_of(device->bus, struct hc32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return hc32_spi_init(spi_drv, configuration);
}

static int32_t hc32_spi_dma_trans(struct hc32_spi_config *spi_config, const uint8_t *pvTxBuf, void *pvRxBuf, uint32_t u32Length)
{
    if ((spi_config == RT_NULL) || (pvTxBuf == RT_NULL) || (pvRxBuf == RT_NULL))
    {
        return LL_ERR;
    }

    SPI_Cmd(spi_config->Instance, DISABLE);
    if (RT_NULL == pvTxBuf)
    {
        DMA_SetSrcAddr(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, (uint32_t)pvTxBuf);
        DMA_SetTransCount(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, u32Length);
        DMA_ChCmd(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, ENABLE);
    }
    if (RT_NULL == pvRxBuf)
    {
        DMA_SetDestAddr(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, (uint32_t)pvRxBuf);
        DMA_SetTransCount(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, u32Length);
        DMA_ChCmd(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, ENABLE);
    }
    SPI_Cmd(spi_config->Instance, ENABLE);

    return LL_OK;
}

static void hc32_spi_enable(CM_SPI_TypeDef *SPIx)
{
    /* Check if the SPI is already enabled */
    if ((SPIx->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SPI_Cmd(SPIx, ENABLE);
    }
}

static rt_uint32_t hc32_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    int32_t state;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct hc32_spi *spi_drv =  rt_container_of(device->bus, struct hc32_spi, spi_bus);
    CM_SPI_TypeDef *spi_instance = spi_drv->config->Instance;
    struct hc32_hw_spi_cs *cs = device->parent.user_data;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            GPIO_SetPins(cs->port, cs->pin);
        }
        else
        {
            GPIO_ResetPins(cs->port, cs->pin);
        }
    }
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d", spi_drv->config->bus_name,
          (uint32_t)message->send_buf, (uint32_t)message->recv_buf, message->length);

    message_length  = message->length;
    recv_buf        = message->recv_buf;
    send_buf        = message->send_buf;
    while (message_length)
    {
        if (message_length > 65535)
        {
            send_length     = 65535;
            message_length  = message_length - 65535;
        }
        else
        {
            send_length     = message_length;
            message_length  = 0;
        }

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        if (message->send_buf && message->recv_buf)
        {
            if ((spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX) && (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX))
            {
                state = hc32_spi_dma_trans(spi_drv->config, send_buf, recv_buf, send_length);
            }
            else
            {
                hc32_spi_enable(spi_instance);
                state = SPI_TransReceive(spi_instance, send_buf, recv_buf, send_length, 1000);
            }
        }
        else if (message->send_buf)
        {
            if (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            {
                /* Maybe need to switch to send only mode */
                state = hc32_spi_dma_trans(spi_drv->config, send_buf, RT_NULL, send_length);
            }
            else
            {
                hc32_spi_enable(spi_instance);
                state = SPI_Trans(spi_instance, send_buf, send_length, 1000);
            }
        }
        else
        {
            rt_memset((uint8_t *)recv_buf, 0xFF, send_length);
            if (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX)
            {
                state = hc32_spi_dma_trans(spi_drv->config, recv_buf, recv_buf, send_length);
            }
            else
            {
                hc32_spi_enable(spi_instance);
                state = SPI_Receive(spi_instance, recv_buf, send_length, 1000);
            }
        }
        if (state != LL_OK)
        {
            LOG_I("spi transfer error : %d", state);
            message->length = 0;
        }
        /* Wait for the spi transfer complete */
        while (RESET != SPI_GetStatus(spi_instance, SPI_FLAG_IDLE));
    }
    /* clear error flag */
    SPI_ClearStatus(spi_instance, SPI_FLAG_CLR_ALL | SPI_FLAG_RX_BUF_FULL);

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            GPIO_ResetPins(cs->port, cs->pin);
        }
        else
        {
            GPIO_SetPins(cs->port, cs->pin);
        }
    }

    return message->length;
}

static const struct rt_spi_ops hc32_spi_ops =
{
    .configure  = hc32_spi_configure,
    .xfer       = hc32_spi_xfer,
};

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, uint8_t cs_gpio_port, uint16_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct hc32_hw_spi_cs *cs_pin;
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinState = PIN_STAT_SET;
    stcGpioInit.u16PinDir   = PIN_DIR_OUT;
    stcGpioInit.u16PullUp   = PIN_PU_ON;
    GPIO_Init(cs_gpio_port, cs_gpio_pin, &stcGpioInit);

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct hc32_hw_spi_cs *)rt_malloc(sizeof(struct hc32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->port = cs_gpio_port;
    cs_pin->pin  = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    return result;
}

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI4_TX_USING_DMA) || \
    defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI6_TX_USING_DMA)
/**
  * @brief  Clear DMA transfer complete flag.
  * @param  dma     specific dam witch spi used.
  * @retval None
  */
static void hc32_dma_irq_handle(struct dma_config *dma)
{
    DMA_ClearTransCompleteStatus(dma->Instance, (1U << dma->channel));
}
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi1_rx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI1_INDEX].dma_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi1_tx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI1_INDEX].dma_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi2_rx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI2_INDEX].dma_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi2_tx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI2_INDEX].dma_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi3_rx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI3_INDEX].dma_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi3_tx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI3_INDEX].dma_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi4_rx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI4_INDEX].dma_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi4_tx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI4_INDEX].dma_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi5_rx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI5_INDEX].dma_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi5_tx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI5_INDEX].dma_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi6_rx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI6_INDEX].dma_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx complete interrupt request.
  * @param  None
  * @retval None
  */
static void spi6_tx_dma_irq_handle(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_dma_irq_handle(spi_config[SPI6_INDEX].dma_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

/**
  * @brief  This function gets dma witch spi used infomation include unit,
  *         channel, interrupt etc.
  * @param  None
  * @retval None
  */
static void hc32_get_dma_info(void)
{
#ifdef BSP_SPI1_RX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi1_dma_rx = SPI1_RX_DMA_CONFIG;
    spi1_dma_rx.irq_callback        = spi1_rx_dma_irq_handle;
    spi_config[SPI1_INDEX].dma_rx   = &spi1_dma_rx;
#endif
#ifdef BSP_SPI1_TX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi1_dma_tx.irq_callback        = spi1_tx_dma_irq_handle;
    spi_config[SPI1_INDEX].dma_tx   = &spi1_dma_tx;
#endif

#ifdef BSP_SPI2_RX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi2_dma_rx.irq_callback        = spi2_rx_dma_irq_handle;
    spi_config[SPI2_INDEX].dma_rx   = &spi2_dma_rx;
#endif
#ifdef BSP_SPI2_TX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi2_dma_tx.irq_callback        = spi2_tx_dma_irq_handle;
    spi_config[SPI2_INDEX].dma_tx   = &spi2_dma_tx;
#endif

#ifdef BSP_SPI3_RX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi3_dma_rx.irq_callback        = spi3_rx_dma_irq_handle;
    spi_config[SPI3_INDEX].dma_rx   = &spi3_dma_rx;
#endif
#ifdef BSP_SPI3_TX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi3_dma_tx.irq_callback        = spi3_tx_dma_irq_handle;
    spi_config[SPI3_INDEX].dma_tx   = &spi3_dma_tx;
#endif

#ifdef BSP_SPI4_RX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi4_dma_rx.irq_callback        = spi4_rx_dma_irq_handle;
    spi_config[SPI4_INDEX].dma_rx   = &spi4_dma_rx;
#endif
#ifdef BSP_SPI4_TX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi4_dma_tx.irq_callback        = spi4_tx_dma_irq_handle;
    spi_config[SPI4_INDEX].dma_tx   = &spi4_dma_tx;
#endif

#ifdef BSP_SPI5_RX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi5_dma_rx = SPI5_RX_DMA_CONFIG;
    spi5_dma_rx.irq_callback        = spi5_rx_dma_irq_handle;
    spi_config[SPI5_INDEX].dma_rx   = &spi5_dma_rx;
#endif
#ifdef BSP_SPI5_TX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi5_dma_tx = SPI5_TX_DMA_CONFIG;
    spi5_dma_tx.irq_callback        = spi5_tx_dma_irq_handle;
    spi_config[SPI5_INDEX].dma_tx   = &spi5_dma_tx;
#endif

#ifdef BSP_SPI6_RX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi6_dma_rx = SPI6_RX_DMA_CONFIG;
    spi6_dma_rx.irq_callback        = spi6_rx_dma_irq_handle;
    spi_config[SPI6_INDEX].dma_rx   = &spi6_dma_rx;
#endif
#ifdef BSP_SPI6_TX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi6_dma_tx = SPI6_TX_DMA_CONFIG;
    spi6_dma_tx.irq_callback        = spi6_tx_dma_irq_handle;
    spi_config[SPI6_INDEX].dma_tx   = &spi6_dma_tx;
#endif
}

static int hc32_hw_spi_bus_init(void)
{
    rt_err_t result;

    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];

        if (spi_bus_obj[i].spi_dma_flag & RT_DEVICE_FLAG_DMA_RX)
        {
            /* Configure the DMA handler */
            hc32_install_irq_handler(&spi_config[i].dma_rx->irq_config, spi_config[i].dma_rx->irq_callback, RT_FALSE);
        }
        if (spi_bus_obj[i].spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
        {
            /* Configure the DMA handler */
            hc32_install_irq_handler(&spi_config[i].dma_tx->irq_config, spi_config[i].dma_tx->irq_callback, RT_FALSE);
        }

        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &hc32_spi_ops);
        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}

int hc32_hw_spi_init(void)
{
    hc32_get_dma_info();
    return hc32_hw_spi_bus_init();
}

INIT_BOARD_EXPORT(hc32_hw_spi_init);

#endif

#endif /* BSP_USING_SPI */
