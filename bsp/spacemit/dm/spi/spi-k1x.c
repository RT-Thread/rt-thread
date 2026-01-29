/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "dev_spi_dm.h"

#define DBG_TAG "spi.k1x.spi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>
#include <spacemit.h>
#include <dt-bindings/size.h>

/* Spacemit k1x SPI Registers */
#define TOP_CTRL                    0x00    /* SSP Top Control Register */
#define FIFO_CTRL                   0x04    /* SSP FIFO Control Register */
#define INT_EN                      0x08    /* SSP Interrupt Enable Register */
#define TO                          0x0c    /* SSP Time Out Register */
#define DATAR                       0x10    /* SSP Data Register */
#define STATUS                      0x14    /* SSP Stauts Register */
#define PSP_CTRL                    0x18    /* SSP Programmable Serial Protocal Control Register */
#define NET_WORK_CTRL               0x1c    /* SSP NET Work Control Register */
#define NET_WORK_STATUS             0x20    /* SSP Net Work Status Register */
#define RWOT_CTRL                   0x24    /* SSP RWOT Control Register */
#define RWOT_CCM                    0x28    /* SSP RWOT Counter Cycles Match Register */
#define RWOT_CVWRn                  0x2c    /* SSP RWOT Counter Value Write for Read Request Register */
#define CLK_PHASE_ADJ               0x30    /* SSP clock phase adjustment for debug */

/* 0x00 TOP_CTRL */
#define TOP_TTELP                   RT_BIT(18)
#define TOP_TTE                     RT_BIT(17)
#define TOP_SCFR                    RT_BIT(16)
#define TOP_IFS                     RT_BIT(15)
#define TOP_HOLD_FRAME_LOW          RT_BIT(14)
#define TOP_TRAIL                   RT_BIT(13)
#define TOP_LBM                     RT_BIT(12)
#define TOP_SPH                     RT_BIT(11)
#define TOP_SPO                     RT_BIT(10)
#define TOP_DSS(x)                  ((x - 1) << 5)
#define TOP_DSS_MASK                (0x1f << 5)
#define TOP_SFRMDIR                 RT_BIT(4)
#define TOP_SCLKDIR                 RT_BIT(3)
#define TOP_FRF_MASK                (0x3 << 1)
#define TOP_FRF_Motorola            (0x0 << 1)  /* Motorola's Serial Peripheral Interface (SPI) */
#define TOP_FRF_TI                  (0x1 << 1)  /* Texas Instruments' Synchronous Serial Protocol (SSP) */
#define TOP_FRF_National            (0x2 << 1)  /* National Microwire */
#define TOP_FRF_PSP                 (0x3 << 1)  /* Programmable Serial Protocol(PSP) */
#define TOP_SSE                     RT_BIT(0)

/* 0x04 FIFO_CTRL */
#define FIFO_STRF                   RT_BIT(19)
#define FIFO_EFWR                   RT_BIT(18)
#define FIFO_RXFIFO_AUTO_FULL_CTRL  RT_BIT(17)
#define FIFO_FPCKE                  RT_BIT(16)
#define FIFO_TXFIFO_WR_ENDIAN_MASK  (0x3 << 14)
#define FIFO_RXFIFO_RD_ENDIAN_MASK  (0x3 << 12)
#define FIFO_WR_ENDIAN_16BITS       RT_BIT(14)  /* Swap first 16 bits and last 16 bits */
#define FIFO_WR_ENDIAN_8BITS        (2 << 14)   /* Swap all 4 bytes */
#define FIFO_RD_ENDIAN_16BITS       RT_BIT(12)  /* Swap first 16 bits and last 16 bits */
#define FIFO_RD_ENDIAN_8BITS        (2 << 12)   /* Swap all 4 bytes */
#define FIFO_RSRE                   RT_BIT(11)
#define FIFO_TSRE                   RT_BIT(10)

/* 0x08 INT_EN */
#define INT_EN_EBCEI                RT_BIT(6)
#define INT_EN_TIM                  RT_BIT(5)
#define INT_EN_RIM                  RT_BIT(4)
#define INT_EN_TIE                  RT_BIT(3)
#define INT_EN_RIE                  RT_BIT(2)
#define INT_EN_TINTE                RT_BIT(1)
#define INT_EN_PINTE                RT_BIT(0)

/* 0x0C TO */
#define TIMEOUT(x)                  ((x) << 0)

/* 0x10 DATAR */
#define DATA(x)                     ((x) << 0)

/* 0x14 STATUS */
#define STATUS_OSS                  RT_BIT(23)
#define STATUS_TX_OSS               RT_BIT(22)
#define STATUS_BCE                  RT_BIT(21)
#define STATUS_ROR                  RT_BIT(20)
#define STATUS_RNE                  RT_BIT(14)
#define STATUS_RFS                  RT_BIT(13)
#define STATUS_TUR                  RT_BIT(12)
#define STATUS_TNF                  RT_BIT(6)
#define STATUS_TFS                  RT_BIT(5)
#define STATUS_EOC                  RT_BIT(4)
#define STATUS_TINT                 RT_BIT(3)
#define STATUS_PINT                 RT_BIT(2)
#define STATUS_CSS                  RT_BIT(1)
#define STATUS_BSY                  RT_BIT(0)

/* 0x18 PSP_CTRL */
#define PSP_EDMYSTOP(x)             ((x) << 27)
#define PSP_EMYSTOP(x)              ((x) << 25)
#define PSP_EDMYSTRT(x)             ((x) << 23)
#define PSP_DMYSTRT(x)              ((x) << 21)
#define PSP_STRTDLY(x)              ((x) << 18)
#define PSP_SFRMWDTH(x)             ((x) << 12)
#define PSP_SFRMDLY(x)              ((x) << 5)
#define PSP_SFRMP                   (1 << 4)
#define PSP_FSRT                    (1 << 3)
#define PSP_ETDS                    (1 << 2)
#define PSP_SCMODE(x)               ((x) << 0)

/* 0x1C NET_WORK_CTRL */
#define RTSA(x)                     ((x) << 12)
#define RTSA_MASK                   (0xff << 12)
#define TTSA(x)                     ((x) << 4)
#define TTSA_MASK                   (0xff << 4)
#define NET_FRDC(x)                 ((x) << 1)
#define NET_WORK_MODE               (1 << 0)

/* 0x20 NET_WORK_STATUS */
#define NET_SATUS_NMBSY             (1 << 3)
#define NET_STATUS_TSS(x)           ((x) << 0)

/* 0x24 RWOT_CTRL */
#define RWOT_MASK_RWOT_LAST_SAMPLE  RT_BIT(4)
#define RWOT_CLR_RWOT_CYCLE         RT_BIT(3)
#define RWOT_SET_RWOT_CYCLE         RT_BIT(2)
#define RWOT_CYCLE_RWOT_EN          RT_BIT(1)
#define RWOT_RWOT                   RT_BIT(0)

#define TIMOUT_DFLT                 3000
#define TIMOUT_DFLT_SLAVE           0x40000

#define RX_THRESH_DFLT              9
#define TX_THRESH_DFLT              8
/* 0x14  */
#define STATUS_TFL_MASK             (0x1f << 7)     /* Transmit FIFO Level mask */
#define STATUS_RFL_MASK             (0x1f << 15)    /* Receive FIFO Level mask */
/* 0x4 */
#define FIFO_TFT                    (0x0000001f)    /* Transmit FIFO Threshold (mask) */
#define FIFO_TxTresh(x)             (((x) - 1) << 0) /* level [1..32] */
#define FIFO_RFT                    (0x000003e0)    /* Receive FIFO Threshold (mask) */
#define FIFO_RxTresh(x)             (((x) - 1) << 5) /* level [1..32] */
/*
 * Select the right DMA implementation.
 */
#define MAX_DMA_LEN                 (512 * SIZE_KB)
#define DEFAULT_DMA_FIFO_CTRL       (FIFO_TSRE | FIFO_RSRE)
#define DEFAULT_DMA_TOP_CTRL        (TOP_TRAIL)

struct k1x_spi;

struct chip_data
{
    rt_uint32_t top_ctrl;
    rt_uint32_t fifo_ctrl;
    rt_uint32_t timeout;
    rt_uint8_t n_bytes;
    rt_uint32_t dma_burst_size;
    rt_uint32_t threshold;
    rt_uint32_t dma_threshold;
    rt_uint8_t enable_dma;
    rt_bool_t (*write)(struct k1x_spi *spi);
    rt_bool_t (*read)(struct k1x_spi *spi);
};

struct k1x_spi
{
    struct rt_spi_bus parent;

    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    int irq;
    void *ioaddr;
    rt_uint32_t ssdr_physical;
    rt_uint32_t max_speed_hz;

    /* SSP masks*/
    rt_uint32_t dma_fifo_ctrl;
    rt_uint32_t dma_top_ctrl;
    rt_uint32_t int_cr;
    rt_uint32_t dma_cr;
    rt_uint32_t clear_sr;
    rt_uint32_t mask_sr;

    rt_bool_t enable_dma;
    rt_atomic_t dma_running;
    struct rt_dma_chan *rx_chan;
    struct rt_dma_chan *tx_chan;
    struct rt_dma_slave_config rx_config;
    struct rt_dma_slave_config tx_config;
    struct rt_dma_slave_transfer rx_transfer;
    struct rt_dma_slave_transfer tx_transfer;

    rt_bool_t (*write)(struct k1x_spi *spi);
    rt_bool_t (*read)(struct k1x_spi *spi);
    void (*transfer_handler)(struct k1x_spi *spi);

    void *tx, *tx_end;
    void *rx, *rx_end;
    rt_uint8_t n_bytes;
    struct rt_spi_message *cur_msg;

    struct chip_data cur_chip;
    struct rt_completion cur_msg_completion;

    /* Support RX FIFO auto full control and endian swap */
    rt_bool_t slave_mode;
    rt_uint32_t ssp_enhancement;
    struct rt_timer slave_rx_timer;
};

#define raw_to_k1x_spi(raw) rt_container_of(raw, struct k1x_spi, parent)

rt_inline rt_uint32_t k1x_spi_read(struct k1x_spi *spi, int reg)
{
    return HWREG32(spi->ioaddr + reg);
}

rt_inline void k1x_spi_write(struct k1x_spi *spi, int reg, rt_uint32_t val)
{
    HWREG32(spi->ioaddr + reg) = val;
}

static void k1x_spi_dma_transfer_complete(struct k1x_spi *spi, rt_bool_t error)
{
    if (!rt_atomic_dec_and_test(&spi->dma_running))
    {
        return;
    }

    /*
     * If the other CPU is still handling the ROR interrupt we
     * might not know about the error yet. So we re-check the
     * ROR bit here before we clear the status register.
     */
    if (!error)
    {
        rt_uint32_t status = k1x_spi_read(spi, STATUS) & spi->mask_sr;

        error = status & STATUS_ROR;
    }

    /* Clear status & disable interrupts */
    k1x_spi_write(spi, FIFO_CTRL, k1x_spi_read(spi, FIFO_CTRL) & ~spi->dma_fifo_ctrl);
    k1x_spi_write(spi, TOP_CTRL, k1x_spi_read(spi, TOP_CTRL) & ~spi->dma_top_ctrl);
    k1x_spi_write(spi, STATUS, spi->clear_sr);
    k1x_spi_write(spi, TO, 0);

    if (error)
    {
        /* In case we got an error we disable the SSP now */
        k1x_spi_write(spi, TOP_CTRL, k1x_spi_read(spi, TOP_CTRL) & ~TOP_SSE);
    }
}

static void k1x_spi_dma_callback(struct rt_dma_chan *chan, rt_size_t size)
{
    struct k1x_spi *spi = chan->priv;

    k1x_spi_dma_transfer_complete(spi, RT_FALSE);
}

static void k1x_spi_dma_transfer(struct k1x_spi *spi)
{
    rt_uint32_t status;

    status = k1x_spi_read(spi, STATUS) & spi->mask_sr;

    if ((spi->slave_mode && status & STATUS_TINT) || (status & STATUS_ROR))
    {
        if (spi->rx)
        {
            rt_dma_chan_stop(spi->rx_chan);
        }
        if (spi->tx)
        {
            rt_dma_chan_stop(spi->tx_chan);
        }
        k1x_spi_dma_transfer_complete(spi, RT_TRUE);
    }
}

static rt_err_t k1x_spi_set_dma_burst_and_threshold(struct chip_data *chip,
        struct rt_spi_device *device,
        rt_uint8_t bits_per_word, rt_uint32_t *burst_code, rt_uint32_t *threshold)
{
    /*
     * If the DMA burst size is given in chip_info we use
     * that, otherwise we set it to half of FIFO size; SPI
     * FIFO has 16 entry, so FIFO size = 16*bits_per_word/8;
     * Also we use the default FIFO thresholds for now.
     */
    if (chip && chip->dma_burst_size)
    {
        *burst_code = chip->dma_burst_size;
    }
    else if (bits_per_word <= 8)
    {
        *burst_code = 8;
    }
    else if (bits_per_word <= 16)
    {
        *burst_code = 16;
    }
    else
    {
        *burst_code = 32;
    }

    *threshold = FIFO_RxTresh(RX_THRESH_DFLT) | FIFO_TxTresh(TX_THRESH_DFLT);

    return RT_EOK;
}

static rt_bool_t k1x_spi_txfifo_full(struct k1x_spi *spi)
{
    return !(k1x_spi_read(spi, STATUS) & STATUS_TNF);
}

/* Clear all rx fifo useless data */
static int k1x_spi_flush(struct k1x_spi *spi)
{
    unsigned long limit = RT_TICK_PER_SECOND << 1;

    do {
        while (k1x_spi_read(spi, STATUS) & STATUS_RNE)
        {
            k1x_spi_read(spi, DATAR);
        }
    } while ((k1x_spi_read(spi, STATUS) & STATUS_BSY) && --limit);

    k1x_spi_write(spi, STATUS, STATUS_ROR);

    return limit;
}

static rt_bool_t null_writer(struct k1x_spi *spi)
{
    rt_uint8_t n_bytes = spi->n_bytes;

    if (k1x_spi_txfifo_full(spi) || spi->tx == spi->tx_end)
    {
        return RT_FALSE;
    }

    k1x_spi_write(spi, DATAR, 0);
    spi->tx += n_bytes;

    return RT_TRUE;
}

static rt_bool_t null_reader(struct k1x_spi *spi)
{
    rt_uint8_t n_bytes = spi->n_bytes;

    while ((k1x_spi_read(spi, STATUS) & STATUS_RNE) && (spi->rx < spi->rx_end))
    {
        k1x_spi_read(spi, DATAR);
        spi->rx += n_bytes;
    }

    return spi->rx == spi->rx_end;
}

static rt_bool_t u8_writer(struct k1x_spi *spi)
{
    if (k1x_spi_txfifo_full(spi) || spi->tx == spi->tx_end)
    {
        return RT_FALSE;
    }

    k1x_spi_write(spi, DATAR, *(rt_uint8_t *)(spi->tx));
    ++spi->tx;

    return RT_TRUE;
}

static rt_bool_t u8_reader(struct k1x_spi *spi)
{
    while ((k1x_spi_read(spi, STATUS) & STATUS_RNE) && spi->rx < spi->rx_end)
    {
        *(rt_uint8_t *)(spi->rx) = k1x_spi_read(spi, DATAR);
        ++spi->rx;
    }

    return spi->rx == spi->rx_end;
}

static rt_bool_t u16_writer(struct k1x_spi *spi)
{
    if (k1x_spi_txfifo_full(spi) || spi->tx == spi->tx_end)
    {
        return RT_FALSE;
    }

    k1x_spi_write(spi, DATAR, *(rt_uint16_t *)(spi->tx));
    spi->tx += 2;

    return RT_TRUE;
}

static rt_bool_t u16_reader(struct k1x_spi *spi)
{
    while ((k1x_spi_read(spi, STATUS) & STATUS_RNE) && spi->rx < spi->rx_end)
    {
        *(rt_uint16_t *)(spi->rx) = k1x_spi_read(spi, DATAR);
        spi->rx += 2;
    }

    return spi->rx == spi->rx_end;
}

static rt_bool_t u32_writer(struct k1x_spi *spi)
{
    if (k1x_spi_txfifo_full(spi) || spi->tx == spi->tx_end)
    {
        return RT_FALSE;
    }

    k1x_spi_write(spi, DATAR, *(rt_uint32_t *)(spi->tx));
    spi->tx += 4;

    return RT_TRUE;
}

static rt_bool_t u32_reader(struct k1x_spi *spi)
{
    while ((k1x_spi_read(spi, STATUS) & STATUS_RNE) && spi->rx < spi->rx_end)
    {
        *(rt_uint32_t *)(spi->rx) = k1x_spi_read(spi, DATAR);
        spi->rx += 4;
    }

    return spi->rx == spi->rx_end;
}

static void reset_fifo_ctrl(struct k1x_spi *spi)
{
    rt_uint32_t fifo_ctrl = 0;
    struct chip_data *chip = &spi->cur_chip;

    fifo_ctrl |= chip->threshold;
    k1x_spi_write(spi, FIFO_CTRL, fifo_ctrl);
}

static void int_transfer_stop(struct k1x_spi *spi)
{
    rt_uint32_t int_en = 0;

    /* Stop SSP */
    k1x_spi_write(spi, STATUS, spi->clear_sr);
    reset_fifo_ctrl(spi);

    int_en = k1x_spi_read(spi, INT_EN);
    int_en &= ~spi->int_cr;
    k1x_spi_write(spi, INT_EN, int_en);

    k1x_spi_write(spi, TO, 0);
}

static void interrupt_transfer(struct k1x_spi *spi)
{
    rt_uint32_t irq_mask, irq_status;

    irq_mask = (k1x_spi_read(spi, INT_EN) & INT_EN_TIE) ?
                   spi->mask_sr : spi->mask_sr & ~STATUS_TFS;
    irq_status = k1x_spi_read(spi, STATUS) & irq_mask;

    if (irq_status & STATUS_ROR)
    {
        /* Stop and rstc SSP */
        int_transfer_stop(spi);
        k1x_spi_flush(spi);
        k1x_spi_write(spi, TOP_CTRL, k1x_spi_read(spi, TOP_CTRL) & ~(TOP_SSE | TOP_HOLD_FRAME_LOW));
        return;
    }

    if (irq_status & STATUS_TINT)
    {
        k1x_spi_write(spi, STATUS, STATUS_TINT);

        if (spi->read(spi))
        {
            int_transfer_stop(spi);
            return;
        }
    }

    /* Drain rx fifo, Fill tx fifo and prevent overruns */
    do {
        if (spi->read(spi))
        {
            int_transfer_stop(spi);
            return;
        }
    } while (spi->write(spi));

    if (spi->read(spi))
    {
        int_transfer_stop(spi);
        return;
    }

    if (spi->tx == spi->tx_end)
    {
        rt_uint32_t int_en;

        int_en = k1x_spi_read(spi, INT_EN);
        int_en &= ~INT_EN_TIE;

        k1x_spi_write(spi, INT_EN, int_en);
    }
}

static void slave_rx_timer_expired(void *param)
{
    struct k1x_spi *spi = param;

    if (spi->rx)
    {
        rt_dma_chan_stop(spi->rx_chan);
    }
    if (spi->tx)
    {
        rt_dma_chan_stop(spi->tx_chan);
    }
    k1x_spi_dma_transfer_complete(spi, RT_TRUE);
}

static rt_err_t k1x_spi_spi_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *conf)
{
    rt_uint32_t tx_thres, rx_thres;
    struct k1x_spi *spi = raw_to_k1x_spi(device->bus);
    struct chip_data *chip = &spi->cur_chip;

    tx_thres = TX_THRESH_DFLT;
    rx_thres = RX_THRESH_DFLT;

    chip->top_ctrl = 0;
    chip->fifo_ctrl = 0;
    chip->enable_dma = spi->enable_dma;

    if (spi->slave_mode)
    {
        chip->dma_burst_size = 32;
    }

    if (chip->enable_dma)
    {
        /* Set up legal burst and threshold for dma */
        if (k1x_spi_set_dma_burst_and_threshold(chip, device,
                device->config.data_width, &chip->dma_burst_size, &chip->dma_threshold))
        {
            LOG_W("DMA burst size reduced to match bits_per_word");
        }
    }
    chip->threshold = (FIFO_RxTresh(rx_thres) & FIFO_RFT) | (FIFO_TxTresh(tx_thres) & FIFO_TFT);

    chip->top_ctrl &= ~(TOP_SPO | TOP_SPH);
    chip->top_ctrl |= (((device->config.mode & RT_SPI_CPHA) != 0) ? TOP_SPH : 0)
                    | (((device->config.mode & RT_SPI_CPOL) != 0) ? TOP_SPO : 0);

    /* Enable rx fifo auto full control */
    if (spi->ssp_enhancement)
    {
        chip->fifo_ctrl |= FIFO_RXFIFO_AUTO_FULL_CTRL;
    }

    if (device->config.data_width <= 8)
    {
        chip->n_bytes = 1;
        chip->read = u8_reader;
        chip->write = u8_writer;
    }
    else if (device->config.data_width <= 16)
    {
        chip->n_bytes = 2;
        chip->read = u16_reader;
        chip->write = u16_writer;
    }
    else if (device->config.data_width <= 32)
    {
        chip->n_bytes = 4;
        chip->read = u32_reader;
        chip->write = u32_writer;
    }

    if (rt_clk_get_rate(spi->clk) != spi->max_speed_hz)
    {
        rt_clk_set_rate(spi->clk, spi->max_speed_hz);
    }

    return RT_EOK;
}

static rt_ssize_t k1x_spi_spi_xfer(struct rt_spi_device *device,
        struct rt_spi_message *msg)
{
    rt_err_t err;
    rt_uint8_t bits = 0;
    rt_uint32_t top_ctrl, fifo_ctrl, int_en = 0, dma_thresh, dma_burst;
    struct k1x_spi *spi = raw_to_k1x_spi(device->bus);
    struct chip_data *chip = &spi->cur_chip;

    dma_thresh = chip->dma_threshold;
    dma_burst = chip->dma_burst_size;

    if (spi->slave_mode)
    {
        rt_tick_t tick = rt_tick_from_millisecond(1000);

        rt_timer_control(&spi->slave_rx_timer, RT_TIMER_CTRL_SET_TIME, &tick);

        rt_timer_start(&spi->slave_rx_timer);
    }

    /* Setup the transfer state based on the type of transfer */
    if (k1x_spi_flush(spi) == 0)
    {
        rt_timer_stop(&spi->slave_rx_timer);

        LOG_E("Flush failed");
        return -RT_EIO;
    }

    if (device->config.max_hz && device->config.max_hz != rt_clk_get_rate(spi->clk))
    {
        rt_clk_set_rate(spi->clk, device->config.max_hz);
    }

    spi->n_bytes = chip->n_bytes;
    spi->tx = (void *)msg->send_buf;
    spi->tx_end = spi->tx + msg->length;
    spi->rx = msg->recv_buf;
    spi->rx_end = spi->rx + msg->length;
    spi->write = spi->tx ? chip->write : null_writer;
    spi->read = spi->rx ? chip->read : null_reader;
    spi->cur_msg = msg;

    /* Change speed and bit per word on a per transfer */
    bits = device->config.data_width;

    if (bits <= 8)
    {
        spi->n_bytes = 1;
        spi->read = spi->read != null_reader ? u8_reader : null_reader;
        spi->write = spi->write != null_writer ? u8_writer : null_writer;
    }
    else if (bits <= 16)
    {
        spi->n_bytes = 2;
        spi->read = spi->read != null_reader ? u16_reader : null_reader;
        spi->write = spi->write != null_writer ? u16_writer : null_writer;
    }
    else if (bits <= 32)
    {
        spi->n_bytes = 4;
        spi->read = spi->read != null_reader ? u32_reader : null_reader;
        spi->write = spi->write != null_writer ? u32_writer : null_writer;
    }

    /*
    * If bits/word is changed in dma mode, then must check the
    * thresholds and burst also
    */
    if (chip->enable_dma)
    {
        if (k1x_spi_set_dma_burst_and_threshold(chip,
                device, bits, &dma_burst, &dma_thresh))
        {
            LOG_W("DMA burst size reduced to match bits_per_word");
        }
    }

    /*
     * Configure topctrl:
     *  set Motorola Frame Format
     *  set DSS
     */
    top_ctrl = TOP_FRF_Motorola | TOP_DSS(bits);
    LOG_D("%u Hz, %s", spi->max_speed_hz, chip->enable_dma ? "DMA" : "PIO");

    top_ctrl |= chip->top_ctrl;
    fifo_ctrl = chip->fifo_ctrl;

    if (spi->ssp_enhancement)
    {
        /*
         * If transfer length is times of 4, then use
         * 32 bit fifo width with endian swap support
         */
        if (msg->length % 4 == 0 && bits <= 16)
        {
            if (bits <= 8)
            {
                fifo_ctrl |=  FIFO_WR_ENDIAN_8BITS | FIFO_RD_ENDIAN_8BITS;
            }
            else if (bits <= 16)
            {
                fifo_ctrl |= FIFO_WR_ENDIAN_16BITS | FIFO_RD_ENDIAN_16BITS;
            }

            bits = 32;
            spi->n_bytes = 4;
            if (msg->recv_buf)
            {
                spi->read = u32_reader;
            }
            if (msg->send_buf)
            {
                spi->write = u32_writer;
            }

            if (chip->enable_dma)
            {
                if (k1x_spi_set_dma_burst_and_threshold(chip,
                        device, bits, &dma_burst, &dma_thresh))
                {
                    LOG_W("DMA burst size reduced to match bits_per_word");
                }
            }

            top_ctrl &= ~TOP_DSS_MASK;
            top_ctrl |= TOP_DSS(32);
        }
    }

    /* Check DMA is possible */
    if (msg->length <= MAX_DMA_LEN)
    {
        enum rt_dma_slave_buswidth width;

        /* Ensure we have the correct interrupt handler */
        spi->transfer_handler = k1x_spi_dma_transfer;

        switch (spi->n_bytes)
        {
        case 1:
            width = RT_DMA_SLAVE_BUSWIDTH_1_BYTE;
            break;
        case 2:
            width = RT_DMA_SLAVE_BUSWIDTH_2_BYTES;
            break;
        default:
            width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
            break;
        }

        if (spi->rx)
        {
            spi->rx_config.dst_addr = (rt_ubase_t)rt_kmem_v2p(spi->rx);
            spi->rx_config.dst_addr_width = width;
            spi->rx_config.dst_maxburst = msg->length;

            if ((err = rt_dma_chan_config(spi->rx_chan, &spi->rx_config)))
            {
                return err;
            }

            spi->rx_transfer.buffer_len = msg->length;
            spi->rx_transfer.dst_addr = spi->rx_config.dst_addr;

            if ((err = rt_dma_prep_single(spi->rx_chan, &spi->rx_transfer)))
            {
                return err;
            }

            if ((err = rt_dma_chan_start(spi->rx_chan)))
            {
                return err;
            }
        }

        if (spi->tx)
        {
            spi->tx_config.src_addr = (rt_ubase_t)rt_kmem_v2p(spi->tx);
            spi->tx_config.src_addr_width = width;
            spi->tx_config.src_maxburst = chip->dma_burst_size;

            if ((err = rt_dma_chan_config(spi->tx_chan, &spi->tx_config)))
            {
                return err;
            }

            spi->tx_transfer.buffer_len = msg->length;
            spi->tx_transfer.src_addr = spi->tx_config.src_addr;

            if ((err = rt_dma_prep_single(spi->tx_chan, &spi->tx_transfer)))
            {
                return err;
            }

            if ((err = rt_dma_chan_start(spi->tx_chan)))
            {
                return err;
            }
        }

        /* Clear status and start DMA engine */
        fifo_ctrl |= chip->fifo_ctrl | dma_thresh | spi->dma_fifo_ctrl;
        top_ctrl |= chip->top_ctrl | spi->dma_top_ctrl;
        k1x_spi_write(spi, STATUS, spi->clear_sr);

        rt_atomic_store(&spi->dma_running, 1);

        int_en = k1x_spi_read(spi, INT_EN) | spi->dma_cr;
    }
    else
    {
        /* Ensure we have the correct interrupt handler */
        spi->transfer_handler = interrupt_transfer;

        fifo_ctrl = fifo_ctrl | chip->fifo_ctrl | chip->threshold;
        int_en = k1x_spi_read(spi, INT_EN) | spi->int_cr;
        k1x_spi_write(spi, STATUS, spi->clear_sr);
    }

    k1x_spi_write(spi, TO, chip->timeout);

    if (spi->slave_mode)
    {
        top_ctrl |= TOP_SSE | TOP_SCLKDIR | TOP_SFRMDIR;
    }
    else
    {
        top_ctrl |= TOP_HOLD_FRAME_LOW;
    }

    /*
     * This part changed the logic
     * 1. clear SSE
     * 2. write TOP_CTRL and other register
     * 3. set SSE in the end of this function
     */
    top_ctrl &= ~TOP_SSE;
    k1x_spi_write(spi, TOP_CTRL, top_ctrl);
    k1x_spi_write(spi, FIFO_CTRL, fifo_ctrl);
    k1x_spi_write(spi, INT_EN, int_en);
    top_ctrl |= TOP_SSE;
    k1x_spi_write(spi, TOP_CTRL, top_ctrl);

    rt_completion_wait(&spi->cur_msg_completion, RT_WAITING_FOREVER);

    /* Disable the SSP now */
    k1x_spi_write(spi, TOP_CTRL, k1x_spi_read(spi, TOP_CTRL) & ~(TOP_SSE | TOP_HOLD_FRAME_LOW));

    return msg->length;
}

static struct rt_spi_ops k1x_spi_spi_ops =
{
    .configure = k1x_spi_spi_configure,
    .xfer = k1x_spi_spi_xfer,
};

static void k1x_spi_spi_isr(int irq, void *param)
{
    rt_uint32_t int_en, mask, isr;
    struct k1x_spi *spi = param;

    /*
     * If the device is not yet in RPM suspended state and we get an
     * interrupt that is meant for another device, check if status bits
     * are all set to one. That means that the device is already powered off.
     */
    isr = k1x_spi_read(spi, STATUS);
    if (isr == ~0)
    {
        return;
    }

    int_en = k1x_spi_read(spi, INT_EN);
    mask = spi->mask_sr;

    /* Ignore possible writes if we don't need to write */
    if (!(int_en & INT_EN_TIE))
    {
        mask &= ~STATUS_TFS;
    }

    /* Ignore RX timeout interrupt if it is disabled */
    if (!(int_en & INT_EN_TINTE))
    {
        mask &= ~STATUS_TINT;
    }

    if (!(isr & mask))
    {
        return;
    }

    if (!spi->cur_msg)
    {
        k1x_spi_write(spi, TOP_CTRL,
                k1x_spi_read(spi, TOP_CTRL) & ~(TOP_SSE | TOP_HOLD_FRAME_LOW));
        k1x_spi_write(spi, INT_EN,
                k1x_spi_read(spi, INT_EN) & ~spi->int_cr);
        k1x_spi_write(spi, TO, 0);
        k1x_spi_write(spi, STATUS, spi->clear_sr);

        LOG_E("Bad message state in interrupt handler");

        /* Never fail */
        return;
    }

    return spi->transfer_handler(spi);
}

static void k1x_spi_free(struct k1x_spi *spi, struct rt_device *dev)
{
    if (!rt_is_err_or_null(spi->rstc))
    {
        rt_reset_control_assert(spi->rstc);
        rt_reset_control_put(spi->rstc);
    }

    if (!rt_is_err_or_null(spi->clk))
    {
        rt_clk_disable_unprepare(spi->clk);
        rt_clk_put(spi->clk);
    }

    if (!rt_is_err_or_null(spi->rx_chan))
    {
        rt_dma_chan_release(spi->rx_chan);
    }

    if (!rt_is_err_or_null(spi->tx_chan))
    {
        rt_dma_chan_release(spi->tx_chan);
    }
}

static rt_err_t k1x_spi_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t value, bus_num;
    const char *bus_name;
    struct rt_device *dev = &pdev->parent;
    struct k1x_spi *spi = rt_calloc(1, sizeof(*spi));

    if (!spi)
    {
        return -RT_ENOMEM;
    }

    if (!(spi->ioaddr = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }
    spi->ssdr_physical = (rt_ubase_t)rt_kmem_v2p(spi->ioaddr) + DATAR;

    if ((spi->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = spi->irq;
        goto _fail;
    }

    spi->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(spi->clk))
    {
        err = rt_ptr_err(spi->clk);
        goto _fail;
    }

    spi->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(spi->clk))
    {
        err = rt_ptr_err(spi->clk);
        goto _fail;
    }

    spi->enable_dma = !rt_dm_dev_prop_read_bool(dev, "k1x,ssp-disable-dma");
    spi->ssp_enhancement = rt_dm_dev_prop_read_bool(dev, "k1x,ssp-enhancement");
    spi->slave_mode = rt_dm_dev_prop_read_bool(dev, "k1x,ssp-slave-mode");

    if ((err = rt_dm_dev_prop_read_u32(dev, "k1x,ssp-clock-rate", &spi->max_speed_hz)))
    {
        goto _fail;
    }

    spi->int_cr = INT_EN_TIE | INT_EN_RIE | INT_EN_TINTE; /* INT_EN */
    spi->dma_cr = spi->slave_mode ? INT_EN_TINTE : 0;
    spi->clear_sr = STATUS_ROR | STATUS_TINT;
    spi->mask_sr = STATUS_TINT | STATUS_RFS | STATUS_TFS | STATUS_ROR;
    spi->dma_top_ctrl = DEFAULT_DMA_TOP_CTRL;
    spi->dma_fifo_ctrl = DEFAULT_DMA_FIFO_CTRL;

    /* Setup DMA if requested */
    if (spi->enable_dma)
    {
        spi->tx_chan = rt_dma_chan_request(dev, "tx");

        if (!rt_is_err_or_null(spi->tx_chan))
        {
            spi->tx_chan->callback = k1x_spi_dma_callback;

            spi->tx_config.direction = RT_DMA_MEM_TO_DEV;
            spi->tx_config.dst_addr = spi->ssdr_physical;

            spi->tx_transfer.dst_addr = spi->tx_config.dst_addr;
        }
        else
        {
            goto _fail;
        }

        spi->rx_chan = rt_dma_chan_request(dev, "rx");

        if (!rt_is_err_or_null(spi->rx_chan))
        {
            spi->rx_chan->callback = k1x_spi_dma_callback;

            spi->rx_config.direction = RT_DMA_MEM_TO_DEV;
            spi->rx_config.src_addr = spi->ssdr_physical;

            spi->rx_transfer.src_addr = spi->rx_config.src_addr;
        }
        else
        {
            goto _fail;
        }
    }

    rt_clk_set_rate(spi->clk, spi->max_speed_hz);
    spi->max_speed_hz = rt_clk_get_rate(spi->clk);

    rt_clk_prepare_enable(spi->clk);
    rt_reset_control_deassert(spi->rstc);

    bus_num = 0;
    rt_dm_dev_prop_read_u32(dev, "k1x,ssp-id", &bus_num);

    if ((bus_num == 2 || bus_num == 3) &&
        rt_dm_dev_prop_read_bool(dev, "k1x,ssp-enable-clk-phase-adj"))
    {
        k1x_spi_write(spi, CLK_PHASE_ADJ, 0x1);
    }

    /* Load default SSP configuration */
    k1x_spi_write(spi, TOP_CTRL, 0);
    k1x_spi_write(spi, FIFO_CTRL, 0);
    value = FIFO_RxTresh(RX_THRESH_DFLT) | FIFO_TxTresh(TX_THRESH_DFLT);
    k1x_spi_write(spi, FIFO_CTRL, value);
    value = TOP_FRF_Motorola | TOP_DSS(8);
    k1x_spi_write(spi, TOP_CTRL, value);
    k1x_spi_write(spi, TO, 0);

    k1x_spi_write(spi, PSP_CTRL, 0);

    rt_completion_init(&spi->cur_msg_completion);

    dev->user_data = spi;

    spi->parent.parent.ofw_node = dev->ofw_node;

    if (pdev->dev_id >= 0)
    {
        rt_dm_dev_set_name(&spi->parent.parent, "spi%u", pdev->dev_id);
    }
    else
    {
        if (bus_num >= 0)
        {
            rt_dm_dev_set_name(&spi->parent.parent, "spi%u", bus_num);
        }
        else
        {
            rt_dm_dev_set_name_auto(&spi->parent.parent, "spi");
        }
    }
    bus_name = rt_dm_dev_get_name(&spi->parent.parent);

    if (spi->slave_mode)
    {
        rt_timer_init(&spi->slave_rx_timer, bus_name, slave_rx_timer_expired, spi,
                0, RT_TIMER_FLAG_PERIODIC);
    }

    rt_hw_interrupt_install(spi->irq, k1x_spi_spi_isr, spi, bus_name);
    rt_hw_interrupt_umask(spi->irq);

    if ((err = rt_spi_bus_register(&spi->parent, bus_name, &k1x_spi_spi_ops)))
    {
        goto _free_irq;
    }

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(spi->irq);
    rt_pic_detach_irq(spi->irq, spi);

_fail:
    k1x_spi_free(spi, dev);

    return err;
}

static rt_err_t k1x_spi_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct k1x_spi *spi = dev->user_data;

    rt_hw_interrupt_mask(spi->irq);
    rt_pic_detach_irq(spi->irq, spi);

    rt_device_unregister(&spi->parent.parent);

    /* Disable the SSP at the peripheral and SOC level */
    k1x_spi_write(spi, TOP_CTRL, 0);
    k1x_spi_write(spi, FIFO_CTRL, 0);

    k1x_spi_free(spi, dev);

    return RT_EOK;
}

static const struct rt_ofw_node_id k1x_spi_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-spi" },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_spi_driver =
{
    .name = "k1x-spi",
    .ids = k1x_spi_ofw_ids,

    .probe = k1x_spi_probe,
    .remove = k1x_spi_remove,
};
RT_PLATFORM_DRIVER_EXPORT(k1x_spi_driver);
