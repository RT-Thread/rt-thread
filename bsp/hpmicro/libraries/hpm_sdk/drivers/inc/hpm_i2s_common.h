/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_I2S_COMMON_H
#define HPM_I2S_COMMON_H

/**
 * @brief I2S common driver APIs
 * @defgroup i2s_common_interface I2S common driver APIs
 * @ingroup io_interfaces
 * @{
 */

#define I2S_PROTOCOL_I2S_PHILIPS (0U)
#define I2S_PROTOCOL_MSB_JUSTIFIED (1U)
#define I2S_PROTOCOL_LEFT_JUSTIFIED (1U)
#define I2S_PROTOCOL_LSB_JUSTIFIED (2U)
#define I2S_PROTOCOL_RIGHT_JUSTIFIED (2U)
#define I2S_PROTOCOL_PCM (3U)

/* i2s channel slot mask */
#define I2S_CHANNEL_SLOT_MASK(x) (1U << (x))
/* convert audio depth value into CFGR[DATASIZ] value map */
#define I2S_CFGR_DATASIZ(x) ((x - 16) >> 3)
/* convert channel length value into CFGR[CHSIZ] value map */
#define I2S_CFGR_CHSIZ(x)   ((x - 16) >> 4)

/**
 * @brief I2S audio depth
 */
enum {
    i2s_audio_depth_16_bits = 16,
    i2s_audio_depth_24_bits = 24,
    i2s_audio_depth_32_bits = 32,
};

/**
 * @brief I2S channel length
 */
enum {
    i2s_channel_length_16_bits = 16,
    i2s_channel_length_32_bits = 32,
};

/**
 * @brief I2S stereo/mono channel
 */
enum {
    i2s_mono_left  = 0,
    i2s_mono_right = 1,
    i2s_stereo     = 2,
};

/**
 * @}
 */

#endif /* HPM_I2S_COMMON_H */
