/**
  ******************************************************************************
  * @file    bl808_dsp2.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl808_dsp2.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSP2
 *  @{
 */

/** @defgroup  DSP2_Private_Macros
 *  @{
 */
#define DSP2_PRINT_LOG 0
#if DSP2_PRINT_LOG
#include "bflb_platform.h"
#endif

/* To avoid divide-0 exception in code */
#define DIV_0_TO_1(a) ((0 == (a)) ? 1 : (a))

#define DIV_ROUND(divident, divider) (((divident) + ((divider) >> 1)) / (divider))

#define SIGN_EXTEND(x, num_bits) ((((int)(x)) & ((1 << num_bits) - 1)) << (32 - num_bits) >> (32 - num_bits))

#define BL_SET_REG_BITS_VAL_2(val, bitname, bitval) \
    (((val)&bitname##_UMSK) | (((uint32_t)(bitval) << bitname##_POS) & bitname##_MSK))

#define AE_SRAM_BASE  ((uint32_t)0x30019000) /*!< AE status SRAM base address */
#define AWB_SRAM_BASE ((uint32_t)0x3001c000) /*!< AWB status SRAM base address */

#define DSP2_BLC_MAX 1023
#define DSP2_BLC_MIN 0

#define DSP2_BNR_WEIGHT_MAX     64
#define DSP2_BNR_WEIGHT_MIN     0
#define DSP2_BNR_LPF_WEIGHT_MAX 16
#define DSP2_BNR_LPF_WEIGHT_MIN 0

#define DSP2_GAIN_MAX 2047
#define DSP2_GAIN_MIN 0

#define DSP2_CCM_MAX 2047
#define DSP2_CCM_MIN -2048

#define DSP2_BRIGHTNESS_MAX 127
#define DSP2_BRIGHTNESS_MIN -128

#define DSP2_CONTRAST_MAX 255
#define DSP2_CONTRAST_MIN 0

#define DSP2_SATURATION_MAX 255
#define DSP2_SATURATION_MIN 0

#define DSP2_NOISE_LEVEL_MAX 63
#define DSP2_NOISE_LEVEL_MIN 0

#define DSP2_NOISE_THRESHOLD_MAX 127
#define DSP2_NOISE_THRESHOLD_MIN 0

#define DSP2_NR_STRENGTH_MAX 15
#define DSP2_NR_STRENGTH_MIN 0

#define DSP2_Edge_Enhance_LEVEL_MAX 127
#define DSP2_Edge_Enhance_LEVEL_MIN 0

#define DSP2_Edge_Enhance_LIMIT_MAX 255
#define DSP2_Edge_Enhance_LIMIT_MIN 0

#define DSP2_Edge_Enhance_HPF_MAX 8
#define DSP2_Edge_Enhance_HPF_MIN 0

#define DSP2_DPC_TH_MAX 255
#define DSP2_DPC_TH_MIN 0

#define DSP2_AE_ROI_START_X_RANGE_MAX 2047
#define DSP2_AE_ROI_START_Y_RANGE_MAX 2047
#define DSP2_AE_ROI_WIDTH_RANGE_MAX   2047
#define DSP2_AE_ROI_WIDTH_RANGE_MIN   32
#define DSP2_AE_ROI_HEIGHT_RANGE_MAX  2047
#define DSP2_AE_ROI_HEIGHT_RANGE_MIN  2

#define DSP2_AE_GRID_WIDTH_RANGE_MAX  255
#define DSP2_AE_GRID_WIDTH_RANGE_MIN  32
#define DSP2_AE_GRID_HEIGHT_RANGE_MAX 255
#define DSP2_AE_GRID_HEIGHT_RANGE_MIN 2
#define DSP2_AE_GRID_NUM_X_RANGE_MAX  12
#define DSP2_AE_GRID_NUM_X_RANGE_MIN  1
#define DSP2_AE_GRID_NUM_Y_RANGE_MAX  8
#define DSP2_AE_GRID_NUM_Y_RANGE_MIN  1

#define DSP2_AWB_ROI_START_X_RANGE_MAX 2047
#define DSP2_AWB_ROI_START_Y_RANGE_MAX 2047
#define DSP2_AWB_ROI_WIDTH_RANGE_MAX   2047
#define DSP2_AWB_ROI_WIDTH_RANGE_MIN   32
#define DSP2_AWB_ROI_HEIGHT_RANGE_MAX  2047
#define DSP2_AWB_ROI_HEIGHT_RANGE_MIN  2

#define DSP2_AWB_GRID_WIDTH_RANGE_MAX  255
#define DSP2_AWB_GRID_WIDTH_RANGE_MIN  32
#define DSP2_AWB_GRID_HEIGHT_RANGE_MAX 255
#define DSP2_AWB_GRID_HEIGHT_RANGE_MIN 2
#define DSP2_AWB_GRID_NUM_X_RANGE_MAX  32
#define DSP2_AWB_GRID_NUM_X_RANGE_MIN  1
#define DSP2_AWB_GRID_NUM_Y_RANGE_MAX  32
#define DSP2_AWB_GRID_NUM_Y_RANGE_MIN  1

#define DSP2_AWB_R_MAX_THR_RANGE_MAX 4095
#define DSP2_AWB_R_MIN_THR_RANGE_MAX 4095
#define DSP2_AWB_G_MAX_THR_RANGE_MAX 4095
#define DSP2_AWB_G_MIN_THR_RANGE_MAX 4095
#define DSP2_AWB_B_MAX_THR_RANGE_MAX 4095
#define DSP2_AWB_B_MIN_THR_RANGE_MAX 4095

#define DSP2_LSC_OFFSET_MAX 127
#define DSP2_LSC_OFFSET_MIN -128

#define DSP2_EE_DIR_SHPNSS_THRESH_MAX     127
#define DSP2_EE_NO_DIR_SHPNSS_THRESH_MAX  127
#define DSP2_EE_FLAT_REGION_THRESH_MAX    255
#define DSP2_EE_TEXTURE_REGION_THRESH_MAX 511
#define DSP2_EE_EDGE_REGION_THRESH_MAX    65535

#define DSP2_EE_STRENGTH_MAX    127
#define DSP2_EE_NR_STRENGTH_MAX 255

#define DSP2_EE_LUMA_WEIGHT_MAX 1023

#define DSP2_AE_SRAM_BANK1 (AE_SRAM_BASE)         /*!< 0x30019000 */
#define DSP2_AE_SRAM_BANK2 (AE_SRAM_BASE + (768)) /*!< 0x30019300 */

#define DSP2_AWB_SRAM_BANK1 (AWB_SRAM_BASE)              /*!< 0x3001c000 */
#define DSP2_AWB_SRAM_BANK2 (AWB_SRAM_BASE + (1024 * 8)) /*!< 0x3001e000 */

#define DSP2_LSC_MAX_MAX 255
#define DSP2_LSC_MAX_MIN 0

#define DSP2_ERROR_ADDR 0xffffffff

/* For 16bits reg, high 8bits offset 1Byte is low 8bits */
#define DSP2_REG_H_L_OFFSET 0X1

/* Read 16 bits data consits of high 8bits and low 8bits */
#define BL_RD_16_H_L_REG(addr_h, addr_l) \
    ((BL_RD_BYTE(addr_h)) << 8) + (BL_RD_BYTE(addr_l))

#define DSP2_RD_16_H_L_REG(regname_h, regname_l) \
    ((BL_RD_BYTE_REG(DSP2_BASE, regname_h)) << 8) + (BL_RD_BYTE_REG(DSP2_BASE, regname_l))

#define IS_BLACK_WHITE_MODE(mode) (mode == BLACK_WHITE_MODE_ON)

/*@} end of group DSP2_Private_Macros */

/** @defgroup  DSP2_Private_Types
 *  @{
 */
typedef enum {
    DSP2_DPC_OFF = 0,
    DSP2_DPC_FLY,
} DSP2_DPC_MODE_TYPE;

typedef enum {
    DSP2_HSYNC_INVERT_NORMAL = 0,
    DSP2_HSYNC_INVERT_INVERT,
} DSP2_HSYNC_INVERT_TYPE;

typedef enum {
    DSP2_VSYNC_INVERT_NORMAL = 0,
    DSP2_VSYNC_INVERT_INVERT,
} DSP2_VSYNC_INVERT_TYPE;

typedef enum {
    DSP2_HCNT_RST_RISING = 0,
    DSP2_HCNT_RST_FALLING,
} DSP2_HCNT_RST_TYPE;

typedef enum {
    DSP2_VCNT_RST_RISING = 0,
    DSP2_VCNT_RST_FALLING,
} DSP2_VCNT_RST_TYPE;

typedef enum {
    DSP2_VCNT_RST_REVERT_FALLING = 0,
    DSP2_VCNT_RST_REVERT_RISING,
} DSP2_VCNT_RST_REVERT_TYPE;

typedef enum {
    DSP2_FHBLK_LINE_OFF = 0,
    DSP2_FHBLK_LINE_ON = 1,
} DSP2_FHBLK_LINE_TYPE;

/*@} end of group DSP2_Private_Types */

/** @defgroup  DSP2_Private_Variables
 *  @{
 */

/*@} end of group DSP2_Private_Variables */

/** @defgroup  DSP2_Global_Variables
 *  @{
 */

/*@} end of group DSP2_Global_Variables */

/** @defgroup  DSP2_Private_Fun_Declaration
 *  @{
 */

/*@} end of group DSP2_Private_Fun_Declaration */

/** @defgroup  DSP2_Private_Functions
 *  @{
 */
static uint16_t DSP2_Calc_Total_Width(const DSP2_TG_Cfg_Type *config)
{
    // uint32_t pix_clk = config->pix_clk;
    // uint32_t DSP2_clk = config->DSP2_clk;
    // uint16_t sns_tot_width = config->total_width;

    return (uint16_t)((uint64_t)config->DSP2_clk / config->total_height / config->fps + 48) & 0xFFFE;

    /* the final total width must be even */

    // return (uint16_t)((uint64_t)DSP2_clk/1125/25) & 0xFFFE;
    // return (uint16_t)((uint64_t)sns_tot_width * DSP2_clk / pix_clk + 48) & 0xFFFE;    //TODO: remove magic number
}

static bool is_LSC_Coeff_Valid(const DSP2_LSC_COEF_S *lsc)
{
    int i;

    const int DSP2_LSC_COEF_LIMIT[LSC_COEF_NUM][2] = {
        { -4194304, 4194303 }, /*!< A */
        { -4096, 4095 },       /*!< B */
        { 0, 255 },            /*!< C */
        { -4194304, 4194303 }, /*!< D */
        { -4096, 4095 },       /*!< E */
        { -4194304, 4194303 }, /*!< G */
    };

    for (i = 0; i < LSC_COEF_NUM; ++i) {
        if ((lsc->lsc_coef_r.coef[i]) < DSP2_LSC_COEF_LIMIT[i][0] || (lsc->lsc_coef_r.coef[i]) > DSP2_LSC_COEF_LIMIT[i][1]) {
            return false;
        }

        if ((lsc->lsc_coef_g.coef[i]) < DSP2_LSC_COEF_LIMIT[i][0] || (lsc->lsc_coef_g.coef[i]) > DSP2_LSC_COEF_LIMIT[i][1]) {
            return false;
        }

        if ((lsc->lsc_coef_b.coef[i]) < DSP2_LSC_COEF_LIMIT[i][0] || (lsc->lsc_coef_b.coef[i]) > DSP2_LSC_COEF_LIMIT[i][1]) {
            return false;
        }
    }

    return true;
}

static int DSP2_Calc_Clamp_Gain(int black_level)
{
    return DIV_ROUND(4095 * 4096, (4095 - black_level));
}

/*@} end of group DSP2_Private_Functions */

/** @defgroup  DSP2_Public_Functions
 *  @{
 */

void DSP2_Init(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_COEFF);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_YSUM_COEFF_R_PRE, 77);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_YSUM_COEFF_G_PRE, 150);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_YSUM_COEFF_B_PRE, 29);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AE_COEFF, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_B);
    /* yuv output 16bit mode */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_OUT_FORMAT_W, 1);
    /* YUYV order */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CBCR_SELECT_W, 1);

    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_DNR_B, tmpVal);
    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_SETTING);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_BL_AWB_GAIN_SEL_W);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_BL_DIGITAL_GAIN_SEL_W);

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AWB_SETTING, tmpVal);
}

void DSP2_Set_TG_Cfg(const DSP2_TG_Cfg_Type *cfg)
{
    dsp2_tg_reg_t *dsp2_tg_reg = (dsp2_tg_reg_t *)DSP2_BASE;

    uint16_t act_start_pixel = 0;
    uint16_t act_pixel_width = 0;
    uint16_t act_start_line = 0;
    uint16_t act_line_height = 0;

    uint16_t out_pixel_width = 0;
    uint16_t out_line_height = 0;

    uint16_t out_start_pixel = 0;
    uint16_t out_start_line = 0;

    /* TODO: crop the best window */
    if (DSP2_SYNC_MODE_INPUT_VBLANK_NO_TOGGLE == cfg->sync_mode_value) {
        act_start_pixel = 0; /* hcount reset in rising edge, so H blanking is put after valid line */
        act_pixel_width = cfg->active_width;
        act_start_line = 0;
        act_line_height = cfg->active_height;
    } else {
        act_start_pixel = cfg->total_width - cfg->active_width;
        act_pixel_width = cfg->active_width;
        act_start_line = cfg->total_height - cfg->active_height;
        act_line_height = cfg->active_height;
    }

    out_pixel_width = cfg->out_width;
    out_line_height = cfg->out_height;

    out_start_pixel = (act_pixel_width - out_pixel_width) / 2;
    out_start_line = (act_line_height - out_line_height) / 2;

    /* further reduce frame latency by enabling act_vsync reset mode on vsync edge */
    dsp2_tg_reg->dvp_mode.BF.reg_act_vsync_rst_en_w = 1;

    /* set sync mode */
    dsp2_tg_reg->dvp_mode.BF.sync_mode_w = cfg->sync_mode_value;
    dsp2_tg_reg->dvp_mode.BF.hsync_in_inv_w = DSP2_HSYNC_INVERT_NORMAL;
    /* dvp_tsrc would do vsync invert so vsync pulse is always active low */
    dsp2_tg_reg->dvp_mode.BF.vsync_in_inv_w = DSP2_VSYNC_INVERT_NORMAL;
    dsp2_tg_reg->dvp_mode.BF.fhblk_line_on_w = DSP2_FHBLK_LINE_OFF;

    /* note: if vsync invert, vcnt reset mode set 0, means falling
	    else if vsync not invert,  vcont reset mode set 1, also means falling
	    this value will not open to user now.
	*/
    if (DSP2_SYNC_MODE_INPUT_VBLANK_NO_TOGGLE == cfg->sync_mode_value) {
        /* hcnt reset in rising edge, so H blanking is put after valid line
		    vcnt reset mode must be 0, to make sure vcnt is reset to 4095 instead of 0. */
        dsp2_tg_reg->dvp_mode.BF.hcnt_rst_mode_w = DSP2_HCNT_RST_RISING;
        dsp2_tg_reg->dvp_mode.BF.vcnt_rst_mode_w = DSP2_VCNT_RST_RISING;
    } else {
        dsp2_tg_reg->dvp_mode.BF.hcnt_rst_mode_w = DSP2_HCNT_RST_FALLING;
        dsp2_tg_reg->dvp_mode.BF.vcnt_rst_mode_w = DSP2_HCNT_RST_FALLING;
    }

    /* set total pixels and total lines */
    dsp2_tg_reg->total_pixels.BF.total_hpixels_w =
        DSP2_Calc_Total_Width(cfg);

    dsp2_tg_reg->total_pixels.BF.total_vlines_w = cfg->total_height;
    ;

    /* act start pixel, act pixel width */
    dsp2_tg_reg->act_pixels_1.BF.act_start_pixel_w = act_start_pixel;
    dsp2_tg_reg->act_pixels_1.BF.act_pixel_width_w = act_pixel_width;

    /* act start line, act line height */
    dsp2_tg_reg->act_pixels_2.BF.act_start_line_w = act_start_line;
    dsp2_tg_reg->act_pixels_2.BF.act_line_height_w = act_line_height;

    /* out start pixel, out pixel width */
    dsp2_tg_reg->fact_pixels_1.BF.fact_start_pixel_w = out_start_pixel;
    dsp2_tg_reg->fact_pixels_1.BF.fact_pixel_width_w = out_pixel_width;

    /* out start line, out line height*/
    dsp2_tg_reg->fact_pixels_2.BF.fact_start_line_w = out_start_line;

    dsp2_tg_reg->fact_pixels_2.BF.fact_line_height_w = out_line_height;
}

int DSP2_Get_Output_Window(BL_Img_Size_T *out_win)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_TG_FACT_PIXELS_1);
    out_win->width = BL_GET_REG_BITS_VAL(tmpVal, DSP2_TG_FACT_PIXEL_WIDTH_W);
    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_TG_FACT_PIXELS_2);
    out_win->height = BL_GET_REG_BITS_VAL(tmpVal, DSP2_TG_FACT_LINE_HEIGHT_W);

    return 0;
}

void DSP2_Set_Bayer_Pattern(const BAYER_PATTERN_E *pattern)
{
    dsp2_front_reg_t *dsp2_front_reg = (dsp2_front_reg_t *)DSP2_BASE;

    dsp2_front_reg->pattern_mode.BF.pattern_mode_w = 0;

    /* fix issue: bayer pattern highly sensitive to total width setting */
    dsp2_front_reg->pattern_mode.BF.reg_bl_lpid_sel_w = 1;

    if (*pattern == BAYER_PATTERN_BG) {
        /* lid invert depends on the total height */
        dsp2_front_reg->pattern_mode.BF.pid_inv_rgb_pre = 1;
        dsp2_front_reg->pattern_mode.BF.lid_inv_rgb_pre = 1;
    } else if (*pattern == BAYER_PATTERN_RG) {
        dsp2_front_reg->pattern_mode.BF.pid_inv_rgb_pre = 0;
        dsp2_front_reg->pattern_mode.BF.lid_inv_rgb_pre = 0;
    } else if (*pattern == BAYER_PATTERN_GR) {
        dsp2_front_reg->pattern_mode.BF.pid_inv_rgb_pre = 1;
        dsp2_front_reg->pattern_mode.BF.lid_inv_rgb_pre = 0;
    } else if (*pattern == BAYER_PATTERN_GB) {
        dsp2_front_reg->pattern_mode.BF.pid_inv_rgb_pre = 0;
        dsp2_front_reg->pattern_mode.BF.lid_inv_rgb_pre = 1;
    } else {
#if DSP2_PRINT_LOG
        MSG("Error bayer pattern!\n");
#endif
        return;
    }

    /* hack for CISTA sensor */
    //dsp2_front_reg->pattern_mode.BF.pid_inv_rgb_pre = 1;
    //dsp2_front_reg->pattern_mode.BF.lid_inv_rgb_pre = 0;
}

void DSP2_Set_AE_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_GRID_SIZE);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_NEW_AE_STA_ENABLE_W);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE_NEW_AE_STA_ENABLE_W);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AE_GRID_SIZE, tmpVal);
}

void DSP2_Set_AE_Stats_Conf(const dsp2_ae_stats_conf_t *ae_stats_conf)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(ae_stats_conf->roi_start_x, DSP2_AE_ROI_START_X_RANGE_MAX);
    CHECK_PARAM_MAX(ae_stats_conf->roi_start_y, DSP2_AE_ROI_START_Y_RANGE_MAX);
    CHECK_PARAM_RANGE(ae_stats_conf->roi_width,
                      DSP2_AE_ROI_WIDTH_RANGE_MIN, DSP2_AE_ROI_WIDTH_RANGE_MAX);
    CHECK_PARAM_RANGE(ae_stats_conf->roi_height,
                      DSP2_AE_ROI_HEIGHT_RANGE_MIN, DSP2_AE_ROI_HEIGHT_RANGE_MAX);
    CHECK_PARAM_MIN(ae_stats_conf->grid_width, DSP2_AE_GRID_WIDTH_RANGE_MIN);
    CHECK_PARAM_MIN(ae_stats_conf->grid_height, DSP2_AE_GRID_HEIGHT_RANGE_MIN);
    CHECK_PARAM_RANGE(ae_stats_conf->grid_num_x,
                      DSP2_AE_GRID_NUM_X_RANGE_MIN, DSP2_AE_GRID_NUM_X_RANGE_MAX);
    CHECK_PARAM_RANGE(ae_stats_conf->grid_num_y,
                      DSP2_AE_GRID_NUM_Y_RANGE_MIN, DSP2_AE_GRID_NUM_Y_RANGE_MAX);

    /* special check */

    /* AE ROI must be in the active image region */
    if ((ae_stats_conf->roi_start_x + ae_stats_conf->roi_width > ae_stats_conf->img_width) ||
        (ae_stats_conf->roi_start_y + ae_stats_conf->roi_height > ae_stats_conf->img_height)) {
#if DSP2_PRINT_LOG
        MSG("AE ROI must be in the active image region!\r\n");
#endif
    }

    /* grid width/height must be even number */
    if ((ae_stats_conf->grid_width & 0x1) & (ae_stats_conf->grid_height & 0x1)) {
#if DSP2_PRINT_LOG
        MSG("Grid width/height must be even number!\r\n");
#endif
    }

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_ROI_X);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_START_X_PRE, ae_stats_conf->roi_start_x);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_WIDTH_PRE, ae_stats_conf->roi_width);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AE_ROI_X, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_ROI_Y);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_START_Y_PRE, ae_stats_conf->roi_start_y);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_HEIGHT_PRE, ae_stats_conf->roi_height);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AE_ROI_Y, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_IMAGE_SIZE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_IMAGE_WIDTH_PRE, ae_stats_conf->img_width);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_IMAGE_HEIGHT_PRE, ae_stats_conf->img_height);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AE_IMAGE_SIZE, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_GRID_SIZE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_WIDTH_PRE, ae_stats_conf->grid_width);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_HEIGHT_PRE, ae_stats_conf->grid_height);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_X_MAX_PRE, ae_stats_conf->grid_num_x);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_Y_MAX_PRE, ae_stats_conf->grid_num_y);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_NEW_AE_STA_ENABLE_W);
    /* AE occupies 2 bank of memory*/
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_AE_SWITCH_BANK_EN_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AE_GRID_SIZE, tmpVal);
}

void DSP2_Get_AE_Stats_Conf(dsp2_ae_stats_conf_t *ae_stats_conf)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_ROI_X);
    ae_stats_conf->roi_start_x = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_START_X_PRE);
    ae_stats_conf->roi_width = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_WIDTH_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_ROI_Y);
    ae_stats_conf->roi_start_y = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_START_Y_PRE);
    ae_stats_conf->roi_height = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_ROI_HEIGHT_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_IMAGE_SIZE);
    ae_stats_conf->img_width = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_IMAGE_WIDTH_PRE);
    ae_stats_conf->img_height = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_IMAGE_HEIGHT_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_GRID_SIZE);
    ae_stats_conf->grid_width = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_WIDTH_PRE);
    ae_stats_conf->grid_height = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_HEIGHT_PRE);
    ae_stats_conf->grid_width = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_X_MAX_PRE);
    ae_stats_conf->grid_height = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AE_GRID_Y_MAX_PRE);
}

int DSP2_Get_AE_Stats(int grid_num, uint32_t *data)
{
    uint32_t tmpVal;
    uint32_t buf_idx;
    uint32_t buf_addr;
    uint32_t w_cnt_idx_start;
    uint32_t w_cnt_idx_end;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_STATUS);
    buf_idx = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAE_BUF_IDX_R);
    w_cnt_idx_start = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAE_W_CNT_R);

    buf_addr = (0 == buf_idx) ? DSP2_AE_SRAM_BANK1 : DSP2_AE_SRAM_BANK2;
    ARCH_MemCpy4(data, (uint32_t *)(uintptr_t)buf_addr, grid_num * 2); // two word per grid

    w_cnt_idx_end = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAE_W_CNT_R);

    if (w_cnt_idx_start != w_cnt_idx_end) {
#if DSP2_PRINT_LOG
        MSG("AE statistics overwrite!\n");
#endif
        return -1;
    }

    return 0;
}

void DSP2_Get_AE_Sum(int grid_idx, AE_GRID_DATA_TYPE_E data_type, uint32_t *data)
{
    dsp2_ae_sum_t *grid_array;
    uint32_t tmpVal;
    uint32_t buf_idx;
    uint32_t buf_addr;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AE_STATUS);
    buf_idx = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAE_BUF_IDX_R);

    buf_addr = (0 == buf_idx) ? DSP2_AE_SRAM_BANK1 : DSP2_AE_SRAM_BANK2;
    grid_array = (dsp2_ae_sum_t *)(uintptr_t)buf_addr;
    *data = grid_array[grid_idx].y_sum;
}

void DSP2_Set_AWB_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_SETTING);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE_NEW_AWB_STA_ENABLE_W);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AWB_SETTING, tmpVal);
}

void DSP2_Set_AWB_Stats_Conf(const dsp2_awb_stats_conf_t *awb_stats_conf)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    CHECK_PARAM_MAX(awb_stats_conf->roi_start_x, DSP2_AWB_ROI_START_X_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->roi_start_y, DSP2_AWB_ROI_START_Y_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->roi_width, DSP2_AWB_ROI_WIDTH_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->roi_height, DSP2_AWB_ROI_HEIGHT_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->grid_num_x, DSP2_AWB_GRID_NUM_X_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->grid_num_y, DSP2_AWB_GRID_NUM_Y_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->r_max_thr, DSP2_AWB_R_MAX_THR_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->r_min_thr, DSP2_AWB_R_MIN_THR_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->g_max_thr, DSP2_AWB_G_MAX_THR_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->g_min_thr, DSP2_AWB_G_MIN_THR_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->b_max_thr, DSP2_AWB_B_MAX_THR_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->b_min_thr, DSP2_AWB_B_MIN_THR_RANGE_MAX);

    CHECK_PARAM_MIN(awb_stats_conf->grid_width, DSP2_AWB_GRID_WIDTH_RANGE_MIN);
    CHECK_PARAM_MIN(awb_stats_conf->grid_height, DSP2_AWB_GRID_HEIGHT_RANGE_MIN);

    /* special check */
    /* AWB ROI must be in the active image region */
    if ((awb_stats_conf->roi_start_x + awb_stats_conf->roi_width > awb_stats_conf->img_width) ||
        (awb_stats_conf->roi_start_y + awb_stats_conf->roi_height > awb_stats_conf->img_height)) {
#if DSP2_PRINT_LOG
        MSG("AWB ROI must be in the active image region!\r\n");
#endif
    }

    /* grid width/height must be even number */
    if ((awb_stats_conf->grid_width & 0x1) & (awb_stats_conf->grid_height & 0x1)) {
#if DSP2_PRINT_LOG
        MSG("Grid width/height must be even number!\r\n");
#endif
    }

    dsp2_middle_reg->awb_roi_x.BF.awb_roi_start_x_w = awb_stats_conf->roi_start_x;
    dsp2_middle_reg->awb_roi_x.BF.awb_roi_width_w = awb_stats_conf->roi_width;
    dsp2_middle_reg->awb_roi_y.BF.awb_roi_start_y_w = awb_stats_conf->roi_start_y;
    dsp2_middle_reg->awb_roi_y.BF.awb_roi_height_w = awb_stats_conf->roi_height;

    dsp2_middle_reg->awb_image_size.BF.awb_image_width_w = awb_stats_conf->img_width;
    dsp2_middle_reg->awb_image_size.BF.awb_image_height_w = awb_stats_conf->img_height;

    dsp2_middle_reg->awb_grid_size.BF.awb_grid_width_w = awb_stats_conf->grid_width;
    dsp2_middle_reg->awb_grid_size.BF.awb_grid_height_w = awb_stats_conf->grid_height;

    dsp2_middle_reg->awb_grid_size.BF.awb_grid_x_max_w = awb_stats_conf->grid_num_x;
    dsp2_middle_reg->awb_grid_size.BF.awb_grid_y_max_w = awb_stats_conf->grid_num_y;

    dsp2_middle_reg->awb_r_thre.BF.awb_r_max_thr_w = awb_stats_conf->r_max_thr;
    dsp2_middle_reg->awb_r_thre.BF.awb_r_min_thr_w = awb_stats_conf->r_min_thr;

    dsp2_middle_reg->awb_g_thre.BF.awb_g_max_thr_w = awb_stats_conf->g_max_thr;
    dsp2_middle_reg->awb_g_thre.BF.awb_g_min_thr_w = awb_stats_conf->g_min_thr;

    dsp2_middle_reg->awb_b_thre.BF.awb_b_max_thr_w = awb_stats_conf->b_max_thr;
    dsp2_middle_reg->awb_b_thre.BF.awb_b_min_thr_w = awb_stats_conf->b_min_thr;

    dsp2_middle_reg->awb_setting.BF.new_awb_sta_enable_w = 1;

    /* AWB occupies 2 banks of memory  */
    dsp2_middle_reg->awb_setting.BF.awb_switch_bank_en_w = 1;
}

void DSP2_Get_AWB_Stats_Conf(dsp2_awb_stats_conf_t *awb_stats_conf)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    awb_stats_conf->roi_start_x = dsp2_middle_reg->awb_roi_x.BF.awb_roi_start_x_w;
    awb_stats_conf->roi_start_y = dsp2_middle_reg->awb_roi_y.BF.awb_roi_start_y_w;
    awb_stats_conf->roi_width = dsp2_middle_reg->awb_roi_x.BF.awb_roi_width_w;
    awb_stats_conf->roi_height = dsp2_middle_reg->awb_roi_y.BF.awb_roi_height_w;
    awb_stats_conf->img_width = dsp2_middle_reg->awb_image_size.BF.awb_image_width_w;
    awb_stats_conf->img_height = dsp2_middle_reg->awb_image_size.BF.awb_image_height_w;

    awb_stats_conf->grid_width = dsp2_middle_reg->awb_grid_size.BF.awb_grid_width_w;
    awb_stats_conf->grid_height = dsp2_middle_reg->awb_grid_size.BF.awb_grid_height_w;

    awb_stats_conf->grid_num_x = dsp2_middle_reg->awb_grid_size.BF.awb_grid_x_max_w;
    awb_stats_conf->grid_num_y = dsp2_middle_reg->awb_grid_size.BF.awb_grid_y_max_w;
}

int DSP2_Get_AWB_Stats(int grid_num, uint32_t *data)
{
    uint32_t tmpVal;
    uint32_t buf_idx;
    uint32_t buf_addr;
    uint32_t w_cnt_idx_start;
    uint32_t w_cnt_idx_end;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_STA_DBG1);
    buf_idx = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAWB_BUF_IDX_R);
    w_cnt_idx_start = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAWB_W_CNT_R);

    buf_addr = (0 == buf_idx) ? DSP2_AWB_SRAM_BANK1 : DSP2_AWB_SRAM_BANK2;
    ARCH_MemCpy4(data, (uint32_t *)(uintptr_t)buf_addr, grid_num * 2); // two word per grid

    w_cnt_idx_end = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAWB_W_CNT_R);

    if (w_cnt_idx_start != w_cnt_idx_end) {
#if DSP2_PRINT_LOG
        MSG("AWB statistics overwrite!\n");
#endif
        return -1;
    }

    return 0;
}

void DSP2_Get_AWB_Sum(int grid_idx, RGB_SUM_S *rgb_sum)
{
    uint32_t tmpVal;
    uint32_t buf_idx;
    uint32_t buf_addr;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_STA_DBG1);
    buf_idx = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_BLAWB_BUF_IDX_R);

    buf_addr = (0 == buf_idx) ? DSP2_AWB_SRAM_BANK1 : DSP2_AWB_SRAM_BANK2;

    // dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t*)DSP2_BASE;
    dsp2_awb_sum_t *grid_array = (dsp2_awb_sum_t *)(uintptr_t)buf_addr;

    rgb_sum->r_sum = grid_array[grid_idx].r_sum;
    rgb_sum->g_sum = grid_array[grid_idx].g_sum;
    rgb_sum->b_sum = grid_array[grid_idx].b_sum;

    // *buf_idx = dsp2_middle_reg->awb_sta_dbg1.BF.blawb_buf_idx_r;
}

void DSP2_Get_AWB_ValidGridNum(int *valid_grid_num)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    *valid_grid_num = dsp2_middle_reg->awb_setting.BF.grid_cnt_within_thre_r;
}

void DSP2_Set_AWB_Gain(const DSP2_RGB_Gain_Type *rgb_gain)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_RGR_GAIN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_R_GAIN_PRE, rgb_gain->r_gain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_GR_GAIN_PRE, rgb_gain->g_gain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AWB_RGR_GAIN, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_BGB_GAIN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_B_GAIN_PRE, rgb_gain->b_gain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_GB_GAIN_PRE, rgb_gain->g_gain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_AWB_BGB_GAIN, tmpVal);
}

void DSP2_Get_AWB_Gain(DSP2_RGB_Gain_Type *rgb_gain)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_RGR_GAIN);

    rgb_gain->r_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_R_GAIN_PRE);
    rgb_gain->g_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_GR_GAIN_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_AWB_BGB_GAIN);
    rgb_gain->b_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_AWB_B_GAIN_PRE);
}

void DSP2_Set_AWB2_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_INT);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE3_AWB2_STAT_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE3_AWB2_STAT_EN_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_INT, tmpVal);
}

void DSP2_Set_AWB2_Gain_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_INT);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE3_AWB2_GAIN_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE3_AWB2_GAIN_EN_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_INT, tmpVal);
}

int DSP2_Get_AWB2_Sum(dsp2_awb2_sum_t *sum)
{
    uint32_t tmpVal;
    uint64_t tmpVal64;
    uint32_t buf_idx;
    uint32_t w_cnt_idx_start;
    uint32_t w_cnt_idx_end;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_INT);
    buf_idx = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_BUF_IDX_R);
    w_cnt_idx_start = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_W_CNT_R);

    if (0 == buf_idx) {
        sum->r_avg = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R0), DSP2_MIDDLE3_AWB2_R_AVG0_R);
        sum->g_avg = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R0), DSP2_MIDDLE3_AWB2_G_AVG0_R);
        sum->b_avg = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R1), DSP2_MIDDLE3_AWB2_B_AVG0_R);
        sum->white_ratio = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R1), DSP2_MIDDLE3_AWB2_WHITE_RATIO0_R);

        tmpVal64 = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R4);
        tmpVal = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R5), DSP2_MIDDLE3_AWB2_WHITER_SUML0_R);
        sum->white_r_sum = (tmpVal64 << 9) + tmpVal;

        tmpVal64 = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R7);
        tmpVal = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R8), DSP2_MIDDLE3_AWB2_WHITEG_SUML0_R);
        sum->white_g_sum = (tmpVal64 << 9) + tmpVal;

        tmpVal64 = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_RA);
        tmpVal = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_RB), DSP2_MIDDLE3_AWB2_WHITEB_SUML0_R);
        sum->white_b_sum = (tmpVal64 << 9) + tmpVal;
    } else {
        sum->r_avg = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R2), DSP2_MIDDLE3_AWB2_R_AVG1_R);
        sum->g_avg = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R2), DSP2_MIDDLE3_AWB2_G_AVG1_R);
        sum->b_avg = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R3), DSP2_MIDDLE3_AWB2_B_AVG1_R);
        sum->white_ratio = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R3), DSP2_MIDDLE3_AWB2_WHITE_RATIO1_R);

        tmpVal64 = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R6);
        tmpVal = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R5), DSP2_MIDDLE3_AWB2_WHITER_SUML1_R);
        sum->white_r_sum = (tmpVal64 << 9) + tmpVal;

        tmpVal64 = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R9);
        tmpVal = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_R8), DSP2_MIDDLE3_AWB2_WHITEG_SUML1_R);
        sum->white_g_sum = (tmpVal64 << 9) + tmpVal;

        tmpVal64 = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_RC);
        tmpVal = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_RB), DSP2_MIDDLE3_AWB2_WHITEB_SUML1_R);
        sum->white_b_sum = (tmpVal64 << 9) + tmpVal;
    }

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_INT);
    w_cnt_idx_end = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_W_CNT_R);

    // TODO: chang the algo
    if (w_cnt_idx_start != w_cnt_idx_end) {
#if DSP2_PRINT_LOG
        MSG("w_cnt_idx_start %d, w_cnt_idx_end %d \r\n", w_cnt_idx_start, w_cnt_idx_end);
        MSG("AWB2 statistics overwrite!\n");
#endif
        return -1;
    }

    return 0;
}

void DSP2_Set_AWB2_Gain(const DSP2_RGB_Gain_Type *rgb_gain)
{
    DSP2_Set_AWB_Gain(rgb_gain);
    // uint32_t tmpVal;

    // tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN1);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_RGAIN_PRE, rgb_gain->r_gain);
    // BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN1, tmpVal);

    // tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN2);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_GGAIN_PRE, rgb_gain->g_gain);
    // tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_BGAIN_PRE, rgb_gain->b_gain);
    // BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN2, tmpVal);
}

void DSP2_Get_AWB2_Gain(DSP2_RGB_Gain_Type *rgb_gain)
{
    DSP2_Get_AWB_Gain(rgb_gain);
    // uint32_t tmpVal;

    // tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN1);
    // rgb_gain->r_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_RGAIN_PRE);

    // tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN2);
    // rgb_gain->g_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_GGAIN_PRE);
    // rgb_gain->b_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_BGAIN_PRE);
}

void DSP2_Set_AWB2_Stats_Conf(const dsp2_awb2_stats_conf_t *awb_stats_conf)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(awb_stats_conf->stat_x_min, DSP2_AWB_ROI_START_X_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->stat_x_max, DSP2_AWB_ROI_START_X_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->stat_y_min, DSP2_AWB_ROI_START_Y_RANGE_MAX);
    CHECK_PARAM_MAX(awb_stats_conf->stat_y_max, DSP2_AWB_ROI_START_Y_RANGE_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_XAXIS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_X_MIN_PRE, awb_stats_conf->stat_x_min);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_X_MAX_PRE, awb_stats_conf->stat_x_max);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_XAXIS, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_YAXIS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_Y_MIN_PRE, awb_stats_conf->stat_y_min);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_Y_MAX_PRE, awb_stats_conf->stat_y_max);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_YAXIS, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_PIXEL_NUM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_PIXEL_NUM_PRE, awb_stats_conf->stat_pixel_num);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_PIXEL_NUM, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_STAT_GGAIN_PRE, awb_stats_conf->stat_g_gain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_STAT_RGAIN_PRE, awb_stats_conf->stat_r_gain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_STAT_BGAIN_PRE, awb_stats_conf->stat_b_gain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_VGAIN_PRE, awb_stats_conf->stat_v_gain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_UGAIN_PRE, awb_stats_conf->stat_u_gain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_GAIN3, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YTH1_PRE, awb_stats_conf->y_th[1]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YTH2_PRE, awb_stats_conf->y_th[2]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YTH3_PRE, awb_stats_conf->y_th[3]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YTH4_PRE, awb_stats_conf->y_th[4]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YTH0_PRE, awb_stats_conf->y_th[0]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YWEIGHT2_PRE, awb_stats_conf->y_weight[2]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YWEIGHT3_PRE, awb_stats_conf->y_weight[3]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YWEIGHT4_PRE, awb_stats_conf->y_weight[4]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YWEIGHT0_PRE, awb_stats_conf->y_weight[0]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_YWEIGHT1_PRE, awb_stats_conf->y_weight[1]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_YSLOPE4_PRE, awb_stats_conf->y_slope[4]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L3);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_YSLOPE3_PRE, awb_stats_conf->y_slope[3]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_YSLOPE2_PRE, awb_stats_conf->y_slope[2]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L3, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L4);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_YSLOPE1_PRE, awb_stats_conf->y_slope[1]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_YSLOPE0_PRE, awb_stats_conf->y_slope[0]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_L4, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C0);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG4_PRE, awb_stats_conf->u[4]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG5_PRE, awb_stats_conf->u[5]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG6_PRE, awb_stats_conf->u[6]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG7_PRE, awb_stats_conf->u[7]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C1);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG0_PRE, awb_stats_conf->u[0]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG1_PRE, awb_stats_conf->u[1]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG2_PRE, awb_stats_conf->u[2]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG3_PRE, awb_stats_conf->u[3]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C2);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_VREG4_PRE, awb_stats_conf->v[4]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_VREG5_PRE, awb_stats_conf->v[5]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_VREG6_PRE, awb_stats_conf->v[6]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_VREG7_PRE, awb_stats_conf->v[7]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C3);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG0_PRE, awb_stats_conf->v[0]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG1_PRE, awb_stats_conf->v[1]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG2_PRE, awb_stats_conf->v[2]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE3_AWB2_UREG3_PRE, awb_stats_conf->v[3]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C3, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH4_PRE, awb_stats_conf->c_th[4]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH5_PRE, awb_stats_conf->c_th[5]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH6_PRE, awb_stats_conf->c_th[6]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH7_PRE, awb_stats_conf->c_th[7]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C4, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH0_PRE, awb_stats_conf->c_th[0]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH1_PRE, awb_stats_conf->c_th[1]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH2_PRE, awb_stats_conf->c_th[2]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CTH3_PRE, awb_stats_conf->c_th[3]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C5, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE4_PRE, awb_stats_conf->c_slope[4]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE5_PRE, awb_stats_conf->c_slope[5]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE6_PRE, awb_stats_conf->c_slope[6]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE7_PRE, awb_stats_conf->c_slope[7]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C6, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE0_PRE, awb_stats_conf->c_slope[0]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE1_PRE, awb_stats_conf->c_slope[1]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE2_PRE, awb_stats_conf->c_slope[2]);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE3_AWB2_CSLOPE3_PRE, awb_stats_conf->c_slope[3]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE3_AWB2_STA_C7, tmpVal);
}

void DSP2_Set_RB_Gain(const DSP2_RB_Gain_Type *rb_gain)
{
    DSP2_RGB_Gain_Type rgb_gain;

    rgb_gain.r_gain = rb_gain->r_gain;
    rgb_gain.g_gain = 4096;
    rgb_gain.b_gain = rb_gain->b_gain;

    DSP2_Set_AWB_Gain(&rgb_gain);
}

int DSP2_Set_BLC(const DSP2_CLAMP_S *clamp)
{
    dsp2_front_reg_t *dsp2_front_reg = (dsp2_front_reg_t *)DSP2_BASE;

    CHECK_PARAM_RANGE(clamp->clamp_r, DSP2_BLC_MIN, DSP2_BLC_MAX);
    CHECK_PARAM_RANGE(clamp->clamp_gr, DSP2_BLC_MIN, DSP2_BLC_MAX);
    CHECK_PARAM_RANGE(clamp->clamp_gb, DSP2_BLC_MIN, DSP2_BLC_MAX);
    CHECK_PARAM_RANGE(clamp->clamp_b, DSP2_BLC_MIN, DSP2_BLC_MAX);

    dsp2_front_reg->clamp_R_Gr.BF.clp_R_pre = clamp->clamp_r;
    dsp2_front_reg->clamp_R_Gr.BF.clp_Gr_pre = clamp->clamp_gr;
    dsp2_front_reg->clamp_B_Gb.BF.clp_Gb_pre = clamp->clamp_gb;
    dsp2_front_reg->clamp_B_Gb.BF.clp_B_pre = clamp->clamp_b;

    dsp2_front_reg->gain_R_G.BF.rgain1_pre = 128;
    dsp2_front_reg->gain_R_G.BF.ggain1_pre = 128;
    dsp2_front_reg->gain_B.BF.bgain1_pre = 128;

    /* compensate back the lost dynamic range for bayer image */
    dsp2_front_reg->clp_rgr_gain.BF.clp_gain_en_pre = 1;
    dsp2_front_reg->clp_rgr_gain.BF.clp_r_gain_pre = DSP2_Calc_Clamp_Gain(clamp->clamp_r);
    dsp2_front_reg->clp_rgr_gain.BF.clp_gr_gain_pre = DSP2_Calc_Clamp_Gain(clamp->clamp_gr);
    dsp2_front_reg->clp_bgb_gain.BF.clp_gb_gain_pre = DSP2_Calc_Clamp_Gain(clamp->clamp_gb);
    dsp2_front_reg->clp_bgb_gain.BF.clp_b_gain_pre = DSP2_Calc_Clamp_Gain(clamp->clamp_b);

    return 0;
}

int DSP2_Get_BLC(DSP2_CLAMP_S *clamp)
{
    dsp2_front_reg_t *dsp2_front_reg = (dsp2_front_reg_t *)DSP2_BASE;

    clamp->clamp_r = dsp2_front_reg->clamp_R_Gr.BF.clp_R_pre;
    clamp->clamp_gr = dsp2_front_reg->clamp_R_Gr.BF.clp_Gr_pre;
    clamp->clamp_gb = dsp2_front_reg->clamp_B_Gb.BF.clp_Gb_pre;
    clamp->clamp_b = dsp2_front_reg->clamp_B_Gb.BF.clp_B_pre;

    return 0;
}

void DSP2_Set_DPC_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_DEFECT_SETTING);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DEFECT_CORRECT_MODE_W, DSP2_DPC_FLY);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DEFECT_CORRECT_MODE_W, DSP2_DPC_OFF);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_DEFECT_SETTING, tmpVal);
}

void DSP2_Enable_DPC(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_DEFECT_SETTING);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DEFECT_CORRECT_MODE_W, DSP2_DPC_FLY);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_DEFECT_SETTING, tmpVal);
}

void DSP2_Disable_DPC(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_DEFECT_SETTING);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DEFECT_CORRECT_MODE_W, DSP2_DPC_OFF);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_DEFECT_SETTING, tmpVal);
}

int DSP2_Set_Defect_Correction_Enhance_Group(const DSP2_DPC_ENHANCE_GROUP_TYPE *value)
{
    int i;
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    for (i = 0; i < DSP2_DPC_Enhance_Num; i++) {
        if ((DISABLE != value->data[i]) && (ENABLE != value->data[i])) {
            return -1;
        }
    }

    dsp2_middle_reg->defect_setting.BF.resolution_enhance1_w = value->data[DSP2_DPC_Enhance1];
    dsp2_middle_reg->defect_setting.BF.resolution_enhance2_w = value->data[DSP2_DPC_Enhance2];
    dsp2_middle_reg->defect_setting.BF.resolution_enhance3_w = value->data[DSP2_DPC_Enhance3];

    return 0;
}

int DSP2_Get_Defect_Correction_Enhance_Group(DSP2_DPC_ENHANCE_GROUP_TYPE *value)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    value->data[DSP2_DPC_Enhance1] = (BL_Fun_Type)dsp2_middle_reg->defect_setting.BF.resolution_enhance1_w;
    value->data[DSP2_DPC_Enhance2] = (BL_Fun_Type)dsp2_middle_reg->defect_setting.BF.resolution_enhance2_w;
    value->data[DSP2_DPC_Enhance3] = (BL_Fun_Type)dsp2_middle_reg->defect_setting.BF.resolution_enhance3_w;

    return 0;
}

int DSP2_Set_Defect_Correction_Threshold_Group(const DSP2_DPC_THRESHOLD_GROUP_TYPE *value)
{
    int i;
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    for (i = 0; i < DSP2_DPC_th_Num; i++) {
        CHECK_PARAM_RANGE(value->data[i], DSP2_DPC_TH_MIN, DSP2_DPC_TH_MAX);
    }

    dsp2_middle_reg->defect_th_A.BF.defect_th1_w = value->data[DSP2_DPC_th1];
    dsp2_middle_reg->defect_th_A.BF.defect_th2_w = value->data[DSP2_DPC_th2];
    dsp2_middle_reg->defect_th_A.BF.defect_th3_w = value->data[DSP2_DPC_th3];
    dsp2_middle_reg->defect_th_A.BF.defect_th4_w = value->data[DSP2_DPC_th4];
    dsp2_middle_reg->defect_th_B.BF.defect_th5_w = value->data[DSP2_DPC_th5];

    return 0;
}

int DSP2_Get_Defect_Correction_Threshold_Group(DSP2_DPC_THRESHOLD_GROUP_TYPE *value)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    value->data[DSP2_DPC_th1] = dsp2_middle_reg->defect_th_A.BF.defect_th1_w;
    value->data[DSP2_DPC_th2] = dsp2_middle_reg->defect_th_A.BF.defect_th2_w;
    value->data[DSP2_DPC_th3] = dsp2_middle_reg->defect_th_A.BF.defect_th3_w;
    value->data[DSP2_DPC_th4] = dsp2_middle_reg->defect_th_A.BF.defect_th4_w;
    value->data[DSP2_DPC_th5] = dsp2_middle_reg->defect_th_B.BF.defect_th5_w;

    return 0;
}

void DSP2_Set_BNR_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE4_BNR_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE4_BNR_EN_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0, tmpVal);
}

void DSP2_Get_BNR_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MIDDLE4_BNR_EN_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

/*
    Set/Get BNR Weight
    value range: 0~64
*/
void DSP2_Set_BNR_Weight(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_BNR_WEIGHT_MIN, DSP2_BNR_WEIGHT_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_BNR_WEIGHT_PRE, value);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0, tmpVal);
}

void DSP2_Get_BNR_Weight(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_BNR_WEIGHT_PRE);
}

/*
    Set/Get BNR LPF Weight
    value range: 0~16
*/
void DSP2_Set_BNR_LPF_Weight(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_BNR_LPF_WEIGHT_MIN, DSP2_BNR_LPF_WEIGHT_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_LPF_WEIGHT_PRE, value);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0, tmpVal);
}

void DSP2_Get_BNR_LPF_Weight(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_LPF_WEIGHT_PRE);
}

void DSP2_Set_BNR_Threshold(const DSP2_BNR_THRESHOLD_TYPE *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_BASE_B_PRE, value->th_base_b);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_BASE_G_PRE, value->th_base_g);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_BASE_R_PRE, value->th_base_r);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_SLOPE_B_PRE, value->th_slope_b);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_SLOPE_G_PRE, value->th_slope_g);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_SLOPE_R_PRE, value->th_slope_r);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_SLOPE_GAIN_PRE, value->slope_gain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_2, tmpVal);
}

void DSP2_Get_BNR_Threshold(DSP2_BNR_THRESHOLD_TYPE *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_0);
    value->th_base_b = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_BASE_B_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_1);
    value->th_base_g = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_BASE_G_PRE);
    value->th_base_r = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_BASE_R_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_2);
    value->th_slope_b = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_SLOPE_B_PRE);
    value->th_slope_g = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_SLOPE_G_PRE);
    value->th_slope_r = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_TH_SLOPE_R_PRE);
    value->slope_gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_SLOPE_GAIN_PRE);
}

void DSP2_Set_BNR_Fallback(const DSP2_BNR_FALLBACK_TYPE *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_FB_LEVEL_PRE, value->fb_level);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE, value->fb_lpf_weight);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_3, tmpVal);
}

void DSP2_Get_BNR_Fallback(DSP2_BNR_FALLBACK_TYPE *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE4_BNR_CONFIG_3);
    value->fb_lpf_weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_FB_LPF_WEIGHT_PRE);
    value->fb_level = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE4_FB_LEVEL_PRE);
}

void DSP2_Set_LSC_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_LSC_ON_W);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE_LSC_ON_W);
    }

    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING, tmpVal);
}

void DSP2_Enable_LSC(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_MIDDLE_LSC_ON_W);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING, tmpVal);
}

void DSP2_Disable_LSC(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_MIDDLE_LSC_ON_W);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING, tmpVal);
}

void DSP2_Get_LSC_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_SETTING);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_MIDDLE_LSC_ON_W)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

/*
    xoffset and yoffset caculated by active and out window
 */
int DSP2_Set_LSC_Offset(int xoffset, int yoffset)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    CHECK_PARAM_RANGE(xoffset, DSP2_LSC_OFFSET_MIN, DSP2_LSC_OFFSET_MAX);
    CHECK_PARAM_RANGE(yoffset, DSP2_LSC_OFFSET_MIN, DSP2_LSC_OFFSET_MAX);

    dsp2_middle_reg->LSC_setting.BF.X_offset_w = xoffset;
    dsp2_middle_reg->LSC_setting.BF.Y_offset_w = yoffset;

    return 0;
}

int DSP2_Set_LSC_Coeff(const DSP2_LSC_COEF_S *lsc)
{
    uint32_t tmpVal;

    if (!is_LSC_Coeff_Valid(lsc)) {
        return -1;
    }

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_A);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_R_ACOEFF_W, lsc->lsc_coef_r.coef[LSC_COEF_A]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_A, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_BE);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_R_BCOEFF_W, lsc->lsc_coef_r.coef[LSC_COEF_B]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_R_ECOEFF_W, lsc->lsc_coef_r.coef[LSC_COEF_E]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_BE, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_CD);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_R_CCOEFF_W, lsc->lsc_coef_r.coef[LSC_COEF_C]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_R_DCOEFF_W, lsc->lsc_coef_r.coef[LSC_COEF_D]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_CD, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_G);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_R_GCOEFF_W, lsc->lsc_coef_r.coef[LSC_COEF_G]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_G, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_A);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_G_ACOEFF_W, lsc->lsc_coef_g.coef[LSC_COEF_A]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_A, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_BE);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_G_BCOEFF_W, lsc->lsc_coef_g.coef[LSC_COEF_B]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_G_ECOEFF_W, lsc->lsc_coef_g.coef[LSC_COEF_E]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_BE, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_CD);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_G_CCOEFF_W, lsc->lsc_coef_g.coef[LSC_COEF_C]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_G_DCOEFF_W, lsc->lsc_coef_g.coef[LSC_COEF_D]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_CD, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_G);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_G_GCOEFF_W, lsc->lsc_coef_g.coef[LSC_COEF_G]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_G, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_A);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_B_ACOEFF_W, lsc->lsc_coef_b.coef[LSC_COEF_A]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_A, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_BE);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_B_BCOEFF_W, lsc->lsc_coef_b.coef[LSC_COEF_B]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_B_ECOEFF_W, lsc->lsc_coef_b.coef[LSC_COEF_E]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_BE, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_CD);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_B_CCOEFF_W, lsc->lsc_coef_b.coef[LSC_COEF_C]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_B_DCOEFF_W, lsc->lsc_coef_b.coef[LSC_COEF_D]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_CD, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_G);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_MIDDLE_B_GCOEFF_W, lsc->lsc_coef_b.coef[LSC_COEF_G]);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_G, tmpVal);

    return 0;
}

int DSP2_Get_LSC_Coeff(DSP2_LSC_COEF_S *lsc)
{
    uint32_t tmpVal;

    /* channel R */
    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_A);
    lsc->lsc_coef_r.coef[LSC_COEF_A] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_R_ACOEFF_W), 23);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_BE);
    lsc->lsc_coef_r.coef[LSC_COEF_B] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_R_BCOEFF_W), 13);
    lsc->lsc_coef_r.coef[LSC_COEF_E] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_R_ECOEFF_W), 13);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_CD);
    lsc->lsc_coef_r.coef[LSC_COEF_C] = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_R_CCOEFF_W);
    lsc->lsc_coef_r.coef[LSC_COEF_D] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_R_DCOEFF_W), 23);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_R_G);
    lsc->lsc_coef_r.coef[LSC_COEF_G] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_R_GCOEFF_W), 23);

    /* channel G */
    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_A);
    lsc->lsc_coef_g.coef[LSC_COEF_A] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_G_ACOEFF_W), 23);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_BE);
    lsc->lsc_coef_g.coef[LSC_COEF_B] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_G_BCOEFF_W), 13);
    lsc->lsc_coef_g.coef[LSC_COEF_E] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_G_ECOEFF_W), 13);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_CD);
    lsc->lsc_coef_g.coef[LSC_COEF_C] = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_G_CCOEFF_W);
    lsc->lsc_coef_g.coef[LSC_COEF_D] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_G_DCOEFF_W), 23);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_G_G);
    lsc->lsc_coef_g.coef[LSC_COEF_G] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_G_GCOEFF_W), 23);

    /* channel B */
    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_A);
    lsc->lsc_coef_b.coef[LSC_COEF_A] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_B_ACOEFF_W), 23);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_BE);
    lsc->lsc_coef_b.coef[LSC_COEF_B] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_B_BCOEFF_W), 13);
    lsc->lsc_coef_b.coef[LSC_COEF_E] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_B_ECOEFF_W), 13);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_CD);
    lsc->lsc_coef_b.coef[LSC_COEF_C] = BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_B_CCOEFF_W);
    lsc->lsc_coef_b.coef[LSC_COEF_D] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_B_DCOEFF_W), 23);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_LSC_COEFF_B_G);
    lsc->lsc_coef_b.coef[LSC_COEF_G] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_B_GCOEFF_W), 23);

    return 0;
}

int DSP2_Set_LSC_Max(const DSP2_LSC_MAX_S *lsc_max)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    CHECK_PARAM_RANGE(lsc_max->max_r, DSP2_LSC_MAX_MIN, DSP2_LSC_MAX_MAX);
    CHECK_PARAM_RANGE(lsc_max->max_g, DSP2_LSC_MAX_MIN, DSP2_LSC_MAX_MAX);
    CHECK_PARAM_RANGE(lsc_max->max_b, DSP2_LSC_MAX_MIN, DSP2_LSC_MAX_MAX);

    dsp2_middle_reg->MAX_R_G.BF.MAXR_w = lsc_max->max_r;
    dsp2_middle_reg->MAX_R_G.BF.MAXG_w = lsc_max->max_g;
    dsp2_middle_reg->MAX_B.BF.MAXB_w = lsc_max->max_b;

    return 0;
}

int DSP2_Get_LSC_Max(DSP2_LSC_MAX_S *lsc_max)
{
    dsp2_middle_reg_t *dsp2_middle_reg = (dsp2_middle_reg_t *)DSP2_BASE;

    lsc_max->max_r = dsp2_middle_reg->MAX_R_G.BF.MAXR_w;
    lsc_max->max_g = dsp2_middle_reg->MAX_R_G.BF.MAXG_w;
    lsc_max->max_b = dsp2_middle_reg->MAX_B.BF.MAXB_w;

    return 0;
}

void DSP2_Set_Digital_Gain(uint16_t dgain)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_DIGITAL_RGR_GAIN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DIGITAL_GR_GAIN_PRE, dgain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DIGITAL_R_GAIN_PRE, dgain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_DIGITAL_RGR_GAIN, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_MIDDLE_DIGITAL_BGB_GAIN);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DIGITAL_GB_GAIN_PRE, dgain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_MIDDLE_DIGITAL_B_GAIN_PRE, dgain);
    BL_WR_REG(DSP2_BASE, DSP2_MIDDLE_DIGITAL_BGB_GAIN, tmpVal);
}

void DSP2_Set_CCM_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_OFFSET_0);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_CC_ENABLE_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_CC_ENABLE_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_OFFSET_0, tmpVal);
}

void DSP2_Get_CCM_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_OFFSET_0);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_BLBACK_CC_ENABLE_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_Set_CCM_Coef(const DSP2_CCM_COEF_S *ccm)
{
    int i;
    uint32_t tmpVal;

    for (i = 0; i < CCM_COEF_NUM; i++) {
        CHECK_PARAM_RANGE(ccm->ccm_coef[i], DSP2_CCM_MIN, DSP2_CCM_MAX);
    }

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_0);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX00_PRE, ccm->ccm_coef[DSP2_CCM_11]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX01_PRE, ccm->ccm_coef[DSP2_CCM_12]);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_1);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX02_PRE, ccm->ccm_coef[DSP2_CCM_13]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX10_PRE, ccm->ccm_coef[DSP2_CCM_21]);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_2);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX11_PRE, ccm->ccm_coef[DSP2_CCM_22]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX12_PRE, ccm->ccm_coef[DSP2_CCM_23]);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_3);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX20_PRE, ccm->ccm_coef[DSP2_CCM_31]);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX21_PRE, ccm->ccm_coef[DSP2_CCM_32]);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_3, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_CE_MATRIX);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CC_MATRIX22_PRE, ccm->ccm_coef[DSP2_CCM_33]);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_CE_MATRIX, tmpVal);
}

void DSP2_Get_CCM_Coef(DSP2_CCM_COEF_S *ccm)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_0);
    ccm->ccm_coef[DSP2_CCM_11] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX00_PRE), DSP2_BLBACK_CC_MATRIX00_PRE_LEN);
    ccm->ccm_coef[DSP2_CCM_12] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX01_PRE), DSP2_BLBACK_CC_MATRIX01_PRE_LEN);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_1);
    ccm->ccm_coef[DSP2_CCM_13] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX02_PRE), DSP2_BLBACK_CC_MATRIX02_PRE_LEN);
    ccm->ccm_coef[DSP2_CCM_21] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX10_PRE), DSP2_BLBACK_CC_MATRIX10_PRE_LEN);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_2);
    ccm->ccm_coef[DSP2_CCM_22] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX11_PRE), DSP2_BLBACK_CC_MATRIX11_PRE_LEN);
    ccm->ccm_coef[DSP2_CCM_23] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX12_PRE), DSP2_BLBACK_CC_MATRIX12_PRE_LEN);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_MATRIX_3);
    ccm->ccm_coef[DSP2_CCM_31] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX20_PRE), DSP2_BLBACK_CC_MATRIX20_PRE_LEN);
    ccm->ccm_coef[DSP2_CCM_32] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX21_PRE), DSP2_BLBACK_CC_MATRIX21_PRE_LEN);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_CE_MATRIX);
    ccm->ccm_coef[DSP2_CCM_33] = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CC_MATRIX22_PRE), DSP2_BLBACK_CC_MATRIX22_PRE_LEN);
}

void DSP2_Set_Gamma_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_GAMMA_A);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_BL_GAMMA_EN_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_BL_GAMMA_EN_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_GAMMA_A, tmpVal);
}

void DSP2_Get_Gamma_State(BL_Fun_Type *state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_GAMMA_A);

    if (BL_IS_REG_BIT_SET(tmpVal, DSP2_BLBACK_BL_GAMMA_EN_PRE)) {
        *state = ENABLE;
    } else {
        *state = DISABLE;
    }
}

void DSP2_Set_Gamma_Coef(const DSP2_Gamma_Curve_Type *gamma_curve)
{
    ARCH_MemCpy4((uint32_t *)(DSP2_BASE + DSP2_BLBACK_BL_GAMMA_TABLE_1_OFFSET), (uint32_t *)&gamma_curve->curve_coef[0],
                 GAMMA_COEF_NUM / 2);
}

void DSP2_Get_Gamma_Coef(DSP2_Gamma_Curve_Type *gamma_curve)
{
    ARCH_MemCpy4((uint32_t *)&gamma_curve->curve_coef[0], (uint32_t *)(DSP2_BASE + DSP2_BLBACK_BL_GAMMA_TABLE_1_OFFSET),
                 GAMMA_COEF_NUM / 2);
}

/*
    should not change, yuv range should change in yuv adjust module
*/
void DSP2_Init_Color_Enhancement()
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_0);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX00_PRE, 0x99);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX01_PRE, 0x12D);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CC_CE_MATRIX);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX02_PRE, 0x3A);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CC_CE_MATRIX, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_1);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX10_PRE, 0xFA9);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX11_PRE, 0xF57);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_2);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX12_PRE, 0x100);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX20_PRE, 0x100);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_3);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX21_PRE, 0xF29);
    tmpVal = BL_SET_REG_BITS_VAL_2(tmpVal, DSP2_BLBACK_CE_MATRIX22_PRE, 0xFD7);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CE_MATRIX_3, tmpVal);
}

void DSP2_Set_YUV_Conv_Mode(DSP2_YUV_CONV_TYPE type)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_DSP2_YUV_CONV_TYPE(type));

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CONV_MODE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CONV_MODE_W, type);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CONV_MODE, tmpVal);
}

void DSP2_Get_YUV_Conv_Mode(DSP2_YUV_CONV_TYPE *type)
{
    *type = BL_GET_REG_BITS_VAL(BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CONV_MODE), DSP2_BLBACK_CONV_MODE_W);
}

void DSP2_Set_Brightness(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_BRIGHTNESS_MIN, DSP2_BRIGHTNESS_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_YBRIGHTNESS_W, value);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A, tmpVal);
}

void DSP2_Get_Brightness(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A);
    *value = SIGN_EXTEND(BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_YBRIGHTNESS_W), DSP2_BLBACK_YBRIGHTNESS_W_LEN);
}

void DSP2_Set_Contrast(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_CONTRAST_MIN, DSP2_CONTRAST_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_YCONTRAST_W, value);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A, tmpVal);
}

void DSP2_Get_Contrast(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_YCONTRAST_W);
}

void DSP2_Set_Saturation(const DSP2_SATURATION_S *saturation)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(saturation->saturation_cb, DSP2_SATURATION_MAX);
    CHECK_PARAM_MAX(saturation->saturation_cr, DSP2_SATURATION_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CBSATURATION_PRE, saturation->saturation_cb);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CRSATURATION_PRE, saturation->saturation_cr);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A, tmpVal);
}

void DSP2_Get_Saturation(DSP2_SATURATION_S *saturation)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_YUVC_A);
    saturation->saturation_cb = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CBSATURATION_PRE);
    saturation->saturation_cr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CRSATURATION_PRE);
}

void DSP2_Set_Noise_Level(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_NOISE_LEVEL_MIN, DSP2_NOISE_LEVEL_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_NOISE_LEVEL_PRE, value);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_DNR_A, tmpVal);
}

void DSP2_Get_Noise_Level(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_A);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_NOISE_LEVEL_PRE);
}

void DSP2_Set_2D_NR(int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_NR_STRENGTH_MIN, DSP2_NR_STRENGTH_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_FILT_STRENGTH_2D_PRE, value);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_DNR_A, tmpVal);
}

void DSP2_Get_2D_NR(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_A);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_FILT_STRENGTH_2D_PRE);
}

void DSP2_Set_3D_NR(const int value)
{
    uint32_t tmpVal;

    CHECK_PARAM_RANGE(value, DSP2_NR_STRENGTH_MIN, DSP2_NR_STRENGTH_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_A);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_FILT_STRENGTH_3D_PRE, value);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_DNR_A, tmpVal);
}

void DSP2_Get_3D_NR(int *value)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_DNR_A);
    *value = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_FILT_STRENGTH_3D_PRE);
}

void DSP2_Set_EE_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_EE_EB_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_EE_EB_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0, tmpVal);
}

void DSP2_Enable_EE(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_EE_EB_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0, tmpVal);
}

void DSP2_Disable_EE(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_EE_EB_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0, tmpVal);
}

void DSP2_EnableEEOverShoot(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_OVRSHT_EB_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0, tmpVal);
}

void DSP2_DisableEEOverShoot(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_OVRSHT_EB_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0, tmpVal);
}

void DSP2_Set_EE_Thresh(const DSP2_EE_Thresh_Type *threshCfg)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(threshCfg->dirShpnessThresh, DSP2_EE_DIR_SHPNSS_THRESH_MAX);
    CHECK_PARAM_MAX(threshCfg->noDirShpnessThresh, DSP2_EE_NO_DIR_SHPNSS_THRESH_MAX);
    CHECK_PARAM_RANGE(threshCfg->textureThresh, (threshCfg->flatThresh + 1), DSP2_EE_TEXTURE_REGION_THRESH_MAX);
    CHECK_PARAM_MIN(threshCfg->edgeThresh, (threshCfg->textureThresh + 1));

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_TXT_THR_PRE, threshCfg->textureThresh);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_THRESH1_PRE, threshCfg->dirShpnessThresh);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_THRESH2_PRE, threshCfg->noDirShpnessThresh);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_FLAT_THR_PRE, threshCfg->flatThresh);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_1, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_3);
    ;
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_EDGE_THR_PRE, threshCfg->edgeThresh);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_3, tmpVal);
}

void DSP2_Get_EE_Thresh(DSP2_EE_Thresh_Type *threshCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_0);
    threshCfg->textureThresh = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_TXT_THR_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_1);
    threshCfg->dirShpnessThresh = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_THRESH1_PRE);
    threshCfg->noDirShpnessThresh = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_THRESH2_PRE);
    threshCfg->flatThresh = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_FLAT_THR_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_3);
    threshCfg->edgeThresh = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_EDGE_THR_PRE);
}

void DSP2_Set_EE_Strength(const DSP2_EE_Str_Type *strCfg)
{
    uint32_t tmpVal;

    CHECK_PARAM_MAX(strCfg->posEdgeOvrshtStr, DSP2_EE_STRENGTH_MAX);
    CHECK_PARAM_MAX(strCfg->negEdgeOvrshtStr, DSP2_EE_STRENGTH_MAX);
    CHECK_PARAM_MAX(strCfg->posEdgeStr, DSP2_EE_STRENGTH_MAX);
    CHECK_PARAM_MAX(strCfg->negEdgeStr, DSP2_EE_STRENGTH_MAX);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_OVRSHT_POS_PRE, strCfg->posEdgeOvrshtStr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_OVRSHT_NEG_PRE, strCfg->negEdgeOvrshtStr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_POSEE_STR_PRE, strCfg->posEdgeStr);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_NEGEE_STR_PRE, strCfg->negEdgeStr);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_2, tmpVal);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_3);
    ;
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_NR_STR_PRE, strCfg->nrStr);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_BLEE_3, tmpVal);
}

void DSP2_Get_EE_Strength(DSP2_EE_Str_Type *strCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_2);
    strCfg->posEdgeOvrshtStr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_OVRSHT_POS_PRE);
    strCfg->negEdgeOvrshtStr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_OVRSHT_NEG_PRE);
    strCfg->posEdgeStr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_POSEE_STR_PRE);
    strCfg->negEdgeStr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_NEGEE_STR_PRE);

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_BLEE_3);
    ;
    strCfg->nrStr = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_NR_STR_PRE);
}

void DSP2_Set_EE_LumaWeight(const DSP2_EE_Luma_Weight_Type *lumaWgtCfg)
{
    int i;
    uint32_t tmpVal;
    uint32_t tmpAddr = DSP2_BASE + DSP2_BLBACK_BLEE_4_OFFSET;

    for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i += 2, tmpAddr += 4) {
        CHECK_PARAM_MAX(lumaWgtCfg->lumaWgtTbl[i], DSP2_EE_LUMA_WEIGHT_MAX);
        CHECK_PARAM_MAX(lumaWgtCfg->lumaWgtTbl[i + 1], DSP2_EE_LUMA_WEIGHT_MAX);
        tmpVal = BL_RD_WORD(tmpAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_LUMA_WGT0_PRE, lumaWgtCfg->lumaWgtTbl[i]);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_LUMA_WGT1_PRE, lumaWgtCfg->lumaWgtTbl[i + 1]);
        BL_WR_WORD(tmpAddr, tmpVal);
    }
}

void DSP2_Get_EE_LumaWeight(DSP2_EE_Luma_Weight_Type *lumaWgtCfg)
{
    int i;
    uint32_t tmpVal;
    uint32_t tmpAddr = DSP2_BASE + DSP2_BLBACK_BLEE_4_OFFSET;

    for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i += 2, tmpAddr += 4) {
        tmpVal = BL_RD_WORD(tmpAddr);
        lumaWgtCfg->lumaWgtTbl[i] = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_LUMA_WGT0_PRE);
        lumaWgtCfg->lumaWgtTbl[i + 1] = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_LUMA_WGT1_PRE);
    }
}

void DSP2_Set_ChromaSuppress_State(BL_Fun_Type state)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CS2);

    if (ENABLE == state) {
        tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_CS2_ENABLE_PRE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_CS2_ENABLE_PRE);
    }

    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CS2, tmpVal);
}

void DSP2_Enable_ChromaSuppress(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CS2);
    tmpVal = BL_SET_REG_BIT(tmpVal, DSP2_BLBACK_CS2_ENABLE_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CS2, tmpVal);
}

void DSP2_Disable_ChromaSuppress(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CS2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, DSP2_BLBACK_CS2_ENABLE_PRE);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CS2, tmpVal);
}

void DSP2_Set_ChromaSuppress(const DSP2_Chroma_Suppress_Type *chromaSupprCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CS2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CS2_GAIN_PRE, chromaSupprCfg->gain);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CS2_WEIGHT_PRE, chromaSupprCfg->weight);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CS2_GREY_TH_PRE, chromaSupprCfg->gain_thresh);
    BL_WR_REG(DSP2_BASE, DSP2_BLBACK_CS2, tmpVal);
}

void DSP2_Get_ChromaSuppress(DSP2_Chroma_Suppress_Type *chromaSupprCfg)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(DSP2_BASE, DSP2_BLBACK_CS2);
    chromaSupprCfg->gain = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CS2_GAIN_PRE);
    chromaSupprCfg->weight = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CS2_WEIGHT_PRE);
    chromaSupprCfg->gain_thresh = BL_GET_REG_BITS_VAL(tmpVal, DSP2_BLBACK_CS2_GREY_TH_PRE);
}

/*@} end of group DSP2_Public_Functions */

/*@} end of group DSP2 */

/*@} end of group BL808_Peripheral_Driver */
