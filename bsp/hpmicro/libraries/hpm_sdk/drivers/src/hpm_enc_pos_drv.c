/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_enc_pos_drv.h"


float encoder_position_to_deg(uint32_t pos)
{
    double tmp;

    tmp = ((double)pos / (double)0xFFFFFFFF) * (double)360.0;

    return (float)tmp;
}

uint32_t encoder_deg_to_position(float deg)
{
    double tmp;

    while (deg < 0) {
        deg += 360;
    }
    while (deg > 360) {
        deg -= 360;
    }

    tmp = ((double)deg / (double)360.0) * (double)0xFFFFFFFF;

    return (uint32_t)tmp;
}

float encoder_position_to_rad(uint32_t pos)
{
    double tmp;
    const double _2pi = 6.283185307179586;

    tmp = ((double)pos / (double)0xFFFFFFFF) * _2pi;

    return (float)tmp;
}

uint32_t encoder_rad_to_position(float rad)
{
    double tmp;
    const double _2pi = 6.283185307179586;

    while (rad < 0) {
        rad += _2pi;
    }
    while (rad > _2pi) {
        rad -= _2pi;
    }

    tmp = ((double)rad / _2pi) * (double)0xFFFFFFFF;

    return (uint32_t)tmp;
}
