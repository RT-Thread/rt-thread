/**
 *******************************************************************************
 * @file  usb_host_driver.h
 * @brief Head file for usb_host_driver.c
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
#ifndef __USB_HOST_DRIVER_H__
#define __USB_HOST_DRIVER_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_def.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
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
extern void host_driver_init(usb_core_instance *pdev);
extern uint32_t host_driver_hostch_init(usb_core_instance *pdev, uint8_t hc_num);
extern uint32_t host_driver_submitrequest(usb_core_instance *pdev, uint8_t hc_num);
extern uint32_t host_driver_getcurrentspd(usb_core_instance *pdev);
extern uint32_t host_driver_getdmdpstate(usb_core_instance *pdev);
extern uint32_t host_driver_getvbusdrivestate(usb_core_instance *pdev);
extern void host_driver_portrst(usb_core_instance *pdev);
extern uint32_t host_driver_ifdevconnected(usb_core_instance *pdev);
extern uint32_t host_driver_getcurrentfrm(usb_core_instance *pdev);
extern HOST_CH_XFER_STATE host_driver_getxferstate(usb_core_instance *pdev, uint8_t ch_num);
extern uint32_t host_driver_getxfercnt(usb_core_instance *pdev, uint8_t ch_num);
extern HOST_CH_STATUS host_driver_gethostchstate(usb_core_instance *pdev,  uint8_t ch_num);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_DRIVER_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


