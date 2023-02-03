/**
  ******************************************************************************
  * @file    bl808_touch.c
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

#include "bl808_touch.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TOUCH
 *  @{
 */

/** @defgroup  TOUCH_Private_Macros
 *  @{
 */

/*@} end of group TOUCH_Private_Macros */

/** @defgroup  TOUCH_Private_Types
 *  @{
 */

/*@} end of group TOUCH_Private_Types */

/** @defgroup  TOUCH_Private_Variables
 *  @{
 */
static intCallback_Type *touchIntCbfArra[TOUCH_INT_INTERRUPT + 1][TOUCH_CHANNEL_11 + 1] = { { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };

/*@} end of group TOUCH_Private_Variables */

/** @defgroup  TOUCH_Global_Variables
 *  @{
 */

/*@} end of group TOUCH_Global_Variables */

/** @defgroup  TOUCH_Private_Fun_Declaration
 *  @{
 */

/*@} end of group TOUCH_Private_Fun_Declaration */

/** @defgroup  TOUCH_Private_Functions
 *  @{
 */

/*@} end of group TOUCH_Private_Functions */

/** @defgroup  TOUCH_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  touch moudle init
 *
 * @param  touchId: touch moudle ID
 * @param  tCfg: touch moudle config
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_Init(TOUCH_ID_Type touchId, TOUCH_CFG_Type *tCfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CLK_SEL_TYPE(tCfg->clkSel));
    CHECK_PARAM(IS_TOUCH_CLK_DIV_TYPE(tCfg->clkDiv));
    CHECK_PARAM(IS_TOUCH_POWER_SEL_TYPE(tCfg->powerSel));
    CHECK_PARAM(IS_TOUCH_WORK_MODE_TYPE(tCfg->workMode));
    CHECK_PARAM(IS_TOUCH_RUN_MODE_TYPE(tCfg->runMode));
    CHECK_PARAM((tCfg->sleepTime <= 0x7FFFFF));
    CHECK_PARAM(IS_TOUCH_PCHARGE_LOW_TYPE(tCfg->pchargeLow));
    CHECK_PARAM(IS_TOUCH_PCHARGE_HIGH_TYPE(tCfg->pchargeHigh));
    CHECK_PARAM(IS_TOUCH_LDO_VOLTAGE_TYPE(tCfg->ldoVol));
    CHECK_PARAM(IS_TOUCH_VREF_VOLTAGE_TYPE(tCfg->vrefVol));
    CHECK_PARAM(IS_TOUCH_HYSTERSIS_VOLTAGE_TYPE(tCfg->hystersisVol));
    CHECK_PARAM(IS_TOUCH_COMPENSATION_CAP_TYPE(tCfg->compensationCap));
    CHECK_PARAM(IS_TOUCH_FILTER_ORDER_CTRL_TYPE(tCfg->filterCtrl));
    CHECK_PARAM(IS_TOUCH_LTA_ORDER_CTRL_TYPE(tCfg->ltaCtrl));
    CHECK_PARAM((tCfg->dataHysCtrl <= 0x1FF));

    /* touch1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH1);

    if (tCfg->powerSel == TOUCH_POWER_SEL_AON) {
        /* power from AON bandgap */
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_TOUCH_CURRENT_SEL);
    } else {
        /* power from internal bandgap */
        tmpVal = BL_SET_REG_BIT(tmpVal, PDS_TOUCH_CURRENT_SEL);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_ULP_EN, tCfg->ulpEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CYCLE_EN, tCfg->cycleEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CONT_EN, tCfg->runMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_PCHARGE_LOW, tCfg->pchargeLow);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_PCHARGE_HIGH, tCfg->pchargeHigh);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CLK_DIV_RATIO, tCfg->clkDiv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CLK_SEL, tCfg->clkSel);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_COMP_HYS_SEL, tCfg->hystersisVol);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VLDO_SEL, tCfg->ldoVol);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VREF_SEL, tCfg->vrefVol);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH1, tmpVal);

    /* touch3 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VLDO_CCSEL, tCfg->compensationCap);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_SELF_MUTUAL_SEL, tCfg->workMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_ORDER, tCfg->filterCtrl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_EN, tCfg->filterEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_ORDER, tCfg->ltaCtrl);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_EN, tCfg->ltaEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_DATA_HYS_EN, tCfg->dataHystersisEn);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL_CAL_EN, tCfg->calibrationEn);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH3, tmpVal);

    /* touch_sleep_time */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_SLEEP_TIME);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_SLEEP_CYCLE, tCfg->sleepTime);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_SLEEP_TIME, tmpVal);

    /* touch_data_hystersis */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_DATA_HYSTERSIS);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_DATA_HYS, tCfg->dataHysCtrl);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_DATA_HYSTERSIS, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch moudle channel init
 *
 * @param  touchId: touch moudle ID
 * @param  tChCfg: touch moudle channel config
 * @param  tChSel: touch moudle channel select
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_CHANNEL_Init(TOUCH_ID_Type touchId, TOUCH_CHANNEL_CFG_Type *tChCfg, TOUCH_CHANNEL_Type tChSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch0));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch1));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch2));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch3));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch4));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch5));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch6));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch7));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch8));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch9));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch10));
    CHECK_PARAM(IS_TOUCH_CHANNEL_HIGHZ_CFG_TYPE(tChCfg->ch11));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tChSel));

    /* touch2 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL11_HIGHZ_EN, tChCfg->ch11);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL10_HIGHZ_EN, tChCfg->ch10);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL9_HIGHZ_EN, tChCfg->ch9);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL8_HIGHZ_EN, tChCfg->ch8);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL7_HIGHZ_EN, tChCfg->ch7);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL6_HIGHZ_EN, tChCfg->ch6);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL5_HIGHZ_EN, tChCfg->ch5);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL4_HIGHZ_EN, tChCfg->ch4);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL3_HIGHZ_EN, tChCfg->ch3);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL2_HIGHZ_EN, tChCfg->ch2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL1_HIGHZ_EN, tChCfg->ch1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL0_HIGHZ_EN, tChCfg->ch0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_CHANNEL_SEL, tChSel);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH2, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch moudle start
 *
 * @param  touchId: touch moudle ID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_Enable(TOUCH_ID_Type touchId)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));

    /* touch1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH1);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_PU_TOUCH);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch moudle stop
 *
 * @param  touchId: touch moudle ID
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_Disable(TOUCH_ID_Type touchId)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));

    /* touch1 */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH1);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_PU_TOUCH);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH1, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch moudle set V threshold  value
 *
 * @param  touchId: touch moudle ID
 * @param  tCh: touch moudle channel
 * @param  value: vth value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_SetVthData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh, uint8_t value)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    if (tCh <= TOUCH_CHANNEL_3) {
        /* channel 0 - channel 3 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_0);

        switch (tCh) {
            case TOUCH_CHANNEL_0:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH0, value);
                break;

            case TOUCH_CHANNEL_1:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH1, value);
                break;

            case TOUCH_CHANNEL_2:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH2, value);
                break;

            case TOUCH_CHANNEL_3:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH3, value);
                break;

            default:
                break;
        }

        tmpVal = BL_WR_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_0, tmpVal);
    } else if (tCh <= TOUCH_CHANNEL_7) {
        /* channel 4 - channel 7 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_1);

        switch (tCh) {
            case TOUCH_CHANNEL_4:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH4, value);
                break;

            case TOUCH_CHANNEL_5:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH5, value);
                break;

            case TOUCH_CHANNEL_6:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH6, value);
                break;

            case TOUCH_CHANNEL_7:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH7, value);
                break;

            default:
                break;
        }

        tmpVal = BL_WR_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_1, tmpVal);
    } else {
        /* channel 8 - channel 11 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_2);

        switch (tCh) {
            case TOUCH_CHANNEL_8:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH8, value);
                break;

            case TOUCH_CHANNEL_9:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH9, value);
                break;

            case TOUCH_CHANNEL_10:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH10, value);
                break;

            case TOUCH_CHANNEL_11:
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH11, value);
                break;

            default:
                break;
        }

        tmpVal = BL_WR_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_2, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get touch moudle vth data
 *
 * @param  touchId: touch moudle ID
 * @param  tCh: touch moudle channel
 *
 * @return vth data
 *
*******************************************************************************/
uint32_t TOUCH_GetVthData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    if (tCh <= TOUCH_CHANNEL_3) {
        /* channel 0 - channel 3 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_0);

        switch (tCh) {
            case TOUCH_CHANNEL_0:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH0);
                break;

            case TOUCH_CHANNEL_1:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH1);
                break;

            case TOUCH_CHANNEL_2:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH2);
                break;

            case TOUCH_CHANNEL_3:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH3);
                break;

            default:
                break;
        }
    } else if (tCh <= TOUCH_CHANNEL_7) {
        /* channel 4 - channel 7 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_1);

        switch (tCh) {
            case TOUCH_CHANNEL_4:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH4);
                break;

            case TOUCH_CHANNEL_5:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH5);
                break;

            case TOUCH_CHANNEL_6:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH6);
                break;

            case TOUCH_CHANNEL_7:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH7);
                break;

            default:
                break;
        }
    } else {
        /* channel 8 - channel 11 */
        tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_VTH_DATA_2);

        switch (tCh) {
            case TOUCH_CHANNEL_8:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH8);
                break;

            case TOUCH_CHANNEL_9:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH9);
                break;

            case TOUCH_CHANNEL_10:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH10);
                break;

            case TOUCH_CHANNEL_11:
                tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_VTH_DATA_CH11);
                break;

            default:
                break;
        }
    }

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  get touch moudle raw data
 *
 * @param  touchId: touch moudle ID
 * @param  tCh: touch moudle channel
 *
 * @return raw data
 *
*******************************************************************************/
uint32_t TOUCH_GetRawData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    switch (tCh) {
        case TOUCH_CHANNEL_0:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_0);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH0);
            break;

        case TOUCH_CHANNEL_1:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_1);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH1);
            break;

        case TOUCH_CHANNEL_2:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_2);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH2);
            break;

        case TOUCH_CHANNEL_3:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_3);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH3);
            break;

        case TOUCH_CHANNEL_4:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_4);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH4);
            break;

        case TOUCH_CHANNEL_5:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_5);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH5);
            break;

        case TOUCH_CHANNEL_6:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_6);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH6);
            break;

        case TOUCH_CHANNEL_7:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_7);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH7);
            break;

        case TOUCH_CHANNEL_8:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_8);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH8);
            break;

        case TOUCH_CHANNEL_9:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_9);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH9);
            break;

        case TOUCH_CHANNEL_10:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_10);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH10);
            break;

        case TOUCH_CHANNEL_11:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_RAW_DATA_11);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_RAW_DATA_CH11);
            break;
    }

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  get touch moudle LTA data
 *
 * @param  touchId: touch moudle ID
 * @param  tCh: touch moudle channel
 *
 * @return LTA data
 *
*******************************************************************************/
uint32_t TOUCH_GetLtaData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    switch (tCh) {
        case TOUCH_CHANNEL_0:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_0);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH0);
            break;

        case TOUCH_CHANNEL_1:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_1);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH1);
            break;

        case TOUCH_CHANNEL_2:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_2);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH2);
            break;

        case TOUCH_CHANNEL_3:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_3);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH3);
            break;

        case TOUCH_CHANNEL_4:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_4);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH4);
            break;

        case TOUCH_CHANNEL_5:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_5);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH5);
            break;

        case TOUCH_CHANNEL_6:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_6);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH6);
            break;

        case TOUCH_CHANNEL_7:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_7);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH7);
            break;

        case TOUCH_CHANNEL_8:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_8);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH8);
            break;

        case TOUCH_CHANNEL_9:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_9);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH9);
            break;

        case TOUCH_CHANNEL_10:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_10);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH10);
            break;

        case TOUCH_CHANNEL_11:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_LTA_DATA_11);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_LTA_DATA_CH11);
            break;
    }

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  get touch moudle FLT data
 *
 * @param  touchId: touch moudle ID
 * @param  tCh: touch moudle channel
 *
 * @return FLT data
 *
*******************************************************************************/
uint32_t TOUCH_GetFltData(TOUCH_ID_Type touchId, TOUCH_CHANNEL_Type tCh)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    switch (tCh) {
        case TOUCH_CHANNEL_0:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_0);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH0);
            break;

        case TOUCH_CHANNEL_1:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_1);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH1);
            break;

        case TOUCH_CHANNEL_2:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_2);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH2);
            break;

        case TOUCH_CHANNEL_3:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_3);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH3);
            break;

        case TOUCH_CHANNEL_4:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_4);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH4);
            break;

        case TOUCH_CHANNEL_5:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_5);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH5);
            break;

        case TOUCH_CHANNEL_6:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_6);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH6);
            break;

        case TOUCH_CHANNEL_7:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_7);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH7);
            break;

        case TOUCH_CHANNEL_8:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_8);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH8);
            break;

        case TOUCH_CHANNEL_9:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_9);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH9);
            break;

        case TOUCH_CHANNEL_10:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_10);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH10);
            break;

        case TOUCH_CHANNEL_11:
            tmpVal = BL_RD_REG(PDS_BASE, PDS_CHANNEL_FLT_DATA_11);
            tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_FLT_DATA_CH11);
            break;
    }

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  get touch end flag
 *
 * @param  touchId: touch moudle ID
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type TOUCH_GetEndStatus(TOUCH_ID_Type touchId)
{
    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));

    return BL_GET_REG_BITS_VAL(BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_STATUS), PDS_TOUCH_END_FLAG) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  touch interrupt enable
 *
 * @param  touchId: touch moudle ID
 * @param  intType: touch moudle interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_IntEnable(TOUCH_ID_Type touchId, TOUCH_INT_Type intType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_INT_TYPE(intType));

    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_SETTING);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDS_TOUCH_INT_EN);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_INT_SETTING, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch interrupt disable
 *
 * @param  touchId: touch moudle ID
 * @param  intType: touch moudle interrupt type
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_IntDisable(TOUCH_ID_Type touchId, TOUCH_INT_Type intType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_INT_TYPE(intType));

    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_SETTING);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PDS_TOUCH_INT_EN);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_INT_SETTING, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch interrupt mask or not
 *
 * @param  touchId: touch moudle ID
 * @param  intType: touch moudle interrupt type
 * @param  tCh: touch moudle channel
 * @param  intMask: MASK or UNMASK
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_IntMask(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;
    uint32_t tmpMask = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_INT_TYPE(intType));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    TOUCH_IntEnable(touchId, intType);

    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_SETTING);

    if (intMask == MASK) {
        tmpMask = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_MASK);
        tmpMask |= (1 << tCh);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_MASK, tmpMask);
    } else {
        tmpMask = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_MASK);
        tmpMask &= (~(1 << tCh));
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_MASK, tmpMask);
    }

    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_INT_SETTING, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  get touch interrupt status
 *
 * @param  touchId: touch moudle ID
 * @param  intType: touch moudle interrupt type
 * @param  tCh: touch moudle channel
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type TOUCH_GetIntStatus(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_INT_TYPE(intType));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_STATUS);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_STATUS);

    if (tmpVal & (1 << tCh)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  clear touch interrupt status
 *
 * @param  touchId: touch moudle ID
 * @param  intType: touch moudle interrupt type
 * @param  tCh: touch moudle channel
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_ClrIntStatus(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh)
{
    uint32_t tmpVal = 0;
    uint32_t tmpClr = 0;

    CHECK_PARAM(IS_TOUCH_ID_TYPE(touchId));
    CHECK_PARAM(IS_TOUCH_INT_TYPE(intType));
    CHECK_PARAM(IS_TOUCH_CHANNEL_TYPE(tCh));

    /* set */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_SETTING);
    tmpClr = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_CLR);
    tmpClr |= (1 << tCh);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_CLR, tmpClr);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_INT_SETTING, tmpVal);

    /* unset */
    tmpVal = BL_RD_REG(PDS_BASE, PDS_TOUCH_INT_SETTING);
    tmpClr = BL_GET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_CLR);
    tmpClr &= (~(1 << tCh));
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDS_TOUCH_INT_CLR, tmpClr);
    tmpVal = BL_WR_REG(PDS_BASE, PDS_TOUCH_INT_SETTING, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  install touch interrupt callback
 *
 * @param  touchId: touch moudle ID
 * @param  intType: touch moudle interrupt type
 * @param  tCh: touch moudle channel
 * @param  cbFun: callback function
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TOUCH_INT_Callback_Install(TOUCH_ID_Type touchId, TOUCH_INT_Type intType, TOUCH_CHANNEL_Type tCh, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_TOUCH_INT_TYPE(intType));

    touchIntCbfArra[intType][tCh] = cbFun;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  touch IRQ handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void TOUCH_IRQHandler(void)
{
    TOUCH_CHANNEL_Type tmpCh;

    for (tmpCh = TOUCH_CHANNEL_0; tmpCh <= TOUCH_CHANNEL_11; tmpCh++) {
        if (SET == TOUCH_GetIntStatus(TOUCH_ID_0, TOUCH_INT_INTERRUPT, tmpCh)) {
            TOUCH_ClrIntStatus(TOUCH_ID_0, TOUCH_INT_INTERRUPT, tmpCh);

            if (touchIntCbfArra[TOUCH_INT_INTERRUPT][tmpCh] != NULL) {
                touchIntCbfArra[TOUCH_INT_INTERRUPT][tmpCh]();
            }
        }
    }
}

/*@} end of group TOUCH_Public_Functions */

/*@} end of group TOUCH */

/*@} end of group BL808_Peripheral_Driver */
