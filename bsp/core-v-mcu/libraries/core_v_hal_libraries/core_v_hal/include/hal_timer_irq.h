/*
 * Copyright (C) 2019 ETH Zurich and University of Bologna
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

/* Author: Robert Balas (balasr@iis.ee.ethz.ch) */

#ifndef HAL_INCLUDE_HAL_TIMER_IRQ_H_
#define HAL_INCLUDE_HAL_TIMER_IRQ_H_

#include <stdint.h>

int timer_irq_init(uint32_t ticks);

int timer_irq_set_timeout(uint32_t ticks, bool idle);

uint32_t timer_irq_clock_elapsed();

uint32_t timer_irq_cycle_get_32();


#endif /* HAL_INCLUDE_HAL_TIMER_IRQ_H_ */
