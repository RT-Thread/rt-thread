/*
 * Copyright (c) 2013-2016 ARM Limited. All rights reserved.
 * Copyright (c) 2016, Freescale Semiconductor, Inc. Not a Contribution.
 * Copyright 2016-2021 NXP. Not a Contribution.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FSL_ENET_CMSIS_H_
#define FSL_ENET_CMSIS_H_

#include "Driver_ETH.h"
#include "Driver_ETH_MAC.h"
#include "RTE_Device.h"
#include "fsl_common.h"
#include "fsl_enet.h"

/* ENET Driver state flags */
#define ENET_FLAG_UNINIT     (0U)
#define ENET_FLAG_INIT       (1U << 0)
#define ENET_FLAG_POWER      (1U << 1)
#define ETH_MAC_EVENT_OTHERS (ARM_ETH_MAC_EVENT_TIMER_ALARM + 1U)

typedef struct _cmsis_enet_mac_resource
{
    ENET_Type *base;           /*!< ENET peripheral base address. */
    uint32_t (*GetFreq)(void); /*!< Function to get frequency. */
} cmsis_enet_mac_resource_t;

extern ARM_DRIVER_ETH_MAC Driver_ETH_MAC0;

#endif
