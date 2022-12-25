/**
  ******************************************************************************
  * @file    bl808_sec_dbg.c
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
#include "bl808_sec_dbg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SEC_DBG
 *  @{
 */

/** @defgroup  SEC_DBG_Private_Macros
 *  @{
 */

/*@} end of group SEC_DBG_Private_Macros */

/** @defgroup  SEC_DBG_Private_Types
 *  @{
 */

/*@} end of group SEC_DBG_Private_Types */

/** @defgroup  SEC_DBG_Private_Variables
 *  @{
 */

/*@} end of group SEC_DBG_Private_Variables */

/** @defgroup  SEC_DBG_Global_Variables
 *  @{
 */

/*@} end of group SEC_DBG_Global_Variables */

/** @defgroup  SEC_DBG_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SEC_DBG_Private_Fun_Declaration */

/** @defgroup  SEC_DBG_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Sec Dbg read chip ID
 *
 * @param  id[8]: chip ID buffer
 *
 * @return None
 *
*******************************************************************************/
void Sec_Dbg_Read_Chip_ID(uint8_t id[8])
{
    uint32_t idLow, idHigh;

    idLow = BL_RD_REG(SEC_DBG_BASE, SEC_DBG_SD_CHIP_ID_LOW);
    BL_WRWD_TO_BYTEP(id, idLow);

    idHigh = BL_RD_REG(SEC_DBG_BASE, SEC_DBG_SD_CHIP_ID_HIGH);
    BL_WRWD_TO_BYTEP((id + 4), idHigh);
}

/***************************************************************************** /
 * @brief  Sec Dbg set PWD
 *
 * @param  pwd: PWD buffer
 *
 * @return None
 *
*******************************************************************************/
void Sec_Dbg_Set_Dbg_Pwd(const uint32_t pwd[4])
{
    BL_WR_REG(SEC_DBG_BASE, SEC_DBG_SD_DBG_PWD_LOW, pwd[0]);
    BL_WR_REG(SEC_DBG_BASE, SEC_DBG_SD_DBG_PWD_HIGH, pwd[1]);
    BL_WR_REG(SEC_DBG_BASE, SEC_DBG_SD_DBG_PWD2_LOW, pwd[2]);
    BL_WR_REG(SEC_DBG_BASE, SEC_DBG_SD_DBG_PWD2_HIGH, pwd[3]);
}

/****************************************************************************/ /**
 * @brief  Sec Dbg read debug mode
 *
 * @param  None
 *
 * @return debug mode status
 *
*******************************************************************************/
uint32_t Sec_Dbg_Read_Dbg_Mode(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(SEC_DBG_BASE, SEC_DBG_SD_STATUS), SEC_DBG_SD_DBG_MODE);
}

/****************************************************************************/ /**
 * @brief  Sec Dbg read debug enable status
 *
 * @param  None
 *
 * @return enable status
 *
*******************************************************************************/
uint32_t Sec_Dbg_Read_Dbg_Enable(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(SEC_DBG_BASE, SEC_DBG_SD_STATUS), SEC_DBG_SD_DBG_ENA);
}

/****************************************************************************/ /**
 * @brief  Sec Dbg Set debug trigger status
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Dbg_Set_Dbg_Trigger(void)
{
    uint32_t tmpVal=0;
    tmpVal=BL_RD_REG(SEC_DBG_BASE, SEC_DBG_SD_STATUS);
    tmpVal=BL_SET_REG_BIT(tmpVal,SEC_DBG_SD_DBG_PWD_TRIG);
    BL_WR_REG(SEC_DBG_BASE, SEC_DBG_SD_STATUS,tmpVal);
}

/*@} end of group SEC_DBG_Public_Functions */

/*@} end of group SEC_DBG */

/*@} end of group BL808_Peripheral_Driver */
