/**
  ******************************************************************************
  * @file    bl808_aon.c
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

#include "bl808_aon.h"

/** @addtogroup  BL808_Peripheral_Driver
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
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_On_MBG(void)
{
    uint32_t tmpVal = 0;

    /* Power up RF for PLL to work */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(55);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off MXX band gap
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_Off_MBG(void)
{
    uint32_t tmpVal = 0;

    /* Power OFF */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power on XTAL
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
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
        arch_delay_us(10);
        timeOut++;
        tmpVal = BL_RD_REG(AON_BASE, AON_TSEN);
    } while (!BL_IS_REG_BIT_SET(tmpVal, AON_XTAL_RDY) && timeOut < 120);

    if (timeOut >= 120) {
        return TIMEOUT;
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set XTAL cap code
 *
 * @param  capIn: Cap code in
 * @param  capOut: Cap code out
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION AON_Set_Xtal_CapCode(uint8_t capIn, uint8_t capOut)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_XTAL_CFG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_XTAL_CAPCODE_IN_AON, capIn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_XTAL_CAPCODE_OUT_AON, capOut);
    BL_WR_REG(AON_BASE, AON_XTAL_CFG, tmpVal);

    arch_delay_us(100);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Get XTAL cap code
 *
 * @param  None
 *
 * @return Cap code
 *
*******************************************************************************/
uint8_t ATTR_CLOCK_SECTION AON_Get_Xtal_CapCode(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_XTAL_CFG);

    return BL_GET_REG_BITS_VAL(tmpVal, AON_XTAL_CAPCODE_IN_AON);
}

/****************************************************************************/ /**
 * @brief  Power off XTAL
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION AON_Power_Off_XTAL(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_XTAL_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_XTAL_BUF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power on bandgap system
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_BG(void)
{
    uint32_t tmpVal = 0;

    /* power up RF for PLL to work */
    tmpVal = BL_RD_REG(AON_BASE, AON_BG_SYS_TOP);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_BG_SYS_AON);
    BL_WR_REG(AON_BASE, AON_BG_SYS_TOP, tmpVal);

    arch_delay_us(55);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off bandgap system
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_BG(void)
{
    uint32_t tmpVal = 0;

    /* power up RF for PLL to work */
    tmpVal = BL_RD_REG(AON_BASE, AON_BG_SYS_TOP);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_BG_SYS_AON);
    BL_WR_REG(AON_BASE, AON_BG_SYS_TOP, tmpVal);

    arch_delay_us(55);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  trim dcdc11 vout
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION AON_Trim_DCDC11_Vout(void)
{
    Efuse_Ana_DCDC11_Trim_Type trim;
    uint32_t tmpVal = 0;

    EF_Ctrl_Read_DCDC11_Trim(&trim);
    if (trim.trimDcdc11VoutAonEn) {
        if (trim.trimDcdc11VoutAonParity == EF_Ctrl_Get_Trim_Parity(trim.trimDcdc11VoutAon, 4)) {
            tmpVal = BL_RD_REG(AON_BASE, AON_DCDC_TOP_0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC11_VOUT_TRIM_AON, trim.trimDcdc11VoutAon);
            BL_WR_REG(AON_BASE, AON_DCDC_TOP_0, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  trim dcdc18 vout
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION AON_Trim_DCDC18_Vout(void)
{
    Efuse_Ana_DCDC18_Trim_Type trim;
    uint32_t tmpVal = 0;

    EF_Ctrl_Read_DCDC18_Trim(&trim);
    if (trim.trimDcdc18VoutAonEn) {
        if (trim.trimDcdc18VoutAonParity == EF_Ctrl_Get_Trim_Parity(trim.trimDcdc18VoutAon, 4)) {
            tmpVal = BL_RD_REG(AON_BASE, AON_DCDC18_TOP_0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC18_VOUT_TRIM_AON, trim.trimDcdc18VoutAon);
            BL_WR_REG(AON_BASE, AON_DCDC18_TOP_0, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  trim usb20 rcal vout
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION AON_Trim_USB20_RCAL(void)
{
    Efuse_Ana_USB20RCAL_Trim_Type trim;
    uint32_t tmpVal = 0;

    EF_Ctrl_Read_USB20RCAL_Trim(&trim);
    if (trim.trimUsb20rcalAonEn) {
        if (trim.trimUsb20rcalAonParity == EF_Ctrl_Get_Trim_Parity(trim.trimUsb20rcalAon, 6)) {
            tmpVal = BL_RD_REG(AON_BASE, AON_PSW_IRRCV);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_USB20_RCAL_CODE_AON, trim.trimUsb20rcalAon);
            BL_WR_REG(AON_BASE, AON_PSW_IRRCV, tmpVal);
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Power on LDO15_RF
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_LDO15_RF(void)
{
    uint32_t tmpVal = 0;

    /* ldo15rf power on */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(90);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off LDO15_RF
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_LDO15_RF(void)
{
    uint32_t tmpVal = 0;

    /* ldo15rf power off */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power on source follow regular
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Power_On_SFReg(void)
{
    uint32_t tmpVal = 0;

    /* power on sfreg */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(10);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power off source follow regular
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Power_Off_SFReg(void)
{
    uint32_t tmpVal = 0;

    /* power off sfreg */
    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Power off the power can be shut down in PDS0
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
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

/****************************************************************************/ /**
 * @brief  Power on the power powered down in PDS0
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_LowPower_Exit_PDS0(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AON_BASE, AON_RF_TOP_AON);

    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_MBG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(20);

    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_LDO15RF_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(60);

    tmpVal = BL_SET_REG_BIT(tmpVal, AON_PU_SFREG_AON);
    BL_WR_REG(AON_BASE, AON_RF_TOP_AON, tmpVal);

    arch_delay_us(20);

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

/****************************************************************************/ /**
 * @brief  AON set DCDC11_Top voltage out
 *
 * @param  dcdcLevel: DCDC11_Top volatge level
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION AON_Set_DCDC11_Top_Vout(AON_DCDC_LEVEL_Type dcdcLevel)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_AON_DCDC_LEVEL_TYPE(dcdcLevel));

    tmpVal = BL_RD_REG(AON_BASE, AON_DCDC_TOP_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_DCDC11_VOUT_SEL_AON, dcdcLevel);
    BL_WR_REG(AON_BASE, AON_DCDC_TOP_0, tmpVal);

    return SUCCESS;
}
/*@} end of group AON_Public_Functions */

/*@} end of group AON */

/*@} end of group BL808_Peripheral_Driver */
