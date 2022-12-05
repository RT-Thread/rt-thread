/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MMC_H_
#define _FSL_MMC_H_

#include "fsl_sdmmc_common.h"

/*!
 * @addtogroup mmccard MMC Card Driver
 * @ingroup card
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Middleware mmc version. */
#define FSL_MMC_DRIVER_VERSION (MAKE_VERSION(2U, 5U, 0U)) /*2.5.0*/

/*! @brief MMC card flags
 * @anchor _mmc_card_flag
 */
enum
{
    kMMC_SupportHighSpeed26MHZFlag            = (1U << 0U),  /*!< Support high speed 26MHZ */
    kMMC_SupportHighSpeed52MHZFlag            = (1U << 1U),  /*!< Support high speed 52MHZ */
    kMMC_SupportHighSpeedDDR52MHZ180V300VFlag = (1 << 2U),   /*!< ddr 52MHZ 1.8V or 3.0V */
    kMMC_SupportHighSpeedDDR52MHZ120VFlag     = (1 << 3U),   /*!< DDR 52MHZ 1.2V */
    kMMC_SupportHS200200MHZ180VFlag           = (1 << 4U),   /*!< HS200 ,200MHZ,1.8V */
    kMMC_SupportHS200200MHZ120VFlag           = (1 << 5U),   /*!< HS200, 200MHZ, 1.2V */
    kMMC_SupportHS400DDR200MHZ180VFlag        = (1 << 6U),   /*!< HS400, DDR, 200MHZ,1.8V */
    kMMC_SupportHS400DDR200MHZ120VFlag        = (1 << 7U),   /*!< HS400, DDR, 200MHZ,1.2V */
    kMMC_SupportHighCapacityFlag              = (1U << 8U),  /*!< Support high capacity */
    kMMC_SupportAlternateBootFlag             = (1U << 9U),  /*!< Support alternate boot */
    kMMC_SupportDDRBootFlag                   = (1U << 10U), /*!< support DDR boot flag*/
    kMMC_SupportHighSpeedBootFlag             = (1U << 11U), /*!< support high speed boot flag */
    kMMC_SupportEnhanceHS400StrobeFlag        = (1U << 12U), /*!< support enhance HS400 strobe */
};

/*! @brief mmccard sleep/awake state */
typedef enum _mmc_sleep_awake
{
    kMMC_Sleep = 1U, /*!< MMC card sleep */
    kMMC_Awake = 0U, /*!< MMC card awake */
} mmc_sleep_awake_t;

/*! @brief card io strength control */
typedef void (*mmc_io_strength_t)(uint32_t busFreq);

/*! @brief card user parameter */
typedef struct _mmc_usr_param
{
    mmc_io_strength_t ioStrength; /*!< switch sd io strength */
    uint32_t maxFreq;             /*!< board support maximum frequency */
    uint32_t capability;          /*!< board capability flag */
} mmc_usr_param_t;

/*!
 * @brief mmc card state
 *
 * Defines the card structure including the necessary fields to identify and describe the card.
 */
typedef struct _mmc_card
{
    sdmmchost_t *host;        /*!< Host information */
    mmc_usr_param_t usrParam; /*!< user parameter */

    bool isHostReady;         /*!< Use this flag to indicate if host re-init needed or not*/
    bool noInteralAlign;      /*!< Use this flag to disable sdmmc align. If disabled, sdmmc will not make sure the
                    data buffer address is word align, otherwise all the transfer are aligned to low level driver. */
    uint32_t busClock_Hz;     /*!< MMC bus clock united in Hz */
    uint32_t relativeAddress; /*!< Relative address of the card */
    bool enablePreDefinedBlockCount; /*!< Enable PRE-DEFINED block count when read/write */
    uint32_t flags;                  /*!< Capability flag in @ref _mmc_card_flag */

    uint8_t internalBuffer[FSL_SDMMC_CARD_INTERNAL_BUFFER_SIZE]; /*!< raw buffer used for mmc driver internal  */
    uint32_t ocr;                                                /*!< Raw OCR content */
    mmc_cid_t cid;                                               /*!< CID */
    mmc_csd_t csd;                                               /*!< CSD */
    mmc_extended_csd_t extendedCsd;                              /*!< Extended CSD */
    uint32_t blockSize;                                          /*!< Card block size */
    uint32_t userPartitionBlocks;                                /*!< Card total block number in user partition */
    uint32_t bootPartitionBlocks;                                /*!< Boot partition size united as block size */
    uint32_t eraseGroupBlocks;                                   /*!< Erase group size united as block size */
    mmc_access_partition_t currentPartition;                     /*!< Current access partition */
    mmc_voltage_window_t hostVoltageWindowVCCQ; /*!< application must set this value according to board specific */
    mmc_voltage_window_t hostVoltageWindowVCC;  /*!< application must set this value according to board specific */
    mmc_high_speed_timing_t busTiming;          /*!< indicates the current work timing mode*/
    mmc_data_bus_width_t busWidth;              /*!< indicates the current work bus width */
    sdmmc_osa_mutex_t lock;                     /*!< card access lock */
} mmc_card_t;

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name MMCCARD Function
 * @{
 */

/*!
 * @brief Initializes the MMC card and host.
 *
 * @param card Card descriptor.
 *
 * Thread safe function, please note that the function will create the mutex lock dynamically by default,
 * so to avoid the mutex to be created redundantly, application must follow bellow sequence for card re-initialization:
 * @code
   MMC_Deinit(card);
   MMC_Init(card);
 * @endcode
 *
 * @retval #kStatus_SDMMC_HostNotReady Host is not ready.
 * @retval #kStatus_SDMMC_GoIdleFailed Going idle failed.
 * @retval #kStatus_SDMMC_HandShakeOperationConditionFailed Sending operation condition failed.
 * @retval #kStatus_SDMMC_AllSendCidFailed Sending CID failed.
 * @retval #kStatus_SDMMC_SetRelativeAddressFailed Setging relative address failed.
 * @retval #kStatus_SDMMC_SendCsdFailed Sending CSD failed.
 * @retval #kStatus_SDMMC_CardNotSupport Card not support.
 * @retval #kStatus_SDMMC_SelectCardFailed Sending SELECT_CARD command failed.
 * @retval #kStatus_SDMMC_SendExtendedCsdFailed Sending EXT_CSD failed.
 * @retval #kStatus_SDMMC_SetDataBusWidthFailed Setting bus width failed.
 * @retval #kStatus_SDMMC_SwitchBusTimingFailed Switching high speed failed.
 * @retval #kStatus_SDMMC_SetCardBlockSizeFailed Setting card block size failed.
 * @retval #kStatus_SDMMC_SetPowerClassFail Setting card power class failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_Init(mmc_card_t *card);

/*!
 * @brief Deinitializes the card and host.
 *
 * @note It is a thread safe function.
 *
 * @param card Card descriptor.
 */
void MMC_Deinit(mmc_card_t *card);

/*!
 * @brief Initializes the card.
 *
 * Thread safe function, please note that the function will create the mutex lock dynamically by default,
 * so to avoid the mutex to be created redundantly, application must follow bellow sequence for card re-initialization:
 * @code
   MMC_CardDeinit(card);
   MMC_CardInit(card);
 * @endcode
 *
 * @param card Card descriptor.
 *
 * @retval #kStatus_SDMMC_HostNotReady Host is not ready.
 * @retval #kStatus_SDMMC_GoIdleFailed Going idle failed.
 * @retval #kStatus_SDMMC_HandShakeOperationConditionFailed Sending operation condition failed.
 * @retval #kStatus_SDMMC_AllSendCidFailed Sending CID failed.
 * @retval #kStatus_SDMMC_SetRelativeAddressFailed Setting relative address failed.
 * @retval #kStatus_SDMMC_SendCsdFailed Sending CSD failed.
 * @retval #kStatus_SDMMC_CardNotSupport Card not support.
 * @retval #kStatus_SDMMC_SelectCardFailed Sending SELECT_CARD command failed.
 * @retval #kStatus_SDMMC_SendExtendedCsdFailed Sending EXT_CSD failed.
 * @retval #kStatus_SDMMC_SetDataBusWidthFailed Setting bus width failed.
 * @retval #kStatus_SDMMC_SwitchBusTimingFailed Switching high speed failed.
 * @retval #kStatus_SDMMC_SetCardBlockSizeFailed Setting card block size failed.
 * @retval #kStatus_SDMMC_SetPowerClassFail Setting card power class failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_CardInit(mmc_card_t *card);

/*!
 * @brief Deinitializes the card.
 *
 * @note It is a thread safe function.
 *
 * @param card Card descriptor.
 */
void MMC_CardDeinit(mmc_card_t *card);

/*!
 * @brief initialize the host.
 *
 * This function deinitializes the specific host.
 *
 * @param card Card descriptor.
 */
status_t MMC_HostInit(mmc_card_t *card);

/*!
 * @brief Deinitializes the host.
 *
 * This function deinitializes the host.
 *
 * @param card Card descriptor.
 */
void MMC_HostDeinit(mmc_card_t *card);

/*!
 * @brief Resets the host.
 *
 * This function resets the specific host.
 *
 * @param card Card descriptor.
 */
void MMC_HostDoReset(mmc_card_t *card);

/*!
 * @brief Resets the host.
 *
 * @deprecated Do not use this function.  It has been superceded by @ref MMC_HostDoReset.
 * This function resets the specific host.
 *
 * @param host Host descriptor.
 */
void MMC_HostReset(SDMMCHOST_CONFIG *host);

/*!
 * @brief Sets card power.
 *
 * @param card Card descriptor.
 * @param enable True is powering on, false is powering off.
 */
void MMC_SetCardPower(mmc_card_t *card, bool enable);

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
 * @note It is a thread safe function.
 *
 * @param card Card descriptor.
 * @param buffer The buffer to save data.
 * @param startBlock The start block index.
 * @param blockCount The number of blocks to read.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDMMC_CardNotSupport Card not support.
 * @retval #kStatus_SDMMC_SetBlockCountFailed Setting block count failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_StopTransmissionFailed Stopping transmission failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_ReadBlocks(mmc_card_t *card, uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Writes data blocks to the card.
 *
 * @note
 * 1. It is a thread safe function.
 * 2. It is an async write function which means that the card status may still be busy after the function returns.
 * Application can call function MMC_PollingCardStatusBusy to wait for the card status to be idle after the write
 * operation.
 *
 * @param card Card descriptor.
 * @param buffer The buffer to save data blocks.
 * @param startBlock Start block number to write.
 * @param blockCount Block count.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDMMC_NotSupportYet Not support now.
 * @retval #kStatus_SDMMC_SetBlockCountFailed Setting block count failed.
 * @retval #kStatus_SDMMC_WaitWriteCompleteFailed Sending status failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_StopTransmissionFailed Stop transmission failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_WriteBlocks(mmc_card_t *card, const uint8_t *buffer, uint32_t startBlock, uint32_t blockCount);

/*!
 * @brief Erases groups of the card.
 *
 * The erase command is best used to erase the entire device or a partition.
 * Erase group is the smallest erase unit in MMC card. The erase range is [startGroup, endGroup].
 *
 * @note
 * 1. It is a thread safe function.
 * 2. This function always polls card busy status according to the timeout value defined in the card register after
 * all the erase command sent out.
 *
 * @param  card Card descriptor.
 * @param  startGroup Start group number.
 * @param  endGroup End group number.
 * @retval #kStatus_InvalidArgument Invalid argument.
 * @retval #kStatus_SDMMC_WaitWriteCompleteFailed Send status failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_EraseGroups(mmc_card_t *card, uint32_t startGroup, uint32_t endGroup);

/*!
 * @brief Selects the partition to access.
 *
 * @note It is a thread safe function.
 *
 * @param card Card descriptor.
 * @param partitionNumber The partition number.
 * @retval #kStatus_SDMMC_ConfigureExtendedCsdFailed Configuring EXT_CSD failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_SelectPartition(mmc_card_t *card, mmc_access_partition_t partitionNumber);

/*!
 * @brief Configures the boot activity of the card.
 *
 * @param card Card descriptor.
 * @param config Boot configuration structure.
 * @retval #kStatus_SDMMC_NotSupportYet Not support now.
 * @retval #kStatus_SDMMC_ConfigureExtendedCsdFailed Configuring EXT_CSD failed.
 * @retval #kStatus_SDMMC_ConfigureBootFailed Configuring boot failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_SetBootConfig(mmc_card_t *card, const mmc_boot_config_t *config);

/*!
 * @brief MMC card start boot.
 *
 * @param card Card descriptor.
 * @param mmcConfig The mmc Boot configuration structure.
 * @param buffer Address to receive data.
 * @param hostConfig Host boot configurations.
 * @retval #kStatus_Fail Failed.
 * @retval #kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval #kStatus_SDMMC_GoIdleFailed Resetting card failed.
 * @retval #kStatus_Success Operation succeeded.
 */
status_t MMC_StartBoot(mmc_card_t *card,
                       const mmc_boot_config_t *mmcConfig,
                       uint8_t *buffer,
                       sdmmchost_boot_config_t *hostConfig);

/*!
 * @brief MMC card set boot configuration write protect.
 *
 * @param card Card descriptor.
 * @param wp Write protect value.
 */
status_t MMC_SetBootConfigWP(mmc_card_t *card, uint8_t wp);

/*!
 * @brief MMC card continuous read boot data.
 *
 * @param card Card descriptor.
 * @param buffer Buffer address.
 * @param hostConfig Host boot configurations.
 */
status_t MMC_ReadBootData(mmc_card_t *card, uint8_t *buffer, sdmmchost_boot_config_t *hostConfig);

/*!
 * @brief MMC card stop boot mode.
 *
 * @param card Card descriptor.
 * @param bootMode Boot mode.
 */
status_t MMC_StopBoot(mmc_card_t *card, uint32_t bootMode);

/*!
 * @brief MMC card set boot partition write protect.
 *
 * @param card Card descriptor.
 * @param bootPartitionWP Boot partition write protect value.
 */
status_t MMC_SetBootPartitionWP(mmc_card_t *card, mmc_boot_partition_wp_t bootPartitionWP);

/*!
 * @brief MMC card cache control function.
 *
 * The mmc device's cache is enabled by the driver by default.
 * The cache should in typical case reduce the access time (compared to an access to the main nonvolatile storage) for
 * both write and read.
 *
 * @param card Card descriptor.
 * @param enable True is enabling the cache, false is disabling the cache.
 */
status_t MMC_EnableCacheControl(mmc_card_t *card, bool enable);

/*!
 * @brief MMC card cache flush function.
 *
 * A Flush operation refers to the requirement, from the host to the device, to write the cached data to the nonvolatile
 * memory. Prior to a flush, the device may autonomously write data to the nonvolatile memory, but after the flush
 * operation all data in the volatile area must be written to nonvolatile memory. There is no requirement for flush due
 * to switching between the partitions. (Note: This also implies that the cache data shall not be lost when switching
 * between partitions). Cached data may be lost in SLEEP state, so host should flush the cache before placing the device
 * into SLEEP state.
 *
 * @param card Card descriptor.
 */
status_t MMC_FlushCache(mmc_card_t *card);

/*!
 * @brief MMC sets card sleep awake state.
 *
 * The Sleep/Awake command is used to initiate the state transition between Standby state and Sleep state.
 * The memory device indicates the transition phase busy by pulling down the DAT0 line.
 * The Sleep/Standby state is reached when the memory device stops pulling down the DAT0 line, then the function
 * returns.
 *
 * @param card Card descriptor.
 * @param state The sleep/awake command argument, refer to @ref mmc_sleep_awake_t.
 *
 * @retval kStatus_SDMMC_NotSupportYet Indicates the memory device doesn't support the Sleep/Awake command.
 * @retval kStatus_SDMMC_TransferFailed Indicates command transferred fail.
 * @retval kStatus_SDMMC_PollingCardIdleFailed Indicates polling DAT0 busy timeout.
 * @retval kStatus_SDMMC_DeselectCardFailed Indicates deselect card command failed.
 * @retval kStatus_SDMMC_SelectCardFailed Indicates select card command failed.
 * @retval kStatus_Success Indicates the card state switched successfully.
 */
status_t MMC_SetSleepAwake(mmc_card_t *card, mmc_sleep_awake_t state);

/*!
 * @brief Polling card idle status.
 *
 * This function can be used to poll the status from busy to idle, the function will return with the card
 * status being idle or timeout or command failed.
 *
 * @param card Card descriptor.
 * @param checkStatus True is send CMD and read DAT0 status to check card status, false is read DAT0 status only.
 * @param timeoutMs Polling card status timeout value.
 *
 * @retval kStatus_SDMMC_CardStatusIdle Card is idle.
 * @retval kStatus_SDMMC_CardStatusBusy Card is busy.
 * @retval kStatus_SDMMC_TransferFailed Command tranfer failed.
 * @retval kStatus_SDMMC_SwitchFailed Status command reports switch error.
 */
status_t MMC_PollingCardStatusBusy(mmc_card_t *card, bool checkStatus, uint32_t timeoutMs);

/* @} */
#if defined(__cplusplus)
}
#endif
/*! @} */
#endif /* _FSL_MMC_H_*/
