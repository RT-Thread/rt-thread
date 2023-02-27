/**
  **************************************************************************
  * @file     usbh_int.c
  * @brief    usb host interrupt request
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
#include "usbh_int.h"

#ifdef USE_OTG_HOST_MODE

/** @defgroup USBH_drivers_interrupt
  * @brief usb host interrupt
  * @{
  */

/** @defgroup USBH_int_private_functions
  * @{
  */

/**
  * @brief  usb host interrupt handler
  * @param  otgdev: to the structure of otg_core_type
  * @retval none
  */
void usbh_irq_handler(otg_core_type *otgdev)
{
  otg_global_type *usbx = otgdev->usb_reg;
  usbh_core_type *uhost = &otgdev->host;
  uint32_t intsts = usb_global_get_all_interrupt(usbx);

  if(usbx->gintsts_bit.curmode == 1)
  {
    if(intsts & USB_OTG_HCH_FLAG)
    {
      usbh_hch_handler(uhost);
      usb_global_clear_interrupt(usbx, USB_OTG_HCH_FLAG);
    }
    if(intsts & USB_OTG_SOF_FLAG)
    {
      usbh_sof_handler(uhost);
      usb_global_clear_interrupt(usbx, USB_OTG_SOF_FLAG);
    }
    if(intsts & USB_OTG_MODEMIS_FLAG)
    {
      usb_global_clear_interrupt(usbx, USB_OTG_MODEMIS_FLAG);
    }
    if(intsts & USB_OTG_WKUP_FLAG)
    {
      usbh_wakeup_handler(uhost);
      usb_global_clear_interrupt(usbx, USB_OTG_WKUP_FLAG);
    }
    while(usbx->gintsts & USB_OTG_RXFLVL_FLAG)
    {
      usbh_rx_qlvl_handler(uhost);
      usb_global_clear_interrupt(usbx, USB_OTG_RXFLVL_FLAG);
    }
    if(intsts & USB_OTG_DISCON_FLAG)
    {
      usbh_disconnect_handler(uhost);
      usb_global_clear_interrupt(usbx, USB_OTG_DISCON_FLAG);
    }
    if(intsts & USB_OTG_PRT_FLAG)
    {
      usbh_port_handler(uhost);
    }
    if(intsts & USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG)
    {
      usb_global_clear_interrupt(usbx, USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG);
    }
    if(intsts & USB_OTG_INCOMISOIN_FLAG)
    {
      usb_global_clear_interrupt(usbx, USB_OTG_INCOMISOIN_FLAG);
    }
    if(intsts & USB_OTG_PTXFEMP_FLAG)
    {
      usb_global_clear_interrupt(usbx, USB_OTG_PTXFEMP_FLAG);
    }
    if(intsts & USB_OTG_ISOOUTDROP_FLAG)
    {
      usb_global_clear_interrupt(usbx, USB_OTG_ISOOUTDROP_FLAG);
    }

  }
}

/**
  * @brief  usb host wakeup handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_wakeup_handler(usbh_core_type *uhost)
{
  uhost->global_state = USBH_WAKEUP;
}

/**
  * @brief  usb host sof handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_sof_handler(usbh_core_type *uhost)
{
  uhost->timer ++;
}

/**
  * @brief  usb host disconnect handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_disconnect_handler(usbh_core_type *uhost)
{
  otg_global_type *usbx = uhost->usb_reg;

  uint8_t i_index;

  usb_host_disable(usbx);

  uhost->conn_sts = 0;

  uhost->global_state = USBH_DISCONNECT;

  for(i_index = 0; i_index < USB_HOST_CHANNEL_NUM; i_index ++)
  {
    usbh_free_channel(uhost, i_index);
  }
  usbh_fsls_clksel(usbx, USB_HCFG_CLK_48M);

  usbh_disconnect_callback(uhost);
}

/**
  * @brief  usb host in transfer request handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  chn: channel number
  * @retval none
  */
void usbh_hch_in_handler(usbh_core_type *uhost, uint8_t chn)
{
  otg_global_type *usbx = uhost->usb_reg;
  otg_hchannel_type *usb_chh = USB_CHL(usbx, chn);
  uint32_t hcint_value = usb_chh->hcint & usb_chh->hcintmsk;

  if( hcint_value & USB_OTG_HC_ACK_FLAG)
  {
    usb_chh->hcint = USB_OTG_HC_ACK_FLAG;
  }
  else if(hcint_value & USB_OTG_HC_STALL_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_chh->hcint = USB_OTG_HC_NAK_FLAG | USB_OTG_HC_STALL_FLAG;
    uhost->hch[chn].state = HCH_STALL;
    usb_hch_halt(usbx, chn);
  }
  else if(hcint_value & USB_OTG_HC_DTGLERR_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_hch_halt(usbx, chn);
    usb_chh->hcint = USB_OTG_HC_DTGLERR_FLAG | USB_OTG_HC_NAK_FLAG;
    uhost->hch[chn].state = HCH_DATATGLERR;
  }

  else if(hcint_value & USB_OTG_HC_FRMOVRRUN_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_hch_halt(usbx, chn);
    usb_chh->hcint = USB_OTG_HC_FRMOVRRUN_FLAG;
  }
  else if(hcint_value & USB_OTG_HC_XFERC_FLAG)
  {
    uhost->hch[chn].state = HCH_XFRC;
    usb_chh->hcint = USB_OTG_HC_XFERC_FLAG;

    if(usb_chh->hcchar_bit.eptype == EPT_BULK_TYPE || usb_chh->hcchar_bit.eptype == EPT_CONTROL_TYPE)
    {
      usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
      usb_hch_halt(usbx, chn);
      usb_chh->hcint = USB_OTG_HC_NAK_FLAG;
    }
    else if(usb_chh->hcchar_bit.eptype == EPT_INT_TYPE)
    {
      usb_chh->hcchar_bit.oddfrm = TRUE;
      uhost->urb_state[chn] = URB_DONE;

      usbd_notify_urbchange_callback(uhost, chn, uhost->urb_state[chn]);
    }
    else if(usb_chh->hcchar_bit.eptype == EPT_ISO_TYPE)
    {
      uhost->urb_state[chn] = URB_DONE;
      usbd_notify_urbchange_callback(uhost, chn, uhost->urb_state[chn]);
    }
    uhost->hch[chn].toggle_in ^= 1;
  }
  else if(hcint_value & USB_OTG_HC_CHHLTD_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = FALSE;
    if(uhost->hch[chn].state == HCH_XFRC )
    {
      uhost->urb_state[chn]  = URB_DONE;
    }
    else if(uhost->hch[chn].state == HCH_STALL)
    {
      uhost->urb_state[chn]  = URB_STALL;
    }
    else if(uhost->hch[chn].state == HCH_XACTERR ||
            uhost->hch[chn].state == HCH_DATATGLERR)
    {
      uhost->err_cnt[chn] ++;
      if(uhost->err_cnt[chn] > 3)
      {
        uhost->urb_state[chn] = URB_ERROR;
        uhost->err_cnt[chn] = 0;
      }
      else
      {
        uhost->urb_state[chn] = URB_NOTREADY;
      }
      usb_chh->hcchar_bit.chdis = FALSE;
      usb_chh->hcchar_bit.chena = TRUE;
    }
    else if(uhost->hch[chn].state == HCH_NAK)
    {
      usb_chh->hcchar_bit.chdis = FALSE;
      usb_chh->hcchar_bit.chena = TRUE;
      uhost->urb_state[chn] = URB_NOTREADY;
    }
    usb_chh->hcint = USB_OTG_HC_CHHLTD_FLAG;
    usbd_notify_urbchange_callback(uhost, chn, uhost->urb_state[chn]);
  }
  else if(hcint_value & USB_OTG_HC_XACTERR_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    uhost->hch[chn].state = HCH_XACTERR;
    usb_hch_halt(usbx, chn);
    uhost->err_cnt[chn] ++;
    usb_chh->hcint = USB_OTG_HC_XACTERR_FLAG;
  }
  else if(hcint_value & USB_OTG_HC_NAK_FLAG)
  {
    if(usb_chh->hcchar_bit.eptype == EPT_INT_TYPE)
    {
      uhost->err_cnt[chn] = 0;
      usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
      usb_hch_halt(usbx, chn);
    }
    else if(usb_chh->hcchar_bit.eptype == EPT_BULK_TYPE ||
      usb_chh->hcchar_bit.eptype == EPT_CONTROL_TYPE)
    {
      uhost->err_cnt[chn] = 0;
      usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
      usb_hch_halt(usbx, chn);
    }
    uhost->hch[chn].state = HCH_NAK;
    usb_chh->hcint = USB_OTG_HC_NAK_FLAG;
  }
  else if(hcint_value & USB_OTG_HC_BBLERR_FLAG)
  {
    usb_chh->hcint = USB_OTG_HC_BBLERR_FLAG;
  }
}

/**
  * @brief  usb host out transfer request handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  chn: channel number
  * @retval none
  */
void usbh_hch_out_handler(usbh_core_type *uhost, uint8_t chn)
{
  otg_global_type *usbx = uhost->usb_reg;
  otg_hchannel_type *usb_chh = USB_CHL(usbx, chn);
  uint32_t hcint_value = usb_chh->hcint & usb_chh->hcintmsk;

  if( hcint_value & USB_OTG_HC_ACK_FLAG)
  {
    usb_chh->hcint = USB_OTG_HC_ACK_FLAG;
  }
  else if( hcint_value & USB_OTG_HC_FRMOVRRUN_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_hch_halt(usbx, chn);
    usb_chh->hcint = USB_OTG_HC_FRMOVRRUN_FLAG;
  }
  else if( hcint_value & USB_OTG_HC_XFERC_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_hch_halt(usbx, chn);
    uhost->hch[chn].state = HCH_XFRC;
    usb_chh->hcint = USB_OTG_HC_XFERC_FLAG;
  }
  else if( hcint_value & USB_OTG_HC_STALL_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_chh->hcint =  USB_OTG_HC_STALL_FLAG;
    uhost->hch[chn].state = HCH_STALL;
    usb_hch_halt(usbx, chn);
  }
  else if( hcint_value & USB_OTG_HC_DTGLERR_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    usb_hch_halt(usbx, chn);
    usb_chh->hcint = USB_OTG_HC_DTGLERR_FLAG | USB_OTG_HC_NAK_FLAG;
    uhost->hch[chn].state = HCH_DATATGLERR;
  }
  else if( hcint_value & USB_OTG_HC_CHHLTD_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = FALSE;
    if(uhost->hch[chn].state == HCH_XFRC)
    {
      uhost->urb_state[chn] = URB_DONE;
      if(uhost->hch[chn].ept_type == EPT_BULK_TYPE ||
        uhost->hch[chn].ept_type == EPT_INT_TYPE)
      {
        uhost->hch[chn].toggle_out ^= 1;
      }
    }
    else if(uhost->hch[chn].state == HCH_NAK)
    {
      uhost->urb_state[chn] = URB_NOTREADY;
    }
    else if(uhost->hch[chn].state == HCH_STALL)
    {
      uhost->hch[chn].urb_sts = URB_STALL;
    }
    else if(uhost->hch[chn].state == HCH_XACTERR ||
            uhost->hch[chn].state == HCH_DATATGLERR)
    {
      uhost->err_cnt[chn] ++;
      if(uhost->err_cnt[chn] > 3)
      {
        uhost->urb_state[chn] = URB_ERROR;
        uhost->err_cnt[chn] = 0;
        usbd_notify_urbchange_callback(uhost, chn, uhost->urb_state[chn]);
      }
      else
      {
        uhost->urb_state[chn] = URB_NOTREADY;
      }

      usb_chh->hcchar_bit.chdis = FALSE;
      usb_chh->hcchar_bit.chena = TRUE;
    }
    usb_chh->hcint = USB_OTG_HC_CHHLTD_FLAG;
    usbd_notify_urbchange_callback(uhost, chn, uhost->urb_state[chn]);
  }
  else if( hcint_value & USB_OTG_HC_XACTERR_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    uhost->err_cnt[chn] ++;
    uhost->hch[chn].state = HCH_XACTERR;
    usb_hch_halt(usbx, chn);
    usb_chh->hcint = USB_OTG_HC_XACTERR_FLAG | USB_OTG_HC_NAK_FLAG;
  }
  else if( hcint_value & USB_OTG_HC_NAK_FLAG)
  {
    usb_chh->hcintmsk_bit.chhltdmsk = TRUE;
    uhost->err_cnt[chn] = 0;
    usb_hch_halt(usbx, chn);
    uhost->hch[chn].state = HCH_NAK;
    usb_chh->hcint = USB_OTG_HC_NAK_FLAG;
  }
}

/**
  * @brief  usb host channel request handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_hch_handler(usbh_core_type *uhost)
{
  otg_global_type *usbx = uhost->usb_reg;
  otg_host_type *usb_host = OTG_HOST(usbx);
  uint32_t intsts, i_index;

  intsts = usb_host->haint & 0xFFFF;
  for(i_index = 0; i_index < 16; i_index ++)
  {
    if(intsts & (1 << i_index))
    {
      if(USB_CHL(usbx, i_index)->hcchar_bit.eptdir)
      {
        //hc in
        usbh_hch_in_handler(uhost, i_index);
      }
      else
      {
        //hc out
        usbh_hch_out_handler(uhost, i_index);
      }
    }
  }
}

/**
  * @brief  usb host rx buffer not empty request handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_rx_qlvl_handler(usbh_core_type *uhost)
{
  uint8_t chn;
  uint32_t pktsts;
  uint32_t pktcnt;
  uint32_t tmp;
  otg_hchannel_type *ch;
  otg_global_type *usbx = uhost->usb_reg;

  usbx->gintmsk_bit.rxflvlmsk = 0;

  tmp = usbx->grxstsp;
  chn = tmp & 0xF;
  pktsts = (tmp >> 17) & 0xF;
  pktcnt = (tmp >> 4) & 0x7FF;
  ch = USB_CHL(usbx, chn);
  switch(pktsts)
  {
    case PKTSTS_IN_DATA_PACKET_RECV:
      if(pktcnt > 0 && (uhost->hch[chn].trans_buf) != 0)
      {
        usb_read_packet(usbx, uhost->hch[chn].trans_buf, chn, pktcnt);
        uhost->hch[chn].trans_buf += pktcnt;
        uhost->hch[chn].trans_count += pktcnt;

        if(ch->hctsiz_bit.pktcnt > 0)
        {
          ch->hcchar_bit.chdis = FALSE;
          ch->hcchar_bit.chena = TRUE;
          uhost->hch[chn].toggle_in ^= 1;
        }
      }
      break;
    case PKTSTS_IN_TRANSFER_COMPLETE:
      break;
    case PKTSTS_DATA_BIT_ERROR:
      break;
    case PKTSTS_CHANNEL_STOP:
      break;
    default:
      break;

  }
  usbx->gintmsk_bit.rxflvlmsk = 1;
}

/**
  * @brief  usb host port request handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_port_handler(usbh_core_type *uhost)
{
  otg_global_type *usbx = uhost->usb_reg;
  otg_host_type *usb_host = OTG_HOST(usbx);

  uint32_t prt = 0, prt_0;

  prt = usb_host->hprt;
  prt_0 = prt;

  prt_0 &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
               USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET);
  if(prt & USB_OTG_HPRT_PRTCONDET)
  {
    if(prt & USB_OTG_HPRT_PRTCONSTS)
    {
      /* connect callback */
      uhost->conn_sts = 1;
    }

    usbh_connect_callback(uhost);
    prt_0 |= USB_OTG_HPRT_PRTCONDET;
  }

  if(prt & USB_OTG_HPRT_PRTENCHNG)
  {
    prt_0 |= USB_OTG_HPRT_PRTENCHNG;

    if(prt & USB_OTG_HPRT_PRTENA)
    {
      if((prt & USB_OTG_HPRT_PRTSPD) == (USB_PRTSPD_LOW_SPEED << 17))
      {
        usbh_fsls_clksel(usbx, USB_HCFG_CLK_6M);
      }
      else
      {
        usbh_fsls_clksel(usbx, USB_HCFG_CLK_48M);
      }
      /* connect callback */
      uhost->port_enable = 1;
    }
    else
    {
      /* clean up hprt */
      uhost->port_enable = 0;
    }
  }

  if(prt & USB_OTG_HPRT_PRTOVRCACT)
  {
    prt_0 |= USB_OTG_HPRT_PRTOVRCACT;
  }

  usb_host->hprt = prt_0;
}

rt_weak void usbh_connect_callback(usbh_core_type *uhost)
{
}

rt_weak void usbh_disconnect_callback(usbh_core_type *uhost)
{
}

rt_weak void usbd_notify_urbchange_callback(usbh_core_type *uhost, uint8_t chnum, urb_sts_type sts)
{
}

/**
  * @}
  */

/**
  * @}
  */

#endif
