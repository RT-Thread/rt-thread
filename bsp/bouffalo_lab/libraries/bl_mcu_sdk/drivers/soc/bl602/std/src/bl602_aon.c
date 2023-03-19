/**
  ******************************************************************************
  * @file    bl602_aon.c
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

#include "bl602_aon.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AON
 *  @{
 */

/** @defgroup  AON_Private_Macros
 *  @{
 */
#define AON_CLK_SET_DUMMY_WAIT \
    {                          \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
    }

/*@} end of group AON_Private_Macros */

/** @defgroup  AON_Private_Types
 *  @{
 */

/*@} end of group AON_Private_Types */

/** @defgroup  AON_Private_Variables
 *  @{
 */

/*@} end of group AON_Private_Variables */

/** @defgroup  AON_Global_Variables
 *  @{
 */

/*@} end of group AON_Global_Variables */

/** @defgroup  AON_Private_Fun_Declaration
 *  @{
 */

/*@} end of group AON_Private_Fun_Declaration */

/** @defgroup  AON_Private_Functions
 *  @{
 */

/*@} end of group AON_Private_Functions */

/** @defgroup  AON_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Power on MXX band gap
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_On_MBG(void)
{
    uint32_t tmpVal = 0;

    /* Power up RF for PLL to work */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    BL602_Delay_US(55);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power off MXX band gap
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_Off_MBG(void)
{
    uint32_t tmpVal = 0;

    /* Power OFF */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on XTAL
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_On_XTAL(void)
{
    uint32_t tmpVal = 0;
    uint32_t timeOut = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_XTAL_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_XTAL_BUF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    /* Polling for ready */
    do {
        BL602_Delay_US(10);
        timeOut++;
        tmpVal = BL_RD_REG(AON_BASE, AON_TSEN);
    } while (!BL_IS_REG_BIT_SET(tmpVal, AON_XTAL_RDY) && timeOut < 120);

    if (timeOut >= 120) {
        return TIMEOUT;
    }

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Set XTAL cap code
 *
 * @param  capIn: Cap code in
 * @param  capOut: Cap code out
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION AON_Set_Xtal_CapCode(uint8_t capIn, uint8_t capOut)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_XTAL_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_XTAL_CAPCODE_IN_AON, capIn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_XTAL_CAPCODE_OUT_AON, capOut);
    BL_WR_REG(AON_BASE, AON_XTAL_CFG, tmpVal);

    BL602_Delay_US(100);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Get XTAL cap code
 *
 * @param  None
 *
 * @return Cap code
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint8_t ATTR_CLOCK_SECTION AON_Get_Xtal_CapCode(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_XTAL_CFG);

    return BL_GET_REG_BITS_VAL(tmpVal, AON_XTAL_CAPCODE_IN_AON);
}
#endif

/****************************************************************************/ /**
 * @brief  Power off XTAL
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_Off_XTAL(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_XTAL_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_XTAL_BUF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on bandgap system
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_BG(void)
{
    uint32_t tmpVal = 0;

    /* power up RF for PLL to work */
    tmpVal = BL_RD_REG(AON_BASE, AON_BG_SYS_TOP);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_BG_SYS_AON);
    BL_WR_REG(AON_BASE, AON_BG_SYS_TOP, tmpVal);

    BL602_Delay_US(55);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power off bandgap system
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_BG(void)
{
    uint32_t tmpVal = 0;

    /* power up RF for PLL to work */
    tmpVal = BL_RD_REG(AON_BASE, AON_BG_SYS_TOP);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_BG_SYS_AON);
    BL_WR_REG(AON_BASE, AON_BG_SYS_TOP, tmpVal);

    BL602_Delay_US(55);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on LDO11
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_LDO11_SOC(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_LDO11SOC_AND_DCTEST);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_LDO11SOC_AON);
    BL_WR_REG(AON_BASE, AON_LDO11SOC_AND_DCTEST, tmpVal);

    BL602_Delay_US(55);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power off LDO11
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_LDO11_SOC(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_LDO11SOC_AND_DCTEST);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_LDO11SOC_AON);
    BL_WR_REG(AON_BASE, AON_LDO11SOC_AND_DCTEST, tmpVal);

    BL602_Delay_US(55);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on LDO15_RF
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_LDO15_RF(void)
{
    uint32_t tmpVal = 0;

    /* ldo15rf power on */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    BL602_Delay_US(90);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power off LDO15_RF
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_LDO15_RF(void)
{
    uint32_t tmpVal = 0;

    /* ldo15rf power off */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  power on source follow regular
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_SFReg(void)
{
    uint32_t tmpVal = 0;

    /* power on sfreg */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    BL602_Delay_US(10);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  power off source follow regular
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_SFReg(void)
{
    uint32_t tmpVal = 0;

    /* power off sfreg */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power off the power can be shut down in PDS0
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_LowPower_Enter_PDS0(void)
{
    uint32_t tmpVal = 0;

    /* power off sfreg */
    tmpVal = BL_RD_REG(AON_BASE, AON_MISC);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_SW_WB_EN_AON);
    BL_WR_REG(AON_BASE, AON_MISC, tmpVal);

    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    /* gating Clock */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpVal = tmpVal & (~(1 << 6));
    tmpVal = tmpVal & (~(1 << 7));
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on the power powered down in PDS0
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION AON_LowPower_Exit_PDS0(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);

    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    BL602_Delay_US(20);

    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    BL602_Delay_US(60);

    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    BL602_Delay_US(20);

    /* power on wb */
    tmpVal = BL_RD_REG(AON_BASE, AON_MISC);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_SW_WB_EN_AON);
    BL_WR_REG(AON_BASE, AON_MISC, tmpVal);

    /* ungating Clock */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_CGEN_CFG0);
    tmpVal = tmpVal | ((1 << 6));
    tmpVal = tmpVal | ((1 << 7));
    BL_WR_REG(GLB_BASE, GLB_CGEN_CFG0, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on the power powered down in PDS0
 *
 * @param  delay: None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Set_LDO11_SOC_Sstart_Delay(uint8_t delay)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM((delay <= 0x3));

    /* config ldo11soc_sstart_delay_aon */
    tmpVal = BL_RD_REG(AON_BASE, AON_LDO11SOC_AND_DCTEST);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_LDO11SOC_SSTART_DELAY_AON, delay);
    BL_WR_REG(AON_BASE, AON_LDO11SOC_AND_DCTEST, tmpVal);

    return SUCCESS;
}

/*@} end of group AON_Public_Functions */

/*@} end of group AON */

/*@} end of group BL602_Peripheral_Driver */
