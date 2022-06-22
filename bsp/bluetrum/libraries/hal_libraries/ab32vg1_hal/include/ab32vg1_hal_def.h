/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AB32VG1_HAL_DEF_H__
#define AB32VG1_HAL_DEF_H__

#include "ab32vgx.h"

typedef int                             hal_bool_t;
typedef long                            hal_base_t;
typedef unsigned long                   hal_ubase_t;

typedef hal_base_t                      hal_error_t;
typedef volatile unsigned long*         hal_sfr_t;


/* HAL error code definitions */
#define HAL_EOK                         0               /**< There is no error */
#define HAL_ERROR                       1               /**< A generic error happens */
#define HAL_ETIMEOUT                    2               /**< Timed out */
#define HAL_EFULL                       3               /**< The resource is full */
#define HAL_EEMPTY                      4               /**< The resource is empty */
#define HAL_ENOMEM                      5               /**< No memory */
#define HAL_ENOSYS                      6               /**< No system */
#define HAL_EBUSY                       7               /**< Busy */
#define HAL_EIO                         8               /**< IO error */
#define HAL_EINTR                       9               /**< Interrupted system call */
#define HAL_EINVAL                      10              /**< Invalid argument */

#define HAL_NULL                        ((void *)0)

#define HAL_DISABLE                     (0)
#define HAL_ENABLE                      (1)

#define HAL_RESET                       (0)
#define HAL_SET                         (1)

#endif
