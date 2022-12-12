/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <dm36x.h>
#include <edma.h>
#include "spi-davinci.h"

#define unlikely(x) x

#define barrier() __asm__ __volatile__("": : :"memory")
#define cpu_relax() barrier()

#define SPI_DEBUG           0
#if SPI_DEBUG
#define spi_dbg(dev, fmt, ...) \
    do { \
        rt_kprintf("%s:", dev->parent.name); \
        rt_kprintf(fmt, ##__VA_ARGS__); \
    } while(0)
#else
#define spi_dbg(dev, fmt, ...)
#endif

#define SZ_64K 0x10000
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define SPI_NO_RESOURCE     ((resource_size_t)-1)

#define SPI_MAX_CHIPSELECT  2

#define CS_DEFAULT  0xFF

#define __iomem
#define BIT(nr)         (1UL << (nr))

#define SPIFMT_PHASE_MASK   BIT(16)
#define SPIFMT_POLARITY_MASK    BIT(17)
#define SPIFMT_DISTIMER_MASK    BIT(18)
#define SPIFMT_SHIFTDIR_MASK    BIT(20)
#define SPIFMT_WAITENA_MASK BIT(21)
#define SPIFMT_PARITYENA_MASK   BIT(22)
#define SPIFMT_ODD_PARITY_MASK  BIT(23)
#define SPIFMT_WDELAY_MASK  0x3f000000u
#define SPIFMT_WDELAY_SHIFT 24
#define SPIFMT_PRESCALE_SHIFT   8

/* SPIPC0 */
#define SPIPC0_DIFUN_MASK   BIT(11)     /* MISO */
#define SPIPC0_DOFUN_MASK   BIT(10)     /* MOSI */
#define SPIPC0_CLKFUN_MASK  BIT(9)      /* CLK */
#define SPIPC0_SPIENA_MASK  BIT(8)      /* nREADY */

#define SPIINT_MASKALL      0x0101035F
#define SPIINT_MASKINT      0x0000015F
#define SPI_INTLVL_1        0x000001FF
#define SPI_INTLVL_0        0x00000000

/* SPIDAT1 (upper 16 bit defines) */
#define SPIDAT1_CSHOLD_MASK BIT(12)

/* SPIGCR1 */
#define SPIGCR1_CLKMOD_MASK BIT(1)
#define SPIGCR1_MASTER_MASK     BIT(0)
#define SPIGCR1_POWERDOWN_MASK  BIT(8)
#define SPIGCR1_LOOPBACK_MASK   BIT(16)
#define SPIGCR1_SPIENA_MASK BIT(24)

/* SPIBUF */
#define SPIBUF_TXFULL_MASK  BIT(29)
#define SPIBUF_RXEMPTY_MASK BIT(31)

/* SPIDELAY */
#define SPIDELAY_C2TDELAY_SHIFT 24
#define SPIDELAY_C2TDELAY_MASK  (0xFF << SPIDELAY_C2TDELAY_SHIFT)
#define SPIDELAY_T2CDELAY_SHIFT 16
#define SPIDELAY_T2CDELAY_MASK  (0xFF << SPIDELAY_T2CDELAY_SHIFT)
#define SPIDELAY_T2EDELAY_SHIFT 8
#define SPIDELAY_T2EDELAY_MASK  (0xFF << SPIDELAY_T2EDELAY_SHIFT)
#define SPIDELAY_C2EDELAY_SHIFT 0
#define SPIDELAY_C2EDELAY_MASK  0xFF

/* Error Masks */
#define SPIFLG_DLEN_ERR_MASK        BIT(0)
#define SPIFLG_TIMEOUT_MASK     BIT(1)
#define SPIFLG_PARERR_MASK      BIT(2)
#define SPIFLG_DESYNC_MASK      BIT(3)
#define SPIFLG_BITERR_MASK      BIT(4)
#define SPIFLG_OVRRUN_MASK      BIT(6)
#define SPIFLG_BUF_INIT_ACTIVE_MASK BIT(24)
#define SPIFLG_ERROR_MASK       (SPIFLG_DLEN_ERR_MASK \
                | SPIFLG_TIMEOUT_MASK | SPIFLG_PARERR_MASK \
                | SPIFLG_DESYNC_MASK | SPIFLG_BITERR_MASK \
                | SPIFLG_OVRRUN_MASK)

#define SPIINT_DMA_REQ_EN   BIT(16)

/* SPI Controller registers */
#define SPIGCR0     0x00
#define SPIGCR1     0x04
#define SPIINT      0x08
#define SPILVL      0x0c
#define SPIFLG      0x10
#define SPIPC0      0x14
#define SPIDAT1     0x3c
#define SPIBUF      0x40
#define SPIDELAY    0x48
#define SPIDEF      0x4c
#define SPIFMT0     0x50

/* We have 2 DMA channels per CS, one for RX and one for TX */
struct davinci_spi_dma {
    int         tx_channel;
    int         rx_channel;
    int         dummy_param_slot;
    enum dma_event_q    eventq;
};

/* SPI Controller driver's private data. */
struct davinci_spi {
    struct rt_spi_bus parent;
    struct clk      *clk;

    u8          version;
    void __iomem        *base;
    u32         irq;
    struct rt_completion    done;

    const void      *tx;
    void            *rx;
#define SMP_CACHE_BYTES 32
#define SPI_TMP_BUFSZ   (SMP_CACHE_BYTES + 1)
    u8          rx_tmp_buf[SPI_TMP_BUFSZ];
    int         rcount;
    int         wcount;
    struct davinci_spi_dma  dma;

    void            (*get_rx)(u32 rx_data, struct davinci_spi *);
    u32         (*get_tx)(struct davinci_spi *);

    u8          bytes_per_word[SPI_MAX_CHIPSELECT];
    u8          chip_sel[SPI_MAX_CHIPSELECT];
    struct davinci_spi_config *controller_data;
    int         cshold_bug;
};

static struct davinci_spi_config davinci_spi_default_cfg;

extern void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size);
extern void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size);

static void davinci_spi_rx_buf_u8(u32 data, struct davinci_spi *dspi)
{
    if (dspi->rx) {
        u8 *rx = dspi->rx;
        *rx++ = (u8)data;
        dspi->rx = rx;
    }
}

static void davinci_spi_rx_buf_u16(u32 data, struct davinci_spi *dspi)
{
    if (dspi->rx) {
        u16 *rx = dspi->rx;
        *rx++ = (u16)data;
        dspi->rx = rx;
    }
}

static u32 davinci_spi_tx_buf_u8(struct davinci_spi *dspi)
{
    u32 data = 0;
    if (dspi->tx) {
        const u8 *tx = dspi->tx;
        data = *tx++;
        dspi->tx = tx;
    }
    return data;
}

static u32 davinci_spi_tx_buf_u16(struct davinci_spi *dspi)
{
    u32 data = 0;
    if (dspi->tx) {
        const u16 *tx = dspi->tx;
        data = *tx++;
        dspi->tx = tx;
    }
    return data;
}

static inline void set_io_bits(void __iomem *addr, u32 bits)
{
    u32 v = readl(addr);

    v |= bits;
    writel(v, addr);
}

static inline void clear_io_bits(void __iomem *addr, u32 bits)
{
    u32 v = readl(addr);

    v &= ~bits;
    writel(v, addr);
}

/*
 * Interface to control the chip select signal
 */
static void davinci_spi_chipselect(struct rt_spi_device *spi, int value)
{
    struct davinci_spi *dspi;
    u8 chip_sel = (u8)spi->parent.user_data;
    u16 spidat1 = CS_DEFAULT;
    bool gpio_chipsel = RT_FALSE;

    dspi = spi->bus->parent.user_data;

    if (chip_sel < SPI_MAX_CHIPSELECT &&
                dspi->chip_sel[chip_sel] != SPI_INTERN_CS)
        gpio_chipsel = RT_TRUE;

    /*
     * Board specific chip select logic decides the polarity and cs
     * line for the controller
     */
    if (gpio_chipsel) {
        if (value == 0)
            gpio_set_value(dspi->chip_sel[chip_sel], 0);
        else
            gpio_set_value(dspi->chip_sel[chip_sel], 1);
    } else {
        spidat1 = readw(dspi->base + SPIDAT1 + 2);
        if (value == 0) {
            spidat1 |= SPIDAT1_CSHOLD_MASK;
            spidat1 &= ~(0x1 << chip_sel);
        } else {
            spidat1 &= ~SPIDAT1_CSHOLD_MASK;
            spidat1 |= 0x03;
        }
        rt_kprintf("0x%04x\n", spidat1);

        writew(spidat1, dspi->base + SPIDAT1 + 2);
    }
}

/**
 * davinci_spi_get_prescale - Calculates the correct prescale value
 * @maxspeed_hz: the maximum rate the SPI clock can run at
 *
 * This function calculates the prescale value that generates a clock rate
 * less than or equal to the specified maximum.
 *
 * Returns: calculated prescale - 1 for easy programming into SPI registers
 * or negative error number if valid prescalar cannot be updated.
 */
static inline int davinci_spi_get_prescale(struct davinci_spi *dspi,
                            u32 max_speed_hz)
{
    int ret;

    ret = DIV_ROUND_UP(clk_get_rate(dspi->clk), max_speed_hz);

    if (ret < 3) {
        rt_kprintf("spi clock freq too high\n");
        ret = 3;
    }
    if (ret > 256) {
        rt_kprintf("spi clock freq too litter\n");
        ret = 256;
    }

    /*if (ret < 3 || ret > 256)
        return -RT_ERROR;*/

    return ret - 1;
}

/**
 * davinci_spi_setup_transfer - This functions will determine transfer method
 * @spi: spi device on which data transfer to be done
 * @t: spi transfer in which transfer info is filled
 *
 * This function determines data transfer method (8/16/32 bit transfer).
 * It will also set the SPI Clock Control register according to
 * SPI slave device freq.
 */
static int davinci_spi_setup_transfer(struct rt_spi_device *spi,
        struct rt_spi_configuration *cfg)
{

    struct davinci_spi *dspi;
    struct davinci_spi_config *spicfg;
    u8 bits_per_word = 0;
    u32 hz = 0, spifmt = 0, prescale = 0;
    u8 chip_select = (u8)spi->parent.user_data;

    dspi = spi->bus->parent.user_data;
    spicfg = (struct davinci_spi_config *)dspi->controller_data;
    if (!spicfg)
        spicfg = &davinci_spi_default_cfg;

    bits_per_word = cfg->data_width;
    hz = cfg->max_hz;

    /*
     * Assign function pointer to appropriate transfer method
     * 8bit, 16bit or 32bit transfer
     */
    if (bits_per_word <= 8 && bits_per_word >= 2) {
        dspi->get_rx = davinci_spi_rx_buf_u8;
        dspi->get_tx = davinci_spi_tx_buf_u8;
        dspi->bytes_per_word[chip_select] = 1;
    } else if (bits_per_word <= 16 && bits_per_word >= 2) {
        dspi->get_rx = davinci_spi_rx_buf_u16;
        dspi->get_tx = davinci_spi_tx_buf_u16;
        dspi->bytes_per_word[chip_select] = 2;
    } else
        return -RT_ERROR;

    /* Set up SPIFMTn register, unique to this chipselect. */

    prescale = davinci_spi_get_prescale(dspi, hz);
    if (prescale < 0)
        return prescale;

    spifmt = (prescale << SPIFMT_PRESCALE_SHIFT) | (bits_per_word & 0x1f);

    if (!(cfg->mode & RT_SPI_MSB))
        spifmt |= SPIFMT_SHIFTDIR_MASK;

    if (cfg->mode & RT_SPI_CPOL)
        spifmt |= SPIFMT_POLARITY_MASK;

    if (!(cfg->mode & RT_SPI_CPHA))
        spifmt |= SPIFMT_PHASE_MASK;

    /*
     * Version 1 hardware supports two basic SPI modes:
     *  - Standard SPI mode uses 4 pins, with chipselect
     *  - 3 pin SPI is a 4 pin variant without CS (SPI_NO_CS)
     *  (distinct from SPI_3WIRE, with just one data wire;
     *  or similar variants without MOSI or without MISO)
     *
     * Version 2 hardware supports an optional handshaking signal,
     * so it can support two more modes:
     *  - 5 pin SPI variant is standard SPI plus SPI_READY
     *  - 4 pin with enable is (SPI_READY | SPI_NO_CS)
     */

    if (dspi->version == SPI_VERSION_2) {

        u32 delay = 0;

        spifmt |= ((spicfg->wdelay << SPIFMT_WDELAY_SHIFT)
                            & SPIFMT_WDELAY_MASK);

        if (spicfg->odd_parity)
            spifmt |= SPIFMT_ODD_PARITY_MASK;

        if (spicfg->parity_enable)
            spifmt |= SPIFMT_PARITYENA_MASK;

        if (spicfg->timer_disable) {
            spifmt |= SPIFMT_DISTIMER_MASK;
        } else {
            delay |= (spicfg->c2tdelay << SPIDELAY_C2TDELAY_SHIFT)
                        & SPIDELAY_C2TDELAY_MASK;
            delay |= (spicfg->t2cdelay << SPIDELAY_T2CDELAY_SHIFT)
                        & SPIDELAY_T2CDELAY_MASK;
        }

        if (cfg->mode & RT_SPI_READY) {
            spifmt |= SPIFMT_WAITENA_MASK;
            delay |= (spicfg->t2edelay << SPIDELAY_T2EDELAY_SHIFT)
                        & SPIDELAY_T2EDELAY_MASK;
            delay |= (spicfg->c2edelay << SPIDELAY_C2EDELAY_SHIFT)
                        & SPIDELAY_C2EDELAY_MASK;
        }

        writel(delay, dspi->base + SPIDELAY);
    }

    writel(spifmt, dspi->base + SPIFMT0);

    return 0;
}

#if 0
/**
 * davinci_spi_setup - This functions will set default transfer method
 * @spi: spi device on which data transfer to be done
 *
 * This functions sets the default transfer method.
 */
static int davinci_spi_setup(struct spi_device *spi)
{
    int retval = 0;
    struct davinci_spi *dspi;
    struct davinci_spi_platform_data *pdata;

    dspi = spi_master_get_devdata(spi->master);
    pdata = dspi->pdata;

    /* if bits per word length is zero then set it default 8 */
    if (!spi->bits_per_word)
        spi->bits_per_word = 8;

    if (!(spi->mode & SPI_NO_CS)) {
        if ((pdata->chip_sel == NULL) ||
            (pdata->chip_sel[spi->chip_select] == SPI_INTERN_CS))
            set_io_bits(dspi->base + SPIPC0, 1 << spi->chip_select);

    }

    if (spi->mode & SPI_READY)
        set_io_bits(dspi->base + SPIPC0, SPIPC0_SPIENA_MASK);

    if (spi->mode & SPI_LOOP)
        set_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);
    else
        clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);

    return retval;
}
#endif

static int davinci_spi_check_error(struct davinci_spi *dspi, int int_status)
{
    struct rt_device *sdev = &dspi->parent.parent;

    if (int_status & SPIFLG_TIMEOUT_MASK) {
        spi_dbg(sdev, "SPI Time-out Error\n");
        return -RT_ETIMEOUT;
    }
    if (int_status & SPIFLG_DESYNC_MASK) {
        spi_dbg(sdev, "SPI Desynchronization Error\n");
        return -RT_EIO;
    }
    if (int_status & SPIFLG_BITERR_MASK) {
        spi_dbg(sdev, "SPI Bit error\n");
        return -RT_EIO;
    }

    if (dspi->version == SPI_VERSION_2) {
        if (int_status & SPIFLG_DLEN_ERR_MASK) {
            spi_dbg(sdev, "SPI Data Length Error\n");
            return -RT_EIO;
        }
        if (int_status & SPIFLG_PARERR_MASK) {
            spi_dbg(sdev, "SPI Parity Error\n");
            return -RT_EIO;
        }
        if (int_status & SPIFLG_OVRRUN_MASK) {
            spi_dbg(sdev, "SPI Data Overrun error\n");
            return -RT_EIO;
        }
        if (int_status & SPIFLG_BUF_INIT_ACTIVE_MASK) {
            spi_dbg(sdev, "SPI Buffer Init Active\n");
            return -RT_EBUSY;
        }
    }

    return 0;
}

/**
 * davinci_spi_process_events - check for and handle any SPI controller events
 * @dspi: the controller data
 *
 * This function will check the SPIFLG register and handle any events that are
 * detected there
 */
static int davinci_spi_process_events(struct davinci_spi *dspi)
{
    u32 buf, status, errors = 0, spidat1;

    buf = readl(dspi->base + SPIBUF);

    if (dspi->rcount > 0 && !(buf & SPIBUF_RXEMPTY_MASK)) {
        dspi->get_rx(buf & 0xFFFF, dspi);
        dspi->rcount--;
    }

    status = readl(dspi->base + SPIFLG);

    if (unlikely(status & SPIFLG_ERROR_MASK)) {
        errors = status & SPIFLG_ERROR_MASK;
        goto out;
    }

    if (dspi->wcount > 0 && !(buf & SPIBUF_TXFULL_MASK)) {
        spidat1 = readl(dspi->base + SPIDAT1);
        dspi->wcount--;
        spidat1 &= ~0xFFFF;
        spidat1 |= 0xFFFF & dspi->get_tx(dspi);
        writel(spidat1, dspi->base + SPIDAT1);
    }

out:
    return errors;
}

static void davinci_spi_dma_callback(unsigned lch, u16 status, void *data)
{
    struct davinci_spi *dspi = data;
    struct davinci_spi_dma *dma = &dspi->dma;

    edma_stop(lch);

    if (status == DMA_COMPLETE) {
        if (lch == dma->rx_channel)
            dspi->rcount = 0;
        if (lch == dma->tx_channel)
            dspi->wcount = 0;
    }

    if ((!dspi->wcount && !dspi->rcount) || (status != DMA_COMPLETE))
        rt_completion_done(&dspi->done);
}

/**
 * davinci_spi_bufs - functions which will handle transfer data
 * @spi: spi device on which data transfer to be done
 * @t: spi transfer in which transfer info is filled
 *
 * This function will put data to be transferred into data register
 * of SPI controller and then wait until the completion will be marked
 * by the IRQ Handler.
 */
static int davinci_spi_bufs(struct rt_spi_device *spi, struct rt_spi_message *msg)
{
    struct davinci_spi *dspi;
    int data_type, ret;
    u32 tx_data, spidat1;
    u32 errors = 0;
    struct davinci_spi_config *spicfg;
    unsigned rx_buf_count;
    struct rt_device *sdev;
    u8 chip_select = (u8)spi->parent.user_data;

    dspi = spi->bus->parent.user_data;
    spicfg = (struct davinci_spi_config *)dspi->controller_data;
    if (!spicfg)
        spicfg = &davinci_spi_default_cfg;
    sdev = &dspi->parent.parent;

    /* convert len to words based on bits_per_word */
    data_type = dspi->bytes_per_word[chip_select];

    dspi->tx = msg->send_buf;
    dspi->rx = msg->recv_buf;
    dspi->wcount = msg->length / data_type;
    dspi->rcount = dspi->wcount;

    spidat1 = readl(dspi->base + SPIDAT1);

    clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_POWERDOWN_MASK);
    set_io_bits(dspi->base + SPIGCR1, SPIGCR1_SPIENA_MASK);

    rt_completion_init(&(dspi->done));

    if (msg->cs_take)
        davinci_spi_chipselect(spi, 0);

    if (spicfg->io_type == SPI_IO_TYPE_INTR)
        set_io_bits(dspi->base + SPIINT, SPIINT_MASKINT);

    if (msg->length > 0) {
        if (spicfg->io_type != SPI_IO_TYPE_DMA) {
            /* start the transfer */
            dspi->wcount--;
            tx_data = dspi->get_tx(dspi);
            spidat1 &= 0xFFFF0000;
            spidat1 |= tx_data & 0xFFFF;
            writel(spidat1, dspi->base + SPIDAT1);
        } else {
            struct davinci_spi_dma *dma;
            unsigned long tx_reg, rx_reg;
            struct edmacc_param param;
            void *rx_buf;
            int b, c;

            dma = &dspi->dma;

            tx_reg = (unsigned long)dspi->base + SPIDAT1;
            rx_reg = (unsigned long)dspi->base + SPIBUF;

            /*
             * Transmit DMA setup
             *
             * If there is transmit data, map the transmit buffer, set it
             * as the source of data and set the source B index to data
             * size. If there is no transmit data, set the transmit register
             * as the source of data, and set the source B index to zero.
             *
             * The destination is always the transmit register itself. And
             * the destination never increments.
             */

            if (msg->send_buf) {
                mmu_clean_dcache((rt_uint32_t)msg->send_buf, (rt_uint32_t)msg->length);
            }

            /*
             * If number of words is greater than 65535, then we need
             * to configure a 3 dimension transfer.  Use the BCNTRLD
             * feature to allow for transfers that aren't even multiples
             * of 65535 (or any other possible b size) by first transferring
             * the remainder amount then grabbing the next N blocks of
             * 65535 words.
             */

            c = dspi->wcount / (SZ_64K - 1);    /* N 65535 Blocks */
            b = dspi->wcount - c * (SZ_64K - 1);    /* Remainder */
            if (b)
                c++;
            else
                b = SZ_64K - 1;

            param.opt = TCINTEN | EDMA_TCC(dma->tx_channel);
            param.src = msg->send_buf ? msg->send_buf : tx_reg;
            param.a_b_cnt = b << 16 | data_type;
            param.dst = tx_reg;
            param.src_dst_bidx = msg->send_buf ? data_type : 0;
            param.link_bcntrld = 0xffffffff;
            param.src_dst_cidx = msg->send_buf ? data_type : 0;
            param.ccnt = c;
            edma_write_slot(dma->tx_channel, &param);
            edma_link(dma->tx_channel, dma->dummy_param_slot);

            /*
             * Receive DMA setup
             *
             * If there is receive buffer, use it to receive data. If there
             * is none provided, use a temporary receive buffer. Set the
             * destination B index to 0 so effectively only one byte is used
             * in the temporary buffer (address does not increment).
             *
             * The source of receive data is the receive data register. The
             * source address never increments.
             */

            if (msg->recv_buf) {
                rx_buf = msg->recv_buf;
                rx_buf_count = msg->length;
            } else {
                rx_buf = dspi->rx_tmp_buf;
                rx_buf_count = sizeof(dspi->rx_tmp_buf);
            }

            mmu_invalidate_dcache((rt_uint32_t)rx_buf, (rt_uint32_t)rx_buf_count);

            param.opt = TCINTEN | EDMA_TCC(dma->rx_channel);
            param.src = rx_reg;
            param.a_b_cnt = b << 16 | data_type;
            param.dst = rx_buf;
            param.src_dst_bidx = (msg->recv_buf ? data_type : 0) << 16;
            param.link_bcntrld = 0xffffffff;
            param.src_dst_cidx = (msg->recv_buf ? data_type : 0) << 16;
            param.ccnt = c;
            edma_write_slot(dma->rx_channel, &param);

            if (dspi->cshold_bug)
                writew(spidat1 >> 16, dspi->base + SPIDAT1 + 2);

            edma_start(dma->rx_channel);
            edma_start(dma->tx_channel);
            set_io_bits(dspi->base + SPIINT, SPIINT_DMA_REQ_EN);
        }

        /* Wait for the transfer to complete */
        if (spicfg->io_type != SPI_IO_TYPE_POLL) {
            rt_completion_wait(&(dspi->done), RT_WAITING_FOREVER);
        } else {
            while (dspi->rcount > 0 || dspi->wcount > 0) {
                errors = davinci_spi_process_events(dspi);
                if (errors)
                    break;
                cpu_relax();
            }
        }
    }

    if (msg->cs_release)
        davinci_spi_chipselect(spi, 1);

    clear_io_bits(dspi->base + SPIINT, SPIINT_MASKALL);
    if (spicfg->io_type == SPI_IO_TYPE_DMA) {
        clear_io_bits(dspi->base + SPIINT, SPIINT_DMA_REQ_EN);
    }

    clear_io_bits(dspi->base + SPIGCR1, SPIGCR1_SPIENA_MASK);
    set_io_bits(dspi->base + SPIGCR1, SPIGCR1_POWERDOWN_MASK);

    /*
     * Check for bit error, desync error,parity error,timeout error and
     * receive overflow errors
     */
    if (errors) {
        ret = davinci_spi_check_error(dspi, errors);
        rt_kprintf("%s: error reported but no error found!\n",
                            spi->bus->parent.parent.name);
        return ret;
    }

    if (dspi->rcount != 0 || dspi->wcount != 0) {
        spi_dbg(sdev, "SPI data transfer error\n");
        return -RT_EIO;
    }

    return msg->length;
}

/**
 * davinci_spi_irq - Interrupt handler for SPI Master Controller
 * @irq: IRQ number for this SPI Master
 * @context_data: structure for SPI Master controller davinci_spi
 *
 * ISR will determine that interrupt arrives either for READ or WRITE command.
 * According to command it will do the appropriate action. It will check
 * transfer length and if it is not zero then dispatch transfer command again.
 * If transfer length is zero then it will indicate the COMPLETION so that
 * davinci_spi_bufs function can go ahead.
 */
static void davinci_spi_irq(int irq, void *data)
{
    struct davinci_spi *dspi = data;
    int status;

    status = davinci_spi_process_events(dspi);
    if (unlikely(status != 0))
        clear_io_bits(dspi->base + SPIINT, SPIINT_MASKINT);

    if ((!dspi->rcount && !dspi->wcount) || status)
        rt_completion_done(&dspi->done);
}

static int davinci_spi_request_dma(struct davinci_spi *dspi)
{
    int r;
    struct davinci_spi_dma *dma = &dspi->dma;

    r = edma_alloc_channel(dma->rx_channel, davinci_spi_dma_callback, dspi,
                                dma->eventq);
    if (r < 0) {
        rt_kprintf("Unable to request DMA channel for SPI RX\n");
        r = -RT_EFULL;
        goto rx_dma_failed;
    }

    r = edma_alloc_channel(dma->tx_channel, davinci_spi_dma_callback, dspi,
                                dma->eventq);
    if (r < 0) {
        rt_kprintf("Unable to request DMA channel for SPI TX\n");
        r = -RT_EFULL;
        goto tx_dma_failed;
    }

    r = edma_alloc_slot(EDMA_CTLR(dma->tx_channel), EDMA_SLOT_ANY);
    if (r < 0) {
        rt_kprintf("Unable to request SPI TX DMA param slot\n");
        r = -RT_EFULL;
        goto param_failed;
    }
    dma->dummy_param_slot = r;
    edma_link(dma->dummy_param_slot, dma->dummy_param_slot);

    return 0;
param_failed:
    edma_free_channel(dma->tx_channel);
tx_dma_failed:
    edma_free_channel(dma->rx_channel);
rx_dma_failed:
    return r;
}

static rt_err_t configure(struct rt_spi_device *device,
                          struct rt_spi_configuration *configuration)
{
    return davinci_spi_setup_transfer(device, configuration);
}

static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    return davinci_spi_bufs(device, message);
};



static struct rt_spi_ops davinci_spi_ops =
{
    configure,
    xfer
};

static void udelay (volatile rt_uint32_t us)
{
    volatile rt_int32_t i;
    for (; us > 0; us--)
    {
        i = 5000;
        while(i > 0)
        {
            i--;
        }
    }
}

void spi_pin_cfg(void)
{
    rt_uint32_t val;

    val = davinci_readl(PINMUX3);
    val |= 0x80000000; /* SPI1 */
    davinci_writel(val, PINMUX3);

    val = davinci_readl(PINMUX4);
    val &= 0xffffffc0; /* SPI1 */
    val |= 0x05;//0x00000015; /* SPI1 */
    davinci_writel(val, PINMUX4);
}

/**
 * davinci_spi_probe - probe function for SPI Master Controller
 * @pdev: platform_device structure which contains plateform specific data
 *
 * According to Linux Device Model this function will be invoked by Linux
 * with platform_device struct which contains the device specific info.
 * This function will map the SPI controller's memory, register IRQ,
 * Reset SPI controller and setting its registers to default value.
 * It will invoke spi_bitbang_start to create work queue so that client driver
 * can register transfer method to work queue.
 */
static int davinci_spi_probe(struct davinci_spi *dspi, char *spi_bus_name)
{
    int i = 0, ret = 0;
    u32 spipc0;

    spi_pin_cfg();
    psc_change_state(DAVINCI_DM365_LPSC_SPI1, PSC_ENABLE);

    dspi->base = DM3XX_SPI1_BASE;//spi;

    dspi->irq = IRQ_DM3XX_SPINT1_0;

    rt_hw_interrupt_install(dspi->irq, davinci_spi_irq, dspi, spi_bus_name);
    rt_hw_interrupt_umask(dspi->irq);

    dspi->clk = clk_get("SPICLK");

    dspi->version = SPI_VERSION_1;
    dspi->chip_sel[0] = 29;//SPI_INTERN_CS;
    dspi->chip_sel[1] = 0;//GPIO0

    dspi->dma.rx_channel = 15;
    dspi->dma.tx_channel = 14;
    dspi->dma.eventq = EVENTQ_3;

    ret = davinci_spi_request_dma(dspi);
    if (ret)
        goto err;

    rt_kprintf("%s: DMA: supported\n", spi_bus_name);
    rt_kprintf("%s: DMA: RX channel: %d, TX channel: %d, "
            "event queue: %d\n", spi_bus_name, dspi->dma.rx_channel,
            dspi->dma.tx_channel, dspi->dma.eventq);

    dspi->get_rx = davinci_spi_rx_buf_u8;
    dspi->get_tx = davinci_spi_tx_buf_u8;

    rt_completion_init(&dspi->done);

    /* Reset In/OUT SPI module */
    writel(0, dspi->base + SPIGCR0);
    udelay(100);
    writel(1, dspi->base + SPIGCR0);

    /* Set up SPIPC0.  CS and ENA init is done in davinci_spi_setup */
    spipc0 = SPIPC0_DIFUN_MASK | SPIPC0_DOFUN_MASK | SPIPC0_CLKFUN_MASK;
    writel(spipc0, dspi->base + SPIPC0);

    /* initialize chip selects */
    for (i = 0; i < SPI_MAX_CHIPSELECT; i++) {
        if (dspi->chip_sel[i] != SPI_INTERN_CS)
            gpio_direction_output(dspi->chip_sel[i], 1);
    }

    if (0)
        writel(SPI_INTLVL_1, dspi->base + SPILVL);
    else
        writel(SPI_INTLVL_0, dspi->base + SPILVL);

    writel(CS_DEFAULT, dspi->base + SPIDEF);

    /* master mode default */
    set_io_bits(dspi->base + SPIGCR1, SPIGCR1_CLKMOD_MASK);
    set_io_bits(dspi->base + SPIGCR1, SPIGCR1_MASTER_MASK);
    set_io_bits(dspi->base + SPIGCR1, SPIGCR1_POWERDOWN_MASK);

    //set_io_bits(dspi->base + SPIGCR1, SPIGCR1_LOOPBACK_MASK);//LOOP BACK mode

    rt_kprintf("%s: Controller at 0x%p\n", spi_bus_name, dspi->base);

    dspi->parent.parent.user_data = dspi;

    return rt_spi_bus_register(&dspi->parent, spi_bus_name, &davinci_spi_ops);

    return ret;

free_dma:
    edma_free_channel(dspi->dma.tx_channel);
    edma_free_channel(dspi->dma.rx_channel);
    edma_free_slot(dspi->dma.dummy_param_slot);

err:
    return ret;
}


int rt_hw_spi_init(void)
{
    /* register spi bus */
    {
        static struct davinci_spi dspi;
        rt_memset(&dspi, 0, sizeof(dspi));
        davinci_spi_probe(&dspi, "spi1");
    }
    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        rt_spi_bus_attach_device(&spi_device, "spi10", "spi1", (void *)0);
    }
    {
        static struct rt_spi_device spi_device;
        rt_spi_bus_attach_device(&spi_device, "spi11", "spi1", (void *)1);
    }

    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_spi_init);

