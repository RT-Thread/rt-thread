/**
  ******************************************************************************
  * @file               ft32f4xx_lptim.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the LPTIM
  *                     firmware library.
  * @version            V1.0.0
  * @data                   2025-03-31
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_LPTIM_H
#define __FT32F4XX_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup LPTIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  LPTIM Init structure definition
  */

typedef struct
{
    uint32_t Source;              /*!< Selects the clock source.
                                This parameter can be a value of @ref LPTIM_Clock_Source   */

    uint32_t Prescaler;           /*!< Specifies the counter clock Prescaler.
                                This parameter can be a value of @ref LPTIM_Clock_Prescaler */

    uint32_t Polarity;            /*!< Selects the polarity of the active edge for the counter unit
                                if the ULPTIM input is selected.
                                Note: This parameter is used only when Ultra low power clock source is used.
                                Note: If the polarity is configured on 'both edges', an auxiliary clock
                                (one of the Low power oscillator) must be active.
                                This parameter can be a value of @ref LPTIM_Clock_Polarity */

    uint32_t Clock_SampleTime;    /*!< Selects the clock sampling time to configure the clock glitch filter.
                                Note: This parameter is used only when Ultra low power clock source is used.
                                This parameter can be a value of @ref LPTIM_Clock_Sample_Time */

    uint32_t Trigger_Source;      /*!< Selects the Trigger source.
                                This parameter can be a value of @ref LPTIM_Trigger_Source */

    uint32_t Trigegr_ActiveEdge;  /*!< Selects the Trigger active edge.
                                Note: This parameter is used only when an external trigger is used.
                                This parameter can be a value of @ref LPTIM_External_Trigger_Polarity */

    uint32_t Trigg_SampleTime;    /*!< Selects the trigger sampling time to configure the clock glitch filter.
                                Note: This parameter is used only when an external trigger is used.
                                This parameter can be a value of @ref LPTIM_Trigger_Sample_Time  */

    uint32_t OutputPolarity;      /*!< Specifies the Output polarity.
                                This parameter can be a value of @ref LPTIM_Output_Polarity */

    uint32_t UpdateMode;          /*!< Specifies whether the update of the autoreload and the compare
                                values is done immediately or after the end of current period.
                                This parameter can be a value of @ref LPTIM_Updating_Mode */

    uint32_t CounterSource;       /*!< Specifies whether the counter is incremented each internal event
                                or each external event.
                                This parameter can be a value of @ref LPTIM_Counter_Source */

    uint32_t Input1Source;        /*!< Specifies source selected for input1 (GPIO or comparator output).
                                This parameter can be a value of @ref LPTIM_Input1_Source */

    uint32_t Input2Source;        /*!< Specifies source selected for input2 (GPIO or comparator output).
                                Note: This parameter is used only for encoder feature so is used only
                                for LPTIM1 instance.
                                This parameter can be a value of @ref LPTIM_Input2_Source */
} LPTIM_InitTypeDef;




/* Exported constants --------------------------------------------------------*/
/** @defgroup LPTIM_Exported_Constants
  * @{
  */

/** @defgroup LPTIM_Clock_Source LPTIM Clock Source
  * @{
  */
#define LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC        0x00000000U
#define LPTIM_CLOCKSOURCE_ULPTIM                LPTIM_CFGR_CKSEL
#define IS_LPTIM_CLOCK_SOURCE(SOURCE)       (((SOURCE) == LPTIM_CLOCKSOURCE_ULPTIM) || \
                                             ((SOURCE) == LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC))
/**
  * @}
  */

/** @defgroup LPTIM_Clock_Prescaler LPTIM Clock Prescaler
  * @{
  */
#define LPTIM_PRESCALER_DIV1                    0x00000000U
#define LPTIM_PRESCALER_DIV2                    LPTIM_CFGR_PRESC_0
#define LPTIM_PRESCALER_DIV4                    LPTIM_CFGR_PRESC_1
#define LPTIM_PRESCALER_DIV8                    (LPTIM_CFGR_PRESC_0 | LPTIM_CFGR_PRESC_1)
#define LPTIM_PRESCALER_DIV16                   LPTIM_CFGR_PRESC_2
#define LPTIM_PRESCALER_DIV32                   (LPTIM_CFGR_PRESC_0 | LPTIM_CFGR_PRESC_2)
#define LPTIM_PRESCALER_DIV64                   (LPTIM_CFGR_PRESC_1 | LPTIM_CFGR_PRESC_2)
#define LPTIM_PRESCALER_DIV128                  LPTIM_CFGR_PRESC
#define IS_LPTIM_CLOCK_PRESCALER(PRESCALER) (((PRESCALER) ==  LPTIM_PRESCALER_DIV1  ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV2  ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV4  ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV8  ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV16 ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV32 ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV64 ) || \
                                             ((PRESCALER) ==  LPTIM_PRESCALER_DIV128))

/**
  * @}
  */

/** @defgroup LPTIM_Clock_Polarity LPTIM Clock Polarity
  * @{
  */
#define LPTIM_CLOCKPOLARITY_RISING              0x00000000U
#define LPTIM_CLOCKPOLARITY_FALLING             LPTIM_CFGR_CKPOL_0
#define LPTIM_CLOCKPOLARITY_RISING_FALLING      LPTIM_CFGR_CKPOL_1
#define IS_LPTIM_CLOCK_POLARITY(POLARITY)   (((POLARITY) == LPTIM_CLOCKPOLARITY_RISING)  || \
                                             ((POLARITY) == LPTIM_CLOCKPOLARITY_FALLING) || \
                                             ((POLARITY) == LPTIM_CLOCKPOLARITY_RISING_FALLING))

/**
  * @}
  */

/** @defgroup LPTIM_Clock_Sample_Time LPTIM Clock Sample Time
  * @{
  */
#define LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION  0x00000000U
#define LPTIM_CLOCKSAMPLETIME_2TRANSITIONS      LPTIM_CFGR_CKFLT_0
#define LPTIM_CLOCKSAMPLETIME_4TRANSITIONS      LPTIM_CFGR_CKFLT_1
#define LPTIM_CLOCKSAMPLETIME_8TRANSITIONS      LPTIM_CFGR_CKFLT
#define IS_LPTIM_CLOCK_SAMPLE_TIME(SAMPLETIME) (((SAMPLETIME) == LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION) || \
                                                ((SAMPLETIME) == LPTIM_CLOCKSAMPLETIME_2TRANSITIONS)     || \
                                                ((SAMPLETIME) == LPTIM_CLOCKSAMPLETIME_4TRANSITIONS)     || \
                                                ((SAMPLETIME) == LPTIM_CLOCKSAMPLETIME_8TRANSITIONS))

/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Source LPTIM Trigger Source
  * @{
  */
//#define LPTIM_TRIGSOURCE_SOFTWARE               0x0000FFFFU
#define LPTIM_TRIGSOURCE_0                      0x00000000U
#define LPTIM_TRIGSOURCE_1                      LPTIM_CFGR_TRIGSEL_0
#define LPTIM_TRIGSOURCE_2                      LPTIM_CFGR_TRIGSEL_1
#define LPTIM_TRIGSOURCE_3                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_1)
#define LPTIM_TRIGSOURCE_4                      LPTIM_CFGR_TRIGSEL_2
#define LPTIM_TRIGSOURCE_5                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_2)
#define LPTIM_TRIGSOURCE_6                      (LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_2)
#define LPTIM_TRIGSOURCE_7                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_2)
#define LPTIM_TRIGSOURCE_8                      LPTIM_CFGR_TRIGSEL_3
#define LPTIM_TRIGSOURCE_9                      (LPTIM_CFGR_TRIGSEL_0 | LPTIM_CFGR_TRIGSEL_3)
#define LPTIM_TRIGSOURCE_10                     (LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_3)
#define LPTIM_TRIGSOURCE_11                     (LPTIM_CFGR_TRIGSEL_0 |LPTIM_CFGR_TRIGSEL_1 | LPTIM_CFGR_TRIGSEL_3)
#define LPTIM_TRIGSOURCE_12                     (LPTIM_CFGR_TRIGSEL_2 | LPTIM_CFGR_TRIGSEL_3)
#define IS_LPTIM_TRG_SOURCE(TRIG)           (((TRIG) == LPTIM_TRIGSOURCE_0) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_1) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_2) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_3) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_4) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_5) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_6) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_7) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_8) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_9) || \
                                             ((TRIG) == LPTIM_TRIGSOURCE_10)|| \
                                             ((TRIG) == LPTIM_TRIGSOURCE_11)|| \
                                             ((TRIG) == LPTIM_TRIGSOURCE_12))

/**
  * @}
  */

/** @defgroup LPTIM_External_Trigger_Polarity LPTIM External Trigger Polarity
  * @{
  */
#define LPTIM_SOFTWARE                         0x00000000
#define LPTIM_ACTIVEEDGE_RISING                LPTIM_CFGR_TRIGEN_0
#define LPTIM_ACTIVEEDGE_FALLING               LPTIM_CFGR_TRIGEN_1
#define LPTIM_ACTIVEEDGE_RISING_FALLING        LPTIM_CFGR_TRIGEN
#define IS_LPTIM_EXT_TRG_POLARITY(POLARITY) (((POLARITY) == LPTIM_SOFTWARE                  ) || \
                                             ((POLARITY) == LPTIM_ACTIVEEDGE_RISING         ) || \
                                             ((POLARITY) == LPTIM_ACTIVEEDGE_FALLING        ) || \
                                             ((POLARITY) == LPTIM_ACTIVEEDGE_RISING_FALLING ))

/**
  * @}
  */

/** @defgroup LPTIM_Trigger_Sample_Time LPTIM Trigger Sample Time
  * @{
  */
#define LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION  0x00000000U
#define LPTIM_TRIGSAMPLETIME_2TRANSITIONS      LPTIM_CFGR_TRGFLT_0
#define LPTIM_TRIGSAMPLETIME_4TRANSITIONS      LPTIM_CFGR_TRGFLT_1
#define LPTIM_TRIGSAMPLETIME_8TRANSITIONS      LPTIM_CFGR_TRGFLT
#define IS_LPTIM_TRIG_SAMPLE_TIME(SAMPLETIME) (((SAMPLETIME) == LPTIM_TRIGSAMPLETIME_DIRECTTRANSITION) || \
                                               ((SAMPLETIME) == LPTIM_TRIGSAMPLETIME_2TRANSITIONS    ) || \
                                               ((SAMPLETIME) == LPTIM_TRIGSAMPLETIME_4TRANSITIONS    ) || \
                                               ((SAMPLETIME) == LPTIM_TRIGSAMPLETIME_8TRANSITIONS    ))


/**
  * @}
  */

/** @defgroup LPTIM_Output_Polarity LPTIM Output Polarity
  * @{
  */

#define LPTIM_OUTPUTPOLARITY_HIGH               0x00000000U
#define LPTIM_OUTPUTPOLARITY_LOW                LPTIM_CFGR_WAVPOL
#define IS_LPTIM_OUTPUT_POLARITY(POLARITY)  (((POLARITY) == LPTIM_OUTPUTPOLARITY_LOW ) || \
                                             ((POLARITY) == LPTIM_OUTPUTPOLARITY_HIGH))

/**
  * @}
  */

/** @defgroup LPTIM_Updating_Mode LPTIM Updating Mode
  * @{
  */

#define LPTIM_UPDATE_IMMEDIATE                  0x00000000U
#define LPTIM_UPDATE_ENDOFPERIOD                LPTIM_CFGR_PRELOAD
#define IS_LPTIM_UPDATE_MODE(MODE)          (((MODE) == LPTIM_UPDATE_IMMEDIATE) || \
                                             ((MODE) == LPTIM_UPDATE_ENDOFPERIOD))
/**
  * @}
  */

/** @defgroup LPTIM_Counter_Source LPTIM Counter Source
  * @{
  */

#define LPTIM_COUNTERSOURCE_INTERNAL            0x00000000U
#define LPTIM_COUNTERSOURCE_EXTERNAL            LPTIM_CFGR_COUNTMODE
#define IS_LPTIM_COUNTER_SOURCE(SOURCE)     (((SOURCE) == LPTIM_COUNTERSOURCE_INTERNAL) || \
                                             ((SOURCE) == LPTIM_COUNTERSOURCE_EXTERNAL))
/**
  * @}
  */

/** @defgroup LPTIM_Input1_Source LPTIM Input1 Source
  * @{
  */

#define LPTIM_INPUT1SOURCE_GPIO         0x00000000U
#define LPTIM_INPUT1SOURCE_COMP1        LPTIM_OR_IN1_0
#define LPTIM_INPUT1SOURCE_COMP3        (LPTIM_OR_IN1_1 | LPTIM_OR_IN1_0)
#define LPTIM_INPUT1SOURCE_COMP5        (LPTIM_OR_IN1_2 | LPTIM_OR_IN1_0)
#define LPTIM_INPUT1SOURCE_COMP5_1      (LPTIM_OR_IN1_2 | LPTIM_OR_IN1_1 | LPTIM_OR_IN1_0)
#define IS_LPTIM_INPUT1_SOURCE(SOURCE)  (((SOURCE) == LPTIM_INPUT1SOURCE_GPIO) ||        \
                                         ((SOURCE) == LPTIM_INPUT1SOURCE_COMP1) ||        \
                                         ((SOURCE) == LPTIM_INPUT1SOURCE_COMP3) ||        \
                                         ((SOURCE) == LPTIM_INPUT1SOURCE_COMP5) ||        \
                                         ((SOURCE) == LPTIM_INPUT1SOURCE_COMP5_1))

/**
  * @}
  */

/** @defgroup LPTIM_Input2_Source LPTIM Input2 Source
  * @{
  */

#define LPTIM_INPUT2SOURCE_GPIO         0x00000000U
#define LPTIM_INPUT2SOURCE_COMP2        LPTIM_OR_IN2_0
#define LPTIM_INPUT2SOURCE_COMP4        (LPTIM_OR_IN2_1 | LPTIM_OR_IN2_0)
#define LPTIM_INPUT2SOURCE_COMP6        (LPTIM_OR_IN2_2 | LPTIM_OR_IN2_0)
#define LPTIM_INPUT2SOURCE_COMP6_1      (LPTIM_OR_IN2_2 | LPTIM_OR_IN2_1 | LPTIM_OR_IN2_0)
#define IS_LPTIM_INPUT2_SOURCE(SOURCE)  (((SOURCE) == LPTIM_INPUT2SOURCE_GPIO) ||        \
                                         ((SOURCE) == LPTIM_INPUT2SOURCE_COMP2) ||        \
                                         ((SOURCE) == LPTIM_INPUT2SOURCE_COMP4) ||        \
                                         ((SOURCE) == LPTIM_INPUT2SOURCE_COMP6) ||        \
                                         ((SOURCE) == LPTIM_INPUT2SOURCE_COMP6_1))
/**
  * @}
  */

/** @defgroup LPTIM_Flag_Definition LPTIM Flags Definition
  * @{
  */

#define LPTIM_FLAG_DOWN                          ((uint32_t)0x00000040)
#define LPTIM_FLAG_UP                            ((uint32_t)0x00000020)
#define LPTIM_FLAG_ARROK                         ((uint32_t)0x00000010)
#define LPTIM_FLAG_CMPOK                         ((uint32_t)0x00000008)
#define LPTIM_FLAG_EXTTRIG                       ((uint32_t)0x00000004)
#define LPTIM_FLAG_ARRM                          ((uint32_t)0x00000002)
#define LPTIM_FLAG_CMPM                          ((uint32_t)0x00000001)
/**
  * @}
  */

/** @defgroup LPTIM_Interrupts_Definition LPTIM Interrupts Definition
  * @{
  */
#define LPTIM_IT_DOWNIE                          ((uint32_t)0x00000040)
#define LPTIM_IT_UPIE                            ((uint32_t)0x00000020)
#define LPTIM_IT_ARROKIE                         ((uint32_t)0x00000010)
#define LPTIM_IT_CMPOKIE                         ((uint32_t)0x00000008)
#define LPTIM_IT_EXTTRIGIE                       ((uint32_t)0x00000004)
#define LPTIM_IT_ARRMIE                          ((uint32_t)0x00000002)
#define LPTIM_IT_CMPMIE                          ((uint32_t)0x00000001)
/**
  * @}
  */

#define IS_LPTIM_AUTORELOAD(AUTORELOAD)     ((AUTORELOAD) <= 0x0000FFFFUL)

#define IS_LPTIM_COMPARE(COMPARE)           ((COMPARE) <= 0x0000FFFFUL)

#define IS_LPTIM_PERIOD(PERIOD)             ((PERIOD) <= 0x0000FFFFUL)

#define IS_LPTIM_PULSE(PULSE)               ((PULSE) <= 0x0000FFFFUL)


/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void LPTIM_DeInit(void);
void LPTIM_Init(LPTIM_InitTypeDef *LPTIM_InitStruct);
void LPTIM_StructInit(LPTIM_InitTypeDef *LPTIM_InitStruct);

/* Reading/Write operation functions ************************************************/
uint32_t LPTIM_ReadCounter(void);
uint32_t LPTIM_ReadAutoReload(void);
uint32_t LPTIM_ReadCompare(void);
void LPTIM_Write_ARRRegister(uint32_t Period);
void LPTIM_Write_CMPRegister(uint32_t Pulse);
void LPTIM_Preload_Config(FunctionalState NewState);

/* Start/Stop operation functions  *********************************************/
/* ################################# PWM Mode ################################*/
/* Blocking mode: Polling */
void LPTIM_PWM_Start(uint32_t Period, uint32_t Pulse);
void LPTIM_PWM_Stop(void);

/* ############################# One Pulse Mode ##############################*/
/* Blocking mode: Polling */
void LPTIM_OnePulse_Start(uint32_t Period, uint32_t Pulse);
void LPTIM_OnePulse_Stop(void);

/* ############################## Set once Mode ##############################*/
/* Blocking mode: Polling */
void LPTIM_SetOnce_Start(uint32_t Period, uint32_t Pulse);
void LPTIM_SetOnce_Stop(void);

/* ############################### Encoder Mode ##############################*/
/* Blocking mode: Polling */
void LPTIM_Encoder_Start(uint32_t Period);
void LPTIM_Encoder_Stop(void);

/* ############################# Time out  Mode ##############################*/
/* Blocking mode: Polling */
void LPTIM_TimeOut_Start(uint32_t Period, uint32_t Timeout);
void LPTIM_TimeOut_Stop(void);

/* ############################## Counter Mode ###############################*/
/* Blocking mode: Polling */
void LPTIM_Counter_Start(uint32_t Period);
void LPTIM_Counter_Stop(void);

/* LPTIM Reset ****************************************************************/
void LPTIM_RSTARE(FunctionalState NewState);
void LPTIM_COUNTRST(void);

/* LPTIM IRQ functions  *******************************************************/
void LPTIM_ITConfig(uint32_t LPTIM_IT, FunctionalState NewState);
uint32_t LPTIM_GetStatus(uint32_t LPTIM_ISR_FLAG);
void LPTIM_ClearFlag(uint32_t flag);
#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_LPTIM_H */

/**
  * @}
  */

/**
  * @}
  */


