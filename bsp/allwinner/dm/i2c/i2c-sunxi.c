/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "i2c.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SUNXI_TWI_ADDR             0x00
#define SUNXI_TWI_DATA             0x08
#define SUNXI_TWI_CTL              0x0c
#define SUNXI_TWI_STAT             0x10
#define SUNXI_TWI_CLK              0x14
#define SUNXI_TWI_SRST             0x18

#define SUNXI_TWI_CTL_ACK          RT_BIT(2)
#define SUNXI_TWI_CTL_INTFLG       RT_BIT(3)
#define SUNXI_TWI_CTL_STP          RT_BIT(4)
#define SUNXI_TWI_CTL_STA          RT_BIT(5)
#define SUNXI_TWI_CTL_BUSEN        RT_BIT(6)

#define SUNXI_TWI_STAT_START       0x08
#define SUNXI_TWI_STAT_RESTART     0x10
#define SUNXI_TWI_STAT_ADDR_W_ACK  0x18
#define SUNXI_TWI_STAT_ADDR_W_NAK  0x20
#define SUNXI_TWI_STAT_DATA_W_ACK  0x28
#define SUNXI_TWI_STAT_DATA_W_NAK  0x30
#define SUNXI_TWI_STAT_ARB_LOST    0x38
#define SUNXI_TWI_STAT_ADDR_R_ACK  0x40
#define SUNXI_TWI_STAT_ADDR_R_NAK  0x48
#define SUNXI_TWI_STAT_DATA_R_ACK  0x50
#define SUNXI_TWI_STAT_DATA_R_NAK  0x58

#define SUNXI_TWI_TIMEOUT_US       50000

struct sunxi_i2c
{
    struct rt_i2c_bus_device parent;
    struct rt_clk *clk;
    struct rt_reset_control *reset;
    void *base;
    rt_uint32_t input_rate;
    rt_uint32_t clear_irq;
};

struct sunxi_i2c_soc_data
{
    rt_uint32_t clear_irq;
};

static const struct sunxi_i2c_soc_data sunxi_i2c_data = { 0 };
static const struct sunxi_i2c_soc_data sunxi_i2c_h616_data =
{
    .clear_irq = SUNXI_TWI_CTL_INTFLG,
};

#define to_sunxi_i2c(raw) rt_container_of(raw, struct sunxi_i2c, parent)

static rt_uint32_t sunxi_i2c_read(struct sunxi_i2c *i2c, rt_uint32_t offset)
{
    return HWREG32(i2c->base + offset);
}

static void sunxi_i2c_write(struct sunxi_i2c *i2c, rt_uint32_t offset,
        rt_uint32_t value)
{
    HWREG32(i2c->base + offset) = value;
}

static rt_err_t sunxi_i2c_wait(struct sunxi_i2c *i2c)
{
    rt_int32_t timeout;

    for (timeout = SUNXI_TWI_TIMEOUT_US; timeout > 0; --timeout)
    {
        if (sunxi_i2c_read(i2c, SUNXI_TWI_CTL) & SUNXI_TWI_CTL_INTFLG)
        {
            return RT_EOK;
        }

        rt_hw_us_delay(1);
    }

    return -RT_ETIMEOUT;
}

static void sunxi_i2c_continue(struct sunxi_i2c *i2c, rt_bool_t ack)
{
    rt_uint32_t control = sunxi_i2c_read(i2c, SUNXI_TWI_CTL);

    control |= SUNXI_TWI_CTL_BUSEN;
    control &= ~(SUNXI_TWI_CTL_STA | SUNXI_TWI_CTL_STP | SUNXI_TWI_CTL_INTFLG);
    if (ack)
    {
        control |= SUNXI_TWI_CTL_ACK;
    }
    else
    {
        control &= ~SUNXI_TWI_CTL_ACK;
    }
    sunxi_i2c_write(i2c, SUNXI_TWI_CTL, control | i2c->clear_irq);
}

static rt_err_t sunxi_i2c_start(struct sunxi_i2c *i2c)
{
    rt_uint32_t control = sunxi_i2c_read(i2c, SUNXI_TWI_CTL);
    rt_err_t err;

    control |= SUNXI_TWI_CTL_BUSEN | SUNXI_TWI_CTL_STA;
    control &= ~SUNXI_TWI_CTL_INTFLG;
    sunxi_i2c_write(i2c, SUNXI_TWI_CTL, control | i2c->clear_irq);

    if ((err = sunxi_i2c_wait(i2c)))
    {
        return err;
    }

    control = sunxi_i2c_read(i2c, SUNXI_TWI_STAT) & 0xff;
    return control == SUNXI_TWI_STAT_START || control == SUNXI_TWI_STAT_RESTART ?
            RT_EOK : -RT_ERROR;
}

static void sunxi_i2c_stop(struct sunxi_i2c *i2c)
{
    rt_int32_t timeout;
    rt_uint32_t control = sunxi_i2c_read(i2c, SUNXI_TWI_CTL);

    control |= SUNXI_TWI_CTL_BUSEN | SUNXI_TWI_CTL_STP;
    control &= ~(SUNXI_TWI_CTL_STA | SUNXI_TWI_CTL_ACK | SUNXI_TWI_CTL_INTFLG);
    sunxi_i2c_write(i2c, SUNXI_TWI_CTL, control | i2c->clear_irq);

    for (timeout = SUNXI_TWI_TIMEOUT_US; timeout > 0; --timeout)
    {
        if (!(sunxi_i2c_read(i2c, SUNXI_TWI_CTL) & SUNXI_TWI_CTL_STP))
        {
            break;
        }
        rt_hw_us_delay(1);
    }
}

static rt_err_t sunxi_i2c_write_byte(struct sunxi_i2c *i2c, rt_uint8_t byte,
        rt_uint8_t expected, rt_bool_t ignore_nack)
{
    rt_err_t err;
    rt_uint32_t status;

    sunxi_i2c_write(i2c, SUNXI_TWI_DATA, byte);
    sunxi_i2c_continue(i2c, RT_FALSE);

    if ((err = sunxi_i2c_wait(i2c)))
    {
        return err;
    }

    status = sunxi_i2c_read(i2c, SUNXI_TWI_STAT) & 0xff;
    if (status == expected || (ignore_nack &&
            (status == SUNXI_TWI_STAT_ADDR_W_NAK ||
             status == SUNXI_TWI_STAT_DATA_W_NAK)))
    {
        return RT_EOK;
    }

    return status == SUNXI_TWI_STAT_ARB_LOST ? -RT_EBUSY : -RT_EIO;
}

static rt_err_t sunxi_i2c_xfer_msg(struct sunxi_i2c *i2c,
        struct rt_i2c_msg *msg, rt_bool_t start)
{
    rt_bool_t read = msg->flags & RT_I2C_RD;
    rt_bool_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
    rt_uint16_t index;
    rt_err_t err;

    if (msg->flags & RT_I2C_ADDR_10BIT)
    {
        return -RT_ENOSYS;
    }

    if (start)
    {
        if ((err = sunxi_i2c_start(i2c)))
        {
            return err;
        }

        err = sunxi_i2c_write_byte(i2c, (msg->addr << 1) | read,
                read ? SUNXI_TWI_STAT_ADDR_R_ACK : SUNXI_TWI_STAT_ADDR_W_ACK,
                ignore_nack);
        if (err)
        {
            return err;
        }
    }

    if (read)
    {
        for (index = 0; index < msg->len; ++index)
        {
            rt_bool_t ack = index + 1 < msg->len &&
                    !(msg->flags & RT_I2C_NO_READ_ACK);
            rt_uint32_t expected = ack ? SUNXI_TWI_STAT_DATA_R_ACK :
                    SUNXI_TWI_STAT_DATA_R_NAK;

            sunxi_i2c_continue(i2c, ack);
            if ((err = sunxi_i2c_wait(i2c)))
            {
                return err;
            }
            if ((sunxi_i2c_read(i2c, SUNXI_TWI_STAT) & 0xff) != expected)
            {
                return -RT_EIO;
            }
            msg->buf[index] = sunxi_i2c_read(i2c, SUNXI_TWI_DATA);
        }
    }
    else
    {
        for (index = 0; index < msg->len; ++index)
        {
            if ((err = sunxi_i2c_write_byte(i2c, msg->buf[index],
                    SUNXI_TWI_STAT_DATA_W_ACK, ignore_nack)))
            {
                return err;
            }
        }
    }

    return RT_EOK;
}

static rt_ssize_t sunxi_i2c_master_xfer(struct rt_i2c_bus_device *bus,
        struct rt_i2c_msg msgs[], rt_uint32_t count)
{
    rt_uint32_t index;
    rt_err_t err;
    struct sunxi_i2c *i2c = to_sunxi_i2c(bus);

    if (!msgs || !count)
    {
        return -RT_EINVAL;
    }

    for (index = 0; index < count; ++index)
    {
        if ((msgs[index].flags & RT_I2C_NO_START) && !index)
        {
            return -RT_EINVAL;
        }

        err = sunxi_i2c_xfer_msg(i2c, &msgs[index],
                !(msgs[index].flags & RT_I2C_NO_START));
        if (err)
        {
            sunxi_i2c_stop(i2c);
            return err;
        }
    }

    if (!(msgs[count - 1].flags & RT_I2C_NO_STOP))
    {
        sunxi_i2c_stop(i2c);
    }

    return count;
}

static rt_err_t sunxi_i2c_set_bus_rate(struct sunxi_i2c *i2c,
        rt_uint32_t target_rate)
{
    rt_uint32_t best_rate = 0;
    rt_uint32_t best_divider = 0;
    int n;
    int m;

    if (!target_rate || !i2c->input_rate)
    {
        return -RT_EINVAL;
    }

    for (n = 0; n <= 7; ++n)
    {
        for (m = 0; m <= 15; ++m)
        {
            rt_uint32_t rate = i2c->input_rate / ((1u << n) * (m + 1) * 10);

            if (rate <= target_rate && rate > best_rate)
            {
                best_rate = rate;
                best_divider = (m << 3) | n;
            }
        }
    }

    if (!best_rate)
    {
        return -RT_EINVAL;
    }

    sunxi_i2c_write(i2c, SUNXI_TWI_CLK, best_divider);
    i2c->parent.config.max_hz = target_rate;
    i2c->parent.config.usage_freq = best_rate;

    return RT_EOK;
}

static rt_err_t sunxi_i2c_control(struct rt_i2c_bus_device *bus, int cmd,
        void *args)
{
    struct sunxi_i2c *i2c = to_sunxi_i2c(bus);

    if (cmd == RT_I2C_DEV_CTRL_CLK && args)
    {
        return sunxi_i2c_set_bus_rate(i2c, *(rt_uint32_t *)args);
    }

    return -RT_ENOSYS;
}

static const struct rt_i2c_bus_device_ops sunxi_i2c_ops =
{
    .master_xfer = sunxi_i2c_master_xfer,
    .i2c_bus_control = sunxi_i2c_control,
};

static void sunxi_i2c_free(struct sunxi_i2c *i2c)
{
    if (!rt_is_err_or_null(i2c->reset))
    {
        rt_reset_control_put(i2c->reset);
    }
    if (!rt_is_err_or_null(i2c->clk))
    {
        rt_clk_disable_unprepare(i2c->clk);
        rt_clk_put(i2c->clk);
    }
    if (i2c->base)
    {
        rt_iounmap(i2c->base);
    }
    rt_free(i2c);
}

static rt_err_t sunxi_i2c_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_err_t err;
    const char *name;
    struct rt_device *dev = &pdev->parent;
    const struct sunxi_i2c_soc_data *soc_data = pdev->id->data;
    struct sunxi_i2c *i2c;

    if (!soc_data)
    {
        return -RT_EINVAL;
    }
    i2c = rt_calloc(1, sizeof(*i2c));
    if (!i2c)
    {
        return -RT_ENOMEM;
    }

    i2c->base = rt_dm_dev_iomap(dev, 0);
    if (!i2c->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    i2c->clear_irq = soc_data->clear_irq;
    i2c->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(i2c->clk))
    {
        err = rt_ptr_err(i2c->clk);
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(i2c->clk)))
    {
        goto _fail;
    }
    i2c->input_rate = rt_clk_get_rate(i2c->clk);

    i2c->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(i2c->reset))
    {
        err = rt_ptr_err(i2c->reset);
        goto _fail;
    }
    if (i2c->reset && (err = rt_reset_control_deassert(i2c->reset)))
    {
        goto _fail;
    }

    sunxi_i2c_write(i2c, SUNXI_TWI_SRST, RT_BIT(0));
    sunxi_i2c_write(i2c, SUNXI_TWI_CTL, SUNXI_TWI_CTL_BUSEN);
    if ((err = sunxi_i2c_set_bus_rate(i2c, I2C_MAX_STANDARD_MODE_FREQ)))
    {
        goto _fail;
    }

    id = rt_ofw_get_alias_id(dev->ofw_node, "i2c");
    if (id >= 0)
    {
        rt_dm_dev_set_name(&i2c->parent.parent, "i2c%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&i2c->parent.parent, "i2c");
    }
    name = rt_dm_dev_get_name(&i2c->parent.parent);

    i2c->parent.ops = &sunxi_i2c_ops;
    i2c->parent.parent.ofw_node = dev->ofw_node;
    dev->user_data = i2c;

    if ((err = rt_i2c_bus_device_register(&i2c->parent, name)))
    {
        goto _fail;
    }
    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2c);

    return RT_EOK;

_fail:
    sunxi_i2c_free(i2c);
    return err;
}

static rt_err_t sunxi_i2c_remove(struct rt_platform_device *pdev)
{
    struct sunxi_i2c *i2c = pdev->parent.user_data;

    rt_dm_dev_unbind_fwdata(&pdev->parent, RT_NULL);
    rt_device_unregister(&i2c->parent.parent);
    sunxi_i2c_free(i2c);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_i2c_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-i2c", .data = &sunxi_i2c_data },
    { .compatible = "allwinner,sun50i-h616-i2c", .data = &sunxi_i2c_h616_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_i2c_driver =
{
    .name = "sunxi-i2c",
    .ids = sunxi_i2c_ofw_ids,
    .probe = sunxi_i2c_probe,
    .remove = sunxi_i2c_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_i2c_driver);
