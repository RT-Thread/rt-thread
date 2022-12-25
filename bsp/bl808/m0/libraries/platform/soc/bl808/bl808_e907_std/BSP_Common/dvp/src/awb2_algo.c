#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "awb2_algo.h"
#include "bl_img_utils.h"
#include "img_param.h"
#include "bl808_dsp2.h"

static void iir_filter(int32_t* iir, int32_t curr, int32_t* result);


/***********OPTIMIZE LATER***********/
#define PIXEL_BW  12
#define PIXEL_MAX  (1 << PIXEL_BW) - 1
#define STAT_PIXEL_BW  8
#define STAT_PIXEL_MAX  (1 << STAT_PIXEL_BW) - 1
#define GAIN_PRECISION  PIXEL_BW
#define GAIN_UNITY  1 << GAIN_PRECISION
#define C_GAIN_PRECISION  8
#define C_GAIN_UNITY  1 << C_GAIN_PRECISION
#define SLOPE_PRECISION  2
#define WEIGHT_PRECISION  8
#define WEIGHT_MAX  1 << WEIGHT_PRECISION
#define Y_NUM  5
#define C_NUM  8
#define RATIO_PRECISION  14

#define DEFAULT_WEIGHT_PRECISION  5
#define COMPENSATE_RATIO_PRECISION  5
#define SOFT_CLIP_SLOPE_PRECISION  5
#define ALPHA_STAT_PRECISION  5
#define ALPHA_STAT_MAX  1 << ALPHA_STAT_PRECISION
#define ALPHA_STAT_SLOPE_PRECISION  5
#define TEMPORAL_SMOOTH_PRECISION  5
#define TEMPORAL_IIR_EXTRA_PRECISION  4

#define COLOR_TEMP_NUM  7
#define H  0
#define A  1
#define TL84  2
#define CWF  3
#define D50  4
#define D65  5
#define D75  6
#define SPARE  7

// static const int32_t wb_gain_map[COLOR_TEMP_NUM][3] = {
//   {3519, 9345, 2300}, // H - 2300K
//   {4031, 8274, 2856}, // A - 2856K
//   {5026, 7799, 4000}, // TL84 - 4000K
//   {5548, 7822, 4150}, // CWF - 4150K
//   {5678, 6409, 5000}, // D50 - 5000K
//   {6397, 5712, 6500}, // D65 - 6500K
//   {6764, 5366, 7500}  // D75 - 7500K
// };

struct __awb2_ctx_t{
    awb_info_t        awb_info;
    uint32_t          awb_configed;
    uint32_t          awb_config_update;
    AWB_MODE          new_awb_mode;
    BL_COLOR_TEMP     new_color_temp;
    int               awb_start_skip_num;
};

static struct __awb2_ctx_t awb2_ctx;

/************************************/

struct Reg
{
  int32_t stat_x_min; // r/w, shadow, 11'b, range: 0 ~ (width - 1)
  int32_t stat_x_max; // r/w, shadow, 11'b, range: 0 ~ (width - 1)
  int32_t stat_y_min; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
  int32_t stat_y_max; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
  int32_t stat_pixel_num; // r/w, shadow, 21'b, = (stat_x_max - stat_x_min + 1) * (stat_y_max - stat_y_min + 1)
  int32_t stat_r_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
  int32_t stat_g_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
  int32_t stat_b_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
  int32_t stat_u_gain; // r/w, shadow, 10'b, = 2 + C_GAIN_PRECISION, 2.8 fixed-point, range: 0 ~ (2 ^ 10 - 1)
  int32_t stat_v_gain; // r/w, shadow, 10'b, = 2 + C_GAIN_PRECISION, 2.8 fixed-point, range: 0 ~ (2 ^ 10 - 1)
  int32_t y_th[Y_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, range: 0 ~ (2 ^ 8 - 1)
  int32_t y_weight[Y_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, range: 0 ~ (2 ^ 8 - 1)
  int32_t y_slope[Y_NUM]; // r/w, shadow, 9'b, = 7 + SLOPE_PRECISION, signed 2's complement, range: -256 ~ +255
  int32_t u[C_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, signed 2's complement, range: -128 ~ +127
  int32_t v[C_NUM]; // r/w, shadow, 8'b, = STAT_PIXEL_BW, signed 2's complement, range: -128 ~ +127
  int32_t c_th[C_NUM]; // r/w, shadow, 6'b, = STAT_PIXEL_BW - 2, range: 0 ~ (2 ^ 6 - 1)
  int32_t c_slope[C_NUM]; // r/w, shadow, 8'b, = 6 + SLOPE_PRECISION, range: 0 ~ (2 ^ 8 - 1)
  int32_t r_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
  int32_t g_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)
  int32_t b_gain; // r/w, shadow, 16'b, = 4 + GAIN_PRECISION, 4.12 fixed-point, range: 0 ~ (2 ^ 16 - 1)

  int32_t r_avg; // r, ping-pong, 12'b, = PIXEL_BW
  int32_t g_avg; // r, ping-pong, 12'b, = PIXEL_BW
  int32_t b_avg; // r, ping-pong, 12'b, = PIXEL_BW
  int64_t white_r_sum; // r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW
  int64_t white_g_sum; // r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW
  int64_t white_b_sum; // r, ping-pong, 41'b, = max. width * height in bit + WEIGHT_PRECISION + PIXEL_BW
  int32_t white_ratio; // r, ping-pong, 15'b, = 1 + RATIO_PRECISION, 1.14 fixed-point
};

struct Fw_param
{
  int32_t default_d65_weight; // 0 ~ (2 ^ DEFAULT_WEIGHT_PRECISION)
  int32_t compensate_en;
  int32_t compensate_ratio;
  int32_t compensate_max;
  int32_t soft_clip_en;
  int32_t soft_clip_r_min;
  int32_t soft_clip_r_max;
  int32_t soft_clip_b_min;
  int32_t soft_clip_b_max;
  int32_t soft_clip_slope; // 0 ~ (2 ^ SOFT_CLIP_SLOPE_PRECISION)
  int32_t alpha_stat_slope;
  int32_t bias_en;
  int32_t bias_r_gain;
  int32_t bias_b_gain;
  int32_t temporal_smooth; // 0 ~ ((2 ^ TEMPORAL_SMOOTH_PRECISION) - 1)
};


static struct Reg reg;
static struct Reg fw_curr;
static struct Reg fw_iir;

static struct Fw_param fw_param;
static dsp2_awb2_sum_t awb2_sum;

static int32_t width = 1920;
static int32_t height = 1080;

static int32_t r_gain_default;
static int32_t b_gain_default;


static int awb2_get_info(awb_info_t **info)
{
    *info = &(awb2_ctx.awb_info);
    return 0;
}

static void awb2_hw_init(dsp2_awb2_stats_conf_t *awb_stats_conf)
{
    awb_stats_conf->stat_x_min = 0;
    awb_stats_conf->stat_x_max = width - 1;
    awb_stats_conf->stat_y_min = 0;
    awb_stats_conf->stat_y_max = height - 1;
    awb_stats_conf->stat_pixel_num = \
       (awb_stats_conf->stat_y_max - awb_stats_conf->stat_y_min + 1)
      *(awb_stats_conf->stat_x_max - awb_stats_conf->stat_x_min + 1);
    awb_stats_conf->stat_u_gain = C_GAIN_UNITY;
    awb_stats_conf->stat_v_gain = C_GAIN_UNITY;
    awb_stats_conf->y_th[0] = 16;
    awb_stats_conf->y_th[1] = 64;
    awb_stats_conf->y_th[2] = 203;
    awb_stats_conf->y_th[3] = 208;
    awb_stats_conf->y_th[4] = 225;
    awb_stats_conf->y_weight[0] = 0;
    awb_stats_conf->y_weight[1] = 12;
    awb_stats_conf->y_weight[2] = 255;
    awb_stats_conf->y_weight[3] = 255;
    awb_stats_conf->y_weight[4] = 119;
    awb_stats_conf->y_slope[0] = 1;
    awb_stats_conf->y_slope[1] = 7;
    awb_stats_conf->y_slope[2] = 0;
    awb_stats_conf->y_slope[3] = -32;
    awb_stats_conf->y_slope[4] = -16;
    awb_stats_conf->u[SPARE] = 0;
    awb_stats_conf->v[SPARE] = 0;
    awb_stats_conf->c_th[H] = 14;
    awb_stats_conf->c_th[A] = 14;
    awb_stats_conf->c_th[TL84] = 16;
    awb_stats_conf->c_th[CWF] = 16;
    awb_stats_conf->c_th[D50] = 18;
    awb_stats_conf->c_th[D65] = 20;
    awb_stats_conf->c_th[D75] = 18;
    awb_stats_conf->c_th[SPARE] = 0;
    awb_stats_conf->c_slope[H] = 12;
    awb_stats_conf->c_slope[A] = 12;
    awb_stats_conf->c_slope[TL84] = 14;
    awb_stats_conf->c_slope[CWF] = 16;
    awb_stats_conf->c_slope[D50] = 24;
    awb_stats_conf->c_slope[D65] = 64;
    awb_stats_conf->c_slope[D75] = 32;
    awb_stats_conf->c_slope[SPARE] = 0;

    // calculate register from sensor calibration results

    awb_stats_conf->stat_r_gain = r_gain_default;
    awb_stats_conf->stat_g_gain = GAIN_UNITY;
    awb_stats_conf->stat_b_gain = b_gain_default;

    const wb_info_t *wb_info_L;
    //const wb_info_t *wb_info_H;
    for (int32_t ic = 0; ic < COLOR_TEMP_NUM; ic++)
    {
        img_param_get_manual_wb_info(ic, &wb_info_L);
        int32_t r_cal = MIN(STAT_PIXEL_MAX, ((awb_stats_conf->stat_r_gain << (STAT_PIXEL_BW - 1))
            + (wb_info_L->rb_gain.r_gain >> 1)) / wb_info_L->rb_gain.r_gain);
        int32_t g_cal = awb_stats_conf->stat_g_gain >> (GAIN_PRECISION - (STAT_PIXEL_BW - 1));
        int32_t b_cal = MIN(STAT_PIXEL_MAX, ((awb_stats_conf->stat_b_gain << (STAT_PIXEL_BW - 1))
            + (wb_info_L->rb_gain.b_gain >> 1)) / wb_info_L->rb_gain.b_gain);

        int32_t u_cal = round_off(-43 * r_cal - 85 * g_cal + 128 * b_cal, 8);
        int32_t v_cal = round_off(128 * r_cal - 107 * g_cal - 21 * b_cal, 8);

        awb_stats_conf->u[ic] = round_off(u_cal * awb_stats_conf->stat_u_gain, C_GAIN_PRECISION);
        awb_stats_conf->v[ic] = round_off(v_cal * awb_stats_conf->stat_v_gain, C_GAIN_PRECISION);
    }

    // avoid statistics discontinuity
    for (int32_t ic = 0; ic < COLOR_TEMP_NUM - 1; ic++)
    {
        int32_t c_dist = MAX(abs(awb_stats_conf->u[ic] - awb_stats_conf->u[ic + 1]), abs(awb_stats_conf->v[ic] - awb_stats_conf->v[ic + 1]));
        int32_t c_dist_half = (c_dist + 1) >> 1;

        awb_stats_conf->c_th[ic] = MAX(c_dist_half, awb_stats_conf->c_th[ic]);
        awb_stats_conf->c_th[ic + 1] = MAX(c_dist_half, awb_stats_conf->c_th[ic + 1]);
    }
//  DSP2_Enable_AWB2();

  // DSP2_Set_AWB2_Stats_Conf(&awb_stats_conf);
  // DSP2_Set_AWB2_State(ENABLE);
}

static void awb2_set_gain_default()
{
  DSP2_RGB_Gain_Type rgb_gain;
  rgb_gain.r_gain = r_gain_default;
  rgb_gain.g_gain = GAIN_UNITY;
  rgb_gain.b_gain = b_gain_default;
  DSP2_Set_AWB2_Gain(&rgb_gain);
}

static int awb2_config(awb_config_t *config, bool is_virtual_sensor)
{
    if (is_virtual_sensor) {
        fw_param.temporal_smooth = 0;
    }
    dsp2_awb2_stats_conf_t awb_stats_conf;
    // awb_stats_enable(&(config->stats_cfg));
    // awb2_ctx.awb_configed = 1;

    width  = config->stats_cfg.act_win.width;
    height = config->stats_cfg.act_win.height;

    awb2_hw_init(&awb_stats_conf);
    awb2_set_gain_default();
    DSP2_Set_AWB2_Stats_Conf(&awb_stats_conf);
    DSP2_Set_AWB2_State(ENABLE);
    DSP2_Set_AWB2_Gain_State(ENABLE);
    return 0;
}

static void decide_awb_gain()
{
  // basic gain from white statistics
  int32_t r_gain_white = (int32_t)((reg.white_g_sum << GAIN_PRECISION) / MAX(1, reg.white_r_sum));
  int32_t b_gain_white = (int32_t)((reg.white_g_sum << GAIN_PRECISION) / MAX(1, reg.white_b_sum));

  // compensate based on difference between grey world and white statistics
  int32_t r_gain_comp;
  int32_t b_gain_comp;

  if (fw_param.compensate_en)
  {
    int32_t r_gain_grey = (reg.g_avg << GAIN_PRECISION) / MAX(1, reg.r_avg);
    int32_t b_gain_grey = (reg.g_avg << GAIN_PRECISION) / MAX(1, reg.b_avg);

    int32_t r_diff = r_gain_white - r_gain_grey;
    int32_t b_diff = b_gain_white - b_gain_grey;

    int32_t abs_r_diff = abs(r_diff);
    int32_t abs_b_diff = abs(b_diff);

    int32_t comp = MIN(fw_param.compensate_max, (MIN(abs_r_diff, abs_b_diff) * fw_param.compensate_ratio) >> COMPENSATE_RATIO_PRECISION);

    if (r_diff >= 0 && b_diff < 0)
    {
      r_gain_comp = r_gain_white + comp;
      b_gain_comp = b_gain_white - comp;
    }
    else if (r_diff < 0 && b_diff >= 0)
    {
      r_gain_comp = r_gain_white - comp;
      b_gain_comp = b_gain_white + comp;
    }
    else
    {
      r_gain_comp = r_gain_white;
      b_gain_comp = b_gain_white;
    }
  }
  else
  {
    r_gain_comp = r_gain_white;
    b_gain_comp = b_gain_white;
  }

  // soft clip on extreme values
  int32_t r_gain_clip;
  int32_t b_gain_clip;

  if (fw_param.soft_clip_en)
  {
    int32_t r_gain_clip_ini = soft_clip(fw_param.soft_clip_r_min, fw_param.soft_clip_r_max, r_gain_comp, fw_param.soft_clip_slope, SOFT_CLIP_SLOPE_PRECISION);
    int32_t b_gain_clip_ini = soft_clip(fw_param.soft_clip_b_min, fw_param.soft_clip_b_max, b_gain_comp, fw_param.soft_clip_slope, SOFT_CLIP_SLOPE_PRECISION);

    r_gain_clip = r_gain_clip_ini - (b_gain_clip_ini - b_gain_comp);
    b_gain_clip = b_gain_clip_ini - (r_gain_clip_ini - r_gain_comp);
  }
  else
  {
    r_gain_clip = r_gain_comp;
    b_gain_clip = b_gain_comp;
  }

  // fallback to default gain when white ratio is too low
  int32_t alpha_stat = MIN(ALPHA_STAT_MAX, (reg.white_ratio * fw_param.alpha_stat_slope) >> ALPHA_STAT_SLOPE_PRECISION);

  int32_t r_gain_fallback = alpha_blend(r_gain_clip, r_gain_default, alpha_stat, ALPHA_STAT_PRECISION);
  int32_t b_gain_fallback = alpha_blend(b_gain_clip, b_gain_default, alpha_stat, ALPHA_STAT_PRECISION);

  // bias for tuning and adaptivity
  if (fw_param.bias_en)
  {
    fw_curr.r_gain = (r_gain_fallback * fw_param.bias_r_gain) >> GAIN_PRECISION;
    fw_curr.b_gain = (b_gain_fallback * fw_param.bias_b_gain) >> GAIN_PRECISION;
  }
  else
  {
    fw_curr.r_gain = r_gain_fallback;
    fw_curr.b_gain = b_gain_fallback;
  }
}

static void temporal_smooth()
{
  iir_filter(&(fw_iir.r_gain), fw_curr.r_gain, &(reg.r_gain));
  iir_filter(&(fw_iir.b_gain), fw_curr.b_gain, &(reg.b_gain));
}

static void iir_filter(int32_t* iir, int32_t curr, int32_t* result)
{
  *iir = alpha_blend(*iir, curr << TEMPORAL_IIR_EXTRA_PRECISION, fw_param.temporal_smooth, TEMPORAL_SMOOTH_PRECISION);
  *result = round_off(*iir, TEMPORAL_IIR_EXTRA_PRECISION);
}

static void awb_get_stats()
{
    DSP2_Get_AWB2_Sum(&awb2_sum);

    reg.r_avg       = awb2_sum.r_avg;
    reg.g_avg       = awb2_sum.g_avg;
    reg.b_avg       = awb2_sum.b_avg;
    reg.white_r_sum = awb2_sum.white_r_sum;
    reg.white_g_sum = awb2_sum.white_g_sum;
    reg.white_b_sum = awb2_sum.white_b_sum;
    reg.white_ratio = awb2_sum.white_ratio;
}

static int32_t calculate_color_temp()
{
    int32_t r_gain;
    int32_t b_gain;

    int32_t color_temp;
    int32_t diff_cal[COLOR_TEMP_NUM];
    int32_t diff;
    int32_t ic;

    const wb_info_t *wb_info_L, *wb_info_H;

    r_gain = reg.r_gain;
    b_gain = reg.b_gain;
    diff = r_gain - b_gain;

    for (ic = 0; ic < COLOR_TEMP_NUM; ic++) {
        // diff_cal[ic] = wb_gain_map[ic][0] - wb_gain_map[ic][1];
        img_param_get_manual_wb_info(ic, &wb_info_H);
        diff_cal[ic] = wb_info_H->rb_gain.r_gain - wb_info_H->rb_gain.b_gain;

        if (diff < diff_cal[ic]) {
          break;
        }
    }

    if (ic == 0) {
        // color_temp = wb_gain_map[0][2];
        img_param_get_manual_wb_info(ic, &wb_info_H);
        color_temp = wb_info_H->color_temp;
    }
    else if (ic == COLOR_TEMP_NUM) {
        // color_temp = wb_gain_map[COLOR_TEMP_NUM - 1][2];
        img_param_get_manual_wb_info(COLOR_TEMP_NUM - 1, &wb_info_H);
        color_temp = wb_info_H->color_temp;
    }
    else {
        // color_temp = ((diff_cal[ic] - diff) * wb_gain_map[ic - 1][2] + (diff - diff_cal[ic - 1]) * wb_gain_map[ic][2]) / (diff_cal[ic] - diff_cal[ic - 1]);
        img_param_get_manual_wb_info(ic - 1, &wb_info_L);
        img_param_get_manual_wb_info(ic, &wb_info_H);
        color_temp = ((diff_cal[ic] - diff) * wb_info_L->color_temp \
            + (diff - diff_cal[ic - 1]) * wb_info_H->color_temp) \
            / (diff_cal[ic] - diff_cal[ic - 1]);
    }

    awb2_ctx.awb_info.color_temp = color_temp;
    awb2_ctx.awb_info.ct_update = 1;

    return 0;
}

static int awb2_set_gain(DSP2_RGB_Gain_Type *rgb_gain)
{
    DSP2_Set_AWB2_Gain(rgb_gain);

    awb2_ctx.awb_info.rb_gain.r_gain = rgb_gain->r_gain;
    awb2_ctx.awb_info.rb_gain.b_gain = rgb_gain->b_gain;
    awb2_ctx.awb_info.rb_gain_update = 1;

    return 0;
}

static int awb2_get_gain(DSP2_RGB_Gain_Type *rgb_gain)
{
    DSP2_Get_AWB2_Gain(rgb_gain);

    return 0;
}

/* for debug purpose only */
static int awb2_set_color_temp(BL_COLOR_TEMP color_temp)
{
    awb2_ctx.new_color_temp = color_temp;

    awb2_ctx.awb_config_update |= AWB_UPDATE_BIT_COLOR_TEMP;

    return 0;
}

static int awb2_get_color_temp(BL_COLOR_TEMP *color_temp)
{
    *color_temp = (BL_COLOR_TEMP)(awb2_ctx.awb_info.color_temp);

    return 0;
}

static int awb2_set_mode(AWB_MODE mode)
{
    if (!is_param_valid(mode, AWB_MODE_AUTO, AWB_MODE_NUM - 1)) {
        MSG("awb2_set_mode: invalid AWB mode %d!\r\n", mode);
        return -1;
    }

    awb2_ctx.new_awb_mode = mode;
    awb2_ctx.awb_config_update |= AWB_UPDATE_BIT_MODE;

    return 0;
}

static int awb2_get_mode(AWB_MODE *mode)
{
    *mode = awb2_ctx.awb_info.awb_mode;

    return 0;
}

static int awb2_clear_info()
{
    awb2_ctx.awb_info.rb_gain_update = 0;
    awb2_ctx.awb_info.ct_update = 0;

    return 0;
}

static int awb2_control()
{

    awb2_clear_info();

    /* Check if AWB config is updated */
    if (awb2_ctx.awb_config_update) {
        if (awb2_ctx.awb_config_update & AWB_UPDATE_BIT_MODE) {
            awb2_ctx.awb_info.awb_mode = awb2_ctx.new_awb_mode;
        }

        /* if new color temp is not equal to previous one, awb_info.ct_update color temp related param */
        if (awb2_ctx.awb_config_update & AWB_UPDATE_BIT_COLOR_TEMP &&
            awb2_ctx.new_color_temp != awb2_ctx.awb_info.color_temp) {
            awb2_ctx.awb_info.color_temp = awb2_ctx.new_color_temp;
            awb2_ctx.awb_info.ct_update = 1;
        }

        awb2_ctx.awb_config_update = 0;
    }

    if (awb2_ctx.awb_info.awb_mode != AWB_MODE_AUTO) {
        return 0;
    }

    // run after every frame hardware interrupt
    awb_get_stats();

    if (0 != awb2_ctx.awb_start_skip_num && awb2_ctx.awb_start_skip_num-- > 0) {
        MSG("AWB booting!\r\n");
        return -1;
    }

    decide_awb_gain();
    temporal_smooth();

    calculate_color_temp();
    // TODO: optimize after verification.
    DSP2_RGB_Gain_Type rgb_gain;
    rgb_gain.r_gain = (uint16_t)reg.r_gain;
    rgb_gain.g_gain = (uint16_t)GAIN_UNITY;
    rgb_gain.b_gain = (uint16_t)reg.b_gain;
    awb2_set_gain(&rgb_gain);

    return 0;
}

static void awb2_func_int(awb_func_t *func)
{
    func->config          = awb2_config;
    func->control         = awb2_control;
    func->get_info        = awb2_get_info;
    func->set_mode        = awb2_set_mode;
    func->get_mode        = awb2_get_mode;
    func->set_gain        = awb2_set_gain;
    func->get_gain        = awb2_get_gain;
    func->set_color_temp  = awb2_set_color_temp;
    func->get_color_temp  = awb2_get_color_temp;
}

int awb2_init(awb_func_t *func)
{
  awb2_ctx.awb_start_skip_num = IMG_START_SKIP_NUM;

  const wb_info_t *wb_info_L, *wb_info_H;
  // TODO: check the color temp table
  awb2_func_int(func);

  img_param_get_manual_wb_info(D65, &wb_info_H);
  img_param_get_manual_wb_info(D50, &wb_info_L);

  r_gain_default = alpha_blend(wb_info_H->rb_gain.r_gain, wb_info_L->rb_gain.r_gain,
        fw_param.default_d65_weight, DEFAULT_WEIGHT_PRECISION);
  b_gain_default = alpha_blend(wb_info_H->rb_gain.b_gain, wb_info_L->rb_gain.b_gain,
        fw_param.default_d65_weight, DEFAULT_WEIGHT_PRECISION);

  // calculate off-line in advance or only once at initial
    img_param_get_manual_wb_info(D75, &wb_info_H);
    img_param_get_manual_wb_info(H, &wb_info_L);


  // typical firmware parameter
  fw_param.default_d65_weight = (1 << DEFAULT_WEIGHT_PRECISION) >> 1;
  fw_param.compensate_en = 1;
  fw_param.compensate_ratio = (1 << COMPENSATE_RATIO_PRECISION) >> 1;
  fw_param.compensate_max = GAIN_UNITY >> 3;
  fw_param.soft_clip_en = 1;
  fw_param.soft_clip_r_min = wb_info_L->rb_gain.r_gain;
  fw_param.soft_clip_r_max = wb_info_H->rb_gain.r_gain;
  fw_param.soft_clip_b_min = wb_info_H->rb_gain.b_gain;
  fw_param.soft_clip_b_max = wb_info_L->rb_gain.b_gain;
  fw_param.soft_clip_slope = (1 << SOFT_CLIP_SLOPE_PRECISION) >> 1;
  fw_param.alpha_stat_slope = 64;
  fw_param.bias_en = 0;
  fw_param.bias_r_gain = GAIN_UNITY;
  fw_param.bias_b_gain = GAIN_UNITY;
  fw_param.temporal_smooth = 22;

  // initialize IIR
  fw_iir.r_gain = r_gain_default;
  fw_iir.b_gain = b_gain_default;

  // increase IIR register precision to avoid permanent residue
  fw_iir.r_gain <<= TEMPORAL_IIR_EXTRA_PRECISION;
  fw_iir.b_gain <<= TEMPORAL_IIR_EXTRA_PRECISION;

  // TODO, optimize after verification

  return 0;
}
