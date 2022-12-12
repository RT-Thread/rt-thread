/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_PL330_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PL330
 *  @{
 */

/** @defgroup PL330_How_To_Use How To Use
 *  @{

 The PL330 driver can be used as follows:

 - Invoke HAL_PL330_Init to initialize pl330.
 - Invoke HAL_PL330_RequestChannel to request a available dma channel.
 - Invoke HAL_PL330_Config to config dma transfer config.
 - Invoke HAL_PL330_PrepDmaSingle/Cyclic for single/cyclic transfer.
 - Invoke HAL_PL330_Start to start a ready dma transfer.
 - Invoke HAL_PL330_Stop to stop the dma channel.
 - Invoke HAL_PL330_ReleaseChannel to release the dma channel.
 - Invoke HAL_PL330_DeInit to deinitialize pl330.
 - More details refer to APIs' descriptions as below.

 @} */

/** @defgroup PL330_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

#ifdef PL330_DEBUG_MCGEN
static uint32_t s_cmdLine;
#define PL330_DBGCMD_DUMP(off, x...) \
    do {                             \
        HAL_DBG("%lx:", s_cmdLine);  \
        HAL_DBG(x);                  \
        s_cmdLine += off;            \
    } while (0)
#define PL330_DBGMC_START(addr) (s_cmdLine = addr)
#else
#define PL330_DBGCMD_DUMP(off, x...) \
    do {                             \
    } while (0)
#define PL330_DBGMC_START(addr) \
    do {                        \
    } while (0)
#endif

#ifndef PL330_MAX_WAIT
#define PL330_MAX_WAIT 4000
#endif

#define DMAC_MODE_NS HAL_BIT(0)

#define DS_ST_STOP   0x0
#define DS_ST_EXEC   0x1
#define DS_ST_CMISS  0x2
#define DS_ST_UPDTPC 0x3
#define DS_ST_WFE    0x4
#define DS_ST_ATBRR  0x5
#define DS_ST_QBUSY  0x6
#define DS_ST_WFP    0x7
#define DS_ST_KILL   0x8
#define DS_ST_CMPLT  0x9
#define DS_ST_FLTCMP 0xe
#define DS_ST_FAULT  0xf

#define CC_SRCINC           HAL_BIT(0)
#define CC_DSTINC           HAL_BIT(14)
#define CC_SRCPRI           HAL_BIT(8)
#define CC_DSTPRI           HAL_BIT(22)
#define CC_SRCNS            HAL_BIT(9)
#define CC_DSTNS            HAL_BIT(23)
#define CC_SRCIA            HAL_BIT(10)
#define CC_DSTIA            HAL_BIT(24)
#define CC_SRCBRSTLEN_SHFT  4
#define CC_DSTBRSTLEN_SHFT  18
#define CC_SRCBRSTSIZE_SHFT 1
#define CC_DSTBRSTSIZE_SHFT 15
#define CC_SRCCCTRL_SHFT    11
#define CC_SRCCCTRL_MASK    0x7
#define CC_DSTCCTRL_SHFT    25
#define CC_DRCCCTRL_MASK    0x7
#define CC_SWAP_SHFT        28

#define CR0_PERIPH_REQ_SET   HAL_BIT(0)
#define CR0_BOOT_EN_SET      HAL_BIT(1)
#define CR0_BOOT_MAN_NS      HAL_BIT(2)
#define CR0_NUM_CHANS_SHIFT  4
#define CR0_NUM_CHANS_MASK   0x7
#define CR0_NUM_PERIPH_SHIFT 12
#define CR0_NUM_PERIPH_MASK  0x1f
#define CR0_NUM_EVENTS_SHIFT 17
#define CR0_NUM_EVENTS_MASK  0x1f

#define CR1_ICACHE_LEN_SHIFT      0
#define CR1_ICACHE_LEN_MASK       0x7
#define CR1_NUM_ICACHELINES_SHIFT 4
#define CR1_NUM_ICACHELINES_MASK  0xf

#define CRD_DATA_WIDTH_SHIFT 0
#define CRD_DATA_WIDTH_MASK  0x7
#define CRD_WR_CAP_SHIFT     4
#define CRD_WR_CAP_MASK      0x7
#define CRD_WR_Q_DEP_SHIFT   8
#define CRD_WR_Q_DEP_MASK    0xf
#define CRD_RD_CAP_SHIFT     12
#define CRD_RD_CAP_MASK      0x7
#define CRD_RD_Q_DEP_SHIFT   16
#define CRD_RD_Q_DEP_MASK    0xf
#define CRD_DATA_BUFF_SHIFT  20
#define CRD_DATA_BUFF_MASK   0x3ff

#define PART          0x330
#define DESIGNER      0x41
#define REVISION      0x0
#define INTEG_CFG     0x0
#define PERIPH_ID_VAL ((PART << 0) | (DESIGNER << 12))

#define PL330_DS_DMA_STATUS         0x0f
#define PL330_DS_DMA_STATUS_STOPPED 0x00
#define PL330_DBGSTATUS_BUSY        0x01
#define PL330_CS_ACTIVE_MASK        0x07
#define PL330_CR1_I_CACHE_LEN_MASK  0x07
#define PL330_INTCLR_ALL_MASK       0xff

#define CMD_DMAADDH   0x54
#define CMD_DMAEND    0x00
#define CMD_DMAFLUSHP 0x35
#define CMD_DMAGO     0xa0
#define CMD_DMALD     0x04
#define CMD_DMALDP    0x25
#define CMD_DMALP     0x20
#define CMD_DMALPEND  0x28
#define CMD_DMAKILL   0x01
#define CMD_DMAMOV    0xbc
#define CMD_DMANOP    0x18
#define CMD_DMARMB    0x12
#define CMD_DMASEV    0x34
#define CMD_DMAST     0x08
#define CMD_DMASTP    0x29
#define CMD_DMASTZ    0x0c
#define CMD_DMAWFE    0x36
#define CMD_DMAWFP    0x30
#define CMD_DMAWMB    0x13

#define SZ_DMAADDH   3
#define SZ_DMAEND    1
#define SZ_DMAFLUSHP 2
#define SZ_DMALD     1
#define SZ_DMALDP    2
#define SZ_DMALP     2
#define SZ_DMALPEND  2
#define SZ_DMAKILL   1
#define SZ_DMAMOV    6
#define SZ_DMANOP    1
#define SZ_DMARMB    1
#define SZ_DMASEV    2
#define SZ_DMAST     1
#define SZ_DMASTP    2
#define SZ_DMASTZ    1
#define SZ_DMAWFE    2
#define SZ_DMAWFP    2
#define SZ_DMAWMB    1
#define SZ_DMAGO     6

#define BRST_LEN(ccr)  ((((ccr) >> CC_SRCBRSTLEN_SHFT) & 0xf) + 1)
#define BRST_SIZE(ccr) (1 << (((ccr) >> CC_SRCBRSTSIZE_SHFT) & 0x7))

#define BYTE_TO_BURST(b, ccr)      ((b) / BRST_SIZE(ccr) / BRST_LEN(ccr))
#define BURST_TO_BYTE(c, ccr)      ((c) * BRST_SIZE(ccr) * BRST_LEN(ccr))
#define BYTE_MOD_BURST_LEN(b, ccr) (((b) / BRST_SIZE(ccr)) % BRST_LEN(ccr))

/*
 * PL330_DBGINST0 - constructs the word for the Debug Instruction-0 Register.
 * @b1: Instruction byte 1
 * @b0: Instruction byte 0
 * @ch: channel number
 * @dbg_th: Debug thread encoding: 0 = DMA manager thread, 1 = DMA channel
 */
#define PL330_DBGINST0(b1, b0, ch, dbg_th) \
    (((b1) << 24) | ((b0) << 16) | (((ch) & 0x7) << 8) | ((dbg_th & 0x1)))

/********************* Private Structure Definition **************************/

typedef enum {
    SAR = 0,
    CCR,
    DAR,
} eDMAMOV_DST;

typedef enum {
    SRC = 0,
    DST,
} ePL330_DST;

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

__STATIC_INLINE int PL330_Instr_DMAADDH(uint8_t dryRun, char *buf,
                                        ePL330_DST da, uint16_t val)
{
    if (dryRun) {
        return SZ_DMAADDH;
    }

    *buf = CMD_DMAADDH;
    *buf |= (da << 1);
    *((uint16_t *)(buf + 1)) = val;

    PL330_DBGCMD_DUMP(SZ_DMAADDH, "\tDMAADDH %s %u\n",
                      da == DST ? "DA" : "SA", val);

    return SZ_DMAADDH;
}

__STATIC_INLINE int PL330_Instr_DMAEND(uint8_t dryRun, char *buf)
{
    if (dryRun) {
        return SZ_DMAEND;
    }
    /*
     * DMAEND encoding:
     * 7 6 5 4 3 2 1 0
     * 0 0 0 0 0 0 0 0
     */
    *buf = CMD_DMAEND;

    PL330_DBGCMD_DUMP(SZ_DMAEND, "\tDMAEND\n");

    return SZ_DMAEND;
}

__STATIC_INLINE void PL330_Memcpy4(char *dst, char *src)
{
    *dst = *src;
    *(dst + 1) = *(src + 1);
    *(dst + 2) = *(src + 2);
    *(dst + 3) = *(src + 3);
}

__STATIC_INLINE int PL330_Instr_DMAGO(uint8_t dryRun, char *buf, uint8_t cn,
                                      uint32_t imm, uint8_t ns)
{
    if (dryRun) {
        return SZ_DMAGO;
    }
    /*
     * DMAGO encoding:
     * 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
     *  0  0  0  0  0 |cn[2:0]| 1  0  1  0  0  0 ns  0
     *
     * 47 ... 16
     *  imm[32:0]
     */
    *buf = CMD_DMAGO | ((ns << 1) & 0x02);

    *(buf + 1) = (uint8_t)(cn & 0x07);

    PL330_Memcpy4(buf + 2, (char *)&imm);

    return SZ_DMAGO;
}

__STATIC_INLINE int PL330_Instr_DMALP(uint8_t dryRun, char *buf, uint8_t lc,
                                      uint16_t loops)
{
    if (dryRun) {
        return SZ_DMALP;
    }
    /*
     * DMALP encoding
     * 15   ...   8 7 6 5 4 3 2 1  0
     * | iter[7:0] |0 0 1 0 0 0 lc 0
     */
    *buf = (uint8_t)(CMD_DMALP | ((lc & 1) << 1));
    *(buf + 1) = (uint8_t)(loops - 1);

    PL330_DBGCMD_DUMP(SZ_DMALP, "\tDMALP_%c %u\n", lc ? '1' : '0', loops - 1);

    return SZ_DMALP;
}

__STATIC_INLINE int PL330_Instr_DMAMOV(uint8_t dryRun, char *buf, uint8_t rd,
                                       uint32_t imm)
{
    if (dryRun) {
        return SZ_DMAMOV;
    }
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
    *buf = CMD_DMAMOV;
    *(buf + 1) = rd & 0x7;
    PL330_Memcpy4(buf + 2, (char *)&imm);

    PL330_DBGCMD_DUMP(SZ_DMAMOV, "\tDMAMOV %s 0x%lx\n",
                      rd == SAR ? "SAR" : (rd == DAR ? "DAR" : "CCR"), imm);

    return SZ_DMAMOV;
}

HAL_UNUSED __STATIC_INLINE int PL330_Instr_DMANOP(uint8_t dryRun, char *buf)
{
    if (dryRun) {
        return SZ_DMANOP;
    }
    /*
     * DMANOP encoding
     * 7 6 5 4 3 2 1 0
     * 0 0 0 1 1 0 0 0
     */
    *buf = CMD_DMANOP;

    PL330_DBGCMD_DUMP(SZ_DMANOP, "\tDMANOP\n");

    return SZ_DMANOP;
}

HAL_UNUSED __STATIC_INLINE int PL330_Instr_DMARMB(uint8_t dryRun, char *buf)
{
    if (dryRun) {
        return SZ_DMARMB;
    }
    /*
     * DMARMB encoding
     * 7 6 5 4 3 2 1 0
     * 0 0 0 1 0 0 1 0
     */
    *buf = CMD_DMARMB;

    PL330_DBGCMD_DUMP(SZ_DMARMB, "\tDMARMB\n");

    return SZ_DMARMB;
}

__STATIC_INLINE int PL330_Instr_DMASEV(uint8_t dryRun, char *buf, uint8_t event)
{
    if (dryRun) {
        return SZ_DMASEV;
    }
    /*
     * DMASEV encoding
     * 15 4 3 2 1  10 9 8 7 6 5 4 3 2 1 0
     * |event[4:0]| 0 0 0 0 0 1 1 0 1 0 0
     */
    *buf = CMD_DMASEV;
    *(buf + 1) = (uint8_t)(event << 3);

    PL330_DBGCMD_DUMP(SZ_DMASEV, "\tDMASEV %u\n", event);

    return SZ_DMASEV;
}

HAL_UNUSED __STATIC_INLINE int PL330_Instr_DMAWMB(uint8_t dryRun, char *buf)
{
    if (dryRun) {
        return SZ_DMAWMB;
    }
    /*
     * DMAWMB encoding
     * 7 6 5 4 3 2 1 0
     * 0 0 0 1 0 0 1 0
     */
    *buf = CMD_DMAWMB;

    PL330_DBGCMD_DUMP(SZ_DMAWMB, "\tDMAWMB\n");

    return SZ_DMAWMB;
}

__STATIC_INLINE int PL330_Instr_DMAFLUSHP(uint8_t dryRun, char *buf,
                                          uint8_t peri)
{
    if (dryRun) {
        return SZ_DMAFLUSHP;
    }
    /*
     * DMAFLUSHP encoding
     * 15 4 3 2 1  10 9 8 7 6 5 4 3 2 1 0
     * |perip[4:0]| 0 0 0 0 0 1 1 0 1 0 1
     */
    *buf = CMD_DMAFLUSHP;

    peri &= 0x1f;
    peri <<= 3;
    *(buf + 1) = peri;

    PL330_DBGCMD_DUMP(SZ_DMAFLUSHP, "\tDMAFLUSHP %u\n", peri >> 3);

    return SZ_DMAFLUSHP;
}

__STATIC_INLINE int PL330_Instr_DMALD(uint8_t dryRun, char *buf,
                                      ePL330_COND cond)
{
    if (dryRun) {
        return SZ_DMALD;
    }
    /*
     * DMALD encoding
     * 7 6 5 4 3 2 1  0
     * 0 0 0 0 0 1 bs x
     */
    *buf = CMD_DMALD;

    if (cond == SINGLE) {
        *buf |= (0 << 1) | (1 << 0);
    } else if (cond == BURST) {
        *buf |= (1 << 1) | (1 << 0);
    }

    PL330_DBGCMD_DUMP(SZ_DMALD, "\tDMALD%c\n",
                      cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'A'));

    return SZ_DMALD;
}

__STATIC_INLINE int PL330_Instr_DMALDP(uint8_t dryRun, char *buf,
                                       ePL330_COND cond, uint8_t peri)
{
    if (dryRun) {
        return SZ_DMALDP;
    }
    /*
     * DMALDP encoding
     * 15 4 3 2 1  10 9 8 7 6 5 4 3 2 1  0
     * |perip[4:0]| 0 0 0 0 0 1 0 0 1 bs 1
     */
    *buf = CMD_DMALDP;

    if (cond == BURST) {
        *buf |= (1 << 1);
    }

    peri &= 0x1f;
    peri <<= 3;
    *(buf + 1) = peri;

    PL330_DBGCMD_DUMP(SZ_DMALDP, "\tDMALDP%c %u\n", cond == SINGLE ? 'S' : 'B',
                      peri >> 3);

    return SZ_DMALDP;
}

__STATIC_INLINE int PL330_Instr_DMALPEND(uint8_t dryRun, char *buf,
                                         ePL330_COND cond, bool forever,
                                         uint32_t loop, uint8_t bjump)
{
    if (dryRun) {
        return SZ_DMALPEND;
    }
    /*
     * DMALPEND encoding
     * 15       ...        8 7 6 5 4  3 2  1  0
     * | backward_jump[7:0] |0 0 1 nf 1 lc bs x
     */
    *buf = CMD_DMALPEND;

    if (loop) {
        *buf |= (1 << 2);
    }

    if (!forever) {
        *buf |= (1 << 4);
    }

    if (cond == SINGLE) {
        *buf |= (0 << 1) | (1 << 0);
    } else if (cond == BURST) {
        *buf |= (1 << 1) | (1 << 0);
    }

    *(buf + 1) = bjump;

    PL330_DBGCMD_DUMP(SZ_DMALPEND, "\tDMALP%s%c_%c bjmpto_%x\n",
                      forever ? "FE" : "END",
                      cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'A'),
                      loop ? '1' : '0', bjump);

    return SZ_DMALPEND;
}

HAL_UNUSED __STATIC_INLINE int PL330_Instr_DMAKILL(uint8_t dryRun, char *buf)
{
    if (dryRun) {
        return SZ_DMAKILL;
    }
    /*
     * DMAKILL encoding
     * 7 6 5 4 3 2 1 0
     * 0 0 0 0 0 0 0 1
     */
    *buf = CMD_DMAKILL;

    return SZ_DMAKILL;
}

__STATIC_INLINE int PL330_Instr_DMAST(uint8_t dryRun, char *buf,
                                      ePL330_COND cond)
{
    if (dryRun) {
        return SZ_DMAST;
    }
    /*
     * DMAST encoding
     * 7 6 5 4 3 2 1  0
     * 0 0 0 0 1 0 bs x
     */
    *buf = CMD_DMAST;

    if (cond == SINGLE) {
        *buf |= (0 << 1) | (1 << 0);
    } else if (cond == BURST) {
        *buf |= (1 << 1) | (1 << 0);
    }

    PL330_DBGCMD_DUMP(SZ_DMAST, "\tDMAST%c\n",
                      cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'A'));

    return SZ_DMAST;
}

__STATIC_INLINE int PL330_Instr_DMASTP(uint8_t dryRun, char *buf,
                                       ePL330_COND cond, uint8_t peri)
{
    if (dryRun) {
        return SZ_DMASTP;
    }
    /*
     * DMASTP encoding
     * 15 4 3 2 1  10 9 8 7 6 5 4 3 2 1  0
     * |perip[4:0]| 0 0 0 0 0 1 0 1 0 bs 1
     */
    *buf = CMD_DMASTP;

    if (cond == BURST) {
        *buf |= (1 << 1);
    }

    peri &= 0x1f;
    peri <<= 3;
    *(buf + 1) = peri;

    PL330_DBGCMD_DUMP(SZ_DMASTP, "\tDMASTP%c %u\n", cond == SINGLE ? 'S' : 'B',
                      peri >> 3);

    return SZ_DMASTP;
}

HAL_UNUSED __STATIC_INLINE int PL330_Instr_DMASTZ(uint8_t dryRun, char *buf)
{
    if (dryRun) {
        return SZ_DMASTZ;
    }
    /*
     * DMASTZ encoding
     * 7 6 5 4 3 2 1 0
     * 0 0 0 1 1 1 0 0
     */
    *buf = CMD_DMASTZ;

    PL330_DBGCMD_DUMP(SZ_DMASTZ, "\tDMASTZ\n");

    return SZ_DMASTZ;
}

HAL_UNUSED __STATIC_INLINE int PL330_Instr_DMAWFE(uint8_t dryRun, char *buf, uint8_t ev,
                                                  uint32_t invalidate)
{
    if (dryRun) {
        return SZ_DMAWFE;
    }
    /*
     * DMAWFE encoding
     * 15 4 3 2 1  10 9 8 7 6 5 4 3 2 1 0
     * |event[4:0]| 0 i 0 0 0 1 1 0 1 1 0
     */
    *buf = CMD_DMAWFE;

    ev &= 0x1f;
    ev <<= 3;
    *(buf + 1) = ev;

    if (invalidate) {
        *(buf + 1) |= (1 << 1);
    }

    PL330_DBGCMD_DUMP(SZ_DMAWFE, "\tDMAWFE %u%s\n", ev >> 3,
                      invalidate ? ", I" : "");

    return SZ_DMAWFE;
}

__STATIC_INLINE int PL330_Instr_DMAWFP(uint8_t dryRun, char *buf,
                                       ePL330_COND cond, uint8_t peri)
{
    if (dryRun) {
        return SZ_DMAWFP;
    }
    /*
     * DMAWFP encoding
     * 15 4 3 2 1  10 9 8 7 6 5 4 3 2 1  0
     * |perip[4:0]| 0 0 0 0 0 1 1 0 0 bs p
     */
    *buf = CMD_DMAWFP;

    if (cond == SINGLE) {
        *buf |= (0 << 1) | (0 << 0);
    } else if (cond == BURST) {
        *buf |= (1 << 1) | (0 << 0);
    } else {
        *buf |= (0 << 1) | (1 << 0);
    }

    peri &= 0x1f;
    peri <<= 3;
    *(buf + 1) = peri;

    PL330_DBGCMD_DUMP(SZ_DMAWFP, "\tDMAWFP%c %u\n",
                      cond == SINGLE ? 'S' : (cond == BURST ? 'B' : 'P'),
                      peri >> 3);

    return SZ_DMAWFP;
}

static int _LDST_MemToMem(uint8_t dryRun, char *buf, int cyc)
{
    int off = 0;

    while (cyc--) {
        off += PL330_Instr_DMALD(dryRun, &buf[off], ALWAYS);
        off += PL330_Instr_DMAST(dryRun, &buf[off], ALWAYS);
    }

    return off;
}

static int _LDST_DevToMem(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                          char *buf, struct PL330_XFER_SPEC *pxs, int cyc)
{
    int off = 0;
    ePL330_COND cond = pl330->peripReqType;

    while (cyc--) {
        off += PL330_Instr_DMAWFP(dryRun, &buf[off], cond, pxs->desc->peri);
        off += PL330_Instr_DMALDP(dryRun, &buf[off], cond, pxs->desc->peri);
        off += PL330_Instr_DMAST(dryRun, &buf[off], ALWAYS);
        off += PL330_Instr_DMAFLUSHP(dryRun, &buf[off], pxs->desc->peri);
        if (pxs->desc->dstInterlaceSize) {
            off += PL330_Instr_DMAADDH(dryRun, &buf[off], DST,
                                       pxs->desc->dstInterlaceSize);
        }
    }

    return off;
}

static int _LDST_MemToDev(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                          char *buf, struct PL330_XFER_SPEC *pxs, int cyc)
{
    int off = 0;
    ePL330_COND cond = pl330->peripReqType;

    while (cyc--) {
        off += PL330_Instr_DMAWFP(dryRun, &buf[off], cond, pxs->desc->peri);
        off += PL330_Instr_DMALD(dryRun, &buf[off], ALWAYS);
        off += PL330_Instr_DMASTP(dryRun, &buf[off], cond, pxs->desc->peri);
        off += PL330_Instr_DMAFLUSHP(dryRun, &buf[off], pxs->desc->peri);
        if (pxs->desc->srcInterlaceSize) {
            off += PL330_Instr_DMAADDH(dryRun, &buf[off], SRC,
                                       pxs->desc->srcInterlaceSize);
        }
    }

    return off;
}

static int _Bursts(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                   char *buf, struct PL330_XFER_SPEC *pxs, int cyc)
{
    int off = 0;

    switch (pxs->desc->dir) {
    case DMA_MEM_TO_DEV:
        off += _LDST_MemToDev(dryRun, pl330, &buf[off], pxs, cyc);
        break;
    case DMA_DEV_TO_MEM:
        off += _LDST_DevToMem(dryRun, pl330, &buf[off], pxs, cyc);
        break;
    case DMA_MEM_TO_MEM:
        off += _LDST_MemToMem(dryRun, &buf[off], cyc);
        break;
    default:
        off += 0x40000000; /* Scare off the Client */
        break;
    }

    return off;
}

/* Returns bytes consumed and updates bursts */
static int _Loop(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                 char *buf, unsigned long *bursts,
                 struct PL330_XFER_SPEC *pxs)
{
    int cyc, cycmax, szlp, szlpend, szbrst, off;
    uint32_t lcnt0, lcnt1, ljmp0, ljmp1;

    if (*bursts == 1) {
        return _Bursts(dryRun, pl330, buf, pxs, 1);
    }

    /* Max iterations possible in DMALP is 256 */
    if (*bursts >= 256 * 256) {
        lcnt1 = 256;
        lcnt0 = 256;
        cyc = *bursts / lcnt1 / lcnt0;
    } else if (*bursts > 256) {
        lcnt1 = 256;
        lcnt0 = *bursts / lcnt1;
        cyc = 1;
    } else {
        lcnt1 = *bursts;
        lcnt0 = 0;
        cyc = 1;
    }

    szlp = PL330_Instr_DMALP(1, buf, 0, 0);
    szbrst = _Bursts(1, pl330, buf, pxs, 1);
    szlpend = PL330_Instr_DMALPEND(1, buf, ALWAYS, false, 0, 0);

    if (lcnt0) {
        szlp *= 2;
        szlpend *= 2;
    }

    /*
     * Max bursts that we can unroll due to limit on the
     * size of backward jump that can be encoded in DMALPEND
     * which is 8-bits and hence 255
     */
    cycmax = (255 - (szlp + szlpend)) / szbrst;
    cyc = (cycmax < cyc) ? cycmax : cyc;
    off = 0;

    if (lcnt0) {
        off += PL330_Instr_DMALP(dryRun, &buf[off], 0, lcnt0);
        ljmp0 = off;
    }

    off += PL330_Instr_DMALP(dryRun, &buf[off], 1, lcnt1);
    ljmp1 = off;

    off += _Bursts(dryRun, pl330, &buf[off], pxs, cyc);

    off +=
        PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, false, 1, off - ljmp1);

    if (lcnt0) {
        off += PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, false, 0,
                                    off - ljmp0);
    }
    *bursts = lcnt1 * cyc;
    if (lcnt0) {
        *bursts *= lcnt0;
    }

    return off;
}

static int _Period(uint8_t dryRun, struct HAL_PL330_DEV *pl330, char *buf,
                   unsigned long bursts, struct PL330_XFER_SPEC *pxs, int ev)
{
    unsigned int lcnt1, ljmp1;
    int cyc, off = 0;
    struct PL330_XFER *x = &pxs->desc->px;

    if (bursts > 256) {
        lcnt1 = 256;
        cyc = bursts / 256;
    } else {
        lcnt1 = bursts;
        cyc = 1;
    }

    /* loop1 */
    off += PL330_Instr_DMALP(dryRun, &buf[off], 1, lcnt1);
    ljmp1 = off;
    off += _Bursts(dryRun, pl330, &buf[off], pxs, cyc);
    off +=
        PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, false, 1, off - ljmp1);

    /* remainder */
    lcnt1 = bursts - (lcnt1 * cyc);

    if (lcnt1) {
        off += PL330_Instr_DMALP(dryRun, &buf[off], 1, lcnt1);
        ljmp1 = off;
        off += _Bursts(dryRun, pl330, &buf[off], pxs, 1);
        off += PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, false, 1,
                                    off - ljmp1);
    }

    if (!pxs->desc->srcInterlaceSize &&
        !pxs->desc->dstInterlaceSize &&
        pl330->peripReqType == BURST) {
        unsigned int ccr = pxs->ccr;
        unsigned long c = 0;

        c = BYTE_MOD_BURST_LEN(x->length, pxs->ccr);

        if (c) {
            ccr &= ~(0xf << CC_SRCBRSTLEN_SHFT);
            ccr &= ~(0xf << CC_DSTBRSTLEN_SHFT);
            off += PL330_Instr_DMAMOV(dryRun, &buf[off], CCR, ccr);
            off += PL330_Instr_DMALP(dryRun, &buf[off], 1, c);
            ljmp1 = off;
            off += _Bursts(dryRun, pl330, &buf[off], pxs, 1);
            off += PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, false, 1,
                                        off - ljmp1);
            off += PL330_Instr_DMAMOV(dryRun, &buf[off], CCR, pxs->ccr);
        }
    }

    off += PL330_Instr_DMASEV(dryRun, &buf[off], ev);

    return off;
}

static int _Loop_Cyclic(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                        char *buf, unsigned long bursts,
                        struct PL330_XFER_SPEC *pxs, int ev)
{
    int off, periods, residue, i;
    unsigned int lcnt0, ljmp0, ljmpfe;
    struct PL330_XFER *x = &pxs->desc->px;

    off = 0;
    ljmpfe = off;
    lcnt0 = pxs->desc->numPeriods;
    periods = 1;

    while (lcnt0 > 256) {
        periods++;
        lcnt0 = pxs->desc->numPeriods / periods;
    }

    residue = pxs->desc->numPeriods % periods;

    /* forever loop */
    off += PL330_Instr_DMAMOV(dryRun, &buf[off], SAR, x->srcAddr);
    off += PL330_Instr_DMAMOV(dryRun, &buf[off], DAR, x->dstAddr);
    off += PL330_Instr_DMAFLUSHP(dryRun, &buf[off], pxs->desc->peri);
    /* loop0 */
    off += PL330_Instr_DMALP(dryRun, &buf[off], 0, lcnt0);
    ljmp0 = off;

    for (i = 0; i < periods; i++) {
        off += _Period(dryRun, pl330, &buf[off], bursts, pxs, ev);
    }

    off +=
        PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, false, 0, off - ljmp0);

    for (i = 0; i < residue; i++) {
        off += _Period(dryRun, pl330, &buf[off], bursts, pxs, ev);
    }

    off +=
        PL330_Instr_DMALPEND(dryRun, &buf[off], ALWAYS, true, 1, off - ljmpfe);

    return off;
}

static int _Setup_Loops(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                        char *buf, struct PL330_XFER_SPEC *pxs)
{
    struct PL330_XFER *x = &pxs->desc->px;
    uint32_t ccr = pxs->ccr;
    unsigned long c, bursts = BYTE_TO_BURST(x->length, ccr);
    int off = 0;

    if (HAL_DMA_IsSlaveDirection(pxs->desc->dir)) {
        off += PL330_Instr_DMAFLUSHP(dryRun, &buf[off], pxs->desc->peri);
    }

    if (pxs->desc->dir == DMA_DEV_TO_MEM) {
        bursts = x->length / (BRST_SIZE(ccr) * BRST_LEN(ccr) +
                              pxs->desc->dstInterlaceSize);
    } else if (pxs->desc->dir == DMA_MEM_TO_DEV) {
        bursts = x->length / (BRST_SIZE(ccr) * BRST_LEN(ccr) +
                              pxs->desc->srcInterlaceSize);
    }

    while (bursts) {
        c = bursts;
        off += _Loop(dryRun, pl330, &buf[off], &c, pxs);
        bursts -= c;
    }

    return off;
}

static int _Setup_Xfer(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                       char *buf, struct PL330_XFER_SPEC *pxs)
{
    struct PL330_XFER *x = &pxs->desc->px;
    int off = 0;

    /* DMAMOV SAR, x->src_addr */
    off += PL330_Instr_DMAMOV(dryRun, &buf[off], SAR, x->srcAddr);
    /* DMAMOV DAR, x->dst_addr */
    off += PL330_Instr_DMAMOV(dryRun, &buf[off], DAR, x->dstAddr);

    /* Setup Loop(s) */
    off += _Setup_Loops(dryRun, pl330, &buf[off], pxs);

    if (!pxs->desc->srcInterlaceSize &&
        !pxs->desc->dstInterlaceSize &&
        pl330->peripReqType == BURST) {
        unsigned int ccr = pxs->ccr;
        unsigned long c = 0;

        c = BYTE_MOD_BURST_LEN(x->length, pxs->ccr);

        if (c) {
            ccr &= ~(0xf << CC_SRCBRSTLEN_SHFT);
            ccr &= ~(0xf << CC_DSTBRSTLEN_SHFT);
            off += PL330_Instr_DMAMOV(dryRun, &buf[off], CCR, ccr);
            off += _Loop(dryRun, pl330, &buf[off], &c, pxs);
        }
    }

    return off;
}

static int _Setup_Xfer_Cyclic(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                              char *buf, struct PL330_XFER_SPEC *pxs, int ev)
{
    struct PL330_XFER *x = &pxs->desc->px;
    uint32_t ccr = pxs->ccr;
    unsigned long bursts = BYTE_TO_BURST(x->length, ccr);
    int off = 0;

    if (pxs->desc->dir == DMA_DEV_TO_MEM) {
        bursts = x->length / (BRST_SIZE(ccr) * BRST_LEN(ccr)
                              + pxs->desc->dstInterlaceSize);
    } else if (pxs->desc->dir == DMA_MEM_TO_DEV) {
        bursts = x->length / (BRST_SIZE(ccr) * BRST_LEN(ccr)
                              + pxs->desc->srcInterlaceSize);
    }

    /* Setup Loop(s) */
    off += _Loop_Cyclic(dryRun, pl330, &buf[off], bursts, pxs, ev);

    return off;
}

/**
 * @brief Conversion from the endian swap size to the bit encoding of the CCR
 *
 * @param endianSwapSize: the endian swap size, in terms of bits, it
 *        could be 8, 16, 32, 64, or 128(We are using DMA assembly syntax)
 *
 * @return The endian swap size bit encoding for the CCR.
 */
HAL_UNUSED __STATIC_INLINE uint32_t PL330_ToendianSwapSizeBits(uint32_t endianSwapSize)
{
    switch (endianSwapSize) {
    case 0:
    case 8:

        return 0;
    case 16:

        return 1;
    case 32:

        return 2;
    case 64:

        return 3;
    case 128:

        return 4;
    default:

        return 0;
    }
}

/**
 * @brief Conversion from the burst size to the bit encoding of the CCR
 *
 * @param burstSize: is the burst size. It's the data width.
 *        In terms of bytes, it could be 1, 2, 4, 8, 16, 32, 64, or 128.
 *        It must be no larger than the bus width.
 *
 * @return The burstSize bit encoding for the CCR.
 */
static uint32_t PL330_ToBurstSizeBits(uint32_t burstSize)
{
    switch (burstSize) {
    case 1:

        return 0;
    case 2:

        return 1;
    case 4:

        return 2;
    case 8:

        return 3;
    case 16:

        return 4;
    case 32:

        return 5;
    case 64:

        return 6;
    case 128:

        return 7;
    default:

        return 0;
    }
}

/**
 * @brief Conversion from PL330 bus transfer descriptors to CCR value.
 *
 * @param rqc: request config.
 *
 * @return The 32-bit CCR value.
 */
static uint32_t _Prepare_CCR(struct PL330_REQCFG *rqc)
{
    uint32_t ccr = 0;

    if (rqc->srcInc) {
        ccr |= CC_SRCINC;
    }

    if (rqc->dstInc) {
        ccr |= CC_DSTINC;
    }

    /* We set same protection levels for Src and DST for now */
    if (rqc->privileged) {
        ccr |= CC_SRCPRI | CC_DSTPRI;
    }
    if (rqc->nonsecure) {
        ccr |= CC_SRCNS | CC_DSTNS;
    }
    if (rqc->insnaccess) {
        ccr |= CC_SRCIA | CC_DSTIA;
    }

    ccr |= (((rqc->brstLen - 1) & 0xf) << CC_SRCBRSTLEN_SHFT);
    ccr |= (((rqc->brstLen - 1) & 0xf) << CC_DSTBRSTLEN_SHFT);

    ccr |= (rqc->brstSize << CC_SRCBRSTSIZE_SHFT);
    ccr |= (rqc->brstSize << CC_DSTBRSTSIZE_SHFT);

    ccr |= (rqc->scctl << CC_SRCCCTRL_SHFT);
    ccr |= (rqc->dcctl << CC_DSTCCTRL_SHFT);

    ccr |= (rqc->swap << CC_SWAP_SHFT);

    return ccr;
}

/* Call after fixing burst size */
static int getBurstLen(struct PL330_DESC *desc, struct HAL_PL330_DEV *pl330,
                       uint32_t len)
{
    int burstLen;

    burstLen = pl330->pcfg.dataBusWidth / 8;
    burstLen *= pl330->pcfg.dataBufDep / pl330->pcfg.numChan;
    burstLen >>= desc->rqcfg.brstSize;

    /* src/dst_burst_len can't be more than 16 */
    if (burstLen > 16) {
        burstLen = 16;
    }

    while (burstLen > 1) {
        if (!(len % (burstLen << desc->rqcfg.brstSize))) {
            break;
        }
        burstLen--;
    }

    return burstLen;
}

/**
 * @brief Use the debug registers to kill the DMA thread.
 *
 * @param reg: the DMA_REG info.
 * @param channel: the DMA channel number.
 * @param thread: the Debug thread encoding.
 *        0: DMA manager thread, 1: DMA channel.
 *
 * @return 0 on success, -1 on time out
 */
static int PL330_Exec_DMAKILL(struct DMA_REG *reg, uint32_t channel, uint32_t thread)
{
    uint32_t dbgInst0;
    int waitCount;

    dbgInst0 = PL330_DBGINST0(0, 0x01, channel, thread);

    /* wait while debug status is busy */
    waitCount = 0;
    while ((READ_REG(reg->DBGSTATUS) & PL330_DBGSTATUS_BUSY) &&
           (waitCount < PL330_MAX_WAIT)) {
        waitCount++;
    }

    if (waitCount >= PL330_MAX_WAIT) {
        /* wait time out */
        HAL_DBG("PL330 device at %p debug status busy time out\n", reg);

        return -1;
    }

    /* write debug instruction 0 */
    WRITE_REG(reg->DBGINST[0], dbgInst0);
    WRITE_REG(reg->DBGINST[1], 0);

    /* run the command in DbgInst0 and DbgInst1 */
    WRITE_REG(reg->DBGCMD, 0);

    return 0;
}

/**
 * @brief Read soc pl330 config.
 *
 * @param pl330: the handle of PL330.
 *
 * return None
 */
static void PL330_Read_Config(struct HAL_PL330_DEV *pl330)
{
    uint32_t val, crdn, cr;
    struct PL330_CONFIG *pcfg = &pl330->pcfg;
    struct DMA_REG *reg = pl330->pReg;

    crdn = READ_REG(reg->CRDN);
    cr = READ_REG(reg->CR[0]);

    val = (crdn >> CRD_DATA_WIDTH_SHIFT) & CRD_DATA_WIDTH_MASK;
    pcfg->dataBusWidth = 8 * (1 << val);

    pcfg->dataBufDep = ((crdn >> CRD_DATA_BUFF_SHIFT) & CRD_DATA_BUFF_MASK) + 1;
    pcfg->numChan = ((cr >> CR0_NUM_CHANS_SHIFT) & CR0_NUM_CHANS_MASK) + 1;

    if (cr & CR0_PERIPH_REQ_SET) {
        pcfg->numPeri = ((cr >> CR0_NUM_PERIPH_SHIFT) & CR0_NUM_PERIPH_MASK) + 1;
        pcfg->periNs = READ_REG(reg->CR[4]);
    } else {
        pcfg->numPeri = 0;
    }

    if (cr & CR0_BOOT_MAN_NS) {
        pcfg->mode |= DMAC_MODE_NS;
    } else {
        pcfg->mode &= ~DMAC_MODE_NS;
    }

    pcfg->numEvents = ((cr >> CR0_NUM_EVENTS_SHIFT) & CR0_NUM_EVENTS_MASK) + 1;
    pcfg->irqNs = READ_REG(reg->CR[3]);
}

/**
 * @brief Construct the DMA program based on the DMA transfer.
 *
 * @param pl330: the handle of PL330.
 * @param pxs: pl330 xfer spec.
 * @param channel: the DMA channel number
 *
 * @return The number of bytes for the program.
 */
static int PL330_BuildDmaProg(uint8_t dryRun, struct HAL_PL330_DEV *pl330,
                              struct PL330_XFER_SPEC *pxs, uint32_t channel)
{
    char *buf = (char *)pxs->desc->mcBuf;
    struct PL330_XFER *x;
    int off = 0;

    PL330_DBGMC_START((uint32_t)buf);

    /* DMAMOV CCR, ccr */
    off += PL330_Instr_DMAMOV(dryRun, &buf[off], CCR, pxs->ccr);

    x = &pxs->desc->px;

    if (pl330->peripReqType != BURST) {
        /* Error if xfer length is not aligned at burst size */
        if (x->length % (BRST_SIZE(pxs->ccr) * BRST_LEN(pxs->ccr))) {
            return HAL_ERROR;
        }
    }

    if (!pxs->desc->cyclic) {
        off += _Setup_Xfer(dryRun, pl330, &buf[off], pxs);
        /* DMASEV peripheral/event */
        off += PL330_Instr_DMASEV(dryRun, &buf[off], channel);
        /* DMAEND */
        off += PL330_Instr_DMAEND(dryRun, &buf[off]);
    } else {
        off += _Setup_Xfer_Cyclic(dryRun, pl330, &buf[off], pxs, channel);
    }

    /* make sure the buf and bufsize is cache line aligned. */
    if (!dryRun) {
        HAL_ASSERT(HAL_IS_CACHELINE_ALIGNED((uint32_t)buf));
        HAL_DCACHE_CleanByRange((uint32_t)buf, PL330_CHAN_BUF_LEN);
    }

    return off;
}

/**
 * @brief Generate a DMA program for the DMA command.
 *
 * @param pl330: the handle of PL330.
 * @param pxs: pl330 xfer spec.
 * @param channel: the DMA channel number
 *
 * @return - HAL_OK on success.
 *         - HAL_ERROR on fail.
 */
static HAL_Status PL330_GenDmaProg(struct HAL_PL330_DEV *pl330, struct PL330_XFER_SPEC *pxs,
                                   uint32_t channel)
{
    HAL_UNUSED struct PL330_DESC *desc = pxs->desc;
    int len;

    HAL_ASSERT(pl330 != NULL);
    HAL_ASSERT(pxs != NULL);
    HAL_ASSERT(desc != NULL);
    HAL_ASSERT(desc->mcBuf != NULL);

    len = PL330_BuildDmaProg(1, pl330, pxs, channel);
    if (len < 0 || len > PL330_CHAN_BUF_LEN) {
        HAL_DBG_ERR("xfer size is too large, try to increase mc size\n");

        return HAL_ERROR;
    }

    PL330_BuildDmaProg(0, pl330, pxs, channel);

    return HAL_OK;
}

/**
 * @brief Execute the DMAGO to start a channel.
 *
 * @param reg: the DMA_REG info.
 * @param channel: the DMA channel number.
 * @param addr: DMA program starting address, this should be DMA address
 *
 * @return HAL_OK on success, HAL_TIMEOUT on time out
 */
static HAL_Status PL330_Exec_DMAGO(struct DMA_REG *reg, uint32_t channel, uint32_t addr)
{
    char buf[8];
    uint32_t dbgInst0;
    uint32_t dbgInst1;
    int waitCount;

    PL330_Instr_DMAGO(0, buf, channel, addr, 1);

    dbgInst0 = PL330_DBGINST0(buf[1], buf[0], 0, 0);
    dbgInst1 = (uint32_t)addr;

    /* wait while debug status is busy */
    waitCount = 0;
    while ((READ_REG(reg->DBGSTATUS) & PL330_DBGSTATUS_BUSY) &&
           (waitCount < PL330_MAX_WAIT)) {
        waitCount++;
    }

    if (waitCount >= PL330_MAX_WAIT) {
        HAL_DBG("PL330 device at %p debug status busy time out\r\n", reg);

        return HAL_TIMEOUT;
    }

    /* write debug instruction 0 */
    WRITE_REG(reg->DBGINST[0], dbgInst0);
    /* write debug instruction 1 */
    WRITE_REG(reg->DBGINST[1], dbgInst1);

    /* wait while the DMA Manager is busy */
    waitCount = 0;
    while ((READ_REG(reg->DSR) & PL330_DS_DMA_STATUS) !=
           PL330_DS_DMA_STATUS_STOPPED &&
           waitCount <= PL330_MAX_WAIT) {
        waitCount++;
    }

    if (waitCount >= PL330_MAX_WAIT) {
        HAL_DBG("PL330 device at %p debug status busy time out\r\n", reg);

        return HAL_TIMEOUT;
    }

    /* run the command in DbgInst0 and DbgInst1 */
    WRITE_REG(reg->DBGCMD, 0);

    return HAL_OK;
}

static void PL330_CleanInvalidateDataBuf(struct PL330_DESC *desc)
{
    /* make sure the buf and bufsize cache line aligned. */
    if (desc->rqcfg.srcInc) {
        HAL_ASSERT(HAL_IS_CACHELINE_ALIGNED(desc->px.srcAddr));
        HAL_ASSERT(HAL_IS_CACHELINE_ALIGNED(desc->px.length));
        HAL_DCACHE_CleanByRange(desc->px.srcAddr, desc->px.length);
    }

    if (desc->rqcfg.dstInc) {
        HAL_ASSERT(HAL_IS_CACHELINE_ALIGNED(desc->px.dstAddr));
        HAL_ASSERT(HAL_IS_CACHELINE_ALIGNED(desc->px.length));
        HAL_DCACHE_InvalidateByRange(desc->px.dstAddr, desc->px.length);
    }
}

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup PL330_Exported_Functions_Group2 State and Errors Functions

 This section provides functions allowing to get the status of the module:

 *  @{
 */

/**
 * @brief PL330 Get Raw IrqStatus
 *
 * @param pl330: the handle of pl330.
 *
 * @return raw irq status
 */
uint32_t HAL_PL330_GetRawIrqStatus(struct HAL_PL330_DEV *pl330)
{
    struct DMA_REG *reg = pl330->pReg;

    return READ_REG(reg->EVENT_RIS);
}

/**
 * @brief PL330 Clear Irq
 *
 * @param pl330: the handle of pl330.
 * @param irq:   the channel irq.
 *
 * @return HAL_Status
 */
HAL_Status HAL_PL330_ClearIrq(struct HAL_PL330_DEV *pl330, uint32_t irq)
{
    struct DMA_REG *reg = pl330->pReg;

    WRITE_REG(reg->INTCLR, 1 << irq);

    return HAL_OK;
}

/**
 * @brief get the position
 *
 * @param pchan: the handle of struct PL330_CHAN.
 *
 * @return the size dma transferred.
 */
int HAL_PL330_GetPosition(struct PL330_CHAN *pchan)
{
    uint32_t val = 0, addr = 0;
    struct HAL_PL330_DEV *pl330 = pchan->pl330;
    struct PL330_DESC *desc = &pchan->desc;
    struct DMA_REG *reg = pl330->pReg;
    int transferred;

    if (desc->rqcfg.srcInc) {
        val = READ_REG(reg->CHAN_CFG[pchan->chanId].SAR);
        addr = desc->px.srcAddr;
    } else {
        val = READ_REG(reg->CHAN_CFG[pchan->chanId].DAR);
        addr = desc->px.dstAddr;
    }

    transferred = val - addr;

    return transferred;
}

/** @} */

/** @defgroup PL330_Exported_Functions_Group4 Init and DeInit Functions

 This section provides functions allowing to init and deinit the module:

 *  @{
 */

/**
 * @brief Initializes a specific PL330 dmac.
 *
 * @param pl330: the handle of PL330.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_Init(struct HAL_PL330_DEV *pl330)
{
    struct PL330_CHAN *pchan;
    uint8_t channel;

    HAL_ASSERT(pl330 != NULL);

    memset(pl330->chans, 0, sizeof(*pchan) * PL330_CHANNELS_PER_DEV);

    for (channel = 0; channel < PL330_CHANNELS_PER_DEV; channel++) {
        pchan = pl330->chans + channel;
        pchan->chanId = channel;
    }

    PL330_Read_Config(pl330);

    return HAL_OK;
}

/**
 * @brief DeInitializes a specific PL330 dmac.
 *
 * @param pl330: the handle of pl330.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_DeInit(struct HAL_PL330_DEV *pl330)
{
    uint32_t dbgInst;
    uint32_t waitCount = 0;
    uint32_t i;
    struct DMA_REG *reg = pl330->pReg;

    /* Disable all the interrupts */
    WRITE_REG(reg->INTEN, 0x00);
    /* Clear the interrupts */
    WRITE_REG(reg->INTCLR, PL330_INTCLR_ALL_MASK);
    /* Kill the dma channel threads */
    for (i = 0; i < PL330_CHANNELS_PER_DEV; i++) {
        while ((READ_REG(reg->DBGSTATUS) & PL330_DBGSTATUS_BUSY) &&
               (waitCount < PL330_MAX_WAIT)) {
            waitCount++;
        }

        dbgInst = PL330_DBGINST0(0, 0x01, i, 1);
        WRITE_REG(reg->DBGINST[0], dbgInst);
        WRITE_REG(reg->DBGINST[1], 0x0);
        WRITE_REG(reg->DBGCMD, 0x0);
    }
    /* Kill the manager thread    */
    dbgInst = PL330_DBGINST0(0, 0x01, 0, 0);
    WRITE_REG(reg->DBGINST[0], dbgInst);
    WRITE_REG(reg->DBGINST[1], 0x0);
    WRITE_REG(reg->DBGCMD, 0x0);

    return HAL_OK;
}

/** @} */

/** @defgroup PL330_Exported_Functions_Group3 IO Functions

 This section provides functions allowing to IO controlling:

 *  @{
 */

/**
 * @brief Start a DMA channel with the desc request.
 *
 * @param pchan: the hanlde of struct PL330_CHAN.
 *
 * @return
 *        - HAL_OK on success
 *        - HAL_BUSY if DMA is busy
 *        - HAL_ERROR on other failures
 */
HAL_Status HAL_PL330_Start(struct PL330_CHAN *pchan)
{
    HAL_Status ret = HAL_OK;
    uint32_t ccr;
    struct PL330_XFER_SPEC xs;
    uint32_t channel = pchan->chanId;
    struct HAL_PL330_DEV *pl330 = pchan->pl330;
    struct PL330_DESC *desc = &pchan->desc;
    struct DMA_REG *reg = pl330->pReg;

    HAL_ASSERT(pl330 != NULL);
    HAL_ASSERT(pchan->mcBuf);

    if (pl330->pcfg.mode & DMAC_MODE_NS) {
        desc->rqcfg.nonsecure = 1;
    } else {
        desc->rqcfg.nonsecure = 0;
    }

    ccr = _Prepare_CCR(&desc->rqcfg);

    xs.ccr = ccr;
    xs.desc = desc;
    desc->mcBuf = pchan->mcBuf;

    ret = PL330_GenDmaProg(pl330, &xs, channel);
    if (ret) {
        return HAL_ERROR;
    }

    /* enable the interrupt */
    SET_BIT(reg->INTEN, 0x01 << channel);

    return PL330_Exec_DMAGO(pl330->pReg, channel, (uint32_t)desc->mcBuf);
}

/**
 * @brief Stop a DMA channel.
 *
 * @param pchan: the hanlde of struct PL330_CHAN.
 *
 * @return
 *        - HAL_OK on success
 *        - HAL_BUSY if DMA is busy
 *        - HAL_ERROR on other failures
 */
HAL_Status HAL_PL330_Stop(struct PL330_CHAN *pchan)
{
    uint32_t intEn = READ_REG(pchan->pl330->pReg->INTEN);

    HAL_ASSERT(pchan != NULL);

    PL330_Exec_DMAKILL(pchan->pl330->pReg, pchan->chanId, 1);

    if (intEn & (1 << pchan->chanId)) {
        WRITE_REG(pchan->pl330->pReg->INTCLR, 1 << pchan->chanId);
    }

    WRITE_REG(pchan->pl330->pReg->INTEN, intEn & ~(1 << pchan->chanId));

    return HAL_OK;
}

/**
 * @brief PL330 IrqHandler
 *
 * @param pl330: the handle of pl330.
 *
 * @return: raw irq status
 */
uint32_t HAL_PL330_IrqHandler(struct HAL_PL330_DEV *pl330)
{
    struct DMA_REG *reg = pl330->pReg;
    uint32_t val, inten;
    unsigned int ev, i = 0;

    val = READ_REG(reg->FSRD) & 0x1;
    if (val) {
        /*
         * if DMA manager is fault
         */
        HAL_DBG("Fault Type: 0x%lx\n", READ_REG(reg->FTRD));
        HAL_DBG("Fault PC 0x%lx\n", READ_REG(reg->DPC));
        /* kill the DMA manager thread */
        /* Should we disable interrupt?*/
        PL330_Exec_DMAKILL(pl330->pReg, 0, 0);
    }

    val = READ_REG(reg->FSRC) & ((1 << pl330->pcfg.numChan) - 1);
    if (val) {
        while (i < pl330->pcfg.numChan) {
            if (val & (1 << i)) {
                HAL_DBG("Reset Channel-%d\t CS-%lx\n",
                        i, READ_REG(reg->CHAN_STS[i].CSR));
                HAL_DBG("Reset Channel-%d\t FTC-%lx\n",
                        i, READ_REG(reg->FTR[i]));
                /* kill the channel thread */
                /* Should we disable interrupt? */
                PL330_Exec_DMAKILL(pl330->pReg, i, 1);
            }
            i++;
        }
    }

    /* Check which event happened i.e, thread notified */
    val = READ_REG(reg->EVENT_RIS);
    inten = READ_REG(reg->INTEN);

    for (ev = 0; ev < PL330_CHANNELS_PER_DEV; ev++) {
        if (val & (1 << ev)) { /* Event occurred */
            /* Clear the event */
            if (inten & (1 << ev)) {
                WRITE_REG(reg->INTCLR, 1 << ev);
            }
        }
    }

    /* return raw irq status */
    return val;
}

/**
 * @brief Set mc buf resource for chan
 *
 * @param pchan: the handle of struct PL330_CHAN.
 * @param buf: mc buf addr.
 *
 * @return HAL_Status.
 *
 * @note must be invoked before function HAL_PL330_PrepDmaXXX.
 */
HAL_Status HAL_PL330_SetMcBuf(struct PL330_CHAN *pchan, void *buf)
{
    HAL_ASSERT(pchan);
    HAL_ASSERT(buf);

    pchan->mcBuf = buf;

    return HAL_OK;
}

/**
 * @brief Get mc buf resource of chan
 *
 * @param pchan: the handle of struct PL330_CHAN.
 *
 * @return mc buf addr.
 */
void *HAL_PL330_GetMcBuf(struct PL330_CHAN *pchan)
{
    HAL_ASSERT(pchan);

    return pchan->mcBuf;
}

/**
 * @brief Get desc resource of chan
 *
 * @param pchan: the handle of struct PL330_CHAN.
 *
 * @return desc ptr.
 */
const struct PL330_DESC *HAL_PL330_GetDesc(struct PL330_CHAN *pchan)
{
    HAL_ASSERT(pchan);

    return &pchan->desc;
}

/**
 * @brief Request a dma channel
 *
 * @param pl330: the handle of struct HAL_PL330_DEV.
 * @param id: the peri id.
 *
 * @return a idle dma channel.
 */
struct PL330_CHAN *HAL_PL330_RequestChannel(struct HAL_PL330_DEV *pl330, DMA_REQ_Type id)
{
    int i = 0;
    struct PL330_CHAN *pchan = NULL;

    for (i = 0; i < PL330_CHANNELS_PER_DEV; i++) {
        if (pl330->chans[i].used) {
            continue;
        }
        pchan = &pl330->chans[i];
        pchan->used = true;
        pchan->periId = id;
        pchan->pl330 = pl330;
        break;
    }

    return pchan;
}

/**
 * @brief Release a dma channel
 *
 * @param pchan: the handle of struct PL330_CHAN.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_ReleaseChannel(struct PL330_CHAN *pchan)
{
    HAL_ASSERT(pchan);

    pchan->periId = 0;
    pchan->used = false;

    return HAL_OK;
}

/**
 * @brief Config a pl330 dma channel
 *
 * @param pchan: the handle of struct PL330_CHAN.
 * @param config: the peri req config.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_Config(struct PL330_CHAN *pchan, struct DMA_SLAVE_CONFIG *config)
{
    HAL_ASSERT(pchan);

    if (config->direction == DMA_MEM_TO_DEV) {
        if (config->dstAddr) {
            pchan->fifoAddr = config->dstAddr;
        }
        if (config->dstAddrWidth) {
            pchan->brstSz = PL330_ToBurstSizeBits(config->dstAddrWidth);
        }
        if (config->dstMaxBurst) {
            pchan->brstLen = config->dstMaxBurst;
        }
        if (config->srcInterlaceSize) {
            pchan->srcInterlaceSize = config->srcInterlaceSize;
        }
    } else if (config->direction == DMA_DEV_TO_MEM) {
        if (config->srcAddr) {
            pchan->fifoAddr = config->srcAddr;
        }
        if (config->srcAddrWidth) {
            pchan->brstSz = PL330_ToBurstSizeBits(config->srcAddrWidth);
        }
        if (config->srcMaxBurst) {
            pchan->brstLen = config->srcMaxBurst;
        }
        if (config->dstInterlaceSize) {
            pchan->dstInterlaceSize = config->dstInterlaceSize;
        }
    }

    return HAL_OK;
}

/**
 * @brief Prepare a cyclic dma transfer for the channel
 *
 * @param pchan: tthe handle of struct PL330_CHAN.
 * @param dmaAddr: the memory addr.
 * @param len: data len.
 * @param periodLen: periodic len.
 * @param direction: transfer direction.
 * @param callback: callback function.
 * @param cparam: callback param.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_PrepDmaCyclic(struct PL330_CHAN *pchan, uint32_t dmaAddr,
                                   uint32_t len, uint32_t periodLen,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   PL330_Callback callback, void *cparam)
{
    struct HAL_PL330_DEV *pl330 = pchan->pl330;
    struct PL330_DESC *desc = &pchan->desc;
    uint32_t dst;
    uint32_t src;

    HAL_ASSERT(pl330 != NULL);
    HAL_ASSERT(len % periodLen == 0);
    HAL_ASSERT(direction == DMA_MEM_TO_DEV || direction == DMA_DEV_TO_MEM);

    memset(desc, 0x0, sizeof(*desc));

    switch (direction) {
    case DMA_MEM_TO_DEV:
        desc->rqcfg.srcInc = 1;
        desc->rqcfg.dstInc = 0;
        src = dmaAddr;
        dst = pchan->fifoAddr;
        break;
    case DMA_DEV_TO_MEM:
        desc->rqcfg.srcInc = 0;
        desc->rqcfg.dstInc = 1;
        src = pchan->fifoAddr;
        dst = dmaAddr;
        break;
    default:

        return HAL_ERROR;
    }

    desc->peri = pchan->periId;
    desc->dir = direction;
    desc->rqcfg.brstSize = pchan->brstSz;

    if (pl330->peripReqType == BURST) {
        desc->rqcfg.brstLen = pchan->brstLen;
    } else {
        desc->rqcfg.brstLen = 1;
    }

    desc->bytesReq = len;
    desc->px.srcAddr = src;
    desc->px.dstAddr = dst;
    desc->px.length = periodLen;

    desc->cyclic = true;
    desc->numPeriods = len / periodLen;

    desc->callback = callback;
    desc->cparam = cparam;

    desc->srcInterlaceSize = pchan->srcInterlaceSize;
    desc->dstInterlaceSize = pchan->dstInterlaceSize;

    HAL_DBG("%s: srcInterlaceSize: %d, dstInterlaceSize: %d\n", __func__,
            desc->srcInterlaceSize, desc->dstInterlaceSize);

    return HAL_OK;
}

/**
 * @brief Prepare a single dma transfer for the channel
 *
 * @param pchan: the handle of struct PL330_CHAN.
 * @param dmaAddr: the memory addr.
 * @param len: data len.
 * @param direction: transfer direction.
 * @param callback: callback function.
 * @param cparam: callback param.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_PrepDmaSingle(struct PL330_CHAN *pchan, uint32_t dmaAddr,
                                   uint32_t len,
                                   eDMA_TRANSFER_DIRECTION direction,
                                   PL330_Callback callback, void *cparam)
{
    struct HAL_PL330_DEV *pl330 = pchan->pl330;
    struct PL330_DESC *desc = &pchan->desc;
    uint32_t dst;
    uint32_t src;

    HAL_ASSERT(pl330 != NULL);
    HAL_ASSERT(direction == DMA_MEM_TO_DEV || direction == DMA_DEV_TO_MEM);

    memset(desc, 0x0, sizeof(*desc));

    switch (direction) {
    case DMA_MEM_TO_DEV:
        desc->rqcfg.srcInc = 1;
        desc->rqcfg.dstInc = 0;
        src = dmaAddr;
        dst = pchan->fifoAddr;
        break;
    case DMA_DEV_TO_MEM:
        desc->rqcfg.srcInc = 0;
        desc->rqcfg.dstInc = 1;
        src = pchan->fifoAddr;
        dst = dmaAddr;
        break;
    default:

        return HAL_ERROR;
    }

    desc->peri = pchan->periId;
    desc->dir = direction;
    desc->rqcfg.brstSize = pchan->brstSz;

    if (pl330->peripReqType == BURST) {
        desc->rqcfg.brstLen = pchan->brstLen;
    } else {
        desc->rqcfg.brstLen = 1;
    }

    desc->bytesReq = len;
    desc->px.srcAddr = src;
    desc->px.dstAddr = dst;
    desc->px.length = len;

    desc->cyclic = false;
    desc->numPeriods = 0;

    desc->callback = callback;
    desc->cparam = cparam;

    PL330_CleanInvalidateDataBuf(desc);

    return HAL_OK;
}

/**
 * @brief Prepare a dma memcpy
 *
 * @param pchan: the handle of struct PL330_CHAN.
 * @param dst: the memory dst addr.
 * @param src: the memory src addr.
 * @param len: data len.
 * @param callback: callback function.
 * @param cparam: callback param.
 *
 * @return
 *        - HAL_OK on success.
 *        - HAL_ERROR on fail.
 */
HAL_Status HAL_PL330_PrepDmaMemcpy(struct PL330_CHAN *pchan, uint32_t dst,
                                   uint32_t src, uint32_t len,
                                   PL330_Callback callback, void *cparam)
{
    struct HAL_PL330_DEV *pl330 = pchan->pl330;
    struct PL330_DESC *desc = &pchan->desc;
    int burst;

    HAL_ASSERT(pl330 != NULL);
    HAL_ASSERT(len > 0);

    memset(desc, 0x0, sizeof(*desc));

    desc->px.srcAddr = src;
    desc->px.dstAddr = dst;
    desc->px.length = len;
    desc->rqcfg.srcInc = 1;
    desc->rqcfg.dstInc = 1;
    desc->dir = DMA_MEM_TO_MEM;

    /* Select max possible burst size */
    burst = pl330->pcfg.dataBusWidth / 8;

    /*
     * Make sure we use a burst size that aligns with all the memcpy
     * parameters because our DMA programming algorithm doesn't cope with
     * transfers which straddle an entry in the DMA device's MFIFO.
     */
    while ((src | dst | len) & (burst - 1)) {
        burst /= 2;
    }

    desc->rqcfg.brstSize = 0;
    while (burst != (1 << desc->rqcfg.brstSize)) {
        desc->rqcfg.brstSize++;
    }

    /*
     * If burst size is smaller than bus width then make sure we only
     * transfer one at a time to avoid a burst stradling an MFIFO entry.
     */
    if (desc->rqcfg.brstSize * 8 < pl330->pcfg.dataBusWidth) {
        desc->rqcfg.brstLen = 1;
    }

    desc->rqcfg.brstLen = getBurstLen(desc, pl330, len);
    desc->bytesReq = len;

    desc->callback = callback;
    desc->cparam = cparam;

    PL330_CleanInvalidateDataBuf(desc);

    return HAL_OK;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_PL330_MODULE_ENABLED */
