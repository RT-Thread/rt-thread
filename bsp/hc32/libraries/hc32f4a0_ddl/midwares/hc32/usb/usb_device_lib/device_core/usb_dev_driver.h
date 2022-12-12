/**
 *******************************************************************************
 * @file  usb_dev_driver.h
 * @brief Peripheral Driver Header file
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
#ifndef __USB_DEV_DRIVER_H__
#define __USB_DEV_DRIVER_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_def.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CORE
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void usb_initdev(usb_core_instance *pdev);
extern void usb_conndevctrl(usb_core_instance *pdev, uint8_t link);
extern void usb_addrset(usb_core_instance *pdev, uint8_t devaddr);
extern void usb_opendevep(usb_core_instance *pdev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_type);
extern void usb_shutdevep(usb_core_instance *pdev, uint8_t ep_addr);
extern void usb_readytorx(usb_core_instance *pdev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);
extern void usb_ep0outstart(usb_core_instance *pdev);
extern void usb_deveptx(usb_core_instance *pdev, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len);
extern void usb_stalldevep(usb_core_instance *pdev, uint8_t epnum);
extern void usb_clrstall(usb_core_instance *pdev, uint8_t epnum);
extern void usb_flsdevep(usb_core_instance *pdev, uint8_t epnum);
extern uint32_t usb_devepstatusget(usb_core_instance *pdev, uint8_t epnum);
extern void usb_devepstatusset(usb_core_instance *pdev, uint8_t epnum, uint32_t status);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_DRIVER_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
