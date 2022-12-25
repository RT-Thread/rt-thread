/**
  ******************************************************************************
  * @file    dma_reg.h
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
#ifndef __DMA_REG_H__
#define __DMA_REG_H__

#include "bl808.h"

/* 0x0 : DMA_IntStatus */
#define DMA_INTSTATUS_OFFSET (0x0)
#define DMA_INTSTATUS        DMA_INTSTATUS
#define DMA_INTSTATUS_POS    (0U)
#define DMA_INTSTATUS_LEN    (8U)
#define DMA_INTSTATUS_MSK    (((1U << DMA_INTSTATUS_LEN) - 1) << DMA_INTSTATUS_POS)
#define DMA_INTSTATUS_UMSK   (~(((1U << DMA_INTSTATUS_LEN) - 1) << DMA_INTSTATUS_POS))

/* 0x4 : DMA_IntTCStatus */
#define DMA_INTTCSTATUS_OFFSET (0x4)
#define DMA_INTTCSTATUS        DMA_INTTCSTATUS
#define DMA_INTTCSTATUS_POS    (0U)
#define DMA_INTTCSTATUS_LEN    (8U)
#define DMA_INTTCSTATUS_MSK    (((1U << DMA_INTTCSTATUS_LEN) - 1) << DMA_INTTCSTATUS_POS)
#define DMA_INTTCSTATUS_UMSK   (~(((1U << DMA_INTTCSTATUS_LEN) - 1) << DMA_INTTCSTATUS_POS))

/* 0x8 : DMA_IntTCClear */
#define DMA_INTTCCLEAR_OFFSET (0x8)
#define DMA_INTTCCLEAR        DMA_INTTCCLEAR
#define DMA_INTTCCLEAR_POS    (0U)
#define DMA_INTTCCLEAR_LEN    (8U)
#define DMA_INTTCCLEAR_MSK    (((1U << DMA_INTTCCLEAR_LEN) - 1) << DMA_INTTCCLEAR_POS)
#define DMA_INTTCCLEAR_UMSK   (~(((1U << DMA_INTTCCLEAR_LEN) - 1) << DMA_INTTCCLEAR_POS))

/* 0xC : DMA_IntErrorStatus */
#define DMA_INTERRORSTATUS_OFFSET (0xC)
#define DMA_INTERRORSTATUS        DMA_INTERRORSTATUS
#define DMA_INTERRORSTATUS_POS    (0U)
#define DMA_INTERRORSTATUS_LEN    (8U)
#define DMA_INTERRORSTATUS_MSK    (((1U << DMA_INTERRORSTATUS_LEN) - 1) << DMA_INTERRORSTATUS_POS)
#define DMA_INTERRORSTATUS_UMSK   (~(((1U << DMA_INTERRORSTATUS_LEN) - 1) << DMA_INTERRORSTATUS_POS))

/* 0x10 : DMA_IntErrClr */
#define DMA_INTERRCLR_OFFSET (0x10)
#define DMA_INTERRCLR        DMA_INTERRCLR
#define DMA_INTERRCLR_POS    (0U)
#define DMA_INTERRCLR_LEN    (8U)
#define DMA_INTERRCLR_MSK    (((1U << DMA_INTERRCLR_LEN) - 1) << DMA_INTERRCLR_POS)
#define DMA_INTERRCLR_UMSK   (~(((1U << DMA_INTERRCLR_LEN) - 1) << DMA_INTERRCLR_POS))

/* 0x14 : DMA_RawIntTCStatus */
#define DMA_RAWINTTCSTATUS_OFFSET (0x14)
#define DMA_RAWINTTCSTATUS        DMA_RAWINTTCSTATUS
#define DMA_RAWINTTCSTATUS_POS    (0U)
#define DMA_RAWINTTCSTATUS_LEN    (8U)
#define DMA_RAWINTTCSTATUS_MSK    (((1U << DMA_RAWINTTCSTATUS_LEN) - 1) << DMA_RAWINTTCSTATUS_POS)
#define DMA_RAWINTTCSTATUS_UMSK   (~(((1U << DMA_RAWINTTCSTATUS_LEN) - 1) << DMA_RAWINTTCSTATUS_POS))

/* 0x18 : DMA_RawIntErrorStatus */
#define DMA_RAWINTERRORSTATUS_OFFSET (0x18)
#define DMA_RAWINTERRORSTATUS        DMA_RAWINTERRORSTATUS
#define DMA_RAWINTERRORSTATUS_POS    (0U)
#define DMA_RAWINTERRORSTATUS_LEN    (8U)
#define DMA_RAWINTERRORSTATUS_MSK    (((1U << DMA_RAWINTERRORSTATUS_LEN) - 1) << DMA_RAWINTERRORSTATUS_POS)
#define DMA_RAWINTERRORSTATUS_UMSK   (~(((1U << DMA_RAWINTERRORSTATUS_LEN) - 1) << DMA_RAWINTERRORSTATUS_POS))

/* 0x1C : DMA_EnbldChns */
#define DMA_ENBLDCHNS_OFFSET     (0x1C)
#define DMA_ENABLEDCHANNELS      DMA_ENABLEDCHANNELS
#define DMA_ENABLEDCHANNELS_POS  (0U)
#define DMA_ENABLEDCHANNELS_LEN  (8U)
#define DMA_ENABLEDCHANNELS_MSK  (((1U << DMA_ENABLEDCHANNELS_LEN) - 1) << DMA_ENABLEDCHANNELS_POS)
#define DMA_ENABLEDCHANNELS_UMSK (~(((1U << DMA_ENABLEDCHANNELS_LEN) - 1) << DMA_ENABLEDCHANNELS_POS))

/* 0x20 : DMA_SoftBReq */
#define DMA_SOFTBREQ_OFFSET (0x20)
#define DMA_SOFTBREQ        DMA_SOFTBREQ
#define DMA_SOFTBREQ_POS    (0U)
#define DMA_SOFTBREQ_LEN    (32U)
#define DMA_SOFTBREQ_MSK    (((1U << DMA_SOFTBREQ_LEN) - 1) << DMA_SOFTBREQ_POS)
#define DMA_SOFTBREQ_UMSK   (~(((1U << DMA_SOFTBREQ_LEN) - 1) << DMA_SOFTBREQ_POS))

/* 0x24 : DMA_SoftSReq */
#define DMA_SOFTSREQ_OFFSET (0x24)
#define DMA_SOFTSREQ        DMA_SOFTSREQ
#define DMA_SOFTSREQ_POS    (0U)
#define DMA_SOFTSREQ_LEN    (32U)
#define DMA_SOFTSREQ_MSK    (((1U << DMA_SOFTSREQ_LEN) - 1) << DMA_SOFTSREQ_POS)
#define DMA_SOFTSREQ_UMSK   (~(((1U << DMA_SOFTSREQ_LEN) - 1) << DMA_SOFTSREQ_POS))

/* 0x28 : DMA_SoftLBReq */
#define DMA_SOFTLBREQ_OFFSET (0x28)
#define DMA_SOFTLBREQ        DMA_SOFTLBREQ
#define DMA_SOFTLBREQ_POS    (0U)
#define DMA_SOFTLBREQ_LEN    (32U)
#define DMA_SOFTLBREQ_MSK    (((1U << DMA_SOFTLBREQ_LEN) - 1) << DMA_SOFTLBREQ_POS)
#define DMA_SOFTLBREQ_UMSK   (~(((1U << DMA_SOFTLBREQ_LEN) - 1) << DMA_SOFTLBREQ_POS))

/* 0x2C : DMA_SoftLSReq */
#define DMA_SOFTLSREQ_OFFSET (0x2C)
#define DMA_SOFTLSREQ        DMA_SOFTLSREQ
#define DMA_SOFTLSREQ_POS    (0U)
#define DMA_SOFTLSREQ_LEN    (32U)
#define DMA_SOFTLSREQ_MSK    (((1U << DMA_SOFTLSREQ_LEN) - 1) << DMA_SOFTLSREQ_POS)
#define DMA_SOFTLSREQ_UMSK   (~(((1U << DMA_SOFTLSREQ_LEN) - 1) << DMA_SOFTLSREQ_POS))

/* 0x30 : DMA_Top_Config */
#define DMA_TOP_CONFIG_OFFSET (0x30)
#define DMA_E                 DMA_E
#define DMA_E_POS             (0U)
#define DMA_E_LEN             (1U)
#define DMA_E_MSK             (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK            (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_M                 DMA_M
#define DMA_M_POS             (1U)
#define DMA_M_LEN             (1U)
#define DMA_M_MSK             (((1U << DMA_M_LEN) - 1) << DMA_M_POS)
#define DMA_M_UMSK            (~(((1U << DMA_M_LEN) - 1) << DMA_M_POS))

/* 0x34 : DMA_Sync */
#define DMA_SYNC_OFFSET (0x34)
#define DMA_SYNC        DMA_SYNC
#define DMA_SYNC_POS    (0U)
#define DMA_SYNC_LEN    (32U)
#define DMA_SYNC_MSK    (((1U << DMA_SYNC_LEN) - 1) << DMA_SYNC_POS)
#define DMA_SYNC_UMSK   (~(((1U << DMA_SYNC_LEN) - 1) << DMA_SYNC_POS))

/* 0x100 : DMA_C0SrcAddr */
#define DMA_C0SRCADDR_OFFSET (0x100)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x104 : DMA_C0DstAddr */
#define DMA_C0DSTADDR_OFFSET (0x104)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x108 : DMA_C0LLI */
#define DMA_C0LLI_OFFSET (0x108)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x10C : DMA_C0Control */
#define DMA_C0CONTROL_OFFSET  (0x10C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x110 : DMA_C0Config */
#define DMA_C0CONFIG_OFFSET    (0x110)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))
#define DMA_LLICOUNTER         DMA_LLICOUNTER
#define DMA_LLICOUNTER_POS     (20U)
#define DMA_LLICOUNTER_LEN     (10U)
#define DMA_LLICOUNTER_MSK     (((1U << DMA_LLICOUNTER_LEN) - 1) << DMA_LLICOUNTER_POS)
#define DMA_LLICOUNTER_UMSK    (~(((1U << DMA_LLICOUNTER_LEN) - 1) << DMA_LLICOUNTER_POS))

/* 0x11C : DMA_C0RSVD */
#define DMA_C0RSVD_OFFSET    (0x11C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

/* 0x200 : DMA_C1SrcAddr */
#define DMA_C1SRCADDR_OFFSET (0x200)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x204 : DMA_C1DstAddr */
#define DMA_C1DSTADDR_OFFSET (0x204)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x208 : DMA_C1LLI */
#define DMA_C1LLI_OFFSET (0x208)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x20C : DMA_C1Control */
#define DMA_C1CONTROL_OFFSET  (0x20C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x210 : DMA_C1Config */
#define DMA_C1CONFIG_OFFSET    (0x210)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))

/* 0x21C : DMA_C1RSVD */
#define DMA_C1RSVD_OFFSET    (0x21C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

/* 0x300 : DMA_C2SrcAddr */
#define DMA_C2SRCADDR_OFFSET (0x300)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x304 : DMA_C2DstAddr */
#define DMA_C2DSTADDR_OFFSET (0x304)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x308 : DMA_C2LLI */
#define DMA_C2LLI_OFFSET (0x308)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x30C : DMA_C2Control */
#define DMA_C2CONTROL_OFFSET  (0x30C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x310 : DMA_C3Config */
#define DMA_C3CONFIG_OFFSET    (0x310)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))

/* 0x31C : DMA_C3RSVD */
#define DMA_C3RSVD_OFFSET    (0x31C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

/* 0x500 : DMA_C4SrcAddr */
#define DMA_C4SRCADDR_OFFSET (0x500)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x504 : DMA_C4DstAddr */
#define DMA_C4DSTADDR_OFFSET (0x504)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x508 : DMA_C4LLI */
#define DMA_C4LLI_OFFSET (0x508)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x50C : DMA_C4Control */
#define DMA_C4CONTROL_OFFSET  (0x50C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x510 : DMA_C4Config */
#define DMA_C4CONFIG_OFFSET    (0x510)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))

/* 0x51C : DMA_C4RSVD */
#define DMA_C4RSVD_OFFSET    (0x51C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

/* 0x600 : DMA_C5SrcAddr */
#define DMA_C5SRCADDR_OFFSET (0x600)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x604 : DMA_C5DstAddr */
#define DMA_C5DSTADDR_OFFSET (0x604)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x608 : DMA_C5LLI */
#define DMA_C5LLI_OFFSET (0x608)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x60C : DMA_C5Control */
#define DMA_C5CONTROL_OFFSET  (0x60C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x610 : DMA_C5Config */
#define DMA_C5CONFIG_OFFSET    (0x610)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))

/* 0x61C : DMA_C5RSVD */
#define DMA_C5RSVD_OFFSET    (0x61C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

/* 0x700 : DMA_C6SrcAddr */
#define DMA_C6SRCADDR_OFFSET (0x700)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x704 : DMA_C6DstAddr */
#define DMA_C6DSTADDR_OFFSET (0x704)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x708 : DMA_C6LLI */
#define DMA_C6LLI_OFFSET (0x708)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x70C : DMA_C6Control */
#define DMA_C6CONTROL_OFFSET  (0x70C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x710 : DMA_C6Config */
#define DMA_C6CONFIG_OFFSET    (0x710)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))

/* 0x71C : DMA_C6RSVD */
#define DMA_C6RSVD_OFFSET    (0x71C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

/* 0x800 : DMA_C7SrcAddr */
#define DMA_C7SRCADDR_OFFSET (0x800)
#define DMA_SRCADDR          DMA_SRCADDR
#define DMA_SRCADDR_POS      (0U)
#define DMA_SRCADDR_LEN      (32U)
#define DMA_SRCADDR_MSK      (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK     (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x804 : DMA_C7DstAddr */
#define DMA_C7DSTADDR_OFFSET (0x804)
#define DMA_DSTADDR          DMA_DSTADDR
#define DMA_DSTADDR_POS      (0U)
#define DMA_DSTADDR_LEN      (32U)
#define DMA_DSTADDR_MSK      (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK     (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x808 : DMA_C7LLI */
#define DMA_C7LLI_OFFSET (0x808)
#define DMA_LLI          DMA_LLI
#define DMA_LLI_POS      (0U)
#define DMA_LLI_LEN      (32U)
#define DMA_LLI_MSK      (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK     (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0x80C : DMA_C7Control */
#define DMA_C7CONTROL_OFFSET  (0x80C)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x810 : DMA_C7Config */
#define DMA_C7CONFIG_OFFSET    (0x810)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))

/* 0x81C : DMA_C7RSVD */
#define DMA_C7RSVD_OFFSET    (0x81C)
#define DMA_DSTREMNSGLE      DMA_DSTREMNSGLE
#define DMA_DSTREMNSGLE_POS  (3U)
#define DMA_DSTREMNSGLE_LEN  (1U)
#define DMA_DSTREMNSGLE_MSK  (((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS)
#define DMA_DSTREMNSGLE_UMSK (~(((1U << DMA_DSTREMNSGLE_LEN) - 1) << DMA_DSTREMNSGLE_POS))
#define DMA_SRCREMNSGLE      DMA_SRCREMNSGLE
#define DMA_SRCREMNSGLE_POS  (4U)
#define DMA_SRCREMNSGLE_LEN  (1U)
#define DMA_SRCREMNSGLE_MSK  (((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS)
#define DMA_SRCREMNSGLE_UMSK (~(((1U << DMA_SRCREMNSGLE_LEN) - 1) << DMA_SRCREMNSGLE_POS))

struct dma_reg {
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
            uint32_t IntTCClear    : 8;  /* [ 7: 0],          w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_IntTCClear;

    /* 0xC : DMA_IntErrorStatus */
    union {
        struct {
            uint32_t IntErrorStatus : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31  : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_IntErrorStatus;

    /* 0x10 : DMA_IntErrClr */
    union {
        struct {
            uint32_t IntErrClr     : 8;  /* [ 7: 0],          w,        0x0 */
            uint32_t reserved_8_31 : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_IntErrClr;

    /* 0x14 : DMA_RawIntTCStatus */
    union {
        struct {
            uint32_t RawIntTCStatus : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31  : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_RawIntTCStatus;

    /* 0x18 : DMA_RawIntErrorStatus */
    union {
        struct {
            uint32_t RawIntErrorStatus : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_RawIntErrorStatus;

    /* 0x1C : DMA_EnbldChns */
    union {
        struct {
            uint32_t EnabledChannels : 8;  /* [ 7: 0],          r,        0x0 */
            uint32_t reserved_8_31   : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_EnbldChns;

    /* 0x20 : DMA_SoftBReq */
    union {
        struct {
            uint32_t SoftBReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftBReq;

    /* 0x24 : DMA_SoftSReq */
    union {
        struct {
            uint32_t SoftSReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftSReq;

    /* 0x28 : DMA_SoftLBReq */
    union {
        struct {
            uint32_t SoftLBReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftLBReq;

    /* 0x2C : DMA_SoftLSReq */
    union {
        struct {
            uint32_t SoftLSReq : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SoftLSReq;

    /* 0x30 : DMA_Top_Config */
    union {
        struct {
            uint32_t E             : 1;  /* [    0],        r/w,        0x0 */
            uint32_t M             : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_31 : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_Top_Config;

    /* 0x34 : DMA_Sync */
    union {
        struct {
            uint32_t DMA_Sync : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_Sync;

    /* 0x38  reserved */
    uint8_t RESERVED0x38[200];

    /* 0x100 : DMA_C0SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C0SrcAddr;

    /* 0x104 : DMA_C0DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C0DstAddr;

    /* 0x108 : DMA_C0LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C0LLI;

    /* 0x10C : DMA_C0Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C0Control;

    /* 0x110 : DMA_C0Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19    : 1;  /* [   19],       rsvd,        0x0 */
            uint32_t LLICounter     : 10; /* [29:20],          r,        0x0 */
            uint32_t reserved_30_31 : 2;  /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C0Config;

    /* 0x114  reserved */
    uint8_t RESERVED0x114[8];

    /* 0x11C : DMA_C0RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C0RSVD;

    /* 0x120  reserved */
    uint8_t RESERVED0x120[224];

    /* 0x200 : DMA_C1SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C1SrcAddr;

    /* 0x204 : DMA_C1DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C1DstAddr;

    /* 0x208 : DMA_C1LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C1LLI;

    /* 0x20C : DMA_C1Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C1Control;

    /* 0x210 : DMA_C1Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C1Config;

    /* 0x214  reserved */
    uint8_t RESERVED0x214[8];

    /* 0x21C : DMA_C1RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C1RSVD;

    /* 0x220  reserved */
    uint8_t RESERVED0x220[224];

    /* 0x300 : DMA_C2SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C2SrcAddr;

    /* 0x304 : DMA_C2DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C2DstAddr;

    /* 0x308 : DMA_C2LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C2LLI;

    /* 0x30C : DMA_C2Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C2Control;

    /* 0x310 : DMA_C3Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C3Config;

    /* 0x314  reserved */
    uint8_t RESERVED0x314[8];

    /* 0x31C : DMA_C3RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C3RSVD;

    /* 0x320  reserved */
    uint8_t RESERVED0x320[480];

    /* 0x500 : DMA_C4SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C4SrcAddr;

    /* 0x504 : DMA_C4DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C4DstAddr;

    /* 0x508 : DMA_C4LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C4LLI;

    /* 0x50C : DMA_C4Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C4Control;

    /* 0x510 : DMA_C4Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C4Config;

    /* 0x514  reserved */
    uint8_t RESERVED0x514[8];

    /* 0x51C : DMA_C4RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C4RSVD;

    /* 0x520  reserved */
    uint8_t RESERVED0x520[224];

    /* 0x600 : DMA_C5SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C5SrcAddr;

    /* 0x604 : DMA_C5DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C5DstAddr;

    /* 0x608 : DMA_C5LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C5LLI;

    /* 0x60C : DMA_C5Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C5Control;

    /* 0x610 : DMA_C5Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C5Config;

    /* 0x614  reserved */
    uint8_t RESERVED0x614[8];

    /* 0x61C : DMA_C5RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C5RSVD;

    /* 0x620  reserved */
    uint8_t RESERVED0x620[224];

    /* 0x700 : DMA_C6SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C6SrcAddr;

    /* 0x704 : DMA_C6DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C6DstAddr;

    /* 0x708 : DMA_C6LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C6LLI;

    /* 0x70C : DMA_C6Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C6Control;

    /* 0x710 : DMA_C6Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C6Config;

    /* 0x714  reserved */
    uint8_t RESERVED0x714[8];

    /* 0x71C : DMA_C6RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C6RSVD;

    /* 0x720  reserved */
    uint8_t RESERVED0x720[224];

    /* 0x800 : DMA_C7SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C7SrcAddr;

    /* 0x804 : DMA_C7DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C7DstAddr;

    /* 0x808 : DMA_C7LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C7LLI;

    /* 0x80C : DMA_C7Control */
    union {
        struct {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C7Control;

    /* 0x810 : DMA_C7Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19_31 : 13; /* [31:19],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C7Config;

    /* 0x814  reserved */
    uint8_t RESERVED0x814[8];

    /* 0x81C : DMA_C7RSVD */
    union {
        struct {
            uint32_t reserved_0_2  : 3;  /* [ 2: 0],       rsvd,        0x0 */
            uint32_t DstRemnSgle   : 1;  /* [    3],        r/w,        0x0 */
            uint32_t SrcRemnSgle   : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_C7RSVD;
};

typedef volatile struct dma_reg dma_reg_t;

/*Following is reg patch*/

/* 0x0 : DMA_SrcAddr */
#define DMA_SRCADDR_OFFSET (0x0)
#define DMA_SRCADDR        DMA_SRCADDR
#define DMA_SRCADDR_POS    (0U)
#define DMA_SRCADDR_LEN    (32U)
#define DMA_SRCADDR_MSK    (((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS)
#define DMA_SRCADDR_UMSK   (~(((1U << DMA_SRCADDR_LEN) - 1) << DMA_SRCADDR_POS))

/* 0x4 : DMA_DstAddr */
#define DMA_DSTADDR_OFFSET (0x4)
#define DMA_DSTADDR        DMA_DSTADDR
#define DMA_DSTADDR_POS    (0U)
#define DMA_DSTADDR_LEN    (32U)
#define DMA_DSTADDR_MSK    (((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS)
#define DMA_DSTADDR_UMSK   (~(((1U << DMA_DSTADDR_LEN) - 1) << DMA_DSTADDR_POS))

/* 0x8 : DMA_LLI */
#define DMA_LLI_OFFSET (0x8)
#define DMA_LLI        DMA_LLI
#define DMA_LLI_POS    (0U)
#define DMA_LLI_LEN    (32U)
#define DMA_LLI_MSK    (((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS)
#define DMA_LLI_UMSK   (~(((1U << DMA_LLI_LEN) - 1) << DMA_LLI_POS))

/* 0xc : DMA_Control */
#define DMA_CONTROL_OFFSET    (0xc)
#define DMA_TRANSFERSIZE      DMA_TRANSFERSIZE
#define DMA_TRANSFERSIZE_POS  (0U)
#define DMA_TRANSFERSIZE_LEN  (12U)
#define DMA_TRANSFERSIZE_MSK  (((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS)
#define DMA_TRANSFERSIZE_UMSK (~(((1U << DMA_TRANSFERSIZE_LEN) - 1) << DMA_TRANSFERSIZE_POS))
#define DMA_SBSIZE            DMA_SBSIZE
#define DMA_SBSIZE_POS        (12U)
#define DMA_SBSIZE_LEN        (2U)
#define DMA_SBSIZE_MSK        (((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS)
#define DMA_SBSIZE_UMSK       (~(((1U << DMA_SBSIZE_LEN) - 1) << DMA_SBSIZE_POS))
#define DMA_DST_MIN_MODE      DMA_DST_MIN_MODE
#define DMA_DST_MIN_MODE_POS  (14U)
#define DMA_DST_MIN_MODE_LEN  (1U)
#define DMA_DST_MIN_MODE_MSK  (((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS)
#define DMA_DST_MIN_MODE_UMSK (~(((1U << DMA_DST_MIN_MODE_LEN) - 1) << DMA_DST_MIN_MODE_POS))
#define DMA_DBSIZE            DMA_DBSIZE
#define DMA_DBSIZE_POS        (15U)
#define DMA_DBSIZE_LEN        (2U)
#define DMA_DBSIZE_MSK        (((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS)
#define DMA_DBSIZE_UMSK       (~(((1U << DMA_DBSIZE_LEN) - 1) << DMA_DBSIZE_POS))
#define DMA_DST_ADD_MODE      DMA_DST_ADD_MODE
#define DMA_DST_ADD_MODE_POS  (17U)
#define DMA_DST_ADD_MODE_LEN  (1U)
#define DMA_DST_ADD_MODE_MSK  (((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS)
#define DMA_DST_ADD_MODE_UMSK (~(((1U << DMA_DST_ADD_MODE_LEN) - 1) << DMA_DST_ADD_MODE_POS))
#define DMA_SWIDTH            DMA_SWIDTH
#define DMA_SWIDTH_POS        (18U)
#define DMA_SWIDTH_LEN        (2U)
#define DMA_SWIDTH_MSK        (((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS)
#define DMA_SWIDTH_UMSK       (~(((1U << DMA_SWIDTH_LEN) - 1) << DMA_SWIDTH_POS))
#define DMA_DWIDTH            DMA_DWIDTH
#define DMA_DWIDTH_POS        (21U)
#define DMA_DWIDTH_LEN        (2U)
#define DMA_DWIDTH_MSK        (((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS)
#define DMA_DWIDTH_UMSK       (~(((1U << DMA_DWIDTH_LEN) - 1) << DMA_DWIDTH_POS))
#define DMA_FIX_CNT           DMA_FIX_CNT
#define DMA_FIX_CNT_POS       (23U)
#define DMA_FIX_CNT_LEN       (3U)
#define DMA_FIX_CNT_MSK       (((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS)
#define DMA_FIX_CNT_UMSK      (~(((1U << DMA_FIX_CNT_LEN) - 1) << DMA_FIX_CNT_POS))
#define DMA_SI                DMA_SI
#define DMA_SI_POS            (26U)
#define DMA_SI_LEN            (1U)
#define DMA_SI_MSK            (((1U << DMA_SI_LEN) - 1) << DMA_SI_POS)
#define DMA_SI_UMSK           (~(((1U << DMA_SI_LEN) - 1) << DMA_SI_POS))
#define DMA_DI                DMA_DI
#define DMA_DI_POS            (27U)
#define DMA_DI_LEN            (1U)
#define DMA_DI_MSK            (((1U << DMA_DI_LEN) - 1) << DMA_DI_POS)
#define DMA_DI_UMSK           (~(((1U << DMA_DI_LEN) - 1) << DMA_DI_POS))
#define DMA_PROT              DMA_PROT
#define DMA_PROT_POS          (28U)
#define DMA_PROT_LEN          (3U)
#define DMA_PROT_MSK          (((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS)
#define DMA_PROT_UMSK         (~(((1U << DMA_PROT_LEN) - 1) << DMA_PROT_POS))
#define DMA_I                 DMA_I
#define DMA_I_POS             (31U)
#define DMA_I_LEN             (1U)
#define DMA_I_MSK             (((1U << DMA_I_LEN) - 1) << DMA_I_POS)
#define DMA_I_UMSK            (~(((1U << DMA_I_LEN) - 1) << DMA_I_POS))

/* 0x10 : DMA_Config */
#define DMA_CONFIG_OFFSET      (0x10)
#define DMA_E                  DMA_E
#define DMA_E_POS              (0U)
#define DMA_E_LEN              (1U)
#define DMA_E_MSK              (((1U << DMA_E_LEN) - 1) << DMA_E_POS)
#define DMA_E_UMSK             (~(((1U << DMA_E_LEN) - 1) << DMA_E_POS))
#define DMA_SRCPERIPHERAL      DMA_SRCPERIPHERAL
#define DMA_SRCPERIPHERAL_POS  (1U)
#define DMA_SRCPERIPHERAL_LEN  (5U)
#define DMA_SRCPERIPHERAL_MSK  (((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS)
#define DMA_SRCPERIPHERAL_UMSK (~(((1U << DMA_SRCPERIPHERAL_LEN) - 1) << DMA_SRCPERIPHERAL_POS))
#define DMA_DSTPERIPHERAL      DMA_DSTPERIPHERAL
#define DMA_DSTPERIPHERAL_POS  (6U)
#define DMA_DSTPERIPHERAL_LEN  (5U)
#define DMA_DSTPERIPHERAL_MSK  (((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS)
#define DMA_DSTPERIPHERAL_UMSK (~(((1U << DMA_DSTPERIPHERAL_LEN) - 1) << DMA_DSTPERIPHERAL_POS))
#define DMA_FLOWCNTRL          DMA_FLOWCNTRL
#define DMA_FLOWCNTRL_POS      (11U)
#define DMA_FLOWCNTRL_LEN      (3U)
#define DMA_FLOWCNTRL_MSK      (((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS)
#define DMA_FLOWCNTRL_UMSK     (~(((1U << DMA_FLOWCNTRL_LEN) - 1) << DMA_FLOWCNTRL_POS))
#define DMA_IE                 DMA_IE
#define DMA_IE_POS             (14U)
#define DMA_IE_LEN             (1U)
#define DMA_IE_MSK             (((1U << DMA_IE_LEN) - 1) << DMA_IE_POS)
#define DMA_IE_UMSK            (~(((1U << DMA_IE_LEN) - 1) << DMA_IE_POS))
#define DMA_ITC                DMA_ITC
#define DMA_ITC_POS            (15U)
#define DMA_ITC_LEN            (1U)
#define DMA_ITC_MSK            (((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS)
#define DMA_ITC_UMSK           (~(((1U << DMA_ITC_LEN) - 1) << DMA_ITC_POS))
#define DMA_L                  DMA_L
#define DMA_L_POS              (16U)
#define DMA_L_LEN              (1U)
#define DMA_L_MSK              (((1U << DMA_L_LEN) - 1) << DMA_L_POS)
#define DMA_L_UMSK             (~(((1U << DMA_L_LEN) - 1) << DMA_L_POS))
#define DMA_A                  DMA_A
#define DMA_A_POS              (17U)
#define DMA_A_LEN              (1U)
#define DMA_A_MSK              (((1U << DMA_A_LEN) - 1) << DMA_A_POS)
#define DMA_A_UMSK             (~(((1U << DMA_A_LEN) - 1) << DMA_A_POS))
#define DMA_H                  DMA_H
#define DMA_H_POS              (18U)
#define DMA_H_LEN              (1U)
#define DMA_H_MSK              (((1U << DMA_H_LEN) - 1) << DMA_H_POS)
#define DMA_H_UMSK             (~(((1U << DMA_H_LEN) - 1) << DMA_H_POS))
#define DMA_LLICOUNTER         DMA_LLICOUNTER
#define DMA_LLICOUNTER_POS     (20U)
#define DMA_LLICOUNTER_LEN     (10U)
#define DMA_LLICOUNTER_MSK     (((1U << DMA_LLICOUNTER_LEN) - 1) << DMA_LLICOUNTER_POS)
#define DMA_LLICOUNTER_UMSK    (~(((1U << DMA_LLICOUNTER_LEN) - 1) << DMA_LLICOUNTER_POS))

struct dma_channel_reg {
    /* 0x0 : DMA_SrcAddr */
    union {
        struct {
            uint32_t SrcAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_SrcAddr;

    /* 0x4 : DMA_DstAddr */
    union {
        struct {
            uint32_t DstAddr : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_DstAddr;

    /* 0x8 : DMA_LLI */
    union {
        struct {
            uint32_t LLI : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_LLI;

    /* 0xc : DMA_Control */
    union {
        struct DMA_Control_Reg {
            uint32_t TransferSize : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t SBSize       : 2;  /* [13:12],        r/w,        0x1 */
            uint32_t dst_min_mode : 1;  /* [   14],        r/w,        0x0 */
            uint32_t DBSize       : 2;  /* [16:15],        r/w,        0x1 */
            uint32_t dst_add_mode : 1;  /* [   17],        r/w,        0x0 */
            uint32_t SWidth       : 2;  /* [19:18],        r/w,        0x2 */
            uint32_t reserved_20  : 1;  /* [   20],       rsvd,        0x0 */
            uint32_t DWidth       : 2;  /* [22:21],        r/w,        0x2 */
            uint32_t fix_cnt      : 3;  /* [25:23],        r/w,        0x0 */
            uint32_t SI           : 1;  /* [   26],        r/w,        0x1 */
            uint32_t DI           : 1;  /* [   27],        r/w,        0x1 */
            uint32_t Prot         : 3;  /* [30:28],        r/w,        0x0 */
            uint32_t I            : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_Control;

    /* 0x10 : DMA_Config */
    union {
        struct {
            uint32_t E              : 1;  /* [    0],        r/w,        0x0 */
            uint32_t SrcPeripheral  : 5;  /* [ 5: 1],        r/w,        0x0 */
            uint32_t DstPeripheral  : 5;  /* [10: 6],        r/w,        0x0 */
            uint32_t FlowCntrl      : 3;  /* [13:11],        r/w,        0x0 */
            uint32_t IE             : 1;  /* [   14],        r/w,        0x0 */
            uint32_t ITC            : 1;  /* [   15],        r/w,        0x0 */
            uint32_t L              : 1;  /* [   16],        r/w,        0x0 */
            uint32_t A              : 1;  /* [   17],          r,        0x0 */
            uint32_t H              : 1;  /* [   18],        r/w,        0x0 */
            uint32_t reserved_19    : 1;  /* [   19],       rsvd,        0x0 */
            uint32_t LLICounter     : 10; /* [29:20],          r,        0x0 */
            uint32_t reserved_30_31 : 2;  /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } DMA_Config;
};

typedef volatile struct dma_channel_reg dma_channel_reg_t;

#define DMA_CHANNEL_OFFSET 0x100

#endif /* __DMA_REG_H__ */
