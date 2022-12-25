#include <bl808_dsp2_wdr.h>
#include "wdr_firmware.h"
#include "bl_img_utils.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

static void wdr_decide_chroma_suppression(wdr_fw_config_t *config);
static void wdr_hist_pre_process();
static void wdr_decide_curve();
static int  wdr_interpolate_curve(int bin_interp, int bin_lf, int bin_rt, int curve_lf, int curve_rt, int hist_integral[]);
static void wdr_decide_enhancement();
static void wdr_decide_fallback(wdr_fw_config_t *config);
static void wdr_temporal_smooth();
static void wdr_iir_filter(int *iir, int curr, int *result);

#define PIXEL_BW                            (12)
#define PIXEL_MAX                           ((1 << PIXEL_BW) - 1)
#define CHROMA_CENTER                       (1 << (PIXEL_BW - 1))
#define CS_GAIN_PRECISION                   (PIXEL_BW)
#define CS_WEIGHT_PRECISION                 (4)
#define HIST_PIXEL_BW                       (10)        // must be <= PIXEL_BW
#define HIST_PIXEL_MAX                      ((1 << HIST_PIXEL_BW) - 1)
#define BIN_BW                              (6)
#define BIN_NUM                             ((1 << BIN_BW) + 1)
#define HIST_WEIGHT_PRECISION               (HIST_PIXEL_BW - BIN_BW)
#define HIST_WEIGHT_MAX                     (1 << HIST_WEIGHT_PRECISION)
#define ROI_NUM                             (8)
#define ROI_WEIGHT_BW                       (4)
#define ROI_WEIGHT_SUM_MAX                  (ROI_NUM * ((1 << ROI_WEIGHT_BW) - 1))
#define HIST_BW                             (24)
#define HIST_MAX                            ((1 << HIST_BW) - 1)
#define Y_RATIO_INT_BW                      (4)
#define Y_RATIO_FRAC_BW                     (PIXEL_BW)
#define Y_RATIO_BW                          (Y_RATIO_INT_BW + Y_RATIO_FRAC_BW)
#define FALLBACK_PRECISION                  (4)
#define FALLBACK_MAX                        (1 << FALLBACK_PRECISION)
#define CURVE_WEIGHT_PRECISION              (FALLBACK_PRECISION)
#define CURVE_WEIGHT_MAX                    (1 << CURVE_WEIGHT_PRECISION)
#define ENH_GAIN_PRECISION                  (PIXEL_BW)
#define ENH_WEIGHT_PRECISION                (FALLBACK_PRECISION)
#define ENH_WEIGHT_MAX                      (1 << ENH_WEIGHT_PRECISION)

#define HIST_SHIFT_LEVEL                    (HIST_WEIGHT_PRECISION + 6)     // unit: 64 pixels
#define BIN_1ST_QUARTER                     ((BIN_NUM - 1) >> 2)
#define BIN_2ND_QUARTER                     ((BIN_NUM - 1) >> 1)
#define BIN_3RD_QUARTER                     (BIN_1ST_QUARTER * 3)
#define PROTECT_RATIO_PRECISION             (5)
#define PROTECT_RATIO_MAX                   (1 << PROTECT_RATIO_PRECISION)
#define PROTECT_SLOPE_PRECISION             (5)
#define SWING_GAIN_PRECISION                (5)
#define SWING_CLIP_PRECISION                (5)
#define KEEP_BRIGHT_LEVEL_PRECISION         (4)
#define BRIGHT_GAIN_PRECISION               (8)
#define EMPTY_RATIO_PRECISON                (12)
#define ENH_LEVEL_PRECISION                 (5)
#define C_GAIN_RATIO_PRECISION              (5)
#define C_GAIN_SLOPE_PRECISION              (PIXEL_BW)
#define INSIGNIFICANT_BIN_RATIO_PRECISION   (12)
#define FALLBACK_SLOPE_PRECISION            (8)
#define TEMPORAL_SMOOTH_PRECISION           (5)
#define TEMPORAL_IIR_EXTRA_PRECISION        (4)

typedef struct
{
    // chroma suppression
    int cs_en; // r/w, shadow, 1'b
    int cs_grey_th; // r/w, shadow, 8'b, = PIXEL_BW - 4, range: 0 ~ 255
    int cs_gain; // r/w, shadow, 13'b, = 1 + CS_GAIN_PRECISION, fixed-point 1.12, range: 0 ~ (2 ^ 13 - 1), typical: ceil(2048 * (1 << CS_GAIN_PRECISION) / (2048 - cs_grey_th))
    int cs_weight; // r/w, shadow, 5'b, = 1 + CS_WEIGHT_PRECISION, range: 0 ~ 16, 0: disable

    // histogram
    int hist_roi_en[ROI_NUM]; // r/w, shadow, 1'b
    int hist_roi_weight[ROI_NUM]; // r/w, shadow, 4'b, = ROI_WEIGHT_BW, range: 0 ~ 15
    int hist_x_min[ROI_NUM]; // r/w, shadow, 11'b, range: 0 ~ (width - 1)
    int hist_x_max[ROI_NUM]; // r/w, shadow, 11'b, range: 0 ~ (width - 1)
    int hist_y_min[ROI_NUM]; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
    int hist_y_max[ROI_NUM]; // r/w, shadow, 11'b, range: 0 ~ (height - 1)
    DSP2_WDR_Hist_Data_Type hist; // r, ping-pong, 24'b, = HIST_BW

    // WDR curve
    int curve_en; // r/w, shadow, 1'b
    int curve_weight; // r/w, shadow, 5'b, = 1 + CURVE_WEIGHT_PRECISION, range: 0 ~ 16, 0: disable
    int curve[BIN_NUM - 1]; // r/w, shadow, 10'b, = HIST_PIXEL_BW, range: 0 ~ 1023, monotonically increasing, i.e. curve[N] <= curve[N + 1]

    // post-enhancement
    int enh_en; // r/w, shadow, 1'b
    int enh_weight; // r/w, shadow, 5'b, = 1 + ENH_WEIGHT_PRECISION, range: 0 ~ 16, 0: disable
    int enh_y_offset; // r/w, shadow, 12'b, = PIXEL_BW, range: 0 ~ 4095
    int enh_y_gain; // r/w, shadow, 15'b, = 3 + ENH_GAIN_PRECISION, fixed-point 3.12, range: 0 ~ (2 ^ 15 - 1)
    int enh_c_gain; // r/w, shadow, 15'b, = 3 + ENH_GAIN_PRECISION, fixed-point 3.12, range: 0 ~ (2 ^ 15 - 1)
} wdr_reg_internal_t;

typedef struct
{
    // chroma suppression
    int fw_cs_en;
    int fw_cs_grey_th;
    int fw_cs_weight; // 0 ~ (2 ^ CS_WEIGHT_PRECISION)

    // histogram pre-processing
    int hist_clip_level;

    // WDR curve
    int fw_curve_en;
    int exclude_over_under_exp_en;
    int swing_gain;
    int swing_clip; // 0 ~ (2 ^ SWING_CLIP_PRECISION)
    int protect_slope;
    int curve_keep_bright_level; // 0 ~ (2 ^ KEEP_BRIGHT_LEVEL_PRECISION)
    int bright_gain;

    // post-enhancement
    int fw_enh_en;
    int empty_ratio;
    int enh_keep_bright_level; // 0 ~ (2 ^ KEEP_BRIGHT_LEVEL_PRECISION)
    int dark_enh_level; // 0 ~ (2 ^ ENH_LEVEL_PRECISION)
    int bright_enh_level; // 0 ~ (2 ^ ENH_LEVEL_PRECISION)
    int enh_c_gain_base;
    int enh_c_gain_extra_slope;

    // fallback
    int fw_fallback_en;
    int peak_sum_range;
    int peak_sum_th;
    int peak_sum_slope;
    int insignificant_bin_ratio;
    int insignificant_bin_num_th;
    int insignificant_bin_num_slope;

    // temporal smoothing
    int temporal_smooth; // 0 ~ ((2 ^ TEMPORAL_SMOOTH_PRECISION) - 1)
} wdr_fw_param_t;

/* TODO: optimize mem usage*/
static wdr_reg_internal_t wdr_reg;
static wdr_reg_internal_t wdr_reg_fw_curr;
static wdr_reg_internal_t wdr_reg_fw_iir;
static wdr_fw_param_t     wdr_fw_param;

static int fw_hist_shift[BIN_NUM];
static int fw_hist_clip[BIN_NUM];
static int fw_hist_clip_integral[BIN_NUM + 1];
static int hist_shift_total;

static void wdr_set_hist(int xmax, int ymax)
{
    // histogram
    for (int ir = 0; ir < ROI_NUM; ir++) {
        wdr_reg.hist_roi_en[ir] = (ir == 0) ? 1 : 0;
        wdr_reg.hist_roi_weight[ir] = 1;
        wdr_reg.hist_x_min[ir] = 0;
        wdr_reg.hist_x_max[ir] = xmax;
        wdr_reg.hist_y_min[ir] = 0;
        wdr_reg.hist_y_max[ir] = ymax;
    }
}

static void wdr_set_reg_default(void)
{
    // chroma suppression
    wdr_reg.cs_en = 0;
    wdr_reg.cs_grey_th = 0;
    wdr_reg.cs_gain = 1 << CS_GAIN_PRECISION;
    wdr_reg.cs_weight = 0;

    // histogram
    wdr_set_hist(1919, 1079);

    // WDR curve
    wdr_reg.curve_en = 0;
    wdr_reg.curve_weight = 0;

    for (int ib = 0; ib < BIN_NUM - 1; ib++) {
        wdr_reg.curve[ib] = ib << HIST_WEIGHT_PRECISION;
    }

    // post-enhancement
    wdr_reg.enh_en = 0;
    wdr_reg.enh_weight = 0;
    wdr_reg.enh_y_offset = 0;
    wdr_reg.enh_y_gain = 1 << ENH_GAIN_PRECISION;
    wdr_reg.enh_c_gain = 1 << ENH_GAIN_PRECISION;
}

static void wdr_fw_param_init(void)
{
  // typical ROI setting
  // for (int ir = 0; ir < ROI_NUM; ir++)
  // {
  //   wdr_reg.hist_roi_en[ir] = (ir == 0) ? 1 : 0;
  //   wdr_reg.hist_roi_weight[ir] = 1;
  //   wdr_reg.hist_x_min[ir] = 0;
  //   wdr_reg.hist_x_max[ir] = width - 1;
  //   wdr_reg.hist_y_min[ir] = 0;
  //   wdr_reg.hist_y_max[ir] = height - 1;
  // }

  // chroma suppression
    wdr_fw_param.fw_cs_en = 1;
    wdr_fw_param.fw_cs_grey_th = 3 << (PIXEL_BW - 8);
    wdr_fw_param.fw_cs_weight = 8;

    // histogram pre-processing
    wdr_fw_param.hist_clip_level = BIN_BW - 1;

    // WDR curve
    wdr_fw_param.fw_curve_en = 1;
    wdr_fw_param.exclude_over_under_exp_en = 1;
    wdr_fw_param.swing_gain = 18;
    wdr_fw_param.swing_clip = 14;
    wdr_fw_param.protect_slope = 48;
    wdr_fw_param.curve_keep_bright_level = 4;
    wdr_fw_param.bright_gain = 256;

    // post-enhancement
    wdr_fw_param.fw_enh_en = 1;
    wdr_fw_param.empty_ratio = 20;
    wdr_fw_param.enh_keep_bright_level = 4;
    wdr_fw_param.dark_enh_level = 26;
    wdr_fw_param.bright_enh_level = 26;
    wdr_fw_param.enh_c_gain_base = 34;
    wdr_fw_param.enh_c_gain_extra_slope = 48;

    // fallback
    wdr_fw_param.fw_fallback_en = 1;
    wdr_fw_param.peak_sum_range = 1;
    wdr_fw_param.peak_sum_th = 35;
    wdr_fw_param.peak_sum_slope = 82;
    wdr_fw_param.insignificant_bin_ratio = 8;
    wdr_fw_param.insignificant_bin_num_th = 50;
    wdr_fw_param.insignificant_bin_num_slope = 164;

    // temporal smoothing
    wdr_fw_param.temporal_smooth = 22;

    // initialize IIR
    wdr_reg_fw_iir.cs_grey_th = 0;
    wdr_reg_fw_iir.cs_gain = 1 << CS_GAIN_PRECISION;
    wdr_reg_fw_iir.cs_weight = 0;

    wdr_reg_fw_iir.curve_weight = 0;

    for (int ib = 0; ib < BIN_NUM - 1; ib++) {
        wdr_reg_fw_iir.curve[ib] = ib << HIST_WEIGHT_PRECISION;
    }

    wdr_reg_fw_iir.enh_weight = 0;
    wdr_reg_fw_iir.enh_y_offset = 0;
    wdr_reg_fw_iir.enh_y_gain = 1 << ENH_GAIN_PRECISION;
    wdr_reg_fw_iir.enh_c_gain = 1 << ENH_GAIN_PRECISION;

    // increase IIR register precision to avoid permanent residue
    wdr_reg_fw_iir.cs_grey_th <<= TEMPORAL_IIR_EXTRA_PRECISION;
    wdr_reg_fw_iir.cs_gain <<= TEMPORAL_IIR_EXTRA_PRECISION;
    wdr_reg_fw_iir.cs_weight <<= TEMPORAL_IIR_EXTRA_PRECISION;

    wdr_reg_fw_iir.curve_weight <<= TEMPORAL_IIR_EXTRA_PRECISION;

    for (int ib = 0; ib < BIN_NUM - 1; ib++) {
        wdr_reg_fw_iir.curve[ib] <<= TEMPORAL_IIR_EXTRA_PRECISION;
    }

    wdr_reg_fw_iir.enh_weight <<= TEMPORAL_IIR_EXTRA_PRECISION;
    wdr_reg_fw_iir.enh_y_offset <<= TEMPORAL_IIR_EXTRA_PRECISION;
    wdr_reg_fw_iir.enh_y_gain <<= TEMPORAL_IIR_EXTRA_PRECISION;
    wdr_reg_fw_iir.enh_c_gain <<= TEMPORAL_IIR_EXTRA_PRECISION;
}

static void wdr_hw_init(void)
{
    DSP2_WDR_Set_CS_State(ENABLE);
    DSP2_WDR_Set_WDR_Curve_State(ENABLE);
    DSP2_WDR_Set_Post_Enhance_State(ENABLE);
}

void wdr_hw_update(void)
{
    int i;
    DSP2_WDR_Curve_Type wdr_curve;
    DSP2_Chroma_Suppress_Type cs_cfg;
    // apply wdr curve
    for (i = 0; i < DSP2_WDR_CURVE_COEF_NUM; i++) {
        wdr_curve.curve_coef[i] = wdr_reg.curve[i];
    }

    cs_cfg.gain = wdr_reg.cs_gain;
    cs_cfg.weight = wdr_reg.cs_weight;
    cs_cfg.gain_thresh = wdr_reg.cs_grey_th;

    DSP2_WDR_Set_CS_Config(&cs_cfg);
    DSP2_WDR_Set_WDR_Curve(&wdr_curve);
    DSP2_WDR_Set_WDR_Curve_Weight(wdr_reg.curve_weight);
    DSP2_WDR_Set_Post_Enhance_Weight(wdr_reg.enh_weight);
    DSP2_WDR_Set_Post_Enhance_Y_Offset(wdr_reg.enh_y_offset);
    DSP2_WDR_Set_Post_Enhance_Luma_Gain(wdr_reg.enh_y_gain);
    DSP2_WDR_Set_Post_Enhance_Chroma_Gain(wdr_reg.enh_c_gain);
}

int wdr_control(wdr_fw_config_t *config)
{
    // run after each frame hardware done (WDR interrupt)
    wdr_decide_chroma_suppression(config);
    wdr_hist_pre_process();
    wdr_decide_curve();
    wdr_decide_enhancement();
    wdr_decide_fallback(config);
    wdr_temporal_smooth();

    return 0;
}

int wdr_init()
{
    wdr_set_reg_default();
    wdr_fw_param_init();
    wdr_hw_init();

    return 0;
}

int wdr_config(wdr_config_t *config, bool is_virtual_sensor)
{
    wdr_set_hist(config->stats_cfg.act_win.width-1, config->stats_cfg.act_win.width-1);
    DSP2_WDR_Set_ROI_State(0, ENABLE);
    DSP2_WDR_Set_ROI_Weight(0, 1);
    DSP2_WDR_Set_ROI_Position(0, 0, config->stats_cfg.act_win.width-1, 0, config->stats_cfg.act_win.height-1);

    if (is_virtual_sensor) {
        wdr_fw_param.temporal_smooth = 0;
    }

    return 0;
}

static void wdr_decide_chroma_suppression(wdr_fw_config_t *config)
{
    wdr_reg.cs_en = wdr_fw_param.fw_cs_en;

    if (wdr_fw_param.fw_cs_en) {
        // had better be ISO-adaptive, stronger suppression for larger noise
        wdr_reg_fw_curr.cs_grey_th = config->param.cs_gain_thresh;
        wdr_reg_fw_curr.cs_weight  = config->param.cs_weight;

        int divisor = (1 << (PIXEL_BW - 1)) - wdr_reg_fw_curr.cs_grey_th;
        wdr_reg_fw_curr.cs_gain = ((1 << (PIXEL_BW - 1)) * (1 << CS_GAIN_PRECISION) + (divisor - 1)) / divisor;
    }
    else {
        wdr_reg_fw_curr.cs_grey_th = 0;
        wdr_reg_fw_curr.cs_gain = 1 << CS_GAIN_PRECISION;
        wdr_reg_fw_curr.cs_weight = 0;
    }
}

static void wdr_hist_pre_process()
{
    DSP2_WDR_Get_Hist_Data(&wdr_reg.hist);

    // shift histogram
    for (int ib = 0; ib < BIN_NUM; ib++) {
        fw_hist_shift[ib] = wdr_reg.hist.hist_bin[ib] >> HIST_SHIFT_LEVEL;
    }

    // calculate histogram total sum
    hist_shift_total = 0;

    for (int ib = 0; ib < BIN_NUM; ib++) {
        hist_shift_total += fw_hist_shift[ib];
    }

    // clip histogram
    int hist_clip_max = hist_shift_total >> wdr_fw_param.hist_clip_level;

    for (int ib = 0; ib < BIN_NUM; ib++) {
        fw_hist_clip[ib] = MIN(hist_clip_max, fw_hist_shift[ib]);
    }

    if (wdr_fw_param.exclude_over_under_exp_en) {
        fw_hist_clip[0] = 0;
        fw_hist_clip[BIN_NUM - 1] = 0;
    }

    // use integral image to reduce calculation of repetitive summation
    fw_hist_clip_integral[0] = 0;

    for (int ib = 1; ib < BIN_NUM + 1; ib++) {
        fw_hist_clip_integral[ib] = fw_hist_clip_integral[ib - 1] + fw_hist_clip[ib - 1];
    }
}

static void wdr_decide_curve()
{
    wdr_reg.curve_en = wdr_fw_param.fw_curve_en;

    if (wdr_fw_param.fw_curve_en) {
        int curve_ini[BIN_NUM];

        // for assertion
        for (int ib = 0; ib < BIN_NUM; ib++) {
            curve_ini[ib] = -1;
        }

        // decide quarter curve points first
        curve_ini[0] = 0;
        curve_ini[BIN_NUM - 1] = 1 << HIST_PIXEL_BW;

        curve_ini[BIN_1ST_QUARTER] = wdr_interpolate_curve(BIN_1ST_QUARTER, 0, BIN_NUM - 1, curve_ini[0], curve_ini[BIN_NUM - 1], fw_hist_clip_integral);
        curve_ini[BIN_3RD_QUARTER] = wdr_interpolate_curve(BIN_3RD_QUARTER, 0, BIN_NUM - 1, curve_ini[0], curve_ini[BIN_NUM - 1], fw_hist_clip_integral);

        curve_ini[BIN_2ND_QUARTER] = wdr_interpolate_curve(BIN_2ND_QUARTER, BIN_1ST_QUARTER, BIN_3RD_QUARTER, curve_ini[BIN_1ST_QUARTER], curve_ini[BIN_3RD_QUARTER], fw_hist_clip_integral);

        curve_ini[BIN_1ST_QUARTER] = alpha_blend(BIN_1ST_QUARTER << HIST_WEIGHT_PRECISION, curve_ini[BIN_1ST_QUARTER], wdr_fw_param.curve_keep_bright_level, KEEP_BRIGHT_LEVEL_PRECISION);
        curve_ini[BIN_2ND_QUARTER] = alpha_blend(BIN_2ND_QUARTER << HIST_WEIGHT_PRECISION, curve_ini[BIN_2ND_QUARTER], wdr_fw_param.curve_keep_bright_level, KEEP_BRIGHT_LEVEL_PRECISION);
        curve_ini[BIN_3RD_QUARTER] = alpha_blend(BIN_3RD_QUARTER << HIST_WEIGHT_PRECISION, curve_ini[BIN_3RD_QUARTER], wdr_fw_param.curve_keep_bright_level, KEEP_BRIGHT_LEVEL_PRECISION);

        for (int step = (BIN_NUM - 1) >> 3; step >= 1; step >>= 1) {
            for (int ib = step; ib < BIN_NUM; ib += (step << 1)) {
                int bin_lf = ib - step;
                int bin_rt = ib + step;

                int curve_lf = curve_ini[bin_lf];
                int curve_rt = curve_ini[bin_rt];

                assert(curve_lf != -1);
                assert(curve_rt != -1);

                curve_ini[ib] = wdr_interpolate_curve(ib, bin_lf, bin_rt, curve_lf, curve_rt, fw_hist_clip_integral);
            }
        }

        for (int ib = 0; ib < BIN_NUM; ib++) {
            assert(curve_ini[ib] != -1);

            if (ib > 0) {
                assert(curve_ini[ib] >= curve_ini[ib - 1]);
            }
        }

        // curve smoothing
        curve_ini[BIN_1ST_QUARTER] = (curve_ini[BIN_1ST_QUARTER - 1] + curve_ini[BIN_1ST_QUARTER + 1]) >> 1;
        curve_ini[BIN_2ND_QUARTER] = (curve_ini[BIN_2ND_QUARTER - 1] + curve_ini[BIN_2ND_QUARTER + 1]) >> 1;
        curve_ini[BIN_3RD_QUARTER] = (curve_ini[BIN_3RD_QUARTER - 1] + curve_ini[BIN_3RD_QUARTER + 1]) >> 1;

        for (int ib = 0; ib < BIN_NUM - 1; ib++) {
            if (ib == 0) {
                wdr_reg_fw_curr.curve[ib] = curve_ini[ib];
            }
            else {
                wdr_reg_fw_curr.curve[ib] = round_off(curve_ini[ib - 1] + (curve_ini[ib] << 1) + curve_ini[ib + 1], 2);
            }
        }

        // adjust brightness
        for (int ib = 0; ib < BIN_NUM - 1; ib++) {
            wdr_reg_fw_curr.curve[ib] = MIN(HIST_PIXEL_MAX, (wdr_reg_fw_curr.curve[ib] * wdr_fw_param.bright_gain) >> BRIGHT_GAIN_PRECISION);
        }
    }
    else {
        for (int ib = 0; ib < BIN_NUM - 1; ib++) {
            wdr_reg_fw_curr.curve[ib] = ib << HIST_WEIGHT_PRECISION;
        }
    }
}

static int wdr_interpolate_curve(int bin_interp, int bin_lf, int bin_rt, int curve_lf, int curve_rt, int hist_integral[])
{
    // sum [a] ~ [b] = integral [b + 1] - [a]
    int sum_lf = hist_integral[bin_interp + 1] - hist_integral[bin_lf];
    int sum_rt = hist_integral[bin_rt + 1] - hist_integral[bin_interp];

    int curve_linear = ((bin_rt - bin_interp) * curve_lf + (bin_interp - bin_lf) * curve_rt + ((bin_rt - bin_lf) >> 1)) / (bin_rt - bin_lf);
    int curve_blend;

    if (sum_lf + sum_rt == 0) {
        curve_blend = curve_linear;
    }
    else {
        curve_blend = (sum_rt * curve_lf + sum_lf * curve_rt + ((sum_lf + sum_rt) >> 1)) / (sum_lf + sum_rt);
    }

    assert(within(curve_lf, curve_rt, curve_blend));

    // protect dynamic range at dark and bright sides
    int protect_ratio = PROTECT_RATIO_MAX - MIN(PROTECT_RATIO_MAX, (abs(bin_interp - BIN_2ND_QUARTER) * wdr_fw_param.protect_slope) >> (PROTECT_SLOPE_PRECISION + (BIN_BW - 1) - PROTECT_RATIO_PRECISION));

    int swing_gain_protect = (wdr_fw_param.swing_gain * protect_ratio) >> PROTECT_RATIO_PRECISION;
    int swing_clip_protect = (wdr_fw_param.swing_clip * protect_ratio) >> PROTECT_RATIO_PRECISION;

    int up_swing_gain;
    int dn_swing_gain;
    int up_swing_clip;
    int dn_swing_clip;

    if (bin_interp <= BIN_2ND_QUARTER) {
        up_swing_gain = wdr_fw_param.swing_gain;
        up_swing_clip = wdr_fw_param.swing_clip;

        dn_swing_gain = swing_gain_protect;
        dn_swing_clip = swing_clip_protect;
    }
    else {
        dn_swing_gain = wdr_fw_param.swing_gain;
        dn_swing_clip = wdr_fw_param.swing_clip;

        up_swing_gain = swing_gain_protect;
        up_swing_clip = swing_clip_protect;
    }

    int up_swing_max = ((curve_rt - curve_linear) * up_swing_clip) >> SWING_CLIP_PRECISION;
    int dn_swing_max = ((curve_linear - curve_lf) * dn_swing_clip) >> SWING_CLIP_PRECISION;

    int swing_ini = curve_blend - curve_linear;
    int swing_gain_mux = (swing_ini >= 0) ? up_swing_gain : dn_swing_gain;
    int swing = clip(-dn_swing_max, up_swing_max, (swing_ini * swing_gain_mux) >> SWING_GAIN_PRECISION);
    int curve_interp = curve_linear + swing;

    assert(within(curve_lf, curve_rt, curve_interp));

    return curve_interp;
}

static void wdr_decide_enhancement()
{
    wdr_reg.enh_en = wdr_fw_param.fw_enh_en;

    if (wdr_fw_param.fw_enh_en) {
        // accumulate histogram from dark and bright ends
        int dark_empty_bin = 0;
        int dark_sum = 0;

        for (int ib = 0; ib < BIN_NUM; ib++) {
            dark_sum += fw_hist_shift[ib];

            if (dark_sum >= ((hist_shift_total * wdr_fw_param.empty_ratio) >> EMPTY_RATIO_PRECISON)) {
                dark_empty_bin = ib;
                break;
            }
        }

        int bright_empty_bin = BIN_NUM - 1;
        int bright_sum = 0;

        for (int ib = BIN_NUM - 1; ib >= 0; ib--) {
            bright_sum += fw_hist_shift[ib];

            if (bright_sum >= ((hist_shift_total * wdr_fw_param.empty_ratio) >> EMPTY_RATIO_PRECISON)) {
                bright_empty_bin = ib;
                break;
            }
        }

        int dark_empty_y = (dark_empty_bin == BIN_NUM - 1) ? (1 << PIXEL_BW) : (wdr_reg_fw_curr.curve[dark_empty_bin] << (PIXEL_BW - HIST_PIXEL_BW));
        int bright_empty_y = (bright_empty_bin == BIN_NUM - 1) ? (1 << PIXEL_BW) : (wdr_reg_fw_curr.curve[bright_empty_bin] << (PIXEL_BW - HIST_PIXEL_BW));

        int dark_shrink_ini = MIN(1 << (PIXEL_BW - 2), (dark_empty_y * wdr_fw_param.dark_enh_level) >> ENH_LEVEL_PRECISION);
        int bright_shrink_ini = MIN(1 << (PIXEL_BW - 2), (((1 << PIXEL_BW) - bright_empty_y) * wdr_fw_param.bright_enh_level) >> ENH_LEVEL_PRECISION);

        int min_shrink = MIN(dark_shrink_ini, bright_shrink_ini);

        int dark_shrink = alpha_blend(min_shrink, dark_shrink_ini, wdr_fw_param.enh_keep_bright_level, KEEP_BRIGHT_LEVEL_PRECISION);
        int bright_shrink = alpha_blend(min_shrink, bright_shrink_ini, wdr_fw_param.enh_keep_bright_level, KEEP_BRIGHT_LEVEL_PRECISION);

        wdr_reg_fw_curr.enh_y_offset = dark_shrink;
        wdr_reg_fw_curr.enh_y_gain = ((1 << PIXEL_BW) << ENH_GAIN_PRECISION) / ((1 << PIXEL_BW) - (dark_shrink + bright_shrink));

        int enh_c_gain_extra = (dark_shrink * wdr_fw_param.enh_c_gain_extra_slope) >> C_GAIN_SLOPE_PRECISION;
        wdr_reg_fw_curr.enh_c_gain = wdr_reg_fw_curr.enh_y_gain * (wdr_fw_param.enh_c_gain_base + enh_c_gain_extra) >> C_GAIN_RATIO_PRECISION;
    }
    else {
        wdr_reg_fw_curr.enh_y_offset = 0;
        wdr_reg_fw_curr.enh_y_gain = 1 << ENH_GAIN_PRECISION;
        wdr_reg_fw_curr.enh_c_gain = 1 << ENH_GAIN_PRECISION;
    }
}

static void wdr_decide_fallback(wdr_fw_config_t *config)
{
    if (wdr_fw_param.fw_fallback_en) {
        // fallback when histogram distribution is too concentrated: too high peak and too many insignificant bins
        int peak_bin = 0;
        int peak_hist = -1;

        for (int ib = 0; ib < BIN_NUM; ib++) {
            if (fw_hist_shift[ib] > peak_hist)   {
                peak_hist = fw_hist_shift[ib];
                peak_bin = ib;
            }
        }

        int peak_sum = 0;

        for (int ib = peak_bin - wdr_fw_param.peak_sum_range; ib <= peak_bin + wdr_fw_param.peak_sum_range; ib++) {
            if (ib >= 0 && ib < BIN_NUM) {
                peak_sum += fw_hist_shift[ib];
            }
        }

        int insignificant_bin_num = 0;
        int insignificant_bin_th = (hist_shift_total * wdr_fw_param.insignificant_bin_ratio) >> INSIGNIFICANT_BIN_RATIO_PRECISION;

        for (int ib = 0; ib < BIN_NUM; ib++) {
            if (fw_hist_shift[ib] < insignificant_bin_th) {
                insignificant_bin_num++;
            }
        }

        int peak_sum_percent = peak_sum * 100 / hist_shift_total;
        int peak_sum_fallback = clip(0, 1 << FALLBACK_PRECISION, ((peak_sum_percent - wdr_fw_param.peak_sum_th) * wdr_fw_param.peak_sum_slope) >> FALLBACK_SLOPE_PRECISION);

        int insignificant_bin_num_percent = (insignificant_bin_num * 100) >> BIN_BW;
        int insignificant_bin_num_fallback = clip(0, 1 << FALLBACK_PRECISION, ((insignificant_bin_num_percent - wdr_fw_param.insignificant_bin_num_th) * wdr_fw_param.insignificant_bin_num_slope) >> FALLBACK_SLOPE_PRECISION);

        int fallback = MIN(1 << FALLBACK_PRECISION, peak_sum_fallback + insignificant_bin_num_fallback);

        // wdr_reg_fw_curr.curve_weight = FALLBACK_MAX - fallback;
        // wdr_reg_fw_curr.enh_weight = FALLBACK_MAX - fallback;
        wdr_reg_fw_curr.curve_weight = MIN(FALLBACK_MAX - fallback, config->param.curve_weight);
        wdr_reg_fw_curr.enh_weight   = MIN(FALLBACK_MAX - fallback, config->param.enh_weight);
    }
    else {
        wdr_reg_fw_curr.curve_weight = config->param.curve_weight;
        wdr_reg_fw_curr.enh_weight   = config->param.enh_weight;
    }
}

static void wdr_temporal_smooth()
{
    wdr_iir_filter(&wdr_reg_fw_iir.cs_grey_th, wdr_reg_fw_curr.cs_grey_th, &wdr_reg.cs_grey_th);
    wdr_iir_filter(&wdr_reg_fw_iir.cs_gain, wdr_reg_fw_curr.cs_gain, &wdr_reg.cs_gain);
    wdr_iir_filter(&wdr_reg_fw_iir.cs_weight, wdr_reg_fw_curr.cs_weight, &wdr_reg.cs_weight);

    wdr_iir_filter(&wdr_reg_fw_iir.curve_weight, wdr_reg_fw_curr.curve_weight, &wdr_reg.curve_weight);

    for (int ib = 0; ib < BIN_NUM - 1; ib++) {
        wdr_iir_filter(&wdr_reg_fw_iir.curve[ib], wdr_reg_fw_curr.curve[ib], &wdr_reg.curve[ib]);
    }

    wdr_iir_filter(&wdr_reg_fw_iir.enh_weight, wdr_reg_fw_curr.enh_weight, &wdr_reg.enh_weight);
    wdr_iir_filter(&wdr_reg_fw_iir.enh_y_offset, wdr_reg_fw_curr.enh_y_offset, &wdr_reg.enh_y_offset);
    wdr_iir_filter(&wdr_reg_fw_iir.enh_y_gain, wdr_reg_fw_curr.enh_y_gain, &wdr_reg.enh_y_gain);
    wdr_iir_filter(&wdr_reg_fw_iir.enh_c_gain, wdr_reg_fw_curr.enh_c_gain, &wdr_reg.enh_c_gain);

    MSG("cs_grey_th %d, cs_gain %d , cs_weight%d , curve_weight %d, enh_weight %d , enh_y_offset %d , enh_y_gain %d\r\n", \
       wdr_reg.cs_grey_th, wdr_reg.cs_gain, wdr_reg.cs_weight, \
       wdr_reg.curve_weight, wdr_reg.enh_weight, wdr_reg.enh_y_offset, wdr_reg.enh_y_gain);
}

static void wdr_iir_filter(int *iir, int curr, int *result)
{
    *iir = alpha_blend(*iir, curr << TEMPORAL_IIR_EXTRA_PRECISION, wdr_fw_param.temporal_smooth, TEMPORAL_SMOOTH_PRECISION);
    *result = round_off(*iir, TEMPORAL_IIR_EXTRA_PRECISION);
}
