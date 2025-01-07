/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-07-11     QT-one       first version
 */

#ifndef __HT32_USBD_INT_H__
#define __HT32_USBD_INT_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#include "ht32_usbd_core.h"

#ifdef __cplusplus
extern "C" {
#endif

    
    
    
    /* º¯ÊýÉùÃ÷ */
    void usbd_sof_callback(USBDCore_TypeDef *pCore);
    void usbd_reset_callback(USBDCore_TypeDef *pCore);
    void usbd_suspend_callback(USBDCore_TypeDef *pCore);
    void usbd_resume_callback(USBDCore_TypeDef *pCore);
    
    void usbd_setup_callback(USBDCore_TypeDef *pCore);
    void usbd_ep0_in_callback(USBDCore_TypeDef *pCore);
    void usbd_ep0_out_callback(USBDCore_TypeDef *pCore);
    
    void usbd_ep_in_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn);
    void usbd_ep_out_callback(USBDCore_TypeDef *pCore, USBD_EPTn_Enum EPTn);
    
//    void USB_Configuration(USBDCore_TypeDef *pCore);
    
    
    
#ifdef __cplusplus
}
#endif

#endif /* __HT32_USBD_INT_H__ */
