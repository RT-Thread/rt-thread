#ifndef HAL_INCLUDE_HAL_PINMUX1_H_
#define HAL_INCLUDE_HAL_PINMUX1_H_

/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna
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
 */

/* Driver to control and configure pad mux */

/* Author: Robert Balas (balasr@iis.ee.ethz.ch) */

#include <stdint.h>
#include "pulp_io.h"
#include "hal_apb_soc.h"
#include "core-v-mcu-pulp-mem-map.h"

#define PINMUX_FUNC_A 0
#define PINMUX_FUNC_B 1
#define PINMUX_FUNC_C 2
#define PINMUX_FUNC_D 3
/* This doesn't exist on PULP */
#define PINMUX_FUNC_E 4
#define PINMUX_FUNC_F 5
#define PINMUX_FUNC_G 6
#define PINMUX_FUNC_H 7

int pinmux_pin_set(int pin, uint32_t func);

int pinmux_pin_get(int pin, uint32_t *func);


#endif /* HAL_INCLUDE_HAL_PINMUX1_H_ */
