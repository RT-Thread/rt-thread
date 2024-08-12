/*
 * Copyright (c) 2021-2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_TRGM_SOC_DRV_H
#define HPM_TRGM_SOC_DRV_H

#include "hpm_soc.h"
#include "hpm_trgm_regs.h"

typedef enum {
    trgm_adc_matrix_output_to_qei0_adc0 = 0,
    trgm_adc_matrix_output_to_qei0_adc1 = 1,
    trgm_adc_matrix_output_to_qei1_adc0 = 2,
    trgm_adc_matrix_output_to_qei1_adc1 = 3,
} trgm_adc_matrix_out_t;

typedef enum {
    trgm_adc_matrix_in_from_adc0 = 0,
    trgm_adc_matrix_in_from_adc1 = 1,
    trgm_adc_matrix_in_from_rdc_adc0 = 2,
    trgm_adc_matrix_in_from_rdc_adc1 = 3,
} trgm_adc_matrix_in_t;

typedef enum {
    trgm_dac_matrix_output_to_acmp0 = 0,
    trgm_dac_matrix_output_to_acmp1 = 1,
    trgm_dac_matrix_output_to_dac0 = 2,
    trgm_dac_matrix_output_to_dac1 = 3,
} trgm_dac_matrix_out_t;

typedef enum {
    trgm_dac_matrix_in_from_qeo0_dac0 = 0,
    trgm_dac_matrix_in_from_qeo0_dac1 = 1,
    trgm_dac_matrix_in_from_qeo0_dac2 = 2,
    trgm_dac_matrix_in_from_qeo1_dac0 = 3,
    trgm_dac_matrix_in_from_qeo1_dac1 = 4,
    trgm_dac_matrix_in_from_qeo1_dac2 = 5,
    trgm_dac_matrix_in_from_rdc_dac0 = 6,
    trgm_dac_matrix_in_from_rdc_dac1 = 7,
} trgm_dac_matrix_in_t;

typedef enum  {
    trgm_pos_matrix_output_to_sei_pos0 = 0,
    trgm_pos_matrix_output_to_sei_pos1 = 1,
    trgm_pos_matrix_output_to_mmc0 = 2,
    trgm_pos_matrix_output_to_mmc1 = 3,
    trgm_pos_matrix_output_to_qeo0 = 4,
    trgm_pos_matrix_output_to_qeo1 = 5,
} trgm_pos_matrix_out_t;

typedef enum {
    trgm_pos_matrix_in_from_sei_pos0 = 0,
    trgm_pos_matrix_in_from_sei_pos1 = 1,
    trgm_pos_matrix_in_from_qei0 = 2,
    trgm_pos_matrix_in_from_qei1 = 3,
    trgm_pos_matrix_in_from_mmc0_pos0 = 4,
    trgm_pos_matrix_in_from_mmc0_pos1 = 5,
    trgm_pos_matrix_in_from_mmc1_pos0 = 6,
    trgm_pos_matrix_in_from_mmc1_pos1 = 7,
} trgm_pos_matrix_in_t;

#if defined(__cplusplus)
extern "C" {
#endif

static inline void trgm_adc_matrix_config(TRGM_Type *ptr, trgm_adc_matrix_out_t consumer, trgm_adc_matrix_in_t src, bool inv_val)
{
    if (inv_val) {
        ptr->ADC_MATRIX_SEL |= 0x80 << consumer * 8U;
    } else {
        ptr->ADC_MATRIX_SEL &= ~(0x80 << consumer * 8U);
    }
    ptr->ADC_MATRIX_SEL &= ~(0x7f << consumer * 8U);
    ptr->ADC_MATRIX_SEL |= src << consumer * 8U;
}

static inline void trgm_dac_matrix_config(TRGM_Type *ptr, trgm_dac_matrix_out_t consumer, trgm_dac_matrix_in_t src, bool inv_val)
{
    if (inv_val) {
        ptr->DAC_MATRIX_SEL |= 0x80 << consumer * 8U;
    } else {
        ptr->DAC_MATRIX_SEL &= ~(0x80 << consumer * 8U);
    }
    ptr->DAC_MATRIX_SEL &= ~(0x7f << consumer * 8U);
    ptr->DAC_MATRIX_SEL |= src << consumer * 8U;
}

static inline void trgm_pos_matrix_config(TRGM_Type *ptr, trgm_pos_matrix_out_t consumer, trgm_pos_matrix_in_t src, bool inv_val)
{
    uint8_t index = consumer / 4U;
    uint8_t offset = (consumer % 4U) * 8U;

    if (index == 0) {
        if (inv_val) {
            ptr->POS_MATRIX_SEL0 |= 0x80 << offset;
        } else {
            ptr->POS_MATRIX_SEL0 &= ~(0x80 << offset);
        }
        ptr->POS_MATRIX_SEL0 &= ~(0x7f << offset);
        ptr->POS_MATRIX_SEL0 |= src << offset;
    } else if (index == 1) {
        if (inv_val) {
            ptr->POS_MATRIX_SEL1 |= 0x80 << offset;
        } else {
            ptr->POS_MATRIX_SEL1 &= ~(0x80 << offset);
        }
        ptr->POS_MATRIX_SEL1 &= ~(0x7f << offset);
        ptr->POS_MATRIX_SEL1 |= src << offset;
    }
}

#if defined(__cplusplus)
}
#endif

#endif /* HPM_TRGM_SOC_DRV_H  */
