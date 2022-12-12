/**
 *******************************************************************************
 * @file  usb_dev_msc_bot.c
 * @brief USB DEV bulk only transfer functions.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_msc_bot.h"
#include "usb_dev_msc_scsi.h"
#include "usb_dev_ctrleptrans.h"
#include "usb_dev_msc_mem.h"
#include "usb_dev_driver.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_MSC USB Device MSC
 * @{
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

uint16_t MSC_BOT_DataLen;
uint8_t  MSC_BOT_State;
static uint8_t  MSC_BOT_Status;

__USB_ALIGN_BEGIN uint8_t MSC_BOT_Data[MSC_MEDIA_PACKET];

__USB_ALIGN_BEGIN MSC_BOT_CBW_TypeDef MSC_BOT_cbw;

__USB_ALIGN_BEGIN MSC_BOT_CSW_TypeDef MSC_BOT_csw;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Send the requested data
 * @param  [in] pdev        device instance
 * @param  [in] buf         pointer for data buffer
 * @param  [in] length      data Length in bytes
 * @retval None
 */
static void msc_bot_txdata(usb_core_instance *pdev, uint8_t *buf, uint16_t length)
{
    length                    = (uint16_t)LL_MIN(MSC_BOT_cbw.dDataLength, length);
    MSC_BOT_csw.dDataResidue -= length;
    MSC_BOT_csw.bStatus       = CSW_CMD_PASSED;
    MSC_BOT_State             = BOT_SEND_DATA;
    usb_deveptx(pdev, MSC_IN_EP, buf, (uint32_t)length);
}

/**
 * @brief  abort current transfer
 * @param  [in] pdev        device instance
 * @retval None
 */
static void msc_bot_abort(usb_core_instance *pdev)
{
    if ((MSC_BOT_cbw.bmFlags == (uint8_t)0) &&
            (MSC_BOT_cbw.dDataLength != (uint32_t)0) &&
            (MSC_BOT_Status == BOT_STATE_NORMAL)) {
        usb_stalldevep(pdev, MSC_OUT_EP);
    }
    usb_stalldevep(pdev, MSC_IN_EP);
    if (MSC_BOT_Status == BOT_STATE_ERROR) {
        usb_readytorx(pdev, MSC_OUT_EP, (uint8_t *)&MSC_BOT_cbw, BOT_CBW_LENGTH);
    }
}

/**
 * @brief  decodes the CBW command and set the BOT state machine accordingly
 * @param  [in] pdev        device instance
 * @retval None
 */
static void msc_bot_decode_cbw(usb_core_instance *pdev)
{

    MSC_BOT_csw.dTag         = MSC_BOT_cbw.dTag;
    MSC_BOT_csw.dDataResidue = MSC_BOT_cbw.dDataLength;

    if ((usb_getrxcnt(pdev, MSC_OUT_EP) != BOT_CBW_LENGTH) ||
            (MSC_BOT_cbw.dSignature != BOT_CBW_SIGNATURE) ||
            (MSC_BOT_cbw.bLUN > 1U) ||
            (MSC_BOT_cbw.bCBLength < 1U) ||
            (MSC_BOT_cbw.bCBLength > 16U)) {
        scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
        MSC_BOT_Status = BOT_STATE_ERROR;
        msc_bot_abort(pdev);

    } else {
        if (scsi_cmdprocess(pdev, MSC_BOT_cbw.bLUN, &MSC_BOT_cbw.CB[0]) < 0) {
            msc_bot_abort(pdev);
        } else if ((MSC_BOT_State != BOT_DATA_IN) &&
                   (MSC_BOT_State != BOT_DATA_OUT) &&
                   (MSC_BOT_State != BOT_LAST_DATA_IN)) {
            if (MSC_BOT_DataLen > (uint16_t)0) {
                msc_bot_txdata(pdev, MSC_BOT_Data, MSC_BOT_DataLen);
            } else {
                msc_bot_txcsw(pdev, CSW_CMD_PASSED);
            }
        } else {
            ;
        }
    }
}

/**
 * @brief  initialize the BOT Process
 * @param  [in] pdev        device instance
 * @retval None
 */
void msc_bot_init(usb_core_instance *pdev)
{
    MSC_BOT_State  = BOT_IDLE;
    MSC_BOT_Status = BOT_STATE_NORMAL;
    msc_fops->Init(0U);

    usb_flsdevep(pdev, MSC_OUT_EP);
    usb_flsdevep(pdev, MSC_IN_EP);
    /* Prapare EP to Receive First BOT command */
    usb_readytorx(pdev, MSC_OUT_EP, (uint8_t *)&MSC_BOT_cbw, BOT_CBW_LENGTH);
}

/**
 * @brief  resets the BOT Machine
 * @param  [in] pdev        device instance
 * @retval None
 */
void msc_bot_rst(usb_core_instance *pdev)
{
    MSC_BOT_State  = BOT_IDLE;
    MSC_BOT_Status = BOT_STATE_RECOVERY;
    /* Prapare OUT EP to Receive First BOT command */
    usb_readytorx(pdev, MSC_OUT_EP, (uint8_t *)&MSC_BOT_cbw, BOT_CBW_LENGTH);
}

/**
 * @brief  deinitialize the BOT Machine
 * @param  [in] pdev        device instance
 * @retval None
 */
void msc_bot_deinit(usb_core_instance *pdev)
{
    MSC_BOT_State = BOT_IDLE;
}

/**
 * @brief  process BOT IN data stage
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint index
 * @retval None
 */
void msc_bot_datain(usb_core_instance *pdev, uint8_t epnum)
{
    switch (MSC_BOT_State) {
        case BOT_DATA_IN:
            if (scsi_cmdprocess(pdev, MSC_BOT_cbw.bLUN, &MSC_BOT_cbw.CB[0]) < 0) {
                msc_bot_txcsw(pdev, CSW_CMD_FAILED);
            }
            break;
        case BOT_SEND_DATA:
        case BOT_LAST_DATA_IN:
            msc_bot_txcsw(pdev, CSW_CMD_PASSED);
            break;
        default:
            break;
    }
}

/**
 * @brief  proccess MSC OUT data stage
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint number
 * @retval None
 */
void msc_bot_dataout(usb_core_instance *pdev, uint8_t epnum)
{
    switch (MSC_BOT_State) {
        case BOT_IDLE:
            msc_bot_decode_cbw(pdev);
            break;
        case BOT_DATA_OUT:
            if (scsi_cmdprocess(pdev, MSC_BOT_cbw.bLUN, &MSC_BOT_cbw.CB[0]) < 0) {
                msc_bot_txcsw(pdev, CSW_CMD_FAILED);
            }
            break;
        default:
            break;
    }
}

/**
 * @brief  send the Command Status Wrapper
 * @param  [in] pdev        device instance
 * @param  [in] CSW_Status  CSW status
 * @retval None
 */
void msc_bot_txcsw(usb_core_instance *pdev, uint8_t CSW_Status)
{
    MSC_BOT_csw.dSignature = BOT_CSW_SIGNATURE;
    MSC_BOT_csw.bStatus    = CSW_Status;
    MSC_BOT_State          = BOT_IDLE;
    usb_deveptx(pdev, MSC_IN_EP, (uint8_t *)&MSC_BOT_csw, BOT_CSW_LENGTH);
    /* Prapare EP to Receive next Cmd */
    usb_readytorx(pdev, MSC_OUT_EP, (uint8_t *)&MSC_BOT_cbw, BOT_CBW_LENGTH);
}

/**
 * @brief  Complete the clear feature request
 * @param  [in] pdev        device instance
 * @param  [in] epnum       endpoint number
 * @retval None
 */
void msc_bot_complete_clearfeature(usb_core_instance *pdev, uint8_t epnum)
{
    if (MSC_BOT_Status == BOT_STATE_ERROR) {
        usb_stalldevep(pdev, MSC_IN_EP);
        MSC_BOT_Status = BOT_STATE_NORMAL;
    } else if (((epnum & 0x80U) == 0x80U) && (MSC_BOT_Status != BOT_STATE_RECOVERY)) {
        msc_bot_txcsw(pdev, CSW_CMD_FAILED);
    } else {
        ;
    }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
