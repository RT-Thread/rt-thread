/**
  ******************************************************************************
  * @file    bl702_pds.c
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

#include "bl702.h"
#include "bl702_pds.h"

/** @addtogroup  BL702_Peripheral_Driver
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
static intCallback_Type *pdsIntCbfArra[PDS_INT_MAX][1] = { { NULL }, { NULL }, { NULL }, { NULL }, { NULL }, { NULL }, { NULL }, { NULL }, { NULL }, { NULL }, { NULL } };

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
 * @brief  power down sleep ram configure
 *
 * @param  ramCfg: power down sleep force ram configuration
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_RAM_Config(PDS_RAM_CFG_Type *ramCfg)
{
    if (NULL == ramCfg) {
        return ERROR;
    }

    /* PDS_RAM1 config */
    BL_WR_REG(PDS_BASE, PDS_RAM1, *(uint32_t *)ramCfg);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power down sleep set pad configure
 *
 * @param  pin: power down sleep pad num
 * @param  cfg: power down sleep pad type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Set_Pad_Config(PDS_PAD_PIN_Type pin, PDS_PAD_CFG_Type cfg)
{
    uint32_t tmpVal = 0;
    uint32_t tmpPu = 0;
    uint32_t tmpPd = 0;

    if (pin < PDS_PAD_PIN_GPIO_23) {
        /* GPIO17 - GPIO22 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_SET_PU_PD);

        switch (cfg) {
            case PDS_PAD_CFG_PULL_NONE:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PD) & ~(1 << pin);
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PU) & ~(1 << pin);
                break;

            case PDS_PAD_CFG_PULL_DOWN:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PD) | (1 << pin);
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PU) & ~(1 << pin);
                break;

            case PDS_PAD_CFG_PULL_UP:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PD) & ~(1 << pin);
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PU) | (1 << pin);
                break;

            case PDS_PAD_CFG_ACTIVE_IE:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PD) | (1 << pin);
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PU) | (1 << pin);
                break;

            default:
                break;
        }

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PD, tmpPd);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_22_17_PU, tmpPu);
        BL_WR_REG(PDS_BASE, PDS_GPIO_SET_PU_PD, tmpVal);
    } else {
        /* GPIO23 - GPIO28 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_SET_PU_PD);

        switch (cfg) {
            case PDS_PAD_CFG_PULL_NONE:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PD) & ~(1 << (pin - PDS_PAD_PIN_GPIO_23));
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PU) & ~(1 << (pin - PDS_PAD_PIN_GPIO_23));
                break;

            case PDS_PAD_CFG_PULL_DOWN:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PD) | (1 << (pin - PDS_PAD_PIN_GPIO_23));
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PU) & ~(1 << (pin - PDS_PAD_PIN_GPIO_23));
                break;

            case PDS_PAD_CFG_PULL_UP:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PD) & ~(1 << (pin - PDS_PAD_PIN_GPIO_23));
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PU) | (1 << (pin - PDS_PAD_PIN_GPIO_23));
                break;

            case PDS_PAD_CFG_ACTIVE_IE:
                tmpPd = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PD) | (1 << (pin - PDS_PAD_PIN_GPIO_23));
                tmpPu = BL_GET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PU) | (1 << (pin - PDS_PAD_PIN_GPIO_23));
                break;

            default:
                break;
        }

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PD, tmpPd);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CR_PDS_GPIO_28_23_PU, tmpPu);
        BL_WR_REG(PDS_BASE, PDS_GPIO_SET_PU_PD, tmpVal);
    }

    return SUCCESS;
}

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
BL_Err_Type ATTR_TCM_SECTION PDS_App_Enable(PDS_CTL_Type *cfg, PDS_CTL4_Type *cfg4, uint32_t pdsSleepCnt)
{
    uint32_t tmpVal=0;
    /* PDS sleep time 1~PDS_WARMUP_LATENCY_CNT <=> error */
    /* PDS sleep time >PDS_WARMUP_LATENCY_CNT <=> correct */
    if ((pdsSleepCnt) && (pdsSleepCnt <= PDS_WARMUP_LATENCY_CNT)) {
        return ERROR;
    } else if (pdsSleepCnt > PDS_WARMUP_LATENCY_CNT) {
        BL_WR_REG(PDS_BASE, PDS_TIME1, pdsSleepCnt - PDS_WARMUP_LATENCY_CNT);
    } else {
        /* PDS sleep time 0 ,means mask pds_timer wakeup  */
    }

    /* PDS_CTL4 config */
    BL_WR_REG(PDS_BASE, PDS_CTL4, *(uint32_t *)cfg4);

    /* PDS_CTL config */
    if (cfg->pdsStart) {
        /* clear pds int */
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

/****************************************************************************/ /**
 * @brief  power down sleep force configure
 *
 * @param  cfg2: power down sleep force configuration 1
 * @param  cfg3: power down sleep force configuration 2
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Force_Config(PDS_CTL2_Type *cfg2, PDS_CTL3_Type *cfg3)
{
    /* PDS_CTL2 config */
    BL_WR_REG(PDS_BASE, PDS_CTL2, *(uint32_t *)cfg2);

    /* PDS_CTL3 config */
    BL_WR_REG(PDS_BASE, PDS_CTL3, *(uint32_t *)cfg3);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power down sleep force configure
 *
 * @param  defaultLvCfg: power down sleep default level configuration
 * @param  pdsSleepCnt: power down sleep time count
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_TCM_SECTION PDS_Default_Level_Config(PDS_DEFAULT_LV_CFG_Type *defaultLvCfg, uint32_t pdsSleepCnt)
{
    PDS_Force_Config((PDS_CTL2_Type *)&(defaultLvCfg->pdsCtl2), (PDS_CTL3_Type *)&(defaultLvCfg->pdsCtl3));
    PDS_App_Enable((PDS_CTL_Type *)&(defaultLvCfg->pdsCtl), (PDS_CTL4_Type *)&(defaultLvCfg->pdsCtl4), pdsSleepCnt);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  power down sleep int enable
 *
 * @param  intType: PDS int type
 * @param  enable: ENABLE or DISABLE
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_IntEn(PDS_INT_Type intType, BL_Fun_Type enable)
{
    uint32_t offset = 0;
    uint32_t tmpVal = 0;

    if ((intType < PDS_INT_PDS_SLEEP_CNT) || (intType > PDS_INT_KYS_QDEC)) {
        return ERROR;
    }

    switch (intType) {
        case PDS_INT_WAKEUP:
        case PDS_INT_RF_DONE:
        case PDS_INT_PLL_DONE:
            return ERROR;

        case PDS_INT_PDS_SLEEP_CNT:
            offset = 16;
            break;

        case PDS_INT_HBN_IRQ_OUT0:
            offset = 17;
            break;

        case PDS_INT_HBN_IRQ_OUT1:
            offset = 18;
            break;

        case PDS_INT_GPIO_IRQ:
            offset = 19;
            break;

        case PDS_INT_IRRX:
            offset = 20;
            break;

        case PDS_INT_BLE_SLP_IRQ:
            offset = 21;
            break;

        case PDS_INT_USB_WKUP:
            offset = 22;
            break;

        case PDS_INT_KYS_QDEC:
            offset = 23;
            break;

        case PDS_INT_MAX:
            break;

        default:
            break;
    }

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);

    if (enable) {
        tmpVal = tmpVal | (1 << offset);
    } else {
        tmpVal = tmpVal & ~(1 << offset);
    }

    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    return SUCCESS;
}

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
    uint32_t offset = 0;
    uint32_t tmpVal = 0;

    if (intType > PDS_INT_PLL_DONE) {
        return ERROR;
    }

    switch (intType) {
        case PDS_INT_WAKEUP:
            offset = 8;
            break;

        case PDS_INT_RF_DONE:
            offset = 10;
            break;

        case PDS_INT_PLL_DONE:
            offset = 11;
            break;

        case PDS_INT_PDS_SLEEP_CNT:
        case PDS_INT_HBN_IRQ_OUT0:
        case PDS_INT_HBN_IRQ_OUT1:
        case PDS_INT_GPIO_IRQ:
        case PDS_INT_IRRX:
        case PDS_INT_BLE_SLP_IRQ:
        case PDS_INT_USB_WKUP:
        case PDS_INT_KYS_QDEC:
        case PDS_INT_MAX:
        default:
            return ERROR;
    }

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);

    if (intMask != UNMASK) {
        tmpVal = tmpVal | (1 << offset);
    } else {
        tmpVal = tmpVal & ~(1 << offset);
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
    uint32_t offset = 0;

    switch (intType) {
        case PDS_INT_WAKEUP:
            offset = 0;
            break;

        case PDS_INT_RF_DONE:
            offset = 2;
            break;

        case PDS_INT_PLL_DONE:
            offset = 3;
            break;

        case PDS_INT_PDS_SLEEP_CNT:
            offset = 24;
            break;

        case PDS_INT_HBN_IRQ_OUT0:
            offset = 25;
            break;

        case PDS_INT_HBN_IRQ_OUT1:
            offset = 26;
            break;

        case PDS_INT_GPIO_IRQ:
            offset = 27;
            break;

        case PDS_INT_IRRX:
            offset = 28;
            break;

        case PDS_INT_BLE_SLP_IRQ:
            offset = 29;
            break;

        case PDS_INT_USB_WKUP:
            offset = 30;
            break;

        case PDS_INT_KYS_QDEC:
            offset = 31;
            break;

        case PDS_INT_MAX:
            break;

        default:
            break;
    }

    return (BL_RD_REG(PDS_BASE, PDS_INT) & (1 << offset)) ? SET : RESET;
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
 * @brief  power down sleep clear reset event
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Clear_Reset_Event(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLR_RESET_EVENT);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLR_RESET_EVENT);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLR_RESET_EVENT);
    BL_WR_REG(PDS_BASE, PDS_INT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get power down sleep reset event
 *
 * @param  event: power down sleep reset event
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type PDS_Get_Reset_Event(PDS_RST_EVENT_Type event)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_INT);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_RESET_EVENT);

    return (tmpVal & (1 << event)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  set power down sleep VDDCORE gpio interrupt config
 *
 * @param  src: PDS VDDCORE src pin num
 * @param  mode: PDS VDDCORE src pin interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Set_Vddcore_GPIO_IntCfg(PDS_VDDCORE_GPIO_SRC_Type src, PDS_AON_GPIO_INT_Trigger_Type mode)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_PDS_VDDCORE_GPIO_SRC_TYPE(src));
    CHECK_PARAM(IS_PDS_AON_GPIO_INT_Trigger_TYPE(mode));

    tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_INT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_GPIO_INT_SELECT, src);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_GPIO_INT_MODE, mode);
    BL_WR_REG(PDS_BASE, PDS_GPIO_INT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set power down sleep VDDCORE gpio interrupt mask
 *
 * @param  intMask: None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Set_Vddcore_GPIO_IntMask(BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_INT);

    if (intMask != UNMASK) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDS_GPIO_INT_MASK);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_INT_MASK);
    }

    BL_WR_REG(PDS_BASE, PDS_GPIO_INT, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  set power down sleep VDDCORE gpio interrupt mask
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Sts_Type PDS_Get_Vddcore_GPIO_IntStatus(void)
{
    return BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE, PDS_GPIO_INT), PDS_GPIO_INT_STAT) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  set power down sleep VDDCORE gpio interrupt mask
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type PDS_Set_Vddcore_GPIO_IntClear(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_INT_CLR);
    BL_WR_REG(PDS_BASE, PDS_GPIO_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_INT);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_GPIO_INT_CLR);
    BL_WR_REG(PDS_BASE, PDS_GPIO_INT, tmpVal);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_GPIO_INT);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_GPIO_INT_CLR);
    BL_WR_REG(PDS_BASE, PDS_GPIO_INT, tmpVal);

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
            BL702_Delay_US(2);
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
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_ICP_1U, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_ICP_5U, 2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_INT_FRAC_SW, 0);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_CP, tmpVal);

    /* clkpll_c3 */
    /* clkpll_cz */
    /* clkpll_rz */
    /* clkpll_r4 */
    /* clkpll_r4_short */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_RZ);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_C3, 3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_CZ, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_RZ, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_R4_SHORT, 1);
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
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, 0x3C0000);
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

    BL702_Delay_US(5);

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

    BL702_Delay_US(5);

    /* clkpll_sdm_reset=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_SDM_RESET);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    BL702_Delay_US(1);
    /* clkpll_reset_fbdv=1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_CLKPLL_RESET_FBDV);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    BL702_Delay_US(2);
    /* clkpll_reset_fbdv=0 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_RESET_FBDV);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);
    BL702_Delay_US(1);
    /* clkpll_sdm_reset=0 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_CLKPLL_SDM_RESET);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    return SUCCESS;
}
#endif
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
 * @brief  Set Audio PLL clock
 *
 * @param  audioPLLFreq: Audio PLL sel frequency , have two vaild input 12.288 or 11.289 MHZ
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
__WEAK
BL_Err_Type ATTR_CLOCK_SECTION PDS_Set_Audio_PLL_Freq(PDS_AUDIO_PLL_Type audioPLLFreq)
{
    uint32_t sdmin_table[] = { 0x374BC6, 0x32CCED, 0x32CCED, 0x6E978D, 0x6C0000, 0x3E8000};
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_PDS_AUDIO_PLL_TYPE(audioPLLFreq));

    /*set PDS_CLKPLL_REFDIV_RATIO as 0x2 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_REFDIV_RATIO, 0x2);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL, tmpVal);

    /*set clkpll_sdmin as sdmin*/
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_SDM);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_SDMIN, (uint32_t)sdmin_table[audioPLLFreq % (sizeof(sdmin_table) / sizeof(sdmin_table[0]))]);

    BL_WR_REG(PDS_BASE, PDS_CLKPLL_SDM, tmpVal);

    /*reset pll */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_PU_RST_CLKPLL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_PU_CLKPLL_SFREG, 1);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    BL702_Delay_MS(10);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_PU_CLKPLL, 1);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_RESET_FBDV, 1);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    BL702_Delay_MS(10);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_RESET_FBDV, 0);
    BL_WR_REG(PDS_BASE, PDS_PU_RST_CLKPLL, tmpVal);

    /*set div for audio pll */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL);

    if (audioPLLFreq != AUDIO_PLL_5644800_HZ) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_POSTDIV, 36);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_POSTDIV, 72);
    }

    BL_WR_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL, tmpVal);

    return SUCCESS;
}

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
void ATTR_TCM_SECTION PDS_Reset(void)
{
    uint32_t tmpVal = 0;

    tmpVal = *(uint32_t *)0x40000010;
    tmpVal = tmpVal | (1 << 14);
    *(uint32_t *)0x40000010 = tmpVal;

    tmpVal = *(uint32_t *)0x40000010;
    tmpVal = tmpVal & ~(1 << 14);
    *(uint32_t *)0x40000010 = tmpVal;
}
#endif

/****************************************************************************/ /**
 * @brief  Enable power down sleep
 *
 * @param  cfg: power down sleep configuration 1
 * @param  pdsSleepCnt: power down sleep count cycle
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION PDS_Enable(PDS_CFG_Type *cfg, uint32_t pdsSleepCnt)
{
    uint32_t *p = (uint32_t *)cfg;

    if (pdsSleepCnt - PDS_WARMUP_CNT <= 0) {
        return;
    }

    BL_WR_REG(PDS_BASE, PDS_TIME1, pdsSleepCnt - PDS_WARMUP_CNT);

    /* Set PDS control register  */
    BL_WR_REG(PDS_BASE, PDS_CTL, *p);
}
#endif

/****************************************************************************/ /**
 * @brief  PDS Auto mode wake up counter config
 *
 * @param  sleepDuration: sleep time, total pds = sleep_duration + max_warmup_cnt (32K clock cycles),
 *                        recommend maxWarmCnt*N+2
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION PDS_Auto_Time_Config(uint32_t sleepDuration)
{
    /* PDS_TIME1 */
    BL_WR_REG(PDS_BASE, PDS_TIME1, sleepDuration);
}
#endif

/****************************************************************************/ /**
 * @brief  PDS Auto mode config and enable
 *
 * @param  powerCfg: PDS Auto mode power domain config
 * @param  normalCfg: PDS Auto mode power normal config
 * @param  enable: PDS Auto mode Enable or Disable
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION PDS_Auto_Enable(PDS_AUTO_POWER_DOWN_CFG_Type *powerCfg, PDS_AUTO_NORMAL_CFG_Type *normalCfg, BL_Fun_Type enable)
{
    uint32_t pdsCtl = 0;

    CHECK_PARAM(IS_PDS_LDO_VOLTAGE_TYPE(normalCfg->vddcoreVol));

    /* power config */
    pdsCtl |= (powerCfg->mbgPower << 31) |
              (powerCfg->ldo18rfPower << 30) |
              (powerCfg->sfregPower << 29) |
              (powerCfg->pllPower << 28) |
              (powerCfg->cpu0Power << 19) |
              (powerCfg->rc32mPower << 17) |
              (powerCfg->xtalPower << 14) |
              (powerCfg->allPower << 13) |
              (powerCfg->isoPower << 11) |
              (powerCfg->bzPower << 10) |
              (powerCfg->sramDisStanby << 9) |
              (powerCfg->cgPower << 8) |
              (powerCfg->cpu1Power << 7) |
              (powerCfg->usbPower << 3);
    pdsCtl = BL_SET_REG_BITS_VAL(pdsCtl, PDS_CR_PDS_LDO_VOL, normalCfg->vddcoreVol);
    pdsCtl |= (normalCfg->vddcoreVolEn << 18) |
              (normalCfg->cpu0NotNeedWFI << 21) |
              (normalCfg->cpu1NotNeedWFI << 20) |
              (normalCfg->busReset << 16) |
              (normalCfg->disIrqWakeUp << 15) |
              (normalCfg->powerOffXtalForever << 2) |
              (normalCfg->sleepForever << 1);
    BL_WR_REG(PDS_BASE, PDS_CTL, pdsCtl);

    pdsCtl = BL_RD_REG(PDS_BASE, PDS_CTL);

    if (enable) {
        pdsCtl |= (1 << 0);
    } else {
        pdsCtl &= ~(1 << 0);
    }

    BL_WR_REG(PDS_BASE, PDS_CTL, pdsCtl);
}
#endif

/****************************************************************************/ /**
 * @brief  PDS force turn off XXX domain
 *
 * @param  domain: PDS domain
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION PDS_Manual_Force_Turn_Off(PDS_FORCE_Type domain)
{
    uint32_t tmpVal = 0;

    /* memory sleep */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal |= 1 << (domain + PDS_FORCE_MEM_STBY_OFFSET);
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* gate clock */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal |= 1 << (domain + PDS_FORCE_GATE_CLK_OFFSET);
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* pds reset */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal |= 1 << (domain + PDS_FORCE_PDS_RST_OFFSET);
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* isolation on */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal |= 1 << (domain + PDS_FORCE_ISO_EN_OFFSET);
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* power off */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal |= 1 << (domain + PDS_FORCE_PWR_OFF_OFFSET);
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);
}
#endif

/****************************************************************************/ /**
 * @brief  PDS force turn on XXX domain
 *
 * @param  domain: PDS domain
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_ROM_DRIVER
__WEAK
void ATTR_TCM_SECTION PDS_Manual_Force_Turn_On(PDS_FORCE_Type domain)
{
    uint32_t tmpVal = 0;

    /* power on */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal &= ~(1 << (domain + PDS_FORCE_PWR_OFF_OFFSET));
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* isolation off */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal &= ~(1 << (domain + PDS_FORCE_ISO_EN_OFFSET));
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* pds de_reset */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal &= ~(1 << (domain + PDS_FORCE_PDS_RST_OFFSET));
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* memory active */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal &= ~(1 << (domain + PDS_FORCE_MEM_STBY_OFFSET));
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);

    /* clock on */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_CTL2);
    tmpVal &= ~(1 << (domain + PDS_FORCE_GATE_CLK_OFFSET));
    BL_WR_REG(PDS_BASE, PDS_CTL2, tmpVal);
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
void PDS_WAKEUP_IRQHandler(void)
{
    for (PDS_INT_Type intType = PDS_INT_WAKEUP; intType < PDS_INT_MAX; intType++) {
        if (PDS_Get_IntStatus(intType) && (pdsIntCbfArra[intType][0] != NULL)) {
            pdsIntCbfArra[intType][0]();
        }
    }
    PDS_Set_Vddcore_GPIO_IntClear();
    PDS_IntClear();
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
    Interrupt_Handler_Register(PDS_WAKEUP_IRQn, PDS_WAKEUP_IRQHandler);
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief
 *
 * @param
 *
 * @return
 *
*******************************************************************************/
BL_Err_Type PDS_Set_Clkpll_Top_Ctrl(uint8_t vg11Sel)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL);
    //clkpll_vg11_sel
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_CLKPLL_VG11_SEL, vg11Sel);
    BL_WR_REG(PDS_BASE, PDS_CLKPLL_TOP_CTRL, tmpVal);

    return SUCCESS;
}

/*@} end of group PDS_Public_Functions */

/*@} end of group PDS */

/*@} end of group BL702_Peripheral_Driver */
