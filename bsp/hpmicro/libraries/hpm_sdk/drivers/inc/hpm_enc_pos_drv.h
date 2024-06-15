/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_ENC_POS_COMMON_H
#define HPM_ENC_POS_COMMON_H

#include "hpm_common.h"

/**
 *
 * @brief enc pos driver APIs
 * @defgroup enc_pos_interface Encode Position driver APIs
 * @ingroup io_interface
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief caculate degree of angle from pos
 *
 * @param[in] pos position value
 * @return degree of angle.
 */
float encoder_position_to_deg(uint32_t pos);

/**
 * @brief caculate posistion from degree of angle
 *
 * @param[in] deg degree of angle
 * @return position value.
 */
uint32_t encoder_deg_to_position(float deg);

/**
 * @brief caculate radian of angle from pos
 *
 * @param[in] pos position value
 * @return radian of angle.
 */
float encoder_position_to_rad(uint32_t pos);

/**
 * @brief caculate posistion from radian of angle
 *
 * @param[in] rad radian of angle
 * @return position value.
 */
uint32_t encoder_rad_to_position(float rad);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* HPM_ENC_POS_COMMON_H */
