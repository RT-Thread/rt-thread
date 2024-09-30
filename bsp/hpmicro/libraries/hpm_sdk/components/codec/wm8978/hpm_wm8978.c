/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_wm8978.h"

#define WM8978_I2C_SLAVE_ADDRESS1  (0x1A)
#define WM8978_I2C_SLAVE_ADDRESS2  (0x1A)

/* store reg value */
static volatile uint16_t wm8978_reg_val[] = {
    0x000, 0x000, 0x000, 0x000, 0x050, 0x000, 0x140, 0x000,
    0x000, 0x000, 0x000, 0x0FF, 0x0FF, 0x000, 0x100, 0x0FF,
    0x0FF, 0x000, 0x12C, 0x02C, 0x02C, 0x02C, 0x02C, 0x000,
    0x032, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
    0x038, 0x00B, 0x032, 0x000, 0x008, 0x00C, 0x093, 0x0E9,
    0x000, 0x000, 0x000, 0x000, 0x003, 0x010, 0x010, 0x100,
    0x100, 0x002, 0x001, 0x001, 0x039, 0x039, 0x039, 0x039,
};
;

hpm_stat_t wm8979_init(wm8978_context_t *control)
{
    hpm_stat_t stat;
    uint8_t i;
    for (i = 0; i < 0x7F; i++) {
        if (i2c_master_write(control->ptr, i, NULL, 0) == status_success) {
            if ((i == WM8978_I2C_SLAVE_ADDRESS1) || (i == WM8978_I2C_SLAVE_ADDRESS2)) {
                control->device_address = i;
                break;
            }
        }
    }
    if (i == 0x7F) {
        return status_fail;
    }
    stat = wm8978_reset(control);
    return stat;
}

hpm_stat_t wm8978_reset(wm8978_context_t *control)
{
    hpm_stat_t stat = status_success;
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RESET, 0));
    return stat;
}

hpm_stat_t wm8978_set_out_volume(wm8978_context_t *control, wm8978_out_channel_t channel, uint8_t volume)
{
    hpm_stat_t stat = status_success;
    uint8_t l_out_reg;
    uint8_t r_out_reg;
    if (volume > WM8978_OUT_VOLUME_MASK) {
        volume = WM8978_OUT_VOLUME_MASK;
    }
    if (channel == wm8978_out1_channel) {
        l_out_reg = WM8978_LOUT1_VOLUME_CTRL;
        r_out_reg = WM8978_ROUT1_VOLUME_CTRL;
    } else if (channel == wm8978_out2_channel) {
        l_out_reg = WM8978_LOUT2_VOLUME_CTRL;
        r_out_reg = WM8978_ROUT2_VOLUME_CTRL;
    } else {
        return status_invalid_argument;
    }
    HPM_CHECK_RET(wm8978_write_reg(control, l_out_reg, WM8978_OUT_VOLUME_SET(volume) | WM8978_OUT_SPKVU_SET(0)));
    /* LOUT1/2 and ROUT1/2 volumes do not update untila 1 is written to SPKkVU */
    HPM_CHECK_RET(wm8978_write_reg(control, r_out_reg, WM8978_OUT_VOLUME_SET(volume) | WM8978_OUT_SPKVU_SET(1)));
    return stat;
}

hpm_stat_t wm8978_get_out_volume(wm8978_context_t *control, wm8978_out_channel_t channel, uint8_t *volume)
{
    hpm_stat_t stat = status_success;
    uint8_t out_reg;
    uint16_t val;
    if (channel == wm8978_out1_channel) {
        out_reg = WM8978_LOUT1_VOLUME_CTRL;
    } else if (channel == wm8978_out2_channel) {
        out_reg = WM8978_LOUT2_VOLUME_CTRL;
    } else {
        return status_invalid_argument;
    }
    HPM_CHECK_RET(wm8978_read_reg(control, out_reg, &val));
    *volume = WM8978_OUT_VOLUME_GET(val);
    return stat;
}

hpm_stat_t wm8978_set_out_mute(wm8978_context_t *control, wm8978_out_channel_t channel, bool mute)
{
    hpm_stat_t stat = status_success;
    uint16_t val;
    uint8_t l_out_reg;
    uint8_t r_out_reg;
    if (channel == wm8978_out1_channel) {
        l_out_reg = WM8978_LOUT1_VOLUME_CTRL;
        r_out_reg = WM8978_ROUT1_VOLUME_CTRL;
    } else if (channel == wm8978_out2_channel) {
        l_out_reg = WM8978_LOUT2_VOLUME_CTRL;
        r_out_reg = WM8978_ROUT2_VOLUME_CTRL;
    } else {
        return status_invalid_argument;
    }
    if (mute == true) {
        HPM_CHECK_RET(wm8978_read_reg(control, l_out_reg, &val));
        val |= WM8978_OUT_MUTE_MASK;
        HPM_CHECK_RET(wm8978_write_reg(control, l_out_reg, val));
        HPM_CHECK_RET(wm8978_read_reg(control, r_out_reg, &val));
        val |= WM8978_OUT_MUTE_MASK;
        HPM_CHECK_RET(wm8978_write_reg(control, r_out_reg, val));
    } else {
        HPM_CHECK_RET(wm8978_read_reg(control, l_out_reg, &val));
        val &= ~WM8978_OUT_MUTE_MASK;
        HPM_CHECK_RET(wm8978_write_reg(control, l_out_reg, val));
        HPM_CHECK_RET(wm8978_read_reg(control, r_out_reg, &val));
        val &= ~WM8978_OUT_MUTE_MASK;
        HPM_CHECK_RET(wm8978_write_reg(control, r_out_reg, val));
    }
    return stat;
}

hpm_stat_t wm8978_set_mic_gain(wm8978_context_t *control, uint8_t gain)
{
    hpm_stat_t stat = status_success;
    if (gain > WM8978_INPPGA_VOL_MASK) {
        gain = WM8978_INPPGA_VOL_MASK;
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LINP_PGA_GAIM_CTRL, WM8978_INPPGA_VOL_SET(gain)));
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LINP_PGA_GAIM_CTRL, WM8978_INPPGA_VOL_SET(gain) | WM8978_INPGA_UPDATE_SET(1)));
    return stat;
}

hpm_stat_t wm8978_set_line_gain(wm8978_context_t *control, uint8_t gain)
{
    uint16_t val;
    hpm_stat_t stat = status_success;
    if (gain > WM8978_AUXL2BOOSTVOL_MASK) {
        gain = WM8978_AUXL2BOOSTVOL_MASK;
    }
    HPM_CHECK_RET(wm8978_read_reg(control, WM8978_LADC_BOOST_CTRL, &val));
    val &= (~WM8978_2_2_BOOSTVOL_MASK);
    val |= WM8978_2_2_BOOSTVOL_SET(gain);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LADC_BOOST_CTRL, val));

    HPM_CHECK_RET(wm8978_read_reg(control, WM8978_RADC_BOOST_CTRL, &val));
    val &= ~WM8978_2_2_BOOSTVOL_MASK;
    val |= WM8978_2_2_BOOSTVOL_SET(gain);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RADC_BOOST_CTRL, val));
    return stat;
}

hpm_stat_t wm8978_power_down(wm8978_context_t *control)
{
    return wm8978_reset(control);
}

hpm_stat_t wm8978_cfg_audio_interface(wm8978_context_t *control, wm8978_audio_interface_t standard, wm8978_word_length_t word_len)
{
    hpm_stat_t stat = status_success;
    uint16_t usReg = 0;
    usReg  |= WM8978_FMT_SET(standard) | WM8978_WL_SET(word_len);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_AUDIO_INTERFACE, usReg));
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_CLOCK_GEN_CTRL, 0x000));
    return stat;
}

hpm_stat_t wm8978_cfg_audio_channel(wm8978_context_t *control, input_channel_flags_t in_flags, output_channel_flag_t out_flags)
{
    uint16_t reg_val = 0;
    hpm_stat_t stat = status_success;
    if ((in_flags == input_off) && (out_flags == output_off)) {
        wm8978_power_down(control);
        return stat;
    }

    reg_val = WM8978_BIASEN_R1_MASK | WM8978_VMIDSEL_R1_SET(3);
    if (out_flags & out_3_4_on) {
        reg_val |= (WM8978_OUT4MIXEN_R1_MASK | WM8978_OUT3MIXEN_R1_MASK);
    }
    if ((in_flags & mic_left_on) || (in_flags & mic_right_on)) {
        reg_val |= WM8978_MICBEN_R1_MASK;
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_POWER_MANAGET_1, reg_val));

    reg_val = 0;
    if (out_flags & earphone_left_on) {
        reg_val |= WM8978_LOUT1EN_R2_MASK;
    }
    if (out_flags & earphone_right_on) {
        reg_val |= WM8978_ROUT1EN_R2_MASK;
    }
    if (in_flags & mic_left_on) {
        reg_val |= (WM8978_BOOSTENL_R2_MASK | WM8978_INPPGAENL_R2_MASK);
    }
    if (in_flags & mic_right_on) {
        reg_val |= (WM8978_BOOSTENR_R2_MASK | WM8978_INPPGAENR_R2_MASK);
    }
    if (in_flags & line_on) {
        reg_val |= (WM8978_BOOSTENL_R2_MASK | WM8978_BOOSTENR_R2_MASK);
    }
    if (in_flags & adc_on) {
        reg_val |= (WM8978_ADCENR_R2_MASK | WM8978_ADCENL_R2_MASK);
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_POWER_MANAGET_2, reg_val));

    reg_val = 0;
    if (out_flags & out_3_4_on) {
        reg_val |= (WM8978_OUT4EN_R3_MASK | WM8978_OUT3EN_R3_MASK);
    }
    if (out_flags & spk_on) {
        reg_val |= (WM8978_LOUT2EN_R3_MASK | WM8978_ROUT2EN_R3_MASK);
    }
    if (out_flags != output_off) {
        reg_val |= (WM8978_RMIXEN_R3_MASK | WM8978_LMIXEN_R3_MASK);
    }
    if (in_flags & dac_on) {
        reg_val |= (WM8978_DACENR_R3_MASK | WM8978_DACENL_R3_MASK);
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_POWER_MANAGET_3, reg_val));

    reg_val = 0 << 8;
    if (in_flags & line_on) {
        reg_val |= (WM8978_R2_2INPPGA_R44_MASK | WM8978_L2_2INPPGA_R44_MASK);
    }
    if (in_flags & mic_right_on) {
        reg_val |= (WM8978_RIN2INPPGA_R44_MASK | WM8978_RIP2INPPGA_R44_MASK);
    }
    if (in_flags & mic_left_on) {
        reg_val |= (WM8978_LIN2INPPGA_R44_MASK | WM8978_LIP2INPPGA_R44_MASK);
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_INPUT_CTRL, reg_val));
    reg_val = 0;
    if (in_flags & adc_on) {
        reg_val |= (WM8978_ADCOSR128_R14_MASK) | (0 << 8) | (4 << 0);
    } else {
        reg_val = 0;
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_ADC_CONTROL, reg_val));

    if (in_flags & adc_on) {
        reg_val = (0 << 7);
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER1, reg_val));
        reg_val = 0;
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER2, reg_val));
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER3, reg_val));
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER4, reg_val));
    }
    reg_val = 0;
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_ALC_CONTROL1, reg_val));
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_ALC_CONTROL2, reg_val));
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_ALC_CONTROL3, reg_val));

    /* Disable automatic gain control */
    reg_val = (3 << 1) | (7 << 0);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOISE_GATE, reg_val));

    reg_val = 0;
    if ((in_flags & mic_left_on) || (in_flags & mic_right_on)) {
        reg_val |= (1 << 8); /* MIC gain = +20dB */
    }
    if (in_flags & aux_on) {
        reg_val |= (3 << 0); /* Aux = 3*/
    }
    if (in_flags & line_on) {
        reg_val |= (3 << 4);	/* Line gain = 3 */
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LADC_BOOST_CTRL, reg_val));
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RADC_BOOST_CTRL, reg_val));

    reg_val = 0xFF;
    /* Select 0dB to cache the left channel first */
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LEFT_ADC_VOL, reg_val));
    reg_val = 0x1FF;
    /* Update left and right channels simultaneously */
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RIGHT_ADC_VOL, reg_val));

    reg_val = 0;
    if (out_flags & spk_on) {
        /* ROUT2 is inverted and used to drive the speaker */
        reg_val |= (1 << 4);
    }
    if (in_flags & aux_on) {
        reg_val |= ((7 << 1) | (1 << 0));
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_BEEP_CONTROL, reg_val));

    reg_val = 0;
    if (in_flags & dac_on) {
        reg_val |= ((1 << 6) | (1 << 5));
    }
    if (out_flags & spk_on) {
        /* SPK 1.5x gain, thermal protection enabled */
        reg_val |=  ((1 << 2) | (1 << 1));
    }
    if (out_flags & out_3_4_on) {
        /* BOOT3  BOOT4  1.5x gain */
        reg_val |=  ((1 << 4) | (1 << 3));
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_OUTPUT_CTRL, reg_val));

    reg_val = 0;
    if (in_flags & aux_on) {
        reg_val |= ((7 << 6) | (1 << 5));
    }
    if ((in_flags & line_on) || (in_flags & mic_left_on) || (in_flags & mic_right_on)) {
        reg_val |= ((7 << 2) | (1 << 1));
    }
    if (in_flags & dac_on) {
        reg_val |= (1 << 0);
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LEFT_MIXER_CTRL, reg_val));
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RIGHT_MIXER_CTRL, reg_val));

    reg_val = 0;
    if (out_flags & out_3_4_on) {
        reg_val |= (1 << 3);
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_OUT3_MIXER_CTRL, reg_val));

    reg_val = 0;
    if (out_flags & out_3_4_on) {
        reg_val |= ((1 << 4) |  (1 << 1));
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_OUT4_MIXER_CTRL, reg_val));

    if (in_flags & dac_on) {
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LEFT_DAC_VOL, 0xFF));
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RIGHT_DAC_VOL, 0x1FF));
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_DAC_CTRL, 0));
    } else {
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_LEFT_DAC_VOL, 0));
        HPM_CHECK_RET(wm8978_write_reg(control, WM8978_RIGHT_DAC_VOL, 0x100));
    }
    return stat;
}

hpm_stat_t wm8978_notch_filter(wm8978_context_t *control, uint16_t nfa0, uint16_t nfa1)
{
    hpm_stat_t stat = status_success;
    uint16_t reg_val;
    reg_val = (1 << 7) | (nfa0 & 0x3F);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER1, reg_val));

    reg_val = ((nfa0 >> 7) & 0x3F);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER2, reg_val));

    reg_val = (nfa1 & 0x3F);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER3, reg_val));

    reg_val = (1 << 8) | ((nfa1 >> 7) & 0x3F);
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_NOTCH_FILTER4, reg_val));
    return stat;
}

hpm_stat_t wm8978_ctrl_gpio1(wm8978_context_t *control, bool value)
{
    hpm_stat_t stat = status_success;
    uint16_t reg_val;
    if (value == false) {
        reg_val = 6; /* B2:0 = 110 */
    } else {
        reg_val = 7; /* B2:0 = 111 */
    }
    HPM_CHECK_RET(wm8978_write_reg(control, WM8978_GPIO_CTRL, reg_val));
    return stat;
}

hpm_stat_t wm8978_write_reg(wm8978_context_t *control, uint8_t reg, uint16_t val)
{
    uint8_t buff[2];
    /* The first 7 bits (B15 to B9) are address bits that select which control register */
    /* is accessed. The remaining 9 bits (B8 to B0) are data bits */
    buff[0] = (reg << 1) | (uint8_t)((val >> 8U) & 0x0001U);
    buff[1] = (uint8_t)(val & 0xFFU);

    /* record reg val */
    wm8978_reg_val[reg] = val;
    return i2c_master_write(control->ptr, control->device_address, buff, 2U);
}

hpm_stat_t wm8978_read_reg(wm8978_context_t *control, uint8_t reg, uint16_t *val)
{
    (void)control;
    *val = wm8978_reg_val[reg];
    return status_success;
}

hpm_stat_t wm8978_modify_reg(wm8978_context_t *control, uint8_t reg, uint16_t mask, uint16_t val)
{
    hpm_stat_t stat = status_success;
    uint16_t reg_val;
    /* Read the register value out */
    HPM_CHECK_RET(wm8978_read_reg(control, reg, &reg_val));
    /* Modify the value */
    reg_val &= (uint16_t)~mask;
    reg_val |= val;
    /* Write the data to register */
    HPM_CHECK_RET(wm8978_write_reg(control, reg, reg_val));
    if (stat != status_success) {
        return status_fail;
    }
    return stat;
}

