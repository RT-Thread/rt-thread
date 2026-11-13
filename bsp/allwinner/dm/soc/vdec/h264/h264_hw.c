/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>

#include <rthw.h>
#include <rtthread.h>

#include "vdec-sun252i.h"
#include "h264_hw.h"

#define DBG_TAG "vdec.h264"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* Sun252i VE top-level and H.264 decoder windows. */
#define H264_HW_MODE                       0x000
#define H264_HW_MODE_DEC_H264              0x009
#define H264_HW_MODE_DEC_MASK              0x00f
#define H264_HW_MODE_MEMORY_MASK           (RT_BIT(21) | RT_BIT(22))
#define H264_HW_TOP_FLAGS                  0x01c
#define H264_HW_TOP_START                  RT_BIT(6)
#define H264_HW_LINE_BUF_CTRL               0x050
#define H264_HW_LINE_BUF_DRAM               0x00aU
#define H264_HW_DEBLOCK_BUF                 0x054
#define H264_HW_INTRA_BUF                   0x058
#define H264_HW_PRIMARY_CHROMA_LEN         0x0c4
#define H264_HW_PRIMARY_LINE_STRIDE        0x0c8
#define H264_HW_PRIMARY_OUTPUT_FORMAT      0x0ec

#define H264_HW_SPS                        0x200
#define H264_HW_SPS_MBS_ONLY               RT_BIT(18)
#define H264_HW_SPS_MBAFF                  RT_BIT(17)
#define H264_HW_SPS_DIRECT_8X8             RT_BIT(16)
#define H264_HW_PPS                        0x204
#define H264_HW_PPS_CABAC                  RT_BIT(15)
#define H264_HW_PPS_WEIGHTED_PRED          RT_BIT(4)
#define H264_HW_PPS_CONSTRAINED_INTRA      RT_BIT(1)
#define H264_HW_PPS_TRANSFORM_8X8          RT_BIT(0)
#define H264_HW_SLICE                      0x208
#define H264_HW_SLICE_FIRST                RT_BIT(5)
#define H264_HW_SLICE_FIELD                RT_BIT(4)
#define H264_HW_SLICE_BOTTOM               RT_BIT(3)
#define H264_HW_SLICE_DIRECT_SPATIAL       RT_BIT(2)
#define H264_HW_SLICE2                     0x20c
#define H264_HW_SLICE2_REF_OVERRIDE        RT_BIT(12)
#define H264_HW_SLICE_QP                   0x21c
#define H264_HW_SLICE_QP_DEFAULT_MATRIX    RT_BIT(24)
#define H264_HW_CTRL                        0x220
#define H264_HW_CTRL_FUNC_ENABLE             RT_BIT(10)
#define H264_HW_CTRL_ERROR_IRQ             RT_BIT(1)
#define H264_HW_CTRL_DONE_IRQ              RT_BIT(0)
#define H264_HW_TRIGGER                    0x224
#define H264_HW_TRIGGER_AVC_SLICE          8
#define H264_HW_STATUS                     0x228
#define H264_HW_VLD_ADDRESS                0x230
#define H264_HW_VLD_ADDRESS_FIRST          RT_BIT(30)
#define H264_HW_VLD_ADDRESS_LAST           RT_BIT(29)
#define H264_HW_VLD_ADDRESS_VALID          RT_BIT(28)
#define H264_HW_VLD_OFFSET                 0x234
#define H264_HW_VLD_LENGTH                 0x238
#define H264_HW_VLD_END                    0x23c
#define H264_HW_SDROT_CTRL                  0x240
#define H264_HW_OUTPUT_FRAME_INDEX          0x24c
#define H264_HW_PIC_INFO                    0x250
#define H264_HW_NEIGHBOR                    0x254
#define H264_HW_MB_ADDRESS                  0x260
#define H264_HW_SRAM_OFFSET                 0x2e0
#define H264_HW_SRAM_DATA                   0x2e4

#define H264_HW_PIC_INFO_SIZE               (130U * 1024U)
#define H264_HW_DEBLOCK_SIZE                (32U * 1024U)
#define H264_HW_INTRA_SIZE                  (32U * 1024U)
#define H264_HW_NEIGHBOR_SIZE               (64U * 1024U)
#define H264_HW_NEIGHBOR_ALIGN              (16U * 1024U)
#define H264_HW_FRAME_SLOTS                 18U
#define H264_HW_SRAM_FRAME_INFO             0x400
#define H264_HW_SRAM_REF_LIST0              0x640
#define H264_HW_SRAM_REF_LIST1              0x664

static rt_uint32_t h264_hw_vld_address(rt_ubase_t address)
{
    return ((rt_uint32_t)address & 0x0ffffff0U) | ((rt_uint32_t)address >> 28);
}

static void h264_hw_write_sram(rt_uint32_t offset, const rt_uint32_t *data, rt_size_t count)
{
    sunxi_vdec_hw_writel(H264_HW_SRAM_OFFSET, offset);
    while (count--)
    {
        sunxi_vdec_hw_writel(H264_HW_SRAM_DATA, *data++);
    }
}

void h264_hw_enable(void)
{
    rt_uint32_t value = sunxi_vdec_hw_readl(H264_HW_MODE);

    /* The Sun252i top block inverts select bit 3; H.264 is selector 9, not 1. */
    sunxi_vdec_hw_writel(H264_HW_MODE,
                          (value & ~(H264_HW_MODE_DEC_MASK | H264_HW_MODE_MEMORY_MASK)) |
                          H264_HW_MODE_DEC_H264);
    rt_hw_dsb();
}

int h264_hw_buffers_init(struct h264_hw_buffers *buffers)
{
    if (!buffers)
    {
        return -EINVAL;
    }
    rt_memset(buffers, 0, sizeof(*buffers));
    buffers->deblock = sunxi_vdec_hw_dma_alloc(H264_HW_DEBLOCK_SIZE,
                                                &buffers->deblock_dma);
    if (!buffers->deblock)
    {
        return -ENOMEM;
    }
    buffers->intra = sunxi_vdec_hw_dma_alloc(H264_HW_INTRA_SIZE,
                                              &buffers->intra_dma);
    if (!buffers->intra)
    {
        h264_hw_buffers_deinit(buffers);
        return -ENOMEM;
    }
    buffers->pic_info = sunxi_vdec_hw_dma_alloc(H264_HW_PIC_INFO_SIZE,
                                                 &buffers->pic_info_dma);
    if (!buffers->pic_info)
    {
        h264_hw_buffers_deinit(buffers);
        return -ENOMEM;
    }
    buffers->neighbor = sunxi_vdec_hw_dma_alloc(H264_HW_NEIGHBOR_SIZE +
                                                 H264_HW_NEIGHBOR_ALIGN - 1U,
                                                 &buffers->neighbor_dma);
    if (!buffers->neighbor)
    {
        h264_hw_buffers_deinit(buffers);
        return -ENOMEM;
    }
    buffers->neighbor_aligned_dma = RT_ALIGN(buffers->neighbor_dma,
                                             H264_HW_NEIGHBOR_ALIGN);
    rt_memset(buffers->deblock, 0, H264_HW_DEBLOCK_SIZE);
    rt_memset(buffers->intra, 0, H264_HW_INTRA_SIZE);
    rt_memset(buffers->pic_info, 0, H264_HW_PIC_INFO_SIZE);
    rt_memset(buffers->neighbor, 0, H264_HW_NEIGHBOR_SIZE +
                                  H264_HW_NEIGHBOR_ALIGN - 1U);
#ifndef ARCH_MM_MMU
    rt_hw_cpu_dcache_clean_and_invalidate(buffers->deblock, H264_HW_DEBLOCK_SIZE);
    rt_hw_cpu_dcache_clean_and_invalidate(buffers->intra, H264_HW_INTRA_SIZE);
    rt_hw_cpu_dcache_clean_and_invalidate(buffers->pic_info, H264_HW_PIC_INFO_SIZE);
    rt_hw_cpu_dcache_clean_and_invalidate(buffers->neighbor, H264_HW_NEIGHBOR_SIZE +
                                          H264_HW_NEIGHBOR_ALIGN - 1U);
#endif
    LOG_I("line buffers: external DRAM (ctrl=0x0a)");
    return 0;
}

void h264_hw_buffers_deinit(struct h264_hw_buffers *buffers)
{
    if (!buffers)
    {
        return;
    }
    if (buffers->neighbor)
    {
        sunxi_vdec_hw_dma_free(buffers->neighbor);
    }
    if (buffers->pic_info)
    {
        sunxi_vdec_hw_dma_free(buffers->pic_info);
    }
    if (buffers->intra)
    {
        sunxi_vdec_hw_dma_free(buffers->intra);
    }
    if (buffers->deblock)
    {
        sunxi_vdec_hw_dma_free(buffers->deblock);
    }
    rt_memset(buffers, 0, sizeof(*buffers));
}

static void h264_hw_write_ref_list(rt_uint32_t offset, struct h264_frame *const *frames,
                                   rt_uint8_t count)
{
    rt_uint32_t words[9] = {0};
    rt_uint8_t index;

    for (index = 0; index < count && index < 32; index++)
    {
        words[index / 4] |= (rt_uint32_t)(frames[index]->index << 1) <<
                            ((index % 4) * 8);
    }
    h264_hw_write_sram(offset, words, RT_ARRAY_SIZE(words));
}

int h264_hw_program_frames(const struct h264_hw_buffers *buffers,
                           const struct h264_frame_pool *pool,
                           const struct h264_frame *output,
                           struct h264_frame *const *ref_list0, rt_uint8_t ref_count0,
                           struct h264_frame *const *ref_list1, rt_uint8_t ref_count1)
{
    rt_uint8_t index;

    if (!buffers || !pool || !output || !buffers->deblock || !buffers->intra ||
        !buffers->pic_info || !buffers->neighbor || !buffers->neighbor_aligned_dma ||
        output->index >= pool->count || ref_count0 > 32 || ref_count1 > 32 ||
        (ref_count0 && !ref_list0) || (ref_count1 && !ref_list1))
    {
        return -EINVAL;
    }
    /* Full-DRAM mode must not exceed the allocated line/MB buffers. */
    if ((rt_size_t)pool->width_in_mbs * 1024U > H264_HW_DEBLOCK_SIZE ||
        16384U + (rt_size_t)pool->width_in_mbs * 546U > H264_HW_INTRA_SIZE ||
        (rt_size_t)pool->width_in_mbs * pool->height_in_mbs * 64U >
            H264_HW_NEIGHBOR_SIZE)
    {
        LOG_E("picture exceeds H.264 scratch buffer capacity");
        return -ENOTSUP;
    }
    for (index = 0; index < H264_HW_FRAME_SLOTS; index++)
    {
        rt_uint32_t entry[8] = {0};
        const struct h264_frame *frame;

        if (index >= pool->count)
        {
            h264_hw_write_sram(H264_HW_SRAM_FRAME_INFO + index * sizeof(entry), entry,
                               RT_ARRAY_SIZE(entry));
            continue;
        }
        frame = &pool->frames[index];
        if (!frame->data || !frame->mv_col || frame->dma > UINT32_MAX ||
            frame->mv_col_dma > UINT32_MAX)
        {
            return -EINVAL;
        }
        entry[0] = frame->poc;
        entry[1] = frame->poc;
        entry[3] = frame->dma;
        entry[4] = frame->dma + frame->stride * RT_ALIGN(frame->height, 32);
        entry[5] = frame->mv_col_dma;
        entry[6] = frame->mv_col_dma + frame->mv_col_field_size;
        h264_hw_write_sram(H264_HW_SRAM_FRAME_INFO + index * sizeof(entry), entry,
                           RT_ARRAY_SIZE(entry));
    }
    sunxi_vdec_hw_writel(H264_HW_SDROT_CTRL, 0);
    /* Mode 1 still uses SRAM for the left part; mode 2 uses DRAM throughout. */
    sunxi_vdec_hw_writel(H264_HW_DEBLOCK_BUF, buffers->deblock_dma);
    sunxi_vdec_hw_writel(H264_HW_INTRA_BUF, buffers->intra_dma);
    sunxi_vdec_hw_writel(H264_HW_LINE_BUF_CTRL,
                          (sunxi_vdec_hw_readl(H264_HW_LINE_BUF_CTRL) & ~0x0fU) |
                          H264_HW_LINE_BUF_DRAM);
    rt_hw_dsb();
    if ((sunxi_vdec_hw_readl(H264_HW_LINE_BUF_CTRL) & 0x0fU) != H264_HW_LINE_BUF_DRAM ||
        sunxi_vdec_hw_readl(H264_HW_DEBLOCK_BUF) != buffers->deblock_dma ||
        sunxi_vdec_hw_readl(H264_HW_INTRA_BUF) != buffers->intra_dma)
    {
        LOG_E("line buffer readback: ctrl=%08x deblock=%08x intra=%08x",
              sunxi_vdec_hw_readl(H264_HW_LINE_BUF_CTRL),
              sunxi_vdec_hw_readl(H264_HW_DEBLOCK_BUF),
              sunxi_vdec_hw_readl(H264_HW_INTRA_BUF));
        return -EIO;
    }
    sunxi_vdec_hw_writel(H264_HW_PIC_INFO, buffers->pic_info_dma);
    sunxi_vdec_hw_writel(H264_HW_NEIGHBOR, buffers->neighbor_aligned_dma);
    sunxi_vdec_hw_writel(H264_HW_MB_ADDRESS, 0);
    sunxi_vdec_hw_writel(H264_HW_OUTPUT_FRAME_INDEX, output->index);
    h264_hw_write_ref_list(H264_HW_SRAM_REF_LIST0, ref_list0, ref_count0);
    h264_hw_write_ref_list(H264_HW_SRAM_REF_LIST1, ref_list1, ref_count1);
    return 0;
}

int h264_hw_program_slice(const struct h264_sps *sps, const struct h264_pps *pps,
                          const struct h264_slice *slice, rt_ubase_t bitstream_dma,
                          rt_size_t bitstream_size, rt_uint32_t bit_offset,
                          rt_bool_t first_slice, rt_bool_t nv21)
{
    rt_uint32_t value;

    if (!sps || !pps || !slice || !bitstream_dma || !bitstream_size ||
        bitstream_dma > UINT32_MAX || bitstream_size > UINT32_MAX / 8 ||
        bit_offset > bitstream_size * 8)
    {
        return -EINVAL;
    }
    if (sps->chroma_format_idc != 1 || sps->width_in_mbs == 0 ||
        sps->height_in_map_units == 0 || slice->slice_type > H264_SLICE_SI)
    {
        return -ENOTSUP;
    }

    /* The decoded picture stays tiled; the VE conversion block makes NV12 later. */
    sunxi_vdec_hw_writel(H264_HW_CTRL, H264_HW_CTRL_FUNC_ENABLE);

    /*
     * The VE's software bitstream-parser initialization must precede the
     * H.264 context registers.  Cedrus does this even though the header is
     * parsed by software: omitting or moving it later leaves the decoder
     * idle on this generation.
     */
    sunxi_vdec_hw_writel(H264_HW_VLD_LENGTH, bitstream_size * 8);
    sunxi_vdec_hw_writel(H264_HW_VLD_OFFSET, 0);
    sunxi_vdec_hw_writel(H264_HW_VLD_END, bitstream_dma + bitstream_size);
    sunxi_vdec_hw_writel(H264_HW_VLD_ADDRESS, h264_hw_vld_address(bitstream_dma) |
                          H264_HW_VLD_ADDRESS_FIRST | H264_HW_VLD_ADDRESS_LAST |
                          H264_HW_VLD_ADDRESS_VALID);
    sunxi_vdec_hw_writel(H264_HW_TRIGGER, 7);
    while (bit_offset)
    {
        rt_uint32_t count = bit_offset > 32U ? 32U : bit_offset;
        rt_uint32_t timeout = 1000;

        sunxi_vdec_hw_writel(H264_HW_TRIGGER, (count << 8) | 3U);
        while (sunxi_vdec_hw_readl(H264_HW_STATUS) & RT_BIT(8))
        {
            if (!timeout--)
            {
                return -ETIMEDOUT;
            }
            rt_hw_us_delay(1);
        }
        bit_offset -= count;
    }

    /* Keep PPS before SPS, matching the hardware driver's programming order. */
    value = ((rt_uint32_t)(slice->num_ref_idx_l0 - 1) << 10) |
            ((rt_uint32_t)(slice->num_ref_idx_l1 - 1) << 5) |
            ((rt_uint32_t)pps->weighted_bipred_idc << 2);
    if (pps->entropy_coding_mode)
    {
        value |= H264_HW_PPS_CABAC;
    }
    if (pps->weighted_pred)
    {
        value |= H264_HW_PPS_WEIGHTED_PRED;
    }
    if (pps->constrained_intra_pred)
    {
        value |= H264_HW_PPS_CONSTRAINED_INTRA;
    }
    if (pps->transform_8x8_mode)
    {
        value |= H264_HW_PPS_TRANSFORM_8X8;
    }
    sunxi_vdec_hw_writel(H264_HW_PPS, value);

    value = ((rt_uint32_t)sps->chroma_format_idc << 19) |
            ((rt_uint32_t)(sps->width_in_mbs - 1) << 8) |
            (sps->height_in_map_units - 1);
    if (sps->frame_mbs_only)
    {
        value |= H264_HW_SPS_MBS_ONLY;
    }
    if (sps->mb_adaptive_frame_field)
    {
        value |= H264_HW_SPS_MBAFF;
    }
    if (sps->direct_8x8_inference)
    {
        value |= H264_HW_SPS_DIRECT_8X8;
    }
    sunxi_vdec_hw_writel(H264_HW_SPS, value);

    value = ((slice->first_mb_in_slice % sps->width_in_mbs) << 24) |
            ((slice->first_mb_in_slice / sps->width_in_mbs) << 16) |
            ((rt_uint32_t)!!slice->nal_ref_idc << 12) |
            ((rt_uint32_t)slice->slice_type << 8) | slice->cabac_init_idc;
    if (first_slice)
    {
        value |= H264_HW_SLICE_FIRST;
    }
    if (slice->field_pic)
    {
        value |= H264_HW_SLICE_FIELD;
    }
    if (slice->bottom_field)
    {
        value |= H264_HW_SLICE_BOTTOM;
    }
    if (slice->direct_spatial_mv_pred)
    {
        value |= H264_HW_SLICE_DIRECT_SPATIAL;
    }
    sunxi_vdec_hw_writel(H264_HW_SLICE, value);

    value = ((rt_uint32_t)(slice->num_ref_idx_l0 - 1) << 24) |
            ((rt_uint32_t)(slice->num_ref_idx_l1 - 1) << 16) |
            ((rt_uint32_t)slice->disable_deblocking_filter_idc << 8) |
            (((rt_uint32_t)slice->slice_alpha_c0_offset_div2 & 0xf) << 4) |
            ((rt_uint32_t)slice->slice_beta_offset_div2 & 0xf);
    /* VE consumes the L0/L1 counts from this register for every slice. */
    value |= H264_HW_SLICE2_REF_OVERRIDE;
    sunxi_vdec_hw_writel(H264_HW_SLICE2, value);

    value = ((rt_uint32_t)pps->second_chroma_qp_index_offset & 0x3f) << 16 |
            ((rt_uint32_t)pps->chroma_qp_index_offset & 0x3f) << 8 |
            ((rt_uint32_t)(pps->pic_init_qp + 26 + slice->slice_qp_delta) & 0x3f) |
            H264_HW_SLICE_QP_DEFAULT_MATRIX;
    sunxi_vdec_hw_writel(H264_HW_SLICE_QP, value);

    sunxi_vdec_hw_writel(H264_HW_STATUS, sunxi_vdec_hw_readl(H264_HW_STATUS));
    value = sunxi_vdec_hw_readl(H264_HW_CTRL);
    sunxi_vdec_hw_writel(H264_HW_CTRL, value | H264_HW_CTRL_DONE_IRQ |
                          H264_HW_CTRL_ERROR_IRQ | RT_BIT(2));

    return 0;
}

void h264_hw_start_slice(void)
{
    /* Complete all VE register writes before the start side effect. */
    rt_hw_dsb();
    sunxi_vdec_hw_writel(H264_HW_TOP_FLAGS,
                          sunxi_vdec_hw_readl(H264_HW_TOP_FLAGS) | H264_HW_TOP_START);
    sunxi_vdec_hw_writel(H264_HW_TRIGGER, H264_HW_TRIGGER_AVC_SLICE);
    rt_hw_dsb();
}

rt_uint32_t h264_hw_read_status(void)
{
    return sunxi_vdec_hw_readl(H264_HW_STATUS);
}

rt_uint32_t h264_hw_ack_status(void)
{
    rt_uint32_t status = h264_hw_read_status();

    sunxi_vdec_hw_writel(H264_HW_STATUS, status);
    return status;
}

