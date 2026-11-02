/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtdevice.h>

#include "fsl_clock.h"
#include "fsl_lpi2c.h"

#if defined(RT_USING_I2C) && defined(BSP_USING_I2C0)

#define MCXC162_LPI2C_READ_CHUNK 256U
#define MCXC162_LPI2C_START_CMD  LPI2C_MTDR_CMD(4U)
#define MCXC162_I2C_UNSUPPORTED  (RT_I2C_ADDR_10BIT | RT_I2C_IGNORE_NACK | RT_I2C_NO_READ_ACK)

static struct rt_i2c_bus_device i2c0_bus;

static status_t mcxc162_i2c_wait_tx_ready(void)
{
    uint32_t flags;
    status_t status;

    do
    {
        flags = LPI2C_MasterGetStatusFlags(LPI2C0);
        status = LPI2C_MasterCheckAndClearError(LPI2C0, flags);
        if (status != kStatus_Success)
        {
            return status;
        }
    } while ((flags & (uint32_t)kLPI2C_MasterTxReadyFlag) == 0U);

    return kStatus_Success;
}

static status_t mcxc162_i2c_restart(const struct rt_i2c_msg *msg)
{
    lpi2c_direction_t direction;
    status_t status;

    status = mcxc162_i2c_wait_tx_ready();
    if (status != kStatus_Success)
    {
        return status;
    }

    direction = (msg->flags & RT_I2C_RD) != 0U ? kLPI2C_Read : kLPI2C_Write;
    LPI2C0->MTDR = MCXC162_LPI2C_START_CMD |
                   ((uint32_t)msg->addr << 1U) | (uint32_t)direction;

    return kStatus_Success;
}

static status_t mcxc162_i2c_transfer_message(const struct rt_i2c_msg *msg)
{
    rt_size_t offset = 0U;
    rt_size_t remaining = msg->len;
    rt_size_t chunk;
    status_t status;

    if ((msg->flags & RT_I2C_RD) == 0U)
    {
        if (remaining == 0U)
        {
            return kStatus_Success;
        }
        return LPI2C_MasterSend(LPI2C0, msg->buf, remaining);
    }

    while (remaining != 0U)
    {
        chunk = remaining > MCXC162_LPI2C_READ_CHUNK ? MCXC162_LPI2C_READ_CHUNK : remaining;
        if (offset != 0U)
        {
            status = mcxc162_i2c_restart(msg);
            if (status != kStatus_Success)
            {
                return status;
            }
        }

        status = LPI2C_MasterReceive(LPI2C0, &msg->buf[offset], chunk);
        if (status != kStatus_Success)
        {
            return status;
        }

        offset += chunk;
        remaining -= chunk;
    }

    return kStatus_Success;
}

static rt_ssize_t mcxc162_i2c_xfer(struct rt_i2c_bus_device *bus,
                                   struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    rt_uint32_t i;
    status_t status;

    if (num == 0U || (msgs[0].flags & RT_I2C_NO_START) != 0U ||
        (msgs[num - 1U].flags & RT_I2C_NO_STOP) != 0U)
    {
        return 0;
    }

    for (i = 0U; i < num; i++)
    {
        if ((msgs[i].flags & MCXC162_I2C_UNSUPPORTED) != 0U)
        {
            return 0;
        }
        if (i != 0U && (msgs[i].flags & RT_I2C_NO_START) != 0U &&
            (((msgs[i - 1U].flags | msgs[i].flags) & RT_I2C_RD) != 0U ||
             msgs[i - 1U].addr != msgs[i].addr))
        {
            return 0;
        }
    }

    if (bus->config.usage_freq != bus->config.max_hz)
    {
        LPI2C_MasterSetBaudRate(LPI2C0, CLOCK_GetLpi2cClkFreq(0U), bus->config.max_hz);
        bus->config.usage_freq = bus->config.max_hz;
    }

    LPI2C_MasterEnable(LPI2C0, true);
    LPI2C_SlaveEnable(LPI2C0, false);
    status = LPI2C_MasterStart(LPI2C0, msgs[0].addr,
                               (msgs[0].flags & RT_I2C_RD) != 0U ? kLPI2C_Read : kLPI2C_Write);
    if (status != kStatus_Success)
    {
        return 0;
    }

    for (i = 0U; i < num; i++)
    {
        if (i != 0U && (msgs[i].flags & RT_I2C_NO_START) == 0U)
        {
            /* ERR053261 requires a START between consecutive receive commands. */
            status = mcxc162_i2c_restart(&msgs[i]);
        }
        if (status == kStatus_Success)
        {
            status = mcxc162_i2c_transfer_message(&msgs[i]);
        }
        if (status != kStatus_Success)
        {
            break;
        }
    }

    if (LPI2C_MasterStop(LPI2C0) != kStatus_Success)
    {
        return 0;
    }

    return status == kStatus_Success ? num : i;
}

static const struct rt_i2c_bus_device_ops mcxc162_i2c_ops = {
    .master_xfer = mcxc162_i2c_xfer,
};

int rt_hw_i2c_init(void)
{
    lpi2c_master_config_t config;

    CLOCK_SetClockDiv(kCLOCK_DivLPI2C0, 1U);
    CLOCK_AttachClk(kFRO_LF_DIV_to_LPI2C0);

    LPI2C_MasterGetDefaultConfig(&config);
    config.baudRate_Hz = 100000U;
    LPI2C_MasterInit(LPI2C0, &config, CLOCK_GetLpi2cClkFreq(0U));

    i2c0_bus.config.max_hz = config.baudRate_Hz;
    i2c0_bus.config.usage_freq = config.baudRate_Hz;
    i2c0_bus.ops = &mcxc162_i2c_ops;
    return rt_i2c_bus_device_register(&i2c0_bus, "i2c0");
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C && BSP_USING_I2C0 */
