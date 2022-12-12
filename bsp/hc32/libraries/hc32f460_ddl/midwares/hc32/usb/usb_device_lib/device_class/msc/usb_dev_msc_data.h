/**
 *******************************************************************************
 * @file  usb_dev_msc_data.h
 * @brief header file for the usb_dev_msc_data.c
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
#ifndef __USB_DEV_MSC_DATA_H__
#define __USB_DEV_MSC_DATA_H__

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
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_MSC
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define MODE_SENSE6_LEN                 (8U)
#define MODE_SENSE10_LEN                (8U)
#define LENGTH_INQUIRY_PAGE00           (7U)
#define LENGTH_FORMAT_CAPACITIES        (20U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern const uint8_t MSC_Page00_Inquiry_Data[LENGTH_INQUIRY_PAGE00];
extern const uint8_t MSC_Mode_Sense6_data[MODE_SENSE6_LEN];
extern const uint8_t MSC_Mode_Sense10_data[MODE_SENSE10_LEN];

/*******************************************************************************
 * Global function prototypes (definition in C source)
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

#endif /* __USB_DEV_MSC_DATA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
