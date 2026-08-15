/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <rtthread.h>

#define DBG_TAG "serial.8250.bcm7271"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "8250.h"

/* Register definitions for UART DMA block. Version 1.1 or later. */
#define UDMA_ARB_RX                             0x00
#define UDMA_ARB_TX                             0x04
#define   UDMA_ARB_REQ                          0x00000001
#define   UDMA_ARB_GRANT                        0x00000002

#define UDMA_RX_REVISION                        0x00
#define UDMA_RX_REVISION_REQUIRED               0x00000101
#define UDMA_RX_CTRL                            0x04
#define   UDMA_RX_CTRL_BUF_CLOSE_MODE           0x00010000
#define   UDMA_RX_CTRL_MASK_WR_DONE             0x00008000
#define   UDMA_RX_CTRL_ENDIAN_OVERRIDE          0x00004000
#define   UDMA_RX_CTRL_ENDIAN                   0x00002000
#define   UDMA_RX_CTRL_OE_IS_ERR                0x00001000
#define   UDMA_RX_CTRL_PE_IS_ERR                0x00000800
#define   UDMA_RX_CTRL_FE_IS_ERR                0x00000400
#define   UDMA_RX_CTRL_NUM_BUF_USED_MASK        0x000003c0
#define   UDMA_RX_CTRL_NUM_BUF_USED_SHIFT       6
#define   UDMA_RX_CTRL_BUF_CLOSE_CLK_SEL_SYS    0x00000020
#define   UDMA_RX_CTRL_BUF_CLOSE_ENA            0x00000010
#define   UDMA_RX_CTRL_TIMEOUT_CLK_SEL_SYS      0x00000008
#define   UDMA_RX_CTRL_TIMEOUT_ENA              0x00000004
#define   UDMA_RX_CTRL_ABORT                    0x00000002
#define   UDMA_RX_CTRL_ENA                      0x00000001
#define UDMA_RX_STATUS                          0x08
#define   UDMA_RX_STATUS_ACTIVE_BUF_MASK        0x0000000f
#define UDMA_RX_TRANSFER_LEN                    0x0c
#define UDMA_RX_TRANSFER_TOTAL                  0x10
#define UDMA_RX_BUFFER_SIZE                     0x14
#define UDMA_RX_SRC_ADDR                        0x18
#define UDMA_RX_TIMEOUT                         0x1c
#define UDMA_RX_BUFFER_CLOSE                    0x20
#define UDMA_RX_BLOCKOUT_COUNTER                0x24
#define UDMA_RX_BUF0_PTR_LO                     0x28
#define UDMA_RX_BUF0_PTR_HI                     0x2c
#define UDMA_RX_BUF0_STATUS                     0x30
#define   UDMA_RX_BUFX_STATUS_OVERRUN_ERR       0x00000010
#define   UDMA_RX_BUFX_STATUS_FRAME_ERR         0x00000008
#define   UDMA_RX_BUFX_STATUS_PARITY_ERR        0x00000004
#define   UDMA_RX_BUFX_STATUS_CLOSE_EXPIRED     0x00000002
#define   UDMA_RX_BUFX_STATUS_DATA_RDY          0x00000001
#define UDMA_RX_BUF0_DATA_LEN                   0x34
#define UDMA_RX_BUF1_PTR_LO                     0x38
#define UDMA_RX_BUF1_PTR_HI                     0x3c
#define UDMA_RX_BUF1_STATUS                     0x40
#define UDMA_RX_BUF1_DATA_LEN                   0x44

#define UDMA_TX_REVISION                        0x00
#define UDMA_TX_REVISION_REQUIRED               0x00000101
#define UDMA_TX_CTRL                            0x04
#define   UDMA_TX_CTRL_ENDIAN_OVERRIDE          0x00000080
#define   UDMA_TX_CTRL_ENDIAN                   0x00000040
#define   UDMA_TX_CTRL_NUM_BUF_USED_MASK        0x00000030
#define   UDMA_TX_CTRL_NUM_BUF_USED_1           0x00000010
#define   UDMA_TX_CTRL_ABORT                    0x00000002
#define   UDMA_TX_CTRL_ENA                      0x00000001
#define UDMA_TX_DST_ADDR                        0x08
#define UDMA_TX_BLOCKOUT_COUNTER                0x10
#define UDMA_TX_TRANSFER_LEN                    0x14
#define UDMA_TX_TRANSFER_TOTAL                  0x18
#define UDMA_TX_STATUS                          0x20
#define UDMA_TX_BUF0_PTR_LO                     0x24
#define UDMA_TX_BUF0_PTR_HI                     0x28
#define UDMA_TX_BUF0_STATUS                     0x2c
#define   UDMA_TX_BUFX_LAST                     0x00000002
#define   UDMA_TX_BUFX_EMPTY                    0x00000001
#define UDMA_TX_BUF0_DATA_LEN                   0x30
#define UDMA_TX_BUF0_DATA_SENT                  0x34
#define UDMA_TX_BUF1_PTR_LO                     0x38

#define UDMA_INTR_STATUS                        0x00
#define   UDMA_INTR_ARB_TX_GRANT                0x00040000
#define   UDMA_INTR_ARB_RX_GRANT                0x00020000
#define   UDMA_INTR_TX_ALL_EMPTY                0x00010000
#define   UDMA_INTR_TX_EMPTY_BUF1               0x00008000
#define   UDMA_INTR_TX_EMPTY_BUF0               0x00004000
#define   UDMA_INTR_TX_ABORT                    0x00002000
#define   UDMA_INTR_TX_DONE                     0x00001000
#define   UDMA_INTR_RX_ERROR                    0x00000800
#define   UDMA_INTR_RX_TIMEOUT                  0x00000400
#define   UDMA_INTR_RX_READY_BUF7               0x00000200
#define   UDMA_INTR_RX_READY_BUF6               0x00000100
#define   UDMA_INTR_RX_READY_BUF5               0x00000080
#define   UDMA_INTR_RX_READY_BUF4               0x00000040
#define   UDMA_INTR_RX_READY_BUF3               0x00000020
#define   UDMA_INTR_RX_READY_BUF2               0x00000010
#define   UDMA_INTR_RX_READY_BUF1               0x00000008
#define   UDMA_INTR_RX_READY_BUF0               0x00000004
#define   UDMA_INTR_RX_READY_MASK               0x000003fc
#define   UDMA_INTR_RX_READY_SHIFT              2
#define   UDMA_INTR_RX_ABORT                    0x00000002
#define   UDMA_INTR_RX_DONE                     0x00000001
#define UDMA_INTR_SET                           0x04
#define UDMA_INTR_CLEAR                         0x08
#define UDMA_INTR_MASK_STATUS                   0x0c
#define UDMA_INTR_MASK_SET                      0x10
#define UDMA_INTR_MASK_CLEAR                    0x14

#define UDMA_RX_INTERRUPTS ( \
        UDMA_INTR_RX_ERROR | \
        UDMA_INTR_RX_TIMEOUT | \
        UDMA_INTR_RX_READY_BUF0 | \
        UDMA_INTR_RX_READY_BUF1 | \
        UDMA_INTR_RX_READY_BUF2 | \
        UDMA_INTR_RX_READY_BUF3 | \
        UDMA_INTR_RX_READY_BUF4 | \
        UDMA_INTR_RX_READY_BUF5 | \
        UDMA_INTR_RX_READY_BUF6 | \
        UDMA_INTR_RX_READY_BUF7 | \
        UDMA_INTR_RX_ABORT | \
        UDMA_INTR_RX_DONE)

#define UDMA_RX_ERR_INTERRUPTS ( \
        UDMA_INTR_RX_ERROR | \
        UDMA_INTR_RX_TIMEOUT | \
        UDMA_INTR_RX_ABORT | \
        UDMA_INTR_RX_DONE)

#define UDMA_TX_INTERRUPTS ( \
        UDMA_INTR_TX_ABORT | \
        UDMA_INTR_TX_DONE)

#define UDMA_IS_RX_INTERRUPT(status) ((status) & UDMA_RX_INTERRUPTS)
#define UDMA_IS_TX_INTERRUPT(status) ((status) & UDMA_TX_INTERRUPTS)


/* Current devices have 8 sets of RX buffer registers */
#define UDMA_RX_BUFS_COUNT          8
#define UDMA_RX_BUFS_REG_OFFSET     (UDMA_RX_BUF1_PTR_LO - UDMA_RX_BUF0_PTR_LO)
#define UDMA_RX_BUFx_PTR_LO(x)      (UDMA_RX_BUF0_PTR_LO + ((x) * UDMA_RX_BUFS_REG_OFFSET))
#define UDMA_RX_BUFx_PTR_HI(x)      (UDMA_RX_BUF0_PTR_HI + ((x) * UDMA_RX_BUFS_REG_OFFSET))
#define UDMA_RX_BUFx_STATUS(x)      (UDMA_RX_BUF0_STATUS + ((x) * UDMA_RX_BUFS_REG_OFFSET))
#define UDMA_RX_BUFx_DATA_LEN(x)    (UDMA_RX_BUF0_DATA_LEN + ((x) * UDMA_RX_BUFS_REG_OFFSET))

/* Current devices have 2 sets of TX buffer registers */
#define UDMA_TX_BUFS_COUNT          2
#define UDMA_TX_BUFS_REG_OFFSET     (UDMA_TX_BUF1_PTR_LO - UDMA_TX_BUF0_PTR_LO)
#define UDMA_TX_BUFx_PTR_LO(x)      (UDMA_TX_BUF0_PTR_LO + ((x) * UDMA_TX_BUFS_REG_OFFSET))
#define UDMA_TX_BUFx_PTR_HI(x)      (UDMA_TX_BUF0_PTR_HI + ((x) * UDMA_TX_BUFS_REG_OFFSET))
#define UDMA_TX_BUFx_STATUS(x)      (UDMA_TX_BUF0_STATUS + ((x) * UDMA_TX_BUFS_REG_OFFSET))
#define UDMA_TX_BUFx_DATA_LEN(x)    (UDMA_TX_BUF0_DATA_LEN + ((x) * UDMA_TX_BUFS_REG_OFFSET))
#define UDMA_TX_BUFx_DATA_SENT(x)   (UDMA_TX_BUF0_DATA_SENT + ((x) * UDMA_TX_BUFS_REG_OFFSET))
#define REGS_8250                   0
#define REGS_DMA_RX                 1
#define REGS_DMA_TX                 2
#define REGS_DMA_ISR                3
#define REGS_DMA_ARB                4
#define REGS_MAX                    5

#define TX_BUF_SIZE                 4096
#define RX_BUF_SIZE                 4096
#define RX_BUFS_COUNT               2
#define UART_XMIT_SIZE              RT_DMA_PAGE_SIZE
#define KHZ                         1000
#define MHZ(x)                      ((x) * KHZ * KHZ)
#define NSEC_PER_SEC                1000000000L
#define NSEC_PER_MSEC               1000000L

static const rt_uint32_t brcmstb_rate_table[] =
{
    MHZ(81),
    MHZ(108),
    MHZ(64),    /* Actually 64285715 for some chips */
    MHZ(48),
};

static const rt_uint32_t brcmstb_rate_table_7278[] =
{
    MHZ(81),
    MHZ(108),
    0,
    MHZ(48),
};

struct brcmuart
{
    struct serial8250 parent;

    int dma_irq;
    void *regs[REGS_MAX];
    struct rt_device *dev;

    rt_ubase_t default_mux_rate;
    rt_uint32_t real_rates[RT_ARRAY_SIZE(brcmstb_rate_table)];
    const rt_uint32_t *rate_table;

    rt_uint32_t char_wait_ms;
    struct rt_timer char_wait_work;

    rt_bool_t dma_enabled;

    void *rx_bufs;
    int rx_index;
    int rx_next_buf;
    rt_ubase_t rx_addr;
    rt_size_t rx_size;
    rt_bool_t rx_running;

    void *tx_buf;
    rt_ubase_t tx_addr;
    rt_size_t tx_size;
    rt_bool_t tx_running;
};

#define to_brcmuart(serial8250) rt_container_of(serial8250, struct brcmuart, parent)

static rt_uint32_t udma_readl(struct brcmuart *brcmuart, int reg_type, int offset)
{
    return HWREG32(brcmuart->regs[reg_type] + offset);
}

static void udma_writel(struct brcmuart *brcmuart, int reg_type, int offset, rt_uint32_t value)
{
    HWREG32(brcmuart->regs[reg_type] + offset) = value;
}

static void udma_set(struct brcmuart *brcmuart, int reg_type, int offset, rt_uint32_t bits)
{
    rt_uint32_t value;
    void *reg = brcmuart->regs[reg_type] + offset;

    value = HWREG32(reg);
    value |= bits;
    HWREG32(reg) = value;
}

static void udma_unset(struct brcmuart *brcmuart, int reg_type, int offset, rt_uint32_t bits)
{
    rt_uint32_t value;
    void *reg = brcmuart->regs[reg_type] + offset;

    value = HWREG32(reg);
    value &= ~bits;
    HWREG32(reg) = value;
}

/*
 * The UART DMA engine hardware can be used by multiple UARTS, but
 * only one at a time. Sharing is not currently supported so
 * the first UART to request the DMA engine will get it and any
 * subsequent requests by other UARTS will fail.
 */
static int brcmuart_arbitration(struct brcmuart *brcmuart, rt_bool_t acquire)
{
    int ret = 0;
    rt_uint32_t rx_grant, tx_grant;

    if (acquire)
    {
        int waits = 1;

        udma_set(brcmuart, REGS_DMA_ARB, UDMA_ARB_RX, UDMA_ARB_REQ);
        udma_set(brcmuart, REGS_DMA_ARB, UDMA_ARB_TX, UDMA_ARB_REQ);

        while (RT_TRUE)
        {
            rx_grant = udma_readl(brcmuart, REGS_DMA_ARB, UDMA_ARB_RX);
            tx_grant = udma_readl(brcmuart, REGS_DMA_ARB, UDMA_ARB_TX);

            if (rx_grant & tx_grant & UDMA_ARB_GRANT)
            {
                return 0;
            }

            if (waits-- == 0)
            {
                break;
            }

            rt_thread_mdelay(1);
        }

        ret = 1;
    }

    udma_unset(brcmuart, REGS_DMA_ARB, UDMA_ARB_RX, UDMA_ARB_REQ);
    udma_unset(brcmuart, REGS_DMA_ARB, UDMA_ARB_TX, UDMA_ARB_REQ);

    return ret;
}

static void brcmuart_init_dma_hardware(struct brcmuart *brcmuart)
{
    rt_uint32_t daddr, value;

    /* Start with all interrupts disabled */
    udma_writel(brcmuart, REGS_DMA_ISR, UDMA_INTR_MASK_SET, 0xffffffff);

    udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_BUFFER_SIZE, RX_BUF_SIZE);

    /*
     * Setup buffer close to happen when 32 character times have
     * elapsed since the last character was received.
     */
    udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_BUFFER_CLOSE, 16 * 10 *32);
    value = (RX_BUFS_COUNT << UDMA_RX_CTRL_NUM_BUF_USED_SHIFT)
            | UDMA_RX_CTRL_BUF_CLOSE_MODE
            | UDMA_RX_CTRL_BUF_CLOSE_ENA;
    udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_CTRL, value);

    udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_BLOCKOUT_COUNTER, 0);
    daddr = brcmuart->rx_addr;

    for (int i = 0; i < RX_BUFS_COUNT; ++i)
    {
        /* Set RX transfer length to 0 for unknown */
        udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_TRANSFER_LEN, 0);

        udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_BUFx_PTR_LO(i),
                rt_lower_32_bits(daddr));
        udma_writel(brcmuart, REGS_DMA_RX, UDMA_RX_BUFx_PTR_HI(i),
                rt_upper_32_bits(daddr));
        daddr += RX_BUF_SIZE;
    }

    daddr = brcmuart->tx_addr;
    udma_writel(brcmuart, REGS_DMA_TX, UDMA_TX_BUFx_PTR_LO(0),
            rt_lower_32_bits(daddr));
    udma_writel(brcmuart, REGS_DMA_TX, UDMA_TX_BUFx_PTR_HI(0),
            rt_upper_32_bits(daddr));
    udma_writel(brcmuart, REGS_DMA_TX, UDMA_TX_CTRL,
            UDMA_TX_CTRL_NUM_BUF_USED_1);

    /* Clear all interrupts then enable them */
    udma_writel(brcmuart, REGS_DMA_ISR, UDMA_INTR_CLEAR, 0xffffffff);
    udma_writel(brcmuart, REGS_DMA_ISR, UDMA_INTR_MASK_CLEAR,
            UDMA_RX_INTERRUPTS | UDMA_TX_INTERRUPTS);
}

static void start_rx_dma(struct brcmuart *brcmuart)
{
    udma_unset(brcmuart, REGS_DMA_RX, UDMA_RX_CTRL, UDMA_RX_CTRL_ENA);

    /* Clear the RX ready bit for all buffers */
    for (int i = 0; i < RX_BUFS_COUNT; ++i)
    {
        udma_unset(brcmuart, REGS_DMA_RX, UDMA_RX_BUFx_STATUS(i),
                UDMA_RX_BUFX_STATUS_DATA_RDY);
    }

    /* Always start with buffer 0 */
    udma_unset(brcmuart, REGS_DMA_RX, UDMA_RX_STATUS,
               UDMA_RX_STATUS_ACTIVE_BUF_MASK);
    brcmuart->rx_next_buf = 0;

    udma_set(brcmuart, REGS_DMA_RX, UDMA_RX_CTRL, UDMA_RX_CTRL_ENA);
    brcmuart->rx_running = RT_TRUE;
}

static void stop_rx_dma(struct brcmuart *brcmuart)
{
    /* If RX is running, set the RX ABORT */
    if (brcmuart->rx_running)
    {
        udma_set(brcmuart, REGS_DMA_RX, UDMA_RX_CTRL, UDMA_RX_CTRL_ABORT);
    }
}

static int stop_tx_dma(struct brcmuart *brcmuart)
{
    rt_uint32_t value;

    /* If TX is running, set the TX ABORT */
    value = udma_readl(brcmuart, REGS_DMA_TX, UDMA_TX_CTRL);

    if (value & UDMA_TX_CTRL_ENA)
    {
        udma_set(brcmuart, REGS_DMA_TX, UDMA_TX_CTRL, UDMA_TX_CTRL_ABORT);
    }

    brcmuart->tx_running = RT_FALSE;
    return 0;
}

static void brcmuart_rx_buf_done(struct brcmuart *brcmuart, int index)
{
    rt_uint32_t status, length;

    /* Make sure we're still in sync with the hardware */
    status = udma_readl(brcmuart, REGS_DMA_RX, UDMA_RX_BUFx_STATUS(index));
    length = udma_readl(brcmuart, REGS_DMA_RX, UDMA_RX_BUFx_DATA_LEN(index));

    if ((status & UDMA_RX_BUFX_STATUS_DATA_RDY) == 0)
    {
        LOG_E("RX done interrupt but DATA_RDY not found");
        return;
    }

    if (status & (UDMA_RX_BUFX_STATUS_OVERRUN_ERR |
                  UDMA_RX_BUFX_STATUS_FRAME_ERR |
                  UDMA_RX_BUFX_STATUS_PARITY_ERR))
    {
        if (status & UDMA_RX_BUFX_STATUS_OVERRUN_ERR)
        {
            LOG_W("RX Overrun");
        }
        if (status & UDMA_RX_BUFX_STATUS_FRAME_ERR)
        {
            LOG_W("RX Framing");
        }
        if (status & UDMA_RX_BUFX_STATUS_PARITY_ERR)
        {
            LOG_W("RX Parity");
        }
    }

    brcmuart->rx_index = index * RX_BUF_SIZE;
    serial8250_dma_rx_done(&brcmuart->parent, length);
}

static void brcmuart_rx_work(struct brcmuart *brcmuart, rt_uint32_t rx_isr)
{
    rt_uint32_t rx_done_isr, check_isr;

    rx_done_isr = (rx_isr & UDMA_INTR_RX_READY_MASK);

    while (rx_done_isr)
    {
        check_isr = UDMA_INTR_RX_READY_BUF0 << brcmuart->rx_next_buf;

        if (check_isr & rx_done_isr)
        {
            brcmuart_rx_buf_done(brcmuart, brcmuart->rx_next_buf);
        }
        else
        {
            LOG_E("RX buffer ready out of sequence, restarting RX DMA");
            start_rx_dma(brcmuart);

            break;
        }
        if (rx_isr & UDMA_RX_ERR_INTERRUPTS)
        {
            if (rx_isr & UDMA_INTR_RX_ERROR)
            {
                LOG_D("RX Error");
            }
            if (rx_isr & UDMA_INTR_RX_TIMEOUT)
            {
                LOG_E("RX Timeout");
            }
            if (rx_isr & UDMA_INTR_RX_ABORT)
            {
                LOG_D("RX Abort");
            }

            brcmuart->rx_running = RT_FALSE;
        }
        /* If not ABORT, re-enable RX buffer */
        if (!(rx_isr & UDMA_INTR_RX_ABORT))
        {
            udma_unset(brcmuart, REGS_DMA_RX,
                    UDMA_RX_BUFx_STATUS(brcmuart->rx_next_buf), UDMA_RX_BUFX_STATUS_DATA_RDY);
        }

        rx_done_isr &= ~check_isr;
        brcmuart->rx_next_buf++;

        if (brcmuart->rx_next_buf == RX_BUFS_COUNT)
        {
            brcmuart->rx_next_buf = 0;
        }
    }
}

static void set_clock_mux(struct brcmuart *brcmuart, rt_uint32_t baud)
{
    rt_tick_t tick;
    int best_index = -1, real_baud, i;
    rt_uint64_t hires_rate, hires_baud, hires_err;
    rt_uint32_t percent, best_percent = RT_UINT32_MAX, quot, best_quot = 1, rate;

    /* Find the closest match for specified baud */
    for (i = 0; i < RT_ARRAY_SIZE(brcmuart->real_rates); ++i)
    {
        if (brcmuart->real_rates[i] == 0)
        {
            continue;
        }

        rate = brcmuart->real_rates[i] / 16;
        quot = RT_DIV_ROUND_CLOSEST(rate, baud);
        if (!quot)
        {
            continue;
        }

        /* increase resolution to get xx.xx percent */
        hires_rate = (rt_uint64_t)rate * 10000;
        hires_baud = (rt_uint64_t)baud * 10000;

        hires_err = rt_div_u64(hires_rate, (rt_uint64_t)quot);

        /* get the delta */
        if (hires_err > hires_baud)
        {
            hires_err = hires_err - hires_baud;
        }
        else
        {
            hires_err = hires_baud - hires_err;
        }

        percent = (rt_ubase_t)RT_DIV_ROUND_CLOSEST_ULL(hires_err, baud);

        LOG_D("Baud rate: %u, MUX Clk: %u, Error: %u.%u%%",
            baud, brcmuart->real_rates[i], percent / 100, percent % 100);

        if (percent < best_percent)
        {
            best_percent = percent;
            best_index = i;
            best_quot = quot;
        }
    }

    if (best_index == -1)
    {
        LOG_E("%d BAUD rate is too fast", baud);
        return;
    }

    rate = brcmuart->real_rates[best_index];

    if (rt_clk_set_rate(brcmuart->parent.clk, rate))
    {
        LOG_E("Selecting BAUD MUX clock");
    }

    /* Error over 3 percent will cause data errors */
    if (best_percent > 300)
    {
        LOG_E("Baud: %d has %u.%u%% error", baud, percent / 100, percent % 100);
    }

    real_baud = rate / 16 / best_quot;
    LOG_D("Selecting BAUD MUX rate: %u", rate);
    LOG_D("Requested baud: %u, Actual baud: %u", baud, real_baud);

    /* calc nanoseconds for 1.5 characters time at the given baud rate */
    i = NSEC_PER_SEC / real_baud / 10;
    i += (i / 2);
    brcmuart->char_wait_ms = NSEC_PER_MSEC / i;

    tick = rt_tick_from_millisecond(brcmuart->char_wait_ms);
    rt_timer_control(&brcmuart->char_wait_work, RT_TIMER_CTRL_SET_TIME, &tick);

    brcmuart->parent.freq = rate;
}

static rt_err_t brcmstb_serial_ios(struct serial8250 *serial, struct serial_configure *ios)
{
    struct brcmuart *brcmuart = to_brcmuart(serial);

    if (brcmuart->dma_enabled)
    {
        stop_rx_dma(brcmuart);
    }

    if (!rt_is_err_or_null(serial->clk))
    {
        set_clock_mux(brcmuart, ios->baud_rate);
    }

    serial8250_ios(serial, ios);

    if (brcmuart->dma_enabled)
    {
        start_rx_dma(brcmuart);
    }

    return RT_EOK;
}

static rt_err_t brcmuart_serial_dma_enable(struct serial8250 *serial, rt_bool_t enabled)
{
    struct brcmuart *brcmuart = to_brcmuart(serial);

    if (!brcmuart->dma_enabled)
    {
        return RT_EOK;
    }

    if (enabled)
    {
        rt_uint32_t ier;

        ier = serial->serial_in(serial, UART_IER);
        serial->serial_out(serial, UART_IER, ier & ~UART_IER_RDI);

        brcmuart_init_dma_hardware(brcmuart);
        start_rx_dma(brcmuart);
    }
    else
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&serial->spinlock);

        stop_rx_dma(brcmuart);
        stop_tx_dma(brcmuart);

        /* Disable all interrupts */
        udma_writel(brcmuart, REGS_DMA_ISR, UDMA_INTR_MASK_SET,
                UDMA_RX_INTERRUPTS | UDMA_TX_INTERRUPTS);

        rt_spin_unlock_irqrestore(&serial->spinlock, level);
    }

    return RT_EOK;
}

static rt_ssize_t brcmuart_serial_dma_tx(struct serial8250 *serial,
        const rt_uint8_t *buf, rt_size_t size)
{
    struct brcmuart *brcmuart = to_brcmuart(serial);

    if (brcmuart->tx_running)
    {
        return 0;
    }

    size = rt_min_t(rt_size_t, size, brcmuart->tx_size);
    rt_memcpy(brcmuart->tx_buf, buf, size);

    udma_writel(brcmuart, REGS_DMA_TX, UDMA_TX_TRANSFER_LEN, size);
    udma_writel(brcmuart, REGS_DMA_TX, UDMA_TX_BUF0_DATA_LEN, size);
    udma_unset(brcmuart, REGS_DMA_TX, UDMA_TX_BUF0_STATUS, UDMA_TX_BUFX_EMPTY);
    udma_set(brcmuart, REGS_DMA_TX, UDMA_TX_CTRL, UDMA_TX_CTRL_ENA);
    brcmuart->tx_running = RT_TRUE;

    return size;
}

static rt_ssize_t brcmuart_serial_dma_rx(struct serial8250 *serial,
        rt_uint8_t *buf, rt_size_t size)
{
    struct brcmuart *brcmuart = to_brcmuart(serial);

    size = rt_min_t(rt_size_t, size, brcmuart->rx_size - brcmuart->rx_index);
    rt_memcpy(buf, brcmuart->rx_bufs + brcmuart->rx_index, size);

    return size;
}

static rt_err_t brcmuart_serial_isr(struct serial8250 *serial, int irq)
{
    rt_ubase_t level;
    rt_uint32_t iir, ier, mcr, status;
    struct brcmuart *brcmuart = to_brcmuart(serial);

    iir = serial->serial_in(serial, UART_LSR);

    /*
     * There's a bug in some 8250 cores where we get a timeout
     * interrupt but there is no data ready.
     */
    if (((iir & UART_IIR_ID) == UART_IIR_RX_TIMEOUT))
    {
        level = rt_spin_lock_irqsave(&serial->spinlock);

        status = serial->serial_in(serial, UART_LSR);

        if ((status & UART_LSR_DR) == 0)
        {
            ier = serial->serial_in(serial, UART_IER);
            mcr = serial->serial_in(serial, UART_MCR);

            /*
             * if Receive Data Interrupt is enabled and
             * we're uing hardware flow control, deassert
             * RTS and wait for any chars in the pipline to
             * arrive and then check for DR again.
             */
            if ((ier & UART_IER_RDI) && (mcr & UART_MCR_AFE))
            {
                ier &= ~(UART_IER_RLSI | UART_IER_RDI);
                serial->serial_out(serial, UART_IER, ier);

                mcr = serial->serial_in(serial, UART_MCR);
                mcr &= ~UART_MCR_RTS;
                serial->serial_out(serial, UART_MCR, mcr);

                rt_timer_start(&brcmuart->char_wait_work);
            }
            else
            {
                serial->serial_in(serial, UART_RX);
            }
        }

        rt_spin_unlock_irqrestore(&serial->spinlock, level);
    }

    return RT_EOK;
}

static void brcmuart_dma_isr(int irqno, void *param)
{
    rt_ubase_t level;
    rt_uint32_t interrupts, rval, tval;
    struct brcmuart *brcmuart = param;
    struct serial8250 *serial = &brcmuart->parent;

    interrupts = udma_readl(brcmuart, REGS_DMA_ISR, UDMA_INTR_STATUS);

    if (!interrupts)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&serial->spinlock);

    /* Clear all interrupts */
    udma_writel(brcmuart, REGS_DMA_ISR, UDMA_INTR_CLEAR, interrupts);

    if ((rval = UDMA_IS_RX_INTERRUPT(interrupts)))
    {
        brcmuart_rx_work(brcmuart, rval);
    }

    if ((tval = UDMA_IS_TX_INTERRUPT(interrupts)))
    {
        if (tval & UDMA_INTR_TX_ABORT)
        {
            if (brcmuart->tx_running)
            {
                LOG_E("Unexpected TX_ABORT interrupt");
            }
        }
        else
        {
            brcmuart->tx_running = RT_FALSE;
            serial8250_dma_tx_done(serial);
        }
    }

    if ((rval | tval) == 0)
    {
        LOG_W("Spurious interrupt: 0x%x", interrupts);
    }

    rt_spin_unlock_irqrestore(&serial->spinlock, level);
}

static void brcmuart_char_wait_work(void *param)
{
    rt_ubase_t level;
    rt_uint32_t ier, status;
    struct brcmuart *brcmuart = param;
    struct serial8250 *serial = &brcmuart->parent;

    level = rt_spin_lock_irqsave(&serial->spinlock);

    status = serial->serial_in(serial, UART_LSR);

    /*
     * If a character did not arrive after the timeout, clear the false
     * receive timeout.
     */
    if ((status & UART_LSR_DR) == 0)
    {
        serial->serial_in(serial, UART_RX);
    }
    ier = serial->serial_in(serial, UART_IER);

    /* re-enable receive unless upper layer has disabled it */
    if ((ier & (UART_IER_RLSI | UART_IER_RDI)) == (UART_IER_RLSI | UART_IER_RDI))
    {
        status = serial->serial_in(serial, UART_IER);
        status |= (UART_IER_RLSI | UART_IER_RDI);
        serial->serial_out(serial, UART_IER, status);
        status = serial->serial_in(serial, UART_MCR);
        status |= UART_MCR_RTS;
        serial->serial_out(serial, UART_MCR, status);
    }

    rt_spin_unlock_irqrestore(&serial->spinlock, level);
}

static void brcmuart_free_resource(struct brcmuart *brcmuart)
{
    struct serial8250 *serial = &brcmuart->parent;

    if (serial->base)
    {
        rt_iounmap(serial->base);
    }

    if (!rt_is_err_or_null(serial->clk))
    {
        rt_clk_disable_unprepare(serial->clk);
        rt_clk_put(serial->clk);
    }

    if (brcmuart->rx_bufs)
    {
        rt_dma_free_coherent(brcmuart->dev, brcmuart->rx_size,
                brcmuart->rx_bufs, brcmuart->rx_addr);
    }
    if (brcmuart->tx_buf)
    {
        rt_dma_free_coherent(brcmuart->dev, brcmuart->tx_size,
                brcmuart->tx_buf, brcmuart->tx_addr);
    }

    if (brcmuart->dma_enabled)
    {
        brcmuart_arbitration(brcmuart, 0);
    }

    rt_free(brcmuart);
}

static void brcmuart_serial_remove(struct serial8250 *serial)
{
    struct brcmuart *brcmuart = to_brcmuart(serial);

    brcmuart_free_resource(brcmuart);

    rt_timer_detach(&brcmuart->char_wait_work);
}

static rt_err_t brcmuart_probe(struct rt_platform_device *pdev)
{
    int ridx;
    rt_err_t err;
    const char *dev_name;
    static const char * const reg_names[REGS_MAX] =
    {
        "uart", "dma_rx", "dma_tx", "dma_intr2", "dma_arb"
    };
    struct serial8250 *serial;
    struct rt_device *dev = &pdev->parent;
    struct brcmuart *brcmuart = rt_calloc(1, sizeof(*brcmuart));
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    if (!brcmuart)
    {
        return -RT_EINVAL;
    }

    brcmuart->dev = dev;

    if (pdev->id)
    {
        brcmuart->rate_table = pdev->id->data;
    }
    else
    {
        brcmuart->rate_table = brcmstb_rate_table;
    }

    serial = &brcmuart->parent;

    serial->irq = rt_dm_dev_get_irq(dev, 0);

    if (serial->irq < 0)
    {
        err = serial->irq;

        goto _free_res;
    }

    for (ridx = 0; ridx < REGS_MAX; ++ridx)
    {
        brcmuart->regs[ridx] = rt_dm_dev_iomap_by_name(dev, reg_names[ridx]);

        if (!brcmuart->regs[ridx])
        {
            if (rt_dm_dev_prop_index_of_string(dev, "reg-names", reg_names[ridx]) < 0)
            {
                break;
            }

            err = -RT_EIO;
            goto _free_res;
        }

        if (ridx == REGS_8250)
        {
            serial->base = brcmuart->regs[ridx];
        }
    }

    if (ridx != 1 && ridx != REGS_MAX)
    {
        LOG_E("Registers %s not specified", reg_names[ridx]);
        err = -RT_EINVAL;
        goto _free_res;
    }

    if (ridx > REGS_DMA_RX)
    {
        if (brcmuart_arbitration(brcmuart, 1) == 0)
        {
            rt_uint32_t txrev = 0, rxrev = 0;

            txrev = udma_readl(brcmuart, REGS_DMA_RX, UDMA_RX_REVISION);
            rxrev = udma_readl(brcmuart, REGS_DMA_TX, UDMA_TX_REVISION);

            if (txrev >= UDMA_TX_REVISION_REQUIRED &&
                rxrev >= UDMA_RX_REVISION_REQUIRED)
            {
                /* Enable the use of the DMA hardware */
                brcmuart->dma_enabled = RT_TRUE;
            }
            else
            {
                brcmuart_arbitration(brcmuart, 0);

                LOG_E("Unsupported DMA Hardware Revision");
            }
        }
        else
        {
            LOG_E("Timeout arbitrating for UART DMA hardware");
        }
    }

    if (brcmuart->dma_enabled)
    {
        brcmuart->dma_irq = rt_dm_dev_get_irq_by_name(dev, "dma");

        if (brcmuart->dma_irq < 0)
        {
            err = brcmuart->dma_irq;
            LOG_E("Get DMA IRQ error = %s", rt_strerror(err));

            goto _free_res;
        }

        brcmuart->rx_size = RX_BUF_SIZE * RX_BUFS_COUNT;
        brcmuart->rx_bufs = rt_dma_alloc_coherent(dev, brcmuart->rx_size, &brcmuart->rx_addr);

        if (!brcmuart->rx_bufs)
        {
            err = -RT_ENOMEM;
            goto _free_res;
        }

        brcmuart->tx_size = UART_XMIT_SIZE;
        brcmuart->tx_buf = rt_dma_alloc_coherent(dev, brcmuart->tx_size, &brcmuart->tx_addr);

        if (!brcmuart->tx_buf)
        {
            err = -RT_ENOMEM;
            goto _free_res;
        }
    }

    rt_dm_dev_prop_read_u32(dev, "clock-frequency", &serial->freq);

    serial->clk = rt_clk_get_by_name(dev, "sw_baud");

    if (rt_is_err(serial->clk))
    {
        err = rt_ptr_err(serial->clk);

        goto _free_res;
    }
    else if (serial->clk)
    {
        if ((err = rt_clk_prepare_enable(serial->clk)))
        {
            goto _free_res;
        }

        brcmuart->default_mux_rate = rt_clk_get_rate(serial->clk);

        for (int i = 0; i < RT_ARRAY_SIZE(brcmuart->real_rates); ++i)
        {
            if (!brcmuart->rate_table[i])
            {
                brcmuart->real_rates[i] = 0;

                continue;
            }

            if (rt_clk_set_rate(serial->clk, brcmuart->rate_table[i]))
            {
                LOG_E("Error selecting BAUD MUX clock for %u", brcmuart->rate_table[i]);
                brcmuart->real_rates[i] = brcmuart->rate_table[i];
            }
            else
            {
                brcmuart->real_rates[i] = rt_clk_get_rate(serial->clk);
            }
        }

        rt_clk_set_rate(serial->clk, brcmuart->default_mux_rate);

        serial->freq = brcmuart->default_mux_rate;
    }

    if (!serial->freq)
    {
        LOG_E("clock-frequency or clk not defined");

        err = -RT_EINVAL;
        goto _free_res;
    }

    serial->iotype = rt_dm_dev_prop_read_bool(dev, "big-endian") ?
            PORT_MMIO32BE : PORT_MMIO32;

    serial->parent.ops = &serial8250_uart_ops;
    serial->parent.config = config;

    serial->serial_ios = brcmstb_serial_ios;
    if (brcmuart->dma_enabled)
    {
        serial->serial_dma_enable = brcmuart_serial_dma_enable;
        serial->serial_dma_tx = brcmuart_serial_dma_tx;
        serial->serial_dma_rx = brcmuart_serial_dma_rx;
    }
    serial->handle_irq = &brcmuart_serial_isr;
    serial->remove = &brcmuart_serial_remove;
    serial->data = brcmuart;

    pdev->parent.user_data = serial;

    if ((err = serial8250_setup(serial)))
    {
        goto _free_res;
    }

    dev_name = rt_dm_dev_get_name(&serial->parent.parent);

    rt_timer_init(&brcmuart->char_wait_work, dev_name, brcmuart_char_wait_work, brcmuart,
            0, RT_TIMER_FLAG_PERIODIC);

    if (brcmuart->dma_enabled)
    {
        rt_hw_interrupt_install(brcmuart->dma_irq, brcmuart_dma_isr, brcmuart, dev_name);
        rt_hw_interrupt_umask(brcmuart->dma_irq);
    }

    return RT_EOK;

_free_res:
    brcmuart_free_resource(brcmuart);

    return err;
}

static rt_err_t brcmuart_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct serial8250 *serial = dev->user_data;

    rt_dm_dev_unbind_fwdata(dev, RT_NULL);

    return serial8250_remove(serial);
}

static const struct rt_ofw_node_id brcmuart_ofw_ids[] =
{
    { .type = "ttyS", .compatible = "brcm,bcm7278-uart", .data = brcmstb_rate_table_7278 },
    { .type = "ttyS", .compatible = "brcm,bcm7271-uart", .data = brcmstb_rate_table },
    { /* sentinel */ }
};

static struct rt_platform_driver brcmuart_driver =
{
    .name = "bcm7271-uart",
    .ids = brcmuart_ofw_ids,

    .probe = brcmuart_probe,
    .remove = brcmuart_remove,
};

static int brcmuart_drv_register(void)
{
    rt_platform_driver_register(&brcmuart_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(brcmuart_drv_register);
