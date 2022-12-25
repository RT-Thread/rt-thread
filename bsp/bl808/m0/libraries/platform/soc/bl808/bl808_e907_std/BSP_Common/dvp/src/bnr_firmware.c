#include <stdint.h>
#include "bnr_firmware.h"
#include "bl_img_utils.h"
#include "bl_comm_aaa.h"

#define PIXEL_BW                  (12)
#define PIXEL_MAX                 ((1 << PIXEL_BW) - 1)
#define LPF_WEIGHT_PRECISION      (4)
#define LPF_WEIGHT_MAX            (1 << LPF_WEIGHT_PRECISION)
#define TH_BW                     (10)
#define TH_MAX                    ((1 << TH_BW) - 1)
#define TH_SLOPE_PRECISION        (8)
#define SLOPE_BW                  (12)
#define SLOPE_MAX                 ((1 << SLOPE_BW) - 1)
#define SLOPE_GAIN_PRECISION      (4)
#define WEIGHT_INI_MAX            (15)
#define FB_LEVEL_BW               (3)
#define FB_LEVEL_MAX              ((1 << FB_LEVEL_BW) - 1)
#define BNR_WEIGHT_PRECISION      (6)
#define BNR_WEIGHT_MAX            (1 << BNR_WEIGHT_PRECISION)

#define BNR_STRENGTH_PRECISION    (6)
#define BNR_STRENGTH_HALF         (1 << (BNR_STRENGTH_PRECISION - 1))
#define TH_SLOPE_ADJUST_PRECISION (6)

typedef struct
{
    uint16_t bnr_weight;
    uint16_t lpf_weight;
    DSP2_BNR_THRESHOLD_TYPE bnr_thr;
    DSP2_BNR_FALLBACK_TYPE  bnr_fb;
} bnr_reg_internal_t;

typedef struct
{
    uint16_t fw_bnr_strength; // range: 0 ~ (2 ^ BNR_STRENGTH_PRECISION)
    uint16_t fw_th_base_r; // range: 0 ~ (2 ^ TH_BW - 1)
    uint16_t fw_th_base_g; // range: 0 ~ (2 ^ TH_BW - 1)
    uint16_t fw_th_base_b; // range: 0 ~ (2 ^ TH_BW - 1)
    uint16_t fw_th_slope_r_adj; // range: 0 ~ (2 ^ TH_SLOPE_ADJUST_PRECISION)
    uint16_t fw_th_slope_g_adj; // range: 0 ~ (2 ^ TH_SLOPE_ADJUST_PRECISION)
    uint16_t fw_th_slope_b_adj; // range: 0 ~ (2 ^ TH_SLOPE_ADJUST_PRECISION)
} bnr_fw_param_t;

/* TODO: optimize mem usage*/
static bnr_reg_internal_t bnr_reg;
static bnr_fw_param_t     bnr_fw;
static uint32_t           iso_debug;

void bnr_init()
{
    bnr_fw.fw_bnr_strength = BNR_STRENGTH_HALF;
    bnr_reg.bnr_thr.slope_gain = 21;
    bnr_reg.bnr_fb.fb_level = 5;
}

void bnr_config(const bnr_fw_config_t *config)
{
    bnr_fw.fw_th_base_r = config->th_base_r;
    bnr_fw.fw_th_base_g = config->th_base_g;
    bnr_fw.fw_th_base_b = config->th_base_b;
    bnr_fw.fw_th_slope_r_adj = config->th_slope_r;
    bnr_fw.fw_th_slope_g_adj = config->th_slope_g;
    bnr_fw.fw_th_slope_b_adj = config->th_slope_b;
}


void bnr_control(BL_GAIN_DB gain)
{

    uint32_t iso = pow(2, GAIN_DB_INT_TO_FLOAT(gain)/6) * 100;
    iso_debug = iso;
    // // SC2232 tuning
    // bnr_fw.fw_th_base_r = 28;
    // bnr_fw.fw_th_base_g = 28;
    // bnr_fw.fw_th_base_b = 28;
    // bnr_fw.fw_th_slope_r_adj = 32;
    // bnr_fw.fw_th_slope_g_adj = 32;
    // bnr_fw.fw_th_slope_b_adj = 32;

    // adjust ISO based on BNR strength
    uint16_t iso_adj = (iso * bnr_fw.fw_bnr_strength) >> (BNR_STRENGTH_PRECISION - 1);

    // strength and ISO adaptive setting
    bnr_reg.bnr_weight = MIN(64, bnr_fw.fw_bnr_strength + (iso_adj >> 4));
    bnr_reg.lpf_weight = MIN(16, (MAX(0, bnr_fw.fw_bnr_strength - BNR_STRENGTH_HALF) >> 1) + (iso_adj >> 8));
    bnr_reg.bnr_thr.th_base_r  = MIN(256, ((bnr_fw.fw_th_base_r * bnr_fw.fw_bnr_strength) >> (BNR_STRENGTH_PRECISION - 1)) + (iso_adj >> 5));
    bnr_reg.bnr_thr.th_base_g  = MIN(256, ((bnr_fw.fw_th_base_g * bnr_fw.fw_bnr_strength) >> (BNR_STRENGTH_PRECISION - 1)) + (iso_adj >> 5));
    bnr_reg.bnr_thr.th_base_b  = MIN(256, ((bnr_fw.fw_th_base_b * bnr_fw.fw_bnr_strength) >> (BNR_STRENGTH_PRECISION - 1)) + (iso_adj >> 5));

    // general default setting
    bnr_reg.bnr_thr.th_slope_r = (bnr_reg.bnr_thr.th_base_r * bnr_fw.fw_th_slope_r_adj) >> (TH_SLOPE_ADJUST_PRECISION - 1);
    bnr_reg.bnr_thr.th_slope_g = (bnr_reg.bnr_thr.th_base_g * bnr_fw.fw_th_slope_g_adj) >> (TH_SLOPE_ADJUST_PRECISION - 1);
    bnr_reg.bnr_thr.th_slope_b = (bnr_reg.bnr_thr.th_base_b * bnr_fw.fw_th_slope_b_adj) >> (TH_SLOPE_ADJUST_PRECISION - 1);
    bnr_reg.bnr_fb.fb_lpf_weight = bnr_reg.lpf_weight >> 1;
    // printf("th_base_r %d, th_slope_r %d\r\n", bnr_reg.bnr_thr.th_base_r, bnr_reg.bnr_thr.th_slope_r);
    // printf("th_base_g %d, th_slope_g %d\r\n", bnr_reg.bnr_thr.th_base_g, bnr_reg.bnr_thr.th_slope_g);
    // printf("th_base_b %d, th_slope_b %d\r\n", bnr_reg.bnr_thr.th_base_b, bnr_reg.bnr_thr.th_slope_b);



}

void bnr_hw_update(void)
{
    DSP2_Set_BNR_Weight(bnr_reg.bnr_weight);
    DSP2_Set_BNR_LPF_Weight(bnr_reg.lpf_weight);
    DSP2_Set_BNR_Threshold(&(bnr_reg.bnr_thr));
    DSP2_Set_BNR_Fallback(&(bnr_reg.bnr_fb));
}

void bnr_control_debug()
{
    DSP2_Set_BNR_State(ENABLE);
    bnr_control(iso_debug);
    bnr_hw_update();
}
