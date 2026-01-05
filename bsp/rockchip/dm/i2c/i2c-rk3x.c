/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "i2c.rk3x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/dev_i2c_dm.h>

/* Register Map */
#define REG_CON                 0x00 /* control register */
#define REG_CLKDIV              0x04 /* clock divisor register */
#define REG_MRXADDR             0x08 /* slave address for REGISTER_TX */
#define REG_MRXRADDR            0x0c /* slave register address for REGISTER_TX */
#define REG_MTXCNT              0x10 /* number of bytes to be transmitted */
#define REG_MRXCNT              0x14 /* number of bytes to be received */
#define REG_IEN                 0x18 /* interrupt enable */
#define REG_IPD                 0x1c /* interrupt pending */
#define REG_FCNT                0x20 /* finished count */

/* Data buffer offsets */
#define TXBUFFER_BASE           0x100
#define RXBUFFER_BASE           0x200

/* REG_CON bits */
#define REG_CON_EN              RT_BIT(0)

enum
{
    REG_CON_MOD_TX = 0,      /* transmit data */
    REG_CON_MOD_REGISTER_TX, /* select register and restart */
    REG_CON_MOD_RX,          /* receive data */
    REG_CON_MOD_REGISTER_RX, /* broken: transmits read addr AND writes register addr */
};

#define REG_CON_MOD(mod)        ((mod) << 1)
#define REG_CON_MOD_MASK        (RT_BIT(1) | RT_BIT(2))
#define REG_CON_START           RT_BIT(3)
#define REG_CON_STOP            RT_BIT(4)
#define REG_CON_LASTACK         RT_BIT(5) /* 1: send NACK after last received byte */
#define REG_CON_ACTACK          RT_BIT(6) /* 1: stop if NACK is received */

#define REG_CON_TUNING_MASK     RT_GENMASK_ULL(15, 8)

#define REG_CON_SDA_CFG(cfg)    ((cfg) << 8)
#define REG_CON_STA_CFG(cfg)    ((cfg) << 12)
#define REG_CON_STO_CFG(cfg)    ((cfg) << 14)

/* REG_MRXADDR bits */
#define REG_MRXADDR_VALID(x)    RT_BIT(24 + (x)) /* [x*8+7:x*8] of MRX[R]ADDR valid */

/* REG_IEN/REG_IPD bits */
#define REG_INT_BTF             RT_BIT(0) /* a byte was transmitted */
#define REG_INT_BRF             RT_BIT(1) /* a byte was received */
#define REG_INT_MBTF            RT_BIT(2) /* master data transmit finished */
#define REG_INT_MBRF            RT_BIT(3) /* master data receive finished */
#define REG_INT_START           RT_BIT(4) /* START condition generated */
#define REG_INT_STOP            RT_BIT(5) /* STOP condition generated */
#define REG_INT_NAKRCV          RT_BIT(6) /* NACK received */
#define REG_INT_ALL             0x7f

/* Constants */
#define WAIT_TIMEOUT            1000 /* ms */
#define DEFAULT_SCL_RATE        (100 * 1000) /* Hz */

/* I2C specification values for various modes */
struct i2c_spec_values
{
    rt_ubase_t min_hold_start_ns;   /* min hold time (repeated) START condition */
    rt_ubase_t min_low_ns;          /* min LOW period of the SCL clock */
    rt_ubase_t min_high_ns;         /* min HIGH period of the SCL cloc */
    rt_ubase_t min_setup_start_ns;  /* min set-up time for a repeated START conditio */
    rt_ubase_t max_data_hold_ns;    /* max data hold time */
    rt_ubase_t min_data_setup_ns;   /* min data set-up time */
    rt_ubase_t min_setup_stop_ns;   /* min set-up time for STOP condition */
    rt_ubase_t min_hold_buffer_ns;  /* min bus free time between a STOP and */
};

static const struct i2c_spec_values standard_mode_spec =
{
    .min_hold_start_ns = 4000,
    .min_low_ns = 4700,
    .min_high_ns = 4000,
    .min_setup_start_ns = 4700,
    .max_data_hold_ns = 3450,
    .min_data_setup_ns = 250,
    .min_setup_stop_ns = 4000,
    .min_hold_buffer_ns = 4700,
};

static const struct i2c_spec_values fast_mode_spec =
{
    .min_hold_start_ns = 600,
    .min_low_ns = 1300,
    .min_high_ns = 600,
    .min_setup_start_ns = 600,
    .max_data_hold_ns = 900,
    .min_data_setup_ns = 100,
    .min_setup_stop_ns = 600,
    .min_hold_buffer_ns = 1300,
};

static const struct i2c_spec_values fast_mode_plus_spec =
{
    .min_hold_start_ns = 260,
    .min_low_ns = 500,
    .min_high_ns = 260,
    .min_setup_start_ns = 260,
    .max_data_hold_ns = 400,
    .min_data_setup_ns = 50,
    .min_setup_stop_ns = 260,
    .min_hold_buffer_ns = 500,
};

/*
 * Calculated V1 timings, setup/hold start time and setup stop time for v1's
 * calc_timings, the tuning should all be 0 for old hardware anyone using v0's
 * calc_timings.
 */
struct rk3x_i2c_calced_timings
{
    rt_ubase_t div_low;     /* Divider output for low */
    rt_ubase_t div_high;    /* Divider output for high */
    rt_uint32_t tuning;     /* Used to adjust setup/hold data time */
};

enum rk3x_i2c_state
{
    STATE_IDLE,
    STATE_START,
    STATE_READ,
    STATE_WRITE,
    STATE_STOP
};

struct rk3x_i2c_soc_data
{
    int grf_offset;
    rt_err_t (*calc_timings)(rt_ubase_t, struct i2c_timings *,
            struct rk3x_i2c_calced_timings *);
};

struct rk3x_i2c
{
    struct rt_i2c_bus_device parent;

    const struct rk3x_i2c_soc_data *soc_data;

    int irq;
    void *regs;

    struct rt_clk *clk;
    struct rt_clk *pclk;
    struct rt_clk_notifier clk_notifier;

    struct i2c_timings timings;

    struct rt_spinlock lock;
    struct rt_completion done;

    struct rt_i2c_msg *msg;
    rt_uint8_t addr;
    rt_uint32_t mode;
    rt_bool_t is_last_msg;

    enum rk3x_i2c_state state;
    rt_uint32_t processed;
    rt_err_t error;
};

#define raw_to_rk3x_i2c(raw) rt_container_of(raw, struct rk3x_i2c, parent)

rt_inline void i2c_writel(struct rk3x_i2c *i2c, rt_uint32_t value, int offset)
{
    HWREG32(i2c->regs + offset) = value;
}

rt_inline rt_uint32_t i2c_readl(struct rk3x_i2c *i2c, int offset)
{
    return HWREG32(i2c->regs + offset);
}

/* Reset all interrupt pending bits */
rt_inline void rk3x_i2c_clean_ipd(struct rk3x_i2c *i2c)
{
    i2c_writel(i2c, REG_INT_ALL, REG_IPD);
}

/* Generate a START condition, which triggers a REG_INT_START interrupt */
static void rk3x_i2c_start(struct rk3x_i2c *i2c)
{
    rt_uint32_t val = i2c_readl(i2c, REG_CON) & REG_CON_TUNING_MASK;

    i2c_writel(i2c, REG_INT_START, REG_IEN);

    /* enable adapter with correct mode, send START condition */
    val |= REG_CON_EN | REG_CON_MOD(i2c->mode) | REG_CON_START;

    /* if we want to react to NACK, set ACTACK bit */
    if (!(i2c->msg->flags & RT_I2C_IGNORE_NACK))
    {
        val |= REG_CON_ACTACK;
    }

    i2c_writel(i2c, val, REG_CON);
}

/* Generate a STOP condition, which triggers a REG_INT_STOP interrupt */
static void rk3x_i2c_stop(struct rk3x_i2c *i2c, rt_err_t error)
{
    rt_uint32_t ctrl;

    i2c->processed = 0;
    i2c->msg = RT_NULL;
    i2c->error = error;

    if (i2c->is_last_msg)
    {
        /* Enable stop interrupt */
        i2c_writel(i2c, REG_INT_STOP, REG_IEN);

        i2c->state = STATE_STOP;

        ctrl = i2c_readl(i2c, REG_CON);
        ctrl |= REG_CON_STOP;
        i2c_writel(i2c, ctrl, REG_CON);
    }
    else
    {
        /* Signal rk3x_i2c_xfer to start the next message. */
        i2c->state = STATE_IDLE;

        /*
         * The HW is actually not capable of REPEATED START. But we can
         * get the intended effect by resetting its internal state
         * and issuing an ordinary START.
         */
        ctrl = i2c_readl(i2c, REG_CON) & REG_CON_TUNING_MASK;
        i2c_writel(i2c, ctrl, REG_CON);

        /* signal that we are finished with the current msg */
        rt_completion_done(&i2c->done);
    }
}

/* Setup a read according to i2c->msg */
static void rk3x_i2c_prepare_read(struct rk3x_i2c *i2c)
{
    rt_uint32_t con, len = i2c->msg->len - i2c->processed;

    con = i2c_readl(i2c, REG_CON);

    /*
     * The hw can read up to 32 bytes at a time. If we need more than one
     * chunk, send an ACK after the last byte of the current chunk.
     */
    if (len > 32)
    {
        len = 32;
        con &= ~REG_CON_LASTACK;
    }
    else
    {
        con |= REG_CON_LASTACK;
    }

    /* make sure we are in plain RX mode if we read a second chunk */
    if (i2c->processed != 0)
    {
        con &= ~REG_CON_MOD_MASK;
        con |= REG_CON_MOD(REG_CON_MOD_RX);
    }

    i2c_writel(i2c, con, REG_CON);
    i2c_writel(i2c, len, REG_MRXCNT);
}

/* Fill the transmit buffer with data from i2c->msg */
static void rk3x_i2c_fill_transmit_buf(struct rk3x_i2c *i2c)
{
    rt_uint32_t cnt = 0;

    for (int i = 0; i < 8; ++i)
    {
        rt_uint32_t val = 0;

        for (int j = 0; j < 4; ++j)
        {
            rt_uint8_t byte;

            if ((i2c->processed == i2c->msg->len) && (cnt != 0))
            {
                break;
            }

            if (i2c->processed == 0 && cnt == 0)
            {
                byte = (i2c->addr & 0x7f) << 1;
            }
            else
            {
                byte = i2c->msg->buf[i2c->processed++];
            }

            val |= byte << (j * 8);
            cnt++;
        }

        i2c_writel(i2c, val, TXBUFFER_BASE + 4 * i);

        if (i2c->processed == i2c->msg->len)
        {
            break;
        }
    }

    i2c_writel(i2c, cnt, REG_MTXCNT);
}

/* IRQ handlers for individual states */
static void rk3x_i2c_handle_start(struct rk3x_i2c *i2c, rt_uint32_t ipd)
{
    if (!(ipd & REG_INT_START))
    {
        rk3x_i2c_stop(i2c, -RT_EIO);
        LOG_W("Unexpected irq in START: 0x%x", ipd);
        rk3x_i2c_clean_ipd(i2c);

        return;
    }

    /* ack interrupt */
    i2c_writel(i2c, REG_INT_START, REG_IPD);

    /* disable start bit */
    i2c_writel(i2c, i2c_readl(i2c, REG_CON) & ~REG_CON_START, REG_CON);

    /* enable appropriate interrupts and transition */
    if (i2c->mode == REG_CON_MOD_TX)
    {
        i2c_writel(i2c, REG_INT_MBTF | REG_INT_NAKRCV, REG_IEN);
        i2c->state = STATE_WRITE;
        rk3x_i2c_fill_transmit_buf(i2c);
    }
    else
    {
        /* in any other case, we are going to be reading. */
        i2c_writel(i2c, REG_INT_MBRF | REG_INT_NAKRCV, REG_IEN);
        i2c->state = STATE_READ;
        rk3x_i2c_prepare_read(i2c);
    }
}

static void rk3x_i2c_handle_write(struct rk3x_i2c *i2c, rt_uint32_t ipd)
{
    if (!(ipd & REG_INT_MBTF))
    {
        rk3x_i2c_stop(i2c, -RT_EIO);
        LOG_E("Unexpected irq in WRITE: 0x%x", ipd);
        rk3x_i2c_clean_ipd(i2c);

        return;
    }

    /* ack interrupt */
    i2c_writel(i2c, REG_INT_MBTF, REG_IPD);

    /* are we finished? */
    if (i2c->processed == i2c->msg->len)
    {
        rk3x_i2c_stop(i2c, i2c->error);
    }
    else
    {
        rk3x_i2c_fill_transmit_buf(i2c);
    }
}

static void rk3x_i2c_handle_read(struct rk3x_i2c *i2c, unsigned int ipd)
{
    rt_uint32_t val = 0, len = i2c->msg->len - i2c->processed;

    /* we only care for MBRF here. */
    if (!(ipd & REG_INT_MBRF))
    {
        return;
    }

    /* ack interrupt (read also produces a spurious START flag, clear it too) */
    i2c_writel(i2c, REG_INT_MBRF | REG_INT_START, REG_IPD);

    /* Can only handle a maximum of 32 bytes at a time */
    if (len > 32)
    {
        len = 32;
    }

    /* read the data from receive buffer */
    for (int i = 0; i < len; ++i)
    {
        rt_uint8_t byte;

        if (i % 4 == 0)
        {
            val = i2c_readl(i2c, RXBUFFER_BASE + (i / 4) * 4);
        }

        byte = (val >> ((i % 4) * 8)) & 0xff;
        i2c->msg->buf[i2c->processed++] = byte;
    }

    /* are we finished? */
    if (i2c->processed == i2c->msg->len)
    {
        rk3x_i2c_stop(i2c, i2c->error);
    }
    else
    {
        rk3x_i2c_prepare_read(i2c);
    }
}

static void rk3x_i2c_handle_stop(struct rk3x_i2c *i2c, rt_uint32_t ipd)
{
    rt_uint32_t con;

    if (!(ipd & REG_INT_STOP))
    {
        rk3x_i2c_stop(i2c, -RT_EIO);
        LOG_E("Unexpected irq in STOP: 0x%x", ipd);
        rk3x_i2c_clean_ipd(i2c);

        return;
    }

    /* ack interrupt */
    i2c_writel(i2c, REG_INT_STOP, REG_IPD);

    /* disable STOP bit */
    con = i2c_readl(i2c, REG_CON);
    con &= ~REG_CON_STOP;
    i2c_writel(i2c, con, REG_CON);

    i2c->state = STATE_IDLE;

    /* signal rk3x_i2c_xfer that we are finished */
    rt_completion_done(&i2c->done);
}

static void rk3x_i2c_adapt_div(struct rk3x_i2c *i2c, rt_ubase_t clk_rate)
{
    rt_err_t err;
    rt_ubase_t level;
    rt_uint32_t val;
    struct rk3x_i2c_calced_timings calc;
    struct i2c_timings *timings = &i2c->timings;

    if ((err = i2c->soc_data->calc_timings(clk_rate, timings, &calc)))
    {
        LOG_W("Could not reach SCL freq %u", timings->bus_freq_hz);
    }

    rt_clk_enable(i2c->pclk);

    level = rt_spin_lock_irqsave(&i2c->lock);

    val = i2c_readl(i2c, REG_CON);
    val &= ~REG_CON_TUNING_MASK;
    val |= calc.tuning;
    i2c_writel(i2c, val, REG_CON);
    i2c_writel(i2c, (calc.div_high << 16) | (calc.div_low & 0xffff), REG_CLKDIV);

    rt_spin_unlock_irqrestore(&i2c->lock, level);

    rt_clk_disable(i2c->pclk);
}

static rt_err_t rk3x_i2c_clk_notifier(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    struct rk3x_i2c_calced_timings calc;
    struct rk3x_i2c *i2c = rt_container_of(notifier, struct rk3x_i2c, clk_notifier);

    switch (msg)
    {
    case RT_CLK_MSG_PRE_RATE_CHANGE:
        /*
         * Try the calculation (but don't store the result) ahead of
         * time to see if we need to block the clock change.  Timings
         * shouldn't actually take effect until rk3x_i2c_adapt_div().
         */
        if (i2c->soc_data->calc_timings(new_rate, &i2c->timings, &calc) != 0)
        {
            return -RT_EIO;
        }

        /* scale up */
        if (new_rate > old_rate)
        {
            rk3x_i2c_adapt_div(i2c, new_rate);
        }
        break;

    case RT_CLK_MSG_POST_RATE_CHANGE:
        /* scale down */
        if (new_rate < old_rate)
        {
            rk3x_i2c_adapt_div(i2c, new_rate);
        }
        break;

    case RT_CLK_MSG_ABORT_RATE_CHANGE:
        /* scale up */
        if (new_rate > old_rate)
        {
            rk3x_i2c_adapt_div(i2c, old_rate);
        }
        break;

    default:
        break;
    }

    return RT_EOK;
}

static const struct i2c_spec_values *rk3x_i2c_get_spec(rt_uint32_t speed)
{
    if (speed <= I2C_MAX_STANDARD_MODE_FREQ)
    {
        return &standard_mode_spec;
    }
    else if (speed <= I2C_MAX_FAST_MODE_FREQ)
    {
        return &fast_mode_spec;
    }
    else
    {
        return &fast_mode_plus_spec;
    }
}

/**
 * rk3x_i2c_v0_calc_timings - Calculate divider values for desired SCL frequency
 * @clk_rate: I2C input clock rate
 * @t: Known I2C timing information
 * @t_calc: Caculated rk3x private timings that would be written into regs
 *
 * Return: %0 on success, -%EINVAL if the goal SCL rate is too slow. In that case
 * a best-effort divider value is returned in divs. If the target rate is
 * too high, we silently use the highest possible rate.
 */
static rt_err_t rk3x_i2c_v0_calc_timings(rt_ubase_t clk_rate,
        struct i2c_timings *t, struct rk3x_i2c_calced_timings *t_calc)
{
    rt_err_t err = RT_EOK;
    rt_ubase_t min_low_ns, min_high_ns;
    rt_ubase_t max_low_ns, min_total_ns;
    rt_ubase_t clk_rate_khz, scl_rate_khz;
    rt_ubase_t min_low_div, min_high_div;
    rt_ubase_t max_low_div;
    rt_ubase_t min_div_for_hold, min_total_div;
    rt_ubase_t extra_div, extra_low_div, ideal_low_div;
    rt_ubase_t data_hold_buffer_ns = 50;
    const struct i2c_spec_values *spec;

    /* Only support standard-mode and fast-mode */
    if (t->bus_freq_hz > I2C_MAX_FAST_MODE_FREQ)
    {
        t->bus_freq_hz = I2C_MAX_FAST_MODE_FREQ;
    }

    /* prevent scl_rate_khz from becoming 0 */
    if (t->bus_freq_hz < 1000)
    {
        t->bus_freq_hz = 1000;
    }

    /*
     * min_low_ns:  The minimum number of ns we need to hold low to
     *      meet I2C specification, should include fall time.
     * min_high_ns: The minimum number of ns we need to hold high to
     *      meet I2C specification, should include rise time.
     * max_low_ns:  The maximum number of ns we can hold low to meet
     *      I2C specification.
     *
     * Note: max_low_ns should be (maximum data hold time * 2 - buffer)
     *   This is because the i2c host on Rockchip holds the data line
     *   for half the low time.
     */
    spec = rk3x_i2c_get_spec(t->bus_freq_hz);
    min_high_ns = t->scl_rise_ns + spec->min_high_ns;

    /*
     * Timings for repeated start:
     * - controller appears to drop SDA at .875x (7/8) programmed clk high.
     * - controller appears to keep SCL high for 2x programmed clk high.
     *
     * We need to account for those rules in picking our "high" time so
     * we meet tSU;STA and tHD;STA times.
     */
    min_high_ns = rt_max(min_high_ns, RT_DIV_ROUND_UP(
            (t->scl_rise_ns + spec->min_setup_start_ns) * 1000, 875));
    min_high_ns = rt_max(min_high_ns, RT_DIV_ROUND_UP(
            (t->scl_rise_ns + spec->min_setup_start_ns + t->sda_fall_ns +
            spec->min_high_ns), 2));

    min_low_ns = t->scl_fall_ns + spec->min_low_ns;
    max_low_ns =  spec->max_data_hold_ns * 2 - data_hold_buffer_ns;
    min_total_ns = min_low_ns + min_high_ns;

    /* Adjust to avoid overflow */
    clk_rate_khz = RT_DIV_ROUND_UP(clk_rate, 1000);
    scl_rate_khz = t->bus_freq_hz / 1000;

    /*
     * We need the total div to be >= this number
     * so we don't clock too fast.
     */
    min_total_div = RT_DIV_ROUND_UP(clk_rate_khz, scl_rate_khz * 8);

    /* These are the min dividers needed for min hold times. */
    min_low_div = RT_DIV_ROUND_UP(clk_rate_khz * min_low_ns, 8 * 1000000);
    min_high_div = RT_DIV_ROUND_UP(clk_rate_khz * min_high_ns, 8 * 1000000);
    min_div_for_hold = (min_low_div + min_high_div);

    /*
     * This is the maximum divider so we don't go over the maximum.
     * We don't round up here (we round down) since this is a maximum.
     */
    max_low_div = clk_rate_khz * max_low_ns / (8 * 1000000);

    if (min_low_div > max_low_div)
    {
        max_low_div = min_low_div;
    }

    if (min_div_for_hold > min_total_div)
    {
        /* Time needed to meet hold requirements is important. Just use that. */
        t_calc->div_low = min_low_div;
        t_calc->div_high = min_high_div;
    }
    else
    {
        /*
         * We've got to distribute some time among the low and high
         * so we don't run too fast.
         */
        extra_div = min_total_div - min_div_for_hold;

        /*
         * We'll try to split things up perfectly evenly,
         * biasing slightly towards having a higher div
         * for low (spend more time low).
         */
        ideal_low_div = RT_DIV_ROUND_UP(clk_rate_khz * min_low_ns,
                scl_rate_khz * 8 * min_total_ns);

        /* Don't allow it to go over the maximum */
        if (ideal_low_div > max_low_div)
        {
            ideal_low_div = max_low_div;
        }

        /* Handle when the ideal low div is going to take up more than we have. */
        if (ideal_low_div > min_low_div + extra_div)
        {
            ideal_low_div = min_low_div + extra_div;
        }

        /* Give low the "ideal" and give high whatever extra is left */
        extra_low_div = ideal_low_div - min_low_div;
        t_calc->div_low = ideal_low_div;
        t_calc->div_high = min_high_div + (extra_div - extra_low_div);
    }

    /*
     * Adjust to the fact that the hardware has an implicit "+1".
     * NOTE: Above calculations always produce div_low > 0 and div_high > 0.
     */
    --t_calc->div_low;
    --t_calc->div_high;

    /* Give the tuning value 0, that would not update con register */
    t_calc->tuning = 0;

    /* Maximum divider supported by hw is 0xffff */
    if (t_calc->div_low > 0xffff)
    {
        t_calc->div_low = 0xffff;
        err = -RT_EINVAL;
    }

    if (t_calc->div_high > 0xffff)
    {
        t_calc->div_high = 0xffff;
        err = -RT_EINVAL;
    }

    return err;
}

/**
 * rk3x_i2c_v1_calc_timings - Calculate timing values for desired SCL frequency
 * @clk_rate: I2C input clock rate
 * @t: Known I2C timing information
 * @t_calc: Caculated rk3x private timings that would be written into regs
 *
 * Return: %0 on success, -%EINVAL if the goal SCL rate is too slow. In that case
 * a best-effort divider value is returned in divs. If the target rate is
 * too high, we silently use the highest possible rate.
 * The following formulas are v1's method to calculate timings.
 *
 * l = divl + 1;
 * h = divh + 1;
 * s = sda_update_config + 1;
 * u = start_setup_config + 1;
 * p = stop_setup_config + 1;
 * T = Tclk_i2c;
 *
 * tHigh = 8 * h * T;
 * tLow = 8 * l * T;
 *
 * tHD;sda = (l * s + 1) * T;
 * tSU;sda = [(8 - s) * l + 1] * T;
 * tI2C = 8 * (l + h) * T;
 *
 * tSU;sta = (8h * u + 1) * T;
 * tHD;sta = [8h * (u + 1) - 1] * T;
 * tSU;sto = (8h * p + 1) * T;
 */
static rt_err_t rk3x_i2c_v1_calc_timings(rt_ubase_t clk_rate,
        struct i2c_timings *t, struct rk3x_i2c_calced_timings *t_calc)
{
    rt_err_t err = 0;
    rt_ubase_t min_low_ns, min_high_ns;
    rt_ubase_t min_setup_start_ns, min_setup_data_ns;
    rt_ubase_t min_setup_stop_ns, max_hold_data_ns;
    rt_ubase_t clk_rate_khz, scl_rate_khz;
    rt_ubase_t min_low_div, min_high_div;
    rt_ubase_t min_div_for_hold, min_total_div;
    rt_ubase_t extra_div, extra_low_div;
    rt_ubase_t sda_update_cfg, stp_sta_cfg, stp_sto_cfg;
    const struct i2c_spec_values *spec;

    /* Support standard-mode, fast-mode and fast-mode plus */
    if (t->bus_freq_hz > I2C_MAX_FAST_MODE_PLUS_FREQ)
    {
        t->bus_freq_hz = I2C_MAX_FAST_MODE_PLUS_FREQ;
    }

    /* prevent scl_rate_khz from becoming 0 */
    if (t->bus_freq_hz < 1000)
    {
        t->bus_freq_hz = 1000;
    }

    /*
     * min_low_ns: The minimum number of ns we need to hold low to
     *         meet I2C specification, should include fall time.
     * min_high_ns: The minimum number of ns we need to hold high to
     *          meet I2C specification, should include rise time.
     */
    spec = rk3x_i2c_get_spec(t->bus_freq_hz);

    /* calculate min-divh and min-divl */
    clk_rate_khz = RT_DIV_ROUND_UP(clk_rate, 1000);
    scl_rate_khz = t->bus_freq_hz / 1000;
    min_total_div = RT_DIV_ROUND_UP(clk_rate_khz, scl_rate_khz * 8);

    min_high_ns = t->scl_rise_ns + spec->min_high_ns;
    min_high_div = RT_DIV_ROUND_UP(clk_rate_khz * min_high_ns, 8 * 1000000);

    min_low_ns = t->scl_fall_ns + spec->min_low_ns;
    min_low_div = RT_DIV_ROUND_UP(clk_rate_khz * min_low_ns, 8 * 1000000);

    /*
     * Final divh and divl must be greater than 0, otherwise the
     * hardware would not output the i2c clk.
     */
    min_high_div = (min_high_div < 1) ? 2 : min_high_div;
    min_low_div = (min_low_div < 1) ? 2 : min_low_div;

    /* These are the min dividers needed for min hold times. */
    min_div_for_hold = (min_low_div + min_high_div);

    /*
     * This is the maximum divider so we don't go over the maximum.
     * We don't round up here (we round down) since this is a maximum.
     */
    if (min_div_for_hold >= min_total_div)
    {
        /*
         * Time needed to meet hold requirements is important.
         * Just use that.
         */
        t_calc->div_low = min_low_div;
        t_calc->div_high = min_high_div;
    }
    else
    {
        /*
         * We've got to distribute some time among the low and high
         * so we don't run too fast.
         * We'll try to split things up by the scale of min_low_div and
         * min_high_div, biasing slightly towards having a higher div
         * for low (spend more time low).
         */
        extra_div = min_total_div - min_div_for_hold;
        extra_low_div = RT_DIV_ROUND_UP(min_low_div * extra_div, min_div_for_hold);

        t_calc->div_low = min_low_div + extra_low_div;
        t_calc->div_high = min_high_div + (extra_div - extra_low_div);
    }

    /*
     * calculate sda data hold count by the rules, data_upd_st:3
     * is a appropriate value to reduce calculated times.
     */
    for (sda_update_cfg = 3; sda_update_cfg > 0; --sda_update_cfg)
    {
        max_hold_data_ns =  RT_DIV_ROUND_UP((sda_update_cfg
                * (t_calc->div_low) + 1) * 1000000, clk_rate_khz);
        min_setup_data_ns =  RT_DIV_ROUND_UP(((8 - sda_update_cfg)
                * (t_calc->div_low) + 1) * 1000000, clk_rate_khz);

        if (max_hold_data_ns < spec->max_data_hold_ns &&
            min_setup_data_ns > spec->min_data_setup_ns)
        {
            break;
        }
    }

    /* calculate setup start config */
    min_setup_start_ns = t->scl_rise_ns + spec->min_setup_start_ns;
    stp_sta_cfg = RT_DIV_ROUND_UP(clk_rate_khz * min_setup_start_ns - 1000000,
            8 * 1000000 * (t_calc->div_high));

    /* calculate setup stop config */
    min_setup_stop_ns = t->scl_rise_ns + spec->min_setup_stop_ns;
    stp_sto_cfg = RT_DIV_ROUND_UP(clk_rate_khz * min_setup_stop_ns - 1000000,
            8 * 1000000 * (t_calc->div_high));

    t_calc->tuning = REG_CON_SDA_CFG(--sda_update_cfg) |
            REG_CON_STA_CFG(--stp_sta_cfg) | REG_CON_STO_CFG(--stp_sto_cfg);

    --t_calc->div_low;
    --t_calc->div_high;

    /* Maximum divider supported by hw is 0xffff */
    if (t_calc->div_low > 0xffff)
    {
        t_calc->div_low = 0xffff;
        err = -RT_EINVAL;
    }

    if (t_calc->div_high > 0xffff)
    {
        t_calc->div_high = 0xffff;
        err = -RT_EINVAL;
    }

    return err;
}

/* Setup I2C registers for an I2C operation specified by msgs, num */
static rt_ssize_t rk3x_i2c_setup(struct rk3x_i2c *i2c, struct rt_i2c_msg *msgs,
        int num)
{
    rt_ssize_t res = 0;
    rt_uint32_t addr = (msgs[0].addr & 0x7f) << 1;

    /*
     * The I2C adapter can issue a small (len < 4) write packet before
     * reading. This speeds up SMBus-style register reads.
     * The MRXADDR/MRXRADDR hold the slave address and the slave register
     * address in this case.
     */

    if (num >= 2 && msgs[0].len < 4 &&
        !(msgs[0].flags & RT_I2C_RD) && (msgs[1].flags & RT_I2C_RD))
    {
        rt_uint32_t reg_addr = 0;

        LOG_D("Combined write/read from addr 0x%x", addr >> 1);

        /* Fill MRXRADDR with the register address(es) */
        for (int i = 0; i < msgs[0].len; ++i)
        {
            reg_addr |= msgs[0].buf[i] << (i * 8);
            reg_addr |= REG_MRXADDR_VALID(i);
        }

        /* msgs[0] is handled by hw. */
        i2c->msg = &msgs[1];
        i2c->mode = REG_CON_MOD_REGISTER_TX;

        i2c_writel(i2c, addr | REG_MRXADDR_VALID(0), REG_MRXADDR);
        i2c_writel(i2c, reg_addr, REG_MRXRADDR);

        res = 2;
    }
    else
    {
        /* We'll have to do it the boring way and process the msgs one-by-one. */
        if (msgs[0].flags & RT_I2C_RD)
        {
            /* set read bit */
            addr |= 1;

            /*
             * We have to transmit the slave addr first. Use
             * MOD_REGISTER_TX for that purpose.
             */
            i2c->mode = REG_CON_MOD_REGISTER_TX;
            i2c_writel(i2c, addr | REG_MRXADDR_VALID(0), REG_MRXADDR);
            i2c_writel(i2c, 0, REG_MRXRADDR);
        }
        else
        {
            i2c->mode = REG_CON_MOD_TX;
        }

        i2c->msg = &msgs[0];

        res = 1;
    }

    i2c->addr = msgs[0].addr;
    i2c->state = STATE_START;
    i2c->processed = 0;
    i2c->error = RT_EOK;

    rk3x_i2c_clean_ipd(i2c);

    return res;
}

static rt_ssize_t rk3x_i2c_master_xfer(struct rt_i2c_bus_device *bus,
        struct rt_i2c_msg msgs[], rt_uint32_t num)
{
    rt_ssize_t res = 0;
    rt_uint32_t val;
    rt_ubase_t level;
    rt_err_t timeout_err;
    struct rk3x_i2c *i2c = raw_to_rk3x_i2c(bus);

    level = rt_spin_lock_irqsave(&i2c->lock);

    rt_clk_enable(i2c->clk);
    rt_clk_enable(i2c->pclk);

    i2c->is_last_msg = RT_FALSE;

    /* Process msgs */
    for (int i = 0; i < num; i += res)
    {
        res = rk3x_i2c_setup(i2c, msgs + i, num - i);

        if (res < 0)
        {
            LOG_E("%s setup failed", rt_dm_dev_get_name(&i2c->parent.parent));

            break;
        }

        if (i + res >= num)
        {
            i2c->is_last_msg = RT_TRUE;
        }

        rt_spin_unlock_irqrestore(&i2c->lock, level);

        rk3x_i2c_start(i2c);

        timeout_err = rt_completion_wait(&i2c->done, rt_tick_from_millisecond(WAIT_TIMEOUT));

        level = rt_spin_lock_irqsave(&i2c->lock);

        if (timeout_err)
        {
            LOG_E("timeout, ipd: 0x%02x, state: %d", i2c_readl(i2c, REG_IPD), i2c->state);

            /* Force a STOP condition without interrupt */
            i2c_writel(i2c, 0, REG_IEN);
            val = i2c_readl(i2c, REG_CON) & REG_CON_TUNING_MASK;
            val |= REG_CON_EN | REG_CON_STOP;
            i2c_writel(i2c, val, REG_CON);

            i2c->state = STATE_IDLE;

            res = timeout_err;
            break;
        }

        if (i2c->error)
        {
            res = i2c->error;

            break;
        }
    }

    rt_clk_disable(i2c->pclk);
    rt_clk_disable(i2c->clk);

    rt_spin_unlock_irqrestore(&i2c->lock, level);

    return res < 0 ? res : num;
}

const static struct rt_i2c_bus_device_ops rk3x_i2c_ops =
{
    .master_xfer = rk3x_i2c_master_xfer,
};

static void rk3x_i2c_isr(int irqno, void *param)
{
    rt_uint32_t ipd;
    struct rk3x_i2c *i2c = param;

    rt_spin_lock(&i2c->lock);

    ipd = i2c_readl(i2c, REG_IPD);

    if (i2c->state == STATE_IDLE)
    {
        LOG_W("IRQ in STATE_IDLE, ipd = 0x%x", ipd);
        rk3x_i2c_clean_ipd(i2c);

        goto _out;
    }

    LOG_D("IRQ: state %d, ipd: %x", i2c->state, ipd);

    /* Clean interrupt bits we don't care about */
    ipd &= ~(REG_INT_BRF | REG_INT_BTF);

    if (ipd & REG_INT_NAKRCV)
    {
        /*
         * We got a NACK in the last operation. Depending on whether
         * IGNORE_NAK is set, we have to stop the operation and report
         * an error.
         */
        i2c_writel(i2c, REG_INT_NAKRCV, REG_IPD);

        ipd &= ~REG_INT_NAKRCV;

        if (!(i2c->msg->flags & RT_I2C_IGNORE_NACK))
        {
            LOG_E("Flags error");

            rk3x_i2c_stop(i2c, -RT_EIO);
        }
    }

    /* is there anything left to handle? */
    if ((ipd & REG_INT_ALL) == 0)
    {
        goto _out;
    }

    switch (i2c->state)
    {
    case STATE_START:
        rk3x_i2c_handle_start(i2c, ipd);
        break;

    case STATE_WRITE:
        rk3x_i2c_handle_write(i2c, ipd);
        break;

    case STATE_READ:
        rk3x_i2c_handle_read(i2c, ipd);
        break;

    case STATE_STOP:
        rk3x_i2c_handle_stop(i2c, ipd);
        break;

    case STATE_IDLE:
        break;
    }

_out:
    rt_spin_unlock(&i2c->lock);
}

static void rk3x_i2c_free(struct rk3x_i2c *i2c)
{
    if (i2c->regs)
    {
        rt_iounmap(i2c->regs);
    }

    if (!rt_is_err_or_null(i2c->clk))
    {
        rt_clk_unprepare(i2c->clk);
        rt_clk_put(i2c->clk);
    }

    if (!rt_is_err_or_null(i2c->pclk))
    {
        if (!rt_is_err_or_null(i2c->clk) && i2c->pclk != i2c->clk)
        {
            rt_clk_unprepare(i2c->pclk);
            rt_clk_put(i2c->pclk);
        }
    }

    if (i2c->clk_notifier.callback)
    {
        rt_clk_notifier_unregister(i2c->clk, &i2c->clk_notifier);
    }

    rt_free(i2c);
}

static rt_err_t rk3x_i2c_probe(struct rt_platform_device *pdev)
{
    int id = -1;
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct rk3x_i2c *i2c = rt_calloc(1, sizeof(*i2c));

    if (!i2c)
    {
        return -RT_ENOMEM;
    }

    i2c->soc_data = pdev->id->data;
    i2c_timings_ofw_parse(dev->ofw_node, &i2c->timings, RT_TRUE);

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

    if (i2c->soc_data->grf_offset >= 0)
    {
        rt_uint32_t value;
        struct rt_syscon *grf;
        struct rt_ofw_node *np = dev->ofw_node;

        id = pdev->dev_id;

        if (id < 0)
        {
            err = -RT_EINVAL;
            LOG_E("alias id not found");

            goto _fail;
        }

        grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,grf");

        if (!grf)
        {
            err = -RT_EIO;
            LOG_E("I2C%d %s not found", id, "rockchip,grf");

            goto _fail;
        }

        /* 27+i: write mask, 11+i: value */
        value = RT_BIT(27 + id) | RT_BIT(11 + id);

        if ((err = rt_syscon_write(grf, i2c->soc_data->grf_offset, value)))
        {
            LOG_E("Could not write to GRF: %s", rt_strerror(err));

            goto _fail;
        }
    }

    if (i2c->soc_data->calc_timings == rk3x_i2c_v0_calc_timings)
    {
        i2c->clk = rt_clk_get_by_index(dev, 0);
        i2c->pclk = i2c->clk;
    }
    else
    {
        i2c->clk = rt_clk_get_by_name(dev, "i2c");
        i2c->pclk = rt_clk_get_by_name(dev, "pclk");
    }

    if (rt_is_err(i2c->clk))
    {
        err = rt_ptr_err(i2c->clk);

        goto _fail;
    }

    if ((err = rt_clk_prepare(i2c->clk)))
    {
        goto _fail;
    }

    if (rt_is_err(i2c->pclk))
    {
        err = rt_ptr_err(i2c->pclk);

        goto _fail;
    }

    if ((err = rt_clk_prepare(i2c->pclk)))
    {
        goto _fail;
    }

    i2c->clk_notifier.callback = rk3x_i2c_clk_notifier;
    if ((err = rt_clk_notifier_register(i2c->clk, &i2c->clk_notifier)))
    {
        goto _fail;
    }

    if ((err = rt_clk_enable(i2c->clk)))
    {
        LOG_E("Can't enable bus clk: %s", rt_strerror(err));

        goto _fail;
    }

    rk3x_i2c_adapt_div(i2c, rt_clk_get_rate(i2c->clk));
    rt_clk_disable(i2c->clk);

    rt_spin_lock_init(&i2c->lock);
    rt_completion_init(&i2c->done);

    if (id >= 0)
    {
        rt_dm_dev_set_name(&i2c->parent.parent, "i2c%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&i2c->parent.parent, "i2c");
    }
    dev_name = rt_dm_dev_get_name(&i2c->parent.parent);

    rt_hw_interrupt_install(i2c->irq, rk3x_i2c_isr, i2c, dev_name);
    rt_hw_interrupt_umask(i2c->irq);

    dev->user_data = i2c;

    i2c->parent.ops = &rk3x_i2c_ops;
    i2c->parent.parent.ofw_node = dev->ofw_node;

    rt_dm_dev_bind_fwdata(dev, RT_NULL, i2c);

    if ((err = rt_i2c_bus_device_register(&i2c->parent, dev_name)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_hw_interrupt_mask(i2c->irq);
    rt_pic_detach_irq(i2c->irq, i2c);

_fail:
    rk3x_i2c_free(i2c);

    return err;
}

static rt_err_t rk3x_i2c_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rk3x_i2c *i2c = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_hw_interrupt_mask(i2c->irq);
    rt_pic_detach_irq(i2c->irq, i2c);

    rt_device_unregister(&i2c->parent.parent);

    rk3x_i2c_free(i2c);

    return RT_EOK;
}

static const struct rk3x_i2c_soc_data rv1108_soc_data =
{
    .grf_offset = -1,
    .calc_timings = rk3x_i2c_v1_calc_timings,
};

static const struct rk3x_i2c_soc_data rv1126_soc_data =
{
    .grf_offset = 0x118,
    .calc_timings = rk3x_i2c_v1_calc_timings,
};

static const struct rk3x_i2c_soc_data rk3066_soc_data =
{
    .grf_offset = 0x154,
    .calc_timings = rk3x_i2c_v0_calc_timings,
};

static const struct rk3x_i2c_soc_data rk3188_soc_data =
{
    .grf_offset = 0x0a4,
    .calc_timings = rk3x_i2c_v0_calc_timings,
};

static const struct rk3x_i2c_soc_data rk3228_soc_data =
{
    .grf_offset = -1,
    .calc_timings = rk3x_i2c_v0_calc_timings,
};

static const struct rk3x_i2c_soc_data rk3288_soc_data =
{
    .grf_offset = -1,
    .calc_timings = rk3x_i2c_v0_calc_timings,
};

static const struct rk3x_i2c_soc_data rk3399_soc_data =
{
    .grf_offset = -1,
    .calc_timings = rk3x_i2c_v1_calc_timings,
};

static const struct rt_ofw_node_id rk3x_i2c_ofw_ids[] =
{
    { .compatible = "rockchip,rv1108-i2c", .data = &rv1108_soc_data },
    { .compatible = "rockchip,rv1126-i2c", .data = &rv1126_soc_data },
    { .compatible = "rockchip,rk3066-i2c", .data = &rk3066_soc_data },
    { .compatible = "rockchip,rk3188-i2c", .data = &rk3188_soc_data },
    { .compatible = "rockchip,rk3228-i2c", .data = &rk3228_soc_data },
    { .compatible = "rockchip,rk3288-i2c", .data = &rk3288_soc_data },
    { .compatible = "rockchip,rk3399-i2c", .data = &rk3399_soc_data },
    { /* sentinel */ }
};

static struct rt_platform_driver rk3x_i2c_driver =
{
    .name = "rk3x-i2c",
    .ids = rk3x_i2c_ofw_ids,

    .probe = rk3x_i2c_probe,
    .remove = rk3x_i2c_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rk3x_i2c_driver);
