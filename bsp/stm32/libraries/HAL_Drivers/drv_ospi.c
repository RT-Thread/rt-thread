/*
 * Copyright (c) 2012-2019
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-27     fanming      first version
 */

#include "board.h"
#include "drv_ospi.h"
#include "drv_config.h"

#ifdef RT_USING_QSPI

#define DRV_DEBUG
#define LOG_TAG              "drv.ospi"
#include <drv_log.h>

#if defined(BSP_USING_OSPI)

struct stm32_hw_spi_cs
{
    uint16_t Pin;
};

struct stm32_ospi_bus
{
    OSPI_HandleTypeDef OSPI_Handler;
    char *bus_name;
#ifdef BSP_OSPI_USING_DMA
    DMA_HandleTypeDef hdma_octospi;
#endif
};

struct rt_spi_bus _ospi_bus1;
struct stm32_ospi_bus _stm32_ospi_bus;

static int stm32_ospi_init(struct rt_qspi_device *device, struct rt_qspi_configuration *qspi_cfg)
{
    int result = RT_EOK;
    unsigned int i = 1;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(qspi_cfg != RT_NULL);

    struct rt_spi_configuration *cfg = &qspi_cfg->parent;
    struct stm32_ospi_bus *ospi_bus = device->parent.bus->parent.user_data;
    rt_memset(&ospi_bus->OSPI_Handler, 0, sizeof(ospi_bus->OSPI_Handler));

    OSPI_HandleTypeDef OSPI_Handler_config = OSPI_BUS_CONFIG;
    ospi_bus->OSPI_Handler = OSPI_Handler_config;

    while (cfg->max_hz < HAL_RCC_GetHCLKFreq() / (i + 1))
    {
        i++;
        if (i == 255)
        {
            LOG_E("OSPI init failed, OSPI frequency(%d) is too low.", cfg->max_hz);
            return -RT_ERROR;
        }
    }
    /* 80/(1+i) */
    ospi_bus->OSPI_Handler.Init.ClockPrescaler = i;

    if (!(cfg->mode & RT_SPI_CPOL))
    {
        /* OSPI MODE0 */
        ospi_bus->OSPI_Handler.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
    }
    else
    {
        /* OSPI MODE3 */
        ospi_bus->OSPI_Handler.Init.ClockMode = HAL_OSPI_CLOCK_MODE_3;
    }

    /* flash size */
    ospi_bus->OSPI_Handler.Init.DeviceSize = POSITION_VAL(qspi_cfg->medium_size);

    ospi_bus->OSPI_Handler.Init.FifoThreshold         = 4;
    ospi_bus->OSPI_Handler.Init.DualQuad              = HAL_OSPI_DUALQUAD_DISABLE;
    ospi_bus->OSPI_Handler.Init.MemoryType            = HAL_OSPI_MEMTYPE_MACRONIX;
    ospi_bus->OSPI_Handler.Init.ChipSelectHighTime    = 2;
    ospi_bus->OSPI_Handler.Init.FreeRunningClock      = HAL_OSPI_FREERUNCLK_DISABLE;
    ospi_bus->OSPI_Handler.Init.WrapSize              = HAL_OSPI_WRAP_NOT_SUPPORTED;
    ospi_bus->OSPI_Handler.Init.SampleShifting        = HAL_OSPI_SAMPLE_SHIFTING_NONE;
    ospi_bus->OSPI_Handler.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE;
    ospi_bus->OSPI_Handler.Init.ChipSelectBoundary    = 0;

    result = HAL_OSPI_Init(&ospi_bus->OSPI_Handler);
    if (result  == HAL_OK)
    {
        LOG_D("ospi init success!");
    }
    else
    {
        LOG_E("ospi init failed (%d)!", result);
    }

#ifdef BSP_OSPI_USING_DMA
    /* QSPI interrupts must be enabled when using the HAL_QSPI_Receive_DMA */
    HAL_NVIC_SetPriority(OSPI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(OSPI1_IRQn);
    HAL_NVIC_SetPriority(OSPI1_DMA_IRQ, 0, 0);
    HAL_NVIC_EnableIRQ(OSPI1_DMA_IRQ);

    /* init QSPI DMA */
    if(OSPI1_DMA_RCC  == RCC_AHB1ENR_DMA1EN)
    {
        __HAL_RCC_DMA1_CLK_ENABLE();
    }
    else
    {
        __HAL_RCC_DMA2_CLK_ENABLE();
    }

    HAL_DMA_DeInit(ospi_bus->OSPI_Handler.hdma);
    DMA_HandleTypeDef hdma_octospi_config = OSPI1_DMA_CONFIG;
    ospi_bus->hdma_octospi = hdma_octospi_config;

    if (HAL_DMA_Init(&ospi_bus->hdma_octospi) != HAL_OK)
    {
        LOG_E("ospi dma init failed (%d)!", result);
    }

    __HAL_LINKDMA(&ospi_bus->OSPI_Handler, hdma, ospi_bus->hdma_octospi);
#endif /* BSP_OSPI_USING_DMA */

    return result;
}

static void ospi_send_cmd(struct stm32_ospi_bus *ospi_bus, struct rt_qspi_message *message)
{
    RT_ASSERT(ospi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    OSPI_RegularCmdTypeDef Cmdhandler;

    /* set OSPI cmd struct */
    Cmdhandler.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    Cmdhandler.FlashId = HAL_OSPI_FLASH_ID_1;
    Cmdhandler.Instruction = message->instruction.content;
    Cmdhandler.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    Cmdhandler.Address = message->address.content;
    Cmdhandler.DummyCycles = message->dummy_cycles;
    if (message->instruction.qspi_lines == 0)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_NONE;
    }
    else if (message->instruction.qspi_lines == 1)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    }
    else if (message->instruction.qspi_lines == 2)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_2_LINES;
    }
    else if (message->instruction.qspi_lines == 4)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_4_LINES;
    }
    if (message->address.qspi_lines == 0)
    {
        Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_NONE;
    }
    else if (message->address.qspi_lines == 1)
    {
        Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
    }
    else if (message->address.qspi_lines == 2)
    {
        Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_2_LINES;
    }
    else if (message->address.qspi_lines == 4)
    {
        Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_4_LINES;
    }
    if (message->address.size == 24)
    {
        Cmdhandler.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
    }
    else
    {
        Cmdhandler.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
    }
    if (message->qspi_data_lines == 0)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_NONE;
    }
    else if (message->qspi_data_lines == 1)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_1_LINE;
    }
    else if (message->qspi_data_lines == 2)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_2_LINES;
    }
    else if (message->qspi_data_lines == 4)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_4_LINES;
    }

    Cmdhandler.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;
    Cmdhandler.NbData = message->parent.length;
    Cmdhandler.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    Cmdhandler.AddressDtrMode  = HAL_OSPI_ADDRESS_DTR_DISABLE;
    Cmdhandler.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    Cmdhandler.DQSMode = HAL_OSPI_DQS_DISABLE;
    Cmdhandler.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    HAL_OSPI_Command(&ospi_bus->OSPI_Handler, &Cmdhandler, 5000);
}

static rt_uint32_t ospixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_size_t len = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    struct stm32_ospi_bus *ospi_bus = device->bus->parent.user_data;
#ifdef BSP_OSPI_USING_SOFTCS
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
        ospi_send_cmd(ospi_bus, qspi_message);
        if (qspi_message->parent.length != 0)
        {
            if (HAL_OSPI_Transmit(&ospi_bus->OSPI_Handler, (rt_uint8_t *)sndb, 5000) == HAL_OK)
            {
                len = length;
            }
            else
            {
                LOG_E("OSPI send data failed(%d)!", ospi_bus->OSPI_Handler.ErrorCode);
                ospi_bus->OSPI_Handler.State = HAL_OSPI_STATE_READY;
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
        ospi_send_cmd(ospi_bus, qspi_message);
#ifdef BSP_QSPI_USING_DMA
        if (HAL_OSPI_Receive_DMA(&ospi_bus->OSPI_Handler, rcvb) == HAL_OK)
#else
        if (HAL_OSPI_Receive(&ospi_bus->OSPI_Handler, rcvb, 5000) == HAL_OK)
#endif
        {
            len = length;
#ifdef BSP_OSPI_USING_DMA
            while (ospi_bus->OSPI_Handler.XferCount != 0);
#endif
        }
        else
        {
            LOG_E("OSPI recv data failed(%d)!", ospi_bus->OSPI_Handler.ErrorCode);
            ospi_bus->OSPI_Handler.State = HAL_OSPI_STATE_READY;
            goto __exit;
        }
    }

__exit:
#ifdef BSP_OSPI_USING_SOFTCS
    if (message->cs_release)
    {
        rt_pin_write(cs->pin, 1);
    }
#endif
    return len;
}

static rt_err_t ospi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct rt_qspi_device *ospi_device = (struct rt_qspi_device *)device;
    return stm32_ospi_init(ospi_device, &ospi_device->config);
}

static const struct rt_spi_ops stm32_ospi_ops =
{
    .configure = ospi_configure,
    .xfer = ospixfer,
};

static int stm32_ospi_register_bus(struct stm32_ospi_bus *ospi_bus, const char *name)
{
    RT_ASSERT(ospi_bus != RT_NULL);
    RT_ASSERT(name != RT_NULL);

    _ospi_bus1.parent.user_data = ospi_bus;
    return rt_qspi_bus_register(&_ospi_bus1, name, &stm32_ospi_ops);
}

/**
  * @brief  This function attach device to QSPI bus.
  * @param  device_name      OSPI device name
  * @param  pin              OSPI cs pin number
  * @param  data_line_width  OSPI data lines width, such as 1, 2, 4
  * @param  enter_qspi_mode  Callback function that lets FLASH enter QSPI mode
  * @param  exit_qspi_mode   Callback function that lets FLASH exit QSPI mode
  * @retval 0 : success
  *        -1 : failed
  */
rt_err_t stm32_ospi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint32_t pin, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)())
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
        LOG_E("no memory, ospi bus attach device failed!");
        result = RT_ENOMEM;
        goto __exit;
    }
    cs_pin = (struct stm32_hw_spi_cs *)rt_malloc(sizeof(struct stm32_hw_spi_cs));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, ospi bus attach device failed!");
        result = RT_ENOMEM;
        goto __exit;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;
    qspi_device->config.qspi_dl_width = data_line_width;

    cs_pin->Pin = pin;
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

#ifdef BSP_OSPI_USING_DMA
void OSPI_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_OSPI_IRQHandler(&_stm32_ospi_bus.OSPI_Handler);

    /* leave interrupt */
    rt_interrupt_leave();
}

void OSPI_DMA_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&_stm32_ospi_bus.hdma_octospi);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* BSP_OSPI_USING_DMA */

static int rt_hw_ospi_bus_init(void)
{
    return stm32_ospi_register_bus(&_stm32_ospi_bus, "ospi1");
}
INIT_BOARD_EXPORT(rt_hw_ospi_bus_init);

#endif /* BSP_USING_OSPI */
#endif /* RT_USING_QSPI */
