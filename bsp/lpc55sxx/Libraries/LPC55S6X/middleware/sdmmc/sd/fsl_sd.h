/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SD_H_
#define _FSL_SD_H_

#include "fsl_sdmmc_common.h"
/*!
 * @addtogroup sdcard SD Card Driver
 * @ingroup card
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Driver version. */
#define FSL_SD_DRIVER_VERSION (MAKE_VERSION(2U, 4U, 0U)) /*2.4.0*/

/*! @brief SD card flags
 * @anchor _sd_card_flag
 */
enum
{
    kSD_SupportHighCapacityFlag     = (1U << 1U), /*!< Support high capacity */
    kSD_Support4BitWidthFlag        = (1U << 2U), /*!< Support 4-bit data width */
    kSD_SupportSdhcFlag             = (1U << 3U), /*!< Card is SDHC */
    kSD_SupportSdxcFlag             = (1U << 4U), /*!< Card is SDXC */
    kSD_SupportVoltage180v          = (1U << 5U), /*!< card support 1.8v voltage*/
    kSD_SupportSetBlockCountCmd     = (1U << 6U), /*!< card support cmd23 flag*/
    kSD_SupportSpeedClassControlCmd = (1U << 7U), /*!< card support speed class control flag */
};

/*!
 * @brief SD card state
 *
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _sd_card
{
    sdmmchost_t *host; /*!< Host configuration */

    sd_usr_param_t usrParam; /*!< user parameter */
    bool isHostReady;        /*!< use this flag to indicate if need host re-init or not*/

    bool noInteralAlign;      /*!< used to enable/disable the functionality of the exchange buffer */
    uint32_t busClock_Hz;     /*!< SD bus clock frequency united in Hz */
    uint32_t relativeAddress; /*!< Relative address of the card */
    uint32_t version;         /*!< Card version */
    uint32_t flags;           /*!< Flags in _sd_card_flag */
    uint8_t internalBuffer[FSL_SDMMC_CARD_INTERNAL_BUFFER_SIZE]; /*!< internal buffer */
    uint32_t ocr;                                                /*!< Raw OCR content */
    sd_cid_t cid;                                                /*!< CID */
    sd_csd_t csd;                                                /*!< CSD */
    sd_scr_t scr;                                                /*!< SCR */
    sd_status_t stat;                                            /*!< sd 512 bit status */
    uint32_t blockCount;                                         /*!< Card total block number */
    uint32_t blockSize;                                          /*!< Card block size */
    sd_timing_mode_t currentTiming;                              /*!< current timing mode */
    sd_driver_strength_t driverStrength;                         /*!< driver strength */
    sd_max_current_t maxCurrent;                                 /*!< card current limit */
    sdmmc_operation_voltage_t operationVoltage;                  /*!< card operation voltage */
    sdmmc_osa_mutex_t lock;                                      /*!< card access lock */
} sd_card_t;

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SDCARD Function
 * @{
 */

/*!
 * @brief Initializes the card on a specific host controller.
 * This function initializes the card on a specific host controller, it is consist of
 * host init, card detect, card init function, however user can ignore this high level function,
 * instead of use the low level function, such as SD_CardInit, SD_HostInit, SD_CardDetect.
 *
 * Thread safe function, please note that the function will create the mutex lock dynamically by default,
 * so to avoid the mutex create redundantly, application must follow bellow sequence for card re-initialization
 * @code
 * SD_Deinit(card);
 * SD_Init(card);
 * @endcode
 *
 * @param card Card descriptor.
 * @retval #kStatus_SDMMC_HostNotReady host is not ready.
 * @retval #kStatus_SDMMC_GoIdleFailed Go idle failed.
 * @retval #kStatus_SDMMC_NotSupportYet Card not support.
 * @retval #kStatus_SDMMC_HandShakeOperationConditionFailed Send operation condition failed.
 * @retval #kStatus_SDMMC_AllSendCidFailed Send CID failed.
 * @retval #kStatus_SDMMC_SendRelativeAddressFailed Send relative address failed.
 * @retval #kStatus_SDMMC_SendCsdFailed Send CSD failed.
 * @retval #kStatus_SDMMC_SelectCardFailed Send SELECT_CARD command failed.
 * @retval #kStatus_SDMMC_SendScrFailed Send SCR failed.
 * @retval #kStatus_SDMMC_SetDataBusWidthFailed Set bus width failed.
 * @retval #kStatus_SDMMC_SwitchBusTimingFailed Switch high speed failed.
 * @retval #kStatus_SDMMC_SetCardBlockSizeFailed Set card block size failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_Init(sd_card_t *card);

/*!
 * @brief Deinitializes the card.
 * This function deinitializes the specific card and host.
 * Please note it is a thread safe function.
 *
 * @param card Card descriptor.
 */
void SD_Deinit(sd_card_t *card);

/*!
 * @brief Initializes the card.
 *
 * This function initializes the card only, make sure the host is ready when call this function,
 * otherwise it will return kStatus_SDMMC_HostNotReady.
 *
 * Thread safe function, please note that the function will create the mutex lock dynamically by default,
 * so to avoid the mutex create redundantly, application must follow bellow sequence for card re-initialization
 * @code
 * SD_CardDeinit(card);
 * SD_CardInit(card);
 * @endcode
 *
 * @param card Card descriptor.
 * @retval #kStatus_SDMMC_HostNotReady host is not ready.
 * @retval #kStatus_SDMMC_GoIdleFailed Go idle failed.
 * @retval #kStatus_SDMMC_NotSupportYet Card not support.
 * @retval #kStatus_SDMMC_HandShakeOperationConditionFailed Send operation condition failed.
 * @retval #kStatus_SDMMC_AllSendCidFailed Send CID failed.
 * @retval #kStatus_SDMMC_SendRelativeAddressFailed Send relative address failed.
 * @retval #kStatus_SDMMC_SendCsdFailed Send CSD failed.
 * @retval #kStatus_SDMMC_SelectCardFailed Send SELECT_CARD command failed.
 * @retval #kStatus_SDMMC_SendScrFailed Send SCR failed.
 * @retval #kStatus_SDMMC_SetDataBusWidthFailed Set bus width failed.
 * @retval #kStatus_SDMMC_SwitchBusTimingFailed Switch high speed failed.
 * @retval #kStatus_SDMMC_SetCardBlockSizeFailed Set card block size failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_CardInit(sd_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * This function deinitializes the specific card.
 * Please note it is a thread safe function.
 *
 *
 * @param card Card descriptor.
 */
void SD_CardDeinit(sd_card_t *card);

/*!
 * @brief initialize the host.
 *
 * This function deinitializes the specific host.
 *
 * @param card Card descriptor.
 */
status_t SD_HostInit(sd_card_t *card);

/*!
 * @brief Deinitializes the host.
 *
 * This function deinitializes the host.
 *
 * @param card Card descriptor.
 */
void SD_HostDeinit(sd_card_t *card);

/*!
 * @brief reset the host.
 *
 * This function reset the specific host.
 *
 * @param card Card descriptor.
 */
void SD_HostDoReset(sd_card_t *card);

/*!
 * @brief set card power.
 *
 * The power off operation depend on host or the user define power on function.
 * @param card card descriptor.
 * @param enable true is power on, false is power off.
 */
void SD_SetCardPower(sd_card_t *card, bool enable);

/*!
 * @brief sd wait card detect function.
 *
 * Detect card through GPIO, CD, DATA3.
 * @param card card descriptor.
 * @param status detect status, kSD_Inserted or kSD_Removed.
 */
status_t SD_PollingCardInsert(sd_card_t *card, uint32_t status);

/*!
 * @brief sd card present check function.
 *
 * @param card card descriptor.
 */
bool SD_IsCardPresent(sd_card_t *card);

/*!
 * @brief Checks whether the card is write-protected.
 *
 * This function checks if the card is write-protected via the CSD register.
 *
 * @param card The specific card.
 * @retval true Card is read only.
 * @retval false Card isn't read only.
 */
bool SD_CheckReadOnly(sd_card_t *card);

/*!
 * @brief Send SELECT_CARD command to set the card to be transfer state or not.
 *
 * @param card Card descriptor.
 * @param isSelected True to set the card into transfer state, false to disselect.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_SelectCard(sd_card_t *card, bool isSelected);

/*!
 * @brief Send ACMD13 to get the card current status.
 *
 * @param card Card descriptor.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_SendApplicationCommandFailed send application command failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_ReadStatus(sd_card_t *card);

/*!
 * @brief Reads blocks from the specific card.
 *
 * This function reads blocks from the specific card with default block size defined by the
 * SDHC_CARD_DEFAULT_BLOCK_SIZE.
 *
 * Please note it is a thread safe function.
 *
 * @param card Card descriptor.
 * @param buffer The buffer to save the data read from card.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to read.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDMMC_CardNotSupport Card not support.
 * @retval #kStatus_SDMMC_NotSupportYet Not support now.
 * @retval #kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_ReadBlocks(sd_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes blocks of data to the specific card.
 *
 * This function writes blocks to the specific card with default block size 512 bytes.
 *
 * Please note,
 * 1. It is a thread safe function.
 * 2. It is a async write function which means that the card status may still busy after the function return.
 * Application can call function SD_PollingCardStatusBusy to wait card status idle after the write operation.
 *
 * @param card Card descriptor.
 * @param buffer The buffer holding the data to be written to the card.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to write.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDMMC_NotSupportYet Not support now.
 * @retval #kStatus_SDMMC_CardNotSupport Card not support.
 * @retval #kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_WriteBlocks(sd_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Erases blocks of the specific card.
 *
 * This function erases blocks of the specific card with default block size 512 bytes.
 *
 * Please note,
 * 1. It is a thread safe function.
 * 2. It is a async erase function which means that the card status may still busy after the function return.
 * Application can call function SD_PollingCardStatusBusy to wait card status idle after the erase operation.
 *
 * @param card Card descriptor.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to erase.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval #kStatus_Success Operate successfully.
 */
status_t SD_EraseBlocks(sd_card_t *card, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief select card driver strength
 * select card driver strength
 * @param card Card descriptor.
 * @param driverStrength Driver strength
 */
status_t SD_SetDriverStrength(sd_card_t *card, sd_driver_strength_t driverStrength);

/*!
 * @brief select max current
 * select max operation current
 * @param card Card descriptor.
 * @param maxCurrent Max current
 */
status_t SD_SetMaxCurrent(sd_card_t *card, sd_max_current_t maxCurrent);

/*!
 * @brief Polling card idle status.
 *
 * This function can be used to polling the status from busy to Idle, the function will return if the card
 * status idle or timeout.
 *
 * @param card Card descriptor.
 * @param timeoutMs polling card status timeout value.
 * @retval kStatus_Success Operate successfully.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed CMD13 transfer failed.
 * @retval kStatus_SDMMC_PollingCardIdleFailed, polling card DAT0 idle failed.
 */
status_t SD_PollingCardStatusBusy(sd_card_t *card, uint32_t timeoutMs);

/* @} */

#if defined(__cplusplus)
}
#endif
/*! @} */
#endif /* _FSL_SD_H_*/
