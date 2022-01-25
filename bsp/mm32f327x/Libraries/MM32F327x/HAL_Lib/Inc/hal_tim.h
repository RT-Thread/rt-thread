////////////////////////////////////////////////////////////////////////////////
/// @file     hal_tim.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE TIM
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_TIM_H
#define __HAL_TIM_H

// Files includes
#include "types.h"
#include "reg_tim.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup TIM_HAL
/// @brief TIM HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup TIM_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Channel
/// @anchor TIM_Channel
typedef enum {
    TIM_Channel_1 = 0x0000,  ///< TIM Channel 1
    TIM_Channel_2 = 0x0004,  ///< TIM Channel 2
    TIM_Channel_3 = 0x0008,  ///< TIM Channel 3
    TIM_Channel_4 = 0x000C,  ///< TIM Channel 4
    TIM_Channel_5 = 0x0010   ///< TIM Channel 5
} TIMCHx_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Counter_Mode
/// @anchor TIM_Counter_Mode
typedef enum {
    TIM_CounterMode_Up             = 0x0000,                        ///< TIM Up Counting Mode
    TIM_CounterMode_Down           = TIM_CR1_DIR,                   ///< TIM Down Counting Mode
    TIM_CounterMode_CenterAligned1 = TIM_CR1_CMS_CENTERALIGNED1,    ///< TIM Center Aligned Mode1
    TIM_CounterMode_CenterAligned2 = TIM_CR1_CMS_CENTERALIGNED2,    ///< TIM Center Aligned Mode2
    TIM_CounterMode_CenterAligned3 = TIM_CR1_CMS_CENTERALIGNED3     ///< TIM Center Aligned Mode3
} TIMCOUNTMODE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_and_PWM_modes_and_Forced_Action
/// @anchor TIM_Output_Compare_and_PWM_modes_and_Forced_Action
typedef enum {
    TIM_OCMode_Timing         = 0x0000,                         ///< Output compare mode: Timing
    TIM_OCMode_Active         = 0x0010,                         ///< Output compare mode: Active
    TIM_OCMode_Inactive       = 0x0020,                         ///< Output compare mode: Inactive
    TIM_OCMode_Toggle         = 0x0030,                         ///< Output compare mode: Toggle
    TIM_OCMode_PWM1           = 0x0060,                         ///< Output compare mode: PWM1
    TIM_OCMode_PWM2           = 0x0070,                         ///< Output compare mode: PWM2
    TIM_ForcedAction_Active   = 0x0050,                         ///< Force active level on OCnREF
    TIM_ForcedAction_InActive = 0x0040                          ///< Force inactive level on OCnREF
} TIMOCMODE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Clock_Division_CKD
/// @anchor TIM_Clock_Division_CKD
typedef enum {
    TIM_CKD_DIV1 = TIM_CR1_CKD_DIV1,                            ///< TDTS = Tck_tim
    TIM_CKD_DIV2 = TIM_CR1_CKD_DIV2,                            ///< TDTS = 2 * Tck_tim
    TIM_CKD_DIV4 = TIM_CR1_CKD_DIV4                             ///< TDTS = 4 * Tck_tim
} TIMCKD_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Internal_Trigger_Selection
/// @anchor TIM_Internal_Trigger_Selection
typedef enum {
    TIM_TS_ITR0    = TIM_SMCR_TS_ITR0,                          ///< Internal Trigger 0
    TIM_TS_ITR1    = TIM_SMCR_TS_ITR1,                          ///< Internal Trigger 1
    TIM_TS_ITR2    = TIM_SMCR_TS_ITR2,                          ///< Internal Trigger 2
    TIM_TS_ITR3    = TIM_SMCR_TS_ITR3,                          ///< Internal Trigger 3
    TIM_TS_TI1F_ED = TIM_SMCR_TS_TI1F_ED,                       ///< TI1 Edge Detector
    TIM_TS_TI1FP1  = TIM_SMCR_TS_TI1FP1,                        ///< Filtered Timer Input 1
    TIM_TS_TI2FP2  = TIM_SMCR_TS_TI2FP2,                        ///< Filtered Timer Input 2
    TIM_TS_ETRF    = TIM_SMCR_TS_ETRF                           ///< TI1 Edge Detector
} TIMTS_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Trigger_Output_Source
/// @anchor TIM_Trigger_Output_Source
typedef enum {
    TIM_TRIGSource_Reset  = TIM_CR2_MMS_RESET,                  ///< The UG bit in the TIM_EGR register is used as the trigger output (TRIG).
    TIM_TRIGSource_Enable = TIM_CR2_MMS_ENABLE,                 ///< The Counter Enable CEN is used as the trigger output (TRIG).
    TIM_TRIGSource_Update = TIM_CR2_MMS_UPDATE,                 ///< The update event is used as the trigger output (TRIG).
    TIM_TRIGSource_OC1    = TIM_CR2_MMS_OC1,                    ///< The trigger output sends a positive pulse when the CC1IF flag
    ///< is to be set, as soon as a capture or compare match occurs (TRIG).
    TIM_TRIGSource_OC1Ref = TIM_CR2_MMS_OC1REF,                 ///< OC1REF signal is used as the trigger output (TRIG).
    TIM_TRIGSource_OC2Ref = TIM_CR2_MMS_OC2REF,                 ///< OC2REF signal is used as the trigger output (TRIG).
    TIM_TRIGSource_OC3Ref = TIM_CR2_MMS_OC3REF,                 ///< OC3REF signal is used as the trigger output (TRIG).
    TIM_TRIGSource_OC4Ref = TIM_CR2_MMS_OC4REF                  ///< OC4REF signal is used as the trigger output (TRIG).
} TIMMMS_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Slave_Mode
/// @anchor TIM_Slave_Mode
typedef enum {
    TIM_SlaveMode_Reset = TIM_SMCR_SMS_RESET,                   ///< Rising edge of the selected trigger signal (TRGI) re-initializes
    ///< the counter and triggers an update of the registers.
    TIM_SlaveMode_Gated     = TIM_SMCR_SMS_GATED,               ///< The counter clock is enabled when the trigger signal (TRGI) is high.
    TIM_SlaveMode_Trigger   = TIM_SMCR_SMS_TRIGGER,             ///< The counter starts at a rising edge of the trigger TRGI.
    TIM_SlaveMode_External1 = TIM_SMCR_SMS_EXTERNAL1            ///< Rising edges of the selected trigger (TRGI) clock the counter.
} TIMSMSMODE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Event_Source
/// @anchor TIM_Event_Source
typedef enum {
    TIM_EventSource_Update  = TIM_EGR_UG,                       ///< Timer update Event source
    TIM_EventSource_CC1     = TIM_EGR_CC1G,                     ///< Timer Capture Compare 1 Event source
    TIM_EventSource_CC2     = TIM_EGR_CC2G,                     ///< Timer Capture Compare 2 Event source
    TIM_EventSource_CC3     = TIM_EGR_CC3G,                     ///< Timer Capture Compare 3 Event source
    TIM_EventSource_CC4     = TIM_EGR_CC4G,                     ///< Timer Capture Compare 4 Event source
    TIM_EventSource_COM     = TIM_EGR_COMG,                     ///< Timer COM event source
    TIM_EventSource_Trigger = TIM_EGR_TG,                       ///< Timer Trigger Event source
    TIM_EventSource_Break   = TIM_EGR_BG,                       ///< Timer Break event source
    TIM_EventSource_CC5     = (s32)0x00010000,                  ///< Timer Capture Compare 5 Event source
} TIMEGR_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_External_Trigger_Prescaler
/// @anchor TIM_External_Trigger_Prescaler
typedef enum {
    TIM_ExtTRGPSC_OFF  = TIM_SMCR_ETPS_OFF,                     ///< ETRP Prescaler OFF
    TIM_ExtTRGPSC_DIV2 = TIM_SMCR_ETPS_DIV2,                    ///< ETRP frequency divided by 2
    TIM_ExtTRGPSC_DIV4 = TIM_SMCR_ETPS_DIV4,                    ///< ETRP frequency divided by 4
    TIM_ExtTRGPSC_DIV8 = TIM_SMCR_ETPS_DIV8                     ///< ETRP frequency divided by 8
} TIMEXTTRGPSC_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_TIx_External_Clock_Source
/// @anchor TIM_TIx_External_Clock_Source
typedef enum {
    TIM_TIxExternalCLK1Source_TI1   = TIM_SMCR_TS_TI1FP1,       ///< Filtered Timer Input 1
    TIM_TIxExternalCLK1Source_TI2   = TIM_SMCR_TS_TI2FP2,       ///< Filtered Timer Input 2
    TIM_TIxExternalCLK1Source_TI1ED = TIM_SMCR_TS_TI1F_ED       ///< TI1 Edge Detector
} TIM_TIEXTCLKSRC_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief Lock_level
/// @anchor Lock_level
typedef enum {
    TIM_LOCKLevel_OFF = TIM_BDTR_LOCK_OFF,                      ///< No bit is write protected.
    TIM_LOCKLevel_1   = TIM_BDTR_LOCK_1,                        ///< DTG bits in TIMx_BDTR register, OISx and OISxN bits in TIMx_CR2
    ///< register and BKE/BKP/AOE bits in TIMx_BDTR register can no longer be written.
    TIM_LOCKLevel_2 = TIM_BDTR_LOCK_2,                          ///< LOCK Level 1 + CC Polarity bits (CCxP/CCxNP bits in TIMx_CCER
    ///< register, as s32 as the related channel is configured in output through the CCxS
    ///< bits) as well as OSSR and OSSI bits can no longer be written.
    TIM_LOCKLevel_3 = TIM_BDTR_LOCK_3                           ///< LOCK Level 2 + CC Control bits (OCxM and OCxPE bits in TIMx_CCMRx registers,
                      ///< as s32 as the related channel is configured in output through the CCxS bits)
                      ///< can no longer be written.
} TIMLOCKLEVEL_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_One_Pulse_Mode
/// @anchor TIM_One_Pulse_Mode
typedef enum {
    TIM_OPMode_Repetitive = 0,                                  ///< Counter is not stopped at update event
    TIM_OPMode_Single     = TIM_CR1_OPM                         ///< Counter stops counting at the next update event (clearing the bit CEN)
} TIMOPMODE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_Polarity
/// @anchor TIM_Output_Compare_Polarity
typedef enum {
    TIM_OCPolarity_High,                                        ///< Output Compare active high
    TIM_OCPolarity_Low = TIM_CCER_CC1P                          ///< Output Compare active low
} TIMCCxP_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_N_Polarity
/// @anchor TIM_Output_Compare_N_Polarity
typedef enum {
    TIM_OCNPolarity_High,                                       ///< Output Compare active high
    TIM_OCNPolarity_Low = TIM_CCER_CC1NP                        ///< Output Compare active low
} TIMCCxNP_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_state
/// @anchor TIM_Output_Compare_state
typedef enum {
    TIM_OutputState_Disable = 0,                                ///< Output Compare Disable
    TIM_OutputState_Enable  = TIM_CCER_CC1EN                     ///< Output Compare Enable
} TIMOUTPUTSTATE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_N_state
/// @anchor TIM_Output_Compare_N_state
typedef enum {
    TIM_OutputNState_Disable = 0,                               ///< Output Compare N Disable
    TIM_OutputNState_Enable  = TIM_CCER_CC1NEN                   ///< Output Compare N Enable
} TIMOUTPUTNSTATE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Capture_Compare_state
/// @anchor TIM_Capture_Compare_state
typedef enum {
    TIM_CCx_Disable = 0,                                        ///< Capture/Compare Enable
    TIM_CCx_Enable  = TIM_CCER_CC1EN                             ///< Capture/Compare Enable
} TIMCCxE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Capture_Compare_N_state
/// @anchor TIM_Capture_Compare_N_state
typedef enum {
    TIM_CCxN_Disable = 0,                                       ///< Capture/Compare N Enable
    TIM_CCxN_Enable  = TIM_CCER_CC1NEN                           ///< Capture/Compare N Enable
} TIMCCxNE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief Break_Input_enable_disable
/// @anchor Break_Input_enable_disable
typedef enum {
    TIM_Break_Disable = 0,                                      ///< Break inputs (BRK and CSS clock failure event) disabled
    TIM_Break_Enable  = TIM_BDTR_BKEN                            ///< Break inputs (BRK and CSS clock failure event) enabled
} TIMBKE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief Break_Polarity
/// @anchor Break_Polarity
typedef enum {
    TIM_BreakPolarity_Low  = 0,                                 ///< Break input BRK is active low
    TIM_BreakPolarity_High = TIM_BDTR_BKP                       ///< Break input BRK is active high
} TIMBKP_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_AOE_Bit_Set_Reset
/// @anchor TIM_AOE_Bit_Set_Reset
typedef enum {
    TIM_AutomaticOutput_Disable = 0,                            ///< MOE can be set only by software.
    TIM_AutomaticOutput_Enable  = TIM_BDTR_AOEN                  ///< MOE can be set by software or automatically at the next
                                  ///< update event (if the break input is not be active).
} TIMAOE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DOE_Bit_Set_Reset
/// @anchor TIM_DOE_Bit_Set_Reset
typedef enum {
    TIM_DirectOutput_Disable = 0,                               ///< Direct output disable, output waiting for dead time
    TIM_DirectOutput_Enable  = TIM_BDTR_DOEN                     ///< Direct output enable, no longer waiting for output after dead time
} TIMDOE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief OSSI_Off_State_Selection_for_Idle_mode_state
/// @anchor OSSI_Off_State_Selection_for_Idle_mode_state
typedef enum {
    TIM_OSSIState_Disable = 0,                                  ///< When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
    TIM_OSSIState_Enable  = TIM_BDTR_OSSI                       ///< When inactive, OC/OCN outputs are forced first with their idle level
                            ///< as soon as CCxE=1 or CCxNE=1. OC/OCN enable output signal=1).
} TIMOSSI_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief OSSR_Off_State_Selection_for_Run_mode_state
/// @anchor OSSR_Off_State_Selection_for_Run_mode_state
typedef enum {
    TIM_OSSRState_Disable = 0,                                  ///< When inactive, OC/OCN outputs are disabled (OC/OCN enable output signal=0).
    TIM_OSSRState_Enable  = TIM_BDTR_OSSR                       ///< When inactive, OC/OCN outputs are enabled with their inactive level
                            ///< as soon as CCxE=1 or CCxNE=1. Then, OC/OCN enable output signal=1.
} TIMOSSR_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_Idle_State
/// @anchor TIM_Output_Compare_Idle_State
typedef enum {
    TIM_OCIdleState_Reset = 0,                                  ///< OCn=0 (after a dead-time if OCnN is implemented) when MOE=0.(n= 0 : 4)
    TIM_OCIdleState_Set   = TIM_CR2_OIS1                        ///< OCn=1 (after a dead-time if OCnN is implemented) when MOE=0.(n= 0 : 4)
} TIMOIS_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_N_Idle_State
/// @anchor TIM_Output_Compare_N_Idle_State
typedef enum {
    TIM_OCNIdleState_Reset = 0,                                 ///< OCnN=0 after a dead-time when MOE=0.(n= 0 : 4)
    TIM_OCNIdleState_Set   = TIM_CR2_OIS1N                      ///< OCnN=1 after a dead-time when MOE=0.(n= 0 : 4)
} TIMOISN_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Input_Capture_Selection
/// @anchor TIM_Input_Capture_Selection
typedef enum {
    TIM_ICSelection_DirectTI   = TIM_CCMR1_CC1S_DIRECTTI,
    TIM_ICSelection_IndirectTI = TIM_CCMR1_CC1S_INDIRECTTI,
    TIM_ICSelection_TRC        = TIM_CCMR1_CC1S_TRC             ///< TIM Input is selected to be connected to TRC.
} TIMICSEL_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Input_Capture_Prescaler
/// @anchor TIM_Input_Capture_Prescaler
typedef enum {
    TIM_ICPSC_DIV1 = 0x0000,                                    ///< no prescaler
    TIM_ICPSC_DIV2 = 0x0004,                                    ///< capture is done once every 2 events
    TIM_ICPSC_DIV4 = 0x0008,                                    ///< capture is done once every 4 events
    TIM_ICPSC_DIV8 = 0x000C                                     ///< capture is done once every 8 events
} TIMICPSC_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Input_Capture_Polarity
/// @anchor TIM_Input_Capture_Polarity
typedef enum {
    TIM_ICPolarity_Rising  = 0,                                 ///< IC Rising edge
    TIM_ICPolarity_Falling = TIM_CCER_CC1P,                     ///< IC Falling edge
    TIM_ICPolarity_BothEdge = TIM_CCER_CC1P | TIM_CCER_CC1NP
} TIMICP_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_External_Trigger_Polarity
/// @anchor TIM_External_Trigger_Polarity
typedef enum {
    TIM_ExtTRGPolarity_NonInverted = 0,                         ///< Active high or rising edge active
    TIM_ExtTRGPolarity_Inverted    = TIM_SMCR_ETP               ///< Active low or falling edge active
} TIMETP_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Prescaler_Reload_Mode
/// @anchor TIM_Prescaler_Reload_Mode
typedef enum {
    TIM_PSCReloadMode_Update    = 0,                            ///< The Prescaler is loaded at the update event
    TIM_PSCReloadMode_Immediate = TIM_EGR_UG                    ///< The Prescaler is loaded immediately
} TIMUG_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Encoder_Mode
/// @anchor TIM_Encoder_Mode
typedef enum {
    TIM_EncoderMode_TI1  = TIM_SMCR_SMS_ENCODER1,               ///< Counter counts on TI1FP1 edge depending on TI2FP2 level.
    TIM_EncoderMode_TI2  = TIM_SMCR_SMS_ENCODER2,               ///< Counter counts on TI2FP2 edge depending on TI1FP1 level.
    TIM_EncoderMode_TI12 = TIM_SMCR_SMS_ENCODER3                ///< Counter counts on both TI1FP1 and TI2FP2 edges depending
                           ///< on the level of the other input.
} TIMSMSENCODER_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Update_Source
/// @anchor TIM_Update_Source
typedef enum {
    TIM_UpdateSource_Global  = 0,                               ///< Source of update is counter overflow/underflow.
    TIM_UpdateSource_Regular = TIM_CR1_URS                      ///< Source of update is the counter overflow/underflow
                               ///< or the setting of UG bit, or an update generation
                               ///< through the slave mode controller.
} TIMURS_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_Preload_State
/// @anchor TIM_Output_Compare_Preload_State
typedef enum {
    TIM_OCPreload_Disable = 0,                                  ///< TIM output compare preload disable
    TIM_OCPreload_Enable  = TIM_CCMR1_OC1PEN                     ///< TIM output compare preload enable
} TIMOCPE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_Fast_State
/// @anchor TIM_Output_Compare_Fast_State
typedef enum {
    TIM_OCFast_Disable = 0,                                     ///< TIM output compare fast disable
    TIM_OCFast_Enable  = TIM_CCMR1_OC1FEN,                       ///< TIM output compare fast enable
} TIMOCFE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Output_Compare_Clear_State
/// @anchor TIM_Output_Compare_Clear_State
typedef enum {
    TIM_OCClear_Disable = 0,                                    ///< TIM Output clear disable
    TIM_OCClear_Enable  = TIM_CCMR1_OC1CEN                       ///< TIM Output clear enable
} TIMOCCE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Master_Slave_Mode
/// @anchor TIM_Master_Slave_Mode
typedef enum {
    TIM_MasterSlaveMode_Disable = 0,                            ///< No action
    TIM_MasterSlaveMode_Enable  = TIM_SMCR_MSM                  ///< synchronization between the current timer and its slaves (through TRIG)
} TIMMSM_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_interrupt_sources
/// @anchor TIM_Master_Slave_Mode
typedef enum {
    TIM_IT_Update  = TIM_DIER_UI,                               ///< TIM update Interrupt source
    TIM_IT_CC1     = TIM_DIER_CC1I,                             ///< TIM Capture Compare 1 Interrupt source
    TIM_IT_CC2     = TIM_DIER_CC2I,                             ///< TIM Capture Compare 2 Interrupt source
    TIM_IT_CC3     = TIM_DIER_CC3I,                             ///< TIM Capture Compare 3 Interrupt source
    TIM_IT_CC4     = TIM_DIER_CC4I,                             ///< TIM Capture Compare 4 Interrupt source
    TIM_IT_COM     = TIM_DIER_COMI,                             ///< TIM Commutation Interrupt source
    TIM_IT_Trigger = TIM_DIER_TI,                               ///< TIM Trigger Interrupt source
    TIM_IT_Break   = TIM_DIER_BI                                ///< TIM Break Interrupt source
    , TIM_IT_CC5     = TIM_DIER_CC5I                            ///< TIM Capture Compare 5 Interrupt source
} TIMIT_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_Flags
/// @anchor TIM_Flags
typedef enum {
    TIM_FLAG_Update  = TIM_SR_UI,                              ///< TIM update Flag
    TIM_FLAG_CC1     = TIM_SR_CC1I,                            ///< TIM Capture Compare 1 Flag
    TIM_FLAG_CC2     = TIM_SR_CC2I,                            ///< TIM Capture Compare 2 Flag
    TIM_FLAG_CC3     = TIM_SR_CC3I,                            ///< TIM Capture Compare 3 Flag
    TIM_FLAG_CC4     = TIM_SR_CC4I,                            ///< TIM Capture Compare 4 Flag
    TIM_FLAG_COM     = TIM_SR_COMI,                            ///< TIM Commutation Flag
    TIM_FLAG_Trigger = TIM_SR_TI,                              ///< TIM Trigger Flag
    TIM_FLAG_Break   = TIM_SR_BI,                              ///< TIM Break Flag
    TIM_FLAG_CC1OF   = TIM_SR_CC1O,                            ///< TIM Capture Compare 1 overcapture Flag
    TIM_FLAG_CC2OF   = TIM_SR_CC2O,                            ///< TIM Capture Compare 2 overcapture Flag
    TIM_FLAG_CC3OF   = TIM_SR_CC3O,                            ///< TIM Capture Compare 3 overcapture Flag
    TIM_FLAG_CC4OF   = TIM_SR_CC4O                             ///< TIM Capture Compare 4 overcapture Flag
    , TIM_FLAG_CC5    = TIM_SR_CC5I                            ///< TIM Capture Compare 5 Flag
} TIMFLAG_Typedef;
////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DMA_sources
/// @anchor TIM_DMA_sources
typedef enum {
    TIM_DMA_Update  = TIM_DIER_UD,                              ///< TIM update Interrupt source
    TIM_DMA_CC1     = TIM_DIER_CC1D,                            ///< TIM Capture Compare 1 DMA source
    TIM_DMA_CC2     = TIM_DIER_CC2D,                            ///< TIM Capture Compare 2 DMA source
    TIM_DMA_CC3     = TIM_DIER_CC3D,                            ///< TIM Capture Compare 3 DMA source
    TIM_DMA_CC4     = TIM_DIER_CC4D,                            ///< TIM Capture Compare 4 DMA source
    TIM_DMA_COM     = TIM_DIER_COMD,                            ///< TIM Commutation DMA source
    TIM_DMA_Trigger = TIM_DIER_TD                               ///< TIM Trigger DMA source
} TIMDMASRC_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DMA_Base_address
/// @anchor TIM_DMA_Base_address
typedef enum {
    TIM_DMABase_CR1   = 0x0000,
    TIM_DMABase_CR2   = 0x0001,
    TIM_DMABase_SMCR  = 0x0002,
    TIM_DMABase_DIER  = 0x0003,
    TIM_DMABase_SR    = 0x0004,
    TIM_DMABase_EGR   = 0x0005,
    TIM_DMABase_CCMR1 = 0x0006,
    TIM_DMABase_CCMR2 = 0x0007,
    TIM_DMABase_CCER  = 0x0008,
    TIM_DMABase_CNT   = 0x0009,
    TIM_DMABase_PSC   = 0x000A,
    TIM_DMABase_ARR   = 0x000B,
    TIM_DMABase_RCR   = 0x000C,
    TIM_DMABase_CCR1  = 0x000D,
    TIM_DMABase_CCR2  = 0x000E,
    TIM_DMABase_CCR3  = 0x000F,
    TIM_DMABase_CCR4  = 0x0010,
    TIM_DMABase_BDTR  = 0x0011,
    TIM_DMABase_DCR   = 0x0012
} TIMDMABASE_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief TIM_DMA_Burst_Length
/// @anchor TIM_DMA_Burst_Length
typedef enum {
    TIM_DMABurstLength_1Byte   = 0x0000,
    TIM_DMABurstLength_2Bytes  = 0x0100,
    TIM_DMABurstLength_3Bytes  = 0x0200,
    TIM_DMABurstLength_4Bytes  = 0x0300,
    TIM_DMABurstLength_5Bytes  = 0x0400,
    TIM_DMABurstLength_6Bytes  = 0x0500,
    TIM_DMABurstLength_7Bytes  = 0x0600,
    TIM_DMABurstLength_8Bytes  = 0x0700,
    TIM_DMABurstLength_9Bytes  = 0x0800,
    TIM_DMABurstLength_10Bytes = 0x0900,
    TIM_DMABurstLength_11Bytes = 0x0A00,
    TIM_DMABurstLength_12Bytes = 0x0B00,
    TIM_DMABurstLength_13Bytes = 0x0C00,
    TIM_DMABurstLength_14Bytes = 0x0D00,
    TIM_DMABurstLength_15Bytes = 0x0E00,
    TIM_DMABurstLength_16Bytes = 0x0F00,
    TIM_DMABurstLength_17Bytes = 0x1000,
    TIM_DMABurstLength_18Bytes = 0x1100
} TIMDMABURSTLENGTH_Typedef;
////////////////////////////////////////////////////////////////////////////////
/// @brief  TIM Time Base Init structure definition
/// @note   This structure is used with all tim.
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u16 TIM_Prescaler;                                          ///< Specifies the prescaler value used to divide the TIM clock.
    ///< This parameter can be a number between 0x0000 and 0xFFFF
    TIMCOUNTMODE_Typedef TIM_CounterMode;                       ///< Specifies the counter mode.
    ///< This parameter can be a value of @ref TIM_Counter_Mode
    u32 TIM_Period;                                             ///< Specifies the period value to be loaded into the active
    ///< Auto-Reload Register at the next update event.
    ///< This parameter must be a number between 0x0000 and 0xFFFF/0xFFFFFFFF.
    ///< @note 0xFFFFFFFF is valid only for MM32 32bit Timers: eg.TIM2 or TIM5.
    TIMCKD_TypeDef TIM_ClockDivision;                           ///< Specifies the clock division.
    ///< This parameter can be a value of @ref TIM_Clock_Division_CKD
    u8 TIM_RepetitionCounter;                                   ///< Specifies the repetition counter value. Each time the RCR downcounter
    ///< reaches zero, an update event is generated and counting restarts
    ///< from the RCR value (N).
    ///< This means in PWM mode that (N+1) corresponds to:
    ///<    - the number of PWM periods in edge-aligned mode
    ///<    - the number of half PWM period in center-aligned mode
    ///< This parameter must be a number between 0x00 and 0xFF.
    ///< @note This parameter is valid only for TIM1 and TIM8.
} TIM_TimeBaseInitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  TIM Output Compare Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    TIMOCMODE_Typedef TIM_OCMode;                               ///< Specifies the TIM mode.
    ///< This parameter can be a value of TIM_Output_Compare_and_PWM_modes
    TIMOUTPUTSTATE_Typedef TIM_OutputState;                     ///< Specifies the TIM Output Compare state.
    ///< This parameter can be a value of TIM_Output_Compare_state
    TIMOUTPUTNSTATE_Typedef TIM_OutputNState;                   ///< Specifies the TIM complementary Output Compare state.
    ///< This parameter can be a value of TIM_Output_Compare_N_state
    ///< @note This parameter is valid only for TIM1 and TIM8.
    u32 TIM_Pulse;                                              ///< Specifies the pulse value to be loaded into the Capture Compare Register.
    ///< This parameter can be a number between 0x0000 and 0xFFFF/0xFFFFFFFF
    ///< @note 0xFFFFFFFF is valid only for MM32 32bit Timers: eg.TIM2 or TIM5.
    TIMCCxP_Typedef TIM_OCPolarity;                             ///< Specifies the output polarity.
    ///< This parameter can be a value of @ref TIM_Output_Compare_Polarity
    TIMCCxNP_Typedef TIM_OCNPolarity;                           ///< Specifies the complementary output polarity.
    ///< This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
    ///< @note This parameter is valid only for TIM1 and TIM8.
    TIMOIS_Typedef TIM_OCIdleState;                             ///< Specifies the TIM Output Compare pin state during Idle state.
    ///< This parameter can be a value of @ref TIM_Output_Compare_Idle_State
    ///< @note This parameter is valid only for TIM1 and TIM8.
    TIMOISN_Typedef TIM_OCNIdleState;                           ///< Specifies the TIM Output Compare pin state during Idle state.
    ///< This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
    ///< @note This parameter is valid only for TIM1 and TIM8.
} TIM_OCInitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  TIM Input Capture Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    TIMCHx_Typedef TIM_Channel;                                 ///< Specifies the TIM channel.
    ///< This parameter can be a value of @ref TIM_Channel
    TIMICP_Typedef TIM_ICPolarity;                              ///< Specifies the active edge of the input signal.
    ///< This parameter can be a value of @ref TIM_Input_Capture_Polarity
    TIMICSEL_Typedef TIM_ICSelection;                           ///< Specifies the input.
    ///< This parameter can be a value of @ref TIM_Input_Capture_Selection
    TIMICPSC_Typedef TIM_ICPrescaler;                           ///< Specifies the Input Capture Prescaler.
    ///< This parameter can be a value of @ref TIM_Input_Capture_Prescaler
    u16 TIM_ICFilter;                                           ///< Specifies the input capture filter.
    ///< This parameter can be a number between 0x0 and 0xF
} TIM_ICInitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  BDTR structure definition
/// @note   This structure is used only with TIM1 and TIM8.
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    TIMOSSR_Typedef TIM_OSSRState;                              ///< Specifies the Off-State selection used in Run mode.
    ///< This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state
    TIMOSSI_Typedef TIM_OSSIState;                              ///< Specifies the Off-State used in Idle state.
    ///< This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state
    TIMLOCKLEVEL_Typedef TIM_LOCKLevel;                         ///< Specifies the LOCK level parameters.
    ///< This parameter can be a value of @ref Lock_level
    u16 TIM_DeadTime;                                           ///< Specifies the delay time between the switching-off and
    ///< the switching-on of the outputs.
    ///< This parameter can be a number between 0x00 and 0xFF
    TIMBKE_Typedef TIM_Break;                                   ///< Specifies whether the TIM Break input is enabled or not.
    ///< This parameter can be a value of @ref Break_Input_enable_disable
    TIMBKP_Typedef TIM_BreakPolarity;                           ///< Specifies the TIM Break Input pin polarity.
    ///< This parameter can be a value of @ref Break_Polarity
    TIMAOE_Typedef TIM_AutomaticOutput;                         ///< Specifies whether the TIM Automatic Output feature is enabled or not.
    ///< This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset
} TIM_BDTRInitTypeDef;
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup TIM_Exported_Variables
/// @{
#ifdef _HAL_TIM_C_
#define GLOBAL

static void TI1_Configure(TIM_TypeDef* tim, u16 polarity, u16 selection, u16 filter);
static void TI2_Configure(TIM_TypeDef* tim, u16 polarity, u16 selection, u16 filter);
static void TI3_Configure(TIM_TypeDef* tim, u16 polarity, u16 selection, u16 filter);
static void TI4_Configure(TIM_TypeDef* tim, u16 polarity, u16 selection, u16 filter);


#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup TIM_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
//=================  TimeBase management  ======================================
void TIM_DeInit(TIM_TypeDef* tim);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* init_struct);
void TIM_TimeBaseInit(TIM_TypeDef* tim, TIM_TimeBaseInitTypeDef* init_struct);
void TIM_PrescalerConfig(TIM_TypeDef* tim, u16 prescaler, TIMUG_Typedef reload_mode);
void TIM_CounterModeConfig(TIM_TypeDef* tim, TIMCOUNTMODE_Typedef counter_mode);
void TIM_SetCounter(TIM_TypeDef* tim, u32 counter);
void TIM_SetAutoreload(TIM_TypeDef* tim, u16 auto_reload);
void TIM_UpdateDisableConfig(TIM_TypeDef* tim, FunctionalState state);
void TIM_UpdateRequestConfig(TIM_TypeDef* tim, TIMURS_Typedef source);
void TIM_ARRPreloadConfig(TIM_TypeDef* tim, FunctionalState state);
void TIM_SelectOnePulseMode(TIM_TypeDef* tim, TIMOPMODE_Typedef mode);
void TIM_SetClockDivision(TIM_TypeDef* tim, TIMCKD_TypeDef clock_div);
void TIM_Cmd(TIM_TypeDef* tim, FunctionalState state);

u32 TIM_GetCounter(TIM_TypeDef* tim);
u16 TIM_GetPrescaler(TIM_TypeDef* tim);

//=================  Advanced-control timers specific features  ================
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* init_struct);
void TIM_BDTRConfig(TIM_TypeDef* tim, TIM_BDTRInitTypeDef* init_struct);
void TIM_CtrlPWMOutputs(TIM_TypeDef* tim, FunctionalState state);

//=================  Output Compare management  ================================
void TIM_OCStructInit(TIM_OCInitTypeDef* init_struct);
void TIM_OC1Init(TIM_TypeDef* tim, TIM_OCInitTypeDef* init_struct);
void TIM_OC2Init(TIM_TypeDef* tim, TIM_OCInitTypeDef* init_struct);
void TIM_OC3Init(TIM_TypeDef* tim, TIM_OCInitTypeDef* init_struct);
void TIM_OC4Init(TIM_TypeDef* tim, TIM_OCInitTypeDef* init_struct);
void TIM_SelectOCxM(TIM_TypeDef* tim, TIMCHx_Typedef channel, TIMOCMODE_Typedef mode);
void TIM_SetCompare1(TIM_TypeDef* tim, u32 compare);
void TIM_SetCompare2(TIM_TypeDef* tim, u32 compare);
void TIM_SetCompare3(TIM_TypeDef* tim, u32 compare);
void TIM_SetCompare4(TIM_TypeDef* tim, u32 compare);
void TIM_ForcedOC1Config(TIM_TypeDef* tim, TIMOCMODE_Typedef forced_action);
void TIM_ForcedOC2Config(TIM_TypeDef* tim, TIMOCMODE_Typedef forced_action);
void TIM_ForcedOC3Config(TIM_TypeDef* tim, TIMOCMODE_Typedef forced_action);
void TIM_ForcedOC4Config(TIM_TypeDef* tim, TIMOCMODE_Typedef forced_action);
void TIM_CCPreloadControl(TIM_TypeDef* tim, FunctionalState state);
void TIM_OC1PreloadConfig(TIM_TypeDef* tim, TIMOCPE_Typedef preload);
void TIM_OC2PreloadConfig(TIM_TypeDef* tim, TIMOCPE_Typedef preload);
void TIM_OC3PreloadConfig(TIM_TypeDef* tim, TIMOCPE_Typedef preload);
void TIM_OC4PreloadConfig(TIM_TypeDef* tim, TIMOCPE_Typedef preload);
void TIM_OC1FastConfig(TIM_TypeDef* tim, TIMOCFE_Typedef fast);
void TIM_OC2FastConfig(TIM_TypeDef* tim, TIMOCFE_Typedef fast);
void TIM_OC3FastConfig(TIM_TypeDef* tim, TIMOCFE_Typedef fast);
void TIM_OC4FastConfig(TIM_TypeDef* tim, TIMOCFE_Typedef fast);
void TIM_ClearOC1Ref(TIM_TypeDef* tim, TIMOCCE_Typedef clear);
void TIM_ClearOC2Ref(TIM_TypeDef* tim, TIMOCCE_Typedef clear);
void TIM_ClearOC3Ref(TIM_TypeDef* tim, TIMOCCE_Typedef clear);
void TIM_ClearOC4Ref(TIM_TypeDef* tim, TIMOCCE_Typedef clear);
void TIM_OC1PolarityConfig(TIM_TypeDef* tim, TIMCCxP_Typedef polarity);
void TIM_OC1NPolarityConfig(TIM_TypeDef* tim, TIMCCxNP_Typedef polarity);
void TIM_OC2PolarityConfig(TIM_TypeDef* tim, TIMCCxP_Typedef polarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* tim, TIMCCxNP_Typedef polarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* tim, TIMCCxP_Typedef polarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* tim, TIMCCxNP_Typedef polarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* tim, TIMCCxP_Typedef polarity);
void TIM_CCxCmd(TIM_TypeDef* tim, TIMCHx_Typedef channel, TIMCCxE_Typedef ccx_en);
void TIM_CCxNCmd(TIM_TypeDef* tim, TIMCHx_Typedef channel, TIMCCxNE_Typedef ccxn_en);
void TIM_SelectCOM(TIM_TypeDef* tim, FunctionalState state);

//=================  Input Capture management  =================================
void TIM_ICStructInit(TIM_ICInitTypeDef* init_struct);
void TIM_ICInit(TIM_TypeDef* tim, TIM_ICInitTypeDef* init_struct);
void TIM_PWMIConfig(TIM_TypeDef* tim, TIM_ICInitTypeDef* init_struct);
void TIM_SetIC1Prescaler(TIM_TypeDef* tim, TIMICPSC_Typedef psc);
void TIM_SetIC2Prescaler(TIM_TypeDef* tim, TIMICPSC_Typedef psc);
void TIM_SetIC3Prescaler(TIM_TypeDef* tim, TIMICPSC_Typedef psc);
void TIM_SetIC4Prescaler(TIM_TypeDef* tim, TIMICPSC_Typedef psc);

u32 TIM_GetCapture1(TIM_TypeDef* tim);
u32 TIM_GetCapture2(TIM_TypeDef* tim);
u32 TIM_GetCapture3(TIM_TypeDef* tim);
u32 TIM_GetCapture4(TIM_TypeDef* tim);

//=================  Interrupts, DMA and flags management  =====================
void TIM_ITConfig(TIM_TypeDef* tim, u32 it, FunctionalState state);//TIMIT_TypeDef
void TIM_GenerateEvent(TIM_TypeDef* tim, TIMEGR_Typedef source);
void TIM_ClearFlag(TIM_TypeDef* tim, TIMFLAG_Typedef flag);
void TIM_ClearITPendingBit(TIM_TypeDef* tim, u32 it);//TIMIT_TypeDef
void TIM_DMAConfig(TIM_TypeDef* tim, TIMDMABASE_Typedef dma_base, TIMDMABURSTLENGTH_Typedef length);
void TIM_DMACmd(TIM_TypeDef* tim, TIMDMASRC_Typedef source, FunctionalState state);
void TIM_SelectCCDMA(TIM_TypeDef* tim, FunctionalState state);
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* tim, TIMFLAG_Typedef flag);
ITStatus   TIM_GetITStatus(TIM_TypeDef* tim, TIMIT_TypeDef it);

//=================  Clocks management  ========================================
void TIM_InternalClockConfig(TIM_TypeDef* tim);
void TIM_ITRxExternalClockConfig(TIM_TypeDef* tim, TIMTS_TypeDef source);
void TIM_TIxExternalClockConfig(TIM_TypeDef* tim, TIM_TIEXTCLKSRC_Typedef source, TIMICP_Typedef polarity, u16 filter);
void TIM_ETRClockMode1Config(TIM_TypeDef* tim, TIMEXTTRGPSC_Typedef psc, TIMETP_Typedef polarity, u16 filter);
void TIM_ETRClockMode2Config(TIM_TypeDef* tim, TIMEXTTRGPSC_Typedef psc, TIMETP_Typedef polarity, u16 filter);

//=================  Synchronization management  ===============================
void TIM_SelectInputTrigger(TIM_TypeDef* tim, TIMTS_TypeDef source);
void TIM_SelectOutputTrigger(TIM_TypeDef* tim, TIMMMS_Typedef source);
void TIM_SelectSlaveMode(TIM_TypeDef* tim, TIMSMSMODE_Typedef mode);
void TIM_SelectMasterSlaveMode(TIM_TypeDef* tim, TIMMSM_Typedef mode);
void TIM_ETRConfig(TIM_TypeDef* tim, TIMEXTTRGPSC_Typedef psc, TIMETP_Typedef polarity, u16 filter);

//=================  Specific interface management  ============================
void TIM_EncoderInterfaceConfig(TIM_TypeDef*          tim,
                                TIMSMSENCODER_Typedef encoder_mode,
                                TIMICP_Typedef        ic1_polarity,
                                TIMICP_Typedef        iC2_polarity);
void TIM_SelectHallSensor(TIM_TypeDef* tim, FunctionalState state);

//=================  extend Channel IC management  ==============================
void TIM_SetIC1Plority(TIM_TypeDef* tim, TIMICP_Typedef pol);
void TIM_SetIC2Plority(TIM_TypeDef* tim, TIMICP_Typedef pol);
void TIM_SetIC3Plority(TIM_TypeDef* tim, TIMICP_Typedef pol);
void TIM_SetIC4Plority(TIM_TypeDef* tim, TIMICP_Typedef pol);

#define exTIM_SetIC1Plority                     TIM_SetIC1Plority
#define exTIM_SetIC2Plority                     TIM_SetIC2Plority
#define exTIM_SetIC3Plority                     TIM_SetIC3Plority
#define exTIM_SetIC4Plority                     TIM_SetIC4Plority
//=================  extend Channel 5 management  ==============================

void TIM_SetCompare5(TIM_TypeDef* tim, u32 compare);
void TIM_OC5Init(TIM_TypeDef* tim, TIM_OCInitTypeDef* init_struct);
void TIM_OC5PreloadConfig(TIM_TypeDef* tim, TIMOCPE_Typedef preload);
void TIM_OC5PolarityConfig(TIM_TypeDef* tim, TIMCCxP_Typedef polarity);
void TIM_OC5FastConfig(TIM_TypeDef* tim, TIMOCFE_Typedef fast);
void TIM_ClearOC5Ref(TIM_TypeDef* tim, TIMOCCE_Typedef clear);
u32 TIM_GetCapture5(TIM_TypeDef* tim);

#define exTIM_SetCompare5                       TIM_SetCompare5
#define exTIM_OC5Init                           TIM_OC5Init
#define exTIM_OC5PreloadConfig                  TIM_OC5PreloadConfig
#define exTIM_OC5PolarityConfig                 TIM_OC5PolarityConfig
#define exTIM_OC5FastConfig                     TIM_OC5FastConfig
#define exTIM_ClearOC5Ref                       TIM_ClearOC5Ref
#define exTIM_GetCapture5                       TIM_GetCapture5

//============= extend Advanced-control timers specific features  ==============
void TIM_DirectOutput(TIM_TypeDef* tim, FunctionalState state);
#define exTIM_DirectOutput TIM_DirectOutput
void TIM_PWMShiftConfig(TIM_TypeDef* tim, u32 it, FunctionalState state);
void TIM_SetCCR1FALL(TIM_TypeDef* tim, u32 shift);
void TIM_SetCCR2FALL(TIM_TypeDef* tim, u32 shift);
void TIM_SetCCR3FALL(TIM_TypeDef* tim, u32 shift);
void TIM_SetCCR4FALL(TIM_TypeDef* tim, u32 shift);
void TIM_SetCCR5FALL(TIM_TypeDef* tim, u32 shift);
/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_TIM_H
////////////////////////////////////////////////////////////////////////////////
