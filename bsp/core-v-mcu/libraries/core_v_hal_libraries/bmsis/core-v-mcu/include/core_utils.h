/*
 * Copyright 2020 Greenwaves Technologies
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
 */

#ifndef __PMSIS_CORE_UTILS__
#define __PMSIS_CORE_UTILS__

#include "csr.h"

/** FC_CLUSTER_ID Definitions */
#define FC_CLUSTER_ID                 32                /**< FC CLuster ID */

/**
  \ingroup  CMSIS_Core_IDFunctionInterface
  \defgroup CMSIS_Core_IDFunctions ID Functions
  \brief    Functions that manage Cluster and Core ID.
  @{
 */

static inline uint32_t __native_core_id() {
  /* encoding of mhartid: {21'b0, cluster_id_i[5:0], 1'b0, core_id_i[3:0]} */
  uint32_t mhartid = csr_read(MHARTID_ADDR);
  return mhartid & 0x01f;
}

static inline uint32_t __native_cluster_id() {
  /* encoding of mhartid {21'b0, cluster_id_i[5:0], 1'b0, core_id_i[3:0]} */
  uint32_t mhartid = csr_read(MHARTID_ADDR);
  return 0 ;//(mhartid >> 5) & 0x3f;
}

static inline uint32_t __native_is_fc() {
  return ( __native_cluster_id() == FC_CLUSTER_ID);
}

#endif
