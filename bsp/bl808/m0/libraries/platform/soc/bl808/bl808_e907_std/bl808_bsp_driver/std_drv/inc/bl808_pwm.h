/**
  ******************************************************************************
  * @file    bl808_pwm.h
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
#ifndef __BL808_PWM_H__
#define __BL808_PWM_H__

#include "pwm_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PWM
 *  @{
 */

/** @defgroup  PWM_Public_Types
 *  @{
 */

/**
 *  @brief PWM No. type definition
 */
typedef enum {
    PWM0_ID = 0, /*!< PWM Channel 0 define */
    PWM1_ID,     /*!< PWM Channel 1 define */
    PWMx_ID_MAX, /*!<  */
} PWMx_ID_Type;

/**
 *  @brief PWM Clock definition
 */
typedef enum {
    PWM_CLK_XCLK = 0, /*!< PWM Clock source :XTAL CLK */
    PWM_CLK_BCLK,     /*!< PWM Clock source :Bus CLK */
    PWM_CLK_32K,      /*!< PWM Clock source :32K CLK */
} PWM_Clk_Type;

/**
 *  @brief PWM Stop Mode definition
 */
typedef enum {
    PWM_STOP_ABRUPT = 0, /*!< PWM stop abrupt select define */
    PWM_STOP_GRACEFUL,   /*!< PWM stop graceful select define */
} PWM_Stop_Mode_Type;

/**
 *  @brief PWM mode type def
 */
typedef enum {
    PWM_POL_ACTIVE_LOW = 0, /*!< PWM active low polarity mode define */
    PWM_POL_ACTIVE_HIGH,    /*!< PWM active high polarity mode define */
} PWM_Polarity_Type;

/**
 *  @brief PWM interrupt type def
 */
typedef enum {
    PWM_INT_CH0L = 0, /*!< PWM Channel 0L interrupt define */
    PWM_INT_CH0H,     /*!< PWM Channel 0H interrupt define */
    PWM_INT_CH1L,     /*!< PWM Channel 1H interrupt define */
    PWM_INT_CH1H,     /*!< PWM Channel 1H interrupt define */
    PWM_INT_CH2L,     /*!< PWM Channel 2L interrupt define */
    PWM_INT_CH2H,     /*!< PWM Channel 2H interrupt define */
    PWM_INT_CH3L,     /*!< PWM Channel 3L interrupt define */
    PWM_INT_CH3H,     /*!< PWM Channel 3H interrupt define */
    PWM_INT_PRDE,     /*!< PWM Period end interrupt define */
    PWM_INT_BRK,      /*!< PWM break interrupt define */
    PWM_INT_REPT,     /*!< PWM repeat interrupt define */
    PWM_INT_ALL,      /*!<  */
} PWM_INT_Type;

/**
 *  @brief PWM Channel No. type definition
 */
typedef enum {
    PWM_CH0 = 0, /*!< PWM Channel 0 define */
    PWM_CH1,     /*!< PWM Channel 1 define */
    PWM_CH2,     /*!< PWM Channel 2 define */
    PWM_CH3,     /*!< PWM Channel 3 define */
    PWM_CHx_MAX, /*!<  */
} PWM_CHx_Type;

/**
 *  @brief PWM Mode type definition
 */
typedef enum {
    PWM_MODE_DISABLE = 0, /*!< PWM Mode Disable define */
    PWM_MODE_ENABLE,      /*!< PWM Mode Enable define */
} PWM_Mode_Type;

/**
 *  @brief PWM Idel State type definition
 */
typedef enum {
    PWM_IDLE_STATE_INACTIVE = 0, /*!< PWM Idle State Inactive define */
    PWM_IDLE_STATE_ACTIVE,       /*!< PWM Idle State Active define */
} PWM_Idle_State_Type;

/**
 *  @brief PWM break State type definition
 */
typedef enum {
    PWM_BREAK_STATE_INACTIVE = 0, /*!< PWM Break State Inactive define */
    PWM_BREAK_STATE_ACTIVE,       /*!< PWM Break State Active define */
} PWM_Break_State_Type;

/**
 *  @brief PWM EXT break Polarity Level type definition
 */
typedef enum {
    PWM_BREAK_Polarity_LOW = 0, /*!< PWM EXT Break Polarity Low Level define */
    PWM_BREAK_Polarity_HIGH,    /*!< PWM EXT Break Polarity High Level define */
} PWM_EXT_Break_Polarity_Type;

/**
 *  @brief PWM Trig ADC Source type definition
 */
typedef enum {
    PWM_TRIGADC_SOURCE_0L = 0,     /*!< PWM Channel 0 Threshold L Trig ADC Source define */
    PWM_TRIGADC_SOURCE_0H,         /*!< PWM Channel 0 Threshold H Trig ADC Source define */
    PWM_TRIGADC_SOURCE_1L,         /*!< PWM Channel 1 Threshold L Trig ADC Source define */
    PWM_TRIGADC_SOURCE_1H,         /*!< PWM Channel 1 Threshold H Trig ADC Source define */
    PWM_TRIGADC_SOURCE_2L,         /*!< PWM Channel 2 Threshold L Trig ADC Source define */
    PWM_TRIGADC_SOURCE_2H,         /*!< PWM Channel 2 Threshold H Trig ADC Source define */
    PWM_TRIGADC_SOURCE_3L,         /*!< PWM Channel 3 Threshold L Trig ADC Source define */
    PWM_TRIGADC_SOURCE_3H,         /*!< PWM Channel 3 Threshold H Trig ADC Source define */
    PWM_TRIGADC_SOURCE_PRDE,       /*!< PWM Period End Reached Trig ADC Source define */
    PWM_TRIGADC_SOURCE_NONE = 0xF, /*!< PWM None Trig ADC Source define */
} PWM_TrigADC_Source_Type;

/**
 *  @brief PWM configuration structure type definition
 */
typedef struct {
    PWM_Clk_Type clk;                   /*!< PWM Clock */
    PWM_Stop_Mode_Type stopMode;        /*!< PWM Stop Mode */
    PWM_EXT_Break_Polarity_Type extPol; /*!< PWM EXT_Break Polarity */
    PWM_TrigADC_Source_Type adcSrc;     /*!< PWM TrigADC Source */
    BL_Fun_Type stpRept;                /*!< PWM Stop On Rept */
    uint16_t clkDiv;                    /*!< PWM clkDiv num */
    uint16_t period;                    /*!< PWM period set */
    uint16_t intPulseCnt;               /*!< PWM interrupt pulse count */
} PWMx_CFG_Type;

/**
 *  @brief PWM CC configuration structure type definition
 */
typedef struct {
    PWM_Mode_Type modP;        /*!< PWM Channelx Positive PWM mode type */
    PWM_Mode_Type modN;        /*!< PWM Channelx Negative PWM mode type */
    PWM_Polarity_Type polP;    /*!< PWM Channelx Positive polarity type */
    PWM_Polarity_Type polN;    /*!< PWM Channelx Negative polarity type */
    PWM_Idle_State_Type idlP;  /*!< PWM Channelx Positive idle state type */
    PWM_Idle_State_Type idlN;  /*!< PWM Channelx Negative idle state type */
    PWM_Break_State_Type brkP; /*!< PWM Channelx Positive break state type */
    PWM_Break_State_Type brkN; /*!< PWM Channelx Negative break state type */
    uint16_t thresholdL;       /*!< PWM thresholdL number */
    uint16_t thresholdH;       /*!< PWM thresholdH number */
    uint8_t dtg;               /*!< PWM Channelx deadtime generator */
} PWM_CHx_CFG_Type;

/*@} end of group PWM_Public_Types */

/** @defgroup  PWM_Public_Constants
 *  @{
 */

/** @defgroup  PWMx_ID_TYPE
 *  @{
 */
#define IS_PWMx_ID_TYPE(type) (((type) == PWM0_ID) || \
                               ((type) == PWM1_ID) || \
                               ((type) == PWM_CH_MAX))

/** @defgroup  PWM_CLK_TYPE
 *  @{
 */
#define IS_PWM_CLK_TYPE(type) (((type) == PWM_CLK_XCLK) || \
                               ((type) == PWM_CLK_BCLK) || \
                               ((type) == PWM_CLK_32K))

/** @defgroup  PWM_STOP_MODE_TYPE
 *  @{
 */
#define IS_PWM_STOP_MODE_TYPE(type) (((type) == PWM_STOP_ABRUPT) || \
                                     ((type) == PWM_STOP_GRACEFUL))

/** @defgroup  PWM_POLARITY_TYPE
 *  @{
 */
#define IS_PWM_POLARITY_TYPE(type) (((type) == PWM_POL_ACTIVE_LOW) || \
                                    ((type) == PWM_POL_ACTIVE_HIGH))

/** @defgroup  PWM_INT_TYPE
 *  @{
 */
#define IS_PWM_INT_TYPE(type) (((type) == PWM_INT_CH0L) || \
                               ((type) == PWM_INT_CH0H) || \
                               ((type) == PWM_INT_CH1L) || \
                               ((type) == PWM_INT_CH1H) || \
                               ((type) == PWM_INT_CH2L) || \
                               ((type) == PWM_INT_CH2H) || \
                               ((type) == PWM_INT_CH3L) || \
                               ((type) == PWM_INT_CH3H) || \
                               ((type) == PWM_INT_PRDE) || \
                               ((type) == PWM_INT_BRK) ||  \
                               ((type) == PWM_INT_REPT) || \
                               ((type) == PWM_INT_ALL))

/** @defgroup  PWM_CHx_TYPE
 *  @{
 */
#define IS_PWM_CHx_TYPE(type) (((type) == PWM_CH0) || \
                               ((type) == PWM_CH1) || \
                               ((type) == PWM_CH2) || \
                               ((type) == PWM_CH3) || \
                               ((type) == PWM_CH_MAX))

/** @defgroup  PWM_MODE_TYPE
 *  @{
 */
#define IS_PWM_MODE_TYPE(type) (((type) == PWM_MODE_DISABLE) || \
                                ((type) == PWM_Mode_ENABLE))

/** @defgroup  PWM_IDLE_STATE_TYPE
 *  @{
 */
#define IS_PWM_IDLE_STATE_TYPE(type) (((type) == PWM_IDLE_STATE_INACTIVE) || \
                                      ((type) == PWM_IDLE_STATE_ACTIVE))

/** @defgroup  PWM_BREAK_STATE_TYPE
 *  @{
 */
#define IS_PWM_BREAK_STATE_TYPE(type) (((type) == PWM_BREAK_STATE_INACTIVE) || \
                                       ((type) == PWM_BREAK_STATE_ACTIVE))

/** @defgroup  PWM_EXT_BREAK_POLARITY_TYPE
 *  @{
 */
#define IS_PWM_EXT_BREAK_POLARITY_TYPE(type) (((type) == PWM_BREAK_Polarity_LOW) || \
                                              ((type) == PWM_BREAK_Polarity_HIGH))

/** @defgroup  PWM_TRIGADC_SOURCE_TYPE
 *  @{
 */
#define IS_PWM_TRIGADC_SOURCE_TYPE(type) (((type) == PWM_TRIGADC_SOURCE_0L) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_0H) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_1L) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_1H) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_2L) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_2H) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_3L) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_3H) ||   \
                                          ((type) == PWM_TRIGADC_SOURCE_PRDE) || \
                                          ((type) == PWM_TRIGADC_SOURCE_NONE))

/*@} end of group PWM_Public_Constants */

/** @defgroup  PWM_Public_Macros
 *  @{
 */
#define IS_PWMx_ID(CH) ((CH) < PWMx_ID_MAX)
#define IS_PWM_CHx(CH) ((CH) < PWM_CHx_MAX)

/*@} end of group PWM_Public_Macros */

/** @defgroup  PWM_Public_Functions
 *  @{
 */

/**
 *  @brief PWM Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void PWM_IRQHandler(void);
#endif
BL_Err_Type PWMx_Init(PWMx_ID_Type pwmx, PWMx_CFG_Type *cfg);
void PWMx_Div_Set(PWMx_ID_Type id, uint16_t div);
void PWMx_Period_Set(PWMx_ID_Type id, uint16_t period);
void PWMx_Period_Get(PWMx_ID_Type id, uint16_t *period);
void PWMx_Enable(PWMx_ID_Type id);
void PWMx_Disable(PWMx_ID_Type id);
void PWM_Channelx_Init(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_CHx_CFG_Type *cfg);
void PWM_Channelx_Threshold_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t thresholdL, uint16_t thresholdH);
void PWM_Channelx_ThresholdL_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t thresholdL);
void PWM_Channelx_ThresholdH_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t thresholdH);
void PWM_Channelx_Threshold_Get(PWMx_ID_Type id, PWM_CHx_Type ch, uint16_t *thresholdL, uint16_t *thresholdH);
void PWM_Channelx_Pwm_Mode_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Mode_Type modP, PWM_Mode_Type modN);
void PWM_Channelx_Positive_Pwm_Mode_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Mode_Type mod);
void PWM_Channelx_Negative_Pwm_Mode_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Mode_Type mod);
void PWM_Channelx_Polarity_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Polarity_Type polP, PWM_Polarity_Type polN);
void PWM_Channelx_Positive_Polarity_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Polarity_Type pol);
void PWM_Channelx_Negative_Polarity_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Polarity_Type pol);
void PWM_Channelx_Idle_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Idle_State_Type idlP, PWM_Idle_State_Type idlN);
void PWM_Channelx_Positive_Idle_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Idle_State_Type idl);
void PWM_Channelx_Negative_Idle_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Idle_State_Type idl);
void PWM_Channelx_Break_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Break_State_Type brkP, PWM_Break_State_Type brkN);
void PWM_Channelx_Positive_Break_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Break_State_Type brk);
void PWM_Channelx_Negative_Break_State_Set(PWMx_ID_Type id, PWM_CHx_Type ch, PWM_Break_State_Type brk);
void PWM_Config1_Set(PWMx_ID_Type id, uint32_t cfg);
void PWM_Config1_Get(PWMx_ID_Type id, uint32_t *cfg);
void PWM_Channelx_Dtg_Set(PWMx_ID_Type id, PWM_CHx_Type ch, uint8_t dtg);
void PWM_SW_Break_Enable(PWMx_ID_Type id);
void PWM_SW_Break_Disable(PWMx_ID_Type id);
void PWM_EXT_Break_Enable(PWMx_ID_Type id);
void PWM_EXT_Break_Disable(PWMx_ID_Type id);
void PWM_EXT_Break_Polarity_Set(PWMx_ID_Type id, PWM_EXT_Break_Polarity_Type pol);
void PWM_TrigADC_Source_Set(PWMx_ID_Type id, PWM_TrigADC_Source_Type src);
void PWM_Int_Mask(PWMx_ID_Type id, PWM_INT_Type intType, BL_Mask_Type intMask);
void PWM_Int_Clear(PWMx_ID_Type id, PWM_INT_Type intType);
BL_Sts_Type PWM_Int_Status_Get(PWMx_ID_Type id, PWM_INT_Type intType);
#ifndef BFLB_USE_HAL_DRIVER
void PWM_Int_Callback_Install(PWMx_ID_Type id, uint32_t intType, intCallback_Type *cbFun);
void PWM_IRQHandler(void);
#endif
/*@} end of group PWM_Public_Functions */

/*@} end of group PWM */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_PWM_H__ */
