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
#if !defined(__FSL_RCM_HAL_H__)
#define __FSL_RCM_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_RCM_COUNT

/*! @addtogroup rcm_hal*/
/*! @{*/

/*! @file fsl_rcm_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief System Reset Source Name definitions */
typedef enum _rcm_source_names {
    kRcmSrcAll         = 0U,                           /*!< Parameter could get all reset flags */
    kRcmWakeup         = RCM_SRS0_WAKEUP_MASK,         /*!< Low-leakage wakeup reset */
    kRcmLowVoltDetect  = RCM_SRS0_LVD_MASK,            /*!< low voltage detect reset */
#if FSL_FEATURE_RCM_HAS_LOC
    kRcmLossOfClk      = RCM_SRS0_LOC_MASK,            /*!< Loss of clock reset */
#endif
#if FSL_FEATURE_RCM_HAS_LOL
    kRcmLossOfLock     = RCM_SRS0_LOL_MASK,            /*!< Loss of lock reset */
#endif
    kRcmWatchDog       = RCM_SRS0_WDOG_MASK,           /*!< Watchdog reset */
    kRcmExternalPin    = RCM_SRS0_PIN_MASK,            /*!< External pin reset */
    kRcmPowerOn        = RCM_SRS0_POR_MASK,            /*!< Power on reset */
#if FSL_FEATURE_RCM_HAS_JTAG
    kRcmJtag           = RCM_SRS1_JTAG_MASK    << 8U,  /*!< JTAG generated reset */
#endif
    kRcmCoreLockup     = RCM_SRS1_LOCKUP_MASK  << 8U,  /*!< Core lockup reset */
    kRcmSoftware       = RCM_SRS1_SW_MASK      << 8U,  /*!< Software reset */
    kRcmMdmAp          = RCM_SRS1_MDM_AP_MASK  << 8U,  /*!< MDM-AP system reset */
#if FSL_FEATURE_RCM_HAS_EZPORT
    kRcmEzport         = RCM_SRS1_EZPT_MASK    << 8U,  /*!< EzPort reset */
#endif
    kRcmStopModeAckErr = RCM_SRS1_SACKERR_MASK << 8U,  /*!< Stop mode ACK error reset */
} rcm_source_names_t;

/*! @brief Reset pin filter select in Run and Wait modes */
typedef enum _rcm_filter_run_wait_modes {
    kRcmFilterDisabled,          /*!< All filtering disabled */
    kRcmFilterBusClk,            /*!< Bus clock filter enabled */
    kRcmFilterLpoClk,            /*!< LPO clock filter enabled */
    kRcmFilterReserverd          /*!< Reserved setting */
} rcm_filter_run_wait_modes_t;

#if FSL_FEATURE_RCM_HAS_BOOTROM
/*! @brief Boot from ROM configuration. */
typedef enum _rcm_boot_rom_config {
    kRcmBootFlash,       /*!< Boot from flash */
    kRcmBootRomCfg0,     /*!< Boot from boot ROM due to BOOTCFG0 */
    kRcmBootRomFopt,     /*!< Boot from boot ROM due to FOPT[7] */
    kRcmBootRomBoth      /*!< Boot from boot ROM due to both BOOTCFG0 and FOPT[7] */
} rcm_boot_rom_config_t;
#endif

/*! @brief Reset pin filter configuration. */
typedef struct _rcm_reset_pin_filter_config
{
    bool filterInStop;                        /*!< Reset pin filter select in stop mode. */
    rcm_filter_run_wait_modes_t filterInRunWait; /*!< Reset pin filter in run/wait mode. */
    uint8_t busClockFilterCount;                 /*!< Reset pin bus clock filter width.  */
} rcm_reset_pin_filter_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name Reset Control Module APIs*/
/*@{*/

/*!
 * @brief Gets the reset source status.
 *
 * This function gets the current reset source status for a specified source.
 *
 * Example:
   @code
   uint32_t resetStatus;

   // To get all reset source statuses.
   resetStatus = RCM_HAL_GetSrcStatus(RCM, kRcmSrcAll);

   // To test whether MCU is reset by watchdog.
   resetStatus = RCM_HAL_GetSrcStatus(RCM, kRcmWatchDog);

   // To test multiple reset source.
   resetStatus = RCM_HAL_GetSrcStatus(RCM, kRcmWatchDog | kRcmSoftware);
   @endcode
 *
 * @param base     Register base address of RCM
 * @param statusMask Bit mask for the reset sources to get.
 * @return The reset source status.
 */
uint32_t RCM_HAL_GetSrcStatus(RCM_Type * base, uint32_t statusMask);

#if FSL_FEATURE_RCM_HAS_SSRS
/*!
 * @brief Gets the sticky reset source status.
 *
 * This function gets the current reset source status that was not cleared
 * by software for a specified source.
 *
 * @param base     Register base address of RCM
 * @param statusMask Bit mask for the reset sources to get.
 * @return The reset source status.
 */
uint32_t RCM_HAL_GetStickySrcStatus(RCM_Type * base, uint32_t statusMask);

/*!
 * @brief Clears the sticky reset source status.
 *
 * This function clears all sticky system reset flags.
 *
 * @param base     Register base address of RCM
 */
void RCM_HAL_ClearStickySrcStatus(RCM_Type * base);
#endif

/*!
 * @brief Sets the reset pin filter base on configuration.
 *
 * This function sets the reset pin filter, including filter source, filter
 * width, and so on.
 *
 * @param base   Register base address of RCM
 * @param config Pointer to the configuration structure.
 */
void RCM_HAL_SetResetPinFilterConfig(RCM_Type * base, rcm_reset_pin_filter_config_t *config);

#if FSL_FEATURE_RCM_HAS_EZPMS
/*!
 * @brief Gets the EZP_MS_B pin assert status.
 *
 * This function gets the easy port mode status (EZP_MS_B) pin assert status.
 *
 * @param base     Register base address of RCM
 * @return status  true - asserted, false - reasserted
 */
static inline bool RCM_HAL_GetEasyPortModeStatus(RCM_Type * base)
{
    return (bool)RCM_BRD_MR_EZP_MS(base);
}
#endif

#if FSL_FEATURE_RCM_HAS_BOOTROM
/*!
 * @brief Forces the boot from ROM.
 *
 * This function forces boot from ROM during all subsequent system resets.
 *
 * @param base     Register base address of RCM
 * @param config       Boot configuration.
 */
static inline void RCM_HAL_SetForceBootRomSrc(RCM_Type * base,
                                              rcm_boot_rom_config_t config)
{
    RCM_BWR_FM_FORCEROM(base, config);
}

/*!
 * @brief Gets the ROM boot source.
 *
 * This function gets the ROM boot source during the last chip reset.
 *
 * @param base     Register base address of RCM
 * @return The ROM boot source.
 */
static inline rcm_boot_rom_config_t RCM_HAL_GetBootRomSrc(RCM_Type * base)
{
    return (rcm_boot_rom_config_t)RCM_BRD_MR_BOOTROM(base);
}

/*!
 * @brief Clears the ROM boot source flag.
 *
 * This function clears the ROM boot source flag.
 *
 * @param base     Register base address of RCM
 */
static inline void RCM_HAL_ClearBootRomSrc(RCM_Type * base)
{
    RCM_BWR_MR_BOOTROM(base, kRcmBootRomBoth);
}
#endif

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_RCM_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

