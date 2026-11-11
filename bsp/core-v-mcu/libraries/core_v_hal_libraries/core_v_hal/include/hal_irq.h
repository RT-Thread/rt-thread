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

/* Interrupt controller definitions */
/* Author: Robert Balas (balasr@iis.ee.ethz.ch)
 *         Germain Haugou (germain.haugou@iis.ee.ethz.ch)
 */

#ifndef HAL_INCLUDE_HAL_IRQ_H_
#define HAL_INCLUDE_HAL_IRQ_H_

#include "bits.h"

#define IRQ_REG_MASK_OFFSET	  0x000
#define IRQ_REG_MASK_SET_OFFSET	  0x004
#define IRQ_REG_MASK_CLEAR_OFFSET 0x008
#define IRQ_REG_INT_OFFSET	  0x00C
#define IRQ_REG_INT_SET_OFFSET	  0x010
#define IRQ_REG_INT_CLEAR_OFFSET  0x014
#define IRQ_REG_ACK_OFFSET	  0x018
#define IRQ_REG_ACK_SET_OFFSET	  0x01C
#define IRQ_REG_ACK_CLEAR_OFFSET  0x020
#define IRQ_REG_FIFO_OFFSET	  0x024

/* Interrupt line masks: these interrupts directly go to the core (after being
 * serialized as reqest + id). We refer to these interrupts with the prefix IRQ.
 * Events on the other we strictly use to refer to "interrupts/events" that are
 * signaled through (muxed) EU SoC interrupts (IRQ_FC_EVT_SOC_EVT) and need
 * additional handling by the user through the Event Unit.
 */
#define IRQ_FC_EVT_SW0	      BIT(0)
#define IRQ_FC_EVT_SW1	      BIT(1)
#define IRQ_FC_EVT_SW2	      BIT(2)
#define IRQ_FC_EVT_SW3	      BIT(3)
#define IRQ_FC_EVT_SW4	      BIT(4)
#define IRQ_FC_EVT_SW5	      BIT(5)
#define IRQ_FC_EVT_SW6	      BIT(6)
#define IRQ_FC_EVT_SW7	      BIT(7)
#define IRQ_FC_EVT_DMA_PE_EVT BIT(8)
#define IRQ_FC_EVT_DMA_PE_IRQ BIT(9)
#define IRQ_FC_EVT_TIMER0_LO  BIT(10)
#define IRQ_FC_EVT_TIMER0_HI  BIT(11)
#define IRQ_FC_EVT_PF	      BIT(12)
#define IRQ_FC_EVT_CLK_REF    BIT(14)
#define IRQ_FC_EVT_GPIO	      BIT(15)

/* is not in PULPissimo */
/*#define IRQ_FC_EVT_RTC		   16 */

#define IRQ_FC_EVT_ADV_TIMER0 BIT(17)
#define IRQ_FC_EVT_ADV_TIMER1 BIT(18)
#define IRQ_FC_EVT_ADV_TIMER2 BIT(19)
#define IRQ_FC_EVT_ADV_TIMER3 BIT(20)

/* is not in PULPissimo */
/* #define IRQ_FC_EVT_CLUSTER_NOT_BUSY 21 */
/* #define IRQ_FC_EVT_CLUSTER_POK	   22 */
/* #define IRQ_FC_EVT_CLUSTER_CG_OK	   23 */
/* #define IRQ_FC_EVT_PICL_OK     24 */
/* #define IRQ_FC_EVT_SCU_OK      25 */

/*
 * SoC event unit events: Many events get implicitely muxed into this interrupt.
 * A user that gets such an interrupt has to check the event unit's registers to
 * see what happened
 */
#define IRQ_FC_EVT_SOC_EVT BIT(26)
/*
 * Event queue error: If we don't process event unit events quickly enough
 * internal fifos can overflow and we get this error interrupt
 */
#define IRQ_FC_EVT_QUIRQE_ERROR BIT(29)
/* High priority peripheral events: these are hardcoded to directly go to the
 * core using a dedicated interrupt line
 */
#define IRQ_FC_EVT_PERIPH0 BIT(30)
#define IRQ_FC_EVT_PERIPH1 BIT(31)

/* TODO: doc */
void irq_mask(uint32_t mask);
void irq_enable(uint32_t mask);
void irq_disable(uint32_t mask);
uint32_t irq_clint_disable();
uint32_t irq_clint_enable();
void pulp_irq_init();

#endif /* HAL_INCLUDE_HAL_IRQ_H_ */
