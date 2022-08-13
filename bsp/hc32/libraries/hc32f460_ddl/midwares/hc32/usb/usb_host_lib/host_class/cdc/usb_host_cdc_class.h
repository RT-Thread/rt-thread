/**
 *******************************************************************************
 * @file  usb_host_cdc_class.h
 * @brief Head file for usb_host_cdc_class.c
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
#ifndef __USB_HOST_CDC_CLASS_H__
#define __USB_HOST_CDC_CLASS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_cdc_ctrl.h"

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
    CDC_IDLE = 0,
    CDC_READ_DATA,
    CDC_SEND_DATA,
    CDC_DATA_SENT,
    CDC_BUSY,
    CDC_GET_DATA,
    CDC_POLL,
    CDC_CTRL_STATE
}
CDC_State;

typedef struct _CDCXfer {
    volatile CDC_State CDCState;
    uint8_t *pRxTxBuff;
    uint8_t *pFillBuff;
    uint8_t *pEmptyBuff;
    uint32_t BufferLen;
    uint16_t DataLength;
} CDC_Xfer_TypeDef;

typedef struct CDC_UserCb {
    void (*Send)(uint8_t *);
    void (*Receive)(uint8_t *, uint32_t len);

} CDC_Usercb_TypeDef;

typedef struct _CDC_CommInterface {
    uint8_t              hc_num_in;
    uint8_t              hc_num_out;
    uint8_t              notificationEp;
    CDC_State            state;
    uint8_t              buff[8];
    uint16_t             length;
    uint8_t              ep_addr;
}
CDC_CommInterface_Typedef ;

typedef struct _CDC_DataInterface {
    uint8_t              hc_num_in;
    uint8_t              hc_num_out;
    uint8_t              cdcOutEp;
    uint8_t              cdcInEp;
    CDC_State            state;
    uint8_t              buff[8];
    uint16_t             length;
    uint8_t              ep_addr;
}
CDC_DataInterface_Typedef ;

typedef struct _CDC_Process {
    CDC_CommInterface_Typedef CDC_CommItf;
    CDC_DataInterface_Typedef CDC_DataItf;
}
CDC_Machine_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define COMMUNICATION_DEVICE_CLASS_CODE                         (0x02U)
#define COMMUNICATION_INTERFACE_CLASS_CODE                      (0x02U)

#define DATA_INTERFACE_CLASS_CODE                               (0x0AU)

#define RESERVED                                                (0x00U)
#define DIRECT_LINE_CONTROL_MODEL                               (0x01U)
#define ABSTRACT_CONTROL_MODEL                                  (0x02U)
#define TELEPHONE_CONTROL_MODEL                                 (0x03U)
#define MULTICHANNEL_CONTROL_MODEL                              (0x04U)
#define CAPI_CONTROL_MODEL                                      (0x05U)
#define ETHERNET_NETWORKING_CONTROL_MODEL                       (0x06U)
#define ATM_NETWORKING_CONTROL_MODEL                            (0x07U)


#define NO_CLASS_SPECIFIC_PROTOCOL_CODE                         (0x00U)
#define COMMON_AT_COMMAND                                       (0x01U)
#define VENDOR_SPECIFIC                                         (0xFFU)


#define CS_INTERFACE                                            (0x24U)
#define CDC_PAGE_SIZE_64                                        (0x40U)


/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern usb_host_class_callback_func  CDC_cb;
extern CDC_Usercb_TypeDef UserCb;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
void  usb_host_cdc_senddata(uint8_t *data, uint16_t length);
void  usb_host_cdc_enable_receive(usb_core_instance *pdev);
void  usb_host_cdc_disable_receive(usb_core_instance *pdev);


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

#endif  /* __USB_HOST_CDC_CLASS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
