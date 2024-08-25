/**
  ******************************************************************************
  * @file    stm32h7xx_hal_hrtim.h
  * @author  MCD Application Team
  * @brief   Header file of HRTIM HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_HRTIM_H
#define STM32H7xx_HAL_HRTIM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

#if defined(HRTIM1)
/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup HRTIM HRTIM
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @addtogroup HRTIM_Exported_Constants HRTIM Exported Constants
  * @{
  */
/** @defgroup HRTIM_Max_Timer HRTIM Max Timer
  * @{
  */
#define MAX_HRTIM_TIMER 6U
/**
  * @}
  */
/**
  * @}
  */

/** @defgroup HRTIM_Exported_Types HRTIM Exported Types
  * @{
  */

/**
  * @brief  HRTIM Configuration Structure definition - Time base related parameters
  */
typedef struct
{
  uint32_t HRTIMInterruptResquests;  /*!< Specifies which interrupts requests must enabled for the HRTIM instance.
                                          This parameter can be any combination of  @ref HRTIM_Common_Interrupt_Enable */
  uint32_t SyncOptions;              /*!< Specifies how the HRTIM instance handles the external synchronization signals.
                                          The HRTIM instance can be configured to act as a slave (waiting for a trigger
                                          to be synchronized) or a master (generating a synchronization signal) or both.
                                          This parameter can be a combination of @ref HRTIM_Synchronization_Options.*/
  uint32_t SyncInputSource;          /*!< Specifies the external synchronization input source (significant only when
                                          the HRTIM instance is configured as a slave).
                                          This parameter can be a value of @ref HRTIM_Synchronization_Input_Source. */
  uint32_t SyncOutputSource;         /*!< Specifies the source and event to be sent on the external synchronization outputs
                                         (significant only when the HRTIM instance is configured as a master).
                                          This parameter can be a value of @ref HRTIM_Synchronization_Output_Source */
  uint32_t SyncOutputPolarity;       /*!< Specifies the conditioning of the event to be sent on the external synchronization
                                          outputs (significant only when the HRTIM instance is configured as a master).
                                          This parameter can be a value of @ref HRTIM_Synchronization_Output_Polarity */
} HRTIM_InitTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_HRTIM_STATE_RESET            = 0x00U,    /*!< Peripheral is not yet Initialized                  */
  HAL_HRTIM_STATE_READY            = 0x01U,    /*!< Peripheral Initialized and ready for use           */
  HAL_HRTIM_STATE_BUSY             = 0x02U,    /*!< an internal process is ongoing                     */
  HAL_HRTIM_STATE_TIMEOUT          = 0x06U,    /*!< Timeout state                                      */
  HAL_HRTIM_STATE_ERROR            = 0x07U,    /*!< Error state                                        */
#if (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
  HAL_HRTIM_STATE_INVALID_CALLBACK = 0x08U    /*!< Invalid Callback error */
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
} HAL_HRTIM_StateTypeDef;

/**
  * @brief HRTIM Timer Structure definition
  */
typedef struct
{
  uint32_t CaptureTrigger1;       /*!< Event(s) triggering capture unit 1.
                                       When the timer operates in Simple mode, this parameter can be a value of @ref HRTIM_External_Event_Channels.
                                       When the timer operates in Waveform mode, this parameter can be a combination of @ref HRTIM_Capture_Unit_Trigger. */
  uint32_t CaptureTrigger2;       /*!< Event(s) triggering capture unit 2.
                                       When the timer operates in Simple mode, this parameter can be a value of @ref HRTIM_External_Event_Channels.
                                       When the timer operates in Waveform mode, this parameter can be a combination of @ref HRTIM_Capture_Unit_Trigger. */
  uint32_t InterruptRequests;     /*!< Interrupts requests enabled for the timer. */
  uint32_t DMARequests;           /*!< DMA requests enabled for the timer. */
  uint32_t DMASrcAddress;          /*!< Address of the source address of the DMA transfer. */
  uint32_t DMADstAddress;          /*!< Address of the destination address of the DMA transfer. */
  uint32_t DMASize;                /*!< Size of the DMA transfer */
} HRTIM_TimerParamTypeDef;

/**
  * @brief  HRTIM Handle Structure definition
  */
#if (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
typedef struct __HRTIM_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
{
  HRTIM_TypeDef *              Instance;                     /*!< Register base address */

  HRTIM_InitTypeDef            Init;                         /*!< HRTIM required parameters */

  HRTIM_TimerParamTypeDef      TimerParam[MAX_HRTIM_TIMER];  /*!< HRTIM timers - including the master - parameters */

  HAL_LockTypeDef              Lock;                         /*!< Locking object          */

  __IO HAL_HRTIM_StateTypeDef  State;                        /*!< HRTIM communication state */

  DMA_HandleTypeDef *          hdmaMaster;                   /*!< Master timer DMA handle parameters */
  DMA_HandleTypeDef *          hdmaTimerA;                   /*!< Timer A DMA handle parameters */
  DMA_HandleTypeDef *          hdmaTimerB;                   /*!< Timer B DMA handle parameters */
  DMA_HandleTypeDef *          hdmaTimerC;                   /*!< Timer C DMA handle parameters */
  DMA_HandleTypeDef *          hdmaTimerD;                   /*!< Timer D DMA handle parameters */
  DMA_HandleTypeDef *          hdmaTimerE;                   /*!< Timer E DMA handle parameters */

#if (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
  void (* Fault1Callback)(struct __HRTIM_HandleTypeDef *hhrtim);                               /*!< Fault 1 interrupt callback function pointer                         */
  void (* Fault2Callback)(struct __HRTIM_HandleTypeDef *hhrtim);                               /*!< Fault 2 interrupt callback function pointer                         */
  void (* Fault3Callback)(struct __HRTIM_HandleTypeDef *hhrtim);                               /*!< Fault 3 interrupt callback function pointer                         */
  void (* Fault4Callback)(struct __HRTIM_HandleTypeDef *hhrtim);                               /*!< Fault 4 interrupt callback function pointer                         */
  void (* Fault5Callback)(struct __HRTIM_HandleTypeDef *hhrtim);                               /*!< Fault 5 interrupt callback function pointer                         */
  void (* SystemFaultCallback)(struct __HRTIM_HandleTypeDef *hhrtim);                          /*!< System fault interrupt callback function pointer                    */
  void (* BurstModePeriodCallback)(struct __HRTIM_HandleTypeDef *hhrtim);                      /*!< Burst mode period interrupt callback function pointer               */
  void (* SynchronizationEventCallback)(struct __HRTIM_HandleTypeDef *hhrtim);                 /*!< Sync Input interrupt callback function pointer                      */
  void (* ErrorCallback)(struct __HRTIM_HandleTypeDef *hhrtim);                                /*!< DMA error callback function pointer                                 */

  void (* RegistersUpdateCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);   /*!< Timer x Update interrupt callback function pointer                  */
  void (* RepetitionEventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);   /*!< Timer x Repetition interrupt callback function pointer              */
  void (* Compare1EventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);     /*!< Timer x Compare 1 match interrupt callback function pointer         */
  void (* Compare2EventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);     /*!< Timer x Compare 2 match interrupt callback function pointer         */
  void (* Compare3EventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);     /*!< Timer x Compare 3 match interrupt callback function pointer         */
  void (* Compare4EventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);     /*!< Timer x Compare 4 match interrupt callback function pointer         */
  void (* Capture1EventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);     /*!< Timer x Capture 1 interrupts callback function pointer              */
  void (* Capture2EventCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);     /*!< Timer x Capture 2 interrupts callback function pointer              */
  void (* DelayedProtectionCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx); /*!< Timer x Delayed protection interrupt callback function pointer      */
  void (* CounterResetCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);      /*!< Timer x counter reset/roll-over interrupt callback function pointer */
  void (* Output1SetCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);        /*!< Timer x output 1 set interrupt callback function pointer            */
  void (* Output1ResetCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);      /*!< Timer x output 1 reset interrupt callback function pointer          */
  void (* Output2SetCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);        /*!< Timer x output 2 set interrupt callback function pointer            */
  void (* Output2ResetCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);      /*!< Timer x output 2 reset interrupt callback function pointer          */
  void (* BurstDMATransferCallback)(struct __HRTIM_HandleTypeDef *hhrtim, uint32_t TimerIdx);  /*!< Timer x Burst DMA completed interrupt callback function pointer     */

  void (* MspInitCallback)(struct __HRTIM_HandleTypeDef *hhrtim);                              /*!< HRTIM MspInit callback function pointer                             */
  void (* MspDeInitCallback)(struct __HRTIM_HandleTypeDef *hhrtim);                            /*!< HRTIM MspInit callback function pointer                             */
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */
} HRTIM_HandleTypeDef;

/**
  * @brief  Simple output compare mode configuration definition
  */
typedef struct
{
  uint32_t Period;                   /*!< Specifies the timer period.
                                          The period value must be above 3 periods of the fHRTIM clock.
                                          Maximum value is = 0xFFDFU */
  uint32_t RepetitionCounter;        /*!< Specifies the timer repetition period.
                                          This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF. */
  uint32_t PrescalerRatio;           /*!< Specifies the timer clock prescaler ratio.
                                          This parameter can be any value of @ref HRTIM_Prescaler_Ratio   */
  uint32_t Mode;                     /*!< Specifies the counter operating mode.
                                          This parameter can be any value of @ref HRTIM_Counter_Operating_Mode   */
} HRTIM_TimeBaseCfgTypeDef;

/**
  * @brief  Simple output compare mode configuration definition
  */
typedef struct
{
  uint32_t Mode;       /*!< Specifies the output compare mode (toggle, active, inactive).
                            This parameter can be any value of of @ref HRTIM_Simple_OC_Mode */
  uint32_t Pulse;      /*!< Specifies the compare value to be loaded into the Compare Register.
                            The compare value must be above or equal to 3 periods of the fHRTIM clock */
  uint32_t Polarity;   /*!< Specifies the output polarity.
                            This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t IdleLevel;  /*!< Specifies whether the output level is active or inactive when in IDLE state.
                            This parameter can be any value of @ref HRTIM_Output_IDLE_Level */
} HRTIM_SimpleOCChannelCfgTypeDef;

/**
  * @brief  Simple PWM output mode configuration definition
  */
typedef struct
{
  uint32_t Pulse;            /*!< Specifies the compare value to be loaded into the Compare Register.
                                  The compare value must be above or equal to 3 periods of the fHRTIM clock */
  uint32_t Polarity;        /*!< Specifies the output polarity.
                                 This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t IdleLevel;       /*!< Specifies whether the output level is active or inactive when in IDLE state.
                                 This parameter can be any value of @ref HRTIM_Output_IDLE_Level */
} HRTIM_SimplePWMChannelCfgTypeDef;

/**
  * @brief  Simple capture mode configuration definition
  */
typedef struct
{
  uint32_t Event;             /*!< Specifies the external event triggering the capture.
                                   This parameter can be any 'EEVx' value of @ref HRTIM_External_Event_Channels */
  uint32_t EventPolarity;     /*!< Specifies the polarity of the external event (in case of level sensitivity).
                                   This parameter can be a value of @ref HRTIM_External_Event_Polarity */
  uint32_t EventSensitivity;  /*!< Specifies the sensitivity of the external event.
                                   This parameter can be a value of @ref HRTIM_External_Event_Sensitivity */
  uint32_t EventFilter;       /*!< Defines the frequency used to sample the External Event and the length of the digital filter.
                                   This parameter can be a value of @ref HRTIM_External_Event_Filter */
} HRTIM_SimpleCaptureChannelCfgTypeDef;

/**
  * @brief  Simple One Pulse mode configuration definition
  */
typedef struct
{
  uint32_t Pulse;             /*!< Specifies the compare value to be loaded into the Compare Register.
                                   The compare value must be above or equal to 3 periods of the fHRTIM clock */
  uint32_t OutputPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t OutputIdleLevel;   /*!< Specifies whether the output level is active or inactive when in IDLE state.
                                   This parameter can be any value of @ref HRTIM_Output_IDLE_Level */
  uint32_t Event;             /*!< Specifies the external event triggering the pulse generation.
                                   This parameter can be any 'EEVx' value of @ref HRTIM_External_Event_Channels */
  uint32_t EventPolarity;     /*!< Specifies the polarity of the external event (in case of level sensitivity).
                                   This parameter can be a value of @ref HRTIM_External_Event_Polarity */
  uint32_t EventSensitivity;  /*!< Specifies the sensitivity of the external event.
                                   This parameter can be a value of @ref HRTIM_External_Event_Sensitivity. */
  uint32_t EventFilter;       /*!< Defines the frequency used to sample the External Event and the length of the digital filter.
                                   This parameter can be a value of @ref HRTIM_External_Event_Filter */
} HRTIM_SimpleOnePulseChannelCfgTypeDef;

/**
  * @brief  Timer configuration definition
  */
typedef struct
{
  uint32_t InterruptRequests;      /*!< Relevant for all HRTIM timers, including the master.
                                       Specifies which interrupts requests must enabled for the timer.
                                       This parameter can be any combination of  @ref HRTIM_Master_Interrupt_Enable
                                       or @ref HRTIM_Timing_Unit_Interrupt_Enable */
  uint32_t DMARequests;            /*!< Relevant for all HRTIM timers, including the master.
                                       Specifies which DMA requests must be enabled for the timer.
                                       This parameter can be any combination of  @ref HRTIM_Master_DMA_Request_Enable
                                       or @ref HRTIM_Timing_Unit_DMA_Request_Enable */
  uint32_t DMASrcAddress;          /*!< Relevant for all HRTIM timers, including the master.
                                       Specifies the address of the source address of the DMA transfer */
  uint32_t DMADstAddress;          /*!< Relevant for all HRTIM timers, including the master.
                                       Specifies the address of the destination address of the DMA transfer */
  uint32_t DMASize;                /*!< Relevant for all HRTIM timers, including the master.
                                       Specifies the size of the DMA transfer */
  uint32_t HalfModeEnable;         /*!< Relevant for all HRTIM timers, including the master.
                                        Specifies whether or not half mode is enabled
                                        This parameter can be any value of @ref HRTIM_Half_Mode_Enable  */
  uint32_t StartOnSync;            /*!< Relevant for all HRTIM timers, including the master.
                                       Specifies whether or not timer is reset by a rising edge on the synchronization input (when enabled).
                                        This parameter can be any value of @ref HRTIM_Start_On_Sync_Input_Event  */
  uint32_t ResetOnSync;            /*!< Relevant for all HRTIM timers, including the master.
                                        Specifies whether or not timer is reset by a rising edge on the synchronization input (when enabled).
                                        This parameter can be any value of @ref HRTIM_Reset_On_Sync_Input_Event  */
  uint32_t DACSynchro;             /*!< Relevant for all HRTIM timers, including the master.
                                        Indicates whether or not the a DAC synchronization event is generated.
                                        This parameter can be any value of @ref HRTIM_DAC_Synchronization   */
  uint32_t PreloadEnable;          /*!< Relevant for all HRTIM timers, including the master.
                                        Specifies whether or not register preload is enabled.
                                        This parameter can be any value of @ref HRTIM_Register_Preload_Enable  */
  uint32_t UpdateGating;           /*!< Relevant for all HRTIM timers, including the master.
                                        Specifies how the update occurs with respect to a burst DMA transaction or
                                        update enable inputs (Slave timers only).
                                        This parameter can be any value of @ref HRTIM_Update_Gating   */
  uint32_t BurstMode;              /*!< Relevant for all HRTIM timers, including the master.
                                        Specifies how the timer behaves during a burst mode operation.
                                        This parameter can be any value of @ref HRTIM_Timer_Burst_Mode  */
  uint32_t RepetitionUpdate;       /*!< Relevant for all HRTIM timers, including the master.
                                        Specifies whether or not registers update is triggered by the repetition event.
                                        This parameter can be any value of @ref HRTIM_Timer_Repetition_Update */
  uint32_t PushPull;               /*!< Relevant for Timer A to Timer E.
                                        Specifies whether or not the push-pull mode is enabled.
                                        This parameter can be any value of @ref HRTIM_Timer_Push_Pull_Mode */
  uint32_t FaultEnable;            /*!< Relevant for Timer A to Timer E.
                                        Specifies which fault channels are enabled for the timer.
                                        This parameter can be a combination of @ref HRTIM_Timer_Fault_Enabling  */
  uint32_t FaultLock;              /*!< Relevant for Timer A to Timer E.
                                        Specifies whether or not fault enabling status is write protected.
                                        This parameter can be a value of @ref HRTIM_Timer_Fault_Lock */
  uint32_t DeadTimeInsertion;      /*!< Relevant for Timer A to Timer E.
                                        Specifies whether or not dead-time insertion is enabled for the timer.
                                        This parameter can be a value of @ref HRTIM_Timer_Deadtime_Insertion */
  uint32_t DelayedProtectionMode;  /*!< Relevant for Timer A to Timer E.
                                        Specifies the delayed protection mode.
                                        This parameter can be a value of @ref HRTIM_Timer_Delayed_Protection_Mode */
  uint32_t UpdateTrigger;          /*!< Relevant for Timer A to Timer E.
                                        Specifies source(s) triggering the timer registers update.
                                        This parameter can be a combination of @ref HRTIM_Timer_Update_Trigger */
  uint32_t ResetTrigger;           /*!< Relevant for Timer A to Timer E.
                                        Specifies source(s) triggering the timer counter reset.
                                        This parameter can be a combination of @ref HRTIM_Timer_Reset_Trigger */
  uint32_t ResetUpdate;           /*!<  Relevant for Timer A to Timer E.
                                        Specifies whether or not registers update is triggered when the timer counter is reset.
                                        This parameter can be a value of @ref HRTIM_Timer_Reset_Update */
} HRTIM_TimerCfgTypeDef;

/**
  * @brief  Compare unit configuration definition
  */
typedef struct
{
  uint32_t CompareValue;         /*!< Specifies the compare value of the timer compare unit.
                                      The minimum value must be greater than or equal to 3 periods of the fHRTIM clock.
                                      The maximum value must be less than or equal to 0xFFFFU - 1 periods of the fHRTIM clock */
  uint32_t AutoDelayedMode;      /*!< Specifies the auto delayed mode for compare unit 2 or 4.
                                      This parameter can be a value of @ref HRTIM_Compare_Unit_Auto_Delayed_Mode */
  uint32_t AutoDelayedTimeout;   /*!< Specifies compare value for timing unit 1 or 3 when auto delayed mode with time out is selected.
                                      CompareValue +  AutoDelayedTimeout must be less than 0xFFFFU */
} HRTIM_CompareCfgTypeDef;

/**
  * @brief  Capture unit configuration definition
  */
typedef struct
{
  uint32_t Trigger;          /*!< Specifies source(s) triggering the capture.
                                  This parameter can be a combination of @ref HRTIM_Capture_Unit_Trigger */
} HRTIM_CaptureCfgTypeDef;

/**
  * @brief  Output configuration definition
  */
typedef struct
{
  uint32_t Polarity;                    /*!< Specifies the output polarity.
                                             This parameter can be any value of @ref HRTIM_Output_Polarity */
  uint32_t SetSource;                   /*!< Specifies the event(s) transitioning the output from its inactive level to its active level.
                                             This parameter can be a combination of @ref HRTIM_Output_Set_Source */
  uint32_t ResetSource;                 /*!< Specifies the event(s) transitioning the output from its active level to its inactive level.
                                             This parameter can be a combination of @ref HRTIM_Output_Reset_Source */
  uint32_t IdleMode;                    /*!< Specifies whether or not the output is affected by a burst mode operation.
                                             This parameter can be any value of @ref HRTIM_Output_Idle_Mode */
  uint32_t IdleLevel;                   /*!< Specifies whether the output level is active or inactive when in IDLE state.
                                             This parameter can be any value of @ref HRTIM_Output_IDLE_Level */
  uint32_t FaultLevel;                  /*!< Specifies whether the output level is active or inactive when in FAULT state.
                                             This parameter can be any value of @ref HRTIM_Output_FAULT_Level */
  uint32_t ChopperModeEnable;           /*!< Indicates whether or not the chopper mode is enabled
                                             This parameter can be any value of @ref HRTIM_Output_Chopper_Mode_Enable */
  uint32_t BurstModeEntryDelayed;       /*!< Indicates whether or not dead-time is inserted when entering the IDLE state during a burst mode operation.
                                             This parameters can be any value of @ref HRTIM_Output_Burst_Mode_Entry_Delayed */
} HRTIM_OutputCfgTypeDef;

/**
  * @brief  External event filtering in timing units configuration definition
  */
typedef struct
{
  uint32_t Filter;       /*!< Specifies the type of event filtering within the timing unit.
                             This parameter can be a value of @ref HRTIM_Timer_External_Event_Filter */
  uint32_t Latch;       /*!< Specifies whether or not the signal is latched.
                             This parameter can be a value of @ref HRTIM_Timer_External_Event_Latch */
} HRTIM_TimerEventFilteringCfgTypeDef;

/**
  * @brief  Dead time feature configuration definition
  */
typedef struct
{
  uint32_t Prescaler;        /*!< Specifies the dead-time prescaler.
                                  This parameter can be a value of @ref  HRTIM_Deadtime_Prescaler_Ratio */
  uint32_t RisingValue;      /*!< Specifies the dead-time following a rising edge.
                                  This parameter can be a number between 0x0 and 0x1FFU */
  uint32_t RisingSign;       /*!< Specifies whether the dead-time is positive or negative on rising edge.
                                  This parameter can be a value of @ref HRTIM_Deadtime_Rising_Sign */
  uint32_t RisingLock;       /*!< Specifies whether or not dead-time rising settings (value and sign) are write protected.
                                  This parameter can be a value of @ref HRTIM_Deadtime_Rising_Lock */
  uint32_t RisingSignLock;   /*!< Specifies whether or not dead-time rising sign is write protected.
                                  This parameter can be a value of @ref HRTIM_Deadtime_Rising_Sign_Lock */
  uint32_t FallingValue;     /*!< Specifies the dead-time following a falling edge.
                                  This parameter can be a number between 0x0 and 0x1FFU */
  uint32_t FallingSign;      /*!< Specifies whether the dead-time is positive or negative on falling edge.
                                  This parameter can be a value of @ref HRTIM_Deadtime_Falling_Sign */
  uint32_t FallingLock;      /*!< Specifies whether or not dead-time falling settings (value and sign) are write protected.
                                  This parameter can be a value of @ref HRTIM_Deadtime_Falling_Lock */
  uint32_t FallingSignLock;  /*!< Specifies whether or not dead-time falling sign is write protected.
                                  This parameter can be a value of @ref HRTIM_Deadtime_Falling_Sign_Lock */
} HRTIM_DeadTimeCfgTypeDef;

/**
  * @brief  Chopper mode configuration definition
  */
typedef struct
{
  uint32_t CarrierFreq;  /*!< Specifies the Timer carrier frequency value.
                              This parameter can be a value of @ref HRTIM_Chopper_Frequency */
  uint32_t DutyCycle;    /*!< Specifies the Timer chopper duty cycle value.
                              This parameter can be a value of @ref HRTIM_Chopper_Duty_Cycle */
  uint32_t StartPulse;   /*!< Specifies the Timer pulse width value.
                              This parameter can be a value of @ref HRTIM_Chopper_Start_Pulse_Width */
} HRTIM_ChopperModeCfgTypeDef;

/**
  * @brief  External event channel configuration definition
  */
typedef struct
{
  uint32_t Source;        /*!< Identifies the source of the external event.
                               This parameter can be a value of @ref HRTIM_External_Event_Sources */
  uint32_t Polarity;      /*!< Specifies the polarity of the external event (in case of level sensitivity).
                               This parameter can be a value of @ref HRTIM_External_Event_Polarity */
  uint32_t Sensitivity;   /*!< Specifies the sensitivity of the external event.
                               This parameter can be a value of @ref HRTIM_External_Event_Sensitivity */
  uint32_t Filter;        /*!< Defines the frequency used to sample the External Event and the length of the digital filter.
                               This parameter can be a value of @ref HRTIM_External_Event_Filter */
  uint32_t FastMode;      /*!< Indicates whether or not low latency mode is enabled for the external event.
                               This parameter can be a value of @ref HRTIM_External_Event_Fast_Mode */
} HRTIM_EventCfgTypeDef;

/**
  * @brief  Fault channel configuration definition
  */
typedef struct
{
  uint32_t Source;        /*!< Identifies the source of the fault.
                               This parameter can be a value of @ref HRTIM_Fault_Sources */
  uint32_t Polarity;      /*!< Specifies the polarity of the fault event.
                               This parameter can be a value of @ref HRTIM_Fault_Polarity */
  uint32_t Filter;        /*!< Defines the frequency used to sample the Fault input and the length of the digital filter.
                               This parameter can be a value of @ref HRTIM_Fault_Filter */
  uint32_t Lock;          /*!< Indicates whether or not fault programming bits are write protected.
                               This parameter can be a value of @ref HRTIM_Fault_Lock */
} HRTIM_FaultCfgTypeDef;

/**
  * @brief  Burst mode configuration definition
  */
typedef struct
{
  uint32_t Mode;           /*!< Specifies the burst mode operating mode.
                                This parameter can be a value of @ref HRTIM_Burst_Mode_Operating_Mode */
  uint32_t ClockSource;    /*!< Specifies the burst mode clock source.
                                This parameter can be a value of @ref HRTIM_Burst_Mode_Clock_Source */
  uint32_t Prescaler;      /*!< Specifies the burst mode prescaler.
                                This parameter can be a value of @ref HRTIM_Burst_Mode_Prescaler */
  uint32_t PreloadEnable;  /*!< Specifies whether or not preload is enabled for burst mode related registers (HRTIM_BMCMPR and HRTIM_BMPER).
                                This parameter can be a combination of @ref HRTIM_Burst_Mode_Register_Preload_Enable  */
  uint32_t Trigger;        /*!< Specifies the event(s) triggering the burst operation.
                                This parameter can be a combination of @ref HRTIM_Burst_Mode_Trigger  */
  uint32_t IdleDuration;   /*!< Specifies number of periods during which the selected timers are in idle state.
                                This parameter can be a number between 0x0 and 0xFFFF  */
  uint32_t Period;         /*!< Specifies burst mode repetition period.
                                This parameter can be a number between 0x1 and 0xFFFF  */
} HRTIM_BurstModeCfgTypeDef;

/**
  * @brief  ADC trigger configuration definition
  */
typedef struct
{
  uint32_t UpdateSource;  /*!< Specifies the ADC trigger update source.
                               This parameter can be a value of @ref HRTIM_ADC_Trigger_Update_Source  */
  uint32_t Trigger;       /*!< Specifies the event(s) triggering the ADC conversion.
                               This parameter can be a combination of @ref HRTIM_ADC_Trigger_Event  */
} HRTIM_ADCTriggerCfgTypeDef;

#if (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL HRTIM Callback ID enumeration definition
  */
typedef enum {
  HAL_HRTIM_FAULT1CALLBACK_CB_ID               = 0x00U, /*!< Fault 1 interrupt callback ID                         */
  HAL_HRTIM_FAULT2CALLBACK_CB_ID               = 0x01U, /*!< Fault 2 interrupt callback ID                         */
  HAL_HRTIM_FAULT3CALLBACK_CB_ID               = 0x02U, /*!< Fault 3 interrupt callback ID                         */
  HAL_HRTIM_FAULT4CALLBACK_CB_ID               = 0x03U, /*!< Fault 4 interrupt callback ID                         */
  HAL_HRTIM_FAULT5CALLBACK_CB_ID               = 0x04U, /*!< Fault 5 interrupt callback ID                         */
  HAL_HRTIM_SYSTEMFAULTCALLBACK_CB_ID          = 0x05U, /*!< System fault interrupt callback ID                    */
  HAL_HRTIM_BURSTMODEPERIODCALLBACK_CB_ID      = 0x07U, /*!< Burst mode period interrupt callback ID               */
  HAL_HRTIM_SYNCHRONIZATIONEVENTCALLBACK_CB_ID = 0x08U, /*!< Sync Input interrupt callback ID                      */
  HAL_HRTIM_ERRORCALLBACK_CB_ID                = 0x09U, /*!< DMA error callback ID                                 */

  HAL_HRTIM_REGISTERSUPDATECALLBACK_CB_ID      = 0x10U, /*!< Timer x Update interrupt callback ID                  */
  HAL_HRTIM_REPETITIONEVENTCALLBACK_CB_ID      = 0x11U, /*!< Timer x Repetition interrupt callback ID              */
  HAL_HRTIM_COMPARE1EVENTCALLBACK_CB_ID        = 0x12U, /*!< Timer x Compare 1 match interrupt callback ID         */
  HAL_HRTIM_COMPARE2EVENTCALLBACK_CB_ID        = 0x13U, /*!< Timer x Compare 2 match interrupt callback ID         */
  HAL_HRTIM_COMPARE3EVENTCALLBACK_CB_ID        = 0x14U, /*!< Timer x Compare 3 match interrupt callback ID         */
  HAL_HRTIM_COMPARE4EVENTCALLBACK_CB_ID        = 0x15U, /*!< Timer x Compare 4 match interrupt callback ID         */
  HAL_HRTIM_CAPTURE1EVENTCALLBACK_CB_ID        = 0x16U, /*!< Timer x Capture 1 interrupts callback ID              */
  HAL_HRTIM_CAPTURE2EVENTCALLBACK_CB_ID        = 0x17U, /*!< Timer x Capture 2 interrupts callback ID              */
  HAL_HRTIM_DELAYEDPROTECTIONCALLBACK_CB_ID    = 0x18U, /*!< Timer x Delayed protection interrupt callback ID      */
  HAL_HRTIM_COUNTERRESETCALLBACK_CB_ID         = 0x19U, /*!< Timer x counter reset/roll-over interrupt callback ID */
  HAL_HRTIM_OUTPUT1SETCALLBACK_CB_ID           = 0x1AU, /*!< Timer x output 1 set interrupt callback ID            */
  HAL_HRTIM_OUTPUT1RESETCALLBACK_CB_ID         = 0x1BU, /*!< Timer x output 1 reset interrupt callback ID          */
  HAL_HRTIM_OUTPUT2SETCALLBACK_CB_ID           = 0x1CU, /*!< Timer x output 2 set interrupt callback ID            */
  HAL_HRTIM_OUTPUT2RESETCALLBACK_CB_ID         = 0x1DU, /*!< Timer x output 2 reset interrupt callback ID          */
  HAL_HRTIM_BURSTDMATRANSFERCALLBACK_CB_ID     = 0x1EU, /*!< Timer x Burst DMA completed interrupt callback ID     */

  HAL_HRTIM_MSPINIT_CB_ID                      = 0x20U, /*!< HRTIM MspInit callback ID                             */
  HAL_HRTIM_MSPDEINIT_CB_ID                    = 0x21U, /*!< HRTIM MspInit callback ID                             */
}HAL_HRTIM_CallbackIDTypeDef;

/**
  * @brief  HAL HRTIM Callback function pointer definitions
  */
typedef void (* pHRTIM_CallbackTypeDef)(HRTIM_HandleTypeDef *hhrtim);       /*!< HRTIM related callback function pointer         */

typedef void (* pHRTIM_TIMxCallbackTypeDef)(HRTIM_HandleTypeDef *hhrtim,    /*!< HRTIM Timer x related callback function pointer */
                                            uint32_t TimerIdx);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Constants HRTIM Exported Constants
  * @{
  */

/** @defgroup HRTIM_Timer_Index HRTIM Timer Index
  * @{
  * @brief Constants defining the timer indexes
  */
#define HRTIM_TIMERINDEX_TIMER_A 0x0U   /*!< Index used to access timer A registers */
#define HRTIM_TIMERINDEX_TIMER_B 0x1U   /*!< Index used to access timer B registers */
#define HRTIM_TIMERINDEX_TIMER_C 0x2U   /*!< Index used to access timer C registers */
#define HRTIM_TIMERINDEX_TIMER_D 0x3U   /*!< Index used to access timer D registers */
#define HRTIM_TIMERINDEX_TIMER_E 0x4U   /*!< Index used to access timer E registers */
#define HRTIM_TIMERINDEX_MASTER  0x5U   /*!< Index used to access master registers  */
#define HRTIM_TIMERINDEX_COMMON  0xFFU  /*!< Index used to access HRTIM common registers */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_identifier HRTIM Timer identifier
  * @{
  * @brief Constants defining timer identifiers
  */
#define HRTIM_TIMERID_MASTER  (HRTIM_MCR_MCEN)   /*!< Master identifier  */
#define HRTIM_TIMERID_TIMER_A (HRTIM_MCR_TACEN)  /*!< Timer A identifier */
#define HRTIM_TIMERID_TIMER_B (HRTIM_MCR_TBCEN)  /*!< Timer B identifier */
#define HRTIM_TIMERID_TIMER_C (HRTIM_MCR_TCCEN)  /*!< Timer C identifier */
#define HRTIM_TIMERID_TIMER_D (HRTIM_MCR_TDCEN)  /*!< Timer D identifier */
#define HRTIM_TIMERID_TIMER_E (HRTIM_MCR_TECEN)  /*!< Timer E identifier */
/**
 * @}
 */

/** @defgroup HRTIM_Compare_Unit HRTIM Compare Unit
  * @{
  * @brief Constants defining compare unit identifiers
  */
#define HRTIM_COMPAREUNIT_1 0x00000001U  /*!< Compare unit 1 identifier */
#define HRTIM_COMPAREUNIT_2 0x00000002U  /*!< Compare unit 2 identifier */
#define HRTIM_COMPAREUNIT_3 0x00000004U  /*!< Compare unit 3 identifier */
#define HRTIM_COMPAREUNIT_4 0x00000008U  /*!< Compare unit 4 identifier */
 /**
  * @}
  */

/** @defgroup HRTIM_Capture_Unit HRTIM Capture Unit
  * @{
  * @brief Constants defining capture unit identifiers
  */
#define HRTIM_CAPTUREUNIT_1 0x00000001U  /*!< Capture unit 1 identifier */
#define HRTIM_CAPTUREUNIT_2 0x00000002U  /*!< Capture unit 2 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Output HRTIM Timer Output
  * @{
  * @brief Constants defining timer output identifiers
  */
#define HRTIM_OUTPUT_TA1  0x00000001U  /*!< Timer A - Output 1 identifier */
#define HRTIM_OUTPUT_TA2  0x00000002U  /*!< Timer A - Output 2 identifier */
#define HRTIM_OUTPUT_TB1  0x00000004U  /*!< Timer B - Output 1 identifier */
#define HRTIM_OUTPUT_TB2  0x00000008U  /*!< Timer B - Output 2 identifier */
#define HRTIM_OUTPUT_TC1  0x00000010U  /*!< Timer C - Output 1 identifier */
#define HRTIM_OUTPUT_TC2  0x00000020U  /*!< Timer C - Output 2 identifier */
#define HRTIM_OUTPUT_TD1  0x00000040U  /*!< Timer D - Output 1 identifier */
#define HRTIM_OUTPUT_TD2  0x00000080U  /*!< Timer D - Output 2 identifier */
#define HRTIM_OUTPUT_TE1  0x00000100U  /*!< Timer E - Output 1 identifier */
#define HRTIM_OUTPUT_TE2  0x00000200U  /*!< Timer E - Output 2 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_ADC_Trigger HRTIM ADC Trigger
  * @{
  * @brief Constants defining ADC triggers identifiers
  */
#define HRTIM_ADCTRIGGER_1  0x00000001U  /*!< ADC trigger 1 identifier */
#define HRTIM_ADCTRIGGER_2  0x00000002U  /*!< ADC trigger 2 identifier */
#define HRTIM_ADCTRIGGER_3  0x00000004U  /*!< ADC trigger 3 identifier */
#define HRTIM_ADCTRIGGER_4  0x00000008U  /*!< ADC trigger 4 identifier */

#define IS_HRTIM_ADCTRIGGER(ADCTRIGGER)\
    (((ADCTRIGGER) == HRTIM_ADCTRIGGER_1)   || \
     ((ADCTRIGGER) == HRTIM_ADCTRIGGER_2)   || \
     ((ADCTRIGGER) == HRTIM_ADCTRIGGER_3)   || \
     ((ADCTRIGGER) == HRTIM_ADCTRIGGER_4))
/**
  * @}
  */
/** @defgroup HRTIM_External_Event_Channels HRTIM External Event Channels
  * @{
  * @brief Constants defining external event channel identifiers
  */
#define HRTIM_EVENT_NONE    (0x00000000U)     /*!< Undefined event channel */
#define HRTIM_EVENT_1       (0x00000001U)     /*!< External event channel 1  identifier */
#define HRTIM_EVENT_2       (0x00000002U)     /*!< External event channel 2  identifier */
#define HRTIM_EVENT_3       (0x00000003U)     /*!< External event channel 3  identifier */
#define HRTIM_EVENT_4       (0x00000004U)     /*!< External event channel 4  identifier */
#define HRTIM_EVENT_5       (0x00000005U)     /*!< External event channel 5  identifier */
#define HRTIM_EVENT_6       (0x00000006U)     /*!< External event channel 6  identifier */
#define HRTIM_EVENT_7       (0x00000007U)     /*!< External event channel 7  identifier */
#define HRTIM_EVENT_8       (0x00000008U)     /*!< External event channel 8  identifier */
#define HRTIM_EVENT_9       (0x00000009U)     /*!< External event channel 9  identifier */
#define HRTIM_EVENT_10      (0x0000000AU)     /*!< External event channel 10 identifier */
/**
  * @}
  */

/** @defgroup HRTIM_Fault_Channel HRTIM Fault Channel
  * @{
  * @brief Constants defining fault channel identifiers
  */
#define HRTIM_FAULT_1      (0x01U)     /*!< Fault channel 1 identifier */
#define HRTIM_FAULT_2      (0x02U)     /*!< Fault channel 2 identifier */
#define HRTIM_FAULT_3      (0x04U)     /*!< Fault channel 3 identifier */
#define HRTIM_FAULT_4      (0x08U)     /*!< Fault channel 4 identifier */
#define HRTIM_FAULT_5      (0x10U)     /*!< Fault channel 5 identifier */
/**
  * @}
  */


 /** @defgroup HRTIM_Prescaler_Ratio HRTIM Prescaler Ratio
  * @{
  * @brief Constants defining timer high-resolution clock prescaler ratio.
  */
#define HRTIM_PRESCALERRATIO_DIV1     (0x00000005U)  /*!< fHRCK: fHRTIM = 144 MHz - Resolution: 6.95 ns - Min PWM frequency: 2.2 kHz (fHRTIM=144MHz)         */
#define HRTIM_PRESCALERRATIO_DIV2     (0x00000006U)  /*!< fHRCK: fHRTIM / 2U = 72 MHz - Resolution: 13.88 ns- Min PWM frequency: 1.1 kHz (fHRTIM=144MHz)     */
#define HRTIM_PRESCALERRATIO_DIV4     (0x00000007U)  /*!< fHRCK: fHRTIM / 4U = 36 MHz - Resolution: 27.7 ns- Min PWM frequency: 550Hz (fHRTIM=144MHz)        */
/**
  * @}
  */

/** @defgroup HRTIM_Counter_Operating_Mode HRTIM Counter Operating Mode
  * @{
  * @brief Constants defining timer counter operating mode.
  */
#define HRTIM_MODE_CONTINUOUS               (0x00000008U)  /*!< The timer operates in continuous (free-running) mode */
#define HRTIM_MODE_SINGLESHOT               (0x00000000U)  /*!< The timer operates in non retriggerable single-shot mode */
#define HRTIM_MODE_SINGLESHOT_RETRIGGERABLE (0x00000010U)  /*!< The timer operates in retriggerable single-shot mode */
/**
  * @}
  */

/** @defgroup HRTIM_Half_Mode_Enable HRTIM Half Mode Enable
  * @{
  * @brief Constants defining half mode enabling status.
  */
#define HRTIM_HALFMODE_DISABLED (0x00000000U)  /*!< Half mode is disabled */
#define HRTIM_HALFMODE_ENABLED  (0x00000020U)  /*!< Half mode is enabled */
/**
  * @}
  */

/** @defgroup HRTIM_Start_On_Sync_Input_Event HRTIM Start On Sync Input Event
  * @{
  * @brief Constants defining the timer behavior following the synchronization event
  */
#define HRTIM_SYNCSTART_DISABLED (0x00000000U)           /*!< Synchronization input event has effect on the timer */
#define HRTIM_SYNCSTART_ENABLED  (HRTIM_MCR_SYNCSTRTM)   /*!< Synchronization input event starts the timer */
/**
  * @}
  */

/** @defgroup HRTIM_Reset_On_Sync_Input_Event HRTIM Reset On Sync Input Event
  * @{
  * @brief Constants defining the timer behavior following the synchronization event
  */
#define HRTIM_SYNCRESET_DISABLED (0x00000000U)           /*!< Synchronization input event has effect on the timer */
#define HRTIM_SYNCRESET_ENABLED  (HRTIM_MCR_SYNCRSTM)    /*!< Synchronization input event resets the timer */
/**
  * @}
  */

/** @defgroup HRTIM_DAC_Synchronization HRTIM DAC Synchronization
  * @{
  * @brief Constants defining on which output the DAC synchronization event is sent
  */
#define HRTIM_DACSYNC_NONE          0x00000000U                                 /*!< No DAC synchronization event generated */
#define HRTIM_DACSYNC_DACTRIGOUT_1  (HRTIM_MCR_DACSYNC_0)                       /*!< DAC synchronization event generated on DACTrigOut1 output upon timer update */
#define HRTIM_DACSYNC_DACTRIGOUT_2  (HRTIM_MCR_DACSYNC_1)                       /*!< DAC synchronization event generated on DACTrigOut2 output upon timer update */
#define HRTIM_DACSYNC_DACTRIGOUT_3  (HRTIM_MCR_DACSYNC_1 | HRTIM_MCR_DACSYNC_0) /*!< DAC update generated on DACTrigOut3 output upon timer update */
/**
  * @}
  */

/** @defgroup HRTIM_Register_Preload_Enable HRTIM Register Preload Enable
  * @{
  * @brief Constants defining whether a write access into a preloadable
  *        register is done into the active or the preload register.
  */
#define HRTIM_PRELOAD_DISABLED (0x00000000U)           /*!< Preload disabled: the write access is directly done into the active register */
#define HRTIM_PRELOAD_ENABLED  (HRTIM_MCR_PREEN)       /*!< Preload enabled: the write access is done into the preload register */
/**
  * @}
  */

/** @defgroup HRTIM_Update_Gating HRTIM Update Gating
  * @{
  * @brief Constants defining how the update occurs relatively to the burst DMA
  *        transaction and the external update request on update enable inputs 1 to 3.
  */
#define HRTIM_UPDATEGATING_INDEPENDENT     0x00000000U                                                           /*!< Update done independently from the DMA burst transfer completion */
#define HRTIM_UPDATEGATING_DMABURST        (HRTIM_TIMCR_UPDGAT_0)                                                /*!< Update done when the DMA burst transfer is completed */
#define HRTIM_UPDATEGATING_DMABURST_UPDATE (HRTIM_TIMCR_UPDGAT_1)                                                /*!< Update done on timer roll-over following a DMA burst transfer completion*/
#define HRTIM_UPDATEGATING_UPDEN1          (HRTIM_TIMCR_UPDGAT_1 | HRTIM_TIMCR_UPDGAT_0)                         /*!< Slave timer only - Update done on a rising edge of HRTIM update enable input 1U */
#define HRTIM_UPDATEGATING_UPDEN2          (HRTIM_TIMCR_UPDGAT_2)                                                /*!< Slave timer only - Update done on a rising edge of HRTIM update enable input 2U */
#define HRTIM_UPDATEGATING_UPDEN3          (HRTIM_TIMCR_UPDGAT_2 | HRTIM_TIMCR_UPDGAT_0)                         /*!< Slave timer only - Update done on a rising edge of HRTIM update enable input 3U */
#define HRTIM_UPDATEGATING_UPDEN1_UPDATE   (HRTIM_TIMCR_UPDGAT_2 | HRTIM_TIMCR_UPDGAT_1)                         /*!< Slave timer only -  Update done on the update event following a rising edge of HRTIM update enable input 1U */
#define HRTIM_UPDATEGATING_UPDEN2_UPDATE   (HRTIM_TIMCR_UPDGAT_2 | HRTIM_TIMCR_UPDGAT_1 | HRTIM_TIMCR_UPDGAT_0)  /*!< Slave timer only -  Update done on the update event following a rising edge of HRTIM update enable input 2U */
#define HRTIM_UPDATEGATING_UPDEN3_UPDATE   (HRTIM_TIMCR_UPDGAT_3)                                                /*!< Slave timer only -  Update done on the update event following a rising edge of HRTIM update enable input 3U */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Burst_Mode HRTIM Timer Burst Mode
  * @{
  * @brief Constants defining how the timer behaves during a burst
            mode operation.
  */
#define HRTIM_TIMERBURSTMODE_MAINTAINCLOCK 0x00000000U           /*!< Timer counter clock is maintained and the timer operates normally */
#define HRTIM_TIMERBURSTMODE_RESETCOUNTER  (HRTIM_BMCR_MTBM)     /*!< Timer counter clock is stopped and the counter is reset */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Repetition_Update HRTIM Timer Repetition Update
  * @{
  * @brief Constants defining whether registers are updated when the timer
  *        repetition period is completed (either due to roll-over or
  *        reset events)
  */
#define HRTIM_UPDATEONREPETITION_DISABLED  0x00000000U           /*!< Update on repetition disabled */
#define HRTIM_UPDATEONREPETITION_ENABLED   (HRTIM_MCR_MREPU)     /*!< Update on repetition enabled */
/**
  * @}
  */


/** @defgroup HRTIM_Timer_Push_Pull_Mode HRTIM Timer Push Pull Mode
  * @{
  * @brief Constants defining whether or not the push-pull mode is enabled for
  *        a timer.
  */
#define HRTIM_TIMPUSHPULLMODE_DISABLED     0x00000000U           /*!< Push-Pull mode disabled */
#define HRTIM_TIMPUSHPULLMODE_ENABLED      (HRTIM_TIMCR_PSHPLL)  /*!< Push-Pull mode enabled */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Fault_Enabling HRTIM Timer Fault Enabling
  * @{
  * @brief Constants defining whether a fault channel is enabled for a timer
  */
#define HRTIM_TIMFAULTENABLE_NONE     0x00000000U           /*!< No fault enabled */
#define HRTIM_TIMFAULTENABLE_FAULT1   (HRTIM_FLTR_FLT1EN)   /*!< Fault 1 enabled */
#define HRTIM_TIMFAULTENABLE_FAULT2   (HRTIM_FLTR_FLT2EN)   /*!< Fault 2 enabled */
#define HRTIM_TIMFAULTENABLE_FAULT3   (HRTIM_FLTR_FLT3EN)   /*!< Fault 3 enabled */
#define HRTIM_TIMFAULTENABLE_FAULT4   (HRTIM_FLTR_FLT4EN)   /*!< Fault 4 enabled */
#define HRTIM_TIMFAULTENABLE_FAULT5   (HRTIM_FLTR_FLT5EN)   /*!< Fault 5 enabled */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Fault_Lock HRTIM Timer Fault Lock
  * @{
  * @brief Constants defining whether or not fault enabling bits are write
  *        protected for a timer
  */
#define HRTIM_TIMFAULTLOCK_READWRITE (0x00000000U)           /*!< Timer fault enabling bits are read/write */
#define HRTIM_TIMFAULTLOCK_READONLY  (HRTIM_FLTR_FLTLCK)     /*!< Timer fault enabling bits are read only */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Deadtime_Insertion HRTIM Timer Dead-time Insertion
  * @{
  * @brief Constants defining whether or not fault the dead time insertion
  *        feature is enabled for a timer
  */
#define HRTIM_TIMDEADTIMEINSERTION_DISABLED   (0x00000000U)           /*!< Output 1 and output 2 signals are independent */
#define HRTIM_TIMDEADTIMEINSERTION_ENABLED    HRTIM_OUTR_DTEN         /*!< Dead-time is inserted between output 1 and output 2U */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Delayed_Protection_Mode HRTIM Timer Delayed Protection Mode
  * @{
  * @brief Constants defining all possible delayed protection modes
  *        for a timer. Also define the source and outputs on which the delayed
  *        protection schemes are applied
  */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED          (0x00000000U)                                                                           /*!< No action */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT1_EEV6  (HRTIM_OUTR_DLYPRTEN)                                                                   /*!< Timers A, B, C: Output 1 delayed Idle on external Event 6U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT2_EEV6  (HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                                             /*!< Timers A, B, C: Output 2 delayed Idle on external Event 6U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDBOTH_EEV6  (HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRTEN)                                             /*!< Timers A, B, C: Output 1 and output 2 delayed Idle on external Event 6U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_BALANCED_EEV6     (HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                       /*!< Timers A, B, C: Balanced Idle on external Event 6U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT1_DEEV7 (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRTEN)                                             /*!< Timers A, B, C: Output 1 delayed Idle on external Event 7U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT2_DEEV7 (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                       /*!< Timers A, B, C: Output 2 delayed Idle on external Event 7U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDBOTH_EEV7  (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRTEN)                       /*!< Timers A, B, C: Output 1 and output2 delayed Idle on external Event 7U */
#define HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_BALANCED_EEV7     (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN) /*!< Timers A, B, C: Balanced Idle on external Event 7U */

#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DISABLED            (0x00000000U)                                                                             /*!< No action */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DELAYEDOUT1_EEV8    (HRTIM_OUTR_DLYPRTEN)                                                                     /*!< Timers D, E: Output 1 delayed Idle on external Event 6U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DELAYEDOUT2_EEV8    (HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                                               /*!< Timers D, E: Output 2 delayed Idle on external Event 6U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DELAYEDBOTH_EEV8    (HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRTEN)                                               /*!< Timers D, E: Output 1 and output 2 delayed Idle on external Event 6U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_BALANCED_EEV8       (HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                         /*!< Timers D, E: Balanced Idle on external Event 6U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DELAYEDOUT1_DEEV9   (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRTEN)                                               /*!< Timers D, E: Output 1 delayed Idle on external Event 7U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DELAYEDOUT2_DEEV9   (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)                         /*!< Timers D, E: Output 2 delayed Idle on external Event 7U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_DELAYEDBOTH_EEV9    (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRTEN)                         /*!< Timers D, E: Output 1 and output2 delayed Idle on external Event 7U */
#define HRTIM_TIMER_D_E_DELAYEDPROTECTION_BALANCED_EEV9       (HRTIM_OUTR_DLYPRT_2 | HRTIM_OUTR_DLYPRT_1 | HRTIM_OUTR_DLYPRT_0 | HRTIM_OUTR_DLYPRTEN)   /*!< Timers D, E: Balanced Idle on external Event 7U */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Update_Trigger HRTIM Timer Update Trigger
  * @{
  * @brief Constants defining whether the registers update is done synchronously
  *        with any other timer or master update
  */
#define HRTIM_TIMUPDATETRIGGER_NONE     0x00000000U          /*!< Register update is disabled */
#define HRTIM_TIMUPDATETRIGGER_MASTER   (HRTIM_TIMCR_MSTU)   /*!< Register update is triggered by the master timer update */
#define HRTIM_TIMUPDATETRIGGER_TIMER_A  (HRTIM_TIMCR_TAU)    /*!< Register update is triggered by the timer A update */
#define HRTIM_TIMUPDATETRIGGER_TIMER_B  (HRTIM_TIMCR_TBU)    /*!< Register update is triggered by the timer B update */
#define HRTIM_TIMUPDATETRIGGER_TIMER_C  (HRTIM_TIMCR_TCU)    /*!< Register update is triggered by the timer C update*/
#define HRTIM_TIMUPDATETRIGGER_TIMER_D  (HRTIM_TIMCR_TDU)    /*!< Register update is triggered by the timer D update */
#define HRTIM_TIMUPDATETRIGGER_TIMER_E  (HRTIM_TIMCR_TEU)    /*!< Register update is triggered by the timer E update */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Reset_Trigger HRTIM Timer Reset Trigger
  * @{
  * @brief Constants defining the events that can be selected to trigger the reset
  *        of the timer counter
  */
#define HRTIM_TIMRESETTRIGGER_NONE        0x00000000U            /*!< No counter reset trigger */
#define HRTIM_TIMRESETTRIGGER_UPDATE      (HRTIM_RSTR_UPDATE)    /*!< The timer counter is reset upon update event */
#define HRTIM_TIMRESETTRIGGER_CMP2        (HRTIM_RSTR_CMP2)      /*!< The timer counter is reset upon Timer Compare 2 event */
#define HRTIM_TIMRESETTRIGGER_CMP4        (HRTIM_RSTR_CMP4)      /*!< The timer counter is reset upon Timer Compare 4 event */
#define HRTIM_TIMRESETTRIGGER_MASTER_PER  (HRTIM_RSTR_MSTPER)    /*!< The timer counter is reset upon master timer period event */
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP1 (HRTIM_RSTR_MSTCMP1)   /*!< The timer counter is reset upon master timer Compare 1 event */
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP2 (HRTIM_RSTR_MSTCMP2)   /*!< The timer counter is reset upon master timer Compare 2 event */
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP3 (HRTIM_RSTR_MSTCMP3)   /*!< The timer counter is reset upon master timer Compare 3 event */
#define HRTIM_TIMRESETTRIGGER_MASTER_CMP4 (HRTIM_RSTR_MSTCMP4)   /*!< The timer counter is reset upon master timer Compare 4 event */
#define HRTIM_TIMRESETTRIGGER_EEV_1       (HRTIM_RSTR_EXTEVNT1)  /*!< The timer counter is reset upon external event 1U */
#define HRTIM_TIMRESETTRIGGER_EEV_2       (HRTIM_RSTR_EXTEVNT2)  /*!< The timer counter is reset upon external event 2U */
#define HRTIM_TIMRESETTRIGGER_EEV_3       (HRTIM_RSTR_EXTEVNT3)  /*!< The timer counter is reset upon external event 3U */
#define HRTIM_TIMRESETTRIGGER_EEV_4       (HRTIM_RSTR_EXTEVNT4)  /*!< The timer counter is reset upon external event 4U */
#define HRTIM_TIMRESETTRIGGER_EEV_5       (HRTIM_RSTR_EXTEVNT5)  /*!< The timer counter is reset upon external event 5U */
#define HRTIM_TIMRESETTRIGGER_EEV_6       (HRTIM_RSTR_EXTEVNT6)  /*!< The timer counter is reset upon external event 6U */
#define HRTIM_TIMRESETTRIGGER_EEV_7       (HRTIM_RSTR_EXTEVNT7)  /*!< The timer counter is reset upon external event 7U */
#define HRTIM_TIMRESETTRIGGER_EEV_8       (HRTIM_RSTR_EXTEVNT8)  /*!< The timer counter is reset upon external event 8U */
#define HRTIM_TIMRESETTRIGGER_EEV_9       (HRTIM_RSTR_EXTEVNT9)  /*!< The timer counter is reset upon external event 9U */
#define HRTIM_TIMRESETTRIGGER_EEV_10      (HRTIM_RSTR_EXTEVNT10) /*!< The timer counter is reset upon external event 10U */
#define HRTIM_TIMRESETTRIGGER_OTHER1_CMP1 (HRTIM_RSTR_TIMBCMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */
#define HRTIM_TIMRESETTRIGGER_OTHER1_CMP2 (HRTIM_RSTR_TIMBCMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */
#define HRTIM_TIMRESETTRIGGER_OTHER1_CMP4 (HRTIM_RSTR_TIMBCMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */
#define HRTIM_TIMRESETTRIGGER_OTHER2_CMP1 (HRTIM_RSTR_TIMCCMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */
#define HRTIM_TIMRESETTRIGGER_OTHER2_CMP2 (HRTIM_RSTR_TIMCCMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */
#define HRTIM_TIMRESETTRIGGER_OTHER2_CMP4 (HRTIM_RSTR_TIMCCMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */
#define HRTIM_TIMRESETTRIGGER_OTHER3_CMP1 (HRTIM_RSTR_TIMDCMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */
#define HRTIM_TIMRESETTRIGGER_OTHER3_CMP2 (HRTIM_RSTR_TIMDCMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */
#define HRTIM_TIMRESETTRIGGER_OTHER3_CMP4 (HRTIM_RSTR_TIMDCMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */
#define HRTIM_TIMRESETTRIGGER_OTHER4_CMP1 (HRTIM_RSTR_TIMECMP1)  /*!< The timer counter is reset upon other timer Compare 1 event */
#define HRTIM_TIMRESETTRIGGER_OTHER4_CMP2 (HRTIM_RSTR_TIMECMP2)  /*!< The timer counter is reset upon other timer Compare 2 event */
#define HRTIM_TIMRESETTRIGGER_OTHER4_CMP4 (HRTIM_RSTR_TIMECMP4)  /*!< The timer counter is reset upon other timer Compare 4 event */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_Reset_Update HRTIM Timer Reset Update
  * @{
  * @brief Constants defining whether the register are updated upon Timerx
  *        counter reset or roll-over to 0 after reaching the period value
  *        in continuous mode
  */
#define HRTIM_TIMUPDATEONRESET_DISABLED 0x00000000U           /*!< Update by timer x reset / roll-over disabled */
#define HRTIM_TIMUPDATEONRESET_ENABLED (HRTIM_TIMCR_TRSTU)    /*!< Update by timer x reset / roll-over enabled */
/**
  * @}
  */

/** @defgroup HRTIM_Compare_Unit_Auto_Delayed_Mode HRTIM Compare Unit Auto Delayed Mode
  * @{
  * @brief Constants defining whether the compare register is behaving in
  *        regular mode (compare match issued as soon as counter equal compare),
  *        or in auto-delayed mode
  */
#define HRTIM_AUTODELAYEDMODE_REGULAR                 (0x00000000U)                                   /*!< standard compare mode */
#define HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT   (HRTIM_TIMCR_DELCMP2_0)                         /*!< Compare event generated only if a capture has occurred */
#define HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1 (HRTIM_TIMCR_DELCMP2_1)                         /*!< Compare event generated if a capture has occurred or after a Compare 1 match (timeout if capture event is missing) */
#define HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3 (HRTIM_TIMCR_DELCMP2_1 | HRTIM_TIMCR_DELCMP2_0) /*!< Compare event generated if a capture has occurred or after a Compare 3 match (timeout if capture event is missing) */
/**
  * @}
  */

/** @defgroup HRTIM_Simple_OC_Mode HRTIM Simple OC Mode
  * @{
  * @brief Constants defining the behavior of the output signal when the timer
           operates in basic output compare mode
  */
#define HRTIM_BASICOCMODE_TOGGLE    (0x00000001U)  /*!< Output toggles when the timer counter reaches the compare value */
#define HRTIM_BASICOCMODE_INACTIVE  (0x00000002U)  /*!< Output forced to active level when the timer counter reaches the compare value */
#define HRTIM_BASICOCMODE_ACTIVE    (0x00000003U)  /*!< Output forced to inactive level when the timer counter reaches the compare value */

#define IS_HRTIM_BASICOCMODE(BASICOCMODE)\
              (((BASICOCMODE) == HRTIM_BASICOCMODE_TOGGLE)   || \
               ((BASICOCMODE) == HRTIM_BASICOCMODE_INACTIVE) || \
               ((BASICOCMODE) == HRTIM_BASICOCMODE_ACTIVE))
/**
  * @}
  */

/** @defgroup HRTIM_Output_Polarity HRTIM Output Polarity
  * @{
  * @brief Constants defining the polarity of a timer output
  */
#define HRTIM_OUTPUTPOLARITY_HIGH    (0x00000000U)           /*!< Output is active HIGH */
#define HRTIM_OUTPUTPOLARITY_LOW     (HRTIM_OUTR_POL1)       /*!< Output is active LOW */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Set_Source HRTIM Output Set Source
  * @{
  * @brief Constants defining the events that can be selected to configure the
  *        set crossbar of a timer output
  */
#define HRTIM_OUTPUTSET_NONE       0x00000000U                      /*!< Reset the output set crossbar */
#define HRTIM_OUTPUTSET_RESYNC     (HRTIM_SET1R_RESYNC)             /*!< Timer reset event coming solely from software or SYNC input forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMPER     (HRTIM_SET1R_PER)                /*!< Timer period event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP1    (HRTIM_SET1R_CMP1)               /*!< Timer compare 1 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP2    (HRTIM_SET1R_CMP2)               /*!< Timer compare 2 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP3    (HRTIM_SET1R_CMP3)               /*!< Timer compare 3 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMCMP4    (HRTIM_SET1R_CMP4)               /*!< Timer compare 4 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERPER  (HRTIM_SET1R_MSTPER)             /*!< The master timer period event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP1 (HRTIM_SET1R_MSTCMP1)            /*!< Master Timer compare 1 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP2 (HRTIM_SET1R_MSTCMP2)            /*!< Master Timer compare 2 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP3 (HRTIM_SET1R_MSTCMP3)            /*!< Master Timer compare 3 event forces the output to its active state */
#define HRTIM_OUTPUTSET_MASTERCMP4 (HRTIM_SET1R_MSTCMP4)            /*!< Master Timer compare 4 event forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_1    (HRTIM_SET1R_TIMEVNT1)           /*!< Timer event 1 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_2    (HRTIM_SET1R_TIMEVNT2)           /*!< Timer event 2 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_3    (HRTIM_SET1R_TIMEVNT3)           /*!< Timer event 3 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_4    (HRTIM_SET1R_TIMEVNT4)           /*!< Timer event 4 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_5    (HRTIM_SET1R_TIMEVNT5)           /*!< Timer event 5 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_6    (HRTIM_SET1R_TIMEVNT6)           /*!< Timer event 6 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_7    (HRTIM_SET1R_TIMEVNT7)           /*!< Timer event 7 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_8    (HRTIM_SET1R_TIMEVNT8)           /*!< Timer event 8 forces the output to its active state */
#define HRTIM_OUTPUTSET_TIMEV_9    (HRTIM_SET1R_TIMEVNT9)           /*!< Timer event 9 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_1      (HRTIM_SET1R_EXTVNT1)            /*!< External event 1 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_2      (HRTIM_SET1R_EXTVNT2)            /*!< External event 2 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_3      (HRTIM_SET1R_EXTVNT3)            /*!< External event 3 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_4      (HRTIM_SET1R_EXTVNT4)            /*!< External event 4 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_5      (HRTIM_SET1R_EXTVNT5)            /*!< External event 5 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_6      (HRTIM_SET1R_EXTVNT6)            /*!< External event 6 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_7      (HRTIM_SET1R_EXTVNT7)            /*!< External event 7 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_8      (HRTIM_SET1R_EXTVNT8)            /*!< External event 8 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_9      (HRTIM_SET1R_EXTVNT9)            /*!< External event 9 forces the output to its active state */
#define HRTIM_OUTPUTSET_EEV_10     (HRTIM_SET1R_EXTVNT10)           /*!< External event 10 forces the output to its active state */
#define HRTIM_OUTPUTSET_UPDATE     (HRTIM_SET1R_UPDATE)             /*!< Timer register update event forces the output to its active state */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Reset_Source HRTIM Output Reset Source
  * @{
  * @brief Constants defining the events that can be selected to configure the
  *        reset crossbar of a timer output
  */
#define HRTIM_OUTPUTRESET_NONE       0x00000000U                      /*!< Reset the output reset crossbar */
#define HRTIM_OUTPUTRESET_RESYNC     (HRTIM_RST1R_RESYNC)             /*!< Timer reset event coming solely from software or SYNC input forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMPER     (HRTIM_RST1R_PER)                /*!< Timer period event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP1    (HRTIM_RST1R_CMP1)               /*!< Timer compare 1 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP2    (HRTIM_RST1R_CMP2)               /*!< Timer compare 2 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP3    (HRTIM_RST1R_CMP3)               /*!< Timer compare 3 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMCMP4    (HRTIM_RST1R_CMP4)               /*!< Timer compare 4 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERPER  (HRTIM_RST1R_MSTPER)             /*!< The master timer period event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP1 (HRTIM_RST1R_MSTCMP1)            /*!< Master Timer compare 1 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP2 (HRTIM_RST1R_MSTCMP2)            /*!< Master Timer compare 2 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP3 (HRTIM_RST1R_MSTCMP3)            /*!< Master Timer compare 3 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_MASTERCMP4 (HRTIM_RST1R_MSTCMP4)            /*!< Master Timer compare 4 event forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_TIMEV_1    (HRTIM_RST1R_TIMEVNT1)           /*!< Timer event 1 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_2    (HRTIM_RST1R_TIMEVNT2)           /*!< Timer event 2 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_3    (HRTIM_RST1R_TIMEVNT3)           /*!< Timer event 3 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_4    (HRTIM_RST1R_TIMEVNT4)           /*!< Timer event 4 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_5    (HRTIM_RST1R_TIMEVNT5)           /*!< Timer event 5 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_6    (HRTIM_RST1R_TIMEVNT6)           /*!< Timer event 6 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_7    (HRTIM_RST1R_TIMEVNT7)           /*!< Timer event 7 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_8    (HRTIM_RST1R_TIMEVNT8)           /*!< Timer event 8 forces the output to its active state */
#define HRTIM_OUTPUTRESET_TIMEV_9    (HRTIM_RST1R_TIMEVNT9)           /*!< Timer event 9 forces the output to its active state */
#define HRTIM_OUTPUTRESET_EEV_1      (HRTIM_RST1R_EXTVNT1)            /*!< External event 1 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_2      (HRTIM_RST1R_EXTVNT2)            /*!< External event 2 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_3      (HRTIM_RST1R_EXTVNT3)            /*!< External event 3 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_4      (HRTIM_RST1R_EXTVNT4)            /*!< External event 4 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_5      (HRTIM_RST1R_EXTVNT5)            /*!< External event 5 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_6      (HRTIM_RST1R_EXTVNT6)            /*!< External event 6 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_7      (HRTIM_RST1R_EXTVNT7)            /*!< External event 7 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_8      (HRTIM_RST1R_EXTVNT8)            /*!< External event 8 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_9      (HRTIM_RST1R_EXTVNT9)            /*!< External event 9 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_EEV_10     (HRTIM_RST1R_EXTVNT10)           /*!< External event 10 forces the output to its inactive state */
#define HRTIM_OUTPUTRESET_UPDATE     (HRTIM_RST1R_UPDATE)             /*!< Timer register update event forces the output to its inactive state */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Idle_Mode HRTIM Output Idle Mode
  * @{
  * @brief Constants defining whether or not the timer output transition to its
           IDLE state when burst mode is entered
  */
#define HRTIM_OUTPUTIDLEMODE_NONE     0x00000000U           /*!< The output is not affected by the burst mode operation */
#define HRTIM_OUTPUTIDLEMODE_IDLE     (HRTIM_OUTR_IDLM1)    /*!< The output is in idle state when requested by the burst mode controller */
 /**
  * @}
  */

/** @defgroup HRTIM_Output_IDLE_Level HRTIM Output IDLE Level
  * @{
  * @brief Constants defining the output level when output is in IDLE state
  */
#define HRTIM_OUTPUTIDLELEVEL_INACTIVE   0x00000000U           /*!< Output at inactive level when in IDLE state */
#define HRTIM_OUTPUTIDLELEVEL_ACTIVE     (HRTIM_OUTR_IDLES1)   /*!< Output at active level when in IDLE state */
/**
  * @}
  */

/** @defgroup HRTIM_Output_FAULT_Level HRTIM Output FAULT Level
  * @{
  * @brief Constants defining the output level when output is in FAULT state
  */
#define HRTIM_OUTPUTFAULTLEVEL_NONE      0x00000000U                                  /*!< The output is not affected by the fault input */
#define HRTIM_OUTPUTFAULTLEVEL_ACTIVE    (HRTIM_OUTR_FAULT1_0)                        /*!< Output at active level when in FAULT state */
#define HRTIM_OUTPUTFAULTLEVEL_INACTIVE  (HRTIM_OUTR_FAULT1_1)                        /*!< Output at inactive level when in FAULT state */
#define HRTIM_OUTPUTFAULTLEVEL_HIGHZ     (HRTIM_OUTR_FAULT1_1 | HRTIM_OUTR_FAULT1_0)  /*!< Output is tri-stated when in FAULT state */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Chopper_Mode_Enable HRTIM Output Chopper Mode Enable
  * @{
  * @brief Constants defining whether or not chopper mode is enabled for a timer
           output
  */
#define HRTIM_OUTPUTCHOPPERMODE_DISABLED   0x00000000U           /*!< Output signal is not altered  */
#define HRTIM_OUTPUTCHOPPERMODE_ENABLED    (HRTIM_OUTR_CHP1)     /*!< Output signal is chopped by a carrier signal  */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Burst_Mode_Entry_Delayed HRTIM Output Burst Mode Entry Delayed
  * @{
  * @brief Constants defining the idle mode entry is delayed by forcing a
           dead-time insertion before switching the outputs to their idle state
  */
#define HRTIM_OUTPUTBURSTMODEENTRY_REGULAR   0x00000000U           /*!< The programmed Idle state is applied immediately to the Output */
#define HRTIM_OUTPUTBURSTMODEENTRY_DELAYED   (HRTIM_OUTR_DIDL1)    /*!< Dead-time is inserted on output before entering the idle mode */
/**
  * @}
  */


/** @defgroup HRTIM_Capture_Unit_Trigger HRTIM Capture Unit Trigger
  * @{
  * @brief Constants defining the events that can be selected to trigger the
  *        capture of the timing unit counter
  */
#define HRTIM_CAPTURETRIGGER_NONE         0x00000000U              /*!< Capture trigger is disabled */
#define HRTIM_CAPTURETRIGGER_UPDATE       (HRTIM_CPT1CR_UPDCPT)    /*!< The update event triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_1        (HRTIM_CPT1CR_EXEV1CPT)  /*!< The External event 1 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_2        (HRTIM_CPT1CR_EXEV2CPT)  /*!< The External event 2 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_3        (HRTIM_CPT1CR_EXEV3CPT)  /*!< The External event 3 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_4        (HRTIM_CPT1CR_EXEV4CPT)  /*!< The External event 4 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_5        (HRTIM_CPT1CR_EXEV5CPT)  /*!< The External event 5 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_6        (HRTIM_CPT1CR_EXEV6CPT)  /*!< The External event 6 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_7        (HRTIM_CPT1CR_EXEV7CPT)  /*!< The External event 7 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_8        (HRTIM_CPT1CR_EXEV8CPT)  /*!< The External event 8 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_9        (HRTIM_CPT1CR_EXEV9CPT)  /*!< The External event 9 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_EEV_10       (HRTIM_CPT1CR_EXEV10CPT) /*!< The External event 10 triggers the Capture */
#define HRTIM_CAPTURETRIGGER_TA1_SET      (HRTIM_CPT1CR_TA1SET)    /*!< Capture is triggered by TA1 output inactive to active transition */
#define HRTIM_CAPTURETRIGGER_TA1_RESET    (HRTIM_CPT1CR_TA1RST)    /*!< Capture is triggered by TA1 output active to inactive transition */
#define HRTIM_CAPTURETRIGGER_TIMERA_CMP1  (HRTIM_CPT1CR_TIMACMP1)  /*!< Timer A Compare 1 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TIMERA_CMP2  (HRTIM_CPT1CR_TIMACMP2)  /*!< Timer A Compare 2 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TB1_SET      (HRTIM_CPT1CR_TB1SET)    /*!< Capture is triggered by TB1 output inactive to active transition */
#define HRTIM_CAPTURETRIGGER_TB1_RESET    (HRTIM_CPT1CR_TB1RST)    /*!< Capture is triggered by TB1 output active to inactive transition */
#define HRTIM_CAPTURETRIGGER_TIMERB_CMP1  (HRTIM_CPT1CR_TIMBCMP1)  /*!< Timer B Compare 1 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TIMERB_CMP2  (HRTIM_CPT1CR_TIMBCMP2)  /*!< Timer B Compare 2 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TC1_SET      (HRTIM_CPT1CR_TC1SET)    /*!< Capture is triggered by TC1 output inactive to active transition */
#define HRTIM_CAPTURETRIGGER_TC1_RESET    (HRTIM_CPT1CR_TC1RST)    /*!< Capture is triggered by TC1 output active to inactive transition */
#define HRTIM_CAPTURETRIGGER_TIMERC_CMP1  (HRTIM_CPT1CR_TIMCCMP1)  /*!< Timer C Compare 1 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TIMERC_CMP2  (HRTIM_CPT1CR_TIMCCMP2)  /*!< Timer C Compare 2 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TD1_SET      (HRTIM_CPT1CR_TD1SET)    /*!< Capture is triggered by TD1 output inactive to active transition */
#define HRTIM_CAPTURETRIGGER_TD1_RESET    (HRTIM_CPT1CR_TD1RST)    /*!< Capture is triggered by TD1 output active to inactive transition */
#define HRTIM_CAPTURETRIGGER_TIMERD_CMP1  (HRTIM_CPT1CR_TIMDCMP1)  /*!< Timer D Compare 1 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TIMERD_CMP2  (HRTIM_CPT1CR_TIMDCMP2)  /*!< Timer D Compare 2 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TE1_SET      (HRTIM_CPT1CR_TE1SET)    /*!< Capture is triggered by TE1 output inactive to active transition */
#define HRTIM_CAPTURETRIGGER_TE1_RESET    (HRTIM_CPT1CR_TE1RST)    /*!< Capture is triggered by TE1 output active to inactive transition */
#define HRTIM_CAPTURETRIGGER_TIMERE_CMP1  (HRTIM_CPT1CR_TIMECMP1)  /*!< Timer E Compare 1 triggers Capture */
#define HRTIM_CAPTURETRIGGER_TIMERE_CMP2  (HRTIM_CPT1CR_TIMECMP2)  /*!< Timer E Compare 2 triggers Capture */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_External_Event_Filter HRTIM Timer External Event Filter
  * @{
  * @brief Constants defining the event filtering applied to external events
  *        by a timer
  */
#define HRTIM_TIMEVENTFILTER_NONE             (0x00000000U)
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP1     (HRTIM_EEFR1_EE1FLTR_0)                                                                          /*!< Blanking from counter reset/roll-over to Compare 1U  */
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP2     (HRTIM_EEFR1_EE1FLTR_1)                                                                          /*!< Blanking from counter reset/roll-over to Compare 2U  */
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP3     (HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)                                                  /*!< Blanking from counter reset/roll-over to Compare 3U  */
#define HRTIM_TIMEVENTFILTER_BLANKINGCMP4     (HRTIM_EEFR1_EE1FLTR_2)                                                                          /*!< Blanking from counter reset/roll-over to Compare 4U  */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR1    (HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_0)                                                  /*!< Blanking from another timing unit: TIMFLTR1 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR2    (HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1)                                                  /*!< Blanking from another timing unit: TIMFLTR2 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR3    (HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)                          /*!< Blanking from another timing unit: TIMFLTR3 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR4    (HRTIM_EEFR1_EE1FLTR_3)                                                                          /*!< Blanking from another timing unit: TIMFLTR4 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR5    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_0)                                                  /*!< Blanking from another timing unit: TIMFLTR5 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR6    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_1)                                                  /*!< Blanking from another timing unit: TIMFLTR6 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR7    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)                          /*!< Blanking from another timing unit: TIMFLTR7 source   */
#define HRTIM_TIMEVENTFILTER_BLANKINGFLTR8    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2)                                                  /*!< Blanking from another timing unit: TIMFLTR8 source   */
#define HRTIM_TIMEVENTFILTER_WINDOWINGCMP2    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_0)                          /*!< Windowing from counter reset/roll-over to Compare 2U */
#define HRTIM_TIMEVENTFILTER_WINDOWINGCMP3    (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1)                          /*!< Windowing from counter reset/roll-over to Compare 3U */
#define HRTIM_TIMEVENTFILTER_WINDOWINGTIM     (HRTIM_EEFR1_EE1FLTR_3 | HRTIM_EEFR1_EE1FLTR_2 | HRTIM_EEFR1_EE1FLTR_1 | HRTIM_EEFR1_EE1FLTR_0)  /*!< Windowing from another timing unit: TIMWIN source    */
/**
  * @}
  */

/** @defgroup HRTIM_Timer_External_Event_Latch HRTIM Timer External Event Latch
  * @{
  * @brief Constants defining whether or not the external event is
  *        memorized (latched) and generated as soon as the blanking period
  *        is completed or the window ends
  */
#define HRTIM_TIMEVENTLATCH_DISABLED    (0x00000000U)           /*!< Event is ignored if it happens during a blank, or passed through during a window */
#define HRTIM_TIMEVENTLATCH_ENABLED     HRTIM_EEFR1_EE1LTCH     /*!< Event is latched and delayed till the end of the blanking or windowing period */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Prescaler_Ratio HRTIM Dead-time Prescaler Ratio
  * @{
  * @brief Constants defining division ratio between the timer clock frequency
  *        (fHRTIM) and the dead-time generator clock (fDTG)
  */
#define HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV1    (HRTIM_DTR_DTPRSC_1 | HRTIM_DTR_DTPRSC_0)                       /*!< fDTG = fHRTIM */
#define HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV2    (HRTIM_DTR_DTPRSC_2)                                            /*!< fDTG = fHRTIM / 2U */
#define HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV4    (HRTIM_DTR_DTPRSC_2 | HRTIM_DTR_DTPRSC_0)                       /*!< fDTG = fHRTIM / 4U */
#define HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV8    (HRTIM_DTR_DTPRSC_2 | HRTIM_DTR_DTPRSC_1)                       /*!< fDTG = fHRTIM / 8U */
#define HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV16   (HRTIM_DTR_DTPRSC_2 | HRTIM_DTR_DTPRSC_1 | HRTIM_DTR_DTPRSC_0)  /*!< fDTG = fHRTIM / 16U */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Rising_Sign HRTIM Dead-time Rising Sign
  * @{
  * @brief Constants defining whether the dead-time is positive or negative
  *        (overlapping signal) on rising edge
  */
#define HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE    (0x00000000U)           /*!< Positive dead-time on rising edge */
#define HRTIM_TIMDEADTIME_RISINGSIGN_NEGATIVE    (HRTIM_DTR_SDTR)        /*!< Negative dead-time on rising edge */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Rising_Lock HRTIM Dead-time Rising Lock
  * @{
  * @brief Constants defining whether or not the dead-time (rising sign and
  *        value) is write protected
  */
#define HRTIM_TIMDEADTIME_RISINGLOCK_WRITE    (0x00000000U)           /*!< Dead-time rising value and sign is writeable */
#define HRTIM_TIMDEADTIME_RISINGLOCK_READONLY (HRTIM_DTR_DTRLK)       /*!< Dead-time rising value and sign is read-only */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Rising_Sign_Lock HRTIM Dead-time Rising Sign Lock
  * @{
  * @brief Constants defining whether or not the dead-time rising sign is write
  *        protected
  */
#define HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE    (0x00000000U)           /*!< Dead-time rising sign is writeable */
#define HRTIM_TIMDEADTIME_RISINGSIGNLOCK_READONLY (HRTIM_DTR_DTRSLK)      /*!< Dead-time rising sign is read-only */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Falling_Sign HRTIM Dead-time Falling Sign
  * @{
  * @brief Constants defining whether the dead-time is positive or negative
  *        (overlapping signal) on falling edge
  */
#define HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE    (0x00000000U)           /*!< Positive dead-time on falling edge */
#define HRTIM_TIMDEADTIME_FALLINGSIGN_NEGATIVE    (HRTIM_DTR_SDTF)        /*!< Negative dead-time on falling edge */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Falling_Lock HRTIM Dead-time Falling Lock
  * @{
  * @brief Constants defining whether or not the dead-time (falling sign and
  *        value) is write protected
  */
#define HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE    (0x00000000U)           /*!< Dead-time falling value and sign is writeable */
#define HRTIM_TIMDEADTIME_FALLINGLOCK_READONLY (HRTIM_DTR_DTFLK)       /*!< Dead-time falling value and sign is read-only */
/**
  * @}
  */

/** @defgroup HRTIM_Deadtime_Falling_Sign_Lock HRTIM Dead-time Falling Sign Lock
  * @{
  * @brief Constants defining whether or not the dead-time falling sign is write
  *        protected
  */
#define HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE    (0x00000000U)           /*!< Dead-time falling sign is writeable */
#define HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_READONLY (HRTIM_DTR_DTFSLK)      /*!< Dead-time falling sign is read-only */
/**
  * @}
  */

/** @defgroup HRTIM_Chopper_Frequency HRTIM Chopper Frequency
  * @{
  * @brief Constants defining the frequency of the generated high frequency carrier
  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV16  (0x000000U)                                                                     /*!< fCHPFRQ = fHRTIM / 16  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV32  (HRTIM_CHPR_CARFRQ_0)                                                                    /*!< fCHPFRQ = fHRTIM / 32  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV48  (HRTIM_CHPR_CARFRQ_1)                                                                    /*!< fCHPFRQ = fHRTIM / 48  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV64  (HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)                                              /*!< fCHPFRQ = fHRTIM / 64  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV80  (HRTIM_CHPR_CARFRQ_2)                                                                    /*!< fCHPFRQ = fHRTIM / 80  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV96  (HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_0)                                              /*!< fCHPFRQ = fHRTIM / 96  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV112 (HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1)                                              /*!< fCHPFRQ = fHRTIM / 112  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV128 (HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)                        /*!< fCHPFRQ = fHRTIM / 128  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV144 (HRTIM_CHPR_CARFRQ_3)                                                                    /*!< fCHPFRQ = fHRTIM / 144  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV160 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_0)                                              /*!< fCHPFRQ = fHRTIM / 160  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV176 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_1)                                              /*!< fCHPFRQ = fHRTIM / 176  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV192 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)                        /*!< fCHPFRQ = fHRTIM / 192  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV208 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2)                                              /*!< fCHPFRQ = fHRTIM / 208  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV224 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_0)                        /*!< fCHPFRQ = fHRTIM / 224  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV240 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1)                        /*!< fCHPFRQ = fHRTIM / 240  */
#define HRTIM_CHOPPER_PRESCALERRATIO_DIV256 (HRTIM_CHPR_CARFRQ_3 | HRTIM_CHPR_CARFRQ_2 | HRTIM_CHPR_CARFRQ_1 | HRTIM_CHPR_CARFRQ_0)  /*!< fCHPFRQ = fHRTIM / 256  */
 /**
  * @}
  */

/** @defgroup HRTIM_Chopper_Duty_Cycle HRTIM Chopper Duty Cycle
  * @{
  * @brief Constants defining the duty cycle of the generated high frequency carrier
  *        Duty cycle can be adjusted by 1/8 step (from 0/8 up to 7/8)
  */
#define HRTIM_CHOPPER_DUTYCYCLE_0    (0x000000U)                                                       /*!< Only 1st pulse is present */
#define HRTIM_CHOPPER_DUTYCYCLE_125  (HRTIM_CHPR_CARDTY_0)                                             /*!< Duty cycle of the carrier signal is 12.5U % */
#define HRTIM_CHOPPER_DUTYCYCLE_250  (HRTIM_CHPR_CARDTY_1)                                             /*!< Duty cycle of the carrier signal is 25U % */
#define HRTIM_CHOPPER_DUTYCYCLE_375  (HRTIM_CHPR_CARDTY_1 | HRTIM_CHPR_CARDTY_0)                       /*!< Duty cycle of the carrier signal is 37.5U % */
#define HRTIM_CHOPPER_DUTYCYCLE_500  (HRTIM_CHPR_CARDTY_2)                                             /*!< Duty cycle of the carrier signal is 50U % */
#define HRTIM_CHOPPER_DUTYCYCLE_625  (HRTIM_CHPR_CARDTY_2 | HRTIM_CHPR_CARDTY_0)                       /*!< Duty cycle of the carrier signal is 62.5U % */
#define HRTIM_CHOPPER_DUTYCYCLE_750  (HRTIM_CHPR_CARDTY_2 | HRTIM_CHPR_CARDTY_1)                       /*!< Duty cycle of the carrier signal is 75U % */
#define HRTIM_CHOPPER_DUTYCYCLE_875  (HRTIM_CHPR_CARDTY_2 | HRTIM_CHPR_CARDTY_1 | HRTIM_CHPR_CARDTY_0) /*!< Duty cycle of the carrier signal is 87.5U % */
/**
  * @}
  */

/** @defgroup HRTIM_Chopper_Start_Pulse_Width HRTIM Chopper Start Pulse Width
  * @{
  * @brief Constants defining the pulse width of the first pulse of the generated
  *        high frequency carrier
  */
#define HRTIM_CHOPPER_PULSEWIDTH_16   (0x000000U)                                                                          /*!< tSTPW = tHRTIM x 16  */
#define HRTIM_CHOPPER_PULSEWIDTH_32   (HRTIM_CHPR_STRPW_0)                                                                 /*!< tSTPW = tHRTIM x 32  */
#define HRTIM_CHOPPER_PULSEWIDTH_48   (HRTIM_CHPR_STRPW_1)                                                                 /*!< tSTPW = tHRTIM x 48  */
#define HRTIM_CHOPPER_PULSEWIDTH_64   (HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)                                            /*!< tSTPW = tHRTIM x 64  */
#define HRTIM_CHOPPER_PULSEWIDTH_80   (HRTIM_CHPR_STRPW_2)                                                                 /*!< tSTPW = tHRTIM x 80  */
#define HRTIM_CHOPPER_PULSEWIDTH_96   (HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_0)                                            /*!< tSTPW = tHRTIM x 96  */
#define HRTIM_CHOPPER_PULSEWIDTH_112  (HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1)                                            /*!< tSTPW = tHRTIM x 112  */
#define HRTIM_CHOPPER_PULSEWIDTH_128  (HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)                       /*!< tSTPW = tHRTIM x 128  */
#define HRTIM_CHOPPER_PULSEWIDTH_144  (HRTIM_CHPR_STRPW_3)                                                                 /*!< tSTPW = tHRTIM x 144  */
#define HRTIM_CHOPPER_PULSEWIDTH_160  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_0)                                            /*!< tSTPW = tHRTIM x 160  */
#define HRTIM_CHOPPER_PULSEWIDTH_176  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_1)                                            /*!< tSTPW = tHRTIM x 176  */
#define HRTIM_CHOPPER_PULSEWIDTH_192  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)                       /*!< tSTPW = tHRTIM x 192  */
#define HRTIM_CHOPPER_PULSEWIDTH_208  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2)                                            /*!< tSTPW = tHRTIM x 208  */
#define HRTIM_CHOPPER_PULSEWIDTH_224  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_0)                       /*!< tSTPW = tHRTIM x 224  */
#define HRTIM_CHOPPER_PULSEWIDTH_240  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1)                       /*!< tSTPW = tHRTIM x 240  */
#define HRTIM_CHOPPER_PULSEWIDTH_256  (HRTIM_CHPR_STRPW_3 | HRTIM_CHPR_STRPW_2 | HRTIM_CHPR_STRPW_1 | HRTIM_CHPR_STRPW_0)  /*!< tSTPW = tHRTIM x 256  */
/**
  * @}
  */

/** @defgroup HRTIM_Synchronization_Options HRTIM Synchronization Options
  * @{
  * @brief Constants defining the options for synchronizing multiple HRTIM
  *        instances, as a master unit (generating a synchronization signal)
  *        or as a slave (waiting for a trigger to be synchronized)
  */
#define HRTIM_SYNCOPTION_NONE   0x00000000U   /*!< HRTIM instance doesn't handle external synchronization signals (SYNCIN, SYNCOUT) */
#define HRTIM_SYNCOPTION_MASTER 0x00000001U   /*!< HRTIM instance acts as a MASTER, i.e. generates external synchronization output (SYNCOUT)*/
#define HRTIM_SYNCOPTION_SLAVE  0x00000002U   /*!< HRTIM instance acts as a SLAVE, i.e. it is synchronized by external sources (SYNCIN) */
/**
  * @}
  */

/** @defgroup HRTIM_Synchronization_Input_Source HRTIM Synchronization Input Source
  * @{
  * @brief Constants defining defining the synchronization input source
  */
#define HRTIM_SYNCINPUTSOURCE_NONE           0x00000000U                                  /*!< disabled. HRTIM is not synchronized and runs in standalone mode */
#define HRTIM_SYNCINPUTSOURCE_INTERNALEVENT  HRTIM_MCR_SYNC_IN_1                          /*!< The HRTIM is synchronized with the on-chip timer */
#define HRTIM_SYNCINPUTSOURCE_EXTERNALEVENT  (HRTIM_MCR_SYNC_IN_1 | HRTIM_MCR_SYNC_IN_0)  /*!< A positive pulse on SYNCIN input triggers the HRTIM */
/**
  * @}
  */

/** @defgroup HRTIM_Synchronization_Output_Source HRTIM Synchronization Output Source
  * @{
  * @brief Constants defining the source and event to be sent on the
  *        synchronization outputs
  */
#define HRTIM_SYNCOUTPUTSOURCE_MASTER_START 0x00000000U                                    /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon master timer start event      */
#define HRTIM_SYNCOUTPUTSOURCE_MASTER_CMP1  (HRTIM_MCR_SYNC_SRC_0)                         /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon master timer compare 1 event  */
#define HRTIM_SYNCOUTPUTSOURCE_TIMA_START   (HRTIM_MCR_SYNC_SRC_1)                         /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon timer A start or reset events */
#define HRTIM_SYNCOUTPUTSOURCE_TIMA_CMP1    (HRTIM_MCR_SYNC_SRC_1 | HRTIM_MCR_SYNC_SRC_0)  /*!< A pulse is sent on HRTIM_SCOUT output and hrtim_out_sync2 upon timer A compare 1 event       */
/**
  * @}
  */

/** @defgroup HRTIM_Synchronization_Output_Polarity HRTIM Synchronization Output Polarity
  * @{
  * @brief Constants defining the routing and conditioning of the synchronization output event
  */
#define HRTIM_SYNCOUTPUTPOLARITY_NONE      0x00000000U                                   /*!< Synchronization output event is disabled */
#define HRTIM_SYNCOUTPUTPOLARITY_POSITIVE  (HRTIM_MCR_SYNC_OUT_1)                        /*!< SCOUT pin has a low idle level and issues a positive pulse of 16 fHRTIM clock cycles length for the synchronization */
#define HRTIM_SYNCOUTPUTPOLARITY_NEGATIVE  (HRTIM_MCR_SYNC_OUT_1 | HRTIM_MCR_SYNC_OUT_0) /*!< SCOUT pin has a high idle level and issues a negative pulse of 16 fHRTIM clock cycles length for the synchronization */
/**
  * @}
  */

/** @defgroup HRTIM_External_Event_Sources HRTIM External Event Sources
  * @{
  * @brief Constants defining available sources associated to external events
  */
#define HRTIM_EVENTSRC_1         (0x00000000U)                                  /*!< External event source 1U */
#define HRTIM_EVENTSRC_2         (HRTIM_EECR1_EE1SRC_0)                         /*!< External event source 2U */
#define HRTIM_EVENTSRC_3         (HRTIM_EECR1_EE1SRC_1)                         /*!< External event source 3U */
#define HRTIM_EVENTSRC_4         (HRTIM_EECR1_EE1SRC_1 | HRTIM_EECR1_EE1SRC_0)  /*!< External event source 4U */
/**
  * @}
  */

/** @defgroup HRTIM_External_Event_Polarity HRTIM External Event Polarity
  * @{
  * @brief Constants defining the polarity of an external event
  */
#define HRTIM_EVENTPOLARITY_HIGH    (0x00000000U)           /*!< External event is active high */
#define HRTIM_EVENTPOLARITY_LOW     (HRTIM_EECR1_EE1POL)    /*!< External event is active low */
/**
  * @}
  */

/** @defgroup HRTIM_External_Event_Sensitivity HRTIM External Event Sensitivity
  * @{
  * @brief Constants defining the sensitivity (level-sensitive or edge-sensitive)
  *        of an external event
  */
#define HRTIM_EVENTSENSITIVITY_LEVEL          (0x00000000U)                                  /*!< External event is active on level */
#define HRTIM_EVENTSENSITIVITY_RISINGEDGE     (HRTIM_EECR1_EE1SNS_0)                         /*!< External event is active on Rising edge */
#define HRTIM_EVENTSENSITIVITY_FALLINGEDGE    (HRTIM_EECR1_EE1SNS_1)                         /*!< External event is active on Falling edge */
#define HRTIM_EVENTSENSITIVITY_BOTHEDGES      (HRTIM_EECR1_EE1SNS_1 | HRTIM_EECR1_EE1SNS_0)  /*!< External event is active on Rising and Falling edges */
/**
  * @}
  */

/** @defgroup HRTIM_External_Event_Fast_Mode HRTIM External Event Fast Mode
  * @{
  * @brief Constants defining whether or not an external event is programmed in
           fast mode
  */
#define HRTIM_EVENTFASTMODE_DISABLE    (0x00000000U)               /*!< External Event is re-synchronized by the HRTIM logic before acting on outputs */
#define HRTIM_EVENTFASTMODE_ENABLE     (HRTIM_EECR1_EE1FAST)       /*!< External Event is acting asynchronously on outputs (low latency mode) */
/**
  * @}
  */

/** @defgroup HRTIM_External_Event_Filter HRTIM External Event Filter
  * @{
  * @brief Constants defining the frequency used to sample an external event 6
  *        input and the length (N) of the digital filter applied
  */
#define HRTIM_EVENTFILTER_NONE      (0x00000000U)                                                                         /*!< Filter disabled */
#define HRTIM_EVENTFILTER_1         (HRTIM_EECR3_EE6F_0)                                                                  /*!< fSAMPLING= fHRTIM, N=2U */
#define HRTIM_EVENTFILTER_2         (HRTIM_EECR3_EE6F_1)                                                                  /*!< fSAMPLING= fHRTIM, N=4U */
#define HRTIM_EVENTFILTER_3         (HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING= fHRTIM, N=8U */
#define HRTIM_EVENTFILTER_4         (HRTIM_EECR3_EE6F_2)                                                                  /*!< fSAMPLING= fEEVS/2U, N=6U */
#define HRTIM_EVENTFILTER_5         (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING= fEEVS/2U, N=8U */
#define HRTIM_EVENTFILTER_6         (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_1)                                             /*!< fSAMPLING= fEEVS/4U, N=6U */
#define HRTIM_EVENTFILTER_7         (HRTIM_EECR3_EE6F_2 | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                        /*!< fSAMPLING= fEEVS/4U, N=8U */
#define HRTIM_EVENTFILTER_8         (HRTIM_EECR3_EE6F_3)                                                                  /*!< fSAMPLING= fEEVS/8U, N=6U */
#define HRTIM_EVENTFILTER_9         (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_0)                                             /*!< fSAMPLING= fEEVS/8U, N=8U */
#define HRTIM_EVENTFILTER_10        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_1)                                             /*!< fSAMPLING= fEEVS/16U, N=5U */
#define HRTIM_EVENTFILTER_11        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)                        /*!< fSAMPLING= fEEVS/16U, N=6U */
#define HRTIM_EVENTFILTER_12        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2)                                             /*!< fSAMPLING= fEEVS/16U, N=8U */
#define HRTIM_EVENTFILTER_13        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_0)                       /*!< fSAMPLING= fEEVS/32U, N=5U */
#define HRTIM_EVENTFILTER_14        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_1)                       /*!< fSAMPLING= fEEVS/32U, N=6U */
#define HRTIM_EVENTFILTER_15        (HRTIM_EECR3_EE6F_3 | HRTIM_EECR3_EE6F_2  | HRTIM_EECR3_EE6F_1 | HRTIM_EECR3_EE6F_0)  /*!< fSAMPLING= fEEVS/32U, N=8U */
/**
  * @}
  */

/** @defgroup HRTIM_External_Event_Prescaler HRTIM External Event Prescaler
  * @{
  * @brief Constants defining division ratio between the timer clock frequency
  *        fHRTIM) and the external event signal sampling clock (fEEVS)
  *        used by the digital filters
  */
#define HRTIM_EVENTPRESCALER_DIV1    (0x00000000U)                                   /*!< fEEVS=fHRTIM */
#define HRTIM_EVENTPRESCALER_DIV2    (HRTIM_EECR3_EEVSD_0)                           /*!< fEEVS=fHRTIM / 2U */
#define HRTIM_EVENTPRESCALER_DIV4    (HRTIM_EECR3_EEVSD_1)                           /*!< fEEVS=fHRTIM / 4U */
#define HRTIM_EVENTPRESCALER_DIV8    (HRTIM_EECR3_EEVSD_1 | HRTIM_EECR3_EEVSD_0)     /*!< fEEVS=fHRTIM / 8U */
/**
  * @}
  */

/** @defgroup HRTIM_Fault_Sources HRTIM Fault Sources
  * @{
  * @brief Constants defining whether a fault is triggered by any external
  *        or internal fault source
  */
#define HRTIM_FAULTSOURCE_DIGITALINPUT      (0x00000000U)              /*!< Fault input is FLT input pin */
#define HRTIM_FAULTSOURCE_INTERNAL          (HRTIM_FLTINR1_FLT1SRC)    /*!< Fault input is FLT_Int signal (e.g. internal comparator) */
/**
  * @}
  */

/** @defgroup HRTIM_Fault_Polarity HRTIM Fault Polarity
  * @{
  * @brief Constants defining the polarity of a fault event
  */
#define HRTIM_FAULTPOLARITY_LOW     (0x00000000U)            /*!< Fault input is active low */
#define HRTIM_FAULTPOLARITY_HIGH    (HRTIM_FLTINR1_FLT1P)    /*!< Fault input is active high */
/**
  * @}
  */

/** @defgroup HRTIM_Fault_Filter HRTIM Fault Filter
  * @{
  * @ brief Constants defining the frequency used to sample the fault input and
  *         the length (N) of the digital filter applied
  */
#define HRTIM_FAULTFILTER_NONE      (0x00000000U)                                                                                    /*!< Filter disabled */
#define HRTIM_FAULTFILTER_1         (HRTIM_FLTINR1_FLT1F_0)                                                                          /*!< fSAMPLING= fHRTIM, N=2U */
#define HRTIM_FAULTFILTER_2         (HRTIM_FLTINR1_FLT1F_1)                                                                          /*!< fSAMPLING= fHRTIM, N=4U */
#define HRTIM_FAULTFILTER_3         (HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)                                                  /*!< fSAMPLING= fHRTIM, N=8U */
#define HRTIM_FAULTFILTER_4         (HRTIM_FLTINR1_FLT1F_2)                                                                          /*!< fSAMPLING= fFLTS/2U, N=6U */
#define HRTIM_FAULTFILTER_5         (HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_0)                                                  /*!< fSAMPLING= fFLTS/2U, N=8U */
#define HRTIM_FAULTFILTER_6         (HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1)                                                  /*!< fSAMPLING= fFLTS/4U, N=6U */
#define HRTIM_FAULTFILTER_7         (HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)                          /*!< fSAMPLING= fFLTS/4U, N=8U */
#define HRTIM_FAULTFILTER_8         (HRTIM_FLTINR1_FLT1F_3)                                                                          /*!< fSAMPLING= fFLTS/8U, N=6U */
#define HRTIM_FAULTFILTER_9         (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_0)                                                  /*!< fSAMPLING= fFLTS/8U, N=8U */
#define HRTIM_FAULTFILTER_10        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_1)                                                  /*!< fSAMPLING= fFLTS/16U, N=5U */
#define HRTIM_FAULTFILTER_11        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)                          /*!< fSAMPLING= fFLTS/16U, N=6U */
#define HRTIM_FAULTFILTER_12        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2)                                                  /*!< fSAMPLING= fFLTS/16U, N=8U */
#define HRTIM_FAULTFILTER_13        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_0)                          /*!< fSAMPLING= fFLTS/32U, N=5U */
#define HRTIM_FAULTFILTER_14        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1)                          /*!< fSAMPLING= fFLTS/32U, N=6U */
#define HRTIM_FAULTFILTER_15        (HRTIM_FLTINR1_FLT1F_3 | HRTIM_FLTINR1_FLT1F_2 | HRTIM_FLTINR1_FLT1F_1 | HRTIM_FLTINR1_FLT1F_0)  /*!< fSAMPLING= fFLTS/32U, N=8U */
/**
  * @}
  */

/** @defgroup HRTIM_Fault_Lock HRTIM Fault Lock
  * @{
  * @brief Constants defining whether or not the fault programming bits are
           write protected
  */
#define HRTIM_FAULTLOCK_READWRITE       (0x00000000U)               /*!< Fault settings bits are read/write */
#define HRTIM_FAULTLOCK_READONLY        (HRTIM_FLTINR1_FLT1LCK)     /*!< Fault settings bits are read only */
/**
  * @}
  */

/** @defgroup HRTIM_External_Fault_Prescaler HRTIM External Fault Prescaler
  * @{
  * @brief Constants defining the division ratio between the timer clock
  *        frequency (fHRTIM) and the fault signal sampling clock (fFLTS) used
  *        by the digital filters.
  */
#define HRTIM_FAULTPRESCALER_DIV1    (0x00000000U)                                     /*!< fFLTS=fHRTIM */
#define HRTIM_FAULTPRESCALER_DIV2    (HRTIM_FLTINR2_FLTSD_0)                           /*!< fFLTS=fHRTIM / 2U */
#define HRTIM_FAULTPRESCALER_DIV4    (HRTIM_FLTINR2_FLTSD_1)                           /*!< fFLTS=fHRTIM / 4U */
#define HRTIM_FAULTPRESCALER_DIV8    (HRTIM_FLTINR2_FLTSD_1 | HRTIM_FLTINR2_FLTSD_0)   /*!< fFLTS=fHRTIM / 8U */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Operating_Mode HRTIM Burst Mode Operating Mode
  * @{
  * @brief Constants defining if the burst mode is entered once or if it is
  *        continuously operating
  */
#define HRTIM_BURSTMODE_SINGLESHOT (0x00000000U)           /*!< Burst mode operates in single shot mode */
#define HRTIM_BURSTMODE_CONTINOUS   (HRTIM_BMCR_BMOM)      /*!< Burst mode operates in continuous mode */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Clock_Source HRTIM Burst Mode Clock Source
  * @{
  * @brief Constants defining the clock source for the burst mode counter
  */
#define HRTIM_BURSTMODECLOCKSOURCE_MASTER     (0x00000000U)                                                   /*!< Master timer counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_A    (HRTIM_BMCR_BMCLK_0)                                            /*!< Timer A counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_B    (HRTIM_BMCR_BMCLK_1)                                            /*!< Timer B counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_C    (HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)                       /*!< Timer C counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_D    (HRTIM_BMCR_BMCLK_2)                                            /*!< Timer D counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIMER_E    (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_0)                       /*!< Timer E counter reset/roll-over is used as clock source for the burst mode counter */
#define HRTIM_BURSTMODECLOCKSOURCE_TIM16_OC   (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_1)                       /*!< On-chip Event 1 (BMClk[1]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_TIM17_OC   (HRTIM_BMCR_BMCLK_2 | HRTIM_BMCR_BMCLK_1 | HRTIM_BMCR_BMCLK_0)  /*!< On-chip Event 2 (BMClk[2]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_TIM7_TRGO  (HRTIM_BMCR_BMCLK_3)                                            /*!< On-chip Event 3 (BMClk[3]), acting as a burst mode counter clock */
#define HRTIM_BURSTMODECLOCKSOURCE_FHRTIM     (HRTIM_BMCR_BMCLK_3 | HRTIM_BMCR_BMCLK_1)                       /*!< Prescaled fHRTIM clock is used as clock source for the burst mode counter */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Prescaler HRTIM Burst Mode Prescaler
  * @{
  * @brief Constants defining the prescaling ratio of the fHRTIM clock
  *        for the burst mode controller
  */
#define HRTIM_BURSTMODEPRESCALER_DIV1     (0x00000000U)                                                                           /*!< fBRST = fHRTIM */
#define HRTIM_BURSTMODEPRESCALER_DIV2     (HRTIM_BMCR_BMPRSC_0)                                                                   /*!< fBRST = fHRTIM/2U */
#define HRTIM_BURSTMODEPRESCALER_DIV4     (HRTIM_BMCR_BMPRSC_1)                                                                   /*!< fBRST = fHRTIM/4U */
#define HRTIM_BURSTMODEPRESCALER_DIV8     (HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0)                                             /*!< fBRST = fHRTIM/8U */
#define HRTIM_BURSTMODEPRESCALER_DIV16    (HRTIM_BMCR_BMPRSC_2)                                                                   /*!< fBRST = fHRTIM/16U */
#define HRTIM_BURSTMODEPRESCALER_DIV32    (HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_0)                                             /*!< fBRST = fHRTIM/32U */
#define HRTIM_BURSTMODEPRESCALER_DIV64    (HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1)                                             /*!< fBRST = fHRTIM/64U */
#define HRTIM_BURSTMODEPRESCALER_DIV128   (HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0)                       /*!< fBRST = fHRTIM/128U */
#define HRTIM_BURSTMODEPRESCALER_DIV256   (HRTIM_BMCR_BMPRSC_3)                                                                   /*!< fBRST = fHRTIM/256U */
#define HRTIM_BURSTMODEPRESCALER_DIV512   (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_0)                                             /*!< fBRST = fHRTIM/512U */
#define HRTIM_BURSTMODEPRESCALER_DIV1024  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_1)                                             /*!< fBRST = fHRTIM/1024U */
#define HRTIM_BURSTMODEPRESCALER_DIV2048  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0)                       /*!< fBRST = fHRTIM/2048U*/
#define HRTIM_BURSTMODEPRESCALER_DIV4096  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2)                                             /*!< fBRST = fHRTIM/4096U */
#define HRTIM_BURSTMODEPRESCALER_DIV8192  (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_0)                       /*!< fBRST = fHRTIM/8192U */
#define HRTIM_BURSTMODEPRESCALER_DIV16384 (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1)                       /*!< fBRST = fHRTIM/16384U */
#define HRTIM_BURSTMODEPRESCALER_DIV32768 (HRTIM_BMCR_BMPRSC_3 | HRTIM_BMCR_BMPRSC_2 | HRTIM_BMCR_BMPRSC_1 | HRTIM_BMCR_BMPRSC_0) /*!< fBRST = fHRTIM/32768U */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Register_Preload_Enable HRTIM Burst Mode Register Preload Enable
  * @{
  * @brief Constants defining whether or not burst mode registers preload
           mechanism is enabled, i.e. a write access into a preloadable register
          (HRTIM_BMCMPR, HRTIM_BMPER) is done into the active or the preload register
  */
#define HRIM_BURSTMODEPRELOAD_DISABLED (0x00000000U)  /*!< Preload disabled: the write access is directly done into active registers */
#define HRIM_BURSTMODEPRELOAD_ENABLED  (HRTIM_BMCR_BMPREN)     /*!< Preload enabled: the write access is done into preload registers */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Trigger HRTIM Burst Mode Trigger
  * @{
  * @brief Constants defining the events that can be used to trig the burst
  *        mode operation
  */
#define HRTIM_BURSTMODETRIGGER_NONE               0x00000000U             /*!<  No trigger */
#define HRTIM_BURSTMODETRIGGER_MASTER_RESET       (HRTIM_BMTRGR_MSTRST)   /*!<  Master reset */
#define HRTIM_BURSTMODETRIGGER_MASTER_REPETITION  (HRTIM_BMTRGR_MSTREP)   /*!<  Master repetition */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP1        (HRTIM_BMTRGR_MSTCMP1)  /*!<  Master compare 1U */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP2        (HRTIM_BMTRGR_MSTCMP2)  /*!<  Master compare 2U */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP3        (HRTIM_BMTRGR_MSTCMP3)  /*!<  Master compare 3U */
#define HRTIM_BURSTMODETRIGGER_MASTER_CMP4        (HRTIM_BMTRGR_MSTCMP4)  /*!<  Master compare 4U */
#define HRTIM_BURSTMODETRIGGER_TIMERA_RESET       (HRTIM_BMTRGR_TARST)    /*!< Timer A reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_REPETITION  (HRTIM_BMTRGR_TAREP)    /*!< Timer A repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_CMP1        (HRTIM_BMTRGR_TACMP1)   /*!< Timer A compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_CMP2        (HRTIM_BMTRGR_TACMP2)   /*!< Timer A compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_RESET       (HRTIM_BMTRGR_TBRST)    /*!< Timer B reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_REPETITION  (HRTIM_BMTRGR_TBREP)    /*!< Timer B repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_CMP1        (HRTIM_BMTRGR_TBCMP1)   /*!< Timer B compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERB_CMP2        (HRTIM_BMTRGR_TBCMP2)   /*!< Timer B compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_RESET       (HRTIM_BMTRGR_TCRST)    /*!< Timer C reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_REPETITION  (HRTIM_BMTRGR_TCREP)    /*!< Timer C repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_CMP1        (HRTIM_BMTRGR_TCCMP1)   /*!< Timer C compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERC_CMP2        (HRTIM_BMTRGR_TCCMP2)   /*!< Timer C compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_RESET       (HRTIM_BMTRGR_TDRST)    /*!< Timer D reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_REPETITION  (HRTIM_BMTRGR_TDREP)    /*!< Timer D repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_CMP1        (HRTIM_BMTRGR_TDCMP1)   /*!< Timer D compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_CMP2        (HRTIM_BMTRGR_TDCMP2)   /*!< Timer D compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_RESET       (HRTIM_BMTRGR_TERST)    /*!< Timer E reset  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_REPETITION  (HRTIM_BMTRGR_TEREP)    /*!< Timer E repetition  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_CMP1        (HRTIM_BMTRGR_TECMP1)   /*!< Timer E compare 1  */
#define HRTIM_BURSTMODETRIGGER_TIMERE_CMP2        (HRTIM_BMTRGR_TECMP2)   /*!< Timer E compare 2  */
#define HRTIM_BURSTMODETRIGGER_TIMERA_EVENT7      (HRTIM_BMTRGR_TAEEV7)   /*!< Timer A period following External Event 7  */
#define HRTIM_BURSTMODETRIGGER_TIMERD_EVENT8      (HRTIM_BMTRGR_TDEEV8)   /*!< Timer D period following External Event 8  */
#define HRTIM_BURSTMODETRIGGER_EVENT_7            (HRTIM_BMTRGR_EEV7)     /*!< External Event 7 (timer A filters applied) */
#define HRTIM_BURSTMODETRIGGER_EVENT_8            (HRTIM_BMTRGR_EEV8)     /*!< External Event 8 (timer D filters applied)*/
#define HRTIM_BURSTMODETRIGGER_EVENT_ONCHIP       (HRTIM_BMTRGR_OCHPEV)   /*!< On-chip Event */
/**
  * @}
  */

/** @defgroup HRTIM_ADC_Trigger_Update_Source HRTIM ADC Trigger Update Source
  * @{
  * @brief constants defining the source triggering the update of the
     HRTIM_ADCxR register (transfer from preload to active register).
  */
#define HRTIM_ADCTRIGGERUPDATE_MASTER  0x00000000U                                   /*!< Master timer */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_A (HRTIM_CR1_ADC1USRC_0)                        /*!< Timer A */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_B (HRTIM_CR1_ADC1USRC_1)                        /*!< Timer B */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_C (HRTIM_CR1_ADC1USRC_1 | HRTIM_CR1_ADC1USRC_0) /*!< Timer C */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_D (HRTIM_CR1_ADC1USRC_2)                        /*!< Timer D */
#define HRTIM_ADCTRIGGERUPDATE_TIMER_E (HRTIM_CR1_ADC1USRC_2 | HRTIM_CR1_ADC1USRC_0) /*!< Timer E */
/**
  * @}
  */

/** @defgroup HRTIM_ADC_Trigger_Event HRTIM ADC Trigger Event
  * @{
  * @brief constants defining the events triggering ADC conversion.
  *        HRTIM_ADCTRIGGEREVENT13_*: ADC Triggers 1 and 3
  *        HRTIM_ADCTRIGGEREVENT24_*: ADC Triggers 2 and 4
  */
#define HRTIM_ADCTRIGGEREVENT13_NONE           0x00000000U              /*!< No ADC trigger event */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP1    (HRTIM_ADC1R_AD1MC1)     /*!< ADC Trigger on master compare 1U */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP2    (HRTIM_ADC1R_AD1MC2)     /*!< ADC Trigger on master compare 2U */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP3    (HRTIM_ADC1R_AD1MC3)     /*!< ADC Trigger on master compare 3U */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_CMP4    (HRTIM_ADC1R_AD1MC4)     /*!< ADC Trigger on master compare 4U */
#define HRTIM_ADCTRIGGEREVENT13_MASTER_PERIOD  (HRTIM_ADC1R_AD1MPER)    /*!< ADC Trigger on master period */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_1        (HRTIM_ADC1R_AD1EEV1)    /*!< ADC Trigger on external event 1U */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_2        (HRTIM_ADC1R_AD1EEV2)    /*!< ADC Trigger on external event 2U */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_3        (HRTIM_ADC1R_AD1EEV3)    /*!< ADC Trigger on external event 3U */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_4        (HRTIM_ADC1R_AD1EEV4)    /*!< ADC Trigger on external event 4U */
#define HRTIM_ADCTRIGGEREVENT13_EVENT_5        (HRTIM_ADC1R_AD1EEV5)    /*!< ADC Trigger on external event 5U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_CMP2    (HRTIM_ADC1R_AD1TAC2)    /*!< ADC Trigger on Timer A compare 2U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_CMP3    (HRTIM_ADC1R_AD1TAC3)    /*!< ADC Trigger on Timer A compare 3U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_CMP4    (HRTIM_ADC1R_AD1TAC4)    /*!< ADC Trigger on Timer A compare 4U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_PERIOD  (HRTIM_ADC1R_AD1TAPER)   /*!< ADC Trigger on Timer A period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERA_RESET   (HRTIM_ADC1R_AD1TARST)   /*!< ADC Trigger on Timer A reset */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_CMP2    (HRTIM_ADC1R_AD1TBC2)    /*!< ADC Trigger on Timer B compare 2U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_CMP3    (HRTIM_ADC1R_AD1TBC3)    /*!< ADC Trigger on Timer B compare 3U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_CMP4    (HRTIM_ADC1R_AD1TBC4)    /*!< ADC Trigger on Timer B compare 4U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_PERIOD  (HRTIM_ADC1R_AD1TBPER)   /*!< ADC Trigger on Timer B period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERB_RESET   (HRTIM_ADC1R_AD1TBRST)   /*!< ADC Trigger on Timer B reset */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_CMP2    (HRTIM_ADC1R_AD1TCC2)    /*!< ADC Trigger on Timer C compare 2U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_CMP3    (HRTIM_ADC1R_AD1TCC3)    /*!< ADC Trigger on Timer C compare 3U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_CMP4    (HRTIM_ADC1R_AD1TCC4)    /*!< ADC Trigger on Timer C compare 4U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERC_PERIOD  (HRTIM_ADC1R_AD1TCPER)   /*!< ADC Trigger on Timer C period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_CMP2    (HRTIM_ADC1R_AD1TDC2)    /*!< ADC Trigger on Timer D compare 2U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_CMP3    (HRTIM_ADC1R_AD1TDC3)    /*!< ADC Trigger on Timer D compare 3U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_CMP4    (HRTIM_ADC1R_AD1TDC4)    /*!< ADC Trigger on Timer D compare 4U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERD_PERIOD  (HRTIM_ADC1R_AD1TDPER)   /*!< ADC Trigger on Timer D period */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_CMP2    (HRTIM_ADC1R_AD1TEC2)    /*!< ADC Trigger on Timer E compare 2U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_CMP3    (HRTIM_ADC1R_AD1TEC3)    /*!< ADC Trigger on Timer E compare 3U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_CMP4    (HRTIM_ADC1R_AD1TEC4)    /*!< ADC Trigger on Timer E compare 4U */
#define HRTIM_ADCTRIGGEREVENT13_TIMERE_PERIOD  (HRTIM_ADC1R_AD1TEPER)   /*!< ADC Trigger on Timer E period */

#define HRTIM_ADCTRIGGEREVENT24_NONE           0x00000000U               /*!< No ADC trigger event */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP1    (HRTIM_ADC2R_AD2MC1)     /*!< ADC Trigger on master compare 1U */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP2    (HRTIM_ADC2R_AD2MC2)     /*!< ADC Trigger on master compare 2U */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP3    (HRTIM_ADC2R_AD2MC3)     /*!< ADC Trigger on master compare 3U */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_CMP4    (HRTIM_ADC2R_AD2MC4)     /*!< ADC Trigger on master compare 4U */
#define HRTIM_ADCTRIGGEREVENT24_MASTER_PERIOD  (HRTIM_ADC2R_AD2MPER)    /*!< ADC Trigger on master period */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_6        (HRTIM_ADC2R_AD2EEV6)    /*!< ADC Trigger on external event 6U */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_7        (HRTIM_ADC2R_AD2EEV7)    /*!< ADC Trigger on external event 7U */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_8        (HRTIM_ADC2R_AD2EEV8)    /*!< ADC Trigger on external event 8U */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_9        (HRTIM_ADC2R_AD2EEV9)    /*!< ADC Trigger on external event 9U */
#define HRTIM_ADCTRIGGEREVENT24_EVENT_10       (HRTIM_ADC2R_AD2EEV10)   /*!< ADC Trigger on external event 10U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_CMP2    (HRTIM_ADC2R_AD2TAC2)    /*!< ADC Trigger on Timer A compare 2U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_CMP3    (HRTIM_ADC2R_AD2TAC3)    /*!< ADC Trigger on Timer A compare 3U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_CMP4    (HRTIM_ADC2R_AD2TAC4)    /*!< ADC Trigger on Timer A compare 4U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERA_PERIOD  (HRTIM_ADC2R_AD2TAPER)   /*!< ADC Trigger on Timer A period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_CMP2    (HRTIM_ADC2R_AD2TBC2)    /*!< ADC Trigger on Timer B compare 2U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_CMP3    (HRTIM_ADC2R_AD2TBC3)    /*!< ADC Trigger on Timer B compare 3U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_CMP4    (HRTIM_ADC2R_AD2TBC4)    /*!< ADC Trigger on Timer B compare 4U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERB_PERIOD  (HRTIM_ADC2R_AD2TBPER)   /*!< ADC Trigger on Timer B period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_CMP2    (HRTIM_ADC2R_AD2TCC2)    /*!< ADC Trigger on Timer C compare 2U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_CMP3    (HRTIM_ADC2R_AD2TCC3)    /*!< ADC Trigger on Timer C compare 3U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_CMP4    (HRTIM_ADC2R_AD2TCC4)    /*!< ADC Trigger on Timer C compare 4U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_PERIOD  (HRTIM_ADC2R_AD2TCPER)   /*!< ADC Trigger on Timer C period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERC_RESET   (HRTIM_ADC2R_AD2TCRST)   /*!< ADC Trigger on Timer C reset */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP2    (HRTIM_ADC2R_AD2TDC2)    /*!< ADC Trigger on Timer D compare 2U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP3    (HRTIM_ADC2R_AD2TDC3)    /*!< ADC Trigger on Timer D compare 3U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_CMP4    (HRTIM_ADC2R_AD2TDC4)    /*!< ADC Trigger on Timer D compare 4U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_PERIOD  (HRTIM_ADC2R_AD2TDPER)   /*!< ADC Trigger on Timer D period */
#define HRTIM_ADCTRIGGEREVENT24_TIMERD_RESET   (HRTIM_ADC2R_AD2TDRST)   /*!< ADC Trigger on Timer D reset */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_CMP2    (HRTIM_ADC2R_AD2TEC2)    /*!< ADC Trigger on Timer E compare 2U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_CMP3    (HRTIM_ADC2R_AD2TEC3)    /*!< ADC Trigger on Timer E compare 3U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_CMP4    (HRTIM_ADC2R_AD2TEC4)    /*!< ADC Trigger on Timer E compare 4U */
#define HRTIM_ADCTRIGGEREVENT24_TIMERE_RESET   (HRTIM_ADC2R_AD2TERST)   /*!< ADC Trigger on Timer E reset */

/**
  * @}
  */

/** @defgroup HRTIM_Burst_DMA_Registers_Update HRTIM Burst DMA Registers Update
  * @{
  * @brief Constants defining the registers that can be written during a burst
  *        DMA operation
  */
#define HRTIM_BURSTDMA_NONE  0x00000000U               /*!< No register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CR    (HRTIM_BDTUPR_TIMCR)      /*!< MCR or TIMxCR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_ICR   (HRTIM_BDTUPR_TIMICR)     /*!< MICR or TIMxICR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_DIER  (HRTIM_BDTUPR_TIMDIER)    /*!< MDIER or TIMxDIER register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CNT   (HRTIM_BDTUPR_TIMCNT)     /*!< MCNTR or CNTxCR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_PER   (HRTIM_BDTUPR_TIMPER)     /*!< MPER or PERxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_REP   (HRTIM_BDTUPR_TIMREP)     /*!< MREPR or REPxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP1  (HRTIM_BDTUPR_TIMCMP1)    /*!< MCMP1R or CMP1xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP2  (HRTIM_BDTUPR_TIMCMP2)    /*!< MCMP2R or CMP2xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP3  (HRTIM_BDTUPR_TIMCMP3)    /*!< MCMP3R or CMP3xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CMP4  (HRTIM_BDTUPR_TIMCMP4)    /*!< MCMP4R or CMP4xR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_DTR   (HRTIM_BDTUPR_TIMDTR)     /*!< TDxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_SET1R (HRTIM_BDTUPR_TIMSET1R)   /*!< SET1R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_RST1R (HRTIM_BDTUPR_TIMRST1R)   /*!< RST1R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_SET2R (HRTIM_BDTUPR_TIMSET2R)   /*!< SET2R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_RST2R (HRTIM_BDTUPR_TIMRST2R)   /*!< RST1R register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_EEFR1 (HRTIM_BDTUPR_TIMEEFR1)   /*!< EEFxR1 register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_EEFR2 (HRTIM_BDTUPR_TIMEEFR2)   /*!< EEFxR2 register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_RSTR  (HRTIM_BDTUPR_TIMRSTR)    /*!< RSTxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_CHPR  (HRTIM_BDTUPR_TIMCHPR)    /*!< CHPxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_OUTR  (HRTIM_BDTUPR_TIMOUTR)    /*!< OUTxR register is updated by Burst DMA accesses */
#define HRTIM_BURSTDMA_FLTR  (HRTIM_BDTUPR_TIMFLTR)    /*!< FLTxR register is updated by Burst DMA accesses */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Control HRTIM Burst Mode Control
  * @{
  * @brief Constants used to enable or disable the burst mode controller
  */
#define HRTIM_BURSTMODECTL_DISABLED 0x00000000U          /*!< Burst mode disabled */
#define HRTIM_BURSTMODECTL_ENABLED  (HRTIM_BMCR_BME)     /*!< Burst mode enabled */
/**
  * @}
  */

/** @defgroup HRTIM_Fault_Mode_Control  HRTIM Fault Mode Control
  * @{
  * @brief Constants used to enable or disable a fault channel
  */
#define HRTIM_FAULTMODECTL_DISABLED 0x00000000U /*!< Fault channel is disabled */
#define HRTIM_FAULTMODECTL_ENABLED  0x00000001U /*!< Fault channel is  enabled */
/**
  * @}
  */

/** @defgroup HRTIM_Software_Timer_Update HRTIM Software Timer Update
  * @{
  * @brief Constants used to force timer registers update
  */
#define HRTIM_TIMERUPDATE_MASTER    (HRTIM_CR2_MSWU)     /*!< Force an immediate transfer from the preload to the active register in the master timer */
#define HRTIM_TIMERUPDATE_A         (HRTIM_CR2_TASWU)    /*!< Force an immediate transfer from the preload to the active register in the timer A */
#define HRTIM_TIMERUPDATE_B         (HRTIM_CR2_TBSWU)    /*!< Force an immediate transfer from the preload to the active register in the timer B */
#define HRTIM_TIMERUPDATE_C         (HRTIM_CR2_TCSWU)    /*!< Force an immediate transfer from the preload to the active register in the timer C */
#define HRTIM_TIMERUPDATE_D         (HRTIM_CR2_TDSWU)    /*!< Force an immediate transfer from the preload to the active register in the timer D */
#define HRTIM_TIMERUPDATE_E         (HRTIM_CR2_TESWU)    /*!< Force an immediate transfer from the preload to the active register in the timer E */
/**
  * @}
  */

/** @defgroup HRTIM_Software_Timer_Reset HRTIM Software Timer Reset
  * @{
  * @brief Constants used to force timer counter reset
  */
#define HRTIM_TIMERRESET_MASTER    (HRTIM_CR2_MRST)     /*!< Reset the master timer counter */
#define HRTIM_TIMERRESET_TIMER_A   (HRTIM_CR2_TARST)    /*!< Reset the timer A counter */
#define HRTIM_TIMERRESET_TIMER_B   (HRTIM_CR2_TBRST)    /*!< Reset the timer B counter */
#define HRTIM_TIMERRESET_TIMER_C   (HRTIM_CR2_TCRST)    /*!< Reset the timer C counter */
#define HRTIM_TIMERRESET_TIMER_D   (HRTIM_CR2_TDRST)    /*!< Reset the timer D counter */
#define HRTIM_TIMERRESET_TIMER_E   (HRTIM_CR2_TERST)    /*!< Reset the timer E counter */
/**
  * @}
  */

/** @defgroup HRTIM_Output_Level HRTIM Output Level
  * @{
  * @brief Constants defining the level of a timer output
  */
#define HRTIM_OUTPUTLEVEL_ACTIVE     (0x00000001U) /*!< Force the output to its active state */
#define HRTIM_OUTPUTLEVEL_INACTIVE   (0x00000002U) /*!< Force the output to its inactive state */

#define IS_HRTIM_OUTPUTLEVEL(OUTPUTLEVEL)\
    (((OUTPUTLEVEL) == HRTIM_OUTPUTLEVEL_ACTIVE)  || \
     ((OUTPUTLEVEL) == HRTIM_OUTPUTLEVEL_INACTIVE))
/**
  * @}
  */

/** @defgroup HRTIM_Output_State HRTIM Output State
  * @{
  * @brief Constants defining the state of a timer output
  */
#define HRTIM_OUTPUTSTATE_IDLE     (0x00000001U)  /*!< Main operating mode, where the output can take the active or
                                                              inactive level as programmed in the crossbar unit */
#define HRTIM_OUTPUTSTATE_RUN      (0x00000002U)  /*!< Default operating state (e.g. after an HRTIM reset, when the
                                                              outputs are disabled by software or during a burst mode operation */
#define HRTIM_OUTPUTSTATE_FAULT    (0x00000003U)  /*!< Safety state, entered in case of a shut-down request on
                                                              FAULTx inputs */
/**
  * @}
  */

/** @defgroup HRTIM_Burst_Mode_Status HRTIM Burst Mode Status
  * @{
  * @brief Constants defining the operating state of the burst mode controller
  */
#define HRTIM_BURSTMODESTATUS_NORMAL   0x00000000U          /*!< Normal operation */
#define HRTIM_BURSTMODESTATUS_ONGOING (HRTIM_BMCR_BMSTAT)   /*!< Burst operation on-going */
/**
  * @}
  */

/** @defgroup HRTIM_Current_Push_Pull_Status HRTIM Current Push Pull Status
  * @{
  * @brief Constants defining on which output the signal is currently applied
  *        in push-pull mode
  */
#define HRTIM_PUSHPULL_CURRENTSTATUS_OUTPUT1    0x00000000U            /*!< Signal applied on output 1 and output 2 forced inactive */
#define HRTIM_PUSHPULL_CURRENTSTATUS_OUTPUT2   (HRTIM_TIMISR_CPPSTAT)  /*!< Signal applied on output 2 and output 1 forced inactive */
/**
  * @}
  */

/** @defgroup HRTIM_Idle_Push_Pull_Status HRTIM Idle Push Pull Status
  * @{
  * @brief Constants defining on which output the signal was applied, in
  *        push-pull mode balanced fault mode or delayed idle mode, when the
  *        protection was triggered
  */
#define HRTIM_PUSHPULL_IDLESTATUS_OUTPUT1    0x00000000U               /*!< Protection occurred when the output 1 was active and output 2 forced inactive */
#define HRTIM_PUSHPULL_IDLESTATUS_OUTPUT2   (HRTIM_TIMISR_IPPSTAT)     /*!< Protection occurred when the output 2 was active and output 1 forced inactive */
/**
  * @}
  */

/** @defgroup HRTIM_Common_Interrupt_Enable HRTIM Common Interrupt Enable
  * @{
  */
#define HRTIM_IT_NONE           0x00000000U           /*!< No interrupt enabled */
#define HRTIM_IT_FLT1           HRTIM_IER_FLT1        /*!< Fault 1 interrupt enable */
#define HRTIM_IT_FLT2           HRTIM_IER_FLT2        /*!< Fault 2 interrupt enable */
#define HRTIM_IT_FLT3           HRTIM_IER_FLT3        /*!< Fault 3 interrupt enable */
#define HRTIM_IT_FLT4           HRTIM_IER_FLT4        /*!< Fault 4 interrupt enable */
#define HRTIM_IT_FLT5           HRTIM_IER_FLT5        /*!< Fault 5 interrupt enable */
#define HRTIM_IT_SYSFLT         HRTIM_IER_SYSFLT      /*!< System Fault interrupt enable */
#define HRTIM_IT_BMPER          HRTIM_IER_BMPER       /*!<  Burst mode period interrupt enable */
/**
  * @}
  */

/** @defgroup HRTIM_Master_Interrupt_Enable HRTIM Master Interrupt Enable
  * @{
  */
#define HRTIM_MASTER_IT_NONE         0x00000000U           /*!< No interrupt enabled */
#define HRTIM_MASTER_IT_MCMP1        HRTIM_MDIER_MCMP1IE   /*!< Master compare 1 interrupt enable */
#define HRTIM_MASTER_IT_MCMP2        HRTIM_MDIER_MCMP2IE   /*!< Master compare 2 interrupt enable */
#define HRTIM_MASTER_IT_MCMP3        HRTIM_MDIER_MCMP3IE   /*!< Master compare 3 interrupt enable */
#define HRTIM_MASTER_IT_MCMP4        HRTIM_MDIER_MCMP4IE   /*!< Master compare 4 interrupt enable */
#define HRTIM_MASTER_IT_MREP         HRTIM_MDIER_MREPIE    /*!< Master Repetition interrupt enable */
#define HRTIM_MASTER_IT_SYNC         HRTIM_MDIER_SYNCIE    /*!< Synchronization input interrupt enable */
#define HRTIM_MASTER_IT_MUPD         HRTIM_MDIER_MUPDIE    /*!< Master update interrupt enable */
/**
  * @}
  */

/** @defgroup HRTIM_Timing_Unit_Interrupt_Enable HRTIM Timing Unit Interrupt Enable
  * @{
  */
#define HRTIM_TIM_IT_NONE       0x00000000U               /*!< No interrupt enabled */
#define HRTIM_TIM_IT_CMP1       HRTIM_TIMDIER_CMP1IE      /*!< Timer compare 1 interrupt enable */
#define HRTIM_TIM_IT_CMP2       HRTIM_TIMDIER_CMP2IE      /*!< Timer compare 2 interrupt enable */
#define HRTIM_TIM_IT_CMP3       HRTIM_TIMDIER_CMP3IE      /*!< Timer compare 3 interrupt enable */
#define HRTIM_TIM_IT_CMP4       HRTIM_TIMDIER_CMP4IE      /*!< Timer compare 4 interrupt enable */
#define HRTIM_TIM_IT_REP        HRTIM_TIMDIER_REPIE       /*!< Timer repetition interrupt enable */
#define HRTIM_TIM_IT_UPD        HRTIM_TIMDIER_UPDIE       /*!< Timer update interrupt enable */
#define HRTIM_TIM_IT_CPT1       HRTIM_TIMDIER_CPT1IE      /*!< Timer capture 1 interrupt enable */
#define HRTIM_TIM_IT_CPT2       HRTIM_TIMDIER_CPT2IE      /*!< Timer capture 2 interrupt enable */
#define HRTIM_TIM_IT_SET1       HRTIM_TIMDIER_SET1IE      /*!< Timer output 1 set interrupt enable */
#define HRTIM_TIM_IT_RST1       HRTIM_TIMDIER_RST1IE      /*!< Timer output 1 reset interrupt enable */
#define HRTIM_TIM_IT_SET2       HRTIM_TIMDIER_SET2IE      /*!< Timer output 2 set interrupt enable */
#define HRTIM_TIM_IT_RST2       HRTIM_TIMDIER_RST2IE      /*!< Timer output 2 reset interrupt enable */
#define HRTIM_TIM_IT_RST        HRTIM_TIMDIER_RSTIE       /*!< Timer reset interrupt enable */
#define HRTIM_TIM_IT_DLYPRT     HRTIM_TIMDIER_DLYPRTIE    /*!< Timer delay protection interrupt enable */
/**
  * @}
  */

/** @defgroup HRTIM_Common_Interrupt_Flag HRTIM Common Interrupt Flag
  * @{
  */
#define HRTIM_FLAG_FLT1           HRTIM_ISR_FLT1    /*!< Fault 1 interrupt flag */
#define HRTIM_FLAG_FLT2           HRTIM_ISR_FLT2    /*!< Fault 2 interrupt flag */
#define HRTIM_FLAG_FLT3           HRTIM_ISR_FLT3    /*!< Fault 3 interrupt flag */
#define HRTIM_FLAG_FLT4           HRTIM_ISR_FLT4    /*!< Fault 4 interrupt flag */
#define HRTIM_FLAG_FLT5           HRTIM_ISR_FLT5    /*!< Fault 5 interrupt flag */
#define HRTIM_FLAG_SYSFLT         HRTIM_ISR_SYSFLT  /*!< System Fault interrupt flag */
#define HRTIM_FLAG_BMPER          HRTIM_ISR_BMPER   /*!< Burst mode period interrupt flag */
/**
  * @}
  */

/** @defgroup HRTIM_Master_Interrupt_Flag HRTIM Master Interrupt Flag
  * @{
  */
#define HRTIM_MASTER_FLAG_MCMP1        HRTIM_MISR_MCMP1    /*!< Master compare 1 interrupt flag */
#define HRTIM_MASTER_FLAG_MCMP2        HRTIM_MISR_MCMP2    /*!< Master compare 2 interrupt flag */
#define HRTIM_MASTER_FLAG_MCMP3        HRTIM_MISR_MCMP3    /*!< Master compare 3 interrupt flag */
#define HRTIM_MASTER_FLAG_MCMP4        HRTIM_MISR_MCMP4    /*!< Master compare 4 interrupt flag */
#define HRTIM_MASTER_FLAG_MREP         HRTIM_MISR_MREP     /*!< Master Repetition interrupt flag */
#define HRTIM_MASTER_FLAG_SYNC         HRTIM_MISR_SYNC     /*!< Synchronization input interrupt flag */
#define HRTIM_MASTER_FLAG_MUPD         HRTIM_MISR_MUPD     /*!< Master update interrupt flag */
/**
  * @}
  */

/** @defgroup HRTIM_Timing_Unit_Interrupt_Flag HRTIM Timing Unit Interrupt Flag
  * @{
  */
#define HRTIM_TIM_FLAG_CMP1       HRTIM_TIMISR_CMP1      /*!< Timer compare 1 interrupt flag */
#define HRTIM_TIM_FLAG_CMP2       HRTIM_TIMISR_CMP2      /*!< Timer compare 2 interrupt flag */
#define HRTIM_TIM_FLAG_CMP3       HRTIM_TIMISR_CMP3      /*!< Timer compare 3 interrupt flag */
#define HRTIM_TIM_FLAG_CMP4       HRTIM_TIMISR_CMP4      /*!< Timer compare 4 interrupt flag */
#define HRTIM_TIM_FLAG_REP        HRTIM_TIMISR_REP       /*!< Timer repetition interrupt flag */
#define HRTIM_TIM_FLAG_UPD        HRTIM_TIMISR_UPD       /*!< Timer update interrupt flag */
#define HRTIM_TIM_FLAG_CPT1       HRTIM_TIMISR_CPT1      /*!< Timer capture 1 interrupt flag */
#define HRTIM_TIM_FLAG_CPT2       HRTIM_TIMISR_CPT2      /*!< Timer capture 2 interrupt flag */
#define HRTIM_TIM_FLAG_SET1       HRTIM_TIMISR_SET1      /*!< Timer output 1 set interrupt flag */
#define HRTIM_TIM_FLAG_RST1       HRTIM_TIMISR_RST1      /*!< Timer output 1 reset interrupt flag */
#define HRTIM_TIM_FLAG_SET2       HRTIM_TIMISR_SET2      /*!< Timer output 2 set interrupt flag */
#define HRTIM_TIM_FLAG_RST2       HRTIM_TIMISR_RST2      /*!< Timer output 2 reset interrupt flag */
#define HRTIM_TIM_FLAG_RST        HRTIM_TIMISR_RST       /*!< Timer reset interrupt flag */
#define HRTIM_TIM_FLAG_DLYPRT     HRTIM_TIMISR_DLYPRT    /*!< Timer delay protection interrupt flag */
/**
  * @}
  */

/** @defgroup HRTIM_Master_DMA_Request_Enable HRTIM Master DMA Request Enable
  * @{
  */
#define HRTIM_MASTER_DMA_NONE         0x00000000U            /*!< No DMA request enable */
#define HRTIM_MASTER_DMA_MCMP1        HRTIM_MDIER_MCMP1DE    /*!< Master compare 1 DMA request enable */
#define HRTIM_MASTER_DMA_MCMP2        HRTIM_MDIER_MCMP2DE    /*!< Master compare 2 DMA request enable */
#define HRTIM_MASTER_DMA_MCMP3        HRTIM_MDIER_MCMP3DE    /*!< Master compare 3 DMA request enable */
#define HRTIM_MASTER_DMA_MCMP4        HRTIM_MDIER_MCMP4DE    /*!< Master compare 4 DMA request enable */
#define HRTIM_MASTER_DMA_MREP         HRTIM_MDIER_MREPDE     /*!< Master Repetition DMA request enable */
#define HRTIM_MASTER_DMA_SYNC         HRTIM_MDIER_SYNCDE     /*!< Synchronization input DMA request enable */
#define HRTIM_MASTER_DMA_MUPD         HRTIM_MDIER_MUPDDE     /*!< Master update DMA request enable */
/**
  * @}
  */

/** @defgroup HRTIM_Timing_Unit_DMA_Request_Enable HRTIM Timing Unit DMA Request Enable
  * @{
  */
#define HRTIM_TIM_DMA_NONE       0x00000000U               /*!< No DMA request enable */
#define HRTIM_TIM_DMA_CMP1       HRTIM_TIMDIER_CMP1DE      /*!< Timer compare 1 DMA request enable */
#define HRTIM_TIM_DMA_CMP2       HRTIM_TIMDIER_CMP2DE      /*!< Timer compare 2 DMA request enable */
#define HRTIM_TIM_DMA_CMP3       HRTIM_TIMDIER_CMP3DE      /*!< Timer compare 3 DMA request enable */
#define HRTIM_TIM_DMA_CMP4       HRTIM_TIMDIER_CMP4DE      /*!< Timer compare 4 DMA request enable */
#define HRTIM_TIM_DMA_REP        HRTIM_TIMDIER_REPDE       /*!< Timer repetition DMA request enable */
#define HRTIM_TIM_DMA_UPD        HRTIM_TIMDIER_UPDDE       /*!< Timer update DMA request enable */
#define HRTIM_TIM_DMA_CPT1       HRTIM_TIMDIER_CPT1DE      /*!< Timer capture 1 DMA request enable */
#define HRTIM_TIM_DMA_CPT2       HRTIM_TIMDIER_CPT2DE      /*!< Timer capture 2 DMA request enable */
#define HRTIM_TIM_DMA_SET1       HRTIM_TIMDIER_SET1DE      /*!< Timer output 1 set DMA request enable */
#define HRTIM_TIM_DMA_RST1       HRTIM_TIMDIER_RST1DE      /*!< Timer output 1 reset DMA request enable */
#define HRTIM_TIM_DMA_SET2       HRTIM_TIMDIER_SET2DE      /*!< Timer output 2 set DMA request enable */
#define HRTIM_TIM_DMA_RST2       HRTIM_TIMDIER_RST2DE      /*!< Timer output 2 reset DMA request enable */
#define HRTIM_TIM_DMA_RST        HRTIM_TIMDIER_RSTDE       /*!< Timer reset DMA request enable */
#define HRTIM_TIM_DMA_DLYPRT     HRTIM_TIMDIER_DLYPRTDE    /*!< Timer delay protection DMA request enable */
/**
  * @}
  */

/**
  * @}
  */

  /* Private macros --------------------------------------------------------*/
/** @addtogroup HRTIM_Private_Macros
  * @{
  */
#define IS_HRTIM_TIMERINDEX(TIMERINDEX)\
    (((TIMERINDEX) == HRTIM_TIMERINDEX_MASTER)   || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_A)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_B)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_C)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_D)  || \
     ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_E))

#define IS_HRTIM_TIMING_UNIT(TIMERINDEX)\
     (((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_A)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_B)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_C)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_D)  || \
      ((TIMERINDEX) == HRTIM_TIMERINDEX_TIMER_E))

#define IS_HRTIM_TIMERID(TIMERID) (((TIMERID) & 0xFFC0FFFFU) == 0x00000000U)

#define IS_HRTIM_COMPAREUNIT(COMPAREUNIT)\
    (((COMPAREUNIT) == HRTIM_COMPAREUNIT_1)  || \
     ((COMPAREUNIT) == HRTIM_COMPAREUNIT_2)  || \
     ((COMPAREUNIT) == HRTIM_COMPAREUNIT_3)  || \
     ((COMPAREUNIT) == HRTIM_COMPAREUNIT_4))

#define IS_HRTIM_CAPTUREUNIT(CAPTUREUNIT)\
    (((CAPTUREUNIT) == HRTIM_CAPTUREUNIT_1)   || \
     ((CAPTUREUNIT) == HRTIM_CAPTUREUNIT_2))

#define IS_HRTIM_OUTPUT(OUTPUT) (((OUTPUT) & 0xFFFFFC00U) == 0x00000000U)

#define IS_HRTIM_TIMER_OUTPUT(TIMER, OUTPUT)\
    ((((TIMER) == HRTIM_TIMERINDEX_TIMER_A) &&   \
     (((OUTPUT) == HRTIM_OUTPUT_TA1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TA2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_B) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TB1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TB2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_C) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TC1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TC2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_D) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TD1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TD2)))           \
    ||                                           \
    (((TIMER) == HRTIM_TIMERINDEX_TIMER_E) &&    \
     (((OUTPUT) == HRTIM_OUTPUT_TE1) ||          \
      ((OUTPUT) == HRTIM_OUTPUT_TE2))))

#define IS_HRTIM_EVENT(EVENT)\
      (((EVENT) == HRTIM_EVENT_NONE)|| \
       ((EVENT) == HRTIM_EVENT_1)   || \
       ((EVENT) == HRTIM_EVENT_2)   || \
       ((EVENT) == HRTIM_EVENT_3)   || \
       ((EVENT) == HRTIM_EVENT_4)   || \
       ((EVENT) == HRTIM_EVENT_5)   || \
       ((EVENT) == HRTIM_EVENT_6)   || \
       ((EVENT) == HRTIM_EVENT_7)   || \
       ((EVENT) == HRTIM_EVENT_8)   || \
       ((EVENT) == HRTIM_EVENT_9)   || \
       ((EVENT) == HRTIM_EVENT_10))

#define IS_HRTIM_FAULT(FAULT)\
      (((FAULT) == HRTIM_FAULT_1)   || \
       ((FAULT) == HRTIM_FAULT_2)   || \
       ((FAULT) == HRTIM_FAULT_3)   || \
       ((FAULT) == HRTIM_FAULT_4)   || \
       ((FAULT) == HRTIM_FAULT_5))

#define IS_HRTIM_PRESCALERRATIO(PRESCALERRATIO)\
        (((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_DIV1) || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_DIV2)  || \
         ((PRESCALERRATIO) == HRTIM_PRESCALERRATIO_DIV4))

#define IS_HRTIM_MODE(MODE)\
          (((MODE) == HRTIM_MODE_CONTINUOUS)  ||  \
           ((MODE) == HRTIM_MODE_SINGLESHOT) || \
           ((MODE) == HRTIM_MODE_SINGLESHOT_RETRIGGERABLE))

#define IS_HRTIM_MODE_ONEPULSE(MODE)\
          (((MODE) == HRTIM_MODE_SINGLESHOT) || \
           ((MODE) == HRTIM_MODE_SINGLESHOT_RETRIGGERABLE))


#define IS_HRTIM_HALFMODE(HALFMODE)\
            (((HALFMODE) == HRTIM_HALFMODE_DISABLED)  ||  \
             ((HALFMODE) == HRTIM_HALFMODE_ENABLED))

#define IS_HRTIM_SYNCSTART(SYNCSTART)\
              (((SYNCSTART) == HRTIM_SYNCSTART_DISABLED)  ||  \
               ((SYNCSTART) == HRTIM_SYNCSTART_ENABLED))

#define IS_HRTIM_SYNCRESET(SYNCRESET)\
                (((SYNCRESET) == HRTIM_SYNCRESET_DISABLED)  ||  \
                 ((SYNCRESET) == HRTIM_SYNCRESET_ENABLED))

#define IS_HRTIM_DACSYNC(DACSYNC)\
                (((DACSYNC) == HRTIM_DACSYNC_NONE)          ||  \
                 ((DACSYNC) == HRTIM_DACSYNC_DACTRIGOUT_1)  ||  \
                 ((DACSYNC) == HRTIM_DACSYNC_DACTRIGOUT_2)  ||  \
                 ((DACSYNC) == HRTIM_DACSYNC_DACTRIGOUT_3))

#define IS_HRTIM_PRELOAD(PRELOAD)\
                (((PRELOAD) == HRTIM_PRELOAD_DISABLED)  ||  \
                 ((PRELOAD) == HRTIM_PRELOAD_ENABLED))

#define IS_HRTIM_UPDATEGATING_MASTER(UPDATEGATING)\
                (((UPDATEGATING) == HRTIM_UPDATEGATING_INDEPENDENT)      ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST)         ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST_UPDATE))

#define IS_HRTIM_UPDATEGATING_TIM(UPDATEGATING)\
                (((UPDATEGATING) == HRTIM_UPDATEGATING_INDEPENDENT)      ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST)         ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_DMABURST_UPDATE)  ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN1)           ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN2)           ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN3)           ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN1_UPDATE)    ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN2_UPDATE)    ||  \
                 ((UPDATEGATING) == HRTIM_UPDATEGATING_UPDEN3_UPDATE))

#define IS_HRTIM_TIMERBURSTMODE(MODE)                               \
                (((MODE) == HRTIM_TIMERBURSTMODE_MAINTAINCLOCK)  || \
                 ((MODE) == HRTIM_TIMERBURSTMODE_RESETCOUNTER))
#define IS_HRTIM_UPDATEONREPETITION(UPDATEONREPETITION)                               \
                (((UPDATEONREPETITION) == HRTIM_UPDATEONREPETITION_DISABLED)  || \
                 ((UPDATEONREPETITION) == HRTIM_UPDATEONREPETITION_ENABLED))

#define IS_HRTIM_TIMPUSHPULLMODE(TIMPUSHPULLMODE)\
                  (((TIMPUSHPULLMODE) == HRTIM_TIMPUSHPULLMODE_DISABLED) || \
                   ((TIMPUSHPULLMODE) == HRTIM_TIMPUSHPULLMODE_ENABLED))
#define IS_HRTIM_TIMFAULTENABLE(TIMFAULTENABLE) (((TIMFAULTENABLE) & 0xFFFFFFE0U) == 0x00000000U)

#define IS_HRTIM_TIMFAULTLOCK(TIMFAULTLOCK)\
      (((TIMFAULTLOCK) == HRTIM_TIMFAULTLOCK_READWRITE) || \
       ((TIMFAULTLOCK) == HRTIM_TIMFAULTLOCK_READONLY))

#define IS_HRTIM_TIMDEADTIMEINSERTION(TIMPUSHPULLMODE, TIMDEADTIMEINSERTION)\
    ((((TIMPUSHPULLMODE) == HRTIM_TIMPUSHPULLMODE_DISABLED) &&               \
        ((((TIMDEADTIMEINSERTION) == HRTIM_TIMDEADTIMEINSERTION_DISABLED) || \
          ((TIMDEADTIMEINSERTION) == HRTIM_TIMDEADTIMEINSERTION_ENABLED))))  \
      ||                                                                     \
        (((TIMPUSHPULLMODE) == HRTIM_TIMPUSHPULLMODE_ENABLED) &&             \
         ((TIMDEADTIMEINSERTION) == HRTIM_TIMDEADTIMEINSERTION_DISABLED)))

#define IS_HRTIM_TIMDELAYEDPROTECTION(TIMPUSHPULLMODE, TIMDELAYEDPROTECTION)\
          ((((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED)          || \
            ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT1_EEV6)  || \
            ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT2_EEV6)  || \
            ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDBOTH_EEV6)  || \
            ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT1_DEEV7) || \
            ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDOUT2_DEEV7) || \
            ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DELAYEDBOTH_EEV7))    \
            ||                                                                           \
            (((TIMPUSHPULLMODE) ==  HRTIM_TIMPUSHPULLMODE_ENABLED) &&                    \
             (((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_BALANCED_EEV6)     || \
             ((TIMDELAYEDPROTECTION) == HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_BALANCED_EEV7))))

#define IS_HRTIM_TIMUPDATETRIGGER(TIMUPDATETRIGGER) (((TIMUPDATETRIGGER) & 0xFE07FFFFU) == 0x00000000U)

#define IS_HRTIM_TIMRESETTRIGGER(TIMRESETTRIGGER) (((TIMRESETTRIGGER) & 0x80000001U) == 0x00000000U)


#define IS_HRTIM_TIMUPDATEONRESET(TIMUPDATEONRESET)                       \
              (((TIMUPDATEONRESET) == HRTIM_TIMUPDATEONRESET_DISABLED) || \
               ((TIMUPDATEONRESET) == HRTIM_TIMUPDATEONRESET_ENABLED))

#define IS_HRTIM_AUTODELAYEDMODE(AUTODELAYEDMODE)\
              (((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR)                  || \
               ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT)    || \
               ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1)  || \
               ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3))

/* Auto delayed mode is only available for compare units 2 and 4U */
#define IS_HRTIM_COMPAREUNIT_AUTODELAYEDMODE(COMPAREUNIT, AUTODELAYEDMODE)     \
    ((((COMPAREUNIT) == HRTIM_COMPAREUNIT_2) &&                                 \
     (((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR)                 ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT)   ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1) ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3)))   \
    ||                                                                         \
    (((COMPAREUNIT) == HRTIM_COMPAREUNIT_4) &&                                 \
     (((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_REGULAR)                 ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_NOTIMEOUT)   ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP1) ||  \
      ((AUTODELAYEDMODE) == HRTIM_AUTODELAYEDMODE_AUTODELAYED_TIMEOUTCMP3))))

#define IS_HRTIM_OUTPUTPOLARITY(OUTPUTPOLARITY)\
              (((OUTPUTPOLARITY) == HRTIM_OUTPUTPOLARITY_HIGH) || \
               ((OUTPUTPOLARITY) == HRTIM_OUTPUTPOLARITY_LOW))

#define IS_HRTIM_OUTPUTPULSE(OUTPUTPULSE) ((OUTPUTPULSE) <= 0x0000FFFFU)

#define IS_HRTIM_OUTPUTSET(OUTPUTSET)\
              (((OUTPUTSET) == HRTIM_OUTPUTSET_NONE)       || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_RESYNC)     || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMPER)     || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP1)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP2)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP3)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMCMP4)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERPER)  || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP1) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP2) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP3) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_MASTERCMP4) || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_1)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_2)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_3)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_4)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_5)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_6)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_7)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_8)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_TIMEV_9)    || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_1)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_2)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_3)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_4)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_5)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_6)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_7)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_8)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_9)      || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_EEV_10)     || \
               ((OUTPUTSET) == HRTIM_OUTPUTSET_UPDATE))

#define IS_HRTIM_OUTPUTRESET(OUTPUTRESET)\
              (((OUTPUTRESET) == HRTIM_OUTPUTRESET_NONE)       || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_RESYNC)     || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMPER)     || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP1)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP2)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP3)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMCMP4)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERPER)  || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP1) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP2) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP3) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_MASTERCMP4) || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_1)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_2)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_3)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_4)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_5)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_6)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_7)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_8)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_TIMEV_9)    || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_1)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_2)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_3)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_4)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_5)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_6)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_7)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_8)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_9)      || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_EEV_10)     || \
               ((OUTPUTRESET) == HRTIM_OUTPUTRESET_UPDATE))

#define IS_HRTIM_OUTPUTIDLEMODE(OUTPUTIDLEMODE)\
              (((OUTPUTIDLEMODE) == HRTIM_OUTPUTIDLEMODE_NONE) || \
               ((OUTPUTIDLEMODE) == HRTIM_OUTPUTIDLEMODE_IDLE))

#define IS_HRTIM_OUTPUTIDLELEVEL(OUTPUTIDLELEVEL)\
              (((OUTPUTIDLELEVEL) == HRTIM_OUTPUTIDLELEVEL_INACTIVE) || \
               ((OUTPUTIDLELEVEL) == HRTIM_OUTPUTIDLELEVEL_ACTIVE))

#define IS_HRTIM_OUTPUTFAULTLEVEL(OUTPUTFAULTLEVEL)\
              (((OUTPUTFAULTLEVEL) == HRTIM_OUTPUTFAULTLEVEL_NONE)     || \
               ((OUTPUTFAULTLEVEL) == HRTIM_OUTPUTFAULTLEVEL_ACTIVE)   || \
               ((OUTPUTFAULTLEVEL) == HRTIM_OUTPUTFAULTLEVEL_INACTIVE) || \
               ((OUTPUTFAULTLEVEL) == HRTIM_OUTPUTFAULTLEVEL_HIGHZ))

#define IS_HRTIM_OUTPUTCHOPPERMODE(OUTPUTCHOPPERMODE)\
              (((OUTPUTCHOPPERMODE) == HRTIM_OUTPUTCHOPPERMODE_DISABLED)  || \
               ((OUTPUTCHOPPERMODE) == HRTIM_OUTPUTCHOPPERMODE_ENABLED))

#define IS_HRTIM_OUTPUTBURSTMODEENTRY(OUTPUTBURSTMODEENTRY)\
              (((OUTPUTBURSTMODEENTRY) == HRTIM_OUTPUTBURSTMODEENTRY_REGULAR)  || \
               ((OUTPUTBURSTMODEENTRY) == HRTIM_OUTPUTBURSTMODEENTRY_DELAYED))


#define IS_HRTIM_TIMER_CAPTURETRIGGER(TIMER, CAPTURETRIGGER)    \
   (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_NONE)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_UPDATE)         || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_1)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_2)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_3)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_4)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_5)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_6)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_7)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_8)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_9)          || \
   ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_EEV_10)            \
   ||                                                           \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_A) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_B) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_C) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_D) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TE1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERE_CMP2)))  \
    ||                                                          \
   (((TIMER) == HRTIM_TIMERINDEX_TIMER_E) &&                    \
     (((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TA1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERA_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TB1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERB_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TC1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERC_CMP2) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_SET)     || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TD1_RESET)   || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP1) || \
      ((CAPTURETRIGGER) == HRTIM_CAPTURETRIGGER_TIMERD_CMP2))))

#define IS_HRTIM_TIMEVENTFILTER(TIMEVENTFILTER)\
                (((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_NONE)           || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP1)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP2)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP3)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGCMP4)   || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR1)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR2)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR3)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR4)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR5)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR6)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR7)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_BLANKINGFLTR8)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_WINDOWINGCMP2)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_WINDOWINGCMP3)  || \
                 ((TIMEVENTFILTER) == HRTIM_TIMEVENTFILTER_WINDOWINGTIM))

#define IS_HRTIM_TIMEVENTLATCH(TIMEVENTLATCH)\
              (((TIMEVENTLATCH) == HRTIM_TIMEVENTLATCH_DISABLED) || \
               ((TIMEVENTLATCH) == HRTIM_TIMEVENTLATCH_ENABLED))

#define IS_HRTIM_TIMDEADTIME_PRESCALERRATIO(PRESCALERRATIO)\
                (((PRESCALERRATIO) == HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV1) || \
                 ((PRESCALERRATIO) == HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV2) || \
                 ((PRESCALERRATIO) == HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV4) || \
                 ((PRESCALERRATIO) == HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV8) || \
                 ((PRESCALERRATIO) == HRTIM_TIMDEADTIME_PRESCALERRATIO_DIV16))

#define IS_HRTIM_TIMDEADTIME_RISINGSIGN(RISINGSIGN)\
                (((RISINGSIGN) == HRTIM_TIMDEADTIME_RISINGSIGN_POSITIVE)    || \
                 ((RISINGSIGN) == HRTIM_TIMDEADTIME_RISINGSIGN_NEGATIVE))

#define IS_HRTIM_TIMDEADTIME_RISINGLOCK(RISINGLOCK)\
                    (((RISINGLOCK) == HRTIM_TIMDEADTIME_RISINGLOCK_WRITE)    || \
                     ((RISINGLOCK) == HRTIM_TIMDEADTIME_RISINGLOCK_READONLY))

#define IS_HRTIM_TIMDEADTIME_RISINGSIGNLOCK(RISINGSIGNLOCK)\
                  (((RISINGSIGNLOCK) == HRTIM_TIMDEADTIME_RISINGSIGNLOCK_WRITE)    || \
                   ((RISINGSIGNLOCK) == HRTIM_TIMDEADTIME_RISINGSIGNLOCK_READONLY))

#define IS_HRTIM_TIMDEADTIME_FALLINGSIGN(FALLINGSIGN)\
                      (((FALLINGSIGN) == HRTIM_TIMDEADTIME_FALLINGSIGN_POSITIVE)    || \
                       ((FALLINGSIGN) == HRTIM_TIMDEADTIME_FALLINGSIGN_NEGATIVE))

#define IS_HRTIM_TIMDEADTIME_FALLINGLOCK(FALLINGLOCK)\
                          (((FALLINGLOCK) == HRTIM_TIMDEADTIME_FALLINGLOCK_WRITE)    || \
                           ((FALLINGLOCK) == HRTIM_TIMDEADTIME_FALLINGLOCK_READONLY))

#define IS_HRTIM_TIMDEADTIME_FALLINGSIGNLOCK(FALLINGSIGNLOCK)\
                        (((FALLINGSIGNLOCK) == HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_WRITE)    || \
                         ((FALLINGSIGNLOCK) == HRTIM_TIMDEADTIME_FALLINGSIGNLOCK_READONLY))

#define IS_HRTIM_CHOPPER_PRESCALERRATIO(PRESCALERRATIO)\
                        (((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV16)    || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV32)    || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV48)    || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV64)    || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV80)    || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV96)    || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV112)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV128)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV144)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV160)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV176)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV192)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV208)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV224)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV240)   || \
                         ((PRESCALERRATIO) == HRTIM_CHOPPER_PRESCALERRATIO_DIV256))

#define IS_HRTIM_CHOPPER_DUTYCYCLE(DUTYCYCLE)\
                        (((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_0)    || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_125)  || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_250)  || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_375)  || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_500)  || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_625)  || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_750)  || \
                         ((DUTYCYCLE) == HRTIM_CHOPPER_DUTYCYCLE_875))

#define IS_HRTIM_CHOPPER_PULSEWIDTH(PULSEWIDTH)\
                        (((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_16)   || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_32)   || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_48)   || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_64)   || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_80)   || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_96)   || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_112)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_128)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_144)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_160)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_176)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_192)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_208)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_224)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_240)  || \
                         ((PULSEWIDTH) == HRTIM_CHOPPER_PULSEWIDTH_256))

#define IS_HRTIM_SYNCINPUTSOURCE(SYNCINPUTSOURCE)\
              (((SYNCINPUTSOURCE) == HRTIM_SYNCINPUTSOURCE_NONE)             || \
               ((SYNCINPUTSOURCE) == HRTIM_SYNCINPUTSOURCE_INTERNALEVENT)    || \
               ((SYNCINPUTSOURCE) == HRTIM_SYNCINPUTSOURCE_EXTERNALEVENT))

#define IS_HRTIM_SYNCOUTPUTSOURCE(SYNCOUTPUTSOURCE)\
              (((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_MASTER_START)  || \
               ((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_MASTER_CMP1)   || \
               ((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_TIMA_START)    || \
               ((SYNCOUTPUTSOURCE) == HRTIM_SYNCOUTPUTSOURCE_TIMA_CMP1))

#define IS_HRTIM_SYNCOUTPUTPOLARITY(SYNCOUTPUTPOLARITY)\
              (((SYNCOUTPUTPOLARITY) == HRTIM_SYNCOUTPUTPOLARITY_NONE)  || \
               ((SYNCOUTPUTPOLARITY) == HRTIM_SYNCOUTPUTPOLARITY_POSITIVE)  || \
               ((SYNCOUTPUTPOLARITY) == HRTIM_SYNCOUTPUTPOLARITY_NEGATIVE))

#define IS_HRTIM_EVENTSRC(EVENTSRC)\
                (((EVENTSRC) == HRTIM_EVENTSRC_1)   || \
                 ((EVENTSRC) == HRTIM_EVENTSRC_2)   || \
                 ((EVENTSRC) == HRTIM_EVENTSRC_3)   || \
                 ((EVENTSRC) == HRTIM_EVENTSRC_4))

#define IS_HRTIM_EVENTPOLARITY(EVENTSENSITIVITY, EVENTPOLARITY)\
    ((((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_LEVEL)  &&      \
       (((EVENTPOLARITY) == HRTIM_EVENTPOLARITY_HIGH)  ||           \
        ((EVENTPOLARITY) == HRTIM_EVENTPOLARITY_LOW)))              \
      ||                                                            \
      (((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_RISINGEDGE) || \
       ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_FALLINGEDGE)|| \
       ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_BOTHEDGES)))

#define IS_HRTIM_EVENTSENSITIVITY(EVENTSENSITIVITY)\
                    (((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_LEVEL)       || \
                     ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_RISINGEDGE)  || \
                     ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_FALLINGEDGE) || \
                     ((EVENTSENSITIVITY) == HRTIM_EVENTSENSITIVITY_BOTHEDGES))

#define IS_HRTIM_EVENTFASTMODE(EVENT, FASTMODE)\
    (((((EVENT) == HRTIM_EVENT_1) ||                 \
       ((EVENT) == HRTIM_EVENT_2) ||                 \
       ((EVENT) == HRTIM_EVENT_3) ||                 \
       ((EVENT) == HRTIM_EVENT_4) ||                 \
       ((EVENT) == HRTIM_EVENT_5)) &&                \
      (((FASTMODE) == HRTIM_EVENTFASTMODE_ENABLE) || \
       ((FASTMODE) == HRTIM_EVENTFASTMODE_DISABLE))) \
    ||                                               \
    (((EVENT) == HRTIM_EVENT_6) ||                   \
     ((EVENT) == HRTIM_EVENT_7) ||                   \
     ((EVENT) == HRTIM_EVENT_8) ||                   \
     ((EVENT) == HRTIM_EVENT_9) ||                   \
     ((EVENT) == HRTIM_EVENT_10)))


#define IS_HRTIM_EVENTFILTER(EVENT, FILTER)\
      ((((EVENT) == HRTIM_EVENT_1) ||            \
        ((EVENT) == HRTIM_EVENT_2) ||            \
        ((EVENT) == HRTIM_EVENT_3) ||            \
        ((EVENT) == HRTIM_EVENT_4) ||            \
        ((EVENT) == HRTIM_EVENT_5))              \
       ||                                        \
      ((((EVENT) == HRTIM_EVENT_6) ||            \
        ((EVENT) == HRTIM_EVENT_7) ||            \
        ((EVENT) == HRTIM_EVENT_8) ||            \
        ((EVENT) == HRTIM_EVENT_9) ||            \
        ((EVENT) == HRTIM_EVENT_10)) &&          \
        (((FILTER) == HRTIM_EVENTFILTER_NONE) || \
        ((FILTER) == HRTIM_EVENTFILTER_1)     || \
        ((FILTER) == HRTIM_EVENTFILTER_2)     || \
        ((FILTER) == HRTIM_EVENTFILTER_3)     || \
        ((FILTER) == HRTIM_EVENTFILTER_4)     || \
        ((FILTER) == HRTIM_EVENTFILTER_5)     || \
        ((FILTER) == HRTIM_EVENTFILTER_6)     || \
        ((FILTER) == HRTIM_EVENTFILTER_7)     || \
        ((FILTER) == HRTIM_EVENTFILTER_8)     || \
        ((FILTER) == HRTIM_EVENTFILTER_9)     || \
        ((FILTER) == HRTIM_EVENTFILTER_10)    || \
        ((FILTER) == HRTIM_EVENTFILTER_11)    || \
        ((FILTER) == HRTIM_EVENTFILTER_12)    || \
        ((FILTER) == HRTIM_EVENTFILTER_13)    || \
        ((FILTER) == HRTIM_EVENTFILTER_14)    || \
        ((FILTER) == HRTIM_EVENTFILTER_15))))

#define IS_HRTIM_EVENTPRESCALER(EVENTPRESCALER)\
             (((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV1)  || \
              ((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV2)   || \
              ((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV4)   || \
              ((EVENTPRESCALER) == HRTIM_EVENTPRESCALER_DIV8))

#define IS_HRTIM_FAULTSOURCE(FAULTSOURCE)\
              (((FAULTSOURCE) == HRTIM_FAULTSOURCE_DIGITALINPUT) || \
              ((FAULTSOURCE) == HRTIM_FAULTSOURCE_INTERNAL))

#define IS_HRTIM_FAULTPOLARITY(HRTIM_FAULTPOLARITY)\
              (((HRTIM_FAULTPOLARITY) == HRTIM_FAULTPOLARITY_LOW) || \
               ((HRTIM_FAULTPOLARITY) == HRTIM_FAULTPOLARITY_HIGH))

#define IS_HRTIM_FAULTMODECTL(FAULTMODECTL)\
    (((FAULTMODECTL) == HRTIM_FAULTMODECTL_DISABLED)  || \
     ((FAULTMODECTL) == HRTIM_FAULTMODECTL_ENABLED))

#define IS_HRTIM_FAULTFILTER(FAULTFILTER)\
                (((FAULTFILTER) == HRTIM_FAULTFILTER_NONE) || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_1)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_2)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_3)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_4)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_5)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_6)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_7)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_8)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_9)    || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_10)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_11)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_12)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_13)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_14)   || \
                 ((FAULTFILTER) == HRTIM_FAULTFILTER_15))

#define IS_HRTIM_FAULTLOCK(FAULTLOCK)\
              (((FAULTLOCK) == HRTIM_FAULTLOCK_READWRITE) || \
               ((FAULTLOCK) == HRTIM_FAULTLOCK_READONLY))

#define IS_HRTIM_FAULTPRESCALER(FAULTPRESCALER)\
             (((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV1)  || \
              ((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV2)   || \
              ((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV4)   || \
              ((FAULTPRESCALER) == HRTIM_FAULTPRESCALER_DIV8))

#define IS_HRTIM_BURSTMODE(BURSTMODE)\
              (((BURSTMODE) == HRTIM_BURSTMODE_SINGLESHOT)  || \
               ((BURSTMODE) == HRTIM_BURSTMODE_CONTINOUS))

#define IS_HRTIM_BURSTMODECLOCKSOURCE(BURSTMODECLOCKSOURCE)\
              (((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_MASTER)      || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_A)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_B)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_C)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_D)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIMER_E)     || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIM16_OC)    || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIM17_OC)    || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_TIM7_TRGO)   || \
               ((BURSTMODECLOCKSOURCE) == HRTIM_BURSTMODECLOCKSOURCE_FHRTIM))

#define IS_HRTIM_HRTIM_BURSTMODEPRESCALER(BURSTMODEPRESCALER)\
              (((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV1)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV2)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV4)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV8)     || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV16)    || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV32)    || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV64)    || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV128)   || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV256)   || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV512)   || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV1024)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV2048)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV4096)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV8192)  || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV16384) || \
               ((BURSTMODEPRESCALER) == HRTIM_BURSTMODEPRESCALER_DIV32768))

#define IS_HRTIM_BURSTMODEPRELOAD(BURSTMODEPRELOAD)\
              (((BURSTMODEPRELOAD) == HRIM_BURSTMODEPRELOAD_DISABLED)  || \
               ((BURSTMODEPRELOAD) == HRIM_BURSTMODEPRELOAD_ENABLED))

#define IS_HRTIM_BURSTMODETRIGGER(BURSTMODETRIGGER)\
              (((BURSTMODETRIGGER) == HRTIM_BURSTMODETRIGGER_NONE)               || \
               ((BURSTMODETRIGGER) == HRTIM_BURSTMODETRIGGER_MASTER_RESET)       || \
               ((BURSTMODETRIGGER) == HRTIM_BURSTMODETRIGGER_MASTER_REPETITION)  || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP3)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_MASTER_CMP4)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERB_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERC_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_RESET)      || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_REPETITION) || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_CMP1)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERE_CMP2)       || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERA_EVENT7)     || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_TIMERD_EVENT8)     || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_EVENT_7)           || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_EVENT_8)           || \
               ((BURSTMODETRIGGER) ==  HRTIM_BURSTMODETRIGGER_EVENT_ONCHIP))

#define IS_HRTIM_ADCTRIGGERUPDATE(ADCTRIGGERUPDATE)\
             (((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_MASTER)   || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_A)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_B)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_C)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_D)  || \
              ((ADCTRIGGERUPDATE) == HRTIM_ADCTRIGGERUPDATE_TIMER_E))

#define IS_HRTIM_CALIBRATIONRATE(CALIBRATIONRATE)\
    (((CALIBRATIONRATE) == HRTIM_SINGLE_CALIBRATION)   || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_7300) || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_910)  || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_114)  || \
     ((CALIBRATIONRATE) == HRTIM_CALIBRATIONRATE_14))

#define IS_HRTIM_TIMER_BURSTDMA(TIMER, BURSTDMA)                                            \
    ((((TIMER) == HRTIM_TIMERINDEX_MASTER)  && (((BURSTDMA) & 0xFFFFC000U) == 0x00000000U)) \
  || (((TIMER) == HRTIM_TIMERINDEX_TIMER_A) && (((BURSTDMA) & 0xFFE00000U) == 0x00000000U)) \
  || (((TIMER) == HRTIM_TIMERINDEX_TIMER_B) && (((BURSTDMA) & 0xFFE00000U) == 0x00000000U)) \
  || (((TIMER) == HRTIM_TIMERINDEX_TIMER_C) && (((BURSTDMA) & 0xFFE00000U) == 0x00000000U)) \
  || (((TIMER) == HRTIM_TIMERINDEX_TIMER_D) && (((BURSTDMA) & 0xFFE00000U) == 0x00000000U)) \
  || (((TIMER) == HRTIM_TIMERINDEX_TIMER_E) && (((BURSTDMA) & 0xFFE00000U) == 0x00000000U)))

#define IS_HRTIM_BURSTMODECTL(BURSTMODECTL)\
    (((BURSTMODECTL) == HRTIM_BURSTMODECTL_DISABLED)  || \
     ((BURSTMODECTL) == HRTIM_BURSTMODECTL_ENABLED))

#define IS_HRTIM_TIMERUPDATE(TIMERUPDATE) (((TIMERUPDATE) & 0xFFFFFFC0U) == 0x00000000U)

#define IS_HRTIM_TIMERRESET(TIMERRESET) (((TIMERRESET) & 0xFFFFC0FFU) == 0x00000000U)

#define IS_HRTIM_IT(IT) (((IT) & 0xFFFCFFC0U) == 0x00000000U)


#define IS_HRTIM_MASTER_IT(MASTER_IT) (((MASTER_IT) & 0xFFFFFF80U) == 0x00000000U)


#define IS_HRTIM_TIM_IT(TIM_IT) (((TIM_IT) & 0xFFFF8020U) == 0x00000000U)


#define IS_HRTIM_MASTER_DMA(MASTER_DMA) (((MASTER_DMA) & 0xFF80FFFFU) == 0x00000000U)

#define IS_HRTIM_TIM_DMA(TIM_DMA) (((TIM_DMA) & 0x8020FFFFU) == 0x00000000U)
/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HRTIM_Exported_Macros HRTIM Exported Macros
  * @{
  */

/** @brief Reset HRTIM handle state
  * @param  __HANDLE__ HRTIM handle.
  * @retval None
  */
#if (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
#define __HAL_HRTIM_RESET_HANDLE_STATE(__HANDLE__)                do{                                                       \
                                                                    (__HANDLE__)->State             = HAL_HRTIM_STATE_RESET; \
                                                                    (__HANDLE__)->MspInitCallback   = NULL;                  \
                                                                    (__HANDLE__)->MspDeInitCallback = NULL;                 \
                                                                  } while(0)
#else
#define __HAL_HRTIM_RESET_HANDLE_STATE(__HANDLE__)                ((__HANDLE__)->State = HAL_HRTIM_STATE_RESET)
#endif

/** @brief  Enables or disables the timer counter(s)
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __TIMERS__ timers to enable/disable
  *        This parameter can be any combinations of the following values:
  *            @arg HRTIM_TIMERID_MASTER: Master timer identifier
  *            @arg HRTIM_TIMERID_TIMER_A: Timer A identifier
  *            @arg HRTIM_TIMERID_TIMER_B: Timer B identifier
  *            @arg HRTIM_TIMERID_TIMER_C: Timer C identifier
  *            @arg HRTIM_TIMERID_TIMER_D: Timer D identifier
  *            @arg HRTIM_TIMERID_TIMER_E: Timer E identifier
  * @retval None
  */
#define __HAL_HRTIM_ENABLE(__HANDLE__, __TIMERS__)   ((__HANDLE__)->Instance->sMasterRegs.MCR |= (__TIMERS__))

/* The counter of a timing unit is disabled only if all the timer outputs */
/* are disabled and no capture is configured                              */
#define HRTIM_TAOEN_MASK (HRTIM_OENR_TA2OEN | HRTIM_OENR_TA1OEN)
#define HRTIM_TBOEN_MASK (HRTIM_OENR_TB2OEN | HRTIM_OENR_TB1OEN)
#define HRTIM_TCOEN_MASK (HRTIM_OENR_TC2OEN | HRTIM_OENR_TC1OEN)
#define HRTIM_TDOEN_MASK (HRTIM_OENR_TD2OEN | HRTIM_OENR_TD1OEN)
#define HRTIM_TEOEN_MASK (HRTIM_OENR_TE2OEN | HRTIM_OENR_TE1OEN)
#define __HAL_HRTIM_DISABLE(__HANDLE__, __TIMERS__)\
  do {\
    if (((__TIMERS__) & HRTIM_TIMERID_MASTER) == HRTIM_TIMERID_MASTER)\
      {\
        ((__HANDLE__)->Instance->sMasterRegs.MCR &= ~HRTIM_TIMERID_MASTER);\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_A) == HRTIM_TIMERID_TIMER_A)\
      {\
        if (((__HANDLE__)->Instance->sCommonRegs.OENR & HRTIM_TAOEN_MASK) == (uint32_t)RESET)\
          {\
            ((__HANDLE__)->Instance->sMasterRegs.MCR &= ~HRTIM_TIMERID_TIMER_A);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_B) == HRTIM_TIMERID_TIMER_B)\
      {\
        if (((__HANDLE__)->Instance->sCommonRegs.OENR & HRTIM_TBOEN_MASK) == (uint32_t)RESET)\
          {\
            ((__HANDLE__)->Instance->sMasterRegs.MCR &= ~HRTIM_TIMERID_TIMER_B);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_C) == HRTIM_TIMERID_TIMER_C)\
      {\
        if (((__HANDLE__)->Instance->sCommonRegs.OENR & HRTIM_TCOEN_MASK) == (uint32_t)RESET)\
          {\
            ((__HANDLE__)->Instance->sMasterRegs.MCR &= ~HRTIM_TIMERID_TIMER_C);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_D) == HRTIM_TIMERID_TIMER_D)\
      {\
        if (((__HANDLE__)->Instance->sCommonRegs.OENR & HRTIM_TDOEN_MASK) == (uint32_t)RESET)\
          {\
            ((__HANDLE__)->Instance->sMasterRegs.MCR &= ~HRTIM_TIMERID_TIMER_D);\
          }\
      }\
    if (((__TIMERS__) & HRTIM_TIMERID_TIMER_E) == HRTIM_TIMERID_TIMER_E)\
      {\
        if (((__HANDLE__)->Instance->sCommonRegs.OENR & HRTIM_TEOEN_MASK) == (uint32_t)RESET)\
          {\
            ((__HANDLE__)->Instance->sMasterRegs.MCR &= ~HRTIM_TIMERID_TIMER_E);\
          }\
      }\
  } while(0U)


/** @brief  Enables or disables the specified HRTIM common interrupts.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_IT_FLT1: Fault 1 interrupt enable
  *            @arg HRTIM_IT_FLT2: Fault 2 interrupt enable
  *            @arg HRTIM_IT_FLT3: Fault 3 interrupt enable
  *            @arg HRTIM_IT_FLT4: Fault 4 interrupt enable
  *            @arg HRTIM_IT_FLT5: Fault 5 interrupt enable
  *            @arg HRTIM_IT_SYSFLT: System Fault interrupt enable
  *            @arg HRTIM_IT_BMPER: Burst mode period interrupt enable
  * @retval None
  */
#define __HAL_HRTIM_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->sCommonRegs.IER |= (__INTERRUPT__))
#define __HAL_HRTIM_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->sCommonRegs.IER &= ~(__INTERRUPT__))

/** @brief  Enables or disables the specified HRTIM Master timer interrupts.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 interrupt enable
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition interrupt enable
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input interrupt enable
  *            @arg HRTIM_MASTER_IT_MUPD: Master update interrupt enable
  * @retval None
  */
#define __HAL_HRTIM_MASTER_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->sMasterRegs.MDIER |= (__INTERRUPT__))
#define __HAL_HRTIM_MASTER_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->sMasterRegs.MDIER &= ~(__INTERRUPT__))

/** @brief  Enables or disables the specified HRTIM Timerx interrupts.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __TIMER__ specified the timing unit (Timer A to E)
  * @param  __INTERRUPT__ specifies the interrupt source to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_TIM_IT_CMP1: Timer compare 1 interrupt enable
  *            @arg HRTIM_TIM_IT_CMP2: Timer compare 2 interrupt enable
  *            @arg HRTIM_TIM_IT_CMP3: Timer compare 3 interrupt enable
  *            @arg HRTIM_TIM_IT_CMP4: Timer compare 4 interrupt enable
  *            @arg HRTIM_TIM_IT_REP: Timer repetition interrupt enable
  *            @arg HRTIM_TIM_IT_UPD: Timer update interrupt enable
  *            @arg HRTIM_TIM_IT_CPT1: Timer capture 1 interrupt enable
  *            @arg HRTIM_TIM_IT_CPT2: Timer capture 2 interrupt enable
  *            @arg HRTIM_TIM_IT_SET1: Timer output 1 set interrupt enable
  *            @arg HRTIM_TIM_IT_RST1: Timer output 1 reset interrupt enable
  *            @arg HRTIM_TIM_IT_SET2: Timer output 2 set interrupt enable
  *            @arg HRTIM_TIM_IT_RST2: Timer output 2 reset interrupt enable
  *            @arg HRTIM_TIM_IT_RST: Timer reset interrupt enable
  *            @arg HRTIM_TIM_IT_DLYPRT: Timer delay protection interrupt enable
  * @retval None
  */
#define __HAL_HRTIM_TIMER_ENABLE_IT(__HANDLE__, __TIMER__, __INTERRUPT__)   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxDIER |= (__INTERRUPT__))
#define __HAL_HRTIM_TIMER_DISABLE_IT(__HANDLE__, __TIMER__, __INTERRUPT__) ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxDIER &= ~(__INTERRUPT__))

/** @brief  Checks if the specified HRTIM common interrupt  source  is enabled or disabled.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __INTERRUPT__ specifies the interrupt source to check.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_IT_FLT1: Fault 1 interrupt enable
  *            @arg HRTIM_IT_FLT2: Fault 2 interrupt enable
  *            @arg HRTIM_IT_FLT3: Fault 3 enable
  *            @arg HRTIM_IT_FLT4: Fault 4 enable
  *            @arg HRTIM_IT_FLT5: Fault 5 enable
  *            @arg HRTIM_IT_SYSFLT: System Fault interrupt enable
  *            @arg HRTIM_IT_BMPER: Burst mode period interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_HRTIM_GET_ITSTATUS(__HANDLE__, __INTERRUPT__)     ((((__HANDLE__)->Instance->sCommonRegs.IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks if the specified HRTIM Master interrupt source  is enabled or disabled.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __INTERRUPT__ specifies the interrupt source to check.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 interrupt enable
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition interrupt enable
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input interrupt enable
  *            @arg HRTIM_MASTER_IT_MUPD: Master update interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_HRTIM_MASTER_GET_ITSTATUS(__HANDLE__, __INTERRUPT__)     ((((__HANDLE__)->Instance->sMasterRegs.MDIER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Checks if the specified HRTIM Timerx interrupt source  is enabled or disabled.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __TIMER__ specified the timing unit (Timer A to E)
  * @param  __INTERRUPT__ specifies the interrupt source to check.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt enable
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 interrupt enable
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition interrupt enable
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input interrupt enable
  *            @arg HRTIM_MASTER_IT_MUPD: Master update interrupt enable
  *            @arg HRTIM_TIM_IT_CMP1: Timer compare 1 interrupt enable
  *            @arg HRTIM_TIM_IT_CMP2: Timer compare 2 interrupt enable
  *            @arg HRTIM_TIM_IT_CMP3: Timer compare 3 interrupt enable
  *            @arg HRTIM_TIM_IT_CMP4: Timer compare 4 interrupt enable
  *            @arg HRTIM_TIM_IT_REP: Timer repetition interrupt enable
  *            @arg HRTIM_TIM_IT_UPD: Timer update interrupt enable
  *            @arg HRTIM_TIM_IT_CPT1: Timer capture 1 interrupt enable
  *            @arg HRTIM_TIM_IT_CPT2: Timer capture 2 interrupt enable
  *            @arg HRTIM_TIM_IT_SET1: Timer output 1 set interrupt enable
  *            @arg HRTIM_TIM_IT_RST1: Timer output 1 reset interrupt enable
  *            @arg HRTIM_TIM_IT_SET2: Timer output 2 set interrupt enable
  *            @arg HRTIM_TIM_IT_RST2: Timer output 2 reset interrupt enable
  *            @arg HRTIM_TIM_IT_RST: Timer reset interrupt enable
  *            @arg HRTIM_TIM_IT_DLYPRT: Timer delay protection interrupt enable
  * @retval The new state of __INTERRUPT__ (TRUE or FALSE).
  */
#define __HAL_HRTIM_TIMER_GET_ITSTATUS(__HANDLE__, __TIMER__, __INTERRUPT__)     ((((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxDIER & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Clears the specified HRTIM common pending flag.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_IT_FLT1: Fault 1 interrupt clear flag
  *            @arg HRTIM_IT_FLT2: Fault 2 interrupt clear flag
  *            @arg HRTIM_IT_FLT3: Fault 3 clear flag
  *            @arg HRTIM_IT_FLT4: Fault 4 clear flag
  *            @arg HRTIM_IT_FLT5: Fault 5 clear flag
  *            @arg HRTIM_IT_SYSFLT: System Fault interrupt clear flag
  *            @arg HRTIM_IT_BMPER: Burst mode period interrupt clear flag
  * @retval None
  */
#define __HAL_HRTIM_CLEAR_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->sCommonRegs.ICR = (__INTERRUPT__))

/** @brief  Clears the specified HRTIM Master pending flag.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_MASTER_IT_MCMP1: Master compare 1 interrupt clear flag
  *            @arg HRTIM_MASTER_IT_MCMP2: Master compare 2 interrupt clear flag
  *            @arg HRTIM_MASTER_IT_MCMP3: Master compare 3 interrupt clear flag
  *            @arg HRTIM_MASTER_IT_MCMP4: Master compare 4 interrupt clear flag
  *            @arg HRTIM_MASTER_IT_MREP: Master Repetition interrupt clear flag
  *            @arg HRTIM_MASTER_IT_SYNC: Synchronization input interrupt clear flag
  *            @arg HRTIM_MASTER_IT_MUPD: Master update interrupt clear flag
  * @retval None
  */
#define __HAL_HRTIM_MASTER_CLEAR_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->sMasterRegs.MICR = (__INTERRUPT__))

/** @brief  Clears the specified HRTIM Timerx pending flag.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __TIMER__ specified the timing unit (Timer A to E)
  * @param  __INTERRUPT__ specifies the interrupt pending bit to clear.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_TIM_IT_CMP1: Timer compare 1 interrupt clear flag
  *            @arg HRTIM_TIM_IT_CMP2: Timer compare 2 interrupt clear flag
  *            @arg HRTIM_TIM_IT_CMP3: Timer compare 3 interrupt clear flag
  *            @arg HRTIM_TIM_IT_CMP4: Timer compare 4 interrupt clear flag
  *            @arg HRTIM_TIM_IT_REP: Timer repetition interrupt clear flag
  *            @arg HRTIM_TIM_IT_UPD: Timer update interrupt clear flag
  *            @arg HRTIM_TIM_IT_CPT1: Timer capture 1 interrupt clear flag
  *            @arg HRTIM_TIM_IT_CPT2: Timer capture 2 interrupt clear flag
  *            @arg HRTIM_TIM_IT_SET1: Timer output 1 set interrupt clear flag
  *            @arg HRTIM_TIM_IT_RST1: Timer output 1 reset interrupt clear flag
  *            @arg HRTIM_TIM_IT_SET2: Timer output 2 set interrupt clear flag
  *            @arg HRTIM_TIM_IT_RST2: Timer output 2 reset interrupt clear flag
  *            @arg HRTIM_TIM_IT_RST: Timer reset interrupt clear flag
  *            @arg HRTIM_TIM_IT_DLYPRT: Timer output 1 delay protection interrupt clear flag
  * @retval None
  */
#define __HAL_HRTIM_TIMER_CLEAR_IT(__HANDLE__, __TIMER__, __INTERRUPT__)   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxICR = (__INTERRUPT__))

/* DMA HANDLING */
/** @brief  Enables or disables the specified HRTIM Master timer DMA requests.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __DMA__ specifies the DMA request to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_MASTER_DMA_MCMP1: Master compare 1 DMA request enable
  *            @arg HRTIM_MASTER_DMA_MCMP2: Master compare 2 DMA request enable
  *            @arg HRTIM_MASTER_DMA_MCMP3: Master compare 3 DMA request enable
  *            @arg HRTIM_MASTER_DMA_MCMP4: Master compare 4 DMA request enable
  *            @arg HRTIM_MASTER_DMA_MREP: Master Repetition DMA request enable
  *            @arg HRTIM_MASTER_DMA_SYNC: Synchronization input DMA request enable
  *            @arg HRTIM_MASTER_DMA_MUPD: Master update DMA request enable
  * @retval None
  */
#define __HAL_HRTIM_MASTER_ENABLE_DMA(__HANDLE__, __DMA__)   ((__HANDLE__)->Instance->sMasterRegs.MDIER |= (__DMA__))
#define __HAL_HRTIM_MASTER_DISABLE_DMA(__HANDLE__, __DMA__) ((__HANDLE__)->Instance->sMasterRegs.MDIER &= ~(__DMA__))

/** @brief  Enables or disables the specified HRTIM Timerx DMA requests.
  * @param  __HANDLE__ specifies the HRTIM Handle.
  * @param  __TIMER__ specified the timing unit (Timer A to E)
  * @param  __DMA__ specifies the DMA request to enable or disable.
  *        This parameter can be one of the following values:
  *            @arg HRTIM_TIM_DMA_CMP1: Timer compare 1 DMA request enable
  *            @arg HRTIM_TIM_DMA_CMP2: Timer compare 2 DMA request enable
  *            @arg HRTIM_TIM_DMA_CMP3: Timer compare 3 DMA request enable
  *            @arg HRTIM_TIM_DMA_CMP4: Timer compare 4 DMA request enable
  *            @arg HRTIM_TIM_DMA_REP: Timer repetition DMA request enable
  *            @arg HRTIM_TIM_DMA_UPD: Timer update DMA request enable
  *            @arg HRTIM_TIM_DMA_CPT1: Timer capture 1 DMA request enable
  *            @arg HRTIM_TIM_DMA_CPT2: Timer capture 2 DMA request enable
  *            @arg HRTIM_TIM_DMA_SET1: Timer output 1 set DMA request enable
  *            @arg HRTIM_TIM_DMA_RST1: Timer output 1 reset DMA request enable
  *            @arg HRTIM_TIM_DMA_SET2: Timer output 2 set DMA request enable
  *            @arg HRTIM_TIM_DMA_RST2: Timer output 2 reset DMA request enable
  *            @arg HRTIM_TIM_DMA_RST: Timer reset DMA request enable
  *            @arg HRTIM_TIM_DMA_DLYPRT: Timer delay protection DMA request enable
  * @retval None
  */
#define __HAL_HRTIM_TIMER_ENABLE_DMA(__HANDLE__, __TIMER__, __DMA__)   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxDIER |= (__DMA__))
#define __HAL_HRTIM_TIMER_DISABLE_DMA(__HANDLE__, __TIMER__, __DMA__) ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxDIER &= ~(__DMA__))

#define __HAL_HRTIM_GET_FLAG(__HANDLE__, __FLAG__)        (((__HANDLE__)->Instance->sCommonRegs.ISR & (__FLAG__)) == (__FLAG__))
#define __HAL_HRTIM_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((__HANDLE__)->Instance->sCommonRegs.ICR = (__FLAG__))

#define __HAL_HRTIM_MASTER_GET_FLAG(__HANDLE__, __FLAG__)        (((__HANDLE__)->Instance->sMasterRegs.MISR & (__FLAG__)) == (__FLAG__))
#define __HAL_HRTIM_MASTER_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((__HANDLE__)->Instance->sMasterRegs.MICR = (__FLAG__))

#define __HAL_HRTIM_TIMER_GET_FLAG(__HANDLE__,  __TIMER__, __FLAG__)        (((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxISR & (__FLAG__)) == (__FLAG__))
#define __HAL_HRTIM_TIMER_CLEAR_FLAG(__HANDLE__,  __TIMER__, __FLAG__)      ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxICR = (__FLAG__))

/** @brief  Sets the HRTIM timer Counter Register value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E
  * @param  __COUNTER__ specifies the Counter Register new value.
  * @retval None
  */
#define __HAL_HRTIM_SETCOUNTER(__HANDLE__, __TIMER__, __COUNTER__) \
  (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? ((__HANDLE__)->Instance->sMasterRegs.MCNTR = (__COUNTER__)) :\
   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CNTxR = (__COUNTER__)))

/** @brief  Gets the HRTIM timer Counter Register value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E
  * @retval HRTIM timer Counter Register value
  */
#define __HAL_HRTIM_GETCOUNTER(__HANDLE__, __TIMER__) \
  (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? ((__HANDLE__)->Instance->sMasterRegs.MCNTR) :\
   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CNTxR))

/** @brief  Sets the HRTIM timer Period value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E
  * @param  __PERIOD__ specifies the Period Register new value.
  * @retval None
  */
#define __HAL_HRTIM_SETPERIOD(__HANDLE__, __TIMER__, __PERIOD__) \
  (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? ((__HANDLE__)->Instance->sMasterRegs.MPER = (__PERIOD__)) :\
   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].PERxR = (__PERIOD__)))

/** @brief  Gets the HRTIM timer Period Register value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E
  * @retval timer Period Register
  */
#define __HAL_HRTIM_GETPERIOD(__HANDLE__, __TIMER__) \
  (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? ((__HANDLE__)->Instance->sMasterRegs.MPER) :\
   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].PERxR))

/** @brief  Sets the HRTIM timer clock prescaler value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E
  * @param  __PRESCALER__ specifies the clock prescaler new value.
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_PRESCALERRATIO_DIV1: fHRCK: 144 MHz - Resolution: 6.95 ns - Min PWM frequency: 2.2 kHz (fHRTIM=144MHz)
  *                   @arg HRTIM_PRESCALERRATIO_DIV2: fHRCK: 72 MHz - Resolution: 13.88 ns- Min PWM frequency: 1.1 kHz (fHRTIM=144MHz)
  *                   @arg HRTIM_PRESCALERRATIO_DIV4: fHRCK: 36 MHz - Resolution: 27.7 ns- Min PWM frequency: 550Hz (fHRTIM=144MHz)
  * @retval None
  */
#define __HAL_HRTIM_SETCLOCKPRESCALER(__HANDLE__, __TIMER__, __PRESCALER__) \
  (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? (MODIFY_REG((__HANDLE__)->Instance->sMasterRegs.MCR, HRTIM_MCR_CK_PSC, (__PRESCALER__))) :\
   (MODIFY_REG((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxCR, HRTIM_TIMCR_CK_PSC, (__PRESCALER__))))

/** @brief  Gets the HRTIM timer clock prescaler value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x5 for master timer
  *                   @arg 0x0 to 0x4 for timers A to E
  * @retval timer clock prescaler value
  */
#define __HAL_HRTIM_GETCLOCKPRESCALER(__HANDLE__, __TIMER__) \
  (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? ((__HANDLE__)->Instance->sMasterRegs.MCR & HRTIM_MCR_CK_PSC) :\
   ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].TIMxCR  & HRTIM_TIMCR_CK_PSC))

/** @brief  Sets the HRTIM timer Compare Register value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E
  * @param  __COMPAREUNIT__ timer compare unit
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_COMPAREUNIT_1: Compare unit 1
  *                   @arg HRTIM_COMPAREUNIT_2: Compare unit 2
  *                   @arg HRTIM_COMPAREUNIT_3: Compare unit 3
  *                   @arg HRTIM_COMPAREUNIT_4: Compare unit 4
  * @param  __COMPARE__ specifies the Compare new value.
  * @retval None
  */
#define __HAL_HRTIM_SETCOMPARE(__HANDLE__, __TIMER__, __COMPAREUNIT__, __COMPARE__) \
      (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? \
        (((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_1) ? ((__HANDLE__)->Instance->sMasterRegs.MCMP1R = (__COMPARE__)) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_2) ? ((__HANDLE__)->Instance->sMasterRegs.MCMP2R = (__COMPARE__)) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_3) ? ((__HANDLE__)->Instance->sMasterRegs.MCMP3R = (__COMPARE__)) :\
         ((__HANDLE__)->Instance->sMasterRegs.MCMP4R = (__COMPARE__))) \
         : \
        (((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_1) ? ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP1xR = (__COMPARE__)) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_2) ? ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP2xR = (__COMPARE__)) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_3) ? ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP3xR = (__COMPARE__)) :\
         ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP4xR = (__COMPARE__))))

/** @brief  Gets the HRTIM timer Compare Register value on runtime
  * @param  __HANDLE__ HRTIM Handle.
  * @param  __TIMER__ HRTIM timer
  *                   This parameter can be one of the following values:
  *                   @arg 0x0 to 0x4 for timers A to E
  * @param  __COMPAREUNIT__ timer compare unit
  *                   This parameter can be one of the following values:
  *                   @arg HRTIM_COMPAREUNIT_1: Compare unit 1
  *                   @arg HRTIM_COMPAREUNIT_2: Compare unit 2
  *                   @arg HRTIM_COMPAREUNIT_3: Compare unit 3
  *                   @arg HRTIM_COMPAREUNIT_4: Compare unit 4
  * @retval Compare value
  */
#define __HAL_HRTIM_GETCOMPARE(__HANDLE__, __TIMER__, __COMPAREUNIT__) \
      (((__TIMER__) == HRTIM_TIMERINDEX_MASTER) ? \
        (((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_1) ? ((__HANDLE__)->Instance->sMasterRegs.MCMP1R) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_2) ? ((__HANDLE__)->Instance->sMasterRegs.MCMP2R) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_3) ? ((__HANDLE__)->Instance->sMasterRegs.MCMP3R) :\
         ((__HANDLE__)->Instance->sMasterRegs.MCMP4R)) \
         : \
        (((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_1) ? ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP1xR) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_2) ? ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP2xR) :\
         ((__COMPAREUNIT__) == HRTIM_COMPAREUNIT_3) ? ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP3xR) :\
         ((__HANDLE__)->Instance->sTimerxRegs[(__TIMER__)].CMP4xR)))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HRTIM_Exported_Functions
* @{
*/

/** @addtogroup HRTIM_Exported_Functions_Group1
* @{
*/

/* Initialization and Configuration functions  ********************************/
HAL_StatusTypeDef HAL_HRTIM_Init(HRTIM_HandleTypeDef *hhrtim);

HAL_StatusTypeDef HAL_HRTIM_DeInit (HRTIM_HandleTypeDef *hhrtim);

void HAL_HRTIM_MspInit(HRTIM_HandleTypeDef *hhrtim);

void HAL_HRTIM_MspDeInit(HRTIM_HandleTypeDef *hhrtim);

HAL_StatusTypeDef HAL_HRTIM_TimeBaseConfig(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx,
                                           const HRTIM_TimeBaseCfgTypeDef * pTimeBaseCfg);
/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group2
* @{
*/

/* Simple time base related functions  *****************************************/
HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStart(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx);

HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStop(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t TimerIdx);

HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStart_IT(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx);

HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStop_IT(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx);

HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStart_DMA(HRTIM_HandleTypeDef *hhrtim,
                                               uint32_t TimerIdx,
                                               uint32_t SrcAddr,
                                               uint32_t DestAddr,
                                               uint32_t Length);

HAL_StatusTypeDef HAL_HRTIM_SimpleBaseStop_DMA(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group3
* @{
*/
/* Simple output compare related functions  ************************************/
HAL_StatusTypeDef HAL_HRTIM_SimpleOCChannelConfig(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t OCChannel,
                                                 const HRTIM_SimpleOCChannelCfgTypeDef* pSimpleOCChannelCfg);

HAL_StatusTypeDef HAL_HRTIM_SimpleOCStart(HRTIM_HandleTypeDef *hhrtim,
                                         uint32_t TimerIdx,
                                         uint32_t OCChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOCStop(HRTIM_HandleTypeDef *hhrtim,
                                        uint32_t TimerIdx,
                                        uint32_t OCChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOCStart_IT(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t OCChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOCStop_IT(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx,
                                           uint32_t OCChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOCStart_DMA(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t OCChannel,
                                             uint32_t SrcAddr,
                                             uint32_t DestAddr,
                                             uint32_t Length);

HAL_StatusTypeDef HAL_HRTIM_SimpleOCStop_DMA(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t OCChannel);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group4
* @{
*/
/* Simple PWM output related functions  ****************************************/
HAL_StatusTypeDef HAL_HRTIM_SimplePWMChannelConfig(HRTIM_HandleTypeDef *hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t PWMChannel,
                                                  const HRTIM_SimplePWMChannelCfgTypeDef* pSimplePWMChannelCfg);

HAL_StatusTypeDef HAL_HRTIM_SimplePWMStart(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t TimerIdx,
                                          uint32_t PWMChannel);

HAL_StatusTypeDef HAL_HRTIM_SimplePWMStop(HRTIM_HandleTypeDef *hhrtim,
                                         uint32_t TimerIdx,
                                         uint32_t PWMChannel);

HAL_StatusTypeDef HAL_HRTIM_SimplePWMStart_IT(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t PWMChannel);

HAL_StatusTypeDef HAL_HRTIM_SimplePWMStop_IT(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t PWMChannel);

HAL_StatusTypeDef HAL_HRTIM_SimplePWMStart_DMA(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t PWMChannel,
                                              uint32_t SrcAddr,
                                              uint32_t DestAddr,
                                              uint32_t Length);

HAL_StatusTypeDef HAL_HRTIM_SimplePWMStop_DMA(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t PWMChannel);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group5
* @{
*/
/* Simple capture related functions  *******************************************/
HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureChannelConfig(HRTIM_HandleTypeDef *hhrtim,
                                                      uint32_t TimerIdx,
                                                      uint32_t CaptureChannel,
                                                      const HRTIM_SimpleCaptureChannelCfgTypeDef* pSimpleCaptureChannelCfg);

HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStart(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t CaptureChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStop(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t CaptureChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStart_IT(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t CaptureChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStop_IT(HRTIM_HandleTypeDef *hhrtim,
                                                uint32_t TimerIdx,
                                                uint32_t CaptureChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStart_DMA(HRTIM_HandleTypeDef *hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t CaptureChannel,
                                                  uint32_t SrcAddr,
                                                  uint32_t DestAddr,
                                                  uint32_t Length);

HAL_StatusTypeDef HAL_HRTIM_SimpleCaptureStop_DMA(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t CaptureChannel);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group6
* @{
*/
/* Simple one pulse related functions  *****************************************/
HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseChannelConfig(HRTIM_HandleTypeDef *hhrtim,
                                                       uint32_t TimerIdx,
                                                       uint32_t OnePulseChannel,
                                                       const HRTIM_SimpleOnePulseChannelCfgTypeDef* pSimpleOnePulseChannelCfg);

HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStart(HRTIM_HandleTypeDef *hhrtim,
                                               uint32_t TimerIdx,
                                               uint32_t OnePulseChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStop(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx,
                                             uint32_t OnePulseChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStart_IT(HRTIM_HandleTypeDef *hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t OnePulseChannel);

HAL_StatusTypeDef HAL_HRTIM_SimpleOnePulseStop_IT(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t OnePulseChannel);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group7
* @{
*/
HAL_StatusTypeDef HAL_HRTIM_BurstModeConfig(HRTIM_HandleTypeDef *hhrtim,
                                            const HRTIM_BurstModeCfgTypeDef* pBurstModeCfg);

HAL_StatusTypeDef HAL_HRTIM_EventConfig(HRTIM_HandleTypeDef *hhrtim,
                                        uint32_t Event,
                                        const HRTIM_EventCfgTypeDef* pEventCfg);

HAL_StatusTypeDef HAL_HRTIM_EventPrescalerConfig(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t Prescaler);

HAL_StatusTypeDef HAL_HRTIM_FaultConfig(HRTIM_HandleTypeDef *hhrtim,
                                        uint32_t Fault,
                                        const HRTIM_FaultCfgTypeDef* pFaultCfg);

HAL_StatusTypeDef HAL_HRTIM_FaultPrescalerConfig(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t Prescaler);

void HAL_HRTIM_FaultModeCtl(HRTIM_HandleTypeDef * hhrtim,
                            uint32_t Faults,
                            uint32_t Enable);

HAL_StatusTypeDef HAL_HRTIM_ADCTriggerConfig(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t ADCTrigger,
                                             const HRTIM_ADCTriggerCfgTypeDef* pADCTriggerCfg);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group8
* @{
*/
/* Waveform related functions *************************************************/
HAL_StatusTypeDef HAL_HRTIM_WaveformTimerConfig(HRTIM_HandleTypeDef *hhrtim,
                                                uint32_t TimerIdx,
                                                const HRTIM_TimerCfgTypeDef * pTimerCfg);

HAL_StatusTypeDef HAL_HRTIM_WaveformCompareConfig(HRTIM_HandleTypeDef *hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t CompareUnit,
                                                  const HRTIM_CompareCfgTypeDef* pCompareCfg);

HAL_StatusTypeDef HAL_HRTIM_WaveformCaptureConfig(HRTIM_HandleTypeDef *hhrtim,
                                                  uint32_t TimerIdx,
                                                  uint32_t CaptureUnit,
                                                  const HRTIM_CaptureCfgTypeDef* pCaptureCfg);

HAL_StatusTypeDef HAL_HRTIM_WaveformOutputConfig(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t TimerIdx,
                                                 uint32_t Output,
                                                 const HRTIM_OutputCfgTypeDef * pOutputCfg);

HAL_StatusTypeDef HAL_HRTIM_WaveformSetOutputLevel(HRTIM_HandleTypeDef *hhrtim,
                                                   uint32_t TimerIdx,
                                                   uint32_t Output,
                                                   uint32_t OutputLevel);

HAL_StatusTypeDef HAL_HRTIM_TimerEventFilteringConfig(HRTIM_HandleTypeDef *hhrtim,
                                                      uint32_t TimerIdx,
                                                      uint32_t Event,
                                                      const HRTIM_TimerEventFilteringCfgTypeDef * pTimerEventFilteringCfg);

HAL_StatusTypeDef HAL_HRTIM_DeadTimeConfig(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx,
                                           const HRTIM_DeadTimeCfgTypeDef* pDeadTimeCfg);

HAL_StatusTypeDef HAL_HRTIM_ChopperModeConfig(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx,
                                              const HRTIM_ChopperModeCfgTypeDef* pChopperModeCfg);

HAL_StatusTypeDef HAL_HRTIM_BurstDMAConfig(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx,
                                           uint32_t RegistersToUpdate);


HAL_StatusTypeDef HAL_HRTIM_WaveformCountStart(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_WaveformCountStop(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_WaveformCountStart_IT(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_WaveformCountStop_IT(HRTIM_HandleTypeDef *hhrtim,
                                                 uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_WaveformCountStart_DMA(HRTIM_HandleTypeDef *hhrtim,
                                                     uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_WaveformCountStop_DMA(HRTIM_HandleTypeDef *hhrtim,
                                                    uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_WaveformOutputStart(HRTIM_HandleTypeDef *hhrtim,
                                                uint32_t OutputsToStart);

HAL_StatusTypeDef HAL_HRTIM_WaveformOutputStop(HRTIM_HandleTypeDef *hhrtim,
                                               uint32_t OutputsToStop);

HAL_StatusTypeDef HAL_HRTIM_BurstModeCtl(HRTIM_HandleTypeDef *hhrtim,
                                         uint32_t Enable);

HAL_StatusTypeDef HAL_HRTIM_BurstModeSoftwareTrigger(HRTIM_HandleTypeDef *hhrtim);

HAL_StatusTypeDef HAL_HRTIM_SoftwareCapture(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx,
                                            uint32_t CaptureUnit);

HAL_StatusTypeDef HAL_HRTIM_SoftwareUpdate(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_SoftwareReset(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_BurstDMATransfer(HRTIM_HandleTypeDef *hhrtim,
                                             uint32_t TimerIdx,
                                             uint32_t BurstBufferAddress,
                                             uint32_t BurstBufferLength);

HAL_StatusTypeDef HAL_HRTIM_UpdateEnable(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t Timers);

HAL_StatusTypeDef HAL_HRTIM_UpdateDisable(HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t Timers);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group9
* @{
*/
/* HRTIM peripheral state functions */
HAL_HRTIM_StateTypeDef HAL_HRTIM_GetState(const HRTIM_HandleTypeDef* hhrtim);

uint32_t HAL_HRTIM_GetCapturedValue(const HRTIM_HandleTypeDef * hhrtim,
                                    uint32_t TimerIdx,
                                    uint32_t CaptureUnit);

uint32_t HAL_HRTIM_WaveformGetOutputLevel(const HRTIM_HandleTypeDef *hhrtim,
                                          uint32_t TimerIdx,
                                          uint32_t Output);

uint32_t HAL_HRTIM_WaveformGetOutputState(const HRTIM_HandleTypeDef * hhrtim,
                                          uint32_t TimerIdx,
                                          uint32_t Output);

uint32_t HAL_HRTIM_GetDelayedProtectionStatus(const HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx,
                                              uint32_t Output);

uint32_t HAL_HRTIM_GetBurstStatus(const HRTIM_HandleTypeDef *hhrtim);

uint32_t HAL_HRTIM_GetCurrentPushPullStatus(const HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);

uint32_t HAL_HRTIM_GetIdlePushPullStatus(const HRTIM_HandleTypeDef *hhrtim,
                                         uint32_t TimerIdx);

/**
  * @}
  */

/** @addtogroup HRTIM_Exported_Functions_Group10
* @{
*/
/* IRQ handler */
void HAL_HRTIM_IRQHandler(HRTIM_HandleTypeDef *hhrtim,
                          uint32_t TimerIdx);

/* HRTIM events related callback functions */
void HAL_HRTIM_Fault1Callback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_Fault2Callback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_Fault3Callback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_Fault4Callback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_Fault5Callback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_SystemFaultCallback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_BurstModePeriodCallback(HRTIM_HandleTypeDef *hhrtim);
void HAL_HRTIM_SynchronizationEventCallback(HRTIM_HandleTypeDef *hhrtim);

/* Timer events related callback functions */
void HAL_HRTIM_RegistersUpdateCallback(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx);
void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx);
void HAL_HRTIM_Compare1EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);
void HAL_HRTIM_Compare2EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);
void HAL_HRTIM_Compare3EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);
void HAL_HRTIM_Compare4EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);
void HAL_HRTIM_Capture1EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);
void HAL_HRTIM_Capture2EventCallback(HRTIM_HandleTypeDef *hhrtim,
                                            uint32_t TimerIdx);
void HAL_HRTIM_DelayedProtectionCallback(HRTIM_HandleTypeDef *hhrtim,
                                                uint32_t TimerIdx);
void HAL_HRTIM_CounterResetCallback(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx);
void HAL_HRTIM_Output1SetCallback(HRTIM_HandleTypeDef *hhrtim,
                                         uint32_t TimerIdx);
void HAL_HRTIM_Output1ResetCallback(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx);
void HAL_HRTIM_Output2SetCallback(HRTIM_HandleTypeDef *hhrtim,
                                         uint32_t TimerIdx);
void HAL_HRTIM_Output2ResetCallback(HRTIM_HandleTypeDef *hhrtim,
                                           uint32_t TimerIdx);
void HAL_HRTIM_BurstDMATransferCallback(HRTIM_HandleTypeDef *hhrtim,
                                               uint32_t TimerIdx);
void HAL_HRTIM_ErrorCallback(HRTIM_HandleTypeDef *hhrtim);

#if (USE_HAL_HRTIM_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_HRTIM_RegisterCallback(HRTIM_HandleTypeDef *       hhrtim,
                                             HAL_HRTIM_CallbackIDTypeDef CallbackID,
                                             pHRTIM_CallbackTypeDef      pCallback);

HAL_StatusTypeDef HAL_HRTIM_UnRegisterCallback(HRTIM_HandleTypeDef *       hhrtim,
                                               HAL_HRTIM_CallbackIDTypeDef CallbackID);

HAL_StatusTypeDef HAL_HRTIM_TIMxRegisterCallback(HRTIM_HandleTypeDef *        hhrtim,
                                                 HAL_HRTIM_CallbackIDTypeDef  CallbackID,
                                                 pHRTIM_TIMxCallbackTypeDef   pCallback);

HAL_StatusTypeDef HAL_HRTIM_TIMxUnRegisterCallback(HRTIM_HandleTypeDef *       hhrtim,
                                                   HAL_HRTIM_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_HRTIM_REGISTER_CALLBACKS */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HRTIM1 */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_HAL_HRTIM_H */
