/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-11     Carl      the first version
 */

#include "drv_qspi.h"
#include <rtthread.h>
#include "rtdevice.h"
#include "ft_qspi.h"
#include "ft_parameters.h"

#ifdef BSP_USE_QSPI

#define DRV_DEBUG
#define LOG_TAG "drv.qspi"
#include <drv_log.h>

struct ft2004_qspi_bus
{
    FQSpi_t fqspi;
    char *name;
    rt_uint32_t init; /* 1 is init already   */
};

static struct rt_spi_bus _qspi_bus;
static struct ft2004_qspi_bus _ft2004_qspi_bus;

static int ft2004_qspi_init(struct rt_qspi_device *device, struct rt_qspi_configuration *qspi_cfg)
{

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(qspi_cfg != RT_NULL);

    // struct rt_spi_configuration *cfg = &qspi_cfg->parent;
    struct ft2004_qspi_bus *qspi_bus_p = device->parent.bus->parent.user_data;

    if (qspi_bus_p->init == 0)
    {
        qspi_bus_p->init = 1;
        FQSpi_CfgInitialize(&qspi_bus_p->fqspi, FQSpi_LookupConfig(0));
    }

    return RT_EOK;
}

static rt_err_t ft2004_cmdOperation(struct ft2004_qspi_bus *qspi_bus_p, struct rt_spi_message *message)
{
    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    ft_error_t ret;
    RT_ASSERT(qspi_bus_p != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    struct FQSpi_CmdPack cmd_pack = {0};

    if (qspi_message->instruction.qspi_lines == 0)
    {
        LOG_E("instruction is not valid");
        return -RT_ERROR;
    }

    cmd_pack.cmd = qspi_message->instruction.content;

    if (qspi_message->address.qspi_lines != 0)
    {
        cmd_pack.flags |= FQSPI_CMD_NEED_ADDR_MASK;
        cmd_pack.addr = qspi_message->address.content;
    }

    if (qspi_message->address.size == 24)
    {
        cmd_pack.flags |= FQSPI_CMD_ADDRESS_3BYTE_MASK;
    }
    else if (qspi_message->address.size == 32)
    {
        cmd_pack.flags |= FQSPI_CMD_ADDRESS_4BYTE_MASK;
    }

    if (qspi_message->qspi_data_lines != 0)
    {
        if (sndb && (message->length > 0))
        {
            cmd_pack.flags |= FQSPI_CMD_NEED_SET_MASK;
            cmd_pack.txBuf = sndb;
            cmd_pack.length = message->length;
        }
        else if (rcvb && (message->length > 0))
        {
            cmd_pack.flags |= FQSPI_CMD_NEED_GET_MASK;
            cmd_pack.rxBuf = rcvb;
            cmd_pack.length = message->length;
        }
        else
        {
            cmd_pack.flags &= ~(FQSPI_CMD_NEED_GET_MASK | FQSPI_CMD_NEED_SET_MASK);
        }
    }

    if (qspi_message->dummy_cycles)
    {
        cmd_pack.flags |= FQSPI_CMD_NEED_DUMMY_MASK;
        cmd_pack.dummyCycle = qspi_message->dummy_cycles;
    }

    if (cmd_pack.cmd == 0x20)
    {
        if (qspi_message->address.size == 32)
        {
            cmd_pack.cmd = 0xdc;
        }
    }

#ifdef BSP_QSPI_DEBUG
    LOG_I("flags %x", cmd_pack.flags);
#endif

    ret = FQSpi_CmdOperation(&qspi_bus_p->fqspi, &cmd_pack);

#ifdef BSP_QSPI_DEBUG
    if (ret == FQSPI_SUCCESS)
        if (cmd_pack.cmd == 5)
        {
            LOG_I("cmd05 0x%x", cmd_pack.rxBuf[0]);
        }
#endif

    return (ret == FQSPI_SUCCESS) ? RT_EOK : -RT_ERROR;
}

static rt_ssize_t ft2004_qspi_xfer(struct ft2004_qspi_bus *qspi_bus_p, struct rt_spi_message *message)
{
    struct rt_qspi_message *qspi_message = (struct rt_qspi_message *)message;
    rt_ssize_t ret_length = 0;
    const rt_uint8_t *sndb = message->send_buf;
    rt_uint8_t *rcvb = message->recv_buf;
    rt_int32_t length = message->length;
    rt_uint32_t cmd;
    rt_uint32_t addr;
    FQSpi_t *qspi_p;
    FQSpi_Config_t *qspi_config_p;
    struct FQSpi_DataPack data_pack = {0};
    qspi_p = &qspi_bus_p->fqspi;
    qspi_config_p = &qspi_bus_p->fqspi.config;

    cmd = qspi_message->instruction.content;
    addr = qspi_message->address.content;

#ifdef BSP_QSPI_DEBUG
    LOG_I("cmd is %x ", cmd);
    LOG_I("length %d , rcvb %x sndb %x addr %x dummy_cycles %x ", length, rcvb, sndb, addr, qspi_message->dummy_cycles);
#endif

    if (qspi_config_p->channel >= FT_QSPI_MAX_CS_NUM)
    {
        LOG_E("invalid channel[%x] ", qspi_config_p->channel);
        return -RT_ERROR;
    }
    switch (cmd)
    {
    case FQSPI_FLASH_CMD_PP:
    {
        if (RT_NULL != sndb)
        {
            data_pack.cmd = cmd;
            data_pack.addr = addr;
            if (qspi_message->address.size == 24)
            {
                data_pack.flags |= FQSPI_DATA_ADDRESS_3BYTE_MASK;
            }
            else
            {
                data_pack.flags |= FQSPI_DATA_ADDRESS_4BYTE_MASK;
            }

            LOG_E("write flags %x ", data_pack.flags);
            data_pack.txBuf = sndb;
            data_pack.length = length;
            ret_length = ((FQSpi_Write(qspi_p, &data_pack) == FQSPI_SUCCESS) ? length : 0);
        }
        else
        {
            LOG_E("pp cmd %x sndb is null", cmd);
            ret_length = 0;
        }
    }
    break;
    case FQSPI_FLASH_CMD_WRDI: /* for sufd qspi fast read */
        FQSpi_FlashRegSet(qspi_p, cmd, RT_NULL, 0);
    case FQSPI_FLASH_CMD_READ:
    {
        if (RT_NULL != rcvb)
        {
            data_pack.cmd = FQSPI_FLASH_CMD_READ;
            data_pack.addr = addr;
            if (qspi_message->address.size == 24)
            {
                data_pack.flags |= FQSPI_DATA_ADDRESS_3BYTE_MASK;
            }
            else
            {
                data_pack.flags |= FQSPI_DATA_ADDRESS_4BYTE_MASK;
            }

            if (qspi_message->dummy_cycles)
            {
                data_pack.flags |= FQSPI_DATA_NEED_DUMMY_MASK;
                data_pack.dummyCycle = qspi_message->dummy_cycles;
            }
            data_pack.rxBuf = rcvb;
            data_pack.length = length;

            ret_length = ((FQSpi_Read(qspi_p, &data_pack) == FQSPI_SUCCESS) ? length : 0);
        }
        else
        {
            // LOG_E("read cmd %x rcvb is null", cmd);
            ret_length = 0;
        }
    }
    break;

    default:
    {
        if (ft2004_cmdOperation(qspi_bus_p, message) == RT_EOK)
        {
            ret_length = 1;
        }
        else
        {
            LOG_E("ft2004_cmdOperation error");
            ret_length = 0;
        }
    }
    }

    return ret_length;
}

static rt_uint32_t qspixfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    struct ft2004_qspi_bus *qspi_bus_p = device->bus->parent.user_data;

    return ft2004_qspi_xfer(qspi_bus_p, message);
}

static rt_err_t qspi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(configuration != RT_NULL);

    struct rt_qspi_device *qspi_device = (struct rt_qspi_device *)device;
    return ft2004_qspi_init(qspi_device, &qspi_device->config);
}

static const struct rt_spi_ops ft2004_qspi_ops =
    {
        .configure = qspi_configure,
        .xfer = qspixfer,
};

static int ft2004_qspi_register_bus(struct ft2004_qspi_bus *qspi_bus, const char *name)
{
    RT_ASSERT(qspi_bus != RT_NULL);
    RT_ASSERT(name != RT_NULL);

    _qspi_bus.parent.user_data = qspi_bus;
    return rt_qspi_bus_register(&_qspi_bus, name, &ft2004_qspi_ops);
}

rt_err_t ft2004_qspi_bus_attach_device(const char *bus_name, const char *device_name, rt_uint8_t data_line_width, void (*enter_qspi_mode)(), void (*exit_qspi_mode)())
{
    struct rt_qspi_device *qspi_device = RT_NULL;
    rt_err_t result = RT_EOK;

    RT_ASSERT(bus_name != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);
    RT_ASSERT(data_line_width == 1 || data_line_width == 2 || data_line_width == 4);

    qspi_device = (struct rt_qspi_device *)rt_malloc(sizeof(struct rt_qspi_device));
    if (qspi_device == RT_NULL)
    {
        LOG_E("no memory, qspi bus attach device failed!");
        result = -RT_ENOMEM;
        goto __exit;
    }

    qspi_device->enter_qspi_mode = enter_qspi_mode;
    qspi_device->exit_qspi_mode = exit_qspi_mode;
    qspi_device->config.qspi_dl_width = data_line_width;

    result = rt_spi_bus_attach_device(&qspi_device->parent, device_name, bus_name, RT_NULL);

__exit:
    if (result != RT_EOK)
    {
        if (qspi_device)
        {
            rt_free(qspi_device);
        }
    }

    return result;
}

static int rt_hw_qspi_bus_init(void)
{
    return ft2004_qspi_register_bus(&_ft2004_qspi_bus, FT2004_QSPI_NAME);
}
INIT_BOARD_EXPORT(rt_hw_qspi_bus_init);
#ifdef BSP_QSPI_DEBUG
static void cmd05_check(void)
{
    struct FQSpi_CmdPack cmd_pack = {0};
    u8 rx_buffer[1];

    cmd_pack.cmd = 0x6;
    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    rt_memset(&cmd_pack, 0, sizeof(&cmd_pack));
    cmd_pack.cmd = 0x5;
    cmd_pack.flags = FQSPI_CMD_NEED_GET_MASK;
    cmd_pack.rxBuf = rx_buffer;
    cmd_pack.length = sizeof(rx_buffer);

    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    for (u32 i = 0; i < cmd_pack.length; i++)
    {
        LOG_I("cnt %d, 0x%x ", i, rx_buffer[i]);
    }

    rt_memset(&cmd_pack, 0, sizeof(&cmd_pack));
    cmd_pack.cmd = 0x4;
    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    rt_memset(&cmd_pack, 0, sizeof(&cmd_pack));
    cmd_pack.cmd = 0x5;
    cmd_pack.flags = FQSPI_CMD_NEED_GET_MASK;
    cmd_pack.rxBuf = rx_buffer;
    cmd_pack.length = sizeof(rx_buffer);

    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    for (u32 i = 0; i < cmd_pack.length; i++)
    {
        LOG_I("cnt %d, 0x%x ", i, rx_buffer[i]);
    }
}
MSH_CMD_EXPORT_ALIAS(cmd05_check, cmd05_check, cmd05_check);
#endif

#ifdef BSP_QSPI_DEBUG
static void cmd35_check(void)
{
    struct FQSpi_CmdPack cmd_pack = {0};
    u8 rx_buffer[1];

    cmd_pack.cmd = 0x6;
    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    rt_memset(&cmd_pack, 0, sizeof(&cmd_pack));
    cmd_pack.cmd = 0x5;
    cmd_pack.flags = FQSPI_CMD_NEED_GET_MASK;
    cmd_pack.rxBuf = rx_buffer;
    cmd_pack.length = sizeof(rx_buffer);

    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    for (u32 i = 0; i < cmd_pack.length; i++)
    {
        LOG_I("cnt %d, 0x%x ", i, rx_buffer[i]);
    }

    cmd_pack.cmd = 0xB7;
    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    rt_memset(&cmd_pack, 0, sizeof(&cmd_pack));
    cmd_pack.cmd = 0x35;
    cmd_pack.flags = FQSPI_CMD_NEED_GET_MASK;
    cmd_pack.rxBuf = rx_buffer;
    cmd_pack.length = sizeof(rx_buffer);

    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    for (u32 i = 0; i < cmd_pack.length; i++)
    {
        LOG_I("cnt %d, 0x%x ", i, rx_buffer[i]);
    }
}
MSH_CMD_EXPORT_ALIAS(cmd35_check, cmd35_check, cmd35_check);
#endif
#ifdef BSP_QSPI_DEBUG
static void cmd15_check(void)
{
    struct FQSpi_CmdPack cmd_pack = {0};
    u8 rx_buffer[1];

    // cmd_pack.cmd = 0xB7;
    // FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    rt_memset(&cmd_pack, 0, sizeof(&cmd_pack));
    cmd_pack.cmd = 0x15;
    cmd_pack.flags = FQSPI_CMD_NEED_GET_MASK;
    cmd_pack.rxBuf = rx_buffer;
    cmd_pack.length = sizeof(rx_buffer);

    FQSpi_CmdOperation(&_ft2004_qspi_bus.fqspi, &cmd_pack);

    for (u32 i = 0; i < cmd_pack.length; i++)
    {
        LOG_I("cnt %d, 0x%x ", i, rx_buffer[i]);
    }
}
MSH_CMD_EXPORT_ALIAS(cmd15_check, cmd15_check, cmd15_check);
#endif
#endif
