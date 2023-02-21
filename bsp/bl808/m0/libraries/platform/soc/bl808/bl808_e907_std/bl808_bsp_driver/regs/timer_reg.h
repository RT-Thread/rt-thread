/**
  ******************************************************************************
  * @file    timer_reg.h
  * @version V1.0
  * @date    2022-03-03
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
#ifndef __TIMER_REG_H__
#define __TIMER_REG_H__

#include "bl808.h"

/* 0x0 : Timer Clock Source */
#define TIMER_TCCR_OFFSET  (0x0)
#define TIMER_CS_2         TIMER_CS_2
#define TIMER_CS_2_POS     (0U)
#define TIMER_CS_2_LEN     (4U)
#define TIMER_CS_2_MSK     (((1U << TIMER_CS_2_LEN) - 1) << TIMER_CS_2_POS)
#define TIMER_CS_2_UMSK    (~(((1U << TIMER_CS_2_LEN) - 1) << TIMER_CS_2_POS))
#define TIMER_CS_3         TIMER_CS_3
#define TIMER_CS_3_POS     (4U)
#define TIMER_CS_3_LEN     (4U)
#define TIMER_CS_3_MSK     (((1U << TIMER_CS_3_LEN) - 1) << TIMER_CS_3_POS)
#define TIMER_CS_3_UMSK    (~(((1U << TIMER_CS_3_LEN) - 1) << TIMER_CS_3_POS))
#define TIMER_CS_WDT       TIMER_CS_WDT
#define TIMER_CS_WDT_POS   (8U)
#define TIMER_CS_WDT_LEN   (4U)
#define TIMER_CS_WDT_MSK   (((1U << TIMER_CS_WDT_LEN) - 1) << TIMER_CS_WDT_POS)
#define TIMER_CS_WDT_UMSK  (~(((1U << TIMER_CS_WDT_LEN) - 1) << TIMER_CS_WDT_POS))
#define TIMER_TMR_RSV      TIMER_TMR_RSV
#define TIMER_TMR_RSV_POS  (16U)
#define TIMER_TMR_RSV_LEN  (8U)
#define TIMER_TMR_RSV_MSK  (((1U << TIMER_TMR_RSV_LEN) - 1) << TIMER_TMR_RSV_POS)
#define TIMER_TMR_RSV_UMSK (~(((1U << TIMER_TMR_RSV_LEN) - 1) << TIMER_TMR_RSV_POS))
#define TIMER_ID           TIMER_ID
#define TIMER_ID_POS       (24U)
#define TIMER_ID_LEN       (8U)
#define TIMER_ID_MSK       (((1U << TIMER_ID_LEN) - 1) << TIMER_ID_POS)
#define TIMER_ID_UMSK      (~(((1U << TIMER_ID_LEN) - 1) << TIMER_ID_POS))

/* 0x10 : Timer2 Match Value 0 */
#define TIMER_TMR2_0_OFFSET (0x10)
#define TIMER_TMR2_0        TIMER_TMR2_0
#define TIMER_TMR2_0_POS    (0U)
#define TIMER_TMR2_0_LEN    (32U)
#define TIMER_TMR2_0_MSK    (((1U << TIMER_TMR2_0_LEN) - 1) << TIMER_TMR2_0_POS)
#define TIMER_TMR2_0_UMSK   (~(((1U << TIMER_TMR2_0_LEN) - 1) << TIMER_TMR2_0_POS))

/* 0x14 : Timer2 Match Value 1 */
#define TIMER_TMR2_1_OFFSET (0x14)
#define TIMER_TMR2_1        TIMER_TMR2_1
#define TIMER_TMR2_1_POS    (0U)
#define TIMER_TMR2_1_LEN    (32U)
#define TIMER_TMR2_1_MSK    (((1U << TIMER_TMR2_1_LEN) - 1) << TIMER_TMR2_1_POS)
#define TIMER_TMR2_1_UMSK   (~(((1U << TIMER_TMR2_1_LEN) - 1) << TIMER_TMR2_1_POS))

/* 0x18 : Timer2 Match Value 2 */
#define TIMER_TMR2_2_OFFSET (0x18)
#define TIMER_TMR2_2        TIMER_TMR2_2
#define TIMER_TMR2_2_POS    (0U)
#define TIMER_TMR2_2_LEN    (32U)
#define TIMER_TMR2_2_MSK    (((1U << TIMER_TMR2_2_LEN) - 1) << TIMER_TMR2_2_POS)
#define TIMER_TMR2_2_UMSK   (~(((1U << TIMER_TMR2_2_LEN) - 1) << TIMER_TMR2_2_POS))

/* 0x1C : Timer3 Match Value 0 */
#define TIMER_TMR3_0_OFFSET (0x1C)
#define TIMER_TMR3_0        TIMER_TMR3_0
#define TIMER_TMR3_0_POS    (0U)
#define TIMER_TMR3_0_LEN    (32U)
#define TIMER_TMR3_0_MSK    (((1U << TIMER_TMR3_0_LEN) - 1) << TIMER_TMR3_0_POS)
#define TIMER_TMR3_0_UMSK   (~(((1U << TIMER_TMR3_0_LEN) - 1) << TIMER_TMR3_0_POS))

/* 0x20 : Timer3 Match Value 1 */
#define TIMER_TMR3_1_OFFSET (0x20)
#define TIMER_TMR3_1        TIMER_TMR3_1
#define TIMER_TMR3_1_POS    (0U)
#define TIMER_TMR3_1_LEN    (32U)
#define TIMER_TMR3_1_MSK    (((1U << TIMER_TMR3_1_LEN) - 1) << TIMER_TMR3_1_POS)
#define TIMER_TMR3_1_UMSK   (~(((1U << TIMER_TMR3_1_LEN) - 1) << TIMER_TMR3_1_POS))

/* 0x24 : Timer3 Match Value 2 */
#define TIMER_TMR3_2_OFFSET (0x24)
#define TIMER_TMR3_2        TIMER_TMR3_2
#define TIMER_TMR3_2_POS    (0U)
#define TIMER_TMR3_2_LEN    (32U)
#define TIMER_TMR3_2_MSK    (((1U << TIMER_TMR3_2_LEN) - 1) << TIMER_TMR3_2_POS)
#define TIMER_TMR3_2_UMSK   (~(((1U << TIMER_TMR3_2_LEN) - 1) << TIMER_TMR3_2_POS))

/* 0x2C : Timer2 Counter Value */
#define TIMER_TCR2_OFFSET   (0x2C)
#define TIMER_TCR2_CNT      TIMER_TCR2_CNT
#define TIMER_TCR2_CNT_POS  (0U)
#define TIMER_TCR2_CNT_LEN  (32U)
#define TIMER_TCR2_CNT_MSK  (((1U << TIMER_TCR2_CNT_LEN) - 1) << TIMER_TCR2_CNT_POS)
#define TIMER_TCR2_CNT_UMSK (~(((1U << TIMER_TCR2_CNT_LEN) - 1) << TIMER_TCR2_CNT_POS))

/* 0x30 : Timer3 Counter Value */
#define TIMER_TCR3_OFFSET   (0x30)
#define TIMER_TCR3_CNT      TIMER_TCR3_CNT
#define TIMER_TCR3_CNT_POS  (0U)
#define TIMER_TCR3_CNT_LEN  (32U)
#define TIMER_TCR3_CNT_MSK  (((1U << TIMER_TCR3_CNT_LEN) - 1) << TIMER_TCR3_CNT_POS)
#define TIMER_TCR3_CNT_UMSK (~(((1U << TIMER_TCR3_CNT_LEN) - 1) << TIMER_TCR3_CNT_POS))

/* 0x38 : Timer2 Match Status */
#define TIMER_TSR2_OFFSET (0x38)
#define TIMER_TSR2_0      TIMER_TSR2_0
#define TIMER_TSR2_0_POS  (0U)
#define TIMER_TSR2_0_LEN  (1U)
#define TIMER_TSR2_0_MSK  (((1U << TIMER_TSR2_0_LEN) - 1) << TIMER_TSR2_0_POS)
#define TIMER_TSR2_0_UMSK (~(((1U << TIMER_TSR2_0_LEN) - 1) << TIMER_TSR2_0_POS))
#define TIMER_TSR2_1      TIMER_TSR2_1
#define TIMER_TSR2_1_POS  (1U)
#define TIMER_TSR2_1_LEN  (1U)
#define TIMER_TSR2_1_MSK  (((1U << TIMER_TSR2_1_LEN) - 1) << TIMER_TSR2_1_POS)
#define TIMER_TSR2_1_UMSK (~(((1U << TIMER_TSR2_1_LEN) - 1) << TIMER_TSR2_1_POS))
#define TIMER_TSR2_2      TIMER_TSR2_2
#define TIMER_TSR2_2_POS  (2U)
#define TIMER_TSR2_2_LEN  (1U)
#define TIMER_TSR2_2_MSK  (((1U << TIMER_TSR2_2_LEN) - 1) << TIMER_TSR2_2_POS)
#define TIMER_TSR2_2_UMSK (~(((1U << TIMER_TSR2_2_LEN) - 1) << TIMER_TSR2_2_POS))

/* 0x3C : Timer3 Match Status */
#define TIMER_TSR3_OFFSET (0x3C)
#define TIMER_TSR3_0      TIMER_TSR3_0
#define TIMER_TSR3_0_POS  (0U)
#define TIMER_TSR3_0_LEN  (1U)
#define TIMER_TSR3_0_MSK  (((1U << TIMER_TSR3_0_LEN) - 1) << TIMER_TSR3_0_POS)
#define TIMER_TSR3_0_UMSK (~(((1U << TIMER_TSR3_0_LEN) - 1) << TIMER_TSR3_0_POS))
#define TIMER_TSR3_1      TIMER_TSR3_1
#define TIMER_TSR3_1_POS  (1U)
#define TIMER_TSR3_1_LEN  (1U)
#define TIMER_TSR3_1_MSK  (((1U << TIMER_TSR3_1_LEN) - 1) << TIMER_TSR3_1_POS)
#define TIMER_TSR3_1_UMSK (~(((1U << TIMER_TSR3_1_LEN) - 1) << TIMER_TSR3_1_POS))
#define TIMER_TSR3_2      TIMER_TSR3_2
#define TIMER_TSR3_2_POS  (2U)
#define TIMER_TSR3_2_LEN  (1U)
#define TIMER_TSR3_2_MSK  (((1U << TIMER_TSR3_2_LEN) - 1) << TIMER_TSR3_2_POS)
#define TIMER_TSR3_2_UMSK (~(((1U << TIMER_TSR3_2_LEN) - 1) << TIMER_TSR3_2_POS))

/* 0x44 : Timer2 Match Interrupt Enable */
#define TIMER_TIER2_OFFSET (0x44)
#define TIMER_TIER2_0      TIMER_TIER2_0
#define TIMER_TIER2_0_POS  (0U)
#define TIMER_TIER2_0_LEN  (1U)
#define TIMER_TIER2_0_MSK  (((1U << TIMER_TIER2_0_LEN) - 1) << TIMER_TIER2_0_POS)
#define TIMER_TIER2_0_UMSK (~(((1U << TIMER_TIER2_0_LEN) - 1) << TIMER_TIER2_0_POS))
#define TIMER_TIER2_1      TIMER_TIER2_1
#define TIMER_TIER2_1_POS  (1U)
#define TIMER_TIER2_1_LEN  (1U)
#define TIMER_TIER2_1_MSK  (((1U << TIMER_TIER2_1_LEN) - 1) << TIMER_TIER2_1_POS)
#define TIMER_TIER2_1_UMSK (~(((1U << TIMER_TIER2_1_LEN) - 1) << TIMER_TIER2_1_POS))
#define TIMER_TIER2_2      TIMER_TIER2_2
#define TIMER_TIER2_2_POS  (2U)
#define TIMER_TIER2_2_LEN  (1U)
#define TIMER_TIER2_2_MSK  (((1U << TIMER_TIER2_2_LEN) - 1) << TIMER_TIER2_2_POS)
#define TIMER_TIER2_2_UMSK (~(((1U << TIMER_TIER2_2_LEN) - 1) << TIMER_TIER2_2_POS))

/* 0x48 : Timer3 Match Interrupt Enable */
#define TIMER_TIER3_OFFSET (0x48)
#define TIMER_TIER3_0      TIMER_TIER3_0
#define TIMER_TIER3_0_POS  (0U)
#define TIMER_TIER3_0_LEN  (1U)
#define TIMER_TIER3_0_MSK  (((1U << TIMER_TIER3_0_LEN) - 1) << TIMER_TIER3_0_POS)
#define TIMER_TIER3_0_UMSK (~(((1U << TIMER_TIER3_0_LEN) - 1) << TIMER_TIER3_0_POS))
#define TIMER_TIER3_1      TIMER_TIER3_1
#define TIMER_TIER3_1_POS  (1U)
#define TIMER_TIER3_1_LEN  (1U)
#define TIMER_TIER3_1_MSK  (((1U << TIMER_TIER3_1_LEN) - 1) << TIMER_TIER3_1_POS)
#define TIMER_TIER3_1_UMSK (~(((1U << TIMER_TIER3_1_LEN) - 1) << TIMER_TIER3_1_POS))
#define TIMER_TIER3_2      TIMER_TIER3_2
#define TIMER_TIER3_2_POS  (2U)
#define TIMER_TIER3_2_LEN  (1U)
#define TIMER_TIER3_2_MSK  (((1U << TIMER_TIER3_2_LEN) - 1) << TIMER_TIER3_2_POS)
#define TIMER_TIER3_2_UMSK (~(((1U << TIMER_TIER3_2_LEN) - 1) << TIMER_TIER3_2_POS))

/* 0x50 : Timer2 Pre-Load Value */
#define TIMER_TPLVR2_OFFSET (0x50)
#define TIMER_TPLVR2        TIMER_TPLVR2
#define TIMER_TPLVR2_POS    (0U)
#define TIMER_TPLVR2_LEN    (32U)
#define TIMER_TPLVR2_MSK    (((1U << TIMER_TPLVR2_LEN) - 1) << TIMER_TPLVR2_POS)
#define TIMER_TPLVR2_UMSK   (~(((1U << TIMER_TPLVR2_LEN) - 1) << TIMER_TPLVR2_POS))

/* 0x54 : Timer3 Pre-Load Value */
#define TIMER_TPLVR3_OFFSET (0x54)
#define TIMER_TPLVR3        TIMER_TPLVR3
#define TIMER_TPLVR3_POS    (0U)
#define TIMER_TPLVR3_LEN    (32U)
#define TIMER_TPLVR3_MSK    (((1U << TIMER_TPLVR3_LEN) - 1) << TIMER_TPLVR3_POS)
#define TIMER_TPLVR3_UMSK   (~(((1U << TIMER_TPLVR3_LEN) - 1) << TIMER_TPLVR3_POS))

/* 0x5C : Timer2 Pre-Load Control */
#define TIMER_TPLCR2_OFFSET (0x5C)
#define TIMER_TPLCR2        TIMER_TPLCR2
#define TIMER_TPLCR2_POS    (0U)
#define TIMER_TPLCR2_LEN    (2U)
#define TIMER_TPLCR2_MSK    (((1U << TIMER_TPLCR2_LEN) - 1) << TIMER_TPLCR2_POS)
#define TIMER_TPLCR2_UMSK   (~(((1U << TIMER_TPLCR2_LEN) - 1) << TIMER_TPLCR2_POS))

/* 0x60 : Timer3 Pre-Load Control */
#define TIMER_TPLCR3_OFFSET (0x60)
#define TIMER_TPLCR3        TIMER_TPLCR3
#define TIMER_TPLCR3_POS    (0U)
#define TIMER_TPLCR3_LEN    (2U)
#define TIMER_TPLCR3_MSK    (((1U << TIMER_TPLCR3_LEN) - 1) << TIMER_TPLCR3_POS)
#define TIMER_TPLCR3_UMSK   (~(((1U << TIMER_TPLCR3_LEN) - 1) << TIMER_TPLCR3_POS))

/* 0x64 : Watch-dog reset/interrupt Mode */
#define TIMER_WMER_OFFSET (0x64)
#define TIMER_WE          TIMER_WE
#define TIMER_WE_POS      (0U)
#define TIMER_WE_LEN      (1U)
#define TIMER_WE_MSK      (((1U << TIMER_WE_LEN) - 1) << TIMER_WE_POS)
#define TIMER_WE_UMSK     (~(((1U << TIMER_WE_LEN) - 1) << TIMER_WE_POS))
#define TIMER_WRIE        TIMER_WRIE
#define TIMER_WRIE_POS    (1U)
#define TIMER_WRIE_LEN    (1U)
#define TIMER_WRIE_MSK    (((1U << TIMER_WRIE_LEN) - 1) << TIMER_WRIE_POS)
#define TIMER_WRIE_UMSK   (~(((1U << TIMER_WRIE_LEN) - 1) << TIMER_WRIE_POS))

/* 0x68 : Watch-dog Match Value */
#define TIMER_WMR_OFFSET     (0x68)
#define TIMER_WMR            TIMER_WMR
#define TIMER_WMR_POS        (0U)
#define TIMER_WMR_LEN        (16U)
#define TIMER_WMR_MSK        (((1U << TIMER_WMR_LEN) - 1) << TIMER_WMR_POS)
#define TIMER_WMR_UMSK       (~(((1U << TIMER_WMR_LEN) - 1) << TIMER_WMR_POS))
#define TIMER_WDT_ALIGN      TIMER_WDT_ALIGN
#define TIMER_WDT_ALIGN_POS  (16U)
#define TIMER_WDT_ALIGN_LEN  (1U)
#define TIMER_WDT_ALIGN_MSK  (((1U << TIMER_WDT_ALIGN_LEN) - 1) << TIMER_WDT_ALIGN_POS)
#define TIMER_WDT_ALIGN_UMSK (~(((1U << TIMER_WDT_ALIGN_LEN) - 1) << TIMER_WDT_ALIGN_POS))

/* 0x6C : Watch-dog Counter Value */
#define TIMER_WVR_OFFSET   (0x6C)
#define TIMER_WDT_CNT      TIMER_WDT_CNT
#define TIMER_WDT_CNT_POS  (0U)
#define TIMER_WDT_CNT_LEN  (16U)
#define TIMER_WDT_CNT_MSK  (((1U << TIMER_WDT_CNT_LEN) - 1) << TIMER_WDT_CNT_POS)
#define TIMER_WDT_CNT_UMSK (~(((1U << TIMER_WDT_CNT_LEN) - 1) << TIMER_WDT_CNT_POS))

/* 0x70 : Watch-dog Reset Status */
#define TIMER_WSR_OFFSET (0x70)
#define TIMER_WTS        TIMER_WTS
#define TIMER_WTS_POS    (0U)
#define TIMER_WTS_LEN    (1U)
#define TIMER_WTS_MSK    (((1U << TIMER_WTS_LEN) - 1) << TIMER_WTS_POS)
#define TIMER_WTS_UMSK   (~(((1U << TIMER_WTS_LEN) - 1) << TIMER_WTS_POS))

/* 0x78 : Timer2 Interrupt Clear */
#define TIMER_TICR2_OFFSET (0x78)
#define TIMER_TCLR2_0      TIMER_TCLR2_0
#define TIMER_TCLR2_0_POS  (0U)
#define TIMER_TCLR2_0_LEN  (1U)
#define TIMER_TCLR2_0_MSK  (((1U << TIMER_TCLR2_0_LEN) - 1) << TIMER_TCLR2_0_POS)
#define TIMER_TCLR2_0_UMSK (~(((1U << TIMER_TCLR2_0_LEN) - 1) << TIMER_TCLR2_0_POS))
#define TIMER_TCLR2_1      TIMER_TCLR2_1
#define TIMER_TCLR2_1_POS  (1U)
#define TIMER_TCLR2_1_LEN  (1U)
#define TIMER_TCLR2_1_MSK  (((1U << TIMER_TCLR2_1_LEN) - 1) << TIMER_TCLR2_1_POS)
#define TIMER_TCLR2_1_UMSK (~(((1U << TIMER_TCLR2_1_LEN) - 1) << TIMER_TCLR2_1_POS))
#define TIMER_TCLR2_2      TIMER_TCLR2_2
#define TIMER_TCLR2_2_POS  (2U)
#define TIMER_TCLR2_2_LEN  (1U)
#define TIMER_TCLR2_2_MSK  (((1U << TIMER_TCLR2_2_LEN) - 1) << TIMER_TCLR2_2_POS)
#define TIMER_TCLR2_2_UMSK (~(((1U << TIMER_TCLR2_2_LEN) - 1) << TIMER_TCLR2_2_POS))

/* 0x7C : Timer3 Interrupt Clear */
#define TIMER_TICR3_OFFSET (0x7C)
#define TIMER_TCLR3_0      TIMER_TCLR3_0
#define TIMER_TCLR3_0_POS  (0U)
#define TIMER_TCLR3_0_LEN  (1U)
#define TIMER_TCLR3_0_MSK  (((1U << TIMER_TCLR3_0_LEN) - 1) << TIMER_TCLR3_0_POS)
#define TIMER_TCLR3_0_UMSK (~(((1U << TIMER_TCLR3_0_LEN) - 1) << TIMER_TCLR3_0_POS))
#define TIMER_TCLR3_1      TIMER_TCLR3_1
#define TIMER_TCLR3_1_POS  (1U)
#define TIMER_TCLR3_1_LEN  (1U)
#define TIMER_TCLR3_1_MSK  (((1U << TIMER_TCLR3_1_LEN) - 1) << TIMER_TCLR3_1_POS)
#define TIMER_TCLR3_1_UMSK (~(((1U << TIMER_TCLR3_1_LEN) - 1) << TIMER_TCLR3_1_POS))
#define TIMER_TCLR3_2      TIMER_TCLR3_2
#define TIMER_TCLR3_2_POS  (2U)
#define TIMER_TCLR3_2_LEN  (1U)
#define TIMER_TCLR3_2_MSK  (((1U << TIMER_TCLR3_2_LEN) - 1) << TIMER_TCLR3_2_POS)
#define TIMER_TCLR3_2_UMSK (~(((1U << TIMER_TCLR3_2_LEN) - 1) << TIMER_TCLR3_2_POS))

/* 0x80 : WDT Interrupt Clear */
#define TIMER_WICR_OFFSET (0x80)
#define TIMER_WICLR       TIMER_WICLR
#define TIMER_WICLR_POS   (0U)
#define TIMER_WICLR_LEN   (1U)
#define TIMER_WICLR_MSK   (((1U << TIMER_WICLR_LEN) - 1) << TIMER_WICLR_POS)
#define TIMER_WICLR_UMSK  (~(((1U << TIMER_WICLR_LEN) - 1) << TIMER_WICLR_POS))

/* 0x84 : Timer Counter Enable/Clear */
#define TIMER_TCER_OFFSET       (0x84)
#define TIMER2_EN               TIMER2_EN
#define TIMER2_EN_POS           (1U)
#define TIMER2_EN_LEN           (1U)
#define TIMER2_EN_MSK           (((1U << TIMER2_EN_LEN) - 1) << TIMER2_EN_POS)
#define TIMER2_EN_UMSK          (~(((1U << TIMER2_EN_LEN) - 1) << TIMER2_EN_POS))
#define TIMER3_EN               TIMER3_EN
#define TIMER3_EN_POS           (2U)
#define TIMER3_EN_LEN           (1U)
#define TIMER3_EN_MSK           (((1U << TIMER3_EN_LEN) - 1) << TIMER3_EN_POS)
#define TIMER3_EN_UMSK          (~(((1U << TIMER3_EN_LEN) - 1) << TIMER3_EN_POS))
#define TIMER_TCR2_CNT_CLR      TIMER_TCR2_CNT_CLR
#define TIMER_TCR2_CNT_CLR_POS  (5U)
#define TIMER_TCR2_CNT_CLR_LEN  (1U)
#define TIMER_TCR2_CNT_CLR_MSK  (((1U << TIMER_TCR2_CNT_CLR_LEN) - 1) << TIMER_TCR2_CNT_CLR_POS)
#define TIMER_TCR2_CNT_CLR_UMSK (~(((1U << TIMER_TCR2_CNT_CLR_LEN) - 1) << TIMER_TCR2_CNT_CLR_POS))
#define TIMER_TCR3_CNT_CLR      TIMER_TCR3_CNT_CLR
#define TIMER_TCR3_CNT_CLR_POS  (6U)
#define TIMER_TCR3_CNT_CLR_LEN  (1U)
#define TIMER_TCR3_CNT_CLR_MSK  (((1U << TIMER_TCR3_CNT_CLR_LEN) - 1) << TIMER_TCR3_CNT_CLR_POS)
#define TIMER_TCR3_CNT_CLR_UMSK (~(((1U << TIMER_TCR3_CNT_CLR_LEN) - 1) << TIMER_TCR3_CNT_CLR_POS))

/* 0x88 : Timer Counter Mode */
#define TIMER_TCMR_OFFSET (0x88)
#define TIMER2_MODE       TIMER2_MODE
#define TIMER2_MODE_POS   (1U)
#define TIMER2_MODE_LEN   (1U)
#define TIMER2_MODE_MSK   (((1U << TIMER2_MODE_LEN) - 1) << TIMER2_MODE_POS)
#define TIMER2_MODE_UMSK  (~(((1U << TIMER2_MODE_LEN) - 1) << TIMER2_MODE_POS))
#define TIMER3_MODE       TIMER3_MODE
#define TIMER3_MODE_POS   (2U)
#define TIMER3_MODE_LEN   (1U)
#define TIMER3_MODE_MSK   (((1U << TIMER3_MODE_LEN) - 1) << TIMER3_MODE_POS)
#define TIMER3_MODE_UMSK  (~(((1U << TIMER3_MODE_LEN) - 1) << TIMER3_MODE_POS))
#define TIMER2_ALIGN      TIMER2_ALIGN
#define TIMER2_ALIGN_POS  (5U)
#define TIMER2_ALIGN_LEN  (1U)
#define TIMER2_ALIGN_MSK  (((1U << TIMER2_ALIGN_LEN) - 1) << TIMER2_ALIGN_POS)
#define TIMER2_ALIGN_UMSK (~(((1U << TIMER2_ALIGN_LEN) - 1) << TIMER2_ALIGN_POS))
#define TIMER3_ALIGN      TIMER3_ALIGN
#define TIMER3_ALIGN_POS  (6U)
#define TIMER3_ALIGN_LEN  (1U)
#define TIMER3_ALIGN_MSK  (((1U << TIMER3_ALIGN_LEN) - 1) << TIMER3_ALIGN_POS)
#define TIMER3_ALIGN_UMSK (~(((1U << TIMER3_ALIGN_LEN) - 1) << TIMER3_ALIGN_POS))

/* 0x90 : Timer2 Match Interrupt Mode */
#define TIMER_TILR2_OFFSET (0x90)
#define TIMER_TILR2_0      TIMER_TILR2_0
#define TIMER_TILR2_0_POS  (0U)
#define TIMER_TILR2_0_LEN  (1U)
#define TIMER_TILR2_0_MSK  (((1U << TIMER_TILR2_0_LEN) - 1) << TIMER_TILR2_0_POS)
#define TIMER_TILR2_0_UMSK (~(((1U << TIMER_TILR2_0_LEN) - 1) << TIMER_TILR2_0_POS))
#define TIMER_TILR2_1      TIMER_TILR2_1
#define TIMER_TILR2_1_POS  (1U)
#define TIMER_TILR2_1_LEN  (1U)
#define TIMER_TILR2_1_MSK  (((1U << TIMER_TILR2_1_LEN) - 1) << TIMER_TILR2_1_POS)
#define TIMER_TILR2_1_UMSK (~(((1U << TIMER_TILR2_1_LEN) - 1) << TIMER_TILR2_1_POS))
#define TIMER_TILR2_2      TIMER_TILR2_2
#define TIMER_TILR2_2_POS  (2U)
#define TIMER_TILR2_2_LEN  (1U)
#define TIMER_TILR2_2_MSK  (((1U << TIMER_TILR2_2_LEN) - 1) << TIMER_TILR2_2_POS)
#define TIMER_TILR2_2_UMSK (~(((1U << TIMER_TILR2_2_LEN) - 1) << TIMER_TILR2_2_POS))

/* 0x94 : Timer3 Match Interrupt Mode */
#define TIMER_TILR3_OFFSET (0x94)
#define TIMER_TILR3_0      TIMER_TILR3_0
#define TIMER_TILR3_0_POS  (0U)
#define TIMER_TILR3_0_LEN  (1U)
#define TIMER_TILR3_0_MSK  (((1U << TIMER_TILR3_0_LEN) - 1) << TIMER_TILR3_0_POS)
#define TIMER_TILR3_0_UMSK (~(((1U << TIMER_TILR3_0_LEN) - 1) << TIMER_TILR3_0_POS))
#define TIMER_TILR3_1      TIMER_TILR3_1
#define TIMER_TILR3_1_POS  (1U)
#define TIMER_TILR3_1_LEN  (1U)
#define TIMER_TILR3_1_MSK  (((1U << TIMER_TILR3_1_LEN) - 1) << TIMER_TILR3_1_POS)
#define TIMER_TILR3_1_UMSK (~(((1U << TIMER_TILR3_1_LEN) - 1) << TIMER_TILR3_1_POS))
#define TIMER_TILR3_2      TIMER_TILR3_2
#define TIMER_TILR3_2_POS  (2U)
#define TIMER_TILR3_2_LEN  (1U)
#define TIMER_TILR3_2_MSK  (((1U << TIMER_TILR3_2_LEN) - 1) << TIMER_TILR3_2_POS)
#define TIMER_TILR3_2_UMSK (~(((1U << TIMER_TILR3_2_LEN) - 1) << TIMER_TILR3_2_POS))

/* 0x98 : WDT Counter Reset */
#define TIMER_WCR_OFFSET (0x98)
#define TIMER_WCR        TIMER_WCR
#define TIMER_WCR_POS    (0U)
#define TIMER_WCR_LEN    (1U)
#define TIMER_WCR_MSK    (((1U << TIMER_WCR_LEN) - 1) << TIMER_WCR_POS)
#define TIMER_WCR_UMSK   (~(((1U << TIMER_WCR_LEN) - 1) << TIMER_WCR_POS))

/* 0x9C : WDT Access Key1 */
#define TIMER_WFAR_OFFSET (0x9C)
#define TIMER_WFAR        TIMER_WFAR
#define TIMER_WFAR_POS    (0U)
#define TIMER_WFAR_LEN    (16U)
#define TIMER_WFAR_MSK    (((1U << TIMER_WFAR_LEN) - 1) << TIMER_WFAR_POS)
#define TIMER_WFAR_UMSK   (~(((1U << TIMER_WFAR_LEN) - 1) << TIMER_WFAR_POS))

/* 0xA0 : WDT Access Key2 */
#define TIMER_WSAR_OFFSET (0xA0)
#define TIMER_WSAR        TIMER_WSAR
#define TIMER_WSAR_POS    (0U)
#define TIMER_WSAR_LEN    (16U)
#define TIMER_WSAR_MSK    (((1U << TIMER_WSAR_LEN) - 1) << TIMER_WSAR_POS)
#define TIMER_WSAR_UMSK   (~(((1U << TIMER_WSAR_LEN) - 1) << TIMER_WSAR_POS))

/* 0xA8 : Timer2 Counter Latch Value */
#define TIMER_TCVWR2_OFFSET     (0xA8)
#define TIMER_TCR2_CNT_LAT      TIMER_TCR2_CNT_LAT
#define TIMER_TCR2_CNT_LAT_POS  (0U)
#define TIMER_TCR2_CNT_LAT_LEN  (32U)
#define TIMER_TCR2_CNT_LAT_MSK  (((1U << TIMER_TCR2_CNT_LAT_LEN) - 1) << TIMER_TCR2_CNT_LAT_POS)
#define TIMER_TCR2_CNT_LAT_UMSK (~(((1U << TIMER_TCR2_CNT_LAT_LEN) - 1) << TIMER_TCR2_CNT_LAT_POS))

/* 0xAC : Timer3 Counter Latch Value */
#define TIMER_TCVWR3_OFFSET     (0xAC)
#define TIMER_TCR3_CNT_LAT      TIMER_TCR3_CNT_LAT
#define TIMER_TCR3_CNT_LAT_POS  (0U)
#define TIMER_TCR3_CNT_LAT_LEN  (32U)
#define TIMER_TCR3_CNT_LAT_MSK  (((1U << TIMER_TCR3_CNT_LAT_LEN) - 1) << TIMER_TCR3_CNT_LAT_POS)
#define TIMER_TCR3_CNT_LAT_UMSK (~(((1U << TIMER_TCR3_CNT_LAT_LEN) - 1) << TIMER_TCR3_CNT_LAT_POS))

/* 0xB4 : Timer2 Counter Sync Value */
#define TIMER_TCVSYN2_OFFSET     (0xB4)
#define TIMER_TCR2_CNT_SYNC      TIMER_TCR2_CNT_SYNC
#define TIMER_TCR2_CNT_SYNC_POS  (0U)
#define TIMER_TCR2_CNT_SYNC_LEN  (32U)
#define TIMER_TCR2_CNT_SYNC_MSK  (((1U << TIMER_TCR2_CNT_SYNC_LEN) - 1) << TIMER_TCR2_CNT_SYNC_POS)
#define TIMER_TCR2_CNT_SYNC_UMSK (~(((1U << TIMER_TCR2_CNT_SYNC_LEN) - 1) << TIMER_TCR2_CNT_SYNC_POS))

/* 0xB8 : Timer3 Counter Sync Value */
#define TIMER_TCVSYN3_OFFSET     (0xB8)
#define TIMER_TCR3_CNT_SYNC      TIMER_TCR3_CNT_SYNC
#define TIMER_TCR3_CNT_SYNC_POS  (0U)
#define TIMER_TCR3_CNT_SYNC_LEN  (32U)
#define TIMER_TCR3_CNT_SYNC_MSK  (((1U << TIMER_TCR3_CNT_SYNC_LEN) - 1) << TIMER_TCR3_CNT_SYNC_POS)
#define TIMER_TCR3_CNT_SYNC_UMSK (~(((1U << TIMER_TCR3_CNT_SYNC_LEN) - 1) << TIMER_TCR3_CNT_SYNC_POS))

/* 0xBC : Timer Division */
#define TIMER_TCDR_OFFSET (0xBC)
#define TIMER_TCDR2       TIMER_TCDR2
#define TIMER_TCDR2_POS   (8U)
#define TIMER_TCDR2_LEN   (8U)
#define TIMER_TCDR2_MSK   (((1U << TIMER_TCDR2_LEN) - 1) << TIMER_TCDR2_POS)
#define TIMER_TCDR2_UMSK  (~(((1U << TIMER_TCDR2_LEN) - 1) << TIMER_TCDR2_POS))
#define TIMER_TCDR3       TIMER_TCDR3
#define TIMER_TCDR3_POS   (16U)
#define TIMER_TCDR3_LEN   (8U)
#define TIMER_TCDR3_MSK   (((1U << TIMER_TCDR3_LEN) - 1) << TIMER_TCDR3_POS)
#define TIMER_TCDR3_UMSK  (~(((1U << TIMER_TCDR3_LEN) - 1) << TIMER_TCDR3_POS))
#define TIMER_WCDR        TIMER_WCDR
#define TIMER_WCDR_POS    (24U)
#define TIMER_WCDR_LEN    (8U)
#define TIMER_WCDR_MSK    (((1U << TIMER_WCDR_LEN) - 1) << TIMER_WCDR_POS)
#define TIMER_WCDR_UMSK   (~(((1U << TIMER_WCDR_LEN) - 1) << TIMER_WCDR_POS))

/* 0xC0 : GPIO Mode */
#define TIMER_GPIO_OFFSET       (0xC0)
#define TIMER2_GPIO_EN          TIMER2_GPIO_EN
#define TIMER2_GPIO_EN_POS      (1U)
#define TIMER2_GPIO_EN_LEN      (1U)
#define TIMER2_GPIO_EN_MSK      (((1U << TIMER2_GPIO_EN_LEN) - 1) << TIMER2_GPIO_EN_POS)
#define TIMER2_GPIO_EN_UMSK     (~(((1U << TIMER2_GPIO_EN_LEN) - 1) << TIMER2_GPIO_EN_POS))
#define TIMER2_GPIO_INV         TIMER2_GPIO_INV
#define TIMER2_GPIO_INV_POS     (5U)
#define TIMER2_GPIO_INV_LEN     (1U)
#define TIMER2_GPIO_INV_MSK     (((1U << TIMER2_GPIO_INV_LEN) - 1) << TIMER2_GPIO_INV_POS)
#define TIMER2_GPIO_INV_UMSK    (~(((1U << TIMER2_GPIO_INV_LEN) - 1) << TIMER2_GPIO_INV_POS))
#define TIMER3_GPIO_INV         TIMER3_GPIO_INV
#define TIMER3_GPIO_INV_POS     (6U)
#define TIMER3_GPIO_INV_LEN     (1U)
#define TIMER3_GPIO_INV_MSK     (((1U << TIMER3_GPIO_INV_LEN) - 1) << TIMER3_GPIO_INV_POS)
#define TIMER3_GPIO_INV_UMSK    (~(((1U << TIMER3_GPIO_INV_LEN) - 1) << TIMER3_GPIO_INV_POS))
#define TIMER_WDT_GPIO_INV      TIMER_WDT_GPIO_INV
#define TIMER_WDT_GPIO_INV_POS  (7U)
#define TIMER_WDT_GPIO_INV_LEN  (1U)
#define TIMER_WDT_GPIO_INV_MSK  (((1U << TIMER_WDT_GPIO_INV_LEN) - 1) << TIMER_WDT_GPIO_INV_POS)
#define TIMER_WDT_GPIO_INV_UMSK (~(((1U << TIMER_WDT_GPIO_INV_LEN) - 1) << TIMER_WDT_GPIO_INV_POS))
#define TIMER_GPIO_LAT_OK       TIMER_GPIO_LAT_OK
#define TIMER_GPIO_LAT_OK_POS   (31U)
#define TIMER_GPIO_LAT_OK_LEN   (1U)
#define TIMER_GPIO_LAT_OK_MSK   (((1U << TIMER_GPIO_LAT_OK_LEN) - 1) << TIMER_GPIO_LAT_OK_POS)
#define TIMER_GPIO_LAT_OK_UMSK  (~(((1U << TIMER_GPIO_LAT_OK_LEN) - 1) << TIMER_GPIO_LAT_OK_POS))

/* 0xC4 : GPIO Latch Value1 */
#define TIMER_GPIO_LAT1_OFFSET (0xC4)
#define TIMER_GPIO_LAT1        TIMER_GPIO_LAT1
#define TIMER_GPIO_LAT1_POS    (0U)
#define TIMER_GPIO_LAT1_LEN    (32U)
#define TIMER_GPIO_LAT1_MSK    (((1U << TIMER_GPIO_LAT1_LEN) - 1) << TIMER_GPIO_LAT1_POS)
#define TIMER_GPIO_LAT1_UMSK   (~(((1U << TIMER_GPIO_LAT1_LEN) - 1) << TIMER_GPIO_LAT1_POS))

/* 0xC8 : GPIO Latch Value2 */
#define TIMER_GPIO_LAT2_OFFSET (0xC8)
#define TIMER_GPIO_LAT2        TIMER_GPIO_LAT2
#define TIMER_GPIO_LAT2_POS    (0U)
#define TIMER_GPIO_LAT2_LEN    (32U)
#define TIMER_GPIO_LAT2_MSK    (((1U << TIMER_GPIO_LAT2_LEN) - 1) << TIMER_GPIO_LAT2_POS)
#define TIMER_GPIO_LAT2_UMSK   (~(((1U << TIMER_GPIO_LAT2_LEN) - 1) << TIMER_GPIO_LAT2_POS))

/* 0xCC : Timer Division Force */
#define TIMER_TCDR_FORCE_OFFSET (0xCC)
#define TIMER_TCDR2_FORCE       TIMER_TCDR2_FORCE
#define TIMER_TCDR2_FORCE_POS   (1U)
#define TIMER_TCDR2_FORCE_LEN   (1U)
#define TIMER_TCDR2_FORCE_MSK   (((1U << TIMER_TCDR2_FORCE_LEN) - 1) << TIMER_TCDR2_FORCE_POS)
#define TIMER_TCDR2_FORCE_UMSK  (~(((1U << TIMER_TCDR2_FORCE_LEN) - 1) << TIMER_TCDR2_FORCE_POS))
#define TIMER_TCDR3_FORCE       TIMER_TCDR3_FORCE
#define TIMER_TCDR3_FORCE_POS   (2U)
#define TIMER_TCDR3_FORCE_LEN   (1U)
#define TIMER_TCDR3_FORCE_MSK   (((1U << TIMER_TCDR3_FORCE_LEN) - 1) << TIMER_TCDR3_FORCE_POS)
#define TIMER_TCDR3_FORCE_UMSK  (~(((1U << TIMER_TCDR3_FORCE_LEN) - 1) << TIMER_TCDR3_FORCE_POS))
#define TIMER_WCDR_FORCE        TIMER_WCDR_FORCE
#define TIMER_WCDR_FORCE_POS    (4U)
#define TIMER_WCDR_FORCE_LEN    (1U)
#define TIMER_WCDR_FORCE_MSK    (((1U << TIMER_WCDR_FORCE_LEN) - 1) << TIMER_WCDR_FORCE_POS)
#define TIMER_WCDR_FORCE_UMSK   (~(((1U << TIMER_WCDR_FORCE_LEN) - 1) << TIMER_WCDR_FORCE_POS))

struct timer_reg {
    /* 0x0 : Timer Clock Source */
    union {
        struct {
            uint32_t cs_2           : 4; /* [ 3: 0],        r/w,        0x5 */
            uint32_t cs_3           : 4; /* [ 7: 4],        r/w,        0x5 */
            uint32_t cs_wdt         : 4; /* [11: 8],        r/w,        0x1 */
            uint32_t reserved_12_15 : 4; /* [15:12],       rsvd,        0x0 */
            uint32_t tmr_rsv        : 8; /* [23:16],       rsvd,        0x0 */
            uint32_t ID             : 8; /* [31:24],          r,       0xa5 */
        } BF;
        uint32_t WORD;
    } TCCR;

    /* 0x4  reserved */
    uint8_t RESERVED0x4[12];

    /* 0x10 : Timer2 Match Value 0 */
    union {
        struct {
            uint32_t tmr2_0 : 32; /* [31: 0],        r/w, 0xffffffff */
        } BF;
        uint32_t WORD;
    } TMR2_0;

    /* 0x14 : Timer2 Match Value 1 */
    union {
        struct {
            uint32_t tmr2_1 : 32; /* [31: 0],        r/w, 0xffffffff */
        } BF;
        uint32_t WORD;
    } TMR2_1;

    /* 0x18 : Timer2 Match Value 2 */
    union {
        struct {
            uint32_t tmr2_2 : 32; /* [31: 0],        r/w, 0xffffffff */
        } BF;
        uint32_t WORD;
    } TMR2_2;

    /* 0x1C : Timer3 Match Value 0 */
    union {
        struct {
            uint32_t tmr3_0 : 32; /* [31: 0],        r/w, 0xffffffff */
        } BF;
        uint32_t WORD;
    } TMR3_0;

    /* 0x20 : Timer3 Match Value 1 */
    union {
        struct {
            uint32_t tmr3_1 : 32; /* [31: 0],        r/w, 0xffffffff */
        } BF;
        uint32_t WORD;
    } TMR3_1;

    /* 0x24 : Timer3 Match Value 2 */
    union {
        struct {
            uint32_t tmr3_2 : 32; /* [31: 0],        r/w, 0xffffffff */
        } BF;
        uint32_t WORD;
    } TMR3_2;

    /* 0x28  reserved */
    uint8_t RESERVED0x28[4];

    /* 0x2C : Timer2 Counter Value */
    union {
        struct {
            uint32_t tcr2_cnt : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } TCR2;

    /* 0x30 : Timer3 Counter Value */
    union {
        struct {
            uint32_t tcr3_cnt : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } TCR3;

    /* 0x34  reserved */
    uint8_t RESERVED0x34[4];

    /* 0x38 : Timer2 Match Status */
    union {
        struct {
            uint32_t tsr2_0        : 1;  /* [    0],          r,        0x0 */
            uint32_t tsr2_1        : 1;  /* [    1],          r,        0x0 */
            uint32_t tsr2_2        : 1;  /* [    2],          r,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TSR2;

    /* 0x3C : Timer3 Match Status */
    union {
        struct {
            uint32_t tsr3_0        : 1;  /* [    0],          r,        0x0 */
            uint32_t tsr3_1        : 1;  /* [    1],          r,        0x0 */
            uint32_t tsr3_2        : 1;  /* [    2],          r,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TSR3;

    /* 0x40  reserved */
    uint8_t RESERVED0x40[4];

    /* 0x44 : Timer2 Match Interrupt Enable */
    union {
        struct {
            uint32_t tier2_0       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t tier2_1       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tier2_2       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TIER2;

    /* 0x48 : Timer3 Match Interrupt Enable */
    union {
        struct {
            uint32_t tier3_0       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t tier3_1       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tier3_2       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TIER3;

    /* 0x4c  reserved */
    uint8_t RESERVED0x4c[4];

    /* 0x50 : Timer2 Pre-Load Value */
    union {
        struct {
            uint32_t tplvr2 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } TPLVR2;

    /* 0x54 : Timer3 Pre-Load Value */
    union {
        struct {
            uint32_t tplvr3 : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } TPLVR3;

    /* 0x58  reserved */
    uint8_t RESERVED0x58[4];

    /* 0x5C : Timer2 Pre-Load Control */
    union {
        struct {
            uint32_t tplcr2        : 2;  /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_31 : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TPLCR2;

    /* 0x60 : Timer3 Pre-Load Control */
    union {
        struct {
            uint32_t tplcr3        : 2;  /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_31 : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TPLCR3;

    /* 0x64 : Watch-dog reset/interrupt Mode */
    union {
        struct {
            uint32_t we            : 1;  /* [    0],        r/w,        0x0 */
            uint32_t wrie          : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_31 : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WMER;

    /* 0x68 : Watch-dog Match Value */
    union {
        struct {
            uint32_t wmr            : 16; /* [15: 0],        r/w,     0xffff */
            uint32_t wdt_align      : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31 : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WMR;

    /* 0x6C : Watch-dog Counter Value */
    union {
        struct {
            uint32_t wdt_cnt        : 16; /* [15: 0],          r,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WVR;

    /* 0x70 : Watch-dog Reset Status */
    union {
        struct {
            uint32_t wts           : 1;  /* [    0],          w,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WSR;

    /* 0x74  reserved */
    uint8_t RESERVED0x74[4];

    /* 0x78 : Timer2 Interrupt Clear */
    union {
        struct {
            uint32_t tclr2_0       : 1;  /* [    0],          w,        0x0 */
            uint32_t tclr2_1       : 1;  /* [    1],          w,        0x0 */
            uint32_t tclr2_2       : 1;  /* [    2],          w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TICR2;

    /* 0x7C : Timer3 Interrupt Clear */
    union {
        struct {
            uint32_t tclr3_0       : 1;  /* [    0],          w,        0x0 */
            uint32_t tclr3_1       : 1;  /* [    1],          w,        0x0 */
            uint32_t tclr3_2       : 1;  /* [    2],          w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TICR3;

    /* 0x80 : WDT Interrupt Clear */
    union {
        struct {
            uint32_t wiclr         : 1;  /* [    0],          w,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WICR;

    /* 0x84 : Timer Counter Enable/Clear */
    union {
        struct {
            uint32_t reserved_0    : 1;  /* [    0],       rsvd,        0x0 */
            uint32_t timer2_en     : 1;  /* [    1],        r/w,        0x0 */
            uint32_t timer3_en     : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_4  : 2;  /* [ 4: 3],       rsvd,        0x0 */
            uint32_t tcr2_cnt_clr  : 1;  /* [    5],        r/w,        0x0 */
            uint32_t tcr3_cnt_clr  : 1;  /* [    6],        r/w,        0x0 */
            uint32_t reserved_7_31 : 25; /* [31: 7],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TCER;

    /* 0x88 : Timer Counter Mode */
    union {
        struct {
            uint32_t reserved_0    : 1;  /* [    0],       rsvd,        0x0 */
            uint32_t timer2_mode   : 1;  /* [    1],        r/w,        0x0 */
            uint32_t timer3_mode   : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_4  : 2;  /* [ 4: 3],       rsvd,        0x0 */
            uint32_t timer2_align  : 1;  /* [    5],        r/w,        0x0 */
            uint32_t timer3_align  : 1;  /* [    6],        r/w,        0x0 */
            uint32_t reserved_7_31 : 25; /* [31: 7],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TCMR;

    /* 0x8c  reserved */
    uint8_t RESERVED0x8c[4];

    /* 0x90 : Timer2 Match Interrupt Mode */
    union {
        struct {
            uint32_t tilr2_0       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t tilr2_1       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tilr2_2       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TILR2;

    /* 0x94 : Timer3 Match Interrupt Mode */
    union {
        struct {
            uint32_t tilr3_0       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t tilr3_1       : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tilr3_2       : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_31 : 29; /* [31: 3],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TILR3;

    /* 0x98 : WDT Counter Reset */
    union {
        struct {
            uint32_t wcr           : 1;  /* [    0],          w,        0x0 */
            uint32_t reserved_1_31 : 31; /* [31: 1],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WCR;

    /* 0x9C : WDT Access Key1 */
    union {
        struct {
            uint32_t wfar           : 16; /* [15: 0],          w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WFAR;

    /* 0xA0 : WDT Access Key2 */
    union {
        struct {
            uint32_t wsar           : 16; /* [15: 0],          w,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } WSAR;

    /* 0xa4  reserved */
    uint8_t RESERVED0xa4[4];

    /* 0xA8 : Timer2 Counter Latch Value */
    union {
        struct {
            uint32_t tcr2_cnt_lat : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } TCVWR2;

    /* 0xAC : Timer3 Counter Latch Value */
    union {
        struct {
            uint32_t tcr3_cnt_lat : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } TCVWR3;

    /* 0xb0  reserved */
    uint8_t RESERVED0xb0[4];

    /* 0xB4 : Timer2 Counter Sync Value */
    union {
        struct {
            uint32_t tcr2_cnt_sync : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } TCVSYN2;

    /* 0xB8 : Timer3 Counter Sync Value */
    union {
        struct {
            uint32_t tcr3_cnt_sync : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } TCVSYN3;

    /* 0xBC : Timer Division */
    union {
        struct {
            uint32_t reserved_0_7 : 8; /* [ 7: 0],       rsvd,        0x0 */
            uint32_t tcdr2        : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t tcdr3        : 8; /* [23:16],        r/w,        0x0 */
            uint32_t wcdr         : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } TCDR;

    /* 0xC0 : GPIO Mode */
    union {
        struct {
            uint32_t reserved_0      : 1;  /* [    0],       rsvd,        0x0 */
            uint32_t timer2_gpio_en  : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_4    : 3;  /* [ 4: 2],       rsvd,        0x0 */
            uint32_t timer2_gpio_inv : 1;  /* [    5],        r/w,        0x0 */
            uint32_t timer3_gpio_inv : 1;  /* [    6],        r/w,        0x0 */
            uint32_t wdt_gpio_inv    : 1;  /* [    7],        r/w,        0x0 */
            uint32_t reserved_8_30   : 23; /* [30: 8],       rsvd,        0x0 */
            uint32_t gpio_lat_ok     : 1;  /* [   31],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } GPIO;

    /* 0xC4 : GPIO Latch Value1 */
    union {
        struct {
            uint32_t gpio_lat1 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } GPIO_LAT1;

    /* 0xC8 : GPIO Latch Value2 */
    union {
        struct {
            uint32_t gpio_lat2 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } GPIO_LAT2;

    /* 0xCC : Timer Division Force */
    union {
        struct {
            uint32_t reserved_0    : 1;  /* [    0],       rsvd,        0x0 */
            uint32_t tcdr2_force   : 1;  /* [    1],        r/w,        0x0 */
            uint32_t tcdr3_force   : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3    : 1;  /* [    3],       rsvd,        0x0 */
            uint32_t wcdr_force    : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } TCDR_FORCE;
};

typedef volatile struct timer_reg timer_reg_t;

#endif /* __TIMER_REG_H__ */
