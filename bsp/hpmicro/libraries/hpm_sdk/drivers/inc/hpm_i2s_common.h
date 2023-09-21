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
