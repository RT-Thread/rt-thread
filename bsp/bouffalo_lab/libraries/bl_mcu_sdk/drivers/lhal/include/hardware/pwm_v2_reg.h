/**
  ******************************************************************************
  * @file    pwm_reg.h
  * @version V1.0
  * @date    2022-08-15
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
#ifndef __HARDWARE_PWM_V2_H__
#define __HARDWARE_PWM_V2_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/

#define PWM_INT_CONFIG_OFFSET    (0x0)  /* pwm_int_config */
#define PWM_MC0_CONFIG0_OFFSET   (0x40) /* pwm_mc0_config0 */
#define PWM_MC0_CONFIG1_OFFSET   (0x44) /* pwm_mc0_config1 */
#define PWM_MC0_PERIOD_OFFSET    (0x48) /* pwm_mc0_period */
#define PWM_MC0_DEAD_TIME_OFFSET (0x4C) /* pwm_mc0_dead_time */
#define PWM_MC0_CH0_THRE_OFFSET  (0x50) /* pwm_mc0_ch0_thre */
#define PWM_MC0_CH1_THRE_OFFSET  (0x54) /* pwm_mc0_ch1_thre */
#define PWM_MC0_CH2_THRE_OFFSET  (0x58) /* pwm_mc0_ch2_thre */
#define PWM_MC0_CH3_THRE_OFFSET  (0x5C) /* pwm_mc0_ch3_thre */
#define PWM_MC0_INT_STS_OFFSET   (0x60) /* pwm_mc0_int_sts */
#define PWM_MC0_INT_MASK_OFFSET  (0x64) /* pwm_mc0_int_mask */
#define PWM_MC0_INT_CLEAR_OFFSET (0x68) /* pwm_mc0_int_clear */
#define PWM_MC0_INT_EN_OFFSET    (0x6C) /* pwm_mc0_int_en */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : pwm_int_config */
#define PWM0_INT_STS (1 << 0U)
#define PWM1_INT_STS (1 << 1U)
#define PWM0_INT_CLR (1 << 8U)
#define PWM1_INT_CLR (1 << 9U)

/* 0x40 : pwm_mc0_config0 */
#define PWM_CLK_DIV_SHIFT     (0U)
#define PWM_CLK_DIV_MASK      (0xffff << PWM_CLK_DIV_SHIFT)
#define PWM_STOP_ON_REPT      (1 << 19U)
#define PWM_ADC_TRG_SRC_SHIFT (20U)
#define PWM_ADC_TRG_SRC_MASK  (0xf << PWM_ADC_TRG_SRC_SHIFT)
#define PWM_SW_BREAK_EN       (1 << 24U)
#define PWM_EXT_BREAK_EN      (1 << 25U)
#define PWM_EXT_BREAK_PL      (1 << 26U)
#define PWM_STOP_EN           (1 << 27U)
#define PWM_STOP_MODE         (1 << 28U)
#define PWM_STS_STOP          (1 << 29U)
#define PWM_REG_CLK_SEL_SHIFT (30U)
#define PWM_REG_CLK_SEL_MASK  (0x3 << PWM_REG_CLK_SEL_SHIFT)

/* 0x44 : pwm_mc0_config1 */
#define PWM_CH0_PEN (1 << 0U)
#define PWM_CH0_PSI (1 << 1U)
#define PWM_CH0_NEN (1 << 2U)
#define PWM_CH0_NSI (1 << 3U)
#define PWM_CH1_PEN (1 << 4U)
#define PWM_CH1_PSI (1 << 5U)
#define PWM_CH1_NEN (1 << 6U)
#define PWM_CH1_NSI (1 << 7U)
#define PWM_CH2_PEN (1 << 8U)
#define PWM_CH2_PSI (1 << 9U)
#define PWM_CH2_NEN (1 << 10U)
#define PWM_CH2_NSI (1 << 11U)
#define PWM_CH3_PEN (1 << 12U)
#define PWM_CH3_PSI (1 << 13U)
#define PWM_CH3_NEN (1 << 14U)
#define PWM_CH3_NSI (1 << 15U)
#define PWM_CH0_PPL (1 << 16U)
#define PWM_CH0_NPL (1 << 17U)
#define PWM_CH1_PPL (1 << 18U)
#define PWM_CH1_NPL (1 << 19U)
#define PWM_CH2_PPL (1 << 20U)
#define PWM_CH2_NPL (1 << 21U)
#define PWM_CH3_PPL (1 << 22U)
#define PWM_CH3_NPL (1 << 23U)
#define PWM_CH0_PBS (1 << 24U)
#define PWM_CH0_NBS (1 << 25U)
#define PWM_CH1_PBS (1 << 26U)
#define PWM_CH1_NBS (1 << 27U)
#define PWM_CH2_PBS (1 << 28U)
#define PWM_CH2_NBS (1 << 29U)
#define PWM_CH3_PBS (1 << 30U)
#define PWM_CH3_NBS (1 << 31U)

/* 0x48 : pwm_mc0_period */
#define PWM_PERIOD_SHIFT         (0U)
#define PWM_PERIOD_MASK          (0xffff << PWM_PERIOD_SHIFT)
#define PWM_INT_PERIOD_CNT_SHIFT (16U)
#define PWM_INT_PERIOD_CNT_MASK  (0xffff << PWM_INT_PERIOD_CNT_SHIFT)

/* 0x4C : pwm_mc0_dead_time */
#define PWM_CH0_DTG_SHIFT (0U)
#define PWM_CH0_DTG_MASK  (0xff << PWM_CH0_DTG_SHIFT)
#define PWM_CH1_DTG_SHIFT (8U)
#define PWM_CH1_DTG_MASK  (0xff << PWM_CH1_DTG_SHIFT)
#define PWM_CH2_DTG_SHIFT (16U)
#define PWM_CH2_DTG_MASK  (0xff << PWM_CH2_DTG_SHIFT)
#define PWM_CH3_DTG_SHIFT (24U)
#define PWM_CH3_DTG_MASK  (0xff << PWM_CH3_DTG_SHIFT)

/* 0x50 : pwm_mc0_ch0_thre */
#define PWM_CH0_THREL_SHIFT (0U)
#define PWM_CH0_THREL_MASK  (0xffff << PWM_CH0_THREL_SHIFT)
#define PWM_CH0_THREH_SHIFT (16U)
#define PWM_CH0_THREH_MASK  (0xffff << PWM_CH0_THREH_SHIFT)

/* 0x54 : pwm_mc0_ch1_thre */
#define PWM_CH1_THREL_SHIFT (0U)
#define PWM_CH1_THREL_MASK  (0xffff << PWM_CH1_THREL_SHIFT)
#define PWM_CH1_THREH_SHIFT (16U)
#define PWM_CH1_THREH_MASK  (0xffff << PWM_CH1_THREH_SHIFT)

/* 0x58 : pwm_mc0_ch2_thre */
#define PWM_CH2_THREL_SHIFT (0U)
#define PWM_CH2_THREL_MASK  (0xffff << PWM_CH2_THREL_SHIFT)
#define PWM_CH2_THREH_SHIFT (16U)
#define PWM_CH2_THREH_MASK  (0xffff << PWM_CH2_THREH_SHIFT)

/* 0x5C : pwm_mc0_ch3_thre */
#define PWM_CH3_THREL_SHIFT (0U)
#define PWM_CH3_THREL_MASK  (0xffff << PWM_CH3_THREL_SHIFT)
#define PWM_CH3_THREH_SHIFT (16U)
#define PWM_CH3_THREH_MASK  (0xffff << PWM_CH3_THREH_SHIFT)

/* 0x60 : pwm_mc0_int_sts */
#define PWM_CH0L_INT (1 << 0U)
#define PWM_CH0H_INT (1 << 1U)
#define PWM_CH1L_INT (1 << 2U)
#define PWM_CH1H_INT (1 << 3U)
#define PWM_CH2L_INT (1 << 4U)
#define PWM_CH2H_INT (1 << 5U)
#define PWM_CH3L_INT (1 << 6U)
#define PWM_CH3H_INT (1 << 7U)
#define PWM_PRDE_INT (1 << 8U)
#define PWM_BRK_INT  (1 << 9U)
#define PWM_REPT_INT (1 << 10U)

/* 0x64 : pwm_mc0_int_mask */
#define PWM_CR_PWM_CH0L_MASK (1 << 0U)
#define PWM_CR_PWM_CH0H_MASK (1 << 1U)
#define PWM_CR_PWM_CH1L_MASK (1 << 2U)
#define PWM_CR_PWM_CH1H_MASK (1 << 3U)
#define PWM_CR_PWM_CH2L_MASK (1 << 4U)
#define PWM_CR_PWM_CH2H_MASK (1 << 5U)
#define PWM_CR_PWM_CH3L_MASK (1 << 6U)
#define PWM_CR_PWM_CH3H_MASK (1 << 7U)
#define PWM_CR_PWM_PRDE_MASK (1 << 8U)
#define PWM_CR_PWM_BRK_MASK  (1 << 9U)
#define PWM_CR_PWM_REPT_MASK (1 << 10U)

/* 0x68 : pwm_mc0_int_clear */
#define PWM_CR_PWM_CH0L_CLR (1 << 0U)
#define PWM_CR_PWM_CH0H_CLR (1 << 1U)
#define PWM_CR_PWM_CH1L_CLR (1 << 2U)
#define PWM_CR_PWM_CH1H_CLR (1 << 3U)
#define PWM_CR_PWM_CH2L_CLR (1 << 4U)
#define PWM_CR_PWM_CH2H_CLR (1 << 5U)
#define PWM_CR_PWM_CH3L_CLR (1 << 6U)
#define PWM_CR_PWM_CH3H_CLR (1 << 7U)
#define PWM_CR_PWM_PRDE_CLR (1 << 8U)
#define PWM_CR_PWM_BRK_CLR  (1 << 9U)
#define PWM_CR_PWM_REPT_CLR (1 << 10U)

/* 0x6C : pwm_mc0_int_en */
#define PWM_CR_PWM_CH0L_EN (1 << 0U)
#define PWM_CR_PWM_CH0H_EN (1 << 1U)
#define PWM_CR_PWM_CH1L_EN (1 << 2U)
#define PWM_CR_PWM_CH1H_EN (1 << 3U)
#define PWM_CR_PWM_CH2L_EN (1 << 4U)
#define PWM_CR_PWM_CH2H_EN (1 << 5U)
#define PWM_CR_PWM_CH3L_EN (1 << 6U)
#define PWM_CR_PWM_CH3H_EN (1 << 7U)
#define PWM_CR_PWM_PRDE_EN (1 << 8U)
#define PWM_CR_PWM_BRK_EN  (1 << 9U)
#define PWM_CR_PWM_REPT_EN (1 << 10U)

#endif /* __HARDWARE_PWM_V2_H__ */
