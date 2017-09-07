/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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
 * @file ipu_common.c
 * @brief common functions defination of IPU.
 * @ingroup diag_ipu
 */

#include <string.h>
#include "ipu/ipu_common.h"

inline int32_t need_csc(int32_t i, int32_t o)
{
    if ((((i & 0xF) == (INTERLEAVED_RGB)) && (o > DCMAP_BRG888))
        || (((i & 0xF) != INTERLEAVED_RGB) && (o <= DCMAP_BRG888)))
        return 1;
    else
        return 0;
}

/*!
 * write field of ipu registers, without affecting other bits.
 *
 * @param	ipu_index:	ipu index
 * @param	ID_addr:    register address
 * @param	ID_mask:    fields position
 * @param	data:	    the value of input
 */
void ipu_write_field(int32_t ipu_index, uint32_t ID_addr, uint32_t ID_mask, uint32_t data)
{
    uint32_t rdata;

    ID_addr += REGS_IPU_BASE(ipu_index);

    rdata = readl(ID_addr);
    rdata &= ~ID_mask;
    rdata |= (data * (ID_mask & -ID_mask)) & ID_mask;
    writel(rdata, ID_addr);
}

/*!
 * write field of ipu registers, without affecting other bits.
 *
 * @param	ipu_index:	ipu index
 * @param	ID_addr:    register address
 */
uint32_t ipu_read(int32_t ipu_index, uint32_t ID_addr)
{
    uint32_t rdata;

    ID_addr += REGS_IPU_BASE(ipu_index);

    rdata = readl(ID_addr);

    return rdata;
}

/*!
 * write field of ipu registers, without affecting other bits.
 *
 * @param	ipu_index:	ipu index
 * @param	ID_addr:    register address
 * @param	ID_mask:    fields position
 * @param	data:	    the value of input
 */
void ipu_write(int32_t ipu_index, uint32_t ID_addr, uint32_t data)
{
    ID_addr += REGS_IPU_BASE(ipu_index);

    writel(data, ID_addr);
}

/*!
 * enable submodules of IPU to establish the data path.
 *
 * @param	ipu_index:	ipu index
 */
void ipu_enable_display(int32_t ipu_index)
{
    /*enable all the related submodules. */
    ipu_write_field(ipu_index, IPU_IPU_CONF__DI0_EN, 1);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DP_EN, 1);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DC_EN, 1);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DMFC_EN, 1);
}

/*!
 * disable submodules of IPU to establish the data path.
 *
 * @param	ipu_index:	ipu index
 */
void ipu_disable_display(int32_t ipu_index)
{
    /*enable all the related submodules. */
    ipu_write_field(ipu_index, IPU_IPU_CONF__DI0_EN, 0);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DI1_EN, 0);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DP_EN, 0);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DC_EN, 0);
    ipu_write_field(ipu_index, IPU_IPU_CONF__DMFC_EN, 0);
}

/*!
 * reset ipu by SRC(system reset controller)
 *
 * @param	ipu_index:	ipu index
 * @param	timeout:    time out setting for ipu reset
 *
 * @return	true for success, others for time out.
 */
int32_t ipu_sw_reset(int32_t ipu_index, int32_t timeout)
{
    uint32_t tmpVal;
    int32_t ipuOffset = 0x3;

    if (ipu_index == 1)
        ipuOffset = 0x3;
    else
        ipuOffset = 0xC;
    tmpVal = readl(SRC_BASE_ADDR);
    writel(tmpVal | (0x1 << ipuOffset), SRC_BASE_ADDR);

    while (timeout > 0) {
        tmpVal = readl(SRC_BASE_ADDR) & (0x1 << ipuOffset);
        timeout--;

        if (tmpVal == 0)
            return true;
    }

    printf("Error: ipu software reset time out!!\n");
    return false;
}

/*!
 * display function HW configuration for IPU.
 *
 * @param   ipu_index ipu index
 * @param   panel ipu panel configuration data structure
 * @param   mem_colorimetry colorimetry configuration
 * @param   csc_type color space conversion type
 */
void ipu_display_setup(uint32_t ipu_index, uint32_t mem_addr0, uint32_t mem_addr1,
                       uint32_t mem_colorimetry, ips_dev_panel_t * panel)
{
    uint32_t channel = MEM_TO_DP_BG_CH23;
    uint32_t di = 0;
    uint32_t in_type, out_type, csc_type = NO_CSC;

    /*step1: determine CSC type according input colorimetry and output colorimetry */
    in_type = ((mem_colorimetry & 0xF) == INTERLEAVED_RGB) ? RGB : YUV;
    switch (panel->colorimetry) {
    case DCMAP_YUV888:
    case DCMAP_UVY888:
    case DCMAP_VYU888:
    case DCMAP_YUVA8888:
        out_type = YUV;
        break;
    default:
        out_type = RGB;
        break;
    }

    if (in_type == RGB && out_type == YUV)
        csc_type = RGB_YUV;
    else if (in_type == YUV && out_type == RGB)
        csc_type = YUV_RGB;
    else
        csc_type = NO_CSC;

    /*step2: setup idma channel for background only */
    ipu_disp_bg_idmac_config(ipu_index, mem_addr0, mem_addr1, panel->width, panel->height,
                             mem_colorimetry);
    ipu_dmfc_config(ipu_index, channel);
    ipu_dc_config(ipu_index, channel, di, panel->width, panel->colorimetry);
    ipu_dp_config(ipu_index, csc_type, 0, 0, 0, 0);
    ipu_di_config(ipu_index, di, panel);
}

/*!
 * display function HW configuration for IPU.
 *
 * @param	ipu_index:	ipu index
 * @param	panel:		ipu panel configuration data structure
 * @param   mem_colorimetry colorimetry configuration
 * @param   fg_width foreground width
 * @param   fg_height foreground height
 * @param   fg_xp foreground x position
 * @param   fg_yp foreground y position
 * @param   alpha alpha value
 */
void ipu_dual_display_setup(uint32_t ipu_index, ips_dev_panel_t * panel, uint32_t mem_colorimetry,
                            uint32_t fg_width, uint32_t fg_height, uint32_t fg_xp, uint32_t fg_yp,
                            uint32_t alpha)
{
    uint32_t bg_channel = MEM_TO_DP_BG_CH23;
    uint32_t fg_channel = MEM_TO_DP_FG_CH27;
    uint32_t di = 0;

    //dual display: partial plane display
    //config foreground idma
    ipu_disp_fg_idmac_config(ipu_index, CH27_EBA0, 0, fg_width, fg_height, mem_colorimetry);
    //config background idma
    ipu_disp_bg_idmac_config(ipu_index, CH23_EBA0, 0, panel->width, panel->height, mem_colorimetry);

    ipu_dmfc_config(ipu_index, fg_channel);
    ipu_dmfc_config(ipu_index, bg_channel);

    ipu_dc_config(ipu_index, bg_channel, di, panel->width, panel->colorimetry);
    //set the foreground position: in the middle of the screen and at the bottom of the screen.
    ipu_dp_config(ipu_index, NO_CSC, 1, fg_xp, fg_yp, alpha);
    ipu_di_config(ipu_index, di, panel);
}

extern int32_t ips_deinterlace_proc(int width, int height, ips_dev_panel_t * panel);
int csi_vdi_direct_path = 0;
int csi_dma_band_mode = 0;
void ipu_ch0_eobnd_interrupt_register(int ipu_index);
void ipu_capture_setup(uint32_t ipu_index, uint32_t csi_interface, uint32_t raw_width,
                       uint32_t raw_height, uint32_t act_width, uint32_t act_height,
                       ips_dev_panel_t * panel)
{
    uint32_t csi_in_channel = CSI_TO_MEM_CH0, disp_channel = MEM_TO_DP_BG_CH23;
    ipu_idmac_info_t idmac_info;
    uint32_t csi_mem0 = CH23_EBA0, csi_mem1 = 0;
    uint32_t disp_mem0 = csi_mem0, disp_mem1 = csi_mem1;
    uint32_t csi_pixel_format = NON_INTERLEAVED_YUV420;
    
    /*step1: config the csi: idma channel (csi -- mem), smfc, csi */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = CSI_TO_MEM_CH0;
    idmac_info.addr0 = csi_mem0;
    idmac_info.addr1 = csi_mem1;
    idmac_info.width = act_width;
    idmac_info.height = act_height;

    if (csi_interface == CSI_TEST_MODE)
        csi_pixel_format = INTERLEAVED_RGB565;
    idmac_info.pixel_format = csi_pixel_format;

    if (csi_interface == CSI_BT656_NTSC_INTERLACED || csi_interface == CSI_BT656_PAL_INTERLACED)
        idmac_info.so = 1;
    else
        idmac_info.so = 0;

    if ((csi_pixel_format & 0xF) >= INTERLEAVED_RGB) {
        idmac_info.sl = panel->width * 2;
        idmac_info.u_offset = 0;
    } else {
        idmac_info.sl = panel->width;
        idmac_info.u_offset = panel->width * panel->height;
    }
    idmac_info.npb = 15;

    if (csi_vdi_direct_path == 0)   // put csi captured image into memory first
    {
        ipu_general_idmac_config(ipu_index, &idmac_info);

        /*step2: allocate smfc fifo for CSI input channel */
        ipu_smfc_fifo_allocate(ipu_index, 0, 0, 3);
    }

    if(csi_dma_band_mode) // enable band mode
    {
        ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, idmac_info.channel), CPMEM_BNDM, 0x6); // set band lines, test 128 lines mode 
        ipu_write_field(ipu_index, IPU_IDMAC_BNDM_EN_1__IDMAC_BNDM_EN_0 << idmac_info.channel, 1); // enable band mode
        if(idmac_info.channel == 0)
            ipu_ch0_eobnd_interrupt_register(ipu_index); 
        else {
            printf("CSI channel not supported! you need to modify the interrupt registration!\n");
            ipu_cpmem_set_field(ipu_cpmem_addr(ipu_index, idmac_info.channel), CPMEM_BNDM, 0x0); 
            ipu_write_field(ipu_index, IPU_IDMAC_BNDM_EN_1__IDMAC_BNDM_EN_0 << idmac_info.channel, 0); 
        }
    }

    /*step3: config csi for IPU */
    ipu_csi_config(ipu_index, csi_interface, raw_width, raw_height, act_width, act_height);

    /*step4: config display channel: idma, dmfc, dc, dp, di */
    if(csi_dma_band_mode)
    {
        disp_mem0 = CH27_EBA0;
        disp_mem1 = 0;
    }
    ipu_display_setup(ipu_index, disp_mem0, disp_mem1, csi_pixel_format, panel);

    /*step5: link csi and display */
    ipu_capture_disp_link(ipu_index, 0);

    /*step6: paint the other display area to white. */
    if (csi_pixel_format == NON_INTERLEAVED_YUV420) {
        memset((void *)disp_mem0, 0xFF, panel->width * panel->height);
        memset((void *)(disp_mem0 + panel->width * panel->height), 0x80,
               panel->width * panel->height / 2);
    } else {
        memset((void *)disp_mem0, 0xFF, panel->width * panel->height * 2);
    }

    if (csi_vdi_direct_path == 1)
        ips_deinterlace_proc(act_width, act_height, panel);

    ipu_channel_buf_ready(ipu_index, csi_in_channel, 0);
    ipu_channel_buf_ready(ipu_index, csi_in_channel, 1);

    ipu_channel_buf_ready(ipu_index, disp_channel, 0);
    ipu_channel_buf_ready(ipu_index, disp_channel, 1);
}

void ipu_capture_streamoff(uint32_t ipu_index)
{
    int timeout = 5000;

    /*wait for idmac eof and disable csi-->smfc-->idmac */

    /* enable idmac channel 0 eof and wait for eof */
    ipu_write_field(ipu_index, IPU_IPU_INT_CTRL_1__IDMAC_EOF_EN_0, 1);
    ipu_write_field(ipu_index, IPU_IPU_INT_STAT_1__IDMAC_EOF_0, 1);

    while (!(ipu_read(ipu_index, IPU_IPU_INT_STAT_1__ADDR) & 0x1)) {
        hal_delay_us(10);
        if (timeout <= 0)
            break;
        timeout--;
    }

    ipu_disable_csi(ipu_index, 0);
    ipu_disable_smfc(ipu_index);

    ipu_idmac_channel_enable(ipu_index, CSI_TO_MEM_CH0, 0);
}

void ipu_mipi_csi2_setup(uint32_t ipu_index, uint32_t csi_width, uint32_t csi_height,
                         ips_dev_panel_t * panel)
{
    uint32_t csi_in_channel = CSI_TO_MEM_CH0;
    ipu_idmac_info_t idmac_info;

    /*step1: config the csi: idma channel (csi -- mem), smfc, csi */

    /*setup idma background channel from MEM to display
       channel: 23
     */
    memset(&idmac_info, 0, sizeof(ipu_idmac_info_t));
    idmac_info.channel = csi_in_channel;
    idmac_info.addr0 = CH23_EBA0;
    idmac_info.addr1 = CH23_EBA1;
    idmac_info.width = csi_width;
    idmac_info.height = csi_height;
    idmac_info.pixel_format = PARTIAL_INTERLEAVED_YUV420;
    idmac_info.sl = panel->width;
    idmac_info.u_offset = panel->width * panel->height;
    idmac_info.npb = 15;
    ipu_general_idmac_config(ipu_index, &idmac_info);

    /*step2: allocate smfc fifo for CSI input channel */
    ipu_smfc_fifo_allocate(ipu_index, 0, 0, 3);

    /*step3: config csi for IPU */
    ipu_csi_config(ipu_index, CSI_MIPI, csi_width, csi_height, csi_width, csi_height);

    /*step4: config display channel: idma, dmfc, dc, dp, di */
    ipu_display_setup(ipu_index, CH23_EBA0, CH23_EBA1, PARTIAL_INTERLEAVED_YUV420, panel);

    /*step5: link csi and display */
    ipu_capture_disp_link(ipu_index, 0);

    /*step6: paint the other display area to white. */
    memset((void *)CH23_EBA0, 0xFF, 2 * panel->width * panel->height);
    memset((void *)(CH23_EBA0 + panel->width * panel->height), 0x80,
           panel->width * panel->height / 2);
    memset((void *)CH23_EBA1, 0xFF, 2 * panel->width * panel->height);
    memset((void *)(CH23_EBA1 + panel->width * panel->height), 0x80,
           panel->width * panel->height / 2);
}

void ipu1_ch0_eobnd_isr(void)
{
    static int i = 0;
    static int frame = 0;
    int frame_width = 1024;
    int cap_height = 480; 
    int band_height = 128; // must match with DMA settings
    int band_num = (cap_height + band_height - 1) / band_height;

    ipu_write_field(1, IPU_IPU_INT_STAT_11__IDMAC_EOBND_0, 1); // clear interrupt state
    
    // copy out the data before it was overwritten, data in YUV444 format
    if(i%band_num != band_num - 1)
        memcpy((void *)(CH27_EBA0 + frame_width*band_height*2*(i%band_num)), (void *)CH23_EBA0, frame_width*band_height*2);
    else
        memcpy((void *)(CH27_EBA0 + frame_width*band_height*2*(i%band_num)), (void *)CH23_EBA0, frame_width*(cap_height - band_height*(band_num-1))*2);

    if((ipu_read(1, IPU_IPU_INT_STAT_1__ADDR) & 0x1) == 1) // clear interrupt state
    {
        ipu_write_field(1, IPU_IPU_INT_STAT_1__IDMAC_EOF_0, 1);
        frame ++;
    }
    
    i++;
}

void ipu_ch0_eobnd_interrupt_register(int ipu_index)
{
    int irq_id = IPU1_SYNC + (ipu_index - 1) * 2;

    // register the IRQ routine
    register_interrupt_routine(irq_id, &ipu1_ch0_eobnd_isr);

    memset((void *)CH27_EBA0, 0xFF, 1024*768*2);
    memset((void *)CH23_EBA0, 0xFF, 1024*768*2);

    // enable interrupt
    ipu_write_field(ipu_index, IPU_IPU_INT_CTRL_1__IDMAC_EOF_EN_0, 1); // enable band mode
    ipu_write_field(ipu_index, IPU_IPU_INT_CTRL_11__IDMAC_EOBND_EN_0, 1); // enable band mode
    enable_interrupt(irq_id, CPU_0, 0);
}

