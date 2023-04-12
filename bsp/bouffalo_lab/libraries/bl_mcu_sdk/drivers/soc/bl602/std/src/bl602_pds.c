/**
  ******************************************************************************
  * @file    bl602_pds.c
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

#include "bl602.h"
#include "bl602_pds.h"

/** @addtogroup  BL602_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PDS
 *  @{
 */

/** @defgroup  PDS_Private_Macros
 *  @{
 */

/*@} end of group PDS_Private_Macros */

/** @defgroup  PDS_Private_Types
 *  @{
 */

/*@} end of group PDS_Private_Types */

/** @defgroup  PDS_Private_Variables
 *  @{
 */
static intCallback_Type *pdsIntCbfArra[4][1] = { { NULL }, { NULL }, { NULL }, { NULL } };

/*@} end of group PDS_Private_Variables */

/** @defgroup  PDS_Global_Variables
 *  @{
 */

/*@} end of group PDS_Global_Variables */

/** @defgroup  PDS_Private_Fun_Declaration
 *  @{
 */

/*@} end of group PDS_Private_Fun_Declaration */

/** @defgroup  PDS_Private_Functions
 *  @{
 */

/*@} end of group PDS_Private_Functions */

/** @defgroup  PDS_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  PDS software reset
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION PDS_Reset(void)
{
    uint32_t tmpVal = 0;

    tmpVal = *(uint32_t *)0x40000014;
    tmpVal = tmpVal | (1 << 14);
    *(uint32_t *)0x40000014 = tmpVal;

    tmpVal = *(uint32_t *)0x40000014;
    tmpVal = tmpVal & ~(1 << 14);
    *(uint32_t *)0x40000014 = tmpVal;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable power down sleep
 *
 * @param  cfg: power down sleep configuration 1
 * @param  cfg4: power down sleep configuration 2
 * @param  pdsSleepCnt: power down sleep count cycle
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
// #ifndef BFLB_USE_ROM_DRIVER
// __WEAK
BL_Err_Type ATTR_TCM_SECTION PDS_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt)
{
    uint32_t tmpVal = 0;

    /* PDS sleep time 0 <=> sleep forever */
    /* PDS sleep time 1~PDS_WARMUP_LATENCY_CNT <=> error */
    /* PDS sleep time >PDS_WARMUP_LATENCY_CNT <=> correct */
    if (!pdsSleepCnt) {
        cfg->sleepForever = 1;
    } else if ((pdsSleepCnt) && (pdsSleepCnt <= PDS_WARMUP_LATENCY_CNT)) {
        return ERROR;
    } else {
        BL_WR_REG(PDS_BASE, PDS_TIME1, pdsSleepCnt - PDS_WARMUP_LATENCY_CNT);
    }

    /* PDS_CTL4 config */
    BL_WR_REG(PDS_BASE, PDS_CTL4, *(uint32_t *)cfg4);

    /* PDS_CTL config */
    if (cfg->pdsStart) {
        tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
        tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
        BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

        tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
        BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

        BL_WR_REG(PDS_BASE, PDS_CTL, (*(uint32_t *)cfg & ~(1 << 0)));
        BL_WR_REG(PDS_BASE, PDS_CTL, (*(uint32_t *)cfg | (1 << 0)));
    } else {
        BL_WR_REG(PDS_BASE, PDS_CTL, *(uint32_t *)cfg);
    }

    return SUCCESS;
}
// #endif

/****************************************************************************/ /**
 * @brief  power down sleep force configure
 *
 * @param  cfg2: power down sleep force configuration 1
 * @param  cfg3: power down sleep force configuration 2
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION PDS_Force_Config(PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3)
{
    /* PDS_CTL2 config */
    BL_WR_REG(PDS_BASE, PDS_CTL2, *(uint32_t *)cfg2);

    /* PDS_CTL3 config */
    BL_WR_REG(PDS_BASE, PDS_CTL3, *(uint32_t *)cfg3);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  power down sleep ram configure
 *
 * @param  ramCfg: power down sleep force ram configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_TCM_SECTION PDS_RAM_Config(PDS_RAM_CFG_Type *ramCfg)
{
    uint32_t tmpVal = 0;

    if (NULL == ramCfg) {
        return SUCCESS;
    }

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MBIST_CTL);
    /* enter bist mode (make ram idle/slp) */
    //tmpVal = tmpVal&~0x1F;
    //tmpVal = tmpVal|0x18;
    /* enter bist mode (make ram ret) */
    tmpVal = tmpVal | (0x1 << 3);
    BL_WR_REG(GLB_BASE, GLB_MBIST_CTL, tmpVal);

    /* PDS_RAM1 config */
    BL_WR_REG(PDS_BASE, PDS_RAM1, *(uint32_t *)ramCfg);

    tmpVal = BL_RD_REG(GLB_BASE, GLB_MBIST_CTL);
    /* exit bist mode (make ram idle/slp) */
    //tmpVal = tmpVal&~0x1F;
    /* exit bist mode (make ram ret) */
    tmpVal = tmpVal & ~(0x1 << 3);
    BL_WR_REG(GLB_BASE, GLB_MBIST_CTL, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  power down sleep force configure
 *
 * @param  defaultLvCfg: power down sleep default level configuration
 * @param  ramCfg: ram configuration
 * @param  pdsSleepCnt: power down sleep time count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
// #ifndef BFLB_USE_ROM_DRIVER
// __WEAK
BL_Err_Type ATTR_TCM_SECTION PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, PDS_RAM_CFG_Type *ramCfg, uint32_t pdsSleepCnt)
{
    /* RAM config need fix after ECO */
    PDS_RAM_Config(ramCfg);
    PDS_Force_Config((PDS_CTL2_Type *)&(defaultLvCfg->pdsCtl2), (PDS_CTL3_Type *)&(defaultLvCfg->pdsCtl3));
    PDS_Enable((PDS_CTL_Type *)&(defaultLvCfg->pdsCtl), (PDS_CTL4_Type *)&(defaultLvCfg->pdsCtl4), pdsSleepCnt);

    return SUCCESS;
}
// #endif

/****************************************************************************/ /**
 * @brief  power down sleep int mask
 *
 * @param  intType: PDS int type
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_IntMask(PDS_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);

    if (intMask != UNMASK) {
        tmpVal = tmpVal | (1 << (intType + PDS_INT_MASK_BIT_OFFSET));
    } else {
        tmpVal = tmpVal & ~(1 << (intType + PDS_INT_MASK_BIT_OFFSET));
    }

    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get power down sleep int status
 *
 * @param  intType: PDS int type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type PDS_Get_IntStatus(PDS_INT_Type intType)
{
    return (BL_RD_REG(PDS_BASE, PDS_INT) & (1 << intType)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  clear power down sleep int status
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_IntClear(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CR_PDS_INT_CLR);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get power down sleep PLL status
 *
 * @param  None
 *
 * @return PDS PLL status
 *
*******************************************************************************/
PDS_PLL_STS_Type PDS_Get_PdsPllStstus(void)
{
    return (PDS_PLL_STS_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE, PDS_STAT), PDS_RO_PDS_PLL_STATE);
}

/****************************************************************************/ /**
 * @brief  get power down sleep RF status
 *
 * @param  None
 *
 * @return PDS RF status
 *
*******************************************************************************/
PDS_RF_STS_Type PDS_Get_PdsRfStstus(void)
{
    return (PDS_RF_STS_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE, PDS_STAT), PDS_RO_PDS_RF_STATE);
}

/****************************************************************************/ /**
 * @brief  get power down sleep status
 *
 * @param  None
 *
 * @return PDS status
 *
*******************************************************************************/
PDS_STS_Type PDS_Get_PdsStstus(void)
{
    return (PDS_STS_Type)BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE, PDS_STAT), PDS_RO_PDS_STATE);
}

/****************************************************************************/ /**
 * @brief  PDS wakeup IRQHandler install
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_WAKEUP_IRQHandler_Install(void)
{
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(PDS_WAKEUP_IRQn, PDS_WAKEUP_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Install PDS interrupt callback function
 *
 * @param  intType: PDS int type
 * @param  cbFun: cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Int_Callback_Install(PDS_INT_Type intType, intCallback_Type *cbFun)
{
    pdsIntCbfArra[intType][0] = cbFun;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Trim RC32M
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Trim_RC32M(void)
{
    Efuse_Ana_RC32M_Trim_Type trim;
    int32_t tmpVal = 0;

    EF_Ctrl_Read_RC32M_Trim(&trim);

    if (trim.trimRc32mExtCodeEn) {
        if (trim.trimRc32mCodeFrExtParity == EF_Ctrl_Get_Trim_Parity(trim.trimRc32mCodeFrExt, 8)) {
            tmpVal = BL_RD_REG(PDS_BASE, PDS_RC32M_CTRL0);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_RC32M_CODE_FR_EXT, trim.trimRc32mCodeFrExt);
            tmpVal = BL_SET_REG_BIT(tmpVal, PDS_RC32M_EXT_CODE_EN);
            BL_WR_REG(PDS_BASE, PDS_RC32M_CTRL0, tmpVal);
            BL602_Delay_US(2);
            return SUCCESS;
        }
    }

    return ERROR;
}
#endif

/****************************************************************************/ /**
 * @brief  Select RC32M as PLL ref source
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Select_RC32M_As_PLL_Ref(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_REFCLK_SEL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_XTAL_RC32M_SEL);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Select XTAL as PLL ref source
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Select_XTAL_As_PLL_Ref(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_REFCLK_SEL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_XTAL_RC32M_SEL);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power on PLL
 *
 * @param  xtalType: xtal type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Power_On_PLL(PDS_PLL_XTAL_Type xtalType)
{
    uint32_t tmpVal = 0;

    /* Check parameter*/
    CHECK_PARAM(IS_PDS_PLL_XTAL_TYPE(xtalType));

    /**************************/
    /* select PLL XTAL source */
    /**************************/

    if ((xtalType == PDS_PLL_XTAL_RC32M) || (xtalType == PDS_PLL_XTAL_NONE)) {
        PDS_Trim_RC32M();
        PDS_Select_RC32M_As_PLL_Ref();
    } else {
        PDS_Select_XTAL_As_PLL_Ref();
    }

    /*******************************************/
    /* PLL power down first, not indispensable */
    /*******************************************/
    /* power off PLL first, this step is not indispensable */
    PDS_Power_Off_PLL();

    /********************/
    /* PLL param config */
    /********************/

    /* clkpll_icp_1u */
    /* clkpll_icp_5u */
    /* clkpll_int_frac_sw */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_CP);

    if (xtalType == PDS_PLL_XTAL_26M) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_ICP_1U, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_ICP_5U, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_INT_FRAC_SW, 1);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_ICP_1U, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_ICP_5U, 2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_INT_FRAC_SW, 0);
    }

    BL_WR_REG(PDS_BASE, PDS_CLKPLL_CP, tmpVal);

    /* clkpll_c3 */
    /* clkpll_cz */
    /* clkpll_rz */
    /* clkpll_r4 */
    /* clkpll_r4_short */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_RZ);

    if (xtalType == PDS_PLL_XTAL_26M) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_C3, 2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_CZ, 2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_RZ, 5);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_R4_SHORT, 0);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_C3, 3);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_CZ, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_RZ, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_R4_SHORT, 1);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_R4, 2);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_RZ, tmpVal);

    /* clkpll_refdiv_ratio */
    /* clkpll_postdiv */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_POSTDIV, 0x14);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_REFDIV_RATIO, 2);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL, tmpVal);

    /* clkpll_sdmin */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_SDM);

    switch (xtalType) {
        case PDS_PLL_XTAL_NONE:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x3C0000);
            break;

        case PDS_PLL_XTAL_24M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x500000);
            break;

        case PDS_PLL_XTAL_32M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x3C0000);
            break;

        case PDS_PLL_XTAL_38P4M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x320000);
            break;

        case PDS_PLL_XTAL_40M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x300000);
            break;

        case PDS_PLL_XTAL_26M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x49D39D);
            break;

        case PDS_PLL_XTAL_RC32M:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x3C0000);
            break;

        default:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x3C0000);
            break;
    }

    BL_WR_REG(PDS_BASE, PDS_CLKPLL_SDM, tmpVal);

    /* clkpll_sel_fb_clk */
    /* clkpll_sel_sample_clk can be 0/1, default is 1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_FBDV);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SEL_FB_CLK, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SEL_SAMPLE_CLK, 1);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_FBDV, tmpVal);

    /*************************/
    /* PLL power up sequence */
    /*************************/

    /* pu_clkpll_sfreg=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_PU_CLKPLL_SFREG);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    BL602_Delay_US(5);

    /* pu_clkpll=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_PU_CLKPLL);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    /* clkpll_pu_cp=1 */
    /* clkpll_pu_pfd=1 */
    /* clkpll_pu_fbdv=1 */
    /* clkpll_pu_postdiv=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_PU_CP);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_PU_PFD);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_PU_FBDV);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_PU_POSTDIV);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    BL602_Delay_US(5);

    /* clkpll_sdm_reset=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_SDM_RESET);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    BL602_Delay_US(1);
    /* clkpll_reset_fbdv=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_RESET_FBDV);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    BL602_Delay_US(2);
    /* clkpll_reset_fbdv=0 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_RESET_FBDV);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    BL602_Delay_US(1);
    /* clkpll_sdm_reset=0 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_SDM_RESET);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Fix XTAL26M Setting
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION PDS_Fix_Xtal_Settig(void)
{
    uint32_t tmpVal;

    /* Fix 26M xtal clkpll_sdmin */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_SDM);

    if (0x49D39D == BL_GET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN)) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x49D89E);
        BL_WR_REG(PDS_BASE, PDS_CLKPLL_SDM, tmpVal);
    }

    return SUCCESS;
}

/** PLL output config **/
/*
[8]    1'h0    r/w    clkpll_en_32m
[7]    1'h0    r/w    clkpll_en_48m
[6]    1'h0    r/w    clkpll_en_80m
[5]    1'h0    r/w    clkpll_en_96m
[4]    1'h0    r/w    clkpll_en_120m
[3]    1'h0    r/w    clkpll_en_160m
[2]    1'h0    r/w    clkpll_en_192m
[1]    1'h0    r/w    clkpll_en_240m
[0]    1'h0    r/w    clkpll_en_480m
*/

/****************************************************************************/ /**
 * @brief  Enable all PLL clock
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Enable_PLL_All_Clks(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN);
    tmpVal |= 0x1FF;
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Disable all PLL clock
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Disable_PLL_All_Clks(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN);
    tmpVal &= (~0x1FF);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable PLL clock
 *
 * @param  pllClk: PLL clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Enable_PLL_Clk(PDS_PLL_CLK_Type pllClk)
{
    uint32_t tmpVal = 0;

    /* Check parameter*/
    CHECK_PARAM(IS_PDS_PLL_CLK_TYPE(pllClk));

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN);
    tmpVal |= (1 << pllClk);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Disable PLL clock
 *
 * @param  pllClk: PLL clock type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Disable_PLL_Clk(PDS_PLL_CLK_Type pllClk)
{
    uint32_t tmpVal = 0;

    /* Check parameter*/
    CHECK_PARAM(IS_PDS_PLL_CLK_TYPE(pllClk));

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN);
    tmpVal &= (~(1 << pllClk));
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_OUTPUT_EN, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power off PLL
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Power_Off_PLL(void)
{
    uint32_t tmpVal = 0;

    /* pu_clkpll_sfreg=0 */
    /* pu_clkpll=0 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_PU_CLKPLL_SFREG);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_PU_CLKPLL);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    /* clkpll_pu_cp=0 */
    /* clkpll_pu_pfd=0 */
    /* clkpll_pu_fbdv=0 */
    /* clkpll_pu_postdiv=0 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_PU_CP);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_PU_PFD);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_PU_FBDV);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_PU_POSTDIV);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  Power down sleep wake up interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void PDS_WAKEUP_IRQHandler(void)
{
    for (PDS_INT_Type intType = PDS_INT_WAKEUP; intType < PDS_INT_MAX; intType++) {
        if (PDS_Get_IntStatus(intType) && (pdsIntCbfArra[intType][0] != NULL)) {
            pdsIntCbfArra[intType][0]();
        }
    }

    PDS_IntClear();
}
#endif

/*@} end of group PDS_Public_Functions */

/*@} end of group PDS */

/*@} end of group BL602_Peripheral_Driver */
