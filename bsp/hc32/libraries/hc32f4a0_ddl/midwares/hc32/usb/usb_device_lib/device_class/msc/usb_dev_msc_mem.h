/**
 *******************************************************************************
 * @file  usb_dev_msc_mem.h
 * @brief header file for the usb_dev_msc_mem.c
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
#ifndef __USB_DEV_MSC_MEM_H__
#define __USB_DEV_MSC_MEM_H__

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
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_MSC
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
typedef struct {
    int8_t (* Init)(uint8_t lun);
    int8_t (* GetCapacity)(uint8_t lun, uint32_t *block_num, uint32_t *block_size);
    int8_t (* GetMaxLun)(void);
    int8_t (* IsReady)(uint8_t lun);
    int8_t (* Read)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
    int8_t (* Write)(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
    int8_t (* IsWriteProtected)(uint8_t lun);
    int8_t *pInquiry;
} USB_DEV_MSC_cbk_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_DEV_INQUIRY_LENGTH     (36U)

extern USB_DEV_MSC_cbk_TypeDef *msc_fops;

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

#endif /* __USB_DEV_MSC_MEM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
