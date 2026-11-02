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

/* Author: Robert Balas (balasr@iis.ee.ethz.ch)
 *         Germain Haugou (germain.haugou@iis.ee.ethz.ch)
 */

#ifndef HAL_INCLUDE_HAL_TIMER_H_
#define HAL_INCLUDE_HAL_TIMER_H_

#include "bits.h"

/* Timer Low Configuration register. */
#define TIMER_CFG_LO_OFFSET 0x0

/* Timer High Configuration register. */
#define TIMER_CFG_HI_OFFSET 0x4

/* Timer Low counter value register. */
#define TIMER_CNT_LO_OFFSET 0x8

/* Timer High counter value register. */
#define TIMER_CNT_HI_OFFSET 0xc

/* Timer Low comparator value register. */
#define TIMER_CMP_LO_OFFSET 0x10

/* Timer High comparator value register. */
#define TIMER_CMP_HI_OFFSET 0x14

/* Start Timer Low counting register. */
#define TIMER_START_LO_OFFSET 0x18

/* Start Timer High counting register. */
#define TIMER_START_HI_OFFSET 0x1c

/* Reset Timer Low counter register. */
#define TIMER_RESET_LO_OFFSET 0x20

/* Reset Timer High counter register. */
#define TIMER_RESET_HI_OFFSET 0x24

/* Timer low enable configuration bitfield: - 1'b0: disabled - 1'b1: enabled
 * (access: R/W) */
#define TIMER_CFG_LO_ENABLE_BIT	  0
#define TIMER_CFG_LO_ENABLE_WIDTH 1
#define TIMER_CFG_LO_ENABLE_MASK  0x1

/* Timer low counter reset command bitfield. Cleared after Timer Low reset
 * execution. (access: R/W) */
#define TIMER_CFG_LO_RESET_BIT	 1
#define TIMER_CFG_LO_RESET_WIDTH 1
#define TIMER_CFG_LO_RESET_MASK	 0x2

/* Timer low compare match interrupt enable configuration bitfield: - 1'b0:
 * disabled - 1'b1: enabled (access: R/W) */
#define TIMER_CFG_LO_IRQEN_BIT	 2
#define TIMER_CFG_LO_IRQEN_WIDTH 1
#define TIMER_CFG_LO_IRQEN_MASK	 0x4

/* Timer low input event mask configuration bitfield: - 1'b0: disabled - 1'b1:
 * enabled (access: R/W) */
#define TIMER_CFG_LO_IEM_BIT   3
#define TIMER_CFG_LO_IEM_WIDTH 1
#define TIMER_CFG_LO_IEM_MASK  0x8

/* Timer low continuous mode configuration bitfield: - 1'b0: Continue mode -
 * continue incrementing Timer low counter when compare match with CMP_LO
 * occurs. - 1'b1: Cycle mode - reset Timer low counter when compare match with
 * CMP_LO occurs. (access: R/W) */
#define TIMER_CFG_LO_MODE_BIT	4
#define TIMER_CFG_LO_MODE_WIDTH 1
#define TIMER_CFG_LO_MODE_MASK	0x10

/* Timer low one shot configuration bitfield: - 1'b0: let Timer low enabled
 * counting when compare match with CMP_LO occurs. - 1'b1: disable Timer low
 * when compare match with CMP_LO occurs. (access: R/W) */
#define TIMER_CFG_LO_ONE_S_BIT	 5
#define TIMER_CFG_LO_ONE_S_WIDTH 1
#define TIMER_CFG_LO_ONE_S_MASK	 0x20

/* Timer low prescaler enable configuration bitfield:- 1'b0: disabled - 1'b1:
 * enabled (access: R/W) */
#define TIMER_CFG_LO_PEN_BIT   6
#define TIMER_CFG_LO_PEN_WIDTH 1
#define TIMER_CFG_LO_PEN_MASK  0x40

/* Timer low clock source configuration bitfield: - 1'b0: FLL or FLL+Prescaler - 1'b1: Reference clock at 32kHz (access: R/W) */
#define TIMER_CFG_LO_CCFG_BIT	7
#define TIMER_CFG_LO_CCFG_WIDTH 1
#define TIMER_CFG_LO_CCFG_MASK	0x80

/* Timer low prescaler value bitfield. Ftimer = Fclk / (1 + PRESC_VAL) (access:
 * R/W) */
#define TIMER_CFG_LO_PVAL_BIT	8
#define TIMER_CFG_LO_PVAL_WIDTH 8
#define TIMER_CFG_LO_PVAL_MASK	0xff00

/* Timer low + Timer high 64bit cascaded mode configuration bitfield. (access:
 * R/W) */
#define TIMER_CFG_LO_CASC_BIT	31
#define TIMER_CFG_LO_CASC_WIDTH 1
#define TIMER_CFG_LO_CASC_MASK	0x80000000

/* Timer high enable configuration bitfield: - 1'b0: disabled - 1'b1: enabled
 * (access: R/W) */
#define TIMER_CFG_HI_ENABLE_BIT	  0
#define TIMER_CFG_HI_ENABLE_WIDTH 1
#define TIMER_CFG_HI_ENABLE_MASK  0x1

/* Timer high counter reset command bitfield. Cleared after Timer high reset
 * execution. (access: W) */
#define TIMER_CFG_HI_RESET_BIT	 1
#define TIMER_CFG_HI_RESET_WIDTH 1
#define TIMER_CFG_HI_RESET_MASK	 0x2

/* Timer high compare match interrupt enable configuration bitfield: - 1'b0:
 * disabled - 1'b1: enabled (access: R/W) */
#define TIMER_CFG_HI_IRQEN_BIT	 2
#define TIMER_CFG_HI_IRQEN_WIDTH 1
#define TIMER_CFG_HI_IRQEN_MASK	 0x4

/* Timer high input event mask configuration bitfield: - 1'b0: disabled - 1'b1:
 * enabled (access: R/W) */
#define TIMER_CFG_HI_IEM_BIT   3
#define TIMER_CFG_HI_IEM_WIDTH 1
#define TIMER_CFG_HI_IEM_MASK  0x8

/* Timer high continuous mode configuration bitfield: - 1'b0: Continue mode -
 * continue incrementing Timer high counter when compare match with CMP_LO
 * occurs. - 1'b1: Cycle mode - reset Timer high counter when compare match with
 * CMP_LO occurs. (access: R/W) */
#define TIMER_CFG_HI_MODE_BIT	4
#define TIMER_CFG_HI_MODE_WIDTH 1
#define TIMER_CFG_HI_MODE_MASK	0x10

/* Timer high one shot configuration bitfield: - 1'b0: let Timer high enabled
 * counting when compare match with CMP_LO occurs. - 1'b1: disable Timer high
 * when compare match with CMP_LO occurs. (access: R/W) */
#define TIMER_CFG_HI_ONE_S_BIT	 5
#define TIMER_CFG_HI_ONE_S_WIDTH 1
#define TIMER_CFG_HI_ONE_S_MASK	 0x20

/* Timer high prescaler enable configuration bitfield: - 1'b0: disabled - 1'b1:
 * enabled (access: R/W) */
#define TIMER_CFG_HI_PEN_BIT   6
#define TIMER_CFG_HI_PEN_WIDTH 1
#define TIMER_CFG_HI_PEN_MASK  0x40


/* Timer high clock source configuration bitfield: - 1'b0: FLL or FLL+Prescaler
 * - 1'b1: Reference clock at 32kHz (access: R/W) */
#define TIMER_CFG_HI_CCFG_BIT	  7
#define TIMER_CFG_HI_CCFG_WIDTH 1
#define TIMER_CFG_HI_CCFG_MASK  0x80

/* Timer Low counter value bitfield. (access: R/W) */
#define TIMER_CNT_LO_CNT_LO_BIT	  0
#define TIMER_CNT_LO_CNT_LO_WIDTH 32
#define TIMER_CNT_LO_CNT_LO_MASK  0xffffffff

/* Timer High counter value bitfield. (access: R/W) */
#define TIMER_CNT_HI_CNT_HI_BIT	  0
#define TIMER_CNT_HI_CNT_HI_WIDTH 32
#define TIMER_CNT_HI_CNT_HI_MASK  0xffffffff

/* Timer Low comparator value bitfield. (access: R/W) */
#define TIMER_CMP_LO_CMP_LO_BIT	  0
#define TIMER_CMP_LO_CMP_LO_WIDTH 32
#define TIMER_CMP_LO_CMP_LO_MASK  0xffffffff

/* Timer High comparator value bitfield. (access: R/W) */
#define TIMER_CMP_HI_CMP_HI_BIT	  0
#define TIMER_CMP_HI_CMP_HI_WIDTH 32
#define TIMER_CMP_HI_CMP_HI_MASK  0xffffffff

/* Timer Low start command bitfield. When executed, CFG_LO.ENABLE is set.
 * (access: W) */
#define TIMER_START_LO_STRT_LO_BIT   0
#define TIMER_START_LO_STRT_LO_WIDTH 1
#define TIMER_START_LO_STRT_LO_MASK  0x1

/* Timer High start command bitfield. When executed, CFG_HI.ENABLE is set.
 * (access: W) */
#define TIMER_START_HI_STRT_HI_BIT   0
#define TIMER_START_HI_STRT_HI_WIDTH 1
#define TIMER_START_HI_STRT_HI_MASK  0x1

/* Timer Low counter reset command bitfield. When executed, CFG_LO.RESET is set.
 * (access: W) */
#define TIMER_RESET_LO_RST_LO_BIT   0
#define TIMER_RESET_LO_RST_LO_WIDTH 1
#define TIMER_RESET_LO_RST_LO_MASK  0x1

/* Timer High counter reset command bitfield. When executed, CFG_HI.RESET is
 * set. (access: W) */
#define TIMER_RESET_HI_RST_HI_BIT   0
#define TIMER_RESET_HI_RST_HI_WIDTH 1
#define TIMER_RESET_HI_RST_HI_MASK  0x1

struct pulp_timer {
	unsigned int current_time;
	unsigned int flags;
	void *base;
};


#endif /* HAL_INCLUDE_HAL_TIMER_H_ */
