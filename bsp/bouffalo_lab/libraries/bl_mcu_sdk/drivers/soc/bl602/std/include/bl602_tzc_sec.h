/**
  ******************************************************************************
  * @file    bl602_tzc_sec.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL602_TZC_SEC_H__
#define __BL602_TZC_SEC_H__

#include "tzc_sec_reg.h"
#include "bl602_common.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TZC_SEC
 *  @{
 */

/** @defgroup  TZC_SEC_Public_Types
 *  @{
 */

/*@} end of group TZC_SEC_Public_Types */

/** @defgroup  TZC_SEC_Public_Constants
 *  @{
 */

/*@} end of group TZC_SEC_Public_Constants */

/** @defgroup  TZC_SEC_Public_Macros
 *  @{
 */

/*@} end of group TZC_SEC_Public_Macros */

/** @defgroup  TZC_SEC_Public_Functions
 *  @{
 */

void TZC_Sboot_Set(uint8_t Val);
void TZC_Set_Rom0_R0_Protect(uint32_t start, uint32_t length);
void TZC_Set_Rom0_R1_Protect(uint32_t start, uint32_t length);
void TZC_Set_Rom1_R0_Protect(uint32_t start, uint32_t length);
void TZC_Set_Rom1_R1_Protect(uint32_t start, uint32_t length);

/*@} end of group TZC_SEC_Public_Functions */

/*@} end of group TZC_SEC */

/*@} end of group BL602_Peripheral_Driver */

#endif /* __BL602_TZC_SEC_H__ */
