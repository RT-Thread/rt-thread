/**
  ******************************************************************************
  * @file    bl808_timer.c
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

#include "bl808_timer.h"
#include "bl808_glb.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TIMER
 *  @{
 */

/** @defgroup  TIMER_Private_Macros
 *  @{
 */
#define TIMER_MAX_MATCH 3

/*@} end of group TIMER_Private_Macros */

/** @defgroup  TIMER_Private_Types
 *  @{
 */

/*@} end of group TIMER_Private_Types */

/** @defgroup  TIMER_Private_Variables
 *  @{
 */
static const uint32_t timerAddr[TIMER_ID_MAX] = { TIMER0_BASE, TIMER1_BASE };
#ifndef BFLB_USE_HAL_DRIVER
intCallback_Type *timerIntCbfArra[TIMER_ID_MAX][TIMER_CH_MAX][TIMER_INT_ALL] = { NULL };
intCallback_Type *wdtIntCbfArra[WDT_ID_MAX][WDT_INT_ALL] = { NULL };
#endif

/*@} end of group TIMER_Private_Variables */

/** @defgroup  TIMER_Global_Variables
 *  @{
 */

/*@} end of group TIMER_Global_Variables */

/** @defgroup  TIMER_Private_Fun_Declaration
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static void TIMER_IntHandler(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
#endif

/*@} end of group TIMER_Private_Fun_Declaration */

/** @defgroup  TIMER_Private_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  TIMER interrupt common handler function
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER_IntHandler(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t intId;
    uint32_t tmpVal;
    uint32_t tmpAddr;
    uint32_t TIMERx = timerAddr[timerId];

    intId = BL_RD_WORD(TIMERx + TIMER_TSR2_OFFSET + 4 * timerCh);
    tmpAddr = TIMERx + TIMER_TICR2_OFFSET + 4 * timerCh;
    tmpVal = BL_RD_WORD(tmpAddr);

    /* Comparator 0 match interrupt */
    if (BL_IS_REG_BIT_SET(intId, TIMER_TSR2_0)) {
        BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TSR2_0));

        if (timerIntCbfArra[timerId][timerCh][TIMER_INT_COMP_0] != NULL) {
            /* Call the callback function */
            timerIntCbfArra[timerId][timerCh][TIMER_INT_COMP_0]();
        }
    }

    /* Comparator 1 match interrupt */
    if (BL_IS_REG_BIT_SET(intId, TIMER_TSR2_1)) {
        BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TSR2_1));

        if (timerIntCbfArra[timerId][timerCh][TIMER_INT_COMP_1] != NULL) {
            /* Call the callback function */
            timerIntCbfArra[timerId][timerCh][TIMER_INT_COMP_1]();
        }
    }

    /* Comparator 2 match interrupt */
    if (BL_IS_REG_BIT_SET(intId, TIMER_TSR2_2)) {
        BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TSR2_2));

        if (timerIntCbfArra[timerId][timerCh][TIMER_INT_COMP_2] != NULL) {
            /* Call the callback function */
            timerIntCbfArra[timerId][timerCh][TIMER_INT_COMP_2]();
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Get the specified channel and match comparator value
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  cmpNo: TIMER comparator ID type
 *
 * @return Match comapre register value
 *
*******************************************************************************/
uint32_t TIMER_GetCompValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_COMP_ID_TYPE(cmpNo));

    tmpVal = BL_RD_WORD(TIMERx + TIMER_TMR2_0_OFFSET + 4 * (TIMER_MAX_MATCH * timerCh + cmpNo));
    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  TIMER set specified channel and comparator compare value
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  cmpNo: TIMER comparator ID type
 * @param  val: TIMER match compare register value
 *
 * @return None
 *
*******************************************************************************/
void TIMER_SetCompValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo, uint32_t val)
{
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_COMP_ID_TYPE(cmpNo));

    BL_WR_WORD(TIMERx + TIMER_TMR2_0_OFFSET + 4 * (TIMER_MAX_MATCH * timerCh + cmpNo), val);
}

/****************************************************************************/ /**
 * @brief  TIMER enable or disable compare value effect immediately after update
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void TIMER_CompValueEffectImmediately(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, BL_Fun_Type enable)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_TCMR);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER2_ALIGN, 1 - enable);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER3_ALIGN, 1 - enable);
    }

    BL_WR_REG(TIMERx, TIMER_TCMR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER get the specified channel count value
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 *
 * @return TIMER count register value
 *
*******************************************************************************/
uint32_t TIMER_GetCounterValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t tmpVal;
    uint32_t tmpAddr;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpAddr = TIMERx + TIMER_TCR2_OFFSET+ 4 * timerCh;
    tmpVal = BL_RD_WORD(tmpAddr);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  TIMER reset count value
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 *
 * @return None
 *
*******************************************************************************/
void TIMER_ResetCounterValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_TCER);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, TIMER_TCR2_CNT_CLR);
        BL_WR_REG(TIMERx, TIMER_TCER, tmpVal);
        tmpVal = BL_CLR_REG_BIT(tmpVal, TIMER_TCR2_CNT_CLR);
        BL_WR_REG(TIMERx, TIMER_TCER, tmpVal);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, TIMER_TCR3_CNT_CLR);
        BL_WR_REG(TIMERx, TIMER_TCER, tmpVal);
        tmpVal = BL_CLR_REG_BIT(tmpVal, TIMER_TCR3_CNT_CLR);
        BL_WR_REG(TIMERx, TIMER_TCER, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  TIMER get specified channel and comparator match status
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  cmpNo: TIMER comparator ID type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type TIMER_GetMatchStatus(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo)
{
    uint32_t tmpVal;
    BL_Sts_Type bitStatus = RESET;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_COMP_ID_TYPE(cmpNo));

    tmpVal = BL_RD_WORD(TIMERx + TIMER_TSR2_OFFSET + 4 * timerCh);

    switch (cmpNo) {
        case TIMER_COMP_ID_0:
            bitStatus = BL_IS_REG_BIT_SET(tmpVal, TIMER_TSR3_0) ? SET : RESET;
            break;

        case TIMER_COMP_ID_1:
            bitStatus = BL_IS_REG_BIT_SET(tmpVal, TIMER_TSR3_1) ? SET : RESET;
            break;

        case TIMER_COMP_ID_2:
            bitStatus = BL_IS_REG_BIT_SET(tmpVal, TIMER_TSR3_2) ? SET : RESET;
            break;

        default:
            break;
    }

    return bitStatus;
}

/****************************************************************************/ /**
 * @brief  TIMER get specified channel preload value
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 *
 * @return Preload register value
 *
*******************************************************************************/
uint32_t TIMER_GetPreloadValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    return BL_RD_WORD(TIMERx + TIMER_TPLVR2_OFFSET + 4 * timerCh);
}

/****************************************************************************/ /**
 * @brief  TIMER set preload register low 32bits value
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  val: Preload register low 32bits value
 *
 * @return None
 *
*******************************************************************************/
void TIMER_SetPreloadValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, uint32_t val)
{
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    BL_WR_WORD(TIMERx + TIMER_TPLVR2_OFFSET + 4 * timerCh, val);
}

/****************************************************************************/ /**
 * @brief  TIMER set preload trigger source,COMP0,COMP1,COMP2 or None
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  plSrc: TIMER preload source type
 *
 * @return None
 *
*******************************************************************************/
void TIMER_SetPreloadTrigSrc(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_PreLoad_Trig_Type plSrc)
{
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_PRELOAD_TRIG_TYPE(plSrc));

    BL_WR_WORD(TIMERx + TIMER_TPLCR2_OFFSET + 4 * timerCh, plSrc);
}

/****************************************************************************/ /**
 * @brief  TIMER set count mode:preload or free run
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  countMode: TIMER count mode: TIMER_COUNT_PRELOAD or TIMER_COUNT_FREERUN
 *
 * @return None
 *
*******************************************************************************/
void TIMER_SetCountMode(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_CountMode_Type countMode)
{
    uint32_t tmpval;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_COUNTMODE_TYPE(countMode));

    tmpval = BL_RD_WORD(TIMERx + TIMER_TCMR_OFFSET);
    tmpval &= (~(1 << (timerCh + 1)));
    tmpval |= (countMode << (timerCh + 1));

    BL_WR_WORD(TIMERx + TIMER_TCMR_OFFSET, tmpval);
}

/****************************************************************************/ /**
 * @brief  TIMER clear interrupt status
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  cmpNo: TIMER macth comparator ID type
 *
 * @return None
 *
*******************************************************************************/
void TIMER_ClearIntStatus(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo)
{
    uint32_t tmpAddr;
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_COMP_ID_TYPE(cmpNo));

    tmpAddr = TIMERx + TIMER_TICR2_OFFSET + 4 * timerCh;

    tmpVal = BL_RD_WORD(tmpAddr);
    tmpVal |= (1 << cmpNo);

    BL_WR_WORD(tmpAddr, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER initialization function
 *
 * @param  timerId: Timer ID type
 * @param  timerCfg: TIMER configuration structure pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type TIMER_Init(TIMER_ID_Type timerId, TIMER_CFG_Type *timerCfg)
{
    TIMER_Chan_Type timerCh = timerCfg->timerCh;
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CLKSRC_TYPE(timerCfg->clkSrc));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCfg->timerCh));
    CHECK_PARAM(IS_TIMER_PRELOAD_TRIG_TYPE(timerCfg->plTrigSrc));
    CHECK_PARAM(IS_TIMER_COUNTMODE_TYPE(timerCfg->countMode));

    GLB_PER_Clock_UnGate(GLB_AHB_CLOCK_TIMER);

    /* Configure timer clock source */
    tmpVal = BL_RD_REG(TIMERx, TIMER_TCCR);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_CS_2, timerCfg->clkSrc);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_CS_3, timerCfg->clkSrc);
    }

    BL_WR_REG(TIMERx, TIMER_TCCR, tmpVal);

    /* Configure timer clock division */
    tmpVal = BL_RD_REG(TIMERx, TIMER_TCDR);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_TCDR2, timerCfg->clockDivision);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_TCDR3, timerCfg->clockDivision);
    }

    BL_WR_REG(TIMERx, TIMER_TCDR, tmpVal);

    /* Configure timer count mode: preload or free run */
    TIMER_SetCountMode(timerId, timerCh, timerCfg->countMode);

    /* Configure timer preload trigger src */
    TIMER_SetPreloadTrigSrc(timerId, timerCh, timerCfg->plTrigSrc);

    if (timerCfg->countMode == TIMER_COUNT_PRELOAD) {
        /* Configure timer preload value */
        TIMER_SetPreloadValue(timerId, timerCh, timerCfg->preLoadVal);

        /* Configure match compare values */
        if (timerCfg->matchVal0 > 1 + timerCfg->preLoadVal) {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_0, timerCfg->matchVal0 - 2);
        } else {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_0, timerCfg->matchVal0);
        }

        if (timerCfg->matchVal1 > 1 + timerCfg->preLoadVal) {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_1, timerCfg->matchVal1 - 2);
        } else {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_1, timerCfg->matchVal1);
        }

        if (timerCfg->matchVal2 > 1 + timerCfg->preLoadVal) {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_2, timerCfg->matchVal2 - 2);
        } else {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_2, timerCfg->matchVal2);
        }
    } else {
        /* Configure match compare values */
        if (timerCfg->matchVal0 > 1) {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_0, timerCfg->matchVal0 - 2);
        } else {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_0, timerCfg->matchVal0);
        }

        if (timerCfg->matchVal1 > 1) {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_1, timerCfg->matchVal1 - 2);
        } else {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_1, timerCfg->matchVal1);
        }

        if (timerCfg->matchVal2 > 1) {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_2, timerCfg->matchVal2 - 2);
        } else {
            TIMER_SetCompValue(timerId, timerCh, TIMER_COMP_ID_2, timerCfg->matchVal2);
        }
    }

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(TIMER0_CH0_IRQn, TIMER0_CH0_IRQHandler);
    Interrupt_Handler_Register(TIMER0_CH1_IRQn, TIMER0_CH1_IRQHandler);
    Interrupt_Handler_Register(TIMER1_CH0_IRQn, TIMER1_CH0_IRQHandler);
    Interrupt_Handler_Register(TIMER1_CH1_IRQn, TIMER1_CH1_IRQHandler);

#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  TIMER set default value of all registers function
 *
 * @param  timerId: TIMER ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type TIMER_DeInit(TIMER_ID_Type timerId)
{
    if (TIMER0_ID == timerId) {
        GLB_AHB_MCU_Software_Reset(GLB_AHB_MCU_SW_TIMER);
    } else if (TIMER1_ID == timerId) {
        GLB_AHB_DSP_Software_Reset(GLB_AHB_DSP_SW_SWRST_TIMER);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  TIMER enable one channel function
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 *
 * @return None
 *
*******************************************************************************/
void TIMER_Enable(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_TCER);
    tmpVal |= (1 << (timerCh + 1));

    BL_WR_REG(TIMERx, TIMER_TCER, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER disable one channel function
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 *
 * @return None
 *
*******************************************************************************/
void TIMER_Disable(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_TCER);
    tmpVal &= (~(1 << (timerCh + 1)));

    BL_WR_REG(TIMERx, TIMER_TCER, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER mask or unmask certain or all interrupt
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  intType: TIMER interrupt type
 * @param  intMask: TIMER interrupt mask value:MASK:disbale interrupt.UNMASK:enable interrupt
 *
 * @return None
 *
*******************************************************************************/
void TIMER_IntMask(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpAddr;
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));
    CHECK_PARAM(IS_TIMER_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    tmpAddr = TIMERx + TIMER_TIER2_OFFSET + 4 * timerCh;
    tmpVal = BL_RD_WORD(tmpAddr);

    switch (intType) {
        case TIMER_INT_COMP_0:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TIER3_0));
            } else {
                /* Disable this interrupt */
                BL_WR_WORD(tmpAddr, BL_CLR_REG_BIT(tmpVal, TIMER_TIER3_0));
            }

            break;

        case TIMER_INT_COMP_1:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TIER3_1));
            } else {
                /* Disable this interrupt */
                BL_WR_WORD(tmpAddr, BL_CLR_REG_BIT(tmpVal, TIMER_TIER3_1));
            }

            break;

        case TIMER_INT_COMP_2:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TIER3_2));
            } else {
                /* Disable this interrupt */
                BL_WR_WORD(tmpAddr, BL_CLR_REG_BIT(tmpVal, TIMER_TIER3_2));
            }

            break;

        case TIMER_INT_ALL:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TIER3_0));
                BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TIER3_1));
                BL_WR_WORD(tmpAddr, BL_SET_REG_BIT(tmpVal, TIMER_TIER3_2));
            } else {
                /* Disable this interrupt */
                BL_WR_WORD(tmpAddr, BL_CLR_REG_BIT(tmpVal, TIMER_TIER3_0));
                BL_WR_WORD(tmpAddr, BL_CLR_REG_BIT(tmpVal, TIMER_TIER3_1));
                BL_WR_WORD(tmpAddr, BL_CLR_REG_BIT(tmpVal, TIMER_TIER3_2));
            }

            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  TIMER set gpio polarity
 *
 * @param  timerId: Timer ID type
 * @param  timerCh: TIMER channel type
 * @param  polarity: TIMER GPIO polarity
 *
 * @return None
 *
*******************************************************************************/
void TIMER_GPIOSetPolarity(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_GPIO_Polarity_Type polarity)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_GPIO);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER2_GPIO_INV, polarity);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER3_GPIO_INV, polarity);
    }

    BL_WR_REG(TIMERx, TIMER_GPIO, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER channel 0 enable or disable measure gpio pulse width function
 *
 * @param  timerId: Timer ID type
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void TIMER_CH0_SetMeasurePulseWidth(TIMER_ID_Type timerId, BL_Fun_Type enable)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));

    tmpVal = BL_RD_REG(TIMERx, TIMER_GPIO);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER2_GPIO_EN, enable);
    BL_WR_REG(TIMERx, TIMER_GPIO, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER channel 0 get gpio pulse width value function
 *
 * @param  timerId: Timer ID type
 *
 * @return Pulse width
 *
*******************************************************************************/
uint32_t TIMER_CH0_GetMeasurePulseWidth(TIMER_ID_Type timerId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));

    do {
        tmpVal = BL_RD_REG(TIMERx, TIMER_GPIO);
    } while (!BL_IS_REG_BIT_SET(tmpVal, TIMER_GPIO_LAT_OK));

    return (BL_RD_REG(TIMERx, TIMER_GPIO_LAT2) - BL_RD_REG(TIMERx, TIMER_GPIO_LAT1));
}

/****************************************************************************/ /**
 * @brief  TIMER force clock division
 *
 * @param  timerId: Timer ID type
 * @param  timerChan: TIMER channel type
 *
 * @return None
 *
*******************************************************************************/
void TIMER_ForceClockDivision(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[timerId];

    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerChan));

    /* write 0 after write 1 to force clock division */
    tmpVal = BL_RD_REG(TIMERx, TIMER_TCDR_FORCE);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, TIMER_TCDR2_FORCE);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, TIMER_TCDR3_FORCE);
    }

    BL_WR_REG(TIMERx, TIMER_TCDR_FORCE, tmpVal);

    tmpVal = BL_RD_REG(TIMERx, TIMER_TCDR_FORCE);

    if (timerCh == TIMER_CH0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, TIMER_TCDR2_FORCE);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, TIMER_TCDR3_FORCE);
    }

    BL_WR_REG(TIMERx, TIMER_TCDR_FORCE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER install interrupt callback
 *
 * @param  timerId: Timer ID type
 * @param  timerChan: TIMER channel type
 * @param  intType: TIMER interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER_Int_Callback_Install(TIMER_ID_Type timerId, TIMER_Chan_Type timerChan, TIMER_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_TIMER_ID_TYPE(timerId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerChan));
    CHECK_PARAM(IS_TIMER_INT_TYPE(intType));

    timerIntCbfArra[timerId][timerChan][intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  TIMER set watchdog clock source and clock division
 *
 * @param  wdtId: Watchdog ID type
 * @param  clkSrc: Watchdog timer clock source type
 * @param  div: Watchdog timer clock division value
 *
 * @return None
 *
*******************************************************************************/
void WDT_Set_Clock(WDT_ID_Type wdtId, TIMER_ClkSrc_Type clkSrc, uint8_t div)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));
    CHECK_PARAM(IS_TIMER_CLKSRC_TYPE(clkSrc));

    /* Configure watchdog timer clock source */
    tmpVal = BL_RD_REG(TIMERx, TIMER_TCCR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_CS_WDT, clkSrc);
    BL_WR_REG(TIMERx, TIMER_TCCR, tmpVal);

    /* Configure watchdog timer clock divison */
    tmpVal = BL_RD_REG(TIMERx, TIMER_TCDR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_WCDR, div);
    BL_WR_REG(TIMERx, TIMER_TCDR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER get watchdog match compare value
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return Watchdog match comapre register value
 *
*******************************************************************************/
uint16_t WDT_GetMatchValue(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    WDT_ENABLE_ACCESS(TIMERx);

    /* Get watchdog timer match register value */
    tmpVal = BL_RD_REG(TIMERx, TIMER_WMR);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, TIMER_WMR);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  TIMER set watchdog match compare value
 *
 * @param  wdtId: Watchdog ID type
 * @param  val: Watchdog match compare value
 *
 * @return None
 *
*******************************************************************************/
void WDT_SetCompValue(WDT_ID_Type wdtId, uint16_t val)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    WDT_ENABLE_ACCESS(TIMERx);

    /* Set watchdog timer match register value */
    tmpVal = BL_RD_REG(TIMERx, TIMER_WMR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_WMR, val);
    BL_WR_REG(TIMERx, TIMER_WMR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Watchdog enable or disable compare value effect immediately after update
 *
 * @param  wdtId: Watchdog ID type
 * @param  enable: Enable or disable
 *
 * @return None
 *
*******************************************************************************/
void WDT_CompValueEffectImmediately(WDT_ID_Type wdtId, BL_Fun_Type enable)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_WMR);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_WDT_ALIGN, 1 - enable);
    BL_WR_REG(TIMERx, TIMER_WMR, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER get watchdog count register value
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return Watchdog count register value
 *
*******************************************************************************/
uint16_t WDT_GetCounterValue(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    WDT_ENABLE_ACCESS(TIMERx);

    /* Get watchdog timer count register value */
    tmpVal = BL_RD_REG(TIMERx, TIMER_WVR);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  TIMER reset watchdog count register value
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return None
 *
*******************************************************************************/
void WDT_ResetCounterValue(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    /* Reset watchdog timer count register value */
    WDT_ENABLE_ACCESS(TIMERx);

    tmpVal = BL_RD_REG(TIMERx, TIMER_WCR);

    /* Set watchdog counter reset register bit0 to 1 */
    BL_WR_REG(TIMERx, TIMER_WCR, BL_SET_REG_BIT(tmpVal, TIMER_WCR));
}

/****************************************************************************/ /**
 * @brief  TIMER get watchdog reset status
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type WDT_GetResetStatus(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    WDT_ENABLE_ACCESS(TIMERx);

    /* Get watchdog status register */
    tmpVal = BL_RD_REG(TIMERx, TIMER_WSR);

    return (BL_IS_REG_BIT_SET(tmpVal, TIMER_WTS)) ? SET : RESET;
}

/****************************************************************************/ /**
 * @brief  TIMER clear watchdog reset status
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return None
 *
*******************************************************************************/
void WDT_ClearResetStatus(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    WDT_ENABLE_ACCESS(TIMERx);

    tmpVal = BL_RD_REG(TIMERx, TIMER_WSR);

    /* Set watchdog status register */
    BL_WR_REG(TIMERx, TIMER_WSR, BL_CLR_REG_BIT(tmpVal, TIMER_WTS));
}

/****************************************************************************/ /**
 * @brief  TIMER enable watchdog function
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return None
 *
*******************************************************************************/
void WDT_Enable(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(TIMER0_WDT_IRQn, TIMER0_WDT_IRQHandler);
    Interrupt_Handler_Register(TIMER1_WDT_IRQn, TIMER1_WDT_IRQHandler);
#endif

    WDT_ENABLE_ACCESS(TIMERx);

    tmpVal = BL_RD_REG(TIMERx, TIMER_WMER);

    BL_WR_REG(TIMERx, TIMER_WMER, BL_SET_REG_BIT(tmpVal, TIMER_WE));
}

/****************************************************************************/ /**
 * @brief  Watchdog timer disable function
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return None
 *
*******************************************************************************/
void WDT_Disable(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    WDT_ENABLE_ACCESS(TIMERx);

    tmpVal = BL_RD_REG(TIMERx, TIMER_WMER);

    BL_WR_REG(TIMERx, TIMER_WMER, BL_CLR_REG_BIT(tmpVal, TIMER_WE));
}

/****************************************************************************/ /**
 * @brief  Watchdog timer disable function
 *
 * @param  wdtId: Watchdog ID type
 *
 * @return None
 *
*******************************************************************************/
void WDT_ForceClockDivision(WDT_ID_Type wdtId)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));

    /* write 0 after write 1 to force clock division */
    tmpVal = BL_RD_REG(TIMERx, TIMER_TCDR_FORCE);

    tmpVal = BL_SET_REG_BIT(tmpVal, TIMER_WCDR_FORCE);

    BL_WR_REG(TIMERx, TIMER_TCDR_FORCE, tmpVal);

    tmpVal = BL_RD_REG(TIMERx, TIMER_TCDR_FORCE);

    tmpVal = BL_CLR_REG_BIT(tmpVal, TIMER_WCDR_FORCE);

    BL_WR_REG(TIMERx, TIMER_TCDR_FORCE, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Watchdog timer mask or unmask certain or all interrupt
 *
 * @param  wdtId: Watchdog ID type
 * @param  intType: Watchdog interrupt type
 * @param  intMask: Watchdog interrupt mask value:MASK:disbale interrupt.UNMASK:enable interrupt
 *
 * @return None
 *
*******************************************************************************/
void WDT_IntMask(WDT_ID_Type wdtId, WDT_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));
    CHECK_PARAM(IS_WDT_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    WDT_ENABLE_ACCESS(TIMERx);

    /* Deal with watchdog match/interrupt enable register,
	  WRIE:watchdog reset/interrupt enable */
    tmpVal = BL_RD_REG(TIMERx, TIMER_WMER);

    switch (intType) {
        case WDT_INT:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                /* 0 means generates a watchdog interrupt,
				   a watchdog timer reset is not generated*/
                BL_WR_REG(TIMERx, TIMER_WMER, BL_CLR_REG_BIT(tmpVal, TIMER_WRIE));
            } else {
                /* Disable this interrupt */
                /* 1 means generates a watchdog timer reset,
				   a watchdog  interrupt is not generated*/
                BL_WR_REG(TIMERx, TIMER_WMER, BL_SET_REG_BIT(tmpVal, TIMER_WRIE));
            }

            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  Watchdog install interrupt callback
 *
 * @param  wdtId: Watchdog ID type
 * @param  wdtInt: Watchdog interrupt type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void WDT_Int_Callback_Install(WDT_ID_Type wdtId, WDT_INT_Type wdtInt, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));
    CHECK_PARAM(IS_WDT_INT_TYPE(wdtInt));

    wdtIntCbfArra[wdtId][wdtInt] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  Watchdog set gpio polarity
 *
 * @param  wdtId: Watchdog ID type
 * @param  polarity: Watchdog GPIO polarity
 *
 * @return None
 *
*******************************************************************************/
void WDT_GPIOSetPolarity(WDT_ID_Type wdtId, TIMER_GPIO_Polarity_Type polarity)
{
    uint32_t tmpVal;
    uint32_t TIMERx = timerAddr[wdtId];

    /* Check the parameters */
    CHECK_PARAM(IS_WDT_ID_TYPE(wdtId));
    CHECK_PARAM(IS_TIMER_CHAN_TYPE(timerCh));

    tmpVal = BL_RD_REG(TIMERx, TIMER_GPIO);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, TIMER_WDT_GPIO_INV, polarity);
    BL_WR_REG(TIMERx, TIMER_GPIO, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TIMER0 channel 0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER0_CH0_IRQHandler(void)
{
    TIMER_IntHandler(TIMER0_ID, TIMER_CH0);
}
#endif

/****************************************************************************/ /**
 * @brief  TIMER0 channel 1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER0_CH1_IRQHandler(void)
{
    TIMER_IntHandler(TIMER0_ID, TIMER_CH1);
}
#endif

/****************************************************************************/ /**
 * @brief  TIMER0 watchdog interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER0_WDT_IRQHandler(void)
{
    uint32_t tmpVal;

    WDT_ENABLE_ACCESS(TIMER0_BASE);

    tmpVal = BL_RD_REG(TIMER0_BASE, TIMER_WICR);
    BL_WR_REG(TIMER0_BASE, TIMER_WICR, BL_SET_REG_BIT(tmpVal, TIMER_WICLR));

    if (wdtIntCbfArra[WDT0_ID][WDT_INT] != NULL) {
        /* Call the callback function */
        wdtIntCbfArra[WDT0_ID][WDT_INT]();
    }
}
#endif

/****************************************************************************/ /**
 * @brief  TIMER1 channel 0 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER1_CH0_IRQHandler(void)
{
    TIMER_IntHandler(TIMER1_ID, TIMER_CH0);
}
#endif

/****************************************************************************/ /**
 * @brief  TIMER1 channel 1 interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER1_CH1_IRQHandler(void)
{
    TIMER_IntHandler(TIMER1_ID, TIMER_CH1);
}
#endif

/****************************************************************************/ /**
 * @brief  TIMER1 watchdog interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void TIMER1_WDT_IRQHandler(void)
{
    uint32_t tmpVal;

    WDT_ENABLE_ACCESS(TIMER1_BASE);

    tmpVal = BL_RD_REG(TIMER1_BASE, TIMER_WICR);
    BL_WR_REG(TIMER1_BASE, TIMER_WICR, BL_SET_REG_BIT(tmpVal, TIMER_WICLR));

    if (wdtIntCbfArra[WDT1_ID][WDT_INT] != NULL) {
        /* Call the callback function */
        wdtIntCbfArra[WDT1_ID][WDT_INT]();
    }
}
#endif
/*@} end of group TIMER_Private_Functions */

/*@} end of group TIMER */

/*@} end of group BL808_Peripheral_Driver */
