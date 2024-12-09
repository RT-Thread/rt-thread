/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2023-09-30     CDT          Delete dma transmit interrupt
 * 2024-02-20     CDT          support HC32F448
 * 2024-04-16     CDT          support HC32F472
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

/* SPI max division */
#define SPI_MAX_DIV_VAL                 (0x7U)  /* Div256 */

#ifdef BSP_SPI_USING_DMA
    #define DMA_CH_REG(reg_base, ch)    (*(__IO uint32_t *)((uint32_t)(&(reg_base)) + ((ch) * 0x40UL)))
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_spi_board_init(CM_SPI_TypeDef *CM_SPIx);

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

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

    uint32_t u32Cnt = 0;
    uint32_t u32BusFreq;
    stc_spi_init_t stcSpiInit;
    CM_SPI_TypeDef *spi_instance = spi_drv->config->Instance;

    /* Enable spi clock */
    FCG_Fcg1PeriphClockCmd(spi_drv->config->clock, ENABLE);
    /* Init spi struct as default value */
    SPI_StructInit(&stcSpiInit);

    if ((cfg->mode & RT_SPI_SLAVE) &&
            ((RT_SPI_MODE_0 == (cfg->mode & RT_SPI_MODE_3)) || (RT_SPI_MODE_2 == (cfg->mode & RT_SPI_MODE_3))))
    {
        return -RT_EINVAL;
    }
    /* Slave or master mode */
    if (cfg->mode & RT_SPI_SLAVE)
    {
        stcSpiInit.u32MasterSlave = SPI_SLAVE;
        stcSpiInit.u32ModeFaultDetect = SPI_MD_FAULT_DETECT_ENABLE;
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
    u32BusFreq = CLK_GetBusClockFreq(CLK_BUS_PCLK1);
    while (cfg->max_hz < u32BusFreq / (1UL << (u32Cnt + 1U)))
    {
        u32Cnt++;
        if (u32Cnt >= SPI_MAX_DIV_VAL)  /* Div256 */
        {
            break;
        }
    }
    stcSpiInit.u32BaudRatePrescaler = (u32Cnt << SPI_CFG2_MBR_POS);
    /* slave limit */
    if ((cfg->mode & RT_SPI_SLAVE) && (stcSpiInit.u32BaudRatePrescaler < SPI_BR_CLK_DIV8))
    {
        stcSpiInit.u32BaudRatePrescaler = SPI_BR_CLK_DIV8;
    }
    LOG_D("Bus freq: %d, SPI freq: %d, BaudRatePrescaler: %d", u32BusFreq, cfg->max_hz, stcSpiInit.u32BaudRatePrescaler);

    /* spi port init */
    rt_hw_spi_board_init(spi_instance);
    if (LL_OK != SPI_Init(spi_instance, &stcSpiInit))
    {
        return -RT_EIO;
    }

#ifdef BSP_SPI_USING_DMA
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
        stcDmaInit.u32BlockSize     = 1UL;
        stcDmaInit.u32SrcAddr       = (uint32_t)(&spi_instance->DR);
        stcDmaInit.u32SrcAddrInc    = DMA_SRC_ADDR_FIX;
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
        stcDmaInit.u32BlockSize     = 1UL;
        stcDmaInit.u32DestAddr      = (uint32_t)(&spi_instance->DR);;
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
        /* Enable Dma */
        DMA_Cmd(spi_dma->Instance, ENABLE);
    }
#endif

    /* Enable error interrupt */
#if defined (HC32F448) || defined (HC32F472)
    INTC_IntSrcCmd(spi_drv->config->err_irq.irq_config.int_src, ENABLE);
#endif
    NVIC_EnableIRQ(spi_drv->config->err_irq.irq_config.irq_num);
    SPI_IntCmd(spi_instance, SPI_INT_ERR, ENABLE);

    LOG_D("%s init done", spi_drv->config->bus_name);
    return RT_EOK;
}

static void hc32_spi_enable(CM_SPI_TypeDef *SPIx)
{
    /* Check if the SPI is already enabled */
#if defined (HC32F460) || defined (HC32F4A0)
    if ((SPIx->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SPI_Cmd(SPIx, ENABLE);
    }
#elif defined (HC32F448) || defined (HC32F472)
    if ((SPIx->CR & SPI_CR_SPE) != SPI_CR_SPE)
    {
        SPI_Cmd(SPIx, ENABLE);
    }
#else
#error "Please select first the target HC32xxxx device used in your application."
#endif
}

static void hc32_spi_set_trans_mode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode)
{
#if defined (HC32F460) || defined (HC32F4A0)
    if (SPI_SEND_ONLY == u32Mode)
    {
        SET_REG32_BIT(SPIx->CR1, SPI_CR1_TXMDS);
    }
    else
    {
        CLR_REG32_BIT(SPIx->CR1, SPI_CR1_TXMDS);
    }
#elif defined (HC32F448) || defined (HC32F472)
    if (SPI_SEND_ONLY == u32Mode)
    {
        SET_REG32_BIT(SPIx->CR, SPI_CR_TXMDS);
    }
    else
    {
        CLR_REG32_BIT(SPIx->CR, SPI_CR_TXMDS);
    }
#else
#error "Please select first the target HC32xxxx device used in your application."
#endif
}

#ifdef BSP_SPI_USING_DMA
static uint32_t hc32_spi_get_trans_mode(CM_SPI_TypeDef *SPIx)
{
#if defined (HC32F460) || defined (HC32F4A0)
    return READ_REG32_BIT(SPIx->CR1, SPI_CR1_TXMDS);
#elif defined (HC32F448) || defined (HC32F472)
    return READ_REG32_BIT(SPIx->CR, SPI_CR_TXMDS);
#else
#error "Please select first the target HC32xxxx device used in your application."
#endif
}

/**
 * @brief  Config DMA source address increment mode.
 * @param  [in] DMAx DMA unit instance.
 * @param  [in] u8Ch DMA channel.
 * @param  [in] u32IncMode DMA source address increment mode @ref DMA_SrcAddr_Incremented_Mode
 * @retval None
 */
void DMA_SetSrcAddrIncMode(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32IncMode)
{
    __IO uint32_t *CHCTLx;

    CHCTLx = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
    MODIFY_REG32(*CHCTLx, DMA_CHCTL_SINC, u32IncMode);
}

/**
 * @brief  Config DMA destination address increment mode.
 * @param  [in] DMAx DMA unit instance.
 * @param  [in] u8Ch DMA channel.
 * @param  [in] u16Count DMA destination address increment mode @ref DMA_DesAddr_Incremented_Mode
 * @retval None
 */
void DMA_SetDestAddrIncMode(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32IncMode)
{
    __IO uint32_t *CHCTLx;

    CHCTLx = &DMA_CH_REG(DMAx->CHCTL0, u8Ch);
    MODIFY_REG32(*CHCTLx, DMA_CHCTL_DINC, u32IncMode);
}
#endif

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
    int32_t i32Ret = LL_OK;
#ifdef BSP_SPI_USING_DMA
    rt_uint32_t u32TimeoutCnt;
    CM_DMA_TypeDef *DmaInstance;
    rt_uint32_t DmaFlag;
    uint32_t u32TxTmp, u32RxTmp;

    if ((spi_config == RT_NULL) || ((pvTxBuf == RT_NULL) && (pvRxBuf == RT_NULL)))
    {
        return LL_ERR;
    }

    SPI_Cmd(spi_config->Instance, DISABLE);
    if (RT_NULL != pvTxBuf)
    {
        DMA_ClearTransCompleteStatus(spi_config->dma_tx->Instance, spi_config->dma_tx->flag);
        DMA_SetSrcAddr(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, (uint32_t)pvTxBuf);
        DMA_SetSrcAddrIncMode(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, DMA_SRC_ADDR_INC);
        DMA_SetTransCount(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, u32Length);
        DMA_ChCmd(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, ENABLE);
    }
    else
    {
        if (SPI_FULL_DUPLEX == hc32_spi_get_trans_mode(spi_config->Instance))
        {
            u32TxTmp = 0xFFFFFFFFUL;
            DMA_ClearTransCompleteStatus(spi_config->dma_tx->Instance, spi_config->dma_tx->flag);
            DMA_SetSrcAddr(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, (uint32_t)&u32TxTmp);
            DMA_SetSrcAddrIncMode(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, DMA_SRC_ADDR_FIX);
            DMA_SetTransCount(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, u32Length);
            DMA_ChCmd(spi_config->dma_tx->Instance, spi_config->dma_tx->channel, ENABLE);
        }
    }
    if (RT_NULL != pvRxBuf)
    {
        DMA_ClearTransCompleteStatus(spi_config->dma_rx->Instance, spi_config->dma_rx->flag);
        DMA_SetDestAddr(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, (uint32_t)pvRxBuf);
        DMA_SetDestAddrIncMode(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, DMA_DEST_ADDR_INC);
        DMA_SetTransCount(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, u32Length);
        DMA_ChCmd(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, ENABLE);
    }
    else
    {
        if (SPI_FULL_DUPLEX == hc32_spi_get_trans_mode(spi_config->Instance))
        {
            DMA_ClearTransCompleteStatus(spi_config->dma_rx->Instance, spi_config->dma_rx->flag);
            DMA_SetDestAddr(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, (uint32_t)&u32RxTmp);
            DMA_SetDestAddrIncMode(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, DMA_DEST_ADDR_FIX);
            DMA_SetTransCount(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, u32Length);
            DMA_ChCmd(spi_config->dma_rx->Instance, spi_config->dma_rx->channel, ENABLE);
        }
    }
    SPI_Cmd(spi_config->Instance, ENABLE);

    u32TimeoutCnt = 0U;
    /* Wait DMA transfer completed */
    if (RT_NULL != pvRxBuf)
    {
        DmaInstance = spi_config->dma_rx->Instance;
        DmaFlag = spi_config->dma_rx->flag;
    }
    else
    {
        DmaInstance = spi_config->dma_tx->Instance;
        DmaFlag = spi_config->dma_tx->flag;
    }
    while ((RESET == DMA_GetTransCompleteStatus(DmaInstance, DmaFlag)) &&
            (u32TimeoutCnt < spi_config->timeout))
    {
        rt_thread_mdelay(1);
        u32TimeoutCnt++;
    }
    if (u32TimeoutCnt >= spi_config->timeout)
    {
        i32Ret = LL_ERR_TIMEOUT;
    }
#endif

    return i32Ret;
}

static rt_ssize_t hc32_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    int32_t state;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;
    rt_uint32_t u32TimeoutCnt;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct hc32_spi *spi_drv =  rt_container_of(device->bus, struct hc32_spi, spi_bus);
    CM_SPI_TypeDef *spi_instance = spi_drv->config->Instance;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_HIGH);
        else
            rt_pin_write(device->cs_pin, PIN_LOW);
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
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
        /* avoid null pointer problems */
        if (message->send_buf)
        {
            send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        }
        if (message->recv_buf)
        {
            recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        }

        if (message->send_buf && message->recv_buf)
        {
            hc32_spi_set_trans_mode(spi_instance, SPI_FULL_DUPLEX);
            if ((spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX) && (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX))
            {
                state = hc32_spi_dma_trans(spi_drv->config, send_buf, recv_buf, send_length);
            }
            else
            {
                hc32_spi_enable(spi_instance);
                state = SPI_TransReceive(spi_instance, send_buf, recv_buf, send_length, spi_drv->config->timeout);
            }
        }
        else if (message->send_buf)
        {
            hc32_spi_set_trans_mode(spi_instance, SPI_SEND_ONLY);
            if (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX)
            {
                state = hc32_spi_dma_trans(spi_drv->config, send_buf, RT_NULL, send_length);
            }
            else
            {
                hc32_spi_enable(spi_instance);
                state = SPI_Trans(spi_instance, send_buf, send_length, spi_drv->config->timeout);
            }
        }
        else
        {
            hc32_spi_set_trans_mode(spi_instance, SPI_FULL_DUPLEX);
            if ((spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_TX) && (spi_drv->spi_dma_flag & RT_DEVICE_FLAG_DMA_RX))
            {
                state = hc32_spi_dma_trans(spi_drv->config, RT_NULL, recv_buf, send_length);
            }
            else
            {
                hc32_spi_enable(spi_instance);
                state = SPI_Receive(spi_instance, recv_buf, send_length, spi_drv->config->timeout);
            }
        }
        if (state != LL_OK)
        {
            LOG_I("spi transfer error : %d", state);
            message->length = 0;
            break;
        }
        else
        {
            /* Wait for the spi transfer complete */
            if (spi_drv->spi_dma_flag & (RT_DEVICE_FLAG_DMA_TX | RT_DEVICE_FLAG_DMA_RX))
            {
                if (spi_drv->cfg->mode & RT_SPI_SLAVE)
                {
                    rt_thread_mdelay(1);
                }
                else
                {
                    u32TimeoutCnt = 0U;
                    while ((RESET == SPI_GetStatus(spi_instance, SPI_FLAG_IDLE)) &&
                            (u32TimeoutCnt < spi_drv->config->timeout))
                    {
                        rt_thread_mdelay(1);
                        u32TimeoutCnt++;
                    }
                    if (u32TimeoutCnt >= spi_drv->config->timeout)
                    {
                        LOG_I("spi transfer timeout!");
                        message->length = 0;
                        break;
                    }
                }
            }
        }
    }
    /* clear error flag */
    SPI_ClearStatus(spi_instance, SPI_FLAG_CLR_ALL);

    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS) && (device->cs_pin != PIN_NONE))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
            rt_pin_write(device->cs_pin, PIN_LOW);
        else
            rt_pin_write(device->cs_pin, PIN_HIGH);
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
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, rt_base_t cs_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);

    result = rt_spi_bus_attach_device_cspin(spi_device, device_name, bus_name, cs_pin, RT_NULL);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    return result;
}

static void hc32_spi_err_irq_handle(struct hc32_spi *spi)
{
#if defined (HC32F448) ||defined (HC32F472)
#define SPI_FLAG_OVERLOAD       SPI_FLAG_OVERRUN
#define SPI_FLAG_UNDERLOAD      SPI_FLAG_UNDERRUN
#endif
    __UNUSED uint32_t UnusedData;
    CM_SPI_TypeDef *spi_instance = spi->config->Instance;

    if (RESET != SPI_GetStatus(spi_instance, SPI_FLAG_OVERLOAD))
    {
        UnusedData = SPI_ReadData(spi_instance);
        SPI_ClearStatus(spi_instance, SPI_FLAG_OVERLOAD);
    }
    if (RESET != SPI_GetStatus(spi_instance, SPI_FLAG_UNDERLOAD))
    {
        SPI_ClearStatus(spi_instance, SPI_FLAG_UNDERLOAD);
    }
    if (RESET != SPI_GetStatus(spi_instance, SPI_FLAG_MD_FAULT))
    {
        SPI_ClearStatus(spi_instance, SPI_FLAG_MD_FAULT);
    }
    if (RESET != SPI_GetStatus(spi_instance, SPI_FLAG_PARITY_ERR))
    {
        SPI_ClearStatus(spi_instance, SPI_FLAG_PARITY_ERR);
    }
}

#if defined(BSP_USING_SPI1)
static void hc32_spi1_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_spi_err_irq_handle(&spi_bus_obj[SPI1_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}

#if defined (HC32F448) ||defined (HC32F472)
void SPI1_Handler(void)
{
    hc32_spi1_err_irq_handler();
}
#endif /* HC32F448, HC32F472 */

#endif /* BSP_USING_SPI1 */

#if defined(BSP_USING_SPI2)
static void hc32_spi2_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_spi_err_irq_handle(&spi_bus_obj[SPI2_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined (HC32F448) ||defined (HC32F472)
void SPI2_Handler(void)
{
    hc32_spi2_err_irq_handler();
}
#endif /* HC32F448, HC32F472 */

#endif /* BSP_USING_SPI2 */

#if defined(BSP_USING_SPI3)
static void hc32_spi3_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_spi_err_irq_handle(&spi_bus_obj[SPI3_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#if defined (HC32F448) ||defined (HC32F472)
void SPI3_Handler(void)
{
    hc32_spi3_err_irq_handler();
}
#endif /* HC32F448, HC32F472 */

#endif /* BSP_USING_SPI3 */

#if defined(BSP_USING_SPI4)
static void hc32_spi4_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_spi_err_irq_handle(&spi_bus_obj[SPI4_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_SPI4 */

#if defined(BSP_USING_SPI5)
static void hc32_spi5_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_spi_err_irq_handle(&spi_bus_obj[SPI5_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_SPI5 */

#if defined(BSP_USING_SPI6)
static void hc32_spi6_err_irq_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    hc32_spi_err_irq_handle(&spi_bus_obj[SPI6_INDEX]);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_USING_SPI6 */


/**
 * @brief  This function gets spi irq handle.
 * @param  None
 * @retval None
 */
static void hc32_get_spi_callback(void)
{
#ifdef BSP_USING_SPI1
    spi_config[SPI1_INDEX].err_irq.irq_callback = hc32_spi1_err_irq_handler;
#endif
#ifdef BSP_USING_SPI2
    spi_config[SPI2_INDEX].err_irq.irq_callback = hc32_spi2_err_irq_handler;
#endif
#ifdef BSP_USING_SPI3
    spi_config[SPI3_INDEX].err_irq.irq_callback = hc32_spi3_err_irq_handler;
#endif
#ifdef BSP_USING_SPI4
    spi_config[SPI4_INDEX].err_irq.irq_callback = hc32_spi4_err_irq_handler;
#endif
#ifdef BSP_USING_SPI5
    spi_config[SPI5_INDEX].err_irq.irq_callback = hc32_spi5_err_irq_handler;
#endif
#ifdef BSP_USING_SPI6
    spi_config[SPI6_INDEX].err_irq.irq_callback = hc32_spi6_err_irq_handler;
#endif
}

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
    spi_config[SPI1_INDEX].dma_rx   = &spi1_dma_rx;
#endif
#ifdef BSP_SPI1_TX_USING_DMA
    spi_bus_obj[SPI1_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi1_dma_tx = SPI1_TX_DMA_CONFIG;
    spi_config[SPI1_INDEX].dma_tx   = &spi1_dma_tx;
#endif

#ifdef BSP_SPI2_RX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi2_dma_rx = SPI2_RX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_rx   = &spi2_dma_rx;
#endif
#ifdef BSP_SPI2_TX_USING_DMA
    spi_bus_obj[SPI2_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi2_dma_tx = SPI2_TX_DMA_CONFIG;
    spi_config[SPI2_INDEX].dma_tx   = &spi2_dma_tx;
#endif

#ifdef BSP_SPI3_RX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_rx   = &spi3_dma_rx;
#endif
#ifdef BSP_SPI3_TX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_tx   = &spi3_dma_tx;
#endif

#ifdef BSP_SPI4_RX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_rx   = &spi4_dma_rx;
#endif
#ifdef BSP_SPI4_TX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_tx   = &spi4_dma_tx;
#endif

#ifdef BSP_SPI5_RX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi5_dma_rx = SPI5_RX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_rx   = &spi5_dma_rx;
#endif
#ifdef BSP_SPI5_TX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi5_dma_tx = SPI5_TX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_tx   = &spi5_dma_tx;
#endif

#ifdef BSP_SPI6_RX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config spi6_dma_rx = SPI6_RX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_rx   = &spi6_dma_rx;
#endif
#ifdef BSP_SPI6_TX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config spi6_dma_tx = SPI6_TX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_tx   = &spi6_dma_tx;
#endif
}

static int hc32_hw_spi_bus_init(void)
{
    rt_err_t result;

    hc32_get_spi_callback();
    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];
        /* register the handle */
#if defined (HC32F460) || defined (HC32F4A0)
        hc32_install_irq_handler(&spi_config[i].err_irq.irq_config, spi_config[i].err_irq.irq_callback, RT_FALSE);
#elif defined (HC32F488)
        INTC_IntSrcCmd(spi_config[i].err_irq.irq_config.int_src, DISABLE);
        NVIC_DisableIRQ(spi_config[i].err_irq.irq_config.irq_num);
#endif
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
