/**
 *******************************************************************************
 * @file  usb_lib.h
 * @brief Header of the Core Layer Driver
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
#ifndef __USB_LIB_H__
#define __USB_LIB_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_usb.h"
#include "hc32_ll.h"

/**
 * @addtogroup LL_USB_LIB LL USB Lib
 * @{
 */

/**
 * @addtogroup LL_USB_LIB_DEF LL USB Lib Define
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define MAX_DATA_LENGTH                        (0x200U)


/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/* status of the host channel */
typedef enum {
    HOST_CH_IDLE = 0U,
    HOST_CH_XFERCOMPL,
    HOST_CH_CHHLTD,
    HOST_CH_NAK,
    HOST_CH_NYET,
    HOST_CH_STALL,
    HOST_CH_XACTERR,
    HOST_CH_BBLERR,
    HOST_CH_DATATGLERR,
    HOST_CH_AHBERR,
    HOST_CH_FRMOVRUN,
    HOST_CH_BNAINTR,
    HOST_CH_XCS_XACT_ERR,
    HOST_CH_DESC_LST_ROLLINTR
} HOST_CH_STATUS;

typedef enum {
    HOST_CH_XFER_IDLE = 0U,
    HOST_CH_XFER_DONE,
    HOST_CH_XFER_UNREADY,
    HOST_CH_XFER_ERROR,
    HOST_CH_XFER_STALL
} HOST_CH_XFER_STATE;

typedef enum {
    CTRL_START = 0U,
    CTRL_XFRC,
    CTRL_HALTED,
    CTRL_NAK,
    CTRL_STALL,
    CTRL_XACTERR,
    CTRL_BBLERR,
    CTRL_DATATGLERR,
    CTRL_FAIL
} CTRL_HANDLE_STATUS;

typedef struct {
    uint8_t   bmRequest;
    uint8_t   bRequest;
    uint16_t  wValue;
    uint16_t  wIndex;
    uint16_t  wLength;
} USB_SETUP_REQ;

typedef struct {
    uint8_t  *(*get_dev_desc)(uint16_t *length);
    uint8_t  *(*get_dev_langiddesc)(uint16_t *length);
    uint8_t  *(*get_dev_manufacturerstr)(uint16_t *length);
    uint8_t  *(*get_dev_productstr)(uint16_t *length);
    uint8_t  *(*get_dev_serialstr)(uint16_t *length);
    uint8_t  *(*get_dev_configstr)(uint16_t *length);
    uint8_t  *(*get_dev_interfacestr)(uint16_t *length);
} usb_dev_desc_func;

typedef struct {
    void (*class_init)(void *pdev);
    void (*class_deinit)(void *pdev);
    uint8_t (*ep0_setup)(void *pdev, USB_SETUP_REQ *req);
    void (*ep0_datain)(void *pdev);
    void (*ep0_dataout)(void *pdev);
    uint8_t  *(*class_getconfigdesc)(uint16_t *length);
    uint8_t (*class_sof)(void *pdev);
    void (*class_datain)(void *pdev, uint8_t epnum);
    void (*class_dataout)(void *pdev, uint8_t epnum);
    void (*class_syn_in_incomplt)(void *pdev);
    void (*class_syn_out_incomplt)(void *pdev);
} usb_dev_class_func;

typedef struct {
    void (*user_init)(void);
    void (*user_devrst)(void);
    void (*user_devconfig)(void);
    void (*user_devsusp)(void);
    void (*user_devresume)(void);
    void (*user_devconn)(void);
    void (*user_devdisconn)(void);
} usb_dev_user_func;

typedef struct {
    __IO uint8_t           device_config;
    __IO uint8_t           device_address;
    __IO uint8_t           device_state;
    __IO uint8_t           device_old_status;
    __IO uint8_t           device_cur_status;
    __IO uint8_t           connection_status;
    __IO uint8_t           device_remote_wakeup;
    __IO uint8_t           test_mode;
    USB_DEV_EP             in_ep[USB_MAX_TX_FIFOS];
    USB_DEV_EP             out_ep[USB_MAX_TX_FIFOS];
    uint8_t                setup_pkt_buf[24];
    usb_dev_class_func     *class_callback;
    usb_dev_user_func      *user_callback;
    usb_dev_desc_func      *desc_callback;
} USB_DEV_PARAM;

typedef struct {
    uint16_t                 channel[USB_MAX_TX_FIFOS];
    USB_HOST_CH              hc[USB_MAX_TX_FIFOS];
    __IO uint32_t            is_dev_connect;
    uint8_t                  Rx_Buffer[MAX_DATA_LENGTH];
    __IO uint32_t            ErrCnt[USB_MAX_TX_FIFOS];
    __IO uint32_t            XferCnt[USB_MAX_TX_FIFOS];
    __IO HOST_CH_STATUS      HC_Status[USB_MAX_TX_FIFOS];
    __IO HOST_CH_XFER_STATE  URB_State[USB_MAX_TX_FIFOS];
} USB_HOST_PARAM;

typedef struct {
    USB_CORE_BASIC_CFGS    basic_cfgs;
    LL_USB_TypeDef            regs;
#ifdef USE_DEVICE_MODE
    USB_DEV_PARAM          dev;
#endif
#ifdef USE_HOST_MODE
    USB_HOST_PARAM         host;
#endif
} usb_core_instance;


/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __USB_LIB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
