/**
  ******************************************************************************
  * @file    bl602_tzc_sec.c
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

#include "string.h"
#include "bl602_tzc_sec.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TZC_SEC
 *  @{
 */

/** @defgroup  TZC_SEC_Private_Macros
 *  @{
 */

/*@} end of group TZC_SEC_Private_Macros */

/** @defgroup  TZC_SEC_Private_Types
 *  @{
 */

/*@} end of group TZC_SEC_Private_Types */

/** @defgroup  TZC_SEC_Private_Variables
 *  @{
 */

/*@} end of group TZC_SEC_Private_Variables */

/** @defgroup  TZC_SEC_Global_Variables
 *  @{
 */

/*@} end of group TZC_SEC_Global_Variables */

/** @defgroup  TZC_SEC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group TZC_SEC_Private_Fun_Declaration */

/** @defgroup  TZC_SEC_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  TZC Security boot set
 *
 * @param  Val: 0 for security boot start, and 0xf for security boot finished
 *
 * @return None
 *
*******************************************************************************/
void TZC_Sboot_Set(uint8_t Val)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_SBOOT_DONE, Val);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TZC Set ROM0 R0 protect range
 *
 * @param  start: Start address to protect
 * @param  length: length to protect
 *
 * @return None
 *
*******************************************************************************/
void TZC_Set_Rom0_R0_Protect(uint32_t start, uint32_t length)
{
    uint32_t tmpVal;
    uint32_t alignEnd = (start+length+1023)&~0x3FF;

    /* Set Range */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM0_R0);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R0_START, ((start >> 10)&0xffff));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R0_END, ((alignEnd >> 10)&0xffff)-1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM0_R0, tmpVal);

    /* Enable */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R0_ID0_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R0_ID1_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R0_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R0_LOCK, 1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TZC Set ROM0 R1 protect range
 *
 * @param  start: Start address to protect
 * @param  length: length to protect
 *
 * @return None
 *
*******************************************************************************/
void TZC_Set_Rom0_R1_Protect(uint32_t start, uint32_t length)
{
    uint32_t tmpVal;
    uint32_t alignEnd = (start+length+1023)&~0x3FF;

    /* Set Range */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM0_R1);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R1_START, ((start >> 10)&0xffff));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R1_END, ((alignEnd >> 10)&0xffff)-1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM0_R1, tmpVal);

    /* Enable */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R1_ID0_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R1_ID1_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R1_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM0_R1_LOCK, 1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TZC Set ROM1 R0 protect range
 *
 * @param  start: Start address to protect
 * @param  length: length to protect
 *
 * @return None
 *
*******************************************************************************/
void TZC_Set_Rom1_R0_Protect(uint32_t start, uint32_t length)
{
    uint32_t tmpVal;
    uint32_t alignEnd = (start+length+1023)&~0x3FF;

    /* Set Range */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM1_R0);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R0_START, ((start >> 10)&0xffff));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R0_END, ((alignEnd >> 10)&0xffff)-1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM1_R0, tmpVal);

    /* Enable */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R0_ID0_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R0_ID1_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R0_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R0_LOCK, 1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TZC Set ROM1 R1 protect range
 *
 * @param  start: Start address to protect
 * @param  length: length to protect
 *
 * @return None
 *
*******************************************************************************/
void TZC_Set_Rom1_R1_Protect(uint32_t start, uint32_t length)
{
    uint32_t tmpVal;
    uint32_t alignEnd = (start+length+1023)&~0x3FF;

    /* Set Range */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM1_R1);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R1_START, ((start >> 10)&0xffff));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R1_END, ((alignEnd >> 10)&0xffff)-1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM1_R1, tmpVal);

    /* Enable */
    tmpVal = BL_RD_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R1_ID0_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R1_ID1_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R1_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TZC_SEC_TZC_ROM1_R1_LOCK, 1);

    BL_WR_REG(TZC_SEC_BASE, TZC_SEC_TZC_ROM_CTRL, tmpVal);
}

/*@} end of group TZC_SEC_Public_Functions */

/*@} end of group TZC_SEC */

/*@} end of group BL602_Peripheral_Driver */
