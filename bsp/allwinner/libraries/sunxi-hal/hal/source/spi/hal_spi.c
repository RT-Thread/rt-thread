/*
 * Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY¡¯S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR
 * MPEGLA, ETC.)
 * IN ALLWINNERS¡¯SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT
 * TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY¡¯S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define DBG_LVL DBG_WARNING
#define DBG_TAG "hal.spi"

#include <stdio.h>
#include <stdlib.h>
#include <interrupt.h>
#include <sunxi_hal_spi.h>
#include <hal_cache.h>
#include <hal_mem.h>
#include <hal_osal.h>
#include <hal_log.h>
#include <hal_gpio.h>
#include <hal_dma.h>
#include <hal_reset.h>
#ifdef CONFIG_OS_MELIS
#include <hal_cfg.h>
#include <script.h>
#endif

#define SPI_ALIGN(x, a) __ALIGN_KERNEL((x), (a))
#define ALIGN_DOWN(x, a) __ALIGN_KERNEL((x) - ((a)-1), (a))
#define __ALIGN_KERNEL(x, a) __ALIGN_KERNEL_MASK(x, (typeof(x))(a)-1)
#define __ALIGN_KERNEL_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define MIN(a, b) (a > b ? b : a)

#if (0)
#define CONFIG_SUNXI_SPI_CPU_XFER_ONLY
#endif

#if (0)
#define SPI_INFO_LEVEL
#endif

#if (0)
#define SPI_DATA_LEVEL
#endif

#if (0)
#define SPI_DUMPREG_LEVEL
#endif

#ifdef SPI_INFO_LEVEL
#define SPI_INFO(fmt, arg...) LOG_I("%s()%d " fmt, __func__, __LINE__, ##arg)
#define SPI_INFO_IRQ(fmt, arg...) LOG_I("%s()%d " fmt, __func__, __LINE__, ##arg)
#define SPI_ERR(fmt, arg...) LOG_E("%s()%d " fmt, __func__, __LINE__, ##arg)
#define SPI_INIT(fmt, arg...) LOG_I("%s()%d " fmt, __func__, __LINE__, ##arg)
#else
#define SPI_INFO(fmt, arg...) \
    do                        \
    {                         \
    } while (0);
#define SPI_INFO_IRQ(fmt, arg...) \
    do                            \
    {                             \
    } while (0);
#define SPI_ERR(fmt, arg...) \
    do                       \
    {                        \
    } while (0);
#define SPI_INIT(fmt, arg...) \
    do                        \
    {                         \
    } while (0);
#endif

static sunxi_spi_t g_sunxi_spi[HAL_SPI_MASTER_MAX];
struct sunxi_spi_params_t g_sunxi_spi_params[] = {
    SPI0_PARAMS,
    SPI1_PARAMS,
#ifdef SPI2_PARAMS
    SPI2_PARAMS,
#endif
};

void spi_dump_reg(sunxi_spi_t *sspi, uint32_t offset, uint32_t len)
{
    uint32_t i;
    uint8_t buf[64], cnt = 0;

    for (i = 0; i < len; i = i + REG_INTERVAL)
    {
        if (i % HEXADECIMAL == 0)
            cnt += sprintf(buf + cnt, "0x%08lx: ",
                           (unsigned long)(sspi->base + offset + i));

        cnt += sprintf(buf + cnt, "%08lx ",
                       (unsigned long)hal_readl(sspi->base + offset + i));

        if (i % HEXADECIMAL == REG_CL)
        {
            rt_kprintf("%s\n", buf);
            cnt = 0;
        }
    }
}

/* config chip select */
static spi_master_status_t spi_set_cs(hal_spi_master_slave_port_t chipselect, sunxi_spi_t *sspi)
{
    spi_master_status_t ret;
    uint32_t reg_val = hal_readl(sspi->base + SPI_TC_REG);

    if (chipselect < 4)
    {
        reg_val &= ~SPI_TC_SS_MASK; /* SS-chip select, clear two bits */
        reg_val |= chipselect
                   << SPI_TC_SS_BIT_POS; /* set chip select */
        hal_writel(reg_val, sspi->base + SPI_TC_REG);
        ret = SPI_MASTER_OK;
    }
    else
    {
        SPI_ERR("[spi%d] Chip Select set fail! cs = %d\n", sspi->port,
                chipselect);
        ret = SPI_MASTER_INVALID_PARAMETER;
    }

    return ret;
}

static void spi_config_dhb(sunxi_spi_t *sspi, uint8_t value)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_TC_REG);

    /*6.discard hash burst-DHB */
    if (value)
    {
        reg_val &= ~SPI_TC_DHB;
    }
    else
    {
        reg_val |= SPI_TC_DHB; /*default DHB =1, discard unused burst */
    }

    hal_writel(reg_val, sspi->base + SPI_TC_REG);
}

/* config spi */
static void spi_config_tc(uint32_t config, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_TC_REG);

    /*1. POL */
    if (config & SPI_POL_ACTIVE_)
    {
        reg_val |= SPI_TC_POL; /*default POL = 1 */
    }
    else
    {
        reg_val &= ~SPI_TC_POL;
    }

    /*2. PHA */
    if (config & SPI_PHA_ACTIVE_)
    {
        reg_val |= SPI_TC_PHA; /*default PHA = 1 */
    }
    else
    {
        reg_val &= ~SPI_TC_PHA;
    }

    /*3. SSPOL,chip select signal polarity */
    if (config & SPI_CS_HIGH_ACTIVE_)
    {
        reg_val &= ~SPI_TC_SPOL;
    }
    else
    {
        reg_val |= SPI_TC_SPOL; /*default SSPOL = 1,Low level effect */
    }

    /*4. LMTF--LSB/MSB transfer first select */
    if (config & SPI_LSB_FIRST_ACTIVE_)
    {
        reg_val |= SPI_TC_FBS;
    }
    else
    {
        reg_val &= ~SPI_TC_FBS; /*default LMTF =0, MSB first */
    }

    /* set DDB,DHB,SMC,SSCTL */
    /*5. dummy burst type */
    if (config & SPI_DUMMY_ONE_ACTIVE_)
    {
        reg_val |= SPI_TC_DDB;
    }
    else
    {
        reg_val &= ~SPI_TC_DDB; /*default DDB =0, ZERO */
    }

    /*6.discard hash burst-DHB */
    if (config & SPI_RECEIVE_ALL_ACTIVE_)
    {
        reg_val &= ~SPI_TC_DHB;
    }
    else
    {
        reg_val |= SPI_TC_DHB; /*default DHB =1, discard unused burst */
    }

    /*7. set SMC = 1 , SSCTL = 0 ,TPE = 1 */
    reg_val &= ~SPI_TC_SSCTL;

    hal_writel(reg_val, sspi->base + SPI_TC_REG);
}

/* delay internal read sample point*/
static void spi_sample_delay(uint32_t sdm, uint32_t sdc, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_TC_REG);
    uint32_t org_val = reg_val;

    if (sdm)
    {
        reg_val |= SPI_TC_SDM;
    }
    else
    {
        reg_val &= ~SPI_TC_SDM;
    }

    if (sdc)
    {
        reg_val |= SPI_TC_SDC;
    }
    else
    {
        reg_val &= ~SPI_TC_SDC;
    }

    if (reg_val != org_val)
    {
        hal_writel(reg_val, sspi->base + SPI_TC_REG);
    }
}

/* start spi transfer */
static void spi_start_xfer(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_TC_REG);

    reg_val |= SPI_TC_XCH;
    hal_writel(reg_val, sspi->base + SPI_TC_REG);
}

/* enable spi bus */
static void spi_enable_bus(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_GC_REG);

    reg_val |= SPI_GC_EN;
    hal_writel(reg_val, sspi->base + SPI_GC_REG);
}

/* disbale spi bus */
static void spi_disable_bus(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_GC_REG);

    reg_val &= ~SPI_GC_EN;
    hal_writel(reg_val, sspi->base + SPI_GC_REG);
}

/* set master mode */
static void spi_set_master(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_GC_REG);

    reg_val |= SPI_GC_MODE;
    hal_writel(reg_val, sspi->base + SPI_GC_REG);
}

/* soft reset spi controller */
static void spi_soft_reset(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_GC_REG);

    reg_val |= SPI_GC_SRST;
    hal_writel(reg_val, sspi->base + SPI_GC_REG);
}

/* enable transmit pause */
static void spi_enable_tp(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_GC_REG);

    reg_val |= SPI_GC_TP_EN;
    hal_writel(reg_val, sspi->base + SPI_GC_REG);
}

/* set ss control */
static void spi_ss_owner(sunxi_spi_t *sspi, uint32_t on_off)
{
    u32 reg_val = hal_readl(sspi->base + SPI_TC_REG);

    on_off &= 0x1;
    if (on_off)
    {
        reg_val |= SPI_TC_SS_OWNER;
    }
    else
    {
        reg_val &= ~SPI_TC_SS_OWNER;
    }
    hal_writel(reg_val, sspi->base + SPI_TC_REG);
}

/* enable irq type */
static void spi_enable_irq(uint32_t bitmap, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_INT_CTL_REG);

    bitmap &= SPI_INTEN_MASK;
    reg_val |= bitmap;
    hal_writel(reg_val, sspi->base + SPI_INT_CTL_REG);
}

/* disable irq type */
static void spi_disable_irq(uint32_t bitmap, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_INT_CTL_REG);

    bitmap &= SPI_INTEN_MASK;
    reg_val &= ~bitmap;
    hal_writel(reg_val, sspi->base + SPI_INT_CTL_REG);
}

/* enable dma irq */
static void spi_enable_dma_irq(uint32_t bitmap, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_FIFO_CTL_REG);

    bitmap &= SPI_FIFO_CTL_DRQEN_MASK;
    reg_val |= bitmap;
    hal_writel(reg_val, sspi->base + SPI_FIFO_CTL_REG);
}

/* disable dma irq */
static void spi_disable_dma_irq(uint32_t bitmap, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_FIFO_CTL_REG);

    bitmap &= SPI_FIFO_CTL_DRQEN_MASK;
    reg_val &= ~bitmap;
    hal_writel(reg_val, sspi->base + SPI_FIFO_CTL_REG);
}

/* query irq enable */
static uint32_t spi_qry_irq_enable(sunxi_spi_t *sspi)
{
    return (SPI_INTEN_MASK & hal_readl(sspi->base + SPI_INT_CTL_REG));
}

/* query irq pending */
static uint32_t spi_qry_irq_pending(sunxi_spi_t *sspi)
{
    return (SPI_INT_STA_MASK & hal_readl(sspi->base + SPI_INT_STA_REG));
}

/* clear irq pending */
static void spi_clr_irq_pending(uint32_t pending_bit, sunxi_spi_t *sspi)
{
    pending_bit &= SPI_INT_STA_MASK;
    hal_writel(pending_bit, sspi->base + SPI_INT_STA_REG);
}

/* query txfifo bytes */
static uint32_t spi_query_txfifo(sunxi_spi_t *sspi)
{
    uint32_t reg_val =
        (SPI_FIFO_STA_TX_CNT & hal_readl(sspi->base + SPI_FIFO_STA_REG));

    reg_val >>= SPI_TXCNT_BIT_POS;
    return reg_val;
}

/* query rxfifo bytes */
static uint32_t spi_query_rxfifo(sunxi_spi_t *sspi)
{
    uint32_t reg_val =
        (SPI_FIFO_STA_RX_CNT & hal_readl(sspi->base + SPI_FIFO_STA_REG));

    reg_val >>= SPI_RXCNT_BIT_POS;
    return reg_val;
}

/* reset fifo */
static void spi_reset_fifo(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_FIFO_CTL_REG);

    reg_val |= (SPI_FIFO_CTL_RX_RST | SPI_FIFO_CTL_TX_RST);
    /* Set the trigger level of RxFIFO/TxFIFO. */
    reg_val &= ~(SPI_FIFO_CTL_RX_LEVEL | SPI_FIFO_CTL_TX_LEVEL);
    reg_val |= (0x20 << 16) | 0x20;
    hal_writel(reg_val, sspi->base + SPI_FIFO_CTL_REG);
}

static void spi_set_rx_trig(uint32_t val, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_FIFO_CTL_REG);

    reg_val &= ~SPI_FIFO_CTL_RX_LEVEL;
    reg_val |= val & SPI_FIFO_CTL_RX_LEVEL;
    hal_writel(reg_val, sspi->base + SPI_FIFO_CTL_REG);
}

static void spi_set_tx_trig(uint32_t val, sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_FIFO_CTL_REG);

    reg_val &= ~SPI_FIFO_CTL_TX_LEVEL;
    reg_val |= (val << 16) & SPI_FIFO_CTL_TX_LEVEL;
    hal_writel(reg_val, sspi->base + SPI_FIFO_CTL_REG);
}

/* set transfer total length BC, transfer length TC and single transmit length
 * STC */
static void spi_set_bc_tc_stc(uint32_t tx_len, uint32_t rx_len,
                              uint32_t stc_len, uint32_t dummy_cnt,
                              sunxi_spi_t *sspi)
{
    uint32_t reg_val;

    /* set MBC(0x30) = tx_len + rx_len + dummy_cnt */
    reg_val = hal_readl(sspi->base + SPI_BURST_CNT_REG);
    reg_val &= ~SPI_BC_CNT_MASK;
    reg_val |= (SPI_BC_CNT_MASK & (rx_len + dummy_cnt));
    hal_writel(reg_val, sspi->base + SPI_BURST_CNT_REG);

    /* set MTC(0x34) = tx_len */
    reg_val = hal_readl(sspi->base + SPI_TRANSMIT_CNT_REG);
    reg_val &= ~SPI_TC_CNT_MASK;
    reg_val |= (SPI_TC_CNT_MASK & tx_len);
    hal_writel(reg_val, sspi->base + SPI_TRANSMIT_CNT_REG);

    /* set BBC(0x38) = dummy cnt & single mode transmit counter */
    reg_val = hal_readl(sspi->base + SPI_BCC_REG);
    reg_val &= ~SPI_BCC_STC_MASK;
    reg_val |= (SPI_BCC_STC_MASK & stc_len);
    reg_val &= ~(0xf << 24);
    reg_val |= (dummy_cnt << 24);
    hal_writel(reg_val, sspi->base + SPI_BCC_REG);
}

/* set ss control */
static void spi_ss_ctrl(sunxi_spi_t *sspi, uint8_t on_off)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_TC_REG);

    on_off &= 0x1;
    if (on_off)
    {
        reg_val |= SPI_TC_SS_LEVEL;
    }
    else
    {
        reg_val &= ~SPI_TC_SS_LEVEL;
    }
    hal_writel(reg_val, sspi->base + SPI_TC_REG);
}

static void spi_disable_dual(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_BCC_REG);
    reg_val &= ~SPI_BCC_DUAL_MODE;
    hal_writel(reg_val, sspi->base + SPI_BCC_REG);
}

static void spi_enable_dual(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_BCC_REG);
    reg_val &= ~SPI_BCC_QUAD_MODE;
    reg_val |= SPI_BCC_DUAL_MODE;
    hal_writel(reg_val, sspi->base + SPI_BCC_REG);
}

static void spi_disable_quad(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_BCC_REG);

    reg_val &= ~SPI_BCC_QUAD_MODE;
    hal_writel(reg_val, sspi->base + SPI_BCC_REG);
}

static void spi_enable_quad(sunxi_spi_t *sspi)
{
    uint32_t reg_val = hal_readl(sspi->base + SPI_BCC_REG);

    reg_val |= SPI_BCC_QUAD_MODE;
    hal_writel(reg_val, sspi->base + SPI_BCC_REG);
}

static spi_master_status_t spi_mode_check(sunxi_spi_t *sspi)
{
    uint32_t flags = 0;

    if (sspi->mode_type != MODE_TYPE_NULL)
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

    /* full duplex */
    if (sspi->transfer->tx_buf && sspi->transfer->rx_buf)
    {
        spi_set_bc_tc_stc(sspi->transfer->tx_len,
                          sspi->transfer->rx_len,
                          sspi->transfer->tx_single_len,
                          sspi->transfer->dummy_byte, sspi);
        sspi->mode_type = FULL_DUPLEX_TX_RX;

        if (sspi->transfer->rx_nbits == SPI_NBITS_QUAD)
        {
            spi_disable_dual(sspi);
            spi_enable_quad(sspi);
            SPI_INFO("[spi%d] Quad mode Full duplex tx rx\n",
                     sspi->port);
        }
        else if (sspi->transfer->rx_nbits == SPI_NBITS_DUAL)
        {
            spi_disable_quad(sspi);
            spi_enable_dual(sspi);
            SPI_INFO("[spi%d] Dual mode Full duplex tx rx\n",
                     sspi->port);
        }
        else
        {
            spi_disable_quad(sspi);
            spi_disable_dual(sspi);
            SPI_INFO("[spi%d] Single mode Full duplex tx rx\n",
                     sspi->port);
        }
    } /* half duplex transmit */
    else if (sspi->transfer->tx_buf)
    {
        if (sspi->transfer->tx_nbits == SPI_NBITS_QUAD)
        {
            spi_disable_dual(sspi);
            spi_enable_quad(sspi);
            spi_set_bc_tc_stc(sspi->transfer->tx_len, sspi->transfer->tx_len,
                              sspi->transfer->tx_single_len,
                              sspi->transfer->dummy_byte, sspi);
            sspi->mode_type = QUAD_HALF_DUPLEX_TX;
            SPI_INFO("[spi%d] Quad mode Half duplex tx\n",
                     sspi->port);
        }
        else if (sspi->transfer->tx_nbits == SPI_NBITS_DUAL)
        {
            spi_disable_quad(sspi);
            spi_enable_dual(sspi);
            spi_set_bc_tc_stc(sspi->transfer->tx_len, sspi->transfer->tx_len,
                              sspi->transfer->tx_single_len,
                              sspi->transfer->dummy_byte, sspi);
            sspi->mode_type = DUAL_HALF_DUPLEX_TX;
            SPI_INFO("[spi%d] Dual mode Half duplex tx\n",
                     sspi->port);
        }
        else
        {
            spi_disable_quad(sspi);
            spi_disable_dual(sspi);
            spi_set_bc_tc_stc(sspi->transfer->tx_len, sspi->transfer->tx_len,
                              sspi->transfer->tx_len,
                              sspi->transfer->dummy_byte, sspi);
            sspi->mode_type = SGLE_HALF_DUPLEX_TX;
            SPI_INFO("[spi%d] Single mode Half duplex tx\n",
                     sspi->port);
        }
    } /* half duplex receive */
    else if (sspi->transfer->rx_buf)
    {
        if (sspi->transfer->rx_nbits == SPI_NBITS_QUAD)
        {
            spi_disable_dual(sspi);
            spi_enable_quad(sspi);
            sspi->mode_type = QUAD_HALF_DUPLEX_RX;
            SPI_INFO("[spi%d] Quad mode Half duplex rx\n",
                     sspi->port);
        }
        else if (sspi->transfer->rx_nbits == SPI_NBITS_DUAL)
        {
            spi_disable_quad(sspi);
            spi_enable_dual(sspi);
            sspi->mode_type = DUAL_HALF_DUPLEX_RX;
            SPI_INFO("[spi%d] Dual mode Half duplex rx\n",
                     sspi->port);
        }
        else
        {
            spi_disable_quad(sspi);
            spi_disable_dual(sspi);
            sspi->mode_type = SGLE_HALF_DUPLEX_RX;
            SPI_INFO("[spi%d] Single mode Half duplex rx\n",
                     sspi->port);
        }
        spi_set_bc_tc_stc(0, sspi->transfer->rx_len, 0,
                          sspi->transfer->dummy_byte, sspi);
    }

    return SPI_MASTER_OK;
}

static spi_master_status_t spi_cpu_write(sunxi_spi_t *sspi)
{
    uint32_t flags = 0;
    uint32_t len = sspi->transfer->tx_len;
    const uint8_t *buf = sspi->transfer->tx_buf;
    volatile int32_t poll_time;
#ifdef SPI_DATA_LEVEL
    uint32_t i, j;
    uint8_t dbuf[64], cnt = 0;
#endif

    if (NULL == buf)
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

#ifdef SPI_DUMPREG_LEVEL
    SPI_INFO("[spi%d] dump reg:\n", sspi->port);
    spi_dump_reg(sspi, 0, 0x60);
#endif

#ifdef SPI_DATA_LEVEL
    SPI_INFO("tx_len = %d\n", len);
    for (i = 0; i < len; i += 16)
    {
        cnt = 0;
        cnt += sprintf(dbuf + cnt, "%04x: ", i);
        for (j = 0; ((i + j) < len) && (j < 16); j++)
            cnt += sprintf(dbuf + cnt, "%02x ",
                           ((uint8_t *)(buf))[i + j]);
        printf("%s\n", dbuf);
    }
#endif

    for (; len > 0; --len)
    {
        poll_time = 0xFFFFFF;
        while ((spi_query_txfifo(sspi) >= MAX_FIFU) && poll_time--)
            ;
        if (poll_time <= 0)
        {
            SPI_ERR("[spi%d] cpu transfer data time out!\n",
                    sspi->port);
            SPI_INFO("[spi%d] dump reg:\n", sspi->port);
            spi_dump_reg(sspi, 0, 0x60);
            return SPI_MASTER_ERROR_TIMEOUT;
        }

        hal_writeb(*buf++, sspi->base + SPI_TXDATA_REG);
    }

    return SPI_MASTER_OK;
}

static spi_master_status_t spi_cpu_read(sunxi_spi_t *sspi)
{
    uint32_t flags = 0;
    uint32_t len = sspi->transfer->rx_len;
    uint8_t *buf = sspi->transfer->rx_buf;
    volatile int32_t poll_time;
    uint32_t n;

#ifdef SPI_DATA_LEVEL
    uint32_t i, j;
    uint8_t dbuf[64], cnt = 0;
#endif

    if (NULL == buf)
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

#ifdef SPI_DUMPREG_LEVEL
    SPI_INFO("[spi%d] dump reg:\n", sspi->port);
    spi_dump_reg(sspi, 0, 0x60);
#endif

    for (n = 0; n < len; n++)
    {
        poll_time = 0xFFFFFF;
        while (!spi_query_rxfifo(sspi) && poll_time--)
        {
        }
        if (poll_time <= 0)
        {
            SPI_ERR("[spi%d] cpu receive data time out!\n",
                    sspi->port);
            SPI_INFO("[spi%d] dump reg:\n", sspi->port);
            spi_dump_reg(sspi, 0, 0x60);
            return SPI_MASTER_ERROR_TIMEOUT;
        }

        *(buf + n) = hal_readb(sspi->base + SPI_RXDATA_REG);
    }

#ifdef SPI_DATA_LEVEL
    SPI_INFO("rx_len = %d\n", len);
    for (i = 0; i < len; i += 16)
    {
        cnt = 0;
        cnt += sprintf(dbuf + cnt, "%04x: ", i);
        for (j = 0; ((i + j) < len) && (j < 16); j++)
            cnt += sprintf(dbuf + cnt, "%02x ",
                           ((uint8_t *)(buf))[i + j]);
        printf("%s\n", dbuf);
    }
#endif

    return SPI_MASTER_OK;
}

#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
static spi_master_status_t spi_dma_tx_config(struct sunxi_spi *sspi)
{
    hal_dma_chan_status_t ret;
    uint32_t flags = 0;
    uint32_t len = sspi->transfer->tx_len;
    uint8_t const *buf = sspi->transfer->tx_buf;
    struct dma_slave_config *config = &sspi->dma_tx.config;

#ifdef SPI_DATA_LEVEL
    unsigned int i, j;
    u8 dbuf[64], cnt = 0;
#endif

    if (NULL == buf)
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

    if (len <= ALIGN_DMA_BUF_SIZE)
    {
        memcpy(sspi->align_dma_buf, buf, len);
        buf = sspi->align_dma_buf;
    }
    else
    {
        SPI_ERR("[spi%d] tx size over dma align buf size\n",
                sspi->port);
        /* buffer on DMA must align to cache line */
        if ((unsigned long)buf & (64 - 1) || len & (64 - 1))
        {
            SPI_ERR("[spi%d] tx buf or len not align to 64\n",
                    sspi->port);
            return SPI_MASTER_INVALID_PARAMETER;
        }
    }
    hal_dcache_clean((unsigned long)buf, SPI_ALIGN(len, 64));

#ifdef SPI_DATA_LEVEL
    SPI_INFO("tx_len = %d\n", len);
    for (i = 0; i < len; i += 16)
    {
        cnt = 0;
        cnt += sprintf(dbuf + cnt, "%03x: ", i);
        for (j = 0; ((i + j) < len) && (j < 16); j++)
            cnt += sprintf(dbuf + cnt, "%02x ",
                           ((uint8_t *)(buf))[i + j]);
        printf("%s\n", dbuf);
    }
#endif

    ret = hal_dma_chan_request(&sspi->dma_tx.chan);
    if (ret == HAL_DMA_CHAN_STATUS_BUSY)
    {
        SPI_ERR("[spi%d] request dma_rx failed\n", sspi->port);
        return SPI_MASTER_ERROR;
    }

    spi_set_tx_trig(0x20, sspi);
    spi_enable_dma_irq(SPI_FIFO_CTL_TX_DRQEN, sspi);

#ifdef SPI_DUMPREG_LEVEL
    SPI_INFO("[spi%d] dump reg:\n", sspi->port);
    spi_dump_reg(sspi, 0, 0x60);
#endif

    config->direction = DMA_MEM_TO_DEV;
    config->dst_addr = sspi->base + SPI_TXDATA_REG;
    config->src_addr = (unsigned long)buf;

    if (len % DMA_SLAVE_BUSWIDTH_4_BYTES)
    {
        config->src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        config->dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        config->dst_maxburst = DMA_SLAVE_BURST_16;
        config->src_maxburst = DMA_SLAVE_BURST_16;
    }
    else
    {
        config->src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
        config->dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
        config->dst_maxburst = DMA_SLAVE_BURST_8;
        config->src_maxburst = DMA_SLAVE_BURST_8;
    }

    config->slave_id =
        sunxi_slave_id(SUNXI_SPI_DRQ_TX(sspi->port), DRQSRC_SDRAM);

    SPI_INFO("[spi%d] config:\n"
             "  direction: %d\n"
             "  src_addr: 0x%08lx,"
             "  dst_addr: 0x%08lx\n"
             "  src_addr_width: %d,"
             "  dst_addr_width: %d\n"
             "  src_maxburst: %lu,"
             "  dst_maxburst: %lu\n"
             "  slave_id: 0x%08lx\n",
             sspi->port, config->direction, config->src_addr,
             config->dst_addr, config->src_addr_width,
             config->dst_addr_width, config->src_maxburst,
             config->dst_maxburst, config->slave_id);

    return SPI_MASTER_OK;
}

#ifdef SPI_INFO_LEVEL
static void spi_dma_tx_callback(void *para)
{
    sunxi_spi_t *sspi = (sunxi_spi_t *)para;
    SPI_INFO("[spi%d] DMA TX callback function\n", sspi->port);
}
#endif

static spi_master_status_t spi_dma_tx_submit(struct sunxi_spi *sspi)
{
    hal_dma_status_t ret;
    uint32_t len = sspi->transfer->tx_len;
    struct dma_slave_config *config = &sspi->dma_tx.config;
    struct sunxi_dma_chan *chan = sspi->dma_tx.chan;

    ret = hal_dma_slave_config(chan, config);
    if (ret)
    {
        SPI_ERR("[spi%d] dma slave config failed! return %d\n",
                sspi->port, ret);
        return SPI_MASTER_ERROR;
    }

    ret = hal_dma_prep_device(chan, config->dst_addr, config->src_addr, len,
                              config->direction);
    if (ret)
    {
        SPI_ERR("[spi%d] dma prep device failed! return %d\n",
                sspi->port, ret);
        return SPI_MASTER_ERROR;
    }

#ifdef SPI_INFO_LEVEL
    chan->callback = spi_dma_tx_callback;
    chan->callback_param = sspi;
#endif

    ret = hal_dma_start(chan);
    if (ret)
    {
        SPI_ERR("[spi%d] dma start error! return %d\n", sspi->port,
                ret);
        return SPI_MASTER_ERROR;
    }

    return SPI_MASTER_OK;
}

static void spi_dma_rx_callback(void *para)
{
    sunxi_spi_t *sspi = (sunxi_spi_t *)para;

    if (hal_sem_post(sspi->xSemaphore_rx))
    {
        SPI_ERR("[spi%d] xSemaphoreGive failed.\n", sspi->port);
    }
}

static spi_master_status_t spi_dma_rx_config(struct sunxi_spi *sspi)
{
    hal_dma_chan_status_t ret;
    uint32_t flags = 0;
    uint32_t len = sspi->transfer->rx_len, size = 0;
    uint8_t *buf = sspi->transfer->rx_buf;
    struct dma_slave_config *config = &sspi->dma_rx.config;

    if (NULL == buf)
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

    if (len <= ALIGN_DMA_BUF_SIZE)
    {
        buf = sspi->align_dma_buf;
        memset(buf, 0, ALIGN_DMA_BUF_SIZE);
    }
    else
    {
        SPI_ERR("[spi%d] rx size over dma align buf size\n",
                sspi->port);
        /* buffer on DMA must align to cache line */
        if ((unsigned long)buf & (64 - 1) || len & (64 - 1))
        {
            SPI_ERR("[spi%d] rx buf or len not align to 64\n",
                    sspi->port);
            return SPI_MASTER_INVALID_PARAMETER;
        }
    }
    hal_dcache_clean_invalidate((unsigned long)buf, SPI_ALIGN(len, 64));
    spi_enable_dma_irq(SPI_FIFO_CTL_RX_DRQEN, sspi);

#ifdef SPI_DUMPREG_LEVEL
    SPI_INFO("[spi%d] dump reg:\n", sspi->port);
    spi_dump_reg(sspi, 0, 0x60);
#endif

    ret = hal_dma_chan_request(&sspi->dma_rx.chan);
    if (ret == HAL_DMA_CHAN_STATUS_BUSY)
    {
        SPI_ERR("[spi%d] request dma_rx failed\n", sspi->port);
        return SPI_MASTER_ERROR;
    }

    config->direction = DMA_DEV_TO_MEM;
    config->dst_addr = (unsigned long)buf;
    config->src_addr = sspi->base + SPI_RXDATA_REG;

    if (len % DMA_SLAVE_BUSWIDTH_4_BYTES)
    {
        config->src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        config->dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
        config->dst_maxburst = DMA_SLAVE_BURST_16;
        config->src_maxburst = DMA_SLAVE_BURST_16;
    }
    else
    {
        config->src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
        config->dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
        config->dst_maxburst = DMA_SLAVE_BURST_8;
        config->src_maxburst = DMA_SLAVE_BURST_8;
    }

    config->slave_id =
        sunxi_slave_id(DRQDST_SDRAM, SUNXI_SPI_DRQ_RX(sspi->port));

    SPI_INFO("[spi%d] config:\n"
             "  direction: %d\n"
             "  src_addr: 0x%08lx,"
             "  dst_addr: 0x%08lx\n"
             "  src_addr_width: %d,"
             "  dst_addr_width: %d\n"
             "  src_maxburst: %lu,"
             "  dst_maxburst: %lu\n"
             "  slave_id: 0x%08lx\n",
             sspi->port, config->direction, config->src_addr,
             config->dst_addr, config->src_addr_width,
             config->dst_addr_width, config->src_maxburst,
             config->dst_maxburst, config->slave_id);

    return SPI_MASTER_OK;
}

static spi_master_status_t spi_dma_rx_submit(struct sunxi_spi *sspi)
{
    hal_dma_status_t ret;
    uint32_t flags = 0;
    uint32_t len = sspi->transfer->rx_len, size = 0;
    struct sunxi_dma_chan *chan = sspi->dma_rx.chan;
    struct dma_slave_config *config = &sspi->dma_rx.config;

    ret = hal_dma_slave_config(chan, config);
    if (ret)
    {
        SPI_ERR("[spi%d] dma slave config failed! return %d\n",
                sspi->port, ret);
        return SPI_MASTER_ERROR;
    }

    ret = hal_dma_prep_device(chan, config->dst_addr, config->src_addr, len,
                              config->direction);
    if (ret)
    {
        SPI_ERR("[spi%d] dma prep device failed! return %d\n",
                sspi->port, ret);
        return SPI_MASTER_ERROR;
    }

    chan->callback = spi_dma_rx_callback;
    chan->callback_param = sspi;

    ret = hal_dma_start(chan);
    if (ret)
    {
        SPI_ERR("[spi%d] dma start error! return %d\n", sspi->port,
                ret);
        return SPI_MASTER_ERROR;
    }

    return SPI_MASTER_OK;
}

#endif

static spi_master_status_t spi_transfer(sunxi_spi_t *sspi)
{
    spi_config_dhb(sspi, 1);

    switch (sspi->mode_type)
    {
    case SGLE_HALF_DUPLEX_RX:
    case DUAL_HALF_DUPLEX_RX:
    case QUAD_HALF_DUPLEX_RX:
    {
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        /* >64 use DMA transfer, or use cpu */
        if (sspi->transfer->rx_len > BULK_DATA_BOUNDARY)
        {
            SPI_INFO("[spi%d] rx by dma\n", sspi->port);
            /* For Rx mode, the DMA end(not TC flag) is real end. */
            spi_disable_irq(SPI_INTEN_TC, sspi);
            if (spi_dma_rx_config(sspi))
            {
                return SPI_MASTER_ERROR;
            }
            if (spi_dma_rx_submit(sspi))
            {
                return SPI_MASTER_ERROR;
            }
            spi_start_xfer(sspi);
        }
        else
        {
#endif
            SPI_INFO("[spi%d] rx by cpu\n", sspi->port);
            spi_clr_irq_pending(SPI_INT_STA_MASK, sspi);
            spi_start_xfer(sspi);
            spi_cpu_read(sspi);
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        }
#endif
        break;
    }
    case SGLE_HALF_DUPLEX_TX:
    case DUAL_HALF_DUPLEX_TX:
    case QUAD_HALF_DUPLEX_TX:
    {
        spi_config_dhb(sspi, 0);
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        /* >64 use DMA transfer, or use cpu */
        if (sspi->transfer->tx_len > BULK_DATA_BOUNDARY)
        {
            SPI_INFO("[spi%d] tx by dma\n", sspi->port);
            sspi->sem = 1;
            spi_start_xfer(sspi);
            if (spi_dma_tx_config(sspi))
            {
                return SPI_MASTER_ERROR;
            }
            if (spi_dma_tx_submit(sspi))
            {
                return SPI_MASTER_ERROR;
            }
        }
        else
        {
#endif
            SPI_INFO("[spi%d] tx by cpu\n", sspi->port);
            spi_start_xfer(sspi);
            spi_cpu_write(sspi);
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        }
#endif
        break;
    }
    case FULL_DUPLEX_TX_RX:
    {
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        /* >64 use DMA transfer, or use cpu */
        if (sspi->transfer->rx_len > BULK_DATA_BOUNDARY)
        {
            SPI_INFO("[spi%d] tx and rx by dma\n", sspi->port);
            /* For Rx mode, the DMA end(not TC flag) is real end. */
            spi_disable_irq(SPI_INTEN_TC, sspi);
            spi_start_xfer(sspi);
            if (spi_dma_rx_config(sspi))
            {
                return SPI_MASTER_ERROR;
            }
            if (spi_dma_rx_submit(sspi))
            {
                return SPI_MASTER_ERROR;
            }
            spi_cpu_write(sspi);
        }
        else
        {
#endif
            SPI_INFO("[spi%d] tx and rx by cpu\n", sspi->port);
            spi_start_xfer(sspi);
            spi_cpu_write(sspi);
            spi_cpu_read(sspi);
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        }
#endif
        break;
    }
    default:
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }
    }

    return SPI_MASTER_OK;
}

/* wake up the sleep thread, and give the result code */
static irqreturn_t spi_irq_handler(int irq, void *ptr)
{
    uint32_t flags = 0;
    uint32_t status = 0, enable = 0;
    sunxi_spi_t *sspi = (sunxi_spi_t *)ptr;

    enable = spi_qry_irq_enable(sspi);
    status = spi_qry_irq_pending(sspi);
    spi_clr_irq_pending(status, sspi);

    sspi->result = SPI_XFER_OK;

    /* master mode, Transfer Complete Interrupt */
    if (status & SPI_INT_STA_TC)
    {
        SPI_INFO_IRQ("[spi%d] SPI TC COME\n", sspi->port);
        spi_disable_irq(SPI_INT_STA_TC | SPI_INT_STA_ERR, sspi);
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        if (sspi->sem)
        {
            sspi->sem = 0;
            if (hal_sem_post(sspi->xSemaphore_tx))
                SPI_INFO_IRQ("[spi%d] xSemaphorePostFromISR failed.\n",
                             sspi->port);
        }
#endif
        return 0;
    }
    else if (status & SPI_INT_STA_ERR) /* master mode:err */
    {
        SPI_INFO_IRQ("[spi%d]  SPI ERR! status %#lx\n", sspi->port, status);
        /* __log("[spi%d] dump reg:\n", sspi->port); */
        /* spi_dump_reg(sspi, 0, 0x60); */
        spi_disable_irq(SPI_INT_STA_TC | SPI_INT_STA_ERR, sspi);
        sspi->result = SPI_XFER_FAILED;
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        if (sspi->sem)
        {
            sspi->sem = 0;
            if (hal_sem_post(sspi->xSemaphore_tx))
                SPI_INFO_IRQ("[spi%d] xSemaphorePostFromISR failed.\n",
                             sspi->port);
        }
#endif
        return 0;
    }
    return 0;
}

static spi_master_status_t spi_pinctrl_init(sunxi_spi_t *sspi)
{
#ifdef CONFIG_OS_MELIS
    user_gpio_set_t gpio_cfg[6] = {0};
    gpio_pin_t spi_pin[6];
    gpio_muxsel_t spi_muxsel[6];
    int count, i;
    char spi_name[16];
    int ret = SPI_MASTER_OK;

    if (sspi->port >= HAL_SPI_MASTER_MAX)
    {
        SPI_ERR("[spi%d] invalid port\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

    sprintf(spi_name, "spi%d", sspi->port);
    count = Hal_Cfg_GetGPIOSecKeyCount(spi_name);
    if (!count)
    {
        SPI_ERR("[spi%d] not support in sys_config\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }
    Hal_Cfg_GetGPIOSecData(spi_name, gpio_cfg, count);

    for (i = 0; i < count; i++)
    {
        spi_pin[i] = (gpio_cfg[i].port - 1) * 32 + gpio_cfg[i].port_num;
        spi_muxsel[i] = gpio_cfg[i].mul_sel;
        ret = hal_gpio_pinmux_set_function(spi_pin[i], spi_muxsel[i]);
        if (ret)
        {
            SPI_ERR("[spi%d] PIN%u set function failed! return %d\n",
                    sspi->port, spi_pin[i], ret);
            return SPI_MASTER_ERROR;
        }
        ret = hal_gpio_set_driving_level(spi_pin[i], gpio_cfg[i].drv_level);
        if (ret)
        {
            SPI_ERR("[spi%d] PIN%u set driving level failed! return %d\n",
                    sspi->port, gpio_cfg[i].drv_level, ret);
            return SPI_MASTER_ERROR;
        }
        if (gpio_cfg[i].pull)
        {
            ret = hal_gpio_set_pull(spi_pin[i], gpio_cfg[i].pull);
        }
    }

    return ret;
#else
    SPI_ERR("[spi%d] not support sys_config format\n", sspi->port);
#endif
}

static spi_master_status_t spi_clk_init(sunxi_spi_t *sspi, u32 mode_clk)
{
    unsigned long rate;
    hal_clk_status_t ret;
    hal_reset_type_t reset_type = HAL_SUNXI_RESET;
    u32 reset_id;
    hal_clk_type_t clk_type = HAL_SUNXI_CCU;
    hal_clk_id_t clk_id;
    hal_clk_id_t clk_bus_id;
    /* hal_clk_t clk; */

    switch (sspi->port)
    {
    case 0:
        clk_id = SUNXI_CLK_SPI(0);
        clk_bus_id = SUNXI_CLK_BUS_SPI(0);
        reset_id = SUNXI_CLK_RST_SPI(0);
        break;
    case 1:
        clk_id = SUNXI_CLK_SPI(1);
        clk_bus_id = SUNXI_CLK_BUS_SPI(1);
        reset_id = SUNXI_CLK_RST_SPI(1);
        break;
    case 2:
        clk_id = SUNXI_CLK_SPI(2);
        clk_bus_id = SUNXI_CLK_BUS_SPI(2);
        reset_id = SUNXI_CLK_RST_SPI(2);
        break;
    default:
        SPI_ERR("spi%d is invalid\n", sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

    sspi->reset = hal_reset_control_get(reset_type, reset_id);
    hal_reset_control_deassert(sspi->reset);

    sspi->mclk = hal_clock_get(clk_type, clk_id);
    sspi->bus_clk = hal_clock_get(clk_type, clk_bus_id);
    sspi->pclk = hal_clock_get(clk_type, SUNXI_CLK_PLL_SPI);

    ret = hal_clk_set_parent(sspi->mclk, sspi->pclk);
    if (ret)
    {
        SPI_ERR("[spi%d] clk set parent failed! return %d\n",
                sspi->port, ret);
        return SPI_MASTER_ERROR;
    }

    rate = mode_clk;
    /* rate = hal_clk_round_rate(sspi->mclk, mode_clk); */
    /* if (!rate) */
    /* { */
    /*     SPI_ERR("[spi%d] clk round rate failed! return %ld\n", */
    /*             sspi->port, rate); */
    /*     return SPI_MASTER_ERROR; */
    /* } */

    ret = hal_clk_set_rate(sspi->mclk, rate);
    if (ret)
    {
        SPI_ERR("[spi%d] clk set rate failed! return %d\n", sspi->port,
                ret);
        return SPI_MASTER_ERROR;
    }

    rate = hal_clk_get_rate(sspi->mclk);
    if (!rate)
    {
        SPI_ERR("[spi%d] clk get rate failed! return %ld\n", sspi->port,
                rate);
        return SPI_MASTER_ERROR;
    }

    ret = hal_clock_enable(sspi->bus_clk);
    ret = hal_clock_enable(sspi->mclk);
    if (ret)
    {
        SPI_ERR("[spi%d] couldn't enable mlck! return %d\n", sspi->port,
                ret);
        return SPI_MASTER_ERROR;
    }

    return SPI_MASTER_OK;
}

static spi_master_status_t spi_clk_exit(sunxi_spi_t *sspi)
{
    hal_clk_status_t ret;

    ret = hal_clock_disable(sspi->mclk);
    ret = hal_clock_disable(sspi->bus_clk);
    if (ret)
    {
        SPI_ERR("[spi%d] couldn't disable mlck! return %d\n",
                sspi->port, ret);
        return SPI_MASTER_ERROR;
    }

    hal_clock_put(sspi->mclk);
    hal_clock_put(sspi->bus_clk);

    hal_reset_control_assert(sspi->reset);
    hal_reset_control_put(sspi->reset);

    return SPI_MASTER_OK;
}

static spi_master_status_t spi_cpu_complete(sunxi_spi_t *sspi)
{
    uint32_t timeout = 0xffff;

    while (!sspi->result && timeout--)
        ;
    if (timeout <= 0)
    {
        SPI_ERR("[spi%d] xfer timeout\n", sspi->port);
        SPI_INFO("[spi%d] dump reg:\n", sspi->port);
        spi_dump_reg(sspi, 0, 0x60);
        return SPI_MASTER_ERROR_TIMEOUT;
    }
    else if (SPI_XFER_FAILED == sspi->result)
    {
        SPI_ERR("[spi%d] xfer failed...\n", sspi->port);
        SPI_INFO("[spi%d] dump reg:\n", sspi->port);
        spi_dump_reg(sspi, 0, 0x60);
        return SPI_MASTER_ERROR;
    }

    return SPI_MASTER_OK;
}

#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
static spi_master_status_t spi_dma_tx_complete(sunxi_spi_t *sspi)
{
    uint32_t flags = 0;
    uint32_t timeout = 0x7fffffff;
    struct sunxi_dma_chan *chan = sspi->dma_tx.chan;
    hal_dma_status_t dma_ret;
    spi_master_status_t ret = 0;
    int xResult;

    xResult = hal_sem_timedwait(sspi->xSemaphore_tx, 100); //100*10ms
    if (xResult == 0)
    {
        if (SPI_XFER_OK == sspi->result)
        {
            SPI_INFO("ok\n");
            ret = SPI_MASTER_OK;
        }
        else if (SPI_XFER_FAILED == sspi->result)
        {
            SPI_ERR("[spi%d] xfer failed...\n", sspi->port);
            SPI_INFO("[spi%d] dump reg:\n", sspi->port);
            spi_dump_reg(sspi, 0, 0x60);
            ret = SPI_MASTER_ERROR;
        }
    }
    else
    {
        SPI_ERR("[spi%d] dma xfer timeout\n", sspi->port);
        SPI_INFO("[spi%d] dump reg:\n", sspi->port);
        spi_dump_reg(sspi, 0, 0x60);

        sspi->result = SPI_XFER_FAILED;

        if (hal_sem_post(sspi->xSemaphore_tx))
        {
            SPI_ERR("[spi%d] xSemaphoreGive failed.\n", sspi->port);
        }

        ret = SPI_MASTER_ERROR_TIMEOUT;
    }

end:

    dma_ret = hal_dma_stop(chan);
    if (dma_ret)
    {
        SPI_ERR("[spi%d] dma stop error! ret %d\n", sspi->port,
                dma_ret);
        return SPI_MASTER_ERROR;
    }

    dma_ret = hal_dma_chan_free(chan);
    if (dma_ret)
    {
        SPI_ERR("[spi%d] free dma_tx failed, ret %d\n", sspi->port,
                dma_ret);
        return SPI_MASTER_ERROR;
    }

    return ret;
}

static spi_master_status_t spi_dma_rx_complete(sunxi_spi_t *sspi)
{
    uint32_t flags = 0;
    uint32_t len = sspi->transfer->rx_len, size = 0;
    uint8_t *buf = sspi->transfer->rx_buf;
    struct sunxi_dma_chan *chan = sspi->dma_rx.chan;
    hal_dma_status_t dma_ret;
    spi_master_status_t ret;
    int xResult;

#ifdef SPI_DATA_LEVEL
    unsigned int i, j;
    u8 dbuf[64], cnt = 0;
#endif

    xResult = hal_sem_timedwait(sspi->xSemaphore_rx, 1000); //100*10ms
    if (xResult != 0)
    {
        rt_kprintf("[spi%d] dma rx timeout\n", sspi->port);
        SPI_INFO("[spi%d] dump reg:\n", sspi->port);
        spi_dump_reg(sspi, 0, 0x40);

        sspi->result = SPI_XFER_FAILED;

        ret = SPI_MASTER_ERROR_TIMEOUT;
        goto end;
    }

    hal_dcache_invalidate((unsigned long)sspi->align_dma_buf, SPI_ALIGN(len, 64));
    sspi->result = SPI_XFER_OK;
    if (len <= ALIGN_DMA_BUF_SIZE)
    {
        memcpy(buf, sspi->align_dma_buf, len);
    }
    ret = SPI_MASTER_OK;
    SPI_INFO("ok\n");

#ifdef SPI_DATA_LEVEL
    SPI_INFO("rx_len = %d\n", len);
    for (i = 0; i < len; i += 16)
    {
        cnt = 0;
        cnt += sprintf(dbuf + cnt, "%03x: ", i);
        for (j = 0; ((i + j) < len) && (j < 16); j++)
            cnt += sprintf(dbuf + cnt, "%02x ",
                           ((uint8_t *)(buf))[i + j]);
        printf("%s\n", dbuf);
    }
#endif

end:
    spi_disable_irq(SPI_INT_STA_TC | SPI_INT_STA_ERR, sspi);

    dma_ret = hal_dma_stop(chan);
    if (dma_ret)
    {
        SPI_ERR("[spi%d] dma stop error! ret %d\n", sspi->port,
                dma_ret);
        ret = SPI_MASTER_ERROR;
    }

    dma_ret = hal_dma_chan_free(chan);
    if (dma_ret)
    {
        SPI_ERR("[spi%d] free dma_rx failed, ret %d\n", sspi->port,
                dma_ret);
        return SPI_MASTER_ERROR;
    }

    return ret;
}
#endif

/*
 * < 64 : cpu ;  >= 64 : dma
 * wait for done completion in this function, wakup in the irq hanlder
 */
spi_master_status_t hal_spi_xfer(hal_spi_master_port_t port,
                                 hal_spi_master_transfer_t *transfer)
{
    uint32_t flags = 0;
    spi_master_status_t ret = 0;
    sunxi_spi_t *sspi = &g_sunxi_spi[port];

    if (NULL == transfer)
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        ret = SPI_MASTER_INVALID_PARAMETER;
        goto end;
    }

    SPI_INFO("[spi%d] tl=%lu rl=%lu, tsl=%lu\n", sspi->port, transfer->tx_len,
             transfer->rx_len, transfer->tx_single_len);

    if ((!transfer->tx_buf && !transfer->rx_buf) ||
        (!transfer->tx_len && !transfer->rx_buf))
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        ret = SPI_MASTER_INVALID_PARAMETER;
        goto end;
    }

    sspi->result = SPI_XFER_READY;
    sspi->transfer = transfer;

    if (spi_mode_check(sspi))
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        ret = SPI_MASTER_INVALID_PARAMETER;
        goto end;
    }

    spi_clr_irq_pending(SPI_INT_STA_MASK, sspi);
    spi_disable_dma_irq(SPI_FIFO_CTL_DRQEN_MASK, sspi);
    spi_reset_fifo(sspi);
    spi_enable_irq(SPI_INTEN_TC | SPI_INTEN_ERR, sspi);
    // cpu_dcache_clean_all();

    if (spi_transfer(sspi))
    {
        ret = SPI_MASTER_ERROR;
        goto end;
    }

    switch (sspi->mode_type)
    {
    case SGLE_HALF_DUPLEX_RX:
    case DUAL_HALF_DUPLEX_RX:
    case QUAD_HALF_DUPLEX_RX:
    case FULL_DUPLEX_TX_RX:
    {
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        /* >64 use DMA transfer, or use cpu */
        if (sspi->transfer->rx_len > BULK_DATA_BOUNDARY)
        {
            if (spi_dma_rx_complete(sspi))
            {
                ret = SPI_MASTER_ERROR;
                goto end;
            }
        }
        else
        {
#endif
            if (spi_cpu_complete(sspi))
            {
                ret = SPI_MASTER_ERROR;
                goto end;
            }
            else
            {
                ret = SPI_MASTER_OK;
            }
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        }
#endif
        break;
    }
    case SGLE_HALF_DUPLEX_TX:
    case DUAL_HALF_DUPLEX_TX:
    case QUAD_HALF_DUPLEX_TX:
    {
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        /* >64 use DMA transfer, or use cpu */
        if (sspi->transfer->tx_len > BULK_DATA_BOUNDARY)
        {
            if (spi_dma_tx_complete(sspi))
            {
                ret = SPI_MASTER_ERROR;
                goto end;
            }
        }
        else
        {
#endif
            if (spi_cpu_complete(sspi))
            {
                ret = SPI_MASTER_ERROR;
                goto end;
            }
            else
            {
                ret = SPI_MASTER_OK;
            }
#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
        }
#endif
        break;
    }
    default:
    {
        SPI_ERR("[spi%d] invalid parameter\n", sspi->port);
        ret = SPI_MASTER_INVALID_PARAMETER;
    }
    }

end:
    if (sspi->mode_type != MODE_TYPE_NULL)
    {
        sspi->mode_type = MODE_TYPE_NULL;
    }

    return ret;
}

static int sunxi_get_spic_clk(sunxi_spi_t *sspi)
{
    unsigned long rate;

    rate = hal_clk_get_rate(sspi->mclk);
    if (!rate)
        SPI_ERR("[spi%d] clk get rate failed! return %ld\n", sspi->port, rate);
    return rate;
}

/* legacy interface*/
static void spi_set_clk(u32 spi_clk, u32 ahb_clk, unsigned long base_addr, u32 cdr)
{
    u32 reg_val = 0;
    u32 div_clk = 0;

    SPI_INFO("set spi clock %ld, mclk %ld\n", spi_clk, ahb_clk);
    reg_val = hal_readl(base_addr + SPI_CLK_CTL_REG);

    /* CDR2 */
    if (cdr)
    {
        div_clk = ahb_clk / (spi_clk * 2) - 1;
        reg_val &= ~SPI_CLK_CTL_CDR2;
        reg_val |= (div_clk | SPI_CLK_CTL_DRS);
        SPI_INFO("CDR2 - n = %ld\n", div_clk);
    }
    else /* CDR1 */
    {
        while (ahb_clk > spi_clk)
        {
            div_clk++;
            ahb_clk >>= 1;
        }
        reg_val &= ~(SPI_CLK_CTL_CDR1 | SPI_CLK_CTL_DRS);
        reg_val |= (div_clk << 8);
        SPI_INFO("CDR1 - n = %ld\n", div_clk);
    }

    hal_writel(reg_val, base_addr + SPI_CLK_CTL_REG);
}

spi_master_status_t hal_spi_hw_config(hal_spi_master_port_t port, hal_spi_master_config_t *spi_config)
{
    int sclk_freq = 0;
    unsigned long clock_frequency;
    sunxi_spi_t *sspi = &g_sunxi_spi[port];
    uint32_t config = 0;

    if (NULL == spi_config)
    {
        SPI_ERR("[spi%d] invalid parameter\n", port);
        return SPI_MASTER_INVALID_PARAMETER;
    }

    sspi->base = g_sunxi_spi_params[port].reg_base;
    sspi->port = port;
    sspi->mode_type = MODE_TYPE_NULL;

    if (spi_config->clock_frequency)
        clock_frequency = spi_config->clock_frequency;
    else
        clock_frequency = SPI_MOD_CLK;

    if (clock_frequency > SPI_MAX_FREQUENCY)
    {
        SPI_ERR("[spi%d] invalid parameter! max_frequency is 100MHZ\n",
                sspi->port);
    }
    else
    {
        SPI_INIT("[spi%d] clock_frequency = %ldHZ\n", sspi->port,
                 clock_frequency);
    }

    if (clock_frequency >= SPI_HIGH_FREQUENCY)
    {
        spi_sample_delay(0, 1, sspi);
    }
    else if (clock_frequency <= SPI_LOW_FREQUENCY)
    {
        spi_sample_delay(1, 0, sspi);
    }
    else
    {
        spi_sample_delay(0, 0, sspi);
    }

    spi_soft_reset(sspi);

    sclk_freq = sunxi_get_spic_clk(sspi);
    if (!sclk_freq)
    {
        SPI_INFO("spi clk error ! \n");
    }
    else if (sclk_freq != clock_frequency)
    {
        spi_clk_exit(sspi);
        if (spi_clk_init(sspi, clock_frequency))
        {
            SPI_ERR("[spi%d] init clk error\n", sspi->port);
            return SPI_MASTER_ERROR;
        }
    }
    //spi_set_clk(clock_frequency, sclk_freq, sspi->base, 0);

    if (spi_config->slave_port)
    {
        SPI_ERR("[spi%d] software control cs isn't support \n",
                sspi->port);
        return SPI_MASTER_INVALID_PARAMETER;
    }
    else
    {
        spi_set_cs(spi_config->slave_port, sspi);
    }

    if (spi_config->bit_order)
    {
        config |= SPI_LSB_FIRST_ACTIVE_;
        // spi_config_tc(SPI_LSB_FIRST_ACTIVE_, sspi);
    }

    config |= (spi_config->cpol) | (spi_config->cpha);
    spi_config_tc(config, sspi);

    spi_enable_bus(sspi);
    spi_set_master(sspi);
    spi_enable_tp(sspi);
    /*spi controller sends ss signal automatically*/
    spi_ss_owner(sspi, spi_config->csmode);
    /* reset fifo */
    spi_reset_fifo(sspi);

    return SPI_MASTER_OK;
}

spi_master_status_t hal_spi_init(hal_spi_master_port_t port,
                                 hal_spi_master_config_t *cfg)
{
    sunxi_spi_t *sspi = &g_sunxi_spi[port];

    if (port >= HAL_SPI_MASTER_MAX)
    {
        SPI_ERR("[spi%d] invalid port\n", sspi->port);
        return SPI_MASTER_ERROR;
    }

    sspi->base = g_sunxi_spi_params[port].reg_base;
    sspi->irqnum = g_sunxi_spi_params[port].irq_num;
    sspi->port = port;
    sspi->mode_type = MODE_TYPE_NULL;

    SPI_INFO("spi[%d] init ,reg base is %lx \n", port, sspi->base);

    if (request_irq(sspi->irqnum, spi_irq_handler, 0, "spi-ctl", sspi) < 0)
    {
        SPI_ERR("[spi%d] request irq error\n", sspi->port);
        return SPI_MASTER_ERROR;
    }
    enable_irq(sspi->irqnum);

    if (spi_pinctrl_init(sspi))
    {
        SPI_ERR("[spi%d] init pinctrl error\n", sspi->port);
        return SPI_MASTER_ERROR;
    }

    if (spi_clk_init(sspi, SPI_MAX_FREQUENCY))
    {
        SPI_ERR("[spi%d] init clk error\n", sspi->port);
        return SPI_MASTER_ERROR;
    }

    spi_soft_reset(sspi);

    hal_spi_hw_config(port, cfg);

#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
    sspi->xSemaphore_tx = hal_sem_create(0);
    if (sspi->xSemaphore_tx == NULL)
    {
        SPI_ERR("[spi%d] creating semaphore_tx failed.\n", sspi->port);
        return SPI_MASTER_ERROR;
    }
    sspi->xSemaphore_rx = hal_sem_create(0);
    if (sspi->xSemaphore_rx == NULL)
    {
        SPI_ERR("[spi%d] creating semaphore_rx failed.\n", sspi->port);
        return SPI_MASTER_ERROR;
    }
    sspi->align_dma_buf = dma_alloc_coherent(ALIGN_DMA_BUF_SIZE);
    if (!sspi->align_dma_buf)
    {
        SPI_ERR("[spi%d] alloc memory failed\n", sspi->port);
        return SPI_MASTER_ERROR_NOMEM;
    }
    SPI_INIT("[spi%d] DMA xfer enable\n", sspi->port);
#else
    SPI_INIT("[spi%d] CPU xfer only\n", sspi->port);
#endif

    return SPI_MASTER_OK;
}

spi_master_status_t hal_spi_deinit(hal_spi_master_port_t port)
{
    uint8_t i;
    sunxi_spi_t *sspi = &g_sunxi_spi[port];

    spi_disable_bus(sspi);

    disable_irq(sspi->irqnum);

#ifndef CONFIG_SUNXI_SPI_CPU_XFER_ONLY
    dma_free_coherent(sspi->align_dma_buf);
    hal_sem_delete(sspi->xSemaphore_tx);
    hal_sem_delete(sspi->xSemaphore_rx);
#endif

    if (spi_clk_exit(sspi))
    {
        SPI_ERR("[spi%d] exit clk error\n", sspi->port);
        return SPI_MASTER_ERROR;
    }

    free_irq(sspi->irqnum, sspi);

    return SPI_MASTER_OK;
}

spi_master_status_t hal_spi_write(hal_spi_master_port_t port,
                                  const void *buf, uint32_t size)
{
    spi_master_status_t ret;
    hal_spi_master_transfer_t tr;

    tr.tx_buf = buf;
    tr.tx_len = size;
    tr.rx_buf = NULL;
    tr.rx_len = 0;
    tr.dummy_byte = 0;
    tr.tx_single_len = size;
    tr.tx_nbits = SPI_NBITS_SINGLE;

    SPI_INFO("spi[%d] write data,len is %ld \n", port, size);
    ret = hal_spi_xfer(port, &tr);
    return ret;
}

spi_master_status_t hal_spi_read(hal_spi_master_port_t port,
                                 void *buf, uint32_t size)
{
    spi_master_status_t ret;
    hal_spi_master_transfer_t tr;

    tr.rx_buf = buf;
    tr.rx_len = size;
    tr.tx_buf = NULL;
    tr.tx_len = 0;
    tr.dummy_byte = 0;
    tr.tx_single_len = size;
    tr.rx_nbits = SPI_NBITS_SINGLE;

    SPI_INFO("spi[%d] read data,len is %ld \n", port, size);
    ret = hal_spi_xfer(port, &tr);
    return ret;
}

void hal_spi_cs(hal_spi_master_port_t port, uint8_t on_off)
{
    sunxi_spi_t *sspi = &g_sunxi_spi[port];

    spi_ss_ctrl(sspi, on_off);
}
