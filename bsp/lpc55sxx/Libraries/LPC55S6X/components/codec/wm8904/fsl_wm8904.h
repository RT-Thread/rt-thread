/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_WM8904_H_
#define _FSL_WM8904_H_

#include "fsl_common.h"
#include "fsl_codec_i2c.h"
/*!
 * @addtogroup wm8904
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief WM8904 driver version 2.1.0. */
#define FSL_WM8904_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/*! @brief wm8904 handle size */
#ifndef WM8904_HANDLE_SIZE
#define WM8904_HANDLE_SIZE (100U)
#endif
/*! @brief wm8904 debug macro */
#ifndef WM8904_DEBUG_REGISTER
#define WM8904_DEBUG_REGISTER 0
#endif

/*! @brief WM8904 register map*/
#define WM8904_RESET (0x00)
#define WM8904_ANALOG_ADC_0 (0x0A)
#define WM8904_POWER_MGMT_0 (0x0C)
#define WM8904_POWER_MGMT_2 (0x0E)
#define WM8904_POWER_MGMT_3 (0x0F)
#define WM8904_POWER_MGMT_6 (0x12)
#define WM8904_CLK_RATES_0 (0x14)
#define WM8904_CLK_RATES_1 (0x15)
#define WM8904_CLK_RATES_2 (0x16)
#define WM8904_AUDIO_IF_0 (0x18)
#define WM8904_AUDIO_IF_1 (0x19)
#define WM8904_AUDIO_IF_2 (0x1A)
#define WM8904_AUDIO_IF_3 (0x1B)
#define WM8904_DAC_DIG_1 (0x21)
#define WM8904_DAC_DIG_0 (0x27)
#define WM8904_ANALOG_LEFT_IN_0 (0x2C)
#define WM8904_ANALOG_RIGHT_IN_0 (0x2D)
#define WM8904_ANALOG_LEFT_IN_1 (0x2E)
#define WM8904_ANALOG_RIGHT_IN_1 (0x2F)
#define WM8904_ANALOG_OUT1_LEFT (0x39)
#define WM8904_ANALOG_OUT1_RIGHT (0x3A)
#define WM8904_ANALOG_OUT12_ZC (0x3D)
#define WM8904_DC_SERVO_0 (0x43)
#define WM8904_ANALOG_HP_0 (0x5A)
#define WM8904_CHRG_PUMP_0 (0x62)
#define WM8904_CLS_W_0 (0x68)
#define WM8904_WRT_SEQUENCER_0 (0x6C)
#define WM8904_WRT_SEQUENCER_3 (0x6F)
#define WM8904_WRT_SEQUENCER_4 (0x70)
#define WM8904_DAC_DIGITAL_VOLUME_LEFT (0x1E)
#define WM8904_DAC_DIGITAL_VOLUME_RIGHT (0x1F)
#define WM8904_ADC_DIGITAL_VOLUME_LEFT (0x24)
#define WM8904_ADC_DIGITAL_VOLUME_RIGHT (0x25)
#define WM8904_ANALOG_OUT2_LEFT (0x3B)
#define WM8904_ANALOG_OUT2_RIGHT (0x3C)

/*! @brief WM8904 I2C address. */
#define WM8904_I2C_ADDRESS (0x1A)

/*! @brief WM8904 I2C bit rate. */
#define WM8904_I2C_BITRATE (400000U)

/*! @brief WM8904 status return codes. */
enum _wm8904_status
{
    kStatus_WM8904_Success = 0x0, /*!< Success */
    kStatus_WM8904_Fail    = 0x1  /*!< Failure */
};

/*! @brief WM8904  lrc polarity. */
enum _wm8904_lrc_polarity
{
    kWM8904_LRCPolarityNormal   = 0U,       /*!< LRC polarity  normal */
    kWM8904_LRCPolarityInverted = 1U << 4U, /*!< LRC polarity inverted */
};

/*! @brief wm8904 module value*/
typedef enum _wm8904_module
{
    kWM8904_ModuleADC       = 0, /*!< moduel ADC */
    kWM8904_ModuleDAC       = 1, /*!< module DAC */
    kWM8904_ModulePGA       = 2, /*!< module PGA */
    kWM8904_ModuleHeadphone = 3, /*!< module headphone */
    kWM8904_ModuleLineout   = 4, /*!< module line out */
} wm8904_module_t;

/*! @brief wm8904 play channel  */
enum _wm8904_play_channel
{
    kWM8904_HeadphoneLeft  = 1U,
    kWM8904_HeadphoneRight = 2U,
    kWM8904_LineoutLeft    = 4U,
    kWM8904_LineoutRight   = 8U,
};

/*! @brief WM8904 time slot. */
typedef enum _wm8904_timeslot
{
    kWM8904_TimeSlot0 = 0U, /*!< time slot0 */
    kWM8904_TimeSlot1 = 1U, /*!< time slot1 */
} wm8904_timeslot_t;

/*! @brief The audio data transfer protocol. */
typedef enum _wm8904_protocol
{
    kWM8904_ProtocolI2S            = 0x2,            /*!< I2S type */
    kWM8904_ProtocolLeftJustified  = 0x1,            /*!< Left justified mode */
    kWM8904_ProtocolRightJustified = 0x0,            /*!< Right justified mode */
    kWM8904_ProtocolPCMA           = 0x3,            /*!< PCM A mode */
    kWM8904_ProtocolPCMB           = 0x3 | (1 << 4), /*!< PCM B mode */
} wm8904_protocol_t;

/*! @brief The SYSCLK / fs ratio. */
typedef enum _wm8904_fs_ratio
{
    kWM8904_FsRatio64X   = 0x0, /*!< SYSCLK is   64 * sample rate * frame width */
    kWM8904_FsRatio128X  = 0x1, /*!< SYSCLK is  128 * sample rate * frame width */
    kWM8904_FsRatio192X  = 0x2, /*!< SYSCLK is  192 * sample rate * frame width */
    kWM8904_FsRatio256X  = 0x3, /*!< SYSCLK is  256 * sample rate * frame width */
    kWM8904_FsRatio384X  = 0x4, /*!< SYSCLK is  384 * sample rate * frame width */
    kWM8904_FsRatio512X  = 0x5, /*!< SYSCLK is  512 * sample rate * frame width */
    kWM8904_FsRatio768X  = 0x6, /*!< SYSCLK is  768 * sample rate * frame width */
    kWM8904_FsRatio1024X = 0x7, /*!< SYSCLK is 1024 * sample rate * frame width */
    kWM8904_FsRatio1408X = 0x8, /*!< SYSCLK is 1408 * sample rate * frame width */
    kWM8904_FsRatio1536X = 0x9  /*!< SYSCLK is 1536 * sample rate * frame width */
} wm8904_fs_ratio_t;

/*! @brief Sample rate. */
typedef enum _wm8904_sample_rate
{
    kWM8904_SampleRate8kHz  = 0x0, /*!< 8 kHz */
    kWM8904_SampleRate12kHz = 0x1, /*!< 11.025kHz, 12kHz */
    kWM8904_SampleRate16kHz = 0x2, /*!< 16kHz */
    kWM8904_SampleRate24kHz = 0x3, /*!< 22.05kHz, 24kHz */
    kWM8904_SampleRate32kHz = 0x4, /*!< 32kHz */
    kWM8904_SampleRate48kHz = 0x5  /*!< 44.1kHz, 48kHz */
} wm8904_sample_rate_t;

/*! @brief Bit width. */
typedef enum _wm8904_bit_width
{
    kWM8904_BitWidth16 = 0x0, /*!< 16 bits */
    kWM8904_BitWidth20 = 0x1, /*!< 20 bits */
    kWM8904_BitWidth24 = 0x2, /*!< 24 bits */
    kWM8904_BitWidth32 = 0x3  /*!< 32 bits */
} wm8904_bit_width_t;

/*! @brief wm8904 record source */
enum _wm8904_record_source
{
    kWM8904_RecordSourceDifferentialLine = 1U, /*!< record source from differential line */
    kWM8904_RecordSourceLineInput        = 2U, /*!< record source from line input */
    kWM8904_RecordSourceDifferentialMic  = 4U, /*!< record source from differential mic */
    kWM8904_RecordSourceDigitalMic       = 8U, /*!< record source from digital microphone */
};

/*! @brief wm8904 record channel*/
enum _wm8904_record_channel
{
    kWM8904_RecordChannelLeft1                 = 1U,  /*!< left record channel 1 */
    kWM8904_RecordChannelLeft2                 = 2U,  /*!< left record channel 2 */
    kWM8904_RecordChannelLeft3                 = 4U,  /*!< left record channel 3 */
    kWM8904_RecordChannelRight1                = 1U,  /*!< right record channel 1 */
    kWM8904_RecordChannelRight2                = 2U,  /*!< right record channel 2 */
    kWM8904_RecordChannelRight3                = 4U,  /*!< right record channel 3 */
    kWM8904_RecordChannelDifferentialPositive1 = 1U,  /*!< differential positive record channel 1 */
    kWM8904_RecordChannelDifferentialPositive2 = 2U,  /*!< differential positive record channel 2 */
    kWM8904_RecordChannelDifferentialPositive3 = 4U,  /*!< differential positive record channel 3 */
    kWM8904_RecordChannelDifferentialNegative1 = 8U,  /*!< differential negative record channel 1 */
    kWM8904_RecordChannelDifferentialNegative2 = 16U, /*!< differential negative record channel 2 */
    kWM8904_RecordChannelDifferentialNegative3 = 32U, /*!< differential negative record channel 3 */
};

/*! @brief wm8904 play source*/
enum _wm8904_play_source
{
    kWM8904_PlaySourcePGA = 1U, /*!< play source PGA, bypass ADC */
    kWM8904_PlaySourceDAC = 4U, /*!< play source Input3 */
};

/*! @brief Audio format configuration. */
typedef struct _wm8904_audio_format
{
    wm8904_fs_ratio_t fsRatio;       /*!< SYSCLK / fs ratio */
    wm8904_sample_rate_t sampleRate; /*!< Sample rate */
    wm8904_bit_width_t bitWidth;     /*!< Bit width */
} wm8904_audio_format_t;

/*! @brief Configuration structure of WM8904.*/
typedef struct _wm8904_config
{
    bool master;                  /*!< Master or slave */
    wm8904_protocol_t protocol;   /*!< Audio transfer protocol */
    wm8904_audio_format_t format; /*!< Audio format */
    uint32_t mclk_HZ;             /*!< MCLK frequency value */

    uint16_t recordSource;       /*!< record source */
    uint16_t recordChannelLeft;  /*!< record channel */
    uint16_t recordChannelRight; /*!< record channel */
    uint16_t playSource;         /*!< play source */

    uint8_t slaveAddress;         /*!< code device slave address */
    codec_i2c_config_t i2cConfig; /*!< i2c bus configuration */
} wm8904_config_t;

/*! @brief wm8904 codec handler
 * Applicationi should allocate a buffer with WM8904_HANDLE_SIZE for handle definition, such as
 * uint8_t wm8904HandleBuffer[WM8904_HANDLE_SIZE];
 * wm8904_handle_t *wm8904Handle = wm8904HandleBuffer;
 */
typedef struct _wm8904_handle
{
    wm8904_config_t *config; /*!< wm8904 config pointer */
    void *i2cHandle;         /*!< i2c handle */
} wm8904_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief WM8904 write register.
 *
 * @param handle WM8904 handle structure.
 * @param reg register address.
 * @param value value to write.
 * @return kStatus_Success, else failed.
 */
status_t WM8904_WriteRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t value);

/*!
 * @brief WM8904 write register.
 *
 * @param handle WM8904 handle structure.
 * @param reg register address.
 * @param value value to read.
 * @return kStatus_Success, else failed.
 */
status_t WM8904_ReadRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t *value);

/*!
 * @brief WM8904 modify register.
 *
 * @param handle WM8904 handle structure.
 * @param reg register address.
 * @oaram mask register bits mask.
 * @param value value to write.
 * @return kStatus_Success, else failed.
 */
status_t WM8904_ModifyRegister(wm8904_handle_t *handle, uint8_t reg, uint16_t mask, uint16_t value);

/*!
 * @brief Initializes WM8904.
 *
 * @param handle WM8904 handle structure.
 * @param codec_config WM8904 configuration structure.
 */
status_t WM8904_Init(wm8904_handle_t *handle, wm8904_config_t *wm8904_config);

/*!
 * @brief Deinitializes the WM8904 codec.
 *
 * This function resets WM8904.
 *
 * @param handle WM8904 handle structure.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_Deinit(wm8904_handle_t *handle);

/*!
 * @brief Fills the configuration structure with default values.
 *
 * The default values are:
 *
 *   master = false;
 *   protocol = kWM8904_ProtocolI2S;
 *   format.fsRatio = kWM8904_FsRatio64X;
 *   format.sampleRate = kWM8904_SampleRate48kHz;
 *   format.bitWidth = kWM8904_BitWidth16;
 *
 * @param handle WM8904 handle structure to be filled with default values.
 */
void WM8904_GetDefaultConfig(wm8904_config_t *config);

/*!
 * @brief Sets WM8904 as master or slave.
 *
 * @param handle WM8904 handle structure.
 * @param master true for master, false for slave.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMasterSlave(wm8904_handle_t *handle, bool master);

/*!
 * @brief Sets the audio data transfer protocol.
 *
 * @param handle WM8904 handle structure.
 * @param protocol Audio transfer protocol.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetProtocol(wm8904_handle_t *handle, wm8904_protocol_t protocol);

/*!
 * @brief Sets the audio data format.
 *
 * @param handle WM8904 handle structure.
 * @param sysclk System clock frequency for codec, user should pay attention to this parater, sysclk is caculate as
 * SYSCLK = MCLK / MCLKDIV, MCLKDIV is bit0 of WM8904_CLK_RATES_0.
 * @param sampleRate Sample rate frequency in Hz.
 * @param bitWidth Audio data bit width.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetAudioFormat(wm8904_handle_t *handle, uint32_t sysclk, uint32_t sampleRate, uint32_t bitWidth);

/*!
 * @brief check and update the audio data format.
 * This api is used check the fsRatio setting based on the mclk and sample rate, if fsRatio setting
 * is not correct, it will correct it according to mclk and sample rate.
 * @param handle WM8904 handle structure.
 * @param format audio data format
 * @param mclkFreq mclk frequency
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_CheckAudioFormat(wm8904_handle_t *handle, wm8904_audio_format_t *format, uint32_t mclkFreq);

/*!
 * @brief Sets the module output volume.
 *
 * The parameter should be from 0 to 100.
 * The resulting volume will be.
 * 0 for mute, 100 for maximum volume value.
 *
 * @param handle WM8904 handle structure.
 * @param module wm8904 module name.
 * @param volume volume value.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetVolume(wm8904_handle_t *handle, uint16_t volumeLeft, uint16_t volumeRight);

/*!
 * @brief Sets the headphone output mute.
 *
 * @param handle WM8904 handle structure.
 * @param muteLeft true to mute left channel, false to unmute.
 * @param muteRight true to mute right channel, false to unmute.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetMute(wm8904_handle_t *handle, bool muteLeft, bool muteRight);

/*!
 * @brief Select LRC polarity.
 *
 * @param handle WM8904 handle structure.
 * @param polarity LRC clock polarity.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SelectLRCPolarity(wm8904_handle_t *handle, uint32_t polarity);

/*!
 * @brief Enable WM8904 DAC time slot.
 *
 * @param handle WM8904 handle structure.
 * @param timeslot timeslot number.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_EnableDACTDMMode(wm8904_handle_t *handle, wm8904_timeslot_t timeSlot);

/*!
 * @brief Enable WM8904 ADC time slot.
 *
 * @param handle WM8904 handle structure.
 * @param timeslot timeslot number.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_EnableADCTDMMode(wm8904_handle_t *handle, wm8904_timeslot_t timeSlot);

#if WM8904_DEBUG_REGISTER
/*!
 * @brief Reads content of all WM8904 registers and prints it to debug console.
 *
 * @param handle WM8904 handle structure.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_PrintRegisters(wm8904_handle_t *handle);
#endif

/*!
 * brief SET the module output power.
 *
 * param handle WM8904 handle structure.
 * param module wm8904 module.
 * param isEnabled, true is power on, false is power down.
 *
 * return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetModulePower(wm8904_handle_t *handle, wm8904_module_t module, bool isEnabled);

/*!
 * @brief Sets the channel output volume.
 *
 * The parameter should be from 0 to 100.
 * The resulting volume will be.
 * 0 for mute, 100 for maximum volume value.
 *
 * param handle codec handle structure.
 * @param channel codec channel.
 * @param volume volume value.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetChannelVolume(wm8904_handle_t *handle, uint32_t channel, uint32_t volume);

/*!
 * @brief SET the WM8904 record source.
 *
 * @param handle WM8904 handle structure.
 * @param recordSource record source , can be a value of kCODEC_ModuleRecordSourceDifferentialLine,
 * kCODEC_ModuleRecordSourceDifferentialMic, kCODEC_ModuleRecordSourceSingleEndMic, kCODEC_ModuleRecordSourceDigitalMic.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetRecord(wm8904_handle_t *handle, uint32_t recordSource);

/*!
 * @brief SET the WM8904 record source.
 *
 * @param handle WM8904 handle structure.
 * @param leftRecordChannel channel number of left record channel when using differential source, channel number of
 * single end left channel when using single end source, channel number of digital mic when using digital mic source.
 * @param rightRecordChannel channel number of right record channel when using differential source, channel number
 * of single end right channel when using single end source.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetRecordChannel(wm8904_handle_t *handle, uint32_t leftRecordChannel, uint32_t rightRecordChannel);

/*!
 * @brief SET the WM8904 play source.
 *
 * @param handle WM8904 handle structure.
 * @param playSource play source , can be a value of kCODEC_ModuleHeadphoneSourcePGA,
 * kCODEC_ModuleHeadphoneSourceDAC, kCODEC_ModuleLineoutSourcePGA, kCODEC_ModuleLineoutSourceDAC.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise..
 */
status_t WM8904_SetPlay(wm8904_handle_t *handle, uint32_t playSource);

/*!
 * @brief Sets the channel mute.
 *
 * @param handle codec handle structure.
 * @param module codec module name.
 * @param isMute true is mute, false unmute.
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise.
 */
status_t WM8904_SetChannelMute(wm8904_handle_t *handle, uint32_t channel, bool isMute);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_WM8904_H_ */
