/*
 * Copyright 2022, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_POWER_H_
#define _FSL_POWER_H_

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include <stdint.h>

/*!
 * @addtogroup power
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief power driver version 1.0.0. */
#define FSL_POWER_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/* Power mode configuration API parameter */
typedef enum _power_mode_config
{
    kPmu_Sleep          = 0U,
    kPmu_Deep_Sleep     = 1U,
    kPmu_PowerDown      = 2U,
    kPmu_Deep_PowerDown = 3U,
} power_mode_cfg_t;

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief   Configures and enters in SLEEP low power mode
 * @param   :
 * @return  Nothing
 */
void POWER_EnterSleep(void);

/**
 * @brief   Configures and enters in DEEP-SLEEP low power mode
 * @param   exclude_from_pd:
 * @param   sram_retention_ctrl:
 * @param   wakeup_interrupts:
 * @param   hardware_wake_ctrl:

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 0 - CPU0 & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           1 - CPU0 Interrupt Enable registers (NVIC->ISER) are modified by this function. They are restored back in
 case of CPU retention or if POWERDOWN is not taken (for instance because an interrupt is pending).
 *           2 - The Non Maskable Interrupt (NMI) is disabled and its configuration before calling this function will be
 restored back if POWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           3 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset) reset)
 */
void POWER_EnterDeepSleep(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t hardware_wake_ctrl);

/**
 * @brief   Configures and enters in POWERDOWN low power mode
 * @param   exclude_from_pd:
 * @param   sram_retention_ctrl:
 * @param   wakeup_interrupts:
 * @param   cpu_retention_ctrl:  0 = CPU retention is disable / 1 = CPU retention is enabled, all other values are
 RESERVED.

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 0 - CPU0 & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           1 - CPU0 Interrupt Enable registers (NVIC->ISER) are modified by this function. They are restored back in
 case of CPU retention or if POWERDOWN is not taken (for instance because an interrupt is pending).
 *           2 - The Non Maskable Interrupt (NMI) is disabled and its configuration before calling this function will be
 restored back if POWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           3 - In case of CPU retention, it is the responsability of the user to make sure that SRAM instance
 containing the stack used to call this function WILL BE preserved during low power (via parameter
 "sram_retention_ctrl")
 *           4 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset) reset)
 */

void POWER_EnterPowerDown(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t cpu_retention_ctrl);

/**
 * @brief   Configures and enters in DEEPPOWERDOWN low power mode
 * @param   exclude_from_pd:
 * @param   sram_retention_ctrl:
 * @param   wakeup_interrupts:
 * @param   wakeup_io_ctrl:

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 0 - CPU0 & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           1 - CPU0 Interrupt Enable registers (NVIC->ISER) are modified by this function. They are restored back if
 DEEPPOWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           2 - The Non Maskable Interrupt (NMI) is disabled and its configuration before calling this function will be
 restored back if DEEPPOWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           3 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset)
 */
void POWER_EnterDeepPowerDown(uint32_t exclude_from_pd,
                              uint32_t sram_retention_ctrl,
                              uint64_t wakeup_interrupts,
                              uint32_t wakeup_io_ctrl);

/*!
 * @brief Power Library API to choose normal regulation and set the voltage for the desired operating frequency.
 *
 * @param system_freq_hz  - The desired frequency (in Hertz) at which the part would like to operate,
 *                note that the voltage and flash wait states should be set before changing frequency
 * @return none
 */
void POWER_SetVoltageForFreq(uint32_t system_freq_hz);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _FSL_POWER_H_ */
