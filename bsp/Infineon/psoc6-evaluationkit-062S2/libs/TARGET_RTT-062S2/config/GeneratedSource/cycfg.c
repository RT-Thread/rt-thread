/*******************************************************************************
* File Name: cycfg.c
*
* Description:
* Wrapper function to initialize all generated code.
* This file was automatically generated and should not be modified.
* Configurator Backend 3.0.0
* device-db 4.3.0.3855
* mtb-pdl-cat1 3.4.0.24948
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

#include "cycfg.h"

/* This function is provided for compatibility with older 2.X style projects. */
void init_cycfg_all(void)
{
    cycfg_config_init();
    cycfg_config_reservations();
}
void cycfg_config_init(void)
{
    init_cycfg_system();
    init_cycfg_clocks();
    init_cycfg_routing();
    init_cycfg_peripherals();
    init_cycfg_pins();
}
void cycfg_config_reservations(void)
{
    reserve_cycfg_system();
    reserve_cycfg_clocks();
    reserve_cycfg_pins();
}
