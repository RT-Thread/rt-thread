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
 */

/* Driver to control and configure the PULP event unit */
/* Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

#include <pulp_io.h>
#include <stdint.h>
#include "core-v-mcu-config.h"
#include "core-v-mcu-memory-map.h" //ToDo: this should be merged into config.h
#include "hal_soc_eu.h"

void soc_eu_mask_set(uint32_t offset, uint32_t mask)
{
	writew(mask, (uintptr_t)(SOC_EU_ADDR + offset));
}

uint32_t soc_eu_mask_get(uint32_t offset)
{
	return readw((uintptr_t)(SOC_EU_ADDR + offset));
}

void pulp_soc_eu_event_init()
{
	/* deactivate all soc events */
	for (int i = 0; i < SOC_NB_EVENT_REGS; i++) {
		soc_eu_mask_set(SOC_FC_FIRST_MASK + i * 4, 0xffffffff);
	}
}
