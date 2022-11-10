/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * Date: 2022-10-09 15:04:36
 * LastEditTime: 2022-10-09 15:04:37
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 */

#ifndef SDK_CONFIG_H__
#define SDK_CONFIG_H__

#include "rtconfig.h"

/* board */

/*  E2000 */

#if defined(TARGET_E2000)
    #define CONFIG_TARGET_E2000
#endif

#if defined(TARGET_E2000Q)
    #define CONFIG_TARGET_E2000Q
#endif

#if defined(TARGET_ARMV8_AARCH64)
    #define CONFIG_TARGET_ARMV8_AARCH64
#endif

/* debug */

#ifdef LOG_VERBOS
    #define CONFIG_LOG_VERBOS
#endif

#ifdef LOG_ERROR
    #define CONFIG_LOG_ERROR
#endif

#ifdef LOG_WARN
    #define CONFIG_LOG_WARN
#endif

#ifdef LOG_INFO
    #define CONFIG_LOG_INFO
#endif

#ifdef LOG_DEBUG
    #define CONFIG_LOG_DEBUG
#endif

#ifdef BOOTUP_DEBUG_PRINTS
    #define CONFIG_BOOTUP_DEBUG_PRINTS
#endif

#endif
