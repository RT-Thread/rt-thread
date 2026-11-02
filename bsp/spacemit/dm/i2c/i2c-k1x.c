/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "i2c.rk3x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/dev_i2c_dm.h>

/* Spacemit i2c registers */
#define REG_CR              0x0     /* Control Register */
#define REG_SR              0x4     /* Status Register */
#define REG_SAR             0x8     /* Slave Address Register */
#define REG_DBR             0xc     /* Data Buffer Register */
#define REG_LCR             0x10    /* Load Count Register */
#define REG_WCR             0x14    /* Wait Count Register */
#define REG_RST_CYC         0x18    /* Bus reset cycle counter */
#define REG_BMR             0x1c    /* Bus monitor register */
#define REG_WFIFO           0x20    /* Write FIFO Register */
#define REG_WFIFO_WPTR      0x24    /* Write FIFO Write Pointer Register */
#define REG_WFIFO_RPTR      0x28    /* Write FIFO Read Pointer Register */
#define REG_RFIFO           0x2c    /* Read FIFO Register */
#define REG_RFIFO_WPTR      0x30    /* Read FIFO Write Pointer Register */
#define REG_RFIFO_RPTR      0x34    /* Read FIFO Read Pointer Register */

/* Register REG_CR fields */
#define CR_START            RT_BIT(0)   /* Start bit */
#define CR_STOP             RT_BIT(1)   /* Stop bit */
#define CR_ACKNAK           RT_BIT(2)   /* Send ACK(0) or NAK(1) */
#define CR_TB               RT_BIT(3)   /* Transfer byte bit */
#define CR_TXBEGIN          RT_BIT(4)   /* Transaction begin */
#define CR_FIFOEN           RT_BIT(5)   /* Enable FIFO mode */
#define CR_GPIOEN           RT_BIT(6)   /* Enable GPIO mode for SCL in HS */
#define CR_DMAEN            RT_BIT(7)   /* Enable DMA for TX and RX FIFOs */
#define CR_MODE_FAST        RT_BIT(8)   /* Bus mode (master operation) */
#define CR_MODE_HIGH        RT_BIT(9)   /* Bus mode (master operation) */
#define CR_UR               RT_BIT(10)  /* Unit reset */
#define CR_RSTREQ           RT_BIT(11)  /* I2c bus reset request */
#define CR_MA               RT_BIT(12)  /* Master abort */
#define CR_SCLE             RT_BIT(13)  /* Master clock enable */
#define CR_IUE              RT_BIT(14)  /* Unit enable */
#define CR_HS_STRETCH       RT_BIT(16)  /* I2C hs stretch */
#define CR_ALDIE            RT_BIT(18)  /* Enable arbitration interrupt */
#define CR_DTEIE            RT_BIT(19)  /* Enable tx interrupts */
#define CR_DRFIE            RT_BIT(20)  /* Enable rx interrupts */
#define CR_GCD              RT_BIT(21)  /* General call disable */
#define CR_BEIE             RT_BIT(22)  /* Enable bus error ints */
#define CR_SADIE            RT_BIT(23)  /* Slave address detected int enable */
#define CR_SSDIE            RT_BIT(24)  /* Slave STOP detected int enable */
#define CR_MSDIE            RT_BIT(25)  /* Master STOP detected int enable */
#define CR_MSDE             RT_BIT(26)  /* Master STOP detected enable */
#define CR_TXDONEIE         RT_BIT(27)  /* Transaction done int enable */
#define CR_TXEIE            RT_BIT(28)  /* Transmit FIFO empty int enable */
#define CR_RXHFIE           RT_BIT(29)  /* Receive FIFO half-full int enable */
#define CR_RXFIE            RT_BIT(30)  /* Receive FIFO full int enable */
#define CR_RXOVIE           RT_BIT(31)  /* Receive FIFO overrun int enable */

/* Register REG_SR fields */
#define SR_RWM              RT_BIT(13)  /* Read/write mode */
#define SR_ACKNAK           RT_BIT(14)  /* ACK/NACK status */
#define SR_UB               RT_BIT(15)  /* Unit busy */
#define SR_IBB              RT_BIT(16)  /* I2c bus busy */
#define SR_EBB              RT_BIT(17)  /* Early bus busy */
#define SR_ALD              RT_BIT(18)  /* Arbitration loss detected */
#define SR_ITE              RT_BIT(19)  /* Tx buffer empty */
#define SR_IRF              RT_BIT(20)  /* Rx buffer full */
#define SR_GCAD             RT_BIT(21)  /* General call address detected */
#define SR_BED              RT_BIT(22)  /* Bus error no ACK/NAK */
#define SR_SAD              RT_BIT(23)  /* Slave address detected */
#define SR_SSD              RT_BIT(24)  /* Slave stop detected */
#define SR_MSD              RT_BIT(26)  /* Master stop detected */
#define SR_TXDONE           RT_BIT(27)  /* Transaction done */
#define SR_TXE              RT_BIT(28)  /* Tx FIFO empty */
#define SR_RXHF             RT_BIT(29)  /* Rx FIFO half-full */
#define SR_RXF              RT_BIT(30)  /* Rx FIFO full */
#define SR_RXOV             RT_BIT(31)  /* RX FIFO overrun */

/* Register REG_LCR fields */
#define LCR_SLV             0x000001ff  /* SLV: bit[8:0] */
#define LCR_FLV             0x0003fe00  /* FLV: bit[17:9] */
#define LCR_HLVH            0x07fc0000  /* HLVH: bit[26:18] */
#define LCR_HLVL            0xf8000000  /* HLVL: bit[31:27] */

/* Register REG_WCR fields */
#define WCR_COUNT           0x0000001f  /* COUNT: bit[4:0] */
#define WCR_COUNT1          0x000003e0  /* HS_COUNT1: bit[9:5] */
#define WCR_COUNT2          0x00007c00  /* HS_COUNT2: bit[14:10] */

/* Register REG_BMR fields */
#define BMR_SDA             RT_BIT(0)   /* SDA line level */
#define BMR_SCL             RT_BIT(1)   /* SCL line level */

/* Register REG_WFIFO fields */
#define WFIFO_DATA_MSK      0x000000ff  /* data: bit[7:0] */
#define WFIFO_CTRL_MSK      0x000003e0  /* control: bit[11:8] */
#define WFIFO_CTRL_START    RT_BIT(8)   /* start bit */
#define WFIFO_CTRL_STOP     RT_BIT(9)   /* stop bit */
#define WFIFO_CTRL_ACKNAK   RT_BIT(10)  /* send ACK(0) or NAK(1) */
#define WFIFO_CTRL_TB       RT_BIT(11)  /* transfer byte bit */

#define USEC_PER_SEC        1000000L
#define USEC_PER_MSEC       1000L
#define I2C_SMBUS_BLOCK_MAX 32

/* Status register init value */
#define SPACEMIT_I2C_INT_STATUS_MASK    0xfffc0000 /* SR bits[31:18] */
#define SPACEMIT_I2C_INT_CTRL_MASK      (CR_ALDIE | CR_DTEIE | CR_DRFIE | CR_BEIE | CR_TXDONEIE | \
                                        CR_TXEIE | CR_RXHFIE | CR_RXFIE | CR_RXOVIE | CR_MSDIE)

/* I2C transfer mode */
enum spacemit_i2c_xfer_mode
{
    SPACEMIT_I2C_MODE_INTERRUPT,
    SPACEMIT_I2C_MODE_FIFO,
    SPACEMIT_I2C_MODE_DMA,
    SPACEMIT_I2C_MODE_PIO,
    SPACEMIT_I2C_MODE_INVALID,
};

/* I2C transfer phase during transaction */
enum spacemit_i2c_xfer_phase
{
    SPACEMIT_I2C_XFER_MASTER_CODE,
    SPACEMIT_I2C_XFER_SLAVE_ADDR,
    SPACEMIT_I2C_XFER_BODY,
    SPACEMIT_I2C_XFER_IDLE,
};

/* i2c controller FIFO depth */
#define SPACEMIT_I2C_RX_FIFO_DEPTH          8
#define SPACEMIT_I2C_TX_FIFO_DEPTH          8

/* i2c bus recover timeout: us */
#define SPACEMIT_I2C_BUS_RECOVER_TIMEOUT    100000

/* i2c bus active timeout: us */
#define SPACEMIT_I2C_BUS_ACTIVE_TIMEOUT     100000

/* scatter list size for DMA mode, equals to max number of i2c messages */
#define SPACEMIT_I2C_SCATTERLIST_SIZE       42

/* for DMA mode, limit one message's length less than 512 bytes */
#define SPACEMIT_I2C_MAX_MSG_LEN            512
#define SPACEMIT_I2C_DMA_TX_BUF_LEN         ((SPACEMIT_I2C_MAX_MSG_LEN + 2) * SPACEMIT_I2C_SCATTERLIST_SIZE)
#define SPACEMIT_I2C_DMA_RX_BUF_LEN         (SPACEMIT_I2C_MAX_MSG_LEN * SPACEMIT_I2C_SCATTERLIST_SIZE)

#define SPACEMIT_I2C_APB_CLOCK_26M          26000000
#define SPACEMIT_I2C_APB_CLOCK_52M          52000000

#define I2C_SDA_GLITCH_FIX_BYPASS           RT_BIT(7)

/* i2c-spacemit driver's main struct */
struct spacemit_i2c
{
    struct rt_i2c_bus_device parent;

    int irq;
    void *regs;
    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    rt_uint32_t drv_retries;

    rt_bool_t clk_always_on;
    rt_bool_t dma_disable;

    /* Speed mode selection */
    rt_bool_t fast_mode;
    rt_bool_t high_mode;

    /* APB clock */
    rt_uint32_t apb_clock;

    /* Master code for high-speed mode */
    rt_uint8_t master_code;
    rt_uint32_t clk_rate;
    rt_uint32_t i2c_lcr;
    rt_uint32_t i2c_wcr;

    /* Slave address with read/write flag */
    rt_uint32_t slave_addr_rw;

    struct rt_i2c_msg *msgs;
    int num;

    struct rt_i2c_msg *cur_msg;
    int msg_idx;

    rt_uint8_t *msg_buf;
    rt_bool_t is_rx;
    rt_size_t rx_cnt;
    rt_size_t tx_cnt;
    int rx_total;
    rt_bool_t is_xfer_start;

    struct rt_completion complete;
    struct rt_spinlock fifo_lock;

    rt_tick_t timeout;
    enum spacemit_i2c_xfer_mode xfer_mode;
    enum spacemit_i2c_xfer_phase phase;
    rt_uint32_t i2c_ctrl_reg_value;
    rt_uint32_t i2c_status;
    rt_uint32_t i2c_err;
};

#define raw_to_spacemit_i2c(raw) rt_container_of(raw, struct spacemit_i2c, parent)

static rt_err_t spacemit_i2c_byte_xfer(struct spacemit_i2c *i2c);
static rt_err_t spacemit_i2c_byte_xfer_next_msg(struct spacemit_i2c *i2c);

rt_inline rt_uint32_t spacemit_i2c_read(struct spacemit_i2c *i2c, int offset)
{
    return HWREG32(i2c->regs + offset);
}

rt_inline void spacemit_i2c_write(struct spacemit_i2c *i2c, int offset, rt_uint32_t val)
{
    HWREG32(i2c->regs + offset) = val;
}

static void spacemit_i2c_enable(struct spacemit_i2c *i2c)
{
    spacemit_i2c_write(i2c, REG_CR, spacemit_i2c_read(i2c, REG_CR) | CR_IUE);
}

static void spacemit_i2c_disable(struct spacemit_i2c *i2c)
{
    i2c->i2c_ctrl_reg_value = spacemit_i2c_read(i2c, REG_CR) & ~CR_IUE;
    spacemit_i2c_write(i2c, REG_CR, i2c->i2c_ctrl_reg_value);
}

static void spacemit_i2c_flush_fifo_buffer(struct spacemit_i2c *i2c)
{
    /* Flush REG_WFIFO_WPTR and REG_WFIFO_RPTR */
    spacemit_i2c_write(i2c, REG_WFIFO_WPTR, 0);
    spacemit_i2c_write(i2c, REG_WFIFO_RPTR, 0);

    /* Flush REG_RFIFO_WPTR and REG_RFIFO_RPTR */
    spacemit_i2c_write(i2c, REG_RFIFO_WPTR, 0);
    spacemit_i2c_write(i2c, REG_RFIFO_RPTR, 0);
}

static void spacemit_i2c_controller_reset(struct spacemit_i2c *i2c)
{
    /* Controller reset */
    spacemit_i2c_write(i2c, REG_CR, CR_UR);
    rt_hw_us_delay(5);
    spacemit_i2c_write(i2c, REG_CR, 0);

    /* Set load counter register */
    if (i2c->i2c_lcr)
    {
        spacemit_i2c_write(i2c, REG_LCR, i2c->i2c_lcr);
    }

    /* Set wait counter register */
    if (i2c->i2c_wcr)
    {
        spacemit_i2c_write(i2c, REG_WCR, i2c->i2c_wcr);
    }
}

static void spacemit_i2c_bus_reset(struct spacemit_i2c *i2c)
{
    rt_uint32_t bus_status, val;

    /* If bus is locked, reset unit. 0: locked */
    bus_status = spacemit_i2c_read(i2c, REG_BMR);
    if (!(bus_status & BMR_SDA) || !(bus_status & BMR_SCL))
    {
        spacemit_i2c_controller_reset(i2c);
        rt_hw_us_delay(15);
    }

    for (int clk_cnt = 0; clk_cnt < 9; ++clk_cnt)
    {
        /* check whether the SDA is still locked by slave */
        bus_status = spacemit_i2c_read(i2c, REG_BMR);
        if (bus_status & BMR_SDA)
        {
            break;
        }

        /* If still locked, send one clk to slave to request release */
        val = spacemit_i2c_read(i2c, REG_RST_CYC);
        spacemit_i2c_write(i2c, REG_RST_CYC, val | 0x1);
        spacemit_i2c_write(i2c, REG_CR, CR_RSTREQ);
        rt_hw_us_delay(25);
    }
}

static void spacemit_i2c_reset(struct spacemit_i2c *i2c)
{
    spacemit_i2c_controller_reset(i2c);
}

static rt_err_t spacemit_i2c_recover_bus_busy(struct spacemit_i2c *i2c)
{
    rt_err_t err;
    int cnt, timeout = i2c->high_mode ? 1000 : 1500; /* us */

    cnt = SPACEMIT_I2C_BUS_RECOVER_TIMEOUT / timeout;

    if (!(spacemit_i2c_read(i2c, REG_SR) & (SR_UB | SR_IBB)))
    {
        return RT_EOK;
    }

    /* Wait unit and bus to recover idle */
    while (spacemit_i2c_read(i2c, REG_SR) & (SR_UB | SR_IBB))
    {
        if (cnt-- <= 0)
        {
            break;
        }

        rt_hw_us_delay((timeout / 2 + timeout) / 2);
    }

    if (cnt <= 0)
    {
        /* Reset controller */
        spacemit_i2c_reset(i2c);
        err = -RT_EIO;
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

static void spacemit_i2c_check_bus_release(struct spacemit_i2c *i2c)
{
    /* In case bus is not released after transfer completes */
    if (spacemit_i2c_read(i2c, REG_SR) & SR_EBB)
    {
        spacemit_i2c_bus_reset(i2c);
        rt_hw_us_delay(120);
    }
}

static void spacemit_i2c_unit_init(struct spacemit_i2c *i2c)
{
    rt_uint32_t cr_val = 0;

    /*
     * Unmask interrupt bits for all xfer mode:
     * bus error, arbitration loss detected.
     * For transaction complete signal, we use master stop
     * interrupt, so we don't need to unmask CR_TXDONEIE.
     */
    cr_val |= CR_BEIE | CR_ALDIE;

    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_INTERRUPT)
    {
        /*
         * Unmask interrupt bits for interrupt xfer mode: DBR rx full.
         * For tx empty interrupt CR_DTEIE, we only need to enable when
         * trigger byte transfer to start data sending.
         */
        cr_val |= CR_DRFIE;
    }
    else if (i2c->xfer_mode == SPACEMIT_I2C_MODE_FIFO)
    {
        /* Enable i2c FIFO mode*/
        cr_val |= CR_FIFOEN;
    }
    else if (i2c->xfer_mode == SPACEMIT_I2C_MODE_DMA)
    {
        /* Enable i2c DMA mode*/
        cr_val |= CR_DMAEN | CR_FIFOEN;
    }

    /* Set speed bits */
    if (i2c->fast_mode)
    {
        cr_val |= CR_MODE_FAST;
    }
    if (i2c->high_mode)
    {
        cr_val |= CR_MODE_HIGH | CR_GPIOEN;
    }

    /* Disable response to general call */
    cr_val |= CR_GCD;

    /* Enable SCL clock output */
    cr_val |= CR_SCLE;

    /* Enable master stop detected */
    cr_val |= CR_MSDE | CR_MSDIE;

    /* Disable int to use pio xfer mode*/
    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_PIO)
    {
        cr_val &= ~(CR_ALDIE | CR_BEIE | CR_MSDIE | CR_DTEIE);
    }

    spacemit_i2c_write(i2c, REG_CR, cr_val);
}

static void spacemit_i2c_trigger_byte_xfer(struct spacemit_i2c *i2c)
{
    rt_uint32_t cr_val;

    /* Send start pulse */
    cr_val = spacemit_i2c_read(i2c, REG_CR);
    cr_val &= ~CR_STOP;
    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_PIO)
    {
        cr_val |= CR_START | CR_TB;
    }
    else
    {
        cr_val |= CR_START | CR_TB | CR_DTEIE;
    }
    spacemit_i2c_write(i2c, REG_CR, cr_val);
}

rt_inline void spacemit_i2c_clear_int_status(struct spacemit_i2c *i2c, rt_uint32_t mask)
{
    spacemit_i2c_write(i2c, REG_SR, mask & SPACEMIT_I2C_INT_STATUS_MASK);
}

static rt_bool_t spacemit_i2c_is_last_byte_to_send(struct spacemit_i2c *i2c)
{
    return i2c->tx_cnt == i2c->cur_msg->len && i2c->msg_idx == i2c->num - 1;
}

static rt_bool_t spacemit_i2c_is_last_byte_to_receive(struct spacemit_i2c *i2c)
{
    return i2c->rx_cnt == i2c->cur_msg->len - 1 && i2c->msg_idx == i2c->num - 1;
}

static void spacemit_i2c_mark_rw_flag(struct spacemit_i2c *i2c)
{
    if (i2c->cur_msg->flags & RT_I2C_RD)
    {
        i2c->is_rx = RT_TRUE;
        i2c->slave_addr_rw = ((i2c->cur_msg->addr & 0x7f) << 1) | 1;
    }
    else
    {
        i2c->is_rx = RT_FALSE;
        i2c->slave_addr_rw = (i2c->cur_msg->addr & 0x7f) << 1;
    }
}

static void spacemit_i2c_byte_xfer_send_master_code(struct spacemit_i2c *i2c)
{
    rt_uint32_t cr_val = spacemit_i2c_read(i2c, REG_CR);

    i2c->phase = SPACEMIT_I2C_XFER_MASTER_CODE;

    spacemit_i2c_write(i2c, REG_DBR, i2c->master_code);

    cr_val &= ~(CR_STOP | CR_ALDIE);

    /* High mode: enable gpio to let I2C core generates SCL clock */
    cr_val |= CR_GPIOEN | CR_START | CR_TB | CR_DTEIE;
    spacemit_i2c_write(i2c, REG_CR, cr_val);
}

static void spacemit_i2c_byte_xfer_send_slave_addr(struct spacemit_i2c *i2c)
{
    i2c->phase = SPACEMIT_I2C_XFER_SLAVE_ADDR;

    /* Write slave address to DBR for interrupt mode */
    spacemit_i2c_write(i2c, REG_DBR, i2c->slave_addr_rw);

    spacemit_i2c_trigger_byte_xfer(i2c);
}

static rt_err_t spacemit_i2c_byte_xfer_body(struct spacemit_i2c *i2c)
{
    rt_err_t err = RT_EOK;
    rt_uint32_t cr_val = spacemit_i2c_read(i2c, REG_CR);

    cr_val &= ~(CR_TB | CR_ACKNAK | CR_STOP | CR_START);
    i2c->phase = SPACEMIT_I2C_XFER_BODY;

    if (i2c->i2c_status & SR_IRF) /* Receive full */
    {
        /* If current is transmit mode, ignore this signal */
        if (!i2c->is_rx)
        {
            return RT_EOK;
        }

        if (i2c->rx_cnt < i2c->cur_msg->len)
        {
            *i2c->msg_buf++ = spacemit_i2c_read(i2c, REG_DBR);
            i2c->rx_cnt++;
        }

        /* If transfer completes, ISR will handle it */
        if (i2c->i2c_status & (SR_MSD | SR_ACKNAK))
        {
            return RT_EOK;
        }

        /* Trigger next byte receive */
        if (i2c->rx_cnt < i2c->cur_msg->len)
        {
            /* Send stop pulse for last byte of last msg */
            if (spacemit_i2c_is_last_byte_to_receive(i2c))
            {
                cr_val |= CR_STOP | CR_ACKNAK;
            }

            cr_val |= CR_ALDIE | CR_TB;
            spacemit_i2c_write(i2c, REG_CR, cr_val);
        }
        else if (i2c->msg_idx < i2c->num - 1)
        {
            err = spacemit_i2c_byte_xfer_next_msg(i2c);
        }
    }
    else if (i2c->i2c_status & SR_ITE) /* Transmit empty */
    {
        /* MSD comes with ITE */
        if (i2c->i2c_status & SR_MSD)
        {
            return err;
        }

        if (i2c->i2c_status & SR_RWM) /* Receive mode */
        {
            /* If current is transmit mode, ignore this signal */
            if (!i2c->is_rx)
            {
                return RT_EOK;
            }

            if (spacemit_i2c_is_last_byte_to_receive(i2c))
            {
                cr_val |= CR_STOP | CR_ACKNAK;
            }

            /* Trigger next byte receive */
            cr_val |= CR_ALDIE | CR_TB;

            /*
             * Mask transmit empty interrupt to avoid useless tx
             * interrupt signal after switch to receive mode, the
             * next expected is receive full interrupt signal.
             */
            cr_val &= ~CR_DTEIE;
            spacemit_i2c_write(i2c, REG_CR, cr_val);
        }
        else /* Transmit mode */
        {
            /* If current is receive mode, ignore this signal */
            if (i2c->is_rx)
            {
                return RT_EOK;
            }

            if (i2c->tx_cnt < i2c->cur_msg->len)
            {
                spacemit_i2c_write(i2c, REG_DBR, *i2c->msg_buf++);
                i2c->tx_cnt++;

                /* Send stop pulse for last byte of last msg */
                if (spacemit_i2c_is_last_byte_to_send(i2c))
                {
                    cr_val |= CR_STOP;
                }

                cr_val |= CR_ALDIE | CR_TB;
                spacemit_i2c_write(i2c, REG_CR, cr_val);
            }
            else if (i2c->msg_idx < i2c->num - 1)
            {
                err = spacemit_i2c_byte_xfer_next_msg(i2c);
            }
        }
    }

    return err;
}

static rt_err_t spacemit_i2c_byte_xfer_next_msg(struct spacemit_i2c *i2c)
{
    if (i2c->msg_idx == i2c->num - 1)
    {
        return RT_EOK;
    }

    i2c->msg_idx++;
    i2c->cur_msg = i2c->msgs + i2c->msg_idx;
    i2c->msg_buf = i2c->cur_msg->buf;
    i2c->rx_cnt = 0;
    i2c->tx_cnt = 0;
    i2c->i2c_err = 0;
    i2c->i2c_status = 0;
    i2c->phase = SPACEMIT_I2C_XFER_IDLE;

    spacemit_i2c_mark_rw_flag(i2c);

    return spacemit_i2c_byte_xfer(i2c);
}

static void spacemit_i2c_fifo_xfer_fill_buffer(struct spacemit_i2c *i2c)
{
    rt_ubase_t level;
    int data_cnt = 0, finish, count = 0, fill = 0;
    rt_uint32_t data = 0, data_buf[SPACEMIT_I2C_TX_FIFO_DEPTH * 2];

    while (i2c->msg_idx < i2c->num)
    {
        spacemit_i2c_mark_rw_flag(i2c);

        if (i2c->is_rx)
        {
            finish = i2c->rx_cnt;
        }
        else
        {
            finish = i2c->tx_cnt;
        }

        /* Write master code to fifo buffer */
        if (i2c->high_mode && i2c->is_xfer_start)
        {
            data = i2c->master_code;
            data |= WFIFO_CTRL_TB | WFIFO_CTRL_START;
            data_buf[data_cnt++] = data;

            fill += 2;
            count = rt_min_t(rt_size_t, i2c->cur_msg->len - finish, SPACEMIT_I2C_TX_FIFO_DEPTH - fill);
        }
        else
        {
            fill += 1;
            count = rt_min_t(rt_size_t, i2c->cur_msg->len - finish, SPACEMIT_I2C_TX_FIFO_DEPTH - fill);
        }

        i2c->is_xfer_start = RT_FALSE;
        fill += count;
        data = i2c->slave_addr_rw;
        data |= WFIFO_CTRL_TB | WFIFO_CTRL_START;

        /* Write slave address to fifo buffer */
        data_buf[data_cnt++] = data;

        if (i2c->is_rx)
        {
            i2c->rx_cnt += count;

            if (i2c->rx_cnt == i2c->cur_msg->len && i2c->msg_idx == i2c->num - 1)
            {
                count -= 1;
            }

            while (count > 0)
            {
                data = *i2c->msg_buf | WFIFO_CTRL_TB;
                data_buf[data_cnt++] = data;
                i2c->msg_buf++;
                count--;
            }

            if (i2c->rx_cnt == i2c->cur_msg->len && i2c->msg_idx == i2c->num - 1)
            {
                data = *i2c->msg_buf++;
                data = i2c->slave_addr_rw | WFIFO_CTRL_TB | WFIFO_CTRL_STOP | WFIFO_CTRL_ACKNAK;
                data_buf[data_cnt++] = data;
            }
        }
        else
        {
            i2c->tx_cnt += count;
            if (spacemit_i2c_is_last_byte_to_send(i2c))
            {
                count -= 1;
            }

            while (count > 0)
            {
                data = *i2c->msg_buf | WFIFO_CTRL_TB;
                data_buf[data_cnt++] = data;
                i2c->msg_buf++;
                count--;
            }
            if (spacemit_i2c_is_last_byte_to_send(i2c))
            {
                data = *i2c->msg_buf | WFIFO_CTRL_TB | WFIFO_CTRL_STOP;
                data_buf[data_cnt++] = data;
            }
        }

        if (i2c->tx_cnt == i2c->cur_msg->len || i2c->rx_cnt == i2c->cur_msg->len)
        {
            i2c->msg_idx++;
            if (i2c->msg_idx == i2c->num)
            {
                break;
            }

            i2c->cur_msg = i2c->msgs + i2c->msg_idx;
            i2c->msg_buf = i2c->cur_msg->buf;
            i2c->rx_cnt = 0;
            i2c->tx_cnt = 0;
        }

        if (fill == SPACEMIT_I2C_TX_FIFO_DEPTH)
        {
            break;
        }
    }

    level = rt_spin_lock_irqsave(&i2c->fifo_lock);

    for (int i = 0; i < data_cnt; ++i)
    {
        spacemit_i2c_write(i2c, REG_WFIFO, data_buf[i]);
    }

    rt_spin_unlock_irqrestore(&i2c->fifo_lock, level);
}

static void spacemit_i2c_fifo_xfer_copy_buffer(struct spacemit_i2c *i2c)
{
    int idx = 0, cnt = 0;
    struct rt_i2c_msg *msg;

    /* Copy the rx FIFO buffer to msg */
    while (idx < i2c->num)
    {
        msg = i2c->msgs + idx;
        if (msg->flags & RT_I2C_RD)
        {
            cnt = msg->len;
            while (cnt > 0)
            {
                *(msg->buf + msg->len - cnt) = spacemit_i2c_read(i2c, REG_RFIFO);
                cnt--;
            }
        }
        idx++;
    }
}

static rt_err_t spacemit_i2c_fifo_xfer(struct spacemit_i2c *i2c)
{
    rt_err_t err = RT_EOK;

    spacemit_i2c_fifo_xfer_fill_buffer(i2c);

    if ((err = rt_completion_wait(&i2c->complete, i2c->timeout)))
    {
        spacemit_i2c_bus_reset(i2c);
        goto _err_out;
    }

    if (i2c->i2c_err)
    {
        err = -RT_ERROR;
        spacemit_i2c_flush_fifo_buffer(i2c);
        goto _err_out;
    }

    spacemit_i2c_fifo_xfer_copy_buffer(i2c);

_err_out:
    return err;
}

static rt_err_t spacemit_i2c_byte_xfer(struct spacemit_i2c *i2c)
{
    rt_err_t err = RT_EOK;

    if (i2c->i2c_err)
    {
        return -RT_ERROR;
    }

    if (i2c->phase == SPACEMIT_I2C_XFER_IDLE)
    {
        if (i2c->high_mode && i2c->is_xfer_start)
        {
            spacemit_i2c_byte_xfer_send_master_code(i2c);
        }
        else
        {
            spacemit_i2c_byte_xfer_send_slave_addr(i2c);
        }

        i2c->is_xfer_start = RT_FALSE;
    }
    else if (i2c->phase == SPACEMIT_I2C_XFER_MASTER_CODE)
    {
        spacemit_i2c_byte_xfer_send_slave_addr(i2c);
    }
    else
    {
        err = spacemit_i2c_byte_xfer_body(i2c);
    }

    return err;
}

static void spacemit_i2c_choose_xfer_mode(struct spacemit_i2c *i2c)
{
    unsigned long timeout;
    int idx = 0, cnt = 0, freq;
    rt_bool_t block = RT_FALSE;

    /* Scan msgs */
    if (i2c->high_mode)
    {
        cnt++;
    }

    i2c->rx_total = 0;

    while (idx < i2c->num)
    {
        cnt += (i2c->msgs + idx)->len + 1;

        if ((i2c->msgs + idx)->flags & RT_I2C_RD)
        {
            i2c->rx_total += (i2c->msgs + idx)->len;
        }

        idx++;
    }

    if (i2c->dma_disable || block)
    {
        i2c->xfer_mode = SPACEMIT_I2C_MODE_INTERRUPT;
    }
    else
    {
        if (cnt <= SPACEMIT_I2C_TX_FIFO_DEPTH)
        {
            i2c->xfer_mode = SPACEMIT_I2C_MODE_FIFO;
        }
        else
        {
            i2c->xfer_mode = SPACEMIT_I2C_MODE_DMA;
        }

        /* Flush fifo buffer */
        spacemit_i2c_flush_fifo_buffer(i2c);
    }

    /*
     * if total message length is too large to over the allocated MDA
     * total buf length, use interrupt mode. This may happens in the
     * syzkaller test.
     */
    if (cnt > (SPACEMIT_I2C_MAX_MSG_LEN * SPACEMIT_I2C_SCATTERLIST_SIZE) ||
        i2c->rx_total > SPACEMIT_I2C_DMA_RX_BUF_LEN)
    {
        i2c->xfer_mode = SPACEMIT_I2C_MODE_INTERRUPT;
    }

    /* calculate timeout */
    if (i2c->high_mode)
    {
        freq = 1500000;
    }
    else if (i2c->fast_mode)
    {
        freq = 400000;
    }
    else
    {
        freq = 100000;
    }

    timeout = cnt * 9 * USEC_PER_SEC / freq;

    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_INTERRUPT ||
        i2c->xfer_mode == SPACEMIT_I2C_MODE_PIO)
    {
        timeout += (cnt - 1) * 220;
    }

    timeout /= USEC_PER_MSEC;

    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_INTERRUPT)
    {
        i2c->timeout = rt_tick_from_millisecond(timeout + 500);
    }
    else
    {
        i2c->timeout = rt_tick_from_millisecond(timeout + 100);
    }
}

static void spacemit_i2c_init_xfer_params(struct spacemit_i2c *i2c)
{
    /* Initialize transfer parameters */
    i2c->msg_idx = 0;
    i2c->cur_msg = i2c->msgs;
    i2c->msg_buf = i2c->cur_msg->buf;
    i2c->rx_cnt = 0;
    i2c->tx_cnt = 0;
    i2c->i2c_err = 0;
    i2c->i2c_status = 0;
    i2c->phase = SPACEMIT_I2C_XFER_IDLE;

    /* Only send master code once for high speed mode */
    i2c->is_xfer_start = RT_TRUE;
}

rt_used
static rt_ssize_t spacemit_i2c_pio_xfer(struct spacemit_i2c *i2c)
{
    rt_ssize_t res;
    int xfer_try = 0;
    rt_uint32_t status;
    signed long timeout;

_xfer_retry:
    /* calculate timeout */
    spacemit_i2c_choose_xfer_mode(i2c);
    i2c->xfer_mode = SPACEMIT_I2C_MODE_PIO;
    timeout = i2c->timeout * (1000U / RT_TICK_PER_SECOND) * USEC_PER_MSEC;

    if (!i2c->clk_always_on)
    {
        rt_clk_enable(i2c->clk);
    }

    spacemit_i2c_controller_reset(i2c);
    rt_hw_us_delay(2);

    spacemit_i2c_unit_init(i2c);

    spacemit_i2c_clear_int_status(i2c, SPACEMIT_I2C_INT_STATUS_MASK);

    spacemit_i2c_init_xfer_params(i2c);

    spacemit_i2c_mark_rw_flag(i2c);

    spacemit_i2c_enable(i2c);

    if ((res = spacemit_i2c_byte_xfer(i2c)) < 0)
    {
        goto _out;
    }

    while (i2c->num > 0 && timeout > 0)
    {
        status = spacemit_i2c_read(i2c, REG_SR);
        spacemit_i2c_clear_int_status(i2c, status);
        i2c->i2c_status = status;

        /* Bus error, arbitration lost */
        i2c->i2c_err = status & (SR_BED | SR_ALD);
        if (i2c->i2c_err)
        {
            res = -RT_ERROR;
            break;
        }

        /* Receive full */
        if (status & SR_IRF)
        {
            if ((res = spacemit_i2c_byte_xfer(i2c)) < 0)
            {
                break;
            }
        }

        /* Transmit empty */
        if (status & SR_ITE)
        {
            if ((res = spacemit_i2c_byte_xfer(i2c)) < 0)
            {
                break;
            }
        }

        /* Transaction done */
        if (status & SR_MSD)
        {
            break;
        }

        rt_hw_us_delay(10);
        timeout -= 10;
    }

    spacemit_i2c_disable(i2c);

    if (!i2c->clk_always_on)
    {
        rt_clk_disable(i2c->clk);
    }

    if (timeout <= 0)
    {
        spacemit_i2c_bus_reset(i2c);
        rt_hw_us_delay(100);
        res = -RT_ETIMEOUT;
        goto _out;
    }

    /* Process i2c error */
    if (i2c->i2c_err)
    {
        res = -RT_EIO;
    }

_out:
    xfer_try++;
    /* Retry i2c transfer 3 times for timeout and bus busy */
    if ((res == -RT_ETIMEOUT || res == -RT_EIO) && xfer_try <= i2c->drv_retries)
    {
        rt_hw_us_delay(150);
        res = 0;
        goto _xfer_retry;
    }

    return res < 0 ? res : i2c->num;
}

static rt_ssize_t spacemit_i2c_xfer(struct rt_i2c_bus_device *bus,
        struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    int xfer_try = 0;
    rt_ssize_t res = 0;
    rt_bool_t clk_directly = RT_FALSE;
    struct spacemit_i2c *i2c = raw_to_spacemit_i2c(bus);

    i2c->msgs = msgs;
    i2c->num = num;

_xfer_retry:
    /* If unit keeps the last control status, don't need to do reset */
    if (spacemit_i2c_read(i2c, REG_CR) != i2c->i2c_ctrl_reg_value)
    {
        /* Controller & bus reset */
        spacemit_i2c_reset(i2c);
    }

    /* Choose transfer mode */
    spacemit_i2c_choose_xfer_mode(i2c);

    /* Unit init */
    spacemit_i2c_unit_init(i2c);

    /* Clear all interrupt status */
    spacemit_i2c_clear_int_status(i2c, SPACEMIT_I2C_INT_STATUS_MASK);

    spacemit_i2c_init_xfer_params(i2c);

    res = spacemit_i2c_read(i2c, REG_RST_CYC);
    spacemit_i2c_write(i2c, REG_RST_CYC, I2C_SDA_GLITCH_FIX_BYPASS | res);

    spacemit_i2c_mark_rw_flag(i2c);

    spacemit_i2c_enable(i2c);

    /* Wait for bus busy */
    if ((res = spacemit_i2c_recover_bus_busy(i2c)))
    {
        goto _err_recover;
    }

    /* Msg transmit */
    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_INTERRUPT)
    {
        res = spacemit_i2c_byte_xfer(i2c);
    }
    else if (i2c->xfer_mode == SPACEMIT_I2C_MODE_FIFO)
    {
        res = spacemit_i2c_fifo_xfer(i2c);
    }
    else
    {
        /* DMA */
        res = -RT_ENOSYS;
    }

    if (res < 0)
    {
        if (res != -RT_ETIMEOUT)
        {
            res = -RT_EINVAL;
        }
        goto _err_xfer;
    }

    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_INTERRUPT)
    {
        if ((res = rt_completion_wait(&i2c->complete, i2c->timeout)))
        {
            spacemit_i2c_bus_reset(i2c);
            spacemit_i2c_reset(i2c);
            goto _timeout_xfex;
        }
    }

_err_xfer:
    if (!res)
    {
        spacemit_i2c_check_bus_release(i2c);
    }

_err_recover:
_timeout_xfex:
    /* Disable spacemit i2c */
    spacemit_i2c_disable(i2c);

    /* Process i2c error */
    if (i2c->i2c_err)
    {
        if (i2c->i2c_err & (SR_BED | SR_ALD))
        {
            spacemit_i2c_reset(i2c);
        }

        /* Try transfer again */
        if (i2c->i2c_err & (SR_RXOV | SR_ALD))
        {
            spacemit_i2c_flush_fifo_buffer(i2c);
        }

        res = -RT_EIO;
    }

    xfer_try++;
    /* Retry i2c transfer 3 times for timeout and bus busy */
    if ((res == -RT_ETIMEOUT || res == -RT_EIO) && xfer_try <= i2c->drv_retries)
    {
        rt_hw_us_delay(175);
        res = 0;
        goto _xfer_retry;
    }

    if (clk_directly)
    {
        /* If clock is enabled directly, here disable it */
        rt_clk_disable(i2c->clk);
    }

    return res < 0 ? res : num;
}

const static struct rt_i2c_bus_device_ops spacemit_i2c_ops =
{
    .master_xfer = spacemit_i2c_xfer,
};

static void spacemit_i2c_isr(int irq, void *param)
{
    rt_ssize_t res = 0;
    rt_uint32_t status, ctrl;
    struct spacemit_i2c *i2c = param;

    /* Record i2c status */
    status = spacemit_i2c_read(i2c, REG_SR);
    i2c->i2c_status = status;

    /* Check if a valid interrupt status */
    if (!status)
    {
        return;
    }

    /* Bus error, rx overrun, arbitration lost */
    i2c->i2c_err = status & (SR_BED | SR_RXOV | SR_ALD);

    /* Clear interrupt status bits[31:18]*/
    spacemit_i2c_clear_int_status(i2c, status);

    /* Error happens */
    if (i2c->i2c_err)
    {
        goto _err_out;
    }

    /* Process interrupt mode */
    if (i2c->xfer_mode == SPACEMIT_I2C_MODE_INTERRUPT)
    {
        res = spacemit_i2c_byte_xfer(i2c);
    }

_err_out:
    /* Send transaction complete signal: error happens, detect master stop */
    if (i2c->i2c_err || res < 0 || (status & SR_MSD))
    {
        /*
         * Here the transaction is already done, we don't need any
         * other interrupt signals from now, in case any interrupt
         * happens before spacemit_i2c_xfer to disable irq and i2c unit,
         * we mask all the interrupt signals and clear the interrupt status.
         */
        ctrl = spacemit_i2c_read(i2c, REG_CR);
        ctrl &= ~SPACEMIT_I2C_INT_CTRL_MASK;
        spacemit_i2c_write(i2c, REG_CR, ctrl);

        spacemit_i2c_clear_int_status(i2c, SPACEMIT_I2C_INT_STATUS_MASK);

        rt_completion_done(&i2c->complete);
    }
}

static void spacemit_i2c_free(struct spacemit_i2c *i2c, struct rt_device *dev)
{
    if (i2c->regs)
    {
        rt_iounmap(i2c->regs);
    }

    if (!rt_is_err_or_null(i2c->rstc))
    {
        rt_reset_control_assert(i2c->rstc);
        rt_reset_control_put(i2c->rstc);
    }

    if (!rt_is_err_or_null(i2c->clk))
    {
        rt_clk_disable_unprepare(i2c->clk);
        rt_clk_put(i2c->clk);
    }

    rt_free(i2c);
}

static rt_err_t spacemit_i2c_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_i2c *i2c = rt_calloc(1, sizeof(*i2c));

    if (!i2c)
    {
        return -RT_ENOMEM;
    }

    i2c->regs = rt_dm_dev_iomap(dev, 0);
    if (!i2c->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    i2c->irq = rt_dm_dev_get_irq(dev, 0);
    if (i2c->irq < 0)
    {
        err = i2c->irq;
        goto _fail;
    }

    i2c->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(i2c->rstc))
    {
        goto _fail;
    }

    /* Reset the i2c controller */
    rt_reset_control_assert(i2c->rstc);
    rt_hw_us_delay(200);
    rt_reset_control_deassert(i2c->rstc);

    /* Enable fast speed mode */
    i2c->fast_mode = rt_dm_dev_prop_read_bool(dev, "spacemit,i2c-fast-mode");
    /* Enable high speed mode */
    i2c->high_mode = rt_dm_dev_prop_read_bool(dev, "spacemit,i2c-high-mode");

    if (i2c->high_mode)
    {
        /* Get master code for high speed mode */
        if (rt_dm_dev_prop_read_u8(dev, "spacemit,i2c-master-code", &i2c->master_code))
        {
            i2c->master_code = 0x0e;
            LOG_W("Failed to get i2c master code, use default: %#x", i2c->master_code);
        }
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,i2c-clk-rate", &i2c->clk_rate)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,i2c-lcr", &i2c->i2c_lcr)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,i2c-wcr", &i2c->i2c_wcr)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,adapter-id", (rt_uint32_t *)&pdev->dev_id)))
    {
        pdev->dev_id = -1;
    }

    /* Disable DMA transfer mode, default: interrupt mode */
    i2c->dma_disable = RT_TRUE;
    i2c->xfer_mode = i2c->dma_disable ? SPACEMIT_I2C_MODE_INTERRUPT : SPACEMIT_I2C_MODE_DMA;

    i2c->drv_retries = 3;

    /* The clock will always on and not use runtime mechanism */
    i2c->clk_always_on = rt_dm_dev_prop_read_bool(dev, "spacemit,clk-always-on");

    /* APB clock: 26MHz or 52MHz */
    if ((err = rt_dm_dev_prop_read_u32(dev, "spacemit,apb_clock", &i2c->apb_clock)))
    {
        goto _fail;
    }
    else if (i2c->apb_clock != SPACEMIT_I2C_APB_CLOCK_26M &&
            i2c->apb_clock != SPACEMIT_I2C_APB_CLOCK_52M)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    i2c->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(i2c->clk))
    {
        err = rt_ptr_err(i2c->clk);
        goto _fail;
    }
    rt_clk_prepare_enable(i2c->clk);

    rt_completion_init(&i2c->complete);
    rt_spin_lock_init(&i2c->fifo_lock);

    if (pdev->dev_id >= 0)
    {
        rt_dm_dev_set_name(&i2c->parent.parent, "i2c%d", pdev->dev_id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&i2c->parent.parent, "i2c");
    }
    dev_name = rt_dm_dev_get_name(&i2c->parent.parent);

    rt_hw_interrupt_install(i2c->irq, spacemit_i2c_isr, i2c, dev_name);
    rt_hw_interrupt_umask(i2c->irq);

    dev->user_data = i2c;

    i2c->parent.ops = &spacemit_i2c_ops;
    i2c->parent.parent.ofw_node = dev->ofw_node;

    if ((err = rt_i2c_bus_device_register(&i2c->parent, dev_name)))
    {
        goto _free_irq;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2c);

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(i2c->irq);
    rt_pic_detach_irq(i2c->irq, i2c);

_fail:
    spacemit_i2c_free(i2c, dev);

    return err;
}

static rt_err_t spacemit_i2c_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct spacemit_i2c *i2c = dev->user_data;

    rt_hw_interrupt_mask(i2c->irq);
    rt_pic_detach_irq(i2c->irq, i2c);

    rt_device_unregister(&i2c->parent.parent);

    spacemit_i2c_free(i2c, dev);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_i2c_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-i2c" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_i2c_driver =
{
    .name = "spacemit-k1x-i2c",
    .ids = spacemit_i2c_ofw_ids,

    .probe = spacemit_i2c_probe,
    .remove = spacemit_i2c_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_i2c_driver);
