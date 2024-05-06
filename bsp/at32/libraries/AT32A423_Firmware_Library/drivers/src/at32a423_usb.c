/**
  **************************************************************************
  * @file     at32a423_usb.c
  * @brief    contains all the functions for the usb firmware library
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

#include "at32a423_conf.h"

/** @addtogroup AT32A423_periph_driver
  * @{
  */

/** @defgroup USB
  * @brief USB driver modules
  * @{
  */

#ifdef USB_MODULE_ENABLED

/** @defgroup USB_private_functions
  * @{
  */

#ifdef OTGFS_USB_GLOBAL
/**
  * @brief  usb global core soft reset
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval error status
  */
error_status usb_global_reset(otg_global_type *usbx)
{
  uint32_t timeout = 0;
  while(usbx->grstctl_bit.ahbidle == RESET)
  {
    if(timeout ++ > 200000)
    {
      break;
    }
  }
  timeout = 0;
  usbx->grstctl_bit.csftrst = TRUE;
  while(usbx->grstctl_bit.csftrst == SET)
  {
    if(timeout ++ > 200000)
    {
      break;
    }
  }
  return SUCCESS;
}

/**
  * @brief  usb global initialization
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_global_init(otg_global_type *usbx)
{
  /* reset otg moudle */
  usb_global_reset(usbx);

  /* exit power down mode */
  usbx->gccfg_bit.pwrdown = TRUE;
}

/**
  * @brief  usb global select usb core (otg1 or otg2).
  * @param  usb_id: select otg1 or otg2
  *         this parameter can be one of the following values:
  *         - USB_OTG1_ID
  * @retval usb global register type pointer
  */
otg_global_type *usb_global_select_core(uint8_t usb_id)
{
  UNUSED(usb_id);
  return OTG1_GLOBAL;
}

/**
  * @brief  flush tx fifo
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  fifo_num: tx fifo num,when fifo_num=16,flush all tx fifo
  *         parameter as following values: 0-16
  * @retval none
  */
void usb_flush_tx_fifo(otg_global_type *usbx, uint32_t fifo_num)
{
  uint32_t timeout = 0;
  /* set flush fifo number */
  usbx->grstctl_bit.txfnum = fifo_num;

  /* start flush fifo */
  usbx->grstctl_bit.txfflsh = TRUE;

  while(usbx->grstctl_bit.txfflsh == TRUE)
  {
    if(timeout ++ > 200000)
    {
      break;
    }
  }
}

/**
  * @brief  flush rx fifo
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_flush_rx_fifo(otg_global_type *usbx)
{
  uint32_t timeout = 0;
  usbx->grstctl_bit.rxfflsh = TRUE;
  while(usbx->grstctl_bit.rxfflsh == TRUE)
  {
    if(timeout ++ > 200000)
    {
      break;
    }
  }
}

/**
  * @brief  usb interrupt mask enable
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  interrupt:
  *         this parameter can be any combination of the following values:
  *         - USB_OTG_MODEMIS_INT
  *         - USB_OTG_OTGINT_INT
  *         - USB_OTG_SOF_INT
  *         - USB_OTG_RXFLVL_INT
  *         - USB_OTG_NPTXFEMP_INT
  *         - USB_OTG_GINNAKEFF_INT
  *         - USB_OTG_GOUTNAKEFF_INT
  *         - USB_OTG_ERLYSUSP_INT
  *         - USB_OTG_USBSUSP_INT
  *         - USB_OTG_USBRST_INT
  *         - USB_OTG_ENUMDONE_INT
  *         - USB_OTG_ISOOUTDROP_INT
  *         - USB_OTG_IEPT_INT
  *         - USB_OTG_OEPT_INT
  *         - USB_OTG_INCOMISOIN_INT
  *         - USB_OTG_INCOMPIP_INCOMPISOOUT_INT
  *         - USB_OTG_PRT_INT
  *         - USB_OTG_HCH_INT
  *         - USB_OTG_PTXFEMP_INT
  *         - USB_OTG_CONIDSCHG_INT
  *         - USB_OTG_DISCON_INT
  *         - USB_OTG_WKUP_INT
  * @param  new_state: TRUE or FALSE
  * @retval none
  */
void usb_global_interrupt_enable(otg_global_type *usbx, uint16_t interrupt, confirm_state new_state)
{
  if(new_state == TRUE)
  {
     usbx->gintmsk |= interrupt;
  }
  else
  {
     usbx->gintmsk &= ~interrupt;
  }
}

/**
  * @brief  get all global core interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval intterupt flag
  */
uint32_t usb_global_get_all_interrupt(otg_global_type *usbx)
{
  uint32_t intsts = usbx->gintsts;
  return intsts & usbx->gintmsk;
}

/**
  * @brief  clear the global interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  *         - OTG2_GLOBAL
  * @param  flag: interrupt flag
  *         this parameter can be any combination of the following values:
  *         - USB_OTG_MODEMIS_FLAG
  *         - USB_OTG_OTGINT_FLAG
  *         - USB_OTG_SOF_FLAG
  *         - USB_OTG_RXFLVL_FLAG
  *         - USB_OTG_NPTXFEMP_FLAG
  *         - USB_OTG_GINNAKEFF_FLAG
  *         - USB_OTG_GOUTNAKEFF_FLAG
  *         - USB_OTG_ERLYSUSP_FLAG
  *         - USB_OTG_USBSUSP_FLAG
  *         - USB_OTG_USBRST_FLAG
  *         - USB_OTG_ENUMDONE_FLAG
  *         - USB_OTG_ISOOUTDROP_FLAG
  *         - USB_OTG_EOPF_FLAG
  *         - USB_OTG_IEPT_FLAG
  *         - USB_OTG_OEPT_FLAG
  *         - USB_OTG_INCOMISOIN_FLAG
  *         - USB_OTG_INCOMPIP_INCOMPISOOUT_FLAG
  *         - USB_OTG_PRT_FLAG
  *         - USB_OTG_HCH_FLAG
  *         - USB_OTG_PTXFEMP_FLAG
  *         - USB_OTG_CONIDSCHG_FLAG
  *         - USB_OTG_DISCON_FLAG
  *         - USB_OTG_WKUP_FLAG
  * @retval none
  */
void usb_global_clear_interrupt(otg_global_type *usbx, uint32_t flag)
{
  usbx->gintsts = flag;
}

/**
  * @brief  usb global interrupt enable
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         OTG1_GLOBAL
  * @retval none
  */
void usb_interrupt_enable(otg_global_type *usbx)
{
  usbx->gahbcfg_bit.glbintmsk = TRUE;
}

/**
  * @brief  usb global interrupt disable
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_interrupt_disable(otg_global_type *usbx)
{
  usbx->gahbcfg_bit.glbintmsk = FALSE;
}

/**
  * @brief  usb set rx fifo size
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  size: rx fifo size
  * @retval none
  */
void usb_set_rx_fifo(otg_global_type *usbx, uint16_t size)
{
  usbx->grxfsiz = size;
}

/**
  * @brief  usb set tx fifo size
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  txfifo: the fifo number
  * @param  size: tx fifo size
  * @retval none
  */
void usb_set_tx_fifo(otg_global_type *usbx, uint8_t txfifo, uint16_t size)
{
  uint8_t i_index = 0;
  uint32_t offset = 0;

  offset = usbx->grxfsiz;
  if(txfifo == 0)
  {
    usbx->gnptxfsiz_ept0tx = offset | (size << 16);
  }
  else
  {
    offset += usbx->gnptxfsiz_ept0tx_bit.nptxfdep;
    for(i_index = 0; i_index < (txfifo - 1); i_index ++)
    {
      offset += usbx->dieptxfn_bit[i_index].ineptxfdep;
    }
    usbx->dieptxfn[txfifo - 1] = offset | (size << 16);
  }
}


/**
  * @brief  set otg mode(device or host mode)
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  mode:
            this parameter can be one of the following values:
  *         - OTG_DEVICE_MODE
  *         - OTG_HOST_MODE
  *         - OTG_DRD_MODE
  * @retval none
  */
void usb_global_set_mode(otg_global_type *usbx, uint32_t mode)
{
  /* set otg to device mode */
  if(mode == OTG_DEVICE_MODE)
  {
    usbx->gusbcfg_bit.fhstmode = FALSE;
    usbx->gusbcfg_bit.fdevmode = TRUE;
  }

  /* set otg to host mode */
  if(mode == OTG_HOST_MODE)
  {
    usbx->gusbcfg_bit.fdevmode = FALSE;
    usbx->gusbcfg_bit.fhstmode = TRUE;
  }

  /* set otg to default mode */
  if(mode == OTG_DRD_MODE)
  {
    usbx->gusbcfg_bit.fdevmode = FALSE;
    usbx->gusbcfg_bit.fhstmode = FALSE;
  }
}


/**
  * @brief  disable the transceiver power down mode
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_global_power_on(otg_global_type *usbx)
{
  /* core soft reset */
  usbx->grstctl_bit.csftrst = TRUE;
  while(usbx->grstctl_bit.csftrst);

  /* disable power down mode */
  usbx->gccfg_bit.pwrdown = TRUE;

}

/**
  * @brief  usb stop phy clock
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_stop_phy_clk(otg_global_type *usbx)
{
  OTG_PCGCCTL(usbx)->pcgcctl_bit.stoppclk = TRUE;
}

/**
  * @brief  usb open phy clock
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_open_phy_clk(otg_global_type *usbx)
{
  OTG_PCGCCTL(usbx)->pcgcctl_bit.stoppclk = FALSE;
}


/**
  * @brief  write data from user memory to usb buffer
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  pusr_buf: point to user buffer
  * @param  offset_addr: endpoint tx offset address
  * @param  nbytes: number of bytes data write to usb buffer
  * @retval none
  */
void usb_write_packet(otg_global_type *usbx, uint8_t *pusr_buf, uint16_t num, uint16_t nbytes)
{
  uint32_t n_index;
  uint32_t nhbytes = (nbytes + 3) / 4;
  uint32_t *pbuf = (uint32_t *)pusr_buf;
  for(n_index = 0; n_index < nhbytes; n_index ++)
  {
#if defined (__ICCARM__) && (__VER__ < 7000000)
    USB_FIFO(usbx, num) = *(__packed uint32_t *)pbuf;
#else
    USB_FIFO(usbx, num) = __UNALIGNED_UINT32_READ(pbuf);
#endif
    pbuf ++;
  }
}

/**
  * @brief  read data from usb buffer to user buffer
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  pusr_buf: point to user buffer
  * @param  offset_addr: endpoint rx offset address
  * @param  nbytes: number of bytes data write to usb buffer
  * @retval none
  */
void usb_read_packet(otg_global_type *usbx, uint8_t *pusr_buf, uint16_t num, uint16_t nbytes)
{
  uint32_t n_index;
  uint32_t nhbytes = (nbytes + 3) / 4;
  uint32_t *pbuf = (uint32_t *)pusr_buf;
  UNUSED(num);
  for(n_index = 0; n_index < nhbytes; n_index ++)
  {
#if defined (__ICCARM__) && (__VER__ < 7000000)
    *(__packed uint32_t *)pbuf = USB_FIFO(usbx, 0);
#else
    __UNALIGNED_UINT32_WRITE(pbuf, (USB_FIFO(usbx, 0)));
#endif
    pbuf ++;
  }
}
#endif


#ifdef OTGFS_USB_DEVICE
/**
  * @brief  open usb endpoint
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval none
  */
void usb_ept_open(otg_global_type *usbx, usb_ept_info *ept_info)
{
  uint8_t mps = USB_EPT0_MPS_64;
  if(ept_info->eptn == USB_EPT0)
  {
    if(ept_info->maxpacket == 0x40)
    {
      mps = USB_EPT0_MPS_64;
    }
    else if(ept_info->maxpacket == 0x20)
    {
      mps = USB_EPT0_MPS_32;
    }
    else if(ept_info->maxpacket == 0x10)
    {
      mps = USB_EPT0_MPS_16;
    }
    else if(ept_info->maxpacket == 0x08)
    {
      mps = USB_EPT0_MPS_8;
    }
  }
  /* endpoint direction is in */
  if(ept_info->inout == EPT_DIR_IN)
  {
    OTG_DEVICE(usbx)->daintmsk |= 1 << ept_info->eptn;
    if(ept_info->eptn == USB_EPT0)
    {
      USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.mps = mps;
    }
    else
    {
      USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.mps = ept_info->maxpacket;
    }
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.eptype = ept_info->trans_type;
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.txfnum = ept_info->eptn;
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.setd0pid = TRUE;
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.usbacept = TRUE;
  }
  /* endpoint direction is out */
  else
  {
    OTG_DEVICE(usbx)->daintmsk |= (1 << ept_info->eptn) << 16;
    if(ept_info->eptn == USB_EPT0)
    {
      USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.mps = mps;
    }
    else
    {
      USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.mps = ept_info->maxpacket;
    }
    USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.eptype = ept_info->trans_type;
    USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.setd0pid = TRUE;
    USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.usbacept = TRUE;
  }
}

/**
  * @brief  close usb endpoint
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval none
  */
void usb_ept_close(otg_global_type *usbx, usb_ept_info *ept_info)
{
  if(ept_info->inout == EPT_DIR_IN)
  {
    OTG_DEVICE(usbx)->daintmsk &= ~(1 << ept_info->eptn);
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.usbacept = FALSE;
  }
  else
  {
    OTG_DEVICE(usbx)->daintmsk &= ~((1 << ept_info->eptn) << 16);
    USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.usbacept = FALSE;
  }
}


/**
  * @brief  set endpoint tx or rx status to stall
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval none
  */
void usb_ept_stall(otg_global_type *usbx, usb_ept_info *ept_info)
{
  if(ept_info->inout == EPT_DIR_IN)
  {
    if(USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.eptena == RESET)
    {
      USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.eptdis = FALSE;
    }
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.stall = SET;
  }
  else
  {
    if(USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.eptena == RESET)
    {
      USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.eptdis = FALSE;
    }
    USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.stall = TRUE;
  }
}

/**
  * @brief  clear endpoint tx or rx status to stall
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  ept_info: endpoint information structure
  * @retval none
  */
void usb_ept_clear_stall(otg_global_type *usbx, usb_ept_info *ept_info)
{
  if(ept_info->inout == EPT_DIR_IN)
  {
    USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.stall = FALSE;
    if(ept_info->trans_type == EPT_INT_TYPE || ept_info->trans_type == EPT_BULK_TYPE)
    {
      USB_INEPT(usbx, ept_info->eptn)->diepctl_bit.setd0pid = TRUE;
    }
  }
  else
  {
    USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.stall = FALSE;
    if(ept_info->trans_type == EPT_INT_TYPE || ept_info->trans_type == EPT_BULK_TYPE)
    {
      USB_OUTEPT(usbx, ept_info->eptn)->doepctl_bit.setd0pid = TRUE;
    }
  }
}

/**
  * @brief  get all out endpoint interrupt bits
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval out endpoint interrupt bits
  */
uint32_t usb_get_all_out_interrupt(otg_global_type *usbx)
{
  uint32_t intsts = OTG_DEVICE(usbx)->daint;
  return ((intsts & (OTG_DEVICE(usbx)->daintmsk)) >> 16);
}

/**
  * @brief  get all in endpoint interrupt bits
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval in endpoint interrupt bits
  */
uint32_t usb_get_all_in_interrupt(otg_global_type *usbx)
{
  uint32_t intsts = OTG_DEVICE(usbx)->daint;
  return ((intsts & (OTG_DEVICE(usbx)->daintmsk)) & 0xFFFF);
}


/**
  * @brief  get out endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  eptn: endpoint number
  * @retval out endpoint interrupt flags
  */
uint32_t usb_ept_out_interrupt(otg_global_type *usbx, uint32_t eptn)
{
  uint32_t intsts = USB_OUTEPT(usbx, eptn)->doepint;
  return (intsts & (OTG_DEVICE(usbx)->doepmsk));
}

/**
  * @brief  get in endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  eptn: endpoint number
  * @retval in endpoint intterupt flags
  */
uint32_t usb_ept_in_interrupt(otg_global_type *usbx, uint32_t eptn)
{
  uint32_t intsts, mask1, mask2;
  mask1 = OTG_DEVICE(usbx)->diepmsk;
  mask2 = OTG_DEVICE(usbx)->diepempmsk;
  mask1 |= ((mask2 >> eptn) & 0x1) << 7;
  intsts = USB_INEPT(usbx, eptn)->diepint & mask1;
  return intsts;
}

/**
  * @brief  clear out endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  eptn: endpoint number
  * @retval flag: interrupt flag
  *         this parameter can be any combination of the following values:
  *         - USB_OTG_DOEPINT_XFERC_FLAG
  *         - USB_OTG_DOEPINT_EPTDISD_FLAG
  *         - USB_OTG_DOEPINT_SETUP_FLAG
  *         - USB_OTG_DOEPINT_OTEPDIS_FLAG
  *         - USB_OTG_DOEPINT_B2BSTUP_FLAG
  */
void usb_ept_out_clear(otg_global_type *usbx, uint32_t eptn, uint32_t flag)
{
  USB_OUTEPT(usbx, eptn)->doepint = flag;
}

/**
  * @brief  clear in endpoint interrupt flag
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  eptn: endpoint number
  * @retval flag: interrupt flag
  *         this parameter can be any combination of the following values:
  *         - USB_OTG_DIEPINT_XFERC_FLAG
  *         - USB_OTG_DIEPINT_EPTDISD_FLAG
  *         - USB_OTG_DIEPINT_TMROC_FLAG
  *         - USB_OTG_DIEPINT_INTTXFE_FLAG
  *         - USB_OTG_DIEPINT_INEPNE_FLAG
  *         - USB_OTG_DIEPINT_TXFE_FLAG
  */
void usb_ept_in_clear(otg_global_type *usbx, uint32_t eptn, uint32_t flag)
{
  USB_INEPT(usbx, eptn)->diepint = flag;
}


/**
  * @brief  set the host assignment address
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  address: host assignment address
  * @retval none
  */
void usb_set_address(otg_global_type *usbx, uint8_t address)
{
  OTG_DEVICE(usbx)->dcfg_bit.devaddr = address;
}

/**
  * @brief  enable endpoint 0 out
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_ept0_start(otg_global_type *usbx)
{
  otg_eptout_type *usb_outept = USB_OUTEPT(usbx, 0);
  usb_outept->doeptsiz = 0;
  usb_outept->doeptsiz_bit.pktcnt = 1;
  usb_outept->doeptsiz_bit.xfersize = 24;
  usb_outept->doeptsiz_bit.rxdpid_setupcnt = 3;
}


/**
  * @brief  endpoint 0 start setup
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_ept0_setup(otg_global_type *usbx)
{
  USB_INEPT(usbx, 0)->diepctl_bit.mps = 0;
  OTG_DEVICE(usbx)->dctl_bit.cgnpinak = FALSE;
}

/**
  * @brief  connect usb device by enable pull-up
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_connect(otg_global_type *usbx)
{
  /* D+ 1.5k pull-up enable */
  OTG_DEVICE(usbx)->dctl_bit.sftdiscon = FALSE;
}

/**
  * @brief  disconnect usb device by disable pull-up
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_disconnect(otg_global_type *usbx)
{
  /* D+ 1.5k pull-up disable */
  OTG_DEVICE(usbx)->dctl_bit.sftdiscon = TRUE;
}


/**
  * @brief  usb remote wakeup set
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_remote_wkup_set(otg_global_type *usbx)
{
  OTG_DEVICE(usbx)->dctl_bit.rwkupsig = TRUE;
}

/**
  * @brief  usb remote wakeup clear
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_remote_wkup_clear(otg_global_type *usbx)
{
  OTG_DEVICE(usbx)->dctl_bit.rwkupsig = FALSE;
}

/**
  * @brief  usb suspend status get
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval usb suspend status
  */
uint8_t usb_suspend_status_get(otg_global_type *usbx)
{
  return OTG_DEVICE(usbx)->dsts_bit.suspsts;
}
#endif

#ifdef OTGFS_USB_HOST
/**
  * @brief  usb port power on
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  state: state (TRUE or FALSE)
  * @retval none
  */
void usb_port_power_on(otg_global_type *usbx, confirm_state state)
{
  otg_host_type *usb_host = OTG_HOST(usbx);
  uint32_t hprt_val = usb_host->hprt;

  hprt_val &= ~(USB_OTG_HPRT_PRTENA | USB_OTG_HPRT_PRTENCHNG |
               USB_OTG_HPRT_PRTOVRCACT | USB_OTG_HPRT_PRTCONDET);

  if(state == TRUE)
  {
    usb_host->hprt = hprt_val | USB_OTG_HPRT_PRTPWR;
  }
  else
  {
    usb_host->hprt = hprt_val & (~USB_OTG_HPRT_PRTPWR);
  }
}

/**
  * @brief  get current frame number
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
uint32_t usbh_get_frame(otg_global_type *usbx)
{
  otg_host_type *usb_host = OTG_HOST(usbx);
  return usb_host->hfnum & 0xFFFF;
}

/**
  * @brief  enable one host channel
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
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
  * @retval none
  */
void usb_hc_enable(otg_global_type *usbx,
                   uint8_t chn,
                   uint8_t ept_num,
                   uint8_t dev_address,
                   uint8_t type,
                   uint16_t maxpacket,
                   uint8_t speed)
{
  otg_hchannel_type *hch = USB_CHL(usbx, chn);
  otg_host_type *usb_host = OTG_HOST(usbx);

  switch(type)
  {
    case EPT_CONTROL_TYPE:
    case EPT_BULK_TYPE:
      hch->hcintmsk |= USB_OTG_HC_XFERCM_INT | USB_OTG_HC_STALLM_INT |
                       USB_OTG_HC_XACTERRM_INT | USB_OTG_HC_NAKM_INT |
                       USB_OTG_HC_DTGLERRM_INT;
      if(ept_num & 0x80)
      {
        hch->hcintmsk_bit.bblerrmsk = TRUE;
      }
      break;
    case EPT_INT_TYPE:
      hch->hcintmsk |= USB_OTG_HC_XFERCM_INT | USB_OTG_HC_STALLM_INT |
                       USB_OTG_HC_XACTERRM_INT | USB_OTG_HC_NAKM_INT |
                       USB_OTG_HC_DTGLERRM_INT | USB_OTG_HC_FRMOVRRUN_INT;
      break;
    case EPT_ISO_TYPE:

      hch->hcintmsk |= USB_OTG_HC_XFERCM_INT | USB_OTG_HC_ACKM_INT |
                       USB_OTG_HC_FRMOVRRUN_INT;
      break;
  }
  usb_host->haintmsk |= 1 << chn;
  usbx->gintmsk_bit.hchintmsk = TRUE;

  hch->hcchar_bit.devaddr = dev_address;
  hch->hcchar_bit.eptnum = ept_num & 0x7F;
  hch->hcchar_bit.eptdir = (ept_num & 0x80)?1:0;
  hch->hcchar_bit.lspddev = (speed == USB_PRTSPD_LOW_SPEED)?1:0;
  hch->hcchar_bit.eptype = type;
  hch->hcchar_bit.mps = maxpacket;

  if(type == EPT_INT_TYPE)
  {
    hch->hcchar_bit.oddfrm = TRUE;
  }
}

/**
  * @brief  host read channel interrupt
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval interrupt flag
  */
uint32_t usb_hch_read_interrupt(otg_global_type *usbx)
{
  otg_host_type *usb_host = OTG_HOST(usbx);
  return usb_host->haint & 0xFFFF;
}

/**
  * @brief  disable host
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @retval none
  */
void usb_host_disable(otg_global_type *usbx)
{
  uint32_t i_index = 0, count = 0;
  otg_hchannel_type *hch;
  otg_host_type *usb_host = OTG_HOST(usbx);

  usbx->gahbcfg_bit.glbintmsk = FALSE;
  usb_flush_rx_fifo(usbx);
  usb_flush_tx_fifo(usbx, 0x10);

  for(i_index = 0; i_index < 16; i_index ++)
  {
    hch = USB_CHL(usbx, i_index);
    hch->hcchar_bit.chdis = TRUE;
    hch->hcchar_bit.chena = FALSE;
    hch->hcchar_bit.eptdir = 0;
  }

  for(i_index = 0; i_index < 16; i_index ++)
  {
    hch = USB_CHL(usbx, i_index);
    hch->hcchar_bit.chdis = TRUE;
    hch->hcchar_bit.chena = TRUE;
    hch->hcchar_bit.eptdir = 0;
    do
    {
      if(count ++ > 1000)
        break;
    }while(hch->hcchar_bit.chena);
  }
  usb_host->haint = 0xFFFFFFFF;
  usbx->gintsts = 0xFFFFFFFF;
  usbx->gahbcfg_bit.glbintmsk = TRUE;
}

/**
  * @brief  halt channel
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  chn: channel number
  * @retval none
  */
void usb_hch_halt(otg_global_type *usbx, uint8_t chn)
{
  uint32_t count = 0;
  otg_hchannel_type *usb_chh = USB_CHL(usbx, chn);
  otg_host_type *usb_host = OTG_HOST(usbx);

  /* endpoint type is control or bulk */
  if(usb_chh->hcchar_bit.eptype == EPT_CONTROL_TYPE ||
     usb_chh->hcchar_bit.eptype == EPT_BULK_TYPE)
  {
    usb_chh->hcchar_bit.chdis = TRUE;
    if((usbx->gnptxsts_bit.nptxqspcavail) == 0)
    {
      usb_chh->hcchar_bit.chena = FALSE;
      usb_chh->hcchar_bit.chena = TRUE;
      do
      {
        if(count ++ > 1000)
          break;
      }while(usb_chh->hcchar_bit.chena == SET);
    }
    else
    {
      usb_chh->hcchar_bit.chena = TRUE;
    }
  }
  else
  {
    usb_chh->hcchar_bit.chdis = TRUE;
    if((usb_host->hptxsts_bit.ptxqspcavil) == 0)
    {
      usb_chh->hcchar_bit.chena = FALSE;
      usb_chh->hcchar_bit.chena = TRUE;
      do
      {
        if(count ++ > 1000)
          break;
      }while(usb_chh->hcchar_bit.chena == SET);
    }
    else
    {
      usb_chh->hcchar_bit.chena = TRUE;
    }
  }
}
/**
  * @brief  select full or low speed clock
  * @param  usbx: to select the otgfs peripheral.
  *         this parameter can be one of the following values:
  *         - OTG1_GLOBAL
  * @param  clk: clock frequency
  * @retval none
  */
void usbh_fsls_clksel(otg_global_type *usbx, uint8_t clk)
{
  otg_host_type *usb_host = OTG_HOST(usbx);

  usb_host->hcfg_bit.fslspclksel = clk;
  if(clk == USB_HCFG_CLK_6M)
  {
    usb_host->hfir = 6000;
  }
  else
  {
    usb_host->hfir = 48000;
  }
}
#endif


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
