/***************************************************************************//**
* \file cyhal_triggers.h
*
* Description:
* Provides definitions for the triggers for each supported device family.
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

/**
* \defgroup group_hal_impl_triggers Trigger Connections
* \ingroup group_hal_impl_interconnect
* \{
* Trigger connections for supported device families:
*
* \addtogroup group_hal_impl_triggers_psoc6_01
* \{
* <b>PSoC™ 6S1 Triggers:</b>
* \image html psoc6able2_trigger_layout.png width=800px
* \}
* \addtogroup group_hal_impl_triggers_psoc6_02
* \{
* <b>PSoC™ 6S2 Triggers:</b>
* \image html psoc6a2m_trigger_layout.png width=800px
* \}
* \addtogroup group_hal_impl_triggers_psoc6_03
* \{
* <b>PSoC™ 6S3 Triggers:</b>
* \image html psoc6a512k_trigger_layout.png width=800px
* \}
* \addtogroup group_hal_impl_triggers_psoc6_04
* \{
* <b>PSoC™ 6S4 Triggers:</b>
* \image html psoc6a256k_trigger_layout.png width=800px
* \}
* \addtogroup group_hal_impl_triggers_xmc7100
* \{
* <b>XMC7100/T2G-B-H-4M Triggers:</b>
* \image html xmc7100_trigger_layout.png width=800px
* \}
* \addtogroup group_hal_impl_triggers_xmc7200
* \{
* <b>XMC7200/T2G-B-H-8M Triggers:</b>
* \image html xmc7200_trigger_layout.png width=800px
* \}
* <p>
*/

#pragma once

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "cy_device.h"

#if defined(CY_DEVICE_PSOC6ABLE2)
#include "triggers/cyhal_triggers_psoc6_01.h"
#elif defined(CY_DEVICE_PSOC6A2M)
#include "triggers/cyhal_triggers_psoc6_02.h"
#elif defined(CY_DEVICE_PSOC6A512K)
#include "triggers/cyhal_triggers_psoc6_03.h"
#elif defined(CY_DEVICE_PSOC6A256K)
#include "triggers/cyhal_triggers_psoc6_04.h"
#elif defined(CY_DEVICE_CYW20829)
#include "triggers/cyhal_triggers_cyw20829.h"
#elif defined(CY_DEVICE_TVIIBH4M)
#include "triggers/cyhal_triggers_xmc7100.h"
#elif defined(CY_DEVICE_TVIIBH8M)
#include "triggers/cyhal_triggers_xmc7200.h"
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_impl_triggers */
