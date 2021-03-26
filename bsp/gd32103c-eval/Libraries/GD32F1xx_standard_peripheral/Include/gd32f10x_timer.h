/**
 ******************************************************************************
  * @brief   TIMER header file of the firmware library
 ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_TIMER_H
#define __GD32F10X_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/** @defgroup TIMER_Exported_Types
  * @{
  */

/**
  * @brief  Timer base init structure
  */
typedef struct {
    uint16_t TIMER_Prescaler;                       /*!< Clock prescaler value . */
    uint16_t TIMER_CounterMode;                     /*!< Counter mode ,
                                                         a value of @ref TIMER_Counter_Mode. */
    uint32_t TIMER_Period;                          /*!< Value to be loaded into the active CARL at the next update event. */
    uint16_t TIMER_ClockDivision;                   /*!< Clock division ,
                                                         a value of @ref TIMER_Clock_Division_CDIV. */
    uint8_t  TIMER_RepetitionCounter;               /*!< Repetition counter value , only valid in TIMER1/8. */
} TIMER_BaseInitPara;

/**
  * @brief  Timer output compare init structure
  */
typedef struct {
    uint16_t TIMER_OCMode;                          /*!< Out mode,
                                                         a value of @ref TIMER_Output_Compare_and_PWM_modes */

    uint16_t TIMER_OutputState;                     /*!< Output Compare state ,
                                                         a value of @ref TIMER_Output_Compare_State */
    uint16_t TIMER_OutputNState;                    /*!< Complementary Output Compare state ,
                                                         a value of @ref TIMER_Output_Compare_N_State,
                                                         valid only for TIMER1. */
    uint32_t TIMER_Pulse;                           /*!< Pulse value to be loaded into the CHCCx. */
    uint16_t TIMER_OCPolarity;                      /*!< Output polarity ,
                                                         a value of @ref TIMER_Output_Compare_Polarity */
    uint16_t TIMER_OCNPolarity;                     /*!< Complementary output polarity ,
                                                         a value of @ref TIMER_Output_Compare_N_Polarity */
    uint16_t TIMER_OCIdleState;                     /*!< TIM Output Compare pin state during Idle state ,
                                                         a value of @ref TIMER_Output_Compare_Idle_State,
                                                         valid only for TIMER1. */
    uint16_t TIMER_OCNIdleState;                    /*!< TIM Complementary Output Compare pin state during Idle state.
                                                         a value of @ref TIMER_Output_Compare_N_Idle_State ,
                                                         valid only for TIMER1. */
} TIMER_OCInitPara;

/**
  * @brief   Timer input capture init structure
  */
typedef struct {
    uint16_t TIMER_CH;                              /*!< TIMER channel ,
                                                         a value of @ref TIMER_Channel */
    uint16_t TIMER_ICPolarity;                      /*!< Active edge of the input signal ,
                                                         a value of @ref TIMER_Input_Capture_Polarity */
    uint16_t TIMER_ICSelection;                     /*!< Input Selection ,
                                                         a value of @ref TIMER_Input_Capture_Selection */
    uint16_t TIMER_ICPrescaler;                     /*!< Input Capture Prescaler ,
                                                         a value of @ref TIMER_Input_Capture_Prescaler */
    uint16_t TIMER_ICFilter;                        /*!< Input capture filter ,
                                                         a number between 0x0 and 0xF */
} TIMER_ICInitPara;

/**
  * @brief   Timer break and dead-time structure , valid only for TIMER1.
  */
typedef struct {
    uint16_t TIMER_ROSState;                        /*!< Off-State selection used in Run mode ,
                                                             a value of @ref TIMER_ROS_Off_State_Selection_for_Run_mode_State */
    uint16_t TIMER_IOSState;                        /*!< Off-State used in Idle state ,
                                                             a value of @ref TIMER_IOS_Off_State_Selection_for_Idle_mode_State */
    uint16_t TIMER_LOCKLevel;                        /*!< LOCK level ,
                                                             a value of @ref TIMER_Lock_level */
    uint16_t TIMER_DeadTime;                        /*!< delay time between the switching off and on of the outputs.
                                                             a number between 0x00 and 0xFF  */
    uint16_t TIMER_Break;                            /*!< Break input is enabled or disable,
                                                             a value of @ref TIMER_Break_Input_State */
    uint16_t TIMER_BreakPolarity;                    /*!< Break Input pin polarity ,
                                                             a value of @ref TIMER_Break_Input_Polarity */
    uint16_t TIMER_OutAuto;                         /*!< Automatic Output is enabled or disable.
                                                             a value of @ref TIMER_OAE_Bit_State */
} TIMER_BKDTInitPara;

/**
  * @}
  */

/** @defgroup TIMER_Exported_Constants
  * @{
  */

/** @defgroup TIMER_Output_Compare_and_PWM_modes
  * @{
  */
#define TIMER_OC_MODE_TIMING                      ((uint16_t)0x0000)
#define TIMER_OC_MODE_ACTIVE                      ((uint16_t)0x0010)
#define TIMER_OC_MODE_INACTIVE                    ((uint16_t)0x0020)
#define TIMER_OC_MODE_TOGGLE                      ((uint16_t)0x0030)
#define TIMER_OC_MODE_PWM1                        ((uint16_t)0x0060)
#define TIMER_OC_MODE_PWM2                        ((uint16_t)0x0070)

/**
  * @}
  */

/** @defgroup TIMER_Single_Pulse_Mode
  * @{
  */
#define TIMER_SP_MODE_SINGLE                      ((uint16_t)0x0008)
#define TIMER_SP_MODE_REPETITIVE                  ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Channel
  * @{
  */
#define TIMER_CH_1                                ((uint16_t)0x0000)
#define TIMER_CH_2                                ((uint16_t)0x0004)
#define TIMER_CH_3                                ((uint16_t)0x0008)
#define TIMER_CH_4                                ((uint16_t)0x000C)

/**
  * @}
  */

/** @defgroup TIMER_Clock_Division_CDIV
  * @{
  */
#define TIMER_CDIV_DIV1                           ((uint16_t)0x0000)
#define TIMER_CDIV_DIV2                           ((uint16_t)0x0100)
#define TIMER_CDIV_DIV4                           ((uint16_t)0x0200)

/**
  * @}
  */

/** @defgroup TIMER_Counter_Mode
  * @{
  */
#define TIMER_COUNTER_UP                          ((uint16_t)0x0000)
#define TIMER_COUNTER_DOWN                        ((uint16_t)0x0010)
#define TIMER_COUNTER_CENTER_ALIGNED1             ((uint16_t)0x0020)
#define TIMER_COUNTER_CENTER_ALIGNED2             ((uint16_t)0x0040)
#define TIMER_COUNTER_CENTER_ALIGNED3             ((uint16_t)0x0060)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_Polarity
  * @{
  */
#define TIMER_OC_POLARITY_HIGH                    ((uint16_t)0x0000)
#define TIMER_OC_POLARITY_LOW                     ((uint16_t)0x0002)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_N_Polarity
  * @{
  */
#define TIMER_OCN_POLARITY_HIGH                   ((uint16_t)0x0000)
#define TIMER_OCN_POLARITY_LOW                    ((uint16_t)0x0008)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_State
  * @{
  */
#define TIMER_OUTPUT_STATE_DISABLE                ((uint16_t)0x0000)
#define TIMER_OUTPUT_STATE_ENABLE                 ((uint16_t)0x0001)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_N_State
  * @{
  */
#define TIMER_OUTPUTN_STATE_DISABLE               ((uint16_t)0x0000)
#define TIMER_OUTPUTN_STATE_ENABLE                ((uint16_t)0x0004)

/**
  * @}
  */

/** @defgroup TIMER_Capture_Compare_State
  * @{
  */
#define TIMER_CCX_ENABLE                          ((uint16_t)0x0001)
#define TIMER_CCX_DISABLE                         ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Capture_Compare_N_State
  * @{
  */
#define TIMER_CCXN_ENABLE                         ((uint16_t)0x0004)
#define TIMER_CCXN_DISABLE                        ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Break_Input_State
  * @{
  */
#define TIMER_BREAK_ENABLE                        ((uint16_t)0x1000)
#define TIMER_BREAK_DISABLE                       ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Break_Input_Polarity
  * @{
  */
#define TIMER_BREAK_POLARITY_LOW                  ((uint16_t)0x0000)
#define TIMER_BREAK_POLARITY_HIGH                 ((uint16_t)0x2000)

/**
  * @}
  */

/** @defgroup TIMER_OAE_Bit_State
  * @{
  */
#define TIMER_OUTAUTO_ENABLE                      ((uint16_t)0x4000)
#define TIMER_OUTAUTO_DISABLE                     ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Lock_level
  * @{
  */
#define TIMER_LOCK_LEVEL_OFF                      ((uint16_t)0x0000)
#define TIMER_LOCK_LEVEL_1                        ((uint16_t)0x0100)
#define TIMER_LOCK_LEVEL_2                        ((uint16_t)0x0200)
#define TIMER_LOCK_LEVEL_3                        ((uint16_t)0x0300)

/**
  * @}
  */

/** @defgroup TIMER_IOS_Off_State_Selection_for_Idle_mode_State
  * @{
  */
#define TIMER_IOS_STATE_ENABLE                    ((uint16_t)0x0400)
#define TIMER_IOS_STATE_DISABLE                   ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_ROS_Off_State_Selection_for_Run_mode_State
  * @{
  */
#define TIMER_ROS_STATE_ENABLE                    ((uint16_t)0x0800)
#define TIMER_ROS_STATE_DISABLE                   ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_Idle_State
  * @{
  */
#define TIMER_OC_IDLE_STATE_SET                   ((uint16_t)0x0100)
#define TIMER_OC_IDLE_STATE_RESET                 ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_N_Idle_State
  * @{
  */
#define TIMER_OCN_IDLE_STATE_SET                  ((uint16_t)0x0200)
#define TIMER_OCN_IDLE_STATE_RESET                ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Input_Capture_Polarity
  * @{
  */
#define  TIMER_IC_POLARITY_RISING                 ((uint16_t)0x0000)
#define  TIMER_IC_POLARITY_FALLING                ((uint16_t)0x0002)

/**
  * @}
  */

/** @defgroup TIMER_Input_Capture_Selection
  * @{
  */
#define TIMER_IC_SELECTION_DIRECTTI               ((uint16_t)0x0001)
#define TIMER_IC_SELECTION_INDIRECTTI             ((uint16_t)0x0002)
#define TIMER_IC_SELECTION_TRC                    ((uint16_t)0x0003)

/**
  * @}
  */

/** @defgroup TIMER_Input_Capture_Prescaler
  * @{
  */
#define TIMER_IC_PSC_DIV1                         ((uint16_t)0x0000)
#define TIMER_IC_PSC_DIV2                         ((uint16_t)0x0004)
#define TIMER_IC_PSC_DIV4                         ((uint16_t)0x0008)
#define TIMER_IC_PSC_DIV8                         ((uint16_t)0x000C)

/**
  * @}
  */

/** @defgroup TIMER_interrupt_sources
  * @{
  */
#define TIMER_INT_UPDATE                          ((uint16_t)0x0001)
#define TIMER_INT_CH1                             ((uint16_t)0x0002)
#define TIMER_INT_CH2                             ((uint16_t)0x0004)
#define TIMER_INT_CH3                             ((uint16_t)0x0008)
#define TIMER_INT_CH4                             ((uint16_t)0x0010)
#define TIMER_INT_CCUG                            ((uint16_t)0x0020)
#define TIMER_INT_TRIGGER                         ((uint16_t)0x0040)
#define TIMER_INT_BREAK                           ((uint16_t)0x0080)

/**
  * @}
  */

/** @defgroup TIMER_DMA_Base_address
  * @{
  */
#define TIMER_DMA_BASE_ADDR_CTLR1                 ((uint16_t)0x0000)
#define TIMER_DMA_BASE_ADDR_CTLR2                 ((uint16_t)0x0001)
#define TIMER_DMA_BASE_ADDR_SMC                   ((uint16_t)0x0002)
#define TIMER_DMA_BASE_ADDR_DIE                   ((uint16_t)0x0003)
#define TIMER_DMA_BASE_ADDR_STR                   ((uint16_t)0x0004)
#define TIMER_DMA_BASE_ADDR_EVG                   ((uint16_t)0x0005)
#define TIMER_DMA_BASE_ADDR_CHCTLR1               ((uint16_t)0x0006)
#define TIMER_DMA_BASE_ADDR_CHCTLR2               ((uint16_t)0x0007)
#define TIMER_DMA_BASE_ADDR_CHE                   ((uint16_t)0x0008)
#define TIMER_DMA_BASE_ADDR_CNT                   ((uint16_t)0x0009)
#define TIMER_DMA_BASE_ADDR_PSC                   ((uint16_t)0x000A)
#define TIMER_DMA_BASE_ADDR_CARL                  ((uint16_t)0x000B)
#define TIMER_DMA_BASE_ADDR_CREP                  ((uint16_t)0x000C)
#define TIMER_DMA_BASE_ADDR_CHCC1                 ((uint16_t)0x000D)
#define TIMER_DMA_BASE_ADDR_CHCC2                 ((uint16_t)0x000E)
#define TIMER_DMA_BASE_ADDR_CHCC3                 ((uint16_t)0x000F)
#define TIMER_DMA_BASE_ADDR_CHCC4                 ((uint16_t)0x0010)
#define TIMER_DMA_BASE_ADDR_BKDT                  ((uint16_t)0x0011)
#define TIMER_DMA_BASE_ADDR_DCTLR                 ((uint16_t)0x0012)

/**
  * @}
  */

/** @defgroup TIMER_DMA_Burst_Transfer_Length
  * @{
  */
#define TIMER_DMA_BURST_1TRANSFER                 ((uint16_t)0x0000)
#define TIMER_DMA_BURST_2TRANSFERS                ((uint16_t)0x0100)
#define TIMER_DMA_BURST_3TRANSFERS                ((uint16_t)0x0200)
#define TIMER_DMA_BURST_4TRANSFERS                ((uint16_t)0x0300)
#define TIMER_DMA_BURST_5TRANSFERS                ((uint16_t)0x0400)
#define TIMER_DMA_BURST_6TRANSFERS                ((uint16_t)0x0500)
#define TIMER_DMA_BURST_7TRANSFERS                ((uint16_t)0x0600)
#define TIMER_DMA_BURST_8TRANSFERS                ((uint16_t)0x0700)
#define TIMER_DMA_BURST_9TRANSFERS                ((uint16_t)0x0800)
#define TIMER_DMA_BURST_10TRANSFERS               ((uint16_t)0x0900)
#define TIMER_DMA_BURST_11TRANSFERS               ((uint16_t)0x0A00)
#define TIMER_DMA_BURST_12TRANSFERS               ((uint16_t)0x0B00)
#define TIMER_DMA_BURST_13TRANSFERS               ((uint16_t)0x0C00)
#define TIMER_DMA_BURST_14TRANSFERS               ((uint16_t)0x0D00)
#define TIMER_DMA_BURST_15TRANSFERS               ((uint16_t)0x0E00)
#define TIMER_DMA_BURST_16TRANSFERS               ((uint16_t)0x0F00)
#define TIMER_DMA_BURST_17TRANSFERS               ((uint16_t)0x1000)
#define TIMER_DMA_BURST_18TRANSFERS               ((uint16_t)0x1100)

/**
  * @}
  */

/** @defgroup TIMER_DMA_sources
  * @{
  */
#define TIMER_DMA_UPDATE                          ((uint16_t)0x0100)
#define TIMER_DMA_CH1                             ((uint16_t)0x0200)
#define TIMER_DMA_CH2                             ((uint16_t)0x0400)
#define TIMER_DMA_CH3                             ((uint16_t)0x0800)
#define TIMER_DMA_CH4                             ((uint16_t)0x1000)
#define TIMER_DMA_COM                             ((uint16_t)0x2000)
#define TIMER_DMA_TRIGGER                         ((uint16_t)0x4000)

/**
  * @}
  */

/** @defgroup TIMER_External_Trigger_Prescaler
  * @{
  */
#define TIMER_EXT_TRI_PSC_OFF                     ((uint16_t)0x0000)
#define TIMER_EXT_TRI_PSC_DIV2                    ((uint16_t)0x1000)
#define TIMER_EXT_TRI_PSC_DIV4                    ((uint16_t)0x2000)
#define TIMER_EXT_TRI_PSC_DIV8                    ((uint16_t)0x3000)

/**
  * @}
  */

/** @defgroup TIMER_Internal_Trigger_Selection
  * @{
  */
#define TIMER_TS_ITR0                             ((uint16_t)0x0000)
#define TIMER_TS_ITR1                             ((uint16_t)0x0010)
#define TIMER_TS_ITR2                             ((uint16_t)0x0020)
#define TIMER_TS_ITR3                             ((uint16_t)0x0030)
#define TIMER_TS_TI1F_ED                          ((uint16_t)0x0040)
#define TIMER_TS_TI1FP1                           ((uint16_t)0x0050)
#define TIMER_TS_TI2FP2                           ((uint16_t)0x0060)
#define TIMER_TS_ETRF                             ((uint16_t)0x0070)

/**
  * @}
  */

/** @defgroup TIMER_TIx_External_Clock_Source
  * @{
  */
#define TIMER_TIX_EXCLK1_SRC_TI1                  ((uint16_t)0x0050)
#define TIMER_TIX_EXCLK1_SRC_TI2                  ((uint16_t)0x0060)
#define TIMER_TIX_EXCLK1_SRC_TI1ED                ((uint16_t)0x0040)

/**
  * @}
  */

/** @defgroup TIMER_External_Trigger_Polarity
  * @{
  */
#define TIMER_EXT_TRI_POLARITY_INVERTED           ((uint16_t)0x8000)
#define TIMER_EXT_TRI_POLARITY_NONINVERTED        ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Prescaler_Reload_Mode
  * @{
  */
#define TIMER_PSC_RELOAD_UPDATE                   ((uint16_t)0x0000)
#define TIMER_PSC_RELOAD_NOW                      ((uint16_t)0x0001)

/**
  * @}
  */

/** @defgroup TIMER_Forced_Output
  * @{
  */
#define TIMER_FORCED_HIGH                         ((uint16_t)0x0050)
#define TIMER_FORCED_LOW                          ((uint16_t)0x0040)

/**
  * @}
  */

/** @defgroup TIMER_Encoder_Mode
  * @{
  */
#define TIMER_ENCODER_MODE_TI1                    ((uint16_t)0x0001)
#define TIMER_ENCODER_MODE_TI2                    ((uint16_t)0x0002)
#define TIMER_ENCODER_MODE_TI12                   ((uint16_t)0x0003)

/**
  * @}
  */

/** @defgroup TIMER_Event_Source
  * @{
  */
#define TIMER_EVENT_SRC_UPDATE                    ((uint16_t)0x0001)
#define TIMER_EVENT_SRC_CH1                       ((uint16_t)0x0002)
#define TIMER_EVENT_SRC_CH2                       ((uint16_t)0x0004)
#define TIMER_EVENT_SRC_CH3                       ((uint16_t)0x0008)
#define TIMER_EVENT_SRC_CH4                       ((uint16_t)0x0010)
#define TIMER_EVENT_SRC_COM                       ((uint16_t)0x0020)
#define TIMER_EVENT_SRC_TRIGGER                   ((uint16_t)0x0040)
#define TIMER_EVENT_SRC_BREAK                     ((uint16_t)0x0080)

/**
  * @}
  */

/** @defgroup TIMER_Update_Source
  * @{
  */
#define TIMER_UPDATE_SRC_GLOBAL                   ((uint16_t)0x0000)
#define TIMER_UPDATE_SRC_REGULAR                  ((uint16_t)0x0001)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_Preload_State
  * @{
  */
#define TIMER_OC_PRELOAD_ENABLE                   ((uint16_t)0x0008)
#define TIMER_OC_PRELOAD_DISABLE                  ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_Fast_State
  * @{
  */
#define TIMER_OC_FAST_ENABLE                      ((uint16_t)0x0004)
#define TIMER_OC_FAST_DISABLE                     ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Output_Compare_Clear_State
  * @{
  */
#define TIMER_OC_CLEAR_ENABLE                     ((uint16_t)0x0080)
#define TIMER_OC_CLEAR_DISABLE                    ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Trigger_Output_Source
  * @{
  */
#define TIMER_TRI_OUT_SRC_RESET                   ((uint16_t)0x0000)
#define TIMER_TRI_OUT_SRC_ENABLE                  ((uint16_t)0x0010)
#define TIMER_TRI_OUT_SRC_UPDATE                  ((uint16_t)0x0020)
#define TIMER_TRI_OUT_SRC_OC1                     ((uint16_t)0x0030)
#define TIMER_TRI_OUT_SRC_OC1REF                  ((uint16_t)0x0040)
#define TIMER_TRI_OUT_SRC_OC2REF                  ((uint16_t)0x0050)
#define TIMER_TRI_OUT_SRC_OC3REF                  ((uint16_t)0x0060)
#define TIMER_TRI_OUT_SRC_OC4REF                  ((uint16_t)0x0070)

/**
  * @}
  */

/** @defgroup TIMER_Slave_Mode
  * @{
  */
#define TIMER_SLAVE_MODE_RESET                    ((uint16_t)0x0004)
#define TIMER_SLAVE_MODE_GATED                    ((uint16_t)0x0005)
#define TIMER_SLAVE_MODE_TRIGGER                  ((uint16_t)0x0006)
#define TIMER_SLAVE_MODE_EXTERNAL1                ((uint16_t)0x0007)

/**
  * @}
  */

/** @defgroup TIMER_Master_Slave_Mode
  * @{
  */
#define TIMER_MASTER_SLAVE_MODE_ENABLE            ((uint16_t)0x0080)
#define TIMER_MASTER_SLAVE_MODE_DISABLE           ((uint16_t)0x0000)

/**
  * @}
  */

/** @defgroup TIMER_Flags
  * @{
  */
#define TIMER_FLAG_UPDATE                         ((uint16_t)0x0001)
#define TIMER_FLAG_CH1                            ((uint16_t)0x0002)
#define TIMER_FLAG_CH2                            ((uint16_t)0x0004)
#define TIMER_FLAG_CH3                            ((uint16_t)0x0008)
#define TIMER_FLAG_CH4                            ((uint16_t)0x0010)
#define TIMER_FLAG_COM                            ((uint16_t)0x0020)
#define TIMER_FLAG_TRIGGER                        ((uint16_t)0x0040)
#define TIMER_FLAG_BREAK                          ((uint16_t)0x0080)
#define TIMER_FLAG_CH1OF                          ((uint16_t)0x0200)
#define TIMER_FLAG_CH2OF                          ((uint16_t)0x0400)
#define TIMER_FLAG_CH3OF                          ((uint16_t)0x0800)
#define TIMER_FLAG_CH4OF                          ((uint16_t)0x1000)

/**
  * @}
  */


/**
  * @}
  */


/** @defgroup TIMER_Exported_Functions
  * @{
  */
/* TimeBase management ********************************************************/
void TIMER_DeInit(TIMER_TypeDef *TIMERx);
void TIMER_BaseInit(TIMER_TypeDef *TIMERx, TIMER_BaseInitPara *TIMER_Init);
void TIMER_BaseStructInit(TIMER_BaseInitPara *TIMER_Init);
void TIMER_PrescalerConfig(TIMER_TypeDef *TIMERx, uint16_t Prescaler, uint16_t TIMER_PSCReloadMode);
void TIMER_CounterMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_CounterMode);
void TIMER_SetCounter(TIMER_TypeDef *TIMERx, uint32_t Counter);
void TIMER_SetAutoreload(TIMER_TypeDef *TIMERx, uint32_t AutoReloadValue);
uint32_t TIMER_GetCounter(TIMER_TypeDef *TIMERx);
uint16_t TIMER_GetPrescaler(TIMER_TypeDef *TIMERx);
void TIMER_UpdateDisableConfig(TIMER_TypeDef *TIMERx, TypeState NewValue);
void TIMER_UpdateRequestConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_UpdateSrc);
void TIMER_CARLPreloadConfig(TIMER_TypeDef *TIMERx, TypeState NewValue);
void TIMER_SinglePulseMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_SPMode);
void TIMER_SetClockDivision(TIMER_TypeDef *TIMERx, uint16_t TIMER_CDIV);
void TIMER_Enable(TIMER_TypeDef *TIMERx, TypeState NewValue);

/* Advanced timer features*******************/
void TIMER_BKDTConfig(TIMER_TypeDef *TIMERx, TIMER_BKDTInitPara *TIMER_BKDTInit);
void TIMER_BKDTStructInit(TIMER_BKDTInitPara *TIMER_BKDTInit);
void TIMER_CtrlPWMOutputs(TIMER_TypeDef *TIMERx, TypeState NewValue);

/* Output Compare management **************************************************/
void TIMER_OC1_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit);
void TIMER_OC2_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit);
void TIMER_OC3_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit);
void TIMER_OC4_Init(TIMER_TypeDef *TIMERx, TIMER_OCInitPara *TIMER_OCInit);
void TIMER_OCStructInit(TIMER_OCInitPara *TIMER_OCInit);
void TIMER_OCxModeConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_Ch, uint16_t TIMER_OCMode);
void TIMER_Compare1Config(TIMER_TypeDef *TIMERx, uint32_t CompValue1);
void TIMER_Compare2Config(TIMER_TypeDef *TIMERx, uint32_t CompValue2);
void TIMER_Compare3Config(TIMER_TypeDef *TIMERx, uint32_t CompValue3);
void TIMER_Compare4Config(TIMER_TypeDef *TIMERx, uint32_t CompValue4);
void TIMER_Forced_OC1(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced);
void TIMER_Forced_OC2(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced);
void TIMER_Forced_OC3(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced);
void TIMER_Forced_OC4(TIMER_TypeDef *TIMERx, uint16_t TIMER_Forced);
void TIMER_CC_PreloadControl(TIMER_TypeDef *TIMERx, TypeState NewValue);
void TIMER_OC1_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload);
void TIMER_OC2_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload);
void TIMER_OC3_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload);
void TIMER_OC4_Preload(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPreload);
void TIMER_OC1_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast);
void TIMER_OC2_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast);
void TIMER_OC3_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast);
void TIMER_OC4_FastConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCFast);
void TIMER_OC1_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear);
void TIMER_OC2_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear);
void TIMER_OC3_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear);
void TIMER_OC4_RefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCClear);
void TIMER_OC1_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity);
void TIMER_OC1N_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCNPolarity);
void TIMER_OC2_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity);
void TIMER_OC2N_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCNPolarity);
void TIMER_OC3_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity);
void TIMER_OC3N_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCNPolarity);
void TIMER_OC4_Polarity(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCPolarity);
void TIMER_SelectOCRefClear(TIMER_TypeDef *TIMERx, uint16_t TIMER_OCRef_Clear);
void TIMER_CCxCmd(TIMER_TypeDef *TIMERx, uint16_t TIMER_Ch, uint16_t TIMER_CCx);
void TIMER_CCxNCmd(TIMER_TypeDef *TIMERx, uint16_t TIMER_Ch, uint16_t TIMER_CCxN);
void TIMER_SelectCOM(TIMER_TypeDef *TIMERx, TypeState NewValue);

/* Input Capture management ***************************************************/
void TIMER_ICInit(TIMER_TypeDef *TIMERx, TIMER_ICInitPara *TIMER_ICInit);
void TIMER_ICStructInit(TIMER_ICInitPara *TIMER_ICInit);
void TIMER_PWMCaptureConfig(TIMER_TypeDef *TIMERx, TIMER_ICInitPara *TIMER_ICInit);
uint32_t TIMER_GetCapture1(TIMER_TypeDef *TIMERx);
uint32_t TIMER_GetCapture2(TIMER_TypeDef *TIMERx);
uint32_t TIMER_GetCapture3(TIMER_TypeDef *TIMERx);
uint32_t TIMER_GetCapture4(TIMER_TypeDef *TIMERx);
void TIMER_Set_IC1_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC);
void TIMER_Set_IC2_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC);
void TIMER_Set_IC3_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC);
void TIMER_Set_IC4_Prescaler(TIMER_TypeDef *TIMERx, uint16_t TIMER_ICPSC);

/* Interrupts, DMA and flags management ***************************************/
void TIMER_INTConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_INT, TypeState NewValue);
void TIMER_GenerateEvent(TIMER_TypeDef *TIMERx, uint16_t TIMER_EventSrc);
TypeState TIMER_GetBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_FLAG);
void TIMER_ClearBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_FLAG);
TypeState TIMER_GetIntBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_INT);
void TIMER_ClearIntBitState(TIMER_TypeDef *TIMERx, uint16_t TIMER_INT);
void TIMER_DMAConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_DMABase, uint16_t TIMER_DMABurstLength);
void TIMER_DMACmd(TIMER_TypeDef *TIMERx, uint16_t TIMER_DMASrc, TypeState NewValue);
void TIMER_CC_DMA(TIMER_TypeDef *TIMERx, TypeState NewValue);

/* Clocks management **********************************************************/
void TIMER_InternalClockConfig(TIMER_TypeDef *TIMERx);
void TIMER_ITRxExtClock(TIMER_TypeDef *TIMERx, uint16_t TIMER_InputTriSrc);
void TIMER_TIxExtCLkConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_TIxExCLKSrc,
                           uint16_t TIMER_ICPolarity, uint16_t ICFilter);
void TIMER_ETRClockMode1Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ExTriPrescaler, uint16_t TIMER_ExTriPolarity,
                               uint16_t ExtTriFilter);
void TIMER_ETRClockMode2Config(TIMER_TypeDef *TIMERx, uint16_t TIMER_ExTriPrescaler,
                               uint16_t TIMER_ExTriPolarity, uint16_t ExtTriFilter);
/* Synchronization management *************************************************/
void TIMER_SelectInputTrigger(TIMER_TypeDef *TIMERx, uint16_t TIMER_InputTriSrc);
void TIMER_SelectOutputTrigger(TIMER_TypeDef *TIMERx, uint16_t TIMER_TriOutSrc);
void TIMER_SelectSlaveMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_SlaveMode);
void TIMER_SelectMasterSlaveMode(TIMER_TypeDef *TIMERx, uint16_t TIMER_MasterSlaveMode);
void TIMER_ETRConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_ExTriPrescaler, uint16_t TIMER_ExTriPolarity,
                     uint16_t ExtTriFilter);

/* Specific interface management **********************************************/
void TIMER_EncoderInterfaceConfig(TIMER_TypeDef *TIMERx, uint16_t TIMER_EncoderMode,
                                  uint16_t TIMER_IC1Polarity, uint16_t TIMER_IC2Polarity);
void TIMER_SelectHallSensor(TIMER_TypeDef *TIMERx, TypeState NewValue);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_TIMER_H */

/**
  * @}
  */

/**
  * @}
  */
