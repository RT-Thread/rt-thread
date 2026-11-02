/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __JPU_H__
#define __JPU_H__

#include <stdint.h>
#include <sys/ioctl.h>

#define JPU_NAME                    "jpu"
#define JPU_BUFFER_MAX_SIZE         (32U * 1024U * 1024U)
#define JPU_STREAM_PADDING          1024U

#define JPU_HUFF_TABLE_NUM          4
#define JPU_HUFF_BITS_NUM           16
#define JPU_HUFF_VALUES_NUM         162
#define JPU_QUANT_COMPONENT_NUM     3
#define JPU_QUANT_VALUES_NUM        64

enum jpu_format
{
    JPU_FORMAT_420 = 0,
    JPU_FORMAT_422,
    JPU_FORMAT_440,
    JPU_FORMAT_444,
    JPU_FORMAT_400,
};

struct jpu_dec_tables
{
    uint8_t huff_bits[JPU_HUFF_TABLE_NUM][JPU_HUFF_BITS_NUM];
    uint8_t huff_values[JPU_HUFF_TABLE_NUM][JPU_HUFF_VALUES_NUM];
    uint16_t quant[JPU_QUANT_COMPONENT_NUM][JPU_QUANT_VALUES_NUM];
};

struct jpu_buffer
{
    uint32_t size;
    uint64_t phys_addr;
    void *virt_addr;
};

/*
 * width, height and format are inputs. The remaining fields are returned by
 * JPU_QUERY_FRAME and describe the decoder's planar output buffer.
 */
struct jpu_frame_info
{
    uint16_t width;
    uint16_t height;
    uint8_t format;
    uint8_t reserved[3];

    uint16_t aligned_width;
    uint16_t aligned_height;
    uint16_t y_stride;
    uint16_t c_stride;
    uint16_t c_height;
    uint16_t reserved2;
    uint32_t size;
};

struct jpu_decode_request
{
    struct jpu_frame_info frame;
    struct jpu_dec_tables tables;

    uint64_t stream_phys;
    uint64_t frame_phys;
    uint32_t stream_size;
    uint32_t stream_capacity;
    uint32_t frame_capacity;
    uint32_t entropy_offset;
    uint16_t restart_interval;
    uint8_t components;
    uint8_t dc_selector[3];
    uint8_t ac_selector[3];

    uint32_t irq_status;
    uint32_t picture_status;
    uint32_t error_mcu;
    uint32_t cycles;
};

#define JPU_IOC_MAGIC               'J'

#define JPU_DECODE                  _IOWR(JPU_IOC_MAGIC, 0, struct jpu_decode_request)
#define JPU_QUERY_FRAME             _IOWR(JPU_IOC_MAGIC, 1, struct jpu_frame_info)
#define JPU_ALLOC_BUFFER            _IOWR(JPU_IOC_MAGIC, 2, struct jpu_buffer)
#define JPU_FREE_BUFFER             _IOW(JPU_IOC_MAGIC, 3, struct jpu_buffer)
#define JPU_RESET                   _IO(JPU_IOC_MAGIC, 5)
#define JPU_GET_MMU_VERSION         _IOR(JPU_IOC_MAGIC, 7, uint32_t)

#endif /* __JPU_H__ */
