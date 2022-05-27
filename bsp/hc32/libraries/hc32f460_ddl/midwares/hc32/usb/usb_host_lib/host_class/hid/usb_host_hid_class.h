/**
 *******************************************************************************
 * @file  usb_host_hid_class.h
 * @brief header file for the usb_host_hid_class.c
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
#ifndef __USB_HOST_HID_CLASS_H__
#define __USB_HOST_HID_CLASS_H__

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
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_HID
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/* States for HID State Machine */
typedef enum {
    HID_IDLE = 0,
    HID_SEND_DATA,
    HID_BUSY,
    HID_GET_DATA,
    HID_SYNC,
    HID_POLL,
    HID_ERROR,
}
HID_State;

typedef enum {
    HID_REQ_IDLE = 0,
    HID_REQ_GET_REPORT_DESC,
    HID_REQ_GET_HID_DESC,
    HID_REQ_SET_IDLE,
    HID_REQ_SET_PROTOCOL,
    HID_REQ_SET_REPORT,

}
HID_CtlState;

typedef struct {
    void (*Init)(void);
    void (*Decode)(uint8_t *data);

} HID_cb_TypeDef;

typedef  struct {
    uint8_t   ReportID;
    uint8_t   ReportType;
    uint16_t  UsagePage;
    uint32_t  Usage[2];
    uint32_t  NbrUsage;
    uint32_t  UsageMin;
    uint32_t  UsageMax;
    int32_t   LogMin;
    int32_t   LogMax;
    int32_t   PhyMin;
    int32_t   PhyMax;
    int32_t   UnitExp;
    uint32_t  Unit;
    uint32_t  ReportSize;
    uint32_t  ReportCnt;
    uint32_t  Flag;
    uint32_t  PhyUsage;
    uint32_t  AppUsage;
    uint32_t  LogUsage;
} HID_Report_TypeDef;

/* Structure for HID process */
typedef struct {
    uint8_t              buff[64];
    uint8_t              hc_num_in;
    uint8_t              hc_num_out;
    HID_State            state;
    uint8_t              HIDIntOutEp;
    uint8_t              HIDIntInEp;
    HID_CtlState         ctl_state;
    uint16_t             length;
    uint8_t              ep_addr;
    uint16_t             poll;
    __IO uint16_t        timer;
    HID_cb_TypeDef       *cb;
} HID_Machine_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_HID_REQ_GET_REPORT       (0x01)
#define USB_HID_GET_IDLE             (0x02)
#define USB_HID_GET_PROTOCOL         (0x03)
#define USB_HID_SET_REPORT           (0x09)
#define USB_HID_SET_IDLE             (0x0A)
#define USB_HID_SET_PROTOCOL         (0x0B)

#define HID_MIN_POLL                 (10U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern usb_host_class_callback_func  USBH_HID_cb;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern HOST_STATUS usb_host_set_hidreport(usb_core_instance *pdev,
        USBH_HOST *phost,
        uint8_t reportType,
        uint8_t reportId,
        uint8_t reportLen,
        uint8_t *reportBuff);

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

#endif /* __USB_HOST_HID_CLASS_H__ */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
