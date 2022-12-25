#ifndef __IMG_PARAM_H__
#define __IMG_PARAM_H__

#include "bl_comm_sns.h"
#include "img_struct.h"


// extern BL_IMG_PARAM_DESC_T sc1245_img_param;
// extern BL_IMG_PARAM_DESC_T sc2232_img_param;
// extern BL_IMG_PARAM_DESC_T ov9732_img_param;

int img_param_init(BL_IMG_PARAM_DESC_T *imgParam);
int img_param_load(const char* sensor_name);
int img_param_get_module(const BL_IMG_PARAM_DESC_T **module);
int img_param_get_states(const BL_Fun_Type **state);

int img_param_get_chroma_suppress(int param_idx, const chroma_suppress_t **csCfg);
int img_param_get_default_EE_luma_weight(const ee_luma_wgt_t **lumaWgtTbl);
int img_param_get_default_blc(const black_lvl_corr_t **blcCfg);
int img_param_get_edge_enhance(int param_idx, const edge_enhance_t **edge_enhance);
int img_param_get_noise_reduction(int param_idx, const noise_reduction_t **noise_reduct);
int img_param_get_default_2DNR_str(uint8_t *nr2d_str);
int img_param_get_default_3DNR_str(uint8_t *nr3d_str);
int img_param_get_manual_wb_info(int param_idx, const wb_info_t **wb_info);
int img_param_get_num_manual_wb_info(void);
int img_param_get_wb_bias(int param_idx, const wb_bais_t **wb_bias);
int img_param_get_num_wb_bias(void);
int img_param_get_lsc(int param_idx, const lens_shade_corr_t **ls_corr);
int img_param_get_num_lsc(void);
int img_param_get_gamma_corr(int param_idx, const gamma_corr_t **gamma_corr);
int img_param_get_num_gamma_corr(void);
int img_param_get_defect_corr(int param_idx, const defect_corr_t **defect_corr);
int img_param_get_color_corr(int param_idx, const color_corr_t **color_corr);
int img_param_get_num_color_corr(void);
int img_param_get_white_region(int param_idx, const white_region_t **region);
int img_param_get_num_white_region(void);
int img_param_get_saturation(int param_idx, const saturation_t **saturation);
int img_param_get_ae_target(int param_idx, int *ae_target);
int img_param_get_wdr_config(int param_idx, const wdr_fw_config_t **wdr_fw_config);
int img_param_get_num_wdr_config(void);
int img_param_get_bnr_config(const bnr_fw_config_t **bnr_fw_config);

#endif /* __IMG_PARAM_H__ */

