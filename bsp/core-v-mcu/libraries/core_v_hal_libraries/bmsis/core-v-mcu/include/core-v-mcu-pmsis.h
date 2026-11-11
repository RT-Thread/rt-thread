/*
 * Copyright 2019 GreenWaves Technologies
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


#ifndef TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PMSIS_H_
#define TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PMSIS_H_

#include <stddef.h>
#include <inttypes.h>

/* Debug helper. */
#ifdef DEBUG
#define DEBUG_PRINTF printf
#else
#define DEBUG_PRINTF(...) ((void) 0)
#endif  /* DEBUG */

#if (!defined(HW_VERIF_ONLY))

#include "hal_fc_event.h"
#include "hal_fll_pi.h"
#include "hal_i2c_internal.h"
#include "hal_uart_internal.h"

#if defined(FEATURE_CLUSTER)
#endif  /* FEATURE_CLUSTER */

#endif  /* HW_VERIF_ONLY */
/* Hal includes. */

#endif /* TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PMSIS_H_ */
