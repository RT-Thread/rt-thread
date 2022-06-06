/**
 *******************************************************************************
 * @file  usb_host_cfgch.c
 * @brief Functions for opening and closing host channels
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
#include "usb_host_cfgch.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE LL USB Host Core
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
 * Local function prototypes ('static')
 ******************************************************************************/
uint16_t usb_host_getfreech(usb_core_instance *pdev);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  configure and open a pipe
 * @param  [in] pdev        device instance
 * @param  [in] hc_num      host channel index
 * @param  [in] dev_address USB Device address allocated to attached device
 * @param  [in] speed       core speed
 * @param  [in] ep_type     communication type of the EP
 * @param  [in] mps         max size of the packet
 * @retval None
 */
void usb_host_chopen(usb_core_instance *pdev,
                     uint8_t  hc_num,
                     uint8_t  dev_address,
                     uint8_t  speed,
                     uint8_t  ep_type,
                     uint16_t mps)
{
    pdev->host.hc[hc_num].ep_idx     = (uint8_t) pdev->host.channel[hc_num] & 0x7Fu;
    pdev->host.hc[hc_num].is_epin    = (uint8_t)((pdev->host.channel[hc_num] & 0x80U) == 0x80U);
    pdev->host.hc[hc_num].dev_addr   = dev_address;
    pdev->host.hc[hc_num].ep_type    = ep_type;
    pdev->host.hc[hc_num].max_packet = mps;
    pdev->host.hc[hc_num].ch_speed   = speed;
    pdev->host.hc[hc_num].in_toggle  = 0U;
    pdev->host.hc[hc_num].out_toggle = 0U;

    (void)usb_inithch(&pdev->regs, hc_num, &pdev->host.hc[hc_num], pdev->basic_cfgs.dmaen);
}

/**
 * @brief  change a pipe on host
 * @param  [in] pdev        device instance
 * @param  [in] hc_num      host channel index
 * @param  [in] dev_address USB Device address allocated to attached device
 * @param  [in] speed       core speed
 * @param  [in] ep_type     communication type of EP
 * @param  [in] mps         max size of packet
 * @retval None
 */
void usb_host_mdfch(usb_core_instance *pdev,
                    uint8_t  hc_num,
                    uint8_t  dev_address,
                    uint8_t  speed,
                    uint8_t  ep_type,
                    uint16_t mps)
{
    (void)(ep_type);
    if (dev_address != 0U) {
        pdev->host.hc[hc_num].dev_addr   = dev_address;
    }
    if ((pdev->host.hc[hc_num].max_packet != mps) && (mps != 0U)) {
        pdev->host.hc[hc_num].max_packet = mps;
    }
    if ((pdev->host.hc[hc_num].ch_speed != speed) && (speed != 0U)) {
        pdev->host.hc[hc_num].ch_speed   = speed;
    }

    (void)usb_inithch(&pdev->regs, hc_num, &pdev->host.hc[hc_num], pdev->basic_cfgs.dmaen);
}

/**
 * @brief  distribute a new channel for the pipe
 * @param  [in] pdev        device instance
 * @param  [in] ep_addr     EP index the channel distributed for
 * @retval hc_num           host channel index
 */
uint8_t usb_host_distrch(usb_core_instance *pdev, uint8_t ep_addr)
{
    __IO uint16_t hc_num;

    hc_num =  usb_host_getfreech(pdev);
    if (hc_num != HC_ERROR) {
        pdev->host.channel[hc_num & (USB_MAX_TX_FIFOS - 1U)] = HC_USED | ep_addr;
    }
    return (uint8_t)hc_num;
}

/**
 * @brief  free the USB host channel assigned by idx
 * @param  [in] pdev        device instance
 * @param  [in] idx         Channel number to be freed
 * @retval Status
 */
uint8_t usb_host_freech(usb_core_instance *pdev, uint8_t idx)
{
    if (idx < MAX_CHNUM) {
        pdev->host.channel[idx & (USB_MAX_TX_FIFOS - 1U)] &= HC_USED_MASK;
    }
    return (uint8_t)HSTATUS_OK;
}

/**
 * @brief  free all the USB host channels
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_host_dedistrallch(usb_core_instance *pdev)
{
    uint8_t idx;

    for (idx = 2U; idx < MAX_CHNUM ; idx ++) {
        pdev->host.channel[idx & (USB_MAX_TX_FIFOS - 1U)] = 0U;
    }
}

/**
 * @brief  Get a free channel number so that can be distributed to a device endpoint
 * @param  [in] pdev        device instance
 * @retval idx              the free channel index
 */
uint16_t usb_host_getfreech(usb_core_instance *pdev)
{
    uint8_t tmp_idx;
    uint16_t u16Ret = HC_ERROR;

    for (tmp_idx = 0U ; tmp_idx < MAX_CHNUM ; tmp_idx++) {
        if ((pdev->host.channel[tmp_idx & (USB_MAX_TX_FIFOS - 1U)] & HC_USED) == 0U) {
            u16Ret = HC_OK;
            break;
        }
    }

    if (u16Ret == HC_OK) {
        u16Ret = tmp_idx;
    } else {
        u16Ret = HC_ERROR;
    }

    return u16Ret;
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
