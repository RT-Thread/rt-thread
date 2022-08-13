/**
 *******************************************************************************
 * @file  usb_host_stdreq.c
 * @brief Standard requests for device enumeration
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_stdreq.h"
#include "usb_host_ctrltrans.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes declared in the last part.
 ******************************************************************************/
void usb_host_parsedevdesc(usb_host_devdesc_typedef *, uint8_t *buf, uint16_t length);

void usb_host_parsecfgdesc(usb_host_cfgdesc_typedef *cfg_desc,
                           usb_host_itfdesc_typedef *itf_desc,
                           USB_HOST_EPDesc_TypeDef ep_desc[][USBH_MAX_NUM_ENDPOINTS],
                           uint8_t *buf,
                           uint16_t length);
void usb_host_parseitfdesc(usb_host_itfdesc_typedef *if_descriptor, uint8_t *buf);
void usb_host_parseepdesc(USB_HOST_EPDesc_TypeDef *ep_descriptor, uint8_t *buf);
void usb_host_parsestringdesc(uint8_t *psrc, uint8_t *pdest, uint16_t length);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @brief  issue a command descriptor from the connected device. parses the
 *         descriptor and updates the status once the response has been received.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] req_type    type of the descriptor
 * @param  [in] value_idx   wValue of setup for the request to get Descriptr
 * @param  [in] buff:       buffer to save the the descriptor
 * @param  [in] length      the length of the description.
 * @retval status
 */
HOST_STATUS usb_host_getdesc(usb_core_instance *pdev,
                             USBH_HOST *phost,
                             uint8_t req_type,
                             uint16_t value_idx,
                             uint8_t *buff,
                             uint16_t length)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_D2H | req_type;
    phost->ctrlparam.setup.b.bRequest      = USB_REQ_GET_DESCRIPTOR;
    phost->ctrlparam.setup.b.wValue.w      = value_idx;

    if ((value_idx & 0xff00U) == USB_DESC_STRING) {
        phost->ctrlparam.setup.b.wIndex.w  = 0x0409U;
    } else {
        phost->ctrlparam.setup.b.wIndex.w  = 0U;
    }
    phost->ctrlparam.setup.b.wLength.w     = length;
    return usb_host_ctrlreq(pdev, phost, buff, length);
}

/**
 * @brief  Issue command to the device to get the device discription. it parses
 *         the device descriptor and updates the status once getting the device
 *         description.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set.
 * @param  [in] length      the length of the description.
 * @retval status
 */
HOST_STATUS usb_host_getdevdesc(usb_core_instance *pdev,
                                USBH_HOST *phost,
                                uint8_t length)
{
    HOST_STATUS status;
    status = usb_host_getdesc(pdev,
                              phost,
                              (uint8_t)(USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD),
                              USB_DESC_DEVICE,
                              pdev->host.Rx_Buffer,
                              (uint16_t)length);
    if (status == HSTATUS_OK) {
        /* Commands successfully sent and Response Received */
        usb_host_parsedevdesc(&phost->device_prop.devdesc, pdev->host.Rx_Buffer, (uint16_t)length);
    }
    return status;
}

/**
 * @brief  Issue a command to get the configuration description from the device
 *         connected, parse the configuration descriptor and update the
 *         status once the response has been received.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set.
 * @param  [in] length      the length of the description.
 * @retval status
 */
HOST_STATUS usb_host_getcfgdesc(usb_core_instance *pdev,
                                USBH_HOST *phost,
                                uint16_t length)
{
    HOST_STATUS status;

    status = usb_host_getdesc(pdev,
                              phost,
                              USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD,
                              USB_DESC_CONFIGURATION,
                              pdev->host.Rx_Buffer,
                              length);
    if (status == HSTATUS_OK) {
        usb_host_parsecfgdesc(&phost->device_prop.devcfgdesc,
                              phost->device_prop.devitfdesc,
                              phost->device_prop.devepdesc,
                              pdev->host.Rx_Buffer,
                              length);
    }
    return status;
}

/**
 * @brief  Issues string Descriptor command to the device. Once the response
 *         received, it parses the string descriptor and updates the status.
 * @param  [in] pdev            device instance
 * @param  [in] phost           host state set
 * @param  [in] string_index    the index for the string
 * @param  [in] buff            buffer to save the the string descriptor
 * @param  [in] length          the length of the description.
 * @retval status
 */
HOST_STATUS usb_host_getstringdesc(usb_core_instance *pdev,
                                   USBH_HOST *phost,
                                   uint8_t string_index,
                                   uint8_t *buff,
                                   uint16_t length)
{
    HOST_STATUS status;
    status = usb_host_getdesc(pdev,
                              phost,
                              USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD,
                              USB_DESC_STRING | string_index,
                              pdev->host.Rx_Buffer,
                              length);
    if (status == HSTATUS_OK) {
        usb_host_parsestringdesc(pdev->host.Rx_Buffer, buff, length);
    }
    return status;
}

/**
 * @brief  issue a command to set the address for the device that have connected.
 * @param  [in] pdev            device instance
 * @param  [in] phost           host state set
 * @param  [in] DeviceAddress   Device address which would be set to the conected device
 * @retval status
 */
HOST_STATUS usb_host_setdevaddr(usb_core_instance *pdev,
                                USBH_HOST *phost,
                                uint8_t DeviceAddress)
{
    /*
    Refer to table9-3 of 9.4
    */
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;
    phost->ctrlparam.setup.b.bRequest      = USB_REQ_SET_ADDRESS;
    phost->ctrlparam.setup.b.wValue.w      = (uint16_t)DeviceAddress;
    phost->ctrlparam.setup.b.wIndex.w      = 0U;
    phost->ctrlparam.setup.b.wLength.w     = 0U;

    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  issue a command to set the configuration to the connected device.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] cfg_idx     value for the configuration setup
 * @retval status
 */
HOST_STATUS usb_host_setconfig(usb_core_instance *pdev,
                               USBH_HOST *phost,
                               uint16_t cfg_idx)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_DEVICE | USB_REQ_TYPE_STANDARD;
    phost->ctrlparam.setup.b.bRequest = USB_REQ_SET_CONFIGURATION;
    phost->ctrlparam.setup.b.wValue.w = cfg_idx;
    phost->ctrlparam.setup.b.wIndex.w = 0U;
    phost->ctrlparam.setup.b.wLength.w = 0U;

    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  issue a command to set the Interface value to the connected device
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] ep_num      the index of the endpoint
 * @param  [in] altSetting  the value for the setup of set interface
 * @retval status
 */
HOST_STATUS usb_host_setintf(usb_core_instance *pdev,
                             USBH_HOST *phost,
                             uint8_t ep_num,
                             uint8_t altSetting)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D | USB_REQ_RECIPIENT_INTERFACE | USB_REQ_TYPE_STANDARD;

    phost->ctrlparam.setup.b.bRequest = USB_REQ_SET_INTERFACE;
    phost->ctrlparam.setup.b.wValue.w = altSetting;
    phost->ctrlparam.setup.b.wIndex.w = ep_num;
    phost->ctrlparam.setup.b.wLength.w = 0U;

    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  issue a comman to clear or disable a specific feature in the device.
 * @param  [in] pdev        device instance
 * @param  [in] phost       host state set
 * @param  [in] ep_num      index of the endpoint
 * @param  [in] hc_num      host channel index
 * @retval status
 */
HOST_STATUS usb_host_clrfeature(usb_core_instance *pdev,
                                USBH_HOST *phost,
                                uint8_t ep_num,
                                uint8_t hc_num)
{
    phost->ctrlparam.setup.b.bmRequestType = USB_H2D |
            USB_REQ_RECIPIENT_ENDPOINT |
            USB_REQ_TYPE_STANDARD;

    phost->ctrlparam.setup.b.bRequest      = USB_REQ_CLEAR_FEATURE;
    phost->ctrlparam.setup.b.wValue.w      = FEATURE_SELECTOR_ENDPOINT;
    phost->ctrlparam.setup.b.wIndex.w      = ep_num;
    phost->ctrlparam.setup.b.wLength.w     = 0U;

    if ((ep_num & USB_REQ_DIR_MASK) == USB_D2H) {
        pdev->host.hc[hc_num].in_toggle    = 0U;
    } else {
        pdev->host.hc[hc_num].out_toggle   = 0U;
    }

    return usb_host_ctrlreq(pdev, phost, NULL, 0U);
}

/**
 * @brief  parse the data frame of device descriptor
 * @param  [in] dev_desc    the structure of the device descriptor
 * @param  [in] buf         buffer where the source descriptor is save
 * @param  [in] length      Length of the descriptor in byte
 * @retval None
 */
void usb_host_parsedevdesc(usb_host_devdesc_typedef *dev_desc,
                           uint8_t *buf,
                           uint16_t length)
{
    dev_desc->bLength                = *(uint8_t *)(buf +  0U);
    dev_desc->bDescriptorType        = *(uint8_t *)(buf +  1U);
    dev_desc->bcdUSB                 = SMALL_END(buf +  2U);
    dev_desc->bDeviceClass           = *(uint8_t *)(buf +  4U);
    dev_desc->bDeviceSubClass        = *(uint8_t *)(buf +  5U);
    dev_desc->bDeviceProtocol        = *(uint8_t *)(buf +  6U);
    dev_desc->bMaxPacketSize0        = *(uint8_t *)(buf +  7U);

    if (length > (uint16_t)8) {
        dev_desc->idVendor           = SMALL_END(buf +  8U);
        dev_desc->idProduct          = SMALL_END(buf + 10U);
        dev_desc->bcdDevice          = SMALL_END(buf + 12U);
        dev_desc->iManufacturer      = *(uint8_t *)(buf + 14U);
        dev_desc->iProduct           = *(uint8_t *)(buf + 15U);
        dev_desc->iSerialNumber      = *(uint8_t *)(buf + 16U);
        dev_desc->bNumConfigurations = *(uint8_t *)(buf + 17U);
    }
}

/**
 * @brief  This function Parses the configuration descriptor from the received buffer
 * @param  [in] cfg_desc    the structure of configuration descriptor
 * @param  [in] itf_desc    the structure of interface descriptor
 * @param  [in] ep_desc     the structure of endpoint descriptor
 * @param  [in] buf         buffer where the source descriptor is save
 * @param  [in] length      Length of the descriptor in byte
 * @retval None
 */
void usb_host_parsecfgdesc(usb_host_cfgdesc_typedef *cfg_desc,
                           usb_host_itfdesc_typedef *itf_desc,
                           USB_HOST_EPDesc_TypeDef ep_desc[][USBH_MAX_NUM_ENDPOINTS],
                           uint8_t *buf,
                           uint16_t length)
{
    usb_host_itfdesc_typedef     *pif ;
    usb_host_itfdesc_typedef     temp_pif ;
    USB_HOST_EPDesc_TypeDef      *pep;
    USB_HOST_DescHeader_TypeDef  *pdesc = (USB_HOST_DescHeader_TypeDef *)buf;
    uint16_t                      ptr;
    int8_t                        if_ix;
    int8_t                        ep_ix;
    static uint16_t               prev_ep_size = 0U;
    static uint8_t                prev_itf = 0U;

    /* Parse the configuration descriptor */
    cfg_desc->bLength             = *(uint8_t *)(buf + 0U);
    cfg_desc->bDescriptorType     = *(uint8_t *)(buf + 1U);
    cfg_desc->wTotalLength        = SMALL_END(buf + 2U);
    cfg_desc->bNumInterfaces      = *(uint8_t *)(buf + 4U);
    cfg_desc->bConfigurationValue = *(uint8_t *)(buf + 5U);
    cfg_desc->iConfiguration      = *(uint8_t *)(buf + 6U);
    cfg_desc->bmAttributes        = *(uint8_t *)(buf + 7U);
    cfg_desc->bMaxPower           = *(uint8_t *)(buf + 8U);

    if (length > USB_CONFIGURATION_DESC_SIZE) {
        ptr = USB_LEN_CFG_DESC;

        if (cfg_desc->bNumInterfaces <= USBH_MAX_NUM_INTERFACES) {

            while (ptr < cfg_desc->wTotalLength) {
                pdesc = usb_host_getnextdesc((uint8_t *)pdesc, &ptr);
                if (pdesc->bDescriptorType   == USB_DESC_TYPE_INTERFACE) {
                    if_ix             = (int8_t) * (((uint8_t *)pdesc) + 2U);
                    pif               = &itf_desc[if_ix];

                    if ((*((uint8_t *)pdesc + 3U)) < 3U) {
                        usb_host_parseitfdesc(&temp_pif, (uint8_t *)pdesc);
                        ep_ix = (int8_t)0;

                        /* Parse Ep descriptors relative to the current interface */
                        if (temp_pif.bNumEndpoints <= USBH_MAX_NUM_ENDPOINTS) {
                            while (ep_ix < (int8_t)temp_pif.bNumEndpoints) {
                                pdesc = usb_host_getnextdesc((void *)pdesc, &ptr);
                                if (pdesc->bDescriptorType   == USB_DESC_TYPE_ENDPOINT) {
                                    pep               = &ep_desc[if_ix][ep_ix];

                                    if (prev_itf != (uint8_t)if_ix) {
                                        prev_itf = (uint8_t)if_ix;
                                        usb_host_parseitfdesc(pif, (uint8_t *)&temp_pif);
                                    } else {
                                        if (prev_ep_size > SMALL_END((uint8_t *)pdesc + 4U)) {
                                            break;
                                        } else {
                                            usb_host_parseitfdesc(pif, (uint8_t *)&temp_pif);
                                        }
                                    }
                                    usb_host_parseepdesc(pep, (uint8_t *)pdesc);
                                    prev_ep_size = SMALL_END((uint8_t *)pdesc + 4U);
                                    ep_ix++;
                                }
                            }
                        }
                    }
                }
            }
        }
        prev_ep_size = 0U;
        prev_itf = 0U;
    }
}

/**
 * @brief  This function parses the interface descriptor from the received buffer.
 * @param  [in] if_descriptor   structure of interface descriptor
 * @param  [in] buf             buffer where the source descriptor is save
 * @retval None
 */
void  usb_host_parseitfdesc(usb_host_itfdesc_typedef *if_descriptor, uint8_t *buf)
{
    if_descriptor->bLength            = *(uint8_t *)(buf + 0U);
    if_descriptor->bDescriptorType    = *(uint8_t *)(buf + 1U);
    if_descriptor->bInterfaceNumber   = *(uint8_t *)(buf + 2U);
    if_descriptor->bAlternateSetting  = *(uint8_t *)(buf + 3U);
    if_descriptor->bNumEndpoints      = *(uint8_t *)(buf + 4U);
    if_descriptor->bInterfaceClass    = *(uint8_t *)(buf + 5U);
    if_descriptor->bInterfaceSubClass = *(uint8_t *)(buf + 6U);
    if_descriptor->bInterfaceProtocol = *(uint8_t *)(buf + 7U);
    if_descriptor->iInterface         = *(uint8_t *)(buf + 8U);
}

/**
 * @brief  This function parses the endpoint descriptor from the received buffer.
 * @param  [in] ep_descriptor   the structure of endpoint descriptor.
 * @param  [in] buf             buffer where the source descriptor is save
 * @retval None
 */
void usb_host_parseepdesc(USB_HOST_EPDesc_TypeDef  *ep_descriptor, uint8_t *buf)
{
    ep_descriptor->bLength          = *(uint8_t *)(buf + 0U);
    ep_descriptor->bDescriptorType  = *(uint8_t *)(buf + 1U);
    ep_descriptor->bEndpointAddress = *(uint8_t *)(buf + 2U);
    ep_descriptor->bmAttributes     = *(uint8_t *)(buf + 3U);
    ep_descriptor->wMaxPacketSize   = SMALL_END(buf + 4U);
    ep_descriptor->bInterval        = *(uint8_t *)(buf + 6U);
}

/**
 * @brief  This function parses the string descriptor from the received buffer.
 * @param  [in] psrc        source data
 * @param  [in] pdest       destination data
 * @param  [in] length      Length of the descriptor in byte
 * @retval None
 */
void usb_host_parsestringdesc(uint8_t *psrc, uint8_t *pdest, uint16_t length)
{
    uint16_t strlength;
    uint16_t tmp_idx;
    /*
    The describ of String Desctipor refers to 9.6.8
    psrc[0] = bLength           bLength = N+2
    psrc[1] = bDescriptorType   STRING Descriptor Type
    ...
    */
    if (psrc[1] == USB_DESC_TYPE_STRING) {
        strlength = ((((uint16_t)psrc[0]) - 2U) <= length) ? (((uint16_t)psrc[0]) - 2U) : length;
        psrc += 2U;
        for (tmp_idx = 0U; tmp_idx < strlength; tmp_idx += 2U) {
            *pdest =  psrc[tmp_idx];
            pdest++;
        }
        *pdest = 0U;
    }
}

/**
 * @brief  This function gets the header of next descriptor.
 * @param  [in] pbuf    buffer where the configuration descriptor is contained.
 * @param  [in] ptr     data popinter inside the cfg descriptor
 * @retval header of next descriptor
 */
USB_HOST_DescHeader_TypeDef  *usb_host_getnextdesc(uint8_t *pbuf, uint16_t *ptr)
{
    USB_HOST_DescHeader_TypeDef  *pnext;

    *ptr += ((USB_HOST_DescHeader_TypeDef *)pbuf)->bLength;
    pnext = (USB_HOST_DescHeader_TypeDef *)((uint8_t *)pbuf + ((USB_HOST_DescHeader_TypeDef *)pbuf)->bLength);

    return (pnext);
}

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
