/**
 *******************************************************************************
 * @file  usb_dev_msc_scsi.c
 * @brief This file provides all the USBD SCSI layer functions.
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
#include "usb_dev_msc_mem.h"
#include "usb_dev_msc_data.h"
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
 * @addtogroup LL_USB_DEV_MSC
 * @{
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint32_t SCSI_blk_size;
static uint32_t SCSI_blk_nbr;
static uint64_t SCSI_blk_addr;
static uint32_t SCSI_blk_len;
static usb_core_instance *cdev;

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
SCSI_Sense_TypeDef SCSI_Sense[SENSE_LIST_DEEPTH];
uint8_t  SCSI_Sense_Head;
uint8_t  SCSI_Sense_Tail;

/*******************************************************************************
 * Local function prototypes
 ******************************************************************************/
int8_t scsi_testunitready(uint8_t lun);
int8_t scsi_inquiry(uint8_t lun, uint8_t *params);
int8_t scsi_readformatcapacity(uint8_t lun);
int8_t scsi_readcapacity10(uint8_t lun);
int8_t scsi_requestsense(uint8_t *params);
int8_t scsi_startstopuint(void);
int8_t scsi_modesense6(uint8_t lun);
int8_t scsi_modesense10(void);
int8_t scsi_write10(uint8_t lun, uint8_t *params);
int8_t scsi_read10(uint8_t lun, uint8_t *params);
int8_t scsi_verify10(uint8_t lun, uint8_t *params);
int8_t scsi_addressrangecheck(uint32_t blk_offset, uint16_t blk_nbr);
int8_t scsi_processread(uint8_t lun);
int8_t scsi_processwrite(uint8_t lun);

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Processes SCSI commands
 * @param  [in] pdev        device instance
 * @param  [in] lun         number of logical unit
 * @param  [in] params      command
 * @retval status
 */
int8_t scsi_cmdprocess(usb_core_instance *pdev, uint8_t lun, uint8_t *params)
{
    int8_t Res;
    cdev = pdev;

    if (params[0] == SCSI_TEST_UNIT_READY) {
        Res = scsi_testunitready(lun);
    } else if (params[0] == SCSI_REQUEST_SENSE) {
        Res = scsi_requestsense(params);
    } else if (params[0] == SCSI_INQUIRY) {
        Res = scsi_inquiry(lun, params);
    } else if (params[0] == SCSI_START_STOP_UNIT) {
        Res = scsi_startstopuint();
    } else if (params[0] == SCSI_ALLOW_MEDIUM_REMOVAL) {
        Res = scsi_startstopuint();
    } else if (params[0] == SCSI_MODE_SENSE6) {
        Res = scsi_modesense6(lun);
    } else if (params[0] == SCSI_MODE_SENSE10) {
        Res = scsi_modesense10();
    } else if (params[0] == SCSI_READ_FORMAT_CAPACITIES) {
        Res = scsi_readformatcapacity(lun);
    } else if (params[0] == SCSI_READ_CAPACITY10) {
        Res = scsi_readcapacity10(lun);
    } else if (params[0] == SCSI_READ10) {
        Res = scsi_read10(lun, params);
    } else if (params[0] == SCSI_WRITE10) {
        Res = scsi_write10(lun, params);
    } else if (params[0] == SCSI_VERIFY10) {
        Res = scsi_verify10(lun, params);
    } else {
        scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
        Res = (int8_t) -1;
    }
    return Res;
}

/**
 * @brief  Processes SCSI Test Unit Ready Command
 * @param  [in] lun         number of logical unit
 * @retval status
 */
int8_t scsi_testunitready(uint8_t lun)
{
    int8_t i8Ret;
    i8Ret = (int8_t)0;
    /* case 9 : Hi > D0 */
    if (MSC_BOT_cbw.dDataLength != 0U) {
        scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
        i8Ret = (int8_t) -1;
    } else {
        if (msc_fops->IsReady(lun) != 0U) {
            scsi_sensecode(NOT_READY, MEDIUM_NOT_PRESENT);
            i8Ret = (int8_t) -1;
        } else {
            MSC_BOT_DataLen = 0U;
        }
    }
    return i8Ret;
}

/**
 * @brief  Processes inquiry command
 * @param  [in] lun         number of logical unit
 * @param  [in] params      command
 * @retval status
 */
int8_t scsi_inquiry(uint8_t lun, uint8_t *params)
{
    const uint8_t *pPage;
    uint16_t len;

    if ((params[1] & 0x01U) != 0U) {
        pPage = (const uint8_t *)MSC_Page00_Inquiry_Data;
        len   = LENGTH_INQUIRY_PAGE00;
    } else {

        pPage = (uint8_t *)&msc_fops->pInquiry[lun * USB_DEV_INQUIRY_LENGTH];
        len   = (uint16_t)pPage[4] + (uint16_t)5;

        if (params[4] <= len) {
            len = params[4];
        }
    }
    MSC_BOT_DataLen = len;

    while (len != 0U) {
        len--;
        MSC_BOT_Data[len] = pPage[len];
    }
    return (int8_t)0;
}

/**
 * @brief  Processes Read Capacity10 command
 * @param  [in] lun         number of logical unit
 * @retval status
 */
int8_t scsi_readcapacity10(uint8_t lun)
{
    int8_t i8Ret = (int8_t)0;
    if (msc_fops->GetCapacity(lun, &SCSI_blk_nbr, &SCSI_blk_size) != 0U) {
        scsi_sensecode(NOT_READY, MEDIUM_NOT_PRESENT);
        i8Ret = (int8_t) -1;
    } else {
        MSC_BOT_Data[0] = (uint8_t)((SCSI_blk_nbr - 1U) >> 24U);
        MSC_BOT_Data[1] = (uint8_t)((SCSI_blk_nbr - 1U) >> 16U);
        MSC_BOT_Data[2] = (uint8_t)((SCSI_blk_nbr - 1U) >> 8U);
        MSC_BOT_Data[3] = (uint8_t)(SCSI_blk_nbr - 1U);

        MSC_BOT_Data[4] = (uint8_t)(SCSI_blk_size >> 24U);
        MSC_BOT_Data[5] = (uint8_t)(SCSI_blk_size >> 16U);
        MSC_BOT_Data[6] = (uint8_t)(SCSI_blk_size >> 8U);
        MSC_BOT_Data[7] = (uint8_t)(SCSI_blk_size);
        MSC_BOT_DataLen = 8U;
    }
    return i8Ret;
}

/**
 * @brief  Processes Read Format Capacity command
 * @param  [in] lun         number of logical unit
 * @retval status
 */
int8_t scsi_readformatcapacity(uint8_t lun)
{
    int8_t i8Ret = (int8_t)0;
    uint32_t blk_size;
    uint32_t blk_nbr;
    uint16_t i;

    i = 0U;
    while (i < 12U) {
        MSC_BOT_Data[i++] = 0U;
    }

    if (msc_fops->GetCapacity(lun, &blk_nbr, &blk_size) != 0U) {
        scsi_sensecode(NOT_READY, MEDIUM_NOT_PRESENT);
        i8Ret = (int8_t) -1;
    } else {
        MSC_BOT_Data[3]  = 0x08U;
        MSC_BOT_Data[4]  = (uint8_t)((blk_nbr - 1U) >> 24U);
        MSC_BOT_Data[5]  = (uint8_t)((blk_nbr - 1U) >> 16U);
        MSC_BOT_Data[6]  = (uint8_t)((blk_nbr - 1U) >> 8U);
        MSC_BOT_Data[7]  = (uint8_t)(blk_nbr - 1U);

        MSC_BOT_Data[8]  = 0x02U;
        MSC_BOT_Data[9]  = (uint8_t)(blk_size >> 16U);
        MSC_BOT_Data[10] = (uint8_t)(blk_size >> 8U);
        MSC_BOT_Data[11] = (uint8_t)(blk_size);

        MSC_BOT_DataLen  = 12U;
    }
    return i8Ret;
}

/**
 * @brief  Processes Mode Sense6 command
 * @param  [in] lun         number of logical unit
 * @retval status
 */
int8_t scsi_modesense6(uint8_t lun)
{
    uint16_t len;
    len = 8U;
    MSC_BOT_DataLen = len;
    while (0U != len) {
        len--;
        MSC_BOT_Data[len] = MSC_Mode_Sense6_data[len];
    }
    return (int8_t)0;
}

/**
 * @brief  processes Mode Sense10 command
 * @param  None
 * @retval status
 */
int8_t scsi_modesense10(void)
{
    uint16_t len = 8U;

    MSC_BOT_DataLen = len;
    while (0U != len) {
        len--;
        MSC_BOT_Data[len] = MSC_Mode_Sense10_data[len];
    }
    return (int8_t)0;
}

/**
 * @brief  processes Request Sense command
 * @param  [in] params          command
 * @retval status
 */
int8_t scsi_requestsense(uint8_t *params)
{
    uint8_t i;

    i = 0U;
    while (i < REQUEST_SENSE_DATA_LEN) {
        MSC_BOT_Data[i++] = 0U;
    }
    MSC_BOT_Data[0] = 0x70U;
    MSC_BOT_Data[7] = REQUEST_SENSE_DATA_LEN - 6U;
    if ((SCSI_Sense_Head != SCSI_Sense_Tail)) {
        MSC_BOT_Data[2]  = (uint8_t)SCSI_Sense[SCSI_Sense_Head].Skey;
        MSC_BOT_Data[12] = (uint8_t)SCSI_Sense[SCSI_Sense_Head].w.b.ASCQ;
        MSC_BOT_Data[13] = (uint8_t)SCSI_Sense[SCSI_Sense_Head].w.b.ASC;
        SCSI_Sense_Head++;
        if (SCSI_Sense_Head == SENSE_LIST_DEEPTH) {
            SCSI_Sense_Head = 0U;
        }
    }
    MSC_BOT_DataLen = REQUEST_SENSE_DATA_LEN;
    if (params[4] <= REQUEST_SENSE_DATA_LEN) {
        MSC_BOT_DataLen = params[4];
    }
    return (int8_t)0;
}

/**
 * @brief  Loads the last error code in the error list
 * @param  [in] sKey        Sense Key
 * @param  [in] ASC         Additional Sense Key
 * @retval None
 */
void scsi_sensecode(uint8_t sKey, uint8_t ASC)
{
    SCSI_Sense[SCSI_Sense_Tail].Skey  = (char)sKey;
    SCSI_Sense[SCSI_Sense_Tail].w.ASC = (uint32_t)ASC << 8U;
    SCSI_Sense_Tail++;
    if (SCSI_Sense_Tail == SENSE_LIST_DEEPTH) {
        SCSI_Sense_Tail = 0U;
    }
}

/**
 * @brief  processes Start Stop Unit command
 * @param  None
 * @retval status
 */
int8_t scsi_startstopuint(void)
{
    MSC_BOT_DataLen = 0U;
    return (int8_t)0;
}

/**
 * @brief  processes Read10 command
 * @param  [in] lun         number of logical unit
 * @param  [in] params      command
 * @retval status
 */
int8_t scsi_read10(uint8_t lun, uint8_t *params)
{
    int8_t i8Ret = (int8_t)0;
    if (MSC_BOT_State == BOT_IDLE) {
        /* case 10 : Ho <> Di */
        if ((MSC_BOT_cbw.bmFlags & 0x80U) != 0x80U) {
            scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
            i8Ret = (int8_t) -1;
        } else if (msc_fops->IsReady(lun) != 0U) {
            scsi_sensecode(NOT_READY, MEDIUM_NOT_PRESENT);
            i8Ret = (int8_t) -1;
        } else {
            SCSI_blk_addr = ((uint64_t)params[2] << 24U) | \
                            ((uint64_t)params[3] << 16U) | \
                            ((uint64_t)params[4] << 8U) | \
                            (uint64_t)params[5];

            SCSI_blk_len = ((uint32_t)params[7] << 8U) | \
                           (uint32_t)params[8];


            if (scsi_addressrangecheck((uint32_t)SCSI_blk_addr, (uint16_t)SCSI_blk_len) < 0) {
                i8Ret = (int8_t) -1;            /* error */
            } else {
                MSC_BOT_State  = BOT_DATA_IN;
                SCSI_blk_addr *= SCSI_blk_size;
                SCSI_blk_len  *= SCSI_blk_size;
                /* cases 4,5 : Hi <> Dn */
                if (MSC_BOT_cbw.dDataLength != SCSI_blk_len) {
                    scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
                    i8Ret = (int8_t) -1;
                }
            }
        }
    }
    if (((int8_t) -1) != i8Ret) {
        MSC_BOT_DataLen = (uint16_t)MSC_MEDIA_PACKET;
        i8Ret = scsi_processread(lun);
    }
    return i8Ret;
}

/**
 * @brief  processes Write10 command
 * @param  [in] lun         number of logical unit
 * @param  [in] params      command
 * @retval status
 */
int8_t scsi_write10(uint8_t lun, uint8_t *params)
{
    int8_t i8Ret = (int8_t)0;
    if (MSC_BOT_State == BOT_IDLE) {
        /* case 8 : Hi <> Do */
        if ((MSC_BOT_cbw.bmFlags & 0x80U) == 0x80U) {
            scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
            i8Ret = (int8_t) -1;
        } else {
            if (msc_fops->IsReady(lun) != 0U) {
                scsi_sensecode(NOT_READY, MEDIUM_NOT_PRESENT);
                i8Ret = (int8_t) -1;
            }
            /* Check If media is write-protected */
            else if (msc_fops->IsWriteProtected(lun) != 0U) {
                scsi_sensecode(NOT_READY, WRITE_PROTECTED);
                i8Ret = (int8_t) -1;
            } else {
                SCSI_blk_addr = ((uint64_t)params[2] << 24U) | \
                                ((uint64_t)params[3] << 16U) | \
                                ((uint64_t)params[4] << 8U) | \
                                (uint64_t)params[5];
                SCSI_blk_len  = ((uint32_t)params[7] << 8U) | \
                                (uint32_t)params[8];
                /* check if LBA address is in the right range */
                if (scsi_addressrangecheck((uint32_t)SCSI_blk_addr, (uint16_t)SCSI_blk_len) < 0) {
                    i8Ret = (int8_t) -1;            /* error */
                } else {
                    SCSI_blk_addr *= SCSI_blk_size;
                    SCSI_blk_len  *= SCSI_blk_size;
                    /* cases 3,11,13 : Hn,Ho <> D0 */
                    if (MSC_BOT_cbw.dDataLength != SCSI_blk_len) {
                        scsi_sensecode(ILLEGAL_REQUEST, INVALID_CDB);
                        i8Ret = (int8_t) -1;
                    } else {
                        /* Prepare EP to receive first data packet */
                        MSC_BOT_State = BOT_DATA_OUT;
                        usb_readytorx(cdev, MSC_OUT_EP, MSC_BOT_Data, (uint16_t)LL_MIN(SCSI_blk_len, MSC_MEDIA_PACKET));
                    }
                }
            }
        }
    } else { /* Write Process ongoing */
        i8Ret = scsi_processwrite(lun);
    }
    return i8Ret;
}

/**
 * @brief  processes Verify10 command
 * @param  [in] lun         number of logical unit
 * @param  [in] params      command
 * @retval status
 */
int8_t scsi_verify10(uint8_t lun, uint8_t *params)
{
    int8_t i8Ret;

    i8Ret = (int8_t)0;
    if ((params[1] & 0x02U) == 0x02U) {
        scsi_sensecode(ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
        i8Ret = (int8_t) -1;                /* Error, Verify Mode Not supported */
    } else if (scsi_addressrangecheck((uint32_t)SCSI_blk_addr, (uint16_t)SCSI_blk_len) < (int8_t)0) {
        i8Ret = (int8_t) -1;                /* error */
    } else {
        MSC_BOT_DataLen = 0U;
    }
    return i8Ret;
}

/**
 * @brief  checks the address range
 * @param  [in] blk_offset      first block address
 * @param  [in] blk_nbr         number of block to be processed
 * @retval status
 */
int8_t scsi_addressrangecheck(uint32_t blk_offset, uint16_t blk_nbr)
{
    int8_t i8Ret = (int8_t)0;
    if ((blk_offset + blk_nbr) > SCSI_blk_nbr) {
        scsi_sensecode(ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
        i8Ret = (int8_t) -1;
    }
    return i8Ret;
}

/**
 * @brief  handles Read Process
 * @param  [in] lun         number of logical unit
 * @retval status
 */
int8_t scsi_processread(uint8_t lun)
{
    uint32_t len;
    int8_t i8Ret = (int8_t)0;

    len = LL_MIN(SCSI_blk_len, MSC_MEDIA_PACKET);

    if (SCSI_blk_size == 0U) {
        i8Ret = (int8_t) -1;
    } else if (msc_fops->Read(lun, MSC_BOT_Data, SCSI_blk_addr / SCSI_blk_size, len / SCSI_blk_size) < 0) {
        scsi_sensecode(HARDWARE_ERROR, UNRECOVERED_READ_ERROR);
        i8Ret = (int8_t) -1;
    } else {
        usb_deveptx(cdev, MSC_IN_EP, MSC_BOT_Data, len);
        SCSI_blk_addr            += len;
        SCSI_blk_len             -= len;
        /* case 6 : Hi = Di */
        MSC_BOT_csw.dDataResidue -= len;
        if (SCSI_blk_len == 0U) {
            MSC_BOT_State = BOT_LAST_DATA_IN;
        }
    }
    return i8Ret;
}

/**
 * @brief  handles Write Process
 * @param  [in] lun         number of logical unit
 * @retval status
 */
int8_t scsi_processwrite(uint8_t lun)
{
    uint32_t len;
    int8_t i8Ret = (int8_t)0;

    len = LL_MIN(SCSI_blk_len, MSC_MEDIA_PACKET);

    if (SCSI_blk_size == 0U) {
        i8Ret = (int8_t) -1;
    } else if (msc_fops->Write(lun, MSC_BOT_Data, SCSI_blk_addr / SCSI_blk_size, len / SCSI_blk_size) < 0) {
        scsi_sensecode(HARDWARE_ERROR, WRITE_FAULT);
        i8Ret = (int8_t) -1;
    } else {
        SCSI_blk_addr            += len;
        SCSI_blk_len             -= len;
        /* case 12 : Ho = Do */
        MSC_BOT_csw.dDataResidue -= len;
        if (SCSI_blk_len == 0U) {
            msc_bot_txcsw(cdev, CSW_CMD_PASSED);
        } else {
            /* Prapare EP to Receive next packet */
            usb_readytorx(cdev, MSC_OUT_EP, MSC_BOT_Data, (uint16_t)LL_MIN(SCSI_blk_len, MSC_MEDIA_PACKET));
        }
    }
    return i8Ret;
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
