/**
 *******************************************************************************
 * @file  usb_host_int.h
 * @brief Head file for usb_host_int.c
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
#ifndef __USB_HOST_INT_H__
#define __USB_HOST_INT_H__

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
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define HCINT_NYET       (1UL << 6)

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @brief  clear the interrupt flag bit
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      the channel index
 * @param  [in] intbit      the interrupt bit of the register HCINTn
 * @retval None
 */
__STATIC_INLINE void usb_host_clrint(usb_core_instance *pdev, uint32_t ch_num, uint32_t intbit)
{
    WRITE_REG32(pdev->regs.HC_REGS[ch_num]->HCINT, intbit);
}

/**
 * @brief  mask the interrupt of ChHltd
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel index of the host application
 * @retval None
 */
__STATIC_INLINE void usb_host_int_mskchhltd(usb_core_instance *pdev, uint32_t ch_num)
{
    CLR_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_CHHM);
}

/**
 * @brief  unmask the interrupt of ChHltd
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel index of the host application
 * @retval None
 */
__STATIC_INLINE void usb_host_int_unmskchhltd(usb_core_instance *pdev, uint32_t ch_num)
{
    SET_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_CHHM);
}

/**
 * @brief  mask the interrupt of ACK
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel index of the host application
 * @retval None
 */
__STATIC_INLINE void usb_host_int_mskack(usb_core_instance *pdev, uint32_t ch_num)
{
    CLR_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_ACKM);
}

/**
 * @brief  unmask the interrupt of ACK
 * @param  [in] pdev        device instance
 * @param  [in] ch_num      channel index of the host application
 * @retval None
 */
__STATIC_INLINE void usb_host_int_unmskack(usb_core_instance *pdev, uint32_t ch_num)
{
    SET_REG32_BIT(pdev->regs.HC_REGS[ch_num]->HCINTMSK, USBFS_HCINTMSK_ACKM);
}

void usb_host_isr(usb_core_instance *pdev);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_INT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


