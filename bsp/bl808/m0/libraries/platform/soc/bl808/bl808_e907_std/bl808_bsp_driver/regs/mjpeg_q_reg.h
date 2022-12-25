/**
  ******************************************************************************
  * @file    mjpeg_q_reg.h
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
#ifndef __MJPEG_Q_REG_H__
#define __MJPEG_Q_REG_H__

#include "bl808.h"

/* 0x400 : mjpeg_q_param_00 */
#define MJPEG_Q_PARAM_00_OFFSET (0x400)
#define MJPEG_Q_REG_Q_0_00      MJPEG_Q_REG_Q_0_00
#define MJPEG_Q_REG_Q_0_00_POS  (0U)
#define MJPEG_Q_REG_Q_0_00_LEN  (12U)
#define MJPEG_Q_REG_Q_0_00_MSK  (((1U << MJPEG_Q_REG_Q_0_00_LEN) - 1) << MJPEG_Q_REG_Q_0_00_POS)
#define MJPEG_Q_REG_Q_0_00_UMSK (~(((1U << MJPEG_Q_REG_Q_0_00_LEN) - 1) << MJPEG_Q_REG_Q_0_00_POS))
#define MJPEG_Q_REG_Q_0_01      MJPEG_Q_REG_Q_0_01
#define MJPEG_Q_REG_Q_0_01_POS  (16U)
#define MJPEG_Q_REG_Q_0_01_LEN  (12U)
#define MJPEG_Q_REG_Q_0_01_MSK  (((1U << MJPEG_Q_REG_Q_0_01_LEN) - 1) << MJPEG_Q_REG_Q_0_01_POS)
#define MJPEG_Q_REG_Q_0_01_UMSK (~(((1U << MJPEG_Q_REG_Q_0_01_LEN) - 1) << MJPEG_Q_REG_Q_0_01_POS))

/* 0x404 : mjpeg_q_param_02 */
#define MJPEG_Q_PARAM_02_OFFSET (0x404)
#define MJPEG_Q_REG_Q_0_02      MJPEG_Q_REG_Q_0_02
#define MJPEG_Q_REG_Q_0_02_POS  (0U)
#define MJPEG_Q_REG_Q_0_02_LEN  (12U)
#define MJPEG_Q_REG_Q_0_02_MSK  (((1U << MJPEG_Q_REG_Q_0_02_LEN) - 1) << MJPEG_Q_REG_Q_0_02_POS)
#define MJPEG_Q_REG_Q_0_02_UMSK (~(((1U << MJPEG_Q_REG_Q_0_02_LEN) - 1) << MJPEG_Q_REG_Q_0_02_POS))
#define MJPEG_Q_REG_Q_0_03      MJPEG_Q_REG_Q_0_03
#define MJPEG_Q_REG_Q_0_03_POS  (16U)
#define MJPEG_Q_REG_Q_0_03_LEN  (12U)
#define MJPEG_Q_REG_Q_0_03_MSK  (((1U << MJPEG_Q_REG_Q_0_03_LEN) - 1) << MJPEG_Q_REG_Q_0_03_POS)
#define MJPEG_Q_REG_Q_0_03_UMSK (~(((1U << MJPEG_Q_REG_Q_0_03_LEN) - 1) << MJPEG_Q_REG_Q_0_03_POS))

/* 0x408 : mjpeg_q_param_04 */
#define MJPEG_Q_PARAM_04_OFFSET (0x408)
#define MJPEG_Q_REG_Q_0_04      MJPEG_Q_REG_Q_0_04
#define MJPEG_Q_REG_Q_0_04_POS  (0U)
#define MJPEG_Q_REG_Q_0_04_LEN  (12U)
#define MJPEG_Q_REG_Q_0_04_MSK  (((1U << MJPEG_Q_REG_Q_0_04_LEN) - 1) << MJPEG_Q_REG_Q_0_04_POS)
#define MJPEG_Q_REG_Q_0_04_UMSK (~(((1U << MJPEG_Q_REG_Q_0_04_LEN) - 1) << MJPEG_Q_REG_Q_0_04_POS))
#define MJPEG_Q_REG_Q_0_05      MJPEG_Q_REG_Q_0_05
#define MJPEG_Q_REG_Q_0_05_POS  (16U)
#define MJPEG_Q_REG_Q_0_05_LEN  (12U)
#define MJPEG_Q_REG_Q_0_05_MSK  (((1U << MJPEG_Q_REG_Q_0_05_LEN) - 1) << MJPEG_Q_REG_Q_0_05_POS)
#define MJPEG_Q_REG_Q_0_05_UMSK (~(((1U << MJPEG_Q_REG_Q_0_05_LEN) - 1) << MJPEG_Q_REG_Q_0_05_POS))

/* 0x40C : mjpeg_q_param_06 */
#define MJPEG_Q_PARAM_06_OFFSET (0x40C)
#define MJPEG_Q_REG_Q_0_06      MJPEG_Q_REG_Q_0_06
#define MJPEG_Q_REG_Q_0_06_POS  (0U)
#define MJPEG_Q_REG_Q_0_06_LEN  (12U)
#define MJPEG_Q_REG_Q_0_06_MSK  (((1U << MJPEG_Q_REG_Q_0_06_LEN) - 1) << MJPEG_Q_REG_Q_0_06_POS)
#define MJPEG_Q_REG_Q_0_06_UMSK (~(((1U << MJPEG_Q_REG_Q_0_06_LEN) - 1) << MJPEG_Q_REG_Q_0_06_POS))
#define MJPEG_Q_REG_Q_0_07      MJPEG_Q_REG_Q_0_07
#define MJPEG_Q_REG_Q_0_07_POS  (16U)
#define MJPEG_Q_REG_Q_0_07_LEN  (12U)
#define MJPEG_Q_REG_Q_0_07_MSK  (((1U << MJPEG_Q_REG_Q_0_07_LEN) - 1) << MJPEG_Q_REG_Q_0_07_POS)
#define MJPEG_Q_REG_Q_0_07_UMSK (~(((1U << MJPEG_Q_REG_Q_0_07_LEN) - 1) << MJPEG_Q_REG_Q_0_07_POS))

/* 0x410 : mjpeg_q_param_08 */
#define MJPEG_Q_PARAM_08_OFFSET (0x410)
#define MJPEG_Q_REG_Q_0_08      MJPEG_Q_REG_Q_0_08
#define MJPEG_Q_REG_Q_0_08_POS  (0U)
#define MJPEG_Q_REG_Q_0_08_LEN  (12U)
#define MJPEG_Q_REG_Q_0_08_MSK  (((1U << MJPEG_Q_REG_Q_0_08_LEN) - 1) << MJPEG_Q_REG_Q_0_08_POS)
#define MJPEG_Q_REG_Q_0_08_UMSK (~(((1U << MJPEG_Q_REG_Q_0_08_LEN) - 1) << MJPEG_Q_REG_Q_0_08_POS))
#define MJPEG_Q_REG_Q_0_09      MJPEG_Q_REG_Q_0_09
#define MJPEG_Q_REG_Q_0_09_POS  (16U)
#define MJPEG_Q_REG_Q_0_09_LEN  (12U)
#define MJPEG_Q_REG_Q_0_09_MSK  (((1U << MJPEG_Q_REG_Q_0_09_LEN) - 1) << MJPEG_Q_REG_Q_0_09_POS)
#define MJPEG_Q_REG_Q_0_09_UMSK (~(((1U << MJPEG_Q_REG_Q_0_09_LEN) - 1) << MJPEG_Q_REG_Q_0_09_POS))

/* 0x414 : mjpeg_q_param_0a */
#define MJPEG_Q_PARAM_0A_OFFSET (0x414)
#define MJPEG_Q_REG_Q_0_0A      MJPEG_Q_REG_Q_0_0A
#define MJPEG_Q_REG_Q_0_0A_POS  (0U)
#define MJPEG_Q_REG_Q_0_0A_LEN  (12U)
#define MJPEG_Q_REG_Q_0_0A_MSK  (((1U << MJPEG_Q_REG_Q_0_0A_LEN) - 1) << MJPEG_Q_REG_Q_0_0A_POS)
#define MJPEG_Q_REG_Q_0_0A_UMSK (~(((1U << MJPEG_Q_REG_Q_0_0A_LEN) - 1) << MJPEG_Q_REG_Q_0_0A_POS))
#define MJPEG_Q_REG_Q_0_0B      MJPEG_Q_REG_Q_0_0B
#define MJPEG_Q_REG_Q_0_0B_POS  (16U)
#define MJPEG_Q_REG_Q_0_0B_LEN  (12U)
#define MJPEG_Q_REG_Q_0_0B_MSK  (((1U << MJPEG_Q_REG_Q_0_0B_LEN) - 1) << MJPEG_Q_REG_Q_0_0B_POS)
#define MJPEG_Q_REG_Q_0_0B_UMSK (~(((1U << MJPEG_Q_REG_Q_0_0B_LEN) - 1) << MJPEG_Q_REG_Q_0_0B_POS))

/* 0x418 : mjpeg_q_param_0c */
#define MJPEG_Q_PARAM_0C_OFFSET (0x418)
#define MJPEG_Q_REG_Q_0_0C      MJPEG_Q_REG_Q_0_0C
#define MJPEG_Q_REG_Q_0_0C_POS  (0U)
#define MJPEG_Q_REG_Q_0_0C_LEN  (12U)
#define MJPEG_Q_REG_Q_0_0C_MSK  (((1U << MJPEG_Q_REG_Q_0_0C_LEN) - 1) << MJPEG_Q_REG_Q_0_0C_POS)
#define MJPEG_Q_REG_Q_0_0C_UMSK (~(((1U << MJPEG_Q_REG_Q_0_0C_LEN) - 1) << MJPEG_Q_REG_Q_0_0C_POS))
#define MJPEG_Q_REG_Q_0_0D      MJPEG_Q_REG_Q_0_0D
#define MJPEG_Q_REG_Q_0_0D_POS  (16U)
#define MJPEG_Q_REG_Q_0_0D_LEN  (12U)
#define MJPEG_Q_REG_Q_0_0D_MSK  (((1U << MJPEG_Q_REG_Q_0_0D_LEN) - 1) << MJPEG_Q_REG_Q_0_0D_POS)
#define MJPEG_Q_REG_Q_0_0D_UMSK (~(((1U << MJPEG_Q_REG_Q_0_0D_LEN) - 1) << MJPEG_Q_REG_Q_0_0D_POS))

/* 0x41C : mjpeg_q_param_0e */
#define MJPEG_Q_PARAM_0E_OFFSET (0x41C)
#define MJPEG_Q_REG_Q_0_0E      MJPEG_Q_REG_Q_0_0E
#define MJPEG_Q_REG_Q_0_0E_POS  (0U)
#define MJPEG_Q_REG_Q_0_0E_LEN  (12U)
#define MJPEG_Q_REG_Q_0_0E_MSK  (((1U << MJPEG_Q_REG_Q_0_0E_LEN) - 1) << MJPEG_Q_REG_Q_0_0E_POS)
#define MJPEG_Q_REG_Q_0_0E_UMSK (~(((1U << MJPEG_Q_REG_Q_0_0E_LEN) - 1) << MJPEG_Q_REG_Q_0_0E_POS))
#define MJPEG_Q_REG_Q_0_0F      MJPEG_Q_REG_Q_0_0F
#define MJPEG_Q_REG_Q_0_0F_POS  (16U)
#define MJPEG_Q_REG_Q_0_0F_LEN  (12U)
#define MJPEG_Q_REG_Q_0_0F_MSK  (((1U << MJPEG_Q_REG_Q_0_0F_LEN) - 1) << MJPEG_Q_REG_Q_0_0F_POS)
#define MJPEG_Q_REG_Q_0_0F_UMSK (~(((1U << MJPEG_Q_REG_Q_0_0F_LEN) - 1) << MJPEG_Q_REG_Q_0_0F_POS))

/* 0x420 : mjpeg_q_param_10 */
#define MJPEG_Q_PARAM_10_OFFSET (0x420)
#define MJPEG_Q_REG_Q_0_10      MJPEG_Q_REG_Q_0_10
#define MJPEG_Q_REG_Q_0_10_POS  (0U)
#define MJPEG_Q_REG_Q_0_10_LEN  (12U)
#define MJPEG_Q_REG_Q_0_10_MSK  (((1U << MJPEG_Q_REG_Q_0_10_LEN) - 1) << MJPEG_Q_REG_Q_0_10_POS)
#define MJPEG_Q_REG_Q_0_10_UMSK (~(((1U << MJPEG_Q_REG_Q_0_10_LEN) - 1) << MJPEG_Q_REG_Q_0_10_POS))
#define MJPEG_Q_REG_Q_0_11      MJPEG_Q_REG_Q_0_11
#define MJPEG_Q_REG_Q_0_11_POS  (16U)
#define MJPEG_Q_REG_Q_0_11_LEN  (12U)
#define MJPEG_Q_REG_Q_0_11_MSK  (((1U << MJPEG_Q_REG_Q_0_11_LEN) - 1) << MJPEG_Q_REG_Q_0_11_POS)
#define MJPEG_Q_REG_Q_0_11_UMSK (~(((1U << MJPEG_Q_REG_Q_0_11_LEN) - 1) << MJPEG_Q_REG_Q_0_11_POS))

/* 0x424 : mjpeg_q_param_12 */
#define MJPEG_Q_PARAM_12_OFFSET (0x424)
#define MJPEG_Q_REG_Q_0_12      MJPEG_Q_REG_Q_0_12
#define MJPEG_Q_REG_Q_0_12_POS  (0U)
#define MJPEG_Q_REG_Q_0_12_LEN  (12U)
#define MJPEG_Q_REG_Q_0_12_MSK  (((1U << MJPEG_Q_REG_Q_0_12_LEN) - 1) << MJPEG_Q_REG_Q_0_12_POS)
#define MJPEG_Q_REG_Q_0_12_UMSK (~(((1U << MJPEG_Q_REG_Q_0_12_LEN) - 1) << MJPEG_Q_REG_Q_0_12_POS))
#define MJPEG_Q_REG_Q_0_13      MJPEG_Q_REG_Q_0_13
#define MJPEG_Q_REG_Q_0_13_POS  (16U)
#define MJPEG_Q_REG_Q_0_13_LEN  (12U)
#define MJPEG_Q_REG_Q_0_13_MSK  (((1U << MJPEG_Q_REG_Q_0_13_LEN) - 1) << MJPEG_Q_REG_Q_0_13_POS)
#define MJPEG_Q_REG_Q_0_13_UMSK (~(((1U << MJPEG_Q_REG_Q_0_13_LEN) - 1) << MJPEG_Q_REG_Q_0_13_POS))

/* 0x428 : mjpeg_q_param_14 */
#define MJPEG_Q_PARAM_14_OFFSET (0x428)
#define MJPEG_Q_REG_Q_0_14      MJPEG_Q_REG_Q_0_14
#define MJPEG_Q_REG_Q_0_14_POS  (0U)
#define MJPEG_Q_REG_Q_0_14_LEN  (12U)
#define MJPEG_Q_REG_Q_0_14_MSK  (((1U << MJPEG_Q_REG_Q_0_14_LEN) - 1) << MJPEG_Q_REG_Q_0_14_POS)
#define MJPEG_Q_REG_Q_0_14_UMSK (~(((1U << MJPEG_Q_REG_Q_0_14_LEN) - 1) << MJPEG_Q_REG_Q_0_14_POS))
#define MJPEG_Q_REG_Q_0_15      MJPEG_Q_REG_Q_0_15
#define MJPEG_Q_REG_Q_0_15_POS  (16U)
#define MJPEG_Q_REG_Q_0_15_LEN  (12U)
#define MJPEG_Q_REG_Q_0_15_MSK  (((1U << MJPEG_Q_REG_Q_0_15_LEN) - 1) << MJPEG_Q_REG_Q_0_15_POS)
#define MJPEG_Q_REG_Q_0_15_UMSK (~(((1U << MJPEG_Q_REG_Q_0_15_LEN) - 1) << MJPEG_Q_REG_Q_0_15_POS))

/* 0x42C : mjpeg_q_param_16 */
#define MJPEG_Q_PARAM_16_OFFSET (0x42C)
#define MJPEG_Q_REG_Q_0_16      MJPEG_Q_REG_Q_0_16
#define MJPEG_Q_REG_Q_0_16_POS  (0U)
#define MJPEG_Q_REG_Q_0_16_LEN  (12U)
#define MJPEG_Q_REG_Q_0_16_MSK  (((1U << MJPEG_Q_REG_Q_0_16_LEN) - 1) << MJPEG_Q_REG_Q_0_16_POS)
#define MJPEG_Q_REG_Q_0_16_UMSK (~(((1U << MJPEG_Q_REG_Q_0_16_LEN) - 1) << MJPEG_Q_REG_Q_0_16_POS))
#define MJPEG_Q_REG_Q_0_17      MJPEG_Q_REG_Q_0_17
#define MJPEG_Q_REG_Q_0_17_POS  (16U)
#define MJPEG_Q_REG_Q_0_17_LEN  (12U)
#define MJPEG_Q_REG_Q_0_17_MSK  (((1U << MJPEG_Q_REG_Q_0_17_LEN) - 1) << MJPEG_Q_REG_Q_0_17_POS)
#define MJPEG_Q_REG_Q_0_17_UMSK (~(((1U << MJPEG_Q_REG_Q_0_17_LEN) - 1) << MJPEG_Q_REG_Q_0_17_POS))

/* 0x430 : mjpeg_q_param_18 */
#define MJPEG_Q_PARAM_18_OFFSET (0x430)
#define MJPEG_Q_REG_Q_0_18      MJPEG_Q_REG_Q_0_18
#define MJPEG_Q_REG_Q_0_18_POS  (0U)
#define MJPEG_Q_REG_Q_0_18_LEN  (12U)
#define MJPEG_Q_REG_Q_0_18_MSK  (((1U << MJPEG_Q_REG_Q_0_18_LEN) - 1) << MJPEG_Q_REG_Q_0_18_POS)
#define MJPEG_Q_REG_Q_0_18_UMSK (~(((1U << MJPEG_Q_REG_Q_0_18_LEN) - 1) << MJPEG_Q_REG_Q_0_18_POS))
#define MJPEG_Q_REG_Q_0_19      MJPEG_Q_REG_Q_0_19
#define MJPEG_Q_REG_Q_0_19_POS  (16U)
#define MJPEG_Q_REG_Q_0_19_LEN  (12U)
#define MJPEG_Q_REG_Q_0_19_MSK  (((1U << MJPEG_Q_REG_Q_0_19_LEN) - 1) << MJPEG_Q_REG_Q_0_19_POS)
#define MJPEG_Q_REG_Q_0_19_UMSK (~(((1U << MJPEG_Q_REG_Q_0_19_LEN) - 1) << MJPEG_Q_REG_Q_0_19_POS))

/* 0x434 : mjpeg_q_param_1a */
#define MJPEG_Q_PARAM_1A_OFFSET (0x434)
#define MJPEG_Q_REG_Q_0_1A      MJPEG_Q_REG_Q_0_1A
#define MJPEG_Q_REG_Q_0_1A_POS  (0U)
#define MJPEG_Q_REG_Q_0_1A_LEN  (12U)
#define MJPEG_Q_REG_Q_0_1A_MSK  (((1U << MJPEG_Q_REG_Q_0_1A_LEN) - 1) << MJPEG_Q_REG_Q_0_1A_POS)
#define MJPEG_Q_REG_Q_0_1A_UMSK (~(((1U << MJPEG_Q_REG_Q_0_1A_LEN) - 1) << MJPEG_Q_REG_Q_0_1A_POS))
#define MJPEG_Q_REG_Q_0_1B      MJPEG_Q_REG_Q_0_1B
#define MJPEG_Q_REG_Q_0_1B_POS  (16U)
#define MJPEG_Q_REG_Q_0_1B_LEN  (12U)
#define MJPEG_Q_REG_Q_0_1B_MSK  (((1U << MJPEG_Q_REG_Q_0_1B_LEN) - 1) << MJPEG_Q_REG_Q_0_1B_POS)
#define MJPEG_Q_REG_Q_0_1B_UMSK (~(((1U << MJPEG_Q_REG_Q_0_1B_LEN) - 1) << MJPEG_Q_REG_Q_0_1B_POS))

/* 0x438 : mjpeg_q_param_1c */
#define MJPEG_Q_PARAM_1C_OFFSET (0x438)
#define MJPEG_Q_REG_Q_0_1C      MJPEG_Q_REG_Q_0_1C
#define MJPEG_Q_REG_Q_0_1C_POS  (0U)
#define MJPEG_Q_REG_Q_0_1C_LEN  (12U)
#define MJPEG_Q_REG_Q_0_1C_MSK  (((1U << MJPEG_Q_REG_Q_0_1C_LEN) - 1) << MJPEG_Q_REG_Q_0_1C_POS)
#define MJPEG_Q_REG_Q_0_1C_UMSK (~(((1U << MJPEG_Q_REG_Q_0_1C_LEN) - 1) << MJPEG_Q_REG_Q_0_1C_POS))
#define MJPEG_Q_REG_Q_0_1D      MJPEG_Q_REG_Q_0_1D
#define MJPEG_Q_REG_Q_0_1D_POS  (16U)
#define MJPEG_Q_REG_Q_0_1D_LEN  (12U)
#define MJPEG_Q_REG_Q_0_1D_MSK  (((1U << MJPEG_Q_REG_Q_0_1D_LEN) - 1) << MJPEG_Q_REG_Q_0_1D_POS)
#define MJPEG_Q_REG_Q_0_1D_UMSK (~(((1U << MJPEG_Q_REG_Q_0_1D_LEN) - 1) << MJPEG_Q_REG_Q_0_1D_POS))

/* 0x43C : mjpeg_q_param_1e */
#define MJPEG_Q_PARAM_1E_OFFSET (0x43C)
#define MJPEG_Q_REG_Q_0_1E      MJPEG_Q_REG_Q_0_1E
#define MJPEG_Q_REG_Q_0_1E_POS  (0U)
#define MJPEG_Q_REG_Q_0_1E_LEN  (12U)
#define MJPEG_Q_REG_Q_0_1E_MSK  (((1U << MJPEG_Q_REG_Q_0_1E_LEN) - 1) << MJPEG_Q_REG_Q_0_1E_POS)
#define MJPEG_Q_REG_Q_0_1E_UMSK (~(((1U << MJPEG_Q_REG_Q_0_1E_LEN) - 1) << MJPEG_Q_REG_Q_0_1E_POS))
#define MJPEG_Q_REG_Q_0_1F      MJPEG_Q_REG_Q_0_1F
#define MJPEG_Q_REG_Q_0_1F_POS  (16U)
#define MJPEG_Q_REG_Q_0_1F_LEN  (12U)
#define MJPEG_Q_REG_Q_0_1F_MSK  (((1U << MJPEG_Q_REG_Q_0_1F_LEN) - 1) << MJPEG_Q_REG_Q_0_1F_POS)
#define MJPEG_Q_REG_Q_0_1F_UMSK (~(((1U << MJPEG_Q_REG_Q_0_1F_LEN) - 1) << MJPEG_Q_REG_Q_0_1F_POS))

/* 0x440 : mjpeg_q_param_20 */
#define MJPEG_Q_PARAM_20_OFFSET (0x440)
#define MJPEG_Q_REG_Q_0_20      MJPEG_Q_REG_Q_0_20
#define MJPEG_Q_REG_Q_0_20_POS  (0U)
#define MJPEG_Q_REG_Q_0_20_LEN  (12U)
#define MJPEG_Q_REG_Q_0_20_MSK  (((1U << MJPEG_Q_REG_Q_0_20_LEN) - 1) << MJPEG_Q_REG_Q_0_20_POS)
#define MJPEG_Q_REG_Q_0_20_UMSK (~(((1U << MJPEG_Q_REG_Q_0_20_LEN) - 1) << MJPEG_Q_REG_Q_0_20_POS))
#define MJPEG_Q_REG_Q_0_21      MJPEG_Q_REG_Q_0_21
#define MJPEG_Q_REG_Q_0_21_POS  (16U)
#define MJPEG_Q_REG_Q_0_21_LEN  (12U)
#define MJPEG_Q_REG_Q_0_21_MSK  (((1U << MJPEG_Q_REG_Q_0_21_LEN) - 1) << MJPEG_Q_REG_Q_0_21_POS)
#define MJPEG_Q_REG_Q_0_21_UMSK (~(((1U << MJPEG_Q_REG_Q_0_21_LEN) - 1) << MJPEG_Q_REG_Q_0_21_POS))

/* 0x444 : mjpeg_q_param_22 */
#define MJPEG_Q_PARAM_22_OFFSET (0x444)
#define MJPEG_Q_REG_Q_0_22      MJPEG_Q_REG_Q_0_22
#define MJPEG_Q_REG_Q_0_22_POS  (0U)
#define MJPEG_Q_REG_Q_0_22_LEN  (12U)
#define MJPEG_Q_REG_Q_0_22_MSK  (((1U << MJPEG_Q_REG_Q_0_22_LEN) - 1) << MJPEG_Q_REG_Q_0_22_POS)
#define MJPEG_Q_REG_Q_0_22_UMSK (~(((1U << MJPEG_Q_REG_Q_0_22_LEN) - 1) << MJPEG_Q_REG_Q_0_22_POS))
#define MJPEG_Q_REG_Q_0_23      MJPEG_Q_REG_Q_0_23
#define MJPEG_Q_REG_Q_0_23_POS  (16U)
#define MJPEG_Q_REG_Q_0_23_LEN  (12U)
#define MJPEG_Q_REG_Q_0_23_MSK  (((1U << MJPEG_Q_REG_Q_0_23_LEN) - 1) << MJPEG_Q_REG_Q_0_23_POS)
#define MJPEG_Q_REG_Q_0_23_UMSK (~(((1U << MJPEG_Q_REG_Q_0_23_LEN) - 1) << MJPEG_Q_REG_Q_0_23_POS))

/* 0x448 : mjpeg_q_param_24 */
#define MJPEG_Q_PARAM_24_OFFSET (0x448)
#define MJPEG_Q_REG_Q_0_24      MJPEG_Q_REG_Q_0_24
#define MJPEG_Q_REG_Q_0_24_POS  (0U)
#define MJPEG_Q_REG_Q_0_24_LEN  (12U)
#define MJPEG_Q_REG_Q_0_24_MSK  (((1U << MJPEG_Q_REG_Q_0_24_LEN) - 1) << MJPEG_Q_REG_Q_0_24_POS)
#define MJPEG_Q_REG_Q_0_24_UMSK (~(((1U << MJPEG_Q_REG_Q_0_24_LEN) - 1) << MJPEG_Q_REG_Q_0_24_POS))
#define MJPEG_Q_REG_Q_0_25      MJPEG_Q_REG_Q_0_25
#define MJPEG_Q_REG_Q_0_25_POS  (16U)
#define MJPEG_Q_REG_Q_0_25_LEN  (12U)
#define MJPEG_Q_REG_Q_0_25_MSK  (((1U << MJPEG_Q_REG_Q_0_25_LEN) - 1) << MJPEG_Q_REG_Q_0_25_POS)
#define MJPEG_Q_REG_Q_0_25_UMSK (~(((1U << MJPEG_Q_REG_Q_0_25_LEN) - 1) << MJPEG_Q_REG_Q_0_25_POS))

/* 0x44C : mjpeg_q_param_26 */
#define MJPEG_Q_PARAM_26_OFFSET (0x44C)
#define MJPEG_Q_REG_Q_0_26      MJPEG_Q_REG_Q_0_26
#define MJPEG_Q_REG_Q_0_26_POS  (0U)
#define MJPEG_Q_REG_Q_0_26_LEN  (12U)
#define MJPEG_Q_REG_Q_0_26_MSK  (((1U << MJPEG_Q_REG_Q_0_26_LEN) - 1) << MJPEG_Q_REG_Q_0_26_POS)
#define MJPEG_Q_REG_Q_0_26_UMSK (~(((1U << MJPEG_Q_REG_Q_0_26_LEN) - 1) << MJPEG_Q_REG_Q_0_26_POS))
#define MJPEG_Q_REG_Q_0_27      MJPEG_Q_REG_Q_0_27
#define MJPEG_Q_REG_Q_0_27_POS  (16U)
#define MJPEG_Q_REG_Q_0_27_LEN  (12U)
#define MJPEG_Q_REG_Q_0_27_MSK  (((1U << MJPEG_Q_REG_Q_0_27_LEN) - 1) << MJPEG_Q_REG_Q_0_27_POS)
#define MJPEG_Q_REG_Q_0_27_UMSK (~(((1U << MJPEG_Q_REG_Q_0_27_LEN) - 1) << MJPEG_Q_REG_Q_0_27_POS))

/* 0x450 : mjpeg_q_param_28 */
#define MJPEG_Q_PARAM_28_OFFSET (0x450)
#define MJPEG_Q_REG_Q_0_28      MJPEG_Q_REG_Q_0_28
#define MJPEG_Q_REG_Q_0_28_POS  (0U)
#define MJPEG_Q_REG_Q_0_28_LEN  (12U)
#define MJPEG_Q_REG_Q_0_28_MSK  (((1U << MJPEG_Q_REG_Q_0_28_LEN) - 1) << MJPEG_Q_REG_Q_0_28_POS)
#define MJPEG_Q_REG_Q_0_28_UMSK (~(((1U << MJPEG_Q_REG_Q_0_28_LEN) - 1) << MJPEG_Q_REG_Q_0_28_POS))
#define MJPEG_Q_REG_Q_0_29      MJPEG_Q_REG_Q_0_29
#define MJPEG_Q_REG_Q_0_29_POS  (16U)
#define MJPEG_Q_REG_Q_0_29_LEN  (12U)
#define MJPEG_Q_REG_Q_0_29_MSK  (((1U << MJPEG_Q_REG_Q_0_29_LEN) - 1) << MJPEG_Q_REG_Q_0_29_POS)
#define MJPEG_Q_REG_Q_0_29_UMSK (~(((1U << MJPEG_Q_REG_Q_0_29_LEN) - 1) << MJPEG_Q_REG_Q_0_29_POS))

/* 0x454 : mjpeg_q_param_2a */
#define MJPEG_Q_PARAM_2A_OFFSET (0x454)
#define MJPEG_Q_REG_Q_0_2A      MJPEG_Q_REG_Q_0_2A
#define MJPEG_Q_REG_Q_0_2A_POS  (0U)
#define MJPEG_Q_REG_Q_0_2A_LEN  (12U)
#define MJPEG_Q_REG_Q_0_2A_MSK  (((1U << MJPEG_Q_REG_Q_0_2A_LEN) - 1) << MJPEG_Q_REG_Q_0_2A_POS)
#define MJPEG_Q_REG_Q_0_2A_UMSK (~(((1U << MJPEG_Q_REG_Q_0_2A_LEN) - 1) << MJPEG_Q_REG_Q_0_2A_POS))
#define MJPEG_Q_REG_Q_0_2B      MJPEG_Q_REG_Q_0_2B
#define MJPEG_Q_REG_Q_0_2B_POS  (16U)
#define MJPEG_Q_REG_Q_0_2B_LEN  (12U)
#define MJPEG_Q_REG_Q_0_2B_MSK  (((1U << MJPEG_Q_REG_Q_0_2B_LEN) - 1) << MJPEG_Q_REG_Q_0_2B_POS)
#define MJPEG_Q_REG_Q_0_2B_UMSK (~(((1U << MJPEG_Q_REG_Q_0_2B_LEN) - 1) << MJPEG_Q_REG_Q_0_2B_POS))

/* 0x458 : mjpeg_q_param_2c */
#define MJPEG_Q_PARAM_2C_OFFSET (0x458)
#define MJPEG_Q_REG_Q_0_2C      MJPEG_Q_REG_Q_0_2C
#define MJPEG_Q_REG_Q_0_2C_POS  (0U)
#define MJPEG_Q_REG_Q_0_2C_LEN  (12U)
#define MJPEG_Q_REG_Q_0_2C_MSK  (((1U << MJPEG_Q_REG_Q_0_2C_LEN) - 1) << MJPEG_Q_REG_Q_0_2C_POS)
#define MJPEG_Q_REG_Q_0_2C_UMSK (~(((1U << MJPEG_Q_REG_Q_0_2C_LEN) - 1) << MJPEG_Q_REG_Q_0_2C_POS))
#define MJPEG_Q_REG_Q_0_2D      MJPEG_Q_REG_Q_0_2D
#define MJPEG_Q_REG_Q_0_2D_POS  (16U)
#define MJPEG_Q_REG_Q_0_2D_LEN  (12U)
#define MJPEG_Q_REG_Q_0_2D_MSK  (((1U << MJPEG_Q_REG_Q_0_2D_LEN) - 1) << MJPEG_Q_REG_Q_0_2D_POS)
#define MJPEG_Q_REG_Q_0_2D_UMSK (~(((1U << MJPEG_Q_REG_Q_0_2D_LEN) - 1) << MJPEG_Q_REG_Q_0_2D_POS))

/* 0x45C : mjpeg_q_param_2e */
#define MJPEG_Q_PARAM_2E_OFFSET (0x45C)
#define MJPEG_Q_REG_Q_0_2E      MJPEG_Q_REG_Q_0_2E
#define MJPEG_Q_REG_Q_0_2E_POS  (0U)
#define MJPEG_Q_REG_Q_0_2E_LEN  (12U)
#define MJPEG_Q_REG_Q_0_2E_MSK  (((1U << MJPEG_Q_REG_Q_0_2E_LEN) - 1) << MJPEG_Q_REG_Q_0_2E_POS)
#define MJPEG_Q_REG_Q_0_2E_UMSK (~(((1U << MJPEG_Q_REG_Q_0_2E_LEN) - 1) << MJPEG_Q_REG_Q_0_2E_POS))
#define MJPEG_Q_REG_Q_0_2F      MJPEG_Q_REG_Q_0_2F
#define MJPEG_Q_REG_Q_0_2F_POS  (16U)
#define MJPEG_Q_REG_Q_0_2F_LEN  (12U)
#define MJPEG_Q_REG_Q_0_2F_MSK  (((1U << MJPEG_Q_REG_Q_0_2F_LEN) - 1) << MJPEG_Q_REG_Q_0_2F_POS)
#define MJPEG_Q_REG_Q_0_2F_UMSK (~(((1U << MJPEG_Q_REG_Q_0_2F_LEN) - 1) << MJPEG_Q_REG_Q_0_2F_POS))

/* 0x460 : mjpeg_q_param_30 */
#define MJPEG_Q_PARAM_30_OFFSET (0x460)
#define MJPEG_Q_REG_Q_0_30      MJPEG_Q_REG_Q_0_30
#define MJPEG_Q_REG_Q_0_30_POS  (0U)
#define MJPEG_Q_REG_Q_0_30_LEN  (12U)
#define MJPEG_Q_REG_Q_0_30_MSK  (((1U << MJPEG_Q_REG_Q_0_30_LEN) - 1) << MJPEG_Q_REG_Q_0_30_POS)
#define MJPEG_Q_REG_Q_0_30_UMSK (~(((1U << MJPEG_Q_REG_Q_0_30_LEN) - 1) << MJPEG_Q_REG_Q_0_30_POS))
#define MJPEG_Q_REG_Q_0_31      MJPEG_Q_REG_Q_0_31
#define MJPEG_Q_REG_Q_0_31_POS  (16U)
#define MJPEG_Q_REG_Q_0_31_LEN  (12U)
#define MJPEG_Q_REG_Q_0_31_MSK  (((1U << MJPEG_Q_REG_Q_0_31_LEN) - 1) << MJPEG_Q_REG_Q_0_31_POS)
#define MJPEG_Q_REG_Q_0_31_UMSK (~(((1U << MJPEG_Q_REG_Q_0_31_LEN) - 1) << MJPEG_Q_REG_Q_0_31_POS))

/* 0x464 : mjpeg_q_param_32 */
#define MJPEG_Q_PARAM_32_OFFSET (0x464)
#define MJPEG_Q_REG_Q_0_32      MJPEG_Q_REG_Q_0_32
#define MJPEG_Q_REG_Q_0_32_POS  (0U)
#define MJPEG_Q_REG_Q_0_32_LEN  (12U)
#define MJPEG_Q_REG_Q_0_32_MSK  (((1U << MJPEG_Q_REG_Q_0_32_LEN) - 1) << MJPEG_Q_REG_Q_0_32_POS)
#define MJPEG_Q_REG_Q_0_32_UMSK (~(((1U << MJPEG_Q_REG_Q_0_32_LEN) - 1) << MJPEG_Q_REG_Q_0_32_POS))
#define MJPEG_Q_REG_Q_0_33      MJPEG_Q_REG_Q_0_33
#define MJPEG_Q_REG_Q_0_33_POS  (16U)
#define MJPEG_Q_REG_Q_0_33_LEN  (12U)
#define MJPEG_Q_REG_Q_0_33_MSK  (((1U << MJPEG_Q_REG_Q_0_33_LEN) - 1) << MJPEG_Q_REG_Q_0_33_POS)
#define MJPEG_Q_REG_Q_0_33_UMSK (~(((1U << MJPEG_Q_REG_Q_0_33_LEN) - 1) << MJPEG_Q_REG_Q_0_33_POS))

/* 0x468 : mjpeg_q_param_34 */
#define MJPEG_Q_PARAM_34_OFFSET (0x468)
#define MJPEG_Q_REG_Q_0_34      MJPEG_Q_REG_Q_0_34
#define MJPEG_Q_REG_Q_0_34_POS  (0U)
#define MJPEG_Q_REG_Q_0_34_LEN  (12U)
#define MJPEG_Q_REG_Q_0_34_MSK  (((1U << MJPEG_Q_REG_Q_0_34_LEN) - 1) << MJPEG_Q_REG_Q_0_34_POS)
#define MJPEG_Q_REG_Q_0_34_UMSK (~(((1U << MJPEG_Q_REG_Q_0_34_LEN) - 1) << MJPEG_Q_REG_Q_0_34_POS))
#define MJPEG_Q_REG_Q_0_35      MJPEG_Q_REG_Q_0_35
#define MJPEG_Q_REG_Q_0_35_POS  (16U)
#define MJPEG_Q_REG_Q_0_35_LEN  (12U)
#define MJPEG_Q_REG_Q_0_35_MSK  (((1U << MJPEG_Q_REG_Q_0_35_LEN) - 1) << MJPEG_Q_REG_Q_0_35_POS)
#define MJPEG_Q_REG_Q_0_35_UMSK (~(((1U << MJPEG_Q_REG_Q_0_35_LEN) - 1) << MJPEG_Q_REG_Q_0_35_POS))

/* 0x46C : mjpeg_q_param_36 */
#define MJPEG_Q_PARAM_36_OFFSET (0x46C)
#define MJPEG_Q_REG_Q_0_36      MJPEG_Q_REG_Q_0_36
#define MJPEG_Q_REG_Q_0_36_POS  (0U)
#define MJPEG_Q_REG_Q_0_36_LEN  (12U)
#define MJPEG_Q_REG_Q_0_36_MSK  (((1U << MJPEG_Q_REG_Q_0_36_LEN) - 1) << MJPEG_Q_REG_Q_0_36_POS)
#define MJPEG_Q_REG_Q_0_36_UMSK (~(((1U << MJPEG_Q_REG_Q_0_36_LEN) - 1) << MJPEG_Q_REG_Q_0_36_POS))
#define MJPEG_Q_REG_Q_0_37      MJPEG_Q_REG_Q_0_37
#define MJPEG_Q_REG_Q_0_37_POS  (16U)
#define MJPEG_Q_REG_Q_0_37_LEN  (12U)
#define MJPEG_Q_REG_Q_0_37_MSK  (((1U << MJPEG_Q_REG_Q_0_37_LEN) - 1) << MJPEG_Q_REG_Q_0_37_POS)
#define MJPEG_Q_REG_Q_0_37_UMSK (~(((1U << MJPEG_Q_REG_Q_0_37_LEN) - 1) << MJPEG_Q_REG_Q_0_37_POS))

/* 0x470 : mjpeg_q_param_38 */
#define MJPEG_Q_PARAM_38_OFFSET (0x470)
#define MJPEG_Q_REG_Q_0_38      MJPEG_Q_REG_Q_0_38
#define MJPEG_Q_REG_Q_0_38_POS  (0U)
#define MJPEG_Q_REG_Q_0_38_LEN  (12U)
#define MJPEG_Q_REG_Q_0_38_MSK  (((1U << MJPEG_Q_REG_Q_0_38_LEN) - 1) << MJPEG_Q_REG_Q_0_38_POS)
#define MJPEG_Q_REG_Q_0_38_UMSK (~(((1U << MJPEG_Q_REG_Q_0_38_LEN) - 1) << MJPEG_Q_REG_Q_0_38_POS))
#define MJPEG_Q_REG_Q_0_39      MJPEG_Q_REG_Q_0_39
#define MJPEG_Q_REG_Q_0_39_POS  (16U)
#define MJPEG_Q_REG_Q_0_39_LEN  (12U)
#define MJPEG_Q_REG_Q_0_39_MSK  (((1U << MJPEG_Q_REG_Q_0_39_LEN) - 1) << MJPEG_Q_REG_Q_0_39_POS)
#define MJPEG_Q_REG_Q_0_39_UMSK (~(((1U << MJPEG_Q_REG_Q_0_39_LEN) - 1) << MJPEG_Q_REG_Q_0_39_POS))

/* 0x474 : mjpeg_q_param_3a */
#define MJPEG_Q_PARAM_3A_OFFSET (0x474)
#define MJPEG_Q_REG_Q_0_3A      MJPEG_Q_REG_Q_0_3A
#define MJPEG_Q_REG_Q_0_3A_POS  (0U)
#define MJPEG_Q_REG_Q_0_3A_LEN  (12U)
#define MJPEG_Q_REG_Q_0_3A_MSK  (((1U << MJPEG_Q_REG_Q_0_3A_LEN) - 1) << MJPEG_Q_REG_Q_0_3A_POS)
#define MJPEG_Q_REG_Q_0_3A_UMSK (~(((1U << MJPEG_Q_REG_Q_0_3A_LEN) - 1) << MJPEG_Q_REG_Q_0_3A_POS))
#define MJPEG_Q_REG_Q_0_3B      MJPEG_Q_REG_Q_0_3B
#define MJPEG_Q_REG_Q_0_3B_POS  (16U)
#define MJPEG_Q_REG_Q_0_3B_LEN  (12U)
#define MJPEG_Q_REG_Q_0_3B_MSK  (((1U << MJPEG_Q_REG_Q_0_3B_LEN) - 1) << MJPEG_Q_REG_Q_0_3B_POS)
#define MJPEG_Q_REG_Q_0_3B_UMSK (~(((1U << MJPEG_Q_REG_Q_0_3B_LEN) - 1) << MJPEG_Q_REG_Q_0_3B_POS))

/* 0x478 : mjpeg_q_param_3c */
#define MJPEG_Q_PARAM_3C_OFFSET (0x478)
#define MJPEG_Q_REG_Q_0_3C      MJPEG_Q_REG_Q_0_3C
#define MJPEG_Q_REG_Q_0_3C_POS  (0U)
#define MJPEG_Q_REG_Q_0_3C_LEN  (12U)
#define MJPEG_Q_REG_Q_0_3C_MSK  (((1U << MJPEG_Q_REG_Q_0_3C_LEN) - 1) << MJPEG_Q_REG_Q_0_3C_POS)
#define MJPEG_Q_REG_Q_0_3C_UMSK (~(((1U << MJPEG_Q_REG_Q_0_3C_LEN) - 1) << MJPEG_Q_REG_Q_0_3C_POS))
#define MJPEG_Q_REG_Q_0_3D      MJPEG_Q_REG_Q_0_3D
#define MJPEG_Q_REG_Q_0_3D_POS  (16U)
#define MJPEG_Q_REG_Q_0_3D_LEN  (12U)
#define MJPEG_Q_REG_Q_0_3D_MSK  (((1U << MJPEG_Q_REG_Q_0_3D_LEN) - 1) << MJPEG_Q_REG_Q_0_3D_POS)
#define MJPEG_Q_REG_Q_0_3D_UMSK (~(((1U << MJPEG_Q_REG_Q_0_3D_LEN) - 1) << MJPEG_Q_REG_Q_0_3D_POS))

/* 0x47C : mjpeg_q_param_3e */
#define MJPEG_Q_PARAM_3E_OFFSET (0x47C)
#define MJPEG_Q_REG_Q_0_3E      MJPEG_Q_REG_Q_0_3E
#define MJPEG_Q_REG_Q_0_3E_POS  (0U)
#define MJPEG_Q_REG_Q_0_3E_LEN  (12U)
#define MJPEG_Q_REG_Q_0_3E_MSK  (((1U << MJPEG_Q_REG_Q_0_3E_LEN) - 1) << MJPEG_Q_REG_Q_0_3E_POS)
#define MJPEG_Q_REG_Q_0_3E_UMSK (~(((1U << MJPEG_Q_REG_Q_0_3E_LEN) - 1) << MJPEG_Q_REG_Q_0_3E_POS))
#define MJPEG_Q_REG_Q_0_3F      MJPEG_Q_REG_Q_0_3F
#define MJPEG_Q_REG_Q_0_3F_POS  (16U)
#define MJPEG_Q_REG_Q_0_3F_LEN  (12U)
#define MJPEG_Q_REG_Q_0_3F_MSK  (((1U << MJPEG_Q_REG_Q_0_3F_LEN) - 1) << MJPEG_Q_REG_Q_0_3F_POS)
#define MJPEG_Q_REG_Q_0_3F_UMSK (~(((1U << MJPEG_Q_REG_Q_0_3F_LEN) - 1) << MJPEG_Q_REG_Q_0_3F_POS))

/* 0x480 : mjpeg_q_param_40 */
#define MJPEG_Q_PARAM_40_OFFSET (0x480)
#define MJPEG_Q_REG_Q_1_00      MJPEG_Q_REG_Q_1_00
#define MJPEG_Q_REG_Q_1_00_POS  (0U)
#define MJPEG_Q_REG_Q_1_00_LEN  (12U)
#define MJPEG_Q_REG_Q_1_00_MSK  (((1U << MJPEG_Q_REG_Q_1_00_LEN) - 1) << MJPEG_Q_REG_Q_1_00_POS)
#define MJPEG_Q_REG_Q_1_00_UMSK (~(((1U << MJPEG_Q_REG_Q_1_00_LEN) - 1) << MJPEG_Q_REG_Q_1_00_POS))
#define MJPEG_Q_REG_Q_1_01      MJPEG_Q_REG_Q_1_01
#define MJPEG_Q_REG_Q_1_01_POS  (16U)
#define MJPEG_Q_REG_Q_1_01_LEN  (12U)
#define MJPEG_Q_REG_Q_1_01_MSK  (((1U << MJPEG_Q_REG_Q_1_01_LEN) - 1) << MJPEG_Q_REG_Q_1_01_POS)
#define MJPEG_Q_REG_Q_1_01_UMSK (~(((1U << MJPEG_Q_REG_Q_1_01_LEN) - 1) << MJPEG_Q_REG_Q_1_01_POS))

/* 0x484 : mjpeg_q_param_42 */
#define MJPEG_Q_PARAM_42_OFFSET (0x484)
#define MJPEG_Q_REG_Q_1_02      MJPEG_Q_REG_Q_1_02
#define MJPEG_Q_REG_Q_1_02_POS  (0U)
#define MJPEG_Q_REG_Q_1_02_LEN  (12U)
#define MJPEG_Q_REG_Q_1_02_MSK  (((1U << MJPEG_Q_REG_Q_1_02_LEN) - 1) << MJPEG_Q_REG_Q_1_02_POS)
#define MJPEG_Q_REG_Q_1_02_UMSK (~(((1U << MJPEG_Q_REG_Q_1_02_LEN) - 1) << MJPEG_Q_REG_Q_1_02_POS))
#define MJPEG_Q_REG_Q_1_03      MJPEG_Q_REG_Q_1_03
#define MJPEG_Q_REG_Q_1_03_POS  (16U)
#define MJPEG_Q_REG_Q_1_03_LEN  (12U)
#define MJPEG_Q_REG_Q_1_03_MSK  (((1U << MJPEG_Q_REG_Q_1_03_LEN) - 1) << MJPEG_Q_REG_Q_1_03_POS)
#define MJPEG_Q_REG_Q_1_03_UMSK (~(((1U << MJPEG_Q_REG_Q_1_03_LEN) - 1) << MJPEG_Q_REG_Q_1_03_POS))

/* 0x488 : mjpeg_q_param_44 */
#define MJPEG_Q_PARAM_44_OFFSET (0x488)
#define MJPEG_Q_REG_Q_1_04      MJPEG_Q_REG_Q_1_04
#define MJPEG_Q_REG_Q_1_04_POS  (0U)
#define MJPEG_Q_REG_Q_1_04_LEN  (12U)
#define MJPEG_Q_REG_Q_1_04_MSK  (((1U << MJPEG_Q_REG_Q_1_04_LEN) - 1) << MJPEG_Q_REG_Q_1_04_POS)
#define MJPEG_Q_REG_Q_1_04_UMSK (~(((1U << MJPEG_Q_REG_Q_1_04_LEN) - 1) << MJPEG_Q_REG_Q_1_04_POS))
#define MJPEG_Q_REG_Q_1_05      MJPEG_Q_REG_Q_1_05
#define MJPEG_Q_REG_Q_1_05_POS  (16U)
#define MJPEG_Q_REG_Q_1_05_LEN  (12U)
#define MJPEG_Q_REG_Q_1_05_MSK  (((1U << MJPEG_Q_REG_Q_1_05_LEN) - 1) << MJPEG_Q_REG_Q_1_05_POS)
#define MJPEG_Q_REG_Q_1_05_UMSK (~(((1U << MJPEG_Q_REG_Q_1_05_LEN) - 1) << MJPEG_Q_REG_Q_1_05_POS))

/* 0x48C : mjpeg_q_param_46 */
#define MJPEG_Q_PARAM_46_OFFSET (0x48C)
#define MJPEG_Q_REG_Q_1_06      MJPEG_Q_REG_Q_1_06
#define MJPEG_Q_REG_Q_1_06_POS  (0U)
#define MJPEG_Q_REG_Q_1_06_LEN  (12U)
#define MJPEG_Q_REG_Q_1_06_MSK  (((1U << MJPEG_Q_REG_Q_1_06_LEN) - 1) << MJPEG_Q_REG_Q_1_06_POS)
#define MJPEG_Q_REG_Q_1_06_UMSK (~(((1U << MJPEG_Q_REG_Q_1_06_LEN) - 1) << MJPEG_Q_REG_Q_1_06_POS))
#define MJPEG_Q_REG_Q_1_07      MJPEG_Q_REG_Q_1_07
#define MJPEG_Q_REG_Q_1_07_POS  (16U)
#define MJPEG_Q_REG_Q_1_07_LEN  (12U)
#define MJPEG_Q_REG_Q_1_07_MSK  (((1U << MJPEG_Q_REG_Q_1_07_LEN) - 1) << MJPEG_Q_REG_Q_1_07_POS)
#define MJPEG_Q_REG_Q_1_07_UMSK (~(((1U << MJPEG_Q_REG_Q_1_07_LEN) - 1) << MJPEG_Q_REG_Q_1_07_POS))

/* 0x490 : mjpeg_q_param_48 */
#define MJPEG_Q_PARAM_48_OFFSET (0x490)
#define MJPEG_Q_REG_Q_1_08      MJPEG_Q_REG_Q_1_08
#define MJPEG_Q_REG_Q_1_08_POS  (0U)
#define MJPEG_Q_REG_Q_1_08_LEN  (12U)
#define MJPEG_Q_REG_Q_1_08_MSK  (((1U << MJPEG_Q_REG_Q_1_08_LEN) - 1) << MJPEG_Q_REG_Q_1_08_POS)
#define MJPEG_Q_REG_Q_1_08_UMSK (~(((1U << MJPEG_Q_REG_Q_1_08_LEN) - 1) << MJPEG_Q_REG_Q_1_08_POS))
#define MJPEG_Q_REG_Q_1_09      MJPEG_Q_REG_Q_1_09
#define MJPEG_Q_REG_Q_1_09_POS  (16U)
#define MJPEG_Q_REG_Q_1_09_LEN  (12U)
#define MJPEG_Q_REG_Q_1_09_MSK  (((1U << MJPEG_Q_REG_Q_1_09_LEN) - 1) << MJPEG_Q_REG_Q_1_09_POS)
#define MJPEG_Q_REG_Q_1_09_UMSK (~(((1U << MJPEG_Q_REG_Q_1_09_LEN) - 1) << MJPEG_Q_REG_Q_1_09_POS))

/* 0x494 : mjpeg_q_param_4a */
#define MJPEG_Q_PARAM_4A_OFFSET (0x494)
#define MJPEG_Q_REG_Q_1_0A      MJPEG_Q_REG_Q_1_0A
#define MJPEG_Q_REG_Q_1_0A_POS  (0U)
#define MJPEG_Q_REG_Q_1_0A_LEN  (12U)
#define MJPEG_Q_REG_Q_1_0A_MSK  (((1U << MJPEG_Q_REG_Q_1_0A_LEN) - 1) << MJPEG_Q_REG_Q_1_0A_POS)
#define MJPEG_Q_REG_Q_1_0A_UMSK (~(((1U << MJPEG_Q_REG_Q_1_0A_LEN) - 1) << MJPEG_Q_REG_Q_1_0A_POS))
#define MJPEG_Q_REG_Q_1_0B      MJPEG_Q_REG_Q_1_0B
#define MJPEG_Q_REG_Q_1_0B_POS  (16U)
#define MJPEG_Q_REG_Q_1_0B_LEN  (12U)
#define MJPEG_Q_REG_Q_1_0B_MSK  (((1U << MJPEG_Q_REG_Q_1_0B_LEN) - 1) << MJPEG_Q_REG_Q_1_0B_POS)
#define MJPEG_Q_REG_Q_1_0B_UMSK (~(((1U << MJPEG_Q_REG_Q_1_0B_LEN) - 1) << MJPEG_Q_REG_Q_1_0B_POS))

/* 0x498 : mjpeg_q_param_4c */
#define MJPEG_Q_PARAM_4C_OFFSET (0x498)
#define MJPEG_Q_REG_Q_1_0C      MJPEG_Q_REG_Q_1_0C
#define MJPEG_Q_REG_Q_1_0C_POS  (0U)
#define MJPEG_Q_REG_Q_1_0C_LEN  (12U)
#define MJPEG_Q_REG_Q_1_0C_MSK  (((1U << MJPEG_Q_REG_Q_1_0C_LEN) - 1) << MJPEG_Q_REG_Q_1_0C_POS)
#define MJPEG_Q_REG_Q_1_0C_UMSK (~(((1U << MJPEG_Q_REG_Q_1_0C_LEN) - 1) << MJPEG_Q_REG_Q_1_0C_POS))
#define MJPEG_Q_REG_Q_1_0D      MJPEG_Q_REG_Q_1_0D
#define MJPEG_Q_REG_Q_1_0D_POS  (16U)
#define MJPEG_Q_REG_Q_1_0D_LEN  (12U)
#define MJPEG_Q_REG_Q_1_0D_MSK  (((1U << MJPEG_Q_REG_Q_1_0D_LEN) - 1) << MJPEG_Q_REG_Q_1_0D_POS)
#define MJPEG_Q_REG_Q_1_0D_UMSK (~(((1U << MJPEG_Q_REG_Q_1_0D_LEN) - 1) << MJPEG_Q_REG_Q_1_0D_POS))

/* 0x49C : mjpeg_q_param_4e */
#define MJPEG_Q_PARAM_4E_OFFSET (0x49C)
#define MJPEG_Q_REG_Q_1_0E      MJPEG_Q_REG_Q_1_0E
#define MJPEG_Q_REG_Q_1_0E_POS  (0U)
#define MJPEG_Q_REG_Q_1_0E_LEN  (12U)
#define MJPEG_Q_REG_Q_1_0E_MSK  (((1U << MJPEG_Q_REG_Q_1_0E_LEN) - 1) << MJPEG_Q_REG_Q_1_0E_POS)
#define MJPEG_Q_REG_Q_1_0E_UMSK (~(((1U << MJPEG_Q_REG_Q_1_0E_LEN) - 1) << MJPEG_Q_REG_Q_1_0E_POS))
#define MJPEG_Q_REG_Q_1_0F      MJPEG_Q_REG_Q_1_0F
#define MJPEG_Q_REG_Q_1_0F_POS  (16U)
#define MJPEG_Q_REG_Q_1_0F_LEN  (12U)
#define MJPEG_Q_REG_Q_1_0F_MSK  (((1U << MJPEG_Q_REG_Q_1_0F_LEN) - 1) << MJPEG_Q_REG_Q_1_0F_POS)
#define MJPEG_Q_REG_Q_1_0F_UMSK (~(((1U << MJPEG_Q_REG_Q_1_0F_LEN) - 1) << MJPEG_Q_REG_Q_1_0F_POS))

/* 0x4A0 : mjpeg_q_param_50 */
#define MJPEG_Q_PARAM_50_OFFSET (0x4A0)
#define MJPEG_Q_REG_Q_1_10      MJPEG_Q_REG_Q_1_10
#define MJPEG_Q_REG_Q_1_10_POS  (0U)
#define MJPEG_Q_REG_Q_1_10_LEN  (12U)
#define MJPEG_Q_REG_Q_1_10_MSK  (((1U << MJPEG_Q_REG_Q_1_10_LEN) - 1) << MJPEG_Q_REG_Q_1_10_POS)
#define MJPEG_Q_REG_Q_1_10_UMSK (~(((1U << MJPEG_Q_REG_Q_1_10_LEN) - 1) << MJPEG_Q_REG_Q_1_10_POS))
#define MJPEG_Q_REG_Q_1_11      MJPEG_Q_REG_Q_1_11
#define MJPEG_Q_REG_Q_1_11_POS  (16U)
#define MJPEG_Q_REG_Q_1_11_LEN  (12U)
#define MJPEG_Q_REG_Q_1_11_MSK  (((1U << MJPEG_Q_REG_Q_1_11_LEN) - 1) << MJPEG_Q_REG_Q_1_11_POS)
#define MJPEG_Q_REG_Q_1_11_UMSK (~(((1U << MJPEG_Q_REG_Q_1_11_LEN) - 1) << MJPEG_Q_REG_Q_1_11_POS))

/* 0x4A4 : mjpeg_q_param_52 */
#define MJPEG_Q_PARAM_52_OFFSET (0x4A4)
#define MJPEG_Q_REG_Q_1_12      MJPEG_Q_REG_Q_1_12
#define MJPEG_Q_REG_Q_1_12_POS  (0U)
#define MJPEG_Q_REG_Q_1_12_LEN  (12U)
#define MJPEG_Q_REG_Q_1_12_MSK  (((1U << MJPEG_Q_REG_Q_1_12_LEN) - 1) << MJPEG_Q_REG_Q_1_12_POS)
#define MJPEG_Q_REG_Q_1_12_UMSK (~(((1U << MJPEG_Q_REG_Q_1_12_LEN) - 1) << MJPEG_Q_REG_Q_1_12_POS))
#define MJPEG_Q_REG_Q_1_13      MJPEG_Q_REG_Q_1_13
#define MJPEG_Q_REG_Q_1_13_POS  (16U)
#define MJPEG_Q_REG_Q_1_13_LEN  (12U)
#define MJPEG_Q_REG_Q_1_13_MSK  (((1U << MJPEG_Q_REG_Q_1_13_LEN) - 1) << MJPEG_Q_REG_Q_1_13_POS)
#define MJPEG_Q_REG_Q_1_13_UMSK (~(((1U << MJPEG_Q_REG_Q_1_13_LEN) - 1) << MJPEG_Q_REG_Q_1_13_POS))

/* 0x4A8 : mjpeg_q_param_54 */
#define MJPEG_Q_PARAM_54_OFFSET (0x4A8)
#define MJPEG_Q_REG_Q_1_14      MJPEG_Q_REG_Q_1_14
#define MJPEG_Q_REG_Q_1_14_POS  (0U)
#define MJPEG_Q_REG_Q_1_14_LEN  (12U)
#define MJPEG_Q_REG_Q_1_14_MSK  (((1U << MJPEG_Q_REG_Q_1_14_LEN) - 1) << MJPEG_Q_REG_Q_1_14_POS)
#define MJPEG_Q_REG_Q_1_14_UMSK (~(((1U << MJPEG_Q_REG_Q_1_14_LEN) - 1) << MJPEG_Q_REG_Q_1_14_POS))
#define MJPEG_Q_REG_Q_1_15      MJPEG_Q_REG_Q_1_15
#define MJPEG_Q_REG_Q_1_15_POS  (16U)
#define MJPEG_Q_REG_Q_1_15_LEN  (12U)
#define MJPEG_Q_REG_Q_1_15_MSK  (((1U << MJPEG_Q_REG_Q_1_15_LEN) - 1) << MJPEG_Q_REG_Q_1_15_POS)
#define MJPEG_Q_REG_Q_1_15_UMSK (~(((1U << MJPEG_Q_REG_Q_1_15_LEN) - 1) << MJPEG_Q_REG_Q_1_15_POS))

/* 0x4AC : mjpeg_q_param_56 */
#define MJPEG_Q_PARAM_56_OFFSET (0x4AC)
#define MJPEG_Q_REG_Q_1_16      MJPEG_Q_REG_Q_1_16
#define MJPEG_Q_REG_Q_1_16_POS  (0U)
#define MJPEG_Q_REG_Q_1_16_LEN  (12U)
#define MJPEG_Q_REG_Q_1_16_MSK  (((1U << MJPEG_Q_REG_Q_1_16_LEN) - 1) << MJPEG_Q_REG_Q_1_16_POS)
#define MJPEG_Q_REG_Q_1_16_UMSK (~(((1U << MJPEG_Q_REG_Q_1_16_LEN) - 1) << MJPEG_Q_REG_Q_1_16_POS))
#define MJPEG_Q_REG_Q_1_17      MJPEG_Q_REG_Q_1_17
#define MJPEG_Q_REG_Q_1_17_POS  (16U)
#define MJPEG_Q_REG_Q_1_17_LEN  (12U)
#define MJPEG_Q_REG_Q_1_17_MSK  (((1U << MJPEG_Q_REG_Q_1_17_LEN) - 1) << MJPEG_Q_REG_Q_1_17_POS)
#define MJPEG_Q_REG_Q_1_17_UMSK (~(((1U << MJPEG_Q_REG_Q_1_17_LEN) - 1) << MJPEG_Q_REG_Q_1_17_POS))

/* 0x4B0 : mjpeg_q_param_58 */
#define MJPEG_Q_PARAM_58_OFFSET (0x4B0)
#define MJPEG_Q_REG_Q_1_18      MJPEG_Q_REG_Q_1_18
#define MJPEG_Q_REG_Q_1_18_POS  (0U)
#define MJPEG_Q_REG_Q_1_18_LEN  (12U)
#define MJPEG_Q_REG_Q_1_18_MSK  (((1U << MJPEG_Q_REG_Q_1_18_LEN) - 1) << MJPEG_Q_REG_Q_1_18_POS)
#define MJPEG_Q_REG_Q_1_18_UMSK (~(((1U << MJPEG_Q_REG_Q_1_18_LEN) - 1) << MJPEG_Q_REG_Q_1_18_POS))
#define MJPEG_Q_REG_Q_1_19      MJPEG_Q_REG_Q_1_19
#define MJPEG_Q_REG_Q_1_19_POS  (16U)
#define MJPEG_Q_REG_Q_1_19_LEN  (12U)
#define MJPEG_Q_REG_Q_1_19_MSK  (((1U << MJPEG_Q_REG_Q_1_19_LEN) - 1) << MJPEG_Q_REG_Q_1_19_POS)
#define MJPEG_Q_REG_Q_1_19_UMSK (~(((1U << MJPEG_Q_REG_Q_1_19_LEN) - 1) << MJPEG_Q_REG_Q_1_19_POS))

/* 0x4B4 : mjpeg_q_param_5a */
#define MJPEG_Q_PARAM_5A_OFFSET (0x4B4)
#define MJPEG_Q_REG_Q_1_1A      MJPEG_Q_REG_Q_1_1A
#define MJPEG_Q_REG_Q_1_1A_POS  (0U)
#define MJPEG_Q_REG_Q_1_1A_LEN  (12U)
#define MJPEG_Q_REG_Q_1_1A_MSK  (((1U << MJPEG_Q_REG_Q_1_1A_LEN) - 1) << MJPEG_Q_REG_Q_1_1A_POS)
#define MJPEG_Q_REG_Q_1_1A_UMSK (~(((1U << MJPEG_Q_REG_Q_1_1A_LEN) - 1) << MJPEG_Q_REG_Q_1_1A_POS))
#define MJPEG_Q_REG_Q_1_1B      MJPEG_Q_REG_Q_1_1B
#define MJPEG_Q_REG_Q_1_1B_POS  (16U)
#define MJPEG_Q_REG_Q_1_1B_LEN  (12U)
#define MJPEG_Q_REG_Q_1_1B_MSK  (((1U << MJPEG_Q_REG_Q_1_1B_LEN) - 1) << MJPEG_Q_REG_Q_1_1B_POS)
#define MJPEG_Q_REG_Q_1_1B_UMSK (~(((1U << MJPEG_Q_REG_Q_1_1B_LEN) - 1) << MJPEG_Q_REG_Q_1_1B_POS))

/* 0x4B8 : mjpeg_q_param_5c */
#define MJPEG_Q_PARAM_5C_OFFSET (0x4B8)
#define MJPEG_Q_REG_Q_1_1C      MJPEG_Q_REG_Q_1_1C
#define MJPEG_Q_REG_Q_1_1C_POS  (0U)
#define MJPEG_Q_REG_Q_1_1C_LEN  (12U)
#define MJPEG_Q_REG_Q_1_1C_MSK  (((1U << MJPEG_Q_REG_Q_1_1C_LEN) - 1) << MJPEG_Q_REG_Q_1_1C_POS)
#define MJPEG_Q_REG_Q_1_1C_UMSK (~(((1U << MJPEG_Q_REG_Q_1_1C_LEN) - 1) << MJPEG_Q_REG_Q_1_1C_POS))
#define MJPEG_Q_REG_Q_1_1D      MJPEG_Q_REG_Q_1_1D
#define MJPEG_Q_REG_Q_1_1D_POS  (16U)
#define MJPEG_Q_REG_Q_1_1D_LEN  (12U)
#define MJPEG_Q_REG_Q_1_1D_MSK  (((1U << MJPEG_Q_REG_Q_1_1D_LEN) - 1) << MJPEG_Q_REG_Q_1_1D_POS)
#define MJPEG_Q_REG_Q_1_1D_UMSK (~(((1U << MJPEG_Q_REG_Q_1_1D_LEN) - 1) << MJPEG_Q_REG_Q_1_1D_POS))

/* 0x4BC : mjpeg_q_param_5e */
#define MJPEG_Q_PARAM_5E_OFFSET (0x4BC)
#define MJPEG_Q_REG_Q_1_1E      MJPEG_Q_REG_Q_1_1E
#define MJPEG_Q_REG_Q_1_1E_POS  (0U)
#define MJPEG_Q_REG_Q_1_1E_LEN  (12U)
#define MJPEG_Q_REG_Q_1_1E_MSK  (((1U << MJPEG_Q_REG_Q_1_1E_LEN) - 1) << MJPEG_Q_REG_Q_1_1E_POS)
#define MJPEG_Q_REG_Q_1_1E_UMSK (~(((1U << MJPEG_Q_REG_Q_1_1E_LEN) - 1) << MJPEG_Q_REG_Q_1_1E_POS))
#define MJPEG_Q_REG_Q_1_1F      MJPEG_Q_REG_Q_1_1F
#define MJPEG_Q_REG_Q_1_1F_POS  (16U)
#define MJPEG_Q_REG_Q_1_1F_LEN  (12U)
#define MJPEG_Q_REG_Q_1_1F_MSK  (((1U << MJPEG_Q_REG_Q_1_1F_LEN) - 1) << MJPEG_Q_REG_Q_1_1F_POS)
#define MJPEG_Q_REG_Q_1_1F_UMSK (~(((1U << MJPEG_Q_REG_Q_1_1F_LEN) - 1) << MJPEG_Q_REG_Q_1_1F_POS))

/* 0x4C0 : mjpeg_q_param_60 */
#define MJPEG_Q_PARAM_60_OFFSET (0x4C0)
#define MJPEG_Q_REG_Q_1_20      MJPEG_Q_REG_Q_1_20
#define MJPEG_Q_REG_Q_1_20_POS  (0U)
#define MJPEG_Q_REG_Q_1_20_LEN  (12U)
#define MJPEG_Q_REG_Q_1_20_MSK  (((1U << MJPEG_Q_REG_Q_1_20_LEN) - 1) << MJPEG_Q_REG_Q_1_20_POS)
#define MJPEG_Q_REG_Q_1_20_UMSK (~(((1U << MJPEG_Q_REG_Q_1_20_LEN) - 1) << MJPEG_Q_REG_Q_1_20_POS))
#define MJPEG_Q_REG_Q_1_21      MJPEG_Q_REG_Q_1_21
#define MJPEG_Q_REG_Q_1_21_POS  (16U)
#define MJPEG_Q_REG_Q_1_21_LEN  (12U)
#define MJPEG_Q_REG_Q_1_21_MSK  (((1U << MJPEG_Q_REG_Q_1_21_LEN) - 1) << MJPEG_Q_REG_Q_1_21_POS)
#define MJPEG_Q_REG_Q_1_21_UMSK (~(((1U << MJPEG_Q_REG_Q_1_21_LEN) - 1) << MJPEG_Q_REG_Q_1_21_POS))

/* 0x4C4 : mjpeg_q_param_62 */
#define MJPEG_Q_PARAM_62_OFFSET (0x4C4)
#define MJPEG_Q_REG_Q_1_22      MJPEG_Q_REG_Q_1_22
#define MJPEG_Q_REG_Q_1_22_POS  (0U)
#define MJPEG_Q_REG_Q_1_22_LEN  (12U)
#define MJPEG_Q_REG_Q_1_22_MSK  (((1U << MJPEG_Q_REG_Q_1_22_LEN) - 1) << MJPEG_Q_REG_Q_1_22_POS)
#define MJPEG_Q_REG_Q_1_22_UMSK (~(((1U << MJPEG_Q_REG_Q_1_22_LEN) - 1) << MJPEG_Q_REG_Q_1_22_POS))
#define MJPEG_Q_REG_Q_1_23      MJPEG_Q_REG_Q_1_23
#define MJPEG_Q_REG_Q_1_23_POS  (16U)
#define MJPEG_Q_REG_Q_1_23_LEN  (12U)
#define MJPEG_Q_REG_Q_1_23_MSK  (((1U << MJPEG_Q_REG_Q_1_23_LEN) - 1) << MJPEG_Q_REG_Q_1_23_POS)
#define MJPEG_Q_REG_Q_1_23_UMSK (~(((1U << MJPEG_Q_REG_Q_1_23_LEN) - 1) << MJPEG_Q_REG_Q_1_23_POS))

/* 0x4C8 : mjpeg_q_param_64 */
#define MJPEG_Q_PARAM_64_OFFSET (0x4C8)
#define MJPEG_Q_REG_Q_1_24      MJPEG_Q_REG_Q_1_24
#define MJPEG_Q_REG_Q_1_24_POS  (0U)
#define MJPEG_Q_REG_Q_1_24_LEN  (12U)
#define MJPEG_Q_REG_Q_1_24_MSK  (((1U << MJPEG_Q_REG_Q_1_24_LEN) - 1) << MJPEG_Q_REG_Q_1_24_POS)
#define MJPEG_Q_REG_Q_1_24_UMSK (~(((1U << MJPEG_Q_REG_Q_1_24_LEN) - 1) << MJPEG_Q_REG_Q_1_24_POS))
#define MJPEG_Q_REG_Q_1_25      MJPEG_Q_REG_Q_1_25
#define MJPEG_Q_REG_Q_1_25_POS  (16U)
#define MJPEG_Q_REG_Q_1_25_LEN  (12U)
#define MJPEG_Q_REG_Q_1_25_MSK  (((1U << MJPEG_Q_REG_Q_1_25_LEN) - 1) << MJPEG_Q_REG_Q_1_25_POS)
#define MJPEG_Q_REG_Q_1_25_UMSK (~(((1U << MJPEG_Q_REG_Q_1_25_LEN) - 1) << MJPEG_Q_REG_Q_1_25_POS))

/* 0x4CC : mjpeg_q_param_66 */
#define MJPEG_Q_PARAM_66_OFFSET (0x4CC)
#define MJPEG_Q_REG_Q_1_26      MJPEG_Q_REG_Q_1_26
#define MJPEG_Q_REG_Q_1_26_POS  (0U)
#define MJPEG_Q_REG_Q_1_26_LEN  (12U)
#define MJPEG_Q_REG_Q_1_26_MSK  (((1U << MJPEG_Q_REG_Q_1_26_LEN) - 1) << MJPEG_Q_REG_Q_1_26_POS)
#define MJPEG_Q_REG_Q_1_26_UMSK (~(((1U << MJPEG_Q_REG_Q_1_26_LEN) - 1) << MJPEG_Q_REG_Q_1_26_POS))
#define MJPEG_Q_REG_Q_1_27      MJPEG_Q_REG_Q_1_27
#define MJPEG_Q_REG_Q_1_27_POS  (16U)
#define MJPEG_Q_REG_Q_1_27_LEN  (12U)
#define MJPEG_Q_REG_Q_1_27_MSK  (((1U << MJPEG_Q_REG_Q_1_27_LEN) - 1) << MJPEG_Q_REG_Q_1_27_POS)
#define MJPEG_Q_REG_Q_1_27_UMSK (~(((1U << MJPEG_Q_REG_Q_1_27_LEN) - 1) << MJPEG_Q_REG_Q_1_27_POS))

/* 0x4D0 : mjpeg_q_param_68 */
#define MJPEG_Q_PARAM_68_OFFSET (0x4D0)
#define MJPEG_Q_REG_Q_1_28      MJPEG_Q_REG_Q_1_28
#define MJPEG_Q_REG_Q_1_28_POS  (0U)
#define MJPEG_Q_REG_Q_1_28_LEN  (12U)
#define MJPEG_Q_REG_Q_1_28_MSK  (((1U << MJPEG_Q_REG_Q_1_28_LEN) - 1) << MJPEG_Q_REG_Q_1_28_POS)
#define MJPEG_Q_REG_Q_1_28_UMSK (~(((1U << MJPEG_Q_REG_Q_1_28_LEN) - 1) << MJPEG_Q_REG_Q_1_28_POS))
#define MJPEG_Q_REG_Q_1_29      MJPEG_Q_REG_Q_1_29
#define MJPEG_Q_REG_Q_1_29_POS  (16U)
#define MJPEG_Q_REG_Q_1_29_LEN  (12U)
#define MJPEG_Q_REG_Q_1_29_MSK  (((1U << MJPEG_Q_REG_Q_1_29_LEN) - 1) << MJPEG_Q_REG_Q_1_29_POS)
#define MJPEG_Q_REG_Q_1_29_UMSK (~(((1U << MJPEG_Q_REG_Q_1_29_LEN) - 1) << MJPEG_Q_REG_Q_1_29_POS))

/* 0x4D4 : mjpeg_q_param_6a */
#define MJPEG_Q_PARAM_6A_OFFSET (0x4D4)
#define MJPEG_Q_REG_Q_1_2A      MJPEG_Q_REG_Q_1_2A
#define MJPEG_Q_REG_Q_1_2A_POS  (0U)
#define MJPEG_Q_REG_Q_1_2A_LEN  (12U)
#define MJPEG_Q_REG_Q_1_2A_MSK  (((1U << MJPEG_Q_REG_Q_1_2A_LEN) - 1) << MJPEG_Q_REG_Q_1_2A_POS)
#define MJPEG_Q_REG_Q_1_2A_UMSK (~(((1U << MJPEG_Q_REG_Q_1_2A_LEN) - 1) << MJPEG_Q_REG_Q_1_2A_POS))
#define MJPEG_Q_REG_Q_1_2B      MJPEG_Q_REG_Q_1_2B
#define MJPEG_Q_REG_Q_1_2B_POS  (16U)
#define MJPEG_Q_REG_Q_1_2B_LEN  (12U)
#define MJPEG_Q_REG_Q_1_2B_MSK  (((1U << MJPEG_Q_REG_Q_1_2B_LEN) - 1) << MJPEG_Q_REG_Q_1_2B_POS)
#define MJPEG_Q_REG_Q_1_2B_UMSK (~(((1U << MJPEG_Q_REG_Q_1_2B_LEN) - 1) << MJPEG_Q_REG_Q_1_2B_POS))

/* 0x4D8 : mjpeg_q_param_6c */
#define MJPEG_Q_PARAM_6C_OFFSET (0x4D8)
#define MJPEG_Q_REG_Q_1_2C      MJPEG_Q_REG_Q_1_2C
#define MJPEG_Q_REG_Q_1_2C_POS  (0U)
#define MJPEG_Q_REG_Q_1_2C_LEN  (12U)
#define MJPEG_Q_REG_Q_1_2C_MSK  (((1U << MJPEG_Q_REG_Q_1_2C_LEN) - 1) << MJPEG_Q_REG_Q_1_2C_POS)
#define MJPEG_Q_REG_Q_1_2C_UMSK (~(((1U << MJPEG_Q_REG_Q_1_2C_LEN) - 1) << MJPEG_Q_REG_Q_1_2C_POS))
#define MJPEG_Q_REG_Q_1_2D      MJPEG_Q_REG_Q_1_2D
#define MJPEG_Q_REG_Q_1_2D_POS  (16U)
#define MJPEG_Q_REG_Q_1_2D_LEN  (12U)
#define MJPEG_Q_REG_Q_1_2D_MSK  (((1U << MJPEG_Q_REG_Q_1_2D_LEN) - 1) << MJPEG_Q_REG_Q_1_2D_POS)
#define MJPEG_Q_REG_Q_1_2D_UMSK (~(((1U << MJPEG_Q_REG_Q_1_2D_LEN) - 1) << MJPEG_Q_REG_Q_1_2D_POS))

/* 0x4DC : mjpeg_q_param_6e */
#define MJPEG_Q_PARAM_6E_OFFSET (0x4DC)
#define MJPEG_Q_REG_Q_1_2E      MJPEG_Q_REG_Q_1_2E
#define MJPEG_Q_REG_Q_1_2E_POS  (0U)
#define MJPEG_Q_REG_Q_1_2E_LEN  (12U)
#define MJPEG_Q_REG_Q_1_2E_MSK  (((1U << MJPEG_Q_REG_Q_1_2E_LEN) - 1) << MJPEG_Q_REG_Q_1_2E_POS)
#define MJPEG_Q_REG_Q_1_2E_UMSK (~(((1U << MJPEG_Q_REG_Q_1_2E_LEN) - 1) << MJPEG_Q_REG_Q_1_2E_POS))
#define MJPEG_Q_REG_Q_1_2F      MJPEG_Q_REG_Q_1_2F
#define MJPEG_Q_REG_Q_1_2F_POS  (16U)
#define MJPEG_Q_REG_Q_1_2F_LEN  (12U)
#define MJPEG_Q_REG_Q_1_2F_MSK  (((1U << MJPEG_Q_REG_Q_1_2F_LEN) - 1) << MJPEG_Q_REG_Q_1_2F_POS)
#define MJPEG_Q_REG_Q_1_2F_UMSK (~(((1U << MJPEG_Q_REG_Q_1_2F_LEN) - 1) << MJPEG_Q_REG_Q_1_2F_POS))

/* 0x4E0 : mjpeg_q_param_70 */
#define MJPEG_Q_PARAM_70_OFFSET (0x4E0)
#define MJPEG_Q_REG_Q_1_30      MJPEG_Q_REG_Q_1_30
#define MJPEG_Q_REG_Q_1_30_POS  (0U)
#define MJPEG_Q_REG_Q_1_30_LEN  (12U)
#define MJPEG_Q_REG_Q_1_30_MSK  (((1U << MJPEG_Q_REG_Q_1_30_LEN) - 1) << MJPEG_Q_REG_Q_1_30_POS)
#define MJPEG_Q_REG_Q_1_30_UMSK (~(((1U << MJPEG_Q_REG_Q_1_30_LEN) - 1) << MJPEG_Q_REG_Q_1_30_POS))
#define MJPEG_Q_REG_Q_1_31      MJPEG_Q_REG_Q_1_31
#define MJPEG_Q_REG_Q_1_31_POS  (16U)
#define MJPEG_Q_REG_Q_1_31_LEN  (12U)
#define MJPEG_Q_REG_Q_1_31_MSK  (((1U << MJPEG_Q_REG_Q_1_31_LEN) - 1) << MJPEG_Q_REG_Q_1_31_POS)
#define MJPEG_Q_REG_Q_1_31_UMSK (~(((1U << MJPEG_Q_REG_Q_1_31_LEN) - 1) << MJPEG_Q_REG_Q_1_31_POS))

/* 0x4E4 : mjpeg_q_param_72 */
#define MJPEG_Q_PARAM_72_OFFSET (0x4E4)
#define MJPEG_Q_REG_Q_1_32      MJPEG_Q_REG_Q_1_32
#define MJPEG_Q_REG_Q_1_32_POS  (0U)
#define MJPEG_Q_REG_Q_1_32_LEN  (12U)
#define MJPEG_Q_REG_Q_1_32_MSK  (((1U << MJPEG_Q_REG_Q_1_32_LEN) - 1) << MJPEG_Q_REG_Q_1_32_POS)
#define MJPEG_Q_REG_Q_1_32_UMSK (~(((1U << MJPEG_Q_REG_Q_1_32_LEN) - 1) << MJPEG_Q_REG_Q_1_32_POS))
#define MJPEG_Q_REG_Q_1_33      MJPEG_Q_REG_Q_1_33
#define MJPEG_Q_REG_Q_1_33_POS  (16U)
#define MJPEG_Q_REG_Q_1_33_LEN  (12U)
#define MJPEG_Q_REG_Q_1_33_MSK  (((1U << MJPEG_Q_REG_Q_1_33_LEN) - 1) << MJPEG_Q_REG_Q_1_33_POS)
#define MJPEG_Q_REG_Q_1_33_UMSK (~(((1U << MJPEG_Q_REG_Q_1_33_LEN) - 1) << MJPEG_Q_REG_Q_1_33_POS))

/* 0x4E8 : mjpeg_q_param_74 */
#define MJPEG_Q_PARAM_74_OFFSET (0x4E8)
#define MJPEG_Q_REG_Q_1_34      MJPEG_Q_REG_Q_1_34
#define MJPEG_Q_REG_Q_1_34_POS  (0U)
#define MJPEG_Q_REG_Q_1_34_LEN  (12U)
#define MJPEG_Q_REG_Q_1_34_MSK  (((1U << MJPEG_Q_REG_Q_1_34_LEN) - 1) << MJPEG_Q_REG_Q_1_34_POS)
#define MJPEG_Q_REG_Q_1_34_UMSK (~(((1U << MJPEG_Q_REG_Q_1_34_LEN) - 1) << MJPEG_Q_REG_Q_1_34_POS))
#define MJPEG_Q_REG_Q_1_35      MJPEG_Q_REG_Q_1_35
#define MJPEG_Q_REG_Q_1_35_POS  (16U)
#define MJPEG_Q_REG_Q_1_35_LEN  (12U)
#define MJPEG_Q_REG_Q_1_35_MSK  (((1U << MJPEG_Q_REG_Q_1_35_LEN) - 1) << MJPEG_Q_REG_Q_1_35_POS)
#define MJPEG_Q_REG_Q_1_35_UMSK (~(((1U << MJPEG_Q_REG_Q_1_35_LEN) - 1) << MJPEG_Q_REG_Q_1_35_POS))

/* 0x4EC : mjpeg_q_param_76 */
#define MJPEG_Q_PARAM_76_OFFSET (0x4EC)
#define MJPEG_Q_REG_Q_1_36      MJPEG_Q_REG_Q_1_36
#define MJPEG_Q_REG_Q_1_36_POS  (0U)
#define MJPEG_Q_REG_Q_1_36_LEN  (12U)
#define MJPEG_Q_REG_Q_1_36_MSK  (((1U << MJPEG_Q_REG_Q_1_36_LEN) - 1) << MJPEG_Q_REG_Q_1_36_POS)
#define MJPEG_Q_REG_Q_1_36_UMSK (~(((1U << MJPEG_Q_REG_Q_1_36_LEN) - 1) << MJPEG_Q_REG_Q_1_36_POS))
#define MJPEG_Q_REG_Q_1_37      MJPEG_Q_REG_Q_1_37
#define MJPEG_Q_REG_Q_1_37_POS  (16U)
#define MJPEG_Q_REG_Q_1_37_LEN  (12U)
#define MJPEG_Q_REG_Q_1_37_MSK  (((1U << MJPEG_Q_REG_Q_1_37_LEN) - 1) << MJPEG_Q_REG_Q_1_37_POS)
#define MJPEG_Q_REG_Q_1_37_UMSK (~(((1U << MJPEG_Q_REG_Q_1_37_LEN) - 1) << MJPEG_Q_REG_Q_1_37_POS))

/* 0x4F0 : mjpeg_q_param_78 */
#define MJPEG_Q_PARAM_78_OFFSET (0x4F0)
#define MJPEG_Q_REG_Q_1_38      MJPEG_Q_REG_Q_1_38
#define MJPEG_Q_REG_Q_1_38_POS  (0U)
#define MJPEG_Q_REG_Q_1_38_LEN  (12U)
#define MJPEG_Q_REG_Q_1_38_MSK  (((1U << MJPEG_Q_REG_Q_1_38_LEN) - 1) << MJPEG_Q_REG_Q_1_38_POS)
#define MJPEG_Q_REG_Q_1_38_UMSK (~(((1U << MJPEG_Q_REG_Q_1_38_LEN) - 1) << MJPEG_Q_REG_Q_1_38_POS))
#define MJPEG_Q_REG_Q_1_39      MJPEG_Q_REG_Q_1_39
#define MJPEG_Q_REG_Q_1_39_POS  (16U)
#define MJPEG_Q_REG_Q_1_39_LEN  (12U)
#define MJPEG_Q_REG_Q_1_39_MSK  (((1U << MJPEG_Q_REG_Q_1_39_LEN) - 1) << MJPEG_Q_REG_Q_1_39_POS)
#define MJPEG_Q_REG_Q_1_39_UMSK (~(((1U << MJPEG_Q_REG_Q_1_39_LEN) - 1) << MJPEG_Q_REG_Q_1_39_POS))

/* 0x4F4 : mjpeg_q_param_7a */
#define MJPEG_Q_PARAM_7A_OFFSET (0x4F4)
#define MJPEG_Q_REG_Q_1_3A      MJPEG_Q_REG_Q_1_3A
#define MJPEG_Q_REG_Q_1_3A_POS  (0U)
#define MJPEG_Q_REG_Q_1_3A_LEN  (12U)
#define MJPEG_Q_REG_Q_1_3A_MSK  (((1U << MJPEG_Q_REG_Q_1_3A_LEN) - 1) << MJPEG_Q_REG_Q_1_3A_POS)
#define MJPEG_Q_REG_Q_1_3A_UMSK (~(((1U << MJPEG_Q_REG_Q_1_3A_LEN) - 1) << MJPEG_Q_REG_Q_1_3A_POS))
#define MJPEG_Q_REG_Q_1_3B      MJPEG_Q_REG_Q_1_3B
#define MJPEG_Q_REG_Q_1_3B_POS  (16U)
#define MJPEG_Q_REG_Q_1_3B_LEN  (12U)
#define MJPEG_Q_REG_Q_1_3B_MSK  (((1U << MJPEG_Q_REG_Q_1_3B_LEN) - 1) << MJPEG_Q_REG_Q_1_3B_POS)
#define MJPEG_Q_REG_Q_1_3B_UMSK (~(((1U << MJPEG_Q_REG_Q_1_3B_LEN) - 1) << MJPEG_Q_REG_Q_1_3B_POS))

/* 0x4F8 : mjpeg_q_param_7c */
#define MJPEG_Q_PARAM_7C_OFFSET (0x4F8)
#define MJPEG_Q_REG_Q_1_3C      MJPEG_Q_REG_Q_1_3C
#define MJPEG_Q_REG_Q_1_3C_POS  (0U)
#define MJPEG_Q_REG_Q_1_3C_LEN  (12U)
#define MJPEG_Q_REG_Q_1_3C_MSK  (((1U << MJPEG_Q_REG_Q_1_3C_LEN) - 1) << MJPEG_Q_REG_Q_1_3C_POS)
#define MJPEG_Q_REG_Q_1_3C_UMSK (~(((1U << MJPEG_Q_REG_Q_1_3C_LEN) - 1) << MJPEG_Q_REG_Q_1_3C_POS))
#define MJPEG_Q_REG_Q_1_3D      MJPEG_Q_REG_Q_1_3D
#define MJPEG_Q_REG_Q_1_3D_POS  (16U)
#define MJPEG_Q_REG_Q_1_3D_LEN  (12U)
#define MJPEG_Q_REG_Q_1_3D_MSK  (((1U << MJPEG_Q_REG_Q_1_3D_LEN) - 1) << MJPEG_Q_REG_Q_1_3D_POS)
#define MJPEG_Q_REG_Q_1_3D_UMSK (~(((1U << MJPEG_Q_REG_Q_1_3D_LEN) - 1) << MJPEG_Q_REG_Q_1_3D_POS))

/* 0x4FC : mjpeg_q_param_7e */
#define MJPEG_Q_PARAM_7E_OFFSET (0x4FC)
#define MJPEG_Q_REG_Q_1_3E      MJPEG_Q_REG_Q_1_3E
#define MJPEG_Q_REG_Q_1_3E_POS  (0U)
#define MJPEG_Q_REG_Q_1_3E_LEN  (12U)
#define MJPEG_Q_REG_Q_1_3E_MSK  (((1U << MJPEG_Q_REG_Q_1_3E_LEN) - 1) << MJPEG_Q_REG_Q_1_3E_POS)
#define MJPEG_Q_REG_Q_1_3E_UMSK (~(((1U << MJPEG_Q_REG_Q_1_3E_LEN) - 1) << MJPEG_Q_REG_Q_1_3E_POS))
#define MJPEG_Q_REG_Q_1_3F      MJPEG_Q_REG_Q_1_3F
#define MJPEG_Q_REG_Q_1_3F_POS  (16U)
#define MJPEG_Q_REG_Q_1_3F_LEN  (12U)
#define MJPEG_Q_REG_Q_1_3F_MSK  (((1U << MJPEG_Q_REG_Q_1_3F_LEN) - 1) << MJPEG_Q_REG_Q_1_3F_POS)
#define MJPEG_Q_REG_Q_1_3F_UMSK (~(((1U << MJPEG_Q_REG_Q_1_3F_LEN) - 1) << MJPEG_Q_REG_Q_1_3F_POS))

struct mjpeg_q_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[1024];

    /* 0x400 : mjpeg_q_param_00 */
    union {
        struct {
            uint32_t reg_q_0_00     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_01     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_00;

    /* 0x404 : mjpeg_q_param_02 */
    union {
        struct {
            uint32_t reg_q_0_02     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_03     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_02;

    /* 0x408 : mjpeg_q_param_04 */
    union {
        struct {
            uint32_t reg_q_0_04     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_05     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_04;

    /* 0x40C : mjpeg_q_param_06 */
    union {
        struct {
            uint32_t reg_q_0_06     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_07     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_06;

    /* 0x410 : mjpeg_q_param_08 */
    union {
        struct {
            uint32_t reg_q_0_08     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_09     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_08;

    /* 0x414 : mjpeg_q_param_0a */
    union {
        struct {
            uint32_t reg_q_0_0a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_0b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_0a;

    /* 0x418 : mjpeg_q_param_0c */
    union {
        struct {
            uint32_t reg_q_0_0c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_0d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_0c;

    /* 0x41C : mjpeg_q_param_0e */
    union {
        struct {
            uint32_t reg_q_0_0e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_0f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_0e;

    /* 0x420 : mjpeg_q_param_10 */
    union {
        struct {
            uint32_t reg_q_0_10     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_11     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_10;

    /* 0x424 : mjpeg_q_param_12 */
    union {
        struct {
            uint32_t reg_q_0_12     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_13     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_12;

    /* 0x428 : mjpeg_q_param_14 */
    union {
        struct {
            uint32_t reg_q_0_14     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_15     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_14;

    /* 0x42C : mjpeg_q_param_16 */
    union {
        struct {
            uint32_t reg_q_0_16     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_17     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_16;

    /* 0x430 : mjpeg_q_param_18 */
    union {
        struct {
            uint32_t reg_q_0_18     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_19     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_18;

    /* 0x434 : mjpeg_q_param_1a */
    union {
        struct {
            uint32_t reg_q_0_1a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_1b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_1a;

    /* 0x438 : mjpeg_q_param_1c */
    union {
        struct {
            uint32_t reg_q_0_1c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_1d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_1c;

    /* 0x43C : mjpeg_q_param_1e */
    union {
        struct {
            uint32_t reg_q_0_1e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_1f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_1e;

    /* 0x440 : mjpeg_q_param_20 */
    union {
        struct {
            uint32_t reg_q_0_20     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_21     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_20;

    /* 0x444 : mjpeg_q_param_22 */
    union {
        struct {
            uint32_t reg_q_0_22     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_23     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_22;

    /* 0x448 : mjpeg_q_param_24 */
    union {
        struct {
            uint32_t reg_q_0_24     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_25     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_24;

    /* 0x44C : mjpeg_q_param_26 */
    union {
        struct {
            uint32_t reg_q_0_26     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_27     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_26;

    /* 0x450 : mjpeg_q_param_28 */
    union {
        struct {
            uint32_t reg_q_0_28     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_29     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_28;

    /* 0x454 : mjpeg_q_param_2a */
    union {
        struct {
            uint32_t reg_q_0_2a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_2b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_2a;

    /* 0x458 : mjpeg_q_param_2c */
    union {
        struct {
            uint32_t reg_q_0_2c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_2d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_2c;

    /* 0x45C : mjpeg_q_param_2e */
    union {
        struct {
            uint32_t reg_q_0_2e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_2f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_2e;

    /* 0x460 : mjpeg_q_param_30 */
    union {
        struct {
            uint32_t reg_q_0_30     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_31     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_30;

    /* 0x464 : mjpeg_q_param_32 */
    union {
        struct {
            uint32_t reg_q_0_32     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_33     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_32;

    /* 0x468 : mjpeg_q_param_34 */
    union {
        struct {
            uint32_t reg_q_0_34     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_35     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_34;

    /* 0x46C : mjpeg_q_param_36 */
    union {
        struct {
            uint32_t reg_q_0_36     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_37     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_36;

    /* 0x470 : mjpeg_q_param_38 */
    union {
        struct {
            uint32_t reg_q_0_38     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_39     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_38;

    /* 0x474 : mjpeg_q_param_3a */
    union {
        struct {
            uint32_t reg_q_0_3a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_3b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_3a;

    /* 0x478 : mjpeg_q_param_3c */
    union {
        struct {
            uint32_t reg_q_0_3c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_3d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_3c;

    /* 0x47C : mjpeg_q_param_3e */
    union {
        struct {
            uint32_t reg_q_0_3e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_0_3f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_3e;

    /* 0x480 : mjpeg_q_param_40 */
    union {
        struct {
            uint32_t reg_q_1_00     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_01     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_40;

    /* 0x484 : mjpeg_q_param_42 */
    union {
        struct {
            uint32_t reg_q_1_02     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_03     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_42;

    /* 0x488 : mjpeg_q_param_44 */
    union {
        struct {
            uint32_t reg_q_1_04     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_05     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_44;

    /* 0x48C : mjpeg_q_param_46 */
    union {
        struct {
            uint32_t reg_q_1_06     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_07     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_46;

    /* 0x490 : mjpeg_q_param_48 */
    union {
        struct {
            uint32_t reg_q_1_08     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_09     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_48;

    /* 0x494 : mjpeg_q_param_4a */
    union {
        struct {
            uint32_t reg_q_1_0a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_0b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_4a;

    /* 0x498 : mjpeg_q_param_4c */
    union {
        struct {
            uint32_t reg_q_1_0c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_0d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_4c;

    /* 0x49C : mjpeg_q_param_4e */
    union {
        struct {
            uint32_t reg_q_1_0e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_0f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_4e;

    /* 0x4A0 : mjpeg_q_param_50 */
    union {
        struct {
            uint32_t reg_q_1_10     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_11     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_50;

    /* 0x4A4 : mjpeg_q_param_52 */
    union {
        struct {
            uint32_t reg_q_1_12     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_13     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_52;

    /* 0x4A8 : mjpeg_q_param_54 */
    union {
        struct {
            uint32_t reg_q_1_14     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_15     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_54;

    /* 0x4AC : mjpeg_q_param_56 */
    union {
        struct {
            uint32_t reg_q_1_16     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_17     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_56;

    /* 0x4B0 : mjpeg_q_param_58 */
    union {
        struct {
            uint32_t reg_q_1_18     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_19     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_58;

    /* 0x4B4 : mjpeg_q_param_5a */
    union {
        struct {
            uint32_t reg_q_1_1a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_1b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_5a;

    /* 0x4B8 : mjpeg_q_param_5c */
    union {
        struct {
            uint32_t reg_q_1_1c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_1d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_5c;

    /* 0x4BC : mjpeg_q_param_5e */
    union {
        struct {
            uint32_t reg_q_1_1e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_1f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_5e;

    /* 0x4C0 : mjpeg_q_param_60 */
    union {
        struct {
            uint32_t reg_q_1_20     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_21     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_60;

    /* 0x4C4 : mjpeg_q_param_62 */
    union {
        struct {
            uint32_t reg_q_1_22     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_23     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_62;

    /* 0x4C8 : mjpeg_q_param_64 */
    union {
        struct {
            uint32_t reg_q_1_24     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_25     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_64;

    /* 0x4CC : mjpeg_q_param_66 */
    union {
        struct {
            uint32_t reg_q_1_26     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_27     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_66;

    /* 0x4D0 : mjpeg_q_param_68 */
    union {
        struct {
            uint32_t reg_q_1_28     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_29     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_68;

    /* 0x4D4 : mjpeg_q_param_6a */
    union {
        struct {
            uint32_t reg_q_1_2a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_2b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_6a;

    /* 0x4D8 : mjpeg_q_param_6c */
    union {
        struct {
            uint32_t reg_q_1_2c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_2d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_6c;

    /* 0x4DC : mjpeg_q_param_6e */
    union {
        struct {
            uint32_t reg_q_1_2e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_2f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_6e;

    /* 0x4E0 : mjpeg_q_param_70 */
    union {
        struct {
            uint32_t reg_q_1_30     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_31     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_70;

    /* 0x4E4 : mjpeg_q_param_72 */
    union {
        struct {
            uint32_t reg_q_1_32     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_33     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_72;

    /* 0x4E8 : mjpeg_q_param_74 */
    union {
        struct {
            uint32_t reg_q_1_34     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_35     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_74;

    /* 0x4EC : mjpeg_q_param_76 */
    union {
        struct {
            uint32_t reg_q_1_36     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_37     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_76;

    /* 0x4F0 : mjpeg_q_param_78 */
    union {
        struct {
            uint32_t reg_q_1_38     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_39     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_78;

    /* 0x4F4 : mjpeg_q_param_7a */
    union {
        struct {
            uint32_t reg_q_1_3a     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_3b     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_7a;

    /* 0x4F8 : mjpeg_q_param_7c */
    union {
        struct {
            uint32_t reg_q_1_3c     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_3d     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_7c;

    /* 0x4FC : mjpeg_q_param_7e */
    union {
        struct {
            uint32_t reg_q_1_3e     : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_q_1_3f     : 12; /* [27:16],        r/w,        0x0 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjpeg_q_param_7e;
};

typedef volatile struct mjpeg_q_reg mjpeg_q_reg_t;

#endif /* __MJPEG_Q_REG_H__ */
