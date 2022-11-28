/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#ifndef __SUNXI_METADATA_H__
#define __SUNXI_METADATA_H__

enum {
    /* hdr static metadata is available */
    SUNXI_METADATA_FLAG_HDR_SATIC_METADATA   = 0x00000001,
    /* hdr dynamic metadata is available */
    SUNXI_METADATA_FLAG_HDR_DYNAMIC_METADATA = 0x00000002,

    /* afbc header data is available */
    SUNXI_METADATA_FLAG_AFBC_HEADER          = 0x00000010,
};

struct afbc_header {
    u32 signature;
    u16 filehdr_size;
    u16 version;
    u32 body_size;
    u8 ncomponents;
    u8 header_layout;
    u8 yuv_transform;
    u8 block_split;
    u8 inputbits[4];
    u16 block_width;
    u16 block_height;
    u16 width;
    u16 height;
    u8  left_crop;
    u8  top_crop;
    u16 block_layout;
};

struct display_master_data {
    /* display primaries */
    u16 display_primaries_x[3];
    u16 display_primaries_y[3];

    /* white_point */
    u16 white_point_x;
    u16 white_point_y;

    /* max/min display mastering luminance */
    u32 max_display_mastering_luminance;
    u32 min_display_mastering_luminance;
};

/* static metadata type 1 */
struct hdr_static_metadata {
    struct display_master_data disp_master;

    u16 maximum_content_light_level;
    u16 maximum_frame_average_light_level;
};

/* sunxi video metadata for ve and de */
struct sunxi_metadata {
    struct hdr_static_metadata hdr_smetada;
    struct afbc_header afbc_head;
};

#endif /* #ifndef __SUNXI_METADATA_H__ */
