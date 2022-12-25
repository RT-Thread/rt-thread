#ifndef __IMG_STRUCT_H__
#define __IMG_STRUCT_H__

#include <bl808.h>
#include <bl808_dsp2.h>
#include "bl_comm_sns.h"

#define MAX_ENTRY_NUM_AE_ISO_AUTO           (10)
#define MAX_ENTRY_NUM_LSC	                (2)
#define MAX_ENTRY_NUM_GAMMA_CORR            (2)
#define MAX_ENTRY_NUM_COLOR_CORR	        (5)
#define MAX_ENTRY_NUM_AWB_WHITE_REGION	    (6)
#define MAX_ENTRY_NUM_EE_LUMA_WEIGHT        (32)
#define VERT_NUM                            (6)

typedef enum {
    ISO_AUTO          = 0,
    ISO_100_0DB       = 0,  // 0 DB
    ISO_200_6DB       = 6,  // 6 DB
    ISO_400_12DB      = 12, // 12DB
    ISO_800_18DB      = 18, // 18DB
    ISO_1600_24DB     = 24, // 24DB
    ISO_3200_30DB     = 30, // 30DB
    ISO_6400_36DB     = 36, // 36DB
    ISO_12800_42DB    = 42, // 42DB
    ISO_25600_48DB    = 48, // 48DB
    ISO_51200_54DB    = 54, // 54DB
    ISO_102400_60DB   = 60, // 60DB
    ISO_204800_66DB   = 66, // 66DB
    ISO_409600_72DB   = 72, // 72DB
    ISO_CUSTOM
}ae_iso_mode_t;

typedef enum {
    WB_AUTO,
    WB_H_2300K     = 2300,
    WB_A_2800K     = 2800,
    WB_TL84_4000K  = 4000,
    WB_CWF_4150K   = 4150,
    WB_D50_5000K   = 5000,
    WB_D65_6500K   = 6500,
    WB_D75_7500K   = 7500,
    WB_CUSTOM
}awb_color_temper_mode_t;

typedef enum {
    DSP2_ADJ_AE = 0,
    DSP2_ADJ_AE_TARGET,
    DSP2_ADJ_AWB,
    DSP2_ADJ_AWB_GAIN,
    DSP2_ADJ_AWB_BIAS,
    DSP2_ADJ_AWB_REGION,
    DSP2_ADJ_BLC,
    DSP2_ADJ_DPC,
    DSP2_ADJ_BNR,
    DSP2_ADJ_LSC,
    DSP2_ADJ_CCM,
    DSP2_ADJ_GAMMA,
    DSP2_ADJ_WDR,
    DSP2_ADJ_SATURATION,
    DSP2_ADJ_NR,
    DSP2_ADJ_EE,
    DSP2_ADJ_CS,
    DSP2_ADJ_PARAM_NUM
}img_param_module_t;

typedef enum {
    DSP2_POL_INIT = 0,
    DSP2_POL_INTERPL,
    DSP2_POL_NUM
}img_param_policy_t;

typedef enum {
    DSP2_TBL_AUTO_ISO = 0,
    DSP2_TBL_AUTO_COLOR_TMPER,
    DSP2_TBL_CUSTOM_ISO,
    DSP2_TBL_CUSTOM_COLOR_TMPER,
    DSP2_TBL_CUSTOM_EV,
    DSP2_TBL_INIT,
}img_param_table_t;


// tips for IQ tunner
typedef struct  {
    img_param_module_t module;
    img_param_policy_t policy;
    img_param_table_t  table;
} img_param_header_t;


typedef struct  {
    BL_Fun_Type state[DSP2_ADJ_PARAM_NUM];
} img_param_state_container_t;

/*********************************************************/
/****************** AE PARAM TYPE ***********************/

typedef struct {
    img_param_header_t header;
    int ae_target[MAX_ENTRY_NUM_AE_ISO_AUTO];
} ae_target_container_t;

/*********************************************************/
/****************** AWB PARAM TYPE ***********************/

// AWB Gain
typedef struct blWB_INFO_S {
    DSP2_RB_Gain_Type rb_gain;
    BL_COLOR_TEMP color_temp;
} wb_info_t;

typedef struct {
    img_param_header_t header;
    int num_wb_info;
    const wb_info_t *wb_info;
} wb_info_container_t;

// AWB Bais
typedef struct blWB_BIAS_S {
    DSP2_RB_Gain_Type rb_gain;
    int sys_gain_db;
} wb_bais_t;

typedef struct {
    img_param_header_t header;
    int num_wb_bias;
    const wb_bais_t *wb_bias;
} wb_bias_container_t;

// AWB White Region
typedef struct blVERTEX_S {
    int vertx;
    int verty;
} vertex_t;

typedef struct {
    union {
        uint32_t    data[VERT_NUM * 2];
        vertex_t    vert_array[VERT_NUM];
    } hexagon;
    int             weight;
    BL_COLOR_TEMP   color_temp;
} white_region_t;

typedef struct {
    img_param_header_t header;
    int num_white_region;
    const white_region_t *white_region;
} white_region_container_t;

/*********************************************************/
/****************** BLC PARAM TYPE ***********************/

typedef struct {
    uint32_t black_level;
} black_lvl_corr_t;

typedef struct {
    img_param_header_t header;
    black_lvl_corr_t black_lvl_corr;
} black_lvl_corr_container_t;

/*********************************************************/
/****************** DPC PARAM TYPE ***********************/

typedef struct {
    uint16_t th_base_r;
    uint16_t th_base_g;
    uint16_t th_base_b;
    uint16_t th_slope_r;
    uint16_t th_slope_g;
    uint16_t th_slope_b;
} bnr_fw_config_t;

typedef struct {
    img_param_header_t header;
    bnr_fw_config_t bnr_fw_config;
} bnr_fw_config_container_t;

/*********************************************************/

/*********************************************************/
/****************** BNR PARAM TYPE ***********************/

typedef struct {
    uint8_t defect_THR_1;
    uint8_t defect_THR_2;
} defect_corr_t;

typedef struct {
    img_param_header_t header;
    defect_corr_t defect_corr[MAX_ENTRY_NUM_AE_ISO_AUTO];
} defect_corr_container_t;

/*********************************************************/

/*********************************************************/
/****************** LSC PARAM TYPE ***********************/

typedef struct {
    int16_t coef[LSC_COEF_NUM];
} lsc_coef_t;

typedef struct {
    uint16_t max_r;
    uint16_t max_g;
    uint16_t max_b;
} lsc_max_t;

typedef struct blLSC_S {
    lsc_coef_t lsc_coef_r;
    lsc_coef_t lsc_coef_g;
    lsc_coef_t lsc_coef_b;
    lsc_max_t lsc_max;
    BL_COLOR_TEMP color_temp;
} lens_shade_corr_t;

typedef struct {
    img_param_header_t header;
    int num_lsc;
    const lens_shade_corr_t *lens_shading_corr;
} lens_shade_corr_container_t;

/****************** CCM PARAM TYPE ***********************/

typedef struct {
    int16_t ccm_coef[CCM_COEF_NUM];
} ccm_t;

typedef struct {
    ccm_t ccm;
    BL_COLOR_TEMP color_temp;
} color_corr_t;

typedef struct {
    img_param_header_t header;
    int num_color_corr;
    const color_corr_t *color_corr;
} color_corr_container_t;

/*********************************************************/
/****************** GAMMA PARAM TYPE *********************/

typedef struct {
    int16_t coef[GAMMA_COEF_NUM];
} gamma_curve_t;

typedef struct {
    gamma_curve_t gamma_curve;
    int sys_gain_db;
} gamma_corr_t;

typedef struct {
    img_param_header_t header;
    int num_gamma_corr;
    const gamma_corr_t *gamma_corr;
} gamma_corr_container_t;

/*********************************************************/
/******************* WDR PARAM TYPE **********************/

typedef struct {
    int cs_weight;
    int cs_gain_thresh;
    int curve_weight;
    int enh_weight;
    int enh_c_gain_extra_slope;
} wdr_param_t;

typedef struct {
    wdr_param_t param;
    int sys_gain_db;
} wdr_fw_config_t;

typedef struct {
    img_param_header_t header;
    int num_wdr_fw_config;
    const wdr_fw_config_t *wdr_fw_config;;
} wdr_fw_config_container_t;

/*********************************************************/
/**************** SATURATION PARAM TYPE ******************/

typedef struct blSATURATION_S {
    uint8_t value;
} saturation_t;

typedef struct {
    img_param_header_t header;
    saturation_t saturation[MAX_ENTRY_NUM_AE_ISO_AUTO];
} saturation_container_t;

/*********************************************************/
/******************** NR PARAM TYPE **********************/

typedef struct _noise_reduction {
    uint8_t noise_level;
} noise_reduction_t;

typedef struct {
    img_param_header_t header;
    noise_reduction_t noise_reduction[MAX_ENTRY_NUM_AE_ISO_AUTO];
    uint8_t filt_str_2d;
    uint8_t filt_str_3d;
} noise_reduct_container_t;

/*********************************************************/
/******************** EE PARAM TYPE **********************/

typedef struct {
    uint8_t posEdgeStr;
    uint8_t negEdgeStr;
    uint8_t posEdgeOvrshtStr;
    uint8_t negEdgeOvrshtStr;
    uint8_t nrStr;
    uint8_t dirShpnessThresh;
    uint8_t noDirShpnessThresh;
    uint8_t flatThresh;
    uint16_t textureThresh;
    uint16_t edgeThresh;
} edge_enhance_t;

typedef struct {
    uint16_t lumaWgtTbl[MAX_ENTRY_NUM_EE_LUMA_WEIGHT];
} ee_luma_wgt_t;

typedef struct {
    img_param_header_t header;
    edge_enhance_t edgeEnhance[MAX_ENTRY_NUM_AE_ISO_AUTO];
    ee_luma_wgt_t lumaWgtTbl;
} edge_enhance_container_t;

/*********************************************************/
/******************** CS PARAM TYPE **********************/
typedef struct {
    int weight;
    int gain_thresh;
} chroma_suppress_t;

typedef struct {
    img_param_header_t header;
    chroma_suppress_t csCfg[MAX_ENTRY_NUM_AE_ISO_AUTO];
} chroma_suppress_container_t;

/*********************************************************/
/************ IMG PARAM DESCRIPTION **********************/

typedef struct {
    const char* name;
    const img_param_state_container_t *state_tbl;
    const ae_target_container_t       *ae_target_tbl;
    const wb_info_container_t         *wb_info_tbl;
    const wb_bias_container_t         *wb_bias_tbl;
    const white_region_container_t    *awb_white_region_tbl;
    const black_lvl_corr_container_t  *blc_tbl;
    const defect_corr_container_t     *defect_corr_tbl;
    const bnr_fw_config_container_t   *bnr_fw_config_tbl;
    const lens_shade_corr_container_t *lens_shading_corr_tbl;
    const color_corr_container_t      *color_corr_tbl;
    const gamma_corr_container_t      *gamma_corr_tbl;
    const wdr_fw_config_container_t   *wdr_fw_config_tbl;
    const saturation_container_t      *saturation_tbl;
    const noise_reduct_container_t    *noise_reduction_tbl;
    const edge_enhance_container_t    *edge_enhance_tbl;
    const chroma_suppress_container_t *cs_tbl;
} BL_IMG_PARAM_DESC_T;


#define ATTR_IMG_PARAM_DESC_TABLE __attribute__((section(".img_param_desc")))  __attribute__((used))


#endif /* __IMG_STRUCT_H__ */

