/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_clc_drv.h"
#include "math.h"

void clc_config_param(CLC_Type *clc, clc_chn_t chn, clc_param_config_t *param)
{
    clc->VDVQ_CHAN[chn].EADC_LOWTH = (uint32_t)param->eadc_lowth;
    clc->VDVQ_CHAN[chn].EADC_HIGHTH = (uint32_t)param->eadc_highth;
    clc->VDVQ_CHAN[chn].EADC_MIDLOWTH = (uint32_t)param->eadc_mid_lowth;
    clc->VDVQ_CHAN[chn].EADC_MIDHIGHTH = (uint32_t)param->eadc_mid_highth;
    clc->VDVQ_CHAN[chn].P2Z2_CLAMP_LO = (uint32_t)param->_2p2z_clamp_lowth;
    clc->VDVQ_CHAN[chn].P2Z2_CLAMP_HI = (uint32_t)param->_2p2z_clamp_highth;
    clc->VDVQ_CHAN[chn].P3Z3_CLAMP_LO = (uint32_t)param->_3p3z_clamp_lowth;
    clc->VDVQ_CHAN[chn].P3Z3_CLAMP_HI = (uint32_t)param->_3p3z_clamp_highth;
    clc->VDVQ_CHAN[chn].P3Z3_FORBID_LO = (uint32_t)param->output_forbid_lowth;
    clc->VDVQ_CHAN[chn].P3Z3_FORBID_MD = (uint32_t)param->output_forbid_mid;
    clc->VDVQ_CHAN[chn].P3Z3_FORBID_HI = (uint32_t)param->output_forbid_highth;
}

hpm_stat_t clc_config_coeff(CLC_Type *clc, clc_chn_t chn, clc_coeff_zone_t zone, clc_coeff_config_t *coeff)
{
    float coeff_abs[7];
    float f_max;
    float f_coeff;
    uint32_t u_max;
    uint32_t coeff_ks;
    uint32_t shift;

    coeff_abs[0] = fabsf(coeff->b0);
    coeff_abs[1] = fabsf(coeff->b1);
    coeff_abs[2] = fabsf(coeff->b2);
    coeff_abs[3] = fabsf(coeff->b3);
    coeff_abs[4] = fabsf(coeff->a0);
    coeff_abs[5] = fabsf(coeff->a1);
    coeff_abs[6] = fabsf(coeff->a2);

    if ((coeff_abs[0] > 0x7FFFFFFFFu) || (coeff_abs[1] > 0x7FFFFFFFFu) || (coeff_abs[2] > 0x7FFFFFFFFu) || (coeff_abs[3] >= 1.0f)
     || (coeff_abs[4] > 0x7FFFFFFFFu) || (coeff_abs[5] > 0x7FFFFFFFFu) || (coeff_abs[6] >= 1.0f)) {
        return status_invalid_argument;
    }

    f_max = coeff_abs[0];
    for (uint8_t i = 1; i < 7u; i++) {
        if (f_max < coeff_abs[i]) {
            f_max = coeff_abs[i];
        }
    }
    u_max = (uint32_t)f_max;

    coeff_ks = 0;
    for (uint8_t i = 0; i < 32u; i++) {
        if (u_max == 0) {
            coeff_ks = i;
            break;
        }
        u_max >>= 1u;
    }

    shift = 31u - coeff_ks;
    f_coeff = (float)(uint32_t)(1u << shift);
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_KS = coeff_ks;
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_B0 = (uint32_t)(int32_t)(coeff->b0 * f_coeff);
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_B1 = (uint32_t)(int32_t)(coeff->b1 * f_coeff);
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_B2 = (uint32_t)(int32_t)(coeff->b2 * f_coeff);
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_B3 = (uint32_t)(int32_t)(coeff->b3 * (float)(0x80000000u));
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_A0 = (uint32_t)(int32_t)(coeff->a0 * f_coeff);
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_A1 = (uint32_t)(int32_t)(coeff->a1 * f_coeff);
    clc->VDVQ_CHAN[chn].COEFF[zone].COEFF_A2 = (uint32_t)(int32_t)(coeff->a2 * (float)(0x80000000u));

    return status_success;
}

void clc_sw_inject_dq_adc_value(CLC_Type *clc, uint32_t d_value, uint32_t q_value)
{
    clc_sw_inject_adc_value(clc, clc_vd_chn, d_value);
    clc_sw_inject_adc_value(clc, clc_vq_chn, q_value);
    clc_set_sw_inject_dq_adc_value_ready(clc);
}
