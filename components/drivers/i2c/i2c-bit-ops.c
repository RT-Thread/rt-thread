/*
 * File      : i2c-bit-ops.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-04-25     weety         first version
 */

#include <rtdevice.h>

#ifdef RT_I2C_BIT_DEBUG
#define bit_dbg(fmt, ...)   rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define bit_dbg(fmt, ...)
#endif

#define SET_SDA(ops, val)   ops->set_sda(ops->data, val)
#define SET_SCL(ops, val)   ops->set_scl(ops->data, val)
#define GET_SDA(ops)        ops->get_sda(ops->data)
#define GET_SCL(ops)        ops->get_scl(ops->data)

rt_inline void i2c_delay(struct rt_i2c_bit_ops *ops)
{
    ops->udelay((ops->delay_us + 1) >> 1);
}

rt_inline void i2c_delay2(struct rt_i2c_bit_ops *ops)
{
    ops->udelay(ops->delay_us);
}

#define SDA_L(ops)          SET_SDA(ops, 0)
#define SDA_H(ops)          SET_SDA(ops, 1)
#define SCL_L(ops)          SET_SCL(ops, 0)

/**
 * release scl line, and wait scl line to high.
 */
static rt_err_t SCL_H(struct rt_i2c_bit_ops *ops)
{
    rt_tick_t start;

    SET_SCL(ops, 1);

    if (!ops->get_scl)
        goto done;

    start = rt_tick_get();
    while (!GET_SCL(ops))
    {
        if ((rt_tick_get() - start) > ops->timeout)
            return -RT_ETIMEOUT;
        rt_thread_delay((ops->timeout + 1) >> 1);
    }
#ifdef RT_I2C_BIT_DEBUG
    if (rt_tick_get() != start)
    {
        bit_dbg("wait %ld tick for SCL line to go high\n",
                rt_tick_get() - start);
    }
#endif

done:
    i2c_delay(ops);

    return RT_EOK;
}

static void i2c_start(struct rt_i2c_bit_ops *ops)
{
#ifdef RT_I2C_BIT_DEBUG
    if (ops->get_scl && !GET_SCL(ops))
    {
        bit_dbg("I2C bus error, SCL line low\n");
    }
    if (ops->get_sda && !GET_SDA(ops))
    {
        bit_dbg("I2C bus error, SDA line low\n");
    }
#endif
    SDA_L(ops);
    i2c_delay(ops);
    SCL_L(ops);
}

static void i2c_restart(struct rt_i2c_bit_ops *ops)
{
    SDA_H(ops);
    SCL_H(ops);
    i2c_delay(ops);
    SDA_L(ops);
    i2c_delay(ops);
    SCL_L(ops);
}

static void i2c_stop(struct rt_i2c_bit_ops *ops)
{
    SDA_L(ops);
    i2c_delay(ops);
    SCL_H(ops);
    i2c_delay(ops);
    SDA_H(ops);
    i2c_delay2(ops);
}

rt_inline rt_bool_t i2c_waitack(struct rt_i2c_bit_ops *ops)
{
    rt_bool_t ack;

    SDA_H(ops);
    i2c_delay(ops);

    if (SCL_H(ops) < 0)
    {
        bit_dbg("wait ack timeout\n");

        return -RT_ETIMEOUT;
    }

    ack = !GET_SDA(ops);    /* ACK : SDA pin is pulled low */
    bit_dbg("%s\n", ack ? "ACK" : "NACK");

    SCL_L(ops);

    return ack;
}

static rt_int32_t i2c_writeb(struct rt_i2c_bus_device *bus, rt_uint8_t data)
{
    rt_int32_t i;
    rt_uint8_t bit;

    struct rt_i2c_bit_ops *ops = bus->priv;

    for (i = 7; i >= 0; i--)
    {
        SCL_L(ops);
        bit = (data >> i) & 1;
        SET_SDA(ops, bit);
        i2c_delay(ops);
        if (SCL_H(ops) < 0)
        {
            bit_dbg("i2c_writeb: 0x%02x, "
                    "wait scl pin high timeout at bit %d\n",
                    data, i);

            return -RT_ETIMEOUT;
        }
    }
    SCL_L(ops);
    i2c_delay(ops);

    return i2c_waitack(ops);
}

static rt_int32_t i2c_readb(struct rt_i2c_bus_device *bus)
{
    rt_uint8_t i;
    rt_uint8_t data = 0;
    struct rt_i2c_bit_ops *ops = bus->priv;

    SDA_H(ops);
    i2c_delay(ops);
    for (i = 0; i < 8; i++)
    {
        data <<= 1;

        if (SCL_H(ops) < 0)
        {
            bit_dbg("i2c_readb: wait scl pin high "
                    "timeout at bit %d\n", 7 - i);

            return -RT_ETIMEOUT;
        }

        if (GET_SDA(ops))
            data |= 1;
        SCL_L(ops);
        i2c_delay2(ops);
    }

    return data;
}

static rt_size_t i2c_send_bytes(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg        *msg)
{
    rt_int32_t ret;
    rt_size_t bytes = 0;
    const rt_uint8_t *ptr = msg->buf;
    rt_int32_t count = msg->len;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;

    while (count > 0)
    {
        ret = i2c_writeb(bus, *ptr);

        if ((ret > 0) || (ignore_nack && (ret == 0)))
        {
            count --;
            ptr ++;
            bytes ++;
        }
        else if (ret == 0)
        {
            i2c_dbg("send bytes: NACK.\n");

            return 0;
        }
        else
        {
            i2c_dbg("send bytes: error %d\n", ret);

            return ret;
        }
    }

    return bytes;
}

static rt_err_t i2c_send_ack_or_nack(struct rt_i2c_bus_device *bus, int ack)
{
    struct rt_i2c_bit_ops *ops = bus->priv;

    if (ack)
        SET_SDA(ops, 0);
    i2c_delay(ops);
    if (SCL_H(ops) < 0)
    {
        bit_dbg("ACK or NACK timeout\n");

        return -RT_ETIMEOUT;
    }
    SCL_L(ops);

    return RT_EOK;
}

static rt_size_t i2c_recv_bytes(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg        *msg)
{
    rt_int32_t val;
    rt_int32_t bytes = 0;   /* actual bytes */
    rt_uint8_t *ptr = msg->buf;
    rt_int32_t count = msg->len;
    const rt_uint32_t flags = msg->flags;

    while (count > 0)
    {
        val = i2c_readb(bus);
        if (val >= 0)
        {
            *ptr = val;
            bytes ++;
        }
        else
        {
            break;
        }

        ptr ++;
        count --;

        bit_dbg("recieve bytes: 0x%02x, %s\n",
                val, (flags & RT_I2C_NO_READ_ACK) ?
                "(No ACK/NACK)" : (count ? "ACK" : "NACK"));

        if (!(flags & RT_I2C_NO_READ_ACK))
        {
            val = i2c_send_ack_or_nack(bus, count);
            if (val < 0)
                return val;
        }
    }

    return bytes;
}

static rt_int32_t i2c_send_address(struct rt_i2c_bus_device *bus,
                                   rt_uint8_t                addr,
                                   rt_int32_t                retries)
{
    struct rt_i2c_bit_ops *ops = bus->priv;
    rt_int32_t i;
    rt_err_t ret = 0;

    for (i = 0; i <= retries; i++)
    {
        ret = i2c_writeb(bus, addr);
        if (ret == 1 || i == retries)
            break;
        bit_dbg("send stop condition\n");
        i2c_stop(ops);
        i2c_delay2(ops);
        bit_dbg("send start condition\n");
        i2c_start(ops);
    }

    return ret;
}

static rt_err_t i2c_bit_send_address(struct rt_i2c_bus_device *bus,
                                     struct rt_i2c_msg        *msg)
{
    rt_uint16_t flags = msg->flags;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
    struct rt_i2c_bit_ops *ops = bus->priv;

    rt_uint8_t addr1, addr2;
    rt_int32_t retries;
    rt_err_t ret;

    retries = ignore_nack ? 0 : bus->retries;

    if (flags & RT_I2C_ADDR_10BIT)
    {
        addr1 = 0xf0 | ((msg->addr >> 7) & 0x06);
        addr2 = msg->addr & 0xff;

        bit_dbg("addr1: %d, addr2: %d\n", addr1, addr2);

        ret = i2c_send_address(bus, addr1, retries);
        if ((ret != 1) && !ignore_nack)
        {
            bit_dbg("NACK: sending first addr\n");

            return -RT_EIO;
        }

        ret = i2c_writeb(bus, addr2);
        if ((ret != 1) && !ignore_nack)
        {
            bit_dbg("NACK: sending second addr\n");

            return -RT_EIO;
        }
        if (flags & RT_I2C_RD)
        {
            bit_dbg("send repeated start condition\n");
            i2c_restart(ops);
            addr1 |= 0x01;
            ret = i2c_send_address(bus, addr1, retries);
            if ((ret != 1) && !ignore_nack)
            {
                bit_dbg("NACK: sending repeated addr\n");

                return -RT_EIO;
            }
        }
    }
    else
    {
        /* 7-bit addr */
        addr1 = msg->addr << 1;
        if (flags & RT_I2C_RD)
            addr1 |= 1;
        ret = i2c_send_address(bus, addr1, retries);
        if ((ret != 1) && !ignore_nack)
            return -RT_EIO;
    }

    return RT_EOK;
}

static rt_size_t i2c_bit_xfer(struct rt_i2c_bus_device *bus,
                              struct rt_i2c_msg         msgs[],
                              rt_uint32_t               num)
{
    struct rt_i2c_msg *msg;
    struct rt_i2c_bit_ops *ops = bus->priv;
    rt_int32_t i, ret;
    rt_uint16_t ignore_nack;

    bit_dbg("send start condition\n");
    i2c_start(ops);
    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
        if (!(msg->flags & RT_I2C_NO_START))
        {
            if (i)
            {
                i2c_restart(ops);
            }
            ret = i2c_bit_send_address(bus, msg);
            if ((ret != RT_EOK) && !ignore_nack)
            {
                bit_dbg("receive NACK from device addr 0x%02x msg %d\n",
                        msgs[i].addr, i);
                goto out;
            }
        }
        if (msg->flags & RT_I2C_RD)
        {
            ret = i2c_recv_bytes(bus, msg);
            if (ret >= 1)
                bit_dbg("read %d byte%s\n", ret, ret == 1 ? "" : "s");
            if (ret < msg->len)
            {
                if (ret >= 0)
                    ret = -RT_EIO;
                goto out;
            }
        }
        else
        {
            ret = i2c_send_bytes(bus, msg);
            if (ret >= 1)
                bit_dbg("write %d byte%s\n", ret, ret == 1 ? "" : "s");
            if (ret < msg->len)
            {
                if (ret >= 0)
                    ret = -RT_ERROR;
                goto out;
            }
        }
    }
    ret = i;

out:
    bit_dbg("send stop condition\n");
    i2c_stop(ops);

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_bit_bus_ops =
{
    i2c_bit_xfer,
    RT_NULL,
    RT_NULL
};

rt_err_t rt_i2c_bit_add_bus(struct rt_i2c_bus_device *bus,
                            const char               *bus_name)
{
    bus->ops = &i2c_bit_bus_ops;

    return rt_i2c_bus_device_register(bus, bus_name);
}
