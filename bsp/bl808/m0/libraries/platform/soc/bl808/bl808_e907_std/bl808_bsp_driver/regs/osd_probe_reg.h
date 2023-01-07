/**
  ******************************************************************************
  * @file    osd_probe_reg.h
  * @version V1.0
  * @date    2021-03-30
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
#ifndef __OSD_PROBE_REG_H__
#define __OSD_PROBE_REG_H__

#include "bl808.h"

/* 0x000 : osd_pb_ctrl_reg */
#define OSD_PB_CTRL_REG_OFFSET         (0x000)
#define OSD_PB_REG_OSD_PB_LUMA_TH      OSD_PB_REG_OSD_PB_LUMA_TH
#define OSD_PB_REG_OSD_PB_LUMA_TH_POS  (0U)
#define OSD_PB_REG_OSD_PB_LUMA_TH_LEN  (8U)
#define OSD_PB_REG_OSD_PB_LUMA_TH_MSK  (((1U << OSD_PB_REG_OSD_PB_LUMA_TH_LEN) - 1) << OSD_PB_REG_OSD_PB_LUMA_TH_POS)
#define OSD_PB_REG_OSD_PB_LUMA_TH_UMSK (~(((1U << OSD_PB_REG_OSD_PB_LUMA_TH_LEN) - 1) << OSD_PB_REG_OSD_PB_LUMA_TH_POS))
#define OSD_PB_STS_OSD_PB_W_CNT_R      OSD_PB_STS_OSD_PB_W_CNT_R
#define OSD_PB_STS_OSD_PB_W_CNT_R_POS  (8U)
#define OSD_PB_STS_OSD_PB_W_CNT_R_LEN  (5U)
#define OSD_PB_STS_OSD_PB_W_CNT_R_MSK  (((1U << OSD_PB_STS_OSD_PB_W_CNT_R_LEN) - 1) << OSD_PB_STS_OSD_PB_W_CNT_R_POS)
#define OSD_PB_STS_OSD_PB_W_CNT_R_UMSK (~(((1U << OSD_PB_STS_OSD_PB_W_CNT_R_LEN) - 1) << OSD_PB_STS_OSD_PB_W_CNT_R_POS))
#define OSD_PB_STS_OSD_PB_IDX_R        OSD_PB_STS_OSD_PB_IDX_R
#define OSD_PB_STS_OSD_PB_IDX_R_POS    (15U)
#define OSD_PB_STS_OSD_PB_IDX_R_LEN    (1U)
#define OSD_PB_STS_OSD_PB_IDX_R_MSK    (((1U << OSD_PB_STS_OSD_PB_IDX_R_LEN) - 1) << OSD_PB_STS_OSD_PB_IDX_R_POS)
#define OSD_PB_STS_OSD_PB_IDX_R_UMSK   (~(((1U << OSD_PB_STS_OSD_PB_IDX_R_LEN) - 1) << OSD_PB_STS_OSD_PB_IDX_R_POS))

/* 0x004 : osd_pb_result0 */
#define OSD_PB_RESULT0_OFFSET             (0x004)
#define OSD_PB_STS_OSD_PB_RESULT_0_R      OSD_PB_STS_OSD_PB_RESULT_0_R
#define OSD_PB_STS_OSD_PB_RESULT_0_R_POS  (0U)
#define OSD_PB_STS_OSD_PB_RESULT_0_R_LEN  (32U)
#define OSD_PB_STS_OSD_PB_RESULT_0_R_MSK  (((1U << OSD_PB_STS_OSD_PB_RESULT_0_R_LEN) - 1) << OSD_PB_STS_OSD_PB_RESULT_0_R_POS)
#define OSD_PB_STS_OSD_PB_RESULT_0_R_UMSK (~(((1U << OSD_PB_STS_OSD_PB_RESULT_0_R_LEN) - 1) << OSD_PB_STS_OSD_PB_RESULT_0_R_POS))

/* 0x008 : osd_pb_result1 */
#define OSD_PB_RESULT1_OFFSET             (0x008)
#define OSD_PB_STS_OSD_PB_RESULT_1_R      OSD_PB_STS_OSD_PB_RESULT_1_R
#define OSD_PB_STS_OSD_PB_RESULT_1_R_POS  (0U)
#define OSD_PB_STS_OSD_PB_RESULT_1_R_LEN  (32U)
#define OSD_PB_STS_OSD_PB_RESULT_1_R_MSK  (((1U << OSD_PB_STS_OSD_PB_RESULT_1_R_LEN) - 1) << OSD_PB_STS_OSD_PB_RESULT_1_R_POS)
#define OSD_PB_STS_OSD_PB_RESULT_1_R_UMSK (~(((1U << OSD_PB_STS_OSD_PB_RESULT_1_R_LEN) - 1) << OSD_PB_STS_OSD_PB_RESULT_1_R_POS))

/* 0x010 : osd_pb_addr_00 */
#define OSD_PB_ADDR_00_OFFSET       (0x010)
#define OSD_PB_REG_OSD_PB_X_00      OSD_PB_REG_OSD_PB_X_00
#define OSD_PB_REG_OSD_PB_X_00_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_00_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_00_MSK  (((1U << OSD_PB_REG_OSD_PB_X_00_LEN) - 1) << OSD_PB_REG_OSD_PB_X_00_POS)
#define OSD_PB_REG_OSD_PB_X_00_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_00_LEN) - 1) << OSD_PB_REG_OSD_PB_X_00_POS))
#define OSD_PB_REG_OSD_PB_Y_00      OSD_PB_REG_OSD_PB_Y_00
#define OSD_PB_REG_OSD_PB_Y_00_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_00_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_00_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_00_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_00_POS)
#define OSD_PB_REG_OSD_PB_Y_00_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_00_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_00_POS))

/* 0x014 : osd_pb_addr_01 */
#define OSD_PB_ADDR_01_OFFSET       (0x014)
#define OSD_PB_REG_OSD_PB_X_01      OSD_PB_REG_OSD_PB_X_01
#define OSD_PB_REG_OSD_PB_X_01_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_01_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_01_MSK  (((1U << OSD_PB_REG_OSD_PB_X_01_LEN) - 1) << OSD_PB_REG_OSD_PB_X_01_POS)
#define OSD_PB_REG_OSD_PB_X_01_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_01_LEN) - 1) << OSD_PB_REG_OSD_PB_X_01_POS))
#define OSD_PB_REG_OSD_PB_Y_01      OSD_PB_REG_OSD_PB_Y_01
#define OSD_PB_REG_OSD_PB_Y_01_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_01_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_01_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_01_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_01_POS)
#define OSD_PB_REG_OSD_PB_Y_01_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_01_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_01_POS))

/* 0x018 : osd_pb_addr_02 */
#define OSD_PB_ADDR_02_OFFSET       (0x018)
#define OSD_PB_REG_OSD_PB_X_02      OSD_PB_REG_OSD_PB_X_02
#define OSD_PB_REG_OSD_PB_X_02_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_02_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_02_MSK  (((1U << OSD_PB_REG_OSD_PB_X_02_LEN) - 1) << OSD_PB_REG_OSD_PB_X_02_POS)
#define OSD_PB_REG_OSD_PB_X_02_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_02_LEN) - 1) << OSD_PB_REG_OSD_PB_X_02_POS))
#define OSD_PB_REG_OSD_PB_Y_02      OSD_PB_REG_OSD_PB_Y_02
#define OSD_PB_REG_OSD_PB_Y_02_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_02_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_02_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_02_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_02_POS)
#define OSD_PB_REG_OSD_PB_Y_02_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_02_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_02_POS))

/* 0x01C : osd_pb_addr_03 */
#define OSD_PB_ADDR_03_OFFSET       (0x01C)
#define OSD_PB_REG_OSD_PB_X_03      OSD_PB_REG_OSD_PB_X_03
#define OSD_PB_REG_OSD_PB_X_03_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_03_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_03_MSK  (((1U << OSD_PB_REG_OSD_PB_X_03_LEN) - 1) << OSD_PB_REG_OSD_PB_X_03_POS)
#define OSD_PB_REG_OSD_PB_X_03_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_03_LEN) - 1) << OSD_PB_REG_OSD_PB_X_03_POS))
#define OSD_PB_REG_OSD_PB_Y_03      OSD_PB_REG_OSD_PB_Y_03
#define OSD_PB_REG_OSD_PB_Y_03_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_03_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_03_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_03_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_03_POS)
#define OSD_PB_REG_OSD_PB_Y_03_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_03_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_03_POS))

/* 0x020 : osd_pb_addr_04 */
#define OSD_PB_ADDR_04_OFFSET       (0x020)
#define OSD_PB_REG_OSD_PB_X_04      OSD_PB_REG_OSD_PB_X_04
#define OSD_PB_REG_OSD_PB_X_04_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_04_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_04_MSK  (((1U << OSD_PB_REG_OSD_PB_X_04_LEN) - 1) << OSD_PB_REG_OSD_PB_X_04_POS)
#define OSD_PB_REG_OSD_PB_X_04_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_04_LEN) - 1) << OSD_PB_REG_OSD_PB_X_04_POS))
#define OSD_PB_REG_OSD_PB_Y_04      OSD_PB_REG_OSD_PB_Y_04
#define OSD_PB_REG_OSD_PB_Y_04_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_04_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_04_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_04_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_04_POS)
#define OSD_PB_REG_OSD_PB_Y_04_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_04_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_04_POS))

/* 0x024 : osd_pb_addr_05 */
#define OSD_PB_ADDR_05_OFFSET       (0x024)
#define OSD_PB_REG_OSD_PB_X_05      OSD_PB_REG_OSD_PB_X_05
#define OSD_PB_REG_OSD_PB_X_05_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_05_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_05_MSK  (((1U << OSD_PB_REG_OSD_PB_X_05_LEN) - 1) << OSD_PB_REG_OSD_PB_X_05_POS)
#define OSD_PB_REG_OSD_PB_X_05_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_05_LEN) - 1) << OSD_PB_REG_OSD_PB_X_05_POS))
#define OSD_PB_REG_OSD_PB_Y_05      OSD_PB_REG_OSD_PB_Y_05
#define OSD_PB_REG_OSD_PB_Y_05_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_05_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_05_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_05_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_05_POS)
#define OSD_PB_REG_OSD_PB_Y_05_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_05_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_05_POS))

/* 0x028 : osd_pb_addr_06 */
#define OSD_PB_ADDR_06_OFFSET       (0x028)
#define OSD_PB_REG_OSD_PB_X_06      OSD_PB_REG_OSD_PB_X_06
#define OSD_PB_REG_OSD_PB_X_06_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_06_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_06_MSK  (((1U << OSD_PB_REG_OSD_PB_X_06_LEN) - 1) << OSD_PB_REG_OSD_PB_X_06_POS)
#define OSD_PB_REG_OSD_PB_X_06_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_06_LEN) - 1) << OSD_PB_REG_OSD_PB_X_06_POS))
#define OSD_PB_REG_OSD_PB_Y_06      OSD_PB_REG_OSD_PB_Y_06
#define OSD_PB_REG_OSD_PB_Y_06_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_06_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_06_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_06_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_06_POS)
#define OSD_PB_REG_OSD_PB_Y_06_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_06_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_06_POS))

/* 0x02C : osd_pb_addr_07 */
#define OSD_PB_ADDR_07_OFFSET       (0x02C)
#define OSD_PB_REG_OSD_PB_X_07      OSD_PB_REG_OSD_PB_X_07
#define OSD_PB_REG_OSD_PB_X_07_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_07_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_07_MSK  (((1U << OSD_PB_REG_OSD_PB_X_07_LEN) - 1) << OSD_PB_REG_OSD_PB_X_07_POS)
#define OSD_PB_REG_OSD_PB_X_07_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_07_LEN) - 1) << OSD_PB_REG_OSD_PB_X_07_POS))
#define OSD_PB_REG_OSD_PB_Y_07      OSD_PB_REG_OSD_PB_Y_07
#define OSD_PB_REG_OSD_PB_Y_07_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_07_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_07_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_07_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_07_POS)
#define OSD_PB_REG_OSD_PB_Y_07_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_07_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_07_POS))

/* 0x030 : osd_pb_addr_08 */
#define OSD_PB_ADDR_08_OFFSET       (0x030)
#define OSD_PB_REG_OSD_PB_X_08      OSD_PB_REG_OSD_PB_X_08
#define OSD_PB_REG_OSD_PB_X_08_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_08_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_08_MSK  (((1U << OSD_PB_REG_OSD_PB_X_08_LEN) - 1) << OSD_PB_REG_OSD_PB_X_08_POS)
#define OSD_PB_REG_OSD_PB_X_08_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_08_LEN) - 1) << OSD_PB_REG_OSD_PB_X_08_POS))
#define OSD_PB_REG_OSD_PB_Y_08      OSD_PB_REG_OSD_PB_Y_08
#define OSD_PB_REG_OSD_PB_Y_08_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_08_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_08_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_08_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_08_POS)
#define OSD_PB_REG_OSD_PB_Y_08_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_08_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_08_POS))

/* 0x034 : osd_pb_addr_09 */
#define OSD_PB_ADDR_09_OFFSET       (0x034)
#define OSD_PB_REG_OSD_PB_X_09      OSD_PB_REG_OSD_PB_X_09
#define OSD_PB_REG_OSD_PB_X_09_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_09_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_09_MSK  (((1U << OSD_PB_REG_OSD_PB_X_09_LEN) - 1) << OSD_PB_REG_OSD_PB_X_09_POS)
#define OSD_PB_REG_OSD_PB_X_09_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_09_LEN) - 1) << OSD_PB_REG_OSD_PB_X_09_POS))
#define OSD_PB_REG_OSD_PB_Y_09      OSD_PB_REG_OSD_PB_Y_09
#define OSD_PB_REG_OSD_PB_Y_09_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_09_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_09_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_09_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_09_POS)
#define OSD_PB_REG_OSD_PB_Y_09_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_09_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_09_POS))

/* 0x038 : osd_pb_addr_0a */
#define OSD_PB_ADDR_0A_OFFSET       (0x038)
#define OSD_PB_REG_OSD_PB_X_0A      OSD_PB_REG_OSD_PB_X_0A
#define OSD_PB_REG_OSD_PB_X_0A_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_0A_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_0A_MSK  (((1U << OSD_PB_REG_OSD_PB_X_0A_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0A_POS)
#define OSD_PB_REG_OSD_PB_X_0A_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_0A_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0A_POS))
#define OSD_PB_REG_OSD_PB_Y_0A      OSD_PB_REG_OSD_PB_Y_0A
#define OSD_PB_REG_OSD_PB_Y_0A_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_0A_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_0A_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_0A_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0A_POS)
#define OSD_PB_REG_OSD_PB_Y_0A_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_0A_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0A_POS))

/* 0x03C : osd_pb_addr_0b */
#define OSD_PB_ADDR_0B_OFFSET       (0x03C)
#define OSD_PB_REG_OSD_PB_X_0B      OSD_PB_REG_OSD_PB_X_0B
#define OSD_PB_REG_OSD_PB_X_0B_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_0B_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_0B_MSK  (((1U << OSD_PB_REG_OSD_PB_X_0B_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0B_POS)
#define OSD_PB_REG_OSD_PB_X_0B_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_0B_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0B_POS))
#define OSD_PB_REG_OSD_PB_Y_0B      OSD_PB_REG_OSD_PB_Y_0B
#define OSD_PB_REG_OSD_PB_Y_0B_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_0B_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_0B_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_0B_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0B_POS)
#define OSD_PB_REG_OSD_PB_Y_0B_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_0B_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0B_POS))

/* 0x040 : osd_pb_addr_0c */
#define OSD_PB_ADDR_0C_OFFSET       (0x040)
#define OSD_PB_REG_OSD_PB_X_0C      OSD_PB_REG_OSD_PB_X_0C
#define OSD_PB_REG_OSD_PB_X_0C_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_0C_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_0C_MSK  (((1U << OSD_PB_REG_OSD_PB_X_0C_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0C_POS)
#define OSD_PB_REG_OSD_PB_X_0C_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_0C_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0C_POS))
#define OSD_PB_REG_OSD_PB_Y_0C      OSD_PB_REG_OSD_PB_Y_0C
#define OSD_PB_REG_OSD_PB_Y_0C_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_0C_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_0C_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_0C_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0C_POS)
#define OSD_PB_REG_OSD_PB_Y_0C_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_0C_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0C_POS))

/* 0x044 : osd_pb_addr_0d */
#define OSD_PB_ADDR_0D_OFFSET       (0x044)
#define OSD_PB_REG_OSD_PB_X_0D      OSD_PB_REG_OSD_PB_X_0D
#define OSD_PB_REG_OSD_PB_X_0D_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_0D_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_0D_MSK  (((1U << OSD_PB_REG_OSD_PB_X_0D_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0D_POS)
#define OSD_PB_REG_OSD_PB_X_0D_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_0D_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0D_POS))
#define OSD_PB_REG_OSD_PB_Y_0D      OSD_PB_REG_OSD_PB_Y_0D
#define OSD_PB_REG_OSD_PB_Y_0D_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_0D_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_0D_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_0D_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0D_POS)
#define OSD_PB_REG_OSD_PB_Y_0D_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_0D_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0D_POS))

/* 0x048 : osd_pb_addr_0e */
#define OSD_PB_ADDR_0E_OFFSET       (0x048)
#define OSD_PB_REG_OSD_PB_X_0E      OSD_PB_REG_OSD_PB_X_0E
#define OSD_PB_REG_OSD_PB_X_0E_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_0E_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_0E_MSK  (((1U << OSD_PB_REG_OSD_PB_X_0E_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0E_POS)
#define OSD_PB_REG_OSD_PB_X_0E_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_0E_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0E_POS))
#define OSD_PB_REG_OSD_PB_Y_0E      OSD_PB_REG_OSD_PB_Y_0E
#define OSD_PB_REG_OSD_PB_Y_0E_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_0E_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_0E_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_0E_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0E_POS)
#define OSD_PB_REG_OSD_PB_Y_0E_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_0E_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0E_POS))

/* 0x04C : osd_pb_addr_0f */
#define OSD_PB_ADDR_0F_OFFSET       (0x04C)
#define OSD_PB_REG_OSD_PB_X_0F      OSD_PB_REG_OSD_PB_X_0F
#define OSD_PB_REG_OSD_PB_X_0F_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_0F_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_0F_MSK  (((1U << OSD_PB_REG_OSD_PB_X_0F_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0F_POS)
#define OSD_PB_REG_OSD_PB_X_0F_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_0F_LEN) - 1) << OSD_PB_REG_OSD_PB_X_0F_POS))
#define OSD_PB_REG_OSD_PB_Y_0F      OSD_PB_REG_OSD_PB_Y_0F
#define OSD_PB_REG_OSD_PB_Y_0F_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_0F_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_0F_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_0F_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0F_POS)
#define OSD_PB_REG_OSD_PB_Y_0F_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_0F_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_0F_POS))

/* 0x050 : osd_pb_addr_10 */
#define OSD_PB_ADDR_10_OFFSET       (0x050)
#define OSD_PB_REG_OSD_PB_X_10      OSD_PB_REG_OSD_PB_X_10
#define OSD_PB_REG_OSD_PB_X_10_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_10_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_10_MSK  (((1U << OSD_PB_REG_OSD_PB_X_10_LEN) - 1) << OSD_PB_REG_OSD_PB_X_10_POS)
#define OSD_PB_REG_OSD_PB_X_10_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_10_LEN) - 1) << OSD_PB_REG_OSD_PB_X_10_POS))
#define OSD_PB_REG_OSD_PB_Y_10      OSD_PB_REG_OSD_PB_Y_10
#define OSD_PB_REG_OSD_PB_Y_10_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_10_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_10_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_10_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_10_POS)
#define OSD_PB_REG_OSD_PB_Y_10_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_10_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_10_POS))

/* 0x054 : osd_pb_addr_11 */
#define OSD_PB_ADDR_11_OFFSET       (0x054)
#define OSD_PB_REG_OSD_PB_X_11      OSD_PB_REG_OSD_PB_X_11
#define OSD_PB_REG_OSD_PB_X_11_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_11_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_11_MSK  (((1U << OSD_PB_REG_OSD_PB_X_11_LEN) - 1) << OSD_PB_REG_OSD_PB_X_11_POS)
#define OSD_PB_REG_OSD_PB_X_11_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_11_LEN) - 1) << OSD_PB_REG_OSD_PB_X_11_POS))
#define OSD_PB_REG_OSD_PB_Y_11      OSD_PB_REG_OSD_PB_Y_11
#define OSD_PB_REG_OSD_PB_Y_11_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_11_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_11_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_11_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_11_POS)
#define OSD_PB_REG_OSD_PB_Y_11_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_11_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_11_POS))

/* 0x058 : osd_pb_addr_12 */
#define OSD_PB_ADDR_12_OFFSET       (0x058)
#define OSD_PB_REG_OSD_PB_X_12      OSD_PB_REG_OSD_PB_X_12
#define OSD_PB_REG_OSD_PB_X_12_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_12_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_12_MSK  (((1U << OSD_PB_REG_OSD_PB_X_12_LEN) - 1) << OSD_PB_REG_OSD_PB_X_12_POS)
#define OSD_PB_REG_OSD_PB_X_12_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_12_LEN) - 1) << OSD_PB_REG_OSD_PB_X_12_POS))
#define OSD_PB_REG_OSD_PB_Y_12      OSD_PB_REG_OSD_PB_Y_12
#define OSD_PB_REG_OSD_PB_Y_12_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_12_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_12_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_12_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_12_POS)
#define OSD_PB_REG_OSD_PB_Y_12_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_12_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_12_POS))

/* 0x05C : osd_pb_addr_13 */
#define OSD_PB_ADDR_13_OFFSET       (0x05C)
#define OSD_PB_REG_OSD_PB_X_13      OSD_PB_REG_OSD_PB_X_13
#define OSD_PB_REG_OSD_PB_X_13_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_13_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_13_MSK  (((1U << OSD_PB_REG_OSD_PB_X_13_LEN) - 1) << OSD_PB_REG_OSD_PB_X_13_POS)
#define OSD_PB_REG_OSD_PB_X_13_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_13_LEN) - 1) << OSD_PB_REG_OSD_PB_X_13_POS))
#define OSD_PB_REG_OSD_PB_Y_13      OSD_PB_REG_OSD_PB_Y_13
#define OSD_PB_REG_OSD_PB_Y_13_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_13_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_13_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_13_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_13_POS)
#define OSD_PB_REG_OSD_PB_Y_13_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_13_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_13_POS))

/* 0x060 : osd_pb_addr_14 */
#define OSD_PB_ADDR_14_OFFSET       (0x060)
#define OSD_PB_REG_OSD_PB_X_14      OSD_PB_REG_OSD_PB_X_14
#define OSD_PB_REG_OSD_PB_X_14_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_14_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_14_MSK  (((1U << OSD_PB_REG_OSD_PB_X_14_LEN) - 1) << OSD_PB_REG_OSD_PB_X_14_POS)
#define OSD_PB_REG_OSD_PB_X_14_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_14_LEN) - 1) << OSD_PB_REG_OSD_PB_X_14_POS))
#define OSD_PB_REG_OSD_PB_Y_14      OSD_PB_REG_OSD_PB_Y_14
#define OSD_PB_REG_OSD_PB_Y_14_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_14_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_14_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_14_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_14_POS)
#define OSD_PB_REG_OSD_PB_Y_14_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_14_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_14_POS))

/* 0x064 : osd_pb_addr_15 */
#define OSD_PB_ADDR_15_OFFSET       (0x064)
#define OSD_PB_REG_OSD_PB_X_15      OSD_PB_REG_OSD_PB_X_15
#define OSD_PB_REG_OSD_PB_X_15_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_15_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_15_MSK  (((1U << OSD_PB_REG_OSD_PB_X_15_LEN) - 1) << OSD_PB_REG_OSD_PB_X_15_POS)
#define OSD_PB_REG_OSD_PB_X_15_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_15_LEN) - 1) << OSD_PB_REG_OSD_PB_X_15_POS))
#define OSD_PB_REG_OSD_PB_Y_15      OSD_PB_REG_OSD_PB_Y_15
#define OSD_PB_REG_OSD_PB_Y_15_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_15_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_15_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_15_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_15_POS)
#define OSD_PB_REG_OSD_PB_Y_15_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_15_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_15_POS))

/* 0x068 : osd_pb_addr_16 */
#define OSD_PB_ADDR_16_OFFSET       (0x068)
#define OSD_PB_REG_OSD_PB_X_16      OSD_PB_REG_OSD_PB_X_16
#define OSD_PB_REG_OSD_PB_X_16_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_16_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_16_MSK  (((1U << OSD_PB_REG_OSD_PB_X_16_LEN) - 1) << OSD_PB_REG_OSD_PB_X_16_POS)
#define OSD_PB_REG_OSD_PB_X_16_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_16_LEN) - 1) << OSD_PB_REG_OSD_PB_X_16_POS))
#define OSD_PB_REG_OSD_PB_Y_16      OSD_PB_REG_OSD_PB_Y_16
#define OSD_PB_REG_OSD_PB_Y_16_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_16_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_16_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_16_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_16_POS)
#define OSD_PB_REG_OSD_PB_Y_16_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_16_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_16_POS))

/* 0x06C : osd_pb_addr_17 */
#define OSD_PB_ADDR_17_OFFSET       (0x06C)
#define OSD_PB_REG_OSD_PB_X_17      OSD_PB_REG_OSD_PB_X_17
#define OSD_PB_REG_OSD_PB_X_17_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_17_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_17_MSK  (((1U << OSD_PB_REG_OSD_PB_X_17_LEN) - 1) << OSD_PB_REG_OSD_PB_X_17_POS)
#define OSD_PB_REG_OSD_PB_X_17_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_17_LEN) - 1) << OSD_PB_REG_OSD_PB_X_17_POS))
#define OSD_PB_REG_OSD_PB_Y_17      OSD_PB_REG_OSD_PB_Y_17
#define OSD_PB_REG_OSD_PB_Y_17_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_17_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_17_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_17_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_17_POS)
#define OSD_PB_REG_OSD_PB_Y_17_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_17_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_17_POS))

/* 0x070 : osd_pb_addr_18 */
#define OSD_PB_ADDR_18_OFFSET       (0x070)
#define OSD_PB_REG_OSD_PB_X_18      OSD_PB_REG_OSD_PB_X_18
#define OSD_PB_REG_OSD_PB_X_18_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_18_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_18_MSK  (((1U << OSD_PB_REG_OSD_PB_X_18_LEN) - 1) << OSD_PB_REG_OSD_PB_X_18_POS)
#define OSD_PB_REG_OSD_PB_X_18_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_18_LEN) - 1) << OSD_PB_REG_OSD_PB_X_18_POS))
#define OSD_PB_REG_OSD_PB_Y_18      OSD_PB_REG_OSD_PB_Y_18
#define OSD_PB_REG_OSD_PB_Y_18_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_18_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_18_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_18_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_18_POS)
#define OSD_PB_REG_OSD_PB_Y_18_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_18_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_18_POS))

/* 0x074 : osd_pb_addr_19 */
#define OSD_PB_ADDR_19_OFFSET       (0x074)
#define OSD_PB_REG_OSD_PB_X_19      OSD_PB_REG_OSD_PB_X_19
#define OSD_PB_REG_OSD_PB_X_19_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_19_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_19_MSK  (((1U << OSD_PB_REG_OSD_PB_X_19_LEN) - 1) << OSD_PB_REG_OSD_PB_X_19_POS)
#define OSD_PB_REG_OSD_PB_X_19_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_19_LEN) - 1) << OSD_PB_REG_OSD_PB_X_19_POS))
#define OSD_PB_REG_OSD_PB_Y_19      OSD_PB_REG_OSD_PB_Y_19
#define OSD_PB_REG_OSD_PB_Y_19_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_19_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_19_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_19_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_19_POS)
#define OSD_PB_REG_OSD_PB_Y_19_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_19_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_19_POS))

/* 0x078 : osd_pb_addr_1a */
#define OSD_PB_ADDR_1A_OFFSET       (0x078)
#define OSD_PB_REG_OSD_PB_X_1A      OSD_PB_REG_OSD_PB_X_1A
#define OSD_PB_REG_OSD_PB_X_1A_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_1A_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_1A_MSK  (((1U << OSD_PB_REG_OSD_PB_X_1A_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1A_POS)
#define OSD_PB_REG_OSD_PB_X_1A_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_1A_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1A_POS))
#define OSD_PB_REG_OSD_PB_Y_1A      OSD_PB_REG_OSD_PB_Y_1A
#define OSD_PB_REG_OSD_PB_Y_1A_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_1A_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_1A_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_1A_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1A_POS)
#define OSD_PB_REG_OSD_PB_Y_1A_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_1A_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1A_POS))

/* 0x07C : osd_pb_addr_1b */
#define OSD_PB_ADDR_1B_OFFSET       (0x07C)
#define OSD_PB_REG_OSD_PB_X_1B      OSD_PB_REG_OSD_PB_X_1B
#define OSD_PB_REG_OSD_PB_X_1B_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_1B_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_1B_MSK  (((1U << OSD_PB_REG_OSD_PB_X_1B_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1B_POS)
#define OSD_PB_REG_OSD_PB_X_1B_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_1B_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1B_POS))
#define OSD_PB_REG_OSD_PB_Y_1B      OSD_PB_REG_OSD_PB_Y_1B
#define OSD_PB_REG_OSD_PB_Y_1B_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_1B_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_1B_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_1B_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1B_POS)
#define OSD_PB_REG_OSD_PB_Y_1B_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_1B_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1B_POS))

/* 0x080 : osd_pb_addr_1c */
#define OSD_PB_ADDR_1C_OFFSET       (0x080)
#define OSD_PB_REG_OSD_PB_X_1C      OSD_PB_REG_OSD_PB_X_1C
#define OSD_PB_REG_OSD_PB_X_1C_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_1C_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_1C_MSK  (((1U << OSD_PB_REG_OSD_PB_X_1C_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1C_POS)
#define OSD_PB_REG_OSD_PB_X_1C_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_1C_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1C_POS))
#define OSD_PB_REG_OSD_PB_Y_1C      OSD_PB_REG_OSD_PB_Y_1C
#define OSD_PB_REG_OSD_PB_Y_1C_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_1C_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_1C_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_1C_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1C_POS)
#define OSD_PB_REG_OSD_PB_Y_1C_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_1C_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1C_POS))

/* 0x084 : osd_pb_addr_1d */
#define OSD_PB_ADDR_1D_OFFSET       (0x084)
#define OSD_PB_REG_OSD_PB_X_1D      OSD_PB_REG_OSD_PB_X_1D
#define OSD_PB_REG_OSD_PB_X_1D_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_1D_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_1D_MSK  (((1U << OSD_PB_REG_OSD_PB_X_1D_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1D_POS)
#define OSD_PB_REG_OSD_PB_X_1D_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_1D_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1D_POS))
#define OSD_PB_REG_OSD_PB_Y_1D      OSD_PB_REG_OSD_PB_Y_1D
#define OSD_PB_REG_OSD_PB_Y_1D_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_1D_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_1D_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_1D_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1D_POS)
#define OSD_PB_REG_OSD_PB_Y_1D_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_1D_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1D_POS))

/* 0x088 : osd_pb_addr_1e */
#define OSD_PB_ADDR_1E_OFFSET       (0x088)
#define OSD_PB_REG_OSD_PB_X_1E      OSD_PB_REG_OSD_PB_X_1E
#define OSD_PB_REG_OSD_PB_X_1E_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_1E_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_1E_MSK  (((1U << OSD_PB_REG_OSD_PB_X_1E_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1E_POS)
#define OSD_PB_REG_OSD_PB_X_1E_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_1E_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1E_POS))
#define OSD_PB_REG_OSD_PB_Y_1E      OSD_PB_REG_OSD_PB_Y_1E
#define OSD_PB_REG_OSD_PB_Y_1E_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_1E_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_1E_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_1E_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1E_POS)
#define OSD_PB_REG_OSD_PB_Y_1E_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_1E_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1E_POS))

/* 0x08C : osd_pb_addr_1f */
#define OSD_PB_ADDR_1F_OFFSET       (0x08C)
#define OSD_PB_REG_OSD_PB_X_1F      OSD_PB_REG_OSD_PB_X_1F
#define OSD_PB_REG_OSD_PB_X_1F_POS  (0U)
#define OSD_PB_REG_OSD_PB_X_1F_LEN  (11U)
#define OSD_PB_REG_OSD_PB_X_1F_MSK  (((1U << OSD_PB_REG_OSD_PB_X_1F_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1F_POS)
#define OSD_PB_REG_OSD_PB_X_1F_UMSK (~(((1U << OSD_PB_REG_OSD_PB_X_1F_LEN) - 1) << OSD_PB_REG_OSD_PB_X_1F_POS))
#define OSD_PB_REG_OSD_PB_Y_1F      OSD_PB_REG_OSD_PB_Y_1F
#define OSD_PB_REG_OSD_PB_Y_1F_POS  (16U)
#define OSD_PB_REG_OSD_PB_Y_1F_LEN  (11U)
#define OSD_PB_REG_OSD_PB_Y_1F_MSK  (((1U << OSD_PB_REG_OSD_PB_Y_1F_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1F_POS)
#define OSD_PB_REG_OSD_PB_Y_1F_UMSK (~(((1U << OSD_PB_REG_OSD_PB_Y_1F_LEN) - 1) << OSD_PB_REG_OSD_PB_Y_1F_POS))

struct osd_pb_reg {
    /* 0x000 : osd_pb_ctrl_reg */
    union {
        struct
        {
            uint32_t reg_osd_pb_luma_th : 8;  /* [ 7: 0],        r/w,        0x0 */
            uint32_t sts_osd_pb_w_cnt_r : 5;  /* [12: 8],          r,        0x0 */
            uint32_t reserved_13_14     : 2;  /* [14:13],       rsvd,        0x0 */
            uint32_t sts_osd_pb_idx_r   : 1;  /* [   15],          r,        0x0 */
            uint32_t reserved_16_31     : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_ctrl_reg;

    /* 0x004 : osd_pb_result0 */
    union {
        struct
        {
            uint32_t sts_osd_pb_result_0_r : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_result0;

    /* 0x008 : osd_pb_result1 */
    union {
        struct
        {
            uint32_t sts_osd_pb_result_1_r : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_result1;

    /* 0xc  reserved */
    uint8_t RESERVED0xc[4];

    /* 0x010 : osd_pb_addr_00 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_00 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_00 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_00;

    /* 0x014 : osd_pb_addr_01 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_01 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_01 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_01;

    /* 0x018 : osd_pb_addr_02 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_02 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_02 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_02;

    /* 0x01C : osd_pb_addr_03 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_03 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_03 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_03;

    /* 0x020 : osd_pb_addr_04 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_04 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_04 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_04;

    /* 0x024 : osd_pb_addr_05 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_05 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_05 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_05;

    /* 0x028 : osd_pb_addr_06 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_06 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_06 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_06;

    /* 0x02C : osd_pb_addr_07 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_07 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_07 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_07;

    /* 0x030 : osd_pb_addr_08 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_08 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_08 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_08;

    /* 0x034 : osd_pb_addr_09 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_09 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_09 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_09;

    /* 0x038 : osd_pb_addr_0a */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_0a : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_0a : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_0a;

    /* 0x03C : osd_pb_addr_0b */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_0b : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_0b : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_0b;

    /* 0x040 : osd_pb_addr_0c */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_0c : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_0c : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_0c;

    /* 0x044 : osd_pb_addr_0d */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_0d : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_0d : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_0d;

    /* 0x048 : osd_pb_addr_0e */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_0e : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_0e : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_0e;

    /* 0x04C : osd_pb_addr_0f */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_0f : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_0f : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_0f;

    /* 0x050 : osd_pb_addr_10 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_10 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_10 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_10;

    /* 0x054 : osd_pb_addr_11 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_11 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_11 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_11;

    /* 0x058 : osd_pb_addr_12 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_12 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_12 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_12;

    /* 0x05C : osd_pb_addr_13 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_13 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_13 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_13;

    /* 0x060 : osd_pb_addr_14 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_14 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_14 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_14;

    /* 0x064 : osd_pb_addr_15 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_15 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_15 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_15;

    /* 0x068 : osd_pb_addr_16 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_16 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_16 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_16;

    /* 0x06C : osd_pb_addr_17 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_17 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_17 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_17;

    /* 0x070 : osd_pb_addr_18 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_18 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_18 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_18;

    /* 0x074 : osd_pb_addr_19 */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_19 : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_19 : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_19;

    /* 0x078 : osd_pb_addr_1a */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_1a : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_1a : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_1a;

    /* 0x07C : osd_pb_addr_1b */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_1b : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_1b : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_1b;

    /* 0x080 : osd_pb_addr_1c */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_1c : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_1c : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_1c;

    /* 0x084 : osd_pb_addr_1d */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_1d : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_1d : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_1d;

    /* 0x088 : osd_pb_addr_1e */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_1e : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_1e : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_1e;

    /* 0x08C : osd_pb_addr_1f */
    union {
        struct
        {
            uint32_t reg_osd_pb_x_1f : 11; /* [10: 0],        r/w,        0x0 */
            uint32_t reserved_11_15  : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t reg_osd_pb_y_1f : 11; /* [26:16],        r/w,        0x0 */
            uint32_t reserved_27_31  : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } osd_pb_addr_1f;
};

typedef volatile struct osd_pb_reg osd_pb_reg_t;

#endif /* __OSD_PROBE_REG_H__ */
