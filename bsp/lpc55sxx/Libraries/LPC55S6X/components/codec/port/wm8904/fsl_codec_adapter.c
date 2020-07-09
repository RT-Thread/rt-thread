/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_wm8904.h"
#include "fsl_codec_adapter.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief module capability definition */
#define HAL_WM8904_MODULE_CAPABILITY                                                                              \
    kCODEC_SupportModuleADC | kCODEC_SupportModuleDAC | kCODEC_SupportModulePGA | kCODEC_SupportModuleHeadphone | \
        kCODEC_SupportModuleLineout
#define HAL_WM8904_PLAY_CAPABILITY                                                                      \
    kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0 | kCODEC_SupportPlayChannelLeft1 | \
        kCODEC_SupportPlayChannelRight1 | kCODEC_SupportPlaySourcePGA | kCODEC_SupportPlaySourceDAC
#define HAL_WM8904_RECORD_CAPABILITY                                                                             \
    kCODEC_SupportRecordSourceDifferentialLine | kCODEC_SupportRecordSourceDifferentialMic |                     \
        kCODEC_SupportRecordSourceLineInput | kCODEC_SupportRecordSourceDigitalMic |                             \
        kCODEC_SupportRecordChannelLeft1 | kCODEC_SupportRecordChannelLeft2 | kCODEC_SupportRecordChannelLeft3 | \
        kCODEC_SupportRecordChannelRight1 | kCODEC_SupportRecordChannelRight2 | kCODEC_SupportRecordChannelRight3

/*! @brief wm8904 map protocol */
#define HAL_WM8904_MAP_PROTOCOL(protocol)                    \
    (protocol == kCODEC_BusI2S ?                             \
         kWM8904_ProtocolI2S :                               \
         protocol == kCODEC_BusLeftJustified ?               \
         kWM8904_ProtocolLeftJustified :                     \
         protocol == kCODEC_BusRightJustified ?              \
         kWM8904_ProtocolRightJustified :                    \
         protocol == kCODEC_BusPCMA ? kWM8904_ProtocolPCMA : \
                                      protocol == kCODEC_BusPCMB ? kWM8904_ProtocolPCMB : kWM8904_ProtocolI2S)

/*! @brief wm8904 map module */
#define HAL_WM8904_MAP_MODULE(module)                                    \
    (module == kCODEC_ModuleADC ?                                        \
         kWM8904_ModuleADC :                                             \
         module == kCODEC_ModuleDAC ?                                    \
         kWM8904_ModuleDAC :                                             \
         module == kCODEC_ModulePGA ? kWM8904_ModulePGA :                \
                                      module == kCODEC_ModuleHeadphone ? \
                                      kWM8904_ModuleHeadphone :          \
                                      module == kCODEC_ModuleLineout ? kWM8904_ModuleLineout : kWM8904_ModuleADC)

/*! @brief wm8904 map protocol */
#define HAL_WM8904_MAP_SAMPLERATE(sampleRATE)        \
    (sampleRATE == kCODEC_AudioSampleRate8KHz ?      \
         kWM8904_SampleRate8kHz :                    \
         sampleRATE == kCODEC_AudioSampleRate12KHz ? \
         kWM8904_SampleRate12kHz :                   \
         sampleRATE == kCODEC_AudioSampleRate16KHz ? \
         kWM8904_SampleRate16kHz :                   \
         sampleRATE == kCODEC_AudioSampleRate24KHz ? \
         kWM8904_SampleRate24kHz :                   \
         sampleRATE == kCODEC_AudioSampleRate32KHz ? kWM8904_SampleRate32kHz : kWM8904_SampleRate48kHz)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Codec initilization.
 *
 * param handle codec handle.
 * param config codec configuration.
 * return kStatus_Success is success, else initial failed.
 */
status_t HAL_CODEC_Init(codec_handle_t *handle, void *config)
{
    assert((config != NULL) && (handle != NULL));
    assert(CODEC_HANDLE_SIZE >= (sizeof(codec_handle_t) + sizeof(wm8904_handle_t)) + HAL_I2C_MASTER_HANDLE_SIZE);

    codec_config_t *codecConfig = (codec_config_t *)config;

    wm8904_config_t *wm8904Config = (wm8904_config_t *)(codecConfig->codecDevConfig);
    wm8904_handle_t *wm8904Handle = (wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle));

    /* load codec capability */
    handle->codecCapability.codecModuleCapability = HAL_WM8904_MODULE_CAPABILITY;
    /* add nop to aovid alignment fault, since that the compiler may generate 'strd' instruction to store 64 bit
    with one instruction, but the address may not word-aligned
    Will remove the __NOP in next release and use a word align address.
    */
    __NOP();
    handle->codecCapability.codecPlayCapability = HAL_WM8904_PLAY_CAPABILITY;
    /* add nop to aovid alignment fault, since that the compiler may generate 'strd' instruction to store 64 bit
    with one instruction, but the address may not word-aligned
    Will remove the __NOP in next release and use a word align address.
    */
    __NOP();
    handle->codecCapability.codecRecordCapability = HAL_WM8904_RECORD_CAPABILITY;
    /* codec device initialization */
    return WM8904_Init(wm8904Handle, wm8904Config);
}

/*!
 * brief Codec de-initilization.
 *
 * param handle codec handle.
 * return kStatus_Success is success, else de-initial failed.
 */
status_t HAL_CODEC_Deinit(codec_handle_t *handle)
{
    assert(handle != NULL);

    return WM8904_Deinit((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)));
}

/*!
 * brief set audio data format.
 *
 * param handle codec handle.
 * param mclk master clock frequency in HZ.
 * param sampleRate sample rate in HZ.
 * param bitWidth bit width.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetFormat(codec_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth)
{
    assert(handle != NULL);

    return WM8904_SetAudioFormat((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)), mclk,
                                 HAL_WM8904_MAP_SAMPLERATE(sampleRate), bitWidth);
}

/*!
 * brief set audio codec module volume.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param volume volume value, support 0 ~ 100, 0 is mute, 100 is the maximum volume value.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetVolume(codec_handle_t *handle, uint32_t playChannel, uint32_t volume)
{
    assert(handle != NULL);

    return WM8904_SetChannelVolume((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)), playChannel, volume);
}

/*!
 * brief set audio codec module mute.
 *
 * param handle codec handle.
 * param channel audio codec play channel, can be a value or combine value of _codec_play_channel.
 * param isMute true is mute, false is unmute.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetMute(codec_handle_t *handle, uint32_t playChannel, bool isMute)
{
    assert(handle != NULL);

    return WM8904_SetChannelMute((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)), playChannel, isMute);
}

/*!
 * brief set audio codec module power.
 *
 * param handle codec handle.
 * param module audio codec module.
 * param powerOn true is power on, false is power down.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetPower(codec_handle_t *handle, codec_module_t module, bool powerOn)
{
    assert(handle != NULL);

    return WM8904_SetModulePower((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)),
                                 HAL_WM8904_MAP_MODULE(module), powerOn);
}

/*!
 * brief codec set record source.
 *
 * param handle codec handle.
 * param source audio codec record source, can be a value or combine value of _codec_record_source.
 *
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetRecord(codec_handle_t *handle, uint32_t recordSource)
{
    assert(handle != NULL);

    return WM8904_SetRecord((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)), recordSource);
}

/*!
 * brief codec set record channel.
 *
 * param handle codec handle.
 * param leftRecordChannel audio codec record channel, reference _codec_record_channel, can be a value or combine value
 of member in _codec_record_channel.
 * param rightRecordChannel audio codec record channel, reference _codec_record_channel, can be a value combine of
 member in _codec_record_channel.

 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetRecordChannel(codec_handle_t *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel)
{
    assert(handle != NULL);

    return WM8904_SetRecordChannel((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)), leftRecordChannel,
                                   rightRecordChannel);
}

/*!
 * brief codec set play source.
 *
 * param handle codec handle.
 * param playSource audio codec play source, can be a value or combine value of _codec_play_source.
 *
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_SetPlay(codec_handle_t *handle, uint32_t playSource)
{
    assert(handle != NULL);

    return WM8904_SetPlay((wm8904_handle_t *)((uint32_t) & (handle->codecDevHandle)), playSource);
}

/*!
 * brief codec module control.
 *
 * param handle codec handle.
 * param cmd module control cmd, reference _codec_module_ctrl_cmd.
 * param data value to write, when cmd is kCODEC_ModuleRecordSourceChannel, the data should be a value combine
 *  of channel and source, please reference macro CODEC_MODULE_RECORD_SOURCE_CHANNEL(source, LP, LN, RP, RN), reference
 *  codec specific driver for detail configurations.
 * return kStatus_Success is success, else configure failed.
 */
status_t HAL_CODEC_ModuleControl(codec_handle_t *handle, codec_module_ctrl_cmd_t cmd, uint32_t data)
{
    return kStatus_CODEC_NotSupport;
}
