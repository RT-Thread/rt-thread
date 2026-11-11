/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#ifndef __VIRTIO_GPU_H__
#define __VIRTIO_GPU_H__

#include <rtdef.h>

#include <virtio.h>

#define VIRTIO_GPU_QUEUE_CTRL       0
#define VIRTIO_GPU_QUEUE_CURSOR     1
#define VIRTIO_GPU_QUEUE_SIZE       32

#define VIRTIO_GPU_F_VIRGL          0   /* VIRTIO_GPU_CMD_CTX_*, VIRTIO_GPU_CMD_*_3D */
#define VIRTIO_GPU_F_EDID           1   /* VIRTIO_GPU_CMD_GET_EDID */
#define VIRTIO_GPU_F_RESOURCE_UUID  2   /* VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID */
#define VIRTIO_GPU_F_RESOURCE_BLOB  3   /* VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB */
#define VIRTIO_GPU_F_CONTEXT_INIT   4   /* VIRTIO_GPU_CMD_CREATE_CONTEXT with context_init and multiple timelines */

#define VIRTIO_GPU_EVENT_DISPLAY    (1 << 0)

#define VIRTIO_GPU_FORMAT_BPP       32
#define VIRTIO_GPU_FORMAT_PIXEL     4
#define VIRTIO_GPU_CURSOR_WIDTH     64
#define VIRTIO_GPU_CURSOR_HEIGHT    64
#define VIRTIO_GPU_CURSOR_IMG_SIZE  (VIRTIO_GPU_CURSOR_WIDTH * VIRTIO_GPU_CURSOR_HEIGHT * VIRTIO_GPU_FORMAT_PIXEL)
#define VIRTIO_GPU_INVALID_PMODE_ID RT_UINT32_MAX

/* GPU control */

struct virtio_gpu_config
{
    rt_uint32_t events_read;
    rt_uint32_t events_clear;
    rt_uint32_t num_scanouts;   /* 1 ~ 16 */
    rt_uint32_t reserved;
};

enum virtio_gpu_ctrl_type
{
    VIRTIO_GPU_UNDEFINED = 0,

    /* 2d commands */
    VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
    VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
    VIRTIO_GPU_CMD_RESOURCE_UNREF,
    VIRTIO_GPU_CMD_SET_SCANOUT,
    VIRTIO_GPU_CMD_RESOURCE_FLUSH,
    VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
    VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
    VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
    VIRTIO_GPU_CMD_GET_CAPSET_INFO,
    VIRTIO_GPU_CMD_GET_CAPSET,
    VIRTIO_GPU_CMD_GET_EDID,
    VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID,
    VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB,
    VIRTIO_GPU_CMD_SET_SCANOUT_BLOB,

    /* 3d commands */
    VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
    VIRTIO_GPU_CMD_CTX_DESTROY,
    VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
    VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
    VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
    VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
    VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
    VIRTIO_GPU_CMD_SUBMIT_3D,
    VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB,
    VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB,

    /* cursor commands */
    VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
    VIRTIO_GPU_CMD_MOVE_CURSOR,

    /* success responses */
    VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
    VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
    VIRTIO_GPU_RESP_OK_CAPSET_INFO,
    VIRTIO_GPU_RESP_OK_CAPSET,
    VIRTIO_GPU_RESP_OK_EDID,
    VIRTIO_GPU_RESP_OK_RESOURCE_UUID,
    VIRTIO_GPU_RESP_OK_MAP_INFO,

    /* error responses */
    VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
    VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
    VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
    VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
    VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
    VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,
};

#define VIRTIO_GPU_FLAG_FENCE (1 << 0)

struct virtio_gpu_ctrl_hdr
{
    rt_uint32_t type;
    rt_uint32_t flags;
    rt_uint64_t fence_id;
    rt_uint32_t ctx_id;
    rt_uint8_t ring_idx;
    rt_uint8_t padding[3];
};

#define VIRTIO_GPU_MAX_SCANOUTS 16

struct virtio_gpu_rect
{
    rt_uint32_t x;
    rt_uint32_t y;
    rt_uint32_t width;
    rt_uint32_t height;
};

struct virtio_gpu_resp_display_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_display_one
    {
        struct virtio_gpu_rect r;
        rt_uint32_t enabled;
        rt_uint32_t flags;
    } pmodes[VIRTIO_GPU_MAX_SCANOUTS];
};

struct virtio_gpu_get_edid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t scanout;
    rt_uint32_t padding;
};

struct virtio_gpu_resp_edid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t size;
    rt_uint32_t padding;
    rt_uint8_t edid[1024];
};

enum virtio_gpu_formats
{
    VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM = 1,
    VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM = 2,
    VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM = 3,
    VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM = 4,

    VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM = 67,
    VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM = 68,

    VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM = 121,
    VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM = 134,
};

struct virtio_gpu_resource_create_2d
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t format;
    rt_uint32_t width;
    rt_uint32_t height;
};

struct virtio_gpu_resource_unref
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
};

struct virtio_gpu_set_scanout
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_uint32_t scanout_id;
    rt_uint32_t resource_id;
};

struct virtio_gpu_resource_flush
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
};

struct virtio_gpu_transfer_to_host_2d
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_uint64_t offset;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
};

struct virtio_gpu_resource_attach_backing
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t nr_entries;
};

struct virtio_gpu_mem_entry
{
    rt_uint64_t addr;
    rt_uint32_t length;
    rt_uint32_t padding;
};

struct virtio_gpu_resource_detach_backing
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
};

struct virtio_gpu_get_capset_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t capset_index;
    rt_uint32_t padding;
};

#define VIRTIO_GPU_CAPSET_VIRGL         1
#define VIRTIO_GPU_CAPSET_VIRGL2        2
#define VIRTIO_GPU_CAPSET_GFXSTREAM     3
#define VIRTIO_GPU_CAPSET_VENUS         4
#define VIRTIO_GPU_CAPSET_CROSS_DOMAIN  5

struct virtio_gpu_resp_capset_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t capset_id;
    rt_uint32_t capset_max_version;
    rt_uint32_t capset_max_size;
    rt_uint32_t padding;
};

struct virtio_gpu_get_capset
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t capset_id;
    rt_uint32_t capset_version;
};

struct virtio_gpu_resp_capset
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint8_t capset_data[];
};

struct virtio_gpu_resource_assign_uuid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
};

struct virtio_gpu_resp_resource_uuid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint8_t uuid[16];
};

#define VIRTIO_GPU_BLOB_MEM_GUEST             0x0001
#define VIRTIO_GPU_BLOB_MEM_HOST3D            0x0002
#define VIRTIO_GPU_BLOB_MEM_HOST3D_GUEST      0x0003

#define VIRTIO_GPU_BLOB_FLAG_USE_MAPPABLE     0x0001
#define VIRTIO_GPU_BLOB_FLAG_USE_SHAREABLE    0x0002
#define VIRTIO_GPU_BLOB_FLAG_USE_CROSS_DEVICE 0x0004

struct virtio_gpu_resource_create_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t blob_mem;
    rt_uint32_t blob_flags;
    rt_uint32_t nr_entries;
    rt_uint64_t blob_id;
    rt_uint64_t size;
};

struct virtio_gpu_set_scanout_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_uint32_t scanout_id;
    rt_uint32_t resource_id;
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t format;
    rt_uint32_t padding;
    rt_uint32_t strides[4];
    rt_uint32_t offsets[4];
};

#define VIRTIO_GPU_CONTEXT_INIT_CAPSET_ID_MASK 0x000000ff
struct virtio_gpu_ctx_create
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t nlen;
    rt_uint32_t context_init;
    char debug_name[64];
};

struct virtio_gpu_resource_map_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
    rt_uint64_t offset;
};

#define VIRTIO_GPU_MAP_CACHE_MASK      0x0f
#define VIRTIO_GPU_MAP_CACHE_NONE      0x00
#define VIRTIO_GPU_MAP_CACHE_CACHED    0x01
#define VIRTIO_GPU_MAP_CACHE_UNCACHED  0x02
#define VIRTIO_GPU_MAP_CACHE_WC        0x03

struct virtio_gpu_resp_map_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t map_info;
    rt_uint32_t padding;
};

struct virtio_gpu_resource_unmap_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t resource_id;
    rt_uint32_t padding;
};

/* GPU cursor */

struct virtio_gpu_cursor_pos
{
    rt_uint32_t scanout_id;
    rt_uint32_t x;
    rt_uint32_t y;
    rt_uint32_t padding;
};

struct virtio_gpu_update_cursor
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_cursor_pos pos;
    rt_uint32_t resource_id;
    rt_uint32_t hot_x;
    rt_uint32_t hot_y;
    rt_uint32_t padding;
};

struct virtio_gpu_device
{
    struct rt_device parent;

    struct virtio_device virtio_dev;

    /* Current display's info */
    struct virtio_gpu_display_one pmode;
    enum virtio_gpu_formats format;
    rt_uint32_t pmode_id;
    rt_uint32_t cursor_x, cursor_y;
    rt_uint32_t display_resource_id;
    rt_uint32_t cursor_resource_id;
    rt_uint32_t next_resource_id;

    /* Display framebuffer */
    struct rt_mutex rw_mutex;
    void *framebuffer;
    rt_uint32_t smem_len;

    /* Cursor image info */
    rt_bool_t cursor_enable;
    struct rt_mutex ops_mutex;
    rt_uint8_t cursor_img[VIRTIO_GPU_CURSOR_IMG_SIZE];

    /* GPU request info */
    struct virtio_gpu_resp_display_info gpu_request;

    struct
    {
        rt_bool_t ctrl_valid;
        rt_bool_t cursor_valid;

        struct virtio_gpu_update_cursor cursor_cmd;
    } info[VIRTIO_GPU_QUEUE_SIZE];
};

rt_err_t rt_virtio_gpu_init(rt_ubase_t *mmio_base, rt_uint32_t irq);

enum
{
    VIRTIO_DEVICE_CTRL_GPU_SET_PRIMARY      = 0x20,
    VIRTIO_DEVICE_CTRL_GPU_CREATE_2D,

    VIRTIO_DEVICE_CTRL_CURSOR_SETUP,
    VIRTIO_DEVICE_CTRL_CURSOR_SET_IMG,
    VIRTIO_DEVICE_CTRL_CURSOR_MOVE,
};

#endif /* __VIRTIO_GPU_H__ */
