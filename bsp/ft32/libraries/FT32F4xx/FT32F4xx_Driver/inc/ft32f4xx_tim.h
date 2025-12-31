/**
  ******************************************************************************
  * @file     ft32f4xx_tim.h
  * @author   FMD AE
  * @brief    This file contains all the functions prototypes for the TIM
  *           firmware library.
  * @version  V1.0.0
  * @date     2025-04-02
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_TIM_H
#define __FT32F4XX_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup TIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  TIM Time Base Init structure definition
  * @note   This sturcture is used with all TIMx.
  */

typedef struct
{
    uint32_t TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

    uint32_t TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

    uint32_t TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF
                                       @note The high 16-bit auto-reload value (TIM2 and TIM5 only) */

    uint32_t TIM_ClockDivision;     /*!< Specifies the clock division.
                                       This parameter can be a value of @ref TIM_Clock_Division_CKD */

    uint32_t TIM_RepetitionCounter; /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF.
                                       @note This parameter is valid only for TIM1 and TIM8. */
} TIM_TimeBaseInitTypeDef;

/**
  * @brief  TIM Output Compare Init structure definition
  */

typedef struct
{
    uint32_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

    uint32_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

    uint32_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1 and TIM8. */

    uint32_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                   This parameter can be a number between 0x0000 and 0xFFFF ( or 0xFFFFFFFF
                                   for TIM2 and TIM5) */

    uint32_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

    uint32_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

    uint32_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

    uint32_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
} TIM_OCInitTypeDef;

/**
  * @brief  TIM Input Capture Init structure definition
  */

typedef struct
{

    uint32_t TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

    uint32_t TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    uint32_t TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

    uint32_t TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

    uint32_t TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TIM_ICInitTypeDef;

/**
  * @brief  TIM_BDTR structure definition
  * @note   This sturcture is used only with TIM1 and TIM8.
  */

typedef struct
{

    uint32_t TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TIM_OSSR_Off_State_Selection_for_Run_mode_state */

    uint32_t TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TIM_OSSI_Off_State_Selection_for_Idle_mode_state */

    uint32_t TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TIM_Lock_level */

    uint32_t TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

    uint32_t TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not.
                                      This parameter can be a value of @ref TIM_Break_Input_enable_disable */

    uint32_t TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref TIM_Break_Polarity */

    uint32_t TIM_BreakFilter;      /*!< Specifies the break input filter.
                                      This parameter can be a number between Min_Data = 0x0 and Max_Data = 0xF */

    uint32_t TIM_BreakBIDMode;     /*!< Specifies the bidirectional function mode of the break input.
                                      This parameter can be a value of @ref TIM_Break_Input_Bidirectional_Mode */

    uint32_t TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not.
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */

    uint32_t TIM_CtrlPWMOutput;    /*!< Specifies whether the TIM Control PWM Output feature is enabled or not.
                                      This parameter can be a value of @ref TIM_MOE_Bit_Set_Reset */
} TIM_BDTRInitTypeDef;

/**
  * @brief  TIM Break input configuration
  */
typedef struct
{
    uint32_t TIM_Source;         /*!< Specifies the source of the timer break input.
                                    This parameter can be a value of @ref TIM_Break_Input_Source */
    uint32_t TIM_Enable;         /*!< Specifies whether or not the break input source is enabled.
                                    This parameter can be a value of @ref TIM_Break_Input_Source_Enable */
    uint32_t TIM_Polarity;       /*!< Specifies the break input source polarity.
                                    This parameter can be a value of @ref TIM_Break_Input_Source_Polarity */
} TIM_BreakInputConfigTypeDef;

/**
  *
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup TIM_Exported_constants
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1 ) || \
                                   ((PERIPH) == TIM2 ) || \
                                   ((PERIPH) == TIM3 ) || \
                                   ((PERIPH) == TIM4 ) || \
                                   ((PERIPH) == TIM5 ) || \
                                   ((PERIPH) == TIM6 ) || \
                                   ((PERIPH) == TIM7 ) || \
                                   ((PERIPH) == TIM8 ) || \
                                   ((PERIPH) == TIM9 ) || \
                                   ((PERIPH) == TIM10) || \
                                   ((PERIPH) == TIM11) || \
                                   ((PERIPH) == TIM12) || \
                                   ((PERIPH) == TIM13) || \
                                   ((PERIPH) == TIM14))

/* LIST1: TIM 1 */
#define IS_TIM_LIST1_PERIPH(PERIPH)  ((PERIPH) == TIM1)

/* LIST2: TIM 1 and 8 */
#define IS_TIM_LIST2_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM8))

/* LIST3: TIM 1, 2, 3, 4, 5 and 8 */
#define IS_TIM_LIST3_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM8))

/* LIST4: TIM 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13 and 14 */
#define IS_TIM_LIST4_PERIPH(PERIPH) (((PERIPH) == TIM1 ) || \
                                     ((PERIPH) == TIM2 ) || \
                                     ((PERIPH) == TIM3 ) || \
                                     ((PERIPH) == TIM4 ) || \
                                     ((PERIPH) == TIM5 ) || \
                                     ((PERIPH) == TIM8 ) || \
                                     ((PERIPH) == TIM9 ) || \
                                     ((PERIPH) == TIM10) || \
                                     ((PERIPH) == TIM11) || \
                                     ((PERIPH) == TIM12) || \
                                     ((PERIPH) == TIM13) || \
                                     ((PERIPH) == TIM14))

/* LIST5: TIM 1, 2, 3, 4, 5, 8, 9 and 12 */
#define IS_TIM_LIST5_PERIPH(PERIPH) (((PERIPH) == TIM1 ) || \
                                     ((PERIPH) == TIM2 ) || \
                                     ((PERIPH) == TIM3 ) || \
                                     ((PERIPH) == TIM4 ) || \
                                     ((PERIPH) == TIM5 ) || \
                                     ((PERIPH) == TIM8 ) || \
                                     ((PERIPH) == TIM9 ) || \
                                     ((PERIPH) == TIM12))

/* LIST6: TIM 1, 2, 3, 4, 5, 6, 7 and 8 */
#define IS_TIM_LIST6_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                     ((PERIPH) == TIM2) || \
                                     ((PERIPH) == TIM3) || \
                                     ((PERIPH) == TIM4) || \
                                     ((PERIPH) == TIM5) || \
                                     ((PERIPH) == TIM6) || \
                                     ((PERIPH) == TIM7) || \
                                     ((PERIPH) == TIM8))

/* LIST7: TIM 2 and 11 */
#define IS_TIM_LIST7_PERIPH(PERIPH)  (((PERIPH) == TIM2 ) || \
                                      ((PERIPH) == TIM11))

/**
  * @}
  */

/** @defgroup TIM_Output_Compare_and_PWM_modes
  * @{
  */

#define TIM_OCMode_Timing                  0x00000000U                                              /*!< Frozen                                 */
#define TIM_OCMode_Active                  TIM_CCMR1_OC1M_0                                         /*!< Set channel to active level on match   */
#define TIM_OCMode_Inactive                TIM_CCMR1_OC1M_1                                         /*!< Set channel to inactive level on match */
#define TIM_OCMode_Toggle                  (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)                    /*!< Toggle                                 */
#define TIM_OCMODE_Forced_Inactive         TIM_CCMR1_OC1M_2                                         /*!< Force inactive level                   */
#define TIM_OCMODE_Forced_Active           (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)                    /*!< Force active level                     */
#define TIM_OCMode_PWM1                    (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)                    /*!< PWM mode 1                             */
#define TIM_OCMode_PWM2                    (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0) /*!< PWM mode 2                             */
#define TIM_OCMode_Combined_PWM1           (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2)                    /*!< Combined PWM mode 1                    */
#define TIM_OCMode_Combined_PWM2           (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0) /*!< Combined PWM mode 2                    */
#define TIM_OCMode_Asymmetric_PWM1         (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1) /*!< Asymmetric PWM mode 1                  */
#define TIM_OCMode_Asymmetric_PWM2         TIM_CCMR1_OC1M                                           /*!< Asymmetric PWM mode 2                  */
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing         ) || \
                              ((MODE) == TIM_OCMode_Active         ) || \
                              ((MODE) == TIM_OCMode_Inactive       ) || \
                              ((MODE) == TIM_OCMode_Toggle         ) || \
                              ((MODE) == TIM_OCMODE_Forced_Inactive) || \
                              ((MODE) == TIM_OCMODE_Forced_Active  ) || \
                              ((MODE) == TIM_OCMode_PWM1           ) || \
                              ((MODE) == TIM_OCMode_PWM2           ) || \
                              ((MODE) == TIM_OCMode_Combined_PWM1  ) || \
                              ((MODE) == TIM_OCMode_Combined_PWM2  ) || \
                              ((MODE) == TIM_OCMode_Asymmetric_PWM1) || \
                              ((MODE) == TIM_OCMode_Asymmetric_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing        ) || \
                          ((MODE) == TIM_OCMode_Active        ) || \
                          ((MODE) == TIM_OCMode_Inactive      ) || \
                          ((MODE) == TIM_OCMode_Toggle        ) || \
                          ((MODE) == TIM_OCMode_PWM1          ) || \
                          ((MODE) == TIM_OCMode_PWM2          ) || \
                          ((MODE) == TIM_ForcedAction_Active  ) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode
  * @{
  */

#define TIM_OPMode_Single                  TIM_CR1_OPM                          /*!< Counter stops counting at the next update event */
#define TIM_OPMode_Repetitive              0x00000000U                          /*!< Counter is not stopped at update event          */
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single     ) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
  * @}
  */

/** @defgroup TIM_Channel
  * @{
  */

#define TIM_Channel_1                      ((uint32_t)0x00000000)
#define TIM_Channel_2                      ((uint32_t)0x00000004)
#define TIM_Channel_3                      ((uint32_t)0x00000008)
#define TIM_Channel_4                      ((uint32_t)0x0000000C)
#define TIM_Channel_5                      ((uint32_t)0x00000010)
#define TIM_Channel_6                      ((uint32_t)0x00000014)

#define IS_TIM_CHANNEL(CHANNEL)               (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3) || \
                                               ((CHANNEL) == TIM_Channel_4) || \
                                               ((CHANNEL) == TIM_Channel_5) || \
                                               ((CHANNEL) == TIM_Channel_6))

#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))

#define IS_TIM_2_TO_5_CHANNEL(CHANNEL)         (((CHANNEL) == TIM_Channel_1) || \
                                                ((CHANNEL) == TIM_Channel_2) || \
                                                ((CHANNEL) == TIM_Channel_3) || \
                                                ((CHANNEL) == TIM_Channel_4))

#define IS_TIM_9_AND_12_CHANNEL(CHANNEL)       (((CHANNEL) == TIM_Channel_1) || \
                                                ((CHANNEL) == TIM_Channel_2))

#define IS_TIM_10_11_13_14_CHANNEL(CHANNEL)    (((CHANNEL) == TIM_Channel_1))

/**
  * @}
  */

/** @defgroup TIM_Clock_Division_CKD
  * @{
  */

#define TIM_CKD_DIV1                       0x00000000U                          /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CKD_DIV2                       TIM_CR1_CKD_0                        /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CKD_DIV4                       TIM_CR1_CKD_1                        /*!< Clock division: tDTS=4*tCK_INT */
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode
  * @{
  */

#define TIM_CounterMode_Up                 0x00000000U                          /*!< Counter used as up-counter   */
#define TIM_CounterMode_Down               TIM_CR1_DIR                          /*!< Counter used as down-counter */
#define TIM_CounterMode_CenterAligned1     TIM_CR1_CMS_0                        /*!< Center-aligned mode 1        */
#define TIM_CounterMode_CenterAligned2     TIM_CR1_CMS_1                        /*!< Center-aligned mode 2        */
#define TIM_CounterMode_CenterAligned3     TIM_CR1_CMS                          /*!< Center-aligned mode 3        */
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up            ) || \
                                   ((MODE) == TIM_CounterMode_Down          ) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3) )
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Polarity
  * @{
  */

#define TIM_OCPolarity_High                0x00000000U                          /*!< Capture/Compare 1 output Polarity */
#define TIM_OCPolarity_Low                 TIM_CCER_CC1P                        /*!< Capture/Compare 1 output Polarity */
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity
  * @{
  */

#define TIM_OCNPolarity_High               0x00000000U                          /*!< Capture/Compare complementary output polarity */
#define TIM_OCNPolarity_Low                TIM_CCER_CC1NP                       /*!< Capture/Compare complementary output polarity */
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_state
  * @{
  */

#define TIM_OutputState_Disable            0x00000000U                          /*!< Capture/Compare 1 output disable */
#define TIM_OutputState_Enable             TIM_CCER_CC1E                        /*!< Capture/Compare 1 output enable  */
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_state
  * @{
  */

#define TIM_OutputNState_Disable           0x00000000U                          /*!< Capture/Compare 1 Complementary output disable */
#define TIM_OutputNState_Enable            TIM_CCER_CC1NE                       /*!< Capture/Compare 1 Complementary output enable  */
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
  * @}
  */

/** @defgroup TIM_Capture_Compare_state
  * @{
  */

#define TIM_CCx_Disable                    0x00000000U                          /*!< Capture/Compare 1 output disable */
#define TIM_CCx_Enable                     TIM_CCER_CC1E                        /*!< Capture/Compare 1 output enable  */
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable  ) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */

/** @defgroup TIM_Capture_Compare_N_state
  * @{
  */

#define TIM_CCxN_Disable                   0x00000000U                          /*!< Capture/Compare 1 Complementary output disable */
#define TIM_CCxN_Enable                    TIM_CCER_CC1NE                       /*!< Capture/Compare 1 Complementary output enable  */
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable ) || \
                           ((CCXN) == TIM_CCxN_Disable))
/**
  * @}
  */

/** @defgroup TIM_Break_Input_enable_disable
  * @{
  */

#define TIM_Break_Enable                   TIM_BDTR_BKE                         /*!< Break input BRK is enabled  */
#define TIM_Break_Disable                  0x00000000U                          /*!< Break input BRK is disabled */
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable ) || \
                                   ((STATE) == TIM_Break_Disable))
/**
  * @}
  */

/** @defgroup TIM_Break_Polarity
  * @{
  */

#define TIM_BreakPolarity_Low              0x00000000U                          /*!< Break input BRK is active low  */
#define TIM_BreakPolarity_High             TIM_BDTR_BKP                         /*!< Break input BRK is active high */
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low ) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))
/**
  * @}
  */

/** @defgroup TIM_Break_Input_Bidirectional_Mode TIM Break Input Bidirectional Function Mode
  * @{
  */

#define TIM_Break_Bid_MODE_INPUT           0x00000000U                          /*!< Break input BRK in input mode */
#define TIM_Break_Bid_MODE_BIDIRECTIONAL   TIM_BDTR_BKBID                       /*!< Break input BRK in bidirectional mode */
#define IS_TIM_BREAK_BID_MODE(MODE) ((MODE == TIM_Break_Bid_MODE_INPUT        ) || \
                                     (MODE == TIM_Break_Bid_MODE_BIDIRECTIONAL))

/**
  * @}
  */

/** @defgroup TIM_AOE_Bit_Set_Reset
  * @{
  */

#define TIM_AutomaticOutput_Enable         TIM_BDTR_AOE                         /*!< MOE can be set by software or automatically at the next update event
                                                                                     (if none of the break inputs BRK is active) */
#define TIM_AutomaticOutput_Disable        0x00000000U                          /*!< MOE can be set only by software */
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable ) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
  * @}
  */

/** @defgroup TIM_MOE_Bit_Set_Reset
  * @{
  */

#define TIM_ControlPWMOutput_Enable        TIM_BDTR_MOE                         /*!< Enable TIM main output  */
#define TIM_ControlPWMOutput_Disable       0x00000000U                          /*!< Disable TIM main output */
#define IS_TIM_CONTROL_PWM_OUTPUT_STATE(STATE) (((STATE) == TIM_ControlPWMOutput_Enable ) || \
                                                ((STATE) == TIM_ControlPWMOutput_Disable))
/**
  * @}
  */

/** @defgroup TIM_Lock_level
  * @{
  */

#define TIM_LOCKLevel_OFF                  0x00000000U                          /*!< LOCK OFF     */
#define TIM_LOCKLevel_1                    TIM_BDTR_LOCK_0                      /*!< LOCK Level 1 */
#define TIM_LOCKLevel_2                    TIM_BDTR_LOCK_1                      /*!< LOCK Level 2 */
#define TIM_LOCKLevel_3                    TIM_BDTR_LOCK                        /*!< LOCK Level 3 */
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1  ) || \
                                  ((LEVEL) == TIM_LOCKLevel_2  ) || \
                                  ((LEVEL) == TIM_LOCKLevel_3  ))
/**
  * @}
  */

/** @defgroup TIM_OSSI_Off_State_Selection_for_Idle_mode_state
  * @{
  */

#define TIM_OSSIState_Enable               TIM_BDTR_OSSI                        /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSIState_Disable              0x00000000U                          /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable ) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup TIM_OSSR_Off_State_Selection_for_Run_mode_state
  * @{
  */

#define TIM_OSSRState_Enable               TIM_BDTR_OSSR                        /*!< When inactive, OC/OCN outputs are enabled (still controlled by the timer)           */
#define TIM_OSSRState_Disable              0x00000000U                          /*!< When inactive, OC/OCN outputs are disabled (not controlled any longer by the timer) */
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable ) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Idle_State
  * @{
  */

#define TIM_OCIdleState_Set                TIM_CR2_OIS1                         /*!< Output Idle state: OCx=1 when MOE=0 */
#define TIM_OCIdleState_Reset              0x00000000U                          /*!< Output Idle state: OCx=0 when MOE=0 */
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set  ) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Idle_State
  * @{
  */

#define TIM_OCNIdleState_Set               TIM_CR2_OIS1N                        /*!< Complementary output Idle state: OCxN=1 when MOE=0 */
#define TIM_OCNIdleState_Reset             0x00000000U                          /*!< Complementary output Idle state: OCxN=0 when MOE=0 */
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set  ) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Polarity
  * @{
  */

#define  TIM_ICPolarity_Rising             0x00000000U                          /*!< Polarity for TIx source */
#define  TIM_ICPolarity_Falling            TIM_CCER_CC1P                        /*!< Polarity for TIx source */
#define  TIM_ICPolarity_BothEdge           (TIM_CCER_CC1P | TIM_CCER_CC1NP)     /*!< Polarity for TIx source */
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising  ) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling ) || \
                                      ((POLARITY) == TIM_ICPolarity_BothEdge))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Selection
  * @{
  */

#define TIM_ICSelection_DirectTI           TIM_CCMR1_CC1S_0                     /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                                     connected to IC1, IC2, IC3 or IC4, respectively.           */
#define TIM_ICSelection_IndirectTI         TIM_CCMR1_CC1S_1                     /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                                     connected to IC2, IC1, IC4 or IC3, respectively.           */
#define TIM_ICSelection_TRC                TIM_CCMR1_CC1S                       /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI  ) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC       ))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Prescaler
  * @{
  */

#define TIM_ICPSC_DIV1                     0x00000000U                          /*!< Capture performed each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                     TIM_CCMR1_IC1PSC_0                   /*!< Capture performed once every 2 events                                */
#define TIM_ICPSC_DIV4                     TIM_CCMR1_IC1PSC_1                   /*!< Capture performed once every 4 events                                */
#define TIM_ICPSC_DIV8                     TIM_CCMR1_IC1PSC                     /*!< Capture performed once every 8 events                                */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))
/**
  * @}
  */

/** @defgroup TIM_Group_Channel5 Group Channel 5 and Channel 1, 2 or 3
  * @{
  */
#define TIM_GroupCH5_None                  0x00000000U                          /* !< No effect of OC5REF on OC1REFC, OC2REFC and OC3REFC */
#define TIM_GroupCH5_OC1Refc               TIM_CCR5_GC5C1                       /* !< OC1REFC is the logical AND of OC1REFC and OC5REF    */
#define TIM_GroupCH5_OC2Refc               TIM_CCR5_GC5C2                       /* !< OC2REFC is the logical AND of OC2REFC and OC5REF    */
#define TIM_GroupCH5_OC3Refc               TIM_CCR5_GC5C3                       /* !< OC3REFC is the logical AND of OC3REFC and OC5REF    */
#define IS_TIM_GROUPCH5(OCREF) (((OCREF) == TIM_GroupCH5_None) || \
                                ((OCREF) == TIM_CCR5_GC5C1   ) || \
                                ((OCREF) == TIM_CCR5_GC5C2   ) || \
                                ((OCREF) == TIM_CCR5_GC5C3   ))
/**
  * @}
  */

/** @defgroup TIM_interrupt_sources
  * @{
  */

#define TIM_IT_Update                      TIM_DIER_UIE                         /*!< Update interrupt            */
#define TIM_IT_CC1                         TIM_DIER_CC1IE                       /*!< Capture/Compare 1 interrupt */
#define TIM_IT_CC2                         TIM_DIER_CC2IE                       /*!< Capture/Compare 2 interrupt */
#define TIM_IT_CC3                         TIM_DIER_CC3IE                       /*!< Capture/Compare 3 interrupt */
#define TIM_IT_CC4                         TIM_DIER_CC4IE                       /*!< Capture/Compare 4 interrupt */
#define TIM_IT_COM                         TIM_DIER_COMIE                       /*!< Commutation interrupt       */
#define TIM_IT_Trigger                     TIM_DIER_TIE                         /*!< Trigger interrupt           */
#define TIM_IT_Break                       TIM_DIER_BIE                         /*!< Break interrupt             */
#define IS_TIM_IT(IT) ((((IT) & (uint32_t)0xFFFFFF00) == 0x00000000) && ((IT) != 0x00000000))
#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update ) || \
                           ((IT) == TIM_IT_CC1    ) || \
                           ((IT) == TIM_IT_CC2    ) || \
                           ((IT) == TIM_IT_CC3    ) || \
                           ((IT) == TIM_IT_CC4    ) || \
                           ((IT) == TIM_IT_COM    ) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break  ))

/**
  * @}
  */

/** @defgroup TIM_DMA_Base_address
  * @{
  */

#define TIM_DMABase_CR1                    ((uint32_t)0x00000000)
#define TIM_DMABase_CR2                    ((uint32_t)0x00000001)
#define TIM_DMABase_SMCR                   ((uint32_t)0x00000002)
#define TIM_DMABase_DIER                   ((uint32_t)0x00000003)
#define TIM_DMABase_SR                     ((uint32_t)0x00000004)
#define TIM_DMABase_EGR                    ((uint32_t)0x00000005)
#define TIM_DMABase_CCMR1                  ((uint32_t)0x00000006)
#define TIM_DMABase_CCMR2                  ((uint32_t)0x00000007)
#define TIM_DMABase_CCER                   ((uint32_t)0x00000008)
#define TIM_DMABase_CNT                    ((uint32_t)0x00000009)
#define TIM_DMABase_PSC                    ((uint32_t)0x0000000A)
#define TIM_DMABase_ARR                    ((uint32_t)0x0000000B)
#define TIM_DMABase_RCR                    ((uint32_t)0x0000000C)
#define TIM_DMABase_CCR1                   ((uint32_t)0x0000000D)
#define TIM_DMABase_CCR2                   ((uint32_t)0x0000000E)
#define TIM_DMABase_CCR3                   ((uint32_t)0x0000000F)
#define TIM_DMABase_CCR4                   ((uint32_t)0x00000010)
#define TIM_DMABase_BDTR                   ((uint32_t)0x00000011)
#define TIM_DMABase_DCR                    ((uint32_t)0x00000012)
#define TIM_DMABase_OR                     ((uint32_t)0x00000014)
#define TIM_DMABase_CCMR3                  ((uint32_t)0x00000015)
#define TIM_DMABase_CCR5                   ((uint32_t)0x00000016)
#define TIM_DMABase_CCR6                   ((uint32_t)0x00000017)
#define TIM_DMABase_AF1                    ((uint32_t)0x00000018)
#define TIM_DMABase_AF2                    ((uint32_t)0x00000019)
#define TIM_DMABase_TISEL                  ((uint32_t)0x0000001A)
#define IS_TIM_DMA_BASE(BASE) (((BASE) == TIM_DMABase_CR1  ) || \
                               ((BASE) == TIM_DMABase_CR2  ) || \
                               ((BASE) == TIM_DMABase_SMCR ) || \
                               ((BASE) == TIM_DMABase_DIER ) || \
                               ((BASE) == TIM_DMABase_SR   ) || \
                               ((BASE) == TIM_DMABase_EGR  ) || \
                               ((BASE) == TIM_DMABase_CCMR1) || \
                               ((BASE) == TIM_DMABase_CCMR2) || \
                               ((BASE) == TIM_DMABase_CCER ) || \
                               ((BASE) == TIM_DMABase_CNT  ) || \
                               ((BASE) == TIM_DMABase_PSC  ) || \
                               ((BASE) == TIM_DMABase_ARR  ) || \
                               ((BASE) == TIM_DMABase_RCR  ) || \
                               ((BASE) == TIM_DMABase_CCR1 ) || \
                               ((BASE) == TIM_DMABase_CCR2 ) || \
                               ((BASE) == TIM_DMABase_CCR3 ) || \
                               ((BASE) == TIM_DMABase_CCR4 ) || \
                               ((BASE) == TIM_DMABase_BDTR ) || \
                               ((BASE) == TIM_DMABase_DCR  ) || \
                               ((BASE) == TIM_DMABase_OR   ) || \
                               ((BASE) == TIM_DMABase_CCMR3) || \
                               ((BASE) == TIM_DMABase_CCR5 ) || \
                               ((BASE) == TIM_DMABase_CCR6 ) || \
                               ((BASE) == TIM_DMABase_AF1  ) || \
                               ((BASE) == TIM_DMABase_AF2  ) || \
                               ((BASE) == TIM_DMABase_TISEL))
/**
  * @}
  */


/** @defgroup TIM_DMA_Burst_Length TIM DMA Burst Length
  * @{
  */

#define TIM_DMABurstLength_1Transfer           0x00000000U                      /*!< The transfer is done to 1 register starting trom TIMx_CR1 + TIMx_DCR.DBA   */
#define TIM_DMABurstLength_2Transfers          0x00000100U                      /*!< The transfer is done to 2 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_3Transfers          0x00000200U                      /*!< The transfer is done to 3 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_4Transfers          0x00000300U                      /*!< The transfer is done to 4 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_5Transfers          0x00000400U                      /*!< The transfer is done to 5 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_6Transfers          0x00000500U                      /*!< The transfer is done to 6 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_7Transfers          0x00000600U                      /*!< The transfer is done to 7 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_8Transfers          0x00000700U                      /*!< The transfer is done to 8 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_9Transfers          0x00000800U                      /*!< The transfer is done to 9 registers starting trom TIMx_CR1 + TIMx_DCR.DBA  */
#define TIM_DMABurstLength_10Transfers         0x00000900U                      /*!< The transfer is done to 10 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_11Transfers         0x00000A00U                      /*!< The transfer is done to 11 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_12Transfers         0x00000B00U                      /*!< The transfer is done to 12 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_13Transfers         0x00000C00U                      /*!< The transfer is done to 13 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_14Transfers         0x00000D00U                      /*!< The transfer is done to 14 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_15Transfers         0x00000E00U                      /*!< The transfer is done to 15 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_16Transfers         0x00000F00U                      /*!< The transfer is done to 16 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_17Transfers         0x00001000U                      /*!< The transfer is done to 17 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define TIM_DMABurstLength_18Transfers         0x00001100U                      /*!< The transfer is done to 18 registers starting trom TIMx_CR1 + TIMx_DCR.DBA */
#define IS_TIM_DMA_LENGTH(LENGTH) (((LENGTH) == TIM_DMABurstLength_1Transfer  ) || \
                                   ((LENGTH) == TIM_DMABurstLength_2Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_3Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_4Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_5Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_6Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_7Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_8Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_9Transfers ) || \
                                   ((LENGTH) == TIM_DMABurstLength_10Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_11Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_12Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_13Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_14Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_15Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_16Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_17Transfers) || \
                                   ((LENGTH) == TIM_DMABurstLength_18Transfers))
/**
  * @}
  */

/** @defgroup TIM_DMA_sources
  * @{
  */

#define TIM_DMA_Update                     TIM_DIER_UDE                         /*!< DMA request is triggered by the update event                        */
#define TIM_DMA_CC1                        TIM_DIER_CC1DE                       /*!< DMA request is triggered by the capture/compare macth 1 event       */
#define TIM_DMA_CC2                        TIM_DIER_CC2DE                       /*!< DMA request is triggered by the capture/compare macth 2 event event */
#define TIM_DMA_CC3                        TIM_DIER_CC3DE                       /*!< DMA request is triggered by the capture/compare macth 3 event event */
#define TIM_DMA_CC4                        TIM_DIER_CC4DE                       /*!< DMA request is triggered by the capture/compare macth 4 event event */
#define TIM_DMA_COM                        TIM_DIER_COMDE                       /*!< DMA request is triggered by the commutation event                   */
#define TIM_DMA_Trigger                    TIM_DIER_TDE                         /*!< DMA request is triggered by the trigger event                       */
#define IS_TIM_DMA_SOURCE(SOURCE) ((((SOURCE) & (uint32_t)0xFFFF80FF) == 0x00000000) && ((SOURCE) != 0x00000000))

/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Prescaler
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  0x00000000U                          /*!< No prescaler is used             */
#define TIM_ExtTRGPSC_DIV2                 TIM_SMCR_ETPS_0                      /*!< ETR input source is divided by 2 */
#define TIM_ExtTRGPSC_DIV4                 TIM_SMCR_ETPS_1                      /*!< ETR input source is divided by 4 */
#define TIM_ExtTRGPSC_DIV8                 TIM_SMCR_ETPS                        /*!< ETR input source is divided by 8 */
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF ) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
  * @}
  */

/** @defgroup TIM_Internal_Trigger_Selection
  * @{
  */

#define TIM_TS_ITR0                        0x00000000U                          /*!< Internal Trigger 0 (ITR0)              */
#define TIM_TS_ITR1                        TIM_SMCR_TS_0                        /*!< Internal Trigger 1 (ITR1)              */
#define TIM_TS_ITR2                        TIM_SMCR_TS_1                        /*!< Internal Trigger 2 (ITR2)              */
#define TIM_TS_ITR3                        (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)      /*!< Internal Trigger 3 (ITR3)              */
#define TIM_TS_TI1F_ED                     TIM_SMCR_TS_2                        /*!< TI1 Edge Detector (TI1F_ED)            */
#define TIM_TS_TI1FP1                      (TIM_SMCR_TS_0 | TIM_SMCR_TS_2)      /*!< Filtered Timer Input 1 (TI1FP1)        */
#define TIM_TS_TI2FP2                      (TIM_SMCR_TS_1 | TIM_SMCR_TS_2)      /*!< Filtered Timer Input 2 (TI2FP2)        */
#define TIM_TS_ETRF                        TIM_SMCR_TS                          /*!< Filtered External Trigger input (ETRF) */
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0   ) || \
                                             ((SELECTION) == TIM_TS_ITR1   ) || \
                                             ((SELECTION) == TIM_TS_ITR2   ) || \
                                             ((SELECTION) == TIM_TS_ITR3   ) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1 ) || \
                                             ((SELECTION) == TIM_TS_TI2FP2 ) || \
                                             ((SELECTION) == TIM_TS_ETRF   ))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))
/**
  * @}
  */

/** @defgroup TIM_TIx_External_Clock_Source
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      (TIM_SMCR_TS_0 | TIM_SMCR_TS_2)      /*!< Filtered Timer Input 1 (TI1FP1)        */
#define TIM_TIxExternalCLK1Source_TI2      (TIM_SMCR_TS_1 | TIM_SMCR_TS_2)      /*!< Filtered Timer Input 2 (TI2FP2)        */
#define TIM_TIxExternalCLK1Source_TI1ED    TIM_SMCR_TS_2                        /*!< TI1 Edge Detector (TI1F_ED)            */

/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Polarity
  * @{
  */
#define TIM_ExtTRGPolarity_Inverted        TIM_SMCR_ETP                         /*!< Polarity for ETR source */
#define TIM_ExtTRGPolarity_NonInverted     0x00000000U                          /*!< Polarity for ETR source */
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted   ) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode
  * @{
  */

#define TIM_PSCReloadMode_Update           0x00000000U                          /*!< Prescaler reload PSC register value at update event */
#define TIM_PSCReloadMode_Immediate        TIM_EGR_UG                           /*!< Prescaler reload PSC register value at immediate    */
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update   ) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
/**
  * @}
  */

/** @defgroup TIM_Forced_Action
  * @{
  */

#define TIM_ForcedAction_Active            (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)   /*!< Force active level                     */
#define TIM_ForcedAction_InActive          TIM_CCMR1_OC1M_2                        /*!< Force inactive level                   */
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active  ) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_Encoder_Mode
  * @{
  */

#define TIM_EncoderMode_TI1                TIM_SMCR_SMS_0                       /*!< Quadrature encoder mode 1, counts up/down on TI2FP2 edge depending on TI1FP1 level                                  */
#define TIM_EncoderMode_TI2                TIM_SMCR_SMS_1                       /*!< Quadrature encoder mode 2, counts up/down on TI1FP1 edge depending on TI2FP2 level                                  */
#define TIM_EncoderMode_TI12               (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)    /*!< Quadrature encoder mode 3, counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input */
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1 ) || \
                                   ((MODE) == TIM_EncoderMode_TI2 ) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
  * @}
  */


/** @defgroup TIM_Event_Source
  * @{
  */

#define TIM_EventSource_Update             TIM_EGR_UG     /*!< Reinitialize the counter and generates an update of the registers */
#define TIM_EventSource_CC1                TIM_EGR_CC1G   /*!< A capture/compare event is generated on channel 1                 */
#define TIM_EventSource_CC2                TIM_EGR_CC2G   /*!< A capture/compare event is generated on channel 2                 */
#define TIM_EventSource_CC3                TIM_EGR_CC3G   /*!< A capture/compare event is generated on channel 3                 */
#define TIM_EventSource_CC4                TIM_EGR_CC4G   /*!< A capture/compare event is generated on channel 4                 */
#define TIM_EventSource_COM                TIM_EGR_COMG   /*!< A commutation event is generated                                  */
#define TIM_EventSource_Trigger            TIM_EGR_TG     /*!< A trigger event is generated                                      */
#define TIM_EventSource_Break              TIM_EGR_BG     /*!< A break event is generated                                        */
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint32_t)0xFFFFFF00) == 0x00000000) && ((SOURCE) != 0x00000000))

/**
  * @}
  */

/** @defgroup TIM_Update_Source
  * @{
  */

#define TIM_UpdateSource_Global            0x00000000U                          /*!< Source of update is the counter overflow/underflow
                                                                                     or the setting of UG bit, or an update generation
                                                                                     through the slave mode controller. */
#define TIM_UpdateSource_Regular           0x00000001U                          /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global ) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Preload_State
  * @{
  */

#define TIM_OCPreload_Enable               TIM_CCMR1_OC1PE                      /*!< Preload register on TIMx_CCR1 enabled  */
#define TIM_OCPreload_Disable              0x00000000U                          /*!< Preload register on TIMx_CCR1 disabled */
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable ) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Fast_State
  * @{
  */

#define TIM_OCFast_Enable                  TIM_CCMR1_OC1FE                      /*!< Output Compare fast enable  */
#define TIM_OCFast_Disable                 0x00000000U                          /*!< Output Compare fast disable */
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable ) || \
                                    ((STATE) == TIM_OCFast_Disable))

/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Clear_State
  * @{
  */

#define TIM_OCClear_Enable                 TIM_CCMR1_OC1CE                      /*!< OC1REF is cleared as soon as a high level is dected on OCREF_CLR_INPUT signal */
#define TIM_OCClear_Disable                0x00000000U                          /*!< OC1REF is not effected by the OCREF_CLR_INPUT signal                          */
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable ) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
  * @}
  */

/** @defgroup TIM_Trigger_Output_Source (TRGO)
  * @{
  */

#define TIM_TRGOSource_Reset               0x00000000U                                      /*!< TIMx_EGR.UG bit is used as trigger output (TRGO)              */
#define TIM_TRGOSource_Enable              TIM_CR2_MMS_0                                    /*!< TIMx_CR1.CEN bit is used as trigger output (TRGO)             */
#define TIM_TRGOSource_Update              TIM_CR2_MMS_1                                    /*!< Update event is used as trigger output (TRGO)                 */
#define TIM_TRGOSource_OC1                 (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)                  /*!< Capture or a compare match 1 is used as trigger output (TRGO) */
#define TIM_TRGOSource_OC1Ref              TIM_CR2_MMS_2                                    /*!< OC1REF signal is used as trigger output (TRGO)                */
#define TIM_TRGOSource_OC2Ref              (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)                  /*!< OC2REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGOSource_OC3Ref              (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)                  /*!< OC3REF signal is used as trigger output(TRGO)                 */
#define TIM_TRGOSource_OC4Ref              (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0)  /*!< OC4REF signal is used as trigger output(TRGO)                 */
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset ) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1   ) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
/**
  * @}
  */

/** @defgroup TIM_Master_Mode_Selection_2 TIM Master Mode Selection 2 (TRGO2)
  * @{
  */

#define TIM_TRGO2Source_Reset                          0x00000000U                                                         /*!< TIMx_EGR.UG bit is used as trigger output (TRGO2)              */
#define TIM_TRGO2Source_Enable                         TIM_CR2_MMS2_0                                                      /*!< TIMx_CR1.CEN bit is used as trigger output (TRGO2)             */
#define TIM_TRGO2Source_Update                         TIM_CR2_MMS2_1                                                      /*!< Update event is used as trigger output (TRGO2)                 */
#define TIM_TRGO2Source_OC1                            (TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)                                   /*!< Capture or a compare match 1 is used as trigger output (TRGO2) */
#define TIM_TRGO2Source_OC1Ref                         TIM_CR2_MMS2_2                                                      /*!< OC1REF signal is used as trigger output (TRGO2)                */
#define TIM_TRGO2Source_OC2Ref                         (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_0)                                   /*!< OC2REF signal is used as trigger output (TRGO2)                */
#define TIM_TRGO2Source_OC3Ref                         (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1)                                   /*!< OC3REF signal is used as trigger output (TRGO2)                */
#define TIM_TRGO2Source_OC4Ref                         (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)                  /*!< OC4REF signal is used as trigger output (TRGO2)                */
#define TIM_TRGO2Source_OC5Ref                         TIM_CR2_MMS2_3                                                      /*!< OC5REF signal is used as trigger output (TRGO2)                */
#define TIM_TRGO2Source_OC6Ref                         (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_0)                                   /*!< OC6REF signal is used as trigger output (TRGO2)                */
#define TIM_TRGO2Source_OC4Ref_RisingFalling           (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1)                                   /*!< OC4REF rising or falling edges generate pulses on TRGO2        */
#define TIM_TRGO2Source_OC6Ref_RisingFalling           (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)                  /*!< OC6REF rising or falling edges generate pulses on TRGO2        */
#define TIM_TRGO2Source_OC4Ref_Rising_OC6Ref_Rising    (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2)                                   /*!< OC4REF or OC6REF rising edges generate pulses on TRGO2         */
#define TIM_TRGO2Source_OC4Ref_Rising_OC6Ref_Falling   (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 | TIM_CR2_MMS2_0)                  /*!< OC4REF rising or OC6REF falling edges generate pulses on TRGO2 */
#define TIM_TRGO2Source_OC5Ref_Rising_OC6Ref_Rising    (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 |TIM_CR2_MMS2_1)                   /*!< OC5REF or OC6REF rising edges generate pulses on TRGO2         */
#define TIM_TRGO2Source_OC5Ref_Rising_OC6Ref_Falling   (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0) /*!< OC5REF or OC6REF rising edges generate pulses on TRGO2         */
#define IS_TIM_TRGO2_SOURCE(SOURCE)     (((SOURCE) == TIM_TRGO2Source_Reset                       ) || \
                                         ((SOURCE) == TIM_TRGO2Source_Enable                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_Update                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC1                         ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC1Ref                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC2Ref                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC3Ref                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC4Ref                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC5Ref                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC6Ref                      ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC4Ref_RisingFalling        ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC6Ref_RisingFalling        ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC4Ref_Rising_OC6Ref_Rising ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC4Ref_Rising_OC6Ref_Falling) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC5Ref_Rising_OC6Ref_Rising ) || \
                                         ((SOURCE) == TIM_TRGO2Source_OC5Ref_Rising_OC6Ref_Falling))

/**
  * @}
  */

/** @defgroup TIM_Slave_Mode
  * @{
  */

#define TIM_SlaveMode_Disable              0x00000000U                                        /*!< Slave mode disabled           */
#define TIM_SlaveMode_Reset                TIM_SMCR_SMS_2                                     /*!< Reset Mode                    */
#define TIM_SlaveMode_Gated                (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)                  /*!< Gated Mode                    */
#define TIM_SlaveMode_Trigger              (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)                  /*!< Trigger Mode                  */
#define TIM_SlaveMode_External1            (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0) /*!< External Clock Mode 1         */
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Disable  ) || \
                                 ((MODE) == TIM_SlaveMode_Reset    ) || \
                                 ((MODE) == TIM_SlaveMode_Gated    ) || \
                                 ((MODE) == TIM_SlaveMode_Trigger  ) || \
                                 ((MODE) == TIM_SlaveMode_External1))
/**
  * @}
  */

/** @defgroup TIM_Master_Slave_Mode
  * @{
  */

#define TIM_MasterSlaveMode_Enable         TIM_SMCR_MSM                         /*!< Master/slave mode is selected */
#define TIM_MasterSlaveMode_Disable        0x00000000U                          /*!< No action                     */
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable ) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
  * @}
  */

/** @defgroup TIM_Flags
  * @{
  */

#define TIM_FLAG_Update                    TIM_SR_UIF                           /*!< Update interrupt flag            */
#define TIM_FLAG_CC1                       TIM_SR_CC1IF                         /*!< Capture/Compare 1 interrupt flag */
#define TIM_FLAG_CC2                       TIM_SR_CC2IF                         /*!< Capture/Compare 2 interrupt flag */
#define TIM_FLAG_CC3                       TIM_SR_CC3IF                         /*!< Capture/Compare 3 interrupt flag */
#define TIM_FLAG_CC4                       TIM_SR_CC4IF                         /*!< Capture/Compare 4 interrupt flag */
#define TIM_FLAG_CC5                       TIM_SR_CC5IF                         /*!< Capture/Compare 5 interrupt flag */
#define TIM_FLAG_CC6                       TIM_SR_CC6IF                         /*!< Capture/Compare 6 interrupt flag */
#define TIM_FLAG_COM                       TIM_SR_COMIF                         /*!< Commutation interrupt flag       */
#define TIM_FLAG_Trigger                   TIM_SR_TIF                           /*!< Trigger interrupt flag           */
#define TIM_FLAG_Break                     TIM_SR_BIF                           /*!< Break interrupt flag             */
#define TIM_FLAG_CC1OF                     TIM_SR_CC1OF                         /*!< Capture 1 overcapture flag       */
#define TIM_FLAG_CC2OF                     TIM_SR_CC2OF                         /*!< Capture 2 overcapture flag       */
#define TIM_FLAG_CC3OF                     TIM_SR_CC3OF                         /*!< Capture 3 overcapture flag       */
#define TIM_FLAG_CC4OF                     TIM_SR_CC4OF                         /*!< Capture 4 overcapture flag       */
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update ) || \
                               ((FLAG) == TIM_FLAG_CC1    ) || \
                               ((FLAG) == TIM_FLAG_CC2    ) || \
                               ((FLAG) == TIM_FLAG_CC3    ) || \
                               ((FLAG) == TIM_FLAG_CC4    ) || \
                               ((FLAG) == TIM_FLAG_CC5    ) || \
                               ((FLAG) == TIM_FLAG_CC6    ) || \
                               ((FLAG) == TIM_FLAG_COM    ) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break  ) || \
                               ((FLAG) == TIM_FLAG_CC1OF  ) || \
                               ((FLAG) == TIM_FLAG_CC2OF  ) || \
                               ((FLAG) == TIM_FLAG_CC3OF  ) || \
                               ((FLAG) == TIM_FLAG_CC4OF  ))


#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint32_t)0xFFFCE100) == 0x00000000) && ((TIM_FLAG) != 0x00000000))
/**
  * @}
  */


/** @defgroup TIM_Input_Capture_Filer_Value
  * @{
  */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Filter
  * @{
  */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TIM_DeadTime Filter
  * @{
  */

#define IS_TIM_DEADTIME(DEADTIME)    ((DEADTIME) <= 0xFFU)
/**
  * @}
  */

/** @defgroup TIM_BreakFilter
  * @{
  */

#define IS_TIM_BREAK_FILTER(BRKFILTER) ((BRKFILTER) <= 0xFUL)
/**
  * @}
  */

/** @defgroup TIM_OCReferenceClear
  * @{
  */
#define TIM_OCReferenceClear_ETRF          TIM_SMCR_OCCS                        /*!< OCREF clear select ETRF                        */
#define TIM_OCReferenceClear_OCREFCLR      0x00000000U                          /*!< OCREF clear select OCREF_CLR int input signals */
#define TIM_OCREFERENCECECLEAR_SOURCE(SOURCE) (((SOURCE) == TIM_OCReferenceClear_ETRF    ) || \
                                               ((SOURCE) == TIM_OCReferenceClear_OCREFCLR))

/**
  * @}
  */
/** @defgroup TIM_Remap
  * @{
  */
#define TIM2_ITR1ConnectTIM8Trgo       ((uint32_t)0x00000000)                   /*!< TIM8 TRGO     is connected to TIM2_ITR1 input */
#define TIM2_ITR1ConnectPTPTrgo        ((uint32_t)0x00000001)                   /*!< PTP TRGO      is connected to TIM2_ITR1 input */
#define TIM2_ITR1ConnectOTGFSSOF       ((uint32_t)0x00000002)                   /*!< OTG FS SOF    is connected to TIM2_ITR1 input */
#define TIM2_ITR1ConnectOTGHSSOF       ((uint32_t)0x00000003)                   /*!< OTG HS SOF    is connected to TIM2_ITR1 input */

#define TIM11_IT1ConnectGPIO_0         ((uint32_t)0x00000000)                   /*!< TIM11 GPIO    is connected to TIM11_TI1 input */
#define TIM11_IT1ConnectGPIO_1         ((uint32_t)0x00000001)                   /*!< TIM11 GPIO    is connected to TIM11_TI1 input */
#define TIM11_IT1ConnectHSE_RTC        ((uint32_t)0x00000002)                   /*!< HSE RTC clock is connected to TIM11_TI1 input */
#define TIM11_IT1ConnectGPIO_3         ((uint32_t)0x00000003)                   /*!< TIM11 GPIO    is connected to TIM11_TI1 input */

#define IS_TIM2_ITR1REMAP(TIM_REMAP)  (((TIM_REMAP) == TIM2_ITR1ConnectTIM8Trgo) || \
                                       ((TIM_REMAP) == TIM2_ITR1ConnectPTPTrgo ) || \
                                       ((TIM_REMAP) == TIM2_ITR1ConnectOTGFSSOF) || \
                                       ((TIM_REMAP) == TIM2_ITR1ConnectOTGHSSOF))

#define IS_TIM11_ITR1REMAP(TIM_REMAP)  (((TIM_REMAP) == TIM11_IT1ConnectGPIO_0 ) || \
                                        ((TIM_REMAP) == TIM11_IT1ConnectGPIO_1 ) || \
                                        ((TIM_REMAP) == TIM11_IT1ConnectHSE_RTC) || \
                                        ((TIM_REMAP) == TIM11_IT1ConnectGPIO_3 ))
/**
  * @}
  */

/** @defgroup TIM_ETRSel_Remap
  * @{
  */

#define TIM_ETR_GPIO        0x00000000U                                              /* !< ETR input is connected to GPIO                  */
#define TIM_ETR_COMP1       TIM_AF1_ETRSEL_0                                         /* !< ETR input is connected to COMP1_OUT             */
#define TIM_ETR_COMP2       TIM_AF1_ETRSEL_1                                         /* !< ETR input is connected to COMP2_OUT             */
#define TIM_ETR_COMP3       (TIM_AF1_ETRSEL_1 | TIM_AF1_ETRSEL_0)                    /* !< ETR input is connected to COMP3_OUT             */
#define TIM_ETR_COMP4       TIM_AF1_ETRSEL_2                                         /* !< ETR input is connected to COMP4_OUT             */
#define TIM_ETR_COMP5       (TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_0)                    /* !< ETR input is connected to COMP5_OUT             */
#define TIM_ETR_COMP6       (TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_1)                    /* !< ETR input is connected to COMP6_OUT             */
#define TIM_ETR_ADC1_AWD1   (TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_1 | TIM_AF1_ETRSEL_0) /* !< ETR input is connected to ADC1 analog watchdog 1 */
#define TIM_ETR_ADC1_AWD2   TIM_AF1_ETRSEL_3                                         /* !< ETR input is connected to ADC1 analog watchdog 2 */
#define TIM_ETR_ADC1_AWD3   (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_0)                    /* !< ETR input is connected to ADC1 analog watchdog 3 */
#define TIM_ETR_ADC2_AWD1   (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_1)                    /* !< ETR input is connected to ADC2 analog watchdog 1 */
#define TIM_ETR_ADC2_AWD2   (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_1 | TIM_AF1_ETRSEL_0) /* !< ETR input is connected to ADC2 analog watchdog 2 */
#define TIM_ETR_ADC2_AWD3   (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_2)                    /* !< ETR input is connected to ADC2 analog watchdog 3 */
#define TIM_ETR_ADC3_AWD1   (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_0) /* !< ETR input is connected to ADC3 analog watchdog 1 */
#define TIM_ETR_ADC3_AWD2   (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_1) /* !< ETR input is connected to ADC3 analog watchdog 2 */
#define TIM_ETR_ADC3_AWD3   TIM_AF1_ETRSEL                                           /* !< ETR input is connected to ADC3 analog watchdog 3 */
#define IS_TIM_ETRSEL_LIST1_REMAP(REMAP) (((REMAP) == TIM_ETR_GPIO     ) || \
                                          ((REMAP) == TIM_ETR_COMP1    ) || \
                                          ((REMAP) == TIM_ETR_COMP2    ) || \
                                          ((REMAP) == TIM_ETR_COMP3    ) || \
                                          ((REMAP) == TIM_ETR_COMP4    ) || \
                                          ((REMAP) == TIM_ETR_COMP5    ) || \
                                          ((REMAP) == TIM_ETR_COMP6    ) || \
                                          ((REMAP) == TIM_ETR_ADC1_AWD1) || \
                                          ((REMAP) == TIM_ETR_ADC1_AWD2) || \
                                          ((REMAP) == TIM_ETR_ADC1_AWD3) || \
                                          ((REMAP) == TIM_ETR_ADC2_AWD1) || \
                                          ((REMAP) == TIM_ETR_ADC2_AWD2) || \
                                          ((REMAP) == TIM_ETR_ADC2_AWD3) || \
                                          ((REMAP) == TIM_ETR_ADC3_AWD1) || \
                                          ((REMAP) == TIM_ETR_ADC3_AWD2) || \
                                          ((REMAP) == TIM_ETR_ADC3_AWD3))

#define TIM_ETR_1           TIM_AF1_ETRSEL_0                                         /* !< ETR input is connected to ETR[ 1] */
#define TIM_ETR_2           TIM_AF1_ETRSEL_1                                         /* !< ETR input is connected to ETR[ 2] */
#define TIM_ETR_3           (TIM_AF1_ETRSEL_1 | TIM_AF1_ETRSEL_0)                    /* !< ETR input is connected to ETR[ 3] */
#define TIM_ETR_4           TIM_AF1_ETRSEL_2                                         /* !< ETR input is connected to ETR[ 4] */
#define TIM_ETR_5           (TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_0)                    /* !< ETR input is connected to ETR[ 5] */
#define TIM_ETR_6           (TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_1)                    /* !< ETR input is connected to ETR[ 6] */
#define TIM_ETR_7           (TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_1 | TIM_AF1_ETRSEL_0) /* !< ETR input is connected to ETR[ 7] */
#define TIM_ETR_8           TIM_AF1_ETRSEL_3                                         /* !< ETR input is connected to ETR[ 8] */
#define TIM_ETR_9           (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_0)                    /* !< ETR input is connected to ETR[ 9] */
#define TIM_ETR_10          (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_1)                    /* !< ETR input is connected to ETR[10] */
#define TIM_ETR_11          (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_1 | TIM_AF1_ETRSEL_0) /* !< ETR input is connected to ETR[11] */
#define TIM_ETR_12          (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_2)                    /* !< ETR input is connected to ETR[12] */
#define TIM_ETR_13          (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_0) /* !< ETR input is connected to ETR[13] */
#define TIM_ETR_14          (TIM_AF1_ETRSEL_3 | TIM_AF1_ETRSEL_2 | TIM_AF1_ETRSEL_1) /* !< ETR input is connected to ETR[14] */
#define TIM_ETR_15          TIM_AF1_ETRSEL                                           /* !< ETR input is connected to ETR[15] */
#define IS_TIM_ETRSEL_LIST2_REMAP(REMAP) (((REMAP) == TIM_ETR_GPIO) || \
                                          ((REMAP) == TIM_ETR_1   ) || \
                                          ((REMAP) == TIM_ETR_2   ) || \
                                          ((REMAP) == TIM_ETR_3   ) || \
                                          ((REMAP) == TIM_ETR_4   ) || \
                                          ((REMAP) == TIM_ETR_5   ) || \
                                          ((REMAP) == TIM_ETR_6   ) || \
                                          ((REMAP) == TIM_ETR_7   ) || \
                                          ((REMAP) == TIM_ETR_8   ) || \
                                          ((REMAP) == TIM_ETR_9   ) || \
                                          ((REMAP) == TIM_ETR_10  ) || \
                                          ((REMAP) == TIM_ETR_11  ) || \
                                          ((REMAP) == TIM_ETR_12  ) || \
                                          ((REMAP) == TIM_ETR_13  ) || \
                                          ((REMAP) == TIM_ETR_14  ) || \
                                          ((REMAP) == TIM_ETR_15  ))

/**
  * @}
  */

/** @defgroup TIM_OCRSel_Remap
  * @{
  */

#define TIM_OCR_COMP1                 (uint32_t)0x00000000                   /* !< OCxref clear source select COMP1_OUT  */
#define TIM_OCR_COMP2                 (uint32_t)0x00000001                   /* !< OCxref clear source select COMP2_OUT  */
#define TIM_OCR_COMP3                 (uint32_t)0x00000002                   /* !< OCxref clear source select COMP3_OUT  */
#define TIM_OCR_COMP4                 (uint32_t)0x00000003                   /* !< OCxref clear source select COMP4_OUT  */
#define TIM_OCR_COMP5                 (uint32_t)0x00000004                   /* !< OCxref clear source select COMP5_OUT  */
#define TIM_OCR_COMP6                 (uint32_t)0x00000005                   /* !< OCxref clear source select COMP6_OUT  */
#define IS_TIM_OCRSEL_LIST1_REMAP(REMAP) (((REMAP) == TIM_OCR_COMP1) || \
                                          ((REMAP) == TIM_OCR_COMP2) || \
                                          ((REMAP) == TIM_OCR_COMP3) || \
                                          ((REMAP) == TIM_OCR_COMP4) || \
                                          ((REMAP) == TIM_OCR_COMP5) || \
                                          ((REMAP) == TIM_OCR_COMP6))

#define TIM_OCR_CLEAR_0               0x00000000U                            /* !< OCxref clear source select ocrefcr[0] */
#define TIM_OCR_CLEAR_1               TIM_AF2_OCRSEL_0                       /* !< OCxref clear source select ocrefcr[1] */
#define TIM_OCR_CLEAR_2               TIM_AF2_OCRSEL_1                       /* !< OCxref clear source select ocrefcr[2] */
#define TIM_OCR_CLEAR_3               (TIM_AF2_OCRSEL_1 | TIM_AF2_OCRSEL_0)  /* !< OCxref clear source select ocrefcr[3] */
#define TIM_OCR_CLEAR_4               TIM_AF2_OCRSEL_2                       /* !< OCxref clear source select ocrefcr[4] */
#define TIM_OCR_CLEAR_5               (TIM_AF2_OCRSEL_2 | TIM_AF2_OCRSEL_0)  /* !< OCxref clear source select ocrefcr[5] */
#define TIM_OCR_CLEAR_6               (TIM_AF2_OCRSEL_2 | TIM_AF2_OCRSEL_1)  /* !< OCxref clear source select ocrefcr[6] */
#define TIM_OCR_CLEAR_7               TIM_AF2_OCRSEL                         /* !< OCxref clear source select ocrefcr[7] */
#define IS_TIM_OCRSEL_LIST2_REMAP(REMAP) (((REMAP) == TIM_OCR_CLEAR_0) || \
                                          ((REMAP) == TIM_OCR_CLEAR_1) || \
                                          ((REMAP) == TIM_OCR_CLEAR_2) || \
                                          ((REMAP) == TIM_OCR_CLEAR_3) || \
                                          ((REMAP) == TIM_OCR_CLEAR_4) || \
                                          ((REMAP) == TIM_OCR_CLEAR_5) || \
                                          ((REMAP) == TIM_OCR_CLEAR_6) || \
                                          ((REMAP) == TIM_OCR_CLEAR_7))


/**
  * @}
  */

/** @defgroup TIM_TISel_Remap
  * @{
  */

#define TIM_TI1_CH1             0x00000000U                                                    /* !< TIM_CH1 input select GPIO      */
#define TIM_TI1_COMP1           TIM_TISEL_TI1SEL_0                                             /* !< TIM_CH1 input select COMP1_OUT */
#define TIM_TI1_COMP2           TIM_TISEL_TI1SEL_1                                             /* !< TIM_CH1 input select COMP2_OUT */
#define TIM_TI1_COMP3           (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)                      /* !< TIM_CH1 input select COMP3_OUT */
#define TIM_TI1_COMP4           TIM_TISEL_TI1SEL_2                                             /* !< TIM_CH1 input select COMP4_OUT */
#define TIM_TI1_COMP5           (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_0)                      /* !< TIM_CH1 input select COMP5_OUT */
#define TIM_TI1_COMP6           (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1)                      /* !< TIM_CH1 input select COMP6_OUT */
#define IS_TIM_TISEL_LIST1_REMAP(REMAP) (((REMAP) == TIM_TI1_CH1  ) || \
                                         ((REMAP) == TIM_TI1_COMP1) || \
                                         ((REMAP) == TIM_TI1_COMP2) || \
                                         ((REMAP) == TIM_TI1_COMP3) || \
                                         ((REMAP) == TIM_TI1_COMP4) || \
                                         ((REMAP) == TIM_TI1_COMP5) || \
                                         ((REMAP) == TIM_TI1_COMP6))

#define TIM_TI_CH               0x00000000U                                                    /* !< TIM_CH input select GPIO      */
#define TIM_TI_I1               TIM_TISEL_TI1SEL_0                                             /* !< TIM_CH input select ti_i[ 1] */
#define TIM_TI_I2               TIM_TISEL_TI1SEL_1                                             /* !< TIM_CH input select ti_i[ 2] */
#define TIM_TI_I3               (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0                     ) /* !< TIM_CH input select ti_i[ 3] */
#define TIM_TI_I4               TIM_TISEL_TI1SEL_2                                             /* !< TIM_CH input select ti_i[ 4] */
#define TIM_TI_I5               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_0                     ) /* !< TIM_CH input select ti_i[ 5] */
#define TIM_TI_I6               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1                     ) /* !< TIM_CH input select ti_i[ 6] */
#define TIM_TI_I7               (TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0) /* !< TIM_CH input select ti_i[ 7] */
#define TIM_TI_I8               TIM_TISEL_TI1SEL_3                                             /* !< TIM_CH input select ti_i[ 8] */
#define TIM_TI_I9               (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_0                     ) /* !< TIM_CH input select ti_i[ 9] */
#define TIM_TI_I10              (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_1                     ) /* !< TIM_CH input select ti_i[10] */
#define TIM_TI_I11              (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0) /* !< TIM_CH input select ti_i[11] */
#define TIM_TI_I12              (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_2                     ) /* !< TIM_CH input select ti_i[12] */
#define TIM_TI_I13              (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_0) /* !< TIM_CH input select ti_i[13] */
#define TIM_TI_I14              (TIM_TISEL_TI1SEL_3 | TIM_TISEL_TI1SEL_2 | TIM_TISEL_TI1SEL_1) /* !< TIM_CH input select ti_i[14] */
#define TIM_TI_I15              TIM_TISEL_TI1SEL                                               /* !< TIM_CH input select ti_i[15] */
#define IS_TIM_TISEL_LIST2_REMAP(REMAP) (((REMAP) == TIM_TI_CH ) || \
                                         ((REMAP) == TIM_TI_I1 ) || \
                                         ((REMAP) == TIM_TI_I2 ) || \
                                         ((REMAP) == TIM_TI_I3 ) || \
                                         ((REMAP) == TIM_TI_I4 ) || \
                                         ((REMAP) == TIM_TI_I5 ) || \
                                         ((REMAP) == TIM_TI_I6 ) || \
                                         ((REMAP) == TIM_TI_I7 ) || \
                                         ((REMAP) == TIM_TI_I8 ) || \
                                         ((REMAP) == TIM_TI_I9 ) || \
                                         ((REMAP) == TIM_TI_I10) || \
                                         ((REMAP) == TIM_TI_I11) || \
                                         ((REMAP) == TIM_TI_I12) || \
                                         ((REMAP) == TIM_TI_I13) || \
                                         ((REMAP) == TIM_TI_I14) || \
                                         ((REMAP) == TIM_TI_I15))

/**
  * @}
  */

/** @defgroup TIM_TISel_Channel
  * @{
  */

#define TIM_TISel_Channel1            (uint32_t)0x00000000                       /* !< TIM_CH input select channel1 */
#define TIM_TISel_Channel2            (uint32_t)0x00000008                       /* !< TIM_CH input select channel2 */
#define TIM_TISel_Channel3            (uint32_t)0x00000010                       /* !< TIM_CH input select channel3 */
#define TIM_TISel_Channel4            (uint32_t)0x00000018                       /* !< TIM_CH input select channel4 */

/**
  * @}
  */

/** @defgroup TIM_Break_Input_Source TIM Extended Break input source
  * @{
  */

#define TIM_BREAKINPUTSOURCE_BKIN     TIM_AF_BKINE                               /* !< An external source (GPIO) is connected to the BKIN pin */
#define TIM_BREAKINPUTSOURCE_COMP1    TIM_AF_BKCMP1E                             /* !< The COMP1 output is connected to the break input       */
#define TIM_BREAKINPUTSOURCE_COMP2    TIM_AF_BKCMP2E                             /* !< The COMP2 output is connected to the break input       */
#define TIM_BREAKINPUTSOURCE_COMP3    TIM_AF_BKCMP3E                             /* !< The COMP3 output is connected to the break input       */
#define TIM_BREAKINPUTSOURCE_COMP4    TIM_AF_BKCMP4E                             /* !< The COMP4 output is connected to the break input       */
#define TIM_BREAKINPUTSOURCE_COMP5    TIM_AF_BKCMP5E                             /* !< The COMP5 output is connected to the break input       */
#define TIM_BREAKINPUTSOURCE_COMP6    TIM_AF_BKCMP6E                             /* !< The COMP6 output is connected to the break input       */
#define IS_TIM_BREAKINPUTSOURCE(SOURCE)  (((SOURCE) == TIM_BREAKINPUTSOURCE_BKIN ) || \
                                          ((SOURCE) == TIM_BREAKINPUTSOURCE_COMP1) || \
                                          ((SOURCE) == TIM_BREAKINPUTSOURCE_COMP2) || \
                                          ((SOURCE) == TIM_BREAKINPUTSOURCE_COMP3) || \
                                          ((SOURCE) == TIM_BREAKINPUTSOURCE_COMP4) || \
                                          ((SOURCE) == TIM_BREAKINPUTSOURCE_COMP5) || \
                                          ((SOURCE) == TIM_BREAKINPUTSOURCE_COMP6))

/**
  * @}
  */

/** @defgroup TIM_Break_Input_Source_Enable TIM Extended Break input source enabling
  * @{
  */

#define TIM_BREAKINPUTSOURCE_DISABLE     0x00000000U                            /* !< Break input source is disabled */
#define TIM_BREAKINPUTSOURCE_ENABLE      0x00000001U                            /* !< Break input source is enabled  */
#define IS_TIM_BREAKINPUTSOURCE_STATE(STATE)  (((STATE) == TIM_BREAKINPUTSOURCE_DISABLE)  || \
                                               ((STATE) == TIM_BREAKINPUTSOURCE_ENABLE ))

/**
  * @}
  */

/** @defgroup TIM_Break_Input_Source_Polarity TIM Extended Break input polarity
  * @{
  */

#define TIM_BREAKINPUTSOURCE_POLARITY_INVERTED        0x00000001U               /* !< Break input source is inverted
                                                                                      (active high if BKP = 0, active low if BKP = 1) */
#define TIM_BREAKINPUTSOURCE_POLARITY_NOT_INVERTED    0x00000000U               /* !< Break input source is not inverted
                                                                                      (active low if BKP = 0, active high if BKP = 1) */
#define IS_TIM_BREAKINPUTSOURCE_POLARITY(POLARITY)  (((POLARITY) == TIM_BREAKINPUTSOURCE_POLARITY_INVERTED     ) || \
                                                     ((POLARITY) == TIM_BREAKINPUTSOURCE_POLARITY_NOT_INVERTED))

/**
  * @}
  */

/** @defgroup TIM_AF1
  * @{
  */
#define  TIM_AF_BKINE_Pos                  (0U)
#define  TIM_AF_BKCMP1E_Pos                (1U)
#define  TIM_AF_BKCMP2E_Pos                (2U)
#define  TIM_AF_BKCMP3E_Pos                (3U)
#define  TIM_AF_BKCMP4E_Pos                (4U)
#define  TIM_AF_BKCMP5E_Pos                (5U)
#define  TIM_AF_BKCMP6E_Pos                (6U)

#define  TIM_AF_BKINP_Pos                  (9U)
#define  TIM_AF_BKCMP1P_Pos                (10U)
#define  TIM_AF_BKCMP2P_Pos                (11U)
#define  TIM_AF_BKCMP3P_Pos                (12U)
#define  TIM_AF_BKCMP4P_Pos                (13U)

/**
  * @}
  */

/** @defgroup TIM_Legacy
  * @{
  */

#define TIM_DMABurstLength_1Byte           TIM_DMABurstLength_1Transfer
#define TIM_DMABurstLength_2Bytes          TIM_DMABurstLength_2Transfers
#define TIM_DMABurstLength_3Bytes          TIM_DMABurstLength_3Transfers
#define TIM_DMABurstLength_4Bytes          TIM_DMABurstLength_4Transfers
#define TIM_DMABurstLength_5Bytes          TIM_DMABurstLength_5Transfers
#define TIM_DMABurstLength_6Bytes          TIM_DMABurstLength_6Transfers
#define TIM_DMABurstLength_7Bytes          TIM_DMABurstLength_7Transfers
#define TIM_DMABurstLength_8Bytes          TIM_DMABurstLength_8Transfers
#define TIM_DMABurstLength_9Bytes          TIM_DMABurstLength_9Transfers
#define TIM_DMABurstLength_10Bytes         TIM_DMABurstLength_10Transfers
#define TIM_DMABurstLength_11Bytes         TIM_DMABurstLength_11Transfers
#define TIM_DMABurstLength_12Bytes         TIM_DMABurstLength_12Transfers
#define TIM_DMABurstLength_13Bytes         TIM_DMABurstLength_13Transfers
#define TIM_DMABurstLength_14Bytes         TIM_DMABurstLength_14Transfers
#define TIM_DMABurstLength_15Bytes         TIM_DMABurstLength_15Transfers
#define TIM_DMABurstLength_16Bytes         TIM_DMABurstLength_16Transfers
#define TIM_DMABurstLength_17Bytes         TIM_DMABurstLength_17Transfers
#define TIM_DMABurstLength_18Bytes         TIM_DMABurstLength_18Transfers
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* TimeBase management ********************************************************/
void TIM_DeInit(TIM_TypeDef* TIMx);
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t TIM_PSCReloadMode);
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint32_t TIM_CounterMode);
void TIM_SetCounter(TIM_TypeDef* TIMx, uint32_t Counter);
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint32_t Autoreload);
void TIM_SetRepetitionCounter(TIM_TypeDef* TIMx, uint32_t RepetitionCounter);
uint32_t TIM_GetCounter(TIM_TypeDef* TIMx);
uint32_t TIM_GetPrescaler(TIM_TypeDef* TIMx);
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, uint32_t TIM_UpdateSource);
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, uint32_t TIM_OPMode);
void TIM_SetClockDivision(TIM_TypeDef* TIMx, uint32_t TIM_CKD);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Advanced-control timers (TIM1 and TIM8) specific features*******************/
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void TIM_ConfigBreakInput(TIM_TypeDef* TIMx, TIM_BreakInputConfigTypeDef* BreakInputConfig);
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_DisarmBreakInput(TIM_TypeDef* TIMx);
FlagStatus TIM_WaitBkdsrmIsHardwareClear(TIM_TypeDef* TIMx);

/* Output Compare management **************************************************/
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC5Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC6Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_GroupChannel5(TIM_TypeDef* TIMx, uint32_t TIM_Group_Channel5);
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_SelectOCxM(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_OCMode);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint32_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint32_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint32_t Compare4);
void TIM_SetCompare5(TIM_TypeDef* TIMx, uint32_t Compare5);
void TIM_SetCompare6(TIM_TypeDef* TIMx, uint32_t Compare6);
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction);
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction);
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction);
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction);
void TIM_ForcedOC5Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction);
void TIM_ForcedOC6Config(TIM_TypeDef* TIMx, uint32_t TIM_ForcedAction);
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState);
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload);
void TIM_OC5PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload);
void TIM_OC6PreloadConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPreload);
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast);
void TIM_OC5FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast);
void TIM_OC6FastConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCFast);
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear);
void TIM_ClearOC5Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear);
void TIM_ClearOC6Ref(TIM_TypeDef* TIMx, uint32_t TIM_OCClear);
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity);
void TIM_OC5PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity);
void TIM_OC6PolarityConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCPolarity);
void TIM_SelectOCREFClear(TIM_TypeDef* TIMx, uint32_t TIM_OCReferenceClear);
void TIM_CCxCmd(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint32_t TIM_Channel, uint32_t TIM_CCxN);
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Input Capture management ***************************************************/
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct);
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct);
uint32_t TIM_GetCapture1(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture2(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture3(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture4(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture5(TIM_TypeDef* TIMx);
uint32_t TIM_GetCapture6(TIM_TypeDef* TIMx);
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC);
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC);
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC);
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, uint32_t TIM_ICPSC);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, uint32_t TIM_IT, FunctionalState NewState);
void TIM_GenerateEvent(TIM_TypeDef* TIMx, uint32_t TIM_EventSource);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, uint32_t TIM_FLAG);
void TIM_ClearFlag(TIM_TypeDef* TIMx, uint32_t TIM_FLAG);
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, uint32_t TIM_IT);
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint32_t TIM_IT);
void TIM_DMAConfig(TIM_TypeDef* TIMx, uint32_t TIM_DMABase, uint32_t TIM_DMABurstLength);
void TIM_DMACmd(TIM_TypeDef* TIMx, uint32_t TIM_DMASource, FunctionalState NewState);
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Clocks management **********************************************************/
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint32_t TIM_InputTriggerSource);
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint32_t TIM_TIxExternalCLKSource,
                                uint32_t TIM_ICPolarity, uint32_t ICFilter);
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                             uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler,
                             uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);


/* Synchronization management *************************************************/
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, uint32_t TIM_InputTriggerSource);
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, uint32_t TIM_TRGOSource);
void TIM_SelectOutputTrigger2(TIM_TypeDef* TIMx, uint32_t TIM_TRGO2Source);
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, uint32_t TIM_SlaveMode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, uint32_t TIM_MasterSlaveMode);
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint32_t TIM_ExtTRGPrescaler, uint32_t TIM_ExtTRGPolarity,
                   uint32_t ExtTRGFilter);

/* Specific interface management **********************************************/
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint32_t TIM_EncoderMode,
                                uint32_t TIM_IC1Polarity, uint32_t TIM_IC2Polarity);
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState);

/* Specific remapping management **********************************************/
/* For TIM2 & TIM11 OR register                         */
void TIM_RemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_Remap);
/* For TIM1/TIM8 and TIM2-5 ETRSEL bits of AF1 register */
void TIM_ETRSelRemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_ETRSel_Remap);
/* For TIM1/TIM8 and TIM2-5 AF2 register                */
void TIM_OCRSelRemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_OCRSel_Remap);
/* For TIM1/TIM8 and TIM2-5 TISEL register              */
void TIM_TISelRemapConfig(TIM_TypeDef* TIMx, uint32_t TIM_TISel_Channel, uint32_t TIM_TISel_Remap);


#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_TIM_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
