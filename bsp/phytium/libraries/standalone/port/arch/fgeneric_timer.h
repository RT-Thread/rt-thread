/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fgeneric_timer.h
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:36:17
 * Description:  This file is for generic timer function port for driver
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/2/28   first release
 */
#ifndef FDRV_GENERIC_TIMER_AARCH32_H
#define FDRV_GENERIC_TIMER_AARCH32_H

/***************************** Include Files *********************************/
#include <stddef.h>
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Function *****************************************/
/* Set generic timer CompareValue */
void GenericTimerSetTimerCompareValue(u32 id, u32 interval);

/* Set generic timer TimerValue */
void GenericTimerSetTimerValue(u32 id, u32 timeout);

/* Unmask generic timer interrupt */
void GenericTimerInterruptEnable(u32 id);

/* Mask generic timer interrupt */
void GenericTimerInterruptDisable(u32 id);

/* Enable generic timer */
void GenericTimerStart(u32 id);

/* Get generic timer physical count value */
u64 GenericTimerRead(u32 id);

/* Get generic timer frequency of the system counter */
u32 GenericTimerFrequecy(void);

/* Disable generic timer */
void GenericTimerStop(u32 id);

#ifdef __cplusplus
}
#endif

#endif