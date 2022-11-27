/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_SDMMC_HOST_H
#define _FSL_SDMMC_HOST_H

#include "fsl_common.h"
#include "fsl_sdif.h"
#include "fsl_sdmmc_osa.h"
/*!
 * @addtogroup  sdmmchost_sdif SDIF HOST Adapter Driver
 * @ingroup sdmmchost
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Middleware adapter version. */
#define FSL_SDMMC_HOST_ADAPTER_VERSION (MAKE_VERSION(2U, 4U, 0U)) /*2.4.0*/

/*! @brief sdmmc host capability */
enum
{
    kSDMMCHOST_SupportHighSpeed         = 1U << 0U,  /*!< high speed capability */
    kSDMMCHOST_SupportSuspendResume     = 1U << 1U,  /*!< suspend resume capability */
    kSDMMCHOST_SupportVoltage3v3        = 1U << 2U,  /*!< 3V3 capability */
    kSDMMCHOST_SupportVoltage3v0        = 1U << 3U,  /*!< 3V0 capability */
    kSDMMCHOST_SupportVoltage1v8        = 1U << 4U,  /*!< 1V8 capability */
    kSDMMCHOST_SupportVoltage1v2        = 1U << 5U,  /*!< 1V2 capability */
    kSDMMCHOST_Support4BitDataWidth     = 1U << 6U,  /*!< 4 bit data width capability */
    kSDMMCHOST_Support8BitDataWidth     = 1U << 7U,  /*!< 8 bit data width capability */
    kSDMMCHOST_SupportDDRMode           = 1U << 8U,  /*!< DDR mode capability */
    kSDMMCHOST_SupportDetectCardByData3 = 1U << 9U,  /*!< data3 detect card capability */
    kSDMMCHOST_SupportDetectCardByCD    = 1U << 10U, /*!< CD detect card capability */
    kSDMMCHOST_SupportAutoCmd12         = 1U << 11U, /*!< auto command 12 capability */
    kSDMMCHOST_SupportSDR104            = 1U << 12U, /*!< SDR104 capability */
    kSDMMCHOST_SupportSDR50             = 1U << 13U, /*!< SDR50 capability */
    kSDMMCHOST_SupportHS200             = 1U << 14U, /*!< HS200 capability */
    kSDMMCHOST_SupportHS400             = 1U << 15U, /*!< HS400 capability */
};

/*!@brief host capability */
#define SDMMCHOST_SUPPORT_HIGH_SPEED           (1U)
#define SDMMCHOST_SUPPORT_SUSPEND_RESUME       (1U)
#define SDMMCHOST_SUPPORT_VOLTAGE_3V3          (1U)
#define SDMMCHOST_SUPPORT_VOLTAGE_3V0          (0U)
#define SDMMCHOST_SUPPORT_VOLTAGE_1V8          (0U)
#define SDMMCHOST_SUPPORT_VOLTAGE_1V2          (0U)
#define SDMMCHOST_SUPPORT_4_BIT_WIDTH          (1U)
#define SDMMCHOST_SUPPORT_8_BIT_WIDTH          (1U)
#define SDMMCHOST_SUPPORT_DDR50                (0U)
#define SDMMCHOST_SUPPORT_SDR104               (0U)
#define SDMMCHOST_SUPPORT_SDR50                (0U)
#define SDMMCHOST_SUPPORT_HS200                (0U)
#define SDMMCHOST_SUPPORT_HS400                (0U)
#define SDMMCHOST_SUPPORT_DETECT_CARD_BY_DATA3 (1U)
#define SDMMCHOST_SUPPORT_DETECT_CARD_BY_CD    (1U)
#define SDMMCHOST_SUPPORT_AUTO_CMD12           (1U)
#define SDMMCHOST_SUPPORT_MAX_BLOCK_LENGTH     (SDIF_BLKSIZ_BLOCK_SIZE_MASK)
#define SDMMCHOST_SUPPORT_MAX_BLOCK_COUNT      (SDIF_BYTCNT_BYTE_COUNT_MASK / SDIF_BLKSIZ_BLOCK_SIZE_MASK)
/*! @brief sdmmc host instance capability */
#define SDMMCHOST_INSTANCE_SUPPORT_8_BIT_WIDTH(host) 1U
#define SDMMCHOST_INSTANCE_SUPPORT_HS400(host)       0U
#define SDMMCHOST_INSTANCE_SUPPORT_1V8_SIGNAL(host)  0U
#define SDMMCHOST_INSTANCE_SUPPORT_HS200(host)       0U
#define SDMMCHOST_INSTANCE_SUPPORT_SDR104(host)      0U
#define SDMMCHOST_INSTANCE_SUPPORT_SDR50(host)       0U
#define SDMMCHOST_INSTANCE_SUPPORT_DDR50(host)       0U

/*!@brief SDMMC host dma descriptor buffer address align size */
#define SDMMCHOST_DMA_DESCRIPTOR_BUFFER_ALIGN_SIZE (4U)
/*! @brief SDMMC host reset timoue value */
#define SDMMCHOST_RESET_TIMEOUT_VALUE (1000000U)

/*! @brief host Endian mode
 * corresponding to driver define
 */
enum _sdmmchost_endian_mode
{
    kSDMMCHOST_EndianModeBig         = 0U, /*!< Big endian mode */
    kSDMMCHOST_EndianModeHalfWordBig = 1U, /*!< Half word big endian mode */
    kSDMMCHOST_EndianModeLittle      = 2U, /*!< Little endian mode */
};

/*!@brief sdmmc host transfer function */
typedef sdif_transfer_t sdmmchost_transfer_t;
typedef sdif_command_t sdmmchost_cmd_t;
typedef sdif_data_t sdmmchost_data_t;
typedef struct _sdmmchost_ SDMMCHOST_CONFIG;
typedef SDIF_Type SDMMCHOST_TYPE;
typedef void sdmmchost_detect_card_t;
typedef void sdmmchost_boot_config_t;

/*!@brief sdmmc host handler  */
typedef struct _sdmmchost_
{
    sdif_host_t hostController;    /*!< host configuration */
    uint8_t hostPort;              /*!< host port number, used for one instance support two card */
    void *dmaDesBuffer;            /*!< DMA descriptor buffer address */
    uint32_t dmaDesBufferWordsNum; /*!< DMA descriptor buffer size in byte */
    sdif_handle_t handle;          /*!< host controller handler */

    uint32_t capability;    /*!< host controller capability */
    uint32_t maxBlockCount; /*!< host controller maximum block count */
    uint32_t maxBlockSize;  /*!< host controller maximum block size */

    sdmmc_osa_event_t hostEvent; /*!< host event handler */
    void *cd;                    /*!< card detect */
    void *cardInt;               /*!< call back function for card interrupt */
    sdmmc_osa_mutex_t lock;      /*!< host access lock */
} sdmmchost_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name SDIF host controller function
 * @{
 */

/*!
 * @brief set data bus width.
 * @param host host handler
 * @param dataBusWidth data bus width
 */
void SDMMCHOST_SetCardBusWidth(sdmmchost_t *host, uint32_t dataBusWidth);

/*!
 * @brief Send initilization active 80 clocks to card.
 * @param host host handler
 */
static inline void SDMMCHOST_SendCardActive(sdmmchost_t *host)
{
    SDIF_SendCardActive(host->hostController.base, 100U);
}

/*!
 * @brief Set card bus clock.
 * @param host host handler
 * @param targetClock target clock frequency
 * @retval actual clock frequency can be reach.
 */
static inline uint32_t SDMMCHOST_SetCardClock(sdmmchost_t *host, uint32_t targetClock)
{
    return SDIF_SetCardClock(host->hostController.base, host->hostController.sourceClock_Hz, targetClock);
}

/*!
 * @brief check card status by DATA0.
 * @param host host handler
 * @retval true is busy, false is idle.
 */
static inline bool SDMMCHOST_IsCardBusy(sdmmchost_t *host)
{
    return (SDIF_GetControllerStatus(host->hostController.base) & SDIF_STATUS_DATA_BUSY_MASK) ==
                   SDIF_STATUS_DATA_BUSY_MASK ?
               true :
               false;
}

/*!
 * @brief start read boot data.
 * @param host host handler
 * @param hostConfig boot configuration
 * @param cmd boot command
 * @param buffer buffer address
 */
static inline status_t SDMMCHOST_StartBoot(sdmmchost_t *host,
                                           sdmmchost_boot_config_t *hostConfig,
                                           sdmmchost_cmd_t *cmd,
                                           uint8_t *buffer)
{
    /* host not support */
    return kStatus_Fail;
}

/*!
 * @brief read boot data.
 * @param host host handler
 * @param hostConfig boot configuration
 * @param buffer buffer address
 */
static inline status_t SDMMCHOST_ReadBootData(sdmmchost_t *host, sdmmchost_boot_config_t *hostConfig, uint8_t *buffer)
{
    /* host not support */
    return kStatus_Fail;
}

/*!
 * @brief enable boot mode.
 * @param host host handler
 * @param enable true is enable, false is disable
 */
static inline void SDMMCHOST_EnableBoot(sdmmchost_t *host, bool enable)
{
    /* not support */
}

/*!
 * @brief enable card interrupt.
 * @param host host handler
 * @param enable true is enable, false is disable.
 */
static inline void SDMMCHOST_EnableCardInt(sdmmchost_t *host, bool enable)
{
    if (enable)
    {
        SDIF_EnableInterrupt(host->hostController.base, kSDIF_SDIOInterrupt);
    }
    else
    {
        SDIF_DisableInterrupt(host->hostController.base, kSDIF_SDIOInterrupt);
    }
}

/*!
 * @brief card interrupt function.
 * @param host host handler
 * @param sdioInt card interrupt configuration
 */
status_t SDMMCHOST_CardIntInit(sdmmchost_t *host, void *sdioInt);

/*!
 * @brief card detect init function.
 * @param host host handler
 * @param cd card detect configuration
 */
status_t SDMMCHOST_CardDetectInit(sdmmchost_t *host, void *cd);

/*!
 * @brief Detect card insert, only need for SD cases.
 * @param host host handler
 * @param waitCardStatus status which user want to wait
 * @param timeout wait time out.
 * @retval kStatus_Success detect card insert
 * @retval kStatus_Fail card insert event fail
 */
status_t SDMMCHOST_PollingCardDetectStatus(sdmmchost_t *host, uint32_t waitCardStatus, uint32_t timeout);

/*!
 * @brief card detect status.
 * @param host host handler
 * @retval kSD_Inserted, kSD_Removed
 */
uint32_t SDMMCHOST_CardDetectStatus(sdmmchost_t *host);

/*!
 * @brief Init host controller.
 *
 * Thread safe function, please note that the function will create the mutex lock dynamically by default,
 * so to avoid the mutex create redundantly, application must follow bellow sequence for card re-initialization
 * @code
 * SDMMCHOST_Deinit(host);
 * SDMMCHOST_Init(host);
 * @endcode
 *
 * @param host host handler
 * @retval kStatus_Success host init success
 * @retval kStatus_Fail event fail
 */
status_t SDMMCHOST_Init(sdmmchost_t *host);

/*!
 * @brief Deinit host controller.
 *
 * Please note it is a thread safe function.
 *
 * @param host host handler
 */
void SDMMCHOST_Deinit(sdmmchost_t *host);

/*!
 * @brief host power off card function.
 * @param host host handler
 * @param enable true is power on, false is power down.
 */
void SDMMCHOST_SetCardPower(sdmmchost_t *host, bool enable);

/*!
 * @brief host transfer function.
 *
 * Please note it is a thread safe function.
 *
 * @param host host handler
 * @param content transfer content.
 */
status_t SDMMCHOST_TransferFunction(sdmmchost_t *host, sdmmchost_transfer_t *content);

/*!
 * @brief host reset function.
 *
 * Please note it is a thread safe function.
 *
 * @param host host handler
 */
void SDMMCHOST_Reset(sdmmchost_t *host);

/*!
 * @brief switch to voltage.
 * @param host host handler
 * @param voltage switch to voltage level.
 */
static inline void SDMMCHOST_SwitchToVoltage(sdmmchost_t *host, uint32_t voltage)
{
    /* host not support */
}

/*!
 * @brief sdmmc host excute tuning.
 *
 * @param host host handler
 * @param tuningCmd tuning command.
 * @param revBuf receive buffer pointer
 * @param blockSize tuning data block size.
 */
static inline status_t SDMMCHOST_ExecuteTuning(sdmmchost_t *host,
                                               uint32_t tuningCmd,
                                               uint32_t *revBuf,
                                               uint32_t blockSize)
{
    /* host not support */
    return kStatus_Fail;
}

/*!
 * @brief enable DDR mode.
 * @param host host handler
 * @param enable true is enable, false is disable.
 * @param nibblePos nibble position indictation. 0- the sequence is 'odd high nibble -> even high nibble ->
 * odd low nibble -> even low nibble'; 1- the sequence is 'odd high nibble -> odd low nibble -> even high
 * nibble -> even low nibble'.
 */
static inline void SDMMCHOST_EnableDDRMode(sdmmchost_t *host, bool enable, uint32_t nibblePos)
{
    /* host not support */
}

/*!
 * @brief enable HS400 mode.
 * @param host host handler
 * @param enable true is enable, false is disable.
 */
static inline void SDMMCHOST_EnableHS400Mode(sdmmchost_t *host, bool enable)
{
    /* host not support */
}

/*!
 * @brief enable STROBE DLL.
 * @param host host handler
 * @param enable true is enable, false is disable.
 */
static inline void SDMMCHOST_EnableStrobeDll(sdmmchost_t *host, bool enable)
{
    /* host not support */
}

/*!
 * @brief Get signal line status.
 * @param host host handler
 * @param signalLine signal line type, reference _sdmmc_signal_line
 */
static inline uint32_t SDMMCHOST_GetSignalLineStatus(sdmmchost_t *host, uint32_t signalLine)
{
    /* host not support */
    return 0U;
}

/*!
 * @brief force card clock on.
 * @param host host handler
 * @param enable true is enable, false is disable.
 */
static inline void SDMMCHOST_ForceClockOn(sdmmchost_t *host, bool enable)
{
    /* host not support */
}

/*!
 * @brief sdmmc host convert data sequence to little endian sequence
 *
 * @param host host handler.
 * @param data data buffer address.
 * @param wordSize data buffer size in word.
 * @param format data packet format.
 */
void SDMMCHOST_ConvertDataToLittleEndian(sdmmchost_t *host, uint32_t *data, uint32_t wordSize, uint32_t format);

/* @} */

#if defined(__cplusplus)
}
#endif
/* @} */
#endif /* _FSL_SDMMC_HOST_H */
