/**
  ******************************************************************************
  * @file    dma2d_reg.h
  * @version V1.0
  * @date    2021-09-10
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
#ifndef __DMA2D_REG_H__
#define __DMA2D_REG_H__

#include "bl808.h"

/* 0x0 : DMA_IntStatus */
#define DMA2D_DMA_INTSTATUS_OFFSET (0x0)
#define DMA2D_INTSTATUS            DMA2D_INTSTATUS
#define DMA2D_INTSTATUS_POS        (0U)
#define DMA2D_INTSTATUS_LEN        (8U)
#define DMA2D_INTSTATUS_MSK        (((1U << DMA2D_INTSTATUS_LEN) - 1) << DMA2D_INTSTATUS_POS)
#define DMA2D_INTSTATUS_UMSK       (~(((1U << DMA2D_INTSTATUS_LEN) - 1) << DMA2D_INTSTATUS_POS))

/* 0x4 : DMA_IntTCStatus */
#define DMA2D_DMA_INTTCSTATUS_OFFSET (0x4)
#define DMA2D_INTTCSTATUS            DMA2D_INTTCSTATUS
#define DMA2D_INTTCSTATUS_POS        (0U)
#define DMA2D_INTTCSTATUS_LEN        (8U)
#define DMA2D_INTTCSTATUS_MSK        (((1U << DMA2D_INTTCSTATUS_LEN) - 1) << DMA2D_INTTCSTATUS_POS)
#define DMA2D_INTTCSTATUS_UMSK       (~(((1U << DMA2D_INTTCSTATUS_LEN) - 1) << DMA2D_INTTCSTATUS_POS))

/* 0x8 : DMA_IntTCClear */
#define DMA2D_DMA_INTTCCLEAR_OFFSET (0x8)
#define DMA2D_INTTCCLEAR            DMA2D_INTTCCLEAR
#define DMA2D_INTTCCLEAR_POS        (0U)
#define DMA2D_INTTCCLEAR_LEN        (8U)
#define DMA2D_INTTCCLEAR_MSK        (((1U << DMA2D_INTTCCLEAR_LEN) - 1) << DMA2D_INTTCCLEAR_POS)
#define DMA2D_INTTCCLEAR_UMSK       (~(((1U << DMA2D_INTTCCLEAR_LEN) - 1) << DMA2D_INTTCCLEAR_POS))

/* 0xC : DMA_EnbldChns */
#define DMA2D_DMA_ENBLDCHNS_OFFSET (0xC)
#define DMA2D_ENABLEDCHANNELS      DMA2D_ENABLEDCHANNELS
#define DMA2D_ENABLEDCHANNELS_POS  (0U)
#define DMA2D_ENABLEDCHANNELS_LEN  (8U)
#define DMA2D_ENABLEDCHANNELS_MSK  (((1U << DMA2D_ENABLEDCHANNELS_LEN) - 1) << DMA2D_ENABLEDCHANNELS_POS)
#define DMA2D_ENABLEDCHANNELS_UMSK (~(((1U << DMA2D_ENABLEDCHANNELS_LEN) - 1) << DMA2D_ENABLEDCHANNELS_POS))

/* 0x10 : DMA_Config */
#define DMA2D_DMA_CONFIG_OFFSET (0x10)
#define DMA2D_E                 DMA2D_E
#define DMA2D_E_POS             (0U)
#define DMA2D_E_LEN             (1U)
#define DMA2D_E_MSK             (((1U << DMA2D_E_LEN) - 1) << DMA2D_E_POS)
#define DMA2D_E_UMSK            (~(((1U << DMA2D_E_LEN) - 1) << DMA2D_E_POS))
#define DMA2D_CHCLKCG           DMA2D_CHCLKCG
#define DMA2D_CHCLKCG_POS       (16U)
#define DMA2D_CHCLKCG_LEN       (8U)
#define DMA2D_CHCLKCG_MSK       (((1U << DMA2D_CHCLKCG_LEN) - 1) << DMA2D_CHCLKCG_POS)
#define DMA2D_CHCLKCG_UMSK      (~(((1U << DMA2D_CHCLKCG_LEN) - 1) << DMA2D_CHCLKCG_POS))

/* 0x14 : DMA_Sync */
#define DMA2D_DMA_SYNC_OFFSET (0x14)
#define DMA2D_DMA_SYNC        DMA2D_DMA_SYNC
#define DMA2D_DMA_SYNC_POS    (0U)
#define DMA2D_DMA_SYNC_LEN    (32U)
#define DMA2D_DMA_SYNC_MSK    (((1U << DMA2D_DMA_SYNC_LEN) - 1) << DMA2D_DMA_SYNC_POS)
#define DMA2D_DMA_SYNC_UMSK   (~(((1U << DMA2D_DMA_SYNC_LEN) - 1) << DMA2D_DMA_SYNC_POS))

/* 0x18 : DMA_SoftBReq */
#define DMA2D_DMA_SOFTBREQ_OFFSET (0x18)
#define DMA2D_SOFTBREQ            DMA2D_SOFTBREQ
#define DMA2D_SOFTBREQ_POS        (0U)
#define DMA2D_SOFTBREQ_LEN        (32U)
#define DMA2D_SOFTBREQ_MSK        (((1U << DMA2D_SOFTBREQ_LEN) - 1) << DMA2D_SOFTBREQ_POS)
#define DMA2D_SOFTBREQ_UMSK       (~(((1U << DMA2D_SOFTBREQ_LEN) - 1) << DMA2D_SOFTBREQ_POS))

/* 0x1C : DMA_SoftLBReq */
#define DMA2D_DMA_SOFTLBREQ_OFFSET (0x1C)
#define DMA2D_SOFTLBREQ            DMA2D_SOFTLBREQ
#define DMA2D_SOFTLBREQ_POS        (0U)
#define DMA2D_SOFTLBREQ_LEN        (32U)
#define DMA2D_SOFTLBREQ_MSK        (((1U << DMA2D_SOFTLBREQ_LEN) - 1) << DMA2D_SOFTLBREQ_POS)
#define DMA2D_SOFTLBREQ_UMSK       (~(((1U << DMA2D_SOFTLBREQ_LEN) - 1) << DMA2D_SOFTLBREQ_POS))

/* 0x20 : DMA_SoftSReq */
#define DMA2D_DMA_SOFTSREQ_OFFSET (0x20)
#define DMA2D_SOFTSREQ            DMA2D_SOFTSREQ
#define DMA2D_SOFTSREQ_POS        (0U)
#define DMA2D_SOFTSREQ_LEN        (32U)
#define DMA2D_SOFTSREQ_MSK        (((1U << DMA2D_SOFTSREQ_LEN) - 1) << DMA2D_SOFTSREQ_POS)
#define DMA2D_SOFTSREQ_UMSK       (~(((1U << DMA2D_SOFTSREQ_LEN) - 1) << DMA2D_SOFTSREQ_POS))

/* 0x24 : DMA_SoftLSReq */
#define DMA2D_DMA_SOFTLSREQ_OFFSET (0x24)
#define DMA2D_SOFTLSREQ            DMA2D_SOFTLSREQ
#define DMA2D_SOFTLSREQ_POS        (0U)
#define DMA2D_SOFTLSREQ_LEN        (32U)
#define DMA2D_SOFTLSREQ_MSK        (((1U << DMA2D_SOFTLSREQ_LEN) - 1) << DMA2D_SOFTLSREQ_POS)
#define DMA2D_SOFTLSREQ_UMSK       (~(((1U << DMA2D_SOFTLSREQ_LEN) - 1) << DMA2D_SOFTLSREQ_POS))

/* 0x100 : DMA2D_C0SrcAddr */
#define DMA2D_C0SRCADDR_OFFSET (0x100)
#define DMA2D_SRCADDR          DMA2D_SRCADDR
#define DMA2D_SRCADDR_POS      (0U)
#define DMA2D_SRCADDR_LEN      (32U)
#define DMA2D_SRCADDR_MSK      (((1U << DMA2D_SRCADDR_LEN) - 1) << DMA2D_SRCADDR_POS)
#define DMA2D_SRCADDR_UMSK     (~(((1U << DMA2D_SRCADDR_LEN) - 1) << DMA2D_SRCADDR_POS))

/* 0x104 : DMA2D_C0DstAddr */
#define DMA2D_C0DSTADDR_OFFSET (0x104)
#define DMA2D_DSTADDR          DMA2D_DSTADDR
#define DMA2D_DSTADDR_POS      (0U)
#define DMA2D_DSTADDR_LEN      (32U)
#define DMA2D_DSTADDR_MSK      (((1U << DMA2D_DSTADDR_LEN) - 1) << DMA2D_DSTADDR_POS)
#define DMA2D_DSTADDR_UMSK     (~(((1U << DMA2D_DSTADDR_LEN) - 1) << DMA2D_DSTADDR_POS))

/* 0x108 : DMA2D_C0LLI */
#define DMA2D_C0LLI_OFFSET  (0x108)
#define DMA2D_LLI_EN        DMA2D_LLI_EN
#define DMA2D_LLI_EN_POS    (0U)
#define DMA2D_LLI_EN_LEN    (1U)
#define DMA2D_LLI_EN_MSK    (((1U << DMA2D_LLI_EN_LEN) - 1) << DMA2D_LLI_EN_POS)
#define DMA2D_LLI_EN_UMSK   (~(((1U << DMA2D_LLI_EN_LEN) - 1) << DMA2D_LLI_EN_POS))
#define DMA2D_LLI_ADDR      DMA2D_LLI_ADDR
#define DMA2D_LLI_ADDR_POS  (2U)
#define DMA2D_LLI_ADDR_LEN  (30U)
#define DMA2D_LLI_ADDR_MSK  (((1U << DMA2D_LLI_ADDR_LEN) - 1) << DMA2D_LLI_ADDR_POS)
#define DMA2D_LLI_ADDR_UMSK (~(((1U << DMA2D_LLI_ADDR_LEN) - 1) << DMA2D_LLI_ADDR_POS))

/* 0x10C : DMA2D_C0_BUS */
#define DMA2D_C0_BUS_OFFSET     (0x10C)
#define DMA2D_TRANSFERSIZE      DMA2D_TRANSFERSIZE
#define DMA2D_TRANSFERSIZE_POS  (0U)
#define DMA2D_TRANSFERSIZE_LEN  (12U)
#define DMA2D_TRANSFERSIZE_MSK  (((1U << DMA2D_TRANSFERSIZE_LEN) - 1) << DMA2D_TRANSFERSIZE_POS)
#define DMA2D_TRANSFERSIZE_UMSK (~(((1U << DMA2D_TRANSFERSIZE_LEN) - 1) << DMA2D_TRANSFERSIZE_POS))
#define DMA2D_SRC_BURST         DMA2D_SRC_BURST
#define DMA2D_SRC_BURST_POS     (12U)
#define DMA2D_SRC_BURST_LEN     (2U)
#define DMA2D_SRC_BURST_MSK     (((1U << DMA2D_SRC_BURST_LEN) - 1) << DMA2D_SRC_BURST_POS)
#define DMA2D_SRC_BURST_UMSK    (~(((1U << DMA2D_SRC_BURST_LEN) - 1) << DMA2D_SRC_BURST_POS))
#define DMA2D_DST_BURST         DMA2D_DST_BURST
#define DMA2D_DST_BURST_POS     (15U)
#define DMA2D_DST_BURST_LEN     (2U)
#define DMA2D_DST_BURST_MSK     (((1U << DMA2D_DST_BURST_LEN) - 1) << DMA2D_DST_BURST_POS)
#define DMA2D_DST_BURST_UMSK    (~(((1U << DMA2D_DST_BURST_LEN) - 1) << DMA2D_DST_BURST_POS))
#define DMA2D_SRC_SIZE          DMA2D_SRC_SIZE
#define DMA2D_SRC_SIZE_POS      (18U)
#define DMA2D_SRC_SIZE_LEN      (2U)
#define DMA2D_SRC_SIZE_MSK      (((1U << DMA2D_SRC_SIZE_LEN) - 1) << DMA2D_SRC_SIZE_POS)
#define DMA2D_SRC_SIZE_UMSK     (~(((1U << DMA2D_SRC_SIZE_LEN) - 1) << DMA2D_SRC_SIZE_POS))
#define DMA2D_DST_SIZE          DMA2D_DST_SIZE
#define DMA2D_DST_SIZE_POS      (21U)
#define DMA2D_DST_SIZE_LEN      (2U)
#define DMA2D_DST_SIZE_MSK      (((1U << DMA2D_DST_SIZE_LEN) - 1) << DMA2D_DST_SIZE_POS)
#define DMA2D_DST_SIZE_UMSK     (~(((1U << DMA2D_DST_SIZE_LEN) - 1) << DMA2D_DST_SIZE_POS))
#define DMA2D_SI                DMA2D_SI
#define DMA2D_SI_POS            (26U)
#define DMA2D_SI_LEN            (1U)
#define DMA2D_SI_MSK            (((1U << DMA2D_SI_LEN) - 1) << DMA2D_SI_POS)
#define DMA2D_SI_UMSK           (~(((1U << DMA2D_SI_LEN) - 1) << DMA2D_SI_POS))
#define DMA2D_DI                DMA2D_DI
#define DMA2D_DI_POS            (27U)
#define DMA2D_DI_LEN            (1U)
#define DMA2D_DI_MSK            (((1U << DMA2D_DI_LEN) - 1) << DMA2D_DI_POS)
#define DMA2D_DI_UMSK           (~(((1U << DMA2D_DI_LEN) - 1) << DMA2D_DI_POS))
#define DMA2D_PROT              DMA2D_PROT
#define DMA2D_PROT_POS          (28U)
#define DMA2D_PROT_LEN          (3U)
#define DMA2D_PROT_MSK          (((1U << DMA2D_PROT_LEN) - 1) << DMA2D_PROT_POS)
#define DMA2D_PROT_UMSK         (~(((1U << DMA2D_PROT_LEN) - 1) << DMA2D_PROT_POS))
#define DMA2D_I                 DMA2D_I
#define DMA2D_I_POS             (31U)
#define DMA2D_I_LEN             (1U)
#define DMA2D_I_MSK             (((1U << DMA2D_I_LEN) - 1) << DMA2D_I_POS)
#define DMA2D_I_UMSK            (~(((1U << DMA2D_I_LEN) - 1) << DMA2D_I_POS))

/* 0x110 : DMA2D_C0_SRC_CNT */
#define DMA2D_C0_SRC_CNT_OFFSET (0x110)
#define DMA2D_SRC_X_CNT         DMA2D_SRC_X_CNT
#define DMA2D_SRC_X_CNT_POS     (0U)
#define DMA2D_SRC_X_CNT_LEN     (16U)
#define DMA2D_SRC_X_CNT_MSK     (((1U << DMA2D_SRC_X_CNT_LEN) - 1) << DMA2D_SRC_X_CNT_POS)
#define DMA2D_SRC_X_CNT_UMSK    (~(((1U << DMA2D_SRC_X_CNT_LEN) - 1) << DMA2D_SRC_X_CNT_POS))
#define DMA2D_SRC_Y_CNT         DMA2D_SRC_Y_CNT
#define DMA2D_SRC_Y_CNT_POS     (16U)
#define DMA2D_SRC_Y_CNT_LEN     (16U)
#define DMA2D_SRC_Y_CNT_MSK     (((1U << DMA2D_SRC_Y_CNT_LEN) - 1) << DMA2D_SRC_Y_CNT_POS)
#define DMA2D_SRC_Y_CNT_UMSK    (~(((1U << DMA2D_SRC_Y_CNT_LEN) - 1) << DMA2D_SRC_Y_CNT_POS))

/* 0x114 : DMA2D_C0_SRC_XIC */
#define DMA2D_C0_SRC_XIC_OFFSET (0x114)
#define DMA2D_SRC_X_INCR        DMA2D_SRC_X_INCR
#define DMA2D_SRC_X_INCR_POS    (0U)
#define DMA2D_SRC_X_INCR_LEN    (32U)
#define DMA2D_SRC_X_INCR_MSK    (((1U << DMA2D_SRC_X_INCR_LEN) - 1) << DMA2D_SRC_X_INCR_POS)
#define DMA2D_SRC_X_INCR_UMSK   (~(((1U << DMA2D_SRC_X_INCR_LEN) - 1) << DMA2D_SRC_X_INCR_POS))

/* 0x118 : DMA2D_C0_SRC_YIC */
#define DMA2D_C0_SRC_YIC_OFFSET (0x118)
#define DMA2D_SRC_Y_INCR        DMA2D_SRC_Y_INCR
#define DMA2D_SRC_Y_INCR_POS    (0U)
#define DMA2D_SRC_Y_INCR_LEN    (32U)
#define DMA2D_SRC_Y_INCR_MSK    (((1U << DMA2D_SRC_Y_INCR_LEN) - 1) << DMA2D_SRC_Y_INCR_POS)
#define DMA2D_SRC_Y_INCR_UMSK   (~(((1U << DMA2D_SRC_Y_INCR_LEN) - 1) << DMA2D_SRC_Y_INCR_POS))

/* 0x11C : DMA2D_C0_DST_CNT */
#define DMA2D_C0_DST_CNT_OFFSET (0x11C)
#define DMA2D_DST_X_CNT         DMA2D_DST_X_CNT
#define DMA2D_DST_X_CNT_POS     (0U)
#define DMA2D_DST_X_CNT_LEN     (16U)
#define DMA2D_DST_X_CNT_MSK     (((1U << DMA2D_DST_X_CNT_LEN) - 1) << DMA2D_DST_X_CNT_POS)
#define DMA2D_DST_X_CNT_UMSK    (~(((1U << DMA2D_DST_X_CNT_LEN) - 1) << DMA2D_DST_X_CNT_POS))

/* 0x120 : DMA2D_C0_DST_XIC */
#define DMA2D_C0_DST_XIC_OFFSET (0x120)
#define DMA2D_DST_X_INCR        DMA2D_DST_X_INCR
#define DMA2D_DST_X_INCR_POS    (0U)
#define DMA2D_DST_X_INCR_LEN    (32U)
#define DMA2D_DST_X_INCR_MSK    (((1U << DMA2D_DST_X_INCR_LEN) - 1) << DMA2D_DST_X_INCR_POS)
#define DMA2D_DST_X_INCR_UMSK   (~(((1U << DMA2D_DST_X_INCR_LEN) - 1) << DMA2D_DST_X_INCR_POS))

/* 0x124 : DMA2D_C0_DST_YIC */
#define DMA2D_C0_DST_YIC_OFFSET (0x124)
#define DMA2D_DST_Y_INCR        DMA2D_DST_Y_INCR
#define DMA2D_DST_Y_INCR_POS    (0U)
#define DMA2D_DST_Y_INCR_LEN    (32U)
#define DMA2D_DST_Y_INCR_MSK    (((1U << DMA2D_DST_Y_INCR_LEN) - 1) << DMA2D_DST_Y_INCR_POS)
#define DMA2D_DST_Y_INCR_UMSK   (~(((1U << DMA2D_DST_Y_INCR_LEN) - 1) << DMA2D_DST_Y_INCR_POS))

/* 0x174 : DMA2D_C0_KEY */
#define DMA2D_C0_KEY_OFFSET (0x174)
#define DMA2D_KEY0          DMA2D_KEY0
#define DMA2D_KEY0_POS      (0U)
#define DMA2D_KEY0_LEN      (8U)
#define DMA2D_KEY0_MSK      (((1U << DMA2D_KEY0_LEN) - 1) << DMA2D_KEY0_POS)
#define DMA2D_KEY0_UMSK     (~(((1U << DMA2D_KEY0_LEN) - 1) << DMA2D_KEY0_POS))
#define DMA2D_KEY1          DMA2D_KEY1
#define DMA2D_KEY1_POS      (8U)
#define DMA2D_KEY1_LEN      (8U)
#define DMA2D_KEY1_MSK      (((1U << DMA2D_KEY1_LEN) - 1) << DMA2D_KEY1_POS)
#define DMA2D_KEY1_UMSK     (~(((1U << DMA2D_KEY1_LEN) - 1) << DMA2D_KEY1_POS))
#define DMA2D_KEY2          DMA2D_KEY2
#define DMA2D_KEY2_POS      (16U)
#define DMA2D_KEY2_LEN      (8U)
#define DMA2D_KEY2_MSK      (((1U << DMA2D_KEY2_LEN) - 1) << DMA2D_KEY2_POS)
#define DMA2D_KEY2_UMSK     (~(((1U << DMA2D_KEY2_LEN) - 1) << DMA2D_KEY2_POS))
#define DMA2D_KEY3          DMA2D_KEY3
#define DMA2D_KEY3_POS      (24U)
#define DMA2D_KEY3_LEN      (8U)
#define DMA2D_KEY3_MSK      (((1U << DMA2D_KEY3_LEN) - 1) << DMA2D_KEY3_POS)
#define DMA2D_KEY3_UMSK     (~(((1U << DMA2D_KEY3_LEN) - 1) << DMA2D_KEY3_POS))

/* 0x178 : DMA2D_C0_KEY_EN */
#define DMA2D_C0_KEY_EN_OFFSET (0x178)
#define DMA2D_KEY_EN           DMA2D_KEY_EN
#define DMA2D_KEY_EN_POS       (0U)
#define DMA2D_KEY_EN_LEN       (1U)
#define DMA2D_KEY_EN_MSK       (((1U << DMA2D_KEY_EN_LEN) - 1) << DMA2D_KEY_EN_POS)
#define DMA2D_KEY_EN_UMSK      (~(((1U << DMA2D_KEY_EN_LEN) - 1) << DMA2D_KEY_EN_POS))
#define DMA2D_KEY_MODE         DMA2D_KEY_MODE
#define DMA2D_KEY_MODE_POS     (1U)
#define DMA2D_KEY_MODE_LEN     (2U)
#define DMA2D_KEY_MODE_MSK     (((1U << DMA2D_KEY_MODE_LEN) - 1) << DMA2D_KEY_MODE_POS)
#define DMA2D_KEY_MODE_UMSK    (~(((1U << DMA2D_KEY_MODE_LEN) - 1) << DMA2D_KEY_MODE_POS))
#define DMA2D_KEY_STRB         DMA2D_KEY_STRB
#define DMA2D_KEY_STRB_POS     (4U)
#define DMA2D_KEY_STRB_LEN     (4U)
#define DMA2D_KEY_STRB_MSK     (((1U << DMA2D_KEY_STRB_LEN) - 1) << DMA2D_KEY_STRB_POS)
#define DMA2D_KEY_STRB_UMSK    (~(((1U << DMA2D_KEY_STRB_LEN) - 1) << DMA2D_KEY_STRB_POS))

/* 0x17C : DMA2D_C0_CFG */
#define DMA2D_C0_CFG_OFFSET      (0x17C)
#define DMA2D_CH_EN              DMA2D_CH_EN
#define DMA2D_CH_EN_POS          (0U)
#define DMA2D_CH_EN_LEN          (1U)
#define DMA2D_CH_EN_MSK          (((1U << DMA2D_CH_EN_LEN) - 1) << DMA2D_CH_EN_POS)
#define DMA2D_CH_EN_UMSK         (~(((1U << DMA2D_CH_EN_LEN) - 1) << DMA2D_CH_EN_POS))
#define DMA2D_SRCPERIPHERAL      DMA2D_SRCPERIPHERAL
#define DMA2D_SRCPERIPHERAL_POS  (1U)
#define DMA2D_SRCPERIPHERAL_LEN  (5U)
#define DMA2D_SRCPERIPHERAL_MSK  (((1U << DMA2D_SRCPERIPHERAL_LEN) - 1) << DMA2D_SRCPERIPHERAL_POS)
#define DMA2D_SRCPERIPHERAL_UMSK (~(((1U << DMA2D_SRCPERIPHERAL_LEN) - 1) << DMA2D_SRCPERIPHERAL_POS))
#define DMA2D_DSTPERIPHERAL      DMA2D_DSTPERIPHERAL
#define DMA2D_DSTPERIPHERAL_POS  (6U)
#define DMA2D_DSTPERIPHERAL_LEN  (5U)
#define DMA2D_DSTPERIPHERAL_MSK  (((1U << DMA2D_DSTPERIPHERAL_LEN) - 1) << DMA2D_DSTPERIPHERAL_POS)
#define DMA2D_DSTPERIPHERAL_UMSK (~(((1U << DMA2D_DSTPERIPHERAL_LEN) - 1) << DMA2D_DSTPERIPHERAL_POS))
#define DMA2D_FLOWCNTRL          DMA2D_FLOWCNTRL
#define DMA2D_FLOWCNTRL_POS      (11U)
#define DMA2D_FLOWCNTRL_LEN      (3U)
#define DMA2D_FLOWCNTRL_MSK      (((1U << DMA2D_FLOWCNTRL_LEN) - 1) << DMA2D_FLOWCNTRL_POS)
#define DMA2D_FLOWCNTRL_UMSK     (~(((1U << DMA2D_FLOWCNTRL_LEN) - 1) << DMA2D_FLOWCNTRL_POS))
#define DMA2D_AHB_B2B            DMA2D_AHB_B2B
#define DMA2D_AHB_B2B_POS        (14U)
#define DMA2D_AHB_B2B_LEN        (1U)
#define DMA2D_AHB_B2B_MSK        (((1U << DMA2D_AHB_B2B_LEN) - 1) << DMA2D_AHB_B2B_POS)
#define DMA2D_AHB_B2B_UMSK       (~(((1U << DMA2D_AHB_B2B_LEN) - 1) << DMA2D_AHB_B2B_POS))
#define DMA2D_FIFO_EMPTY         DMA2D_FIFO_EMPTY
#define DMA2D_FIFO_EMPTY_POS     (16U)
#define DMA2D_FIFO_EMPTY_LEN     (1U)
#define DMA2D_FIFO_EMPTY_MSK     (((1U << DMA2D_FIFO_EMPTY_LEN) - 1) << DMA2D_FIFO_EMPTY_POS)
#define DMA2D_FIFO_EMPTY_UMSK    (~(((1U << DMA2D_FIFO_EMPTY_LEN) - 1) << DMA2D_FIFO_EMPTY_POS))
#define DMA2D_LLICOUNTER         DMA2D_LLICOUNTER
#define DMA2D_LLICOUNTER_POS     (20U)
#define DMA2D_LLICOUNTER_LEN     (10U)
#define DMA2D_LLICOUNTER_MSK     (((1U << DMA2D_LLICOUNTER_LEN) - 1) << DMA2D_LLICOUNTER_POS)
#define DMA2D_LLICOUNTER_UMSK    (~(((1U << DMA2D_LLICOUNTER_LEN) - 1) << DMA2D_LLICOUNTER_POS))
#define DMA2D_REG_DMA_2D_EN      DMA2D_REG_DMA_2D_EN
#define DMA2D_REG_DMA_2D_EN_POS  (31U)
#define DMA2D_REG_DMA_2D_EN_LEN  (1U)
#define DMA2D_REG_DMA_2D_EN_MSK  (((1U << DMA2D_REG_DMA_2D_EN_LEN) - 1) << DMA2D_REG_DMA_2D_EN_POS)
#define DMA2D_REG_DMA_2D_EN_UMSK (~(((1U << DMA2D_REG_DMA_2D_EN_LEN) - 1) << DMA2D_REG_DMA_2D_EN_POS))

struct dma2d_reg {
    /* 0x0 : DMA_IntStatus */
    union {
        struct {
            uint32_t IntStatus     : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_IntStatus;

    /* 0x4 : DMA_IntTCStatus */
    union {
        struct {
            uint32_t IntTCStatus   : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_IntTCStatus;

    /* 0x8 : DMA_IntTCClear */
    union {
        struct {
            uint32_t IntTCClear    : 8;  /* [ 7: 0],        w1p,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_IntTCClear;

    /* 0xC : DMA_EnbldChns */
    union {
        struct {
            uint32_t EnabledChannels : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31   : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_EnbldChns;

    /* 0x10 : DMA_Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_15  : 15; /* [15: 1],       rsvd,        0x0 */
            uint32_t ChClkCG        : 8;  /* [23:16],        r/w,       0xff */
            uint32_t reserved_24_31 : 8;  /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_Config;

    /* 0x14 : DMA_Sync */
    union {
        struct {
            uint32_t DMA_Sync : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_Sync;

    /* 0x18 : DMA_SoftBReq */
    union {
        struct {
            uint32_t SoftBReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftBReq;

    /* 0x1C : DMA_SoftLBReq */
    union {
        struct {
            uint32_t SoftLBReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftLBReq;

    /* 0x20 : DMA_SoftSReq */
    union {
        struct {
            uint32_t SoftSReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftSReq;

    /* 0x24 : DMA_SoftLSReq */
    union {
        struct {
            uint32_t SoftLSReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftLSReq;

    /* 0x28  reserved */
    uint8_t RESERVED0x28[216];

    /* 0x100 : DMA2D_C0SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0SrcAddr;

    /* 0x104 : DMA2D_C0DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0DstAddr;

    /* 0x108 : DMA2D_C0LLI */
    union {
        struct {
            uint32_t LLI_EN     : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1 : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t LLI_ADDR   : 30; /* [31: 2],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0LLI;

    /* 0x10C : DMA2D_C0_BUS */
    union {
        struct DMA2D_Control_Reg {
            uint32_t TransferSize   : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SRC_BURST      : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t reserved_14    : 1;  /* [   14],       rsvd,        0x0 */
            uint32_t DST_BURST      : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t reserved_17    : 1;  /* [   17],       rsvd,        0x0 */
            uint32_t SRC_SIZE       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20    : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DST_SIZE       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t reserved_23_25 : 3;  /* [25:23],       rsvd,        0x0 */
            uint32_t SI             : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI             : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot           : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I              : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_BUS;

    /* 0x110 : DMA2D_C0_SRC_CNT */
    union {
        struct {
            uint32_t SRC_X_CNT : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t SRC_Y_CNT : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_SRC_CNT;

    /* 0x114 : DMA2D_C0_SRC_XIC */
    union {
        struct {
            uint32_t SRC_X_INCR : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_SRC_XIC;

    /* 0x118 : DMA2D_C0_SRC_YIC */
    union {
        struct {
            uint32_t SRC_Y_INCR : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_SRC_YIC;

    /* 0x11C : DMA2D_C0_DST_CNT */
    union {
        struct {
            uint32_t DST_X_CNT      : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_DST_CNT;

    /* 0x120 : DMA2D_C0_DST_XIC */
    union {
        struct {
            uint32_t DST_X_INCR : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_DST_XIC;

    /* 0x124 : DMA2D_C0_DST_YIC */
    union {
        struct {
            uint32_t DST_Y_INCR : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_DST_YIC;

    /* 0x128  reserved */
    uint8_t RESERVED0x128[76];

    /* 0x174 : DMA2D_C0_KEY */
    union {
        struct {
            uint32_t KEY0 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t KEY1 : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t KEY2 : 8; /* [23:16],        r/w,        0x0 */
            uint32_t KEY3 : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_KEY;

    /* 0x178 : DMA2D_C0_KEY_EN */
    union {
        struct {
            uint32_t KEY_EN        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t KEY_MODE      : 2;  /* [ 2: 1],        r/w,        0x0 */
            uint32_t reserved_3    : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t KEY_STRB      : 4;  /* [ 7: 4],        r/w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_KEY_EN;

    /* 0x17C : DMA2D_C0_CFG */
    union {
        struct {
            uint32_t CH_EN          : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t AHB_B2B        : 1;  /* [   14],        r/w,        0x0 */
            uint32_t reserved_15    : 1;  /* [   15],       rsvd,        0x0 */
            uint32_t FIFO_Empty     : 1;  /* [   16],          r,        0x0 */
            uint32_t reserved_17_19 : 3;  /* [19:17],       rsvd,        0x0 */
            uint32_t LLICounter     : 10; /* [29:20],          r,        0x0 */
            uint32_t reserved_30    : 1;  /* [   30],       rsvd,        0x0 */
            uint32_t reg_dma_2d_en  : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA2D_C0_CFG;
};

typedef volatile struct dma2d_reg dma2d_reg_t;

#endif /* __DMA2D_REG_H__ */
