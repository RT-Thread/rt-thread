/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-4-1       IceBear003   the first version
 */

#include "board.h"
#include "drv_i2c.h"

#ifdef BSP_USING_HWI2C

#define LOG_TAG "drv.hwi2c"
#include "drv_log.h"

#if !defined(BSP_USING_I2C1) && !defined(BSP_USING_I2C2)
#error "Please define at least one BSP_USING_I2Cx"
/* this driver can be disabled at menuconfig -> RT-Thread Components -> Device Drivers */
#endif

#define TIMEOUT 0xFF

#ifdef BSP_USING_I2C1
struct i2c_bus_device i2c_bus1;
#endif
#ifdef BSP_USING_I2C2
struct i2c_bus_device i2c_bus2;
#endif

static int i2c_read(I2C_TypeDef *i2c_periph,
                         rt_uint16_t addr,
                         rt_uint8_t flags,
                         rt_uint16_t len,
                         rt_uint8_t *buf)
{
    rt_uint16_t try = 0;
    while (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_BUSY))
        if (try++ >= TIMEOUT) return -1;

    I2C_GenerateSTART(i2c_periph, ENABLE);

    try = 0;
    while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))                       //EVT5
        if (try++ >= TIMEOUT) return -1;

    if(flags & RT_I2C_ADDR_10BIT)   //10-bit address mode
    {
        rt_uint8_t frame_head = 0xF0 + (addr >> 8) << 1;                                    //11110XX0
        I2C_SendData(i2c_periph, frame_head);                                               //FrameHead

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_ADDRESS10))                //EVT9
            if (try++ >= TIMEOUT) return -1;

        I2C_SendData(i2c_periph,0xff & addr);

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))     //EVT6
            if (try++ >= TIMEOUT) return -1;

        I2C_GenerateSTART(i2c_periph, ENABLE);                                              //Sr

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))                   //EVT5
            if (try++ >= TIMEOUT) return -1;

        I2C_SendData(i2c_periph,frame_head);                                                //Resend FrameHead
    }
    else
    {
        I2C_Send7bitAddress(i2c_periph, addr << 1, I2C_Direction_Receiver);
    }

    try = 0;
    while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))            //EVT6
        if (try++ >= TIMEOUT) return -1;

    while(len-- > 0)
    {

        try = 0;
        while (!I2C_GetFlagStatus(i2c_periph, I2C_FLAG_RXNE))                               //Got ACK For the Last Byte
            if (try++ >= TIMEOUT) return -1;

        *(buf++)=I2C_ReceiveData(i2c_periph);
    }

    I2C_GenerateSTOP(i2c_periph, ENABLE);
}

static int i2c_write(I2C_TypeDef *i2c_periph,
                            rt_uint16_t addr,
                            rt_uint8_t flags,
                            rt_uint8_t *buf,
                            rt_uint16_t len)
{
    rt_uint16_t try = 0;
    while (I2C_GetFlagStatus(i2c_periph, I2C_FLAG_BUSY))
        if (try++ >= TIMEOUT) return -1;

    I2C_GenerateSTART(i2c_periph, ENABLE);

    try = 0;
    while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_SELECT))                       //EVT5
        if (try++ >= TIMEOUT) return -1;

    if(flags & RT_I2C_ADDR_10BIT)   //10-bit address mode
    {
        I2C_SendData(i2c_periph,0xF0 + (addr >> 8) << 1);                                   //FrameHead 11110XX0

        try = 0;
        while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_MODE_ADDRESS10))                //EVT9
            if (try++ >= TIMEOUT) return -1;

        I2C_SendData(i2c_periph,0xff & addr);
    }
    else    //7-bit address mode
    {
        I2C_Send7bitAddress(i2c_periph, addr << 1, I2C_Direction_Transmitter);
    }

    try = 0;
    while (!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))         //EVT6
        if (try++ >= TIMEOUT) return -1;

    //Missing Evt8_1 (No definition)

    while(len-- > 0)
    {
        try = 0;
        while (!I2C_GetFlagStatus(i2c_periph, I2C_FLAG_TXE))                                //Got ACK For the Last Byte
            if (try++ >= TIMEOUT) return -1;

        I2C_SendData(i2c_periph,*(buf++));
    }

    try = 0;
    while(!I2C_CheckEvent(i2c_periph, I2C_EVENT_MASTER_BYTE_TRANSMITTING))                  //Last byte sent successfully
        if (try++ >= TIMEOUT) return -1;

    I2C_GenerateSTOP(i2c_periph, ENABLE);
}

rt_size_t i2c_master_xfer(struct rt_i2c_bus_device *bus,
                            struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
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
            i2c_read(i2c_bus_dev->periph,
                          msg->addr,
                          msg->flags,
                          msg->len,
                          msg->buf);
        }
        else
        {
            i2c_write(i2c_bus_dev->periph,
                           msg->addr,
                           msg->flags,
                           msg->buf,
                           msg->len);
        }
    }

    return index;
}

static const struct rt_i2c_bus_device_ops ch32_i2c_ops =
{
        .master_xfer = i2c_master_xfer,
        .slave_xfer = RT_NULL,                   //Not Used in i2c_core?
        .i2c_bus_control = RT_NULL
};

int rt_hw_i2c_init(struct i2c_config *config = &{5000, I2C_DutyCycle_2, 0, I2C_Ack_Disable, I2C_AcknowledgedAddress_7bit})
{
    int result = RT_EOK;

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

    I2C_InitTypeDef I2C_InitTSturcture = {0};
    I2C_StructInit(&I2C_InitTSturcture);
    I2C_InitTSturcture.I2C_ClockSpeed = config->clock_speed;
    I2C_InitTSturcture.I2C_DutyCycle = config->duty_cycle;
    I2C_InitTSturcture.I2C_OwnAddress1 = config->own_address;
    I2C_InitTSturcture.I2C_Ack = config->enable_ack ? I2C_Ack_Enable : I2C_Ack_Disable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = config->is_7_bit_address ? I2C_AcknowledgedAddress_7bit : I2C_AcknowledgedAddress_10bit;


#ifdef BSP_USING_I2C1

    i2c_bus1.periph = I2C1;

    //Clock & IO Initialization
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

    //I2C Initialization Config
    I2C_Init(I2C1, &I2C_InitTSturcture);
    I2C_Cmd(I2C1, ENABLE);

    //Hook to RT-Thread
    i2c_bus1.parent.ops = &ch32_i2c_ops;
    result += rt_i2c_bus_device_register(&i2c_bus1.parent, "i2c1");

#endif

#ifdef BSP_USING_I2C2

    i2c_bus2.periph = I2C2;

    //Clock & IO Initialization
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //I2C Initialization Config
    I2C_Init(I2C2, &I2C_InitTSturcture);
    I2C_Cmd(I2C2, ENABLE);

    //Hook to RT-Thread
    i2c_bus2.parent.ops = &ch32_i2c_ops;
    result += rt_i2c_bus_device_register(&i2c_bus2.parent, "i2c2");

#endif

    return result;
}

#endif //BSP_USING_HWI2C