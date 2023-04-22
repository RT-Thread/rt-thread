/**
  ******************************************************************************
  * @file    acomp_reg.h
  * @version V1.0
  * @date    2023-03-07
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

#ifndef __HARDWARE_ACOMP_H__
#define __HARDWARE_ACOMP_H__

/****************************************************************************
 * Pre-processor Definitions
****************************************************************************/

/* Register offsets *********************************************************/
/* aon base */
#define AON_ACOMP_REG_ACOMP0_CTRL_OFFSET        (0x900) /* acomp0_ctrl */
#define AON_ACOMP_REG_ACOMP1_CTRL_OFFSET        (0x904) /* acomp0_ctrl */
#define AON_ACOMP_REG_ACOMP_CFG_OFFSET          (0x908) /* acomp_ctrl */


/* Register Bitfield definitions *****************************************************/
/* 0x900 : acomp0_ctrl */
/* 0x904 : acomp1_ctrl */
#define AON_ACOMP_MUX_EN           (1 << 26U)
#define AON_ACOMP_POS_SEL_SHIFT    (22U)
#define AON_ACOMP_POS_SEL_MASK     (0xf << AON_ACOMP_POS_SEL_SHIFT)
#define AON_ACOMP_NEG_SEL_SHIFT    (18U)
#define AON_ACOMP_NEG_SEL_MASK     (0xf << AON_ACOMP_NEG_SEL_SHIFT)
#define AON_ACOMP_LEVEL_SEL_SHIFT  (12U)
#define AON_ACOMP_LEVEL_SEL_MASK   (0x3f << AON_ACOMP_LEVEL_SEL_SHIFT)
#define AON_ACOMP_BIAS_PROG_SHIFT  (10U)
#define AON_ACOMP_BIAS_PROG_MASK   (0x3 << AON_ACOMP_BIAS_PROG_SHIFT)
#define AON_ACOMP_HYST_SELP_SHIFT  (7U)
#define AON_ACOMP_HYST_SELP_MASK   (0x7 << AON_ACOMP_HYST_SELP_SHIFT)
#define AON_ACOMP_HYST_SELN_SHIFT  (4U)
#define AON_ACOMP_HYST_SELN_MASK   (0x7 << AON_ACOMP_HYST_SELN_SHIFT)
#define AON_ACOMP_EN               (1 << 0U)

/* 0x908 : acomp_ctrl */
#define AON_ACOMP_VREF_SEL_SHIFT        (24U)
#define AON_ACOMP_VREF_SEL_MASK         (0x3f << AON_ACOMP_VREF_SEL_SHIFT)
#define AON_ACOMP0_OUT_RAW_DATA_SHIFT   (19U)
#define AON_ACOMP0_OUT_RAW_DATA_MASK    (0x1 << AON_ACOMP0_OUT_RAW_DATA_SHIFT)
#define AON_ACOMP1_OUT_RAW_DATA_SHIFT   (17U)
#define AON_ACOMP1_OUT_RAW_DATA_MASK    (0x1 << AON_ACOMP1_OUT_RAW_DATA_SHIFT)
#define AON_ACOMP0_TEST_SEL_SHIFT       (12U)
#define AON_ACOMP0_TEST_SEL_MASK        (0x3 << AON_ACOMP0_TEST_SEL_SHIFT)
#define AON_ACOMP1_TEST_SEL_SHIFT       (10U)
#define AON_ACOMP1_TEST_SEL_MASK        (0x3 << AON_ACOMP1_TEST_SEL_SHIFT)
#define AON_ACOMP0_TEST_EN              (1 << 9U)
#define AON_ACOMP1_TEST_EN              (1 << 8U)
#define AON_ACOMP0_RSTN_ANA             (1 << 1U)
#define AON_ACOMP1_RSTN_ANA             (1 << 0U)
#endif
