/*******************************************************************************
 * File Name: cycfg_routing.h
 *
 * Description:
 * Establishes all necessary connections between hardware elements.
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.20.0
 * device-db 4.15.0.5746
 * mtb-pdl-cat1 3.10.0.32115
 *
 *******************************************************************************
 * Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
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
 ******************************************************************************/

#if !defined(CYCFG_ROUTING_H)
#define CYCFG_ROUTING_H

#include "cycfg_notices.h"

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define ioss_0_port_21_pin_0_ANALOG P21_0_SRSS_WCO_IN
#define ioss_0_port_21_pin_1_ANALOG P21_1_SRSS_WCO_OUT
#define ioss_0_port_21_pin_2_ANALOG P21_2_SRSS_ECO_IN
#define ioss_0_port_21_pin_3_ANALOG P21_3_SRSS_ECO_OUT
#define ioss_0_port_23_pin_4_HSIOM P23_4_CPUSS_SWJ_SWO_TDO
#define ioss_0_port_23_pin_5_HSIOM P23_5_CPUSS_SWJ_SWCLK_TCLK
#define ioss_0_port_23_pin_6_HSIOM P23_6_CPUSS_SWJ_SWDIO_TMS

static inline void init_cycfg_routing(void) {}

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_ROUTING_H */
