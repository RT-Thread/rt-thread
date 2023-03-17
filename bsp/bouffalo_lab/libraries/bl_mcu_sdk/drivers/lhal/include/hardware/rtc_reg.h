/**
  ******************************************************************************
  * @file    rtc_reg.h
  * @version V1.0
  * @date    2022-08-05
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
#ifndef __HARDWARE_RTC_H__
#define __HARDWARE_RTC_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define HBN_CTL_OFFSET        (0x0)  /* HBN_CTL */
#define HBN_TIME_L_OFFSET     (0x4)  /* HBN_TIME_L */
#define HBN_TIME_H_OFFSET     (0x8)  /* HBN_TIME_H */
#define HBN_RTC_TIME_L_OFFSET (0xC)  /* RTC_TIME_L */
#define HBN_RTC_TIME_H_OFFSET (0x10) /* RTC_TIME_H */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : HBN_CTL */
#define HBN_RTC_CTL_SHIFT            (0U)
#define HBN_RTC_CTL_MASK             (0x7f << HBN_RTC_CTL_SHIFT)
#define HBN_MODE                     (1 << 7U)
#define HBN_TRAP_MODE                (1 << 8U)
#define HBN_PWRDN_HBN_CORE           (1 << 9U)
#define HBN_PWRDN_HBN_RTC            (1 << 11U)
#define HBN_SW_RST                   (1 << 12U)
#define HBN_DIS_PWR_OFF_LDO11        (1 << 13U)
#define HBN_DIS_PWR_OFF_LDO11_RT     (1 << 14U)
#define HBN_LDO11_RT_VOUT_SEL_SHIFT  (15U)
#define HBN_LDO11_RT_VOUT_SEL_MASK   (0xf << HBN_LDO11_RT_VOUT_SEL_SHIFT)
#define HBN_LDO11_AON_VOUT_SEL_SHIFT (19U)
#define HBN_LDO11_AON_VOUT_SEL_MASK  (0xf << HBN_LDO11_AON_VOUT_SEL_SHIFT)
#define HBN_PU_DCDC18_AON            (1 << 23U)
#define HBN_RTC_DLY_OPTION           (1 << 24U)
#define HBN_PWR_ON_OPTION            (1 << 25U)
#define HBN_SRAM_SLP_OPTION          (1 << 26U)
#define HBN_SRAM_SLP                 (1 << 27U)
#define HBN_STATE_SHIFT              (28U)
#define HBN_STATE_MASK               (0xf << HBN_STATE_SHIFT)

/* 0x4 : HBN_TIME_L */
#define HBN_TIME_L_SHIFT (0U)
#define HBN_TIME_L_MASK  (0xffffffff << HBN_TIME_L_SHIFT)

/* 0x8 : HBN_TIME_H */
#define HBN_TIME_H_SHIFT (0U)
#define HBN_TIME_H_MASK  (0xff << HBN_TIME_H_SHIFT)

/* 0xC : RTC_TIME_L */
#define HBN_RTC_TIME_LATCH_L_SHIFT (0U)
#define HBN_RTC_TIME_LATCH_L_MASK  (0xffffffff << HBN_RTC_TIME_LATCH_L_SHIFT)

/* 0x10 : RTC_TIME_H */
#define HBN_RTC_TIME_LATCH_H_SHIFT (0U)
#define HBN_RTC_TIME_LATCH_H_MASK  (0xff << HBN_RTC_TIME_LATCH_H_SHIFT)
#define HBN_RTC_TIME_LATCH         (1 << 31U)

#endif /* __HARDWARE_RTC_H__ */
