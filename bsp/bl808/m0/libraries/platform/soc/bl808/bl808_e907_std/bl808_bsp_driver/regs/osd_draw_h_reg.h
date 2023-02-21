/**
  ******************************************************************************
  * @file    osd_draw_h_reg.h
  * @version V1.0
  * @date    2021-06-28
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
#ifndef __OSD_DRAW_H_REG_H__
#define __OSD_DRAW_H_REG_H__

#include "bl808.h"

/* 0x4 : draw_partial_config */
#define OSD_DRAW_H_DRAW_PARTIAL_CONFIG_OFFSET (0x4)
#define OSD_DRAW_H_REG_DRAW_EN_H              OSD_DRAW_H_REG_DRAW_EN_H
#define OSD_DRAW_H_REG_DRAW_EN_H_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_EN_H_LEN          (16U)
#define OSD_DRAW_H_REG_DRAW_EN_H_MSK          (((1U << OSD_DRAW_H_REG_DRAW_EN_H_LEN) - 1) << OSD_DRAW_H_REG_DRAW_EN_H_POS)
#define OSD_DRAW_H_REG_DRAW_EN_H_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_EN_H_LEN) - 1) << OSD_DRAW_H_REG_DRAW_EN_H_POS))
#define OSD_DRAW_H_REG_DRAW_TYPE_H            OSD_DRAW_H_REG_DRAW_TYPE_H
#define OSD_DRAW_H_REG_DRAW_TYPE_H_POS        (16U)
#define OSD_DRAW_H_REG_DRAW_TYPE_H_LEN        (16U)
#define OSD_DRAW_H_REG_DRAW_TYPE_H_MSK        (((1U << OSD_DRAW_H_REG_DRAW_TYPE_H_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TYPE_H_POS)
#define OSD_DRAW_H_REG_DRAW_TYPE_H_UMSK       (~(((1U << OSD_DRAW_H_REG_DRAW_TYPE_H_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TYPE_H_POS))

/* 0x8 : draw_partial_yuv_config10 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG10_OFFSET (0x8)
#define OSD_DRAW_H_REG_DRAW_TH_10                   OSD_DRAW_H_REG_DRAW_TH_10
#define OSD_DRAW_H_REG_DRAW_TH_10_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_10_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_10_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_10_POS)
#define OSD_DRAW_H_REG_DRAW_TH_10_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_10_POS))
#define OSD_DRAW_H_REG_DRAW_V_10                    OSD_DRAW_H_REG_DRAW_V_10
#define OSD_DRAW_H_REG_DRAW_V_10_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_10_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_10_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_10_POS)
#define OSD_DRAW_H_REG_DRAW_V_10_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_10_POS))
#define OSD_DRAW_H_REG_DRAW_U_10                    OSD_DRAW_H_REG_DRAW_U_10
#define OSD_DRAW_H_REG_DRAW_U_10_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_10_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_10_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_10_POS)
#define OSD_DRAW_H_REG_DRAW_U_10_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_10_POS))
#define OSD_DRAW_H_REG_DRAW_Y_10                    OSD_DRAW_H_REG_DRAW_Y_10
#define OSD_DRAW_H_REG_DRAW_Y_10_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_10_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_10_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_10_POS)
#define OSD_DRAW_H_REG_DRAW_Y_10_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_10_POS))

/* 0xC : draw_partial_x_config10 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG10_OFFSET (0xC)
#define OSD_DRAW_H_REG_DRAW_X_MIN_10              OSD_DRAW_H_REG_DRAW_X_MIN_10
#define OSD_DRAW_H_REG_DRAW_X_MIN_10_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_10_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_10_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_10_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_10_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_10_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_10              OSD_DRAW_H_REG_DRAW_X_MAX_10
#define OSD_DRAW_H_REG_DRAW_X_MAX_10_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_10_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_10_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_10_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_10_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_10_POS))

/* 0x10 : draw_partial_y_config10 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG10_OFFSET (0x10)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_10              OSD_DRAW_H_REG_DRAW_Y_MIN_10
#define OSD_DRAW_H_REG_DRAW_Y_MIN_10_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_10_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_10_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_10_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_10_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_10_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_10              OSD_DRAW_H_REG_DRAW_Y_MAX_10
#define OSD_DRAW_H_REG_DRAW_Y_MAX_10_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_10_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_10_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_10_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_10_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_10_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_10_POS))

/* 0x14 : draw_partial_yuv_config11 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG11_OFFSET (0x14)
#define OSD_DRAW_H_REG_DRAW_TH_11                   OSD_DRAW_H_REG_DRAW_TH_11
#define OSD_DRAW_H_REG_DRAW_TH_11_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_11_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_11_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_11_POS)
#define OSD_DRAW_H_REG_DRAW_TH_11_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_11_POS))
#define OSD_DRAW_H_REG_DRAW_V_11                    OSD_DRAW_H_REG_DRAW_V_11
#define OSD_DRAW_H_REG_DRAW_V_11_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_11_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_11_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_11_POS)
#define OSD_DRAW_H_REG_DRAW_V_11_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_11_POS))
#define OSD_DRAW_H_REG_DRAW_U_11                    OSD_DRAW_H_REG_DRAW_U_11
#define OSD_DRAW_H_REG_DRAW_U_11_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_11_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_11_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_11_POS)
#define OSD_DRAW_H_REG_DRAW_U_11_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_11_POS))
#define OSD_DRAW_H_REG_DRAW_Y_11                    OSD_DRAW_H_REG_DRAW_Y_11
#define OSD_DRAW_H_REG_DRAW_Y_11_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_11_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_11_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_11_POS)
#define OSD_DRAW_H_REG_DRAW_Y_11_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_11_POS))

/* 0x18 : draw_partial_x_config11 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG11_OFFSET (0x18)
#define OSD_DRAW_H_REG_DRAW_X_MIN_11              OSD_DRAW_H_REG_DRAW_X_MIN_11
#define OSD_DRAW_H_REG_DRAW_X_MIN_11_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_11_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_11_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_11_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_11_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_11_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_11              OSD_DRAW_H_REG_DRAW_X_MAX_11
#define OSD_DRAW_H_REG_DRAW_X_MAX_11_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_11_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_11_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_11_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_11_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_11_POS))

/* 0x1C : draw_partial_y_config11 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG11_OFFSET (0x1C)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_11              OSD_DRAW_H_REG_DRAW_Y_MIN_11
#define OSD_DRAW_H_REG_DRAW_Y_MIN_11_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_11_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_11_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_11_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_11_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_11_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_11              OSD_DRAW_H_REG_DRAW_Y_MAX_11
#define OSD_DRAW_H_REG_DRAW_Y_MAX_11_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_11_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_11_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_11_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_11_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_11_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_11_POS))

/* 0x20 : draw_partial_yuv_config12 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG12_OFFSET (0x20)
#define OSD_DRAW_H_REG_DRAW_TH_12                   OSD_DRAW_H_REG_DRAW_TH_12
#define OSD_DRAW_H_REG_DRAW_TH_12_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_12_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_12_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_12_POS)
#define OSD_DRAW_H_REG_DRAW_TH_12_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_12_POS))
#define OSD_DRAW_H_REG_DRAW_V_12                    OSD_DRAW_H_REG_DRAW_V_12
#define OSD_DRAW_H_REG_DRAW_V_12_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_12_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_12_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_12_POS)
#define OSD_DRAW_H_REG_DRAW_V_12_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_12_POS))
#define OSD_DRAW_H_REG_DRAW_U_12                    OSD_DRAW_H_REG_DRAW_U_12
#define OSD_DRAW_H_REG_DRAW_U_12_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_12_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_12_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_12_POS)
#define OSD_DRAW_H_REG_DRAW_U_12_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_12_POS))
#define OSD_DRAW_H_REG_DRAW_Y_12                    OSD_DRAW_H_REG_DRAW_Y_12
#define OSD_DRAW_H_REG_DRAW_Y_12_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_12_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_12_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_12_POS)
#define OSD_DRAW_H_REG_DRAW_Y_12_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_12_POS))

/* 0x24 : draw_partial_x_config12 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG12_OFFSET (0x24)
#define OSD_DRAW_H_REG_DRAW_X_MIN_12              OSD_DRAW_H_REG_DRAW_X_MIN_12
#define OSD_DRAW_H_REG_DRAW_X_MIN_12_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_12_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_12_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_12_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_12_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_12_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_12              OSD_DRAW_H_REG_DRAW_X_MAX_12
#define OSD_DRAW_H_REG_DRAW_X_MAX_12_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_12_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_12_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_12_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_12_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_12_POS))

/* 0x28 : draw_partial_y_config12 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG12_OFFSET (0x28)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_12              OSD_DRAW_H_REG_DRAW_Y_MIN_12
#define OSD_DRAW_H_REG_DRAW_Y_MIN_12_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_12_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_12_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_12_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_12_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_12_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_12              OSD_DRAW_H_REG_DRAW_Y_MAX_12
#define OSD_DRAW_H_REG_DRAW_Y_MAX_12_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_12_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_12_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_12_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_12_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_12_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_12_POS))

/* 0x2C : draw_partial_yuv_config13 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG13_OFFSET (0x2C)
#define OSD_DRAW_H_REG_DRAW_TH_13                   OSD_DRAW_H_REG_DRAW_TH_13
#define OSD_DRAW_H_REG_DRAW_TH_13_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_13_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_13_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_13_POS)
#define OSD_DRAW_H_REG_DRAW_TH_13_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_13_POS))
#define OSD_DRAW_H_REG_DRAW_V_13                    OSD_DRAW_H_REG_DRAW_V_13
#define OSD_DRAW_H_REG_DRAW_V_13_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_13_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_13_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_13_POS)
#define OSD_DRAW_H_REG_DRAW_V_13_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_13_POS))
#define OSD_DRAW_H_REG_DRAW_U_13                    OSD_DRAW_H_REG_DRAW_U_13
#define OSD_DRAW_H_REG_DRAW_U_13_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_13_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_13_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_13_POS)
#define OSD_DRAW_H_REG_DRAW_U_13_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_13_POS))
#define OSD_DRAW_H_REG_DRAW_Y_13                    OSD_DRAW_H_REG_DRAW_Y_13
#define OSD_DRAW_H_REG_DRAW_Y_13_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_13_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_13_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_13_POS)
#define OSD_DRAW_H_REG_DRAW_Y_13_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_13_POS))

/* 0x30 : draw_partial_x_config13 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG13_OFFSET (0x30)
#define OSD_DRAW_H_REG_DRAW_X_MIN_13              OSD_DRAW_H_REG_DRAW_X_MIN_13
#define OSD_DRAW_H_REG_DRAW_X_MIN_13_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_13_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_13_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_13_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_13_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_13_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_13              OSD_DRAW_H_REG_DRAW_X_MAX_13
#define OSD_DRAW_H_REG_DRAW_X_MAX_13_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_13_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_13_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_13_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_13_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_13_POS))

/* 0x34 : draw_partial_y_config13 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG13_OFFSET (0x34)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_13              OSD_DRAW_H_REG_DRAW_Y_MIN_13
#define OSD_DRAW_H_REG_DRAW_Y_MIN_13_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_13_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_13_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_13_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_13_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_13_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_13              OSD_DRAW_H_REG_DRAW_Y_MAX_13
#define OSD_DRAW_H_REG_DRAW_Y_MAX_13_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_13_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_13_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_13_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_13_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_13_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_13_POS))

/* 0x38 : draw_partial_yuv_config14 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG14_OFFSET (0x38)
#define OSD_DRAW_H_REG_DRAW_TH_14                   OSD_DRAW_H_REG_DRAW_TH_14
#define OSD_DRAW_H_REG_DRAW_TH_14_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_14_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_14_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_14_POS)
#define OSD_DRAW_H_REG_DRAW_TH_14_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_14_POS))
#define OSD_DRAW_H_REG_DRAW_V_14                    OSD_DRAW_H_REG_DRAW_V_14
#define OSD_DRAW_H_REG_DRAW_V_14_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_14_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_14_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_14_POS)
#define OSD_DRAW_H_REG_DRAW_V_14_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_14_POS))
#define OSD_DRAW_H_REG_DRAW_U_14                    OSD_DRAW_H_REG_DRAW_U_14
#define OSD_DRAW_H_REG_DRAW_U_14_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_14_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_14_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_14_POS)
#define OSD_DRAW_H_REG_DRAW_U_14_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_14_POS))
#define OSD_DRAW_H_REG_DRAW_Y_14                    OSD_DRAW_H_REG_DRAW_Y_14
#define OSD_DRAW_H_REG_DRAW_Y_14_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_14_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_14_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_14_POS)
#define OSD_DRAW_H_REG_DRAW_Y_14_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_14_POS))

/* 0x3C : draw_partial_x_config14 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG14_OFFSET (0x3C)
#define OSD_DRAW_H_REG_DRAW_X_MIN_14              OSD_DRAW_H_REG_DRAW_X_MIN_14
#define OSD_DRAW_H_REG_DRAW_X_MIN_14_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_14_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_14_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_14_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_14_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_14_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_14              OSD_DRAW_H_REG_DRAW_X_MAX_14
#define OSD_DRAW_H_REG_DRAW_X_MAX_14_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_14_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_14_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_14_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_14_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_14_POS))

/* 0x40 : draw_partial_y_config14 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG14_OFFSET (0x40)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_14              OSD_DRAW_H_REG_DRAW_Y_MIN_14
#define OSD_DRAW_H_REG_DRAW_Y_MIN_14_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_14_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_14_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_14_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_14_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_14_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_14              OSD_DRAW_H_REG_DRAW_Y_MAX_14
#define OSD_DRAW_H_REG_DRAW_Y_MAX_14_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_14_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_14_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_14_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_14_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_14_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_14_POS))

/* 0x44 : draw_partial_yuv_config15 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG15_OFFSET (0x44)
#define OSD_DRAW_H_REG_DRAW_TH_15                   OSD_DRAW_H_REG_DRAW_TH_15
#define OSD_DRAW_H_REG_DRAW_TH_15_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_15_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_15_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_15_POS)
#define OSD_DRAW_H_REG_DRAW_TH_15_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_15_POS))
#define OSD_DRAW_H_REG_DRAW_V_15                    OSD_DRAW_H_REG_DRAW_V_15
#define OSD_DRAW_H_REG_DRAW_V_15_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_15_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_15_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_15_POS)
#define OSD_DRAW_H_REG_DRAW_V_15_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_15_POS))
#define OSD_DRAW_H_REG_DRAW_U_15                    OSD_DRAW_H_REG_DRAW_U_15
#define OSD_DRAW_H_REG_DRAW_U_15_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_15_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_15_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_15_POS)
#define OSD_DRAW_H_REG_DRAW_U_15_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_15_POS))
#define OSD_DRAW_H_REG_DRAW_Y_15                    OSD_DRAW_H_REG_DRAW_Y_15
#define OSD_DRAW_H_REG_DRAW_Y_15_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_15_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_15_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_15_POS)
#define OSD_DRAW_H_REG_DRAW_Y_15_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_15_POS))

/* 0x48 : draw_partial_x_config15 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG15_OFFSET (0x48)
#define OSD_DRAW_H_REG_DRAW_X_MIN_15              OSD_DRAW_H_REG_DRAW_X_MIN_15
#define OSD_DRAW_H_REG_DRAW_X_MIN_15_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_15_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_15_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_15_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_15_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_15_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_15              OSD_DRAW_H_REG_DRAW_X_MAX_15
#define OSD_DRAW_H_REG_DRAW_X_MAX_15_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_15_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_15_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_15_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_15_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_15_POS))

/* 0x4C : draw_partial_y_config15 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG15_OFFSET (0x4C)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_15              OSD_DRAW_H_REG_DRAW_Y_MIN_15
#define OSD_DRAW_H_REG_DRAW_Y_MIN_15_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_15_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_15_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_15_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_15_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_15_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_15              OSD_DRAW_H_REG_DRAW_Y_MAX_15
#define OSD_DRAW_H_REG_DRAW_Y_MAX_15_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_15_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_15_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_15_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_15_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_15_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_15_POS))

/* 0x50 : draw_partial_yuv_config16 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG16_OFFSET (0x50)
#define OSD_DRAW_H_REG_DRAW_TH_16                   OSD_DRAW_H_REG_DRAW_TH_16
#define OSD_DRAW_H_REG_DRAW_TH_16_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_16_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_16_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_16_POS)
#define OSD_DRAW_H_REG_DRAW_TH_16_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_16_POS))
#define OSD_DRAW_H_REG_DRAW_V_16                    OSD_DRAW_H_REG_DRAW_V_16
#define OSD_DRAW_H_REG_DRAW_V_16_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_16_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_16_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_16_POS)
#define OSD_DRAW_H_REG_DRAW_V_16_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_16_POS))
#define OSD_DRAW_H_REG_DRAW_U_16                    OSD_DRAW_H_REG_DRAW_U_16
#define OSD_DRAW_H_REG_DRAW_U_16_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_16_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_16_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_16_POS)
#define OSD_DRAW_H_REG_DRAW_U_16_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_16_POS))
#define OSD_DRAW_H_REG_DRAW_Y_16                    OSD_DRAW_H_REG_DRAW_Y_16
#define OSD_DRAW_H_REG_DRAW_Y_16_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_16_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_16_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_16_POS)
#define OSD_DRAW_H_REG_DRAW_Y_16_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_16_POS))

/* 0x54 : draw_partial_x_config16 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG16_OFFSET (0x54)
#define OSD_DRAW_H_REG_DRAW_X_MIN_16              OSD_DRAW_H_REG_DRAW_X_MIN_16
#define OSD_DRAW_H_REG_DRAW_X_MIN_16_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_16_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_16_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_16_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_16_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_16_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_16              OSD_DRAW_H_REG_DRAW_X_MAX_16
#define OSD_DRAW_H_REG_DRAW_X_MAX_16_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_16_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_16_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_16_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_16_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_16_POS))

/* 0x58 : draw_partial_y_config16 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG16_OFFSET (0x58)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_16              OSD_DRAW_H_REG_DRAW_Y_MIN_16
#define OSD_DRAW_H_REG_DRAW_Y_MIN_16_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_16_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_16_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_16_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_16_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_16_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_16              OSD_DRAW_H_REG_DRAW_Y_MAX_16
#define OSD_DRAW_H_REG_DRAW_Y_MAX_16_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_16_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_16_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_16_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_16_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_16_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_16_POS))

/* 0x5C : draw_partial_yuv_config17 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG17_OFFSET (0x5C)
#define OSD_DRAW_H_REG_DRAW_TH_17                   OSD_DRAW_H_REG_DRAW_TH_17
#define OSD_DRAW_H_REG_DRAW_TH_17_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_17_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_17_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_17_POS)
#define OSD_DRAW_H_REG_DRAW_TH_17_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_17_POS))
#define OSD_DRAW_H_REG_DRAW_V_17                    OSD_DRAW_H_REG_DRAW_V_17
#define OSD_DRAW_H_REG_DRAW_V_17_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_17_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_17_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_17_POS)
#define OSD_DRAW_H_REG_DRAW_V_17_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_17_POS))
#define OSD_DRAW_H_REG_DRAW_U_17                    OSD_DRAW_H_REG_DRAW_U_17
#define OSD_DRAW_H_REG_DRAW_U_17_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_17_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_17_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_17_POS)
#define OSD_DRAW_H_REG_DRAW_U_17_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_17_POS))
#define OSD_DRAW_H_REG_DRAW_Y_17                    OSD_DRAW_H_REG_DRAW_Y_17
#define OSD_DRAW_H_REG_DRAW_Y_17_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_17_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_17_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_17_POS)
#define OSD_DRAW_H_REG_DRAW_Y_17_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_17_POS))

/* 0x60 : draw_partial_x_config17 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG17_OFFSET (0x60)
#define OSD_DRAW_H_REG_DRAW_X_MIN_17              OSD_DRAW_H_REG_DRAW_X_MIN_17
#define OSD_DRAW_H_REG_DRAW_X_MIN_17_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_17_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_17_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_17_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_17_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_17_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_17              OSD_DRAW_H_REG_DRAW_X_MAX_17
#define OSD_DRAW_H_REG_DRAW_X_MAX_17_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_17_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_17_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_17_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_17_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_17_POS))

/* 0x64 : draw_partial_y_config17 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG17_OFFSET (0x64)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_17              OSD_DRAW_H_REG_DRAW_Y_MIN_17
#define OSD_DRAW_H_REG_DRAW_Y_MIN_17_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_17_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_17_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_17_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_17_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_17_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_17              OSD_DRAW_H_REG_DRAW_Y_MAX_17
#define OSD_DRAW_H_REG_DRAW_Y_MAX_17_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_17_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_17_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_17_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_17_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_17_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_17_POS))

/* 0x68 : draw_partial_yuv_config18 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG18_OFFSET (0x68)
#define OSD_DRAW_H_REG_DRAW_TH_18                   OSD_DRAW_H_REG_DRAW_TH_18
#define OSD_DRAW_H_REG_DRAW_TH_18_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_18_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_18_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_18_POS)
#define OSD_DRAW_H_REG_DRAW_TH_18_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_18_POS))
#define OSD_DRAW_H_REG_DRAW_V_18                    OSD_DRAW_H_REG_DRAW_V_18
#define OSD_DRAW_H_REG_DRAW_V_18_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_18_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_18_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_18_POS)
#define OSD_DRAW_H_REG_DRAW_V_18_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_18_POS))
#define OSD_DRAW_H_REG_DRAW_U_18                    OSD_DRAW_H_REG_DRAW_U_18
#define OSD_DRAW_H_REG_DRAW_U_18_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_18_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_18_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_18_POS)
#define OSD_DRAW_H_REG_DRAW_U_18_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_18_POS))
#define OSD_DRAW_H_REG_DRAW_Y_18                    OSD_DRAW_H_REG_DRAW_Y_18
#define OSD_DRAW_H_REG_DRAW_Y_18_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_18_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_18_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_18_POS)
#define OSD_DRAW_H_REG_DRAW_Y_18_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_18_POS))

/* 0x6C : draw_partial_x_config18 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG18_OFFSET (0x6C)
#define OSD_DRAW_H_REG_DRAW_X_MIN_18              OSD_DRAW_H_REG_DRAW_X_MIN_18
#define OSD_DRAW_H_REG_DRAW_X_MIN_18_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_18_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_18_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_18_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_18_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_18_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_18              OSD_DRAW_H_REG_DRAW_X_MAX_18
#define OSD_DRAW_H_REG_DRAW_X_MAX_18_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_18_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_18_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_18_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_18_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_18_POS))

/* 0x70 : draw_partial_y_config18 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG18_OFFSET (0x70)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_18              OSD_DRAW_H_REG_DRAW_Y_MIN_18
#define OSD_DRAW_H_REG_DRAW_Y_MIN_18_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_18_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_18_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_18_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_18_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_18_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_18              OSD_DRAW_H_REG_DRAW_Y_MAX_18
#define OSD_DRAW_H_REG_DRAW_Y_MAX_18_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_18_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_18_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_18_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_18_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_18_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_18_POS))

/* 0x74 : draw_partial_yuv_config19 */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG19_OFFSET (0x74)
#define OSD_DRAW_H_REG_DRAW_TH_19                   OSD_DRAW_H_REG_DRAW_TH_19
#define OSD_DRAW_H_REG_DRAW_TH_19_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_19_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_19_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_19_POS)
#define OSD_DRAW_H_REG_DRAW_TH_19_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_19_POS))
#define OSD_DRAW_H_REG_DRAW_V_19                    OSD_DRAW_H_REG_DRAW_V_19
#define OSD_DRAW_H_REG_DRAW_V_19_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_19_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_19_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_19_POS)
#define OSD_DRAW_H_REG_DRAW_V_19_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_19_POS))
#define OSD_DRAW_H_REG_DRAW_U_19                    OSD_DRAW_H_REG_DRAW_U_19
#define OSD_DRAW_H_REG_DRAW_U_19_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_19_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_19_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_19_POS)
#define OSD_DRAW_H_REG_DRAW_U_19_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_19_POS))
#define OSD_DRAW_H_REG_DRAW_Y_19                    OSD_DRAW_H_REG_DRAW_Y_19
#define OSD_DRAW_H_REG_DRAW_Y_19_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_19_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_19_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_19_POS)
#define OSD_DRAW_H_REG_DRAW_Y_19_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_19_POS))

/* 0x78 : draw_partial_x_config19 */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG19_OFFSET (0x78)
#define OSD_DRAW_H_REG_DRAW_X_MIN_19              OSD_DRAW_H_REG_DRAW_X_MIN_19
#define OSD_DRAW_H_REG_DRAW_X_MIN_19_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_19_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_19_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_19_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_19_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_19_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_19              OSD_DRAW_H_REG_DRAW_X_MAX_19
#define OSD_DRAW_H_REG_DRAW_X_MAX_19_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_19_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_19_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_19_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_19_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_19_POS))

/* 0x7C : draw_partial_y_config19 */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG19_OFFSET (0x7C)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_19              OSD_DRAW_H_REG_DRAW_Y_MIN_19
#define OSD_DRAW_H_REG_DRAW_Y_MIN_19_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_19_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_19_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_19_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_19_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_19_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_19              OSD_DRAW_H_REG_DRAW_Y_MAX_19
#define OSD_DRAW_H_REG_DRAW_Y_MAX_19_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_19_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_19_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_19_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_19_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_19_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_19_POS))

/* 0x80 : draw_partial_yuv_config1a */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG1A_OFFSET (0x80)
#define OSD_DRAW_H_REG_DRAW_TH_1A                   OSD_DRAW_H_REG_DRAW_TH_1A
#define OSD_DRAW_H_REG_DRAW_TH_1A_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_1A_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_1A_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1A_POS)
#define OSD_DRAW_H_REG_DRAW_TH_1A_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1A_POS))
#define OSD_DRAW_H_REG_DRAW_V_1A                    OSD_DRAW_H_REG_DRAW_V_1A
#define OSD_DRAW_H_REG_DRAW_V_1A_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1A_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1A_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1A_POS)
#define OSD_DRAW_H_REG_DRAW_V_1A_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1A_POS))
#define OSD_DRAW_H_REG_DRAW_U_1A                    OSD_DRAW_H_REG_DRAW_U_1A
#define OSD_DRAW_H_REG_DRAW_U_1A_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_1A_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_1A_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1A_POS)
#define OSD_DRAW_H_REG_DRAW_U_1A_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1A_POS))
#define OSD_DRAW_H_REG_DRAW_Y_1A                    OSD_DRAW_H_REG_DRAW_Y_1A
#define OSD_DRAW_H_REG_DRAW_Y_1A_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_1A_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_1A_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1A_POS)
#define OSD_DRAW_H_REG_DRAW_Y_1A_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1A_POS))

/* 0x84 : draw_partial_x_config1a */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG1A_OFFSET (0x84)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1A              OSD_DRAW_H_REG_DRAW_X_MIN_1A
#define OSD_DRAW_H_REG_DRAW_X_MIN_1A_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1A_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1A_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1A_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1A_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1A_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_1A              OSD_DRAW_H_REG_DRAW_X_MAX_1A
#define OSD_DRAW_H_REG_DRAW_X_MAX_1A_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1A_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1A_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1A_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1A_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1A_POS))

/* 0x88 : draw_partial_y_config1a */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG1A_OFFSET (0x88)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1A              OSD_DRAW_H_REG_DRAW_Y_MIN_1A
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1A_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1A_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1A_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1A_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1A_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1A_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1A              OSD_DRAW_H_REG_DRAW_Y_MAX_1A
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1A_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1A_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1A_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1A_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1A_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1A_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1A_POS))

/* 0x8C : draw_partial_yuv_config1b */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG1B_OFFSET (0x8C)
#define OSD_DRAW_H_REG_DRAW_TH_1B                   OSD_DRAW_H_REG_DRAW_TH_1B
#define OSD_DRAW_H_REG_DRAW_TH_1B_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_1B_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_1B_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1B_POS)
#define OSD_DRAW_H_REG_DRAW_TH_1B_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1B_POS))
#define OSD_DRAW_H_REG_DRAW_V_1B                    OSD_DRAW_H_REG_DRAW_V_1B
#define OSD_DRAW_H_REG_DRAW_V_1B_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1B_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1B_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1B_POS)
#define OSD_DRAW_H_REG_DRAW_V_1B_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1B_POS))
#define OSD_DRAW_H_REG_DRAW_U_1B                    OSD_DRAW_H_REG_DRAW_U_1B
#define OSD_DRAW_H_REG_DRAW_U_1B_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_1B_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_1B_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1B_POS)
#define OSD_DRAW_H_REG_DRAW_U_1B_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1B_POS))
#define OSD_DRAW_H_REG_DRAW_Y_1B                    OSD_DRAW_H_REG_DRAW_Y_1B
#define OSD_DRAW_H_REG_DRAW_Y_1B_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_1B_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_1B_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1B_POS)
#define OSD_DRAW_H_REG_DRAW_Y_1B_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1B_POS))

/* 0x90 : draw_partial_x_config1b */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG1B_OFFSET (0x90)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1B              OSD_DRAW_H_REG_DRAW_X_MIN_1B
#define OSD_DRAW_H_REG_DRAW_X_MIN_1B_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1B_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1B_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1B_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1B_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1B_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_1B              OSD_DRAW_H_REG_DRAW_X_MAX_1B
#define OSD_DRAW_H_REG_DRAW_X_MAX_1B_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1B_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1B_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1B_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1B_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1B_POS))

/* 0x94 : draw_partial_y_config1b */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG1B_OFFSET (0x94)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1B              OSD_DRAW_H_REG_DRAW_Y_MIN_1B
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1B_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1B_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1B_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1B_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1B_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1B_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1B              OSD_DRAW_H_REG_DRAW_Y_MAX_1B
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1B_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1B_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1B_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1B_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1B_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1B_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1B_POS))

/* 0x98 : draw_partial_yuv_config1c */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG1C_OFFSET (0x98)
#define OSD_DRAW_H_REG_DRAW_TH_1C                   OSD_DRAW_H_REG_DRAW_TH_1C
#define OSD_DRAW_H_REG_DRAW_TH_1C_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_1C_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_1C_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1C_POS)
#define OSD_DRAW_H_REG_DRAW_TH_1C_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1C_POS))
#define OSD_DRAW_H_REG_DRAW_V_1C                    OSD_DRAW_H_REG_DRAW_V_1C
#define OSD_DRAW_H_REG_DRAW_V_1C_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1C_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1C_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1C_POS)
#define OSD_DRAW_H_REG_DRAW_V_1C_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1C_POS))
#define OSD_DRAW_H_REG_DRAW_U_1C                    OSD_DRAW_H_REG_DRAW_U_1C
#define OSD_DRAW_H_REG_DRAW_U_1C_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_1C_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_1C_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1C_POS)
#define OSD_DRAW_H_REG_DRAW_U_1C_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1C_POS))
#define OSD_DRAW_H_REG_DRAW_Y_1C                    OSD_DRAW_H_REG_DRAW_Y_1C
#define OSD_DRAW_H_REG_DRAW_Y_1C_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_1C_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_1C_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1C_POS)
#define OSD_DRAW_H_REG_DRAW_Y_1C_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1C_POS))

/* 0x9C : draw_partial_x_config1c */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG1C_OFFSET (0x9C)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1C              OSD_DRAW_H_REG_DRAW_X_MIN_1C
#define OSD_DRAW_H_REG_DRAW_X_MIN_1C_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1C_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1C_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1C_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1C_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1C_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_1C              OSD_DRAW_H_REG_DRAW_X_MAX_1C
#define OSD_DRAW_H_REG_DRAW_X_MAX_1C_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1C_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1C_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1C_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1C_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1C_POS))

/* 0xA0 : draw_partial_y_config1c */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG1C_OFFSET (0xA0)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1C              OSD_DRAW_H_REG_DRAW_Y_MIN_1C
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1C_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1C_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1C_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1C_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1C_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1C_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1C              OSD_DRAW_H_REG_DRAW_Y_MAX_1C
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1C_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1C_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1C_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1C_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1C_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1C_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1C_POS))

/* 0xA4 : draw_partial_yuv_config1d */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG1D_OFFSET (0xA4)
#define OSD_DRAW_H_REG_DRAW_TH_1D                   OSD_DRAW_H_REG_DRAW_TH_1D
#define OSD_DRAW_H_REG_DRAW_TH_1D_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_1D_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_1D_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1D_POS)
#define OSD_DRAW_H_REG_DRAW_TH_1D_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1D_POS))
#define OSD_DRAW_H_REG_DRAW_V_1D                    OSD_DRAW_H_REG_DRAW_V_1D
#define OSD_DRAW_H_REG_DRAW_V_1D_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1D_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1D_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1D_POS)
#define OSD_DRAW_H_REG_DRAW_V_1D_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1D_POS))
#define OSD_DRAW_H_REG_DRAW_U_1D                    OSD_DRAW_H_REG_DRAW_U_1D
#define OSD_DRAW_H_REG_DRAW_U_1D_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_1D_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_1D_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1D_POS)
#define OSD_DRAW_H_REG_DRAW_U_1D_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1D_POS))
#define OSD_DRAW_H_REG_DRAW_Y_1D                    OSD_DRAW_H_REG_DRAW_Y_1D
#define OSD_DRAW_H_REG_DRAW_Y_1D_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_1D_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_1D_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1D_POS)
#define OSD_DRAW_H_REG_DRAW_Y_1D_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1D_POS))

/* 0xA8 : draw_partial_x_config1d */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG1D_OFFSET (0xA8)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1D              OSD_DRAW_H_REG_DRAW_X_MIN_1D
#define OSD_DRAW_H_REG_DRAW_X_MIN_1D_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1D_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1D_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1D_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1D_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1D_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_1D              OSD_DRAW_H_REG_DRAW_X_MAX_1D
#define OSD_DRAW_H_REG_DRAW_X_MAX_1D_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1D_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1D_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1D_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1D_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1D_POS))

/* 0xAC : draw_partial_y_config1d */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG1D_OFFSET (0xAC)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1D              OSD_DRAW_H_REG_DRAW_Y_MIN_1D
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1D_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1D_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1D_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1D_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1D_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1D_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1D              OSD_DRAW_H_REG_DRAW_Y_MAX_1D
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1D_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1D_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1D_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1D_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1D_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1D_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1D_POS))

/* 0xB0 : draw_partial_yuv_config1e */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG1E_OFFSET (0xB0)
#define OSD_DRAW_H_REG_DRAW_TH_1E                   OSD_DRAW_H_REG_DRAW_TH_1E
#define OSD_DRAW_H_REG_DRAW_TH_1E_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_1E_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_1E_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1E_POS)
#define OSD_DRAW_H_REG_DRAW_TH_1E_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1E_POS))
#define OSD_DRAW_H_REG_DRAW_V_1E                    OSD_DRAW_H_REG_DRAW_V_1E
#define OSD_DRAW_H_REG_DRAW_V_1E_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1E_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1E_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1E_POS)
#define OSD_DRAW_H_REG_DRAW_V_1E_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1E_POS))
#define OSD_DRAW_H_REG_DRAW_U_1E                    OSD_DRAW_H_REG_DRAW_U_1E
#define OSD_DRAW_H_REG_DRAW_U_1E_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_1E_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_1E_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1E_POS)
#define OSD_DRAW_H_REG_DRAW_U_1E_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1E_POS))
#define OSD_DRAW_H_REG_DRAW_Y_1E                    OSD_DRAW_H_REG_DRAW_Y_1E
#define OSD_DRAW_H_REG_DRAW_Y_1E_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_1E_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_1E_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1E_POS)
#define OSD_DRAW_H_REG_DRAW_Y_1E_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1E_POS))

/* 0xB4 : draw_partial_x_config1e */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG1E_OFFSET (0xB4)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1E              OSD_DRAW_H_REG_DRAW_X_MIN_1E
#define OSD_DRAW_H_REG_DRAW_X_MIN_1E_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1E_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1E_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1E_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1E_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1E_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_1E              OSD_DRAW_H_REG_DRAW_X_MAX_1E
#define OSD_DRAW_H_REG_DRAW_X_MAX_1E_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1E_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1E_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1E_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1E_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1E_POS))

/* 0xB8 : draw_partial_y_config1e */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG1E_OFFSET (0xB8)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1E              OSD_DRAW_H_REG_DRAW_Y_MIN_1E
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1E_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1E_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1E_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1E_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1E_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1E_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1E              OSD_DRAW_H_REG_DRAW_Y_MAX_1E
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1E_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1E_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1E_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1E_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1E_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1E_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1E_POS))

/* 0xBC : draw_partial_yuv_config1f */
#define OSD_DRAW_H_DRAW_PARTIAL_YUV_CONFIG1F_OFFSET (0xBC)
#define OSD_DRAW_H_REG_DRAW_TH_1F                   OSD_DRAW_H_REG_DRAW_TH_1F
#define OSD_DRAW_H_REG_DRAW_TH_1F_POS               (0U)
#define OSD_DRAW_H_REG_DRAW_TH_1F_LEN               (8U)
#define OSD_DRAW_H_REG_DRAW_TH_1F_MSK               (((1U << OSD_DRAW_H_REG_DRAW_TH_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1F_POS)
#define OSD_DRAW_H_REG_DRAW_TH_1F_UMSK              (~(((1U << OSD_DRAW_H_REG_DRAW_TH_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_TH_1F_POS))
#define OSD_DRAW_H_REG_DRAW_V_1F                    OSD_DRAW_H_REG_DRAW_V_1F
#define OSD_DRAW_H_REG_DRAW_V_1F_POS                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1F_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_V_1F_MSK                (((1U << OSD_DRAW_H_REG_DRAW_V_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1F_POS)
#define OSD_DRAW_H_REG_DRAW_V_1F_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_V_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_V_1F_POS))
#define OSD_DRAW_H_REG_DRAW_U_1F                    OSD_DRAW_H_REG_DRAW_U_1F
#define OSD_DRAW_H_REG_DRAW_U_1F_POS                (16U)
#define OSD_DRAW_H_REG_DRAW_U_1F_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_U_1F_MSK                (((1U << OSD_DRAW_H_REG_DRAW_U_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1F_POS)
#define OSD_DRAW_H_REG_DRAW_U_1F_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_U_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_U_1F_POS))
#define OSD_DRAW_H_REG_DRAW_Y_1F                    OSD_DRAW_H_REG_DRAW_Y_1F
#define OSD_DRAW_H_REG_DRAW_Y_1F_POS                (24U)
#define OSD_DRAW_H_REG_DRAW_Y_1F_LEN                (8U)
#define OSD_DRAW_H_REG_DRAW_Y_1F_MSK                (((1U << OSD_DRAW_H_REG_DRAW_Y_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1F_POS)
#define OSD_DRAW_H_REG_DRAW_Y_1F_UMSK               (~(((1U << OSD_DRAW_H_REG_DRAW_Y_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_1F_POS))

/* 0xC0 : draw_partial_x_config1f */
#define OSD_DRAW_H_DRAW_PARTIAL_X_CONFIG1F_OFFSET (0xC0)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1F              OSD_DRAW_H_REG_DRAW_X_MIN_1F
#define OSD_DRAW_H_REG_DRAW_X_MIN_1F_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1F_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1F_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1F_POS)
#define OSD_DRAW_H_REG_DRAW_X_MIN_1F_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MIN_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MIN_1F_POS))
#define OSD_DRAW_H_REG_DRAW_X_MAX_1F              OSD_DRAW_H_REG_DRAW_X_MAX_1F
#define OSD_DRAW_H_REG_DRAW_X_MAX_1F_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1F_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1F_MSK          (((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1F_POS)
#define OSD_DRAW_H_REG_DRAW_X_MAX_1F_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_X_MAX_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_X_MAX_1F_POS))

/* 0xC4 : draw_partial_y_config1f */
#define OSD_DRAW_H_DRAW_PARTIAL_Y_CONFIG1F_OFFSET (0xC4)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1F              OSD_DRAW_H_REG_DRAW_Y_MIN_1F
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1F_POS          (0U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1F_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1F_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1F_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MIN_1F_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MIN_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MIN_1F_POS))
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1F              OSD_DRAW_H_REG_DRAW_Y_MAX_1F
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1F_POS          (16U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1F_LEN          (11U)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1F_MSK          (((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1F_POS)
#define OSD_DRAW_H_REG_DRAW_Y_MAX_1F_UMSK         (~(((1U << OSD_DRAW_H_REG_DRAW_Y_MAX_1F_LEN) - 1) << OSD_DRAW_H_REG_DRAW_Y_MAX_1F_POS))

struct osd_draw_h_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[4];

    /* 0x4 : draw_partial_config */
    union {
        struct {
            uint32_t reg_draw_en_h   : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_draw_type_h : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_config;

    /* 0x8 : draw_partial_yuv_config10 */
    union {
        struct {
            uint32_t reg_draw_th_10 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_10  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_10  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_10  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config10;

    /* 0xC : draw_partial_x_config10 */
    union {
        struct {
            uint32_t reg_draw_x_min_10 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_10 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config10;

    /* 0x10 : draw_partial_y_config10 */
    union {
        struct {
            uint32_t reg_draw_y_min_10 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_10 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config10;

    /* 0x14 : draw_partial_yuv_config11 */
    union {
        struct {
            uint32_t reg_draw_th_11 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_11  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_11  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_11  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config11;

    /* 0x18 : draw_partial_x_config11 */
    union {
        struct {
            uint32_t reg_draw_x_min_11 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_11 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config11;

    /* 0x1C : draw_partial_y_config11 */
    union {
        struct {
            uint32_t reg_draw_y_min_11 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_11 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config11;

    /* 0x20 : draw_partial_yuv_config12 */
    union {
        struct {
            uint32_t reg_draw_th_12 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_12  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_12  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_12  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config12;

    /* 0x24 : draw_partial_x_config12 */
    union {
        struct {
            uint32_t reg_draw_x_min_12 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_12 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config12;

    /* 0x28 : draw_partial_y_config12 */
    union {
        struct {
            uint32_t reg_draw_y_min_12 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_12 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config12;

    /* 0x2C : draw_partial_yuv_config13 */
    union {
        struct {
            uint32_t reg_draw_th_13 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_13  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_13  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_13  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config13;

    /* 0x30 : draw_partial_x_config13 */
    union {
        struct {
            uint32_t reg_draw_x_min_13 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_13 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config13;

    /* 0x34 : draw_partial_y_config13 */
    union {
        struct {
            uint32_t reg_draw_y_min_13 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_13 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config13;

    /* 0x38 : draw_partial_yuv_config14 */
    union {
        struct {
            uint32_t reg_draw_th_14 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_14  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_14  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_14  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config14;

    /* 0x3C : draw_partial_x_config14 */
    union {
        struct {
            uint32_t reg_draw_x_min_14 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_14 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config14;

    /* 0x40 : draw_partial_y_config14 */
    union {
        struct {
            uint32_t reg_draw_y_min_14 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_14 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config14;

    /* 0x44 : draw_partial_yuv_config15 */
    union {
        struct {
            uint32_t reg_draw_th_15 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_15  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_15  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_15  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config15;

    /* 0x48 : draw_partial_x_config15 */
    union {
        struct {
            uint32_t reg_draw_x_min_15 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_15 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config15;

    /* 0x4C : draw_partial_y_config15 */
    union {
        struct {
            uint32_t reg_draw_y_min_15 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_15 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config15;

    /* 0x50 : draw_partial_yuv_config16 */
    union {
        struct {
            uint32_t reg_draw_th_16 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_16  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_16  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_16  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config16;

    /* 0x54 : draw_partial_x_config16 */
    union {
        struct {
            uint32_t reg_draw_x_min_16 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_16 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config16;

    /* 0x58 : draw_partial_y_config16 */
    union {
        struct {
            uint32_t reg_draw_y_min_16 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_16 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config16;

    /* 0x5C : draw_partial_yuv_config17 */
    union {
        struct {
            uint32_t reg_draw_th_17 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_17  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_17  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_17  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config17;

    /* 0x60 : draw_partial_x_config17 */
    union {
        struct {
            uint32_t reg_draw_x_min_17 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_17 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config17;

    /* 0x64 : draw_partial_y_config17 */
    union {
        struct {
            uint32_t reg_draw_y_min_17 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_17 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config17;

    /* 0x68 : draw_partial_yuv_config18 */
    union {
        struct {
            uint32_t reg_draw_th_18 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_18  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_18  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_18  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config18;

    /* 0x6C : draw_partial_x_config18 */
    union {
        struct {
            uint32_t reg_draw_x_min_18 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_18 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config18;

    /* 0x70 : draw_partial_y_config18 */
    union {
        struct {
            uint32_t reg_draw_y_min_18 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_18 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config18;

    /* 0x74 : draw_partial_yuv_config19 */
    union {
        struct {
            uint32_t reg_draw_th_19 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_19  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_19  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_19  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config19;

    /* 0x78 : draw_partial_x_config19 */
    union {
        struct {
            uint32_t reg_draw_x_min_19 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_19 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config19;

    /* 0x7C : draw_partial_y_config19 */
    union {
        struct {
            uint32_t reg_draw_y_min_19 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_19 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config19;

    /* 0x80 : draw_partial_yuv_config1a */
    union {
        struct {
            uint32_t reg_draw_th_1a : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_1a  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_1a  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_1a  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1a;

    /* 0x84 : draw_partial_x_config1a */
    union {
        struct {
            uint32_t reg_draw_x_min_1a : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_1a : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1a;

    /* 0x88 : draw_partial_y_config1a */
    union {
        struct {
            uint32_t reg_draw_y_min_1a : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_1a : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1a;

    /* 0x8C : draw_partial_yuv_config1b */
    union {
        struct {
            uint32_t reg_draw_th_1b : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_1b  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_1b  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_1b  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1b;

    /* 0x90 : draw_partial_x_config1b */
    union {
        struct {
            uint32_t reg_draw_x_min_1b : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_1b : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1b;

    /* 0x94 : draw_partial_y_config1b */
    union {
        struct {
            uint32_t reg_draw_y_min_1b : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_1b : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1b;

    /* 0x98 : draw_partial_yuv_config1c */
    union {
        struct {
            uint32_t reg_draw_th_1c : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_1c  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_1c  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_1c  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1c;

    /* 0x9C : draw_partial_x_config1c */
    union {
        struct {
            uint32_t reg_draw_x_min_1c : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_1c : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1c;

    /* 0xA0 : draw_partial_y_config1c */
    union {
        struct {
            uint32_t reg_draw_y_min_1c : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_1c : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1c;

    /* 0xA4 : draw_partial_yuv_config1d */
    union {
        struct {
            uint32_t reg_draw_th_1d : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_1d  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_1d  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_1d  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1d;

    /* 0xA8 : draw_partial_x_config1d */
    union {
        struct {
            uint32_t reg_draw_x_min_1d : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_1d : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1d;

    /* 0xAC : draw_partial_y_config1d */
    union {
        struct {
            uint32_t reg_draw_y_min_1d : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_1d : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1d;

    /* 0xB0 : draw_partial_yuv_config1e */
    union {
        struct {
            uint32_t reg_draw_th_1e : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_1e  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_1e  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_1e  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1e;

    /* 0xB4 : draw_partial_x_config1e */
    union {
        struct {
            uint32_t reg_draw_x_min_1e : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_1e : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1e;

    /* 0xB8 : draw_partial_y_config1e */
    union {
        struct {
            uint32_t reg_draw_y_min_1e : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_1e : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1e;

    /* 0xBC : draw_partial_yuv_config1f */
    union {
        struct {
            uint32_t reg_draw_th_1f : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_1f  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_1f  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_1f  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1f;

    /* 0xC0 : draw_partial_x_config1f */
    union {
        struct {
            uint32_t reg_draw_x_min_1f : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_1f : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1f;

    /* 0xC4 : draw_partial_y_config1f */
    union {
        struct {
            uint32_t reg_draw_y_min_1f : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_1f : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1f;
};

typedef volatile struct osd_draw_h_reg osd_draw_h_reg_t;

#endif /* __OSD_DRAW_H_REG_H__ */
