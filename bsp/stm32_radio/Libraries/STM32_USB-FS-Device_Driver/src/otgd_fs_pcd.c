/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : otgd_fs_pcd.c
* Author             : MCD Application Team
* Version            : V3.1.0
* Date               : 10/30/2009
* Description        : Peripheral Device Interface low layer.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef STM32F10X_CL

#include "usb_lib.h"
#include "otgd_fs_cal.h"
#include "otgd_fs_pcd.h"

USB_OTG_PCD_DEV USB_OTG_PCD_dev;

extern USB_OTG_CORE_REGS     core_regs;
/*******************************************************************************
* Function Name  : OTGD_FS_PCD_Init
* Description    : Initialize the USB Device portion of the driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void OTGD_FS_PCD_Init(void)
{
  uint32_t i;
  USB_OTG_EP *ep;

  ep = &USB_OTG_PCD_dev.ep0;
  USB_OTG_PCD_dev.ep0state = 0;

  /* Init ep structure */
  ep->num = 0;
  ep->tx_fifo_num = 0;

  /* Control until ep is actvated */
  ep->type = EP_TYPE_CTRL;
  ep->maxpacket = MAX_PACKET_SIZE;

  ep->xfer_buff = 0;
  ep->xfer_len = 0;

  for (i = 1; i < MAX_TX_FIFOS ; i++)
  {
    ep = &USB_OTG_PCD_dev.in_ep[i-1];

    /* Init ep structure */
    ep->is_in = 1;
    ep->num = i;
    ep->tx_fifo_num = i;

    /* Control until ep is actvated */
    ep->type = EP_TYPE_CTRL;
    ep->maxpacket = MAX_PACKET_SIZE;
    ep->xfer_buff = 0;
    ep->xfer_len = 0;
  }

  for (i = 1; i < MAX_TX_FIFOS; i++)
  {
    ep = &USB_OTG_PCD_dev.out_ep[i-1];

    /* Init ep structure */
    ep->is_in = 0;
    ep->num = i;
    ep->tx_fifo_num = i;

    /* Control until ep is activated */
    ep->type = EP_TYPE_CTRL;
    ep->maxpacket = MAX_PACKET_SIZE;
    ep->xfer_buff = 0;
    ep->xfer_len = 0;
  }

  USB_OTG_PCD_dev.ep0.maxpacket = MAX_EP0_SIZE;
  USB_OTG_PCD_dev.ep0.type = EP_TYPE_CTRL;

}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP_Open
* Description    : Configure an Endpoint
* Input          : None
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_PCD_EP_Open(EP_DESCRIPTOR *epdesc)
{
  USB_OTG_EP *ep;


  if ((0x80 & epdesc->bEndpointAddress) != 0)
  {
    ep = OTGD_FS_PCD_GetInEP(epdesc->bEndpointAddress & 0x7F);
  }
  else
  {
    ep = OTGD_FS_PCD_GetOutEP(epdesc->bEndpointAddress & 0x7F);
  }

  ep->num   = epdesc->bEndpointAddress & 0x7F;
  ep->is_in = (0x80 & epdesc->bEndpointAddress) != 0;
  ep->maxpacket = epdesc->wMaxPacketSize;
  ep->type = epdesc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;

  if (ep->is_in)
  {
    /* Assign a Tx FIFO */
    ep->tx_fifo_num = ep->num;
  }
  
  /* Set initial data PID. */
  if ((epdesc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK )
  {
    ep->data_pid_start = 0;
  }

  OTGD_FS_EPActivate(ep );

  return 0;
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP_Close
* Description    : Called when an EP is disabled
* Input          : Endpoint address.
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_PCD_EP_Close(uint8_t  ep_addr)
{

  USB_OTG_EP *ep;

  if ((0x80 & ep_addr) != 0)
  {
    ep = OTGD_FS_PCD_GetInEP(ep_addr & 0x7F);
  }
  else
  {
    ep = OTGD_FS_PCD_GetOutEP(ep_addr & 0x7F);
  }

  ep->num   = ep_addr & 0x7F;
  ep->is_in = (0x80 & ep_addr) != 0;

  OTGD_FS_EPDeactivate(ep );
  return 0;
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP_Read
* Description    : Read data from Fifo
* Input          : Endpoint address.
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t OTGD_FS_PCD_EP_Read (uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len)
{
  USB_OTG_EP *ep;
  uint32_t i;

  ep = OTGD_FS_PCD_GetOutEP(ep_addr & 0x7F);

  /* copy received data into application buffer */
  for (i = 0 ; i < buf_len ; i++)
  {
    pbuf[i] = ep->xfer_buff[i];
  }

  /*setup and start the Xfer */
  ep->xfer_buff = pbuf;
  ep->xfer_len = buf_len;
  ep->xfer_count = 0;
  ep->is_in = 0;
  ep->num = ep_addr & 0x7F;

  if ( ep->num == 0 )
  {
    OTGD_FS_EP0StartXfer(ep);
  }
  else if (USB_OTG_PCD_dev.ep0state == 0)
  {
    OTGD_FS_EPStartXfer( ep );
  }

  return 0;
}

/*******************************************************************************
* Function Name  : USBF_EP_Write
* Description    : Read data from Fifo
* Input          : ep
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t  OTGD_FS_PCD_EP_Write (uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len)
{
  USB_OTG_EP *ep;

  ep = OTGD_FS_PCD_GetInEP(ep_addr & 0x7f);

  /* assign data to EP structure buffer */
  ep->xfer_buff = pbuf;

  /* Setup and start the Transfer */
  ep->xfer_count = 0;
  ep->xfer_len = buf_len;
  ep->is_in = 1;
  ep->num = ep_addr & 0x7F;
  
  if ( ep->num == 0 )
  {
    OTGD_FS_EP0StartXfer(ep);
  }
  else if (USB_OTG_PCD_dev.ep0state == 0)
  {
    OTGD_FS_EPStartXfer( ep );
  }

  return 0;
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP_Stall
* Description    : Stall an endpoint.
* Input          : Endpoint Address.
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t  OTGD_FS_PCD_EP_Stall (uint8_t ep_addr)
{
  USB_OTG_EP *ep;

  if ((0x80 & ep_addr) != 0)
  {
    ep = OTGD_FS_PCD_GetInEP(ep_addr & 0x7F);
  }
  else
  {
    ep = OTGD_FS_PCD_GetOutEP(ep_addr & 0x7F);
  }

  ep->num   = ep_addr & 0x7F;
  ep->is_in = ((ep_addr & 0x80) == 0x80) ? 1 : 0;

  OTGD_FS_EPSetStall(ep);
  return (0);
}
/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP_ClrStall
* Description    : Clear stall condition on endpoints.
* Input          : Endpoint Address.
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t  OTGD_FS_PCD_EP_ClrStall (uint8_t ep_addr)
{

  USB_OTG_EP *ep;

  if ((0x80 & ep_addr) != 0)
  {
    ep = OTGD_FS_PCD_GetInEP(ep_addr & 0x7F);
  }
  else
  {
    ep = OTGD_FS_PCD_GetOutEP(ep_addr & 0x7F);
  }

  ep->num   = ep_addr & 0x7F;
  ep->is_in = ((ep_addr & 0x80) == 0x80) ? 1 : 0;

  OTGD_FS_EPClearStall(ep);

  return (0);
}

/*******************************************************************************
* Function Name  : USBF_FCD_EP_Flush()
* Description    : This Function flushes the buffer.
* Input          : Endpoint Address.
* Output         : None
* Return         : status
*******************************************************************************/
uint32_t  OTGD_FS_PCD_EP_Flush (uint8_t ep_addr)
{

  uint8_t  is_out;
  uint8_t  ep_nbr;

  ep_nbr   = ep_addr & 0x7F;
  is_out = ((ep_addr & 0x80) == 0x80) ? 0 : 1;

  if (is_out == 0)
  {
    OTGD_FS_FlushTxFifo(ep_nbr);
  }
  else
  {
    OTGD_FS_FlushRxFifo();
  }
  OTGD_FS_PCD_EP_ClrStall(ep_addr);
  return (0);
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP_SetAddress
* Description    : This Function set USB device address
* Input          : The new device Address to be set.
* Output         : None
* Return         : status
*******************************************************************************/
void  OTGD_FS_PCD_EP_SetAddress (uint8_t address)
{

  USB_OTG_dev_cfg_data dcfg;
  dcfg.d32 = 0;

  dcfg.b.devaddr = address;
  MODIFY_REG32( &core_regs.dev_regs->dev_cfg, 0, dcfg.d32);
}


/*******************************************************************************
* Function Name  : OTGD_FS_PCD_GetInEP
* Description    : This function returns pointer to IN EP struct with number ep_num
* Input          : Endpoint Number.
* Output         : None
* Return         : status
*******************************************************************************/
USB_OTG_EP* OTGD_FS_PCD_GetInEP(uint32_t ep_num)
{
  uint32_t i;
  if (ep_num == 0)
  {
    return &USB_OTG_PCD_dev.ep0;
  }
  else
  {
    for (i = 0; i < MAX_TX_FIFOS; ++i)
    {
      if (USB_OTG_PCD_dev.in_ep[i].num == ep_num)
        return &USB_OTG_PCD_dev.in_ep[i];
    }
    return 0;
  }
}
/*******************************************************************************
* Function Name  : USBF_GetOutEP
* Description    : returns pointer to OUT EP struct with number ep_num
* Input          : Endpoint Number.
* Output         : None
* Return         : USBF_EP
*******************************************************************************/
USB_OTG_EP* OTGD_FS_PCD_GetOutEP(uint32_t ep_num)
{
  uint32_t i;
  if (ep_num == 0)
  {
    return &USB_OTG_PCD_dev.ep0;
  }
  else
  {
    for (i = 0; i < MAX_TX_FIFOS; ++i)
    {
      if (USB_OTG_PCD_dev.out_ep[i].num == ep_num)
        return &USB_OTG_PCD_dev.out_ep[i];
    }
    return 0;
  }
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_DevConnect
* Description    : Connect device
* Input         : None
* Output         : None
* Return         : status
*******************************************************************************/
void  OTGD_FS_PCD_DevConnect(void)
{

  USB_OTG_dev_ctl_data dctl;

  dctl.d32 = READ_REG32(&core_regs.dev_regs->dev_ctl);

  /* Connect device */
  dctl.b.sftdiscon  = 0;
  WRITE_REG32(&core_regs.dev_regs->dev_ctl, dctl.d32);
  mDELAY(25);
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_DevDisconnect
* Description    : Disconnect device
* Input         : None
* Output         : None
* Return         : status
*******************************************************************************/
void  OTGD_FS_PCD_DevDisconnect (void)
{

  USB_OTG_dev_ctl_data dctl;

  dctl.d32 = READ_REG32(&core_regs.dev_regs->dev_ctl);

  /* Disconnect device for 20ms */
  dctl.b.sftdiscon  = 1;
  WRITE_REG32(&core_regs.dev_regs->dev_ctl, dctl.d32);
  mDELAY(25);
}

/*******************************************************************************
* Function Name  : OTGD_FS_PCD_EP0_OutStart
* Description    : Configures EPO to receive SETUP packets.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void OTGD_FS_PCD_EP0_OutStart(void)
{

  USB_OTG_dev_ep_txfer_size0_data doeptsize0;

  doeptsize0.d32 = 0;
  doeptsize0.b.supcnt = 3;
  doeptsize0.b.pktcnt = 1;
  doeptsize0.b.xfersize = 8 * 3;

  WRITE_REG32( &core_regs.outep_regs[0]->dev_out_ep_txfer_siz, doeptsize0.d32 );

}

#endif /* STM32F10X_CL */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

