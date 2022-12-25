/**
  ******************************************************************************
  * @file    bl808_ef_ctrl.c
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
#include "bl808_ef_ctrl.h"
#include "ef_data_0_reg.h"
#include "ef_data_1_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SEC_EF_CTRL
 *  @{
 */

/** @defgroup  SEC_EF_CTRL_Private_Macros
 *  @{
 */
#define EF_CTRL_EFUSE_CYCLE_PROTECT (0xbf << 24)
#define EF_CTRL_EFUSE_CTRL_PROTECT  (0xbf << 8)
#define EF_CTRL_DFT_TIMEOUT_VAL     (320 * 1000)
#ifndef BOOTROM
#define EF_CTRL_LOAD_BEFORE_READ_R0 EF_Ctrl_Load_Efuse_R0()
#define EF_CTRL_LOAD_BEFORE_READ_R1 EF_Ctrl_Load_Efuse_R1()
#else
#define EF_CTRL_LOAD_BEFORE_READ_R0
#define EF_CTRL_LOAD_BEFORE_READ_R1
#endif
#define EF_CTRL_DATA0_CLEAR EF_Ctrl_Clear(0, 0, EF_CTRL_EFUSE_R0_SIZE / 4)
#define EF_CTRL_DATA1_CLEAR EF_Ctrl_Clear(1, 0, EF_CTRL_EFUSE_R1_SIZE / 4)

/*@} end of group SEC_EF_CTRL_Private_Macros */

/** @defgroup  SEC_EF_CTRL_Private_Types
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Private_Types */

/** @defgroup  SEC_EF_CTRL_Private_Variables
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Private_Variables */

/** @defgroup  SEC_EF_CTRL_Global_Variables
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Global_Variables */

/** @defgroup  SEC_EF_CTRL_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SEC_EF_CTRL_Private_Fun_Declaration */

/** @defgroup  SEC_EF_CTRL_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  get custom USB PID VID
 *
 * @param  PID
 *
 * @param  VID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION EF_Ctrl_Get_Customer_PIDVID(uint16_t pid[1], uint16_t vid[1])
{
    uint32_t tmpVal;

    EF_Ctrl_Read_Sw_Usage(4, &tmpVal);

    pid[0] = (uint16_t)(tmpVal & 0xFFFF);
    vid[0] = (uint16_t)(tmpVal >> 16);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Switch efuse region 0 control to AHB clock
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION EF_Ctrl_Sw_AHB_Clk_0(void)
{
    uint32_t tmpVal;
    uint32_t timeout = EF_CTRL_DFT_TIMEOUT_VAL;

    while (EF_Ctrl_Busy() == SET) {
        timeout--;

        if (timeout == 0) {
            break;
        }
    }

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);

    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  Switch efuse region 1 control to AHB clock
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION EF_Ctrl_Sw_AHB_Clk_1(void)
{
    uint32_t tmpVal;
    uint32_t timeout = EF_CTRL_DFT_TIMEOUT_VAL;

    while (EF_Ctrl_Busy() == SET) {
        timeout--;

        if (timeout == 0) {
            break;
        }
    }

    /* Note:ef_if_ctrl_1 has no EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS bit as ef_if_ctrl_0,
	   so we select it(them) in ef_if_ctrl_0 */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_1_RW_POS) |
             (0 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  Program efuse region 0
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION EF_Ctrl_Program_Efuse_0(void)
{
    uint32_t tmpVal;

    /* Select auto mode and select ef clock */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    /* Program */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (1 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (1 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    /* Add delay for POR to be stable */
    arch_delay_us(4);

    /* Trigger */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (1 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (1 << EF_CTRL_EF_IF_0_RW_POS) |
             (1 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  Program efuse region 1
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION EF_Ctrl_Program_Efuse_1(void)
{
    uint32_t tmpVal;

    /* Select auto mode and select ef clock */
    /* Note:ef_if_ctrl_1 has no EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS bit as ef_if_ctrl_0,
	   so we select it(them) in ef_if_ctrl_0 */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_1_RW_POS) |
             (0 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);

    /* Program */
    /* Note:ef_if_ctrl_1 has no EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS bit as ef_if_ctrl_0,
	so we select it(them) in ef_if_ctrl_0 */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (1 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    /* Add delay for POR to be stable */
    arch_delay_us(4);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (1 << EF_CTRL_EF_IF_1_RW_POS) |
             (0 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (1 << EF_CTRL_EF_IF_1_RW_POS) |
             (1 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  Load efuse region 0
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION EF_Ctrl_Load_Efuse_R0(void)
{
    uint32_t tmpVal;
    uint32_t timeout = EF_CTRL_DFT_TIMEOUT_VAL;

    EF_CTRL_DATA0_CLEAR;

    /* Trigger read */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (1 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    arch_delay_us(10);

    /* Wait for efuse control idle */
    do {
        tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0);
        timeout--;

        if (timeout == 0) {
            break;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_IF_0_BUSY) ||

             (!BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_IF_0_AUTOLOAD_DONE)));

    /* Switch to AHB clock */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  Load efuse region 1
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void EF_Ctrl_Load_Efuse_R1(void)
{
    uint32_t tmpVal;

    EF_CTRL_DATA1_CLEAR;

    /* Trigger read */
    /* Note:ef_if_ctrl_1 has no EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS bit as ef_if_ctrl_0,
	so we select it(them) in ef_if_ctrl_0 */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_1_RW_POS) |
             (0 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_1_RW_POS) |
             (1 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);

    arch_delay_us(10);

    /* Wait for efuse control idle */
    do {
        tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1);
    } while (BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_IF_1_BUSY));

    do {
        tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0);
    } while (!BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_IF_0_AUTOLOAD_DONE));

    /* Switch to AHB clock since often read efuse data after load */
    /* Note:ef_if_ctrl_1 has no EF_CTRL_EF_CLK_SAHB_DATA_SEL_POS bit as ef_if_ctrl_0,
	   so we select it(them) in ef_if_ctrl_0 */
    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_0_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_0_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_AUTO_RD_EN_POS) |
             (0 << EF_CTRL_EF_IF_POR_DIG_POS) |
             (1 << EF_CTRL_EF_IF_0_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_0_RW_POS) |
             (0 << EF_CTRL_EF_IF_0_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0, tmpVal);

    tmpVal = (EF_CTRL_EFUSE_CTRL_PROTECT) |
             (EF_CTRL_OP_MODE_AUTO << EF_CTRL_EF_IF_1_MANUAL_EN_POS) |
             (EF_CTRL_PARA_DFT << EF_CTRL_EF_IF_1_CYC_MODIFY_POS) |
             (1 << EF_CTRL_EF_IF_1_INT_CLR_POS) |
             (0 << EF_CTRL_EF_IF_1_RW_POS) |
             (0 << EF_CTRL_EF_IF_1_TRIG_POS);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  Check efuse busy status
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Sts_Type ATTR_TCM_SECTION EF_Ctrl_Busy(void)
{
    if (BL_IS_REG_BIT_SET(BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0), EF_CTRL_EF_IF_0_BUSY) ||
        BL_IS_REG_BIT_SET(BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_1), EF_CTRL_EF_IF_1_BUSY)) {
        return SET;
    }

    return RESET;
}
#endif

/****************************************************************************/ /**
 * @brief  Check efuse whether finish loading
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Sts_Type ATTR_TCM_SECTION EF_Ctrl_AutoLoad_Done(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_IF_CTRL_0);

    if (BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_IF_0_AUTOLOAD_DONE)) {
        return SET;
    } else {
        return RESET;
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse write debug password
 *
 * @param  slot: password slot0 or slot1
 * @param  passWdLow: password low 32 bits
 * @param  passWdHigh: password high 32 bits
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_Dbg_Pwd(uint8_t slot, uint32_t passWdLow, uint32_t passWdHigh, uint8_t program)
{
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    if (slot == 0) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD_LOW, passWdLow);
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD_HIGH, passWdHigh);
    } else if (slot == 1) {
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD2_LOW, passWdLow);
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD2_HIGH, passWdHigh);
    }

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read debug password
 *
 * @param  slot: password slot0 or slot1
 * @param  passWdLow: password low 32 bits pointer to store value
 * @param  passWdHigh: password high 32 bits pointer to store value
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Dbg_Pwd(uint8_t slot, uint32_t *passWdLow, uint32_t *passWdHigh)
{
    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    if (slot == 0) {
        *passWdLow = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD_LOW);
        *passWdHigh = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD_HIGH);
    } else if (slot == 1) {
        *passWdLow = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD2_LOW);
        *passWdHigh = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_DBG_PWD2_HIGH);
    }
}

/****************************************************************************/ /**
 * @brief  Efuse lock reading for passwd
 *
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Readlock_Dbg_Pwd(uint8_t program)
{
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);
    tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_RD_LOCK_DBG_PWD);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_LOCK, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse lock writing for passwd
 *
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Writelock_Dbg_Pwd(uint8_t program)
{
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);
    tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_WR_LOCK_DBG_PWD);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_LOCK, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read security configuration
 *
 * @param  cfg: security configuration pointer
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_Secure_Cfg(EF_Ctrl_Sec_Param_Type *cfg, uint8_t program)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_DBG_MODE, cfg->ef_dbg_mode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_DBG_JTAG_0_DIS, cfg->ef_dbg_jtag_0_dis);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_DBG_JTAG_1_DIS, cfg->ef_dbg_jtag_1_dis);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_SBOOT_EN, cfg->ef_sboot_en);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read security configuration
 *
 * @param  cfg: security configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Secure_Cfg(EF_Ctrl_Sec_Param_Type *cfg)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);

    cfg->ef_dbg_mode = (EF_Ctrl_Dbg_Mode_Type)BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_DBG_MODE);
    cfg->ef_dbg_jtag_0_dis = BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_DBG_JTAG_0_DIS);
    cfg->ef_dbg_jtag_1_dis = BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_DBG_JTAG_1_DIS);
    cfg->ef_sboot_en = BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_SBOOT_EN);
}

/****************************************************************************/ /**
 * @brief  Efuse write security boot configuration
 *
 * @param  sign[1]: Sign configuration pointer
 * @param  aes[1]: AES configuration pointer
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_Secure_Boot(EF_Ctrl_Sign_Type sign[1], EF_Ctrl_SF_AES_Type aes[1], uint8_t program)
{
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    if (aes[0] != EF_CTRL_SF_AES_NONE) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_SF_AES_MODE, aes[0]);
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0, tmpVal);
    }

    if (EF_CTRL_SIGN_NONE != sign[0]) {
        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_SBOOT_SIGN_MODE, sign[0]);
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_0, tmpVal);
    }

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse write security boot configuration
 *
 * @param  aes[2]: AES configuration pointer
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Secure_Boot(EF_Ctrl_SF_AES_Type aes[2])
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);

    aes[1] = aes[0] = (EF_Ctrl_SF_AES_Type)BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_SF_AES_MODE);
}

/****************************************************************************/ /**
 * @brief  Efuse read xtal trim rc32m configuration
 *
 * @param  forceNoTrim: force no trim
 * @param  noXtal: no xtal
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Xtal_Trim_RC32M(uint8_t *forceNoTrim, uint8_t *noXtal)
{
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);

    *forceNoTrim = BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_FORCE_NO_TRIM);
    *noXtal = BL_GET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_NO_XTAL);
}

/****************************************************************************/ /**
 * @brief  Efuse Set sf key re sel
 *
 * @param  ef_sf_key_re_sel: Efuse sf key re sel
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Set_sf_key_re_sel(uint8_t ef_sf_key_re_sel)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, EF_DATA_0_EF_SF_KEY_RE_SEL, ef_sf_key_re_sel);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_CFG_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Analog Trim parity calculate
 *
 * @param  val: Value of efuse trim data
 * @param  len: Length of bit to calculate
 *
 * @return Parity bit value
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
uint8_t ATTR_CLOCK_SECTION EF_Ctrl_Get_Trim_Parity(uint32_t val, uint8_t len)
{
    uint8_t cnt = 0;
    uint8_t i = 0;

    for (i = 0; i < len; i++) {
        if (val & (1 << i)) {
            cnt++;
        }
    }

    return cnt & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read DCDC11 trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_DCDC11_Trim(Efuse_Ana_DCDC11_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W3);
    trim->trimDcdc11VoutAon = (tmpVal >> 26) & 0x0f;
    trim->trimDcdc11VoutAonParity = (tmpVal >> 30) & 0x01;
    trim->trimDcdc11VoutAonEn = (tmpVal >> 31) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read DCDC18 trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_DCDC18_Trim(Efuse_Ana_DCDC18_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W3);
    trim->trimDcdc18VoutAon = (tmpVal >> 20) & 0x0f;
    trim->trimDcdc18VoutAonParity = (tmpVal >> 24) & 0x01;
    trim->trimDcdc18VoutAonEn = (tmpVal >> 25) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read LDO18FLASH trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_LDO18FLASH_Trim(Efuse_Ana_LDO18FLASH_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W3);
    trim->trimLdo18flashVoutAon = (tmpVal >> 26) & 0x0f;
    trim->trimLdo18flashVoutAonParity = (tmpVal >> 30) & 0x01;
    trim->trimLdo18flashVoutAonEn = (tmpVal >> 31) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read USB20RCAL trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_USB20RCAL_Trim(Efuse_Ana_USB20RCAL_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_2);
    trim->trimUsb20rcalAon = (tmpVal >> 8) & 0x3f;
    trim->trimUsb20rcalAonParity = (tmpVal >> 14) & 0x01;
    trim->trimUsb20rcalAonEn = (tmpVal >> 15) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read RC32M trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_RC32M_Trim(Efuse_Ana_RC32M_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);
    trim->trimRc32mCodeFrExt = (tmpVal >> 4) & 0xff;
    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W3);
    trim->trimRc32mCodeFrExtParity = (tmpVal >> 0) & 0x01;
    trim->trimRc32mExtCodeEn = (tmpVal >> 1) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read RC32K trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_RC32K_Trim(Efuse_Ana_RC32K_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_1();

    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_KEY_SLOT_10_W3);
    trim->trimRc32kCodeFrExt = (tmpVal >> 8) & 0x3ff;
    trim->trimRc32kCodeFrExtParity = (tmpVal >> 18) & 0x01;
    trim->trimRc32kExtCodeEn = (tmpVal >> 19) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief
 *
 * @param
 *
 * @return
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_CLOCK_SECTION EF_Ctrl_Read_LDO18IO_Vout_Trim(Efuse_Ana_LDO18IO_VOUT_Trim_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W3);
    trim->trimLdo18ioVoutVal = (tmpVal >> 14) & 0x0f;
    trim->trimLdo18ioVoutParity = (tmpVal >> 18) & 0x01;
    trim->trimLdo18ioVoutEn = (tmpVal >> 19) & 0x01;
}
#endif

/****************************************************************************/ /**
 * @brief  Efuse read TSEN trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void ATTR_CLOCK_SECTION EF_Ctrl_Read_TSEN_Trim(Efuse_TSEN_Refcode_Corner_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_1();

    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_EF_DAT_1_RSVD_0);
    trim->tsenRefcodeCorner = (tmpVal >> 0) & 0xfff;
    trim->tsenRefcodeCornerParity = (tmpVal >> 12) & 0x01;
    trim->tsenRefcodeCornerEn = (tmpVal >> 13) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse read ADC Gain trim
 *
 * @param  trim: Trim data pointer
 *
 * @return None
 *
*******************************************************************************/
void ATTR_CLOCK_SECTION EF_Ctrl_Read_ADC_Gain_Trim(Efuse_ADC_Gain_Coeff_Type *trim)
{
    uint32_t tmpVal = 0;
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_1();

    EF_CTRL_LOAD_BEFORE_READ_R1;

    tmpVal = BL_RD_REG(EF_DATA_BASE,EF_DATA_1_EF_DAT_1_RSVD_0);
    trim->adcGainCoeff = (tmpVal >> 14) & 0xfff;
    trim->adcGainCoeffParity = (tmpVal >> 26) & 0x01;
    trim->adcGainCoeffEn = (tmpVal >> 27) & 0x01;
}

/****************************************************************************/ /**
 * @brief  Efuse write software usage
 *
 * @param  index: index of software usage
 * @param  usage: usage value
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_Sw_Usage(uint32_t index, uint32_t usage, uint8_t program)
{
    /* switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    switch (index) {
        case 0:
            BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_0, usage);
            break;

        case 1:
            BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_1, usage);
            break;

        case 2:
            BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_2, usage);
            break;

        case 3:
            BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3, usage);
            break;

        case 4:
            BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W0, usage);
            break;

        default:
            break;
    }

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read software usage
 *
 * @param  index: index of software usage
 * @param  usage: usage value
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Sw_Usage(uint32_t index, uint32_t *usage)
{
    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    EF_CTRL_LOAD_BEFORE_READ_R0;

    switch (index) {
        case 0:
            *usage = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_0);
            break;

        case 1:
            *usage = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_1);
            break;

        case 2:
            *usage = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_2);
            break;

        case 3:
            *usage = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_SW_USAGE_3);
            break;

        case 4:
            *usage = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_KEY_SLOT_11_W0);
            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read software usage
 *
 * @param  index: index of software usage
 * @param  program: usage value
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Writelock_Sw_Usage(uint32_t index, uint8_t program)
{
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);

    if (index == 0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_WR_LOCK_SW_USAGE_0);
    } else if (index == 1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_WR_LOCK_SW_USAGE_1);
    } else if (index == 2) {
        tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_WR_LOCK_SW_USAGE_2);
    } else if (index == 3) {
        tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_WR_LOCK_SW_USAGE_3);
    }

    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_LOCK, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse write MAC address
 *
 * @param  mac[6]: MAC address buffer
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_MAC_Address(uint8_t mac[6], uint8_t program)
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    /* The low 32 bits */
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_LOW, BL_RDWD_FRM_BYTEP(maclow));
    /* The high 16 bits */
    tmpVal = machigh[0] + (machigh[1] << 8);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Efuse Ctrl get zero bit count
 *
 * @param  val: Value to count
 *
 * @return Zero bit count
 *
*******************************************************************************/
static uint32_t EF_Ctrl_Get_Byte_Zero_Cnt(uint8_t val)
{
    uint32_t cnt = 0;
    uint32_t i = 0;

    for (i = 0; i < 8; i++) {
        if ((val & (1 << i)) == 0) {
            cnt += 1;
        }
    }

    return cnt;
}

/****************************************************************************/ /**
 * @brief  Efuse read MAC address
 *
 * @param  mac[6]: MAC address buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EF_Ctrl_Read_MAC_Address(uint8_t mac[6])
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpVal;
    uint32_t i = 0;
    uint32_t cnt = 0;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_LOW);
    BL_WRWD_TO_BYTEP(maclow, tmpVal);

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH);
    machigh[0] = tmpVal & 0xff;
    machigh[1] = (tmpVal >> 8) & 0xff;

    /* Check parity */
    for (i = 0; i < 6; i++) {
        cnt += EF_Ctrl_Get_Byte_Zero_Cnt(mac[i]);
    }

    if ((cnt & 0x3f) == ((tmpVal >> 16) & 0x3f)) {
        /* Change to network order */
        for (i = 0; i < 3; i++) {
            tmpVal = mac[i];
            mac[i] = mac[5 - i];
            mac[5 - i] = tmpVal;
        }

        return SUCCESS;
    } else {
        return ERROR;
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read MAC address
 *
 * @param  mac[7]: MAC address buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EF_Ctrl_Read_MAC_Address_Raw(uint8_t mac[7])
{
    uint8_t *maclow = (uint8_t *)mac;
    uint8_t *machigh = (uint8_t *)(mac + 4);
    uint32_t tmpVal;

    /* Trigger read data from efuse */
    EF_CTRL_LOAD_BEFORE_READ_R0;

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_LOW);
    BL_WRWD_TO_BYTEP(maclow, tmpVal);

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_EF_WIFI_MAC_HIGH);
    machigh[0] = tmpVal & 0xff;
    machigh[1] = (tmpVal >> 8) & 0xff;
    machigh[2] = (tmpVal >> 16) & 0xff;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Efuse lock writing for MAC address
 *
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Writelock_MAC_Address(uint8_t program)
{
    uint32_t tmpVal;

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);
    tmpVal = BL_SET_REG_BIT(tmpVal, EF_DATA_0_WR_LOCK_WIFI_MAC);
    BL_WR_REG(EF_DATA_BASE, EF_DATA_0_LOCK, tmpVal);

    if (program) {
        EF_Ctrl_Program_Efuse_0();
    }
}

/****************************************************************************/ /**
 * @brief  Whether a value bits is all zero
 *
 * @param  val: value to check
 * @param  start: start bit
 * @param  len: total length of bits to check
 *
 * @return 1 for all bits zero 0 for others
 *
*******************************************************************************/
uint8_t EF_Ctrl_Is_All_Bits_Zero(uint32_t val, uint8_t start, uint8_t len)
{
    uint32_t mask = 0;

    val = (val >> start);

    if (len >= 32) {
        mask = 0xffffffff;
    } else {
        mask = (1 << len) - 1;
    }

    if ((val & mask) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read chip ID
 *
 * @param  chipID[8]: Chip ID buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EF_Ctrl_Read_Chip_ID(uint8_t chipID[8])
{
    chipID[6] = 0;
    chipID[7] = 0;
    return EF_Ctrl_Read_MAC_Address_Raw(chipID);
}

/****************************************************************************/ /**
 * @brief  Efuse write AES key
 *
 * @param  keyRegion: efuse key region
 * @param  index: index of key slot
 * @param  keyData: key data buffer
 * @param  len: key data length in words
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Write_AES_Key(uint8_t index, uint32_t *keyData, uint32_t len, uint8_t program)
{
    uint32_t *pAESKeyStart0 = (uint32_t *)(EF_DATA_BASE + 0x1C);
    uint32_t *pAESKeyStart1 = (uint32_t *)(EF_DATA_BASE + 0x80);

    /* slot_w0~slot_w3,slot_w11 in ef_data0 
       slot_w4~slot_w10,in ef_data1 */

    if ((index <= 3) || (index == 11)) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        index = ((index == 11) ? 5 : index);

        /* Every key is 4 words len*/

        ARCH_MemCpy4(pAESKeyStart0 + index * 4, keyData, len);

        if (program) {
            EF_Ctrl_Program_Efuse_0();
        }
    } else if ((index < 11) && (index > 3)) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_1();

        index = index - 4;

        /* Every key is 4 words len*/
        ARCH_MemCpy4(pAESKeyStart1 + index * 4, keyData, len);

        if (program) {
            EF_Ctrl_Program_Efuse_1();
        }
    }
}

/****************************************************************************/ /**
 * @brief  Efuse read AES key from specified region and index
 *
 * @param  keyRegion: efuse key region
 * @param  index: index of key slot
 * @param  keyData: key data buffer
 * @param  len: key data length in words
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_AES_Key(uint8_t index, uint32_t *keyData, uint32_t len)
{
    uint32_t *pAESKeyStart0 = (uint32_t *)(EF_DATA_BASE + 0x1C);
    uint32_t *pAESKeyStart1 = (uint32_t *)(EF_DATA_BASE + 0x80);

    if ((index <= 3) || (index == 11)) {
        /* Trigger read data from efuse*/
        EF_CTRL_LOAD_BEFORE_READ_R0;

        index = ((index == 11) ? 5 : index);

        /* Every key is 4 words len*/
        ARCH_MemCpy4(keyData, pAESKeyStart0 + index * 4, len);
    } else if ((index < 11) && (index > 3)) {
        /* Trigger read data from efuse*/
        EF_CTRL_LOAD_BEFORE_READ_R1;
        index = index - 4;
        /* Every key is 4 words len*/
        ARCH_MemCpy4(keyData, pAESKeyStart1 + index * 4, len);
    }
}

/****************************************************************************/ /**
 * @brief  Efuse lock writing for aes key
 *
 * @param  keyRegion: efuse key region
 * @param  index: index of key slot
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Writelock_AES_Key(uint8_t index, uint8_t program)
{
    uint32_t tmpVal;

    if ((index <= 3) || (index == 11)) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        index = ((index == 11) ? 8 : index);

        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);
        tmpVal |= (1 << (index + 17));
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_LOCK, tmpVal);

        if (program) {
            EF_Ctrl_Program_Efuse_0();
        }
    } else if ((index < 11) && (index > 3)) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_1();

        index = index - 4;

        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_LOCK);
        tmpVal |= (1 << (index + 15));
        BL_WR_REG(EF_DATA_BASE, EF_DATA_1_LOCK, tmpVal);

        if (program) {
            EF_Ctrl_Program_Efuse_1();
        }
    }
}

/****************************************************************************/ /**
 * @brief  Efuse lock reading for aes key
 *
 * @param  keyRegion: efuse key region
 * @param  index: index of key slot
 * @param  program: program to efuse entity or not
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Readlock_AES_Key(uint8_t index, uint8_t program)
{
    uint32_t tmpVal;

    if ((index <= 3) || (index == 11)) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        index = ((index == 11) ? 4 : index);

        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_0_LOCK);
        tmpVal |= (1 << (index + 27));
        BL_WR_REG(EF_DATA_BASE, EF_DATA_0_LOCK, tmpVal);

        if (program) {
            EF_Ctrl_Program_Efuse_0();
        }
    } else if ((index < 11) && (index > 3)) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_1();

        index = index - 4;

        tmpVal = BL_RD_REG(EF_DATA_BASE, EF_DATA_1_LOCK);
        tmpVal |= (1 << (index + 25));
        BL_WR_REG(EF_DATA_BASE, EF_DATA_1_LOCK, tmpVal);

        if (program) {
            EF_Ctrl_Program_Efuse_1();
        }
    }
}

/****************************************************************************/ /**
 * @brief  Program data to efuse region 0
 *
 * @param  index: index of efuse in word
 * @param  data: data buffer
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Program_Direct_R0(uint32_t index, uint32_t *data, uint32_t len)
{
    uint32_t *pEfuseStart0 = (uint32_t *)(EF_DATA_BASE + 0x00);

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_0();

    /* Add delay for CLK to be stable */
    arch_delay_us(4);

    if (data != NULL) {
        ARCH_MemCpy4(pEfuseStart0 + index, data, len);
    }

    EF_Ctrl_Program_Efuse_0();
}

/****************************************************************************/ /**
 * @brief  Program data to efuse region 1
 *
 * @param  index: index of efuse in word
 * @param  data: data buffer
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Program_Direct_R1(uint32_t index, uint32_t *data, uint32_t len)
{
    uint32_t *pEfuseStart1 = (uint32_t *)(EF_DATA_BASE + 0x80);

    /* Switch to AHB clock */
    EF_Ctrl_Sw_AHB_Clk_1();

    /* Add delay for CLK to be stable */
    arch_delay_us(4);

    if (data != NULL) {
        ARCH_MemCpy4(pEfuseStart1 + index, data, len);
    }

    EF_Ctrl_Program_Efuse_1();
}

/****************************************************************************/ /**
 * @brief  Read data from efuse region 0
 *
 * @param  index: index of efuse in word
 * @param  data: data buffer
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Direct_R0(uint32_t index, uint32_t *data, uint32_t len)
{
    uint32_t *pEfuseStart0 = (uint32_t *)(EF_DATA_BASE + 0x00);

    EF_CTRL_LOAD_BEFORE_READ_R0;

    ARCH_MemCpy4(data, pEfuseStart0 + index, len);
}

/****************************************************************************/ /**
 * @brief  Read data from efuse region 1
 *
 * @param  index: index of efuse in word
 * @param  data: data buffer
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Direct_R1(uint32_t index, uint32_t *data, uint32_t len)
{
    uint32_t *pEfuseStart1 = (uint32_t *)(EF_DATA_BASE + 0x80);

    EF_CTRL_LOAD_BEFORE_READ_R1;

    ARCH_MemCpy4(data, pEfuseStart1 + index, len);
}

/****************************************************************************/ /**
 * @brief  Program data to efuse entity
 *
 * @param  region: index of efuse region
 * @param  index: index of efuse in word
 * @param  data: data buffer
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Program_Direct(uint32_t region, uint32_t index, uint32_t *data, uint32_t len)
{
    if (region == 0) {
        EF_Ctrl_Program_Direct_R0(index, data, len);
    } else if (region == 1) {
        EF_Ctrl_Program_Direct_R1(index, data, len);
    }
}

/****************************************************************************/ /**
 * @brief  Read efuse from register
 *
 * @param  region: index of efuse region
 * @param  index: index of efuse in word
 * @param  data: data buffer
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Read_Direct(uint32_t region, uint32_t index, uint32_t *data, uint32_t len)
{
    if (region == 0) {
        EF_Ctrl_Read_Direct_R0(index, data, len);
    } else if (region == 1) {
        EF_Ctrl_Read_Direct_R1(index, data, len);
    }
}

/****************************************************************************/ /**
 * @brief  Clear efuse data register
 *
 * @param  region: index efuse region
 * @param  index: index of efuse in word
 * @param  len: data length
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION EF_Ctrl_Clear(uint8_t region, uint32_t index, uint32_t len)
{
    uint32_t *pEfuseStart0 = (uint32_t *)(EF_DATA_BASE + 0x00);
    uint32_t *pEfuseStart1 = (uint32_t *)(EF_DATA_BASE + 0x80);
    uint32_t i = 0;

    if (region == 0) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_0();

        /* Clear data */
        for (i = 0; i < len; i++) {
            pEfuseStart0[index + i] = 0;
        }
    } else if (region == 1) {
        /* Switch to AHB clock */
        EF_Ctrl_Sw_AHB_Clk_1();

        /* Clear data */
        for (i = 0; i < len; i++) {
            pEfuseStart1[index + i] = 0;
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  efuse ctrl crc enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Crc_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, EF_CTRL_EF_CRC_TRIG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, EF_CTRL_EF_CRC_MODE);
    tmpVal = BL_SET_REG_BIT(tmpVal, EF_CTRL_EF_CRC_DOUT_INV_EN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, EF_CTRL_EF_CRC_DOUT_ENDIAN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, EF_CTRL_EF_CRC_DIN_ENDIAN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, EF_CTRL_EF_CRC_INT_CLR);
    tmpVal = BL_CLR_REG_BIT(tmpVal, EF_CTRL_EF_CRC_INT_SET);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_0, tmpVal);

    tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, EF_CTRL_EF_CRC_EN);
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  efuse ctrl get crc busy status
 *
 * @param  None
 *
 * @return DISABLE or ENABLE
 *
*******************************************************************************/
BL_Sts_Type EF_Ctrl_Crc_Is_Busy(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_0);
    return (BL_Sts_Type)BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_CRC_BUSY);
}

/****************************************************************************/ /**
 * @brief  efuse ctrl set golden value
 *
 * @param  goldenValue: Crc golden value
 *
 * @return None
 *
*******************************************************************************/
void EF_Ctrl_Crc_Set_Golden(uint32_t goldenValue)
{
    BL_WR_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_4, goldenValue);
}

/****************************************************************************/ /**
 * @brief  efuse ctrl get crc result
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type EF_Ctrl_Crc_Result(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(EF_CTRL_BASE, EF_CTRL_EF_CRC_CTRL_0);
    return (BL_Err_Type)BL_IS_REG_BIT_SET(tmpVal, EF_CTRL_EF_CRC_ERROR);
}

/*@} end of group SEC_EF_CTRL_Public_Functions */

/*@} end of group SEC_EF_CTRL */

/*@} end of group BL808_Peripheral_Driver */
