/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-07-15     sp-cai        first version
 */

#include <rtdevice.h>
#include <rthw.h>

#ifdef RT_USING_SOFT_I2C

#define DBG_ENABLE
#define DBG_TAG                         "I2C_S"
#ifdef RT_USING_SOFT_I2C_DEBUG
    #define DBG_LEVEL                   DBG_LOG
    #define I2C_DEBUG_LOG(log, ...)     log(##__VA_ARGS__)
#else
    #define I2C_DEBUG_LOG(...)
#endif
#include <rtdbg.h>

struct soft_i2c_config
{
    rt_base_t       scl_pin;
    rt_base_t       sda_pin;
    const char      *bus_name;
    rt_uint16_t     timing_delay;   /* scl and sda line delay */
    rt_uint16_t     timing_timeout; /* in tick */
};

const struct soft_i2c_config i2c_cfg[] =
{
    #ifdef RT_USING_SOFT_I2C5
    {
        .scl_pin        = RT_SOFT_I2C5_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C5_SDA_PIN,
        .bus_name       = RT_SOFT_I2C5_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C5_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C5_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C5
    #ifdef RT_USING_SOFT_I2C6
    {
        .scl_pin        = RT_SOFT_I2C6_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C6_SDA_PIN,
        .bus_name       = RT_SOFT_I2C6_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C6_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C6_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C6
    #ifdef RT_USING_SOFT_I2C7
    {
        .scl_pin        = RT_SOFT_I2C7_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C7_SDA_PIN,
        .bus_name       = RT_SOFT_I2C7_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C7_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C7_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C7
    #ifdef RT_USING_SOFT_I2C8
    {
        .scl_pin        = RT_SOFT_I2C8_SCL_PIN,
        .sda_pin        = RT_SOFT_I2C8_SDA_PIN,
        .bus_name       = RT_SOFT_I2C8_BUS_NAME,
        .timing_delay   = RT_SOFT_I2C8_TIMING_DELAY,
        .timing_timeout = RT_SOFT_I2C8_TIMING_TIMEOUT,
    },
    #endif  //RT_USING_SOFT_I2C8
};

struct soft_i2c
{
    struct rt_i2c_bus_device i2c_bus;
    const struct soft_i2c_config *cfg;
    #ifdef RT_I2C_DETAIL
    rt_ubase_t state;                   /* I2C communication state */
    rt_err_t error;                     /* I2C Error code */
    #endif  //RT_I2C_DETAIL
};

static struct soft_i2c i2c_bus_obj[sizeof(i2c_cfg) / sizeof(i2c_cfg[0])] =
{ 0 };

#ifdef RT_I2C_DETAIL
    #define SET_STATE(obj,X)        (obj)->state |= (X)
    #define SET_ERROR(obj,X)        (obj)->error = (X)
#else
    #define SET_STATE(obj,X)        //RT_UNUSED((X))
    #define SET_ERROR(obj,X)        //RT_UNUSED((X))
#endif  //RT_I2C_DETAIL

#define SET_SDA(cfg, val)   rt_pin_write((cfg)->sda_pin, val)
#define SET_SCL(cfg, val)   rt_pin_write((cfg)->scl_pin, val)
#define GET_SDA(cfg)        rt_pin_read((cfg)->sda_pin)
#define GET_SCL(cfg)        rt_pin_read((cfg)->scl_pin)

rt_inline void i2c_delay(const struct soft_i2c_config *cfg)
{
    rt_hw_us_delay((cfg->timing_delay + 1) >> 1);
}

#define SDA_L(cfg)              SET_SDA(cfg, PIN_LOW)
#define SDA_H(cfg)              SET_SDA(cfg, PIN_HIGH)
#define SCL_L(cfg)              SET_SCL(cfg, PIN_LOW)

/**
 * release scl line, and wait scl line to high.
 */
static rt_err_t SCL_H(const struct soft_i2c_config *cfg)
{
    rt_tick_t start;

    SET_SCL(cfg, PIN_HIGH);

    if(GET_SCL(cfg) == PIN_HIGH)
        return RT_EOK;

    start = rt_tick_get();
    while(GET_SCL(cfg) == PIN_LOW)
    {
        if((rt_tick_get() - start) > cfg->timing_timeout)
            return -RT_ETIMEOUT;
    }

    I2C_DEBUG_LOG(LOG_I, "%s SCL to high takes %ld tick"
                  , cfg->bus_name
                  , rt_tick_get() - start
                 );

    return RT_EOK;
}

static rt_err_t _i2c_start(struct rt_i2c_bus_device *bus
#ifdef RT_I2C_DETAIL
    , rt_i2c_state_t state
#endif  //RT_I2C_DETAIL
                          )
{
    rt_err_t ret;
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    #ifdef RT_I2C_DETAIL
    SET_STATE(obj, state);
    I2C_DEBUG_LOG(LOG_D, "%s send %sstart condition"
                  , rt_i2c_bus_name(bus)
                  , (state == RT_I2C_STATE_RESTART) ? "re" : ""
                 );
    #else
    I2C_DEBUG_LOG(LOG_D, "%s send start condition", rt_i2c_bus_name(bus));
    #endif  //RT_I2C_DETAIL
    SDA_H(cfg);
    if(GET_SCL(cfg) == PIN_LOW)
    {
        ret = SCL_H(cfg);
        if(ret < 0)
        {
            LOG_E("%s start error: SCL low", rt_i2c_bus_name(bus));
            SET_ERROR(obj, ret);
            return ret;
        }
        i2c_delay(cfg);
    }
    if(GET_SDA(cfg) == PIN_LOW)
    {
        LOG_E("%s start error: SDA low", rt_i2c_bus_name(bus));
        SET_ERROR(obj, -RT_EIO);
        return -RT_EIO;
    }
    SDA_L(cfg);
    i2c_delay(cfg);
    SCL_L(cfg);
    return RT_EOK;
}
#ifdef RT_I2C_DETAIL
    #define i2c_start(bus) _i2c_start(bus, RT_I2C_STATE_START)
    #define i2c_restart(bus) _i2c_start(bus, RT_I2C_STATE_RESTART)
#else
    #define i2c_start(bus) _i2c_start(bus)
    #define i2c_restart(bus) _i2c_start(bus)
#endif  //RT_I2C_DETAIL

static rt_err_t i2c_stop(struct rt_i2c_bus_device *bus)
{
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    SET_STATE(obj, RT_I2C_STATE_BUSY | RT_I2C_STATE_STOP);
    I2C_DEBUG_LOG(LOG_D, "%s send stop condition", rt_i2c_bus_name(bus));
    SDA_L(cfg);
    i2c_delay(cfg);
    #ifdef RT_USING_SOFT_I2C_SIMPLE
    SCL_H(cfg);
    #else
    {
        rt_err_t ret;
        ret = SCL_H(cfg);
        if(ret < 0)
        {
            LOG_E("%s stop error: SCL low", rt_i2c_bus_name(bus));
            SET_ERROR(obj, ret);
            return ret;
        }
    }
    #endif // RT_USING_SOFT_I2C_SIMPLE
    i2c_delay(cfg);
    SDA_H(cfg);
    i2c_delay(cfg);
    i2c_delay(cfg);
    if(GET_SDA(cfg) == PIN_LOW)
    {
        LOG_E("%s stop error: SDA low", rt_i2c_bus_name(bus));
        SET_ERROR(obj, -RT_EIO);
        return -RT_EIO;
    }
    #ifdef RT_I2C_DETAIL
    obj->state &= RT_I2C_STATE_READY;
    #endif  //RT_I2C_DETAIL
    SET_ERROR(obj, RT_EOK);
    return RT_EOK;
}

/**
* if i2c is locked, this function will unlock it
*
* @param config class
*
* @return RT_EOK indicates successful unlock.
*/
static rt_err_t i2c_bus_unlock(struct rt_i2c_bus_device *bus)
{
    rt_err_t ret;
    rt_int32_t i = 0;
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    SET_STATE(obj, RT_I2C_STATE_BUSY | RT_I2C_STATE_UNLOCK);

    SDA_H(cfg);
    if(GET_SCL(cfg) == PIN_LOW)
    {
        ret = SCL_H(cfg);
        if(ret < 0)
            goto _SCL_low;
        i2c_delay(cfg);
    }
    if(PIN_LOW == GET_SDA(cfg))
    {
        LOG_I("%s bus unlock", rt_i2c_bus_name(bus));
        SCL_L(cfg);
        while(i++ < 9)
        {
            #ifdef RT_USING_SOFT_I2C_SIMPLE
            i2c_delay(cfg);
            SCL_H(cfg);
            i2c_delay(cfg);
            SCL_L(cfg);
            #else
            i2c_delay(cfg);
            ret = SCL_H(cfg);
            if(ret < 0)
                goto _SCL_low;
            i2c_delay(cfg);
            SCL_L(cfg);
            if(PIN_HIGH == GET_SDA(cfg))
                break;
            #endif // RT_USING_SOFT_I2C_SIMPLE
        }
        ret = i2c_stop(bus);
        if(RT_EOK != ret)
            return ret;
        I2C_DEBUG_LOG(LOG_D, "%s bus unlock success", rt_i2c_bus_name(bus));
    }
    else
        I2C_DEBUG_LOG(LOG_I, "%s bus not lock", rt_i2c_bus_name(bus));

    return RT_EOK;

_SCL_low:
    LOG_E("%s unlock error: SCL low", rt_i2c_bus_name(bus));
    SET_ERROR(obj, ret);
    return ret;
}

rt_inline rt_bool_t i2c_waitack(struct rt_i2c_bus_device *bus)
{
    rt_bool_t ack;
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    #ifdef RT_USING_SOFT_I2C_SIMPLE
    SDA_H(cfg);
    i2c_delay(cfg);
    SCL_H(cfg);
    #else
    SCL_L(cfg);
    SDA_H(cfg);
    i2c_delay(cfg);

    {
        rt_err_t ret;
        ret = SCL_H(cfg);
        if(ret < 0)
        {
            LOG_W("%s wait ACK: %s", rt_i2c_bus_name(bus), rt_strerror(ret));
            SET_ERROR(obj, ret);
            return ret;
        }
    }
    #endif // RT_USING_SOFT_I2C_SIMPLE
    i2c_delay(cfg);

    ack = (GET_SDA(cfg) == PIN_LOW);    /* ACK : SDA pin is pulled low */
    I2C_DEBUG_LOG(LOG_D, "%s: %s", rt_i2c_bus_name(bus), ack ? "ACK" : "NACK");

    SCL_L(cfg);

    return ack;
}

rt_inline rt_err_t i2c_send_ack(struct rt_i2c_bus_device *bus, rt_bool_t ack)
{
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    #ifdef RT_USING_SOFT_I2C_SIMPLE
    if(ack)
        SDA_L(cfg);
    else
        SDA_H(cfg);
    i2c_delay(cfg);
    SCL_H(cfg);
    #else
    SCL_L(cfg);
    if(ack)
        SDA_L(cfg);
    else
        SDA_H(cfg);
    i2c_delay(cfg);
    if(0 == ack && GET_SDA(cfg) == PIN_LOW)
    {
        LOG_W("%s SDA low at send ACK", rt_i2c_bus_name(bus));
        SET_ERROR(obj, -RT_EIO);
        return -RT_EIO;
    }
    {
        rt_err_t ret;
        ret = SCL_H(cfg);
        if(ret < 0)
        {
            LOG_E("%s send %s: %s",
                  rt_i2c_bus_name(bus), ack ? "ACK" : "NACK",
                  rt_strerror(ret));
            SET_ERROR(obj, ret);
            return ret;
        }
    }
    #endif // RT_USING_SOFT_I2C_SIMPLE
    i2c_delay(cfg);
    SCL_L(cfg);

    return RT_EOK;
}

static rt_int32_t i2c_writeb(struct rt_i2c_bus_device *bus, rt_uint8_t data)
{
    rt_uint8_t bit;
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    #ifdef RT_USING_SOFT_I2C_SIMPLE
    for(rt_int8_t i = 7; i >= 0; i--)
    {
        bit = (data >> i) & 1;
        if(bit)
            SDA_H(cfg);
        else
            SDA_L(cfg);
        i2c_delay(cfg);
        SCL_H(cfg);
        i2c_delay(cfg);
        SCL_L(cfg);
    }
    #else
    for(rt_int8_t i = 7; i >= 0; i--)
    {
        rt_err_t ret;

        SCL_L(cfg);
        bit = (data >> i) & 1;
        if(bit)
            SDA_H(cfg);
        else
            SDA_L(cfg);
        i2c_delay(cfg);
        if(bit > 0 && GET_SDA(cfg) == PIN_LOW)
        {
            LOG_W("%s SDA low at writing: 0x%02X, bit%d",
                  rt_i2c_bus_name(bus), data, i);
            SET_ERROR(obj, -RT_EIO);
            return -RT_EIO;
        }
        ret = SCL_H(cfg);
        if(ret < 0)
        {
            LOG_W("%s SCL low at writing: 0x%02X, bit%d",
                  rt_i2c_bus_name(bus), data, i);
            SET_ERROR(obj, ret);
            return ret;
        }
        i2c_delay(cfg);
    }
    SCL_L(cfg);
    #endif // RT_USING_SOFT_I2C_SIMPLE

    return i2c_waitack(bus);
}

static rt_int32_t i2c_readb(struct rt_i2c_bus_device *bus)
{
    rt_uint8_t data = 0;
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    const struct soft_i2c_config *cfg = obj->cfg;

    #ifdef RT_USING_SOFT_I2C_SIMPLE
    SDA_H(cfg);
    for(rt_uint8_t i = 0; i < 8; i++)
    {
        data <<= 1;
        i2c_delay(cfg);

        SCL_H(cfg);
        i2c_delay(cfg);

        if(GET_SDA(cfg))
            data |= 1;
        SCL_L(cfg);
    }
    #else
    SCL_L(cfg);
    SDA_H(cfg);
    for(rt_uint8_t i = 0; i < 8; i++)
    {
        rt_err_t ret;

        data <<= 1;
        i2c_delay(cfg);

        ret = SCL_H(cfg);
        if(ret < 0)
        {
            LOG_W("%s SCL low at Reading: bit%d", rt_i2c_bus_name(bus), 7 - i);
            SET_ERROR(obj, ret);
            return ret;
        }
        i2c_delay(cfg);

        if(GET_SDA(cfg))
            data |= 1;
        SCL_L(cfg);
    }
    #endif // RT_USING_SOFT_I2C_SIMPLE

    return data;
}

static rt_ssize_t i2c_send_bytes(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg        *msg)
{
    rt_int32_t ret;
    rt_size_t bytes = 0;
    const rt_uint8_t *ptr = msg->buf;
    rt_int32_t count = msg->len;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;

    SET_STATE((struct soft_i2c *)bus, RT_I2C_STATE_BUSY | RT_I2C_STATE_TX);

    while(count > 0)
    {
        ret = i2c_writeb(bus, *ptr);

        if((ret > 0) || ((ignore_nack > 0) && (ret == 0)))
        {
            count --;
            ptr ++;
            bytes ++;
        }
        else if(ret == 0)
        {
            LOG_W("%s send bytes: NACK", rt_i2c_bus_name(bus));
            return 0;
        }
        else
        {
            LOG_E("%s send bytes error: %s",
                  rt_i2c_bus_name(bus), rt_strerror(ret));
            return ret;
        }
    }

    return bytes;
}

static rt_ssize_t i2c_recv_bytes(struct rt_i2c_bus_device *bus,
                                 struct rt_i2c_msg        *msg)
{
    rt_int32_t val;
    rt_int32_t bytes = 0;   /* actual bytes */
    rt_uint8_t *ptr = msg->buf;
    rt_int32_t count = msg->len;
    const rt_uint32_t flags = msg->flags;

    SET_STATE((struct soft_i2c *)bus, RT_I2C_STATE_BUSY | RT_I2C_STATE_TX);

    while(count > 0)
    {
        val = i2c_readb(bus);
        if(val >= 0)
        {
            *ptr = val;
            bytes ++;
        }
        else
            break;

        ptr ++;
        count --;

        I2C_DEBUG_LOG(LOG_D, "%s recieve bytes: 0x%02X, %s"
                      , rt_i2c_bus_name(bus)
                      , val
                      , (flags & RT_I2C_NO_READ_ACK)
                      ? "(No ACK)" : (count ? "ACK" : "NACK")
                     );
        if((flags & RT_I2C_NO_READ_ACK) == 0)
        {
            val = i2c_send_ack(bus, (rt_bool_t)(count > 0));
            if(val < 0)
                return val;
        }
    }

    return bytes;
}

static rt_err_t _i2c_addr_restart(struct rt_i2c_bus_device *bus, rt_uint8_t nd)
{
    rt_err_t ret;
    ret = i2c_stop(bus);
    if(RT_EOK != ret || nd)
        return ret;
    I2C_DEBUG_LOG(LOG_D, "%s try sending address again", rt_i2c_bus_name(bus));
    return i2c_start(bus);
}

static rt_int32_t i2c_send_address(struct rt_i2c_bus_device *bus,
                                   rt_uint8_t                addr,
                                   rt_uint16_t               retries)
{
    rt_err_t ret;
    rt_err_t ack;

    SET_STATE((struct soft_i2c *)bus, RT_I2C_STATE_BUSY | RT_I2C_STATE_ADDR);

    I2C_DEBUG_LOG(LOG_D, "%s send addr: 0x%02X", rt_i2c_bus_name(bus), addr);
    for(rt_uint16_t i = 0; i <= retries; i++)
    {
        ack = i2c_writeb(bus, addr);
        if(ack == 1 || 0 == retries)
            return ack;
        I2C_DEBUG_LOG(LOG_W, "%s send addr NACK", rt_i2c_bus_name(bus));
        ret = _i2c_addr_restart(bus, i == retries);
        if(RT_EOK != ret)
            return ret;
    }
    LOG_W("%s send addr failed", rt_i2c_bus_name(bus));

    return ack;
}
static rt_int32_t i2c_send_address10(struct rt_i2c_bus_device *bus,
                                     rt_uint16_t               addr,
                                     rt_uint16_t               retries)
{
    rt_err_t ret;
    rt_uint8_t addr1, addr2;
    rt_err_t ack;

    SET_STATE((struct soft_i2c *)bus, RT_I2C_STATE_BUSY | RT_I2C_STATE_ADDR);

    I2C_DEBUG_LOG(LOG_D, "%s send addr: 0x%04X", rt_i2c_bus_name(bus), addr);
    addr1 = 0xF0 | ((addr >> 7) & 0x06);
    addr2 = addr & 0xFF;
    for(rt_uint16_t i = 0; i <= retries; i++)
    {
        ack = i2c_writeb(bus, addr1);
        if(ack == 1 || 0 == retries)
        {
            ack = i2c_writeb(bus, addr2);
            if(ack == 1 || 0 == retries)
                return ack;
            else
                I2C_DEBUG_LOG(LOG_W, "%s send addr2 NACK",
                              rt_i2c_bus_name(bus));
        }
        else
            I2C_DEBUG_LOG(LOG_W, "%s send addr1 NACK", rt_i2c_bus_name(bus));

        ret = _i2c_addr_restart(bus, i == retries);
        if(RT_EOK != ret)
            return ret;
    }
    LOG_W("%s send addr failed", rt_i2c_bus_name(bus));

    return ack;
}

static rt_err_t soft_i2c_send_address(struct rt_i2c_bus_device *bus,
                                      struct rt_i2c_msg        *msg,
                                      rt_uint8_t ignore)
{
    rt_err_t ret;
    rt_uint16_t flags = msg->flags;
    rt_uint16_t ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
    rt_uint16_t retries;
    rt_err_t ack;

    retries = ignore_nack ? 0 : bus->retries;

    if(flags & RT_I2C_ADDR_10BIT)
    {
        do
        {
            if((flags & RT_I2C_RD) == 0 || ignore == 0)
            {
                ack = i2c_send_address10(bus, msg->addr, retries);
                if(ack < 0)
                {
                    SET_ERROR((struct soft_i2c *)bus, ack);
                    return ack;
                }
                else if((ack != 1) && 0 == ignore_nack)
                {
                    if(0 == ack)
                        SET_ERROR((struct soft_i2c *)bus, -RT_EIO);
                    return -RT_EIO;
                }
            }
            if(flags & RT_I2C_RD)
            {
                i2c_restart(bus);
                if(RT_EOK != ret)
                    return ret;
                ack = i2c_send_address(bus, 0xF1 | ((msg->addr >> 7) & 0x06),
                                       0);
                if(ack < 0)
                {
                    SET_ERROR((struct soft_i2c *)bus, ack);
                    return ack;
                }
                else if((ack != 1) && 0 == ignore_nack)
                {
                    if(retries > 0)
                    {
                        retries--;
                        ignore = 0;
                        I2C_DEBUG_LOG(LOG_W, "%s send addr NACK",
                                      rt_i2c_bus_name(bus));
                        ret = _i2c_addr_restart(bus, 0 == retries);
                        if(RT_EOK != ret)
                            return ret;
                        continue;
                    }
                    LOG_W("%s send addr failed", rt_i2c_bus_name(bus));
                    if(0 == ack)
                        SET_ERROR((struct soft_i2c *)bus, -RT_EIO);
                    return -RT_EIO;
                }
            }
        }
        while(0);
    }
    else
    {
        rt_uint8_t addr1;
        /* 7-bit addr */
        addr1 = msg->addr << 1;
        if(flags & RT_I2C_RD)
            addr1 |= 1;
        ack = i2c_send_address(bus, addr1, retries);
        if(ack < 0)
        {
            SET_ERROR((struct soft_i2c *)bus, ack);
            return ack;
        }
        else if((ack != 1) && 0 == ignore_nack)
        {
            if(0 == ack)
                SET_ERROR((struct soft_i2c *)bus, -RT_EIO);
            return -RT_EIO;
        }
    }

    return RT_EOK;
}

static rt_ssize_t soft_i2c_xfer(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg         msgs[],
                                rt_uint32_t               num)
{
    rt_int32_t ret;
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_uint16_t addr = 0;
    rt_uint16_t ignore_nack;

    if(num == 0) return 0;
    SET_STATE((struct soft_i2c *)bus, RT_I2C_STATE_BUSY);

    for(i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
        I2C_DEBUG_LOG(LOG_D, "%s xfer msgs[%d]:"
                      "addr = 0x%02X, flags = 0x%04X, len = %d"
                      , rt_i2c_bus_name(bus), i
                      , msgs->addr
                      , msgs->flags
                      , msgs->len
                     );
        if((msg->flags & RT_I2C_NO_START) == 0)
        {
            if(i == 0)
            {
                ret = i2c_start(bus);
                if(RT_EOK != ret)
                    goto _getout;
                ret = soft_i2c_send_address(bus, msg, 0);
            }
            else
            {
                ret = i2c_restart(bus);
                if(RT_EOK != ret)
                    goto _getout;
                ret = soft_i2c_send_address(bus, msg, addr == msgs->addr);
            }
            if((RT_EOK != ret) && 0 == ignore_nack)
                goto _getout;
            addr = msgs->addr;
        }
        if(msg->flags & RT_I2C_RD)
        {
            ret = i2c_recv_bytes(bus, msg);
            if(ret >= 1)
                I2C_DEBUG_LOG(LOG_D, "%s readed %d byte%s",
                              rt_i2c_bus_name(bus), ret,
                              ret == 1 ? "" : "s");
            if(ret < msg->len)
            {
                if(ret >= 0)
                    ret = -RT_EIO;
                goto _getout;
            }
        }
        else
        {
            ret = i2c_send_bytes(bus, msg);
            if(ret >= 1)
                I2C_DEBUG_LOG(LOG_D, "%s writed %d byte%s",
                              rt_i2c_bus_name(bus), ret,
                              ret == 1 ? "" : "s");
            if(ret < msg->len)
            {
                if(ret >= 0)
                    ret = -RT_ERROR;
                goto _getout;
            }
        }
    }
    ret = i;

_getout:
    if((msg->flags & RT_I2C_NO_STOP) == 0)
    {
        i2c_stop(bus);
    }

    return ret;
}

static rt_err_t soft_i2c_control(struct rt_i2c_bus_device   *bus,
                                 int                        cmd,
                                 void                       *args)
{
    rt_err_t ret = RT_EOK;
    struct soft_i2c *obj = (struct soft_i2c *)bus;
    RT_UNUSED(obj);
    RT_ASSERT(bus != RT_NULL);

    I2C_DEBUG_LOG(LOG_D, "%s CMD start: 0x%04X", rt_i2c_bus_name(bus), cmd);
    switch(cmd)
    {
        case RT_I2C_DEV_CTRL_UNLOCK:
            rt_i2c_bus_lock(bus, RT_WAITING_FOREVER);
            ret = i2c_bus_unlock(bus);
            rt_i2c_bus_unlock(bus);
            break;
            #ifdef RT_I2C_DETAIL
        case RT_I2C_DEV_CTRL_GET_STATE:
            if(args)
            {
                *(rt_int32_t *)args = obj->state;
            }
            else
            {
                LOG_W("%s invalid args CMD:", rt_i2c_bus_name(bus), cmd);
                ret = -RT_EINVAL;
            }
            break;
        case RT_I2C_DEV_CTRL_GET_ERROR:
            if(args)
            {
                *(rt_int32_t *)args = obj->error;
            }
            else
            {
                LOG_W("%s invalid args CMD:", rt_i2c_bus_name(bus), cmd);
                ret = -RT_EINVAL;
            }
            break;
            #endif  //RT_I2C_DETAIL
        default:
            LOG_W("%s invalid CMD: 0x%04X", rt_i2c_bus_name(bus), cmd);
            return -RT_ENOSYS;
    }
    I2C_DEBUG_LOG(LOG_D, "%s CMD end: 0x%04X", rt_i2c_bus_name(bus), cmd);

    return ret;
}
static const struct rt_i2c_bus_device_ops i2c_bit_bus_ops =
{
    .master_xfer        = soft_i2c_xfer,
    .slave_xfer         = RT_NULL,
    .i2c_bus_control    = soft_i2c_control,
};


/* I2C initialization function */
int rt_soft_i2c_init(void)
{
    int err = RT_EOK;
    struct soft_i2c *obj;

    for(int i = 0; i < sizeof(i2c_bus_obj) / sizeof(i2c_bus_obj[0]); i++)
    {
        const struct soft_i2c_config *cfg = &i2c_cfg[i];
        obj = &i2c_bus_obj[i];
        obj->cfg = cfg;

        rt_pin_mode(cfg->scl_pin, PIN_MODE_OUTPUT_OD);
        rt_pin_mode(cfg->sda_pin, PIN_MODE_OUTPUT_OD);
        rt_pin_write(cfg->scl_pin, PIN_HIGH);
        rt_pin_write(cfg->sda_pin, PIN_HIGH);

        obj->i2c_bus.ops = &i2c_bit_bus_ops;
        if(rt_i2c_bus_device_register(&obj->i2c_bus, cfg->bus_name) == RT_EOK)
        {
            i2c_bus_unlock(&obj->i2c_bus);
            #ifdef RT_I2C_DETAIL
            obj->state = RT_I2C_STATE_READY;
            #endif  //RT_I2C_DETAIL
            I2C_DEBUG_LOG(LOG_D, "Software simulation %s init done"
                          ", SCL pin: 0x%02X, SDA pin: 0x%02X"
                          , cfg->bus_name
                          , cfg->scl_pin
                          , cfg->sda_pin
                         );
        }
        else
        {
            err++;
            SET_ERROR(obj, -RT_ERROR);
            LOG_E("Software simulation %s init fail"
                  ", SCL pin: 0x%02X, SDA pin: 0x%02X"
                  , cfg->bus_name
                  , cfg->scl_pin
                  , cfg->sda_pin
                 );
        }
    }

    return err;
}
INIT_PREV_EXPORT(rt_soft_i2c_init);


#if defined(RT_USING_FINSH) && defined(RT_USING_SOFT_I2C_FINSH)
#include <string.h>
#include <stdlib.h>

static rt_uint16_t i2c_str2flags(const char *str)
{
    rt_uint16_t flags = 0;
    if(strchr(str, 'r'))
        flags |= RT_I2C_RD;
    if(strchr(str, 'i'))
        flags |= RT_I2C_IGNORE_NACK;
    if(strchr(str, 'a'))
        flags |= RT_I2C_NO_READ_ACK;
    if(strchr(str, 's'))
        flags |= RT_I2C_NO_START;
    if(strchr(str, 'p'))
        flags |= RT_I2C_NO_STOP;

    return flags;
}

int cmd_soft_i2c(int argc, char **argv)
{
    static struct rt_i2c_bus_device *bus = RT_NULL;
    rt_int32_t ret = 0;

    if(argc < 2)
        goto _usage;

    for(argc--, argv++; argc > 0;)
    {
        if(rt_strcmp(argv[0], "find") == 0)
        {
            struct rt_i2c_bus_device    *_bus;

            if(argc < 2)
                break;

            _bus = rt_i2c_bus_device_find(argv[1]);
            if(_bus)
            {
                bus = _bus;
                rt_kprintf("Find the I2C bus: %s\n", rt_i2c_bus_name(bus));
                argc -= 2;
                argv += 2;
            }
            else
            {
                rt_kprintf("Not Find the I2C bus: %s\n", argv[1]);
                return 1;
            }
        }
        else if(rt_strcmp(argv[0], "xfer") == 0)
        {
            struct rt_i2c_msg       msg = { 0 };
            rt_uint32_t             data = 0;
            char                    str[10];

            if(RT_NULL == bus)
                goto _bus_null;
            if(argc < 4)
                break;

            msg.flags = i2c_str2flags(argv[1]);
            msg.addr = strtoull(argv[2], 0, 0);
            if(msg.addr > 0xFF)
                msg.flags |= RT_I2C_ADDR_10BIT;
            msg.buf = (rt_uint8_t *)&data;

            rt_kprintf("%s bus xfer: addr = 0x%02X",
                       rt_i2c_bus_name(bus), msg.addr);
            if(msg.flags & RT_I2C_RD)
            {
                msg.len = strtoull(argv[3], 0, 0);
                rt_kprintf(", len = %d: ", msg.len);
                if(msg.len > sizeof(data))
                {
                    rt_kprintf("Length greater than %d\n", sizeof(data));
                    return 1;
                }
            }
            else
            {
                data = strtoull(argv[3], 0, 0);
                msg.len = (rt_strlen(argv[3]) >> 1) - 1;//must hex
                rt_snprintf(str, sizeof(str), "0x%%0%dX: ", msg.len * 2);
                rt_kprintf(", data = ");
                rt_kprintf(str, data);
            }
            ret = soft_i2c_xfer(bus, &msg, 1);
            if(ret < 0)
            {
                rt_kprintf("%s\n", rt_strerror(ret));
                return 1;
            }
            else
            {
                if(msg.flags & RT_I2C_RD)
                {
                    rt_snprintf(str, sizeof(str), "0x%%0%dX\n", msg.len * 2);
                    rt_kprintf(str, data);
                }
                else
                    rt_kprintf("success\n");
            }
            argc -= 4;
            argv += 4;
        }
        else if(rt_strcmp(argv[0], "start") == 0)
        {
            if(RT_NULL == bus)
                goto _bus_null;

            ret = i2c_start(bus);
            if(RT_EOK != ret)
            {
                rt_kprintf("%s bus start fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
                return 1;
            }
            argc -= 1;
            argv += 1;
        }
        else if(rt_strcmp(argv[0], "restart") == 0)
        {
            if(RT_NULL == bus)
                goto _bus_null;

            ret = i2c_restart(bus);
            if(RT_EOK != ret)
            {
                rt_kprintf("%s bus restart fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
                return 1;
            }
            argc -= 1;
            argv += 1;
        }
        else if(rt_strcmp(argv[0], "stop") == 0)
        {
            if(RT_NULL == bus)
                goto _bus_null;

            ret = i2c_stop(bus);
            if(RT_EOK != ret)
            {
                rt_kprintf("%s bus stop fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
                return 1;
            }
            argc -= 1;
            argv += 1;
        }
        else if(rt_strcmp(argv[0], "unlock") == 0)
        {
            if(RT_NULL == bus)
                goto _bus_null;

            ret = i2c_bus_unlock(bus);
            if(RT_EOK == ret)
            {
                rt_kprintf("%s bus unlocked\n", rt_i2c_bus_name(bus));
            }
            else
            {
                rt_kprintf("%s bus unlock fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
                return 1;
            }
            argc -= 1;
            argv += 1;
        }
        else if(rt_strcmp(argv[0], "addr") == 0)
        {
            struct rt_i2c_msg       msg = { 0 };

            if(RT_NULL == bus)
                goto _bus_null;
            if(argc < 3)
                break;

            msg.flags = i2c_str2flags(argv[1]);
            msg.addr = strtoull(argv[2], 0, 0);
            if(msg.addr > 0xFF)
                msg.flags |= RT_I2C_ADDR_10BIT;

            rt_kprintf("%s bus addr: 0x%02X %s: ",
                       rt_i2c_bus_name(bus), msg.addr,
                       msg.flags & RT_I2C_RD ? "read" : "write");
            ret = soft_i2c_send_address(bus, &msg, 0);
            if(ret < 0)
            {
                rt_kprintf("%s\n", rt_strerror(ret));
                return 1;
            }
            else
                rt_kprintf("success\n");
            argc -= 3;
            argv += 3;
        }
        else if(rt_strcmp(argv[0], "send") == 0)
        {
            struct rt_i2c_msg       msg = { 0 };
            rt_uint32_t             data;
            char                    str[10];

            if(RT_NULL == bus)
                goto _bus_null;
            if(argc < 3)
                break;

            msg.flags = i2c_str2flags(argv[1]);
            msg.buf = (rt_uint8_t *)&data;
            data = strtoull(argv[2], 0, 0);
            msg.len = (rt_strlen(argv[2]) >> 1) - 1;//argv[2] must hex

            if(msg.len > sizeof(data))
            {
                rt_kprintf("Once send data length must"
                           "not greater %d\n", sizeof(data));
                return 1;
            }
            else
            {
                rt_snprintf(str, sizeof(str), "0x%%0%dX: ", msg.len * 2);
                rt_kprintf("%s bus send ", rt_i2c_bus_name(bus));
                rt_kprintf(str, data);
                ret = i2c_send_bytes(bus, &msg);
                if(ret < msg.len)
                {
                    if(ret < 0)
                        rt_kprintf("%s\n", rt_strerror(ret));
                    else
                        rt_kprintf("%d\n", ret);
                    return 1;
                }
                else
                {
                    rt_kprintf("success\n", ret);
                }
                argc -= 3;
                argv += 3;
            }
        }
        else if(rt_strcmp(argv[0], "recv") == 0)
        {
            struct rt_i2c_msg       msg = { 0 };
            rt_uint32_t             data = 0;
            char                    str[10];

            if(RT_NULL == bus)
                goto _bus_null;
            if(argc < 3)
                break;

            msg.flags = i2c_str2flags(argv[1]);
            msg.buf = (rt_uint8_t *)&data;
            msg.len = strtoull(argv[2], 0, 0);

            if(msg.len > sizeof(data))
            {
                rt_kprintf("Once recv data length must"
                           "not greater %d\n", sizeof(data));
                return 1;
            }
            else
            {
                rt_kprintf("%s bus recv %d:",
                           rt_i2c_bus_name(bus), msg.len);
                ret = i2c_recv_bytes(bus, &msg);
                if(ret < msg.len)
                {
                    if(ret < 0)
                        rt_kprintf("%s\n", rt_strerror(ret));
                    else
                        rt_kprintf("%d\n", ret);
                    return 1;
                }
                else
                {
                    rt_snprintf(str, sizeof(str),
                                "0x%%0%dX\n", msg.len * 2);
                    rt_kprintf(str, data);
                }
                argc -= 3;
                argv += 3;
            }
        }
        #ifdef RT_I2C_DETAIL
        else if(rt_strcmp(argv[0], "state") == 0)
        {
            rt_ubase_t state;   /* I2C communication state */

            if(RT_NULL == bus)
                goto _bus_null;

            ret = soft_i2c_control(bus, RT_I2C_DEV_CTRL_GET_STATE, &state);
            if(RT_EOK == ret)
                rt_kprintf("%s bus state: 0x%08X\n",
                           rt_i2c_bus_name(bus), state);
            else
                rt_kprintf("%s bus get state fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
            argc -= 1;
            argv += 1;
        }
        #endif  //RT_I2C_DETAIL
        else if(rt_strcmp(argv[0], "info") == 0)
        {
            struct soft_i2c *obj = (struct soft_i2c *)bus;
            #ifdef RT_USING_SOFT_I2C_SIMPLE
            rt_kprintf("Simple soft I2C, ");
            #else
            rt_kprintf("Normal soft I2C, ");
            #endif // RT_USING_SOFT_I2C_SIMPLE
            if(RT_NULL == bus)
                goto _bus_null;
            rt_kprintf("bus name: %s\n", rt_i2c_bus_name(bus));

            rt_kprintf("Bus pin: SCL = 0x%02X, SDA = 0x%02X\n",
                       obj->cfg->scl_pin, obj->cfg->sda_pin);
            rt_kprintf("Timing delay (us): %d\n", obj->cfg->timing_delay);
            rt_kprintf("Timing timeout (tick): %d\n",
                       obj->cfg->timing_timeout);

            #ifdef RT_I2C_DETAIL
            rt_kprintf("State: 0x%08X\n", obj->state);
            rt_kprintf("Error code: 0x%08X(%s)\n",
                       obj->error, rt_strerror(obj->error));
            #endif  //RT_I2C_DETAIL

            argc -= 1;
            argv += 1;
        }
        else if(rt_strcmp(argv[0], "take") == 0)
        {
            if(RT_NULL == bus)
                goto _bus_null;

            ret = rt_i2c_bus_lock(bus, RT_WAITING_FOREVER);

            if(RT_EOK == ret)
                rt_kprintf("%s bus take\n", rt_i2c_bus_name(bus));
            else
                rt_kprintf("%s bus take fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
            argc -= 1;
            argv += 1;
        }
        else if(rt_strcmp(argv[0], "release") == 0)
        {
            if(RT_NULL == bus)
                goto _bus_null;

            ret = rt_i2c_bus_unlock(bus);

            if(RT_EOK == ret)
                rt_kprintf("%s bus release\n", rt_i2c_bus_name(bus));
            else
                rt_kprintf("%s bus release fail: %s\n",
                           rt_i2c_bus_name(bus), rt_strerror(ret));
            argc -= 1;
            argv += 1;
        }
        else
        {
            struct rt_i2c_bus_device    *_bus;

            _bus = rt_i2c_bus_device_find(argv[0]);
            if(_bus)
            {
                bus = _bus;
                rt_kprintf("Find the I2C bus: %s\n", rt_i2c_bus_name(bus));
                argc -= 1;
                argv += 1;
            }
            else
            {
                rt_kprintf("Invalid CMD: %s\n", argv[0]);
                break;
            }
        }
    }

    if(0 == argc)
        return 0;

_usage:
    rt_kprintf("Usage: soft_i2c [name] [options [...]]\n");
    rt_kprintf("[name]: I2C bus name.\n");
    rt_kprintf("[options]:\n");
    rt_kprintf("    %-12s - Find and set the current bus by name.\n", "find");
    rt_kprintf("    %-12s - Xfer data.\n", "xfer");
    rt_kprintf("    %-12s - Send start condition.\n", "start");
    rt_kprintf("    %-12s - Send restart condition.\n", "restart");
    rt_kprintf("    %-12s - Send stop condition.\n", "stop");
    rt_kprintf("    %-12s - Unlock bus.\n", "unlock");
    rt_kprintf("    %-12s - Send addr.\n", "addr");
    rt_kprintf("    %-12s - Send bytes.\n", "send");
    rt_kprintf("    %-12s - Recv bytes.\n", "recv");
    #ifdef RT_I2C_DETAIL
    rt_kprintf("    %-12s - Get bus status.\n", "state");
    #endif  //RT_I2C_DETAIL
    rt_kprintf("    %-12s - Get state info.\n", "info");
    rt_kprintf("    %-12s - Take bus.\n", "take");
    rt_kprintf("    %-12s - Release bus.\n", "release");
    return 1;

_bus_null:
    rt_kprintf("Bus is null!\n", argv[0]);
    return 1;
}
MSH_CMD_EXPORT_ALIAS(cmd_soft_i2c, soft_i2c, Soft I2C Test);
#endif  //RT_USING_SOFT_I2C_FINSH

#endif // RT_USING_SOFT_I2C
