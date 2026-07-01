/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

/**
 * @file dma-pl330.c
 * @brief ARM PL330 DMA Controller (DMA-330) driver
 *
 * Implements a DMA controller driver for the ARM PrimeCell PL330
 * (also known as DMA-330). The PL330 uses a programmable microcode
 * engine to execute DMA transfers. This driver generates microcode
 * sequences for memcpy, cyclic, and single transfers on-the-fly.
 *
 * Key features:
 * - Microcode generation for DMAMOV, DMALD, DMAST, DMALP, DMAEND
 *   DMAWFE, DMASEV instructions
 * - Busrt size and width configuration from DMA slave config
 * - Nested loop support for transfers exceeding 256 burst iterations
 * - Cyclic (infinite loop) transfers with periodic callbacks
 * - Debug instruction interface for starting and killing channels
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <bitmap.h>

#define DBG_TAG "dma.pl330"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/** @brief Extract a bit field from a register value */
#define _FIELD_READ(h, l, x) ((RT_GENMASK(h, l) & (x)) >> l)

/** @brief DMA Manager Status Register */
#define PL330_REG_DSR 0x000
/** @brief DMA Program Counter Register */
#define PL330_REG_DPC 0x004
/** @brief Interrupt Enable Register */
#define PL330_REG_INTEN 0x020
/** @brief Event-Interrupt Raw Status Register */
#define PL330_REG_INT_EVENT_RIS 0x024
/** @brief Interrupt Status Register */
#define PL330_REG_INTMIS 0x028
/** @brief Interrupt Clear Register */
#define PL330_REG_INTCLR 0x02c
/** @brief Fault Status DMA Manager Register */
#define PL330_REG_FSRD 0x030
/** @brief Fault Status DMA Channel Register */
#define PL330_REG_FSRC 0x034
/** @brief Fault Type DMA Manager Register */
#define PL330_REG_FTRD 0x038
/** @brief Fault Type DMA Channel [n] Register */
#define PL330_REG_FTR(n) (0x040 + (n) * 0x4)
/** @brief Undefined instruction fault flag */
#define PL330_FT_UNDEF_INSTR RT_BIT(0)
/** @brief Invalid operand fault flag */
#define PL330_FT_OPERAND_INVALID RT_BIT(1)
/** @brief DMAGO error fault flag */
#define PL330_FT_DMAGO_ERR RT_BIT(4)
/** @brief Event error fault flag */
#define PL330_FT_EVENT_ERR RT_BIT(5)
/** @brief Channel peripheral error fault flag */
#define PL330_FT_CH_PERIPH_ERR RT_BIT(6)
/** @brief Channel read/write error fault flag */
#define PL330_FT_CH_RDWR_ERR RT_BIT(7)
/** @brief Store data unavailable fault flag */
#define PL330_FT_ST_DATA_UNAVAILABLE RT_BIT(12)
/** @brief FIFO empty error fault flag */
#define PL330_FT_FIFOEMPTY_ERR RT_BIT(13)
/** @brief Instruction fetch error fault flag */
#define PL330_FT_INSTR_FETCH_ERR RT_BIT(16)
/** @brief Data write error fault flag */
#define PL330_FT_DATA_WRITE_ERR RT_BIT(17)
/** @brief Data read error fault flag */
#define PL330_FT_DATA_READ_ERR RT_BIT(18)
/** @brief Debug instruction fault flag */
#define PL330_FT_DBG_INSTR RT_BIT(30)
/** @brief Lockup error fault flag */
#define PL330_FT_LOCKUP_ERR RT_BIT(31)
/** @brief Channel [n] Status Register */
#define PL330_REG_CSR(n) (0x100 + (n) * 0x8)
/** @brief Channel stopped */
#define PL330_CS_STOP 0x0
/** @brief Channel executing */
#define PL330_CS_EXEC 0x1
/** @brief Channel cache miss */
#define PL330_CS_CMISS 0x2
/** @brief Channel updating PC */
#define PL330_CS_UPDTPC 0x3
/** @brief Channel waiting for event */
#define PL330_CS_WFE 0x4
/** @brief Channel at barrier */
#define PL330_CS_ATBRR 0x5
/** @brief Channel queue busy */
#define PL330_CS_QBUSY 0x6
/** @brief Channel waiting for peripheral */
#define PL330_CS_WFP 0x7
/** @brief Channel killed */
#define PL330_CS_KILL 0x8
/** @brief Channel completed */
#define PL330_CS_CMPLT 0x9
/** @brief Channel fault completed */
#define PL330_CS_FLTCMP 0xe
/** @brief Channel fault */
#define PL330_CS_FAULT 0xf
/** @brief Channel [n] Program Counter Register */
#define PL330_REG_CPC(n) (0x104 + (n) * 0x8)
/** @brief Channel [n] Source Address Register */
#define pl330_REG_SAR(n) (0x0400 + (n) * 0x20)
/** @brief Channel [n] Destination Address Register */
#define pl330_REG_DAR(n) (0x0404 + (n) * 0x20)
/** @brief Channel [n] Channel Control Register */
#define pl330_REG_CCR(n) (0x0408 + (n) * 0x20)
/** @brief Channel [n] Loop Counter 0 Register */
#define pl330_REG_LC0(n) (0x040c + (n) * 0x20)
/** @brief Channel [n] Loop Counter 1 Register */
#define pl330_REG_LC1(n) (0x0410 + (n) * 0x20)
/** @brief Debug Status Register */
#define PL330_REG_DBGSTATUS 0xd00
/** @brief Debug unit idle */
#define PL330_DBGSTATUS_IDLE 0
/** @brief Debug unit busy */
#define PL330_DBGSTATUS_BUSY RT_BIT(0)
/** @brief Debug Command Register */
#define PL330_REG_DBGCMD 0xd04
/** @brief Debug Instruction-0 Register */
#define PL330_REG_DBGINST0 0xd08
/** @brief Debug Instruction-1 Register */
#define PL330_REG_DBGINST1 0xd0c
/** @brief Configuration Register [n] */
#define PL330_REG_CR(n) (0xe00 + (n) * 0x4)
/** @brief Peripheral request set at reset */
#define PL330_CR0_PERIPH_REQ_SET RT_BIT(0)
/** @brief Manager non-secure at reset flag */
#define PL330_CR0_MGR_NS_AT_RST(x) _FIELD_READ(2, 2, x)
/** @brief Number of channels field */
#define PL330_CR0_NUM_CHNLS(x) _FIELD_READ(6, 4, x)
/** @brief Number of peripherals field */
#define PL330_CR0_NUM_PERIPH(x) _FIELD_READ(16, 12, x)
/** @brief Number of events field */
#define PL330_CR0_NUM_EVENTS(x) _FIELD_READ(21, 17, x)
/** @brief Configuration Data Register */
#define PL330_REG_CRD 0x0e14
/** @brief Data width field */
#define PL330_CRD_DATA_WIDTH(x) _FIELD_READ(2, 0, x)
/** @brief Write capability field */
#define PL330_CRD_WR_CAP(x) _FIELD_READ(6, 4, x)
/** @brief Write queue depth field */
#define PL330_CRD_WR_Q_DEP(x) _FIELD_READ(11, 8, x)
/** @brief Read capability field */
#define PL330_CRD_RD_CAP(x) _FIELD_READ(14, 12, x)
/** @brief Read queue depth field */
#define PL330_CRD_RD_Q_DEP(x) _FIELD_READ(19, 16, x)
/** @brief Data buffer depth field */
#define PL330_CRD_DATA_BUFFER_DEP(x) _FIELD_READ(29, 20, x)
/** @brief DMA Watchdog Register */
#define PL330_REG_WDT 0x0e80
/** @brief Peripheral ID Register */
#define PL330_REG_PERIPH_ID 0x0fe0
/** @brief Peripheral revision field */
#define PL330_PERIPH_REV(x) _FIELD_READ(23, 20, x)
/** @brief PL330 revision r0p0 */
#define PL330_PERIPH_REV_R0P0 0
/** @brief PL330 revision r1p0 */
#define PL330_PERIPH_REV_R1P0 1
/** @brief PL330 revision r1p1 */
#define PL330_PERIPH_REV_R1P1 2

/** @brief Microcode instruction: add halfword to address */
#define PL330_CMD_DMAADDH 0x54
/** @brief Microcode instruction: end program */
#define PL330_CMD_DMAEND 0x00
/** @brief Microcode instruction: flush pipeline */
#define PL330_CMD_DMAFLUSHP 0x35
/** @brief Microcode instruction: go (execute channel) */
#define PL330_CMD_DMAGO 0xa0
/** @brief Microcode instruction: load (read from source) */
#define PL330_CMD_DMALD 0x04
/** @brief Microcode instruction: load peripheral */
#define PL330_CMD_DMALDP 0x25
/** @brief Microcode instruction: loop */
#define PL330_CMD_DMALP 0x20
/** @brief Microcode instruction: loop end */
#define PL330_CMD_DMALPEND 0x28
/** @brief Microcode instruction: kill */
#define PL330_CMD_DMAKILL 0x01
/** @brief Microcode instruction: move immediate */
#define PL330_CMD_DMAMOV 0xbc
/** @brief Microcode instruction: no operation */
#define PL330_CMD_DMANOP 0x18
/** @brief Microcode instruction: memory barrier */
#define PL330_CMD_DMARMB 0x12
/** @brief Microcode instruction: send event */
#define PL330_CMD_DMASEV 0x34
/** @brief Microcode instruction: store (write to dest) */
#define PL330_CMD_DMAST 0x08
/** @brief Microcode instruction: store peripheral */
#define PL330_CMD_DMASTP 0x29
/** @brief Microcode instruction: store zero */
#define PL330_CMD_DMASTZ 0x0c
/** @brief Microcode instruction: wait for event */
#define PL330_CMD_DMAWFE 0x36
/** @brief Microcode instruction: wait for peripheral */
#define PL330_CMD_DMAWFP 0x30
/** @brief Microcode instruction: write memory barrier */
#define PL330_CMD_DMAWMB 0x13

/** @brief Microcode instruction sizes */
#define PL330_SIZE_DMAADDH 3
#define PL330_SIZE_DMAEND 1
#define PL330_SIZE_DMAFLUSHP 2
#define PL330_SIZE_DMALD 1
#define PL330_SIZE_DMALDP 2
#define PL330_SIZE_DMALP 2
#define PL330_SIZE_DMALPEND 2
#define PL330_SIZE_DMAKILL 1
#define PL330_SIZE_DMAMOV 6
#define PL330_SIZE_DMANOP 1
#define PL330_SIZE_DMARMB 1
#define PL330_SIZE_DMASEV 2
#define PL330_SIZE_DMAST 1
#define PL330_SIZE_DMASTP 2
#define PL330_SIZE_DMASTZ 1
#define PL330_SIZE_DMAWFE 2
#define PL330_SIZE_DMAWFP 2
#define PL330_SIZE_DMAWMB 1
#define PL330_SIZE_DMAGO 6

/** @brief DMAMOV to Source Address Register */
#define PL330_DIR_SAR 0
/** @brief DMAMOV to Channel Control Register */
#define PL330_DIR_CCR 1
/** @brief DMAMOV to Destination Address Register */
#define PL330_DIR_DAR 2

/** @brief Source address increment flag in CCR */
#define PL330_SRC_INC RT_BIT(0)
/** @brief Source burst size shift in CCR */
#define PL330_SRC_BURST_SIZE_SHIFT 1
/** @brief Source burst length shift in CCR */
#define PL330_SRC_BURST_LEN_SHIFT 4
/** @brief Destination address increment flag in CCR */
#define PL330_DST_INC RT_BIT(14)
/** @brief Destination burst size shift in CCR */
#define PL330_DST_BURST_SIZE_SHIFT 15
/** @brief Destination burst length shift in CCR */
#define PL330_DST_BURST_LEN_SHIFT 18

/** @brief Single transfer condition */
#define PL330_COND_SINGLE 0
/** @brief Burst transfer condition */
#define PL330_COND_BURST 1
/** @brief Always execute (unconditional) */
#define PL330_COND_ALWAYS 2

/** @brief Maximum microcode program size in bytes (128 instructions) */
#define PL330_MICROCODE_SIZE 128
/** @brief Maximum number of AMBA IRQs */
#define AMBA_NR_IRQS 9

/**
 * @brief PL330 DMA channel descriptor
 *
 * Extends the generic DMA channel with microcode buffer management.
 * The microcode is generated at prep time and stored in microcode_raw
 * with alignment padding.
 */
struct pl330_chan
{
    struct rt_dma_chan parent;                       /**< Generic DMA channel */

    rt_bool_t enabled;                               /**< Channel is currently in use */
    rt_size_t size;                                  /**< Transfer size for callback reporting */

    void *microcode;                                 /**< Aligned microcode buffer pointer */
    rt_size_t microcode_len;                         /**< Microcode length in bytes */
    rt_ubase_t microcode_dma;                        /**< Physical address of microcode buffer */
    rt_uint8_t microcode_raw[PL330_MICROCODE_SIZE + 4]; /**< Raw microcode storage (+4 for alignment) */
};

/**
 * @brief PL330 DMA controller private data
 */
struct pl330
{
    struct rt_dma_controller parent;                 /**< Generic DMA controller */

    void *regs;                                      /**< MMIO register base */
    int irqs_nr;                                     /**< Number of IRQ lines */
    int irqs[AMBA_NR_IRQS];                          /**< IRQ numbers */

#define PL330_QUIRK_BROKEN_NO_FLUSHP RT_BIT(0)    /**< Quirk: broken FLUSHP instruction */
#define PL330_QUIRK_PERIPH_BURST     RT_BIT(1)    /**< Quirk: peripheral burst support */
    rt_uint32_t quirk;                               /**< Hardware quirk flags */

    rt_uint32_t mode_ns;                             /**< Non-secure mode flag */
    rt_uint32_t num_chan;                            /**< Number of DMA channels */
    rt_uint32_t num_peri;                            /**< Number of peripheral interfaces */
    rt_uint32_t num_events;                          /**< Number of event interfaces */
    rt_uint32_t data_width;                          /**< Data bus width in bits */
    rt_uint32_t data_buffer_dep;                     /**< Data buffer depth in entries */
    rt_uint32_t ins;                                 /**< Instruction space configuration */

    struct pl330_chan *chans;                        /**< Array of channel descriptors */

    struct rt_clk *pclk;                             /**< APB peripheral clock */
    struct rt_reset_control *rstc;                   /**< DMA reset control */
    struct rt_reset_control *rstc_ocp;               /**< OCP (Open Core Protocol) reset control */
};
/** @brief Cast from rt_dma_controller to pl330 */
#define raw_to_pl330(raw) rt_container_of(raw, struct pl330, parent)

/**
 * @brief Read PL330 configuration from hardware registers
 *
 * Extracts channel count, event count, peripheral count, data width,
 * and data buffer depth from the configuration registers (CR0, CRD).
 *
 * @param[in] pl330  PL330 controller instance (updated in place)
 */
static void pl330_read_config(struct pl330 *pl330)
{
    rt_uint32_t value;
    void *regs = pl330->regs;

    value = HWREG32(regs + PL330_REG_CR(0));
    pl330->mode_ns = !!PL330_CR0_NUM_EVENTS(value);
    pl330->num_chan = PL330_CR0_NUM_CHNLS(value) + 1;
    pl330->num_events = PL330_CR0_NUM_EVENTS(value) + 1;

    if (value & PL330_CR0_PERIPH_REQ_SET)
    {
        pl330->num_peri = PL330_CR0_NUM_PERIPH(value) + 1;
    }

    value = HWREG32(regs + PL330_REG_CRD);
    pl330->data_width = 8 * (1 << PL330_CRD_DATA_WIDTH(value));
    pl330->data_buffer_dep = PL330_CRD_DATA_BUFFER_DEP(value) + 1;

    pl330->ins = HWREG32(regs + PL330_REG_CR(3));
}

/**
 * @brief Configure the PL330 Channel Control Register value from a slave config
 *
 * Sets source/destination increment, burst sizes, and address widths
 * based on the DMA slave configuration.
 *
 * @param[in]  conf  DMA slave configuration
 * @param[out] ccr   Computed CCR value
 *
 * @return RT_EOK on success, -RT_EINVAL if address width is unsupported
 */
static rt_err_t pl330_ccr_config(struct rt_dma_slave_config *conf, rt_uint32_t *ccr)
{
    *ccr = PL330_SRC_INC | PL330_DST_INC;
    *ccr |= conf->src_maxburst << PL330_SRC_BURST_LEN_SHIFT;
    *ccr |= conf->dst_maxburst << PL330_DST_BURST_LEN_SHIFT;

    switch (conf->src_addr_width)
    {
    case RT_DMA_SLAVE_BUSWIDTH_1_BYTE:
        *ccr |= 0 << PL330_SRC_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_2_BYTES:
        *ccr |= 1 << PL330_SRC_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_4_BYTES:
        *ccr |= 2 << PL330_SRC_BURST_SIZE_SHIFT;
        break;

    default:
        return -RT_EINVAL;
    }

    switch (conf->dst_addr_width)
    {
    case RT_DMA_SLAVE_BUSWIDTH_1_BYTE:
        *ccr |= 0 << PL330_DST_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_2_BYTES:
        *ccr |= 1 << PL330_DST_BURST_SIZE_SHIFT;
        break;
    case RT_DMA_SLAVE_BUSWIDTH_4_BYTES:
        *ccr |= 2 << PL330_DST_BURST_SIZE_SHIFT;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

/**
 * @brief Emit a DMAMOV microcode instruction
 *
 * DMAMOV writes an immediate 32-bit value to a register (SAR, CCR, or DAR).
 * Encoding: 6 bytes.
 *
 * @param[in] microcode  Output buffer (advanced by 6 bytes)
 * @param[in] rd         Destination register (PL330_DIR_SAR/CCR/DAR)
 * @param[in] imm        32-bit immediate value
 *
 * @return Number of bytes written (always 6)
 */
static int pl330_cmd_dmamov(rt_uint8_t *microcode, rt_uint8_t rd, rt_uint32_t imm)
{
    /*
     * DMAMOV encoding
     * 15 4 3 2 1 10 ... 8 7 6 5 4 3 2 1 0
     *  0 0 0 0 0 |rd[2:0]|1 0 1 1 1 1 0 0
     *
     * 47 ... 16
     *  imm[32:0]
     *
     * rd: b000 for SAR, b001 CCR, b010 DAR
     */

    *microcode++ = PL330_CMD_DMAMOV;
    *microcode++ = rd;
    *microcode++ = imm;
    *microcode++ = imm >> 8;
    *microcode++ = imm >> 16;
    *microcode++ = imm >> 24;

    LOG_D("DMAMOV %s, %#x", ((const char * const[]){ [PL330_DIR_SAR] = "SAR", [PL330_DIR_CCR] = "CCR", [PL330_DIR_DAR] = "DAR" })[rd], imm);

    return PL330_SIZE_DMAMOV;
}

/**
 * @brief Emit a DMALD microcode instruction
 *
 * DMALD loads data from the source address. Condition codes:
 * - SINGLE: single transfer, end if last
 * - BURST: burst transfer, end if last
 * - ALWAYS: unconditional (no end check)
 *
 * @param[in] microcode  Output buffer (advanced by 1 byte)
 * @param[in] cond       Transfer condition (PL330_COND_*)
 *
 * @return Number of bytes written (always 1)
 */
static int pl330_cmd_dmald(rt_uint8_t *microcode, rt_uint32_t cond)
{
    /*
     * DMALD encoding
     * 7 6 5 4 3 2 1  0
     * 0 0 0 0 0 1 bs x
     */
    *microcode = PL330_CMD_DMALD;

    if (cond == PL330_COND_SINGLE)
    {
        *microcode |= (0 << 1) | (1 << 0);
    }
    else if (cond == PL330_COND_BURST)
    {
        *microcode |= (1 << 1) | (1 << 0);
    }

    LOG_D("DMALD %c", ((char[]){
                          [PL330_COND_SINGLE] = 'S',
                          [PL330_COND_BURST] = 'B',
                          [PL330_COND_ALWAYS] = 'A' })[cond]);

    return PL330_SIZE_DMALD;
}

/**
 * @brief Emit a DMAST microcode instruction
 *
 * DMAST stores data to the destination address. Same condition
 * semantics as DMALD.
 *
 * @param[in] microcode  Output buffer (advanced by 1 byte)
 * @param[in] cond       Transfer condition
 *
 * @return Number of bytes written (always 1)
 */
static int pl330_cmd_dmast(rt_uint8_t *microcode, rt_uint32_t cond)
{
    /*
     * DMAST encoding
     * 7 6 5 4 3 2 1  0
     * 0 0 0 0 1 0 bs x
     */
    *microcode = PL330_CMD_DMAST;

    if (cond == PL330_COND_SINGLE)
    {
        *microcode |= (0 << 1) | (1 << 0);
    }
    else if (cond == PL330_COND_BURST)
    {
        *microcode |= (1 << 1) | (1 << 0);
    }

    LOG_D("DMAST %c", ((char[]){
                          [PL330_COND_SINGLE] = 'S',
                          [PL330_COND_BURST] = 'B',
                          [PL330_COND_ALWAYS] = 'A' })[cond]);

    return PL330_SIZE_DMAST;
}

/**
 * @brief Emit a DMALP (loop begin) microcode instruction
 *
 * Sets up a counted loop using one of the two loop counters (LC0 or LC1).
 * The loop body follows immediately after.
 *
 * @param[in] microcode  Output buffer (advanced by 2 bytes)
 * @param[in] lc         Loop counter index (0 or 1)
 * @param[in] loops      Number of iterations (1-256, stored as loops-1)
 *
 * @return Number of bytes written (always 2)
 */
static int pl330_cmd_dmalp(rt_uint8_t *microcode, rt_uint8_t lc, rt_uint16_t loops)
{
    /*
     * DMALP encoding
     * 15   ...   8 7 6 5 4 3 2 1  0
     * | iter[7:0] |0 0 1 0 0 0 lc 0
     */
    *microcode++ = PL330_CMD_DMALP | ((lc & 1) << 1);
    *microcode |= loops - 1;

    LOG_D("DMALP %u (lc: %c)", loops - 1, lc ? '1' : '0');

    return PL330_SIZE_DMALP;
}

/**
 * @brief Emit a DMALPEND (loop end) microcode instruction
 *
 * Closes a loop by branching back to the DMALP instruction. Supports:
 * - Forever loops (nf=0): never terminates
 * - Conditional termination based on loop counter
 * - Non-forever loops (nf=1): terminates when counter reaches 0
 *
 * @param[in] microcode  Output buffer (advanced by 2 bytes)
 * @param[in] cond       Loop termination condition
 * @param[in] forever    RT_TRUE for infinite loop, RT_FALSE for counted
 * @param[in] loop       Which loop counter to test (0=LC0, 1=LC1)
 * @param[in] bjump      Backward jump offset in bytes
 *
 * @return Number of bytes written (always 2)
 */
static int pl330_cmd_dmalpend(rt_uint8_t *microcode, rt_uint32_t cond,
                              rt_bool_t forever, rt_uint32_t loop, rt_uint8_t bjump)
{
    /*
     * DMALPEND encoding
     * 15       ...        8 7 6 5 4  3 2  1  0
     * | backward_jump[7:0] |0 0 1 nf 1 lc bs x
     */
    *microcode = PL330_CMD_DMALPEND;

    if (loop)
    {
        *microcode |= (1 << 2);
    }

    if (!forever)
    {
        *microcode |= (1 << 4);
    }

    if (cond == PL330_COND_SINGLE)
    {
        *microcode |= (0 << 1) | (1 << 0);
    }
    else if (cond == PL330_COND_BURST)
    {
        *microcode |= (1 << 1) | (1 << 0);
    }

    ++microcode;

    *microcode = bjump;

    LOG_D("DMALPEND %c (%sloop: %c bjump: %d)", ((char[]){ [PL330_COND_SINGLE] = 'S', [PL330_COND_BURST] = 'B', [PL330_COND_ALWAYS] = 'A' })[cond], forever ? "FE, " : "", loop ? 'Y' : 'N', bjump);

    return PL330_SIZE_DMALPEND;
}

/**
 * @brief Emit a DMASEV microcode instruction
 *
 * Sends an event to the specified event interface, triggering an
 * interrupt on the IRQ line corresponding to the channel.
 *
 * @param[in] microcode  Output buffer (advanced by 2 bytes)
 * @param[in] event      Event number (0-31)
 *
 * @return Number of bytes written (always 2)
 */
static int pl330_cmd_dmasev(rt_uint8_t *microcode, int event)
{
    *microcode++ = PL330_CMD_DMASEV;
    *microcode++ = (event & 0x1f) << 3;

    LOG_D("DMASEV %u", event & 0x1f);

    return PL330_SIZE_DMASEV;
}

/**
 * @brief Emit a DMAEND microcode instruction
 *
 * Terminates the microcode program and signals completion.
 *
 * @param[in] microcode  Output buffer (advanced by 1 byte)
 *
 * @return Number of bytes written (always 1)
 */
static int pl330_cmd_dmaend(rt_uint8_t *microcode)
{
    /*
     * DMAEND encoding:
     * 7 6 5 4 3 2 1 0
     * 0 0 0 0 0 0 0 0
     */
    *microcode = PL330_CMD_DMAEND;

    LOG_D("DMAEND");

    return PL330_SIZE_DMAEND;
}

/**
 * @brief Get the hardware channel ID from a pl330_chan pointer
 *
 * @param[in] pl330  PL330 controller
 * @param[in] pc     Channel descriptor
 *
 * @return Zero-based channel index
 */
static rt_uint32_t pl330_chan_id(struct pl330 *pl330, struct pl330_chan *pc)
{
    return pc - pl330->chans;
}

/**
 * @brief Request a DMA channel from the PL330 controller
 *
 * If fw_data (device tree args) specifies a channel number, that
 * specific channel is requested. Otherwise any unallocated channel
 * is used. Marks the channel as enabled and unmasks its IRQ.
 *
 * @param[in] ctrl   DMA controller
 * @param[in] slave  Requesting device
 * @param[in] fw_data Device tree cell args (may be NULL for mem-to-mem)
 *
 * @return DMA channel pointer, or RT_NULL/error pointer on failure
 */
static struct rt_dma_chan *pl330_dma_request_chan(struct rt_dma_controller *ctrl,
                                                  struct rt_device *slave, void *fw_data)
{
    int idx = -1;
    struct pl330_chan *pc;
    struct pl330 *pl330 = raw_to_pl330(ctrl);
    struct rt_ofw_cell_args *args = fw_data;

    if (args && (idx = args->args[0]) >= pl330->num_chan)
    {
        return rt_err_ptr(-RT_EINVAL);
    }

    if (idx >= 0)
    {
        pc = &pl330->chans[idx];

        if (pc->enabled)
        {
            return rt_err_ptr(-RT_EBUSY);
        }
    }
    else
    {
        /*
         * Memory to Memory is often called after after DM has been initialized,
         * So just return unused chan
         */
        for (int i = 0; i < pl330->num_chan; ++i)
        {
            pc = &pl330->chans[i];

            if (!pc->enabled)
            {
                goto _found;
            }
        }

        return RT_NULL;
    }

_found:
    pc->enabled = RT_TRUE;
    HWREG32(pl330->regs + PL330_REG_INTEN) |= RT_BIT(pl330_chan_id(pl330, pc));

    return &pc->parent;
}

/**
 * @brief Release a previously requested PL330 DMA channel
 *
 * @param[in] chan  DMA channel to release
 *
 * @return RT_EOK
 */
static rt_err_t pl330_dma_release_chan(struct rt_dma_chan *chan)
{
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);

    pc->enabled = RT_FALSE;

    return RT_EOK;
}

/**
 * @brief Start a DMA transfer on a PL330 channel
 *
 * Waits for the debug unit to become idle, flushes the microcode
 * buffer from cache, and issues a DMAGO instruction via the debug
 * registers.
 *
 * @param[in] chan  DMA channel (must be prepared)
 *
 * @return RT_EOK
 */
static rt_err_t pl330_dma_start(struct rt_dma_chan *chan)
{
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);

    while (HWREG32(pl330->regs + PL330_REG_DBGSTATUS) & PL330_DBGSTATUS_BUSY)
    {
        rt_hw_cpu_relax();
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, pc->microcode, pc->microcode_len);

    HWREG32(pl330->regs + PL330_REG_DBGINST0) = ((pl330_chan_id(pl330, pc) + 1) << 8) | (PL330_CMD_DMAGO << 16);
    HWREG32(pl330->regs + PL330_REG_DBGINST1) = pc->microcode_dma;
    HWREG32(pl330->regs + PL330_REG_DBGCMD) = 0;

    return RT_EOK;
}

/**
 * @brief Stop a DMA transfer on a PL330 channel
 *
 * Issues a DMAKILL instruction via the debug registers to abort
 * the channel's current transfer.
 *
 * @param[in] chan  DMA channel to stop
 *
 * @return RT_EOK
 */
static rt_err_t pl330_dma_stop(struct rt_dma_chan *chan)
{
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);

    while (HWREG32(pl330->regs + PL330_REG_DBGSTATUS) & PL330_DBGSTATUS_BUSY)
    {
        rt_hw_cpu_relax();
    }

    HWREG32(pl330->regs + PL330_REG_DBGINST0) = ((pl330_chan_id(pl330, pc) + 1) << 8) | PL330_CMD_DMAKILL;
    HWREG32(pl330->regs + PL330_REG_DBGINST1) = 0;
    HWREG32(pl330->regs + PL330_REG_DBGCMD) = 0;

    return RT_EOK;
}

/**
 * @brief Configure a PL330 DMA channel (no-op for PL330)
 *
 * The PL330 applies configuration at prep time via CCR values
 * embedded in the microcode. No separate config step is needed.
 *
 * @param[in] chan  DMA channel
 * @param[in] conf  Slave configuration (unused)
 *
 * @return RT_EOK
 */
static rt_err_t pl330_dma_config(struct rt_dma_chan *chan,
                                 struct rt_dma_slave_config *conf)
{
    return RT_EOK;
}

/**
 * @brief Prepare a memory-to-memory transfer on a PL330 channel
 *
 * Generates microcode:
 *   DMAMOV CCR, <ccr_value>
 *   DMAMOV SAR, <src_addr>
 *   DMAMOV DAR, <dst_addr>
 *   DMALP  1, <outer>         ; outer loop
 *   DMALP  0, <inner_first>   ; inner loop (up to 256 bursts)
 *   DMALD  A                  ; load burst from source
 *   DMAST  A                  ; store burst to dest
 *   DMALPEND                  ; end inner loop
 *   [remainder loop if len > 256 bursts]
 *   DMALPEND                  ; end outer loop
 *   DMASEV <channel_id>       ; signal completion interrupt
 *   DMAEND
 *
 * @param[in] chan          DMA channel
 * @param[in] dma_addr_src  Source physical address
 * @param[in] dma_addr_dst  Destination physical address
 * @param[in] len           Transfer length in bytes
 *
 * @return RT_EOK on success, -RT_EINVAL if parameters are invalid
 */
static rt_err_t pl330_dma_prep_memcpy(struct rt_dma_chan *chan,
                                      rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len)
{
    void *mc;
    rt_err_t err;
    rt_uint32_t value;
    rt_size_t burst_bytes;
    rt_uint8_t ljmp_inner, ljmp_outer;
    rt_uint16_t loop, outer, rem, inner_first;
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);
    struct rt_dma_slave_config *conf = &chan->conf;

    mc = pc->microcode;

    if ((err = pl330_ccr_config(conf, &value)))
    {
        return err;
    }
    mc += pl330_cmd_dmamov(mc, PL330_DIR_CCR, value);

    mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, dma_addr_src);

    mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, dma_addr_dst);

    burst_bytes = conf->src_addr_width * conf->src_maxburst;

    if (!burst_bytes || !len)
    {
        return -RT_EINVAL;
    }

    if (len % burst_bytes)
    {
        LOG_E("Memcpy len(%lu) must be multiple of burst(%lu)", len, burst_bytes);
        return -RT_EINVAL;
    }

    /* Total iterations */
    loop = len / burst_bytes;
    if (loop == 0)
    {
        return -RT_EINVAL;
    }

    outer = loop / 256;
    rem = loop % 256;

    if (outer == 0)
    {
        outer = 1;
    }

    inner_first = (loop < 256) ? loop : 256;

    mc += pl330_cmd_dmalp(mc, 1, outer);
    ljmp_outer = mc - pc->microcode;

    mc += pl330_cmd_dmalp(mc, 0, inner_first);
    ljmp_inner = mc - pc->microcode;

    mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
    mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS, RT_FALSE, 0,
                             mc - pc->microcode - ljmp_inner);

    if (rem && loop > 256)
    {
        rt_uint8_t ljmp_inner2;

        mc += pl330_cmd_dmalp(mc, 0, rem);
        ljmp_inner2 = mc - pc->microcode;

        mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
        mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

        mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS, RT_FALSE, 0,
                                 mc - pc->microcode - ljmp_inner2);
    }

    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS, RT_FALSE, 1,
                             mc - pc->microcode - ljmp_outer);

    mc += pl330_cmd_dmasev(mc, pl330_chan_id(pl330, pc));

    mc += pl330_cmd_dmaend(mc);

    pc->size = len;
    pc->microcode_len = mc - pc->microcode;

    return RT_EOK;
}

/**
 * @brief Prepare a cyclic (infinite loop) transfer on a PL330 channel
 *
 * Generates microcode with an infinite outer loop and a finite inner loop
 * per period. Each period completion triggers a DMASEV interrupt.
 *
 * Microcode structure:
 *   DMAMOV CCR, ...
 *   DMAMOV SAR/DAR, ...
 *   DMALP  1, 0             ; infinite outer loop
 *   DMALP  0, <period_loop> ; inner loop per period
 *   DMALD  A
 *   DMAST  A
 *   DMALPEND                ; end inner loop
 *   DMASEV <channel_id>     ; signal period done
 *   DMALPEND                ; end outer loop (forever)
 *
 * @param[in] chan          DMA channel
 * @param[in] dma_buf_addr  Buffer address for device-side data
 * @param[in] buf_len       Total buffer length in bytes
 * @param[in] period_len    Bytes per period
 * @param[in] dir           Transfer direction (MEM_TO_DEV or DEV_TO_MEM)
 *
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters
 */
static rt_err_t pl330_dma_prep_cyclic(struct rt_dma_chan *chan,
                                      rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
                                      enum rt_dma_transfer_direction dir)
{
    void *mc;
    rt_err_t err;
    rt_uint32_t ccr_val;
    rt_size_t burst_bytes;
    rt_uint16_t period_loop, total_periods;
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);
    struct rt_dma_slave_config *conf = &chan->conf;

    mc = pc->microcode;

    if ((err = pl330_ccr_config(conf, &ccr_val)))
    {
        return err;
    }

    mc += pl330_cmd_dmamov(mc, PL330_DIR_CCR, ccr_val);

    if (dir == RT_DMA_MEM_TO_DEV)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, dma_buf_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, conf->dst_addr);
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, conf->src_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, dma_buf_addr);
    }

    burst_bytes = conf->src_addr_width * conf->src_maxburst;
    if (!burst_bytes)
    {
        return -RT_EINVAL;
    }

    if (period_len % burst_bytes)
    {
        return -RT_EINVAL;
    }

    if (buf_len % period_len)
    {
        return -RT_EINVAL;
    }

    period_loop = period_len / burst_bytes;

    if (period_loop == 0 || period_loop > 255)
    {
        return -RT_EINVAL;
    }

    total_periods = buf_len / period_len;
    if (total_periods == 0)
    {
        return -RT_EINVAL;
    }

    /* Outer Loop */
    mc += pl330_cmd_dmalp(mc, 1 /* LC1 */, 0 /* Infinite loop */);
    rt_uint8_t outer_ljmp = mc - pc->microcode;

    /* Inner Loop */
    mc += pl330_cmd_dmalp(mc, 0 /* LC0 */, period_loop);
    rt_uint8_t inner_ljmp = mc - pc->microcode;

    mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
    mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS,
                             RT_FALSE, 0,
                             mc - pc->microcode - inner_ljmp);

    mc += pl330_cmd_dmasev(mc, pl330_chan_id(pl330, pc));

    /* Outer loop end */
    mc += pl330_cmd_dmalpend(mc, PL330_COND_ALWAYS,
                             RT_FALSE, 1,  /* LC1 */
                             mc - pc->microcode - outer_ljmp);

    pc->microcode_len = mc - pc->microcode;

    return RT_EOK;
}

/**
 * @brief Prepare a single (one-shot) transfer on a PL330 channel
 *
 * Generates a simple counted loop microcode program:
 *   DMAMOV CCR, ...
 *   DMAMOV SAR/DAR, ...
 *   DMALP  0, <loop>
 *   DMALD  A
 *   DMAST  A
 *   DMALPEND
 *   DMASEV <channel_id>
 *   DMAEND
 *
 * @param[in] chan          DMA channel
 * @param[in] dma_buf_addr  Buffer address for device-side data
 * @param[in] buf_len       Transfer length in bytes
 * @param[in] dir           Transfer direction
 *
 * @return RT_EOK on success, -RT_EINVAL on invalid parameters
 */
static rt_err_t pl330_dma_prep_single(struct rt_dma_chan *chan,
                                      rt_ubase_t dma_buf_addr, rt_size_t buf_len,
                                      enum rt_dma_transfer_direction dir)
{
    void *mc;
    rt_err_t err;
    rt_uint16_t loop;
    rt_uint32_t ccr_val;
    rt_size_t burst_bytes;
    struct pl330_chan *pc = rt_container_of(chan, struct pl330_chan, parent);
    struct pl330 *pl330 = raw_to_pl330(chan->ctrl);
    struct rt_dma_slave_config *conf = &chan->conf;

    mc = pc->microcode;

    if ((err = pl330_ccr_config(conf, &ccr_val)))
    {
        return err;
    }

    mc += pl330_cmd_dmamov(mc, PL330_DIR_CCR, ccr_val);

    if (dir == RT_DMA_MEM_TO_DEV)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, dma_buf_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, conf->dst_addr);
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        mc += pl330_cmd_dmamov(mc, PL330_DIR_SAR, conf->src_addr);
        mc += pl330_cmd_dmamov(mc, PL330_DIR_DAR, dma_buf_addr);
    }

    burst_bytes = conf->src_addr_width * conf->src_maxburst;
    if (!burst_bytes || !buf_len)
    {
        return -RT_EINVAL;
    }

    if (buf_len % burst_bytes)
    {
        return -RT_EINVAL;
    }

    loop = buf_len / burst_bytes;
    if (loop == 0 || loop > 255)
    {
        return -RT_EINVAL;
    }

    mc += pl330_cmd_dmalp(mc, 0 /* LC0 */, loop);
    rt_uint8_t ljmp = mc - pc->microcode;

    mc += pl330_cmd_dmald(mc, PL330_COND_ALWAYS);
    mc += pl330_cmd_dmast(mc, PL330_COND_ALWAYS);

    mc += pl330_cmd_dmalpend(mc,
                             PL330_COND_ALWAYS,
                             RT_FALSE,
                             0, /* LC0 */
                             mc - pc->microcode - ljmp);

    mc += pl330_cmd_dmasev(mc, pl330_chan_id(pl330, pc));

    mc += pl330_cmd_dmaend(mc);

    pc->microcode_len = mc - pc->microcode;
    pc->size = buf_len;

    return RT_EOK;
}

/** @brief PL330 DMA controller operations vtable */
static const struct rt_dma_controller_ops pl330_dma_ops = {
    .request_chan = pl330_dma_request_chan,
    .release_chan = pl330_dma_release_chan,
    .start = pl330_dma_start,
    .stop = pl330_dma_stop,
    .config = pl330_dma_config,
    .prep_memcpy = pl330_dma_prep_memcpy,
    .prep_cyclic = pl330_dma_prep_cyclic,
    .prep_single = pl330_dma_prep_single,
};

/**
 * @brief PL330 interrupt service routine
 *
 * Handles all channel interrupts. Reads the Interrupt Status Register
 * to identify which channel triggered, then checks the Channel Status
 * Register:
 * - PL330_CS_CMPLT / PL330_CS_STOP: transfer completed successfully
 * - PL330_CS_FAULT / PL330_CS_FLTCMP: transfer faulted
 *
 * @param[in] irqno  Hardware IRQ number
 * @param[in] params Controller instance pointer
 */
static void pl330_isr(int irqno, void *params)
{
    rt_uint32_t isr, csr;
    struct pl330_chan *pc;
    struct pl330 *pl330 = params;

    isr = HWREG32(pl330->regs + PL330_REG_INTMIS);

    for (int i = 0; i < pl330->num_chan; ++i)
    {
        if (!(isr & RT_BIT(i)))
        {
            continue;
        }

        pc = &pl330->chans[i];

        HWREG32(pl330->regs + PL330_REG_INTCLR) = RT_BIT(i);

        csr = HWREG32(pl330->regs + PL330_REG_CSR(i)) & 0xf;

        switch (csr)
        {
        case PL330_CS_CMPLT:
        case PL330_CS_STOP:
            rt_dma_chan_done(&pc->parent, pc->size);
            break;

        case PL330_CS_FAULT:
        case PL330_CS_FLTCMP:
            LOG_E("Channel[%d] fault", i);
            rt_dma_chan_done(&pc->parent, 0);
            break;

        default:
            LOG_E("Unhandle CSR = %x", csr);
            break;
        }
    }
}

/**
 * @brief Free all resources allocated by the PL330 driver
 *
 * Unmaps registers, disables the clock, asserts reset controls,
 * and frees the channel array and controller structure.
 *
 * @param[in] pl330  PL330 controller instance
 */
static void pl330_free(struct pl330 *pl330)
{
    if (pl330->regs)
    {
        rt_iounmap(pl330->regs);
    }

    if (!rt_is_err_or_null(pl330->pclk))
    {
        rt_clk_disable_unprepare(pl330->pclk);
        rt_clk_put(pl330->pclk);
    }

    if (!rt_is_err_or_null(pl330->rstc))
    {
        rt_reset_control_assert(pl330->rstc);
        rt_reset_control_put(pl330->rstc);
    }

    if (!rt_is_err_or_null(pl330->rstc_ocp))
    {
        rt_reset_control_assert(pl330->rstc_ocp);
        rt_reset_control_put(pl330->rstc_ocp);
    }

    if (pl330->chans)
    {
        rt_free(pl330->chans);
    }

    rt_free(pl330);
}

/**
 * @brief Probe a PL330 DMA controller platform device
 *
 * Initialization sequence:
 * 1. Allocate pl330 structure
 * 2. Map MMIO registers
 * 3. Get IRQ lines
 * 4. Enable APB clock
 * 5. Deassert reset controls (dma, dma-ocp)
 * 6. Read hardware quirks from device tree
 * 7. Read hardware configuration (channel count, data width, etc.)
 * 8. Allocate channel descriptors with microcode buffer alignment
 * 9. Register with the DMA framework
 * 10. Install and unmask IRQ handlers
 *
 * @param[in] pdev  Platform device matching "arm,pl330"
 *
 * @return RT_EOK on success, error code otherwise
 */
static rt_err_t pl330_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    char isr_name[RT_NAME_MAX];
    struct rt_device *dev = &pdev->parent;
    struct pl330 *pl330 = rt_calloc(1, sizeof(*pl330));

    if (!pl330)
    {
        return -RT_ENOMEM;
    }

    pl330->regs = rt_dm_dev_iomap(dev, 0);

    if (!pl330->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    pl330->irqs_nr = rt_dm_dev_get_irq_count(dev);

    if (pl330->irqs_nr < 0)
    {
        err = pl330->irqs_nr;
        goto _fail;
    }
    else if (pl330->irqs_nr == 0)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    for (int i = 0; i < pl330->irqs_nr; ++i)
    {
        int irq = rt_dm_dev_get_irq(dev, i);

        if (irq < 0)
        {
            err = irq;
            goto _fail;
        }

        pl330->irqs[i] = irq;
    }

    pl330->pclk = rt_clk_get_by_name(dev, "apb_pclk");

    if (rt_is_err(pl330->pclk))
    {
        err = rt_ptr_err(pl330->pclk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(pl330->pclk)))
    {
        goto _fail;
    }

    pl330->rstc = rt_reset_control_get_by_name(dev, "dma");

    if (rt_is_err(pl330->rstc))
    {
        err = rt_ptr_err(pl330->rstc);
        goto _fail;
    }

    if (pl330->rstc && (err = rt_reset_control_deassert(pl330->rstc)))
    {
        goto _fail;
    }

    pl330->rstc_ocp = rt_reset_control_get_by_name(dev, "dma-ocp");

    if (rt_is_err(pl330->rstc_ocp))
    {
        err = rt_ptr_err(pl330->rstc_ocp);
        goto _fail;
    }

    if (pl330->rstc_ocp && (err = rt_reset_control_deassert(pl330->rstc_ocp)))
    {
        goto _fail;
    }

    if (rt_dm_dev_prop_read_bool(dev, "arm,pl330-broken-no-flushp"))
    {
        pl330->quirk |= PL330_QUIRK_BROKEN_NO_FLUSHP;
    }

    if (rt_dm_dev_prop_read_bool(dev, "arm,pl330-periph-burst"))
    {
        pl330->quirk |= PL330_QUIRK_PERIPH_BURST;
    }

    pl330_read_config(pl330);

    pl330->chans = rt_calloc(pl330->num_chan, sizeof(pl330->chans[0]));

    if (!pl330->chans)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int i = 0; i < pl330->num_chan; ++i)
    {
        int offset = 0;
        struct pl330_chan *chan = &pl330->chans[i];

        chan->microcode_dma = (rt_ubase_t)rt_kmem_v2p(chan->microcode_raw);
        offset = RT_ALIGN(chan->microcode_dma, 4) - chan->microcode_dma;

        chan->microcode = chan->microcode_raw + offset;
        chan->microcode_dma += offset;
    }

    pl330->parent.dev = dev;
    pl330->parent.ops = &pl330_dma_ops;
    rt_dma_controller_add_direction(&pl330->parent, RT_DMA_MEM_TO_MEM);
    rt_dma_controller_add_direction(&pl330->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_add_direction(&pl330->parent, RT_DMA_DEV_TO_MEM);
    rt_dma_controller_set_addr_mask(&pl330->parent, RT_DMA_ADDR_MASK(32));

    if ((err = rt_dma_controller_register(&pl330->parent)))
    {
        goto _fail;
    }

    dev->user_data = pl330;

    for (int i = 0; i < pl330->irqs_nr; ++i)
    {
        rt_snprintf(isr_name, RT_NAME_MAX, "%s-%u", rt_dm_dev_get_name(dev), i);
        rt_hw_interrupt_install(pl330->irqs[i], pl330_isr, pl330, isr_name);
        rt_hw_interrupt_umask(pl330->irqs[i]);
    }

    return RT_EOK;

_fail:
    pl330_free(pl330);

    return err;
}

/**
 * @brief Remove a PL330 DMA controller platform device
 *
 * Masks and detaches all IRQs, unregisters from the DMA framework,
 * and frees all resources.
 *
 * @param[in] pdev  Platform device
 *
 * @return RT_EOK
 */
static rt_err_t pl330_remove(struct rt_platform_device *pdev)
{
    struct pl330 *pl330 = pdev->parent.user_data;

    for (int i = 0; i < pl330->irqs_nr; ++i)
    {
        rt_hw_interrupt_mask(pl330->irqs[i]);
        rt_pic_detach_irq(pl330->irqs[i], pl330);
    }

    rt_dma_controller_unregister(&pl330->parent);

    pl330_free(pl330);

    return RT_EOK;
}

/** @brief Device tree compatible IDs for the PL330 driver */
static const struct rt_ofw_node_id pl330_ofw_ids[] = {
    { .compatible = "arm,pl330" },
    { /* sentinel */ }
};

/** @brief PL330 platform driver descriptor */
static struct rt_platform_driver pl330_driver = {
    .name = "dma-pl330",
    .ids = pl330_ofw_ids,

    .probe = pl330_probe,
    .remove = pl330_remove,
};

/**
 * @brief Register the PL330 platform driver at boot
 *
 * @return 0
 */
static int pl330_drv_register(void)
{
    rt_platform_driver_register(&pl330_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(pl330_drv_register);
