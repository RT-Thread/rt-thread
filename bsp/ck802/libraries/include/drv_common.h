/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     drv_common.h
 * @brief    Header File for Common Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _DRV_COMMON_H_
#define _DRV_COMMON_H_

#include <stdint.h>
#include <drv_errno.h>
#include "config.h"

/** pin definition */
typedef int32_t pin_t;

/// \details driver handle
typedef void *drv_handle_t;

/**
\brief General power states
*/
typedef enum  {
    DRV_POWER_OFF,                        ///< Power off: no operation possible
    DRV_POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
    DRV_POWER_FULL                        ///< Power on: full operation at maximum performance
} drv_power_stat_e;

#endif /* _DRV_COMMON_H */

