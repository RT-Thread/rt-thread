/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-03     AisinoChip   first implementation.
 */

#include "board.h"

#if defined(RT_USING_I2C)
#if defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2)
#include <rtdevice.h>
#include "i2c_config.h"

enum
{
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C2
    I2C2_INDEX,
#endif
    I2C_MAX_INDEX
};

struct acm32_i2c_config
{
    I2C_TypeDef         *Instance;
    char                *name;
    IRQn_Type           irq_type;
    enum_Enable_ID_t    enable_id;

    uint32_t            clock_speed;

    enum_GPIOx_t        scl_port;
    rt_uint32_t         scl_pin;
    rt_uint32_t         scl_alternate;

    enum_GPIOx_t        sda_port;
    rt_uint32_t         sda_pin;
    rt_uint32_t         sda_alternate;
};

struct acm32_i2c
{
    I2C_HandleTypeDef           handle;
    struct acm32_i2c_config     *config;
    struct rt_i2c_bus_device    i2c_bus;
};

static struct acm32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_CONFIG,
#endif

#ifdef BSP_USING_I2C2
    I2C2_CONFIG,
#endif
};

static struct acm32_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static int acm32_i2c_read(struct acm32_i2c *hi2c, rt_uint16_t slave_address, rt_uint8_t *p_buffer, rt_uint16_t data_byte)
{
    if (HAL_I2C_Master_Receive(&hi2c->handle, slave_address, p_buffer, data_byte, 1000) != HAL_OK)
    {
        return -1;
    }

    return 0;
}

static int acm32_i2c_write(struct acm32_i2c *hi2c, uint16_t slave_address, uint8_t *p_buffer, uint16_t data_byte)
{
    if (HAL_I2C_Master_Transmit(&hi2c->handle, slave_address, p_buffer, data_byte, 1000) != HAL_OK)
    {
        return -1;
    }

    return 0;
}

static rt_ssize_t _i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    struct acm32_i2c *i2c_obj;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    i2c_obj = rt_container_of(bus, struct acm32_i2c, i2c_bus);

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            if (acm32_i2c_read(i2c_obj, msg->addr, msg->buf, msg->len) != 0)
            {
                goto out;
            }
        }
        else
        {
            if (acm32_i2c_write(i2c_obj, msg->addr, msg->buf, msg->len) != 0)
            {
                goto out;
            }
        }
    }

out:

    return i;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    _i2c_xfer,
    RT_NULL,
    RT_NULL
};

int rt_hw_i2c_init(void)
{
    rt_err_t result;

    for (int i = 0; i < sizeof(i2c_config) / sizeof(i2c_config[0]); i++)
    {
        i2c_objs[i].config = &i2c_config[i];
        i2c_objs[i].i2c_bus.parent.user_data = &i2c_config[i];
        i2c_objs[i].handle.Instance = i2c_config[i].Instance;

        i2c_objs[i].i2c_bus.ops = &i2c_ops;

        /* hardware initial */
        i2c_objs[i].handle.Init.Clock_Speed = i2c_config[i].clock_speed ;
        i2c_objs[i].handle.Init.Tx_Auto_En = TX_AUTO_EN_ENABLE;
        i2c_objs[i].handle.Init.I2C_Mode = I2C_MODE_MASTER;

        HAL_I2C_Init(&i2c_objs[i].handle);

        result = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_config[i].name);
        RT_ASSERT(result == RT_EOK);
    }

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

/************************************************************************
 * function   : HAL_I2C_MspInit
 * Description:
 * input      : hi2c : pointer to a I2C_HandleTypeDef structure that contains
 *                     the configuration information for I2C module
 ************************************************************************/
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef GPIO_Handle;
    struct acm32_i2c *i2c_obj;
    struct acm32_i2c_config *i2c_config;

    RT_ASSERT(hi2c != RT_NULL);

    i2c_obj = rt_container_of(hi2c, struct acm32_i2c, handle);

    RT_ASSERT(i2c_obj->i2c_bus.parent.user_data != RT_NULL);

    i2c_config = (struct acm32_i2c_config *)i2c_obj->i2c_bus.parent.user_data;

    /* Enable Clock */
    System_Module_Enable(i2c_config->enable_id);

    /* I2C SDA */
    GPIO_Handle.Pin            = i2c_config->sda_pin;
    GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull           = GPIO_PULLUP;
    GPIO_Handle.Alternate      = i2c_config->sda_alternate;
    HAL_GPIO_Init(i2c_config->sda_port, &GPIO_Handle);

    /* I2C SCL */
    GPIO_Handle.Pin            = i2c_config->scl_pin;
    GPIO_Handle.Mode           = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull           = GPIO_PULLUP;
    GPIO_Handle.Alternate      = i2c_config->scl_alternate;
    HAL_GPIO_Init(i2c_config->scl_port, &GPIO_Handle);

    /* Clear Pending Interrupt */
    NVIC_ClearPendingIRQ(i2c_config->irq_type);

    /* Enable External Interrupt */
    NVIC_EnableIRQ(i2c_config->irq_type);
}

#endif /* defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) */
#endif /* RT_USING_I2C */

