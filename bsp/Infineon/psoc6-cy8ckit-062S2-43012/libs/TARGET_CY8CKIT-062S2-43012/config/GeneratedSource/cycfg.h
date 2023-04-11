/*******************************************************************************
* File Name: cycfg.h
*
* Description:
* Simple wrapper header containing all generated files.
* This file was automatically generated and should not be modified.
* Configurator Backend 3.0.0
* device-db 4.1.0.3437
* mtb-pdl-cat1 3.3.0.21979
*
********************************************************************************
* Copyright 2023 Cypress Semiconductor Corporation (an Infineon company) or
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
********************************************************************************/

#if !defined(CYCFG_H)
#define CYCFG_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "cycfg_notices.h"
#include "cycfg_system.h"
#include "cycfg_connectivity_bt.h"
#include "cycfg_clocks.h"
#include "cycfg_routing.h"
#include "cycfg_peripherals.h"
#include "cycfg_pins.h"

void init_cycfg_all(void);
void cycfg_config_init(void);
void cycfg_config_reservations(void);


#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_H */
