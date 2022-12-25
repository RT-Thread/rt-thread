/**
  ******************************************************************************
  * @file    dsp2_blawb_reg.h
  * @version V1.2
  * @date    2019-04-25
  * @brief   This file is the description of.IP register
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 Bouffalo Lab</center></h2>
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
#ifndef __DSP2_BLAWB_REG_H__
#define __DSP2_BLAWB_REG_H__

#include "bl808.h"

/* 0x600 : blawb_read_grid_addr */
#define DSP2_BLAWB_BLAWB_READ_GRID_ADDR_OFFSET (0x600)
#define DSP2_BLAWB_BLAWB_READ_GRID_ADDR        DSP2_BLAWB_BLAWB_READ_GRID_ADDR
#define DSP2_BLAWB_BLAWB_READ_GRID_ADDR_POS    (0U)
#define DSP2_BLAWB_BLAWB_READ_GRID_ADDR_LEN    (12U)
#define DSP2_BLAWB_BLAWB_READ_GRID_ADDR_MSK    (((1U << DSP2_BLAWB_BLAWB_READ_GRID_ADDR_LEN) - 1) << DSP2_BLAWB_BLAWB_READ_GRID_ADDR_POS)
#define DSP2_BLAWB_BLAWB_READ_GRID_ADDR_UMSK   (~(((1U << DSP2_BLAWB_BLAWB_READ_GRID_ADDR_LEN) - 1) << DSP2_BLAWB_BLAWB_READ_GRID_ADDR_POS))
#define DSP2_BLAWB_BLAWB_BUF_IDX               DSP2_BLAWB_BLAWB_BUF_IDX
#define DSP2_BLAWB_BLAWB_BUF_IDX_POS           (16U)
#define DSP2_BLAWB_BLAWB_BUF_IDX_LEN           (1U)
#define DSP2_BLAWB_BLAWB_BUF_IDX_MSK           (((1U << DSP2_BLAWB_BLAWB_BUF_IDX_LEN) - 1) << DSP2_BLAWB_BLAWB_BUF_IDX_POS)
#define DSP2_BLAWB_BLAWB_BUF_IDX_UMSK          (~(((1U << DSP2_BLAWB_BLAWB_BUF_IDX_LEN) - 1) << DSP2_BLAWB_BLAWB_BUF_IDX_POS))
#define DSP2_BLAWB_BLAWB_W_CNT                 DSP2_BLAWB_BLAWB_W_CNT
#define DSP2_BLAWB_BLAWB_W_CNT_POS             (20U)
#define DSP2_BLAWB_BLAWB_W_CNT_LEN             (5U)
#define DSP2_BLAWB_BLAWB_W_CNT_MSK             (((1U << DSP2_BLAWB_BLAWB_W_CNT_LEN) - 1) << DSP2_BLAWB_BLAWB_W_CNT_POS)
#define DSP2_BLAWB_BLAWB_W_CNT_UMSK            (~(((1U << DSP2_BLAWB_BLAWB_W_CNT_LEN) - 1) << DSP2_BLAWB_BLAWB_W_CNT_POS))

/* 0x604 : blawb_grid_data */
#define DSP2_BLAWB_BLAWB_GRID_DATA_OFFSET (0x604)
#define DSP2_BLAWB_BLAWB_GRID_DATA        DSP2_BLAWB_BLAWB_GRID_DATA
#define DSP2_BLAWB_BLAWB_GRID_DATA_POS    (0U)
#define DSP2_BLAWB_BLAWB_GRID_DATA_LEN    (32U)
#define DSP2_BLAWB_BLAWB_GRID_DATA_MSK    (((1U << DSP2_BLAWB_BLAWB_GRID_DATA_LEN) - 1) << DSP2_BLAWB_BLAWB_GRID_DATA_POS)
#define DSP2_BLAWB_BLAWB_GRID_DATA_UMSK   (~(((1U << DSP2_BLAWB_BLAWB_GRID_DATA_LEN) - 1) << DSP2_BLAWB_BLAWB_GRID_DATA_POS))

struct dsp2_blawb_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[1536];

    /* 0x600 : blawb_read_grid_addr */
    union {
        struct {
            uint32_t blawb_read_grid_addr : 12; /* [11: 0],        r/w,        0x0 */
            uint32_t reserved_12_15       : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t blawb_buf_idx        : 1;  /* [   16],          r,        0x0 */
            uint32_t reserved_17_19       : 3;  /* [19:17],       rsvd,        0x0 */
            uint32_t blawb_w_cnt          : 5;  /* [24:20],          r,        0x0 */
            uint32_t reserved_25_31       : 7;  /* [31:25],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } blawb_read_grid_addr;

    /* 0x604 : blawb_grid_data */
    union {
        struct {
            uint32_t blawb_grid_data : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } blawb_grid_data;
};

typedef volatile struct dsp2_blawb_reg dsp2_blawb_reg_t;

#endif /* __DSP2_BLAWB_REG_H__ */
