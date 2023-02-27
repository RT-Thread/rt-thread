/**
  **************************************************************************
  * @file     usbd_core.c
  * @brief    usb device driver
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

#include "usb_core.h"
#include "usbd_core.h"
#include "usbd_sdr.h"

/** @defgroup USBD_drivers_core
  * @brief usb device drivers core
  * @{
  */

/** @defgroup USBD_core_private_functions
  * @{
  */

#ifdef USE_OTG_DEVICE_MODE

/**
  * @brief  usb core in transfer complete handler
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval none
  */
void usbd_core_in_handler(usbd_core_type *udev, uint8_t ept_addr)
{
  /* get endpoint info*/
  usb_ept_info *ept_info = &udev->ept_in[ept_addr & 0x7F];

  if(ept_addr == 0)
  {
    if(udev->ept0_sts == USB_EPT0_DATA_IN)
    {
      if(ept_info->rem0_len > ept_info->maxpacket)
      {
        ept_info->rem0_len -= ept_info->maxpacket;
        usbd_ept_send(udev, 0, ept_info->trans_buf,
                      MIN(ept_info->rem0_len, ept_info->maxpacket));
      }
      /* endpoint 0 */
      else if(ept_info->last_len == ept_info->maxpacket
        && ept_info->ept0_slen >= ept_info->maxpacket
        && ept_info->ept0_slen < udev->ept0_wlength)
      {
        ept_info->last_len = 0;
        usbd_ept_send(udev, 0, 0, 0);
        usbd_ept_recv(udev, ept_addr, 0, 0);
      }
      else
      {

        if(udev->class_handler->ept0_tx_handler != 0 &&
            udev->conn_state == USB_CONN_STATE_CONFIGURED)
        {
          udev->class_handler->ept0_tx_handler(udev);
        }
        usbd_ctrl_recv_status(udev);

      }
    }
  }
  else if(udev->class_handler->in_handler != 0 &&
          udev->conn_state == USB_CONN_STATE_CONFIGURED)
  {
    /* other user define endpoint */
    udev->class_handler->in_handler(udev, ept_addr);
  }
}

/**
  * @brief  usb core out transfer complete handler
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval none
  */
void usbd_core_out_handler(usbd_core_type *udev, uint8_t ept_addr)
{
   /* get endpoint info*/
  usb_ept_info *ept_info = &udev->ept_out[ept_addr & 0x7F];

  if(ept_addr == 0)
  {
    /* endpoint 0 */
    if(udev->ept0_sts == USB_EPT0_DATA_OUT)
    {
      if(ept_info->rem0_len > ept_info->maxpacket)
      {
        ept_info->rem0_len -= ept_info->maxpacket;
        usbd_ept_recv(udev, ept_addr, ept_info->trans_buf,
                      MIN(ept_info->rem0_len, ept_info->maxpacket));
      }
      else
      {
          if(udev->class_handler->ept0_rx_handler != 0)
          {
            udev->class_handler->ept0_rx_handler(udev);
          }
          usbd_ctrl_send_status(udev);
      }
    }
  }
  else if(udev->class_handler->out_handler != 0 &&
          udev->conn_state == USB_CONN_STATE_CONFIGURED)
  {
    /* other user define endpoint */
    udev->class_handler->out_handler(udev, ept_addr);
  }
}

/**
  * @brief  usb core setup transfer complete handler
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval none
  */
void usbd_core_setup_handler(usbd_core_type *udev, uint8_t ept_num)
{
  /* setup parse */
  usbd_setup_request_parse(&udev->setup, udev->setup_buffer);

  /* set ept0 status */
  udev->ept0_sts = USB_EPT0_SETUP;
  udev->ept0_wlength = udev->setup.wLength;

  switch(udev->setup.bmRequestType & USB_REQ_RECIPIENT_MASK)
  {
    case USB_REQ_RECIPIENT_DEVICE:
      /* recipient device request */
      usbd_device_request(udev);
      break;
    case USB_REQ_RECIPIENT_INTERFACE:
      /* recipient interface request */
      usbd_interface_request(udev);
      break;
    case USB_REQ_RECIPIENT_ENDPOINT:
      /* recipient endpoint request */
      usbd_endpoint_request(udev);
      break;
    default:
      break;
  }
}

/**
  * @brief  usb control endpoint send data
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @param  buffer: send data buffer
  * @param  len: send data length
  * @retval none
  */
void usbd_ctrl_send(usbd_core_type *udev, uint8_t *buffer, uint16_t len)
{
  usb_ept_info *ept_info = &udev->ept_in[0];

  ept_info->ept0_slen = len;
  ept_info->rem0_len = len;
  udev->ept0_sts = USB_EPT0_DATA_IN;

  usbd_ept_send(udev, 0, buffer, len);
}

/**
  * @brief  usb control endpoint recv data
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @param  buffer: recv data buffer
  * @param  len: recv data length
  * @retval none
  */
void usbd_ctrl_recv(usbd_core_type *udev, uint8_t *buffer, uint16_t len)
{
  usb_ept_info *ept_info = &udev->ept_out[0];

  ept_info->ept0_slen = len;
  ept_info->rem0_len = len;
  udev->ept0_sts = USB_EPT0_DATA_OUT;

  usbd_ept_recv(udev, 0, buffer, len);
}

/**
  * @brief  usb control endpoint send in status
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_ctrl_send_status(usbd_core_type *udev)
{
  udev->ept0_sts = USB_EPT0_STATUS_IN;

  usbd_ept_send(udev, 0, 0, 0);
}

/**
  * @brief  usb control endpoint send out status
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_ctrl_recv_status(usbd_core_type *udev)
{
  udev->ept0_sts = USB_EPT0_STATUS_OUT;

  usbd_ept_recv(udev, 0, 0, 0);
}

/**
  * @brief  clear endpoint stall
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval none
  */
void usbd_clear_stall(usbd_core_type *udev, uint8_t ept_addr)
{
  usb_ept_info *ept_info;
  usb_reg_type *usbx = udev->usb_reg;

  if(ept_addr & 0x80)
  {
    /* in endpoint */
    ept_info = &udev->ept_in[ept_addr & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &udev->ept_out[ept_addr & 0x7F];
  }
  usb_ept_clear_stall(usbx, ept_info);
  ept_info->stall = 0;
}

/**
  * @brief  usb set endpoint to stall status
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval none
  */
void usbd_set_stall(usbd_core_type *udev, uint8_t ept_addr)
{
  usb_ept_info *ept_info;
  usb_reg_type *usbx = udev->usb_reg;

  if(ept_addr & 0x80)
  {
    /* in endpoint */
    ept_info = &udev->ept_in[ept_addr & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &udev->ept_out[ept_addr & 0x7F];
  }
  usb_ept_stall(usbx, ept_info);

  ept_info->stall = 1;
}

/**
  * @brief  un-support device request
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_ctrl_unsupport(usbd_core_type *udev)
{
  /* return stall status */
  usbd_set_stall(udev, 0x00);
  usbd_set_stall(udev, 0x80);
}

/**
  * @brief  get endpoint receive data length
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval data receive len
  */
uint32_t usbd_get_recv_len(usbd_core_type *udev, uint8_t ept_addr)
{
  usb_ept_info *ept = &udev->ept_out[ept_addr & 0x7F];
  return ept->trans_len;
}

/**
  * @brief  usb open endpoint
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @param  ept_type: endpoint type
  * @param  maxpacket: endpoint support max buffer size
  * @retval none
  */
void usbd_ept_open(usbd_core_type *udev, uint8_t ept_addr, uint8_t ept_type, uint16_t maxpacket)
{
  usb_reg_type *usbx = udev->usb_reg;
  usb_ept_info *ept_info;

  if((ept_addr & 0x80) == 0)
  {
    /* out endpoint info */
    ept_info = &udev->ept_out[ept_addr & 0x7F];
    ept_info->inout = EPT_DIR_OUT;
  }
  else
  {
    /* in endpoint info */
    ept_info = &udev->ept_in[ept_addr & 0x7F];
    ept_info->inout = EPT_DIR_IN;
  }

  /* set endpoint maxpacket and type */
  ept_info->maxpacket = maxpacket;
  ept_info->trans_type = ept_type;

  /* open endpoint */
  usb_ept_open(usbx, ept_info);
}

/**
  * @brief  usb close endpoint
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @retval none
  */
void usbd_ept_close(usbd_core_type *udev, uint8_t ept_addr)
{
  usb_ept_info *ept_info;
  if(ept_addr & 0x80)
  {
    /* in endpoint */
    ept_info = &udev->ept_in[ept_addr & 0x7F];
  }
  else
  {
    /* out endpoint */
    ept_info = &udev->ept_out[ept_addr & 0x7F];
  }

  /* close endpoint */
  usb_ept_close(udev->usb_reg, ept_info);
}

/**
  * @brief  usb device connect to host
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_connect(usbd_core_type *udev)
{
  usb_connect(udev->usb_reg);
}

/**
  * @brief  usb device disconnect to host
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_disconnect(usbd_core_type *udev)
{
  usb_disconnect(udev->usb_reg);
}

/**
  * @brief  usb device set device address.
  * @param  udev: to the structure of usbd_core_type
  * @param  address: host assignment address
  * @retval none
  */
void usbd_set_device_addr(usbd_core_type *udev, uint8_t address)
{
  usb_set_address(udev->usb_reg, address);
}

/**
  * @brief  usb endpoint structure initialization
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usb_ept_default_init(usbd_core_type *udev)
{
  uint8_t i_index = 0;
  /* init in endpoint info structure */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    udev->ept_in[i_index].eptn        = i_index;
    udev->ept_in[i_index].ept_address = i_index;
    udev->ept_in[i_index].inout         = EPT_DIR_IN;
    udev->ept_in[i_index].maxpacket   = 0;
    udev->ept_in[i_index].trans_buf   = 0;
    udev->ept_in[i_index].total_len   = 0;
  }

  /* init out endpoint info structure */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    udev->ept_out[i_index].eptn        = i_index;
    udev->ept_out[i_index].ept_address = i_index;
    udev->ept_out[i_index].inout       = EPT_DIR_OUT;
    udev->ept_out[i_index].maxpacket   = 0;
    udev->ept_out[i_index].trans_buf   = 0;
    udev->ept_out[i_index].total_len   = 0;
  }
}

/**
  * @brief  endpoint send data
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @param  buffer: send data buffer
  * @param  len: send data length
  * @retval none
  */
void usbd_ept_send(usbd_core_type *udev, uint8_t ept_addr, uint8_t *buffer, uint16_t len)
{
  /* get endpoint info struct and register */
  usb_reg_type *usbx = udev->usb_reg;
  usb_ept_info *ept_info = &udev->ept_in[ept_addr & 0x7F];
  otg_eptin_type *ept_in = USB_INEPT(usbx, ept_info->eptn);
  otg_device_type *dev = OTG_DEVICE(usbx);
  uint32_t pktcnt;

  /* set send data buffer and length */
  ept_info->trans_buf = buffer;
  ept_info->total_len = len;
  ept_info->trans_len = 0;

  /* transfer data len is zero */
  if(ept_info->total_len == 0)
  {
    ept_in->dieptsiz_bit.pktcnt = 1;
    ept_in->dieptsiz_bit.xfersize = 0;
  }
  else
  {
    if((ept_addr & 0x7F) == 0) // endpoint 0
    {
      /* endpoint 0 */
      if(ept_info->total_len > ept_info->maxpacket)
      {
        ept_info->total_len = ept_info->maxpacket;
      }

      /* set transfer size  */
      ept_in->dieptsiz_bit.xfersize = ept_info->total_len;

      /* set packet count */
      ept_in->dieptsiz_bit.pktcnt = 1;

      ept_info->last_len = ept_info->total_len;
    }
    else
    {
      /* other endpoint */

      /* packet count */
      pktcnt = (ept_info->total_len + ept_info->maxpacket - 1) / ept_info->maxpacket;

      /* set transfer size  */
      ept_in->dieptsiz_bit.xfersize = ept_info->total_len;

      /* set packet count */
      ept_in->dieptsiz_bit.pktcnt = pktcnt;

      if(ept_info->trans_type == EPT_ISO_TYPE)
      {
        ept_in->dieptsiz_bit.mc = 1;
      }
    }
  }

  if(ept_info->trans_type == EPT_ISO_TYPE)
  {
    if((dev->dsts_bit.soffn & 0x1) == 0)
    {
      ept_in->diepctl_bit.setd1pid = TRUE;
    }
    else
    {
      ept_in->diepctl_bit.setd0pid = TRUE;
    }
  }

  /* clear endpoint nak */
  ept_in->diepctl_bit.cnak = TRUE;

  /* endpoint enable */
  ept_in->diepctl_bit.eptena = TRUE;

  if(ept_info->trans_type == EPT_ISO_TYPE)
  {
    /* write data to fifo */
    usb_write_packet(usbx, ept_info->trans_buf, ept_info->eptn, ept_info->total_len);
  }
  if(ept_info->trans_type != EPT_ISO_TYPE)
  {
    if(ept_info->total_len > 0)
    {
      /* set in endpoint tx fifo empty interrupt mask */
      dev->diepempmsk |= 1 << ept_info->eptn;
    }
  }
}

/**
  * @brief  endpoint receive data
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_addr: endpoint number
  * @param  buffer: receive data buffer
  * @param  len: receive data length
  * @retval none
  */
void usbd_ept_recv(usbd_core_type *udev, uint8_t ept_addr, uint8_t *buffer, uint16_t len)
{
  /* get endpoint info struct and register */
  usb_reg_type *usbx = udev->usb_reg;
  usb_ept_info *ept_info = &udev->ept_out[ept_addr & 0x7F];
  otg_eptout_type *ept_out = USB_OUTEPT(usbx, ept_info->eptn);
  otg_device_type *dev = OTG_DEVICE(usbx);
  uint32_t pktcnt;

   /* set receive data buffer and length */
  ept_info->trans_buf = buffer;
  ept_info->total_len = len;
  ept_info->trans_len = 0;

  if((ept_addr & 0x7F) == 0)
  {
    /* endpoint 0 */
    ept_info->total_len = ept_info->maxpacket;
  }

  if(ept_info->total_len == 0 || ((ept_addr & 0x7F) == 0))
  {
    /* set transfer size  */
    ept_out->doeptsiz_bit.xfersize = ept_info->maxpacket;

    /* set packet count */
    ept_out->doeptsiz_bit.pktcnt = 1;
  }
  else
  {
    pktcnt = (ept_info->total_len + ept_info->maxpacket - 1) / ept_info->maxpacket;

    /* set transfer size  */
    ept_out->doeptsiz_bit.xfersize = ept_info->maxpacket * pktcnt;

    /* set packet count */
    ept_out->doeptsiz_bit.pktcnt = pktcnt;
  }

  if(ept_info->trans_type == EPT_ISO_TYPE)
  {
   if((dev->dsts_bit.soffn & 0x01) == 0)
   {
     ept_out->doepctl_bit.setd1pid = TRUE;
   }
   else
   {
     ept_out->doepctl_bit.setd0pid = TRUE;
   }
  }

  /* clear endpoint nak */
  ept_out->doepctl_bit.cnak = TRUE;

  /* endpoint enable */
  ept_out->doepctl_bit.eptena = TRUE;
}

/**
  * @brief  get usb connect state
  * @param  udev: to the structure of usbd_core_type
  * @retval usb connect state
  */
usbd_conn_state usbd_connect_state_get(usbd_core_type *udev)
{
  return udev->conn_state;
}

/**
  * @brief  usb device remote wakeup
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_remote_wakeup(usbd_core_type *udev)
{
  /* check device is in suspend mode */
  if(usb_suspend_status_get(udev->usb_reg) == 1)
  {
    /* set connect state */
    udev->conn_state = udev->old_conn_state;

    /* open phy clock */
    usb_open_phy_clk(udev->usb_reg);

    /* set remote wakeup */
    usb_remote_wkup_set(udev->usb_reg);

    /* delay 10 ms */
    rt_thread_mdelay(10);

    /* clear remote wakup */
    usb_remote_wkup_clear(udev->usb_reg);
  }
}

/**
  * @brief  usb device enter suspend mode
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_enter_suspend(usbd_core_type *udev)
{
  /* check device is in suspend mode */
  if(usb_suspend_status_get(udev->usb_reg) == 1)
  {
    /* stop phy clk */
    usb_stop_phy_clk(udev->usb_reg);
  }
}

/**
  * @brief  usb device flush in endpoint fifo
  * @param  udev: to the structure of usbd_core_type
  * @param  ept_num: endpoint number
  * @retval none
  */
void usbd_flush_tx_fifo(usbd_core_type *udev, uint8_t ept_num)
{
  /* flush endpoint tx fifo */
  usb_flush_tx_fifo(udev->usb_reg, ept_num & 0x1F);
}

/**
  * @brief  usb device endpoint fifo alloc
  * @param  udev: to the structure of usbd_core_type
  * @retval none
  */
void usbd_fifo_alloc(usbd_core_type *udev)
{
  usb_reg_type *usbx = udev->usb_reg;

  if(usbx == OTG1_GLOBAL)
  {
    /* set receive fifo size */
    usb_set_rx_fifo(usbx, USBD_RX_SIZE);

    /* set endpoint0 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT0, USBD_EP0_TX_SIZE);

    /* set endpoint1 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT1, USBD_EP1_TX_SIZE);

    /* set endpoint2 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT2, USBD_EP2_TX_SIZE);

    /* set endpoint3 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT3, USBD_EP3_TX_SIZE);
#if (USB_EPT_MAX_NUM == 8)
    if(USB_EPT_MAX_NUM == 8)
    {
      /* set endpoint4 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT4, USBD_EP4_TX_SIZE);

      /* set endpoint5 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT5, USBD_EP5_TX_SIZE);

      /* set endpoint6 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT6, USBD_EP6_TX_SIZE);

      /* set endpoint7 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT7, USBD_EP7_TX_SIZE);
    }
#endif
  }
#ifdef OTG2_GLOBAL
  if(usbx == OTG2_GLOBAL)
  {
    /* set receive fifo size */
    usb_set_rx_fifo(usbx, USBD2_RX_SIZE);

    /* set endpoint0 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT0, USBD2_EP0_TX_SIZE);

    /* set endpoint1 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT1, USBD2_EP1_TX_SIZE);

    /* set endpoint2 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT2, USBD2_EP2_TX_SIZE);

    /* set endpoint3 tx fifo size */
    usb_set_tx_fifo(usbx, USB_EPT3, USBD2_EP3_TX_SIZE);

    if(USB_EPT_MAX_NUM == 8)
    {
      /* set endpoint4 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT4, USBD2_EP4_TX_SIZE);

      /* set endpoint5 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT5, USBD2_EP5_TX_SIZE);

      /* set endpoint6 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT6, USBD2_EP6_TX_SIZE);

      /* set endpoint7 tx fifo size */
      usb_set_tx_fifo(usbx, USB_EPT7, USBD2_EP7_TX_SIZE);
    }
  }
#endif
}

/**
  * @brief  usb device core initialization
  * @param  udev: to the structure of usbd_core_type
  * @param  usb_reg: usb otgfs peripheral global register
  *         this parameter can be one of the following values:
  *         OTG1_GLOBAL , OTG2_GLOBAL
  * @param  class_handler: usb class handler
  * @param  desc_handler: device config handler
  * @param  core_id: usb core id number
  * @retval usb_sts_type
  */
usb_sts_type usbd_core_init(usbd_core_type *udev,
                            usb_reg_type *usb_reg,
                            uint8_t core_id)
{
  usb_reg_type *usbx;
  otg_device_type *dev;
  otg_eptin_type *ept_in;
  otg_eptout_type *ept_out;
  uint32_t i_index;

  udev->usb_reg = usb_reg;
  usbx = usb_reg;
  dev = OTG_DEVICE(usbx);

  /* set connect state */
  udev->conn_state = USB_CONN_STATE_DEFAULT;

  /* device class config */
  udev->device_addr = 0;
  /* set device disconnect */
  usbd_disconnect(udev);

  /* set endpoint to default status */
  usb_ept_default_init(udev);

  /* disable usb global interrupt */
  usb_interrupt_disable(usbx);

  /* init global register */
  usb_global_init(usbx);

  /* set device mode */
  usb_global_set_mode(usbx, OTG_DEVICE_MODE);

  /* open phy clock */
  usb_open_phy_clk(udev->usb_reg);

  /* set periodic frame interval */
  dev->dcfg_bit.perfrint = DCFG_PERFRINT_80;

  /* set device speed to full-speed */
  dev->dcfg_bit.devspd = USB_DCFG_FULL_SPEED;

  /* flush all tx fifo */
  usb_flush_tx_fifo(usbx, 16);

  /* flush share rx fifo */
  usb_flush_rx_fifo(usbx);

  /* clear all endpoint interrupt flag and mask */
  dev->daint = 0xFFFFFFFF;
  dev->daintmsk = 0;
  dev->diepmsk = 0;
  dev->doepmsk = 0;

  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    usbx->dieptxfn[i_index] = 0;
  }

  /* endpoint fifo alloc */
  usbd_fifo_alloc(udev);

  /* disable all in endpoint */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    ept_in = USB_INEPT(usbx, i_index);
    if(ept_in->diepctl_bit.eptena)
    {
      ept_in->diepctl = 0;
      ept_in->diepctl_bit.eptdis = TRUE;
      ept_in->diepctl_bit.snak = TRUE;
    }
    else
    {
      ept_in->diepctl = 0;
    }
    ept_in->dieptsiz = 0;
    ept_in->diepint = 0xFF;
  }

  /* disable all out endpoint */
  for(i_index = 0; i_index < USB_EPT_MAX_NUM; i_index ++)
  {
    ept_out = USB_OUTEPT(usbx, i_index);
    if(ept_out->doepctl_bit.eptena)
    {
      ept_out->doepctl = 0;
      ept_out->doepctl_bit.eptdis = TRUE;
      ept_out->doepctl_bit.snak = TRUE;
    }
    else
    {
      ept_out->doepctl = 0;
    }
    ept_out->doeptsiz = 0;
    ept_out->doepint = 0xFF;
  }
  dev->diepmsk_bit.txfifoudrmsk = TRUE;

  /* clear global interrupt and mask */
  usbx->gintmsk = 0;
  usbx->gintsts = 0xBFFFFFFF;

  /* enable global interrupt mask */
  usbx->gintmsk = USB_OTG_SOF_INT | USB_OTG_RXFLVL_INT |
                  USB_OTG_USBSUSP_INT | USB_OTG_USBRST_INT |
                  USB_OTG_ENUMDONE_INT | USB_OTG_IEPT_INT |
                  USB_OTG_OEPT_INT | USB_OTG_INCOMISOIN_INT |
                  USB_OTG_INCOMPIP_INCOMPISOOUT_INT | USB_OTG_WKUP_INT |
                  USB_OTG_OTGINT_INT;

  /* usb connect */
  usbd_connect(udev);

  /* enable global interrupt */
  usb_interrupt_enable(usbx);

  return USB_OK;

}

#endif

/**
  * @}
  */

/**
  * @}
  */
