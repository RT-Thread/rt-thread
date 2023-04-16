/***************************************************************************//**
* \file cyhal_syspm_impl.h
*
* \brief
* Provides a PSoC™ Specific interface for interacting with the Infineon power
* management and system clock configuration. This interface abstracts out the
* chip specific details. If any chip specific functionality is necessary, or
* performance is critical the low level functions can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#if defined(COMPONENT_CAT1)
/**
* \addtogroup group_hal_impl_syspm System Power Management
* \ingroup group_hal_impl
* \{
* On CAT1 devices, the Pin based Hibernate wakeup sources (\ref CYHAL_SYSPM_HIBERNATE_PINA_LOW,
* \ref CYHAL_SYSPM_HIBERNATE_PINA_HIGH, \ref CYHAL_SYSPM_HIBERNATE_PINB_LOW, and \ref
* CYHAL_SYSPM_HIBERNATE_PINB_HIGH) are mapped to datsheet capabilities as follows:<br>
* PINA = hibernate_wakeup[0]<br>
* PINB = hibernate_wakeup[1]
*
* The CAT1 (PSoC™ 6) Power Management has the following characteristics:<br>
* \ref CYHAL_SYSPM_SYSTEM_NORMAL equates to the Low Power mode<br>
* \ref CYHAL_SYSPM_SYSTEM_LOW equates to the Ultra Low Power mode
*
* \section group_hal_impl_syspm_ulp Switching the System into Ultra Low Power
* Before switching into system Ultra Low Power mode, ensure that the device meets
* the requirements below:
*
* * The core regulator voltage is set to <b>0.9 V (nominal)</b> and the
* following limitations must be meet:
* * The maximum operating frequency for all Clk_HF paths must not exceed
* <b>50* MHz</b>
* * The maximum operating frequency for peripheral and slow clock must not exceed
* <b>25* MHz</b>.
* * The total current consumption must be less than or equal to <b>20* mA</b>
* * Flash write operations are prohibited. Flash is Read-only in this mode.
*
* \note * - Numbers shown are approximate and real limit values may be
* different because they are device specific. You should refer to the device
* datasheet for exact values of maximum frequency and current in system
* ULP mode.
* \} group_hal_impl_syspm
*/
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \cond INTERNAL
*/

void _cyhal_syspm_register_peripheral_callback(cyhal_syspm_callback_data_t *callback_data);
void _cyhal_syspm_unregister_peripheral_callback(cyhal_syspm_callback_data_t *callback_data);

cy_rslt_t cyhal_syspm_tickless_sleep_deepsleep(cyhal_lptimer_t *obj, uint32_t desired_ms, uint32_t *actual_ms, bool deep_sleep);

#define cyhal_syspm_tickless_deepsleep(obj, desired_ms, actual_ms) cyhal_syspm_tickless_sleep_deepsleep(obj, desired_ms, actual_ms, true)

#define cyhal_syspm_tickless_sleep(obj, desired_ms, actual_ms) cyhal_syspm_tickless_sleep_deepsleep(obj, desired_ms, actual_ms, false)


#if defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) || defined(COMPONENT_CAT1C)
#define cyhal_syspm_sleep()              Cy_SysPm_CpuEnterSleep(CY_SYSPM_WAIT_FOR_INTERRUPT)
#if defined(COMPONENT_CAT1A)
#define cyhal_syspm_get_system_state()   (Cy_SysPm_IsSystemUlp() ? CYHAL_SYSPM_SYSTEM_LOW : CYHAL_SYSPM_SYSTEM_NORMAL)
#elif defined(COMPONENT_CAT1B)
#define cyhal_syspm_get_system_state()   (Cy_SysPm_IsSystemLpActiveEnabled() ? CYHAL_SYSPM_SYSTEM_LOW : CYHAL_SYSPM_SYSTEM_NORMAL)
#elif defined(COMPONENT_CAT1C)
#define cyhal_syspm_get_system_state()   (CYHAL_SYSPM_SYSTEM_NORMAL)
#endif
#elif defined(COMPONENT_CAT2) /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */
#define cyhal_syspm_sleep()              Cy_SysPm_CpuEnterSleep()
#define cyhal_syspm_get_system_state()   (CYHAL_SYSPM_SYSTEM_NORMAL)
#endif /* defined(COMPONENT_CAT1A) || defined(COMPONENT_CAT1B) */

/** \endcond */

#if defined(__cplusplus)
}
#endif
