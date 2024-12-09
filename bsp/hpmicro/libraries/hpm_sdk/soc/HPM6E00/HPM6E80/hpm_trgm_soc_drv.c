/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_trgm_soc_drv.h"

void trgm_adc_matrix_config(TRGM_Type *ptr, trgm_adc_matrix_out_t consumer, trgm_adc_matrix_in_t src, bool inv_val)
{
    uint8_t sel;

    sel = (uint8_t)src;
    if (inv_val) {
        sel |= BIT7_MASK;
    }

    switch (consumer) {
    case trgm_adc_matrix_output_to_rdc0_adc0:
        ptr->ADC_MATRIX_SEL0 = (ptr->ADC_MATRIX_SEL0 & ~TRGM_ADC_MATRIX_SEL0_RDC0_ADC0_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL0_RDC0_ADC0_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_rdc0_adc1:
        ptr->ADC_MATRIX_SEL0 = (ptr->ADC_MATRIX_SEL0 & ~TRGM_ADC_MATRIX_SEL0_RDC0_ADC1_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL0_RDC0_ADC1_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_rdc1_adc0:
        ptr->ADC_MATRIX_SEL0 = (ptr->ADC_MATRIX_SEL0 & ~TRGM_ADC_MATRIX_SEL0_RDC1_ADC0_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL0_RDC1_ADC0_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_rdc1_adc1:
        ptr->ADC_MATRIX_SEL0 = (ptr->ADC_MATRIX_SEL0 & ~TRGM_ADC_MATRIX_SEL0_RDC1_ADC1_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL0_RDC1_ADC1_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_qei2_adc0:
        ptr->ADC_MATRIX_SEL1 = (ptr->ADC_MATRIX_SEL1 & ~TRGM_ADC_MATRIX_SEL1_QEI2_ADC0_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL1_QEI2_ADC0_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_qei2_adc1:
        ptr->ADC_MATRIX_SEL1 = (ptr->ADC_MATRIX_SEL1 & ~TRGM_ADC_MATRIX_SEL1_QEI2_ADC1_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL1_QEI2_ADC1_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_qei3_adc0:
        ptr->ADC_MATRIX_SEL1 = (ptr->ADC_MATRIX_SEL1 & ~TRGM_ADC_MATRIX_SEL1_QEI3_ADC0_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL1_QEI3_ADC0_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_qei3_adc1:
        ptr->ADC_MATRIX_SEL1 = (ptr->ADC_MATRIX_SEL1 & ~TRGM_ADC_MATRIX_SEL1_QEI3_ADC1_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL1_QEI3_ADC1_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_vsc0_adc0:
        ptr->ADC_MATRIX_SEL2 = (ptr->ADC_MATRIX_SEL2 & ~TRGM_ADC_MATRIX_SEL2_VSC0_ADC0_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL2_VSC0_ADC0_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_vsc0_adc1:
        ptr->ADC_MATRIX_SEL2 = (ptr->ADC_MATRIX_SEL2 & ~TRGM_ADC_MATRIX_SEL2_VSC0_ADC1_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL2_VSC0_ADC1_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_vsc0_adc2:
        ptr->ADC_MATRIX_SEL2 = (ptr->ADC_MATRIX_SEL2 & ~TRGM_ADC_MATRIX_SEL2_VSC0_ADC2_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL2_VSC0_ADC2_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_vsc1_adc0:
        ptr->ADC_MATRIX_SEL2 = (ptr->ADC_MATRIX_SEL2 & ~TRGM_ADC_MATRIX_SEL2_VSC1_ADC0_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL2_VSC1_ADC0_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_vsc1_adc1:
        ptr->ADC_MATRIX_SEL3 = (ptr->ADC_MATRIX_SEL3 & ~TRGM_ADC_MATRIX_SEL3_VSC1_ADC1_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL3_VSC1_ADC1_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_vsc1_adc2:
        ptr->ADC_MATRIX_SEL3 = (ptr->ADC_MATRIX_SEL3 & ~TRGM_ADC_MATRIX_SEL3_VSC1_ADC2_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL3_VSC1_ADC2_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_clc0_id_adc:
        ptr->ADC_MATRIX_SEL3 = (ptr->ADC_MATRIX_SEL3 & ~TRGM_ADC_MATRIX_SEL3_CLC0_ID_ADC_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL3_CLC0_ID_ADC_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_clc0_iq_adc:
        ptr->ADC_MATRIX_SEL3 = (ptr->ADC_MATRIX_SEL3 & ~TRGM_ADC_MATRIX_SEL3_CLC0_IQ_ADC_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL3_CLC0_IQ_ADC_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_clc0_vb_adc:
        ptr->ADC_MATRIX_SEL4 = (ptr->ADC_MATRIX_SEL4 & ~TRGM_ADC_MATRIX_SEL4_CLC0_VB_ADC_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL4_CLC0_VB_ADC_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_clc1_id_adc:
        ptr->ADC_MATRIX_SEL4 = (ptr->ADC_MATRIX_SEL4 & ~TRGM_ADC_MATRIX_SEL4_CLC1_ID_ADC_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL4_CLC1_ID_ADC_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_clc1_iq_adc:
        ptr->ADC_MATRIX_SEL4 = (ptr->ADC_MATRIX_SEL4 & ~TRGM_ADC_MATRIX_SEL4_CLC1_IQ_ADC_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL4_CLC1_IQ_ADC_SEL_SET(sel);
        break;
    case trgm_adc_matrix_output_to_clc1_vb_adc:
        ptr->ADC_MATRIX_SEL4 = (ptr->ADC_MATRIX_SEL4 & ~TRGM_ADC_MATRIX_SEL4_CLC1_VB_ADC_SEL_MASK)
                             | TRGM_ADC_MATRIX_SEL4_CLC1_VB_ADC_SEL_SET(sel);
        break;
    default:
        break;
    }
}

void trgm_dac_matrix_config(TRGM_Type *ptr, trgm_dac_matrix_out_t consumer, trgm_dac_matrix_in_t src, bool inv_val)
{
    uint8_t sel;

    sel = (uint8_t)src;
    if (inv_val) {
        sel |= BIT7_MASK;
    }

    switch (consumer) {
    case trgm_dac_matrix_output_to_acmp0:
        ptr->DAC_MATRIX_SEL0 = (ptr->DAC_MATRIX_SEL0 & ~TRGM_DAC_MATRIX_SEL0_ACMP0_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL0_ACMP0_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp1:
        ptr->DAC_MATRIX_SEL0 = (ptr->DAC_MATRIX_SEL0 & ~TRGM_DAC_MATRIX_SEL0_ACMP1_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL0_ACMP1_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp2:
        ptr->DAC_MATRIX_SEL0 = (ptr->DAC_MATRIX_SEL0 & ~TRGM_DAC_MATRIX_SEL0_ACMP2_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL0_ACMP2_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp3:
        ptr->DAC_MATRIX_SEL0 = (ptr->DAC_MATRIX_SEL0 & ~TRGM_DAC_MATRIX_SEL0_ACMP3_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL0_ACMP3_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp4:
        ptr->DAC_MATRIX_SEL1 = (ptr->DAC_MATRIX_SEL1 & ~TRGM_DAC_MATRIX_SEL1_ACMP4_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL1_ACMP4_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp5:
        ptr->DAC_MATRIX_SEL1 = (ptr->DAC_MATRIX_SEL1 & ~TRGM_DAC_MATRIX_SEL1_ACMP5_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL1_ACMP5_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp6:
        ptr->DAC_MATRIX_SEL1 = (ptr->DAC_MATRIX_SEL1 & ~TRGM_DAC_MATRIX_SEL1_ACMP6_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL1_ACMP6_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_acmp7:
        ptr->DAC_MATRIX_SEL1 = (ptr->DAC_MATRIX_SEL1 & ~TRGM_DAC_MATRIX_SEL1_ACMP7_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL1_ACMP7_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm0_dac0:
        ptr->DAC_MATRIX_SEL2 = (ptr->DAC_MATRIX_SEL2 & ~TRGM_DAC_MATRIX_SEL2_PWM0_DAC0_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL2_PWM0_DAC0_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm0_dac1:
        ptr->DAC_MATRIX_SEL2 = (ptr->DAC_MATRIX_SEL2 & ~TRGM_DAC_MATRIX_SEL2_PWM0_DAC1_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL2_PWM0_DAC1_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm0_dac2:
        ptr->DAC_MATRIX_SEL2 = (ptr->DAC_MATRIX_SEL2 & ~TRGM_DAC_MATRIX_SEL2_PWM0_DAC2_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL2_PWM0_DAC2_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm0_dac3:
        ptr->DAC_MATRIX_SEL2 = (ptr->DAC_MATRIX_SEL2 & ~TRGM_DAC_MATRIX_SEL2_PWM0_DAC3_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL2_PWM0_DAC3_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm1_dac0:
        ptr->DAC_MATRIX_SEL3 = (ptr->DAC_MATRIX_SEL3 & ~TRGM_DAC_MATRIX_SEL3_PWM1_DAC0_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL3_PWM1_DAC0_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm1_dac1:
        ptr->DAC_MATRIX_SEL3 = (ptr->DAC_MATRIX_SEL3 & ~TRGM_DAC_MATRIX_SEL3_PWM1_DAC1_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL3_PWM1_DAC1_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm1_dac2:
        ptr->DAC_MATRIX_SEL3 = (ptr->DAC_MATRIX_SEL3 & ~TRGM_DAC_MATRIX_SEL3_PWM1_DAC2_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL3_PWM1_DAC2_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm1_dac3:
        ptr->DAC_MATRIX_SEL3 = (ptr->DAC_MATRIX_SEL3 & ~TRGM_DAC_MATRIX_SEL3_PWM1_DAC3_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL3_PWM1_DAC3_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm2_dac0:
        ptr->DAC_MATRIX_SEL4 = (ptr->DAC_MATRIX_SEL4 & ~TRGM_DAC_MATRIX_SEL4_PWM2_DAC0_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL4_PWM2_DAC0_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm2_dac1:
        ptr->DAC_MATRIX_SEL4 = (ptr->DAC_MATRIX_SEL4 & ~TRGM_DAC_MATRIX_SEL4_PWM2_DAC1_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL4_PWM2_DAC1_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm2_dac2:
        ptr->DAC_MATRIX_SEL4 = (ptr->DAC_MATRIX_SEL4 & ~TRGM_DAC_MATRIX_SEL4_PWM2_DAC2_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL4_PWM2_DAC2_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm2_dac3:
        ptr->DAC_MATRIX_SEL4 = (ptr->DAC_MATRIX_SEL4 & ~TRGM_DAC_MATRIX_SEL4_PWM2_DAC3_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL4_PWM2_DAC3_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm3_dac0:
        ptr->DAC_MATRIX_SEL5 = (ptr->DAC_MATRIX_SEL5 & ~TRGM_DAC_MATRIX_SEL5_PWM3_DAC0_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL5_PWM3_DAC0_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm3_dac1:
        ptr->DAC_MATRIX_SEL5 = (ptr->DAC_MATRIX_SEL5 & ~TRGM_DAC_MATRIX_SEL5_PWM3_DAC1_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL5_PWM3_DAC1_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm3_dac2:
        ptr->DAC_MATRIX_SEL5 = (ptr->DAC_MATRIX_SEL5 & ~TRGM_DAC_MATRIX_SEL5_PWM3_DAC2_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL5_PWM3_DAC2_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_pwm3_dac3:
        ptr->DAC_MATRIX_SEL5 = (ptr->DAC_MATRIX_SEL5 & ~TRGM_DAC_MATRIX_SEL5_PWM3_DAC3_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL5_PWM3_DAC3_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo0_vd_dac:
        ptr->DAC_MATRIX_SEL6 = (ptr->DAC_MATRIX_SEL6 & ~TRGM_DAC_MATRIX_SEL6_QEO0_VD_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL6_QEO0_VD_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo0_vq_dac:
        ptr->DAC_MATRIX_SEL6 = (ptr->DAC_MATRIX_SEL6 & ~TRGM_DAC_MATRIX_SEL6_QEO0_VQ_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL6_QEO0_VQ_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo1_vd_dac:
        ptr->DAC_MATRIX_SEL6 = (ptr->DAC_MATRIX_SEL6 & ~TRGM_DAC_MATRIX_SEL6_QEO1_VD_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL6_QEO1_VD_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo1_vq_dac:
        ptr->DAC_MATRIX_SEL6 = (ptr->DAC_MATRIX_SEL6 & ~TRGM_DAC_MATRIX_SEL6_QEO1_VQ_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL6_QEO1_VQ_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo2_vd_dac:
        ptr->DAC_MATRIX_SEL7 = (ptr->DAC_MATRIX_SEL7 & ~TRGM_DAC_MATRIX_SEL7_QEO2_VD_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL7_QEO2_VD_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo2_vq_dac:
        ptr->DAC_MATRIX_SEL7 = (ptr->DAC_MATRIX_SEL7 & ~TRGM_DAC_MATRIX_SEL7_QEO2_VQ_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL7_QEO2_VQ_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo3_vd_dac:
        ptr->DAC_MATRIX_SEL7 = (ptr->DAC_MATRIX_SEL7 & ~TRGM_DAC_MATRIX_SEL7_QEO3_VD_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL7_QEO3_VD_DAC_SEL_SET(sel);
        break;
    case trgm_dac_matrix_output_to_qeo3_vq_dac:
        ptr->DAC_MATRIX_SEL7 = (ptr->DAC_MATRIX_SEL7 & ~TRGM_DAC_MATRIX_SEL7_QEO3_VQ_DAC_SEL_MASK)
                             | TRGM_DAC_MATRIX_SEL7_QEO3_VQ_DAC_SEL_SET(sel);
        break;
    default:
        break;
    }
}

void trgm_pos_matrix_config(TRGM_Type *ptr, trgm_pos_matrix_out_t consumer, trgm_pos_matrix_in_t src, bool inv_val)
{
    uint8_t sel;

    sel = (uint8_t)src;
    if (inv_val) {
        sel |= BIT7_MASK;
    }

    switch (consumer) {
    case trgm_pos_matrix_output_to_sei_pos0:
        ptr->POS_MATRIX_SEL0 = (ptr->POS_MATRIX_SEL0 & ~TRGM_POS_MATRIX_SEL0_SEI_POSIN0_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL0_SEI_POSIN0_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_sei_pos1:
        ptr->POS_MATRIX_SEL0 = (ptr->POS_MATRIX_SEL0 & ~TRGM_POS_MATRIX_SEL0_SEI_POSIN1_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL0_SEI_POSIN1_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_sei_pos2:
        ptr->POS_MATRIX_SEL0 = (ptr->POS_MATRIX_SEL0 & ~TRGM_POS_MATRIX_SEL0_SEI_POSIN2_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL0_SEI_POSIN2_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_sei_pos3:
        ptr->POS_MATRIX_SEL0 = (ptr->POS_MATRIX_SEL0 & ~TRGM_POS_MATRIX_SEL0_SEI_POSIN3_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL0_SEI_POSIN3_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_mtg0:
        ptr->POS_MATRIX_SEL1 = (ptr->POS_MATRIX_SEL1 & ~TRGM_POS_MATRIX_SEL1_MTG0_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL1_MTG0_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_mtg1:
        ptr->POS_MATRIX_SEL1 = (ptr->POS_MATRIX_SEL1 & ~TRGM_POS_MATRIX_SEL1_MTG1_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL1_MTG1_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_qeo0:
        ptr->POS_MATRIX_SEL1 = (ptr->POS_MATRIX_SEL1 & ~TRGM_POS_MATRIX_SEL1_QEO0_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL1_QEO0_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_qeo1:
        ptr->POS_MATRIX_SEL1 = (ptr->POS_MATRIX_SEL1 & ~TRGM_POS_MATRIX_SEL1_QEO1_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL1_QEO1_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_qeo2:
        ptr->POS_MATRIX_SEL2 = (ptr->POS_MATRIX_SEL2 & ~TRGM_POS_MATRIX_SEL2_QEO2_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL2_QEO2_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_qeo3:
        ptr->POS_MATRIX_SEL2 = (ptr->POS_MATRIX_SEL2 & ~TRGM_POS_MATRIX_SEL2_QEO3_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL2_QEO3_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_vsc0:
        ptr->POS_MATRIX_SEL2 = (ptr->POS_MATRIX_SEL2 & ~TRGM_POS_MATRIX_SEL2_VSC0_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL2_VSC0_POS_SEL_SET(sel);
        break;
    case trgm_pos_matrix_output_to_vsc1:
        ptr->POS_MATRIX_SEL2 = (ptr->POS_MATRIX_SEL2 & ~TRGM_POS_MATRIX_SEL2_VSC1_POS_SEL_MASK)
                             | TRGM_POS_MATRIX_SEL2_VSC1_POS_SEL_SET(sel);
        break;
    default:
        break;
    }
}
