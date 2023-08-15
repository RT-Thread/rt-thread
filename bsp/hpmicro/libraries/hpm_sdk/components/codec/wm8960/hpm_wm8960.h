/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_SGTL5000_H_
#define _HPM_SGTL5000_H_

#include "hpm_i2c_drv.h"
#include "hpm_common.h"
#include "hpm_wm8960_regs.h"

#define WM8960_I2C_ADDR 0x1A

typedef enum wm8960_module {
    wm8960_module_adc            = 0, /* ADC module in WM8960 */
    wm8960_module_dac            = 1, /* DAC module in WM8960 */
    wm8960_module_vref           = 2, /* VREF module */
    wm8960_module_headphone      = 3, /* Headphone */
    wm8960_module_micbais        = 4, /* Mic bias */
    wm8960_module_ana_in         = 6, /* Analog in PGA  */
    wm8960_module_lineout        = 7, /* Line out module */
    wm8960_module_speaker        = 8, /* Speaker module */
    wm8960_module_output_mixer   = 9, /* Output mixer */
} wm8960_module_t;

/* wm8960 play source for output mixer */
typedef enum wm8960_play_source {
    wm8960_play_source_input_mixer   = 1, /* Input Boost Mixer to Output Mixer */
    wm8960_play_source_input3        = 2, /* L/RINPUT3 to Output Mixer */
    wm8960_play_source_dac           = 4, /* DAC to Output Mixer */
} wm8960_play_source_t;

/* WM8960 data route */
typedef enum wm8960_route {
    wm8960_route_bypass            = 0, /* ANA_IN->Headphone. */
    wm8960_route_playback          = 1, /*  I2SIN->DAC->Headphone. */
    wm8960_route_playback_and_record = 2, /* I2SIN->DAC->Headphone, ANA_IN->ADC->I2SOUT. */
    wm8960_route_record            = 5  /* ANA_IN->ADC->I2SOUT. */
} wm8960_route_t;

/* The audio data transfer protocol choice */
typedef enum wm8960_protocol {
    wm8960_bus_i2s             = 2,           /* I2S type */
    wm8960_bus_left_justified  = 1,           /* Left justified mode */
    wm8960_bus_right_justified = 0,           /* Right justified mode */
    wm8960_bus_pcma            = 3,           /* PCM A mode */
    wm8960_bus_pcmb            = 3 | (1 << 4) /* PCM B mode */
} wm8960_protocol_t;

/* wm8960 input source */
typedef enum wm8960_input {
    wm8960_input_closed                  = 0, /* Input device is closed */
    wm8960_input_single_ended_mic        = 1, /* Input as single ended mic, only use L/RINPUT1 */
    wm8960_input_differential_mic_input2 = 2, /* Input as differential mic, use L/RINPUT1 and L/RINPUT2 */
    wm8960_input_differential_mic_input3 = 3, /* Input as differential mic, use L/RINPUT1 and L/RINPUT3*/
    wm8960_input_line_input2             = 4, /* Input as line input, only use L/RINPUT2 */
    wm8960_input_line_input3             = 5  /* Input as line input, only use L/RINPUT3 */
} wm8960_input_t;

/* wm8960 audio format */
typedef struct wm8960_audio_format {
    uint32_t mclk_hz;     /* master clock frequency */
    uint32_t sample_rate; /* sample rate */
    uint32_t bit_width;   /* bit width */
} wm8960_audio_format_t;

/* configure structure of WM8960 */
typedef struct wm8960_config {
    wm8960_route_t route;                      /* Audio data route.*/
    wm8960_protocol_t bus;                     /* Audio transfer protocol */
    bool enable_speaker;                       /* True means enable class D speaker as output, false means no */
    wm8960_input_t left_input;                 /* Left input source for WM8960 */
    wm8960_input_t right_input;                /* Right input source for wm8960 */
    wm8960_play_source_t play_source;          /* play source */
    wm8960_audio_format_t format;              /* Audio format */
} wm8960_config_t;

typedef struct {
    I2C_Type *ptr;;                    /* I2C bus */
    uint8_t slave_address;             /* code device address */
} wm8960_control_t;


#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief WM8960 initialize function.
 *
 * @param control WM8960 control structure.
 * @param config WM8960 configuration structure.
 */
hpm_stat_t wm8960_init(wm8960_control_t *control, wm8960_config_t *config);

/**
 * @brief Deinit the WM8960 codec.
 *
 * This function close all modules in WM8960 to save power.
 *
 * @param control WM8960 control structure pointer.
 */
hpm_stat_t wm8960_deinit(wm8960_control_t *control);

/**
 * @brief Set audio data route in WM8960.
 *
 * This function would set the data route according to route.
 *
 * @param control WM8960 control structure.
 * @param config Audio configure structure in WM8960.
 */
hpm_stat_t wm8960_set_data_route(wm8960_control_t *control, wm8960_config_t *config);

/**
 * @brief Set left audio input source in WM8960.
 *
 * @param control WM8960 control structure.
 * @param input Audio input source.
 */
hpm_stat_t wm8960_set_left_input(wm8960_control_t *control, wm8960_input_t input);

/**
 * @brief Set right audio input source in WM8960.
 *
 * @param control WM8960 control structure.
 * @param input Audio input source.
 */
hpm_stat_t wm8960_set_right_input(wm8960_control_t *control, wm8960_input_t input);

/**
 * @brief Set the audio transfer protocol.
 *
 * @param control WM8960 control structure.
 * @param protocol Audio data transfer protocol.
 */
hpm_stat_t wm8960_set_protocol(wm8960_control_t *control, wm8960_protocol_t protocol);

/**
 * @brief Set the volume of different modules in WM8960.
 *
 * This function would set the volume of WM8960 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 *
 * Module:wm8960_module_adc, volume range value: 0 is mute, 1-255 is -97db to 30db
 * Module:wm8960_module_dac, volume range value: 0 is mute, 1-255 is -127db to 0db
 * Module:wm8960_module_headphone, volume range value: 0 - 2F is mute, 0x30 - 0x7F is -73db to 6db
 * Module:wm8960_module_ana_in, volume range value: 0 - 0x3F is -17.25db to 30db
 * Module:wm8960_module_speaker, volume range value: 0 - 2F is mute, 0x30 - 0x7F is -73db to 6db
 *
 *
 * @param control WM8960 control structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @param volume Volume value need to be set.
 */
hpm_stat_t wm8960_set_volume(wm8960_control_t *control, wm8960_module_t module, uint32_t volume);

/**
 * @brief Enable/disable expected module.
 *
 * @param control WM8960 control structure.
 * @param module Module expected to enable.
 * @param enable Enable or disable moudles.
 */
hpm_stat_t wm8960_set_module(wm8960_control_t *control, wm8960_module_t module, bool enable);

/**
 * @brief SET the WM8960 play source.
 *
 * @param control WM8960 control structure.
 * @param play_source play source
 *
 * @return kStatus_WM8904_Success if successful, different code otherwise..
 */
hpm_stat_t wm8960_config_input_to_output_mixer(wm8960_control_t *control, uint32_t play_source);

/**
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 *
 * @param control WM8960 control structure pointer.
 * @param sysclk system clock of the codec which can be generated by MCLK or PLL output.
 * @param sample_rate Sample rate of audio file running in WM8960. WM8960 now
 * supports 8k, 11.025k, 12k, 16k, 22.05k, 24k, 32k, 44.1k, 48k and 96k sample rate.
 * @param bits Bit depth of audio file (WM8960 only supports 16bit, 20bit, 24bit
 * and 32 bit in HW).
 */
hpm_stat_t wm8960_set_data_format(wm8960_control_t *control, uint32_t sysclk, uint32_t sample_rate, uint32_t bits);


/**
 * @brief Write register to WM8960 using I2C.
 *
 * @param control WM8960 control structure.
 * @param reg The register address in WM8960.
 * @param val Value needs to write into the register.
 */
hpm_stat_t wm8960_write_reg(wm8960_control_t *control, uint8_t reg, uint16_t val);

/**
 * @brief Read register from WM8960 using I2C.
 * @param reg The register address in WM8960.
 * @param val Value written to.
 */
hpm_stat_t wm8960_read_reg(uint8_t reg, uint16_t *val);

/**
 * @brief Modify some bits in the register using I2C.
 * @param control WM8960 control structure.
 * @param reg The register address in WM8960.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
hpm_stat_t wm8960_modify_reg(wm8960_control_t *control, uint8_t reg, uint16_t mask, uint16_t val);


#endif /* _HPM_SGTL5000_H_ */
