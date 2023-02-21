/**
  ******************************************************************************
  * @file    osd_reg.h
  * @version V1.0
  * @date    2020-12-25
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
#ifndef __OSD_REG_H__
#define __OSD_REG_H__

#include "bl808.h"

/* 0x0 : osd_draw_config */
#define OSD_DRAW_CONFIG_OFFSET   (0x0)
#define OSD_REG_DRAW_EN_L        OSD_REG_DRAW_EN_L
#define OSD_REG_DRAW_EN_L_POS    (0U)
#define OSD_REG_DRAW_EN_L_LEN    (16U)
#define OSD_REG_DRAW_EN_L_MSK    (((1U << OSD_REG_DRAW_EN_L_LEN) - 1) << OSD_REG_DRAW_EN_L_POS)
#define OSD_REG_DRAW_EN_L_UMSK   (~(((1U << OSD_REG_DRAW_EN_L_LEN) - 1) << OSD_REG_DRAW_EN_L_POS))
#define OSD_REG_DRAW_TYPE_L      OSD_REG_DRAW_TYPE_L
#define OSD_REG_DRAW_TYPE_L_POS  (16U)
#define OSD_REG_DRAW_TYPE_L_LEN  (16U)
#define OSD_REG_DRAW_TYPE_L_MSK  (((1U << OSD_REG_DRAW_TYPE_L_LEN) - 1) << OSD_REG_DRAW_TYPE_L_POS)
#define OSD_REG_DRAW_TYPE_L_UMSK (~(((1U << OSD_REG_DRAW_TYPE_L_LEN) - 1) << OSD_REG_DRAW_TYPE_L_POS))

/* 0x4 : draw_partial_yuv_config0 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG0_OFFSET (0x4)
#define OSD_REG_DRAW_TH_00                  OSD_REG_DRAW_TH_00
#define OSD_REG_DRAW_TH_00_POS              (0U)
#define OSD_REG_DRAW_TH_00_LEN              (8U)
#define OSD_REG_DRAW_TH_00_MSK              (((1U << OSD_REG_DRAW_TH_00_LEN) - 1) << OSD_REG_DRAW_TH_00_POS)
#define OSD_REG_DRAW_TH_00_UMSK             (~(((1U << OSD_REG_DRAW_TH_00_LEN) - 1) << OSD_REG_DRAW_TH_00_POS))
#define OSD_REG_DRAW_V_00                   OSD_REG_DRAW_V_00
#define OSD_REG_DRAW_V_00_POS               (8U)
#define OSD_REG_DRAW_V_00_LEN               (8U)
#define OSD_REG_DRAW_V_00_MSK               (((1U << OSD_REG_DRAW_V_00_LEN) - 1) << OSD_REG_DRAW_V_00_POS)
#define OSD_REG_DRAW_V_00_UMSK              (~(((1U << OSD_REG_DRAW_V_00_LEN) - 1) << OSD_REG_DRAW_V_00_POS))
#define OSD_REG_DRAW_U_00                   OSD_REG_DRAW_U_00
#define OSD_REG_DRAW_U_00_POS               (16U)
#define OSD_REG_DRAW_U_00_LEN               (8U)
#define OSD_REG_DRAW_U_00_MSK               (((1U << OSD_REG_DRAW_U_00_LEN) - 1) << OSD_REG_DRAW_U_00_POS)
#define OSD_REG_DRAW_U_00_UMSK              (~(((1U << OSD_REG_DRAW_U_00_LEN) - 1) << OSD_REG_DRAW_U_00_POS))
#define OSD_REG_DRAW_Y_00                   OSD_REG_DRAW_Y_00
#define OSD_REG_DRAW_Y_00_POS               (24U)
#define OSD_REG_DRAW_Y_00_LEN               (8U)
#define OSD_REG_DRAW_Y_00_MSK               (((1U << OSD_REG_DRAW_Y_00_LEN) - 1) << OSD_REG_DRAW_Y_00_POS)
#define OSD_REG_DRAW_Y_00_UMSK              (~(((1U << OSD_REG_DRAW_Y_00_LEN) - 1) << OSD_REG_DRAW_Y_00_POS))

/* 0x8 : draw_partial_x_config0 */
#define OSD_DRAW_PARTIAL_X_CONFIG0_OFFSET (0x8)
#define OSD_REG_DRAW_X_MIN_00             OSD_REG_DRAW_X_MIN_00
#define OSD_REG_DRAW_X_MIN_00_POS         (0U)
#define OSD_REG_DRAW_X_MIN_00_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_00_MSK         (((1U << OSD_REG_DRAW_X_MIN_00_LEN) - 1) << OSD_REG_DRAW_X_MIN_00_POS)
#define OSD_REG_DRAW_X_MIN_00_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_00_LEN) - 1) << OSD_REG_DRAW_X_MIN_00_POS))
#define OSD_REG_DRAW_X_MAX_00             OSD_REG_DRAW_X_MAX_00
#define OSD_REG_DRAW_X_MAX_00_POS         (16U)
#define OSD_REG_DRAW_X_MAX_00_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_00_MSK         (((1U << OSD_REG_DRAW_X_MAX_00_LEN) - 1) << OSD_REG_DRAW_X_MAX_00_POS)
#define OSD_REG_DRAW_X_MAX_00_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_00_LEN) - 1) << OSD_REG_DRAW_X_MAX_00_POS))

/* 0xC : draw_partial_y_config0 */
#define OSD_DRAW_PARTIAL_Y_CONFIG0_OFFSET (0xC)
#define OSD_REG_DRAW_Y_MIN_00             OSD_REG_DRAW_Y_MIN_00
#define OSD_REG_DRAW_Y_MIN_00_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_00_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_00_MSK         (((1U << OSD_REG_DRAW_Y_MIN_00_LEN) - 1) << OSD_REG_DRAW_Y_MIN_00_POS)
#define OSD_REG_DRAW_Y_MIN_00_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_00_LEN) - 1) << OSD_REG_DRAW_Y_MIN_00_POS))
#define OSD_REG_DRAW_Y_MAX_00             OSD_REG_DRAW_Y_MAX_00
#define OSD_REG_DRAW_Y_MAX_00_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_00_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_00_MSK         (((1U << OSD_REG_DRAW_Y_MAX_00_LEN) - 1) << OSD_REG_DRAW_Y_MAX_00_POS)
#define OSD_REG_DRAW_Y_MAX_00_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_00_LEN) - 1) << OSD_REG_DRAW_Y_MAX_00_POS))

/* 0x10 : draw_partial_yuv_config1 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG1_OFFSET (0x10)
#define OSD_REG_DRAW_TH_01                  OSD_REG_DRAW_TH_01
#define OSD_REG_DRAW_TH_01_POS              (0U)
#define OSD_REG_DRAW_TH_01_LEN              (8U)
#define OSD_REG_DRAW_TH_01_MSK              (((1U << OSD_REG_DRAW_TH_01_LEN) - 1) << OSD_REG_DRAW_TH_01_POS)
#define OSD_REG_DRAW_TH_01_UMSK             (~(((1U << OSD_REG_DRAW_TH_01_LEN) - 1) << OSD_REG_DRAW_TH_01_POS))
#define OSD_REG_DRAW_V_01                   OSD_REG_DRAW_V_01
#define OSD_REG_DRAW_V_01_POS               (8U)
#define OSD_REG_DRAW_V_01_LEN               (8U)
#define OSD_REG_DRAW_V_01_MSK               (((1U << OSD_REG_DRAW_V_01_LEN) - 1) << OSD_REG_DRAW_V_01_POS)
#define OSD_REG_DRAW_V_01_UMSK              (~(((1U << OSD_REG_DRAW_V_01_LEN) - 1) << OSD_REG_DRAW_V_01_POS))
#define OSD_REG_DRAW_U_01                   OSD_REG_DRAW_U_01
#define OSD_REG_DRAW_U_01_POS               (16U)
#define OSD_REG_DRAW_U_01_LEN               (8U)
#define OSD_REG_DRAW_U_01_MSK               (((1U << OSD_REG_DRAW_U_01_LEN) - 1) << OSD_REG_DRAW_U_01_POS)
#define OSD_REG_DRAW_U_01_UMSK              (~(((1U << OSD_REG_DRAW_U_01_LEN) - 1) << OSD_REG_DRAW_U_01_POS))
#define OSD_REG_DRAW_Y_01                   OSD_REG_DRAW_Y_01
#define OSD_REG_DRAW_Y_01_POS               (24U)
#define OSD_REG_DRAW_Y_01_LEN               (8U)
#define OSD_REG_DRAW_Y_01_MSK               (((1U << OSD_REG_DRAW_Y_01_LEN) - 1) << OSD_REG_DRAW_Y_01_POS)
#define OSD_REG_DRAW_Y_01_UMSK              (~(((1U << OSD_REG_DRAW_Y_01_LEN) - 1) << OSD_REG_DRAW_Y_01_POS))

/* 0x14 : draw_partial_x_config1 */
#define OSD_DRAW_PARTIAL_X_CONFIG1_OFFSET (0x14)
#define OSD_REG_DRAW_X_MIN_01             OSD_REG_DRAW_X_MIN_01
#define OSD_REG_DRAW_X_MIN_01_POS         (0U)
#define OSD_REG_DRAW_X_MIN_01_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_01_MSK         (((1U << OSD_REG_DRAW_X_MIN_01_LEN) - 1) << OSD_REG_DRAW_X_MIN_01_POS)
#define OSD_REG_DRAW_X_MIN_01_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_01_LEN) - 1) << OSD_REG_DRAW_X_MIN_01_POS))
#define OSD_REG_DRAW_X_MAX_01             OSD_REG_DRAW_X_MAX_01
#define OSD_REG_DRAW_X_MAX_01_POS         (16U)
#define OSD_REG_DRAW_X_MAX_01_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_01_MSK         (((1U << OSD_REG_DRAW_X_MAX_01_LEN) - 1) << OSD_REG_DRAW_X_MAX_01_POS)
#define OSD_REG_DRAW_X_MAX_01_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_01_LEN) - 1) << OSD_REG_DRAW_X_MAX_01_POS))

/* 0x18 : draw_partial_y_config1 */
#define OSD_DRAW_PARTIAL_Y_CONFIG1_OFFSET (0x18)
#define OSD_REG_DRAW_Y_MIN_01             OSD_REG_DRAW_Y_MIN_01
#define OSD_REG_DRAW_Y_MIN_01_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_01_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_01_MSK         (((1U << OSD_REG_DRAW_Y_MIN_01_LEN) - 1) << OSD_REG_DRAW_Y_MIN_01_POS)
#define OSD_REG_DRAW_Y_MIN_01_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_01_LEN) - 1) << OSD_REG_DRAW_Y_MIN_01_POS))
#define OSD_REG_DRAW_Y_MAX_01             OSD_REG_DRAW_Y_MAX_01
#define OSD_REG_DRAW_Y_MAX_01_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_01_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_01_MSK         (((1U << OSD_REG_DRAW_Y_MAX_01_LEN) - 1) << OSD_REG_DRAW_Y_MAX_01_POS)
#define OSD_REG_DRAW_Y_MAX_01_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_01_LEN) - 1) << OSD_REG_DRAW_Y_MAX_01_POS))

/* 0x1C : draw_partial_yuv_config2 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG2_OFFSET (0x1C)
#define OSD_REG_DRAW_TH_02                  OSD_REG_DRAW_TH_02
#define OSD_REG_DRAW_TH_02_POS              (0U)
#define OSD_REG_DRAW_TH_02_LEN              (8U)
#define OSD_REG_DRAW_TH_02_MSK              (((1U << OSD_REG_DRAW_TH_02_LEN) - 1) << OSD_REG_DRAW_TH_02_POS)
#define OSD_REG_DRAW_TH_02_UMSK             (~(((1U << OSD_REG_DRAW_TH_02_LEN) - 1) << OSD_REG_DRAW_TH_02_POS))
#define OSD_REG_DRAW_V_02                   OSD_REG_DRAW_V_02
#define OSD_REG_DRAW_V_02_POS               (8U)
#define OSD_REG_DRAW_V_02_LEN               (8U)
#define OSD_REG_DRAW_V_02_MSK               (((1U << OSD_REG_DRAW_V_02_LEN) - 1) << OSD_REG_DRAW_V_02_POS)
#define OSD_REG_DRAW_V_02_UMSK              (~(((1U << OSD_REG_DRAW_V_02_LEN) - 1) << OSD_REG_DRAW_V_02_POS))
#define OSD_REG_DRAW_U_02                   OSD_REG_DRAW_U_02
#define OSD_REG_DRAW_U_02_POS               (16U)
#define OSD_REG_DRAW_U_02_LEN               (8U)
#define OSD_REG_DRAW_U_02_MSK               (((1U << OSD_REG_DRAW_U_02_LEN) - 1) << OSD_REG_DRAW_U_02_POS)
#define OSD_REG_DRAW_U_02_UMSK              (~(((1U << OSD_REG_DRAW_U_02_LEN) - 1) << OSD_REG_DRAW_U_02_POS))
#define OSD_REG_DRAW_Y_02                   OSD_REG_DRAW_Y_02
#define OSD_REG_DRAW_Y_02_POS               (24U)
#define OSD_REG_DRAW_Y_02_LEN               (8U)
#define OSD_REG_DRAW_Y_02_MSK               (((1U << OSD_REG_DRAW_Y_02_LEN) - 1) << OSD_REG_DRAW_Y_02_POS)
#define OSD_REG_DRAW_Y_02_UMSK              (~(((1U << OSD_REG_DRAW_Y_02_LEN) - 1) << OSD_REG_DRAW_Y_02_POS))

/* 0x20 : draw_partial_x_config2 */
#define OSD_DRAW_PARTIAL_X_CONFIG2_OFFSET (0x20)
#define OSD_REG_DRAW_X_MIN_02             OSD_REG_DRAW_X_MIN_02
#define OSD_REG_DRAW_X_MIN_02_POS         (0U)
#define OSD_REG_DRAW_X_MIN_02_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_02_MSK         (((1U << OSD_REG_DRAW_X_MIN_02_LEN) - 1) << OSD_REG_DRAW_X_MIN_02_POS)
#define OSD_REG_DRAW_X_MIN_02_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_02_LEN) - 1) << OSD_REG_DRAW_X_MIN_02_POS))
#define OSD_REG_DRAW_X_MAX_02             OSD_REG_DRAW_X_MAX_02
#define OSD_REG_DRAW_X_MAX_02_POS         (16U)
#define OSD_REG_DRAW_X_MAX_02_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_02_MSK         (((1U << OSD_REG_DRAW_X_MAX_02_LEN) - 1) << OSD_REG_DRAW_X_MAX_02_POS)
#define OSD_REG_DRAW_X_MAX_02_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_02_LEN) - 1) << OSD_REG_DRAW_X_MAX_02_POS))

/* 0x24 : draw_partial_y_config2 */
#define OSD_DRAW_PARTIAL_Y_CONFIG2_OFFSET (0x24)
#define OSD_REG_DRAW_Y_MIN_02             OSD_REG_DRAW_Y_MIN_02
#define OSD_REG_DRAW_Y_MIN_02_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_02_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_02_MSK         (((1U << OSD_REG_DRAW_Y_MIN_02_LEN) - 1) << OSD_REG_DRAW_Y_MIN_02_POS)
#define OSD_REG_DRAW_Y_MIN_02_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_02_LEN) - 1) << OSD_REG_DRAW_Y_MIN_02_POS))
#define OSD_REG_DRAW_Y_MAX_02             OSD_REG_DRAW_Y_MAX_02
#define OSD_REG_DRAW_Y_MAX_02_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_02_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_02_MSK         (((1U << OSD_REG_DRAW_Y_MAX_02_LEN) - 1) << OSD_REG_DRAW_Y_MAX_02_POS)
#define OSD_REG_DRAW_Y_MAX_02_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_02_LEN) - 1) << OSD_REG_DRAW_Y_MAX_02_POS))

/* 0x28 : draw_partial_yuv_config3 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG3_OFFSET (0x28)
#define OSD_REG_DRAW_TH_03                  OSD_REG_DRAW_TH_03
#define OSD_REG_DRAW_TH_03_POS              (0U)
#define OSD_REG_DRAW_TH_03_LEN              (8U)
#define OSD_REG_DRAW_TH_03_MSK              (((1U << OSD_REG_DRAW_TH_03_LEN) - 1) << OSD_REG_DRAW_TH_03_POS)
#define OSD_REG_DRAW_TH_03_UMSK             (~(((1U << OSD_REG_DRAW_TH_03_LEN) - 1) << OSD_REG_DRAW_TH_03_POS))
#define OSD_REG_DRAW_V_03                   OSD_REG_DRAW_V_03
#define OSD_REG_DRAW_V_03_POS               (8U)
#define OSD_REG_DRAW_V_03_LEN               (8U)
#define OSD_REG_DRAW_V_03_MSK               (((1U << OSD_REG_DRAW_V_03_LEN) - 1) << OSD_REG_DRAW_V_03_POS)
#define OSD_REG_DRAW_V_03_UMSK              (~(((1U << OSD_REG_DRAW_V_03_LEN) - 1) << OSD_REG_DRAW_V_03_POS))
#define OSD_REG_DRAW_U_03                   OSD_REG_DRAW_U_03
#define OSD_REG_DRAW_U_03_POS               (16U)
#define OSD_REG_DRAW_U_03_LEN               (8U)
#define OSD_REG_DRAW_U_03_MSK               (((1U << OSD_REG_DRAW_U_03_LEN) - 1) << OSD_REG_DRAW_U_03_POS)
#define OSD_REG_DRAW_U_03_UMSK              (~(((1U << OSD_REG_DRAW_U_03_LEN) - 1) << OSD_REG_DRAW_U_03_POS))
#define OSD_REG_DRAW_Y_03                   OSD_REG_DRAW_Y_03
#define OSD_REG_DRAW_Y_03_POS               (24U)
#define OSD_REG_DRAW_Y_03_LEN               (8U)
#define OSD_REG_DRAW_Y_03_MSK               (((1U << OSD_REG_DRAW_Y_03_LEN) - 1) << OSD_REG_DRAW_Y_03_POS)
#define OSD_REG_DRAW_Y_03_UMSK              (~(((1U << OSD_REG_DRAW_Y_03_LEN) - 1) << OSD_REG_DRAW_Y_03_POS))

/* 0x2C : draw_partial_x_config3 */
#define OSD_DRAW_PARTIAL_X_CONFIG3_OFFSET (0x2C)
#define OSD_REG_DRAW_X_MIN_03             OSD_REG_DRAW_X_MIN_03
#define OSD_REG_DRAW_X_MIN_03_POS         (0U)
#define OSD_REG_DRAW_X_MIN_03_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_03_MSK         (((1U << OSD_REG_DRAW_X_MIN_03_LEN) - 1) << OSD_REG_DRAW_X_MIN_03_POS)
#define OSD_REG_DRAW_X_MIN_03_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_03_LEN) - 1) << OSD_REG_DRAW_X_MIN_03_POS))
#define OSD_REG_DRAW_X_MAX_03             OSD_REG_DRAW_X_MAX_03
#define OSD_REG_DRAW_X_MAX_03_POS         (16U)
#define OSD_REG_DRAW_X_MAX_03_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_03_MSK         (((1U << OSD_REG_DRAW_X_MAX_03_LEN) - 1) << OSD_REG_DRAW_X_MAX_03_POS)
#define OSD_REG_DRAW_X_MAX_03_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_03_LEN) - 1) << OSD_REG_DRAW_X_MAX_03_POS))

/* 0x30 : draw_partial_y_config3 */
#define OSD_DRAW_PARTIAL_Y_CONFIG3_OFFSET (0x30)
#define OSD_REG_DRAW_Y_MIN_03             OSD_REG_DRAW_Y_MIN_03
#define OSD_REG_DRAW_Y_MIN_03_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_03_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_03_MSK         (((1U << OSD_REG_DRAW_Y_MIN_03_LEN) - 1) << OSD_REG_DRAW_Y_MIN_03_POS)
#define OSD_REG_DRAW_Y_MIN_03_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_03_LEN) - 1) << OSD_REG_DRAW_Y_MIN_03_POS))
#define OSD_REG_DRAW_Y_MAX_03             OSD_REG_DRAW_Y_MAX_03
#define OSD_REG_DRAW_Y_MAX_03_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_03_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_03_MSK         (((1U << OSD_REG_DRAW_Y_MAX_03_LEN) - 1) << OSD_REG_DRAW_Y_MAX_03_POS)
#define OSD_REG_DRAW_Y_MAX_03_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_03_LEN) - 1) << OSD_REG_DRAW_Y_MAX_03_POS))

/* 0x34 : draw_partial_yuv_config4 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG4_OFFSET (0x34)
#define OSD_REG_DRAW_TH_04                  OSD_REG_DRAW_TH_04
#define OSD_REG_DRAW_TH_04_POS              (0U)
#define OSD_REG_DRAW_TH_04_LEN              (8U)
#define OSD_REG_DRAW_TH_04_MSK              (((1U << OSD_REG_DRAW_TH_04_LEN) - 1) << OSD_REG_DRAW_TH_04_POS)
#define OSD_REG_DRAW_TH_04_UMSK             (~(((1U << OSD_REG_DRAW_TH_04_LEN) - 1) << OSD_REG_DRAW_TH_04_POS))
#define OSD_REG_DRAW_V_04                   OSD_REG_DRAW_V_04
#define OSD_REG_DRAW_V_04_POS               (8U)
#define OSD_REG_DRAW_V_04_LEN               (8U)
#define OSD_REG_DRAW_V_04_MSK               (((1U << OSD_REG_DRAW_V_04_LEN) - 1) << OSD_REG_DRAW_V_04_POS)
#define OSD_REG_DRAW_V_04_UMSK              (~(((1U << OSD_REG_DRAW_V_04_LEN) - 1) << OSD_REG_DRAW_V_04_POS))
#define OSD_REG_DRAW_U_04                   OSD_REG_DRAW_U_04
#define OSD_REG_DRAW_U_04_POS               (16U)
#define OSD_REG_DRAW_U_04_LEN               (8U)
#define OSD_REG_DRAW_U_04_MSK               (((1U << OSD_REG_DRAW_U_04_LEN) - 1) << OSD_REG_DRAW_U_04_POS)
#define OSD_REG_DRAW_U_04_UMSK              (~(((1U << OSD_REG_DRAW_U_04_LEN) - 1) << OSD_REG_DRAW_U_04_POS))
#define OSD_REG_DRAW_Y_04                   OSD_REG_DRAW_Y_04
#define OSD_REG_DRAW_Y_04_POS               (24U)
#define OSD_REG_DRAW_Y_04_LEN               (8U)
#define OSD_REG_DRAW_Y_04_MSK               (((1U << OSD_REG_DRAW_Y_04_LEN) - 1) << OSD_REG_DRAW_Y_04_POS)
#define OSD_REG_DRAW_Y_04_UMSK              (~(((1U << OSD_REG_DRAW_Y_04_LEN) - 1) << OSD_REG_DRAW_Y_04_POS))

/* 0x38 : draw_partial_x_config4 */
#define OSD_DRAW_PARTIAL_X_CONFIG4_OFFSET (0x38)
#define OSD_REG_DRAW_X_MIN_04             OSD_REG_DRAW_X_MIN_04
#define OSD_REG_DRAW_X_MIN_04_POS         (0U)
#define OSD_REG_DRAW_X_MIN_04_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_04_MSK         (((1U << OSD_REG_DRAW_X_MIN_04_LEN) - 1) << OSD_REG_DRAW_X_MIN_04_POS)
#define OSD_REG_DRAW_X_MIN_04_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_04_LEN) - 1) << OSD_REG_DRAW_X_MIN_04_POS))
#define OSD_REG_DRAW_X_MAX_04             OSD_REG_DRAW_X_MAX_04
#define OSD_REG_DRAW_X_MAX_04_POS         (16U)
#define OSD_REG_DRAW_X_MAX_04_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_04_MSK         (((1U << OSD_REG_DRAW_X_MAX_04_LEN) - 1) << OSD_REG_DRAW_X_MAX_04_POS)
#define OSD_REG_DRAW_X_MAX_04_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_04_LEN) - 1) << OSD_REG_DRAW_X_MAX_04_POS))

/* 0x3C : draw_partial_y_config4 */
#define OSD_DRAW_PARTIAL_Y_CONFIG4_OFFSET (0x3C)
#define OSD_REG_DRAW_Y_MIN_04             OSD_REG_DRAW_Y_MIN_04
#define OSD_REG_DRAW_Y_MIN_04_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_04_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_04_MSK         (((1U << OSD_REG_DRAW_Y_MIN_04_LEN) - 1) << OSD_REG_DRAW_Y_MIN_04_POS)
#define OSD_REG_DRAW_Y_MIN_04_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_04_LEN) - 1) << OSD_REG_DRAW_Y_MIN_04_POS))
#define OSD_REG_DRAW_Y_MAX_04             OSD_REG_DRAW_Y_MAX_04
#define OSD_REG_DRAW_Y_MAX_04_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_04_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_04_MSK         (((1U << OSD_REG_DRAW_Y_MAX_04_LEN) - 1) << OSD_REG_DRAW_Y_MAX_04_POS)
#define OSD_REG_DRAW_Y_MAX_04_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_04_LEN) - 1) << OSD_REG_DRAW_Y_MAX_04_POS))

/* 0x40 : draw_partial_yuv_config5 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG5_OFFSET (0x40)
#define OSD_REG_DRAW_TH_05                  OSD_REG_DRAW_TH_05
#define OSD_REG_DRAW_TH_05_POS              (0U)
#define OSD_REG_DRAW_TH_05_LEN              (8U)
#define OSD_REG_DRAW_TH_05_MSK              (((1U << OSD_REG_DRAW_TH_05_LEN) - 1) << OSD_REG_DRAW_TH_05_POS)
#define OSD_REG_DRAW_TH_05_UMSK             (~(((1U << OSD_REG_DRAW_TH_05_LEN) - 1) << OSD_REG_DRAW_TH_05_POS))
#define OSD_REG_DRAW_V_05                   OSD_REG_DRAW_V_05
#define OSD_REG_DRAW_V_05_POS               (8U)
#define OSD_REG_DRAW_V_05_LEN               (8U)
#define OSD_REG_DRAW_V_05_MSK               (((1U << OSD_REG_DRAW_V_05_LEN) - 1) << OSD_REG_DRAW_V_05_POS)
#define OSD_REG_DRAW_V_05_UMSK              (~(((1U << OSD_REG_DRAW_V_05_LEN) - 1) << OSD_REG_DRAW_V_05_POS))
#define OSD_REG_DRAW_U_05                   OSD_REG_DRAW_U_05
#define OSD_REG_DRAW_U_05_POS               (16U)
#define OSD_REG_DRAW_U_05_LEN               (8U)
#define OSD_REG_DRAW_U_05_MSK               (((1U << OSD_REG_DRAW_U_05_LEN) - 1) << OSD_REG_DRAW_U_05_POS)
#define OSD_REG_DRAW_U_05_UMSK              (~(((1U << OSD_REG_DRAW_U_05_LEN) - 1) << OSD_REG_DRAW_U_05_POS))
#define OSD_REG_DRAW_Y_05                   OSD_REG_DRAW_Y_05
#define OSD_REG_DRAW_Y_05_POS               (24U)
#define OSD_REG_DRAW_Y_05_LEN               (8U)
#define OSD_REG_DRAW_Y_05_MSK               (((1U << OSD_REG_DRAW_Y_05_LEN) - 1) << OSD_REG_DRAW_Y_05_POS)
#define OSD_REG_DRAW_Y_05_UMSK              (~(((1U << OSD_REG_DRAW_Y_05_LEN) - 1) << OSD_REG_DRAW_Y_05_POS))

/* 0x44 : draw_partial_x_config5 */
#define OSD_DRAW_PARTIAL_X_CONFIG5_OFFSET (0x44)
#define OSD_REG_DRAW_X_MIN_05             OSD_REG_DRAW_X_MIN_05
#define OSD_REG_DRAW_X_MIN_05_POS         (0U)
#define OSD_REG_DRAW_X_MIN_05_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_05_MSK         (((1U << OSD_REG_DRAW_X_MIN_05_LEN) - 1) << OSD_REG_DRAW_X_MIN_05_POS)
#define OSD_REG_DRAW_X_MIN_05_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_05_LEN) - 1) << OSD_REG_DRAW_X_MIN_05_POS))
#define OSD_REG_DRAW_X_MAX_05             OSD_REG_DRAW_X_MAX_05
#define OSD_REG_DRAW_X_MAX_05_POS         (16U)
#define OSD_REG_DRAW_X_MAX_05_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_05_MSK         (((1U << OSD_REG_DRAW_X_MAX_05_LEN) - 1) << OSD_REG_DRAW_X_MAX_05_POS)
#define OSD_REG_DRAW_X_MAX_05_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_05_LEN) - 1) << OSD_REG_DRAW_X_MAX_05_POS))

/* 0x48 : draw_partial_y_config5 */
#define OSD_DRAW_PARTIAL_Y_CONFIG5_OFFSET (0x48)
#define OSD_REG_DRAW_Y_MIN_05             OSD_REG_DRAW_Y_MIN_05
#define OSD_REG_DRAW_Y_MIN_05_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_05_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_05_MSK         (((1U << OSD_REG_DRAW_Y_MIN_05_LEN) - 1) << OSD_REG_DRAW_Y_MIN_05_POS)
#define OSD_REG_DRAW_Y_MIN_05_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_05_LEN) - 1) << OSD_REG_DRAW_Y_MIN_05_POS))
#define OSD_REG_DRAW_Y_MAX_05             OSD_REG_DRAW_Y_MAX_05
#define OSD_REG_DRAW_Y_MAX_05_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_05_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_05_MSK         (((1U << OSD_REG_DRAW_Y_MAX_05_LEN) - 1) << OSD_REG_DRAW_Y_MAX_05_POS)
#define OSD_REG_DRAW_Y_MAX_05_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_05_LEN) - 1) << OSD_REG_DRAW_Y_MAX_05_POS))

/* 0x4C : draw_partial_yuv_config6 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG6_OFFSET (0x4C)
#define OSD_REG_DRAW_TH_06                  OSD_REG_DRAW_TH_06
#define OSD_REG_DRAW_TH_06_POS              (0U)
#define OSD_REG_DRAW_TH_06_LEN              (8U)
#define OSD_REG_DRAW_TH_06_MSK              (((1U << OSD_REG_DRAW_TH_06_LEN) - 1) << OSD_REG_DRAW_TH_06_POS)
#define OSD_REG_DRAW_TH_06_UMSK             (~(((1U << OSD_REG_DRAW_TH_06_LEN) - 1) << OSD_REG_DRAW_TH_06_POS))
#define OSD_REG_DRAW_V_06                   OSD_REG_DRAW_V_06
#define OSD_REG_DRAW_V_06_POS               (8U)
#define OSD_REG_DRAW_V_06_LEN               (8U)
#define OSD_REG_DRAW_V_06_MSK               (((1U << OSD_REG_DRAW_V_06_LEN) - 1) << OSD_REG_DRAW_V_06_POS)
#define OSD_REG_DRAW_V_06_UMSK              (~(((1U << OSD_REG_DRAW_V_06_LEN) - 1) << OSD_REG_DRAW_V_06_POS))
#define OSD_REG_DRAW_U_06                   OSD_REG_DRAW_U_06
#define OSD_REG_DRAW_U_06_POS               (16U)
#define OSD_REG_DRAW_U_06_LEN               (8U)
#define OSD_REG_DRAW_U_06_MSK               (((1U << OSD_REG_DRAW_U_06_LEN) - 1) << OSD_REG_DRAW_U_06_POS)
#define OSD_REG_DRAW_U_06_UMSK              (~(((1U << OSD_REG_DRAW_U_06_LEN) - 1) << OSD_REG_DRAW_U_06_POS))
#define OSD_REG_DRAW_Y_06                   OSD_REG_DRAW_Y_06
#define OSD_REG_DRAW_Y_06_POS               (24U)
#define OSD_REG_DRAW_Y_06_LEN               (8U)
#define OSD_REG_DRAW_Y_06_MSK               (((1U << OSD_REG_DRAW_Y_06_LEN) - 1) << OSD_REG_DRAW_Y_06_POS)
#define OSD_REG_DRAW_Y_06_UMSK              (~(((1U << OSD_REG_DRAW_Y_06_LEN) - 1) << OSD_REG_DRAW_Y_06_POS))

/* 0x50 : draw_partial_x_config6 */
#define OSD_DRAW_PARTIAL_X_CONFIG6_OFFSET (0x50)
#define OSD_REG_DRAW_X_MIN_06             OSD_REG_DRAW_X_MIN_06
#define OSD_REG_DRAW_X_MIN_06_POS         (0U)
#define OSD_REG_DRAW_X_MIN_06_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_06_MSK         (((1U << OSD_REG_DRAW_X_MIN_06_LEN) - 1) << OSD_REG_DRAW_X_MIN_06_POS)
#define OSD_REG_DRAW_X_MIN_06_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_06_LEN) - 1) << OSD_REG_DRAW_X_MIN_06_POS))
#define OSD_REG_DRAW_X_MAX_06             OSD_REG_DRAW_X_MAX_06
#define OSD_REG_DRAW_X_MAX_06_POS         (16U)
#define OSD_REG_DRAW_X_MAX_06_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_06_MSK         (((1U << OSD_REG_DRAW_X_MAX_06_LEN) - 1) << OSD_REG_DRAW_X_MAX_06_POS)
#define OSD_REG_DRAW_X_MAX_06_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_06_LEN) - 1) << OSD_REG_DRAW_X_MAX_06_POS))

/* 0x54 : draw_partial_y_config6 */
#define OSD_DRAW_PARTIAL_Y_CONFIG6_OFFSET (0x54)
#define OSD_REG_DRAW_Y_MIN_06             OSD_REG_DRAW_Y_MIN_06
#define OSD_REG_DRAW_Y_MIN_06_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_06_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_06_MSK         (((1U << OSD_REG_DRAW_Y_MIN_06_LEN) - 1) << OSD_REG_DRAW_Y_MIN_06_POS)
#define OSD_REG_DRAW_Y_MIN_06_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_06_LEN) - 1) << OSD_REG_DRAW_Y_MIN_06_POS))
#define OSD_REG_DRAW_Y_MAX_06             OSD_REG_DRAW_Y_MAX_06
#define OSD_REG_DRAW_Y_MAX_06_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_06_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_06_MSK         (((1U << OSD_REG_DRAW_Y_MAX_06_LEN) - 1) << OSD_REG_DRAW_Y_MAX_06_POS)
#define OSD_REG_DRAW_Y_MAX_06_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_06_LEN) - 1) << OSD_REG_DRAW_Y_MAX_06_POS))

/* 0x58 : draw_partial_yuv_config7 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG7_OFFSET (0x58)
#define OSD_REG_DRAW_TH_07                  OSD_REG_DRAW_TH_07
#define OSD_REG_DRAW_TH_07_POS              (0U)
#define OSD_REG_DRAW_TH_07_LEN              (8U)
#define OSD_REG_DRAW_TH_07_MSK              (((1U << OSD_REG_DRAW_TH_07_LEN) - 1) << OSD_REG_DRAW_TH_07_POS)
#define OSD_REG_DRAW_TH_07_UMSK             (~(((1U << OSD_REG_DRAW_TH_07_LEN) - 1) << OSD_REG_DRAW_TH_07_POS))
#define OSD_REG_DRAW_V_07                   OSD_REG_DRAW_V_07
#define OSD_REG_DRAW_V_07_POS               (8U)
#define OSD_REG_DRAW_V_07_LEN               (8U)
#define OSD_REG_DRAW_V_07_MSK               (((1U << OSD_REG_DRAW_V_07_LEN) - 1) << OSD_REG_DRAW_V_07_POS)
#define OSD_REG_DRAW_V_07_UMSK              (~(((1U << OSD_REG_DRAW_V_07_LEN) - 1) << OSD_REG_DRAW_V_07_POS))
#define OSD_REG_DRAW_U_07                   OSD_REG_DRAW_U_07
#define OSD_REG_DRAW_U_07_POS               (16U)
#define OSD_REG_DRAW_U_07_LEN               (8U)
#define OSD_REG_DRAW_U_07_MSK               (((1U << OSD_REG_DRAW_U_07_LEN) - 1) << OSD_REG_DRAW_U_07_POS)
#define OSD_REG_DRAW_U_07_UMSK              (~(((1U << OSD_REG_DRAW_U_07_LEN) - 1) << OSD_REG_DRAW_U_07_POS))
#define OSD_REG_DRAW_Y_07                   OSD_REG_DRAW_Y_07
#define OSD_REG_DRAW_Y_07_POS               (24U)
#define OSD_REG_DRAW_Y_07_LEN               (8U)
#define OSD_REG_DRAW_Y_07_MSK               (((1U << OSD_REG_DRAW_Y_07_LEN) - 1) << OSD_REG_DRAW_Y_07_POS)
#define OSD_REG_DRAW_Y_07_UMSK              (~(((1U << OSD_REG_DRAW_Y_07_LEN) - 1) << OSD_REG_DRAW_Y_07_POS))

/* 0x5C : draw_partial_x_config7 */
#define OSD_DRAW_PARTIAL_X_CONFIG7_OFFSET (0x5C)
#define OSD_REG_DRAW_X_MIN_07             OSD_REG_DRAW_X_MIN_07
#define OSD_REG_DRAW_X_MIN_07_POS         (0U)
#define OSD_REG_DRAW_X_MIN_07_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_07_MSK         (((1U << OSD_REG_DRAW_X_MIN_07_LEN) - 1) << OSD_REG_DRAW_X_MIN_07_POS)
#define OSD_REG_DRAW_X_MIN_07_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_07_LEN) - 1) << OSD_REG_DRAW_X_MIN_07_POS))
#define OSD_REG_DRAW_X_MAX_07             OSD_REG_DRAW_X_MAX_07
#define OSD_REG_DRAW_X_MAX_07_POS         (16U)
#define OSD_REG_DRAW_X_MAX_07_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_07_MSK         (((1U << OSD_REG_DRAW_X_MAX_07_LEN) - 1) << OSD_REG_DRAW_X_MAX_07_POS)
#define OSD_REG_DRAW_X_MAX_07_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_07_LEN) - 1) << OSD_REG_DRAW_X_MAX_07_POS))

/* 0x60 : draw_partial_y_config7 */
#define OSD_DRAW_PARTIAL_Y_CONFIG7_OFFSET (0x60)
#define OSD_REG_DRAW_Y_MIN_07             OSD_REG_DRAW_Y_MIN_07
#define OSD_REG_DRAW_Y_MIN_07_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_07_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_07_MSK         (((1U << OSD_REG_DRAW_Y_MIN_07_LEN) - 1) << OSD_REG_DRAW_Y_MIN_07_POS)
#define OSD_REG_DRAW_Y_MIN_07_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_07_LEN) - 1) << OSD_REG_DRAW_Y_MIN_07_POS))
#define OSD_REG_DRAW_Y_MAX_07             OSD_REG_DRAW_Y_MAX_07
#define OSD_REG_DRAW_Y_MAX_07_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_07_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_07_MSK         (((1U << OSD_REG_DRAW_Y_MAX_07_LEN) - 1) << OSD_REG_DRAW_Y_MAX_07_POS)
#define OSD_REG_DRAW_Y_MAX_07_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_07_LEN) - 1) << OSD_REG_DRAW_Y_MAX_07_POS))

/* 0x64 : draw_partial_yuv_config8 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG8_OFFSET (0x64)
#define OSD_REG_DRAW_TH_08                  OSD_REG_DRAW_TH_08
#define OSD_REG_DRAW_TH_08_POS              (0U)
#define OSD_REG_DRAW_TH_08_LEN              (8U)
#define OSD_REG_DRAW_TH_08_MSK              (((1U << OSD_REG_DRAW_TH_08_LEN) - 1) << OSD_REG_DRAW_TH_08_POS)
#define OSD_REG_DRAW_TH_08_UMSK             (~(((1U << OSD_REG_DRAW_TH_08_LEN) - 1) << OSD_REG_DRAW_TH_08_POS))
#define OSD_REG_DRAW_V_08                   OSD_REG_DRAW_V_08
#define OSD_REG_DRAW_V_08_POS               (8U)
#define OSD_REG_DRAW_V_08_LEN               (8U)
#define OSD_REG_DRAW_V_08_MSK               (((1U << OSD_REG_DRAW_V_08_LEN) - 1) << OSD_REG_DRAW_V_08_POS)
#define OSD_REG_DRAW_V_08_UMSK              (~(((1U << OSD_REG_DRAW_V_08_LEN) - 1) << OSD_REG_DRAW_V_08_POS))
#define OSD_REG_DRAW_U_08                   OSD_REG_DRAW_U_08
#define OSD_REG_DRAW_U_08_POS               (16U)
#define OSD_REG_DRAW_U_08_LEN               (8U)
#define OSD_REG_DRAW_U_08_MSK               (((1U << OSD_REG_DRAW_U_08_LEN) - 1) << OSD_REG_DRAW_U_08_POS)
#define OSD_REG_DRAW_U_08_UMSK              (~(((1U << OSD_REG_DRAW_U_08_LEN) - 1) << OSD_REG_DRAW_U_08_POS))
#define OSD_REG_DRAW_Y_08                   OSD_REG_DRAW_Y_08
#define OSD_REG_DRAW_Y_08_POS               (24U)
#define OSD_REG_DRAW_Y_08_LEN               (8U)
#define OSD_REG_DRAW_Y_08_MSK               (((1U << OSD_REG_DRAW_Y_08_LEN) - 1) << OSD_REG_DRAW_Y_08_POS)
#define OSD_REG_DRAW_Y_08_UMSK              (~(((1U << OSD_REG_DRAW_Y_08_LEN) - 1) << OSD_REG_DRAW_Y_08_POS))

/* 0x68 : draw_partial_x_config8 */
#define OSD_DRAW_PARTIAL_X_CONFIG8_OFFSET (0x68)
#define OSD_REG_DRAW_X_MIN_08             OSD_REG_DRAW_X_MIN_08
#define OSD_REG_DRAW_X_MIN_08_POS         (0U)
#define OSD_REG_DRAW_X_MIN_08_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_08_MSK         (((1U << OSD_REG_DRAW_X_MIN_08_LEN) - 1) << OSD_REG_DRAW_X_MIN_08_POS)
#define OSD_REG_DRAW_X_MIN_08_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_08_LEN) - 1) << OSD_REG_DRAW_X_MIN_08_POS))
#define OSD_REG_DRAW_X_MAX_08             OSD_REG_DRAW_X_MAX_08
#define OSD_REG_DRAW_X_MAX_08_POS         (16U)
#define OSD_REG_DRAW_X_MAX_08_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_08_MSK         (((1U << OSD_REG_DRAW_X_MAX_08_LEN) - 1) << OSD_REG_DRAW_X_MAX_08_POS)
#define OSD_REG_DRAW_X_MAX_08_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_08_LEN) - 1) << OSD_REG_DRAW_X_MAX_08_POS))

/* 0x6C : draw_partial_y_config8 */
#define OSD_DRAW_PARTIAL_Y_CONFIG8_OFFSET (0x6C)
#define OSD_REG_DRAW_Y_MIN_08             OSD_REG_DRAW_Y_MIN_08
#define OSD_REG_DRAW_Y_MIN_08_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_08_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_08_MSK         (((1U << OSD_REG_DRAW_Y_MIN_08_LEN) - 1) << OSD_REG_DRAW_Y_MIN_08_POS)
#define OSD_REG_DRAW_Y_MIN_08_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_08_LEN) - 1) << OSD_REG_DRAW_Y_MIN_08_POS))
#define OSD_REG_DRAW_Y_MAX_08             OSD_REG_DRAW_Y_MAX_08
#define OSD_REG_DRAW_Y_MAX_08_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_08_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_08_MSK         (((1U << OSD_REG_DRAW_Y_MAX_08_LEN) - 1) << OSD_REG_DRAW_Y_MAX_08_POS)
#define OSD_REG_DRAW_Y_MAX_08_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_08_LEN) - 1) << OSD_REG_DRAW_Y_MAX_08_POS))

/* 0x70 : draw_partial_yuv_config9 */
#define OSD_DRAW_PARTIAL_YUV_CONFIG9_OFFSET (0x70)
#define OSD_REG_DRAW_TH_09                  OSD_REG_DRAW_TH_09
#define OSD_REG_DRAW_TH_09_POS              (0U)
#define OSD_REG_DRAW_TH_09_LEN              (8U)
#define OSD_REG_DRAW_TH_09_MSK              (((1U << OSD_REG_DRAW_TH_09_LEN) - 1) << OSD_REG_DRAW_TH_09_POS)
#define OSD_REG_DRAW_TH_09_UMSK             (~(((1U << OSD_REG_DRAW_TH_09_LEN) - 1) << OSD_REG_DRAW_TH_09_POS))
#define OSD_REG_DRAW_V_09                   OSD_REG_DRAW_V_09
#define OSD_REG_DRAW_V_09_POS               (8U)
#define OSD_REG_DRAW_V_09_LEN               (8U)
#define OSD_REG_DRAW_V_09_MSK               (((1U << OSD_REG_DRAW_V_09_LEN) - 1) << OSD_REG_DRAW_V_09_POS)
#define OSD_REG_DRAW_V_09_UMSK              (~(((1U << OSD_REG_DRAW_V_09_LEN) - 1) << OSD_REG_DRAW_V_09_POS))
#define OSD_REG_DRAW_U_09                   OSD_REG_DRAW_U_09
#define OSD_REG_DRAW_U_09_POS               (16U)
#define OSD_REG_DRAW_U_09_LEN               (8U)
#define OSD_REG_DRAW_U_09_MSK               (((1U << OSD_REG_DRAW_U_09_LEN) - 1) << OSD_REG_DRAW_U_09_POS)
#define OSD_REG_DRAW_U_09_UMSK              (~(((1U << OSD_REG_DRAW_U_09_LEN) - 1) << OSD_REG_DRAW_U_09_POS))
#define OSD_REG_DRAW_Y_09                   OSD_REG_DRAW_Y_09
#define OSD_REG_DRAW_Y_09_POS               (24U)
#define OSD_REG_DRAW_Y_09_LEN               (8U)
#define OSD_REG_DRAW_Y_09_MSK               (((1U << OSD_REG_DRAW_Y_09_LEN) - 1) << OSD_REG_DRAW_Y_09_POS)
#define OSD_REG_DRAW_Y_09_UMSK              (~(((1U << OSD_REG_DRAW_Y_09_LEN) - 1) << OSD_REG_DRAW_Y_09_POS))

/* 0x74 : draw_partial_x_config9 */
#define OSD_DRAW_PARTIAL_X_CONFIG9_OFFSET (0x74)
#define OSD_REG_DRAW_X_MIN_09             OSD_REG_DRAW_X_MIN_09
#define OSD_REG_DRAW_X_MIN_09_POS         (0U)
#define OSD_REG_DRAW_X_MIN_09_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_09_MSK         (((1U << OSD_REG_DRAW_X_MIN_09_LEN) - 1) << OSD_REG_DRAW_X_MIN_09_POS)
#define OSD_REG_DRAW_X_MIN_09_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_09_LEN) - 1) << OSD_REG_DRAW_X_MIN_09_POS))
#define OSD_REG_DRAW_X_MAX_09             OSD_REG_DRAW_X_MAX_09
#define OSD_REG_DRAW_X_MAX_09_POS         (16U)
#define OSD_REG_DRAW_X_MAX_09_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_09_MSK         (((1U << OSD_REG_DRAW_X_MAX_09_LEN) - 1) << OSD_REG_DRAW_X_MAX_09_POS)
#define OSD_REG_DRAW_X_MAX_09_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_09_LEN) - 1) << OSD_REG_DRAW_X_MAX_09_POS))

/* 0x78 : draw_partial_y_config9 */
#define OSD_DRAW_PARTIAL_Y_CONFIG9_OFFSET (0x78)
#define OSD_REG_DRAW_Y_MIN_09             OSD_REG_DRAW_Y_MIN_09
#define OSD_REG_DRAW_Y_MIN_09_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_09_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_09_MSK         (((1U << OSD_REG_DRAW_Y_MIN_09_LEN) - 1) << OSD_REG_DRAW_Y_MIN_09_POS)
#define OSD_REG_DRAW_Y_MIN_09_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_09_LEN) - 1) << OSD_REG_DRAW_Y_MIN_09_POS))
#define OSD_REG_DRAW_Y_MAX_09             OSD_REG_DRAW_Y_MAX_09
#define OSD_REG_DRAW_Y_MAX_09_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_09_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_09_MSK         (((1U << OSD_REG_DRAW_Y_MAX_09_LEN) - 1) << OSD_REG_DRAW_Y_MAX_09_POS)
#define OSD_REG_DRAW_Y_MAX_09_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_09_LEN) - 1) << OSD_REG_DRAW_Y_MAX_09_POS))

/* 0x7C : draw_partial_yuv_configa */
#define OSD_DRAW_PARTIAL_YUV_CONFIGA_OFFSET (0x7C)
#define OSD_REG_DRAW_TH_0A                  OSD_REG_DRAW_TH_0A
#define OSD_REG_DRAW_TH_0A_POS              (0U)
#define OSD_REG_DRAW_TH_0A_LEN              (8U)
#define OSD_REG_DRAW_TH_0A_MSK              (((1U << OSD_REG_DRAW_TH_0A_LEN) - 1) << OSD_REG_DRAW_TH_0A_POS)
#define OSD_REG_DRAW_TH_0A_UMSK             (~(((1U << OSD_REG_DRAW_TH_0A_LEN) - 1) << OSD_REG_DRAW_TH_0A_POS))
#define OSD_REG_DRAW_V_0A                   OSD_REG_DRAW_V_0A
#define OSD_REG_DRAW_V_0A_POS               (8U)
#define OSD_REG_DRAW_V_0A_LEN               (8U)
#define OSD_REG_DRAW_V_0A_MSK               (((1U << OSD_REG_DRAW_V_0A_LEN) - 1) << OSD_REG_DRAW_V_0A_POS)
#define OSD_REG_DRAW_V_0A_UMSK              (~(((1U << OSD_REG_DRAW_V_0A_LEN) - 1) << OSD_REG_DRAW_V_0A_POS))
#define OSD_REG_DRAW_U_0A                   OSD_REG_DRAW_U_0A
#define OSD_REG_DRAW_U_0A_POS               (16U)
#define OSD_REG_DRAW_U_0A_LEN               (8U)
#define OSD_REG_DRAW_U_0A_MSK               (((1U << OSD_REG_DRAW_U_0A_LEN) - 1) << OSD_REG_DRAW_U_0A_POS)
#define OSD_REG_DRAW_U_0A_UMSK              (~(((1U << OSD_REG_DRAW_U_0A_LEN) - 1) << OSD_REG_DRAW_U_0A_POS))
#define OSD_REG_DRAW_Y_0A                   OSD_REG_DRAW_Y_0A
#define OSD_REG_DRAW_Y_0A_POS               (24U)
#define OSD_REG_DRAW_Y_0A_LEN               (8U)
#define OSD_REG_DRAW_Y_0A_MSK               (((1U << OSD_REG_DRAW_Y_0A_LEN) - 1) << OSD_REG_DRAW_Y_0A_POS)
#define OSD_REG_DRAW_Y_0A_UMSK              (~(((1U << OSD_REG_DRAW_Y_0A_LEN) - 1) << OSD_REG_DRAW_Y_0A_POS))

/* 0x80 : draw_partial_x_configa */
#define OSD_DRAW_PARTIAL_X_CONFIGA_OFFSET (0x80)
#define OSD_REG_DRAW_X_MIN_0A             OSD_REG_DRAW_X_MIN_0A
#define OSD_REG_DRAW_X_MIN_0A_POS         (0U)
#define OSD_REG_DRAW_X_MIN_0A_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_0A_MSK         (((1U << OSD_REG_DRAW_X_MIN_0A_LEN) - 1) << OSD_REG_DRAW_X_MIN_0A_POS)
#define OSD_REG_DRAW_X_MIN_0A_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_0A_LEN) - 1) << OSD_REG_DRAW_X_MIN_0A_POS))
#define OSD_REG_DRAW_X_MAX_0A             OSD_REG_DRAW_X_MAX_0A
#define OSD_REG_DRAW_X_MAX_0A_POS         (16U)
#define OSD_REG_DRAW_X_MAX_0A_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_0A_MSK         (((1U << OSD_REG_DRAW_X_MAX_0A_LEN) - 1) << OSD_REG_DRAW_X_MAX_0A_POS)
#define OSD_REG_DRAW_X_MAX_0A_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_0A_LEN) - 1) << OSD_REG_DRAW_X_MAX_0A_POS))

/* 0x84 : draw_partial_y_configa */
#define OSD_DRAW_PARTIAL_Y_CONFIGA_OFFSET (0x84)
#define OSD_REG_DRAW_Y_MIN_0A             OSD_REG_DRAW_Y_MIN_0A
#define OSD_REG_DRAW_Y_MIN_0A_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_0A_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_0A_MSK         (((1U << OSD_REG_DRAW_Y_MIN_0A_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0A_POS)
#define OSD_REG_DRAW_Y_MIN_0A_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_0A_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0A_POS))
#define OSD_REG_DRAW_Y_MAX_0A             OSD_REG_DRAW_Y_MAX_0A
#define OSD_REG_DRAW_Y_MAX_0A_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_0A_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_0A_MSK         (((1U << OSD_REG_DRAW_Y_MAX_0A_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0A_POS)
#define OSD_REG_DRAW_Y_MAX_0A_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_0A_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0A_POS))

/* 0x88 : draw_partial_yuv_configb */
#define OSD_DRAW_PARTIAL_YUV_CONFIGB_OFFSET (0x88)
#define OSD_REG_DRAW_TH_0B                  OSD_REG_DRAW_TH_0B
#define OSD_REG_DRAW_TH_0B_POS              (0U)
#define OSD_REG_DRAW_TH_0B_LEN              (8U)
#define OSD_REG_DRAW_TH_0B_MSK              (((1U << OSD_REG_DRAW_TH_0B_LEN) - 1) << OSD_REG_DRAW_TH_0B_POS)
#define OSD_REG_DRAW_TH_0B_UMSK             (~(((1U << OSD_REG_DRAW_TH_0B_LEN) - 1) << OSD_REG_DRAW_TH_0B_POS))
#define OSD_REG_DRAW_V_0B                   OSD_REG_DRAW_V_0B
#define OSD_REG_DRAW_V_0B_POS               (8U)
#define OSD_REG_DRAW_V_0B_LEN               (8U)
#define OSD_REG_DRAW_V_0B_MSK               (((1U << OSD_REG_DRAW_V_0B_LEN) - 1) << OSD_REG_DRAW_V_0B_POS)
#define OSD_REG_DRAW_V_0B_UMSK              (~(((1U << OSD_REG_DRAW_V_0B_LEN) - 1) << OSD_REG_DRAW_V_0B_POS))
#define OSD_REG_DRAW_U_0B                   OSD_REG_DRAW_U_0B
#define OSD_REG_DRAW_U_0B_POS               (16U)
#define OSD_REG_DRAW_U_0B_LEN               (8U)
#define OSD_REG_DRAW_U_0B_MSK               (((1U << OSD_REG_DRAW_U_0B_LEN) - 1) << OSD_REG_DRAW_U_0B_POS)
#define OSD_REG_DRAW_U_0B_UMSK              (~(((1U << OSD_REG_DRAW_U_0B_LEN) - 1) << OSD_REG_DRAW_U_0B_POS))
#define OSD_REG_DRAW_Y_0B                   OSD_REG_DRAW_Y_0B
#define OSD_REG_DRAW_Y_0B_POS               (24U)
#define OSD_REG_DRAW_Y_0B_LEN               (8U)
#define OSD_REG_DRAW_Y_0B_MSK               (((1U << OSD_REG_DRAW_Y_0B_LEN) - 1) << OSD_REG_DRAW_Y_0B_POS)
#define OSD_REG_DRAW_Y_0B_UMSK              (~(((1U << OSD_REG_DRAW_Y_0B_LEN) - 1) << OSD_REG_DRAW_Y_0B_POS))

/* 0x8C : draw_partial_x_configb */
#define OSD_DRAW_PARTIAL_X_CONFIGB_OFFSET (0x8C)
#define OSD_REG_DRAW_X_MIN_0B             OSD_REG_DRAW_X_MIN_0B
#define OSD_REG_DRAW_X_MIN_0B_POS         (0U)
#define OSD_REG_DRAW_X_MIN_0B_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_0B_MSK         (((1U << OSD_REG_DRAW_X_MIN_0B_LEN) - 1) << OSD_REG_DRAW_X_MIN_0B_POS)
#define OSD_REG_DRAW_X_MIN_0B_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_0B_LEN) - 1) << OSD_REG_DRAW_X_MIN_0B_POS))
#define OSD_REG_DRAW_X_MAX_0B             OSD_REG_DRAW_X_MAX_0B
#define OSD_REG_DRAW_X_MAX_0B_POS         (16U)
#define OSD_REG_DRAW_X_MAX_0B_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_0B_MSK         (((1U << OSD_REG_DRAW_X_MAX_0B_LEN) - 1) << OSD_REG_DRAW_X_MAX_0B_POS)
#define OSD_REG_DRAW_X_MAX_0B_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_0B_LEN) - 1) << OSD_REG_DRAW_X_MAX_0B_POS))

/* 0x90 : draw_partial_y_configb */
#define OSD_DRAW_PARTIAL_Y_CONFIGB_OFFSET (0x90)
#define OSD_REG_DRAW_Y_MIN_0B             OSD_REG_DRAW_Y_MIN_0B
#define OSD_REG_DRAW_Y_MIN_0B_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_0B_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_0B_MSK         (((1U << OSD_REG_DRAW_Y_MIN_0B_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0B_POS)
#define OSD_REG_DRAW_Y_MIN_0B_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_0B_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0B_POS))
#define OSD_REG_DRAW_Y_MAX_0B             OSD_REG_DRAW_Y_MAX_0B
#define OSD_REG_DRAW_Y_MAX_0B_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_0B_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_0B_MSK         (((1U << OSD_REG_DRAW_Y_MAX_0B_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0B_POS)
#define OSD_REG_DRAW_Y_MAX_0B_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_0B_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0B_POS))

/* 0x94 : draw_partial_yuv_configc */
#define OSD_DRAW_PARTIAL_YUV_CONFIGC_OFFSET (0x94)
#define OSD_REG_DRAW_TH_0C                  OSD_REG_DRAW_TH_0C
#define OSD_REG_DRAW_TH_0C_POS              (0U)
#define OSD_REG_DRAW_TH_0C_LEN              (8U)
#define OSD_REG_DRAW_TH_0C_MSK              (((1U << OSD_REG_DRAW_TH_0C_LEN) - 1) << OSD_REG_DRAW_TH_0C_POS)
#define OSD_REG_DRAW_TH_0C_UMSK             (~(((1U << OSD_REG_DRAW_TH_0C_LEN) - 1) << OSD_REG_DRAW_TH_0C_POS))
#define OSD_REG_DRAW_V_0C                   OSD_REG_DRAW_V_0C
#define OSD_REG_DRAW_V_0C_POS               (8U)
#define OSD_REG_DRAW_V_0C_LEN               (8U)
#define OSD_REG_DRAW_V_0C_MSK               (((1U << OSD_REG_DRAW_V_0C_LEN) - 1) << OSD_REG_DRAW_V_0C_POS)
#define OSD_REG_DRAW_V_0C_UMSK              (~(((1U << OSD_REG_DRAW_V_0C_LEN) - 1) << OSD_REG_DRAW_V_0C_POS))
#define OSD_REG_DRAW_U_0C                   OSD_REG_DRAW_U_0C
#define OSD_REG_DRAW_U_0C_POS               (16U)
#define OSD_REG_DRAW_U_0C_LEN               (8U)
#define OSD_REG_DRAW_U_0C_MSK               (((1U << OSD_REG_DRAW_U_0C_LEN) - 1) << OSD_REG_DRAW_U_0C_POS)
#define OSD_REG_DRAW_U_0C_UMSK              (~(((1U << OSD_REG_DRAW_U_0C_LEN) - 1) << OSD_REG_DRAW_U_0C_POS))
#define OSD_REG_DRAW_Y_0C                   OSD_REG_DRAW_Y_0C
#define OSD_REG_DRAW_Y_0C_POS               (24U)
#define OSD_REG_DRAW_Y_0C_LEN               (8U)
#define OSD_REG_DRAW_Y_0C_MSK               (((1U << OSD_REG_DRAW_Y_0C_LEN) - 1) << OSD_REG_DRAW_Y_0C_POS)
#define OSD_REG_DRAW_Y_0C_UMSK              (~(((1U << OSD_REG_DRAW_Y_0C_LEN) - 1) << OSD_REG_DRAW_Y_0C_POS))

/* 0x98 : draw_partial_x_configc */
#define OSD_DRAW_PARTIAL_X_CONFIGC_OFFSET (0x98)
#define OSD_REG_DRAW_X_MIN_0C             OSD_REG_DRAW_X_MIN_0C
#define OSD_REG_DRAW_X_MIN_0C_POS         (0U)
#define OSD_REG_DRAW_X_MIN_0C_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_0C_MSK         (((1U << OSD_REG_DRAW_X_MIN_0C_LEN) - 1) << OSD_REG_DRAW_X_MIN_0C_POS)
#define OSD_REG_DRAW_X_MIN_0C_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_0C_LEN) - 1) << OSD_REG_DRAW_X_MIN_0C_POS))
#define OSD_REG_DRAW_X_MAX_0C             OSD_REG_DRAW_X_MAX_0C
#define OSD_REG_DRAW_X_MAX_0C_POS         (16U)
#define OSD_REG_DRAW_X_MAX_0C_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_0C_MSK         (((1U << OSD_REG_DRAW_X_MAX_0C_LEN) - 1) << OSD_REG_DRAW_X_MAX_0C_POS)
#define OSD_REG_DRAW_X_MAX_0C_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_0C_LEN) - 1) << OSD_REG_DRAW_X_MAX_0C_POS))

/* 0x9C : draw_partial_y_configc */
#define OSD_DRAW_PARTIAL_Y_CONFIGC_OFFSET (0x9C)
#define OSD_REG_DRAW_Y_MIN_0C             OSD_REG_DRAW_Y_MIN_0C
#define OSD_REG_DRAW_Y_MIN_0C_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_0C_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_0C_MSK         (((1U << OSD_REG_DRAW_Y_MIN_0C_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0C_POS)
#define OSD_REG_DRAW_Y_MIN_0C_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_0C_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0C_POS))
#define OSD_REG_DRAW_Y_MAX_0C             OSD_REG_DRAW_Y_MAX_0C
#define OSD_REG_DRAW_Y_MAX_0C_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_0C_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_0C_MSK         (((1U << OSD_REG_DRAW_Y_MAX_0C_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0C_POS)
#define OSD_REG_DRAW_Y_MAX_0C_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_0C_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0C_POS))

/* 0xA0 : draw_partial_yuv_configd */
#define OSD_DRAW_PARTIAL_YUV_CONFIGD_OFFSET (0xA0)
#define OSD_REG_DRAW_TH_0D                  OSD_REG_DRAW_TH_0D
#define OSD_REG_DRAW_TH_0D_POS              (0U)
#define OSD_REG_DRAW_TH_0D_LEN              (8U)
#define OSD_REG_DRAW_TH_0D_MSK              (((1U << OSD_REG_DRAW_TH_0D_LEN) - 1) << OSD_REG_DRAW_TH_0D_POS)
#define OSD_REG_DRAW_TH_0D_UMSK             (~(((1U << OSD_REG_DRAW_TH_0D_LEN) - 1) << OSD_REG_DRAW_TH_0D_POS))
#define OSD_REG_DRAW_V_0D                   OSD_REG_DRAW_V_0D
#define OSD_REG_DRAW_V_0D_POS               (8U)
#define OSD_REG_DRAW_V_0D_LEN               (8U)
#define OSD_REG_DRAW_V_0D_MSK               (((1U << OSD_REG_DRAW_V_0D_LEN) - 1) << OSD_REG_DRAW_V_0D_POS)
#define OSD_REG_DRAW_V_0D_UMSK              (~(((1U << OSD_REG_DRAW_V_0D_LEN) - 1) << OSD_REG_DRAW_V_0D_POS))
#define OSD_REG_DRAW_U_0D                   OSD_REG_DRAW_U_0D
#define OSD_REG_DRAW_U_0D_POS               (16U)
#define OSD_REG_DRAW_U_0D_LEN               (8U)
#define OSD_REG_DRAW_U_0D_MSK               (((1U << OSD_REG_DRAW_U_0D_LEN) - 1) << OSD_REG_DRAW_U_0D_POS)
#define OSD_REG_DRAW_U_0D_UMSK              (~(((1U << OSD_REG_DRAW_U_0D_LEN) - 1) << OSD_REG_DRAW_U_0D_POS))
#define OSD_REG_DRAW_Y_0D                   OSD_REG_DRAW_Y_0D
#define OSD_REG_DRAW_Y_0D_POS               (24U)
#define OSD_REG_DRAW_Y_0D_LEN               (8U)
#define OSD_REG_DRAW_Y_0D_MSK               (((1U << OSD_REG_DRAW_Y_0D_LEN) - 1) << OSD_REG_DRAW_Y_0D_POS)
#define OSD_REG_DRAW_Y_0D_UMSK              (~(((1U << OSD_REG_DRAW_Y_0D_LEN) - 1) << OSD_REG_DRAW_Y_0D_POS))

/* 0xA4 : draw_partial_x_configd */
#define OSD_DRAW_PARTIAL_X_CONFIGD_OFFSET (0xA4)
#define OSD_REG_DRAW_X_MIN_0D             OSD_REG_DRAW_X_MIN_0D
#define OSD_REG_DRAW_X_MIN_0D_POS         (0U)
#define OSD_REG_DRAW_X_MIN_0D_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_0D_MSK         (((1U << OSD_REG_DRAW_X_MIN_0D_LEN) - 1) << OSD_REG_DRAW_X_MIN_0D_POS)
#define OSD_REG_DRAW_X_MIN_0D_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_0D_LEN) - 1) << OSD_REG_DRAW_X_MIN_0D_POS))
#define OSD_REG_DRAW_X_MAX_0D             OSD_REG_DRAW_X_MAX_0D
#define OSD_REG_DRAW_X_MAX_0D_POS         (16U)
#define OSD_REG_DRAW_X_MAX_0D_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_0D_MSK         (((1U << OSD_REG_DRAW_X_MAX_0D_LEN) - 1) << OSD_REG_DRAW_X_MAX_0D_POS)
#define OSD_REG_DRAW_X_MAX_0D_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_0D_LEN) - 1) << OSD_REG_DRAW_X_MAX_0D_POS))

/* 0xA8 : draw_partial_y_configd */
#define OSD_DRAW_PARTIAL_Y_CONFIGD_OFFSET (0xA8)
#define OSD_REG_DRAW_Y_MIN_0D             OSD_REG_DRAW_Y_MIN_0D
#define OSD_REG_DRAW_Y_MIN_0D_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_0D_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_0D_MSK         (((1U << OSD_REG_DRAW_Y_MIN_0D_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0D_POS)
#define OSD_REG_DRAW_Y_MIN_0D_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_0D_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0D_POS))
#define OSD_REG_DRAW_Y_MAX_0D             OSD_REG_DRAW_Y_MAX_0D
#define OSD_REG_DRAW_Y_MAX_0D_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_0D_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_0D_MSK         (((1U << OSD_REG_DRAW_Y_MAX_0D_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0D_POS)
#define OSD_REG_DRAW_Y_MAX_0D_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_0D_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0D_POS))

/* 0xAC : draw_partial_yuv_confige */
#define OSD_DRAW_PARTIAL_YUV_CONFIGE_OFFSET (0xAC)
#define OSD_REG_DRAW_TH_0E                  OSD_REG_DRAW_TH_0E
#define OSD_REG_DRAW_TH_0E_POS              (0U)
#define OSD_REG_DRAW_TH_0E_LEN              (8U)
#define OSD_REG_DRAW_TH_0E_MSK              (((1U << OSD_REG_DRAW_TH_0E_LEN) - 1) << OSD_REG_DRAW_TH_0E_POS)
#define OSD_REG_DRAW_TH_0E_UMSK             (~(((1U << OSD_REG_DRAW_TH_0E_LEN) - 1) << OSD_REG_DRAW_TH_0E_POS))
#define OSD_REG_DRAW_V_0E                   OSD_REG_DRAW_V_0E
#define OSD_REG_DRAW_V_0E_POS               (8U)
#define OSD_REG_DRAW_V_0E_LEN               (8U)
#define OSD_REG_DRAW_V_0E_MSK               (((1U << OSD_REG_DRAW_V_0E_LEN) - 1) << OSD_REG_DRAW_V_0E_POS)
#define OSD_REG_DRAW_V_0E_UMSK              (~(((1U << OSD_REG_DRAW_V_0E_LEN) - 1) << OSD_REG_DRAW_V_0E_POS))
#define OSD_REG_DRAW_U_0E                   OSD_REG_DRAW_U_0E
#define OSD_REG_DRAW_U_0E_POS               (16U)
#define OSD_REG_DRAW_U_0E_LEN               (8U)
#define OSD_REG_DRAW_U_0E_MSK               (((1U << OSD_REG_DRAW_U_0E_LEN) - 1) << OSD_REG_DRAW_U_0E_POS)
#define OSD_REG_DRAW_U_0E_UMSK              (~(((1U << OSD_REG_DRAW_U_0E_LEN) - 1) << OSD_REG_DRAW_U_0E_POS))
#define OSD_REG_DRAW_Y_0E                   OSD_REG_DRAW_Y_0E
#define OSD_REG_DRAW_Y_0E_POS               (24U)
#define OSD_REG_DRAW_Y_0E_LEN               (8U)
#define OSD_REG_DRAW_Y_0E_MSK               (((1U << OSD_REG_DRAW_Y_0E_LEN) - 1) << OSD_REG_DRAW_Y_0E_POS)
#define OSD_REG_DRAW_Y_0E_UMSK              (~(((1U << OSD_REG_DRAW_Y_0E_LEN) - 1) << OSD_REG_DRAW_Y_0E_POS))

/* 0xB0 : draw_partial_x_confige */
#define OSD_DRAW_PARTIAL_X_CONFIGE_OFFSET (0xB0)
#define OSD_REG_DRAW_X_MIN_0E             OSD_REG_DRAW_X_MIN_0E
#define OSD_REG_DRAW_X_MIN_0E_POS         (0U)
#define OSD_REG_DRAW_X_MIN_0E_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_0E_MSK         (((1U << OSD_REG_DRAW_X_MIN_0E_LEN) - 1) << OSD_REG_DRAW_X_MIN_0E_POS)
#define OSD_REG_DRAW_X_MIN_0E_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_0E_LEN) - 1) << OSD_REG_DRAW_X_MIN_0E_POS))
#define OSD_REG_DRAW_X_MAX_0E             OSD_REG_DRAW_X_MAX_0E
#define OSD_REG_DRAW_X_MAX_0E_POS         (16U)
#define OSD_REG_DRAW_X_MAX_0E_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_0E_MSK         (((1U << OSD_REG_DRAW_X_MAX_0E_LEN) - 1) << OSD_REG_DRAW_X_MAX_0E_POS)
#define OSD_REG_DRAW_X_MAX_0E_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_0E_LEN) - 1) << OSD_REG_DRAW_X_MAX_0E_POS))

/* 0xB4 : draw_partial_y_confige */
#define OSD_DRAW_PARTIAL_Y_CONFIGE_OFFSET (0xB4)
#define OSD_REG_DRAW_Y_MIN_0E             OSD_REG_DRAW_Y_MIN_0E
#define OSD_REG_DRAW_Y_MIN_0E_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_0E_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_0E_MSK         (((1U << OSD_REG_DRAW_Y_MIN_0E_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0E_POS)
#define OSD_REG_DRAW_Y_MIN_0E_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_0E_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0E_POS))
#define OSD_REG_DRAW_Y_MAX_0E             OSD_REG_DRAW_Y_MAX_0E
#define OSD_REG_DRAW_Y_MAX_0E_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_0E_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_0E_MSK         (((1U << OSD_REG_DRAW_Y_MAX_0E_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0E_POS)
#define OSD_REG_DRAW_Y_MAX_0E_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_0E_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0E_POS))

/* 0xB8 : draw_partial_yuv_configf */
#define OSD_DRAW_PARTIAL_YUV_CONFIGF_OFFSET (0xB8)
#define OSD_REG_DRAW_TH_0F                  OSD_REG_DRAW_TH_0F
#define OSD_REG_DRAW_TH_0F_POS              (0U)
#define OSD_REG_DRAW_TH_0F_LEN              (8U)
#define OSD_REG_DRAW_TH_0F_MSK              (((1U << OSD_REG_DRAW_TH_0F_LEN) - 1) << OSD_REG_DRAW_TH_0F_POS)
#define OSD_REG_DRAW_TH_0F_UMSK             (~(((1U << OSD_REG_DRAW_TH_0F_LEN) - 1) << OSD_REG_DRAW_TH_0F_POS))
#define OSD_REG_DRAW_V_0F                   OSD_REG_DRAW_V_0F
#define OSD_REG_DRAW_V_0F_POS               (8U)
#define OSD_REG_DRAW_V_0F_LEN               (8U)
#define OSD_REG_DRAW_V_0F_MSK               (((1U << OSD_REG_DRAW_V_0F_LEN) - 1) << OSD_REG_DRAW_V_0F_POS)
#define OSD_REG_DRAW_V_0F_UMSK              (~(((1U << OSD_REG_DRAW_V_0F_LEN) - 1) << OSD_REG_DRAW_V_0F_POS))
#define OSD_REG_DRAW_U_0F                   OSD_REG_DRAW_U_0F
#define OSD_REG_DRAW_U_0F_POS               (16U)
#define OSD_REG_DRAW_U_0F_LEN               (8U)
#define OSD_REG_DRAW_U_0F_MSK               (((1U << OSD_REG_DRAW_U_0F_LEN) - 1) << OSD_REG_DRAW_U_0F_POS)
#define OSD_REG_DRAW_U_0F_UMSK              (~(((1U << OSD_REG_DRAW_U_0F_LEN) - 1) << OSD_REG_DRAW_U_0F_POS))
#define OSD_REG_DRAW_Y_0F                   OSD_REG_DRAW_Y_0F
#define OSD_REG_DRAW_Y_0F_POS               (24U)
#define OSD_REG_DRAW_Y_0F_LEN               (8U)
#define OSD_REG_DRAW_Y_0F_MSK               (((1U << OSD_REG_DRAW_Y_0F_LEN) - 1) << OSD_REG_DRAW_Y_0F_POS)
#define OSD_REG_DRAW_Y_0F_UMSK              (~(((1U << OSD_REG_DRAW_Y_0F_LEN) - 1) << OSD_REG_DRAW_Y_0F_POS))

/* 0xBC : draw_partial_x_configf */
#define OSD_DRAW_PARTIAL_X_CONFIGF_OFFSET (0xBC)
#define OSD_REG_DRAW_X_MIN_0F             OSD_REG_DRAW_X_MIN_0F
#define OSD_REG_DRAW_X_MIN_0F_POS         (0U)
#define OSD_REG_DRAW_X_MIN_0F_LEN         (11U)
#define OSD_REG_DRAW_X_MIN_0F_MSK         (((1U << OSD_REG_DRAW_X_MIN_0F_LEN) - 1) << OSD_REG_DRAW_X_MIN_0F_POS)
#define OSD_REG_DRAW_X_MIN_0F_UMSK        (~(((1U << OSD_REG_DRAW_X_MIN_0F_LEN) - 1) << OSD_REG_DRAW_X_MIN_0F_POS))
#define OSD_REG_DRAW_X_MAX_0F             OSD_REG_DRAW_X_MAX_0F
#define OSD_REG_DRAW_X_MAX_0F_POS         (16U)
#define OSD_REG_DRAW_X_MAX_0F_LEN         (11U)
#define OSD_REG_DRAW_X_MAX_0F_MSK         (((1U << OSD_REG_DRAW_X_MAX_0F_LEN) - 1) << OSD_REG_DRAW_X_MAX_0F_POS)
#define OSD_REG_DRAW_X_MAX_0F_UMSK        (~(((1U << OSD_REG_DRAW_X_MAX_0F_LEN) - 1) << OSD_REG_DRAW_X_MAX_0F_POS))

/* 0xC0 : draw_partial_y_configf */
#define OSD_DRAW_PARTIAL_Y_CONFIGF_OFFSET (0xC0)
#define OSD_REG_DRAW_Y_MIN_0F             OSD_REG_DRAW_Y_MIN_0F
#define OSD_REG_DRAW_Y_MIN_0F_POS         (0U)
#define OSD_REG_DRAW_Y_MIN_0F_LEN         (11U)
#define OSD_REG_DRAW_Y_MIN_0F_MSK         (((1U << OSD_REG_DRAW_Y_MIN_0F_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0F_POS)
#define OSD_REG_DRAW_Y_MIN_0F_UMSK        (~(((1U << OSD_REG_DRAW_Y_MIN_0F_LEN) - 1) << OSD_REG_DRAW_Y_MIN_0F_POS))
#define OSD_REG_DRAW_Y_MAX_0F             OSD_REG_DRAW_Y_MAX_0F
#define OSD_REG_DRAW_Y_MAX_0F_POS         (16U)
#define OSD_REG_DRAW_Y_MAX_0F_LEN         (11U)
#define OSD_REG_DRAW_Y_MAX_0F_MSK         (((1U << OSD_REG_DRAW_Y_MAX_0F_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0F_POS)
#define OSD_REG_DRAW_Y_MAX_0F_UMSK        (~(((1U << OSD_REG_DRAW_Y_MAX_0F_LEN) - 1) << OSD_REG_DRAW_Y_MAX_0F_POS))

/* 0xF8 : osd_int_sts */
#define OSD_DRAW_INT_STS_OFFSET           (0xF8)
#define OSD_DRAW_REG_SEOF_INT_CLR_W       OSD_DRAW_REG_SEOF_INT_CLR_W
#define OSD_DRAW_REG_SEOF_INT_CLR_W_POS   (0U)
#define OSD_DRAW_REG_SEOF_INT_CLR_W_LEN   (1U)
#define OSD_DRAW_REG_SEOF_INT_CLR_W_MSK   (((1U << OSD_DRAW_REG_SEOF_INT_CLR_W_LEN) - 1) << OSD_DRAW_REG_SEOF_INT_CLR_W_POS)
#define OSD_DRAW_REG_SEOF_INT_CLR_W_UMSK  (~(((1U << OSD_DRAW_REG_SEOF_INT_CLR_W_LEN) - 1) << OSD_DRAW_REG_SEOF_INT_CLR_W_POS))
#define OSD_DRAW_REG_SEOF_INT_MASK_W      OSD_DRAW_REG_SEOF_INT_MASK_W
#define OSD_DRAW_REG_SEOF_INT_MASK_W_POS  (1U)
#define OSD_DRAW_REG_SEOF_INT_MASK_W_LEN  (1U)
#define OSD_DRAW_REG_SEOF_INT_MASK_W_MSK  (((1U << OSD_DRAW_REG_SEOF_INT_MASK_W_LEN) - 1) << OSD_DRAW_REG_SEOF_INT_MASK_W_POS)
#define OSD_DRAW_REG_SEOF_INT_MASK_W_UMSK (~(((1U << OSD_DRAW_REG_SEOF_INT_MASK_W_LEN) - 1) << OSD_DRAW_REG_SEOF_INT_MASK_W_POS))
#define OSD_DRAW_REG_SEOF_INT_EDGE_W      OSD_DRAW_REG_SEOF_INT_EDGE_W
#define OSD_DRAW_REG_SEOF_INT_EDGE_W_POS  (2U)
#define OSD_DRAW_REG_SEOF_INT_EDGE_W_LEN  (1U)
#define OSD_DRAW_REG_SEOF_INT_EDGE_W_MSK  (((1U << OSD_DRAW_REG_SEOF_INT_EDGE_W_LEN) - 1) << OSD_DRAW_REG_SEOF_INT_EDGE_W_POS)
#define OSD_DRAW_REG_SEOF_INT_EDGE_W_UMSK (~(((1U << OSD_DRAW_REG_SEOF_INT_EDGE_W_LEN) - 1) << OSD_DRAW_REG_SEOF_INT_EDGE_W_POS))
#define OSD_DRAW_STS_DRAIN_INT_R          OSD_DRAW_STS_DRAIN_INT_R
#define OSD_DRAW_STS_DRAIN_INT_R_POS      (16U)
#define OSD_DRAW_STS_DRAIN_INT_R_LEN      (4U)
#define OSD_DRAW_STS_DRAIN_INT_R_MSK      (((1U << OSD_DRAW_STS_DRAIN_INT_R_LEN) - 1) << OSD_DRAW_STS_DRAIN_INT_R_POS)
#define OSD_DRAW_STS_DRAIN_INT_R_UMSK     (~(((1U << OSD_DRAW_STS_DRAIN_INT_R_LEN) - 1) << OSD_DRAW_STS_DRAIN_INT_R_POS))
#define OSD_DRAW_STS_SEOF_INT_R           OSD_DRAW_STS_SEOF_INT_R
#define OSD_DRAW_STS_SEOF_INT_R_POS       (20U)
#define OSD_DRAW_STS_SEOF_INT_R_LEN       (1U)
#define OSD_DRAW_STS_SEOF_INT_R_MSK       (((1U << OSD_DRAW_STS_SEOF_INT_R_LEN) - 1) << OSD_DRAW_STS_SEOF_INT_R_POS)
#define OSD_DRAW_STS_SEOF_INT_R_UMSK      (~(((1U << OSD_DRAW_STS_SEOF_INT_R_LEN) - 1) << OSD_DRAW_STS_SEOF_INT_R_POS))

/* 0xFC : osd_misc */
#define OSD_DRAW_MISC_OFFSET              (0xFC)
#define OSD_DRAW_REG_BUS_STRT_W           OSD_DRAW_REG_BUS_STRT_W
#define OSD_DRAW_REG_BUS_STRT_W_POS       (0U)
#define OSD_DRAW_REG_BUS_STRT_W_LEN       (1U)
#define OSD_DRAW_REG_BUS_STRT_W_MSK       (((1U << OSD_DRAW_REG_BUS_STRT_W_LEN) - 1) << OSD_DRAW_REG_BUS_STRT_W_POS)
#define OSD_DRAW_REG_BUS_STRT_W_UMSK      (~(((1U << OSD_DRAW_REG_BUS_STRT_W_LEN) - 1) << OSD_DRAW_REG_BUS_STRT_W_POS))
#define OSD_DRAW_REG_FIFO_AUTO_CLR_W      OSD_DRAW_REG_FIFO_AUTO_CLR_W
#define OSD_DRAW_REG_FIFO_AUTO_CLR_W_POS  (1U)
#define OSD_DRAW_REG_FIFO_AUTO_CLR_W_LEN  (1U)
#define OSD_DRAW_REG_FIFO_AUTO_CLR_W_MSK  (((1U << OSD_DRAW_REG_FIFO_AUTO_CLR_W_LEN) - 1) << OSD_DRAW_REG_FIFO_AUTO_CLR_W_POS)
#define OSD_DRAW_REG_FIFO_AUTO_CLR_W_UMSK (~(((1U << OSD_DRAW_REG_FIFO_AUTO_CLR_W_LEN) - 1) << OSD_DRAW_REG_FIFO_AUTO_CLR_W_POS))
#define OSD_DRAW_REG_QOS_SW_MODE_W        OSD_DRAW_REG_QOS_SW_MODE_W
#define OSD_DRAW_REG_QOS_SW_MODE_W_POS    (4U)
#define OSD_DRAW_REG_QOS_SW_MODE_W_LEN    (1U)
#define OSD_DRAW_REG_QOS_SW_MODE_W_MSK    (((1U << OSD_DRAW_REG_QOS_SW_MODE_W_LEN) - 1) << OSD_DRAW_REG_QOS_SW_MODE_W_POS)
#define OSD_DRAW_REG_QOS_SW_MODE_W_UMSK   (~(((1U << OSD_DRAW_REG_QOS_SW_MODE_W_LEN) - 1) << OSD_DRAW_REG_QOS_SW_MODE_W_POS))
#define OSD_DRAW_REG_QOS_SW_W             OSD_DRAW_REG_QOS_SW_W
#define OSD_DRAW_REG_QOS_SW_W_POS         (5U)
#define OSD_DRAW_REG_QOS_SW_W_LEN         (1U)
#define OSD_DRAW_REG_QOS_SW_W_MSK         (((1U << OSD_DRAW_REG_QOS_SW_W_LEN) - 1) << OSD_DRAW_REG_QOS_SW_W_POS)
#define OSD_DRAW_REG_QOS_SW_W_UMSK        (~(((1U << OSD_DRAW_REG_QOS_SW_W_LEN) - 1) << OSD_DRAW_REG_QOS_SW_W_POS))
#define OSD_DRAW_REG_OSTD_MAX_W           OSD_DRAW_REG_OSTD_MAX_W
#define OSD_DRAW_REG_OSTD_MAX_W_POS       (8U)
#define OSD_DRAW_REG_OSTD_MAX_W_LEN       (2U)
#define OSD_DRAW_REG_OSTD_MAX_W_MSK       (((1U << OSD_DRAW_REG_OSTD_MAX_W_LEN) - 1) << OSD_DRAW_REG_OSTD_MAX_W_POS)
#define OSD_DRAW_REG_OSTD_MAX_W_UMSK      (~(((1U << OSD_DRAW_REG_OSTD_MAX_W_LEN) - 1) << OSD_DRAW_REG_OSTD_MAX_W_POS))
#define OSD_DRAW_REG_XLEN_W               OSD_DRAW_REG_XLEN_W
#define OSD_DRAW_REG_XLEN_W_POS           (12U)
#define OSD_DRAW_REG_XLEN_W_LEN           (3U)
#define OSD_DRAW_REG_XLEN_W_MSK           (((1U << OSD_DRAW_REG_XLEN_W_LEN) - 1) << OSD_DRAW_REG_XLEN_W_POS)
#define OSD_DRAW_REG_XLEN_W_UMSK          (~(((1U << OSD_DRAW_REG_XLEN_W_LEN) - 1) << OSD_DRAW_REG_XLEN_W_POS))
#define OSD_DRAW_STS_L0_CMD_IDLE_R        OSD_DRAW_STS_L0_CMD_IDLE_R
#define OSD_DRAW_STS_L0_CMD_IDLE_R_POS    (16U)
#define OSD_DRAW_STS_L0_CMD_IDLE_R_LEN    (1U)
#define OSD_DRAW_STS_L0_CMD_IDLE_R_MSK    (((1U << OSD_DRAW_STS_L0_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L0_CMD_IDLE_R_POS)
#define OSD_DRAW_STS_L0_CMD_IDLE_R_UMSK   (~(((1U << OSD_DRAW_STS_L0_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L0_CMD_IDLE_R_POS))
#define OSD_DRAW_STS_L1_CMD_IDLE_R        OSD_DRAW_STS_L1_CMD_IDLE_R
#define OSD_DRAW_STS_L1_CMD_IDLE_R_POS    (17U)
#define OSD_DRAW_STS_L1_CMD_IDLE_R_LEN    (1U)
#define OSD_DRAW_STS_L1_CMD_IDLE_R_MSK    (((1U << OSD_DRAW_STS_L1_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L1_CMD_IDLE_R_POS)
#define OSD_DRAW_STS_L1_CMD_IDLE_R_UMSK   (~(((1U << OSD_DRAW_STS_L1_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L1_CMD_IDLE_R_POS))
#define OSD_DRAW_STS_L2_CMD_IDLE_R        OSD_DRAW_STS_L2_CMD_IDLE_R
#define OSD_DRAW_STS_L2_CMD_IDLE_R_POS    (18U)
#define OSD_DRAW_STS_L2_CMD_IDLE_R_LEN    (1U)
#define OSD_DRAW_STS_L2_CMD_IDLE_R_MSK    (((1U << OSD_DRAW_STS_L2_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L2_CMD_IDLE_R_POS)
#define OSD_DRAW_STS_L2_CMD_IDLE_R_UMSK   (~(((1U << OSD_DRAW_STS_L2_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L2_CMD_IDLE_R_POS))
#define OSD_DRAW_STS_L3_CMD_IDLE_R        OSD_DRAW_STS_L3_CMD_IDLE_R
#define OSD_DRAW_STS_L3_CMD_IDLE_R_POS    (19U)
#define OSD_DRAW_STS_L3_CMD_IDLE_R_LEN    (1U)
#define OSD_DRAW_STS_L3_CMD_IDLE_R_MSK    (((1U << OSD_DRAW_STS_L3_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L3_CMD_IDLE_R_POS)
#define OSD_DRAW_STS_L3_CMD_IDLE_R_UMSK   (~(((1U << OSD_DRAW_STS_L3_CMD_IDLE_R_LEN) - 1) << OSD_DRAW_STS_L3_CMD_IDLE_R_POS))
#define OSD_DRAW_STS_AXI_IDLE_R           OSD_DRAW_STS_AXI_IDLE_R
#define OSD_DRAW_STS_AXI_IDLE_R_POS       (20U)
#define OSD_DRAW_STS_AXI_IDLE_R_LEN       (1U)
#define OSD_DRAW_STS_AXI_IDLE_R_MSK       (((1U << OSD_DRAW_STS_AXI_IDLE_R_LEN) - 1) << OSD_DRAW_STS_AXI_IDLE_R_POS)
#define OSD_DRAW_STS_AXI_IDLE_R_UMSK      (~(((1U << OSD_DRAW_STS_AXI_IDLE_R_LEN) - 1) << OSD_DRAW_STS_AXI_IDLE_R_POS))
#define OSD_DRAW_REG_PCLK_FORCE_ON_W      OSD_DRAW_REG_PCLK_FORCE_ON_W
#define OSD_DRAW_REG_PCLK_FORCE_ON_W_POS  (24U)
#define OSD_DRAW_REG_PCLK_FORCE_ON_W_LEN  (8U)
#define OSD_DRAW_REG_PCLK_FORCE_ON_W_MSK  (((1U << OSD_DRAW_REG_PCLK_FORCE_ON_W_LEN) - 1) << OSD_DRAW_REG_PCLK_FORCE_ON_W_POS)
#define OSD_DRAW_REG_PCLK_FORCE_ON_W_UMSK (~(((1U << OSD_DRAW_REG_PCLK_FORCE_ON_W_LEN) - 1) << OSD_DRAW_REG_PCLK_FORCE_ON_W_POS))

struct osd_draw_reg {
    /* 0x0 : osd_draw_config */
    union {
        struct {
            uint32_t reg_draw_en_l   : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_draw_type_l : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_draw_config;

    /* 0x4 : draw_partial_yuv_config0 */
    union {
        struct {
            uint32_t reg_draw_th_00 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_00  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_00  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_00  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config0;

    /* 0x8 : draw_partial_x_config0 */
    union {
        struct {
            uint32_t reg_draw_x_min_00 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_00 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config0;

    /* 0xC : draw_partial_y_config0 */
    union {
        struct {
            uint32_t reg_draw_y_min_00 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_00 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config0;

    /* 0x10 : draw_partial_yuv_config1 */
    union {
        struct {
            uint32_t reg_draw_th_01 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_01  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_01  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_01  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config1;

    /* 0x14 : draw_partial_x_config1 */
    union {
        struct {
            uint32_t reg_draw_x_min_01 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_01 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config1;

    /* 0x18 : draw_partial_y_config1 */
    union {
        struct {
            uint32_t reg_draw_y_min_01 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_01 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config1;

    /* 0x1C : draw_partial_yuv_config2 */
    union {
        struct {
            uint32_t reg_draw_th_02 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_02  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_02  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_02  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config2;

    /* 0x20 : draw_partial_x_config2 */
    union {
        struct {
            uint32_t reg_draw_x_min_02 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_02 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config2;

    /* 0x24 : draw_partial_y_config2 */
    union {
        struct {
            uint32_t reg_draw_y_min_02 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_02 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config2;

    /* 0x28 : draw_partial_yuv_config3 */
    union {
        struct {
            uint32_t reg_draw_th_03 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_03  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_03  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_03  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config3;

    /* 0x2C : draw_partial_x_config3 */
    union {
        struct {
            uint32_t reg_draw_x_min_03 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_03 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config3;

    /* 0x30 : draw_partial_y_config3 */
    union {
        struct {
            uint32_t reg_draw_y_min_03 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_03 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config3;

    /* 0x34 : draw_partial_yuv_config4 */
    union {
        struct {
            uint32_t reg_draw_th_04 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_04  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_04  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_04  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config4;

    /* 0x38 : draw_partial_x_config4 */
    union {
        struct {
            uint32_t reg_draw_x_min_04 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_04 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config4;

    /* 0x3C : draw_partial_y_config4 */
    union {
        struct {
            uint32_t reg_draw_y_min_04 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_04 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config4;

    /* 0x40 : draw_partial_yuv_config5 */
    union {
        struct {
            uint32_t reg_draw_th_05 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_05  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_05  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_05  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config5;

    /* 0x44 : draw_partial_x_config5 */
    union {
        struct {
            uint32_t reg_draw_x_min_05 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_05 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config5;

    /* 0x48 : draw_partial_y_config5 */
    union {
        struct {
            uint32_t reg_draw_y_min_05 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_05 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config5;

    /* 0x4C : draw_partial_yuv_config6 */
    union {
        struct {
            uint32_t reg_draw_th_06 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_06  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_06  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_06  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config6;

    /* 0x50 : draw_partial_x_config6 */
    union {
        struct {
            uint32_t reg_draw_x_min_06 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_06 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config6;

    /* 0x54 : draw_partial_y_config6 */
    union {
        struct {
            uint32_t reg_draw_y_min_06 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_06 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config6;

    /* 0x58 : draw_partial_yuv_config7 */
    union {
        struct {
            uint32_t reg_draw_th_07 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_07  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_07  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_07  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config7;

    /* 0x5C : draw_partial_x_config7 */
    union {
        struct {
            uint32_t reg_draw_x_min_07 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_07 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config7;

    /* 0x60 : draw_partial_y_config7 */
    union {
        struct {
            uint32_t reg_draw_y_min_07 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_07 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config7;

    /* 0x64 : draw_partial_yuv_config8 */
    union {
        struct {
            uint32_t reg_draw_th_08 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_08  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_08  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_08  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config8;

    /* 0x68 : draw_partial_x_config8 */
    union {
        struct {
            uint32_t reg_draw_x_min_08 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_08 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config8;

    /* 0x6C : draw_partial_y_config8 */
    union {
        struct {
            uint32_t reg_draw_y_min_08 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_08 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config8;

    /* 0x70 : draw_partial_yuv_config9 */
    union {
        struct {
            uint32_t reg_draw_th_09 : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_09  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_09  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_09  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_config9;

    /* 0x74 : draw_partial_x_config9 */
    union {
        struct {
            uint32_t reg_draw_x_min_09 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_09 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_config9;

    /* 0x78 : draw_partial_y_config9 */
    union {
        struct {
            uint32_t reg_draw_y_min_09 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_09 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_config9;

    /* 0x7C : draw_partial_yuv_configa */
    union {
        struct {
            uint32_t reg_draw_th_0a : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_0a  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_0a  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_0a  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_configa;

    /* 0x80 : draw_partial_x_configa */
    union {
        struct {
            uint32_t reg_draw_x_min_0a : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_0a : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_configa;

    /* 0x84 : draw_partial_y_configa */
    union {
        struct {
            uint32_t reg_draw_y_min_0a : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_0a : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_configa;

    /* 0x88 : draw_partial_yuv_configb */
    union {
        struct {
            uint32_t reg_draw_th_0b : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_0b  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_0b  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_0b  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_configb;

    /* 0x8C : draw_partial_x_configb */
    union {
        struct {
            uint32_t reg_draw_x_min_0b : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_0b : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_configb;

    /* 0x90 : draw_partial_y_configb */
    union {
        struct {
            uint32_t reg_draw_y_min_0b : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_0b : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_configb;

    /* 0x94 : draw_partial_yuv_configc */
    union {
        struct {
            uint32_t reg_draw_th_0c : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_0c  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_0c  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_0c  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_configc;

    /* 0x98 : draw_partial_x_configc */
    union {
        struct {
            uint32_t reg_draw_x_min_0c : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_0c : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_configc;

    /* 0x9C : draw_partial_y_configc */
    union {
        struct {
            uint32_t reg_draw_y_min_0c : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_0c : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_configc;

    /* 0xA0 : draw_partial_yuv_configd */
    union {
        struct {
            uint32_t reg_draw_th_0d : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_0d  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_0d  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_0d  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_configd;

    /* 0xA4 : draw_partial_x_configd */
    union {
        struct {
            uint32_t reg_draw_x_min_0d : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_0d : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_configd;

    /* 0xA8 : draw_partial_y_configd */
    union {
        struct {
            uint32_t reg_draw_y_min_0d : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_0d : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_configd;

    /* 0xAC : draw_partial_yuv_confige */
    union {
        struct {
            uint32_t reg_draw_th_0e : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_0e  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_0e  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_0e  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_confige;

    /* 0xB0 : draw_partial_x_confige */
    union {
        struct {
            uint32_t reg_draw_x_min_0e : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_0e : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_confige;

    /* 0xB4 : draw_partial_y_confige */
    union {
        struct {
            uint32_t reg_draw_y_min_0e : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_0e : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_confige;

    /* 0xB8 : draw_partial_yuv_configf */
    union {
        struct {
            uint32_t reg_draw_th_0f : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t reg_draw_v_0f  : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t reg_draw_u_0f  : 8; /* [23:16],        r/w,        0x0 */
            uint32_t reg_draw_y_0f  : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_yuv_configf;

    /* 0xBC : draw_partial_x_configf */
    union {
        struct {
            uint32_t reg_draw_x_min_0f : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_x_max_0f : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_x_configf;

    /* 0xC0 : draw_partial_y_configf */
    union {
        struct {
            uint32_t reg_draw_y_min_0f : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_draw_y_max_0f : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31    : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } draw_partial_y_configf;

    /* 0xc4  reserved */
    uint8_t RESERVED0xc4[52];

    /* 0xF8 : osd_int_sts */
    union {
        struct {
            uint32_t reg_seof_int_clr_w  : 1;  /* [    0],        w1p,        0x0 */
            uint32_t reg_seof_int_mask_w : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reg_seof_int_edge_w : 1;  /* [    2],        r/w,        0x0 */
            uint32_t reserved_3_15       : 13; /* [15: 3],       rsvd,        0x0 */
            uint32_t sts_drain_int_r     : 4;  /* [19:16],          r,        0x0 */
            uint32_t sts_seof_int_r      : 1;  /* [   20],          r,        0x0 */
            uint32_t reserved_21_31      : 11; /* [31:21],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_int_sts;

    /* 0xFC : osd_misc */
    union {
        struct {
            uint32_t reg_bus_strt_w      : 1; /* [    0],        w1p,        0x0 */
            uint32_t reg_fifo_auto_clr_w : 1; /* [    1],        r/w,        0x1 */
            uint32_t reserved_2_3        : 2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t reg_qos_sw_mode_w   : 1; /* [    4],        r/w,        0x0 */
            uint32_t reg_qos_sw_w        : 1; /* [    5],        r/w,        0x0 */
            uint32_t reserved_6_7        : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t reg_ostd_max_w      : 2; /* [ 9: 8],        r/w,        0x3 */
            uint32_t reserved_10_11      : 2; /* [11:10],       rsvd,        0x0 */
            uint32_t reg_xlen_w          : 3; /* [14:12],        r/w,        0x4 */
            uint32_t reserved_15         : 1; /* [   15],       rsvd,        0x0 */
            uint32_t sts_l0_cmd_idle_r   : 1; /* [   16],          r,        0x0 */
            uint32_t sts_l1_cmd_idle_r   : 1; /* [   17],          r,        0x0 */
            uint32_t sts_l2_cmd_idle_r   : 1; /* [   18],          r,        0x0 */
            uint32_t sts_l3_cmd_idle_r   : 1; /* [   19],          r,        0x0 */
            uint32_t sts_axi_idle_r      : 1; /* [   20],          r,        0x0 */
            uint32_t reserved_21_23      : 3; /* [23:21],       rsvd,        0x0 */
            uint32_t reg_pclk_force_on_w : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_misc;
};

typedef volatile struct osd_draw_reg osd_draw_reg_t;

#endif /* __OSD_REG_H__ */
