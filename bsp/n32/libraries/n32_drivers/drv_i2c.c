/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file drv_i2c.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include <rthw.h>
#include <rtthread.h>
#include "drv_i2c.h"
#include "board.h"

#ifdef RT_USING_I2C

#include <rtdevice.h>

#define DBG_TAG               "drv.I2C"
#ifdef RT_I2C_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif
#include <rtdbg.h>

#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))



#ifdef RT_USING_I2C_BITOPS

/*user can change this*/
#define I2C_BUS_NAME  "i2c1"

/*user should change this to adapt specific board*/
#define I2C_SCL_PIN          GPIO_PIN_8
#define I2C_SCL_PORT         GPIOB
#define I2C_SCL_CLK          RCC_APB2_PERIPH_GPIOB
#define I2C_SDA_PIN          GPIO_PIN_9
#define I2C_SDA_PORT         GPIOB
#define I2C_SDA_CLK          RCC_APB2_PERIPH_GPIOB

struct n32_i2c_bit_data
{
    struct
    {
        rt_uint32_t clk;
        GPIO_Module* port;
        rt_uint32_t pin;
    }scl, sda;
};

static void gpio_set_sda(void *data, rt_int32_t state)
{
    struct n32_i2c_bit_data* bd = data;

    if (state)
    {
        GPIO_SetBits((GPIO_Module*)bd->sda.port, bd->sda.pin);
    }
    else
    {
        GPIO_ResetBits((GPIO_Module*)bd->sda.port, bd->sda.pin);
    }
}

static void gpio_set_scl(void *data, rt_int32_t state)
{
    struct n32_i2c_bit_data* bd = data;
    if (state)
    {
        GPIO_SetBits((GPIO_Module*)bd->scl.port, bd->scl.pin);
    }
    else
    {
        GPIO_ResetBits((GPIO_Module*)bd->scl.port, bd->scl.pin);
    }
}

static rt_int32_t gpio_get_sda(void *data)
{
    struct n32_i2c_bit_data* bd = data;

    return GPIO_ReadInputDataBit((GPIO_Module*)bd->sda.port, bd->sda.pin);
}

static rt_int32_t gpio_get_scl(void *data)
{
    struct n32_i2c_bit_data* bd = data;

    return GPIO_ReadInputDataBit((GPIO_Module*)bd->scl.port, bd->scl.pin);
}

static void gpio_udelay(rt_uint32_t us)
{
    RCC_ClocksType* RCC_Clocks = {0};
    RCC_GetClocksFreqValue(RCC_Clocks);
    int i = ( RCC_Clocks->SysclkFreq / 4000000 * us);
    while(i)
    {
        i--;
    }
}

static void drv_i2c_gpio_init(const struct n32_i2c_bit_data* bd)
{
    RCC_EnableAPB2PeriphClk(bd->sda.clk | bd->scl.clk, ENABLE);
    GPIOInit((GPIO_Module*)bd->sda.port, GPIO_Mode_Out_OD, GPIO_Speed_10MHz, bd->sda.pin);
    GPIOInit((GPIO_Module*)bd->scl.port, GPIO_Mode_Out_OD, GPIO_Speed_10MHz, bd->scl.pin);

    GPIO_SetBits((GPIO_Module*)bd->sda.port, bd->sda.pin);
    GPIO_SetBits((GPIO_Module*)bd->scl.port, bd->scl.pin);
}

#else /* use hardware i2c */

static uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

static int rt_i2c_read(rt_uint32_t i2c_periph, rt_uint16_t slave_address, rt_uint8_t* p_buffer, rt_uint16_t data_byte)
{
    I2CTimeout = I2CT_LONG_TIMEOUT;
    /* wait until I2C bus is idle */
    while(I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_BUSY))
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

//    /* clear the ADDSEND bit */
//    I2C_ClrFlag((I2C_Module*)i2c_periph,I2C_FLAG_ADDRF);

//    if(1 == data_byte){
//        /* disable acknowledge */
//        I2C_ConfigAck((I2C_Module*)i2c_periph,DISABLE);
//        /* send a stop condition to I2C bus */
//        I2C_GenerateStop(I2C1, ENABLE);
//    }

    /* while there is data to be read */
    while(data_byte)
    {
        /* wait until the RBNE bit is set and clear it */
        if(I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_RXDATNE))
        {
            /* read a byte*/
            *p_buffer = I2C_RecvData((I2C_Module*)i2c_periph);

            /* point to the next location where the byte read will be saved */
            p_buffer++; 

            /* decrement the read bytes counter */
            data_byte--;
            if(1 == data_byte)
            {
                /* disable acknowledge */
                I2C_ConfigAck((I2C_Module*)i2c_periph, DISABLE);
                /* send a stop condition to I2C bus */
                I2C_GenerateStop((I2C_Module*)i2c_periph, ENABLE);
            }
        }
    }

    /* wait until the stop condition is finished */
    while(I2C_GetFlag((I2C_Module*)i2c_periph, I2C_FLAG_STOPF))
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

    // send data
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



static rt_size_t rt_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
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

#endif /* RT_USING_I2C_BITOPS */

int rt_hw_i2c_init(void)
{
#ifdef RT_USING_I2C_BITOPS
    {
        static struct rt_i2c_bus_device i2c_device;
        static const struct n32_i2c_bit_data _i2c_bdata =
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

#ifdef BSP_USING_I2C1
#define I2C1_SPEED  400000

    static struct rt_i2c_bus i2c_bus1;
    I2C_InitType I2C_InitStructure;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_ConfigPinRemap(GPIO_RMP_I2C1, ENABLE);
    /* connect PB8 to I2C1_SCL, PB9 to I2C1_SDA */
    GPIOInit(GPIOB, GPIO_Mode_AF_OD, GPIO_Speed_50MHz, GPIO_PIN_8 | GPIO_PIN_9);
    
    /* enable I2C clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    
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
    I2C_InitType I2C_InitStructure;

    /* enable I2C clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C2, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* connect PB10 to I2C2_SCL, PB11 to I2C2_SDA */
    GPIOInit(GPIOB, GPIO_Mode_AF_OD, GPIO_Speed_50MHz, GPIO_PIN_10 | GPIO_PIN_11);

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

#ifdef BSP_USING_I2C3
#define I2C3_SPEED  100000

    static struct rt_i2c_bus i2c_bus3;
    I2C_InitType I2C_InitStructure;

    /* enable I2C clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C3, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* connect PC0 to I2C3_SCL, PC1 to I2C3_SDA */
    GPIOInit(GPIOC, GPIO_Mode_AF_OD, GPIO_Speed_50MHz, GPIO_PIN_0 | GPIO_PIN_1);
    
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
    I2C_InitType I2C_InitStructure;

    /* enable I2C clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_I2C4, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* connect PC6 to I2C4_SCL, PC7 to I2C4_SDA */
    GPIOInit(GPIOC, GPIO_Mode_AF_OD, GPIO_Speed_50MHz, GPIO_PIN_6 | GPIO_PIN_7);

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

#endif /* RT_USING_I2C_BITOPS */

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
/* end of i2c driver */
