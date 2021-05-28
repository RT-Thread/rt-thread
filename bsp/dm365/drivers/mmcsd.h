/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

#ifndef __DAVINCI_MMC_H__
#define __DAVINCI_MMC_H__

/* DAVINCI_MMCCTL definitions */
#define MMCCTL_DATRST         (1 << 0)
#define MMCCTL_CMDRST         (1 << 1)
#define MMCCTL_WIDTH_8_BIT    (1 << 8)
#define MMCCTL_WIDTH_4_BIT    (1 << 2)
#define MMCCTL_DATEG_DISABLED (0 << 6)
#define MMCCTL_DATEG_RISING   (1 << 6)
#define MMCCTL_DATEG_FALLING  (2 << 6)
#define MMCCTL_DATEG_BOTH     (3 << 6)
#define MMCCTL_PERMDR_LE      (0 << 9)
#define MMCCTL_PERMDR_BE      (1 << 9)
#define MMCCTL_PERMDX_LE      (0 << 10)
#define MMCCTL_PERMDX_BE      (1 << 10)

/* DAVINCI_MMCCLK definitions */
#define MMCCLK_CLKEN          (1 << 8)
#define MMCCLK_CLKRT_MASK     (0xFF << 0)

/* IRQ bit definitions, for DAVINCI_MMCST0 and DAVINCI_MMCIM */
#define MMCST0_DATDNE         (1 << 0)  /* data done */
#define MMCST0_BSYDNE         (1 << 1)  /* busy done */
#define MMCST0_RSPDNE         (1 << 2)  /* command done */
#define MMCST0_TOUTRD         (1 << 3)  /* data read timeout */
#define MMCST0_TOUTRS         (1 << 4)  /* command response timeout */
#define MMCST0_CRCWR          (1 << 5)  /* data write CRC error */
#define MMCST0_CRCRD          (1 << 6)  /* data read CRC error */
#define MMCST0_CRCRS          (1 << 7)  /* command response CRC error */
#define MMCST0_DXRDY          (1 << 9)  /* data transmit ready (fifo empty) */
#define MMCST0_DRRDY          (1 << 10) /* data receive ready (data in fifo)*/
#define MMCST0_DATED          (1 << 11) /* DAT3 edge detect */
#define MMCST0_TRNDNE         (1 << 12) /* transfer done */

/* DAVINCI_MMCST1 definitions */
#define MMCST1_BUSY           (1 << 0)

/* DAVINCI_MMCCMD definitions */
#define MMCCMD_CMD_MASK       (0x3F << 0)
#define MMCCMD_PPLEN          (1 << 7)
#define MMCCMD_BSYEXP         (1 << 8)
#define MMCCMD_RSPFMT_MASK    (3 << 9)
#define MMCCMD_RSPFMT_NONE    (0 << 9)
#define MMCCMD_RSPFMT_R1456   (1 << 9)
#define MMCCMD_RSPFMT_R2      (2 << 9)
#define MMCCMD_RSPFMT_R3      (3 << 9)
#define MMCCMD_DTRW           (1 << 11)
#define MMCCMD_STRMTP         (1 << 12)
#define MMCCMD_WDATX          (1 << 13)
#define MMCCMD_INITCK         (1 << 14)
#define MMCCMD_DCLR           (1 << 15)
#define MMCCMD_DMATRIG        (1 << 16)

/* DAVINCI_MMCFIFOCTL definitions */
#define MMCFIFOCTL_FIFORST    (1 << 0)
#define MMCFIFOCTL_FIFODIR_WR (1 << 1)
#define MMCFIFOCTL_FIFODIR_RD (0 << 1)
#define MMCFIFOCTL_FIFOLEV    (1 << 2) /* 0 = 128 bits, 1 = 256 bits */
#define MMCFIFOCTL_ACCWD_4    (0 << 3) /* access width of 4 bytes    */
#define MMCFIFOCTL_ACCWD_3    (1 << 3) /* access width of 3 bytes    */
#define MMCFIFOCTL_ACCWD_2    (2 << 3) /* access width of 2 bytes    */
#define MMCFIFOCTL_ACCWD_1    (3 << 3) /* access width of 1 byte     */

/* DAVINCI_SDIOST0 definitions */
#define SDIOST0_DAT1_HI       (1 << 0)
#define SDIOST0_INTPRD        (1 << 1)
#define SDIOST0_RDWTST        (1 << 2)

/* DAVINCI_SDIOIEN definitions */
#define SDIOIEN_IOINTEN       (1 << 0)
#define SDIOIEN_RWSEN         (1 << 1)

/* DAVINCI_SDIOIST definitions */
#define SDIOIST_IOINT         (1 << 0)
#define SDIOIST_RWS           (1 << 1)

/* MMCSD Init clock in Hz in opendrain mode */
#define MMCSD_INIT_CLOCK        200000

#define MAX_CCNT    ((1 << 16) - 1)

#define MAX_NR_SG   16

#define MMC_DATA_WRITE  (1 << 8)
#define MMC_DATA_READ   (1 << 9)
#define MMC_DATA_STREAM (1 << 10)

typedef struct {
    volatile rt_uint32_t MMCCTL;
    volatile rt_uint32_t MMCCLK;
    volatile rt_uint32_t MMCST0;
    volatile rt_uint32_t MMCST1;
    volatile rt_uint32_t MMCIM;
    volatile rt_uint32_t MMCTOR;
    volatile rt_uint32_t MMCTOD;
    volatile rt_uint32_t MMCBLEN;
    volatile rt_uint32_t MMCNBLK;
    volatile rt_uint32_t MMCNBLC;
    volatile rt_uint32_t MMCDRR;
    volatile rt_uint32_t MMCDXR;
    volatile rt_uint32_t MMCCMD;
    volatile rt_uint32_t MMCARGHL;
    volatile rt_uint32_t MMCRSP01;
    volatile rt_uint32_t MMCRSP23;
    volatile rt_uint32_t MMCRSP45;
    volatile rt_uint32_t MMCRSP67;
    volatile rt_uint32_t MMCDRSP;
    volatile rt_uint32_t reserved0;
    volatile rt_uint32_t MMCCIDX;
    volatile rt_uint32_t reserved1[4];
    volatile rt_uint32_t SDIOCTL;
    volatile rt_uint32_t SDIOST0;
    volatile rt_uint32_t SDIOIEN;
    volatile rt_uint32_t SDIOIST;
    volatile rt_uint32_t MMCFIFOCTL;
}mmcsd_regs_t;

extern int rt_hw_mmcsd_init(void);

#endif
