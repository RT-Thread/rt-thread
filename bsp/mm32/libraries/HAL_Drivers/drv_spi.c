/**
 * @file drv_spi.c
 * @author 100ask development team
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022 Chongqing 100ASK Technology Co., LTD
 * 
 */

#include <rtthread.h>
#include <rtdevice.h>

#define RT_USING_SPI
#define BSP_USING_SPI1
#define BSP_SPI1_TX_USING_DMA
#define BSP_SPI1_RX_USING_DMA

#ifdef RT_USING_SPI

#if defined(BSP_USING_SPI1) || defined(BSP_USING_SPI2) || defined(BSP_USING_SPI3)

#include "drv_spi.h"
#include "drv_config.h"
#include <string.h>

//#define DRV_DEBUG
#define LOG_TAG              "drv.spi"
#include <drv_log.h>

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
};

static struct mm32_spi_config spi_config[] =
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
};

static struct mm32_spi spi_bus_obj[sizeof(spi_config) / sizeof(spi_config[0])] = {0};

static rt_err_t mm32_spi_init(struct mm32_spi *spi_drv, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(spi_drv != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    SPI_Master_Init_Type *spi_handle = &spi_drv->handle;

    spi_handle->ClockFreqHz = Drv_Get_APB1_Clock();

    if (cfg->data_width == 8)
    {
        spi_handle->DataWidth = SPI_DataWidth_8b;
    }
    else if (cfg->data_width == 16)
    {
        spi_handle->DataWidth = SPI_DataWidth_8b;
    }
    else
    {
        return RT_EIO;
    }

    if (cfg->mode & RT_SPI_CPOL)
    {
        spi_handle->PolarityPhase = SPI_PolarityPhase_Alt0;
    }
    else
    {
        spi_handle->PolarityPhase = SPI_PolarityPhase_Alt1;
    }

    if (cfg->mode & RT_SPI_NO_CS)
    {
        spi_handle->AutoCS = RT_FALSE;
    }
    else
    {
        spi_handle->AutoCS = RT_TRUE;
    }

    uint32_t SPI_APB_CLOCK;
    SPI_APB_CLOCK = Drv_Get_APB1_Clock();

    if (cfg->max_hz >= SPI_APB_CLOCK / 2)
    {
        spi_handle->BaudRate= (SPI_APB_CLOCK>>1);
    }
    else
    {
        spi_handle->BaudRate = cfg->max_hz;
    }

    LOG_D("sys freq: %d, pclk2 freq: %d, SPI limiting freq: %d, BaudRatePrescaler: %d",
          HAL_RCC_GetSysClockFreq(),
          SPI_APB_CLOCK,
          cfg->max_hz,
          spi_handle->BaudRate);

    if (cfg->mode & RT_SPI_MSB)
    {
        spi_handle->LSB = RT_FALSE;
    }
    else
    {
        spi_handle->LSB = RT_TRUE;
    }

    spi_handle->XferMode = SPI_XferMode_TxRx;
    extern void SPI_MspInit(SPI_Type *mspi, , uint8_t autocs);
    SPI_MspInit(spi_drv->config->Instance, cfg->mode & RT_SPI_NO_CS);
    SPI_InitMaster(spi_drv->config->Instance, spi_handle);

    /* DMA configuration */
    extern int DMA_MspInit(DMA_Channel_Init_Type handle, \
                 DMA_Type *dma, \
                 uint32_t req, \
                 IRQn_Type irqn, \
                 rt_uint32_t rcc, \
                 uint8_t *buf, \
                 uint16_t buf_len);
    if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
    {
        int ret = DMA_MspInit(spi_drv->dma.handle_rx, \
                    spi_drv->config->dma_rx->Instance, \
                    spi_drv->config->dma_rx->dma_req, \
                    spi_drv->config->dma_rx->dma_irq, \
                    spi_drv->config->dma_rx->dma_rcc, \
                    spi_drv->dma.rx_buf_len, \
                    spi_drv->dma.rx_buf);
        if(ret == -1)   
        {
            LOG_D("%s init DMA failed.\r\n", spi_drv->config->bus_name);
            return RT_ERROR;
        }
        SPI_EnableDMA(spi_drv->config->dma_rx->Instance, RT_TRUE);
    }

    if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
    {
        int ret = DMA_MspInit(spi_drv->dma.handle_tx, \
                    spi_drv->config->dma_tx->Instance, \
                    spi_drv->config->dma_tx->dma_req, \
                    spi_drv->config->dma_tx->dma_irq, \
                    spi_drv->config->dma_tx->dma_rcc, 
                    spi_drv->dma.tx_buf_len, \
                    spi_drv->dma.tx_buf);
        if(ret == -1)   
        {
            LOG_D("%s init DMA failed.\r\n", spi_drv->config->bus_name);
            return RT_ERROR;
        }

        SPI_EnableDMA(spi_drv->config->dma_tx->Instance, RT_TRUE);
    }

    SPI_Enable(spi_drv->config->Instance, RT_TRUE);

    LOG_D("%s init done", spi_drv->config->bus_name);
    return RT_EOK;
}

static rt_uint32_t spixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    HAL_StatusTypeDef state;
    rt_size_t message_length, already_send_length;
    rt_uint16_t send_length;
    rt_uint8_t *recv_buf;
    const rt_uint8_t *send_buf;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->bus->parent.user_data != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct mm32_spi *spi_drv =  rt_container_of(device->bus, struct mm32_spi, spi_bus);
    SPI_Master_Init_Type *spi_handle = &spi_drv->handle;
    struct mm32_hw_spi_cs *cs = device->parent.user_data;

    if (message->cs_take)
    {
        GPIO_WriteBit(cs->GPIOx, cs->GPIO_Pin, 0);
    }

    LOG_D("%s transfer prepare and start", spi_drv->config->bus_name);
    LOG_D("%s sendbuf: %X, recvbuf: %X, length: %d",
          spi_drv->config->bus_name,
          (uint32_t)message->send_buf,
          (uint32_t)message->recv_buf, message->length);

    message_length = message->length;
    recv_buf = message->recv_buf;
    send_buf = message->send_buf;
    while (message_length)
    {
        /* the HAL library use uint16 to save the data length */
        if (message_length > 65535)
        {
            send_length = 65535;
            message_length = message_length - 65535;
        }
        else
        {
            send_length = message_length;
            message_length = 0;
        }

        /* calculate the start address */
        already_send_length = message->length - send_length - message_length;
        send_buf = (rt_uint8_t *)message->send_buf + already_send_length;
        recv_buf = (rt_uint8_t *)message->recv_buf + already_send_length;
        
        /* start once data exchange in DMA mode */
        if (message->send_buf && message->recv_buf)
        {
            if ((spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG) && (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG))
            {
                state = HAL_SPI_TransmitReceive_DMA(spi_handle, (uint8_t *)send_buf, (uint8_t *)recv_buf, send_length);
            }
            else
            {
                state = HAL_SPI_TransmitReceive(spi_handle, (uint8_t *)send_buf, (uint8_t *)recv_buf, send_length, 1000);
            }
        }
        else if (message->send_buf)
        {
            if (spi_drv->spi_dma_flag & SPI_USING_TX_DMA_FLAG)
            {
                state = HAL_SPI_Transmit_DMA(spi_handle, (uint8_t *)send_buf, send_length);
            }
            else
            {
                state = HAL_SPI_Transmit(spi_handle, (uint8_t *)send_buf, send_length, 1000);
            }
        }
        else
        {
            memset((uint8_t *)recv_buf, 0xff, send_length);
            if (spi_drv->spi_dma_flag & SPI_USING_RX_DMA_FLAG)
            {
                state = HAL_SPI_Receive_DMA(spi_handle, (uint8_t *)recv_buf, send_length);
            }
            else
            {
                state = HAL_SPI_Receive(spi_handle, (uint8_t *)recv_buf, send_length, 1000);
            }
        }

        if (state != HAL_OK)
        {
            LOG_I("spi transfer error : %d", state);
            message->length = 0;
            spi_handle->State = HAL_SPI_STATE_READY;
        }
        else
        {
            LOG_D("%s transfer done", spi_drv->config->bus_name);
        }

        /* For simplicity reasons, this example is just waiting till the end of the
           transfer, but application may perform other tasks while transfer operation
           is ongoing. */
        while (HAL_SPI_GetState(spi_handle) != HAL_SPI_STATE_READY);
    }

    if (message->cs_release)
    {
        HAL_GPIO_WritePin(cs->GPIOx, cs->GPIO_Pin, GPIO_PIN_SET);
    }

    return message->length;
}

static rt_err_t spi_configure(struct rt_spi_device *device,
                              struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct mm32_spi *spi_drv =  rt_container_of(device->bus, struct mm32_spi, spi_bus);
    spi_drv->cfg = configuration;

    return mm32_spi_init(spi_drv, configuration);
}

static const struct rt_spi_ops stm_spi_ops =
{
    .configure = spi_configure,
    .xfer = spixfer,
};

static int rt_hw_spi_bus_init(void)
{
    rt_err_t result;
    for (int i = 0; i < sizeof(spi_config) / sizeof(spi_config[0]); i++)
    {
        spi_bus_obj[i].config = &spi_config[i];
        spi_bus_obj[i].spi_bus.parent.user_data = &spi_config[i];
        spi_bus_obj[i].handle.Instance = spi_config[i].Instance;

        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_RX_DMA_FLAG)
        {
            /* Configure the DMA handler for Transmission process */
            spi_bus_obj[i].dma.handle_rx.Instance = spi_config[i].dma_rx->Instance;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            spi_bus_obj[i].dma.handle_rx.Init.Channel = spi_config[i].dma_rx->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
            spi_bus_obj[i].dma.handle_rx.Init.Request = spi_config[i].dma_rx->request;
#endif
            spi_bus_obj[i].dma.handle_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
            spi_bus_obj[i].dma.handle_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
            spi_bus_obj[i].dma.handle_rx.Init.MemInc              = DMA_MINC_ENABLE;
            spi_bus_obj[i].dma.handle_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            spi_bus_obj[i].dma.handle_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
            spi_bus_obj[i].dma.handle_rx.Init.Mode                = DMA_NORMAL;
            spi_bus_obj[i].dma.handle_rx.Init.Priority            = DMA_PRIORITY_HIGH;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            spi_bus_obj[i].dma.handle_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
            spi_bus_obj[i].dma.handle_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
            spi_bus_obj[i].dma.handle_rx.Init.MemBurst            = DMA_MBURST_INC4;
            spi_bus_obj[i].dma.handle_rx.Init.PeriphBurst         = DMA_PBURST_INC4;
#endif

            {
                rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0)
                /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
                SET_BIT(RCC->AHBENR, spi_config[i].dma_rx->dma_rcc);
                tmpreg = READ_BIT(RCC->AHBENR, spi_config[i].dma_rx->dma_rcc);
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4)
                SET_BIT(RCC->AHB1ENR, spi_config[i].dma_rx->dma_rcc);
                /* Delay after an RCC peripheral clock enabling */
                tmpreg = READ_BIT(RCC->AHB1ENR, spi_config[i].dma_rx->dma_rcc);
#endif
                UNUSED(tmpreg); /* To avoid compiler warnings */
            }
        }

        if (spi_bus_obj[i].spi_dma_flag & SPI_USING_TX_DMA_FLAG)
        {
            /* Configure the DMA handler for Transmission process */
            spi_bus_obj[i].dma.handle_tx.Instance = spi_config[i].dma_tx->Instance;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            spi_bus_obj[i].dma.handle_tx.Init.Channel = spi_config[i].dma_tx->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0)
            spi_bus_obj[i].dma.handle_tx.Init.Request = spi_config[i].dma_tx->request;
#endif
            spi_bus_obj[i].dma.handle_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
            spi_bus_obj[i].dma.handle_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
            spi_bus_obj[i].dma.handle_tx.Init.MemInc              = DMA_MINC_ENABLE;
            spi_bus_obj[i].dma.handle_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            spi_bus_obj[i].dma.handle_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
            spi_bus_obj[i].dma.handle_tx.Init.Mode                = DMA_NORMAL;
            spi_bus_obj[i].dma.handle_tx.Init.Priority            = DMA_PRIORITY_LOW;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            spi_bus_obj[i].dma.handle_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
            spi_bus_obj[i].dma.handle_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
            spi_bus_obj[i].dma.handle_tx.Init.MemBurst            = DMA_MBURST_INC4;
            spi_bus_obj[i].dma.handle_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
#endif

            {
                rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0)
                /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
                SET_BIT(RCC->AHBENR, spi_config[i].dma_tx->dma_rcc);
                tmpreg = READ_BIT(RCC->AHBENR, spi_config[i].dma_tx->dma_rcc);
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4)
                SET_BIT(RCC->AHB1ENR, spi_config[i].dma_tx->dma_rcc);
                /* Delay after an RCC peripheral clock enabling */
                tmpreg = READ_BIT(RCC->AHB1ENR, spi_config[i].dma_tx->dma_rcc);
#endif
                UNUSED(tmpreg); /* To avoid compiler warnings */
            }
        }

        result = rt_spi_bus_register(&spi_bus_obj[i].spi_bus, spi_config[i].bus_name, &stm_spi_ops);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", spi_config[i].bus_name);
    }

    return result;
}

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_TypeDef *cs_gpiox, uint16_t cs_gpio_pin)
{
    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    rt_err_t result;
    struct rt_spi_device *spi_device;
    struct mm32_hw_spi_cs *cs_pin;

    /* initialize the cs pin && select the slave*/
    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin = cs_gpio_pin;
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(cs_gpiox, &GPIO_Initure);
    HAL_GPIO_WritePin(cs_gpiox, cs_gpio_pin, GPIO_PIN_SET);

    /* attach the device to spi bus*/
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
    cs_pin = (struct mm32_hw_spi_cs *)rt_malloc(sizeof(struct mm32_hw_spi_cs));
    RT_ASSERT(cs_pin != RT_NULL);
    cs_pin->GPIOx = cs_gpiox;
    cs_pin->GPIO_Pin = cs_gpio_pin;
    result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)cs_pin);

    if (result != RT_EOK)
    {
        LOG_E("%s attach to %s faild, %d\n", device_name, bus_name, result);
    }

    RT_ASSERT(result == RT_EOK);

    LOG_D("%s attach to %s done", device_name, bus_name);

    return result;
}

#if defined(BSP_SPI1_TX_USING_DMA) || defined(BSP_SPI1_RX_USING_DMA)
void SPI1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None
  */
void SPI1_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI1_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPI1_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI1_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI1) && defined(BSP_SPI_USING_DMA) */

#if defined(BSP_SPI2_TX_USING_DMA) || defined(BSP_SPI2_RX_USING_DMA)
void SPI2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None
  */
void SPI2_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI2_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPI2_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI2_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI2) && defined(BSP_SPI_USING_DMA) */

#if defined(BSP_SPI3_TX_USING_DMA) || defined(BSP_SPI3_RX_USING_DMA)
void SPI3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI3_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI3) && defined(BSP_SPI3_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI3_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI3) && defined(BSP_SPI_USING_DMA) */

#if defined(BSP_SPI4_TX_USING_DMA) || defined(BSP_SPI4_RX_USING_DMA)
void SPI4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI4_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None
  */
void SPI4_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI4_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI4) && defined(BSP_SPI4_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPI4_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI4_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI4) && defined(BSP_SPI_USING_DMA) */

#if defined(BSP_SPI5_TX_USING_DMA) || defined(BSP_SPI5_RX_USING_DMA)
void SPI5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_SPI_IRQHandler(&spi_bus_obj[SPI5_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None
  */
void SPI5_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI5_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI5) && defined(BSP_SPI5_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPI5_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI5_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI5) && defined(BSP_SPI_USING_DMA) */

#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_RX_USING_DMA)
/**
  * @brief  This function handles DMA Rx interrupt request.
  * @param  None
  * @retval None
  */
void SPI6_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI6_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_SPI6) && defined(BSP_SPI6_TX_USING_DMA)
/**
  * @brief  This function handles DMA Tx interrupt request.
  * @param  None
  * @retval None
  */
void SPI6_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&spi_bus_obj[SPI6_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_SPI6) && defined(BSP_SPI_USING_DMA) */

static void mm32_get_dma_info(void)
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

#ifdef BSP_SPI3_RX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi3_dma_rx = SPI3_RX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_rx = &spi3_dma_rx;
#endif
#ifdef BSP_SPI3_TX_USING_DMA
    spi_bus_obj[SPI3_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi3_dma_tx = SPI3_TX_DMA_CONFIG;
    spi_config[SPI3_INDEX].dma_tx = &spi3_dma_tx;
#endif

#ifdef BSP_SPI4_RX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi4_dma_rx = SPI4_RX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_rx = &spi4_dma_rx;
#endif
#ifdef BSP_SPI4_TX_USING_DMA
    spi_bus_obj[SPI4_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi4_dma_tx = SPI4_TX_DMA_CONFIG;
    spi_config[SPI4_INDEX].dma_tx = &spi4_dma_tx;
#endif

#ifdef BSP_SPI5_RX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi5_dma_rx = SPI5_RX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_rx = &spi5_dma_rx;
#endif
#ifdef BSP_SPI5_TX_USING_DMA
    spi_bus_obj[SPI5_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi5_dma_tx = SPI5_TX_DMA_CONFIG;
    spi_config[SPI5_INDEX].dma_tx = &spi5_dma_tx;
#endif

#ifdef BSP_SPI6_RX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= SPI_USING_RX_DMA_FLAG;
    static struct dma_config spi6_dma_rx = SPI6_RX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_rx = &spi6_dma_rx;
#endif
#ifdef BSP_SPI6_TX_USING_DMA
    spi_bus_obj[SPI6_INDEX].spi_dma_flag |= SPI_USING_TX_DMA_FLAG;
    static struct dma_config spi6_dma_tx = SPI6_TX_DMA_CONFIG;
    spi_config[SPI6_INDEX].dma_tx = &spi6_dma_tx;
#endif
}

#if defined(SOC_SERIES_STM32F0)
void SPI1_DMA_RX_TX_IRQHandler(void) 
{
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_TX_USING_DMA)
    SPI1_DMA_TX_IRQHandler();
#endif
    
#if defined(BSP_USING_SPI1) && defined(BSP_SPI1_RX_USING_DMA)
    SPI1_DMA_RX_IRQHandler();
#endif
}

void SPI2_DMA_RX_TX_IRQHandler(void) 
{
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_TX_USING_DMA)
    SPI2_DMA_TX_IRQHandler();
#endif
    
#if defined(BSP_USING_SPI2) && defined(BSP_SPI2_RX_USING_DMA)
    SPI2_DMA_RX_IRQHandler();
#endif
}
#endif  /* SOC_SERIES_STM32F0 */

int rt_hw_spi_init(void)
{
    mm32_get_dma_info();
    return rt_hw_spi_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_spi_init);


#endif /* BSP_USING_SPI1 || BSP_USING_SPI2 || BSP_USING_SPI3 */

#endif /* RT_USING_SPI */

