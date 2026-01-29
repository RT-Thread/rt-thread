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

#define DBG_TAG "spi.k1x.qspi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>
#include <cpuport.h>
#include <spacemit.h>
#include <dt-bindings/size.h>

#define QSPI_WAIT_TIMEOUT               300 /* ms */
#define QSPI_AUTOSUSPEND_TIMEOUT        2000
#define K1X_MPMU_ACGR                   0xd4051024

/* QSPI PMUap register */
#define PMUA_QSPI_CLK_RES_CTRL          0xd4282860
#define QSPI_CLK_SEL(x)                 ((x) << 6)
#define QSPI_CLK_SEL_MASK               RT_GENMASK(8, 6)
#define QSPI_CLK_EN                     RT_BIT(4)
#define QSPI_BUS_CLK_EN                 RT_BIT(3)
#define QSPI_CLK_RST                    RT_BIT(1)
#define QSPI_BUS_RST                    RT_BIT(0)

/* QSPI memory base */
#define QSPI_AMBA_BASE(qspi)            ((qspi)->memmap_base)
#define QSPI_FLASH_A1_BASE(qspi)        QSPI_AMBA_BASE(qspi)
#define QSPI_FLASH_A1_TOP(qspi)         (QSPI_FLASH_A1_BASE(qspi) + 0x4000000)
#define QSPI_FLASH_A2_BASE(qspi)        QSPI_FLASH_A1_TOP(qspi)
#define QSPI_FLASH_A2_TOP(qspi)         (QSPI_FLASH_A2_BASE(qspi) + 0x100000)
#define QSPI_FLASH_B1_BASE(qspi)        QSPI_FLASH_A2_TOP(qspi)
#define QSPI_FLASH_B1_TOP(qspi)         (QSPI_FLASH_B1_BASE(qspi) + 0x100000)
#define QSPI_FLASH_B2_BASE(qspi)        QSPI_FLASH_B1_TOP(qspi)
#define QSPI_FLASH_B2_TOP(qspi)         (QSPI_FLASH_B2_BASE(qspi) + 0x100000)

/* TX/RX/ABH buffer max */
#define QSPI_RX_BUFF_MAX                128
#define QSPI_TX_BUFF_MAX                256
#define QSPI_TX_BUFF_POP_MIN            16
#define QSPI_AHB_BUFF_MAX_SIZE          512
#define QSPI_TX_DMA_BURST               16

#define QSPI_WAIT_BIT_CLEAR             0
#define QSPI_WAIT_BIT_SET               1

/* QSPI Host Registers used by the driver */
#define QSPI_MCR                        0x00
#define QSPI_MCR_ISD_MASK               RT_GENMASK(19, 16)
#define QSPI_MCR_MDIS_MASK              RT_BIT(14)
#define QSPI_MCR_CLR_TXF_MASK           RT_BIT(11)
#define QSPI_MCR_CLR_RXF_MASK           RT_BIT(10)
#define QSPI_MCR_DDR_EN_MASK            RT_BIT(7)
#define QSPI_MCR_END_CFG_MASK           RT_GENMASK(3, 2)
#define QSPI_MCR_SWRSTHD_MASK           RT_BIT(1)
#define QSPI_MCR_SWRSTSD_MASK           RT_BIT(0)

#define QSPI_TCR                        0x04
#define QSPI_IPCR                       0x08
#define QSPI_IPCR_SEQID(x)              ((x) << 24)

#define QSPI_FLSHCR                     0x0c

#define QSPI_BUF0CR                     0x10
#define QSPI_BUF1CR                     0x14
#define QSPI_BUF2CR                     0x18
#define QSPI_BUF3CR                     0x1c
#define QSPI_BUF3CR_ALLMST_MASK         RT_BIT(31)
#define QSPI_BUF3CR_ADATSZ(x)           ((x) << 8)
#define QSPI_BUF3CR_ADATSZ_MASK         RT_GENMASK(15, 8)

#define QSPI_BFGENCR                    0x20
#define QSPI_BFGENCR_SEQID(x)           ((x) << 12)

#define QSPI_SOCCR                      0x24

#define QSPI_BUF0IND                    0x30
#define QSPI_BUF1IND                    0x34
#define QSPI_BUF2IND                    0x38

#define QSPI_SFAR                       0x100
#define QSPI_SFACR                      0x104

#define QSPI_SMPR                       0x108
#define QSPI_SMPR_DDRSMP_MASK           RT_GENMASK(18, 16)
#define QSPI_SMPR_FSDLY_MASK            RT_BIT(6)
#define QSPI_SMPR_FSPHS_MASK            RT_BIT(5)
#define QSPI_SMPR_FSPHS_CLK             (416000000)
#define QSPI_SMPR_HSENA_MASK            RT_BIT(0)

#define QSPI_RBSR                       0x10c

#define QSPI_RBCT                       0x110
#define QSPI_RBCT_WMRK_MASK             RT_GENMASK(4, 0)
#define QSPI_RBCT_RXBRD_MASK            RT_BIT(8)

#define QSPI_TBSR                       0x150
#define QSPI_TBDR                       0x154
#define QSPI_TBCT                       0x158
#define QSPI_TX_WMRK                    (QSPI_TX_DMA_BURST / 4 - 1)

#define QSPI_SR                         0x15c
#define QSPI_SR_BUSY                    RT_BIT(0)
#define QSPI_SR_IP_ACC_MASK             RT_BIT(1)
#define QSPI_SR_AHB_ACC_MASK            RT_BIT(2)
#define QSPI_SR_TXFULL                  RT_BIT(27)

#define QSPI_FR                         0x160
#define QSPI_FR_TFF_MASK                RT_BIT(0)
#define QSPI_FR_IPGEF                   RT_BIT(4)
#define QSPI_FR_IPIEF                   RT_BIT(6)
#define QSPI_FR_IPAEF                   RT_BIT(7)
#define QSPI_FR_IUEF                    RT_BIT(11)
#define QSPI_FR_ABOF                    RT_BIT(12)
#define QSPI_FR_AIBSEF                  RT_BIT(13)
#define QSPI_FR_AITEF                   RT_BIT(14)
#define QSPI_FR_ABSEF                   RT_BIT(15)
#define QSPI_FR_RBDF                    RT_BIT(16)
#define QSPI_FR_RBOF                    RT_BIT(17)
#define QSPI_FR_ILLINE                  RT_BIT(23)
#define QSPI_FR_TBUF                    RT_BIT(26)
#define QSPI_FR_TBFF                    RT_BIT(27)
#define BUFFER_FR_FLAG                  (QSPI_FR_ABOF| QSPI_FR_RBOF| QSPI_FR_TBUF)

#define COMMAND_FR_FLAG                 (QSPI_FR_ABSEF | QSPI_FR_AITEF | QSPI_FR_AIBSEF | QSPI_FR_IUEF | \
                                        QSPI_FR_IPAEF |QSPI_FR_IPIEF | QSPI_FR_IPGEF)

#define QSPI_RSER                       0x164
#define QSPI_RSER_TFIE                  RT_BIT(0)
#define QSPI_RSER_IPGEIE                RT_BIT(4)
#define QSPI_RSER_IPIEIE                RT_BIT(6)
#define QSPI_RSER_IPAEIE                RT_BIT(7)
#define QSPI_RSER_IUEIE                 RT_BIT(11)
#define QSPI_RSER_ABOIE                 RT_BIT(12)
#define QSPI_RSER_AIBSIE                RT_BIT(13)
#define QSPI_RSER_AITIE                 RT_BIT(14)
#define QSPI_RSER_ABSEIE                RT_BIT(15)
#define QSPI_RSER_RBDIE                 RT_BIT(16)
#define QSPI_RSER_RBOIE                 RT_BIT(17)
#define QSPI_RSER_RBDDE                 RT_BIT(21)
#define QSPI_RSER_ILLINIE               RT_BIT(23)
#define QSPI_RSER_TBFDE                 RT_BIT(25)
#define QSPI_RSER_TBUIE                 RT_BIT(26)
#define QSPI_RSER_TBFIE                 RT_BIT(27)
#define BUFFER_ERROR_INT                (QSPI_RSER_ABOIE| QSPI_RSER_RBOIE | QSPI_RSER_TBUIE)

#define COMMAND_ERROR_INT               (QSPI_RSER_ABSEIE | QSPI_RSER_AITIE | QSPI_RSER_AIBSIE | QSPI_RSER_IUEIE | \
                                        QSPI_RSER_IPAEIE |QSPI_RSER_IPIEIE | QSPI_RSER_IPGEIE)

#define QSPI_SPNDST                     0x168
#define QSPI_SPTRCLR                    0x16c
#define QSPI_SPTRCLR_IPPTRC             RT_BIT(8)
#define QSPI_SPTRCLR_BFPTRC             RT_BIT(0)

#define QSPI_SFA1AD                     0x180
#define QSPI_SFA2AD                     0x184
#define QSPI_SFB1AD                     0x188
#define QSPI_SFB2AD                     0x18c
#define QSPI_DLPR                       0x190
#define QSPI_RBDR(x)                    (0x200 + ((x) * 4))

#define QSPI_LUTKEY                     0x300
#define QSPI_LUTKEY_VALUE               0x5af05af0

#define QSPI_LCKCR                      0x304
#define QSPI_LCKER_LOCK                 RT_BIT(0)
#define QSPI_LCKER_UNLOCK               RT_BIT(1)

#define QSPI_LUT_BASE                   0x310
/* 16Bytes per sequence */
#define QSPI_LUT_REG(seqid, i)          (QSPI_LUT_BASE + (seqid) * 16 + (i) * 4)

/*
 * QSPI Sequence index.
 * index 0 is preset at boot for AHB read,
 * index 1 is used for other command.
 */
#define SEQID_LUT_AHBREAD_ID            0
#define SEQID_LUT_SHARED_ID             1

/* QSPI Instruction set for the LUT register */
#define LUT_INSTR_STOP                  0
#define LUT_INSTR_CMD                   1
#define LUT_INSTR_ADDR                  2
#define LUT_INSTR_DUMMY                 3
#define LUT_INSTR_MODE                  4
#define LUT_INSTR_MODE2                 5
#define LUT_INSTR_MODE4                 6
#define LUT_INSTR_READ                  7
#define LUT_INSTR_WRITE                 8
#define LUT_INSTR_JMP_ON_CS             9
#define LUT_INSTR_ADDR_DDR              10
#define LUT_INSTR_MODE_DDR              11
#define LUT_INSTR_MODE2_DDR             12
#define LUT_INSTR_MODE4_DDR             13
#define LUT_INSTR_READ_DDR              14
#define LUT_INSTR_WRITE_DDR             15
#define LUT_INSTR_DATA_LEARN            16

/*
 * The PAD definitions for LUT register.
 *
 * The pad stands for the number of IO lines [0:3].
 * For example, the quad read needs four IO lines,
 * so you should use LUT_PAD(4).
 */
#define LUT_PAD(x)                      (fls(x) - 1)

/*
 * One sequence must be consisted of 4 LUT enteries(16Bytes).
 * LUT entries with the following register layout:
 * b'31                                                                     b'0
 *  ---------------------------------------------------------------------------
 *  |INSTR1[15~10]|PAD1[9~8]|OPRND1[7~0] | INSTR0[15~10]|PAD0[9~8]|OPRND0[7~0]|
 *  ---------------------------------------------------------------------------
 */
#define LUT_DEF(idx, ins, pad, opr)     ((((ins) << 10) | ((pad) << 8) | (opr)) << (((idx) & 0x1) * 16))

#define READ_FROM_CACHE_OP              0x03
#define READ_FROM_CACHE_OP_Fast         0x0b
#define READ_FROM_CACHE_OP_X2           0x3b
#define READ_FROM_CACHE_OP_X4           0x6b
#define READ_FROM_CACHE_OP_DUALIO       0xbb
#define READ_FROM_CACHE_OP_QUADIO       0xeb

enum qpsi_cs
{
    QSPI_CS_A1 = 0,
    QSPI_CS_A2,
    QSPI_CS_B1,
    QSPI_CS_B2,
    QSPI_CS_MAX,
    QSPI_DEFAULT_CS = QSPI_CS_A1,
};

enum qpsi_mode
{
    QSPI_NORMAL_MODE = 0,
    QSPI_DISABLE_MODE,
    QSPI_STOP_MODE,
};

struct k1x_qspi
{
    struct rt_spi_bus parent;

    struct rt_clk *clk;
    struct rt_clk *bus_clk;
    struct rt_reset_control *rstc;

    int irq;
    void *io_map;
    rt_ubase_t io_phys;

    void *ahb_map;
    rt_ubase_t memmap_base;
    rt_ubase_t memmap_size;

    rt_uint32_t sfa1ad;
    rt_uint32_t sfa2ad;
    rt_uint32_t sfb1ad;
    rt_uint32_t sfb2ad;

    void *pmuap_addr;
    void *mpmu_acgr;
    rt_uint32_t pmuap_reg;
    rt_uint32_t mpmu_acgr_reg;

    rt_uint32_t rx_buf_size;
    rt_uint32_t tx_buf_size;
    rt_uint32_t ahb_buf_size;
    rt_uint32_t ahb_read_enable;
    rt_uint32_t tx_unit_size;
    rt_uint32_t rx_unit_size;

    rt_uint32_t cmd_interrupt;
    rt_uint32_t fr_error_flag;

    rt_uint32_t cs_selected;
    rt_uint32_t max_hz;
    rt_uint32_t endian_xchg;
    rt_uint32_t dma_enable;

    rt_uint32_t tx_wmrk;
    rt_uint32_t tx_dma_enable;
    rt_uint32_t rx_dma_enable;

    struct rt_dma_slave_config rx_config;
    struct rt_dma_slave_config tx_config;
    struct rt_dma_slave_transfer rx_transfer;
    struct rt_dma_slave_transfer tx_transfer;

    struct rt_dma_chan *dma_rx;
    struct rt_dma_chan *dma_tx;

    struct rt_completion cmd_completion;
    struct rt_completion dma_completion;
};

#define raw_to_k1x_qspi(raw) rt_container_of(raw, struct k1x_qspi, parent)

static void qspi_writel(struct k1x_qspi *qspi, rt_uint32_t val, void *addr)
{
    if (qspi->endian_xchg)
    {
        HWREG32(addr) = rt_cpu_to_be32(val);
    }
    else
    {
        HWREG32(addr) = val;
    }
}

static rt_uint32_t qspi_readl(struct k1x_qspi *qspi, void *addr)
{
    if (qspi->endian_xchg)
    {
        return rt_be32_to_cpu(HWREG32(addr));
    }
    else
    {
        return HWREG32(addr);
    }
}

static rt_err_t k1x_qspi_readl_poll_tout(struct k1x_qspi *qspi, void *base,
        rt_uint32_t mask, rt_uint32_t timeout_us, rt_uint8_t wait_set)
{
    rt_uint32_t reg;

    if (qspi->endian_xchg)
    {
        mask = __builtin_bswap32(mask);
    }

    if (wait_set)
    {
        return readl_poll_timeout(base, reg, (reg & mask), 10, timeout_us);
    }
    else
    {
        return readl_poll_timeout(base, reg, !(reg & mask), 10, timeout_us);
    }
}

static void qspi_reset(struct k1x_qspi *qspi)
{
    rt_uint32_t reg;

    /* QSPI_SR[QSPI_SR_BUSY] must be 0 */
    if (k1x_qspi_readl_poll_tout(qspi, qspi->io_map + QSPI_SR,
            QSPI_SR_BUSY, QSPI_WAIT_TIMEOUT*1000, QSPI_WAIT_BIT_CLEAR))
    {
        return;
    }

    /* qspi softreset first */
    reg = qspi_readl(qspi, qspi->io_map + QSPI_MCR);
    reg |= QSPI_MCR_SWRSTHD_MASK | QSPI_MCR_SWRSTSD_MASK;
    qspi_writel(qspi, reg, qspi->io_map + QSPI_MCR);
    reg = qspi_readl(qspi, qspi->io_map + QSPI_MCR);

    if ((reg & 0x3) != 0x3)
    {
        LOG_I("Reset ignored %#x", reg);
    }

    rt_hw_us_delay(1);
    reg &= ~(QSPI_MCR_SWRSTHD_MASK | QSPI_MCR_SWRSTSD_MASK);
    qspi_writel(qspi, reg, qspi->io_map + QSPI_MCR);
}

static void qspi_enter_mode(struct k1x_qspi *qspi, rt_uint32_t mode)
{
    rt_uint32_t mcr;

    mcr = qspi_readl(qspi, qspi->io_map + QSPI_MCR);
    if (mode == QSPI_NORMAL_MODE)
    {
        mcr &= ~QSPI_MCR_MDIS_MASK;
    }
    else if (mode == QSPI_DISABLE_MODE)
    {
        mcr |= QSPI_MCR_MDIS_MASK;
    }
    qspi_writel(qspi, mcr, qspi->io_map + QSPI_MCR);
}

static void qspi_write_sfar(struct k1x_qspi *qspi, rt_uint32_t val)
{
    /* QSPI_SR[IP_ACC] must be 0 */
    if (k1x_qspi_readl_poll_tout(qspi, qspi->io_map + QSPI_SR,
            QSPI_SR_IP_ACC_MASK, QSPI_WAIT_TIMEOUT*1000, QSPI_WAIT_BIT_CLEAR))
    {
        return;
    }
    qspi_writel(qspi, val, qspi->io_map + QSPI_SFAR);
}

/*
 * IP Command Trigger could not be executed Error Flag may happen for write
 * access to RBCT/SFAR register, need retry for these two register
 */
static void qspi_write_rbct(struct k1x_qspi *qspi, rt_uint32_t val)
{
    /* QSPI_SR[IP_ACC] must be 0 */
    if (k1x_qspi_readl_poll_tout(qspi, qspi->io_map + QSPI_SR,
            QSPI_SR_IP_ACC_MASK, QSPI_WAIT_TIMEOUT*1000, QSPI_WAIT_BIT_CLEAR))
    {
        return;
    }

    qspi_writel(qspi, val, qspi->io_map + QSPI_RBCT);
}

/*
 * If the slave device content being changed by Write/Erase, need to
 * invalidate the AHB buffer. This can be achieved by doing the reset
 * of controller after setting MCR0[SWRESET] bit.
 */
rt_inline void k1x_qspi_invalid(struct k1x_qspi *qspi)
{
    rt_uint32_t reg;

    reg = qspi_readl(qspi, qspi->io_map + QSPI_MCR);
    reg |= QSPI_MCR_SWRSTHD_MASK | QSPI_MCR_SWRSTSD_MASK;
    qspi_writel(qspi, reg, qspi->io_map + QSPI_MCR);

    /*
     * The minimum delay : 1 AHB + 2 SFCK clocks.
     * Delay 1 us is enough.
     */
    rt_hw_us_delay(1);

    reg &= ~(QSPI_MCR_SWRSTHD_MASK | QSPI_MCR_SWRSTSD_MASK);
    qspi_writel(qspi, reg, qspi->io_map + QSPI_MCR);
}

static void k1x_qspi_prepare_lut(struct k1x_qspi *qspi,
        struct rt_qspi_message *qxfer, rt_uint32_t seq_id)
{
    int lutidx = 0;
    rt_uint32_t lutval[4] = {};

    /* qspi cmd */
    lutval[0] |= LUT_DEF(lutidx, LUT_INSTR_CMD,
            LUT_PAD(qxfer->instruction.qspi_lines), qxfer->instruction.content);
    lutidx++;

    /* addr bytes */
    if (qxfer->address.size)
    {
        lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_INSTR_ADDR,
                LUT_PAD(qxfer->address.qspi_lines), qxfer->address.size * 8);
        lutidx++;
    }

    /* dummy bytes, if needed */
    if (qxfer->alternate_bytes.size)
    {
        lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_INSTR_DUMMY,
                LUT_PAD(qxfer->alternate_bytes.qspi_lines),
                qxfer->alternate_bytes.size * 8 / qxfer->alternate_bytes.qspi_lines);
        lutidx++;
    }

    /* read/write data bytes */
    if (qxfer->parent.length)
    {
        lutval[lutidx / 2] |= LUT_DEF(lutidx,
                qxfer->parent.recv_buf ? LUT_INSTR_READ : LUT_INSTR_WRITE,
                    LUT_PAD(qxfer->qspi_data_lines), 0);
        lutidx++;
    }

    /* stop condition. */
    lutval[lutidx / 2] |= LUT_DEF(lutidx, LUT_INSTR_STOP, 0, 0);

    /* unlock LUT */
    qspi_writel(qspi, QSPI_LUTKEY_VALUE, qspi->io_map + QSPI_LUTKEY);
    qspi_writel(qspi, QSPI_LCKER_UNLOCK, qspi->io_map + QSPI_LCKCR);

    /* fill LUT register */
    for (int i = 0; i < RT_ARRAY_SIZE(lutval); ++i)
    {
        qspi_writel(qspi, lutval[i], qspi->io_map + QSPI_LUT_REG(seq_id, i));
    }

    /* lock LUT */
    qspi_writel(qspi, QSPI_LUTKEY_VALUE, qspi->io_map + QSPI_LUTKEY);
    qspi_writel(qspi, QSPI_LCKER_LOCK, qspi->io_map + QSPI_LCKCR);
}

static void k1x_qspi_enable_interrupt(struct k1x_qspi *qspi, rt_uint32_t val)
{
    rt_uint32_t resr = 0;

    resr = qspi_readl(qspi, qspi->io_map + QSPI_RSER);
    resr |= val;
    qspi_writel(qspi, resr, qspi->io_map + QSPI_RSER);
}

static void k1x_qspi_disable_interrupt(struct k1x_qspi *qspi, rt_uint32_t val)
{
    rt_uint32_t resr = 0;

    resr = qspi_readl(qspi, qspi->io_map + QSPI_RSER);
    resr &= ~val;
    qspi_writel(qspi, resr, qspi->io_map + QSPI_RSER);
}

static void k1x_qspi_dma_callback(struct rt_dma_chan *chan, rt_size_t size)
{
    struct k1x_qspi *qspi = chan->priv;

    rt_completion_done(&qspi->dma_completion);
}

static rt_err_t k1x_qspi_tx_dma_exec(struct k1x_qspi *qspi, struct rt_qspi_message *qxfer)
{
    rt_err_t err;

    qspi->tx_config.src_addr = (rt_ubase_t)rt_kmem_v2p((void *)qxfer->parent.send_buf);

    if ((err = rt_dma_chan_config(qspi->dma_tx, &qspi->tx_config)))
    {
        return err;
    }

    qspi->tx_transfer.buffer_len = qxfer->parent.length;
    qspi->tx_transfer.src_addr = qspi->tx_config.src_addr;

    if ((err = rt_dma_prep_single(qspi->dma_tx, &qspi->tx_transfer)))
    {
        return err;
    }

    if ((err = rt_dma_chan_start(qspi->dma_tx)))
    {
        return err;
    }

    return rt_completion_wait(&qspi->dma_completion, RT_WAITING_FOREVER);
}

static rt_err_t k1x_qspi_rx_dma_exec(struct k1x_qspi *qspi, struct rt_qspi_message *qxfer)
{
    rt_err_t err;

    qspi->rx_config.dst_addr = (rt_ubase_t)rt_kmem_v2p(qxfer->parent.recv_buf);

    if ((err = rt_dma_chan_config(qspi->dma_rx, &qspi->rx_config)))
    {
        return err;
    }

    qspi->rx_transfer.buffer_len = qxfer->parent.length;
    qspi->rx_transfer.dst_addr = qspi->rx_config.dst_addr;

    if ((err = rt_dma_prep_memcpy(qspi->dma_rx, &qspi->rx_transfer)))
    {
        return err;
    }

    if ((err = rt_dma_chan_start(qspi->dma_rx)))
    {
        return err;
    }

    return rt_completion_wait(&qspi->dma_completion,
            rt_tick_from_millisecond(qxfer->parent.length));
}

static rt_err_t k1x_qspi_ahb_read(struct k1x_qspi *qspi, struct rt_qspi_message *qxfer)
{
    rt_err_t err;
    rt_uint32_t len = qxfer->parent.length, from = qxfer->address.content;

    /* Read out the data directly from the AHB buffer. */
    if (from + len > qspi->memmap_size)
    {
        return -RT_ENOSYS;
    }

    /* Firstly try the DMA */
    if (qspi->rx_dma_enable)
    {
        if (!(err = k1x_qspi_rx_dma_exec(qspi, qxfer)))
        {
            return RT_EOK;
        }
        else
        {
            LOG_D("Read rx dma fallback to memcpy read");
        }
    }

    rt_memcpy(qxfer->parent.recv_buf, (qspi->ahb_map + qxfer->address.content), len);

    return RT_EOK;
}

static rt_err_t k1x_qspi_fill_txfifo(struct k1x_qspi *qspi, struct rt_qspi_message *qxfer)
{
    int i;
    void *base = qspi->io_map;
    rt_uint32_t val, tbsr, wait_cnt;
    rt_size_t length = qxfer->parent.length;

    if (!qspi->tx_dma_enable || (length % QSPI_TX_BUFF_POP_MIN))
    {
        qspi->tx_wmrk = 0;
        for (i = 0; i < RT_ALIGN_DOWN(length, 4); i += 4)
        {
            rt_memcpy(&val, qxfer->parent.send_buf + i, 4);
            qspi_writel(qspi, val, base + QSPI_TBDR);
        }

        if (i < length)
        {
            rt_memcpy(&val, qxfer->parent.send_buf + i, length - i);
            qspi_writel(qspi, val, base + QSPI_TBDR);
        }

        /*
         * There must be at least 128bit data available in TX FIFO
         * for any pop operation otherwise QSPI_FR[TBUF] will be set
         */
        for (i = length; i < RT_ALIGN_DOWN(length + (QSPI_TX_BUFF_POP_MIN - 1), QSPI_TX_BUFF_POP_MIN); i += 4)
        {
            qspi_writel(qspi, 0, base + QSPI_TBDR);
        }
    }
    else
    {
        /*
         * Note that the number of bytes per DMA loop is determined
         * by thee size of the QSPI_TBCT[WMRK].
         * bytes per DMA loop = (QSPI_TBCT[WMRK] + 1) * 4.
         * set QSPI_TX_WMRK as the TX watermark.
         */
        qspi->tx_wmrk = QSPI_TX_WMRK;
        qspi_writel(qspi, qspi->tx_wmrk, base + QSPI_TBCT);

        /* Config DMA channel and start */
        if (k1x_qspi_tx_dma_exec(qspi, qxfer))
        {
            qspi->tx_wmrk = 0;
            LOG_E("Failed to start tx dma");
            return -RT_EIO;
        }

        /* Enable DMA request */
        k1x_qspi_enable_interrupt(qspi, QSPI_RSER_TBFDE);

        /*
         * before trigger qspi to send data to external bus, TX bufer
         * need to have some data, or underrun error may happen.
         * DMA need some time to write data to TX buffer, so add
         * a delay here for this requirement.
         */
        wait_cnt = 0;
        tbsr = qspi_readl(qspi, base + QSPI_TBSR);

        while (4 * (tbsr >> 16) < rt_min_t(unsigned int, qspi->tx_buf_size, length))
        {
            rt_hw_us_delay(1);
            tbsr = qspi_readl(qspi, base + QSPI_TBSR);

            if (wait_cnt++ >= 100)
            {
                rt_thread_mdelay(100);
                tbsr = qspi_readl(qspi, base + QSPI_TBSR);

                if (4 * (tbsr >> 16) < rt_min_t(unsigned int, qspi->tx_buf_size, length))
                {
                    LOG_E("Failed to fill tx dma");
                    /* Disable all interrupts */
                    qspi_writel(qspi, 0, qspi->io_map + QSPI_RSER);
                    rt_dma_chan_stop(qspi->dma_tx);
                    qspi->tx_wmrk = 0;

                    return -RT_EIO;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return RT_EOK;
}

static void k1x_qspi_read_rxfifo(struct k1x_qspi *qspi, struct rt_qspi_message *qxfer)
{
    int i;
    rt_uint32_t val;
    rt_uint8_t *buf;
    void *base = qspi->io_map;
    rt_size_t length = qxfer->parent.length;

    buf = qxfer->parent.recv_buf;

    for (i = 0; i < RT_ALIGN_DOWN(length, 4); i += 4)
    {
        val = qspi_readl(qspi, base + QSPI_RBDR(i / 4));
        rt_memcpy(buf + i, &val, 4);
    }

    if (i < length)
    {
        val = qspi_readl(qspi, base + QSPI_RBDR(i / 4));
        rt_memcpy(buf + i, &val, length - i);
    }
}

static rt_err_t k1x_qspi_do_op(struct k1x_qspi *qspi, struct rt_qspi_message *qxfer)
{
    rt_uint32_t mcr;
    rt_err_t err = RT_EOK;
    void *base = qspi->io_map;
    rt_size_t length = qxfer->parent.length;

    if (qspi->cmd_interrupt)
    {
        k1x_qspi_enable_interrupt(qspi, QSPI_RSER_TFIE | BUFFER_ERROR_INT | COMMAND_ERROR_INT);
    }

    /* Trigger LUT */
    qspi_writel(qspi, length | QSPI_IPCR_SEQID(SEQID_LUT_SHARED_ID), base + QSPI_IPCR);

    /* Wait for the transaction complete */
    if (qspi->cmd_interrupt)
    {
        rt_completion_wait(&qspi->cmd_completion, RT_WAITING_FOREVER);
    }
    else
    {
        err = k1x_qspi_readl_poll_tout(qspi, base + QSPI_FR, QSPI_FR_TFF_MASK,
                QSPI_WAIT_TIMEOUT * 1000, QSPI_WAIT_BIT_SET);
    }

    if (err)
    {
        goto _tx_dma_unmap;
    }

    if ((err = k1x_qspi_readl_poll_tout(qspi, base + QSPI_SR, QSPI_SR_BUSY,
            QSPI_WAIT_TIMEOUT * 1000, QSPI_WAIT_BIT_CLEAR)))
    {
        goto _tx_dma_unmap;
    }

    /* Read RX buffer for IP command read */
    if (length && qxfer->parent.recv_buf)
    {
        k1x_qspi_read_rxfifo(qspi, qxfer);
    }

    if (qspi->fr_error_flag & QSPI_FR_TBUF)
    {
        /* Abort current dma transfer */
        if (qspi->tx_dma_enable)
        {
            rt_dma_chan_stop(qspi->dma_tx);
        }

        /* Clear TX buf */
        mcr = qspi_readl(qspi, qspi->io_map + QSPI_MCR);
        mcr |= QSPI_MCR_CLR_TXF_MASK ;
        qspi_writel(qspi, mcr, qspi->io_map + QSPI_MCR);

        /* Reduce tx unit size and retry */
        if (qspi->tx_dma_enable)
        {
            qspi->tx_unit_size = qspi->tx_buf_size;
        }

        err = -RT_EIO;
    }
    else
    {
        if (qspi->tx_dma_enable)
        {
            qspi->tx_unit_size = qspi->tx_buf_size;
        }
    }

_tx_dma_unmap:
    if (qspi->tx_wmrk)
    {
        /* Disable TBFDE interrupt and dma unmap */
        k1x_qspi_disable_interrupt(qspi, QSPI_RSER_TBFDE);
        qspi->tx_wmrk = 0;
    }

    return err;
}

static rt_bool_t is_read_from_cache_opcode(rt_uint8_t opcode)
{
    return ((opcode == READ_FROM_CACHE_OP) ||
            (opcode == READ_FROM_CACHE_OP_Fast) ||
            (opcode == READ_FROM_CACHE_OP_X2) ||
            (opcode == READ_FROM_CACHE_OP_X4) ||
            (opcode == READ_FROM_CACHE_OP_DUALIO) ||
            (opcode == READ_FROM_CACHE_OP_QUADIO));
}

static rt_err_t k1x_qspi_configure(struct rt_spi_device *device,
        struct rt_spi_configuration *conf)
{
    return RT_EOK;
}

static rt_ssize_t k1x_qspi_xfer(struct rt_spi_device *device,
        struct rt_spi_message *xfer)
{
    void *base;
    rt_err_t err = RT_EOK;
    rt_uint32_t mask, reg;
    struct k1x_qspi *qspi = raw_to_k1x_qspi(device->bus);
    struct rt_qspi_message *qxfer = rt_container_of(xfer, struct rt_qspi_message, parent);

    base = qspi->io_map;

    /* Wait for controller being ready */
    mask = QSPI_SR_BUSY | QSPI_SR_IP_ACC_MASK | QSPI_SR_AHB_ACC_MASK;
    if ((err = k1x_qspi_readl_poll_tout(qspi,
        base + QSPI_SR, mask, QSPI_WAIT_TIMEOUT * 1000, QSPI_WAIT_BIT_CLEAR)))
    {
        LOG_E("Controller not ready");
        return err;
    }

    /* Clear TX/RX buffer before transaction */
    reg = qspi_readl(qspi, base + QSPI_MCR);
    reg |= QSPI_MCR_CLR_TXF_MASK | QSPI_MCR_CLR_RXF_MASK;
    qspi_writel(qspi, reg, base + QSPI_MCR);

    /*
     * Reset the sequence pointers whenever the sequence ID is changed by
     * updating the SEDID filed in QSPI_IPCR OR QSPI_BFGENCR.
     */
    reg = qspi_readl(qspi, base + QSPI_SPTRCLR);
    reg |= (QSPI_SPTRCLR_IPPTRC | QSPI_SPTRCLR_BFPTRC);
    qspi_writel(qspi, reg, base + QSPI_SPTRCLR);

    /* Set the flash address into the QSPI_SFAR */
    qspi_write_sfar(qspi, qspi->memmap_base + qxfer->address.content);

    /* Clear QSPI_FR before trigger LUT command */
    if ((reg = qspi_readl(qspi, base + QSPI_FR)))
    {
        qspi_writel(qspi, reg, base + QSPI_FR);
    }
    qspi->fr_error_flag = 0;

    /*
     * Read page command 13h must be done by IP command.
     * read from cache through the AHB bus by accessing the mapped memory.
     * In all other cases we use IP commands to access the flash.
     */
    if (xfer->length > (qspi->rx_buf_size - 4) &&
        xfer->recv_buf && qspi->ahb_read_enable &&
        is_read_from_cache_opcode(qxfer->instruction.content))
    {
        k1x_qspi_prepare_lut(qspi, qxfer, SEQID_LUT_AHBREAD_ID);
        err = k1x_qspi_ahb_read(qspi, qxfer);
    }
    else
    {
        /* IP command */
        k1x_qspi_prepare_lut(qspi, qxfer, SEQID_LUT_SHARED_ID);

        if (xfer->length && xfer->send_buf)
        {
            err = k1x_qspi_fill_txfifo(qspi, qxfer);
        }
        if (!err)
        {
            err = k1x_qspi_do_op(qspi, qxfer);
        }
    }

    /* Invalidate the data in the AHB buffer. */
    k1x_qspi_invalid(qspi);

    return err ? : xfer->length;
}

static const struct rt_spi_ops k1x_qspi_ops =
{
    .configure = k1x_qspi_configure,
    .xfer = k1x_qspi_xfer,
};

static void k1x_qspi_isr(int irq, void *param)
{
    rt_uint32_t fr;
    struct k1x_qspi *qspi = param;

    /* Disable all interrupts */
    qspi_writel(qspi, 0, qspi->io_map + QSPI_RSER);

    fr = qspi_readl(qspi, qspi->io_map + QSPI_FR);

    /* Check QSPI_FR error flag */
    if (fr & (COMMAND_FR_FLAG | BUFFER_FR_FLAG))
    {
        qspi->fr_error_flag = fr & (COMMAND_FR_FLAG | BUFFER_FR_FLAG);

        if (fr & QSPI_FR_IPGEF)
        {
            LOG_E("IP command trigger during AHB grant");
        }
        if (fr & QSPI_FR_IPIEF)
        {
            LOG_E("IP command trigger could not be executed");
        }
        if (fr & QSPI_FR_IPAEF)
        {
            LOG_E("IP command trigger during AHB access");
        }
        if (fr & QSPI_FR_IUEF)
        {
            LOG_E("IP command usage error");
        }
        if (fr & QSPI_FR_AIBSEF)
        {
            LOG_E("AHB illegal burst size error");
        }
        if (fr & QSPI_FR_AITEF)
        {
            LOG_E("AHB illegal trancaction error");
        }
        if (fr & QSPI_FR_ABSEF)
        {
            LOG_E("AHB sequence error");
        }

        if (fr & QSPI_FR_TBUF)
        {
            /* Disable TBFDE interrupt */
            k1x_qspi_disable_interrupt(qspi, QSPI_RSER_TBFDE);
            LOG_E("TX buffer underrun");
        }
        if (fr & QSPI_FR_RBOF)
        {
            LOG_E("RX buffer overflow");
        }
        if (fr & QSPI_FR_ABOF)
        {
            LOG_E("AHB buffer overflow");
        }
    }

    if (qspi->cmd_interrupt && (fr & (QSPI_FR_TFF_MASK | COMMAND_FR_FLAG | BUFFER_FR_FLAG)))
    {
        rt_completion_done(&qspi->cmd_completion);
    }
}

static void k1x_qspi_free(struct k1x_qspi *qspi, struct rt_device *dev)
{
    /* Set disable mode */
    qspi_writel(qspi, QSPI_MCR_MDIS_MASK, qspi->io_map + QSPI_MCR);
    qspi_writel(qspi, 0x0, qspi->io_map + QSPI_RSER);

    if (qspi->io_map)
    {
        rt_iounmap(qspi->io_map);
    }

    if (qspi->pmuap_addr)
    {
        rt_iounmap(qspi->pmuap_addr);
    }

    if (!rt_is_err_or_null(qspi->dma_tx))
    {
        rt_dma_chan_release(qspi->dma_tx);
    }

    if (!rt_is_err_or_null(qspi->dma_rx))
    {
        rt_dma_chan_release(qspi->dma_rx);
    }

    if (!rt_is_err_or_null(qspi->rstc))
    {
        rt_reset_control_assert(qspi->rstc);
        rt_reset_control_put(qspi->rstc);
    }

    if (!rt_is_err_or_null(qspi->clk))
    {
        rt_clk_disable_unprepare(qspi->clk);
        rt_clk_put(qspi->clk);
    }

    if (!rt_is_err_or_null(qspi->bus_clk))
    {
        rt_clk_disable_unprepare(qspi->bus_clk);
        rt_clk_put(qspi->bus_clk);
    }

    rt_free(qspi);
}

static rt_err_t k1x_qspi_probe(struct rt_platform_device *pdev)
{
    void *base;
    rt_err_t err;
    rt_uint32_t reg;
    const char *bus_name;
    rt_uint64_t addr, size;
    rt_uint32_t qspi_bus_num = 0;
    struct rt_device *dev = &pdev->parent;
    struct k1x_qspi *qspi = rt_calloc(1, sizeof(*qspi));

    if (!qspi)
    {
        return -RT_ENOMEM;
    }

    if (!(qspi->io_map = rt_dm_dev_iomap_by_name(dev, "qspi-base")))
    {
        err = -RT_EIO;
        goto _fail;
    }
    qspi->io_phys = (rt_ubase_t)rt_kmem_v2p(qspi->io_map);

    if ((err = rt_dm_dev_get_address_by_name(dev, "qspi-mmap", &addr, &size)))
    {
        err = -RT_EIO;
        goto _fail;
    }
    qspi->ahb_map = rt_ioremap((void *)addr, size);
    qspi->memmap_base = addr;
    qspi->memmap_size = size;

    if ((qspi->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = qspi->irq;
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "k1x,qspi-freq", &qspi->max_hz)))
    {
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-sfa1ad", &qspi->sfa1ad))
    {
        qspi->sfa1ad = QSPI_FLASH_A1_TOP(qspi);
    }
    else
    {
        qspi->sfa1ad += qspi->memmap_base;
    }
    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-sfa2ad", &qspi->sfa2ad))
    {
        qspi->sfa2ad = QSPI_FLASH_A2_TOP(qspi);
    }
    else
    {
        qspi->sfa2ad += qspi->sfa1ad;
    }
    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-sfb1ad", &qspi->sfb1ad))
    {
        qspi->sfb1ad = QSPI_FLASH_B1_TOP(qspi);
    }
    else
    {
        qspi->sfb1ad = qspi->sfa2ad;
    }
    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-sfb2ad", &qspi->sfb2ad))
    {
        qspi->sfb2ad = QSPI_FLASH_B2_TOP(qspi);
    }
    else
    {
        qspi->sfb2ad += qspi->sfb1ad;
    }

    /* map QSPI PMUap register address */
    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-pmuap-reg", &qspi->pmuap_reg))
    {
        qspi->pmuap_reg = PMUA_QSPI_CLK_RES_CTRL;
    }
    qspi->pmuap_addr = rt_ioremap((void *)(rt_ubase_t)qspi->pmuap_reg, 4);

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-mpmu-acgr-reg", &qspi->mpmu_acgr_reg))
    {
        qspi->mpmu_acgr_reg = K1X_MPMU_ACGR;
    }
    qspi->mpmu_acgr = rt_ioremap((void *)(rt_ubase_t)qspi->mpmu_acgr_reg, 4);

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-rx-buf", &qspi->rx_buf_size))
    {
        qspi->rx_buf_size = QSPI_RX_BUFF_MAX;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-tx-buf", &qspi->tx_buf_size))
    {
        qspi->tx_buf_size = QSPI_TX_BUFF_MAX;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-ahb-buf", &qspi->ahb_buf_size))
    {
        qspi->ahb_buf_size = QSPI_AHB_BUFF_MAX_SIZE;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-ahb-enable", &qspi->ahb_read_enable))
    {
        qspi->ahb_read_enable = 1;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-interrupt", &qspi->cmd_interrupt))
    {
        qspi->cmd_interrupt = 1;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-endian-xchg", &qspi->endian_xchg))
    {
        qspi->endian_xchg = 0;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-cs", &qspi->cs_selected))
    {
        qspi->cs_selected = QSPI_DEFAULT_CS;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-tx-dma", &qspi->tx_dma_enable))
    {
        qspi->tx_dma_enable = 0;
    }

    if (rt_dm_dev_prop_read_u32(dev, "k1x,qspi-rx-dma", &qspi->rx_dma_enable))
    {
        qspi->rx_dma_enable = 0;
    }

    rt_dm_dev_prop_read_u32(dev, "k1x,qspi-id", &qspi_bus_num);

    /* Prepare DMA */
    if (qspi->rx_dma_enable)
    {
        qspi->dma_rx = rt_dma_chan_request(dev, RT_NULL);

        if (!rt_is_err_or_null(qspi->dma_rx))
        {
            qspi->dma_rx->callback = k1x_qspi_dma_callback;

            qspi->rx_config.direction = RT_DMA_MEM_TO_MEM;
            qspi->rx_config.src_addr = qspi->memmap_base;

            qspi->rx_transfer.src_addr = qspi->rx_config.src_addr;
        }
        else
        {
            qspi->dma_rx = RT_NULL;
            qspi->rx_dma_enable = 0;
        }
    }

    if (qspi->tx_dma_enable)
    {
        qspi->dma_tx = rt_dma_chan_request(dev, "tx-dma");

        if (!rt_is_err_or_null(qspi->dma_tx))
        {
            qspi->dma_tx->callback = k1x_qspi_dma_callback;

            qspi->tx_config.direction = RT_DMA_MEM_TO_DEV;
            qspi->tx_config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
            qspi->tx_config.dst_addr = qspi->io_phys + QSPI_TBDR - 4;
            qspi->tx_config.dst_maxburst = QSPI_TX_DMA_BURST;

            qspi->tx_transfer.dst_addr = qspi->tx_config.dst_addr;
        }
        else
        {
            qspi->dma_tx = RT_NULL;
            qspi->tx_dma_enable = 0;
        }
    }

    if (qspi->dma_tx || qspi->dma_rx)
    {
        rt_completion_init(&qspi->dma_completion);
    }

    if (qspi->tx_dma_enable)
    {
        qspi->tx_unit_size = qspi->tx_buf_size;
    }
    else
    {
        qspi->tx_unit_size = qspi->tx_buf_size;
    }

    if (qspi->ahb_read_enable)
    {
        qspi->rx_unit_size = 4 * SIZE_KB;
    }
    else
    {
        qspi->rx_unit_size = qspi->rx_buf_size;
    }

    /* QSPI init start */
    base = qspi->io_map;

    qspi->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(qspi->rstc))
    {
        err = rt_ptr_err(qspi->rstc);
        goto _fail;
    }

    rt_reset_control_assert(qspi->rstc);

    /* Set PMUap */
    qspi->clk = rt_clk_get_by_name(dev, "qspi_clk");
    if (rt_is_err(qspi->clk))
    {
        err = rt_ptr_err(qspi->clk);
        goto _fail;
    }

    qspi->bus_clk = rt_clk_get_by_name(dev, "qspi_bus_clk");
    if (rt_is_err(qspi->bus_clk))
    {
        err = rt_ptr_err(qspi->bus_clk);
        goto _fail;
    }

    if ((err = rt_clk_set_rate(qspi->clk, qspi->max_hz)))
    {
        LOG_E("Fail to set clk");
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(qspi->clk)))
    {
        LOG_E("Fail to enable clk");
        goto _fail;
    }

    rt_clk_prepare_enable(qspi->bus_clk);

    rt_reset_control_deassert(qspi->rstc);

    /* Rest qspi */
    qspi_reset(qspi);

    /* Clock settings */
    qspi_enter_mode(qspi, QSPI_DISABLE_MODE);

    /* Sampled by sfif_clk_b; half cycle delay; */
    if (qspi->max_hz < (QSPI_SMPR_FSPHS_CLK >> 2))
    {
        qspi_writel(qspi, 0x0, base + QSPI_SMPR);
    }
    else
    {
        qspi_writel(qspi, QSPI_SMPR_FSPHS_MASK, base + QSPI_SMPR);
    }

    /* Fix wirte failure issue*/
    qspi_writel(qspi, 0x8, base + QSPI_SOCCR);

    /* Set the default source address QSPI_AMBA_BASE*/
    qspi_write_sfar(qspi, qspi->memmap_base);
    qspi_writel(qspi, 0x0, base + QSPI_SFACR);

    /* Config ahb read start */
    /* Disable BUF0~BUF1, use BUF3 for all masters */
    qspi_writel(qspi, 0, base + QSPI_BUF0IND);
    qspi_writel(qspi, 0, base + QSPI_BUF1IND);
    qspi_writel(qspi, 0, base + QSPI_BUF2IND);

    /* AHB Master port */
    qspi_writel(qspi, 0xe, base + QSPI_BUF0CR);
    qspi_writel(qspi, 0xe, base + QSPI_BUF1CR);
    qspi_writel(qspi, 0xe, base + QSPI_BUF2CR);
    qspi_writel(qspi,
        QSPI_BUF3CR_ALLMST_MASK | QSPI_BUF3CR_ADATSZ((qspi->ahb_buf_size / 8)),
        base + QSPI_BUF3CR);

    /* Set AHB read sequence id */
    qspi_writel(qspi,
        QSPI_BFGENCR_SEQID(SEQID_LUT_AHBREAD_ID),
        base + QSPI_BFGENCR);
    /* Config ahb read end */

    /* Set flash memory map */
    qspi_writel(qspi, qspi->sfa1ad & 0xfffffc00, base + QSPI_SFA1AD);
    qspi_writel(qspi, qspi->sfa2ad & 0xfffffc00, base + QSPI_SFA2AD);
    qspi_writel(qspi, qspi->sfb1ad & 0xfffffc00, base + QSPI_SFB1AD);
    qspi_writel(qspi, qspi->sfb2ad & 0xfffffc00, base + QSPI_SFB2AD);

    /* ISD3FB, ISD2FB, ISD3FA, ISD2FA = 1; END_CFG=0x3 */
    reg = qspi_readl(qspi, base + QSPI_MCR);
    reg |= QSPI_MCR_END_CFG_MASK | QSPI_MCR_ISD_MASK;
    qspi_writel(qspi, reg, base + QSPI_MCR);

    /* Module enabled */
    qspi_enter_mode(qspi, QSPI_NORMAL_MODE);

    /* Read using the IP Bus registers QSPI_RBDR0 to QSPI_RBDR31*/
    qspi_write_rbct(qspi, QSPI_RBCT_RXBRD_MASK);

    /* Clear all interrupt status */
    qspi_writel(qspi, 0xffffffff, base + QSPI_FR);
    /* QSPI init end */

    rt_completion_init(&qspi->cmd_completion);

    dev->user_data = qspi;

    qspi->parent.parent.ofw_node = dev->ofw_node;

    rt_dm_dev_set_name(&qspi->parent.parent, "qspi%d", qspi_bus_num);
    bus_name = rt_dm_dev_get_name(&qspi->parent.parent);

    rt_hw_interrupt_install(qspi->irq, k1x_qspi_isr, qspi, bus_name);
    rt_hw_interrupt_umask(qspi->irq);

    if ((err = rt_qspi_bus_register(&qspi->parent, bus_name, &k1x_qspi_ops)))
    {
        goto _fail;
    }

    return RT_EOK;
_fail:
    k1x_qspi_free(qspi, dev);

    return err;
}

static rt_err_t k1x_qspi_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct k1x_qspi *qspi = dev->user_data;

    rt_hw_interrupt_mask(qspi->irq);
    rt_pic_detach_irq(qspi->irq, qspi);

    rt_device_unregister(&qspi->parent.parent);

    k1x_qspi_free(qspi, dev);

    return RT_EOK;
}

static const struct rt_ofw_node_id k1x_qspi_ofw_ids[] =
{
    { .compatible = "spacemit,k1x-qspi", },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_qspi_driver =
{
    .name = "k1x-qspi",
    .ids = k1x_qspi_ofw_ids,

    .probe = k1x_qspi_probe,
    .remove = k1x_qspi_remove,
};
RT_PLATFORM_DRIVER_EXPORT(k1x_qspi_driver);
