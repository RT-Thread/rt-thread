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
 * FilePath: sys.h
 * Created Date: 2025-04-30 15:19:21
 * Last Modified: 2025-04-30 15:20:05
 * Description:  This file is for
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 *  1.0    LiuSM    2025-04-30 15:19:21  file creation
 */

 #ifndef __METAL_SYS__H__
 #define __METAL_SYS__H__

 #ifdef __cplusplus
 extern "C" {
 #endif

 #define METAL_INTERNAL

 #if 1

 #define XLNX_MAXIRQS XSCUGIC_MAX_NUM_INTR_INPUTS

 static inline void sys_irq_enable(unsigned int vector)
 {
     InterruptUmask(vector);
 }

 static inline void sys_irq_disable(unsigned int vector)
 {
     InterruptMask(vector);
 }

 #endif /* METAL_INTERNAL */

 #ifdef __cplusplus
 }
 #endif

#endif /*  */
