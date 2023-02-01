/**
  ******************************************************************************
  * @file    bl808_pwm.c
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

#include "bl808_pwm.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PWM
 *  @{
 */

/** @defgroup  PWM_Private_Macros
 *  @{
 */
#define PWMx_Get_Reg_Addr(id)  (PWM_BASE + PWM_CHANNEL_OFFSET + (id)*0x40)
#define PWM_INT_TIMEOUT_COUNT  (320 * 1000)
#define PWM_STOP_TIMEOUT_COUNT (320 * 1000)

/*@} end of group PWM_Private_Macros */

/** @defgroup  PWM_Private_Types
 *  @{
 */

/*@} end of group PWM_Private_Types */

/** @defgroup  PWM_Private_Variables
 *  @{
 */

/**
 *  @brief PWM interrupt callback function address array
*/
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *PWMIntCbfArra[PWMx_ID_MAX][PWM_INT_ALL] = { { NULL } };
#endif
/*@} end of group PWM_Private_Variables */

/** @defgroup  PWM_Global_Variables
 *  @{
 */

/*@} end of group PWM_Global_Variables */

/** @defgroup  PWM_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type PWM_IntHandler(IRQn_Type intPeriph);
#endif

/*@} end of group PWM_Private_Fun_Declaration */

/** @defgroup  PWM_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  PWM interrupt handle
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static BL_Err_Type PWM_IntHandler(IRQn_Type intPeriph)
{
    uint32_t tmpVal = 0;
    uint32_t maskVal = 0;
    uint32_t PWMx;
    uint16_t intIndex;
    PWMx_ID_Type id;

    for (id = PWM0_ID; id < PWMx_ID_MAX; id++) {
        /* Get PWMx start register address */
        PWMx = PWMx_Get_Reg_Addr(id);
        tmpVal = BL_RD_REG(PWMx, PWM_INT_STS);
        maskVal = BL_RD_REG(PWMx, PWM_INT_MASK);
        for (intIndex = 0; intIndex < PWM_INT_ALL; intIndex++) {
            if (((1 << intIndex) & tmpVal) && (((1 << intIndex) & maskVal) == 0)) {
                if (intIndex == PWM_INT_REPT) {
                    if (BL_GET_REG_BITS_VAL(BL_RD_REG(PWMx, PWM_CONFIG0), PWM_STOP_ON_REPT) == 1) {
                        PWMx_Disable(id);
                    }
                }
                BL_WR_REG(PWMx, PWM_INT_CLEAR, 1 << intIndex);
                if (PWMIntCbfArra[id][intIndex] != NULL) {
                    PWMIntCbfArra[id][intIndex]();
                }
            }
        }
    }
    return SUCCESS;
}

#endif

/*@} end of group PWM_Private_Functions */

/** @defgroup  PWM_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  PWMx init
 *
 * @param  id: PWM ID
 * @param  chCfg: PWMx configuration
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type PWMx_Init(PWMx_ID_Type id, PWMx_CFG_Type *cfg)
{
    uint32_t tmpVal;
    uint32_t timeoutCnt = PWM_STOP_TIMEOUT_COUNT;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CLK_TYPE(cfg->clk));
    CHECK_PARAM(IS_PWM_STOP_MODE_TYPE(cfg->stopMode));
    CHECK_PARAM(IS_PWM_EXT_BREAK_POLARITY_TYPE(cfg->extPol));
    CHECK_PARAM(IS_PWM_TRIGADC_SOURCE_TYPE(cfg->adcSrc));

    /* Ungate pwm clock gate */
    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_PWM);

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    BL_WR_REG(PWMx, PWM_CONFIG0, BL_SET_REG_BIT(tmpVal, PWM_STOP_EN));
    while (!BL_IS_REG_BIT_SET(BL_RD_REG(PWMx, PWM_CONFIG0), PWM_STS_STOP)) {
        timeoutCnt--;
        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    }
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_REG_CLK_SEL, cfg->clk);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_STOP_MODE, cfg->stopMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_EXT_BREAK_PL, cfg->extPol);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_ADC_TRG_SRC, cfg->adcSrc);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_STOP_ON_REPT, cfg->stpRept);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CLK_DIV, cfg->clkDiv);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);

    /* Config pwm period and rept count */
    tmpVal = BL_RD_REG(PWMx, PWM_PERIOD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_PERIOD, cfg->period);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_INT_PERIOD_CNT, cfg->intPulseCnt);
    BL_WR_REG(PWMx, PWM_PERIOD, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(PWM_IRQn, PWM_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  PWMx update clock divider
 *
 * @param  id: PWM ID
 * @param  div: Clock divider
 *
 * @return None
 *
*******************************************************************************/
void PWMx_Div_Set(PWMx_ID_Type id, uint16_t div)
{
    uint32_t tmpVal;
    //* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CLK_DIV, div);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  PWMx update period
 *
 * @param  id: PWM ID
 * @param  period: period
 *
 * @return None
 *
*******************************************************************************/
void PWMx_Period_Set(PWMx_ID_Type id, uint16_t period)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* Config pwm period and duty */
    tmpVal = BL_RD_REG(PWMx, PWM_PERIOD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_PERIOD, period);
    BL_WR_REG(PWMx, PWM_PERIOD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  PWMx get configuration
 *
 * @param  id: PWM ID
 * @param  period: period pointer
 *
 * @return None
 *
*******************************************************************************/
void PWMx_Period_Get(PWMx_ID_Type id, uint16_t *period)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* get pwm period */
    tmpVal = BL_RD_REG(PWMx, PWM_PERIOD);
    *period = BL_GET_REG_BITS_VAL(tmpVal, PWM_PERIOD);
}

/****************************************************************************/ /**
 * @brief  PWMx enable
 *
 * @param  id: PWMx ID
 *
 * @return None
 *
*******************************************************************************/
void PWMx_Enable(PWMx_ID_Type id)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* Config pwm clock to enable pwm */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    BL_WR_REG(PWMx, PWM_CONFIG0, BL_CLR_REG_BIT(tmpVal, PWM_STOP_EN));
}

/****************************************************************************/ /**
 * @brief  PWMx disable
 *
 * @param  id: PWMx ID
 *
 * @return None
 *
*******************************************************************************/
void PWMx_Disable(PWMx_ID_Type id)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(id));

    /* Config pwm clock to disable pwm */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    BL_WR_REG(PWMx, PWM_CONFIG0, BL_SET_REG_BIT(tmpVal, PWM_STOP_EN));
}

void PWM_Channelx_Init(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_CHx_CFG_Type *cfg)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_MODE_TYPE(cfg->modP));
    CHECK_PARAM(IS_PWM_MODE_TYPE(cfg->modN));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(cfg->polP));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(cfg->polN));
    CHECK_PARAM(IS_PWM_IDLE_STATE_TYPE(cfg->idlP));
    CHECK_PARAM(IS_PWM_IDLE_STATE_TYPE(cfg->idlN));
    CHECK_PARAM(IS_PWM_BREAK_STATE_TYPE(cfg->brkP));
    CHECK_PARAM(IS_PWM_BREAK_STATE_TYPE(cfg->brkN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PEN, cfg->modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NEN, cfg->modN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PPL, cfg->polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NPL, cfg->polN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PSI, cfg->idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NSI, cfg->idlN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PBS, cfg->brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NBS, cfg->brkN);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PEN, cfg->modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NEN, cfg->modN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PPL, cfg->polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NPL, cfg->polN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PSI, cfg->idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NSI, cfg->idlN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PBS, cfg->brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NBS, cfg->brkN);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PEN, cfg->modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NEN, cfg->modN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PPL, cfg->polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NPL, cfg->polN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PSI, cfg->idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NSI, cfg->idlN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PBS, cfg->brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NBS, cfg->brkN);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PEN, cfg->modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NEN, cfg->modN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PPL, cfg->polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NPL, cfg->polN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PSI, cfg->idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NSI, cfg->idlN);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PBS, cfg->brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NBS, cfg->brkN);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);

    /* Config pwm thresholdL and thresholdH */
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_RD_REG(PWMx, PWM_CH0_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_THREL, cfg->thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_THREH, cfg->thresholdH);
            BL_WR_REG(PWMx, PWM_CH0_THRE, tmpVal);
            break;
        case PWM_CH1:
            tmpVal = BL_RD_REG(PWMx, PWM_CH1_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_THREL, cfg->thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_THREH, cfg->thresholdH);
            BL_WR_REG(PWMx, PWM_CH1_THRE, tmpVal);
            break;
        case PWM_CH2:
            tmpVal = BL_RD_REG(PWMx, PWM_CH2_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_THREL, cfg->thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_THREH, cfg->thresholdH);
            BL_WR_REG(PWMx, PWM_CH2_THRE, tmpVal);
            break;
        case PWM_CH3:
            tmpVal = BL_RD_REG(PWMx, PWM_CH3_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_THREL, cfg->thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_THREH, cfg->thresholdH);
            BL_WR_REG(PWMx, PWM_CH3_THRE, tmpVal);
            break;
        default:
            break;
    }

    /* Config pwm dead time */
    tmpVal = BL_RD_REG(PWMx, PWM_DEAD_TIME);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_DTG, cfg->dtg);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_DTG, cfg->dtg);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_DTG, cfg->dtg);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_DTG, cfg->dtg);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_DEAD_TIME, tmpVal);
}

void PWM_Channelx_Threshold_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t thresholdL, uint16_t thresholdH)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));

    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_RD_REG(PWMx, PWM_CH0_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_THREL, thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH0_THRE, tmpVal);
            break;
        case PWM_CH1:
            tmpVal = BL_RD_REG(PWMx, PWM_CH1_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_THREL, thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH1_THRE, tmpVal);
            break;
        case PWM_CH2:
            tmpVal = BL_RD_REG(PWMx, PWM_CH2_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_THREL, thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH2_THRE, tmpVal);
            break;
        case PWM_CH3:
            tmpVal = BL_RD_REG(PWMx, PWM_CH3_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_THREL, thresholdL);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH3_THRE, tmpVal);
            break;
        default:
            break;
    }
}

void PWM_Channelx_ThresholdL_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t thresholdL)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));

    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_RD_REG(PWMx, PWM_CH0_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_THREL, thresholdL);
            BL_WR_REG(PWMx, PWM_CH0_THRE, tmpVal);
            break;
        case PWM_CH1:
            tmpVal = BL_RD_REG(PWMx, PWM_CH1_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_THREL, thresholdL);
            BL_WR_REG(PWMx, PWM_CH1_THRE, tmpVal);
            break;
        case PWM_CH2:
            tmpVal = BL_RD_REG(PWMx, PWM_CH2_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_THREL, thresholdL);
            BL_WR_REG(PWMx, PWM_CH2_THRE, tmpVal);
            break;
        case PWM_CH3:
            tmpVal = BL_RD_REG(PWMx, PWM_CH3_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_THREL, thresholdL);
            BL_WR_REG(PWMx, PWM_CH3_THRE, tmpVal);
            break;
        default:
            break;
    }
}

void PWM_Channelx_ThresholdH_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t thresholdH)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));

    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_RD_REG(PWMx, PWM_CH0_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH0_THRE, tmpVal);
            break;
        case PWM_CH1:
            tmpVal = BL_RD_REG(PWMx, PWM_CH1_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH1_THRE, tmpVal);
            break;
        case PWM_CH2:
            tmpVal = BL_RD_REG(PWMx, PWM_CH2_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH2_THRE, tmpVal);
            break;
        case PWM_CH3:
            tmpVal = BL_RD_REG(PWMx, PWM_CH3_THRE);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_THREH, thresholdH);
            BL_WR_REG(PWMx, PWM_CH3_THRE, tmpVal);
            break;
        default:
            break;
    }
}

void PWM_Channelx_Threshold_Get(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t *thresholdL, uint16_t *thresholdH)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));

    /* get pwm thresholdL and thresholdH */
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_RD_REG(PWMx, PWM_CH0_THRE);
            *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH0_THREL);
            *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH0_THREH);
            break;
        case PWM_CH1:
            tmpVal = BL_RD_REG(PWMx, PWM_CH1_THRE);
            *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH1_THREL);
            *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH1_THREH);
            break;
        case PWM_CH2:
            tmpVal = BL_RD_REG(PWMx, PWM_CH2_THRE);
            *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH2_THREL);
            *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH2_THREH);
            break;
        case PWM_CH3:
            tmpVal = BL_RD_REG(PWMx, PWM_CH3_THRE);
            *thresholdL = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH3_THREL);
            *thresholdH = BL_GET_REG_BITS_VAL(tmpVal, PWM_CH3_THREH);
            break;
        default:
            break;
    }
}

void PWM_Channelx_Pwm_Mode_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Mode_Type modP, PWM_Mode_Type modN)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_MODE_TYPE(modP));
    CHECK_PARAM(IS_PWM_MODE_TYPE(modN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PEN, modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NEN, modN);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PEN, modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NEN, modN);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PEN, modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NEN, modN);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PEN, modP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NEN, modN);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}
void PWM_Channelx_Positive_Pwm_Mode_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Mode_Type mod)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_MODE_TYPE(mod));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PEN, mod);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PEN, mod);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PEN, mod);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PEN, mod);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}
void PWM_Channelx_Negative_Pwm_Mode_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Mode_Type mod)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_MODE_TYPE(mod));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NEN, mod);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NEN, mod);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NEN, mod);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NEN, mod);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Polarity_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Polarity_Type polP, PWM_Polarity_Type polN)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(polP));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(polN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PPL, polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NPL, polN);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PPL, polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NPL, polN);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PPL, polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NPL, polN);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PPL, polP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NPL, polN);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Positive_Polarity_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Polarity_Type pol)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(pol));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PPL, pol);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PPL, pol);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PPL, pol);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PPL, pol);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Negative_Polarity_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Polarity_Type pol)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_POLARITY_TYPE(pol));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NPL, pol);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NPL, pol);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NPL, pol);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NPL, pol);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Idle_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Idle_State_Type idlP, PWM_Idle_State_Type idlN)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_IDLE_STATE_TYPE(idlP));
    CHECK_PARAM(IS_PWM_IDLE_STATE_TYPE(idlN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PSI, idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NSI, idlN);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PSI, idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NSI, idlN);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PSI, idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NSI, idlN);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PSI, idlP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NSI, idlN);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Positive_Idle_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Idle_State_Type idl)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_IDLE_STATE_TYPE(idl));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PSI, idl);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PSI, idl);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PSI, idl);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PSI, idl);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Negative_Idle_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Idle_State_Type idl)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_IDLE_STATE_TYPE(idl));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NSI, idl);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NSI, idl);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NSI, idl);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NSI, idl);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Break_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Break_State_Type brkP, PWM_Break_State_Type brkN)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_BREAK_STATE_TYPE(brkP));
    CHECK_PARAM(IS_PWM_BREAK_STATE_TYPE(brkN));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PBS, brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NBS, brkN);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PBS, brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NBS, brkN);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PBS, brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NBS, brkN);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PBS, brkP);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NBS, brkN);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Positive_Break_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Break_State_Type brk)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_BREAK_STATE_TYPE(brk));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_PBS, brk);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_PBS, brk);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_PBS, brk);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_PBS, brk);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Channelx_Negative_Break_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Break_State_Type brk)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));
    CHECK_PARAM(IS_PWM_BREAK_STATE_TYPE(brk));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG1);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_NBS, brk);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_NBS, brk);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_NBS, brk);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_NBS, brk);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_CONFIG1, tmpVal);
}

void PWM_Config1_Set(PWMx_ID_Type id, uint32_t cfg)
{
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* Config pwm config1 */
    BL_WR_REG(PWMx, PWM_CONFIG1, cfg);
}

void PWM_Config1_Get(PWMx_ID_Type id, uint32_t *cfg)
{
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* Get pwm config1 value */
    *cfg = BL_RD_REG(PWMx, PWM_CONFIG1);
}

void PWM_Channelx_Dtg_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint8_t dtg)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_CHx_TYPE(ch));

    /* Config pwm config1 */
    tmpVal = BL_RD_REG(PWMx, PWM_DEAD_TIME);
    switch (ch) {
        case PWM_CH0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH0_DTG, dtg);
            break;
        case PWM_CH1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH1_DTG, dtg);
            break;
        case PWM_CH2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH2_DTG, dtg);
            break;
        case PWM_CH3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_CH3_DTG, dtg);
            break;
        default:
            break;
    }
    BL_WR_REG(PWMx, PWM_DEAD_TIME, tmpVal);
}

void PWM_SW_Break_Enable(PWMx_ID_Type id)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, PWM_SW_BREAK_EN);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

void PWM_SW_Break_Disable(PWMx_ID_Type id)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PWM_SW_BREAK_EN);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

void PWM_EXT_Break_Enable(PWMx_ID_Type id)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(id));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_SET_REG_BIT(tmpVal, PWM_EXT_BREAK_EN);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

void PWM_EXT_Break_Disable(PWMx_ID_Type id)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(id));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, PWM_EXT_BREAK_EN);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

void PWM_EXT_Break_Polarity_Set(PWMx_ID_Type id, PWM_EXT_Break_Polarity_Type pol)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_EXT_BREAK_POLARITY_TYPE(pol));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_EXT_BREAK_PL, pol);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

void PWM_TrigADC_Source_Set(PWMx_ID_Type id, PWM_TrigADC_Source_Type src)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_TRIGADC_SOURCE_TYPE(src));

    /* Config pwm config0 */
    tmpVal = BL_RD_REG(PWMx, PWM_CONFIG0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PWM_ADC_TRG_SRC, src);
    BL_WR_REG(PWMx, PWM_CONFIG0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Mask/Unmask the PWM interrupt
 *
 * @param  id: PWM ID
 * @param  intType: Specifies the interrupt type
 * @param  intMask: Enable/Disable Specified interrupt type
 *
 * @return None
 *
*******************************************************************************/
void PWM_Int_Mask(PWMx_ID_Type id, PWM_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_INT_TYPE(intType));

    tmpVal = BL_RD_REG(PWMx, PWM_INT_MASK);
    if (intType == PWM_INT_ALL) {
        if (intMask == UNMASK) {
            tmpVal &= ~((1U << PWM_INT_ALL) - 1);
        } else {
            tmpVal |= ((1U << PWM_INT_ALL) - 1);
        }
    } else {
        if (intMask == UNMASK) {
            tmpVal &= ~(1U << intType);
        } else {
            tmpVal |= (1U << intType);
        }
    }
    BL_WR_REG(PWMx, PWM_INT_MASK, tmpVal);
}

void PWM_Int_Clear(PWMx_ID_Type id, PWM_INT_Type intType)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWMx_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_INT_TYPE(intType));

    tmpVal = BL_RD_REG(PWMx, PWM_INT_CLEAR);

    if (intType == PWM_INT_ALL) {
        tmpVal = ((1U << PWM_INT_ALL) - 1);
    } else {
        tmpVal = (1U << intType);
    }
    BL_WR_REG(PWMx, PWM_INT_CLEAR, tmpVal);
}

BL_Sts_Type PWM_Int_Status_Get(PWMx_ID_Type id, PWM_INT_Type intType)
{
    uint32_t tmpVal;
    /* Get PWMx start register address */
    uint32_t PWMx = PWMx_Get_Reg_Addr(id);

    /* Check the parameters */
    CHECK_PARAM(IS_PWM_CH_ID_TYPE(id));
    CHECK_PARAM(IS_PWM_INT_TYPE(intType));

    tmpVal = BL_RD_REG(PWMx, PWM_INT_STS);

    if (intType == PWM_INT_ALL) {
        if (tmpVal & ((1 << PWM_CHx_MAX) - 1)) {
            return SET;
        } else {
            return RESET;
        }
    } else {
        if (tmpVal & (1 << intType)) {
            return SET;
        } else {
            return RESET;
        }
    }
}

/****************************************************************************/ /**
 * @brief  Install PWM interrupt callback function
 *
 * @param  id: PWM ID
 * @param  intType: PWM interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void PWM_Int_Callback_Install(PWMx_ID_Type id, uint32_t intType, intCallback_Type *cbFun)
{
    PWMIntCbfArra[id][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  PWM interrupt function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void PWM_IRQHandler(void)
{
    PWM_IntHandler(PWM_IRQn);
}
#endif

/*@} end of group PWM_Public_Functions */

/*@} end of group PWM */

/*@} end of group BL808_Peripheral_Driver */
