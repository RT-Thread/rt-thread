/**
  ******************************************************************************
  * @file    cnn_reg.h
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
#ifndef __CNN_REG_H__
#define __CNN_REG_H__

#include "bl808.h"

/* 0x00 : bl_cnn_cfg */
#define CNN_BL_CNN_CFG_OFFSET (0x00)
#define CNN_REG_INT_CLR       CNN_REG_INT_CLR
#define CNN_REG_INT_CLR_POS   (24U)
#define CNN_REG_INT_CLR_LEN   (1U)
#define CNN_REG_INT_CLR_MSK   (((1U << CNN_REG_INT_CLR_LEN) - 1) << CNN_REG_INT_CLR_POS)
#define CNN_REG_INT_CLR_UMSK  (~(((1U << CNN_REG_INT_CLR_LEN) - 1) << CNN_REG_INT_CLR_POS))
#define CNN_INT               CNN_INT
#define CNN_INT_POS           (25U)
#define CNN_INT_LEN           (1U)
#define CNN_INT_MSK           (((1U << CNN_INT_LEN) - 1) << CNN_INT_POS)
#define CNN_INT_UMSK          (~(((1U << CNN_INT_LEN) - 1) << CNN_INT_POS))
#define CNN_REG_BUS_RST       CNN_REG_BUS_RST
#define CNN_REG_BUS_RST_POS   (27U)
#define CNN_REG_BUS_RST_LEN   (1U)
#define CNN_REG_BUS_RST_MSK   (((1U << CNN_REG_BUS_RST_LEN) - 1) << CNN_REG_BUS_RST_POS)
#define CNN_REG_BUS_RST_UMSK  (~(((1U << CNN_REG_BUS_RST_LEN) - 1) << CNN_REG_BUS_RST_POS))
#define CNN_AXI_IDLE          CNN_AXI_IDLE
#define CNN_AXI_IDLE_POS      (31U)
#define CNN_AXI_IDLE_LEN      (1U)
#define CNN_AXI_IDLE_MSK      (((1U << CNN_AXI_IDLE_LEN) - 1) << CNN_AXI_IDLE_POS)
#define CNN_AXI_IDLE_UMSK     (~(((1U << CNN_AXI_IDLE_LEN) - 1) << CNN_AXI_IDLE_POS))

/* 0x04 : bl_cnn_weig_addr */
#define CNN_BL_CNN_WEIG_ADDR_OFFSET (0x04)
#define CNN_WEIG_ADDR_BASE          CNN_WEIG_ADDR_BASE
#define CNN_WEIG_ADDR_BASE_POS      (0U)
#define CNN_WEIG_ADDR_BASE_LEN      (32U)
#define CNN_WEIG_ADDR_BASE_MSK      (((1U << CNN_WEIG_ADDR_BASE_LEN) - 1) << CNN_WEIG_ADDR_BASE_POS)
#define CNN_WEIG_ADDR_BASE_UMSK     (~(((1U << CNN_WEIG_ADDR_BASE_LEN) - 1) << CNN_WEIG_ADDR_BASE_POS))

/* 0x08 : bl_cnn_img_addr */
#define CNN_BL_CNN_IMG_ADDR_OFFSET (0x08)
#define CNN_IMG_ADDR_BASE          CNN_IMG_ADDR_BASE
#define CNN_IMG_ADDR_BASE_POS      (0U)
#define CNN_IMG_ADDR_BASE_LEN      (32U)
#define CNN_IMG_ADDR_BASE_MSK      (((1U << CNN_IMG_ADDR_BASE_LEN) - 1) << CNN_IMG_ADDR_BASE_POS)
#define CNN_IMG_ADDR_BASE_UMSK     (~(((1U << CNN_IMG_ADDR_BASE_LEN) - 1) << CNN_IMG_ADDR_BASE_POS))

/* 0x0C : bl_cnn_bias_addr */
#define CNN_BL_CNN_BIAS_ADDR_OFFSET (0x0C)
#define CNN_BIAS_ADDR_BASE          CNN_BIAS_ADDR_BASE
#define CNN_BIAS_ADDR_BASE_POS      (0U)
#define CNN_BIAS_ADDR_BASE_LEN      (32U)
#define CNN_BIAS_ADDR_BASE_MSK      (((1U << CNN_BIAS_ADDR_BASE_LEN) - 1) << CNN_BIAS_ADDR_BASE_POS)
#define CNN_BIAS_ADDR_BASE_UMSK     (~(((1U << CNN_BIAS_ADDR_BASE_LEN) - 1) << CNN_BIAS_ADDR_BASE_POS))

/* 0x10 : bl_cnn_inst_addr */
#define CNN_BL_CNN_INST_ADDR_OFFSET (0x10)
#define CNN_INST_ADDR_BASE          CNN_INST_ADDR_BASE
#define CNN_INST_ADDR_BASE_POS      (0U)
#define CNN_INST_ADDR_BASE_LEN      (32U)
#define CNN_INST_ADDR_BASE_MSK      (((1U << CNN_INST_ADDR_BASE_LEN) - 1) << CNN_INST_ADDR_BASE_POS)
#define CNN_INST_ADDR_BASE_UMSK     (~(((1U << CNN_INST_ADDR_BASE_LEN) - 1) << CNN_INST_ADDR_BASE_POS))

/* 0x14 : bl_cnn_out_addr */
#define CNN_BL_CNN_OUT_ADDR_OFFSET (0x14)
#define CNN_OUT_ADDR_BASE          CNN_OUT_ADDR_BASE
#define CNN_OUT_ADDR_BASE_POS      (0U)
#define CNN_OUT_ADDR_BASE_LEN      (32U)
#define CNN_OUT_ADDR_BASE_MSK      (((1U << CNN_OUT_ADDR_BASE_LEN) - 1) << CNN_OUT_ADDR_BASE_POS)
#define CNN_OUT_ADDR_BASE_UMSK     (~(((1U << CNN_OUT_ADDR_BASE_LEN) - 1) << CNN_OUT_ADDR_BASE_POS))

/* 0x18 : bl_cnn_num1 */
#define CNN_BL_CNN_NUM1_OFFSET (0x18)
#define CNN_WEIG_NUM           CNN_WEIG_NUM
#define CNN_WEIG_NUM_POS       (0U)
#define CNN_WEIG_NUM_LEN       (16U)
#define CNN_WEIG_NUM_MSK       (((1U << CNN_WEIG_NUM_LEN) - 1) << CNN_WEIG_NUM_POS)
#define CNN_WEIG_NUM_UMSK      (~(((1U << CNN_WEIG_NUM_LEN) - 1) << CNN_WEIG_NUM_POS))
#define CNN_IMG_NUM            CNN_IMG_NUM
#define CNN_IMG_NUM_POS        (16U)
#define CNN_IMG_NUM_LEN        (16U)
#define CNN_IMG_NUM_MSK        (((1U << CNN_IMG_NUM_LEN) - 1) << CNN_IMG_NUM_POS)
#define CNN_IMG_NUM_UMSK       (~(((1U << CNN_IMG_NUM_LEN) - 1) << CNN_IMG_NUM_POS))

/* 0x1C : bl_cnn_num2 */
#define CNN_BL_CNN_NUM2_OFFSET (0x1C)
#define CNN_BIAS_NUM           CNN_BIAS_NUM
#define CNN_BIAS_NUM_POS       (0U)
#define CNN_BIAS_NUM_LEN       (16U)
#define CNN_BIAS_NUM_MSK       (((1U << CNN_BIAS_NUM_LEN) - 1) << CNN_BIAS_NUM_POS)
#define CNN_BIAS_NUM_UMSK      (~(((1U << CNN_BIAS_NUM_LEN) - 1) << CNN_BIAS_NUM_POS))
#define CNN_OUT_NUM            CNN_OUT_NUM
#define CNN_OUT_NUM_POS        (16U)
#define CNN_OUT_NUM_LEN        (16U)
#define CNN_OUT_NUM_MSK        (((1U << CNN_OUT_NUM_LEN) - 1) << CNN_OUT_NUM_POS)
#define CNN_OUT_NUM_UMSK       (~(((1U << CNN_OUT_NUM_LEN) - 1) << CNN_OUT_NUM_POS))

/* 0x20 : bl_cnn_num3 */
#define CNN_BL_CNN_NUM3_OFFSET (0x20)
#define CNN_INST_NUM           CNN_INST_NUM
#define CNN_INST_NUM_POS       (0U)
#define CNN_INST_NUM_LEN       (16U)
#define CNN_INST_NUM_MSK       (((1U << CNN_INST_NUM_LEN) - 1) << CNN_INST_NUM_POS)
#define CNN_INST_NUM_UMSK      (~(((1U << CNN_INST_NUM_LEN) - 1) << CNN_INST_NUM_POS))
#define CNN_START              CNN_START
#define CNN_START_POS          (16U)
#define CNN_START_LEN          (1U)
#define CNN_START_MSK          (((1U << CNN_START_LEN) - 1) << CNN_START_POS)
#define CNN_START_UMSK         (~(((1U << CNN_START_LEN) - 1) << CNN_START_POS))
#define CNN_RST                CNN_RST
#define CNN_RST_POS            (17U)
#define CNN_RST_LEN            (1U)
#define CNN_RST_MSK            (((1U << CNN_RST_LEN) - 1) << CNN_RST_POS)
#define CNN_RST_UMSK           (~(((1U << CNN_RST_LEN) - 1) << CNN_RST_POS))
#define CNN_INPUT_CHANNEL      CNN_INPUT_CHANNEL
#define CNN_INPUT_CHANNEL_POS  (18U)
#define CNN_INPUT_CHANNEL_LEN  (2U)
#define CNN_INPUT_CHANNEL_MSK  (((1U << CNN_INPUT_CHANNEL_LEN) - 1) << CNN_INPUT_CHANNEL_POS)
#define CNN_INPUT_CHANNEL_UMSK (~(((1U << CNN_INPUT_CHANNEL_LEN) - 1) << CNN_INPUT_CHANNEL_POS))

struct cnn_reg {
    /* 0x00 : bl_cnn_cfg */
    union {
        struct {
            uint32_t reserved_0_23  : 24; /* [23: 0],       rsvd,        0x0 */
            uint32_t reg_int_clr    : 1;  /* [   24],        w1p,        0x0 */
            uint32_t cnn_int        : 1;  /* [   25],          r,        0x0 */
            uint32_t reserved_26    : 1;  /* [   26],       rsvd,        0x0 */
            uint32_t reg_bus_rst    : 1;  /* [   27],        w1p,        0x0 */
            uint32_t reserved_28_30 : 3;  /* [30:28],       rsvd,        0x0 */
            uint32_t axi_idle       : 1;  /* [   31],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_cfg;

    /* 0x04 : bl_cnn_weig_addr */
    union {
        struct {
            uint32_t WEIG_addr_base : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_weig_addr;

    /* 0x08 : bl_cnn_img_addr */
    union {
        struct {
            uint32_t IMG_addr_base : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_img_addr;

    /* 0x0C : bl_cnn_bias_addr */
    union {
        struct {
            uint32_t BIAS_addr_base : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_bias_addr;

    /* 0x10 : bl_cnn_inst_addr */
    union {
        struct {
            uint32_t INST_addr_base : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_inst_addr;

    /* 0x14 : bl_cnn_out_addr */
    union {
        struct {
            uint32_t OUT_addr_base : 32; /* [31: 0],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_out_addr;

    /* 0x18 : bl_cnn_num1 */
    union {
        struct {
            uint32_t WEIG_num : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t IMG_num  : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_num1;

    /* 0x1C : bl_cnn_num2 */
    union {
        struct {
            uint32_t BIAS_num : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t OUT_num  : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_num2;

    /* 0x20 : bl_cnn_num3 */
    union {
        struct {
            uint32_t INST_num       : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t CNN_start      : 1;  /* [   16],        r/w,        0x0 */
            uint32_t CNN_rst        : 1;  /* [   17],        r/w,        0x0 */
            uint32_t input_channel  : 2;  /* [19:18],        r/w,        0x0 */
            uint32_t reserved_20_31 : 12; /* [31:20],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } bl_cnn_num3;
};

typedef volatile struct cnn_reg cnn_reg_t;

#endif /* __CNN_REG_H__ */
