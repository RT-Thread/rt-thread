/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-27     zylx         first version
 */

#include "board.h"
#include "drv_qspi.h"
#include "drv_config.h"

#ifdef RT_USING_QSPI

#define DRV_DEBUG
#define LOG_TAG              "drv.qspi"
#include <drv_log.h>

#if defined(BSP_USING_QSPI)

struct stm32_hw_spi_cs
{
    uint16_t pin;
};

struct stm32_qspi_bus
{
    QSPI_HandleTypeDef QSPI_Handler;
    char *bus_name;
#ifdef BSP_QSPI_USING_DMA
    DMA_HandleTypeDef hdma_quadspi;
#endif
};

struct rt_spi_bus _qspi_bus1;
struct stm32_qspi_bus _stm32_qspi_bus;

static int stm32_qspi_init(struct rt_qspi_device *device, struct rt_qspi_configuration *qspi_cfg)
{
    int result = RT_EOK;
    unsigned int i = 1;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(qspi_cfg != RT_NULL);

    struct rt_spi_configuration *cfg = &qspi_cfg->parent;
    struct stm32_qspi_bus *qspi_bus = device->parent.bus->parent.user_data;
    rt_memset(&qspi_bus->QSPI_Handler, 0, sizeof(qspi_bus->QSPI_Handler));

    QSPI_HandleTypeDef QSPI_Handler_config = QSPI_BUS_CONFIG;
    qspi_bus->QSPI_Handler = QSPI_Handler_config;

#if defined(SOC_SERIES_STM32MP1)
    while (cfg->max_hz < HAL_RCC_GetACLKFreq() / (i + 1))
#else
    while (cfg->max_hz < HAL_RCC_GetHCLKFreq() / (i + 1))
#endif
   {
        i++;
        if (i == 255)
        {
            LOG_E("QSPI init failed, QSPI frequency(%d) is too low.", cfg->max_hz);
            return -RT_ERROR;
        }
    }
    /* 80/(1+i) */
    qspi_bus->QSPI_Handler.Init.ClockPrescaler = i;

    if (!(cfg->mode & RT_SPI_CPOL))
    {
        /* QSPI MODE0 */
        qspi_bus->QSPI_Handler.Init.ClockMode = QSPI_CLOCK_MODE_0;
    }
    else
    {
        /* QSPI MODE3 */
        qspi_bus->QSPI_Handler.Init.ClockMode = QSPI_CLOCK_MODE_3;
    }

    /* flash size */
    qspi_bus->QSPI_Handler.Init.FlashSize = POSITION_VAL(qspi_cfg->medium_size) - 1;

    result = HAL_QSPI_Init(&qspi_bus->QSPI_Handler);
    if (result  == HAL_OK)
    {
        LOG_D("qspi init success!");
    }
    else
    {
        LOG_E("qspi init failed (%d)!", result);
    }

#ifdef BSP_QSPI_USING_DMA
    /* QSPI interrupts must be enabled when using the HAL_QSPI_Receive_DMA */
    HAL_NVIC_SetPriority(QSPI_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(QSPI_IRQn);
    HAL_NVIC_SetPriority(QSPI_DMA_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(QSPI_DMA_IRQ);

    /* init QSPI DMA */
    if(QSPI_DMA_RCC  == RCC_AHB1ENR_DMA1EN)
    {
        __HAL_RCC_DMA1_CLK_ENABLE();
    }
    else
    {
        __HAL_RCC_DMA2_CLK_ENABLE();
    }

    HAL_DMA_DeInit(qspi_bus->QSPI_Handler.hdma);
    DMA_HandleTypeDef hdma_quadspi_config = QSPI_DMA_CONFIG;
    qspi_bus->hdma_quadspi = hdma_quadspi_config;

    if (HAL_DMA_Init(&qspi_bus->hdma_quadspi) != HAL_OK)
    {
        LOG_E("qspi dma init failed (%d)!", result);
    }

    __HAL_LINKDMA(&qspi_bus->QSPI_Handler, hdma, qspi_bus->hdma_quadspi);
#endif /* BSP_QSPI_USING_DMA */

    return result;
}

static void qspi_send_cmd(struct stm32_qspi_bus *qspi_bus, struct rt_qspi_message *message)
{
    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    QSPI_CommandTypeDef Cmdhandler;

    /* set QSPI cmd struct */
    Cmdhandler.Instruction = message->instruction.content;
    Cmdhandler.Address = message->address.content;
    Cmdhandler.DummyCycles = message->dummy_cycles;
    if (message->instruction.qspi_lines == 0)
    {
        Cmdhandler.InstructionMode = QSPI_INSTRUCTION_NONE;
    }
    else if (message->instruction.qspi_lines == 1)
    {
        Cmdhandler.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    }
    else if (message->instruction.qspi_lines == 2)
    {
        Cmdhandler.InstructionMode = QSPI_INSTRUCTION_2_LINES;
    }
    else if (message->instruction.qspi_lines == 4)
    {
        Cmdhandler.InstructionMode = QSPI_INSTRUCTION_4_LINES;
    }
    if (message->address.qspi_lines == 0)
    {
        Cmdhandler.AddressMode = QSPI_ADDRESS_NONE;
    }
    else if (message->address.qspi_lines == 1)
    {
        Cmdhandler.AddressMode = QSPI_ADDRESS_1_LINE;
    }
    else if (message->address.qspi_lines == 2)
    {
        Cmdhandler.AddressMode = QSPI_ADDRESS_2_LINES;
    }
    else if (message->address.qspi_lines == 4)
    {
        Cmdhandler.AddressMode = QSPI_ADDRESS_4_LINES;
    }
    if (message->address.size == 24)
    {
        Cmdhandler.AddressSize = QSPI_ADDRESS_24_BITS;
    }
    else
    {
        Cmdhandler.AddressSize = QSPI_ADDRESS_32_BITS;
    }
    if (message->qspi_data_lines == 0)
    {
        Cmdhandler.DataMode = QSPI_DATA_NONE;
    }
    else if (message->qspi_data_lines == 1)
    {
        Cmdhandler.DataMode = QSPI_DATA_1_LINE;
    }
    else if (message->qspi_data_lines == 2)
    {
        Cmdhandler.DataMode = QSPI_DATA_2_LINES;
    }
    else if (message->qspi_data_lines == 4)
    {
        Cmdhandler.DataMode = QSPI_DATA_4_LINES;
    }

    Cmdhandler.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    Cmdhandler.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    Cmdhandler.DdrMode = QSPI_DDR_MODE_DISABLE;
    Cmdhandler.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
    Cmdhandler.NbData = message->parent.length;
    HAL_QSPI_Command(&qspi_bus->QSPI_Handler, &Cmdhandler, 5000);
}

static rt_uint32_t qspixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_size_t len = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    struct stm32_qspi_bus *qspi_bus = device->bus->parent.user_data;
#ifdef BSP_QSPI_USING_SOFTCS
    struct stm32_hw_spi_cs *cs = device->parent.user_data;
#endif

    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;

#ifdef BSP_QSPI_USING_SOFTCS
    if (message->cs_take)
    {
        rt_pin_write(cs->pin, 0);
    }
#endif

    /* send data */
    if (sndb)
    {
        qspi_send_cmd(qspi_bus, qspi_message);
        if (qspi_message->parent.length != 0)
        {
            if (HAL_QSPI_Transmit(&qspi_bus->QSPI_Handler, (rt_uint8_t *)sndb, 5000) == HAL_OK)
            {
                len = length;
            }
            else
            {
                LOG_E("QSPI send data failed(%d)!", qspi_bus->QSPI_Handler.ErrorCode);
                qspi_bus->QSPI_Handler.State = HAL_QSPI_STATE_READY;
                goto __exit;
            }
        }
        else
        {
            len = 1;
        }
    }
    else if (rcvb)/* recv data */
    {
        qspi_send_cmd(qspi_bus, qspi_message);
#ifdef BSP_QSPI_USING_DMA
        if (HAL_QSPI_Receive_DMA(&qspi_bus->QSPI_Handler, rcvb) == HAL_OK)
#else
        if (HAL_QSPI_Receive(&qspi_bus->QSPI_Handler, rcvb, 5000) == HAL_OK)
#endif
        {
            len = length;
#ifdef BSP_QSPI_USING_DMA
            while (qspi_bus->QSPI_Handler.RxXferCount != 0);
#endif
        }
        else
        {
            LOG_E("QSPI recv data failed(%d)!", qspi_bus->QSPI_Handler.ErrorCode);
            qspi_bus->QSPI_Handler.State = HAL_QSPI_STATE_READY;
            goto __exit;
        }
    }

__exit:
#ifdef BSP_QSPI_USING_SOFTCS
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
#endif
    return len;
}

static rt_err_t qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct rt_qspi_device *qspi_device = (struct rt_qspi_device *)device;
    return stm32_qspi_init(qspi_device, &qspi_device->config);
}

static const struct rt_spi_ops stm32_qspi_ops =
{
    .configure = qspi_configure,
    .xfer = qspixfer,
};

static int stm32_qspi_register_bus(struct stm32_qspi_bus *qspi_bus, const char *name)
{
    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(name != RT_NULL);

    _qspi_bus1.parent.user_data = qspi_bus;
    return rt_qspi_bus_register(&_qspi_bus1, name, &stm32_qspi_ops);
}

/**
  * @brief  This function attach device to QSPI bus.
  * @param  device_name      QSPI device name
  * @param  pin              QSPI cs pin number
  * @param  data_line_width  QSPI data lines width, such as 1, 2, 4
  * @param  enter_qspi_mode  Callback function that lets FLASH enter QSPI mode
  * @param  exit_qspi_mode   Callback function that lets FLASH exit QSPI mode
  * @retval 0 : success
  *        -1 : failed
  */
rt_err_t stm32_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)())
{
    struct rt_qspi_device *qspi_device = RT_NULL;
    struct stm32_hw_spi_cs *cs_pin = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(data_line_width == 1 || data_line_width == 2 || data_line_width == 4);

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = RT_ENOMEM;
        goto __exit;
    }
    cs_pin = (struct stm32_hw_spi_cs *)rt_malloc(sizeof(struct stm32_hw_spi_cs));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = RT_ENOMEM;
        goto __exit;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;
    qspi_device->config.qspi_dl_width = data_line_width;

    cs_pin->pin = pin;
#ifdef BSP_QSPI_USING_SOFTCS
    rt_pin_mode(pin, PIN_MODE_OUTPUT);
    rt_pin_write(pin, 1);
#endif

    result = rt_spi_bus_attach_device(&qspi_device->parent, device_name, bus_name, (void *)cs_pin);

__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }

        if (cs_pin)
        {
            rt_free(cs_pin);
        }
    }

    return  result;
}

#ifdef BSP_QSPI_USING_DMA
void QSPI_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_QSPI_IRQHandler(&_stm32_qspi_bus.QSPI_Handler);

    /* leave interrupt */
    rt_interrupt_leave();
}

void QSPI_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&_stm32_qspi_bus.hdma_quadspi);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_QSPI_USING_DMA */

static int rt_hw_qspi_bus_init(void)
{
    return stm32_qspi_register_bus(&_stm32_qspi_bus, "qspi1");
}
INIT_BOARD_EXPORT(rt_hw_qspi_bus_init);

#endif /* BSP_USING_QSPI */
#endif /* RT_USING_QSPI */
