#include <string.h>
#include <bl808_dsp2_misc.h>
#include <bl808_dsp2_wdr.h>

#include "img_param.h"
#include "img_proc.h"
#include "wdr_firmware.h"
#include "bnr_firmware.h"


#define PERFORMANCE_MONITOR     0
#define IMG_PROC_SKIP_NUM       0
#define DEFAULT_AWB_ALGO        AWB_ALGO_2
#define ENABLE_3DNR             1
#define WB_BIAS_CT_THRESH       COLOR_TEMP_D50

#define GPIO_IR_BOARD_IRC       (0xFF)
#define GPIO_SENSOR_BOARD_IRC   (0xFF)

#define IMG_UPDATE_MASK_LSC         (1 << 0)
#define IMG_UPDATE_MASK_DPC         (1 << 1)
#define IMG_UPDATE_MASK_WB_GAIN     (1 << 2)
#define IMG_UPDATE_MASK_CCM         (1 << 3)
#define IMG_UPDATE_MASK_GAMMA       (1 << 4)
#define IMG_UPDATE_MASK_WDR         (1 << 5)
#define IMG_UPDATE_MASK_SATURATION  (1 << 6)
#define IMG_UPDATE_MASK_NOISE_LEVEL (1 << 7)
#define IMG_UPDATE_MASK_EE          (1 << 8)
#define IMG_UPDATE_MASK_CS          (1 << 9)
#define IMG_UPDATE_MASK_BLC         (1 << 10)
#define IMG_UPDATE_MASK_BNR         (1 << 11)


typedef struct {
    int stop_imgproc_flag;
    uint16_t skip_num;
    uint16_t start_skip_num;
    uint16_t update_force;
    AWB_ALGO awb_algo;
    const BL_IMG_PARAM_DESC_T *img_param;
} imgproc_obj_t;

typedef struct
{
    uint32_t update_mask;
    DSP2_CLAMP_S clamp;
    DSP2_LSC_COEF_S lsc;
    DSP2_LSC_MAX_S lsc_max;
    DSP2_DPC_THRESHOLD_GROUP_TYPE dpc;
    DSP2_RB_Gain_Type rb_gain;
    DSP2_CCM_COEF_S ccm;
    DSP2_Gamma_Curve_Type gamma;
    int saturation;
    int noise_lv;
    DSP2_EE_Str_Type ee_str;
    DSP2_EE_Thresh_Type ee_th;
    DSP2_Chroma_Suppress_Type cs;
} img_porc_dsp2_cfg_t;

// TODO: use heap
static imgproc_obj_t img_proc;
static img_porc_dsp2_cfg_t dsp2_cfg;
static BL_DSP2_DAY_NIGHT_MODE_T day_night_mode = BL_DAY_MODE;

static int img_procawb_algo_new = DEFAULT_AWB_ALGO;

extern BL_EXPO_TIME sensor_expo_time;
extern BL_GAIN_DB sensor_gain;

#if PERFORMANCE_MONITOR
#define FRM_CNT_FOR_ONE_STATS     100       /* 8 sec */
static int ae_handl_cnt = 0;
static TickType_t ae_handl_start_time = 0;
#endif

void ir_cut_switch(bool enable)
{
}

static BL_Fun_Type imgproc_is_module_enable(img_param_module_t module)
{
    return (img_proc.img_param->state_tbl->state)[module];
}

static uint32_t imgproc_is_module_update(uint32_t mask)
{
    return mask & dsp2_cfg.update_mask;
}

static void imgproc_set_module_update(uint32_t mask)
{
    dsp2_cfg.update_mask |= mask;
}

static void imgproc_clear_module_update()
{
    dsp2_cfg.update_mask = 0;
}

static void imgproc_set_reg()
{
	DSP2_SATURATION_S satCfg;
	
    if (imgproc_is_module_update(IMG_UPDATE_MASK_BLC)) {
        DSP2_Set_BLC(&(dsp2_cfg.clamp));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_DPC)) {
        DSP2_Set_Defect_Correction_Threshold_Group(&(dsp2_cfg.dpc));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_DPC)) {
        DSP2_Set_Defect_Correction_Threshold_Group(&(dsp2_cfg.dpc));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_BNR)) {
        bnr_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_WB_GAIN)) {
        DSP2_Set_RB_Gain(&(dsp2_cfg.rb_gain));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_GAMMA)) {
        DSP2_Set_Gamma_Coef(&(dsp2_cfg.gamma));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_CCM)) {
        DSP2_Set_CCM_Coef(&(dsp2_cfg.ccm));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_WDR)) {
        wdr_hw_update();
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_SATURATION)) {
		if (BL_DAY_MODE == day_night_mode) {
			satCfg.saturation_cb = dsp2_cfg.saturation;
			satCfg.saturation_cr = dsp2_cfg.saturation;
			DSP2_Set_Saturation(&satCfg);
		} else {
			satCfg.saturation_cb = 0;
			satCfg.saturation_cr = 0;
			DSP2_Set_Saturation(&satCfg);
		}
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_NOISE_LEVEL)) {
        DSP2_Set_Noise_Level(dsp2_cfg.noise_lv);
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_EE)) {
        DSP2_Set_EE_Strength(&(dsp2_cfg.ee_str));
        DSP2_Set_EE_Thresh(&(dsp2_cfg.ee_th));
    }

    if (imgproc_is_module_update(IMG_UPDATE_MASK_CS)) {
        DSP2_Set_ChromaSuppress(&(dsp2_cfg.cs));
    }

    imgproc_clear_module_update();
}

static int imgproc_check_param_table()
{
    int ret = 1;

    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->ae_target_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->awb_white_region_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->wb_bias_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->wb_info_tbl->header.table));
    ret *= (DSP2_TBL_INIT \
        == (img_proc.img_param->blc_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->defect_corr_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->bnr_fw_config_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->lens_shading_corr_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_COLOR_TMPER \
        == (img_proc.img_param->color_corr_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_EV \
        == (img_proc.img_param->gamma_corr_tbl->header.table));
    ret *= (DSP2_TBL_CUSTOM_EV \
        == (img_proc.img_param->wdr_fw_config_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->saturation_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->noise_reduction_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->edge_enhance_tbl->header.table));
    ret *= (DSP2_TBL_AUTO_ISO \
        == (img_proc.img_param->cs_tbl->header.table));

    return (ret == 1) ? 0 : -1;
}

static int imgproc_check_param_policy()
{
    int ret = 1;

    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->ae_target_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->awb_white_region_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->wb_bias_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->wb_info_tbl->header.policy));
    ret *= (DSP2_POL_INIT \
        == (img_proc.img_param->blc_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->defect_corr_tbl->header.policy));
    ret *= (DSP2_POL_INIT \
        == (img_proc.img_param->bnr_fw_config_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->lens_shading_corr_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->color_corr_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->gamma_corr_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->wdr_fw_config_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->saturation_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->noise_reduction_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->edge_enhance_tbl->header.policy));
    ret *= (DSP2_POL_INTERPL \
        == (img_proc.img_param->cs_tbl->header.policy));

    return (ret == 1) ? 0 : -1;
}

static void linear_intpl_by_gain(int value_L, int value_H, BL_GAIN_DB gain, int *value_out)
{
    BL_GAIN_DB gain_L = (gain / GAIN_6_DB) * GAIN_6_DB;
    BL_GAIN_DB gain_H = gain_L + GAIN_6_DB;

    intpl_point_t point_L = create_intpl_point(gain_L, value_L);
    intpl_point_t point_H = create_intpl_point(gain_H, value_H);
    linear_interpolate(&point_L, &point_H, gain, value_out);
}

static int img_update_ae()
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AE)) {
        return -1;
    }

    ae_control();
    return 0;
}

static int img_update_ae_target(BL_GAIN_DB gain, int *ae_target)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AE)) {
        return -1;
    }

    int param_idx;
    BL_GAIN_DB gain_L, gain_H;
    int ae_target_L, ae_target_H, ae_target_new;
    intpl_point_t point_L;
    intpl_point_t point_H;

    param_idx = gain / GAIN_6_DB;

    img_param_get_ae_target(param_idx, &ae_target_L);
    img_param_get_ae_target(param_idx + 1, &ae_target_H);

    gain_L = INT_TO_GAIN_DB(param_idx * 6);
    gain_H = INT_TO_GAIN_DB((param_idx + 1) * 6);

    point_L = create_intpl_point(gain_L, ae_target_L);
    point_H = create_intpl_point(gain_H, ae_target_H);
    linear_interpolate(&point_L, &point_H, gain, &ae_target_new);

    *ae_target = ae_target_new;

//    MSG("ae_target: (%d ~ %d) -> %d\r\n", ae_target_L, ae_target_H, ae_target_new);

    return 0;
}

static int img_update_awb()
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AWB)) {
        return -1;
    }

    awb_control();
    return 0;
}

static int img_update_wb_gain(DSP2_RB_Gain_Type *rb_gain, BL_COLOR_TEMP color_temp, DSP2_RB_Gain_Type *rb_bias)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AWB)) {
        return -1;
    }

    imgproc_set_module_update(IMG_UPDATE_MASK_WB_GAIN);

    /* apply wb gain bias according to color temp thresh */
    if (color_temp <= WB_BIAS_CT_THRESH) {
        dsp2_cfg.rb_gain = *rb_gain;
    } else {
        dsp2_cfg.rb_gain.r_gain = DIV_ROUND(rb_gain->r_gain * rb_bias->r_gain, RGB_GAIN_1X);
        dsp2_cfg.rb_gain.b_gain = DIV_ROUND(rb_gain->b_gain * rb_bias->b_gain, RGB_GAIN_1X);
    }

    MSG("final wb gain: (%d, %d) -> (%d, %d)\r\n", rb_gain->r_gain, rb_gain->b_gain,
        dsp2_cfg.rb_gain.r_gain, dsp2_cfg.rb_gain.b_gain);

    return 0;
}

static int img_update_wb_bias(BL_GAIN_DB sys_gain, DSP2_RB_Gain_Type *rb_bias)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_AWB)) {
        return -1;
    }

    int wb_bias_idx;
    BL_GAIN_DB sys_gain_L, sys_gain_H;
    const wb_bais_t *wb_bias_L, *wb_bias_H;
    intpl_point_t point_L, point_H;
    int gain_tmp;
    int num_wb_bias = img_param_get_num_wb_bias();

    for (wb_bias_idx = 0; wb_bias_idx < (num_wb_bias - 1); wb_bias_idx++) {

        img_param_get_wb_bias(wb_bias_idx, &wb_bias_L);
        img_param_get_wb_bias(wb_bias_idx + 1, &wb_bias_H);

        sys_gain_L = INT_TO_GAIN_DB(wb_bias_L->sys_gain_db);
        sys_gain_H = INT_TO_GAIN_DB(wb_bias_H->sys_gain_db);

        if (sys_gain >= sys_gain_L && sys_gain <= sys_gain_H) {
            /* now we get the range of sys gain */

            /* interpolate r_gain */
            point_L = create_intpl_point(sys_gain_L, wb_bias_L->rb_gain.r_gain);
            point_H = create_intpl_point(sys_gain_H, wb_bias_H->rb_gain.r_gain);
            linear_interpolate(&point_L, &point_H, sys_gain, &gain_tmp);
            rb_bias->r_gain = gain_tmp;

            /* interpolate b_gain */
            point_L = create_intpl_point(sys_gain_L, wb_bias_L->rb_gain.b_gain);
            point_H = create_intpl_point(sys_gain_H, wb_bias_H->rb_gain.b_gain);
            linear_interpolate(&point_L, &point_H, sys_gain, &gain_tmp);
            rb_bias->b_gain = gain_tmp;
            return 0;
        }

        if (wb_bias_idx == 0 && sys_gain < sys_gain_L) {
            *rb_bias = wb_bias_L->rb_gain;
            return 0;
        }

        if (wb_bias_idx == (num_wb_bias - 2) && sys_gain > sys_gain_H) {
            *rb_bias = wb_bias_H->rb_gain;
            return 0;
        }
    }

    /* should never reach here */
    return -1;
}

static int img_update_blc()
{
    if (!imgproc_is_module_enable(DSP2_ADJ_BLC)) {
        return -1;
    }

    imgproc_set_module_update(IMG_UPDATE_MASK_BLC);
    const black_lvl_corr_t *black_lvl_corr;

    img_param_get_default_blc(&black_lvl_corr);
    dsp2_cfg.clamp.clamp_r  = black_lvl_corr->black_level;
    dsp2_cfg.clamp.clamp_gr = black_lvl_corr->black_level;
    dsp2_cfg.clamp.clamp_gb = black_lvl_corr->black_level;
    dsp2_cfg.clamp.clamp_b  = black_lvl_corr->black_level;

    return 0;
}

static int img_update_dpc(BL_GAIN_DB gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_DPC)) {
        return -1;
    }

    int param_idx;
    const defect_corr_t *defect_corr_L, *defect_corr_H;
    int defect_THR_1, defect_THR_2;

    param_idx = gain / GAIN_6_DB;
    imgproc_set_module_update(IMG_UPDATE_MASK_DPC);
//    MSG("gain %.4f dB, param_idx %d\r\n", GAIN_DB_INT_TO_FLOAT(gain), param_idx);

    img_param_get_defect_corr(param_idx, &defect_corr_L);
    img_param_get_defect_corr(param_idx + 1, &defect_corr_H);

    linear_intpl_by_gain(defect_corr_L->defect_THR_1, defect_corr_H->defect_THR_1, gain, &defect_THR_1);
    linear_intpl_by_gain(defect_corr_L->defect_THR_2, defect_corr_H->defect_THR_2, gain, &defect_THR_2);

    dsp2_cfg.dpc.data[0] = defect_THR_1;
    dsp2_cfg.dpc.data[1] = defect_THR_2;
    dsp2_cfg.dpc.data[2] = 50;
    dsp2_cfg.dpc.data[3] = 50;
    dsp2_cfg.dpc.data[4] = 20;


//    MSG("Defect corr: defect_THR_1 (%d ~ %d) -> %d, defect_THR_2 (%d ~ %d) -> %d\r\n",
//        defect_corr_L->defect_THR_1, defect_corr_H->defect_THR_1, defect_THR_1,
//        defect_corr_L->defect_THR_2, defect_corr_H->defect_THR_2, defect_THR_2);

    return 0;
}

static int img_update_bnr(BL_GAIN_DB gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_BNR)) {
        return -1;
    }

    imgproc_set_module_update(IMG_UPDATE_MASK_BNR);
    bnr_control(gain);

    return 0;
}

static int img_update_lsc(BL_COLOR_TEMP color_temp)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_LSC)) {
        return -1;
    }

    int lsc_idx, i;
    int lsc_num = img_param_get_num_lsc();
    BL_COLOR_TEMP color_temp_L, color_temp_H;
    const lens_shade_corr_t *lsc_corr_L, *lsc_corr_H;
    intpl_point_t point_L, point_H;

    imgproc_set_module_update(IMG_UPDATE_MASK_LSC);

    for (lsc_idx = 0; lsc_idx < (lsc_num - 1); lsc_idx++) {

        img_param_get_lsc(lsc_idx, &lsc_corr_L);
        img_param_get_lsc(lsc_idx + 1, &lsc_corr_H);

        color_temp_L = lsc_corr_L->color_temp;
        color_temp_H = lsc_corr_H->color_temp;

        if (color_temp >= color_temp_L && color_temp <= color_temp_H) {
            /* now we get the range of color temp */

            for (i = 0; i < LSC_COEF_NUM; i++) {
                /* interpolate each coef of LSC R */
                point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_coef_r.coef[i]);
                point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_coef_r.coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &(dsp2_cfg.lsc.lsc_coef_r.coef[i]));
            }
            for (i = 0; i < LSC_COEF_NUM; i++) {
                /* interpolate each coef of LSC G */
                point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_coef_g.coef[i]);
                point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_coef_g.coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &(dsp2_cfg.lsc.lsc_coef_g.coef[i]));
            }
            for (i = 0; i < LSC_COEF_NUM; i++) {
                /* interpolate each coef of LSC B */
                point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_coef_b.coef[i]);
                point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_coef_b.coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &(dsp2_cfg.lsc.lsc_coef_b.coef[i]));
            }

            point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_max.max_r);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_max.max_r);
            linear_interpolate(&point_L, &point_H, color_temp, &(dsp2_cfg.lsc_max.max_r));
            point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_max.max_g);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_max.max_g);
            linear_interpolate(&point_L, &point_H, color_temp, &(dsp2_cfg.lsc_max.max_g));
            point_L = create_intpl_point(color_temp_L, lsc_corr_L->lsc_max.max_b);
            point_H = create_intpl_point(color_temp_H, lsc_corr_H->lsc_max.max_b);
            linear_interpolate(&point_L, &point_H, color_temp, &(dsp2_cfg.lsc_max.max_b));

            break;
        }
        else if (lsc_idx == 0 && color_temp < color_temp_L) {
            for (i = 0; i < LSC_COEF_NUM; i++) {
                dsp2_cfg.lsc.lsc_coef_r.coef[i] = lsc_corr_L->lsc_coef_r.coef[i];
                dsp2_cfg.lsc.lsc_coef_g.coef[i] = lsc_corr_L->lsc_coef_g.coef[i];
                dsp2_cfg.lsc.lsc_coef_b.coef[i] = lsc_corr_L->lsc_coef_b.coef[i];
            }
            dsp2_cfg.lsc_max.max_r = lsc_corr_L->lsc_max.max_r;
            dsp2_cfg.lsc_max.max_g = lsc_corr_L->lsc_max.max_g;
            dsp2_cfg.lsc_max.max_b = lsc_corr_L->lsc_max.max_b;
            break;
        }
        else if (lsc_idx == (lsc_num - 2) && color_temp > color_temp_H) {
            for (i = 0; i < LSC_COEF_NUM; i++) {
                dsp2_cfg.lsc.lsc_coef_r.coef[i] = lsc_corr_H->lsc_coef_r.coef[i];
                dsp2_cfg.lsc.lsc_coef_g.coef[i] = lsc_corr_H->lsc_coef_g.coef[i];
                dsp2_cfg.lsc.lsc_coef_b.coef[i] = lsc_corr_H->lsc_coef_b.coef[i];
            }
            dsp2_cfg.lsc_max.max_r = lsc_corr_H->lsc_max.max_r;
            dsp2_cfg.lsc_max.max_g = lsc_corr_H->lsc_max.max_g;
            dsp2_cfg.lsc_max.max_b = lsc_corr_H->lsc_max.max_b;
            break;
        }
    }

//    MSG("img_update_lsc: %d, %d, %d\r\n", dsp2_cfg.lsc.lsc_coef_r.coef[0], dsp2_cfg.lsc.lsc_coef_r.coef[1],
//        dsp2_cfg.lsc.lsc_coef_r.coef[2]);

    return 0;
}

static int calc_ccm_by_color_temp(BL_COLOR_TEMP color_temp, DSP2_CCM_COEF_S *ccm)
{
    int ccm_idx, i;
    int ccm_num = img_param_get_num_color_corr();
    BL_COLOR_TEMP color_temp_L, color_temp_H;
    const color_corr_t *color_corr_L, *color_corr_H;
    intpl_point_t point_L, point_H;

    for (ccm_idx = 0; ccm_idx < (ccm_num - 1); ccm_idx++) {

        img_param_get_color_corr(ccm_idx, &color_corr_L);
        img_param_get_color_corr(ccm_idx + 1, &color_corr_H);

        color_temp_L = color_corr_L->color_temp;
        color_temp_H = color_corr_H->color_temp;

        if (color_temp >= color_temp_L && color_temp <= color_temp_H) {
            /* now we get the range of color temp */

            for (i = 0; i < CCM_COEF_NUM; i++) {
                /* interpolate each coef of CCM */
                point_L = create_intpl_point(color_temp_L, color_corr_L->ccm.ccm_coef[i]);
                point_H = create_intpl_point(color_temp_H, color_corr_H->ccm.ccm_coef[i]);
                linear_interpolate(&point_L, &point_H, color_temp, &ccm->ccm_coef[i]);
            }
            return 0;
        }
        else if (ccm_idx == 0 && color_temp < color_temp_L) {
            for (i = 0; i < CCM_COEF_NUM; i++) {
                ccm->ccm_coef[i] = color_corr_L->ccm.ccm_coef[i];
            }
            return 0;
        }
        else if (ccm_idx == (ccm_num - 2) && color_temp > color_temp_H) {
            for (i = 0; i < CCM_COEF_NUM; i++) {
                ccm->ccm_coef[i] = color_corr_H->ccm.ccm_coef[i];
            }
            return 0;
        }
    }

    /* shouldn't reach here */
    return -1;
}

static int img_update_ccm(BL_COLOR_TEMP color_temp)
{
    DSP2_CCM_COEF_S ccm;
    if (!imgproc_is_module_enable(DSP2_ADJ_CCM)) {
        for (int i = 0; i < CCM_COEF_NUM; i++) {
			ccm.ccm_coef[i] = 0;
		}
		
		ccm.ccm_coef[0] = 512;
		ccm.ccm_coef[4] = 512;
		ccm.ccm_coef[8] = 512;
		DSP2_Set_CCM_Coef(&ccm);
		
        return -1;
    }

    imgproc_set_module_update(IMG_UPDATE_MASK_CCM);
    calc_ccm_by_color_temp(color_temp, &(dsp2_cfg.ccm));
    return 0;
}

static int calc_gamma_by_sys_gain(BL_GAIN_DB sys_gain, DSP2_Gamma_Curve_Type *gamma)
{
    int i, value, gamma_idx, num_gamma;
    int ret = -1;
    BL_GAIN_DB sys_gain_L, sys_gain_H;
    const gamma_corr_t *gamma_L, *gamma_H;
    intpl_point_t point_L, point_H;

    num_gamma = img_param_get_num_gamma_corr();
    CHECK_PARAM(num_gamma >= 2);

    for (gamma_idx = 0; gamma_idx < (num_gamma - 1); gamma_idx++) {

        img_param_get_gamma_corr(gamma_idx, &gamma_L);
        img_param_get_gamma_corr(gamma_idx + 1, &gamma_H);

        sys_gain_L = INT_TO_GAIN_DB(gamma_L->sys_gain_db);
        sys_gain_H = INT_TO_GAIN_DB(gamma_H->sys_gain_db);

        if (sys_gain >= sys_gain_L && sys_gain <= sys_gain_H) {
            for (i = 0; i < GAMMA_COEF_NUM; i++) {
                /* interpolate each coef of gamma */
                point_L = create_intpl_point(sys_gain_L, gamma_L->gamma_curve.coef[i]);
                point_H = create_intpl_point(sys_gain_H, gamma_H->gamma_curve.coef[i]);
                linear_interpolate(&point_L, &point_H, sys_gain, &value);
                gamma->curve_coef[i] = value;
            }
            ret = 0;
            break;
        } else if (gamma_idx == 0 && sys_gain < sys_gain_L) {
            for (i = 0; i < GAMMA_COEF_NUM; i++) {
                gamma->curve_coef[i] = gamma_L->gamma_curve.coef[i];
            }
            ret = 0;
            break;
        } else if (gamma_idx == (num_gamma - 2) && sys_gain > sys_gain_H) {
            for (i = 0; i < GAMMA_COEF_NUM; i++) {
                gamma->curve_coef[i] = gamma_H->gamma_curve.coef[i];
            }
            ret = 0;
            break;
        }
    }

    return ret;
}

static int img_update_gamma(BL_GAIN_DB sys_gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_GAMMA)) {
        return -1;
    }

    imgproc_set_module_update(IMG_UPDATE_MASK_GAMMA);
    calc_gamma_by_sys_gain(sys_gain, &(dsp2_cfg.gamma));
    return 0;
}

static int calc_wdr_fw_config_by_sys_gain(BL_GAIN_DB sys_gain, wdr_fw_config_t *wdr_fw_config)
{
    int wdr_fw_config_idx;
    BL_GAIN_DB sys_gain_L, sys_gain_H;
    const wdr_fw_config_t *wdr_fw_config_L, *wdr_fw_config_H;
    intpl_point_t point_L, point_H;
    int num_wdr_fw_config = img_param_get_num_wdr_config();

    for (wdr_fw_config_idx = 0; wdr_fw_config_idx < (num_wdr_fw_config - 1); wdr_fw_config_idx++) {

        img_param_get_wdr_config(wdr_fw_config_idx, &wdr_fw_config_L);
        img_param_get_wdr_config(wdr_fw_config_idx + 1, &wdr_fw_config_H);

        sys_gain_L = INT_TO_GAIN_DB(wdr_fw_config_L->sys_gain_db);
        sys_gain_H = INT_TO_GAIN_DB(wdr_fw_config_H->sys_gain_db);

        if (sys_gain >= sys_gain_L && sys_gain <= sys_gain_H) {
            /* now we get the range of sys gain */

            // /* interpolate cs weight */
            point_L = create_intpl_point(sys_gain_L, wdr_fw_config_L->param.cs_weight);
            point_H = create_intpl_point(sys_gain_H, wdr_fw_config_H->param.cs_weight);
            linear_interpolate(&point_L, &point_H, sys_gain, (int *)&(wdr_fw_config->param.cs_weight));

            // /* interpolate cs gain_thresh */
            point_L = create_intpl_point(sys_gain_L, wdr_fw_config_L->param.cs_gain_thresh);
            point_H = create_intpl_point(sys_gain_H, wdr_fw_config_H->param.cs_gain_thresh);
            linear_interpolate(&point_L, &point_H, sys_gain, (int *)&(wdr_fw_config->param.cs_gain_thresh));

            /* interpolate curve_weight */
            point_L = create_intpl_point(sys_gain_L, wdr_fw_config_L->param.curve_weight);
            point_H = create_intpl_point(sys_gain_H, wdr_fw_config_H->param.curve_weight);
            linear_interpolate(&point_L, &point_H, sys_gain, (int *)&(wdr_fw_config->param.curve_weight));

            /* interpolate enh_weight */
            point_L = create_intpl_point(sys_gain_L, wdr_fw_config_L->param.enh_weight);
            point_H = create_intpl_point(sys_gain_H, wdr_fw_config_H->param.enh_weight);
            linear_interpolate(&point_L, &point_H, sys_gain, (int *)&(wdr_fw_config->param.enh_weight));

            /* interpolate enh_c_gain_extra_slope */
            point_L = create_intpl_point(sys_gain_L, wdr_fw_config_L->param.enh_c_gain_extra_slope);
            point_H = create_intpl_point(sys_gain_H, wdr_fw_config_H->param.enh_c_gain_extra_slope);
            linear_interpolate(&point_L, &point_H, sys_gain, (int *)&(wdr_fw_config->param.enh_c_gain_extra_slope));
            return 0;
        }

        if (wdr_fw_config_idx == 0 && sys_gain < sys_gain_L) {
            *wdr_fw_config = *wdr_fw_config_L;
            return 0;
        }

        if (wdr_fw_config_idx == (num_wdr_fw_config - 2) && sys_gain > sys_gain_H) {
            *wdr_fw_config = *wdr_fw_config_H;
            return 0;
        }
    }

    /* should never reach here */
    return -1;
}

static int img_update_wdr(BL_GAIN_DB sys_gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_WDR)) {
        return -1;
    }

    wdr_fw_config_t wdr_fw_config;
    imgproc_set_module_update(IMG_UPDATE_MASK_WDR);
    calc_wdr_fw_config_by_sys_gain(sys_gain, &wdr_fw_config);
    wdr_control(&wdr_fw_config);

    return 0;
}

static int img_update_saturation(BL_GAIN_DB gain)
{
	DSP2_SATURATION_S satCfg;
	
    if (!imgproc_is_module_enable(DSP2_ADJ_SATURATION)) {
        satCfg.saturation_cb = 0;
		satCfg.saturation_cr = 0;
		DSP2_Set_Saturation(&satCfg);
		
        return -1;
    }

    int param_idx;
    const saturation_t *saturation_L, *saturation_H;

    param_idx = gain / GAIN_6_DB;
    imgproc_set_module_update(IMG_UPDATE_MASK_SATURATION);

    img_param_get_saturation(param_idx, &saturation_L);
    img_param_get_saturation(param_idx + 1, &saturation_H);

    linear_intpl_by_gain(saturation_L->value, saturation_H->value, gain, &(dsp2_cfg.saturation));

//    MSG("saturation: (%d ~ %d) -> %d\r\n", saturation_L, saturation_H, saturation_new);

    return 0;
}

static int img_set_default_ee_luma_weight(void)
{
    int i;
    const ee_luma_wgt_t *lumaWgt;
    DSP2_EE_Luma_Weight_Type lumaWgtCfg;

    img_param_get_default_EE_luma_weight(&lumaWgt);

    for (i = 0; i < DSP2_EE_LUMA_WEIGHT_NUM; i ++) {
        lumaWgtCfg.lumaWgtTbl[i] = lumaWgt->lumaWgtTbl[i];
    }

    DSP2_Set_EE_LumaWeight(&lumaWgtCfg);

    return 0;
}

static int img_update_ee(BL_GAIN_DB gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_EE)) {
        return -1;
    }

    int param_idx;
    const edge_enhance_t *edge_enhance_L, *edge_enhance_H;
    int value;

    param_idx = gain / GAIN_6_DB;
    imgproc_set_module_update(IMG_UPDATE_MASK_EE);

    img_param_get_edge_enhance(param_idx, &edge_enhance_L);
    img_param_get_edge_enhance(param_idx + 1, &edge_enhance_H);

    linear_intpl_by_gain(edge_enhance_L->posEdgeStr, edge_enhance_H->posEdgeStr, gain, &value);
    dsp2_cfg.ee_str.posEdgeStr = value;
    linear_intpl_by_gain(edge_enhance_L->negEdgeStr, edge_enhance_H->negEdgeStr, gain, &value);
    dsp2_cfg.ee_str.negEdgeStr = value;
    linear_intpl_by_gain(edge_enhance_L->posEdgeOvrshtStr, edge_enhance_H->posEdgeOvrshtStr, gain, &value);
    dsp2_cfg.ee_str.posEdgeOvrshtStr = value;
    linear_intpl_by_gain(edge_enhance_L->negEdgeOvrshtStr, edge_enhance_H->negEdgeOvrshtStr, gain, &value);
    dsp2_cfg.ee_str.negEdgeOvrshtStr = value;
    linear_intpl_by_gain(edge_enhance_L->nrStr, edge_enhance_H->nrStr, gain, &value);
    dsp2_cfg.ee_str.nrStr = value;
    linear_intpl_by_gain(edge_enhance_L->dirShpnessThresh, edge_enhance_H->dirShpnessThresh, gain, &value);
    dsp2_cfg.ee_th.dirShpnessThresh = value;
    linear_intpl_by_gain(edge_enhance_L->noDirShpnessThresh, edge_enhance_H->noDirShpnessThresh, gain, &value);
    dsp2_cfg.ee_th.noDirShpnessThresh = value;
    linear_intpl_by_gain(edge_enhance_L->flatThresh, edge_enhance_H->flatThresh, gain, &value);
    dsp2_cfg.ee_th.flatThresh = value;
    linear_intpl_by_gain(edge_enhance_L->textureThresh, edge_enhance_H->textureThresh, gain, &value);
    dsp2_cfg.ee_th.textureThresh = value;
    linear_intpl_by_gain(edge_enhance_L->edgeThresh, edge_enhance_H->edgeThresh, gain, &value);
    dsp2_cfg.ee_th.edgeThresh = value;
//    MSG("EE: noise_thresh (%d ~ %d) -> %d\r\n", edge_enhance_L->noise_thresh, edge_enhance_H->noise_thresh, noise_thresh);

    return 0;
}

static int img_update_nr(BL_GAIN_DB gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_NR)) {
        DSP2_Set_Noise_Level(0);
        return -1;
    }

    int param_idx;
    const noise_reduction_t *noise_reduct_L, *noise_reduct_H;

    param_idx = gain / GAIN_6_DB;
    imgproc_set_module_update(IMG_UPDATE_MASK_NOISE_LEVEL);

    img_param_get_noise_reduction(param_idx, &noise_reduct_L);
    img_param_get_noise_reduction(param_idx + 1, &noise_reduct_H);

    linear_intpl_by_gain(noise_reduct_L->noise_level, noise_reduct_H->noise_level, gain, &(dsp2_cfg.noise_lv));
//    MSG("NR: noise_level (%d ~ %d) -> %d\r\n", noise_reduct_L->noise_level, noise_reduct_H->noise_level, noise_level);

    return 0;
}

static int img_update_cs(BL_GAIN_DB gain)
{
    if (!imgproc_is_module_enable(DSP2_ADJ_CS)) {
        return -1;
    }

    int param_idx, value, divisor;
    const chroma_suppress_t *chroma_suppress_L, *chroma_suppress_H;

    param_idx = gain / GAIN_6_DB;
    imgproc_set_module_update(IMG_UPDATE_MASK_CS);

    img_param_get_chroma_suppress(param_idx, &chroma_suppress_L);
    img_param_get_chroma_suppress(param_idx + 1, &chroma_suppress_H);

    linear_intpl_by_gain(chroma_suppress_L->weight, chroma_suppress_H->weight, gain, &value);
    dsp2_cfg.cs.weight = value;
    linear_intpl_by_gain(chroma_suppress_L->gain_thresh, chroma_suppress_H->gain_thresh, gain, &value);
    dsp2_cfg.cs.gain_thresh = value;

    // ref to wdr
    divisor = (1 << (8 - 1)) - dsp2_cfg.cs.gain_thresh;
    dsp2_cfg.cs.gain = ((1 << (8 - 1)) * (1 << 8) + (divisor - 1)) / divisor;

    return 0;
}

static void imgproc_set_init_only_module()
{
    img_update_blc();
}

static int img_set_module_param(void)
{
    uint8_t nr_str;
    const bnr_fw_config_t *config;

    img_param_get_bnr_config(&config);
    bnr_config(config);

    img_param_get_default_2DNR_str(&nr_str);
    DSP2_Set_2D_NR(nr_str);

    img_param_get_default_3DNR_str(&nr_str);
#if ENABLE_3DNR
    DSP2_Set_3D_NR(nr_str);
#endif

    img_set_default_ee_luma_weight();

    return 0;
}

static bool imgproc_is_update_force()
{
    return ((0 != img_proc.update_force)? true: false);
}

static void imgproc_update_down()
{
    if (img_proc.update_force > 0) {
        img_proc.update_force--;
    }
}

// only for debug mode
int imgproc_update_force()
{
    img_proc.update_force = 3;
    return 0;
}

static int imgproc_is_boot_frame()
{
    if (0 != img_proc.start_skip_num && img_proc.start_skip_num-- > 0) {
        return 1;
    }

    return 0;
}


static int imgproc_is_skip_frame(int *count)
{
    if ((*count)++ < img_proc.skip_num - 1) {
        return 1;
    }

    *count = 0;
    return 0;
}

static void imgproc_set_interrupt(BL_Fun_Type state)
{//Todo
    if (DISABLE == state) {
//        CPU_Interrupt_Disable(AE_STATS_IRQn);
//        CPU_Interrupt_Disable(AWB_STATS_IRQn);
//        CPU_Interrupt_Disable(AWB2_STATS_IRQn);
//        CPU_Interrupt_Disable(WDR_STATS_IRQn);
//
//        CPU_Interrupt_Disable(SEOF1_IRQn);
//        CPU_Interrupt_Disable(SEOF2_IRQn);
//        CPU_Interrupt_Disable(SEOF3_IRQn);
    }
    else {
//        CPU_Interrupt_Enable(AE_STATS_IRQn);
//            if (AWB_ALGO_1 == img_proc.awb_algo) {
//                CPU_Interrupt_Enable(AWB_STATS_IRQn);
//            }
//            else if (AWB_ALGO_2 == img_proc.awb_algo) {
//                CPU_Interrupt_Enable(AWB2_STATS_IRQn);
//            }
//            else {
//                MSG("AWB algo NOT Support!\r\n");
//            }
//        CPU_Interrupt_Enable(WDR_STATS_IRQn);
//
//        CPU_Interrupt_Enable(SEOF1_IRQn);
//        CPU_Interrupt_Enable(SEOF2_IRQn);
//        CPU_Interrupt_Enable(SEOF3_IRQn);
    }
}

void imgproc_dbg_set_awb_algo(AWB_ALGO algo)
{
    img_procawb_algo_new = algo;
}

int imgproc_init(void)
{
    int ret;

    memset(&img_proc, 0, sizeof(img_proc));
    memset(&dsp2_cfg, 0, sizeof(dsp2_cfg));

    ret = img_param_get_module(&(img_proc.img_param));
    if (-1 == ret) {
        MSG("improc: Get sensor param failed!\n");
    }

    ret = imgproc_check_param_table();
    if (-1 == ret) {
        MSG("improc: Please check module table!\n");
    }

    ret = imgproc_check_param_policy();
    if (-1 == ret) {
        MSG("improc: Please check module policy!\n");
    }

    img_proc.skip_num = IMG_PROC_SKIP_NUM;
    img_proc.start_skip_num  = IMG_START_SKIP_NUM;
    img_proc.awb_algo = img_procawb_algo_new;

    imgproc_set_interrupt(DISABLE);

    ae_init();
    awb_init(img_proc.awb_algo);
    wdr_init();
    bnr_init();
    //ir_board_config();
    //sensor_board_config();

    return 0;
}

int imgproc_bind_sensor_model(const char* sensor_name)
{
    return img_param_load(sensor_name);
}

int imgproc_set_config(img_proc_cfg_t *cfg, bool is_virtual_sensor)
{
    ae_config_t  ae_cfg;
    awb_config_t awb_cfg;
    wdr_config_t wdr_cfg;

    memcpy(&(ae_cfg.stats_cfg),  &(cfg->stats_cfg), sizeof(aaa_stats_cfg_t));
    memcpy(&(awb_cfg.stats_cfg), &(cfg->stats_cfg), sizeof(aaa_stats_cfg_t));
    memcpy(&(wdr_cfg.stats_cfg), &(cfg->stats_cfg), sizeof(aaa_stats_cfg_t));

    if (ae_config(&ae_cfg, is_virtual_sensor) < 0)
        return -1;

    if (awb_config(&awb_cfg, is_virtual_sensor) < 0)
        return -1;

    if (wdr_config(&wdr_cfg, is_virtual_sensor) < 0)
        return -1;

    img_set_module_param();

    return 0;
}

void vImageControlTask(void)
{
    int skip_cnt = img_proc.skip_num;

    ae_info_t  *ae_info;
    awb_info_t *awb_info;
    ae_get_info(&ae_info);
    awb_get_info(&awb_info);

    imgproc_update_force();
    imgproc_set_init_only_module();

    /* interrupts should be enabled after scheduler is started,
        otherwise deferring any work in ISR to Daemon task will assert */

    imgproc_set_interrupt(ENABLE);

    //while (!img_proc.stop_imgproc_flag) {

        if (imgproc_is_skip_frame(&skip_cnt)) {
            //continue;
        }

        img_update_ae();
        img_update_awb();

        if (imgproc_is_boot_frame()) {
            //continue;
        }

         if (ae_info->expo_time_update || imgproc_is_update_force()) {
             if (ae_info->ae_mode != AE_MODE_DBG_VIRTUAL) {
                 sensor_expo_time = ae_info->expo_time;
             }
         }
         if (ae_info->iso_update || imgproc_is_update_force()) {
             if (ae_info->ae_mode != AE_MODE_DBG_VIRTUAL) {
                 sensor_gain = ae_info->iso;
             }
         }

        if (ae_info->sys_gain_update || imgproc_is_update_force()) {
            img_update_wdr(ae_info->sys_gain);
            if (AWB_ALGO_1 == img_proc.awb_algo) {
                img_update_wb_bias(ae_info->sys_gain, &(awb_info->rb_bias));
            }
            img_update_gamma(ae_info->sys_gain);
        }

        if (ae_info->iso_update || imgproc_is_update_force()) {
            img_update_ae_target(ae_info->iso, &(ae_info->luma_target));
            img_update_dpc(ae_info->iso);
            img_update_bnr(ae_info->iso);
            img_update_cs(ae_info->iso);
            img_update_ee(ae_info->iso);
            img_update_nr(ae_info->iso);
            img_update_saturation(ae_info->iso);
        }

        if (awb_info->rb_gain_update || imgproc_is_update_force()) {
            if (AWB_ALGO_1 == img_proc.awb_algo) {
                img_update_wb_gain(&(awb_info->rb_gain), awb_info->color_temp, &(awb_info->rb_bias));
            }
        }

       if (awb_info->ct_update || imgproc_is_update_force()) {
           img_update_ccm(awb_info->color_temp);
           img_update_lsc(awb_info->color_temp);
       }

        imgproc_set_reg();

        imgproc_update_down();

        //imgproc_night_mode_enable(true);

#if PERFORMANCE_MONITOR
        do_frame_rate_stats("img handl", &ae_handl_cnt, FRM_CNT_FOR_ONE_STATS, &ae_handl_start_time);
#endif
    //}
}

void imgproc_night_mode_enable(bool enable)
{
    static bool pre_state;

    if (enable != pre_state) {
        ir_cut_switch(enable);
        day_night_mode = (enable ? BL_NIGHT_MODE : BL_DAY_MODE);
        pre_state = enable;
        MSG("night mode %d\r\n", enable);
    }
}

int imgproc_start(void)
{
    img_proc.stop_imgproc_flag = 0;
    vImageControlTask();

    return 0;
}

int imgproc_stop(void)
{
    img_proc.stop_imgproc_flag = 1;

    return 0;
}
