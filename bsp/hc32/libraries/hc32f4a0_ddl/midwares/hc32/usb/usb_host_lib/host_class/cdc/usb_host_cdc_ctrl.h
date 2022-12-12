/**
 *******************************************************************************
 * @file  usb_host_cdc_ctrl.h
 * @brief Head file for usb_host_cdc_ctrl.c
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

#ifndef __USB_HOST_CDC_CTRL_H__
#define __USB_HOST_CDC_CTRL_H__

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
#include "usb_host_ctrltrans.h"
#include "usb_host_cfgch.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CDC
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
typedef enum {
    CDC_SET_LINE_CODING_RQUEST = 0,
    CDC_GET_LINE_CODING_RQUEST,
    CDC_SET_CONTROL_LINE_STATE_REQUEST,
    CDC_ERROR_STATE
}
CDC_Requests;

#define LINE_CODING_STRUCTURE_SIZE                              (0x07U)
typedef union _CDC_LineCodingStructure {
    uint8_t Array[LINE_CODING_STRUCTURE_SIZE];

    struct {

        uint32_t             dwDTERate;    /* Data terminal rate, in bits per second */
        /* Data terminal rate:
        such as 9600, 115200, ... */

        uint8_t              bCharFormat;  /* Stop bits */
        /* Stop bits:
        0 - 1 Stop bit
        1 - 1.5 Stop bits
        2 - 2 Stop bits */

        uint8_t              bParityType;  /* Parity */
        /* Parity:
        0 - None
        1 - Odd
        2 - Even
        3 - Mark
        4 - Space */

        uint8_t                bDataBits;  /* Data bits */
        /* Data bits:
        (5, 6, 7, 8 or 16) */
    } b;
}
CDC_LineCodingTypeDef;

typedef struct _FunctionalDescriptorHeader {
    uint8_t     bLength;            /* Size of this descriptor in bytes */
    uint8_t     bDescriptorType;    /* CS_INTERFACE(24h) descriptor type */
    uint8_t     bDescriptorSubType; /* Header functional descriptor subtype */
    uint16_t    bcdCDC;             /* USB Class Definitions for Communications
                                     Devices Specification release number in
                                     binary-coded decima */
}
CDC_HeaderFuncDesc_TypeDef;

typedef struct _CallMgmtFunctionalDescriptor {
    uint8_t    bLength;            /* Size of this functional descriptor, in bytes */
    uint8_t    bDescriptorType;    /* CS_INTERFACE(24h) */
    uint8_t    bDescriptorSubType; /* Call Management functional descriptor subtype */
    uint8_t    bmCapabilities;     /* The capabilities that this configuration supports */
    /* capabilities:
     D7..D2: RESERVED (Reset to zero)
     D1:     0 - Device sends/receives call management
             information only over the Communications Class
             interface.
             1 - Device can send/receive call management
             information over a Data Class interface.
     D0:     0 - Device does not handle call management
             itself.
             1 - Device handles call management itself
    The previous bits, in combination, identify which call
    management scenario is used. If bit D0 is reset to 0, then the
    value of bit D1 is ignored. In this case, bit D1 is reset to zero
    for future compatibility.*/
    uint8_t    bDataInterface;     /* Interface number of Data Class interface optionally used for call management */
    /* Interface number:
      Zero based index of the interface in this configuration */
}
CDC_CallMgmtFuncDesc_TypeDef;

typedef struct _AbstractCntrlMgmtFunctionalDescriptor {
    uint8_t    bLength;            /* Size of this functional descriptor, in bytes */
    uint8_t    bDescriptorType;    /* CS_INTERFACE(24h) */
    uint8_t    bDescriptorSubType; /* Abstract Control Management functional descriptor subtype */
    uint8_t    bmCapabilities;     /* The capabilities that this configuration supports */
    /* capabilities:(A bit valueof zero means that the request is not supported)
     D7..D4: RESERVED (Reset to zero)
     D3:     1 - Device supports the notification
             Network_Connection.
     D2:     1 - Device supports the request Send_Break
     D1:     1 - Device supports the request combination of
             Set_Line_Coding, Set_Control_Line_State,
             Get_Line_Coding, and the notification
             Serial_State.
     D0:     1 - Device supports the request combination of
             Set_Comm_Feature, Clear_Comm_Feature, and
             Get_Comm_Feature.
    The previous bits, in combination, identify which
    requests/notifications are supported by a
    CommunicationsClass interface with the SubClass code of
    Abstract Control Model. */
}
CDC_AbstCntrlMgmtFuncDesc_TypeDef;

typedef struct _UnionFunctionalDescriptor {
    uint8_t    bLength;                  /* Size of this functional descriptor, in bytes */
    uint8_t    bDescriptorType;          /* CS_INTERFACE(24h) */
    uint8_t    bDescriptorSubType;       /* Union Functional Descriptor SubType */
    uint8_t    bControlInterface;        /* The interface number of the Communications
                                          or Data Class interface, designated as the
                                          controlling interface for the union.*/
    uint8_t    bSubordinateInterface0;   /* Interface number of first subordinate interfacein the union. */
    /*    ...    */
    /* uint8_t    bSubordinateInterfaceN-1; */ /* Interface number of N-1 subordinate interfacein the union. */
}
CDC_UnionFuncDesc_TypeDef;

typedef struct _USBH_CDCInterfaceDesc {
    CDC_HeaderFuncDesc_TypeDef           CDC_HeaderFuncDesc;
    CDC_CallMgmtFuncDesc_TypeDef         CDC_CallMgmtFuncDesc;
    CDC_AbstCntrlMgmtFuncDesc_TypeDef    CDC_AbstCntrlMgmtFuncDesc;
    CDC_UnionFuncDesc_TypeDef            CDC_UnionFuncDesc;
}
CDC_InterfaceDesc_Typedef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CDC_SET_LINE_CODING                                     (0x20U)
#define CDC_GET_LINE_CODING                                     (0x21U)
#define CDC_SET_CONTROL_LINE_STATE                              (0x22U)

#define CDC_ACTIVATE_CARRIER_SIGNAL_RTS                         (0x0002U)
#define CDC_DEACTIVATE_CARRIER_SIGNAL_RTS                       (0x0000U)
#define CDC_ACTIVATE_SIGNAL_DTR                                 (0x0001U)
#define CDC_DEACTIVATE_SIGNAL_DTR                               (0x0000U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern CDC_LineCodingTypeDef             CDC_SetLineCode;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
HOST_STATUS usb_host_cdc_getlinecoding(usb_core_instance *pdev, USBH_HOST *phost);
HOST_STATUS usb_host_cdc_setlinecoding(usb_core_instance *pdev, USBH_HOST *phost);
HOST_STATUS usb_host_cdc_setcontrollinestate(usb_core_instance *pdev, USBH_HOST *phost);
void usb_host_cdc_issue_setlinecoding(usb_core_instance *pdev, USBH_HOST *phost);
void usb_host_cdc_issue_getlinecoding(usb_core_instance *pdev, USBH_HOST *phost);

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

#endif  /* __USB_HOST_CDC_CTRL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
