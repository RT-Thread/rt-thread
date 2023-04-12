/**
  ******************************************************************************
  * @file    bl616_l1c.h
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
#ifndef __BL616_L1C_H__
#define __BL616_L1C_H__

// #include "pds_reg.h"
#include "bl616_common.h"

/** @addtogroup  BL616_Peripheral_Driver
 *  @{
 */

/** @addtogroup  L1C
 *  @{
 */

/** @defgroup  L1C_Public_Types
 *  @{
 */

/**
 *  @brief L1C configuration structure type definition
 */
typedef struct
{
    uint8_t cacheEn;
    uint8_t wayDis;
    uint8_t wa;
    uint8_t wb;
    uint8_t wt;
    uint8_t rsvd[3];
    uint32_t cacheRangeL;
    uint32_t cacheRangeH;
} L1C_CACHE_Cfg_Type;

/*@} end of group L1C_Public_Types */

/** @defgroup  L1C_Public_Constants
 *  @{
 */

/*@} end of group L1C_Public_Constants */

/** @defgroup  L1C_Public_Macros
 *  @{
 */
#define L1C_WAY_DISABLE_NONE       0x00
#define L1C_WAY_DISABLE_ONE        0x01
#define L1C_WAY_DISABLE_TWO        0x03
#define L1C_WAY_DISABLE_ALL        0x03
#define L1C_WAY_DISABLE_NOT_CAHNGE 0xFF

/*@} end of group L1C_Public_Macros */

/** @defgroup  L1C_Public_Functions
 *  @{
 */

/*----------*/
BL_Err_Type L1C_ICache_Enable(uint8_t wayDsiable);
BL_Err_Type L1C_DCache_Enable(uint8_t wayDsiable);
BL_Err_Type L1C_ICache_Disable(void);
BL_Err_Type L1C_DCache_Disable(void);
void L1C_DCache_Write_Set(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn);
BL_Err_Type L1C_DCache_Clean_All(void);
BL_Err_Type L1C_DCache_Clean_Invalid_All(void);
BL_Err_Type L1C_ICache_Invalid_All(void);
BL_Err_Type L1C_DCache_Invalid_All(void);
BL_Err_Type L1C_DCache_Clean_By_Addr(uintptr_t addr, uint32_t len);
BL_Err_Type L1C_DCache_Clean_Invalid_By_Addr(uintptr_t addr, uint32_t len);
BL_Err_Type L1C_ICache_Invalid_By_Addr(uintptr_t addr, uint32_t len);
BL_Err_Type L1C_DCache_Invalid_By_Addr(uintptr_t addr, uint32_t len);
/*----------*/
BL_Err_Type L1C_Set_Wrap(uint8_t en);
BL_Err_Type L1C_Set_Cache_Setting_By_ID(uint8_t core, L1C_CACHE_Cfg_Type *cacheSetting);
/*----------*/
int L1C_Is_DCache_Range(uintptr_t addr);
int L1C_Get_None_Cache_Addr(uintptr_t addr);
/*@} end of group L1C_Public_Functions */

/*@} end of group L1C */

/*@} end of group BL616_Peripheral_Driver */

#endif /* __BL616_L1C_H__ */
