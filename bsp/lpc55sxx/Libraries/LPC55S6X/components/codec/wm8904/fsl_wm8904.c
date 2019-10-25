/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wm8904.h"
#if WM8904_DEBUG_REGISTER
#include "fsl_debug_console.h"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief wm8904 volume mapping */
#define WM8904_MAP_DAC_ADC_VOLUME(volume) (volume * (255 / 100U))
#define WM8904_MAP_PGA_VOLUME(volume) (volume > 0x1FU ? 0x1FU : volume)
#define WM8904_MAP_HEADPHONE_LINEOUT_VOLUME(volume) (volume > 0x3FU ? 0x3FU : volume)
#define WM8904_SWAP_UINT16_BYTE_SEQUENCE(x) (__REV16(x))
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief WM8904 update format.
 *
 * @param handle WM8904 handle structure.
 * @param format format configurations.
 * @return kStatus_Success, else failed.
 */
static status_t WM8904_UpdateFormat(wm8904_handle_t *handle, wm8904_audio_format_t *format);

/*!
 * @brief WM8904 wait on write sequencer.
 *
 * @param handle WM8904 handle structure.
 * @return kStatus_Success, else failed.
 */
static status_t WM8904_WaitOnWriteSequencer(wm8904_handle_t *handle);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if WM8904_DEBUG_REGISTER
/*! @brief register definition */
static const uint8_t allRegisters[] = {
    0x00, 0x04, 0x05, 0x06, 0x07, 0x0A, 0x0C, 0x0E, 0x0F, 0x12, 0x14, 0x15, 0x16, 0x18, 0x19, 0x1A, 0x1B,
    0x1E, 0x1F, 0x20, 0x21, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x43, 0x44, 0x45, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x5A, 0x5E, 0x62,
    0x68, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
    0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0xC6, 0xF7, 0xF8};
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
static status_t WM8904_UpdateFormat(wm8904_handle_t *handle, wm8904_audio_format_t *format)
{
    status_t result;

    /* Disable SYSCLK */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_2, 0x00);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Set Clock ratio and sample rate */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_1, (format->fsRatio << 10) | format->sampleRate);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Set bit resolution */
    result = WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 0x000C, format->bitWidth);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Enable SYSCLK */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_2, 0x1007);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

static status_t WM8904_WaitOnWriteSequencer(wm8904_handle_t *handle)
{
    status_t result;
    uint16_t value;

    do
    {
        result = WM8904_ReadRegister(handle, WM8904_WRT_SEQUENCER_4, &value);
    } while ((result == kStatus_WM8904_Success) && (value & 1));

    return result;
}

/*!
 * brief WM8904 write register.
 *
 * param handle WM8904 handle structure.
 * param reg register address.
 * param value value to write.
 * return kStatus_Success, else failed.
 */
status_t WM8904_WriteRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t value)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    uint16_t writeValue = WM8904_SWAP_UINT16_BYTE_SEQUENCE(value);

    return CODEC_I2C_Send(&(handle->i2cHandle), handle->config->slaveAddress, reg, 1U, (uint8_t *)&writeValue, 2U);
}

/*!
 * brief WM8904 write register.
 *
 * param handle WM8904 handle structure.
 * param reg register address.
 * param value value to read.
 * return kStatus_Success, else failed.
 */
status_t WM8904_ReadRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t *value)
{
    assert(handle->config != NULL);
    assert(handle->config->slaveAddress != 0U);

    uint8_t retval     = 0;
    uint16_t readValue = 0U;

    retval = CODEC_I2C_Receive(&(handle->i2cHandle), handle->config->slaveAddress, reg, 1U, (uint8_t *)&readValue, 2U);

    *value = WM8904_SWAP_UINT16_BYTE_SEQUENCE(readValue);

    return retval;
}

/*!
 * brief WM8904 modify register.
 *
 * param handle WM8904 handle structure.
 * param reg register address.
 * oaram mask register bits mask.
 * param value value to write.
 * return kStatus_Success, else failed.
 */
status_t WM8904_ModifyRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t mask, uint16_t value)
{
    status_t result;
    uint16_t regValue;

    result = WM8904_ReadRegister(handle, reg, &regValue);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    regValue &= (uint16_t)~mask;
    regValue |= value;

    return WM8904_WriteRegister(handle, reg, regValue);
}

/*!
 * brief Initializes WM8904.
 *
 * param handle WM8904 handle structure.
 * param codec_config WM8904 configuration structure.
 */
status_t WM8904_Init(wm8904_handle_t *handle, wm8904_config_t *wm8904Config)
{
    assert(handle != NULL);
    assert(wm8904Config != NULL);

    status_t result;
    wm8904_config_t *config = wm8904Config;
    handle->config          = config;

    /* i2c bus initialization */
    result = CODEC_I2C_Init(&(handle->i2cHandle), wm8904Config->i2cConfig.codecI2CInstance, WM8904_I2C_BITRATE,
                            wm8904Config->i2cConfig.codecI2CSourceClock);
    if (result != kStatus_HAL_I2cSuccess)
    {
        return kStatus_WM8904_Fail;
    }

    /* reset */
    result = WM8904_WriteRegister(handle, WM8904_RESET, 0x0000);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* MCLK_INV=0, SYSCLK_SRC=0, TOCLK_RATE=0, OPCLK_ENA=1,
     * CLK_SYS_ENA=1, CLK_DSP_ENA=1, TOCLK_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_2, 0x000F);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* WSEQ_ENA=1, WSEQ_WRITE_INDEX=0_0000 */
    result = WM8904_WriteRegister(handle, WM8904_WRT_SEQUENCER_0, 0x0100);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* WSEQ_ABORT=0, WSEQ_START=1, WSEQ_START_INDEX=00_0000 */
    result = WM8904_WriteRegister(handle, WM8904_WRT_SEQUENCER_3, 0x0100);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_WaitOnWriteSequencer(handle);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* TOCLK_RATE_DIV16=0, TOCLK_RATE_x4=1, SR_MODE=0, MCLK_DIV=1
     * (Required for MMCs: SGY, KRT see erratum CE000546) */
    result = WM8904_WriteRegister(handle, WM8904_CLK_RATES_0, 0xA45F);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* INL_ENA=1, INR ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_POWER_MGMT_0, 0x0003);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPL_PGA_ENA=1, HPR_PGA_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_POWER_MGMT_2, 0x0003);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* DACL_ENA=1, DACR_ENA=1, ADCL_ENA=1, ADCR_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_POWER_MGMT_6, 0x000F);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* ADC_OSR128=1 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_ADC_0, 0x0001);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* DACL_DATINV=0, DACR_DATINV=0, DAC_BOOST=00, LOOPBACK=0, AIFADCL_SRC=0,
     * AIFADCR_SRC=1, AIFDACL_SRC=0, AIFDACR_SRC=1, ADC_COMP=0, ADC_COMPMODE=0,
     * DAC_COMP=0, DAC_COMPMODE=0 */
    result = WM8904_WriteRegister(handle, WM8904_AUDIO_IF_0, 0x0050);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* DAC_MONO=0, DAC_SB_FILT-0, DAC_MUTERATE=0, DAC_UNMUTE RAMP=0,
     * DAC_OSR128=1, DAC_MUTE=0, DEEMPH=0 (none) */
    result = WM8904_WriteRegister(handle, WM8904_DAC_DIG_1, 0x0040);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* LINMUTE=0, LIN_VOL=0_0101 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_LEFT_IN_0, 0x0005);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* RINMUTE=0, RIN VOL=0_0101 LINEOUTL RMV SHORT-1, LINEOUTL ENA_OUTP=1,
     * LINEOUTL_ENA_DLY=1, LINEOUTL_ENA=1, LINEOUTR_RMV_SHORT-1,
     * LINEOUTR_ENA_OUTP=1 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_RIGHT_IN_0, 0x0005);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPOUTL_MUTE=0, HPOUT_VU=0, HPOUTLZC=0, HPOUTL_VOL=11_1001 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x0039);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPOUTR_MUTE=0, HPOUT_VU=0, HPOUTRZC=0, HPOUTR_VOL=11_1001 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0x0039);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* Enable DC servos for headphone out */
    result = WM8904_WriteRegister(handle, WM8904_DC_SERVO_0, 0x0003);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* HPL_RMV_SHORT=1, HPL_ENA_OUTP=1, HPL_ENA_DLY=1, HPL_ENA=1,
     * HPR_RMV_SHORT=1, HPR_ENA_OUTP=1, HPR_ENA_DLY=1, HPR_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_ANALOG_HP_0, 0x00FF);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* CP_DYN_PWR=1 */
    result = WM8904_WriteRegister(handle, WM8904_CLS_W_0, 0x0001);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* CP_ENA=1 */
    result = WM8904_WriteRegister(handle, WM8904_CHRG_PUMP_0, 0x0001);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* set wm8904 as slave */
    result = WM8904_SetMasterSlave(handle, config->master);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* set audio format */
    result = WM8904_SetProtocol(handle, config->protocol);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_CheckAudioFormat(handle, &config->format, config->mclk_HZ);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    /* set record source and channel */
    result = WM8904_SetRecord(handle, config->recordSource);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }
    result = WM8904_SetRecordChannel(handle, config->recordChannelLeft, config->recordChannelRight);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }
    /* set play source */
    result = WM8904_SetPlay(handle, config->playSource);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return result;
}

/*!
 * brief Deinitializes the WM8904 codec.
 *
 * This function resets WM8904.
 *
 * param handle WM8904 handle structure.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_Deinit(wm8904_handle_t *handle)
{
    /* reset */
    if (WM8904_WriteRegister(handle, WM8904_RESET, 0x0000) == kStatus_WM8904_Success)
    {
        return CODEC_I2C_Deinit(&(handle->i2cHandle));
    }

    return kStatus_WM8904_Fail;
}

/*!
 * brief Fills the configuration structure with default values.
 *
 * The default values are:
 *
 *   master = false;
 *   protocol = kWM8904_ProtocolI2S;
 *   format.fsRatio = kWM8904_FsRatio64X;
 *   format.sampleRate = kWM8904_SampleRate48kHz;
 *   format.bitWidth = kWM8904_BitWidth16;
 *
 * param handle WM8904 handle structure to be filled with default values.
 */
void WM8904_GetDefaultConfig(wm8904_config_t *config)
{
    memset(config, 0, sizeof(wm8904_config_t));

    config->master            = false;
    config->protocol          = kWM8904_ProtocolI2S;
    config->format.sampleRate = kWM8904_SampleRate48kHz;
    config->format.bitWidth   = kWM8904_BitWidth16;
}

/*!
 * brief Sets WM8904 as master or slave.
 *
 * param handle WM8904 handle structure.
 * param master true for master, false for slave.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMasterSlave(wm8904_handle_t *handle, bool master)
{
    if (master)
    {
        /* only slave currently supported */
        return kStatus_WM8904_Fail;
    }

    return kStatus_WM8904_Success;
}

/*!
 * brief Sets the audio data transfer protocol.
 *
 * param handle WM8904 handle structure.
 * param protocol Audio transfer protocol.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetProtocol(wm8904_handle_t *handle, wm8904_protocol_t protocol)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, (0x0003 | (1U << 4U)), (uint16_t)protocol);
}

/*!
 * brief Select LRC polarity.
 *
 * param handle WM8904 handle structure.
 * param polarity LRC clock polarity.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SelectLRCPolarity(wm8904_handle_t *handle, uint32_t polarity)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 0x0010, polarity);
}

/*!
 * brief Enable WM8904 DAC time slot.
 *
 * param handle WM8904 handle structure.
 * param timeslot timeslot number.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_EnableDACTDMMode(wm8904_handle_t *handle, wm8904_timeslot_t timeSlot)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 3U << 12U, 1U << 13U | timeSlot << 12U);
}

/*!
 * brief Enable WM8904 ADC time slot.
 *
 * param handle WM8904 handle structure.
 * param timeslot timeslot number.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_EnableADCTDMMode(wm8904_handle_t *handle, wm8904_timeslot_t timeSlot)
{
    return WM8904_ModifyRegister(handle, WM8904_AUDIO_IF_1, 3U << 10U, 1U << 11U | timeSlot << 10U);
}

/*!
 * brief check and update the audio data format.
 * This api is used check the fsRatio setting based on the mclk and sample rate, if fsRatio setting
 * is not correct, it will correct it according to mclk and sample rate.
 * param handle WM8904 handle structure.
 * param format audio data format
 * param mclkFreq mclk frequency
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_CheckAudioFormat(wm8904_handle_t *handle, wm8904_audio_format_t *format, uint32_t mclkFreq)
{
    assert(handle && format);

    status_t result;
    uint16_t mclkDiv    = 0U;
    uint32_t sampleRate = 0U;
    uint32_t fsRatio    = 0U;

    result = WM8904_ReadRegister(handle, WM8904_CLK_RATES_0, &mclkDiv);
    if (kStatus_WM8904_Success != result)
    {
        return result;
    }

    switch (format->sampleRate)
    {
        case kWM8904_SampleRate8kHz:
            sampleRate = 8000;
            break;
        case kWM8904_SampleRate12kHz:
            sampleRate = 12000;
            break;
        case kWM8904_SampleRate16kHz:
            sampleRate = 16000;
            break;
        case kWM8904_SampleRate24kHz:
            sampleRate = 24000;
            break;
        case kWM8904_SampleRate32kHz:
            sampleRate = 32000;
            break;
        case kWM8904_SampleRate48kHz:
            sampleRate = 48000;
            break;
        default:
            break;
    }

    fsRatio = (mclkFreq >> (mclkDiv & 0x1U)) / sampleRate;

    switch (fsRatio)
    {
        case 64:
            format->fsRatio = kWM8904_FsRatio64X;
            break;
        case 128:
            format->fsRatio = kWM8904_FsRatio128X;
            break;
        case 192:
            format->fsRatio = kWM8904_FsRatio192X;
            break;
        case 256:
            format->fsRatio = kWM8904_FsRatio256X;
            break;
        case 384:
            format->fsRatio = kWM8904_FsRatio384X;
            break;
        case 512:
            format->fsRatio = kWM8904_FsRatio512X;
            break;
        case 768:
            format->fsRatio = kWM8904_FsRatio768X;
            break;
        case 1024:
            format->fsRatio = kWM8904_FsRatio1024X;
            break;
        case 1408:
            format->fsRatio = kWM8904_FsRatio1408X;
            break;
        case 1536:
            format->fsRatio = kWM8904_FsRatio1536X;
            break;
        default:
            break;
    }

    return WM8904_UpdateFormat(handle, format);
}

/*!
 * brief Sets the audio data format.
 *
 * param handle WM8904 handle structure.
 * param sysclk System clock frequency for codec, user should pay attention to this parater, sysclk is caculate as
 * SYSCLK = MCLK / MCLKDIV, MCLKDIV is bit0 of WM8904_CLK_RATES_0.
 * param sampleRate Sample rate frequency in Hz.
 * param bitWidth Audio data bit width.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetAudioFormat(wm8904_handle_t *handle, uint32_t sysclk, uint32_t sampleRate, uint32_t bitWidth)
{
    status_t result;
    wm8904_audio_format_t format;
    uint32_t ratio = 0;

    switch (sampleRate)
    {
        case 8000:
            format.sampleRate = kWM8904_SampleRate8kHz;
            break;
        case 11025:
        case 12000:
            format.sampleRate = kWM8904_SampleRate12kHz;
            break;
        case 16000:
            format.sampleRate = kWM8904_SampleRate16kHz;
            break;
        case 22050:
        case 24000:
            format.sampleRate = kWM8904_SampleRate24kHz;
            break;
        case 32000:
            format.sampleRate = kWM8904_SampleRate32kHz;
            break;
        case 44100:
        case 48000:
            format.sampleRate = kWM8904_SampleRate48kHz;
            break;
        default:
            return kStatus_WM8904_Fail;
    }

    switch (bitWidth)
    {
        case 16:
            format.bitWidth = kWM8904_BitWidth16;
            break;
        case 20:
            format.bitWidth = kWM8904_BitWidth20;
            break;
        case 24:
            format.bitWidth = kWM8904_BitWidth24;
            break;
        case 32:
            format.bitWidth = kWM8904_BitWidth32;
            break;
        default:
            break;
    }

    ratio = sysclk / sampleRate;
    switch (ratio)
    {
        case 64:
            format.fsRatio = kWM8904_FsRatio64X;
            break;
        case 128:
            format.fsRatio = kWM8904_FsRatio128X;
            break;
        case 192:
            format.fsRatio = kWM8904_FsRatio192X;
            break;
        case 256:
            format.fsRatio = kWM8904_FsRatio256X;
            break;
        case 384:
            format.fsRatio = kWM8904_FsRatio384X;
            break;
        case 512:
            format.fsRatio = kWM8904_FsRatio512X;
            break;
        case 768:
            format.fsRatio = kWM8904_FsRatio768X;
            break;
        case 1024:
            format.fsRatio = kWM8904_FsRatio1024X;
            break;
        case 1408:
            format.fsRatio = kWM8904_FsRatio1408X;
            break;
        case 1536:
            format.fsRatio = kWM8904_FsRatio1536X;
            break;
        default:
            return kStatus_WM8904_Fail;
    }

    result = WM8904_UpdateFormat(handle, &format);

    return result;
}

/*!
 * brief Sets the headphone output volume.
 *
 * The parameter should be from 0 to 63.
 * The resulting volume will be (parameter - 57 dB).
 * 0 for -57 dB, 57 for 0 dB, 63 for +6 dB etc.
 *
 * param handle WM8904 handle structure.
 * param volumeLeft Volume of the left channel.
 * param volumeRight Volume of the right channel.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetVolume(wm8904_handle_t *handle, uint16_t volumeLeft, uint16_t volumeRight)
{
    status_t result;

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x3F, volumeLeft);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0xBF, volumeRight | 0x0080);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

/*!
 * brief Sets the headphone output mute.
 *
 * param handle WM8904 handle structure.
 * param muteLeft true to mute left channel, false to unmute.
 * param muteRight true to mute right channel, false to unmute.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMute(wm8904_handle_t *handle, bool muteLeft, bool muteRight)
{
    status_t result;
    uint16_t left  = muteLeft ? 0x0100 : 0x0000;
    uint16_t right = muteRight ? 0x0100 : 0x0000;

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, 0x0100, left);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    result = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, 0x0180, right | 0x0080);
    if (result != kStatus_WM8904_Success)
    {
        return result;
    }

    return kStatus_WM8904_Success;
}

#if WM8904_DEBUG_REGISTER
/*!
 * brief Reads content of all WM8904 registers and prints it to debug console.
 *
 * param handle WM8904 handle structure.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_PrintRegisters(wm8904_handle_t *handle)
{
    status_t result;
    uint16_t value;
    uint32_t i;

    for (i = 0; i < sizeof(allRegisters); i++)
    {
        result = WM8904_ReadRegister(handle, allRegisters[i], &value);
        if (result != kStatus_WM8904_Success)
        {
            PRINTF("\r\n");
            return result;
        }
        PRINTF("%s", ((i % 8) == 0) ? "\r\n" : "\t");
        PRINTF("%02X:%04X", allRegisters[i], value);
    }

    PRINTF("\r\n");
    return result;
}
#endif

/*!
 * brief Sets the channel output volume.
 *
 * The parameter should be from 0 to 100.
 * The resulting volume will be.
 * 0 for mute, 100 for maximum volume value.
 *
 * param handle codec handle structure.
 * param channel codec channel.
 * param volume volume value.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetChannelVolume(wm8904_handle_t *handle, uint32_t channel, uint32_t volume)
{
    status_t ret = kStatus_Fail;
    volume       = WM8904_MAP_HEADPHONE_LINEOUT_VOLUME(volume);

    /* headphone left channel */
    if (channel & kWM8904_HeadphoneLeft)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, volume == 0U ? 0x100U : 0x3FU,
                                    volume == 0U ? 0x100U : (volume));
    }
    /* headphone right channel */
    if (channel & kWM8904_HeadphoneRight)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, volume == 0U ? 0x100U : 0xBFU,
                                    volume == 0U ? 0x100U : (volume | 0x80U));
    }
    /* line out left channel */
    if (channel & kWM8904_LineoutLeft)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_LEFT, volume == 0U ? 0x100U : 0x3FU,
                                    volume == 0U ? 0x100U : (volume));
    }
    /* line out right channel */
    if (channel & kWM8904_LineoutRight)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_RIGHT, volume == 0U ? 0x100U : 0xBFU,
                                    volume == 0U ? 0x100U : (volume | 0x80U));
    }

    return ret;
}

/*!
 * brief Sets the channel mute.
 *
 * param handle codec handle structure.
 * param channel codec module name.
 * param isMute true is mute, false unmute.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetChannelMute(wm8904_handle_t *handle, uint32_t channel, bool isMute)
{
    status_t ret      = kStatus_Fail;
    uint16_t regValue = 0U, regMask = 0U;

    regValue = isMute ? 0x180U : 0x80U;
    regMask  = 0x100U;

    /* headphone left channel */
    if (channel & kWM8904_HeadphoneLeft)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_LEFT, regMask, regValue);
    }

    /* headphone right channel */
    if (channel & kWM8904_HeadphoneRight)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT1_RIGHT, regMask, regValue);
    }

    /* line out left channel */
    if (channel & kWM8904_LineoutLeft)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_LEFT, regMask, regValue);
    }

    /* line out right channel */
    if (channel & kWM8904_LineoutRight)
    {
        ret = WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT2_RIGHT, regMask, regValue);
    }

    return ret;
}

/*!
 * brief SET the module output power.
 *
 * param handle WM8904 handle structure.
 * param module wm8904 module.
 * param isEnabled, true is power on, false is power down.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetModulePower(wm8904_handle_t *handle, wm8904_module_t module, bool isEnabled)
{
    uint8_t regAddr = 0, regBitMask = 0U, regValue = 0U;

    switch (module)
    {
        case kWM8904_ModuleADC:
            regAddr    = WM8904_POWER_MGMT_6;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;
            break;
        case kWM8904_ModuleDAC:
            regAddr    = WM8904_POWER_MGMT_6;
            regBitMask = 0xCU;
            regValue   = isEnabled ? 0xCU : 0U;

            break;
        case kWM8904_ModulePGA:
            regAddr    = WM8904_POWER_MGMT_0;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;

            break;
        case kWM8904_ModuleHeadphone:
            regAddr    = WM8904_POWER_MGMT_2;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;
            break;
        case kWM8904_ModuleLineout:
            regAddr    = WM8904_POWER_MGMT_3;
            regBitMask = 3U;
            regValue   = isEnabled ? 3U : 0U;
            break;
        default:
            return kStatus_InvalidArgument;
    }

    return WM8904_ModifyRegister(handle, regAddr, regBitMask, regValue);
}

/*!
 * brief SET the WM8904 record source.
 *
 * param handle WM8904 handle structure.
 * param recordSource record source , can be a value of kWM8904_ModuleRecordSourceDifferentialLine,
 * kWM8904_ModuleRecordSourceDifferentialMic, kWM8904_ModuleRecordSourceSingleEndMic,
 * kWM8904_ModuleRecordSourceDigitalMic.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetRecord(wm8904_handle_t *handle, uint32_t recordSource)
{
    uint8_t regLeftAddr = WM8904_ANALOG_LEFT_IN_1, regRightAddr = WM8904_ANALOG_RIGHT_IN_1;
    uint16_t regLeftValue = 0U, regRightValue = 0U, regBitMask;
    status_t ret = kStatus_Success;

    switch (recordSource)
    {
        case kWM8904_RecordSourceDifferentialLine:
            regLeftValue  = 1U;
            regRightValue = 1U;
            regBitMask    = 0x3FU;
            break;
        case kWM8904_RecordSourceDifferentialMic:
            regLeftValue  = 2U;
            regRightValue = 2U;
            regBitMask    = 0x3FU;
            break;
        case kWM8904_RecordSourceLineInput:
            regLeftValue  = 0U;
            regRightValue = 0U;
            regBitMask    = 0x3FU;
            break;
        case kWM8904_RecordSourceDigitalMic:
            regLeftValue = (1U << 12U);
            regLeftAddr  = WM8904_DAC_DIG_0;
            regRightAddr = 0U;
            regBitMask   = 1U << 12U;
            break;

        default:
            return kStatus_InvalidArgument;
    }

    ret = WM8904_ModifyRegister(handle, regLeftAddr, regBitMask, regLeftValue);

    if ((ret == kStatus_Success) && (regRightAddr))
    {
        return WM8904_ModifyRegister(handle, regRightAddr, regBitMask, regRightValue);
    }

    return kStatus_Success;
}

/*!
 * brief SET the WM8904 record source.
 *
 * param handle WM8904 handle structure.
 * param leftRecordChannel channel number of left record channel when using differential source, channel number of
 * single end left channel when using single end source, channel number of digital mic when using digital mic source.
 * param rightRecordChannel channel number of right record channel when using differential source, channel number
 * of single end right channel when using single end source.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetRecordChannel(wm8904_handle_t *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
{
    uint8_t regLeftAddr = WM8904_ANALOG_LEFT_IN_1, regRightAddr = WM8904_ANALOG_RIGHT_IN_1;
    uint16_t regLeftValue = 0U, regRightValue = 0U, regBitMask;
    status_t ret                = kStatus_Success;
    uint8_t leftPositiveChannel = 0U, leftNegativeChannel = 0U, rightPositiveChannel = 0U, rightNegativeChannel = 0U;

    if (leftRecordChannel & kWM8904_RecordChannelDifferentialPositive1)
    {
        leftPositiveChannel = 0U;
    }
    else if (leftRecordChannel & kWM8904_RecordChannelDifferentialPositive2)
    {
        leftPositiveChannel = 1U;
    }
    else
    {
        leftPositiveChannel = 2U;
    }

    if (leftRecordChannel & kWM8904_RecordChannelDifferentialNegative1)
    {
        leftNegativeChannel = 0U;
    }
    else if (leftRecordChannel & kWM8904_RecordChannelDifferentialNegative2)
    {
        leftNegativeChannel = 1U;
    }
    else if (leftRecordChannel & kWM8904_RecordChannelDifferentialNegative3)
    {
        leftNegativeChannel = 2U;
    }
    else
    {
        leftNegativeChannel = leftPositiveChannel;
    }

    if (rightRecordChannel & kWM8904_RecordChannelDifferentialPositive1)
    {
        rightPositiveChannel = 0U;
    }
    else if (rightRecordChannel & kWM8904_RecordChannelDifferentialPositive2)
    {
        rightPositiveChannel = 1U;
    }
    else
    {
        rightPositiveChannel = 2U;
    }

    if (rightRecordChannel & kWM8904_RecordChannelDifferentialNegative1)
    {
        rightNegativeChannel = 0U;
    }
    else if (rightRecordChannel & kWM8904_RecordChannelDifferentialNegative2)
    {
        rightNegativeChannel = 1U;
    }
    else if (rightRecordChannel & kWM8904_RecordChannelDifferentialNegative3)
    {
        rightNegativeChannel = 2U;
    }
    else
    {
        rightNegativeChannel = rightPositiveChannel;
    }

    regLeftValue  = ((leftNegativeChannel & 3U) << 4U) | ((leftPositiveChannel & 3U) << 2U);
    regRightValue = ((rightNegativeChannel & 3U) << 4U) | ((rightPositiveChannel & 3U) << 2U);
    regBitMask    = 0x3CU;

    ret = WM8904_ModifyRegister(handle, regLeftAddr, regBitMask, regLeftValue);

    if ((ret == kStatus_Success) && (regRightAddr))
    {
        return WM8904_ModifyRegister(handle, regRightAddr, regBitMask, regRightValue);
    }

    return kStatus_Success;
}

/*!
 * brief SET the WM8904 play source.
 *
 * param handle WM8904 handle structure.
 * param playSource play source , can be a value of kWM8904_PlaySourcePGA/kWM8904_PlaySourceDAC.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetPlay(wm8904_handle_t *handle, uint32_t playSource)
{
    uint16_t regValue = 0U, regBitMask = 0xFU;

    /* source form PGA*/
    if (playSource == kWM8904_PlaySourcePGA)
    {
        regValue |= (3U << 2U) | 3U;
    }
    /* source from DAC*/
    if (playSource == kWM8904_PlaySourceDAC)
    {
        regValue &= ~((3U << 2U) | 3U);
    }

    return WM8904_ModifyRegister(handle, WM8904_ANALOG_OUT12_ZC, regBitMask, regValue);
}
