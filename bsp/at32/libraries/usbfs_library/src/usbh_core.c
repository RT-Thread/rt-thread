/**
  **************************************************************************
  * @file     usbh_core.c
  * @brief    usb host driver
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

#include "usbh_core.h"
#include "usb_core.h"
#include "usbh_ctrl.h"

#ifdef USE_OTG_HOST_MODE

/** @defgroup USBH_drivers_core
  * @brief usb host drivers core
  * @{
  */

/** @defgroup USBH_core_private_functions
  * @{
  */

static void usbh_attached(usbh_core_type *uhost);
static void usbh_enumeration(usbh_core_type *uhost);
static void usbh_class_request(usbh_core_type *uhost);
static void usbh_class(usbh_core_type *uhost);
static void usbh_suspend(usbh_core_type *uhost);
static void usbh_wakeup(usbh_core_type *uhost);
static void usbh_disconnect(usbh_core_type *uhost);
/**
  * @brief  usb host free channel
  * @param  uhost: to the structure of usbh_core_type
  * @param  index: channle number
  * @retval none
  */
void usbh_free_channel(usbh_core_type *uhost, uint8_t index)
{
  if(index < USB_HOST_CHANNEL_NUM)
  {
    /* free host channel */
    uhost->channel[index] = 0x0;
  }
}

/**
  * @brief  get usb host free channel
  * @param  uhost: to the structure of usbh_core_type
  * @retval channel index
  */
uint16_t usbh_get_free_channel(usbh_core_type *uhost)
{
  uint16_t i_index = 0;
  for(i_index = 0; i_index < USB_HOST_CHANNEL_NUM; i_index ++)
  {
    /* find unuse channel */
    if((uhost->channel[i_index] & HCH_USED) == 0)
    {
      /* return channel index */
      return i_index;
    }
  }
  return HCH_ERROR;
}


/**
  * @brief  usb host set toggle
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  toggle: toggle value
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_set_toggle(usbh_core_type *uhost, uint8_t hc_num, uint8_t toggle)
{
  if(uhost->hch[hc_num].dir)
  {
    /* direction in */
    uhost->hch[hc_num].toggle_in = toggle;
  }
  else
  {
    /* direction out */
    uhost->hch[hc_num].toggle_out = toggle;
  }
  return USB_OK;
}

/**
  * @brief  usb host in out request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_in_out_request(usbh_core_type *uhost, uint8_t hc_num)
{
  usb_sts_type status = USB_OK;
  uint32_t n_packet = 0;
  uint32_t num_words = 0;
  uint32_t tmp;
  otg_global_type *usbx = uhost->usb_reg;
  otg_hchannel_type *ch = USB_CHL(uhost->usb_reg, hc_num);

  /* set usb request block to idle */
  uhost->urb_state[hc_num] = URB_IDLE;
  uhost->hch[hc_num].state = HCH_IDLE;

  /* set usb channel transmit count to zero */
  uhost->hch[hc_num].trans_count = 0;

  /* check transmit data len */
  if(uhost->hch[hc_num].trans_len > 0)
  {
    /* count how many packet need to send */
    n_packet = (uhost->hch[hc_num].trans_len + \
               uhost->hch[hc_num].maxpacket - 1) / \
               uhost->hch[hc_num].maxpacket;

    /* packet count max 256 */
    if(n_packet > 256)
    {
      n_packet = 256;
      uhost->hch[hc_num].trans_len = n_packet * uhost->hch[hc_num].maxpacket;
    }
  }
  else
  {
    /* zero data len */
    n_packet = 1;
  }

  /* direction is in */
  if(uhost->hch[hc_num].dir)
  {
    uhost->hch[hc_num].trans_len = n_packet * uhost->hch[hc_num].maxpacket;
  }

  /* set transfer information to channel register */
  ch->hctsiz = (uhost->hch[hc_num].trans_len & USB_OTG_HCTSIZ_XFERSIZE) |
               ((n_packet << 19) & USB_OTG_HCTSIZ_PKTCNT) |
               ((uhost->hch[hc_num].data_pid << 29) & USB_OTG_HCTSIZ_PID);

  /* set odd frame */
  ch->hcchar_bit.oddfrm = !(OTG_HOST(uhost->usb_reg)->hfnum & 0x1);

  /* clear channel disable bit and enable channel */
  tmp = ch->hcchar;
  tmp &= ~(USB_OTG_HCCHAR_CHDIS);
  tmp |= USB_OTG_HCCHAR_CHENA;
  ch->hcchar = tmp;

  /* channel direction is out and transfer len > 0 */
  if((uhost->hch[hc_num].dir == 0) &&
    (uhost->hch[hc_num].trans_len > 0 ))
  {
    switch(uhost->hch[hc_num].ept_type)
    {
      case EPT_CONTROL_TYPE:
      case EPT_BULK_TYPE:
        num_words = (uhost->hch[hc_num].trans_len + 3) / 4;

        /* non-periodic transfer */
        if(num_words > usbx->gnptxsts_bit.nptxfspcavail)
        {
          usbx->gintmsk_bit.nptxfempmsk = 1;
        }
        break;
      case EPT_ISO_TYPE:
      case EPT_INT_TYPE:
        num_words = (uhost->hch[hc_num].trans_len + 3) / 4;

        /* periodic transfer */
        if(num_words > OTG_HOST(usbx)->hptxsts_bit.ptxfspcavil)
        {
          usbx->gintmsk_bit.ptxfempmsk = 1;
        }
        break;
      default:
        break;
    }
    /* write data to fifo */
    usb_write_packet(usbx, uhost->hch[hc_num].trans_buf,
                    hc_num, uhost->hch[hc_num].trans_len);
  }

  return status;
}

/**
  * @brief  usb host interrupt receive request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  buffer: receive buffer
  * @param  length: receive length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_interrupt_recv(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length)
{
  /* set direction is in */
  uhost->hch[hc_num].dir = 1;

  /* set transfer buffer */
  uhost->hch[hc_num].trans_buf = buffer;

  /* set transfer len*/
  uhost->hch[hc_num].trans_len = length;

  if(uhost->hch[hc_num].toggle_in == 0)
  {
    /* pid: data0 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA0;
  }
  else
  {
    /* pid: data1 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA1;
  }

  return usbh_in_out_request(uhost, hc_num);
}

/**
  * @brief  usb host interrupt send request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  buffer: send buffer
  * @param  length: send length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_interrupt_send(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length)
{
  /* set direction is out */
  uhost->hch[hc_num].dir = 0;

  /* set transfer buffer */
  uhost->hch[hc_num].trans_buf = buffer;

  /* set transfer len*/
  uhost->hch[hc_num].trans_len = length;

  if(uhost->hch[hc_num].toggle_out == 0)
  {
    /* pid: data0 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA0;
  }
  else
  {
    /* pid: data1 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA1;
  }

  return usbh_in_out_request(uhost, hc_num);
}


/**
  * @brief  usb host bulk receive request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  buffer: receive buffer
  * @param  length: receive length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_bulk_recv(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length)
{
  /* set direction is in */
  uhost->hch[hc_num].dir = 1;

  /* set transfer buffer */
  uhost->hch[hc_num].trans_buf = buffer;

  /* set transfer len*/
  uhost->hch[hc_num].trans_len = length;

  if(uhost->hch[hc_num].toggle_in == 0)
  {
    /* pid: data0 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA0;
  }
  else
  {
    /* pid: data1 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA1;
  }

  return usbh_in_out_request(uhost, hc_num);
}


/**
  * @brief  usb host bulk send request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  buffer: receive buffer
  * @param  length: receive length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_bulk_send(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length)
{
  /* set direction is out */
  uhost->hch[hc_num].dir = 0;

  /* set transfer buffer */
  uhost->hch[hc_num].trans_buf = buffer;

  /* set transfer len*/
  uhost->hch[hc_num].trans_len = length;

  if(uhost->hch[hc_num].toggle_out == 0)
  {
    /* pid: data0 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA0;
  }
  else
  {
    /* pid: data1 */
    uhost->hch[hc_num].data_pid = HCH_PID_DATA1;
  }

  return usbh_in_out_request(uhost, hc_num);
}


/**
  * @brief  usb host iso send request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  buffer: send buffer
  * @param  length: send length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_isoc_send(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length)
{
  /* set direction is out */
  uhost->hch[hc_num].dir = 0;

  /* set transfer buffer */
  uhost->hch[hc_num].trans_buf = buffer;

  /* set transfer len*/
  uhost->hch[hc_num].trans_len = length;

  /* pid: data0 */
  uhost->hch[hc_num].data_pid = HCH_PID_DATA0;

  return usbh_in_out_request(uhost, hc_num);
}

/**
  * @brief  usb host iso receive request
  * @param  uhost: to the structure of usbh_core_type
  * @param  hc_num: channel number
  * @param  buffer: receive buffer
  * @param  length: receive length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_isoc_recv(usbh_core_type *uhost, uint8_t hc_num,
                            uint8_t *buffer, uint16_t length)
{
  /* set direction is in */
  uhost->hch[hc_num].dir = 1;

  /* set transfer buffer */
  uhost->hch[hc_num].trans_buf = buffer;

  /* set transfer len*/
  uhost->hch[hc_num].trans_len = length;

  /* pid: data0 */
  uhost->hch[hc_num].data_pid = HCH_PID_DATA0;

  return usbh_in_out_request(uhost, hc_num);
}

/**
  * @brief  usb host cfg default init
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_cfg_default_init(usbh_core_type *uhost)
{
  /* set global state to idle */
  uhost->global_state = USBH_IDLE;

  /* enumeration state to get description */
  uhost->enum_state = ENUM_GET_MIN_DESC;

  /* request state send */
  uhost->req_state = CMD_SEND;

  /* control transfer state is idle*/
  uhost->ctrl.state = CONTROL_IDLE;

  /* defaut endpoint 0 max size is 8byte */
  uhost->ctrl.ept0_size = 8;

  /* default device address is 0 */
  uhost->dev.address = 0;

  /* default speed is full speed */
  uhost->dev.speed = USB_FULL_SPEED_CORE_ID;

  uhost->timer = 0;

  uhost->ctrl.err_cnt = 0;

  /* free all channel */
  usbh_free_channel(uhost, uhost->ctrl.hch_in);
  usbh_free_channel(uhost, uhost->ctrl.hch_out);
  return USB_OK;
}

/**
  * @brief  usb host enter suspend
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_enter_suspend(usbh_core_type *uhost)
{
  otg_host_type *host = OTG_HOST(uhost->usb_reg);
  uint32_t hprt_val = host->hprt;

  hprt_val &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
               USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET);

  /* set port suspend */
  host->hprt = hprt_val | USB_OTG_HPRT_PRTSUSP;

  /* stop phy clock */
  usb_stop_phy_clk(uhost->usb_reg);

}

/**
  * @brief  usb host resume
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
void usbh_resume(usbh_core_type *uhost)
{
  otg_host_type *host = OTG_HOST(uhost->usb_reg);
  uint32_t temp = host->hprt;

  /* open phy clock */
  usb_open_phy_clk(uhost->usb_reg);

  /* clear port suspend and set port resume*/
  temp &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
           USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET
           | USB_OTG_HPRT_PRTSUSP);
  host->hprt = temp | USB_OTG_HPRT_PRTRES;

  /* delay 20 ms */
  rt_thread_mdelay(20);

  /*clear port resume */
  temp = host->hprt;
  temp &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
           USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET
           | USB_OTG_HPRT_PRTRES);
  host->hprt = temp;
  rt_thread_mdelay(5);
}

/**
  * @brief  usb host core initialize
  * @param  uhost: to the structure of usbh_core_type
  * @param  usb_reg: usb otgfs peripheral global register
  *         this parameter can be one of the following values:
  *         OTG1_GLOBAL , OTG2_GLOBAL
  * @param  class_handler: usb host class handler type pointer
  * @param  user_handler: usb host user handler type pointer
  * @param  core_id: usb core select id
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_core_init(usbh_core_type *uhost,
                            usb_reg_type *usb_reg,
                            uint8_t core_id)
{
  usb_sts_type status = USB_OK;
  uint32_t i_index;
  otg_global_type *usbx = usb_reg;
  otg_host_type *host =  OTG_HOST(usbx);
  uhost->usb_reg = usb_reg;

  uhost->timer = 0;

  /* usb host cfg default init */
  usbh_cfg_default_init(uhost);

  /* clear host config to default value */
  for(i_index = 0; i_index < USB_HOST_CHANNEL_NUM; i_index ++)
  {
    uhost->err_cnt[i_index] = 0;
    uhost->xfer_cnt[i_index] = 0;
    uhost->hch_state[i_index] = HCH_IDLE;
    uhost->hch[0].maxpacket = 8;
  }

  /* no device connect */
  uhost->conn_sts = 0;

  /* disable usb interrupt */
  usb_interrupt_disable(usbx);

  /* usb global init */
  usb_global_init(usbx);

  /* set usb host mode */
  usb_global_set_mode(usbx, OTG_HOST_MODE);

  /* open usb phy clock*/
  usb_open_phy_clk(usbx);

  /* clock select */
  usbh_fsls_clksel(usbx, USB_HCFG_CLK_48M);

  /* set support ls and fs device */
  host->hcfg_bit.fslssupp = 0;

  if(usbx == OTG1_GLOBAL)
  {
    /* set receive fifo size */
    usbx->grxfsiz = USBH_RX_FIFO_SIZE;

    /* set non-periodic transmit fifo start address and depth */
    usbx->gnptxfsiz_ept0tx_bit.nptxfstaddr = USBH_RX_FIFO_SIZE;
    usbx->gnptxfsiz_ept0tx_bit.nptxfdep = USBH_NP_TX_FIFO_SIZE;

    /* set periodic transmit fifo start address and depth */
    usbx->hptxfsiz_bit.ptxfstaddr = USBH_RX_FIFO_SIZE + USBH_NP_TX_FIFO_SIZE;
    usbx->hptxfsiz_bit.ptxfsize = USBH_P_TX_FIFO_SIZE;
  }
#ifdef OTG2_GLOBAL
  if(usbx == OTG2_GLOBAL)
  {
    /* set receive fifo size */
    usbx->grxfsiz = USBH2_RX_FIFO_SIZE;

    /* set non-periodic transmit fifo start address and depth */
    usbx->gnptxfsiz_ept0tx_bit.nptxfstaddr = USBH2_RX_FIFO_SIZE;
    usbx->gnptxfsiz_ept0tx_bit.nptxfdep = USBH2_NP_TX_FIFO_SIZE;

    /* set periodic transmit fifo start address and depth */
    usbx->hptxfsiz_bit.ptxfstaddr = USBH2_RX_FIFO_SIZE + USBH2_NP_TX_FIFO_SIZE;
    usbx->hptxfsiz_bit.ptxfsize = USBH2_P_TX_FIFO_SIZE;
  }
#endif
  /* flush tx fifo */
  usb_flush_tx_fifo(usbx, 16);

  /* flush rx fifo */
  usb_flush_rx_fifo(usbx);

  /* clear host channel interrut mask and status */
  for(i_index = 0; i_index < USB_HOST_CHANNEL_NUM; i_index ++)
  {
    USB_CHL(usbx, i_index)->hcintmsk = 0;
    USB_CHL(usbx, i_index)->hcint = 0xFFFFFFFF;
  }

  /* power on to this port */
  usb_port_power_on(usbx, TRUE);

  /* clear global interrupt mask and status */
  usbx->gintmsk = 0;
  usbx->gintsts = 0xBFFFFFFF;

  /* set global interrut mask */
  usbx->gintmsk = USB_OTG_SOF_INT | USB_OTG_RXFLVL_INT |
                  USB_OTG_USBSUSP_INT | USB_OTG_PRT_INT |
                   USB_OTG_HCH_INT | USB_OTG_INCOMISOIN_INT |
                  USB_OTG_INCOMPIP_INCOMPISOOUT_INT | USB_OTG_WKUP_INT |
                  USB_OTG_DISCON_INT;

  /* enable usb global interrupt */
  usb_interrupt_enable(usbx);

  /* active vbus */
  usbh_active_vbus(uhost, TRUE);
  return status;
}

/**
  * @brief  usb host open channel
  * @param  uhost: to the structure of usbh_core_type
  * @param  chn: host channel number
  * @param  ept_num: devvice endpoint number
  * @param  dev_address: device address
  * @param  type: channel transfer type
  *         this parameter can be one of the following values:
  *         - EPT_CONTROL_TYPE
  *         - EPT_BULK_TYPE
  *         - EPT_INT_TYPE
  *         - EPT_ISO_TYPE
  * @param  maxpacket: support max packe size for this channel
  * @param  speed: device speed
  *         this parameter can be one of the following values:
  *         - USB_PRTSPD_FULL_SPEED
  *         - USB_PRTSPD_LOW_SPEED
  * @param  ept_addr: endpoint address
  * @retval usb_sts_type
  */
void usbh_hc_open(usbh_core_type *uhost,
                   uint8_t chn,
                   uint8_t ept_num,
                   uint8_t dev_address,
                   uint8_t type,
                   uint16_t maxpacket,
                   uint8_t speed)
{
  /* device address */
  uhost->hch[chn].address = dev_address;

  /* device speed */
  uhost->hch[chn].speed = speed;

  /* endpoint transfer type */
  uhost->hch[chn].ept_type = type;

  /* endpoint support maxpacket */
  uhost->hch[chn].maxpacket = maxpacket;

  /* endpoint direction in or out */
  uhost->hch[chn].dir = (ept_num & 0x80)?1:0;;

  /* host channel number */
  uhost->hch[chn].ch_num = chn;

  /* device endpoint number */
  uhost->hch[chn].ept_num = ept_num;

  /* enable channel */
  usb_hc_enable(uhost->usb_reg, chn,
                ept_num, dev_address,
                type, maxpacket, speed
           );
}

/**
  * @brief  disable host channel
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  chn: channel number
  * @retval none
  */
void usbh_ch_disable(usbh_core_type *uhost, uint8_t chn)
{
  usb_hch_halt(uhost->usb_reg, chn);
}

/**
  * @brief  usb host alloc channel
  * @param  uhost: to the structure of usbh_core_type
  * @param  ept_addr: endpoint address
  * @retval usb_sts_type
  */
uint16_t usbh_alloc_channel(usbh_core_type *uhost, uint8_t ept_addr)
{
  /* get one free channel */
  uint16_t ch_num = usbh_get_free_channel(uhost);

  if(ch_num == HCH_ERROR)
    return USB_FAIL;

  /* set channel to used */
  uhost->channel[ch_num] = HCH_USED | ept_addr;
  return ch_num;
}

hch_sts_type usbh_get_status(usbh_core_type *uhost, uint8_t ch_num)
{
   return uhost->hch_state[ch_num];
}

/**
  * @brief  usb host get urb status
  * @param  uhost: to the structure of usbh_core_type
  * @param  ch_num: channel number
  * @retval urb_sts_type: urb status
  */
urb_sts_type usbh_get_urb_status(usbh_core_type *uhost, uint8_t ch_num)
{
  return uhost->urb_state[ch_num];
}
/**
  * @brief  usb wait control setup complete
  * @param  uhost: to the structure of usbh_core_type
  * @param  next_ctrl_state: next ctrl state when setup complete
  * @param  next_enum_state: next enum state when setup complete
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_result_check(usbh_core_type *uhost, ctrl_ept0_sts_type next_ctrl_state, uint8_t next_enum_state)
{
  usb_sts_type status;

  /* control transfer loop */
  status = usbh_ctrl_transfer_loop(uhost);

  if(status == USB_OK)
  {
    uhost->ctrl.state = next_ctrl_state;
    uhost->enum_state = next_enum_state;
    uhost->req_state = CMD_SEND;
  }
  else if(status == USB_ERROR)
  {
    uhost->ctrl.state = CONTROL_IDLE;
    uhost->req_state = CMD_SEND;
  }
  else if(status == USB_NOT_SUPPORT)
  {
    uhost->ctrl.state = next_ctrl_state;
    uhost->enum_state = next_enum_state;
    uhost->req_state = CMD_SEND;
  }
  return status;
}

/**
  * @brief  auto alloc address (1...20)
  * @param  none
  * @retval address (1...20)
  */
uint8_t usbh_alloc_address(void)
{
  static uint8_t address = 1;
  if(address == 20)
    address = 1;
  return address ++;
}


/**
  * @brief  usb host enumeration handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_enum_handler(usbh_core_type *uhost)
{
  usb_sts_type status = USB_WAIT;
  switch(uhost->enum_state)
  {
    case ENUM_IDLE:
      break;
    case ENUM_GET_MIN_DESC:
      /* get description */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_device_descriptor(uhost, 8);
      }
      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_GET_FULL_DESC) == USB_OK)
      {
        usbh_parse_dev_desc(uhost, uhost->rx_buffer, 8);

        /* set new control endpoint maxpacket size */
        uhost->ctrl.ept0_size = (uhost->dev).dev_desc.bMaxPacketSize0;

        /* enable channel */
        usbh_hc_open(uhost, uhost->ctrl.hch_in,0x80,
                      uhost->dev.address, EPT_CONTROL_TYPE,
                      uhost->ctrl.ept0_size,
                      uhost->dev.speed);

        /* enable channel */
        usbh_hc_open(uhost, uhost->ctrl.hch_out,0x00,
                      uhost->dev.address, EPT_CONTROL_TYPE,
                      uhost->ctrl.ept0_size,
                      uhost->dev.speed);
      }
      break;

    case ENUM_GET_FULL_DESC:
      /* get description */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_device_descriptor(uhost, 18);
      }
      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_SET_ADDR) == USB_OK)
      {
        usbh_parse_dev_desc(uhost, uhost->rx_buffer, 18);
      }
      break;

    case ENUM_SET_ADDR:
      /* set device address */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        uhost->dev.address = usbh_alloc_address();
        usbh_set_address(uhost, uhost->dev.address);
      }
      if (usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_GET_CFG) == USB_OK)
      {
        /* enable channel */
        usbh_hc_open(uhost, uhost->ctrl.hch_in,0x80,
                      uhost->dev.address, EPT_CONTROL_TYPE,
                      uhost->ctrl.ept0_size,
                      uhost->dev.speed);

        /* enable channel */
        usbh_hc_open(uhost, uhost->ctrl.hch_out,0x00,
                      uhost->dev.address, EPT_CONTROL_TYPE,
                      uhost->ctrl.ept0_size,
                      uhost->dev.speed);
      }
      break;

    case ENUM_GET_CFG:
      /* get device confiuration */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_configure_descriptor(uhost, 9);
      }

      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_GET_FULL_CFG) == USB_OK)
      {
        usbh_parse_configure_desc(uhost, uhost->rx_buffer, 9);
      }
      break;

    case ENUM_GET_FULL_CFG:
      /* get device confiuration */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_configure_descriptor(uhost, uhost->dev.cfg_desc.cfg.wTotalLength);
      }

      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_GET_MFC_STRING) == USB_OK)
      {
        usbh_parse_configure_desc(uhost, uhost->rx_buffer, uhost->dev.cfg_desc.cfg.wTotalLength);
      }
      break;

    case ENUM_GET_MFC_STRING:
      /* get device mfc string */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_sting_descriptor(uhost, uhost->dev.dev_desc.iManufacturer,
                                  uhost->rx_buffer, 0xFF);
      }

      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_GET_PRODUCT_STRING) == USB_OK)
      {
        usbh_parse_string_desc(uhost->rx_buffer, uhost->rx_buffer, 0xFF);
        uhost->user_handler->user_mfc_string(uhost->rx_buffer);
      }
      break;

    case ENUM_GET_PRODUCT_STRING:
      /* get device product string */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_sting_descriptor(uhost, uhost->dev.dev_desc.iProduct,
                                  uhost->rx_buffer, 0xFF);
      }

      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_GET_SERIALNUM_STRING) == USB_OK)
      {
        usbh_parse_string_desc(uhost->rx_buffer, uhost->rx_buffer, 0xFF);
        uhost->user_handler->user_product_string(uhost->rx_buffer);
      }
      break;

    case ENUM_GET_SERIALNUM_STRING:
      /* get device serial string */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_get_sting_descriptor(uhost, uhost->dev.dev_desc.iSerialNumber,
                                  uhost->rx_buffer, 0xFF);
      }

      if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_SET_CONFIG) == USB_OK)
      {
        usbh_parse_string_desc(uhost->rx_buffer, uhost->rx_buffer, 0xFF);
        uhost->user_handler->user_serial_string(uhost->rx_buffer);
      }
      break;

    case ENUM_SET_CONFIG:
      /* set device config */
      if(uhost->ctrl.state == CONTROL_IDLE)
      {
        usbh_set_configuration(uhost, uhost->dev.cfg_desc.cfg.bConfigurationValue);
      }
      usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_COMPLETE);

      break;

    case ENUM_COMPLETE:
      /* enum complete */
      status = USB_OK;
      break;
    default:
      break;
  }
  return status;
}

/**
  * @brief  active vbus.
  * @param  uhost: to the structure of usbh_core_type
  * @param  state: vbus state
  * @retval none
  */
void usbh_active_vbus(usbh_core_type *uhost, confirm_state state)
{
}

/**
  * @brief  reset usb port
  * @param  usbx: to the structure of otg_global_type
  * @retval none
  */
void usbh_reset_port(usbh_core_type *uhost)
{
  otg_host_type *usb_host = OTG_HOST(uhost->usb_reg);
  uint32_t hprt_val = usb_host->hprt;

  hprt_val &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
               USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET);

  /* set port reset */
  usb_host->hprt = hprt_val | USB_OTG_HPRT_PRTRST;

  rt_thread_mdelay(100);

  /* clear port reset */
  usb_host->hprt = hprt_val & (~USB_OTG_HPRT_PRTRST);

  rt_thread_mdelay(20);
}

/**
  * @brief  usb host attached
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_attached(usbh_core_type *uhost)
{
  /* get free channel */
  uhost->ctrl.hch_in = usbh_alloc_channel(uhost, 0x80);
  uhost->ctrl.hch_out = usbh_alloc_channel(uhost, 0x00);

  /* user reset callback handler */
  uhost->user_handler->user_reset();

  /* get device speed */
  uhost->dev.speed = OTG_HOST(uhost->usb_reg)->hprt_bit.prtspd;
  uhost->global_state  = USBH_ENUMERATION;
  uhost->user_handler->user_speed(uhost->dev.speed);

  /* enable channel */
  usbh_hc_open(uhost, uhost->ctrl.hch_in,0x80,
                uhost->dev.address, EPT_CONTROL_TYPE,
                uhost->ctrl.ept0_size,
                uhost->dev.speed);

  /* enable channel */
  usbh_hc_open(uhost, uhost->ctrl.hch_out,0x00,
                uhost->dev.address, EPT_CONTROL_TYPE,
                uhost->ctrl.ept0_size,
                uhost->dev.speed);

  usb_flush_tx_fifo(uhost->usb_reg, 0x10);
  usb_flush_rx_fifo(uhost->usb_reg);

  /* user attached callback */
  uhost->user_handler->user_attached();
}


/**
  * @brief  usb host enumeration
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_enumeration(usbh_core_type *uhost)
{
  /* enumeration process */
  if(usbh_enum_handler(uhost) == USB_OK)
  {
    /* user enumeration done callback */
    uhost->user_handler->user_enumeration_done();
    uhost->global_state  = USBH_USER_HANDLER;
  }
}

/**
  * @brief  usb host class request
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_class_request(usbh_core_type *uhost)
{
  usb_sts_type status;

  /* class request callback */
  status = uhost->class_handler->request_handler((void *)uhost);
  if(status == USB_OK)
  {
    uhost->global_state = USBH_CLASS;
  }
  else if(status == USB_ERROR || status == USB_FAIL)
  {
    uhost->global_state = USBH_ERROR_STATE;
  }
  else if(status == USB_NOT_SUPPORT)
  {
    uhost->global_state = USBH_ERROR_STATE;
  }
}

/**
  * @brief  usb host class handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_class(usbh_core_type *uhost)
{
  /* process handler */
  if(uhost->class_handler->process_handler((void *)uhost) == USB_OK)
  {
  }
}

/**
  * @brief  usb host suspend
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_suspend(usbh_core_type *uhost)
{
  /* set device feature */
  if(uhost->ctrl.state == CONTROL_IDLE)
  {
    usbh_set_feature(uhost, 0x01, 0);
  }
  if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_IDLE) == USB_OK)
  {
    /* enter suspend mode */
    rt_thread_mdelay(3);
    usbh_enter_suspend(uhost);
    uhost->global_state = USBH_SUSPENDED;

  }
}

/**
  * @brief  usb host wakeup
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_wakeup(usbh_core_type *uhost)
{
  /* clear device feature */
  if(uhost->ctrl.state == CONTROL_IDLE)
  {
   /* usb host resume */
    usbh_resume(uhost);
    usbh_clear_dev_feature(uhost, 0x01, 0);
  }
  if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_IDLE) == USB_OK)
  {
    uhost->global_state = USBH_CLASS_REQUEST;
  }
}

/**
  * @brief  usb host disconnect
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
static void usbh_disconnect(usbh_core_type *uhost)
{
  uint8_t i_index = 0;

  /* set host to default state */
  usbh_cfg_default_init(uhost);

  /* free host channel */
  for(i_index = 0; i_index < USB_HOST_CHANNEL_NUM; i_index ++)
  {
    usbh_free_channel(uhost, i_index);
  }

  /* call class reset handler */
  if(uhost->class_handler->reset_handler != RT_NULL)
  {
    uhost->class_handler->reset_handler(uhost);
  }

  /* set global state to idle */
  uhost->global_state = USBH_IDLE;

  /*call user disconnect function */
  uhost->user_handler->user_disconnect();
}


/**
  * @brief  usb host enum loop handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval none
  */
usb_sts_type usbh_loop_handler(usbh_core_type *uhost)
{
  usb_sts_type status = USB_FAIL;

  if(uhost->conn_sts == 0 &&
      uhost->global_state != USBH_IDLE &&
      uhost->global_state != USBH_DISCONNECT)
  {
    uhost->global_state  = USBH_IDLE;
  }
  switch(uhost->global_state)
  {
    case USBH_IDLE:
      if(uhost->conn_sts == 1)
      {
        uhost->global_state  = USBH_PORT_EN;

        /* wait stable */
        rt_thread_mdelay(200);

        /* port reset */
        usbh_reset_port(uhost);

        /* user reset */
        uhost->user_handler->user_reset();
      }
      break;

    case USBH_PORT_EN:
      if(uhost->port_enable)
      {
        uhost->global_state  = USBH_ATTACHED;
        rt_thread_mdelay(50);
      }
      break;

    case USBH_ATTACHED:
      usbh_attached(uhost);
      break;

    case USBH_ENUMERATION:
      usbh_enumeration(uhost);
      break;

    case USBH_USER_HANDLER:
      uhost->global_state  = USBH_CLASS_REQUEST;
      if( uhost->class_handler->init_handler(uhost) == USB_NOT_SUPPORT)
      {
        uhost->global_state = USBH_UNSUPPORT;
      }
      break;

    case USBH_CLASS_REQUEST:
      usbh_class_request(uhost);
      break;

    case USBH_CLASS:
      usbh_class(uhost);
      break;

    case USBH_SUSPEND:
      usbh_suspend(uhost);
      break;

    case USBH_SUSPENDED:
      break;

    case USBH_WAKEUP:
      usbh_wakeup(uhost);
      break;

    case USBH_DISCONNECT:
      usbh_disconnect(uhost);
      break;

    case USBH_ERROR_STATE:
      usbh_cfg_default_init(uhost);
      uhost->class_handler->reset_handler(uhost);
      uhost->user_handler->user_reset();
      break;
    case USBH_UNSUPPORT:
      break;
    default:
      break;
  }

  return status;
}

/**
  * @}
  */

/**
  * @}
  */

#endif
