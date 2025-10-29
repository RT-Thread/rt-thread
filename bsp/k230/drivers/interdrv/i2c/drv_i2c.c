/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <riscv_io.h>
#include <ioremap.h>
#include "board.h"
#include "drv_i2c.h"
#include "sysctl_clk.h"

#undef DBG_TAG
#undef DBG_LVL
#define DBG_TAG     "drv_i2c"
#define DBG_LVL     DBG_INFO
#include <rtdbg.h>

struct _i2c_speed_cfg
{
    rt_uint16_t hcnt;
    rt_uint16_t lcnt;
    rt_uint16_t spklen;
};

struct k230_i2c_dev
{
    struct rt_i2c_bus_device dev;
    const char *name;
    rt_ubase_t base;
    size_t size;
    int vector;
    rt_uint32_t clock;
    struct rt_i2c_msg *msg;
    struct _i2c_speed_cfg speed_cfg;
};

static rt_size_t k230_i2c_get_timer(rt_size_t base)
{
    return rt_tick_get() - base ;
}

static void k230_i2c_enable(struct k230_i2c_dev *dev, rt_bool_t enable)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_uint32_t en_value = enable ? 1 : 0;
    int timeout = 100;

    do
    {
        i2c->enable.enable = en_value;
        if(i2c->enable_status.en == en_value)
        {
            return;
        }

        /*
         * Wait 10 times the signaling period of the highest I2C
         * transfer supported by the driver (for 400KHz this is
         * 25us) as described in the DesignWare I2C databook.
         */
        rt_hw_us_delay(25);
    }while(timeout--);

    LOG_E("timeout in %s i2c\n", enable ? "enable" : "disable");
}

static void k230_i2c_set_bus_timeout(struct k230_i2c_dev *dev, rt_uint32_t timeout)
{
    float tick = 0;

    tick = RT_TICK_PER_SECOND / 1000.0f; /* ms to tick */
    dev->dev.timeout = (rt_uint32_t)(timeout * tick);
}

static int k230_i2c_set_bus_speed(struct k230_i2c_dev *dev, rt_uint32_t speed)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_uint32_t i2c_spd, period, spklen, ft;

    /*
     * Calculate clock counts for I2C speed
     * hcnt + lcnt + spklen + 7 + 1 + fall_time * clk = clk / speed
     * fall_time = 10ns
     * spklen = 0~50ns
     */

    spklen = dev->clock * 10 / 1e9;
    ft = dev->clock * 10 / 1e9;
    period = dev->clock / speed;
    period = period - spklen - 7 - 1 - ft;
    dev->speed_cfg.lcnt = period / 2;
    dev->speed_cfg.hcnt = period - dev->speed_cfg.lcnt;
    dev->speed_cfg.spklen = spklen;

    if(speed <= I2C_STANDARD_SPEED_UP)
    {
        i2c_spd = I2C_SPEED_MODE_STANDARD;
    }
    else if(speed <= I2C_FAST_SPEED_UP)
    {
        i2c_spd = I2C_SPEED_MODE_FAST;
    }
    else if(speed <= I2C_MAX_SPEED_UP)
    {
        i2c_spd = I2C_SPEED_MODE_MAX;
    }
    else
    {
        return -RT_EINVAL;
    }

    /* to set speed cltr must be disabled */
    k230_i2c_enable(dev, RT_FALSE);

    switch(i2c_spd)
    {
        case I2C_SPEED_MODE_STANDARD:
            i2c->ss_ufm_scl_hcnt.cnt = dev->speed_cfg.hcnt;
            i2c->ss_ufm_scl_lcnt.cnt = dev->speed_cfg.lcnt;
            i2c->fs_ufm_spklen.spklen = dev->speed_cfg.spklen;
            break;

        case I2C_SPEED_MODE_FAST:
            i2c->fs_scl_hcnt_ufm_tbuf_cnt.cnt = dev->speed_cfg.hcnt;
            i2c->fs_scl_lcnt.cnt = dev->speed_cfg.lcnt;
            i2c->fs_ufm_spklen.spklen = dev->speed_cfg.spklen;
            break;

        case I2C_SPEED_MODE_MAX:
            i2c->hs_scl_hcnt.cnt = dev->speed_cfg.hcnt;
            i2c->hs_scl_lcnt.cnt = dev->speed_cfg.lcnt;
            i2c->hs_spklen.spklen = dev->speed_cfg.spklen;
            break;

        default: break;
    }

    i2c->con.speed = i2c_spd;

    /* Enable back i2c now speed set */
    k230_i2c_enable(dev, RT_TRUE);

    return RT_EOK;
}

static void k230_i2c_set_addr(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_uint16_t i2c_addr = dev->msg->addr;

    /* Disable i2c */
    k230_i2c_enable(dev, RT_FALSE);

    if(dev->msg->flags & RT_I2C_ADDR_10BIT || dev->dev.flags & RT_I2C_ADDR_10BIT)
    {
        i2c->tar.master_10bit_addr = 1;
        i2c_addr &= 0x3FF;
    }
    else
    {
        i2c->tar.master_10bit_addr = 0;
        i2c_addr &= 0x7F;
    }

    i2c->tar.tar = i2c_addr;

    /* Enable i2c */
    k230_i2c_enable(dev, RT_TRUE);
}

static void k230_i2c_flush_rxfifo(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;

    while(i2c->status.rfne)
    {
        readl(&i2c->data_cmd);
    }
}

static int k230_i2c_wait_for_bus_busy(struct k230_i2c_dev *dev)
{
    rt_size_t start_time = k230_i2c_get_timer(0);
    volatile i2c_t *i2c = (i2c_t *)dev->base;

    while((i2c->status.mst_activity) || !(i2c->status.tfe))
    {
        /* Evaluate timeout */
        if(k230_i2c_get_timer(start_time) > (rt_size_t)dev->dev.timeout * I2C_TX_FIFO_SIZE)
        {
            return -RT_ETIMEOUT;
        }
    }

    return RT_EOK;
}

static int k230_i2c_xfer_init(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_uint8_t addr = 0;

    if(k230_i2c_wait_for_bus_busy(dev) != RT_EOK)
    {
        return -RT_EBUSY;
    }

    k230_i2c_set_addr(dev);

    return RT_EOK;
}

static int k230_i2c_xfer_finish(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_uint32_t start_stop_det = k230_i2c_get_timer(0);

    while (1)
    {
        if(i2c->raw_intr_stat.stop_det)
        {
            readl(&i2c->clr_stop_det);
            break;
        }

        else if (k230_i2c_get_timer(start_stop_det) > dev->dev.timeout)
        {
            break;
        }
    }

    if (k230_i2c_wait_for_bus_busy(dev) != RT_EOK)
    {
        return -RT_EBUSY;
    }

    k230_i2c_flush_rxfifo(dev);

    return RT_EOK;
}

static int _k230_i2c_read(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_size_t start_time_rx = 0;
    rt_uint32_t recv_len = dev->msg->len;
    rt_uint32_t tran_len = dev->msg->len;
    rt_uint8_t *buffer = dev->msg->buf;
    rt_uint32_t cmd = 0;

    /* If no start condition is sent before reading, then send a repeated start. */
    if(dev->msg->flags & RT_I2C_NO_START)
    {
        cmd |= I2C_DATA_CMD_RESTART;
    }
    else
    {
        if(k230_i2c_xfer_init(dev) != RT_EOK)
        {
            return -RT_EBUSY;
        }
    }

    start_time_rx = k230_i2c_get_timer(0);
    while(recv_len || tran_len)
    {
        if (tran_len)
        {
            while(i2c->status.tfnf == 0);
            /* Write stop when the last byte */
            cmd = tran_len == 1 ? cmd | I2C_DATA_CMD_STOP : cmd;
            /* Write to data cmd register to trigger i2c */
            writel(cmd | I2C_DATA_CMD_READ, &i2c->data_cmd);
            cmd = 0;
            tran_len--;
        }

        if(i2c->status.rfne)
        {
            *buffer++ = i2c->data_cmd.dat;
            recv_len--;
            start_time_rx = k230_i2c_get_timer(0);
        }
        else if(k230_i2c_get_timer(start_time_rx) > dev->dev.timeout)
        {
            return -RT_ETIMEOUT;
        }
    }
    return k230_i2c_xfer_finish(dev);
}

static int _k230_i2c_write(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;
    rt_size_t start_time_tx = 0;
    rt_uint32_t tran_len = dev->msg->len;
    rt_uint8_t *buffer = dev->msg->buf;
    rt_uint32_t cmd = 0;
    rt_uint32_t cut = 0;

    if (k230_i2c_xfer_init(dev) != RT_EOK)
    {
        return -RT_EBUSY;
    }

    start_time_tx = k230_i2c_get_timer(0);
    while(tran_len)
    {
        if(i2c->status.tfnf)
        {
            /* If there is no stop flag, the stop condition will not be sent at the last byte. */
            if(tran_len == 1 && !(dev->msg->flags & RT_I2C_NO_STOP))
            {
                cmd |= I2C_DATA_CMD_STOP;
            }
            else
            {
                cmd &= ~I2C_DATA_CMD_STOP;
            }
            cmd |= *buffer++;
            writel(cmd, &i2c->data_cmd);
            cmd = 0;
            tran_len--;
            start_time_tx = k230_i2c_get_timer(0);
        }
        else if(k230_i2c_get_timer(start_time_tx) > dev->dev.timeout)
        {
            return -RT_ETIMEOUT;
        }
    }

    if (dev->msg->flags & RT_I2C_NO_STOP)
    {
        return RT_EOK;
    }

    if (k230_i2c_wait_for_bus_busy(dev) != RT_EOK)
    {
        return -RT_EBUSY;
    }

    return RT_EOK;
}

static rt_ssize_t k230_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct k230_i2c_dev *i2c_dev = rt_container_of(bus, struct k230_i2c_dev, dev);
    volatile i2c_t *i2c = (i2c_t *)i2c_dev->base;
    int ret;
    rt_ssize_t send_mesgs = num;

    for (; num > 0; num--, msgs++)
    {
        i2c_dev->msg = msgs;

        if(msgs->flags & RT_I2C_RD)
        {
            ret = _k230_i2c_read(i2c_dev);
        }
        else
        {
            ret = _k230_i2c_write(i2c_dev);
        }
        if (ret != RT_EOK)
        {
            return -RT_EIO;
        }
    }

    return send_mesgs;
}

static rt_err_t k230_i2c_control(struct rt_i2c_bus_device *bus, int cmd, void *args)
{
    struct k230_i2c_dev *i2c_dev = rt_container_of(bus, struct k230_i2c_dev, dev);
    rt_uint32_t arg = *(rt_uint32_t *)args;
    rt_err_t ret;

    RT_ASSERT(bus != RT_NULL);

    switch (cmd)
    {
        /* set 10-bit addr mode */
        case RT_I2C_DEV_CTRL_10BIT:
            if(arg & RT_I2C_ADDR_10BIT)
            {
                i2c_dev->dev.flags |= RT_I2C_ADDR_10BIT;
            }
            else
            {
                i2c_dev->dev.flags &= ~RT_I2C_ADDR_10BIT;
            }
            break;

        case RT_I2C_DEV_CTRL_TIMEOUT:
            k230_i2c_set_bus_timeout(i2c_dev, arg);
            break;

        case RT_I2C_DEV_CTRL_CLK:
            ret = k230_i2c_set_bus_speed(i2c_dev, arg);
            if (ret != RT_EOK)
            {
                return -RT_EIO;
            }
            break;

        default: break;
    }

    return RT_EOK;
}

static void k230_i2c_master_init(struct k230_i2c_dev *dev)
{
    volatile i2c_t *i2c = (i2c_t *)dev->base;

    /* Disable i2c */
    k230_i2c_enable(dev, RT_FALSE);

    i2c->con.slave_disable = 1;
    i2c->con.restart_en = 1;
    i2c->con.master_mode = 1;
    i2c->tx_tl.tl = I2C_TX_TL;
    i2c->rx_tl.tl = I2C_RX_TL;
    i2c->intr_mask.m_stop_det = 1;

    /* Enable i2c */
    k230_i2c_enable(dev, RT_TRUE);
}

static const struct rt_i2c_bus_device_ops k230_i2c_ops =
{
    .master_xfer = k230_i2c_xfer,
    .i2c_bus_control = k230_i2c_control,
};

static struct k230_i2c_dev k230_i2c_devs[] =
{
#ifdef BSP_USING_I2C0
    {
        .name = "i2c0",
        .base = I2C0_BASE_ADDR,
        .size = I2C0_IO_SIZE,
        .vector = K230_IRQ_I2C0,
    },
#endif
#ifdef BSP_USING_I2C1
    {
        .name = "i2c1",
        .base = I2C1_BASE_ADDR,
        .size = I2C1_IO_SIZE,
        .vector = K230_IRQ_I2C1,
    },
#endif
#ifdef BSP_USING_I2C2
    {
        .name = "i2c2",
        .base = I2C2_BASE_ADDR,
        .size = I2C2_IO_SIZE,
        .vector = K230_IRQ_I2C2,
    },
#endif
#ifdef BSP_USING_I2C3
    {
        .name = "i2c3",
        .base = I2C3_BASE_ADDR,
        .size = I2C3_IO_SIZE,
        .vector = K230_IRQ_I2C3,
    },
#endif
#ifdef BSP_USING_I2C4
    {
        .name = "i2c4",
        .base = I2C4_BASE_ADDR,
        .size = I2C4_IO_SIZE,
        .vector = K230_IRQ_I2C4,
    },
#endif
};

int rt_hw_i2c_init(void)
{
    int i;

    for (i = 0; i < sizeof(k230_i2c_devs) / sizeof(k230_i2c_devs[0]); i++)
    {
        k230_i2c_devs[i].base = (rt_ubase_t)rt_ioremap((void *)k230_i2c_devs[i].base, k230_i2c_devs[i].size);
        k230_i2c_devs[i].dev.ops = &k230_i2c_ops;
        k230_i2c_devs[i].clock = sysctl_clk_get_leaf_freq(SYSCTL_CLK_I2C0_CORE + i);

        k230_i2c_master_init(&k230_i2c_devs[i]);
        k230_i2c_set_bus_timeout(&k230_i2c_devs[i], I2C_DEFAULT_TIMEOUT);
        k230_i2c_set_bus_speed(&k230_i2c_devs[i], I2C_DEFAULT_SPEED);
        rt_i2c_bus_device_register(&k230_i2c_devs[i].dev, k230_i2c_devs[i].name);
        LOG_I("i2c%d master mode, i2c%d clock=%dHz\n", i, i, k230_i2c_devs[i].clock);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);
