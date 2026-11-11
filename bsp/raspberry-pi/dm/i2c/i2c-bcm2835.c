/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "i2c.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include <drivers/dev_i2c_dm.h>

#define BCM2835_I2C_C           0x0
#define BCM2835_I2C_S           0x4
#define BCM2835_I2C_DLEN        0x8
#define BCM2835_I2C_A           0xc
#define BCM2835_I2C_FIFO        0x10
#define BCM2835_I2C_DIV         0x14
#define BCM2835_I2C_DEL         0x18
/*
 * 16-bit field for the number of SCL cycles to wait after rising SCL
 * before deciding the slave is not responding. 0 disables the
 * timeout detection.
 */
#define BCM2835_I2C_CLKT        0x1c

#define BCM2835_I2C_C_READ      RT_BIT(0)
#define BCM2835_I2C_C_CLEAR     RT_BIT(4) /* bits 4 and 5 both clear */
#define BCM2835_I2C_C_ST        RT_BIT(7)
#define BCM2835_I2C_C_INTD      RT_BIT(8)
#define BCM2835_I2C_C_INTT      RT_BIT(9)
#define BCM2835_I2C_C_INTR      RT_BIT(10)
#define BCM2835_I2C_C_I2CEN     RT_BIT(15)

#define BCM2835_I2C_S_TA        RT_BIT(0)
#define BCM2835_I2C_S_DONE      RT_BIT(1)
#define BCM2835_I2C_S_TXW       RT_BIT(2)
#define BCM2835_I2C_S_RXR       RT_BIT(3)
#define BCM2835_I2C_S_TXD       RT_BIT(4)
#define BCM2835_I2C_S_RXD       RT_BIT(5)
#define BCM2835_I2C_S_TXE       RT_BIT(6)
#define BCM2835_I2C_S_RXF       RT_BIT(7)
#define BCM2835_I2C_S_ERR       RT_BIT(8)
#define BCM2835_I2C_S_CLKT      RT_BIT(9)
#define BCM2835_I2C_S_LEN       RT_BIT(10) /* Fake bit for SW error reporting */

#define BCM2835_I2C_FEDL_SHIFT  16
#define BCM2835_I2C_REDL_SHIFT  0

#define BCM2835_I2C_CDIV_MIN    0x0002
#define BCM2835_I2C_CDIV_MAX    0xfffe

#define CLK_TOUT_MS             35

struct bcm2835_i2c
{
    struct rt_i2c_bus_device parent;

    void *regs;
    int irq;
    struct rt_clk *clk;

    struct rt_completion done;

    struct rt_i2c_msg *curr_msg;
    int num_msgs;
    rt_err_t msg_err;
    rt_uint8_t *msg_buf;
    rt_size_t msg_buf_remaining;
};

#define raw_to_bcm2835_i2c(raw) rt_container_of(raw, struct bcm2835_i2c, parent)

rt_inline void bcm2835_i2c_writel(struct bcm2835_i2c *i2c, int offset, rt_uint32_t val)
{
    HWREG32(i2c->regs + offset) = val;
}

rt_inline rt_uint32_t bcm2835_i2c_readl(struct bcm2835_i2c *i2c, int offset)
{
    return HWREG32(i2c->regs + offset);
}

static void bcm2835_fill_txfifo(struct bcm2835_i2c *i2c)
{
    while (i2c->msg_buf_remaining)
    {
        if (!(bcm2835_i2c_readl(i2c, BCM2835_I2C_S) & BCM2835_I2C_S_TXD))
        {
            break;
        }

        bcm2835_i2c_writel(i2c, BCM2835_I2C_FIFO, *i2c->msg_buf);

        ++i2c->msg_buf;
        --i2c->msg_buf_remaining;
    }
}

static void bcm2835_drain_rxfifo(struct bcm2835_i2c *i2c)
{
    while (i2c->msg_buf_remaining)
    {
        if (!(bcm2835_i2c_readl(i2c, BCM2835_I2C_S) & BCM2835_I2C_S_RXD))
        {
            break;
        }

        *i2c->msg_buf = bcm2835_i2c_readl(i2c, BCM2835_I2C_FIFO);

        ++i2c->msg_buf;
        --i2c->msg_buf_remaining;
    }
}

static void bcm2835_i2c_start_transfer(struct bcm2835_i2c *i2c)
{
    rt_uint32_t c;
    rt_bool_t last_msg;
    struct rt_i2c_msg *msg = i2c->curr_msg;

    if (!i2c->num_msgs)
    {
        return;
    }

    last_msg = (i2c->num_msgs == 1);
    c = BCM2835_I2C_C_ST | BCM2835_I2C_C_I2CEN;

    --i2c->num_msgs;
    i2c->msg_buf = msg->buf;
    i2c->msg_buf_remaining = msg->len;
    rt_hw_rmb();

    if (msg->flags & RT_I2C_RD)
    {
        c |= BCM2835_I2C_C_READ | BCM2835_I2C_C_INTR;
    }
    else
    {
        c |= BCM2835_I2C_C_INTT;
    }

    if (last_msg)
    {
        c |= BCM2835_I2C_C_INTD;
    }

    bcm2835_i2c_writel(i2c, BCM2835_I2C_A, msg->addr);
    bcm2835_i2c_writel(i2c, BCM2835_I2C_DLEN, msg->len);
    bcm2835_i2c_writel(i2c, BCM2835_I2C_C, c);
}

static void bcm2835_i2c_finish_transfer(struct bcm2835_i2c *i2c)
{
    i2c->curr_msg = RT_NULL;
    i2c->num_msgs = 0;

    i2c->msg_buf = RT_NULL;
    i2c->msg_buf_remaining = 0;
}

static rt_ssize_t bcm2835_i2c_master_xfer(struct rt_i2c_bus_device *bus,
        struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    rt_err_t err;
    rt_bool_t ignore_nak = RT_FALSE;
    struct bcm2835_i2c *i2c = raw_to_bcm2835_i2c(bus);

    for (int i = 0; i < num - 1; ++i)
    {
        if (msgs[i].flags & RT_I2C_RD)
        {
            return -RT_ENOSYS;
        }

        if (msgs[i].flags & RT_I2C_IGNORE_NACK)
        {
            ignore_nak = RT_TRUE;
        }
    }

    i2c->curr_msg = msgs;
    i2c->num_msgs = num;
    i2c->msg_err = 0;

    bcm2835_i2c_start_transfer(i2c);

    err = rt_completion_wait(&i2c->done, RT_TICK_PER_SECOND);

    bcm2835_i2c_finish_transfer(i2c);

    if (ignore_nak)
    {
        i2c->msg_err &= ~BCM2835_I2C_S_ERR;
    }

    if (err)
    {
        bcm2835_i2c_writel(i2c, BCM2835_I2C_C, BCM2835_I2C_C_CLEAR);

        return -RT_ETIMEOUT;
    }

    if (!i2c->msg_err)
    {
        return num;
    }

    if (i2c->msg_err & BCM2835_I2C_S_ERR)
    {
        LOG_E("Bus error");
    }

    return -RT_EIO;
}

const static struct rt_i2c_bus_device_ops bcm2835_i2c_ops =
{
    .master_xfer = bcm2835_i2c_master_xfer,
};

static void bcm2835_i2c_isr(int irqno, void *param)
{
    rt_uint32_t val, err;
    struct bcm2835_i2c *i2c = param;

    val = bcm2835_i2c_readl(i2c, BCM2835_I2C_S);

    err = val & (BCM2835_I2C_S_CLKT | BCM2835_I2C_S_ERR);
    if (err && !(val & BCM2835_I2C_S_TA))
    {
        i2c->msg_err = err;
    }

    if (val & BCM2835_I2C_S_DONE)
    {
        if (!i2c->curr_msg)
        {
            LOG_E("Got unexpected interrupt (from firmware?)");
        }
        else if (i2c->curr_msg->flags & RT_I2C_RD)
        {
            bcm2835_drain_rxfifo(i2c);
            val = bcm2835_i2c_readl(i2c, BCM2835_I2C_S);
        }

        if ((val & BCM2835_I2C_S_RXD) || i2c->msg_buf_remaining)
        {
            i2c->msg_err = BCM2835_I2C_S_LEN;
        }

        goto _complete;
    }

    if (val & BCM2835_I2C_S_TXW)
    {
        if (!i2c->msg_buf_remaining)
        {
            i2c->msg_err = val | BCM2835_I2C_S_LEN;
            goto _complete;
        }

        bcm2835_fill_txfifo(i2c);

        if (i2c->num_msgs && !i2c->msg_buf_remaining)
        {
            i2c->curr_msg++;
            bcm2835_i2c_start_transfer(i2c);
        }

        return;
    }

    if (val & BCM2835_I2C_S_RXR)
    {
        if (!i2c->msg_buf_remaining)
        {
            i2c->msg_err = val | BCM2835_I2C_S_LEN;
            goto _complete;
        }

        bcm2835_drain_rxfifo(i2c);
    }

    return;

_complete:
    bcm2835_i2c_writel(i2c, BCM2835_I2C_C, BCM2835_I2C_C_CLEAR);
    bcm2835_i2c_writel(i2c, BCM2835_I2C_S, BCM2835_I2C_S_CLKT |
            BCM2835_I2C_S_ERR | BCM2835_I2C_S_DONE);
    rt_completion_done(&i2c->done);
}

static int clk_bcm2835_i2c_calc_divider(rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_uint32_t divider = RT_DIV_ROUND_UP(parent_rate, rate);

    if (divider & 1)
    {
        ++divider;
    }

    if (divider < BCM2835_I2C_CDIV_MIN || divider > BCM2835_I2C_CDIV_MAX)
    {
        return -RT_EINVAL;
    }

    return divider;
}

static rt_err_t bcm2835_i2c_clk_set_rate(struct bcm2835_i2c *i2c, rt_ubase_t rate)
{
    rt_uint32_t redl, fedl, clk_tout, divider;

    divider = clk_bcm2835_i2c_calc_divider(rate, rt_clk_get_rate(i2c->clk));

    if ((rt_int32_t)divider < 0)
    {
        return (rt_err_t)divider;
    }

    bcm2835_i2c_writel(i2c, BCM2835_I2C_DIV, divider);

    /*
     * Number of core clocks to wait after falling edge before
     * outputting the next data bit.  Note that both FEDL and REDL
     * can't be greater than CDIV/2.
     */
    fedl = rt_max(divider / 16, 1U);

    /*
     * Number of core clocks to wait after rising edge before
     * sampling the next incoming data bit.
     */
    redl = rt_max(divider / 4, 1U);

    bcm2835_i2c_writel(i2c, BCM2835_I2C_DEL,
            (fedl << BCM2835_I2C_FEDL_SHIFT) | (redl << BCM2835_I2C_REDL_SHIFT));

    /* Set the clock stretch timeout. */
    if (rate > 0xffff * 1000 / CLK_TOUT_MS)
    {
        clk_tout = 0xffff;
    }
    else
    {
        clk_tout = CLK_TOUT_MS * rate / 1000;
    }

    bcm2835_i2c_writel(i2c, BCM2835_I2C_CLKT, clk_tout);

    return RT_EOK;
}

static void bcm2835_i2c_free(struct bcm2835_i2c *i2c)
{
    if (i2c->regs)
    {
        rt_iounmap(i2c->regs);
    }

    if (!rt_is_err_or_null(i2c->clk))
    {
        rt_clk_disable_unprepare(i2c->clk);
        rt_clk_put(i2c->clk);
    }

    rt_free(i2c);
}

static rt_err_t bcm2835_i2c_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    rt_uint32_t bus_clk_rate;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_i2c *i2c = rt_calloc(1, sizeof(*i2c));

    if (!i2c)
    {
        return -RT_ENOMEM;
    }

    i2c->regs = rt_dm_dev_iomap(dev, 0);

    if (!i2c->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    i2c->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(i2c->clk))
    {
        err = rt_ptr_err(i2c->clk);
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "clock-frequency", &bus_clk_rate))
    {
        bus_clk_rate = I2C_MAX_STANDARD_MODE_FREQ;
    }

    if ((err = bcm2835_i2c_clk_set_rate(i2c, bus_clk_rate)))
    {
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(i2c->clk)))
    {
        goto _fail;
    }

    i2c->irq = rt_dm_dev_get_irq(dev, 0);

    if (i2c->irq < 0)
    {
        err = i2c->irq;
        goto _fail;
    }

    /*
     * Disable the hardware clock stretching timeout. SMBUS
     * specifies a limit for how long the device can stretch the
     * clock, but core I2C doesn't.
     */
    bcm2835_i2c_writel(i2c, BCM2835_I2C_CLKT, 0);
    bcm2835_i2c_writel(i2c, BCM2835_I2C_C, 0);

    rt_completion_init(&i2c->done);

    rt_dm_dev_set_name_auto(&i2c->parent.parent, "i2c");
    dev_name = rt_dm_dev_get_name(&i2c->parent.parent);

    rt_hw_interrupt_install(i2c->irq, bcm2835_i2c_isr, i2c, dev_name);
    rt_hw_interrupt_umask(i2c->irq);

    dev->user_data = i2c;

    i2c->parent.ops = &bcm2835_i2c_ops;
    i2c->parent.parent.ofw_node = dev->ofw_node;

    if ((err = rt_i2c_bus_device_register(&i2c->parent, dev_name)))
    {
        goto _free_irq;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2c);

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(i2c->irq);
    rt_pic_detach_irq(i2c->irq, i2c);

_fail:
    bcm2835_i2c_free(i2c);

    return err;
}

static rt_err_t bcm2835_i2c_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_i2c *i2c = pdev->parent.user_data;

    rt_hw_interrupt_mask(i2c->irq);
    rt_pic_detach_irq(i2c->irq, i2c);

    rt_device_unregister(&i2c->parent.parent);

    bcm2835_i2c_free(i2c);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835_i2c_ofw_ids[] =
{
    { .compatible = "brcm,bcm2711-i2c" },
    { .compatible = "brcm,bcm2835-i2c" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_i2c_driver =
{
    .name = "bcm2835-i2c",
    .ids = bcm2835_i2c_ofw_ids,

    .probe = bcm2835_i2c_probe,
    .remove = bcm2835_i2c_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_i2c_driver);
