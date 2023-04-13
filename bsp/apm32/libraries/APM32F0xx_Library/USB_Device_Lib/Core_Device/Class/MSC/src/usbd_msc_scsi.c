/*!
 * @file        usbd_msc_scsi.c
 *
 * @brief       MSC scsi
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "usbd_msc_bot.h"
#include "usbd_msc_scsi.h"
#include "usbd_storage_disk.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Class
  @{
*/

/** @addtogroup MSC_SCSI
  @{
*/

/** @defgroup MSC_SCSI_Macros Macros
  @{
*/

/**@} end of group MSC_SCSI_Macros */

/** @defgroup MSC_SCSI_Enumerations Enumerations
  @{
*/

/**@} end of group MSC_SCSI_Enumerations */

/** @defgroup MSC_SCSI_Structures Structures
  @{
*/

/**@} end of group MSC_SCSI_Structures */

/** @defgroup MSC_SCSI_Variables Variables
  @{
*/

SCSI_Sense_T g_scsiSenseCode[SCSI_SENSE_LIST_NUMBER];
uint8_t g_senseTxCnt;
uint8_t g_sensePutCnt;

static uint32_t  s_blkSize;
static uint32_t  s_blkNbr;

static uint32_t  s_blkAddr;
static uint32_t  s_blkLen;

/* USB Mass storage Page 0 Inquiry Data */
static const uint8_t  s_page00InquiryData[] =
{
    0x00,
    0x00,
    0x00,
    (7 - 4),
    0x00,
    0x80,
    0x83
};
/* USB Mass storage sense 6 Data */
static const uint8_t  s_modeSense6Data[] =
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};
/* USB Mass storage sense 10 Data */
static const uint8_t  s_modeSense10Data[] =
{
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
};

/**@} end of group MSC_SCSI_Variables */

/** @defgroup MSC_SCSI_Functions Functions
  @{
*/

static uint8_t SCSI_TestUnitReady(uint8_t lun);
static uint8_t SCSI_Inquiry(uint8_t lun, uint8_t* command);
static uint8_t SCSI_RequestSense(uint8_t lun, uint8_t* command);

static uint8_t SCSI_ReadFormatCapacity(uint8_t lun, uint8_t* command);
static uint8_t SCSI_ReadCapacity10(uint8_t lun, uint8_t* command);
static uint8_t SCSI_Read10(uint8_t lun, uint8_t* command);
static uint8_t SCSI_Write10(uint8_t lun, uint8_t* command);
static uint8_t SCSI_Verify10(uint8_t lun, uint8_t* command);

static uint8_t SCSI_StartStopUnit(void);
static uint8_t SCSI_ModeSense6(uint8_t lun, uint8_t* command);
static uint8_t SCSI_ModeSense10(uint8_t lun, uint8_t* command);

static uint8_t SCSI_Read(uint8_t lun);
static uint8_t SCSI_Write(uint8_t lun);
static uint8_t SCSI_CheckAddress(uint8_t lun, uint32_t blkOffset, uint16_t blkNbr);

/*!
 * @brief       SCSI command handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: Command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
uint8_t SCSI_CmdHandler(uint8_t lun, uint8_t* command)
{
    uint8_t ret = SCSI_OK;

    switch (command[0])
    {
        case SCSI_CMD_TEST_UNIT_READY:
            ret = SCSI_TestUnitReady(lun);
            break;

        case SCSI_CMD_INQUIRY:
            ret = SCSI_Inquiry(lun, command);
            break;

        case SCSI_CMD_REQUEST_SENSE:
            ret = SCSI_RequestSense(lun, command);
            break;

        case SCSI_CMD_READ_FORMAT_CAPACITIES:
            ret = SCSI_ReadFormatCapacity(lun, command);
            break;

        case SCSI_CMD_READ_CAPACITY_10:
            ret = SCSI_ReadCapacity10(lun, command);
            break;

        case SCSI_CMD_READ_10:
            ret = SCSI_Read10(lun, command);
            break;

        case SCSI_CMD_WRITE10:
            ret = SCSI_Write10(lun, command);
            break;

        case SCSI_CMD_VERIFY_10:
            ret = SCSI_Verify10(lun, command);
            break;
        case SCSI_CMD_ALLOW_MEDIUM_REMOVAL:
        case SCSI_CMD_START_STOP_UNIT:
            ret = SCSI_StartStopUnit();
            break;

        case SCSI_CMD_MODE_SENSE_6:
            ret = SCSI_ModeSense6(lun, command);
            break;

        case SCSI_CMD_MODE_SENSE_10:
            ret = SCSI_ModeSense10(lun, command);
            break;

        default:
            SCSI_PutSenseCode(lun, SCSI_SKEY_ILLEGAL_REQUEST,
                              SCSI_ASC_INVALID_CDB, 0);
            ret = SCSI_FAIL;
    }

    return ret;
}

/*!
 * @brief       Put the sense code to array.
 *
 * @param       sKey: sense Key
 *
 * @param       ASC: Additional Sense Code
 *
 * @param       ASCQ: Additional Sense Code Qualifier
 *
 * @retval      None
 */
void SCSI_PutSenseCode(uint8_t lun, uint8_t sKey, uint8_t ASC, uint8_t ASCQ)
{
    g_scsiSenseCode[g_sensePutCnt].sensekey = sKey;
    g_scsiSenseCode[g_sensePutCnt].ASC = ASC;
    g_scsiSenseCode[g_sensePutCnt].ASCQ = ASCQ;

    if ((++g_sensePutCnt) == SCSI_SENSE_LIST_NUMBER)
    {
        g_sensePutCnt = 0;
    }
}

/*!
 * @brief       SCSI Test Unit Ready handler.
 *
 * @param       lun: Logical unit number
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_TestUnitReady(uint8_t lun)
{
    if (g_BOTInfo.CBW.dDataXferLen)
    {
        SCSI_PutSenseCode(g_BOTInfo.CBW.bLUN, SCSI_SKEY_ILLEGAL_REQUEST,
                          SCSI_ASC_INVALID_CDB, 0);

        return SCSI_FAIL;
    }
    else if (g_storageCallBack.CheckReady(lun) != SCSI_OK)
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_NOT_READY,
                          SCSI_ASC_MEDIUM_NOT_PRESENT, 0);

        return SCSI_FAIL;
    }
    else
    {
        g_BOTInfo.dataLen = 0;
        return SCSI_OK;
    }
}

/*!
 * @brief       SCSI Inquiry handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_Inquiry(uint8_t lun, uint8_t* command)
{
    uint16_t i;
    uint8_t* pInquiryData;

    if (command[1] & 0x01)
    {
        pInquiryData = (uint8_t*)s_page00InquiryData;
        g_BOTInfo.dataLen = s_page00InquiryData[3] + 4;
    }
    else
    {
        pInquiryData = &g_storageCallBack.pInquiryData[lun * SCSI_INQUIRY_LENGTH];

        g_BOTInfo.dataLen = USB_MIN((pInquiryData[4] + 5), command[4]);
    }

    for (i = 0; i < g_BOTInfo.dataLen; i++)
    {
        g_BOTInfo.data[i] = pInquiryData[i];
    }

    return SCSI_OK;
}

/*!
 * @brief       SCSI Request Sense handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_RequestSense(uint8_t lun, uint8_t* command)
{
    uint8_t i = 0;

    while (i < SCSI_REQUEST_SENSE_DATA_LEN)
    {
        g_BOTInfo.data[i++] = 0;
    }

    g_BOTInfo.data[0] = 0x70;
    g_BOTInfo.data[7] = SCSI_REQUEST_SENSE_DATA_LEN - 6;

    if (g_senseTxCnt != g_sensePutCnt)
    {
        g_BOTInfo.data[2] = g_scsiSenseCode[g_senseTxCnt].sensekey;
        g_BOTInfo.data[12] = g_scsiSenseCode[g_senseTxCnt].ASC;
        g_BOTInfo.data[13] = g_scsiSenseCode[g_senseTxCnt].ASCQ;

        if ((++g_senseTxCnt) == SCSI_SENSE_LIST_NUMBER)
        {
            g_senseTxCnt = 0;
        }
    }

    g_BOTInfo.dataLen = (SCSI_REQUEST_SENSE_DATA_LEN < command[4]) ? \
                        SCSI_REQUEST_SENSE_DATA_LEN : command[4];

    return SCSI_OK;
}

/*!
 * @brief       SCSI Read Format Capacity handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_ReadFormatCapacity(uint8_t lun, uint8_t* command)
{
    uint16_t i = 0;
    uint32_t blkSize;
    uint32_t blkNbr;

    while (i < 12)
    {
        g_BOTInfo.data[i++] = 0;
    }

    if (g_storageCallBack.ReadCapacity(lun, &blkNbr, &blkSize) != SCSI_OK)
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_NOT_READY,
                          SCSI_ASC_MEDIUM_NOT_PRESENT, 0);

        return SCSI_FAIL;
    }
    else
    {
        blkNbr--;

        g_BOTInfo.data[3] = 0x08;
        g_BOTInfo.data[4] = (uint8_t)(blkNbr >> 24);
        g_BOTInfo.data[5] = (uint8_t)(blkNbr >> 16);
        g_BOTInfo.data[6] = (uint8_t)(blkNbr >> 8);
        g_BOTInfo.data[7] = (uint8_t)(blkNbr);
        g_BOTInfo.data[8] = 0x02;
        g_BOTInfo.data[9] = (uint8_t)(blkSize >> 16);
        g_BOTInfo.data[10] = (uint8_t)(blkSize >> 8);
        g_BOTInfo.data[11] = (uint8_t)blkSize;

        g_BOTInfo.dataLen = 12;

        return SCSI_OK;
    }
}

/*!
 * @brief       SCSI Read Capacity10 handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_ReadCapacity10(uint8_t lun, uint8_t* command)
{
    if (g_storageCallBack.ReadCapacity(lun, &s_blkNbr, &s_blkSize) != SCSI_OK)
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_NOT_READY,
                          SCSI_ASC_MEDIUM_NOT_PRESENT, 0);

        return SCSI_FAIL;
    }
    else
    {
        g_BOTInfo.data[0] = (uint8_t)((s_blkNbr - 1) >> 24);
        g_BOTInfo.data[1] = (uint8_t)((s_blkNbr - 1) >> 16);
        g_BOTInfo.data[2] = (uint8_t)((s_blkNbr - 1) >>  8);
        g_BOTInfo.data[3] = (uint8_t)(s_blkNbr - 1);
        g_BOTInfo.data[4] = (uint8_t)(s_blkSize >>  24);
        g_BOTInfo.data[5] = (uint8_t)(s_blkSize >>  16);
        g_BOTInfo.data[6] = (uint8_t)(s_blkSize >>  8);
        g_BOTInfo.data[7] = (uint8_t)(s_blkSize);

        g_BOTInfo.dataLen = 8;

        return SCSI_OK;
    }
}

/*!
 * @brief       SCSI Read10 handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_Read10(uint8_t lun, uint8_t* command)
{
    uint8_t ret = SCSI_OK;

    if (g_BOTInfo.state == BOT_STATE_IDLE)
    {
        if ((g_BOTInfo.CBW.bmFlags & 0x80) != 0x80)
        {
            SCSI_PutSenseCode(g_BOTInfo.CBW.bLUN, SCSI_SKEY_ILLEGAL_REQUEST,
                              SCSI_ASC_INVALID_CDB, 0);

            return SCSI_FAIL;
        }

        if (g_storageCallBack.CheckReady(lun) != SCSI_OK)
        {
            SCSI_PutSenseCode(lun, SCSI_SKEY_NOT_READY,
                              SCSI_ASC_MEDIUM_NOT_PRESENT, 0);

            return SCSI_FAIL;
        }

        s_blkAddr = ((uint32_t)command[2] << 24) | \
                    ((uint32_t)command[3] << 16) | \
                    ((uint32_t)command[4] << 8)  | \
                    (uint32_t)command[5];

        s_blkLen = ((uint16_t)command[7] << 8 | (uint8_t)command[8]);

        if (SCSI_CheckAddress(lun, s_blkAddr, s_blkLen) != SCSI_OK)
        {
            return SCSI_FAIL;
        }

        g_BOTInfo.state = BOT_STATE_DATA_IN;
        s_blkAddr *= s_blkSize;
        s_blkLen *= s_blkSize;

        if (g_BOTInfo.CBW.dDataXferLen != s_blkLen)
        {
            SCSI_PutSenseCode(g_BOTInfo.CBW.bLUN, SCSI_SKEY_ILLEGAL_REQUEST,
                              SCSI_ASC_INVALID_CDB, 0);

            return SCSI_FAIL;
        }

    }

    g_BOTInfo.dataLen = MSC_MEDIA_PACKET;

    ret = SCSI_Read(lun);

    return ret;
}

/*!
 * @brief       SCSI write10 handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_Write10(uint8_t lun, uint8_t* command)
{
    uint8_t ret = SCSI_OK;
    uint32_t len;

    if (g_BOTInfo.state == BOT_STATE_IDLE)
    {
        if (g_BOTInfo.CBW.bmFlags & 0x80)
        {
            SCSI_PutSenseCode(g_BOTInfo.CBW.bLUN, SCSI_SKEY_ILLEGAL_REQUEST,
                              SCSI_ASC_INVALID_CDB, 0);

            return SCSI_FAIL;
        }

        if (g_storageCallBack.CheckReady(lun) != SCSI_OK)
        {
            SCSI_PutSenseCode(lun, SCSI_SKEY_NOT_READY,
                              SCSI_ASC_MEDIUM_NOT_PRESENT, 0);

            return SCSI_FAIL;
        }

        if (g_storageCallBack.CheckWPR(lun) != SCSI_OK)
        {
            SCSI_PutSenseCode(lun, SCSI_SKEY_NOT_READY,
                              SCSI_ASC_WRITE_PROTECTED, 0);

            return SCSI_FAIL;
        }

        s_blkAddr = ((uint32_t)command[2] << 24) | \
                    ((uint32_t)command[3] << 16) | \
                    ((uint32_t)command[4] << 8)  | \
                    (uint32_t)command[5];

        s_blkLen = ((uint16_t)command[7] << 8 | (uint8_t)command[8]);

        if (SCSI_CheckAddress(lun, s_blkAddr, s_blkLen) != SCSI_OK)
        {
            return SCSI_FAIL;
        }

        s_blkAddr *= s_blkSize;
        s_blkLen  *= s_blkSize;

        if (g_BOTInfo.CBW.dDataXferLen != s_blkLen)
        {
            SCSI_PutSenseCode(g_BOTInfo.CBW.bLUN, SCSI_SKEY_ILLEGAL_REQUEST,
                              SCSI_ASC_INVALID_CDB, 0);

            return SCSI_FAIL;
        }

        g_BOTInfo.state = BOT_STATE_DATA_OUT;
        len = USB_MIN(s_blkLen, MSC_MEDIA_PACKET);

        USBD_RxData(MSC_OUT_EP & 0x7F, g_BOTInfo.data, len);

    }
    else
    {
        ret = SCSI_Write(lun);
    }

    return ret;
}

/*!
 * @brief       SCSI Verify10 Handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_Verify10(uint8_t lun, uint8_t* command)
{
    if (command[1] & 0x02)
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_ILLEGAL_REQUEST,
                          SCSI_ASC_INVALID_FIELED_IN_COMMAND, 0);

        return SCSI_FAIL;
    }

    s_blkAddr = ((uint32_t)command[2] << 24) | \
                ((uint32_t)command[3] << 16) | \
                ((uint32_t)command[4] << 8)  | \
                (uint32_t)command[5];

    s_blkLen = ((uint16_t)command[7] << 8 | (uint8_t)command[8]);

    if (SCSI_CheckAddress(lun, s_blkAddr, s_blkLen) != SCSI_OK)
    {
        return SCSI_FAIL;
    }

    g_BOTInfo.dataLen = 0;

    return SCSI_OK;
}

/*!
 * @brief       SCSI Start Stop Unit Handler.
 *
 * @param       None
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_StartStopUnit(void)
{
    g_BOTInfo.dataLen = 0;
    return SCSI_OK;
}

/*!
 * @brief       SCSI Mode Sense6 Handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_ModeSense6(uint8_t lun, uint8_t* command)
{
    for (uint16_t i = 0; i < 8; i++)
    {
        g_BOTInfo.data[i] = s_modeSense6Data[i];
    }

    g_BOTInfo.dataLen = 8;

    return SCSI_OK;
}

/*!
 * @brief       SCSI Mode Sense10 Handler.
 *
 * @param       lun: Logical unit number
 *
 * @param       command: command pointer
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_ModeSense10(uint8_t lun, uint8_t* command)
{
    for (uint16_t i = 0; i < 8; i++)
    {
        g_BOTInfo.data[i] = s_modeSense10Data[i];
    }

    g_BOTInfo.dataLen = 8;

    return SCSI_OK;
}

/*!
 * @brief       SCSI Read Process.
 *
 * @param       lun: Logical unit number
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_Read(uint8_t lun)
{
    uint32_t len = USB_MIN(MSC_MEDIA_PACKET, s_blkLen);

    if (g_storageCallBack.ReadData(len, g_BOTInfo.data, (s_blkAddr / s_blkSize),
                                   (len / s_blkSize)) != SCSI_OK)
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_HARDWARE_ERROR,
                          SCSI_ASC_UNRECOVERED_READ_ERROR, 0);

        return SCSI_FAIL;
    }

    USBD_TxData(MSC_IN_EP & 0x7F, g_BOTInfo.data, len);

    s_blkAddr += len;
    s_blkLen  -= len;

    g_BOTInfo.CSW.dDataResidue -= len;

    if (s_blkLen == 0)
    {
        g_BOTInfo.state = BOT_STATE_LAST_DATA_IN;
    }

    return SCSI_OK;
}

/*!
 * @brief       SCSI Write Process.
 *
 * @param       lun: Logical unit number
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_Write(uint8_t lun)
{
    uint32_t len = USB_MIN(MSC_MEDIA_PACKET, s_blkLen);

    if (s_blkLen - len)
    {
        __NOP();
    }
    if (g_storageCallBack.WriteData(lun, g_BOTInfo.data, s_blkAddr / s_blkSize,
                                    len / s_blkSize) != SCSI_OK)
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_HARDWARE_ERROR, SCSI_ASC_WRITE_FAULT, 0);

        return SCSI_FAIL;
    }

    s_blkAddr += len;
    s_blkLen  -= len;

    g_BOTInfo.CSW.dDataResidue -= len;

    if (s_blkLen)
    {
        len = USB_MIN(MSC_MEDIA_PACKET, s_blkLen);

        USBD_RxData(MSC_OUT_EP & 0x7f, g_BOTInfo.data, len);
    }
    else
    {
        USBD_MSC_BOT_TxCSW(BOT_CSW_STATUS_CMD_OK);
    }

    return SCSI_OK;
}

/*!
 * @brief       SCSI Check Address Range.
 *
 * @param       lun: Logical unit number
 *
 * @param       blkOffset: first block address
 *
 * @param       blkNbr: number of block to be processed
 *
 * @retval      SCSI_OK or SCSI_FAILL
 */
static uint8_t SCSI_CheckAddress(uint8_t lun, uint32_t blkOffset, uint16_t blkNbr)
{
    if (s_blkNbr < (blkNbr + blkOffset))
    {
        SCSI_PutSenseCode(lun, SCSI_SKEY_ILLEGAL_REQUEST,
                          SCSI_ASC_ADDRESS_OUT_OF_RANGE, 0);

        return SCSI_FAIL;
    }

    return SCSI_OK;
}

/**@} end of group MSC_SCSI_Functions */
/**@} end of group MSC_SCSI */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
