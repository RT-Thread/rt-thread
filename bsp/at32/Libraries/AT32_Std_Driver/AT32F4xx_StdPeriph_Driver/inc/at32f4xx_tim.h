/**
 **************************************************************************
 * File Name    : at32f4xx_tim.h
 * Description  : at32f4xx TIMER header file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_TIM_H
#define __AT32F4xx_TIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup TMR
  * @{
  */ 

/** @defgroup TMR_Exported_Types
  * @{
  */ 

/** 
  * @brief  TMR Time Base Init structure definition
  * @note   This structure is used with all TMRx except for TMR6 and TMR7.    
  */

typedef struct
{
  uint16_t TMR_DIV;         			/*!< Specifies the prescaler value used to divide the TMR clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

  uint32_t TMR_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TMR_Counter_Mode */

  uint32_t TMR_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event. 
																			 This parameter must be a number between 0x0000 and 0xFFFF. */ 

  uint16_t TMR_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TMR_Clock_Division_CKD */

  uint8_t TMR_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF. 
                                       @note This parameter is valid only for TMR1 and TMR8. */
} TMR_TimerBaseInitType;       

/** 
  * @brief  TMR Output Compare Init structure definition  
  */

typedef struct
{
  uint16_t TMR_OCMode;        /*!< Specifies the TMR mode.
                                   This parameter can be a value of @ref TMR_Output_Compare_and_PWM_modes */

  uint16_t TMR_OutputState;   /*!< Specifies the TMR Output Compare state.
                                   This parameter can be a value of @ref TMR_Output_Compare_state */

  uint16_t TMR_OutputNState;  /*!< Specifies the TMR complementary Output Compare state.
                                   This parameter can be a value of @ref TMR_Output_Compare_N_state
                                   @note This parameter is valid only for TMR1 and TMR8. */

  uint32_t TMR_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */
 

  uint16_t TMR_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TMR_Output_Compare_Polarity */

  uint16_t TMR_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TMR_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TMR1 and TMR8. */

  uint16_t TMR_OCIdleState;   /*!< Specifies the TMR Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TMR_Output_Compare_Idle_State
                                   @note This parameter is valid only for TMR1 and TMR8. */

  uint16_t TMR_OCNIdleState;  /*!< Specifies the TMR Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TMR_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TMR1 and TMR8. */
} TMR_OCInitType;

/** 
  * @brief  TMR Input Capture Init structure definition  
  */

typedef struct
{

  uint16_t TMR_Channel;       /*!< Specifies the TMR channel.
                                  This parameter can be a value of @ref TMR_Channel */

  uint16_t TMR_ICPolarity;    /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TMR_Input_Capture_Polarity */

  uint16_t TMR_ICSelection;   /*!< Specifies the input.
                                  This parameter can be a value of @ref TMR_Input_Capture_Selection */

  uint16_t TMR_ICDIV;         /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TMR_Input_Capture_Prescaler */

  uint16_t TMR_ICFilter;      /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} TMR_ICInitType;

/** 
  * @brief  BDTR structure definition 
  * @note   This structure is used only with TMR1 and TMR8.    
  */

typedef struct
{

  uint16_t TMR_OSIMRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state */

  uint16_t TMR_OSIMIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state */

  uint16_t TMR_LOCKgrade;         /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref Lock_level */ 

  uint16_t TMR_DeadTime;          /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

  uint16_t TMR_Break;             /*!< Specifies whether the TMR Break input is enabled or not. 
                                      This parameter can be a value of @ref Break_Input_enable_disable */

  uint16_t TMR_BreakPolarity;     /*!< Specifies the TMR Break Input pin polarity.
                                      This parameter can be a value of @ref Break_Polarity */

  uint16_t TMR_AutomaticOutput;   /*!< Specifies whether the TMR Automatic Output feature is enabled or not. 
                                      This parameter can be a value of @ref TMR_AOE_Bit_Set_Reset */
} TMR_BRKDTInitType;

/** @defgroup TMR_Exported_constants 
  * @{
  */

#if defined (AT32F403xx)
#define IS_TMR_ALL_PERIPH(PERIPH)    (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR6) || \
                                      ((PERIPH) == TMR7) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11)|| \
                                      ((PERIPH) == TMR12)|| \
                                      ((PERIPH) == TMR13)|| \
                                      ((PERIPH) == TMR14)|| \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_ALL_PERIPH(PERIPH)    (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11))
#elif defined (AT32F415xx)
#define IS_TMR_ALL_PERIPH(PERIPH)    (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_ALL_PERIPH(PERIPH)    (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR6) || \
                                      ((PERIPH) == TMR7) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11)|| \
                                      ((PERIPH) == TMR12)|| \
                                      ((PERIPH) == TMR13)|| \
                                      ((PERIPH) == TMR14))
#endif



/* LIST1: TMR 1, 8 and 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST1_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST1_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR8))
#elif defined (AT32F415xx)
#define IS_TMR_LIST1_PERIPH(PERIPH)  (((PERIPH) == TMR1))

#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST1_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR8))
#endif

/* LIST2: TMR 1, 8, 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST2_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST2_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR8))
#elif defined (AT32F415xx)
#define IS_TMR_LIST2_PERIPH(PERIPH)  (((PERIPH) == TMR1))

#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST2_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR8))
#endif


/* LIST3: TMR 1, 2, 3, 4, 5 ,8 and 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST3_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR15)) 
#elif defined (AT32F413xx)
#define IS_TMR_LIST3_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8)) 
#elif defined (AT32F415xx)
#define IS_TMR_LIST3_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST3_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8))
#endif
									                                 
/* LIST4: TMR 1, 2, 3, 4, 5, 8, 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST4_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST4_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8))
#elif defined (AT32F415xx)
#define IS_TMR_LIST4_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST4_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8))
#endif

/* LIST5: TMR 1, 2, 3, 4, 5, 8 and 15 */ 

#if defined (AT32F403xx)
#define IS_TMR_LIST5_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST5_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8))
#elif defined (AT32F415xx)
#define IS_TMR_LIST5_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST5_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8))
#endif

/* LIST6: TMR 1, 2, 3, 4, 5, 8, 9, 12 and 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST6_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR12)|| \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST6_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9))
#elif defined (AT32F415xx)
#define IS_TMR_LIST6_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR9))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST6_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR12))
#endif

/* LIST7: TMR 1, 2, 3, 4, 5, 6, 7, 8, 9, 12 and 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST7_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR6) || \
                                      ((PERIPH) == TMR7) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR12)|| \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST7_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9))
#elif defined (AT32F415xx)
#define IS_TMR_LIST7_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR9))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST7_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR6) || \
                                      ((PERIPH) == TMR7) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR12))
#endif

/* LIST8: TMR 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15 */  
#if defined (AT32F403xx)
#define IS_TMR_LIST8_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11)|| \
                                      ((PERIPH) == TMR12)|| \
                                      ((PERIPH) == TMR13)|| \
                                      ((PERIPH) == TMR14)|| \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST8_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11))
#elif defined (AT32F415xx)
#define IS_TMR_LIST8_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST8_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR9) || \
                                      ((PERIPH) == TMR10)|| \
                                      ((PERIPH) == TMR11)|| \
                                      ((PERIPH) == TMR12)|| \
                                      ((PERIPH) == TMR13)|| \
                                      ((PERIPH) == TMR14))
#endif

/* LIST9: TMR 1, 2, 3, 4, 5, 6, 7, 8, 15 */
#if defined (AT32F403xx)
#define IS_TMR_LIST9_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR6) || \
                                      ((PERIPH) == TMR7) || \
                                      ((PERIPH) == TMR8) || \
                                      ((PERIPH) == TMR15))
#elif defined (AT32F413xx)
#define IS_TMR_LIST9_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR8))
#elif defined (AT32F415xx)
#define IS_TMR_LIST9_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5))
#elif defined (AT32F403Axx) || defined (AT32F407xx)
#define IS_TMR_LIST9_PERIPH(PERIPH)  (((PERIPH) == TMR1) || \
                                      ((PERIPH) == TMR2) || \
                                      ((PERIPH) == TMR3) || \
                                      ((PERIPH) == TMR4) || \
                                      ((PERIPH) == TMR5) || \
                                      ((PERIPH) == TMR6) || \
                                      ((PERIPH) == TMR7) || \
                                      ((PERIPH) == TMR8))
#endif

/*LIST10:TIM 2, 5*/																	 
#define IS_TMR_PLUSMODE_PERIPH(PERIPH) (((PERIPH)==TMR2) ||\
																			 ((PERIPH)==TMR5))
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_and_PWM_modes 
  * @{
  */

#define TMR_OCMode_Timing                  ((uint16_t)0x0000)
#define TMR_OCMode_Active                  ((uint16_t)0x0010)
#define TMR_OCMode_Inactive                ((uint16_t)0x0020)
#define TMR_OCMode_Toggle                  ((uint16_t)0x0030)
#define TMR_OCMode_PWM1                    ((uint16_t)0x0060)
#define TMR_OCMode_PWM2                    ((uint16_t)0x0070)
#define IS_TMR_OC_MODE(MODE)               (((MODE) == TMR_OCMode_Timing) || \
                                            ((MODE) == TMR_OCMode_Active) || \
                                            ((MODE) == TMR_OCMode_Inactive) || \
                                            ((MODE) == TMR_OCMode_Toggle)|| \
                                            ((MODE) == TMR_OCMode_PWM1) || \
                                            ((MODE) == TMR_OCMode_PWM2))
#define IS_TMR_OCM(MODE)                   (((MODE) == TMR_OCMode_Timing) || \
                                            ((MODE) == TMR_OCMode_Active) || \
                                            ((MODE) == TMR_OCMode_Inactive) || \
                                            ((MODE) == TMR_OCMode_Toggle)|| \
                                            ((MODE) == TMR_OCMode_PWM1) || \
                                            ((MODE) == TMR_OCMode_PWM2) ||	\
                                            ((MODE) == TMR_ForcedAction_Active) || \
                                            ((MODE) == TMR_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TMR_One_Pulse_Mode 
  * @{
  */

#define TMR_OPMode_Once                  ((uint16_t)0x0008)
#define TMR_OPMode_Repetitive            ((uint16_t)0x0000)
#define IS_TMR_OPM_MODE(MODE)            (((MODE) == TMR_OPMode_Once) || \
                                          ((MODE) == TMR_OPMode_Repetitive))
/**
  * @}
  */ 

/** @defgroup TMR_Channel 
  * @{
  */

#define TMR_Channel_1                      ((uint16_t)0x0000)
#define TMR_Channel_2                      ((uint16_t)0x0004)
#define TMR_Channel_3                      ((uint16_t)0x0008)
#define TMR_Channel_4                      ((uint16_t)0x000C)
#define IS_TMR_CHANNEL(CHANNEL)            (((CHANNEL) == TMR_Channel_1) || \
                                            ((CHANNEL) == TMR_Channel_2) || \
                                            ((CHANNEL) == TMR_Channel_3) || \
                                            ((CHANNEL) == TMR_Channel_4))
#define IS_TMR_PWMI_CHANNEL(CHANNEL)       (((CHANNEL) == TMR_Channel_1) || \
                                            ((CHANNEL) == TMR_Channel_2))
#define IS_TMR_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TMR_Channel_1) || \
                                               ((CHANNEL) == TMR_Channel_2) || \
                                               ((CHANNEL) == TMR_Channel_3))
/**
  * @}
  */ 

/** @defgroup TMR_Clock_Division_CKD 
  * @{
  */

#define TMR_CKD_DIV1                       ((uint16_t)0x0000)
#define TMR_CKD_DIV2                       ((uint16_t)0x0100)
#define TMR_CKD_DIV4                       ((uint16_t)0x0200)
#define IS_TMR_CKD_DIV(DIV)                (((DIV) == TMR_CKD_DIV1) || \
                                            ((DIV) == TMR_CKD_DIV2) || \
                                            ((DIV) == TMR_CKD_DIV4))
/**
  * @}
  */


/** @defgroup TMR_Counter_Mode 
  * @{
  */

#define TMR_CounterDIR_Up                 ((uint16_t)0x0000)
#define TMR_CounterDIR_Down               ((uint16_t)0x0010)
#define TMR_CounterDIR_CenterAligned1     ((uint16_t)0x0020)
#define TMR_CounterDIR_CenterAligned2     ((uint16_t)0x0040)
#define TMR_CounterDIR_CenterAligned3     ((uint16_t)0x0060)
#define IS_TMR_COUNTER_DIR(DIR)           (((DIR) == TMR_CounterDIR_Up) ||  \
                                           ((DIR) == TMR_CounterDIR_Down) || \
                                           ((DIR) == TMR_CounterDIR_CenterAligned1) || \
                                           ((DIR) == TMR_CounterDIR_CenterAligned2) || \
                                           ((DIR) == TMR_CounterDIR_CenterAligned3))
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_Polarity 
  * @{
  */

#define TMR_OCPolarity_High                ((uint16_t)0x0000)
#define TMR_OCPolarity_Low                 ((uint16_t)0x0002)
#define IS_TMR_OC_POLARITY(POLARITY)       (((POLARITY) == TMR_OCPolarity_High) || \
                                            ((POLARITY) == TMR_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_N_Polarity 
  * @{
  */
  
#define TMR_OCNPolarity_High               ((uint16_t)0x0000)
#define TMR_OCNPolarity_Low                ((uint16_t)0x0008)
#define IS_TMR_OCN_POLARITY(POLARITY)      (((POLARITY) == TMR_OCNPolarity_High) || \
                                            ((POLARITY) == TMR_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TMR_Output_Compare_state 
  * @{
  */

#define TMR_OutputState_Disable            ((uint16_t)0x0000)
#define TMR_OutputState_Enable             ((uint16_t)0x0001)
#define IS_TMR_OUTPUT_STATE(STATE)         (((STATE) == TMR_OutputState_Disable) || \
                                            ((STATE) == TMR_OutputState_Enable))
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_N_state 
  * @{
  */

#define TMR_OutputNState_Disable           ((uint16_t)0x0000)
#define TMR_OutputNState_Enable            ((uint16_t)0x0004)
#define IS_TMR_OUTPUTN_STATE(STATE)        (((STATE) == TMR_OutputNState_Disable) || \
                                            ((STATE) == TMR_OutputNState_Enable))
/**
  * @}
  */ 

/** @defgroup TMR_Capture_Compare_state 
  * @{
  */

#define TMR_CCx_Enable                     ((uint16_t)0x0001)
#define TMR_CCx_Disable                    ((uint16_t)0x0000)
#define IS_TMR_CCX(CCX)                    (((CCX) == TMR_CCx_Enable) || \
                                            ((CCX) == TMR_CCx_Disable))
/**
  * @}
  */ 

/** @defgroup TMR_Capture_Compare_N_state 
  * @{
  */

#define TMR_CCxN_Enable                    ((uint16_t)0x0004)
#define TMR_CCxN_Disable                   ((uint16_t)0x0000)
#define IS_TMR_CCXN(CCXN)                  (((CCXN) == TMR_CCxN_Enable) || \
                                            ((CCXN) == TMR_CCxN_Disable))
/**
  * @}
  */ 

/** @defgroup Break_Input_enable_disable 
  * @{
  */

#define TMR_Break_Enable                  ((uint16_t)0x1000)
#define TMR_Break_Disable                 ((uint16_t)0x0000)
#define IS_TMR_BREAK_STATE(STATE)         (((STATE) == TMR_Break_Enable) || \
                                           ((STATE) == TMR_Break_Disable))
/**
  * @}
  */ 

/** @defgroup Break_Polarity 
  * @{
  */

#define TMR_BreakPolarity_Low             ((uint16_t)0x0000)
#define TMR_BreakPolarity_High            ((uint16_t)0x2000)
#define IS_TMR_BREAK_POLARITY(POLARITY)   (((POLARITY) == TMR_BreakPolarity_Low) || \
                                           ((POLARITY) == TMR_BreakPolarity_High))
/**
  * @}
  */ 

/** @defgroup TMR_AOE_Bit_Set_Reset 
  * @{
  */

#define TMR_AutomaticOutput_Enable            ((uint16_t)0x4000)
#define TMR_AutomaticOutput_Disable           ((uint16_t)0x0000)
#define IS_TMR_AUTOMATIC_OUTPUT_STATE(STATE)  (((STATE) == TMR_AutomaticOutput_Enable) || \
                                               ((STATE) == TMR_AutomaticOutput_Disable))
/**
  * @}
  */ 

/** @defgroup Lock_level 
  * @{
  */

#define TMR_LOCKgrade_OFF                  ((uint16_t)0x0000)
#define TMR_LOCKgrade_1                    ((uint16_t)0x0100)
#define TMR_LOCKgrade_2                    ((uint16_t)0x0200)
#define TMR_LOCKgrade_3                    ((uint16_t)0x0300)
#define IS_TMR_LOCK_grade(grade)           (((grade) == TMR_LOCKgrade_OFF) || \
                                            ((grade) == TMR_LOCKgrade_1) || \
                                            ((grade) == TMR_LOCKgrade_2) || \
                                            ((grade) == TMR_LOCKgrade_3))
/**
  * @}
  */ 

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state 
  * @{
  */

#define TMR_OSIMIState_Enable              ((uint16_t)0x0400)
#define TMR_OSIMIState_Disable             ((uint16_t)0x0000)
#define IS_TMR_OSIMI_STATE(STATE)          (((STATE) == TMR_OSIMIState_Enable) || \
                                            ((STATE) == TMR_OSIMIState_Disable))
/**
  * @}
  */

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state 
  * @{
  */

#define TMR_OSIMRState_Enable              ((uint16_t)0x0800)
#define TMR_OSIMRState_Disable             ((uint16_t)0x0000)
#define IS_TMR_OSIMR_STATE(STATE)          (((STATE) == TMR_OSIMRState_Enable) || \
                                            ((STATE) == TMR_OSIMRState_Disable))
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_Idle_State 
  * @{
  */

#define TMR_OCIdleState_Set                ((uint16_t)0x0100)
#define TMR_OCIdleState_Reset              ((uint16_t)0x0000)
#define IS_TMR_OCIDLE_STATE(STATE)         (((STATE) == TMR_OCIdleState_Set) || \
                                            ((STATE) == TMR_OCIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_N_Idle_State 
  * @{
  */

#define TMR_OCNIdleState_Set               ((uint16_t)0x0200)
#define TMR_OCNIdleState_Reset             ((uint16_t)0x0000)
#define IS_TMR_OCNIDLE_STATE(STATE)        (((STATE) == TMR_OCNIdleState_Set) || \
                                            ((STATE) == TMR_OCNIdleState_Reset))
/**
  * @}
  */ 

/** @defgroup TMR_Input_Capture_Polarity 
  * @{
  */

#define  TMR_ICPolarity_Rising             ((uint16_t)0x0000)
#define  TMR_ICPolarity_Falling            ((uint16_t)0x0002)
#define  TMR_ICPolarity_BothEdge           ((uint16_t)0x000A)
#define IS_TMR_IC_POLARITY(POLARITY)       (((POLARITY) == TMR_ICPolarity_Rising) || \
                                            ((POLARITY) == TMR_ICPolarity_Falling))
#define IS_TMR_IC_POLARITY_LITE(POLARITY)  (((POLARITY) == TMR_ICPolarity_Rising) || \
                                            ((POLARITY) == TMR_ICPolarity_Falling)|| \
                                            ((POLARITY) == TMR_ICPolarity_BothEdge))                                      
/**
  * @}
  */ 

/** @defgroup TMR_Input_Capture_Selection 
  * @{
  */

#define TMR_ICSelection_DirectTI           ((uint16_t)0x0001) /*!< TMR Input 1, 2, 3 or 4 is selected to be 
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */
#define TMR_ICSelection_IndirectTI         ((uint16_t)0x0002) /*!< TMR Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */
#define TMR_ICSelection_TRC                ((uint16_t)0x0003) /*!< TMR Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TMR_IC_SELECTION(SELECTION)     (((SELECTION) == TMR_ICSelection_DirectTI) || \
                                            ((SELECTION) == TMR_ICSelection_IndirectTI) || \
                                            ((SELECTION) == TMR_ICSelection_TRC))
/**
  * @}
  */ 

/** @defgroup TMR_Input_Capture_Prescaler 
  * @{
  */

#define TMR_ICDIV_DIV1                     ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TMR_ICDIV_DIV2                     ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define TMR_ICDIV_DIV4                     ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define TMR_ICDIV_DIV8                     ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TMR_IC_DIV(DIV)                 (((DIV) == TMR_ICDIV_DIV1) || \
                                            ((DIV) == TMR_ICDIV_DIV2) || \
                                            ((DIV) == TMR_ICDIV_DIV4) || \
                                            ((DIV) == TMR_ICDIV_DIV8))
/**
  * @}
  */ 

/** @defgroup TMR_interrupt_sources 
  * @{
  */

#define TMR_INT_Overflow                    ((uint16_t)0x0001)
#define TMR_INT_CC1                         ((uint16_t)0x0002)
#define TMR_INT_CC2                         ((uint16_t)0x0004)
#define TMR_INT_CC3                         ((uint16_t)0x0008)
#define TMR_INT_CC4                         ((uint16_t)0x0010)
#define TMR_INT_HALL                        ((uint16_t)0x0020)
#define TMR_INT_Trigger                     ((uint16_t)0x0040)
#define TMR_INT_Break                       ((uint16_t)0x0080)
#define IS_TMR_INT(INT) ((((INT) & (uint16_t)0xFF00) == 0x0000) && ((INT) != 0x0000))

#define IS_TMR_GET_INT(INT)                 (((INT) == TMR_INT_Overflow) || \
                                             ((INT) == TMR_INT_CC1) || \
                                             ((INT) == TMR_INT_CC2) || \
                                             ((INT) == TMR_INT_CC3) || \
                                             ((INT) == TMR_INT_CC4) || \
                                             ((INT) == TMR_INT_HALL) || \
                                             ((INT) == TMR_INT_Trigger) || \
                                             ((INT) == TMR_INT_Break))
/**
  * @}
  */ 

/** @defgroup TMR_DMA_Base_address 
  * @{
  */

#define TMR_DMABase_CTRL1                   ((uint16_t)0x0000)
#define TMR_DMABase_CTRL2                   ((uint16_t)0x0001)
#define TMR_DMABase_SMC                     ((uint16_t)0x0002)
#define TMR_DMABase_DIE                     ((uint16_t)0x0003)
#define TMR_DMABase_STS                     ((uint16_t)0x0004)
#define TMR_DMABase_EVEG                    ((uint16_t)0x0005)
#define TMR_DMABase_CCM1                    ((uint16_t)0x0006)
#define TMR_DMABase_CCM2                    ((uint16_t)0x0007)
#define TMR_DMABase_CCE                     ((uint16_t)0x0008)
#define TMR_DMABase_CNT                     ((uint16_t)0x0009)
#define TMR_DMABase_DIV                     ((uint16_t)0x000A)
#define TMR_DMABase_AR                      ((uint16_t)0x000B)
#define TMR_DMABase_RC                      ((uint16_t)0x000C)
#define TMR_DMABase_CC1                     ((uint16_t)0x000D)
#define TMR_DMABase_CC2                     ((uint16_t)0x000E)
#define TMR_DMABase_CC3                     ((uint16_t)0x000F)
#define TMR_DMABase_CC4                     ((uint16_t)0x0010)
#define TMR_DMABase_BRKDT                   ((uint16_t)0x0011)
#define TMR_DMABase_DMAC                    ((uint16_t)0x0012)
#define IS_TMR_DMA_BASE(BASE)               (((BASE) == TMR_DMABase_CTRL1) || \
                                             ((BASE) == TMR_DMABase_CTRL2) || \
                                             ((BASE) == TMR_DMABase_SMC) || \
                                             ((BASE) == TMR_DMABase_DIE) || \
                                             ((BASE) == TMR_DMABase_STS) || \
                                             ((BASE) == TMR_DMABase_EVEG) || \
                                             ((BASE) == TMR_DMABase_CCM1) || \
                                             ((BASE) == TMR_DMABase_CCM2) || \
                                             ((BASE) == TMR_DMABase_CCE) || \
                                             ((BASE) == TMR_DMABase_CNT) || \
                                             ((BASE) == TMR_DMABase_DIV) || \
                                             ((BASE) == TMR_DMABase_AR) || \
                                             ((BASE) == TMR_DMABase_RC) || \
                                             ((BASE) == TMR_DMABase_CC1) || \
                                             ((BASE) == TMR_DMABase_CC2) || \
                                             ((BASE) == TMR_DMABase_CC3) || \
                                             ((BASE) == TMR_DMABase_CC4) || \
                                             ((BASE) == TMR_DMABase_BRKDT) || \
                                             ((BASE) == TMR_DMABase_DMAC))
/**
  * @}
  */ 

/** @defgroup TMR_DMA_Burst_Length 
  * @{
  */

#define TMR_DMABurstLength_1Transfer           ((uint16_t)0x0000)
#define TMR_DMABurstLength_2Transfers          ((uint16_t)0x0100)
#define TMR_DMABurstLength_3Transfers          ((uint16_t)0x0200)
#define TMR_DMABurstLength_4Transfers          ((uint16_t)0x0300)
#define TMR_DMABurstLength_5Transfers          ((uint16_t)0x0400)
#define TMR_DMABurstLength_6Transfers          ((uint16_t)0x0500)
#define TMR_DMABurstLength_7Transfers          ((uint16_t)0x0600)
#define TMR_DMABurstLength_8Transfers          ((uint16_t)0x0700)
#define TMR_DMABurstLength_9Transfers          ((uint16_t)0x0800)
#define TMR_DMABurstLength_10Transfers         ((uint16_t)0x0900)
#define TMR_DMABurstLength_11Transfers         ((uint16_t)0x0A00)
#define TMR_DMABurstLength_12Transfers         ((uint16_t)0x0B00)
#define TMR_DMABurstLength_13Transfers         ((uint16_t)0x0C00)
#define TMR_DMABurstLength_14Transfers         ((uint16_t)0x0D00)
#define TMR_DMABurstLength_15Transfers         ((uint16_t)0x0E00)
#define TMR_DMABurstLength_16Transfers         ((uint16_t)0x0F00)
#define TMR_DMABurstLength_17Transfers         ((uint16_t)0x1000)
#define TMR_DMABurstLength_18Transfers         ((uint16_t)0x1100)
#define IS_TMR_DMA_LENGTH(LENGTH)              (((LENGTH) == TMR_DMABurstLength_1Transfer) || \
                                                ((LENGTH) == TMR_DMABurstLength_2Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_3Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_4Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_5Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_6Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_7Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_8Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_9Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_10Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_11Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_12Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_13Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_14Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_15Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_16Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_17Transfers) || \
                                                ((LENGTH) == TMR_DMABurstLength_18Transfers))
/**
  * @}
  */ 

/** @defgroup TMR_DMA_sources 
  * @{
  */

#define TMR_DMA_Update                      ((uint16_t)0x0100)
#define TMR_DMA_CC1                         ((uint16_t)0x0200)
#define TMR_DMA_CC2                         ((uint16_t)0x0400)
#define TMR_DMA_CC3                         ((uint16_t)0x0800)
#define TMR_DMA_CC4                         ((uint16_t)0x1000)
#define TMR_DMA_HALL                        ((uint16_t)0x2000)
#define TMR_DMA_Trigger                     ((uint16_t)0x4000)
#define IS_TMR_DMA_SOURCE(SOURCE)           ((((SOURCE) & (uint16_t)0x80FF) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TMR_External_Trigger_Prescaler 
  * @{
  */

#define TMR_ExtTRGDIV_OFF                  ((uint16_t)0x0000)
#define TMR_ExtTRGDIV_DIV2                 ((uint16_t)0x1000)
#define TMR_ExtTRGDIV_DIV4                 ((uint16_t)0x2000)
#define TMR_ExtTRGDIV_DIV8                 ((uint16_t)0x3000)
#define IS_TMR_EXT_DIV(DIV)                (((DIV) == TMR_ExtTRGDIV_OFF) || \
                                            ((DIV) == TMR_ExtTRGDIV_DIV2) || \
                                            ((DIV) == TMR_ExtTRGDIV_DIV4) || \
                                            ((DIV) == TMR_ExtTRGDIV_DIV8))
/**
  * @}
  */ 

/** @defgroup TMR_Internal_Trigger_Selection 
  * @{
  */

#define TMR_TRGSEL_ITR0                        ((uint16_t)0x0000)
#define TMR_TRGSEL_ITR1                        ((uint16_t)0x0010)
#define TMR_TRGSEL_ITR2                        ((uint16_t)0x0020)
#define TMR_TRGSEL_ITR3                        ((uint16_t)0x0030)
#define TMR_TRGSEL_TI1F_ED                     ((uint16_t)0x0040)
#define TMR_TRGSEL_TI1FP1                      ((uint16_t)0x0050)
#define TMR_TRGSEL_TI2FP2                      ((uint16_t)0x0060)
#define TMR_TRGSEL_ETRF                        ((uint16_t)0x0070)
#define IS_TMR_TRIGGER_SELECTION(SELECTION)    (((SELECTION) == TMR_TRGSEL_ITR0) || \
                                                ((SELECTION) == TMR_TRGSEL_ITR1) || \
                                                ((SELECTION) == TMR_TRGSEL_ITR2) || \
                                                ((SELECTION) == TMR_TRGSEL_ITR3) || \
                                                ((SELECTION) == TMR_TRGSEL_TI1F_ED) || \
                                                ((SELECTION) == TMR_TRGSEL_TI1FP1) || \
                                                ((SELECTION) == TMR_TRGSEL_TI2FP2) || \
                                                ((SELECTION) == TMR_TRGSEL_ETRF))
#define IS_TMR_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TMR_TRGSEL_ITR0) || \
                                                      ((SELECTION) == TMR_TRGSEL_ITR1) || \
                                                      ((SELECTION) == TMR_TRGSEL_ITR2) || \
                                                      ((SELECTION) == TMR_TRGSEL_ITR3))
/**
  * @}
  */ 

/** @defgroup TMR_TIx_External_Clock_Source 
  * @{
  */

#define TMR_TIxExternalCLK1Source_TI1         ((uint16_t)0x0050)
#define TMR_TIxExternalCLK1Source_TI2         ((uint16_t)0x0060)
#define TMR_TIxExternalCLK1Source_TI1ED       ((uint16_t)0x0040)
#define IS_TMR_TIXCLK_SOURCE(SOURCE)          (((SOURCE) == TMR_TIxExternalCLK1Source_TI1) || \
                                               ((SOURCE) == TMR_TIxExternalCLK1Source_TI2) || \
                                               ((SOURCE) == TMR_TIxExternalCLK1Source_TI1ED))
/**
  * @}
  */ 

/** @defgroup TMR_External_Trigger_Polarity 
  * @{
  */ 
#define TMR_ExtTRGPolarity_Inverted         ((uint16_t)0x8000)
#define TMR_ExtTRGPolarity_NonInverted      ((uint16_t)0x0000)
#define IS_TMR_EXT_POLARITY(POLARITY)       (((POLARITY) == TMR_ExtTRGPolarity_Inverted) || \
                                             ((POLARITY) == TMR_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TMR_Prescaler_Reload_Mode 
  * @{
  */

#define TMR_DIVReloadMode_Update           ((uint16_t)0x0000)
#define TMR_DIVReloadMode_Immediate        ((uint16_t)0x0001)
#define IS_TMR_DIV_RELOAD(RELOAD)          (((RELOAD) == TMR_DIVReloadMode_Update) || \
                                            ((RELOAD) == TMR_DIVReloadMode_Immediate))
/**
  * @}
  */ 

/** @defgroup TMR_Forced_Action 
  * @{
  */

#define TMR_ForcedAction_Active            ((uint16_t)0x0050)
#define TMR_ForcedAction_InActive          ((uint16_t)0x0040)
#define IS_TMR_FORCED_ACTION(ACTION)       (((ACTION) == TMR_ForcedAction_Active) || \
                                            ((ACTION) == TMR_ForcedAction_InActive))
/**
  * @}
  */ 

/** @defgroup TMR_Encoder_Mode 
  * @{
  */

#define TMR_EncoderMode_TI1                ((uint16_t)0x0001)
#define TMR_EncoderMode_TI2                ((uint16_t)0x0002)
#define TMR_EncoderMode_TI12               ((uint16_t)0x0003)
#define IS_TMR_ENCODER_MODE(MODE)          (((MODE) == TMR_EncoderMode_TI1) || \
                                            ((MODE) == TMR_EncoderMode_TI2) || \
                                            ((MODE) == TMR_EncoderMode_TI12))
/**
  * @}
  */ 


/** @defgroup TMR_Event_Source 
  * @{
  */

#define TMR_EventSource_Update             ((uint16_t)0x0001)
#define TMR_EventSource_CC1                ((uint16_t)0x0002)
#define TMR_EventSource_CC2                ((uint16_t)0x0004)
#define TMR_EventSource_CC3                ((uint16_t)0x0008)
#define TMR_EventSource_CC4                ((uint16_t)0x0010)
#define TMR_EventSource_HALL               ((uint16_t)0x0020)
#define TMR_EventSource_Trigger            ((uint16_t)0x0040)
#define TMR_EventSource_Break              ((uint16_t)0x0080)
#define IS_TMR_EVENT_SOURCE(SOURCE)        ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */ 

/** @defgroup TMR_Update_Source 
  * @{
  */

#define TMR_UpdateSource_Global            ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TMR_UpdateSource_Regular           ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TMR_UPDATE_SOURCE(SOURCE)       (((SOURCE) == TMR_UpdateSource_Global) || \
                                            ((SOURCE) == TMR_UpdateSource_Regular))
/**
  * @}
  */ 

/** @defgroup TIM_Plus_Mode__State 
  * @{
  */	
	
#define TMR_Plus_Mode_Enable              ((uint16_t)0x0400)	
#define TMR_Plus_Mode_Disable             ((uint16_t)0x0000)	
#define IS_TMR_PLUS_MODE_STATE(STATE) (((STATE) == TMR_Plus_Mode_Enable) || \
                                       ((STATE) == TMR_Plus_Mode_Disable))	
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_Preload_State 
  * @{
  */

#define TMR_OCPreload_Enable               ((uint16_t)0x0008)
#define TMR_OCPreload_Disable              ((uint16_t)0x0000)
#define IS_TMR_OCPRELOAD_STATE(STATE)      (((STATE) == TMR_OCPreload_Enable) || \
                                            ((STATE) == TMR_OCPreload_Disable))
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_Fast_State 
  * @{
  */

#define TMR_OCFast_Enable                  ((uint16_t)0x0004)
#define TMR_OCFast_Disable                 ((uint16_t)0x0000)
#define IS_TMR_OCFAST_STATE(STATE)         (((STATE) == TMR_OCFast_Enable) || \
                                            ((STATE) == TMR_OCFast_Disable))
                                     
/**
  * @}
  */ 

/** @defgroup TMR_Output_Compare_Clear_State 
  * @{
  */

#define TMR_OCClear_Enable                 ((uint16_t)0x0080)
#define TMR_OCClear_Disable                ((uint16_t)0x0000)
#define IS_TMR_OCCLEAR_STATE(STATE)        (((STATE) == TMR_OCClear_Enable) || \
                                            ((STATE) == TMR_OCClear_Disable))
/**
  * @}
  */ 

/** @defgroup TMR_Trigger_Output_Source 
  * @{
  */

#define TMR_TRGOSource_Reset               ((uint16_t)0x0000)
#define TMR_TRGOSource_Enable              ((uint16_t)0x0010)
#define TMR_TRGOSource_Update              ((uint16_t)0x0020)
#define TMR_TRGOSource_OC1                 ((uint16_t)0x0030)
#define TMR_TRGOSource_OC1Ref              ((uint16_t)0x0040)
#define TMR_TRGOSource_OC2Ref              ((uint16_t)0x0050)
#define TMR_TRGOSource_OC3Ref              ((uint16_t)0x0060)
#define TMR_TRGOSource_OC4Ref              ((uint16_t)0x0070)
#define IS_TMR_TRGO_SOURCE(SOURCE)         (((SOURCE) == TMR_TRGOSource_Reset) || \
                                            ((SOURCE) == TMR_TRGOSource_Enable) || \
                                            ((SOURCE) == TMR_TRGOSource_Update) || \
                                            ((SOURCE) == TMR_TRGOSource_OC1) || \
                                            ((SOURCE) == TMR_TRGOSource_OC1Ref) || \
                                            ((SOURCE) == TMR_TRGOSource_OC2Ref) || \
                                            ((SOURCE) == TMR_TRGOSource_OC3Ref) || \
                                            ((SOURCE) == TMR_TRGOSource_OC4Ref))
/**
  * @}
  */ 

/** @defgroup TMR_Slave_Mode 
  * @{
  */

#define TMR_SlaveMode_Reset                ((uint16_t)0x0004)
#define TMR_SlaveMode_Gate                 ((uint16_t)0x0005)
#define TMR_SlaveMode_Trigger              ((uint16_t)0x0006)
#define TMR_SlaveMode_External1            ((uint16_t)0x0007)
#define IS_TMR_SLAVE_MODE(MODE)            (((MODE) == TMR_SlaveMode_Reset) || \
                                            ((MODE) == TMR_SlaveMode_Gate) || \
                                            ((MODE) == TMR_SlaveMode_Trigger) || \
                                            ((MODE) == TMR_SlaveMode_External1))
/**
  * @}
  */ 

/** @defgroup TMR_Master_Slave_Mode 
  * @{
  */

#define TMR_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TMR_MasterSlaveMode_Disable        ((uint16_t)0x0000)
#define IS_TMR_MSMODE_STATE(STATE)         (((STATE) == TMR_MasterSlaveMode_Enable) || \
                                            ((STATE) == TMR_MasterSlaveMode_Disable))
/**
  * @}
  */ 

/** @defgroup TMR_Flags 
  * @{
  */

#define TMR_FLAG_Update                    ((uint16_t)0x0001)
#define TMR_FLAG_CC1                       ((uint16_t)0x0002)
#define TMR_FLAG_CC2                       ((uint16_t)0x0004)
#define TMR_FLAG_CC3                       ((uint16_t)0x0008)
#define TMR_FLAG_CC4                       ((uint16_t)0x0010)
#define TMR_FLAG_HALL                      ((uint16_t)0x0020)
#define TMR_FLAG_Trigger                   ((uint16_t)0x0040)
#define TMR_FLAG_Break                     ((uint16_t)0x0080)
#define TMR_FLAG_C1OF                      ((uint16_t)0x0200)
#define TMR_FLAG_C2OF                      ((uint16_t)0x0400)
#define TMR_FLAG_C3OF                      ((uint16_t)0x0800)
#define TMR_FLAG_C4OF                      ((uint16_t)0x1000)
#define IS_TMR_GET_FLAG(FLAG)              (((FLAG) == TMR_FLAG_Update) || \
                                            ((FLAG) == TMR_FLAG_CC1) || \
                                            ((FLAG) == TMR_FLAG_CC2) || \
                                            ((FLAG) == TMR_FLAG_CC3) || \
                                            ((FLAG) == TMR_FLAG_CC4) || \
                                            ((FLAG) == TMR_FLAG_HALL) || \
                                            ((FLAG) == TMR_FLAG_Trigger) || \
                                            ((FLAG) == TMR_FLAG_Break) || \
                                            ((FLAG) == TMR_FLAG_C1OF) || \
                                            ((FLAG) == TMR_FLAG_C2OF) || \
                                            ((FLAG) == TMR_FLAG_C3OF) || \
                                            ((FLAG) == TMR_FLAG_C4OF))
                               
                               
#define IS_TMR_CLEAR_FLAG(TMR_FLAG)        ((((TMR_FLAG) & (uint16_t)0xE100) == 0x0000) && ((TMR_FLAG) != 0x0000))
/**
  * @}
  */ 

/** @defgroup TMR_Input_Capture_Filer_Value 
  * @{
  */

#define IS_TMR_IC_FILTER(ICFILTER)         ((ICFILTER) <= 0xF) 
/**
  * @}
  */ 

/** @defgroup TMR_External_Trigger_Filter 
  * @{
  */

#define IS_TMR_EXT_FILTER(EXTFILTER)      ((EXTFILTER) <= 0xF)
/**
  * @}
  */ 

/** @defgroup TMR_Legacy 
  * @{
  */

#define TMR_DMABurstLength_1Byte           TMR_DMABurstLength_1Transfer
#define TMR_DMABurstLength_2Bytes          TMR_DMABurstLength_2Transfers
#define TMR_DMABurstLength_3Bytes          TMR_DMABurstLength_3Transfers
#define TMR_DMABurstLength_4Bytes          TMR_DMABurstLength_4Transfers
#define TMR_DMABurstLength_5Bytes          TMR_DMABurstLength_5Transfers
#define TMR_DMABurstLength_6Bytes          TMR_DMABurstLength_6Transfers
#define TMR_DMABurstLength_7Bytes          TMR_DMABurstLength_7Transfers
#define TMR_DMABurstLength_8Bytes          TMR_DMABurstLength_8Transfers
#define TMR_DMABurstLength_9Bytes          TMR_DMABurstLength_9Transfers
#define TMR_DMABurstLength_10Bytes         TMR_DMABurstLength_10Transfers
#define TMR_DMABurstLength_11Bytes         TMR_DMABurstLength_11Transfers
#define TMR_DMABurstLength_12Bytes         TMR_DMABurstLength_12Transfers
#define TMR_DMABurstLength_13Bytes         TMR_DMABurstLength_13Transfers
#define TMR_DMABurstLength_14Bytes         TMR_DMABurstLength_14Transfers
#define TMR_DMABurstLength_15Bytes         TMR_DMABurstLength_15Transfers
#define TMR_DMABurstLength_16Bytes         TMR_DMABurstLength_16Transfers
#define TMR_DMABurstLength_17Bytes         TMR_DMABurstLength_17Transfers
#define TMR_DMABurstLength_18Bytes         TMR_DMABurstLength_18Transfers
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup TMR_Exported_Macros
  * @{
  */

/**
  * @}
  */ 

/** @defgroup TMR_Exported_Functions
  * @{
  */

void TMR_Reset(TMR_Type* TMRx);
void TMR_TimeBaseInit(TMR_Type* TMRx, TMR_TimerBaseInitType* TMR_TimeBaseInitStruct);
void TMR_OC1Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_OC2Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_OC3Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_OC4Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct);
void TMR_ICInit(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct);
void TMR_PWMIConfig(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct);
void TMR_BRKDTConfig(TMR_Type* TMRx, TMR_BRKDTInitType *TMR_BDTRInitStruct);
void TMR_TimeBaseStructInit(TMR_TimerBaseInitType* TMR_TimeBaseInitStruct);
void TMR_OCStructInit(TMR_OCInitType* TMR_OCInitStruct);
void TMR_ICStructInit(TMR_ICInitType* TMR_ICInitStruct);
void TMR_BRKDTStructInit(TMR_BRKDTInitType* TMR_BDTRInitStruct);
void TMR_Cmd(TMR_Type* TMRx, FunctionalState NewState);
void TMR_CtrlPWMOutputs(TMR_Type* TMRx, FunctionalState NewState);
void TMR_INTConfig(TMR_Type* TMRx, uint16_t TMR_INT, FunctionalState NewState);
void TMR_GenerateEvent(TMR_Type* TMRx, uint16_t TMR_EventSource);
void TMR_DMAConfig(TMR_Type* TMRx, uint16_t TMR_DMABase, uint16_t TMR_DMABurstLength);
void TMR_DMACmd(TMR_Type* TMRx, uint16_t TMR_DMASource, FunctionalState NewState);
void TMR_InternalClockConfig(TMR_Type* TMRx);
void TMR_ITRxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource);
void TMR_TIxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_TIxExternalCLKSource,
                                uint16_t TMR_ICPolarity, uint16_t ICFilter);
void TMR_ETRClockMode1Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity,
                             uint16_t ExtTRGFilter);
void TMR_ETRClockMode2Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, 
                             uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter);
void TMR_ETRConfig(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity,
                   uint16_t ExtTRGFilter);
void TMR_DIVConfig(TMR_Type* TMRx, uint16_t Prescaler, uint16_t TMR_PSCReloadMode);
void TMR_CounterModeConfig(TMR_Type* TMRx, uint16_t TMR_CounterMode);
void TMR_SelectInputTrigger(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource);
void TMR_EncoderInterfaceConfig(TMR_Type* TMRx, uint16_t TMR_EncoderMode,
                                uint16_t TMR_IC1Polarity, uint16_t TMR_IC2Polarity);
void TMR_ForcedOC1Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ForcedOC2Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ForcedOC3Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ForcedOC4Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction);
void TMR_ARPreloadConfig(TMR_Type* TMRx, FunctionalState NewState);
void TMR_SelectHALL(TMR_Type* TMRx, FunctionalState NewState);
void TMR_SelectCCDMA(TMR_Type* TMRx, FunctionalState NewState);
void TMR_CCPreloadControl(TMR_Type* TMRx, FunctionalState NewState);
void TMR_OC1PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC2PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC3PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC4PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload);
void TMR_OC1FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_OC2FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_OC3FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_OC4FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast);
void TMR_ClearOC1Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_ClearOC2Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_ClearOC3Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_ClearOC4Ref(TMR_Type* TMRx, uint16_t TMR_OCClear);
void TMR_OC1PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_OC1NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity);
void TMR_OC2PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_OC2NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity);
void TMR_OC3PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_OC3NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity);
void TMR_OC4PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity);
void TMR_CCxCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCx);
void TMR_CCxNCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCxN);
void TMR_SelectOCxM(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_OCMode);
void TMR_UpdateDisableConfig(TMR_Type* TMRx, FunctionalState NewState);
void TMR_UpdateRequestConfig(TMR_Type* TMRx, uint16_t TMR_UpdateSource);
void TMR_SelectHallSensor(TMR_Type* TMRx, FunctionalState NewState);
void TMR_SelectOnePulseMode(TMR_Type* TMRx, uint16_t TMR_OPMode);
void TMR_SelectPlusMode(TMR_Type* TIMx, uint16_t  TIMX_PLUS_MODE_STATE);
void TMR_SelectOutputTrigger(TMR_Type* TMRx, uint16_t TMR_TRGOSource);
void TMR_SelectSlaveMode(TMR_Type* TMRx, uint16_t TMR_SlaveMode);
void TMR_SelectMasterSlaveMode(TMR_Type* TMRx, uint16_t TMR_MasterSlaveMode);
void TMR_SetCounter(TMR_Type* TMRx, uint32_t Counter);
void TMR_SetAutoreload(TMR_Type* TMRx, uint32_t Autoreload);
void TMR_SetCompare1(TMR_Type* TMRx, uint32_t Compare1);
void TMR_SetCompare2(TMR_Type* TMRx, uint32_t Compare2);
void TMR_SetCompare3(TMR_Type* TMRx, uint32_t Compare3);
void TMR_SetCompare4(TMR_Type* TMRx, uint32_t Compare4);
void TMR_SetIC1DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetIC2DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetIC3DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetIC4DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC);
void TMR_SetClockDivision(TMR_Type* TMRx, uint16_t TMR_CKD);
uint32_t TMR_GetCapture1(TMR_Type* TMRx);
uint32_t TMR_GetCapture2(TMR_Type* TMRx);
uint32_t TMR_GetCapture3(TMR_Type* TMRx);
uint32_t TMR_GetCapture4(TMR_Type* TMRx);
uint32_t TMR_GetCounter(TMR_Type* TMRx);
uint16_t TMR_GetDIV(TMR_Type* TMRx);
FlagStatus TMR_GetFlagStatus(TMR_Type* TMRx, uint16_t TMR_FLAG);
void TMR_ClearFlag(TMR_Type* TMRx, uint16_t TMR_FLAG);
ITStatus TMR_GetINTStatus(TMR_Type* TMRx, uint16_t TMR_INT);
void TMR_ClearITPendingBit(TMR_Type* TMRx, uint16_t TMR_INT);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_TIM_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */


