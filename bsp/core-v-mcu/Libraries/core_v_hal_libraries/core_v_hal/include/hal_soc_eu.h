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


#ifndef HAL_INCLUDE_HAL_SOC_EU_H_
#define HAL_INCLUDE_HAL_SOC_EU_H_


/*
 * SOC EVENTS
 */

/* Let's remove for the time being the SOC_EU* macros from the pulp-sdk and use
 * the ones form pulp-runtime
 */

/*
#define SOC_EU_EVENT_PERIPH_EVT_NB 160

#define SOC_EU_EVENT_SW_NB (8)

#define SOC_EU_EVENT_NB_TOTAL 256

#define SOC_EU_EVENT_UDMA_NB_CHANNEL_EVT_LOG2 2
#define SOC_EU_EVENT_UDMA_NB_CHANNEL_EVT                                       \
	(1 << SOC_EU_EVENT_UDMA_NB_CHANNEL_EVT_LOG2)
#define SOC_EU_EVENT_UDMA_FIRST_EVT 0
#define SOC_EU_EVENT_UDMA_NB_EVT                                               \
	(SOC_EU_EVENT_UDMA_NB_CHANNEL_EVT * EU_NB_PERIPH)
#define SOC_EU_EVENT_UDMA_NB_TGEN_EVT 6

#define SOC_EU_EVENT_PERIPH_FIRST_EVT(x) ((x)*SOC_EU_EVENT_UDMA_NB_CHANNEL_EVT)

#define SOC_EU_EVENT_UART0_RX	   0
#define SOC_EU_EVENT_UART0_TX	   1
#define SOC_EU_EVENT_UART0_EOT	   2
#define SOC_EU_EVENT_UART0_RX_DATA 3

#define SOC_EU_EVENT_SPIM0_RX  4
#define SOC_EU_EVENT_SPIM0_TX  5
#define SOC_EU_EVENT_SPIM0_CMD 6
#define SOC_EU_EVENT_SPIM0_EOT 7

#define SOC_EU_EVENT_I2C0_RX 8
#define SOC_EU_EVENT_I2C0_TX 9

#define SOC_EU_EVENT_I2C1_RX 12
#define SOC_EU_EVENT_I2C1_TX 13

#define SOC_EU_EVENT_SDIO0_RX 16
#define SOC_EU_EVENT_SDIO0_TX 17

#define SOC_EU_EVENT_I2S0_RX 20
#define SOC_EU_EVENT_I2S0_TX 21

#define SOC_EU_EVENT_CPI0_RX 24

#define SOC_EU_EVENT_FILTER0_RX 28
#define SOC_EU_EVENT_FILTER0_TX 29

#define SOC_EU_EVENT_CLUSTER_ON_OFF   31
#define SOC_EU_EVENT_MSP	      37
#define SOC_EU_EVENT_ICU_MODE_CHANGED 37
#define SOC_EU_EVENT_ICU_OK	      37
#define SOC_EU_EVENT_ICU_DELAYED      37
#define SOC_EU_EVENT_CLUSTER_CG_OK    35
#define SOC_EU_EVENT_PICL_OK	      36
#define SOC_EU_EVENT_SCU_OK	      37
#define SOC_EU_EVENT_PMU_FIRST_EVENT  SOC_EU_EVENT_CLUSTER_ON_OFF
#define SOC_EU_EVENT_PMU_NB_EVENTS    7

#define SOC_EU_EVENT_GPIO 42

#define SOC_EU_EVENT_NB_I2S_CHANNELS  4
#define SOC_EU_EVENT_NB_UDMA_CHANNELS 19

#define SOC_EU_EVENT_FCHWPE0 140
#define SOC_EU_EVENT_FCHWPE1 141

#define SOC_EU_EVENT_SW_EVENT0 48
#define SOC_EU_EVENT_SW_EVENT1 49
#define SOC_EU_EVENT_SW_EVENT2 50
#define SOC_EU_EVENT_SW_EVENT3 51
#define SOC_EU_EVENT_SW_EVENT4 52
#define SOC_EU_EVENT_SW_EVENT5 53
#define SOC_EU_EVENT_SW_EVENT6 54
#define SOC_EU_EVENT_SW_EVENT7 55

#define SOC_EU_EVENT_NB 8

#define SOC_EU_EVENT_REF_CLK_RISE 56
*/

#define SOC_EU_EVENT	   0x00
#define SOC_FC_FIRST_MASK  0x04
#define SOC_CL_FIRST_MASK  0x24
#define SOC_PR_FIRST_MASK  0x44
#define SOC_ERR_FIRST_MASK 0x64
#define SOC_TIMER_SEL_HI   0x84
#define SOC_TIMER_SEL_LO   0x88

#define SOC_EU_EVENT_0 0x1
#define SOC_EU_EVENT_1 0x2
#define SOC_EU_EVENT_2 0x4
#define SOC_EU_EVENT_3 0x8
#define SOC_EU_EVENT_4 0x10
#define SOC_EU_EVENT_5 0x20
#define SOC_EU_EVENT_6 0x40
#define SOC_EU_EVENT_7 0x80

#define SOC_TIMER_SEL_ENABLE_SHIFT 31
#define SOC_TIMER_SEL_EVT_SHIFT	   0
#define SOC_TIMER_SEL_EVT_WIDTH	   8
#define SOC_TIMER_SEL_EVT_MASK	   ((~0U) >> (32 - SOC_TIMER_SEL_EVT_WIDTH))
// #define SOC_TIMER_SEL_EVT_MASK    0xff

#define SOC_TIMER_SEL_ENABLE_DISABLED 0
#define SOC_TIMER_SEL_ENABLE_ENABLED  1

#define SOC_TIMER_SEL_ENABLE_DIS   (0 << SOC_TIMER_SEL_ENABLE_SHIFT)
#define SOC_TIMER_SEL_ENABLE_ENA   (1 << SOC_TIMER_SEL_ENABLE_SHIFT)
#define SOC_TIMER_SEL_EVT_VAL(val) ((val) << SOC_TIMER_SEL_EVT_SHIFT)

// related to XX_FIRST_MASK registers
#define SOC_NB_EVENT_REGS    8
#define SOC_NB_EVENT_TARGETS 3

#define SOC_FC_MASK(x) (SOC_FC_FIRST_MASK + (x)*4)
#define SOC_CL_MASK(x) (SOC_CL_FIRST_MASK + (x)*4)
#define SOC_PR_MASK(x) (SOC_PR_FIRST_MASK + (x)*4)

/* TODO: doc */
void soc_eu_mask_set(uint32_t offset, uint32_t mask);
uint32_t soc_eu_mask_get(uint32_t offset);
void pulp_soc_eu_event_init();


#endif /* HAL_INCLUDE_HAL_SOC_EU_H_ */
