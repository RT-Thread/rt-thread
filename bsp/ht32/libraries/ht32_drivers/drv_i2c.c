/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include "drv_i2c.h"

#ifdef RT_USING_I2C
#if !defined(BSP_USING_I2C0_HW) && !defined(BSP_USING_I2C1_HW)
    #error "Please define at least one BSP_USING_I2Cx_HW"
    /* this driver can be disabled at menuconfig RT-Thread Components Device Drivers */
#endif

struct ht32_i2c_config
{
    HT_I2C_TypeDef *i2c_x;
    const char *i2c_name;
    IRQn_Type irq;
};

struct ht32_i2c
{
    struct ht32_i2c_config *config;
    struct rt_i2c_bus_device i2c_bus;
};

enum
{
#ifdef BSP_USING_I2C0_HW
    I2C0_INDEX,
#endif
#ifdef BSP_USING_I2C1_HW
    I2C1_INDEX,
#endif
};

static struct ht32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C0_HW
    {
        .i2c_x      = HT_I2C0,
        .i2c_name   = BSP_USING_I2C0_HW_NAME,
        .irq        = I2C0_IRQn
    },
#endif
#ifdef BSP_USING_I2C1_HW
    {
        .i2c_x      = HT_I2C1,
        .i2c_name   = BSP_USING_I2C1_HW_NAME,
        .irq        = I2C1_IRQn
    },
#endif
};

static struct ht32_i2c i2cs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static rt_size_t ht32_i2c_init(struct ht32_i2c *i2c_drv)
{
    struct ht32_i2c_config *i2c_config = i2c_drv->config;

    CKCU_PeripClockConfig_TypeDef   CKCUClock = {{0}};
#ifdef BSP_USING_I2C0_HW
    if (HT_I2C0 == i2c_config->i2c_x)
    {
        CKCUClock.Bit.I2C0  = 1;
    }
#endif
#ifdef BSP_USING_I2C1_HW
    if (HT_I2C1 == i2c_config->i2c_x)
    {
        CKCUClock.Bit.I2C1  = 1;
    }
#endif
    CKCUClock.Bit.AFIO  = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    ht32_hardware_i2c_gpio_init(i2c_config->i2c_x);

    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_GeneralCall   =   DISABLE;
    I2C_InitStructure.I2C_AddressingMode    =   I2C_ADDRESSING_7BIT;
    I2C_InitStructure.I2C_Acknowledge   =   DISABLE;
    I2C_InitStructure.I2C_OwnAddress    =   0x00;
    I2C_InitStructure.I2C_Speed         =   400000;
    I2C_InitStructure.I2C_SpeedOffset   =   0;

    I2C_Init(i2c_config->i2c_x, &I2C_InitStructure);
    I2C_Cmd(i2c_config->i2c_x, ENABLE);

    return RT_EOK;
}

static int ht32_i2c_read(struct ht32_i2c_config *hi2c,
                        rt_uint16_t slave_address,
                        rt_uint8_t *p_buffer,
                        rt_uint16_t data_byte)
{
    uint16_t date_num = 0;
    uint8_t data = 0xFF;

    /* Determine if the bus is idle */
    while (I2C_GetFlagStatus(hi2c->i2c_x, I2C_FLAG_BUSBUSY));
    /* Send start bit, slave address and read/write bit */
    I2C_TargetAddressConfig(hi2c->i2c_x, slave_address, I2C_MASTER_READ);

    while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_SEND_START));
    while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_RECEIVER_MODE));
    I2C_AckCmd(hi2c->i2c_x, ENABLE);
    while (date_num < data_byte)
    {
        date_num++;

        while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_RX_NOT_EMPTY));
        data = I2C_ReceiveData(hi2c->i2c_x);

        if (date_num == (data_byte - 1))
        {
            I2C_AckCmd(hi2c->i2c_x, DISABLE);
        }
        if (p_buffer != RT_NULL)
        {
            *p_buffer++ = data;
        }
    }
    I2C_GenerateSTOP(hi2c->i2c_x);
    while (I2C_ReadRegister(hi2c->i2c_x, I2C_REGISTER_SR) & 0x80000);

    return 0;
}

static int ht32_i2c_write(struct ht32_i2c_config *hi2c,
                        uint16_t slave_address,
                        uint8_t *p_buffer,
                        uint16_t data_byte)
{
    uint16_t date_num = data_byte;

    /* Determine if the bus is idle */
    while (I2C_GetFlagStatus(hi2c->i2c_x, I2C_FLAG_BUSBUSY));
    /* Send start bit, slave address and read/write bit */
    I2C_TargetAddressConfig(hi2c->i2c_x, slave_address, I2C_MASTER_WRITE);

    while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_SEND_START));

    while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_TRANSMITTER_MODE));
    while (date_num--)
    {
        while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_TX_EMPTY));
        I2C_SendData(hi2c->i2c_x, *p_buffer);
        p_buffer++;
    }

    while (!I2C_CheckStatus(hi2c->i2c_x, I2C_MASTER_TX_EMPTY));
    I2C_GenerateSTOP(hi2c->i2c_x);
    while (I2C_ReadRegister(hi2c->i2c_x, I2C_REGISTER_SR) & 0x80000);
    return 0;
}

static rt_ssize_t ht32_master_xfer(struct rt_i2c_bus_device *bus,
                                   struct rt_i2c_msg msgs[],
                                   rt_uint32_t num)
{
    struct ht32_i2c *i2c_instance;
    struct rt_i2c_msg *msg;
    rt_uint32_t i;

    i2c_instance = rt_container_of(bus, struct ht32_i2c, i2c_bus);
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            if (ht32_i2c_read(i2c_instance->config, msg->addr, msg->buf, msg->len) != 0)
            {
                return i;
            }
        }
        else
        {
            if (ht32_i2c_write(i2c_instance->config, msg->addr, msg->buf, msg->len) != 0)
            {
                return i;
            }
        }
    }
    return i;
}

static struct rt_i2c_bus_device_ops ht32_i2c_ops =
{
    .master_xfer = ht32_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = RT_NULL
};

int rt_hw_i2c_init(void)
{
    int i;
    rt_err_t result;
    rt_size_t obj_num = sizeof(i2cs) / sizeof(struct ht32_i2c);

    for (i = 0; i < obj_num; i++)
    {
        i2cs[i].config = &i2c_config[i];
        i2cs[i].i2c_bus.parent.user_data = (void *)&i2cs[i];
        i2cs[i].i2c_bus.ops = &ht32_i2c_ops;

        ht32_i2c_init(&i2cs[i]);
        result = rt_i2c_bus_device_register(&i2cs[i].i2c_bus, i2cs[i].config->i2c_name);
    }
    return result;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* RT_USING_I2C */
