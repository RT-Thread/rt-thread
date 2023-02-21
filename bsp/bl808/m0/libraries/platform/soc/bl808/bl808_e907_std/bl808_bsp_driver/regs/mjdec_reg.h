/**
  ******************************************************************************
  * @file    mjdec_reg.h
  * @version V1.0
  * @date    2021-07-02
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
#ifndef __MJDEC_REG_H__
#define __MJDEC_REG_H__

#include "bl808.h"

/* 0x0 : jdec_control_1 */
#define MJDEC_JDEC_CONTROL_1_OFFSET     (0x0)
#define MJDEC_REG_MJ_DEC_ENABLE         MJDEC_REG_MJ_DEC_ENABLE
#define MJDEC_REG_MJ_DEC_ENABLE_POS     (0U)
#define MJDEC_REG_MJ_DEC_ENABLE_LEN     (1U)
#define MJDEC_REG_MJ_DEC_ENABLE_MSK     (((1U << MJDEC_REG_MJ_DEC_ENABLE_LEN) - 1) << MJDEC_REG_MJ_DEC_ENABLE_POS)
#define MJDEC_REG_MJ_DEC_ENABLE_UMSK    (~(((1U << MJDEC_REG_MJ_DEC_ENABLE_LEN) - 1) << MJDEC_REG_MJ_DEC_ENABLE_POS))
#define MJDEC_REG_SWAP_MODE             MJDEC_REG_SWAP_MODE
#define MJDEC_REG_SWAP_MODE_POS         (1U)
#define MJDEC_REG_SWAP_MODE_LEN         (1U)
#define MJDEC_REG_SWAP_MODE_MSK         (((1U << MJDEC_REG_SWAP_MODE_LEN) - 1) << MJDEC_REG_SWAP_MODE_POS)
#define MJDEC_REG_SWAP_MODE_UMSK        (~(((1U << MJDEC_REG_SWAP_MODE_LEN) - 1) << MJDEC_REG_SWAP_MODE_POS))
#define MJDEC_REG_U_EVEN                MJDEC_REG_U_EVEN
#define MJDEC_REG_U_EVEN_POS            (2U)
#define MJDEC_REG_U_EVEN_LEN            (1U)
#define MJDEC_REG_U_EVEN_MSK            (((1U << MJDEC_REG_U_EVEN_LEN) - 1) << MJDEC_REG_U_EVEN_POS)
#define MJDEC_REG_U_EVEN_UMSK           (~(((1U << MJDEC_REG_U_EVEN_LEN) - 1) << MJDEC_REG_U_EVEN_POS))
#define MJDEC_REG_YUV_MODE              MJDEC_REG_YUV_MODE
#define MJDEC_REG_YUV_MODE_POS          (3U)
#define MJDEC_REG_YUV_MODE_LEN          (2U)
#define MJDEC_REG_YUV_MODE_MSK          (((1U << MJDEC_REG_YUV_MODE_LEN) - 1) << MJDEC_REG_YUV_MODE_POS)
#define MJDEC_REG_YUV_MODE_UMSK         (~(((1U << MJDEC_REG_YUV_MODE_LEN) - 1) << MJDEC_REG_YUV_MODE_POS))
#define MJDEC_REG_LAST_HF_WBLK_DMY      MJDEC_REG_LAST_HF_WBLK_DMY
#define MJDEC_REG_LAST_HF_WBLK_DMY_POS  (5U)
#define MJDEC_REG_LAST_HF_WBLK_DMY_LEN  (1U)
#define MJDEC_REG_LAST_HF_WBLK_DMY_MSK  (((1U << MJDEC_REG_LAST_HF_WBLK_DMY_LEN) - 1) << MJDEC_REG_LAST_HF_WBLK_DMY_POS)
#define MJDEC_REG_LAST_HF_WBLK_DMY_UMSK (~(((1U << MJDEC_REG_LAST_HF_WBLK_DMY_LEN) - 1) << MJDEC_REG_LAST_HF_WBLK_DMY_POS))
#define MJDEC_REG_LAST_HF_HBLK_DMY      MJDEC_REG_LAST_HF_HBLK_DMY
#define MJDEC_REG_LAST_HF_HBLK_DMY_POS  (6U)
#define MJDEC_REG_LAST_HF_HBLK_DMY_LEN  (1U)
#define MJDEC_REG_LAST_HF_HBLK_DMY_MSK  (((1U << MJDEC_REG_LAST_HF_HBLK_DMY_LEN) - 1) << MJDEC_REG_LAST_HF_HBLK_DMY_POS)
#define MJDEC_REG_LAST_HF_HBLK_DMY_UMSK (~(((1U << MJDEC_REG_LAST_HF_HBLK_DMY_LEN) - 1) << MJDEC_REG_LAST_HF_HBLK_DMY_POS))
#define MJDEC_REG_W_XLEN                MJDEC_REG_W_XLEN
#define MJDEC_REG_W_XLEN_POS            (8U)
#define MJDEC_REG_W_XLEN_LEN            (3U)
#define MJDEC_REG_W_XLEN_MSK            (((1U << MJDEC_REG_W_XLEN_LEN) - 1) << MJDEC_REG_W_XLEN_POS)
#define MJDEC_REG_W_XLEN_UMSK           (~(((1U << MJDEC_REG_W_XLEN_LEN) - 1) << MJDEC_REG_W_XLEN_POS))
#define MJDEC_REG_LAST_HF_BLK_DMY       MJDEC_REG_LAST_HF_BLK_DMY
#define MJDEC_REG_LAST_HF_BLK_DMY_POS   (11U)
#define MJDEC_REG_LAST_HF_BLK_DMY_LEN   (1U)
#define MJDEC_REG_LAST_HF_BLK_DMY_MSK   (((1U << MJDEC_REG_LAST_HF_BLK_DMY_LEN) - 1) << MJDEC_REG_LAST_HF_BLK_DMY_POS)
#define MJDEC_REG_LAST_HF_BLK_DMY_UMSK  (~(((1U << MJDEC_REG_LAST_HF_BLK_DMY_LEN) - 1) << MJDEC_REG_LAST_HF_BLK_DMY_POS))
#define MJDEC_REG_R_XLEN                MJDEC_REG_R_XLEN
#define MJDEC_REG_R_XLEN_POS            (12U)
#define MJDEC_REG_R_XLEN_LEN            (3U)
#define MJDEC_REG_R_XLEN_MSK            (((1U << MJDEC_REG_R_XLEN_LEN) - 1) << MJDEC_REG_R_XLEN_POS)
#define MJDEC_REG_R_XLEN_UMSK           (~(((1U << MJDEC_REG_R_XLEN_LEN) - 1) << MJDEC_REG_R_XLEN_POS))
#define MJDEC_REG_Q_MODE                MJDEC_REG_Q_MODE
#define MJDEC_REG_Q_MODE_POS            (16U)
#define MJDEC_REG_Q_MODE_LEN            (7U)
#define MJDEC_REG_Q_MODE_MSK            (((1U << MJDEC_REG_Q_MODE_LEN) - 1) << MJDEC_REG_Q_MODE_POS)
#define MJDEC_REG_Q_MODE_UMSK           (~(((1U << MJDEC_REG_Q_MODE_LEN) - 1) << MJDEC_REG_Q_MODE_POS))

/* 0x08 : jdec_yy_frame_addr */
#define MJDEC_JDEC_YY_FRAME_ADDR_OFFSET (0x08)
#define MJDEC_REG_YY_ADDR_START         MJDEC_REG_YY_ADDR_START
#define MJDEC_REG_YY_ADDR_START_POS     (0U)
#define MJDEC_REG_YY_ADDR_START_LEN     (32U)
#define MJDEC_REG_YY_ADDR_START_MSK     (((1U << MJDEC_REG_YY_ADDR_START_LEN) - 1) << MJDEC_REG_YY_ADDR_START_POS)
#define MJDEC_REG_YY_ADDR_START_UMSK    (~(((1U << MJDEC_REG_YY_ADDR_START_LEN) - 1) << MJDEC_REG_YY_ADDR_START_POS))

/* 0x0C : jdec_uv_frame_addr */
#define MJDEC_JDEC_UV_FRAME_ADDR_OFFSET (0x0C)
#define MJDEC_REG_UV_ADDR_START         MJDEC_REG_UV_ADDR_START
#define MJDEC_REG_UV_ADDR_START_POS     (0U)
#define MJDEC_REG_UV_ADDR_START_LEN     (32U)
#define MJDEC_REG_UV_ADDR_START_MSK     (((1U << MJDEC_REG_UV_ADDR_START_LEN) - 1) << MJDEC_REG_UV_ADDR_START_POS)
#define MJDEC_REG_UV_ADDR_START_UMSK    (~(((1U << MJDEC_REG_UV_ADDR_START_LEN) - 1) << MJDEC_REG_UV_ADDR_START_POS))

/* 0x1C : jdec_control_3 */
#define MJDEC_JDEC_CONTROL_3_OFFSET       (0x1C)
#define MJDEC_REG_INT_NORMAL_EN           MJDEC_REG_INT_NORMAL_EN
#define MJDEC_REG_INT_NORMAL_EN_POS       (0U)
#define MJDEC_REG_INT_NORMAL_EN_LEN       (1U)
#define MJDEC_REG_INT_NORMAL_EN_MSK       (((1U << MJDEC_REG_INT_NORMAL_EN_LEN) - 1) << MJDEC_REG_INT_NORMAL_EN_POS)
#define MJDEC_REG_INT_NORMAL_EN_UMSK      (~(((1U << MJDEC_REG_INT_NORMAL_EN_LEN) - 1) << MJDEC_REG_INT_NORMAL_EN_POS))
#define MJDEC_REG_INT_IDLE_EN             MJDEC_REG_INT_IDLE_EN
#define MJDEC_REG_INT_IDLE_EN_POS         (1U)
#define MJDEC_REG_INT_IDLE_EN_LEN         (1U)
#define MJDEC_REG_INT_IDLE_EN_MSK         (((1U << MJDEC_REG_INT_IDLE_EN_LEN) - 1) << MJDEC_REG_INT_IDLE_EN_POS)
#define MJDEC_REG_INT_IDLE_EN_UMSK        (~(((1U << MJDEC_REG_INT_IDLE_EN_LEN) - 1) << MJDEC_REG_INT_IDLE_EN_POS))
#define MJDEC_STS_NORMAL_INT              MJDEC_STS_NORMAL_INT
#define MJDEC_STS_NORMAL_INT_POS          (4U)
#define MJDEC_STS_NORMAL_INT_LEN          (1U)
#define MJDEC_STS_NORMAL_INT_MSK          (((1U << MJDEC_STS_NORMAL_INT_LEN) - 1) << MJDEC_STS_NORMAL_INT_POS)
#define MJDEC_STS_NORMAL_INT_UMSK         (~(((1U << MJDEC_STS_NORMAL_INT_LEN) - 1) << MJDEC_STS_NORMAL_INT_POS))
#define MJDEC_STS_IDLE_INT                MJDEC_STS_IDLE_INT
#define MJDEC_STS_IDLE_INT_POS            (5U)
#define MJDEC_STS_IDLE_INT_LEN            (1U)
#define MJDEC_STS_IDLE_INT_MSK            (((1U << MJDEC_STS_IDLE_INT_LEN) - 1) << MJDEC_STS_IDLE_INT_POS)
#define MJDEC_STS_IDLE_INT_UMSK           (~(((1U << MJDEC_STS_IDLE_INT_LEN) - 1) << MJDEC_STS_IDLE_INT_POS))
#define MJDEC_MJPEG_IDLE                  MJDEC_MJPEG_IDLE
#define MJDEC_MJPEG_IDLE_POS              (8U)
#define MJDEC_MJPEG_IDLE_LEN              (1U)
#define MJDEC_MJPEG_IDLE_MSK              (((1U << MJDEC_MJPEG_IDLE_LEN) - 1) << MJDEC_MJPEG_IDLE_POS)
#define MJDEC_MJPEG_IDLE_UMSK             (~(((1U << MJDEC_MJPEG_IDLE_LEN) - 1) << MJDEC_MJPEG_IDLE_POS))
#define MJDEC_MJPEG_FUNC                  MJDEC_MJPEG_FUNC
#define MJDEC_MJPEG_FUNC_POS              (9U)
#define MJDEC_MJPEG_FUNC_LEN              (1U)
#define MJDEC_MJPEG_FUNC_MSK              (((1U << MJDEC_MJPEG_FUNC_LEN) - 1) << MJDEC_MJPEG_FUNC_POS)
#define MJDEC_MJPEG_FUNC_UMSK             (~(((1U << MJDEC_MJPEG_FUNC_LEN) - 1) << MJDEC_MJPEG_FUNC_POS))
#define MJDEC_MJPEG_FLSH                  MJDEC_MJPEG_FLSH
#define MJDEC_MJPEG_FLSH_POS              (11U)
#define MJDEC_MJPEG_FLSH_LEN              (1U)
#define MJDEC_MJPEG_FLSH_MSK              (((1U << MJDEC_MJPEG_FLSH_LEN) - 1) << MJDEC_MJPEG_FLSH_POS)
#define MJDEC_MJPEG_FLSH_UMSK             (~(((1U << MJDEC_MJPEG_FLSH_LEN) - 1) << MJDEC_MJPEG_FLSH_POS))
#define MJDEC_AXI_READ_IDLE               MJDEC_AXI_READ_IDLE
#define MJDEC_AXI_READ_IDLE_POS           (14U)
#define MJDEC_AXI_READ_IDLE_LEN           (1U)
#define MJDEC_AXI_READ_IDLE_MSK           (((1U << MJDEC_AXI_READ_IDLE_LEN) - 1) << MJDEC_AXI_READ_IDLE_POS)
#define MJDEC_AXI_READ_IDLE_UMSK          (~(((1U << MJDEC_AXI_READ_IDLE_LEN) - 1) << MJDEC_AXI_READ_IDLE_POS))
#define MJDEC_AXI_WRITE_IDLE              MJDEC_AXI_WRITE_IDLE
#define MJDEC_AXI_WRITE_IDLE_POS          (15U)
#define MJDEC_AXI_WRITE_IDLE_LEN          (1U)
#define MJDEC_AXI_WRITE_IDLE_MSK          (((1U << MJDEC_AXI_WRITE_IDLE_LEN) - 1) << MJDEC_AXI_WRITE_IDLE_POS)
#define MJDEC_AXI_WRITE_IDLE_UMSK         (~(((1U << MJDEC_AXI_WRITE_IDLE_LEN) - 1) << MJDEC_AXI_WRITE_IDLE_POS))
#define MJDEC_REG_FRAME_CNT_TRGR_INT      MJDEC_REG_FRAME_CNT_TRGR_INT
#define MJDEC_REG_FRAME_CNT_TRGR_INT_POS  (16U)
#define MJDEC_REG_FRAME_CNT_TRGR_INT_LEN  (5U)
#define MJDEC_REG_FRAME_CNT_TRGR_INT_MSK  (((1U << MJDEC_REG_FRAME_CNT_TRGR_INT_LEN) - 1) << MJDEC_REG_FRAME_CNT_TRGR_INT_POS)
#define MJDEC_REG_FRAME_CNT_TRGR_INT_UMSK (~(((1U << MJDEC_REG_FRAME_CNT_TRGR_INT_LEN) - 1) << MJDEC_REG_FRAME_CNT_TRGR_INT_POS))
#define MJDEC_FRAME_VALID_CNT             MJDEC_FRAME_VALID_CNT
#define MJDEC_FRAME_VALID_CNT_POS         (24U)
#define MJDEC_FRAME_VALID_CNT_LEN         (8U)
#define MJDEC_FRAME_VALID_CNT_MSK         (((1U << MJDEC_FRAME_VALID_CNT_LEN) - 1) << MJDEC_FRAME_VALID_CNT_POS)
#define MJDEC_FRAME_VALID_CNT_UMSK        (~(((1U << MJDEC_FRAME_VALID_CNT_LEN) - 1) << MJDEC_FRAME_VALID_CNT_POS))

/* 0x20 : jdec_int_clr */
#define MJDEC_JDEC_INT_CLR_OFFSET    (0x20)
#define MJDEC_REG_INT_CLR            MJDEC_REG_INT_CLR
#define MJDEC_REG_INT_CLR_POS        (0U)
#define MJDEC_REG_INT_CLR_LEN        (1U)
#define MJDEC_REG_INT_CLR_MSK        (((1U << MJDEC_REG_INT_CLR_LEN) - 1) << MJDEC_REG_INT_CLR_POS)
#define MJDEC_REG_INT_CLR_UMSK       (~(((1U << MJDEC_REG_INT_CLR_LEN) - 1) << MJDEC_REG_INT_CLR_POS))
#define MJDEC_REG_YUV_FRAME_POP      MJDEC_REG_YUV_FRAME_POP
#define MJDEC_REG_YUV_FRAME_POP_POS  (1U)
#define MJDEC_REG_YUV_FRAME_POP_LEN  (1U)
#define MJDEC_REG_YUV_FRAME_POP_MSK  (((1U << MJDEC_REG_YUV_FRAME_POP_LEN) - 1) << MJDEC_REG_YUV_FRAME_POP_POS)
#define MJDEC_REG_YUV_FRAME_POP_UMSK (~(((1U << MJDEC_REG_YUV_FRAME_POP_LEN) - 1) << MJDEC_REG_YUV_FRAME_POP_POS))

/* 0x24 : jdec_fram_push */
#define MJDEC_JDEC_FRAM_PUSH_OFFSET (0x24)
#define MJDEC_REG_JP_PUSH           MJDEC_REG_JP_PUSH
#define MJDEC_REG_JP_PUSH_POS       (0U)
#define MJDEC_REG_JP_PUSH_LEN       (1U)
#define MJDEC_REG_JP_PUSH_MSK       (((1U << MJDEC_REG_JP_PUSH_LEN) - 1) << MJDEC_REG_JP_PUSH_POS)
#define MJDEC_REG_JP_PUSH_UMSK      (~(((1U << MJDEC_REG_JP_PUSH_LEN) - 1) << MJDEC_REG_JP_PUSH_POS))
#define MJDEC_REG_JP_ADDR           MJDEC_REG_JP_ADDR
#define MJDEC_REG_JP_ADDR_POS       (2U)
#define MJDEC_REG_JP_ADDR_LEN       (30U)
#define MJDEC_REG_JP_ADDR_MSK       (((1U << MJDEC_REG_JP_ADDR_LEN) - 1) << MJDEC_REG_JP_ADDR_POS)
#define MJDEC_REG_JP_ADDR_UMSK      (~(((1U << MJDEC_REG_JP_ADDR_LEN) - 1) << MJDEC_REG_JP_ADDR_POS))

/* 0x28 : jdec_fram_sts */
#define MJDEC_JDEC_FRAM_STS_OFFSET (0x28)
#define MJDEC_JP_FRAME_CNT         MJDEC_JP_FRAME_CNT
#define MJDEC_JP_FRAME_CNT_POS     (0U)
#define MJDEC_JP_FRAME_CNT_LEN     (5U)
#define MJDEC_JP_FRAME_CNT_MSK     (((1U << MJDEC_JP_FRAME_CNT_LEN) - 1) << MJDEC_JP_FRAME_CNT_POS)
#define MJDEC_JP_FRAME_CNT_UMSK    (~(((1U << MJDEC_JP_FRAME_CNT_LEN) - 1) << MJDEC_JP_FRAME_CNT_POS))

/* 0x2C : jdec_frame_size */
#define MJDEC_JDEC_FRAME_SIZE_OFFSET (0x2C)
#define MJDEC_REG_FRAME_WBLK         MJDEC_REG_FRAME_WBLK
#define MJDEC_REG_FRAME_WBLK_POS     (0U)
#define MJDEC_REG_FRAME_WBLK_LEN     (12U)
#define MJDEC_REG_FRAME_WBLK_MSK     (((1U << MJDEC_REG_FRAME_WBLK_LEN) - 1) << MJDEC_REG_FRAME_WBLK_POS)
#define MJDEC_REG_FRAME_WBLK_UMSK    (~(((1U << MJDEC_REG_FRAME_WBLK_LEN) - 1) << MJDEC_REG_FRAME_WBLK_POS))
#define MJDEC_REG_FRAME_HBLK         MJDEC_REG_FRAME_HBLK
#define MJDEC_REG_FRAME_HBLK_POS     (16U)
#define MJDEC_REG_FRAME_HBLK_LEN     (12U)
#define MJDEC_REG_FRAME_HBLK_MSK     (((1U << MJDEC_REG_FRAME_HBLK_LEN) - 1) << MJDEC_REG_FRAME_HBLK_POS)
#define MJDEC_REG_FRAME_HBLK_UMSK    (~(((1U << MJDEC_REG_FRAME_HBLK_LEN) - 1) << MJDEC_REG_FRAME_HBLK_POS))

/* 0x30 : jdec_header_skip */
#define MJDEC_JDEC_HEADER_SKIP_OFFSET (0x30)
#define MJDEC_REG_HDER_SKIP_BYTE      MJDEC_REG_HDER_SKIP_BYTE
#define MJDEC_REG_HDER_SKIP_BYTE_POS  (0U)
#define MJDEC_REG_HDER_SKIP_BYTE_LEN  (16U)
#define MJDEC_REG_HDER_SKIP_BYTE_MSK  (((1U << MJDEC_REG_HDER_SKIP_BYTE_LEN) - 1) << MJDEC_REG_HDER_SKIP_BYTE_POS)
#define MJDEC_REG_HDER_SKIP_BYTE_UMSK (~(((1U << MJDEC_REG_HDER_SKIP_BYTE_LEN) - 1) << MJDEC_REG_HDER_SKIP_BYTE_POS))
#define MJDEC_REG_HDER_SKIP           MJDEC_REG_HDER_SKIP
#define MJDEC_REG_HDER_SKIP_POS       (16U)
#define MJDEC_REG_HDER_SKIP_LEN       (1U)
#define MJDEC_REG_HDER_SKIP_MSK       (((1U << MJDEC_REG_HDER_SKIP_LEN) - 1) << MJDEC_REG_HDER_SKIP_POS)
#define MJDEC_REG_HDER_SKIP_UMSK      (~(((1U << MJDEC_REG_HDER_SKIP_LEN) - 1) << MJDEC_REG_HDER_SKIP_POS))

/* 0x40 : jp_addr0 */
#define MJDEC_JP_ADDR0_OFFSET (0x40)
#define MJDEC_JP_ADDR_0       MJDEC_JP_ADDR_0
#define MJDEC_JP_ADDR_0_POS   (0U)
#define MJDEC_JP_ADDR_0_LEN   (32U)
#define MJDEC_JP_ADDR_0_MSK   (((1U << MJDEC_JP_ADDR_0_LEN) - 1) << MJDEC_JP_ADDR_0_POS)
#define MJDEC_JP_ADDR_0_UMSK  (~(((1U << MJDEC_JP_ADDR_0_LEN) - 1) << MJDEC_JP_ADDR_0_POS))

/* 0x44 : jp_addr1 */
#define MJDEC_JP_ADDR1_OFFSET (0x44)
#define MJDEC_JP_ADDR_1       MJDEC_JP_ADDR_1
#define MJDEC_JP_ADDR_1_POS   (0U)
#define MJDEC_JP_ADDR_1_LEN   (32U)
#define MJDEC_JP_ADDR_1_MSK   (((1U << MJDEC_JP_ADDR_1_LEN) - 1) << MJDEC_JP_ADDR_1_POS)
#define MJDEC_JP_ADDR_1_UMSK  (~(((1U << MJDEC_JP_ADDR_1_LEN) - 1) << MJDEC_JP_ADDR_1_POS))

/* 0x48 : jp_addr2 */
#define MJDEC_JP_ADDR2_OFFSET (0x48)
#define MJDEC_JP_ADDR_2       MJDEC_JP_ADDR_2
#define MJDEC_JP_ADDR_2_POS   (0U)
#define MJDEC_JP_ADDR_2_LEN   (32U)
#define MJDEC_JP_ADDR_2_MSK   (((1U << MJDEC_JP_ADDR_2_LEN) - 1) << MJDEC_JP_ADDR_2_POS)
#define MJDEC_JP_ADDR_2_UMSK  (~(((1U << MJDEC_JP_ADDR_2_LEN) - 1) << MJDEC_JP_ADDR_2_POS))

/* 0x4C : jp_addr3 */
#define MJDEC_JP_ADDR3_OFFSET (0x4C)
#define MJDEC_JP_ADDR_3       MJDEC_JP_ADDR_3
#define MJDEC_JP_ADDR_3_POS   (0U)
#define MJDEC_JP_ADDR_3_LEN   (32U)
#define MJDEC_JP_ADDR_3_MSK   (((1U << MJDEC_JP_ADDR_3_LEN) - 1) << MJDEC_JP_ADDR_3_POS)
#define MJDEC_JP_ADDR_3_UMSK  (~(((1U << MJDEC_JP_ADDR_3_LEN) - 1) << MJDEC_JP_ADDR_3_POS))

/* 0x50 : jp_addr4 */
#define MJDEC_JP_ADDR4_OFFSET (0x50)
#define MJDEC_JP_ADDR_4       MJDEC_JP_ADDR_4
#define MJDEC_JP_ADDR_4_POS   (0U)
#define MJDEC_JP_ADDR_4_LEN   (32U)
#define MJDEC_JP_ADDR_4_MSK   (((1U << MJDEC_JP_ADDR_4_LEN) - 1) << MJDEC_JP_ADDR_4_POS)
#define MJDEC_JP_ADDR_4_UMSK  (~(((1U << MJDEC_JP_ADDR_4_LEN) - 1) << MJDEC_JP_ADDR_4_POS))

/* 0x54 : jp_addr5 */
#define MJDEC_JP_ADDR5_OFFSET (0x54)
#define MJDEC_JP_ADDR_5       MJDEC_JP_ADDR_5
#define MJDEC_JP_ADDR_5_POS   (0U)
#define MJDEC_JP_ADDR_5_LEN   (32U)
#define MJDEC_JP_ADDR_5_MSK   (((1U << MJDEC_JP_ADDR_5_LEN) - 1) << MJDEC_JP_ADDR_5_POS)
#define MJDEC_JP_ADDR_5_UMSK  (~(((1U << MJDEC_JP_ADDR_5_LEN) - 1) << MJDEC_JP_ADDR_5_POS))

/* 0x58 : jp_addr6 */
#define MJDEC_JP_ADDR6_OFFSET (0x58)
#define MJDEC_JP_ADDR_6       MJDEC_JP_ADDR_6
#define MJDEC_JP_ADDR_6_POS   (0U)
#define MJDEC_JP_ADDR_6_LEN   (32U)
#define MJDEC_JP_ADDR_6_MSK   (((1U << MJDEC_JP_ADDR_6_LEN) - 1) << MJDEC_JP_ADDR_6_POS)
#define MJDEC_JP_ADDR_6_UMSK  (~(((1U << MJDEC_JP_ADDR_6_LEN) - 1) << MJDEC_JP_ADDR_6_POS))

/* 0x5C : jp_addr7 */
#define MJDEC_JP_ADDR7_OFFSET (0x5C)
#define MJDEC_JP_ADDR_7       MJDEC_JP_ADDR_7
#define MJDEC_JP_ADDR_7_POS   (0U)
#define MJDEC_JP_ADDR_7_LEN   (32U)
#define MJDEC_JP_ADDR_7_MSK   (((1U << MJDEC_JP_ADDR_7_LEN) - 1) << MJDEC_JP_ADDR_7_POS)
#define MJDEC_JP_ADDR_7_UMSK  (~(((1U << MJDEC_JP_ADDR_7_LEN) - 1) << MJDEC_JP_ADDR_7_POS))

/* 0x60 : jp_addr_8 */
#define MJDEC_JP_ADDR_8_OFFSET (0x60)
#define MJDEC_JP_ADDR_8        MJDEC_JP_ADDR_8
#define MJDEC_JP_ADDR_8_POS    (0U)
#define MJDEC_JP_ADDR_8_LEN    (32U)
#define MJDEC_JP_ADDR_8_MSK    (((1U << MJDEC_JP_ADDR_8_LEN) - 1) << MJDEC_JP_ADDR_8_POS)
#define MJDEC_JP_ADDR_8_UMSK   (~(((1U << MJDEC_JP_ADDR_8_LEN) - 1) << MJDEC_JP_ADDR_8_POS))

/* 0x64 : jp_addr_9 */
#define MJDEC_JP_ADDR_9_OFFSET (0x64)
#define MJDEC_JP_ADDR_9        MJDEC_JP_ADDR_9
#define MJDEC_JP_ADDR_9_POS    (0U)
#define MJDEC_JP_ADDR_9_LEN    (32U)
#define MJDEC_JP_ADDR_9_MSK    (((1U << MJDEC_JP_ADDR_9_LEN) - 1) << MJDEC_JP_ADDR_9_POS)
#define MJDEC_JP_ADDR_9_UMSK   (~(((1U << MJDEC_JP_ADDR_9_LEN) - 1) << MJDEC_JP_ADDR_9_POS))

/* 0x68 : jp_addr_a */
#define MJDEC_JP_ADDR_A_OFFSET (0x68)
#define MJDEC_JP_ADDR_A        MJDEC_JP_ADDR_A
#define MJDEC_JP_ADDR_A_POS    (0U)
#define MJDEC_JP_ADDR_A_LEN    (32U)
#define MJDEC_JP_ADDR_A_MSK    (((1U << MJDEC_JP_ADDR_A_LEN) - 1) << MJDEC_JP_ADDR_A_POS)
#define MJDEC_JP_ADDR_A_UMSK   (~(((1U << MJDEC_JP_ADDR_A_LEN) - 1) << MJDEC_JP_ADDR_A_POS))

/* 0x6C : jp_addr_b */
#define MJDEC_JP_ADDR_B_OFFSET (0x6C)
#define MJDEC_JP_ADDR_B        MJDEC_JP_ADDR_B
#define MJDEC_JP_ADDR_B_POS    (0U)
#define MJDEC_JP_ADDR_B_LEN    (32U)
#define MJDEC_JP_ADDR_B_MSK    (((1U << MJDEC_JP_ADDR_B_LEN) - 1) << MJDEC_JP_ADDR_B_POS)
#define MJDEC_JP_ADDR_B_UMSK   (~(((1U << MJDEC_JP_ADDR_B_LEN) - 1) << MJDEC_JP_ADDR_B_POS))

/* 0x70 : jp_addr_c */
#define MJDEC_JP_ADDR_C_OFFSET (0x70)
#define MJDEC_JP_ADDR_C        MJDEC_JP_ADDR_C
#define MJDEC_JP_ADDR_C_POS    (0U)
#define MJDEC_JP_ADDR_C_LEN    (32U)
#define MJDEC_JP_ADDR_C_MSK    (((1U << MJDEC_JP_ADDR_C_LEN) - 1) << MJDEC_JP_ADDR_C_POS)
#define MJDEC_JP_ADDR_C_UMSK   (~(((1U << MJDEC_JP_ADDR_C_LEN) - 1) << MJDEC_JP_ADDR_C_POS))

/* 0x74 : jp_addr_d */
#define MJDEC_JP_ADDR_D_OFFSET (0x74)
#define MJDEC_JP_ADDR_D        MJDEC_JP_ADDR_D
#define MJDEC_JP_ADDR_D_POS    (0U)
#define MJDEC_JP_ADDR_D_LEN    (32U)
#define MJDEC_JP_ADDR_D_MSK    (((1U << MJDEC_JP_ADDR_D_LEN) - 1) << MJDEC_JP_ADDR_D_POS)
#define MJDEC_JP_ADDR_D_UMSK   (~(((1U << MJDEC_JP_ADDR_D_LEN) - 1) << MJDEC_JP_ADDR_D_POS))

/* 0x78 : jp_addr_e */
#define MJDEC_JP_ADDR_E_OFFSET (0x78)
#define MJDEC_JP_ADDR_E        MJDEC_JP_ADDR_E
#define MJDEC_JP_ADDR_E_POS    (0U)
#define MJDEC_JP_ADDR_E_LEN    (32U)
#define MJDEC_JP_ADDR_E_MSK    (((1U << MJDEC_JP_ADDR_E_LEN) - 1) << MJDEC_JP_ADDR_E_POS)
#define MJDEC_JP_ADDR_E_UMSK   (~(((1U << MJDEC_JP_ADDR_E_LEN) - 1) << MJDEC_JP_ADDR_E_POS))

/* 0x7C : jp_addr_f */
#define MJDEC_JP_ADDR_F_OFFSET (0x7C)
#define MJDEC_JP_ADDR_F        MJDEC_JP_ADDR_F
#define MJDEC_JP_ADDR_F_POS    (0U)
#define MJDEC_JP_ADDR_F_LEN    (32U)
#define MJDEC_JP_ADDR_F_MSK    (((1U << MJDEC_JP_ADDR_F_LEN) - 1) << MJDEC_JP_ADDR_F_POS)
#define MJDEC_JP_ADDR_F_UMSK   (~(((1U << MJDEC_JP_ADDR_F_LEN) - 1) << MJDEC_JP_ADDR_F_POS))

/* 0x1F0 : mjdec_debug */
#define MJDEC_DEBUG_OFFSET           (0x1F0)
#define MJDEC_REG_MJDEC_DBG_EN       MJDEC_REG_MJDEC_DBG_EN
#define MJDEC_REG_MJDEC_DBG_EN_POS   (0U)
#define MJDEC_REG_MJDEC_DBG_EN_LEN   (1U)
#define MJDEC_REG_MJDEC_DBG_EN_MSK   (((1U << MJDEC_REG_MJDEC_DBG_EN_LEN) - 1) << MJDEC_REG_MJDEC_DBG_EN_POS)
#define MJDEC_REG_MJDEC_DBG_EN_UMSK  (~(((1U << MJDEC_REG_MJDEC_DBG_EN_LEN) - 1) << MJDEC_REG_MJDEC_DBG_EN_POS))
#define MJDEC_REG_MJDEC_DBG_SEL      MJDEC_REG_MJDEC_DBG_SEL
#define MJDEC_REG_MJDEC_DBG_SEL_POS  (4U)
#define MJDEC_REG_MJDEC_DBG_SEL_LEN  (4U)
#define MJDEC_REG_MJDEC_DBG_SEL_MSK  (((1U << MJDEC_REG_MJDEC_DBG_SEL_LEN) - 1) << MJDEC_REG_MJDEC_DBG_SEL_POS)
#define MJDEC_REG_MJDEC_DBG_SEL_UMSK (~(((1U << MJDEC_REG_MJDEC_DBG_SEL_LEN) - 1) << MJDEC_REG_MJDEC_DBG_SEL_POS))

/* 0x1FC : mjdec_dummy_reg */
#define MJDEC_DUMMY_REG_OFFSET    (0x1FC)
#define MJDEC_JDEC_DUMMY_REG      MJDEC_JDEC_DUMMY_REG
#define MJDEC_JDEC_DUMMY_REG_POS  (0U)
#define MJDEC_JDEC_DUMMY_REG_LEN  (32U)
#define MJDEC_JDEC_DUMMY_REG_MSK  (((1U << MJDEC_JDEC_DUMMY_REG_LEN) - 1) << MJDEC_JDEC_DUMMY_REG_POS)
#define MJDEC_JDEC_DUMMY_REG_UMSK (~(((1U << MJDEC_JDEC_DUMMY_REG_LEN) - 1) << MJDEC_JDEC_DUMMY_REG_POS))

struct mjdec_reg {
    /* 0x0 : jdec_control_1 */
    union {
        struct {
            uint32_t reg_mj_dec_enable    : 1; /* [    0],        r/w,        0x0 */
            uint32_t reg_swap_mode        : 1; /* [    1],        r/w,        0x0 */
            uint32_t reg_u_even           : 1; /* [    2],        r/w,        0x1 */
            uint32_t reg_yuv_mode         : 2; /* [ 4: 3],        r/w,        0x0 */
            uint32_t reg_last_hf_wblk_dmy : 1; /* [    5],        r/w,        0x0 */
            uint32_t reg_last_hf_hblk_dmy : 1; /* [    6],        r/w,        0x0 */
            uint32_t reserved_7           : 1; /* [    7],       rsvd,        0x0 */
            uint32_t reg_w_xlen           : 3; /* [10: 8],        r/w,        0x3 */
            uint32_t reg_last_hf_blk_dmy  : 1; /* [   11],        r/w,        0x0 */
            uint32_t reg_r_xlen           : 3; /* [14:12],        r/w,        0x3 */
            uint32_t reserved_15          : 1; /* [   15],       rsvd,        0x0 */
            uint32_t reg_q_mode           : 7; /* [22:16],        r/w,       0x32 */
            uint32_t reserved_23_31       : 9; /* [31:23],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_control_1;

    /* 0x4  reserved */
    uint8_t RESERVED0x4[4];

    /* 0x08 : jdec_yy_frame_addr */
    union {
        struct {
            uint32_t reg_yy_addr_start : 32; /* [31: 0],        r/w, 0x80000000 */
        } BF;
        uint32_t WORD;
    } jdec_yy_frame_addr;

    /* 0x0C : jdec_uv_frame_addr */
    union {
        struct {
            uint32_t reg_uv_addr_start : 32; /* [31: 0],        r/w, 0x80000000 */
        } BF;
        uint32_t WORD;
    } jdec_uv_frame_addr;

    /* 0x10  reserved */
    uint8_t RESERVED0x10[12];

    /* 0x1C : jdec_control_3 */
    union {
        struct {
            uint32_t reg_int_normal_en      : 1; /* [    0],        r/w,        0x1 */
            uint32_t reg_int_idle_en        : 1; /* [    1],        r/w,        0x0 */
            uint32_t reserved_2_3           : 2; /* [ 3: 2],       rsvd,        0x0 */
            uint32_t sts_normal_int         : 1; /* [    4],          r,        0x0 */
            uint32_t sts_idle_int           : 1; /* [    5],          r,        0x0 */
            uint32_t reserved_6_7           : 2; /* [ 7: 6],       rsvd,        0x0 */
            uint32_t mjpeg_idle             : 1; /* [    8],          r,        0x1 */
            uint32_t mjpeg_func             : 1; /* [    9],          r,        0x0 */
            uint32_t reserved_10            : 1; /* [   10],       rsvd,        0x0 */
            uint32_t mjpeg_flsh             : 1; /* [   11],          r,        0x0 */
            uint32_t reserved_12_13         : 2; /* [13:12],       rsvd,        0x0 */
            uint32_t axi_read_idle          : 1; /* [   14],          r,        0x0 */
            uint32_t axi_write_idle         : 1; /* [   15],          r,        0x0 */
            uint32_t reg_frame_cnt_trgr_int : 5; /* [20:16],        r/w,        0x0 */
            uint32_t reserved_21_23         : 3; /* [23:21],       rsvd,        0x0 */
            uint32_t frame_valid_cnt        : 8; /* [31:24],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_control_3;

    /* 0x20 : jdec_int_clr */
    union {
        struct {
            uint32_t reg_int_clr       : 1;  /* [    0],        w1p,        0x0 */
            uint32_t reg_yuv_frame_pop : 1;  /* [    1],        w1p,        0x0 */
            uint32_t reserved_2_31     : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_int_clr;

    /* 0x24 : jdec_fram_push */
    union {
        struct {
            uint32_t reg_jp_push : 1;  /* [    0],        w1p,        0x0 */
            uint32_t reserved_1  : 1;  /* [    1],       rsvd,        0x0 */
            uint32_t reg_jp_addr : 30; /* [31: 2],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_fram_push;

    /* 0x28 : jdec_fram_sts */
    union {
        struct {
            uint32_t jp_frame_cnt  : 5;  /* [ 4: 0],          r,        0x0 */
            uint32_t reserved_5_31 : 27; /* [31: 5],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_fram_sts;

    /* 0x2C : jdec_frame_size */
    union {
        struct {
            uint32_t reg_frame_wblk : 12; /* [11: 0],        r/w,        0xf */
            uint32_t reserved_12_15 : 4;  /* [15:12],       rsvd,        0x0 */
            uint32_t reg_frame_hblk : 12; /* [27:16],        r/w,       0x14 */
            uint32_t reserved_28_31 : 4;  /* [31:28],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_frame_size;

    /* 0x30 : jdec_header_skip */
    union {
        struct {
            uint32_t reg_hder_skip_byte : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t reg_hder_skip      : 1;  /* [   16],        r/w,        0x0 */
            uint32_t reserved_17_31     : 15; /* [31:17],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } jdec_header_skip;

    /* 0x34  reserved */
    uint8_t RESERVED0x34[12];

    /* 0x40 : jp_addr0 */
    union {
        struct {
            uint32_t jp_addr_0 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr0;

    /* 0x44 : jp_addr1 */
    union {
        struct {
            uint32_t jp_addr_1 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr1;

    /* 0x48 : jp_addr2 */
    union {
        struct {
            uint32_t jp_addr_2 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr2;

    /* 0x4C : jp_addr3 */
    union {
        struct {
            uint32_t jp_addr_3 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr3;

    /* 0x50 : jp_addr4 */
    union {
        struct {
            uint32_t jp_addr_4 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr4;

    /* 0x54 : jp_addr5 */
    union {
        struct {
            uint32_t jp_addr_5 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr5;

    /* 0x58 : jp_addr6 */
    union {
        struct {
            uint32_t jp_addr_6 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr6;

    /* 0x5C : jp_addr7 */
    union {
        struct {
            uint32_t jp_addr_7 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr7;

    /* 0x60 : jp_addr_8 */
    union {
        struct {
            uint32_t jp_addr_8 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_8;

    /* 0x64 : jp_addr_9 */
    union {
        struct {
            uint32_t jp_addr_9 : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_9;

    /* 0x68 : jp_addr_a */
    union {
        struct {
            uint32_t jp_addr_a : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_a;

    /* 0x6C : jp_addr_b */
    union {
        struct {
            uint32_t jp_addr_b : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_b;

    /* 0x70 : jp_addr_c */
    union {
        struct {
            uint32_t jp_addr_c : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_c;

    /* 0x74 : jp_addr_d */
    union {
        struct {
            uint32_t jp_addr_d : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_d;

    /* 0x78 : jp_addr_e */
    union {
        struct {
            uint32_t jp_addr_e : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_e;

    /* 0x7C : jp_addr_f */
    union {
        struct {
            uint32_t jp_addr_f : 32; /* [31: 0],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } jp_addr_f;

    /* 0x80  reserved */
    uint8_t RESERVED0x80[368];

    /* 0x1F0 : mjdec_debug */
    union {
        struct {
            uint32_t reg_mjdec_dbg_en  : 1;  /* [    0],        r/w,        0x0 */
            uint32_t reserved_1_3      : 3;  /* [ 3: 1],       rsvd,        0x0 */
            uint32_t reg_mjdec_dbg_sel : 4;  /* [ 7: 4],        r/w,        0x0 */
            uint32_t reserved_8_31     : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } mjdec_debug;

    /* 0x1f4  reserved */
    uint8_t RESERVED0x1f4[8];

    /* 0x1FC : mjdec_dummy_reg */
    union {
        struct {
            uint32_t jdec_dummy_reg : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } mjdec_dummy_reg;
};

typedef volatile struct mjdec_reg mjdec_reg_t;

#endif /* __MJDEC_REG_H__ */
