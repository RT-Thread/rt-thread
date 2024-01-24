/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-14     CDT          first version
 */

#ifndef __DRV_USBD_H__
#define __DRV_USBD_H__

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

/* The bit of the diepint/doepint */
#define XFER_COMPL           (1UL)
#define EPDISABLED           (1UL<<1)
#define TIME_OUT             (1UL<<3)
#define SETUP_BIT            (1UL<<3)
#define INTKNTXFEMP          (1UL<<4)
#define INEPNAKEFF           (1UL<<6)
#define TXFEMP               (1UL<<7)

/* The bit of the GINTSTS */
#define MODEMIS_INT          (1UL<<1)
#define SOF_INT              (1UL<<3)
#define RXFLVL_INT           (1UL<<4)
#define USBSUSP_INT          (1UL<<11)
#define USBRST_INT           (1UL<<12)
#define ENUMDONE_INT         (1UL<<13)
#define INEP_INT             (1UL<<18)
#define OUTEP_INT            (1UL<<19)
#define INCOMPLSOIN          (1UL<<20)
#define INCOMPLSOOUT         (1UL<<21)
#define VBUSV_INT            (1UL<<30)
#define WAKEUP_INT           (1UL<<31)

/* Data packet status for device mode */
#define STS_GOUT_NAK         (1U)
#define STS_DATA_UPDT        (2U)
#define STS_XFER_COMP        (3U)
#define STS_SETUP_COMP       (4U)
#define STS_SETUP_UPDT       (6U)

/* USB EP0 state */
#define USB_EP0_IDLE         (0U)
#define USB_EP0_SETUP        (1U)
#define USB_EP0_DATA_IN      (2U)
#define USB_EP0_DATA_OUT     (3U)
#define USB_EP0_STATUS_IN    (4U)
#define USB_EP0_STATUS_OUT   (5U)
#define USB_EP0_STALL        (6U)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

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
    uint8_t  *(*get_dev_desc)(uint16_t *length);
    uint8_t  *(*get_dev_langiddesc)(uint16_t *length);
    uint8_t  *(*get_dev_manufacturerstr)(uint16_t *length);
    uint8_t  *(*get_dev_productstr)(uint16_t *length);
    uint8_t  *(*get_dev_serialstr)(uint16_t *length);
    uint8_t  *(*get_dev_configstr)(uint16_t *length);
    uint8_t  *(*get_dev_interfacestr)(uint16_t *length);
} usb_dev_desc_func;

typedef struct
{
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

typedef struct
{
    USB_CORE_BASIC_CFGS    basic_cfgs;
    LL_USB_TypeDef            regs;
#ifdef USE_DEVICE_MODE
    USB_DEV_PARAM          dev;
#endif
#ifdef USE_HOST_MODE
    USB_HOST_PARAM         host;
#endif
} usb_core_instance;

typedef struct
{
    void (* Reset)(usb_core_instance *pdev);
    void (* devctrlconnect)(usb_core_instance *pdev, uint8_t conn);
    void (* Suspend)(usb_core_instance *pdev);
    void (* Resume)(usb_core_instance *pdev);
    void (* SOF)(usb_core_instance *pdev);
    void (* SetupStage)(usb_core_instance *pdev);
    void (* DataOutStage)(usb_core_instance *pdev, uint8_t epnum);
    void (* DataInStage)(usb_core_instance *pdev, uint8_t epnum);
    void (* IsoINIncomplete)(usb_core_instance *pdev);
    void (* IsoOUTIncomplete)(usb_core_instance *pdev);
} usb_dev_int_cbk_typedef;


/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @brief  get the IN Endpoint TxFIFO avail space
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint number
 * @retval the avail space in 32-bit words
 */
__STATIC_INLINE uint16_t usb_rdineptxfspcavail(usb_core_instance *pdev, uint32_t epnum)
{
    return (uint16_t)(READ_REG32(pdev->regs.INEP_REGS[epnum]->DTXFSTS) & USBFS_DTXFSTS_INEPTFSAV);
}

/**
 * @brief  set the USB turn around time
 * @param  [in] pdev        device instance
 * @retval None
 */
__STATIC_INLINE void usb_setaroundtim(usb_core_instance *pdev)
{
    SET_REG32_BIT(pdev->regs.GREGS->GUSBCFG, USBFS_GUSBCFG_TRDT);
}

#ifdef __cplusplus
}
#endif

#endif /* __DRV_USBD_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
