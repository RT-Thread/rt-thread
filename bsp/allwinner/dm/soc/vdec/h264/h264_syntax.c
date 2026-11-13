/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <rtthread.h>

#include "h264_bitstream.h"
#include "h264_syntax.h"

struct h264_bit_reader
{
    const uint8_t *data;
    size_t length;
    size_t bit_offset;
};

static int h264_read_bits(struct h264_bit_reader *reader, unsigned int count, uint32_t *value)
{
    uint32_t result = 0;

    if (!reader || !value || count > 32 || reader->bit_offset > reader->length * 8 ||
        count > reader->length * 8 - reader->bit_offset)
    {
        return -EINVAL;
    }
    while (count--)
    {
        result = (result << 1) |
                 ((reader->data[reader->bit_offset >> 3] >>
                   (7 - (reader->bit_offset & 7))) & 1);
        reader->bit_offset++;
    }
    *value = result;
    return 0;
}

static int h264_read_ue(struct h264_bit_reader *reader, uint32_t *value)
{
    unsigned int leading_zeroes = 0;
    uint32_t suffix;
    uint32_t bit;

    do
    {
        if (h264_read_bits(reader, 1, &bit))
        {
            return -EINVAL;
        }
        if (++leading_zeroes > 31)
        {
            return -EINVAL;
        }
    } while (bit == 0);

    leading_zeroes--;
    if (!leading_zeroes)
    {
        *value = 0;
        return 0;
    }
    if (h264_read_bits(reader, leading_zeroes, &suffix))
    {
        return -EINVAL;
    }
    *value = ((uint32_t)1 << leading_zeroes) - 1 + suffix;
    return 0;
}

static int h264_read_se(struct h264_bit_reader *reader, int32_t *value)
{
    uint32_t code_num;

    if (h264_read_ue(reader, &code_num))
    {
        return -EINVAL;
    }
    *value = code_num & 1 ? (int32_t)((code_num + 1) >> 1) :
             -(int32_t)(code_num >> 1);
    return 0;
}

static int h264_skip_scaling_list(struct h264_bit_reader *reader, unsigned int size)
{
    int32_t delta_scale;
    int last_scale = 8;
    int next_scale = 8;
    unsigned int index;

    for (index = 0; index < size; index++)
    {
        if (next_scale != 0)
        {
            if (h264_read_se(reader, &delta_scale))
            {
                return -EINVAL;
            }
            next_scale = (last_scale + delta_scale + 256) & 0xff;
        }
        last_scale = next_scale == 0 ? last_scale : next_scale;
    }
    return 0;
}

static rt_bool_t h264_more_rbsp_data(const struct h264_bit_reader *reader)
{
    size_t bit;

    if (reader->bit_offset >= reader->length * 8)
    {
        return RT_FALSE;
    }
    for (bit = reader->bit_offset; bit < reader->length * 8; bit++)
    {
        uint8_t value = (reader->data[bit >> 3] >> (7 - (bit & 7))) & 1;

        if (bit == reader->bit_offset)
        {
            if (!value)
            {
                return RT_TRUE;
            }
        }
        else if (value)
        {
            return RT_TRUE;
        }
    }
    return RT_FALSE;
}

static rt_bool_t h264_high_profile(uint32_t profile_idc)
{
    switch (profile_idc)
    {
    case 44:
    case 83:
    case 86:
    case 100:
    case 110:
    case 118:
    case 122:
    case 128:
    case 134:
    case 135:
    case 138:
    case 139:
    case 244:
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static int h264_make_rbsp(const uint8_t *nalu, size_t length, int nalu_type,
                          uint8_t **rbsp, size_t *rbsp_length)
{
    size_t header_offset;
    size_t input;
    size_t output = 0;
    unsigned int zeroes = 0;
    uint8_t *data;

    if (h264_annexb_nalu_type(nalu, length) != nalu_type)
    {
        return -EINVAL;
    }
    header_offset = nalu[2] == 1 ? 4 : 5;
    if (header_offset >= length)
    {
        return -EINVAL;
    }
    data = rt_malloc(length - header_offset);
    if (!data)
    {
        return -ENOMEM;
    }
    for (input = header_offset; input < length; input++)
    {
        if (zeroes == 2 && nalu[input] == 3)
        {
            zeroes = 0;
            continue;
        }
        data[output++] = nalu[input];
        zeroes = nalu[input] == 0 ? zeroes + 1 : 0;
    }
    if (!output)
    {
        rt_free(data);
        return -EINVAL;
    }
    *rbsp = data;
    *rbsp_length = output;
    return 0;
}

static int h264_nalu_header(const uint8_t *nalu, size_t length, uint8_t *header)
{
    size_t offset;

    if (!nalu || !header || length < 4 ||
        (nalu[0] != 0 || nalu[1] != 0) ||
        (nalu[2] != 1 && (length < 5 || nalu[2] != 0 || nalu[3] != 1)))
    {
        return -EINVAL;
    }
    offset = nalu[2] == 1 ? 3 : 4;
    if (offset >= length)
    {
        return -EINVAL;
    }
    *header = nalu[offset];
    if (*header & 0x80)
    {
        return -EINVAL;
    }
    return 0;
}

int h264_sps_parse(const uint8_t *nalu, size_t length, struct h264_sps *sps)
{
    struct h264_bit_reader reader;
    uint8_t *rbsp;
    size_t rbsp_length;
    uint32_t profile_idc;
    uint32_t chroma_format_idc = 1;
    uint32_t value;
    uint32_t pic_order_cnt_type;
    uint32_t sps_id;
    uint32_t frame_mbs_only;
    uint32_t crop_left;
    uint32_t crop_right;
    uint32_t crop_top;
    uint32_t crop_bottom;
    uint32_t width;
    uint32_t height;
    uint32_t log2_max_frame_num_minus4;
    uint32_t max_num_ref_frames;
    uint32_t mb_adaptive_frame_field;
    uint32_t direct_8x8_inference;
    unsigned int index;
    int result;

    if (!nalu || !sps || length < 5)
    {
        return -EINVAL;
    }
    rt_memset(sps, 0, sizeof(*sps));
    result = h264_make_rbsp(nalu, length, 7, &rbsp, &rbsp_length);
    if (result)
    {
        return result;
    }
    reader.data = rbsp;
    reader.length = rbsp_length;
    reader.bit_offset = 0;

    result = h264_read_bits(&reader, 8, &profile_idc) ||
             h264_read_bits(&reader, 8, &value) ||
             h264_read_bits(&reader, 8, &value) ||
             h264_read_ue(&reader, &sps_id);
    if (result)
    {
        goto out;
    }
    if (h264_high_profile(profile_idc))
    {
        result = h264_read_ue(&reader, &chroma_format_idc);
        if (result || chroma_format_idc > 3)
        {
            result = -EINVAL;
            goto out;
        }
        if (chroma_format_idc == 3 && h264_read_bits(&reader, 1, &value))
        {
            result = -EINVAL;
            goto out;
        }
        result = h264_read_ue(&reader, &value) || h264_read_ue(&reader, &value) ||
                 h264_read_bits(&reader, 1, &value) || h264_read_bits(&reader, 1, &value);
        if (result)
        {
            goto out;
        }
        if (value)
        {
            for (index = 0; index < (chroma_format_idc == 3 ? 12 : 8); index++)
            {
                if (h264_read_bits(&reader, 1, &value) ||
                    (value && h264_skip_scaling_list(&reader, index < 6 ? 16 : 64)))
                {
                    result = -EINVAL;
                    goto out;
                }
            }
        }
    }
    result = h264_read_ue(&reader, &log2_max_frame_num_minus4) ||
             h264_read_ue(&reader, &pic_order_cnt_type);
    if (result)
    {
        goto out;
    }
    if (pic_order_cnt_type == 0)
    {
        result = h264_read_ue(&reader, &value);
        if (!result && value > 12)
        {
            result = -ENOTSUP;
            goto out;
        }
        sps->log2_max_pic_order_cnt_lsb = value + 4;
    }
    else if (pic_order_cnt_type == 1)
    {
        int32_t signed_value;

        result = h264_read_bits(&reader, 1, &value);
        sps->delta_pic_order_always_zero = value;
        result = result || h264_read_se(&reader, &signed_value) ||
                 h264_read_se(&reader, &signed_value) || h264_read_ue(&reader, &value);
        for (index = 0; !result && index < value; index++)
        {
            result = h264_read_se(&reader, &signed_value);
        }
    }
    if (result || sps_id > UINT8_MAX || pic_order_cnt_type > 2 ||
        log2_max_frame_num_minus4 > 12 || h264_read_ue(&reader, &max_num_ref_frames) ||
        max_num_ref_frames > 16 || h264_read_bits(&reader, 1, &value) ||
        h264_read_ue(&reader, &width) ||
        h264_read_ue(&reader, &height) || h264_read_bits(&reader, 1, &frame_mbs_only))
    {
        result = -EINVAL;
        goto out;
    }
    mb_adaptive_frame_field = 0;
    if (!frame_mbs_only && h264_read_bits(&reader, 1, &mb_adaptive_frame_field))
    {
        result = -EINVAL;
        goto out;
    }
    result = h264_read_bits(&reader, 1, &direct_8x8_inference) ||
             h264_read_bits(&reader, 1, &value);
    if (result)
    {
        goto out;
    }
    crop_left = crop_right = crop_top = crop_bottom = 0;
    if (value)
    {
        result = h264_read_ue(&reader, &crop_left) || h264_read_ue(&reader, &crop_right) ||
                 h264_read_ue(&reader, &crop_top) || h264_read_ue(&reader, &crop_bottom);
        if (result)
        {
            goto out;
        }
    }
    width = (width + 1) * 16;
    height = (height + 1) * 16 * (2 - frame_mbs_only);
    if (chroma_format_idc == 1)
    {
        crop_left *= 2;
        crop_right *= 2;
        crop_top *= 2 * (2 - frame_mbs_only);
        crop_bottom *= 2 * (2 - frame_mbs_only);
    }
    else if (chroma_format_idc == 2)
    {
        crop_left *= 2;
        crop_right *= 2;
        crop_top *= 2 - frame_mbs_only;
        crop_bottom *= 2 - frame_mbs_only;
    }
    else
    {
        crop_top *= 2 - frame_mbs_only;
        crop_bottom *= 2 - frame_mbs_only;
    }
    if (crop_left + crop_right >= width || crop_top + crop_bottom >= height ||
        width - crop_left - crop_right > UINT16_MAX ||
        height - crop_top - crop_bottom > UINT16_MAX)
    {
        result = -EINVAL;
        goto out;
    }
    sps->width = width - crop_left - crop_right;
    sps->height = height - crop_top - crop_bottom;
    sps->width_in_mbs = (width + 15) / 16;
    sps->height_in_map_units = (height + (16 * (2 - frame_mbs_only) - 1)) /
                               (16 * (2 - frame_mbs_only));
    sps->sps_id = sps_id;
    sps->profile_idc = profile_idc;
    sps->level_idc = rbsp[2];
    sps->chroma_format_idc = chroma_format_idc;
    sps->frame_mbs_only = frame_mbs_only;
    sps->mb_adaptive_frame_field = mb_adaptive_frame_field;
    sps->direct_8x8_inference = direct_8x8_inference;
    sps->pic_order_cnt_type = pic_order_cnt_type;
    sps->log2_max_frame_num = log2_max_frame_num_minus4 + 4;
    sps->max_num_ref_frames = max_num_ref_frames;
    result = 0;
out:
    rt_free(rbsp);
    return result;
}

int h264_pps_parse(const uint8_t *nalu, size_t length, struct h264_pps *pps)
{
    struct h264_bit_reader reader;
    uint8_t *rbsp;
    size_t rbsp_length;
    uint32_t pps_id;
    uint32_t sps_id;
    uint32_t value;
    int32_t signed_value;
    int result;

    if (!nalu || !pps || length < 5)
    {
        return -EINVAL;
    }
    rt_memset(pps, 0, sizeof(*pps));
    result = h264_make_rbsp(nalu, length, 8, &rbsp, &rbsp_length);
    if (result)
    {
        return result;
    }
    reader.data = rbsp;
    reader.length = rbsp_length;
    reader.bit_offset = 0;

    result = h264_read_ue(&reader, &pps_id) || h264_read_ue(&reader, &sps_id) ||
             h264_read_bits(&reader, 1, &value);
    if (result || pps_id > UINT8_MAX || sps_id > UINT8_MAX)
    {
        result = -EINVAL;
        goto out;
    }
    pps->entropy_coding_mode = value;
    result = h264_read_bits(&reader, 1, &value);
    pps->bottom_field_pic_order_in_frame = value;
    result = result || h264_read_ue(&reader, &value);
    if (result || value != 0)
    {
        result = -ENOTSUP;
        goto out;
    }
    result = h264_read_ue(&reader, &value);
    if (result || value > UINT8_MAX - 1)
    {
        result = -EINVAL;
        goto out;
    }
    pps->num_ref_idx_l0 = value + 1;
    result = h264_read_ue(&reader, &value);
    if (result || value > UINT8_MAX - 1)
    {
        result = -EINVAL;
        goto out;
    }
    pps->num_ref_idx_l1 = value + 1;
    result = h264_read_bits(&reader, 1, &value);
    pps->weighted_pred = value;
    result = result || h264_read_bits(&reader, 2, &value);
    pps->weighted_bipred_idc = value;
    result = result || h264_read_se(&reader, &signed_value);
    if (result || signed_value < INT8_MIN || signed_value > INT8_MAX)
    {
        result = -EINVAL;
        goto out;
    }
    pps->pic_init_qp = signed_value;
    result = h264_read_se(&reader, &signed_value);
    result = result || h264_read_se(&reader, &signed_value);
    if (result || signed_value < INT8_MIN || signed_value > INT8_MAX)
    {
        result = -EINVAL;
        goto out;
    }
    pps->chroma_qp_index_offset = signed_value;
    pps->second_chroma_qp_index_offset = signed_value;
    result = h264_read_bits(&reader, 1, &value);
    if (result)
    {
        goto out;
    }
    pps->deblocking_filter_control = value;
    result = h264_read_bits(&reader, 1, &value);
    pps->constrained_intra_pred = value;
    result = result || h264_read_bits(&reader, 1, &value);
    pps->redundant_pic_cnt_present = value;
    if (h264_more_rbsp_data(&reader))
    {
        result = h264_read_bits(&reader, 1, &value);
        pps->transform_8x8_mode = value;
        if (result)
        {
            goto out;
        }
        result = h264_read_bits(&reader, 1, &value);
        if (result || value)
        {
            result = result ? result : -ENOTSUP;
            goto out;
        }
        result = h264_read_se(&reader, &signed_value);
        if (result || signed_value < INT8_MIN || signed_value > INT8_MAX)
        {
            result = result ? result : -EINVAL;
            goto out;
        }
        pps->second_chroma_qp_index_offset = signed_value;
    }
    if (result)
    {
        goto out;
    }
    pps->pps_id = pps_id;
    pps->sps_id = sps_id;
    result = 0;
out:
    rt_free(rbsp);
    return result;
}

static int h264_slice_check_ref_list_modification(struct h264_bit_reader *reader,
                                                  uint8_t slice_type)
{
    uint32_t value;

    if (slice_type != H264_SLICE_I && slice_type != H264_SLICE_SI)
    {
        if (h264_read_bits(reader, 1, &value))
        {
            return -EINVAL;
        }
        if (value)
        {
            return -ENOTSUP;
        }
    }
    if (slice_type == H264_SLICE_B)
    {
        if (h264_read_bits(reader, 1, &value))
        {
            return -EINVAL;
        }
        if (value)
        {
            return -ENOTSUP;
        }
    }
    return 0;
}

static int h264_slice_check_ref_marking(struct h264_bit_reader *reader, uint8_t idr_pic)
{
    uint32_t value;

    if (idr_pic)
    {
        return h264_read_bits(reader, 1, &value) || h264_read_bits(reader, 1, &value);
    }
    if (h264_read_bits(reader, 1, &value))
    {
        return -EINVAL;
    }
    return value ? -ENOTSUP : 0;
}

int h264_slice_parse(const uint8_t *nalu, size_t length, const struct h264_sps *sps,
                     const struct h264_pps *pps, struct h264_slice *slice)
{
    struct h264_bit_reader reader;
    uint8_t *rbsp;
    uint8_t nal_header;
    size_t rbsp_length;
    uint32_t value;
    uint32_t slice_type;
    int32_t signed_value;
    int result;

    if (!nalu || !sps || !pps || !slice || length < 5)
    {
        return -EINVAL;
    }
    result = h264_nalu_header(nalu, length, &nal_header);
    if (result)
    {
        return result;
    }
    if ((nal_header & 0x1f) != 1 && (nal_header & 0x1f) != 5)
    {
        return -EINVAL;
    }
    result = h264_make_rbsp(nalu, length, nal_header & 0x1f, &rbsp, &rbsp_length);
    if (result)
    {
        return result;
    }

    rt_memset(slice, 0, sizeof(*slice));
    reader.data = rbsp;
    reader.length = rbsp_length;
    reader.bit_offset = 0;
    result = h264_read_ue(&reader, &slice->first_mb_in_slice) ||
             h264_read_ue(&reader, &slice_type) || h264_read_ue(&reader, &value);
    if (result || slice_type > 9 || value != pps->pps_id)
    {
        result = result ? result : -ENOTSUP;
        goto out;
    }
    slice->slice_type = slice_type % 5;
    slice->pps_id = value;
    slice->nal_ref_idc = nal_header >> 5;
    slice->nal_unit_type = nal_header & 0x1f;
    slice->idr_pic = slice->nal_unit_type == 5;
    result = h264_read_bits(&reader, sps->log2_max_frame_num, &slice->frame_num);
    if (result)
    {
        goto out;
    }
    if (!sps->frame_mbs_only)
    {
        result = h264_read_bits(&reader, 1, &value);
        if (result || value)
        {
            result = result ? result : -ENOTSUP;
            goto out;
        }
    }
    if (slice->idr_pic && h264_read_ue(&reader, &value))
    {
        result = -EINVAL;
        goto out;
    }
    if (sps->pic_order_cnt_type == 0)
    {
        result = h264_read_bits(&reader, sps->log2_max_pic_order_cnt_lsb,
                                &slice->pic_order_cnt_lsb);
        if (!result && pps->bottom_field_pic_order_in_frame)
        {
            result = h264_read_se(&reader, &slice->delta_pic_order_bottom);
        }
    }
    else if (sps->pic_order_cnt_type == 1 && !sps->delta_pic_order_always_zero)
    {
        result = h264_read_se(&reader, &slice->delta_pic_order0);
        if (!result && pps->bottom_field_pic_order_in_frame)
        {
            result = h264_read_se(&reader, &slice->delta_pic_order1);
        }
    }
    if (!result && pps->redundant_pic_cnt_present)
    {
        result = h264_read_ue(&reader, &value);
    }
    if (result)
    {
        goto out;
    }
    if (slice->slice_type == H264_SLICE_B)
    {
        result = h264_read_bits(&reader, 1, &value);
        if (result)
        {
            goto out;
        }
        slice->direct_spatial_mv_pred = value;
    }
    slice->num_ref_idx_l0 = pps->num_ref_idx_l0;
    slice->num_ref_idx_l1 = pps->num_ref_idx_l1;
    if (slice->slice_type == H264_SLICE_P || slice->slice_type == H264_SLICE_SP ||
        slice->slice_type == H264_SLICE_B)
    {
        result = h264_read_bits(&reader, 1, &value);
        if (result)
        {
            goto out;
        }
        if (value)
        {
            slice->num_ref_idx_active_override = 1;
            result = h264_read_ue(&reader, &value);
            if (result || value > UINT8_MAX - 1)
            {
                result = result ? result : -EINVAL;
                goto out;
            }
            slice->num_ref_idx_l0 = value + 1;
            if (slice->slice_type == H264_SLICE_B)
            {
                result = h264_read_ue(&reader, &value);
                if (result || value > UINT8_MAX - 1)
                {
                    result = result ? result : -EINVAL;
                    goto out;
                }
                slice->num_ref_idx_l1 = value + 1;
            }
        }
    }
    result = h264_slice_check_ref_list_modification(&reader, slice->slice_type);
    if (result)
    {
        goto out;
    }
    if ((pps->weighted_pred && (slice->slice_type == H264_SLICE_P ||
                                slice->slice_type == H264_SLICE_SP)) ||
        (pps->weighted_bipred_idc == 1 && slice->slice_type == H264_SLICE_B))
    {
        result = -ENOTSUP;
        goto out;
    }
    if (slice->nal_ref_idc)
    {
        result = h264_slice_check_ref_marking(&reader, slice->idr_pic);
        if (result)
        {
            goto out;
        }
    }
    if (pps->entropy_coding_mode && slice->slice_type != H264_SLICE_I &&
        slice->slice_type != H264_SLICE_SI)
    {
        result = h264_read_ue(&reader, &value);
        if (result || value > 2)
        {
            result = result ? result : -EINVAL;
            goto out;
        }
        slice->cabac_init_idc = value;
    }
    result = h264_read_se(&reader, &signed_value);
    if (result || signed_value < INT8_MIN || signed_value > INT8_MAX)
    {
        result = result ? result : -EINVAL;
        goto out;
    }
    slice->slice_qp_delta = signed_value;
    if (slice->slice_type == H264_SLICE_SP || slice->slice_type == H264_SLICE_SI)
    {
        result = -ENOTSUP;
        goto out;
    }
    if (pps->deblocking_filter_control)
    {
        result = h264_read_ue(&reader, &value);
        if (result || value > 2)
        {
            result = result ? result : -EINVAL;
            goto out;
        }
        slice->disable_deblocking_filter_idc = value;
        if (value != 1)
        {
            result = h264_read_se(&reader, &signed_value);
            if (result || signed_value < INT8_MIN || signed_value > INT8_MAX)
            {
                result = result ? result : -EINVAL;
                goto out;
            }
            slice->slice_alpha_c0_offset_div2 = signed_value;
            result = h264_read_se(&reader, &signed_value);
            if (result || signed_value < INT8_MIN || signed_value > INT8_MAX)
            {
                result = result ? result : -EINVAL;
                goto out;
            }
            slice->slice_beta_offset_div2 = signed_value;
        }
    }
    slice->header_bits = reader.bit_offset;
    result = 0;
out:
    rt_free(rbsp);
    return result;
}
