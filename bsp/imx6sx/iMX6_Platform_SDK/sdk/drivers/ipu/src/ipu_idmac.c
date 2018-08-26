/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file ipu_idmac.c
 * @brief IPU IDMAC configuration
 * @ingroup diag_ipu
 */
#include "ipu/ipu_common.h"

inline void ipu_cpmem_set_field(uint32_t base, int32_t w, int32_t bit, int32_t size, uint32_t v)
{
    int32_t i = (bit) / 32;
    int32_t off = (bit) % 32;
    _param_word(base, w)[i] |= (v) << off;
    if (((bit) + (size) - 1) / 32 > i) {
        _param_word(base, w)[i + 1] |= (v) >> (off ? (32 - off) : 0);
    }
}

inline void ipu_cpmem_mod_field(uint32_t base, int32_t w, int32_t bit, int32_t size, uint32_t v)
{
    int32_t i = (bit) / 32;
    int32_t off = (bit) % 32;
    uint32_t mask = (1UL << size) - 1;
    uint32_t temp = _param_word(base, w)[i];
    temp &= ~(mask << off);
    _param_word(base, w)[i] = temp | (v) << off;
    if (((bit) + (size) - 1) / 32 > i) {
        temp = _param_word(base, w)[i + 1];
        temp &= ~(mask >> (32 - off));
        _param_word(base, w)[i + 1] = temp | ((v) >> (off ? (32 - off) : 0));
    }
}

inline uint32_t ipu_cpmem_read_field(uint32_t base, int32_t w, int32_t bit, int32_t size)
{
    uint32_t temp2;
    int32_t i = (bit) / 32;
    int32_t off = (bit) % 32;
    uint32_t mask = (1UL << size) - 1;
    uint32_t temp1 = _param_word(base, w)[i];
    temp1 = mask & (temp1 >> off);
    if (((bit) + (size) - 1) / 32 > i) {
        temp2 = _param_word(base, w)[i + 1];
        temp2 &= mask >> (off ? (32 - off) : 0);
        temp1 |= temp2 << (off ? (32 - off) : 0);
    }
    return temp1;
}

/*!
 * set the ipu channel buffer ready signal
 *
 * @param 	ipu_index: 	ipu index
 * @param 	channel: IPU dma channel index
 * @param 	buf: choose the buffer number, 0 or 1
 */
void ipu_channel_buf_ready(int32_t ipu_index, int32_t channel, int32_t buf)
{
    int32_t idx = channel / 32;
    int32_t offset = channel % 32;

    if (idx) {
        if (buf) {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF1_RDY1_CLR, 0);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF1_RDY1__ADDR, 1 << offset, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF0_RDY1_CLR, 0);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF0_RDY1__ADDR, 1 << offset, 1);
        }
    } else {
        if (buf) {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF1_RDY0_CLR, 0);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF1_RDY0__ADDR, 1 << offset, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF0_RDY0_CLR, 0);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF0_RDY0__ADDR, 1 << offset, 1);
        }
    }
}

/*!
 * unset the ipu channel buffer ready signal
 *
 * @param 	ipu_index: 	ipu index
 * @param 	channel: IPU dma channel index
 * @param 	buf: choose the buffer number, 0 or 1
 */
void ipu_channel_buf_not_ready(int32_t ipu_index, int32_t channel, int32_t buf)
{
    int32_t idx = channel / 32;
    int32_t offset = channel % 32;

    if (idx) {
        if (buf) {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF1_RDY1_CLR, 1);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF1_RDY1__ADDR, 1 << offset, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF0_RDY1_CLR, 1);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF0_RDY1__ADDR, 1 << offset, 1);
        }
    } else {
        if (buf) {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF1_RDY0_CLR, 1);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF1_RDY0__ADDR, 1 << offset, 1);
        } else {
            ipu_write_field(ipu_index, IPU_IPU_GPR__IPU_CH_BUF0_RDY0_CLR, 1);
            ipu_write_field(ipu_index, IPU_IPU_CH_BUF0_RDY0__ADDR, 1 << offset, 1);
        }
    }
}

/*!
 * set the ipu channel buffer mode, single or double
 *
 * @param 	ipu_index:      ipu index
 * @param 	channel:        IPU dma channel index
 * @param 	double_buf_en:  enable double buffer 
 *
 */
void ipu_idmac_channel_mode_sel(int32_t ipu_index, int32_t channel, int32_t double_buf_en)
{
    int32_t idx = channel / 32;
    int32_t offset = channel % 32;
    ipu_write_field(ipu_index, IPU_IPU_CH_DB_MODE_SEL_0__ADDR + idx * 4, 1 << offset,
                    double_buf_en);
}

/*!
 * set the ipu channel buffer mode, single or double
 *
 * @param 	ipu_index:  ipu index
 * @param 	channel:    IPU dma channel index
 * @param 	enable:     enable channel  
 *
 */
void ipu_idmac_channel_enable(int32_t ipu_index, int32_t channel, int32_t enable)
{
    int32_t idx = channel / 32;
    int32_t offset = channel % 32;
    ipu_write_field(ipu_index, IPU_IDMAC_CH_EN_1__ADDR + idx * 4, 1 << offset, enable);
}

/*!
 * query the ipu channel buffer busy status
 *
 * @param 	ipu_index:  ipu index
 * @param 	channel:    IPU dma channel index
 *
 * @return 	1 for busy, 0 for idle
 */
int32_t ipu_idmac_channel_busy(int32_t ipu_index, int32_t channel)
{
    int32_t idx, offset;
    uint32_t ipu_base_addr = REGS_IPU_BASE(ipu_index);

    idx = channel / 32;
    offset = channel % 32;
    return ((readl(ipu_base_addr + IPU_IDMAC_CH_BUSY_1__ADDR + 4 * idx) & (1 << offset)) >> offset);
}

/*!
 * Generic IPU DMA channel config
 *
 * @param	ipu_index:	ipu index
 * @param	conf:		ipu configuration data structure
 */
void ipu_general_idmac_config(uint32_t ipu_index, ipu_idmac_info_t * idmac_info)
{
    uint32_t channel = idmac_info->channel;

    ipu_idmac_channel_enable(ipu_index, channel, 0);
    memset((void *)ipu_cpmem_addr(ipu_index, channel), 0, sizeof(ipu_cpmem_t));

    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_EBA0, idmac_info->addr0 / 8);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_EBA1, idmac_info->addr1 / 8);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_FW, idmac_info->width - 1);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_FH, idmac_info->height - 1);

    /*setup default pixel format */
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_PFS, idmac_info->pixel_format);
    ipu_idma_pixel_format_config(ipu_index, channel, idmac_info->pixel_format, idmac_info->so,
                                 idmac_info->sl, idmac_info->u_offset);

    /*setup pixel per burst */
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_NPB, idmac_info->npb);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_SO, idmac_info->so);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_ILO, idmac_info->ilo);

    //setup rotate/vf/hf and block mode
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_ROT, idmac_info->rot);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_VF, idmac_info->vf);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_HF, idmac_info->hf);
    ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_BM, idmac_info->bm);

    if ((void *)idmac_info->addr1 == NULL)
        ipu_idmac_channel_mode_sel(ipu_index, channel, IDMAC_SINGLE_BUFFER);
    else
        ipu_idmac_channel_mode_sel(ipu_index, channel, IDMAC_DOUBLE_BUFFER);

    ipu_idmac_channel_enable(ipu_index, channel, 1);
}

/*!
 * IPU background display DMA channel config (CH23)
 *
 * @param	ipu_index:  ipu index
 * @param	width:		background width
 * @param	height:		background height
 * @param	pixel_format:   background pixel format
 */
void ipu_disp_bg_idmac_config(uint32_t ipu_index, uint32_t addr0, uint32_t addr1, uint32_t width,
                              uint32_t height, uint32_t pixel_format)
{
    ipu_idmac_info_t idmac_info;

    /*setup idma background channel from MEM to display
       channel: 23
     */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = MEM_TO_DP_BG_CH23;
    idmac_info.addr0 = addr0;
    idmac_info.addr1 = addr1;
    idmac_info.width = width;
    idmac_info.height = height;
    idmac_info.pixel_format = pixel_format;
    if (pixel_format == INTERLEAVED_ARGB8888) {
        idmac_info.sl = width * 4;
        idmac_info.u_offset = 0;
    } else if ((pixel_format & 0xF) >= INTERLEAVED_RGB) {
        idmac_info.sl = width * 2;
        idmac_info.u_offset = 0;
    } else {
        idmac_info.sl = width;
        idmac_info.u_offset = width * height;
    }

    idmac_info.npb = 15;
    ipu_general_idmac_config(ipu_index, &idmac_info);
}

/*!
 * IPU foreground display DMA channel config (CH23)
 *
 * @param	ipu_index:  ipu index
 * @param	width:		background width
 * @param	height:		background height
 * @param	pixel_format:   background pixel format
 */
void ipu_disp_fg_idmac_config(uint32_t ipu_index, uint32_t addr0, uint32_t addr1, uint32_t width,
                              uint32_t height, uint32_t pixel_format)
{
    ipu_idmac_info_t idmac_info;

    /*setup idma background channel from MEM to display
       channel: 27
       buffer addr: CH27_EBA0
     */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = MEM_TO_DP_FG_CH27;
    idmac_info.addr0 = addr0;
    idmac_info.addr1 = addr1;
    idmac_info.width = width;
    idmac_info.height = height;
    idmac_info.pixel_format = pixel_format;
    if (pixel_format == INTERLEAVED_ARGB8888) {
        idmac_info.sl = width * 4;
        idmac_info.u_offset = 0;
    } else if ((pixel_format & 0xF) >= INTERLEAVED_RGB) {
        idmac_info.sl = width * 2;
        idmac_info.u_offset = 0;
    } else {
        idmac_info.sl = width;
        idmac_info.u_offset = width * height;
    }

    idmac_info.npb = 15;        // for rotate operation, npb must be equal 7
    ipu_general_idmac_config(ipu_index, &idmac_info);
}

void ipu_dma_update_buffer(uint32_t ipu_index, uint32_t channel, uint32_t buffer_index,
                           uint32_t buffer_addr)
{
    if (buffer_index == 0)
        ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_EBA0, buffer_addr / 8);
    else if (buffer_index == 1)
        ipu_cpmem_mod_field(ipu_cpmem_addr(ipu_index, channel), CPMEM_EBA1, buffer_addr / 8);
    else {
        printf("Wrong buffer index input!!!\n");
    }

}

int32_t ipu_idmac_chan_cur_buff(uint32_t ipu_index, uint32_t channel)
{
    int32_t idx, offset, cur_buf = 0;
    idx = channel / 32;
    offset = channel % 32;
    cur_buf =
        (readl(REGS_IPU_BASE(ipu_index) + IPU_IPU_CUR_BUF_0__ADDR + 4 * idx) & (1 << offset)) >>
        offset;
    return cur_buf;
}

void ipu_rotate_idmac_config(uint32_t ipu_index, uint32_t channel_in, uint32_t channel_out,
                             ipu_rot_info_t rot_info)
{
    ipu_idmac_info_t idmac_info;

    /*setup input idmac channel */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = channel_in;
    idmac_info.addr0 = rot_info.addr0_in;
    idmac_info.addr1 = rot_info.addr1_in;
    idmac_info.width = rot_info.width_in;
    idmac_info.height = rot_info.height_in;
    idmac_info.pixel_format = rot_info.pixel_format_in;
    idmac_info.sl = rot_info.strideline_in;
    idmac_info.u_offset = rot_info.ubo_in;
    idmac_info.npb = 7;         // for rotate operation, npb must be equal 7
    idmac_info.rot = rot_info.rot;
    idmac_info.bm = 1;
    ipu_general_idmac_config(ipu_index, &idmac_info);

    /*setup output idmac channel */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = channel_out;
    idmac_info.addr0 = rot_info.addr0_out;
    idmac_info.addr1 = rot_info.addr1_out;
    idmac_info.width = rot_info.width_out;
    idmac_info.height = rot_info.height_out;
    idmac_info.pixel_format = rot_info.pixel_format_out;
    idmac_info.sl = rot_info.strideline_out;
    idmac_info.u_offset = rot_info.ubo_out;
    idmac_info.npb = 7;         // for rotate operation, npb must be equal 7
    idmac_info.rot = 0;
    idmac_info.vf = rot_info.vf;
    idmac_info.hf = rot_info.hf;
    idmac_info.bm = 1;
    ipu_general_idmac_config(ipu_index, &idmac_info);
}

void ipu_resize_idmac_config(uint32_t ipu_index, uint32_t channel_in, uint32_t channel_out,
                             ipu_res_info_t res_info)
{
    ipu_idmac_info_t idmac_info;

    /*setup input idmac channel */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = channel_in;
    idmac_info.addr0 = res_info.addr0_in;
    idmac_info.addr1 = res_info.addr1_in;
    idmac_info.width = res_info.width_in;
    idmac_info.height = res_info.height_in;
    idmac_info.pixel_format = res_info.pixel_format_in;
    idmac_info.sl = res_info.strideline_in;
    idmac_info.u_offset = res_info.u_offset_in;
    if (res_info.width_in % 16 == 0)
        idmac_info.npb = 15;    //number of pixels per burst
    else
        idmac_info.npb = 7;
    ipu_general_idmac_config(ipu_index, &idmac_info);

    /*setup output idmac channel */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = channel_out;
    idmac_info.addr0 = res_info.addr0_out;
    idmac_info.addr1 = res_info.addr1_out;
    idmac_info.width = res_info.width_out;
    idmac_info.height = res_info.height_out;
    idmac_info.pixel_format = res_info.pixel_format_out;
    idmac_info.sl = res_info.strideline_out;
    idmac_info.u_offset = res_info.u_offset_out;
    if (res_info.width_out % 16 == 0)
        idmac_info.npb = 15;    //number of pixels per burst
    else
        idmac_info.npb = 7;
    ipu_general_idmac_config(ipu_index, &idmac_info);
}

/*in deinterlace we only demo the one field mode, channel 9 as the input*/
void ipu_deinterlace_idmac_config(uint32_t ipu_index, uint32_t channel_in, uint32_t channel_out,
                                  ipu_vdi_info_t res_info)
{
    ipu_idmac_info_t idmac_info;

    if (csi_vdi_direct_path == 0)   // data direct from CSI, no input channel needed
    {
        /*setup input idmac channel */
        memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
        idmac_info.channel = channel_in;
        idmac_info.addr0 = res_info.addr0_in;
        idmac_info.addr1 = res_info.addr1_in;
        idmac_info.width = res_info.width_in;
        idmac_info.height = res_info.height_in / 2;
        idmac_info.pixel_format = res_info.pixel_format_in;
        idmac_info.sl = res_info.strideline_in;
        idmac_info.u_offset = res_info.u_offset_in;
        if (res_info.width_in % 16 == 0)
            idmac_info.npb = 15;    //number of pixels per burst
        else
            idmac_info.npb = 7;
        ipu_general_idmac_config(ipu_index, &idmac_info);
    }

    /*setup output idmac channel */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = channel_out;
    idmac_info.addr0 = res_info.addr0_out;
    idmac_info.addr1 = res_info.addr1_out;
    idmac_info.width = res_info.width_out;
    idmac_info.height = res_info.height_out;
    idmac_info.pixel_format = res_info.pixel_format_out;
    idmac_info.sl = res_info.strideline_out;
    idmac_info.u_offset = res_info.u_offset_out;
    if (res_info.width_out % 16 == 0)
        idmac_info.npb = 15;    //number of pixels per burst
    else
        idmac_info.npb = 7;
    ipu_general_idmac_config(ipu_index, &idmac_info);
}

void ipu_idma_pixel_format_config(uint32_t ipu_index, uint32_t channel, uint32_t pixel_format,
                                  uint32_t so, uint32_t sl, uint32_t ubo)
{
    switch (pixel_format) {
    case NON_INTERLEAVED_YUV444:
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_UBO, ubo / 8);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_VBO, ubo * 2 / 8);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLUV, sl - 1);
        break;
    case NON_INTERLEAVED_YUV422:
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_UBO, ubo / 8);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_VBO, ubo * 3 / 16);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLUV, sl / 2 - 1);
        break;
    case NON_INTERLEAVED_YUV420:
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_UBO, ubo / 8);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_VBO, ubo * 5 / 32);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLUV, sl / 2 - 1);
        break;
    case PARTIAL_INTERLEAVED_YUV422:
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_UBO, ubo / 8);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_VBO, ubo / 8);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLUV, sl - 1);
        break;
    case PARTIAL_INTERLEAVED_YUV420:
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_UBO, ubo / 8);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_VBO, ubo / 8);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLUV, sl - 1);
        break;
    case INTERLEAVED_LUT:
        break;
    case INTERLEAVED_GENERIC:
        break;
    case INTERLEAVED_RGB565:   //default INTERLEAVED_RGB: RGB565
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_BPP, 0x3);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID0, 5 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID1, 6 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID2, 5 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID3, 0 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF0, 0);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF1, 5);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF2, 11);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF3, 16);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        break;
    case INTERLEAVED_ARGB8888: //for GPU demo usage
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_BPP, 0x0);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID0, 8 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID1, 8 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID2, 8 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_WID3, 8 - 1);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF0, 8);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF1, 16);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF2, 24);
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_OFF3, 0);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        break;
    case INTERLEAVED_Y1U1Y2V1:
    case INTERLEAVED_Y2U1Y1V1:
    case INTERLEAVED_U1Y1V1Y2:
    case INTERLEAVED_U1Y2V1Y1:
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), INTERLEAVED_BPP, 3);
        if (so == 1) {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY,
                                sl * 2 - 1);
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_ILO, sl / 8);
        } else {
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, channel), NON_INTERLEAVED_SLY, sl - 1);
        }
        break;
    default:
        printf("Invalid pixel format!\n");
        break;
    }
}
