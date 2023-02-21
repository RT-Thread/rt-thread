/**
  ******************************************************************************
  * @file    dsp2_front_reg.h
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
#ifndef __DSP2_FRONT_REG_H__
#define __DSP2_FRONT_REG_H__

#include "bl808.h"

/* 0x110 : pattern_mode */
#define DSP2_FRONT_PATTERN_MODE_OFFSET    (0x110)
#define DSP2_FRONT_PATTERN_MODE_W         DSP2_FRONT_PATTERN_MODE_W
#define DSP2_FRONT_PATTERN_MODE_W_POS     (0U)
#define DSP2_FRONT_PATTERN_MODE_W_LEN     (3U)
#define DSP2_FRONT_PATTERN_MODE_W_MSK     (((1U << DSP2_FRONT_PATTERN_MODE_W_LEN) - 1) << DSP2_FRONT_PATTERN_MODE_W_POS)
#define DSP2_FRONT_PATTERN_MODE_W_UMSK    (~(((1U << DSP2_FRONT_PATTERN_MODE_W_LEN) - 1) << DSP2_FRONT_PATTERN_MODE_W_POS))
#define DSP2_FRONT_PID_INV_RGB_PRE        DSP2_FRONT_PID_INV_RGB_PRE
#define DSP2_FRONT_PID_INV_RGB_PRE_POS    (8U)
#define DSP2_FRONT_PID_INV_RGB_PRE_LEN    (1U)
#define DSP2_FRONT_PID_INV_RGB_PRE_MSK    (((1U << DSP2_FRONT_PID_INV_RGB_PRE_LEN) - 1) << DSP2_FRONT_PID_INV_RGB_PRE_POS)
#define DSP2_FRONT_PID_INV_RGB_PRE_UMSK   (~(((1U << DSP2_FRONT_PID_INV_RGB_PRE_LEN) - 1) << DSP2_FRONT_PID_INV_RGB_PRE_POS))
#define DSP2_FRONT_LID_INV_RGB_PRE        DSP2_FRONT_LID_INV_RGB_PRE
#define DSP2_FRONT_LID_INV_RGB_PRE_POS    (9U)
#define DSP2_FRONT_LID_INV_RGB_PRE_LEN    (1U)
#define DSP2_FRONT_LID_INV_RGB_PRE_MSK    (((1U << DSP2_FRONT_LID_INV_RGB_PRE_LEN) - 1) << DSP2_FRONT_LID_INV_RGB_PRE_POS)
#define DSP2_FRONT_LID_INV_RGB_PRE_UMSK   (~(((1U << DSP2_FRONT_LID_INV_RGB_PRE_LEN) - 1) << DSP2_FRONT_LID_INV_RGB_PRE_POS))
#define DSP2_FRONT_REG_BL_LPID_SEL_W      DSP2_FRONT_REG_BL_LPID_SEL_W
#define DSP2_FRONT_REG_BL_LPID_SEL_W_POS  (10U)
#define DSP2_FRONT_REG_BL_LPID_SEL_W_LEN  (1U)
#define DSP2_FRONT_REG_BL_LPID_SEL_W_MSK  (((1U << DSP2_FRONT_REG_BL_LPID_SEL_W_LEN) - 1) << DSP2_FRONT_REG_BL_LPID_SEL_W_POS)
#define DSP2_FRONT_REG_BL_LPID_SEL_W_UMSK (~(((1U << DSP2_FRONT_REG_BL_LPID_SEL_W_LEN) - 1) << DSP2_FRONT_REG_BL_LPID_SEL_W_POS))
#define DSP2_FRONT_ACT_HSIZE_W            DSP2_FRONT_ACT_HSIZE_W
#define DSP2_FRONT_ACT_HSIZE_W_POS        (16U)
#define DSP2_FRONT_ACT_HSIZE_W_LEN        (16U)
#define DSP2_FRONT_ACT_HSIZE_W_MSK        (((1U << DSP2_FRONT_ACT_HSIZE_W_LEN) - 1) << DSP2_FRONT_ACT_HSIZE_W_POS)
#define DSP2_FRONT_ACT_HSIZE_W_UMSK       (~(((1U << DSP2_FRONT_ACT_HSIZE_W_LEN) - 1) << DSP2_FRONT_ACT_HSIZE_W_POS))

/* 0x114 : clamp_R_Gr */
#define DSP2_FRONT_CLAMP_R_GR_OFFSET (0x114)
#define DSP2_FRONT_CLP_R_PRE         DSP2_FRONT_CLP_R_PRE
#define DSP2_FRONT_CLP_R_PRE_POS     (0U)
#define DSP2_FRONT_CLP_R_PRE_LEN     (16U)
#define DSP2_FRONT_CLP_R_PRE_MSK     (((1U << DSP2_FRONT_CLP_R_PRE_LEN) - 1) << DSP2_FRONT_CLP_R_PRE_POS)
#define DSP2_FRONT_CLP_R_PRE_UMSK    (~(((1U << DSP2_FRONT_CLP_R_PRE_LEN) - 1) << DSP2_FRONT_CLP_R_PRE_POS))
#define DSP2_FRONT_CLP_GR_PRE        DSP2_FRONT_CLP_GR_PRE
#define DSP2_FRONT_CLP_GR_PRE_POS    (16U)
#define DSP2_FRONT_CLP_GR_PRE_LEN    (16U)
#define DSP2_FRONT_CLP_GR_PRE_MSK    (((1U << DSP2_FRONT_CLP_GR_PRE_LEN) - 1) << DSP2_FRONT_CLP_GR_PRE_POS)
#define DSP2_FRONT_CLP_GR_PRE_UMSK   (~(((1U << DSP2_FRONT_CLP_GR_PRE_LEN) - 1) << DSP2_FRONT_CLP_GR_PRE_POS))

/* 0x118 : clamp_B_Gb */
#define DSP2_FRONT_CLAMP_B_GB_OFFSET (0x118)
#define DSP2_FRONT_CLP_GB_PRE        DSP2_FRONT_CLP_GB_PRE
#define DSP2_FRONT_CLP_GB_PRE_POS    (0U)
#define DSP2_FRONT_CLP_GB_PRE_LEN    (16U)
#define DSP2_FRONT_CLP_GB_PRE_MSK    (((1U << DSP2_FRONT_CLP_GB_PRE_LEN) - 1) << DSP2_FRONT_CLP_GB_PRE_POS)
#define DSP2_FRONT_CLP_GB_PRE_UMSK   (~(((1U << DSP2_FRONT_CLP_GB_PRE_LEN) - 1) << DSP2_FRONT_CLP_GB_PRE_POS))
#define DSP2_FRONT_CLP_B_PRE         DSP2_FRONT_CLP_B_PRE
#define DSP2_FRONT_CLP_B_PRE_POS     (16U)
#define DSP2_FRONT_CLP_B_PRE_LEN     (16U)
#define DSP2_FRONT_CLP_B_PRE_MSK     (((1U << DSP2_FRONT_CLP_B_PRE_LEN) - 1) << DSP2_FRONT_CLP_B_PRE_POS)
#define DSP2_FRONT_CLP_B_PRE_UMSK    (~(((1U << DSP2_FRONT_CLP_B_PRE_LEN) - 1) << DSP2_FRONT_CLP_B_PRE_POS))

/* 0x130 : ob_win */
#define DSP2_FRONT_OB_WIN_OFFSET        (0x130)
#define DSP2_FRONT_OB_WIN_STARTX_W      DSP2_FRONT_OB_WIN_STARTX_W
#define DSP2_FRONT_OB_WIN_STARTX_W_POS  (0U)
#define DSP2_FRONT_OB_WIN_STARTX_W_LEN  (16U)
#define DSP2_FRONT_OB_WIN_STARTX_W_MSK  (((1U << DSP2_FRONT_OB_WIN_STARTX_W_LEN) - 1) << DSP2_FRONT_OB_WIN_STARTX_W_POS)
#define DSP2_FRONT_OB_WIN_STARTX_W_UMSK (~(((1U << DSP2_FRONT_OB_WIN_STARTX_W_LEN) - 1) << DSP2_FRONT_OB_WIN_STARTX_W_POS))
#define DSP2_FRONT_OB_WIN_STARTY_W      DSP2_FRONT_OB_WIN_STARTY_W
#define DSP2_FRONT_OB_WIN_STARTY_W_POS  (16U)
#define DSP2_FRONT_OB_WIN_STARTY_W_LEN  (16U)
#define DSP2_FRONT_OB_WIN_STARTY_W_MSK  (((1U << DSP2_FRONT_OB_WIN_STARTY_W_LEN) - 1) << DSP2_FRONT_OB_WIN_STARTY_W_POS)
#define DSP2_FRONT_OB_WIN_STARTY_W_UMSK (~(((1U << DSP2_FRONT_OB_WIN_STARTY_W_LEN) - 1) << DSP2_FRONT_OB_WIN_STARTY_W_POS))

/* 0x134 : black_columns_bit */
#define DSP2_FRONT_BLACK_COLUMNS_BIT_OFFSET (0x134)
#define DSP2_FRONT_BLACK_ROWS_BIT_W         DSP2_FRONT_BLACK_ROWS_BIT_W
#define DSP2_FRONT_BLACK_ROWS_BIT_W_POS     (0U)
#define DSP2_FRONT_BLACK_ROWS_BIT_W_LEN     (4U)
#define DSP2_FRONT_BLACK_ROWS_BIT_W_MSK     (((1U << DSP2_FRONT_BLACK_ROWS_BIT_W_LEN) - 1) << DSP2_FRONT_BLACK_ROWS_BIT_W_POS)
#define DSP2_FRONT_BLACK_ROWS_BIT_W_UMSK    (~(((1U << DSP2_FRONT_BLACK_ROWS_BIT_W_LEN) - 1) << DSP2_FRONT_BLACK_ROWS_BIT_W_POS))
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W      DSP2_FRONT_BLACK_COLUMNS_BIT_W
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_POS  (4U)
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_LEN  (4U)
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_MSK  (((1U << DSP2_FRONT_BLACK_COLUMNS_BIT_W_LEN) - 1) << DSP2_FRONT_BLACK_COLUMNS_BIT_W_POS)
#define DSP2_FRONT_BLACK_COLUMNS_BIT_W_UMSK (~(((1U << DSP2_FRONT_BLACK_COLUMNS_BIT_W_LEN) - 1) << DSP2_FRONT_BLACK_COLUMNS_BIT_W_POS))

/* 0x138 : Ob_R_Gr */
#define DSP2_FRONT_OB_R_GR_OFFSET (0x138)
#define DSP2_FRONT_OB_R_R         DSP2_FRONT_OB_R_R
#define DSP2_FRONT_OB_R_R_POS     (0U)
#define DSP2_FRONT_OB_R_R_LEN     (16U)
#define DSP2_FRONT_OB_R_R_MSK     (((1U << DSP2_FRONT_OB_R_R_LEN) - 1) << DSP2_FRONT_OB_R_R_POS)
#define DSP2_FRONT_OB_R_R_UMSK    (~(((1U << DSP2_FRONT_OB_R_R_LEN) - 1) << DSP2_FRONT_OB_R_R_POS))
#define DSP2_FRONT_OB_GR_R        DSP2_FRONT_OB_GR_R
#define DSP2_FRONT_OB_GR_R_POS    (16U)
#define DSP2_FRONT_OB_GR_R_LEN    (16U)
#define DSP2_FRONT_OB_GR_R_MSK    (((1U << DSP2_FRONT_OB_GR_R_LEN) - 1) << DSP2_FRONT_OB_GR_R_POS)
#define DSP2_FRONT_OB_GR_R_UMSK   (~(((1U << DSP2_FRONT_OB_GR_R_LEN) - 1) << DSP2_FRONT_OB_GR_R_POS))

/* 0x13C : Ob_B_Gb */
#define DSP2_FRONT_OB_B_GB_OFFSET (0x13C)
#define DSP2_FRONT_OB_GB_R        DSP2_FRONT_OB_GB_R
#define DSP2_FRONT_OB_GB_R_POS    (0U)
#define DSP2_FRONT_OB_GB_R_LEN    (16U)
#define DSP2_FRONT_OB_GB_R_MSK    (((1U << DSP2_FRONT_OB_GB_R_LEN) - 1) << DSP2_FRONT_OB_GB_R_POS)
#define DSP2_FRONT_OB_GB_R_UMSK   (~(((1U << DSP2_FRONT_OB_GB_R_LEN) - 1) << DSP2_FRONT_OB_GB_R_POS))
#define DSP2_FRONT_OB_B_R         DSP2_FRONT_OB_B_R
#define DSP2_FRONT_OB_B_R_POS     (16U)
#define DSP2_FRONT_OB_B_R_LEN     (16U)
#define DSP2_FRONT_OB_B_R_MSK     (((1U << DSP2_FRONT_OB_B_R_LEN) - 1) << DSP2_FRONT_OB_B_R_POS)
#define DSP2_FRONT_OB_B_R_UMSK    (~(((1U << DSP2_FRONT_OB_B_R_LEN) - 1) << DSP2_FRONT_OB_B_R_POS))

/* 0x150 : gain_R_G */
#define DSP2_FRONT_GAIN_R_G_OFFSET (0x150)
#define DSP2_FRONT_RGAIN1_PRE      DSP2_FRONT_RGAIN1_PRE
#define DSP2_FRONT_RGAIN1_PRE_POS  (0U)
#define DSP2_FRONT_RGAIN1_PRE_LEN  (11U)
#define DSP2_FRONT_RGAIN1_PRE_MSK  (((1U << DSP2_FRONT_RGAIN1_PRE_LEN) - 1) << DSP2_FRONT_RGAIN1_PRE_POS)
#define DSP2_FRONT_RGAIN1_PRE_UMSK (~(((1U << DSP2_FRONT_RGAIN1_PRE_LEN) - 1) << DSP2_FRONT_RGAIN1_PRE_POS))
#define DSP2_FRONT_GGAIN1_PRE      DSP2_FRONT_GGAIN1_PRE
#define DSP2_FRONT_GGAIN1_PRE_POS  (16U)
#define DSP2_FRONT_GGAIN1_PRE_LEN  (11U)
#define DSP2_FRONT_GGAIN1_PRE_MSK  (((1U << DSP2_FRONT_GGAIN1_PRE_LEN) - 1) << DSP2_FRONT_GGAIN1_PRE_POS)
#define DSP2_FRONT_GGAIN1_PRE_UMSK (~(((1U << DSP2_FRONT_GGAIN1_PRE_LEN) - 1) << DSP2_FRONT_GGAIN1_PRE_POS))

/* 0x154 : gain_B */
#define DSP2_FRONT_GAIN_B_OFFSET   (0x154)
#define DSP2_FRONT_BGAIN1_PRE      DSP2_FRONT_BGAIN1_PRE
#define DSP2_FRONT_BGAIN1_PRE_POS  (0U)
#define DSP2_FRONT_BGAIN1_PRE_LEN  (11U)
#define DSP2_FRONT_BGAIN1_PRE_MSK  (((1U << DSP2_FRONT_BGAIN1_PRE_LEN) - 1) << DSP2_FRONT_BGAIN1_PRE_POS)
#define DSP2_FRONT_BGAIN1_PRE_UMSK (~(((1U << DSP2_FRONT_BGAIN1_PRE_LEN) - 1) << DSP2_FRONT_BGAIN1_PRE_POS))

/* 0x1D0 : clp_rgr_gain */
#define DSP2_FRONT_CLP_RGR_GAIN_OFFSET  (0x1D0)
#define DSP2_FRONT_CLP_GR_GAIN_PRE      DSP2_FRONT_CLP_GR_GAIN_PRE
#define DSP2_FRONT_CLP_GR_GAIN_PRE_POS  (0U)
#define DSP2_FRONT_CLP_GR_GAIN_PRE_LEN  (15U)
#define DSP2_FRONT_CLP_GR_GAIN_PRE_MSK  (((1U << DSP2_FRONT_CLP_GR_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_GR_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_GR_GAIN_PRE_UMSK (~(((1U << DSP2_FRONT_CLP_GR_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_GR_GAIN_PRE_POS))
#define DSP2_FRONT_CLP_R_GAIN_PRE       DSP2_FRONT_CLP_R_GAIN_PRE
#define DSP2_FRONT_CLP_R_GAIN_PRE_POS   (16U)
#define DSP2_FRONT_CLP_R_GAIN_PRE_LEN   (15U)
#define DSP2_FRONT_CLP_R_GAIN_PRE_MSK   (((1U << DSP2_FRONT_CLP_R_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_R_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_R_GAIN_PRE_UMSK  (~(((1U << DSP2_FRONT_CLP_R_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_R_GAIN_PRE_POS))
#define DSP2_FRONT_CLP_GAIN_EN_PRE      DSP2_FRONT_CLP_GAIN_EN_PRE
#define DSP2_FRONT_CLP_GAIN_EN_PRE_POS  (31U)
#define DSP2_FRONT_CLP_GAIN_EN_PRE_LEN  (1U)
#define DSP2_FRONT_CLP_GAIN_EN_PRE_MSK  (((1U << DSP2_FRONT_CLP_GAIN_EN_PRE_LEN) - 1) << DSP2_FRONT_CLP_GAIN_EN_PRE_POS)
#define DSP2_FRONT_CLP_GAIN_EN_PRE_UMSK (~(((1U << DSP2_FRONT_CLP_GAIN_EN_PRE_LEN) - 1) << DSP2_FRONT_CLP_GAIN_EN_PRE_POS))

/* 0x1D4 : clp_bgb_gain */
#define DSP2_FRONT_CLP_BGB_GAIN_OFFSET  (0x1D4)
#define DSP2_FRONT_CLP_GB_GAIN_PRE      DSP2_FRONT_CLP_GB_GAIN_PRE
#define DSP2_FRONT_CLP_GB_GAIN_PRE_POS  (0U)
#define DSP2_FRONT_CLP_GB_GAIN_PRE_LEN  (15U)
#define DSP2_FRONT_CLP_GB_GAIN_PRE_MSK  (((1U << DSP2_FRONT_CLP_GB_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_GB_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_GB_GAIN_PRE_UMSK (~(((1U << DSP2_FRONT_CLP_GB_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_GB_GAIN_PRE_POS))
#define DSP2_FRONT_CLP_B_GAIN_PRE       DSP2_FRONT_CLP_B_GAIN_PRE
#define DSP2_FRONT_CLP_B_GAIN_PRE_POS   (16U)
#define DSP2_FRONT_CLP_B_GAIN_PRE_LEN   (15U)
#define DSP2_FRONT_CLP_B_GAIN_PRE_MSK   (((1U << DSP2_FRONT_CLP_B_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_B_GAIN_PRE_POS)
#define DSP2_FRONT_CLP_B_GAIN_PRE_UMSK  (~(((1U << DSP2_FRONT_CLP_B_GAIN_PRE_LEN) - 1) << DSP2_FRONT_CLP_B_GAIN_PRE_POS))

/* 0x1F0 : Image_select */
#define DSP2_FRONT_IMAGE_SELECT_OFFSET   (0x1F0)
#define DSP2_FRONT_IMAGE_SELECT_PRE      DSP2_FRONT_IMAGE_SELECT_PRE
#define DSP2_FRONT_IMAGE_SELECT_PRE_POS  (0U)
#define DSP2_FRONT_IMAGE_SELECT_PRE_LEN  (2U)
#define DSP2_FRONT_IMAGE_SELECT_PRE_MSK  (((1U << DSP2_FRONT_IMAGE_SELECT_PRE_LEN) - 1) << DSP2_FRONT_IMAGE_SELECT_PRE_POS)
#define DSP2_FRONT_IMAGE_SELECT_PRE_UMSK (~(((1U << DSP2_FRONT_IMAGE_SELECT_PRE_LEN) - 1) << DSP2_FRONT_IMAGE_SELECT_PRE_POS))

struct dsp2_front_reg {
    /* 0x0  reserved */
    uint8_t RESERVED0x0[272];

    /* 0x110 : pattern_mode */
    union {
        struct {
            uint32_t pattern_mode_w    : 3;  /* [ 2: 0],        r/w,        0x0 */
            uint32_t reserved_3_7      : 5;  /* [ 7: 3],       rsvd,        0x0 */
            uint32_t pid_inv_rgb_pre   : 1;  /* [    8],        r/w,        0x0 */
            uint32_t lid_inv_rgb_pre   : 1;  /* [    9],        r/w,        0x0 */
            uint32_t reg_bl_lpid_sel_w : 1;  /* [   10],        r/w,        0x0 */
            uint32_t reserved_11_15    : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t act_hsize_w       : 16; /* [31:16],        r/w,      0x788 */
        } BF;
        uint32_t WORD;
    } pattern_mode;

    /* 0x114 : clamp_R_Gr */
    union {
        struct {
            uint32_t clp_R_pre  : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t clp_Gr_pre : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } clamp_R_Gr;

    /* 0x118 : clamp_B_Gb */
    union {
        struct {
            uint32_t clp_Gb_pre : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t clp_B_pre  : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } clamp_B_Gb;

    /* 0x11c  reserved */
    uint8_t RESERVED0x11c[20];

    /* 0x130 : ob_win */
    union {
        struct {
            uint32_t ob_win_startx_w : 16; /* [15: 0],        r/w,        0x0 */
            uint32_t ob_win_starty_w : 16; /* [31:16],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } ob_win;

    /* 0x134 : black_columns_bit */
    union {
        struct {
            uint32_t black_rows_bit_w    : 4;  /* [ 3: 0],        r/w,        0x2 */
            uint32_t black_columns_bit_w : 4;  /* [ 7: 4],        r/w,        0x8 */
            uint32_t reserved_8_31       : 24; /* [31: 8],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } black_columns_bit;

    /* 0x138 : Ob_R_Gr */
    union {
        struct {
            uint32_t Ob_R_r  : 16; /* [15: 0],          r,        0x0 */
            uint32_t Ob_Gr_r : 16; /* [31:16],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } Ob_R_Gr;

    /* 0x13C : Ob_B_Gb */
    union {
        struct {
            uint32_t Ob_Gb_r : 16; /* [15: 0],          r,        0x0 */
            uint32_t Ob_B_r  : 16; /* [31:16],          r,        0x0 */
        } BF;
        uint32_t WORD;
    } Ob_B_Gb;

    /* 0x140  reserved */
    uint8_t RESERVED0x140[16];

    /* 0x150 : gain_R_G */
    union {
        struct {
            uint32_t rgain1_pre     : 11; /* [10: 0],        r/w,       0x80 */
            uint32_t reserved_11_15 : 5;  /* [15:11],       rsvd,        0x0 */
            uint32_t ggain1_pre     : 11; /* [26:16],        r/w,       0x80 */
            uint32_t reserved_27_31 : 5;  /* [31:27],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gain_R_G;

    /* 0x154 : gain_B */
    union {
        struct {
            uint32_t bgain1_pre     : 11; /* [10: 0],        r/w,       0x80 */
            uint32_t reserved_11_31 : 21; /* [31:11],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } gain_B;

    /* 0x158  reserved */
    uint8_t RESERVED0x158[120];

    /* 0x1D0 : clp_rgr_gain */
    union {
        struct {
            uint32_t clp_gr_gain_pre : 15; /* [14: 0],        r/w,     0x1000 */
            uint32_t reserved_15     : 1;  /* [   15],       rsvd,        0x0 */
            uint32_t clp_r_gain_pre  : 15; /* [30:16],        r/w,     0x1000 */
            uint32_t clp_gain_en_pre : 1;  /* [   31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } clp_rgr_gain;

    /* 0x1D4 : clp_bgb_gain */
    union {
        struct {
            uint32_t clp_gb_gain_pre : 15; /* [14: 0],        r/w,     0x1000 */
            uint32_t reserved_15     : 1;  /* [   15],       rsvd,        0x0 */
            uint32_t clp_b_gain_pre  : 15; /* [30:16],        r/w,     0x1000 */
            uint32_t reserved_31     : 1;  /* [   31],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } clp_bgb_gain;

    /* 0x1d8  reserved */
    uint8_t RESERVED0x1d8[24];

    /* 0x1F0 : Image_select */
    union {
        struct {
            uint32_t Image_Select_pre : 2;  /* [ 1: 0],        r/w,        0x0 */
            uint32_t reserved_2_31    : 30; /* [31: 2],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } Image_select;
};

typedef volatile struct dsp2_front_reg dsp2_front_reg_t;

#endif /* __DSP2_FRONT_REG_H__ */
