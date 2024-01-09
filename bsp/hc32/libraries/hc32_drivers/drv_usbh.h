/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-25     CDT          first version
 */

#ifndef __DRV_USBH_H__
#define __DRV_USBH_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include "rtdevice.h"
#include "hc32_ll_usb.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_FS_PORT                             (1U)

#define MAX_DATA_LENGTH                         (0x200U)

#define HCINT_NYET                              (1UL << 6)

/* Macro definations for host mode */
#define PID_DATA0                               (0U)
#define PID_DATA2                               (1U)
#define PID_DATA1                               (2U)
#define PID_SETUP                               (3U)
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/* status of the host channel */
typedef enum
{
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

typedef enum
{
    HOST_CH_XFER_IDLE = 0U,
    HOST_CH_XFER_DONE,
    HOST_CH_XFER_UNREADY,
    HOST_CH_XFER_ERROR,
    HOST_CH_XFER_STALL
} HOST_CH_XFER_STATE;

typedef enum
{
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

typedef struct
{
    uint8_t   bmRequest;
    uint8_t   bRequest;
    uint16_t  wValue;
    uint16_t  wIndex;
    uint16_t  wLength;
} USB_SETUP_REQ;

typedef struct
{
    void (*user_init)(void);
    void (*user_devrst)(void);
    void (*user_devconfig)(void);
    void (*user_devsusp)(void);
    void (*user_devresume)(void);
    void (*user_devconn)(void);
    void (*user_devdisconn)(void);
} usb_dev_user_func;

typedef struct
{
    uint16_t                 channel[USB_MAX_TX_FIFOS];
    USB_HOST_CH              hc[USB_MAX_TX_FIFOS];
    __IO uint32_t            is_dev_connect;
    uint8_t                  Rx_Buffer[MAX_DATA_LENGTH];
    __IO uint32_t            ErrCnt[USB_MAX_TX_FIFOS];
    __IO uint32_t            XferCnt[USB_MAX_TX_FIFOS];
    __IO HOST_CH_STATUS      HC_Status[USB_MAX_TX_FIFOS];
    __IO HOST_CH_XFER_STATE  URB_State[USB_MAX_TX_FIFOS];
    __IO uint8_t             devspeed;
} USB_HOST_PARAM;

typedef struct
{
    USB_CORE_BASIC_CFGS    basic_cfgs;
    LL_USB_TypeDef            regs;
#ifdef USE_DEVICE_MODE
    USB_DEV_PARAM          dev;
#endif
#ifdef USE_HOST_MODE
    USB_HOST_PARAM         host;
    void                   *pData;
#endif
} usb_core_instance;



/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
__STATIC_INLINE void usb_host_clrint(usb_core_instance *pdev, uint32_t ch_num, uint32_t intbit)
{
    WRITE_REG32(pdev->regs.HC_REGS[ch_num]->HCINT, intbit);
}

__STATIC_INLINE void usb_host_int_mskchhltd(usb_core_instance *pdev, uint32_t ch_num)
{
    CLR_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_CHHM);
}

__STATIC_INLINE void usb_host_int_unmskchhltd(usb_core_instance *pdev, uint32_t ch_num)
{
    SET_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_CHHM);
}

__STATIC_INLINE void usb_host_int_mskack(usb_core_instance *pdev, uint32_t ch_num)
{
    CLR_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_ACKM);
}

__STATIC_INLINE void usb_host_int_unmskack(usb_core_instance *pdev, uint32_t ch_num)
{
    SET_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_ACKM);
}

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USBH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
