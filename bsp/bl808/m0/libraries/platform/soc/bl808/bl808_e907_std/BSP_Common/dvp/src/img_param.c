#include <string.h>
#include "img_param.h"

extern BL_IMG_PARAM_DESC_T _ld_bl_img_param_desc_start;
extern BL_IMG_PARAM_DESC_T _ld_bl_img_param_desc_end;


#define PARAM_IDX_MIN  0
#define PARAM_EDGE_ENHANCE_IDX_MAX  (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_NR_IDX_MAX            (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_DEFECT_CORR_IDX_MAX   (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_SATURATION_IDX_MAX    (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_AE_TARGET_IDX_MAX     (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)
#define PARAM_WDR_CONFIG_IDX_MAX    (MAX_ENTRY_NUM_AE_ISO_AUTO - 1)

static BL_IMG_PARAM_DESC_T *img_param = NULL;

#if 0
typedef struct _img_param_lut {
    BL_SENSOR_UID_E sensor_uid;
    BL_IMG_PARAM_DESC_T *img_param;
} img_param_lut_t;

static const img_param_lut_t img_param_lut[] = {
    {SENSOR_UID_SC1245, &sc1245_img_param},
    {SENSOR_UID_SC2232, &sc2232_img_param},
    {SENSOR_UID_OV9732, &ov9732_img_param},
};

static BL_IMG_PARAM_DESC_T* find_img_param(BL_SENSOR_UID_E sensor_uid)
{
    int i;
    for (i = 0; i < sizeof(img_param_lut)/sizeof(img_param_lut[0]); i++) {
        if (sensor_uid == img_param_lut[i].sensor_uid) {
            return img_param_lut[i].img_param;
        }
    }

    return NULL;
}
#endif

static int img_param_get_index(int value, int min, int max)
{
    int index = value;
    if (!is_param_valid(index, min, max)) {
        clip_param_range(&index, min, max);
        // MSG("img_param_get_index: invalid param idx %d, clip to %d\r\n", value, index);
    }

    return index;
}

int img_param_init(BL_IMG_PARAM_DESC_T *imgParam)
{
    img_param = imgParam;
    return 0;
}

int img_param_load(const char* sensor_name)
{
    BL_IMG_PARAM_DESC_T *start, *end;

    start = &_ld_bl_img_param_desc_start;
    end = &_ld_bl_img_param_desc_end;

    while (start < end) {
        MSG("try matching the img param desc [%s]\r\n", start->name);
        if(0 == strcmp(sensor_name, start->name)) {
            img_param = start;
            return 0;
        }
        start++;
    }

    return -1;
}

int img_param_get_module(const BL_IMG_PARAM_DESC_T **module)
{
    if (NULL == img_param) {
        MSG("img_param not init!");
        return -1;
    }

    *module = img_param;
    return 0;
}

int img_param_get_states(const BL_Fun_Type **state)
{
    *state = img_param->state_tbl->state;

    return 0;
}

int img_param_get_default_blc(const black_lvl_corr_t **blcCfg)
{
    *blcCfg = &img_param->blc_tbl->black_lvl_corr;

    return 0;
}

int img_param_get_chroma_suppress(int param_idx, const chroma_suppress_t **csCfg)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_NR_IDX_MAX);
    *csCfg = &img_param->cs_tbl->csCfg[index];

    return 0;
}

int img_param_get_default_EE_luma_weight(const ee_luma_wgt_t **lumaWgtTbl)
{
    *lumaWgtTbl = &img_param->edge_enhance_tbl->lumaWgtTbl;

    return 0;
}

int img_param_get_wdr_config(int param_idx, const wdr_fw_config_t **wdr_fw_config)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->wdr_fw_config_tbl->num_wdr_fw_config-1);
    *wdr_fw_config = &img_param->wdr_fw_config_tbl->wdr_fw_config[index];

    MSG("img_param_get_wdr_config: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_wdr_config(void)
{
    return img_param->wdr_fw_config_tbl->num_wdr_fw_config;
}

int img_param_get_bnr_config(const bnr_fw_config_t **bnr_fw_config)
{
    *bnr_fw_config = &img_param->bnr_fw_config_tbl->bnr_fw_config;

    return 0;
}

int img_param_get_edge_enhance(int param_idx, const edge_enhance_t **edge_enhance)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_EDGE_ENHANCE_IDX_MAX);
    *edge_enhance = &img_param->edge_enhance_tbl->edgeEnhance[index];

    MSG("img_param_get_edge_enhance: idx %d\r\n", index);

    return 0;
}

int img_param_get_noise_reduction(int param_idx, const noise_reduction_t **noise_reduct)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_NR_IDX_MAX);
    *noise_reduct = &img_param->noise_reduction_tbl->noise_reduction[index];

    MSG("img_param_get_noise_reduction: idx %d\r\n", index);

    return 0;
}

int img_param_get_default_2DNR_str(uint8_t *nr2d_str)
{
    *nr2d_str = img_param->noise_reduction_tbl->filt_str_2d;

    return 0;
}

int img_param_get_default_3DNR_str(uint8_t *nr3d_str)
{
    *nr3d_str = img_param->noise_reduction_tbl->filt_str_3d;

    return 0;
}

int img_param_get_manual_wb_info(int param_idx, const wb_info_t **wb_info)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->wb_info_tbl->num_wb_info-1);
    *wb_info = &img_param->wb_info_tbl->wb_info[index];

    MSG("img_param_get_manual_wb_info: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_manual_wb_info(void)
{
    return img_param->wb_info_tbl->num_wb_info;
}

int img_param_get_wb_bias(int param_idx, const wb_bais_t **wb_bias)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->wb_bias_tbl->num_wb_bias-1);
    *wb_bias = &img_param->wb_bias_tbl->wb_bias[index];

    MSG("img_param_get_wb_bias: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_wb_bias(void)
{
    return img_param->wb_bias_tbl->num_wb_bias;
}

int img_param_get_lsc(int param_idx, const lens_shade_corr_t **ls_corr)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->lens_shading_corr_tbl->num_lsc-1);
    *ls_corr = &img_param->lens_shading_corr_tbl->lens_shading_corr[index];

    MSG("img_param_get_noise_reduction: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_lsc(void)
{
    return img_param->lens_shading_corr_tbl->num_lsc;
}

int img_param_get_gamma_corr(int param_idx, const gamma_corr_t **gamma_corr)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->gamma_corr_tbl->num_gamma_corr-1);
    *gamma_corr = &img_param->gamma_corr_tbl->gamma_corr[index];

    MSG("img_param_get_gamma_corr: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_gamma_corr(void)
{
    return img_param->gamma_corr_tbl->num_gamma_corr;
}

int img_param_get_defect_corr(int param_idx, const defect_corr_t **defect_corr)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_DEFECT_CORR_IDX_MAX);
    *defect_corr = &img_param->defect_corr_tbl->defect_corr[index];

    MSG("img_param_get_defect_corr: idx %d\r\n", index);

    return 0;
}

int img_param_get_color_corr(int param_idx, const color_corr_t **color_corr)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->color_corr_tbl->num_color_corr-1);
    *color_corr = &img_param->color_corr_tbl->color_corr[index];

    MSG("img_param_get_color_corr: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_color_corr(void)
{
    return img_param->color_corr_tbl->num_color_corr;
}

int img_param_get_saturation(int param_idx, const saturation_t **saturation)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_SATURATION_IDX_MAX);
    *saturation = &img_param->saturation_tbl->saturation[index];

    MSG("img_param_get_saturation: idx %d\r\n", index);

    return 0;
}

int img_param_get_white_region(int param_idx, const white_region_t **region)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, img_param->awb_white_region_tbl->num_white_region-1);
    *region = &img_param->awb_white_region_tbl->white_region[index];

    MSG("img_param_get_white_region: idx %d\r\n", index);

    return 0;
}

int img_param_get_num_white_region(void)
{
    return img_param->awb_white_region_tbl->num_white_region;
}

int img_param_get_ae_target(int param_idx, int *ae_target)
{
    int index = img_param_get_index(param_idx, PARAM_IDX_MIN, PARAM_AE_TARGET_IDX_MAX);

    *ae_target = img_param->ae_target_tbl->ae_target[index];

    MSG("img_param_get_ae_target: idx %d\r\n", index);

    return 0;
}

