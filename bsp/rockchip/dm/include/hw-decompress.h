/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __HW_DECOMPRESS_H__
#define __HW_DECOMPRESS_H__

#include <sys/ioctl.h>

#define HW_DECOMPRESS_NAME  "hw_decom"

enum hw_decompress_mod
{
    HW_DECOMPRESS_LZ4_MOD,
    HW_DECOMPRESS_GZIP_MOD,
    HW_DECOMPRESS_ZLIB_MOD,
    HW_DECOMPRESS_MAX_MOD,
};

/* Input of RK_DECOM_USER */
struct hw_decompress_param
{
    uint32_t mode;
    uint32_t dst_max_size;
    uint64_t src;
    uint64_t dst;
    uint64_t decom_data_len;
};

#define HW_DECOMPRESS_IOC_MAGIC 'D'

#define HW_DECOMPRESS_REQ       _IOWR(HW_DECOMPRESS_IOC_MAGIC, 0, struct hw_decompress_param)

#endif /* __HW_DECOMPRESS_H__ */
