/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_IPC_EVENT_MGR_MBX_CONFIG_H
#define HPM_IPC_EVENT_MGR_MBX_CONFIG_H


#if defined(HPM_FEATURE_MBX_SIDE_A)
#define HPM_MBX HPM_MBX0A
#define IRQn_MBX IRQn_MBX0A
#elif defined(HPM_FEATURE_MBX_SIDE_B)
#define HPM_MBX HPM_MBX0B
#define IRQn_MBX IRQn_MBX0B
#endif


#endif /* HPM_IPC_EVENT_MGR_MBX_CONFIG_H */
