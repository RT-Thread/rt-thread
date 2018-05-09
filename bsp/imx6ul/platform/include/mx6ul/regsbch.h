/*
 * Copyright (C) 2011-2012, Freescale Semiconductor, Inc. All Rights Reserved
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * Freescale Semiconductor, Inc.
 */

#ifndef _BCH_H
#define _BCH_H  1

#include "regs.h"
//#include "registers.h"

#ifndef REGS_BCH_BASE
#define REGS_BCH_BASE (REGS_BASE + 0x114000)
#endif

/*
 * HW_BCH_CTRL - Hardware BCH ECC Accelerator Control Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned COMPLETE_IRQ:1;
        unsigned RSVD0:1;
        unsigned DEBUG_STALL_IRQ:1;
        unsigned BM_ERROR_IRQ:1;
        unsigned RSVD1:4;
        unsigned COMPLETE_IRQ_EN:1;
        unsigned RSVD2:1;
        unsigned DEBUG_STALL_IRQ_EN:1;
        unsigned RSVD3:5;
        unsigned M2M_ENABLE:1;
        unsigned M2M_ENCODE:1;
        unsigned M2M_LAYOUT:2;
        unsigned RSVD4:2;
        unsigned DEBUGSYNDROME:1;
        unsigned RSVD5:7;
        unsigned CLKGATE:1;
        unsigned SFTRST:1;
    } B;
} hw_bch_ctrl_t;
#endif

/*
 * constants & macros for entire HW_BCH_CTRL register
 */
#define HW_BCH_CTRL_ADDR      (0x00114000)
#define HW_BCH_CTRL_SET_ADDR  (0x00114004)
#define HW_BCH_CTRL_CLR_ADDR  (0x00114008)
#define HW_BCH_CTRL_TOG_ADDR  (0x0011400c)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_CTRL           (*(volatile hw_bch_ctrl_t *) HW_BCH_CTRL_ADDR)
#define HW_BCH_CTRL_RD()      (HW_BCH_CTRL.U)
#define HW_BCH_CTRL_WR(v)     (HW_BCH_CTRL.U = (v))
#define HW_BCH_CTRL_SET(v)    ((*(volatile reg32_t *) HW_BCH_CTRL_SET_ADDR) = (v))
#define HW_BCH_CTRL_CLR(v)    ((*(volatile reg32_t *) HW_BCH_CTRL_CLR_ADDR) = (v))
#define HW_BCH_CTRL_TOG(v)    ((*(volatile reg32_t *) HW_BCH_CTRL_TOG_ADDR) = (v))
#else
#define HW_BCH_CTRL_RD()      (_rbase->mem32_read(HW_BCH_CTRL_ADDR))
#define HW_BCH_CTRL_WR(v)     (_rbase->mem32_write(HW_BCH_CTRL_ADDR,(v)))
#define HW_BCH_CTRL_SET(v)    (_rbase->mem32_write(HW_BCH_CTRL_SET_ADDR,(v)))
#define HW_BCH_CTRL_CLR(v)    (_rbase->mem32_write(HW_BCH_CTRL_CLR_ADDR,(v)))
#define HW_BCH_CTRL_TOG(v)    (_rbase->mem32_write(HW_BCH_CTRL_TOG_ADDR,(v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_CTRL bitfields
 */
/* --- Register HW_BCH_CTRL, field SFTRST */

#define BP_BCH_CTRL_SFTRST      31
#define BM_BCH_CTRL_SFTRST      0x80000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_CTRL_SFTRST(v)   ((((reg32_t) v) << 31) & BM_BCH_CTRL_SFTRST)
#else
#define BF_BCH_CTRL_SFTRST(v)   (((v) << 31) & BM_BCH_CTRL_SFTRST)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_SFTRST(v)   BF_CS1(BCH_CTRL, SFTRST, v)
#endif

#define BV_BCH_CTRL_SFTRST__RUN    0x0
#define BV_BCH_CTRL_SFTRST__RESET  0x1

/* --- Register HW_BCH_CTRL, field CLKGATE */

#define BP_BCH_CTRL_CLKGATE      30
#define BM_BCH_CTRL_CLKGATE      0x40000000

#define BF_BCH_CTRL_CLKGATE(v)   (((v) << 30) & BM_BCH_CTRL_CLKGATE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_CLKGATE(v)   BF_CS1(BCH_CTRL, CLKGATE, v)
#endif

#define BV_BCH_CTRL_CLKGATE__RUN      0x0
#define BV_BCH_CTRL_CLKGATE__NO_CLKS  0x1

/* --- Register HW_BCH_CTRL, field RSVD5 */

#define BP_BCH_CTRL_RSVD5      23
#define BM_BCH_CTRL_RSVD5      0x3F800000

#define BF_BCH_CTRL_RSVD5(v)   (((v) << 23) & BM_BCH_CTRL_RSVD5)
/* --- Register HW_BCH_CTRL, field DEBUGSYNDROME */

#define BP_BCH_CTRL_DEBUGSYNDROME      22
#define BM_BCH_CTRL_DEBUGSYNDROME      0x00400000

#define BF_BCH_CTRL_DEBUGSYNDROME(v)   (((v) << 22) & BM_BCH_CTRL_DEBUGSYNDROME)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_DEBUGSYNDROME(v)   BF_CS1(BCH_CTRL, DEBUGSYNDROME, v)
#endif

/* --- Register HW_BCH_CTRL, field RSVD4 */

#define BP_BCH_CTRL_RSVD4      20
#define BM_BCH_CTRL_RSVD4      0x00300000

#define BF_BCH_CTRL_RSVD4(v)   (((v) << 20) & BM_BCH_CTRL_RSVD4)
/* --- Register HW_BCH_CTRL, field M2M_LAYOUT */

#define BP_BCH_CTRL_M2M_LAYOUT      18
#define BM_BCH_CTRL_M2M_LAYOUT      0x000C0000

#define BF_BCH_CTRL_M2M_LAYOUT(v)   (((v) << 18) & BM_BCH_CTRL_M2M_LAYOUT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_M2M_LAYOUT(v)   BF_CS1(BCH_CTRL, M2M_LAYOUT, v)
#endif

/* --- Register HW_BCH_CTRL, field M2M_ENCODE */

#define BP_BCH_CTRL_M2M_ENCODE      17
#define BM_BCH_CTRL_M2M_ENCODE      0x00020000

#define BF_BCH_CTRL_M2M_ENCODE(v)   (((v) << 17) & BM_BCH_CTRL_M2M_ENCODE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_M2M_ENCODE(v)   BF_CS1(BCH_CTRL, M2M_ENCODE, v)
#endif

/* --- Register HW_BCH_CTRL, field M2M_ENABLE */

#define BP_BCH_CTRL_M2M_ENABLE      16
#define BM_BCH_CTRL_M2M_ENABLE      0x00010000

#define BF_BCH_CTRL_M2M_ENABLE(v)   (((v) << 16) & BM_BCH_CTRL_M2M_ENABLE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_M2M_ENABLE(v)   BF_CS1(BCH_CTRL, M2M_ENABLE, v)
#endif

/* --- Register HW_BCH_CTRL, field RSVD3 */

#define BP_BCH_CTRL_RSVD3      11
#define BM_BCH_CTRL_RSVD3      0x0000F800

#define BF_BCH_CTRL_RSVD3(v)   (((v) << 11) & BM_BCH_CTRL_RSVD3)
/* --- Register HW_BCH_CTRL, field DEBUG_STALL_IRQ_EN */

#define BP_BCH_CTRL_DEBUG_STALL_IRQ_EN      10
#define BM_BCH_CTRL_DEBUG_STALL_IRQ_EN      0x00000400

#define BF_BCH_CTRL_DEBUG_STALL_IRQ_EN(v)   (((v) << 10) & BM_BCH_CTRL_DEBUG_STALL_IRQ_EN)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_DEBUG_STALL_IRQ_EN(v)   BF_CS1(BCH_CTRL, DEBUG_STALL_IRQ_EN, v)
#endif

/* --- Register HW_BCH_CTRL, field RSVD2 */

#define BP_BCH_CTRL_RSVD2      9
#define BM_BCH_CTRL_RSVD2      0x00000200

#define BF_BCH_CTRL_RSVD2(v)   (((v) << 9) & BM_BCH_CTRL_RSVD2)
/* --- Register HW_BCH_CTRL, field COMPLETE_IRQ_EN */

#define BP_BCH_CTRL_COMPLETE_IRQ_EN      8
#define BM_BCH_CTRL_COMPLETE_IRQ_EN      0x00000100

#define BF_BCH_CTRL_COMPLETE_IRQ_EN(v)   (((v) << 8) & BM_BCH_CTRL_COMPLETE_IRQ_EN)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_COMPLETE_IRQ_EN(v)   BF_CS1(BCH_CTRL, COMPLETE_IRQ_EN, v)
#endif

/* --- Register HW_BCH_CTRL, field RSVD1 */

#define BP_BCH_CTRL_RSVD1      4
#define BM_BCH_CTRL_RSVD1      0x000000F0

#define BF_BCH_CTRL_RSVD1(v)   (((v) << 4) & BM_BCH_CTRL_RSVD1)
/* --- Register HW_BCH_CTRL, field BM_ERROR_IRQ */

#define BP_BCH_CTRL_BM_ERROR_IRQ      3
#define BM_BCH_CTRL_BM_ERROR_IRQ      0x00000008

#define BF_BCH_CTRL_BM_ERROR_IRQ(v)   (((v) << 3) & BM_BCH_CTRL_BM_ERROR_IRQ)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_BM_ERROR_IRQ(v)   BF_CS1(BCH_CTRL, BM_ERROR_IRQ, v)
#endif

/* --- Register HW_BCH_CTRL, field DEBUG_STALL_IRQ */

#define BP_BCH_CTRL_DEBUG_STALL_IRQ      2
#define BM_BCH_CTRL_DEBUG_STALL_IRQ      0x00000004

#define BF_BCH_CTRL_DEBUG_STALL_IRQ(v)   (((v) << 2) & BM_BCH_CTRL_DEBUG_STALL_IRQ)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_DEBUG_STALL_IRQ(v)   BF_CS1(BCH_CTRL, DEBUG_STALL_IRQ, v)
#endif

/* --- Register HW_BCH_CTRL, field RSVD0 */

#define BP_BCH_CTRL_RSVD0      1
#define BM_BCH_CTRL_RSVD0      0x00000002

#define BF_BCH_CTRL_RSVD0(v)   (((v) << 1) & BM_BCH_CTRL_RSVD0)
/* --- Register HW_BCH_CTRL, field COMPLETE_IRQ */

#define BP_BCH_CTRL_COMPLETE_IRQ      0
#define BM_BCH_CTRL_COMPLETE_IRQ      0x00000001

#define BF_BCH_CTRL_COMPLETE_IRQ(v)   (((v) << 0) & BM_BCH_CTRL_COMPLETE_IRQ)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_CTRL_COMPLETE_IRQ(v)   BF_CS1(BCH_CTRL, COMPLETE_IRQ, v)
#endif

/*
 * HW_BCH_STATUS0 - Hardware ECC Accelerator Status Register 0
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned RSVD0:2;
        unsigned UNCORRECTABLE:1;
        unsigned CORRECTED:1;
        unsigned ALLONES:1;
        unsigned RSVD1:3;
        unsigned STATUS_BLK0:8;
        unsigned COMPLETED_CE:4;
        unsigned HANDLE:12;
    } B;
} hw_bch_status0_t;
#endif

/*
 * constants & macros for entire HW_BCH_STATUS0 register
 */
#define HW_BCH_STATUS0_ADDR      (0x00114010)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_STATUS0           (*(volatile hw_bch_status0_t *) HW_BCH_STATUS0_ADDR)
#define HW_BCH_STATUS0_RD()      (HW_BCH_STATUS0.U)
#else
#define HW_BCH_STATUS0_RD()      (_rbase->mem32_read(HW_BCH_STATUS0_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_STATUS0 bitfields
 */
/* --- Register HW_BCH_STATUS0, field HANDLE */

#define BP_BCH_STATUS0_HANDLE      20
#define BM_BCH_STATUS0_HANDLE      0xFFF00000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_STATUS0_HANDLE(v)   ((((reg32_t) v) << 20) & BM_BCH_STATUS0_HANDLE)
#else
#define BF_BCH_STATUS0_HANDLE(v)   (((v) << 20) & BM_BCH_STATUS0_HANDLE)
#endif
/* --- Register HW_BCH_STATUS0, field COMPLETED_CE */

#define BP_BCH_STATUS0_COMPLETED_CE      16
#define BM_BCH_STATUS0_COMPLETED_CE      0x000F0000

#define BF_BCH_STATUS0_COMPLETED_CE(v)   (((v) << 16) & BM_BCH_STATUS0_COMPLETED_CE)
/* --- Register HW_BCH_STATUS0, field STATUS_BLK0 */

#define BP_BCH_STATUS0_STATUS_BLK0      8
#define BM_BCH_STATUS0_STATUS_BLK0      0x0000FF00

#define BF_BCH_STATUS0_STATUS_BLK0(v)   (((v) << 8) & BM_BCH_STATUS0_STATUS_BLK0)
#define BV_BCH_STATUS0_STATUS_BLK0__ZERO           0x00
#define BV_BCH_STATUS0_STATUS_BLK0__ERROR1         0x01
#define BV_BCH_STATUS0_STATUS_BLK0__ERROR2         0x02
#define BV_BCH_STATUS0_STATUS_BLK0__ERROR3         0x03
#define BV_BCH_STATUS0_STATUS_BLK0__ERROR4         0x04
#define BV_BCH_STATUS0_STATUS_BLK0__UNCORRECTABLE  0xFE
#define BV_BCH_STATUS0_STATUS_BLK0__ERASED         0xFF

/* --- Register HW_BCH_STATUS0, field RSVD1 */

#define BP_BCH_STATUS0_RSVD1      5
#define BM_BCH_STATUS0_RSVD1      0x000000E0

#define BF_BCH_STATUS0_RSVD1(v)   (((v) << 5) & BM_BCH_STATUS0_RSVD1)
/* --- Register HW_BCH_STATUS0, field ALLONES */

#define BP_BCH_STATUS0_ALLONES      4
#define BM_BCH_STATUS0_ALLONES      0x00000010

#define BF_BCH_STATUS0_ALLONES(v)   (((v) << 4) & BM_BCH_STATUS0_ALLONES)
/* --- Register HW_BCH_STATUS0, field CORRECTED */

#define BP_BCH_STATUS0_CORRECTED      3
#define BM_BCH_STATUS0_CORRECTED      0x00000008

#define BF_BCH_STATUS0_CORRECTED(v)   (((v) << 3) & BM_BCH_STATUS0_CORRECTED)
/* --- Register HW_BCH_STATUS0, field UNCORRECTABLE */

#define BP_BCH_STATUS0_UNCORRECTABLE      2
#define BM_BCH_STATUS0_UNCORRECTABLE      0x00000004

#define BF_BCH_STATUS0_UNCORRECTABLE(v)   (((v) << 2) & BM_BCH_STATUS0_UNCORRECTABLE)
/* --- Register HW_BCH_STATUS0, field RSVD0 */

#define BP_BCH_STATUS0_RSVD0      0
#define BM_BCH_STATUS0_RSVD0      0x00000003

#define BF_BCH_STATUS0_RSVD0(v)   (((v) << 0) & BM_BCH_STATUS0_RSVD0)

/*
 * HW_BCH_MODE - Hardware ECC Accelerator Mode Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned ERASE_THRESHOLD:8;
        unsigned RSVD:24;
    } B;
} hw_bch_mode_t;
#endif

/*
 * constants & macros for entire HW_BCH_MODE register
 */
#define HW_BCH_MODE_ADDR      (0x00114020)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_MODE           (*(volatile hw_bch_mode_t *) HW_BCH_MODE_ADDR)
#define HW_BCH_MODE_RD()      (HW_BCH_MODE.U)
#define HW_BCH_MODE_WR(v)     (HW_BCH_MODE.U = (v))
#define HW_BCH_MODE_SET(v)    (HW_BCH_MODE_WR(HW_BCH_MODE_RD() |  (v)))
#define HW_BCH_MODE_CLR(v)    (HW_BCH_MODE_WR(HW_BCH_MODE_RD() & ~(v)))
#define HW_BCH_MODE_TOG(v)    (HW_BCH_MODE_WR(HW_BCH_MODE_RD() ^  (v)))
#else
#define HW_BCH_MODE_RD()      (_rbase->mem32_read(HW_BCH_MODE_ADDR))
#define HW_BCH_MODE_WR(v)     (_rbase->mem32_write(HW_BCH_MODE_ADDR,(v)))
#define HW_BCH_MODE_SET(v)    (HW_BCH_MODE_WR(HW_BCH_MODE_RD() |  (v)))
#define HW_BCH_MODE_CLR(v)    (HW_BCH_MODE_WR(HW_BCH_MODE_RD() & ~(v)))
#define HW_BCH_MODE_TOG(v)    (HW_BCH_MODE_WR(HW_BCH_MODE_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_MODE bitfields
 */
/* --- Register HW_BCH_MODE, field RSVD */

#define BP_BCH_MODE_RSVD      8
#define BM_BCH_MODE_RSVD      0xFFFFFF00

#ifndef __LANGUAGE_ASM__
#define BF_BCH_MODE_RSVD(v)   ((((reg32_t) v) << 8) & BM_BCH_MODE_RSVD)
#else
#define BF_BCH_MODE_RSVD(v)   (((v) << 8) & BM_BCH_MODE_RSVD)
#endif
/* --- Register HW_BCH_MODE, field ERASE_THRESHOLD */

#define BP_BCH_MODE_ERASE_THRESHOLD      0
#define BM_BCH_MODE_ERASE_THRESHOLD      0x000000FF

#define BF_BCH_MODE_ERASE_THRESHOLD(v)   (((v) << 0) & BM_BCH_MODE_ERASE_THRESHOLD)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_MODE_ERASE_THRESHOLD(v)   (HW_BCH_MODE.B.ERASE_THRESHOLD = (v))
#endif

/*
 * HW_BCH_ENCODEPTR - Hardware BCH ECC Loopback Encode Buffer Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned ADDR:32;
    } B;
} hw_bch_encodeptr_t;
#endif

/*
 * constants & macros for entire HW_BCH_ENCODEPTR register
 */
#define HW_BCH_ENCODEPTR_ADDR      (0x00114030)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_ENCODEPTR           (*(volatile hw_bch_encodeptr_t *) HW_BCH_ENCODEPTR_ADDR)
#define HW_BCH_ENCODEPTR_RD()      (HW_BCH_ENCODEPTR.U)
#define HW_BCH_ENCODEPTR_WR(v)     (HW_BCH_ENCODEPTR.U = (v))
#define HW_BCH_ENCODEPTR_SET(v)    (HW_BCH_ENCODEPTR_WR(HW_BCH_ENCODEPTR_RD() |  (v)))
#define HW_BCH_ENCODEPTR_CLR(v)    (HW_BCH_ENCODEPTR_WR(HW_BCH_ENCODEPTR_RD() & ~(v)))
#define HW_BCH_ENCODEPTR_TOG(v)    (HW_BCH_ENCODEPTR_WR(HW_BCH_ENCODEPTR_RD() ^  (v)))
#else
#define HW_BCH_ENCODEPTR_RD()      (_rbase->mem32_read(HW_BCH_ENCODEPTR_ADDR))
#define HW_BCH_ENCODEPTR_WR(v)     (_rbase->mem32_write(HW_BCH_ENCODEPTR_ADDR,(v)))
#define HW_BCH_ENCODEPTR_SET(v)    (HW_BCH_ENCODEPTR_WR(HW_BCH_ENCODEPTR_RD() |  (v)))
#define HW_BCH_ENCODEPTR_CLR(v)    (HW_BCH_ENCODEPTR_WR(HW_BCH_ENCODEPTR_RD() & ~(v)))
#define HW_BCH_ENCODEPTR_TOG(v)    (HW_BCH_ENCODEPTR_WR(HW_BCH_ENCODEPTR_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_ENCODEPTR bitfields
 */
/* --- Register HW_BCH_ENCODEPTR, field ADDR */

#define BP_BCH_ENCODEPTR_ADDR      0
#define BM_BCH_ENCODEPTR_ADDR      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_ENCODEPTR_ADDR(v)   ((reg32_t) v)
#else
#define BF_BCH_ENCODEPTR_ADDR(v)   (v)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_ENCODEPTR_ADDR(v)   (HW_BCH_ENCODEPTR.B.ADDR = (v))
#endif

/*
 * HW_BCH_DATAPTR - Hardware BCH ECC Loopback Data Buffer Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned ADDR:32;
    } B;
} hw_bch_dataptr_t;
#endif

/*
 * constants & macros for entire HW_BCH_DATAPTR register
 */
#define HW_BCH_DATAPTR_ADDR      (0x00114040)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_DATAPTR           (*(volatile hw_bch_dataptr_t *) HW_BCH_DATAPTR_ADDR)
#define HW_BCH_DATAPTR_RD()      (HW_BCH_DATAPTR.U)
#define HW_BCH_DATAPTR_WR(v)     (HW_BCH_DATAPTR.U = (v))
#define HW_BCH_DATAPTR_SET(v)    (HW_BCH_DATAPTR_WR(HW_BCH_DATAPTR_RD() |  (v)))
#define HW_BCH_DATAPTR_CLR(v)    (HW_BCH_DATAPTR_WR(HW_BCH_DATAPTR_RD() & ~(v)))
#define HW_BCH_DATAPTR_TOG(v)    (HW_BCH_DATAPTR_WR(HW_BCH_DATAPTR_RD() ^  (v)))
#else
#define HW_BCH_DATAPTR_RD()      (_rbase->mem32_read(HW_BCH_DATAPTR_ADDR))
#define HW_BCH_DATAPTR_WR(v)     (_rbase->mem32_write(HW_BCH_DATAPTR_ADDR,(v)))
#define HW_BCH_DATAPTR_SET(v)    (HW_BCH_DATAPTR_WR(HW_BCH_DATAPTR_RD() |  (v)))
#define HW_BCH_DATAPTR_CLR(v)    (HW_BCH_DATAPTR_WR(HW_BCH_DATAPTR_RD() & ~(v)))
#define HW_BCH_DATAPTR_TOG(v)    (HW_BCH_DATAPTR_WR(HW_BCH_DATAPTR_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_DATAPTR bitfields
 */
/* --- Register HW_BCH_DATAPTR, field ADDR */

#define BP_BCH_DATAPTR_ADDR      0
#define BM_BCH_DATAPTR_ADDR      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_DATAPTR_ADDR(v)   ((reg32_t) v)
#else
#define BF_BCH_DATAPTR_ADDR(v)   (v)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DATAPTR_ADDR(v)   (HW_BCH_DATAPTR.B.ADDR = (v))
#endif

/*
 * HW_BCH_METAPTR - Hardware BCH ECC Loopback Metadata Buffer Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned ADDR:32;
    } B;
} hw_bch_metaptr_t;
#endif

/*
 * constants & macros for entire HW_BCH_METAPTR register
 */
#define HW_BCH_METAPTR_ADDR      (0x00114050)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_METAPTR           (*(volatile hw_bch_metaptr_t *) HW_BCH_METAPTR_ADDR)
#define HW_BCH_METAPTR_RD()      (HW_BCH_METAPTR.U)
#define HW_BCH_METAPTR_WR(v)     (HW_BCH_METAPTR.U = (v))
#define HW_BCH_METAPTR_SET(v)    (HW_BCH_METAPTR_WR(HW_BCH_METAPTR_RD() |  (v)))
#define HW_BCH_METAPTR_CLR(v)    (HW_BCH_METAPTR_WR(HW_BCH_METAPTR_RD() & ~(v)))
#define HW_BCH_METAPTR_TOG(v)    (HW_BCH_METAPTR_WR(HW_BCH_METAPTR_RD() ^  (v)))
#else
#define HW_BCH_METAPTR_RD()      (_rbase->mem32_read(HW_BCH_METAPTR_ADDR))
#define HW_BCH_METAPTR_WR(v)     (_rbase->mem32_write(HW_BCH_METAPTR_ADDR,(v)))
#define HW_BCH_METAPTR_SET(v)    (HW_BCH_METAPTR_WR(HW_BCH_METAPTR_RD() |  (v)))
#define HW_BCH_METAPTR_CLR(v)    (HW_BCH_METAPTR_WR(HW_BCH_METAPTR_RD() & ~(v)))
#define HW_BCH_METAPTR_TOG(v)    (HW_BCH_METAPTR_WR(HW_BCH_METAPTR_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_METAPTR bitfields
 */
/* --- Register HW_BCH_METAPTR, field ADDR */

#define BP_BCH_METAPTR_ADDR      0
#define BM_BCH_METAPTR_ADDR      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_METAPTR_ADDR(v)   ((reg32_t) v)
#else
#define BF_BCH_METAPTR_ADDR(v)   (v)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_METAPTR_ADDR(v)   (HW_BCH_METAPTR.B.ADDR = (v))
#endif

/*
 * HW_BCH_LAYOUTSELECT - Hardware ECC Accelerator Layout Select Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned CS0_SELECT:2;
        unsigned CS1_SELECT:2;
        unsigned CS2_SELECT:2;
        unsigned CS3_SELECT:2;
        unsigned CS4_SELECT:2;
        unsigned CS5_SELECT:2;
        unsigned CS6_SELECT:2;
        unsigned CS7_SELECT:2;
        unsigned CS8_SELECT:2;
        unsigned CS9_SELECT:2;
        unsigned CS10_SELECT:2;
        unsigned CS11_SELECT:2;
        unsigned CS12_SELECT:2;
        unsigned CS13_SELECT:2;
        unsigned CS14_SELECT:2;
        unsigned CS15_SELECT:2;
    } B;
} hw_bch_layoutselect_t;
#endif

/*
 * constants & macros for entire HW_BCH_LAYOUTSELECT register
 */
#define HW_BCH_LAYOUTSELECT_ADDR      (0x00114070)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_LAYOUTSELECT           (*(volatile hw_bch_layoutselect_t *) HW_BCH_LAYOUTSELECT_ADDR)
#define HW_BCH_LAYOUTSELECT_RD()      (HW_BCH_LAYOUTSELECT.U)
#define HW_BCH_LAYOUTSELECT_WR(v)     (HW_BCH_LAYOUTSELECT.U = (v))
#define HW_BCH_LAYOUTSELECT_SET(v)    (HW_BCH_LAYOUTSELECT_WR(HW_BCH_LAYOUTSELECT_RD() |  (v)))
#define HW_BCH_LAYOUTSELECT_CLR(v)    (HW_BCH_LAYOUTSELECT_WR(HW_BCH_LAYOUTSELECT_RD() & ~(v)))
#define HW_BCH_LAYOUTSELECT_TOG(v)    (HW_BCH_LAYOUTSELECT_WR(HW_BCH_LAYOUTSELECT_RD() ^  (v)))
#else
#define HW_BCH_LAYOUTSELECT_RD()      (_rbase->mem32_read(HW_BCH_LAYOUTSELECT_ADDR))
#define HW_BCH_LAYOUTSELECT_WR(v)     (_rbase->mem32_write(HW_BCH_LAYOUTSELECT_ADDR,(v)))
#define HW_BCH_LAYOUTSELECT_SET(v)    (HW_BCH_LAYOUTSELECT_WR(HW_BCH_LAYOUTSELECT_RD() |  (v)))
#define HW_BCH_LAYOUTSELECT_CLR(v)    (HW_BCH_LAYOUTSELECT_WR(HW_BCH_LAYOUTSELECT_RD() & ~(v)))
#define HW_BCH_LAYOUTSELECT_TOG(v)    (HW_BCH_LAYOUTSELECT_WR(HW_BCH_LAYOUTSELECT_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_LAYOUTSELECT bitfields
 */
/* --- Register HW_BCH_LAYOUTSELECT, field CS15_SELECT */

#define BP_BCH_LAYOUTSELECT_CS15_SELECT      30
#define BM_BCH_LAYOUTSELECT_CS15_SELECT      0xC0000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_LAYOUTSELECT_CS15_SELECT(v)   ((((reg32_t) v) << 30) & BM_BCH_LAYOUTSELECT_CS15_SELECT)
#else
#define BF_BCH_LAYOUTSELECT_CS15_SELECT(v)   (((v) << 30) & BM_BCH_LAYOUTSELECT_CS15_SELECT)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS15_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS15_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS14_SELECT */

#define BP_BCH_LAYOUTSELECT_CS14_SELECT      28
#define BM_BCH_LAYOUTSELECT_CS14_SELECT      0x30000000

#define BF_BCH_LAYOUTSELECT_CS14_SELECT(v)   (((v) << 28) & BM_BCH_LAYOUTSELECT_CS14_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS14_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS14_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS13_SELECT */

#define BP_BCH_LAYOUTSELECT_CS13_SELECT      26
#define BM_BCH_LAYOUTSELECT_CS13_SELECT      0x0C000000

#define BF_BCH_LAYOUTSELECT_CS13_SELECT(v)   (((v) << 26) & BM_BCH_LAYOUTSELECT_CS13_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS13_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS13_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS12_SELECT */

#define BP_BCH_LAYOUTSELECT_CS12_SELECT      24
#define BM_BCH_LAYOUTSELECT_CS12_SELECT      0x03000000

#define BF_BCH_LAYOUTSELECT_CS12_SELECT(v)   (((v) << 24) & BM_BCH_LAYOUTSELECT_CS12_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS12_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS12_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS11_SELECT */

#define BP_BCH_LAYOUTSELECT_CS11_SELECT      22
#define BM_BCH_LAYOUTSELECT_CS11_SELECT      0x00C00000

#define BF_BCH_LAYOUTSELECT_CS11_SELECT(v)   (((v) << 22) & BM_BCH_LAYOUTSELECT_CS11_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS11_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS11_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS10_SELECT */

#define BP_BCH_LAYOUTSELECT_CS10_SELECT      20
#define BM_BCH_LAYOUTSELECT_CS10_SELECT      0x00300000

#define BF_BCH_LAYOUTSELECT_CS10_SELECT(v)   (((v) << 20) & BM_BCH_LAYOUTSELECT_CS10_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS10_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS10_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS9_SELECT */

#define BP_BCH_LAYOUTSELECT_CS9_SELECT      18
#define BM_BCH_LAYOUTSELECT_CS9_SELECT      0x000C0000

#define BF_BCH_LAYOUTSELECT_CS9_SELECT(v)   (((v) << 18) & BM_BCH_LAYOUTSELECT_CS9_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS9_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS9_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS8_SELECT */

#define BP_BCH_LAYOUTSELECT_CS8_SELECT      16
#define BM_BCH_LAYOUTSELECT_CS8_SELECT      0x00030000

#define BF_BCH_LAYOUTSELECT_CS8_SELECT(v)   (((v) << 16) & BM_BCH_LAYOUTSELECT_CS8_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS8_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS8_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS7_SELECT */

#define BP_BCH_LAYOUTSELECT_CS7_SELECT      14
#define BM_BCH_LAYOUTSELECT_CS7_SELECT      0x0000C000

#define BF_BCH_LAYOUTSELECT_CS7_SELECT(v)   (((v) << 14) & BM_BCH_LAYOUTSELECT_CS7_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS7_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS7_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS6_SELECT */

#define BP_BCH_LAYOUTSELECT_CS6_SELECT      12
#define BM_BCH_LAYOUTSELECT_CS6_SELECT      0x00003000

#define BF_BCH_LAYOUTSELECT_CS6_SELECT(v)   (((v) << 12) & BM_BCH_LAYOUTSELECT_CS6_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS6_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS6_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS5_SELECT */

#define BP_BCH_LAYOUTSELECT_CS5_SELECT      10
#define BM_BCH_LAYOUTSELECT_CS5_SELECT      0x00000C00

#define BF_BCH_LAYOUTSELECT_CS5_SELECT(v)   (((v) << 10) & BM_BCH_LAYOUTSELECT_CS5_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS5_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS5_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS4_SELECT */

#define BP_BCH_LAYOUTSELECT_CS4_SELECT      8
#define BM_BCH_LAYOUTSELECT_CS4_SELECT      0x00000300

#define BF_BCH_LAYOUTSELECT_CS4_SELECT(v)   (((v) << 8) & BM_BCH_LAYOUTSELECT_CS4_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS4_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS4_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS3_SELECT */

#define BP_BCH_LAYOUTSELECT_CS3_SELECT      6
#define BM_BCH_LAYOUTSELECT_CS3_SELECT      0x000000C0

#define BF_BCH_LAYOUTSELECT_CS3_SELECT(v)   (((v) << 6) & BM_BCH_LAYOUTSELECT_CS3_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS3_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS3_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS2_SELECT */

#define BP_BCH_LAYOUTSELECT_CS2_SELECT      4
#define BM_BCH_LAYOUTSELECT_CS2_SELECT      0x00000030

#define BF_BCH_LAYOUTSELECT_CS2_SELECT(v)   (((v) << 4) & BM_BCH_LAYOUTSELECT_CS2_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS2_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS2_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS1_SELECT */

#define BP_BCH_LAYOUTSELECT_CS1_SELECT      2
#define BM_BCH_LAYOUTSELECT_CS1_SELECT      0x0000000C

#define BF_BCH_LAYOUTSELECT_CS1_SELECT(v)   (((v) << 2) & BM_BCH_LAYOUTSELECT_CS1_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS1_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS1_SELECT, v)
#endif

/* --- Register HW_BCH_LAYOUTSELECT, field CS0_SELECT */

#define BP_BCH_LAYOUTSELECT_CS0_SELECT      0
#define BM_BCH_LAYOUTSELECT_CS0_SELECT      0x00000003

#define BF_BCH_LAYOUTSELECT_CS0_SELECT(v)   (((v) << 0) & BM_BCH_LAYOUTSELECT_CS0_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_LAYOUTSELECT_CS0_SELECT(v)   BF_CS1(BCH_LAYOUTSELECT, CS0_SELECT, v)
#endif

/*
 * HW_BCH_FLASH0LAYOUT0 - Hardware BCH ECC Flash 0 Layout 0 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA0_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECC0:5;
        unsigned META_SIZE:8;
        unsigned NBLOCKS:8;
    } B;
} hw_bch_flash0layout0_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH0LAYOUT0 register
 */
#define HW_BCH_FLASH0LAYOUT0_ADDR      (0x00114080)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH0LAYOUT0           (*(volatile hw_bch_flash0layout0_t *) HW_BCH_FLASH0LAYOUT0_ADDR)
#define HW_BCH_FLASH0LAYOUT0_RD()      (HW_BCH_FLASH0LAYOUT0.U)
#define HW_BCH_FLASH0LAYOUT0_WR(v)     (HW_BCH_FLASH0LAYOUT0.U = (v))
#define HW_BCH_FLASH0LAYOUT0_SET(v)    (HW_BCH_FLASH0LAYOUT0_WR(HW_BCH_FLASH0LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH0LAYOUT0_CLR(v)    (HW_BCH_FLASH0LAYOUT0_WR(HW_BCH_FLASH0LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH0LAYOUT0_TOG(v)    (HW_BCH_FLASH0LAYOUT0_WR(HW_BCH_FLASH0LAYOUT0_RD() ^  (v)))
#else
#define HW_BCH_FLASH0LAYOUT0_RD()      (_rbase->mem32_read(HW_BCH_FLASH0LAYOUT0_ADDR))
#define HW_BCH_FLASH0LAYOUT0_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH0LAYOUT0_ADDR,(v)))
#define HW_BCH_FLASH0LAYOUT0_SET(v)    (HW_BCH_FLASH0LAYOUT0_WR(HW_BCH_FLASH0LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH0LAYOUT0_CLR(v)    (HW_BCH_FLASH0LAYOUT0_WR(HW_BCH_FLASH0LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH0LAYOUT0_TOG(v)    (HW_BCH_FLASH0LAYOUT0_WR(HW_BCH_FLASH0LAYOUT0_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH0LAYOUT0 bitfields
 */
/* --- Register HW_BCH_FLASH0LAYOUT0, field NBLOCKS */

#define BP_BCH_FLASH0LAYOUT0_NBLOCKS      24
#define BM_BCH_FLASH0LAYOUT0_NBLOCKS      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH0LAYOUT0_NBLOCKS(v)   ((((reg32_t) v) << 24) & BM_BCH_FLASH0LAYOUT0_NBLOCKS)
#else
#define BF_BCH_FLASH0LAYOUT0_NBLOCKS(v)   (((v) << 24) & BM_BCH_FLASH0LAYOUT0_NBLOCKS)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT0_NBLOCKS(v)   (HW_BCH_FLASH0LAYOUT0.B.NBLOCKS = (v))
#endif

/* --- Register HW_BCH_FLASH0LAYOUT0, field META_SIZE */

#define BP_BCH_FLASH0LAYOUT0_META_SIZE      16
#define BM_BCH_FLASH0LAYOUT0_META_SIZE      0x00FF0000

#define BF_BCH_FLASH0LAYOUT0_META_SIZE(v)   (((v) << 16) & BM_BCH_FLASH0LAYOUT0_META_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT0_META_SIZE(v)   (HW_BCH_FLASH0LAYOUT0.B.META_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH0LAYOUT0, field ECC0 */

#define BP_BCH_FLASH0LAYOUT0_ECC0      11
#define BM_BCH_FLASH0LAYOUT0_ECC0      0x0000F800

#define BF_BCH_FLASH0LAYOUT0_ECC0(v)   (((v) << 11) & BM_BCH_FLASH0LAYOUT0_ECC0)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT0_ECC0(v)   BF_CS1(BCH_FLASH0LAYOUT0, ECC0, v)
#endif

#define BV_BCH_FLASH0LAYOUT0_ECC0__NONE   0x0
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC2   0x1
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC4   0x2
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC6   0x3
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC8   0x4
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC10  0x5
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC12  0x6
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC14  0x7
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC16  0x8
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC18  0x9
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC20  0xA
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC22  0xB
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC24  0xC
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC26  0xD
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC28  0xE
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC30  0xF
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC32  0x10
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC34  0x11
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC36  0x12
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC38  0x13
#define BV_BCH_FLASH0LAYOUT0_ECC0__ECC40  0x14

/* --- Register HW_BCH_FLASH0LAYOUT0, field GF13_0_GF14_1 */

#define BP_BCH_FLASH0LAYOUT0_GF13_0_GF14_1      10
#define BM_BCH_FLASH0LAYOUT0_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH0LAYOUT0_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH0LAYOUT0_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT0_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH0LAYOUT0, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH0LAYOUT0, field DATA0_SIZE */

#define BP_BCH_FLASH0LAYOUT0_DATA0_SIZE      0
#define BM_BCH_FLASH0LAYOUT0_DATA0_SIZE      0x000003FF

#define BF_BCH_FLASH0LAYOUT0_DATA0_SIZE(v)   (((v) << 0) & BM_BCH_FLASH0LAYOUT0_DATA0_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT0_DATA0_SIZE(v)   BF_CS1(BCH_FLASH0LAYOUT0, DATA0_SIZE, v)
#endif

/*
 * HW_BCH_FLASH0LAYOUT1 - Hardware BCH ECC Flash 0 Layout 1 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATAN_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECCN:5;
        unsigned PAGE_SIZE:16;
    } B;
} hw_bch_flash0layout1_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH0LAYOUT1 register
 */
#define HW_BCH_FLASH0LAYOUT1_ADDR      (0x00114090)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH0LAYOUT1           (*(volatile hw_bch_flash0layout1_t *) HW_BCH_FLASH0LAYOUT1_ADDR)
#define HW_BCH_FLASH0LAYOUT1_RD()      (HW_BCH_FLASH0LAYOUT1.U)
#define HW_BCH_FLASH0LAYOUT1_WR(v)     (HW_BCH_FLASH0LAYOUT1.U = (v))
#define HW_BCH_FLASH0LAYOUT1_SET(v)    (HW_BCH_FLASH0LAYOUT1_WR(HW_BCH_FLASH0LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH0LAYOUT1_CLR(v)    (HW_BCH_FLASH0LAYOUT1_WR(HW_BCH_FLASH0LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH0LAYOUT1_TOG(v)    (HW_BCH_FLASH0LAYOUT1_WR(HW_BCH_FLASH0LAYOUT1_RD() ^  (v)))
#else
#define HW_BCH_FLASH0LAYOUT1_RD()      (_rbase->mem32_read(HW_BCH_FLASH0LAYOUT1_ADDR))
#define HW_BCH_FLASH0LAYOUT1_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH0LAYOUT1_ADDR,(v)))
#define HW_BCH_FLASH0LAYOUT1_SET(v)    (HW_BCH_FLASH0LAYOUT1_WR(HW_BCH_FLASH0LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH0LAYOUT1_CLR(v)    (HW_BCH_FLASH0LAYOUT1_WR(HW_BCH_FLASH0LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH0LAYOUT1_TOG(v)    (HW_BCH_FLASH0LAYOUT1_WR(HW_BCH_FLASH0LAYOUT1_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH0LAYOUT1 bitfields
 */
/* --- Register HW_BCH_FLASH0LAYOUT1, field PAGE_SIZE */

#define BP_BCH_FLASH0LAYOUT1_PAGE_SIZE      16
#define BM_BCH_FLASH0LAYOUT1_PAGE_SIZE      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(v)   ((((reg32_t) v) << 16) & BM_BCH_FLASH0LAYOUT1_PAGE_SIZE)
#else
#define BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(v)   (((v) << 16) & BM_BCH_FLASH0LAYOUT1_PAGE_SIZE)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT1_PAGE_SIZE(v)   (HW_BCH_FLASH0LAYOUT1.B.PAGE_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH0LAYOUT1, field ECCN */

#define BP_BCH_FLASH0LAYOUT1_ECCN      11
#define BM_BCH_FLASH0LAYOUT1_ECCN      0x0000F800

#define BF_BCH_FLASH0LAYOUT1_ECCN(v)   (((v) << 11) & BM_BCH_FLASH0LAYOUT1_ECCN)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT1_ECCN(v)   BF_CS1(BCH_FLASH0LAYOUT1, ECCN, v)
#endif

#define BV_BCH_FLASH0LAYOUT1_ECCN__NONE   0x0
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC2   0x1
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC4   0x2
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC6   0x3
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC8   0x4
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC10  0x5
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC12  0x6
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC14  0x7
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC16  0x8
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC18  0x9
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC20  0xA
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC22  0xB
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC24  0xC
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC26  0xD
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC28  0xE
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC30  0xF
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC32  0x10
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC34  0x11
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC36  0x12
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC38  0x13
#define BV_BCH_FLASH0LAYOUT1_ECCN__ECC40  0x14

/* --- Register HW_BCH_FLASH0LAYOUT1, field GF13_0_GF14_1 */

#define BP_BCH_FLASH0LAYOUT1_GF13_0_GF14_1      10
#define BM_BCH_FLASH0LAYOUT1_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH0LAYOUT1_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH0LAYOUT1_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT1_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH0LAYOUT1, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH0LAYOUT1, field DATAN_SIZE */

#define BP_BCH_FLASH0LAYOUT1_DATAN_SIZE      0
#define BM_BCH_FLASH0LAYOUT1_DATAN_SIZE      0x000003FF

#define BF_BCH_FLASH0LAYOUT1_DATAN_SIZE(v)   (((v) << 0) & BM_BCH_FLASH0LAYOUT1_DATAN_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH0LAYOUT1_DATAN_SIZE(v)   BF_CS1(BCH_FLASH0LAYOUT1, DATAN_SIZE, v)
#endif

/*
 * HW_BCH_FLASH1LAYOUT0 - Hardware BCH ECC Flash 1 Layout 0 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA0_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECC0:5;
        unsigned META_SIZE:8;
        unsigned NBLOCKS:8;
    } B;
} hw_bch_flash1layout0_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH1LAYOUT0 register
 */
#define HW_BCH_FLASH1LAYOUT0_ADDR      (0x001140a0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH1LAYOUT0           (*(volatile hw_bch_flash1layout0_t *) HW_BCH_FLASH1LAYOUT0_ADDR)
#define HW_BCH_FLASH1LAYOUT0_RD()      (HW_BCH_FLASH1LAYOUT0.U)
#define HW_BCH_FLASH1LAYOUT0_WR(v)     (HW_BCH_FLASH1LAYOUT0.U = (v))
#define HW_BCH_FLASH1LAYOUT0_SET(v)    (HW_BCH_FLASH1LAYOUT0_WR(HW_BCH_FLASH1LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH1LAYOUT0_CLR(v)    (HW_BCH_FLASH1LAYOUT0_WR(HW_BCH_FLASH1LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH1LAYOUT0_TOG(v)    (HW_BCH_FLASH1LAYOUT0_WR(HW_BCH_FLASH1LAYOUT0_RD() ^  (v)))
#else
#define HW_BCH_FLASH1LAYOUT0_RD()      (_rbase->mem32_read(HW_BCH_FLASH1LAYOUT0_ADDR))
#define HW_BCH_FLASH1LAYOUT0_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH1LAYOUT0_ADDR,(v)))
#define HW_BCH_FLASH1LAYOUT0_SET(v)    (HW_BCH_FLASH1LAYOUT0_WR(HW_BCH_FLASH1LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH1LAYOUT0_CLR(v)    (HW_BCH_FLASH1LAYOUT0_WR(HW_BCH_FLASH1LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH1LAYOUT0_TOG(v)    (HW_BCH_FLASH1LAYOUT0_WR(HW_BCH_FLASH1LAYOUT0_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH1LAYOUT0 bitfields
 */
/* --- Register HW_BCH_FLASH1LAYOUT0, field NBLOCKS */

#define BP_BCH_FLASH1LAYOUT0_NBLOCKS      24
#define BM_BCH_FLASH1LAYOUT0_NBLOCKS      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH1LAYOUT0_NBLOCKS(v)   ((((reg32_t) v) << 24) & BM_BCH_FLASH1LAYOUT0_NBLOCKS)
#else
#define BF_BCH_FLASH1LAYOUT0_NBLOCKS(v)   (((v) << 24) & BM_BCH_FLASH1LAYOUT0_NBLOCKS)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT0_NBLOCKS(v)   (HW_BCH_FLASH1LAYOUT0.B.NBLOCKS = (v))
#endif

/* --- Register HW_BCH_FLASH1LAYOUT0, field META_SIZE */

#define BP_BCH_FLASH1LAYOUT0_META_SIZE      16
#define BM_BCH_FLASH1LAYOUT0_META_SIZE      0x00FF0000

#define BF_BCH_FLASH1LAYOUT0_META_SIZE(v)   (((v) << 16) & BM_BCH_FLASH1LAYOUT0_META_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT0_META_SIZE(v)   (HW_BCH_FLASH1LAYOUT0.B.META_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH1LAYOUT0, field ECC0 */

#define BP_BCH_FLASH1LAYOUT0_ECC0      11
#define BM_BCH_FLASH1LAYOUT0_ECC0      0x0000F800

#define BF_BCH_FLASH1LAYOUT0_ECC0(v)   (((v) << 11) & BM_BCH_FLASH1LAYOUT0_ECC0)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT0_ECC0(v)   BF_CS1(BCH_FLASH1LAYOUT0, ECC0, v)
#endif

#define BV_BCH_FLASH1LAYOUT0_ECC0__NONE   0x0
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC2   0x1
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC4   0x2
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC6   0x3
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC8   0x4
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC10  0x5
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC12  0x6
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC14  0x7
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC16  0x8
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC18  0x9
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC20  0xA
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC22  0xB
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC24  0xC
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC26  0xD
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC28  0xE
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC30  0xF
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC32  0x10
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC34  0x11
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC36  0x12
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC38  0x13
#define BV_BCH_FLASH1LAYOUT0_ECC0__ECC40  0x14

/* --- Register HW_BCH_FLASH1LAYOUT0, field GF13_0_GF14_1 */

#define BP_BCH_FLASH1LAYOUT0_GF13_0_GF14_1      10
#define BM_BCH_FLASH1LAYOUT0_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH1LAYOUT0_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH1LAYOUT0_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT0_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH1LAYOUT0, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH1LAYOUT0, field DATA0_SIZE */

#define BP_BCH_FLASH1LAYOUT0_DATA0_SIZE      0
#define BM_BCH_FLASH1LAYOUT0_DATA0_SIZE      0x000003FF

#define BF_BCH_FLASH1LAYOUT0_DATA0_SIZE(v)   (((v) << 0) & BM_BCH_FLASH1LAYOUT0_DATA0_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT0_DATA0_SIZE(v)   BF_CS1(BCH_FLASH1LAYOUT0, DATA0_SIZE, v)
#endif

/*
 * HW_BCH_FLASH1LAYOUT1 - Hardware BCH ECC Flash 1 Layout 1 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATAN_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECCN:5;
        unsigned PAGE_SIZE:16;
    } B;
} hw_bch_flash1layout1_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH1LAYOUT1 register
 */
#define HW_BCH_FLASH1LAYOUT1_ADDR      (0x001140b0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH1LAYOUT1           (*(volatile hw_bch_flash1layout1_t *) HW_BCH_FLASH1LAYOUT1_ADDR)
#define HW_BCH_FLASH1LAYOUT1_RD()      (HW_BCH_FLASH1LAYOUT1.U)
#define HW_BCH_FLASH1LAYOUT1_WR(v)     (HW_BCH_FLASH1LAYOUT1.U = (v))
#define HW_BCH_FLASH1LAYOUT1_SET(v)    (HW_BCH_FLASH1LAYOUT1_WR(HW_BCH_FLASH1LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH1LAYOUT1_CLR(v)    (HW_BCH_FLASH1LAYOUT1_WR(HW_BCH_FLASH1LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH1LAYOUT1_TOG(v)    (HW_BCH_FLASH1LAYOUT1_WR(HW_BCH_FLASH1LAYOUT1_RD() ^  (v)))
#else
#define HW_BCH_FLASH1LAYOUT1_RD()      (_rbase->mem32_read(HW_BCH_FLASH1LAYOUT1_ADDR))
#define HW_BCH_FLASH1LAYOUT1_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH1LAYOUT1_ADDR,(v)))
#define HW_BCH_FLASH1LAYOUT1_SET(v)    (HW_BCH_FLASH1LAYOUT1_WR(HW_BCH_FLASH1LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH1LAYOUT1_CLR(v)    (HW_BCH_FLASH1LAYOUT1_WR(HW_BCH_FLASH1LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH1LAYOUT1_TOG(v)    (HW_BCH_FLASH1LAYOUT1_WR(HW_BCH_FLASH1LAYOUT1_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH1LAYOUT1 bitfields
 */
/* --- Register HW_BCH_FLASH1LAYOUT1, field PAGE_SIZE */

#define BP_BCH_FLASH1LAYOUT1_PAGE_SIZE      16
#define BM_BCH_FLASH1LAYOUT1_PAGE_SIZE      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH1LAYOUT1_PAGE_SIZE(v)   ((((reg32_t) v) << 16) & BM_BCH_FLASH1LAYOUT1_PAGE_SIZE)
#else
#define BF_BCH_FLASH1LAYOUT1_PAGE_SIZE(v)   (((v) << 16) & BM_BCH_FLASH1LAYOUT1_PAGE_SIZE)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT1_PAGE_SIZE(v)   (HW_BCH_FLASH1LAYOUT1.B.PAGE_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH1LAYOUT1, field ECCN */

#define BP_BCH_FLASH1LAYOUT1_ECCN      11
#define BM_BCH_FLASH1LAYOUT1_ECCN      0x0000F800

#define BF_BCH_FLASH1LAYOUT1_ECCN(v)   (((v) << 11) & BM_BCH_FLASH1LAYOUT1_ECCN)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT1_ECCN(v)   BF_CS1(BCH_FLASH1LAYOUT1, ECCN, v)
#endif

#define BV_BCH_FLASH1LAYOUT1_ECCN__NONE   0x0
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC2   0x1
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC4   0x2
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC6   0x3
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC8   0x4
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC10  0x5
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC12  0x6
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC14  0x7
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC16  0x8
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC18  0x9
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC20  0xA
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC22  0xB
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC24  0xC
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC26  0xD
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC28  0xE
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC30  0xF
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC32  0x10
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC34  0x11
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC36  0x12
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC38  0x13
#define BV_BCH_FLASH1LAYOUT1_ECCN__ECC40  0x14

/* --- Register HW_BCH_FLASH1LAYOUT1, field GF13_0_GF14_1 */

#define BP_BCH_FLASH1LAYOUT1_GF13_0_GF14_1      10
#define BM_BCH_FLASH1LAYOUT1_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH1LAYOUT1_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH1LAYOUT1_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT1_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH1LAYOUT1, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH1LAYOUT1, field DATAN_SIZE */

#define BP_BCH_FLASH1LAYOUT1_DATAN_SIZE      0
#define BM_BCH_FLASH1LAYOUT1_DATAN_SIZE      0x000003FF

#define BF_BCH_FLASH1LAYOUT1_DATAN_SIZE(v)   (((v) << 0) & BM_BCH_FLASH1LAYOUT1_DATAN_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH1LAYOUT1_DATAN_SIZE(v)   BF_CS1(BCH_FLASH1LAYOUT1, DATAN_SIZE, v)
#endif

/*
 * HW_BCH_FLASH2LAYOUT0 - Hardware BCH ECC Flash 2 Layout 0 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA0_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECC0:5;
        unsigned META_SIZE:8;
        unsigned NBLOCKS:8;
    } B;
} hw_bch_flash2layout0_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH2LAYOUT0 register
 */
#define HW_BCH_FLASH2LAYOUT0_ADDR      (0x001140c0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH2LAYOUT0           (*(volatile hw_bch_flash2layout0_t *) HW_BCH_FLASH2LAYOUT0_ADDR)
#define HW_BCH_FLASH2LAYOUT0_RD()      (HW_BCH_FLASH2LAYOUT0.U)
#define HW_BCH_FLASH2LAYOUT0_WR(v)     (HW_BCH_FLASH2LAYOUT0.U = (v))
#define HW_BCH_FLASH2LAYOUT0_SET(v)    (HW_BCH_FLASH2LAYOUT0_WR(HW_BCH_FLASH2LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH2LAYOUT0_CLR(v)    (HW_BCH_FLASH2LAYOUT0_WR(HW_BCH_FLASH2LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH2LAYOUT0_TOG(v)    (HW_BCH_FLASH2LAYOUT0_WR(HW_BCH_FLASH2LAYOUT0_RD() ^  (v)))
#else
#define HW_BCH_FLASH2LAYOUT0_RD()      (_rbase->mem32_read(HW_BCH_FLASH2LAYOUT0_ADDR))
#define HW_BCH_FLASH2LAYOUT0_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH2LAYOUT0_ADDR,(v)))
#define HW_BCH_FLASH2LAYOUT0_SET(v)    (HW_BCH_FLASH2LAYOUT0_WR(HW_BCH_FLASH2LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH2LAYOUT0_CLR(v)    (HW_BCH_FLASH2LAYOUT0_WR(HW_BCH_FLASH2LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH2LAYOUT0_TOG(v)    (HW_BCH_FLASH2LAYOUT0_WR(HW_BCH_FLASH2LAYOUT0_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH2LAYOUT0 bitfields
 */
/* --- Register HW_BCH_FLASH2LAYOUT0, field NBLOCKS */

#define BP_BCH_FLASH2LAYOUT0_NBLOCKS      24
#define BM_BCH_FLASH2LAYOUT0_NBLOCKS      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH2LAYOUT0_NBLOCKS(v)   ((((reg32_t) v) << 24) & BM_BCH_FLASH2LAYOUT0_NBLOCKS)
#else
#define BF_BCH_FLASH2LAYOUT0_NBLOCKS(v)   (((v) << 24) & BM_BCH_FLASH2LAYOUT0_NBLOCKS)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT0_NBLOCKS(v)   (HW_BCH_FLASH2LAYOUT0.B.NBLOCKS = (v))
#endif

/* --- Register HW_BCH_FLASH2LAYOUT0, field META_SIZE */

#define BP_BCH_FLASH2LAYOUT0_META_SIZE      16
#define BM_BCH_FLASH2LAYOUT0_META_SIZE      0x00FF0000

#define BF_BCH_FLASH2LAYOUT0_META_SIZE(v)   (((v) << 16) & BM_BCH_FLASH2LAYOUT0_META_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT0_META_SIZE(v)   (HW_BCH_FLASH2LAYOUT0.B.META_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH2LAYOUT0, field ECC0 */

#define BP_BCH_FLASH2LAYOUT0_ECC0      11
#define BM_BCH_FLASH2LAYOUT0_ECC0      0x0000F800

#define BF_BCH_FLASH2LAYOUT0_ECC0(v)   (((v) << 11) & BM_BCH_FLASH2LAYOUT0_ECC0)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT0_ECC0(v)   BF_CS1(BCH_FLASH2LAYOUT0, ECC0, v)
#endif

#define BV_BCH_FLASH2LAYOUT0_ECC0__NONE   0x0
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC2   0x1
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC4   0x2
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC6   0x3
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC8   0x4
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC10  0x5
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC12  0x6
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC14  0x7
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC16  0x8
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC18  0x9
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC20  0xA
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC22  0xB
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC24  0xC
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC26  0xD
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC28  0xE
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC30  0xF
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC32  0x10
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC34  0x11
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC36  0x12
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC38  0x13
#define BV_BCH_FLASH2LAYOUT0_ECC0__ECC40  0x14

/* --- Register HW_BCH_FLASH2LAYOUT0, field GF13_0_GF14_1 */

#define BP_BCH_FLASH2LAYOUT0_GF13_0_GF14_1      10
#define BM_BCH_FLASH2LAYOUT0_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH2LAYOUT0_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH2LAYOUT0_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT0_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH2LAYOUT0, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH2LAYOUT0, field DATA0_SIZE */

#define BP_BCH_FLASH2LAYOUT0_DATA0_SIZE      0
#define BM_BCH_FLASH2LAYOUT0_DATA0_SIZE      0x000003FF

#define BF_BCH_FLASH2LAYOUT0_DATA0_SIZE(v)   (((v) << 0) & BM_BCH_FLASH2LAYOUT0_DATA0_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT0_DATA0_SIZE(v)   BF_CS1(BCH_FLASH2LAYOUT0, DATA0_SIZE, v)
#endif

/*
 * HW_BCH_FLASH2LAYOUT1 - Hardware BCH ECC Flash 2 Layout 1 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATAN_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECCN:5;
        unsigned PAGE_SIZE:16;
    } B;
} hw_bch_flash2layout1_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH2LAYOUT1 register
 */
#define HW_BCH_FLASH2LAYOUT1_ADDR      (0x001140d0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH2LAYOUT1           (*(volatile hw_bch_flash2layout1_t *) HW_BCH_FLASH2LAYOUT1_ADDR)
#define HW_BCH_FLASH2LAYOUT1_RD()      (HW_BCH_FLASH2LAYOUT1.U)
#define HW_BCH_FLASH2LAYOUT1_WR(v)     (HW_BCH_FLASH2LAYOUT1.U = (v))
#define HW_BCH_FLASH2LAYOUT1_SET(v)    (HW_BCH_FLASH2LAYOUT1_WR(HW_BCH_FLASH2LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH2LAYOUT1_CLR(v)    (HW_BCH_FLASH2LAYOUT1_WR(HW_BCH_FLASH2LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH2LAYOUT1_TOG(v)    (HW_BCH_FLASH2LAYOUT1_WR(HW_BCH_FLASH2LAYOUT1_RD() ^  (v)))
#else
#define HW_BCH_FLASH2LAYOUT1_RD()      (_rbase->mem32_read(HW_BCH_FLASH2LAYOUT1_ADDR))
#define HW_BCH_FLASH2LAYOUT1_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH2LAYOUT1_ADDR,(v)))
#define HW_BCH_FLASH2LAYOUT1_SET(v)    (HW_BCH_FLASH2LAYOUT1_WR(HW_BCH_FLASH2LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH2LAYOUT1_CLR(v)    (HW_BCH_FLASH2LAYOUT1_WR(HW_BCH_FLASH2LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH2LAYOUT1_TOG(v)    (HW_BCH_FLASH2LAYOUT1_WR(HW_BCH_FLASH2LAYOUT1_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH2LAYOUT1 bitfields
 */
/* --- Register HW_BCH_FLASH2LAYOUT1, field PAGE_SIZE */

#define BP_BCH_FLASH2LAYOUT1_PAGE_SIZE      16
#define BM_BCH_FLASH2LAYOUT1_PAGE_SIZE      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH2LAYOUT1_PAGE_SIZE(v)   ((((reg32_t) v) << 16) & BM_BCH_FLASH2LAYOUT1_PAGE_SIZE)
#else
#define BF_BCH_FLASH2LAYOUT1_PAGE_SIZE(v)   (((v) << 16) & BM_BCH_FLASH2LAYOUT1_PAGE_SIZE)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT1_PAGE_SIZE(v)   (HW_BCH_FLASH2LAYOUT1.B.PAGE_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH2LAYOUT1, field ECCN */

#define BP_BCH_FLASH2LAYOUT1_ECCN      11
#define BM_BCH_FLASH2LAYOUT1_ECCN      0x0000F800

#define BF_BCH_FLASH2LAYOUT1_ECCN(v)   (((v) << 11) & BM_BCH_FLASH2LAYOUT1_ECCN)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT1_ECCN(v)   BF_CS1(BCH_FLASH2LAYOUT1, ECCN, v)
#endif

#define BV_BCH_FLASH2LAYOUT1_ECCN__NONE   0x0
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC2   0x1
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC4   0x2
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC6   0x3
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC8   0x4
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC10  0x5
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC12  0x6
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC14  0x7
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC16  0x8
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC18  0x9
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC20  0xA
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC22  0xB
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC24  0xC
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC26  0xD
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC28  0xE
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC30  0xF
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC32  0x10
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC34  0x11
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC36  0x12
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC38  0x13
#define BV_BCH_FLASH2LAYOUT1_ECCN__ECC40  0x14

/* --- Register HW_BCH_FLASH2LAYOUT1, field GF13_0_GF14_1 */

#define BP_BCH_FLASH2LAYOUT1_GF13_0_GF14_1      10
#define BM_BCH_FLASH2LAYOUT1_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH2LAYOUT1_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH2LAYOUT1_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT1_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH2LAYOUT1, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH2LAYOUT1, field DATAN_SIZE */

#define BP_BCH_FLASH2LAYOUT1_DATAN_SIZE      0
#define BM_BCH_FLASH2LAYOUT1_DATAN_SIZE      0x000003FF

#define BF_BCH_FLASH2LAYOUT1_DATAN_SIZE(v)   (((v) << 0) & BM_BCH_FLASH2LAYOUT1_DATAN_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH2LAYOUT1_DATAN_SIZE(v)   BF_CS1(BCH_FLASH2LAYOUT1, DATAN_SIZE, v)
#endif

/*
 * HW_BCH_FLASH3LAYOUT0 - Hardware BCH ECC Flash 3 Layout 0 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATA0_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECC0:5;
        unsigned META_SIZE:8;
        unsigned NBLOCKS:8;
    } B;
} hw_bch_flash3layout0_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH3LAYOUT0 register
 */
#define HW_BCH_FLASH3LAYOUT0_ADDR      (0x001140e0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH3LAYOUT0           (*(volatile hw_bch_flash3layout0_t *) HW_BCH_FLASH3LAYOUT0_ADDR)
#define HW_BCH_FLASH3LAYOUT0_RD()      (HW_BCH_FLASH3LAYOUT0.U)
#define HW_BCH_FLASH3LAYOUT0_WR(v)     (HW_BCH_FLASH3LAYOUT0.U = (v))
#define HW_BCH_FLASH3LAYOUT0_SET(v)    (HW_BCH_FLASH3LAYOUT0_WR(HW_BCH_FLASH3LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH3LAYOUT0_CLR(v)    (HW_BCH_FLASH3LAYOUT0_WR(HW_BCH_FLASH3LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH3LAYOUT0_TOG(v)    (HW_BCH_FLASH3LAYOUT0_WR(HW_BCH_FLASH3LAYOUT0_RD() ^  (v)))
#else
#define HW_BCH_FLASH3LAYOUT0_RD()      (_rbase->mem32_read(HW_BCH_FLASH3LAYOUT0_ADDR))
#define HW_BCH_FLASH3LAYOUT0_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH3LAYOUT0_ADDR,(v)))
#define HW_BCH_FLASH3LAYOUT0_SET(v)    (HW_BCH_FLASH3LAYOUT0_WR(HW_BCH_FLASH3LAYOUT0_RD() |  (v)))
#define HW_BCH_FLASH3LAYOUT0_CLR(v)    (HW_BCH_FLASH3LAYOUT0_WR(HW_BCH_FLASH3LAYOUT0_RD() & ~(v)))
#define HW_BCH_FLASH3LAYOUT0_TOG(v)    (HW_BCH_FLASH3LAYOUT0_WR(HW_BCH_FLASH3LAYOUT0_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH3LAYOUT0 bitfields
 */
/* --- Register HW_BCH_FLASH3LAYOUT0, field NBLOCKS */

#define BP_BCH_FLASH3LAYOUT0_NBLOCKS      24
#define BM_BCH_FLASH3LAYOUT0_NBLOCKS      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH3LAYOUT0_NBLOCKS(v)   ((((reg32_t) v) << 24) & BM_BCH_FLASH3LAYOUT0_NBLOCKS)
#else
#define BF_BCH_FLASH3LAYOUT0_NBLOCKS(v)   (((v) << 24) & BM_BCH_FLASH3LAYOUT0_NBLOCKS)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT0_NBLOCKS(v)   (HW_BCH_FLASH3LAYOUT0.B.NBLOCKS = (v))
#endif

/* --- Register HW_BCH_FLASH3LAYOUT0, field META_SIZE */

#define BP_BCH_FLASH3LAYOUT0_META_SIZE      16
#define BM_BCH_FLASH3LAYOUT0_META_SIZE      0x00FF0000

#define BF_BCH_FLASH3LAYOUT0_META_SIZE(v)   (((v) << 16) & BM_BCH_FLASH3LAYOUT0_META_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT0_META_SIZE(v)   (HW_BCH_FLASH3LAYOUT0.B.META_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH3LAYOUT0, field ECC0 */

#define BP_BCH_FLASH3LAYOUT0_ECC0      11
#define BM_BCH_FLASH3LAYOUT0_ECC0      0x0000F800

#define BF_BCH_FLASH3LAYOUT0_ECC0(v)   (((v) << 11) & BM_BCH_FLASH3LAYOUT0_ECC0)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT0_ECC0(v)   BF_CS1(BCH_FLASH3LAYOUT0, ECC0, v)
#endif

#define BV_BCH_FLASH3LAYOUT0_ECC0__NONE   0x0
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC2   0x1
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC4   0x2
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC6   0x3
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC8   0x4
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC10  0x5
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC12  0x6
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC14  0x7
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC16  0x8
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC18  0x9
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC20  0xA
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC22  0xB
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC24  0xC
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC26  0xD
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC28  0xE
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC30  0xF
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC32  0x10
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC34  0x11
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC36  0x12
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC38  0x13
#define BV_BCH_FLASH3LAYOUT0_ECC0__ECC40  0x14

/* --- Register HW_BCH_FLASH3LAYOUT0, field GF13_0_GF14_1 */

#define BP_BCH_FLASH3LAYOUT0_GF13_0_GF14_1      10
#define BM_BCH_FLASH3LAYOUT0_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH3LAYOUT0_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH3LAYOUT0_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT0_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH3LAYOUT0, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH3LAYOUT0, field DATA0_SIZE */

#define BP_BCH_FLASH3LAYOUT0_DATA0_SIZE      0
#define BM_BCH_FLASH3LAYOUT0_DATA0_SIZE      0x000003FF

#define BF_BCH_FLASH3LAYOUT0_DATA0_SIZE(v)   (((v) << 0) & BM_BCH_FLASH3LAYOUT0_DATA0_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT0_DATA0_SIZE(v)   BF_CS1(BCH_FLASH3LAYOUT0, DATA0_SIZE, v)
#endif

/*
 * HW_BCH_FLASH3LAYOUT1 - Hardware BCH ECC Flash 3 Layout 1 Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DATAN_SIZE:10;
        unsigned GF13_0_GF14_1:1;
        unsigned ECCN:5;
        unsigned PAGE_SIZE:16;
    } B;
} hw_bch_flash3layout1_t;
#endif

/*
 * constants & macros for entire HW_BCH_FLASH3LAYOUT1 register
 */
#define HW_BCH_FLASH3LAYOUT1_ADDR      (0x001140f0)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_FLASH3LAYOUT1           (*(volatile hw_bch_flash3layout1_t *) HW_BCH_FLASH3LAYOUT1_ADDR)
#define HW_BCH_FLASH3LAYOUT1_RD()      (HW_BCH_FLASH3LAYOUT1.U)
#define HW_BCH_FLASH3LAYOUT1_WR(v)     (HW_BCH_FLASH3LAYOUT1.U = (v))
#define HW_BCH_FLASH3LAYOUT1_SET(v)    (HW_BCH_FLASH3LAYOUT1_WR(HW_BCH_FLASH3LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH3LAYOUT1_CLR(v)    (HW_BCH_FLASH3LAYOUT1_WR(HW_BCH_FLASH3LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH3LAYOUT1_TOG(v)    (HW_BCH_FLASH3LAYOUT1_WR(HW_BCH_FLASH3LAYOUT1_RD() ^  (v)))
#else
#define HW_BCH_FLASH3LAYOUT1_RD()      (_rbase->mem32_read(HW_BCH_FLASH3LAYOUT1_ADDR))
#define HW_BCH_FLASH3LAYOUT1_WR(v)     (_rbase->mem32_write(HW_BCH_FLASH3LAYOUT1_ADDR,(v)))
#define HW_BCH_FLASH3LAYOUT1_SET(v)    (HW_BCH_FLASH3LAYOUT1_WR(HW_BCH_FLASH3LAYOUT1_RD() |  (v)))
#define HW_BCH_FLASH3LAYOUT1_CLR(v)    (HW_BCH_FLASH3LAYOUT1_WR(HW_BCH_FLASH3LAYOUT1_RD() & ~(v)))
#define HW_BCH_FLASH3LAYOUT1_TOG(v)    (HW_BCH_FLASH3LAYOUT1_WR(HW_BCH_FLASH3LAYOUT1_RD() ^  (v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_FLASH3LAYOUT1 bitfields
 */
/* --- Register HW_BCH_FLASH3LAYOUT1, field PAGE_SIZE */

#define BP_BCH_FLASH3LAYOUT1_PAGE_SIZE      16
#define BM_BCH_FLASH3LAYOUT1_PAGE_SIZE      0xFFFF0000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_FLASH3LAYOUT1_PAGE_SIZE(v)   ((((reg32_t) v) << 16) & BM_BCH_FLASH3LAYOUT1_PAGE_SIZE)
#else
#define BF_BCH_FLASH3LAYOUT1_PAGE_SIZE(v)   (((v) << 16) & BM_BCH_FLASH3LAYOUT1_PAGE_SIZE)
#endif
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT1_PAGE_SIZE(v)   (HW_BCH_FLASH3LAYOUT1.B.PAGE_SIZE = (v))
#endif

/* --- Register HW_BCH_FLASH3LAYOUT1, field ECCN */

#define BP_BCH_FLASH3LAYOUT1_ECCN      11
#define BM_BCH_FLASH3LAYOUT1_ECCN      0x0000F800

#define BF_BCH_FLASH3LAYOUT1_ECCN(v)   (((v) << 11) & BM_BCH_FLASH3LAYOUT1_ECCN)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT1_ECCN(v)   BF_CS1(BCH_FLASH3LAYOUT1, ECCN, v)
#endif

#define BV_BCH_FLASH3LAYOUT1_ECCN__NONE   0x0
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC2   0x1
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC4   0x2
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC6   0x3
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC8   0x4
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC10  0x5
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC12  0x6
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC14  0x7
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC16  0x8
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC18  0x9
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC20  0xA
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC22  0xB
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC24  0xC
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC26  0xD
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC28  0xE
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC30  0xF
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC32  0x10
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC34  0x11
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC36  0x12
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC38  0x13
#define BV_BCH_FLASH3LAYOUT1_ECCN__ECC40  0x14

/* --- Register HW_BCH_FLASH3LAYOUT1, field GF13_0_GF14_1 */

#define BP_BCH_FLASH3LAYOUT1_GF13_0_GF14_1      10
#define BM_BCH_FLASH3LAYOUT1_GF13_0_GF14_1      0x00000400

#define BF_BCH_FLASH3LAYOUT1_GF13_0_GF14_1(v)   (((v) << 10) & BM_BCH_FLASH3LAYOUT1_GF13_0_GF14_1)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT1_GF13_0_GF14_1(v)   BF_CS1(BCH_FLASH3LAYOUT1, GF13_0_GF14_1, v)
#endif

/* --- Register HW_BCH_FLASH3LAYOUT1, field DATAN_SIZE */

#define BP_BCH_FLASH3LAYOUT1_DATAN_SIZE      0
#define BM_BCH_FLASH3LAYOUT1_DATAN_SIZE      0x000003FF

#define BF_BCH_FLASH3LAYOUT1_DATAN_SIZE(v)   (((v) << 0) & BM_BCH_FLASH3LAYOUT1_DATAN_SIZE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_FLASH3LAYOUT1_DATAN_SIZE(v)   BF_CS1(BCH_FLASH3LAYOUT1, DATAN_SIZE, v)
#endif

/*
 * HW_BCH_DEBUG0 - Hardware BCH ECC Debug Register0
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned DEBUG_REG_SELECT:6;
        unsigned RSVD0:2;
        unsigned BM_KES_TEST_BYPASS:1;
        unsigned KES_DEBUG_STALL:1;
        unsigned KES_DEBUG_STEP:1;
        unsigned KES_STANDALONE:1;
        unsigned KES_DEBUG_KICK:1;
        unsigned KES_DEBUG_MODE4K:1;
        unsigned KES_DEBUG_PAYLOAD_FLAG:1;
        unsigned KES_DEBUG_SHIFT_SYND:1;
        unsigned KES_DEBUG_SYNDROME_SYMBOL:9;
        unsigned RSVD1:7;
    } B;
} hw_bch_debug0_t;
#endif

/*
 * constants & macros for entire HW_BCH_DEBUG0 register
 */
#define HW_BCH_DEBUG0_ADDR      (0x00114100)
#define HW_BCH_DEBUG0_SET_ADDR  (0x00114104)
#define HW_BCH_DEBUG0_CLR_ADDR  (0x00114108)
#define HW_BCH_DEBUG0_TOG_ADDR  (0x0011410c)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_DEBUG0           (*(volatile hw_bch_debug0_t *) HW_BCH_DEBUG0_ADDR)
#define HW_BCH_DEBUG0_RD()      (HW_BCH_DEBUG0.U)
#define HW_BCH_DEBUG0_WR(v)     (HW_BCH_DEBUG0.U = (v))
#define HW_BCH_DEBUG0_SET(v)    ((*(volatile reg32_t *) HW_BCH_DEBUG0_SET_ADDR) = (v))
#define HW_BCH_DEBUG0_CLR(v)    ((*(volatile reg32_t *) HW_BCH_DEBUG0_CLR_ADDR) = (v))
#define HW_BCH_DEBUG0_TOG(v)    ((*(volatile reg32_t *) HW_BCH_DEBUG0_TOG_ADDR) = (v))
#else
#define HW_BCH_DEBUG0_RD()      (_rbase->mem32_read(HW_BCH_DEBUG0_ADDR))
#define HW_BCH_DEBUG0_WR(v)     (_rbase->mem32_write(HW_BCH_DEBUG0_ADDR,(v)))
#define HW_BCH_DEBUG0_SET(v)    (_rbase->mem32_write(HW_BCH_DEBUG0_SET_ADDR,(v)))
#define HW_BCH_DEBUG0_CLR(v)    (_rbase->mem32_write(HW_BCH_DEBUG0_CLR_ADDR,(v)))
#define HW_BCH_DEBUG0_TOG(v)    (_rbase->mem32_write(HW_BCH_DEBUG0_TOG_ADDR,(v)))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_DEBUG0 bitfields
 */
/* --- Register HW_BCH_DEBUG0, field RSVD1 */

#define BP_BCH_DEBUG0_RSVD1      25
#define BM_BCH_DEBUG0_RSVD1      0xFE000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_DEBUG0_RSVD1(v)   ((((reg32_t) v) << 25) & BM_BCH_DEBUG0_RSVD1)
#else
#define BF_BCH_DEBUG0_RSVD1(v)   (((v) << 25) & BM_BCH_DEBUG0_RSVD1)
#endif
/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_SYNDROME_SYMBOL */

#define BP_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL      16
#define BM_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL      0x01FF0000

#define BF_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL(v)   (((v) << 16) & BM_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_SYNDROME_SYMBOL, v)
#endif

#define BV_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL__NORMAL     0x0
#define BV_BCH_DEBUG0_KES_DEBUG_SYNDROME_SYMBOL__TEST_MODE  0x1

/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_SHIFT_SYND */

#define BP_BCH_DEBUG0_KES_DEBUG_SHIFT_SYND      15
#define BM_BCH_DEBUG0_KES_DEBUG_SHIFT_SYND      0x00008000

#define BF_BCH_DEBUG0_KES_DEBUG_SHIFT_SYND(v)   (((v) << 15) & BM_BCH_DEBUG0_KES_DEBUG_SHIFT_SYND)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_SHIFT_SYND(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_SHIFT_SYND, v)
#endif

/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_PAYLOAD_FLAG */

#define BP_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG      14
#define BM_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG      0x00004000

#define BF_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG(v)   (((v) << 14) & BM_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_PAYLOAD_FLAG, v)
#endif

#define BV_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG__DATA  0x1
#define BV_BCH_DEBUG0_KES_DEBUG_PAYLOAD_FLAG__AUX   0x1

/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_MODE4K */

#define BP_BCH_DEBUG0_KES_DEBUG_MODE4K      13
#define BM_BCH_DEBUG0_KES_DEBUG_MODE4K      0x00002000

#define BF_BCH_DEBUG0_KES_DEBUG_MODE4K(v)   (((v) << 13) & BM_BCH_DEBUG0_KES_DEBUG_MODE4K)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_MODE4K(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_MODE4K, v)
#endif

#define BV_BCH_DEBUG0_KES_DEBUG_MODE4K__4k  0x1
#define BV_BCH_DEBUG0_KES_DEBUG_MODE4K__2k  0x1

/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_KICK */

#define BP_BCH_DEBUG0_KES_DEBUG_KICK      12
#define BM_BCH_DEBUG0_KES_DEBUG_KICK      0x00001000

#define BF_BCH_DEBUG0_KES_DEBUG_KICK(v)   (((v) << 12) & BM_BCH_DEBUG0_KES_DEBUG_KICK)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_KICK(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_KICK, v)
#endif

/* --- Register HW_BCH_DEBUG0, field KES_STANDALONE */

#define BP_BCH_DEBUG0_KES_STANDALONE      11
#define BM_BCH_DEBUG0_KES_STANDALONE      0x00000800

#define BF_BCH_DEBUG0_KES_STANDALONE(v)   (((v) << 11) & BM_BCH_DEBUG0_KES_STANDALONE)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_STANDALONE(v)   BF_CS1(BCH_DEBUG0, KES_STANDALONE, v)
#endif

#define BV_BCH_DEBUG0_KES_STANDALONE__NORMAL     0x0
#define BV_BCH_DEBUG0_KES_STANDALONE__TEST_MODE  0x1

/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_STEP */

#define BP_BCH_DEBUG0_KES_DEBUG_STEP      10
#define BM_BCH_DEBUG0_KES_DEBUG_STEP      0x00000400

#define BF_BCH_DEBUG0_KES_DEBUG_STEP(v)   (((v) << 10) & BM_BCH_DEBUG0_KES_DEBUG_STEP)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_STEP(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_STEP, v)
#endif

/* --- Register HW_BCH_DEBUG0, field KES_DEBUG_STALL */

#define BP_BCH_DEBUG0_KES_DEBUG_STALL      9
#define BM_BCH_DEBUG0_KES_DEBUG_STALL      0x00000200

#define BF_BCH_DEBUG0_KES_DEBUG_STALL(v)   (((v) << 9) & BM_BCH_DEBUG0_KES_DEBUG_STALL)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_KES_DEBUG_STALL(v)   BF_CS1(BCH_DEBUG0, KES_DEBUG_STALL, v)
#endif

#define BV_BCH_DEBUG0_KES_DEBUG_STALL__NORMAL  0x0
#define BV_BCH_DEBUG0_KES_DEBUG_STALL__WAIT    0x1

/* --- Register HW_BCH_DEBUG0, field BM_KES_TEST_BYPASS */

#define BP_BCH_DEBUG0_BM_KES_TEST_BYPASS      8
#define BM_BCH_DEBUG0_BM_KES_TEST_BYPASS      0x00000100

#define BF_BCH_DEBUG0_BM_KES_TEST_BYPASS(v)   (((v) << 8) & BM_BCH_DEBUG0_BM_KES_TEST_BYPASS)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_BM_KES_TEST_BYPASS(v)   BF_CS1(BCH_DEBUG0, BM_KES_TEST_BYPASS, v)
#endif

#define BV_BCH_DEBUG0_BM_KES_TEST_BYPASS__NORMAL     0x0
#define BV_BCH_DEBUG0_BM_KES_TEST_BYPASS__TEST_MODE  0x1

/* --- Register HW_BCH_DEBUG0, field RSVD0 */

#define BP_BCH_DEBUG0_RSVD0      6
#define BM_BCH_DEBUG0_RSVD0      0x000000C0

#define BF_BCH_DEBUG0_RSVD0(v)   (((v) << 6) & BM_BCH_DEBUG0_RSVD0)
/* --- Register HW_BCH_DEBUG0, field DEBUG_REG_SELECT */

#define BP_BCH_DEBUG0_DEBUG_REG_SELECT      0
#define BM_BCH_DEBUG0_DEBUG_REG_SELECT      0x0000003F

#define BF_BCH_DEBUG0_DEBUG_REG_SELECT(v)   (((v) << 0) & BM_BCH_DEBUG0_DEBUG_REG_SELECT)
#ifndef __LANGUAGE_ASM__
#define BW_BCH_DEBUG0_DEBUG_REG_SELECT(v)   BF_CS1(BCH_DEBUG0, DEBUG_REG_SELECT, v)
#endif

/*
 * HW_BCH_DBGKESREAD - KES Debug Read Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned VALUES:32;
    } B;
} hw_bch_dbgkesread_t;
#endif

/*
 * constants & macros for entire HW_BCH_DBGKESREAD register
 */
#define HW_BCH_DBGKESREAD_ADDR      (0x00114110)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_DBGKESREAD           (*(volatile hw_bch_dbgkesread_t *) HW_BCH_DBGKESREAD_ADDR)
#define HW_BCH_DBGKESREAD_RD()      (HW_BCH_DBGKESREAD.U)
#else
#define HW_BCH_DBGKESREAD_RD()      (_rbase->mem32_read(HW_BCH_DBGKESREAD_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_DBGKESREAD bitfields
 */
/* --- Register HW_BCH_DBGKESREAD, field VALUES */

#define BP_BCH_DBGKESREAD_VALUES      0
#define BM_BCH_DBGKESREAD_VALUES      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_DBGKESREAD_VALUES(v)   ((reg32_t) v)
#else
#define BF_BCH_DBGKESREAD_VALUES(v)   (v)
#endif

/*
 * HW_BCH_DBGCSFEREAD - Chien Search Debug Read Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned VALUES:32;
    } B;
} hw_bch_dbgcsferead_t;
#endif

/*
 * constants & macros for entire HW_BCH_DBGCSFEREAD register
 */
#define HW_BCH_DBGCSFEREAD_ADDR      (0x00114120)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_DBGCSFEREAD           (*(volatile hw_bch_dbgcsferead_t *) HW_BCH_DBGCSFEREAD_ADDR)
#define HW_BCH_DBGCSFEREAD_RD()      (HW_BCH_DBGCSFEREAD.U)
#else
#define HW_BCH_DBGCSFEREAD_RD()      (_rbase->mem32_read(HW_BCH_DBGCSFEREAD_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_DBGCSFEREAD bitfields
 */
/* --- Register HW_BCH_DBGCSFEREAD, field VALUES */

#define BP_BCH_DBGCSFEREAD_VALUES      0
#define BM_BCH_DBGCSFEREAD_VALUES      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_DBGCSFEREAD_VALUES(v)   ((reg32_t) v)
#else
#define BF_BCH_DBGCSFEREAD_VALUES(v)   (v)
#endif

/*
 * HW_BCH_DBGSYNDGENREAD - Syndrome Generator Debug Read Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned VALUES:32;
    } B;
} hw_bch_dbgsyndgenread_t;
#endif

/*
 * constants & macros for entire HW_BCH_DBGSYNDGENREAD register
 */
#define HW_BCH_DBGSYNDGENREAD_ADDR      (0x00114130)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_DBGSYNDGENREAD           (*(volatile hw_bch_dbgsyndgenread_t *) HW_BCH_DBGSYNDGENREAD_ADDR)
#define HW_BCH_DBGSYNDGENREAD_RD()      (HW_BCH_DBGSYNDGENREAD.U)
#else
#define HW_BCH_DBGSYNDGENREAD_RD()      (_rbase->mem32_read(HW_BCH_DBGSYNDGENREAD_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_DBGSYNDGENREAD bitfields
 */
/* --- Register HW_BCH_DBGSYNDGENREAD, field VALUES */

#define BP_BCH_DBGSYNDGENREAD_VALUES      0
#define BM_BCH_DBGSYNDGENREAD_VALUES      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_DBGSYNDGENREAD_VALUES(v)   ((reg32_t) v)
#else
#define BF_BCH_DBGSYNDGENREAD_VALUES(v)   (v)
#endif

/*
 * HW_BCH_DBGAHBMREAD - Bus Master and ECC Controller Debug Read Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned VALUES:32;
    } B;
} hw_bch_dbgahbmread_t;
#endif

/*
 * constants & macros for entire HW_BCH_DBGAHBMREAD register
 */
#define HW_BCH_DBGAHBMREAD_ADDR      (0x00114140)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_DBGAHBMREAD           (*(volatile hw_bch_dbgahbmread_t *) HW_BCH_DBGAHBMREAD_ADDR)
#define HW_BCH_DBGAHBMREAD_RD()      (HW_BCH_DBGAHBMREAD.U)
#else
#define HW_BCH_DBGAHBMREAD_RD()      (_rbase->mem32_read(HW_BCH_DBGAHBMREAD_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_DBGAHBMREAD bitfields
 */
/* --- Register HW_BCH_DBGAHBMREAD, field VALUES */

#define BP_BCH_DBGAHBMREAD_VALUES      0
#define BM_BCH_DBGAHBMREAD_VALUES      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_DBGAHBMREAD_VALUES(v)   ((reg32_t) v)
#else
#define BF_BCH_DBGAHBMREAD_VALUES(v)   (v)
#endif

/*
 * HW_BCH_BLOCKNAME - Block Name Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned NAME:32;
    } B;
} hw_bch_blockname_t;
#endif

/*
 * constants & macros for entire HW_BCH_BLOCKNAME register
 */
#define HW_BCH_BLOCKNAME_ADDR      (0x00114150)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_BLOCKNAME           (*(volatile hw_bch_blockname_t *) HW_BCH_BLOCKNAME_ADDR)
#define HW_BCH_BLOCKNAME_RD()      (HW_BCH_BLOCKNAME.U)
#else
#define HW_BCH_BLOCKNAME_RD()      (_rbase->mem32_read(HW_BCH_BLOCKNAME_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_BLOCKNAME bitfields
 */
/* --- Register HW_BCH_BLOCKNAME, field NAME */

#define BP_BCH_BLOCKNAME_NAME      0
#define BM_BCH_BLOCKNAME_NAME      0xFFFFFFFF

#ifndef __LANGUAGE_ASM__
#define BF_BCH_BLOCKNAME_NAME(v)   ((reg32_t) v)
#else
#define BF_BCH_BLOCKNAME_NAME(v)   (v)
#endif

/*
 * HW_BCH_VERSION - BCH Version Register
 */
#ifndef __LANGUAGE_ASM__
typedef union {
    reg32_t U;
    struct {
        unsigned STEP:16;
        unsigned MINOR:8;
        unsigned MAJOR:8;
    } B;
} hw_bch_version_t;
#endif

/*
 * constants & macros for entire HW_BCH_VERSION register
 */
#define HW_BCH_VERSION_ADDR      (0x00114160)

#ifndef __LANGUAGE_ASM__
#ifndef ROCOO_TEST
#define HW_BCH_VERSION           (*(volatile hw_bch_version_t *) HW_BCH_VERSION_ADDR)
#define HW_BCH_VERSION_RD()      (HW_BCH_VERSION.U)
#else
#define HW_BCH_VERSION_RD()      (_rbase->mem32_read(HW_BCH_VERSION_ADDR))
#endif
#endif

/*
 * constants & macros for individual HW_BCH_VERSION bitfields
 */
/* --- Register HW_BCH_VERSION, field MAJOR */

#define BP_BCH_VERSION_MAJOR      24
#define BM_BCH_VERSION_MAJOR      0xFF000000

#ifndef __LANGUAGE_ASM__
#define BF_BCH_VERSION_MAJOR(v)   ((((reg32_t) v) << 24) & BM_BCH_VERSION_MAJOR)
#else
#define BF_BCH_VERSION_MAJOR(v)   (((v) << 24) & BM_BCH_VERSION_MAJOR)
#endif
/* --- Register HW_BCH_VERSION, field MINOR */

#define BP_BCH_VERSION_MINOR      16
#define BM_BCH_VERSION_MINOR      0x00FF0000

#define BF_BCH_VERSION_MINOR(v)   (((v) << 16) & BM_BCH_VERSION_MINOR)
/* --- Register HW_BCH_VERSION, field STEP */

#define BP_BCH_VERSION_STEP      0
#define BM_BCH_VERSION_STEP      0x0000FFFF

#define BF_BCH_VERSION_STEP(v)   (((v) << 0) & BM_BCH_VERSION_STEP)

#endif /* _BCH_H */

////////////////////////////////////////////////////////////////////////////////
