/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _FSL_CARD_H_
#define _FSL_CARD_H_

#include "fsl_common.h"
#include "fsl_specification.h"
#include "fsl_host.h"
#include "stdlib.h"
/*!
 * @addtogroup CARD
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Driver version. */
#define FSL_SDMMC_DRIVER_VERSION (MAKE_VERSION(2U, 1U, 4U)) /*2.1.4*/

/*! @brief Default block size */
#define FSL_SDMMC_DEFAULT_BLOCK_SIZE (512U)
/*! @brief SDMMC global data buffer size, word unit*/
#define SDMMC_GLOBAL_BUFFER_SIZE (64U)

/*! @brief SD/MMC card API's running status. */
enum _sdmmc_status
{
    kStatus_SDMMC_NotSupportYet = MAKE_STATUS(kStatusGroup_SDMMC, 0U),             /*!< Haven't supported */
    kStatus_SDMMC_TransferFailed = MAKE_STATUS(kStatusGroup_SDMMC, 1U),            /*!< Send command failed */
    kStatus_SDMMC_SetCardBlockSizeFailed = MAKE_STATUS(kStatusGroup_SDMMC, 2U),    /*!< Set block size failed */
    kStatus_SDMMC_HostNotSupport = MAKE_STATUS(kStatusGroup_SDMMC, 3U),            /*!< Host doesn't support */
    kStatus_SDMMC_CardNotSupport = MAKE_STATUS(kStatusGroup_SDMMC, 4U),            /*!< Card doesn't support */
    kStatus_SDMMC_AllSendCidFailed = MAKE_STATUS(kStatusGroup_SDMMC, 5U),          /*!< Send CID failed */
    kStatus_SDMMC_SendRelativeAddressFailed = MAKE_STATUS(kStatusGroup_SDMMC, 6U), /*!< Send relative address failed */
    kStatus_SDMMC_SendCsdFailed = MAKE_STATUS(kStatusGroup_SDMMC, 7U),             /*!< Send CSD failed */
    kStatus_SDMMC_SelectCardFailed = MAKE_STATUS(kStatusGroup_SDMMC, 8U),          /*!< Select card failed */
    kStatus_SDMMC_SendScrFailed = MAKE_STATUS(kStatusGroup_SDMMC, 9U),             /*!< Send SCR failed */
    kStatus_SDMMC_SetDataBusWidthFailed = MAKE_STATUS(kStatusGroup_SDMMC, 10U),    /*!< Set bus width failed */
    kStatus_SDMMC_GoIdleFailed = MAKE_STATUS(kStatusGroup_SDMMC, 11U),             /*!< Go idle failed */
    kStatus_SDMMC_HandShakeOperationConditionFailed =
        MAKE_STATUS(kStatusGroup_SDMMC, 12U), /*!< Send Operation Condition failed */
    kStatus_SDMMC_SendApplicationCommandFailed =
        MAKE_STATUS(kStatusGroup_SDMMC, 13U),                                    /*!< Send application command failed */
    kStatus_SDMMC_SwitchFailed = MAKE_STATUS(kStatusGroup_SDMMC, 14U),           /*!< Switch command failed */
    kStatus_SDMMC_StopTransmissionFailed = MAKE_STATUS(kStatusGroup_SDMMC, 15U), /*!< Stop transmission failed */
    kStatus_SDMMC_WaitWriteCompleteFailed = MAKE_STATUS(kStatusGroup_SDMMC, 16U),    /*!< Wait write complete failed */
    kStatus_SDMMC_SetBlockCountFailed = MAKE_STATUS(kStatusGroup_SDMMC, 17U),        /*!< Set block count failed */
    kStatus_SDMMC_SetRelativeAddressFailed = MAKE_STATUS(kStatusGroup_SDMMC, 18U),   /*!< Set relative address failed */
    kStatus_SDMMC_SwitchBusTimingFailed = MAKE_STATUS(kStatusGroup_SDMMC, 19U),      /*!< Switch high speed failed */
    kStatus_SDMMC_SendExtendedCsdFailed = MAKE_STATUS(kStatusGroup_SDMMC, 20U),      /*!< Send EXT_CSD failed */
    kStatus_SDMMC_ConfigureBootFailed = MAKE_STATUS(kStatusGroup_SDMMC, 21U),        /*!< Configure boot failed */
    kStatus_SDMMC_ConfigureExtendedCsdFailed = MAKE_STATUS(kStatusGroup_SDMMC, 22U), /*!< Configure EXT_CSD failed */
    kStatus_SDMMC_EnableHighCapacityEraseFailed =
        MAKE_STATUS(kStatusGroup_SDMMC, 23U), /*!< Enable high capacity erase failed */
    kStatus_SDMMC_SendTestPatternFailed = MAKE_STATUS(kStatusGroup_SDMMC, 24U),    /*!< Send test pattern failed */
    kStatus_SDMMC_ReceiveTestPatternFailed = MAKE_STATUS(kStatusGroup_SDMMC, 25U), /*!< Receive test pattern failed */
    kStatus_SDMMC_SDIO_ResponseError = MAKE_STATUS(kStatusGroup_SDMMC, 26U),       /*!< sdio response error */
    kStatus_SDMMC_SDIO_InvalidArgument =
        MAKE_STATUS(kStatusGroup_SDMMC, 27U), /*!< sdio invalid argument response error */
    kStatus_SDMMC_SDIO_SendOperationConditionFail =
        MAKE_STATUS(kStatusGroup_SDMMC, 28U),                            /*!< sdio send operation condition fail */
    kStatus_SDMMC_InvalidVoltage = MAKE_STATUS(kStatusGroup_SDMMC, 29U), /*!<  invaild voltage */
    kStatus_SDMMC_SDIO_SwitchHighSpeedFail = MAKE_STATUS(kStatusGroup_SDMMC, 30U), /*!<  switch to high speed fail */
    kStatus_SDMMC_SDIO_ReadCISFail = MAKE_STATUS(kStatusGroup_SDMMC, 31U),         /*!<  read CIS fail */
    kStatus_SDMMC_SDIO_InvalidCard = MAKE_STATUS(kStatusGroup_SDMMC, 32U),         /*!<  invaild SDIO card */
    kStatus_SDMMC_TuningFail = MAKE_STATUS(kStatusGroup_SDMMC, 33U),               /*!<  tuning fail */
    kStatus_SDMMC_SwitchVoltageFail = MAKE_STATUS(kStatusGroup_SDMMC, 34U),        /*!< switch voltage fail*/
    kStatus_SDMMC_ReTuningRequest = MAKE_STATUS(kStatusGroup_SDMMC, 35U),          /*!<  retuning request */
    kStatus_SDMMC_SetDriverStrengthFail = MAKE_STATUS(kStatusGroup_SDMMC, 36U),    /*!<  set driver strength fail */
    kStatus_SDMMC_SetPowerClassFail = MAKE_STATUS(kStatusGroup_SDMMC, 37U),        /*!<  set power class fail */
};

/*! @brief SD card flags */
enum _sd_card_flag
{
    kSD_SupportHighCapacityFlag = (1U << 1U),     /*!< Support high capacity */
    kSD_Support4BitWidthFlag = (1U << 2U),        /*!< Support 4-bit data width */
    kSD_SupportSdhcFlag = (1U << 3U),             /*!< Card is SDHC */
    kSD_SupportSdxcFlag = (1U << 4U),             /*!< Card is SDXC */
    kSD_SupportVoltage180v = (1U << 5U),          /*!< card support 1.8v voltage*/
    kSD_SupportSetBlockCountCmd = (1U << 6U),     /*!< card support cmd23 flag*/
    kSD_SupportSpeedClassControlCmd = (1U << 7U), /*!< card support speed class control flag */
};

/*! @brief MMC card flags */
enum _mmc_card_flag
{
    kMMC_SupportHighSpeed26MHZFlag = (1U << 0U),           /*!< Support high speed 26MHZ */
    kMMC_SupportHighSpeed52MHZFlag = (1U << 1U),           /*!< Support high speed 52MHZ */
    kMMC_SupportHighSpeedDDR52MHZ180V300VFlag = (1 << 2U), /*!< ddr 52MHZ 1.8V or 3.0V */
    kMMC_SupportHighSpeedDDR52MHZ120VFlag = (1 << 3U),     /*!< DDR 52MHZ 1.2V */
    kMMC_SupportHS200200MHZ180VFlag = (1 << 4U),           /*!< HS200 ,200MHZ,1.8V */
    kMMC_SupportHS200200MHZ120VFlag = (1 << 5U),           /*!< HS200, 200MHZ, 1.2V */
    kMMC_SupportHS400DDR200MHZ180VFlag = (1 << 6U),        /*!< HS400, DDR, 200MHZ,1.8V */
    kMMC_SupportHS400DDR200MHZ120VFlag = (1 << 7U),        /*!< HS400, DDR, 200MHZ,1.2V */
    kMMC_SupportHighCapacityFlag = (1U << 8U),             /*!< Support high capacity */
    kMMC_SupportAlternateBootFlag = (1U << 9U),            /*!< Support alternate boot */
    kMMC_SupportDDRBootFlag = (1U << 10U),                 /*!< support DDR boot flag*/
    kMMC_SupportHighSpeedBootFlag = (1U << 11U),           /*!< support high speed boot flag*/

    kMMC_DataBusWidth4BitFlag = (1U << 12U), /*!< current data bus is 4 bit mode*/
    kMMC_DataBusWidth8BitFlag = (1U << 13U), /*!< current data bus is 8 bit mode*/
    kMMC_DataBusWidth1BitFlag = (1U << 14U), /*!< current data bus is 1 bit mode */

};

/*! @brief card operation voltage */
typedef enum _card_operation_voltage
{
    kCARD_OperationVoltageNone = 0U, /*!< indicate current voltage setting is not setting bu suser*/
    kCARD_OperationVoltage330V = 1U, /*!< card operation voltage around 3.3v */
    kCARD_OperationVoltage300V = 2U, /*!< card operation voltage around 3.0v */
    kCARD_OperationVoltage180V = 3U, /*!< card operation voltage around 31.8v */
} card_operation_voltage_t;

/*!
 * @brief SD card state
 *
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _sd_card
{
    HOST_CONFIG host; /*!< Host information */

    bool isHostReady;                          /*!< use this flag to indicate if need host re-init or not*/
    uint32_t busClock_Hz;                      /*!< SD bus clock frequency united in Hz */
    uint32_t relativeAddress;                  /*!< Relative address of the card */
    uint32_t version;                          /*!< Card version */
    uint32_t flags;                            /*!< Flags in _sd_card_flag */
    uint32_t rawCid[4U];                       /*!< Raw CID content */
    uint32_t rawCsd[4U];                       /*!< Raw CSD content */
    uint32_t rawScr[2U];                       /*!< Raw CSD content */
    uint32_t ocr;                              /*!< Raw OCR content */
    sd_cid_t cid;                              /*!< CID */
    sd_csd_t csd;                              /*!< CSD */
    sd_scr_t scr;                              /*!< SCR */
    uint32_t blockCount;                       /*!< Card total block number */
    uint32_t blockSize;                        /*!< Card block size */
    sd_timing_mode_t currentTiming;            /*!< current timing mode */
    sd_driver_strength_t driverStrength;       /*!< driver strength */
    sd_max_current_t maxCurrent;               /*!< card current limit */
    card_operation_voltage_t operationVoltage; /*!< card operation voltage */
} sd_card_t;

/*!
 * @brief SDIO card state
 *
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _sdio_card
{
    HOST_CONFIG host; /*!< Host information */

    bool isHostReady;    /*!< use this flag to indicate if need host re-init or not*/
    bool memPresentFlag; /*!< indicate if memory present */

    uint32_t busClock_Hz;      /*!< SD bus clock frequency united in Hz */
    uint32_t relativeAddress;  /*!< Relative address of the card */
    uint8_t sdVersion;         /*!< SD version */
    uint8_t sdioVersion;       /*!< SDIO version */
    uint8_t cccrVersioin;      /*!< CCCR version */
    uint8_t ioTotalNumber;     /*!< total number of IO function */
    uint32_t cccrflags;        /*!< Flags in _sd_card_flag */
    uint32_t io0blockSize;     /*!< record the io0 block size*/
    uint32_t ocr;              /*!< Raw OCR content, only 24bit avalible for SDIO card */
    uint32_t commonCISPointer; /*!< point to common CIS */

    sdio_fbr_t ioFBR[7U]; /*!< FBR table */

    sdio_common_cis_t commonCIS; /*!< CIS table */
    sdio_func_cis_t funcCIS[7U]; /*!< function CIS table*/

} sdio_card_t;

/*!
 * @brief SD card state
 *
 * Define the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _mmc_card
{
    HOST_CONFIG host; /*!< Host information */

    bool isHostReady;                                     /*!< use this flag to indicate if need host re-init or not*/
    uint32_t busClock_Hz;                                 /*!< MMC bus clock united in Hz */
    uint32_t relativeAddress;                             /*!< Relative address of the card */
    bool enablePreDefinedBlockCount;                      /*!< Enable PRE-DEFINED block count when read/write */
    uint32_t flags;                                       /*!< Capability flag in _mmc_card_flag */
    uint32_t rawCid[4U];                                  /*!< Raw CID content */
    uint32_t rawCsd[4U];                                  /*!< Raw CSD content */
    uint32_t rawExtendedCsd[MMC_EXTENDED_CSD_BYTES / 4U]; /*!< Raw MMC Extended CSD content */
    uint32_t ocr;                                         /*!< Raw OCR content */
    mmc_cid_t cid;                                        /*!< CID */
    mmc_csd_t csd;                                        /*!< CSD */
    mmc_extended_csd_t extendedCsd;                       /*!< Extended CSD */
    uint32_t blockSize;                                   /*!< Card block size */
    uint32_t userPartitionBlocks;                         /*!< Card total block number in user partition */
    uint32_t bootPartitionBlocks;                         /*!< Boot partition size united as block size */
    uint32_t eraseGroupBlocks;                            /*!< Erase group size united as block size */
    mmc_access_partition_t currentPartition;              /*!< Current access partition */
    mmc_voltage_window_t hostVoltageWindowVCCQ;           /*!< Host IO voltage window */
    mmc_voltage_window_t hostVoltageWindowVCC; /*!< application must set this value according to board specific */
    mmc_high_speed_timing_t currentTiming;     /*!< indicate the current host timing mode*/

} mmc_card_t;

/*! @brief MMC card boot configuration definition. */
typedef struct _mmc_boot_config
{
    bool enableBootAck;                        /*!< Enable boot ACK */
    mmc_boot_partition_enable_t bootPartition; /*!< Boot partition */
    bool retainBootBusWidth;                   /*!< If retain boot bus width */
    mmc_data_bus_width_t bootDataBusWidth;     /*!< Boot data bus width */
} mmc_boot_config_t;

/* define a function pointer for tuning */
typedef status_t (*card_send_tuning_func)(void *cardType);

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
 *
 * This function initializes the card on a specific host controller.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_GoIdleFailed Go idle failed.
 * @retval kStatus_SDMMC_NotSupportYet Card not support.
 * @retval kStatus_SDMMC_SendOperationConditionFailed Send operation condition failed.
 * @retval kStatus_SDMMC_AllSendCidFailed Send CID failed.
 * @retval kStatus_SDMMC_SendRelativeAddressFailed Send relative address failed.
 * @retval kStatus_SDMMC_SendCsdFailed Send CSD failed.
 * @retval kStatus_SDMMC_SelectCardFailed Send SELECT_CARD command failed.
 * @retval kStatus_SDMMC_SendScrFailed Send SCR failed.
 * @retval kStatus_SDMMC_SetBusWidthFailed Set bus width failed.
 * @retval kStatus_SDMMC_SwitchHighSpeedFailed Switch high speed failed.
 * @retval kStatus_SDMMC_SetCardBlockSizeFailed Set card block size failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SD_Init(sd_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * This function deinitializes the specific card.
 *
 * @param card Card descriptor.
 */
void SD_Deinit(sd_card_t *card);

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
 * @brief Reads blocks from the specific card.
 *
 * This function reads blocks from the specific card with default block size defined by the
 * SDHC_CARD_DEFAULT_BLOCK_SIZE.
 *
 * @param card Card descriptor.
 * @param buffer The buffer to save the data read from card.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to read.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDMMC_CardNotSupport Card not support.
 * @retval kStatus_SDMMC_NotSupportYet Not support now.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SD_ReadBlocks(sd_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes blocks of data to the specific card.
 *
 * This function writes blocks to the specific card with default block size 512 bytes.
 *
 * @param card Card descriptor.
 * @param buffer The buffer holding the data to be written to the card.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to write.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDMMC_NotSupportYet Not support now.
 * @retval kStatus_SDMMC_CardNotSupport Card not support.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SD_WriteBlocks(sd_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Erases blocks of the specific card.
 *
 * This function erases blocks of the specific card with default block size 512 bytes.
 *
 * @param card Card descriptor.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to erase.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SD_EraseBlocks(sd_card_t *card, uint32_t startBlock, uint32_t blockCount);

/* @} */

/*!
 * @name MMCCARD Function
 * @{
 */

/*!
 * @brief Initializes the MMC card.
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_GoIdleFailed Go idle failed.
 * @retval kStatus_SDMMC_SendOperationConditionFailed Send operation condition failed.
 * @retval kStatus_SDMMC_AllSendCidFailed Send CID failed.
 * @retval kStatus_SDMMC_SetRelativeAddressFailed Set relative address failed.
 * @retval kStatus_SDMMC_SendCsdFailed Send CSD failed.
 * @retval kStatus_SDMMC_CardNotSupport Card not support.
 * @retval kStatus_SDMMC_SelectCardFailed Send SELECT_CARD command failed.
 * @retval kStatus_SDMMC_SendExtendedCsdFailed Send EXT_CSD failed.
 * @retval kStatus_SDMMC_SetBusWidthFailed Set bus width failed.
 * @retval kStatus_SDMMC_SwitchHighSpeedFailed Switch high speed failed.
 * @retval kStatus_SDMMC_SetCardBlockSizeFailed Set card block size failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t MMC_Init(mmc_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * @param card Card descriptor.
 */

void MMC_Deinit(mmc_card_t *card);

/*!
 * @brief Checks if the card is read-only.
 *
 * @param card Card descriptor.
 * @retval true Card is read only.
 * @retval false Card isn't read only.
 */
bool MMC_CheckReadOnly(mmc_card_t *card);

/*!
 * @brief Reads data blocks from the card.
 *
 * @param card Card descriptor.
 * @param buffer The buffer to save data.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to read.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDMMC_CardNotSupport Card not support.
 * @retval kStatus_SDMMC_SetBlockCountFailed Set block count failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t MMC_ReadBlocks(mmc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes data blocks to the card.
 *
 * @param card Card descriptor.
 * @param buffer The buffer to save data blocks.
 * @param startBlock Start block number to write.
 * @param blockCount Block count.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDMMC_NotSupportYet Not support now.
 * @retval kStatus_SDMMC_SetBlockCountFailed Set block count failed.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t MMC_WriteBlocks(mmc_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Erases groups of the card.
 *
 * Erase group is the smallest erase unit in MMC card. The erase range is [startGroup, endGroup].
 *
 * @param  card Card descriptor.
 * @param  startGroup Start group number.
 * @param  endGroup End group number.
 * @retval kStatus_InvalidArgument Invalid argument.
 * @retval kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t MMC_EraseGroups(mmc_card_t *card, uint32_t startGroup, uint32_t endGroup);

/*!
 * @brief Selects the partition to access.
 *
 * @param card Card descriptor.
 * @param partitionNumber The partition number.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure EXT_CSD failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t MMC_SelectPartition(mmc_card_t *card, mmc_access_partition_t partitionNumber);

/*!
 * @brief Configures the boot activity of the card.
 *
 * @param card Card descriptor.
 * @param config Boot configuration structure.
 * @retval kStatus_SDMMC_NotSupportYet Not support now.
 * @retval kStatus_SDMMC_ConfigureExtendedCsdFailed Configure EXT_CSD failed.
 * @retval kStatus_SDMMC_ConfigureBootFailed Configure boot failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t MMC_SetBootConfig(mmc_card_t *card, const mmc_boot_config_t *config);

/*!
 * @brief set SDIO card to inactive state
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_CardInActive(sdio_card_t *card);

/*!
 * @brief IO direct write transfer function
 *
 * @param card Card descriptor.
 * @param function IO numner
 * @param register address
 * @param the data pinter to write
 * @param raw flag, indicate read after write or write only
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_IO_Write_Direct(sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *data, bool raw);

/*!
 * @brief IO direct read transfer function
 *
 * @param card Card descriptor.
 * @param function IO number
 * @param register address
 * @param data pointer to read
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_IO_Read_Direct(sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *data);

/*!
 * @brief IO extended write transfer function
 *
 * @param card Card descriptor.
 * @param function IO number
 * @param register address
 * @param data buffer to write
 * @param data count
 * @param write flags
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_SDMMC_SDIO_InvalidArgument
 * @retval kStatus_Success
 */
status_t SDIO_IO_Write_Extended(
    sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *buffer, uint32_t count, uint32_t flags);
/*!
 * @brief IO extended read transfer function
 *
 * @param card Card descriptor.
 * @param function IO number
 * @param register address
 * @param data buffer to read
 * @param data count
 * @param write flags
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_SDMMC_SDIO_InvalidArgument
 * @retval kStatus_Success
 */
status_t SDIO_IO_Read_Extended(
    sdio_card_t *card, sdio_func_num_t func, uint32_t regAddr, uint8_t *buffer, uint32_t count, uint32_t flags);
/*!
 * @brief get SDIO card capability
 *
 * @param card Card descriptor.
 * @param function IO number
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_GetCardCapability(sdio_card_t *card, sdio_func_num_t func);

/*!
 * @brief set SDIO card block size
 *
 * @param card Card descriptor.
 * @param function io number
 * @param block size
 * @retval kStatus_SDMMC_SetCardBlockSizeFailed
 * @retval kStatus_SDMMC_SDIO_InvalidArgument
 * @retval kStatus_Success
 */
status_t SDIO_SetBlockSize(sdio_card_t *card, sdio_func_num_t func, uint32_t blockSize);

/*!
 * @brief set SDIO card reset
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_CardReset(sdio_card_t *card);

/*!
 * @brief set SDIO card data bus width
 *
 * @param card Card descriptor.
 * @param data bus width
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_SetDataBusWidth(sdio_card_t *card, sdio_bus_width_t busWidth);

/*!
 * @brief switch the card to high speed
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_SDMMC_SDIO_SwitchHighSpeedFail
 * @retval kStatus_Success
 */
status_t SDIO_SwitchToHighSpeed(sdio_card_t *card);

/*!
 * @brief read SDIO card CIS for each function
 *
 * @param card Card descriptor.
 * @param function io number
 * @param tuple code list
 * @param tuple code number
 * @retval kStatus_SDMMC_SDIO_ReadCISFail
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_ReadCIS(sdio_card_t *card, sdio_func_num_t func, const uint32_t *tupleList, uint32_t tupleNum);

/*!
 * @brief SDIO card init function
 *
 * @param card Card descriptor.
 * @retval kStatus_SDMMC_GoIdleFailed
 * @retval kStatus_SDMMC_HandShakeOperationConditionFailed
 * @retval kStatus_SDMMC_SDIO_InvalidCard
 * @retval kStatus_SDMMC_SDIO_InvalidVoltage
 * @retval kStatus_SDMMC_SendRelativeAddressFailed
 * @retval kStatus_SDMMC_SelectCardFailed
 * @retval kStatus_SDMMC_SDIO_SwitchHighSpeedFail
 * @retval kStatus_SDMMC_SDIO_ReadCISFail
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_Init(sdio_card_t *card);

/*!
 * @brief enable IO interrupt
 *
 * @param card Card descriptor.
 * @param function IO number
 * @param enable/disable flag
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_EnableIOInterrupt(sdio_card_t *card, sdio_func_num_t func, bool enable);

/*!
 * @brief enable IO and wait IO ready
 *
 * @param card Card descriptor.
 * @param function IO number
 * @param enable/disable flag
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_EnableIO(sdio_card_t *card, sdio_func_num_t func, bool enable);

/*!
 * @brief select IO
 *
 * @param card Card descriptor.
 * @param function IO number
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_SelectIO(sdio_card_t *card, sdio_func_num_t func);

/*!
 * @brief Abort IO transfer
 *
 * @param card Card descriptor.
 * @param function IO number
 * @retval kStatus_SDMMC_TransferFailed
 * @retval kStatus_Success
 */
status_t SDIO_AbortIO(sdio_card_t *card, sdio_func_num_t func);

/*!
 * @brief SDIO card deinit
 *
 * @param card Card descriptor.
 */
void SDIO_DeInit(sdio_card_t *card);

/* @} */
#if defined(__cplusplus)
}
#endif
/*! @} */
#endif /* _FSL_CARD_H_*/
