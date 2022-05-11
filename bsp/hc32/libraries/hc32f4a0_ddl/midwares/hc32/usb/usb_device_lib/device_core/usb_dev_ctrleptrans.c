/**
 *******************************************************************************
 * @file  usb_dev_ctrleptrans.c
 * @brief The IO requests APIs for control endpoints.
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
#include "usb_dev_ctrleptrans.h"
#include "usb_dev_driver.h"

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
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  send data on the ctl pipe
 * @param  [in] pdev        device instance
 * @param  [in] pbuf        pointer to data buffer
 * @param  [in] len         length of data to be sent
 * @retval None
 */
void usb_ctrldatatx(usb_core_instance *pdev, uint8_t *pbuf, uint16_t len)
{
    pdev->dev.in_ep[0].total_data_len = (uint32_t)len;
    pdev->dev.in_ep[0].rem_data_len   = (uint32_t)len;
    pdev->dev.device_state            = USB_EP0_DATA_IN;

    usb_deveptx(pdev, 0U, pbuf, (uint32_t)len);
}

/**
 * @brief  continue sending data on the ctl pipe
 * @param  [in] pdev        device instance
 * @param  [in] pbuf        pointer to data buffer
 * @param  [in] len         length of data to be sent
 * @retval None
 */
void usb_ctrldatacontinuetx(usb_core_instance *pdev, uint8_t *pbuf, uint16_t len)
{
    usb_deveptx(pdev, 0U, pbuf, (uint32_t)len);
}

/**
 * @brief  receive data on the ctl pipe
 * @param  [in] pdev        device instance
 * @param  [in] pbuf        pointer to data buffer
 * @param  [in] len         length of data to be received
 * @retval status
 */
void usb_ctrldatarx(usb_core_instance *pdev, uint8_t *pbuf, uint16_t len)
{
    pdev->dev.out_ep[0].total_data_len = len;
    pdev->dev.out_ep[0].rem_data_len   = len;
    pdev->dev.device_state             = USB_EP0_DATA_OUT;

    usb_readytorx(pdev, 0U, pbuf, len);
}

/**
 * @brief  continue receive data on the ctl pipe
 * @param  [in] pdev        device instance
 * @param  [in] pbuf        pointer to data buffer
 * @param  [in] len         length of data to be received
 * @retval status
 */
void usb_ctrldatacontinuerx(usb_core_instance *pdev, uint8_t *pbuf, uint16_t len)
{
    usb_readytorx(pdev, 0U, pbuf, len);
}
/**
 * @brief  send zero lzngth packet on the ctl pipe
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_ctrlstatustx(usb_core_instance *pdev)
{
    pdev->dev.device_state = USB_EP0_STATUS_IN;
    usb_deveptx(pdev, 0U, pdev->dev.setup_pkt_buf, 0U);
}

/**
 * @brief  receive zero lzngth packet on the ctl pipe
 * @param  [in] pdev        device instance
 * @retval None
 */
void usb_ctrlstatusrx(usb_core_instance *pdev)
{
    pdev->dev.device_state = USB_EP0_STATUS_OUT;
    usb_readytorx(pdev, 0U, pdev->dev.setup_pkt_buf, 0U);
}

/**
 * @brief  get the received data length
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval Rx Data blength
 */
uint16_t usb_getrxcnt(usb_core_instance *pdev, uint8_t epnum)
{
    return (uint16_t)pdev->dev.out_ep[epnum].xfer_count;
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
