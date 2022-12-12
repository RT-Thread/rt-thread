/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

#include <rtthread.h>
#include <drivers/i2c.h>
#include <dm36x.h>

/* ----- global defines ----------------------------------------------- */
#define BIT(nr)         (1UL << (nr))

#define DAVINCI_I2C_TIMEOUT (1*RT_TICK_PER_SECOND)
#define DAVINCI_I2C_MAX_TRIES   2
#define I2C_DAVINCI_INTR_ALL    (DAVINCI_I2C_IMR_AAS | \
                 DAVINCI_I2C_IMR_SCD | \
                 DAVINCI_I2C_IMR_ARDY | \
                 DAVINCI_I2C_IMR_NACK | \
                 DAVINCI_I2C_IMR_AL)

#define DAVINCI_I2C_OAR_REG 0x00
#define DAVINCI_I2C_IMR_REG 0x04
#define DAVINCI_I2C_STR_REG 0x08
#define DAVINCI_I2C_CLKL_REG    0x0c
#define DAVINCI_I2C_CLKH_REG    0x10
#define DAVINCI_I2C_CNT_REG 0x14
#define DAVINCI_I2C_DRR_REG 0x18
#define DAVINCI_I2C_SAR_REG 0x1c
#define DAVINCI_I2C_DXR_REG 0x20
#define DAVINCI_I2C_MDR_REG 0x24
#define DAVINCI_I2C_IVR_REG 0x28
#define DAVINCI_I2C_EMDR_REG    0x2c
#define DAVINCI_I2C_PSC_REG 0x30

#define DAVINCI_I2C_IVR_AAS 0x07
#define DAVINCI_I2C_IVR_SCD 0x06
#define DAVINCI_I2C_IVR_XRDY    0x05
#define DAVINCI_I2C_IVR_RDR 0x04
#define DAVINCI_I2C_IVR_ARDY    0x03
#define DAVINCI_I2C_IVR_NACK    0x02
#define DAVINCI_I2C_IVR_AL  0x01

#define DAVINCI_I2C_STR_BB  BIT(12)
#define DAVINCI_I2C_STR_RSFULL  BIT(11)
#define DAVINCI_I2C_STR_SCD BIT(5)
#define DAVINCI_I2C_STR_ARDY    BIT(2)
#define DAVINCI_I2C_STR_NACK    BIT(1)
#define DAVINCI_I2C_STR_AL  BIT(0)

#define DAVINCI_I2C_MDR_NACK    BIT(15)
#define DAVINCI_I2C_MDR_STT BIT(13)
#define DAVINCI_I2C_MDR_STP BIT(11)
#define DAVINCI_I2C_MDR_MST BIT(10)
#define DAVINCI_I2C_MDR_TRX BIT(9)
#define DAVINCI_I2C_MDR_XA  BIT(8)
#define DAVINCI_I2C_MDR_RM  BIT(7)
#define DAVINCI_I2C_MDR_IRS BIT(5)

#define DAVINCI_I2C_IMR_AAS BIT(6)
#define DAVINCI_I2C_IMR_SCD BIT(5)
#define DAVINCI_I2C_IMR_XRDY    BIT(4)
#define DAVINCI_I2C_IMR_RRDY    BIT(3)
#define DAVINCI_I2C_IMR_ARDY    BIT(2)
#define DAVINCI_I2C_IMR_NACK    BIT(1)
#define DAVINCI_I2C_IMR_AL  BIT(0)

#ifdef RT_EDMA_DEBUG
#define i2c_dbg(fmt, ...)  rt_kprintf(fmt, ##__VA_ARGS__)
#else
#define i2c_dbg(fmt, ...)
#endif


struct davinci_i2c_dev {
    void        *base;
    struct rt_semaphore  completion;
    struct clk  *clk;
    int         cmd_err;
    rt_uint8_t  *buf;
    rt_uint32_t      buf_len;
    int         irq;
    int         stop;
    rt_uint8_t  terminate;
    rt_uint32_t bus_freq;
    rt_uint32_t bus_delay;
    struct rt_i2c_bus_device *bus;
};

static inline void davinci_i2c_write_reg(struct davinci_i2c_dev *i2c_dev,
                     int reg, rt_uint16_t val)
{
    davinci_writew(val, i2c_dev->base + reg);
}

static inline rt_uint16_t davinci_i2c_read_reg(struct davinci_i2c_dev *i2c_dev, int reg)
{
    return davinci_readw(i2c_dev->base + reg);
}

static void udelay (rt_uint32_t us)
{
    rt_int32_t i;
    for (; us > 0; us--)
    {
        i = 50000;
        while(i > 0)
        {
            i--;
        }
    }
}


#if 0
/* Generate a pulse on the i2c clock pin. */
static void generic_i2c_clock_pulse(unsigned int scl_pin)
{
    rt_uint16_t i;

    if (scl_pin) {
        /* Send high and low on the SCL line */
        for (i = 0; i < 9; i++) {
            gpio_set_value(scl_pin, 0);
            udelay(20);
            gpio_set_value(scl_pin, 1);
            udelay(20);
        }
    }
}
#endif

/* This routine does i2c bus recovery as specified in the
 * i2c protocol Rev. 03 section 3.16 titled "Bus clear"
 */
static void i2c_recover_bus(struct davinci_i2c_dev *dev)
{
    rt_uint32_t flag = 0;

    i2c_dbg("initiating i2c bus recovery\n");
    /* Send NACK to the slave */
    flag = davinci_i2c_read_reg(dev, DAVINCI_I2C_MDR_REG);
    flag |=  DAVINCI_I2C_MDR_NACK;
    /* write the data into mode register */
    davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, flag);
#if 0
    if (pdata)
        generic_i2c_clock_pulse(pdata->scl_pin);
#endif
    /* Send STOP */
    flag = davinci_i2c_read_reg(dev, DAVINCI_I2C_MDR_REG);
    flag |= DAVINCI_I2C_MDR_STP;
    davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, flag);
}

static inline void davinci_i2c_reset_ctrl(struct davinci_i2c_dev *i2c_dev,
                                int val)
{
    rt_uint16_t w;

    w = davinci_i2c_read_reg(i2c_dev, DAVINCI_I2C_MDR_REG);
    if (!val)   /* put I2C into reset */
        w &= ~DAVINCI_I2C_MDR_IRS;
    else        /* take I2C out of reset */
        w |= DAVINCI_I2C_MDR_IRS;

    davinci_i2c_write_reg(i2c_dev, DAVINCI_I2C_MDR_REG, w);
}

static void i2c_davinci_calc_clk_dividers(struct davinci_i2c_dev *dev)
{
    rt_uint16_t psc;
    rt_uint32_t clk;
    rt_uint32_t d;
    rt_uint32_t clkh;
    rt_uint32_t clkl;
    rt_uint32_t input_clock = clk_get_rate(dev->clk);

    /* NOTE: I2C Clock divider programming info
     * As per I2C specs the following formulas provide prescaler
     * and low/high divider values
     * input clk --> PSC Div -----------> ICCL/H Div --> output clock
     *                       module clk
     *
     * output clk = module clk / (PSC + 1) [ (ICCL + d) + (ICCH + d) ]
     *
     * Thus,
     * (ICCL + ICCH) = clk = (input clk / ((psc +1) * output clk)) - 2d;
     *
     * where if PSC == 0, d = 7,
     *       if PSC == 1, d = 6
     *       if PSC > 1 , d = 5
     */

    /* get minimum of 7 MHz clock, but max of 12 MHz */
    psc = (input_clock / 7000000) - 1;
    if ((input_clock / (psc + 1)) > 12000000)
        psc++;  /* better to run under spec than over */
    d = (psc >= 2) ? 5 : 7 - psc;

    clk = ((input_clock / (psc + 1)) / (dev->bus_freq * 1000)) - (d << 1);
    clkh = clk >> 1;
    clkl = clk - clkh;

    davinci_i2c_write_reg(dev, DAVINCI_I2C_PSC_REG, psc);
    davinci_i2c_write_reg(dev, DAVINCI_I2C_CLKH_REG, clkh);
    davinci_i2c_write_reg(dev, DAVINCI_I2C_CLKL_REG, clkl);

    i2c_dbg("input_clock = %d, CLK = %d\n", input_clock, clk);
}

/*
 * This function configures I2C and brings I2C out of reset.
 * This function is called during I2C init function. This function
 * also gets called if I2C encounters any errors.
 */
static int i2c_davinci_init(struct davinci_i2c_dev *dev)
{
    /* put I2C into reset */
    davinci_i2c_reset_ctrl(dev, 0);

    /* compute clock dividers */
    i2c_davinci_calc_clk_dividers(dev);

    /* Respond at reserved "SMBus Host" slave address" (and zero);
     * we seem to have no option to not respond...
     */
    davinci_i2c_write_reg(dev, DAVINCI_I2C_OAR_REG, 0x08);

    i2c_dbg("PSC  = %d\n",
        davinci_i2c_read_reg(dev, DAVINCI_I2C_PSC_REG));
    i2c_dbg("CLKL = %d\n",
        davinci_i2c_read_reg(dev, DAVINCI_I2C_CLKL_REG));
    i2c_dbg("CLKH = %d\n",
        davinci_i2c_read_reg(dev, DAVINCI_I2C_CLKH_REG));
    i2c_dbg("bus_freq = %dkHz, bus_delay = %d\n",
        dev->bus_freq, dev->bus_delay);

    /* Take the I2C module out of reset: */
    davinci_i2c_reset_ctrl(dev, 1);

    /* Enable interrupts */
    davinci_i2c_write_reg(dev, DAVINCI_I2C_IMR_REG, I2C_DAVINCI_INTR_ALL);

    return 0;
}

/*
 * Waiting for bus not busy
 */
static int i2c_davinci_wait_bus_not_busy(struct davinci_i2c_dev *dev,
                     char allow_sleep)
{
    unsigned long timeout;
    static rt_uint16_t to_cnt;
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->bus != RT_NULL);

    timeout = rt_tick_get() + dev->bus->timeout;
    while (davinci_i2c_read_reg(dev, DAVINCI_I2C_STR_REG)
           & DAVINCI_I2C_STR_BB) {
        if (to_cnt <= DAVINCI_I2C_MAX_TRIES) {
            if (rt_tick_get() >= timeout) {
                rt_kprintf("timeout waiting for bus ready\n");
                to_cnt++;
                return -RT_ETIMEOUT;
            } else {
                to_cnt = 0;
                i2c_recover_bus(dev);
                i2c_davinci_init(dev);
            }
        }
        if (allow_sleep)
            rt_thread_delay(2);
    }

    return 0;
}

/*
 * Low level master read/write transaction. This function is called
 * from i2c_davinci_xfer.
 */
static int
i2c_davinci_xfer_msg(struct rt_i2c_bus_device *bus, struct rt_i2c_msg *msg, int stop)
{
    struct davinci_i2c_dev *dev = bus->priv;
    rt_uint32_t flag;
    rt_uint16_t w;
    int r;

    /* Introduce a delay, required for some boards (e.g Davinci EVM) */
    if (dev->bus_delay)
        udelay(dev->bus_delay);

    /* set the slave address */
    davinci_i2c_write_reg(dev, DAVINCI_I2C_SAR_REG, msg->addr);

    dev->buf = msg->buf;
    dev->buf_len = msg->len;
    dev->stop = stop;

    davinci_i2c_write_reg(dev, DAVINCI_I2C_CNT_REG, dev->buf_len);

    //INIT_COMPLETION(dev->cmd_complete);
    dev->cmd_err = 0;

    /* Take I2C out of reset and configure it as master */
    flag = DAVINCI_I2C_MDR_IRS | DAVINCI_I2C_MDR_MST;

    /* if the slave address is ten bit address, enable XA bit */
    if (msg->flags & RT_I2C_ADDR_10BIT)
        flag |= DAVINCI_I2C_MDR_XA;
    if (!(msg->flags & RT_I2C_RD))
        flag |= DAVINCI_I2C_MDR_TRX;
    if (msg->len == 0)
        flag |= DAVINCI_I2C_MDR_RM;

    /* Enable receive or transmit interrupts */
    w = davinci_i2c_read_reg(dev, DAVINCI_I2C_IMR_REG);
    if (msg->flags & RT_I2C_RD)
        w |= DAVINCI_I2C_IMR_RRDY;
    else
        w |= DAVINCI_I2C_IMR_XRDY;
    davinci_i2c_write_reg(dev, DAVINCI_I2C_IMR_REG, w);

    dev->terminate = 0;

    /*
     * Write mode register first as needed for correct behaviour
     * on OMAP-L138, but don't set STT yet to avoid a race with XRDY
     * occurring before we have loaded DXR
     */
    davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, flag);

    /*
     * First byte should be set here, not after interrupt,
     * because transmit-data-ready interrupt can come before
     * NACK-interrupt during sending of previous message and
     * ICDXR may have wrong data
     * It also saves us one interrupt, slightly faster
     */
    if ((!(msg->flags & RT_I2C_RD)) && dev->buf_len)
    {
        davinci_i2c_write_reg(dev, DAVINCI_I2C_DXR_REG, *dev->buf++);
        dev->buf_len--;
    }

    /* Set STT to begin transmit now DXR is loaded */
    flag |= DAVINCI_I2C_MDR_STT;
    if (stop && msg->len != 0)
        flag |= DAVINCI_I2C_MDR_STP;
    davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, flag);

    r = rt_sem_take(&dev->completion, dev->bus->timeout);
    if (r == -RT_ETIMEOUT)
    {
        rt_kprintf("controller timed out\n");
        i2c_recover_bus(dev);
        i2c_davinci_init(dev);
        dev->buf_len = 0;
        return -RT_ETIMEOUT;
    }
    if (dev->buf_len)
    {
        /* This should be 0 if all bytes were transferred
         * or dev->cmd_err denotes an error.
         * A signal may have aborted the transfer.
         */
        if (r == RT_EOK)
        {
            rt_kprintf("abnormal termination buf_len=%i\n",
                dev->buf_len);
            r = -RT_EIO;
        }
        dev->terminate = 1;
        dev->buf_len = 0;
    }
    if (r < 0)
        return r;

    /* no error */
    if (!dev->cmd_err)
        return msg->len;

    /* We have an error */
    if (dev->cmd_err & DAVINCI_I2C_STR_AL)
    {
        i2c_davinci_init(dev);
        return -RT_EIO;
    }

    if (dev->cmd_err & DAVINCI_I2C_STR_NACK)
    {
        if (msg->flags & RT_I2C_IGNORE_NACK)
            return msg->len;
        if (stop)
        {
            w = davinci_i2c_read_reg(dev, DAVINCI_I2C_MDR_REG);
            w |= DAVINCI_I2C_MDR_STP;
            davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, w);
        }
        return -RT_EIO;
    }
    return -RT_EIO;
}

/*
 * Prepare controller for a transaction and call i2c_davinci_xfer_msg
 */
static int
i2c_davinci_xfer(struct rt_i2c_bus_device *bus, struct rt_i2c_msg msgs[], int num)
{
    struct davinci_i2c_dev *dev = bus->priv;
    int i;
    int ret;

    i2c_dbg("%s: msgs: %d\n", __func__, num);

    ret = i2c_davinci_wait_bus_not_busy(dev, 1);
    if (ret < 0)
    {
        i2c_dbg("timeout waiting for bus ready\n");
        return ret;
    }

    for (i = 0; i < num; i++)
    {
        ret = i2c_davinci_xfer_msg(bus, &msgs[i], (i == (num - 1)));
        i2c_dbg("%s [%d/%d] ret: %d\n", __func__, i + 1, num,
            ret);
        if (ret < 0)
            return ret;
    }


    return num;
}


static void terminate_read(struct davinci_i2c_dev *dev)
{
    rt_uint16_t w = davinci_i2c_read_reg(dev, DAVINCI_I2C_MDR_REG);
    w |= DAVINCI_I2C_MDR_NACK;
    davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, w);

    /* Throw away data */
    davinci_i2c_read_reg(dev, DAVINCI_I2C_DRR_REG);
    if (!dev->terminate)
        rt_kprintf("RDR IRQ while no data requested\n");
}
static void terminate_write(struct davinci_i2c_dev *dev)
{
    rt_uint16_t w = davinci_i2c_read_reg(dev, DAVINCI_I2C_MDR_REG);
    w |= DAVINCI_I2C_MDR_RM | DAVINCI_I2C_MDR_STP;
    davinci_i2c_write_reg(dev, DAVINCI_I2C_MDR_REG, w);

    if (!dev->terminate)
        i2c_dbg("TDR IRQ while no data to send\n");
}

/*
 * Interrupt service routine. This gets called whenever an I2C interrupt
 * occurs.
 */
static void i2c_davinci_isr(int irq, void *param)
{
    struct davinci_i2c_dev *dev = (struct davinci_i2c_dev *)param;
    rt_uint32_t stat;
    int count = 0;
    rt_uint16_t w;

    while ((stat = davinci_i2c_read_reg(dev, DAVINCI_I2C_IVR_REG))) {
        i2c_dbg("%s: stat=0x%x\n", __func__, stat);
        if (count++ == 100) {
            rt_kprintf("Too much work in one IRQ\n");
            break;
        }

        switch (stat) {
        case DAVINCI_I2C_IVR_AL:
            /* Arbitration lost, must retry */
            dev->cmd_err |= DAVINCI_I2C_STR_AL;
            dev->buf_len = 0;
            rt_sem_release(&dev->completion);
            break;

        case DAVINCI_I2C_IVR_NACK:
            dev->cmd_err |= DAVINCI_I2C_STR_NACK;
            dev->buf_len = 0;
            rt_sem_release(&dev->completion);
            break;

        case DAVINCI_I2C_IVR_ARDY:
            davinci_i2c_write_reg(dev,
                DAVINCI_I2C_STR_REG, DAVINCI_I2C_STR_ARDY);
            if (((dev->buf_len == 0) && (dev->stop != 0)) ||
                (dev->cmd_err & DAVINCI_I2C_STR_NACK)) {
                w = davinci_i2c_read_reg(dev,
                             DAVINCI_I2C_MDR_REG);
                w |= DAVINCI_I2C_MDR_STP;
                davinci_i2c_write_reg(dev,
                              DAVINCI_I2C_MDR_REG, w);
            }
            rt_sem_release(&dev->completion);
            break;

        case DAVINCI_I2C_IVR_RDR:
            if (dev->buf_len) {
                *dev->buf++ =
                    davinci_i2c_read_reg(dev,
                             DAVINCI_I2C_DRR_REG);
                dev->buf_len--;
                if (dev->buf_len)
                    continue;

                davinci_i2c_write_reg(dev,
                    DAVINCI_I2C_STR_REG,
                    DAVINCI_I2C_IMR_RRDY);
            } else {
                /* signal can terminate transfer */
                terminate_read(dev);
            }
            break;

        case DAVINCI_I2C_IVR_XRDY:
            if (dev->buf_len) {
                davinci_i2c_write_reg(dev, DAVINCI_I2C_DXR_REG,
                              *dev->buf++);
                dev->buf_len--;
                if (dev->buf_len)
                    continue;

                w = davinci_i2c_read_reg(dev,
                             DAVINCI_I2C_IMR_REG);
                w &= ~DAVINCI_I2C_IMR_XRDY;
                davinci_i2c_write_reg(dev,
                              DAVINCI_I2C_IMR_REG,
                              w);
            } else {
                /* signal can terminate transfer */
                terminate_write(dev);
            }
            break;

        case DAVINCI_I2C_IVR_SCD:
            davinci_i2c_write_reg(dev,
                DAVINCI_I2C_STR_REG, DAVINCI_I2C_STR_SCD);
            rt_sem_release(&dev->completion);
            break;

        case DAVINCI_I2C_IVR_AAS:
            i2c_dbg("Address as slave interrupt\n");
            break;

        default:
            i2c_dbg("Unrecognized irq stat %d\n", stat);
            break;
        }
    }

}



static struct rt_i2c_bus_device_ops bus_ops = {
    .master_xfer    = i2c_davinci_xfer,
};

int davinci_i2c_init(char *bus_name)
{
    struct rt_i2c_bus_device *bus;
    struct davinci_i2c_dev *dev;
    int r;

    bus = rt_malloc(sizeof(struct rt_i2c_bus_device));
    if (bus == RT_NULL)
    {
        rt_kprintf("rt_malloc failed\n");
        return -RT_ENOMEM;
    }

    rt_memset((void *)bus, 0, sizeof(struct rt_i2c_bus_device));

    bus->ops = &bus_ops;
    bus->timeout = DAVINCI_I2C_TIMEOUT;

    dev = rt_malloc(sizeof(struct davinci_i2c_dev));
    if (!dev)
    {
        r = -RT_ENOMEM;
        goto err;
    }

    rt_memset((void *)dev, 0, sizeof(struct davinci_i2c_dev));

    rt_sem_init(&dev->completion, "i2c_ack", 0, RT_IPC_FLAG_FIFO);

    dev->irq = IRQ_I2C;

    dev->clk = clk_get("I2CCLK");
    if (dev->clk == RT_NULL) {
        r = -RT_ERROR;
        goto err1;
    }

    psc_change_state(DAVINCI_DM365_LPSC_I2C, 3);

    dev->base = DAVINCI_I2C_BASE;
    dev->bus_freq = 100;
    dev->bus_delay = 0;
    dev->bus = bus;

    bus->priv = dev;

    i2c_davinci_init(dev);

    rt_hw_interrupt_install(dev->irq, i2c_davinci_isr, (void *)dev, "I2C");
    rt_hw_interrupt_umask(dev->irq);

    return rt_i2c_bus_device_register(bus, bus_name);

err1:
    rt_free(dev);

err:
    rt_free(bus);

    return r;
}

int rt_hw_iic_init(void)
{
    davinci_i2c_init("I2C1");
}

INIT_DEVICE_EXPORT(rt_hw_iic_init);

