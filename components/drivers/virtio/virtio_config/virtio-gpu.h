/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 * 2023-02-25     GuEe-GUI     using virtio dm
 */

#ifndef __VIRTIO_GPU_H__
#define __VIRTIO_GPU_H__

#include <drivers/core/dm.h>

#define VIRTIO_GPU_F_VIRGL               0 /* VIRTIO_GPU_CMD_CTX_*, VIRTIO_GPU_CMD_*_3D */
#define VIRTIO_GPU_F_EDID                1 /* VIRTIO_GPU_CMD_GET_EDID */
#define VIRTIO_GPU_F_RESOURCE_UUID       2 /* VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID */
#define VIRTIO_GPU_F_RESOURCE_BLOB       3 /* VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB */
#define VIRTIO_GPU_F_CONTEXT_INIT        4 /* VIRTIO_GPU_CMD_CREATE_CONTEXT with context_init and multiple timelines */

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

enum virtio_gpu_shm_id
{
    VIRTIO_GPU_SHM_ID_UNDEFINED = 0,
    /*
     * VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB
     * VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB
     */
    VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1
};

#define VIRTIO_GPU_FLAG_FENCE         (1 << 0)
/*
 * If the following flag is set, then ring_idx contains the index
 * of the command ring that needs to used when creating the fence
 */
#define VIRTIO_GPU_FLAG_INFO_RING_IDX (1 << 1)

struct virtio_gpu_ctrl_hdr
{
    /*
     * specifies the type of the driver request (VIRTIO_GPU_CMD_*) or
     * device response (VIRTIO_GPU_RESP_*).
     */
    rt_le32_t type;
    /*
     * request / response flags.
     */
    rt_le32_t flags;
    /*
     * If the driver sets the VIRTIO_GPU_FLAG_FENCE bit
     * in the request flags field the device MUST:
     *  set VIRTIO_GPU_FLAG_FENCE bit in the response,
     *  copy the content of the fence_id field from the request to the response,
     *  and send the response only after command processing is complete.
     */
    rt_le64_t fence_id;
    /*
     * Rendering context (used in 3D mode only).
     */
    rt_le32_t ctx_id;
    /*
     * If VIRTIO_GPU_F_CONTEXT_INIT is supported,
     * then the driver MAY set VIRTIO_GPU_FLAG_INFO_RING_IDX bit
     * in the request flags. In that case:
     *  ring_idx indicates the value of a context-specific ring index.
     *      The minimum value is 0 and maximum value is 63 (inclusive).
     *  If VIRTIO_GPU_FLAG_FENCE is set, fence_id acts as a sequence number
     *      on the synchronization timeline defined by ctx_idx and the ring index.
     *  If VIRTIO_GPU_FLAG_FENCE is set and when the command associated
     *      with fence_id is complete, the device MUST send a response for
     *      all outstanding commands with a sequence number less than or
     *      equal to fence_id on the same synchronization timeline.
     */
    rt_uint8_t ring_idx;
    rt_uint8_t padding[3];
};

/* data passed in the cursor vq */

struct virtio_gpu_cursor_pos
{
    rt_le32_t scanout_id;
    rt_le32_t x;
    rt_le32_t y;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_UPDATE_CURSOR, VIRTIO_GPU_CMD_MOVE_CURSOR */
struct virtio_gpu_update_cursor
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_cursor_pos pos;   /* update & move */
    rt_le32_t resource_id;              /* update only */
    rt_le32_t hot_x;                    /* update only */
    rt_le32_t hot_y;                    /* update only */
    rt_le32_t padding;
};

/* data passed in the control vq, 2d related */

struct virtio_gpu_rect
{
    rt_le32_t x;
    rt_le32_t y;
    rt_le32_t width;
    rt_le32_t height;
};

/* VIRTIO_GPU_CMD_RESOURCE_UNREF */
struct virtio_gpu_resource_unref
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_2D: create a 2d resource with a format */
struct virtio_gpu_resource_create_2d
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t format;
    rt_le32_t width;
    rt_le32_t height;
};

/* VIRTIO_GPU_CMD_SET_SCANOUT */
struct virtio_gpu_set_scanout
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_le32_t scanout_id;
    rt_le32_t resource_id;
};

/* VIRTIO_GPU_CMD_RESOURCE_FLUSH */
struct virtio_gpu_resource_flush
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D: simple transfer to_host */
struct virtio_gpu_transfer_to_host_2d
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_le64_t offset;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

struct virtio_gpu_mem_entry
{
    rt_le64_t addr;
    rt_le32_t length;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING */
struct virtio_gpu_resource_attach_backing
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t nr_entries;
};

/* VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING */
struct virtio_gpu_resource_detach_backing
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

/* VIRTIO_GPU_RESP_OK_DISPLAY_INFO */
#define VIRTIO_GPU_MAX_SCANOUTS 16
struct virtio_gpu_resp_display_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_display_one
    {
        struct virtio_gpu_rect r;
        rt_le32_t enabled;
        rt_le32_t flags;
    } pmodes[VIRTIO_GPU_MAX_SCANOUTS];
};

/* data passed in the control vq, 3d related */

struct virtio_gpu_box
{
    rt_le32_t x, y, z;
    rt_le32_t w, h, d;
};

/* VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D, VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D */
struct virtio_gpu_transfer_host_3d
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_box box;
    rt_le64_t offset;
    rt_le32_t resource_id;
    rt_le32_t level;
    rt_le32_t stride;
    rt_le32_t layer_stride;
};

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_3D */
#define VIRTIO_GPU_RESOURCE_FLAG_Y_0_TOP (1 << 0)
struct virtio_gpu_resource_create_3d
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t target;
    rt_le32_t format;
    rt_le32_t bind;
    rt_le32_t width;
    rt_le32_t height;
    rt_le32_t depth;
    rt_le32_t array_size;
    rt_le32_t last_level;
    rt_le32_t nr_samples;
    rt_le32_t flags;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_CTX_CREATE */
#define VIRTIO_GPU_CONTEXT_INIT_CAPSET_ID_MASK 0x000000ff
struct virtio_gpu_ctx_create
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t nlen;
    rt_le32_t context_init;
    char debug_name[64];
};

/* VIRTIO_GPU_CMD_CTX_DESTROY */
struct virtio_gpu_ctx_destroy
{
    struct virtio_gpu_ctrl_hdr hdr;
};

/* VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE, VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE */
struct virtio_gpu_ctx_resource
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_SUBMIT_3D */
struct virtio_gpu_cmd_submit
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t size;
    rt_le32_t padding;
};

#define VIRTIO_GPU_CAPSET_VIRGL         1
#define VIRTIO_GPU_CAPSET_VIRGL2        2
#define VIRTIO_GPU_CAPSET_GFXSTREAM     3
#define VIRTIO_GPU_CAPSET_VENUS         4
#define VIRTIO_GPU_CAPSET_CROSS_DOMAIN  5

/* VIRTIO_GPU_CMD_GET_CAPSET_INFO */
struct virtio_gpu_get_capset_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t capset_index;
    rt_le32_t padding;
};

/* VIRTIO_GPU_RESP_OK_CAPSET_INFO */
struct virtio_gpu_resp_capset_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t capset_id;
    rt_le32_t capset_max_version;
    rt_le32_t capset_max_size;
    rt_le32_t padding;
};

/* VIRTIO_GPU_CMD_GET_CAPSET */
struct virtio_gpu_get_capset
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t capset_id;
    rt_le32_t capset_version;
};

/* VIRTIO_GPU_RESP_OK_CAPSET */
struct virtio_gpu_resp_capset
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint8_t capset_data[];
};

/* VIRTIO_GPU_CMD_GET_EDID */
struct virtio_gpu_cmd_get_edid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t scanout;
    rt_le32_t padding;
};

/* VIRTIO_GPU_RESP_OK_EDID */
struct virtio_gpu_resp_edid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t size;
    rt_le32_t padding;
    rt_uint8_t edid[1024];
};

#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

struct virtio_gpu_config
{
    /*
     * signals pending events to the driver.
     * The driver MUST NOT write to this field.
     */
    rt_le32_t events_read;
    /*
     * clears pending events in the device.
     * Writing a '1' into a bit will clear the corresponding bit in events_read,
     * mimicking write-to-clear behavior.
     */
    rt_le32_t events_clear;
    /*
     * specifies the maximum number of scanouts supported by the device.
     * Minimum value is 1, maximum value is 16.
     */
    rt_le32_t num_scanouts;
    /*
     * specifies the maximum number of capability sets supported by the device.
     * The minimum value is zero.
     */
    rt_le32_t num_capsets;
};

/* simple formats for fbcon/X use */
enum virtio_gpu_formats
{
    VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM  = 1,
    VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM  = 2,
    VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM  = 3,
    VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM  = 4,

    VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM  = 67,
    VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM  = 68,

    VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM  = 121,
    VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM  = 134,
};

/* VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID */
struct virtio_gpu_resource_assign_uuid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

/* VIRTIO_GPU_RESP_OK_RESOURCE_UUID */
struct virtio_gpu_resp_resource_uuid
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint8_t uuid[16];
};

/* VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB */
struct virtio_gpu_resource_create_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
#define VIRTIO_GPU_BLOB_MEM_GUEST             0x0001
#define VIRTIO_GPU_BLOB_MEM_HOST3D            0x0002
#define VIRTIO_GPU_BLOB_MEM_HOST3D_GUEST      0x0003

#define VIRTIO_GPU_BLOB_FLAG_USE_MAPPABLE     0x0001
#define VIRTIO_GPU_BLOB_FLAG_USE_SHAREABLE    0x0002
#define VIRTIO_GPU_BLOB_FLAG_USE_CROSS_DEVICE 0x0004
    /* zero is invalid blob mem */
    rt_le32_t blob_mem;
    rt_le32_t blob_flags;
    rt_le32_t nr_entries;
    rt_le64_t blob_id;
    rt_le64_t size;
    /*
     * sizeof(nr_entries * virtio_gpu_mem_entry) bytes follow
     */
};

/* VIRTIO_GPU_CMD_SET_SCANOUT_BLOB */
struct virtio_gpu_set_scanout_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    struct virtio_gpu_rect r;
    rt_le32_t scanout_id;
    rt_le32_t resource_id;
    rt_le32_t width;
    rt_le32_t height;
    rt_le32_t format;
    rt_le32_t padding;
    rt_le32_t strides[4];
    rt_le32_t offsets[4];
};

/* VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB */
struct virtio_gpu_resource_map_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t padding;
    rt_le64_t offset;
};

/* VIRTIO_GPU_RESP_OK_MAP_INFO */
#define VIRTIO_GPU_MAP_CACHE_MASK     0x0f
#define VIRTIO_GPU_MAP_CACHE_NONE     0x00
#define VIRTIO_GPU_MAP_CACHE_CACHED   0x01
#define VIRTIO_GPU_MAP_CACHE_UNCACHED 0x02
#define VIRTIO_GPU_MAP_CACHE_WC       0x03
struct virtio_gpu_resp_map_info
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_uint32_t map_info;
    rt_uint32_t padding;
};

/* VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB */
struct virtio_gpu_resource_unmap_blob
{
    struct virtio_gpu_ctrl_hdr hdr;
    rt_le32_t resource_id;
    rt_le32_t padding;
};

#endif /* __VIRTIO_GPU_H__ */
