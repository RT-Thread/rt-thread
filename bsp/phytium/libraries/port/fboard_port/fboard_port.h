/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fboard_port.h
 * Created Date: 2023-10-27 17:02:35
 * Last Modified: 2023-10-27 09:22:20
 * Description:  This file is for board layer code decoupling
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 *  1.0     zhangyan  2023/10/27    first release
 */
#ifndef FBOARD_PORT_H
#define FBOARD_PORT_H

#include <rtthread.h>
#include <rtdbg.h>
#include "rtconfig.h"


#if (DBG_LEVEL >= DBG_WARNING)
    #define FT_DEBUG_PRINT_W(TAG, format, ...) LOG_W(format, ##__VA_ARGS__)
#else
    #define FT_DEBUG_PRINT_W(TAG, format, ...) LOG_W(...)
#endif

#if (DBG_LEVEL >= DBG_INFO)
    #define FT_DEBUG_PRINT_I(TAG, format, ...) LOG_I(format, ##__VA_ARGS__)
#else
    #define FT_DEBUG_PRINT_I(TAG, format, ...) LOG_I(...)
#endif

#if (DBG_LEVEL >= DBG_ERROR)
    #define FT_DEBUG_PRINT_E(TAG, format, ...) LOG_E(format, ##__VA_ARGS__)
#else
    #define FT_DEBUG_PRINT_E(TAG, format, ...) LOG_E(...)
#endif

#if (DBG_LEVEL >= DBG_LOG)
    #define FT_DEBUG_PRINT_D(TAG, format, ...) LOG_D(format, ##__VA_ARGS__)
#else
    #define FT_DEBUG_PRINT_D(TAG, format, ...) LOG_D(...)
#endif

#endif