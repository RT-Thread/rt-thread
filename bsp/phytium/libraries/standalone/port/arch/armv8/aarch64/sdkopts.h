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
 *  1.0    zhugengyu    2023/03/03            first release
 */

#ifndef SDK_OPTS_H
#define SDK_OPTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************Control Options*******************/
/* cpu aarch 32/64 */
#define CPU_AARCH     64
#define TARGET_NAME   "e2000d_baremetal_a64"

/* e2000d e2000q e2000s d2000 ft2004 */
#define CPU_TYPE_E2000D      0
#define CPU_TYPE_E2000Q      1
#define CPU_TYPE_E2000S      2
#define CPU_TYPE_D2000       3
#define CPU_TYPE_FT2004      4
#define CPU_TYPE             CPU_TYPE_E2000D

/* log type */
#define LOG_TYPE_VERBOS      0
#define LOG_TYPE_DEBUG       1
#define LOG_TYPE_INFO        2
#define LOG_TYPE_WARN        3
#define LOG_TYPE_ERROR       4
#define LOG_TYPE_NONE        5
#define LOG_TYPE             LOG_TYPE_ERROR

/*******************SDK Configures*******************/
#include "sdkopts.h"

#ifdef __cplusplus
}
#endif

#endif /* SDK_OPTS_H */