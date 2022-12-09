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

/* Backend includes. */
//#include "pmsis/backend/implementation_specific_defines.h"
//#include "hal/include/hal_target.h"
/* pmsis_api includes. */
//#include "pmsis/device.h"
//#include "pmsis/task.h"
//#include "pmsis_types.h"
//#include "../../../pmsis_api/include/pmsis/rtos/rtos-orig.h"
//#include "pmsis/rtos/assert.h"
//#include "pmsis/mem_slab.h"

/* PMSIS includes. */
//#include "pmsis/implem/debug.h"
//#include "pmsis/implem/drivers/drivers_data.h"
//#include "hal/include/hal_pmsis_drivers.h"
	#include "hal_fc_event.h"
	#include "hal_fll_pi.h"
	#include "hal_i2c_internal.h"
	#include "hal_uart_internal.h"
//#include "pmsis/rtos/os/pmsis_task.h"
//#include "pmsis/rtos/os/pmsis_freq.h"
//#include "target/core-v-mcu/include/core-v-mcu-pmsis-rtos-os.h"
//#include "hal/include/hal_native_task_api.h"
#if defined(FEATURE_CLUSTER)
//#include "pmsis/implem/cluster/cluster.h"
#endif  /* FEATURE_CLUSTER */

#endif  /* HW_VERIF_ONLY */

/* Hal includes. */
//#include "pmsis/implem/hal/hal.h"

#endif /* TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_PMSIS_H_ */
