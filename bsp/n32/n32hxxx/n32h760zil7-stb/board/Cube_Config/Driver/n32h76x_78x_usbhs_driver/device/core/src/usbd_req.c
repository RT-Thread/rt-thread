/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file usbd_req.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbd_req.h"
#include "usbd_ioreq.h"
#include "usbd_desc.h"


#ifdef USB_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint32_t USBD_ep_status __ALIGN_END  = 0;

#ifdef USB_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint32_t  USBD_default_cfg __ALIGN_END  = 0;

#ifdef USB_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_HS_INTERNAL_DMA_ENABLED */
__ALIGN_BEGIN uint32_t  USBD_cfg_status __ALIGN_END  = 0;


static void USBD_GetDescriptor(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static void USBD_SetAddress(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static void USBD_SetConfig(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static void USBD_GetConfig(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static void USBD_GetStatus(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static void USBD_SetFeature(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static void USBD_ClrFeature(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req);
static uint8_t USBD_GetLen(uint8_t *buf);

extern uint32_t SET_TEST_MODE;

/**
*\*\name   USBD_StdDevReq.
*\*\fun    Handle standard usb device requests
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return USBD_OK
**/
USBD_Status USBD_StdDevReq (USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    USBD_Status ret = USBD_OK;

    switch (req->bRequest)
    {
        case USB_REQ_GET_DESCRIPTOR:
          USBD_GetDescriptor (USBx, req) ;
          break;

        case USB_REQ_SET_ADDRESS:
          USBD_SetAddress(USBx, req);
          break;

        case USB_REQ_SET_CONFIGURATION:
          USBD_SetConfig (USBx , req);
          break;

        case USB_REQ_GET_CONFIGURATION:
          USBD_GetConfig (USBx , req);
          break;

        case USB_REQ_GET_STATUS:
          USBD_GetStatus (USBx , req);
          break;

        case USB_REQ_SET_FEATURE:
          USBD_SetFeature (USBx , req);
          break;

        case USB_REQ_CLEAR_FEATURE:
          USBD_ClrFeature (USBx , req);
          break;

        default:
          USBD_CtrlError(USBx , req);
          break;
    }
    return ret;
}

/**
*\*\name   USBD_StdItfReq.
*\*\fun    Handle standard usb interface requests
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return USBD_OK
**/
USBD_Status USBD_StdItfReq(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    USBD_Status ret = USBD_OK;

    switch (USBx->dev.device_status)
    {
        case USB_CONFIGURED:
            if (LOBYTE(req->wIndex) <= USBD_ITF_MAX_NUM)
            {
                USBx->dev.class_cb->Setup (USBx, req);
                if((req->wLength == 0) && (ret == USBD_OK))
                {
                    USBD_CtrlSendStatus(USBx);
                }
            }
            else
            {
                USBD_CtrlError(USBx , req);
            }
            break;

        default:
            USBD_CtrlError(USBx , req);
          break;
    }
    return ret;
}

/**
*\*\name   USBD_StdEPReq.
*\*\fun    Handle standard usb endpoint requests
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return USBD_OK
**/
USBD_Status USBD_StdEPReq(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    uint8_t   ep_addr;
    USBD_Status ret = USBD_OK;

    ep_addr  = LOBYTE(req->wIndex);

    /* Check the class specific requests before going to standard request */
    if ((req->bmRequest & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_CLASS)
    {
        USBx->dev.class_cb->Setup (USBx, req);
        return ret;
    }

    switch (req->bRequest)
    {
        case USB_REQ_SET_FEATURE :
            switch (USBx->dev.device_status)
            {
                case USB_ADDRESSED:
                    if ((ep_addr != 0x00) && (ep_addr != 0x80))
                    {
                        USBDEV_EP_Stall(USBx , ep_addr);
                    }
                    break;

                case USB_CONFIGURED:
                if (req->wValue == USB_FEATURE_EP_HALT)
                {
                    if ((ep_addr != 0x00) && (ep_addr != 0x80))
                    {
                        USBDEV_EP_Stall(USBx , ep_addr);
                    }
                }
                USBx->dev.class_cb->Setup(USBx, req);
                USBD_CtrlSendStatus(USBx);
                break;

                default:
                    USBD_CtrlError(USBx , req);
                break;
            }
            break;

        case USB_REQ_CLEAR_FEATURE :

            switch (USBx->dev.device_status)
            {
                case USB_ADDRESSED:
                if ((ep_addr != 0x00) && (ep_addr != 0x80))
                {
                    USBDEV_EP_Stall(USBx , ep_addr);
                }
                break;

                case USB_CONFIGURED:
                if (req->wValue == USB_FEATURE_EP_HALT)
                {
                    if ((ep_addr != 0x00) && (ep_addr != 0x80))
                    {
                        USBDEV_EP_ClrStall(USBx , ep_addr);
                        USBx->dev.class_cb->Setup (USBx, req);
                    }
                    USBD_CtrlSendStatus(USBx);
                }
                break;

                default:
                    USBD_CtrlError(USBx , req);
                break;
            }
        break;

        case USB_REQ_GET_STATUS:
            switch (USBx->dev.device_status)
            {
                case USB_ADDRESSED:
                    if ((ep_addr != 0x00) && (ep_addr != 0x80))
                    {
                        USBDEV_EP_Stall(USBx , ep_addr);
                    }
                break;

                case USB_CONFIGURED:
                    if ((ep_addr & 0x80)== 0x80)
                    {
                        if(USBx->dev.in_ep[ep_addr & 0x7F].is_stall)
                        {
                            USBD_ep_status = 0x0001;
                        }
                        else
                        {
                            USBD_ep_status = 0x0000;
                        }
                    }
                    else if ((ep_addr & 0x80)== 0x00)
                    {
                        if(USBx->dev.out_ep[ep_addr].is_stall)
                        {
                            USBD_ep_status = 0x0001;
                        }
                        else
                        {
                            USBD_ep_status = 0x0000;
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                    USBD_CtrlSendData (USBx, (uint8_t *)&USBD_ep_status, 2);
                break;

                default:
                    USBD_CtrlError(USBx , req);
                break;
            }
        break;

        default:
        break;
    }
    return ret;
}

/**
*\*\name   USBD_GetDescriptor.
*\*\fun    Handle standard usb Descriptor requests
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return USBD_OK
**/
static void USBD_GetDescriptor(USB_CORE_MODULE  *USBx, USB_SETUP_REQ *req)
{
    uint16_t len;
    uint8_t *pbuf;
    len = req->wLength ;

    switch (req->wValue >> 8)
    {
#if (USBD_LPM_ENABLED == 1)
    case USB_DESC_TYPE_BOS:
        pbuf = USBx->pDesc->GetBOSDescriptor(USBx->dev_speed, &len);
    break;
#endif
    case USB_DESC_TYPE_DEVICE:
        pbuf = USBx->dev.user_device->GetDeviceDescriptor(USBx->cfg.speed, &len);
    break;

    case USB_DESC_TYPE_CONFIGURATION:
        pbuf = (uint8_t *)USBx->dev.class_cb->GetConfigDescriptor(USBx->cfg.speed, &len);
        if(USBx->cfg.speed == USB_SPEED_FULL)
        {
            pbuf   = (uint8_t *)USBx->dev.class_cb->GetOtherConfigDescriptor(USBx->cfg.speed, &len);
        }
        pbuf[1] = USB_DESC_TYPE_CONFIGURATION;
        USBx->dev.pConfig_descriptor = pbuf;
    break;

    case USB_DESC_TYPE_STRING:
        switch ((uint8_t)(req->wValue))
        {
            case USBD_IDX_LANGID_STR:
                pbuf = USBx->dev.user_device->GetLangIDStrDescriptor(USBx->cfg.speed, &len);
            break;

            case USBD_IDX_MFC_STR:
                pbuf = USBx->dev.user_device->GetManufacturerStrDescriptor(USBx->cfg.speed, &len);
            break;

            case USBD_IDX_PRODUCT_STR:
                pbuf = USBx->dev.user_device->GetProductStrDescriptor(USBx->cfg.speed, &len);
            break;

            case USBD_IDX_SERIAL_STR:
                pbuf = USBx->dev.user_device->GetSerialStrDescriptor(USBx->cfg.speed, &len);
            break;

            case USBD_IDX_CONFIG_STR:
                pbuf = USBx->dev.user_device->GetConfigurationStrDescriptor(USBx->cfg.speed, &len);
            break;

            case USBD_IDX_INTERFACE_STR:
                pbuf = USBx->dev.user_device->GetInterfaceStrDescriptor(USBx->cfg.speed, &len);
            break;

            default:
#ifdef  USB_SUPPORT_USER_STRING_DESC
                pbuf = USBx->dev.class_cb->GetUserStrDescriptor(USBx->cfg.speed, (req->wValue) , &len);
            break;
#else
            USBD_CtrlError(USBx , req);
            return;
#endif /* USBD_CtrlError(USBx , req)*/
        }
    break;
    case USB_DESC_TYPE_DEVICE_QUALIFIER:
        if(USBx->cfg.speed == USB_SPEED_HIGH)
        {
            pbuf = (uint8_t *)USBx->dev.class_cb->GetConfigDescriptor(USBx->cfg.speed, &len);

            USBD_DeviceQualifierDesc[4]= pbuf[14];
            USBD_DeviceQualifierDesc[5]= pbuf[15];
            USBD_DeviceQualifierDesc[6]= pbuf[16];

            pbuf = USBD_DeviceQualifierDesc;
            len  = USB_LEN_DEV_QUALIFIER_DESC;
            break;
        }
        else
        {
            USBD_CtrlError(USBx , req);
            return;
        }
    case USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION:
        if(USBx->cfg.speed == USB_SPEED_HIGH)
        {
            pbuf   = (uint8_t *)USBx->dev.class_cb->GetOtherConfigDescriptor(USBx->cfg.speed, &len);
            pbuf[1] = USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION;
            break;
        }
        else
        {
            USBD_CtrlError(USBx , req);
            return;
        }

    default:
        USBD_CtrlError(USBx , req);
    
    return;
    }
    if((len != 0)&& (req->wLength != 0))
    {
        len = MIN(len , req->wLength);
        USBD_CtrlSendData (USBx, pbuf, len);
    }
}

/**
*\*\name   USBD_SetAddress.
*\*\fun    Set device address
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
static void USBD_SetAddress(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    uint8_t  dev_addr;

    if ((req->wIndex == 0) && (req->wLength == 0))
    {
        dev_addr = (uint8_t)(req->wValue) & 0x7F;

        if (USBx->dev.device_status == USB_CONFIGURED)
        {
            USBD_CtrlError(USBx , req);
        }
        else
        {
            USBx->dev.device_address = dev_addr;
            USBDEV_EP_SetAddress(USBx, dev_addr);
            USBD_CtrlSendStatus(USBx);

            if (dev_addr != 0)
            {
                USBx->dev.device_status  = USB_ADDRESSED;
            }
            else
            {
                USBx->dev.device_status  = USB_DEFAULT;
            }
        }
    }
    else
    {
        USBD_CtrlError(USBx , req);
    }
}

/**
*\*\name   USBD_SetConfig.
*\*\fun    Handle Set device configuration request
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
static void USBD_SetConfig(USB_CORE_MODULE  *USBx, USB_SETUP_REQ *req)
{
    static uint8_t  cfgidx;

    cfgidx = (uint8_t)(req->wValue);

    if (cfgidx > USBD_CFG_MAX_NUM )
    {
        USBD_CtrlError(USBx , req);
    }
    else
    {
        switch (USBx->dev.device_status)
        {
            case USB_ADDRESSED:
                if (cfgidx)
                {
                    USBx->dev.device_config = cfgidx;
                    USBx->dev.device_status = USB_CONFIGURED;
                    USBD_SetCfg(USBx, cfgidx);
                    USBD_CtrlSendStatus(USBx);
                }
                else
                {
                    USBD_CtrlSendStatus(USBx);
                }
            break;

            case USB_CONFIGURED:
            if (cfgidx == 0)
            {
                USBx->dev.device_status = USB_ADDRESSED;
                USBx->dev.device_config = cfgidx;
                USBD_ClrCfg(USBx, cfgidx);
                USBD_CtrlSendStatus(USBx);
            }
            else if (cfgidx != USBx->dev.device_config)
            {
                /* Clear old configuration */
                USBD_ClrCfg(USBx, USBx->dev.device_config);

                /* set new configuration */
                USBx->dev.device_config = cfgidx;
                USBD_SetCfg(USBx, cfgidx);
                USBD_CtrlSendStatus(USBx);
            }
            else
            {
                USBD_CtrlSendStatus(USBx);
            }
            break;

            default:
                USBD_CtrlError(USBx , req);
            break;
        }
    }
}

/**
*\*\name   USBD_GetConfig.
*\*\fun    Handle Get device configuration request
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
static void USBD_GetConfig(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    if (req->wLength != 1)
    {
        USBD_CtrlError(USBx , req);
    }
    else
    {
        switch (USBx->dev.device_status )
        {
            case USB_ADDRESSED:
                USBD_CtrlSendData (USBx, (uint8_t *)&USBD_default_cfg, 1);
                break;

            case USB_CONFIGURED:
                USBD_CtrlSendData (USBx, &USBx->dev.device_config, 1);
                break;

            default:
                USBD_CtrlError(USBx , req);
                break;
        }
    }
}

/**
*\*\name   USBD_GetStatus.
*\*\fun    Handle Get Status request
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
static void USBD_GetStatus(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    switch (USBx->dev.device_status)
    {
        case USB_ADDRESSED:
        case USB_CONFIGURED:

#ifdef USBD_SELF_POWERED
            USBD_cfg_status = USB_CONFIG_SELF_POWERED;
#else
            USBD_cfg_status = 0x00;
#endif

            if (USBx->dev.DevRemoteWakeup)
            {
                USBD_cfg_status |= USB_CONFIG_REMOTE_WAKEUP;
            }

            USBD_CtrlSendData (USBx, (uint8_t *)&USBD_cfg_status, 2);
        break;

        default :
            USBD_CtrlError(USBx, req);
        break;
    }
}

/**
*\*\name   USBD_SetFeature.
*\*\fun    Handle Set Status request
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
static void USBD_SetFeature(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    uint32_t dctl;
    uint8_t test_mode = 0;

    if (req->wValue == USB_FEATURE_REMOTE_WAKEUP)
    {
        USBx->dev.DevRemoteWakeup = 1;
        USBx->dev.class_cb->Setup (USBx, req);
        USBD_CtrlSendStatus(USBx);
    }

    else if ((req->wValue == USB_FEATURE_TEST_MODE) && ((req->wIndex & 0xFF) == 0))
    {
        dctl = USB_READ_REG32(&USBx->regs.DCSR->DCTRL);

        test_mode = req->wIndex >> 8;
        switch (test_mode)
        {
            case 1: /* TEST_J */
                dctl |= 1<<4;
            break;

            case 2: /* TEST_K */
                dctl |= 2<<4;
            break;

            case 3: /* TEST_SE0_NAK */
                dctl |= 3<<4;
            break;

            case 4: /* TEST_PACKET */
                dctl |= 4<<4;
            break;

            case 5: /* TEST_FORCE_ENABLE */
                dctl |= 5<<4;
            break;

            default :
                dctl |= 1<<4;
            break;
        }
        USB_WRITE_REG32(&USBx->regs.DCSR->DCTRL, dctl);
        SET_TEST_MODE = dctl;
        USBx->dev.test_mode = 1;
        USBD_CtrlSendStatus(USBx);
    }
    else
    {
        /* Do Nothing */
    }
}

/**
*\*\name   USBD_ClrFeature.
*\*\fun    Handle clear device feature request
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
static void USBD_ClrFeature(USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    switch (USBx->dev.device_status)
    {
        case USB_ADDRESSED:
        case USB_CONFIGURED:
        if (req->wValue == USB_FEATURE_REMOTE_WAKEUP)
        {
            USBx->dev.DevRemoteWakeup = 0;
            USBx->dev.class_cb->Setup (USBx, req);
            USBD_CtrlSendStatus(USBx);
        }
        break;

        default :
            USBD_CtrlError(USBx , req);
        break;
    }
}

/**
*\*\name   USBD_ParseSetupRequest.
*\*\fun    Copy buffer into setup structure
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
void USBD_ParseSetupRequest( USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    req->bmRequest     = *(uint8_t *)  (USBx->dev.setup_packet);
    req->bRequest      = *(uint8_t *)  (USBx->dev.setup_packet +  1);
    req->wValue        = SWAPBYTE      (USBx->dev.setup_packet +  2);
    req->wIndex        = SWAPBYTE      (USBx->dev.setup_packet +  4);
    req->wLength       = SWAPBYTE      (USBx->dev.setup_packet +  6);

    USBx->dev.in_ep[0].ctrl_data_len = req->wLength  ;
    USBx->dev.device_state = USB_EP0_SETUP;
}

/**
*\*\name   USBD_CtrlError.
*\*\fun    Handle USB low level Error
*\*\param  USBx : USB device
*\*\param  req: usb request
*\*\return none
**/
void USBD_CtrlError( USB_CORE_MODULE *USBx, USB_SETUP_REQ *req)
{
    USBDEV_EP_Stall(USBx , 0x80);
    USBDEV_EP_Stall(USBx , 0);
    USB_EP0_OutStart(USBx);
}

/**
*\*\name   USBD_GetString.
*\*\fun    Convert Ascii string into unicode one
*\*\param  desc : descriptor buffer
*\*\param  unicode : Formatted string buffer (unicode)
*\*\param  len : descriptor length
*\*\return none
**/
void USBD_GetString(uint8_t *desc, uint8_t *unicode, uint16_t *len)
{
    uint8_t idx = 0;

    if (desc != NULL)
    {
        *len =  USBD_GetLen(desc) * 2 + 2;
        unicode[idx++] = *len;
        unicode[idx++] =  USB_DESC_TYPE_STRING;

        while (*desc != '\0')
        {
            unicode[idx++] = *desc++;
            unicode[idx++] =  0x00;
        }
    }
}

/**
*\*\name   USBD_GetLen.
*\*\fun    return the string length
*\*\param  buf : pointer to the ascii string buffer
*\*\return string length
**/
static uint8_t USBD_GetLen(uint8_t *buf)
{
    uint8_t  len = 0;

    while (*buf != '\0')
    {
        len++;
        buf++;
    }

    return len;
}
