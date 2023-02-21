/**
  ******************************************************************************
  * @file    dsp2_tg_reg.h
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
#ifndef __DSP2_TG_REG_H__
#define __DSP2_TG_REG_H__

#include "bl808.h"

/* 0x00 : ip_info */
#define DSP2_TG_IP_INFO_OFFSET (0x00)
#define DSP2_TG_IP_ID_R        DSP2_TG_IP_ID_R
#define DSP2_TG_IP_ID_R_POS    (8U)
#define DSP2_TG_IP_ID_R_LEN    (8U)
#define DSP2_TG_IP_ID_R_MSK    (((1U << DSP2_TG_IP_ID_R_LEN) - 1) << DSP2_TG_IP_ID_R_POS)
#define DSP2_TG_IP_ID_R_UMSK   (~(((1U << DSP2_TG_IP_ID_R_LEN) - 1) << DSP2_TG_IP_ID_R_POS))
#define DSP2_TG_VERSION_R      DSP2_TG_VERSION_R
#define DSP2_TG_VERSION_R_POS  (16U)
#define DSP2_TG_VERSION_R_LEN  (8U)
#define DSP2_TG_VERSION_R_MSK  (((1U << DSP2_TG_VERSION_R_LEN) - 1) << DSP2_TG_VERSION_R_POS)
#define DSP2_TG_VERSION_R_UMSK (~(((1U << DSP2_TG_VERSION_R_LEN) - 1) << DSP2_TG_VERSION_R_POS))

/* 0x08 : dvp_mode */
#define DSP2_TG_DVP_MODE_OFFSET             (0x08)
#define DSP2_TG_FHBLK_LINE_ON_W             DSP2_TG_FHBLK_LINE_ON_W
#define DSP2_TG_FHBLK_LINE_ON_W_POS         (0U)
#define DSP2_TG_FHBLK_LINE_ON_W_LEN         (1U)
#define DSP2_TG_FHBLK_LINE_ON_W_MSK         (((1U << DSP2_TG_FHBLK_LINE_ON_W_LEN) - 1) << DSP2_TG_FHBLK_LINE_ON_W_POS)
#define DSP2_TG_FHBLK_LINE_ON_W_UMSK        (~(((1U << DSP2_TG_FHBLK_LINE_ON_W_LEN) - 1) << DSP2_TG_FHBLK_LINE_ON_W_POS))
#define DSP2_TG_HBLK_LINE_ON_W              DSP2_TG_HBLK_LINE_ON_W
#define DSP2_TG_HBLK_LINE_ON_W_POS          (1U)
#define DSP2_TG_HBLK_LINE_ON_W_LEN          (1U)
#define DSP2_TG_HBLK_LINE_ON_W_MSK          (((1U << DSP2_TG_HBLK_LINE_ON_W_LEN) - 1) << DSP2_TG_HBLK_LINE_ON_W_POS)
#define DSP2_TG_HBLK_LINE_ON_W_UMSK         (~(((1U << DSP2_TG_HBLK_LINE_ON_W_LEN) - 1) << DSP2_TG_HBLK_LINE_ON_W_POS))
#define DSP2_TG_VCNT_RST_MODE_W             DSP2_TG_VCNT_RST_MODE_W
#define DSP2_TG_VCNT_RST_MODE_W_POS         (16U)
#define DSP2_TG_VCNT_RST_MODE_W_LEN         (1U)
#define DSP2_TG_VCNT_RST_MODE_W_MSK         (((1U << DSP2_TG_VCNT_RST_MODE_W_LEN) - 1) << DSP2_TG_VCNT_RST_MODE_W_POS)
#define DSP2_TG_VCNT_RST_MODE_W_UMSK        (~(((1U << DSP2_TG_VCNT_RST_MODE_W_LEN) - 1) << DSP2_TG_VCNT_RST_MODE_W_POS))
#define DSP2_TG_HCNT_RST_MODE_W             DSP2_TG_HCNT_RST_MODE_W
#define DSP2_TG_HCNT_RST_MODE_W_POS         (17U)
#define DSP2_TG_HCNT_RST_MODE_W_LEN         (1U)
#define DSP2_TG_HCNT_RST_MODE_W_MSK         (((1U << DSP2_TG_HCNT_RST_MODE_W_LEN) - 1) << DSP2_TG_HCNT_RST_MODE_W_POS)
#define DSP2_TG_HCNT_RST_MODE_W_UMSK        (~(((1U << DSP2_TG_HCNT_RST_MODE_W_LEN) - 1) << DSP2_TG_HCNT_RST_MODE_W_POS))
#define DSP2_TG_VSYNC_IN_INV_W              DSP2_TG_VSYNC_IN_INV_W
#define DSP2_TG_VSYNC_IN_INV_W_POS          (18U)
#define DSP2_TG_VSYNC_IN_INV_W_LEN          (1U)
#define DSP2_TG_VSYNC_IN_INV_W_MSK          (((1U << DSP2_TG_VSYNC_IN_INV_W_LEN) - 1) << DSP2_TG_VSYNC_IN_INV_W_POS)
#define DSP2_TG_VSYNC_IN_INV_W_UMSK         (~(((1U << DSP2_TG_VSYNC_IN_INV_W_LEN) - 1) << DSP2_TG_VSYNC_IN_INV_W_POS))
#define DSP2_TG_HSYNC_IN_INV_W              DSP2_TG_HSYNC_IN_INV_W
#define DSP2_TG_HSYNC_IN_INV_W_POS          (19U)
#define DSP2_TG_HSYNC_IN_INV_W_LEN          (1U)
#define DSP2_TG_HSYNC_IN_INV_W_MSK          (((1U << DSP2_TG_HSYNC_IN_INV_W_LEN) - 1) << DSP2_TG_HSYNC_IN_INV_W_POS)
#define DSP2_TG_HSYNC_IN_INV_W_UMSK         (~(((1U << DSP2_TG_HSYNC_IN_INV_W_LEN) - 1) << DSP2_TG_HSYNC_IN_INV_W_POS))
#define DSP2_TG_SYNC_MODE_W                 DSP2_TG_SYNC_MODE_W
#define DSP2_TG_SYNC_MODE_W_POS             (20U)
#define DSP2_TG_SYNC_MODE_W_LEN             (2U)
#define DSP2_TG_SYNC_MODE_W_MSK             (((1U << DSP2_TG_SYNC_MODE_W_LEN) - 1) << DSP2_TG_SYNC_MODE_W_POS)
#define DSP2_TG_SYNC_MODE_W_UMSK            (~(((1U << DSP2_TG_SYNC_MODE_W_LEN) - 1) << DSP2_TG_SYNC_MODE_W_POS))
#define DSP2_TG_REG_ACT_VSYNC_RST_EN_W      DSP2_TG_REG_ACT_VSYNC_RST_EN_W
#define DSP2_TG_REG_ACT_VSYNC_RST_EN_W_POS  (24U)
#define DSP2_TG_REG_ACT_VSYNC_RST_EN_W_LEN  (1U)
#define DSP2_TG_REG_ACT_VSYNC_RST_EN_W_MSK  (((1U << DSP2_TG_REG_ACT_VSYNC_RST_EN_W_LEN) - 1) << DSP2_TG_REG_ACT_VSYNC_RST_EN_W_POS)
#define DSP2_TG_REG_ACT_VSYNC_RST_EN_W_UMSK (~(((1U << DSP2_TG_REG_ACT_VSYNC_RST_EN_W_LEN) - 1) << DSP2_TG_REG_ACT_VSYNC_RST_EN_W_POS))

/* 0x0C : total_pixels */
#define DSP2_TG_TOTAL_PIXELS_OFFSET  (0x0C)
#define DSP2_TG_TOTAL_HPIXELS_W      DSP2_TG_TOTAL_HPIXELS_W
#define DSP2_TG_TOTAL_HPIXELS_W_POS  (0U)
#define DSP2_TG_TOTAL_HPIXELS_W_LEN  (16U)
#define DSP2_TG_TOTAL_HPIXELS_W_MSK  (((1U << DSP2_TG_TOTAL_HPIXELS_W_LEN) - 1) << DSP2_TG_TOTAL_HPIXELS_W_POS)
#define DSP2_TG_TOTAL_HPIXELS_W_UMSK (~(((1U << DSP2_TG_TOTAL_HPIXELS_W_LEN) - 1) << DSP2_TG_TOTAL_HPIXELS_W_POS))
#define DSP2_TG_TOTAL_VLINES_W       DSP2_TG_TOTAL_VLINES_W
#define DSP2_TG_TOTAL_VLINES_W_POS   (16U)
#define DSP2_TG_TOTAL_VLINES_W_LEN   (16U)
#define DSP2_TG_TOTAL_VLINES_W_MSK   (((1U << DSP2_TG_TOTAL_VLINES_W_LEN) - 1) << DSP2_TG_TOTAL_VLINES_W_POS)
#define DSP2_TG_TOTAL_VLINES_W_UMSK  (~(((1U << DSP2_TG_TOTAL_VLINES_W_LEN) - 1) << DSP2_TG_TOTAL_VLINES_W_POS))

/* 0x10 : act_pixels_1 */
#define DSP2_TG_ACT_PIXELS_1_OFFSET    (0x10)
#define DSP2_TG_ACT_START_PIXEL_W      DSP2_TG_ACT_START_PIXEL_W
#define DSP2_TG_ACT_START_PIXEL_W_POS  (0U)
#define DSP2_TG_ACT_START_PIXEL_W_LEN  (16U)
#define DSP2_TG_ACT_START_PIXEL_W_MSK  (((1U << DSP2_TG_ACT_START_PIXEL_W_LEN) - 1) << DSP2_TG_ACT_START_PIXEL_W_POS)
#define DSP2_TG_ACT_START_PIXEL_W_UMSK (~(((1U << DSP2_TG_ACT_START_PIXEL_W_LEN) - 1) << DSP2_TG_ACT_START_PIXEL_W_POS))
#define DSP2_TG_ACT_PIXEL_WIDTH_W      DSP2_TG_ACT_PIXEL_WIDTH_W
#define DSP2_TG_ACT_PIXEL_WIDTH_W_POS  (16U)
#define DSP2_TG_ACT_PIXEL_WIDTH_W_LEN  (16U)
#define DSP2_TG_ACT_PIXEL_WIDTH_W_MSK  (((1U << DSP2_TG_ACT_PIXEL_WIDTH_W_LEN) - 1) << DSP2_TG_ACT_PIXEL_WIDTH_W_POS)
#define DSP2_TG_ACT_PIXEL_WIDTH_W_UMSK (~(((1U << DSP2_TG_ACT_PIXEL_WIDTH_W_LEN) - 1) << DSP2_TG_ACT_PIXEL_WIDTH_W_POS))

/* 0x14 : act_pixels_2 */
#define DSP2_TG_ACT_PIXELS_2_OFFSET    (0x14)
#define DSP2_TG_ACT_START_LINE_W       DSP2_TG_ACT_START_LINE_W
#define DSP2_TG_ACT_START_LINE_W_POS   (0U)
#define DSP2_TG_ACT_START_LINE_W_LEN   (16U)
#define DSP2_TG_ACT_START_LINE_W_MSK   (((1U << DSP2_TG_ACT_START_LINE_W_LEN) - 1) << DSP2_TG_ACT_START_LINE_W_POS)
#define DSP2_TG_ACT_START_LINE_W_UMSK  (~(((1U << DSP2_TG_ACT_START_LINE_W_LEN) - 1) << DSP2_TG_ACT_START_LINE_W_POS))
#define DSP2_TG_ACT_LINE_HEIGHT_W      DSP2_TG_ACT_LINE_HEIGHT_W
#define DSP2_TG_ACT_LINE_HEIGHT_W_POS  (16U)
#define DSP2_TG_ACT_LINE_HEIGHT_W_LEN  (16U)
#define DSP2_TG_ACT_LINE_HEIGHT_W_MSK  (((1U << DSP2_TG_ACT_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_ACT_LINE_HEIGHT_W_POS)
#define DSP2_TG_ACT_LINE_HEIGHT_W_UMSK (~(((1U << DSP2_TG_ACT_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_ACT_LINE_HEIGHT_W_POS))

/* 0x18 : fact_pixels_1 */
#define DSP2_TG_FACT_PIXELS_1_OFFSET    (0x18)
#define DSP2_TG_FACT_START_PIXEL_W      DSP2_TG_FACT_START_PIXEL_W
#define DSP2_TG_FACT_START_PIXEL_W_POS  (0U)
#define DSP2_TG_FACT_START_PIXEL_W_LEN  (16U)
#define DSP2_TG_FACT_START_PIXEL_W_MSK  (((1U << DSP2_TG_FACT_START_PIXEL_W_LEN) - 1) << DSP2_TG_FACT_START_PIXEL_W_POS)
#define DSP2_TG_FACT_START_PIXEL_W_UMSK (~(((1U << DSP2_TG_FACT_START_PIXEL_W_LEN) - 1) << DSP2_TG_FACT_START_PIXEL_W_POS))
#define DSP2_TG_FACT_PIXEL_WIDTH_W      DSP2_TG_FACT_PIXEL_WIDTH_W
#define DSP2_TG_FACT_PIXEL_WIDTH_W_POS  (16U)
#define DSP2_TG_FACT_PIXEL_WIDTH_W_LEN  (16U)
#define DSP2_TG_FACT_PIXEL_WIDTH_W_MSK  (((1U << DSP2_TG_FACT_PIXEL_WIDTH_W_LEN) - 1) << DSP2_TG_FACT_PIXEL_WIDTH_W_POS)
#define DSP2_TG_FACT_PIXEL_WIDTH_W_UMSK (~(((1U << DSP2_TG_FACT_PIXEL_WIDTH_W_LEN) - 1) << DSP2_TG_FACT_PIXEL_WIDTH_W_POS))

/* 0x1C : fact_pixels_2 */
#define DSP2_TG_FACT_PIXELS_2_OFFSET    (0x1C)
#define DSP2_TG_FACT_START_LINE_W       DSP2_TG_FACT_START_LINE_W
#define DSP2_TG_FACT_START_LINE_W_POS   (0U)
#define DSP2_TG_FACT_START_LINE_W_LEN   (16U)
#define DSP2_TG_FACT_START_LINE_W_MSK   (((1U << DSP2_TG_FACT_START_LINE_W_LEN) - 1) << DSP2_TG_FACT_START_LINE_W_POS)
#define DSP2_TG_FACT_START_LINE_W_UMSK  (~(((1U << DSP2_TG_FACT_START_LINE_W_LEN) - 1) << DSP2_TG_FACT_START_LINE_W_POS))
#define DSP2_TG_FACT_LINE_HEIGHT_W      DSP2_TG_FACT_LINE_HEIGHT_W
#define DSP2_TG_FACT_LINE_HEIGHT_W_POS  (16U)
#define DSP2_TG_FACT_LINE_HEIGHT_W_LEN  (16U)
#define DSP2_TG_FACT_LINE_HEIGHT_W_MSK  (((1U << DSP2_TG_FACT_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_FACT_LINE_HEIGHT_W_POS)
#define DSP2_TG_FACT_LINE_HEIGHT_W_UMSK (~(((1U << DSP2_TG_FACT_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_FACT_LINE_HEIGHT_W_POS))

/* 0x20 : hsync_pixel */
#define DSP2_TG_HSYNC_PIXEL_OFFSET       (0x20)
#define DSP2_TG_HSYNC_START_PIXEL_W      DSP2_TG_HSYNC_START_PIXEL_W
#define DSP2_TG_HSYNC_START_PIXEL_W_POS  (0U)
#define DSP2_TG_HSYNC_START_PIXEL_W_LEN  (16U)
#define DSP2_TG_HSYNC_START_PIXEL_W_MSK  (((1U << DSP2_TG_HSYNC_START_PIXEL_W_LEN) - 1) << DSP2_TG_HSYNC_START_PIXEL_W_POS)
#define DSP2_TG_HSYNC_START_PIXEL_W_UMSK (~(((1U << DSP2_TG_HSYNC_START_PIXEL_W_LEN) - 1) << DSP2_TG_HSYNC_START_PIXEL_W_POS))
#define DSP2_TG_HSYNC_PIXEL_WIDTH_W      DSP2_TG_HSYNC_PIXEL_WIDTH_W
#define DSP2_TG_HSYNC_PIXEL_WIDTH_W_POS  (16U)
#define DSP2_TG_HSYNC_PIXEL_WIDTH_W_LEN  (16U)
#define DSP2_TG_HSYNC_PIXEL_WIDTH_W_MSK  (((1U << DSP2_TG_HSYNC_PIXEL_WIDTH_W_LEN) - 1) << DSP2_TG_HSYNC_PIXEL_WIDTH_W_POS)
#define DSP2_TG_HSYNC_PIXEL_WIDTH_W_UMSK (~(((1U << DSP2_TG_HSYNC_PIXEL_WIDTH_W_LEN) - 1) << DSP2_TG_HSYNC_PIXEL_WIDTH_W_POS))

/* 0x24 : hsync_line */
#define DSP2_TG_HSYNC_LINE_OFFSET        (0x24)
#define DSP2_TG_HSYNC_START_LINE_W       DSP2_TG_HSYNC_START_LINE_W
#define DSP2_TG_HSYNC_START_LINE_W_POS   (0U)
#define DSP2_TG_HSYNC_START_LINE_W_LEN   (16U)
#define DSP2_TG_HSYNC_START_LINE_W_MSK   (((1U << DSP2_TG_HSYNC_START_LINE_W_LEN) - 1) << DSP2_TG_HSYNC_START_LINE_W_POS)
#define DSP2_TG_HSYNC_START_LINE_W_UMSK  (~(((1U << DSP2_TG_HSYNC_START_LINE_W_LEN) - 1) << DSP2_TG_HSYNC_START_LINE_W_POS))
#define DSP2_TG_HSYNC_LINE_HEIGHT_W      DSP2_TG_HSYNC_LINE_HEIGHT_W
#define DSP2_TG_HSYNC_LINE_HEIGHT_W_POS  (16U)
#define DSP2_TG_HSYNC_LINE_HEIGHT_W_LEN  (16U)
#define DSP2_TG_HSYNC_LINE_HEIGHT_W_MSK  (((1U << DSP2_TG_HSYNC_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_HSYNC_LINE_HEIGHT_W_POS)
#define DSP2_TG_HSYNC_LINE_HEIGHT_W_UMSK (~(((1U << DSP2_TG_HSYNC_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_HSYNC_LINE_HEIGHT_W_POS))

/* 0x28 : vsync_line */
#define DSP2_TG_VSYNC_LINE_OFFSET        (0x28)
#define DSP2_TG_VSYNC_START_LINE_W       DSP2_TG_VSYNC_START_LINE_W
#define DSP2_TG_VSYNC_START_LINE_W_POS   (0U)
#define DSP2_TG_VSYNC_START_LINE_W_LEN   (16U)
#define DSP2_TG_VSYNC_START_LINE_W_MSK   (((1U << DSP2_TG_VSYNC_START_LINE_W_LEN) - 1) << DSP2_TG_VSYNC_START_LINE_W_POS)
#define DSP2_TG_VSYNC_START_LINE_W_UMSK  (~(((1U << DSP2_TG_VSYNC_START_LINE_W_LEN) - 1) << DSP2_TG_VSYNC_START_LINE_W_POS))
#define DSP2_TG_VSYNC_LINE_HEIGHT_W      DSP2_TG_VSYNC_LINE_HEIGHT_W
#define DSP2_TG_VSYNC_LINE_HEIGHT_W_POS  (16U)
#define DSP2_TG_VSYNC_LINE_HEIGHT_W_LEN  (16U)
#define DSP2_TG_VSYNC_LINE_HEIGHT_W_MSK  (((1U << DSP2_TG_VSYNC_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_VSYNC_LINE_HEIGHT_W_POS)
#define DSP2_TG_VSYNC_LINE_HEIGHT_W_UMSK (~(((1U << DSP2_TG_VSYNC_LINE_HEIGHT_W_LEN) - 1) << DSP2_TG_VSYNC_LINE_HEIGHT_W_POS))

/* 0x2C : vsync_pixel */
#define DSP2_TG_VSYNC_PIXEL_OFFSET       (0x2C)
#define DSP2_TG_VSYNC_START_PIXEL_W      DSP2_TG_VSYNC_START_PIXEL_W
#define DSP2_TG_VSYNC_START_PIXEL_W_POS  (0U)
#define DSP2_TG_VSYNC_START_PIXEL_W_LEN  (16U)
#define DSP2_TG_VSYNC_START_PIXEL_W_MSK  (((1U << DSP2_TG_VSYNC_START_PIXEL_W_LEN) - 1) << DSP2_TG_VSYNC_START_PIXEL_W_POS)
#define DSP2_TG_VSYNC_START_PIXEL_W_UMSK (~(((1U << DSP2_TG_VSYNC_START_PIXEL_W_LEN) - 1) << DSP2_TG_VSYNC_START_PIXEL_W_POS))
#define DSP2_TG_VSYNC_END_PIXEL_W        DSP2_TG_VSYNC_END_PIXEL_W
#define DSP2_TG_VSYNC_END_PIXEL_W_POS    (16U)
#define DSP2_TG_VSYNC_END_PIXEL_W_LEN    (16U)
#define DSP2_TG_VSYNC_END_PIXEL_W_MSK    (((1U << DSP2_TG_VSYNC_END_PIXEL_W_LEN) - 1) << DSP2_TG_VSYNC_END_PIXEL_W_POS)
#define DSP2_TG_VSYNC_END_PIXEL_W_UMSK   (~(((1U << DSP2_TG_VSYNC_END_PIXEL_W_LEN) - 1) << DSP2_TG_VSYNC_END_PIXEL_W_POS))

/* 0x30 : sync_out_inv */
#define DSP2_TG_SYNC_OUT_INV_OFFSET  (0x30)
#define DSP2_TG_VSYNC_OUT_INV_W      DSP2_TG_VSYNC_OUT_INV_W
#define DSP2_TG_VSYNC_OUT_INV_W_POS  (10U)
#define DSP2_TG_VSYNC_OUT_INV_W_LEN  (1U)
#define DSP2_TG_VSYNC_OUT_INV_W_MSK  (((1U << DSP2_TG_VSYNC_OUT_INV_W_LEN) - 1) << DSP2_TG_VSYNC_OUT_INV_W_POS)
#define DSP2_TG_VSYNC_OUT_INV_W_UMSK (~(((1U << DSP2_TG_VSYNC_OUT_INV_W_LEN) - 1) << DSP2_TG_VSYNC_OUT_INV_W_POS))
#define DSP2_TG_HSYNC_OUT_INV_W      DSP2_TG_HSYNC_OUT_INV_W
#define DSP2_TG_HSYNC_OUT_INV_W_POS  (11U)
#define DSP2_TG_HSYNC_OUT_INV_W_LEN  (1U)
#define DSP2_TG_HSYNC_OUT_INV_W_MSK  (((1U << DSP2_TG_HSYNC_OUT_INV_W_LEN) - 1) << DSP2_TG_HSYNC_OUT_INV_W_POS)
#define DSP2_TG_HSYNC_OUT_INV_W_UMSK (~(((1U << DSP2_TG_HSYNC_OUT_INV_W_LEN) - 1) << DSP2_TG_HSYNC_OUT_INV_W_POS))

/* 0x34 : hvcount_ctrl */
#define DSP2_TG_HVCOUNT_CTRL_OFFSET     (0x34)
#define DSP2_TG_AUTO_HVSYNC_GEN_W       DSP2_TG_AUTO_HVSYNC_GEN_W
#define DSP2_TG_AUTO_HVSYNC_GEN_W_POS   (0U)
#define DSP2_TG_AUTO_HVSYNC_GEN_W_LEN   (1U)
#define DSP2_TG_AUTO_HVSYNC_GEN_W_MSK   (((1U << DSP2_TG_AUTO_HVSYNC_GEN_W_LEN) - 1) << DSP2_TG_AUTO_HVSYNC_GEN_W_POS)
#define DSP2_TG_AUTO_HVSYNC_GEN_W_UMSK  (~(((1U << DSP2_TG_AUTO_HVSYNC_GEN_W_LEN) - 1) << DSP2_TG_AUTO_HVSYNC_GEN_W_POS))
#define DSP2_TG_RSHP_VSYNC_INV_W        DSP2_TG_RSHP_VSYNC_INV_W
#define DSP2_TG_RSHP_VSYNC_INV_W_POS    (1U)
#define DSP2_TG_RSHP_VSYNC_INV_W_LEN    (1U)
#define DSP2_TG_RSHP_VSYNC_INV_W_MSK    (((1U << DSP2_TG_RSHP_VSYNC_INV_W_LEN) - 1) << DSP2_TG_RSHP_VSYNC_INV_W_POS)
#define DSP2_TG_RSHP_VSYNC_INV_W_UMSK   (~(((1U << DSP2_TG_RSHP_VSYNC_INV_W_LEN) - 1) << DSP2_TG_RSHP_VSYNC_INV_W_POS))
#define DSP2_TG_RSHP_HSYNC_INV_W        DSP2_TG_RSHP_HSYNC_INV_W
#define DSP2_TG_RSHP_HSYNC_INV_W_POS    (2U)
#define DSP2_TG_RSHP_HSYNC_INV_W_LEN    (1U)
#define DSP2_TG_RSHP_HSYNC_INV_W_MSK    (((1U << DSP2_TG_RSHP_HSYNC_INV_W_LEN) - 1) << DSP2_TG_RSHP_HSYNC_INV_W_POS)
#define DSP2_TG_RSHP_HSYNC_INV_W_UMSK   (~(((1U << DSP2_TG_RSHP_HSYNC_INV_W_LEN) - 1) << DSP2_TG_RSHP_HSYNC_INV_W_POS))
#define DSP2_TG_TG_CTRL_START_W         DSP2_TG_TG_CTRL_START_W
#define DSP2_TG_TG_CTRL_START_W_POS     (3U)
#define DSP2_TG_TG_CTRL_START_W_LEN     (1U)
#define DSP2_TG_TG_CTRL_START_W_MSK     (((1U << DSP2_TG_TG_CTRL_START_W_LEN) - 1) << DSP2_TG_TG_CTRL_START_W_POS)
#define DSP2_TG_TG_CTRL_START_W_UMSK    (~(((1U << DSP2_TG_TG_CTRL_START_W_LEN) - 1) << DSP2_TG_TG_CTRL_START_W_POS))
#define DSP2_TG_AUTO_OHVSYNC_GEN_W      DSP2_TG_AUTO_OHVSYNC_GEN_W
#define DSP2_TG_AUTO_OHVSYNC_GEN_W_POS  (4U)
#define DSP2_TG_AUTO_OHVSYNC_GEN_W_LEN  (1U)
#define DSP2_TG_AUTO_OHVSYNC_GEN_W_MSK  (((1U << DSP2_TG_AUTO_OHVSYNC_GEN_W_LEN) - 1) << DSP2_TG_AUTO_OHVSYNC_GEN_W_POS)
#define DSP2_TG_AUTO_OHVSYNC_GEN_W_UMSK (~(((1U << DSP2_TG_AUTO_OHVSYNC_GEN_W_LEN) - 1) << DSP2_TG_AUTO_OHVSYNC_GEN_W_POS))
#define DSP2_TG_TG_CTRL_OSTART_W        DSP2_TG_TG_CTRL_OSTART_W
#define DSP2_TG_TG_CTRL_OSTART_W_POS    (7U)
#define DSP2_TG_TG_CTRL_OSTART_W_LEN    (1U)
#define DSP2_TG_TG_CTRL_OSTART_W_MSK    (((1U << DSP2_TG_TG_CTRL_OSTART_W_LEN) - 1) << DSP2_TG_TG_CTRL_OSTART_W_POS)
#define DSP2_TG_TG_CTRL_OSTART_W_UMSK   (~(((1U << DSP2_TG_TG_CTRL_OSTART_W_LEN) - 1) << DSP2_TG_TG_CTRL_OSTART_W_POS))

/* 0xFC : dsp2_apb_ctrl */
#define DSP2_TG_DSP2_APB_CTRL_OFFSET     (0xFC)
#define DSP2_TG_RG_PCLK_FORCE_ON_W      DSP2_TG_RG_PCLK_FORCE_ON_W
#define DSP2_TG_RG_PCLK_FORCE_ON_W_POS  (0U)
#define DSP2_TG_RG_PCLK_FORCE_ON_W_LEN  (16U)
#define DSP2_TG_RG_PCLK_FORCE_ON_W_MSK  (((1U << DSP2_TG_RG_PCLK_FORCE_ON_W_LEN) - 1) << DSP2_TG_RG_PCLK_FORCE_ON_W_POS)
#define DSP2_TG_RG_PCLK_FORCE_ON_W_UMSK (~(((1U << DSP2_TG_RG_PCLK_FORCE_ON_W_LEN) - 1) << DSP2_TG_RG_PCLK_FORCE_ON_W_POS))

struct dsp2_tg_reg {
    /* 0x00 : ip_info */
    union {
        struct {
            uint32_t reserved_0_7   : 8; /* [ 7: 0],       rsvd,        0x0 */
            uint32_t IP_ID_r        : 8; /* [15: 8],          r,       0x13 */
            uint32_t Version_r      : 8; /* [23:16],          r,       0x28 */
            uint32_t reserved_24_31 : 8; /* [31:24],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ip_info;

    /* 0x4  reserved */
    uint8_t RESERVED0x4[4];

    /* 0x08 : dvp_mode */
    union {
        struct {
            uint32_t fhblk_line_on_w        : 1;  /* [    0],        r/w,        0x0 */
            uint32_t hblk_line_on_w         : 1;  /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_15          : 14; /* [15: 2],       rsvd,        0x0 */
            uint32_t vcnt_rst_mode_w        : 1;  /* [   16],        r/w,        0x1 */
            uint32_t hcnt_rst_mode_w        : 1;  /* [   17],        r/w,        0x1 */
            uint32_t vsync_in_inv_w         : 1;  /* [   18],        r/w,        0x0 */
            uint32_t hsync_in_inv_w         : 1;  /* [   19],        r/w,        0x0 */
            uint32_t sync_mode_w            : 2;  /* [21:20],        r/w,        0x0 */
            uint32_t reserved_22_23         : 2;  /* [23:22],       rsvd,        0x0 */
            uint32_t reg_act_vsync_rst_en_w : 1;  /* [   24],        r/w,        0x0 */
            uint32_t reserved_25_31         : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dvp_mode;

    /* 0x0C : total_pixels */
    union {
        struct {
            uint32_t total_hpixels_w : 16; /* [15: 0],        r/w,      0xb0c */
            uint32_t total_vlines_w  : 16; /* [31:16],        r/w,      0x45a */
        } BF;
        uint32_t WORD;
    } total_pixels;

    /* 0x10 : act_pixels_1 */
    union {
        struct {
            uint32_t act_start_pixel_w : 16; /* [15: 0],        r/w,      0x384 */
            uint32_t act_pixel_width_w : 16; /* [31:16],        r/w,      0x5dc */
        } BF;
        uint32_t WORD;
    } act_pixels_1;

    /* 0x14 : act_pixels_2 */
    union {
        struct {
            uint32_t act_start_line_w  : 16; /* [15: 0],        r/w,       0x1a */
            uint32_t act_line_height_w : 16; /* [31:16],        r/w,      0x440 */
        } BF;
        uint32_t WORD;
    } act_pixels_2;

    /* 0x18 : fact_pixels_1 */
    union {
        struct {
            uint32_t fact_start_pixel_w : 16; /* [15: 0],        r/w,      0x43c */
            uint32_t fact_pixel_width_w : 16; /* [31:16],        r/w,      0x780 */
        } BF;
        uint32_t WORD;
    } fact_pixels_1;

    /* 0x1C : fact_pixels_2 */
    union {
        struct {
            uint32_t fact_start_line_w  : 16; /* [15: 0],        r/w,      0x438 */
            uint32_t fact_line_height_w : 16; /* [31:16],        r/w,       0x26 */
        } BF;
        uint32_t WORD;
    } fact_pixels_2;

    /* 0x20 : hsync_pixel */
    union {
        struct {
            uint32_t hsync_start_pixel_w : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t hsync_pixel_width_w : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } hsync_pixel;

    /* 0x24 : hsync_line */
    union {
        struct {
            uint32_t hsync_start_line_w  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t hsync_line_height_w : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } hsync_line;

    /* 0x28 : vsync_line */
    union {
        struct {
            uint32_t vsync_start_line_w  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t vsync_line_height_w : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } vsync_line;

    /* 0x2C : vsync_pixel */
    union {
        struct {
            uint32_t vsync_start_pixel_w : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t vsync_end_pixel_w   : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } vsync_pixel;

    /* 0x30 : sync_out_inv */
    union {
        struct {
            uint32_t reserved_0_9    : 10; /* [ 9: 0],       rsvd,        0x0 */
            uint32_t vsync_out_inv_w : 1;  /* [   10],        r/w,        0x0 */
            uint32_t hsync_out_inv_w : 1;  /* [   11],        r/w,        0x0 */
            uint32_t reserved_12_31  : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } sync_out_inv;

    /* 0x34 : hvcount_ctrl */
    union {
        struct {
            uint32_t auto_hvsync_gen_w  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t rshp_vsync_inv_w   : 1;  /* [    1],        r/w,        0x0 */
            uint32_t rshp_hsync_inv_w   : 1;  /* [    2],        r/w,        0x0 */
            uint32_t tg_ctrl_start_w    : 1;  /* [    3],        w1p,        0x0 */
            uint32_t auto_ohvsync_gen_w : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_6       : 2;  /* [ 6: 5],       rsvd,        0x0 */
            uint32_t tg_ctrl_ostart_w   : 1;  /* [    7],        w1p,        0x0 */
            uint32_t reserved_8_31      : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } hvcount_ctrl;

    /* 0x38  reserved */
    uint8_t RESERVED0x38[196];

    /* 0xFC : dsp2_apb_ctrl */
    union {
        struct {
            uint32_t rg_pclk_force_on_w : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reserved_16_31     : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } dsp2_apb_ctrl;
};

typedef volatile struct dsp2_tg_reg dsp2_tg_reg_t;

#endif /* __DSP2_TG_REG_H__ */
