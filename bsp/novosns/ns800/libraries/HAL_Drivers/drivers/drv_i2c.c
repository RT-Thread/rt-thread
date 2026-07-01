/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-06-07     dirtwillfly    first version for NS800
 */

#include "rtthread.h"
#include "drv_i2c.h"

#if defined(BSP_USING_I2C)

#define DRV_DEBUG
#define LOG_TAG "drv.i2c"
#include <drv_log.h>

#define DEFAULT_I2C_BAUDRATE (100 * 1000U)
#define I2C_TIMEOUT_MS        (1000U)

#if !defined(BSP_USING_HARD_I2C1) && !defined(BSP_USING_HARD_I2C2)
#error "BSP_USING_I2C is enabled, but no hardware I2C instance is selected"
#endif

enum
{
#ifdef BSP_USING_HARD_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_HARD_I2C2
    I2C2_INDEX,
#endif
};

static struct ns800_i2c_config i2c_config[] =
{
#ifdef BSP_USING_HARD_I2C1
    I2C1_BUS_CONFIG,
#endif
#ifdef BSP_USING_HARD_I2C2
    I2C2_BUS_CONFIG,
#endif
};

static struct ns800_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static I2C_Status ns800_i2c_wait_master_tx_ready(I2C_TypeDef *i2c, uint32_t timeout_ms)
{
    uint32_t start_tick = rt_tick_get();
    uint32_t status;
    I2C_Status result;
    uint8_t txCount;
    uint8_t txFifoSize = 16U;

    while ((rt_tick_get() - start_tick) < rt_tick_from_millisecond(timeout_ms))
    {
        txCount = txFifoSize - I2C_getMasterTxFifoCounts(i2c);

        status = I2C_getMasterStatusFlags(i2c);
        result = I2C_checkAndClearMasterError(i2c, status);
        if (result != I2C_STATUS_SUCCESS)
        {
            return result;
        }

        if (txCount > 0U)
        {
            return I2C_STATUS_SUCCESS;
        }

        rt_thread_mdelay(1);
    }

    LOG_E("I2C wait TX ready timeout");
    return I2C_STATUS_TIMEOUT;
}

static I2C_Status ns800_i2c_wait_bus_available(I2C_TypeDef *i2c, uint32_t timeout_ms)
{
    uint32_t start_tick = rt_tick_get();

    while ((rt_tick_get() - start_tick) < rt_tick_from_millisecond(timeout_ms))
    {
        I2C_Status result = I2C_checkMasterBusyBus(i2c);
        if (result == I2C_STATUS_SUCCESS)
        {
            return I2C_STATUS_SUCCESS;
        }

        rt_thread_mdelay(1);
    }

    return I2C_STATUS_BUSY;
}

static I2C_Status ns800_i2c_send_stop(I2C_TypeDef *i2c, uint32_t timeout_ms)
{
    uint32_t start_tick = rt_tick_get();
    uint32_t status;
    I2C_Status result;

    result = ns800_i2c_wait_master_tx_ready(i2c, timeout_ms);
    if (result != I2C_STATUS_SUCCESS)
    {
        return result;
    }

    WRITE_REG(i2c->MTDR.WORDVAL, (uint32_t)I2C_COMMAND_STOP);

    while ((rt_tick_get() - start_tick) < rt_tick_from_millisecond(timeout_ms))
    {
        status = I2C_getMasterStatusFlags(i2c);
        if ((status & (uint32_t)I2C_MASTER_FLAG_STOP) != 0U)
        {
            result = I2C_checkAndClearMasterError(i2c, status);
            I2C_clearMasterStatusFlags(i2c, (uint32_t)I2C_MASTER_FLAG_CLEAR);
            return result;
        }

        if ((status & (uint32_t)I2C_MASTER_FLAG_NACK) != 0U)
        {
            result = I2C_checkAndClearMasterError(i2c, status);
            I2C_clearMasterStatusFlags(i2c, (uint32_t)I2C_MASTER_FLAG_CLEAR);
            return result;
        }

        rt_thread_mdelay(1);
    }

    status = I2C_getMasterStatusFlags(i2c);
    LOG_E("I2C wait STOP timeout, status=0x%x, resetting I2C", status);
    I2C_resetMaster(i2c);
    I2C_enableMasterModule(i2c);

    return I2C_STATUS_TIMEOUT;
}

static void ns800_i2c_reset_bus(I2C_TypeDef *i2c)
{
    I2C_resetMaster(i2c);
    I2C_enableMasterModule(i2c);
    I2C_clearMasterStatusFlags(i2c, (uint32_t)I2C_MASTER_FLAG_CLEAR);
}

static void ns800_i2c_apply_default_config(struct ns800_i2c_config *cfg)
{
    RT_ASSERT(cfg != RT_NULL);

    if (cfg->baudrate == 0U)
    {
        cfg->baudrate = DEFAULT_I2C_BAUDRATE;
    }
}

/**
 * @brief   Initialize I2C GPIO pins
 * @param   cfg I2C configuration structure
 */
static void ns800_i2c_gpio_init(struct ns800_i2c_config *cfg)
{
    RT_ASSERT(cfg != RT_NULL);

    LOG_D("I2C[%s] GPIO init: SCL(port=%p, pin=%d, alt=%d), SDA(port=%p, pin=%d, alt=%d)",
          cfg->name, (void *)cfg->scl_port, cfg->scl_pin, cfg->scl_alt_func,
          (void *)cfg->sda_port, cfg->sda_pin, cfg->sda_alt_func);

    /* SCL pin configuration - follow SDK example order */
    if (cfg->scl_port != RT_NULL && cfg->scl_alt_func != 0U)
    {
        GPIO_setPinConfig(cfg->scl_port, cfg->scl_pin, cfg->scl_alt_func);
        GPIO_setAnalogMode(cfg->scl_port, cfg->scl_pin, GPIO_ANALOG_DISABLED);
        GPIO_setPadConfig(cfg->scl_port, cfg->scl_pin, GPIO_PIN_TYPE_PULLUP);
        GPIO_setQualificationMode(cfg->scl_port, cfg->scl_pin, GPIO_QUAL_ASYNC);
        GPIO_setDirectionMode(cfg->scl_port, cfg->scl_pin, GPIO_DIR_MODE_IN);
    }

    /* SDA pin configuration - follow SDK example order */
    if (cfg->sda_port != RT_NULL && cfg->sda_alt_func != 0U)
    {
        GPIO_setPinConfig(cfg->sda_port, cfg->sda_pin, cfg->sda_alt_func);
        GPIO_setAnalogMode(cfg->sda_port, cfg->sda_pin, GPIO_ANALOG_DISABLED);
        GPIO_setPadConfig(cfg->sda_port, cfg->sda_pin, GPIO_PIN_TYPE_PULLUP);
        GPIO_setQualificationMode(cfg->sda_port, cfg->sda_pin, GPIO_QUAL_ASYNC);
        GPIO_setDirectionMode(cfg->sda_port, cfg->sda_pin, GPIO_DIR_MODE_IN);
    }
}

static rt_err_t ns800_i2c_init(struct ns800_i2c *i2c_drv)
{
    RT_ASSERT(i2c_drv != RT_NULL);

    I2C_TypeDef *i2c = i2c_drv->config->Instance;
    struct ns800_i2c_config *cfg = i2c_drv->config;

    LOG_D("I2C[%s] init start, Instance=%p, baudrate=%d",
          cfg->name, (void *)i2c, cfg->baudrate);

    ns800_i2c_apply_default_config(cfg);

    /* Initialize GPIO pins FIRST - follow SDK example order */
    ns800_i2c_gpio_init(cfg);

    /* Enable I2C module clock */
    if (i2c == I2C1)
    {
        LOG_D("I2C[%s] enabling I2C1 clock", cfg->name);
        RCC_enableI2c1Clock();
    }
    else if (i2c == I2C2)
    {
        LOG_D("I2C[%s] enabling I2C2 clock", cfg->name);
        RCC_enableI2c2Clock();
    }

    LOG_D("I2C[%s] clock enabled, PCLKEN5=0x%x", cfg->name, RCC->PCLKEN5.WORDVAL);

    /* Reset module before configuring it */
    I2C_resetMaster(i2c);
    LOG_D("I2C[%s] master reset done", cfg->name);

    /* Disable debug mode */
    I2C_disableMasterDebug(i2c);

    /* Set master water marks */
    I2C_setMasterWatermarks(i2c, I2C_MASTER_WATERMARK_0, I2C_MASTER_WATERMARK_0);

    /* Configure master glitch filters
       And set FILTSDA to 0 disables the filter, so the min value is 1 */
    I2C_setMasterGlitchFilter(i2c, I2C_MASTER_FILTER_PCLK1, I2C_MASTER_FILTER_PCLK1);

    /* Configure baudrate after the SDA/SCL glitch filter setting */
    I2C_configMasterBaudRate(i2c, RCC_getPclk2Frequency(), cfg->baudrate);

    /* Configure bus idle timeouts after baudrate setting
       The value is equal to BUSIDLE cycles of functional clock divided by prescaler
       And set BUSIDLE to 0 disables the filter, so the min value is 1 */
    I2C_setMasterBusIdleTimeout(i2c, 1U);

    /* Configure pin low timeouts after baudrate setting
       The value is equal to PINLOW cycles of functional clock divided by prescaler
       Set PINLOW to 0 to disable the timeout filter */
    I2C_setMasterPinLowTimeout(i2c, I2C_MASTER_PINLOW_SCLSDA, 0U);

    /* Config master data match mode, match code and rxmatchonly */
    I2C_configMasterDataMatch(i2c, I2C_MASTER_MATCHMODE_DISABLED, 0U, 0U, I2C_MASTER_RXMATCHDATAONLY_DISABLE);

    /* Enable master module */
    I2C_enableMasterModule(i2c);
    LOG_D("I2C[%s] master module enabled", cfg->name);

    /* Verify I2C is properly initialized */
    uint32_t mcr = READ_REG(i2c->MCR.WORDVAL);
    uint32_t msr = READ_REG(i2c->MSR.WORDVAL);
    LOG_D("I2C[%s] MCR=0x%x, MSR=0x%x", cfg->name, mcr, msr);

    return RT_EOK;
}

static rt_err_t ns800_i2c_configure(struct rt_i2c_bus_device *bus)
{
    RT_ASSERT(RT_NULL != bus);
    struct ns800_i2c *i2c_drv = rt_container_of(bus, struct ns800_i2c, i2c_bus);

    return ns800_i2c_init(i2c_drv);
}

static rt_ssize_t ns800_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                         struct rt_i2c_msg msgs[],
                                         rt_uint32_t num)
{
    rt_uint32_t i = 0;
    rt_int32_t ret = 0;
    struct rt_i2c_msg *msg = RT_NULL;
    struct ns800_i2c *i2c_obj;
    I2C_Status status;
    rt_uint32_t timeout;
    rt_bool_t xfer_active = RT_FALSE;

    if (num == 0)
    {
        return 0;
    }

    RT_ASSERT((msgs != RT_NULL) && (bus != RT_NULL));
    i2c_obj = rt_container_of(bus, struct ns800_i2c, i2c_bus);
    RT_ASSERT(i2c_obj != RT_NULL);
    I2C_TypeDef *i2c = i2c_obj->config->Instance;

    /* Get timeout from config, default 1000ms */
    timeout = i2c_obj->config->timeout > 0 ? i2c_obj->config->timeout : I2C_TIMEOUT_MS;

    LOG_D("xfer start %d msgs", num);

    status = ns800_i2c_wait_bus_available(i2c, timeout);
    if (status != I2C_STATUS_SUCCESS)
    {
        LOG_E("I2C[%s] Bus is busy", bus->parent.parent.name);
        return -RT_EBUSY;
    }

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        LOG_D("xfer msgs[%d] addr=0x%02x buf=%p len=%u flags=0x%x",
              i, msg->addr, (void *)msg->buf, (unsigned int)msg->len, msg->flags);

        if ((msg->flags & RT_I2C_ADDR_10BIT) || (msg->addr > 0x7FU))
        {
            LOG_E("I2C[%s] only 7-bit addressing is supported, addr=0x%x",
                  bus->parent.parent.name, msg->addr);
            ret = -RT_EINVAL;
            goto out;
        }

        if (!(msg->flags & RT_I2C_NO_START))
        {
            /* RT-Thread uses 7-bit address, SDK expects 8-bit address */
            /* Convert 7-bit address to 8-bit address by shifting left */
            uint8_t addr_8bit = msg->addr << 1;

            if (msg->flags & RT_I2C_RD)
            {
                status = (i == 0U) ? I2C_sendStart(i2c, addr_8bit, I2C_DIRECTION_READ)
                                   : I2C_sendReStart(i2c, addr_8bit, I2C_DIRECTION_READ);
            }
            else
            {
                status = (i == 0U) ? I2C_sendStart(i2c, addr_8bit, I2C_DIRECTION_WRITE)
                                   : I2C_sendReStart(i2c, addr_8bit, I2C_DIRECTION_WRITE);
            }

            LOG_D("I2C[%s] SendStart status=%d, MSR=0x%x", bus->parent.parent.name, status, I2C_getMasterStatusFlags(i2c));

            if (status != I2C_STATUS_SUCCESS)
            {
                LOG_E("I2C[%s] SendStart error(%d)", bus->parent.parent.name, status);
                ret = -RT_EIO;
                goto out;
            }

            xfer_active = RT_TRUE;
        }
        else
        {
            /* RT_I2C_NO_START: do not generate START/RESTART.
             * Only sequential writes (continuing the previous address phase)
             * are supported.
             */
            if ((i == 0) || ((msg->flags & RT_I2C_RD)))
            {
                LOG_E("I2C[%s] RT_I2C_NO_START is not supported for the first message or read transfer",
                      bus->parent.parent.name);
                ret = -RT_EINVAL;
                goto out;
            }

            status = I2C_STATUS_SUCCESS;
        }

        if (msg->flags & RT_I2C_RD)
        {
            status = I2C_receiveDataMaster(i2c, msg->buf, msg->len);
            if (status != I2C_STATUS_SUCCESS)
            {
                LOG_E("I2C[%s] Read error(%d)", bus->parent.parent.name, status);
                ret = -RT_EIO;
                goto out;
            }
        }
        else
        {
            status = I2C_sendDataMaster(i2c, msg->buf, msg->len);
            if (status != I2C_STATUS_SUCCESS)
            {
                LOG_E("I2C[%s] Write error(%d)", bus->parent.parent.name, status);
                ret = -RT_EIO;
                goto out;
            }
        }

        if (((i + 1U) == num) && !(msg->flags & RT_I2C_NO_STOP))
        {
            /* Use timeout protected STOP */
            status = ns800_i2c_send_stop(i2c, timeout);
            if (status != I2C_STATUS_SUCCESS)
            {
                LOG_E("I2C[%s] SendStop error(%d), resetting bus", bus->parent.parent.name, status);
                ns800_i2c_reset_bus(i2c);
                xfer_active = RT_FALSE;
                ret = -RT_EIO;
                goto out;
            }
            xfer_active = RT_FALSE;
        }
    }

    ret = num;
    LOG_D("xfer end %d msgs", num);
    return ret;

out:
    if (xfer_active)
    {
        /* Safe error recovery - use timeout protected STOP or reset. */
        ns800_i2c_send_stop(i2c, timeout / 2);  /* Shorter timeout for recovery. */
    }
    return ret;
}

static rt_err_t ns800_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                       int cmd,
                                       void *args)
{
    rt_err_t result = RT_EOK;
    struct ns800_i2c *i2c_obj;

    RT_ASSERT(bus != RT_NULL);
    i2c_obj = rt_container_of(bus, struct ns800_i2c, i2c_bus);
    RT_ASSERT(i2c_obj != RT_NULL);

    I2C_TypeDef *i2c = i2c_obj->config->Instance;

    switch (cmd)
    {
    case RT_I2C_DEV_CTRL_ADDR:
        /* Set slave address - not typically used for master */
        result = -RT_ENOSYS;
        break;

    case RT_I2C_DEV_CTRL_TIMEOUT:
        /* Set timeout in milliseconds */
        if (args != RT_NULL)
        {
            i2c_obj->config->timeout = *(rt_uint32_t *)args;
        }
        break;

    case RT_I2C_CTRL_SET_MAX_HZ:
        /* Change baudrate */
        if (args != RT_NULL)
        {
            i2c_obj->config->baudrate = *(rt_uint32_t *)args;
            I2C_resetMaster(i2c);
            I2C_configMasterBaudRate(i2c, RCC_getPclk2Frequency(), i2c_obj->config->baudrate);
            I2C_enableMasterModule(i2c);
        }
        break;

    case RT_I2C_DEV_CTRL_RW:
        /* Combined read/write operation */
        result = -RT_ENOSYS;
        break;

    case RT_I2C_DEV_CTRL_CLK:
        /* Set clock - similar to baud rate */
        if (args != RT_NULL)
        {
            i2c_obj->config->baudrate = *(rt_uint32_t *)args;
            I2C_resetMaster(i2c);
            I2C_configMasterBaudRate(i2c, RCC_getPclk2Frequency(), i2c_obj->config->baudrate);
            I2C_enableMasterModule(i2c);
        }
        break;

    case BSP_I2C_CTRL_SET_TIMING:
        /* Set timing - map to baudrate setting */
        if (args != RT_NULL)
        {
            i2c_obj->config->baudrate = *(rt_uint32_t *)args;
            I2C_resetMaster(i2c);
            I2C_configMasterBaudRate(i2c, RCC_getPclk2Frequency(), i2c_obj->config->baudrate);
            I2C_enableMasterModule(i2c);
        }
        break;

    default:
        result = -RT_ENOSYS;
        break;
    }

    return result;
}

static const struct rt_i2c_bus_device_ops ns800_i2c_ops =
{
    .master_xfer = ns800_i2c_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = ns800_i2c_bus_control,
};

int ns800_hw_i2c_bus_init(void)
{
    int ret = -RT_ERROR;
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(i2c_objs[0]);

    for (int i = 0; i < obj_num; i++)
    {
        i2c_objs[i].i2c_bus.ops = &ns800_i2c_ops;
        i2c_objs[i].config = &i2c_config[i];
        ns800_i2c_apply_default_config(&i2c_config[i]);

        /* Initialize bus timeout from config */
        i2c_objs[i].i2c_bus.timeout = i2c_config[i].timeout;
        i2c_objs[i].i2c_bus.retries = 0;

        ret = ns800_i2c_configure(&i2c_objs[i].i2c_bus);
        if (ret != RT_EOK)
        {
            LOG_E("%s bus configure failed %d", i2c_config[i].name, ret);
            return -RT_ERROR;
        }

        ret = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_objs[i].config->name);
        if (ret != RT_EOK)
        {
            LOG_E("%s bus init failed %d", i2c_config[i].name, ret);
        }
        else
        {
            LOG_D("%s bus init done", i2c_config[i].name);
        }
    }

    return ret;
}

int rt_hw_i2c_init(void)
{
    return ns800_hw_i2c_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#ifdef RT_USING_FINSH

/**
 * @brief   Scan I2C bus for devices
 * @param   i2c I2C instance
 * @param   bus_name Bus name for logging
 */
static void ns800_i2c_scan_bus(I2C_TypeDef *i2c, const char *bus_name)
{
    uint8_t found_count = 0;
    uint32_t timeout = 100;

    LOG_I("Scanning I2C bus: %s...", bus_name);

    for (uint8_t addr = 1; addr < 128; addr++)
    {
        I2C_Status status;

        /* RT-Thread uses 7-bit address, SDK expects 8-bit address */
        uint8_t addr_8bit = addr << 1;

        /* Send START with write direction */
        status = I2C_sendStart(i2c, addr_8bit, I2C_DIRECTION_WRITE);

        if (status == I2C_STATUS_SUCCESS)
        {
            uint32_t msr = I2C_getMasterStatusFlags(i2c);

            /* Check if we got ACK (no NACK) */
            if (!(msr & I2C_MASTER_FLAG_NACK))
            {
                LOG_I("I2C device found at address: 0x%02X", addr);
                found_count++;
            }

            /* Clear any pending flags */
            I2C_clearMasterStatusFlags(i2c, I2C_MASTER_FLAG_NACK);

            /* Send STOP to release bus */
            ns800_i2c_send_stop(i2c, timeout);
        }
        else
        {
            /* Failed to send start, reset and continue */
            I2C_resetMaster(i2c);
            I2C_enableMasterModule(i2c);
        }

        /* Small delay between devices */
        rt_thread_mdelay(1);
    }

    if (found_count == 0)
    {
        LOG_W("No I2C devices found on bus: %s", bus_name);
    }
    else
    {
        LOG_I("Found %d I2C device(s) on bus: %s", found_count, bus_name);
    }
}

/**
 * @brief   Finsh command to scan I2C buses
 * @param   argc Argument count
 * @param   argv Argument array
 */
static void i2c_scan(int argc, char **argv)
{
    const char *bus_name = RT_NULL;

    if (argc == 2)
    {
        bus_name = argv[1];
    }

    for (int i = 0; i < sizeof(i2c_objs) / sizeof(i2c_objs[0]); i++)
    {
        if (i2c_objs[i].config->name != RT_NULL)
        {
            if (bus_name == RT_NULL || rt_strcmp(bus_name, i2c_objs[i].config->name) == 0)
            {
                ns800_i2c_scan_bus(i2c_objs[i].config->Instance, i2c_objs[i].config->name);
            }
        }
    }
}
MSH_CMD_EXPORT(i2c_scan, Scan I2C bus for devices);

#endif /* RT_USING_FINSH */

#endif /* defined(BSP_USING_I2C) */

