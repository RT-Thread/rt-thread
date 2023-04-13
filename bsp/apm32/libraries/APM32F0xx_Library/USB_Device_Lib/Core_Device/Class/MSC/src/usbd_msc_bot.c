/*!
 * @file        usbd_msv_bot.c
 *
 * @brief       MSC BOT protocol core functions
 *
 * @version     V1.0.0
 *
 * @date        2021-12-25
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
#include "usbd_core.h"
#include "usbd_storage_disk.h"
#include "usbd_msc_scsi.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Class
  @{
*/

/** @addtogroup MSC_BOT
  @{
*/

/** @defgroup MSC_BOT_Macros Macros
  @{
*/

/**@} end of group MSC_BOT_Macros */

/** @defgroup MSC_BOT_Enumerations Enumerations
  @{
*/

/**@} end of group MSC_BOT_Enumerations */

/** @defgroup MSC_BOT_Structures Structures
  @{
*/

/**@} end of group MSC_BOT_Structures */

/** @defgroup MSC_BOT_Variables Variables
  @{
*/

BOT_Info_T g_BOTInfo;

/**@} end of group MSC_BOT_Variables */

/** @defgroup MSC_BOT_Functions Functions
  @{
*/

static void USBD_MSC_BOT_DecodeCBW(void);
static void USBD_MSC_BOT_TxData(uint8_t* txBuf, uint16_t len);
static void USBD_MSC_BOT_Stall(void);

/*!
 * @brief       BOT Process Reset.
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_MSC_BOT_Reset(void)
{
    g_BOTInfo.state = BOT_STATE_IDLE;
    g_BOTInfo.status = BOT_STATUS_RECOVERY;

    USBD_RxData(MSC_OUT_EP & 0x7f, (uint8_t*)&g_BOTInfo.CBW, MSC_BOT_CBW_LENGTH);
}

/*!
 * @brief       BOT Process initialization.
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_MSC_BOT_Init(void)
{
    g_BOTInfo.state = BOT_STATE_IDLE;
    g_BOTInfo.status = BOT_STATUS_NORMAL;

    g_storageCallBack.Init(0);

    USBD_RxData(MSC_OUT_EP & 0x7f, (uint8_t*)&g_BOTInfo.CBW, MSC_BOT_CBW_LENGTH);
}

/*!
 * @brief       Bulk OUT data handler.
 *
 * @param       ep : OUT endpoint
 *
 * @retval      None
 */
void USBD_MSC_BOT_OutData(uint8_t ep)
{
    if (g_BOTInfo.state == BOT_STATE_IDLE)
    {
        USBD_MSC_BOT_DecodeCBW();
    }
    else if (g_BOTInfo.state == BOT_STATE_DATA_OUT)
    {
        if (SCSI_CmdHandler(g_BOTInfo.CBW.bLUN, g_BOTInfo.CBW.CB) != SCSI_OK)
        {
            USBD_MSC_BOT_TxCSW(BOT_CSW_STATUS_CMD_FAIL);
        }
    }
}

/*!
 * @brief       Bulk IN data handler.
 *
 * @param       ep : IN endpoint
 *
 * @retval      None
 */
void USBD_MSC_BOT_InData(uint8_t ep)
{
    if (g_BOTInfo.state == BOT_STATE_DATA_IN)
    {
        if (SCSI_CmdHandler(g_BOTInfo.CBW.bLUN, g_BOTInfo.CBW.CB) != SCSI_OK)
        {
            USBD_MSC_BOT_TxCSW(BOT_CSW_STATUS_CMD_FAIL);
        }
    }
    else if ((g_BOTInfo.state == BOT_STATE_SEND_DATA) || \
             (g_BOTInfo.state == BOT_STATE_LAST_DATA_IN))
    {
        USBD_MSC_BOT_TxCSW(BOT_CSW_STATUS_CMD_OK);
    }
}

/*!
 * @brief       Decode CBW.
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_MSC_BOT_DecodeCBW(void)
{
    uint32_t xferCnt = g_usbDev.outBuf[MSC_OUT_EP & 0x7f].xferCnt;

    g_BOTInfo.CSW.dTag = g_BOTInfo.CBW.dTag;
    g_BOTInfo.CSW.dDataResidue = g_BOTInfo.CBW.dDataXferLen;

    if ((xferCnt != MSC_BOT_CBW_LENGTH) || \
            (g_BOTInfo.CBW.dSignature != MSC_BOT_CBW_SIGNATURE) || \
            (g_BOTInfo.CBW.bLUN > 1) || (g_BOTInfo.CBW.bCBLen < 1) || \
            (g_BOTInfo.CBW.bCBLen > 16))
    {
        SCSI_PutSenseCode(g_BOTInfo.CBW.bLUN, SCSI_SKEY_ILLEGAL_REQUEST,
                          SCSI_ASC_INVALID_CDB, 0);

        g_BOTInfo.status = BOT_STATUS_ERROR;
    }
    else
    {
        if (SCSI_CmdHandler(g_BOTInfo.CBW.bLUN, g_BOTInfo.CBW.CB) != SCSI_OK)
        {
            USBD_MSC_BOT_Stall();
        }
        else if ((g_BOTInfo.state == BOT_STATE_IDLE) || \
                 (g_BOTInfo.state == BOT_STATE_SEND_DATA))
        {
            if (g_BOTInfo.dataLen)
            {
                USBD_MSC_BOT_TxData(g_BOTInfo.data, g_BOTInfo.dataLen);
            }
            else
            {
                USBD_MSC_BOT_TxCSW(BOT_CSW_STATUS_CMD_OK);
            }
        }
    }
}

/*!
 * @brief       MSC send data.
 *
 * @param       txBuf : buffer to send
 *
 * @param       len : buffer length
 *
 * @retval      None
 */
static void USBD_MSC_BOT_TxData(uint8_t* txBuf, uint16_t len)
{
    len = USB_MIN(len, g_BOTInfo.CBW.dDataXferLen);

    g_BOTInfo.CSW.dDataResidue -= len;
    g_BOTInfo.CSW.bStatus = BOT_CSW_STATUS_CMD_OK;
    g_BOTInfo.state = BOT_STATE_SEND_DATA;

    USBD_TxData(MSC_IN_EP & 0x7f, txBuf, len);
}

/*!
 * @brief       Send CSW.
 *
 * @param       cswStatus : status of CSW
 *
 * @retval      None
 */
void USBD_MSC_BOT_TxCSW(uint8_t cswStatus)
{
    g_BOTInfo.CSW.dSignature = MSC_BOT_CSW_SIGNATURE;
    g_BOTInfo.CSW.bStatus = cswStatus;
    g_BOTInfo.state = BOT_STATE_IDLE;

    USBD_TxData(MSC_IN_EP & 0x7f, (uint8_t*)&g_BOTInfo.CSW,
                MSC_BOT_CSW_LENGTH);

    USBD_RxData(MSC_OUT_EP & 0x7f, (uint8_t*)&g_BOTInfo.CBW,
                MSC_BOT_CBW_LENGTH);
}

/*!
 * @brief       handler clearFeature in standard request.
 *
 * @param       None
 *
 * @retval      None
 */
void USBD_MSV_BOT_ClearFeatureHandler(void)
{
    if (g_BOTInfo.status == BOT_STATUS_ERROR)
    {
        USBD_SetEPTxStatus(MSC_IN_EP & 0x7f, USBD_EP_STATUS_NAK);
        g_BOTInfo.status = BOT_STATUS_NORMAL;
    }
    else if (((g_usbDev.reqData.byte.wIndex[0] & 0x80) == 0x80) && \
             g_BOTInfo.status != BOT_STATUS_RECOVERY)
    {
        USBD_MSC_BOT_TxCSW(BOT_CSW_STATUS_CMD_FAIL);
    }
}

/*!
 * @brief       Stall MSC.
 *
 * @param       None
 *
 * @retval      None
 */
static void USBD_MSC_BOT_Stall(void)
{
    if ((g_BOTInfo.CBW.bmFlags == 0) && (g_BOTInfo.CBW.dDataXferLen != 0) && \
            (g_BOTInfo.status == BOT_STATUS_NORMAL))
    {
        USBD_SetEPRxStatus(MSC_OUT_EP & 0x7f, USBD_EP_STATUS_STALL);
    }

    USBD_SetEPTxStatus(MSC_IN_EP & 0x7f, USBD_EP_STATUS_STALL);

    if (g_BOTInfo.status == BOT_STATUS_ERROR)
    {
        USBD_RxData(MSC_OUT_EP & 0x7f, (uint8_t*)&g_BOTInfo.CBW, MSC_BOT_CBW_LENGTH);
    }
}

/**@} end of group MSC_BOT_Functions */
/**@} end of group MSC_BOT_ */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
