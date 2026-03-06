/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-11     liYony       the first version
 * 2024-07-07     GuEe-GUI     port to the DM
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>
#include <drivers/misc.h>
#include <drivers/serial_dm.h>

/* Register offsets for the UART. */
#define CDNS_UART_CR                0x00  /* Control Register */
#define CDNS_UART_MR                0x04  /* Mode Register */
#define CDNS_UART_IER               0x08  /* Interrupt Enable */
#define CDNS_UART_IDR               0x0c  /* Interrupt Disable */
#define CDNS_UART_IMR               0x10  /* Interrupt Mask */
#define CDNS_UART_ISR               0x14  /* Interrupt Status */
#define CDNS_UART_BAUDGEN           0x18  /* Baud Rate Generator */
#define CDNS_UART_RXTOUT            0x1c  /* RX Timeout */
#define CDNS_UART_RXWM              0x20  /* RX FIFO Trigger Level */
#define CDNS_UART_MODEMCR           0x24  /* Modem Control */
#define CDNS_UART_MODEMSR           0x28  /* Modem Status */
#define CDNS_UART_SR                0x2c  /* Channel Status */
#define CDNS_UART_FIFO              0x30  /* FIFO */
#define CDNS_UART_BAUDDIV           0x34  /* Baud Rate Divider */
#define CDNS_UART_FLOWDEL           0x38  /* Flow Delay */
#define CDNS_UART_IRRX_PWIDTH       0x3c  /* IR Min Received Pulse Width */
#define CDNS_UART_IRTX_PWIDTH       0x40  /* IR Transmitted pulse Width */
#define CDNS_UART_TXWM              0x44  /* TX FIFO Trigger Level */
#define CDNS_UART_RXBS              0x48  /* RX FIFO byte status register */

/* Control Register Bit Definitions */
#define CDNS_UART_CR_STOPBRK        0x00000100  /* Stop TX break */
#define CDNS_UART_CR_STARTBRK       0x00000080  /* Set TX break */
#define CDNS_UART_CR_TX_DIS         0x00000020  /* TX disabled. */
#define CDNS_UART_CR_TX_EN          0x00000010  /* TX enabled */
#define CDNS_UART_CR_RX_DIS         0x00000008  /* RX disabled. */
#define CDNS_UART_CR_RX_EN          0x00000004  /* RX enabled */
#define CDNS_UART_CR_TXRST          0x00000002  /* TX logic reset */
#define CDNS_UART_CR_RXRST          0x00000001  /* RX logic reset */
#define CDNS_UART_CR_RST_TO         0x00000040  /* Restart Timeout Counter */
#define CDNS_UART_RXBS_PARITY       0x00000001 /* Parity error status */
#define CDNS_UART_RXBS_FRAMING      0x00000002 /* Framing error status */
#define CDNS_UART_RXBS_BRK          0x00000004 /* Overrun error status */

/*
 * Mode Register:
 * The mode register (MR) defines the mode of transfer as well as the data
 * format. If this register is modified during transmission or reception,
 * data validity cannot be guaranteed.
 */
#define CDNS_UART_MR_CLKSEL         0x00000001  /* Pre-scalar selection */
#define CDNS_UART_MR_CHMODE_L_LOOP  0x00000200  /* Local loop back mode */
#define CDNS_UART_MR_CHMODE_NORM    0x00000000  /* Normal mode */
#define CDNS_UART_MR_CHMODE_MASK    0x00000300  /* Mask for mode bits */

#define CDNS_UART_MR_STOPMODE_2_BIT 0x00000080  /* 2 stop bits */
#define CDNS_UART_MR_STOPMODE_1_BIT 0x00000000  /* 1 stop bit */

#define CDNS_UART_MR_PARITY_NONE    0x00000020  /* No parity mode */
#define CDNS_UART_MR_PARITY_MARK    0x00000018  /* Mark parity mode */
#define CDNS_UART_MR_PARITY_SPACE   0x00000010  /* Space parity mode */
#define CDNS_UART_MR_PARITY_ODD     0x00000008  /* Odd parity mode */
#define CDNS_UART_MR_PARITY_EVEN    0x00000000  /* Even parity mode */

#define CDNS_UART_MR_CHARLEN_6_BIT  0x00000006  /* 6 bits data */
#define CDNS_UART_MR_CHARLEN_7_BIT  0x00000004  /* 7 bits data */
#define CDNS_UART_MR_CHARLEN_8_BIT  0x00000000  /* 8 bits data */

/*
 * Interrupt Registers:
 * Interrupt control logic uses the interrupt enable register (IER) and the
 * interrupt disable register (IDR) to set the value of the bits in the
 * interrupt mask register (IMR). The IMR determines whether to pass an
 * interrupt to the interrupt status register (ISR).
 * Writing a 1 to IER Enables an interrupt, writing a 1 to IDR disables an
 * interrupt. IMR and ISR are read only, and IER and IDR are write only.
 * Reading either IER or IDR returns 0x00.
 * All four registers have the same bit definitions.
 */
#define CDNS_UART_IXR_TOUT          0x00000100 /* RX Timeout error interrupt */
#define CDNS_UART_IXR_PARITY        0x00000080 /* Parity error interrupt */
#define CDNS_UART_IXR_FRAMING       0x00000040 /* Framing error interrupt */
#define CDNS_UART_IXR_OVERRUN       0x00000020 /* Overrun error interrupt */
#define CDNS_UART_IXR_TXFULL        0x00000010 /* TX FIFO Full interrupt */
#define CDNS_UART_IXR_TXEMPTY       0x00000008 /* TX FIFO empty interrupt */
#define CDNS_UART_ISR_RXEMPTY       0x00000002 /* RX FIFO empty interrupt */
#define CDNS_UART_IXR_RXTRIG        0x00000001 /* RX FIFO trigger interrupt */
#define CDNS_UART_IXR_RXFULL        0x00000004 /* RX FIFO full interrupt. */
#define CDNS_UART_IXR_RXEMPTY       0x00000002 /* RX FIFO empty interrupt. */
#define CDNS_UART_IXR_RXMASK        0x000021e7 /* Valid RX bit mask */

/*
 * Do not enable parity error interrupt for the following
 * reason: When parity error interrupt is enabled, each Rx
 * parity error always results in 2 events. The first one
 * being parity error interrupt and the second one with a
 * proper Rx interrupt with the incoming data.  Disabling
 * parity error interrupt ensures better handling of parity
 * error events. With this change, for a parity error case, we
 * get a Rx interrupt with parity error set in ISR register
 * and we still handle parity errors in the desired way.
 */

#define CDNS_UART_RX_IRQS           (CDNS_UART_IXR_FRAMING | CDNS_UART_IXR_OVERRUN | CDNS_UART_IXR_RXTRIG | CDNS_UART_IXR_TOUT)

/* Goes in read_status_mask for break detection as the HW doesn't do it*/
#define CDNS_UART_IXR_BRK           0x00002000
#define CDNS_UART_RXWM_MASK         0x0000003f /* Valid bits mask */

/*
 * Modem Control register:
 * The read/write Modem Control register controls the interface with the modem
 * or data set, or a peripheral device emulating a modem.
 */
#define CDNS_UART_MODEMCR_FCM       0x00000020 /* Automatic flow control mode */
#define CDNS_UART_MODEMCR_RTS       0x00000002 /* Request to send output control */
#define CDNS_UART_MODEMCR_DTR       0x00000001 /* Data Terminal Ready */

/*
 * Modem Status register:
 * The read/write Modem Status register reports the interface with the modem
 * or data set, or a peripheral device emulating a modem.
 */
#define CDNS_UART_MODEMSR_DCD       RT_BIT(7) /* Data Carrier Detect */
#define CDNS_UART_MODEMSR_RI        RT_BIT(6) /* Ting Indicator */
#define CDNS_UART_MODEMSR_DSR       RT_BIT(5) /* Data Set Ready */
#define CDNS_UART_MODEMSR_CTS       RT_BIT(4) /* Clear To Send */

/*
 * Channel Status Register:
 * The channel status register (CSR) is provided to enable the control logic
 * to monitor the status of bits in the channel interrupt status register,
 * even if these are masked out by the interrupt mask register.
 */
#define CDNS_UART_SR_RXEMPTY        0x00000002 /* RX FIFO empty */
#define CDNS_UART_SR_TXEMPTY        0x00000008 /* TX FIFO empty */
#define CDNS_UART_SR_TXFULL         0x00000010 /* TX FIFO full */
#define CDNS_UART_SR_RXTRIG         0x00000001 /* Rx Trigger */
#define CDNS_UART_SR_TACTIVE        0x00000800 /* TX state machine active */

/* baud dividers min/max values */
#define CDNS_UART_BDIV_MIN          4
#define CDNS_UART_BDIV_MAX          255
#define CDNS_UART_CD_MAX            65535

struct cdns_uart_soc_data
{
    rt_uint32_t quirks;
};

struct cdns_uart
{
    struct rt_serial_device parent;

    int irq;
    void *base;
    rt_ubase_t freq;
    struct rt_clk *clk;
    struct rt_clk *pclk;
    struct rt_reset_control *rstc;

    struct rt_clk_notifier clk_rate_notifier;
    struct rt_spinlock spinlock;
};

#define raw_to_cdns_uart(raw) rt_container_of(raw, struct cdns_uart, parent)

static rt_uint32_t cdns_uart_calc_baud_divs(rt_ubase_t freq, rt_uint32_t baud_rate,
        rt_uint32_t *rbdiv, rt_uint32_t *rcd, rt_int32_t *div8)
{
    rt_uint32_t cd, bdiv, calc_baud, bestbaud = 0, bauderror, besterror = ~0;

    if (baud_rate < freq / ((CDNS_UART_BDIV_MAX + 1) * CDNS_UART_CD_MAX))
    {
        *div8 = 1;
        freq /= 8;
    }
    else
    {
        *div8 = 0;
    }

    for (bdiv = CDNS_UART_BDIV_MIN; bdiv <= CDNS_UART_BDIV_MAX; ++bdiv)
    {
        cd = RT_DIV_ROUND_CLOSEST(freq, baud_rate * (bdiv + 1));

        if (cd < 1 || cd > CDNS_UART_CD_MAX)
        {
            continue;
        }

        calc_baud = freq / (cd * (bdiv + 1));

        if (baud_rate > calc_baud)
        {
            bauderror = baud_rate - calc_baud;
        }
        else
        {
            bauderror = calc_baud - baud_rate;
        }

        if (besterror > bauderror)
        {
            *rbdiv = bdiv;
            *rcd = cd;
            bestbaud = calc_baud;
            besterror = bauderror;
        }
    }

    if (((besterror * 100) / baud_rate) < 3)
    {
        bestbaud = baud_rate;
    }

    return bestbaud;
}

static rt_uint32_t cdns_uart_set_baud_rate(struct cdns_uart *cdns_uart,
        struct serial_configure *cfg)
{
    rt_int32_t div8;
    rt_uint32_t cd = 0, bdiv = 0, mreg, calc_baud;

    calc_baud = cdns_uart_calc_baud_divs(cdns_uart->freq, cfg->baud_rate, &bdiv, &cd, &div8);
    mreg = HWREG32(cdns_uart->base + CDNS_UART_MR);

    if (div8)
    {
        mreg |= CDNS_UART_MR_CLKSEL;
    }
    else
    {
        mreg &= ~CDNS_UART_MR_CLKSEL;
    }

    HWREG32(cdns_uart->base + CDNS_UART_MR) = mreg;
    HWREG32(cdns_uart->base + CDNS_UART_BAUDGEN) = cd;
    HWREG32(cdns_uart->base + CDNS_UART_BAUDDIV) = bdiv;

    return calc_baud;
}

static rt_err_t cdns_uart_uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    rt_err_t err = RT_EOK;
    rt_ubase_t level;
    rt_uint32_t ctrl_reg, mode_reg, minbaud, maxbaud;
    struct cdns_uart *cdns_uart = raw_to_cdns_uart(serial);

    level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

    /* Disable the TX and RX to set baud rate */
    ctrl_reg = HWREG32(cdns_uart->base + CDNS_UART_CR);
    ctrl_reg |= CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS;
    HWREG32(cdns_uart->base + CDNS_UART_CR) = ctrl_reg;

    minbaud = cdns_uart->freq / ((CDNS_UART_BDIV_MAX + 1) * CDNS_UART_CD_MAX * 8);
    maxbaud = cdns_uart->freq / (CDNS_UART_BDIV_MIN + 1);

    if (cfg->baud_rate < minbaud || cfg->baud_rate > maxbaud)
    {
        err = -RT_ENOSYS;
        goto _out_lock;
    }

    cdns_uart_set_baud_rate(cdns_uart, cfg);

    /* Set TX/RX Reset */
    ctrl_reg = HWREG32(cdns_uart->base + CDNS_UART_CR);
    ctrl_reg |= CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST;
    HWREG32(cdns_uart->base + CDNS_UART_CR) = ctrl_reg;

    while (HWREG32(cdns_uart->base + CDNS_UART_CR) & (CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
    {
        rt_hw_cpu_relax();
    }

    /*
     * Clear the RX disable and TX disable bits and then set the TX enable
     * bit and RX enable bit to enable the transmitter and receiver.
     */
    ctrl_reg = HWREG32(cdns_uart->base + CDNS_UART_CR);
    ctrl_reg &= ~(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS);
    ctrl_reg |= CDNS_UART_CR_TX_EN | CDNS_UART_CR_RX_EN;
    HWREG32(cdns_uart->base + CDNS_UART_CR) = ctrl_reg;

    HWREG32(cdns_uart->base + CDNS_UART_RXTOUT) = 10;

    mode_reg = HWREG32(cdns_uart->base + CDNS_UART_MR);

    switch (cfg->data_bits)
    {
    case DATA_BITS_6:
        mode_reg |= CDNS_UART_MR_CHARLEN_6_BIT;
        break;

    case DATA_BITS_7:
        mode_reg |= CDNS_UART_MR_CHARLEN_7_BIT;
        break;

    case DATA_BITS_8:
    default:
        mode_reg |= CDNS_UART_MR_CHARLEN_8_BIT;
        break;
    }

    switch (cfg->stop_bits)
    {
    case STOP_BITS_2:
        mode_reg |= CDNS_UART_MR_STOPMODE_2_BIT;
        break;

    case STOP_BITS_1:
    default:
        mode_reg |= CDNS_UART_MR_STOPMODE_1_BIT;
        break;
    }

    switch (cfg->parity)
    {
    case PARITY_ODD:
        mode_reg |= CDNS_UART_MR_PARITY_ODD;
        break;

    case PARITY_EVEN:
        mode_reg |= CDNS_UART_MR_PARITY_EVEN;
        break;

    case PARITY_NONE:
    default:
        mode_reg |= CDNS_UART_MR_PARITY_NONE;
        break;
    }

    /* Write the mode register out */
    HWREG32(cdns_uart->base + CDNS_UART_MR) = mode_reg & 1;

_out_lock:
    rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);

    return err;
}

static rt_err_t cdns_uart_uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    rt_uint32_t value;
    rt_ubase_t level;
    struct cdns_uart *cdns_uart = raw_to_cdns_uart(serial);

    level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        rt_hw_interrupt_mask(cdns_uart->irq);

        HWREG32(cdns_uart->base + CDNS_UART_IER) = 0;
        HWREG32(cdns_uart->base + CDNS_UART_IDR) = ~0U;
        break;

    case RT_DEVICE_CTRL_SET_INT:
        /*
         * Write the new value for the FIFO control register to it such that the
         * threshold is changed
         */

        value = 1; /* Trigger level */
        HWREG32(cdns_uart->base + CDNS_UART_RXWM) = value & CDNS_UART_RXWM_MASK;

        rt_hw_interrupt_umask(cdns_uart->irq);

        value = CDNS_UART_IXR_RXTRIG & CDNS_UART_IXR_RXMASK;
        HWREG32(cdns_uart->base + CDNS_UART_IER) = value;
        HWREG32(cdns_uart->base + CDNS_UART_IDR) = ~value;
        break;
    }

    rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);

    return RT_EOK;
}

static int cdns_uart_uart_putc(struct rt_serial_device *serial, char c)
{
    rt_ubase_t level;
    struct cdns_uart *cdns_uart = raw_to_cdns_uart(serial);

    level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

    /* Wait until there is space in TX FIFO */
    while (!(HWREG32(cdns_uart->base + CDNS_UART_SR) & CDNS_UART_SR_TXEMPTY))
    {
        rt_hw_cpu_relax();
    }

    /* Write the byte into the TX FIFO */
    HWREG32(cdns_uart->base + CDNS_UART_FIFO) = c;

    /* Wait until FIFO is empty */
    while (!(HWREG32(cdns_uart->base + CDNS_UART_SR) & CDNS_UART_SR_TXEMPTY))
    {
        rt_hw_cpu_relax();
    }

    rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);

    return 1;
}

static int cdns_uart_uart_getc(struct rt_serial_device *serial)
{
    int ch = -1;
    rt_ubase_t level;
    struct cdns_uart *cdns_uart = raw_to_cdns_uart(serial);

    level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

    /* Check if FIFO is empty */
    if (!(HWREG32(cdns_uart->base + CDNS_UART_SR) & CDNS_UART_SR_RXEMPTY))
    {
        ch = HWREG32(cdns_uart->base + CDNS_UART_FIFO);
    }

    rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);

    return ch;
}

static const struct rt_uart_ops cdns_uart_uart_ops =
{
    .configure = cdns_uart_uart_configure,
    .control = cdns_uart_uart_control,
    .putc = cdns_uart_uart_putc,
    .getc = cdns_uart_uart_getc,
};

static void cdns_uart_early_kick(struct rt_fdt_earlycon *con, int why)
{
    struct cdns_uart *cdns_uart = raw_to_cdns_uart(con->data);

    switch (why)
    {
    case FDT_EARLYCON_KICK_UPDATE:
        cdns_uart->base = rt_ioremap((void *)con->mmio, con->size);
        break;

    case FDT_EARLYCON_KICK_COMPLETED:
        rt_iounmap(cdns_uart->base);
        break;

    default:
        break;
    }
}

static rt_err_t cdns_uart_early_setup(struct rt_fdt_earlycon *con, const char *options)
{
    rt_uint32_t freq = 0;
    static struct cdns_uart cdns_uart = { };

    if (!con->mmio)
    {
        return -RT_ERROR;
    }

    cdns_uart.base = rt_ioremap_early((void *)con->mmio, con->size);

    HWREG32(cdns_uart.base + CDNS_UART_CR) = CDNS_UART_CR_TX_EN |
            CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST;

    con->console_putc = (typeof(con->console_putc))&cdns_uart_uart_putc;
    con->console_kick = cdns_uart_early_kick;
    con->data = &cdns_uart.parent;
    cdns_uart.parent.config = options ? serial_cfg_from_args((char *)options) :
            (typeof(cdns_uart.parent.config))RT_SERIAL_CONFIG_DEFAULT;

    fdt_getprop_u32(con->fdt, con->nodeoffset, "clock-frequency", &freq, RT_NULL);

    if ((cdns_uart.freq = freq))
    {
        rt_int32_t div8;
        rt_uint32_t cd = 0, bdiv = 0, mr = CDNS_UART_MR_PARITY_NONE;

        cdns_uart_calc_baud_divs(cdns_uart.freq,
                cdns_uart.parent.config.baud_rate, &bdiv, &cd, &div8);

        if (div8)
        {
            mr |= CDNS_UART_MR_CLKSEL;
        }

        HWREG32(cdns_uart.base + CDNS_UART_MR) = mr;
        HWREG32(cdns_uart.base + CDNS_UART_BAUDGEN) = cd;
        HWREG32(cdns_uart.base + CDNS_UART_BAUDDIV) = bdiv;
    }

    return RT_EOK;
}
RT_FDT_EARLYCON_EXPORT(xlnx_xuartps, "cdns_uart", "xlnx,xuartps", cdns_uart_early_setup);
RT_FDT_EARLYCON_EXPORT(cdns_uart_r1p8, "cdns_uart", "cdns,uart-r1p8", cdns_uart_early_setup);
RT_FDT_EARLYCON_EXPORT(cdns_uart_r1p12, "cdns_uart", "cdns,uart-r1p12", cdns_uart_early_setup);
RT_FDT_EARLYCON_EXPORT(xlnx_zynqmp_uart, "cdns_uart", "xlnx,zynqmp-uart", cdns_uart_early_setup);

static void cdns_uart_isr(int irqno, void *param)
{
    rt_uint32_t isr;
    rt_base_t level;
    rt_bool_t event = RT_FALSE;
    struct cdns_uart *cdns_uart = param;

    level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

    isr = HWREG32(cdns_uart->base + CDNS_UART_ISR);
    HWREG32(cdns_uart->base + CDNS_UART_ISR) = isr;

    if ((isr & CDNS_UART_IXR_RXMASK) &&
        !(HWREG32(cdns_uart->base + CDNS_UART_CR) & CDNS_UART_CR_RX_DIS))
    {
        event = RT_TRUE;
    }

    rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);

    if (event)
    {
        rt_hw_serial_isr(&cdns_uart->parent, RT_SERIAL_EVENT_RX_IND);
    }
}

static rt_err_t cdns_uart_clk_notify(struct rt_clk_notifier *notifier,
        rt_ubase_t msg, rt_ubase_t old_rate, rt_ubase_t new_rate)
{
    rt_ubase_t level;
    rt_int32_t div8;
    rt_uint32_t ctrl_reg, cd = 0, bdiv = 0;
    struct cdns_uart *cdns_uart;

    cdns_uart = rt_container_of(notifier, struct cdns_uart, clk_rate_notifier);

    switch (msg)
    {
    case RT_CLK_MSG_PRE_RATE_CHANGE:
        if (!cdns_uart_calc_baud_divs(new_rate, cdns_uart->parent.config.baud_rate, &bdiv, &cd, &div8))
        {
            return -RT_EIO;
        }

        level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

        /* Disable the TX and RX to set baud rate */
        ctrl_reg = HWREG32(cdns_uart->base + CDNS_UART_CR);
        ctrl_reg |= CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS;
        HWREG32(cdns_uart->base + CDNS_UART_CR) = ctrl_reg;

        rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);
        break;

    case RT_CLK_MSG_POST_RATE_CHANGE:
        level = rt_spin_lock_irqsave(&cdns_uart->spinlock);

        cdns_uart->freq = new_rate;
        cdns_uart_set_baud_rate(cdns_uart, &cdns_uart->parent.config);

        /* Fallthrough */
    case RT_CLK_MSG_ABORT_RATE_CHANGE:
        if (msg == RT_CLK_MSG_ABORT_RATE_CHANGE)
        {
            level = rt_spin_lock_irqsave(&cdns_uart->spinlock);
        }

        /* Set TX/RX Reset */
        ctrl_reg = HWREG32(cdns_uart->base + CDNS_UART_CR);
        ctrl_reg |= CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST;
        HWREG32(cdns_uart->base + CDNS_UART_CR) = ctrl_reg;

        while (HWREG32(cdns_uart->base + CDNS_UART_CR) & (CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
        {
            rt_hw_cpu_relax();
        }

        /*
         * Clear the RX disable and TX disable bits and then set the TX
         * enable bit and RX enable bit to enable the transmitter and receiver.
         */
        HWREG32(cdns_uart->base + CDNS_UART_RXTOUT) = 10;
        ctrl_reg = HWREG32(cdns_uart->base + CDNS_UART_CR);
        ctrl_reg &= ~(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS);
        ctrl_reg |= CDNS_UART_CR_TX_EN | CDNS_UART_CR_RX_EN;
        HWREG32(cdns_uart->base + CDNS_UART_CR) = ctrl_reg;

        rt_spin_unlock_irqrestore(&cdns_uart->spinlock, level);
        break;

    default:
        break;
    }

    return RT_EOK;
}

static void cdns_uart_free(struct cdns_uart *cdns_uart)
{
    if (cdns_uart->base)
    {
        rt_iounmap(cdns_uart->base);
    }

    if (cdns_uart->clk_rate_notifier.callback)
    {
        rt_clk_notifier_unregister(cdns_uart->clk, &cdns_uart->clk_rate_notifier);
    }

    if (!rt_is_err_or_null(cdns_uart->clk))
    {
        rt_clk_disable(cdns_uart->clk);
        rt_clk_put(cdns_uart->clk);
    }

    if (!rt_is_err_or_null(cdns_uart->pclk))
    {
        rt_clk_disable_unprepare(cdns_uart->pclk);
        rt_clk_put(cdns_uart->pclk);
    }

    if (!rt_is_err_or_null(cdns_uart->rstc))
    {
        rt_reset_control_put(cdns_uart->rstc);
    }

    rt_free(cdns_uart);
}

static rt_err_t cdns_uart_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *name;
    char isr_name[RT_NAME_MAX];
    struct rt_device *dev = &pdev->parent;
    struct cdns_uart *cdns_uart = rt_calloc(1, sizeof(*cdns_uart));
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (!cdns_uart)
    {
        return -RT_ENOMEM;
    }

    cdns_uart->base = rt_dm_dev_iomap(dev, 0);

    if (!cdns_uart->base)
    {
        err = -RT_EIO;

        goto _fail;
    }

    cdns_uart->irq = rt_dm_dev_get_irq(dev, 0);

    if (cdns_uart->irq < 0)
    {
        err = cdns_uart->irq;

        goto _fail;
    }

    cdns_uart->clk = rt_clk_get_by_name(dev, "uart_clk");

    if (rt_is_err(cdns_uart->clk))
    {
        err = rt_ptr_err(cdns_uart->clk);

        goto _fail;
    }

    if (!cdns_uart->clk)
    {
        cdns_uart->clk = rt_clk_get_by_name(dev, "ref_clk");

        if (rt_is_err(cdns_uart->clk))
        {
            err = rt_ptr_err(cdns_uart->clk);

            goto _fail;
        }
    }

    cdns_uart->pclk = rt_clk_get_by_name(dev, "pclk");

    if (rt_is_err(cdns_uart->pclk))
    {
        err = rt_ptr_err(cdns_uart->pclk);

        goto _fail;
    }

    if (!cdns_uart->pclk)
    {
        cdns_uart->pclk = rt_clk_get_by_name(dev, "aper_clk");

        if (rt_is_err(cdns_uart->clk))
        {
            err = rt_ptr_err(cdns_uart->clk);

            goto _fail;
        }
    }

    if ((err = rt_clk_prepare_enable(cdns_uart->pclk)))
    {
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(cdns_uart->clk)))
    {
        goto _fail;
    }

    cdns_uart->rstc = rt_reset_control_get_by_index(dev, 0);

    if (rt_is_err(cdns_uart->rstc))
    {
        err = rt_ptr_err(cdns_uart->rstc);

        goto _fail;
    }

    if ((err = rt_reset_control_deassert(cdns_uart->rstc)))
    {
        goto _fail;
    }

    cdns_uart->clk_rate_notifier.callback = cdns_uart_clk_notify;
    if ((err = rt_clk_notifier_register(cdns_uart->clk, &cdns_uart->clk_rate_notifier)))
    {
        cdns_uart->clk_rate_notifier.callback = RT_NULL;
        goto _fail;
    }

    cdns_uart->freq = rt_clk_get_rate(cdns_uart->clk);

    rt_spin_lock_init(&cdns_uart->spinlock);

    rt_dm_dev_bind_fwdata(&cdns_uart->parent.parent, dev->ofw_node, &cdns_uart->parent);
    dev->user_data = cdns_uart;

    serial_dev_set_name(&cdns_uart->parent);
    name = rt_dm_dev_get_name(&cdns_uart->parent.parent);

    cdns_uart->parent.ops = &cdns_uart_uart_ops;
    cdns_uart->parent.config = config;

    rt_hw_serial_register(&cdns_uart->parent, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX, cdns_uart);
    rt_snprintf(isr_name, RT_NAME_MAX, "%s-cdns_uart", name);
    rt_hw_interrupt_install(cdns_uart->irq, cdns_uart_isr, cdns_uart, isr_name);

    return RT_EOK;

_fail:
    cdns_uart_free(cdns_uart);

    return err;
}

static rt_err_t cdns_uart_remove(struct rt_platform_device *pdev)
{
    rt_uint32_t status;
    struct rt_device *dev = &pdev->parent;
    struct cdns_uart *cdns_uart = dev->user_data;

    /* Disable interrupts */
    status = HWREG32(cdns_uart->base + CDNS_UART_IMR);
    HWREG32(cdns_uart->base + CDNS_UART_IDR) = status;
    HWREG32(cdns_uart->base + CDNS_UART_ISR) = 0xffffffffU;

    /* Disable the TX and RX */
    HWREG32(cdns_uart->base + CDNS_UART_CR) = CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    rt_hw_interrupt_mask(cdns_uart->irq);
    rt_pic_detach_irq(cdns_uart->irq, cdns_uart);

    rt_device_unregister(&cdns_uart->parent.parent);

    rt_reset_control_assert(cdns_uart->rstc);

    cdns_uart_free(cdns_uart);

    return RT_EOK;
}

static const struct rt_ofw_node_id cdns_uart_ofw_ids[] =
{
    { .type = "ttyPS", .compatible = "xlnx,xuartps", },
    { .type = "ttyPS", .compatible = "cdns,uart-r1p8", },
    { .type = "ttyPS", .compatible = "cdns,uart-r1p12", },
    { .type = "ttyPS", .compatible = "xlnx,zynqmp-uart", },
    { /* sentinel */ }
};

static struct rt_platform_driver cdns_uart_driver =
{
    .name = "serial-cdns-uart",
    .ids = cdns_uart_ofw_ids,

    .probe = cdns_uart_probe,
    .remove = cdns_uart_remove,
};

static int cdns_uart_drv_register(void)
{
    rt_platform_driver_register(&cdns_uart_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(cdns_uart_drv_register);
