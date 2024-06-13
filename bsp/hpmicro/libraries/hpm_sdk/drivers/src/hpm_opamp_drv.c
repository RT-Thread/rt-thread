#include "hpm_opamp_drv.h"

hpm_stat_t opamp_init(OPAMP_Type *opamp, opamp_cfg_t *cfg)
{
    opamp_disable(opamp);
    opamp->CTRL0 = 0;
    opamp_inn_pad_select(opamp, cfg->negative_input_pin);
    opamp_inp_pad_select(opamp, cfg->positive_input_pin);
    opamp_gain_select(opamp, cfg->gain);
    opamp_miller_cap_select(opamp, cfg->miller_cap);
    if (cfg->enable_phase_margin_cap) {
        opamp_phase_margin_cap_enable(opamp);
    } else {
        opamp_phase_margin_cap_disable(opamp);
    }
    switch (cfg->mode) {
    case mode_follow:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) == 0) {
            return status_invalid_argument;
        }
        opamp_disconnect_vssa(opamp);
        opamp_phase_margin_cap_enable(opamp);
        opamp_mode_set(opamp, OPAMP_MODE_FOLLOW_KEY);
        break;
    case mode_invert_intern_vol:
        if ((cfg->positive_input_pin & 0x04) == 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_connect_vssa(opamp);
        opamp_phase_margin_cap_disable(opamp);
        opamp_mode_set(opamp, OPAMP_MODE_INVERT_INDEX0_KEY);
        break;
    case mode_invert_extern_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if (cfg->enable_extern_filter_cap) {
            opamp_mode_set(opamp, OPAMP_MODE_INVERT_INDEX1_KEY);
        } else {
            opamp_mode_set(opamp, OPAMP_MODE_INVERT_INDEX0_KEY);
        }
        break;
    case mode_invert_dac_vol:
        opamp_inp_pad_select(opamp, 0x02);
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_connect_vssa(opamp);
        opamp_mode_set(opamp, OPAMP_MODE_INVERT_INDEX0_KEY);
        break;
    case mode_non_invert_gnd_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_connect_vssa(opamp);
        if (!cfg->enable_extern_filter_cap) {
            if ((cfg->negative_input_pin & 0x04) == 0) {
                return status_invalid_argument;
            }
            opamp_mode_set(opamp, OPAMP_MODE_NON_INVERT_INDEX0_KEY);
        } else {
            if ((cfg->negative_input_pin & 0x04) != 0) {
                return status_invalid_argument;
            }
            opamp_mode_set(opamp, OPAMP_MODE_NON_INVERT_INDEX2_KEY);
        }
        break;
    case mode_non_invert_extern_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_connect_vssa(opamp);
        if (!cfg->enable_extern_filter_cap) {
            opamp_mode_set(opamp, OPAMP_MODE_NON_INVERT_INDEX1_KEY);
        } else {
            opamp_mode_set(opamp, OPAMP_MODE_NON_INVERT_INDEX3_KEY);
        }
        break;
    case mode_non_invert_dac_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_inn_pad_select(opamp, 0x02);
        opamp_connect_vssa(opamp);
        opamp_mode_set(opamp, OPAMP_MODE_NON_INVERT_INDEX4_KEY);
        break;
    case mode_user:
        opamp_mode_set(opamp, OPAMP_MODE_USER_DEFINE_KEY);
        break;
    default:
        return status_invalid_argument;
        break;
    }
    return status_success;
}


hpm_stat_t opamp_set_preset_cfg(OPAMP_Type *opamp, uint8_t preset_chn, opamp_cfg_t *cfg)
{
    if (preset_chn > OPAMP_SOC_HAS_MAX_PRESET_CHN_NUM) {
        return status_invalid_argument;
    }
    opamp->CFG[preset_chn].CFG0 = 0;
    opamp->CFG[preset_chn].CFG1 = 0;
    opamp_preset_inn_pad_select(opamp, preset_chn, cfg->negative_input_pin);
    opamp_preset_inp_pad_select(opamp, preset_chn, cfg->positive_input_pin);
    opamp_preset_gain_select(opamp, preset_chn, cfg->gain);
    opamp_preset_miller_cap_select(opamp, preset_chn, cfg->miller_cap);
    if (cfg->enable_phase_margin_cap) {
        opamp_preset_phase_margin_cap_enable(opamp, preset_chn);
    } else {
        opamp_preset_phase_margin_cap_disable(opamp, preset_chn);
    }
    switch (cfg->mode) {
    case mode_follow:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) == 0) {
            return status_invalid_argument;
        }
        opamp_preset_disconnect_vssa(opamp, preset_chn);
        opamp_preset_phase_margin_cap_enable(opamp, preset_chn);
        opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_FOLLOW_KEY);
        break;
    case mode_invert_intern_vol:
        if ((cfg->positive_input_pin & 0x04) == 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_preset_disconnect_vssa(opamp, preset_chn);
        opamp_preset_phase_margin_cap_disable(opamp, preset_chn);
        opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_INVERT_INDEX0_KEY);
        break;
    case mode_invert_extern_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if (cfg->enable_extern_filter_cap) {
            opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_INVERT_INDEX1_KEY);
        } else {
            opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_INVERT_INDEX0_KEY);
        }
        break;
    case mode_invert_dac_vol:
        opamp_preset_inp_pad_select(opamp, preset_chn, 0x02);
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_preset_disconnect_vssa(opamp, preset_chn);
        opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_INVERT_INDEX0_KEY);
        break;
    case mode_non_invert_gnd_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_preset_disconnect_vssa(opamp, preset_chn);
        if (!cfg->enable_extern_filter_cap) {
            if ((cfg->negative_input_pin & 0x04) == 0) {
                return status_invalid_argument;
            }
            opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_NON_INVERT_INDEX0_KEY);
        } else {
            if ((cfg->negative_input_pin & 0x04) != 0) {
                return status_invalid_argument;
            }
            opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_NON_INVERT_INDEX2_KEY);
        }
        break;
    case mode_non_invert_extern_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        if ((cfg->negative_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_preset_disconnect_vssa(opamp, preset_chn);
        if (!cfg->enable_extern_filter_cap) {
            opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_NON_INVERT_INDEX1_KEY);
        } else {
            opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_NON_INVERT_INDEX3_KEY);
        }
        break;
    case mode_non_invert_dac_vol:
        if ((cfg->positive_input_pin & 0x04) != 0) {
            return status_invalid_argument;
        }
        opamp_preset_inn_pad_select(opamp, preset_chn, 0x02);
        opamp_preset_disconnect_vssa(opamp, preset_chn);
        opamp_preset_mode_set(opamp, preset_chn, OPAMP_MODE_NON_INVERT_INDEX4_KEY);
        break;
    case mode_user:
        return status_success;
        break;
    default:
        return status_invalid_argument;
        break;
    }
    return status_success;
}

