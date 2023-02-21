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

/* Driver to configure PULP timer as periodic interrupt source */
/* Author: Robert Balas (balasr@iis.ee.ethz.ch)
 *         Germain Haugou (germain.haugou@iis.ee.ethz.ch)
*/

#include <bits.h>
#include <pulp_io.h>
#include <stdint.h>
#include <stdbool.h>
#include "core-v-mcu-pulp-mem-map.h"
#include "hal_timer.h"
#include "hal_timer_irq.h"

/* TODO: used to measure elapsed time since last "visit" */
static uint32_t last_count;
int timer_irq_disable(){
	writew (0,(uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_CFG_LO_OFFSET));
	writew (0,(uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_CFG_HI_OFFSET));

}

int timer_irq_init(uint32_t ticks)
{
	/* TODO: enable soc_eu timer interrupt */

	/* set the interrupt interval */
	timer_irq_set_timeout(ticks, false);

	/* We use only one of the 32-bit timer, leaving the other half available
	 * as an additional timer. We didn't opt for using both together as
	 * 64-bit timer.
	 *
	 * Enable timer, use 32khz ref clock as source. Timer will reset
	 * automatically to zero after causing an interrupt.
	 */
/* use high timer for now as int actually gets to cpu */
#ifdef configMTIME_BASE_ADDRESS
	writew(0xc000000f,(uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_CFG_LO_OFFSET));
#else
	writew(TIMER_CFG_LO_ENABLE_MASK | TIMER_CFG_LO_RESET_MASK |
		       TIMER_CFG_LO_MODE_MASK |
		       TIMER_CFG_LO_IRQEN_MASK,
	       (uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_CFG_LO_OFFSET));
#endif

	return 0;
}

int timer_irq_set_timeout(uint32_t ticks, bool idle)
{
	(void)idle;
	/* fast reset, value doesn't matter */

	writew(1, (uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_RESET_LO_OFFSET));
	writew(ticks, (uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_CMP_LO_OFFSET));
	writew(1, (uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_RESET_HI_OFFSET));
	
	return 0;
}

/* TODO: implement */
uint32_t timer_irq_clock_elapsed()
{
	return 0;
}

uint32_t timer_irq_cycle_get_32()
{
	return readw((uintptr_t)(PULP_FC_TIMER_ADDR + TIMER_CNT_LO_OFFSET));
}
