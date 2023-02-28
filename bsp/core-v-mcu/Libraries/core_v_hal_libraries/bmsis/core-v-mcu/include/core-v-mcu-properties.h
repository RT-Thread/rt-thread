/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna and GreenWaves Technologies
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

#ifndef TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PROPERTIES_H_
#define TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PROPERTIES_H_

/* PULP defs */
#define PULP

#define ARCHI_FPGA_FREQUENCY 5000000

/* hardware modules */
#define ARCHI_NUM_TIMER 1
#define ARCHI_NUM_FLL 2

#define ARCHI_REF_CLOCK_LOG2 15
#define ARCHI_REF_CLOCK	(1 << ARCHI_REF_CLOCK_LOG2)

#define ARCHI_NB_FLL	  3

#define __RT_FLL_CL	2
#define __RT_FLL_PERIPH 1
#define __RT_FLL_FC	0

#define __RT_FREQ_DOMAIN_FC	0
#define __RT_FREQ_DOMAIN_CL	2
#define __RT_FREQ_DOMAIN_PERIPH 1
#define RT_FREQ_NB_DOMAIN	3

/* Cores & cluster */
/* FC */
#define ARCHI_FC_CID                (32)

/* Cluster */
#define ARCHI_HAS_CLUSTER           (1)
#define ARCHI_CL_CID(id)            (id)
#define ARCHI_CLUSTER_NB_PE         (8) /* Processing elements. */

/* Memories */
/* FC memory */
#define ARCHI_HAS_FC_TCDM           (1)
#define ARCHI_HAS_FC_ALIAS          (1)
#define FC_TCDM_SIZE                (0x00004000) /* 16kB. */

/* L2 memory */
#define ARCHI_HAS_L2_ALIAS          (0)
#define L2_SHARED_SIZE              (0x00080000) /* 512kB. */

/* L1 cluster memory */
#define ARCHI_HAS_CL_L1_ALIAS       (1)
#define CL_L1_SIZE                  (0x00010000) /* 64kB. */

/* L1 cluster TS */
#define ARCHI_HAS_CL_L1_TS          (1)

#define UDMA_NB_PERIPH              (10)
/* Size of each UDMA peripheral */
#define UDMA_PERIPH_SIZE_LOG2       (7)
#define UDMA_PERIPH_SIZE            (1 << UDMA_PERIPH_SIZE_LOG2)

#endif /* TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PROPERTIES_H_ */
