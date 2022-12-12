/**
 *******************************************************************************
 * @file  usb_dev_int.h
 * @brief Peripheral Device Interface Layer
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
#ifndef __USB_DEV_INT_H__
#define __USB_DEV_INT_H__

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
 * @addtogroup LL_USB_DEV_CORE
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* The bit of the diepint/doepint */
#define XFER_COMPL        (1UL)
#define EPDISABLED        (1UL<<1)
#define TIME_OUT          (1UL<<3)
#define SETUP_BIT         (1UL<<3)
#define INTKNTXFEMP       (1UL<<4)
#define INEPNAKEFF        (1UL<<6)
#define TXFEMP            (1UL<<7)

/* The bit of the GINTSTS */
#define MODEMIS_INT       (1UL<<1)
#define SOF_INT           (1UL<<3)
#define RXFLVL_INT        (1UL<<4)
#define USBSUSP_INT       (1UL<<11)
#define USBRST_INT        (1UL<<12)
#define ENUMDONE_INT      (1UL<<13)
#define INEP_INT          (1UL<<18)
#define OUTEP_INT         (1UL<<19)
#define INCOMPLSOIN       (1UL<<20)
#define INCOMPLSOOUT      (1UL<<21)
#define VBUSV_INT         (1UL<<30)
#define WAKEUP_INT        (1UL<<31)

/* Data packet status for device mode */
#define STS_GOUT_NAK      (1U)
#define STS_DATA_UPDT     (2U)
#define STS_XFER_COMP     (3U)
#define STS_SETUP_COMP    (4U)
#define STS_SETUP_UPDT    (6U)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
typedef struct {
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

extern usb_dev_int_cbk_typedef *dev_int_cbkpr;
extern void usb_isr_handler(usb_core_instance *pdev);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_INT_H__ */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
