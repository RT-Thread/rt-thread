/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-01-21     charlown           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "board.h"
#include "drv_hwi2c.h"

#ifdef BSP_USING_HWI2C

#define LOG_TAG "drv.hwi2c"
#include "drv_log.h"

#define TIMEOUT 0x0FF

struct i2c_bus_device
{
    struct rt_i2c_bus_device parent;
    I2C_TypeDef *periph;
};

#ifdef BSP_USING_HWI2C1

struct i2c_bus_device i2c_bus1;
#endif

#ifdef BSP_USING_HWI2C2

struct i2c_bus_device i2c_bus2;
#endif

static int ch32f2_i2c_read(I2C_TypeDef *i2c_periph,
                           rt_uint8_t flags,
                           rt_uint16_t slave_address,
                           rt_uint8_t *p_buffer,
                           rt_uint16_t data_byte)
{
    rt_uint32_t try;

    if (flags & RT_I2C_ADDR_10BIT)
    {
        //fixme
    }
    else
    {
        //7 bit address
        try = 0;
        while (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_BUSY) != RESET)
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus read getflag timeout! \n");
                return -1;
            }
            try++;
        };

        I2C_GenerateSTART(i2c_periph, ENABLE);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus read checkevent timeout! \n");
                return -1;
            }
            try++;
        };
        I2C_Send7bitAddress(i2c_periph, (slave_address << 1), I2C_Direction_Transmitter);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus read checkevent timeout! \n");
                return -1;
            }
            try++;
        };

        I2C_GenerateSTART(i2c_periph, ENABLE);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus read checkevent timeout! \n");
                return -1;
            }
            try++;
        };
        I2C_Send7bitAddress(i2c_periph, (slave_address << 1), I2C_Direction_Receiver);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus read checkevent timeout! \n");
                return -1;
            }
            try++;
        };

        if (data_byte == 1)
        {
            try = 0;
            while (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_RXNE) == RESET)
            {

                if (try == TIMEOUT)
                {
                    LOG_E("i2c bus read checkevent timeout! \n");
                    return -1;
                }
                try++;
            };

            I2C_AcknowledgeConfig(i2c_periph, DISABLE);

            *p_buffer = I2C_ReceiveData(i2c_periph);

            I2C_GenerateSTOP(i2c_periph, ENABLE);
        }
        else
        {

            try = 0;
            while (data_byte)
            {

                if (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_RXNE) == RESET)
                {
                    *p_buffer = I2C_ReceiveData(i2c_periph);

                    p_buffer++;
                    data_byte--;
                    try = 0;

                    if (data_byte == 1)
                    {
                        I2C_AcknowledgeConfig(i2c_periph, DISABLE);
                        I2C_GenerateSTOP(i2c_periph, ENABLE);
                    }
                }

                if (try == TIMEOUT)
                {
                    LOG_E("i2c bus read checkevent timeout! \n");
                    return -1;
                }

                try++;
            }
        }
    }

    return 0;
}

static int ch32f2_i2c_write(I2C_TypeDef *i2c_periph,
                            rt_uint8_t flags,
                            rt_uint16_t slave_address,
                            rt_uint8_t *p_buffer,
                            rt_uint16_t data_byte)
{
    rt_uint32_t try;

    if (flags & RT_I2C_ADDR_10BIT)
    {
        //fixme
    }
    else
    {
        //7 bit address
        try = 0;
        while (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_BUSY) != RESET)
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus write getflag timeout! \n");
                return -1;
            }
            try++;
        };

        I2C_GenerateSTART(i2c_periph, ENABLE);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus write checkevent timeout! \n");
                return -1;
            }
            try++;
        };
        I2C_Send7bitAddress(i2c_periph, (slave_address << 1), I2C_Direction_Transmitter);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus write checkevent timeout! \n");
                return -1;
            }
            try++;
        };

        I2C_GenerateSTART(i2c_periph, ENABLE);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus write checkevent timeout! \n");
                return -1;
            }
            try++;
        };
        I2C_Send7bitAddress(i2c_periph, (slave_address << 1), I2C_Direction_Transmitter);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus write checkevent timeout! \n");
                return -1;
            }
            try++;
        };

        try = 0;
        while (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_TXE) == RESET)
        {

            if (try == TIMEOUT)
            {
                LOG_E("i2c bus write checkevent timeout! \n");
                return -1;
            }
            try++;
        };

        while (data_byte)
        {
            I2C_SendData(i2c_periph, *p_buffer);
            p_buffer++;
            data_byte--;

            try = 0;
            while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            {
                if (try == TIMEOUT)
                {
                    LOG_E("i2c bus write checkevent timeout! \n");
                    return -1;
                }
                try++;
            };
        }

        I2C_GenerateSTOP(i2c_periph, ENABLE);
    }

    return 0;
}

static rt_ssize_t ch32f2_master_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    struct i2c_bus_device *i2c_bus_dev;
    rt_uint32_t index;

    i2c_bus_dev = (struct i2c_bus_device *)bus;

    for (index = 0; index < num; index++)
    {
        msg = &msgs[index];
        if (msg->flags & RT_I2C_RD)
        {

            if (ch32f2_i2c_read(i2c_bus_dev->periph, msg->flags, msg->addr, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                return 0;
            }
        }
        else
        {

            if (ch32f2_i2c_write(i2c_bus_dev->periph, msg->flags, msg->addr, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                return 0;
            }
        }
    }

    return index;
}

const struct rt_i2c_bus_device_ops ch32f2_i2c_ops = {
    .master_xfer = ch32f2_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = RT_NULL,
};

int rt_hw_i2c_init(void)
{
    int result = RT_EOK;

#ifdef BSP_USING_HWI2C1

    i2c_bus1.periph = I2C1;
    ch32f2_i2c_clock_and_io_init(i2c_bus1.periph);
    ch32f2_i2c_config(i2c_bus1.periph);

    i2c_bus1.parent.ops = &ch32f2_i2c_ops;
    result = rt_i2c_bus_device_register(&i2c_bus1.parent, "hwi2c1");
    if (result != RT_EOK)
    {
        return result;
    }
#endif

#ifdef BSP_USING_HWI2C2

    i2c_bus2.periph = I2C2;
    ch32f2_i2c_clock_and_io_init(i2c_bus2.periph);
    ch32f2_i2c_config(i2c_bus2.periph);

    i2c_bus2.parent.ops = &ch32f2_i2c_ops;

    rt_i2c_bus_device_register(&i2c_bus2.parent, "hwi2c2");
    if (result != RT_EOK)
    {
        return result;
    }
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_HWI2C */
