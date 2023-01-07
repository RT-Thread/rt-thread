/**
  ******************************************************************************
  * @file    pwm_reg.h
  * @version V1.0
  * @date    2020-11-24
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

#include "bl808.h"

/* 0x00 : pwm0_config0 */
#define PWM0_CONFIG0_OFFSET   (0x00)
#define PWM_CLK_DIV           PWM_CLK_DIV
#define PWM_CLK_DIV_POS       (0U)
#define PWM_CLK_DIV_LEN       (16U)
#define PWM_CLK_DIV_MSK       (((1U << PWM_CLK_DIV_LEN) - 1) << PWM_CLK_DIV_POS)
#define PWM_CLK_DIV_UMSK      (~(((1U << PWM_CLK_DIV_LEN) - 1) << PWM_CLK_DIV_POS))
#define PWM_STOP_ON_REPT      PWM_STOP_ON_REPT
#define PWM_STOP_ON_REPT_POS  (19U)
#define PWM_STOP_ON_REPT_LEN  (1U)
#define PWM_STOP_ON_REPT_MSK  (((1U << PWM_STOP_ON_REPT_LEN) - 1) << PWM_STOP_ON_REPT_POS)
#define PWM_STOP_ON_REPT_UMSK (~(((1U << PWM_STOP_ON_REPT_LEN) - 1) << PWM_STOP_ON_REPT_POS))
#define PWM_ADC_TRG_SRC       PWM_ADC_TRG_SRC
#define PWM_ADC_TRG_SRC_POS   (20U)
#define PWM_ADC_TRG_SRC_LEN   (4U)
#define PWM_ADC_TRG_SRC_MSK   (((1U << PWM_ADC_TRG_SRC_LEN) - 1) << PWM_ADC_TRG_SRC_POS)
#define PWM_ADC_TRG_SRC_UMSK  (~(((1U << PWM_ADC_TRG_SRC_LEN) - 1) << PWM_ADC_TRG_SRC_POS))
#define PWM_SW_BREAK_EN       PWM_SW_BREAK_EN
#define PWM_SW_BREAK_EN_POS   (24U)
#define PWM_SW_BREAK_EN_LEN   (1U)
#define PWM_SW_BREAK_EN_MSK   (((1U << PWM_SW_BREAK_EN_LEN) - 1) << PWM_SW_BREAK_EN_POS)
#define PWM_SW_BREAK_EN_UMSK  (~(((1U << PWM_SW_BREAK_EN_LEN) - 1) << PWM_SW_BREAK_EN_POS))
#define PWM_EXT_BREAK_EN      PWM_EXT_BREAK_EN
#define PWM_EXT_BREAK_EN_POS  (25U)
#define PWM_EXT_BREAK_EN_LEN  (1U)
#define PWM_EXT_BREAK_EN_MSK  (((1U << PWM_EXT_BREAK_EN_LEN) - 1) << PWM_EXT_BREAK_EN_POS)
#define PWM_EXT_BREAK_EN_UMSK (~(((1U << PWM_EXT_BREAK_EN_LEN) - 1) << PWM_EXT_BREAK_EN_POS))
#define PWM_EXT_BREAK_PL      PWM_EXT_BREAK_PL
#define PWM_EXT_BREAK_PL_POS  (26U)
#define PWM_EXT_BREAK_PL_LEN  (1U)
#define PWM_EXT_BREAK_PL_MSK  (((1U << PWM_EXT_BREAK_PL_LEN) - 1) << PWM_EXT_BREAK_PL_POS)
#define PWM_EXT_BREAK_PL_UMSK (~(((1U << PWM_EXT_BREAK_PL_LEN) - 1) << PWM_EXT_BREAK_PL_POS))
#define PWM_STOP_EN           PWM_STOP_EN
#define PWM_STOP_EN_POS       (27U)
#define PWM_STOP_EN_LEN       (1U)
#define PWM_STOP_EN_MSK       (((1U << PWM_STOP_EN_LEN) - 1) << PWM_STOP_EN_POS)
#define PWM_STOP_EN_UMSK      (~(((1U << PWM_STOP_EN_LEN) - 1) << PWM_STOP_EN_POS))
#define PWM_STOP_MODE         PWM_STOP_MODE
#define PWM_STOP_MODE_POS     (28U)
#define PWM_STOP_MODE_LEN     (1U)
#define PWM_STOP_MODE_MSK     (((1U << PWM_STOP_MODE_LEN) - 1) << PWM_STOP_MODE_POS)
#define PWM_STOP_MODE_UMSK    (~(((1U << PWM_STOP_MODE_LEN) - 1) << PWM_STOP_MODE_POS))
#define PWM_STS_STOP          PWM_STS_STOP
#define PWM_STS_STOP_POS      (29U)
#define PWM_STS_STOP_LEN      (1U)
#define PWM_STS_STOP_MSK      (((1U << PWM_STS_STOP_LEN) - 1) << PWM_STS_STOP_POS)
#define PWM_STS_STOP_UMSK     (~(((1U << PWM_STS_STOP_LEN) - 1) << PWM_STS_STOP_POS))
#define PWM_REG_CLK_SEL       PWM_REG_CLK_SEL
#define PWM_REG_CLK_SEL_POS   (30U)
#define PWM_REG_CLK_SEL_LEN   (2U)
#define PWM_REG_CLK_SEL_MSK   (((1U << PWM_REG_CLK_SEL_LEN) - 1) << PWM_REG_CLK_SEL_POS)
#define PWM_REG_CLK_SEL_UMSK  (~(((1U << PWM_REG_CLK_SEL_LEN) - 1) << PWM_REG_CLK_SEL_POS))

/* 0x04 : pwm0_config1 */
#define PWM0_CONFIG1_OFFSET (0x04)
#define PWM_CH0_PEN         PWM_CH0_PEN
#define PWM_CH0_PEN_POS     (0U)
#define PWM_CH0_PEN_LEN     (1U)
#define PWM_CH0_PEN_MSK     (((1U << PWM_CH0_PEN_LEN) - 1) << PWM_CH0_PEN_POS)
#define PWM_CH0_PEN_UMSK    (~(((1U << PWM_CH0_PEN_LEN) - 1) << PWM_CH0_PEN_POS))
#define PWM_CH0_PSI         PWM_CH0_PSI
#define PWM_CH0_PSI_POS     (1U)
#define PWM_CH0_PSI_LEN     (1U)
#define PWM_CH0_PSI_MSK     (((1U << PWM_CH0_PSI_LEN) - 1) << PWM_CH0_PSI_POS)
#define PWM_CH0_PSI_UMSK    (~(((1U << PWM_CH0_PSI_LEN) - 1) << PWM_CH0_PSI_POS))
#define PWM_CH0_NEN         PWM_CH0_NEN
#define PWM_CH0_NEN_POS     (2U)
#define PWM_CH0_NEN_LEN     (1U)
#define PWM_CH0_NEN_MSK     (((1U << PWM_CH0_NEN_LEN) - 1) << PWM_CH0_NEN_POS)
#define PWM_CH0_NEN_UMSK    (~(((1U << PWM_CH0_NEN_LEN) - 1) << PWM_CH0_NEN_POS))
#define PWM_CH0_NSI         PWM_CH0_NSI
#define PWM_CH0_NSI_POS     (3U)
#define PWM_CH0_NSI_LEN     (1U)
#define PWM_CH0_NSI_MSK     (((1U << PWM_CH0_NSI_LEN) - 1) << PWM_CH0_NSI_POS)
#define PWM_CH0_NSI_UMSK    (~(((1U << PWM_CH0_NSI_LEN) - 1) << PWM_CH0_NSI_POS))
#define PWM_CH1_PEN         PWM_CH1_PEN
#define PWM_CH1_PEN_POS     (4U)
#define PWM_CH1_PEN_LEN     (1U)
#define PWM_CH1_PEN_MSK     (((1U << PWM_CH1_PEN_LEN) - 1) << PWM_CH1_PEN_POS)
#define PWM_CH1_PEN_UMSK    (~(((1U << PWM_CH1_PEN_LEN) - 1) << PWM_CH1_PEN_POS))
#define PWM_CH1_PSI         PWM_CH1_PSI
#define PWM_CH1_PSI_POS     (5U)
#define PWM_CH1_PSI_LEN     (1U)
#define PWM_CH1_PSI_MSK     (((1U << PWM_CH1_PSI_LEN) - 1) << PWM_CH1_PSI_POS)
#define PWM_CH1_PSI_UMSK    (~(((1U << PWM_CH1_PSI_LEN) - 1) << PWM_CH1_PSI_POS))
#define PWM_CH1_NEN         PWM_CH1_NEN
#define PWM_CH1_NEN_POS     (6U)
#define PWM_CH1_NEN_LEN     (1U)
#define PWM_CH1_NEN_MSK     (((1U << PWM_CH1_NEN_LEN) - 1) << PWM_CH1_NEN_POS)
#define PWM_CH1_NEN_UMSK    (~(((1U << PWM_CH1_NEN_LEN) - 1) << PWM_CH1_NEN_POS))
#define PWM_CH1_NSI         PWM_CH1_NSI
#define PWM_CH1_NSI_POS     (7U)
#define PWM_CH1_NSI_LEN     (1U)
#define PWM_CH1_NSI_MSK     (((1U << PWM_CH1_NSI_LEN) - 1) << PWM_CH1_NSI_POS)
#define PWM_CH1_NSI_UMSK    (~(((1U << PWM_CH1_NSI_LEN) - 1) << PWM_CH1_NSI_POS))
#define PWM_CH2_PEN         PWM_CH2_PEN
#define PWM_CH2_PEN_POS     (8U)
#define PWM_CH2_PEN_LEN     (1U)
#define PWM_CH2_PEN_MSK     (((1U << PWM_CH2_PEN_LEN) - 1) << PWM_CH2_PEN_POS)
#define PWM_CH2_PEN_UMSK    (~(((1U << PWM_CH2_PEN_LEN) - 1) << PWM_CH2_PEN_POS))
#define PWM_CH2_PSI         PWM_CH2_PSI
#define PWM_CH2_PSI_POS     (9U)
#define PWM_CH2_PSI_LEN     (1U)
#define PWM_CH2_PSI_MSK     (((1U << PWM_CH2_PSI_LEN) - 1) << PWM_CH2_PSI_POS)
#define PWM_CH2_PSI_UMSK    (~(((1U << PWM_CH2_PSI_LEN) - 1) << PWM_CH2_PSI_POS))
#define PWM_CH2_NEN         PWM_CH2_NEN
#define PWM_CH2_NEN_POS     (10U)
#define PWM_CH2_NEN_LEN     (1U)
#define PWM_CH2_NEN_MSK     (((1U << PWM_CH2_NEN_LEN) - 1) << PWM_CH2_NEN_POS)
#define PWM_CH2_NEN_UMSK    (~(((1U << PWM_CH2_NEN_LEN) - 1) << PWM_CH2_NEN_POS))
#define PWM_CH2_NSI         PWM_CH2_NSI
#define PWM_CH2_NSI_POS     (11U)
#define PWM_CH2_NSI_LEN     (1U)
#define PWM_CH2_NSI_MSK     (((1U << PWM_CH2_NSI_LEN) - 1) << PWM_CH2_NSI_POS)
#define PWM_CH2_NSI_UMSK    (~(((1U << PWM_CH2_NSI_LEN) - 1) << PWM_CH2_NSI_POS))
#define PWM_CH3_PEN         PWM_CH3_PEN
#define PWM_CH3_PEN_POS     (12U)
#define PWM_CH3_PEN_LEN     (1U)
#define PWM_CH3_PEN_MSK     (((1U << PWM_CH3_PEN_LEN) - 1) << PWM_CH3_PEN_POS)
#define PWM_CH3_PEN_UMSK    (~(((1U << PWM_CH3_PEN_LEN) - 1) << PWM_CH3_PEN_POS))
#define PWM_CH3_PSI         PWM_CH3_PSI
#define PWM_CH3_PSI_POS     (13U)
#define PWM_CH3_PSI_LEN     (1U)
#define PWM_CH3_PSI_MSK     (((1U << PWM_CH3_PSI_LEN) - 1) << PWM_CH3_PSI_POS)
#define PWM_CH3_PSI_UMSK    (~(((1U << PWM_CH3_PSI_LEN) - 1) << PWM_CH3_PSI_POS))
#define PWM_CH3_NEN         PWM_CH3_NEN
#define PWM_CH3_NEN_POS     (14U)
#define PWM_CH3_NEN_LEN     (1U)
#define PWM_CH3_NEN_MSK     (((1U << PWM_CH3_NEN_LEN) - 1) << PWM_CH3_NEN_POS)
#define PWM_CH3_NEN_UMSK    (~(((1U << PWM_CH3_NEN_LEN) - 1) << PWM_CH3_NEN_POS))
#define PWM_CH3_NSI         PWM_CH3_NSI
#define PWM_CH3_NSI_POS     (15U)
#define PWM_CH3_NSI_LEN     (1U)
#define PWM_CH3_NSI_MSK     (((1U << PWM_CH3_NSI_LEN) - 1) << PWM_CH3_NSI_POS)
#define PWM_CH3_NSI_UMSK    (~(((1U << PWM_CH3_NSI_LEN) - 1) << PWM_CH3_NSI_POS))
#define PWM_CH0_PPL         PWM_CH0_PPL
#define PWM_CH0_PPL_POS     (16U)
#define PWM_CH0_PPL_LEN     (1U)
#define PWM_CH0_PPL_MSK     (((1U << PWM_CH0_PPL_LEN) - 1) << PWM_CH0_PPL_POS)
#define PWM_CH0_PPL_UMSK    (~(((1U << PWM_CH0_PPL_LEN) - 1) << PWM_CH0_PPL_POS))
#define PWM_CH0_NPL         PWM_CH0_NPL
#define PWM_CH0_NPL_POS     (17U)
#define PWM_CH0_NPL_LEN     (1U)
#define PWM_CH0_NPL_MSK     (((1U << PWM_CH0_NPL_LEN) - 1) << PWM_CH0_NPL_POS)
#define PWM_CH0_NPL_UMSK    (~(((1U << PWM_CH0_NPL_LEN) - 1) << PWM_CH0_NPL_POS))
#define PWM_CH1_PPL         PWM_CH1_PPL
#define PWM_CH1_PPL_POS     (18U)
#define PWM_CH1_PPL_LEN     (1U)
#define PWM_CH1_PPL_MSK     (((1U << PWM_CH1_PPL_LEN) - 1) << PWM_CH1_PPL_POS)
#define PWM_CH1_PPL_UMSK    (~(((1U << PWM_CH1_PPL_LEN) - 1) << PWM_CH1_PPL_POS))
#define PWM_CH1_NPL         PWM_CH1_NPL
#define PWM_CH1_NPL_POS     (19U)
#define PWM_CH1_NPL_LEN     (1U)
#define PWM_CH1_NPL_MSK     (((1U << PWM_CH1_NPL_LEN) - 1) << PWM_CH1_NPL_POS)
#define PWM_CH1_NPL_UMSK    (~(((1U << PWM_CH1_NPL_LEN) - 1) << PWM_CH1_NPL_POS))
#define PWM_CH2_PPL         PWM_CH2_PPL
#define PWM_CH2_PPL_POS     (20U)
#define PWM_CH2_PPL_LEN     (1U)
#define PWM_CH2_PPL_MSK     (((1U << PWM_CH2_PPL_LEN) - 1) << PWM_CH2_PPL_POS)
#define PWM_CH2_PPL_UMSK    (~(((1U << PWM_CH2_PPL_LEN) - 1) << PWM_CH2_PPL_POS))
#define PWM_CH2_NPL         PWM_CH2_NPL
#define PWM_CH2_NPL_POS     (21U)
#define PWM_CH2_NPL_LEN     (1U)
#define PWM_CH2_NPL_MSK     (((1U << PWM_CH2_NPL_LEN) - 1) << PWM_CH2_NPL_POS)
#define PWM_CH2_NPL_UMSK    (~(((1U << PWM_CH2_NPL_LEN) - 1) << PWM_CH2_NPL_POS))
#define PWM_CH3_PPL         PWM_CH3_PPL
#define PWM_CH3_PPL_POS     (22U)
#define PWM_CH3_PPL_LEN     (1U)
#define PWM_CH3_PPL_MSK     (((1U << PWM_CH3_PPL_LEN) - 1) << PWM_CH3_PPL_POS)
#define PWM_CH3_PPL_UMSK    (~(((1U << PWM_CH3_PPL_LEN) - 1) << PWM_CH3_PPL_POS))
#define PWM_CH3_NPL         PWM_CH3_NPL
#define PWM_CH3_NPL_POS     (23U)
#define PWM_CH3_NPL_LEN     (1U)
#define PWM_CH3_NPL_MSK     (((1U << PWM_CH3_NPL_LEN) - 1) << PWM_CH3_NPL_POS)
#define PWM_CH3_NPL_UMSK    (~(((1U << PWM_CH3_NPL_LEN) - 1) << PWM_CH3_NPL_POS))
#define PWM_CH0_PBS         PWM_CH0_PBS
#define PWM_CH0_PBS_POS     (24U)
#define PWM_CH0_PBS_LEN     (1U)
#define PWM_CH0_PBS_MSK     (((1U << PWM_CH0_PBS_LEN) - 1) << PWM_CH0_PBS_POS)
#define PWM_CH0_PBS_UMSK    (~(((1U << PWM_CH0_PBS_LEN) - 1) << PWM_CH0_PBS_POS))
#define PWM_CH0_NBS         PWM_CH0_NBS
#define PWM_CH0_NBS_POS     (25U)
#define PWM_CH0_NBS_LEN     (1U)
#define PWM_CH0_NBS_MSK     (((1U << PWM_CH0_NBS_LEN) - 1) << PWM_CH0_NBS_POS)
#define PWM_CH0_NBS_UMSK    (~(((1U << PWM_CH0_NBS_LEN) - 1) << PWM_CH0_NBS_POS))
#define PWM_CH1_PBS         PWM_CH1_PBS
#define PWM_CH1_PBS_POS     (26U)
#define PWM_CH1_PBS_LEN     (1U)
#define PWM_CH1_PBS_MSK     (((1U << PWM_CH1_PBS_LEN) - 1) << PWM_CH1_PBS_POS)
#define PWM_CH1_PBS_UMSK    (~(((1U << PWM_CH1_PBS_LEN) - 1) << PWM_CH1_PBS_POS))
#define PWM_CH1_NBS         PWM_CH1_NBS
#define PWM_CH1_NBS_POS     (27U)
#define PWM_CH1_NBS_LEN     (1U)
#define PWM_CH1_NBS_MSK     (((1U << PWM_CH1_NBS_LEN) - 1) << PWM_CH1_NBS_POS)
#define PWM_CH1_NBS_UMSK    (~(((1U << PWM_CH1_NBS_LEN) - 1) << PWM_CH1_NBS_POS))
#define PWM_CH2_PBS         PWM_CH2_PBS
#define PWM_CH2_PBS_POS     (28U)
#define PWM_CH2_PBS_LEN     (1U)
#define PWM_CH2_PBS_MSK     (((1U << PWM_CH2_PBS_LEN) - 1) << PWM_CH2_PBS_POS)
#define PWM_CH2_PBS_UMSK    (~(((1U << PWM_CH2_PBS_LEN) - 1) << PWM_CH2_PBS_POS))
#define PWM_CH2_NBS         PWM_CH2_NBS
#define PWM_CH2_NBS_POS     (29U)
#define PWM_CH2_NBS_LEN     (1U)
#define PWM_CH2_NBS_MSK     (((1U << PWM_CH2_NBS_LEN) - 1) << PWM_CH2_NBS_POS)
#define PWM_CH2_NBS_UMSK    (~(((1U << PWM_CH2_NBS_LEN) - 1) << PWM_CH2_NBS_POS))
#define PWM_CH3_PBS         PWM_CH3_PBS
#define PWM_CH3_PBS_POS     (30U)
#define PWM_CH3_PBS_LEN     (1U)
#define PWM_CH3_PBS_MSK     (((1U << PWM_CH3_PBS_LEN) - 1) << PWM_CH3_PBS_POS)
#define PWM_CH3_PBS_UMSK    (~(((1U << PWM_CH3_PBS_LEN) - 1) << PWM_CH3_PBS_POS))
#define PWM_CH3_NBS         PWM_CH3_NBS
#define PWM_CH3_NBS_POS     (31U)
#define PWM_CH3_NBS_LEN     (1U)
#define PWM_CH3_NBS_MSK     (((1U << PWM_CH3_NBS_LEN) - 1) << PWM_CH3_NBS_POS)
#define PWM_CH3_NBS_UMSK    (~(((1U << PWM_CH3_NBS_LEN) - 1) << PWM_CH3_NBS_POS))
/* 0x08 : pwm0_period */
#define PWM0_PERIOD_OFFSET      (0x08)
#define PWM_PERIOD              PWM_PERIOD
#define PWM_PERIOD_POS          (0U)
#define PWM_PERIOD_LEN          (16U)
#define PWM_PERIOD_MSK          (((1U << PWM_PERIOD_LEN) - 1) << PWM_PERIOD_POS)
#define PWM_PERIOD_UMSK         (~(((1U << PWM_PERIOD_LEN) - 1) << PWM_PERIOD_POS))
#define PWM_INT_PERIOD_CNT      PWM_INT_PERIOD_CNT
#define PWM_INT_PERIOD_CNT_POS  (16U)
#define PWM_INT_PERIOD_CNT_LEN  (16U)
#define PWM_INT_PERIOD_CNT_MSK  (((1U << PWM_INT_PERIOD_CNT_LEN) - 1) << PWM_INT_PERIOD_CNT_POS)
#define PWM_INT_PERIOD_CNT_UMSK (~(((1U << PWM_INT_PERIOD_CNT_LEN) - 1) << PWM_INT_PERIOD_CNT_POS))

/* 0x0C : pwm0_dead_time */
#define PWM0_DEAD_TIME_OFFSET (0x0C)
#define PWM_CH0_DTG           PWM_CH0_DTG
#define PWM_CH0_DTG_POS       (0U)
#define PWM_CH0_DTG_LEN       (8U)
#define PWM_CH0_DTG_MSK       (((1U << PWM_CH0_DTG_LEN) - 1) << PWM_CH0_DTG_POS)
#define PWM_CH0_DTG_UMSK      (~(((1U << PWM_CH0_DTG_LEN) - 1) << PWM_CH0_DTG_POS))
#define PWM_CH1_DTG           PWM_CH1_DTG
#define PWM_CH1_DTG_POS       (8U)
#define PWM_CH1_DTG_LEN       (8U)
#define PWM_CH1_DTG_MSK       (((1U << PWM_CH1_DTG_LEN) - 1) << PWM_CH1_DTG_POS)
#define PWM_CH1_DTG_UMSK      (~(((1U << PWM_CH1_DTG_LEN) - 1) << PWM_CH1_DTG_POS))
#define PWM_CH2_DTG           PWM_CH2_DTG
#define PWM_CH2_DTG_POS       (16U)
#define PWM_CH2_DTG_LEN       (8U)
#define PWM_CH2_DTG_MSK       (((1U << PWM_CH2_DTG_LEN) - 1) << PWM_CH2_DTG_POS)
#define PWM_CH2_DTG_UMSK      (~(((1U << PWM_CH2_DTG_LEN) - 1) << PWM_CH2_DTG_POS))
#define PWM_CH3_DTG           PWM_CH3_DTG
#define PWM_CH3_DTG_POS       (24U)
#define PWM_CH3_DTG_LEN       (8U)
#define PWM_CH3_DTG_MSK       (((1U << PWM_CH3_DTG_LEN) - 1) << PWM_CH3_DTG_POS)
#define PWM_CH3_DTG_UMSK      (~(((1U << PWM_CH3_DTG_LEN) - 1) << PWM_CH3_DTG_POS))

/* 0x10 : pwm0_ch0_thre */
#define PWM0_CH0_THRE_OFFSET (0x10)
#define PWM_CH0_THREL        PWM_CH0_THREL
#define PWM_CH0_THREL_POS    (0U)
#define PWM_CH0_THREL_LEN    (16U)
#define PWM_CH0_THREL_MSK    (((1U << PWM_CH0_THREL_LEN) - 1) << PWM_CH0_THREL_POS)
#define PWM_CH0_THREL_UMSK   (~(((1U << PWM_CH0_THREL_LEN) - 1) << PWM_CH0_THREL_POS))
#define PWM_CH0_THREH        PWM_CH0_THREH
#define PWM_CH0_THREH_POS    (16U)
#define PWM_CH0_THREH_LEN    (16U)
#define PWM_CH0_THREH_MSK    (((1U << PWM_CH0_THREH_LEN) - 1) << PWM_CH0_THREH_POS)
#define PWM_CH0_THREH_UMSK   (~(((1U << PWM_CH0_THREH_LEN) - 1) << PWM_CH0_THREH_POS))

/* 0x14 : pwm0_ch1_thre */
#define PWM0_CH1_THRE_OFFSET (0x14)
#define PWM_CH1_THREL        PWM_CH1_THREL
#define PWM_CH1_THREL_POS    (0U)
#define PWM_CH1_THREL_LEN    (16U)
#define PWM_CH1_THREL_MSK    (((1U << PWM_CH1_THREL_LEN) - 1) << PWM_CH1_THREL_POS)
#define PWM_CH1_THREL_UMSK   (~(((1U << PWM_CH1_THREL_LEN) - 1) << PWM_CH1_THREL_POS))
#define PWM_CH1_THREH        PWM_CH1_THREH
#define PWM_CH1_THREH_POS    (16U)
#define PWM_CH1_THREH_LEN    (16U)
#define PWM_CH1_THREH_MSK    (((1U << PWM_CH1_THREH_LEN) - 1) << PWM_CH1_THREH_POS)
#define PWM_CH1_THREH_UMSK   (~(((1U << PWM_CH1_THREH_LEN) - 1) << PWM_CH1_THREH_POS))

/* 0x18 : pwm0_ch2_thre */
#define PWM0_CH2_THRE_OFFSET (0x18)
#define PWM_CH2_THREL        PWM_CH2_THREL
#define PWM_CH2_THREL_POS    (0U)
#define PWM_CH2_THREL_LEN    (16U)
#define PWM_CH2_THREL_MSK    (((1U << PWM_CH2_THREL_LEN) - 1) << PWM_CH2_THREL_POS)
#define PWM_CH2_THREL_UMSK   (~(((1U << PWM_CH2_THREL_LEN) - 1) << PWM_CH2_THREL_POS))
#define PWM_CH2_THREH        PWM_CH2_THREH
#define PWM_CH2_THREH_POS    (16U)
#define PWM_CH2_THREH_LEN    (16U)
#define PWM_CH2_THREH_MSK    (((1U << PWM_CH2_THREH_LEN) - 1) << PWM_CH2_THREH_POS)
#define PWM_CH2_THREH_UMSK   (~(((1U << PWM_CH2_THREH_LEN) - 1) << PWM_CH2_THREH_POS))

/* 0x1C : pwm0_ch3_thre */
#define PWM0_CH3_THRE_OFFSET (0x1C)
#define PWM_CH3_THREL        PWM_CH3_THREL
#define PWM_CH3_THREL_POS    (0U)
#define PWM_CH3_THREL_LEN    (16U)
#define PWM_CH3_THREL_MSK    (((1U << PWM_CH3_THREL_LEN) - 1) << PWM_CH3_THREL_POS)
#define PWM_CH3_THREL_UMSK   (~(((1U << PWM_CH3_THREL_LEN) - 1) << PWM_CH3_THREL_POS))
#define PWM_CH3_THREH        PWM_CH3_THREH
#define PWM_CH3_THREH_POS    (16U)
#define PWM_CH3_THREH_LEN    (16U)
#define PWM_CH3_THREH_MSK    (((1U << PWM_CH3_THREH_LEN) - 1) << PWM_CH3_THREH_POS)
#define PWM_CH3_THREH_UMSK   (~(((1U << PWM_CH3_THREH_LEN) - 1) << PWM_CH3_THREH_POS))

/* 0x20 : pwm0_int_sts */
#define PWM0_INT_STS_OFFSET (0x20)
#define PWM_CH0L_INT        PWM_CH0L_INT
#define PWM_CH0L_INT_POS    (0U)
#define PWM_CH0L_INT_LEN    (1U)
#define PWM_CH0L_INT_MSK    (((1U << PWM_CH0L_INT_LEN) - 1) << PWM_CH0L_INT_POS)
#define PWM_CH0L_INT_UMSK   (~(((1U << PWM_CH0L_INT_LEN) - 1) << PWM_CH0L_INT_POS))
#define PWM_CH0H_INT        PWM_CH0H_INT
#define PWM_CH0H_INT_POS    (1U)
#define PWM_CH0H_INT_LEN    (1U)
#define PWM_CH0H_INT_MSK    (((1U << PWM_CH0H_INT_LEN) - 1) << PWM_CH0H_INT_POS)
#define PWM_CH0H_INT_UMSK   (~(((1U << PWM_CH0H_INT_LEN) - 1) << PWM_CH0H_INT_POS))
#define PWM_CH1L_INT        PWM_CH1L_INT
#define PWM_CH1L_INT_POS    (2U)
#define PWM_CH1L_INT_LEN    (1U)
#define PWM_CH1L_INT_MSK    (((1U << PWM_CH1L_INT_LEN) - 1) << PWM_CH1L_INT_POS)
#define PWM_CH1L_INT_UMSK   (~(((1U << PWM_CH1L_INT_LEN) - 1) << PWM_CH1L_INT_POS))
#define PWM_CH1H_INT        PWM_CH1H_INT
#define PWM_CH1H_INT_POS    (3U)
#define PWM_CH1H_INT_LEN    (1U)
#define PWM_CH1H_INT_MSK    (((1U << PWM_CH1H_INT_LEN) - 1) << PWM_CH1H_INT_POS)
#define PWM_CH1H_INT_UMSK   (~(((1U << PWM_CH1H_INT_LEN) - 1) << PWM_CH1H_INT_POS))
#define PWM_CH2L_INT        PWM_CH2L_INT
#define PWM_CH2L_INT_POS    (4U)
#define PWM_CH2L_INT_LEN    (1U)
#define PWM_CH2L_INT_MSK    (((1U << PWM_CH2L_INT_LEN) - 1) << PWM_CH2L_INT_POS)
#define PWM_CH2L_INT_UMSK   (~(((1U << PWM_CH2L_INT_LEN) - 1) << PWM_CH2L_INT_POS))
#define PWM_CH2H_INT        PWM_CH2H_INT
#define PWM_CH2H_INT_POS    (5U)
#define PWM_CH2H_INT_LEN    (1U)
#define PWM_CH2H_INT_MSK    (((1U << PWM_CH2H_INT_LEN) - 1) << PWM_CH2H_INT_POS)
#define PWM_CH2H_INT_UMSK   (~(((1U << PWM_CH2H_INT_LEN) - 1) << PWM_CH2H_INT_POS))
#define PWM_CH3L_INT        PWM_CH3L_INT
#define PWM_CH3L_INT_POS    (6U)
#define PWM_CH3L_INT_LEN    (1U)
#define PWM_CH3L_INT_MSK    (((1U << PWM_CH3L_INT_LEN) - 1) << PWM_CH3L_INT_POS)
#define PWM_CH3L_INT_UMSK   (~(((1U << PWM_CH3L_INT_LEN) - 1) << PWM_CH3L_INT_POS))
#define PWM_CH3H_INT        PWM_CH3H_INT
#define PWM_CH3H_INT_POS    (7U)
#define PWM_CH3H_INT_LEN    (1U)
#define PWM_CH3H_INT_MSK    (((1U << PWM_CH3H_INT_LEN) - 1) << PWM_CH3H_INT_POS)
#define PWM_CH3H_INT_UMSK   (~(((1U << PWM_CH3H_INT_LEN) - 1) << PWM_CH3H_INT_POS))
#define PWM_PRDE_INT        PWM_PRDE_INT
#define PWM_PRDE_INT_POS    (8U)
#define PWM_PRDE_INT_LEN    (1U)
#define PWM_PRDE_INT_MSK    (((1U << PWM_PRDE_INT_LEN) - 1) << PWM_PRDE_INT_POS)
#define PWM_PRDE_INT_UMSK   (~(((1U << PWM_PRDE_INT_LEN) - 1) << PWM_PRDE_INT_POS))
#define PWM_BRK_INT         PWM_BRK_INT
#define PWM_BRK_INT_POS     (9U)
#define PWM_BRK_INT_LEN     (1U)
#define PWM_BRK_INT_MSK     (((1U << PWM_BRK_INT_LEN) - 1) << PWM_BRK_INT_POS)
#define PWM_BRK_INT_UMSK    (~(((1U << PWM_BRK_INT_LEN) - 1) << PWM_BRK_INT_POS))
#define PWM_REPT_INT        PWM_REPT_INT
#define PWM_REPT_INT_POS    (10U)
#define PWM_REPT_INT_LEN    (1U)
#define PWM_REPT_INT_MSK    (((1U << PWM_REPT_INT_LEN) - 1) << PWM_REPT_INT_POS)
#define PWM_REPT_INT_UMSK   (~(((1U << PWM_REPT_INT_LEN) - 1) << PWM_REPT_INT_POS))

/* 0x24 : pwm0_int_mask */
#define PWM0_INT_MASK_OFFSET      (0x24)
#define PWM_CR_PWM_CH0L_MASK      PWM_CR_PWM_CH0L_MASK
#define PWM_CR_PWM_CH0L_MASK_POS  (0U)
#define PWM_CR_PWM_CH0L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH0L_MASK_MSK  (((1U << PWM_CR_PWM_CH0L_MASK_LEN) - 1) << PWM_CR_PWM_CH0L_MASK_POS)
#define PWM_CR_PWM_CH0L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH0L_MASK_LEN) - 1) << PWM_CR_PWM_CH0L_MASK_POS))
#define PWM_CR_PWM_CH0H_MASK      PWM_CR_PWM_CH0H_MASK
#define PWM_CR_PWM_CH0H_MASK_POS  (1U)
#define PWM_CR_PWM_CH0H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH0H_MASK_MSK  (((1U << PWM_CR_PWM_CH0H_MASK_LEN) - 1) << PWM_CR_PWM_CH0H_MASK_POS)
#define PWM_CR_PWM_CH0H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH0H_MASK_LEN) - 1) << PWM_CR_PWM_CH0H_MASK_POS))
#define PWM_CR_PWM_CH1L_MASK      PWM_CR_PWM_CH1L_MASK
#define PWM_CR_PWM_CH1L_MASK_POS  (2U)
#define PWM_CR_PWM_CH1L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH1L_MASK_MSK  (((1U << PWM_CR_PWM_CH1L_MASK_LEN) - 1) << PWM_CR_PWM_CH1L_MASK_POS)
#define PWM_CR_PWM_CH1L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH1L_MASK_LEN) - 1) << PWM_CR_PWM_CH1L_MASK_POS))
#define PWM_CR_PWM_CH1H_MASK      PWM_CR_PWM_CH1H_MASK
#define PWM_CR_PWM_CH1H_MASK_POS  (3U)
#define PWM_CR_PWM_CH1H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH1H_MASK_MSK  (((1U << PWM_CR_PWM_CH1H_MASK_LEN) - 1) << PWM_CR_PWM_CH1H_MASK_POS)
#define PWM_CR_PWM_CH1H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH1H_MASK_LEN) - 1) << PWM_CR_PWM_CH1H_MASK_POS))
#define PWM_CR_PWM_CH2L_MASK      PWM_CR_PWM_CH2L_MASK
#define PWM_CR_PWM_CH2L_MASK_POS  (4U)
#define PWM_CR_PWM_CH2L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH2L_MASK_MSK  (((1U << PWM_CR_PWM_CH2L_MASK_LEN) - 1) << PWM_CR_PWM_CH2L_MASK_POS)
#define PWM_CR_PWM_CH2L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH2L_MASK_LEN) - 1) << PWM_CR_PWM_CH2L_MASK_POS))
#define PWM_CR_PWM_CH2H_MASK      PWM_CR_PWM_CH2H_MASK
#define PWM_CR_PWM_CH2H_MASK_POS  (5U)
#define PWM_CR_PWM_CH2H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH2H_MASK_MSK  (((1U << PWM_CR_PWM_CH2H_MASK_LEN) - 1) << PWM_CR_PWM_CH2H_MASK_POS)
#define PWM_CR_PWM_CH2H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH2H_MASK_LEN) - 1) << PWM_CR_PWM_CH2H_MASK_POS))
#define PWM_CR_PWM_CH3L_MASK      PWM_CR_PWM_CH3L_MASK
#define PWM_CR_PWM_CH3L_MASK_POS  (6U)
#define PWM_CR_PWM_CH3L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH3L_MASK_MSK  (((1U << PWM_CR_PWM_CH3L_MASK_LEN) - 1) << PWM_CR_PWM_CH3L_MASK_POS)
#define PWM_CR_PWM_CH3L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH3L_MASK_LEN) - 1) << PWM_CR_PWM_CH3L_MASK_POS))
#define PWM_CR_PWM_CH3H_MASK      PWM_CR_PWM_CH3H_MASK
#define PWM_CR_PWM_CH3H_MASK_POS  (7U)
#define PWM_CR_PWM_CH3H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH3H_MASK_MSK  (((1U << PWM_CR_PWM_CH3H_MASK_LEN) - 1) << PWM_CR_PWM_CH3H_MASK_POS)
#define PWM_CR_PWM_CH3H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH3H_MASK_LEN) - 1) << PWM_CR_PWM_CH3H_MASK_POS))
#define PWM_CR_PWM_PRDE_MASK      PWM_CR_PWM_PRDE_MASK
#define PWM_CR_PWM_PRDE_MASK_POS  (8U)
#define PWM_CR_PWM_PRDE_MASK_LEN  (1U)
#define PWM_CR_PWM_PRDE_MASK_MSK  (((1U << PWM_CR_PWM_PRDE_MASK_LEN) - 1) << PWM_CR_PWM_PRDE_MASK_POS)
#define PWM_CR_PWM_PRDE_MASK_UMSK (~(((1U << PWM_CR_PWM_PRDE_MASK_LEN) - 1) << PWM_CR_PWM_PRDE_MASK_POS))
#define PWM_CR_PWM_BRK_MASK       PWM_CR_PWM_BRK_MASK
#define PWM_CR_PWM_BRK_MASK_POS   (9U)
#define PWM_CR_PWM_BRK_MASK_LEN   (1U)
#define PWM_CR_PWM_BRK_MASK_MSK   (((1U << PWM_CR_PWM_BRK_MASK_LEN) - 1) << PWM_CR_PWM_BRK_MASK_POS)
#define PWM_CR_PWM_BRK_MASK_UMSK  (~(((1U << PWM_CR_PWM_BRK_MASK_LEN) - 1) << PWM_CR_PWM_BRK_MASK_POS))
#define PWM_CR_PWM_REPT_MASK      PWM_CR_PWM_REPT_MASK
#define PWM_CR_PWM_REPT_MASK_POS  (10U)
#define PWM_CR_PWM_REPT_MASK_LEN  (1U)
#define PWM_CR_PWM_REPT_MASK_MSK  (((1U << PWM_CR_PWM_REPT_MASK_LEN) - 1) << PWM_CR_PWM_REPT_MASK_POS)
#define PWM_CR_PWM_REPT_MASK_UMSK (~(((1U << PWM_CR_PWM_REPT_MASK_LEN) - 1) << PWM_CR_PWM_REPT_MASK_POS))

/* 0x28 : pwm0_int_clear */
#define PWM0_INT_CLEAR_OFFSET    (0x28)
#define PWM_CR_PWM_CH0L_CLR      PWM_CR_PWM_CH0L_CLR
#define PWM_CR_PWM_CH0L_CLR_POS  (0U)
#define PWM_CR_PWM_CH0L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH0L_CLR_MSK  (((1U << PWM_CR_PWM_CH0L_CLR_LEN) - 1) << PWM_CR_PWM_CH0L_CLR_POS)
#define PWM_CR_PWM_CH0L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH0L_CLR_LEN) - 1) << PWM_CR_PWM_CH0L_CLR_POS))
#define PWM_CR_PWM_CH0H_CLR      PWM_CR_PWM_CH0H_CLR
#define PWM_CR_PWM_CH0H_CLR_POS  (1U)
#define PWM_CR_PWM_CH0H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH0H_CLR_MSK  (((1U << PWM_CR_PWM_CH0H_CLR_LEN) - 1) << PWM_CR_PWM_CH0H_CLR_POS)
#define PWM_CR_PWM_CH0H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH0H_CLR_LEN) - 1) << PWM_CR_PWM_CH0H_CLR_POS))
#define PWM_CR_PWM_CH1L_CLR      PWM_CR_PWM_CH1L_CLR
#define PWM_CR_PWM_CH1L_CLR_POS  (2U)
#define PWM_CR_PWM_CH1L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH1L_CLR_MSK  (((1U << PWM_CR_PWM_CH1L_CLR_LEN) - 1) << PWM_CR_PWM_CH1L_CLR_POS)
#define PWM_CR_PWM_CH1L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH1L_CLR_LEN) - 1) << PWM_CR_PWM_CH1L_CLR_POS))
#define PWM_CR_PWM_CH1H_CLR      PWM_CR_PWM_CH1H_CLR
#define PWM_CR_PWM_CH1H_CLR_POS  (3U)
#define PWM_CR_PWM_CH1H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH1H_CLR_MSK  (((1U << PWM_CR_PWM_CH1H_CLR_LEN) - 1) << PWM_CR_PWM_CH1H_CLR_POS)
#define PWM_CR_PWM_CH1H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH1H_CLR_LEN) - 1) << PWM_CR_PWM_CH1H_CLR_POS))
#define PWM_CR_PWM_CH2L_CLR      PWM_CR_PWM_CH2L_CLR
#define PWM_CR_PWM_CH2L_CLR_POS  (4U)
#define PWM_CR_PWM_CH2L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH2L_CLR_MSK  (((1U << PWM_CR_PWM_CH2L_CLR_LEN) - 1) << PWM_CR_PWM_CH2L_CLR_POS)
#define PWM_CR_PWM_CH2L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH2L_CLR_LEN) - 1) << PWM_CR_PWM_CH2L_CLR_POS))
#define PWM_CR_PWM_CH2H_CLR      PWM_CR_PWM_CH2H_CLR
#define PWM_CR_PWM_CH2H_CLR_POS  (5U)
#define PWM_CR_PWM_CH2H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH2H_CLR_MSK  (((1U << PWM_CR_PWM_CH2H_CLR_LEN) - 1) << PWM_CR_PWM_CH2H_CLR_POS)
#define PWM_CR_PWM_CH2H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH2H_CLR_LEN) - 1) << PWM_CR_PWM_CH2H_CLR_POS))
#define PWM_CR_PWM_CH3L_CLR      PWM_CR_PWM_CH3L_CLR
#define PWM_CR_PWM_CH3L_CLR_POS  (6U)
#define PWM_CR_PWM_CH3L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH3L_CLR_MSK  (((1U << PWM_CR_PWM_CH3L_CLR_LEN) - 1) << PWM_CR_PWM_CH3L_CLR_POS)
#define PWM_CR_PWM_CH3L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH3L_CLR_LEN) - 1) << PWM_CR_PWM_CH3L_CLR_POS))
#define PWM_CR_PWM_CH3H_CLR      PWM_CR_PWM_CH3H_CLR
#define PWM_CR_PWM_CH3H_CLR_POS  (7U)
#define PWM_CR_PWM_CH3H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH3H_CLR_MSK  (((1U << PWM_CR_PWM_CH3H_CLR_LEN) - 1) << PWM_CR_PWM_CH3H_CLR_POS)
#define PWM_CR_PWM_CH3H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH3H_CLR_LEN) - 1) << PWM_CR_PWM_CH3H_CLR_POS))
#define PWM_CR_PWM_PRDE_CLR      PWM_CR_PWM_PRDE_CLR
#define PWM_CR_PWM_PRDE_CLR_POS  (8U)
#define PWM_CR_PWM_PRDE_CLR_LEN  (1U)
#define PWM_CR_PWM_PRDE_CLR_MSK  (((1U << PWM_CR_PWM_PRDE_CLR_LEN) - 1) << PWM_CR_PWM_PRDE_CLR_POS)
#define PWM_CR_PWM_PRDE_CLR_UMSK (~(((1U << PWM_CR_PWM_PRDE_CLR_LEN) - 1) << PWM_CR_PWM_PRDE_CLR_POS))
#define PWM_CR_PWM_BRK_CLR       PWM_CR_PWM_BRK_CLR
#define PWM_CR_PWM_BRK_CLR_POS   (9U)
#define PWM_CR_PWM_BRK_CLR_LEN   (1U)
#define PWM_CR_PWM_BRK_CLR_MSK   (((1U << PWM_CR_PWM_BRK_CLR_LEN) - 1) << PWM_CR_PWM_BRK_CLR_POS)
#define PWM_CR_PWM_BRK_CLR_UMSK  (~(((1U << PWM_CR_PWM_BRK_CLR_LEN) - 1) << PWM_CR_PWM_BRK_CLR_POS))
#define PWM_CR_PWM_REPT_CLR      PWM_CR_PWM_REPT_CLR
#define PWM_CR_PWM_REPT_CLR_POS  (10U)
#define PWM_CR_PWM_REPT_CLR_LEN  (1U)
#define PWM_CR_PWM_REPT_CLR_MSK  (((1U << PWM_CR_PWM_REPT_CLR_LEN) - 1) << PWM_CR_PWM_REPT_CLR_POS)
#define PWM_CR_PWM_REPT_CLR_UMSK (~(((1U << PWM_CR_PWM_REPT_CLR_LEN) - 1) << PWM_CR_PWM_REPT_CLR_POS))

/* 0x2C : pwm0_int_en */
#define PWM0_INT_EN_OFFSET      (0x2C)
#define PWM_CR_PWM_CH0L_EN      PWM_CR_PWM_CH0L_EN
#define PWM_CR_PWM_CH0L_EN_POS  (0U)
#define PWM_CR_PWM_CH0L_EN_LEN  (1U)
#define PWM_CR_PWM_CH0L_EN_MSK  (((1U << PWM_CR_PWM_CH0L_EN_LEN) - 1) << PWM_CR_PWM_CH0L_EN_POS)
#define PWM_CR_PWM_CH0L_EN_UMSK (~(((1U << PWM_CR_PWM_CH0L_EN_LEN) - 1) << PWM_CR_PWM_CH0L_EN_POS))
#define PWM_CR_PWM_CH0H_EN      PWM_CR_PWM_CH0H_EN
#define PWM_CR_PWM_CH0H_EN_POS  (1U)
#define PWM_CR_PWM_CH0H_EN_LEN  (1U)
#define PWM_CR_PWM_CH0H_EN_MSK  (((1U << PWM_CR_PWM_CH0H_EN_LEN) - 1) << PWM_CR_PWM_CH0H_EN_POS)
#define PWM_CR_PWM_CH0H_EN_UMSK (~(((1U << PWM_CR_PWM_CH0H_EN_LEN) - 1) << PWM_CR_PWM_CH0H_EN_POS))
#define PWM_CR_PWM_CH1L_EN      PWM_CR_PWM_CH1L_EN
#define PWM_CR_PWM_CH1L_EN_POS  (2U)
#define PWM_CR_PWM_CH1L_EN_LEN  (1U)
#define PWM_CR_PWM_CH1L_EN_MSK  (((1U << PWM_CR_PWM_CH1L_EN_LEN) - 1) << PWM_CR_PWM_CH1L_EN_POS)
#define PWM_CR_PWM_CH1L_EN_UMSK (~(((1U << PWM_CR_PWM_CH1L_EN_LEN) - 1) << PWM_CR_PWM_CH1L_EN_POS))
#define PWM_CR_PWM_CH1H_EN      PWM_CR_PWM_CH1H_EN
#define PWM_CR_PWM_CH1H_EN_POS  (3U)
#define PWM_CR_PWM_CH1H_EN_LEN  (1U)
#define PWM_CR_PWM_CH1H_EN_MSK  (((1U << PWM_CR_PWM_CH1H_EN_LEN) - 1) << PWM_CR_PWM_CH1H_EN_POS)
#define PWM_CR_PWM_CH1H_EN_UMSK (~(((1U << PWM_CR_PWM_CH1H_EN_LEN) - 1) << PWM_CR_PWM_CH1H_EN_POS))
#define PWM_CR_PWM_CH2L_EN      PWM_CR_PWM_CH2L_EN
#define PWM_CR_PWM_CH2L_EN_POS  (4U)
#define PWM_CR_PWM_CH2L_EN_LEN  (1U)
#define PWM_CR_PWM_CH2L_EN_MSK  (((1U << PWM_CR_PWM_CH2L_EN_LEN) - 1) << PWM_CR_PWM_CH2L_EN_POS)
#define PWM_CR_PWM_CH2L_EN_UMSK (~(((1U << PWM_CR_PWM_CH2L_EN_LEN) - 1) << PWM_CR_PWM_CH2L_EN_POS))
#define PWM_CR_PWM_CH2H_EN      PWM_CR_PWM_CH2H_EN
#define PWM_CR_PWM_CH2H_EN_POS  (5U)
#define PWM_CR_PWM_CH2H_EN_LEN  (1U)
#define PWM_CR_PWM_CH2H_EN_MSK  (((1U << PWM_CR_PWM_CH2H_EN_LEN) - 1) << PWM_CR_PWM_CH2H_EN_POS)
#define PWM_CR_PWM_CH2H_EN_UMSK (~(((1U << PWM_CR_PWM_CH2H_EN_LEN) - 1) << PWM_CR_PWM_CH2H_EN_POS))
#define PWM_CR_PWM_CH3L_EN      PWM_CR_PWM_CH3L_EN
#define PWM_CR_PWM_CH3L_EN_POS  (6U)
#define PWM_CR_PWM_CH3L_EN_LEN  (1U)
#define PWM_CR_PWM_CH3L_EN_MSK  (((1U << PWM_CR_PWM_CH3L_EN_LEN) - 1) << PWM_CR_PWM_CH3L_EN_POS)
#define PWM_CR_PWM_CH3L_EN_UMSK (~(((1U << PWM_CR_PWM_CH3L_EN_LEN) - 1) << PWM_CR_PWM_CH3L_EN_POS))
#define PWM_CR_PWM_CH3H_EN      PWM_CR_PWM_CH3H_EN
#define PWM_CR_PWM_CH3H_EN_POS  (7U)
#define PWM_CR_PWM_CH3H_EN_LEN  (1U)
#define PWM_CR_PWM_CH3H_EN_MSK  (((1U << PWM_CR_PWM_CH3H_EN_LEN) - 1) << PWM_CR_PWM_CH3H_EN_POS)
#define PWM_CR_PWM_CH3H_EN_UMSK (~(((1U << PWM_CR_PWM_CH3H_EN_LEN) - 1) << PWM_CR_PWM_CH3H_EN_POS))
#define PWM_CR_PWM_PRDE_EN      PWM_CR_PWM_PRDE_EN
#define PWM_CR_PWM_PRDE_EN_POS  (8U)
#define PWM_CR_PWM_PRDE_EN_LEN  (1U)
#define PWM_CR_PWM_PRDE_EN_MSK  (((1U << PWM_CR_PWM_PRDE_EN_LEN) - 1) << PWM_CR_PWM_PRDE_EN_POS)
#define PWM_CR_PWM_PRDE_EN_UMSK (~(((1U << PWM_CR_PWM_PRDE_EN_LEN) - 1) << PWM_CR_PWM_PRDE_EN_POS))
#define PWM_CR_PWM_BRK_EN       PWM_CR_PWM_BRK_EN
#define PWM_CR_PWM_BRK_EN_POS   (9U)
#define PWM_CR_PWM_BRK_EN_LEN   (1U)
#define PWM_CR_PWM_BRK_EN_MSK   (((1U << PWM_CR_PWM_BRK_EN_LEN) - 1) << PWM_CR_PWM_BRK_EN_POS)
#define PWM_CR_PWM_BRK_EN_UMSK  (~(((1U << PWM_CR_PWM_BRK_EN_LEN) - 1) << PWM_CR_PWM_BRK_EN_POS))
#define PWM_CR_PWM_REPT_EN      PWM_CR_PWM_REPT_EN
#define PWM_CR_PWM_REPT_EN_POS  (10U)
#define PWM_CR_PWM_REPT_EN_LEN  (1U)
#define PWM_CR_PWM_REPT_EN_MSK  (((1U << PWM_CR_PWM_REPT_EN_LEN) - 1) << PWM_CR_PWM_REPT_EN_POS)
#define PWM_CR_PWM_REPT_EN_UMSK (~(((1U << PWM_CR_PWM_REPT_EN_LEN) - 1) << PWM_CR_PWM_REPT_EN_POS))

struct pwm_reg {
    /* 0x00 : pwm0_config0 */
    union {
        struct {
            uint32_t pwm_clk_div      : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_18   : 3;  /* [18:16],       rsvd,        0x0 */
            uint32_t pwm_stop_on_rept : 1;  /* [   19],        r/w,        0x0 */
            uint32_t pwm_adc_trg_src  : 4;  /* [23:20],        r/w,        0xf */
            uint32_t pwm_sw_break_en  : 1;  /* [   24],        r/w,        0x0 */
            uint32_t pwm_ext_break_en : 1;  /* [   25],        r/w,        0x0 */
            uint32_t pwm_ext_break_pl : 1;  /* [   26],        r/w,        0x0 */
            uint32_t pwm_stop_en      : 1;  /* [   27],        r/w,        0x0 */
            uint32_t pwm_stop_mode    : 1;  /* [   28],        r/w,        0x1 */
            uint32_t pwm_sts_stop     : 1;  /* [   29],          r,        0x0 */
            uint32_t reg_clk_sel      : 2;  /* [31:30],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_config0;

    /* 0x04 : pwm0_config1 */
    union {
        struct {
            uint32_t pwm_ch0_pen : 1; /* [    0],        r/w,        0x0 */
            uint32_t pwm_ch0_psi : 1; /* [    1],        r/w,        0x0 */
            uint32_t pwm_ch0_nen : 1; /* [    2],        r/w,        0x0 */
            uint32_t pwm_ch0_nsi : 1; /* [    3],        r/w,        0x1 */
            uint32_t pwm_ch1_pen : 1; /* [    4],        r/w,        0x0 */
            uint32_t pwm_ch1_psi : 1; /* [    5],        r/w,        0x0 */
            uint32_t pwm_ch1_nen : 1; /* [    6],        r/w,        0x0 */
            uint32_t pwm_ch1_nsi : 1; /* [    7],        r/w,        0x1 */
            uint32_t pwm_ch2_pen : 1; /* [    8],        r/w,        0x0 */
            uint32_t pwm_ch2_psi : 1; /* [    9],        r/w,        0x0 */
            uint32_t pwm_ch2_nen : 1; /* [   10],        r/w,        0x0 */
            uint32_t pwm_ch2_nsi : 1; /* [   11],        r/w,        0x1 */
            uint32_t pwm_ch3_pen : 1; /* [   12],        r/w,        0x0 */
            uint32_t pwm_ch3_psi : 1; /* [   13],        r/w,        0x0 */
            uint32_t pwm_ch3_nen : 1; /* [   14],        r/w,        0x0 */
            uint32_t pwm_ch3_nsi : 1; /* [   15],        r/w,        0x1 */
            uint32_t pwm_ch0_ppl : 1; /* [   16],        r/w,        0x1 */
            uint32_t pwm_ch0_npl : 1; /* [   17],        r/w,        0x1 */
            uint32_t pwm_ch1_ppl : 1; /* [   18],        r/w,        0x1 */
            uint32_t pwm_ch1_npl : 1; /* [   19],        r/w,        0x1 */
            uint32_t pwm_ch2_ppl : 1; /* [   20],        r/w,        0x1 */
            uint32_t pwm_ch2_npl : 1; /* [   21],        r/w,        0x1 */
            uint32_t pwm_ch3_ppl : 1; /* [   22],        r/w,        0x1 */
            uint32_t pwm_ch3_npl : 1; /* [   23],        r/w,        0x1 */
            uint32_t pwm_ch0_pbs : 1; /* [   24],        r/w,        0x0 */
            uint32_t pwm_ch0_nbs : 1; /* [   25],        r/w,        0x0 */
            uint32_t pwm_ch1_pbs : 1; /* [   26],        r/w,        0x0 */
            uint32_t pwm_ch1_nbs : 1; /* [   27],        r/w,        0x0 */
            uint32_t pwm_ch2_pbs : 1; /* [   28],        r/w,        0x0 */
            uint32_t pwm_ch2_nbs : 1; /* [   29],        r/w,        0x0 */
            uint32_t pwm_ch3_pbs : 1; /* [   30],        r/w,        0x0 */
            uint32_t pwm_ch3_nbs : 1; /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_config1;

    /* 0x08 : pwm0_period */
    union {
        struct {
            uint32_t pwm_period         : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_int_period_cnt : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_period;

    /* 0x0C : pwm0_dead_time */
    union {
        struct {
            uint32_t pwm_ch0_dtg : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t pwm_ch1_dtg : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t pwm_ch2_dtg : 8; /* [23:16],        r/w,        0x0 */
            uint32_t pwm_ch3_dtg : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_dead_time;

    /* 0x10 : pwm0_ch0_thre */
    union {
        struct {
            uint32_t pwm_ch0_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch0_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_ch0_thre;

    /* 0x14 : pwm0_ch1_thre */
    union {
        struct {
            uint32_t pwm_ch1_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch1_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_ch1_thre;

    /* 0x18 : pwm0_ch2_thre */
    union {
        struct {
            uint32_t pwm_ch2_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch2_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_ch2_thre;

    /* 0x1C : pwm0_ch3_thre */
    union {
        struct {
            uint32_t pwm_ch3_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch3_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_ch3_thre;

    /* 0x20 : pwm0_int_sts */
    union {
        struct {
            uint32_t pwm_ch0l_int   : 1;  /* [    0],          r,        0x0 */
            uint32_t pwm_ch0h_int   : 1;  /* [    1],          r,        0x0 */
            uint32_t pwm_ch1l_int   : 1;  /* [    2],          r,        0x0 */
            uint32_t pwm_ch1h_int   : 1;  /* [    3],          r,        0x0 */
            uint32_t pwm_ch2l_int   : 1;  /* [    4],          r,        0x0 */
            uint32_t pwm_ch2h_int   : 1;  /* [    5],          r,        0x0 */
            uint32_t pwm_ch3l_int   : 1;  /* [    6],          r,        0x0 */
            uint32_t pwm_ch3h_int   : 1;  /* [    7],          r,        0x0 */
            uint32_t pwm_prde_int   : 1;  /* [    8],          r,        0x0 */
            uint32_t pwm_brk_int    : 1;  /* [    9],          r,        0x0 */
            uint32_t pwm_rept_int   : 1;  /* [   10],          r,        0x0 */
            uint32_t reserved_11_31 : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_int_sts;

    /* 0x24 : pwm0_int_mask */
    union {
        struct {
            uint32_t cr_pwm_ch0l_mask : 1;  /* [    0],        r/w,        0x1 */
            uint32_t cr_pwm_ch0h_mask : 1;  /* [    1],        r/w,        0x1 */
            uint32_t cr_pwm_ch1l_mask : 1;  /* [    2],        r/w,        0x1 */
            uint32_t cr_pwm_ch1h_mask : 1;  /* [    3],        r/w,        0x1 */
            uint32_t cr_pwm_ch2l_mask : 1;  /* [    4],        r/w,        0x1 */
            uint32_t cr_pwm_ch2h_mask : 1;  /* [    5],        r/w,        0x1 */
            uint32_t cr_pwm_ch3l_mask : 1;  /* [    6],        r/w,        0x1 */
            uint32_t cr_pwm_ch3h_mask : 1;  /* [    7],        r/w,        0x1 */
            uint32_t cr_pwm_prde_mask : 1;  /* [    8],        r/w,        0x1 */
            uint32_t cr_pwm_brk_mask  : 1;  /* [    9],        r/w,        0x1 */
            uint32_t cr_pwm_rept_mask : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_31   : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_int_mask;

    /* 0x28 : pwm0_int_clear */
    union {
        struct {
            uint32_t cr_pwm_ch0l_clr : 1;  /* [    0],        w1c,        0x0 */
            uint32_t cr_pwm_ch0h_clr : 1;  /* [    1],        w1c,        0x0 */
            uint32_t cr_pwm_ch1l_clr : 1;  /* [    2],        w1c,        0x0 */
            uint32_t cr_pwm_ch1h_clr : 1;  /* [    3],        w1c,        0x0 */
            uint32_t cr_pwm_ch2l_clr : 1;  /* [    4],        w1c,        0x0 */
            uint32_t cr_pwm_ch2h_clr : 1;  /* [    5],        w1c,        0x0 */
            uint32_t cr_pwm_ch3l_clr : 1;  /* [    6],        w1c,        0x0 */
            uint32_t cr_pwm_ch3h_clr : 1;  /* [    7],        w1c,        0x0 */
            uint32_t cr_pwm_prde_clr : 1;  /* [    8],        w1c,        0x0 */
            uint32_t cr_pwm_brk_clr  : 1;  /* [    9],        w1c,        0x0 */
            uint32_t cr_pwm_rept_clr : 1;  /* [   10],        w1c,        0x0 */
            uint32_t reserved_11_31  : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_int_clear;

    /* 0x2C : pwm0_int_en */
    union {
        struct {
            uint32_t cr_pwm_ch0l_en : 1;  /* [    0],        r/w,        0x1 */
            uint32_t cr_pwm_ch0h_en : 1;  /* [    1],        r/w,        0x1 */
            uint32_t cr_pwm_ch1l_en : 1;  /* [    2],        r/w,        0x1 */
            uint32_t cr_pwm_ch1h_en : 1;  /* [    3],        r/w,        0x1 */
            uint32_t cr_pwm_ch2l_en : 1;  /* [    4],        r/w,        0x1 */
            uint32_t cr_pwm_ch2h_en : 1;  /* [    5],        r/w,        0x1 */
            uint32_t cr_pwm_ch3l_en : 1;  /* [    6],        r/w,        0x1 */
            uint32_t cr_pwm_ch3h_en : 1;  /* [    7],        r/w,        0x1 */
            uint32_t cr_pwm_prde_en : 1;  /* [    8],        r/w,        0x1 */
            uint32_t cr_pwm_brk_en  : 1;  /* [    9],        r/w,        0x0 */
            uint32_t cr_pwm_rept_en : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_31 : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm0_int_en;
};

typedef volatile struct pwm_reg pwm_reg_t;

/*Following is reg patch*/

/* 0x00 : pwm_config0 */
#define PWM_CONFIG0_OFFSET    (0x00)
#define PWM_CLK_DIV           PWM_CLK_DIV
#define PWM_CLK_DIV_POS       (0U)
#define PWM_CLK_DIV_LEN       (16U)
#define PWM_CLK_DIV_MSK       (((1U << PWM_CLK_DIV_LEN) - 1) << PWM_CLK_DIV_POS)
#define PWM_CLK_DIV_UMSK      (~(((1U << PWM_CLK_DIV_LEN) - 1) << PWM_CLK_DIV_POS))
#define PWM_STOP_ON_REPT      PWM_STOP_ON_REPT
#define PWM_STOP_ON_REPT_POS  (19U)
#define PWM_STOP_ON_REPT_LEN  (1U)
#define PWM_STOP_ON_REPT_MSK  (((1U << PWM_STOP_ON_REPT_LEN) - 1) << PWM_STOP_ON_REPT_POS)
#define PWM_STOP_ON_REPT_UMSK (~(((1U << PWM_STOP_ON_REPT_LEN) - 1) << PWM_STOP_ON_REPT_POS))
#define PWM_ADC_TRG_SRC       PWM_ADC_TRG_SRC
#define PWM_ADC_TRG_SRC_POS   (20U)
#define PWM_ADC_TRG_SRC_LEN   (4U)
#define PWM_ADC_TRG_SRC_MSK   (((1U << PWM_ADC_TRG_SRC_LEN) - 1) << PWM_ADC_TRG_SRC_POS)
#define PWM_ADC_TRG_SRC_UMSK  (~(((1U << PWM_ADC_TRG_SRC_LEN) - 1) << PWM_ADC_TRG_SRC_POS))
#define PWM_SW_BREAK_EN       PWM_SW_BREAK_EN
#define PWM_SW_BREAK_EN_POS   (24U)
#define PWM_SW_BREAK_EN_LEN   (1U)
#define PWM_SW_BREAK_EN_MSK   (((1U << PWM_SW_BREAK_EN_LEN) - 1) << PWM_SW_BREAK_EN_POS)
#define PWM_SW_BREAK_EN_UMSK  (~(((1U << PWM_SW_BREAK_EN_LEN) - 1) << PWM_SW_BREAK_EN_POS))
#define PWM_EXT_BREAK_EN      PWM_EXT_BREAK_EN
#define PWM_EXT_BREAK_EN_POS  (25U)
#define PWM_EXT_BREAK_EN_LEN  (1U)
#define PWM_EXT_BREAK_EN_MSK  (((1U << PWM_EXT_BREAK_EN_LEN) - 1) << PWM_EXT_BREAK_EN_POS)
#define PWM_EXT_BREAK_EN_UMSK (~(((1U << PWM_EXT_BREAK_EN_LEN) - 1) << PWM_EXT_BREAK_EN_POS))
#define PWM_EXT_BREAK_PL      PWM_EXT_BREAK_PL
#define PWM_EXT_BREAK_PL_POS  (26U)
#define PWM_EXT_BREAK_PL_LEN  (1U)
#define PWM_EXT_BREAK_PL_MSK  (((1U << PWM_EXT_BREAK_PL_LEN) - 1) << PWM_EXT_BREAK_PL_POS)
#define PWM_EXT_BREAK_PL_UMSK (~(((1U << PWM_EXT_BREAK_PL_LEN) - 1) << PWM_EXT_BREAK_PL_POS))
#define PWM_STOP_EN           PWM_STOP_EN
#define PWM_STOP_EN_POS       (27U)
#define PWM_STOP_EN_LEN       (1U)
#define PWM_STOP_EN_MSK       (((1U << PWM_STOP_EN_LEN) - 1) << PWM_STOP_EN_POS)
#define PWM_STOP_EN_UMSK      (~(((1U << PWM_STOP_EN_LEN) - 1) << PWM_STOP_EN_POS))
#define PWM_STOP_MODE         PWM_STOP_MODE
#define PWM_STOP_MODE_POS     (28U)
#define PWM_STOP_MODE_LEN     (1U)
#define PWM_STOP_MODE_MSK     (((1U << PWM_STOP_MODE_LEN) - 1) << PWM_STOP_MODE_POS)
#define PWM_STOP_MODE_UMSK    (~(((1U << PWM_STOP_MODE_LEN) - 1) << PWM_STOP_MODE_POS))
#define PWM_STS_STOP          PWM_STS_STOP
#define PWM_STS_STOP_POS      (29U)
#define PWM_STS_STOP_LEN      (1U)
#define PWM_STS_STOP_MSK      (((1U << PWM_STS_STOP_LEN) - 1) << PWM_STS_STOP_POS)
#define PWM_STS_STOP_UMSK     (~(((1U << PWM_STS_STOP_LEN) - 1) << PWM_STS_STOP_POS))
#define PWM_REG_CLK_SEL       PWM_REG_CLK_SEL
#define PWM_REG_CLK_SEL_POS   (30U)
#define PWM_REG_CLK_SEL_LEN   (2U)
#define PWM_REG_CLK_SEL_MSK   (((1U << PWM_REG_CLK_SEL_LEN) - 1) << PWM_REG_CLK_SEL_POS)
#define PWM_REG_CLK_SEL_UMSK  (~(((1U << PWM_REG_CLK_SEL_LEN) - 1) << PWM_REG_CLK_SEL_POS))

/* 0x04 : pwm_config1 */
#define PWM_CONFIG1_OFFSET (0x04)
#define PWM_CH0_PEN        PWM_CH0_PEN
#define PWM_CH0_PEN_POS    (0U)
#define PWM_CH0_PEN_LEN    (1U)
#define PWM_CH0_PEN_MSK    (((1U << PWM_CH0_PEN_LEN) - 1) << PWM_CH0_PEN_POS)
#define PWM_CH0_PEN_UMSK   (~(((1U << PWM_CH0_PEN_LEN) - 1) << PWM_CH0_PEN_POS))
#define PWM_CH0_PSI        PWM_CH0_PSI
#define PWM_CH0_PSI_POS    (1U)
#define PWM_CH0_PSI_LEN    (1U)
#define PWM_CH0_PSI_MSK    (((1U << PWM_CH0_PSI_LEN) - 1) << PWM_CH0_PSI_POS)
#define PWM_CH0_PSI_UMSK   (~(((1U << PWM_CH0_PSI_LEN) - 1) << PWM_CH0_PSI_POS))
#define PWM_CH0_NEN        PWM_CH0_NEN
#define PWM_CH0_NEN_POS    (2U)
#define PWM_CH0_NEN_LEN    (1U)
#define PWM_CH0_NEN_MSK    (((1U << PWM_CH0_NEN_LEN) - 1) << PWM_CH0_NEN_POS)
#define PWM_CH0_NEN_UMSK   (~(((1U << PWM_CH0_NEN_LEN) - 1) << PWM_CH0_NEN_POS))
#define PWM_CH0_NSI        PWM_CH0_NSI
#define PWM_CH0_NSI_POS    (3U)
#define PWM_CH0_NSI_LEN    (1U)
#define PWM_CH0_NSI_MSK    (((1U << PWM_CH0_NSI_LEN) - 1) << PWM_CH0_NSI_POS)
#define PWM_CH0_NSI_UMSK   (~(((1U << PWM_CH0_NSI_LEN) - 1) << PWM_CH0_NSI_POS))
#define PWM_CH1_PEN        PWM_CH1_PEN
#define PWM_CH1_PEN_POS    (4U)
#define PWM_CH1_PEN_LEN    (1U)
#define PWM_CH1_PEN_MSK    (((1U << PWM_CH1_PEN_LEN) - 1) << PWM_CH1_PEN_POS)
#define PWM_CH1_PEN_UMSK   (~(((1U << PWM_CH1_PEN_LEN) - 1) << PWM_CH1_PEN_POS))
#define PWM_CH1_PSI        PWM_CH1_PSI
#define PWM_CH1_PSI_POS    (5U)
#define PWM_CH1_PSI_LEN    (1U)
#define PWM_CH1_PSI_MSK    (((1U << PWM_CH1_PSI_LEN) - 1) << PWM_CH1_PSI_POS)
#define PWM_CH1_PSI_UMSK   (~(((1U << PWM_CH1_PSI_LEN) - 1) << PWM_CH1_PSI_POS))
#define PWM_CH1_NEN        PWM_CH1_NEN
#define PWM_CH1_NEN_POS    (6U)
#define PWM_CH1_NEN_LEN    (1U)
#define PWM_CH1_NEN_MSK    (((1U << PWM_CH1_NEN_LEN) - 1) << PWM_CH1_NEN_POS)
#define PWM_CH1_NEN_UMSK   (~(((1U << PWM_CH1_NEN_LEN) - 1) << PWM_CH1_NEN_POS))
#define PWM_CH1_NSI        PWM_CH1_NSI
#define PWM_CH1_NSI_POS    (7U)
#define PWM_CH1_NSI_LEN    (1U)
#define PWM_CH1_NSI_MSK    (((1U << PWM_CH1_NSI_LEN) - 1) << PWM_CH1_NSI_POS)
#define PWM_CH1_NSI_UMSK   (~(((1U << PWM_CH1_NSI_LEN) - 1) << PWM_CH1_NSI_POS))
#define PWM_CH2_PEN        PWM_CH2_PEN
#define PWM_CH2_PEN_POS    (8U)
#define PWM_CH2_PEN_LEN    (1U)
#define PWM_CH2_PEN_MSK    (((1U << PWM_CH2_PEN_LEN) - 1) << PWM_CH2_PEN_POS)
#define PWM_CH2_PEN_UMSK   (~(((1U << PWM_CH2_PEN_LEN) - 1) << PWM_CH2_PEN_POS))
#define PWM_CH2_PSI        PWM_CH2_PSI
#define PWM_CH2_PSI_POS    (9U)
#define PWM_CH2_PSI_LEN    (1U)
#define PWM_CH2_PSI_MSK    (((1U << PWM_CH2_PSI_LEN) - 1) << PWM_CH2_PSI_POS)
#define PWM_CH2_PSI_UMSK   (~(((1U << PWM_CH2_PSI_LEN) - 1) << PWM_CH2_PSI_POS))
#define PWM_CH2_NEN        PWM_CH2_NEN
#define PWM_CH2_NEN_POS    (10U)
#define PWM_CH2_NEN_LEN    (1U)
#define PWM_CH2_NEN_MSK    (((1U << PWM_CH2_NEN_LEN) - 1) << PWM_CH2_NEN_POS)
#define PWM_CH2_NEN_UMSK   (~(((1U << PWM_CH2_NEN_LEN) - 1) << PWM_CH2_NEN_POS))
#define PWM_CH2_NSI        PWM_CH2_NSI
#define PWM_CH2_NSI_POS    (11U)
#define PWM_CH2_NSI_LEN    (1U)
#define PWM_CH2_NSI_MSK    (((1U << PWM_CH2_NSI_LEN) - 1) << PWM_CH2_NSI_POS)
#define PWM_CH2_NSI_UMSK   (~(((1U << PWM_CH2_NSI_LEN) - 1) << PWM_CH2_NSI_POS))
#define PWM_CH3_PEN        PWM_CH3_PEN
#define PWM_CH3_PEN_POS    (12U)
#define PWM_CH3_PEN_LEN    (1U)
#define PWM_CH3_PEN_MSK    (((1U << PWM_CH3_PEN_LEN) - 1) << PWM_CH3_PEN_POS)
#define PWM_CH3_PEN_UMSK   (~(((1U << PWM_CH3_PEN_LEN) - 1) << PWM_CH3_PEN_POS))
#define PWM_CH3_PSI        PWM_CH3_PSI
#define PWM_CH3_PSI_POS    (13U)
#define PWM_CH3_PSI_LEN    (1U)
#define PWM_CH3_PSI_MSK    (((1U << PWM_CH3_PSI_LEN) - 1) << PWM_CH3_PSI_POS)
#define PWM_CH3_PSI_UMSK   (~(((1U << PWM_CH3_PSI_LEN) - 1) << PWM_CH3_PSI_POS))
#define PWM_CH3_NEN        PWM_CH3_NEN
#define PWM_CH3_NEN_POS    (14U)
#define PWM_CH3_NEN_LEN    (1U)
#define PWM_CH3_NEN_MSK    (((1U << PWM_CH3_NEN_LEN) - 1) << PWM_CH3_NEN_POS)
#define PWM_CH3_NEN_UMSK   (~(((1U << PWM_CH3_NEN_LEN) - 1) << PWM_CH3_NEN_POS))
#define PWM_CH3_NSI        PWM_CH3_NSI
#define PWM_CH3_NSI_POS    (15U)
#define PWM_CH3_NSI_LEN    (1U)
#define PWM_CH3_NSI_MSK    (((1U << PWM_CH3_NSI_LEN) - 1) << PWM_CH3_NSI_POS)
#define PWM_CH3_NSI_UMSK   (~(((1U << PWM_CH3_NSI_LEN) - 1) << PWM_CH3_NSI_POS))
#define PWM_CH0_PPL        PWM_CH0_PPL
#define PWM_CH0_PPL_POS    (16U)
#define PWM_CH0_PPL_LEN    (1U)
#define PWM_CH0_PPL_MSK    (((1U << PWM_CH0_PPL_LEN) - 1) << PWM_CH0_PPL_POS)
#define PWM_CH0_PPL_UMSK   (~(((1U << PWM_CH0_PPL_LEN) - 1) << PWM_CH0_PPL_POS))
#define PWM_CH0_NPL        PWM_CH0_NPL
#define PWM_CH0_NPL_POS    (17U)
#define PWM_CH0_NPL_LEN    (1U)
#define PWM_CH0_NPL_MSK    (((1U << PWM_CH0_NPL_LEN) - 1) << PWM_CH0_NPL_POS)
#define PWM_CH0_NPL_UMSK   (~(((1U << PWM_CH0_NPL_LEN) - 1) << PWM_CH0_NPL_POS))
#define PWM_CH1_PPL        PWM_CH1_PPL
#define PWM_CH1_PPL_POS    (18U)
#define PWM_CH1_PPL_LEN    (1U)
#define PWM_CH1_PPL_MSK    (((1U << PWM_CH1_PPL_LEN) - 1) << PWM_CH1_PPL_POS)
#define PWM_CH1_PPL_UMSK   (~(((1U << PWM_CH1_PPL_LEN) - 1) << PWM_CH1_PPL_POS))
#define PWM_CH1_NPL        PWM_CH1_NPL
#define PWM_CH1_NPL_POS    (19U)
#define PWM_CH1_NPL_LEN    (1U)
#define PWM_CH1_NPL_MSK    (((1U << PWM_CH1_NPL_LEN) - 1) << PWM_CH1_NPL_POS)
#define PWM_CH1_NPL_UMSK   (~(((1U << PWM_CH1_NPL_LEN) - 1) << PWM_CH1_NPL_POS))
#define PWM_CH2_PPL        PWM_CH2_PPL
#define PWM_CH2_PPL_POS    (20U)
#define PWM_CH2_PPL_LEN    (1U)
#define PWM_CH2_PPL_MSK    (((1U << PWM_CH2_PPL_LEN) - 1) << PWM_CH2_PPL_POS)
#define PWM_CH2_PPL_UMSK   (~(((1U << PWM_CH2_PPL_LEN) - 1) << PWM_CH2_PPL_POS))
#define PWM_CH2_NPL        PWM_CH2_NPL
#define PWM_CH2_NPL_POS    (21U)
#define PWM_CH2_NPL_LEN    (1U)
#define PWM_CH2_NPL_MSK    (((1U << PWM_CH2_NPL_LEN) - 1) << PWM_CH2_NPL_POS)
#define PWM_CH2_NPL_UMSK   (~(((1U << PWM_CH2_NPL_LEN) - 1) << PWM_CH2_NPL_POS))
#define PWM_CH3_PPL        PWM_CH3_PPL
#define PWM_CH3_PPL_POS    (22U)
#define PWM_CH3_PPL_LEN    (1U)
#define PWM_CH3_PPL_MSK    (((1U << PWM_CH3_PPL_LEN) - 1) << PWM_CH3_PPL_POS)
#define PWM_CH3_PPL_UMSK   (~(((1U << PWM_CH3_PPL_LEN) - 1) << PWM_CH3_PPL_POS))
#define PWM_CH3_NPL        PWM_CH3_NPL
#define PWM_CH3_NPL_POS    (23U)
#define PWM_CH3_NPL_LEN    (1U)
#define PWM_CH3_NPL_MSK    (((1U << PWM_CH3_NPL_LEN) - 1) << PWM_CH3_NPL_POS)
#define PWM_CH3_NPL_UMSK   (~(((1U << PWM_CH3_NPL_LEN) - 1) << PWM_CH3_NPL_POS))
#define PWM_CH0_PBS        PWM_CH0_PBS
#define PWM_CH0_PBS_POS    (24U)
#define PWM_CH0_PBS_LEN    (1U)
#define PWM_CH0_PBS_MSK    (((1U << PWM_CH0_PBS_LEN) - 1) << PWM_CH0_PBS_POS)
#define PWM_CH0_PBS_UMSK   (~(((1U << PWM_CH0_PBS_LEN) - 1) << PWM_CH0_PBS_POS))
#define PWM_CH0_NBS        PWM_CH0_NBS
#define PWM_CH0_NBS_POS    (25U)
#define PWM_CH0_NBS_LEN    (1U)
#define PWM_CH0_NBS_MSK    (((1U << PWM_CH0_NBS_LEN) - 1) << PWM_CH0_NBS_POS)
#define PWM_CH0_NBS_UMSK   (~(((1U << PWM_CH0_NBS_LEN) - 1) << PWM_CH0_NBS_POS))
#define PWM_CH1_PBS        PWM_CH1_PBS
#define PWM_CH1_PBS_POS    (26U)
#define PWM_CH1_PBS_LEN    (1U)
#define PWM_CH1_PBS_MSK    (((1U << PWM_CH1_PBS_LEN) - 1) << PWM_CH1_PBS_POS)
#define PWM_CH1_PBS_UMSK   (~(((1U << PWM_CH1_PBS_LEN) - 1) << PWM_CH1_PBS_POS))
#define PWM_CH1_NBS        PWM_CH1_NBS
#define PWM_CH1_NBS_POS    (27U)
#define PWM_CH1_NBS_LEN    (1U)
#define PWM_CH1_NBS_MSK    (((1U << PWM_CH1_NBS_LEN) - 1) << PWM_CH1_NBS_POS)
#define PWM_CH1_NBS_UMSK   (~(((1U << PWM_CH1_NBS_LEN) - 1) << PWM_CH1_NBS_POS))
#define PWM_CH2_PBS        PWM_CH2_PBS
#define PWM_CH2_PBS_POS    (28U)
#define PWM_CH2_PBS_LEN    (1U)
#define PWM_CH2_PBS_MSK    (((1U << PWM_CH2_PBS_LEN) - 1) << PWM_CH2_PBS_POS)
#define PWM_CH2_PBS_UMSK   (~(((1U << PWM_CH2_PBS_LEN) - 1) << PWM_CH2_PBS_POS))
#define PWM_CH2_NBS        PWM_CH2_NBS
#define PWM_CH2_NBS_POS    (29U)
#define PWM_CH2_NBS_LEN    (1U)
#define PWM_CH2_NBS_MSK    (((1U << PWM_CH2_NBS_LEN) - 1) << PWM_CH2_NBS_POS)
#define PWM_CH2_NBS_UMSK   (~(((1U << PWM_CH2_NBS_LEN) - 1) << PWM_CH2_NBS_POS))
#define PWM_CH3_PBS        PWM_CH3_PBS
#define PWM_CH3_PBS_POS    (30U)
#define PWM_CH3_PBS_LEN    (1U)
#define PWM_CH3_PBS_MSK    (((1U << PWM_CH3_PBS_LEN) - 1) << PWM_CH3_PBS_POS)
#define PWM_CH3_PBS_UMSK   (~(((1U << PWM_CH3_PBS_LEN) - 1) << PWM_CH3_PBS_POS))
#define PWM_CH3_NBS        PWM_CH3_NBS
#define PWM_CH3_NBS_POS    (31U)
#define PWM_CH3_NBS_LEN    (1U)
#define PWM_CH3_NBS_MSK    (((1U << PWM_CH3_NBS_LEN) - 1) << PWM_CH3_NBS_POS)
#define PWM_CH3_NBS_UMSK   (~(((1U << PWM_CH3_NBS_LEN) - 1) << PWM_CH3_NBS_POS))

/* 0x08 : pwm_period */
#define PWM_PERIOD_OFFSET       (0x08)
#define PWM_PERIOD              PWM_PERIOD
#define PWM_PERIOD_POS          (0U)
#define PWM_PERIOD_LEN          (16U)
#define PWM_PERIOD_MSK          (((1U << PWM_PERIOD_LEN) - 1) << PWM_PERIOD_POS)
#define PWM_PERIOD_UMSK         (~(((1U << PWM_PERIOD_LEN) - 1) << PWM_PERIOD_POS))
#define PWM_INT_PERIOD_CNT      PWM_INT_PERIOD_CNT
#define PWM_INT_PERIOD_CNT_POS  (16U)
#define PWM_INT_PERIOD_CNT_LEN  (16U)
#define PWM_INT_PERIOD_CNT_MSK  (((1U << PWM_INT_PERIOD_CNT_LEN) - 1) << PWM_INT_PERIOD_CNT_POS)
#define PWM_INT_PERIOD_CNT_UMSK (~(((1U << PWM_INT_PERIOD_CNT_LEN) - 1) << PWM_INT_PERIOD_CNT_POS))

/* 0x0C : pwm_dead_time */
#define PWM_DEAD_TIME_OFFSET (0x0C)
#define PWM_CH0_DTG          PWM_CH0_DTG
#define PWM_CH0_DTG_POS      (0U)
#define PWM_CH0_DTG_LEN      (8U)
#define PWM_CH0_DTG_MSK      (((1U << PWM_CH0_DTG_LEN) - 1) << PWM_CH0_DTG_POS)
#define PWM_CH0_DTG_UMSK     (~(((1U << PWM_CH0_DTG_LEN) - 1) << PWM_CH0_DTG_POS))
#define PWM_CH1_DTG          PWM_CH1_DTG
#define PWM_CH1_DTG_POS      (8U)
#define PWM_CH1_DTG_LEN      (8U)
#define PWM_CH1_DTG_MSK      (((1U << PWM_CH1_DTG_LEN) - 1) << PWM_CH1_DTG_POS)
#define PWM_CH1_DTG_UMSK     (~(((1U << PWM_CH1_DTG_LEN) - 1) << PWM_CH1_DTG_POS))
#define PWM_CH2_DTG          PWM_CH2_DTG
#define PWM_CH2_DTG_POS      (16U)
#define PWM_CH2_DTG_LEN      (8U)
#define PWM_CH2_DTG_MSK      (((1U << PWM_CH2_DTG_LEN) - 1) << PWM_CH2_DTG_POS)
#define PWM_CH2_DTG_UMSK     (~(((1U << PWM_CH2_DTG_LEN) - 1) << PWM_CH2_DTG_POS))
#define PWM_CH3_DTG          PWM_CH3_DTG
#define PWM_CH3_DTG_POS      (24U)
#define PWM_CH3_DTG_LEN      (8U)
#define PWM_CH3_DTG_MSK      (((1U << PWM_CH3_DTG_LEN) - 1) << PWM_CH3_DTG_POS)
#define PWM_CH3_DTG_UMSK     (~(((1U << PWM_CH3_DTG_LEN) - 1) << PWM_CH3_DTG_POS))

/* 0x10 : pwm_ch0_thre */
#define PWM_CH0_THRE_OFFSET (0x10)
#define PWM_CH0_THREL       PWM_CH0_THREL
#define PWM_CH0_THREL_POS   (0U)
#define PWM_CH0_THREL_LEN   (16U)
#define PWM_CH0_THREL_MSK   (((1U << PWM_CH0_THREL_LEN) - 1) << PWM_CH0_THREL_POS)
#define PWM_CH0_THREL_UMSK  (~(((1U << PWM_CH0_THREL_LEN) - 1) << PWM_CH0_THREL_POS))
#define PWM_CH0_THREH       PWM_CH0_THREH
#define PWM_CH0_THREH_POS   (16U)
#define PWM_CH0_THREH_LEN   (16U)
#define PWM_CH0_THREH_MSK   (((1U << PWM_CH0_THREH_LEN) - 1) << PWM_CH0_THREH_POS)
#define PWM_CH0_THREH_UMSK  (~(((1U << PWM_CH0_THREH_LEN) - 1) << PWM_CH0_THREH_POS))

/* 0x14 : pwm_ch1_thre */
#define PWM_CH1_THRE_OFFSET (0x14)
#define PWM_CH1_THREL       PWM_CH1_THREL
#define PWM_CH1_THREL_POS   (0U)
#define PWM_CH1_THREL_LEN   (16U)
#define PWM_CH1_THREL_MSK   (((1U << PWM_CH1_THREL_LEN) - 1) << PWM_CH1_THREL_POS)
#define PWM_CH1_THREL_UMSK  (~(((1U << PWM_CH1_THREL_LEN) - 1) << PWM_CH1_THREL_POS))
#define PWM_CH1_THREH       PWM_CH1_THREH
#define PWM_CH1_THREH_POS   (16U)
#define PWM_CH1_THREH_LEN   (16U)
#define PWM_CH1_THREH_MSK   (((1U << PWM_CH1_THREH_LEN) - 1) << PWM_CH1_THREH_POS)
#define PWM_CH1_THREH_UMSK  (~(((1U << PWM_CH1_THREH_LEN) - 1) << PWM_CH1_THREH_POS))

/* 0x18 : pwm_ch2_thre */
#define PWM_CH2_THRE_OFFSET (0x18)
#define PWM_CH2_THREL       PWM_CH2_THREL
#define PWM_CH2_THREL_POS   (0U)
#define PWM_CH2_THREL_LEN   (16U)
#define PWM_CH2_THREL_MSK   (((1U << PWM_CH2_THREL_LEN) - 1) << PWM_CH2_THREL_POS)
#define PWM_CH2_THREL_UMSK  (~(((1U << PWM_CH2_THREL_LEN) - 1) << PWM_CH2_THREL_POS))
#define PWM_CH2_THREH       PWM_CH2_THREH
#define PWM_CH2_THREH_POS   (16U)
#define PWM_CH2_THREH_LEN   (16U)
#define PWM_CH2_THREH_MSK   (((1U << PWM_CH2_THREH_LEN) - 1) << PWM_CH2_THREH_POS)
#define PWM_CH2_THREH_UMSK  (~(((1U << PWM_CH2_THREH_LEN) - 1) << PWM_CH2_THREH_POS))

/* 0x1C : pwm_ch3_thre */
#define PWM_CH3_THRE_OFFSET (0x1C)
#define PWM_CH3_THREL       PWM_CH3_THREL
#define PWM_CH3_THREL_POS   (0U)
#define PWM_CH3_THREL_LEN   (16U)
#define PWM_CH3_THREL_MSK   (((1U << PWM_CH3_THREL_LEN) - 1) << PWM_CH3_THREL_POS)
#define PWM_CH3_THREL_UMSK  (~(((1U << PWM_CH3_THREL_LEN) - 1) << PWM_CH3_THREL_POS))
#define PWM_CH3_THREH       PWM_CH3_THREH
#define PWM_CH3_THREH_POS   (16U)
#define PWM_CH3_THREH_LEN   (16U)
#define PWM_CH3_THREH_MSK   (((1U << PWM_CH3_THREH_LEN) - 1) << PWM_CH3_THREH_POS)
#define PWM_CH3_THREH_UMSK  (~(((1U << PWM_CH3_THREH_LEN) - 1) << PWM_CH3_THREH_POS))

/* 0x20 : pwm_int_sts */
#define PWM_INT_STS_OFFSET (0x20)
#define PWM_CH0L_INT       PWM_CH0L_INT
#define PWM_CH0L_INT_POS   (0U)
#define PWM_CH0L_INT_LEN   (1U)
#define PWM_CH0L_INT_MSK   (((1U << PWM_CH0L_INT_LEN) - 1) << PWM_CH0L_INT_POS)
#define PWM_CH0L_INT_UMSK  (~(((1U << PWM_CH0L_INT_LEN) - 1) << PWM_CH0L_INT_POS))
#define PWM_CH0H_INT       PWM_CH0H_INT
#define PWM_CH0H_INT_POS   (1U)
#define PWM_CH0H_INT_LEN   (1U)
#define PWM_CH0H_INT_MSK   (((1U << PWM_CH0H_INT_LEN) - 1) << PWM_CH0H_INT_POS)
#define PWM_CH0H_INT_UMSK  (~(((1U << PWM_CH0H_INT_LEN) - 1) << PWM_CH0H_INT_POS))
#define PWM_CH1L_INT       PWM_CH1L_INT
#define PWM_CH1L_INT_POS   (2U)
#define PWM_CH1L_INT_LEN   (1U)
#define PWM_CH1L_INT_MSK   (((1U << PWM_CH1L_INT_LEN) - 1) << PWM_CH1L_INT_POS)
#define PWM_CH1L_INT_UMSK  (~(((1U << PWM_CH1L_INT_LEN) - 1) << PWM_CH1L_INT_POS))
#define PWM_CH1H_INT       PWM_CH1H_INT
#define PWM_CH1H_INT_POS   (3U)
#define PWM_CH1H_INT_LEN   (1U)
#define PWM_CH1H_INT_MSK   (((1U << PWM_CH1H_INT_LEN) - 1) << PWM_CH1H_INT_POS)
#define PWM_CH1H_INT_UMSK  (~(((1U << PWM_CH1H_INT_LEN) - 1) << PWM_CH1H_INT_POS))
#define PWM_CH2L_INT       PWM_CH2L_INT
#define PWM_CH2L_INT_POS   (4U)
#define PWM_CH2L_INT_LEN   (1U)
#define PWM_CH2L_INT_MSK   (((1U << PWM_CH2L_INT_LEN) - 1) << PWM_CH2L_INT_POS)
#define PWM_CH2L_INT_UMSK  (~(((1U << PWM_CH2L_INT_LEN) - 1) << PWM_CH2L_INT_POS))
#define PWM_CH2H_INT       PWM_CH2H_INT
#define PWM_CH2H_INT_POS   (5U)
#define PWM_CH2H_INT_LEN   (1U)
#define PWM_CH2H_INT_MSK   (((1U << PWM_CH2H_INT_LEN) - 1) << PWM_CH2H_INT_POS)
#define PWM_CH2H_INT_UMSK  (~(((1U << PWM_CH2H_INT_LEN) - 1) << PWM_CH2H_INT_POS))
#define PWM_CH3L_INT       PWM_CH3L_INT
#define PWM_CH3L_INT_POS   (6U)
#define PWM_CH3L_INT_LEN   (1U)
#define PWM_CH3L_INT_MSK   (((1U << PWM_CH3L_INT_LEN) - 1) << PWM_CH3L_INT_POS)
#define PWM_CH3L_INT_UMSK  (~(((1U << PWM_CH3L_INT_LEN) - 1) << PWM_CH3L_INT_POS))
#define PWM_CH3H_INT       PWM_CH3H_INT
#define PWM_CH3H_INT_POS   (7U)
#define PWM_CH3H_INT_LEN   (1U)
#define PWM_CH3H_INT_MSK   (((1U << PWM_CH3H_INT_LEN) - 1) << PWM_CH3H_INT_POS)
#define PWM_CH3H_INT_UMSK  (~(((1U << PWM_CH3H_INT_LEN) - 1) << PWM_CH3H_INT_POS))
#define PWM_PRDE_INT       PWM_PRDE_INT
#define PWM_PRDE_INT_POS   (8U)
#define PWM_PRDE_INT_LEN   (1U)
#define PWM_PRDE_INT_MSK   (((1U << PWM_PRDE_INT_LEN) - 1) << PWM_PRDE_INT_POS)
#define PWM_PRDE_INT_UMSK  (~(((1U << PWM_PRDE_INT_LEN) - 1) << PWM_PRDE_INT_POS))
#define PWM_BRK_INT        PWM_BRK_INT
#define PWM_BRK_INT_POS    (9U)
#define PWM_BRK_INT_LEN    (1U)
#define PWM_BRK_INT_MSK    (((1U << PWM_BRK_INT_LEN) - 1) << PWM_BRK_INT_POS)
#define PWM_BRK_INT_UMSK   (~(((1U << PWM_BRK_INT_LEN) - 1) << PWM_BRK_INT_POS))
#define PWM_REPT_INT       PWM_REPT_INT
#define PWM_REPT_INT_POS   (10U)
#define PWM_REPT_INT_LEN   (1U)
#define PWM_REPT_INT_MSK   (((1U << PWM_REPT_INT_LEN) - 1) << PWM_REPT_INT_POS)
#define PWM_REPT_INT_UMSK  (~(((1U << PWM_REPT_INT_LEN) - 1) << PWM_REPT_INT_POS))

/* 0x24 : pwm_int_mask */
#define PWM_INT_MASK_OFFSET       (0x24)
#define PWM_CR_PWM_CH0L_MASK      PWM_CR_PWM_CH0L_MASK
#define PWM_CR_PWM_CH0L_MASK_POS  (0U)
#define PWM_CR_PWM_CH0L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH0L_MASK_MSK  (((1U << PWM_CR_PWM_CH0L_MASK_LEN) - 1) << PWM_CR_PWM_CH0L_MASK_POS)
#define PWM_CR_PWM_CH0L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH0L_MASK_LEN) - 1) << PWM_CR_PWM_CH0L_MASK_POS))
#define PWM_CR_PWM_CH0H_MASK      PWM_CR_PWM_CH0H_MASK
#define PWM_CR_PWM_CH0H_MASK_POS  (1U)
#define PWM_CR_PWM_CH0H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH0H_MASK_MSK  (((1U << PWM_CR_PWM_CH0H_MASK_LEN) - 1) << PWM_CR_PWM_CH0H_MASK_POS)
#define PWM_CR_PWM_CH0H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH0H_MASK_LEN) - 1) << PWM_CR_PWM_CH0H_MASK_POS))
#define PWM_CR_PWM_CH1L_MASK      PWM_CR_PWM_CH1L_MASK
#define PWM_CR_PWM_CH1L_MASK_POS  (2U)
#define PWM_CR_PWM_CH1L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH1L_MASK_MSK  (((1U << PWM_CR_PWM_CH1L_MASK_LEN) - 1) << PWM_CR_PWM_CH1L_MASK_POS)
#define PWM_CR_PWM_CH1L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH1L_MASK_LEN) - 1) << PWM_CR_PWM_CH1L_MASK_POS))
#define PWM_CR_PWM_CH1H_MASK      PWM_CR_PWM_CH1H_MASK
#define PWM_CR_PWM_CH1H_MASK_POS  (3U)
#define PWM_CR_PWM_CH1H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH1H_MASK_MSK  (((1U << PWM_CR_PWM_CH1H_MASK_LEN) - 1) << PWM_CR_PWM_CH1H_MASK_POS)
#define PWM_CR_PWM_CH1H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH1H_MASK_LEN) - 1) << PWM_CR_PWM_CH1H_MASK_POS))
#define PWM_CR_PWM_CH2L_MASK      PWM_CR_PWM_CH2L_MASK
#define PWM_CR_PWM_CH2L_MASK_POS  (4U)
#define PWM_CR_PWM_CH2L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH2L_MASK_MSK  (((1U << PWM_CR_PWM_CH2L_MASK_LEN) - 1) << PWM_CR_PWM_CH2L_MASK_POS)
#define PWM_CR_PWM_CH2L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH2L_MASK_LEN) - 1) << PWM_CR_PWM_CH2L_MASK_POS))
#define PWM_CR_PWM_CH2H_MASK      PWM_CR_PWM_CH2H_MASK
#define PWM_CR_PWM_CH2H_MASK_POS  (5U)
#define PWM_CR_PWM_CH2H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH2H_MASK_MSK  (((1U << PWM_CR_PWM_CH2H_MASK_LEN) - 1) << PWM_CR_PWM_CH2H_MASK_POS)
#define PWM_CR_PWM_CH2H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH2H_MASK_LEN) - 1) << PWM_CR_PWM_CH2H_MASK_POS))
#define PWM_CR_PWM_CH3L_MASK      PWM_CR_PWM_CH3L_MASK
#define PWM_CR_PWM_CH3L_MASK_POS  (6U)
#define PWM_CR_PWM_CH3L_MASK_LEN  (1U)
#define PWM_CR_PWM_CH3L_MASK_MSK  (((1U << PWM_CR_PWM_CH3L_MASK_LEN) - 1) << PWM_CR_PWM_CH3L_MASK_POS)
#define PWM_CR_PWM_CH3L_MASK_UMSK (~(((1U << PWM_CR_PWM_CH3L_MASK_LEN) - 1) << PWM_CR_PWM_CH3L_MASK_POS))
#define PWM_CR_PWM_CH3H_MASK      PWM_CR_PWM_CH3H_MASK
#define PWM_CR_PWM_CH3H_MASK_POS  (7U)
#define PWM_CR_PWM_CH3H_MASK_LEN  (1U)
#define PWM_CR_PWM_CH3H_MASK_MSK  (((1U << PWM_CR_PWM_CH3H_MASK_LEN) - 1) << PWM_CR_PWM_CH3H_MASK_POS)
#define PWM_CR_PWM_CH3H_MASK_UMSK (~(((1U << PWM_CR_PWM_CH3H_MASK_LEN) - 1) << PWM_CR_PWM_CH3H_MASK_POS))
#define PWM_CR_PWM_PRDE_MASK      PWM_CR_PWM_PRDE_MASK
#define PWM_CR_PWM_PRDE_MASK_POS  (8U)
#define PWM_CR_PWM_PRDE_MASK_LEN  (1U)
#define PWM_CR_PWM_PRDE_MASK_MSK  (((1U << PWM_CR_PWM_PRDE_MASK_LEN) - 1) << PWM_CR_PWM_PRDE_MASK_POS)
#define PWM_CR_PWM_PRDE_MASK_UMSK (~(((1U << PWM_CR_PWM_PRDE_MASK_LEN) - 1) << PWM_CR_PWM_PRDE_MASK_POS))
#define PWM_CR_PWM_BRK_MASK       PWM_CR_PWM_BRK_MASK
#define PWM_CR_PWM_BRK_MASK_POS   (9U)
#define PWM_CR_PWM_BRK_MASK_LEN   (1U)
#define PWM_CR_PWM_BRK_MASK_MSK   (((1U << PWM_CR_PWM_BRK_MASK_LEN) - 1) << PWM_CR_PWM_BRK_MASK_POS)
#define PWM_CR_PWM_BRK_MASK_UMSK  (~(((1U << PWM_CR_PWM_BRK_MASK_LEN) - 1) << PWM_CR_PWM_BRK_MASK_POS))
#define PWM_CR_PWM_REPT_MASK      PWM_CR_PWM_REPT_MASK
#define PWM_CR_PWM_REPT_MASK_POS  (10U)
#define PWM_CR_PWM_REPT_MASK_LEN  (1U)
#define PWM_CR_PWM_REPT_MASK_MSK  (((1U << PWM_CR_PWM_REPT_MASK_LEN) - 1) << PWM_CR_PWM_REPT_MASK_POS)
#define PWM_CR_PWM_REPT_MASK_UMSK (~(((1U << PWM_CR_PWM_REPT_MASK_LEN) - 1) << PWM_CR_PWM_REPT_MASK_POS))

/* 0x28 : pwm_int_clear */
#define PWM_INT_CLEAR_OFFSET     (0x28)
#define PWM_CR_PWM_CH0L_CLR      PWM_CR_PWM_CH0L_CLR
#define PWM_CR_PWM_CH0L_CLR_POS  (0U)
#define PWM_CR_PWM_CH0L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH0L_CLR_MSK  (((1U << PWM_CR_PWM_CH0L_CLR_LEN) - 1) << PWM_CR_PWM_CH0L_CLR_POS)
#define PWM_CR_PWM_CH0L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH0L_CLR_LEN) - 1) << PWM_CR_PWM_CH0L_CLR_POS))
#define PWM_CR_PWM_CH0H_CLR      PWM_CR_PWM_CH0H_CLR
#define PWM_CR_PWM_CH0H_CLR_POS  (1U)
#define PWM_CR_PWM_CH0H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH0H_CLR_MSK  (((1U << PWM_CR_PWM_CH0H_CLR_LEN) - 1) << PWM_CR_PWM_CH0H_CLR_POS)
#define PWM_CR_PWM_CH0H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH0H_CLR_LEN) - 1) << PWM_CR_PWM_CH0H_CLR_POS))
#define PWM_CR_PWM_CH1L_CLR      PWM_CR_PWM_CH1L_CLR
#define PWM_CR_PWM_CH1L_CLR_POS  (2U)
#define PWM_CR_PWM_CH1L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH1L_CLR_MSK  (((1U << PWM_CR_PWM_CH1L_CLR_LEN) - 1) << PWM_CR_PWM_CH1L_CLR_POS)
#define PWM_CR_PWM_CH1L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH1L_CLR_LEN) - 1) << PWM_CR_PWM_CH1L_CLR_POS))
#define PWM_CR_PWM_CH1H_CLR      PWM_CR_PWM_CH1H_CLR
#define PWM_CR_PWM_CH1H_CLR_POS  (3U)
#define PWM_CR_PWM_CH1H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH1H_CLR_MSK  (((1U << PWM_CR_PWM_CH1H_CLR_LEN) - 1) << PWM_CR_PWM_CH1H_CLR_POS)
#define PWM_CR_PWM_CH1H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH1H_CLR_LEN) - 1) << PWM_CR_PWM_CH1H_CLR_POS))
#define PWM_CR_PWM_CH2L_CLR      PWM_CR_PWM_CH2L_CLR
#define PWM_CR_PWM_CH2L_CLR_POS  (4U)
#define PWM_CR_PWM_CH2L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH2L_CLR_MSK  (((1U << PWM_CR_PWM_CH2L_CLR_LEN) - 1) << PWM_CR_PWM_CH2L_CLR_POS)
#define PWM_CR_PWM_CH2L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH2L_CLR_LEN) - 1) << PWM_CR_PWM_CH2L_CLR_POS))
#define PWM_CR_PWM_CH2H_CLR      PWM_CR_PWM_CH2H_CLR
#define PWM_CR_PWM_CH2H_CLR_POS  (5U)
#define PWM_CR_PWM_CH2H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH2H_CLR_MSK  (((1U << PWM_CR_PWM_CH2H_CLR_LEN) - 1) << PWM_CR_PWM_CH2H_CLR_POS)
#define PWM_CR_PWM_CH2H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH2H_CLR_LEN) - 1) << PWM_CR_PWM_CH2H_CLR_POS))
#define PWM_CR_PWM_CH3L_CLR      PWM_CR_PWM_CH3L_CLR
#define PWM_CR_PWM_CH3L_CLR_POS  (6U)
#define PWM_CR_PWM_CH3L_CLR_LEN  (1U)
#define PWM_CR_PWM_CH3L_CLR_MSK  (((1U << PWM_CR_PWM_CH3L_CLR_LEN) - 1) << PWM_CR_PWM_CH3L_CLR_POS)
#define PWM_CR_PWM_CH3L_CLR_UMSK (~(((1U << PWM_CR_PWM_CH3L_CLR_LEN) - 1) << PWM_CR_PWM_CH3L_CLR_POS))
#define PWM_CR_PWM_CH3H_CLR      PWM_CR_PWM_CH3H_CLR
#define PWM_CR_PWM_CH3H_CLR_POS  (7U)
#define PWM_CR_PWM_CH3H_CLR_LEN  (1U)
#define PWM_CR_PWM_CH3H_CLR_MSK  (((1U << PWM_CR_PWM_CH3H_CLR_LEN) - 1) << PWM_CR_PWM_CH3H_CLR_POS)
#define PWM_CR_PWM_CH3H_CLR_UMSK (~(((1U << PWM_CR_PWM_CH3H_CLR_LEN) - 1) << PWM_CR_PWM_CH3H_CLR_POS))
#define PWM_CR_PWM_PRDE_CLR      PWM_CR_PWM_PRDE_CLR
#define PWM_CR_PWM_PRDE_CLR_POS  (8U)
#define PWM_CR_PWM_PRDE_CLR_LEN  (1U)
#define PWM_CR_PWM_PRDE_CLR_MSK  (((1U << PWM_CR_PWM_PRDE_CLR_LEN) - 1) << PWM_CR_PWM_PRDE_CLR_POS)
#define PWM_CR_PWM_PRDE_CLR_UMSK (~(((1U << PWM_CR_PWM_PRDE_CLR_LEN) - 1) << PWM_CR_PWM_PRDE_CLR_POS))
#define PWM_CR_PWM_BRK_CLR       PWM_CR_PWM_BRK_CLR
#define PWM_CR_PWM_BRK_CLR_POS   (9U)
#define PWM_CR_PWM_BRK_CLR_LEN   (1U)
#define PWM_CR_PWM_BRK_CLR_MSK   (((1U << PWM_CR_PWM_BRK_CLR_LEN) - 1) << PWM_CR_PWM_BRK_CLR_POS)
#define PWM_CR_PWM_BRK_CLR_UMSK  (~(((1U << PWM_CR_PWM_BRK_CLR_LEN) - 1) << PWM_CR_PWM_BRK_CLR_POS))
#define PWM_CR_PWM_REPT_CLR      PWM_CR_PWM_REPT_CLR
#define PWM_CR_PWM_REPT_CLR_POS  (10U)
#define PWM_CR_PWM_REPT_CLR_LEN  (1U)
#define PWM_CR_PWM_REPT_CLR_MSK  (((1U << PWM_CR_PWM_REPT_CLR_LEN) - 1) << PWM_CR_PWM_REPT_CLR_POS)
#define PWM_CR_PWM_REPT_CLR_UMSK (~(((1U << PWM_CR_PWM_REPT_CLR_LEN) - 1) << PWM_CR_PWM_REPT_CLR_POS))

/* 0x2C : pwm_int_en */
#define PWM_INT_EN_OFFSET       (0x2C)
#define PWM_CR_PWM_CH0L_EN      PWM_CR_PWM_CH0L_EN
#define PWM_CR_PWM_CH0L_EN_POS  (0U)
#define PWM_CR_PWM_CH0L_EN_LEN  (1U)
#define PWM_CR_PWM_CH0L_EN_MSK  (((1U << PWM_CR_PWM_CH0L_EN_LEN) - 1) << PWM_CR_PWM_CH0L_EN_POS)
#define PWM_CR_PWM_CH0L_EN_UMSK (~(((1U << PWM_CR_PWM_CH0L_EN_LEN) - 1) << PWM_CR_PWM_CH0L_EN_POS))
#define PWM_CR_PWM_CH0H_EN      PWM_CR_PWM_CH0H_EN
#define PWM_CR_PWM_CH0H_EN_POS  (1U)
#define PWM_CR_PWM_CH0H_EN_LEN  (1U)
#define PWM_CR_PWM_CH0H_EN_MSK  (((1U << PWM_CR_PWM_CH0H_EN_LEN) - 1) << PWM_CR_PWM_CH0H_EN_POS)
#define PWM_CR_PWM_CH0H_EN_UMSK (~(((1U << PWM_CR_PWM_CH0H_EN_LEN) - 1) << PWM_CR_PWM_CH0H_EN_POS))
#define PWM_CR_PWM_CH1L_EN      PWM_CR_PWM_CH1L_EN
#define PWM_CR_PWM_CH1L_EN_POS  (2U)
#define PWM_CR_PWM_CH1L_EN_LEN  (1U)
#define PWM_CR_PWM_CH1L_EN_MSK  (((1U << PWM_CR_PWM_CH1L_EN_LEN) - 1) << PWM_CR_PWM_CH1L_EN_POS)
#define PWM_CR_PWM_CH1L_EN_UMSK (~(((1U << PWM_CR_PWM_CH1L_EN_LEN) - 1) << PWM_CR_PWM_CH1L_EN_POS))
#define PWM_CR_PWM_CH1H_EN      PWM_CR_PWM_CH1H_EN
#define PWM_CR_PWM_CH1H_EN_POS  (3U)
#define PWM_CR_PWM_CH1H_EN_LEN  (1U)
#define PWM_CR_PWM_CH1H_EN_MSK  (((1U << PWM_CR_PWM_CH1H_EN_LEN) - 1) << PWM_CR_PWM_CH1H_EN_POS)
#define PWM_CR_PWM_CH1H_EN_UMSK (~(((1U << PWM_CR_PWM_CH1H_EN_LEN) - 1) << PWM_CR_PWM_CH1H_EN_POS))
#define PWM_CR_PWM_CH2L_EN      PWM_CR_PWM_CH2L_EN
#define PWM_CR_PWM_CH2L_EN_POS  (4U)
#define PWM_CR_PWM_CH2L_EN_LEN  (1U)
#define PWM_CR_PWM_CH2L_EN_MSK  (((1U << PWM_CR_PWM_CH2L_EN_LEN) - 1) << PWM_CR_PWM_CH2L_EN_POS)
#define PWM_CR_PWM_CH2L_EN_UMSK (~(((1U << PWM_CR_PWM_CH2L_EN_LEN) - 1) << PWM_CR_PWM_CH2L_EN_POS))
#define PWM_CR_PWM_CH2H_EN      PWM_CR_PWM_CH2H_EN
#define PWM_CR_PWM_CH2H_EN_POS  (5U)
#define PWM_CR_PWM_CH2H_EN_LEN  (1U)
#define PWM_CR_PWM_CH2H_EN_MSK  (((1U << PWM_CR_PWM_CH2H_EN_LEN) - 1) << PWM_CR_PWM_CH2H_EN_POS)
#define PWM_CR_PWM_CH2H_EN_UMSK (~(((1U << PWM_CR_PWM_CH2H_EN_LEN) - 1) << PWM_CR_PWM_CH2H_EN_POS))
#define PWM_CR_PWM_CH3L_EN      PWM_CR_PWM_CH3L_EN
#define PWM_CR_PWM_CH3L_EN_POS  (6U)
#define PWM_CR_PWM_CH3L_EN_LEN  (1U)
#define PWM_CR_PWM_CH3L_EN_MSK  (((1U << PWM_CR_PWM_CH3L_EN_LEN) - 1) << PWM_CR_PWM_CH3L_EN_POS)
#define PWM_CR_PWM_CH3L_EN_UMSK (~(((1U << PWM_CR_PWM_CH3L_EN_LEN) - 1) << PWM_CR_PWM_CH3L_EN_POS))
#define PWM_CR_PWM_CH3H_EN      PWM_CR_PWM_CH3H_EN
#define PWM_CR_PWM_CH3H_EN_POS  (7U)
#define PWM_CR_PWM_CH3H_EN_LEN  (1U)
#define PWM_CR_PWM_CH3H_EN_MSK  (((1U << PWM_CR_PWM_CH3H_EN_LEN) - 1) << PWM_CR_PWM_CH3H_EN_POS)
#define PWM_CR_PWM_CH3H_EN_UMSK (~(((1U << PWM_CR_PWM_CH3H_EN_LEN) - 1) << PWM_CR_PWM_CH3H_EN_POS))
#define PWM_CR_PWM_PRDE_EN      PWM_CR_PWM_PRDE_EN
#define PWM_CR_PWM_PRDE_EN_POS  (8U)
#define PWM_CR_PWM_PRDE_EN_LEN  (1U)
#define PWM_CR_PWM_PRDE_EN_MSK  (((1U << PWM_CR_PWM_PRDE_EN_LEN) - 1) << PWM_CR_PWM_PRDE_EN_POS)
#define PWM_CR_PWM_PRDE_EN_UMSK (~(((1U << PWM_CR_PWM_PRDE_EN_LEN) - 1) << PWM_CR_PWM_PRDE_EN_POS))
#define PWM_CR_PWM_BRK_EN       PWM_CR_PWM_BRK_EN
#define PWM_CR_PWM_BRK_EN_POS   (9U)
#define PWM_CR_PWM_BRK_EN_LEN   (1U)
#define PWM_CR_PWM_BRK_EN_MSK   (((1U << PWM_CR_PWM_BRK_EN_LEN) - 1) << PWM_CR_PWM_BRK_EN_POS)
#define PWM_CR_PWM_BRK_EN_UMSK  (~(((1U << PWM_CR_PWM_BRK_EN_LEN) - 1) << PWM_CR_PWM_BRK_EN_POS))
#define PWM_CR_PWM_REPT_EN      PWM_CR_PWM_REPT_EN
#define PWM_CR_PWM_REPT_EN_POS  (10U)
#define PWM_CR_PWM_REPT_EN_LEN  (1U)
#define PWM_CR_PWM_REPT_EN_MSK  (((1U << PWM_CR_PWM_REPT_EN_LEN) - 1) << PWM_CR_PWM_REPT_EN_POS)
#define PWM_CR_PWM_REPT_EN_UMSK (~(((1U << PWM_CR_PWM_REPT_EN_LEN) - 1) << PWM_CR_PWM_REPT_EN_POS))

struct pwm_channel_reg {
    /* 0x00 : pwm_config0 */
    union {
        struct {
            uint32_t pwm_clk_div      : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_18   : 3;  /* [18:16],       rsvd,        0x0 */
            uint32_t pwm_stop_on_rept : 1;  /* [   19],        r/w,        0x0 */
            uint32_t pwm_adc_trg_src  : 4;  /* [23:20],        r/w,        0xf */
            uint32_t pwm_sw_break_en  : 1;  /* [   24],        r/w,        0x0 */
            uint32_t pwm_ext_break_en : 1;  /* [   25],        r/w,        0x0 */
            uint32_t pwm_ext_break_pl : 1;  /* [   26],        r/w,        0x0 */
            uint32_t pwm_stop_en      : 1;  /* [   27],        r/w,        0x0 */
            uint32_t pwm_stop_mode    : 1;  /* [   28],        r/w,        0x1 */
            uint32_t pwm_sts_stop     : 1;  /* [   29],          r,        0x0 */
            uint32_t reg_clk_sel      : 2;  /* [31:30],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_config0;

    /* 0x04 : pwm_config1 */
    union {
        struct {
            uint32_t pwm_ch0_pen : 1; /* [    0],        r/w,        0x0 */
            uint32_t pwm_ch0_psi : 1; /* [    1],        r/w,        0x0 */
            uint32_t pwm_ch0_nen : 1; /* [    2],        r/w,        0x0 */
            uint32_t pwm_ch0_nsi : 1; /* [    3],        r/w,        0x1 */
            uint32_t pwm_ch1_pen : 1; /* [    4],        r/w,        0x0 */
            uint32_t pwm_ch1_psi : 1; /* [    5],        r/w,        0x0 */
            uint32_t pwm_ch1_nen : 1; /* [    6],        r/w,        0x0 */
            uint32_t pwm_ch1_nsi : 1; /* [    7],        r/w,        0x1 */
            uint32_t pwm_ch2_pen : 1; /* [    8],        r/w,        0x0 */
            uint32_t pwm_ch2_psi : 1; /* [    9],        r/w,        0x0 */
            uint32_t pwm_ch2_nen : 1; /* [   10],        r/w,        0x0 */
            uint32_t pwm_ch2_nsi : 1; /* [   11],        r/w,        0x1 */
            uint32_t pwm_ch3_pen : 1; /* [   12],        r/w,        0x0 */
            uint32_t pwm_ch3_psi : 1; /* [   13],        r/w,        0x0 */
            uint32_t pwm_ch3_nen : 1; /* [   14],        r/w,        0x0 */
            uint32_t pwm_ch3_nsi : 1; /* [   15],        r/w,        0x1 */
            uint32_t pwm_ch0_ppl : 1; /* [   16],        r/w,        0x1 */
            uint32_t pwm_ch0_npl : 1; /* [   17],        r/w,        0x1 */
            uint32_t pwm_ch1_ppl : 1; /* [   18],        r/w,        0x1 */
            uint32_t pwm_ch1_npl : 1; /* [   19],        r/w,        0x1 */
            uint32_t pwm_ch2_ppl : 1; /* [   20],        r/w,        0x1 */
            uint32_t pwm_ch2_npl : 1; /* [   21],        r/w,        0x1 */
            uint32_t pwm_ch3_ppl : 1; /* [   22],        r/w,        0x1 */
            uint32_t pwm_ch3_npl : 1; /* [   23],        r/w,        0x1 */
            uint32_t pwm_ch0_pbs : 1; /* [   24],        r/w,        0x0 */
            uint32_t pwm_ch0_nbs : 1; /* [   25],        r/w,        0x0 */
            uint32_t pwm_ch1_pbs : 1; /* [   26],        r/w,        0x0 */
            uint32_t pwm_ch1_nbs : 1; /* [   27],        r/w,        0x0 */
            uint32_t pwm_ch2_pbs : 1; /* [   28],        r/w,        0x0 */
            uint32_t pwm_ch2_nbs : 1; /* [   29],        r/w,        0x0 */
            uint32_t pwm_ch3_pbs : 1; /* [   30],        r/w,        0x0 */
            uint32_t pwm_ch3_nbs : 1; /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_config1;

    /* 0x08 : pwm_period */
    union {
        struct {
            uint32_t pwm_period         : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_int_period_cnt : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_period;

    /* 0x0C : pwm_dead_time */
    union {
        struct {
            uint32_t pwm_ch0_dtg : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t pwm_ch1_dtg : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t pwm_ch2_dtg : 8; /* [23:16],        r/w,        0x0 */
            uint32_t pwm_ch3_dtg : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_dead_time;

    /* 0x10 : pwm_ch0_thre */
    union {
        struct {
            uint32_t pwm_ch0_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch0_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_ch0_thre;

    /* 0x14 : pwm_ch1_thre */
    union {
        struct {
            uint32_t pwm_ch1_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch1_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_ch1_thre;

    /* 0x18 : pwm_ch2_thre */
    union {
        struct {
            uint32_t pwm_ch2_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch2_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_ch2_thre;

    /* 0x1C : pwm_ch3_thre */
    union {
        struct {
            uint32_t pwm_ch3_threL : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t pwm_ch3_threH : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_ch3_thre;

    /* 0x20 : pwm_int_sts */
    union {
        struct {
            uint32_t pwm_ch0l_int   : 1;  /* [    0],          r,        0x0 */
            uint32_t pwm_ch0h_int   : 1;  /* [    1],          r,        0x0 */
            uint32_t pwm_ch1l_int   : 1;  /* [    2],          r,        0x0 */
            uint32_t pwm_ch1h_int   : 1;  /* [    3],          r,        0x0 */
            uint32_t pwm_ch2l_int   : 1;  /* [    4],          r,        0x0 */
            uint32_t pwm_ch2h_int   : 1;  /* [    5],          r,        0x0 */
            uint32_t pwm_ch3l_int   : 1;  /* [    6],          r,        0x0 */
            uint32_t pwm_ch3h_int   : 1;  /* [    7],          r,        0x0 */
            uint32_t pwm_prde_int   : 1;  /* [    8],          r,        0x0 */
            uint32_t pwm_brk_int    : 1;  /* [    9],          r,        0x0 */
            uint32_t pwm_rept_int   : 1;  /* [   10],          r,        0x0 */
            uint32_t reserved_11_31 : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_int_sts;

    /* 0x24 : pwm_int_mask */
    union {
        struct {
            uint32_t cr_pwm_ch0l_mask : 1;  /* [    0],        r/w,        0x1 */
            uint32_t cr_pwm_ch0h_mask : 1;  /* [    1],        r/w,        0x1 */
            uint32_t cr_pwm_ch1l_mask : 1;  /* [    2],        r/w,        0x1 */
            uint32_t cr_pwm_ch1h_mask : 1;  /* [    3],        r/w,        0x1 */
            uint32_t cr_pwm_ch2l_mask : 1;  /* [    4],        r/w,        0x1 */
            uint32_t cr_pwm_ch2h_mask : 1;  /* [    5],        r/w,        0x1 */
            uint32_t cr_pwm_ch3l_mask : 1;  /* [    6],        r/w,        0x1 */
            uint32_t cr_pwm_ch3h_mask : 1;  /* [    7],        r/w,        0x1 */
            uint32_t cr_pwm_prde_mask : 1;  /* [    8],        r/w,        0x1 */
            uint32_t cr_pwm_brk_mask  : 1;  /* [    9],        r/w,        0x1 */
            uint32_t cr_pwm_rept_mask : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_31   : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_int_mask;

    /* 0x28 : pwm_int_clear */
    union {
        struct {
            uint32_t cr_pwm_ch0l_clr : 1;  /* [    0],        w1c,        0x0 */
            uint32_t cr_pwm_ch0h_clr : 1;  /* [    1],        w1c,        0x0 */
            uint32_t cr_pwm_ch1l_clr : 1;  /* [    2],        w1c,        0x0 */
            uint32_t cr_pwm_ch1h_clr : 1;  /* [    3],        w1c,        0x0 */
            uint32_t cr_pwm_ch2l_clr : 1;  /* [    4],        w1c,        0x0 */
            uint32_t cr_pwm_ch2h_clr : 1;  /* [    5],        w1c,        0x0 */
            uint32_t cr_pwm_ch3l_clr : 1;  /* [    6],        w1c,        0x0 */
            uint32_t cr_pwm_ch3h_clr : 1;  /* [    7],        w1c,        0x0 */
            uint32_t cr_pwm_prde_clr : 1;  /* [    8],        w1c,        0x0 */
            uint32_t cr_pwm_brk_clr  : 1;  /* [    9],        w1c,        0x0 */
            uint32_t cr_pwm_rept_clr : 1;  /* [   10],        w1c,        0x0 */
            uint32_t reserved_11_31  : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_int_clear;

    /* 0x2C : pwm_int_en */
    union {
        struct {
            uint32_t cr_pwm_ch0l_en : 1;  /* [    0],        r/w,        0x1 */
            uint32_t cr_pwm_ch0h_en : 1;  /* [    1],        r/w,        0x1 */
            uint32_t cr_pwm_ch1l_en : 1;  /* [    2],        r/w,        0x1 */
            uint32_t cr_pwm_ch1h_en : 1;  /* [    3],        r/w,        0x1 */
            uint32_t cr_pwm_ch2l_en : 1;  /* [    4],        r/w,        0x1 */
            uint32_t cr_pwm_ch2h_en : 1;  /* [    5],        r/w,        0x1 */
            uint32_t cr_pwm_ch3l_en : 1;  /* [    6],        r/w,        0x1 */
            uint32_t cr_pwm_ch3h_en : 1;  /* [    7],        r/w,        0x1 */
            uint32_t cr_pwm_prde_en : 1;  /* [    8],        r/w,        0x1 */
            uint32_t cr_pwm_brk_en  : 1;  /* [    9],        r/w,        0x0 */
            uint32_t cr_pwm_rept_en : 1;  /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_31 : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } pwm_int_en;
};

typedef volatile struct pwm_channel_reg pwm_channel_reg_t;

#define PWM_CHANNEL_OFFSET 0x40

#endif /* __PWM_REG_H__ */
