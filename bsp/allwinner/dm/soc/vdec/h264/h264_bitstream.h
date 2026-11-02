/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VDEC_H264_BITSTREAM_H__
#define __VDEC_H264_BITSTREAM_H__

#include <stddef.h>
#include <stdint.h>

const uint8_t *h264_annexb_find_start_code(const uint8_t *data, const uint8_t *end);
int h264_annexb_nalu_type(const uint8_t *nalu, size_t length);

#endif /* __VDEC_H264_BITSTREAM_H__ */
