/*
 * @brief IOH Architecture B mnemonics
 *
 * @note
 * Copyright 2014, 2019, NXP
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef FSL_SMARTDMA_PRV_H_
#define FSL_SMARTDMA_PRV_H_

#include "fsl_common.h"

#define SMARTDMA_INPUT_SOURCE_0 0
#define SMARTDMA_INPUT_SOURCE_1 1
#define SMARTDMA_INPUT_SOURCE_2 2
#define SMARTDMA_INPUT_SOURCE_3 3
#define SMARTDMA_INPUT_SOURCE_4 4
#define SMARTDMA_INPUT_SOURCE_5 5
#define SMARTDMA_INPUT_SOURCE_6 6
#define SMARTDMA_INPUT_SOURCE_7 7

#define BS0(c) (c << 8)
#define BS1(c) (c << 11)
#define BS2(c) (c << 14)
#define BS3(c) (c << 17)
#define BS4(c) (c << 20)
#define BS5(c) (c << 23)
#define BS6(c) (c << 26)
#define BS7(c) (c << 29)

#define SMARTDMA_DISABLE_EMERGENCY_BIT 8

#define SMARTDMA_HANDSHAKE_EVENT  0
#define SMARTDMA_HANDSHAKE_ENABLE 1

#define SMARTDMA_MASK_RESP       2
#define SMARTDMA_ENABLE_AHBBUF   3
#define SMARTDMA_ENABLE_GPISYNCH 4

typedef enum
{
    ezh_trap_low  = 1,
    ezh_trap_high = 0
} trap_pol;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                      SMARTDMA ARCH B */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define R0  0x00
#define R1  0x01
#define R2  0x02
#define R3  0x03
#define R4  0x04
#define R5  0x05
#define R6  0x06
#define R7  0x07
#define GPO 0x08
#define GPD 0x09
#define CFS 0x0a
#define CFM 0x0b
#define SP  0x0c
#define PC  0x0d
#define GPI 0x0e
#define RA  0x0f

/* Conditional Flags */
#define EU  0x0
#define ZE  0x1
#define NZ  0x2
#define PO  0x3
#define NE  0x4
#define AZ  0x5
#define ZB  0x6
#define CA  0x7
#define NC  0x8
#define CZ  0x9
#define SPO 0xa
#define SNE 0xb
#define NBS 0xc
#define NEX 0xd
#define BS  0xe
#define EX  0xf

#define UNS 0xa
#define NZS 0xb

#define VECT0 0x1
#define VECT1 0x2
#define VECT2 0x4
#define VECT3 0x8
#define VECT4 0x10
#define VECT5 0x20
#define VECT6 0x40
#define VECT7 0x80

/* Bit Slice Mux cfg */

#define BS_1      0
#define BS_RISE   1
#define BS_FALL   2
#define BS_CHANGE 3
#define BS_SIG    4
#define BS_SIGN   5
#define BS_0      6
#define BS_EVENT  7

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                      Unconditional OpCodes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define E_GOSUB(a30)       DCD 0x03 + a30
#define E_NOP              DCD 0x12
#define E_INT_TRIGGER(x24) DCD 0x14 + (x24 << 8)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_GOTO */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* the pre-processor/linker will calculate it this way (<< relative not allowed) */
#define E_GOTO(a21)                                                                                                 \
    DCD 0x15 + (1 << 9) + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21

#define E_GOTO_REG(raddr) DCD 0x15 + (raddr << 14)

/* the pre-processor/linker will calculate it this way (<< relative not allowed) */
#define E_GOTOL(a21)                                                                                                \
    DCD 0x15 + (1 << 10) + (1 << 9) + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21

#define E_GOTO_REGL(raddr) DCD 0x15 + (raddr << 14) + (1 << 10)

#define E_COND_GOTO(cond, a21)                                                                                        \
    DCD 0x15 + (cond << 5) + (1 << 9) + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21

#define E_COND_GOTO_REG(cond, raddr) DCD 0x15 + (raddr << 14) + (cond << 5)

/* the pre-processor/linker will calculate it this way (<< relative not allowed) */
#define E_COND_GOTOL(cond, a21)                                                                                       \
    DCD 0x15 + (1 << 10) + (cond << 5) + (1 << 9) + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 +   \
        a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21 + a21

#define E_COND_GOTO_REGL(cond, raddr) DCD 0x15 + (raddr << 14) + (1 << 10) + (cond << 5)
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_MOV */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define E_MOV(dest, source)             DCD 0x0 + (source << 14) + (dest << 10) + (EU << 5)
#define E_MOVS(dest, source)            DCD 0x0 + (source << 14) + (dest << 10) + (1 << 9) + (EU << 5)
#define E_COND_MOV(cond, dest, source)  DCD 0x0 + (source << 14) + (dest << 10) + (cond << 5)
#define E_COND_MOVS(cond, dest, source) DCD 0x0 + (source << 14) + (dest << 10) + (1 << 9) + (cond << 5)

/* Invert */
#define E_MVN(dest, source)             DCD 0x0 + (source << 14) + (dest << 10) + (EU << 5) + (1 << 31)
#define E_MVNS(dest, source)            DCD 0x0 + (source << 14) + (dest << 10) + (1 << 9) + (EU << 5) + (1 << 31)
#define E_COND_MVN(cond, dest, source)  DCD 0x0 + (source << 14) + (dest << 10) + (cond << 5) + (1 << 31)
#define E_COND_MVNS(cond, dest, source) DCD 0x0 + (source << 14) + (dest << 10) + (1 << 9) + (cond << 5) + (1 << 31)

/* Load  Immediate */
#define E_LOAD_IMM(dest, imm11s)            DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5)
#define E_LOAD_IMMS(dest, imm11s)           DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5)
#define E_COND_LOAD_IMM(cond, dest, imm11s) DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5)
#define E_COND_LOAD_IMMS(cond, dest, imm11s) \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5)

/* Load Shifted Immediate */
#define E_LOAD_SIMM(dest, imm11s, sam)                                                                \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19)
#define E_LOAD_SIMMS(dest, imm11s, sam)                                                                          \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19)
#define E_COND_LOAD_SIMM(cond, dest, imm11s, sam)                                                       \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19)
#define E_COND_LOAD_SIMMS(cond, dest, imm11s, sam)                                                                 \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19)

/* Load  Inverted Immediate */
#define E_LOAD_IMMN(dest, imm11s) DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5) + (1 << 31)
#define E_LOAD_IMMNS(dest, imm11s) \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5) + (1 << 31)
#define E_COND_LOAD_IMMN(cond, dest, imm11s) \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5) + (1 << 31)
#define E_COND_LOAD_IMMNS(cond, dest, imm11s) \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5) + (1 << 31)

/* Load Shifted then inverted Immediate */
#define E_LOAD_SIMMN(dest, imm11s, sam)                                                               \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (EU << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19) + (1 << 31)
#define E_LOAD_SIMMNS(dest, imm11s, sam)                                                                         \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (EU << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19) + (1 << 31)
#define E_COND_LOAD_SIMMN(cond, dest, imm11s, sam)                                                      \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (cond << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19) + (1 << 31)
#define E_COND_LOAD_SIMMNS(cond, dest, imm11s, sam)                                                                \
    DCD 0x0 + (dest << 10) + ((imm11s & 0x7ff) << 20) + (1 << 18) + (1 << 9) + (cond << 5) + ((sam & 0xf) << 14) + \
        (((sam & 0x10) >> 4) << 19) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_AHB_READ Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                        opcode    Ptr PostIncrement (0 means pre-inc)   Rdata Dest */
/*                                                        Pointer       WData Source        Offset UpdatePointer */
/*                                                        SizeWord    Signed Access  Cond */

/* LDR (Load, Load Byte, LoadByteSigned) */
#define E_LDR(dest, source, offset8s)                                                                            \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (1 << 18) + (0 << 21) + \
        (EU << 5)
#define E_LDRB(dest, source, offset8s)                                                                           \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (0 << 21) + \
        (EU << 5)
#define E_LDRBS(dest, source, offset8s)                                                                          \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (1 << 21) + \
        (EU << 5)

/* Conditional LDR (Load, Load Byte, LoadByteSigned) */
#define E_COND_LDR(cond, dest, source, offset8s)                                                                 \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (1 << 18) + (0 << 21) + \
        (cond << 5)
#define E_COND_LDRB(cond, dest, source, offset8s)                                                                \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (0 << 21) + \
        (cond << 5)
#define E_COND_LDRBS(cond, dest, source, offset8s)                                                               \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (0 << 20) + (0 << 18) + (1 << 21) + \
        (cond << 5)

/* With Update Pointer */
#define E_LDR_PRE(dest, source, offset8s)                                                                        \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + \
        (EU << 5)
#define E_LDRB_PRE(dest, source, offset8s)                                                                       \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + \
        (EU << 5)
#define E_LDRBS_PRE(dest, source, offset8s)                                                                      \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + \
        (EU << 5)
#define E_COND_LDR_PRE(cond, dest, source, offset8s)                                                             \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + \
        (cond << 5)
#define E_COND_LDRB_PRE(cond, dest, source, offset8s)                                                            \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + \
        (cond << 5)
#define E_COND_LDRBS_PRE(cond, dest, source, offset8s)                                                           \
    DCD 0x1 + (0 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + \
        (cond << 5)

/* With Update Pointer (Post Increment pointer) */
#define E_LDR_POST(dest, source, offset8s)                                                                       \
    DCD 0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + \
        (EU << 5)
#define E_LDRB_POST(dest, source, offset8s)                                                                      \
    DCD 0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + \
        (EU << 5)
#define E_LDRBS_POST(dest, source, offset8s)                                                                     \
    DCD 0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + \
        (EU << 5)
#define E_COND_LDR_POST(cond, dest, source, offset8s)                                                            \
    DCD 0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (1 << 18) + (0 << 21) + \
        (cond << 5)
#define E_COND_LDRB_POST(cond, dest, source, offset8s)                                                           \
    DCD 0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (0 << 21) + \
        (cond << 5)
#define E_COND_LDRBS_POST(cond, dest, source, offset8s)                                                          \
    DCD 0x1 + (1 << 19) + (dest << 10) + (source << 14) + (offset8s << 24) + (1 << 20) + (0 << 18) + (1 << 21) + \
        (cond << 5)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_AHB_WRITE Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                       opcode    Ptr PostIncrement (0 means pre-inc)   Rdata Dest */
/*                                                       Pointer       WData Source        offset8s UpdatePointer */
/*                                                       SizeWord    Signed Access  Cond */

/* STR (Load, Load Byte, LoadByteSigned) */
#define E_STR(raddr, rdata, offset8s)                                                                            \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (1 << 18) + (0 << 11) + \
        (EU << 5)
#define E_STRB(raddr, rdata, offset8s)                                                                           \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (0 << 18) + (0 << 11) + \
        (EU << 5)

/* Conditional STR (Load, Load Byte, LoadByteSigned) */
#define E_COND_STR(cond, raddr, rdata, offset8s)                                                                 \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (1 << 18) + (0 << 11) + \
        (cond << 5)
#define E_COND_STRB(cond, raddr, rdata, offset8s)                                                                \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (0 << 10) + (0 << 18) + (0 << 11) + \
        (cond << 5)

/* With Update Pointer */
#define E_STR_PRE(raddr, rdata, offset8s)                                                                        \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + \
        (EU << 5)
#define E_STRB_PRE(raddr, rdata, offset8s)                                                                       \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + \
        (EU << 5)
#define E_COND_STR_PRE(cond, raddr, rdata, offset8s)                                                             \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + \
        (cond << 5)
#define E_COND_STRB_PRE(cond, raddr, rdata, offset8s)                                                            \
    DCD 0x2 + (0 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + \
        (cond << 5)

/* With Update Pointer (Post Increment pointer) */
#define E_STR_POST(raddr, rdata, offset8s)                                                                       \
    DCD 0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + \
        (EU << 5)
#define E_STRB_POST(raddr, rdata, offset8s)                                                                      \
    DCD 0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + \
        (EU << 5)
#define E_COND_STR_POST(cond, raddr, rdata, offset8s)                                                            \
    DCD 0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (1 << 18) + (0 << 11) + \
        (cond << 5)
#define E_COND_STRB_POST(cond, raddr, rdata, offset8s)                                                           \
    DCD 0x2 + (1 << 19) + (raddr << 14) + (rdata << 20) + (offset8s << 24) + (1 << 10) + (0 << 18) + (0 << 11) + \
        (cond << 5)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                      Stack Operations (built up from E_LDR and E_STR codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                       opcode    Ptr PostIncrement (0 means pre-inc)   Rdata Dest */
/*                                                       Pointer       WData Source        Offset          UpdatePointer
 */
/*                                                       SizeWord    Signed Access  Cond */

#define E_PUSH(source) \
    DCD 0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (EU << 5)
#define E_POP(dest) \
    DCD 0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (EU << 5)
#define E_PUSHB(source) \
    DCD 0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (EU << 5)
#define E_POPB(dest) \
    DCD 0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (EU << 5)

#define E_POPBS(dest) \
    DCD 0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (EU << 5)

#define E_COND_PUSH(cond, source) \
    DCD 0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (1 << 18) + (0 << 11) + (cond << 5)
#define E_COND_POP(cond, dest) \
    DCD 0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (1 << 18) + (0 << 21) + (cond << 5)
#define E_COND_PUSHB(cond, source) \
    DCD 0x2 + (1 << 19) + (SP << 14) + (source << 20) + (1 << 24) + (1 << 10) + (0 << 18) + (0 << 11) + (cond << 5)
#define E_COND_POPB(cond, dest) \
    DCD 0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (0 << 21) + (cond << 5)

#define E_COND_POPBS(cond, dest) \
    DCD 0x1 + (0 << 19) + (dest << 10) + (SP << 14) + ((-1) << 24) + (1 << 20) + (0 << 18) + (1 << 21) + (cond << 5)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_PER_READ Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest       Address                        Cond */

#define E_PER_READ(dest, addr20)            DCD 0x4 + (dest << 10) + ((addr20 & 0x000ffffc) << 12) + (EU << 5)
#define E_COND_PER_READ(cond, dest, addr20) DCD 0x4 + (dest << 10) + ((addr20 & 0x000ffffc) << 12) + (cond << 5)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_PER_WRITE Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest       Address                        Cond */

#define E_PER_WRITE(source, addr20) \
    DCD 0x5 + (source << 20) + ((addr20 & 0x000ff000) << 12) + ((addr20 & 0x00000ffc) << 8) + (EU << 5)
#define E_COND_PER_WRITE(cond, source, addr20) \
    DCD 0x5 + (source << 20) + ((addr20 & 0x000ff000) << 12) + ((addr20 & 0x00000ffc) << 8) + (cond << 5)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_ADD Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result       Shift Amount
 */
/*                                                         Shift/Rotate    Left/Right   Flip */

/* Add reg to reg */
#define E_ADD(dest, src1, src2)            DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_ADDS(dest, src1, src2)           DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_ADD(cond, dest, src1, src2) DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_ADDS(cond, dest, src1, src2) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* Add reg to reg and invert result */
#define E_ADDN(dest, src1, src2) DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_ADDNS(dest, src1, src2) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_ADDN(cond, dest, src1, src2) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_ADDNS(cond, dest, src1, src2) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* Add imm12s to reg */
#define E_ADD_IMM(dest, src1, imm12s) DCD 0x6 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_ADD_IMMS(dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_ADD_IMM(cond, dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_ADD_IMMS(cond, dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* Add imm12s to reg and invert result */
#define E_ADDN_IMM(dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_ADDN_IMMS(dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ADDN_IMM(cond, dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ADDN_IMMS(cond, dest, src1, imm12s) \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* Add reg to reg with Post Shift Left */
#define E_ADD_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_ADD_LSLS(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADD_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_ADD_LSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* Add reg to reg and invert result with Post Shift Left */
#define E_ADDN_LSL(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_ADDN_LSLS(dest, src1, src2, shift5)                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADDN_LSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADDN_LSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* Add reg to reg with Post Shift Right */
#define E_ADD_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_ADD_LSRS(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADD_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_ADD_LSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* Add reg to reg and invert result with Post Shift Right */
#define E_ADDN_LSR(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_ADDN_LSRS(dest, src1, src2, shift5)                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADDN_LSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADDN_LSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* Add reg to reg with Post Arith Shift Right */
#define E_ADD_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_ADD_ASRS(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADD_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_ADD_ASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* Add reg to reg and invert result with Post Arith Shift Right */
#define E_ADDN_ASR(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_ADDN_ASRS(dest, src1, src2, shift5)                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADDN_ASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADDN_ASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* Add reg to reg with Post ROR */
#define E_ADD_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_ADD_RORS(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADD_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_ADD_RORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* Add reg to reg and invert result with ROR */
#define E_ADDN_ROR(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_ADDN_RORS(dest, src1, src2, shift5)                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADDN_ROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADDN_RORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)

/* Add reg to reg with Flip */
#define E_ADD_F(dest, src1, src2)                                                                                   \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_ADD_FS(dest, src1, src2)                                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADD_F(cond, dest, src1, src2)                                                                          \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_ADD_FS(cond, dest, src1, src2)                                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* Add reg to reg and invert result with Flip */
#define E_ADDN_F(dest, src1, src2)                                                                                  \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ADDN_FS(dest, src1, src2)                                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADDN_F(cond, dest, src1, src2)                                                                         \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADDN_FS(cond, dest, src1, src2)                                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* Add reg to reg with Post Shift Left */
#define E_ADD_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ADD_FLSLS(dest, src1, src2, shift5)                                                               \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADD_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADD_FLSLS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* Add reg to reg and invert result with Post Shift Left */
#define E_ADDN_FLSL(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_ADDN_FLSLS(dest, src1, src2, shift5)                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADDN_FLSL(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADDN_FLSLS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* Add reg to reg with Post Shift Right */
#define E_ADD_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_ADD_FLSRS(dest, src1, src2, shift5)                                                               \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADD_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_ADD_FLSRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* Add reg to reg and invert result with Post Shift Right */
#define E_ADDN_FLSR(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_ADDN_FLSRS(dest, src1, src2, shift5)                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADDN_FLSR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADDN_FLSRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* Add reg to reg with Post Arith Shift Right */
#define E_ADD_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ADD_FASRS(dest, src1, src2, shift5)                                                               \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADD_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADD_FASRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* Add reg to reg and invert result with Post Arith Shift Right */
#define E_ADDN_FASR(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_ADDN_FASRS(dest, src1, src2, shift5)                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADDN_FASR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADDN_FASRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* Add reg to reg with Post ROR */
#define E_ADD_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_ADD_FRORS(dest, src1, src2, shift5)                                                               \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADD_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_ADD_FRORS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* Add reg to reg and invert result with ROR */
#define E_ADDN_FROR(dest, src1, src2, shift5)                                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_ADDN_FRORS(dest, src1, src2, shift5)                                                \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADDN_FROR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADDN_FRORS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x6 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_SUB Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result    Shift Result */

/* sub reg from reg */
#define E_SUB(dest, src1, src2)            DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_SUBS(dest, src1, src2)           DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_SUB(cond, dest, src1, src2) DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_SUBS(cond, dest, src1, src2) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* sub reg from reg and invert result */
#define E_SUBN(dest, src1, src2) DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_SUBNS(dest, src1, src2) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_SUBN(cond, dest, src1, src2) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_SUBNS(cond, dest, src1, src2) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* sub imm12s from reg */
#define E_SUB_IMM(dest, src1, imm12s) DCD 0x8 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_SUB_IMMS(dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_SUB_IMM(cond, dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_SUB_IMMS(cond, dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* sub imm12s from reg and invert result */
#define E_SUBN_IMM(dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_SUBN_IMMS(dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_SUBN_IMM(cond, dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_SUBN_IMMS(cond, dest, src1, imm12s) \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* SUB reg to reg with Post Shift Left */
#define E_SUB_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_SUB_LSLS(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SUB_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_SUB_LSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* SUB reg to reg and invert result with Post Shift Left */
#define E_SUBN_LSL(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_SUBN_LSLS(dest, src1, src2, shift5)                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SUBN_LSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SUBN_LSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* SUB reg to reg with Post Shift Right */
#define E_SUB_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_SUB_LSRS(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SUB_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_SUB_LSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* SUB reg to reg and invert result with Post Shift Right */
#define E_SUBN_LSR(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_SUBN_LSRS(dest, src1, src2, shift5)                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SUBN_LSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SUBN_LSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* SUB reg to reg with Post Arith Shift Right */
#define E_SUB_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_SUB_ASRS(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SUB_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_SUB_ASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* SUB reg to reg and invert result with Post Arith Shift Right */
#define E_SUBN_ASR(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_SUBN_ASRS(dest, src1, src2, shift5)                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SUBN_ASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SUBN_ASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* SUB reg to reg with Post ROR */
#define E_SUB_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_SUB_RORS(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SUB_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_SUB_RORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* SUB reg to reg and invert result with ROR */
#define E_SUBN_ROR(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_SUBN_RORS(dest, src1, src2, shift5)                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SUBN_ROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SUBN_RORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)

/* Flip Endianness and then shift5/Rotate */

/* Sub reg to reg with Flip */
#define E_SUB_F(dest, src1, src2)                                                                                   \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_SUB_FS(dest, src1, src2)                                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SUB_F(cond, dest, src1, src2)                                                                          \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_SUB_FS(cond, dest, src1, src2)                                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* Sub reg to reg and invert result with Flip */
#define E_SUBN_F(dest, src1, src2)                                                                                  \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_SUBN_FS(dest, src1, src2)                                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUBN_F(cond, dest, src1, src2)                                                                         \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SUBN_FS(cond, dest, src1, src2)                                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* SUB reg to reg with Post Shift Left */
#define E_SUB_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_SUB_FLSLS(dest, src1, src2, shift5)                                                               \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUB_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SUB_FLSLS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* SUB reg to reg and invert result with Post Shift Left */
#define E_SUBN_FLSL(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_SUBN_FLSLS(dest, src1, src2, shift5)                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUBN_FLSL(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUBN_FLSLS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* SUB reg to reg with Post Shift Right */
#define E_SUB_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_SUB_FLSRS(dest, src1, src2, shift5)                                                               \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SUB_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_SUB_FLSRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* SUB reg to reg and invert result with Post Shift Right */
#define E_SUBN_FLSR(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_SUBN_FLSRS(dest, src1, src2, shift5)                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SUBN_FLSR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SUBN_FLSRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* SUB reg to reg with Post Arith Shift Right */
#define E_SUB_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_SUB_FASRS(dest, src1, src2, shift5)                                                               \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUB_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SUB_FASRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* SUB reg to reg and invert result with Post Arith Shift Right */
#define E_SUBN_FASR(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_SUBN_FASRS(dest, src1, src2, shift5)                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUBN_FASR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SUBN_FASRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* SUB reg to reg with Post ROR */
#define E_SUB_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_SUB_FRORS(dest, src1, src2, shift5)                                                               \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SUB_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_SUB_FRORS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* SUB reg to reg and invert result with ROR */
#define E_SUBN_FROR(dest, src1, src2, shift5)                                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_SUBN_FRORS(dest, src1, src2, shift5)                                                \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SUBN_FROR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SUBN_FRORS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x8 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_ADC Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result    Shift Result */

/* carry add reg from reg */
#define E_ADC(dest, src1, src2)            DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_ADCS(dest, src1, src2)           DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_ADC(cond, dest, src1, src2) DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_ADCS(cond, dest, src1, src2) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* carry add reg from reg and invert result */
#define E_ADCN(dest, src1, src2) DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_ADCNS(dest, src1, src2) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_ADCN(cond, dest, src1, src2) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_ADCNS(cond, dest, src1, src2) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* carry add imm12s from reg */
#define E_ADC_IMM(dest, src1, imm12s) DCD 0x9 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_ADC_IMMS(dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_ADC_IMM(cond, dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_ADC_IMMS(cond, dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* carry add imm12s from reg and invert result */
#define E_ADCN_IMM(dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_ADCN_IMMS(dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ADCN_IMM(cond, dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ADCN_IMMS(cond, dest, src1, imm12s) \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* ADC reg to reg with Post Shift Left */
#define E_ADC_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_ADC_LSLS(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADC_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_ADC_LSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* ADC reg to reg and invert result with Post Shift Left */
#define E_ADCN_LSL(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_ADCN_LSLS(dest, src1, src2, shift5)                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADCN_LSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADCN_LSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* ADC reg to reg with Post Shift Right */
#define E_ADC_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_ADC_LSRS(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADC_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_ADC_LSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* ADC reg to reg and invert result with Post Shift Right */
#define E_ADCN_LSR(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_ADCN_LSRS(dest, src1, src2, shift5)                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADCN_LSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADCN_LSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* ADC reg to reg with Post Arith Shift Right */
#define E_ADC_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_ADC_ASRS(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADC_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_ADC_ASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* ADC reg to reg and invert result with Post Arith Shift Right */
#define E_ADCN_ASR(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_ADCN_ASRS(dest, src1, src2, shift5)                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADCN_ASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ADCN_ASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* ADC reg to reg with Post ROR */
#define E_ADC_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_ADC_RORS(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADC_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_ADC_RORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* ADC reg to reg and invert result with ROR */
#define E_ADCN_ROR(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_ADCN_RORS(dest, src1, src2, shift5)                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADCN_ROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ADCN_RORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)

/* Flip Endianness and then shift5/Rotate */

/* adc reg to reg with Flip */
#define E_ADC_F(dest, src1, src2)                                                                                   \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_ADC_FS(dest, src1, src2)                                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADC_F(cond, dest, src1, src2)                                                                          \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_ADC_FS(cond, dest, src1, src2)                                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* ADC reg to reg and invert result with Flip */
#define E_ADCN_F(dest, src1, src2)                                                                                  \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ADCN_FS(dest, src1, src2)                                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADCN_F(cond, dest, src1, src2)                                                                         \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADCN_FS(cond, dest, src1, src2)                                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* ADC reg to reg with Post Shift Left */
#define E_ADC_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ADC_FLSLS(dest, src1, src2, shift5)                                                               \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADC_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADC_FLSLS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* ADC reg to reg and invert result with Post Shift Left */
#define E_ADCN_FLSL(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_ADCN_FLSLS(dest, src1, src2, shift5)                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADCN_FLSL(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADCN_FLSLS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* ADC reg to reg with Post Shift Right */
#define E_ADC_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_ADC_FLSRS(dest, src1, src2, shift5)                                                               \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADC_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_ADC_FLSRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* ADC reg to reg and invert result with Post Shift Right */
#define E_ADCN_FLSR(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_ADCN_FLSRS(dest, src1, src2, shift5)                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADCN_FLSR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADCN_FLSRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* ADC reg to reg with Post Arith Shift Right */
#define E_ADC_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ADC_FASRS(dest, src1, src2, shift5)                                                               \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADC_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ADC_FASRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* ADC reg to reg and invert result with Post Arith Shift Right */
#define E_ADCN_FASR(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_ADCN_FASRS(dest, src1, src2, shift5)                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADCN_FASR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ADCN_FASRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* ADC reg to reg with Post ROR */
#define E_ADC_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_ADC_FRORS(dest, src1, src2, shift5)                                                               \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADC_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_ADC_FRORS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* ADC reg to reg and invert result with ROR */
#define E_ADCN_FROR(dest, src1, src2, shift5)                                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_ADCN_FRORS(dest, src1, src2, shift5)                                                \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADCN_FROR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ADCN_FRORS(cond, dest, src1, src2, shift5)                                       \
    DCD 0x9 + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_SBC Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result    Shift Result */

/* carry sub reg from reg */
#define E_SBC(dest, src1, src2)            DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_SBCS(dest, src1, src2)           DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_SBC(cond, dest, src1, src2) DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_SBCS(cond, dest, src1, src2) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* carry sub reg from reg and invert result */
#define E_SBCN(dest, src1, src2) DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_SBCNS(dest, src1, src2) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_SBCN(cond, dest, src1, src2) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_SBCNS(cond, dest, src1, src2) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* carry sub imm12s from reg */
#define E_SBC_IMM(dest, src1, imm12s) DCD 0xA + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_SBC_IMMS(dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_SBC_IMM(cond, dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_SBC_IMMS(cond, dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* carry sub imm12s from reg and invert result */
#define E_SBCN_IMM(dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_SBCN_IMMS(dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_SBCN_IMM(cond, dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_SBCN_IMMS(cond, dest, src1, imm12s) \
    DCD 0xA + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* SBC reg to reg with Post Shift Left */
#define E_SBC_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_SBC_LSLS(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SBC_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_SBC_LSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* SBC reg to reg and invert result with Post Shift Left */
#define E_SBCN_LSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_SBCN_LSLS(dest, src1, src2, shift5)                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SBCN_LSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SBCN_LSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* SBC reg to reg with Post Shift Right */
#define E_SBC_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_SBC_LSRS(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SBC_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_SBC_LSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* SBC reg to reg and invert result with Post Shift Right */
#define E_SBCN_LSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_SBCN_LSRS(dest, src1, src2, shift5)                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SBCN_LSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SBCN_LSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* SBC reg to reg with Post Arith Shift Right */
#define E_SBC_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_SBC_ASRS(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SBC_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_SBC_ASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* SBC reg to reg and invert result with Post Arith Shift Right */
#define E_SBCN_ASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_SBCN_ASRS(dest, src1, src2, shift5)                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SBCN_ASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_SBCN_ASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* SBC reg to reg with Post ROR */
#define E_SBC_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_SBC_RORS(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SBC_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_SBC_RORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* SBC reg to reg and invert result with ROR */
#define E_SBCN_ROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_SBCN_RORS(dest, src1, src2, shift5)                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SBCN_ROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_SBCN_RORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)

/* Flip Endianness and then shift5/Rotate */

/* SBC reg to reg with Flip */
#define E_SBC_F(dest, src1, src2)                                                                                   \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_SBC_FS(dest, src1, src2)                                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SBC_F(cond, dest, src1, src2)                                                                          \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_SBC_FS(cond, dest, src1, src2)                                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* SBC reg to reg and invert result with Flip */
#define E_SBCN_F(dest, src1, src2)                                                                                  \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_SBCN_FS(dest, src1, src2)                                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBCN_F(cond, dest, src1, src2)                                                                         \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SBCN_FS(cond, dest, src1, src2)                                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* SBC reg to reg with Post Shift Left */
#define E_SBC_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_SBC_FLSLS(dest, src1, src2, shift5)                                                               \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBC_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SBC_FLSLS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* SBC reg to reg and invert result with Post Shift Left */
#define E_SBCN_FLSL(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_SBCN_FLSLS(dest, src1, src2, shift5)                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBCN_FLSL(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBCN_FLSLS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* SBC reg to reg with Post Shift Right */
#define E_SBC_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_SBC_FLSRS(dest, src1, src2, shift5)                                                               \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SBC_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_SBC_FLSRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* SBC reg to reg and invert result with Post Shift Right */
#define E_SBCN_FLSR(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_SBCN_FLSRS(dest, src1, src2, shift5)                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SBCN_FLSR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SBCN_FLSRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* SBC reg to reg with Post Arith Shift Right */
#define E_SBC_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_SBC_FASRS(dest, src1, src2, shift5)                                                               \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBC_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_SBC_FASRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* SBC reg to reg and invert result with Post Arith Shift Right */
#define E_SBCN_FASR(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_SBCN_FASRS(dest, src1, src2, shift5)                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBCN_FASR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_SBCN_FASRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* SBC reg to reg with Post ROR */
#define E_SBC_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_SBC_FRORS(dest, src1, src2, shift5)                                                               \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SBC_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_SBC_FRORS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* SBC reg to reg and invert result with ROR */
#define E_SBCN_FROR(dest, src1, src2, shift5)                                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_SBCN_FRORS(dest, src1, src2, shift5)                                                \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SBCN_FROR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_SBCN_FRORS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xA + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_OR Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result    Shift Result */

/* or reg with reg */
#define E_OR(dest, src1, src2)             DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_ORS(dest, src1, src2)            DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_OR(cond, dest, src1, src2)  DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_ORS(cond, dest, src1, src2) DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* or reg with reg and invert result */
#define E_ORN(dest, src1, src2)  DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_ORNS(dest, src1, src2) DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_ORN(cond, dest, src1, src2) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_ORNS(cond, dest, src1, src2) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* or imm12s with reg */
#define E_OR_IMM(dest, src1, imm12s) DCD 0xC + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_OR_IMMS(dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_OR_IMM(cond, dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_OR_IMMS(cond, dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* or imm12s with reg and invert result */
#define E_ORN_IMM(dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_ORN_IMMS(dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ORN_IMM(cond, dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ORN_IMMS(cond, dest, src1, imm12s) \
    DCD 0xC + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* OR reg to reg with Post Shift Left */
#define E_OR_LSL(dest, src1, src2, shift5)                                                                   \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_OR_LSLS(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_OR_LSL(cond, dest, src1, src2, shift5)                                                          \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_OR_LSLS(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* OR reg to reg and invert result with Post Shift Left */
#define E_ORN_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_ORN_LSLS(dest, src1, src2, shift5)                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ORN_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ORN_LSLS(cond, dest, src1, src2, shift5)                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* OR reg to reg with Post Shift Right */
#define E_OR_LSR(dest, src1, src2, shift5)                                                                   \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_OR_LSRS(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_OR_LSR(cond, dest, src1, src2, shift5)                                                          \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_OR_LSRS(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* OR reg to reg and invert result with Post Shift Right */
#define E_ORN_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_ORN_LSRS(dest, src1, src2, shift5)                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ORN_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ORN_LSRS(cond, dest, src1, src2, shift5)                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* OR reg to reg with Post Arith Shift Right */
#define E_OR_ASR(dest, src1, src2, shift5)                                                                   \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_OR_ASRS(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_OR_ASR(cond, dest, src1, src2, shift5)                                                          \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_OR_ASRS(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* OR reg to reg and invert result with Post Arith Shift Right */
#define E_ORN_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_ORN_ASRS(dest, src1, src2, shift5)                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ORN_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ORN_ASRS(cond, dest, src1, src2, shift5)                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* OR reg to reg with Post ROR */
#define E_OR_ROR(dest, src1, src2, shift5)                                                                   \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_OR_RORS(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_OR_ROR(cond, dest, src1, src2, shift5)                                                          \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_OR_RORS(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* OR reg to reg and invert result with ROR */
#define E_ORN_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_ORN_RORS(dest, src1, src2, shift5)                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ORN_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ORN_RORS(cond, dest, src1, src2, shift5)                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
/* Flip Endianness and then shift5/Rotate */

/* OR reg to reg with Flip */
#define E_OR_F(dest, src1, src2)                                                                                    \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_OR_FS(dest, src1, src2)                                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_OR_F(cond, dest, src1, src2)                                                                           \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_OR_FS(cond, dest, src1, src2)                                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* OR reg to reg and invert result with Flip */
#define E_ORN_F(dest, src1, src2)                                                                                   \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ORN_FS(dest, src1, src2)                                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ORN_F(cond, dest, src1, src2)                                                                          \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ORN_FS(cond, dest, src1, src2)                                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* OR reg to reg with Post Shift Left */
#define E_OR_FLSL(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_OR_FLSLS(dest, src1, src2, shift5)                                                                \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_OR_FLSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_OR_FLSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* OR reg to reg and invert result with Post Shift Left */
#define E_ORN_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_ORN_FLSLS(dest, src1, src2, shift5)                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ORN_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ORN_FLSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* OR reg to reg with Post Shift Right */
#define E_OR_FLSR(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_OR_FLSRS(dest, src1, src2, shift5)                                                                \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_OR_FLSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_OR_FLSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* OR reg to reg and invert result with Post Shift Right */
#define E_ORN_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_ORN_FLSRS(dest, src1, src2, shift5)                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ORN_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ORN_FLSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* OR reg to reg with Post Arith Shift Right */
#define E_OR_FASR(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_OR_FASRS(dest, src1, src2, shift5)                                                                \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_OR_FASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_OR_FASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* OR reg to reg and invert result with Post Arith Shift Right */
#define E_ORN_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_ORN_FASRS(dest, src1, src2, shift5)                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ORN_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ORN_FASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* OR reg to reg with Post ROR */
#define E_OR_FROR(dest, src1, src2, shift5)                                                                  \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_OR_FRORS(dest, src1, src2, shift5)                                                                \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_OR_FROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_OR_FRORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* OR reg to reg and invert result with ROR */
#define E_ORN_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_ORN_FRORS(dest, src1, src2, shift5)                                                 \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ORN_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ORN_FRORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xC + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_AND Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result    Shift Result */

/* AND reg with reg */
#define E_AND(dest, src1, src2)            DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_ANDS(dest, src1, src2)           DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_AND(cond, dest, src1, src2) DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_ANDS(cond, dest, src1, src2) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* AND reg with reg and invert result */
#define E_ANDN(dest, src1, src2) DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_ANDNS(dest, src1, src2) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_ANDN(cond, dest, src1, src2) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_ANDNS(cond, dest, src1, src2) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* AND imm12s with reg */
#define E_AND_IMM(dest, src1, imm12s) DCD 0xd + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_AND_IMMS(dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_AND_IMM(cond, dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_AND_IMMS(cond, dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* AND imm12s with reg and invert result */
#define E_ANDN_IMM(dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_ANDN_IMMS(dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ANDN_IMM(cond, dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_ANDN_IMMS(cond, dest, src1, imm12s) \
    DCD 0xd + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* AND reg to reg with Post Shift Left */
#define E_AND_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_AND_LSLS(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_AND_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_AND_LSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* AND reg to reg and invert result with Post Shift Left */
#define E_ANDN_LSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_ANDN_LSLS(dest, src1, src2, shift5)                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ANDN_LSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ANDN_LSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* AND reg to reg with Post Shift Right */
#define E_AND_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_AND_LSRS(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_AND_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_AND_LSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* AND reg to reg and invert result with Post Shift Right */
#define E_ANDN_LSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_ANDN_LSRS(dest, src1, src2, shift5)                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ANDN_LSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ANDN_LSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* AND reg to reg with Post Arith Shift Right */
#define E_AND_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_AND_ASRS(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_AND_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_AND_ASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* AND reg to reg and invert result with Post Arith Shift Right */
#define E_ANDN_ASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_ANDN_ASRS(dest, src1, src2, shift5)                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ANDN_ASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_ANDN_ASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* AND reg to reg with Post ROR */
#define E_AND_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_AND_RORS(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_AND_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_AND_RORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* AND reg to reg and invert result with ROR */
#define E_ANDN_ROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_ANDN_RORS(dest, src1, src2, shift5)                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ANDN_ROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_ANDN_RORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)

/* Flip Endianness and then shift5/Rotate */

/* AND reg to reg with Flip */
#define E_AND_F(dest, src1, src2)                                                                                   \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_AND_FS(dest, src1, src2)                                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_AND_F(cond, dest, src1, src2)                                                                          \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_AND_FS(cond, dest, src1, src2)                                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* AND reg to reg and invert result with Flip */
#define E_ANDN_F(dest, src1, src2)                                                                                  \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_ANDN_FS(dest, src1, src2)                                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ANDN_F(cond, dest, src1, src2)                                                                         \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_ANDN_FS(cond, dest, src1, src2)                                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* AND reg to reg with Post Shift Left */
#define E_AND_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_AND_FLSLS(dest, src1, src2, shift5)                                                               \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_AND_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_AND_FLSLS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* AND reg to reg and invert result with Post Shift Left */
#define E_ANDN_FLSL(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_ANDN_FLSLS(dest, src1, src2, shift5)                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ANDN_FLSL(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ANDN_FLSLS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* AND reg to reg with Post Shift Right */
#define E_AND_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_AND_FLSRS(dest, src1, src2, shift5)                                                               \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_AND_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_AND_FLSRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* AND reg to reg and invert result with Post Shift Right */
#define E_ANDN_FLSR(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_ANDN_FLSRS(dest, src1, src2, shift5)                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ANDN_FLSR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ANDN_FLSRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* AND reg to reg with Post Arith Shift Right */
#define E_AND_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_AND_FASRS(dest, src1, src2, shift5)                                                               \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_AND_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_AND_FASRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* AND reg to reg and invert result with Post Arith Shift Right */
#define E_ANDN_FASR(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_ANDN_FASRS(dest, src1, src2, shift5)                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ANDN_FASR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_ANDN_FASRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* AND reg to reg with Post ROR */
#define E_AND_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_AND_FRORS(dest, src1, src2, shift5)                                                               \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_AND_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_AND_FRORS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* AND reg to reg and invert result with ROR */
#define E_ANDN_FROR(dest, src1, src2, shift5)                                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_ANDN_FRORS(dest, src1, src2, shift5)                                                \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ANDN_FROR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_ANDN_FRORS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xd + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_XOR Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm            Use_Imm      Invert Result    Shift Result */

/* XOR reg with reg */
#define E_XOR(dest, src1, src2)            DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5)
#define E_XORS(dest, src1, src2)           DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5)
#define E_COND_XOR(cond, dest, src1, src2) DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5)
#define E_COND_XORS(cond, dest, src1, src2) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5)

/* XOR reg with reg XOR invert result */
#define E_XORN(dest, src1, src2) DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19)
#define E_XORNS(dest, src1, src2) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19)
#define E_COND_XORN(cond, dest, src1, src2) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19)
#define E_COND_XORNS(cond, dest, src1, src2) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19)

/* XOR imm12s with reg */
#define E_XOR_IMM(dest, src1, imm12s) DCD 0xe + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_XOR_IMMS(dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_XOR_IMM(cond, dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18)
#define E_COND_XOR_IMMS(cond, dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18)

/* XOR imm12s with reg XOR invert result */
#define E_XORN_IMM(dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_XORN_IMMS(dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (EU << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_XORN_IMM(cond, dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)
#define E_COND_XORN_IMMS(cond, dest, src1, imm12s) \
    DCD 0xe + (dest << 10) + (src1 << 14) + (1 << 9) + (cond << 5) + (imm12s << 20) + (1 << 18) + (1 << 19)

/* XOR reg to reg with Post Shift Left */
#define E_XOR_LSL(dest, src1, src2, shift5)                                                                  \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_XOR_LSLS(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_XOR_LSL(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_XOR_LSLS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)

/* XOR reg to reg XOR invert result with Post Shift Left */
#define E_XORN_LSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_XORN_LSLS(dest, src1, src2, shift5)                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_XORN_LSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (0 << 31)
#define E_COND_XORN_LSLS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (0 << 31)

/* XOR reg to reg with Post Shift Right */
#define E_XOR_LSR(dest, src1, src2, shift5)                                                                  \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_XOR_LSRS(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_XOR_LSR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_XOR_LSRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)

/* XOR reg to reg XOR invert result with Post Shift Right */
#define E_XORN_LSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_XORN_LSRS(dest, src1, src2, shift5)                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_XORN_LSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (0 << 31)
#define E_COND_XORN_LSRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (0 << 31)

/* XOR reg to reg with Post Arith Shift Right */
#define E_XOR_ASR(dest, src1, src2, shift5)                                                                  \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_XOR_ASRS(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_XOR_ASR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (0 << 31)
#define E_COND_XOR_ASRS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)

/* XOR reg to reg XOR invert result with Post Arith Shift Right */
#define E_XORN_ASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_XORN_ASRS(dest, src1, src2, shift5)                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_XORN_ASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (0 << 31)
#define E_COND_XORN_ASRS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (0 << 31)

/* XOR reg to reg with Post ROR */
#define E_XOR_ROR(dest, src1, src2, shift5)                                                                  \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_XOR_RORS(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_XOR_ROR(cond, dest, src1, src2, shift5)                                                         \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (0 << 31)
#define E_COND_XOR_RORS(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)

/* XOR reg to reg XOR invert result with ROR */
#define E_XORN_ROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_XORN_RORS(dest, src1, src2, shift5)                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_XORN_ROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (0 << 31)
#define E_COND_XORN_RORS(cond, dest, src1, src2, shift5)                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (0 << 31)

/* Flip Endianness and then shift5/Rotate */

/* XOR reg to reg with Flip */
#define E_XOR_F(dest, src1, src2)                                                                                   \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_XOR_FS(dest, src1, src2)                                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_XOR_F(cond, dest, src1, src2)                                                                          \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + (0 << 30) + \
        (1 << 31)
#define E_COND_XOR_FS(cond, dest, src1, src2)                                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)

/* XOR reg to reg and invert result with Flip */
#define E_XORN_F(dest, src1, src2)                                                                                  \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_XORN_FS(dest, src1, src2)                                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XORN_F(cond, dest, src1, src2)                                                                         \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_XORN_FS(cond, dest, src1, src2)                                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + ((0 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* XOR reg to reg with Post Shift Left */
#define E_XOR_FLSL(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_XOR_FLSLS(dest, src1, src2, shift5)                                                               \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XOR_FLSL(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_XOR_FLSLS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)

/* XOR reg to reg XOR invert result with Post Shift Left */
#define E_XORN_FLSL(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_XORN_FLSLS(dest, src1, src2, shift5)                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XORN_FLSL(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XORN_FLSLS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (0 << 30) + (1 << 31)

/* XOR reg to reg with Post Shift Right */
#define E_XOR_FLSR(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_XOR_FLSRS(dest, src1, src2, shift5)                                                               \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_XOR_FLSR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_XOR_FLSRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)

/* XOR reg to reg XOR invert result with Post Shift Right */
#define E_XORN_FLSR(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_XORN_FLSRS(dest, src1, src2, shift5)                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_XORN_FLSR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (0 << 29) + (1 << 30) + (1 << 31)
#define E_COND_XORN_FLSRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (0 << 29) + (1 << 30) + (1 << 31)

/* XOR reg to reg with Post Arith Shift Right */
#define E_XOR_FASR(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_XOR_FASRS(dest, src1, src2, shift5)                                                               \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XOR_FASR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (0 << 30) + (1 << 31)
#define E_COND_XOR_FASRS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)

/* XOR reg to reg XOR invert result with Post Arith Shift Right */
#define E_XORN_FASR(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_XORN_FASRS(dest, src1, src2, shift5)                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XORN_FASR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 30) + (1 << 31)
#define E_COND_XORN_FASRS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (0 << 30) + (1 << 31)

/* XOR reg to reg with Post ROR */
#define E_XOR_FROR(dest, src1, src2, shift5)                                                                 \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_XOR_FRORS(dest, src1, src2, shift5)                                                               \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_XOR_FROR(cond, dest, src1, src2, shift5)                                                        \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + ((shift5 & 0x1f) << 24) + (1 << 29) + \
        (1 << 30) + (1 << 31)
#define E_COND_XOR_FRORS(cond, dest, src1, src2, shift5)                                                      \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)

/* XOR reg to reg XOR invert result with ROR */
#define E_XORN_FROR(dest, src1, src2, shift5)                                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (EU << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_XORN_FRORS(dest, src1, src2, shift5)                                                \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (EU << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_XORN_FROR(cond, dest, src1, src2, shift5)                                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (cond << 5) + (1 << 19) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 30) + (1 << 31)
#define E_COND_XORN_FRORS(cond, dest, src1, src2, shift5)                                       \
    DCD 0xe + (dest << 10) + (src1 << 14) + (src2 << 20) + (1 << 9) + (cond << 5) + (1 << 19) + \
        ((shift5 & 0x1f) << 24) + (1 << 29) + (1 << 30) + (1 << 31)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_Shift Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                    Extra Operation */
/*                                                         Left/Right   Shift/Rotate */

/* Logical Shift */
#define E_LSL(dest, r2shift, shift5)                                                                         \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_LSR(dest, r2shift, shift5)                                                                         \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag */
#define E_LSLS(dest, r2shift, shift5)                                                                        \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_LSRS(dest, r2shift, shift5)                                                                        \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)

/* Logical Shift and then AND */
#define E_LSL_AND(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_AND(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then AND */
#define E_LSL_ANDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_ANDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then OR */
#define E_LSL_OR(dest, roperand, r2shift, shift5)                                                                   \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_OR(dest, roperand, r2shift, shift5)                                                                   \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then OR */
#define E_LSL_ORS(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_ORS(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then XOR */
#define E_LSL_XOR(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_XOR(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then XOR */
#define E_LSL_XORS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_XORS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADD */
#define E_LSL_ADD(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_ADD(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADD */
#define E_LSL_ADDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_ADDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SUB */
#define E_LSL_SUB(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_SUB(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SUB */
#define E_LSL_SUBS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_SUBS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADC */
#define E_LSL_ADC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_ADC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADC */
#define E_LSL_ADCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_ADCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SBC */
#define E_LSL_SBC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_SBC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SBC */
#define E_LSL_SBCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_LSR_SBCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)

/* Conditional */
/* Logical Shift */
#define E_COND_LSL(cond, dest, r2shift, shift5)                                                                \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_COND_LSR(cond, dest, r2shift, shift5)                                                                \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag */
#define E_COND_LSLS(cond, dest, r2shift, shift5)                                                               \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_COND_LSRS(cond, dest, r2shift, shift5)                                                               \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)

/* Logical Shift and then AND */
#define E_COND_LSL_AND(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_AND(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then AND */
#define E_COND_LSL_ANDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_ANDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then OR */
#define E_COND_LSL_OR(cond, dest, roperand, r2shift, shift5)                                                          \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_OR(cond, dest, roperand, r2shift, shift5)                                                          \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then OR */
#define E_COND_LSL_ORS(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_ORS(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then XOR */
#define E_COND_LSL_XOR(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_XOR(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then XOR */
#define E_COND_LSL_XORS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_XORS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADD */
#define E_COND_LSL_ADD(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_ADD(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADD */
#define E_COND_LSL_ADDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_ADDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SUB */
#define E_COND_LSL_SUB(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_SUB(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SUB */
#define E_COND_LSL_SUBS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_SUBS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADC */
#define E_COND_LSL_ADC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_ADC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADC */
#define E_COND_LSL_ADCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_ADCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SBC */
#define E_COND_LSL_SBC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_SBC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SBC */
#define E_COND_LSL_SBCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_COND_LSR_SBCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_ROTATE Codes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Left/Right
 */
/*                                                         Shift/Rotate */

/* Rotate */
#define E_ROR(dest, r2shift, shift5)                                                                         \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)
/* Rotate and Set Flag */
#define E_RORS(dest, r2shift, shift5)                                                                        \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)

/* Rotate and then AND */
#define E_ROR_AND(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then AND */
#define E_ROR_ANDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then OR */
#define E_ROR_OR(dest, roperand, r2shift, shift5)                                                                   \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then OR */
#define E_ROR_ORS(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then XOR */
#define E_ROR_XOR(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then XOR */
#define E_ROR_XORS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADD */
#define E_ROR_ADD(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADD */
#define E_ROR_ADDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SUB */
#define E_ROR_SUB(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SUB */
#define E_ROR_SUBS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADC */
#define E_ROR_ADC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADC */
#define E_ROR_ADCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SBC */
#define E_ROR_SBC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SBC */
#define E_ROR_SBCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)

/* Conditional */
/* Rotate */
#define E_COND_ROR(cond, dest, r2shift, shift5)                                                                \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)
/* Rotate and Set Flag */
#define E_COND_RORS(cond, dest, r2shift, shift5)                                                               \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)

/* Rotate and then AND */
#define E_COND_ROR_AND(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then AND */
#define E_COND_ROR_ANDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then OR */
#define E_COND_ROR_OR(cond, dest, roperand, r2shift, shift5)                                                          \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then OR */
#define E_COND_ROR_ORS(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then XOR */
#define E_COND_ROR_XOR(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then XOR */
#define E_COND_ROR_XORS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADD */
#define E_COND_ROR_ADD(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADD */
#define E_COND_ROR_ADDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SUB */
#define E_COND_ROR_SUB(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SUB */
#define E_COND_ROR_SUBS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADC */
#define E_COND_ROR_ADC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADC */
#define E_COND_ROR_ADCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SBC */
#define E_COND_ROR_SBC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SBC */
#define E_COND_ROR_SBCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Arithmetical Shift Codes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Left/Right
 */
/*                                                         Shift/Rotate  Arith/Shift */

/* Arith Shift Right */
#define E_ASR(dest, r2shift, shift5)                                                                         \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag */
#define E_ASRS(dest, r2shift, shift5)                                                                        \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)

/* Arith Shift Right and then AND */
#define E_ASR_AND(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then AND */
#define E_ASR_ANDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then OR */
#define E_ASR_OR(dest, roperand, r2shift, shift5)                                                                   \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then OR */
#define E_ASR_ORS(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then XOR */
#define E_ASR_XOR(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then XOR */
#define E_ASR_XORS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then ADD */
#define E_ASR_ADD(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then ADD */
#define E_ASR_ADDS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then SUB */
#define E_ASR_SUB(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then SUB */
#define E_ASR_SUBS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then ADC */
#define E_ASR_ADC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then ADC */
#define E_ASR_ADCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then SBC */
#define E_ASR_SBC(dest, roperand, r2shift, shift5)                                                                  \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then SBC */
#define E_ASR_SBCS(dest, roperand, r2shift, shift5)                                                                 \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)

/* Conditional */
/* Conditional Arith Shift */
#define E_COND_ASR(cond, dest, r2shift, shift5)                                                                \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag */
#define E_COND_ASRS(cond, dest, r2shift, shift5)                                                               \
    DCD 0x10 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then AND */
#define E_COND_ASR_AND(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then AND */
#define E_COND_ASR_ANDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then OR */
#define E_COND_ASR_OR(cond, dest, roperand, r2shift, shift5)                                                          \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then OR */
#define E_COND_ASR_ORS(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then XOR */
#define E_COND_ASR_XOR(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then XOR */
#define E_COND_ASR_XORS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then ADD */
#define E_COND_ASR_ADD(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then ADD */
#define E_COND_ASR_ADDS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then SUB */
#define E_COND_ASR_SUB(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then SUB */
#define E_COND_ASR_SUBS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then ADC */
#define E_COND_ASR_ADC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then ADC */
#define E_COND_ASR_ADCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then SBC */
#define E_COND_ASR_SBC(cond, dest, roperand, r2shift, shift5)                                                         \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then SBC */
#define E_COND_ASR_SBCS(cond, dest, roperand, r2shift, shift5)                                                        \
    DCD 0x10 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Flip Opcodes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Endian/bit
 */
/*                                                         ARITH  Arith/Shift */

/* Flip Endian , ASR Right */
#define E_FEND_ASR(dest, r2shift, shift5)                                                                    \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag */
#define E_FEND_ASRS(dest, r2shift, shift5)                                                                   \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , AND */
#define E_FEND_ASR_AND(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then AND */
#define E_FEND_ASR_ANDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , OR */
#define E_FEND_ASR_OR(dest, roperand, r2shift, shift5)                                                              \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then OR */
#define E_FEND_ASR_ORS(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , XOR */
#define E_FEND_ASR_XOR(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then XOR */
#define E_FEND_ASR_XORS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , ADD */
#define E_FEND_ASR_ADD(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then ADD */
#define E_FEND_ASR_ADDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , SUB */
#define E_FEND_ASR_SUB(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then SUB */
#define E_FEND_ASR_SUBS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , ADC */
#define E_FEND_ASR_ADC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then ADC */
#define E_FEND_ASR_ADCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (1 << 19)

/* Flip Endian , ASR Right , SBC */
#define E_FEND_ASR_SBC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (1 << 19)
/* Flip Endian , ASR Right ,Set Flag then SBC */
#define E_FEND_ASR_SBCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (1 << 19)

/* Conditional */
/* Conditional Flip Endian , ASR */
#define E_COND_FEND_ASR(cond, dest, r2shift, shift5)                                                           \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag */
#define E_COND_FEND_ASRS(cond, dest, r2shift, shift5)                                                          \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , AND */
#define E_COND_FEND_ASR_AND(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then AND */
#define E_COND_FEND_ASR_ANDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , OR */
#define E_COND_FEND_ASR_OR(cond, dest, roperand, r2shift, shift5)                                                     \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then OR */
#define E_COND_FEND_ASR_ORS(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , XOR */
#define E_COND_FEND_ASR_XOR(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then XOR */
#define E_COND_FEND_ASR_XORS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , ADD */
#define E_COND_FEND_ASR_ADD(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then ADD */
#define E_COND_FEND_ASR_ADDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , SUB */
#define E_COND_FEND_ASR_SUB(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then SUB */
#define E_COND_FEND_ASR_SUBS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , ADC */
#define E_COND_FEND_ASR_ADC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then ADC */
#define E_COND_FEND_ASR_ADCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (1 << 19)

/* Conditional Flip Endian , ASR , SBC */
#define E_COND_FEND_ASR_SBC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (1 << 19)
/* Conditional Flip Endian , ASR ,Set Flag then SBC */
#define E_COND_FEND_ASR_SBCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (1 << 19)

/* Bitwise Flip ASR */

/* Flip Bitwise , ASR Right */
#define E_FBIT_ASR(dest, r2shift, shift5)                                                                    \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag */
#define E_FBIT_ASRS(dest, r2shift, shift5)                                                                   \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , AND */
#define E_FBIT_ASR_AND(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then AND */
#define E_FBIT_ASR_ANDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , OR */
#define E_FBIT_ASR_OR(dest, roperand, r2shift, shift5)                                                              \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then OR */
#define E_FBIT_ASR_ORS(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , XOR */
#define E_FBIT_ASR_XOR(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then XOR */
#define E_FBIT_ASR_XORS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , ADD */
#define E_FBIT_ASR_ADD(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then ADD */
#define E_FBIT_ASR_ADDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , SUB */
#define E_FBIT_ASR_SUB(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then SUB */
#define E_FBIT_ASR_SUBS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , ADC */
#define E_FBIT_ASR_ADC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then ADC */
#define E_FBIT_ASR_ADCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (1 << 19)

/* Flip Bitwise , ASR Right , SBC */
#define E_FBIT_ASR_SBC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (1 << 19)
/* Flip Bitwise , ASR Right ,Set Flag then SBC */
#define E_FBIT_ASR_SBCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (1 << 19)

/* Conditional */
/* Conditional Flip Bitwise , ASR */
#define E_COND_FBIT_ASR(cond, dest, r2shift, shift5)                                                           \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag */
#define E_COND_FBIT_ASRS(cond, dest, r2shift, shift5)                                                          \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , AND */
#define E_COND_FBIT_ASR_AND(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then AND */
#define E_COND_FBIT_ASR_ANDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , OR */
#define E_COND_FBIT_ASR_OR(cond, dest, roperand, r2shift, shift5)                                                     \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then OR */
#define E_COND_FBIT_ASR_ORS(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , XOR */
#define E_COND_FBIT_ASR_XOR(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then XOR */
#define E_COND_FBIT_ASR_XORS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , ADD */
#define E_COND_FBIT_ASR_ADD(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then ADD */
#define E_COND_FBIT_ASR_ADDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , SUB */
#define E_COND_FBIT_ASR_SUB(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then SUB */
#define E_COND_FBIT_ASR_SUBS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , ADC */
#define E_COND_FBIT_ASR_ADC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then ADC */
#define E_COND_FBIT_ASR_ADCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (1 << 19)

/* Conditional Flip Bitwise , ASR , SBC */
#define E_COND_FBIT_ASR_SBC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (1 << 19)
/* Conditional Flip Bitwise , ASR ,Set Flag then SBC */
#define E_COND_FBIT_ASR_SBCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (1 << 19)

/* Flip Endian , LSR Right */
#define E_FEND_LSR(dest, r2shift, shift5)                                                                    \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag */
#define E_FEND_LSRS(dest, r2shift, shift5)                                                                   \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , AND */
#define E_FEND_LSR_AND(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then AND */
#define E_FEND_LSR_ANDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , OR */
#define E_FEND_LSR_OR(dest, roperand, r2shift, shift5)                                                              \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then OR */
#define E_FEND_LSR_ORS(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , XOR */
#define E_FEND_LSR_XOR(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then XOR */
#define E_FEND_LSR_XORS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , ADD */
#define E_FEND_LSR_ADD(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then ADD */
#define E_FEND_LSR_ADDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , SUB */
#define E_FEND_LSR_SUB(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then SUB */
#define E_FEND_LSR_SUBS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , ADC */
#define E_FEND_LSR_ADC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then ADC */
#define E_FEND_LSR_ADCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (0 << 19)

/* Flip Endian , LSR Right , SBC */
#define E_FEND_LSR_SBC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (0 << 19)
/* Flip Endian , LSR Right ,Set Flag then SBC */
#define E_FEND_LSR_SBCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (0 << 19)

/* Conditional */
/* Conditional Flip Endian , LSR */
#define E_COND_FEND_LSR(cond, dest, r2shift, shift5)                                                           \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag */
#define E_COND_FEND_LSRS(cond, dest, r2shift, shift5)                                                          \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , AND */
#define E_COND_FEND_LSR_AND(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then AND */
#define E_COND_FEND_LSR_ANDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , OR */
#define E_COND_FEND_LSR_OR(cond, dest, roperand, r2shift, shift5)                                                     \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then OR */
#define E_COND_FEND_LSR_ORS(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , XOR */
#define E_COND_FEND_LSR_XOR(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then XOR */
#define E_COND_FEND_LSR_XORS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , ADD */
#define E_COND_FEND_LSR_ADD(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then ADD */
#define E_COND_FEND_LSR_ADDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , SUB */
#define E_COND_FEND_LSR_SUB(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then SUB */
#define E_COND_FEND_LSR_SUBS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , ADC */
#define E_COND_FEND_LSR_ADC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then ADC */
#define E_COND_FEND_LSR_ADCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (0 << 18) + (0 << 19)

/* Conditional Flip Endian , LSR , SBC */
#define E_COND_FEND_LSR_SBC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (0 << 19)
/* Conditional Flip Endian , LSR ,Set Flag then SBC */
#define E_COND_FEND_LSR_SBCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (0 << 18) + (0 << 19)

/* Bitwise Flip LSR */

/* Flip Bitwise , LSR Right */
#define E_FBIT_LSR(dest, r2shift, shift5)                                                                    \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag */
#define E_FBIT_LSRS(dest, r2shift, shift5)                                                                   \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , AND */
#define E_FBIT_LSR_AND(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then AND */
#define E_FBIT_LSR_ANDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , OR */
#define E_FBIT_LSR_OR(dest, roperand, r2shift, shift5)                                                              \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then OR */
#define E_FBIT_LSR_ORS(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , XOR */
#define E_FBIT_LSR_XOR(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then XOR */
#define E_FBIT_LSR_XORS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , ADD */
#define E_FBIT_LSR_ADD(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then ADD */
#define E_FBIT_LSR_ADDS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , SUB */
#define E_FBIT_LSR_SUB(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then SUB */
#define E_FBIT_LSR_SUBS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , ADC */
#define E_FBIT_LSR_ADC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then ADC */
#define E_FBIT_LSR_ADCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (0 << 19)

/* Flip Bitwise , LSR Right , SBC */
#define E_FBIT_LSR_SBC(dest, roperand, r2shift, shift5)                                                             \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (0 << 19)
/* Flip Bitwise , LSR Right ,Set Flag then SBC */
#define E_FBIT_LSR_SBCS(dest, roperand, r2shift, shift5)                                                            \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (0 << 19)

/* Conditional */
/* Conditional Flip Bitwise , LSR */
#define E_COND_FBIT_LSR(cond, dest, r2shift, shift5)                                                           \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag */
#define E_COND_FBIT_LSRS(cond, dest, r2shift, shift5)                                                          \
    DCD 0x11 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + (0 << 29) + \
        (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , AND */
#define E_COND_FBIT_LSR_AND(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then AND */
#define E_COND_FBIT_LSR_ANDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (1 << 29) + (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , OR */
#define E_COND_FBIT_LSR_OR(cond, dest, roperand, r2shift, shift5)                                                     \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then OR */
#define E_COND_FBIT_LSR_ORS(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (2 << 29) + (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , XOR */
#define E_COND_FBIT_LSR_XOR(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then XOR */
#define E_COND_FBIT_LSR_XORS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (3 << 29) + (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , ADD */
#define E_COND_FBIT_LSR_ADD(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then ADD */
#define E_COND_FBIT_LSR_ADDS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (4 << 29) + (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , SUB */
#define E_COND_FBIT_LSR_SUB(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then SUB */
#define E_COND_FBIT_LSR_SUBS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (5 << 29) + (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , ADC */
#define E_COND_FBIT_LSR_ADC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then ADC */
#define E_COND_FBIT_LSR_ADCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (6 << 29) + (1 << 18) + (0 << 19)

/* Conditional Flip Bitwise , LSR , SBC */
#define E_COND_FBIT_LSR_SBC(cond, dest, roperand, r2shift, shift5)                                                    \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (0 << 19)
/* Conditional Flip Bitwise , LSR ,Set Flag then SBC */
#define E_COND_FBIT_LSR_SBCS(cond, dest, roperand, r2shift, shift5)                                                   \
    DCD 0x11 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((shift5 & 0x1f) << 24) + \
        (7 << 29) + (1 << 18) + (0 << 19)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_ANDOR */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         opcode      Dest            Src1               src2 SFlag */
/*                                                         Cond         SRC3 */

/* ANDOR */
#define E_ANDOR(dest, rsrc, rand, ror) \
    DCD 0x16 + (dest << 10) + (rsrc << 14)(rand << 20) + (0 << 9) + (EU << 5) + (ror << 24)
#define E_ANDORS(dest, rsrc, rand, ror) \
    DCD 0x16 + (dest << 10) + (rsrc << 14)(rand << 20) + (1 << 9) + (EU << 5) + (ror << 24)
#define E_COND_ANDOR(cond, dest, rsrc, rand, ror) \
    DCD 0x16 + (dest << 10) + (rsrc << 14)(rand << 20) + (0 << 9) + (cond << 5) + (ror << 24)
#define E_COND_ANDORS(cond, dest, rsrc, rand, ror) \
    DCD 0x16 + (dest << 10) + (rsrc << 14)(rand << 20) + (1 << 9) + (cond << 5) + (ror << 24)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_Shift byte reg Codes */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              src2 SFlag Cond
 */
/*                                                         Imm                    Extra Operation    Left/Right */
/*                                                         Shift/Rotate    Invert */

/* Logical Shift */
#define E_RLSL(dest, r2shift, rshift)                                                                        \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_RLSR(dest, r2shift, rshift)                                                                        \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag */
#define E_RLSLS(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_RLSRS(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)

/* Logical Shift and then AND */
#define E_RLSL_AND(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_AND(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then AND */
#define E_RLSL_ANDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_ANDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then OR */
#define E_RLSL_OR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_OR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then OR */
#define E_RLSL_ORS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_ORS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then XOR */
#define E_RLSL_XOR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_XOR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then XOR */
#define E_RLSL_XORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_XORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADD */
#define E_RLSL_ADD(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_ADD(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADD */
#define E_RLSL_ADDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_ADDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SUB */
#define E_RLSL_SUB(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_SUB(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SUB */
#define E_RLSL_SUBS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_SUBS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADC */
#define E_RLSL_ADC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_ADC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADC */
#define E_RLSL_ADCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_ADCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SBC */
#define E_RLSL_SBC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_SBC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SBC */
#define E_RLSL_SBCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_RLSR_SBCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)

/* Conditional */
/* Logical Shift */
#define E_COND_RLSL(cond, dest, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_COND_RLSR(cond, dest, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag */
#define E_COND_RLSLS(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18)
#define E_COND_RLSRS(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18)

/* Logical Shift and then AND */
#define E_COND_RLSL_AND(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_AND(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then AND */
#define E_COND_RLSL_ANDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_ANDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then OR */
#define E_COND_RLSL_OR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_OR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then OR */
#define E_COND_RLSL_ORS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_ORS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then XOR */
#define E_COND_RLSL_XOR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_XOR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then XOR */
#define E_COND_RLSL_XORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_XORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADD */
#define E_COND_RLSL_ADD(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_ADD(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADD */
#define E_COND_RLSL_ADDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_ADDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SUB */
#define E_COND_RLSL_SUB(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_SUB(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SUB */
#define E_COND_RLSL_SUBS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_SUBS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then ADC */
#define E_COND_RLSL_ADC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_ADC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then ADC */
#define E_COND_RLSL_ADCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_ADCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18)

/* Logical Shift and then SBC */
#define E_COND_RLSL_SBC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_SBC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)
/* Logical Shift and Set Flag then SBC */
#define E_COND_RLSL_SBCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18)
#define E_COND_RLSR_SBCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18)

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                    Extra Operation */
/*                                                         Left/Right   Shift/Rotate  POSTshift */

/* Logical Shift and then AND */
#define E_AND_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_AND_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then AND */
#define E_AND_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_AND_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then OR */
#define E_OR_RLSL(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_OR_RLSR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then OR */
#define E_OR_RLSLS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_OR_RLSRS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then XOR */
#define E_XOR_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_XOR_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then XOR */
#define E_XOR_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_XOR_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then ADD */
#define E_ADD_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_ADD_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then ADD */
#define E_ADD_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_ADD_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then SUB */
#define E_SUB_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_SUB_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then SUB */
#define E_SUB_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_SUB_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then ADC */
#define E_ADC_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_ADC_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then ADC */
#define E_ADC_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_ADC_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then SBC */
#define E_SBC_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_SBC_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then SBC */
#define E_SBC_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_SBC_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Conditional */

/* Logical Shift and then AND */
#define E_COND_AND_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_AND_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then AND */
#define E_COND_AND_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_AND_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then OR */
#define E_COND_OR_RLSL(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_OR_RLSR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then OR */
#define E_COND_OR_RLSLS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_OR_RLSRS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then XOR */
#define E_COND_XOR_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_XOR_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then XOR */
#define E_COND_XOR_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_XOR_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then ADD */
#define E_COND_ADD_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_ADD_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then ADD */
#define E_COND_ADD_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_ADD_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then SUB */
#define E_COND_SUB_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_SUB_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then SUB */
#define E_COND_SUB_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_SUB_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then ADC */
#define E_COND_ADC_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_ADC_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then ADC */
#define E_COND_ADC_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_ADC_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/* Logical Shift and then SBC */
#define E_COND_SBC_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_SBC_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)
/* Logical Shift and Set Flag then SBC */
#define E_COND_SBC_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 28)
#define E_COND_SBC_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 28)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_Shift byte reg with inversion */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Logical Shift */
#define E_RLSLN(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSRN(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag */
#define E_RLSLNS(dest, r2shift, rshift)                                                                      \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSRNS(dest, r2shift, rshift)                                                                      \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then AND */
#define E_RLSL_ANDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ANDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then AND */
#define E_RLSL_ANDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ANDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then OR */
#define E_RLSL_ORN(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ORN(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then OR */
#define E_RLSL_ORNS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ORNS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then XOR */
#define E_RLSL_XORN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_XORN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then XOR */
#define E_RLSL_XORNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_XORNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then ADD */
#define E_RLSL_ADDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ADDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then ADD */
#define E_RLSL_ADDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ADDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then SUB */
#define E_RLSL_SUBN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_SUBN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then SUB */
#define E_RLSL_SUBNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_SUBNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then ADC */
#define E_RLSL_ADCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ADCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then ADC */
#define E_RLSL_ADCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_ADCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then SBC */
#define E_RLSL_SBCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_SBCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then SBC */
#define E_RLSL_SBCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_RLSR_SBCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Conditional */
/* Logical Shift */
#define E_COND_RLSLN(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSRN(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag */
#define E_COND_RLSLNS(cond, dest, r2shift, rshift)                                                             \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSRNS(cond, dest, r2shift, rshift)                                                             \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then AND */
#define E_COND_RLSL_ANDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ANDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then AND */
#define E_COND_RLSL_ANDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ANDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then OR */
#define E_COND_RLSL_ORN(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ORN(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then OR */
#define E_COND_RLSL_ORNS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ORNS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then XOR */
#define E_COND_RLSL_XORN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_XORN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then XOR */
#define E_COND_RLSL_XORNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_XORNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then ADD */
#define E_COND_RLSL_ADDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ADDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then ADD */
#define E_COND_RLSL_ADDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ADDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then SUB */
#define E_COND_RLSL_SUBN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_SUBN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then SUB */
#define E_COND_RLSL_SUBNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_SUBNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then ADC */
#define E_COND_RLSL_ADCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ADCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then ADC */
#define E_COND_RLSL_ADCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_ADCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/* Logical Shift and then SBC */
#define E_COND_RLSL_SBCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_SBCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)
/* Logical Shift and Set Flag then SBC */
#define E_COND_RLSL_SBCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27)
#define E_COND_RLSR_SBCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27)

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                    Extra Operation */
/*                                                         Left/Right   Shift/Rotate   Inv  POSTshift */

/* Logical Shift and then AND */
#define E_ANDN_RLSL(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ANDN_RLSR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then AND */
#define E_ANDN_RLSLS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ANDN_RLSRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then OR */
#define E_ORN_RLSL(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ORN_RLSR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then OR */
#define E_ORN_RLSLS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ORN_RLSRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then XOR */
#define E_XORN_RLSL(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_XORN_RLSR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then XOR */
#define E_XORN_RLSLS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_XORN_RLSRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then ADD */
#define E_ADDN_RLSL(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ADDN_RLSR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then ADD */
#define E_ADDN_RLSLS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ADDN_RLSRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then SUB */
#define E_SUBN_RLSL(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_SUBN_RLSR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then SUB */
#define E_SUBN_RLSLS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_SUBN_RLSRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then ADC */
#define E_ADCN_RLSL(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ADCN_RLSR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then ADC */
#define E_ADCN_RLSLS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_ADCN_RLSRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then SBC */
#define E_SBCN_RLSL(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_SBCN_RLSR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then SBC */
#define E_SBCN_RLSLS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_SBCN_RLSRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Conditional */

/* Logical Shift and then AND */
#define E_COND_ANDN_RLSL(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ANDN_RLSR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then AND */
#define E_COND_ANDN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ANDN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then OR */
#define E_COND_ORN_RLSL(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ORN_RLSR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then OR */
#define E_COND_ORN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ORN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then XOR */
#define E_COND_XORN_RLSL(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_XORN_RLSR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then XOR */
#define E_COND_XORN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_XORN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then ADD */
#define E_COND_ADDN_RLSL(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ADDN_RLSR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then ADD */
#define E_COND_ADDN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ADDN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then SUB */
#define E_COND_SUBN_RLSL(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_SUBN_RLSR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then SUB */
#define E_COND_SUBN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_SUBN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then ADC */
#define E_COND_ADCN_RLSL(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ADCN_RLSR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then ADC */
#define E_COND_ADCN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_ADCN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/* Logical Shift and then SBC */
#define E_COND_SBCN_RLSL(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_SBCN_RLSR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
/* Logical Shift and Set Flag then SBC */
#define E_COND_SBCN_RLSLS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (0 << 18) + (1 << 27) + (1 << 28)
#define E_COND_SBCN_RLSRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (0 << 18) + (1 << 27) + (1 << 28)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_ROTATE by Reg Codes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Left/Right
 */
/*                                                         Shift/Rotate */

/* Rotate */
#define E_RROR(dest, r2shift, rshift)                                                                        \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)
/* Rotate and Set Flag */
#define E_RRORS(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)

/* Rotate and then AND */
#define E_RROR_AND(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then AND */
#define E_RROR_ANDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then OR */
#define E_RROR_OR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then OR */
#define E_RROR_ORS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then XOR */
#define E_RROR_XOR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then XOR */
#define E_RROR_XORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADD */
#define E_RROR_ADD(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADD */
#define E_RROR_ADDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SUB */
#define E_RROR_SUB(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SUB */
#define E_RROR_SUBS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADC */
#define E_RROR_ADC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADC */
#define E_RROR_ADCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SBC */
#define E_RROR_SBC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SBC */
#define E_RROR_SBCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)

/* Conditional */
/* Rotate */
#define E_COND_RROR(cond, dest, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)
/* Rotate and Set Flag */
#define E_COND_RRORS(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18)

/* Rotate and then AND */
#define E_COND_RROR_AND(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then AND */
#define E_COND_RROR_ANDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then OR */
#define E_COND_RROR_OR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then OR */
#define E_COND_RROR_ORS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then XOR */
#define E_COND_RROR_XOR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then XOR */
#define E_COND_RROR_XORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADD */
#define E_COND_RROR_ADD(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADD */
#define E_COND_RROR_ADDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SUB */
#define E_COND_RROR_SUB(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SUB */
#define E_COND_RROR_SUBS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then ADC */
#define E_COND_RROR_ADC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then ADC */
#define E_COND_RROR_ADCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then SBC */
#define E_COND_RROR_SBC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)
/* Rotate and Set Flag then SBC */
#define E_COND_RROR_SBCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18)

/* Rotate and then AND */
#define E_AND_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then AND */
#define E_AND_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then OR */
#define E_OR_RROR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then OR */
#define E_OR_RRORS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then XOR */
#define E_XOR_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then XOR */
#define E_XOR_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then ADD */
#define E_ADD_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then ADD */
#define E_ADD_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then SUB */
#define E_SUB_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then SUB */
#define E_SUB_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then ADC */
#define E_ADC_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then ADC */
#define E_ADC_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then SBC */
#define E_SBC_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then SBC */
#define E_SBC_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Conditional */

/* Rotate and then AND */
#define E_COND_AND_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then AND */
#define E_COND_AND_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then OR */
#define E_COND_OR_RROR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then OR */
#define E_COND_OR_RRORS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then XOR */
#define E_COND_XOR_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then XOR */
#define E_COND_XOR_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then ADD */
#define E_COND_ADD_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then ADD */
#define E_COND_ADD_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then SUB */
#define E_COND_SUB_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then SUB */
#define E_COND_SUB_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then ADC */
#define E_COND_ADC_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then ADC */
#define E_COND_ADC_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/* Rotate and then SBC */
#define E_COND_SBC_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)
/* Rotate and Set Flag then SBC */
#define E_COND_SBC_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 28)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       E_ROTATE by Reg Codes and invert ALU result */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Left/Right
 */
/*                                                         Shift/Rotate */

/* Rotate */
#define E_RRORN(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag */
#define E_RRORNS(dest, r2shift, rshift)                                                                      \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then AND */
#define E_RROR_ANDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then AND */
#define E_RROR_ANDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then OR */
#define E_RROR_ORN(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then OR */
#define E_RROR_ORNS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then XOR */
#define E_RROR_XORN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then XOR */
#define E_RROR_XORNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then ADD */
#define E_RROR_ADDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then ADD */
#define E_RROR_ADDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then SUB */
#define E_RROR_SUBN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then SUB */
#define E_RROR_SUBNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then ADC */
#define E_RROR_ADCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then ADC */
#define E_RROR_ADCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then SBC */
#define E_RROR_SBCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then SBC */
#define E_RROR_SBCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Conditional */
/* Rotate */
#define E_COND_RRORN(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag */
#define E_COND_RRORNS(cond, dest, r2shift, rshift)                                                             \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then AND */
#define E_COND_RROR_ANDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then AND */
#define E_COND_RROR_ANDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then OR */
#define E_COND_RROR_ORN(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then OR */
#define E_COND_RROR_ORNS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then XOR */
#define E_COND_RROR_XORN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then XOR */
#define E_COND_RROR_XORNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then ADD */
#define E_COND_RROR_ADDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then ADD */
#define E_COND_RROR_ADDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then SUB */
#define E_COND_RROR_SUBN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then SUB */
#define E_COND_RROR_SUBNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then ADC */
#define E_COND_RROR_ADCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then ADC */
#define E_COND_RROR_ADCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then SBC */
#define E_COND_RROR_SBCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)
/* Rotate and Set Flag then SBC */
#define E_COND_RROR_SBCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27)

/* Rotate and then AND */
#define E_ANDN_RROR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then AND */
#define E_ANDN_RRORS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then OR */
#define E_ORN_RROR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then OR */
#define E_ORN_RRORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then XOR */
#define E_XORN_RROR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then XOR */
#define E_XORN_RRORS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then ADD */
#define E_ADDN_RROR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then ADD */
#define E_ADDN_RRORS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then SUB */
#define E_SUBN_RROR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then SUB */
#define E_SUBN_RRORS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then ADC */
#define E_ADCN_RROR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then ADC */
#define E_ADCN_RRORS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then SBC */
#define E_SBCN_RROR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then SBC */
#define E_SBCN_RRORS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional */

/* Rotate and then AND */
#define E_COND_ANDN_RROR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then AND */
#define E_COND_ANDN_RRORS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then OR */
#define E_COND_ORN_RROR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then OR */
#define E_COND_ORN_RRORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then XOR */
#define E_COND_XORN_RROR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then XOR */
#define E_COND_XORN_RRORS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then ADD */
#define E_COND_ADDN_RROR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then ADD */
#define E_COND_ADDN_RRORS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then SUB */
#define E_COND_SUBN_RROR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then SUB */
#define E_COND_SUBN_RRORS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then ADC */
#define E_COND_ADCN_RROR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then ADC */
#define E_COND_ADCN_RRORS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Rotate and then SBC */
#define E_COND_SBCN_RROR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Rotate and Set Flag then SBC */
#define E_COND_SBCN_RRORS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (1 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Arithmetical Shift Codes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Left/Right
 */
/*                                                         Shift/Rotate  Arith/Shift */

/* Arith Shift Right */
#define E_RASR(dest, r2shift, rshift)                                                                        \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag */
#define E_RASRS(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)

/* Arith Shift Right and then AND */
#define E_RASR_AND(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then AND */
#define E_RASR_ANDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then OR */
#define E_RASR_OR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then OR */
#define E_RASR_ORS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then XOR */
#define E_RASR_XOR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then XOR */
#define E_RASR_XORS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then ADD */
#define E_RASR_ADD(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then ADD */
#define E_RASR_ADDS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then SUB */
#define E_RASR_SUB(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then SUB */
#define E_RASR_SUBS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then ADC */
#define E_RASR_ADC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then ADC */
#define E_RASR_ADCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then SBC */
#define E_RASR_SBC(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)
/* Arith Shift Right and Set Flag then SBC */
#define E_RASR_SBCS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)

/* Conditional */
/* Conditional Arith Shift */
#define E_COND_RASR(cond, dest, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag */
#define E_COND_RASRS(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then AND */
#define E_COND_RASR_AND(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then AND */
#define E_COND_RASR_ANDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then OR */
#define E_COND_RASR_OR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then OR */
#define E_COND_RASR_ORS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then XOR */
#define E_COND_RASR_XOR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then XOR */
#define E_COND_RASR_XORS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then ADD */
#define E_COND_RASR_ADD(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then ADD */
#define E_COND_RASR_ADDS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then SUB */
#define E_COND_RASR_SUB(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then SUB */
#define E_COND_RASR_SUBS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then ADC */
#define E_COND_RASR_ADC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then ADC */
#define E_COND_RASR_ADCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18)

/* Conditional Arith Shift and then SBC */
#define E_COND_RASR_SBC(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)
/* Conditional Arith Shift and Set Flag then SBC */
#define E_COND_RASR_SBCS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18)

/* Arith Shift Right and then AND */
#define E_AND_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then AND */
#define E_AND_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Arith Shift Right and then OR */
#define E_OR_RASR(dest, roperand, r2shift, rshift)                                                                  \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then OR */
#define E_OR_RASRS(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Arith Shift Right and then XOR */
#define E_XOR_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then XOR */
#define E_XOR_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Arith Shift Right and then ADD */
#define E_ADD_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then ADD */
#define E_ADD_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Arith Shift Right and then SUB */
#define E_SUB_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then SUB */
#define E_SUB_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Arith Shift Right and then ADC */
#define E_ADC_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then ADC */
#define E_ADC_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Arith Shift Right and then SBC */
#define E_SBC_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Arith Shift Right and Set Flag then SBC */
#define E_SBC_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional */

/* Conditional Arith Shift and then AND */
#define E_COND_AND_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then AND */
#define E_COND_AND_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional Arith Shift and then OR */
#define E_COND_OR_RASR(cond, dest, roperand, r2shift, rshift)                                                         \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then OR */
#define E_COND_OR_RASRS(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional Arith Shift and then XOR */
#define E_COND_XOR_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then XOR */
#define E_COND_XOR_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional Arith Shift and then ADD */
#define E_COND_ADD_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then ADD */
#define E_COND_ADD_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional Arith Shift and then SUB */
#define E_COND_SUB_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then SUB */
#define E_COND_SUB_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional Arith Shift and then ADC */
#define E_COND_ADC_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then ADC */
#define E_COND_ADC_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/* Conditional Arith Shift and then SBC */
#define E_COND_SBC_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)
/* Conditional Arith Shift and Set Flag then SBC */
#define E_COND_SBC_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 28)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Arithmetical Shift Codes with invert ALU */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                         opcode      Dest            Src1              r2shift SFlag
 */
/*                                                         Cond         Imm                   Extra Operation Left/Right
 */
/*                                                         Shift/Rotate  pOSTShift */

/* Arith Shift Right */
#define E_RASRN(dest, r2shift, rshift)                                                                       \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag */
#define E_RASRNS(dest, r2shift, rshift)                                                                      \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then AND */
#define E_RASR_ANDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then AND */
#define E_RASR_ANDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then OR */
#define E_RASR_ORN(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then OR */
#define E_RASR_ORNS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then XOR */
#define E_RASR_XORN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then XOR */
#define E_RASR_XORNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then ADD */
#define E_RASR_ADDN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then ADD */
#define E_RASR_ADDNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then SUB */
#define E_RASR_SUBN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then SUB */
#define E_RASR_SUBNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then ADC */
#define E_RASR_ADCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then ADC */
#define E_RASR_ADCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then SBC */
#define E_RASR_SBCN(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Arith Shift Right and Set Flag then SBC */
#define E_RASR_SBCNS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional */
/* Conditional Arith Shift */
#define E_COND_RASRN(cond, dest, r2shift, rshift)                                                              \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag */
#define E_COND_RASRNS(cond, dest, r2shift, rshift)                                                             \
    DCD 0x19 + (dest << 10) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + (0 << 29) + \
        (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then AND */
#define E_COND_RASR_ANDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then AND */
#define E_COND_RASR_ANDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then OR */
#define E_COND_RASR_ORN(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then OR */
#define E_COND_RASR_ORNS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then XOR */
#define E_COND_RASR_XORN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then XOR */
#define E_COND_RASR_XORNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then ADD */
#define E_COND_RASR_ADDN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then ADD */
#define E_COND_RASR_ADDNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then SUB */
#define E_COND_RASR_SUBN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then SUB */
#define E_COND_RASR_SUBNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then ADC */
#define E_COND_RASR_ADCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then ADC */
#define E_COND_RASR_ADCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Conditional Arith Shift and then SBC */
#define E_COND_RASR_SBCN(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)
/* Conditional Arith Shift and Set Flag then SBC */
#define E_COND_RASR_SBCNS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27)

/* Arith Shift Right and then AND */
#define E_ANDN_RASR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then AND */
#define E_ANDN_RASRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Arith Shift Right and then OR */
#define E_ORN_RASR(dest, roperand, r2shift, rshift)                                                                 \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then OR */
#define E_ORN_RASRS(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Arith Shift Right and then XOR */
#define E_XORN_RASR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then XOR */
#define E_XORN_RASRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Arith Shift Right and then ADD */
#define E_ADDN_RASR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then ADD */
#define E_ADDN_RASRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Arith Shift Right and then SUB */
#define E_SUBN_RASR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then SUB */
#define E_SUBN_RASRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Arith Shift Right and then ADC */
#define E_ADCN_RASR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then ADC */
#define E_ADCN_RASRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Arith Shift Right and then SBC */
#define E_SBCN_RASR(dest, roperand, r2shift, rshift)                                                                \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Arith Shift Right and Set Flag then SBC */
#define E_SBCN_RASRS(dest, roperand, r2shift, rshift)                                                               \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (EU << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional */

/* Conditional Arith Shift and then AND */
#define E_COND_ANDN_RASR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then AND */
#define E_COND_ANDN_RASRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (1 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional Arith Shift and then OR */
#define E_COND_ORN_RASR(cond, dest, roperand, r2shift, rshift)                                                        \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then OR */
#define E_COND_ORN_RASRS(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (2 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional Arith Shift and then XOR */
#define E_COND_XORN_RASR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then XOR */
#define E_COND_XORN_RASRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (3 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional Arith Shift and then ADD */
#define E_COND_ADDN_RASR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then ADD */
#define E_COND_ADDN_RASRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (4 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional Arith Shift and then SUB */
#define E_COND_SUBN_RASR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then SUB */
#define E_COND_SUBN_RASRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (5 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional Arith Shift and then ADC */
#define E_COND_ADCN_RASR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then ADC */
#define E_COND_ADCN_RASRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (6 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/* Conditional Arith Shift and then SBC */
#define E_COND_SBCN_RASR(cond, dest, roperand, r2shift, rshift)                                                       \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (0 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)
/* Conditional Arith Shift and Set Flag then SBC */
#define E_COND_SBCN_RASRS(cond, dest, roperand, r2shift, rshift)                                                      \
    DCD 0x19 + (dest << 10) + (roperand << 14) + (r2shift << 20) + (1 << 9) + (cond << 5) + ((rshift & 0x1f) << 24) + \
        (7 << 29) + (0 << 19) + (1 << 18) + (1 << 27) + (1 << 28)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Bit Manipulate */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                         opcode      Dest            Src1               src2 SFlag */
/*                                                         Cond         Imm                  Extra Operation ShiftByByte
 */
/*                                                         Neg/Pos Mask */

/* Bit test by byte */
#define E_BTST(dest, rdata, rbit)                                                                           \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (1 << 31)
#define E_BCLR(dest, rdata, rbit)                                                                           \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (0 << 31)
#define E_BSET(dest, rdata, rbit)                                                                           \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (2 << 29) + \
        (1 << 18) + (1 << 31)
#define E_BTOG(dest, rdata, rbit)                                                                           \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (EU << 5) + (0 << 24) + (3 << 29) + \
        (1 << 18) + (1 << 31)

/* Bit test by byte with set flags */
#define E_BTSTS(dest, rdata, rbit)                                                                          \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (1 << 31)
#define E_BCLRS(dest, rdata, rbit)                                                                          \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (0 << 31)
#define E_BSETS(dest, rdata, rbit)                                                                          \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (2 << 29) + \
        (1 << 18) + (1 << 31)
#define E_BTOGS(dest, rdata, rbit)                                                                          \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (EU << 5) + (0 << 24) + (3 << 29) + \
        (1 << 18) + (1 << 31)

/* Conditional Bit test by byte */
#define E_COND_BTST(cond, dest, rdata, rbit)                                                                  \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (1 << 31)
#define E_COND_BCLR(cond, dest, rdata, rbit)                                                                  \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (0 << 31)
#define E_COND_BSET(cond, dest, rdata, rbit)                                                                  \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (2 << 29) + \
        (1 << 18) + (1 << 31)
#define E_COND_BTOG(cond, dest, rdata, rbit)                                                                  \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (0 << 9) + (cond << 5) + (0 << 24) + (3 << 29) + \
        (1 << 18) + (1 << 31)

/* Conditional Bit test by byte with set flags */
#define E_COND_BTSTS(cond, dest, rdata, rbit)                                                                 \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (1 << 31)
#define E_COND_BCLRS(cond, dest, rdata, rbit)                                                                 \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (1 << 29) + \
        (1 << 18) + (0 << 31)
#define E_COND_BSETS(cond, dest, rdata, rbit)                                                                 \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (2 << 29) + \
        (1 << 18) + (1 << 31)
#define E_COND_BTOGS(cond, dest, rdata, rbit)                                                                 \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (rbit << 20) + (1 << 9) + (cond << 5) + (0 << 24) + (3 << 29) + \
        (1 << 18) + (1 << 31)

/* Bit test by imm */
#define E_BTST_IMM(dest, rdata, bit5)                                                                                \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (1 << 31)
#define E_BCLR_IMM(dest, rdata, bit5)                                                                                \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (0 << 31)
#define E_BSET_IMM(dest, rdata, bit5)                                                                                \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + \
        (1 << 31)
#define E_BTOG_IMM(dest, rdata, bit5)                                                                                \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + \
        (1 << 31)

/* Bit test by imm with set flags */
#define E_BTST_IMMS(dest, rdata, bit5)                                                                               \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (1 << 31)
#define E_BCLR_IMMS(dest, rdata, bit5)                                                                               \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (0 << 31)
#define E_BSET_IMMS(dest, rdata, bit5)                                                                               \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + \
        (1 << 31)
#define E_BTOG_IMMS(dest, rdata, bit5)                                                                               \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (EU << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + \
        (1 << 31)

/* Conditional Bit test by imm */
#define E_COND_BTST_IMM(cond, dest, rdata, bit5)                                                                       \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (1 << 31)
#define E_COND_BCLR_IMM(cond, dest, rdata, bit5)                                                                       \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (0 << 31)
#define E_COND_BSET_IMM(cond, dest, rdata, bit5)                                                                       \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + \
        (1 << 31)
#define E_COND_BTOG_IMM(cond, dest, rdata, bit5)                                                                       \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (0 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + \
        (1 << 31)

/* Conditional Bit test by imm with set flags */
#define E_COND_BTST_IMMS(cond, dest, rdata, bit5)                                                                      \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (1 << 31)
#define E_COND_BCLR_IMMS(cond, dest, rdata, bit5)                                                                      \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (1 << 29) + (0 << 18) + \
        (0 << 31)
#define E_COND_BSET_IMMS(cond, dest, rdata, bit5)                                                                      \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (2 << 29) + (0 << 18) + \
        (1 << 31)
#define E_COND_BTOG_IMMS(cond, dest, rdata, bit5)                                                                      \
    DCD 0x18 + (dest << 10) + (rdata << 14) + (1 << 9) + (cond << 5) + ((bit5 & 0x1f) << 24) + (3 << 29) + (0 << 18) + \
        (1 << 31)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                      Tight Loop */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define E_TIGHT_LOOP(rend, rcount)            DCD 0x1A + (rend << 14) + (rcount << 20)
#define E_COND_TIGHT_LOOP(cond, rend, rcount) DCD 0x1A + (rend << 14) + (rcount << 20) + (cond << 5)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                    Boolean Detect */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                Opcode     Dest           Vector/Single NoUpdateRA */
/*                                                                LargeVectors    Cond              Table */

#define E_HOLD            DCD 0x1C + (PC << 10) + (1 << 15) + (0 << 18) + (0 << 19) + (EU << 5)
#define E_COND_HOLD(cond) DCD 0x1C + (PC << 10) + (1 << 15) + (0 << 18) + (0 << 19) + (cond << 5)

/* Small Vector Versions */
#define E_VECTORED_HOLD(table) DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (EU << 5) + (table << 20)
#define E_COND_VECTORED_HOLD(cond, table) \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (cond << 5) + (table << 20)
#define E_VECTORED_HOLD_NRA(table) \
    DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (EU << 5) + (table << 20)
#define E_COND_VECTORED_HOLD_NRA \
    (cond, table) DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (cond << 5) + (table << 20)

/* Large Vector Versions */
#define E_VECTORED_HOLD_LV(table) \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (EU << 5) + (table << 20)
#define E_COND_VECTORED_HOLD_LV(cond, table) \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (cond << 5) + (table << 20)
#define E_VECTORED_HOLD_LV_NRA(table) \
    DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (EU << 5) + (table << 20)
#define E_COND_VECTORED_HOLD_LV_NRA \
    (cond, table) DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (cond << 5) + (table << 20)

/*/ Accelarated Vectored_hold */
/* Small Vector Versions */
#define E_ACC_VECTORED_HOLD(table, vectors)                                                               \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (EU << 5) + (table << 20) + (1 << 9) + \
        (vectors << 24)
#define E_COND_ACC_VECTORED_HOLD(cond, table, vectors)                                                      \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (0 << 19) + (cond << 5) + (table << 20) + (1 << 9) + \
        (vectors << 24)
#define E_ACC_VECTORED_HOLD_NRA(table, vectors)                                                           \
    DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (EU << 5) + (table << 20) + (1 << 9) + \
        (vectors << 24)
#define E_COND_ACC_VECTORED_HOLD_NRA                                                                    \
    (cond, table, vectors) DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (0 << 19) + (cond << 5) + \
        (table << 20) + (1 << 9) + (vectors << 24)

/* Large Vector Versions */
#define E_ACC_VECTORED_HOLD_LV(table, vectors)                                                            \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (EU << 5) + (table << 20) + (1 << 9) + \
        (vectors << 24)
#define E_COND_ACC_VECTORED_HOLD_LV(cond, table, vectors)                                                   \
    DCD 0x1C + (table << 10) + (0 << 15) + (0 << 18) + (1 << 19) + (cond << 5) + (table << 20) + (1 << 9) + \
        (vectors << 24)
#define E_ACC_VECTORED_HOLD_LV_NRA(table, vectors)                                                        \
    DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (EU << 5) + (table << 20) + (1 << 9) + \
        (vectors << 24)
#define E_COND_ACC_VECTORED_HOLD_LV_NRA                                                                 \
    (cond, table, vectors) DCD 0x1C + (table << 10) + (0 << 15) + (1 << 18) + (1 << 19) + (cond << 5) + \
        (table << 20) + (1 << 9) + (vectors << 24)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Reg offset Read */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                        opcode      Rdata Dest       Pointer         WData Source */
/*                                                        Offset             SizeWord    Signed Access  Cond Write */

/* LDR (Load, Load Byte, LoadByteSigned) */
#define E_LDR_REG(dest, source, offset) \
    DCD 0x1D + (dest << 10) + (source << 14) + (offset << 24) + (1 << 18) + (0 << 21) + (EU << 5)
#define E_LDR_REGB(dest, source, offset) \
    DCD 0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (0 << 21) + (EU << 5)
#define E_LDR_REGBS(dest, source, offset) \
    DCD 0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (1 << 21) + (EU << 5)

/* Conditional LDR (Load, Load Byte, LoadByteSigned) */
#define E_COND_LDR_REG(cond, dest, source, offset) \
    DCD 0x1D + (dest << 10) + (source << 14) + (offset << 24) + (1 << 18) + (0 << 21) + (cond << 5)
#define E_COND_LDR_REGB(cond, dest, source, offset) \
    DCD 0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (0 << 21) + (cond << 5)
#define E_COND_LDR_REGBS(cond, dest, source, offset) \
    DCD 0x1D + (dest << 10) + (source << 14) + (offset << 24) + (0 << 18) + (1 << 21) + (cond << 5)

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                       Reg offset Write */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*                                                       opcode      Rdata Dest         Pointer       WData Source */
/*                                                       Offset             SizeWord    Signed Access  Cond Write */

/* STR (Load, Load Byte, LoadByteSigned) */
#define E_STR_REG(raddr, rdata, roffset) \
    DCD 0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (1 << 18) + (0 << 11) + (EU << 5) + (1 << 30)
#define E_STR_REGB(raddr, rdata, roffset) \
    DCD 0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (0 << 18) + (0 << 11) + (EU << 5) + (1 << 30)

/* Conditional STR (Load, Load Byte, LoadByteSigned) */
#define E_COND_STR_REG(cond, raddr, rdata, roffset) \
    DCD 0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (1 << 18) + (0 << 11) + (cond << 5) + (1 << 30)
#define E_COND_STR_REGB(cond, raddr, rdata, roffset) \
    DCD 0x1D + (raddr << 14) + (rdata << 20) + (roffset << 24) + (0 << 18) + (0 << 11) + (cond << 5) + (1 << 30)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                     GPO modify Byte */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define E_MODIFY_GPO_BYTE(andmask, ormask, xormask) DCD 0x1E + (andmask << 8) + (ormask << 16) + (xormask << 24)

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*                                    HeartBeat opcodes */
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define E_HEART_RYTHM_IMM(val16imm) DCD 0x32 + (val16imm << 16)
#define E_HEART_RYTHM(r16bit)       DCD 0x32 + (r16bit << 14) + (1 << 9)
#define E_SYNCH_ALL_TO_BEAT(on1imm) DCD 0x52 + (on1imm << 31)
#define E_WAIT_FOR_BEAT             DCD 0x72

#endif
