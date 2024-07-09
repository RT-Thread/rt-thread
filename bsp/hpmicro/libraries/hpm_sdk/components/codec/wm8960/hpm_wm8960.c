/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_wm8960.h"

#ifndef HPM_WM8960_MCLK_TOLERANCE
#define HPM_WM8960_MCLK_TOLERANCE (4U)
#endif

/* wm8960 register default value */
static const uint16_t wm8960_default_reg_val[WM8960_REG_NUM] = {
    0x0097, 0x0097, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x000a, 0x01c0, 0x0000, 0x00ff, 0x00ff, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x007b, 0x0100, 0x0032, 0x0000, 0x00c3, 0x00c3, 0x01c0, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0100, 0x0050, 0x0050, 0x0050, 0x0050, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0040, 0x0000, 0x0000, 0x0050, 0x0050, 0x0000, 0x0002, 0x0037, 0x004d, 0x0080, 0x0008, 0x0031, 0x0026, 0x00e9,
};

/* store reg value */
static uint16_t wm8960_reg_val[WM8960_REG_NUM];

hpm_stat_t wm8960_init(wm8960_control_t *control, wm8960_config_t *config)
{
    assert(control != NULL);
    assert(config != NULL);

    hpm_stat_t stat = status_success;

    (void)memcpy(wm8960_reg_val, wm8960_default_reg_val, sizeof(wm8960_default_reg_val));

    /* Reset */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RESET, 0x00));

    /* Power on input modules */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, 0xFE));
    /* Power on output modules */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER2, 0x1F8));
    /* Power on PGA and mixer */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER3, 0x3C));

    /* ADC and DAC uses same clock */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_IFACE2, 0x40));

    /* set data protocol */
    HPM_CHECK_RET(wm8960_set_protocol(control, config->bus));

    /* set wm8960 as slave */
    HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_MS_MASK, WM8960_IFACE1_MS_SET(0)));

    /* invert LRCLK */
    HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_LRP_MASK, WM8960_IFACE1_LRP_SET(1)));

    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ADDCTL1, 0xC0));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ADDCTL4, 0x40));

    /* ADC volume, 8dB */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LADC, 0x1D3));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RADC, 0x1D3));

    /* Digital DAC volume, 0dB */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LDAC, 0x1E0));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RDAC, 0x1E0));

    /* Headphone volume, LOUT1 and ROUT1, 6dB */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LOUT1, 0x17F));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ROUT1, 0x17F));

    /* speaker volume 6dB */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LOUT2, 0x1ff));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ROUT2, 0x1ff));
    /* enable class D output */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_CLASSD1, 0xf7));

    /* Unmute DAC. */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_DACCTL1, 0x0000));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINVOL, 0x117));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINVOL, 0x117));

    HPM_CHECK_RET(wm8960_set_data_format(control, config->format.mclk_hz, config->format.sample_rate, config->format.bit_width));

    /* set data route */
    HPM_CHECK_RET(wm8960_set_data_route(control, config));

    return status_success;
}

hpm_stat_t wm8960_deinit(wm8960_control_t *control)
{
    hpm_stat_t stat = status_success;

    /* power off all modules */
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, 0x00U));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER2, 0x00U));
    HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER3, 0x00U));

    return status_success;
}

hpm_stat_t wm8960_set_protocol(wm8960_control_t *control, wm8960_protocol_t protocol)
{
    return wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_FORMAT_MASK, (uint16_t)protocol);
}

hpm_stat_t wm8960_set_module(wm8960_control_t *control, wm8960_module_t module, bool enable)
{
    hpm_stat_t stat = status_success;
    switch (module) {
    case wm8960_module_adc:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER1, WM8960_POWER1_ADCL_MASK,
                                            ((uint16_t)enable << WM8960_POWER1_ADCL_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER1, WM8960_POWER1_ADCR_MASK,
                                            ((uint16_t)enable << WM8960_POWER1_ADCR_SHIFT)));
        break;
    case wm8960_module_dac:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER2, WM8960_POWER2_DACL_MASK,
                                            ((uint16_t)enable << WM8960_POWER2_DACL_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER2, WM8960_POWER2_DACR_MASK,
                                            ((uint16_t)enable << WM8960_POWER2_DACR_SHIFT)));
        break;
    case wm8960_module_vref:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER1, WM8960_POWER1_VREF_MASK,
                                            ((uint16_t)enable << WM8960_POWER1_VREF_SHIFT)));
        break;
    case wm8960_module_ana_in:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER1, WM8960_POWER1_AINL_MASK,
                                            ((uint16_t)enable << WM8960_POWER1_AINL_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER1, WM8960_POWER1_AINR_MASK,
                                            ((uint16_t)enable << WM8960_POWER1_AINR_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER3, WM8960_POWER3_LMIC_MASK,
                                            ((uint16_t)enable << WM8960_POWER3_LMIC_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER3, WM8960_POWER3_RMIC_MASK,
                                            ((uint16_t)enable << WM8960_POWER3_RMIC_SHIFT)));
        break;
    case wm8960_module_lineout:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER2, WM8960_POWER2_LOUT1_MASK,
                                            ((uint16_t)enable << WM8960_POWER2_LOUT1_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER2, WM8960_POWER2_ROUT1_MASK,
                                            ((uint16_t)enable << WM8960_POWER2_ROUT1_SHIFT)));
        break;
    case wm8960_module_micbais:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER1, WM8960_POWER1_MICB_MASK,
                                            ((uint16_t)enable << WM8960_POWER1_MICB_SHIFT)));
        break;
    case wm8960_module_speaker:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER2, WM8960_POWER2_SPKL_MASK,
                                            ((uint16_t)enable << WM8960_POWER2_SPKL_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER2, WM8960_POWER2_SPKR_MASK,
                                            ((uint16_t)enable << WM8960_POWER2_SPKR_SHIFT)));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_CLASSD1, 0xF7));
        break;
    case wm8960_module_output_mixer:
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER3, WM8960_POWER3_LOMIX_MASK,
                                            ((uint16_t)enable << WM8960_POWER3_LOMIX_SHIFT)));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_POWER3, WM8960_POWER3_ROMIX_MASK,
                                            ((uint16_t)enable << WM8960_POWER3_ROMIX_SHIFT)));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    return stat;
}

hpm_stat_t wm8960_set_data_route(wm8960_control_t *control, wm8960_config_t *config)
{
    hpm_stat_t stat = status_success;

    /* select left input */
    HPM_CHECK_RET(wm8960_set_left_input(control, config->left_input));
    /* select right input */
    HPM_CHECK_RET(wm8960_set_right_input(control, config->right_input));
    /* select source to output mixer */
    HPM_CHECK_RET(wm8960_config_input_to_output_mixer(control, config->play_source));

    switch (config->route) {
    case wm8960_route_bypass:
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_micbais, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_ana_in, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_output_mixer, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_lineout, true));
        break;
    case wm8960_route_playback:
        /* I2S_IN-> DAC-> HP */
        /* Set power for DAC */
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER3, 0x0C));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_dac, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_output_mixer, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_lineout, true));
        break;
    case wm8960_route_playback_and_record:
        /* Set power */
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER3, 0x3C));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_adc, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_micbais, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_ana_in, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_dac, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_output_mixer, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_lineout, true));
        break;
    case wm8960_route_record:
        /* ANA_IN->ADC->I2S_OUT */
        /* Power up ADC and AIN */
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER3, 0x30));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_micbais, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_ana_in, true));
        HPM_CHECK_RET(wm8960_set_module(control, wm8960_module_adc, true));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    return stat;
}

hpm_stat_t wm8960_set_left_input(wm8960_control_t *control, wm8960_input_t input)
{
    hpm_stat_t stat = status_success;
    uint16_t val = 0;

    switch (input) {
    case wm8960_input_closed:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val &= (uint16_t) ~(WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        break;
    case wm8960_input_single_ended_mic:
        /* Only LMN1 enabled, LMICBOOST to 13db, LMIC2B enabled */
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK | WM8960_POWER1_MICB_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINPATH, 0x138));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINVOL, 0x117));
        break;
    case wm8960_input_differential_mic_input2:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK | WM8960_POWER1_MICB_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINPATH, 0x178));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINVOL, 0x117));
        break;
    case wm8960_input_differential_mic_input3:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK | WM8960_POWER1_MICB_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINPATH, 0x1B8));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINVOL, 0x117));
        break;
    case wm8960_input_line_input2:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_read_reg(WM8960_INBMIX1, &val));
        val |= 0xEU;
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_INBMIX1, val));
        break;
    case wm8960_input_line_input3:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINL_MASK | WM8960_POWER1_ADCL_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_read_reg(WM8960_INBMIX1, &val));
        val |= 0x70U;
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_INBMIX1, val));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }

    return stat;
}

hpm_stat_t wm8960_set_right_input(wm8960_control_t *control, wm8960_input_t input)
{
    hpm_stat_t stat = status_success;
    uint16_t val = 0;

    switch (input) {
    case wm8960_input_closed:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val &= (uint16_t) ~(WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        break;
    case wm8960_input_single_ended_mic:
        /* Only LMN1 enabled, LMICBOOST to 13db, LMIC2B enabled */
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK | WM8960_POWER1_MICB_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINPATH, 0x138));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINVOL, 0x117));
        break;
    case wm8960_input_differential_mic_input2:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK | WM8960_POWER1_MICB_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINPATH, 0x178));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINVOL, 0x117));
        break;
    case wm8960_input_differential_mic_input3:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK | WM8960_POWER1_MICB_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINPATH, 0x1B8));
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINVOL, 0x117));
        break;
    case wm8960_input_line_input2:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_read_reg(WM8960_INBMIX2, &val));
        val |= 0xEU;
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_INBMIX2, val));
        break;
    case wm8960_input_line_input3:
        HPM_CHECK_RET(wm8960_read_reg(WM8960_POWER1, &val));
        val |= (WM8960_POWER1_AINR_MASK | WM8960_POWER1_ADCR_MASK);
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_POWER1, val));
        HPM_CHECK_RET(wm8960_read_reg(WM8960_INBMIX2, &val));
        val |= 0x70U;
        HPM_CHECK_RET(wm8960_write_reg(control, WM8960_INBMIX2, val));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }

    return stat;
}

hpm_stat_t wm8960_set_volume(wm8960_control_t *control, wm8960_module_t module, uint32_t volume)
{
    uint16_t vol = 0;
    hpm_stat_t stat = status_success;
    switch (module) {
    case wm8960_module_adc:
        if (volume > 255U) {
            stat = status_invalid_argument;
        } else {
            vol = (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LADC, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RADC, vol));
            /* Update volume */
            vol = (uint16_t)(0x100U | volume);
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LADC, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RADC, vol));
        }
        break;
    case wm8960_module_dac:
        if (volume > 255U) {
            stat = status_invalid_argument;
        } else {
            vol = (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LDAC, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RDAC, vol));
            vol = 0x100U | (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LDAC, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RDAC, vol));
        }
        break;
    case wm8960_module_headphone:
        if (volume > 0x7FU) {
            stat = status_invalid_argument;
        } else {
            vol = (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LOUT1, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ROUT1, vol));
            vol = 0x100U | (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LOUT1, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ROUT1, vol));
        }
        break;
    case wm8960_module_ana_in:
        if (volume > 0x3FU) {
            stat = status_invalid_argument;
        } else {
            vol = (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINVOL, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINVOL, vol));
            vol = 0x100U | (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LINVOL, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_RINVOL, vol));
        }
        break;
    case wm8960_module_speaker:
        if (volume > 0x7FU) {
            stat = status_invalid_argument;
        } else {
            vol = (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LOUT2, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ROUT2, vol));
            vol = 0x100U | (uint16_t)volume;
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_LOUT2, vol));
            HPM_CHECK_RET(wm8960_write_reg(control, WM8960_ROUT2, vol));
        }
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    return stat;
}

static bool wm8960_check_clock_tolerance(uint32_t source, uint32_t target)
{
    uint32_t delta = (source >= target) ? (source - target) : (target - source);
    if (delta * 100 <= HPM_WM8960_MCLK_TOLERANCE * target) {
        return true;
    }
    return false;
}

hpm_stat_t wm8960_set_data_format(wm8960_control_t *control, uint32_t sysclk, uint32_t sample_rate, uint32_t bits)
{
    hpm_stat_t stat = status_success;
    uint16_t val = 0;
    uint32_t ratio[7] = {256, 256 * 1.5, 256 * 2, 256 * 3, 256 * 4, 256 * 5.5, 256 * 6};
    bool clock_meet_requirement = false;

    if (sysclk / sample_rate > 256 * 6) {
        sysclk = sysclk / 2;
        val = WM8960_CLOCK1_SYSCLKDIV_SET(2U); /* SYSCLK Pre-divider */
    }

    for (uint8_t i = 0; i < 7; i++) {
        if (wm8960_check_clock_tolerance(sysclk, sample_rate * ratio[i])) {
            val |= ((i << WM8960_CLOCK1_ADCDIV_SHIFT) | (i << WM8960_CLOCK1_DACDIV_SHIFT));
            clock_meet_requirement = true;
            break;
        }
    }

    if (!clock_meet_requirement) {
        return status_invalid_argument;
    }
    HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_CLOCK1, 0x1FEU, val));

    /* set sample bit */
    switch (bits) {
    case 16:
        stat = wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_WL_MASK, WM8960_IFACE1_WL_SET(0U));
        break;
    case 20:
        stat = wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_WL_MASK, WM8960_IFACE1_WL_SET(1U));
        break;
    case 24:
        stat = wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_WL_MASK, WM8960_IFACE1_WL_SET(2U));
        break;
    case 32:
        stat = wm8960_modify_reg(control, WM8960_IFACE1, WM8960_IFACE1_WL_MASK, WM8960_IFACE1_WL_SET(3U));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }

    return stat;
}

hpm_stat_t wm8960_config_input_to_output_mixer(wm8960_control_t *control, uint32_t play_source)
{
    hpm_stat_t stat = status_success;

    if ((play_source & (uint32_t)wm8960_play_source_input_mixer) != 0U) {
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_BYPASS1, 0x80U, 0x80U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_BYPASS2, 0x80U, 0x80U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_LOUTMIX, 0x180U, 0U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_ROUTMIX, 0x180U, 0U));
    }

    if ((play_source & (uint32_t)wm8960_play_source_dac) != 0U) {
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_BYPASS1, 0x80U, 0x00U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_BYPASS2, 0x80U, 0x00U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_LOUTMIX, 0x180U, 0x100U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_ROUTMIX, 0x180U, 0x100U));
    }

    if ((play_source & (uint32_t)wm8960_play_source_input3) != 0U) {
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_BYPASS1, 0x80U, 0x0U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_BYPASS2, 0x80U, 0x0U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_LOUTMIX, 0x180U, 0x80U));
        HPM_CHECK_RET(wm8960_modify_reg(control, WM8960_ROUTMIX, 0x180U, 0x80U));
    }

    return stat;
}


hpm_stat_t wm8960_write_reg(wm8960_control_t *control, uint8_t reg, uint16_t val)
{
    uint8_t buff[2];
    /* The first 7 bits (B15 to B9) are address bits that select which control register */
    /* is accessed. The remaining 9 bits (B8 to B0) are data bits */
    buff[0] = (reg << 1) | (uint8_t)((val >> 8U) & 0x0001U);
    buff[1] = (uint8_t)(val & 0xFFU);

    /* record reg val */
    wm8960_reg_val[reg] = val;

    return i2c_master_write(control->ptr, control->slave_address, buff, 2U);
}

hpm_stat_t wm8960_read_reg(uint8_t reg, uint16_t *val)
{
    if (reg >= WM8960_REG_NUM) {
        return status_invalid_argument;
    }
    *val = wm8960_reg_val[reg];

    return status_success;
}

hpm_stat_t wm8960_modify_reg(wm8960_control_t *control, uint8_t reg, uint16_t mask, uint16_t val)
{
    hpm_stat_t stat = 0;
    uint16_t reg_val;

    /* Read the register value out */
    stat = wm8960_read_reg(reg, &reg_val);
    if (stat != status_success) {
        return status_fail;
    }

    /* Modify the value */
    reg_val &= (uint16_t)~mask;
    reg_val |= val;

    /* Write the data to register */
    stat = wm8960_write_reg(control, reg, reg_val);
    if (stat != status_success) {
        return status_fail;
    }

    return status_success;
}
