/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_W8978_H_
#define _HPM_W8978_H_

#include "hpm_i2c_drv.h"
#include "hpm_wm8978_regs.h"

typedef enum wm8978_audio_interface {
    wm8978_right_justified = 0,  /* Right Justified */
    wm8978_left_justified,       /* Left Justified */
    wm8978_philips_i2s,          /* I2S format */
    wm8978_pcm_mode,             /* DSP/PCM mode */
} wm8978_audio_interface_t;

typedef enum wm8978_word_length {
    wm8978_16bits_length        = 0,  /* 16bits */
    wm8978_20bits_length,           /* 20bits */
    wm8978_24bits_length,           /* 24bits */
    wm8978_32bits_length,           /* 32bits */
} wm8978_word_length_t;

typedef enum wm8978_out_channel {
    wm8978_out1_channel         = 0,  /* R/LOUT1 channel. */
    wm8978_out2_channel         = 1, /*  R/LOUT2 channel. */
} wm8978_out_channel_t;

typedef enum input_channel_flag {
    input_off                  = 0x00,    /* no input */
    mic_left_on                = 0x01,    /* LIN,LIP pin，MIC left input */
    mic_right_on               = 0x02,    /* RIN,RIP pin，MIC right input */
    line_on                    = 0x04,    /* L2,R2 pin input */
    aux_on                     = 0x08,    /* AUXL,AUXR pins input */
    dac_on                     = 0x10,    /* dac for i2s */
    adc_on                     = 0x20     /* input fed into the WM8978 internal ADC */
} input_channel_flags_t;

/* WM8978 音频输出通道控制选项, 可以选择多路 */
typedef enum output_channel_flag {
    output_off                 = 0x00,    /* no output */
    earphone_left_on           = 0x01,    /* LOUT1 earphone */
    earphone_right_on          = 0x02,    /* ROUT1 earphone */
    spk_on                     = 0x04,    /* LOUT2 and ROUT2 Inverting output mono*/
    out_3_4_on                 = 0x08,    /* OUT3 and OUT4 output mono audio*/
} output_channel_flag_t;

typedef struct {
    I2C_Type *ptr;                      /* I2C bus */
    uint8_t device_address;             /* code device address */
} wm8978_context_t;

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief WM8979 initialize function.
 *
 * @param [in] control WM8979 control structure.
 * @retval hpm_stat_t status_success if init without any error
 */
hpm_stat_t wm8979_init(wm8978_context_t *control);

/**
 * @brief WM8979 set out volume function.
 *
 * @param [in] control WM8979 control structure.
 * @param [in] channel out channel
 * @param [in] volume volume value
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_set_out_volume(wm8978_context_t *control, wm8978_out_channel_t channel, uint8_t volume);

/**
 * @brief WM8979 read out volume function.
 *
 * @param [in] control WM8979 control structure.
 * @param [in] channel out channel
 * @param [out] volume volume points value
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_get_out_volume(wm8978_context_t *control, wm8978_out_channel_t channel, uint8_t *volume);

/**
 * @brief WM8979 set out mute.
 *
 * @param [in] control WM8979 control structure.
 * @param [in] channel out channel
 * @param [in] mute if mute is set to true
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_set_out_mute(wm8978_context_t *control, wm8978_out_channel_t channel, bool mute);

/**
 * @brief WM8979 set gain of mic.
 *
 * @param [in] control WM8979 control structure.
 * @param [in] gain gain value, range: 0 ~ 63
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_set_mic_gain(wm8978_context_t *control, uint8_t gain);

/**
 * @brief WM8979 set the gain of the Line input channel
 *
 * @param [in] control WM8979 control structure.
 * @param [in] gain volume value, range: 0 ~ 7
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_set_line_gain(wm8978_context_t *control, uint8_t gain);

/**
 * @brief WM8979 enter power down mode
 *
 * @param [in] control WM8979 control structure.
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_power_down(wm8978_context_t *control);

/**
 * @brief Control the GPIO1 pin of WM8978 to output high or low
 *
 * @param [in] control WM8979 control structure.
 * @param [in] value output high or low. if true, it's high
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_ctrl_gpio1(wm8978_context_t *control, bool value);

/**
 * @brief Configuring the audio interface of WM8978
 *
 * @param [in] control WM8979 control structure.
 * @param [in] standard wm8978_audio_interface_t structure
 * @param [in] word_len wm8978_word_length_t structure
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_cfg_audio_interface(wm8978_context_t *control,
                                        wm8978_audio_interface_t standard,
                                        wm8978_word_length_t word_len);

/**
 * @brief Configure wm8978 audio channel
 *
 * @param [in] control WM8979 control structure.
 * @param [in] in_flags input_channel_flags_t structure
 * @param [in] out_flags output_channel_flag_t structure
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_cfg_audio_channel(wm8978_context_t *control,
                                    input_channel_flags_t in_flags,
                                    output_channel_flag_t out_flags);

/**
 * @brief setting the Notch Filter for WM8978
 *
 * @note used to suppress positive feedback of microphone sound waves to avoid howling
 * @param [in] control WM8979 control structure.
 * @param [in] nfa0 Notch Filter0 value
 * @param [in] nfa1 Notch Filter1 value
 * @retval hpm_stat_t status_success if set without any error
 */
hpm_stat_t wm8978_notch_filter(wm8978_context_t *control, uint16_t nfa0, uint16_t nfa1);

/**
 * @brief Write register to WM8978 using I2C.
 *
 * @param [in] control WM8978 control structure.
 * @retval hpm_stat_t status_success if reset without any error
 */
hpm_stat_t wm8978_reset(wm8978_context_t *control);

/**
 * @brief Write register to WM8978 using I2C.
 *
 * @param [in] control WM8978 control structure.
 * @param [in] reg The register address in WM8978.
 * @param [in] val Value needs to write into the register.
 * @retval hpm_stat_t status_success if write reg without any error
 */
hpm_stat_t wm8978_write_reg(wm8978_context_t *control, uint8_t reg, uint16_t val);

/**
 * @brief Read register from WM8978 using I2C.
 * @param [in] reg The register address in WM8978.
 * @param [in] reg The register address in WM8978.
 * @param [out] val Value point read to.
 * @retval hpm_stat_t status_success if read reg without any error
 */
hpm_stat_t wm8978_read_reg(wm8978_context_t *control, uint8_t reg, uint16_t *val);

/**
 * @brief Modify some bits in the register using I2C.
 * @param [in] control WM8978 control structure.
 * @param [in] reg The register address in WM8978.
 * @param [in] mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param [in] val Value needs to write into the register.
 * @retval hpm_stat_t status_success if modify reg without any error
 */
hpm_stat_t wm8978_modify_reg(wm8978_context_t *control, uint8_t reg, uint16_t mask, uint16_t val);

#ifdef __cplusplus
}
#endif

/**
 * @}
 *
 */

#endif /* HPM_WM8978_H */