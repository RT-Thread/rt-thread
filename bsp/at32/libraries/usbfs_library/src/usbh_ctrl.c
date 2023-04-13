/**
  **************************************************************************
  * @file     usbh_ctrl.c
  * @brief    usb host control request
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
#include "usbh_ctrl.h"
#include "usbh_core.h"
#include "usb_std.h"

#ifdef USE_OTG_HOST_MODE

/** @defgroup USBH_drivers_control
  * @brief usb host drivers control
  * @{
  */

/** @defgroup USBH_ctrl_private_functions
  * @{
  */

/* control timeout 5s */
#define CTRL_TIMEOUT          5000

/**
  * @brief  usb host control send setup packet
  * @param  uhost: to the structure of usbh_core_type
  * @param  buffer: usb control setup send buffer
  * @param  hc_num: channel number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_send_setup(usbh_core_type *uhost, uint8_t *buffer, uint8_t hc_num)
{
  uhost->hch[hc_num].dir = 0;
  uhost->hch[hc_num].data_pid = HCH_PID_SETUP;
  uhost->hch[hc_num].trans_buf = buffer;
  uhost->hch[hc_num].trans_len = 8; /*setup */

  return usbh_in_out_request(uhost, hc_num);
}

/**
  * @brief  usb host control receive data from device
  * @param  uhost: to the structure of usbh_core_type
  * @param  buffer: usb control receive data buffer
  * @param  length: usb control receive data length
  * @param  hc_num: channel number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_recv_data(usbh_core_type *uhost, uint8_t *buffer,
                            uint16_t length, uint16_t hc_num)
{
  uhost->hch[hc_num].dir = 1;
  uhost->hch[hc_num].data_pid = HCH_PID_DATA1;
  uhost->hch[hc_num].trans_buf = buffer;
  uhost->hch[hc_num].trans_len = length;

  return usbh_in_out_request(uhost, hc_num);
}

/**
  * @brief  usb host control send data packet
  * @param  uhost: to the structure of usbh_core_type
  * @param  buffer: usb control send data buffer
  * @param  length: usb control send data length
  * @param  hc_num: channel number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_send_data(usbh_core_type *uhost, uint8_t *buffer,
                            uint16_t length, uint16_t hc_num)
{
  uhost->hch[hc_num].dir = 0;
  uhost->hch[hc_num].trans_buf = buffer;
  uhost->hch[hc_num].trans_len = length;

  if(length == 0)
  {
    uhost->hch[uhost->ctrl.hch_out].toggle_out = 1;
  }
  if(uhost->hch[uhost->ctrl.hch_out].toggle_out == 0)
  {
    uhost->hch[hc_num].data_pid = HCH_PID_DATA0;
  }
  else
  {
    uhost->hch[hc_num].data_pid = HCH_PID_DATA1;
  }
  return usbh_in_out_request(uhost, hc_num);
}

/**
  * @brief  usb host control setup request handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_setup_handler(usbh_core_type *uhost)
{
  usbh_ctrl_send_setup(uhost, (uint8_t *)(&uhost->ctrl.setup),
                       uhost->ctrl.hch_out);
  uhost->ctrl.state = CONTROL_SETUP_WAIT;
  return USB_OK;
}

/**
  * @brief  usb host control setup request wait handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  timeout: pointer of wait timeout
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_setup_wait_handler(usbh_core_type *uhost, uint32_t *timeout)
{
  urb_sts_type urb_state;
  usb_sts_type status = USB_WAIT;
  uint8_t dir;
  urb_state = uhost->urb_state[uhost->ctrl.hch_out];
  if(urb_state == URB_DONE)
  {
    dir = uhost->ctrl.setup.bmRequestType &  USB_REQUEST_DIR_MASK;
    if(uhost->ctrl.setup.wLength != 0)
    {
      *timeout = DATA_STAGE_TIMEOUT;
      if(dir == USB_DIR_D2H) //in
      {
        uhost->ctrl.state = CONTROL_DATA_IN;
      }
      else //out
      {
        uhost->ctrl.state = CONTROL_DATA_OUT;
      }
    }
    else
    {
      *timeout = NODATA_STAGE_TIMEOUT;
      if(dir == USB_DIR_D2H) //no data, send status
      {
        uhost->ctrl.state = CONTROL_STATUS_OUT;
      }
      else //out
      {
        uhost->ctrl.state = CONTROL_STATUS_IN;
      }
    }
    uhost->ctrl.timer = uhost->timer;
    status = USB_OK;
  }
  else if(urb_state == URB_ERROR || urb_state == URB_NOTREADY)
  {
    uhost->ctrl.state = CONTROL_ERROR;
    uhost->ctrl.sts = CTRL_XACTERR;
    status = USB_ERROR;
  }
  else
  {
    /* wait nak timeout 5s*/
    if(uhost->timer - uhost->ctrl.timer > CTRL_TIMEOUT)
    {
      uhost->ctrl.state = CONTROL_ERROR;
      uhost->ctrl.sts = CTRL_XACTERR;
      status = USB_ERROR;
    }
  }
  return status;
}

/**
  * @brief  usb host control data in request handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_data_in_handler(usbh_core_type *uhost)
{
  usb_sts_type status = USB_OK;
  usbh_ctrl_recv_data(uhost, uhost->ctrl.buffer,
                      uhost->ctrl.len,
                      uhost->ctrl.hch_in);
  uhost->ctrl.state = CONTROL_DATA_IN_WAIT;

  return status;
}

/**
  * @brief  usb host control data in wait handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  timeout: wait timeout
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_data_in_wait_handler(usbh_core_type *uhost, uint32_t timeout)
{
  usb_sts_type status = USB_OK;
  urb_sts_type urb_state;
  urb_state = uhost->urb_state[uhost->ctrl.hch_in];

  if(urb_state == URB_DONE)
  {
    uhost->ctrl.state = CONTROL_STATUS_OUT;
  }
  else if(urb_state == URB_STALL)
  {
    uhost->ctrl.state = CONTROL_STALL;
  }
  else if(urb_state == URB_ERROR)
  {
    uhost->ctrl.state = CONTROL_ERROR;
  }
  else
  {
    /* wait nak timeout 5s*/
    if(uhost->timer - uhost->ctrl.timer > CTRL_TIMEOUT)
    {
      uhost->ctrl.state = CONTROL_ERROR;
      uhost->ctrl.sts = CTRL_XACTERR;
      status = USB_ERROR;
    }

  }
  return status;
}

/**
  * @brief  usb host control data out request handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_data_out_handler(usbh_core_type *uhost)
{
  usb_sts_type status = USB_OK;
  uhost->hch[uhost->ctrl.hch_out].toggle_out = 1;

  usbh_ctrl_send_data(uhost, uhost->ctrl.buffer,
                      uhost->ctrl.len,
                      uhost->ctrl.hch_out);
  uhost->ctrl.state = CONTROL_DATA_OUT_WAIT;

  return status;
}

/**
  * @brief  usb host control data out wait handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  timeout: wait timeout
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_data_out_wait_handler(usbh_core_type *uhost, uint32_t timeout)
{
  usb_sts_type status = USB_OK;
  urb_sts_type urb_state;
  urb_state = uhost->urb_state[uhost->ctrl.hch_out];
  if(urb_state == URB_DONE)
  {
    uhost->ctrl.state = CONTROL_STATUS_IN;
  }
  else if(urb_state == URB_STALL)
  {
    uhost->ctrl.state = CONTROL_STALL;
  }
  else if(urb_state == URB_ERROR)
  {
    uhost->ctrl.state = CONTROL_ERROR;
  }
  else if(urb_state == URB_NOTREADY)
  {
    uhost->ctrl.state = CONTROL_DATA_OUT;
  }

  /* wait nak timeout 5s*/
  if((uhost->timer - uhost->ctrl.timer > CTRL_TIMEOUT) && (urb_state == URB_NOTREADY))
  {
    uhost->ctrl.state = CONTROL_ERROR;
    uhost->ctrl.sts = CTRL_XACTERR;
    status = USB_ERROR;
  }
  return status;
}

/**
  * @brief  usb host control status data in handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_status_in_handler(usbh_core_type *uhost)
{
  usb_sts_type status = USB_OK;
  usbh_ctrl_recv_data(uhost, 0, 0,
                      uhost->ctrl.hch_in);
  uhost->ctrl.state = CONTROL_STATUS_IN_WAIT;


  return status;
}

/**
  * @brief  usb host control status data in wait handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  timeout: wait timeout
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_status_in_wait_handler(usbh_core_type *uhost, uint32_t timeout)
{
  usb_sts_type status = USB_OK;
  urb_sts_type urb_state;
  urb_state = uhost->urb_state[uhost->ctrl.hch_in];
  if(urb_state == URB_DONE)
  {
    uhost->ctrl.state = CONTROL_COMPLETE;
  }
  else if(urb_state == URB_STALL)
  {
    uhost->ctrl.state = CONTROL_STALL;
    status = USB_NOT_SUPPORT;
  }
  else if(urb_state == URB_ERROR)
  {
    uhost->ctrl.state = CONTROL_ERROR;
  }
  else
  {
    /* wait nak timeout 5s*/
    if(uhost->timer - uhost->ctrl.timer > CTRL_TIMEOUT)
    {
      uhost->ctrl.state = CONTROL_ERROR;
      uhost->ctrl.sts = CTRL_XACTERR;
      status = USB_ERROR;
    }
  }
  return status;
}

/**
  * @brief  usb host control status data out wait handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_status_out_handler(usbh_core_type *uhost)
{
  usb_sts_type status = USB_OK;
  uhost->hch[uhost->ctrl.hch_out].toggle_out ^= 1;

  usbh_ctrl_send_data(uhost, 0, 0, uhost->ctrl.hch_out);
  uhost->ctrl.state = CONTROL_STATUS_OUT_WAIT;

  return status;
}

/**
  * @brief  usb host control status data out wait handler
  * @param  uhost: to the structure of usbh_core_type
  * @param  timeout: wait timeout
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_status_out_wait_handler(usbh_core_type *uhost, uint32_t timeout)
{
  usb_sts_type status = USB_OK;
  urb_sts_type urb_state;
  urb_state = uhost->urb_state[uhost->ctrl.hch_out];
  if(urb_state == URB_DONE)
  {
    uhost->ctrl.state = CONTROL_COMPLETE;
  }
  else if(urb_state == URB_STALL)
  {
    uhost->ctrl.state = CONTROL_STALL;
  }
  else if(urb_state == URB_ERROR)
  {
    uhost->ctrl.state = CONTROL_ERROR;
  }
  else if(urb_state == URB_NOTREADY)
  {
    uhost->ctrl.state = CONTROL_STATUS_OUT;
  }
  /* wait nak timeout 5s*/
  if((uhost->timer - uhost->ctrl.timer > CTRL_TIMEOUT) && (urb_state == URB_NOTREADY))
  {
    uhost->ctrl.state = CONTROL_ERROR;
    uhost->ctrl.sts = CTRL_XACTERR;
    status = USB_ERROR;
  }
  return status;
}

/**
  * @brief  usb host control error handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_error_handler(usbh_core_type *uhost)
{
  usb_sts_type status =  USB_WAIT;
  if(++ uhost->ctrl.err_cnt <= USBH_MAX_ERROR_COUNT)
  {
    uhost->ctrl.state = CONTROL_SETUP;
  }
  else
  {
    uhost->ctrl.sts = CTRL_FAIL;
    uhost->global_state = USBH_ERROR_STATE;
    uhost->ctrl.err_cnt = 0;
    status = USB_ERROR;
  }
  return status;
}

/**
  * @brief  usb host control stall handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval usb_sts_type
  */
usb_sts_type usbh_ctrl_stall_handler(usbh_core_type *uhost)
{
  return USB_NOT_SUPPORT;
}

/**
  * @brief  usb host control complete handler
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_complete_handler(usbh_core_type *uhost)
{
  return USB_OK;
}

/**
  * @brief  usb host control transfer loop function
  * @param  uhost: to the structure of usbh_core_type
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_transfer_loop(usbh_core_type *uhost)
{
  usb_sts_type status = USB_WAIT;
  static uint32_t timeout = 0;
  uhost->ctrl.sts = CTRL_START;

  switch(uhost->ctrl.state)
  {
    case CONTROL_SETUP:
      usbh_ctrl_setup_handler(uhost);
      uhost->ctrl.timer = uhost->timer;
      break;

    case CONTROL_SETUP_WAIT:
      usbh_ctrl_setup_wait_handler(uhost, &timeout);
      break;

    case CONTROL_DATA_IN:
      usbh_ctrl_data_in_handler(uhost);
      break;

    case CONTROL_DATA_IN_WAIT:
      usbh_ctrl_data_in_wait_handler(uhost, timeout);
      break;

    case CONTROL_DATA_OUT:
      usbh_ctrl_data_out_handler(uhost);
      break;

    case CONTROL_DATA_OUT_WAIT:
      usbh_ctrl_data_out_wait_handler(uhost, timeout);
      break;

    case CONTROL_STATUS_IN:
      usbh_ctrl_status_in_handler(uhost);
      break;

    case CONTROL_STATUS_IN_WAIT:
      usbh_ctrl_status_in_wait_handler(uhost, timeout);
      break;

    case CONTROL_STATUS_OUT:
      usbh_ctrl_status_out_handler(uhost);
      break;

    case CONTROL_STATUS_OUT_WAIT:
      usbh_ctrl_status_out_wait_handler(uhost, timeout);
      break;
    case CONTROL_STALL:
      status = usbh_ctrl_stall_handler(uhost);
      break;
    case CONTROL_ERROR:
      status = usbh_ctrl_error_handler(uhost);
      break;
    case CONTROL_COMPLETE:
      status = usbh_ctrl_complete_handler(uhost);
      break;

    default:
      break;
  }

  return status;
}

/**
  * @brief  usb host control request
  * @param  uhost: to the structure of usbh_core_type
  * @param  buffer: usb request buffer
  * @param  length: usb request length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_ctrl_request(usbh_core_type *uhost, uint8_t *buffer, uint16_t length)
{
  usb_sts_type status = USB_OK;
  if(uhost->req_state == CMD_SEND)
  {
    uhost->req_state = CMD_WAIT;
    uhost->ctrl.buffer = buffer;
    uhost->ctrl.len = length;
    uhost->ctrl.state = CONTROL_SETUP;
  }
  return status;
}

/**
  * @brief  usb host get device descriptor
  * @param  uhost: to the structure of usbh_core_type
  * @param  length: get descriptor request length
  * @param  req_type: usb request type
  * @param  wvalue: usb wvalue
  * @param  buffer: request buffer
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_get_descriptor(usbh_core_type *uhost, uint16_t length,
                            uint8_t req_type, uint16_t wvalue,
                            uint8_t *buffer)
{
  usb_sts_type status;
  uhost->ctrl.setup.bmRequestType = USB_DIR_D2H | req_type;
  uhost->ctrl.setup.bRequest = USB_STD_REQ_GET_DESCRIPTOR;
  uhost->ctrl.setup.wValue = wvalue;
  uhost->ctrl.setup.wLength = length;

  if((wvalue & 0xFF00) == ((USB_DESCIPTOR_TYPE_STRING << 8) & 0xFF00))
  {
    uhost->ctrl.setup.wIndex = 0x0409;
  }
  else
  {
    uhost->ctrl.setup.wIndex = 0;
  }

  status = usbh_ctrl_request(uhost, buffer, length);
  return status;
}

/**
  * @brief  usb host parse device descriptor
  * @param  uhost: to the structure of usbh_core_type
  * @param  buffer: usb device descriptor buffer
  * @param  length: usb device descriptor length
  * @retval status: usb_sts_type status
  */
void usbh_parse_dev_desc(usbh_core_type *uhost, uint8_t *buffer, uint16_t length)
{
  usbh_dev_desc_type *desc = &(uhost->dev);

  desc->dev_desc.bLength = *(uint8_t *)(buffer + 0);
  desc->dev_desc.bDescriptorType = *(uint8_t *)(buffer + 1);
  desc->dev_desc.bcdUSB = SWAPBYTE(buffer + 2);
  desc->dev_desc.bDeviceClass = *(uint8_t *)(buffer + 4);
  desc->dev_desc.bDeviceSubClass = *(uint8_t *)(buffer + 5);
  desc->dev_desc.bDeviceProtocol = *(uint8_t *)(buffer + 6);
  desc->dev_desc.bMaxPacketSize0 = *(uint8_t *)(buffer + 7);

  if(length > 8)
  {
    desc->dev_desc.idVendor = SWAPBYTE(buffer + 8);
    desc->dev_desc.idProduct = SWAPBYTE(buffer + 10);
    desc->dev_desc.bcdDevice = SWAPBYTE(buffer + 12);
    desc->dev_desc.iManufacturer = *(uint8_t *)(buffer + 14);
    desc->dev_desc.iProduct = *(uint8_t *)(buffer + 15);
    desc->dev_desc.iSerialNumber = *(uint8_t *)(buffer + 16);
    desc->dev_desc.bNumConfigurations = *(uint8_t *)(buffer + 17);
  }
}

/**
  * @brief  usb host get next header
  * @param  buffer: usb data buffer
  * @param  index_len: pointer of index len
  * @retval status: usb_sts_type status
  */
usb_header_desc_type *usbh_get_next_header(uint8_t *buf, uint16_t *index_len)
{
  *index_len += ((usb_header_desc_type *)buf)->bLength;
  return (usb_header_desc_type *)
          ((uint8_t *)buf + ((usb_header_desc_type *)buf)->bLength);
}

/**
  * @brief  usb host parse interface descriptor
  * @param  intf: usb interface description type
  * @param  buf: interface description data buffer
  * @retval none
  */
void usbh_parse_interface_desc(usb_interface_desc_type *intf, uint8_t *buf)
{
  intf->bLength                          = *(uint8_t *)buf;
  intf->bDescriptorType                  = *(uint8_t *)(buf + 1);
  intf->bInterfaceNumber                 = *(uint8_t *)(buf + 2);
  intf->bAlternateSetting                = *(uint8_t *)(buf + 3);
  intf->bNumEndpoints                    = *(uint8_t *)(buf + 4);
  intf->bInterfaceClass                  = *(uint8_t *)(buf + 5);
  intf->bInterfaceSubClass               = *(uint8_t *)(buf + 6);
  intf->bInterfaceProtocol               = *(uint8_t *)(buf + 7);
  intf->iInterface                       = *(uint8_t *)(buf + 8);
}

/**
  * @brief  usb host parse endpoint descriptor
  * @param  ept_desc: endpoint type
  * @param  buf: endpoint description data buffer
  * @retval none
  */
void usbh_parse_endpoint_desc(usb_endpoint_desc_type *ept_desc, uint8_t *buf)
{
  ept_desc->bLength                      = *(uint8_t *)(buf + 0);
  ept_desc->bDescriptorType              = *(uint8_t *)(buf + 1);
  ept_desc->bEndpointAddress             = *(uint8_t *)(buf + 2);
  ept_desc->bmAttributes                 = *(uint8_t *)(buf + 3);
  ept_desc->wMaxPacketSize               = SWAPBYTE(buf + 4);
  ept_desc->bInterval                    = *(uint8_t *)(buf + 6);
}

/**
  * @brief  usb host parse configure descriptor
  * @param  uhost: to the structure of usbh_core_type
  * @param  buffer: configure buffer
  * @param  length: configure length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_parse_configure_desc(usbh_core_type *uhost,
                                  uint8_t *buffer, uint16_t length)
{
  usb_cfg_desc_type *cfg_desc = &(uhost->dev.cfg_desc);
  usb_interface_desc_type *intf_desc;
  usb_endpoint_desc_type *ept_desc;
  usb_header_desc_type *desc;
  uint16_t index_len;
  uint8_t index_intf = 0;
  uint8_t index_ept = 0;

  desc = (usb_header_desc_type *)buffer;
  cfg_desc->cfg.bLength                      = *(uint8_t *)buffer;
  cfg_desc->cfg.bDescriptorType              = *(uint8_t *)(buffer + 1);
  cfg_desc->cfg.wTotalLength                 = SWAPBYTE(buffer + 2);
  cfg_desc->cfg.bNumInterfaces               = *(uint8_t *)(buffer + 4);
  cfg_desc->cfg.bConfigurationValue          = *(uint8_t *)(buffer + 5);
  cfg_desc->cfg.iConfiguration               = *(uint8_t *)(buffer + 6);
  cfg_desc->cfg.bmAttributes                 = *(uint8_t *)(buffer + 7);
  cfg_desc->cfg.bMaxPower                    = *(uint8_t *)(buffer + 8);

  if(length > USB_DEVICE_CFG_DESC_LEN)
  {
    index_len = USB_DEVICE_CFG_DESC_LEN;

    while((index_intf < USBH_MAX_INTERFACE) && index_len < cfg_desc->cfg.wTotalLength)
    {
      desc = usbh_get_next_header((uint8_t *)desc, &index_len);
      if(desc->bDescriptorType == USB_DESCIPTOR_TYPE_INTERFACE)
      {
        index_ept = 0;
        intf_desc = &cfg_desc->interface[index_intf].interface;
        usbh_parse_interface_desc(intf_desc, (uint8_t *)desc);

        while(index_ept < intf_desc->bNumEndpoints && index_len < cfg_desc->cfg.wTotalLength)
        {
          desc = usbh_get_next_header((uint8_t *)desc, &index_len);
          if(desc->bDescriptorType == USB_DESCIPTOR_TYPE_ENDPOINT)
          {
            ept_desc = &(cfg_desc->interface[index_intf].endpoint[index_ept]);
            usbh_parse_endpoint_desc(ept_desc, (uint8_t *)desc);
            index_ept ++;
          }
        }
        index_intf ++;
      }
    }
  }
  return USB_OK;
}

/**
  * @brief  usb host find interface
  * @param  uhost: to the structure of usbh_core_type
  * @param  class_code: class code
  * @param  sub_class: subclass code
  * @param  protocol: prtocol code
  * @retval idx: interface index
  */
uint8_t usbh_find_interface(usbh_core_type *uhost, uint8_t class_code, uint8_t sub_class, uint8_t protocol)
{
  uint8_t idx = 0;
  usb_itf_desc_type *usbitf;
  for(idx = 0; idx < uhost->dev.cfg_desc.cfg.bNumInterfaces; idx ++)
  {
    usbitf = &uhost->dev.cfg_desc.interface[idx];
    if(((usbitf->interface.bInterfaceClass == class_code) || (class_code == 0xFF)) &&
      ((usbitf->interface.bInterfaceSubClass == sub_class) || (sub_class == 0xFF)) &&
      ((usbitf->interface.bInterfaceProtocol == protocol) || (protocol == 0xFF))
       )
    {
      return idx;
    }
  }
  return 0xFF;
}

/**
  * @brief  usbh parse string descriptor
  * @param  src: string source pointer
  * @param  dest: string destination pointer
  * @param  length: string length
  * @retval none
  */
void usbh_parse_string_desc(uint8_t *src, uint8_t *dest, uint16_t length)
{
  uint16_t len;
  uint16_t i_index;

  if(src[1] == USB_DESCIPTOR_TYPE_STRING)
  {
    len = ((src[0] - 2) <= length ? (src[0] - 2) : length);
    src += 2;
    for(i_index = 0; i_index < len; i_index += 2)
    {
      *dest = src[i_index];
      dest ++;
    }
    *dest = 0;
  }
}

/**
  * @brief  usb host get device descriptor
  * @param  uhost: to the structure of usbh_core_type
  * @param  length: get device descriptor length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_get_device_descriptor(usbh_core_type *uhost, uint16_t length)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  uint16_t wvalue;

  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;
  wvalue = (USB_DESCIPTOR_TYPE_DEVICE << 8) & 0xFF00;

  status = usbh_get_descriptor(uhost, length, bm_req,
                               wvalue, uhost->rx_buffer);
  return status;
}

/**
  * @brief  usb host get configure descriptor
  * @param  uhost: to the structure of usbh_core_type
  * @param  length: get device configure length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_get_configure_descriptor(usbh_core_type *uhost, uint16_t length)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  uint16_t wvalue;

  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;
  wvalue = (USB_DESCIPTOR_TYPE_CONFIGURATION << 8) & 0xFF00;

  status = usbh_get_descriptor(uhost, length, bm_req,
                               wvalue, uhost->rx_buffer);

  return status;
}

/**
  * @brief  usb host get string descriptor
  * @param  uhost: to the structure of usbh_core_type
  * @param  string_id: string id
  * @param  buffer: receive data buffer
  * @param  length: get device string length
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_get_sting_descriptor(usbh_core_type *uhost, uint8_t string_id,
                                  uint8_t *buffer, uint16_t length)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  uint16_t wvalue;

  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;
  wvalue = (USB_DESCIPTOR_TYPE_STRING << 8) | string_id;

  status = usbh_get_descriptor(uhost, length, bm_req,
                               wvalue, uhost->rx_buffer);

  return status;
}

/**
  * @brief  usb host set configurtion
  * @param  uhost: to the structure of usbh_core_type
  * @param  config: usb configuration
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_set_configuration(usbh_core_type *uhost, uint16_t config)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;

  uhost->ctrl.setup.bmRequestType = USB_DIR_H2D | bm_req;
  uhost->ctrl.setup.bRequest = USB_STD_REQ_SET_CONFIGURATION;
  uhost->ctrl.setup.wValue = config;
  uhost->ctrl.setup.wLength = 0;
  uhost->ctrl.setup.wIndex = 0;
  status = usbh_ctrl_request(uhost, 0, 0);
  return status;
}

/**
  * @brief  usb host set device address
  * @param  uhost: to the structure of usbh_core_type
  * @param  address: device address
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_set_address(usbh_core_type *uhost, uint8_t address)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;

  uhost->ctrl.setup.bmRequestType = USB_DIR_H2D | bm_req;
  uhost->ctrl.setup.bRequest = USB_STD_REQ_SET_ADDRESS;
  uhost->ctrl.setup.wValue = (uint16_t)address;
  uhost->ctrl.setup.wLength = 0;
  uhost->ctrl.setup.wIndex = 0;
  status = usbh_ctrl_request(uhost, 0, 0);
  return status;
}

/**
  * @brief  usb host set interface
  * @param  uhost: to the structure of usbh_core_type
  * @param  ept_num: endpoint number
  * @param  altsetting: alter setting
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_set_interface(usbh_core_type *uhost, uint8_t ept_num, uint8_t altsetting)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  bm_req = USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD;

  uhost->ctrl.setup.bmRequestType = USB_DIR_H2D | bm_req;
  uhost->ctrl.setup.bRequest = USB_STD_REQ_SET_INTERFACE;
  uhost->ctrl.setup.wValue = (uint16_t)altsetting;
  uhost->ctrl.setup.wLength = 0;
  uhost->ctrl.setup.wIndex = ept_num;
  status = usbh_ctrl_request(uhost, 0, 0);
  return status;
}

/**
  * @brief  usb host set feature
  * @param  uhost: to the structure of usbh_core_type
  * @param  feature: feature number
  * @param  index: index number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_set_feature(usbh_core_type *uhost, uint8_t feature, uint16_t index)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;

  uhost->ctrl.setup.bmRequestType = USB_DIR_H2D | bm_req;
  uhost->ctrl.setup.bRequest = USB_STD_REQ_SET_FEATURE;
  uhost->ctrl.setup.wValue = (uint16_t)feature;
  uhost->ctrl.setup.wLength = 0;
  uhost->ctrl.setup.wIndex = index;
  status = usbh_ctrl_request(uhost, 0, 0);
  return status;
}


/**
  * @brief  usb host clear device feature
  * @param  uhost: to the structure of usbh_core_type
  * @param  feature: feature number
  * @param  index: index number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_clear_dev_feature(usbh_core_type *uhost, uint8_t feature, uint16_t index)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  bm_req = USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;

  uhost->ctrl.setup.bmRequestType = USB_DIR_H2D | bm_req;
  uhost->ctrl.setup.bRequest = USB_STD_REQ_CLEAR_FEATURE;
  uhost->ctrl.setup.wValue = (uint16_t)feature;
  uhost->ctrl.setup.wLength = 0;
  uhost->ctrl.setup.wIndex = index;
  status = usbh_ctrl_request(uhost, 0, 0);
  return status;
}

/**
  * @brief  usb host clear endpoint feature
  * @param  uhost: to the structure of usbh_core_type
  * @param  ept_num: endpoint number
  * @param  hc_num: host channel number
  * @retval status: usb_sts_type status
  */
usb_sts_type usbh_clear_ept_feature(usbh_core_type *uhost, uint8_t ept_num, uint8_t hc_num)
{
  usb_sts_type status = USB_WAIT;
  uint8_t bm_req;
  if(uhost->ctrl.state == CONTROL_IDLE )
  {
    bm_req = USB_REQ_RECIPIENT_ENDPOINT | USB_REQ_TYPE_STANDARD;

    uhost->ctrl.setup.bmRequestType = USB_DIR_H2D | bm_req;
    uhost->ctrl.setup.bRequest = USB_STD_REQ_CLEAR_FEATURE;
    uhost->ctrl.setup.wValue = USB_FEATURE_EPT_HALT;
    uhost->ctrl.setup.wLength = 0;
    uhost->ctrl.setup.wIndex = ept_num;
    usbh_ctrl_request(uhost, 0, 0);
  }
  if(usbh_ctrl_result_check(uhost, CONTROL_IDLE, ENUM_IDLE) == USB_OK)
  {
    status = USB_OK;
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
