/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include "drv_i2c.h"

#ifdef RT_USING_I2C

#define DBG_TAG               "drv.I2C"
#ifdef RT_I2C_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif
#include <rtdbg.h>


#ifdef RT_USING_I2C_BITOPS
static const struct n32_soft_i2c_config soft_i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C2
    I2C2_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C3
    I2C3_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C4
    I2C4_BUS_CONFIG,
#endif
};

static struct n32_i2c i2c_obj[sizeof(soft_i2c_config) / sizeof(soft_i2c_config[0])];

/**
*\*\name    n32_i2c_gpio_init
*\*\fun     Initializes the i2c pin.
*\*\param   i2c dirver class
*\*\return  none
**/
static void n32_i2c_gpio_init(struct n32_i2c *i2c)
{
    struct n32_soft_i2c_config* cfg = (struct n32_soft_i2c_config*)i2c->ops.data;

    rt_pin_mode(cfg->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(cfg->sda, PIN_MODE_OUTPUT_OD);

    rt_pin_write(cfg->scl, PIN_HIGH);
    rt_pin_write(cfg->sda, PIN_HIGH);
}

/**
*\*\name    n32_set_sda
*\*\fun     sets the sda pin.
*\*\param   data config class
*\*\param   state sda pin state
*\*\return  none
**/
static void n32_set_sda(void *data, rt_int32_t state)
{
    struct n32_soft_i2c_config* cfg = (struct n32_soft_i2c_config*)data;
    if (state)
    {
        rt_pin_write(cfg->sda, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->sda, PIN_LOW);
    }
}

/**
*\*\name    n32_set_scl
*\*\fun     sets the scl pin.
*\*\param   data config class
*\*\param   state scl pin state
*\*\return  none
**/
static void n32_set_scl(void *data, rt_int32_t state)
{
    struct n32_soft_i2c_config* cfg = (struct n32_soft_i2c_config*)data;
    if (state)
    {
        rt_pin_write(cfg->scl, PIN_HIGH);
    }
    else
    {
        rt_pin_write(cfg->scl, PIN_LOW);
    }
}

/**
*\*\name    n32_get_sda
*\*\fun     gets the sda pin state.
*\*\param   data config class
*\*\return  sda pin state
**/
static rt_int32_t n32_get_sda(void *data)
{
    struct n32_soft_i2c_config* cfg = (struct n32_soft_i2c_config*)data;
    return rt_pin_read(cfg->sda);
}

/**
*\*\name    n32_get_scl
*\*\fun     gets the scl pin state.
*\*\param   data config class
*\*\return  scl pin state
**/
static rt_int32_t n32_get_scl(void *data)
{
    struct n32_soft_i2c_config* cfg = (struct n32_soft_i2c_config*)data;
    return rt_pin_read(cfg->scl);
}


/**
*\*\name    n32_udelay
*\*\fun     The time delay function.
*\*\param   us
*\*\return  none
**/
static void n32_udelay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;

    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;

            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

static const struct rt_i2c_bit_ops n32_bit_ops_default =
{
    .data     = RT_NULL,
    .set_sda  = n32_set_sda,
    .set_scl  = n32_set_scl,
    .get_sda  = n32_get_sda,
    .get_scl  = n32_get_scl,
    .udelay   = n32_udelay,
    .delay_us = 1,
    .timeout  = 100
};


/**
*\*\name    n32_i2c_bus_unlock
*\*\fun     If i2c is locked, this function will unlock it.
*\*\param   cfg
*\*\return  RT_EOK indicates successful unlock
**/
static rt_err_t n32_i2c_bus_unlock(const struct n32_soft_i2c_config *cfg)
{
    rt_int32_t i = 0;

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        while (i++ < 9)
        {
            rt_pin_write(cfg->scl, PIN_HIGH);
            n32_udelay(100);
            rt_pin_write(cfg->scl, PIN_LOW);
            n32_udelay(100);
        }
    }

    if (PIN_LOW == rt_pin_read(cfg->sda))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
#endif /* RT_USING_I2C_BITOPS */

#ifdef RT_USING_HARDWARE_I2C

#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

static uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

static int rt_i2c_read(rt_uint32_t i2c_periph, rt_uint16_t slave_address, rt_uint8_t* p_buffer, rt_uint16_t data_byte)
{
    I2CTimeout = I2CT_LONG_TIMEOUT;
    /* wait until I2C bus is idle */
    while (I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
            return 9;
    };

    I2C_ConfigAck((I2C_Module*)i2c_periph, ENABLE);

    /** Send START condition */
    I2C_GenerateStart((I2C_Module*)i2c_periph, ENABLE);

    I2CTimeout = I2CT_LONG_TIMEOUT;
    /* wait until SBSEND bit is set */
    while (!I2C_CheckEvent((I2C_Module*)i2c_periph, I2C_EVT_MASTER_MODE_FLAG)) // EV5
    {
        if ((I2CTimeout--) == 0)
            return 10;
    };

    /* send slave address to I2C bus */
    I2C_SendAddr7bit((I2C_Module*)i2c_periph, slave_address, I2C_DIRECTION_RECV);

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent((I2C_Module*)i2c_periph, I2C_EVT_MASTER_RXMODE_FLAG)) // EV6
    {
        if ((I2CTimeout--) == 0)
            return 6;
    };

    /* while there is data to be read */
    while (data_byte)
    {
        /* wait until the RBNE bit is set and clear it */
        if (I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_RXDATNE))
        {
            /* read a byte*/
            *p_buffer = I2C_RecvData((I2C_Module*)i2c_periph);

            /* point to the next location where the byte read will be saved */
            p_buffer++;

            /* decrement the read bytes counter */
            data_byte--;
            if (1 == data_byte)
            {
                /* disable acknowledge */
                I2C_ConfigAck((I2C_Module*)i2c_periph, DISABLE);
                /* send a stop condition to I2C bus */
                I2C_GenerateStop((I2C_Module*)i2c_periph, ENABLE);
            }
        }
    }

    /* wait until the stop condition is finished */
    while (I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_STOPF))
    {
        if ((I2CTimeout--) == 0)
            return 7;
    };

    /* enable acknowledge */
    I2C_ConfigAck((I2C_Module*)i2c_periph, ENABLE);

    I2C_ConfigNackLocation((I2C_Module*)i2c_periph,I2C_NACK_POS_CURRENT);

    return 0;
}

static int rt_i2c_write(rt_uint32_t i2c_periph, uint16_t slave_address, uint8_t* p_buffer, uint16_t data_byte)
{
    uint8_t* sendBufferPtr = p_buffer;
    I2CTimeout             = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
            return 4;
    };

    I2C_ConfigAck((I2C_Module*)i2c_periph, ENABLE);
    I2C_GenerateStart((I2C_Module*)i2c_periph, ENABLE);
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent((I2C_Module*)i2c_periph, I2C_EVT_MASTER_MODE_FLAG)) // EV5
    {
        if ((I2CTimeout--) == 0)
            return 5;
    };

    I2C_SendAddr7bit((I2C_Module*)i2c_periph, slave_address, I2C_DIRECTION_SEND);
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent((I2C_Module*)i2c_periph, I2C_EVT_MASTER_TXMODE_FLAG)) // EV6
    {
        if ((I2CTimeout--) == 0)
            return 6;
    };

    /* send data */
    while (data_byte-- > 0)
    {
        I2C_SendData((I2C_Module*)i2c_periph, *sendBufferPtr++);
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_CheckEvent((I2C_Module*)i2c_periph, I2C_EVT_MASTER_DATA_SENDING)) // EV8
        {
            if ((I2CTimeout--) == 0)
                return 7;
        };
    };

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent((I2C_Module*)i2c_periph, I2C_EVT_MASTER_DATA_SENDED)) // EV8-2
    {
        if ((I2CTimeout--) == 0)
            return 8;
    };
    I2C_GenerateStop((I2C_Module*)i2c_periph, ENABLE);
    return 0;
}



static rt_ssize_t rt_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    struct rt_i2c_bus *rt_i2c = (struct rt_i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_RD)
        {
            if (rt_i2c_read(rt_i2c->i2c_periph, msg->addr, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                goto out;
            }
        }
        else
        {
            if (rt_i2c_write(rt_i2c->i2c_periph, msg->addr, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                goto out;
            }
        }
    }

    ret = i;
    return ret;

out:
    LOG_E("send stop condition\n");

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    rt_i2c_xfer,
    RT_NULL,
    RT_NULL
};

#endif /* RT_USING_HARDWARE_I2C */

int rt_hw_i2c_init(void)
{
#ifdef RT_USING_I2C_BITOPS

    rt_size_t obj_num = sizeof(i2c_obj) / sizeof(struct n32_i2c);
    rt_err_t result;

    for(int i = 0; i < obj_num; i++)
    {
        i2c_obj[i].ops           = n32_bit_ops_default;
        i2c_obj[i].ops.data      = (void*)&soft_i2c_config[i];
        i2c_obj[i].i2c2_bus.priv = &i2c_obj[i].ops;

        n32_i2c_gpio_init(&i2c_obj[i]);
        result = rt_i2c_bit_add_bus(&i2c_obj[i].i2c2_bus, soft_i2c_config[i].bus_name);

        RT_ASSERT(result == RT_EOK);
        n32_i2c_bus_unlock(&soft_i2c_config[i]);

        rt_kprintf("software simulation %s init done, pin scl: %d, pin sda %d",
                   soft_i2c_config[i].bus_name,
                   soft_i2c_config[i].scl,
                   soft_i2c_config[i].sda);
    }
#endif /* RT_USING_I2C_BITOPS */

#ifdef RT_USING_HARDWARE_I2C

    GPIO_InitType GPIO_InitStructure;
    I2C_InitType  I2C_InitStructure;
#ifdef BSP_USING_I2C1
#define I2C1_SPEED  400000

    static struct rt_i2c_bus i2c_bus1;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* connect PB8 to I2C1_SCL, PB9 to I2C1_SDA */
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    GPIO_ConfigPinRemap(GPIO_RMP_I2C1, ENABLE);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    /* Enable I2C clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Confige I2C1_SCL(PB8) and  I2C1_SDA(PB9) */
    GPIO_InitStructure.Pin            = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_I2C1;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif

    I2C_DeInit(I2C1);
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = 0xff;
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = I2C1_SPEED; // 400000 400K

    I2C_Init(I2C1, &I2C_InitStructure);

    rt_memset((void *)&i2c_bus1, 0, sizeof(struct rt_i2c_bus));
    i2c_bus1.parent.ops = &i2c_ops;
    i2c_bus1.i2c_periph = (rt_uint32_t)I2C1;
    rt_i2c_bus_device_register(&i2c_bus1.parent, "i2c1");
#endif

#ifdef BSP_USING_I2C2
#define I2C2_SPEED  100000

    static struct rt_i2c_bus i2c_bus2;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C2, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* connect PB10 to I2C2_SCL, PB11 to I2C2_SDA */
    GPIO_InitStructure.Pin        = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    /* Enable I2C clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C2, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Confige I2C1_SCL(PB10) and  I2C1_SDA(PB11) */
    GPIO_InitStructure.Pin            = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_I2C2;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
#endif

    I2C_DeInit(I2C2);
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = 0xff;
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = I2C2_SPEED; // 100000 100K

    I2C_Init(I2C2, &I2C_InitStructure);

    rt_memset((void *)&i2c_bus2, 0, sizeof(struct rt_i2c_bus));
    i2c_bus2.parent.ops = &i2c_ops;
    i2c_bus2.i2c_periph = (rt_uint32_t)I2C2;
    rt_i2c_bus_device_register(&i2c_bus2.parent, "i2c2");
#endif

#if defined(SOC_N32G45X) || defined(SOC_N32WB452)
#ifdef BSP_USING_I2C3
#define I2C3_SPEED  100000

    static struct rt_i2c_bus i2c_bus3;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C3, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* connect PC0 to I2C3_SCL, PC1 to I2C3_SDA */
    GPIO_InitStructure.Pin        = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

    I2C_DeInit(I2C3);
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = 0xff;
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = I2C3_SPEED; // 100000 100K

    I2C_Init(I2C3, &I2C_InitStructure);

    rt_memset((void *)&i2c_bus3, 0, sizeof(struct rt_i2c_bus));
    i2c_bus3.parent.ops = &i2c_ops;
    i2c_bus3.i2c_periph = (rt_uint32_t)I2C3;
    rt_i2c_bus_device_register(&i2c_bus3.parent, "i2c3");
#endif

#ifdef BSP_USING_I2C4
#define I2C4_SPEED  100000

    static struct rt_i2c_bus i2c_bus4;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C4, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* connect PC6 to I2C4_SCL, PC7 to I2C4_SDA */
    GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

    I2C_DeInit(I2C4);
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = 0xff;
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = I2C4_SPEED; // 100000 100K

    I2C_Init(I2C4, &I2C_InitStructure);

    rt_memset((void *)&i2c_bus4, 0, sizeof(struct rt_i2c_bus));
    i2c_bus4.parent.ops = &i2c_ops;
    i2c_bus4.i2c_periph = (rt_uint32_t)I2C4;
    rt_i2c_bus_device_register(&i2c_bus4.parent, "i2c4");
#endif
#endif
#endif /* RT_USING_HARDWARE_I2C */

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
/* end of i2c driver */
