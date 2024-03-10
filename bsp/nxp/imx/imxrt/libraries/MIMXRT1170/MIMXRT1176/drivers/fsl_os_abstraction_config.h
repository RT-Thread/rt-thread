/*!
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_OS_ABSTRACTION_CONFIG_H_
#define _FSL_OS_ABSTRACTION_CONFIG_H_

#ifndef gMainThreadStackSize_c
#define gMainThreadStackSize_c 1024
#endif

#ifndef gMainThreadPriority_c
#define gMainThreadPriority_c 1
#endif

#ifndef gTaskMultipleInstancesManagement_c
#define gTaskMultipleInstancesManagement_c 0
#endif

/*! @brief Definition to determine whether enable OSA's TASK module. */
#ifndef OSA_USED
#ifndef FSL_OSA_TASK_ENABLE
#define FSL_OSA_TASK_ENABLE 0U
#endif
#else
#if defined(FSL_OSA_TASK_ENABLE)
#undef FSL_OSA_TASK_ENABLE
#endif
#define FSL_OSA_TASK_ENABLE 1U
#endif /* OSA_USED */

#endif /* _FSL_OS_ABSTRACTION_CONFIG_H_ */
