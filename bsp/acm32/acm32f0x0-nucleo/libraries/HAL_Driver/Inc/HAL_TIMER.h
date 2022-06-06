/***********************************************************************
 * Filename    : hal_timer.h
 * Description : timer driver header file
 * Author(s)   : Eric
 * version     : V1.0
 * Modify date : 2016-03-24
 ***********************************************************************/
#ifndef __HAL_TIMER_H__
#define __HAL_TIMER_H__

#include "ACM32Fxx_HAL.h"

#define IS_TIMER_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1) || ((INSTANCE) == TIM3) \
                                                                            || ((INSTANCE) == TIM6) \
                                                                            || ((INSTANCE) == TIM14) || ((INSTANCE) == TIM15) || ((INSTANCE) == TIM16)\
                                                                            | ((INSTANCE) == TIM17) )

/****************** TIM Instances : supporting the break function *************/
#define IS_TIM_BREAK_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)    || \
                                            ((INSTANCE) == TIM15)   || \
                                            ((INSTANCE) == TIM16)   || \
                                            ((INSTANCE) == TIM17))

/************** TIM Instances : supporting Break source selection *************/
#define IS_TIM_BREAKSOURCE_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                               ((INSTANCE) == TIM15)  || \
                                               ((INSTANCE) == TIM16)  || \
                                               ((INSTANCE) == TIM17))


/************* TIM Instances : at least 1 capture/compare channel *************/
#define IS_TIM_CC1_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                                                                 ((INSTANCE) == TIM3)   || \
                                                                                 ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM14)  || \
                                         ((INSTANCE) == TIM15)  || \
                                         ((INSTANCE) == TIM16)  || \
                                         ((INSTANCE) == TIM17))

/************ TIM Instances : at least 2 capture/compare channels *************/
#define IS_TIM_CC2_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                                                                 ((INSTANCE) == TIM3)   || \
                                                                                 ((INSTANCE) == TIM4)   || \
                                         ((INSTANCE) == TIM15))

/************ TIM Instances : at least 3 capture/compare channels *************/
#define IS_TIM_CC3_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                                                                 ((INSTANCE) == TIM2)   || \
                                                                                 ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4))

/************ TIM Instances : at least 4 capture/compare channels *************/
#define IS_TIM_CC4_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)   || \
                                         ((INSTANCE) == TIM2)   || \
                                                                                 ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM4))


/****************** TIM Instances : DMA requests generation (TIMx_DIER.UDE) ***/
#define IS_TIM_UDMA_INSTANCE(INSTANCE)      (((INSTANCE) == TIM1)   || \
                                            ((INSTANCE) == TIM3)   || \
                                            ((INSTANCE) == TIM6)   || \
                                            ((INSTANCE) == TIM7)   || \
                                            ((INSTANCE) == TIM15)  || \
                                            ((INSTANCE) == TIM16)  || \
                                            ((INSTANCE) == TIM17))

/******************* TIM Instances : output(s) available **********************/
#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
    ( (((INSTANCE) == TIM1) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4) ) )          \
         ||                                        \
     (((INSTANCE) == TIM3) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)) )           \
     ||                                        \
     (((INSTANCE) == TIM14) &&                 \
     (((CHANNEL) == TIM_CHANNEL_1)) )           \
     ||                                        \
     (((INSTANCE) == TIM15) &&                 \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2)) )           \
     ||                                        \
     (((INSTANCE) == TIM16) &&                 \
     (((CHANNEL) == TIM_CHANNEL_1)) )           \
     ||                                        \
     (((INSTANCE) == TIM17) &&                 \
      ((CHANNEL) == TIM_CHANNEL_1) ) )

/****************** TIM Instances : supporting complementary output(s) ********/
#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
   ((( (INSTANCE) == TIM1) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3)) )            \
    ||                                          \
    (((INSTANCE) == TIM15) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM16) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1))              \
    ||                                          \
    (((INSTANCE) == TIM17) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1)  ) )

/****************** TIM Instances : supporting clock division *****************/
#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)   (((INSTANCE) == TIM1)    || \
                                                                                                        ((INSTANCE) == TIM3)    || \
                                                    ((INSTANCE) == TIM14)   || \
                                                    ((INSTANCE) == TIM15)   || \
                                                    ((INSTANCE) == TIM16)   || \
                                                    ((INSTANCE) == TIM17))

/****** TIM Instances : supporting external clock mode 1 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) \
                                                                                                                ((INSTANCE) == TIM3) \
                                                                                                                ((INSTANCE) == TIM4) )

/****** TIM Instances : supporting external clock mode 2 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE) (((INSTANCE) == TIM1) || \
                                                        ((INSTANCE) == TIM2) \
                                                                                                                ((INSTANCE) == TIM3) \
                                                                                                                ((INSTANCE) == TIM4) )

/****************** TIM Instances : supporting combined 3-phase PWM mode ******/
#define IS_TIM_COMBINED3PHASEPWM_INSTANCE(INSTANCE)    ((INSTANCE) == TIM1)

/****************** TIM Instances : supporting commutation event generation ***/
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                                     ((INSTANCE) == TIM15)  || \
                                                     ((INSTANCE) == TIM16)  || \
                                                     ((INSTANCE) == TIM17))

/****************** TIM Instances : supporting encoder interface **************/
#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1)  || \
                                                      ((INSTANCE) == TIM2) \
                                                                                                            ((INSTANCE) == TIM3) \
                                                                                                            ((INSTANCE) == TIM4) )

/****************** TIM Instances : supporting Hall sensor interface **********/
#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE) (((INSTANCE) == TIM1)   || \
                                                      ((INSTANCE) == TIM2) \
                                                                                                            ((INSTANCE) == TIM3) \
                                                                                                            ((INSTANCE) == TIM4) )

/*********** TIM Instances : Slave mode available (TIMx_SMCR available )*******/
#define IS_TIM_SLAVE_INSTANCE(INSTANCE)    (((INSTANCE) == TIM1)  || \
                                                                                        ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting repetition counter *************/
#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)  (((INSTANCE) == TIM1)  || \
                                                       ((INSTANCE) == TIM15) || \
                                                       ((INSTANCE) == TIM16) || \
                                                       ((INSTANCE) == TIM17))

#define HAL_TIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->DIER |= (__INTERRUPT__))
#define HAL_TIM_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->DIER &= ~(__INTERRUPT__))

#define HAL_TIM_ENABLE_IT_EX(__INSTANCE__, __INTERRUPT__)    ((__INSTANCE__)->DIER |= (__INTERRUPT__))
#define HAL_TIM_DISABLE_IT_EX(__INSTANCE__, __INTERRUPT__)   ((__INSTANCE__)->DIER &= ~(__INTERRUPT__))

#define HAL_TIM_ENABLE_DMA(__HANDLE__, __DMA_REQ__)    ((__HANDLE__)->Instance->DIER |= (__DMA_REQ__))
#define HAL_TIM_DISABLE_DMA(__HANDLE__, __DMA_REQ__)   ((__HANDLE__)->Instance->DIER &= ~(__DMA_REQ__))



#define TIM_CR2_CCPC_Pos          (0U)
#define TIM_CR2_CCPC_Msk          (0x1UL << TIM_CR2_CCPC_Pos)
#define TIM_CR2_CCPC              TIM_CR2_CCPC_Msk
#define TIM_CR2_CCUS_Pos          (2U)
#define TIM_CR2_CCUS_Msk          (0x1UL << TIM_CR2_CCUS_Pos)
#define TIM_CR2_CCUS              TIM_CR2_CCUS_Msk
#define TIM_CR2_CCDS_Pos          (3U)
#define TIM_CR2_CCDS_Msk          (0x1UL << TIM_CR2_CCDS_Pos)
#define TIM_CR2_CCDS              TIM_CR2_CCDS_Msk

#define TIM_COMMUTATION_TRGI              TIM_CR2_CCUS
#define TIM_COMMUTATION_SOFTWARE          0x00000000U

#define TIM_IT_UPDATE                      BIT0
#define TIM_IT_CC1                         BIT1
#define TIM_IT_CC2                         BIT2
#define TIM_IT_CC3                         BIT3
#define TIM_IT_CC4                         BIT4
#define TIM_IT_COM                         BIT5
#define TIM_IT_TRIGGER                     BIT6
#define TIM_IT_BREAK                       BIT7

#define TIM_DMA_UPDATE                      BIT8
#define TIM_DMA_CC1                         BIT9
#define TIM_DMA_CC2                         BIT10
#define TIM_DMA_CC3                         BIT11
#define TIM_DMA_CC4                         BIT12
#define TIM_DMA_COM                         BIT13
#define TIM_DMA_TRIGGER                     BIT14
#define TIM_DMA_BREAK                       BIT15



#define TIM_EVENTSOURCE_UPDATE              BIT0     /*!< Reinitialize the counter and generates an update of the registers */
#define TIM_EVENTSOURCE_CC1                 BIT1     /*!< A capture/compare event is generated on channel 1 */
#define TIM_EVENTSOURCE_CC2                 BIT2     /*!< A capture/compare event is generated on channel 2 */
#define TIM_EVENTSOURCE_CC3                 BIT3     /*!< A capture/compare event is generated on channel 3 */
#define TIM_EVENTSOURCE_CC4                 BIT4     /*!< A capture/compare event is generated on channel 4 */
#define TIM_EVENTSOURCE_COM                 BIT5     /*!< A commutation event is generated */
#define TIM_EVENTSOURCE_TRIGGER             BIT6     /*!< A trigger event is generated */
#define TIM_EVENTSOURCE_BREAK               BIT7     /*!< A break event is generated */

#define TIM_ARR_PRELOAD_DISABLE   0
#define TIM_ARR_PRELOAD_ENABLE    1

#define TIM_COUNTERMODE_DIR_INDEX          4
#define TIM_COUNTERMODE_UP                 (0 << TIM_COUNTERMODE_DIR_INDEX)
#define TIM_COUNTERMODE_DOWN               (1 << TIM_COUNTERMODE_DIR_INDEX)

#define TIM_COUNTERMODE_CMS_INDEX          5
#define TIM_COUNTERMODE_CENTERALIGNED1     (1 << TIM_COUNTERMODE_CMS_INDEX)
#define TIM_COUNTERMODE_CENTERALIGNED2     (2 << TIM_COUNTERMODE_CMS_INDEX)
#define TIM_COUNTERMODE_CENTERALIGNED3     (3 << TIM_COUNTERMODE_CMS_INDEX)

#define TIM_CLKCK_DIV_INDEX                8
#define TIM_CLOCKDIVISION_DIV1             0x00000000U                          /*!< Clock division: tDTS=tCK_INT   */
#define TIM_CLOCKDIVISION_DIV2             (1U << TIM_CLKCK_DIV_INDEX)          /*!< Clock division: tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4             (2U << TIM_CLKCK_DIV_INDEX)          /*!< Clock division: tDTS=4*tCK_INT */

#define TIM_TRGO_RESET       (0 << 4)
#define TIM_TRGO_ENABLE      (1 << 4)
#define TIM_TRGO_UPDATE      (2 << 4)
#define TIM_TRGO_CMP_PULSE   (3 << 4)
#define TIM_TRGO_OC1REF      (4 << 4)
#define TIM_TRGO_OC2REF      (5 << 4)
#define TIM_TRGO_OC3REF      (6 << 4)
#define TIM_TRGO_OC4REF      (7 << 4)

#define TIM_MASTERSLAVEMODE_DISABLE  0
#define TIM_MASTERSLAVEMODE_ENABLE   BIT7


#define TIM_SLAVE_MODE_INDEX     0
#define TIM_SLAVE_MODE_DIS       (0U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_ENC1      (1U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_ENC2      (2U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_ENC3      (3U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_RST       (4U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_GATE      (5U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_TRIG      (6U << TIM_SLAVE_MODE_INDEX)
#define TIM_SLAVE_MODE_EXT1      (7U << TIM_SLAVE_MODE_INDEX)

#define TIM_TRIGGER_SOURCE_INDEX        4
#define TIM_TRIGGER_SOURCE_ITR0         (0U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_ITR1         (1U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_ITR2         (2U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_ITR3         (3U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_TI1F_ED      (4U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_TI1FP1       (5U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_TI2FP2       (6U << TIM_TRIGGER_SOURCE_INDEX)
#define TIM_TRIGGER_SOURCE_ETRF         (7U << TIM_TRIGGER_SOURCE_INDEX)

#define TIMER_SR_UIF    BIT0
#define TIMER_SR_CC1IF  BIT1
#define TIMER_SR_CC2IF  BIT2
#define TIMER_SR_CC3IF  BIT3
#define TIMER_SR_CC4IF  BIT4
#define TIMER_SR_COMIF  BIT5
#define TIMER_SR_TIF    BIT6
#define TIMER_SR_BIF    BIT7
#define TIMER_SR_CC1OF  BIT9
#define TIMER_SR_CC2OF  BIT10
#define TIMER_SR_CC3OF  BIT11
#define TIMER_SR_CC4OF  BIT12

#define TIMER_INT_EN_UPD       BIT0
#define TIMER_INT_EN_CC1       BIT1
#define TIMER_INT_EN_CC2       BIT2
#define TIMER_INT_EN_CC3       BIT3
#define TIMER_INT_EN_CC4       BIT4
#define TIMER_INT_EN_COM       BIT5
#define TIMER_INT_EN_TRI       BIT6
#define TIMER_INT_EN_BRK       BIT7

#define TIMER_DMA_EN_UPD       BIT8
#define TIMER_DMA_EN_CC1       BIT9
#define TIMER_DMA_EN_CC2       BIT10
#define TIMER_DMA_EN_CC3       BIT11
#define TIMER_DMA_EN_CC4       BIT12
#define TIMER_DMA_EN_COM       BIT13
#define TIMER_DMA_EN_TRI       BIT14

#define TIM_CHANNEL_1                      0
#define TIM_CHANNEL_2                      1
#define TIM_CHANNEL_3                      2
#define TIM_CHANNEL_4                      3

#define OUTPUT_FAST_MODE_DISABLE  0
#define OUTPUT_FAST_MODE_ENABLE   1

#define OUTPUT_POL_ACTIVE_HIGH  0
#define OUTPUT_POL_ACTIVE_LOW   1

#define OUTPUT_DISABLE_IDLE_STATE  0
#define OUTPUT_ENABLE_IDLE_STATE   1

#define OUTPUT_IDLE_STATE_0     0
#define OUTPUT_IDLE_STATE_1     1

#define OUTPUT_MODE_FROZEN          0
#define OUTPUT_MODE_MATCH_HIGH      1
#define OUTPUT_MODE_MATCH_LOW       2
#define OUTPUT_MODE_MATCH_TOGGLE    3
#define OUTPUT_MODE_FORCE_LOW       4
#define OUTPUT_MODE_FORCE_HIGH      5
#define OUTPUT_MODE_PWM1            6
#define OUTPUT_MODE_PWM2            7

#define TIM_CLOCKSOURCE_INT       0
#define TIM_CLOCKSOURCE_ITR0      1
#define TIM_CLOCKSOURCE_ITR1      2
#define TIM_CLOCKSOURCE_ITR2      3
#define TIM_CLOCKSOURCE_ITR3      4
#define TIM_CLOCKSOURCE_TI1FP1    5
#define TIM_CLOCKSOURCE_TI2FP2    6
#define TIM_CLOCKSOURCE_ETR       7

#define TIM_ETR_POLAIRTY_HIGH     0
#define TIM_ETR_POLAIRTY_LOW      (BIT15)
#define TIM_ETR_FILTER_LVL(x)     (x << 8)   //BIT8-BIT11

#define TIM_ETR_PRESCALER_1    0
#define TIM_ETR_PRESCALER_2    (BIT12)
#define TIM_ETR_PRESCALER_4    (BIT13)
#define TIM_ETR_PRESCALER_8    (BIT12|BIT13)

#define ETR_SELECT_GPIO        0
#define ETR_SELECT_COMP1_OUT   BIT14
#define ETR_SELECT_COMP2_OUT   BIT15
#define ETR_SELECT_ADC_AWD     BIT14|BIT15
#define ETR_SELECT_MASK        (BIT14|BIT15)

#define TIM_TI1_FILTER_LVL(x)     (x << 4)
#define TIM_TI2_FILTER_LVL(x)     (x << 12)
#define TIM_TI3_FILTER_LVL(x)     (x << 4)
#define TIM_TI4_FILTER_LVL(x)     (x << 12)

#define TIM_IC1_PRESCALER_1    0
#define TIM_IC1_PRESCALER_2    (BIT2)
#define TIM_IC1_PRESCALER_4    (BIT3)
#define TIM_IC1_PRESCALER_8    (BIT2|BIT3)

#define TIM_IC2_PRESCALER_1    0
#define TIM_IC2_PRESCALER_2    (BIT10)
#define TIM_IC2_PRESCALER_4    (BIT11)
#define TIM_IC2_PRESCALER_8    (BIT10|BIT11)

#define TIM_IC3_PRESCALER_1    0
#define TIM_IC3_PRESCALER_2    (BIT2)
#define TIM_IC3_PRESCALER_4    (BIT3)
#define TIM_IC3_PRESCALER_8    (BIT2|BIT3)

#define TIM_IC4_PRESCALER_1    0
#define TIM_IC4_PRESCALER_2    (BIT10)
#define TIM_IC4_PRESCALER_4    (BIT11)
#define TIM_IC4_PRESCALER_8    (BIT10|BIT11)

typedef struct
{
  uint32_t ClockSource;     //TIMER clock sources
  uint32_t ClockPolarity;   //TIMER clock polarity
  uint32_t ClockPrescaler;  //TIMER clock prescaler
  uint32_t ClockFilter;     //TIMER clock filter
} TIM_ClockConfigTypeDef;

typedef struct
{
  uint32_t OCMode;        // Specifies the TIM mode.
  uint32_t Pulse;         // Specifies the pulse value to be loaded into the Capture Compare Register.
  uint32_t OCPolarity;    // Specifies the output polarity.
  uint32_t OCNPolarity;   // Specifies the complementary output polarity.
  uint32_t OCFastMode;    // Specifies the Fast mode state.
  uint32_t OCIdleState;   // Specifies the TIM Output Compare pin state during Idle state.
  uint32_t OCNIdleState;  // Specifies the TIM Output Compare complementary pin state during Idle state.
} TIM_OC_InitTypeDef;


#define TIM_SLAVE_CAPTURE_ACTIVE_RISING          0
#define TIM_SLAVE_CAPTURE_ACTIVE_FALLING         1
#define TIM_SLAVE_CAPTURE_ACTIVE_RISING_FALLING  2

#define TIM_ICSELECTION_DIRECTTI    0
#define TIM_ICSELECTION_INDIRECTTI  1

#define TIM_CC1_SLAVE_CAPTURE_POL_RISING    (0)
#define TIM_CC1_SLAVE_CAPTURE_POL_FALLING   (BIT1)
#define TIM_CC1_SLAVE_CAPTURE_POL_BOTH      (BIT1 | BIT3)

#define TIM_CC2_SLAVE_CAPTURE_POL_RISING    (0)
#define TIM_CC2_SLAVE_CAPTURE_POL_FALLING   (BIT5)
#define TIM_CC2_SLAVE_CAPTURE_POL_BOTH      (BIT5 | BIT7)

#define TIM_CC3_SLAVE_CAPTURE_POL_RISING    (0)
#define TIM_CC3_SLAVE_CAPTURE_POL_FALLING   (BIT9)
#define TIM_CC3_SLAVE_CAPTURE_POL_BOTH      (BIT9 | BIT11)

#define TIM_CC4_SLAVE_CAPTURE_POL_RISING    (0)
#define TIM_CC4_SLAVE_CAPTURE_POL_FALLING   (BIT13)
#define TIM_CC4_SLAVE_CAPTURE_POL_BOTH      (BIT13 | BIT15)

typedef struct
{
  uint32_t  SlaveMode;         // Slave mode selection
  uint32_t  InputTrigger;      // Input Trigger source
  uint32_t  TriggerPolarity;   // Input Trigger polarity
  uint32_t  TriggerPrescaler;  // input prescaler, only for ETR input
  uint32_t  TriggerFilter;     // Input trigger filter
} TIM_SlaveConfigTypeDef;

typedef struct
{
  uint32_t ICPolarity;   // Specifies the active edge of the input signal.
  uint32_t ICSelection;  // Specifies the input
  uint32_t ICPrescaler;  // Specifies the Input Capture Prescaler.
  uint32_t TIFilter;     // Specifies the input capture filter.
} TIM_IC_InitTypeDef;

typedef struct
{
  uint32_t  MasterOutputTrigger;   // Trigger output (TRGO) selection
  uint32_t  MasterSlaveMode;       // Master/slave mode selection
} TIM_MasterConfigTypeDef;

#define TIM_DMA_UPDATE_INDEX    0
#define TIM_DMA_CC1_INDEX       1
#define TIM_DMA_CC2_INDEX       2
#define TIM_DMA_CC3_INDEX       3
#define TIM_DMA_CC4_INDEX       4
#define TIM_DMA_COM_INDEX       5
#define TIM_DMA_TRIG_INDEX      6

#define MAX_DMA_REQ_ONE_TIMER   7

typedef struct
{
  uint32_t Prescaler;         // Specifies the prescaler value used to divide the TIM clock.
  uint32_t Period;            // Specifies the ARR value
  uint32_t ARRPreLoadEn;      // Specifies the preload enable or disable
  uint32_t RepetitionCounter; // Specifies the repetition counter value
  uint32_t CounterMode;       // Specifies the counter mode.Up/Down/Center
  uint32_t ClockDivision;     // Specifies the clock division, used for deadtime or sampling
} TIM_Base_InitTypeDef;

typedef struct
{
    TIM_TypeDef *Instance;
    TIM_Base_InitTypeDef     Init;          /*!< TIM Time Base required parameters */
    DMA_HandleTypeDef        *hdma[MAX_DMA_REQ_ONE_TIMER];
}TIM_HandleTypeDef;

/* HAL_TIMER_MSP_Init */
extern uint32_t HAL_TIMER_MSP_Init(TIM_HandleTypeDef * htim);
/* HAL_TIMER_Slave_Mode_Config */
extern uint32_t HAL_TIMER_Slave_Mode_Config(TIM_HandleTypeDef *htim, TIM_SlaveConfigTypeDef *sSlaveConfig);
/* HAL_TIMER_Base_Init */
extern uint32_t HAL_TIMER_Base_Init(TIM_HandleTypeDef * htim);
/* HAL_TIMER_Output_Config */
extern uint32_t HAL_TIMER_Output_Config(TIM_TypeDef *TIMx, TIM_OC_InitTypeDef * Output_Config, uint32_t Channel);
/* HAL_TIMER_Base_Start */
extern void HAL_TIMER_Base_Start(TIM_TypeDef *TIMx);
extern HAL_StatusTypeDef HAL_TIMER_Base_Stop(TIM_TypeDef *TIMx);
/* HAL_TIM_PWM_Output_Start */
extern uint32_t HAL_TIM_PWM_Output_Start(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIM_PWM_Output_Stop */
extern HAL_StatusTypeDef HAL_TIM_PWM_Output_Stop(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIMER_OC_Start */
extern uint32_t HAL_TIMER_OC_Start(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIMER_OCxN_Start */
extern uint32_t HAL_TIMER_OCxN_Start(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIMER_OC_Stop */
extern HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIM_Capture_Start */
extern uint32_t HAL_TIM_Capture_Start(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIM_Capture_Stop */
extern uint32_t HAL_TIM_Capture_Stop(TIM_TypeDef *TIMx, uint32_t Channel);
/* HAL_TIMER_Capture_Config */
extern uint32_t HAL_TIMER_Capture_Config(TIM_TypeDef *TIMx, TIM_IC_InitTypeDef * Capture_Config, uint32_t Channel);
/* HAL_TIMER_Master_Mode_Config */
extern uint32_t HAL_TIMER_Master_Mode_Config(TIM_TypeDef *TIMx, TIM_MasterConfigTypeDef * sMasterConfig);
/* HAL_TIMER_SelectClockSource */
extern HAL_StatusTypeDef HAL_TIMER_SelectClockSource(TIM_HandleTypeDef *htim, TIM_ClockConfigTypeDef * sClockSourceConfig);
/* HAL_TIMER_ReadCapturedValue */
extern uint32_t HAL_TIMER_ReadCapturedValue(TIM_HandleTypeDef *htim, uint32_t Channel);
/* HAL_TIMER_Clear_Capture_Flag */
extern void HAL_TIMER_Clear_Capture_Flag(TIM_HandleTypeDef *htim, uint32_t Channel);
#endif




