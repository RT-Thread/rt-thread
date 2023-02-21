/**
  ******************************************************************************
  * @file    ir_reg.h
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
#ifndef __IR_REG_H__
#define __IR_REG_H__

#include "bl808.h"

/* 0x0 : irtx_config */
#define IRTX_CONFIG_OFFSET             (0x0)
#define IR_CR_IRTX_EN                  IR_CR_IRTX_EN
#define IR_CR_IRTX_EN_POS              (0U)
#define IR_CR_IRTX_EN_LEN              (1U)
#define IR_CR_IRTX_EN_MSK              (((1U << IR_CR_IRTX_EN_LEN) - 1) << IR_CR_IRTX_EN_POS)
#define IR_CR_IRTX_EN_UMSK             (~(((1U << IR_CR_IRTX_EN_LEN) - 1) << IR_CR_IRTX_EN_POS))
#define IR_CR_IRTX_OUT_INV             IR_CR_IRTX_OUT_INV
#define IR_CR_IRTX_OUT_INV_POS         (1U)
#define IR_CR_IRTX_OUT_INV_LEN         (1U)
#define IR_CR_IRTX_OUT_INV_MSK         (((1U << IR_CR_IRTX_OUT_INV_LEN) - 1) << IR_CR_IRTX_OUT_INV_POS)
#define IR_CR_IRTX_OUT_INV_UMSK        (~(((1U << IR_CR_IRTX_OUT_INV_LEN) - 1) << IR_CR_IRTX_OUT_INV_POS))
#define IR_CR_IRTX_MOD_EN              IR_CR_IRTX_MOD_EN
#define IR_CR_IRTX_MOD_EN_POS          (2U)
#define IR_CR_IRTX_MOD_EN_LEN          (1U)
#define IR_CR_IRTX_MOD_EN_MSK          (((1U << IR_CR_IRTX_MOD_EN_LEN) - 1) << IR_CR_IRTX_MOD_EN_POS)
#define IR_CR_IRTX_MOD_EN_UMSK         (~(((1U << IR_CR_IRTX_MOD_EN_LEN) - 1) << IR_CR_IRTX_MOD_EN_POS))
#define IR_CR_IRTX_SWM_EN              IR_CR_IRTX_SWM_EN
#define IR_CR_IRTX_SWM_EN_POS          (3U)
#define IR_CR_IRTX_SWM_EN_LEN          (1U)
#define IR_CR_IRTX_SWM_EN_MSK          (((1U << IR_CR_IRTX_SWM_EN_LEN) - 1) << IR_CR_IRTX_SWM_EN_POS)
#define IR_CR_IRTX_SWM_EN_UMSK         (~(((1U << IR_CR_IRTX_SWM_EN_LEN) - 1) << IR_CR_IRTX_SWM_EN_POS))
#define IR_CR_IRTX_DATA_EN             IR_CR_IRTX_DATA_EN
#define IR_CR_IRTX_DATA_EN_POS         (4U)
#define IR_CR_IRTX_DATA_EN_LEN         (1U)
#define IR_CR_IRTX_DATA_EN_MSK         (((1U << IR_CR_IRTX_DATA_EN_LEN) - 1) << IR_CR_IRTX_DATA_EN_POS)
#define IR_CR_IRTX_DATA_EN_UMSK        (~(((1U << IR_CR_IRTX_DATA_EN_LEN) - 1) << IR_CR_IRTX_DATA_EN_POS))
#define IR_CR_IRTX_LOGIC0_HL_INV       IR_CR_IRTX_LOGIC0_HL_INV
#define IR_CR_IRTX_LOGIC0_HL_INV_POS   (5U)
#define IR_CR_IRTX_LOGIC0_HL_INV_LEN   (1U)
#define IR_CR_IRTX_LOGIC0_HL_INV_MSK   (((1U << IR_CR_IRTX_LOGIC0_HL_INV_LEN) - 1) << IR_CR_IRTX_LOGIC0_HL_INV_POS)
#define IR_CR_IRTX_LOGIC0_HL_INV_UMSK  (~(((1U << IR_CR_IRTX_LOGIC0_HL_INV_LEN) - 1) << IR_CR_IRTX_LOGIC0_HL_INV_POS))
#define IR_CR_IRTX_LOGIC1_HL_INV       IR_CR_IRTX_LOGIC1_HL_INV
#define IR_CR_IRTX_LOGIC1_HL_INV_POS   (6U)
#define IR_CR_IRTX_LOGIC1_HL_INV_LEN   (1U)
#define IR_CR_IRTX_LOGIC1_HL_INV_MSK   (((1U << IR_CR_IRTX_LOGIC1_HL_INV_LEN) - 1) << IR_CR_IRTX_LOGIC1_HL_INV_POS)
#define IR_CR_IRTX_LOGIC1_HL_INV_UMSK  (~(((1U << IR_CR_IRTX_LOGIC1_HL_INV_LEN) - 1) << IR_CR_IRTX_LOGIC1_HL_INV_POS))
#define IR_CR_IRTX_HEAD_EN             IR_CR_IRTX_HEAD_EN
#define IR_CR_IRTX_HEAD_EN_POS         (8U)
#define IR_CR_IRTX_HEAD_EN_LEN         (1U)
#define IR_CR_IRTX_HEAD_EN_MSK         (((1U << IR_CR_IRTX_HEAD_EN_LEN) - 1) << IR_CR_IRTX_HEAD_EN_POS)
#define IR_CR_IRTX_HEAD_EN_UMSK        (~(((1U << IR_CR_IRTX_HEAD_EN_LEN) - 1) << IR_CR_IRTX_HEAD_EN_POS))
#define IR_CR_IRTX_HEAD_HL_INV         IR_CR_IRTX_HEAD_HL_INV
#define IR_CR_IRTX_HEAD_HL_INV_POS     (9U)
#define IR_CR_IRTX_HEAD_HL_INV_LEN     (1U)
#define IR_CR_IRTX_HEAD_HL_INV_MSK     (((1U << IR_CR_IRTX_HEAD_HL_INV_LEN) - 1) << IR_CR_IRTX_HEAD_HL_INV_POS)
#define IR_CR_IRTX_HEAD_HL_INV_UMSK    (~(((1U << IR_CR_IRTX_HEAD_HL_INV_LEN) - 1) << IR_CR_IRTX_HEAD_HL_INV_POS))
#define IR_CR_IRTX_TAIL_EN             IR_CR_IRTX_TAIL_EN
#define IR_CR_IRTX_TAIL_EN_POS         (10U)
#define IR_CR_IRTX_TAIL_EN_LEN         (1U)
#define IR_CR_IRTX_TAIL_EN_MSK         (((1U << IR_CR_IRTX_TAIL_EN_LEN) - 1) << IR_CR_IRTX_TAIL_EN_POS)
#define IR_CR_IRTX_TAIL_EN_UMSK        (~(((1U << IR_CR_IRTX_TAIL_EN_LEN) - 1) << IR_CR_IRTX_TAIL_EN_POS))
#define IR_CR_IRTX_TAIL_HL_INV         IR_CR_IRTX_TAIL_HL_INV
#define IR_CR_IRTX_TAIL_HL_INV_POS     (11U)
#define IR_CR_IRTX_TAIL_HL_INV_LEN     (1U)
#define IR_CR_IRTX_TAIL_HL_INV_MSK     (((1U << IR_CR_IRTX_TAIL_HL_INV_LEN) - 1) << IR_CR_IRTX_TAIL_HL_INV_POS)
#define IR_CR_IRTX_TAIL_HL_INV_UMSK    (~(((1U << IR_CR_IRTX_TAIL_HL_INV_LEN) - 1) << IR_CR_IRTX_TAIL_HL_INV_POS))
#define IR_CR_IRTX_FRM_EN              IR_CR_IRTX_FRM_EN
#define IR_CR_IRTX_FRM_EN_POS          (12U)
#define IR_CR_IRTX_FRM_EN_LEN          (1U)
#define IR_CR_IRTX_FRM_EN_MSK          (((1U << IR_CR_IRTX_FRM_EN_LEN) - 1) << IR_CR_IRTX_FRM_EN_POS)
#define IR_CR_IRTX_FRM_EN_UMSK         (~(((1U << IR_CR_IRTX_FRM_EN_LEN) - 1) << IR_CR_IRTX_FRM_EN_POS))
#define IR_CR_IRTX_FRM_CONT_EN         IR_CR_IRTX_FRM_CONT_EN
#define IR_CR_IRTX_FRM_CONT_EN_POS     (13U)
#define IR_CR_IRTX_FRM_CONT_EN_LEN     (1U)
#define IR_CR_IRTX_FRM_CONT_EN_MSK     (((1U << IR_CR_IRTX_FRM_CONT_EN_LEN) - 1) << IR_CR_IRTX_FRM_CONT_EN_POS)
#define IR_CR_IRTX_FRM_CONT_EN_UMSK    (~(((1U << IR_CR_IRTX_FRM_CONT_EN_LEN) - 1) << IR_CR_IRTX_FRM_CONT_EN_POS))
#define IR_CR_IRTX_FRM_FRAME_SIZE      IR_CR_IRTX_FRM_FRAME_SIZE
#define IR_CR_IRTX_FRM_FRAME_SIZE_POS  (14U)
#define IR_CR_IRTX_FRM_FRAME_SIZE_LEN  (2U)
#define IR_CR_IRTX_FRM_FRAME_SIZE_MSK  (((1U << IR_CR_IRTX_FRM_FRAME_SIZE_LEN) - 1) << IR_CR_IRTX_FRM_FRAME_SIZE_POS)
#define IR_CR_IRTX_FRM_FRAME_SIZE_UMSK (~(((1U << IR_CR_IRTX_FRM_FRAME_SIZE_LEN) - 1) << IR_CR_IRTX_FRM_FRAME_SIZE_POS))
#define IR_CR_IRTX_DATA_NUM            IR_CR_IRTX_DATA_NUM
#define IR_CR_IRTX_DATA_NUM_POS        (16U)
#define IR_CR_IRTX_DATA_NUM_LEN        (7U)
#define IR_CR_IRTX_DATA_NUM_MSK        (((1U << IR_CR_IRTX_DATA_NUM_LEN) - 1) << IR_CR_IRTX_DATA_NUM_POS)
#define IR_CR_IRTX_DATA_NUM_UMSK       (~(((1U << IR_CR_IRTX_DATA_NUM_LEN) - 1) << IR_CR_IRTX_DATA_NUM_POS))

/* 0x4 : irtx_int_sts */
#define IRTX_INT_STS_OFFSET       (0x4)
#define IRTX_END_INT              IRTX_END_INT
#define IRTX_END_INT_POS          (0U)
#define IRTX_END_INT_LEN          (1U)
#define IRTX_END_INT_MSK          (((1U << IRTX_END_INT_LEN) - 1) << IRTX_END_INT_POS)
#define IRTX_END_INT_UMSK         (~(((1U << IRTX_END_INT_LEN) - 1) << IRTX_END_INT_POS))
#define IRTX_FRDY_INT             IRTX_FRDY_INT
#define IRTX_FRDY_INT_POS         (1U)
#define IRTX_FRDY_INT_LEN         (1U)
#define IRTX_FRDY_INT_MSK         (((1U << IRTX_FRDY_INT_LEN) - 1) << IRTX_FRDY_INT_POS)
#define IRTX_FRDY_INT_UMSK        (~(((1U << IRTX_FRDY_INT_LEN) - 1) << IRTX_FRDY_INT_POS))
#define IRTX_FER_INT              IRTX_FER_INT
#define IRTX_FER_INT_POS          (2U)
#define IRTX_FER_INT_LEN          (1U)
#define IRTX_FER_INT_MSK          (((1U << IRTX_FER_INT_LEN) - 1) << IRTX_FER_INT_POS)
#define IRTX_FER_INT_UMSK         (~(((1U << IRTX_FER_INT_LEN) - 1) << IRTX_FER_INT_POS))
#define IR_CR_IRTX_END_MASK       IR_CR_IRTX_END_MASK
#define IR_CR_IRTX_END_MASK_POS   (8U)
#define IR_CR_IRTX_END_MASK_LEN   (1U)
#define IR_CR_IRTX_END_MASK_MSK   (((1U << IR_CR_IRTX_END_MASK_LEN) - 1) << IR_CR_IRTX_END_MASK_POS)
#define IR_CR_IRTX_END_MASK_UMSK  (~(((1U << IR_CR_IRTX_END_MASK_LEN) - 1) << IR_CR_IRTX_END_MASK_POS))
#define IR_CR_IRTX_FRDY_MASK      IR_CR_IRTX_FRDY_MASK
#define IR_CR_IRTX_FRDY_MASK_POS  (9U)
#define IR_CR_IRTX_FRDY_MASK_LEN  (1U)
#define IR_CR_IRTX_FRDY_MASK_MSK  (((1U << IR_CR_IRTX_FRDY_MASK_LEN) - 1) << IR_CR_IRTX_FRDY_MASK_POS)
#define IR_CR_IRTX_FRDY_MASK_UMSK (~(((1U << IR_CR_IRTX_FRDY_MASK_LEN) - 1) << IR_CR_IRTX_FRDY_MASK_POS))
#define IR_CR_IRTX_FER_MASK       IR_CR_IRTX_FER_MASK
#define IR_CR_IRTX_FER_MASK_POS   (10U)
#define IR_CR_IRTX_FER_MASK_LEN   (1U)
#define IR_CR_IRTX_FER_MASK_MSK   (((1U << IR_CR_IRTX_FER_MASK_LEN) - 1) << IR_CR_IRTX_FER_MASK_POS)
#define IR_CR_IRTX_FER_MASK_UMSK  (~(((1U << IR_CR_IRTX_FER_MASK_LEN) - 1) << IR_CR_IRTX_FER_MASK_POS))
#define IR_CR_IRTX_END_CLR        IR_CR_IRTX_END_CLR
#define IR_CR_IRTX_END_CLR_POS    (16U)
#define IR_CR_IRTX_END_CLR_LEN    (1U)
#define IR_CR_IRTX_END_CLR_MSK    (((1U << IR_CR_IRTX_END_CLR_LEN) - 1) << IR_CR_IRTX_END_CLR_POS)
#define IR_CR_IRTX_END_CLR_UMSK   (~(((1U << IR_CR_IRTX_END_CLR_LEN) - 1) << IR_CR_IRTX_END_CLR_POS))
#define IR_CR_IRTX_END_EN         IR_CR_IRTX_END_EN
#define IR_CR_IRTX_END_EN_POS     (24U)
#define IR_CR_IRTX_END_EN_LEN     (1U)
#define IR_CR_IRTX_END_EN_MSK     (((1U << IR_CR_IRTX_END_EN_LEN) - 1) << IR_CR_IRTX_END_EN_POS)
#define IR_CR_IRTX_END_EN_UMSK    (~(((1U << IR_CR_IRTX_END_EN_LEN) - 1) << IR_CR_IRTX_END_EN_POS))
#define IR_CR_IRTX_FRDY_EN        IR_CR_IRTX_FRDY_EN
#define IR_CR_IRTX_FRDY_EN_POS    (25U)
#define IR_CR_IRTX_FRDY_EN_LEN    (1U)
#define IR_CR_IRTX_FRDY_EN_MSK    (((1U << IR_CR_IRTX_FRDY_EN_LEN) - 1) << IR_CR_IRTX_FRDY_EN_POS)
#define IR_CR_IRTX_FRDY_EN_UMSK   (~(((1U << IR_CR_IRTX_FRDY_EN_LEN) - 1) << IR_CR_IRTX_FRDY_EN_POS))
#define IR_CR_IRTX_FER_EN         IR_CR_IRTX_FER_EN
#define IR_CR_IRTX_FER_EN_POS     (26U)
#define IR_CR_IRTX_FER_EN_LEN     (1U)
#define IR_CR_IRTX_FER_EN_MSK     (((1U << IR_CR_IRTX_FER_EN_LEN) - 1) << IR_CR_IRTX_FER_EN_POS)
#define IR_CR_IRTX_FER_EN_UMSK    (~(((1U << IR_CR_IRTX_FER_EN_LEN) - 1) << IR_CR_IRTX_FER_EN_POS))

/* 0x10 : irtx_pulse_width */
#define IRTX_PULSE_WIDTH_OFFSET   (0x10)
#define IR_CR_IRTX_PW_UNIT        IR_CR_IRTX_PW_UNIT
#define IR_CR_IRTX_PW_UNIT_POS    (0U)
#define IR_CR_IRTX_PW_UNIT_LEN    (12U)
#define IR_CR_IRTX_PW_UNIT_MSK    (((1U << IR_CR_IRTX_PW_UNIT_LEN) - 1) << IR_CR_IRTX_PW_UNIT_POS)
#define IR_CR_IRTX_PW_UNIT_UMSK   (~(((1U << IR_CR_IRTX_PW_UNIT_LEN) - 1) << IR_CR_IRTX_PW_UNIT_POS))
#define IR_CR_IRTX_MOD_PH0_W      IR_CR_IRTX_MOD_PH0_W
#define IR_CR_IRTX_MOD_PH0_W_POS  (16U)
#define IR_CR_IRTX_MOD_PH0_W_LEN  (8U)
#define IR_CR_IRTX_MOD_PH0_W_MSK  (((1U << IR_CR_IRTX_MOD_PH0_W_LEN) - 1) << IR_CR_IRTX_MOD_PH0_W_POS)
#define IR_CR_IRTX_MOD_PH0_W_UMSK (~(((1U << IR_CR_IRTX_MOD_PH0_W_LEN) - 1) << IR_CR_IRTX_MOD_PH0_W_POS))
#define IR_CR_IRTX_MOD_PH1_W      IR_CR_IRTX_MOD_PH1_W
#define IR_CR_IRTX_MOD_PH1_W_POS  (24U)
#define IR_CR_IRTX_MOD_PH1_W_LEN  (8U)
#define IR_CR_IRTX_MOD_PH1_W_MSK  (((1U << IR_CR_IRTX_MOD_PH1_W_LEN) - 1) << IR_CR_IRTX_MOD_PH1_W_POS)
#define IR_CR_IRTX_MOD_PH1_W_UMSK (~(((1U << IR_CR_IRTX_MOD_PH1_W_LEN) - 1) << IR_CR_IRTX_MOD_PH1_W_POS))

/* 0x14 : irtx_pw_0 */
#define IRTX_PW_0_OFFSET             (0x14)
#define IR_CR_IRTX_LOGIC0_PH0_W      IR_CR_IRTX_LOGIC0_PH0_W
#define IR_CR_IRTX_LOGIC0_PH0_W_POS  (0U)
#define IR_CR_IRTX_LOGIC0_PH0_W_LEN  (8U)
#define IR_CR_IRTX_LOGIC0_PH0_W_MSK  (((1U << IR_CR_IRTX_LOGIC0_PH0_W_LEN) - 1) << IR_CR_IRTX_LOGIC0_PH0_W_POS)
#define IR_CR_IRTX_LOGIC0_PH0_W_UMSK (~(((1U << IR_CR_IRTX_LOGIC0_PH0_W_LEN) - 1) << IR_CR_IRTX_LOGIC0_PH0_W_POS))
#define IR_CR_IRTX_LOGIC0_PH1_W      IR_CR_IRTX_LOGIC0_PH1_W
#define IR_CR_IRTX_LOGIC0_PH1_W_POS  (8U)
#define IR_CR_IRTX_LOGIC0_PH1_W_LEN  (8U)
#define IR_CR_IRTX_LOGIC0_PH1_W_MSK  (((1U << IR_CR_IRTX_LOGIC0_PH1_W_LEN) - 1) << IR_CR_IRTX_LOGIC0_PH1_W_POS)
#define IR_CR_IRTX_LOGIC0_PH1_W_UMSK (~(((1U << IR_CR_IRTX_LOGIC0_PH1_W_LEN) - 1) << IR_CR_IRTX_LOGIC0_PH1_W_POS))
#define IR_CR_IRTX_LOGIC1_PH0_W      IR_CR_IRTX_LOGIC1_PH0_W
#define IR_CR_IRTX_LOGIC1_PH0_W_POS  (16U)
#define IR_CR_IRTX_LOGIC1_PH0_W_LEN  (8U)
#define IR_CR_IRTX_LOGIC1_PH0_W_MSK  (((1U << IR_CR_IRTX_LOGIC1_PH0_W_LEN) - 1) << IR_CR_IRTX_LOGIC1_PH0_W_POS)
#define IR_CR_IRTX_LOGIC1_PH0_W_UMSK (~(((1U << IR_CR_IRTX_LOGIC1_PH0_W_LEN) - 1) << IR_CR_IRTX_LOGIC1_PH0_W_POS))
#define IR_CR_IRTX_LOGIC1_PH1_W      IR_CR_IRTX_LOGIC1_PH1_W
#define IR_CR_IRTX_LOGIC1_PH1_W_POS  (24U)
#define IR_CR_IRTX_LOGIC1_PH1_W_LEN  (8U)
#define IR_CR_IRTX_LOGIC1_PH1_W_MSK  (((1U << IR_CR_IRTX_LOGIC1_PH1_W_LEN) - 1) << IR_CR_IRTX_LOGIC1_PH1_W_POS)
#define IR_CR_IRTX_LOGIC1_PH1_W_UMSK (~(((1U << IR_CR_IRTX_LOGIC1_PH1_W_LEN) - 1) << IR_CR_IRTX_LOGIC1_PH1_W_POS))

/* 0x18 : irtx_pw_1 */
#define IRTX_PW_1_OFFSET           (0x18)
#define IR_CR_IRTX_HEAD_PH0_W      IR_CR_IRTX_HEAD_PH0_W
#define IR_CR_IRTX_HEAD_PH0_W_POS  (0U)
#define IR_CR_IRTX_HEAD_PH0_W_LEN  (8U)
#define IR_CR_IRTX_HEAD_PH0_W_MSK  (((1U << IR_CR_IRTX_HEAD_PH0_W_LEN) - 1) << IR_CR_IRTX_HEAD_PH0_W_POS)
#define IR_CR_IRTX_HEAD_PH0_W_UMSK (~(((1U << IR_CR_IRTX_HEAD_PH0_W_LEN) - 1) << IR_CR_IRTX_HEAD_PH0_W_POS))
#define IR_CR_IRTX_HEAD_PH1_W      IR_CR_IRTX_HEAD_PH1_W
#define IR_CR_IRTX_HEAD_PH1_W_POS  (8U)
#define IR_CR_IRTX_HEAD_PH1_W_LEN  (8U)
#define IR_CR_IRTX_HEAD_PH1_W_MSK  (((1U << IR_CR_IRTX_HEAD_PH1_W_LEN) - 1) << IR_CR_IRTX_HEAD_PH1_W_POS)
#define IR_CR_IRTX_HEAD_PH1_W_UMSK (~(((1U << IR_CR_IRTX_HEAD_PH1_W_LEN) - 1) << IR_CR_IRTX_HEAD_PH1_W_POS))
#define IR_CR_IRTX_TAIL_PH0_W      IR_CR_IRTX_TAIL_PH0_W
#define IR_CR_IRTX_TAIL_PH0_W_POS  (16U)
#define IR_CR_IRTX_TAIL_PH0_W_LEN  (8U)
#define IR_CR_IRTX_TAIL_PH0_W_MSK  (((1U << IR_CR_IRTX_TAIL_PH0_W_LEN) - 1) << IR_CR_IRTX_TAIL_PH0_W_POS)
#define IR_CR_IRTX_TAIL_PH0_W_UMSK (~(((1U << IR_CR_IRTX_TAIL_PH0_W_LEN) - 1) << IR_CR_IRTX_TAIL_PH0_W_POS))
#define IR_CR_IRTX_TAIL_PH1_W      IR_CR_IRTX_TAIL_PH1_W
#define IR_CR_IRTX_TAIL_PH1_W_POS  (24U)
#define IR_CR_IRTX_TAIL_PH1_W_LEN  (8U)
#define IR_CR_IRTX_TAIL_PH1_W_MSK  (((1U << IR_CR_IRTX_TAIL_PH1_W_LEN) - 1) << IR_CR_IRTX_TAIL_PH1_W_POS)
#define IR_CR_IRTX_TAIL_PH1_W_UMSK (~(((1U << IR_CR_IRTX_TAIL_PH1_W_LEN) - 1) << IR_CR_IRTX_TAIL_PH1_W_POS))

/* 0x40 : irrx_config */
#define IRRX_CONFIG_OFFSET      (0x40)
#define IR_CR_IRRX_EN           IR_CR_IRRX_EN
#define IR_CR_IRRX_EN_POS       (0U)
#define IR_CR_IRRX_EN_LEN       (1U)
#define IR_CR_IRRX_EN_MSK       (((1U << IR_CR_IRRX_EN_LEN) - 1) << IR_CR_IRRX_EN_POS)
#define IR_CR_IRRX_EN_UMSK      (~(((1U << IR_CR_IRRX_EN_LEN) - 1) << IR_CR_IRRX_EN_POS))
#define IR_CR_IRRX_IN_INV       IR_CR_IRRX_IN_INV
#define IR_CR_IRRX_IN_INV_POS   (1U)
#define IR_CR_IRRX_IN_INV_LEN   (1U)
#define IR_CR_IRRX_IN_INV_MSK   (((1U << IR_CR_IRRX_IN_INV_LEN) - 1) << IR_CR_IRRX_IN_INV_POS)
#define IR_CR_IRRX_IN_INV_UMSK  (~(((1U << IR_CR_IRRX_IN_INV_LEN) - 1) << IR_CR_IRRX_IN_INV_POS))
#define IR_CR_IRRX_MODE         IR_CR_IRRX_MODE
#define IR_CR_IRRX_MODE_POS     (2U)
#define IR_CR_IRRX_MODE_LEN     (2U)
#define IR_CR_IRRX_MODE_MSK     (((1U << IR_CR_IRRX_MODE_LEN) - 1) << IR_CR_IRRX_MODE_POS)
#define IR_CR_IRRX_MODE_UMSK    (~(((1U << IR_CR_IRRX_MODE_LEN) - 1) << IR_CR_IRRX_MODE_POS))
#define IR_CR_IRRX_DEG_EN       IR_CR_IRRX_DEG_EN
#define IR_CR_IRRX_DEG_EN_POS   (4U)
#define IR_CR_IRRX_DEG_EN_LEN   (1U)
#define IR_CR_IRRX_DEG_EN_MSK   (((1U << IR_CR_IRRX_DEG_EN_LEN) - 1) << IR_CR_IRRX_DEG_EN_POS)
#define IR_CR_IRRX_DEG_EN_UMSK  (~(((1U << IR_CR_IRRX_DEG_EN_LEN) - 1) << IR_CR_IRRX_DEG_EN_POS))
#define IR_CR_IRRX_DEG_CNT      IR_CR_IRRX_DEG_CNT
#define IR_CR_IRRX_DEG_CNT_POS  (8U)
#define IR_CR_IRRX_DEG_CNT_LEN  (4U)
#define IR_CR_IRRX_DEG_CNT_MSK  (((1U << IR_CR_IRRX_DEG_CNT_LEN) - 1) << IR_CR_IRRX_DEG_CNT_POS)
#define IR_CR_IRRX_DEG_CNT_UMSK (~(((1U << IR_CR_IRRX_DEG_CNT_LEN) - 1) << IR_CR_IRRX_DEG_CNT_POS))

/* 0x44 : irrx_int_sts */
#define IRRX_INT_STS_OFFSET       (0x44)
#define IRRX_END_INT              IRRX_END_INT
#define IRRX_END_INT_POS          (0U)
#define IRRX_END_INT_LEN          (1U)
#define IRRX_END_INT_MSK          (((1U << IRRX_END_INT_LEN) - 1) << IRRX_END_INT_POS)
#define IRRX_END_INT_UMSK         (~(((1U << IRRX_END_INT_LEN) - 1) << IRRX_END_INT_POS))
#define IRRX_FRDY_INT             IRRX_FRDY_INT
#define IRRX_FRDY_INT_POS         (1U)
#define IRRX_FRDY_INT_LEN         (1U)
#define IRRX_FRDY_INT_MSK         (((1U << IRRX_FRDY_INT_LEN) - 1) << IRRX_FRDY_INT_POS)
#define IRRX_FRDY_INT_UMSK        (~(((1U << IRRX_FRDY_INT_LEN) - 1) << IRRX_FRDY_INT_POS))
#define IRRX_FER_INT              IRRX_FER_INT
#define IRRX_FER_INT_POS          (2U)
#define IRRX_FER_INT_LEN          (1U)
#define IRRX_FER_INT_MSK          (((1U << IRRX_FER_INT_LEN) - 1) << IRRX_FER_INT_POS)
#define IRRX_FER_INT_UMSK         (~(((1U << IRRX_FER_INT_LEN) - 1) << IRRX_FER_INT_POS))
#define IR_CR_IRRX_END_MASK       IR_CR_IRRX_END_MASK
#define IR_CR_IRRX_END_MASK_POS   (8U)
#define IR_CR_IRRX_END_MASK_LEN   (1U)
#define IR_CR_IRRX_END_MASK_MSK   (((1U << IR_CR_IRRX_END_MASK_LEN) - 1) << IR_CR_IRRX_END_MASK_POS)
#define IR_CR_IRRX_END_MASK_UMSK  (~(((1U << IR_CR_IRRX_END_MASK_LEN) - 1) << IR_CR_IRRX_END_MASK_POS))
#define IR_CR_IRRX_FRDY_MASK      IR_CR_IRRX_FRDY_MASK
#define IR_CR_IRRX_FRDY_MASK_POS  (9U)
#define IR_CR_IRRX_FRDY_MASK_LEN  (1U)
#define IR_CR_IRRX_FRDY_MASK_MSK  (((1U << IR_CR_IRRX_FRDY_MASK_LEN) - 1) << IR_CR_IRRX_FRDY_MASK_POS)
#define IR_CR_IRRX_FRDY_MASK_UMSK (~(((1U << IR_CR_IRRX_FRDY_MASK_LEN) - 1) << IR_CR_IRRX_FRDY_MASK_POS))
#define IR_CR_IRRX_FER_MASK       IR_CR_IRRX_FER_MASK
#define IR_CR_IRRX_FER_MASK_POS   (10U)
#define IR_CR_IRRX_FER_MASK_LEN   (1U)
#define IR_CR_IRRX_FER_MASK_MSK   (((1U << IR_CR_IRRX_FER_MASK_LEN) - 1) << IR_CR_IRRX_FER_MASK_POS)
#define IR_CR_IRRX_FER_MASK_UMSK  (~(((1U << IR_CR_IRRX_FER_MASK_LEN) - 1) << IR_CR_IRRX_FER_MASK_POS))
#define IR_CR_IRRX_END_CLR        IR_CR_IRRX_END_CLR
#define IR_CR_IRRX_END_CLR_POS    (16U)
#define IR_CR_IRRX_END_CLR_LEN    (1U)
#define IR_CR_IRRX_END_CLR_MSK    (((1U << IR_CR_IRRX_END_CLR_LEN) - 1) << IR_CR_IRRX_END_CLR_POS)
#define IR_CR_IRRX_END_CLR_UMSK   (~(((1U << IR_CR_IRRX_END_CLR_LEN) - 1) << IR_CR_IRRX_END_CLR_POS))
#define IR_CR_IRRX_END_EN         IR_CR_IRRX_END_EN
#define IR_CR_IRRX_END_EN_POS     (24U)
#define IR_CR_IRRX_END_EN_LEN     (1U)
#define IR_CR_IRRX_END_EN_MSK     (((1U << IR_CR_IRRX_END_EN_LEN) - 1) << IR_CR_IRRX_END_EN_POS)
#define IR_CR_IRRX_END_EN_UMSK    (~(((1U << IR_CR_IRRX_END_EN_LEN) - 1) << IR_CR_IRRX_END_EN_POS))
#define IR_CR_IRRX_FRDY_EN        IR_CR_IRRX_FRDY_EN
#define IR_CR_IRRX_FRDY_EN_POS    (25U)
#define IR_CR_IRRX_FRDY_EN_LEN    (1U)
#define IR_CR_IRRX_FRDY_EN_MSK    (((1U << IR_CR_IRRX_FRDY_EN_LEN) - 1) << IR_CR_IRRX_FRDY_EN_POS)
#define IR_CR_IRRX_FRDY_EN_UMSK   (~(((1U << IR_CR_IRRX_FRDY_EN_LEN) - 1) << IR_CR_IRRX_FRDY_EN_POS))
#define IR_CR_IRRX_FER_EN         IR_CR_IRRX_FER_EN
#define IR_CR_IRRX_FER_EN_POS     (26U)
#define IR_CR_IRRX_FER_EN_LEN     (1U)
#define IR_CR_IRRX_FER_EN_MSK     (((1U << IR_CR_IRRX_FER_EN_LEN) - 1) << IR_CR_IRRX_FER_EN_POS)
#define IR_CR_IRRX_FER_EN_UMSK    (~(((1U << IR_CR_IRRX_FER_EN_LEN) - 1) << IR_CR_IRRX_FER_EN_POS))

/* 0x48 : irrx_pw_config */
#define IRRX_PW_CONFIG_OFFSET   (0x48)
#define IR_CR_IRRX_DATA_TH      IR_CR_IRRX_DATA_TH
#define IR_CR_IRRX_DATA_TH_POS  (0U)
#define IR_CR_IRRX_DATA_TH_LEN  (16U)
#define IR_CR_IRRX_DATA_TH_MSK  (((1U << IR_CR_IRRX_DATA_TH_LEN) - 1) << IR_CR_IRRX_DATA_TH_POS)
#define IR_CR_IRRX_DATA_TH_UMSK (~(((1U << IR_CR_IRRX_DATA_TH_LEN) - 1) << IR_CR_IRRX_DATA_TH_POS))
#define IR_CR_IRRX_END_TH       IR_CR_IRRX_END_TH
#define IR_CR_IRRX_END_TH_POS   (16U)
#define IR_CR_IRRX_END_TH_LEN   (16U)
#define IR_CR_IRRX_END_TH_MSK   (((1U << IR_CR_IRRX_END_TH_LEN) - 1) << IR_CR_IRRX_END_TH_POS)
#define IR_CR_IRRX_END_TH_UMSK  (~(((1U << IR_CR_IRRX_END_TH_LEN) - 1) << IR_CR_IRRX_END_TH_POS))

/* 0x50 : irrx_data_count */
#define IRRX_DATA_COUNT_OFFSET    (0x50)
#define IR_STS_IRRX_DATA_CNT      IR_STS_IRRX_DATA_CNT
#define IR_STS_IRRX_DATA_CNT_POS  (0U)
#define IR_STS_IRRX_DATA_CNT_LEN  (7U)
#define IR_STS_IRRX_DATA_CNT_MSK  (((1U << IR_STS_IRRX_DATA_CNT_LEN) - 1) << IR_STS_IRRX_DATA_CNT_POS)
#define IR_STS_IRRX_DATA_CNT_UMSK (~(((1U << IR_STS_IRRX_DATA_CNT_LEN) - 1) << IR_STS_IRRX_DATA_CNT_POS))

/* 0x54 : irrx_data_word0 */
#define IRRX_DATA_WORD0_OFFSET      (0x54)
#define IR_STS_IRRX_DATA_WORD0      IR_STS_IRRX_DATA_WORD0
#define IR_STS_IRRX_DATA_WORD0_POS  (0U)
#define IR_STS_IRRX_DATA_WORD0_LEN  (32U)
#define IR_STS_IRRX_DATA_WORD0_MSK  (((1U << IR_STS_IRRX_DATA_WORD0_LEN) - 1) << IR_STS_IRRX_DATA_WORD0_POS)
#define IR_STS_IRRX_DATA_WORD0_UMSK (~(((1U << IR_STS_IRRX_DATA_WORD0_LEN) - 1) << IR_STS_IRRX_DATA_WORD0_POS))

/* 0x58 : irrx_data_word1 */
#define IRRX_DATA_WORD1_OFFSET      (0x58)
#define IR_STS_IRRX_DATA_WORD1      IR_STS_IRRX_DATA_WORD1
#define IR_STS_IRRX_DATA_WORD1_POS  (0U)
#define IR_STS_IRRX_DATA_WORD1_LEN  (32U)
#define IR_STS_IRRX_DATA_WORD1_MSK  (((1U << IR_STS_IRRX_DATA_WORD1_LEN) - 1) << IR_STS_IRRX_DATA_WORD1_POS)
#define IR_STS_IRRX_DATA_WORD1_UMSK (~(((1U << IR_STS_IRRX_DATA_WORD1_LEN) - 1) << IR_STS_IRRX_DATA_WORD1_POS))

/* 0x80 : irtx_fifo_config_0 */
#define IRTX_FIFO_CONFIG_0_OFFSET (0x80)
#define IRTX_DMA_EN               IRTX_DMA_EN
#define IRTX_DMA_EN_POS           (0U)
#define IRTX_DMA_EN_LEN           (1U)
#define IRTX_DMA_EN_MSK           (((1U << IRTX_DMA_EN_LEN) - 1) << IRTX_DMA_EN_POS)
#define IRTX_DMA_EN_UMSK          (~(((1U << IRTX_DMA_EN_LEN) - 1) << IRTX_DMA_EN_POS))
#define IR_TX_FIFO_CLR            IR_TX_FIFO_CLR
#define IR_TX_FIFO_CLR_POS        (2U)
#define IR_TX_FIFO_CLR_LEN        (1U)
#define IR_TX_FIFO_CLR_MSK        (((1U << IR_TX_FIFO_CLR_LEN) - 1) << IR_TX_FIFO_CLR_POS)
#define IR_TX_FIFO_CLR_UMSK       (~(((1U << IR_TX_FIFO_CLR_LEN) - 1) << IR_TX_FIFO_CLR_POS))
#define IR_RX_FIFO_CLR            IR_RX_FIFO_CLR
#define IR_RX_FIFO_CLR_POS        (3U)
#define IR_RX_FIFO_CLR_LEN        (1U)
#define IR_RX_FIFO_CLR_MSK        (((1U << IR_RX_FIFO_CLR_LEN) - 1) << IR_RX_FIFO_CLR_POS)
#define IR_RX_FIFO_CLR_UMSK       (~(((1U << IR_RX_FIFO_CLR_LEN) - 1) << IR_RX_FIFO_CLR_POS))
#define IR_TX_FIFO_OVERFLOW       IR_TX_FIFO_OVERFLOW
#define IR_TX_FIFO_OVERFLOW_POS   (4U)
#define IR_TX_FIFO_OVERFLOW_LEN   (1U)
#define IR_TX_FIFO_OVERFLOW_MSK   (((1U << IR_TX_FIFO_OVERFLOW_LEN) - 1) << IR_TX_FIFO_OVERFLOW_POS)
#define IR_TX_FIFO_OVERFLOW_UMSK  (~(((1U << IR_TX_FIFO_OVERFLOW_LEN) - 1) << IR_TX_FIFO_OVERFLOW_POS))
#define IR_TX_FIFO_UNDERFLOW      IR_TX_FIFO_UNDERFLOW
#define IR_TX_FIFO_UNDERFLOW_POS  (5U)
#define IR_TX_FIFO_UNDERFLOW_LEN  (1U)
#define IR_TX_FIFO_UNDERFLOW_MSK  (((1U << IR_TX_FIFO_UNDERFLOW_LEN) - 1) << IR_TX_FIFO_UNDERFLOW_POS)
#define IR_TX_FIFO_UNDERFLOW_UMSK (~(((1U << IR_TX_FIFO_UNDERFLOW_LEN) - 1) << IR_TX_FIFO_UNDERFLOW_POS))
#define IR_RX_FIFO_OVERFLOW       IR_RX_FIFO_OVERFLOW
#define IR_RX_FIFO_OVERFLOW_POS   (6U)
#define IR_RX_FIFO_OVERFLOW_LEN   (1U)
#define IR_RX_FIFO_OVERFLOW_MSK   (((1U << IR_RX_FIFO_OVERFLOW_LEN) - 1) << IR_RX_FIFO_OVERFLOW_POS)
#define IR_RX_FIFO_OVERFLOW_UMSK  (~(((1U << IR_RX_FIFO_OVERFLOW_LEN) - 1) << IR_RX_FIFO_OVERFLOW_POS))
#define IR_RX_FIFO_UNDERFLOW      IR_RX_FIFO_UNDERFLOW
#define IR_RX_FIFO_UNDERFLOW_POS  (7U)
#define IR_RX_FIFO_UNDERFLOW_LEN  (1U)
#define IR_RX_FIFO_UNDERFLOW_MSK  (((1U << IR_RX_FIFO_UNDERFLOW_LEN) - 1) << IR_RX_FIFO_UNDERFLOW_POS)
#define IR_RX_FIFO_UNDERFLOW_UMSK (~(((1U << IR_RX_FIFO_UNDERFLOW_LEN) - 1) << IR_RX_FIFO_UNDERFLOW_POS))

/* 0x84 : irtx_fifo_config_1 */
#define IRTX_FIFO_CONFIG_1_OFFSET (0x84)
#define IR_TX_FIFO_CNT            IR_TX_FIFO_CNT
#define IR_TX_FIFO_CNT_POS        (0U)
#define IR_TX_FIFO_CNT_LEN        (3U)
#define IR_TX_FIFO_CNT_MSK        (((1U << IR_TX_FIFO_CNT_LEN) - 1) << IR_TX_FIFO_CNT_POS)
#define IR_TX_FIFO_CNT_UMSK       (~(((1U << IR_TX_FIFO_CNT_LEN) - 1) << IR_TX_FIFO_CNT_POS))
#define IR_RX_FIFO_CNT            IR_RX_FIFO_CNT
#define IR_RX_FIFO_CNT_POS        (8U)
#define IR_RX_FIFO_CNT_LEN        (7U)
#define IR_RX_FIFO_CNT_MSK        (((1U << IR_RX_FIFO_CNT_LEN) - 1) << IR_RX_FIFO_CNT_POS)
#define IR_RX_FIFO_CNT_UMSK       (~(((1U << IR_RX_FIFO_CNT_LEN) - 1) << IR_RX_FIFO_CNT_POS))
#define IR_TX_FIFO_TH             IR_TX_FIFO_TH
#define IR_TX_FIFO_TH_POS         (16U)
#define IR_TX_FIFO_TH_LEN         (2U)
#define IR_TX_FIFO_TH_MSK         (((1U << IR_TX_FIFO_TH_LEN) - 1) << IR_TX_FIFO_TH_POS)
#define IR_TX_FIFO_TH_UMSK        (~(((1U << IR_TX_FIFO_TH_LEN) - 1) << IR_TX_FIFO_TH_POS))
#define IR_RX_FIFO_TH             IR_RX_FIFO_TH
#define IR_RX_FIFO_TH_POS         (24U)
#define IR_RX_FIFO_TH_LEN         (6U)
#define IR_RX_FIFO_TH_MSK         (((1U << IR_RX_FIFO_TH_LEN) - 1) << IR_RX_FIFO_TH_POS)
#define IR_RX_FIFO_TH_UMSK        (~(((1U << IR_RX_FIFO_TH_LEN) - 1) << IR_RX_FIFO_TH_POS))

/* 0x88 : ir_fifo_wdata */
#define IR_FIFO_WDATA_OFFSET  (0x88)
#define IR_TX_FIFO_WDATA      IR_TX_FIFO_WDATA
#define IR_TX_FIFO_WDATA_POS  (0U)
#define IR_TX_FIFO_WDATA_LEN  (32U)
#define IR_TX_FIFO_WDATA_MSK  (((1U << IR_TX_FIFO_WDATA_LEN) - 1) << IR_TX_FIFO_WDATA_POS)
#define IR_TX_FIFO_WDATA_UMSK (~(((1U << IR_TX_FIFO_WDATA_LEN) - 1) << IR_TX_FIFO_WDATA_POS))

/* 0x8C : ir_fifo_rdata */
#define IR_FIFO_RDATA_OFFSET  (0x8C)
#define IR_RX_FIFO_RDATA      IR_RX_FIFO_RDATA
#define IR_RX_FIFO_RDATA_POS  (0U)
#define IR_RX_FIFO_RDATA_LEN  (16U)
#define IR_RX_FIFO_RDATA_MSK  (((1U << IR_RX_FIFO_RDATA_LEN) - 1) << IR_RX_FIFO_RDATA_POS)
#define IR_RX_FIFO_RDATA_UMSK (~(((1U << IR_RX_FIFO_RDATA_LEN) - 1) << IR_RX_FIFO_RDATA_POS))

struct ir_reg {
    /* 0x0 : irtx_config */
    union {
        struct {
            uint32_t cr_irtx_en             : 1; /* [    0],        r/w,        0x0 */
            uint32_t cr_irtx_out_inv        : 1; /* [    1],        r/w,        0x0 */
            uint32_t cr_irtx_mod_en         : 1; /* [    2],        r/w,        0x0 */
            uint32_t cr_irtx_swm_en         : 1; /* [    3],        r/w,        0x0 */
            uint32_t cr_irtx_data_en        : 1; /* [    4],        r/w,        0x1 */
            uint32_t cr_irtx_logic0_hl_inv  : 1; /* [    5],        r/w,        0x0 */
            uint32_t cr_irtx_logic1_hl_inv  : 1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7             : 1; /* [    7],       rsvd,        0x0 */
            uint32_t cr_irtx_head_en        : 1; /* [    8],        r/w,        0x1 */
            uint32_t cr_irtx_head_hl_inv    : 1; /* [    9],        r/w,        0x0 */
            uint32_t cr_irtx_tail_en        : 1; /* [   10],        r/w,        0x1 */
            uint32_t cr_irtx_tail_hl_inv    : 1; /* [   11],        r/w,        0x0 */
            uint32_t cr_irtx_frm_en         : 1; /* [   12],        r/w,        0x0 */
            uint32_t cr_irtx_frm_cont_en    : 1; /* [   13],        r/w,        0x0 */
            uint32_t cr_irtx_frm_frame_size : 2; /* [15:14],        r/w,        0x0 */
            uint32_t cr_irtx_data_num       : 7; /* [22:16],        r/w,       0x1f */
            uint32_t reserved_23_31         : 9; /* [31:23],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irtx_config;

    /* 0x4 : irtx_int_sts */
    union {
        struct {
            uint32_t irtx_end_int      : 1; /* [    0],          r,        0x0 */
            uint32_t irtx_frdy_int     : 1; /* [    1],          r,        0x1 */
            uint32_t irtx_fer_int      : 1; /* [    2],          r,        0x0 */
            uint32_t reserved_3_7      : 5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t cr_irtx_end_mask  : 1; /* [    8],        r/w,        0x1 */
            uint32_t cr_irtx_frdy_mask : 1; /* [    9],        r/w,        0x1 */
            uint32_t cr_irtx_fer_mask  : 1; /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_15    : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t cr_irtx_end_clr   : 1; /* [   16],        w1c,        0x0 */
            uint32_t rsvd_17           : 1; /* [   17],       rsvd,        0x0 */
            uint32_t rsvd_18           : 1; /* [   18],       rsvd,        0x0 */
            uint32_t reserved_19_23    : 5; /* [23:19],       rsvd,        0x0 */
            uint32_t cr_irtx_end_en    : 1; /* [   24],        r/w,        0x1 */
            uint32_t cr_irtx_frdy_en   : 1; /* [   25],        r/w,        0x1 */
            uint32_t cr_irtx_fer_en    : 1; /* [   26],        r/w,        0x1 */
            uint32_t reserved_27_31    : 5; /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irtx_int_sts;

    /* 0x8  reserved */
    uint8_t RESERVED0x8[8];

    /* 0x10 : irtx_pulse_width */
    union {
        struct {
            uint32_t cr_irtx_pw_unit   : 12; /* [11: 0],        r/w,      0x464 */
            uint32_t reserved_12_15    : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t cr_irtx_mod_ph0_w : 8;  /* [23:16],        r/w,       0x11 */
            uint32_t cr_irtx_mod_ph1_w : 8;  /* [31:24],        r/w,       0x22 */
        } BF;
        uint32_t WORD;
    } irtx_pulse_width;

    /* 0x14 : irtx_pw_0 */
    union {
        struct {
            uint32_t cr_irtx_logic0_ph0_w : 8; /* [ 7: 0],        r/w,        0x0 */
            uint32_t cr_irtx_logic0_ph1_w : 8; /* [15: 8],        r/w,        0x0 */
            uint32_t cr_irtx_logic1_ph0_w : 8; /* [23:16],        r/w,        0x0 */
            uint32_t cr_irtx_logic1_ph1_w : 8; /* [31:24],        r/w,        0x2 */
        } BF;
        uint32_t WORD;
    } irtx_pw_0;

    /* 0x18 : irtx_pw_1 */
    union {
        struct {
            uint32_t cr_irtx_head_ph0_w : 8; /* [ 7: 0],        r/w,        0xf */
            uint32_t cr_irtx_head_ph1_w : 8; /* [15: 8],        r/w,        0x7 */
            uint32_t cr_irtx_tail_ph0_w : 8; /* [23:16],        r/w,        0x0 */
            uint32_t cr_irtx_tail_ph1_w : 8; /* [31:24],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } irtx_pw_1;

    /* 0x1c  reserved */
    uint8_t RESERVED0x1c[36];

    /* 0x40 : irrx_config */
    union {
        struct {
            uint32_t cr_irrx_en      : 1;  /* [    0],        r/w,        0x0 */
            uint32_t cr_irrx_in_inv  : 1;  /* [    1],        r/w,        0x1 */
            uint32_t cr_irrx_mode    : 2;  /* [ 3: 2],        r/w,        0x0 */
            uint32_t cr_irrx_deg_en  : 1;  /* [    4],        r/w,        0x0 */
            uint32_t reserved_5_7    : 3;  /* [ 7: 5],       rsvd,        0x0 */
            uint32_t cr_irrx_deg_cnt : 4;  /* [11: 8],        r/w,        0x0 */
            uint32_t reserved_12_31  : 20; /* [31:12],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irrx_config;

    /* 0x44 : irrx_int_sts */
    union {
        struct {
            uint32_t irrx_end_int      : 1; /* [    0],          r,        0x0 */
            uint32_t irrx_frdy_int     : 1; /* [    1],          r,        0x0 */
            uint32_t irrx_fer_int      : 1; /* [    2],          r,        0x0 */
            uint32_t reserved_3_7      : 5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t cr_irrx_end_mask  : 1; /* [    8],        r/w,        0x1 */
            uint32_t cr_irrx_frdy_mask : 1; /* [    9],        r/w,        0x1 */
            uint32_t cr_irrx_fer_mask  : 1; /* [   10],        r/w,        0x1 */
            uint32_t reserved_11_15    : 5; /* [15:11],       rsvd,        0x0 */
            uint32_t cr_irrx_end_clr   : 1; /* [   16],        w1c,        0x0 */
            uint32_t rsvd_17           : 1; /* [   17],       rsvd,        0x0 */
            uint32_t rsvd_18           : 1; /* [   18],       rsvd,        0x0 */
            uint32_t reserved_19_23    : 5; /* [23:19],       rsvd,        0x0 */
            uint32_t cr_irrx_end_en    : 1; /* [   24],        r/w,        0x1 */
            uint32_t cr_irrx_frdy_en   : 1; /* [   25],        r/w,        0x1 */
            uint32_t cr_irrx_fer_en    : 1; /* [   26],        r/w,        0x1 */
            uint32_t reserved_27_31    : 5; /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irrx_int_sts;

    /* 0x48 : irrx_pw_config */
    union {
        struct {
            uint32_t cr_irrx_data_th : 16; /* [15: 0],        r/w,      0xd47 */
            uint32_t cr_irrx_end_th  : 16; /* [31:16],        r/w,     0x2327 */
        } BF;
        uint32_t WORD;
    } irrx_pw_config;

    /* 0x4c  reserved */
    uint8_t RESERVED0x4c[4];

    /* 0x50 : irrx_data_count */
    union {
        struct {
            uint32_t sts_irrx_data_cnt : 7;  /* [ 6: 0],          r,        0x0 */
            uint32_t reserved_7_31     : 25; /* [31: 7],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irrx_data_count;

    /* 0x54 : irrx_data_word0 */
    union {
        struct {
            uint32_t sts_irrx_data_word0 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } irrx_data_word0;

    /* 0x58 : irrx_data_word1 */
    union {
        struct {
            uint32_t sts_irrx_data_word1 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } irrx_data_word1;

    /* 0x5c  reserved */
    uint8_t RESERVED0x5c[36];

    /* 0x80 : irtx_fifo_config_0 */
    union {
        struct {
            uint32_t irtx_dma_en       : 1;  /* [    0],        r/w,        0x0 */
            uint32_t rsvd_1            : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t tx_fifo_clr       : 1;  /* [    2],        w1c,        0x0 */
            uint32_t rx_fifo_clr       : 1;  /* [    3],        w1c,        0x0 */
            uint32_t tx_fifo_overflow  : 1;  /* [    4],          r,        0x0 */
            uint32_t tx_fifo_underflow : 1;  /* [    5],          r,        0x0 */
            uint32_t rx_fifo_overflow  : 1;  /* [    6],          r,        0x0 */
            uint32_t rx_fifo_underflow : 1;  /* [    7],          r,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irtx_fifo_config_0;

    /* 0x84 : irtx_fifo_config_1 */
    union {
        struct {
            uint32_t tx_fifo_cnt    : 3; /* [ 2: 0],          r,        0x4 */
            uint32_t reserved_3_7   : 5; /* [ 7: 3],       rsvd,        0x0 */
            uint32_t rx_fifo_cnt    : 7; /* [14: 8],          r,        0x0 */
            uint32_t reserved_15    : 1; /* [   15],       rsvd,        0x0 */
            uint32_t tx_fifo_th     : 2; /* [17:16],        r/w,        0x0 */
            uint32_t reserved_18_23 : 6; /* [23:18],       rsvd,        0x0 */
            uint32_t rx_fifo_th     : 6; /* [29:24],        r/w,        0x0 */
            uint32_t reserved_30_31 : 2; /* [31:30],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } irtx_fifo_config_1;

    /* 0x88 : ir_fifo_wdata */
    union {
        struct {
            uint32_t tx_fifo_wdata : 32; /* [31: 0],          w,        0x0 */
        } BF;
        uint32_t WORD;
    } ir_fifo_wdata;

    /* 0x8C : ir_fifo_rdata */
    union {
        struct {
            uint32_t rx_fifo_rdata  : 16; /* [15: 0],          r,        0x0 */
            uint32_t reserved_16_31 : 16; /* [31:16],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } ir_fifo_rdata;
};

typedef volatile struct ir_reg ir_reg_t;

#endif /* __IR_REG_H__ */
