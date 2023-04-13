/**
  ******************************************************************************
  * @file    pwm_reg.h
  * @version V1.0
  * @date    2022-10-10
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
#ifndef __PWM_REG_H__
#define __PWM_REG_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/
#if defined(BL702L)
#define PWM_INT_CONFIG_OFFSET (-0x20) /* pwm_int_config */
#else
#define PWM_INT_CONFIG_OFFSET (0x0) /* pwm_int_config */
#endif
#define PWM0_CLKDIV_OFFSET    (0x20) /* pwm0_clkdiv */
#define PWM0_THRE1_OFFSET     (0x24) /* pwm0_thre1 */
#define PWM0_THRE2_OFFSET     (0x28) /* pwm0_thre2 */
#define PWM0_PERIOD_OFFSET    (0x2C) /* pwm0_period */
#define PWM0_CONFIG_OFFSET    (0x30) /* pwm0_config */
#define PWM0_INTERRUPT_OFFSET (0x34) /* pwm0_interrupt */
#define PWM1_CLKDIV_OFFSET    (0x40) /* pwm1_clkdiv */
#define PWM1_THRE1_OFFSET     (0x44) /* pwm1_thre1 */
#define PWM1_THRE2_OFFSET     (0x48) /* pwm1_thre2 */
#define PWM1_PERIOD_OFFSET    (0x4C) /* pwm1_period */
#define PWM1_CONFIG_OFFSET    (0x50) /* pwm1_config */
#define PWM1_INTERRUPT_OFFSET (0x54) /* pwm1_interrupt */
#define PWM2_CLKDIV_OFFSET    (0x60) /* pwm2_clkdiv */
#define PWM2_THRE1_OFFSET     (0x64) /* pwm2_thre1 */
#define PWM2_THRE2_OFFSET     (0x68) /* pwm2_thre2 */
#define PWM2_PERIOD_OFFSET    (0x6C) /* pwm2_period */
#define PWM2_CONFIG_OFFSET    (0x70) /* pwm2_config */
#define PWM2_INTERRUPT_OFFSET (0x74) /* pwm2_interrupt */
#define PWM3_CLKDIV_OFFSET    (0x80) /* pwm3_clkdiv */
#define PWM3_THRE1_OFFSET     (0x84) /* pwm3_thre1 */
#define PWM3_THRE2_OFFSET     (0x88) /* pwm3_thre2 */
#define PWM3_PERIOD_OFFSET    (0x8C) /* pwm3_period */
#define PWM3_CONFIG_OFFSET    (0x90) /* pwm3_config */
#define PWM3_INTERRUPT_OFFSET (0x94) /* pwm3_interrupt */
#define PWM4_CLKDIV_OFFSET    (0xA0) /* pwm4_clkdiv */
#define PWM4_THRE1_OFFSET     (0xA4) /* pwm4_thre1 */
#define PWM4_THRE2_OFFSET     (0xA8) /* pwm4_thre2 */
#define PWM4_PERIOD_OFFSET    (0xAC) /* pwm4_period */
#define PWM4_CONFIG_OFFSET    (0xB0) /* pwm4_config */
#define PWM4_INTERRUPT_OFFSET (0xB4) /* pwm4_interrupt */

/* Register Bitfield definitions *****************************************************/

/* 0x0 : pwm_int_config */
#define PWM_INTERRUPT_STS_SHIFT (0U)
#define PWM_INTERRUPT_STS_MASK  (0x3f << PWM_INTERRUPT_STS_SHIFT)
#define PWM_INT_CLEAR_SHIFT     (8U)
#define PWM_INT_CLEAR_MASK      (0x3f << PWM_INT_CLEAR_SHIFT)

/* 0x20 : pwm0_clkdiv */
#define PWM_CLK_DIV_SHIFT (0U)
#define PWM_CLK_DIV_MASK  (0xffff << PWM_CLK_DIV_SHIFT)

/* 0x24 : pwm0_thre1 */
#define PWM_THRE1_SHIFT (0U)
#define PWM_THRE1_MASK  (0xffff << PWM_THRE1_SHIFT)

/* 0x28 : pwm0_thre2 */
#define PWM_THRE2_SHIFT (0U)
#define PWM_THRE2_MASK  (0xffff << PWM_THRE2_SHIFT)

/* 0x2C : pwm0_period */
#define PWM_PERIOD_SHIFT (0U)
#define PWM_PERIOD_MASK  (0xffff << PWM_PERIOD_SHIFT)

/* 0x30 : pwm0_config */
#define PWM_REG_CLK_SEL_SHIFT (0U)
#define PWM_REG_CLK_SEL_MASK  (0x3 << PWM_REG_CLK_SEL_SHIFT)
#define PWM_OUT_INV           (1 << 2U)
#define PWM_STOP_MODE         (1 << 3U)
#define PWM_SW_FORCE_VAL      (1 << 4U)
#define PWM_SW_MODE           (1 << 5U)
#define PWM_STOP_EN           (1 << 6U)
#define PWM_STS_TOP           (1 << 7U)

/* 0x34 : pwm0_interrupt */
#define PWM_INT_PERIOD_CNT_SHIFT (0U)
#define PWM_INT_PERIOD_CNT_MASK  (0xffff << PWM_INT_PERIOD_CNT_SHIFT)
#define PWM_INT_ENABLE           (1 << 16U)

/* 0x40 : pwm1_clkdiv */
#define PWM_CLK_DIV_SHIFT (0U)
#define PWM_CLK_DIV_MASK  (0xffff << PWM_CLK_DIV_SHIFT)

/* 0x44 : pwm1_thre1 */
#define PWM_THRE1_SHIFT (0U)
#define PWM_THRE1_MASK  (0xffff << PWM_THRE1_SHIFT)

/* 0x48 : pwm1_thre2 */
#define PWM_THRE2_SHIFT (0U)
#define PWM_THRE2_MASK  (0xffff << PWM_THRE2_SHIFT)

/* 0x4C : pwm1_period */
#define PWM_PERIOD_SHIFT (0U)
#define PWM_PERIOD_MASK  (0xffff << PWM_PERIOD_SHIFT)

/* 0x50 : pwm1_config */
#define PWM_REG_CLK_SEL_SHIFT (0U)
#define PWM_REG_CLK_SEL_MASK  (0x3 << PWM_REG_CLK_SEL_SHIFT)
#define PWM_OUT_INV           (1 << 2U)
#define PWM_STOP_MODE         (1 << 3U)
#define PWM_SW_FORCE_VAL      (1 << 4U)
#define PWM_SW_MODE           (1 << 5U)
#define PWM_STOP_EN           (1 << 6U)
#define PWM_STS_TOP           (1 << 7U)

/* 0x54 : pwm1_interrupt */
#define PWM_INT_PERIOD_CNT_SHIFT (0U)
#define PWM_INT_PERIOD_CNT_MASK  (0xffff << PWM_INT_PERIOD_CNT_SHIFT)
#define PWM_INT_ENABLE           (1 << 16U)

/* 0x60 : pwm2_clkdiv */
#define PWM_CLK_DIV_SHIFT (0U)
#define PWM_CLK_DIV_MASK  (0xffff << PWM_CLK_DIV_SHIFT)

/* 0x64 : pwm2_thre1 */
#define PWM_THRE1_SHIFT (0U)
#define PWM_THRE1_MASK  (0xffff << PWM_THRE1_SHIFT)

/* 0x68 : pwm2_thre2 */
#define PWM_THRE2_SHIFT (0U)
#define PWM_THRE2_MASK  (0xffff << PWM_THRE2_SHIFT)

/* 0x6C : pwm2_period */
#define PWM_PERIOD_SHIFT (0U)
#define PWM_PERIOD_MASK  (0xffff << PWM_PERIOD_SHIFT)

/* 0x70 : pwm2_config */
#define PWM_REG_CLK_SEL_SHIFT (0U)
#define PWM_REG_CLK_SEL_MASK  (0x3 << PWM_REG_CLK_SEL_SHIFT)
#define PWM_OUT_INV           (1 << 2U)
#define PWM_STOP_MODE         (1 << 3U)
#define PWM_SW_FORCE_VAL      (1 << 4U)
#define PWM_SW_MODE           (1 << 5U)
#define PWM_STOP_EN           (1 << 6U)
#define PWM_STS_TOP           (1 << 7U)

/* 0x74 : pwm2_interrupt */
#define PWM_INT_PERIOD_CNT_SHIFT (0U)
#define PWM_INT_PERIOD_CNT_MASK  (0xffff << PWM_INT_PERIOD_CNT_SHIFT)
#define PWM_INT_ENABLE           (1 << 16U)

/* 0x80 : pwm3_clkdiv */
#define PWM_CLK_DIV_SHIFT (0U)
#define PWM_CLK_DIV_MASK  (0xffff << PWM_CLK_DIV_SHIFT)

/* 0x84 : pwm3_thre1 */
#define PWM_THRE1_SHIFT (0U)
#define PWM_THRE1_MASK  (0xffff << PWM_THRE1_SHIFT)

/* 0x88 : pwm3_thre2 */
#define PWM_THRE2_SHIFT (0U)
#define PWM_THRE2_MASK  (0xffff << PWM_THRE2_SHIFT)

/* 0x8C : pwm3_period */
#define PWM_PERIOD_SHIFT (0U)
#define PWM_PERIOD_MASK  (0xffff << PWM_PERIOD_SHIFT)

/* 0x90 : pwm3_config */
#define PWM_REG_CLK_SEL_SHIFT (0U)
#define PWM_REG_CLK_SEL_MASK  (0x3 << PWM_REG_CLK_SEL_SHIFT)
#define PWM_OUT_INV           (1 << 2U)
#define PWM_STOP_MODE         (1 << 3U)
#define PWM_SW_FORCE_VAL      (1 << 4U)
#define PWM_SW_MODE           (1 << 5U)
#define PWM_STOP_EN           (1 << 6U)
#define PWM_STS_TOP           (1 << 7U)

/* 0x94 : pwm3_interrupt */
#define PWM_INT_PERIOD_CNT_SHIFT (0U)
#define PWM_INT_PERIOD_CNT_MASK  (0xffff << PWM_INT_PERIOD_CNT_SHIFT)
#define PWM_INT_ENABLE           (1 << 16U)

/* 0xA0 : pwm4_clkdiv */
#define PWM_CLK_DIV_SHIFT (0U)
#define PWM_CLK_DIV_MASK  (0xffff << PWM_CLK_DIV_SHIFT)

/* 0xA4 : pwm4_thre1 */
#define PWM_THRE1_SHIFT (0U)
#define PWM_THRE1_MASK  (0xffff << PWM_THRE1_SHIFT)

/* 0xA8 : pwm4_thre2 */
#define PWM_THRE2_SHIFT (0U)
#define PWM_THRE2_MASK  (0xffff << PWM_THRE2_SHIFT)

/* 0xAC : pwm4_period */
#define PWM_PERIOD_SHIFT (0U)
#define PWM_PERIOD_MASK  (0xffff << PWM_PERIOD_SHIFT)

/* 0xB0 : pwm4_config */
#define PWM_REG_CLK_SEL_SHIFT (0U)
#define PWM_REG_CLK_SEL_MASK  (0x3 << PWM_REG_CLK_SEL_SHIFT)
#define PWM_OUT_INV           (1 << 2U)
#define PWM_STOP_MODE         (1 << 3U)
#define PWM_SW_FORCE_VAL      (1 << 4U)
#define PWM_SW_MODE           (1 << 5U)
#define PWM_STOP_EN           (1 << 6U)
#define PWM_STS_TOP           (1 << 7U)

/* 0xB4 : pwm4_interrupt */
#define PWM_INT_PERIOD_CNT_SHIFT (0U)
#define PWM_INT_PERIOD_CNT_MASK  (0xffff << PWM_INT_PERIOD_CNT_SHIFT)
#define PWM_INT_ENABLE           (1 << 16U)

#endif /* __PWM_REG_H__ */
