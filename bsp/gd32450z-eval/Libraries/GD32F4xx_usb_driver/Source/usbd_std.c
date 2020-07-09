/*!
    \file  usbd_std.c
    \brief USB 2.0 standard handler driver
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#include "usbd_std.h"
#include "usb_core.h"

static usbd_status_enum usbd_standard_request     (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static usbd_status_enum usbd_device_class_request (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static usbd_status_enum usbd_vendor_request       (usb_core_handle_struct *pudev, usb_device_req_struct *req);

static void usbd_setup_request_parse(usb_core_handle_struct *pudev, usb_device_req_struct *req);

static void usbd_getdescriptor  (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_setaddress     (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_setconfig      (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_getconfig      (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_getstatus      (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_setfeature     (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_clrfeature     (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_reserved       (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_setdescriptor  (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_getinterface   (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_setinterface   (usb_core_handle_struct *pudev, usb_device_req_struct *req);
static void usbd_synchframe     (usb_core_handle_struct *pudev, usb_device_req_struct *req);

static uint8_t* usbd_device_descriptor_get (usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen);
static uint8_t* usbd_configuration_descriptor_get (usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen);
static uint8_t* usbd_string_descriptor_get (usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen);

static void (*StandardDeviceRequest[])(usb_core_handle_struct *pudev, usb_device_req_struct *req) =
{
    usbd_getstatus,
    usbd_clrfeature,
    usbd_reserved,
    usbd_setfeature,
    usbd_reserved,
    usbd_setaddress,
    usbd_getdescriptor,
    usbd_setdescriptor,
    usbd_getconfig,
    usbd_setconfig,
    usbd_getinterface,
    usbd_setinterface,
    usbd_synchframe,
};

/* get standard descriptor handler */
static uint8_t* (*standard_descriptor_get[])(usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen) = 
{
    usbd_device_descriptor_get,
    usbd_configuration_descriptor_get,
    usbd_string_descriptor_get
};

/*!
    \brief      USB setup stage processing
    \param[in]  pudev: pointer to USB device instance
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum usbd_setup_transaction(usb_core_handle_struct *pudev)
{
    usb_device_req_struct req;

    usbd_setup_request_parse(pudev, &req);

    switch (req.bmRequestType & USB_REQ_MASK) {
        /* standard device request */
        case USB_STANDARD_REQ:
            usbd_standard_request(pudev, &req);
            break;
        /* device class request */
        case USB_CLASS_REQ:
            usbd_device_class_request(pudev, &req);
            break;
        /* vendor defined request */
        case USB_VENDOR_REQ:
            usbd_vendor_request(pudev, &req);
            break;
        default:
            usbd_ep_stall(pudev, req.bmRequestType & 0x80U);
            break;
    }

    return USBD_OK;
}

/*!
    \brief      data out stage processing
    \param[in]  pudev: pointer to USB device instance
    \param[in]  ep_id: endpoint identifier(0..7)
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum usbd_out_transaction (usb_core_handle_struct *pudev, uint8_t endp_num)
{
    usb_ep_struct *ep;

    if (0U == endp_num) {
        ep = &pudev->dev.out_ep[0];

        if (USB_CTRL_DATA_OUT == pudev->dev.ctl_status) {
            if (pudev->dev.remain_len > ep->endp_mps) {
                pudev->dev.remain_len -= ep->endp_mps;

                if (1U == pudev->cfg.dma_enable) {
                    /* update buffer location */
                    ep->xfer_buff += ep->endp_mps;
                }

                usbd_ep_rx (pudev, 
                            0U, 
                            ep->xfer_buff, 
                            (uint16_t)USB_MIN(pudev->dev.remain_len, ep->endp_mps));
            } else {
                if (USB_STATUS_CONFIGURED == pudev->dev.status) {
                    pudev->dev.class_data_handler(pudev, USBD_RX, 0U);
                }

                usbd_ctlstatus_tx(pudev);
            }
        }
    } else if (USB_STATUS_CONFIGURED == pudev->dev.status) {
        pudev->dev.class_data_handler(pudev, USBD_RX, endp_num);
    } else {
        /* no operation */
    }

    return USBD_OK;
}

/*!
    \brief      data in stage processing
    \param[in]  pudev: pointer to USB device instance
    \param[in]  ep_id: endpoint identifier(0..7)
    \param[out] none
    \retval     USB device operation status
*/
usbd_status_enum usbd_in_transaction (usb_core_handle_struct *pudev, uint8_t endp_num)
{
    usb_ep_struct *ep;

    if (0U == endp_num) {
        ep = &pudev->dev.in_ep[0];

        if (USB_CTRL_DATA_IN == pudev->dev.ctl_status) {
            if (pudev->dev.remain_len > ep->endp_mps) {
                pudev->dev.remain_len -= ep->endp_mps;

                if (1U == pudev->cfg.dma_enable) {
                    /* update buffer location */
                    ep->xfer_buff += ep->endp_mps;
                }

                usbd_ep_tx (pudev, 0U, ep->xfer_buff, pudev->dev.remain_len);
            } else {
                /* last packet is MPS multiple, so send ZLP packet */
                if ((pudev->dev.sum_len % ep->endp_mps == 0U) &&
                     (pudev->dev.sum_len >= ep->endp_mps) &&
                      (pudev->dev.sum_len < pudev->dev.ctl_len)) {
                    usbd_ep_tx (pudev, 0U, NULL, 0U);
                    pudev->dev.ctl_len = 0U;
                } else {
                    if (USB_STATUS_CONFIGURED == pudev->dev.status) {
                        pudev->dev.class_data_handler(pudev, USBD_TX, 0U);
                    }

                    usbd_ctlstatus_rx(pudev);
                }
            }
        }
    } else if (USB_STATUS_CONFIGURED == pudev->dev.status) {
        pudev->dev.class_data_handler(pudev, USBD_TX, endp_num);
    } else {
        /* no operation */
    }

    return USBD_OK;
}

/*!
    \brief      handle USB standard device request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     USB device operation status
*/
static usbd_status_enum  usbd_standard_request (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    /* call device request handle function */
    (*StandardDeviceRequest[req->bRequest])(pudev, req);

    return USBD_OK;
}

/*!
    \brief      handle USB device class request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device class request
    \param[out] none
    \retval     USB device operation status
*/
static usbd_status_enum  usbd_device_class_request (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    usbd_status_enum ret = USBD_OK;

    switch (pudev->dev.status) {
        case USB_STATUS_CONFIGURED:
            if (LOWBYTE(req->wIndex) <= USBD_ITF_MAX_NUM) {
                ret = (usbd_status_enum)(pudev->dev.class_req_handler(pudev, req));

                if ((0U == req->wLength) && (USBD_OK == ret)) {
                    /* no data stage */
                    usbd_ctlstatus_tx(pudev);
                }
            } else {
                usbd_enum_error(pudev, req);
            }
            break;

        default:
            usbd_enum_error(pudev, req);
            break;
    }

    return ret;
}

/*!
    \brief      handle USB vendor request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB vendor request
    \param[out] none
    \retval     USB device operation status
*/
static usbd_status_enum  usbd_vendor_request (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    /* added by user... */

    return USBD_OK;
}

/*!
    \brief      no operation, just for reserved
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_reserved (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    /* no operation... */
}

/*!
    \brief      get the device descriptor
    \brief[in]  index: no use
    \param[in]  none
    \param[out] pLen: data length pointer
    \retval     descriptor buffer pointer
*/
static uint8_t* usbd_device_descriptor_get (usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen)
{
    *pLen = pudev->dev.dev_desc[0];

    return pudev->dev.dev_desc;
}

/*!
    \brief      get the configuration descriptor
    \brief[in]  index: no use
    \param[in]  none
    \param[out] pLen: data length pointer
    \retval     descriptor buffer pointer
*/
static uint8_t* usbd_configuration_descriptor_get (usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen)
{
    *pLen = pudev->dev.config_desc[2];

    return pudev->dev.config_desc;
}

/*!
    \brief      get string descriptor
    \param[in]  index: string descriptor index
    \param[in]  pLen: pointer to string length
    \param[out] none
    \retval     none
*/
static uint8_t* usbd_string_descriptor_get (usb_core_handle_struct *pudev, uint8_t index, uint16_t *pLen)
{
    uint8_t *desc = pudev->dev.strings[index];

    *pLen = desc[0];

    return desc;
}

/*!
    \brief      handle Get_Status request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_getstatus (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
}

/*!
    \brief      handle USB Clear_Feature request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_clrfeature (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    uint8_t ep_addr = 0U;

    switch (req->bmRequestType & USB_REQTYPE_MASK) {
        case USB_REQTYPE_DEVICE:
            switch (pudev->dev.status) {
                case USB_STATUS_ADDRESSED:
                case USB_STATUS_CONFIGURED:
                    if (USB_FEATURE_REMOTE_WAKEUP == req->wValue) {
                        pudev->dev.remote_wakeup = 0U;
                        pudev->dev.class_req_handler(pudev, req);

                        usbd_ctlstatus_tx(pudev);
                    }
                    break;

                default:
                    usbd_enum_error(pudev, req);
                    break;
            }
            break;
        case USB_REQTYPE_INTERFACE:
            switch (pudev->dev.status) {
                case USB_STATUS_ADDRESSED:
                    usbd_enum_error(pudev, req);
                    break;
                case USB_STATUS_CONFIGURED:
                    if (LOWBYTE(req->wIndex) <= USBD_ITF_MAX_NUM) {
                        /* no operation */
                    } else {
                        usbd_enum_error(pudev, req);
                    }
                    break;
                default:
                    break;
            }
            break;
        case USB_REQTYPE_ENDPOINT:
            ep_addr = LOWBYTE(req->wIndex);

            switch (pudev->dev.status) {
                case USB_STATUS_ADDRESSED:
                    if (IS_NOT_EP0(ep_addr)) {
                        usbd_ep_stall(pudev, ep_addr);
                    }
                    break;
                case USB_STATUS_CONFIGURED:
                    if (USB_FEATURE_ENDP_HALT == req->wValue) {
                        if (IS_NOT_EP0(ep_addr)) {
                            usbd_ep_clear_stall(pudev, ep_addr);

                            pudev->dev.class_req_handler(pudev, req);
                        }
                    }
                    usbd_ctlstatus_tx(pudev);
                    break;
                default:
                    break;
            }
            break;
        default:
            usbd_enum_error(pudev, req);
            break;
    }
}

/*!
    \brief      handle USB Set_Feature request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_setfeature (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    uint8_t ep_addr = 0U;
    __IO uint32_t DctlrStatus;

    switch (req->bmRequestType & USB_REQ_MASK) {
        case USB_REQTYPE_DEVICE:
            switch (pudev->dev.status) {
                case USB_STATUS_ADDRESSED:
                case USB_STATUS_CONFIGURED:
                    if (USB_FEATURE_REMOTE_WAKEUP == req->wValue) {
                        pudev->dev.remote_wakeup = 1U;
                        pudev->dev.class_req_handler(pudev, req);

                        usbd_ctlstatus_tx(pudev);
                    } else if ((req->wValue == USB_FEATURE_TEST_MODE) && 
                                (0U == (req->wIndex & 0xFFU))) {
                        DctlrStatus = USB_DCTL;

                        usbd_ctlstatus_tx(pudev);
                    } else {
                        /* no operation */
                    }
                    break;
                default:
                    break;
            }
            break;
        case USB_REQTYPE_INTERFACE:
            switch (pudev->dev.status) {
                case USB_STATUS_ADDRESSED:
                    usbd_enum_error(pudev, req);
                    break;
                case USB_STATUS_CONFIGURED:
                    if (LOWBYTE(req->wIndex) <= USBD_ITF_MAX_NUM) {
                        /* no operation */
                    } else {
                        usbd_enum_error(pudev, req);
                    }
                    break;
                default:
                    break;
            }
            break;
        case USB_REQTYPE_ENDPOINT:
            switch (pudev->dev.status) {
                case USB_STATUS_ADDRESSED:
                    if (IS_NOT_EP0(ep_addr)) {
                        usbd_ep_stall(pudev, ep_addr);
                    }
                    break;
                case USB_STATUS_CONFIGURED:
                    if (USB_FEATURE_ENDP_HALT == req->wValue) {
                        if (IS_NOT_EP0(ep_addr)) {
                            usbd_ep_stall(pudev, ep_addr);
                        }
                    }
                    pudev->dev.class_req_handler(pudev, req);

                    usbd_ctlstatus_tx(pudev);
                    break;
                default:
                    break;
            }
            break;
        default:
            usbd_enum_error(pudev, req);
            break;
    }
}

/*!
    \brief      handle USB Set_Address request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_setaddress (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    uint8_t DevAddr;

    if ((0U == req->wIndex) && (0U == req->wLength)) {
        DevAddr = (uint8_t)(req->wValue) & 0x7FU;

        if (USB_STATUS_CONFIGURED == pudev->dev.status) {
            usbd_enum_error(pudev, req);
        } else {
            USB_SET_DEVADDR((uint32_t)DevAddr);

            usbd_ctlstatus_tx(pudev);

            if (0U != DevAddr) {
                pudev->dev.status = USB_STATUS_ADDRESSED;
            } else {
                pudev->dev.status = USB_STATUS_DEFAULT;
            }
        }
    } else {
        usbd_enum_error(pudev, req);
    }
}

/*!
    \brief      handle USB Get_Descriptor request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_getdescriptor (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    if (USB_REQTYPE_DEVICE == (req->bmRequestType & USB_REQTYPE_MASK)) {
        uint8_t desc_index = (uint8_t)(req->wValue >> 8U);

        if (desc_index <= 0x03U) {
            uint16_t len;
            uint8_t *pbuf;

            /* call corresponding descriptor get function */
            pbuf = standard_descriptor_get[desc_index - 1U](pudev, (uint8_t)(req->wValue) & 0xFFU, &len);

            if ((0U != len) && (0U != req->wLength)) {
                len = USB_MIN(len, req->wLength);

                if ((1U == desc_index) && (64U == req->wLength)) {
                    len = 8U;
                }

                usbd_ctltx(pudev, pbuf, len);
            }
        } else {
            usbd_enum_error(pudev, req);
        }
    } else if (USB_REQTYPE_INTERFACE == (req->bmRequestType & USB_REQTYPE_MASK)) {
        pudev->dev.class_req_handler(pudev, req);
    } else {
        /* no operation */
    }
}

/*!
    \brief      handle USB Set_Descriptor request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_setdescriptor (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    /* no handle... */
}

/*!
    \brief      handle USB Get_Configuration request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_getconfig (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    uint32_t USBD_default_config = 0U;

    if (1U != req->wLength) {
        usbd_enum_error(pudev, req);
    } else {
        switch (pudev->dev.status) {
            case USB_STATUS_ADDRESSED:
                usbd_ctltx(pudev, (uint8_t *)&USBD_default_config, 1U);
                break;
            case USB_STATUS_CONFIGURED:
                usbd_ctltx(pudev, &pudev->dev.config_num, 1U);
                break;
            default:
                usbd_enum_error(pudev, req);
                break;
        }
    }
}

/*!
    \brief      handle USB Set_Configuration request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_setconfig (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    static uint8_t  cfgidx;

    cfgidx = (uint8_t)(req->wValue);

    if (cfgidx > USBD_CFG_MAX_NUM) {
        usbd_enum_error(pudev, req);
    } else {
        switch (pudev->dev.status) {
            case USB_STATUS_ADDRESSED:
                if (cfgidx) {
                    pudev->dev.config_num = cfgidx;
                    pudev->dev.status = USB_STATUS_CONFIGURED;
                    pudev->dev.class_init(pudev, cfgidx);
                }

                usbd_ctlstatus_tx(pudev);
                break;
            case USB_STATUS_CONFIGURED:
                if (0U == cfgidx) {
                    pudev->dev.status = USB_STATUS_ADDRESSED;
                    pudev->dev.config_num = cfgidx;
                    pudev->dev.class_deinit(pudev, cfgidx);
                } else if (cfgidx != pudev->dev.config_num) {
                    /* clear old configuration */
                    pudev->dev.class_deinit(pudev, pudev->dev.config_num);

                    /* set new configuration */
                    pudev->dev.config_num = cfgidx;
                    pudev->dev.class_init(pudev, cfgidx);
                } else {
                    /* no operation */
                }

                usbd_ctlstatus_tx(pudev);
                break;
            default:
                usbd_enum_error(pudev, req);
                break;
        }
    }
}

/*!
    \brief      handle USB Get_Interface request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_getinterface (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    pudev->dev.class_req_handler(pudev, req);
}

/*!
    \brief      handle USB Set_Interface request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_setinterface (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    pudev->dev.class_req_handler(pudev, req);
}

/*!
    \brief      handle USB SynchFrame request
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void  usbd_synchframe (usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    /* no handle... */
}

/*!
    \brief      decode setup data packet
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
static void usbd_setup_request_parse(usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    uint8_t *psetup = pudev->dev.setup_packet;
  
    req->bmRequestType = *psetup;
    req->bRequest      = *(uint8_t *)(psetup + 1U);
    req->wValue        = SWAPBYTE (psetup + 2U);
    req->wIndex        = SWAPBYTE (psetup + 4U);
    req->wLength       = SWAPBYTE (psetup + 6U);

    pudev->dev.ctl_len = req->wLength;
}

/*!
    \brief      handle USB low level error event
    \param[in]  pudev: pointer to USB device instance
    \param[in]  req: pointer to USB device request
    \param[out] none
    \retval     none
*/
void usbd_enum_error(usb_core_handle_struct *pudev, usb_device_req_struct *req)
{
    usbd_ep_stall(pudev, 0x80U);
    usbd_ep_stall(pudev, 0x00U);
    usb_ep0_startout(pudev);
}
