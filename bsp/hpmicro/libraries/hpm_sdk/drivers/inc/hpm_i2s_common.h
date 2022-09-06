/*
 * Copyright (c) 2021 hpmicro
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

#define I2S_AUDIO_DEPTH_16_BITS (0U)
#define I2S_AUDIO_DEPTH_24_BITS (1U)
#define I2S_AUDIO_DEPTH_32_BITS (2U)
#define I2S_AUDIO_DEPTH_IS_NOT_VALID(x) ((x) > I2S_AUDIO_DEPTH_32_BITS)

#define I2S_CHANNEL_LENGTH_16_BITS (0U)
#define I2S_CHANNEL_LENGTH_32_BITS (1U)

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
