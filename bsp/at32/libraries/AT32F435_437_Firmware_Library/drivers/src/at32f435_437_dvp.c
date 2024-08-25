/**
  **************************************************************************
  * @file     at32f435_437_dvp.c
  * @brief    contains all the functions for the dvp firmware library
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f435_437_conf.h"

/** @addtogroup AT32F435_437_periph_driver
  * @{
  */

/** @defgroup DVP
  * @brief DVP driver modules
  * @{
  */

#ifdef DVP_MODULE_ENABLED

/** @defgroup DVP_private_functions
  * @{
  */

/**
  * @brief  reset the dvp register
  * @param  none
  * @retval none
  */
void dvp_reset(void)
{
  crm_periph_reset(CRM_DVP_PERIPH_RESET, TRUE);
  crm_periph_reset(CRM_DVP_PERIPH_RESET, FALSE);
}

/**
  * @brief  enable or disable dvp capture
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_capture_enable(confirm_state new_state)
{
  DVP->ctrl_bit.cap = new_state;
}

/**
  * @brief  set dvp capture mode
  * @param  cap_mode
  *         this parameter can be one of the following values:
  *         - DVP_CAP_FUNC_MODE_CONTINUOUS
  *         - DVP_CAP_FUNC_MODE_SINGLE
  * @retval none
  */
void dvp_capture_mode_set(dvp_cfm_type cap_mode)
{
  DVP->ctrl_bit.cfm = cap_mode;
}

/**
  * @brief  set dvp cropping window enable
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_window_crop_enable(confirm_state new_state)
{
  DVP->ctrl_bit.crp = new_state;
}

/**
  * @brief  set dvp cropping window configuration
  * @param  crop_x: cropping window horizontal start pixel
  * @param  crop_y: cropping window vertical start line
  * @param  crop_w: cropping window horizontal pixel number
  * @param  crop_h: cropping window vertical line number
  * @param  bytes: the number of bytes corresponding to one pixel
  *         eg. y8:bytes = 1, rgb565:bytes = 2
  * @retval none
  */
void dvp_window_crop_set(uint16_t crop_x, uint16_t crop_y, uint16_t crop_w, uint16_t crop_h, uint8_t bytes)
{
  DVP->cwst = ((crop_x * bytes) | (crop_y << 16));
  DVP->cwsz = ((crop_w * bytes - 1) | ((crop_h - 1) << 16));
}

/**
  * @brief  enable or disable dvp jpeg
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_jpeg_enable(confirm_state new_state)
{
  DVP->ctrl_bit.jpeg = new_state;
}

/**
  * @brief  set dvp synchronization mode
  * @param  sync_mode
  *         this parameter can be one of the following values:
  *         - DVP_SYNC_MODE_HARDWARE
  *         - DVP_SYNC_MODE_EMBEDDED
  * @retval none
  */
void dvp_sync_mode_set(dvp_sm_type sync_mode)
{
  DVP->ctrl_bit.sm = sync_mode;
}

/**
  * @brief  set dvp synchronization code configuration
  * @param  fmsc(0x00~0xFF): frame start code
  * @param  fmec(0x00~0xFF): frame end code
  * @param  lnsc(0x00~0xFF): line start code
  * @param  lnec(0x00~0xFF): line end code
  * @retval none
  */
void dvp_sync_code_set(uint8_t fmsc, uint8_t fmec, uint8_t lnsc, uint8_t lnec)
{
  DVP->scr = (fmsc | (lnsc << 8) | (lnec << 16) | (fmec << 24));
}

/**
  * @brief  set dvp synchronization unmask configuration
  * @param  fmsu(0x00~0xFF): frame start unmask
  * @param  fmeu(0x00~0xFF): frame end unmask
  * @param  lnsu(0x00~0xFF): line start unmask
  * @param  lneu(0x00~0xFF): line end unmask
  * @retval none
  */
void dvp_sync_unmask_set(uint8_t fmsu, uint8_t fmeu, uint8_t lnsu, uint8_t lneu)
{
  DVP->sur = (fmsu | (lnsu << 8) | (lneu << 16) | (fmeu << 24));
}

/**
  * @brief  set dvp pixel clock polarity
  * @param  edge
  *         this parameter can be one of the following values:
  *         - DVP_CLK_POLARITY_RISING
  *         - DVP_CLK_POLARITY_FALLING
  * @retval none
  */
void dvp_pclk_polarity_set(dvp_ckp_type edge)
{
  DVP->ctrl_bit.ckp = edge;
}

/**
  * @brief  set dvp horizontal synchronization polarity
  * @param  hsync_pol
  *         this parameter can be one of the following values:
  *         - DVP_HSYNC_POLARITY_HIGH
  *         - DVP_HSYNC_POLARITY_LOW
  * @retval none
  */
void dvp_hsync_polarity_set(dvp_hsp_type hsync_pol)
{
  DVP->ctrl_bit.hsp = hsync_pol;
}

/**
  * @brief  set dvp vertical synchronization polarity
  * @param  vsync_pol
  *         this parameter can be one of the following values:
  *         - DVP_VSYNC_POLARITY_LOW
  *         - DVP_VSYNC_POLARITY_HIGH
  * @retval none
  */
void dvp_vsync_polarity_set(dvp_vsp_type vsync_pol)
{
  DVP->ctrl_bit.vsp = vsync_pol;
}

/**
  * @brief  config dvp basic frame rate control
  * @note   this function only work in continuous fire mode(ctrl_bit.cfm = 0)
  * @param  dvp_bfrc
  *         this parameter can be one of the following values:
  *         - DVP_BFRC_ALL
  *         - DVP_BFRC_HALF
  *         - DVP_BFRC_QUARTER
  * @retval none
  */
void dvp_basic_frame_rate_control_set(dvp_bfrc_type dvp_bfrc)
{
  DVP->ctrl_bit.bfrc = dvp_bfrc;
}

/**
  * @brief  config dvp pixel data length
  * @param  dvp_pdl
  *         this parameter can be one of the following values:
  *         - DVP_PIXEL_DATA_LENGTH_8
  *         - DVP_PIXEL_DATA_LENGTH_10
  *         - DVP_PIXEL_DATA_LENGTH_12
  *         - DVP_PIXEL_DATA_LENGTH_14
  * @retval none
  */
void dvp_pixel_data_length_set(dvp_pdl_type dvp_pdl)
{
  DVP->ctrl_bit.pdl = dvp_pdl;
}

/**
  * @brief  enable or disable dvp function
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_enable(confirm_state new_state)
{
  DVP->ctrl_bit.ena = new_state;
}

/**
  * @brief  set dvp zoomout select
  * @param  dvp_pcdes: pixel capture/drop selection extension (Only work when pcdc = 2)
  *         this parameter can be one of the following values:
  *         - DVP_PCDES_CAP_FIRST
  *         - DVP_PCDES_DROP_FIRST
  * @retval none
  */
void dvp_zoomout_select(dvp_pcdes_type dvp_pcdes)
{
  DVP->actrl_bit.pcdes = dvp_pcdes;
}

/**
  * @brief  set dvp zoomout configuration
  * @param  dvp_pcdc: basic pixel capture/drop control
  *         this parameter can be one of the following values:
  *         - DVP_PCDC_ALL
  *         - DVP_PCDC_ONE_IN_TWO
  *         - DVP_PCDC_ONE_IN_FOUR
  *         - DVP_PCDC_TWO_IN_FOUR
  * @param  dvp_pcds: pixel capture/drop selection
  *         this parameter can be one of the following values:
  *         - DVP_PCDS_CAP_FIRST
  *         - DVP_PCDS_DROP_FIRST
  * @param  dvp_lcdc: line capture/drop control
  *         this parameter can be one of the following values:
  *         - DVP_LCDC_ALL
  *         - DVP_LCDC_ONE_IN_TWO
  * @param  dvp_lcds: line capture/drop selection
  *         this parameter can be one of the following values:
  *         - DVP_LCDS_CAP_FIRST
  *         - DVP_LCDS_DROP_FIRST
  * @retval none
  */
void dvp_zoomout_set(dvp_pcdc_type dvp_pcdc, dvp_pcds_type dvp_pcds, dvp_lcdc_type dvp_lcdc, dvp_lcds_type dvp_lcds)
{
  DVP->ctrl_bit.pcdc = dvp_pcdc;
  DVP->ctrl_bit.pcds = dvp_pcds;
  DVP->ctrl_bit.lcdc = dvp_lcdc;
  DVP->ctrl_bit.lcds = dvp_lcds;
}

/**
  * @brief  get dvp basic status
  * @param  dvp_status_basic_type:
  *         this parameter can be one of the following values:
  *         - DVP_STATUS_HSYN
  *         - DVP_STATUS_VSYN
  *         - DVP_STATUS_OFNE
  * @retval flag_status (SET or RESET)
  */
flag_status dvp_basic_status_get(dvp_status_basic_type dvp_status_basic)
{
  flag_status status = RESET;

  if ((DVP->sts & (0x1 << dvp_status_basic)) != (uint16_t)RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  enable or disable dvp interrupt
  * @param  dvp_int:
  *         this parameter can be any combination of the following values:
  *         - DVP_CFD_INT
  *         - DVP_OVR_INT
  *         - DVP_ESE_INT
  *         - DVP_VS_INT
  *         - DVP_HS_INT
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_interrupt_enable(uint32_t dvp_int, confirm_state new_state)
{
  if(new_state == TRUE)
  {
    DVP->ier |= dvp_int;
  }
  else
  {
    DVP->ier &= ~dvp_int;
  }
}

/**
  * @brief  get dvp interrupt flag status
  * @param  flag
  *         this parameter can be one of the following values:
  *         - DVP_CFD_INT_FLAG
  *         - DVP_OVR_INT_FLAG
  *         - DVP_ESE_INT_FLAG
  *         - DVP_VS_INT_FLAG
  *         - DVP_HS_INT_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status dvp_interrupt_flag_get(uint32_t flag)
{
  flag_status status = RESET;

  if((DVP->ists & flag) != RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  get dvp event flag status
  * @param  flag
  *         this parameter can be one of the following values:
  *         - DVP_CFD_EVT_FLAG
  *         - DVP_OVR_EVT_FLAG
  *         - DVP_ESE_EVT_FLAG
  *         - DVP_VS_EVT_FLAG
  *         - DVP_HS_EVT_FLAG
  * @retval flag_status (SET or RESET)
  */
flag_status dvp_flag_get(uint32_t flag)
{
  flag_status status = RESET;
  flag &= ~0x80000000;

  if((DVP->ests & flag) != RESET)
  {
    status = SET;
  }
  else
  {
    status = RESET;
  }

  return status;
}

/**
  * @brief  clear dvp's pending flags
  * @param  flag
  *         this parameter can be one of the following values:
  *         event flag:
  *         - DVP_CFD_EVT_FLAG
  *         - DVP_OVR_EVT_FLAG
  *         - DVP_ESE_EVT_FLAG
  *         - DVP_VS_EVT_FLAG
  *         - DVP_HS_EVT_FLAG
  *         interrupt flag:
  *         - DVP_CFD_INT_FLAG
  *         - DVP_OVR_INT_FLAG
  *         - DVP_ESE_INT_FLAG
  *         - DVP_VS_INT_FLAG
  *         - DVP_HS_INT_FLAG
  * @retval none
  */
void dvp_flag_clear(uint32_t flag)
{
  flag &= ~0x80000000;
  DVP->iclr = flag;
}

/**
  * @brief  set dvp enhanced image scaling resize enable
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_enhanced_scaling_resize_enable(confirm_state new_state)
{
  DVP->actrl_bit.eisre = new_state;
}
/**
  * @brief  set dvp enhanced image scaling resize configuration
  * @param  src_w(0x0001~0x1FFF): horizontal scaling resize source size (source image width)
  * @param  des_w(0x0001~0x1FFF): horizontal scaling resize target size (target image width)
  * @param  src_h(0x0001~0x1FFF): vertical scaling resize source size (source image height)
  * @param  des_h(0x0001~0x1FFF): vertical scaling resize target size (target image height)
  * @retval none
  */
void dvp_enhanced_scaling_resize_set(uint16_t src_w, uint16_t des_w, uint16_t src_h, uint16_t des_h)
{
  if((!DVP->ctrl_bit.pcdc) && (!DVP->ctrl_bit.lcdc) && DVP->actrl_bit.efdf)
  {
    DVP->hscf = (src_w | (des_w << 16));
    DVP->vscf = (src_h | (des_h << 16));
  }
}

/**
  * @brief  set enhanced frame rate control configuration
  * @param  efrcsf(0x00~0x1F): original frame rate contorl factor
  * @param  efrctf(0x00~0x1F): enhanced frame rate contorl factor
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void dvp_enhanced_framerate_set(uint16_t efrcsf, uint16_t efrctf, confirm_state new_state)
{
  if((!DVP->ctrl_bit.cfm) && (!DVP->ctrl_bit.bfrc) && (efrctf <= efrcsf))
  {
    DVP->frf = (efrcsf | (efrctf << 8));
  }

  DVP->actrl_bit.efrce = new_state;
}

/**
  * @brief  set dvp monochrome image binarization configuration
  * @param  mibthd(0x00~0xFF): monochrome image binarization threshold
  * @param  new_state: (TRUE or FALSE)
  * @retval none
  */
void dvp_monochrome_image_binarization_set(uint8_t mibthd, confirm_state new_state)
{
  DVP->bth_bit.mibthd = mibthd;
  DVP->actrl_bit.mibe = new_state;
}

/**
  * @brief  set dvp enhanced function data format configuration
  * @param  dvp_efdf: enhanced function data format
  *         this parameter can be one of the following values:
  *         - DVP_EFDF_BYPASS
  *         - DVP_EFDF_YUV422_UYVY
  *         - DVP_EFDF_YUV422_YUYV
  *         - DVP_EFDF_RGB565_555
  *         - DVP_EFDF_Y8
  * @retval none
  */
void dvp_enhanced_data_format_set(dvp_efdf_type dvp_efdf)
{
  DVP->actrl_bit.efdf = dvp_efdf;
}

/**
  * @brief  set dvp input data un-used condition/number configuration
  * @param  dvp_idus: input data un-used condition
  *         this parameter can be one of the following values:
  *         - DVP_IDUS_MSB
  *         - DVP_IDUS_LSB
  * @param  dvp_idun: input data un-used number
  *         this parameter can be one of the following values:
  *         - DVP_IDUN_0
  *         - DVP_IDUN_2
  *         - DVP_IDUN_4
  *         - DVP_IDUN_6
  * @retval none
  */
void dvp_input_data_unused_set(dvp_idus_type dvp_idus, dvp_idun_type dvp_idun)
{
  DVP->actrl_bit.idus = dvp_idus;
  DVP->actrl_bit.idun = dvp_idun;
}

/**
  * @brief  set dvp dma burst transfer configuration
  * @param  dvp_dmabt: dma burst transfer configuration
  *         this parameter can be one of the following values:
  *         - DVP_DMABT_SINGLE
  *         - DVP_DMABT_BURST
  * @retval none
  */
void dvp_dma_burst_set(dvp_dmabt_type dvp_dmabt)
{
  DVP->actrl_bit.dmabt = dvp_dmabt;
}

/**
  * @brief  set dvp hsync/vsync event interrupt strategy configuration
  * @param  dvp_hseid: hsync event interrupt strategy
  *         this parameter can be one of the following values:
  *         - DVP_HSEID_LINE_END
  *         - DVP_HSEID_LINE_START
  * @param  dvp_vseid: vsync event interrupt strategy
  *         this parameter can be one of the following values:
  *         - DVP_VSEID_FRAME_END
  *         - DVP_VSEID_FRMAE_START
  * @retval none
  */
void dvp_sync_event_interrupt_set(dvp_hseid_type dvp_hseid, dvp_vseid_type dvp_vseid)
{
  DVP->actrl_bit.hseid = dvp_hseid;
  DVP->actrl_bit.vseid = dvp_vseid;
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */
