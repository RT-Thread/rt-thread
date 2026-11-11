/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __ROCKCHIP_RGA2_H__
#define __ROCKCHIP_RGA2_H__

#include <stdint.h>
#include <sys/ioctl.h>

#define RGA2_NAME                   "rga"
#define RGA2_BUFFER_MAX_SIZE        (64U * 1024U * 1024U)

enum rga2_render_mode
{
    RGA2_MODE_BITBLT = 0,
    RGA2_MODE_COLOR_FILL = 2,
};

enum rga2_format
{
    RGA2_FORMAT_RGBA8888,
    RGA2_FORMAT_BGRA8888,
    RGA2_FORMAT_RGBX8888,
    RGA2_FORMAT_BGRX8888,
    RGA2_FORMAT_RGB888,
    RGA2_FORMAT_BGR888,
    RGA2_FORMAT_RGB565,
    RGA2_FORMAT_BGR565,
};

enum rga2_rotate
{
    RGA2_ROTATE_0,
    RGA2_ROTATE_90,
    RGA2_ROTATE_180,
    RGA2_ROTATE_270,
};

#define RGA2_MIRROR_X               (1U << 0)
#define RGA2_MIRROR_Y               (1U << 1)

struct rga2_buffer
{
    uint32_t size;
    uint32_t reserved;
    uint64_t phys_addr;
    void *virt_addr;
};

struct rga2_rect
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
};

struct rga2_image
{
    uint64_t address;
    uint16_t width;
    uint16_t height;
    uint16_t stride;
    uint16_t format;
    struct rga2_rect rect;
};

struct rga2_req
{
    uint8_t render_mode;
    uint8_t rotate;
    uint8_t mirror;
    uint8_t reserved;
    uint32_t color;
    struct rga2_image src;
    struct rga2_image dst;
    uint32_t irq_status;
};

#define RGA2_IOC_MAGIC              'R'
#define RGA2_SUBMIT                 _IOWR(RGA2_IOC_MAGIC, 0, struct rga2_req)
#define RGA2_ALLOC_BUFFER           _IOWR(RGA2_IOC_MAGIC, 1, struct rga2_buffer)
#define RGA2_FREE_BUFFER            _IOW(RGA2_IOC_MAGIC, 2, struct rga2_buffer)
#define RGA2_GET_VERSION            _IOR(RGA2_IOC_MAGIC, 3, uint32_t)
#define RGA2_RESET                  _IO(RGA2_IOC_MAGIC, 4)

#endif /* __ROCKCHIP_RGA2_H__ */
