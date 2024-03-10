/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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

#ifndef _FSL_HOST_H
#define _FSL_HOST_H

#include "fsl_common.h"
#include "board.h"
#if defined(FSL_FEATURE_SOC_SDHC_COUNT) && FSL_FEATURE_SOC_SDHC_COUNT > 0U
#include "fsl_sdhc.h"
#elif defined(FSL_FEATURE_SOC_SDIF_COUNT) && FSL_FEATURE_SOC_SDIF_COUNT > 0U
#include "fsl_sdif.h"
#elif defined(FSL_FEATURE_SOC_USDHC_COUNT) && FSL_FEATURE_SOC_USDHC_COUNT > 0U
#include "fsl_usdhc.h"
#include "fsl_iomuxc.h"
#endif

/*!
 * @addtogroup CARD
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define HOST_NOT_SUPPORT 0U /*!< use this define to indicate the host not support feature*/
#define HOST_SUPPORT 1U     /*!< use this define to indicate the host support feature*/
/* select host */
#if defined(FSL_FEATURE_SOC_SDHC_COUNT) && FSL_FEATURE_SOC_SDHC_COUNT > 0U

/* SDR104 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_SDR104_FREQ
#define HOST_SUPPORT_SDR104_FREQ SD_CLOCK_208MHZ
#else
#define HOST_SUPPORT_SDR104_FREQ SD_CLOCK_208MHZ
#endif
/* HS200 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_HS200_FREQ
#define HOST_SUPPORT_HS200_FREQ MMC_CLOCK_HS200
#else
#define HOST_SUPPORT_HS200_FREQ MMC_CLOCK_HS200
#endif
/* HS400 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_HS400_FREQ
#define HOST_SUPPORT_HS400_FREQ BOARD_SD_HOST_SUPPORT_HS400_FREQ /* host do not support HS400 */
#else
#define HOST_SUPPORT_HS400_FREQ MMC_CLOCK_HS400
#endif

/*define host baseaddr ,clk freq, IRQ number*/
#define MMC_HOST_BASEADDR BOARD_SDHC_BASEADDR
#define MMC_HOST_CLK_FREQ BOARD_SDHC_CLK_FREQ
#define MMC_HOST_IRQ BOARD_SDHC_IRQ
#define SD_HOST_BASEADDR BOARD_SDHC_BASEADDR
#define SD_HOST_CLK_FREQ BOARD_SDHC_CLK_FREQ
#define SD_HOST_IRQ BOARD_SDHC_IRQ

/* define for card bus speed/strength cnofig */
#define CARD_BUS_FREQ_50MHZ (0U)
#define CARD_BUS_FREQ_100MHZ0 (0U)
#define CARD_BUS_FREQ_100MHZ1 (0U)
#define CARD_BUS_FREQ_200MHZ (0U)

#define CARD_BUS_STRENGTH_0 (0U)
#define CARD_BUS_STRENGTH_1 (0U)
#define CARD_BUS_STRENGTH_2 (0U)
#define CARD_BUS_STRENGTH_3 (0U)
#define CARD_BUS_STRENGTH_4 (0U)
#define CARD_BUS_STRENGTH_5 (0U)
#define CARD_BUS_STRENGTH_6 (0U)
#define CARD_BUS_STRENGTH_7 (0U)

#define HOST_TYPE SDHC_Type
#define HOST_CONFIG sdhc_host_t
#define HOST_TRANSFER sdhc_transfer_t
#define HOST_COMMAND sdhc_command_t
#define HOST_DATA sdhc_data_t
#define HOST_BUS_WIDTH_TYPE sdhc_data_bus_width_t
#define HOST_CAPABILITY sdhc_capability_t

#define CARD_DATA0_STATUS_MASK kSDHC_Data0LineLevelFlag
#define CARD_DATA0_NOT_BUSY kSDHC_Data0LineLevelFlag
#define CARD_DATA1_STATUS_MASK kSDHC_Data1LineLevelFlag
#define CARD_DATA2_STATUS_MASK kSDHC_Data2LineLevelFlag
#define CARD_DATA3_STATUS_MASK kSDHC_Data3LineLevelFlag

#define kHOST_DATABUSWIDTH1BIT kSDHC_DataBusWidth1Bit /*!< 1-bit mode */
#define kHOST_DATABUSWIDTH4BIT kSDHC_DataBusWidth4Bit /*!< 4-bit mode */
#define kHOST_DATABUSWIDTH8BIT kSDHC_DataBusWidth8Bit /*!< 8-bit mode */

#define HOST_STANDARD_TUNING_START (0U) /*!< standard tuning start point */
#define HOST_TUINIG_STEP (1U)           /*!< standard tuning step */
#define HOST_RETUNING_TIMER_COUNT (4U)  /*!< Re-tuning timer */
#define HOST_TUNING_DELAY_MAX (0x7FU)
#define HOST_RETUNING_REQUEST (1U)

/* function pointer define */
#define HOST_TRANSFER_FUNCTION sdhc_transfer_function_t
#define GET_HOST_CAPABILITY(base, capability) (SDHC_GetCapability(base, capability))
#define GET_HOST_STATUS(base) (SDHC_GetPresentStatusFlags(base))
#define HOST_SET_CARD_CLOCK(base, sourceClock_HZ, busClock_HZ) (SDHC_SetSdClock(base, sourceClock_HZ, busClock_HZ))
#define HOST_SET_CARD_BUS_WIDTH(base, busWidth) (SDHC_SetDataBusWidth(base, busWidth))
#define HOST_SEND_CARD_ACTIVE(base, timeout) (SDHC_SetCardActive(base, timeout))
#define HOST_SWITCH_VOLTAGE180V(base, enable18v)
#define HOST_CONFIG_IO_STRENGTH(speed, strength)
#define HOST_EXECUTE_STANDARD_TUNING_ENABLE(base, flag)
#define HOST_EXECUTE_STANDARD_TUNING_STATUS(base) (0U)
#define HOST_EXECUTE_STANDARD_TUNING_RESULT(base) (1U)
#define HOST_CONFIG_SD_IO(speed, strength)
#define HOST_CONFIG_MMC_IO(speed, strength)
#define HOST_ENABLE_DDR_MODE(base, flag)
#define HOST_FORCE_SDCLOCK_ON(base, enable)
#define HOST_EXECUTE_MANUAL_TUNING_ENABLE(base, flag)
#define HOST_ADJUST_MANUAL_TUNING_DELAY(base, delay)
#define HOST_AUTO_MANUAL_TUNING_ENABLE(base, flag)
#define HOST_ENABLE_CARD_CLOCK(base, enable) (SDHC_EnableSdClock(base, enable))
#define HOST_RESET_TUNING(base, timeout)
#define HOST_EXECUTE_STANDARD_TUNING(base, transfer) (HOST_NotSupport(transfer))
#define HOST_CHECK_TUNING_ERROR(base) (0U)
#define HOST_ADJUST_TUNING_DELAY(base, delay)
#define HOST_AUTO_STANDARD_RETUNING_TIMER(base)
#define HOST_ENABLE_HS400_MODE(base, flag)

/*! @brief SDHC host capability*/
enum _host_capability
{
    kHOST_SupportAdma = kSDHC_SupportAdmaFlag,
    kHOST_SupportHighSpeed = kSDHC_SupportHighSpeedFlag,
    kHOST_SupportDma = kSDHC_SupportDmaFlag,
    kHOST_SupportSuspendResume = kSDHC_SupportSuspendResumeFlag,
    kHOST_SupportV330 = kSDHC_SupportV330Flag,
    kHOST_SupportV300 = HOST_NOT_SUPPORT,
    kHOST_SupportV180 = HOST_NOT_SUPPORT,
    kHOST_Support4BitBusWidth = kSDHC_Support4BitFlag,
    kHOST_Support8BitBusWidth = kSDHC_Support8BitFlag,
    kHOST_SupportDDR50 = HOST_NOT_SUPPORT,
    kHOST_SupportSDR104 = HOST_NOT_SUPPORT,
    kHOST_SupportSDR50 = HOST_NOT_SUPPORT,
    kHOST_SupportHS200 = HOST_NOT_SUPPORT,
    kHOST_SupportHS400 = HOST_NOT_SUPPORT,

};

/* Endian mode. */
#define SDHC_ENDIAN_MODE kSDHC_EndianModeLittle

/* DMA mode */
#define SDHC_DMA_MODE kSDHC_DmaModeAdma2

/* Read/write watermark level. The bigger value indicates DMA has higher read/write performance. */
#define SDHC_READ_WATERMARK_LEVEL (0x80U)
#define SDHC_WRITE_WATERMARK_LEVEL (0x80U)

/* ADMA table length united as word.
 *
 * SD card driver can't support ADMA1 transfer mode currently.
 * One ADMA2 table item occupy two words which can transfer maximum 0xFFFFU bytes one time.
 * The more data to be transferred in one time, the bigger value of SDHC_ADMA_TABLE_WORDS need to be set.
 */
#define SDHC_ADMA_TABLE_WORDS (8U)

#elif defined(FSL_FEATURE_SOC_SDIF_COUNT) && FSL_FEATURE_SOC_SDIF_COUNT > 0U

/* SDR104 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_SDR104_FREQ
#define HOST_SUPPORT_SDR104_FREQ SD_CLOCK_208MHZ
#else
#define HOST_SUPPORT_SDR104_FREQ SD_CLOCK_208MHZ
#endif
/* HS200 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_HS200_FREQ
#define HOST_SUPPORT_HS200_FREQ MMC_CLOCK_HS200
#else
#define HOST_SUPPORT_HS200_FREQ MMC_CLOCK_HS200
#endif
/* HS400 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_HS400_FREQ
#define HOST_SUPPORT_HS400_FREQ BOARD_SD_HOST_SUPPORT_HS400_FREQ /* host do not support HS400 */
#else
#define HOST_SUPPORT_HS400_FREQ MMC_CLOCK_HS400
#endif

/*define host baseaddr ,clk freq, IRQ number*/
#define MMC_HOST_BASEADDR BOARD_SDIF_BASEADDR
#define MMC_HOST_CLK_FREQ BOARD_SDIF_CLK_FREQ
#define MMC_HOST_IRQ BOARD_SDIF_IRQ
#define SD_HOST_BASEADDR BOARD_SDIF_BASEADDR
#define SD_HOST_CLK_FREQ BOARD_SDIF_CLK_FREQ
#define SD_HOST_IRQ BOARD_SDIF_IRQ

/* define for card bus speed/strength cnofig */
#define CARD_BUS_FREQ_50MHZ (0U)
#define CARD_BUS_FREQ_100MHZ0 (0U)
#define CARD_BUS_FREQ_100MHZ1 (0U)
#define CARD_BUS_FREQ_200MHZ (0U)

#define CARD_BUS_STRENGTH_0 (0U)
#define CARD_BUS_STRENGTH_1 (0U)
#define CARD_BUS_STRENGTH_2 (0U)
#define CARD_BUS_STRENGTH_3 (0U)
#define CARD_BUS_STRENGTH_4 (0U)
#define CARD_BUS_STRENGTH_5 (0U)
#define CARD_BUS_STRENGTH_6 (0U)
#define CARD_BUS_STRENGTH_7 (0U)

#define HOST_TYPE SDIF_Type
#define HOST_CONFIG sdif_host_t
#define HOST_TRANSFER sdif_transfer_t
#define HOST_COMMAND sdif_command_t
#define HOST_DATA sdif_data_t
#define HOST_BUS_WIDTH_TYPE sdif_bus_width_t
#define HOST_CAPABILITY sdif_capability_t

#define CARD_DATA0_STATUS_MASK SDIF_STATUS_DATA_BUSY_MASK
#define CARD_DATA0_NOT_BUSY 0U

#define CARD_DATA1_STATUS_MASK (0U)
#define CARD_DATA2_STATUS_MASK (0U)
#define CARD_DATA3_STATUS_MASK (0U)

#define kHOST_DATABUSWIDTH1BIT kSDIF_Bus1BitWidth /*!< 1-bit mode */
#define kHOST_DATABUSWIDTH4BIT kSDIF_Bus4BitWidth /*!< 4-bit mode */
#define kHOST_DATABUSWIDTH8BIT kSDIF_Bus8BitWidth /*!< 8-bit mode */

#define HOST_STANDARD_TUNING_START (0U) /*!< standard tuning start point */
#define HOST_TUINIG_STEP (1U)           /*!< standard tuning step */
#define HOST_RETUNING_TIMER_COUNT (4U)  /*!< Re-tuning timer */
#define HOST_TUNING_DELAY_MAX (0x7FU)
#define HOST_RETUNING_REQUEST (1U)
/* function pointer define */
#define HOST_TRANSFER_FUNCTION sdif_transfer_function_t
#define GET_HOST_CAPABILITY(base, capability) (SDIF_GetCapability(base, capability))
#define GET_HOST_STATUS(base) (SDIF_GetControllerStatus(base))
#define HOST_SET_CARD_CLOCK(base, sourceClock_HZ, busClock_HZ) (SDIF_SetCardClock(base, sourceClock_HZ, busClock_HZ))
#define HOST_SET_CARD_BUS_WIDTH(base, busWidth) (SDIF_SetCardBusWidth(base, busWidth))
#define HOST_SEND_CARD_ACTIVE(base, timeout) (SDIF_SendCardActive(base, timeout))
#define HOST_SWITCH_VOLTAGE180V(base, enable18v)
#define HOST_CONFIG_IO_STRENGTH(speed, strength)
#define HOST_EXECUTE_STANDARD_TUNING_ENABLE(base, flag)
#define HOST_EXECUTE_STANDARD_TUNING_STATUS(base) (0U)
#define HOST_EXECUTE_STANDARD_TUNING_RESULT(base) (1U)
#define HOST_CONFIG_SD_IO(speed, strength)
#define HOST_CONFIG_MMC_IO(speed, strength)
#define HOST_ENABLE_DDR_MODE(base, flag)
#define HOST_FORCE_SDCLOCK_ON(base, enable)
#define HOST_EXECUTE_MANUAL_TUNING_ENABLE(base, flag)
#define HOST_ADJUST_MANUAL_TUNING_DELAY(base, delay)
#define HOST_AUTO_MANUAL_TUNING_ENABLE(base, flag)
#define HOST_ENABLE_CARD_CLOCK(base, enable) (SDIF_EnableCardClock(base, enable))
#define HOST_RESET_TUNING(base, timeout)
#define HOST_EXECUTE_STANDARD_TUNING(base, transfer) (HOST_NotSupport(transfer))
#define HOST_CHECK_TUNING_ERROR(base) (0U)
#define HOST_ADJUST_TUNING_DELAY(base, delay)
#define HOST_AUTO_STANDARD_RETUNING_TIMER(base)
#define HOST_ENABLE_HS400_MODE(base, flag)
/*! @brief SDIF host capability*/
enum _host_capability
{
    kHOST_SupportHighSpeed = kSDIF_SupportHighSpeedFlag,
    kHOST_SupportDma = kSDIF_SupportDmaFlag,
    kHOST_SupportSuspendResume = kSDIF_SupportSuspendResumeFlag,
    kHOST_SupportV330 = kSDIF_SupportV330Flag,
    kHOST_SupportV300 = HOST_NOT_SUPPORT,
    kHOST_SupportV180 = HOST_NOT_SUPPORT,
    kHOST_Support4BitBusWidth = kSDIF_Support4BitFlag,
    kHOST_Support8BitBusWidth = HOST_NOT_SUPPORT, /* mask the 8 bit here,user can change depend on your board */
    kHOST_SupportDDR50 = HOST_NOT_SUPPORT,
    kHOST_SupportSDR104 = HOST_NOT_SUPPORT,
    kHOST_SupportSDR50 = HOST_NOT_SUPPORT,
    kHOST_SupportHS200 = HOST_NOT_SUPPORT,
    kHOST_SupportHS400 = HOST_NOT_SUPPORT,

};

/*! @brief DMA table length united as word
 * One dma table item occupy four words which can transfer maximum 2*8188 bytes in dual DMA mode
 * and 8188 bytes in chain mode
 * The more data to be transferred in one time, the bigger value of SDHC_ADMA_TABLE_WORDS need to be set.
 * user need check the DMA descriptor table lenght if bigger enough.
 */
#define SDIF_DMA_TABLE_WORDS (0x40U)

#elif defined(FSL_FEATURE_SOC_USDHC_COUNT) && FSL_FEATURE_SOC_USDHC_COUNT > 0U
/* SDR104 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_SDR104_FREQ
#define HOST_SUPPORT_SDR104_FREQ BOARD_SD_HOST_SUPPORT_SDR104_FREQ
#else
#define HOST_SUPPORT_SDR104_FREQ SD_CLOCK_208MHZ
#endif
/* HS200 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_HS200_FREQ
#define HOST_SUPPORT_HS200_FREQ BOARD_SD_HOST_SUPPORT_HS200_FREQ
#else
#define HOST_SUPPORT_HS200_FREQ MMC_CLOCK_HS200
#endif
/* HS400 mode freq */
#if defined BOARD_SD_HOST_SUPPORT_HS400_FREQ
#define HOST_SUPPORT_HS400_FREQ BOARD_SD_HOST_SUPPORT_HS400_FREQ
#else
#define HOST_SUPPORT_HS400_FREQ MMC_CLOCK_HS400
#endif

/*define host baseaddr ,clk freq, IRQ number*/
#define MMC_HOST_BASEADDR BOARD_MMC_HOST_BASEADDR
#define MMC_HOST_CLK_FREQ BOARD_MMC_HOST_CLK_FREQ
#define MMC_HOST_IRQ BOARD_MMC_HOST_IRQ
#define SD_HOST_BASEADDR BOARD_SD_HOST_BASEADDR
#define SD_HOST_CLK_FREQ BOARD_SD_HOST_CLK_FREQ
#define SD_HOST_IRQ BOARD_SD_HOST_IRQ

#define HOST_TYPE USDHC_Type
#define HOST_CONFIG usdhc_host_t
#define HOST_TRANSFER usdhc_transfer_t
#define HOST_COMMAND usdhc_command_t
#define HOST_DATA usdhc_data_t

#define CARD_DATA0_STATUS_MASK kUSDHC_Data0LineLevelFlag
#define CARD_DATA1_STATUS_MASK kUSDHC_Data1LineLevelFlag
#define CARD_DATA2_STATUS_MASK kUSDHC_Data2LineLevelFlag
#define CARD_DATA3_STATUS_MASK kUSDHC_Data3LineLevelFlag
#define CARD_DATA0_NOT_BUSY kUSDHC_Data0LineLevelFlag

#define HOST_BUS_WIDTH_TYPE usdhc_data_bus_width_t
#define HOST_CAPABILITY usdhc_capability_t

#define kHOST_DATABUSWIDTH1BIT kUSDHC_DataBusWidth1Bit /*!< 1-bit mode */
#define kHOST_DATABUSWIDTH4BIT kUSDHC_DataBusWidth4Bit /*!< 4-bit mode */
#define kHOST_DATABUSWIDTH8BIT kUSDHC_DataBusWidth8Bit /*!< 8-bit mode */

#define HOST_STANDARD_TUNING_START (10U) /*!< standard tuning start point */
#define HOST_TUINIG_STEP (2U)            /*!< standard tuning step */
#define HOST_RETUNING_TIMER_COUNT (0U)   /*!< Re-tuning timer */
#define HOST_TUNING_DELAY_MAX (0x7FU)
#define HOST_RETUNING_REQUEST kStatus_USDHC_ReTuningRequest

/* define for card bus speed/strength cnofig */
#define CARD_BUS_FREQ_50MHZ (0U)
#define CARD_BUS_FREQ_100MHZ0 (1U)
#define CARD_BUS_FREQ_100MHZ1 (2U)
#define CARD_BUS_FREQ_200MHZ (3U)

#define CARD_BUS_STRENGTH_0 (0U)
#define CARD_BUS_STRENGTH_1 (1U)
#define CARD_BUS_STRENGTH_2 (2U)
#define CARD_BUS_STRENGTH_3 (3U)
#define CARD_BUS_STRENGTH_4 (4U)
#define CARD_BUS_STRENGTH_5 (5U)
#define CARD_BUS_STRENGTH_6 (6U)
#define CARD_BUS_STRENGTH_7 (7U)

/* function pointer define */
#define HOST_TRANSFER_FUNCTION usdhc_transfer_function_t
#define GET_HOST_CAPABILITY(base, capability) (USDHC_GetCapability(base, capability))
#define GET_HOST_STATUS(base) (USDHC_GetPresentStatusFlags(base))
#define HOST_SET_CARD_CLOCK(base, sourceClock_HZ, busClock_HZ) (USDHC_SetSdClock(base, sourceClock_HZ, busClock_HZ))
#define HOST_ENABLE_CARD_CLOCK(base, enable) (USDHC_EnableSdClock(base, enable))
#define HOST_FORCE_SDCLOCK_ON(base, enable) (USDHC_ForceClockOn(base, enable))
#define HOST_SET_CARD_BUS_WIDTH(base, busWidth) (USDHC_SetDataBusWidth(base, busWidth))
#define HOST_SEND_CARD_ACTIVE(base, timeout) (USDHC_SetCardActive(base, timeout))
#define HOST_SWITCH_VOLTAGE180V(base, enable18v) (UDSHC_SelectVoltage(base, enable18v))
#define HOST_CONFIG_SD_IO(speed, strength) BOARD_SD_PIN_CONFIG(speed, strength)
#define HOST_CONFIG_MMC_IO(speed, strength) BOARD_MMC_PIN_CONFIG(speed, strength)

#define HOST_EXECUTE_STANDARD_TUNING_ENABLE(base, flag) \
    (USDHC_EnableStandardTuning(base, HOST_STANDARD_TUNING_START, HOST_TUINIG_STEP, flag))
#define HOST_EXECUTE_STANDARD_TUNING_STATUS(base) (USDHC_GetExecuteStdTuningStatus(base))
#define HOST_EXECUTE_STANDARD_TUNING_RESULT(base) (USDHC_CheckStdTuningResult(base))
#define HOST_AUTO_STANDARD_RETUNING_TIMER(base) (USDHC_SetRetuningTimer(base, HOST_RETUNING_TIMER_COUNT))
#define HOST_AUTO_TUNING_CONFIG(base) (USDHC_EnableAutoTuningForCmdAndData(base))
#define HOST_EXECUTE_MANUAL_TUNING_ENABLE(base, flag) (USDHC_EnableManualTuning(base, flag))

#define HOST_ADJUST_TUNING_DELAY(base, delay) (USDHC_AdjustDelayForManualTuning(base, delay))
#define HOST_AUTO_MANUAL_TUNING_ENABLE(base, flag) (USDHC_EnableAutoTuningForManualTuning(base, flag))
#define HOST_RESET_TUNING(base, timeout)                                                           \
    {                                                                                              \
        HOST_EXECUTE_MANUAL_TUNING_ENABLE(base, false);                                            \
        (USDHC_Reset(base, kUSDHC_ResetTuning | kUSDHC_ResetData | kUSDHC_ResetCommand, timeout)); \
    }

#define HOST_ENABLE_DDR_MODE(base, flag) (USDHC_EnableDDRMode(base, flag, 1U))

#if FSL_FEATURE_USDHC_HAS_HS400_MODE
#define HOST_ENABLE_HS400_MODE(base, flag) (USDHC_EnableHS400Mode(base, flag))
#else
#define HOST_ENABLE_HS400_MODE(base, flag)
#endif

#define HOST_EXECUTE_STANDARD_TUNING(base, transfer) (USDHC_ExecuteStdTuning(base, transfer))
#define HOST_CHECK_TUNING_ERROR(base) (USDHC_CheckTuningError(base))
/*! @brief USDHC host capability*/
enum _host_capability
{
    kHOST_SupportAdma = kUSDHC_SupportAdmaFlag,
    kHOST_SupportHighSpeed = kUSDHC_SupportHighSpeedFlag,
    kHOST_SupportDma = kUSDHC_SupportDmaFlag,
    kHOST_SupportSuspendResume = kUSDHC_SupportSuspendResumeFlag,
    kHOST_SupportV330 = kUSDHC_SupportV330Flag,
    kHOST_SupportV300 = kUSDHC_SupportV300Flag,
    kHOST_SupportV180 = kUSDHC_SupportV180Flag,
    kHOST_Support4BitBusWidth = kUSDHC_Support4BitFlag,
    kHOST_Support8BitBusWidth = kUSDHC_Support8BitFlag,
    kHOST_SupportDDR50 = kUSDHC_SupportDDR50Flag,
    kHOST_SupportSDR104 = kUSDHC_SupportSDR104Flag,
    kHOST_SupportSDR50 = kUSDHC_SupportSDR50Flag,
    kHOST_SupportHS200 = kUSDHC_SupportSDR104Flag,
#if FSL_FEATURE_USDHC_HAS_HS400_MODE
    kHOST_SupportHS400 = HOST_SUPPORT
#else
    kHOST_SupportHS400 = HOST_NOT_SUPPORT,
#endif
};

/* Endian mode. */
#define USDHC_ENDIAN_MODE kUSDHC_EndianModeLittle

/* DMA mode */
#define USDHC_DMA_MODE kUSDHC_DmaModeAdma2

/* Read/write watermark level. The bigger value indicates DMA has higher read/write performance. */
#define USDHC_READ_WATERMARK_LEVEL (0x80U)
#define USDHC_WRITE_WATERMARK_LEVEL (0x80U)

/* ADMA table length united as word.
 *
 * One ADMA2 table item occupy two words which can transfer maximum 0xFFFFU bytes one time.
 * The more data to be transferred in one time, the bigger value of SDHC_ADMA_TABLE_WORDS need to be set.
 */
#define USDHC_ADMA_TABLE_WORDS (8U)

#define USDHC_READ_BURST_LEN (8U)  /*!< number of words USDHC read in a single burst */
#define USDHC_WRITE_BURST_LEN (8U) /*!< number of words USDHC write in a single burst */
#define USDHC_DATA_TIMEOUT (0xFU)  /*!< data timeout counter value */

#endif

/*! @brief host Endian mode
* corresponding to driver define
*/
enum _host_endian_mode
{
    kHOST_EndianModeBig = 0U,         /*!< Big endian mode */
    kHOST_EndianModeHalfWordBig = 1U, /*!< Half word big endian mode */
    kHOST_EndianModeLittle = 2U,      /*!< Little endian mode */
};

#define EVENT_TIMEOUT_TRANSFER_COMPLETE (1000U)
#define EVENT_TIMEOUT_CARD_DETECT (~0U)

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name adaptor function
 * @{
 */

/*!
 * @brief host not support function, this function is used for host not support feature
 * @param  void parameter ,used to avoid build warning
 * @retval kStatus_Fail ,host do not suppport
 */
static inline status_t HOST_NotSupport(void *parameter)
{
    parameter = parameter;
    return kStatus_Success;
}

/*!
 * @brief Detect card insert, only need for SD cases.
 * @param hostBase the pointer to host base address
 * @retval kStatus_Success detect card insert
 * @retval kStatus_Fail card insert event fail
 */
status_t CardInsertDetect(HOST_TYPE *hostBase);

/*!
 * @brief Init host controller.
 * @param host the pointer to host structure in card structure.
 * @retval kStatus_Success host init success
 * @retval kStatus_Fail event fail
 */
status_t HOST_Init(void *host);

/*!
 * @brief Deinit host controller.
 * @param host the pointer to host structure in card structure.
 */
void HOST_Deinit(void *host);

/* @} */

#if defined(__cplusplus)
}
#endif

#endif
