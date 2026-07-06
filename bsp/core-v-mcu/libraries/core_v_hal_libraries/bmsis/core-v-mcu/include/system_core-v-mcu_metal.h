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

#ifndef __SYSTEM_PULPISSIMO_RI5CY_METAL_H
#define __SYSTEM_PULPISSIMO_RI5CY_METAL_H

#include <stdint.h>
#include <stdbool.h>

/* PULPissimo defs */
#define PULPISSIMO

#define ARCHI_FPGA_FREQUENCY 5000000

#define ARCHI_REF_CLOCK_LOG2 15
#define ARCHI_REF_CLOCK	     (1 << ARCHI_REF_CLOCK_LOG2)

/* hardware modules */
#define ARCHI_NUM_TIMER 1
#define ARCHI_NUM_FLL 2

/* TODO: clean up those macros */
#define ARCHI_FPGA_FREQUENCY 5000000

#define ARCHI_REF_CLOCK_LOG2 15
#define ARCHI_REF_CLOCK	     (1 << ARCHI_REF_CLOCK_LOG2)

#define ARCHI_NB_FLL	  2
#define RT_FREQ_NB_DOMAIN 2

#define __RT_FLL_CL	2
#define __RT_FLL_PERIPH 1
#define __RT_FLL_FC	0

#define __RT_FREQ_DOMAIN_FC	0
#define __RT_FREQ_DOMAIN_CL	2
#define __RT_FREQ_DOMAIN_PERIPH 1
#define RT_FREQ_NB_DOMAIN	2

extern volatile uint32_t system_core_clock;

void pulp_sys_init (void);
void system_core_clock_update (void);

#endif  /* __SYSTEM_PULPISSIMO_RI5CY_H */
