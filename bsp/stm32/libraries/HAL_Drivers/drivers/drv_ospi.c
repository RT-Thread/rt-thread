/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-08-17     CliffLL        first version
 */

#include "board.h"
#include "drv_ospi.h"
#include "drv_dma.h"
#include "drv_config.h"

#ifdef RT_USING_OSPI

#define DRV_DEBUG
#define LOG_TAG "drv.ospi"
#include <drv_log.h>

#if defined(BSP_USING_OSPI)

struct stm32_ospi_bus
{
    OSPI_HandleTypeDef OSPI_Handler;
    char *bus_name;
};

struct rt_spi_bus _ospi_bus1;
struct stm32_ospi_bus _stm32_ospi_bus;

static int stm32_ospi_init(struct rt_ospi_device *device, struct rt_ospi_configuration *ospi_cfg)
{
    int result = RT_EOK;
    unsigned int i = 1;

    OSPIM_CfgTypeDef OSPIM_Cfg_Struct = { 0 };

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(ospi_cfg != RT_NULL);

    struct rt_spi_configuration *cfg = &ospi_cfg->parent;
    struct stm32_ospi_bus *ospi_bus = device->parent.bus->parent.user_data;
    rt_memset(&ospi_bus->OSPI_Handler, 0, sizeof(ospi_bus->OSPI_Handler));

    OSPI_HandleTypeDef OSPI_Handler_config = OSPI_BUS_CONFIG;
    ospi_bus->OSPI_Handler = OSPI_Handler_config;

    while (cfg->max_hz < HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_OSPI) / (i + 1))
    {
        i++;
        if (i == 255)
        {
            LOG_E("OSPI init failed, OSPI frequency(%d) is too low.", cfg->max_hz);
            return -RT_ERROR;
        }
    }

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
    ospi_bus->OSPI_Handler.Init.DeviceSize = POSITION_VAL(ospi_cfg->medium_size);

    /* dqs mode */
    if (ospi_cfg->dtr_mode)
    {
        /* OSPI DTR MODE */
        ospi_bus->OSPI_Handler.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_ENABLE;
    }
    else
    {
        /* OSPI STR MODE */
        ospi_bus->OSPI_Handler.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
    }

    result = HAL_OSPI_Init(&ospi_bus->OSPI_Handler);
    if (result == HAL_OK)
    {
        LOG_D("ospi init success!");
    }
    else
    {
        LOG_E("ospi init failed (%d)!", result);
        return -RT_EIO;
    }

    OSPIM_Cfg_Struct.ClkPort = OSPI_CLK_PORT;
    OSPIM_Cfg_Struct.DQSPort = OSPI_DQS_PORT;
    OSPIM_Cfg_Struct.NCSPort = OSPI_NCS_PORT;
    OSPIM_Cfg_Struct.IOLowPort = OSPI_IO_LOW_PORT;
    OSPIM_Cfg_Struct.IOHighPort = OSPI_IO_HIGH_PORT;

    if (HAL_OSPIM_Config(&ospi_bus->OSPI_Handler, &OSPIM_Cfg_Struct, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        LOG_E("ospim init failed !");
        return -RT_EIO;
    }

    return result;
}

static rt_err_t stm32_ospi_recover(struct rt_spi_device *device)
{
    HAL_StatusTypeDef status;
    struct rt_ospi_device *ospi_device;
    struct stm32_ospi_bus *ospi_bus;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    ospi_device = (struct rt_ospi_device *)device;
    ospi_bus = device->bus->parent.user_data;

    RT_ASSERT(ospi_bus != RT_NULL);

    /*
     * Abort may fail if the previous command did not enter a transferable
     * state, but DeInit is still attempted for controller recovery.
     */
    status = HAL_OSPI_Abort(&ospi_bus->OSPI_Handler);
    if (status != HAL_OK)
    {
        LOG_W("HAL_OSPI_Abort failed, status=%d, error=0x%08X", (int)status, (unsigned int)ospi_bus->OSPI_Handler.ErrorCode);
    }

    status = HAL_OSPI_DeInit(&ospi_bus->OSPI_Handler);
    if (status != HAL_OK)
    {
        LOG_E("HAL_OSPI_DeInit failed, status=%d, error=0x%08X", (int)status, (unsigned int)ospi_bus->OSPI_Handler.ErrorCode);
        return -RT_EIO;
    }

    /*
     * Rebuild OSPI Handle and configure OSPIM routing using the current
     * OSPI device configuration.
     */
    return stm32_ospi_init(ospi_device, &ospi_device->config);
}

static rt_err_t ospi_send_cmd(struct stm32_ospi_bus *ospi_bus, struct rt_ospi_message *message)
{
    RT_ASSERT(ospi_bus != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    OSPI_RegularCmdTypeDef Cmdhandler = { 0 };
    HAL_StatusTypeDef status;

    /* set OSPI cmd struct */
    Cmdhandler.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    Cmdhandler.FlashId = HAL_OSPI_FLASH_ID_1;
    Cmdhandler.Instruction = message->instruction.content;
    Cmdhandler.Address = message->address.content;
    Cmdhandler.DummyCycles = message->dummy_cycles;
    if (message->instruction.ospi_lines == 0)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_NONE;
    }
    else if (message->instruction.ospi_lines == 1)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_1_LINE;
    }
    else if (message->instruction.ospi_lines == 2)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_2_LINES;
    }
    else if (message->instruction.ospi_lines == 4)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_4_LINES;
    }
    else if (message->instruction.ospi_lines == 8)
    {
        Cmdhandler.InstructionMode = HAL_OSPI_INSTRUCTION_8_LINES;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (message->instruction.dtrmode == 0)
    {
        Cmdhandler.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    }
    else if (message->instruction.dtrmode == 1)
    {
        Cmdhandler.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_ENABLE;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (message->instruction.size == 8)
    {
        Cmdhandler.InstructionSize = HAL_OSPI_INSTRUCTION_8_BITS;
    }
    else if (message->instruction.size == 16)
    {
        Cmdhandler.InstructionSize = HAL_OSPI_INSTRUCTION_16_BITS;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (message->address.ospi_lines == 0)
    {
        Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_NONE;
    }
    else
    {
        if (message->address.ospi_lines == 1)
        {
            Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_1_LINE;
        }
        else if (message->address.ospi_lines == 2)
        {
            Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_2_LINES;
        }
        else if (message->address.ospi_lines == 4)
        {
            Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_4_LINES;
        }
        else if (message->address.ospi_lines == 8)
        {
            Cmdhandler.AddressMode = HAL_OSPI_ADDRESS_8_LINES;
        }
        else
        {
            return -RT_EINVAL;
        }

        if (message->address.dtrmode == 0)
        {
            Cmdhandler.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_DISABLE;
        }
        else if (message->address.dtrmode == 1)
        {
            Cmdhandler.AddressDtrMode = HAL_OSPI_ADDRESS_DTR_ENABLE;
        }
        else
        {
            return -RT_EINVAL;
        }

        if (message->address.size == 24)
        {
            Cmdhandler.AddressSize = HAL_OSPI_ADDRESS_24_BITS;
        }
        else if (message->address.size == 32)
        {
            Cmdhandler.AddressSize = HAL_OSPI_ADDRESS_32_BITS;
        }
        else
        {
            return -RT_EINVAL;
        }
    }

    if (message->ospi_data_lines == 0)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_NONE;
    }
    else if (message->ospi_data_lines == 1)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_1_LINE;
    }
    else if (message->ospi_data_lines == 2)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_2_LINES;
    }
    else if (message->ospi_data_lines == 4)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_4_LINES;
    }
    else if (message->ospi_data_lines == 8)
    {
        Cmdhandler.DataMode = HAL_OSPI_DATA_8_LINES;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (message->ospi_data_dtrmode == 0)
    {
        Cmdhandler.DataDtrMode = HAL_OSPI_DATA_DTR_DISABLE;
    }
    else if (message->ospi_data_dtrmode == 1)
    {
        Cmdhandler.DataDtrMode = HAL_OSPI_DATA_DTR_ENABLE;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (message->dqs_mode == 0)
    {
        Cmdhandler.DQSMode = HAL_OSPI_DQS_DISABLE;
    }
    else if (message->dqs_mode == 1)
    {
        Cmdhandler.DQSMode = HAL_OSPI_DQS_ENABLE;
    }
    else
    {
        return -RT_EINVAL;
    }

    Cmdhandler.SIOOMode = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Alternate bytes are not required by currently supported */
    Cmdhandler.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    Cmdhandler.NbData = message->parent.length;

    status = HAL_OSPI_Command(&ospi_bus->OSPI_Handler, &Cmdhandler, 5000);
    if (status != HAL_OK)
    {
        LOG_E("HAL_OSPI_Command failed, status=%d, error=0x%08X", (int)status, (unsigned int)ospi_bus->OSPI_Handler.ErrorCode);
        if (HAL_OSPI_Abort(&ospi_bus->OSPI_Handler) != HAL_OK)
        {
            LOG_E("HAL_OSPI_Abort failed, error=0x%08X", (unsigned int)ospi_bus->OSPI_Handler.ErrorCode);
        }
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_ssize_t ospixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    rt_ssize_t result = 0;
    rt_err_t cmd_result;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);

    struct rt_ospi_message *ospi_message = (struct rt_ospi_message *)message;
    struct stm32_ospi_bus *ospi_bus = device->bus->parent.user_data;

    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;

    /* Length < 0 is invalid */
    if (length < 0)
    {
        return -RT_EINVAL;
    }

    /* Length > 0 but neither TX or RX buffer exists is invalid */
    if ((length > 0) && (sndb == RT_NULL) && (rcvb == RT_NULL))
    {
        return -RT_EINVAL;
    }

    /* TX and RX buffer exists at the same time is invalid */
    if ((sndb != RT_NULL) && (rcvb != RT_NULL))
    {
        return -RT_EINVAL;
    }

    /* Execute HAL_OSPI_Command */
    cmd_result = ospi_send_cmd(ospi_bus, ospi_message);
    if (cmd_result != RT_EOK)
    {
        if (stm32_ospi_recover(device) != RT_EOK)
        {
            LOG_W("OSPI controller recovery failed after command error.");
        }
        return cmd_result;
    }

    /* send only header */
    if (length == 0)
    {
        /* rt_ospi_transfer_message() treats zero as failure, return a positive value for a successful command-only transfer */
        return 1;
    }
    else if (sndb)/* send data */
    {
        if (HAL_OSPI_Transmit(&ospi_bus->OSPI_Handler, (rt_uint8_t *)sndb, 5000) == HAL_OK)
        {
            return length;
        }
        else
        {
            LOG_E("OSPI send data failed(%d)!", ospi_bus->OSPI_Handler.ErrorCode);
            if (stm32_ospi_recover(device) != RT_EOK)
            {
                LOG_W("OSPI controller recovery failed after transmit error.");
            }
            return -RT_EIO;
        }
    }
    else if (rcvb)/* recv data */
    {
        if (HAL_OSPI_Receive(&ospi_bus->OSPI_Handler, rcvb, 5000) == HAL_OK)
        {
            return length;
        }
        else
        {
            LOG_E("OSPI recv data failed(%d)!", ospi_bus->OSPI_Handler.ErrorCode);
            if (stm32_ospi_recover(device) != RT_EOK)
            {
                LOG_W("OSPI controller recovery failed after transmit error.");
            }
            return -RT_EIO;
        }
    }

    return -RT_EINVAL;
}

static rt_err_t ospi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct rt_ospi_device *ospi_device = (struct rt_ospi_device *)device;
    return stm32_ospi_init(ospi_device, &ospi_device->config);
}

static const struct rt_spi_ops stm32_ospi_ops = {
    .configure = ospi_configure,
    .xfer = ospixfer,
};

static int stm32_ospi_register_bus(struct stm32_ospi_bus *ospi_bus, const char *name)
{
    RT_ASSERT(ospi_bus != RT_NULL);
    RT_ASSERT(name != RT_NULL);

    _ospi_bus1.parent.user_data = ospi_bus;
    return rt_ospi_bus_register(&_ospi_bus1, name, &stm32_ospi_ops);
}

/**
  * @brief  This function attach device to OSPI bus.
  * @param  device_name      OSPI device name
  * @param  enter_ospi_str_mode  Callback function that lets FLASH enter STR-OPI mode
  * @param  enter_ospi_dtr_mode  Callback function that lets FLASH enter DTR-OPI mode
  * @param  exit_ospi_mode       Callback function that lets FLASH exit OSPI mode
  * @retval 0 : success
  *        -1 : failed
  */
rt_err_t rt_hw_ospi_device_attach(const char *bus_name, const char *device_name, rt_err_t (*enter_ospi_str_mode)(struct rt_ospi_device *device), rt_err_t (*enter_ospi_dtr_mode)(struct rt_ospi_device *device), rt_err_t (*exit_ospi_mode)(struct rt_ospi_device *device))
{
    struct rt_ospi_device *ospi_device = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    ospi_device = (struct rt_ospi_device *)rt_malloc(sizeof(struct rt_ospi_device));
    if (ospi_device == RT_NULL)
    {
        LOG_E("no memory, ospi bus attach device failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }
    rt_memset(ospi_device, 0, sizeof(struct rt_ospi_device));
    ospi_device->config.dtr_mode = 0;
    ospi_device->ospi_mode = RT_OSPI_MODE_OFF;

    ospi_device->enter_ospi_str_mode = enter_ospi_str_mode;
    ospi_device->enter_ospi_dtr_mode = enter_ospi_dtr_mode;
    ospi_device->exit_ospi_mode = exit_ospi_mode;

    result = rt_spi_bus_attach_device_cspin(&ospi_device->parent, device_name, bus_name, PIN_NONE, RT_NULL);

__exit:
    if (result != RT_EOK)
    {
        if (ospi_device)
        {
            rt_free(ospi_device);
        }
    }

    return result;
}

static int rt_hw_ospi_bus_init(void)
{
    return stm32_ospi_register_bus(&_stm32_ospi_bus, "ospi1");
}
INIT_BOARD_EXPORT(rt_hw_ospi_bus_init);

#endif /* BSP_USING_OSPI */
#endif /* RT_USING_OSPI */
