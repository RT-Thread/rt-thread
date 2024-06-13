/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include "hpm_sgtl5000.h"

#ifndef HPM_SGTL5000_MCLK_TOLERANCE
#define HPM_SGTL5000_MCLK_TOLERANCE (4U)
#endif

hpm_stat_t sgtl_init(sgtl_context_t *context, sgtl_config_t *config)
{
    assert(context != NULL);
    assert(config != NULL);

    if (sgtl_write_reg(context, CHIP_ANA_POWER, 0x6AFF) != status_success)
    {
        return status_fail;
    }

    /* Set the data route */
    if (sgtl_set_data_route(context, config->route) != status_success)
    {
        return status_fail;
    }

    /* Set sgtl5000 to master or slave */
    sgtl_set_master_mode(context, config->master);

    /* Input Volume Control
    Configure ADC left and right analog volume to desired default.
    Example shows volume of 0dB. */
    if (sgtl_write_reg(context, CHIP_ANA_ADC_CTRL, 0x0000U) != status_success)
    {
        return status_fail;
    }

    /* Volume and Mute Control
       Configure HP_OUT left and right volume to minimum, unmute.
       HP_OUT and ramp the volume up to desired volume.*/
    if (sgtl_write_reg(context, CHIP_ANA_HP_CTRL, 0x0C0CU) != status_success)
    {
        return status_fail;
    }

    if (sgtl_modify_reg(context, CHIP_ANA_CTRL, 0xFFEFU, 0x0000U) != status_success)
    {
        return status_fail;
    }

    /* LINEOUT and DAC volume control */
    if (sgtl_modify_reg(context, CHIP_ANA_CTRL, 0xFEFFU, 0x0000U) != status_success)
    {
        return status_fail;
    }

    /* Configure DAC left and right digital volume */
    if (sgtl_write_reg(context, CHIP_DAC_VOL, 0x5C5CU) != status_success)
    {
        return status_fail;
    }

    /* Configure ADC volume, reduce 6db. */
    if (sgtl_write_reg(context, CHIP_ANA_ADC_CTRL, 0x0100U) != status_success)
    {
        return status_fail;
    }

    /* Unmute DAC */
    if (sgtl_modify_reg(context, CHIP_ADCDAC_CTRL, 0xFFFBU, 0x0000U) != status_success)
    {
        return status_fail;
    }

    if (sgtl_modify_reg(context, CHIP_ADCDAC_CTRL, 0xFFF7U, 0x0000U) != status_success)
    {
        return status_fail;
    }

    /* Unmute ADC */
    if (sgtl_modify_reg(context, CHIP_ANA_CTRL, 0xFFFEU, 0x0000U) != status_success)
    {
        return status_fail;
    }

    /* Set the audio format */
    if (sgtl_set_protocol(context, config->bus) != status_success)
    {
        return status_fail;
    }

    if (sgtl_config_data_format(context, config->format.mclk_hz, config->format.sample_rate, config->format.bit_width) !=
        status_success)
    {
        return status_fail;
    }

    /* sclk valid edge */
    if (config->format.sclk_edge == sgtl_sclk_valid_edge_rising)
    {
        if (sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE) !=
            status_success)
        {
            return status_fail;
        }
    }
    else
    {
        if (sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_FALLING_EDGE) !=
            status_success)
        {
            return status_fail;
        }
    }

    return status_success;
}

hpm_stat_t sgtl_deinit(sgtl_context_t *context)
{
    hpm_stat_t stat = status_success;

    HPM_CHECK_RET(sgtl_disable_module(context, sgtl_module_adc));
    HPM_CHECK_RET(sgtl_disable_module(context, sgtl_module_dac));
    HPM_CHECK_RET(sgtl_disable_module(context, sgtl_module_dap));
    HPM_CHECK_RET(sgtl_disable_module(context, sgtl_module_i2sin));
    HPM_CHECK_RET(sgtl_disable_module(context, sgtl_module_i2sout));
    HPM_CHECK_RET(sgtl_disable_module(context, sgtl_module_lineout));

    return stat;
}

void sgtl_set_master_mode(sgtl_context_t *context, bool master)
{
    if (master == true)
    {
        (void)sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MS_CLR_MASK, SGTL5000_I2S_MASTER);
    }
    else
    {
        (void)sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MS_CLR_MASK, SGTL5000_I2S_SLAVE);
    }
}

hpm_stat_t sgtl_enable_module(sgtl_context_t *context, sgtl_module_t module)
{
    hpm_stat_t stat = status_success;
    switch (module)
    {
        case sgtl_module_adc:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_ADC_ENABLE_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_ADC_ENABLE_SHIFT)));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_ADC_POWERUP_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_ADC_POWERUP_SHIFT)));
            break;
        case sgtl_module_dac:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_DAC_ENABLE_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_DAC_ENABLE_SHIFT)));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_DAC_POWERUP_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_DAC_POWERUP_SHIFT)));
            break;
        case sgtl_module_dap:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_DAP_ENABLE_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_DAP_ENABLE_SHIFT)));
            HPM_CHECK_RET(sgtl_modify_reg(context, SGTL5000_DAP_CONTROL, SGTL5000_DAP_CONTROL_DAP_EN_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_DAP_CONTROL_DAP_EN_SHIFT)));
            break;
        case sgtl_module_i2sin:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_I2S_IN_ENABLE_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_I2S_IN_ENABLE_SHIFT)));
            break;
        case sgtl_module_i2sout:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_I2S_OUT_ENABLE_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_I2S_OUT_ENABLE_SHIFT)));
            break;
        case sgtl_module_hp:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_HEADPHONE_POWERUP_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_HEADPHONE_POWERUP_SHIFT)));
            break;
        case sgtl_module_lineout:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_LINEOUT_POWERUP_CLR_MASK,
                                 ((uint16_t)1U << SGTL5000_LINEOUT_POWERUP_SHIFT)));
            break;
        default:
            stat = status_invalid_argument;
            break;
    }
    return stat;
}

hpm_stat_t sgtl_disable_module(sgtl_context_t *context, sgtl_module_t module)
{
    hpm_stat_t stat = status_success;
    switch (module)
    {
        case sgtl_module_adc:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_ADC_ENABLE_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_ADC_ENABLE_SHIFT)));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_ADC_POWERUP_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_ADC_POWERUP_SHIFT)));
            break;
        case sgtl_module_dac:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_DAC_ENABLE_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_DAC_ENABLE_SHIFT)));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_DAC_POWERUP_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_DAC_POWERUP_SHIFT)));
            break;
        case sgtl_module_dap:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_DAP_ENABLE_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_DAP_ENABLE_SHIFT)));
            HPM_CHECK_RET(sgtl_modify_reg(context, SGTL5000_DAP_CONTROL, SGTL5000_DAP_CONTROL_DAP_EN_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_DAP_CONTROL_DAP_EN_SHIFT)));
            break;
        case sgtl_module_i2sin:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_I2S_IN_ENABLE_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_I2S_IN_ENABLE_SHIFT)));
            break;
        case sgtl_module_i2sout:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_DIG_POWER, SGTL5000_I2S_OUT_ENABLE_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_I2S_OUT_ENABLE_SHIFT)));
            break;
        case sgtl_module_hp:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_HEADPHONE_POWERUP_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_HEADPHONE_POWERUP_SHIFT)));
            break;
        case sgtl_module_lineout:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_POWER, SGTL5000_LINEOUT_POWERUP_CLR_MASK,
                                 ((uint16_t)0U << SGTL5000_LINEOUT_POWERUP_SHIFT)));
            break;
        default:
            stat = status_invalid_argument;
            break;
    }
    return stat;
}

hpm_stat_t sgtl_set_data_route(sgtl_context_t *context, sgtl_route_t route)
{
    hpm_stat_t stat = status_success;
    switch (route)
    {
        case sgtl_route_bypass:
            /* Bypass means from line-in to HP*/
            HPM_CHECK_RET(sgtl_write_reg(context, CHIP_DIG_POWER, 0x0000));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_hp));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_LINEIN));
            break;
        case sgtl_route_playback:
            /* Data route I2S_IN-> DAC-> HP */
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_hp));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_dac));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sin));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_I2S_IN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC));
            break;
        case sgtl_route_playback_record:
            /* I2S IN->DAC->HP  LINE_IN->ADC->I2S_OUT */
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_hp));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_dac));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sin));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sout));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_adc));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_I2S_IN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_ADC_CLR_MASK, SGTL5000_SEL_ADC_LINEIN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_I2S_OUT_SEL_CLR_MASK, SGTL5000_I2S_OUT_SEL_ADC));
            break;
        case sgtl_route_playback_with_dap:
            /* I2S_IN->DAP->DAC->HP */
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_hp));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_dac));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sin));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_dap));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_DAP_SEL_CLR_MASK, SGTL5000_DAP_SEL_I2S_IN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_DAP));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC));
            break;
        case sgtl_route_playback_with_dap_record:
            /* I2S_IN->DAP->DAC->HP,  LINE_IN->ADC->I2S_OUT */
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_hp));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_dac));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sin));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sout));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_adc));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_dap));
            HPM_CHECK_RET(sgtl_modify_reg(context, SGTL5000_DAP_CONTROL, SGTL5000_DAP_CONTROL_DAP_EN_CLR_MASK, 0x0001));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_DAP_SEL_CLR_MASK, SGTL5000_DAP_SEL_I2S_IN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_DAC_SEL_CLR_MASK, SGTL5000_DAC_SEL_DAP));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_HP_CLR_MASK, SGTL5000_SEL_HP_DAC));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_ADC_CLR_MASK, SGTL5000_SEL_ADC_LINEIN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_I2S_OUT_SEL_CLR_MASK, SGTL5000_I2S_OUT_SEL_ADC));
            break;
        case sgtl_route_record:
            /* LINE_IN->ADC->I2S_OUT */
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_i2sout));
            HPM_CHECK_RET(sgtl_enable_module(context, sgtl_module_adc));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_SEL_ADC_CLR_MASK, SGTL5000_SEL_ADC_LINEIN));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_SSS_CTRL, SGTL5000_I2S_OUT_SEL_CLR_MASK, SGTL5000_I2S_OUT_SEL_ADC));
            break;
        default:
            stat = status_invalid_argument;
            break;
    }
    return stat;
}

hpm_stat_t sgtl_set_protocol(sgtl_context_t *context, sgtl_protocol_t protocol)
{
    hpm_stat_t stat = status_success;
    switch (protocol)
    {
        case sgtl_bus_i2s:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_I2S_LJ));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_ONE_BIT_DELAY));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE));
            break;
        case sgtl_bus_left_justified:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_I2S_LJ));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_NO_DELAY));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE));
            break;
        case sgtl_bus_right_justified:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_RJ));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_RISING_EDGE));
            break;
        case sgtl_bus_pcma:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_PCM));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_ONE_BIT_DELAY));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_FALLING_EDGE));
            break;
        case sgtl_bus_pcmb:
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_MODE_CLR_MASK, SGTL5000_I2S_MODE_PCM));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_LRALIGN_CLR_MASK, SGTL5000_I2S_NO_DELAY));
            HPM_CHECK_RET(sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_SCLK_INV_CLR_MASK, SGTL5000_I2S_VAILD_FALLING_EDGE));
            break;
        default:
            stat = status_invalid_argument;
            break;
    }
    return stat;
}

hpm_stat_t sgtl_set_volume(sgtl_context_t *context, sgtl_module_t module, uint32_t volume)
{
    uint16_t vol = 0;
    hpm_stat_t stat = status_success;
    switch (module)
    {
        case sgtl_module_adc:
            if (volume > SGTL5000_ADC_MAX_VOLUME_VALUE)
            {
                return status_invalid_argument;
            }

            vol = (uint16_t)(volume | (volume << 4U));
            stat = sgtl_modify_reg(context, CHIP_ANA_ADC_CTRL,
                                 SGTL5000_ADC_VOL_LEFT_CLR_MASK & SGTL5000_ADC_VOL_RIGHT_CLR_MASK, vol);
            break;
        case sgtl_module_dac:
            if ((volume > SGTL5000_DAC_MAX_VOLUME_VALUE) || (volume < SGTL5000_DAC_MIN_VOLUME_VALUE))
            {
                return status_invalid_argument;
            }
            vol = (uint16_t)(volume | (volume << 8U));
            stat = sgtl_write_reg(context, CHIP_DAC_VOL, vol);
            break;
        case sgtl_module_hp:
            if (volume > SGTL5000_HEADPHONE_MAX_VOLUME_VALUE)
            {
                return status_invalid_argument;
            }
            vol = (uint16_t)(volume | (volume << 8U));
            stat = sgtl_write_reg(context, CHIP_ANA_HP_CTRL, vol);
            break;
        case sgtl_module_lineout:
            if (volume > SGTL5000_LINE_OUT_MAX_VOLUME_VALUE)
            {
                return status_invalid_argument;
            }
            vol = (uint16_t)(volume | (volume << 8U));
            stat = sgtl_write_reg(context, CHIP_LINE_OUT_VOL, vol);
            break;
        default:
            stat = status_invalid_argument;
            break;
    }
    return stat;
}

uint32_t sgtl_get_volume(sgtl_context_t *context, sgtl_module_t module)
{
    uint16_t vol = 0;
    hpm_stat_t stat = status_success;

    switch (module)
    {
        case sgtl_module_adc:
            stat = sgtl_read_reg(context, CHIP_ANA_ADC_CTRL, &vol);
            vol = (vol & (uint16_t)SGTL5000_ADC_VOL_LEFT_GET_MASK) >> SGTL5000_ADC_VOL_LEFT_SHIFT;
            break;
        case sgtl_module_dac:
            stat = sgtl_read_reg(context, CHIP_DAC_VOL, &vol);
            vol = (vol & (uint16_t)SGTL5000_DAC_VOL_LEFT_GET_MASK) >> SGTL5000_DAC_VOL_LEFT_SHIFT;
            break;
        case sgtl_module_hp:
            stat = sgtl_read_reg(context, CHIP_ANA_HP_CTRL, &vol);
            vol = (vol & (uint16_t)SGTL5000_HP_VOL_LEFT_GET_MASK) >> SGTL5000_HP_VOL_LEFT_SHIFT;
            break;
        case sgtl_module_lineout:
            stat = sgtl_read_reg(context, CHIP_LINE_OUT_VOL, &vol);
            vol = (vol & (uint16_t)SGTL5000_LINE_OUT_VOL_LEFT_GET_MASK) >> SGTL5000_LINE_OUT_VOL_LEFT_SHIFT;
            break;
        default:
            vol = 0;
            break;
    }
    return stat == status_success ? vol : 0U;
}

hpm_stat_t sgtl_set_mute(sgtl_context_t *context, sgtl_module_t module, bool mute)
{
    hpm_stat_t stat = status_success;
    switch (module)
    {
        case sgtl_module_adc:
            stat = sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_MUTE_ADC_CLR_MASK, mute ? 1U : 0U);
            break;
        case sgtl_module_dac:
            if (mute)
            {
                stat = sgtl_modify_reg(context, CHIP_ADCDAC_CTRL,
                                     SGTL5000_DAC_MUTE_LEFT_CLR_MASK & SGTL5000_DAC_MUTE_RIGHT_CLR_MASK, 0x000C);
            }
            else
            {
                stat = sgtl_modify_reg(context, CHIP_ADCDAC_CTRL,
                                     SGTL5000_DAC_MUTE_LEFT_CLR_MASK & SGTL5000_DAC_MUTE_RIGHT_CLR_MASK, 0x0000);
            }
            break;
        case sgtl_module_hp:
            stat = sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_MUTE_HP_CLR_MASK,
                                 ((uint16_t)mute << SGTL5000_MUTE_HP_SHIFT));
            break;
        case sgtl_module_lineout:
            stat = sgtl_modify_reg(context, CHIP_ANA_CTRL, SGTL5000_MUTE_LO_CLR_MASK,
                                 ((uint16_t)mute << SGTL5000_MUTE_LO_SHIFT));
            break;
        default:
            stat = status_invalid_argument;
            break;
    }
    return stat;
}

static bool sgtl_check_clock_tolerance(uint32_t source, uint32_t target)
{
    uint32_t delta = (source >= target) ? (source - target) : (target - source);
    if (delta * 100 <= HPM_SGTL5000_MCLK_TOLERANCE * target) {
        return true;
    }
    return false;
}

hpm_stat_t sgtl_config_data_format(sgtl_context_t *context, uint32_t mclk, uint32_t sample_rate, uint32_t bits)
{
    uint16_t val     = 0;
    uint16_t regVal  = 0;
    uint32_t mul_div = 0U;
    uint32_t sysFs   = 0U;
    hpm_stat_t stat     = status_success;

    /* Over sample rate can only up to 512, the least to 8k */
    if ((mclk / (MIN(sample_rate * 6U, 96000U)) > 512U) || (mclk / sample_rate < 256U))
    {
        return status_invalid_argument;
    }

    /* Configure the sample rate */
    switch (sample_rate)
    {
        case 8000:
            if (mclk > 32000U * 512U)
            {
                val   = 0x0038;
                sysFs = 48000;
            }
            else
            {
                val   = 0x0020;
                sysFs = 32000;
            }
            break;
        case 11025:
            val   = 0x0024;
            sysFs = 44100;
            break;
        case 12000:
            val   = 0x0028;
            sysFs = 48000;
            break;
        case 16000:
            if (mclk > 32000U * 512U)
            {
                val   = 0x003C;
                sysFs = 96000;
            }
            else
            {
                val   = 0x0010;
                sysFs = 32000;
            }
            break;
        case 22050:
            val   = 0x0014;
            sysFs = 44100;
            break;
        case 24000:
            if (mclk > 48000U * 512U)
            {
                val   = 0x002C;
                sysFs = 96000;
            }
            else
            {
                val   = 0x0018;
                sysFs = 48000;
            }
            break;
        case 32000:
            val   = 0x0000;
            sysFs = 32000;
            break;
        case 44100:
            val   = 0x0004;
            sysFs = 44100;
            break;
        case 48000:
            if (mclk > 48000U * 512U)
            {
                val   = 0x001C;
                sysFs = 96000;
            }
            else
            {
                val   = 0x0008;
                sysFs = 48000;
            }
            break;
        case 96000:
            val   = 0x000C;
            sysFs = 96000;
            break;
        default:
            stat = status_invalid_argument;
            break;
    }

    if (stat != status_success)
    {
        return stat;
    }

    if (sgtl_read_reg(context, CHIP_I2S_CTRL, &regVal) != status_success)
    {
        return status_fail;
    }

    mul_div = mclk / sysFs;

    if (sgtl_check_clock_tolerance(mul_div, 256)) {
        mul_div = 256;
    } else if (sgtl_check_clock_tolerance(mul_div, 384)) {
        mul_div = 384;
    } else if (sgtl_check_clock_tolerance(mul_div, 512)) {
        mul_div = 512;
    } else {
        return status_invalid_argument;
    }
    val |= (mul_div / 128U - 2U);

    if (sgtl_write_reg(context, CHIP_CLK_CTRL, val) != status_success)
    {
        return status_fail;
    }

    /* Data bits configure,sgtl supports 16bit, 20bit 24bit, 32bit */
    if (sgtl_modify_reg(context, CHIP_I2S_CTRL, 0xFEFF, SGTL5000_I2S_SCLKFREQ_64FS) != status_success)
    {
        return status_fail;
    }

    switch (bits)
    {
        case 16:
            stat = sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_16);
            break;
        case 20:
            stat = sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_20);
            break;
        case 24:
            stat = sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_24);
            break;
        case 32:
            stat = sgtl_modify_reg(context, CHIP_I2S_CTRL, SGTL5000_I2S_DLEN_CLR_MASK, SGTL5000_I2S_DLEN_32);
            break;
        default:
            stat = status_invalid_argument;
            break;
    }

    return stat;
}

hpm_stat_t sgtl_set_play(sgtl_context_t *context, uint32_t playSource)
{
    uint16_t regValue = 0U, regBitMask = 0x40U;

    /* headphone source form PGA */
    if (playSource == (uint32_t)sgtl_play_source_linein)
    {
        regValue = 0x40U;
    }
    /* headphone source from DAC */
    else
    {
        regValue = 0U;
    }

    return sgtl_modify_reg(context, CHIP_ANA_CTRL, regBitMask, regValue);
}

hpm_stat_t sgtl_set_record(sgtl_context_t *context, uint32_t recordSource)
{
    uint16_t regValue = 0U, regBitMask = 0x4U;

    /* ADC source form LINEIN */
    if (recordSource == (uint32_t)sgtl_record_source_linein)
    {
        regValue = 0x4U;
    }
    /* ADC source from MIC */
    else
    {
        regValue = 0U;
    }

    return sgtl_modify_reg(context, CHIP_ANA_CTRL, regBitMask, regValue);
}

hpm_stat_t sgtl_write_reg(sgtl_context_t *context, uint16_t reg, uint16_t val)
{
    rt_size_t size;
    rt_uint8_t data[4];
    data[0] = reg >> 8;
    data[1] = reg & 0xFF;
    data[2] = (uint8_t) (val>>8);
    data[3] = (uint8_t) (val & 0xFF);
    size = rt_i2c_master_send(context->i2c_bus, context->slave_address, RT_I2C_WR, data, 4U);
    if (size != 4) {
        return status_fail;
    }
    return status_success;
}

hpm_stat_t sgtl_read_reg(sgtl_context_t *context, uint16_t reg, uint16_t *val)
{
    rt_size_t size;
    rt_uint8_t r[2];
    uint8_t d[2];
    r[0] = reg >> 8;
    r[1] = reg & 0xFF;

    size = rt_i2c_master_send(context->i2c_bus, context->slave_address, RT_I2C_WR, r, 2U);
    if (size != 2) {
        return status_fail;
    }

    size = rt_i2c_master_recv(context->i2c_bus, context->slave_address, RT_I2C_RD, d, 2U);
    if (size != 2) {
        return status_fail;
    }
    *val = (uint16_t)((d[0] << 8) | d[1]);
    return status_success;
}

hpm_stat_t sgtl_modify_reg(sgtl_context_t *context, uint16_t reg, uint16_t clr_mask, uint16_t val)
{
    hpm_stat_t retval = 0;
    uint16_t reg_val;

    /* Read the register value out */
    retval = sgtl_read_reg(context, reg, &reg_val);
    if (retval != status_success)
    {
        return status_fail;
    }

    /* Modify the value */
    reg_val &= clr_mask;
    reg_val |= val;

    /* Write the data to register */
    retval = sgtl_write_reg(context, reg, reg_val);
    if (retval != status_success)
    {
        return status_fail;
    }

    return status_success;
}
