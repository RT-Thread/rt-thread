/*
 * Copyright : (C) 2025 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: sdkconfig.h
 * Created Date: 2025-04-24 10:47:57
 * Last Modified: 2025-05-08 19:35:29
 * Description:  This file is for
 *
 * Modify History:
 *   Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */

#ifndef SDK_CONFIG_H
#define SDK_CONFIG_H

#include "rtconfig.h"

/* openamp define */
#if defined(USE_OPENAMP)
#define CONFIG_USE_AMP
#define CONFIG_USE_LIBMETAL
#define CONFIG_USE_OPENAMP
#endif

#if defined(USE_OPENAMP_IPI)
#define CONFIG_USE_OPENAMP_IPI
#endif

#if defined (SKIP_SHBUF_IO_WRITE)
#define CONFIG_SKIP_SHBUF_IO_WRITE
#endif

#if defined (USE_MASTER_VRING_DEFINE)
#define CONFIG_USE_MASTER_VRING_DEFINE
#endif

#if defined (USE_CACHE_COHERENCY)
#define CONFIG_USE_CACHE_COHERENCY
#endif

#if defined (USE_DEFAULT_INTERRUPT_CONFIG)
#define CONFIG_USE_DEFAULT_INTERRUPT_CONFIG
#endif

#if defined (CONFIG_USE_DEFAULT_INTERRUPT_CONFIG)
#if defined (INTERRUPT_ROLE_SLAVE)
#define CONFIG_INTERRUPT_ROLE_SLAVE
#endif
#endif
#define CONFIG_MAX_XLAT_TABLES 256
#endif /* SDK_CONFIG_H */
