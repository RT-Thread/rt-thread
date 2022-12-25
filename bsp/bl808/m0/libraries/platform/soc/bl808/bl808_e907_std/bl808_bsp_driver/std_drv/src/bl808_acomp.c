/**
  ******************************************************************************
  * @file    bl808_acomp.c
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

#include "bl808_acomp.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ACOMP
 *  @{
 */

/** @defgroup  ACOMP_Private_Macros
 *  @{
 */

/*@} end of group ACOMP_Private_Macros */

/** @defgroup  ACOMP_Private_Types
 *  @{
 */

/*@} end of group ACOMP_Private_Types */

/** @defgroup  ACOMP_Private_Variables
 *  @{
 */

/*@} end of group ACOMP_Private_Variables */

/** @defgroup  ACOMP_Global_Variables
 *  @{
 */

/*@} end of group ACOMP_Global_Variables */

/** @defgroup  ACOMP_Private_Fun_Declaration
 *  @{
 */

/*@} end of group ACOMP_Private_Fun_Declaration */

/** @defgroup  ACOMP_Private_Functions
 *  @{
 */

/*@} end of group ACOMP_Private_Functions */

/** @defgroup  ACOMP_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Analog compare init
 *
 * @param  acompNo: Compare ID
 * @param  cfg: Compare consideration pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type AON_ACOMP_Init(AON_ACOMP_ID_Type acompNo, AON_ACOMP_CFG_Type *cfg)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_AON_ACOMP_ID_TYPE(acompNo));

    if (acompNo == AON_ACOMP0_ID) {
        /* Disable ACOMP first */
        tmpVal = BL_RD_REG(AON_BASE, AON_ACOMP0_CTRL);
        tmpVal = BL_CLR_REG_BIT(tmpVal, AON_ACOMP0_EN);
        tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP0_CTRL, tmpVal);

        /* Set ACOMP config */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_MUXEN, cfg->muxEn);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_POS_SEL, cfg->posChanSel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_NEG_SEL, cfg->negChanSel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_LEVEL_SEL, cfg->scalingFactor);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_BIAS_PROG, cfg->biasProg);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_HYST_SELP, cfg->hysteresisPosVolt);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP0_HYST_SELN, cfg->hysteresisNegVolt);

        tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP0_CTRL, tmpVal);
    } else {
        /* Disable ACOMP first */
        tmpVal = BL_RD_REG(AON_BASE, AON_ACOMP1_CTRL);
        tmpVal = BL_CLR_REG_BIT(tmpVal, AON_ACOMP1_EN);
        tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP1_CTRL, tmpVal);

        /* Set ACOMP config */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_MUXEN, cfg->muxEn);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_POS_SEL, cfg->posChanSel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_NEG_SEL, cfg->negChanSel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_LEVEL_SEL, cfg->scalingFactor);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_BIAS_PROG, cfg->biasProg);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_HYST_SELP, cfg->hysteresisPosVolt);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP1_HYST_SELN, cfg->hysteresisNegVolt);

        tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP1_CTRL, tmpVal);
    }

    tmpVal = BL_RD_REG(AON_BASE, AON_ACOMP_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_ACOMP_VREF_SEL, cfg->vioSel);
    tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Analog compare enable
 *
 * @param  acompNo: Compare ID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type AON_ACOMP_Enable(AON_ACOMP_ID_Type acompNo)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_AON_ACOMP_ID_TYPE(acompNo));

    if (acompNo == AON_ACOMP0_ID) {
        tmpVal = BL_RD_REG(AON_BASE, AON_ACOMP0_CTRL);
        tmpVal = BL_SET_REG_BIT(tmpVal, AON_ACOMP0_EN);
        tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP0_CTRL, tmpVal);
    } else {
        tmpVal = BL_RD_REG(AON_BASE, AON_ACOMP1_CTRL);
        tmpVal = BL_SET_REG_BIT(tmpVal, AON_ACOMP1_EN);
        tmpVal = BL_WR_REG(AON_BASE, AON_ACOMP1_CTRL, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Analog compare enable
 *
 * @param  acompNo: Compare ID
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type AON_ACOMP_Get_Result(AON_ACOMP_ID_Type acompNo)
{
    uint32_t tmpVal = 0;

    /* Check the parameters */
    CHECK_PARAM(IS_AON_ACOMP_ID_TYPE(acompNo));

    tmpVal = BL_RD_REG(AON_BASE, AON_ACOMP_CTRL);

    /* Disable ACOMP first */
    if (acompNo == AON_ACOMP0_ID) {
        if (BL_IS_REG_BIT_SET(tmpVal, AON_ACOMP0_OUT_RAW)) {
            return SET;
        } else {
            return RESET;
        }
    } else {
        if (BL_IS_REG_BIT_SET(tmpVal, AON_ACOMP1_OUT_RAW)) {
            return SET;
        } else {
            return RESET;
        }
    }
}

/*@} end of group ACOMP_Public_Functions */

/*@} end of group ACOMP */

/*@} end of group BL808_Peripheral_Driver */
