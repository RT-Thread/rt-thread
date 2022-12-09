/*
 * Copyright 2021 QuickLogic
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

#include <stdint.h>

#ifndef HAL_INCLUDE_HAL_PINMUX_H_
#define HAL_INCLUDE_HAL_PINMUX_H_

void hal_setpullup(uint8_t io_num, uint8_t on);
void hal_setpinmux(uint8_t io_num, uint8_t mux_sel);
uint8_t hal_getpinmux(uint8_t io_num);

#endif /* HAL_INCLUDE_HAL_PINMUX_H_ */
