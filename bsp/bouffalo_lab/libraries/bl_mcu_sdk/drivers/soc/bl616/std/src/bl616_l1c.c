/**
  ******************************************************************************
  * @file    bl616_l1c.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
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

#include "bl616_l1c.h"
#include "bl616_common.h"
// #include "bl616_glb.h"

/** @addtogroup  BL616_Peripheral_Driver
 *  @{
 */

/** @addtogroup  L1C
 *  @{
 */

/** @defgroup  L1C_Private_Macros
 *  @{
 */

/*@} end of group L1C_Private_Macros */

/** @defgroup  L1C_Private_Types
 *  @{
 */

/*@} end of group L1C_Private_Types */

/** @defgroup  L1C_Private_Variables
 *  @{
 */

/*@} end of group L1C_Private_Variables */

/** @defgroup  L1C_Global_Variables
 *  @{
 */

/*@} end of group L1C_Global_Variables */

/** @defgroup  L1C_Private_Fun_Declaration
 *  @{
 */

/*@} end of group L1C_Private_Fun_Declaration */

/** @defgroup  L1C_Private_Functions
 *  @{
 */

/*@} end of group L1C_Private_Functions */

/** @defgroup  L1C_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Enable I-Cache
 *
 * @param  wayDsiable: cache way disable config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Enable(uint8_t wayDsiable)
{
#ifndef __riscv_32e
    csi_icache_enable();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Enable D-Cache
 *
 * @param  wayDsiable: cache way disable config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Enable(uint8_t wayDsiable)
{
#ifndef __riscv_32e
    csi_dcache_enable();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable I-Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Disable(void)
{
#ifndef __riscv_32e
    csi_icache_disable();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Disable D-Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Disable(void)
{
#ifndef __riscv_32e
    csi_dcache_disable();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  L1C D-Cache write set
 *
 * @param  wtEn: L1C write through enable
 * @param  wbEn: L1C write back enable
 * @param  waEn: L1C write allocate enable
 *
 * @return None
 *
*******************************************************************************/
__WEAK
void ATTR_TCM_SECTION L1C_DCache_Write_Set(BL_Fun_Type wtEn, BL_Fun_Type wbEn, BL_Fun_Type waEn)
{
    return;
}

/****************************************************************************/ /**
 * @brief  Clean all D_Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_All(void)
{
#ifndef __riscv_32e
    csi_dcache_clean();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clean and invalid all D_Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_Invalid_All(void)
{
#ifndef __riscv_32e
    csi_dcache_clean_invalid();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Invalid all I-Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Invalid_All(void)
{
#ifndef __riscv_32e
    csi_icache_invalid();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Invalid all D_Cache
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Invalid_All(void)
{
#ifndef __riscv_32e
    csi_dcache_invalid();
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clean D-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_By_Addr(uintptr_t addr, uint32_t len)
{
#ifndef __riscv_32e
#ifdef CPU_D0
    csi_dcache_clean_range((uintptr_t *)addr, len);
#else
    csi_dcache_clean_range((uint32_t *)(uintptr_t *)addr, len);
#endif
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Clean and invalid D-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Clean_Invalid_By_Addr(uintptr_t addr, uint32_t len)
{
#ifndef __riscv_32e
#ifdef CPU_D0
    csi_dcache_clean_invalid_range((uintptr_t *)addr, len);
#else
    csi_dcache_clean_invalid_range((uint32_t *)(uintptr_t *)addr, len);
#endif
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Invalid I-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_ICache_Invalid_By_Addr(uintptr_t addr, uint32_t len)
{
    L1C_ICache_Invalid_All();

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Invalid D-Cache according to address
 *
 * @param  addr: Address to clean
 * @param  len: Length to clean
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_TCM_SECTION L1C_DCache_Invalid_By_Addr(uintptr_t addr, uint32_t len)
{
#ifndef __riscv_32e
#ifdef CPU_D0
    csi_dcache_invalid_range((uintptr_t *)addr, len);
#else
    csi_dcache_invalid_range((uint32_t *)(uintptr_t *)addr, len);
#endif
#endif
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  cache wrap
 *
 * @param  en: wrap enable or disable
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Wrap(uint8_t en)
{
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  cache wrap
 *
 * @param  core: cpu core
 * @param  cacheSetting: cache setting
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION L1C_Set_Cache_Setting_By_ID(uint8_t core, L1C_CACHE_Cfg_Type *cacheSetting)
{
    (void)core;
    (void)cacheSetting;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Judge addr is in cache range
 *
 * @param  addr: phyical addr
 *
 * @return 1 for addr is in cache range and 0 for not in cache range
 *
*******************************************************************************/
int ATTR_TCM_SECTION L1C_Is_DCache_Range(uintptr_t addr)
{
    if(((addr>>16)&0xffff)>=0x62FC){
        return 1;
    }else{
        return 0;
    }
}

/****************************************************************************/ /**
 * @brief  Get None Cache address according to Cache address
 *
 * @param  addr: cache addr
 *
 * @return none cache addr
 *
*******************************************************************************/
int ATTR_TCM_SECTION L1C_Get_None_Cache_Addr(uintptr_t addr)
{
    return (addr&0x0FFFFFFF)|0x20000000;
}

/*@} end of group L1C_Public_Functions */

/*@} end of group L1C */

/*@} end of group BL616_Peripheral_Driver */
