/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_DEF_H_
#define _FAL_DEF_H_

#include <stdint.h>
#include <stdio.h>
#include <rtthread.h>

#define FAL_PRINTF      rt_kprintf
#define FAL_MALLOC      rt_malloc
#define FAL_CALLOC      rt_calloc
#define FAL_REALLOC     rt_realloc
#define FAL_FREE        rt_free

#ifndef FAL_DEBUG
#define FAL_DEBUG                      0
#endif

#if FAL_DEBUG
#ifdef assert
#undef assert
#endif
#define assert(x) RT_ASSERT(x)
#endif

/* FAL flash and partition device name max length */
#ifndef FAL_DEV_NAME_MAX
#define FAL_DEV_NAME_MAX 24
#endif

#ifndef FAL_DEV_BLK_MAX
#define FAL_DEV_BLK_MAX 6
#endif

struct flash_blk
{
    size_t size;
    size_t count;
};

struct fal_flash_dev
{
    char name[FAL_DEV_NAME_MAX];

    /* flash device start address and len  */
    uint32_t addr;
    size_t len;
    /* the block size in the flash for erase minimum granularity */
    size_t blk_size;

    struct
    {
        int (*init)(void);
        int (*read)(long offset, uint8_t *buf, size_t size);
        int (*write)(long offset, const uint8_t *buf, size_t size);
        int (*erase)(long offset, size_t size);
    } ops;

    /* write minimum granularity, unit: bit.
       1(nor flash)/ 8(stm32f2/f4)/ 32(stm32f1)/ 64(stm32l4)
       0 will not take effect. */
    size_t write_gran;
    struct flash_blk blocks[FAL_DEV_BLK_MAX];
};
typedef struct fal_flash_dev *fal_flash_dev_t;

/**
 * FAL partition
 */
struct fal_partition
{
    uint32_t magic_word;

    /* partition name */
    char name[FAL_DEV_NAME_MAX];
    /* flash device name for partition */
    char flash_name[FAL_DEV_NAME_MAX];

    /* partition offset address on flash device */
    long offset;
    size_t len;

    uint32_t reserved;
};
typedef struct fal_partition *fal_partition_t;

#endif /* _FAL_DEF_H_ */
