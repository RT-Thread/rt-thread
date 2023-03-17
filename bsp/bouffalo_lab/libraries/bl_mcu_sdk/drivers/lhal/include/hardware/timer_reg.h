/**
  ******************************************************************************
  * @file    timer_reg.h
  * @version V1.0
  * @date    2022-08-03
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
#ifndef __HARDWARE_TIMER_H__
#define __HARDWARE_TIMER_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define TIMER_TCCR_OFFSET    (0x0)  /* Timer Clock Source */
#define TIMER_TMR0_0_OFFSET  (0x10) /* Timer0 Match Value 0 */
#define TIMER_TMR0_1_OFFSET  (0x14) /* Timer0 Match Value 1 */
#define TIMER_TMR0_2_OFFSET  (0x18) /* Timer0 Match Value 2 */
#define TIMER_TMR1_0_OFFSET  (0x1C) /* Timer1 Match Value 0 */
#define TIMER_TMR1_1_OFFSET  (0x20) /* Timer1 Match Value 1 */
#define TIMER_TMR1_2_OFFSET  (0x24) /* Timer1 Match Value 2 */
#define TIMER_TCR0_OFFSET    (0x2C) /* Timer0 Counter Value */
#define TIMER_TCR1_OFFSET    (0x30) /* Timer1 Counter Value */
#define TIMER_TSR0_OFFSET    (0x38) /* Timer0 Match Status */
#define TIMER_TSR1_OFFSET    (0x3C) /* Timer1 Match Status */
#define TIMER_TIER0_OFFSET   (0x44) /* Timer0 Match Interrupt Enable */
#define TIMER_TIER1_OFFSET   (0x48) /* Timer1 Match Interrupt Enable */
#define TIMER_TPLVR0_OFFSET  (0x50) /* Timer0 Pre-Load Value */
#define TIMER_TPLVR1_OFFSET  (0x54) /* Timer1 Pre-Load Value */
#define TIMER_TPLCR0_OFFSET  (0x5C) /* Timer0 Pre-Load Control */
#define TIMER_TPLCR1_OFFSET  (0x60) /* Timer1 Pre-Load Control */
#define TIMER_WMER_OFFSET    (0x64) /* Watch-dog reset/interrupt Mode */
#define TIMER_WMR_OFFSET     (0x68) /* Watch-dog Match Value */
#define TIMER_WVR_OFFSET     (0x6C) /* Watch-dog Counter Value */
#define TIMER_WSR_OFFSET     (0x70) /* Watch-dog Reset Status */
#define TIMER_TICR0_OFFSET   (0x78) /* Timer0 Interrupt Clear */
#define TIMER_TICR1_OFFSET   (0x7C) /* Timer1 Interrupt Clear */
#define TIMER_WICR_OFFSET    (0x80) /* WDT Interrupt Clear */
#define TIMER_TCER_OFFSET    (0x84) /* Timer Counter Enable/Clear */
#define TIMER_TCMR_OFFSET    (0x88) /* Timer Counter Mode */
#define TIMER_TILR0_OFFSET   (0x90) /* Timer0 Match Interrupt Mode */
#define TIMER_TILR1_OFFSET   (0x94) /* Timer1 Match Interrupt Mode */
#define TIMER_WCR_OFFSET     (0x98) /* WDT Counter Reset */
#define TIMER_WFAR_OFFSET    (0x9C) /* WDT Access Key1 */
#define TIMER_WSAR_OFFSET    (0xA0) /* WDT Access Key2 */
#define TIMER_TCVWR0_OFFSET  (0xA8) /* Timer0 Counter Latch Value */
#define TIMER_TCVWR1_OFFSET  (0xAC) /* Timer1 Counter Latch Value */
#define TIMER_TCVSYN0_OFFSET (0xB4) /* Timer0 Counter Sync Value */
#define TIMER_TCVSYN1_OFFSET (0xB8) /* Timer1 Counter Sync Value */
#define TIMER_TCDR_OFFSET    (0xBC) /* Timer Division */
#if !defined(BL702) || !defined(BL602)
#define TIMER_GPIO_OFFSET       (0xC0) /* GPIO Mode */
#define TIMER_GPIO_LAT1_OFFSET  (0xC4) /* GPIO Latch Value1 */
#define TIMER_GPIO_LAT2_OFFSET  (0xC8) /* GPIO Latch Value2 */
#define TIMER_TCDR_FORCE_OFFSET (0xCC) /* Timer Division Force */
#endif

/* Register Bitfield definitions *****************************************************/

/* 0x0 : Timer Clock Source */
#if defined(BL702) || defined(BL602)
#define TIMER_CS_0_SHIFT   (2U)
#define TIMER_CS_0_MASK    (0x3 << TIMER_CS_0_SHIFT)
#define TIMER_CS_1_SHIFT   (5U)
#define TIMER_CS_1_MASK    (0x3 << TIMER_CS_1_SHIFT)
#define TIMER_CS_WDT_SHIFT (8U)
#define TIMER_CS_WDT_MASK  (0x3 << TIMER_CS_WDT_SHIFT)
#else
#define TIMER_CS_0_SHIFT   (0U)
#define TIMER_CS_0_MASK    (0xf << TIMER_CS_0_SHIFT)
#define TIMER_CS_1_SHIFT   (4U)
#define TIMER_CS_1_MASK    (0xf << TIMER_CS_1_SHIFT)
#define TIMER_CS_WDT_SHIFT (8U)
#define TIMER_CS_WDT_MASK  (0xf << TIMER_CS_WDT_SHIFT)
#define TIMER_ID_SHIFT     (24U)
#define TIMER_ID_MASK      (0xff << TIMER_ID_SHIFT)
#endif

/* 0x10 : Timer0 Match Value 0 */
#define TIMER_TMR0_0_SHIFT (0U)
#define TIMER_TMR0_0_MASK  (0xffffffff << TIMER_TMR0_0_SHIFT)

/* 0x14 : Timer0 Match Value 1 */
#define TIMER_TMR0_1_SHIFT (0U)
#define TIMER_TMR0_1_MASK  (0xffffffff << TIMER_TMR0_1_SHIFT)

/* 0x18 : Timer0 Match Value 2 */
#define TIMER_TMR0_2_SHIFT (0U)
#define TIMER_TMR0_2_MASK  (0xffffffff << TIMER_TMR0_2_SHIFT)

/* 0x1C : Timer1 Match Value 0 */
#define TIMER_TMR1_0_SHIFT (0U)
#define TIMER_TMR1_0_MASK  (0xffffffff << TIMER_TMR1_0_SHIFT)

/* 0x20 : Timer1 Match Value 1 */
#define TIMER_TMR1_1_SHIFT (0U)
#define TIMER_TMR1_1_MASK  (0xffffffff << TIMER_TMR1_1_SHIFT)

/* 0x24 : Timer1 Match Value 2 */
#define TIMER_TMR1_2_SHIFT (0U)
#define TIMER_TMR1_2_MASK  (0xffffffff << TIMER_TMR1_2_SHIFT)

/* 0x2C : Timer0 Counter Value */
#define TIMER_TCR0_CNT_SHIFT (0U)
#define TIMER_TCR0_CNT_MASK  (0xffffffff << TIMER_TCR0_CNT_SHIFT)

/* 0x30 : Timer1 Counter Value */
#define TIMER_TCR1_CNT_SHIFT (0U)
#define TIMER_TCR1_CNT_MASK  (0xffffffff << TIMER_TCR1_CNT_SHIFT)

/* 0x38 : Timer0 Match Status */
#define TIMER_TSR0_0 (1 << 0U)
#define TIMER_TSR0_1 (1 << 1U)
#define TIMER_TSR0_2 (1 << 2U)

/* 0x3C : Timer1 Match Status */
#define TIMER_TSR1_0 (1 << 0U)
#define TIMER_TSR1_1 (1 << 1U)
#define TIMER_TSR1_2 (1 << 2U)

/* 0x44 : Timer0 Match Interrupt Enable */
#define TIMER_TIER0_0 (1 << 0U)
#define TIMER_TIER0_1 (1 << 1U)
#define TIMER_TIER0_2 (1 << 2U)

/* 0x48 : Timer1 Match Interrupt Enable */
#define TIMER_TIER1_0 (1 << 0U)
#define TIMER_TIER1_1 (1 << 1U)
#define TIMER_TIER1_2 (1 << 2U)

/* 0x50 : Timer0 Pre-Load Value */
#define TIMER_TPLVR0_SHIFT (0U)
#define TIMER_TPLVR0_MASK  (0xffffffff << TIMER_TPLVR0_SHIFT)

/* 0x54 : Timer1 Pre-Load Value */
#define TIMER_TPLVR1_SHIFT (0U)
#define TIMER_TPLVR1_MASK  (0xffffffff << TIMER_TPLVR1_SHIFT)

/* 0x5C : Timer0 Pre-Load Control */
#define TIMER_TPLCR0_SHIFT (0U)
#define TIMER_TPLCR0_MASK  (0x3 << TIMER_TPLCR0_SHIFT)

/* 0x60 : Timer1 Pre-Load Control */
#define TIMER_TPLCR1_SHIFT (0U)
#define TIMER_TPLCR1_MASK  (0x3 << TIMER_TPLCR1_SHIFT)

/* 0x64 : Watch-dog reset/interrupt Mode */
#define TIMER_WE   (1 << 0U)
#define TIMER_WRIE (1 << 1U)

/* 0x68 : Watch-dog Match Value */
#define TIMER_WMR_SHIFT (0U)
#define TIMER_WMR_MASK  (0xffff << TIMER_WMR_SHIFT)
#define TIMER_WDT_ALIGN (1 << 16U)

/* 0x6C : Watch-dog Counter Value */
#define TIMER_WDT_CNT_SHIFT (0U)
#define TIMER_WDT_CNT_MASK  (0xffff << TIMER_WDT_CNT_SHIFT)

/* 0x70 : Watch-dog Reset Status */
#define TIMER_WTS (1 << 0U)

/* 0x78 : Timer0 Interrupt Clear */
#define TIMER_TCLR0_0 (1 << 0U)
#define TIMER_TCLR0_1 (1 << 1U)
#define TIMER_TCLR0_2 (1 << 2U)

/* 0x7C : Timer1 Interrupt Clear */
#define TIMER_TCLR1_0 (1 << 0U)
#define TIMER_TCLR1_1 (1 << 1U)
#define TIMER_TCLR1_2 (1 << 2U)

/* 0x80 : WDT Interrupt Clear */
#define TIMER_WICLR (1 << 0U)

/* 0x84 : Timer Counter Enable/Clear */
#define TIMER0_EN          (1 << 1U)
#define TIMER1_EN          (1 << 2U)
#define TIMER_TCR0_CNT_CLR (1 << 5U)
#define TIMER_TCR1_CNT_CLR (1 << 6U)

/* 0x88 : Timer Counter Mode */
#define TIMER0_MODE  (1 << 1U)
#define TIMER1_MODE  (1 << 2U)
#define TIMER0_ALIGN (1 << 5U)
#define TIMER1_ALIGN (1 << 6U)

/* 0x90 : Timer0 Match Interrupt Mode */
#define TIMER_TILR0_0 (1 << 0U)
#define TIMER_TILR0_1 (1 << 1U)
#define TIMER_TILR0_2 (1 << 2U)

/* 0x94 : Timer1 Match Interrupt Mode */
#define TIMER_TILR1_0 (1 << 0U)
#define TIMER_TILR1_1 (1 << 1U)
#define TIMER_TILR1_2 (1 << 2U)

/* 0x98 : WDT Counter Reset */
#define TIMER_WCR (1 << 0U)

/* 0x9C : WDT Access Key1 */
#define TIMER_WFAR_SHIFT (0U)
#define TIMER_WFAR_MASK  (0xffff << TIMER_WFAR_SHIFT)

/* 0xA0 : WDT Access Key2 */
#define TIMER_WSAR_SHIFT (0U)
#define TIMER_WSAR_MASK  (0xffff << TIMER_WSAR_SHIFT)

/* 0xA8 : Timer0 Counter Latch Value */
#define TIMER_TCR0_CNT_LAT_SHIFT (0U)
#define TIMER_TCR0_CNT_LAT_MASK  (0xffffffff << TIMER_TCR0_CNT_LAT_SHIFT)

/* 0xAC : Timer1 Counter Latch Value */
#define TIMER_TCR1_CNT_LAT_SHIFT (0U)
#define TIMER_TCR1_CNT_LAT_MASK  (0xffffffff << TIMER_TCR1_CNT_LAT_SHIFT)

/* 0xB4 : Timer0 Counter Sync Value */
#define TIMER_TCR0_CNT_SYNC_SHIFT (0U)
#define TIMER_TCR0_CNT_SYNC_MASK  (0xffffffff << TIMER_TCR0_CNT_SYNC_SHIFT)

/* 0xB8 : Timer1 Counter Sync Value */
#define TIMER_TCR1_CNT_SYNC_SHIFT (0U)
#define TIMER_TCR1_CNT_SYNC_MASK  (0xffffffff << TIMER_TCR1_CNT_SYNC_SHIFT)

/* 0xBC : Timer Division */
#define TIMER_TCDR0_SHIFT (8U)
#define TIMER_TCDR0_MASK  (0xff << TIMER_TCDR0_SHIFT)
#define TIMER_TCDR1_SHIFT (16U)
#define TIMER_TCDR1_MASK  (0xff << TIMER_TCDR1_SHIFT)
#define TIMER_WCDR_SHIFT  (24U)
#define TIMER_WCDR_MASK   (0xff << TIMER_WCDR_SHIFT)

#if !defined(BL702) || !defined(BL602)
/* 0xC0 : GPIO Mode */
#define TIMER0_GPIO_EN     (1 << 1U)
#define TIMER0_GPIO_INV    (1 << 5U)
#define TIMER1_GPIO_INV    (1 << 6U)
#define TIMER_WDT_GPIO_INV (1 << 7U)
#define TIMER_GPIO_LAT_OK  (1 << 31U)

/* 0xC4 : GPIO Latch Value1 */
#define TIMER_GPIO_LAT1_SHIFT (0U)
#define TIMER_GPIO_LAT1_MASK  (0xffffffff << TIMER_GPIO_LAT1_SHIFT)

/* 0xC8 : GPIO Latch Value2 */
#define TIMER_GPIO_LAT2_SHIFT (0U)
#define TIMER_GPIO_LAT2_MASK  (0xffffffff << TIMER_GPIO_LAT2_SHIFT)

/* 0xCC : Timer Division Force */
#define TIMER_TCDR0_FORCE (1 << 1U)
#define TIMER_TCDR1_FORCE (1 << 2U)
#define TIMER_WCDR_FORCE  (1 << 4U)
#endif

#endif /* __HARDWARE_TIMER_H__ */
