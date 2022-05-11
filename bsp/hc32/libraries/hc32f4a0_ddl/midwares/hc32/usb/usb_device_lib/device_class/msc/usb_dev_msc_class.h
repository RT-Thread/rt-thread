/**
 *******************************************************************************
 * @file  usb_dev_msc_class.h
 * @brief header file for the usb_dev_msc_class.c
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
#ifndef __USB_DEV_MSC_CLASS_H__
#define __USB_DEV_MSC_CLASS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_MSC
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define BOT_GET_MAX_LUN              (0xFEU)
#define BOT_RESET                    (0xFFU)
#define USB_MSC_CONFIG_DESC_SIZ      (32U)

#define MSC_EPIN_SIZE                (MSC_MAX_PACKET)
#define MSC_EPOUT_SIZE               (MSC_MAX_PACKET)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
extern usb_dev_class_func usb_dev_msc_cbk;

/* MSC Device library callbacks */
extern void usb_dev_msc_init(void *pdev);
extern void usb_dev_msc_deinit(void *pdev);
extern uint8_t usb_dev_msc_setup(void *pdev, USB_SETUP_REQ *req);
extern void usb_dev_msc_datain(void *pdev, uint8_t epnum);
extern void usb_dev_msc_dataout(void *pdev, uint8_t epnum);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_DEV_MSC_CLASS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
