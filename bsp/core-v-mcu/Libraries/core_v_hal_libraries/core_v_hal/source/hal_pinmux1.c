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
 * Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

/* Driver to control and configure pad mux */

#include <stdint.h>
#include <assert.h>
#include <hal_pinmux1.h>
#include <pulp_io.h>
#include "core-v-mcu-pulp-mem-map.h"
#include "hal_apb_soc.h"

/* TODO: we only support pin 0-31 */

int pinmux_pin_set(int pin, uint32_t func)
{
	assert(0 <= pin && pin < 32);

	uintptr_t padfun_reg =
		((pin & 0xf) >> 4) * 4 +
		(PULP_APB_SOC_CTRL_ADDR + APB_SOC_PADFUN0_OFFSET);
	uint32_t padfun_shift = (pin & 0x7) << 1; /* 16 pads a 2 bits per reg */
	writew((func & 0x3) << padfun_shift, padfun_reg);

	return 0;
}

int pinmux_pin_get(int pin, uint32_t *func)
{
	assert(0 <= pin && pin < 32);

	uintptr_t padfun_reg =
		((pin & 0xf) >> 4) * 4 +
		(PULP_APB_SOC_CTRL_ADDR + APB_SOC_PADFUN0_OFFSET);
	uint32_t padfun_shift = (pin & 0x7) << 1; /* 16 pads a 2 bits per reg */
	uint32_t padfunval = readw(padfun_reg);
	*func = (padfunval >> padfun_shift) & 0x3;
	return 0;
}
