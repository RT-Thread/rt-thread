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

#if !defined(__FSL_SMC_HAL_H__)
#define __FSL_SMC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_SMC_COUNT

/*! @addtogroup smc_hal*/
/*! @{*/

/*! @file fsl_smc_hal.h */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Power Modes */
typedef enum _power_modes {
    kPowerModeRun    = 0x01U << 0U,
    kPowerModeWait   = 0x01U << 1U,
    kPowerModeStop   = 0x01U << 2U,
    kPowerModeVlpr   = 0x01U << 3U,
    kPowerModeVlpw   = 0x01U << 4U,
    kPowerModeVlps   = 0x01U << 5U,
    kPowerModeLls    = 0x01U << 6U,
    kPowerModeVlls   = 0x01U << 7U,
    kPowerModeHsrun  = 0x01U << 8U,
    kPowerModeMax    = 0x01U << 9U,
} power_modes_t;

/*!
 * @brief Error code definition for the system mode controller manager APIs.
 */
typedef enum _smc_hal_error_code {
    kSmcHalSuccess,                           /*!< Success */
    kSmcHalNoSuchModeName,                    /*!< Cannot find the mode name specified*/
    kSmcHalAlreadyInTheState,                 /*!< Already in the required state*/
    kSmcHalFailed                             /*!< Unknown error, operation failed*/
} smc_hal_error_code_t;

/*! @brief Power Modes in PMSTAT*/
typedef enum _power_mode_stat {
    kStatRun    = 0x01U,             /*!< 0000_0001 - Current power mode is RUN*/
    kStatStop   = 0x02U,             /*!< 0000_0010 - Current power mode is STOP*/
    kStatVlpr   = 0x04U,             /*!< 0000_0100 - Current power mode is VLPR*/
    kStatVlpw   = 0x08U,             /*!< 0000_1000 - Current power mode is VLPW*/
    kStatVlps   = 0x10U,             /*!< 0001_0000 - Current power mode is VLPS*/
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
    kStatLls    = 0x20U,             /*!< 0010_0000 - Current power mode is LLS*/
#endif
    kStatVlls   = 0x40U,             /*!< 0100_0000 - Current power mode is VLLS*/
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    kStatHsrun  = 0x80U              /*!< 1000_0000 - Current power mode is HSRUN*/
#endif
} power_mode_stat_t;

/*! @brief Power Modes Protection*/
typedef enum _power_modes_protect {
    kAllowPowerModeVlls  = SMC_PMPROT_AVLLS_MASK,   /*!< Allow Very-Low-Leakage Stop Mode*/
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
    kAllowPowerModeLls   = SMC_PMPROT_ALLS_MASK,    /*!< Allow Low-Leakage Stop Mode*/
#endif
    kAllowPowerModeVlp   = SMC_PMPROT_AVLP_MASK,    /*!< Allow Very-Low-Power Modes*/
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    kAllowPowerModeHsrun = SMC_PMPROT_AHSRUN_MASK,  /*!< Allow High Speed Run mode*/
#endif
    kAllowPowerModeAll   = (SMC_PMPROT_AVLLS_MASK  |
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
                            SMC_PMPROT_ALLS_MASK   |
#endif
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
                            SMC_PMPROT_AHSRUN_MASK |
#endif
                            SMC_PMPROT_AVLP_MASK)   /*!< Allow all power modes. */
} power_modes_protect_t;

/*!
 * @brief Run mode definition
 */
typedef enum _smc_run_mode {
    kSmcRun,                                /*!< normal RUN mode*/
    kSmcReservedRun,
    kSmcVlpr,                               /*!< Very-Low-Power RUN mode*/
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    kSmcHsrun                               /*!< High Speed Run mode (HSRUN)*/
#endif
} smc_run_mode_t;

/*!
 * @brief Stop mode definition
 */
typedef enum _smc_stop_mode {
    kSmcStop           = 0U,  /*!< Normal STOP mode*/
    kSmcReservedStop1  = 1U,  /*!< Reserved*/
    kSmcVlps           = 2U,  /*!< Very-Low-Power STOP mode*/
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
    kSmcLls            = 3U,  /*!< Low-Leakage Stop mode*/
#endif
    kSmcVlls           = 4U   /*!< Very-Low-Leakage Stop mode*/
} smc_stop_mode_t;

/*!
 * @brief VLLS/LLS stop sub mode definition
 */
typedef enum _smc_stop_submode {
    kSmcStopSub0,          /*!< Stop submode 0, for VLLS0/LLS0. */
    kSmcStopSub1,          /*!< Stop submode 1, for VLLS1/LLS1. */
    kSmcStopSub2,          /*!< Stop submode 2, for VLLS2/LLS2. */
    kSmcStopSub3           /*!< Stop submode 3, for VLLS3/LLS3. */
} smc_stop_submode_t;

/*! @brief Low Power Wake Up on Interrupt option*/
typedef enum _smc_lpwui_option {
    kSmcLpwuiDisabled,                        /*!< Low Power Wake Up on Interrupt disabled. @internal gui name="Disabled" */
    kSmcLpwuiEnabled                          /*!< Low Power Wake Up on Interrupt enabled. @internal gui name="Enabled" */
} smc_lpwui_option_t;

/*! @brief Partial STOP option*/
typedef enum _smc_pstop_option {
    kSmcPstopStop,                          /*!< STOP - Normal Stop mode*/
    kSmcPstopStop1,                         /*!< Partial Stop with both system and bus clocks disabled*/
    kSmcPstopStop2,                         /*!< Partial Stop with system clock disabled and bus clock enabled*/
    kSmcPstopReserved
} smc_pstop_option_t;

/*! @brief POR option*/
typedef enum _smc_por_option {
    kSmcPorEnabled,                        /*!< POR detect circuit is enabled in VLLS0. @internal gui name="Enabled" */
    kSmcPorDisabled                        /*!< POR detect circuit is disabled in VLLS0. @internal gui name="Disabled" */
} smc_por_option_t;

/*! @brief RAM2 power option*/
typedef enum _smc_ram2_option {
    kSmcRam2DisPowered,                    /*!< RAM2 not powered in LLS2/VLLS2. @internal gui name="Not Powered" */
    kSmcRam2Powered                        /*!< RAM2 powered in LLS2/VLLS2. @internal gui name="Powered" */
} smc_ram2_option_t;

/*! @brief LPO power option*/
typedef enum _smc_lpo_option {
    kSmcLpoEnabled,                        /*!< LPO clock is enabled in LLS/VLLSx. @internal gui name="Enabled" */
    kSmcLpoDisabled                        /*!< LPO clock is disabled in LLS/VLLSx. @internal gui name="Disabled" */
} smc_lpo_option_t;

/*! @brief Power mode control configuration used for calling the SMC_SYS_SetPowerMode API. */
typedef struct _smc_power_mode_config {
    power_modes_t       powerModeName;      /*!< Power mode(enum), see power_modes_t */
    smc_stop_submode_t  stopSubMode;        /*!< Stop submode(enum), see smc_stop_submode_t */
#if FSL_FEATURE_SMC_HAS_LPWUI
    smc_lpwui_option_t  lpwuiOptionValue;   /*!< LPWUI option(enum), see smc_lpwui_option_t */
#endif
#if FSL_FEATURE_SMC_HAS_PORPO
    smc_por_option_t    porOptionValue;     /*!< POR option(enum), see smc_por_option_t */
#endif
#if FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION
    smc_ram2_option_t   ram2OptionValue;    /*!< RAM2 option(enum), see smc_ram2_option_t */
#endif
#if FSL_FEATURE_SMC_HAS_PSTOPO
    smc_pstop_option_t  pstopOptionValue;   /*!< PSTOPO option(enum), see smc_por_option_t */
#endif
#if FSL_FEATURE_SMC_HAS_LPOPO
    smc_lpo_option_t    lpoOptionValue;     /*!< LPOPO option, see smc_lpo_option_t */
#endif
} smc_power_mode_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name System mode controller APIs*/
/*@{*/

/*!
 * @brief Configures the power mode.
 *
 * This function configures the power mode base on configuration structure. If
 * it not possible to switch to the target mode directly, this function checks
 * internally and chooses the right path.
 *
 * @param base  Base address for current SMC instance.
 * @param powerModeConfig Power mode configuration structure smc_power_mode_config_t 
 * @return SMC error code.
 */
smc_hal_error_code_t SMC_HAL_SetMode(SMC_Type * base, 
                                     const smc_power_mode_config_t *powerModeConfig);

/*!
 * @brief Configures all power mode protection settings.
 *
 * This function  configures the power mode protection settings for
 * supported power modes in the specified chip family. The available power modes
 * are defined in the power_modes_protect_t. This should be done at an early
 * system level initialization stage. See the reference manual for details.
 * This register can only write once after the power reset.
 *
 * The allowed modes are passed as bit map, for example, to allow LLS and VLLS,
 * use SMC_HAL_SetProtection(SMC, kAllowPowerModeLls | kAllowPowerModeVlls).
 * To allow all modes, use SMC_HAL_SetProtection(SMC, kAllowPowerModeAll).
 * 
 * @param base  Base address for current SMC instance.
 * @param allowedModes Bitmap of the allowed power modes.
 */
static inline void SMC_HAL_SetProtection(SMC_Type * base, uint8_t allowedModes)
{
    SMC_WR_PMPROT(base, allowedModes);
}

/*!
 * @brief Gets the power mode protection setting.
 *
 * This function checks whether the power modes are allowed. The modes to check
 * are passed as a bit map, for example, to check LLS and VLLS,
 * use SMC_HAL_GetProtection(SMC, kAllowPowerModeLls | kAllowPowerModeVlls).
 * To test all modes, use SMC_HAL_GetProtection(SMC, kAllowPowerModeAll).
 * 
 * @param base  Base address for current SMC instance.
 * @param modes Bitmap of the power modes to check.
 * @return Bitmap of the allowed power modes.
 */
static inline uint8_t SMC_HAL_GetProtection(SMC_Type * base, uint8_t modes)
{
    return (uint8_t)(SMC_RD_PMPROT(base) & modes);
}

#if FSL_FEATURE_SMC_HAS_LPWUI
/*!
 * @brief Configures the LPWUI (Low Power Wake Up on interrupt) option.
 *
 * This function  sets the LPWUI option and cause the system to exit
 * to normal RUN mode when any active interrupt occurs while in a specific lower
 * power mode. See the  smc_lpwui_option_t for supported options and the  
 * reference manual for more details about this option.
 * The function SMC_HAL_SetMode does not affect this bit. To configure it,
 * make sure current power mode is a normal RUN mode.
 *
 * @param base  Base address for current SMC instance.
 * @param option LPWUI option setting defined in smc_lpwui_option_t
 */
static inline void SMC_HAL_SetLpwuiMode(SMC_Type * base, smc_lpwui_option_t option)
{
    SMC_BWR_PMCTRL_LPWUI(base, option);
}
#endif

/*!
 * @brief Checks whether the previous stop mode entry was successful.
 *
 * @param base  Base address for current SMC instance.
 * @return The previous stop mode entry status.
 * @retval true  The previous stop mode entry was aborted.
 * @retval false The previous stop mode entry was successful.
 */
static inline bool SMC_HAL_IsStopAbort(SMC_Type * base)
{
    return (bool)SMC_BRD_PMCTRL_STOPA(base);
}

/*!
 * @brief Gets the current power mode status.
 *
 * This function  returns the current power mode stat. Once application
 * switches the power mode, it should always check the stat to check whether it 
 * runs into the specified mode or not. An application  should  check 
 * this mode before switching to a different mode. The system  requires that
 * only certain modes can switch to other specific modes. See the 
 * reference manual for details and the _power_mode_stat for information about
 * the power stat.
 *
 * @param base  Base address for current SMC instance.
 * @return Current power mode status.
 */
power_mode_stat_t SMC_HAL_GetStat(SMC_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_SMC_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

