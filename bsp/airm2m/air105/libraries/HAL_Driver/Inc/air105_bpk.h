/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __AIR105_BPK_H
#define __AIR105_BPK_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"


/** @defgroup BPK_Exported_Types
  * @{
  */

#define BPK_KEY_REGION_0                      ((uint32_t)0x0001)
#define BPK_KEY_REGION_1                      ((uint32_t)0x0002)
#define BPK_KEY_REGION_ALL                    ((uint32_t)0x0003)
#define IS_BPK_KEY_REGION(REGION)             ((((REGION) & ~BPK_KEY_REGION_ALL) == 0x00) && ((REGION) != 0x00))


#define IS_BPK_LOCK(LOCK)                     ((((LOCK) & ~BPK_LR_LOCK_ALL) == 0x00) && ((LOCK) != (uint32_t)0x00))


FlagStatus BPK_IsReady(void);
ErrorStatus BPK_WriteKey(uint32_t *Key,uint32_t Key_Len, uint32_t Key_Offset);
ErrorStatus BPK_ReadKey(uint32_t *Key,uint32_t Key_Len, uint32_t Key_Offset);
void BPK_KeyWriteLock(uint16_t BPK_KEY_Region, FunctionalState NewState);
void BPK_KeyReadLock(uint16_t BPK_KEY_Region, FunctionalState NewState);
void BPK_KeyClear(uint16_t BPK_KEY_Region);

void BPK_SetScramber(uint32_t Scram);
void BPK_Lock(uint32_t BPK_LOCK, FunctionalState NewState);
void BPK_LockSelf(void);
FlagStatus BPK_GetLockStatus(uint32_t BPK_LOCK);


#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
