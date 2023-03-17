/**
  ******************************************************************************
  * @file    ipc_reg.h
  * @version V1.2
  * @date    2020-09-21
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __IPC_REG_H__
#define __IPC_REG_H__

#include "bl808.h"

/* 0x0 : Interrupt Set Write Register */
#define IPC_CPU1_IPC_ISWR_OFFSET (0x0)
#define IPC_CPU1_IPC_ISWR        IPC_CPU1_IPC_ISWR
#define IPC_CPU1_IPC_ISWR_POS    (0U)
#define IPC_CPU1_IPC_ISWR_LEN    (16U)
#define IPC_CPU1_IPC_ISWR_MSK    (((1U << IPC_CPU1_IPC_ISWR_LEN) - 1) << IPC_CPU1_IPC_ISWR_POS)
#define IPC_CPU1_IPC_ISWR_UMSK   (~(((1U << IPC_CPU1_IPC_ISWR_LEN) - 1) << IPC_CPU1_IPC_ISWR_POS))

/* 0x4 : Interrupt raw status Register */
#define IPC_CPU1_IPC_IRSRR_OFFSET (0x4)
#define IPC_CPU1_IPC_IRSRR        IPC_CPU1_IPC_IRSRR
#define IPC_CPU1_IPC_IRSRR_POS    (0U)
#define IPC_CPU1_IPC_IRSRR_LEN    (16U)
#define IPC_CPU1_IPC_IRSRR_MSK    (((1U << IPC_CPU1_IPC_IRSRR_LEN) - 1) << IPC_CPU1_IPC_IRSRR_POS)
#define IPC_CPU1_IPC_IRSRR_UMSK   (~(((1U << IPC_CPU1_IPC_IRSRR_LEN) - 1) << IPC_CPU1_IPC_IRSRR_POS))

/* 0x8 : Interrupt Clear Register */
#define IPC_CPU1_IPC_ICR_OFFSET (0x8)
#define IPC_CPU1_IPC_ICR        IPC_CPU1_IPC_ICR
#define IPC_CPU1_IPC_ICR_POS    (0U)
#define IPC_CPU1_IPC_ICR_LEN    (16U)
#define IPC_CPU1_IPC_ICR_MSK    (((1U << IPC_CPU1_IPC_ICR_LEN) - 1) << IPC_CPU1_IPC_ICR_POS)
#define IPC_CPU1_IPC_ICR_UMSK   (~(((1U << IPC_CPU1_IPC_ICR_LEN) - 1) << IPC_CPU1_IPC_ICR_POS))

/* 0xc : Interrupt Unmask Set Register */
#define IPC_CPU1_IPC_IUSR_OFFSET (0xc)
#define IPC_CPU1_IPC_IUSR        IPC_AP_IPC_IUSR
#define IPC_CPU1_IPC_IUSR_POS    (0U)
#define IPC_CPU1_IPC_IUSR_LEN    (16U)
#define IPC_CPU1_IPC_IUSR_MSK    (((1U << IPC_CPU1_IPC_IUSR_LEN) - 1) << IPC_CPU1_IPC_IUSR_POS)
#define IPC_CPU1_IPC_IUSR_UMSK   (~(((1U << IPC_CPU1_IPC_IUSR_LEN) - 1) << IPC_CPU1_IPC_IUSR_POS))

/* 0x10 : Interrupt Unmask Clear Register */
#define IPC_CPU1_IPC_IUCR_OFFSET (0x10)
#define IPC_CPU1_IPC_IUCR        IPC_CPU1_IPC_IUCR
#define IPC_CPU1_IPC_IUCR_POS    (0U)
#define IPC_CPU1_IPC_IUCR_LEN    (16U)
#define IPC_CPU1_IPC_IUCR_MSK    (((1U << IPC_CPU1_IPC_IUCR_LEN) - 1) << IPC_CPU1_IPC_IUCR_POS)
#define IPC_CPU1_IPC_IUCR_UMSK   (~(((1U << IPC_CPU1_IPC_IUCR_LEN) - 1) << IPC_CPU1_IPC_IUCR_POS))

/* 0x14 : Interrupt Line Sel Low Register */
#define IPC_CPU1_IPC_ILSLR_OFFSET (0x14)
#define IPC_CPU1_IPC_ILSLR        IPC_CPU1_IPC_ILSLR
#define IPC_CPU1_IPC_ILSLR_POS    (0U)
#define IPC_CPU1_IPC_ILSLR_LEN    (32U)
#define IPC_CPU1_IPC_ILSLR_MSK    (((1U << IPC_CPU1_IPC_ILSLR_LEN) - 1) << IPC_CPU1_IPC_ILSLR_POS)
#define IPC_CPU1_IPC_ILSLR_UMSK   (~(((1U << IPC_CPU1_IPC_ILSLR_LEN) - 1) << IPC_CPU1_IPC_ILSLR_POS))

/* 0x18 : Interrupt Line Sel High Register */
#define IPC_CPU1_IPC_ILSHR_OFFSET (0x18)
#define IPC_CPU1_IPC_ILSHR        IPC_CPU1_IPC_ILSHR
#define IPC_CPU1_IPC_ILSHR_POS    (0U)
#define IPC_CPU1_IPC_ILSHR_LEN    (32U)
#define IPC_CPU1_IPC_ILSHR_MSK    (((1U << IPC_CPU1_IPC_ILSHR_LEN) - 1) << IPC_CPU1_IPC_ILSHR_POS)
#define IPC_CPU1_IPC_ILSHR_UMSK   (~(((1U << IPC_CPU1_IPC_ILSHR_LEN) - 1) << IPC_CPU1_IPC_ILSHR_POS))

/* 0x1C : Interrupt status Register */
#define IPC_CPU1_IPC_ISR_OFFSET (0x1C)
#define IPC_CPU1_IPC_ISR        IPC_CPU1_IPC_ISR
#define IPC_CPU1_IPC_ISR_POS    (0U)
#define IPC_CPU1_IPC_ISR_LEN    (16U)
#define IPC_CPU1_IPC_ISR_MSK    (((1U << IPC_CPU1_IPC_ISR_LEN) - 1) << IPC_CPU1_IPC_ISR_POS)
#define IPC_CPU1_IPC_ISR_UMSK   (~(((1U << IPC_CPU1_IPC_ISR_LEN) - 1) << IPC_CPU1_IPC_ISR_POS))

/* 0x20 : Interrupt Set Write Register */
#define IPC_CPU0_IPC_ISWR_OFFSET (0x20)
#define IPC_CPU0_IPC_ISWR        IPC_CPU0_IPC_ISWR
#define IPC_CPU0_IPC_ISWR_POS    (0U)
#define IPC_CPU0_IPC_ISWR_LEN    (16U)
#define IPC_CPU0_IPC_ISWR_MSK    (((1U << IPC_CPU0_IPC_ISWR_LEN) - 1) << IPC_CPU0_IPC_ISWR_POS)
#define IPC_CPU0_IPC_ISWR_UMSK   (~(((1U << IPC_CPU0_IPC_ISWR_LEN) - 1) << IPC_CPU0_IPC_ISWR_POS))

/* 0x24 : Interrupt raw status Register */
#define IPC_CPU0_IPC_IRSRR_OFFSET (0x24)
#define IPC_CPU0_IPC_IRSRR        IPC_CPU0_IPC_IRSRR
#define IPC_CPU0_IPC_IRSRR_POS    (0U)
#define IPC_CPU0_IPC_IRSRR_LEN    (16U)
#define IPC_CPU0_IPC_IRSRR_MSK    (((1U << IPC_CPU0_IPC_IRSRR_LEN) - 1) << IPC_CPU0_IPC_IRSRR_POS)
#define IPC_CPU0_IPC_IRSRR_UMSK   (~(((1U << IPC_CPU0_IPC_IRSRR_LEN) - 1) << IPC_CPU0_IPC_IRSRR_POS))

/* 0x28 : Interrupt Clear Register */
#define IPC_CPU0_IPC_ICR_OFFSET (0x28)
#define IPC_CPU0_IPC_ICR        IPC_CPU0_IPC_ICR
#define IPC_CPU0_IPC_ICR_POS    (0U)
#define IPC_CPU0_IPC_ICR_LEN    (16U)
#define IPC_CPU0_IPC_ICR_MSK    (((1U << IPC_CPU0_IPC_ICR_LEN) - 1) << IPC_CPU0_IPC_ICR_POS)
#define IPC_CPU0_IPC_ICR_UMSK   (~(((1U << IPC_CPU0_IPC_ICR_LEN) - 1) << IPC_CPU0_IPC_ICR_POS))

/* 0x2c : Interrupt Unmask Set Register */
#define IPC_CPU0_IPC_IUSR_OFFSET (0x2c)
#define IPC_CPU0_IPC_IUSR        IPC_CPU0_IPC_IUSR
#define IPC_CPU0_IPC_IUSR_POS    (0U)
#define IPC_NP_IPC_IUSR_LEN      (16U)
#define IPC_CPU0_IPC_IUSR_MSK    (((1U << IPC_CPU0_IPC_IUSR_LEN) - 1) << IPC_CPU0_IPC_IUSR_POS)
#define IPC_CPU0_IPC_IUSR_UMSK   (~(((1U << IPC_CPU0_IPC_IUSR_LEN) - 1) << IPC_CPU0_IPC_IUSR_POS))

/* 0x30 : Interrupt Unmask Clear Register */
#define IPC_CPU0_IPC_IUCR_OFFSET (0x30)
#define IPC_CPU0_IPC_IUCR        IPC_CPU0_IPC_IUCR
#define IPC_CPU0_IPC_IUCR_POS    (0U)
#define IPC_CPU0_IPC_IUCR_LEN    (16U)
#define IPC_CPU0_IPC_IUCR_MSK    (((1U << IPC_CPU0_IPC_IUCR_LEN) - 1) << IPC_CPU0_IPC_IUCR_POS)
#define IPC_CPU0_IPC_IUCR_UMSK   (~(((1U << IPC_CPU0_IPC_IUCR_LEN) - 1) << IPC_CPU0_IPC_IUCR_POS))

/* 0x34 : Interrupt Line Sel Low Register */
#define IPC_CPU0_IPC_ILSLR_OFFSET (0x34)
#define IPC_CPU0_IPC_ILSLR        IPC_CPU0_IPC_ILSLR
#define IPC_CPU0_IPC_ILSLR_POS    (0U)
#define IPC_CPU0_IPC_ILSLR_LEN    (32U)
#define IPC_CPU0_IPC_ILSLR_MSK    (((1U << IPC_CPU0_IPC_ILSLR_LEN) - 1) << IPC_CPU0_IPC_ILSLR_POS)
#define IPC_CPU0_IPC_ILSLR_UMSK   (~(((1U << IPC_CPU0_IPC_ILSLR_LEN) - 1) << IPC_CPU0_IPC_ILSLR_POS))

/* 0x38 : Interrupt Line Sel High Register */
#define IPC_CPU0_IPC_ILSHR_OFFSET (0x38)
#define IPC_CPU0_IPC_ILSHR        IPC_CPU0_IPC_ILSHR
#define IPC_CPU0_IPC_ILSHR_POS    (0U)
#define IPC_CPU0_IPC_ILSHR_LEN    (32U)
#define IPC_CPU0_IPC_ILSHR_MSK    (((1U << IPC_CPU0_IPC_ILSHR_LEN) - 1) << IPC_CPU0_IPC_ILSHR_POS)
#define IPC_CPU0_IPC_ILSHR_UMSK   (~(((1U << IPC_CPU0_IPC_ILSHR_LEN) - 1) << IPC_CPU0_IPC_ILSHR_POS))

/* 0x3C : Interrupt status Register */
#define IPC_CPU0_IPC_ISR_OFFSET (0x3C)
#define IPC_CPU0_IPC_ISR        IPC_CPU0_IPC_ISR
#define IPC_CPU0_IPC_ISR_POS    (0U)
#define IPC_CPU0_IPC_ISR_LEN    (16U)
#define IPC_CPU0_IPC_ISR_MSK    (((1U << IPC_CPU0_IPC_ISR_LEN) - 1) << IPC_CPU0_IPC_ISR_POS)
#define IPC_CPU0_IPC_ISR_UMSK   (~(((1U << IPC_CPU0_IPC_ISR_LEN) - 1) << IPC_CPU0_IPC_ISR_POS))

struct ipc_reg {
    /* 0x0 : Interrupt Set Write Register */
    union {
        struct {
            uint32_t CPU1_IPC_ISWR  : 16; /* [15: 0],         WO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_ISWR;

    /* 0x4 : Interrupt raw status Register */
    union {
        struct {
            uint32_t CPU1_IPC_IRSRR : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_IRSRR;

    /* 0x8 : Interrupt Clear Register */
    union {
        struct {
            uint32_t CPU1_IPC_ICR   : 16; /* [15: 0],         WO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_ICR;

    /* 0xc : Interrupt Unmask Set Register */
    union {
        struct {
            uint32_t CPU1_IPC_IUSR  : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_IUSR;

    /* 0x10 : Interrupt Unmask Clear Register */
    union {
        struct {
            uint32_t CPU1_IPC_IUCR  : 16; /* [15: 0],         WO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_IUCR;

    /* 0x14 : Interrupt Line Sel Low Register */
    union {
        struct {
            uint32_t CPU1_IPC_ILSLR : 32; /* [31: 0],         RW,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_ILSLR;

    /* 0x18 : Interrupt Line Sel High Register */
    union {
        struct {
            uint32_t CPU1_IPC_ILSHR : 32; /* [31: 0],         RW,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_ILSHR;

    /* 0x1C : Interrupt status Register */
    union {
        struct {
            uint32_t CPU1_IPC_ISR   : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU1_IPC_ISR;

    /* 0x20 : Interrupt Set Write Register */
    union {
        struct {
            uint32_t CPU0_IPC_ISWR  : 16; /* [15: 0],         WO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_ISWR;

    /* 0x24 : Interrupt raw status Register */
    union {
        struct {
            uint32_t CPU0_IPC_IRSRR : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_IRSRR;

    /* 0x28 : Interrupt Clear Register */
    union {
        struct {
            uint32_t CPU0_IPC_ICR   : 16; /* [15: 0],         WO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_ICR;

    /* 0x2c : Interrupt Unmask Set Register */
    union {
        struct {
            uint32_t CPU0_IPC_IUSR  : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_IUSR;

    /* 0x30 : Interrupt Unmask Clear Register */
    union {
        struct {
            uint32_t CPU0_IPC_IUCR  : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_IUCR;

    /* 0x34 : Interrupt Line Sel Low Register */
    union {
        struct {
            uint32_t CPU0_IPC_ILSLR : 32; /* [31: 0],         RW,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_ILSLR;

    /* 0x38 : Interrupt Line Sel High Register */
    union {
        struct {
            uint32_t CPU0_IPC_ILSHR : 32; /* [31: 0],         RW,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_ILSHR;

    /* 0x3C : Interrupt status Register */
    union {
        struct {
            uint32_t CPU0_IPC_ISR   : 16; /* [15: 0],         RO,        0x0 */
            uint32_t Reserved_31_16 : 16; /* [31:16],       RSVD,        0x0 */
        } BF;
        uint32_t WORD;
    } CPU0_IPC_ISR;
};

typedef volatile struct ipc_reg ipc_reg_t;

#endif /* __IPC_REG_H__ */
