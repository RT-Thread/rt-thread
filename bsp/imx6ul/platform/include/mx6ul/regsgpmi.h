/*
 * Copyright (C) 2011-2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
 */

#ifndef _GPMI_H
#define _GPMI_H  1

#include "regs.h"
//#include "registers.h"

#ifndef REGS_GPMI_BASE
#define REGS_GPMI_BASE (REGS_BASE + 0x112000)
#endif

/*
 * HW_GPMI_CTRL0 - GPMI Control Register 0
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned XFER_COUNT:16;
        unsigned ADDRESS_INCREMENT:1;
        unsigned ADDRESS:3;
        unsigned CS:3;
        unsigned WORD_LENGTH:1;
        unsigned COMMAND_MODE:2;
        unsigned UDMA:1;
        unsigned LOCK_CS:1;
        unsigned DEV_IRQ_EN:1;
        unsigned RUN:1;
        unsigned CLKGATE:1;
        unsigned SFTRST:1;
    } B;
} hw_gpmi_ctrl0_t;
#endif

/*
 * constants & macros for entire HW_GPMI_CTRL0 register
 */
#define HW_GPMI_CTRL0_ADDR      (0x00112000)
#define HW_GPMI_CTRL0_SET_ADDR  (0x00112004)
#define HW_GPMI_CTRL0_CLR_ADDR  (0x00112008)
#define HW_GPMI_CTRL0_TOG_ADDR  (0x0011200c)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_CTRL0           (*(volatile hw_gpmi_ctrl0_t *) HW_GPMI_CTRL0_ADDR)
#define HW_GPMI_CTRL0_RD()      (HW_GPMI_CTRL0.U)
#define HW_GPMI_CTRL0_WR(v)     (HW_GPMI_CTRL0.U = (v))
#define HW_GPMI_CTRL0_SET(v)    ((*(volatile reg32_t *) HW_GPMI_CTRL0_SET_ADDR) = (v))
#define HW_GPMI_CTRL0_CLR(v)    ((*(volatile reg32_t *) HW_GPMI_CTRL0_CLR_ADDR) = (v))
#define HW_GPMI_CTRL0_TOG(v)    ((*(volatile reg32_t *) HW_GPMI_CTRL0_TOG_ADDR) = (v))
#else
#define HW_GPMI_CTRL0_RD()      (_rbase->mem32_read(HW_GPMI_CTRL0_ADDR))
#define HW_GPMI_CTRL0_WR(v)     (_rbase->mem32_write(HW_GPMI_CTRL0_ADDR,(v)))
#define HW_GPMI_CTRL0_SET(v)    (_rbase->mem32_write(HW_GPMI_CTRL0_SET_ADDR,(v)))
#define HW_GPMI_CTRL0_CLR(v)    (_rbase->mem32_write(HW_GPMI_CTRL0_CLR_ADDR,(v)))
#define HW_GPMI_CTRL0_TOG(v)    (_rbase->mem32_write(HW_GPMI_CTRL0_TOG_ADDR,(v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_CTRL0 bitfields
 */
/* --- Register HW_GPMI_CTRL0, field SFTRST */

#define BP_GPMI_CTRL0_SFTRST      31
#define BM_GPMI_CTRL0_SFTRST      0x80000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_CTRL0_SFTRST(v)   ((((reg32_t) v) << 31) & BM_GPMI_CTRL0_SFTRST)
#else
#define BF_GPMI_CTRL0_SFTRST(v)   (((v) << 31) & BM_GPMI_CTRL0_SFTRST)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_SFTRST(v)   BF_CS1(GPMI_CTRL0, SFTRST, v)
#endif

#define BV_GPMI_CTRL0_SFTRST__RUN    0x0
#define BV_GPMI_CTRL0_SFTRST__RESET  0x1

/* --- Register HW_GPMI_CTRL0, field CLKGATE */

#define BP_GPMI_CTRL0_CLKGATE      30
#define BM_GPMI_CTRL0_CLKGATE      0x40000000

#define BF_GPMI_CTRL0_CLKGATE(v)   (((v) << 30) & BM_GPMI_CTRL0_CLKGATE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_CLKGATE(v)   BF_CS1(GPMI_CTRL0, CLKGATE, v)
#endif

#define BV_GPMI_CTRL0_CLKGATE__RUN      0x0
#define BV_GPMI_CTRL0_CLKGATE__NO_CLKS  0x1

/* --- Register HW_GPMI_CTRL0, field RUN */

#define BP_GPMI_CTRL0_RUN      29
#define BM_GPMI_CTRL0_RUN      0x20000000

#define BF_GPMI_CTRL0_RUN(v)   (((v) << 29) & BM_GPMI_CTRL0_RUN)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_RUN(v)   BF_CS1(GPMI_CTRL0, RUN, v)
#endif

#define BV_GPMI_CTRL0_RUN__IDLE  0x0
#define BV_GPMI_CTRL0_RUN__BUSY  0x1

/* --- Register HW_GPMI_CTRL0, field DEV_IRQ_EN */

#define BP_GPMI_CTRL0_DEV_IRQ_EN      28
#define BM_GPMI_CTRL0_DEV_IRQ_EN      0x10000000

#define BF_GPMI_CTRL0_DEV_IRQ_EN(v)   (((v) << 28) & BM_GPMI_CTRL0_DEV_IRQ_EN)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_DEV_IRQ_EN(v)   BF_CS1(GPMI_CTRL0, DEV_IRQ_EN, v)
#endif

/* --- Register HW_GPMI_CTRL0, field LOCK_CS */

#define BP_GPMI_CTRL0_LOCK_CS      27
#define BM_GPMI_CTRL0_LOCK_CS      0x08000000

#define BF_GPMI_CTRL0_LOCK_CS(v)   (((v) << 27) & BM_GPMI_CTRL0_LOCK_CS)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_LOCK_CS(v)   BF_CS1(GPMI_CTRL0, LOCK_CS, v)
#endif

#define BV_GPMI_CTRL0_LOCK_CS__DISABLED  0x0
#define BV_GPMI_CTRL0_LOCK_CS__ENABLED   0x1

/* --- Register HW_GPMI_CTRL0, field UDMA */

#define BP_GPMI_CTRL0_UDMA      26
#define BM_GPMI_CTRL0_UDMA      0x04000000

#define BF_GPMI_CTRL0_UDMA(v)   (((v) << 26) & BM_GPMI_CTRL0_UDMA)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_UDMA(v)   BF_CS1(GPMI_CTRL0, UDMA, v)
#endif

#define BV_GPMI_CTRL0_UDMA__DISABLED  0x0
#define BV_GPMI_CTRL0_UDMA__ENABLED   0x1

/* --- Register HW_GPMI_CTRL0, field COMMAND_MODE */

#define BP_GPMI_CTRL0_COMMAND_MODE      24
#define BM_GPMI_CTRL0_COMMAND_MODE      0x03000000

#define BF_GPMI_CTRL0_COMMAND_MODE(v)   (((v) << 24) & BM_GPMI_CTRL0_COMMAND_MODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_COMMAND_MODE(v)   BF_CS1(GPMI_CTRL0, COMMAND_MODE, v)
#endif

#define BV_GPMI_CTRL0_COMMAND_MODE__WRITE             0x0
#define BV_GPMI_CTRL0_COMMAND_MODE__READ              0x1
#define BV_GPMI_CTRL0_COMMAND_MODE__READ_AND_COMPARE  0x2
#define BV_GPMI_CTRL0_COMMAND_MODE__WAIT_FOR_READY    0x3

/* --- Register HW_GPMI_CTRL0, field WORD_LENGTH */

#define BP_GPMI_CTRL0_WORD_LENGTH      23
#define BM_GPMI_CTRL0_WORD_LENGTH      0x00800000

#define BF_GPMI_CTRL0_WORD_LENGTH(v)   (((v) << 23) & BM_GPMI_CTRL0_WORD_LENGTH)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_WORD_LENGTH(v)   BF_CS1(GPMI_CTRL0, WORD_LENGTH, v)
#endif

#define BV_GPMI_CTRL0_WORD_LENGTH__16_BIT  0x0
#define BV_GPMI_CTRL0_WORD_LENGTH__8_BIT   0x1

/* --- Register HW_GPMI_CTRL0, field CS */

#define BP_GPMI_CTRL0_CS      20
#define BM_GPMI_CTRL0_CS      0x00700000

#define BF_GPMI_CTRL0_CS(v)   (((v) << 20) & BM_GPMI_CTRL0_CS)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_CS(v)   BF_CS1(GPMI_CTRL0, CS, v)
#endif

/* --- Register HW_GPMI_CTRL0, field ADDRESS */

#define BP_GPMI_CTRL0_ADDRESS      17
#define BM_GPMI_CTRL0_ADDRESS      0x000E0000

#define BF_GPMI_CTRL0_ADDRESS(v)   (((v) << 17) & BM_GPMI_CTRL0_ADDRESS)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_ADDRESS(v)   BF_CS1(GPMI_CTRL0, ADDRESS, v)
#endif

#define BV_GPMI_CTRL0_ADDRESS__NAND_DATA  0x0
#define BV_GPMI_CTRL0_ADDRESS__NAND_CLE   0x1
#define BV_GPMI_CTRL0_ADDRESS__NAND_ALE   0x2

/* --- Register HW_GPMI_CTRL0, field ADDRESS_INCREMENT */

#define BP_GPMI_CTRL0_ADDRESS_INCREMENT      16
#define BM_GPMI_CTRL0_ADDRESS_INCREMENT      0x00010000

#define BF_GPMI_CTRL0_ADDRESS_INCREMENT(v)   (((v) << 16) & BM_GPMI_CTRL0_ADDRESS_INCREMENT)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_ADDRESS_INCREMENT(v)   BF_CS1(GPMI_CTRL0, ADDRESS_INCREMENT, v)
#endif

#define BV_GPMI_CTRL0_ADDRESS_INCREMENT__DISABLED  0x0
#define BV_GPMI_CTRL0_ADDRESS_INCREMENT__ENABLED   0x1

/* --- Register HW_GPMI_CTRL0, field XFER_COUNT */

#define BP_GPMI_CTRL0_XFER_COUNT      0
#define BM_GPMI_CTRL0_XFER_COUNT      0x0000FFFF

#define BF_GPMI_CTRL0_XFER_COUNT(v)   (((v) << 0) & BM_GPMI_CTRL0_XFER_COUNT)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL0_XFER_COUNT(v)   (HW_GPMI_CTRL0.B.XFER_COUNT = (v))
#endif

/*
 * HW_GPMI_COMPARE - GPMI Compare Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned REFERENCE:16;
        unsigned MASK:16;
    } B;
} hw_gpmi_compare_t;
#endif

/*
 * constants & macros for entire HW_GPMI_COMPARE register
 */
#define HW_GPMI_COMPARE_ADDR      (0x00112010)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_COMPARE           (*(volatile hw_gpmi_compare_t *) HW_GPMI_COMPARE_ADDR)
#define HW_GPMI_COMPARE_RD()      (HW_GPMI_COMPARE.U)
#define HW_GPMI_COMPARE_WR(v)     (HW_GPMI_COMPARE.U = (v))
#define HW_GPMI_COMPARE_SET(v)    (HW_GPMI_COMPARE_WR(HW_GPMI_COMPARE_RD() |  (v)))
#define HW_GPMI_COMPARE_CLR(v)    (HW_GPMI_COMPARE_WR(HW_GPMI_COMPARE_RD() & ~(v)))
#define HW_GPMI_COMPARE_TOG(v)    (HW_GPMI_COMPARE_WR(HW_GPMI_COMPARE_RD() ^  (v)))
#else
#define HW_GPMI_COMPARE_RD()      (_rbase->mem32_read(HW_GPMI_COMPARE_ADDR))
#define HW_GPMI_COMPARE_WR(v)     (_rbase->mem32_write(HW_GPMI_COMPARE_ADDR,(v)))
#define HW_GPMI_COMPARE_SET(v)    (HW_GPMI_COMPARE_WR(HW_GPMI_COMPARE_RD() |  (v)))
#define HW_GPMI_COMPARE_CLR(v)    (HW_GPMI_COMPARE_WR(HW_GPMI_COMPARE_RD() & ~(v)))
#define HW_GPMI_COMPARE_TOG(v)    (HW_GPMI_COMPARE_WR(HW_GPMI_COMPARE_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_COMPARE bitfields
 */
/* --- Register HW_GPMI_COMPARE, field MASK */

#define BP_GPMI_COMPARE_MASK      16
#define BM_GPMI_COMPARE_MASK      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_COMPARE_MASK(v)   ((((reg32_t) v) << 16) & BM_GPMI_COMPARE_MASK)
#else
#define BF_GPMI_COMPARE_MASK(v)   (((v) << 16) & BM_GPMI_COMPARE_MASK)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_COMPARE_MASK(v)   (HW_GPMI_COMPARE.B.MASK = (v))
#endif

/* --- Register HW_GPMI_COMPARE, field REFERENCE */

#define BP_GPMI_COMPARE_REFERENCE      0
#define BM_GPMI_COMPARE_REFERENCE      0x0000FFFF

#define BF_GPMI_COMPARE_REFERENCE(v)   (((v) << 0) & BM_GPMI_COMPARE_REFERENCE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_COMPARE_REFERENCE(v)   (HW_GPMI_COMPARE.B.REFERENCE = (v))
#endif

/*
 * HW_GPMI_ECCCTRL - GPMI Integrated ECC Control Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned BUFFER_MASK:9;
        unsigned RSVD1:3;
        unsigned ENABLE_ECC:1;
        unsigned ECC_CMD:2;
        unsigned RSVD2:1;
        unsigned HANDLE:16;
    } B;
} hw_gpmi_eccctrl_t;
#endif

/*
 * constants & macros for entire HW_GPMI_ECCCTRL register
 */
#define HW_GPMI_ECCCTRL_ADDR      (0x00112020)
#define HW_GPMI_ECCCTRL_SET_ADDR  (0x00112024)
#define HW_GPMI_ECCCTRL_CLR_ADDR  (0x00112028)
#define HW_GPMI_ECCCTRL_TOG_ADDR  (0x0011202c)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_ECCCTRL           (*(volatile hw_gpmi_eccctrl_t *) HW_GPMI_ECCCTRL_ADDR)
#define HW_GPMI_ECCCTRL_RD()      (HW_GPMI_ECCCTRL.U)
#define HW_GPMI_ECCCTRL_WR(v)     (HW_GPMI_ECCCTRL.U = (v))
#define HW_GPMI_ECCCTRL_SET(v)    ((*(volatile reg32_t *) HW_GPMI_ECCCTRL_SET_ADDR) = (v))
#define HW_GPMI_ECCCTRL_CLR(v)    ((*(volatile reg32_t *) HW_GPMI_ECCCTRL_CLR_ADDR) = (v))
#define HW_GPMI_ECCCTRL_TOG(v)    ((*(volatile reg32_t *) HW_GPMI_ECCCTRL_TOG_ADDR) = (v))
#else
#define HW_GPMI_ECCCTRL_RD()      (_rbase->mem32_read(HW_GPMI_ECCCTRL_ADDR))
#define HW_GPMI_ECCCTRL_WR(v)     (_rbase->mem32_write(HW_GPMI_ECCCTRL_ADDR,(v)))
#define HW_GPMI_ECCCTRL_SET(v)    (_rbase->mem32_write(HW_GPMI_ECCCTRL_SET_ADDR,(v)))
#define HW_GPMI_ECCCTRL_CLR(v)    (_rbase->mem32_write(HW_GPMI_ECCCTRL_CLR_ADDR,(v)))
#define HW_GPMI_ECCCTRL_TOG(v)    (_rbase->mem32_write(HW_GPMI_ECCCTRL_TOG_ADDR,(v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_ECCCTRL bitfields
 */
/* --- Register HW_GPMI_ECCCTRL, field HANDLE */

#define BP_GPMI_ECCCTRL_HANDLE      16
#define BM_GPMI_ECCCTRL_HANDLE      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_ECCCTRL_HANDLE(v)   ((((reg32_t) v) << 16) & BM_GPMI_ECCCTRL_HANDLE)
#else
#define BF_GPMI_ECCCTRL_HANDLE(v)   (((v) << 16) & BM_GPMI_ECCCTRL_HANDLE)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_ECCCTRL_HANDLE(v)   (HW_GPMI_ECCCTRL.B.HANDLE = (v))
#endif

/* --- Register HW_GPMI_ECCCTRL, field RSVD2 */

#define BP_GPMI_ECCCTRL_RSVD2      15
#define BM_GPMI_ECCCTRL_RSVD2      0x00008000

#define BF_GPMI_ECCCTRL_RSVD2(v)   (((v) << 15) & BM_GPMI_ECCCTRL_RSVD2)
/* --- Register HW_GPMI_ECCCTRL, field ECC_CMD */

#define BP_GPMI_ECCCTRL_ECC_CMD      13
#define BM_GPMI_ECCCTRL_ECC_CMD      0x00006000

#define BF_GPMI_ECCCTRL_ECC_CMD(v)   (((v) << 13) & BM_GPMI_ECCCTRL_ECC_CMD)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_ECCCTRL_ECC_CMD(v)   BF_CS1(GPMI_ECCCTRL, ECC_CMD, v)
#endif

#define BV_GPMI_ECCCTRL_ECC_CMD__DECODE    0x0
#define BV_GPMI_ECCCTRL_ECC_CMD__ENCODE    0x1
#define BV_GPMI_ECCCTRL_ECC_CMD__RESERVE2  0x2
#define BV_GPMI_ECCCTRL_ECC_CMD__RESERVE3  0x3

/* --- Register HW_GPMI_ECCCTRL, field ENABLE_ECC */

#define BP_GPMI_ECCCTRL_ENABLE_ECC      12
#define BM_GPMI_ECCCTRL_ENABLE_ECC      0x00001000

#define BF_GPMI_ECCCTRL_ENABLE_ECC(v)   (((v) << 12) & BM_GPMI_ECCCTRL_ENABLE_ECC)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_ECCCTRL_ENABLE_ECC(v)   BF_CS1(GPMI_ECCCTRL, ENABLE_ECC, v)
#endif

#define BV_GPMI_ECCCTRL_ENABLE_ECC__ENABLE   0x1
#define BV_GPMI_ECCCTRL_ENABLE_ECC__DISABLE  0x0

/* --- Register HW_GPMI_ECCCTRL, field RSVD1 */

#define BP_GPMI_ECCCTRL_RSVD1      9
#define BM_GPMI_ECCCTRL_RSVD1      0x00000E00

#define BF_GPMI_ECCCTRL_RSVD1(v)   (((v) << 9) & BM_GPMI_ECCCTRL_RSVD1)
/* --- Register HW_GPMI_ECCCTRL, field BUFFER_MASK */

#define BP_GPMI_ECCCTRL_BUFFER_MASK      0
#define BM_GPMI_ECCCTRL_BUFFER_MASK      0x000001FF

#define BF_GPMI_ECCCTRL_BUFFER_MASK(v)   (((v) << 0) & BM_GPMI_ECCCTRL_BUFFER_MASK)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_ECCCTRL_BUFFER_MASK(v)   BF_CS1(GPMI_ECCCTRL, BUFFER_MASK, v)
#endif

#define BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY  0x100
#define BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE     0x1FF

/*
 * HW_GPMI_ECCCOUNT - GPMI Integrated ECC Transfer Count Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned COUNT:16;
        unsigned RSVD2:16;
    } B;
} hw_gpmi_ecccount_t;
#endif

/*
 * constants & macros for entire HW_GPMI_ECCCOUNT register
 */
#define HW_GPMI_ECCCOUNT_ADDR      (0x00112030)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_ECCCOUNT           (*(volatile hw_gpmi_ecccount_t *) HW_GPMI_ECCCOUNT_ADDR)
#define HW_GPMI_ECCCOUNT_RD()      (HW_GPMI_ECCCOUNT.U)
#define HW_GPMI_ECCCOUNT_WR(v)     (HW_GPMI_ECCCOUNT.U = (v))
#define HW_GPMI_ECCCOUNT_SET(v)    (HW_GPMI_ECCCOUNT_WR(HW_GPMI_ECCCOUNT_RD() |  (v)))
#define HW_GPMI_ECCCOUNT_CLR(v)    (HW_GPMI_ECCCOUNT_WR(HW_GPMI_ECCCOUNT_RD() & ~(v)))
#define HW_GPMI_ECCCOUNT_TOG(v)    (HW_GPMI_ECCCOUNT_WR(HW_GPMI_ECCCOUNT_RD() ^  (v)))
#else
#define HW_GPMI_ECCCOUNT_RD()      (_rbase->mem32_read(HW_GPMI_ECCCOUNT_ADDR))
#define HW_GPMI_ECCCOUNT_WR(v)     (_rbase->mem32_write(HW_GPMI_ECCCOUNT_ADDR,(v)))
#define HW_GPMI_ECCCOUNT_SET(v)    (HW_GPMI_ECCCOUNT_WR(HW_GPMI_ECCCOUNT_RD() |  (v)))
#define HW_GPMI_ECCCOUNT_CLR(v)    (HW_GPMI_ECCCOUNT_WR(HW_GPMI_ECCCOUNT_RD() & ~(v)))
#define HW_GPMI_ECCCOUNT_TOG(v)    (HW_GPMI_ECCCOUNT_WR(HW_GPMI_ECCCOUNT_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_ECCCOUNT bitfields
 */
/* --- Register HW_GPMI_ECCCOUNT, field RSVD2 */

#define BP_GPMI_ECCCOUNT_RSVD2      16
#define BM_GPMI_ECCCOUNT_RSVD2      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_ECCCOUNT_RSVD2(v)   ((((reg32_t) v) << 16) & BM_GPMI_ECCCOUNT_RSVD2)
#else
#define BF_GPMI_ECCCOUNT_RSVD2(v)   (((v) << 16) & BM_GPMI_ECCCOUNT_RSVD2)
#endif
/* --- Register HW_GPMI_ECCCOUNT, field COUNT */

#define BP_GPMI_ECCCOUNT_COUNT      0
#define BM_GPMI_ECCCOUNT_COUNT      0x0000FFFF

#define BF_GPMI_ECCCOUNT_COUNT(v)   (((v) << 0) & BM_GPMI_ECCCOUNT_COUNT)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_ECCCOUNT_COUNT(v)   (HW_GPMI_ECCCOUNT.B.COUNT = (v))
#endif

/*
 * HW_GPMI_PAYLOAD - GPMI Payload Address Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned RSVD0:2;
        unsigned ADDRESS:30;
    } B;
} hw_gpmi_payload_t;
#endif

/*
 * constants & macros for entire HW_GPMI_PAYLOAD register
 */
#define HW_GPMI_PAYLOAD_ADDR      (0x00112040)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_PAYLOAD           (*(volatile hw_gpmi_payload_t *) HW_GPMI_PAYLOAD_ADDR)
#define HW_GPMI_PAYLOAD_RD()      (HW_GPMI_PAYLOAD.U)
#define HW_GPMI_PAYLOAD_WR(v)     (HW_GPMI_PAYLOAD.U = (v))
#define HW_GPMI_PAYLOAD_SET(v)    (HW_GPMI_PAYLOAD_WR(HW_GPMI_PAYLOAD_RD() |  (v)))
#define HW_GPMI_PAYLOAD_CLR(v)    (HW_GPMI_PAYLOAD_WR(HW_GPMI_PAYLOAD_RD() & ~(v)))
#define HW_GPMI_PAYLOAD_TOG(v)    (HW_GPMI_PAYLOAD_WR(HW_GPMI_PAYLOAD_RD() ^  (v)))
#else
#define HW_GPMI_PAYLOAD_RD()      (_rbase->mem32_read(HW_GPMI_PAYLOAD_ADDR))
#define HW_GPMI_PAYLOAD_WR(v)     (_rbase->mem32_write(HW_GPMI_PAYLOAD_ADDR,(v)))
#define HW_GPMI_PAYLOAD_SET(v)    (HW_GPMI_PAYLOAD_WR(HW_GPMI_PAYLOAD_RD() |  (v)))
#define HW_GPMI_PAYLOAD_CLR(v)    (HW_GPMI_PAYLOAD_WR(HW_GPMI_PAYLOAD_RD() & ~(v)))
#define HW_GPMI_PAYLOAD_TOG(v)    (HW_GPMI_PAYLOAD_WR(HW_GPMI_PAYLOAD_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_PAYLOAD bitfields
 */
/* --- Register HW_GPMI_PAYLOAD, field ADDRESS */

#define BP_GPMI_PAYLOAD_ADDRESS      2
#define BM_GPMI_PAYLOAD_ADDRESS      0xFFFFFFFC

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_PAYLOAD_ADDRESS(v)   ((((reg32_t) v) << 2) & BM_GPMI_PAYLOAD_ADDRESS)
#else
#define BF_GPMI_PAYLOAD_ADDRESS(v)   (((v) << 2) & BM_GPMI_PAYLOAD_ADDRESS)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_PAYLOAD_ADDRESS(v)   BF_CS1(GPMI_PAYLOAD, ADDRESS, v)
#endif

/* --- Register HW_GPMI_PAYLOAD, field RSVD0 */

#define BP_GPMI_PAYLOAD_RSVD0      0
#define BM_GPMI_PAYLOAD_RSVD0      0x00000003

#define BF_GPMI_PAYLOAD_RSVD0(v)   (((v) << 0) & BM_GPMI_PAYLOAD_RSVD0)

/*
 * HW_GPMI_AUXILIARY - GPMI Auxiliary Address Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned RSVD0:2;
        unsigned ADDRESS:30;
    } B;
} hw_gpmi_auxiliary_t;
#endif

/*
 * constants & macros for entire HW_GPMI_AUXILIARY register
 */
#define HW_GPMI_AUXILIARY_ADDR      (0x00112050)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_AUXILIARY           (*(volatile hw_gpmi_auxiliary_t *) HW_GPMI_AUXILIARY_ADDR)
#define HW_GPMI_AUXILIARY_RD()      (HW_GPMI_AUXILIARY.U)
#define HW_GPMI_AUXILIARY_WR(v)     (HW_GPMI_AUXILIARY.U = (v))
#define HW_GPMI_AUXILIARY_SET(v)    (HW_GPMI_AUXILIARY_WR(HW_GPMI_AUXILIARY_RD() |  (v)))
#define HW_GPMI_AUXILIARY_CLR(v)    (HW_GPMI_AUXILIARY_WR(HW_GPMI_AUXILIARY_RD() & ~(v)))
#define HW_GPMI_AUXILIARY_TOG(v)    (HW_GPMI_AUXILIARY_WR(HW_GPMI_AUXILIARY_RD() ^  (v)))
#else
#define HW_GPMI_AUXILIARY_RD()      (_rbase->mem32_read(HW_GPMI_AUXILIARY_ADDR))
#define HW_GPMI_AUXILIARY_WR(v)     (_rbase->mem32_write(HW_GPMI_AUXILIARY_ADDR,(v)))
#define HW_GPMI_AUXILIARY_SET(v)    (HW_GPMI_AUXILIARY_WR(HW_GPMI_AUXILIARY_RD() |  (v)))
#define HW_GPMI_AUXILIARY_CLR(v)    (HW_GPMI_AUXILIARY_WR(HW_GPMI_AUXILIARY_RD() & ~(v)))
#define HW_GPMI_AUXILIARY_TOG(v)    (HW_GPMI_AUXILIARY_WR(HW_GPMI_AUXILIARY_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_AUXILIARY bitfields
 */
/* --- Register HW_GPMI_AUXILIARY, field ADDRESS */

#define BP_GPMI_AUXILIARY_ADDRESS      2
#define BM_GPMI_AUXILIARY_ADDRESS      0xFFFFFFFC

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_AUXILIARY_ADDRESS(v)   ((((reg32_t) v) << 2) & BM_GPMI_AUXILIARY_ADDRESS)
#else
#define BF_GPMI_AUXILIARY_ADDRESS(v)   (((v) << 2) & BM_GPMI_AUXILIARY_ADDRESS)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_AUXILIARY_ADDRESS(v)   BF_CS1(GPMI_AUXILIARY, ADDRESS, v)
#endif

/* --- Register HW_GPMI_AUXILIARY, field RSVD0 */

#define BP_GPMI_AUXILIARY_RSVD0      0
#define BM_GPMI_AUXILIARY_RSVD0      0x00000003

#define BF_GPMI_AUXILIARY_RSVD0(v)   (((v) << 0) & BM_GPMI_AUXILIARY_RSVD0)

/*
 * HW_GPMI_CTRL1 - GPMI Control Register 1
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned GPMI_MODE:1;
        unsigned CAMERA_MODE:1;
        unsigned ATA_IRQRDY_POLARITY:1;
        unsigned DEV_RESET:1;
        unsigned ABORT_WAIT_FOR_READY_CHANNEL:3;
        unsigned ABORT_WAIT_REQUEST:1;
        unsigned BURST_EN:1;
        unsigned TIMEOUT_IRQ:1;
        unsigned DEV_IRQ:1;
        unsigned DMA2ECC_MODE:1;
        unsigned RDN_DELAY:4;
        unsigned HALF_PERIOD:1;
        unsigned DLL_ENABLE:1;
        unsigned BCH_MODE:1;
        unsigned GANGED_RDYBUSY:1;
        unsigned TIMEOUT_IRQ_EN:1;
        unsigned RSVD1:1;
        unsigned WRN_DLY_SEL:2;
        unsigned DECOUPLE_CS:1;
        unsigned SSYNCMODE:1;
        unsigned UPDATE_CS:1;
        unsigned GPMI_CLK_DIV2_EN:1;
        unsigned TOGGLE_MODE:1;
        unsigned WRITE_CLK_STOP:1;
        unsigned SSYNC_CLK_STOP:1;
        unsigned DEV_CLK_STOP:1;
    } B;
} hw_gpmi_ctrl1_t;
#endif

/*
 * constants & macros for entire HW_GPMI_CTRL1 register
 */
#define HW_GPMI_CTRL1_ADDR      (0x00112060)
#define HW_GPMI_CTRL1_SET_ADDR  (0x00112064)
#define HW_GPMI_CTRL1_CLR_ADDR  (0x00112068)
#define HW_GPMI_CTRL1_TOG_ADDR  (0x0011206c)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_CTRL1           (*(volatile hw_gpmi_ctrl1_t *) HW_GPMI_CTRL1_ADDR)
#define HW_GPMI_CTRL1_RD()      (HW_GPMI_CTRL1.U)
#define HW_GPMI_CTRL1_WR(v)     (HW_GPMI_CTRL1.U = (v))
#define HW_GPMI_CTRL1_SET(v)    ((*(volatile reg32_t *) HW_GPMI_CTRL1_SET_ADDR) = (v))
#define HW_GPMI_CTRL1_CLR(v)    ((*(volatile reg32_t *) HW_GPMI_CTRL1_CLR_ADDR) = (v))
#define HW_GPMI_CTRL1_TOG(v)    ((*(volatile reg32_t *) HW_GPMI_CTRL1_TOG_ADDR) = (v))
#else
#define HW_GPMI_CTRL1_RD()      (_rbase->mem32_read(HW_GPMI_CTRL1_ADDR))
#define HW_GPMI_CTRL1_WR(v)     (_rbase->mem32_write(HW_GPMI_CTRL1_ADDR,(v)))
#define HW_GPMI_CTRL1_SET(v)    (_rbase->mem32_write(HW_GPMI_CTRL1_SET_ADDR,(v)))
#define HW_GPMI_CTRL1_CLR(v)    (_rbase->mem32_write(HW_GPMI_CTRL1_CLR_ADDR,(v)))
#define HW_GPMI_CTRL1_TOG(v)    (_rbase->mem32_write(HW_GPMI_CTRL1_TOG_ADDR,(v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_CTRL1 bitfields
 */
/* --- Register HW_GPMI_CTRL1, field DEV_CLK_STOP */

#define BP_GPMI_CTRL1_DEV_CLK_STOP      31
#define BM_GPMI_CTRL1_DEV_CLK_STOP      0x80000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_CTRL1_DEV_CLK_STOP(v)   ((((reg32_t) v) << 31) & BM_GPMI_CTRL1_DEV_CLK_STOP)
#else
#define BF_GPMI_CTRL1_DEV_CLK_STOP(v)   (((v) << 31) & BM_GPMI_CTRL1_DEV_CLK_STOP)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_DEV_CLK_STOP(v)   BF_CS1(GPMI_CTRL1, DEV_CLK_STOP, v)
#endif

/* --- Register HW_GPMI_CTRL1, field SSYNC_CLK_STOP */

#define BP_GPMI_CTRL1_SSYNC_CLK_STOP      30
#define BM_GPMI_CTRL1_SSYNC_CLK_STOP      0x40000000

#define BF_GPMI_CTRL1_SSYNC_CLK_STOP(v)   (((v) << 30) & BM_GPMI_CTRL1_SSYNC_CLK_STOP)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_SSYNC_CLK_STOP(v)   BF_CS1(GPMI_CTRL1, SSYNC_CLK_STOP, v)
#endif

/* --- Register HW_GPMI_CTRL1, field WRITE_CLK_STOP */

#define BP_GPMI_CTRL1_WRITE_CLK_STOP      29
#define BM_GPMI_CTRL1_WRITE_CLK_STOP      0x20000000

#define BF_GPMI_CTRL1_WRITE_CLK_STOP(v)   (((v) << 29) & BM_GPMI_CTRL1_WRITE_CLK_STOP)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_WRITE_CLK_STOP(v)   BF_CS1(GPMI_CTRL1, WRITE_CLK_STOP, v)
#endif

/* --- Register HW_GPMI_CTRL1, field TOGGLE_MODE */

#define BP_GPMI_CTRL1_TOGGLE_MODE      28
#define BM_GPMI_CTRL1_TOGGLE_MODE      0x10000000

#define BF_GPMI_CTRL1_TOGGLE_MODE(v)   (((v) << 28) & BM_GPMI_CTRL1_TOGGLE_MODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_TOGGLE_MODE(v)   BF_CS1(GPMI_CTRL1, TOGGLE_MODE, v)
#endif

/* --- Register HW_GPMI_CTRL1, field GPMI_CLK_DIV2_EN */

#define BP_GPMI_CTRL1_GPMI_CLK_DIV2_EN      27
#define BM_GPMI_CTRL1_GPMI_CLK_DIV2_EN      0x08000000

#define BF_GPMI_CTRL1_GPMI_CLK_DIV2_EN(v)   (((v) << 27) & BM_GPMI_CTRL1_GPMI_CLK_DIV2_EN)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_GPMI_CLK_DIV2_EN(v)   BF_CS1(GPMI_CTRL1, GPMI_CLK_DIV2_EN, v)
#endif

/* --- Register HW_GPMI_CTRL1, field UPDATE_CS */

#define BP_GPMI_CTRL1_UPDATE_CS      26
#define BM_GPMI_CTRL1_UPDATE_CS      0x04000000

#define BF_GPMI_CTRL1_UPDATE_CS(v)   (((v) << 26) & BM_GPMI_CTRL1_UPDATE_CS)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_UPDATE_CS(v)   BF_CS1(GPMI_CTRL1, UPDATE_CS, v)
#endif

/* --- Register HW_GPMI_CTRL1, field SSYNCMODE */

#define BP_GPMI_CTRL1_SSYNCMODE      25
#define BM_GPMI_CTRL1_SSYNCMODE      0x02000000

#define BF_GPMI_CTRL1_SSYNCMODE(v)   (((v) << 25) & BM_GPMI_CTRL1_SSYNCMODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_SSYNCMODE(v)   BF_CS1(GPMI_CTRL1, SSYNCMODE, v)
#endif

#define BV_GPMI_CTRL1_SSYNCMODE__ASYNC  0x0
#define BV_GPMI_CTRL1_SSYNCMODE__SSYNC  0x1

/* --- Register HW_GPMI_CTRL1, field DECOUPLE_CS */

#define BP_GPMI_CTRL1_DECOUPLE_CS      24
#define BM_GPMI_CTRL1_DECOUPLE_CS      0x01000000

#define BF_GPMI_CTRL1_DECOUPLE_CS(v)   (((v) << 24) & BM_GPMI_CTRL1_DECOUPLE_CS)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_DECOUPLE_CS(v)   BF_CS1(GPMI_CTRL1, DECOUPLE_CS, v)
#endif

/* --- Register HW_GPMI_CTRL1, field WRN_DLY_SEL */

#define BP_GPMI_CTRL1_WRN_DLY_SEL      22
#define BM_GPMI_CTRL1_WRN_DLY_SEL      0x00C00000

#define BF_GPMI_CTRL1_WRN_DLY_SEL(v)   (((v) << 22) & BM_GPMI_CTRL1_WRN_DLY_SEL)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_WRN_DLY_SEL(v)   BF_CS1(GPMI_CTRL1, WRN_DLY_SEL, v)
#endif

/* --- Register HW_GPMI_CTRL1, field RSVD1 */

#define BP_GPMI_CTRL1_RSVD1      21
#define BM_GPMI_CTRL1_RSVD1      0x00200000

#define BF_GPMI_CTRL1_RSVD1(v)   (((v) << 21) & BM_GPMI_CTRL1_RSVD1)
/* --- Register HW_GPMI_CTRL1, field TIMEOUT_IRQ_EN */

#define BP_GPMI_CTRL1_TIMEOUT_IRQ_EN      20
#define BM_GPMI_CTRL1_TIMEOUT_IRQ_EN      0x00100000

#define BF_GPMI_CTRL1_TIMEOUT_IRQ_EN(v)   (((v) << 20) & BM_GPMI_CTRL1_TIMEOUT_IRQ_EN)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_TIMEOUT_IRQ_EN(v)   BF_CS1(GPMI_CTRL1, TIMEOUT_IRQ_EN, v)
#endif

/* --- Register HW_GPMI_CTRL1, field GANGED_RDYBUSY */

#define BP_GPMI_CTRL1_GANGED_RDYBUSY      19
#define BM_GPMI_CTRL1_GANGED_RDYBUSY      0x00080000

#define BF_GPMI_CTRL1_GANGED_RDYBUSY(v)   (((v) << 19) & BM_GPMI_CTRL1_GANGED_RDYBUSY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_GANGED_RDYBUSY(v)   BF_CS1(GPMI_CTRL1, GANGED_RDYBUSY, v)
#endif

/* --- Register HW_GPMI_CTRL1, field BCH_MODE */

#define BP_GPMI_CTRL1_BCH_MODE      18
#define BM_GPMI_CTRL1_BCH_MODE      0x00040000

#define BF_GPMI_CTRL1_BCH_MODE(v)   (((v) << 18) & BM_GPMI_CTRL1_BCH_MODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_BCH_MODE(v)   BF_CS1(GPMI_CTRL1, BCH_MODE, v)
#endif

/* --- Register HW_GPMI_CTRL1, field DLL_ENABLE */

#define BP_GPMI_CTRL1_DLL_ENABLE      17
#define BM_GPMI_CTRL1_DLL_ENABLE      0x00020000

#define BF_GPMI_CTRL1_DLL_ENABLE(v)   (((v) << 17) & BM_GPMI_CTRL1_DLL_ENABLE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_DLL_ENABLE(v)   BF_CS1(GPMI_CTRL1, DLL_ENABLE, v)
#endif

/* --- Register HW_GPMI_CTRL1, field HALF_PERIOD */

#define BP_GPMI_CTRL1_HALF_PERIOD      16
#define BM_GPMI_CTRL1_HALF_PERIOD      0x00010000

#define BF_GPMI_CTRL1_HALF_PERIOD(v)   (((v) << 16) & BM_GPMI_CTRL1_HALF_PERIOD)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_HALF_PERIOD(v)   BF_CS1(GPMI_CTRL1, HALF_PERIOD, v)
#endif

/* --- Register HW_GPMI_CTRL1, field RDN_DELAY */

#define BP_GPMI_CTRL1_RDN_DELAY      12
#define BM_GPMI_CTRL1_RDN_DELAY      0x0000F000

#define BF_GPMI_CTRL1_RDN_DELAY(v)   (((v) << 12) & BM_GPMI_CTRL1_RDN_DELAY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_RDN_DELAY(v)   BF_CS1(GPMI_CTRL1, RDN_DELAY, v)
#endif

/* --- Register HW_GPMI_CTRL1, field DMA2ECC_MODE */

#define BP_GPMI_CTRL1_DMA2ECC_MODE      11
#define BM_GPMI_CTRL1_DMA2ECC_MODE      0x00000800

#define BF_GPMI_CTRL1_DMA2ECC_MODE(v)   (((v) << 11) & BM_GPMI_CTRL1_DMA2ECC_MODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_DMA2ECC_MODE(v)   BF_CS1(GPMI_CTRL1, DMA2ECC_MODE, v)
#endif

/* --- Register HW_GPMI_CTRL1, field DEV_IRQ */

#define BP_GPMI_CTRL1_DEV_IRQ      10
#define BM_GPMI_CTRL1_DEV_IRQ      0x00000400

#define BF_GPMI_CTRL1_DEV_IRQ(v)   (((v) << 10) & BM_GPMI_CTRL1_DEV_IRQ)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_DEV_IRQ(v)   BF_CS1(GPMI_CTRL1, DEV_IRQ, v)
#endif

/* --- Register HW_GPMI_CTRL1, field TIMEOUT_IRQ */

#define BP_GPMI_CTRL1_TIMEOUT_IRQ      9
#define BM_GPMI_CTRL1_TIMEOUT_IRQ      0x00000200

#define BF_GPMI_CTRL1_TIMEOUT_IRQ(v)   (((v) << 9) & BM_GPMI_CTRL1_TIMEOUT_IRQ)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_TIMEOUT_IRQ(v)   BF_CS1(GPMI_CTRL1, TIMEOUT_IRQ, v)
#endif

/* --- Register HW_GPMI_CTRL1, field BURST_EN */

#define BP_GPMI_CTRL1_BURST_EN      8
#define BM_GPMI_CTRL1_BURST_EN      0x00000100

#define BF_GPMI_CTRL1_BURST_EN(v)   (((v) << 8) & BM_GPMI_CTRL1_BURST_EN)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_BURST_EN(v)   BF_CS1(GPMI_CTRL1, BURST_EN, v)
#endif

/* --- Register HW_GPMI_CTRL1, field ABORT_WAIT_REQUEST */

#define BP_GPMI_CTRL1_ABORT_WAIT_REQUEST      7
#define BM_GPMI_CTRL1_ABORT_WAIT_REQUEST      0x00000080

#define BF_GPMI_CTRL1_ABORT_WAIT_REQUEST(v)   (((v) << 7) & BM_GPMI_CTRL1_ABORT_WAIT_REQUEST)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_ABORT_WAIT_REQUEST(v)   BF_CS1(GPMI_CTRL1, ABORT_WAIT_REQUEST, v)
#endif

/* --- Register HW_GPMI_CTRL1, field ABORT_WAIT_FOR_READY_CHANNEL */

#define BP_GPMI_CTRL1_ABORT_WAIT_FOR_READY_CHANNEL      4
#define BM_GPMI_CTRL1_ABORT_WAIT_FOR_READY_CHANNEL      0x00000070

#define BF_GPMI_CTRL1_ABORT_WAIT_FOR_READY_CHANNEL(v)   (((v) << 4) & BM_GPMI_CTRL1_ABORT_WAIT_FOR_READY_CHANNEL)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_ABORT_WAIT_FOR_READY_CHANNEL(v)   BF_CS1(GPMI_CTRL1, ABORT_WAIT_FOR_READY_CHANNEL, v)
#endif

/* --- Register HW_GPMI_CTRL1, field DEV_RESET */

#define BP_GPMI_CTRL1_DEV_RESET      3
#define BM_GPMI_CTRL1_DEV_RESET      0x00000008

#define BF_GPMI_CTRL1_DEV_RESET(v)   (((v) << 3) & BM_GPMI_CTRL1_DEV_RESET)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_DEV_RESET(v)   BF_CS1(GPMI_CTRL1, DEV_RESET, v)
#endif

#define BV_GPMI_CTRL1_DEV_RESET__ENABLED   0x0
#define BV_GPMI_CTRL1_DEV_RESET__DISABLED  0x1

/* --- Register HW_GPMI_CTRL1, field ATA_IRQRDY_POLARITY */

#define BP_GPMI_CTRL1_ATA_IRQRDY_POLARITY      2
#define BM_GPMI_CTRL1_ATA_IRQRDY_POLARITY      0x00000004

#define BF_GPMI_CTRL1_ATA_IRQRDY_POLARITY(v)   (((v) << 2) & BM_GPMI_CTRL1_ATA_IRQRDY_POLARITY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_ATA_IRQRDY_POLARITY(v)   BF_CS1(GPMI_CTRL1, ATA_IRQRDY_POLARITY, v)
#endif

#define BV_GPMI_CTRL1_ATA_IRQRDY_POLARITY__ACTIVELOW   0x0
#define BV_GPMI_CTRL1_ATA_IRQRDY_POLARITY__ACTIVEHIGH  0x1

/* --- Register HW_GPMI_CTRL1, field CAMERA_MODE */

#define BP_GPMI_CTRL1_CAMERA_MODE      1
#define BM_GPMI_CTRL1_CAMERA_MODE      0x00000002

#define BF_GPMI_CTRL1_CAMERA_MODE(v)   (((v) << 1) & BM_GPMI_CTRL1_CAMERA_MODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_CAMERA_MODE(v)   BF_CS1(GPMI_CTRL1, CAMERA_MODE, v)
#endif

/* --- Register HW_GPMI_CTRL1, field GPMI_MODE */

#define BP_GPMI_CTRL1_GPMI_MODE      0
#define BM_GPMI_CTRL1_GPMI_MODE      0x00000001

#define BF_GPMI_CTRL1_GPMI_MODE(v)   (((v) << 0) & BM_GPMI_CTRL1_GPMI_MODE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_CTRL1_GPMI_MODE(v)   BF_CS1(GPMI_CTRL1, GPMI_MODE, v)
#endif

#define BV_GPMI_CTRL1_GPMI_MODE__NAND  0x0
#define BV_GPMI_CTRL1_GPMI_MODE__ATA   0x1

/*
 * HW_GPMI_TIMING0 - GPMI Timing Register 0
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA_SETUP:8;
        unsigned DATA_HOLD:8;
        unsigned ADDRESS_SETUP:8;
        unsigned RSVD1:8;
    } B;
} hw_gpmi_timing0_t;
#endif

/*
 * constants & macros for entire HW_GPMI_TIMING0 register
 */
#define HW_GPMI_TIMING0_ADDR      (0x00112070)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_TIMING0           (*(volatile hw_gpmi_timing0_t *) HW_GPMI_TIMING0_ADDR)
#define HW_GPMI_TIMING0_RD()      (HW_GPMI_TIMING0.U)
#define HW_GPMI_TIMING0_WR(v)     (HW_GPMI_TIMING0.U = (v))
#define HW_GPMI_TIMING0_SET(v)    (HW_GPMI_TIMING0_WR(HW_GPMI_TIMING0_RD() |  (v)))
#define HW_GPMI_TIMING0_CLR(v)    (HW_GPMI_TIMING0_WR(HW_GPMI_TIMING0_RD() & ~(v)))
#define HW_GPMI_TIMING0_TOG(v)    (HW_GPMI_TIMING0_WR(HW_GPMI_TIMING0_RD() ^  (v)))
#else
#define HW_GPMI_TIMING0_RD()      (_rbase->mem32_read(HW_GPMI_TIMING0_ADDR))
#define HW_GPMI_TIMING0_WR(v)     (_rbase->mem32_write(HW_GPMI_TIMING0_ADDR,(v)))
#define HW_GPMI_TIMING0_SET(v)    (HW_GPMI_TIMING0_WR(HW_GPMI_TIMING0_RD() |  (v)))
#define HW_GPMI_TIMING0_CLR(v)    (HW_GPMI_TIMING0_WR(HW_GPMI_TIMING0_RD() & ~(v)))
#define HW_GPMI_TIMING0_TOG(v)    (HW_GPMI_TIMING0_WR(HW_GPMI_TIMING0_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_TIMING0 bitfields
 */
/* --- Register HW_GPMI_TIMING0, field RSVD1 */

#define BP_GPMI_TIMING0_RSVD1      24
#define BM_GPMI_TIMING0_RSVD1      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_TIMING0_RSVD1(v)   ((((reg32_t) v) << 24) & BM_GPMI_TIMING0_RSVD1)
#else
#define BF_GPMI_TIMING0_RSVD1(v)   (((v) << 24) & BM_GPMI_TIMING0_RSVD1)
#endif
/* --- Register HW_GPMI_TIMING0, field ADDRESS_SETUP */

#define BP_GPMI_TIMING0_ADDRESS_SETUP      16
#define BM_GPMI_TIMING0_ADDRESS_SETUP      0x00FF0000

#define BF_GPMI_TIMING0_ADDRESS_SETUP(v)   (((v) << 16) & BM_GPMI_TIMING0_ADDRESS_SETUP)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING0_ADDRESS_SETUP(v)   (HW_GPMI_TIMING0.B.ADDRESS_SETUP = (v))
#endif

/* --- Register HW_GPMI_TIMING0, field DATA_HOLD */

#define BP_GPMI_TIMING0_DATA_HOLD      8
#define BM_GPMI_TIMING0_DATA_HOLD      0x0000FF00

#define BF_GPMI_TIMING0_DATA_HOLD(v)   (((v) << 8) & BM_GPMI_TIMING0_DATA_HOLD)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING0_DATA_HOLD(v)   (HW_GPMI_TIMING0.B.DATA_HOLD = (v))
#endif

/* --- Register HW_GPMI_TIMING0, field DATA_SETUP */

#define BP_GPMI_TIMING0_DATA_SETUP      0
#define BM_GPMI_TIMING0_DATA_SETUP      0x000000FF

#define BF_GPMI_TIMING0_DATA_SETUP(v)   (((v) << 0) & BM_GPMI_TIMING0_DATA_SETUP)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING0_DATA_SETUP(v)   (HW_GPMI_TIMING0.B.DATA_SETUP = (v))
#endif

/*
 * HW_GPMI_TIMING1 - GPMI Timing Register 1
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned RSVD1:16;
        unsigned DEVICE_BUSY_TIMEOUT:16;
    } B;
} hw_gpmi_timing1_t;
#endif

/*
 * constants & macros for entire HW_GPMI_TIMING1 register
 */
#define HW_GPMI_TIMING1_ADDR      (0x00112080)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_TIMING1           (*(volatile hw_gpmi_timing1_t *) HW_GPMI_TIMING1_ADDR)
#define HW_GPMI_TIMING1_RD()      (HW_GPMI_TIMING1.U)
#define HW_GPMI_TIMING1_WR(v)     (HW_GPMI_TIMING1.U = (v))
#define HW_GPMI_TIMING1_SET(v)    (HW_GPMI_TIMING1_WR(HW_GPMI_TIMING1_RD() |  (v)))
#define HW_GPMI_TIMING1_CLR(v)    (HW_GPMI_TIMING1_WR(HW_GPMI_TIMING1_RD() & ~(v)))
#define HW_GPMI_TIMING1_TOG(v)    (HW_GPMI_TIMING1_WR(HW_GPMI_TIMING1_RD() ^  (v)))
#else
#define HW_GPMI_TIMING1_RD()      (_rbase->mem32_read(HW_GPMI_TIMING1_ADDR))
#define HW_GPMI_TIMING1_WR(v)     (_rbase->mem32_write(HW_GPMI_TIMING1_ADDR,(v)))
#define HW_GPMI_TIMING1_SET(v)    (HW_GPMI_TIMING1_WR(HW_GPMI_TIMING1_RD() |  (v)))
#define HW_GPMI_TIMING1_CLR(v)    (HW_GPMI_TIMING1_WR(HW_GPMI_TIMING1_RD() & ~(v)))
#define HW_GPMI_TIMING1_TOG(v)    (HW_GPMI_TIMING1_WR(HW_GPMI_TIMING1_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_TIMING1 bitfields
 */
/* --- Register HW_GPMI_TIMING1, field DEVICE_BUSY_TIMEOUT */

#define BP_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT      16
#define BM_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT(v)   ((((reg32_t) v) << 16) & BM_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT)
#else
#define BF_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT(v)   (((v) << 16) & BM_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING1_DEVICE_BUSY_TIMEOUT(v)   (HW_GPMI_TIMING1.B.DEVICE_BUSY_TIMEOUT = (v))
#endif

/* --- Register HW_GPMI_TIMING1, field RSVD1 */

#define BP_GPMI_TIMING1_RSVD1      0
#define BM_GPMI_TIMING1_RSVD1      0x0000FFFF

#define BF_GPMI_TIMING1_RSVD1(v)   (((v) << 0) & BM_GPMI_TIMING1_RSVD1)

/*
 * HW_GPMI_TIMING2 - GPMI Timing Register 2
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA_PAUSE:4;
        unsigned CMDADD_PAUSE:4;
        unsigned POSTAMBLE_DELAY:4;
        unsigned PREAMBLE_DELAY:4;
        unsigned CE_DELAY:5;
        unsigned RSVD0:3;
        unsigned READ_LATENCY:3;
        unsigned RSVD1:5;
    } B;
} hw_gpmi_timing2_t;
#endif

/*
 * constants & macros for entire HW_GPMI_TIMING2 register
 */
#define HW_GPMI_TIMING2_ADDR      (0x00112090)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_TIMING2           (*(volatile hw_gpmi_timing2_t *) HW_GPMI_TIMING2_ADDR)
#define HW_GPMI_TIMING2_RD()      (HW_GPMI_TIMING2.U)
#define HW_GPMI_TIMING2_WR(v)     (HW_GPMI_TIMING2.U = (v))
#define HW_GPMI_TIMING2_SET(v)    (HW_GPMI_TIMING2_WR(HW_GPMI_TIMING2_RD() |  (v)))
#define HW_GPMI_TIMING2_CLR(v)    (HW_GPMI_TIMING2_WR(HW_GPMI_TIMING2_RD() & ~(v)))
#define HW_GPMI_TIMING2_TOG(v)    (HW_GPMI_TIMING2_WR(HW_GPMI_TIMING2_RD() ^  (v)))
#else
#define HW_GPMI_TIMING2_RD()      (_rbase->mem32_read(HW_GPMI_TIMING2_ADDR))
#define HW_GPMI_TIMING2_WR(v)     (_rbase->mem32_write(HW_GPMI_TIMING2_ADDR,(v)))
#define HW_GPMI_TIMING2_SET(v)    (HW_GPMI_TIMING2_WR(HW_GPMI_TIMING2_RD() |  (v)))
#define HW_GPMI_TIMING2_CLR(v)    (HW_GPMI_TIMING2_WR(HW_GPMI_TIMING2_RD() & ~(v)))
#define HW_GPMI_TIMING2_TOG(v)    (HW_GPMI_TIMING2_WR(HW_GPMI_TIMING2_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_TIMING2 bitfields
 */
/* --- Register HW_GPMI_TIMING2, field RSVD1 */

#define BP_GPMI_TIMING2_RSVD1      27
#define BM_GPMI_TIMING2_RSVD1      0xF8000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_TIMING2_RSVD1(v)   ((((reg32_t) v) << 27) & BM_GPMI_TIMING2_RSVD1)
#else
#define BF_GPMI_TIMING2_RSVD1(v)   (((v) << 27) & BM_GPMI_TIMING2_RSVD1)
#endif
/* --- Register HW_GPMI_TIMING2, field READ_LATENCY */

#define BP_GPMI_TIMING2_READ_LATENCY      24
#define BM_GPMI_TIMING2_READ_LATENCY      0x07000000

#define BF_GPMI_TIMING2_READ_LATENCY(v)   (((v) << 24) & BM_GPMI_TIMING2_READ_LATENCY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING2_READ_LATENCY(v)   BF_CS1(GPMI_TIMING2, READ_LATENCY, v)
#endif

/* --- Register HW_GPMI_TIMING2, field RSVD0 */

#define BP_GPMI_TIMING2_RSVD0      21
#define BM_GPMI_TIMING2_RSVD0      0x00E00000

#define BF_GPMI_TIMING2_RSVD0(v)   (((v) << 21) & BM_GPMI_TIMING2_RSVD0)
/* --- Register HW_GPMI_TIMING2, field CE_DELAY */

#define BP_GPMI_TIMING2_CE_DELAY      16
#define BM_GPMI_TIMING2_CE_DELAY      0x001F0000

#define BF_GPMI_TIMING2_CE_DELAY(v)   (((v) << 16) & BM_GPMI_TIMING2_CE_DELAY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING2_CE_DELAY(v)   BF_CS1(GPMI_TIMING2, CE_DELAY, v)
#endif

/* --- Register HW_GPMI_TIMING2, field PREAMBLE_DELAY */

#define BP_GPMI_TIMING2_PREAMBLE_DELAY      12
#define BM_GPMI_TIMING2_PREAMBLE_DELAY      0x0000F000

#define BF_GPMI_TIMING2_PREAMBLE_DELAY(v)   (((v) << 12) & BM_GPMI_TIMING2_PREAMBLE_DELAY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING2_PREAMBLE_DELAY(v)   BF_CS1(GPMI_TIMING2, PREAMBLE_DELAY, v)
#endif

/* --- Register HW_GPMI_TIMING2, field POSTAMBLE_DELAY */

#define BP_GPMI_TIMING2_POSTAMBLE_DELAY      8
#define BM_GPMI_TIMING2_POSTAMBLE_DELAY      0x00000F00

#define BF_GPMI_TIMING2_POSTAMBLE_DELAY(v)   (((v) << 8) & BM_GPMI_TIMING2_POSTAMBLE_DELAY)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING2_POSTAMBLE_DELAY(v)   BF_CS1(GPMI_TIMING2, POSTAMBLE_DELAY, v)
#endif

/* --- Register HW_GPMI_TIMING2, field CMDADD_PAUSE */

#define BP_GPMI_TIMING2_CMDADD_PAUSE      4
#define BM_GPMI_TIMING2_CMDADD_PAUSE      0x000000F0

#define BF_GPMI_TIMING2_CMDADD_PAUSE(v)   (((v) << 4) & BM_GPMI_TIMING2_CMDADD_PAUSE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING2_CMDADD_PAUSE(v)   BF_CS1(GPMI_TIMING2, CMDADD_PAUSE, v)
#endif

/* --- Register HW_GPMI_TIMING2, field DATA_PAUSE */

#define BP_GPMI_TIMING2_DATA_PAUSE      0
#define BM_GPMI_TIMING2_DATA_PAUSE      0x0000000F

#define BF_GPMI_TIMING2_DATA_PAUSE(v)   (((v) << 0) & BM_GPMI_TIMING2_DATA_PAUSE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_TIMING2_DATA_PAUSE(v)   BF_CS1(GPMI_TIMING2, DATA_PAUSE, v)
#endif

/*
 * HW_GPMI_DATA - GPMI DMA Data Transfer Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA:32;
    } B;
} hw_gpmi_data_t;
#endif

/*
 * constants & macros for entire HW_GPMI_DATA register
 */
#define HW_GPMI_DATA_ADDR      (0x001120a0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_DATA           (*(volatile hw_gpmi_data_t *) HW_GPMI_DATA_ADDR)
#define HW_GPMI_DATA_RD()      (HW_GPMI_DATA.U)
#define HW_GPMI_DATA_WR(v)     (HW_GPMI_DATA.U = (v))
#define HW_GPMI_DATA_SET(v)    (HW_GPMI_DATA_WR(HW_GPMI_DATA_RD() |  (v)))
#define HW_GPMI_DATA_CLR(v)    (HW_GPMI_DATA_WR(HW_GPMI_DATA_RD() & ~(v)))
#define HW_GPMI_DATA_TOG(v)    (HW_GPMI_DATA_WR(HW_GPMI_DATA_RD() ^  (v)))
#else
#define HW_GPMI_DATA_RD()      (_rbase->mem32_read(HW_GPMI_DATA_ADDR))
#define HW_GPMI_DATA_WR(v)     (_rbase->mem32_write(HW_GPMI_DATA_ADDR,(v)))
#define HW_GPMI_DATA_SET(v)    (HW_GPMI_DATA_WR(HW_GPMI_DATA_RD() |  (v)))
#define HW_GPMI_DATA_CLR(v)    (HW_GPMI_DATA_WR(HW_GPMI_DATA_RD() & ~(v)))
#define HW_GPMI_DATA_TOG(v)    (HW_GPMI_DATA_WR(HW_GPMI_DATA_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_DATA bitfields
 */
/* --- Register HW_GPMI_DATA, field DATA */

#define BP_GPMI_DATA_DATA      0
#define BM_GPMI_DATA_DATA      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_DATA_DATA(v)   ((reg32_t) v)
#else
#define BF_GPMI_DATA_DATA(v)   (v)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_DATA_DATA(v)   (HW_GPMI_DATA.B.DATA = (v))
#endif

/*
 * HW_GPMI_STAT - GPMI Status Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned PRESENT:1;
        unsigned FIFO_FULL:1;
        unsigned FIFO_EMPTY:1;
        unsigned INVALID_BUFFER_MASK:1;
        unsigned ATA_IRQ:1;
        unsigned RSVD1:3;
        unsigned DEV0_ERROR:1;
        unsigned DEV1_ERROR:1;
        unsigned DEV2_ERROR:1;
        unsigned DEV3_ERROR:1;
        unsigned DEV4_ERROR:1;
        unsigned DEV5_ERROR:1;
        unsigned DEV6_ERROR:1;
        unsigned DEV7_ERROR:1;
        unsigned RDY_TIMEOUT:8;
        unsigned READY_BUSY:8;
    } B;
} hw_gpmi_stat_t;
#endif

/*
 * constants & macros for entire HW_GPMI_STAT register
 */
#define HW_GPMI_STAT_ADDR      (0x001120b0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_STAT           (*(volatile hw_gpmi_stat_t *) HW_GPMI_STAT_ADDR)
#define HW_GPMI_STAT_RD()      (HW_GPMI_STAT.U)
#else
#define HW_GPMI_STAT_RD()      (_rbase->mem32_read(HW_GPMI_STAT_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_STAT bitfields
 */
/* --- Register HW_GPMI_STAT, field READY_BUSY */

#define BP_GPMI_STAT_READY_BUSY      24
#define BM_GPMI_STAT_READY_BUSY      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_STAT_READY_BUSY(v)   ((((reg32_t) v) << 24) & BM_GPMI_STAT_READY_BUSY)
#else
#define BF_GPMI_STAT_READY_BUSY(v)   (((v) << 24) & BM_GPMI_STAT_READY_BUSY)
#endif
/* --- Register HW_GPMI_STAT, field RDY_TIMEOUT */

#define BP_GPMI_STAT_RDY_TIMEOUT      16
#define BM_GPMI_STAT_RDY_TIMEOUT      0x00FF0000

#define BF_GPMI_STAT_RDY_TIMEOUT(v)   (((v) << 16) & BM_GPMI_STAT_RDY_TIMEOUT)
/* --- Register HW_GPMI_STAT, field DEV7_ERROR */

#define BP_GPMI_STAT_DEV7_ERROR      15
#define BM_GPMI_STAT_DEV7_ERROR      0x00008000

#define BF_GPMI_STAT_DEV7_ERROR(v)   (((v) << 15) & BM_GPMI_STAT_DEV7_ERROR)
/* --- Register HW_GPMI_STAT, field DEV6_ERROR */

#define BP_GPMI_STAT_DEV6_ERROR      14
#define BM_GPMI_STAT_DEV6_ERROR      0x00004000

#define BF_GPMI_STAT_DEV6_ERROR(v)   (((v) << 14) & BM_GPMI_STAT_DEV6_ERROR)
/* --- Register HW_GPMI_STAT, field DEV5_ERROR */

#define BP_GPMI_STAT_DEV5_ERROR      13
#define BM_GPMI_STAT_DEV5_ERROR      0x00002000

#define BF_GPMI_STAT_DEV5_ERROR(v)   (((v) << 13) & BM_GPMI_STAT_DEV5_ERROR)
/* --- Register HW_GPMI_STAT, field DEV4_ERROR */

#define BP_GPMI_STAT_DEV4_ERROR      12
#define BM_GPMI_STAT_DEV4_ERROR      0x00001000

#define BF_GPMI_STAT_DEV4_ERROR(v)   (((v) << 12) & BM_GPMI_STAT_DEV4_ERROR)
/* --- Register HW_GPMI_STAT, field DEV3_ERROR */

#define BP_GPMI_STAT_DEV3_ERROR      11
#define BM_GPMI_STAT_DEV3_ERROR      0x00000800

#define BF_GPMI_STAT_DEV3_ERROR(v)   (((v) << 11) & BM_GPMI_STAT_DEV3_ERROR)
/* --- Register HW_GPMI_STAT, field DEV2_ERROR */

#define BP_GPMI_STAT_DEV2_ERROR      10
#define BM_GPMI_STAT_DEV2_ERROR      0x00000400

#define BF_GPMI_STAT_DEV2_ERROR(v)   (((v) << 10) & BM_GPMI_STAT_DEV2_ERROR)
/* --- Register HW_GPMI_STAT, field DEV1_ERROR */

#define BP_GPMI_STAT_DEV1_ERROR      9
#define BM_GPMI_STAT_DEV1_ERROR      0x00000200

#define BF_GPMI_STAT_DEV1_ERROR(v)   (((v) << 9) & BM_GPMI_STAT_DEV1_ERROR)
/* --- Register HW_GPMI_STAT, field DEV0_ERROR */

#define BP_GPMI_STAT_DEV0_ERROR      8
#define BM_GPMI_STAT_DEV0_ERROR      0x00000100

#define BF_GPMI_STAT_DEV0_ERROR(v)   (((v) << 8) & BM_GPMI_STAT_DEV0_ERROR)
/* --- Register HW_GPMI_STAT, field RSVD1 */

#define BP_GPMI_STAT_RSVD1      5
#define BM_GPMI_STAT_RSVD1      0x000000E0

#define BF_GPMI_STAT_RSVD1(v)   (((v) << 5) & BM_GPMI_STAT_RSVD1)
/* --- Register HW_GPMI_STAT, field ATA_IRQ */

#define BP_GPMI_STAT_ATA_IRQ      4
#define BM_GPMI_STAT_ATA_IRQ      0x00000010

#define BF_GPMI_STAT_ATA_IRQ(v)   (((v) << 4) & BM_GPMI_STAT_ATA_IRQ)
/* --- Register HW_GPMI_STAT, field INVALID_BUFFER_MASK */

#define BP_GPMI_STAT_INVALID_BUFFER_MASK      3
#define BM_GPMI_STAT_INVALID_BUFFER_MASK      0x00000008

#define BF_GPMI_STAT_INVALID_BUFFER_MASK(v)   (((v) << 3) & BM_GPMI_STAT_INVALID_BUFFER_MASK)
/* --- Register HW_GPMI_STAT, field FIFO_EMPTY */

#define BP_GPMI_STAT_FIFO_EMPTY      2
#define BM_GPMI_STAT_FIFO_EMPTY      0x00000004

#define BF_GPMI_STAT_FIFO_EMPTY(v)   (((v) << 2) & BM_GPMI_STAT_FIFO_EMPTY)
#define BV_GPMI_STAT_FIFO_EMPTY__NOT_EMPTY  0x0
#define BV_GPMI_STAT_FIFO_EMPTY__EMPTY      0x1

/* --- Register HW_GPMI_STAT, field FIFO_FULL */

#define BP_GPMI_STAT_FIFO_FULL      1
#define BM_GPMI_STAT_FIFO_FULL      0x00000002

#define BF_GPMI_STAT_FIFO_FULL(v)   (((v) << 1) & BM_GPMI_STAT_FIFO_FULL)
#define BV_GPMI_STAT_FIFO_FULL__NOT_FULL  0x0
#define BV_GPMI_STAT_FIFO_FULL__FULL      0x1

/* --- Register HW_GPMI_STAT, field PRESENT */

#define BP_GPMI_STAT_PRESENT      0
#define BM_GPMI_STAT_PRESENT      0x00000001

#define BF_GPMI_STAT_PRESENT(v)   (((v) << 0) & BM_GPMI_STAT_PRESENT)
#define BV_GPMI_STAT_PRESENT__UNAVAILABLE  0x0
#define BV_GPMI_STAT_PRESENT__AVAILABLE    0x1

/*
 * HW_GPMI_DEBUG - GPMI Debug Information Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned CMD_END:8;
        unsigned DMAREQ:8;
        unsigned DMA_SENSE:8;
        unsigned WAIT_FOR_READY_END:8;
    } B;
} hw_gpmi_debug_t;
#endif

/*
 * constants & macros for entire HW_GPMI_DEBUG register
 */
#define HW_GPMI_DEBUG_ADDR      (0x001120c0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_DEBUG           (*(volatile hw_gpmi_debug_t *) HW_GPMI_DEBUG_ADDR)
#define HW_GPMI_DEBUG_RD()      (HW_GPMI_DEBUG.U)
#else
#define HW_GPMI_DEBUG_RD()      (_rbase->mem32_read(HW_GPMI_DEBUG_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_DEBUG bitfields
 */
/* --- Register HW_GPMI_DEBUG, field WAIT_FOR_READY_END */

#define BP_GPMI_DEBUG_WAIT_FOR_READY_END      24
#define BM_GPMI_DEBUG_WAIT_FOR_READY_END      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_DEBUG_WAIT_FOR_READY_END(v)   ((((reg32_t) v) << 24) & BM_GPMI_DEBUG_WAIT_FOR_READY_END)
#else
#define BF_GPMI_DEBUG_WAIT_FOR_READY_END(v)   (((v) << 24) & BM_GPMI_DEBUG_WAIT_FOR_READY_END)
#endif
/* --- Register HW_GPMI_DEBUG, field DMA_SENSE */

#define BP_GPMI_DEBUG_DMA_SENSE      16
#define BM_GPMI_DEBUG_DMA_SENSE      0x00FF0000

#define BF_GPMI_DEBUG_DMA_SENSE(v)   (((v) << 16) & BM_GPMI_DEBUG_DMA_SENSE)
/* --- Register HW_GPMI_DEBUG, field DMAREQ */

#define BP_GPMI_DEBUG_DMAREQ      8
#define BM_GPMI_DEBUG_DMAREQ      0x0000FF00

#define BF_GPMI_DEBUG_DMAREQ(v)   (((v) << 8) & BM_GPMI_DEBUG_DMAREQ)
/* --- Register HW_GPMI_DEBUG, field CMD_END */

#define BP_GPMI_DEBUG_CMD_END      0
#define BM_GPMI_DEBUG_CMD_END      0x000000FF

#define BF_GPMI_DEBUG_CMD_END(v)   (((v) << 0) & BM_GPMI_DEBUG_CMD_END)

/*
 * HW_GPMI_VERSION - GPMI Version Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned STEP:16;
        unsigned MINOR:8;
        unsigned MAJOR:8;
    } B;
} hw_gpmi_version_t;
#endif

/*
 * constants & macros for entire HW_GPMI_VERSION register
 */
#define HW_GPMI_VERSION_ADDR      (0x001120d0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_VERSION           (*(volatile hw_gpmi_version_t *) HW_GPMI_VERSION_ADDR)
#define HW_GPMI_VERSION_RD()      (HW_GPMI_VERSION.U)
#else
#define HW_GPMI_VERSION_RD()      (_rbase->mem32_read(HW_GPMI_VERSION_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_VERSION bitfields
 */
/* --- Register HW_GPMI_VERSION, field MAJOR */

#define BP_GPMI_VERSION_MAJOR      24
#define BM_GPMI_VERSION_MAJOR      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_VERSION_MAJOR(v)   ((((reg32_t) v) << 24) & BM_GPMI_VERSION_MAJOR)
#else
#define BF_GPMI_VERSION_MAJOR(v)   (((v) << 24) & BM_GPMI_VERSION_MAJOR)
#endif
/* --- Register HW_GPMI_VERSION, field MINOR */

#define BP_GPMI_VERSION_MINOR      16
#define BM_GPMI_VERSION_MINOR      0x00FF0000

#define BF_GPMI_VERSION_MINOR(v)   (((v) << 16) & BM_GPMI_VERSION_MINOR)
/* --- Register HW_GPMI_VERSION, field STEP */

#define BP_GPMI_VERSION_STEP      0
#define BM_GPMI_VERSION_STEP      0x0000FFFF

#define BF_GPMI_VERSION_STEP(v)   (((v) << 0) & BM_GPMI_VERSION_STEP)

/*
 * HW_GPMI_DEBUG2 - GPMI Debug2 Information Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned RDN_TAP:6;
        unsigned UPDATE_WINDOW:1;
        unsigned VIEW_DELAYED_RDN:1;
        unsigned SYND2GPMI_READY:1;
        unsigned SYND2GPMI_VALID:1;
        unsigned GPMI2SYND_READY:1;
        unsigned GPMI2SYND_VALID:1;
        unsigned SYND2GPMI_BE:4;
        unsigned MAIN_STATE:4;
        unsigned PIN_STATE:3;
        unsigned BUSY:1;
        unsigned UDMA_STATE:4;
        unsigned RSVD1:4;
    } B;
} hw_gpmi_debug2_t;
#endif

/*
 * constants & macros for entire HW_GPMI_DEBUG2 register
 */
#define HW_GPMI_DEBUG2_ADDR      (0x001120e0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_DEBUG2           (*(volatile hw_gpmi_debug2_t *) HW_GPMI_DEBUG2_ADDR)
#define HW_GPMI_DEBUG2_RD()      (HW_GPMI_DEBUG2.U)
#define HW_GPMI_DEBUG2_WR(v)     (HW_GPMI_DEBUG2.U = (v))
#define HW_GPMI_DEBUG2_SET(v)    (HW_GPMI_DEBUG2_WR(HW_GPMI_DEBUG2_RD() |  (v)))
#define HW_GPMI_DEBUG2_CLR(v)    (HW_GPMI_DEBUG2_WR(HW_GPMI_DEBUG2_RD() & ~(v)))
#define HW_GPMI_DEBUG2_TOG(v)    (HW_GPMI_DEBUG2_WR(HW_GPMI_DEBUG2_RD() ^  (v)))
#else
#define HW_GPMI_DEBUG2_RD()      (_rbase->mem32_read(HW_GPMI_DEBUG2_ADDR))
#define HW_GPMI_DEBUG2_WR(v)     (_rbase->mem32_write(HW_GPMI_DEBUG2_ADDR,(v)))
#define HW_GPMI_DEBUG2_SET(v)    (HW_GPMI_DEBUG2_WR(HW_GPMI_DEBUG2_RD() |  (v)))
#define HW_GPMI_DEBUG2_CLR(v)    (HW_GPMI_DEBUG2_WR(HW_GPMI_DEBUG2_RD() & ~(v)))
#define HW_GPMI_DEBUG2_TOG(v)    (HW_GPMI_DEBUG2_WR(HW_GPMI_DEBUG2_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_DEBUG2 bitfields
 */
/* --- Register HW_GPMI_DEBUG2, field RSVD1 */

#define BP_GPMI_DEBUG2_RSVD1      28
#define BM_GPMI_DEBUG2_RSVD1      0xF0000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_DEBUG2_RSVD1(v)   ((((reg32_t) v) << 28) & BM_GPMI_DEBUG2_RSVD1)
#else
#define BF_GPMI_DEBUG2_RSVD1(v)   (((v) << 28) & BM_GPMI_DEBUG2_RSVD1)
#endif
/* --- Register HW_GPMI_DEBUG2, field UDMA_STATE */

#define BP_GPMI_DEBUG2_UDMA_STATE      24
#define BM_GPMI_DEBUG2_UDMA_STATE      0x0F000000

#define BF_GPMI_DEBUG2_UDMA_STATE(v)   (((v) << 24) & BM_GPMI_DEBUG2_UDMA_STATE)
/* --- Register HW_GPMI_DEBUG2, field BUSY */

#define BP_GPMI_DEBUG2_BUSY      23
#define BM_GPMI_DEBUG2_BUSY      0x00800000

#define BF_GPMI_DEBUG2_BUSY(v)   (((v) << 23) & BM_GPMI_DEBUG2_BUSY)
#define BV_GPMI_DEBUG2_BUSY__DISABLED  0x0
#define BV_GPMI_DEBUG2_BUSY__ENABLED   0x1

/* --- Register HW_GPMI_DEBUG2, field PIN_STATE */

#define BP_GPMI_DEBUG2_PIN_STATE      20
#define BM_GPMI_DEBUG2_PIN_STATE      0x00700000

#define BF_GPMI_DEBUG2_PIN_STATE(v)   (((v) << 20) & BM_GPMI_DEBUG2_PIN_STATE)
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_IDLE    0x0
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_BYTCNT  0x1
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_ADDR    0x2
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_STALL   0x3
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_STROBE  0x4
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_ATARDY  0x5
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_DHOLD   0x6
#define BV_GPMI_DEBUG2_PIN_STATE__PSM_DONE    0x7

/* --- Register HW_GPMI_DEBUG2, field MAIN_STATE */

#define BP_GPMI_DEBUG2_MAIN_STATE      16
#define BM_GPMI_DEBUG2_MAIN_STATE      0x000F0000

#define BF_GPMI_DEBUG2_MAIN_STATE(v)   (((v) << 16) & BM_GPMI_DEBUG2_MAIN_STATE)
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_IDLE    0x0
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_BYTCNT  0x1
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_WAITFE  0x2
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_WAITFR  0x3
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_DMAREQ  0x4
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_DMAACK  0x5
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_WAITFF  0x6
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_LDFIFO  0x7
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_LDDMAR  0x8
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_RDCMP   0x9
#define BV_GPMI_DEBUG2_MAIN_STATE__MSM_DONE    0xA

/* --- Register HW_GPMI_DEBUG2, field SYND2GPMI_BE */

#define BP_GPMI_DEBUG2_SYND2GPMI_BE      12
#define BM_GPMI_DEBUG2_SYND2GPMI_BE      0x0000F000

#define BF_GPMI_DEBUG2_SYND2GPMI_BE(v)   (((v) << 12) & BM_GPMI_DEBUG2_SYND2GPMI_BE)
/* --- Register HW_GPMI_DEBUG2, field GPMI2SYND_VALID */

#define BP_GPMI_DEBUG2_GPMI2SYND_VALID      11
#define BM_GPMI_DEBUG2_GPMI2SYND_VALID      0x00000800

#define BF_GPMI_DEBUG2_GPMI2SYND_VALID(v)   (((v) << 11) & BM_GPMI_DEBUG2_GPMI2SYND_VALID)
/* --- Register HW_GPMI_DEBUG2, field GPMI2SYND_READY */

#define BP_GPMI_DEBUG2_GPMI2SYND_READY      10
#define BM_GPMI_DEBUG2_GPMI2SYND_READY      0x00000400

#define BF_GPMI_DEBUG2_GPMI2SYND_READY(v)   (((v) << 10) & BM_GPMI_DEBUG2_GPMI2SYND_READY)
/* --- Register HW_GPMI_DEBUG2, field SYND2GPMI_VALID */

#define BP_GPMI_DEBUG2_SYND2GPMI_VALID      9
#define BM_GPMI_DEBUG2_SYND2GPMI_VALID      0x00000200

#define BF_GPMI_DEBUG2_SYND2GPMI_VALID(v)   (((v) << 9) & BM_GPMI_DEBUG2_SYND2GPMI_VALID)
/* --- Register HW_GPMI_DEBUG2, field SYND2GPMI_READY */

#define BP_GPMI_DEBUG2_SYND2GPMI_READY      8
#define BM_GPMI_DEBUG2_SYND2GPMI_READY      0x00000100

#define BF_GPMI_DEBUG2_SYND2GPMI_READY(v)   (((v) << 8) & BM_GPMI_DEBUG2_SYND2GPMI_READY)
/* --- Register HW_GPMI_DEBUG2, field VIEW_DELAYED_RDN */

#define BP_GPMI_DEBUG2_VIEW_DELAYED_RDN      7
#define BM_GPMI_DEBUG2_VIEW_DELAYED_RDN      0x00000080

#define BF_GPMI_DEBUG2_VIEW_DELAYED_RDN(v)   (((v) << 7) & BM_GPMI_DEBUG2_VIEW_DELAYED_RDN)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_DEBUG2_VIEW_DELAYED_RDN(v)   BF_CS1(GPMI_DEBUG2, VIEW_DELAYED_RDN, v)
#endif

/* --- Register HW_GPMI_DEBUG2, field UPDATE_WINDOW */

#define BP_GPMI_DEBUG2_UPDATE_WINDOW      6
#define BM_GPMI_DEBUG2_UPDATE_WINDOW      0x00000040

#define BF_GPMI_DEBUG2_UPDATE_WINDOW(v)   (((v) << 6) & BM_GPMI_DEBUG2_UPDATE_WINDOW)
/* --- Register HW_GPMI_DEBUG2, field RDN_TAP */

#define BP_GPMI_DEBUG2_RDN_TAP      0
#define BM_GPMI_DEBUG2_RDN_TAP      0x0000003F

#define BF_GPMI_DEBUG2_RDN_TAP(v)   (((v) << 0) & BM_GPMI_DEBUG2_RDN_TAP)

/*
 * HW_GPMI_DEBUG3 - GPMI Debug3 Information Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DEV_WORD_CNTR:16;
        unsigned APB_WORD_CNTR:16;
    } B;
} hw_gpmi_debug3_t;
#endif

/*
 * constants & macros for entire HW_GPMI_DEBUG3 register
 */
#define HW_GPMI_DEBUG3_ADDR      (0x001120f0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_DEBUG3           (*(volatile hw_gpmi_debug3_t *) HW_GPMI_DEBUG3_ADDR)
#define HW_GPMI_DEBUG3_RD()      (HW_GPMI_DEBUG3.U)
#else
#define HW_GPMI_DEBUG3_RD()      (_rbase->mem32_read(HW_GPMI_DEBUG3_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_DEBUG3 bitfields
 */
/* --- Register HW_GPMI_DEBUG3, field APB_WORD_CNTR */

#define BP_GPMI_DEBUG3_APB_WORD_CNTR      16
#define BM_GPMI_DEBUG3_APB_WORD_CNTR      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_DEBUG3_APB_WORD_CNTR(v)   ((((reg32_t) v) << 16) & BM_GPMI_DEBUG3_APB_WORD_CNTR)
#else
#define BF_GPMI_DEBUG3_APB_WORD_CNTR(v)   (((v) << 16) & BM_GPMI_DEBUG3_APB_WORD_CNTR)
#endif
/* --- Register HW_GPMI_DEBUG3, field DEV_WORD_CNTR */

#define BP_GPMI_DEBUG3_DEV_WORD_CNTR      0
#define BM_GPMI_DEBUG3_DEV_WORD_CNTR      0x0000FFFF

#define BF_GPMI_DEBUG3_DEV_WORD_CNTR(v)   (((v) << 0) & BM_GPMI_DEBUG3_DEV_WORD_CNTR)

/*
 * HW_GPMI_READ_DDR_DLL_CTRL - GPMI Double Rate Read DLL Control Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned ENABLE:1;
        unsigned RESET:1;
        unsigned SLV_FORCE_UPD:1;
        unsigned SLV_DLY_TARGET:4;
        unsigned GATE_UPDATE:1;
        unsigned REFCLK_ON:1;
        unsigned SLV_OVERRIDE:1;
        unsigned SLV_OVERRIDE_VAL:8;
        unsigned RSVD1:2;
        unsigned SLV_UPDATE_INT:8;
        unsigned REF_UPDATE_INT:4;
    } B;
} hw_gpmi_read_ddr_dll_ctrl_t;
#endif

/*
 * constants & macros for entire HW_GPMI_READ_DDR_DLL_CTRL register
 */
#define HW_GPMI_READ_DDR_DLL_CTRL_ADDR      (0x00112100)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_READ_DDR_DLL_CTRL           (*(volatile hw_gpmi_read_ddr_dll_ctrl_t *) HW_GPMI_READ_DDR_DLL_CTRL_ADDR)
#define HW_GPMI_READ_DDR_DLL_CTRL_RD()      (HW_GPMI_READ_DDR_DLL_CTRL.U)
#define HW_GPMI_READ_DDR_DLL_CTRL_WR(v)     (HW_GPMI_READ_DDR_DLL_CTRL.U = (v))
#define HW_GPMI_READ_DDR_DLL_CTRL_SET(v)    (HW_GPMI_READ_DDR_DLL_CTRL_WR(HW_GPMI_READ_DDR_DLL_CTRL_RD() |  (v)))
#define HW_GPMI_READ_DDR_DLL_CTRL_CLR(v)    (HW_GPMI_READ_DDR_DLL_CTRL_WR(HW_GPMI_READ_DDR_DLL_CTRL_RD() & ~(v)))
#define HW_GPMI_READ_DDR_DLL_CTRL_TOG(v)    (HW_GPMI_READ_DDR_DLL_CTRL_WR(HW_GPMI_READ_DDR_DLL_CTRL_RD() ^  (v)))
#else
#define HW_GPMI_READ_DDR_DLL_CTRL_RD()      (_rbase->mem32_read(HW_GPMI_READ_DDR_DLL_CTRL_ADDR))
#define HW_GPMI_READ_DDR_DLL_CTRL_WR(v)     (_rbase->mem32_write(HW_GPMI_READ_DDR_DLL_CTRL_ADDR,(v)))
#define HW_GPMI_READ_DDR_DLL_CTRL_SET(v)    (HW_GPMI_READ_DDR_DLL_CTRL_WR(HW_GPMI_READ_DDR_DLL_CTRL_RD() |  (v)))
#define HW_GPMI_READ_DDR_DLL_CTRL_CLR(v)    (HW_GPMI_READ_DDR_DLL_CTRL_WR(HW_GPMI_READ_DDR_DLL_CTRL_RD() & ~(v)))
#define HW_GPMI_READ_DDR_DLL_CTRL_TOG(v)    (HW_GPMI_READ_DDR_DLL_CTRL_WR(HW_GPMI_READ_DDR_DLL_CTRL_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_READ_DDR_DLL_CTRL bitfields
 */
/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field REF_UPDATE_INT */

#define BP_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT      28
#define BM_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT      0xF0000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT(v)   ((((reg32_t) v) << 28) & BM_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT)
#else
#define BF_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT(v)   (((v) << 28) & BM_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_REF_UPDATE_INT(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, REF_UPDATE_INT, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field SLV_UPDATE_INT */

#define BP_GPMI_READ_DDR_DLL_CTRL_SLV_UPDATE_INT      20
#define BM_GPMI_READ_DDR_DLL_CTRL_SLV_UPDATE_INT      0x0FF00000

#define BF_GPMI_READ_DDR_DLL_CTRL_SLV_UPDATE_INT(v)   (((v) << 20) & BM_GPMI_READ_DDR_DLL_CTRL_SLV_UPDATE_INT)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_SLV_UPDATE_INT(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, SLV_UPDATE_INT, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field RSVD1 */

#define BP_GPMI_READ_DDR_DLL_CTRL_RSVD1      18
#define BM_GPMI_READ_DDR_DLL_CTRL_RSVD1      0x000C0000

#define BF_GPMI_READ_DDR_DLL_CTRL_RSVD1(v)   (((v) << 18) & BM_GPMI_READ_DDR_DLL_CTRL_RSVD1)
/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field SLV_OVERRIDE_VAL */

#define BP_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE_VAL      10
#define BM_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE_VAL      0x0003FC00

#define BF_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE_VAL(v)   (((v) << 10) & BM_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE_VAL)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE_VAL(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, SLV_OVERRIDE_VAL, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field SLV_OVERRIDE */

#define BP_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE      9
#define BM_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE      0x00000200

#define BF_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE(v)   (((v) << 9) & BM_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_SLV_OVERRIDE(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, SLV_OVERRIDE, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field REFCLK_ON */

#define BP_GPMI_READ_DDR_DLL_CTRL_REFCLK_ON      8
#define BM_GPMI_READ_DDR_DLL_CTRL_REFCLK_ON      0x00000100

#define BF_GPMI_READ_DDR_DLL_CTRL_REFCLK_ON(v)   (((v) << 8) & BM_GPMI_READ_DDR_DLL_CTRL_REFCLK_ON)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_REFCLK_ON(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, REFCLK_ON, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field GATE_UPDATE */

#define BP_GPMI_READ_DDR_DLL_CTRL_GATE_UPDATE      7
#define BM_GPMI_READ_DDR_DLL_CTRL_GATE_UPDATE      0x00000080

#define BF_GPMI_READ_DDR_DLL_CTRL_GATE_UPDATE(v)   (((v) << 7) & BM_GPMI_READ_DDR_DLL_CTRL_GATE_UPDATE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_GATE_UPDATE(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, GATE_UPDATE, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field SLV_DLY_TARGET */

#define BP_GPMI_READ_DDR_DLL_CTRL_SLV_DLY_TARGET      3
#define BM_GPMI_READ_DDR_DLL_CTRL_SLV_DLY_TARGET      0x00000078

#define BF_GPMI_READ_DDR_DLL_CTRL_SLV_DLY_TARGET(v)   (((v) << 3) & BM_GPMI_READ_DDR_DLL_CTRL_SLV_DLY_TARGET)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_SLV_DLY_TARGET(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, SLV_DLY_TARGET, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field SLV_FORCE_UPD */

#define BP_GPMI_READ_DDR_DLL_CTRL_SLV_FORCE_UPD      2
#define BM_GPMI_READ_DDR_DLL_CTRL_SLV_FORCE_UPD      0x00000004

#define BF_GPMI_READ_DDR_DLL_CTRL_SLV_FORCE_UPD(v)   (((v) << 2) & BM_GPMI_READ_DDR_DLL_CTRL_SLV_FORCE_UPD)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_SLV_FORCE_UPD(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, SLV_FORCE_UPD, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field RESET */

#define BP_GPMI_READ_DDR_DLL_CTRL_RESET      1
#define BM_GPMI_READ_DDR_DLL_CTRL_RESET      0x00000002

#define BF_GPMI_READ_DDR_DLL_CTRL_RESET(v)   (((v) << 1) & BM_GPMI_READ_DDR_DLL_CTRL_RESET)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_RESET(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, RESET, v)
#endif

/* --- Register HW_GPMI_READ_DDR_DLL_CTRL, field ENABLE */

#define BP_GPMI_READ_DDR_DLL_CTRL_ENABLE      0
#define BM_GPMI_READ_DDR_DLL_CTRL_ENABLE      0x00000001

#define BF_GPMI_READ_DDR_DLL_CTRL_ENABLE(v)   (((v) << 0) & BM_GPMI_READ_DDR_DLL_CTRL_ENABLE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_READ_DDR_DLL_CTRL_ENABLE(v)   BF_CS1(GPMI_READ_DDR_DLL_CTRL, ENABLE, v)
#endif

/*
 * HW_GPMI_WRITE_DDR_DLL_CTRL - GPMI Double Rate Write DLL Control Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned ENABLE:1;
        unsigned RESET:1;
        unsigned SLV_FORCE_UPD:1;
        unsigned SLV_DLY_TARGET:4;
        unsigned GATE_UPDATE:1;
        unsigned REFCLK_ON:1;
        unsigned SLV_OVERRIDE:1;
        unsigned SLV_OVERRIDE_VAL:8;
        unsigned RSVD1:2;
        unsigned SLV_UPDATE_INT:8;
        unsigned REF_UPDATE_INT:4;
    } B;
} hw_gpmi_write_ddr_dll_ctrl_t;
#endif

/*
 * constants & macros for entire HW_GPMI_WRITE_DDR_DLL_CTRL register
 */
#define HW_GPMI_WRITE_DDR_DLL_CTRL_ADDR      (0x00112110)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_WRITE_DDR_DLL_CTRL           (*(volatile hw_gpmi_write_ddr_dll_ctrl_t *) HW_GPMI_WRITE_DDR_DLL_CTRL_ADDR)
#define HW_GPMI_WRITE_DDR_DLL_CTRL_RD()      (HW_GPMI_WRITE_DDR_DLL_CTRL.U)
#define HW_GPMI_WRITE_DDR_DLL_CTRL_WR(v)     (HW_GPMI_WRITE_DDR_DLL_CTRL.U = (v))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_SET(v)    (HW_GPMI_WRITE_DDR_DLL_CTRL_WR(HW_GPMI_WRITE_DDR_DLL_CTRL_RD() |  (v)))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_CLR(v)    (HW_GPMI_WRITE_DDR_DLL_CTRL_WR(HW_GPMI_WRITE_DDR_DLL_CTRL_RD() & ~(v)))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_TOG(v)    (HW_GPMI_WRITE_DDR_DLL_CTRL_WR(HW_GPMI_WRITE_DDR_DLL_CTRL_RD() ^  (v)))
#else
#define HW_GPMI_WRITE_DDR_DLL_CTRL_RD()      (_rbase->mem32_read(HW_GPMI_WRITE_DDR_DLL_CTRL_ADDR))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_WR(v)     (_rbase->mem32_write(HW_GPMI_WRITE_DDR_DLL_CTRL_ADDR,(v)))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_SET(v)    (HW_GPMI_WRITE_DDR_DLL_CTRL_WR(HW_GPMI_WRITE_DDR_DLL_CTRL_RD() |  (v)))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_CLR(v)    (HW_GPMI_WRITE_DDR_DLL_CTRL_WR(HW_GPMI_WRITE_DDR_DLL_CTRL_RD() & ~(v)))
#define HW_GPMI_WRITE_DDR_DLL_CTRL_TOG(v)    (HW_GPMI_WRITE_DDR_DLL_CTRL_WR(HW_GPMI_WRITE_DDR_DLL_CTRL_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_WRITE_DDR_DLL_CTRL bitfields
 */
/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field REF_UPDATE_INT */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT      28
#define BM_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT      0xF0000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT(v)   ((((reg32_t) v) << 28) & BM_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT)
#else
#define BF_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT(v)   (((v) << 28) & BM_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_REF_UPDATE_INT(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, REF_UPDATE_INT, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field SLV_UPDATE_INT */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_SLV_UPDATE_INT      20
#define BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_UPDATE_INT      0x0FF00000

#define BF_GPMI_WRITE_DDR_DLL_CTRL_SLV_UPDATE_INT(v)   (((v) << 20) & BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_UPDATE_INT)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_SLV_UPDATE_INT(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, SLV_UPDATE_INT, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field RSVD1 */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_RSVD1      18
#define BM_GPMI_WRITE_DDR_DLL_CTRL_RSVD1      0x000C0000

#define BF_GPMI_WRITE_DDR_DLL_CTRL_RSVD1(v)   (((v) << 18) & BM_GPMI_WRITE_DDR_DLL_CTRL_RSVD1)
/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field SLV_OVERRIDE_VAL */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE_VAL      10
#define BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE_VAL      0x0003FC00

#define BF_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE_VAL(v)   (((v) << 10) & BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE_VAL)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE_VAL(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, SLV_OVERRIDE_VAL, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field SLV_OVERRIDE */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE      9
#define BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE      0x00000200

#define BF_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE(v)   (((v) << 9) & BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_SLV_OVERRIDE(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, SLV_OVERRIDE, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field REFCLK_ON */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_REFCLK_ON      8
#define BM_GPMI_WRITE_DDR_DLL_CTRL_REFCLK_ON      0x00000100

#define BF_GPMI_WRITE_DDR_DLL_CTRL_REFCLK_ON(v)   (((v) << 8) & BM_GPMI_WRITE_DDR_DLL_CTRL_REFCLK_ON)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_REFCLK_ON(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, REFCLK_ON, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field GATE_UPDATE */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_GATE_UPDATE      7
#define BM_GPMI_WRITE_DDR_DLL_CTRL_GATE_UPDATE      0x00000080

#define BF_GPMI_WRITE_DDR_DLL_CTRL_GATE_UPDATE(v)   (((v) << 7) & BM_GPMI_WRITE_DDR_DLL_CTRL_GATE_UPDATE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_GATE_UPDATE(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, GATE_UPDATE, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field SLV_DLY_TARGET */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_SLV_DLY_TARGET      3
#define BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_DLY_TARGET      0x00000078

#define BF_GPMI_WRITE_DDR_DLL_CTRL_SLV_DLY_TARGET(v)   (((v) << 3) & BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_DLY_TARGET)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_SLV_DLY_TARGET(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, SLV_DLY_TARGET, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field SLV_FORCE_UPD */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_SLV_FORCE_UPD      2
#define BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_FORCE_UPD      0x00000004

#define BF_GPMI_WRITE_DDR_DLL_CTRL_SLV_FORCE_UPD(v)   (((v) << 2) & BM_GPMI_WRITE_DDR_DLL_CTRL_SLV_FORCE_UPD)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_SLV_FORCE_UPD(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, SLV_FORCE_UPD, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field RESET */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_RESET      1
#define BM_GPMI_WRITE_DDR_DLL_CTRL_RESET      0x00000002

#define BF_GPMI_WRITE_DDR_DLL_CTRL_RESET(v)   (((v) << 1) & BM_GPMI_WRITE_DDR_DLL_CTRL_RESET)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_RESET(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, RESET, v)
#endif

/* --- Register HW_GPMI_WRITE_DDR_DLL_CTRL, field ENABLE */

#define BP_GPMI_WRITE_DDR_DLL_CTRL_ENABLE      0
#define BM_GPMI_WRITE_DDR_DLL_CTRL_ENABLE      0x00000001

#define BF_GPMI_WRITE_DDR_DLL_CTRL_ENABLE(v)   (((v) << 0) & BM_GPMI_WRITE_DDR_DLL_CTRL_ENABLE)
#ifndef __LANGUAGE_ASM__
#define BW_GPMI_WRITE_DDR_DLL_CTRL_ENABLE(v)   BF_CS1(GPMI_WRITE_DDR_DLL_CTRL, ENABLE, v)
#endif

/*
 * HW_GPMI_READ_DDR_DLL_STS - GPMI Double Rate Read DLL Status Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned SLV_LOCK:1;
        unsigned SLV_SEL:8;
        unsigned RSVD0:7;
        unsigned REF_LOCK:1;
        unsigned REF_SEL:8;
        unsigned RSVD1:7;
    } B;
} hw_gpmi_read_ddr_dll_sts_t;
#endif

/*
 * constants & macros for entire HW_GPMI_READ_DDR_DLL_STS register
 */
#define HW_GPMI_READ_DDR_DLL_STS_ADDR      (0x00112120)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_READ_DDR_DLL_STS           (*(volatile hw_gpmi_read_ddr_dll_sts_t *) HW_GPMI_READ_DDR_DLL_STS_ADDR)
#define HW_GPMI_READ_DDR_DLL_STS_RD()      (HW_GPMI_READ_DDR_DLL_STS.U)
#else
#define HW_GPMI_READ_DDR_DLL_STS_RD()      (_rbase->mem32_read(HW_GPMI_READ_DDR_DLL_STS_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_READ_DDR_DLL_STS bitfields
 */
/* --- Register HW_GPMI_READ_DDR_DLL_STS, field RSVD1 */

#define BP_GPMI_READ_DDR_DLL_STS_RSVD1      25
#define BM_GPMI_READ_DDR_DLL_STS_RSVD1      0xFE000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_READ_DDR_DLL_STS_RSVD1(v)   ((((reg32_t) v) << 25) & BM_GPMI_READ_DDR_DLL_STS_RSVD1)
#else
#define BF_GPMI_READ_DDR_DLL_STS_RSVD1(v)   (((v) << 25) & BM_GPMI_READ_DDR_DLL_STS_RSVD1)
#endif
/* --- Register HW_GPMI_READ_DDR_DLL_STS, field REF_SEL */

#define BP_GPMI_READ_DDR_DLL_STS_REF_SEL      17
#define BM_GPMI_READ_DDR_DLL_STS_REF_SEL      0x01FE0000

#define BF_GPMI_READ_DDR_DLL_STS_REF_SEL(v)   (((v) << 17) & BM_GPMI_READ_DDR_DLL_STS_REF_SEL)
/* --- Register HW_GPMI_READ_DDR_DLL_STS, field REF_LOCK */

#define BP_GPMI_READ_DDR_DLL_STS_REF_LOCK      16
#define BM_GPMI_READ_DDR_DLL_STS_REF_LOCK      0x00010000

#define BF_GPMI_READ_DDR_DLL_STS_REF_LOCK(v)   (((v) << 16) & BM_GPMI_READ_DDR_DLL_STS_REF_LOCK)
/* --- Register HW_GPMI_READ_DDR_DLL_STS, field RSVD0 */

#define BP_GPMI_READ_DDR_DLL_STS_RSVD0      9
#define BM_GPMI_READ_DDR_DLL_STS_RSVD0      0x0000FE00

#define BF_GPMI_READ_DDR_DLL_STS_RSVD0(v)   (((v) << 9) & BM_GPMI_READ_DDR_DLL_STS_RSVD0)
/* --- Register HW_GPMI_READ_DDR_DLL_STS, field SLV_SEL */

#define BP_GPMI_READ_DDR_DLL_STS_SLV_SEL      1
#define BM_GPMI_READ_DDR_DLL_STS_SLV_SEL      0x000001FE

#define BF_GPMI_READ_DDR_DLL_STS_SLV_SEL(v)   (((v) << 1) & BM_GPMI_READ_DDR_DLL_STS_SLV_SEL)
/* --- Register HW_GPMI_READ_DDR_DLL_STS, field SLV_LOCK */

#define BP_GPMI_READ_DDR_DLL_STS_SLV_LOCK      0
#define BM_GPMI_READ_DDR_DLL_STS_SLV_LOCK      0x00000001

#define BF_GPMI_READ_DDR_DLL_STS_SLV_LOCK(v)   (((v) << 0) & BM_GPMI_READ_DDR_DLL_STS_SLV_LOCK)

/*
 * HW_GPMI_WRITE_DDR_DLL_STS - GPMI Double Rate Write DLL Status Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned SLV_LOCK:1;
        unsigned SLV_SEL:8;
        unsigned RSVD0:7;
        unsigned REF_LOCK:1;
        unsigned REF_SEL:8;
        unsigned RSVD1:7;
    } B;
} hw_gpmi_write_ddr_dll_sts_t;
#endif

/*
 * constants & macros for entire HW_GPMI_WRITE_DDR_DLL_STS register
 */
#define HW_GPMI_WRITE_DDR_DLL_STS_ADDR      (0x00112130)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_GPMI_WRITE_DDR_DLL_STS           (*(volatile hw_gpmi_write_ddr_dll_sts_t *) HW_GPMI_WRITE_DDR_DLL_STS_ADDR)
#define HW_GPMI_WRITE_DDR_DLL_STS_RD()      (HW_GPMI_WRITE_DDR_DLL_STS.U)
#else
#define HW_GPMI_WRITE_DDR_DLL_STS_RD()      (_rbase->mem32_read(HW_GPMI_WRITE_DDR_DLL_STS_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_GPMI_WRITE_DDR_DLL_STS bitfields
 */
/* --- Register HW_GPMI_WRITE_DDR_DLL_STS, field RSVD1 */

#define BP_GPMI_WRITE_DDR_DLL_STS_RSVD1      25
#define BM_GPMI_WRITE_DDR_DLL_STS_RSVD1      0xFE000000

#ifndef __LANGUAGE_ASM__
#define BF_GPMI_WRITE_DDR_DLL_STS_RSVD1(v)   ((((reg32_t) v) << 25) & BM_GPMI_WRITE_DDR_DLL_STS_RSVD1)
#else
#define BF_GPMI_WRITE_DDR_DLL_STS_RSVD1(v)   (((v) << 25) & BM_GPMI_WRITE_DDR_DLL_STS_RSVD1)
#endif
/* --- Register HW_GPMI_WRITE_DDR_DLL_STS, field REF_SEL */

#define BP_GPMI_WRITE_DDR_DLL_STS_REF_SEL      17
#define BM_GPMI_WRITE_DDR_DLL_STS_REF_SEL      0x01FE0000

#define BF_GPMI_WRITE_DDR_DLL_STS_REF_SEL(v)   (((v) << 17) & BM_GPMI_WRITE_DDR_DLL_STS_REF_SEL)
/* --- Register HW_GPMI_WRITE_DDR_DLL_STS, field REF_LOCK */

#define BP_GPMI_WRITE_DDR_DLL_STS_REF_LOCK      16
#define BM_GPMI_WRITE_DDR_DLL_STS_REF_LOCK      0x00010000

#define BF_GPMI_WRITE_DDR_DLL_STS_REF_LOCK(v)   (((v) << 16) & BM_GPMI_WRITE_DDR_DLL_STS_REF_LOCK)
/* --- Register HW_GPMI_WRITE_DDR_DLL_STS, field RSVD0 */

#define BP_GPMI_WRITE_DDR_DLL_STS_RSVD0      9
#define BM_GPMI_WRITE_DDR_DLL_STS_RSVD0      0x0000FE00

#define BF_GPMI_WRITE_DDR_DLL_STS_RSVD0(v)   (((v) << 9) & BM_GPMI_WRITE_DDR_DLL_STS_RSVD0)
/* --- Register HW_GPMI_WRITE_DDR_DLL_STS, field SLV_SEL */

#define BP_GPMI_WRITE_DDR_DLL_STS_SLV_SEL      1
#define BM_GPMI_WRITE_DDR_DLL_STS_SLV_SEL      0x000001FE

#define BF_GPMI_WRITE_DDR_DLL_STS_SLV_SEL(v)   (((v) << 1) & BM_GPMI_WRITE_DDR_DLL_STS_SLV_SEL)
/* --- Register HW_GPMI_WRITE_DDR_DLL_STS, field SLV_LOCK */

#define BP_GPMI_WRITE_DDR_DLL_STS_SLV_LOCK      0
#define BM_GPMI_WRITE_DDR_DLL_STS_SLV_LOCK      0x00000001

#define BF_GPMI_WRITE_DDR_DLL_STS_SLV_LOCK(v)   (((v) << 0) & BM_GPMI_WRITE_DDR_DLL_STS_SLV_LOCK)

#endif /* _GPMI_H */

////////////////////////////////////////////////////////////////////////////////
