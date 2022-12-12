/**
 *******************************************************************************
 * @file  usb_host_hid_mouseapp.c
 * @brief The application layer for USB Host HID Mouse Handling.
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
#include "usb_host_hid_mouseapp.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_HID
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
void mouse_init(void);
void mouse_decode(uint8_t *data);

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
#ifdef USB_INTERNAL_DMA_ENABLED
#if defined   (__CC_ARM) /*!< ARM Compiler */
__align(4)
#elif defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma data_alignment=4
#elif defined (__GNUC__) /*!< GNU Compiler */
#pragma pack(4)
#elif defined  (__TASKING__) /*!< TASKING Compiler */
__align(4)
#endif /* __CC_ARM */
#endif

HID_MOUSE_Data_TypeDef HID_MOUSE_Data;
HID_cb_TypeDef HID_MOUSE_cb = {
    mouse_init,
    mouse_decode,
};

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  initialize the mouse application of the hid class
 * @param  None
 * @retval None
 */
void mouse_init(void)
{
    /* Call User Init*/
    user_mouse_init();
}

/**
 * @brief  decode the mouse report data
 * @param  [in] data        buffer of the hid report data
 * @retval None
 */
void mouse_decode(uint8_t *data)
{
    HID_MOUSE_Data.button = data[0];
    HID_MOUSE_Data.x      = data[1];
    HID_MOUSE_Data.y      = data[2];
    user_mouse_dataprocess(&HID_MOUSE_Data);
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
