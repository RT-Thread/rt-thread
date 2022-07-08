/**
 *******************************************************************************
 * @file  usb_dev_stdreq.c
 * @brief The standard USB requests following chapter 9.
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
#include <string.h>
#include "usb_dev_core.h"
#include "usb_dev_stdreq.h"
#include "usb_dev_driver.h"
#include "usb_dev_ctrleptrans.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CORE
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
static __USB_ALIGN_BEGIN uint32_t dev_ep_status   = 0UL;
static __USB_ALIGN_BEGIN uint32_t dev_default_cfg = 0UL;
static __USB_ALIGN_BEGIN uint32_t dev_cfg_status  = 0UL;

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
void usb_getdesc(usb_core_instance *pdev, const USB_SETUP_REQ *req);
void usb_setaddr(usb_core_instance  *pdev, const USB_SETUP_REQ *req);
void usb_setconfig(usb_core_instance *pdev, const USB_SETUP_REQ *req);
void usb_getconfig(usb_core_instance *pdev, const USB_SETUP_REQ *req);
void usb_getstatus(usb_core_instance  *pdev, const USB_SETUP_REQ *req);
void usb_getintf(usb_core_instance *pdev);
void usb_setfeature(usb_core_instance *pdev, USB_SETUP_REQ *req);
void usb_clrfeature(usb_core_instance *pdev, USB_SETUP_REQ *req);
uint8_t usb_getlength(uint8_t *buf);
void usb_dev_ctrlconfig(usb_core_instance  *pdev, uint8_t cfgidx, uint8_t action);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Handle standard usb device requests
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_standarddevreq(usb_core_instance *pdev, USB_SETUP_REQ *req)
{
    if (req->bRequest == USB_REQ_GET_DESCRIPTOR) {
        usb_getdesc(pdev, req) ;
    } else if (req->bRequest == USB_REQ_SET_ADDRESS) {
        usb_setaddr(pdev, req);
    } else if (req->bRequest == USB_REQ_SET_CONFIGURATION) {
        usb_setconfig(pdev, req);
    } else if (req->bRequest == USB_REQ_GET_CONFIGURATION) {
        usb_getconfig(pdev, req);
    } else if (req->bRequest == USB_REQ_GET_STATUS) {
        usb_getstatus(pdev, req);
    } else if (req->bRequest == USB_REQ_SET_FEATURE) {
        usb_setfeature(pdev, req);
    } else if (req->bRequest == USB_REQ_CLEAR_FEATURE) {
        usb_clrfeature(pdev, req);
    } else {
        if (0U != pdev->dev.class_callback->ep0_setup(pdev, req)) {
            usb_ctrlerr(pdev);
        }
    }
}

/**
 * @brief  Handle standard usb interface requests
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_standarditfreq(usb_core_instance *pdev, USB_SETUP_REQ *req)
{
    uint8_t u8RetFlag = 0U;

    if (req->bRequest == USB_REQ_GET_STATUS) {
        usb_getstatus(pdev, req);
        u8RetFlag = 1U;
    } else if (req->bRequest == USB_REQ_GET_INTERFACE) {
        if (req->bmRequest != 0x21U) {
            usb_getintf(pdev);
            u8RetFlag = 1U;
        }
    } else if (req->bRequest == 0xFEU) {
        usb_getintf(pdev);
        u8RetFlag = 1U;
    } else {
        ;
    }

    if (1U != u8RetFlag) {
        if (pdev->dev.device_cur_status == USB_DEV_CONFIGURED) {
            if (LOBYTE(req->wIndex) <= USBD_ITF_MAX_NUM) {
                pdev->dev.class_callback->ep0_setup(pdev, req);
                if (req->wLength == 0U) {
                    usb_ctrlstatustx(pdev);
                }
            } else {
                usb_ctrlerr(pdev);
            }
        } else {
            usb_ctrlerr(pdev);
        }
    }
}

/**
 * @brief  Handle standard usb endpoint requests
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_standardepreq(usb_core_instance *pdev, USB_SETUP_REQ *req)
{
    __IO uint8_t   ep_addr;
    ep_addr  = LOBYTE(req->wIndex);

    switch (req->bRequest) {
        case USB_REQ_SET_FEATURE :
            switch (pdev->dev.device_cur_status) {
                case USB_DEV_ADDRESSED:
                    if ((ep_addr != 0x00U) && (ep_addr != 0x80U)) {
                        usb_stalldevep(pdev, ep_addr);
                    }
                    break;
                case USB_DEV_CONFIGURED:
                    if (req->wValue == USB_FEATURE_EP_HALT) {
                        if ((ep_addr != 0x00U) && (ep_addr != 0x80U)) {
                            usb_stalldevep(pdev, ep_addr);
                        }
                    }
                    pdev->dev.class_callback->ep0_setup(pdev, req);
                    usb_ctrlstatustx(pdev);
                    break;
                default:
                    usb_ctrlerr(pdev);
                    break;
            }
            break;
        case USB_REQ_CLEAR_FEATURE :
            switch (pdev->dev.device_cur_status) {
                case USB_DEV_ADDRESSED:
                    if ((ep_addr != 0x00U) && (ep_addr != 0x80U)) {
                        usb_stalldevep(pdev, ep_addr);
                    }
                    break;
                case USB_DEV_CONFIGURED:
                    if (req->wValue == USB_FEATURE_EP_HALT) {
                        if ((ep_addr != 0x00U) && (ep_addr != 0x80U)) {
                            usb_clrstall(pdev, ep_addr);
                            pdev->dev.class_callback->ep0_setup(pdev, req);
                        }
                        usb_ctrlstatustx(pdev);
                    }
                    break;
                default:
                    usb_ctrlerr(pdev);
                    break;
            }
            break;
        case USB_REQ_GET_STATUS:
            switch (pdev->dev.device_cur_status) {
                case USB_DEV_ADDRESSED:
                    if ((ep_addr != 0x00U) && (ep_addr != 0x80U)) {
                        usb_stalldevep(pdev, ep_addr);
                    }
                    break;
                case USB_DEV_CONFIGURED:
                    if ((ep_addr & 0x80U) == 0x80U) {
                        if (0U != pdev->dev.in_ep[ep_addr % USB_MAX_TX_FIFOS].ep_stall) {
                            dev_ep_status = 0x0001U;
                        } else {
                            dev_ep_status = 0x0000U;
                        }
                    } else if ((ep_addr & 0x80U) == 0x00U) {
                        if (0U != pdev->dev.out_ep[ep_addr % USB_MAX_TX_FIFOS].ep_stall) {
                            dev_ep_status = 0x0001U;
                        } else {
                            dev_ep_status = 0x0000U;
                        }
                    } else {
                        ;
                    }
                    usb_ctrldatatx(pdev, (uint8_t *)&dev_ep_status, 2U);
                    break;

                default:
                    usb_ctrlerr(pdev);
                    break;
            }
            break;
        default:
            break;
    }
}

/**
 * @brief  Handle Get Descriptor requests
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval status
 */
void usb_getdesc(usb_core_instance *pdev, const USB_SETUP_REQ *req)
{
    uint16_t len = 0U;
    uint8_t *pbuf = NULL;
    uint8_t u8ErrFlag = 0U;

    switch (req->wValue >> 8U) {
        case USB_DESC_TYPE_DEVICE:
            pbuf = pdev->dev.desc_callback->get_dev_desc(&len);
            break;
        case USB_DESC_TYPE_CONFIGURATION:
            pbuf   = (uint8_t *)pdev->dev.class_callback->class_getconfigdesc(&len);
            pbuf[1] = USB_DESC_TYPE_CONFIGURATION;
            break;
        case USB_DESC_TYPE_STRING:
            switch ((uint8_t)(req->wValue)) {
                case LANGID_STR_IDX:
                    pbuf = pdev->dev.desc_callback->get_dev_langiddesc(&len);
                    break;
                case MFC_STR_IDX:
                    pbuf = pdev->dev.desc_callback->get_dev_manufacturerstr(&len);
                    break;
                case PRODUCT_STR_IDX:
                    pbuf = pdev->dev.desc_callback->get_dev_productstr(&len);
                    break;
                case SERIAL_STR_IDX:
                    pbuf = pdev->dev.desc_callback->get_dev_serialstr(&len);
                    break;
                case CONFIG_STR_IDX:
                    pbuf = pdev->dev.desc_callback->get_dev_configstr(&len);
                    break;
                case INTERFACE_STR_IDX:
                    pbuf = pdev->dev.desc_callback->get_dev_interfacestr(&len);
                    break;
                default:
                    usb_ctrlerr(pdev);
                    u8ErrFlag = 1U;
                    break;
            }
            break;
        case USB_DESC_TYPE_DEVICE_QUALIFIER:
            usb_ctrlerr(pdev);
            u8ErrFlag = 1U;
            break;
        case USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION:
            usb_ctrlerr(pdev);
            u8ErrFlag = 1U;
            break;
        default:
            usb_ctrlerr(pdev);
            u8ErrFlag = 1U;
            break;
    }

    if (0U == u8ErrFlag) {
        if ((len != 0U) && (req->wLength != 0U)) {
            len = LL_MIN(len, req->wLength);
            usb_ctrldatatx(pdev, pbuf, len);
        }
    }
}

/**
 * @brief  Set device address
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_setaddr(usb_core_instance  *pdev, const USB_SETUP_REQ *req)
{
    uint8_t  dev_addr;

    if ((req->wIndex == 0U) && (req->wLength == 0U)) {
        dev_addr = (uint8_t)(req->wValue) & 0x7Fu;

        if (pdev->dev.device_cur_status == USB_DEV_CONFIGURED) {
            usb_ctrlerr(pdev);
        } else {
            pdev->dev.device_address = dev_addr;
            usb_addrset(pdev, dev_addr);
            usb_ctrlstatustx(pdev);

            if (dev_addr != 0U) {
                pdev->dev.device_cur_status  = USB_DEV_ADDRESSED;
            } else {
                pdev->dev.device_cur_status  = USB_DEV_DEFAULT;
            }
        }
    } else {
        usb_ctrlerr(pdev);
    }
}

/**
 * @brief  Handle Set device configuration request
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_setconfig(usb_core_instance *pdev, const USB_SETUP_REQ *req)
{
    static uint8_t  tmp_cfgidx;

    tmp_cfgidx = (uint8_t)(req->wValue);

    if (tmp_cfgidx > DEV_MAX_CFG_NUM) {
        usb_ctrlerr(pdev);
    } else {
        switch (pdev->dev.device_cur_status) {
            case USB_DEV_ADDRESSED:
                if (0U != tmp_cfgidx) {
                    pdev->dev.device_config     = tmp_cfgidx;
                    pdev->dev.device_cur_status = USB_DEV_CONFIGURED;
                    usb_dev_ctrlconfig(pdev, tmp_cfgidx, USB_DEV_CONFIG_SET);
                    usb_ctrlstatustx(pdev);
                } else {
                    usb_ctrlstatustx(pdev);
                }
                break;
            case USB_DEV_CONFIGURED:
                if (tmp_cfgidx == 0U) {
                    pdev->dev.device_cur_status = USB_DEV_ADDRESSED;
                    pdev->dev.device_config     = tmp_cfgidx;
                    usb_dev_ctrlconfig(pdev, tmp_cfgidx, USB_DEV_CONFIG_CLEAR);
                    usb_ctrlstatustx(pdev);
                } else if (tmp_cfgidx != pdev->dev.device_config) {
                    /* Clear old configuration */
                    usb_dev_ctrlconfig(pdev, pdev->dev.device_config, USB_DEV_CONFIG_CLEAR);
                    /* set new configuration */
                    pdev->dev.device_config = tmp_cfgidx;
                    usb_dev_ctrlconfig(pdev, tmp_cfgidx, USB_DEV_CONFIG_SET);
                    usb_ctrlstatustx(pdev);
                } else {
                    usb_ctrlstatustx(pdev);
                }
                break;
            case USB_DEV_SUSPENDED:

                break;
            default:
                usb_ctrlerr(pdev);
                break;
        }
    }
}

/**
 * @brief  Handle Get device configuration request
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_getconfig(usb_core_instance *pdev, const USB_SETUP_REQ *req)
{
    if (req->wLength != 1U) {
        usb_ctrlerr(pdev);
    } else {
        switch (pdev->dev.device_cur_status) {
            case USB_DEV_ADDRESSED:
                usb_ctrldatatx(pdev, (uint8_t *)&dev_default_cfg, 1U);
                break;
            case USB_DEV_CONFIGURED:
                usb_ctrldatatx(pdev, (uint8_t *)&pdev->dev.device_config, 1U);
                break;
            default:
                usb_ctrlerr(pdev);
                break;
        }
    }
}

/**
 * @brief  Handle Get Status request
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_getstatus(usb_core_instance  *pdev, const USB_SETUP_REQ *req)
{
    (void)(req);
    switch (pdev->dev.device_cur_status) {
        case USB_DEV_ADDRESSED:
        case USB_DEV_CONFIGURED:
#ifdef SELF_POWER
            dev_cfg_status = USB_CONFIG_SELF_POWERED;
#else
            dev_cfg_status = 0x00U;
#endif
            if (0U != pdev->dev.device_remote_wakeup) {
                dev_cfg_status |= USB_CONFIG_REMOTE_WAKEUP;
            }
            usb_ctrldatatx(pdev, (uint8_t *)&dev_cfg_status, 2U);
            break;
        default :
            usb_ctrlerr(pdev);
            break;
    }
}

/**
 * @brief  usb_getintf
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_getintf(usb_core_instance  *pdev)
{
    dev_cfg_status = 0U;
    usb_ctrldatatx(pdev, (uint8_t *)&dev_cfg_status, 1U);
}

/**
 * @brief  Handle Set device feature request
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_setfeature(usb_core_instance *pdev, USB_SETUP_REQ *req)
{
    uint32_t dctl;
    uint8_t test_mode;

    if (req->wValue == USB_FEATURE_REMOTE_WAKEUP) {
        pdev->dev.device_remote_wakeup = 1U;
        pdev->dev.class_callback->ep0_setup(pdev, req);
        usb_ctrlstatustx(pdev);
    } else if ((req->wValue == USB_FEATURE_TEST_MODE) && ((req->wIndex & 0xFFU) == 0U)) {
        dctl = READ_REG32(pdev->regs.DREGS->DCTL);
        test_mode = (uint8_t)req->wIndex >> 8U;
        test_mode = test_mode & (uint8_t)(~0xF8U);
        dctl = (uint32_t)test_mode << 4U;
        SET_TEST_MODE = dctl;
        pdev->dev.test_mode = 1U;
        usb_ctrlstatustx(pdev);
    } else {
        ;
    }
}

/**
 * @brief  Handle clear device feature request
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_clrfeature(usb_core_instance *pdev, USB_SETUP_REQ *req)
{
    switch (pdev->dev.device_cur_status) {
        case USB_DEV_ADDRESSED:
        case USB_DEV_CONFIGURED:
            if (req->wValue == USB_FEATURE_REMOTE_WAKEUP) {
                pdev->dev.device_remote_wakeup = 0U;
                pdev->dev.class_callback->ep0_setup(pdev, req);
                usb_ctrlstatustx(pdev);
            }
            break;
        default :
            usb_ctrlerr(pdev);
            break;
    }
}

/**
 * @brief  Copy buffer into setup structure
 * @param  [in] pdev        device instance
 * @param  [in] req         usb request
 * @retval None
 */
void usb_parsesetupreq(usb_core_instance *pdev, USB_SETUP_REQ *req)
{
    req->bmRequest = *(uint8_t *)(pdev->dev.setup_pkt_buf);
    req->bRequest = *(uint8_t *)(pdev->dev.setup_pkt_buf + 1U);
    req->wValue = SWAPBYTE(pdev->dev.setup_pkt_buf + 2U);
    req->wIndex = SWAPBYTE(pdev->dev.setup_pkt_buf + 4U);
    req->wLength = SWAPBYTE(pdev->dev.setup_pkt_buf + 6U);

    pdev->dev.in_ep[0].ctl_data_len = req->wLength;
    pdev->dev.device_state = USB_EP0_SETUP;
}

/**
 * @brief  Handle USB low level Error
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_ctrlerr(usb_core_instance *pdev)
{
    usb_stalldevep(pdev, 0x80U);
    usb_stalldevep(pdev, 0U);
    usb_ep0outstart(pdev);
}

/**
 * @brief  Convert Ascii string into unicode one
 * @param  [in] desc        descriptor buffer
 * @param  [in] unicode     Formatted string buffer (unicode)
 * @param  [in] len         descriptor length
 * @retval None
 */
void usb_getstring(uint8_t *desc, uint8_t *unicode, uint16_t *len)
{
    uint8_t tmp_idx = 0U;

    if (desc != NULL) {
        *len = (uint16_t)usb_getlength(desc) * 2U + 2U;
        unicode[tmp_idx++] = (uint8_t) * len;
        unicode[tmp_idx++] = USB_DESC_TYPE_STRING;

        while (*desc != (uint8_t)0U) {
            unicode[tmp_idx++] = *desc++;
            unicode[tmp_idx++] = 0x00U;
        }
    }
}

/**
 * @brief  get the string length
 * @param  [in] buf     pointer to the ascii string buffer
 * @retval string length
 */
uint8_t usb_getlength(uint8_t *buf)
{
    uint8_t tmp_len = 0U;

    while (*buf != (uint8_t)0U) {
        tmp_len++;
        buf++;
    }
    return tmp_len;
}

/**
 * @brief  set current configuration or clear current configuration
 * @param  [in] pdev        device instance
 * @param  [in] cfgidx      configuration index
 * @param  [in] action      USB_DEV_CONFIG_SET or USB_DEV_CONFIG_CLEAR
 * @retval None
 */
void usb_dev_ctrlconfig(usb_core_instance *pdev, uint8_t cfgidx, uint8_t action)
{
    __IO uint8_t tmp_1;

    (void)(cfgidx);
    tmp_1 = action;
    if (tmp_1 == USB_DEV_CONFIG_SET) {          /* set configuration */
        pdev->dev.class_callback->class_init(pdev);
        pdev->dev.user_callback->user_devconfig();
    } else if (tmp_1 == USB_DEV_CONFIG_CLEAR) { /* clear configuration */
        pdev->dev.class_callback->class_deinit(pdev);
    } else {
        ;
    }
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
