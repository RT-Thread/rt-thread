/**
  ******************************************************************************
  * @file    dma_reg.h
  * @version V1.0
  * @date    2022-06-20
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
#ifndef __HARDWARE_DMA_H__
#define __HARDWARE_DMA_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define DMA_INTSTATUS_OFFSET         (0x0)  /* DMA_IntStatus */
#define DMA_INTTCSTATUS_OFFSET       (0x4)  /* DMA_IntTCStatus */
#define DMA_INTTCCLEAR_OFFSET        (0x8)  /* DMA_IntTCClear */
#define DMA_INTERRORSTATUS_OFFSET    (0xC)  /* DMA_IntErrorStatus */
#define DMA_INTERRCLR_OFFSET         (0x10) /* DMA_IntErrClr */
#define DMA_RAWINTTCSTATUS_OFFSET    (0x14) /* DMA_RawIntTCStatus */
#define DMA_RAWINTERRORSTATUS_OFFSET (0x18) /* DMA_RawIntErrorStatus */
#define DMA_ENBLDCHNS_OFFSET         (0x1C) /* DMA_EnbldChns */
#define DMA_SOFTBREQ_OFFSET          (0x20) /* DMA_SoftBReq */
#define DMA_SOFTSREQ_OFFSET          (0x24) /* DMA_SoftSReq */
#define DMA_SOFTLBREQ_OFFSET         (0x28) /* DMA_SoftLBReq */
#define DMA_SOFTLSREQ_OFFSET         (0x2C) /* DMA_SoftLSReq */
#define DMA_TOP_CONFIG_OFFSET        (0x30) /* DMA_Top_Config */
#define DMA_SYNC_OFFSET              (0x34) /* DMA_Sync */

#define DMA_CxSRCADDR_OFFSET (0x00) /* DMA_CxSrcAddr */
#define DMA_CxDSTADDR_OFFSET (0x04) /* DMA_CxDstAddr */
#define DMA_CxLLI_OFFSET     (0x08) /* DMA_CxLLI */
#define DMA_CxCONTROL_OFFSET (0x0C) /* DMA_CxControl */
#define DMA_CxCONFIG_OFFSET  (0x10) /* DMA_CxConfig */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : DMA_IntStatus */
#define DMA_INTSTATUS_SHIFT (0U)
#define DMA_INTSTATUS_MASK  (0xff << DMA_INTSTATUS_SHIFT)

/* 0x4 : DMA_IntTCStatus */
#define DMA_INTTCSTATUS_SHIFT (0U)
#define DMA_INTTCSTATUS_MASK  (0xff << DMA_INTTCSTATUS_SHIFT)

/* 0x8 : DMA_IntTCClear */
#define DMA_INTTCCLEAR_SHIFT (0U)
#define DMA_INTTCCLEAR_MASK  (0xff << DMA_INTTCCLEAR_SHIFT)

/* 0xC : DMA_IntErrorStatus */
#define DMA_INTERRORSTATUS_SHIFT (0U)
#define DMA_INTERRORSTATUS_MASK  (0xff << DMA_INTERRORSTATUS_SHIFT)

/* 0x10 : DMA_IntErrClr */
#define DMA_INTERRCLR_SHIFT (0U)
#define DMA_INTERRCLR_MASK  (0xff << DMA_INTERRCLR_SHIFT)

/* 0x14 : DMA_RawIntTCStatus */
#define DMA_RAWINTTCSTATUS_SHIFT (0U)
#define DMA_RAWINTTCSTATUS_MASK  (0xff << DMA_RAWINTTCSTATUS_SHIFT)

/* 0x18 : DMA_RawIntErrorStatus */
#define DMA_RAWINTERRORSTATUS_SHIFT (0U)
#define DMA_RAWINTERRORSTATUS_MASK  (0xff << DMA_RAWINTERRORSTATUS_SHIFT)

/* 0x1C : DMA_EnbldChns */
#define DMA_ENABLEDCHANNELS_SHIFT (0U)
#define DMA_ENABLEDCHANNELS_MASK  (0xff << DMA_ENABLEDCHANNELS_SHIFT)

/* 0x20 : DMA_SoftBReq */
#define DMA_SOFTBREQ_SHIFT (0U)
#define DMA_SOFTBREQ_MASK  (0xffffffff << DMA_SOFTBREQ_SHIFT)

/* 0x24 : DMA_SoftSReq */
#define DMA_SOFTSREQ_SHIFT (0U)
#define DMA_SOFTSREQ_MASK  (0xffffffff << DMA_SOFTSREQ_SHIFT)

/* 0x28 : DMA_SoftLBReq */
#define DMA_SOFTLBREQ_SHIFT (0U)
#define DMA_SOFTLBREQ_MASK  (0xffffffff << DMA_SOFTLBREQ_SHIFT)

/* 0x2C : DMA_SoftLSReq */
#define DMA_SOFTLSREQ_SHIFT (0U)
#define DMA_SOFTLSREQ_MASK  (0xffffffff << DMA_SOFTLSREQ_SHIFT)

/* 0x30 : DMA_Top_Config */
#define DMA_E (1 << 0U)
#define DMA_M (1 << 1U)

/* 0x34 : DMA_Sync */
#define DMA_SYNC_SHIFT (0U)
#define DMA_SYNC_MASK  (0xffffffff << DMA_SYNC_SHIFT)

/* 0x100 : DMA_CxSrcAddr */
#define DMA_SRCADDR_SHIFT (0U)
#define DMA_SRCADDR_MASK  (0xffffffff << DMA_SRCADDR_SHIFT)

/* 0x104 : DMA_CxDstAddr */
#define DMA_DSTADDR_SHIFT (0U)
#define DMA_DSTADDR_MASK  (0xffffffff << DMA_DSTADDR_SHIFT)

/* 0x108 : DMA_CxLLI */
#define DMA_LLI_SHIFT (0U)
#define DMA_LLI_MASK  (0xffffffff << DMA_LLI_SHIFT)

/* 0x10C : DMA_CxControl */
#define DMA_TRANSFERSIZE_SHIFT (0U)
#define DMA_TRANSFERSIZE_MASK  (0xfff << DMA_TRANSFERSIZE_SHIFT)
#define DMA_SBSIZE_SHIFT       (12U)
#if defined(BL602)
#define DMA_SBSIZE_MASK        (0x7 << DMA_SBSIZE_SHIFT)
#else
#define DMA_SBSIZE_MASK        (0x3 << DMA_SBSIZE_SHIFT)
#define DMA_DST_MIN_MODE       (1 << 14U)
#endif
#define DMA_DBSIZE_SHIFT       (15U)
#if defined(BL602)
#define DMA_DBSIZE_MASK        (0x7 << DMA_DBSIZE_SHIFT)
#else
#define DMA_DBSIZE_MASK        (0x3 << DMA_DBSIZE_SHIFT)
#define DMA_DST_ADD_MODE       (1 << 17U)
#endif
#define DMA_SWIDTH_SHIFT       (18U)
#if defined(BL602)
#define DMA_SWIDTH_MASK        (0x7 << DMA_SWIDTH_SHIFT)
#else
#define DMA_SWIDTH_MASK        (0x3 << DMA_SWIDTH_SHIFT)
#endif
#define DMA_DWIDTH_SHIFT       (21U)
#if defined(BL602)
#define DMA_DWIDTH_MASK        (0x7 << DMA_DWIDTH_SHIFT)
#define DMA_SLARGERD           (1 << 24U)
#else
#define DMA_DWIDTH_MASK        (0x3 << DMA_DWIDTH_SHIFT)
#define DMA_FIX_CNT_SHIFT      (23U)
#define DMA_FIX_CNT_MASK       (0x7 << DMA_FIX_CNT_SHIFT)
#endif
#define DMA_SI                 (1 << 26U)
#define DMA_DI                 (1 << 27U)
#define DMA_PROT_SHIFT         (28U)
#define DMA_PROT_MASK          (0x7 << DMA_PROT_SHIFT)
#define DMA_I                  (1 << 31U)

/* 0x110 : DMA_CxConfig */
#define DMA_E                   (1 << 0U)
#define DMA_SRCPERIPHERAL_SHIFT (1U)
#define DMA_SRCPERIPHERAL_MASK  (0x1f << DMA_SRCPERIPHERAL_SHIFT)
#define DMA_DSTPERIPHERAL_SHIFT (6U)
#define DMA_DSTPERIPHERAL_MASK  (0x1f << DMA_DSTPERIPHERAL_SHIFT)
#define DMA_FLOWCNTRL_SHIFT     (11U)
#define DMA_FLOWCNTRL_MASK      (0x7 << DMA_FLOWCNTRL_SHIFT)
#define DMA_IE                  (1 << 14U)
#define DMA_ITC                 (1 << 15U)
#define DMA_L                   (1 << 16U)
#define DMA_A                   (1 << 17U)
#define DMA_H                   (1 << 18U)
#define DMA_LLICOUNTER_SHIFT    (20U)
#define DMA_LLICOUNTER_MASK     (0x3ff << DMA_LLICOUNTER_SHIFT)

#endif /* __HARDWARE_DMA_H__ */
