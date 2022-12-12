/**
 *******************************************************************************
 * @file  usb_host_msc_class.h
 * @brief Head file for usb_host_msc_class.c
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
#ifndef __USB_HOST_MSC_CLASS_H__
#define __USB_HOST_MSC_CLASS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_core.h"
#include "usb_host_stdreq.h"
#include "usb_bsp.h"
#include "usb_host_ctrltrans.h"
#include "usb_host_cfgch.h"
#include "usb_host_msc_class.h"
#include "usb_host_msc_scsi.h"
#include "usb_host_msc_bot.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_MSC
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/* Structure for MSC process */
typedef struct {
    uint8_t              hc_num_in;
    uint8_t              hc_num_out;
    uint8_t              MSC_BulkOutEp;
    uint8_t              MSC_BulkInEp;
    uint16_t             MSC_BulkInEpSize;
    uint16_t             MSC_BulkOutEpSize;
    uint8_t              buff[USBH_MSC_MPS_SIZE];
    uint8_t              maxLun;
} MSC_Machine_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_REQ_BOT_RESET                (0xFFU)
#define USB_REQ_GET_MAX_LUN              (0xFEU)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern usb_host_class_callback_func  USBH_MSC_cb;
extern MSC_Machine_TypeDef    MSC_Machine;
extern uint8_t MSCErrorCount;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

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

#endif  /* __USB_HOST_MSC_CLASS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/




