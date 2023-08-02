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
 * FilePath: sdkopts.h
 * Date: 2022-09-16 13:54:28
 * LastEditTime: 2022-09-16 13:54:28
 * Description:  This file is for configure sdkconfig in non-Kconfig way
 * 
 * Modify History: 
 *  Ver     Who           Date                  Changes
 * -----   ------       --------     --------------------------------------
 *  1.0   zhugengyu    2023/03/01            first release
 */

#ifndef SDK_CONFIG_H
#define SDK_CONFIG_H

#include "rtconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TARGET_ARMV8_AARCH32)
#define CONFIG_TARGET_ARMV8_AARCH32
#elif defined(TARGET_ARMV8_AARCH64)
#define CONFIG_TARGET_ARMV8_AARCH64
#endif

#if defined(TARGET_E2000D)
#define CONFIG_TARGET_E2000
#define CONFIG_TARGET_E2000D
#elif defined(TARGET_E2000Q)
#define CONFIG_TARGET_E2000
#define CONFIG_TARGET_E2000Q
#elif defined(TARGET_E2000S)
#define CONFIG_TARGET_E2000
#define CONFIG_TARGET_E2000S
#elif defined(TARGET_D2000)
#define CONFIG_TARGET_D2000
#elif defined(TARGET_F2000_4)
#define CONFIG_TARGET_F2000_4
#endif

#if defined(LOG_VERBOS)
#define CONFIG_LOG_VERBOS
#elif defined(LOG_DEBUG)
#define CONFIG_LOG_DEBUG
#elif defined(LOG_INFO)
#define CONFIG_LOG_INFO
#elif defined(LOG_WARN)
#define CONFIG_LOG_WARN
#elif defined(LOG_ERROR)
#define CONFIG_LOG_ERROR
#elif defined(LOG_NONE)
#define CONFIG_LOG_NONE
#endif

#if defined(BSP_USING_UART)
#define CONFIG_USE_SERIAL
#define CONFIG_ENABLE_Pl011_UART
#endif

#if defined(BSP_USING_CAN)
#define CONFIG_USE_CAN
#define CONFIG_USE_FCAN
#define CONFIG_FCAN_USE_CANFD
#endif

#if defined(BSP_USING_QSPI)
#define CONFIG_USE_QSPI
#define CONFIG_USE_FQSPI
#endif

#if defined(BSP_USING_ETH)
#define CONFIG_USE_ETH
#endif

#ifdef __cplusplus
}
#endif

#endif /* SDK_CONFIG_H */