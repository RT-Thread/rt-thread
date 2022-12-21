/*
 * hal_pmsis_types.h
 *
 *  Created on: Feb 20, 2021
 *      Author: qlblue
 */

#ifndef HAL_INCLUDE_HAL_PMSIS_TYPES_PI_H_
#define HAL_INCLUDE_HAL_PMSIS_TYPES_PI_H_

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

#ifndef __PMSIS_IMPLEM_PMSIS_TYPES_H__
#define __PMSIS_IMPLEM_PMSIS_TYPES_H__

#include "hal_pmsis_types.h"

#ifndef PI_TASK_IMPLEM
#define PI_TASK_IMPLEM \
    int8_t destroy;
#endif

#ifndef PI_TASK_IMPLEM_NB_DATA
#define PI_TASK_IMPLEM_NB_DATA 8
#endif  /* PI_TASK_IMPLEM_NB_DATA */

typedef struct pi_task
{
    // Warning, might be accessed inline in asm, and thus can not be moved
    uintptr_t arg[4];
    int32_t id;
    uint32_t data[PI_TASK_IMPLEM_NB_DATA];
    pi_sem_t wait_on;
    struct pi_task *next;
    volatile int8_t done;
    int8_t core_id;
    int8_t cluster_id;
    PI_TASK_IMPLEM;
} pi_task_t;

#endif  /* __PMSIS_IMPLEM_PMSIS_TYPES_H__ */

#endif /* HAL_INCLUDE_HAL_PMSIS_TYPES_PI_H_ */
