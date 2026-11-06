/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __VDEC_H264_SYNTAX_H__
#define __VDEC_H264_SYNTAX_H__

#include <stddef.h>
#include <stdint.h>

struct h264_sps
{
    uint16_t width;
    uint16_t height;
    uint16_t width_in_mbs;
    uint16_t height_in_map_units;
    uint8_t sps_id;
    uint8_t profile_idc;
    uint8_t level_idc;
    uint8_t chroma_format_idc;
    uint8_t frame_mbs_only;
    uint8_t mb_adaptive_frame_field;
    uint8_t direct_8x8_inference;
    uint8_t pic_order_cnt_type;
    uint8_t log2_max_frame_num;
    uint8_t log2_max_pic_order_cnt_lsb;
    uint8_t max_num_ref_frames;
    uint8_t delta_pic_order_always_zero;
};

int h264_sps_parse(const uint8_t *nalu, size_t length, struct h264_sps *sps);

struct h264_pps
{
    uint8_t pps_id;
    uint8_t sps_id;
    uint8_t entropy_coding_mode;
    uint8_t bottom_field_pic_order_in_frame;
    uint8_t weighted_pred;
    uint8_t weighted_bipred_idc;
    uint8_t redundant_pic_cnt_present;
    uint8_t deblocking_filter_control;
    uint8_t constrained_intra_pred;
    uint8_t transform_8x8_mode;
    uint8_t num_ref_idx_l0;
    uint8_t num_ref_idx_l1;
    int8_t pic_init_qp;
    int8_t chroma_qp_index_offset;
    int8_t second_chroma_qp_index_offset;
};

int h264_pps_parse(const uint8_t *nalu, size_t length, struct h264_pps *pps);

enum h264_slice_type
{
    H264_SLICE_P = 0,
    H264_SLICE_B = 1,
    H264_SLICE_I = 2,
    H264_SLICE_SP = 3,
    H264_SLICE_SI = 4,
};

struct h264_slice
{
    uint32_t first_mb_in_slice;
    uint32_t frame_num;
    uint32_t pic_order_cnt_lsb;
    int32_t delta_pic_order_bottom;
    int32_t delta_pic_order0;
    int32_t delta_pic_order1;
    uint8_t nal_ref_idc;
    uint8_t nal_unit_type;
    uint8_t slice_type;
    uint8_t pps_id;
    uint8_t field_pic;
    uint8_t bottom_field;
    uint8_t idr_pic;
    uint8_t direct_spatial_mv_pred;
    uint8_t num_ref_idx_active_override;
    uint8_t num_ref_idx_l0;
    uint8_t num_ref_idx_l1;
    uint8_t cabac_init_idc;
    uint8_t disable_deblocking_filter_idc;
    int8_t slice_qp_delta;
    int8_t slice_alpha_c0_offset_div2;
    int8_t slice_beta_offset_div2;
    uint32_t header_bits;
};

int h264_slice_parse(const uint8_t *nalu, size_t length, const struct h264_sps *sps,
                     const struct h264_pps *pps, struct h264_slice *slice);

#endif /* __VDEC_H264_SYNTAX_H__ */
