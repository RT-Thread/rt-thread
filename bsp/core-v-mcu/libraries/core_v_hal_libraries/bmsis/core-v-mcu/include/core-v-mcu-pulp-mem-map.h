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
 * Author: Robert Balas (balasr@iis.ee.ethz.ch)
 */

#ifndef TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PULP_MEM_MAP_H_
#define TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PULP_MEM_MAP_H_

/*
 * SOC PERIPHERALS
 */

#define PULP_SOC_PERIPHERALS_ADDR 0x1A100000

#define PULP_FC_TIMER_SIZE 0x00000800

#define PULP_FLL_OFFSET		 0x00000000
#define PULP_GPIO_OFFSET	 0x00001000
#define PULP_UDMA_OFFSET	 0x00002000
#define PULP_APB_SOC_CTRL_OFFSET 0x00004000
#define PULP_ADV_TIMER_OFFSET	 0x00005000
#define PULP_SOC_EU_OFFSET	 0x00006000
#define PULP_FC_IRQ_OFFSET	 0x00009800
/* #define PULP_FC_IRQ_OFFSET	 0x00009000 */ /* this is a mirror of above */
#define PULP_FC_TIMER_OFFSET 0x0000B000
#define PULP_FC_HWPE_OFFSET  0x0000C000
#define PULP_STDOUT_OFFSET   0x0000F000
#define PULP_DEBUG_OFFSET    0x00010000

#define PULP_FLL_ADDR  (PULP_SOC_PERIPHERALS_ADDR + PULP_FLL_OFFSET)
#define PULP_GPIO_ADDR (PULP_SOC_PERIPHERALS_ADDR + PULP_GPIO_OFFSET)
#define PULP_UDMA_ADDR (PULP_SOC_PERIPHERALS_ADDR + PULP_UDMA_OFFSET)
#define PULP_APB_SOC_CTRL_ADDR                                                 \
	(PULP_SOC_PERIPHERALS_ADDR + PULP_APB_SOC_CTRL_OFFSET)
#define PULP_ADV_TIMER_ADDR (PULP_SOC_PERIPHERALS_ADDR + PULP_ADV_TIMER_OFFSET)
#define PULP_SOC_EU_ADDR    (PULP_SOC_PERIPHERALS_ADDR + PULP_SOC_EU_OFFSET)
#define PULP_FC_IRQ_ADDR    (PULP_SOC_PERIPHERALS_ADDR + PULP_FC_IRQ_OFFSET)
/* #define PULP_FC_ITC_ADDR   (PULP_SOC_PERIPHERALS_ADDR + PULP_FC_ITC_OFFSET) */
#define PULP_FC_TIMER_ADDR (PULP_SOC_PERIPHERALS_ADDR + PULP_FC_TIMER_OFFSET)
#define PULP_FC_HWPE_ADDR  (PULP_SOC_PERIPHERALS_ADDR + PULP_FC_HWPE_OFFSET)
#define PULP_STDOUT_ADDR   (PULP_SOC_PERIPHERALS_ADDR + PULP_STDOUT_OFFSET)

#define PULP_FLL_AREA_SIZE 0x00000010

/*
 * CLUSTER
 */

#define PULP_CLUSTER_ADDR	      0x00000000
#define PULP_CLUSTER_SIZE	      0x00400000
#define PULP_CLUSTER_GLOBAL_ADDR(cid) (0x10000000 + (cid)*PULP_CLUSTER_SIZE)

/*
 * CLUSTER PERIPHERALS
 */

#define PULP_CLUSTER_PERIPHERALS_OFFSET 0x00200000

#define PULP_TIMER_OFFSET 0x00000400

#define PULP_CLUSTER_PERIPHERALS_ADDR                                          \
	(PULP_CLUSTER_ADDR + PULP_CLUSTER_PERIPHERALS_OFFSET)
#define PULP_CLUSTER_PERIPHERALS_GLOBAL_ADDR(cid)                              \
	(PULP_CLUSTER_GLOBAL_ADDR(cid) + PULP_CLUSTER_PERIPHERALS_OFFSET)

#endif /* TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PULP_MEM_MAP_H_ */
