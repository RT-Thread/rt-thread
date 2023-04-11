/***********************************************************************************************//**
 * \copyright
 * Copyright 2020-2022 Cypress Semiconductor Corporation (an Infineon company) or
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
 **************************************************************************************************/

#if defined(COMPONENT_WICED_BLE)

#include "cybsp_bt_config.h"

const cybt_platform_config_t cybsp_bt_platform_cfg =
{
    .hci_config                             =
    {
        .hci_transport                      = CYBT_HCI_IPC,
    },

    .controller_config                      =
    {
        .sleep_mode                         = { .sleep_mode_enabled = 1 },
    }
};

#endif /* defined(COMPONENT_WICED_BLE) */
