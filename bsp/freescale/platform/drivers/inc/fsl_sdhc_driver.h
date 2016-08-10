/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_SDHC_H__
#define __FSL_SDHC_H__

#include <stdio.h>
#include "fsl_os_abstraction.h"
#include "fsl_sdhc_hal.h"
#if FSL_FEATURE_SOC_SDHC_COUNT

/*! @addtogroup sdhc_pd_data_types */
/*! @{ */

/*
 * These macros enables features of SDHC driver:
 *
 * BSP_FSL_SDHC_USING_IRQ
 *  - Enables IRQ on Initialization 
 *
 * BSP_FSL_SDHC_ENABLE_ADMA1
 *  - Enables the ADMA1 feature. As a result of the alignment limitation of the ADMA1,
 *  it falls back to PIO if the data size/address does not align.
 *
 * BSP_FSL_SDHC_ENABLE_AUTOCMD12
 *  - Enables sending cmd12 automatically for multiple block R/W access.
 *
 * BSP_FSL_SDHC_USING_DYNALLOC
 *  - Enables dynamic allocate memory in SDHC/SDCARD driver
 *
 */
#define BSP_FSL_SDHC_USING_IRQ
#define BSP_FSL_SDHC_ENABLE_AUTOCMD12
#define BSP_FSL_SDHC_ENABLE_ADMA1

extern SDHC_Type * const g_sdhcBase[];
extern const IRQn_Type g_sdhcIrqId[SDHC_INSTANCE_COUNT];

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum _sdhc_status {
    kStatus_SDHC_NoError = 0,               /*!< No error */
    kStatus_SDHC_InitFailed,                /*!< Driver initialization failed */
    kStatus_SDHC_SetClockFailed,            /*!< Failed to set clock of host controller */
    kStatus_SDHC_SetCardToIdle,             /*!< Failed to set card to idle */
    kStatus_SDHC_SetCardBlockSizeFailed,    /*!< Failed to set card block size */
    kStatus_SDHC_SendAppOpCondFailed,       /*!< Failed to send app_op_cond command */
    kStatus_SDHC_AllSendCidFailed,          /*!< Failed to send all_send_cid command */
    kStatus_SDHC_SendRcaFailed,             /*!< Failed to send send_rca command */
    kStatus_SDHC_SendCsdFailed,             /*!< Failed to send send_csd command */
    kStatus_SDHC_SendScrFailed,             /*!< Failed to send send_scr command */
    kStatus_SDHC_SelectCardFailed,          /*!< Failed to send select_card command */
    kStatus_SDHC_SwitchHighSpeedFailed,     /*!< Failed to switch to high speed mode */
    kStatus_SDHC_SetCardWideBusFailed,      /*!< Failed to set card's bus mode */
    kStatus_SDHC_SetBusWidthFailed,         /*!< Failed to set host's bus mode */
    kStatus_SDHC_SendCardStatusFailed,      /*!< Failed to send card status */
    kStatus_SDHC_StopTransmissionFailed,    /*!< Failed to stop transmission */
    kStatus_SDHC_CardEraseBlocksFailed,     /*!< Failed to erase blocks */
    kStatus_SDHC_InvalidIORange,            /*!< Invalid read/write/erase address range */
    kStatus_SDHC_BlockSizeNotSupportError,  /*!< Unsupported block size */
    kStatus_SDHC_HostIsAlreadyInited,       /*!< Host controller is already initialized */
    kStatus_SDHC_HostNotSupport,            /*!< Host not error */
    kStatus_SDHC_HostIsBusyError,           /*!< Bus busy error */
    kStatus_SDHC_DataPrepareError,          /*!< Data preparation error */
    kStatus_SDHC_WaitTimeoutError,          /*!< Wait timeout error */
    kStatus_SDHC_OutOfMemory,               /*!< Out of memory error */
    kStatus_SDHC_IoError,                   /*!< General IO error */
    kStatus_SDHC_CmdIoError,                /*!< CMD I/O error */
    kStatus_SDHC_DataIoError,               /*!< Data I/O error */
    kStatus_SDHC_InvalidParameter,          /*!< Invalid parameter error */
    kStatus_SDHC_RequestFailed,             /*!< Request failed */
    kStatus_SDHC_RequestCardStatusError,    /*!< Status error */
    kStatus_SDHC_SwitchFailed,              /*!< Switch failed */
    kStatus_SDHC_NotSupportYet,             /*!< Not support */
    kStatus_SDHC_TimeoutError,              /*!< Timeout error*/
    kStatus_SDHC_CardNotSupport,            /*!< Card does not support */
    kStatus_SDHC_CmdError,                  /*!< CMD error */
    kStatus_SDHC_DataError,                 /*!< Data error */
    kStatus_SDHC_DmaAddressError,           /*!< DMA address error */
    kStatus_SDHC_Failed,                    /*!< General failed */
    kStatus_SDHC_NoMedium,                  /*!< No medium error */
    kStatus_SDHC_UnknownStatus              /*!< Unknown if card is present */
} sdhc_status_t;

typedef enum _sdhc_card_detect_type {
    kSdhcCardDetectGpio = 1,        /*!< Use GPIO for card detection. @internal gui name="GPIO" */
    kSdhcCardDetectDat3,            /*!< Use DAT3 for card detection. @internal gui name="DAT3" */
    kSdhcCardDetectCdPin,           /*!< Use host controller dedicate CD pin for card detection. @internal gui name="HOST" */
    kSdhcCardDetectPollDat3,        /*!< Poll DAT3 for card detection. @internal gui name="Poll-DAT3" */
    kSdhcCardDetectPollCd,          /*!< Poll host controller dedicate CD pin for card detection. @internal gui name="Poll-HOST" */
} sdhc_cd_type_t;

typedef enum _sdhc_power_mode {
    kSdhcPowerModeRunning = 0,      /*!< SDHC is running */
    kSdhcPowerModeSuspended,        /*!< SDHC is suspended */
    kSdhcPowerModeStopped,          /*!< SDHC is stopped */
} sdhc_power_mode_t;

typedef enum _sdhc_buswidth {
    kSdhcBusWidth1Bit = 1,          /*!< 1-bit bus width. @internal gui name="1-bit bus width" */
    kSdhcBusWidth4Bit,              /*!< 4-bit bus width. @internal gui name="4-bit bus width" */
    kSdhcBusWidth8Bit,              /*!< 8-bit bus width. @internal gui name="8-bit bus width" */
} sdhc_buswidth_t;

typedef enum _sdhc_transfer_mode {
    kSdhcTransModePio = 1,          /*!< Transfer mode: PIO. @internal gui name="PIO" */
    kSdhcTransModeSdma,             /*!< Transfer mode: SDMA. @internal gui name="SDMA" */
    kSdhcTransModeAdma1,            /*!< Transfer mode: ADMA1. @internal gui name="ADMA1" */
    kSdhcTransModeAdma2,            /*!< Transfer mode: ADMA2. @internal gui name="ADMA2" */
} sdhc_transfer_mode_t;

#define FSL_SDHC_REQ_RSPTYPE_PRESENT       (1 << 1)                         /* response presented */
#define FSL_SDHC_REQ_RSPTYPE_136BITS       (1 << 2)                         /* response with 136 bits length */
#define FSL_SDHC_REQ_RSPTYPE_CRC           (1 << 3)                         /* response checking CRC */
#define FSL_SDHC_REQ_RSPTYPE_BUSY          (1 << 4)                         /* response with busy */
#define FSL_SDHC_REQ_RSPTYPE_CHK_IDX       (1 << 5)                         /* response with checking command index*/

#define FSL_SDHC_REQ_RSPTYPE_NONE    (0U)
#define FSL_SDHC_REQ_RSPTYPE_R1      (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC | \
                                      FSL_SDHC_REQ_RSPTYPE_CHK_IDX)         /* Response 1 */
#define FSL_SDHC_REQ_RSPTYPE_R1B     (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC | \
                                      FSL_SDHC_REQ_RSPTYPE_CHK_IDX | \
                                      FSL_SDHC_REQ_RSPTYPE_BUSY)            /* Response 1 with busy */
#define FSL_SDHC_REQ_RSPTYPE_R2      (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_136BITS | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC)             /* Response 2 */
#define FSL_SDHC_REQ_RSPTYPE_R3      (FSL_SDHC_REQ_RSPTYPE_PRESENT)         /* Response 3 */
#define FSL_SDHC_REQ_RSPTYPE_R4      (FSL_SDHC_REQ_RSPTYPE_PRESENT)         /* Response 4 */
#define FSL_SDHC_REQ_RSPTYPE_R5      (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC | \
                                      FSL_SDHC_REQ_RSPTYPE_CHK_IDX)         /* Response 5 */
#define FSL_SDHC_REQ_RSPTYPE_R5B     (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC | \
                                      FSL_SDHC_REQ_RSPTYPE_CHK_IDX | \
                                      FSL_SDHC_REQ_RSPTYPE_BUSY)            /* Response 5 with busy */
#define FSL_SDHC_REQ_RSPTYPE_R6      (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC | \
                                      FSL_SDHC_REQ_RSPTYPE_CHK_IDX)         /* Response 6 */
#define FSL_SDHC_REQ_RSPTYPE_R7      (FSL_SDHC_REQ_RSPTYPE_PRESENT | \
                                      FSL_SDHC_REQ_RSPTYPE_CRC | \
                                      FSL_SDHC_REQ_RSPTYPE_CHK_IDX)         /* Response 7 */

static const uint32_t g_req_resp_flags[] = {
        FSL_SDHC_REQ_RSPTYPE_NONE,              /*!< R0 flags */
        FSL_SDHC_REQ_RSPTYPE_R1,                /*!< R1 flags */
        FSL_SDHC_REQ_RSPTYPE_R1B,               /*!< R1b flags */
        FSL_SDHC_REQ_RSPTYPE_R2,                /*!< R2 flags */
        FSL_SDHC_REQ_RSPTYPE_R3,                /*!< R3 flags */
        FSL_SDHC_REQ_RSPTYPE_R4,                /*!< R4 flags */
        FSL_SDHC_REQ_RSPTYPE_R5,                /*!< R5 flags */
        FSL_SDHC_REQ_RSPTYPE_R5B,               /*!< R5b flags */
        FSL_SDHC_REQ_RSPTYPE_R6,                /*!< R6 flags */
        FSL_SDHC_REQ_RSPTYPE_R7,                /*!< R7 flags */
};

typedef enum _sdhc_resp_type {
    kSdhcRespTypeNone = 0,          /*!< Response type: none */
    kSdhcRespTypeR1,                /*!< Response type: R1 */
    kSdhcRespTypeR1b,               /*!< Response type: R1b */
    kSdhcRespTypeR2,                /*!< Response type: R2 */
    kSdhcRespTypeR3,                /*!< Response type: R3 */
    kSdhcRespTypeR4,                /*!< Response type: R4 */
    kSdhcRespTypeR5,                /*!< Response type: R5 */
    kSdhcRespTypeR5b,               /*!< Response type: R5b */
    kSdhcRespTypeR6,                /*!< Response type: R6 */
    kSdhcRespTypeR7,                /*!< Response type: R7 */
} sdhc_resp_type_t;


/*!
 * @brief SDHC Initialization Configuration Structure
 *
 * Defines the configuration data structure to initialize the SDHC.
 * @internal gui name="Basic Configuration" id="sdhcCfg"
 */
typedef struct SdhcUserConfig
{
    uint32_t clock;                                 /*!< Clock rate @internal gui name="Bus clock" id="BusClock" */
    sdhc_transfer_mode_t transMode;                 /*!< SDHC transfer mode @internal gui name="Transfer mode" id="transferMode" */
    sdhc_cd_type_t cdType;                          /*!< Card detection type @internal gui name="Card detection type" id="cardDetection" */
    void (*cardDetectCallback)(bool inserted);      /*!< Callback function for card detect occurs @internal gui name="Card detect callback function" id="CardDetectCallback" type="callback" */
    void (*cardIntCallback)(void);                  /*!< Callback function for card interrupt occurs @internal gui name="Card interrupt callback function" id="CardInterruptCallback" type="callback" */
    void (*blockGapCallback)(void);                 /*!< Callback function for block gap occurs @internal gui name="Card block gap callback function" id="CardBlockGapCallback" type="callback" */
} sdhc_user_config_t;

/*!
 * @brief SDHC Host Device Structure
 *
 * Defines the Host device structure which includes both the static and the runtime SDHC information.
 */
typedef struct SdhcHostDevice
{
    uint32_t instance;                              /*!< Host instance index */
    sdhc_cd_type_t cdType;                          /*!< Host controller card detection type */
    sdhc_hal_endian_t endian;                       /*!< Endian mode the host's working at */
    uint32_t swFeature;                             /*!< Host controller driver features */
#define FSL_SDHC_HOST_SW_FEATURE_NODMA        (1 << 0)      /*!< No DMA supported in driver */
    uint32_t flags;                                 /*!< Host flags */
#define FSL_SDHC_HOST_FLAGS_CARD_PRESENTED    (1 << 0)      /*!< Card presented */
    sdhc_transfer_mode_t mode;
    uint32_t busWidth;                              /*!< Current busWidth */
    uint32_t caps;                                  /*!< Host capability */
#define FSL_SDHC_HOST_CAPS_SUPPORT_V180      (1 << 0)    /*!< Host support 1.8v */
#define FSL_SDHC_HOST_CAPS_SUPPORT_HIGHSPEED (1 << 1)    /*!< Host support highspeed mode */
#define FSL_SDHC_HOST_CAPS_SUPPORT_4BITS     (1 << 2)    /*!< Host support 4-bit bus width */
#define FSL_SDHC_HOST_CAPS_SUPPORT_DMA       (1 << 3)    /*!< Host support DMA mode */
#define FSL_SDHC_HOST_CAPS_SUPPORT_ADMA      (1 << 4)    /*!< Host support ADMA mode */
#define FSL_SDHC_HOST_CAPS_SUPPORT_EXDMA     (1 << 5)    /*!< Host support ExDMA mode */
#define FSL_SDHC_HOST_CAPS_SUPPORT_SRS       (1 << 6)    /*!< Host support suspend resume mode*/
    uint32_t ocrSupported;                          /*!< Supported OCR */
    uint32_t clock;                                 /*!< Current clock frequency */
    sdhc_power_mode_t powerMode;                    /*!< Current power mode */
    uint32_t maxClock;                              /*!< Maximum clock supported */
    uint32_t maxBlockSize;                          /*!< Maximum block size supported */
    uint32_t maxBlockCount;                         /*!< Maximum block count supported */
    uint32_t *admaTableAddress;                     /*!< ADMA table address */
#if defined BSP_FSL_SDHC_USING_DYNALLOC
    uint32_t admaTableMaxEntries;                   /*!< Maximum entries can be held in table */
#endif
    struct SdhcRequest * currentReq;                /*!< Associated request */
    void (*cardIntCallback)(void);                  /*!< Callback function for card interrupt occurs */
    void (*cardDetectCallback)(bool inserted);      /*!< Callback function for card detect occurs */
    void (*blockGapCallback)(void);                 /*!< Callback function for block gap occurs */
} sdhc_host_t;

#define DOES_HOST_SUPPORT_HIGHSPEED(x)       (x->caps & FSL_SDHC_HOST_CAPS_SUPPORT_HIGHSPEED)
#define DOES_HOST_SUPPORT_4BITS(x)           (x->caps & FSL_SDHC_HOST_CAPS_SUPPORT_4BITS)

/*!
 * @brief SDHC Data Structure
 *
 * Defines the SDHC data structure including the block size/count and flags.
 */
typedef struct SdhcData
{
    struct SdhcRequest *req;                        /*!< Associated request */
    uint32_t blockSize;                             /*!< Block size */
    uint32_t blockCount;                            /*!< Block count */
    uint32_t bytesTransferred;                      /*!< Transferred buffer */
    uint32_t *buffer;                               /*!< Data buffer */
} sdhc_data_t;

/*!
 * @brief SDHC Request Structure
 *
 * Defines the SDHC request structure including the command index, argument, flags, response, and data.
 */
typedef struct SdhcRequest
{
    uint32_t cmdIndex;                              /*!< Command index */
    uint32_t argument;                              /*!< Command argument */
    uint32_t flags;                                 /*!< Flags */
#define FSL_SDHC_REQ_FLAGS_DATA_READ      (1 << 0)  /*!< Request will read data */
#define FSL_SDHC_REQ_FLAGS_USE_DMA        (1 << 1)  /*!< Request will use DMA for data transferring */
#define FSL_SDHC_REQ_FLAGS_STOP_TRANS     (1 << 2)  /*!< Request to stop transmition */ 
    sdhc_resp_type_t respType;                      /*!< Response type */
    volatile uint32_t error;                                 /*!< Command error code */
#define FSL_SDHC_REQ_ERR_HOST_BUSY        (1 << 0)  /*!< Host is busy */
#define FSL_SDHC_REQ_ERR_SEND_CMD         (1 << 1)  /*!< Send command error */
#define FSL_SDHC_REQ_ERR_CMD_CRC          (1 << 2)  /*!< Command CRC error */
#define FSL_SDHC_REQ_ERR_CMD_INDEX        (1 << 3)  /*!< Command index error */
#define FSL_SDHC_REQ_ERR_CMD_END_BIT      (1 << 4)  /*!< Command end bit error */
#define FSL_SDHC_REQ_ERR_CMD_TIMEOUT      (1 << 5)  /*!< Command timeout error */
#define FSL_SDHC_REQ_ERR_CARD_REMOVED     (1 << 6)  /*!< Card removed */
#define FSL_SDHC_REQ_ERR_RSPBUSY_TIMEOUT  (1 << 7)  /*!< Response busy timeout error */
#define FSL_SDHC_REQ_ERR_DAT_TIMEOUT      (1 << 8)  /*!< Data timeout error */
#define FSL_SDHC_REQ_ERR_DATA_CRC         (1 << 9)  /*!< Data CRC error */
#define FSL_SDHC_REQ_ERR_DATA_END_BIT     (1 << 10) /*!< Data end bit error */
#define FSL_SDHC_REQ_ERR_AUTO_CMD12       (1 << 11) /*!< Auto cmd12 error */
#define FSL_SDHC_REQ_ERR_DMA              (1 << 12) /*!< DMA error */
#define FSL_SDHC_REQ_ERR_TIMEOUT          (1 << 13) /*!< Request timeout error */
#define FSL_SDHC_REQ_ERR_DATA_PREPARE     (1 << 14) /*!< Data preparation error */
    uint32_t cardErrStatus;                         /*!< Card error status from response 1 */
    uint32_t response[4];                           /*!< Response for this command */
    semaphore_t *complete;                        /*!< Request completion sync object */
    struct SdhcData *data;                          /*!< Data associated with request */
} sdhc_request_t;

/*! @} */

/*! @addtogroup sdhc_pd */
/*! @{ */

/*************************************************************************************************
 * API
 ************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif
/*! @name SDHC PD FUNCTION */
/*@{ */

/*!
 * @brief Initializes the Host controller with a specific instance index.
 *
 * This function initializes the SDHC module according to the given
 * initialization configuration structure including the clock frequency,
 * bus width, and card detect callback.
 *
 * @param instance the specific instance index
 * @param host pointer to a place storing the sdhc_host_t structure
 * @param config initialization configuration data
 * @return kStatus_SDHC_NoError if success
 */
sdhc_status_t SDHC_DRV_Init(uint32_t instance, sdhc_host_t *host, const sdhc_user_config_t *config);

/*!
 * @brief Destroys the host controller.
 *
 * @param instance the instance index of host controller
 * @return kStatus_SDHC_NoError if success
 */
sdhc_status_t SDHC_DRV_Shutdown(uint32_t instance);

/*!
 * @brief Checks whether the card is present on a specified host controller.
 *
 * This function checks if there's a card inserted in the SDHC.
 *
 * @param instance the instance index of host controller
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDHC_DRV_DetectCard(uint32_t instance);

/*!
 * @brief Sets the clock frequency of the host controller.
 *
 * @param instance the instance index of host controller
 * @param clock the desired frequency to be set to controller
 *
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDHC_DRV_ConfigClock(uint32_t instance, uint32_t clock);

/*!
 * @brief Sets the bus width of the host controller.
 *
 * @param instance the instance index of host controller
 * @param busWidth the desired bus width to be set to controller
 *
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDHC_DRV_SetBusWidth(uint32_t instance, sdhc_buswidth_t busWidth);

/*!
 * @brief Issues the request on a specific host controller and returns on completion.
 *
 * This function  issues the request to the card on a specific SDHC.
 * The command  is sent and is blocked as long as
 * the response/data is sending back from the card.
 *
 * @param instance the instance index of host controller
 * @param req the pointer to the request
 * @param timeoutInMs timeout value in microseconds
 * @return kStatus_SDHC_NoError on success
 */
sdhc_status_t SDHC_DRV_IssueRequestBlocking(uint32_t instance, sdhc_request_t *req, uint32_t timeoutInMs);

#if defined BSP_FSL_SDHC_USING_IRQ
/*!
 * @brief IRQ handler for SDHC
 *
 * This function deals with IRQs on the given host controller.
 *
 * @param instance the instance index of host controller
 */
void SDHC_DRV_DoIrq(uint32_t instance);
#endif

/*@} */
#if defined(__cplusplus)
}
#endif
/*! @} */
#endif
#endif /* __FSL_SDHC_H__ */

/*************************************************************************************************
 * EOF
 ************************************************************************************************/

