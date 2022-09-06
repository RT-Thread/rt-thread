/**
 *******************************************************************************
 * @file  usb_dev_msc_bot.h
 * @brief header file for the usb_dev_msc_bot.c
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
#ifndef __USB_DEV_MSC_BOT_H__
#define __USB_DEV_MSC_BOT_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_core.h"

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
    uint32_t dSignature;
    uint32_t dTag;
    uint32_t dDataLength;
    uint8_t  bmFlags;
    uint8_t  bLUN;
    uint8_t  bCBLength;
    uint8_t  CB[16];
} MSC_BOT_CBW_TypeDef;

typedef struct {
    uint32_t dSignature;
    uint32_t dTag;
    uint32_t dDataResidue;
    uint8_t  bStatus;
} MSC_BOT_CSW_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define BOT_IDLE                      (0U)       /* Idle state */
#define BOT_DATA_OUT                  (1U)       /* Data Out state */
#define BOT_DATA_IN                   (2U)       /* Data In state */
#define BOT_LAST_DATA_IN              (3U)       /* Last Data In Last */
#define BOT_SEND_DATA                 (4U)       /* Send Immediate data */

#define BOT_CBW_SIGNATURE             (0x43425355UL)
#define BOT_CSW_SIGNATURE             (0x53425355UL)
#define BOT_CBW_LENGTH                (31U)
#define BOT_CSW_LENGTH                (13U)

/* CSW Status Definitions */
#define CSW_CMD_PASSED                (0x00U)
#define CSW_CMD_FAILED                (0x01U)
#define CSW_PHASE_ERROR               (0x02U)

/* BOT Status */
#define BOT_STATE_NORMAL              (0U)
#define BOT_STATE_RECOVERY            (1U)
#define BOT_STATE_ERROR               (2U)

#define DIR_IN                        (0U)
#define DIR_OUT                       (1U)
#define BOTH_DIR                      (2U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern uint8_t  MSC_BOT_Data[MSC_MEDIA_PACKET];
extern uint16_t MSC_BOT_DataLen;
extern uint8_t  MSC_BOT_State;
extern MSC_BOT_CBW_TypeDef MSC_BOT_cbw;
extern MSC_BOT_CSW_TypeDef MSC_BOT_csw;

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
extern void msc_bot_init(usb_core_instance *pdev);
extern void msc_bot_rst(usb_core_instance *pdev);
extern void msc_bot_deinit(usb_core_instance *pdev);
extern void msc_bot_datain(usb_core_instance *pdev, uint8_t epnum);
extern void msc_bot_dataout(usb_core_instance *pdev, uint8_t epnum);
extern void msc_bot_txcsw(usb_core_instance *pdev, uint8_t CSW_Status);
extern void msc_bot_complete_clearfeature(usb_core_instance *pdev, uint8_t epnum);

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

#endif /* __USB_DEV_MSC_BOT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
