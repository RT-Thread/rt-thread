/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-06-05     tanek        first implementation.
 * 2018-04-19     misonyo      Porting for gd32f30x
 * 2019-03-31     xuzhuoyi     Porting for gd32e230
 */

#include "drv_i2c.h"
#include <rtthread.h>
#include "gd32e230.h"

#ifdef RT_USING_I2C

#include <rtdevice.h>

#define DBG_TAG               "drv.I2C"
#ifdef RT_I2C_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif
#include <rtdbg.h>

#ifdef RT_USING_I2C_BITOPS

/*user can change this*/
#define I2C_BUS_NAME  "i2c2"

/*user should change this to adapt specific board*/
#define I2C_SCL_PIN          GPIO_PIN_4
#define I2C_SCL_PORT         GPIOE
#define I2C_SCL_CLK          RCU_GPIOE
#define I2C_SDA_PIN          GPIO_PIN_5
#define I2C_SDA_PORT         GPIOE
#define I2C_SDA_CLK          RCU_GPIOE

struct gd32_i2c_bit_data
{
    struct
    {
        rcu_periph_enum clk;
        rt_uint32_t port;
        rt_uint32_t pin;
    }scl, sda;
};

static void gpio_set_sda(void *data, rt_int32_t state)
{
    struct gd32_i2c_bit_data* bd = data;

    if (state)
    {
        gpio_bit_set(bd->sda.port, bd->sda.pin);
    }
    else
    {
        gpio_bit_reset(bd->sda.port, bd->sda.pin);
    }
}

static void gpio_set_scl(void *data, rt_int32_t state)
{
    struct gd32_i2c_bit_data* bd = data;
    if (state)
    {
        gpio_bit_set(bd->scl.port, bd->scl.pin);
    }
    else
    {
        gpio_bit_reset(bd->scl.port, bd->scl.pin);
    }
}

static rt_int32_t gpio_get_sda(void *data)
{
    struct gd32_i2c_bit_data* bd = data;

    return gpio_input_bit_get(bd->sda.port, bd->sda.pin);
}

static rt_int32_t gpio_get_scl(void *data)
{
    struct gd32_i2c_bit_data* bd = data;

    return gpio_input_bit_get(bd->scl.port, bd->scl.pin);
}

static void gpio_udelay(rt_uint32_t us)
{
    int i = ( rcu_clock_freq_get(CK_SYS) / 4000000 * us);
    while(i)
    {
        i--;
    }
}

static void drv_i2c_gpio_init(const struct gd32_i2c_bit_data* bd)
{
    rcu_periph_clock_enable(bd->sda.clk);
    rcu_periph_clock_enable(bd->scl.clk);
    gpio_init(bd->sda.port, GPIO_MODE_OUT_OD, GPIO_OSPEED_10MHZ, bd->sda.pin);
    gpio_init(bd->scl.port, GPIO_MODE_OUT_OD, GPIO_OSPEED_10MHZ, bd->scl.pin);

    gpio_bit_set(bd->sda.port, bd->sda.pin);
    gpio_bit_set(bd->scl.port, bd->scl.pin);
}

#else /* use hardware i2c */

struct gd32_i2c_bus
{
    struct rt_i2c_bus_device parent;
    rt_uint32_t i2c_periph;
};

static int gd32_i2c_read(rt_uint32_t i2c_periph, rt_uint16_t slave_address, rt_uint8_t* p_buffer, rt_uint16_t data_byte)
{
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);

    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));

    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, slave_address<<1, I2C_RECEIVER);

    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);

    if(1 == data_byte){
        /* disable acknowledge */
        i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
    }

    /* while there is data to be read */
    while(data_byte)
    {
        /* wait until the RBNE bit is set and clear it */
        if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE))
        {
            /* read a byte from the EEPROM */
            *p_buffer = i2c_data_receive(i2c_periph);

            /* point to the next location where the byte read will be saved */
            p_buffer++;

            /* decrement the read bytes counter */
            data_byte--;
            if(1 == data_byte)
            {
                /* disable acknowledge */
                i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
                /* send a stop condition to I2C bus */
                i2c_stop_on_bus(i2c_periph);
            }
        }
    }

    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);

    /* enable acknowledge */
    i2c_ack_config(i2c_periph,I2C_ACK_ENABLE);

    i2c_ackpos_config(i2c_periph,I2C_ACKPOS_CURRENT);

    return 0;
}

static int gd32_i2c_write(rt_uint32_t i2c_periph, uint16_t slave_address, uint8_t* p_buffer, uint16_t data_byte)
{
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);

    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));

    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, slave_address<<1, I2C_TRANSMITTER);

    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));

    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);

    /* wait until the transmit data buffer is empty */
    while(SET != i2c_flag_get( i2c_periph , I2C_FLAG_TBE));

    /* while there is data to be read */
    while(data_byte)
    {
        i2c_data_transmit(i2c_periph, *p_buffer);

        /* point to the next byte to be written */
        p_buffer++;

        /* decrement the write bytes counter */
        data_byte --;

        /* wait until BTC bit is set */
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    }

        /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);

    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);

    return 0;
}

static rt_ssize_t gd32_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    struct gd32_i2c_bus *gd32_i2c = (struct gd32_i2c_bus *)bus;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];

        if (msg->flags & RT_I2C_ADDR_10BIT)
        {
            i2c_mode_addr_config(gd32_i2c->i2c_periph,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_10BITS,0);
        }
        else
        {
            i2c_mode_addr_config(gd32_i2c->i2c_periph,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,0);
        }
        if (msg->flags & RT_I2C_RD)
        {
            if (gd32_i2c_read(gd32_i2c->i2c_periph, msg->addr, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                goto out;
            }
        }
        else
        {
            if (gd32_i2c_write(gd32_i2c->i2c_periph, msg->addr, msg->buf, msg->len) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!");
                goto out;
            }
        }
    }

    ret = i;

out:
    LOG_D("send stop condition");

    return ret;
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    gd32_i2c_xfer,
    RT_NULL,
    RT_NULL
};

#endif /* RT_USING_I2C_BITOPS */

int rt_hw_i2c_init(void)
{
#ifdef RT_USING_I2C_BITOPS
    {
        static struct rt_i2c_bus_device i2c_device;
        static const struct gd32_i2c_bit_data _i2c_bdata =
        {
            /* SCL */
            {    I2C_SCL_CLK, I2C_SCL_PORT, I2C_SCL_PIN},
            /* SDA */
            {    I2C_SDA_CLK, I2C_SDA_PORT, I2C_SDA_PIN},
        };

        static const struct rt_i2c_bit_ops _i2c_bit_ops =
        {
            (void*)&_i2c_bdata,
            gpio_set_sda,
            gpio_set_scl,
            gpio_get_sda,
            gpio_get_scl,
            gpio_udelay,
            1,
            100
        };

        drv_i2c_gpio_init(&_i2c_bdata);

        i2c_device.priv = (void *)&_i2c_bit_ops;
        rt_i2c_bit_add_bus(&i2c_device, I2C_BUS_NAME);
    }

#else   /* register hardware I2C */

#ifdef RT_USING_I2C0
#define I2C0_SPEED  100000

    static struct gd32_i2c_bus gd32_i2c0;
    /* enable GPIOB clock */
    rcu_periph_clock_enable(RCU_GPIOB);

    /* connect PB6 to I2C0_SCL */
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_6);
    /* connect PB7 to I2C0_SDA */
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_7);
    /* configure GPIO pins of I2C0 */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_6);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_6);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_7);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_7);

    /* enable I2C clock */
    rcu_periph_clock_enable(RCU_I2C0);
    /* configure I2C clock */
    i2c_clock_config(I2C0,I2C0_SPEED,I2C_DTCY_2);

    i2c_enable(I2C0);
    /* enable acknowledge */
    i2c_ack_config(I2C0,I2C_ACK_ENABLE);

    rt_memset((void *)&gd32_i2c0, 0, sizeof(struct gd32_i2c_bus));
    gd32_i2c0.parent.ops = &i2c_ops;
    gd32_i2c0.i2c_periph = I2C0;
    rt_i2c_bus_device_register(&gd32_i2c0.parent, "i2c0");
#endif

#ifdef RT_USING_I2C1
#define I2C1_SPEED  100000

    static struct gd32_i2c_bus gd32_i2c1;
    /* enable GPIOB clock */
    rcu_periph_clock_enable(RCU_GPIOB);

    /* connect PB10 to I2C1_SCL */
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_10);
    /* connect PB11 to I2C1_SDA */
    gpio_af_set(GPIOB, GPIO_AF_1, GPIO_PIN_11);
    /* configure GPIO pins of I2C1 */
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_10);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_11);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_11);

    /* enable I2C clock */
    rcu_periph_clock_enable(RCU_I2C1);
    /* configure I2C clock */
    i2c_clock_config(I2C1,I2C1_SPEED,I2C_DTCY_2);

    i2c_enable(I2C1);
    /* enable acknowledge */
    i2c_ack_config(I2C1,I2C_ACK_ENABLE);

    rt_memset((void *)&gd32_i2c1, 0, sizeof(struct gd32_i2c_bus));
    gd32_i2c1.parent.ops = &i2c_ops;
    gd32_i2c1.i2c_periph = I2C1;
    rt_i2c_bus_device_register(&gd32_i2c1.parent, "i2c1");
#endif

#endif /* RT_USING_I2C_BITOPS */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
/* end of i2c driver */
