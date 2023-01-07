/**
  ******************************************************************************
  * @file    bl808p_psram_ctrl.c
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
#include "bl808_glb.h"
#include "bl808_psram.h"
#include "psram_reg.h"

/** @addtogroup  BL808P_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PSRAM_CTRL
 *  @{
 */

/** @defgroup  PSRAM_CTRL_Private_Macros
 *  @{
 */

/*@} end of group PSRAM_CTRL_Private_Macros */

/** @defgroup  PSRAM_CTRL_Private_Types
 *  @{
 */

/*@} end of group PSRAM_CTRL_Private_Types */

/** @defgroup  PSRAM_CTRL_Private_Variables
 *  @{
 */

/*@} end of group PSRAM_CTRL_Private_Variables */

/** @defgroup  PSRAM_CTRL_Global_Variables
 *  @{
 */

/*@} end of group PSRAM_CTRL_Global_Variables */

/** @defgroup  PSRAM_CTRL_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PSRAM_CTRL_Private_Fun_Declaration */

/** @defgroup  PSRAM_CTRL_Private_Functions
 *  @{
 */

/*@} end of group PSRAM_CTRL_Private_Functions */

/** @defgroup  PSRAM_CTRL_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Init PSRAM controller
 *
 * @param  PSRAM_ID: PSRAM vendor
 * @param  psramCtrlCfg: PSRAM controller IO type
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_Init(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_Cfg_Type *psramCtrlCfg)
{
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));
    CHECK_PARAM(IS_PSRAM_CTRL_CFG_TYPE(psramCtrlCfg));

    //PSRAM initial sequence
    arch_delay_us(150);
    /* set psram ctrl x8 */
    tmpVal = BL_RD_REG(GLB_BASE, GLB_PARM_CFG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GLB_REG_SEL_PSRAM0_X16, 0x0);
    BL_WR_REG(GLB_BASE, GLB_PARM_CFG0, tmpVal);

    /* set psram dqs delay 0xfff0 */
    tmpVal = BL_RD_REG(psram_base, PSRAM_ROUGH_DELAY_CTRL5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_ROUGH_SEL_I_DQS0, 0xfff0);
    BL_WR_REG(psram_base, PSRAM_ROUGH_DELAY_CTRL5, tmpVal);

    /* Set vendor and mode for psram controller */
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    //	tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_PCK_S_DIV, 0x1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_VENDOR_SEL, psramCtrlCfg->vendor);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_X16_MODE, psramCtrlCfg->ioMode);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    tmpVal = BL_RD_REG(psram_base, PSRAM_MANUAL_CONTROL2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_ADDR_MASK, psramCtrlCfg->size);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_DQS_REL_VAL, 0x1f);
    BL_WR_REG(psram_base, PSRAM_MANUAL_CONTROL2, tmpVal);

    if (psramCtrlCfg->vendor == PSRAM_CTRL_VENDOR_WINBOND && psramCtrlCfg->ioMode == PSRAM_CTRL_X16_MODE && psramCtrlCfg->size == PSRAM_SIZE_16MB) {
        //If using W957D6NKR, must set reg_wb_hyper3 bit to 1
        tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
        tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_REG_WB_HYPER3);
        BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  PSRAM Ctrl request access
 *
 * @param  PSRAM_ID: PSRAM ID
 *
 * @return None
 *
*******************************************************************************/
static void PSram_Ctrl_Request(PSRAM_ID_Type PSRAM_ID)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    //start configure request
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_CONFIG_REQ, 1);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //Waiting for the authorization
    do {
        tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_REG_CONFIG_GNT));
}

/****************************************************************************/ /**
 * @brief  PSRAM Ctrl release access
 *
 * @param  PSRAM_ID: PSRAM ID
 *
 * @return None
 *
*******************************************************************************/
static void PSram_Ctrl_Release(PSRAM_ID_Type PSRAM_ID)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    //clear start configure request
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_CONFIG_REQ, 0);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Read register for winbond PSRAM
 *
 * @param  PSRAM_ID: PSRAM ID
 * @param  reg_addr: PSRAM Register ID CR0 or CR1
 * @param  regVal: read Reister value
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_Winbond_Read_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_Winbond_Cfg_Reg_Type reg_addr, uint16_t *regVal)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_WINBON_CFG_TYPE(reg_cfg));
    CHECK_PARAM(IS_PSRAM_CTRL_WINBOND_CFG_REG_TYPE(reg_addr));
    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    PSram_Ctrl_Request(PSRAM_ID);

    //configure pSRAM register,select reg_addr CR0 or CR1
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_REG_SEL, reg_addr);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //start psram configure
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_CONFIG_R_PUSLE, 1);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //waiting confiure complete
    do {
        tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_STS_CONFIG_R_DONE));

    //read reg data form sts_config_read
    tmpVal = BL_RD_REG(psram_base, PSRAM_MANUAL_CONTROL);
    *regVal = (uint16_t)(tmpVal >> 16);

    PSram_Ctrl_Release(PSRAM_ID);
}

/****************************************************************************/ /**
 * @brief  write register for winbond PSRAM
 *
 * @param  PSRAM_ID: PSRAM ID
 * @param  reg_addr: PSRAM Register ID CR0 or CR1
 * @param  reg_cfg: winbond configuration
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_Winbond_Write_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_Winbond_Cfg_Reg_Type reg_addr, PSRAM_Winbond_Cfg_Type *reg_cfg)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);
    PSRAM_Ctrl_Size_Type psramDensity;

    CHECK_PARAM(IS_PSRAM_WINBON_CFG_TYPE(reg_cfg));
    CHECK_PARAM(IS_PSRAM_CTRL_WINBOND_CFG_REG_TYPE(reg_addr));
    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    PSram_Ctrl_Request(PSRAM_ID);

    //configure Winbond register
    tmpVal = BL_RD_REG(psram_base, PSRAM_WINBOND_PSRAM_CONFIGURE);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_LATENCY, reg_cfg->latency);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_DRIVE_ST, reg_cfg->driveStrength);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_HYBRID_EN, reg_cfg->brustType);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_BURST_LENGTH, reg_cfg->brustLen);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_FIX_LATENCY, reg_cfg->fixedLatency);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_DPD_DIS, reg_cfg->disDeepPowerDownMode);

    psramDensity = BL_GET_REG_BITS_VAL(BL_RD_REG(psram_base, PSRAM_MANUAL_CONTROL2), PSRAM_REG_ADDR_MASK);

    if (psramDensity == PSRAM_SIZE_4MB) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_PASR, reg_cfg->PASR);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_PASR, reg_cfg->PASR << 2);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_HYBRID_SLP, reg_cfg->hybridSleepMode);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_IPD, reg_cfg->inputPowerDownMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_MCLK_TYPE, reg_cfg->clockType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_LINEAR_DIS, reg_cfg->linear_dis);
    /* W955D8MKY don't support sw rst */
    /* tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_SW_RST, reg_cfg->rst); */

    BL_WR_REG(psram_base, PSRAM_WINBOND_PSRAM_CONFIGURE, tmpVal);

    //configure pSRAM register,select reg_addr CR0 or CR1
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_REG_SEL, reg_addr);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //start psram configure
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_CONFIG_W_PUSLE, 1);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //waiting confiure complete
    do {
        tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_STS_CONFIG_W_DONE));

    PSram_Ctrl_Release(PSRAM_ID);
}

/****************************************************************************/ /**
 * @brief  Read register for APmemory PSRAM
 *
 * @param  PSRAM_ID: PSRAM ID
 * @param  reg_addr: PSRAM Register ID CR0 or CR1
 * @param  regVal: read Reister value
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_ApMem_Read_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_ApMem_Cfg_Reg_Type reg_addr, uint16_t *regVal)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_WINBON_CFG_TYPE(reg_cfg));
    CHECK_PARAM(IS_PSRAM_CTRL_APMEM_CFG_REG_TYPE(reg_addr));
    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    PSram_Ctrl_Request(PSRAM_ID);

    //configure pSRAM register,select reg_addr CR0 or CR1
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_REG_SEL, reg_addr);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //start psram configure
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_CONFIG_R_PUSLE, 1);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //waiting confiure complete
    do {
        tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_STS_CONFIG_R_DONE));

    //read reg data form sts_config_read
    tmpVal = BL_RD_REG(psram_base, PSRAM_MANUAL_CONTROL);
    *regVal = (uint16_t)(tmpVal >> 16);

    PSram_Ctrl_Release(PSRAM_ID);
}

/****************************************************************************/ /**
 * @brief  write register for Apmemory PSRAM
 *
 * @param  PSRAM_ID: PSRAM ID
 * @param  reg_addr: PSRAM Register ID
 * @param  reg_cfg: winbond configuration
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_ApMem_Write_Reg(PSRAM_ID_Type PSRAM_ID, PSRAM_Ctrl_ApMem_Cfg_Reg_Type reg_addr, PSRAM_APMemory_Cfg_Type *reg_cfg)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_WINBON_CFG_TYPE(reg_cfg));
    CHECK_PARAM(IS_PSRAM_CTRL_APMEM_CFG_REG_TYPE(reg_addr));
    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    PSram_Ctrl_Request(PSRAM_ID);

    //configure Winbond register
    tmpVal = BL_RD_REG(psram_base, PSRAM_APMEMORY_PSRAM_CONFIGURE);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_R_LATENCY_TYPE, reg_cfg->fixedLatency);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_R_LATENCY_CODE, reg_cfg->readLatency);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_RF, reg_cfg->refreshFreq);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_DRIVE_ST, reg_cfg->driveStrength);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_W_LATENCY_CODE, reg_cfg->writeLatency);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_PASR, reg_cfg->PASR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_SLEEP, reg_cfg->halfSleepModeEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_DPD, reg_cfg->deepPowerDownModeEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_RBX, reg_cfg->crossBoundaryEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_BURST_TYPE, reg_cfg->brustType);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_AP_BURST_LENGTH, reg_cfg->brustLen);

    BL_WR_REG(psram_base, PSRAM_APMEMORY_PSRAM_CONFIGURE, tmpVal);

    //configure pSRAM register,select reg_addr CR0 or CR1
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_WB_REG_SEL, reg_addr);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //start psram configure
    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_CONFIG_W_PUSLE, 1);
    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);

    //waiting confiure complete
    do {
        tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);
    } while (!BL_IS_REG_BIT_SET(tmpVal, PSRAM_STS_CONFIG_W_DONE));

    PSram_Ctrl_Release(PSRAM_ID);
}

/****************************************************************************/ /**
 * @brief  write register for apmemory PSRAM
 *
 * @param  PSRAM_ID: apmemory configuration register type
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_ApMem_Reset(PSRAM_ID_Type PSRAM_ID)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    tmpVal = BL_RD_REG(psram_base, PSRAM_APMEMORY_PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_REG_GLB_RESET_PULSE);
    BL_WR_REG(psram_base, PSRAM_APMEMORY_PSRAM_CONFIGURE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  write register for Winbond PSRAM
 *
 * @param  PSRAM_ID: Winbond configuration register type
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_Winbond_Reset(PSRAM_ID_Type PSRAM_ID)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    tmpVal = BL_RD_REG(psram_base, PSRAM_WINBOND_PSRAM_CONFIGURE);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_REG_WB_SW_RST);
    BL_WR_REG(psram_base, PSRAM_WINBOND_PSRAM_CONFIGURE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set clk type diff/single
 *
 * @param  PSRAM_ID: PSRAM ID
 * @param  clkSel: Clock Type
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_CK_Sel(PSRAM_ID_Type PSRAM_ID, PSRAM_Clock_Type clkSel)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    tmpVal = BL_RD_REG(psram_base, PSRAM_CONFIGURE);

    if (clkSel == PSRAM_CLOCK_DIFF) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_REG_CLKN_FREE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_REG_CLKN_FREE);
    }

    BL_WR_REG(psram_base, PSRAM_CONFIGURE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  get timeout status
 *
 * @param  PSRAM_ID: PSRAM ID
 *
 * @return FLAG
 *
*******************************************************************************/
uint8_t PSram_Ctrl_Get_Timeout_Flag(PSRAM_ID_Type PSRAM_ID)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    tmpVal = BL_RD_REG(psram_base, PSRAM_TIMEOUT_REG);

    return BL_IS_REG_BIT_SET(tmpVal, PSRAM_STS_TIMEOUT);
}

/****************************************************************************/ /**
 * @brief  PSram_Ctrl_Clear_Timout_Flag
 *
 * @param  PSRAM_ID: PSRAM ID
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_Clear_Timout_Flag(PSRAM_ID_Type PSRAM_ID)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    tmpVal = BL_RD_REG(psram_base, PSRAM_TIMEOUT_REG);
    tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_REG_TIMEOUT_CLR);
    BL_WR_REG(psram_base, PSRAM_TIMEOUT_REG, tmpVal);

    tmpVal = BL_RD_REG(psram_base, PSRAM_TIMEOUT_REG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_REG_TIMEOUT_CLR);
    BL_WR_REG(psram_base, PSRAM_TIMEOUT_REG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set clk type diff/single
 *
 * @param  PSRAM_ID: PSRAM ID
 * @param  enable: Enable or not
 * @param  timeoutThr: timeoutThr
 *
 * @return None
 *
*******************************************************************************/
void PSram_Ctrl_Debug_Timout(PSRAM_ID_Type PSRAM_ID, uint8_t enable, uint32_t timeoutThr)
{
    uint32_t tmpVal = 0;
    uint32_t psram_base = PSRAM_CTRL_BASE + (0x1000 * PSRAM_ID);

    CHECK_PARAM(IS_PSRAM_ID_TYPE(PSRAM_ID));

    tmpVal = BL_RD_REG(psram_base, PSRAM_TIMEOUT_REG);

    if (enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PSRAM_REG_TIMEOUT_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, PSRAM_REG_TIMEOUT_EN);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PSRAM_REG_TIMEOUT_CNT, timeoutThr);

    BL_WR_REG(psram_base, PSRAM_TIMEOUT_REG, tmpVal);
}

/*@} end of group PSRAM_CTRL_Public_Functions */

/*@} end of group PSRAM_CTRL */

/*@} end of group BL808P_Peripheral_Driver */
