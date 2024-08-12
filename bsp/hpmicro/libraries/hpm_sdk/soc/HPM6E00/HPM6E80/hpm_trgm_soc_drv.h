/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TRGM_SOC_DRV_H
#define HPM_TRGM_SOC_DRV_H

#include "hpm_soc.h"
#include "hpm_trgm_regs.h"

typedef enum {
    trgm_adc_matrix_output_to_rdc0_adc0 = 0,
    trgm_adc_matrix_output_to_rdc0_adc1,
    trgm_adc_matrix_output_to_rdc1_adc0,
    trgm_adc_matrix_output_to_rdc1_adc1,
    trgm_adc_matrix_output_to_qei2_adc0,
    trgm_adc_matrix_output_to_qei2_adc1,
    trgm_adc_matrix_output_to_qei3_adc0,
    trgm_adc_matrix_output_to_qei3_adc1,
    trgm_adc_matrix_output_to_vsc0_adc0,
    trgm_adc_matrix_output_to_vsc0_adc1,
    trgm_adc_matrix_output_to_vsc0_adc2,
    trgm_adc_matrix_output_to_vsc1_adc0,
    trgm_adc_matrix_output_to_vsc1_adc1,
    trgm_adc_matrix_output_to_vsc1_adc2,
    trgm_adc_matrix_output_to_clc0_id_adc,
    trgm_adc_matrix_output_to_clc0_iq_adc,
    trgm_adc_matrix_output_to_clc0_vb_adc,
    trgm_adc_matrix_output_to_clc1_id_adc,
    trgm_adc_matrix_output_to_clc1_iq_adc,
    trgm_adc_matrix_output_to_clc1_vb_adc,
} trgm_adc_matrix_out_t;

typedef enum {
    trgm_adc_matrix_in_from_adc0 = 0,
    trgm_adc_matrix_in_from_adc1,
    trgm_adc_matrix_in_from_adc2,
    trgm_adc_matrix_in_from_adc3,
    trgm_adc_matrix_in_from_sdm_adc0,
    trgm_adc_matrix_in_from_sdm_adc1,
    trgm_adc_matrix_in_from_sdm_adc2,
    trgm_adc_matrix_in_from_sdm_adc3,
    trgm_adc_matrix_in_from_sdm_adc4,
    trgm_adc_matrix_in_from_sdm_adc5,
    trgm_adc_matrix_in_from_sdm_adc6,
    trgm_adc_matrix_in_from_sdm_adc7,
    trgm_adc_matrix_in_from_vsc0_id_adc,
    trgm_adc_matrix_in_from_vsc0_iq_adc,
    trgm_adc_matrix_in_from_vsc1_id_adc,
    trgm_adc_matrix_in_from_vsc1_iq_adc,
} trgm_adc_matrix_in_t;

typedef enum {
    trgm_dac_matrix_output_to_acmp0 = 0,
    trgm_dac_matrix_output_to_acmp1,
    trgm_dac_matrix_output_to_acmp2,
    trgm_dac_matrix_output_to_acmp3,
    trgm_dac_matrix_output_to_acmp4,
    trgm_dac_matrix_output_to_acmp5,
    trgm_dac_matrix_output_to_acmp6,
    trgm_dac_matrix_output_to_acmp7,
    trgm_dac_matrix_output_to_pwm0_dac0,
    trgm_dac_matrix_output_to_pwm0_dac1,
    trgm_dac_matrix_output_to_pwm0_dac2,
    trgm_dac_matrix_output_to_pwm0_dac3,
    trgm_dac_matrix_output_to_pwm1_dac0,
    trgm_dac_matrix_output_to_pwm1_dac1,
    trgm_dac_matrix_output_to_pwm1_dac2,
    trgm_dac_matrix_output_to_pwm1_dac3,
    trgm_dac_matrix_output_to_pwm2_dac0,
    trgm_dac_matrix_output_to_pwm2_dac1,
    trgm_dac_matrix_output_to_pwm2_dac2,
    trgm_dac_matrix_output_to_pwm2_dac3,
    trgm_dac_matrix_output_to_pwm3_dac0,
    trgm_dac_matrix_output_to_pwm3_dac1,
    trgm_dac_matrix_output_to_pwm3_dac2,
    trgm_dac_matrix_output_to_pwm3_dac3,
    trgm_dac_matrix_output_to_qeo0_vd_dac,
    trgm_dac_matrix_output_to_qeo0_vq_dac,
    trgm_dac_matrix_output_to_qeo1_vd_dac,
    trgm_dac_matrix_output_to_qeo1_vq_dac,
    trgm_dac_matrix_output_to_qeo2_vd_dac,
    trgm_dac_matrix_output_to_qeo2_vq_dac,
    trgm_dac_matrix_output_to_qeo3_vd_dac,
    trgm_dac_matrix_output_to_qeo3_vq_dac,
} trgm_dac_matrix_out_t;

typedef enum {
    trgm_dac_matrix_in_from_qeo0_dac0 = 0,
    trgm_dac_matrix_in_from_qeo0_dac1,
    trgm_dac_matrix_in_from_qeo0_dac2,
    trgm_dac_matrix_in_from_qeo1_dac0,
    trgm_dac_matrix_in_from_qeo1_dac1,
    trgm_dac_matrix_in_from_qeo1_dac2,
    trgm_dac_matrix_in_from_qeo2_dac0,
    trgm_dac_matrix_in_from_qeo2_dac1,
    trgm_dac_matrix_in_from_qeo2_dac2,
    trgm_dac_matrix_in_from_qeo3_dac0,
    trgm_dac_matrix_in_from_qeo3_dac1,
    trgm_dac_matrix_in_from_qeo3_dac2,
    trgm_dac_matrix_in_from_clc0_vd_dac,
    trgm_dac_matrix_in_from_clc0_vq_dac,
    trgm_dac_matrix_in_from_clc1_vd_dac,
    trgm_dac_matrix_in_from_clc1_vq_dac,
} trgm_dac_matrix_in_t;

typedef enum  {
    trgm_pos_matrix_output_to_sei_pos0 = 0,
    trgm_pos_matrix_output_to_sei_pos1,
    trgm_pos_matrix_output_to_sei_pos2,
    trgm_pos_matrix_output_to_sei_pos3,
    trgm_pos_matrix_output_to_mtg0,
    trgm_pos_matrix_output_to_mtg1,
    trgm_pos_matrix_output_to_qeo0,
    trgm_pos_matrix_output_to_qeo1,
    trgm_pos_matrix_output_to_qeo2,
    trgm_pos_matrix_output_to_qeo3,
    trgm_pos_matrix_output_to_vsc0,
    trgm_pos_matrix_output_to_vsc1,
} trgm_pos_matrix_out_t;

typedef enum {
    trgm_pos_matrix_in_from_sei_pos0 = 0,
    trgm_pos_matrix_in_from_sei_pos1,
    trgm_pos_matrix_in_from_sei_pos2,
    trgm_pos_matrix_in_from_sei_pos3,
    trgm_pos_matrix_in_from_qei0,
    trgm_pos_matrix_in_from_qei1,
    trgm_pos_matrix_in_from_qei2,
    trgm_pos_matrix_in_from_qei3,
    trgm_pos_matrix_in_from_mtg0_pos0,
    trgm_pos_matrix_in_from_mtg0_pos1,
    trgm_pos_matrix_in_from_mtg1_pos0,
    trgm_pos_matrix_in_from_mtg1_pos1,
} trgm_pos_matrix_in_t;

#if defined(__cplusplus)
extern "C" {
#endif

void trgm_adc_matrix_config(TRGM_Type *ptr, trgm_adc_matrix_out_t consumer, trgm_adc_matrix_in_t src, bool inv_val);

void trgm_dac_matrix_config(TRGM_Type *ptr, trgm_dac_matrix_out_t consumer, trgm_dac_matrix_in_t src, bool inv_val);

void trgm_pos_matrix_config(TRGM_Type *ptr, trgm_pos_matrix_out_t consumer, trgm_pos_matrix_in_t src, bool inv_val);

#if defined(__cplusplus)
}
#endif

#endif /* HPM_TRGM_SOC_DRV_H  */
