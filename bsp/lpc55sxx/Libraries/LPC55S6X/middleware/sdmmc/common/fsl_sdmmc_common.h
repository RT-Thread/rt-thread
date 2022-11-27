/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SDMMC_COMMON_H_
#define _FSL_SDMMC_COMMON_H_

#include "fsl_common.h"
#include "fsl_sdmmc_host.h"
#include "fsl_sdmmc_spec.h"
#include "stdlib.h"

/*!
 * @addtogroup sdmmc_common SDMMC Common
 * @ingroup card
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Reverse byte sequence in uint32_t */
#define SWAP_WORD_BYTE_SEQUENCE(x) (__REV(x))
/*! @brief Reverse byte sequence for each half word in uint32_t */
#define SWAP_HALF_WROD_BYTE_SEQUENCE(x) (__REV16(x))
/*! @brief Maximum loop count to check the card operation voltage range */
#define FSL_SDMMC_MAX_VOLTAGE_RETRIES (1000U)
/*! @brief Maximum loop count to send the cmd */
#define FSL_SDMMC_MAX_CMD_RETRIES (10U)
/*! @brief Default block size */
#define FSL_SDMMC_DEFAULT_BLOCK_SIZE (512U)

/*! @brief make sure the internal buffer address is cache align */
#if defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#if defined(FSL_FEATURE_L2DCACHE_LINESIZE_BYTE)
#define SDMMC_DATA_BUFFER_ALIGN_CACHE MAX(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE, FSL_FEATURE_L2DCACHE_LINESIZE_BYTE)
#else
#define SDMMC_DATA_BUFFER_ALIGN_CACHE FSL_FEATURE_L1DCACHE_LINESIZE_BYTE
#endif
#else
#define SDMMC_DATA_BUFFER_ALIGN_CACHE sizeof(uint32_t)
#endif

/*! @brief sdmmc card internal buffer size */
#define FSL_SDMMC_CARD_INTERNAL_BUFFER_SIZE (FSL_SDMMC_DEFAULT_BLOCK_SIZE + SDMMC_DATA_BUFFER_ALIGN_CACHE)
#define FSL_SDMMC_CARD_INTERNAL_BUFFER_ALIGN_ADDR(buffer)                     \
    (uint32_t)((uint32_t)(buffer) + (uint32_t)SDMMC_DATA_BUFFER_ALIGN_CACHE - \
               ((uint32_t)(buffer) & ((uint32_t)SDMMC_DATA_BUFFER_ALIGN_CACHE - 1U)))
/*! @brief get maximum freq */
#define FSL_SDMMC_CARD_MAX_BUS_FREQ(max, target) ((max) == 0U ? (target) : ((max) > (target) ? (target) : (max)))
/*! @brief SD/MMC error log. */
#if defined SDMMC_ENABLE_LOG_PRINT
#include "fsl_debug_console.h"
#define SDMMC_LOG(...) PRINTF(__VA_ARGS__)
#else
#define SDMMC_LOG(format, ...)
#endif

/*! @brief SD/MMC card API's running status.
 *  @anchor _sdmmc_status
 */
enum
{
    kStatus_SDMMC_NotSupportYet             = MAKE_STATUS(kStatusGroup_SDMMC, 0U),  /*!< Haven't supported */
    kStatus_SDMMC_TransferFailed            = MAKE_STATUS(kStatusGroup_SDMMC, 1U),  /*!< Send command failed */
    kStatus_SDMMC_SetCardBlockSizeFailed    = MAKE_STATUS(kStatusGroup_SDMMC, 2U),  /*!< Set block size failed */
    kStatus_SDMMC_HostNotSupport            = MAKE_STATUS(kStatusGroup_SDMMC, 3U),  /*!< Host doesn't support */
    kStatus_SDMMC_CardNotSupport            = MAKE_STATUS(kStatusGroup_SDMMC, 4U),  /*!< Card doesn't support */
    kStatus_SDMMC_AllSendCidFailed          = MAKE_STATUS(kStatusGroup_SDMMC, 5U),  /*!< Send CID failed */
    kStatus_SDMMC_SendRelativeAddressFailed = MAKE_STATUS(kStatusGroup_SDMMC, 6U),  /*!< Send relative address failed */
    kStatus_SDMMC_SendCsdFailed             = MAKE_STATUS(kStatusGroup_SDMMC, 7U),  /*!< Send CSD failed */
    kStatus_SDMMC_SelectCardFailed          = MAKE_STATUS(kStatusGroup_SDMMC, 8U),  /*!< Select card failed */
    kStatus_SDMMC_SendScrFailed             = MAKE_STATUS(kStatusGroup_SDMMC, 9U),  /*!< Send SCR failed */
    kStatus_SDMMC_SetDataBusWidthFailed     = MAKE_STATUS(kStatusGroup_SDMMC, 10U), /*!< Set bus width failed */
    kStatus_SDMMC_GoIdleFailed              = MAKE_STATUS(kStatusGroup_SDMMC, 11U), /*!< Go idle failed */
    kStatus_SDMMC_HandShakeOperationConditionFailed =
        MAKE_STATUS(kStatusGroup_SDMMC, 12U), /*!< Send Operation Condition failed */
    kStatus_SDMMC_SendApplicationCommandFailed =
        MAKE_STATUS(kStatusGroup_SDMMC, 13U), /*!< Send application command failed */
    kStatus_SDMMC_SwitchFailed               = MAKE_STATUS(kStatusGroup_SDMMC, 14U), /*!< Switch command failed */
    kStatus_SDMMC_StopTransmissionFailed     = MAKE_STATUS(kStatusGroup_SDMMC, 15U), /*!< Stop transmission failed */
    kStatus_SDMMC_WaitWriteCompleteFailed    = MAKE_STATUS(kStatusGroup_SDMMC, 16U), /*!< Wait write complete failed */
    kStatus_SDMMC_SetBlockCountFailed        = MAKE_STATUS(kStatusGroup_SDMMC, 17U), /*!< Set block count failed */
    kStatus_SDMMC_SetRelativeAddressFailed   = MAKE_STATUS(kStatusGroup_SDMMC, 18U), /*!< Set relative address failed */
    kStatus_SDMMC_SwitchBusTimingFailed      = MAKE_STATUS(kStatusGroup_SDMMC, 19U), /*!< Switch high speed failed */
    kStatus_SDMMC_SendExtendedCsdFailed      = MAKE_STATUS(kStatusGroup_SDMMC, 20U), /*!< Send EXT_CSD failed */
    kStatus_SDMMC_ConfigureBootFailed        = MAKE_STATUS(kStatusGroup_SDMMC, 21U), /*!< Configure boot failed */
    kStatus_SDMMC_ConfigureExtendedCsdFailed = MAKE_STATUS(kStatusGroup_SDMMC, 22U), /*!< Configure EXT_CSD failed */
    kStatus_SDMMC_EnableHighCapacityEraseFailed =
        MAKE_STATUS(kStatusGroup_SDMMC, 23U), /*!< Enable high capacity erase failed */
    kStatus_SDMMC_SendTestPatternFailed    = MAKE_STATUS(kStatusGroup_SDMMC, 24U), /*!< Send test pattern failed */
    kStatus_SDMMC_ReceiveTestPatternFailed = MAKE_STATUS(kStatusGroup_SDMMC, 25U), /*!< Receive test pattern failed */
    kStatus_SDMMC_SDIO_ResponseError       = MAKE_STATUS(kStatusGroup_SDMMC, 26U), /*!< sdio response error */
    kStatus_SDMMC_SDIO_InvalidArgument =
        MAKE_STATUS(kStatusGroup_SDMMC, 27U), /*!< sdio invalid argument response error */
    kStatus_SDMMC_SDIO_SendOperationConditionFail =
        MAKE_STATUS(kStatusGroup_SDMMC, 28U), /*!< sdio send operation condition fail */
    kStatus_SDMMC_InvalidVoltage           = MAKE_STATUS(kStatusGroup_SDMMC, 29U), /*!<  invaild voltage */
    kStatus_SDMMC_SDIO_SwitchHighSpeedFail = MAKE_STATUS(kStatusGroup_SDMMC, 30U), /*!<  switch to high speed fail */
    kStatus_SDMMC_SDIO_ReadCISFail         = MAKE_STATUS(kStatusGroup_SDMMC, 31U), /*!<  read CIS fail */
    kStatus_SDMMC_SDIO_InvalidCard         = MAKE_STATUS(kStatusGroup_SDMMC, 32U), /*!<  invaild SDIO card */
    kStatus_SDMMC_TuningFail               = MAKE_STATUS(kStatusGroup_SDMMC, 33U), /*!<  tuning fail */

    kStatus_SDMMC_SwitchVoltageFail              = MAKE_STATUS(kStatusGroup_SDMMC, 34U), /*!< switch voltage fail*/
    kStatus_SDMMC_SwitchVoltage18VFail33VSuccess = MAKE_STATUS(kStatusGroup_SDMMC, 35U), /*!< switch voltage fail*/

    kStatus_SDMMC_ReTuningRequest       = MAKE_STATUS(kStatusGroup_SDMMC, 36U), /*!<  retuning request */
    kStatus_SDMMC_SetDriverStrengthFail = MAKE_STATUS(kStatusGroup_SDMMC, 37U), /*!<  set driver strength fail */
    kStatus_SDMMC_SetPowerClassFail     = MAKE_STATUS(kStatusGroup_SDMMC, 38U), /*!<  set power class fail */
    kStatus_SDMMC_HostNotReady          = MAKE_STATUS(kStatusGroup_SDMMC, 39U), /*!<  host controller not ready */
    kStatus_SDMMC_CardDetectFailed      = MAKE_STATUS(kStatusGroup_SDMMC, 40U), /*!<  card detect failed */
    kStatus_SDMMC_AuSizeNotSetProperly  = MAKE_STATUS(kStatusGroup_SDMMC, 41U), /*!<  AU size not set properly */
    kStatus_SDMMC_PollingCardIdleFailed = MAKE_STATUS(kStatusGroup_SDMMC, 42U), /*!< polling card idle status failed */
    kStatus_SDMMC_DeselectCardFailed    = MAKE_STATUS(kStatusGroup_SDMMC, 43U), /*!< deselect card failed */
    kStatus_SDMMC_CardStatusIdle        = MAKE_STATUS(kStatusGroup_SDMMC, 44U), /*!< card idle  */
    kStatus_SDMMC_CardStatusBusy        = MAKE_STATUS(kStatusGroup_SDMMC, 45U), /*!< card busy */
    kStatus_SDMMC_CardInitFailed        = MAKE_STATUS(kStatusGroup_SDMMC, 46U), /*!< card init failed */
};

/*! @brief sdmmc signal line
 * @anchor _sdmmc_signal_line
 */
enum
{
    kSDMMC_SignalLineCmd   = 1U,   /*!< cmd line */
    kSDMMC_SignalLineData0 = 2U,   /*!< data line */
    kSDMMC_SignalLineData1 = 4U,   /*!< data line */
    kSDMMC_SignalLineData2 = 8U,   /*!< data line */
    kSDMMC_SignalLineData3 = 16U,  /*!< data line */
    kSDMMC_SignalLineData4 = 32U,  /*!< data line */
    kSDMMC_SignalLineData5 = 64U,  /*!< data line */
    kSDMMC_SignalLineData6 = 128U, /*!< data line */
    kSDMMC_SignalLineData7 = 256U, /*!< data line */
};

/*! @brief card operation voltage */
typedef enum _sdmmc_operation_voltage
{
    kSDMMC_OperationVoltageNone = 0U, /*!< indicate current voltage setting is not setting by suser*/
    kSDMMC_OperationVoltage330V = 1U, /*!< card operation voltage around 3.3v */
    kSDMMC_OperationVoltage300V = 2U, /*!< card operation voltage around 3.0v */
    kSDMMC_OperationVoltage180V = 3U, /*!< card operation voltage around 1.8v */
} sdmmc_operation_voltage_t;

/*!@brief card bus width
 * @anchor _sdmmc_bus_width
 */
enum
{
    kSDMMC_BusWdith1Bit = 0U, /*!< card bus 1 width */
    kSDMMC_BusWdith4Bit = 1U, /*!< card bus 4 width */
    kSDMMC_BusWdith8Bit = 2U, /*!< card bus 8 width */
};

/*!@brief sdmmc capability flag
 * @anchor _sdmmc_capability_flag
 */
enum
{
    kSDMMC_Support8BitWidth = 1U, /*!< 8 bit data width capability */
};

/*!@ brief sdmmc data packet format
 * @anchor _sdmmc_data_packet_format
 */
enum
{
    kSDMMC_DataPacketFormatLSBFirst, /*!< usual data packet format LSB first, MSB last */
    kSDMMC_DataPacketFormatMSBFirst, /*!< Wide width data packet format MSB first, LSB last */
};

/*! @brief sd card detect type */
typedef enum _sd_detect_card_type
{
    kSD_DetectCardByGpioCD,    /*!< sd card detect by CD pin through GPIO */
    kSD_DetectCardByHostCD,    /*!< sd card detect by CD pin through host */
    kSD_DetectCardByHostDATA3, /*!< sd card detect by DAT3 pin through host */
} sd_detect_card_type_t;

/*!@ brief SD card detect status
 * @anchor _sd_card_cd_status
 */
enum
{
    kSD_Inserted = 1U, /*!< card is inserted*/
    kSD_Removed  = 0U, /*!< card is removed */
};

/*!@ brief SD card detect status
 * @anchor _sd_card_dat3_pull_status
 */
enum
{
    kSD_DAT3PullDown = 0U, /*!< data3 pull down */
    kSD_DAT3PullUp   = 1U, /*!< data3 pull up */
};

/*! @brief card detect aoolication callback definition */
typedef void (*sd_cd_t)(bool isInserted, void *userData);
/*! @brief card detect status */
typedef bool (*sd_cd_status_t)(void);
typedef void (*sd_dat3_pull_t)(uint32_t pullStatus);

/*! @brief sd card detect */
typedef struct _sd_detect_card
{
    sd_detect_card_type_t type;  /*!< card detect type */
    uint32_t cdDebounce_ms;      /*!< card detect debounce delay ms */
    sd_cd_t callback;            /*!< card inserted callback which is meaningful for interrupt case */
    sd_cd_status_t cardDetected; /*!< used to check sd cd status when card detect through GPIO */
    sd_dat3_pull_t dat3PullFunc; /*!< function pointer of DATA3 pull up/down */

    void *userData; /*!< user data */
} sd_detect_card_t;

/*!@brief io voltage control type*/
typedef enum _sd_io_voltage_ctrl_type
{
    kSD_IOVoltageCtrlNotSupport = 0U, /*!< io voltage control not support */
    kSD_IOVoltageCtrlByHost     = 1U, /*!< io voltage control by host */
    kSD_IOVoltageCtrlByGpio     = 2U, /*!< io voltage control by gpio */
} sd_io_voltage_ctrl_type_t;

/*! @brief card switch voltage function pointer */
typedef void (*sd_io_voltage_func_t)(sdmmc_operation_voltage_t voltage);

/*!@brief io voltage control configuration */
typedef struct _sd_io_voltage
{
    sd_io_voltage_ctrl_type_t type; /*!< io voltage switch type */
    sd_io_voltage_func_t func;      /*!< io voltage switch function */
} sd_io_voltage_t;

/*! @brief card power control function pointer */
typedef void (*sd_pwr_t)(bool enable);
/*! @brief card io strength control */
typedef void (*sd_io_strength_t)(uint32_t busFreq);
/*! @brief sdcard user parameter */
typedef struct _sd_usr_param
{
    sd_pwr_t pwr;             /*!< power control configuration pointer */
    uint32_t powerOnDelayMS;  /*!< power on delay time */
    uint32_t powerOffDelayMS; /*!< power off delay time */

    sd_io_strength_t ioStrength; /*!< swicth sd io strength */
    sd_io_voltage_t *ioVoltage;  /*!< switch io voltage */
    sd_detect_card_t *cd;        /*!< card detect */

    uint32_t maxFreq;    /*!< board support maximum frequency */
    uint32_t capability; /*!< board capability flag */
} sd_usr_param_t;

/*! @brief card interrupt function pointer */
typedef void (*sdio_int_t)(void *userData);

/*! @brief card interrupt application callback */
typedef struct _sdio_card_int
{
    void *userData;           /*!< user data */
    sdio_int_t cardInterrupt; /*!< card int call back */
} sdio_card_int_t;

/*! @brief sdio user parameter */
typedef struct _sdio_usr_param
{
    sd_pwr_t pwr;             /*!< power control configuration pointer */
    uint32_t powerOnDelayMS;  /*!< power on delay time */
    uint32_t powerOffDelayMS; /*!< power off delay time */

    sd_io_strength_t ioStrength; /*!< swicth sd io strength */
    sd_io_voltage_t *ioVoltage;  /*!< switch io voltage */
    sd_detect_card_t *cd;        /*!< card detect */
    sdio_card_int_t *sdioInt;    /*!< card int */
    uint32_t maxFreq;            /*!< board support maximum frequency */
    uint32_t capability;         /*!< board capability flag */
} sdio_usr_param_t;

/*! @brief tuning pattern */
#if SDMMCHOST_SUPPORT_DDR50 || SDMMCHOST_SUPPORT_SDR104 || SDMMCHOST_SUPPORT_SDR50 || SDMMCHOST_SUPPORT_HS200 || \
    SDMMCHOST_SUPPORT_HS400
/* sdmmc tuning block */
extern const uint32_t SDMMC_TuningBlockPattern4Bit[16U];
extern const uint32_t SDMMC_TuningBlockPattern8Bit[32U];
#endif

/*************************************************************************************************
 * API
 ************************************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif
/*!
 * @name common function
 * @{
 */

/*!
 * @brief Selects the card to put it into transfer state.
 *
 * @param host host handler.
 * @param relativeAddress Relative address.
 * @param isSelected True to put card into transfer state.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SelectCard(sdmmchost_t *host, uint32_t relativeAddress, bool isSelected);

/*!
 * @brief Sends an application command.
 *
 * @param host host handler.
 * @param relativeAddress Card relative address.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_SDMMC_CardNotSupport Card doesn't support.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SendApplicationCommand(sdmmchost_t *host, uint32_t relativeAddress);

/*!
 * @brief Sets the block count.
 *
 * @param host host handler.
 * @param blockCount Block count.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SetBlockCount(sdmmchost_t *host, uint32_t blockCount);

/*!
 * @brief Sets the card to be idle state.
 *
 * @param host host handler.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_GoIdle(sdmmchost_t *host);
/*!
 * @brief Sets data block size.
 *
 * @param host host handler.
 * @param blockSize Block size.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SetBlockSize(sdmmchost_t *host, uint32_t blockSize);
/*!
 * @brief Sets card to inactive status
 *
 * @param host host handler.
 * @retval kStatus_SDMMC_TransferFailed Transfer failed.
 * @retval kStatus_Success Operate successfully.
 */
status_t SDMMC_SetCardInactive(sdmmchost_t *host);

/* @} */

#if defined(__cplusplus)
}
#endif
/* @} */
#endif /* _FSL_SDMMC_COMMON_H_ */
