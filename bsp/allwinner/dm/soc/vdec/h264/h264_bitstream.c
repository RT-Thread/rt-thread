/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "h264_bitstream.h"

/* Return the beginning of a three- or four-byte Annex-B start code. */
const uint8_t *h264_annexb_find_start_code(const uint8_t *data, const uint8_t *end)
{
    const uint8_t *position;

    for (position = data; position + 3 <= end; position++)
    {
        if (position[0] == 0 && position[1] == 0 && position[2] == 1)
        {
            return position > data && position[-1] == 0 ? position - 1 : position;
        }
    }

    return NULL;
}

int h264_annexb_nalu_type(const uint8_t *nalu, size_t length)
{
    size_t header_offset;

    if (length < 4 || nalu[0] != 0 || nalu[1] != 0)
    {
        return -1;
    }
    if (nalu[2] == 1)
    {
        header_offset = 3;
    }
    else if (length >= 5 && nalu[2] == 0 && nalu[3] == 1)
    {
        header_offset = 4;
    }
    else
    {
        return -1;
    }
    if (header_offset >= length || nalu[header_offset] & 0x80)
    {
        return -1;
    }

    return nalu[header_offset] & 0x1f;
}
