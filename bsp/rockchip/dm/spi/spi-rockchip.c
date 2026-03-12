/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     add DMA support
 */

#include "dev_spi_dm.h"

#define DBG_TAG "spi.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>

#define ROCKCHIP_SPI_CLR_BITS(reg, bits) HWREG32(reg) = HWREG32(reg) & ~(bits)
#define ROCKCHIP_SPI_SET_BITS(reg, bits) HWREG32(reg) = HWREG32(reg) | (bits)

/* SPI register offsets */
#define ROCKCHIP_SPI_CTRLR0         0x0000
#define ROCKCHIP_SPI_CTRLR1         0x0004
#define ROCKCHIP_SPI_SSIENR         0x0008
#define ROCKCHIP_SPI_SER            0x000c
#define ROCKCHIP_SPI_BAUDR          0x0010
#define ROCKCHIP_SPI_TXFTLR         0x0014
#define ROCKCHIP_SPI_RXFTLR         0x0018
#define ROCKCHIP_SPI_TXFLR          0x001c
#define ROCKCHIP_SPI_RXFLR          0x0020
#define ROCKCHIP_SPI_SR             0x0024
#define ROCKCHIP_SPI_IPR            0x0028
#define ROCKCHIP_SPI_IMR            0x002c
#define ROCKCHIP_SPI_ISR            0x0030
#define ROCKCHIP_SPI_RISR           0x0034
#define ROCKCHIP_SPI_ICR            0x0038
#define ROCKCHIP_SPI_DMACR          0x003c
#define ROCKCHIP_SPI_DMATDLR        0x0040
#define ROCKCHIP_SPI_DMARDLR        0x0044
#define ROCKCHIP_SPI_VERSION        0x0048
#define ROCKCHIP_SPI_TXDR           0x0400
#define ROCKCHIP_SPI_RXDR           0x0800

/* Bit fields in CTRLR0 */
#define CR0_DFS_OFFSET              0
#define CR0_DFS_4BIT                0x0
#define CR0_DFS_8BIT                0x1
#define CR0_DFS_16BIT               0x2

#define CR0_CFS_OFFSET              2

#define CR0_SCPH_OFFSET             6
#define CR0_SCPH_START_EDGE         0x1
#define CR0_SCPH_MIDDLE_EDGE        0x0

#define CR0_SCPOL_OFFSET            7
#define CR0_SCPOL_HIGH              0x1
#define CR0_SCPOL_LOW               0x0

#define CR0_CSM_OFFSET              8
#define CR0_CSM_KEEP                0x0
/* ss_n be high for half sclk_out cycles */
#define CR0_CSM_HALF                0X1
/* ss_n be high for one sclk_out cycle */
#define CR0_CSM_ONE                 0x2

/* ss_n to sclk_out delay */
#define CR0_SSD_OFFSET              10
/*
 * The period between ss_n active and
 * sclk_out active is half sclk_out cycles
 */
#define CR0_SSD_HALF                0x0
/*
 * The period between ss_n active and
 * sclk_out active is one sclk_out cycle
 */
#define CR0_SSD_ONE                 0x1

#define CR0_EM_OFFSET               11
#define CR0_EM_LITTLE               0x0
#define CR0_EM_BIG                  0x1

#define CR0_FBM_OFFSET              12
#define CR0_FBM_MSB                 0x0
#define CR0_FBM_LSB                 0x1

#define CR0_BHT_OFFSET              13
#define CR0_BHT_16BIT               0x0
#define CR0_BHT_8BIT                0x1

#define CR0_RSD_OFFSET              14
#define CR0_RSD_MAX                 0x3

#define CR0_FRF_OFFSET              16
#define CR0_FRF_SPI                 0x0
#define CR0_FRF_SSP                 0x1
#define CR0_FRF_MICROWIRE           0x2

#define CR0_XFM_OFFSET              18
#define CR0_XFM_MASK                (0x03 << SPI_XFM_OFFSET)
#define CR0_XFM_TR                  0x0
#define CR0_XFM_TO                  0x1
#define CR0_XFM_RO                  0x2

#define CR0_OPM_OFFSET              20
#define CR0_OPM_MASTER              0x0
#define CR0_OPM_SLAVE               0x1

#define CR0_SOI_OFFSET              23

#define CR0_MTM_OFFSET              0x21

/* Bit fields in SER, 2bit */
#define SER_MASK                    0x3

/* Bit fields in BAUDR */
#define BAUDR_SCKDV_MIN             2
#define BAUDR_SCKDV_MAX             65534

/* Bit fields in SR, 6bit */
#define SR_MASK                     0x3f
#define SR_BUSY                     (1 << 0)
#define SR_TF_FULL                  (1 << 1)
#define SR_TF_EMPTY                 (1 << 2)
#define SR_RF_EMPTY                 (1 << 3)
#define SR_RF_FULL                  (1 << 4)
#define SR_SLAVE_TX_BUSY            (1 << 5)

/* Bit fields in ISR, IMR, ISR, RISR, 5bit */
#define INT_MASK                    0x1f
#define INT_TF_EMPTY                (1 << 0)
#define INT_TF_OVERFLOW             (1 << 1)
#define INT_RF_UNDERFLOW            (1 << 2)
#define INT_RF_OVERFLOW             (1 << 3)
#define INT_RF_FULL                 (1 << 4)
#define INT_CS_INACTIVE             (1 << 6)

/* Bit fields in ICR, 4bit */
#define ICR_MASK                    0x0f
#define ICR_ALL                     (1 << 0)
#define ICR_RF_UNDERFLOW            (1 << 1)
#define ICR_RF_OVERFLOW             (1 << 2)
#define ICR_TF_OVERFLOW             (1 << 3)

/* Bit fields in DMACR */
#define RF_DMA_EN                   (1 << 0)
#define TF_DMA_EN                   (1 << 1)

/* sclk_out: spi master internal logic in rk3x can support 50Mhz */
#define MAX_SCLK_OUT                50000000U
/* max sclk of driver strength 4mA */
#define IO_DRIVER_4MA_MAX_SCLK_OUT  24000000U

/*
 * SPI_CTRLR1 is 16-bits, so we should support lengths of 0xffff + 1. However,
 * the controller seems to hang when given 0x10000, so stick with this for now.
 */
#define ROCKCHIP_SPI_MAX_TRANLEN        0xffff

/* 2 for native cs, 2 for cs-gpio */
#define ROCKCHIP_SPI_MAX_CS_NUM         4
#define ROCKCHIP_SPI_VER2_TYPE1         0x05ec0002
#define ROCKCHIP_SPI_VER2_TYPE2         0x00110002

struct rockchip_spi_soc_data
{
    rt_uint32_t max_baud_div_in_cpha;
};

struct rockchip_spi
{
    struct rt_spi_bus parent;

    struct rt_clk *spiclk;
    struct rt_clk *apb_pclk;
    struct rt_clk *sclk_in;

    struct rt_dma_chan *dma_rx;
    struct rt_dma_chan *dma_tx;

    int irq;
    void *regs;
    rt_ubase_t dma_addr_rx;
    rt_ubase_t dma_addr_tx;

    rt_uint8_t mode;

    const void *tx;
    void *rx;
    rt_uint32_t tx_left;
    rt_uint32_t rx_left;
    rt_uint32_t max_baud_div_in_cpha;

    /* DMA state */
    rt_err_t dma_err;
    rt_bool_t is_dma_rx;
    rt_bool_t is_dma_tx;

    /* depth of the FIFO buffer */
    rt_uint32_t fifo_len;
    /* frequency of spiclk */
    rt_uint32_t freq;
    rt_uint32_t speed_hz;

    rt_uint8_t n_bytes;
    rt_uint8_t bits_per_word;
    rt_uint8_t rsd;

    rt_bool_t cs_asserted[ROCKCHIP_SPI_MAX_CS_NUM];

    rt_int8_t high_speed_state;
    rt_bool_t slave_abort;
    rt_bool_t cs_inactive;          /* spi slave tansmition stop when cs inactive */
    rt_bool_t cs_high_supported;    /* native CS supports active-high polarity */

    struct rt_spi_message *xfer;

    struct rt_completion done;
};

#define raw_to_rockchip_spi(raw) rt_container_of(raw, struct rockchip_spi, parent)

rt_inline rt_uint32_t rockchip_spi_readl(struct rockchip_spi *rk_spi, int offset)
{
    return HWREG32(rk_spi->regs + offset);
}

rt_inline void rockchip_spi_writel(struct rockchip_spi *rk_spi, int offset, rt_uint32_t value)
{
    HWREG32(rk_spi->regs + offset) = value;
}

rt_inline void spi_enable_chip(struct rockchip_spi *rk_spi, rt_bool_t enable)
{
    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_SSIENR, !!enable);
}

rt_inline void wait_for_tx_idle(struct rockchip_spi *rk_spi, rt_bool_t slave_mode)
{
    rt_tick_t timeout = rt_tick_get() + 5;

    do {
        if (slave_mode)
        {
            if (!(rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_SR) & SR_SLAVE_TX_BUSY) &&
                !((rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_SR) & SR_BUSY)))
            {
                return;
            }
        }
        else
        {
            if (!(rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_SR) & SR_BUSY))
            {
                return;
            }
        }
    } while (timeout > rt_tick_get());

    LOG_W("Controller is in busy state");
}

static rt_uint32_t get_fifo_len(struct rockchip_spi *rk_spi)
{
    rt_uint32_t ver = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_VERSION);

    switch (ver)
    {
    case ROCKCHIP_SPI_VER2_TYPE1:
    case ROCKCHIP_SPI_VER2_TYPE2:
        return 64;

    default:
        return 32;
    }
}

static void rockchip_spi_set_cs(struct rt_spi_device *spi_dev, rt_bool_t enable)
{
    rt_uint32_t en_value;
    struct rockchip_spi *rk_spi = raw_to_rockchip_spi(spi_dev->bus);
    rt_bool_t cs_asserted = spi_dev->config.mode & RT_SPI_CS_HIGH ? !enable : enable;

    /* Return immediately for no-op */
    if (cs_asserted == rk_spi->cs_asserted[spi_dev->chip_select[0]])
    {
        return;
    }

    if (spi_dev->cs_pin != PIN_NONE)
    {
        en_value = 1;
    }
    else
    {
        en_value = RT_BIT(spi_dev->chip_select[0]);
    }

    if (cs_asserted)
    {
        ROCKCHIP_SPI_SET_BITS(rk_spi->regs + ROCKCHIP_SPI_SER, en_value);
    }
    else
    {
        ROCKCHIP_SPI_CLR_BITS(rk_spi->regs + ROCKCHIP_SPI_SER, en_value);
    }

    rk_spi->cs_asserted[spi_dev->chip_select[0]] = cs_asserted;
}

static void rockchip_spi_pio_writer(struct rockchip_spi *rk_spi)
{
    rt_uint32_t tx_free, words;

    tx_free = rk_spi->fifo_len - rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_TXFLR);
    words = rt_min(rk_spi->tx_left, tx_free);

    for (rk_spi->tx_left -= words; words; --words)
    {
        rt_uint32_t txw;

        if (rk_spi->n_bytes == 1)
        {
            txw = *(rt_uint8_t *)rk_spi->tx;
        }
        else
        {
            txw = *(rt_uint16_t *)rk_spi->tx;
        }

        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_TXDR, txw);
        rk_spi->tx += rk_spi->n_bytes;
    }
}

static void rockchip_spi_pio_reader(struct rockchip_spi *rk_spi)
{
    rt_uint32_t words, rx_left;

    words = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_RXFLR);
    rx_left = (rk_spi->rx_left > words) ? rk_spi->rx_left - words : 0;

    /*
     * the hardware doesn't allow us to change fifo threshold
     * level while spi is enabled, so instead make sure to leave
     * enough words in the rx fifo to get the last interrupt
     * exactly when all words have been received
     */
    if (rx_left)
    {
        rt_uint32_t ftl = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_RXFTLR) + 1;

        if (rx_left < ftl)
        {
            rx_left = ftl;
            words = rk_spi->rx_left - rx_left;
        }
    }

    for (rk_spi->rx_left = rx_left; words; --words)
    {
        rt_uint32_t rxw = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_RXDR);

        if (!rk_spi->rx)
        {
            continue;
        }

        if (rk_spi->n_bytes == 1)
        {
            *(rt_uint8_t *)rk_spi->rx = (rt_uint8_t)rxw;
        }
        else
        {
            *(rt_uint16_t *)rk_spi->rx = (rt_uint16_t)rxw;
        }

        rk_spi->rx += rk_spi->n_bytes;
    }
}

static rt_ssize_t rockchip_spi_prepare_irq(struct rockchip_spi *rk_spi,
        struct rt_spi_message *xfer)
{
    int cs_flags = 0;

    rk_spi->tx = xfer->send_buf;
    rk_spi->rx = xfer->recv_buf;
    rk_spi->tx_left = rk_spi->tx ? xfer->length / rk_spi->n_bytes : 0;
    rk_spi->rx_left = xfer->length / rk_spi->n_bytes;

    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_ICR, 0xffffffff);

    spi_enable_chip(rk_spi, RT_TRUE);

    if (rk_spi->tx_left)
    {
        rockchip_spi_pio_writer(rk_spi);
    }

    if (rk_spi->cs_inactive)
    {
        cs_flags |= INT_CS_INACTIVE;
    }

    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_IMR, INT_RF_FULL | cs_flags);

    return xfer->length;
}

static void rockchip_spi_slave_abort(struct rockchip_spi *rk_spi)
{
    rt_uint32_t rx_fifo_left;

    if (rk_spi->is_dma_rx)
    {
        rk_spi->dma_err = -RT_EIO;
    }

    if (rk_spi->rx)
    {
        rx_fifo_left = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_RXFLR);

        for (; rx_fifo_left; --rx_fifo_left)
        {
            rt_uint32_t rxw = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_RXDR);

            if (rk_spi->n_bytes == 1)
            {
                *(rt_uint8_t *)rk_spi->rx = (rt_uint8_t)rxw;
            }
            else
            {
                *(rt_uint16_t *)rk_spi->rx = (rt_uint16_t)rxw;
            }

            rk_spi->rx += rk_spi->n_bytes;
        }

        rk_spi->xfer->length = (rt_uint32_t)(rk_spi->rx - rk_spi->xfer->recv_buf);
    }

    spi_enable_chip(rk_spi, RT_FALSE);
    rk_spi->slave_abort = RT_TRUE;

    rt_completion_done(&rk_spi->done);
}

static rt_uint32_t rockchip_spi_calc_burst_size(rt_uint32_t data_len)
{
    rt_uint32_t i;

    /* burst size: 1, 2, 4, 8 */
    for (i = 1; i < 8; i <<= 1)
    {
        if (data_len & i)
        {
            break;
        }
    }

    return i;
}

static rt_bool_t rockchip_spi_can_dma(struct rockchip_spi *rk_spi,
        struct rt_spi_message *xfer)
{
    rt_size_t bytes_per_word = rk_spi->bits_per_word <= 8 ? 1 : 2;

    if (rk_spi->dma_tx && rk_spi->dma_rx)
    {
        return xfer->length / bytes_per_word >= rk_spi->fifo_len;
    }

    return RT_FALSE;
}

static void rockchip_spi_dma_rx_done(struct rt_dma_chan *chan, rt_size_t size)
{
    struct rockchip_spi *rk_spi = chan->priv;

    if (rk_spi->is_dma_tx && !rk_spi->slave_abort)
    {
        return;
    }

    if (rk_spi->cs_inactive)
    {
        HWREG32(rk_spi->regs + ROCKCHIP_SPI_IMR) = 0;
    }

    spi_enable_chip(rk_spi, RT_FALSE);
    rt_completion_done(&rk_spi->done);
}

static void rockchip_spi_dma_tx_done(struct rt_dma_chan *chan, rt_size_t size)
{
    struct rockchip_spi *rk_spi = chan->priv;

    if (rk_spi->is_dma_rx && !rk_spi->slave_abort)
    {
        return;
    }

    wait_for_tx_idle(rk_spi, rk_spi->parent.slave);

    spi_enable_chip(rk_spi, RT_FALSE);
    rt_completion_done(&rk_spi->done);
}

static rt_ssize_t rockchip_spi_prepare_dma(struct rockchip_spi *rk_spi,
        struct rt_spi_device *spi_dev, struct rt_spi_message *xfer)
{
    rt_err_t err;

    rk_spi->dma_err = RT_EOK;
    rk_spi->is_dma_rx = RT_FALSE;
    rk_spi->is_dma_tx = RT_FALSE;

    rk_spi->rx = xfer->recv_buf;
    rk_spi->tx = xfer->send_buf;

    if (rk_spi->rx)
    {
        struct rt_dma_slave_config config;
        struct rt_dma_slave_transfer transfer;

        rt_memset(&config, 0, sizeof(config));

        config.direction = RT_DMA_DEV_TO_MEM;
        config.src_addr = rk_spi->dma_addr_rx;
        config.dst_addr = (rt_ubase_t)rt_kmem_v2p((void *)rk_spi->rx);
        config.src_addr_width = rk_spi->n_bytes;
        config.src_maxburst = rockchip_spi_calc_burst_size(xfer->length / rk_spi->n_bytes);

        if ((err = rt_dma_chan_config(rk_spi->dma_rx, &config)))
        {
            LOG_E("Config RX error = %s", rt_strerror(err));
            return err;
        }

        rt_memset(&transfer, 0, sizeof(transfer));
        transfer.src_addr = config.src_addr;
        transfer.dst_addr = config.dst_addr;
        transfer.buffer_len = xfer->length;

        if ((err = rt_dma_prep_single(rk_spi->dma_rx, &transfer)))
        {
            LOG_E("Prepare RX error = %s", rt_strerror(err));
            return err;
        }
    }

    if (rk_spi->tx)
    {
        struct rt_dma_slave_config config;
        struct rt_dma_slave_transfer transfer;

        rt_memset(&config, 0, sizeof(config));

        config.direction = RT_DMA_MEM_TO_DEV;
        config.src_addr = rk_spi->dma_addr_tx;
        config.dst_addr = (rt_ubase_t)rt_kmem_v2p((void *)rk_spi->tx);
        config.dst_addr_width = rk_spi->n_bytes;
        config.dst_maxburst = rk_spi->fifo_len / 4;

        if ((err = rt_dma_chan_config(rk_spi->dma_tx, &config)))
        {
            LOG_E("Config TX error = %s", rt_strerror(err));
            return err;
        }

        rt_memset(&transfer, 0, sizeof(transfer));
        transfer.src_addr = config.src_addr;
        transfer.dst_addr = config.dst_addr;
        transfer.buffer_len = xfer->length;

        if ((err = rt_dma_prep_single(rk_spi->dma_tx, &transfer)))
        {
            LOG_E("Prepare TX error = %s", rt_strerror(err));
            return err;
        }
    }

    if (rk_spi->rx)
    {
        rk_spi->is_dma_rx = RT_TRUE;
        rt_dma_chan_start(rk_spi->dma_rx);
    }

    if (rk_spi->cs_inactive)
    {
        HWREG32(rk_spi->regs + ROCKCHIP_SPI_IMR) = INT_CS_INACTIVE;
    }

    spi_enable_chip(rk_spi, RT_TRUE);

    if (rk_spi->tx)
    {
        rk_spi->is_dma_tx = RT_TRUE;
        rt_dma_chan_start(rk_spi->dma_tx);
    }

    return xfer->length;
}

static rt_err_t rockchip_spi_config(struct rockchip_spi *rk_spi,
        struct rt_spi_device *spi_dev, struct rt_spi_message *xfer,
        rt_bool_t use_dma, rt_bool_t slave_mode)
{
    rt_uint32_t cr0, cr1, dmacr = 0, rxftlr;
    struct rt_spi_configuration *conf = &spi_dev->config;

    rk_spi->slave_abort = RT_FALSE;

    cr0 = (CR0_BHT_8BIT << CR0_BHT_OFFSET) |    /* APB, SPI 8bit write/read */
            (CR0_SSD_ONE << CR0_SSD_OFFSET) |   /* One sclk_out cycle */
            (CR0_EM_BIG << CR0_EM_OFFSET) |     /* Big endian */
            (CR0_FRF_SPI << CR0_FRF_OFFSET) |   /* Motorola SPI */
            (CR0_CSM_KEEP << CR0_CSM_OFFSET) |  /* Keep low after every frame */
            (rk_spi->rsd << CR0_RSD_OFFSET);    /* Rxd sample delay */

    if (conf->mode & RT_SPI_CPOL)
    {
        cr0 |= CR0_SCPOL_HIGH << CR0_SCPOL_OFFSET;
    }

    if (conf->mode & RT_SPI_CPHA)
    {
        cr0 |= CR0_SCPH_START_EDGE << CR0_SCPH_OFFSET;
    }

    if (conf->mode & RT_SPI_LSB)
    {
        cr0 |= CR0_FBM_LSB << CR0_FBM_OFFSET;
    }

    if (slave_mode)
    {
        cr0 |= CR0_OPM_SLAVE << CR0_OPM_OFFSET;
    }

    if (conf->mode & RT_SPI_CS_HIGH)
    {
        cr0 |= RT_BIT(spi_dev->chip_select[0]) << CR0_SOI_OFFSET;
    }

    if (xfer->recv_buf && xfer->send_buf)
    {
        cr0 |= CR0_XFM_TR << CR0_XFM_OFFSET;
    }
    else if (xfer->recv_buf)
    {
        cr0 |= CR0_XFM_RO << CR0_XFM_OFFSET;
    }
    else if (use_dma)
    {
        cr0 |= CR0_XFM_TO << CR0_XFM_OFFSET;
    }

    switch (rk_spi->bits_per_word)
    {
    case 4:
        cr0 |= CR0_DFS_4BIT << CR0_DFS_OFFSET;
        cr1 = xfer->length - 1;
        break;

    case 8:
        cr0 |= CR0_DFS_8BIT << CR0_DFS_OFFSET;
        cr1 = xfer->length - 1;
        break;

    case 16:
        cr0 |= CR0_DFS_16BIT << CR0_DFS_OFFSET;
        cr1 = xfer->length / 2 - 1;
        break;

    default:
        return -RT_EINVAL;
    }

    if (use_dma)
    {
        if (xfer->send_buf)
        {
            dmacr |= TF_DMA_EN;
        }
        if (xfer->recv_buf)
        {
            dmacr |= RF_DMA_EN;
        }
    }

    /* If speed is larger than IO_DRIVER_4MA_MAX_SCLK_OUT, set higher driver strength. */
    if (rk_spi->high_speed_state >= 0)
    {
        struct rt_device *dev = &rk_spi->parent.parent;

        if (rk_spi->freq > IO_DRIVER_4MA_MAX_SCLK_OUT)
        {
            rt_pin_ctrl_confs_apply(dev, rk_spi->high_speed_state);
        }
    }

    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_CTRLR0, cr0);
    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_CTRLR1, cr1);

    /*
     * unfortunately setting the fifo threshold level to generate an
     * interrupt exactly when the fifo is full doesn't seem to work,
     * so we need the strict inequality here
     */
    if ((xfer->length / rk_spi->n_bytes) < rk_spi->fifo_len)
    {
        rxftlr = xfer->length / rk_spi->n_bytes - 1;
    }
    else
    {
        rxftlr = rk_spi->fifo_len / 2 - 1;
    }
    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_RXFTLR, rxftlr);

    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_DMATDLR, rk_spi->fifo_len / 2 - 1);
    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_DMARDLR,
            rockchip_spi_calc_burst_size(xfer->length / rk_spi->n_bytes) - 1);
    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_DMACR, dmacr);

    if (rk_spi->max_baud_div_in_cpha && conf->max_hz != rk_spi->speed_hz)
    {
        /* the minimum divisor is 2 */
        if (rk_spi->freq < 2 * conf->max_hz)
        {
            rt_clk_set_rate(rk_spi->spiclk, 2 * conf->max_hz);
            rk_spi->freq = rt_clk_get_rate(rk_spi->spiclk);
        }

        if (conf->mode & RT_SPI_CPHA &&
            RT_DIV_ROUND_UP(rk_spi->freq, conf->max_hz) > rk_spi->max_baud_div_in_cpha)
        {
            rt_clk_set_rate(rk_spi->spiclk, rk_spi->max_baud_div_in_cpha * conf->max_hz);
            rk_spi->freq = rt_clk_get_rate(rk_spi->spiclk);
        }
    }

    /*
     * the hardware only supports an even clock divisor, so
     * round divisor = spiclk / speed up to nearest even number
     * so that the resulting speed is <= the requested speed
     */
    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_BAUDR,
            2 * RT_DIV_ROUND_UP(rk_spi->freq, 2 * conf->max_hz));
    rk_spi->speed_hz = conf->max_hz;

    return RT_EOK;
}

static rt_err_t rockchip_spi_configure(struct rt_spi_device *spi_dev,
        struct rt_spi_configuration *conf)
{
    rt_uint32_t cr0;
    rt_uint8_t chip_select = spi_dev->chip_select[0];
    struct rockchip_spi *rk_spi = raw_to_rockchip_spi(spi_dev->bus);

    if (!conf->max_hz)
    {
        LOG_E("Not max hz in %s", rt_dm_dev_get_name(&spi_dev->parent));

        return -RT_EINVAL;
    }

    if (rk_spi->parent.cs_pins[0] < 0 && conf->mode & RT_SPI_CS_HIGH && !rk_spi->cs_high_supported)
    {
        LOG_W("None GPIO CS can't be active-high in %s",
                rt_dm_dev_get_name(&spi_dev->parent));
        return -RT_EINVAL;
    }

    cr0 = rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_CTRLR0);
    cr0 &= ~(0x3 << CR0_SCPH_OFFSET);

    if (conf->mode & RT_SPI_CPHA)
    {
        cr0 |= CR0_SCPH_START_EDGE << CR0_SCPH_OFFSET;
    }

    if (conf->mode & RT_SPI_CS_HIGH && chip_select <= 1)
    {
        cr0 |= RT_BIT(chip_select) << CR0_SOI_OFFSET;
    }
    else if (chip_select <= 1)
    {
        cr0 &= ~(RT_BIT(chip_select) << CR0_SOI_OFFSET);
    }

    rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_CTRLR0, cr0);

    return RT_EOK;
}

static rt_ssize_t rockchip_spi_xfer(struct rt_spi_device *spi_dev,
        struct rt_spi_message *xfer)
{
    rt_err_t err;
    rt_ssize_t res;
    rt_bool_t use_dma;
    struct rt_spi_bus *spi_bus = spi_dev->bus;
    struct rockchip_spi *rk_spi = raw_to_rockchip_spi(spi_bus);

    if (!xfer->length)
    {
        rt_completion_done(&rk_spi->done);

        return rk_spi->xfer ? rk_spi->xfer->length : 1;
    }

    if (!xfer->send_buf && !xfer->recv_buf)
    {
        if (xfer->cs_take)
        {
            rockchip_spi_set_cs(spi_dev, RT_TRUE);
        }

        if (xfer->cs_release)
        {
            rockchip_spi_set_cs(spi_dev, RT_FALSE);
        }

        LOG_E("No buffer for transfer");

        return -RT_EINVAL;
    }

    if (xfer->length > ROCKCHIP_SPI_MAX_TRANLEN)
    {
        LOG_E("Transfer is too long = %u", xfer->length);

        return -RT_EINVAL;
    }

    rk_spi->n_bytes = rk_spi->bits_per_word <= 8 ? 1 : 2;
    rk_spi->xfer = xfer;
    use_dma = rockchip_spi_can_dma(rk_spi, xfer);

    if ((err = rockchip_spi_config(rk_spi, spi_dev, xfer, use_dma, spi_bus->slave)))
    {
        return err;
    }

    if (use_dma)
    {
        res = rockchip_spi_prepare_dma(rk_spi, spi_dev, xfer);

        rt_completion_wait(&rk_spi->done, RT_WAITING_FOREVER);

        if (rk_spi->is_dma_tx)
        {
            rt_dma_chan_stop(rk_spi->dma_tx);
        }

        if (rk_spi->is_dma_rx)
        {
            rt_dma_chan_stop(rk_spi->dma_rx);
        }

        if (rk_spi->dma_err)
        {
            res = rk_spi->dma_err;
        }

        return res;
    }

    if (!spi_bus->slave)
    {
        rt_uint32_t timeout, div;

        if (xfer->cs_take)
        {
            rockchip_spi_set_cs(spi_dev, RT_TRUE);
        }

        res = rockchip_spi_prepare_irq(rk_spi, xfer);

        div = RT_DIV_ROUND_UP(rk_spi->freq, spi_dev->config.max_hz);
        div = (div + 1) & 0xfffe;
        timeout = xfer->length * 8 * 1000 / (rk_spi->freq / div) + 100;

        err = rt_completion_wait(&rk_spi->done, rt_tick_from_millisecond(timeout));

        if (err)
        {
            res = err;
        }

        if (xfer->cs_release)
        {
            rockchip_spi_set_cs(spi_dev, RT_FALSE);
        }

        if (xfer->send_buf && !err)
        {
            wait_for_tx_idle(rk_spi, spi_bus->slave);
        }
    }
    else
    {
        res = rockchip_spi_prepare_irq(rk_spi, xfer);

        rt_completion_wait(&rk_spi->done, RT_WAITING_FOREVER);

        if (xfer->send_buf)
        {
            wait_for_tx_idle(rk_spi, spi_bus->slave);
        }
    }

    spi_enable_chip(rk_spi, RT_FALSE);

    if (res < 0)
    {
        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_IMR, 0);
        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_ICR, 0xffffffff);
    }

    return res;
}

const static struct rt_spi_ops rockchip_spi_ops =
{
    .configure = rockchip_spi_configure,
    .xfer = rockchip_spi_xfer,
};

static void rockchip_spi_isr(int irqno, void *param)
{
    struct rockchip_spi *rk_spi = param;

    /* When int_cs_inactive comes, spi slave abort */
    if (rk_spi->cs_inactive &&
        rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_IMR) & INT_CS_INACTIVE)
    {
        rockchip_spi_slave_abort(rk_spi);

        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_IMR, 0);
        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_ICR, 0xffffffff);

        if (rk_spi->is_dma_rx || rk_spi->is_dma_tx)
        {
            rt_completion_done(&rk_spi->done);
        }

        return;
    }

    if (rk_spi->tx_left)
    {
        rockchip_spi_pio_writer(rk_spi);
    }

    rockchip_spi_pio_reader(rk_spi);

    if (!rk_spi->rx_left)
    {
        spi_enable_chip(rk_spi, RT_FALSE);

        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_IMR, 0);
        rockchip_spi_writel(rk_spi, ROCKCHIP_SPI_ICR, 0xffffffff);

        rt_completion_done(&rk_spi->done);
    }
}

static void rockchip_spi_free(struct rockchip_spi *rk_spi)
{
    if (rk_spi->regs)
    {
        rt_iounmap(rk_spi->regs);
    }

    if (!rt_is_err_or_null(rk_spi->apb_pclk))
    {
        rt_clk_disable_unprepare(rk_spi->apb_pclk);
        rt_clk_put(rk_spi->apb_pclk);
    }

    if (!rt_is_err_or_null(rk_spi->spiclk))
    {
        rt_clk_disable_unprepare(rk_spi->spiclk);
        rt_clk_put(rk_spi->spiclk);
    }

    if (!rt_is_err_or_null(rk_spi->sclk_in))
    {
        rt_clk_disable_unprepare(rk_spi->sclk_in);
        rt_clk_put(rk_spi->sclk_in);
    }

    if (!rt_is_err_or_null(rk_spi->dma_rx))
    {
        rt_dma_chan_release(rk_spi->dma_rx);
    }

    if (!rt_is_err_or_null(rk_spi->dma_tx))
    {
        rt_dma_chan_release(rk_spi->dma_tx);
    }

    rt_free(rk_spi);
}

static rt_err_t rockchip_spi_probe(struct rt_platform_device *pdev)
{
    int id;
    rt_err_t err;
    rt_uint32_t nsecs;
    rt_bool_t slave_mode;
    const char *bus_name;
    struct rt_device *dev = &pdev->parent;
    struct rockchip_spi *rk_spi = rt_calloc(1, sizeof(*rk_spi));
    const struct rockchip_spi_soc_data *soc_data;

    if (!rk_spi)
    {
        return -RT_ENOMEM;
    }

    rk_spi->regs = rt_dm_dev_iomap(dev, 0);

    if (!rk_spi->regs)
    {
        err = -RT_EIO;

        goto _fail;
    }

    rk_spi->irq = rt_dm_dev_get_irq(dev, 0);

    if (rk_spi->irq < 0)
    {
        err = rk_spi->irq;

        goto _fail;
    }

    rk_spi->apb_pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(rk_spi->apb_pclk))
    {
        err = rt_ptr_err(rk_spi->apb_pclk);

        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(rk_spi->apb_pclk)))
    {
        goto _fail;
    }

    rk_spi->spiclk = rt_clk_get_by_name(dev, "spiclk");

    if (rt_is_err(rk_spi->spiclk))
    {
        err = rt_ptr_err(rk_spi->spiclk);

        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(rk_spi->spiclk)))
    {
        goto _fail;
    }

    if (rt_dm_dev_prop_index_of_string(dev, "clock-names", "sclk_in") >= 0)
    {
        rk_spi->sclk_in = rt_clk_get_by_name(dev, "sclk_in");

        if (rt_is_err(rk_spi->sclk_in))
        {
            err = rt_ptr_err(rk_spi->sclk_in);

            goto _fail;
        }

        if ((err = rt_clk_prepare_enable(rk_spi->sclk_in)))
        {
            goto _fail;
        }
    }

    spi_enable_chip(rk_spi, RT_FALSE);

    rk_spi->freq = rt_clk_get_rate(rk_spi->spiclk);

    if (rk_spi->freq < 0)
    {
        if ((err = rt_dm_dev_prop_read_u32(dev, "clock-frequency", &rk_spi->freq)))
        {
            LOG_E("Failed to get clock or clock-frequency");

            goto _fail;
        }
    }

    if (!rt_dm_dev_prop_read_u32(dev, "rx-sample-delay-ns", &nsecs))
    {
        /* rx sample delay is expressed in parent clock cycles (max 3) */
        rt_uint32_t rsd = RT_DIV_ROUND_CLOSEST(nsecs * (rk_spi->freq >> 8),
                1000000000 >> 8);

        if (!rsd)
        {
            LOG_W("%u Hz are too slow to express %u ns delay", rk_spi->freq, nsecs);
        }
        else if (rsd > CR0_RSD_MAX)
        {
            rsd = CR0_RSD_MAX;
            LOG_W("%u Hz are too fast to express %u ns delay, clamping at %u ns",
                    rk_spi->freq, nsecs, CR0_RSD_MAX * 1000000000U / rk_spi->freq);
        }

        rk_spi->rsd = rsd;
    }

    rk_spi->bits_per_word = 8;
    rk_spi->fifo_len = get_fifo_len(rk_spi);

    if (!rk_spi->fifo_len)
    {
        LOG_E("Failed to get fifo length");
        err = -RT_EINVAL;

        goto _fail;
    }

    if ((soc_data = pdev->id->data))
    {
        rk_spi->max_baud_div_in_cpha = soc_data->max_baud_div_in_cpha;
    }

    slave_mode = rt_dm_dev_prop_read_bool(dev, "spi-slave");
    rk_spi->parent.slave = slave_mode;

    if (!slave_mode)
    {
        rt_uint32_t num_cs = 1;

        rt_dm_dev_prop_read_u32(dev, "num-cs", &num_cs);

        rk_spi->parent.num_chipselect = num_cs;
    }

    rk_spi->dma_rx = rt_dma_chan_request(dev, "rx");

    if (rt_is_err(rk_spi->dma_rx))
    {
        LOG_W("Failed to get %s DMA channel", "RX");

        rk_spi->dma_rx = RT_NULL;
    }
    else
    {
        rk_spi->dma_tx = rt_dma_chan_request(dev, "tx");

        if (rt_is_err(rk_spi->dma_tx))
        {
            LOG_W("Failed to get %s DMA channel", "TX");

            rk_spi->dma_tx = RT_NULL;
        }
    }

    if (rk_spi->dma_rx && rk_spi->dma_tx)
    {
        rt_ubase_t spi_regs_phy = (rt_ubase_t)rt_kmem_v2p(rk_spi->regs);

        rk_spi->dma_rx->callback = rockchip_spi_dma_rx_done;
        rk_spi->dma_tx->callback = rockchip_spi_dma_tx_done;

        rk_spi->dma_rx->priv = rk_spi;
        rk_spi->dma_tx->priv = rk_spi;

        rk_spi->dma_addr_rx = spi_regs_phy + ROCKCHIP_SPI_TXDR;
        rk_spi->dma_addr_tx = spi_regs_phy + ROCKCHIP_SPI_RXDR;
    }

    switch (rockchip_spi_readl(rk_spi, ROCKCHIP_SPI_VERSION))
    {
    case ROCKCHIP_SPI_VER2_TYPE2:
        rk_spi->cs_high_supported = RT_TRUE;
        rk_spi->mode |= RT_SPI_CS_HIGH;
        if (rk_spi->dma_rx && rk_spi->dma_tx && slave_mode)
        {
            rk_spi->cs_inactive = RT_TRUE;
        }
        else
        {
            rk_spi->cs_inactive = RT_FALSE;
        }
        break;

    default:
        rk_spi->cs_inactive = RT_FALSE;
        break;
    }

    rk_spi->high_speed_state = rt_pin_ctrl_confs_lookup(dev, "high_speed");

    rt_pin_ctrl_confs_apply_by_name(dev, RT_NULL);

    rt_completion_init(&rk_spi->done);

    dev->user_data = rk_spi;

    rk_spi->parent.parent.ofw_node = dev->ofw_node;

    if ((id = pdev->dev_id) >= 0)
    {
        rt_dm_dev_set_name(&rk_spi->parent.parent, "spi%u", id);
    }
    else
    {
        rt_dm_dev_set_name_auto(&rk_spi->parent.parent, "spi");
    }
    bus_name = rt_dm_dev_get_name(&rk_spi->parent.parent);

    rt_hw_interrupt_install(rk_spi->irq, rockchip_spi_isr, rk_spi, bus_name);
    rt_hw_interrupt_umask(rk_spi->irq);

    if ((err = rt_spi_bus_register(&rk_spi->parent, bus_name, &rockchip_spi_ops)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(rk_spi->irq);
    rt_pic_detach_irq(rk_spi->irq, rk_spi);

_fail:
    rockchip_spi_free(rk_spi);

    return err;
}

static rt_err_t rockchip_spi_remove(struct rt_platform_device *pdev)
{
    struct rockchip_spi *rk_spi = pdev->parent.user_data;

    spi_enable_chip(rk_spi, RT_FALSE);

    rt_hw_interrupt_mask(rk_spi->irq);
    rt_pic_detach_irq(rk_spi->irq, rk_spi);

    rt_device_unregister(&rk_spi->parent.parent);

    rockchip_spi_free(rk_spi);

    return RT_EOK;
}

static const struct rockchip_spi_soc_data px30_data =
{
    .max_baud_div_in_cpha = 4,
};

static const struct rt_ofw_node_id rockchip_spi_ofw_ids[] =
{
    { .compatible = "rockchip,px30-spi", .data = &px30_data },
    { .compatible = "rockchip,rk3036-spi", },
    { .compatible = "rockchip,rk3066-spi", },
    { .compatible = "rockchip,rk3188-spi", },
    { .compatible = "rockchip,rk3228-spi", },
    { .compatible = "rockchip,rk3288-spi", },
    { .compatible = "rockchip,rk3308-spi", },
    { .compatible = "rockchip,rk3328-spi", },
    { .compatible = "rockchip,rk3368-spi", },
    { .compatible = "rockchip,rk3399-spi", },
    { .compatible = "rockchip,rv1108-spi", },
    { .compatible = "rockchip,rv1126-spi", },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_spi_driver =
{
    .name = "rockchip-spi",
    .ids = rockchip_spi_ofw_ids,

    .probe = rockchip_spi_probe,
    .remove = rockchip_spi_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_spi_driver);
