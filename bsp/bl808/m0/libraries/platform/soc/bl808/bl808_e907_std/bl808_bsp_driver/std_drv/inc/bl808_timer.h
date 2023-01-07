/**
  ******************************************************************************
  * @file    bl808_timer.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __BL808_TIMER_H__
#define __BL808_TIMER_H__

#include "timer_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TIMER
 *  @{
 */

/** @defgroup  TIMER_Public_Types
 *  @{
 */

/**
 *  @brief TIMER port type definition
 */
typedef enum {
    TIMER0_ID,    /*!< TIMER0 port define */
    TIMER1_ID,    /*!< TIMER1 port define */
    TIMER_ID_MAX, /*!< TIMER MAX ID define */
} TIMER_ID_Type;

/**
 *  @brief Watchdog timer port type definition
 */
typedef enum {
    WDT0_ID,    /*!< Watchdog0 port define */
    WDT1_ID,    /*!< Watchdog1 port define */
    WDT_ID_MAX, /*!< Watchdog MAX ID define */
} WDT_ID_Type;

/**
 *  @brief TIMER channel type definition
 */
typedef enum {
    TIMER_CH0,    /*!< TIMER channel 0 port define */
    TIMER_CH1,    /*!< TIMER channel 1 port define */
    TIMER_CH_MAX, /*!<  */
} TIMER_Chan_Type;

/**
 *  @brief TIMER clock source type definition
 */
typedef enum {
    TIMER_CLKSRC_FCLK, /*!< TIMER clock source :System CLK */
    TIMER_CLKSRC_32K,  /*!< TIMER clock source :32K CLK */
    TIMER_CLKSRC_1K,   /*!< TIMER clock source :1K CLK,Only for Timer not for Watchdog */
    TIMER_CLKSRC_XTAL, /*!< TIMER clock source :XTAL CLK */
    TIMER_CLKSRC_GPIO, /*!< TIMER clock source :GPIO */
    TIMER_CLKSRC_NO,   /*!< TIMER clock source :No CLK */
} TIMER_ClkSrc_Type;

/**
 *  @brief TIMER match compare ID type definition
 */
typedef enum {
    TIMER_COMP_ID_0, /*!< TIMER match compare ID 0 define */
    TIMER_COMP_ID_1, /*!< TIMER match compare ID 1 define */
    TIMER_COMP_ID_2, /*!< TIMER match compare ID 2 define */
} TIMER_Comp_ID_Type;

/**
 *  @brief TIMER preload source type definition
 */
typedef enum {
    TIMER_PRELOAD_TRIG_NONE,  /*!< TIMER no preload source, just free run */
    TIMER_PRELOAD_TRIG_COMP0, /*!< TIMER count register preload triggered by comparator 0 */
    TIMER_PRELOAD_TRIG_COMP1, /*!< TIMER count register preload triggered by comparator 1 */
    TIMER_PRELOAD_TRIG_COMP2, /*!< TIMER count register preload triggered by comparator 2 */
} TIMER_PreLoad_Trig_Type;

/**
 *  @brief TIMER count register run mode type definition
 */
typedef enum {
    TIMER_COUNT_PRELOAD, /*!< TIMER count register preload from comparator register */
    TIMER_COUNT_FREERUN, /*!< TIMER count register free run */
} TIMER_CountMode_Type;

/**
 *  @brief TIMER gpio polarity type definition
 */
typedef enum {
    TIMER_GPIO_POS, /*!< TIMER gpio plarity posedge */
    TIMER_GPIO_NEG, /*!< TIMER gpio plarity negedge */
} TIMER_GPIO_Polarity_Type;

/**
 *  @brief TIMER interrupt type definition
 */
typedef enum {
    TIMER_INT_COMP_0, /*!< Comparator 0 match cause interrupt */
    TIMER_INT_COMP_1, /*!< Comparator 1 match cause interrupt */
    TIMER_INT_COMP_2, /*!< Comparator 2 match cause interrupt */
    TIMER_INT_ALL,    /*!<  */
} TIMER_INT_Type;

/**
 *  @brief Watchdog timer interrupt type definition
 */
typedef enum {
    WDT_INT,     /*!< Comparator 0 match cause interrupt */
    WDT_INT_ALL, /*!<  */
} WDT_INT_Type;

/**
 *  @brief TIMER configuration structure type definition
 */
typedef struct
{
    TIMER_Chan_Type timerCh;           /*!< Timer channel */
    TIMER_ClkSrc_Type clkSrc;          /*!< Timer clock source */
    TIMER_PreLoad_Trig_Type plTrigSrc; /*!< Timer count register preload trigger source slelect */
    TIMER_CountMode_Type countMode;    /*!< Timer count mode */
    uint8_t clockDivision;             /*!< Timer clock divison value */
    uint32_t matchVal0;                /*!< Timer match 0 value 0 */
    uint32_t matchVal1;                /*!< Timer match 1 value 0 */
    uint32_t matchVal2;                /*!< Timer match 2 value 0 */
    uint32_t preLoadVal;               /*!< Timer preload value */
} TIMER_CFG_Type;

/*@} end of group TIMER_Public_Types */

/** @defgroup  TIMER_Public_Constants
 *  @{
 */

/** @defgroup  TIMER_ID_TYPE
 *  @{
 */
#define IS_TIMER_ID_TYPE(type) (((type) == TIMER0_ID) || \
                                ((type) == TIMER1_ID) || \
                                ((type) == TIMER_ID_MAX))

/** @defgroup  WDT_ID_TYPE
 *  @{
 */
#define IS_WDT_ID_TYPE(type) (((type) == WDT0_ID) || \
                              ((type) == WDT1_ID) || \
                              ((type) == WDT_ID_MAX))

/** @defgroup  TIMER_CHAN_TYPE
 *  @{
 */
#define IS_TIMER_CHAN_TYPE(type) (((type) == TIMER_CH0) || \
                                  ((type) == TIMER_CH1) || \
                                  ((type) == TIMER_CH_MAX))

/** @defgroup  TIMER_CLKSRC_TYPE
 *  @{
 */
#define IS_TIMER_CLKSRC_TYPE(type) (((type) == TIMER_CLKSRC_FCLK) || \
                                    ((type) == TIMER_CLKSRC_32K) ||  \
                                    ((type) == TIMER_CLKSRC_1K) ||   \
                                    ((type) == TIMER_CLKSRC_XTAL) || \
                                    ((type) == TIMER_CLKSRC_GPIO) || \
                                    ((type) == TIMER_CLKSRC_NO))

/** @defgroup  TIMER_COMP_ID_TYPE
 *  @{
 */
#define IS_TIMER_COMP_ID_TYPE(type) (((type) == TIMER_COMP_ID_0) || \
                                     ((type) == TIMER_COMP_ID_1) || \
                                     ((type) == TIMER_COMP_ID_2))

/** @defgroup  TIMER_PRELOAD_TRIG_TYPE
 *  @{
 */
#define IS_TIMER_PRELOAD_TRIG_TYPE(type) (((type) == TIMER_PRELOAD_TRIG_NONE) ||  \
                                          ((type) == TIMER_PRELOAD_TRIG_COMP0) || \
                                          ((type) == TIMER_PRELOAD_TRIG_COMP1) || \
                                          ((type) == TIMER_PRELOAD_TRIG_COMP2))

/** @defgroup  TIMER_COUNTMODE_TYPE
 *  @{
 */
#define IS_TIMER_COUNTMODE_TYPE(type) (((type) == TIMER_COUNT_PRELOAD) || \
                                       ((type) == TIMER_COUNT_FREERUN))

/** @defgroup  TIMER_GPIO_POLARITY_TYPE
 *  @{
 */
#define IS_TIMER_GPIO_POLARITY_TYPE(type) (((type) == TIMER_GPIO_POS) || \
                                           ((type) == TIMER_GPIO_NEG))

/** @defgroup  TIMER_INT_TYPE
 *  @{
 */
#define IS_TIMER_INT_TYPE(type) (((type) == TIMER_INT_COMP_0) || \
                                 ((type) == TIMER_INT_COMP_1) || \
                                 ((type) == TIMER_INT_COMP_2) || \
                                 ((type) == TIMER_INT_ALL))

/** @defgroup  WDT_INT_TYPE
 *  @{
 */
#define IS_WDT_INT_TYPE(type) (((type) == WDT_INT) || \
                               ((type) == WDT_INT_ALL))

/*@} end of group TIMER_Public_Constants */

/** @defgroup  TIMER_Public_Macros
 *  @{
 */
#define WDT_ENABLE_ACCESS(baseAddr)                                                                                \
    {                                                                                                              \
        BL_WR_REG(baseAddr, TIMER_WFAR, BL_SET_REG_BITS_VAL(BL_RD_REG(baseAddr, TIMER_WFAR), TIMER_WFAR, 0xBABA)); \
        BL_WR_REG(baseAddr, TIMER_WSAR, BL_SET_REG_BITS_VAL(BL_RD_REG(baseAddr, TIMER_WSAR), TIMER_WSAR, 0xEB10)); \
    }

/*@} end of group TIMER_Public_Macros */

/** @defgroup  TIMER_Public_Functions
 *  @{
 */

/**
 *  @brief UART Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void TIMER0_CH0_IRQHandler(void);
void TIMER0_CH1_IRQHandler(void);
void TIMER0_WDT_IRQHandler(void);
void TIMER1_CH0_IRQHandler(void);
void TIMER1_CH1_IRQHandler(void);
void TIMER1_WDT_IRQHandler(void);
#endif
BL_Err_Type TIMER_Init(TIMER_ID_Type timerId, TIMER_CFG_Type *timerCfg);
BL_Err_Type TIMER_DeInit(TIMER_ID_Type timerId);
uint32_t TIMER_GetCompValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo);
void TIMER_SetCompValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo, uint32_t val);
void TIMER_CompValueEffectImmediately(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, BL_Fun_Type enable);
uint32_t TIMER_GetCounterValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
void TIMER_ResetCounterValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
BL_Sts_Type TIMER_GetMatchStatus(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo);
uint32_t TIMER_GetPreloadValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
void TIMER_SetPreloadValue(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, uint32_t val);
void TIMER_SetPreloadSrc(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_PreLoad_Trig_Type plSrc);
void TIMER_SetCountMode(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_CountMode_Type countMode);
void TIMER_ClearIntStatus(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_Comp_ID_Type cmpNo);
void TIMER_Enable(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
void TIMER_Disable(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
void TIMER_IntMask(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_INT_Type intType, BL_Mask_Type intMask);
void TIMER_GPIOSetPolarity(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_GPIO_Polarity_Type polarity);
void TIMER_CH0_SetMeasurePulseWidth(TIMER_ID_Type timerId, BL_Fun_Type enable);
uint32_t TIMER_CH0_GetMeasurePulseWidth(TIMER_ID_Type timerId);
void TIMER_ForceClockDivision(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh);
void TIMER_SetPreloadTrigSrc(TIMER_ID_Type timerId, TIMER_Chan_Type timerCh, TIMER_PreLoad_Trig_Type plSrc);
void TIMER_Int_Callback_Install(TIMER_ID_Type timerId, TIMER_Chan_Type timerChan, TIMER_INT_Type intType, intCallback_Type *cbFun);

void WDT_Set_Clock(WDT_ID_Type wdtId, TIMER_ClkSrc_Type clkSrc, uint8_t div);
uint16_t WDT_GetMatchValue(WDT_ID_Type wdtId);
void WDT_SetCompValue(WDT_ID_Type wdtId, uint16_t val);
void WDT_CompValueEffectImmediately(WDT_ID_Type wdtId, BL_Fun_Type enable);
uint16_t WDT_GetCounterValue(WDT_ID_Type wdtId);
void WDT_ResetCounterValue(WDT_ID_Type wdtId);
BL_Sts_Type WDT_GetResetStatus(WDT_ID_Type wdtId);
void WDT_ClearResetStatus(WDT_ID_Type wdtId);
void WDT_Enable(WDT_ID_Type wdtId);
void WDT_Disable(WDT_ID_Type wdtId);
void WDT_IntMask(WDT_ID_Type wdtId, WDT_INT_Type intType, BL_Mask_Type intMask);
void WDT_ForceClockDivision(WDT_ID_Type wdtId);
void WDT_Int_Callback_Install(WDT_ID_Type wdtId, WDT_INT_Type wdtInt, intCallback_Type *cbFun);
void WDT_GPIOSetPolarity(WDT_ID_Type wdtId, TIMER_GPIO_Polarity_Type polarity);

/*@} end of group TIMER_Public_Functions */

/*@} end of group TIMER */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_TIMER_H__ */
