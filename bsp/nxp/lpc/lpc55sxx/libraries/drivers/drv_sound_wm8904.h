/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     Vandoul      the first version
 */

#ifndef __DRV_SOUND_WM8904_H__
#define __DRV_SOUND_WM8904_H__

#include <rtthread.h>

typedef enum
{
    WM8904_RESET                    = 0x00,
    WM8904_ANALOG_ADC_0             = 0x0A,
    WM8904_POWER_MGMT_0             = 0x0C,
    WM8904_POWER_MGMT_2             = 0x0E,
    WM8904_POWER_MGMT_3             = 0x0F,
    WM8904_POWER_MGMT_6             = 0x12,
    WM8904_CLK_RATES_0              = 0x14,
    WM8904_CLK_RATES_1              = 0x15,
    WM8904_CLK_RATES_2              = 0x16,
    WM8904_AUDIO_IF_0               = 0x18,
    WM8904_AUDIO_IF_1               = 0x19,
    WM8904_AUDIO_IF_2               = 0x1A,
    WM8904_AUDIO_IF_3               = 0x1B,
    WM8904_DAC_DIG_1                = 0x21,
    WM8904_DAC_DIG_0                = 0x27,
    WM8904_ANALOG_LEFT_IN_0         = 0x2C,
    WM8904_ANALOG_RIGHT_IN_0        = 0x2D,
    WM8904_ANALOG_LEFT_IN_1         = 0x2E,
    WM8904_ANALOG_RIGHT_IN_1        = 0x2F,
    WM8904_ANALOG_OUT1_LEFT         = 0x39,
    WM8904_ANALOG_OUT1_RIGHT        = 0x3A,
    WM8904_ANALOG_OUT12_ZC          = 0x3D,
    WM8904_DC_SERVO_0               = 0x43,
    WM8904_ANALOG_HP_0              = 0x5A,
    WM8904_CHRG_PUMP_0              = 0x62,
    WM8904_CLS_W_0                  = 0x68,
    WM8904_WRT_SEQUENCER_0          = 0x6C,
    WM8904_WRT_SEQUENCER_3          = 0x6F,
    WM8904_WRT_SEQUENCER_4          = 0x70,
    WM8904_DAC_DIGITAL_VOLUME_LEFT  = 0x1E,
    WM8904_DAC_DIGITAL_VOLUME_RIGHT = 0x1F,
    WM8904_ADC_DIGITAL_VOLUME_LEFT  = 0x24,
    WM8904_ADC_DIGITAL_VOLUME_RIGHT = 0x25,
    WM8904_ANALOG_OUT2_LEFT         = 0x3B,
    WM8904_ANALOG_OUT2_RIGHT        = 0x3C,
    /* FLL control register */
    WM8904_FLL_CONTROL_1            = 0x74,
    WM8904_FLL_CONTROL_2            = 0x75,
    WM8904_FLL_CONTROL_3            = 0x76,
    WM8904_FLL_CONTROL_4            = 0x77,
    WM8904_FLL_CONTROL_5            = 0x78,
    /* GPIO control register */
    WM8904_GPIO_CONTROL_1           = 0x79,
    WM8904_GPIO_CONTROL_2           = 0x7A,
    WM8904_GPIO_CONTROL_3           = 0x7B,
    WM8904_GPIO_CONTROL_4           = 0x7C,
    /* FLL nco */
    WM89004_FLL_NCO_TEST_0          = 0xF7,
    WM89004_FLL_NCO_TEST_1          = 0xF8,
}wm8904_reg_t;

#define WM8904_LRC_POLARITY_POS         (4U)
#define WM8904_LRC_POLARITY_NOOMAL      (0)
#define WM8904_LRC_POLARITY_INVERTED    (1U << WM8904_LRC_POLARITY_POS)

typedef enum _wm8904_module
{
    WM8904_MODULE_ADC = 0, /*!< module ADC */
    WM8904_MODULE_DAC, /*!< module DAC */
    WM8904_MODULE_PGA, /*!< module PGA */
    WM8904_MODULE_HEADPHONE, /*!< module headphone */
    WM8904_MODULE_LINEOUT, /*!< module line out */
}wm8904_module_t;

enum
{
    WM8904_HEADPHONE_LEFT = 1U,
    WM8904_HEADPHONE_RIGHT = 2U,
    WM8904_LINEOUT_LEFT = 4U,
    WM8904_LINEOUT_RIGHT = 8U,
};

typedef enum _wm8904_timeslot{
    WM8904_TIMESLOT_0 = 0U,
    WM8904_TIMESLOT_1,
}wm8904_timeslot_t;

typedef enum
{
    WM8904_PROTOCOL_RIGHT_JUSTIFIED     = 0x00,
    WM8904_PROTOCOL_LEFT_JUSTIFIED      = 0x01,
    WM8904_PROTOCOL_I2S                 = 0x02,
    WM8904_PROTOCOL_PCMA                = 0x03,
    WM8904_PROTOCOL_PCMB                = 0x13,
}wm8904_protocol_t;

/*! @brief The SYSCLK / fs ratio. */
typedef enum _wm8904_fs_ratio
{
    WM8904_FSRATIO_64X   = 0x0, /*!< SYSCLK is   64 * sample rate * frame width */
    WM8904_FSRATIO_128X  = 0x1, /*!< SYSCLK is  128 * sample rate * frame width */
    WM8904_FSRATIO_192X  = 0x2, /*!< SYSCLK is  192 * sample rate * frame width */
    WM8904_FSRATIO_256X  = 0x3, /*!< SYSCLK is  256 * sample rate * frame width */
    WM8904_FSRATIO_384X  = 0x4, /*!< SYSCLK is  384 * sample rate * frame width */
    WM8904_FSRATIO_512X  = 0x5, /*!< SYSCLK is  512 * sample rate * frame width */
    WM8904_FSRATIO_768X  = 0x6, /*!< SYSCLK is  768 * sample rate * frame width */
    WM8904_FSRATIO_1024X = 0x7, /*!< SYSCLK is 1024 * sample rate * frame width */
    WM8904_FSRATIO_1408X = 0x8, /*!< SYSCLK is 1408 * sample rate * frame width */
    WM8904_FSRATIO_1536X = 0x9  /*!< SYSCLK is 1536 * sample rate * frame width */
} wm8904_fs_ratio_t;

/*! @brief Sample rate. */
typedef enum _wm8904_sample_rate
{
    WM8904_SAMPLERATE_8kHz    = 0x0, /*!< 8 kHz */
    WM8904_SAMPLERATE_12kHz   = 0x1, /*!< 12kHz */
    WM8904_SAMPLERATE_16kHz   = 0x2, /*!< 16kHz */
    WM8904_SAMPLERATE_24kHz   = 0x3, /*!< 24kHz */
    WM8904_SAMPLERATE_32kHz   = 0x4, /*!< 32kHz */
    WM8904_SAMPLERATE_48kHz   = 0x5, /*!< 48kHz */
    WM8904_SAMPLERATE_11025Hz = 0x6, /*!< 11.025kHz */
    WM8904_SAMPLERATE_22050Hz = 0x7, /*!< 22.05kHz */
    WM8904_SAMPLERATE_44100Hz = 0x8  /*!< 44.1kHz */
} wm8904_sample_rate_t;

/*! @brief Bit width. */
typedef enum _wm8904_bit_width
{
    WM8904_BITWIDTH_16 = 0x0, /*!< 16 bits */
    WM8904_BITWIDTH_20 = 0x1, /*!< 20 bits */
    WM8904_BITWIDTH_24 = 0x2, /*!< 24 bits */
    WM8904_BITWIDTH_32 = 0x3  /*!< 32 bits */
} wm8904_bit_width_t;

enum
{
    WM8904_RECORD_SOURCE_DIFFERENTIAL_LINE = 1U, /*!< record source from differential line */
    WM8904_RECORD_SOURCE_LINE_INPUT = 2U, /*!< record source from line input */
    WM8904_RECORD_SOURCE_DIFFERENTIAL_MIC = 4U, /*!< record source from differential mic */
    WM8904_RECORD_SOURCE_DIGITAL_MIC = 8U, /*!< record source from digital microphone */
};

enum
{
    WM8904_RECORD_CHANNEL_LEFT1 = 1U, /*!< left record channel 1 */
    WM8904_RECORD_CHANNEL_LEFT2 = 2U, /*!< left record channel 2 */
    WM8904_RECORD_CHANNEL_LEFT3 = 4U, /*!< left record channel 3 */
    WM8904_RECORD_CHANNEL_RIGHT1 = 1U, /*!< right record channel 1 */
    WM8904_RECORD_CHANNEL_RIGHT2 = 2U, /*!< right record channel 2 */
    WM8904_RECORD_CHANNEL_RIGHT3 = 4U, /*!< right record channel 3 */
    WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE1 = 1U, /*!< differential positive record channel 1 */
    WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE2 = 2U, /*!< differential positive record channel 2 */
    WM8904_RECORD_CHANNEL_DIFFERENTIAL_POSITIVE3 = 4U, /*!< differential positive record channel 3 */
    WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE1 = 8U, /*!< differential negative record channel 1 */
    WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE2 = 16U, /*!< differential negative record channel 2 */
    WM8904_RECORD_CHANNEL_DIFFERENTIAL_NEGATIVE3 = 32U, /*!< differential negative record channel 3 */
};

/*! @brief wm8904 play source
 *
 */
enum
{
    WM8904_PLAY_SOURCE_PGA = 1U, /*!< play source PGA, bypass ADC */
    WM8904_PLAY_SOURCE_DAC = 4U, /*!< play source Input3 */
};

/*! @brief wm8904_fll_clk_source */
typedef enum _wm8904_fll_clk_source
{
    WM8904_FLL_CLK_SOURCE_MCLK = 0U, /**< wm8904 FLL clock source from MCLK */
}wm8904_fll_clk_source_t;

/*! @brief wm8904 fll configuration */
typedef struct _wm8904_fll_config
{
    wm8904_fll_clk_source_t source; /*!< fll reference clock source */
    rt_uint32_t ref_clock_hz; /*!< fll reference clock frequency */
    rt_uint32_t output_clock_hz; /*!< fll output clock frequency */
}wm8904_fll_config_t;

/*! @brief Audio format configuration. */
typedef struct _wm8904_audio_format
{
    wm8904_fs_ratio_t fsRatio;       /*!< SYSCLK / fs ratio */
    wm8904_sample_rate_t sampleRate; /*!< Sample rate */
    wm8904_bit_width_t bitWidth;     /*!< Bit width */
} wm8904_audio_format_t;

struct wm8904_config
{
    const char *i2c_bus_name;
    const char *i2s_bus_name;
    int i2c_addr;
    wm8904_protocol_t protocol;
    wm8904_audio_format_t format;
};

#define WM8904_I2C_ADDRESS          (0x1A)
#define WM8904_I2C_BITRATE          (400000U)

/* WM8904 maximum volume */
#define WM8904_MAP_HEADPHONE_LINEOUT_MAX_VOLUME     0x3FU
#define WM8904_DAC_MAX_VOLUME                       0xC0U

#endif

