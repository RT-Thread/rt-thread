/*!
 * @file        usbd_msc_bot.h
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
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "usbd_core.h"

#ifndef __USBD_MSC_BOT_H
#define __USBD_MSC_BOT_H

#define MSC_BOT_CBW_SIGNATURE             (uint32_t)(0x43425355)
#define MSC_BOT_CBW_LENGTH                31

#define MSC_BOT_CSW_SIGNATURE             (uint32_t)(0x53425355)
#define MSC_BOT_CSW_LENGTH                13

typedef enum
{
    BOT_STATE_IDLE,          //!< Idle state
    BOT_STATE_DATA_OUT,      //!< Data Out state
    BOT_STATE_DATA_IN,       //!< Data In state
    BOT_STATE_LAST_DATA_IN,  //!< Last Data In Last
    BOT_STATE_SEND_DATA      //!< Send Immediate data
} BOT_STATE_T;

typedef enum
{
    BOT_STATUS_NORMAL,
    BOT_STATUS_RECOVERY,
    BOT_STATUS_ERROR
} BOT_STATUS_T;

typedef enum
{
    BOT_CSW_STATUS_CMD_OK,
    BOT_CSW_STATUS_CMD_FAIL,
    BOT_CSW_STATUS_PHASE_ERROR
} BOT_CSW_STATUS_T;


/**
 * @brief   Command Block Wrapper
 */
typedef struct
{
    uint32_t dSignature;
    uint32_t dTag;
    uint32_t dDataXferLen;
    uint8_t  bmFlags;
    uint8_t  bLUN;
    uint8_t  bCBLen;
    uint8_t  CB[16];
} BOT_CBW_T;

/**
 * @brief   Command Status Wrapper
 */
typedef struct
{
    uint32_t dSignature;
    uint32_t dTag;
    uint32_t dDataResidue;
    uint8_t  bStatus;
} BOT_CSW_T;

typedef struct
{
    uint8_t   state;
    uint8_t   status;
    uint16_t  dataLen;
    BOT_CBW_T CBW;
    BOT_CSW_T CSW;
    uint8_t   data[MSC_MEDIA_PACKET];
} BOT_Info_T;

extern BOT_Info_T g_BOTInfo;

void USBD_MSC_BOT_Reset(void);
void USBD_MSC_BOT_Init(void);
void USBD_MSC_BOT_OutData(uint8_t ep);
void USBD_MSC_BOT_InData(uint8_t ep);
void USBD_MSC_BOT_TxCSW(uint8_t cswStatus);
void USBD_MSC_BOT_Stall(void);
void USBD_MSV_BOT_ClearFeatureHandler(void);

#endif
