/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 * 2018-10-10     Ernest Chen  update and improve capability
 * 2018-11-11     Ernest Chen  add sharing SDA with different SCL
 * 2018-12-30     ppxiasky     Change to F4 Standard Library for simulation i2c 
 * 2019-01-04     ppxiasky     add hardware i2c.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "drv_i2c.h"
#include "stm32f4xx.h"
//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(...) rt_kprintf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(...)
#endif

/*user can change this*/
#define I2CBUS_NAME "i2c1"

/*user should change this to adapt specific board*/
#define I2C_SCL_PIN GPIO_Pin_8
#define I2C_SDA_PIN GPIO_Pin_9
#define I2C_PORT GPIOB
#define I2C_CLK_ENABLE()                RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE)
#define I2C_GPIOClk_ENABLE()        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

#define I2C_SDA_PORT GPIOB
#define I2C_SCL_PORT GPIOB
#define I2C1_SDA_PINSOURCE      GPIO_PinSource9
#define I2C1_SCL_PINSOURCE      GPIO_PinSource8


#define I2C_SCL_PINX    8
#define I2C_SDA_PINX    9

#define I2C_SDA_IN()  {I2C_SDA_PORT->MODER&=~(3<<(I2C_SDA_PINX*2));I2C_SDA_PORT->MODER|=0<<I2C_SDA_PINX*2;}
#define I2C_SDA_OUT() {I2C_SDA_PORT->MODER&=~(3<<(I2C_SDA_PINX*2));I2C_SDA_PORT->MODER|=1<<I2C_SDA_PINX*2;}

#define I2C_SCL_IN()  {I2C_SCL_PORT->MODER&=~(3<<(I2C_SCL_PINX*2));I2C_SCL_PORT->MODER|=0<<I2C_SCL_PINX*2;}
#define I2C_SCL_OUT() {I2C_SCL_PORT->MODER&=~(3<<(I2C_SCL_PINX*2));I2C_SCL_PORT->MODER|=1<<I2C_SCL_PINX*2;}

#ifdef RT_USING_I2C

static struct rt_i2c_bus_device i2c1_bus;

static void stm32_i2c_gpio_init()
{
    GPIO_InitTypeDef GPIO_Initure;

    I2C_CLK_ENABLE();
    I2C_GPIOClk_ENABLE();

    /*Configure I2C1*/
#ifdef RT_USING_I2C_BITOPS

    /*!< Configure I2C1 pins: SCL */
    GPIO_Initure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_Initure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Initure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Initure.GPIO_OType = GPIO_OType_OD;//GPIO_OType_PP;
    GPIO_Initure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(I2C_PORT, &GPIO_Initure);

    /*!< Configure sEE_I2C pins: SDA */
    GPIO_Initure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_PORT, &GPIO_Initure);

    GPIO_SetBits(I2C_PORT, I2C_SDA_PIN);
    GPIO_SetBits(I2C_PORT, I2C_SCL_PIN);
#else


    I2C_InitTypeDef  I2C_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* Reset sEE_I2C IP */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    /* Release reset signal of sEE_I2C IP */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    /*!< GPIO configuration */
    /* Connect PXx to I2C_SCL*/
    GPIO_PinAFConfig(I2C_PORT, I2C1_SCL_PINSOURCE, GPIO_AF_I2C1);
    /* Connect PXx to I2C_SDA*/
    GPIO_PinAFConfig(I2C_PORT, I2C1_SDA_PINSOURCE, GPIO_AF_I2C1);


    /*!< Configure I2C1 pins: SCL */
    GPIO_Initure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_Initure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Initure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Initure.GPIO_OType = GPIO_OType_OD;
    GPIO_Initure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(I2C_PORT, &GPIO_Initure);

    /*!< Configure sEE_I2C pins: SDA */
    GPIO_Initure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_PORT, &GPIO_Initure);


    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0xaa;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 100000;

    /* Apply I2C2 configuration after enabling it */
    I2C_Init(I2C1, &I2C_InitStructure);
    /* I2C2 Peripheral Enable */
    I2C_Cmd(I2C1, ENABLE);
#endif
}

#ifdef RT_USING_I2C_BITOPS
static void stm32_set_sda(void *data, rt_int32_t state)
{
    if (state)
    {
        I2C_SDA_PORT->BSRRL = I2C_SDA_PIN;
    }
    else
    {
        I2C_SDA_PORT->BSRRH = I2C_SDA_PIN;
    }
}



static void stm32_set_scl(void *data, rt_int32_t state)
{
    if (state)
    {
        I2C_SCL_PORT->BSRRL = I2C_SCL_PIN;
    }
    else
    {
        I2C_SCL_PORT->BSRRH = I2C_SCL_PIN;
    }
}

static rt_int32_t stm32_get_sda(void *data)
{
    if ((I2C_SDA_PORT->IDR & I2C_SDA_PIN))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



static rt_int32_t stm32_get_scl(void *data)
{
    if ((I2C_SCL_PORT->IDR & I2C_SCL_PIN))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static void stm32_udelay(rt_uint32_t us)
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

static const struct rt_i2c_bit_ops stm32_bit_ops =
{
    RT_NULL,
    stm32_set_sda,
    stm32_set_scl,
    stm32_get_sda,
    stm32_get_scl,
    stm32_udelay,
    5,
    5
};



/* if i2c is locked, the function will unlock it  */
static rt_err_t stm32_i2c_bus_unlock()
{
    rt_int32_t i = 0;

    if (0 == GPIO_ReadInputDataBit(I2C_PORT, I2C_SDA_PIN))
    {
        while (i++ < 9)
        {
            GPIO_WriteBit(I2C_PORT, I2C_SCL_PIN, Bit_RESET); //reset clk
            GPIO_WriteBit(I2C_PORT, I2C_SDA_PIN, Bit_RESET); //reset clk
            stm32_udelay(100);
            GPIO_WriteBit(I2C_PORT, I2C_SCL_PIN, Bit_SET);
            GPIO_WriteBit(I2C_PORT, I2C_SDA_PIN, Bit_SET);
            stm32_udelay(100);
        }
    }

    if (0 == GPIO_ReadInputDataBit(I2C_PORT, I2C_SCL_PIN) || 0 == GPIO_ReadInputDataBit(I2C_PORT, I2C_SDA_PIN))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}
#else
static rt_size_t stm32_i2c_recv_bytes(I2C_TypeDef* I2Cx, struct rt_i2c_msg *msg)
{
    rt_size_t bytes = 0;
    rt_size_t len = msg->len;

    while (len--)
    {
        while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));

        msg->buf[bytes++] = (rt_uint8_t)I2Cx->DR;

    }
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    return bytes;
}


static rt_size_t stm32_i2c_send_bytes(I2C_TypeDef* I2Cx, struct rt_i2c_msg *msg)
{
    rt_size_t bytes = 0;
    rt_size_t len = msg->len;

    while (len--)
    {
        I2Cx->DR = msg->buf[bytes++];
        while (! I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    return bytes;
}


static void I2C_SendAddress(I2C_TypeDef* I2Cx, struct rt_i2c_msg *msg)
{
    rt_uint16_t addr;
    rt_uint16_t flags = msg->flags;
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Test on the direction to set/reset the read/write bit */
    addr = msg->addr << 1;
    if (flags & RT_I2C_RD)
    {
        /* Set the address bit0 for read */
        addr |= 1;
    }
    /* Send the address */
    I2Cx->DR = addr;
}


static rt_size_t stm32_i2c_xfer(struct rt_i2c_bus_device *bus,
                                struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_int32_t i, ret;
    rt_uint16_t ignore_nack;
    I2C_Cmd(I2C1, ENABLE);
    I2C_GenerateSTART(I2C1, ENABLE);
    /* Test on EV5 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
        if (!(msg->flags & RT_I2C_NO_START))
        {
            if (i)
            {
                I2C_GenerateSTART(I2C1, ENABLE);
                /* Test on EV5 and clear it */
                while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
            }
            I2C_SendAddress(I2C1, msg);
            if (msg->flags & RT_I2C_RD)
                while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
            else
                while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

        }
        if (msg->flags & RT_I2C_RD)
        {
            if (!(msg->flags & RT_I2C_NO_READ_ACK))
                I2C_AcknowledgeConfig(I2C1, ENABLE);
            else
                I2C_AcknowledgeConfig(I2C1, DISABLE);
            ret = stm32_i2c_recv_bytes(I2C1, msg);
            if (ret >= 1)
                i2c_dbg("read %d byte%s\n",
                        ret, ret == 1 ? "" : "s");
            if (ret < msg->len)
            {
                if (ret >= 0)
                    ret = -RT_EIO;
                goto out;
            }
        }
        else
        {
            ret = stm32_i2c_send_bytes(I2C1, msg);
            if (ret >= 1)
                i2c_dbg("write %d byte%s\n",
                        ret, ret == 1 ? "" : "s");
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
    i2c_dbg("send stop condition\n");
    I2C_GenerateSTOP(I2C1, ENABLE);

    return ret;
}


static const struct rt_i2c_bus_device_ops i2c1_ops =
{
    stm32_i2c_xfer,
    RT_NULL,
    RT_NULL
};

#endif

int hw_i2c_init(void)
{

    stm32_i2c_gpio_init();

#ifdef RT_USING_I2C_BITOPS
    if (stm32_i2c_bus_unlock() != RT_EOK)
    {
        rt_kprintf("Failed to unlock i2c \n");
        return -RT_ERROR;
    }

    rt_memset((void *)&i2c1_bus, 0, sizeof(struct rt_i2c_bus_device));

    i2c1_bus.priv = (void *)&stm32_bit_ops;

    rt_i2c_bit_add_bus(&i2c1_bus, I2CBUS_NAME);

    return RT_EOK;
#else
    rt_memset((void *)&i2c1_bus, 0, sizeof(struct rt_i2c_bus_device));

    i2c1_bus.ops = &i2c1_ops;

    rt_i2c_bus_device_register(&i2c1_bus, I2CBUS_NAME);

    return RT_EOK;
#endif
}
INIT_BOARD_EXPORT(hw_i2c_init);

#endif /* end of i2c driver */
