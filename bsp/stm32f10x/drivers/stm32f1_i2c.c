/*
 * File      : stm32f1_i2c.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2017, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author                Notes
 * 2017-07-04     aubrcool@qq.com       1st version
 */
#include "stm32f10x.h"
#include "stm32f1_i2c.h"
#include <rtdevice.h>

#ifdef RT_USING_I2C

/* I2C SPE mask */
#define CR1_PE_Set              ((uint16_t)0x0001)
#define CR1_PE_Reset            ((uint16_t)0xFFFE)

/* I2C START mask */
#define CR1_START_Set           ((uint16_t)0x0100)
#define CR1_START_Reset         ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CR1_STOP_Set            ((uint16_t)0x0200)
#define CR1_STOP_Reset          ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CR1_ACK_Set             ((uint16_t)0x0400)
#define CR1_ACK_Reset           ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CR1_ENGC_Set            ((uint16_t)0x0040)
#define CR1_ENGC_Reset          ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CR1_SWRST_Set           ((uint16_t)0x8000)
#define CR1_SWRST_Reset         ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CR1_PEC_Set             ((uint16_t)0x1000)
#define CR1_PEC_Reset           ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CR1_ENPEC_Set           ((uint16_t)0x0020)
#define CR1_ENPEC_Reset         ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CR1_ENARP_Set           ((uint16_t)0x0010)
#define CR1_ENARP_Reset         ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CR1_NOSTRETCH_Set       ((uint16_t)0x0080)
#define CR1_NOSTRETCH_Reset     ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CR1_CLEAR_Mask          ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CR2_DMAEN_Set           ((uint16_t)0x0800)
#define CR2_DMAEN_Reset         ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CR2_LAST_Set            ((uint16_t)0x1000)
#define CR2_LAST_Reset          ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CR2_FREQ_Reset          ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OAR1_ADD0_Set           ((uint16_t)0x0001)
#define OAR1_ADD0_Reset         ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OAR2_ENDUAL_Set         ((uint16_t)0x0001)
#define OAR2_ENDUAL_Reset       ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OAR2_ADD2_Reset         ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CCR_FS_Set              ((uint16_t)0x8000)

/* I2C CCR mask */
#define CCR_CCR_Set             ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask               ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask               ((uint32_t)0x07000000)

#define I2CADDR  0x0A

enum
{
    EV_END = 0,
};

#ifdef RT_USING_I2C1
static struct stm32_i2c_bus stm32_i2c1 =
{
    .I2C = I2C1,
};
#endif /*RT_USING_I2C1*/
#ifdef RT_USING_I2C2
static struct stm32_i2c_bus stm32_i2c2 =
{
    .I2C = I2C2,
};
#endif /*RT_USING_I2C2*/

rt_inline rt_err_t stm32_i2c_wait_ev(struct stm32_i2c_bus *bus,
                                  rt_uint32_t ev, rt_uint32_t timeout)
{
    rt_uint32_t res = 0;
    rt_event_recv(&bus->ev, 0x01 << ev,
                  RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                  timeout, &res);
    if(res != ev)
    {
        return RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}
rt_inline void stm32_i2c_send_ev(struct stm32_i2c_bus *bus, rt_uint32_t ev)
{
      rt_event_send(&bus->ev, 0x01 << ev);
}

static rt_size_t stm_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                        struct rt_i2c_msg msgs[],
                                               rt_uint32_t num);
static rt_size_t stm_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                       struct rt_i2c_msg msgs[],
                                               rt_uint32_t num);
static rt_err_t stm_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                                      rt_uint32_t,
                                                     rt_uint32_t);

static const struct rt_i2c_bus_device_ops stm32_i2c_ops =
{
     stm_i2c_mst_xfer,
     stm_i2c_slv_xfer,
     stm_i2c_bus_control,
};
rt_inline void stm32_i2c_disable_nvic(I2C_TypeDef *I2C, rt_uint32_t value)
{
    NVIC_InitTypeDef  NVIC_InitStructure;

    rt_uint32_t evno, erno;
    if(I2C == I2C1)
    {
        evno = I2C1_EV_IRQn;
        erno = I2C1_ER_IRQn;
    }
    else
    {
        evno = I2C2_EV_IRQn;
        erno = I2C2_ER_IRQn;
    }
    NVIC_InitStructure.NVIC_IRQChannel = evno;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = value;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = erno;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = value;
    NVIC_Init(&NVIC_InitStructure);
}
static void stm32_i2c_nvic_Config(I2C_TypeDef *I2C)
{
    stm32_i2c_disable_nvic(I2C, ENABLE);
}
static rt_err_t stm_i2c_init(struct rt_i2c_bus_device *bus, rt_uint32_t bitrate)
{
    struct stm32_i2c_bus *stm32_i2c;
    I2C_InitTypeDef   I2C_InitStructure;

    RT_ASSERT(bus != RT_NULL);
    if(bitrate != 100000 && bitrate != 400000)
    {
        return RT_EIO;
    }

    stm32_i2c = (struct stm32_i2c_bus *) bus;
    I2C_Cmd(stm32_i2c->I2C, DISABLE);
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2CADDR;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = bitrate;

    I2C_Init(stm32_i2c->I2C, &I2C_InitStructure);
    I2C_Cmd(stm32_i2c->I2C, ENABLE);

    I2C_ITConfig(stm32_i2c->I2C, I2C_IT_EVT | I2C_IT_BUF | I2C_IT_ERR, ENABLE);

    stm32_i2c_nvic_Config(stm32_i2c->I2C);

    return RT_EOK;
}

static rt_size_t stm_i2c_mst_xfer(struct rt_i2c_bus_device *bus,
                                       struct rt_i2c_msg msgs[],
                                                rt_uint32_t num)
{
     struct stm32_i2c_bus *stm32_i2c;
     rt_uint32_t numbak = num;
     RT_ASSERT(bus != RT_NULL);
     stm32_i2c = (struct stm32_i2c_bus *) bus;

     stm32_i2c->msg = msgs;
     stm32_i2c->msg_ptr = 0;
     stm32_i2c->msg_cnt = num;
     stm32_i2c->dptr = 0;
     stm32_i2c->wait_stop = 0;

     I2C_GetLastEvent(stm32_i2c->I2C);
     while(stm32_i2c->msg_ptr < stm32_i2c->msg_cnt)
     {
          stm32_i2c->wait_stop = 0;
          if(!(stm32_i2c->msg[stm32_i2c->msg_ptr].flags & RT_I2C_NO_START))
          {
              stm32_i2c->I2C->CR1 |= CR1_START_Set;
          }
          stm32_i2c_wait_ev(stm32_i2c, EV_END, 1000);
     }
     stm32_i2c->msg = RT_NULL;
     stm32_i2c->msg_ptr = 0;
     stm32_i2c->msg_cnt = 0;
     stm32_i2c->dptr = 0;
     stm32_i2c->wait_stop = 0;
     return numbak;
}
static rt_size_t stm_i2c_slv_xfer(struct rt_i2c_bus_device *bus,
                                       struct rt_i2c_msg msgs[],
                                                rt_uint32_t num)
{
     return 0;
}
static rt_err_t stm_i2c_bus_control(struct rt_i2c_bus_device *bus,
                                                  rt_uint32_t cmd,
                                                  rt_uint32_t arg)
{
     return RT_ERROR;
}
rt_inline void stm32_i2c_ev_handler(struct stm32_i2c_bus *stm32_i2c)
{
    unsigned int I2C_Event;
    rt_uint8_t data = 0;
    struct rt_i2c_msg *pmsg;

    I2C_Event = I2C_GetLastEvent(stm32_i2c->I2C);

    if(!stm32_i2c->msg)
    {
        return;
    }
    // EV5 0x00030001
    if ((I2C_Event & I2C_EVENT_MASTER_MODE_SELECT) == I2C_EVENT_MASTER_MODE_SELECT)
    {
        // EV5 0x00030001
        pmsg = &stm32_i2c->msg[stm32_i2c->msg_ptr];
        if(pmsg->flags & RT_I2C_ADDR_10BIT)
        {
            data = ((pmsg->addr >> 8) << 1) | 0xF0;
        }
        else
        {
            data = pmsg->addr << 1;
        }
        if(pmsg->flags & RT_I2C_RD)
        {
            data |= 0x01;
        }
        stm32_i2c->I2C->DR = data;
        if(!(pmsg->flags & RT_I2C_RD))
        {
             return;
        }
        if(pmsg->len > 1)
        {
             stm32_i2c->I2C->CR1 |= CR1_ACK_Set;
             return;
        }
    }
    else if((I2C_Event & I2C_EVENT_MASTER_MODE_ADDRESS10) ==
                                        I2C_EVENT_MASTER_MODE_ADDRESS10)
    {
        // EV9
        data = pmsg->addr & 0xFF;
        stm32_i2c->I2C->DR = data;
    }
    else if((I2C_Event & I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) ==
                                       I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)
    {
        //EVT 6 SEND  0x00070082
    }
    else if ((I2C_Event & I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) ==
                                          I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)
    {
        //EVT 6 RECE  0x00030002
        pmsg = &stm32_i2c->msg[stm32_i2c->msg_ptr];
        if(!(pmsg->flags & RT_I2C_RD))
        {
             return;
        }
        if(pmsg->len > 1)
        {
             return;
        }
        if(stm32_i2c->msg_ptr < stm32_i2c->msg_cnt - 1)
        {
             return;
        }
        else if((pmsg[1].flags & RT_I2C_NO_START))
        {
             return;
        }
        stm32_i2c->I2C->CR1 |= CR1_STOP_Set;
        stm32_i2c->I2C->CR1 &= CR1_ACK_Reset;
    }
    else if ((I2C_Event & I2C_EVENT_MASTER_BYTE_RECEIVED) ==
                                                   I2C_EVENT_MASTER_BYTE_RECEIVED)
    {
        // EVT 7  0x00030040
        pmsg = &stm32_i2c->msg[stm32_i2c->msg_ptr];

        if(pmsg->len && (pmsg->flags & RT_I2C_RD))
        {
            pmsg->buf[stm32_i2c->dptr] = stm32_i2c->I2C->DR;
            stm32_i2c->dptr++;
            pmsg->len--;
        }
        if(pmsg->len == 1 && (pmsg->flags & RT_I2C_RD))
        {
            if(stm32_i2c->msg_ptr >= stm32_i2c->msg_cnt - 1)
            {
                stm32_i2c->I2C->CR1 &= CR1_ACK_Reset;
                stm32_i2c->I2C->CR1 |= CR1_STOP_Set;
            }
            else if(!(pmsg[1].flags & RT_I2C_NO_START))
            {
                stm32_i2c->I2C->CR1 &= CR1_ACK_Reset;
                stm32_i2c->I2C->CR1 |= CR1_STOP_Set;
            }
        }
        if(pmsg->len)
        {
            return;
        }
        stm32_i2c->dptr = 0;
        stm32_i2c->msg_ptr++;
        if(stm32_i2c->msg_ptr < stm32_i2c->msg_cnt)
        {
            return;
        }
        stm32_i2c->I2C->CR1 |= CR1_ACK_Set;
        stm32_i2c_send_ev(stm32_i2c, EV_END);
    }
    else if((I2C_Event & I2C_EVENT_MASTER_BYTE_TRANSMITTING) ==
                                               I2C_EVENT_MASTER_BYTE_TRANSMITTING)
    {
        //EVT8  0x00070080
        if(stm32_i2c->wait_stop == 0xAAAA5555)
        {
            stm32_i2c->wait_stop = 0;
            stm32_i2c->I2C->CR1 |= CR1_STOP_Set;
            stm32_i2c_send_ev(stm32_i2c, EV_END);
            return;
        }
        if(stm32_i2c->wait_stop == 0x5555AAAA)
        {   //restart cond
            stm32_i2c->wait_stop = 0;
            stm32_i2c_send_ev(stm32_i2c, EV_END);
            return;
        }

        pmsg = &stm32_i2c->msg[stm32_i2c->msg_ptr];
        if(!(pmsg->flags & RT_I2C_RD) && pmsg->len)
        {
            stm32_i2c->I2C->DR = pmsg->buf[stm32_i2c->dptr];
            stm32_i2c->dptr++;
            pmsg->len--;
        }

        if(!(pmsg->flags & RT_I2C_RD) && pmsg->len)
        {
             return;
        }

        if(stm32_i2c->msg_ptr < stm32_i2c->msg_cnt - 1 && pmsg->len == 0)
        {
           stm32_i2c->msg_ptr++;
           stm32_i2c->dptr = 0;
           pmsg = &stm32_i2c->msg[stm32_i2c->msg_ptr];
           if(pmsg->flags & RT_I2C_NO_START)
           {
               return;
           }
           else
           {
               stm32_i2c->wait_stop == 0x5555AAAA;
               return;
           }
        }
        if(stm32_i2c->msg_ptr < stm32_i2c->msg_cnt && pmsg->len == 0)
        {
           stm32_i2c->msg_ptr++;
           stm32_i2c->dptr = 0;
        }
        stm32_i2c->wait_stop = 0xAAAA5555;
    }
}

#ifdef RT_USING_I2C1
void I2C1_EV_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    stm32_i2c_ev_handler(&stm32_i2c1);

    /* leave interrupt */
    rt_interrupt_leave();

}
#endif /*RT_USING_I2C1*/

#ifdef RT_USING_I2C2
void I2C2_EV_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    stm32_i2c_ev_handler(&stm32_i2c2);

    /* leave interrupt */
    rt_interrupt_leave();

}
#endif /*RT_USING_I2C2*/

rt_inline void stm32_i2c_er_handler(struct stm32_i2c_bus *stm32_i2c)
{
    if (I2C2->SR1 & 1 << 10)
    {
        I2C2->SR1 &= ~(1 << 10);
    }
    if (I2C2->SR1 & 1 << 14)
    {
        I2C2->SR1 &= ~(1 << 14);
    }
    if (I2C2->SR1 & 1 << 11)
    {
        I2C2->SR1 &= ~(1 << 11);
    }
    if (I2C2->SR1 & 1 << 9)
    {
        I2C2->SR1 &= ~(1 << 9);
    }
    if (I2C2->SR1 & 1 << 8)
    {
        I2C2->SR1 &= ~(1 << 8);
    }
}

#ifdef RT_USING_I2C1
void I2C1_ER_IRQHandler(void)       //I2C2 Error Interrupt
{
    /* enter interrupt */
    rt_interrupt_enter();

    stm32_i2c_er_handler(&stm32_i2c1);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /*RT_USING_I2C1*/

#ifdef RT_USING_I2C2
void I2C2_ER_IRQHandler(void)       //I2C2 Error Interrupt
{
    /* enter interrupt */
    rt_interrupt_enter();

    stm32_i2c_er_handler(&stm32_i2c2);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /*RT_USING_I2C2*/

rt_err_t stm32_i2c_register(I2C_TypeDef *I2C, rt_uint32_t bitrate,
                                        const char * i2c_bus_name)
{
    struct stm32_i2c_bus *pi2c;
    rt_err_t res;

#ifdef RT_USING_I2C1
    if(I2C == I2C1)
    {
        pi2c = &stm32_i2c1;
        RCC_APB2PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    }
    else
#endif /*RT_USING_I2C1*/
#ifdef RT_USING_I2C2
    if(I2C == I2C2)
    {
        pi2c = &stm32_i2c2;
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    }
    else
#endif /*RT_USING_I2C2*/
    {
        return RT_ENOSYS;
    }
    if(rt_event_init(&pi2c->ev, i2c_bus_name, RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        return RT_ERROR;
    }
    pi2c->parent.ops = &stm32_i2c_ops;
    if((res = stm_i2c_init(&pi2c->parent, bitrate)) != RT_EOK)
    {
         return res;
    }
    return rt_i2c_bus_device_register(&pi2c->parent, i2c_bus_name);
}
#endif /*RT_USING_I2C*/
