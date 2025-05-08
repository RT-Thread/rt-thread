/***********************************************************************************************//**
 * \file cybsp_hw_config.h
 *
 * \brief
 * Basic API for handling defaults for hardware so code examples behave the same across different
 * devices.
 *
 ***************************************************************************************************
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
 **************************************************************************************************/
#pragma once

#include "cy_result.h"
#include "cybsp_types.h"
#include "cycfg_pins.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef CYBSP_USER_BTN_DRIVE
#define CYBSP_USER_BTN_DRIVE          (CYHAL_GPIO_DRIVE_PULLUP)
#endif

#ifndef CYBSP_DEBUG_UART_CTS
#define CYBSP_DEBUG_UART_CTS (NC)
#endif
#ifndef CYBSP_DEBUG_UART_RTS
#define CYBSP_DEBUG_UART_RTS (NC)
#endif

#if defined(__cplusplus)
}
#endif
