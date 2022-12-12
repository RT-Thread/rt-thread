/*
 * Copyright 2020 ETH Zurich
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
 *
 * SPDX-License-Identifier: Apache-2.0
 * Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

/* Description: Platform system level functions */

#ifndef _CORE_V_MCU_SYSTEM_H
#define _CORE_V_MCU_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

extern volatile uint32_t system_core_clock;

void system_init (void);
void system_core_clock_update (void);

#endif  /* _CORE_V_MCU_SYSTEM_H */
