/*
 * File      : nuc97x_i2c.c
 * This file is part of RT-Thread RTOS
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/05/28     Urey         first implementation
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "nuc97x.h"

#define i2cDisable(I2Cx)     (I2Cx->CSR = 0x00)/* Disable i2c core and interrupt */
#define i2cEnable(I2Cx)      (I2Cx->CSR = 0x03)  /* Enable i2c core and interrupt  */

#define i2cIsBusFree(I2Cx)   (((I2Cx->SWR & 0x18) == 0x18) && ((I2Cx->CSR & 0x0400) == 0) ? 1 : 0)


/*
 *  msg_end_type: The bus control which need to be send at end of transfer.
 *  @MSG_END_STOP: Send stop pulse at end of transfer.
 *  @MSG_END_REPEAT_START: Send repeat start at end of transfer.
 */
enum msg_end_type
{
    MSG_END_STOP,
    MSG_END_CONTINUE,
    MSG_END_REPEAT_START,
};


struct nuc97x_i2c_bus
{
    struct rt_i2c_bus_device parent;

    I2C_Typedef            *I2Cx;
    struct rt_completion    completion;

    struct rt_i2c_msg      *msg;
    enum msg_end_type       end_type;
    rt_bool_t               bNackValid;
    rt_uint16_t     pos;
    int             irqno;
    int             error;
    int             rate;
};

static int32_t _i2cSetSpeed(I2C_Typedef *I2Cx, int32_t sp)
{
    int32_t div;

    if (sp != 100 && sp != 400)
        return (I2C_ERR_NOTTY);

    div = I2C_INPUT_CLOCK / (sp * 5) - 1;

    I2Cx->DIVIDER = div & 0xffff;

    return 0;
}


static void nux97x_i2c_isr(int vector,void *param)
{
    rt_uint32_t csr, val;

    struct nuc97x_i2c_bus *i2c = (struct nuc97x_i2c_bus *)param;

    csr = i2c->I2Cx->CSR;
    i2c->I2Cx->CSR |= 0x04;     /* clear interrupt flag */

    if ((csr & 0x800) && i2c->bNackValid)
    { /* NACK only valid in WRITE */
        i2c->error = I2C_ERR_NACK;
        i2c->I2Cx->CMDR = I2C_CMD_STOP;
        rt_completion_done(&i2c->completion);
    }
    else if(csr & 0x200)
    { /* Arbitration lost */
        rt_kprintf("Arbitration lost\n");
        i2c->error = I2C_ERR_LOSTARBITRATION;
        rt_completion_done(&i2c->completion);
    }
    else if(!(csr & 0x100))
    {/* transmit complete */
        if(i2c->msg->flags & RT_I2C_RD)
        {
            i2c->msg->buf[i2c->pos++] = i2c->I2Cx->RXR;

            if(i2c->pos < i2c->msg->len)
            {
                if(i2c->pos == (i2c->msg->len - 1))
                {/* last character */
                    if(i2c->end_type == MSG_END_STOP)
                        i2c->I2Cx->CMDR = I2C_CMD_READ | I2C_CMD_STOP | I2C_CMD_NACK;
                    else
                        i2c->I2Cx->CMDR = I2C_CMD_READ | I2C_CMD_NACK;
                }
                else
                {
                    i2c->I2Cx->CMDR = I2C_CMD_READ;
                }
            }
            else
            {
                rt_kprintf("i2c read done!\n");
                rt_completion_done(&i2c->completion);
            }
        }
        else
        {
            if(i2c->pos < i2c->msg->len)
            {
                i2c->I2Cx->TXR = i2c->msg->buf[i2c->pos];

                if (i2c->pos == (i2c->msg->len - 1))
                {/* last character */
                    if(i2c->end_type == MSG_END_STOP)
                        i2c->I2Cx->CMDR = I2C_CMD_WRITE | I2C_CMD_STOP;
                    else
                        i2c->I2Cx->CMDR = I2C_CMD_WRITE;
                }
                else
                {
                    i2c->I2Cx->CMDR = I2C_CMD_WRITE;
                }
                i2c->pos++;
            }
            else
            {
                rt_kprintf("i2c write done!\n");
                rt_completion_done(&i2c->completion);
            }
        }
    }
}

static int nux97x_xfer_read(struct nuc97x_i2c_bus *i2c, struct rt_i2c_msg *msg, enum msg_end_type end_type)
{
    int ret = 0;
    int timeout = I2C_TIMEOUT;

    if (!i2cIsBusFree(i2c->I2Cx))
        return (I2C_ERR_BUSY);
    i2c->msg = msg;

    //send address
    i2c->I2Cx->TXR  = msg->addr;
    if(end_type == MSG_END_CONTINUE)
        i2c->I2Cx->CMDR = I2C_CMD_WRITE;
    else
        i2c->I2Cx->CMDR = I2C_CMD_START | I2C_CMD_WRITE;

    //wait for transmit complete
    rt_completion_wait(&i2c->completion,I2C_TIMEOUT);

    if(i2c->error != I2C_ERR_NOERROR)
        return 0;
    else
        return msg->len;
}

static int nux97x_xfer_write(struct nuc97x_i2c_bus *i2c, struct rt_i2c_msg *msg, enum msg_end_type end_type)
{
    int ret = 0;
    int timeout = I2C_TIMEOUT;

    if (!i2cIsBusFree(i2c->I2Cx))
        return (I2C_ERR_BUSY);
    i2c->msg = msg;
    //send address
    i2c->I2Cx->TXR  = msg->addr;
    if(end_type == MSG_END_CONTINUE)
        i2c->I2Cx->CMDR = I2C_CMD_WRITE;
    else
        i2c->I2Cx->CMDR = I2C_CMD_START | I2C_CMD_WRITE;
    i2c->bNackValid = RT_TRUE;
    i2c->error      = I2C_ERR_NOERROR;
    i2c->pos        = 0;

    //wait for transmit complete
    rt_completion_wait(&i2c->completion,I2C_TIMEOUT);

    if(i2c->error != I2C_ERR_NOERROR)
        return 0;
    else
        return msg->len;
}
static rt_size_t nux97x_i2c_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    int i;
    int ret = RT_EOK;
    struct nuc97x_i2c_bus *i2c = (struct nuc97x_i2c_bus *)bus;

    i2cEnable(i2c->I2Cx);

    for (i = 0; i < num; i++)
    {
        enum msg_end_type end_type = MSG_END_STOP;

        if (i < (num - 1))
        {
            if (msgs[i + 1].flags & RT_I2C_NO_START)
            {
                end_type = MSG_END_CONTINUE;        /* have no STOP and START */
            }
            else
            {
                end_type = MSG_END_REPEAT_START;    /* have no STOP but have RESTART */
            }
        }

        /* initialize completion */
        rt_completion_init(&(i2c->completion));

        if (msgs[i].flags & RT_I2C_RD)
        {
            ret = nux97x_xfer_read(i2c, &msgs[i], end_type);
        }
        else
        {
            ret = nux97x_xfer_write(i2c, &msgs[i], end_type);
        }

        if (ret < 0)
        {
            goto _error_exit;
        }
    }

    i2cDisable(i2c->I2Cx);
    return num;
_error_exit:
    return 0;
}

static const struct rt_i2c_bus_device_ops nuc97x_i2c_ops =
{
    nux97x_i2c_xfer,
    RT_NULL,
    RT_NULL
};

#ifdef BOARD_USING_I2C0
static struct nuc97x_i2c_bus nuc97x_i2c0 =
{
    .I2Cx = I2C0,
};
#endif

#ifdef BOARD_USING_I2C1
static struct nuc97x_i2c_bus nuc97x_i2c1 =
{
    .I2Cx = I2C1,
};
#endif


int rt_hw_i2c_init(void)
{
    struct nuc97x_i2c_bus *i2c;
#ifdef BOARD_USING_I2C0
    {
        i2c = & nuc97x_i2c0;
        /* Enable engine clock */
        outpw(REG_CLK_PCLKEN1, inpw(REG_CLK_PCLKEN1) | 0x1);
        /* Configure multi function pins to I2C0 */
        outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & ~0xffff) | 0x88);
        i2cDisable(i2c->I2Cx);
        _i2cSetSpeed(i2c->I2Cx,400);        //speed = 400K

        rt_hw_interrupt_install(I2C0_IRQn,nux97x_i2c_isr,i2c,"i2c0ISR");
        rt_hw_interrupt_set_priority(I2C0_IRQn,IRQ_LEVEL_2);
        rt_hw_interrupt_umask(I2C0_IRQn);

        i2c->parent.ops = &nuc97x_i2c_ops;
        rt_i2c_bus_device_register(&i2c->parent, "i2c0");
    }
#endif

#ifdef BOARD_USING_I2C1
    {
        i2c = &nuc97x_i2c1;
        outpw(REG_CLK_PCLKEN1, inpw(REG_CLK_PCLKEN1) | 0x2);

        outpw(REG_SYS_GPG_MFPL, (inpw(REG_SYS_GPG_MFPL) & ~0xff00) | 0x8800);

        rt_hw_interrupt_install(I2C1_IRQn, nux97x_i2c_isr, i2c, "i2c1ISR");
        rt_hw_interrupt_set_priority(I2C1_IRQn, IRQ_LEVEL_2);
        rt_hw_interrupt_umask(I2C1_IRQn);
    }
#endif

    return(0);
}
INIT_PREV_EXPORT(rt_hw_i2c_init);
