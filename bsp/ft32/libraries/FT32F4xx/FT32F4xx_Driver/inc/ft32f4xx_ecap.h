/**
  ******************************************************************************
  * @file         ft32f4xx_ecap.h
  * @author       FMD AE
  * @brief        This file contains all the functions prototypes for the eCAP firmware
  *               library.
  * @version      V1.0.0
  * @data         2025-04-17
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_ECAP_H
#define __FT32F4XX_ECAP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup ECAP
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ECAP Init structures definition
  */
typedef struct
{
    uint32_t ECAPMode;              /*!< Specifies the mode of operation for ecap.
                                       This parameter can be a value of @ref ECAP_mode */
    uint32_t EventPrescaler;        /*!< Specifies the event filter prescale of capture mode.
                                       This parameter can be a value of @ref ECAP_event_prescaler */
    FunctionalState CaptureLoad;    /*!< Specifies the enable loading of CAP1-4 registers on a capture event.
                                       This parameter can be set to ENABLE or DISABLE. */
    FunctionalState CaptureEvent4Reset;    /*!< Specifies whether the counter should be reset at capture event 4.
                                              This parameter can be set to ENABLE or DISABLE */
    FunctionalState CaptureEvent3Reset;    /*!< Specifies whether the counter should be reset at capture event 3.
                                              This parameter can be set to ENABLE or DISABLE */
    FunctionalState CaptureEvent2Reset;    /*!< Specifies whether the counter should be reset at capture event 2.
                                              This parameter can be set to ENABLE or DISABLE */
    FunctionalState CaptureEvent1Reset;    /*!< Specifies whether the counter should be reset at capture event 1.
                                              This parameter can be set to ENABLE or DISABLE */
    uint32_t CaptureEvent4Polarity; /*!< Specifies the polarity of capture event 4.
                                       This parameter can be a value of @ref ECAP_event_polarity */
    uint32_t CaptureEvent3Polarity; /*!< Specifies the polarity of capture event 3.
                                       This parameter can be a value of @ref ECAP_event_polarity */
    uint32_t CaptureEvent2Polarity; /*!< Specifies the polarity of capture event 2.
                                       This parameter can be a value of @ref ECAP_event_polarity */
    uint32_t CaptureEvent1Polarity; /*!< Specifies the polarity of capture event 1.
                                       This parameter can be a value of @ref ECAP_event_polarity */
    FunctionalState CounterSyncIn;  /*!< Specifies the Counter Sync-In select mode.
                                       This parameter can be set to ENABLE or DISABLE */
    uint32_t ModCounterStopWrap;    /*!< Specifies the stop value for one-shot mode, and wrap value for continuous mode.
                                       This parameter can be a value of @ref ECAP_mod_counter_stop_wrap  */
    uint32_t ModCounterMode;        /*!< Specifies the one-shot or continuous mode for Mod4 counter.
                                       This parameter can be a value of @ref ECAP_mod_counter_mode */
    uint32_t APWMPolarity;          /*!< Specifies the polarity of APWM output.
                                       This parameter can be a value of @ref ECAP_apwm_output_polarity
                                       Note: This parameter is only valid if the ECAPMode is selected as APWM mode.*/
    uint32_t CounterValue;          /*!< Specifies the counter value for ecap.
                                       This parameter can be a value of @ref ECAP_counter_value
                                       Note: This parameter is only valid if the ECAPMode is selected as APWM mode.*/
    uint32_t CounterPhaseValue;     /*!< Specifies the counter phase offset value for ecap.
                                       This parameter can be a value of @ref ECAP_counter_phase_value
                                       Note: This parameter is only valid if the ECAPMode is selected as APWM mode.*/
    uint32_t Capture1RegisterValue; /*!< Specifies the capture 1 register value for ecap.
                                       This parameter can be a value of @ref ECAP_capture1_register_value
                                       Note: This parameter is only valid if the ECAPMode is selected as APWM mode.*/
    uint32_t Capture2RegisterValue; /*!< Specifies the capture 2 register value for ecap.
                                       This parameter can be a value of @ref ECAP_capture2_register_value
                                       Note: This parameter is only valid if the ECAPMode is selected as APWM mode.*/

} ECAP_InitTypeDef;




/**
  * @brief  ECAP_data_registers_definition
  */
#define  ECAP_DATA_REG_TSCTR   ((uint8_t)0x00U)
#define  ECAP_DATA_REG_CTRPHS  ((uint8_t)0x01U)
#define  ECAP_DATA_REG_CAP1    ((uint8_t)0x02U)
#define  ECAP_DATA_REG_CAP2    ((uint8_t)0x03U)
#define  ECAP_DATA_REG_CAP3    ((uint8_t)0x04U)
#define  ECAP_DATA_REG_CAP4    ((uint8_t)0x05U)

#define IS_ECAP_DATA_REG(TYPE) (((TYPE) == ECAP_DATA_REG_TSCTR ) || \
                                ((TYPE) == ECAP_DATA_REG_CTRPHS) || \
                                ((TYPE) == ECAP_DATA_REG_CAP1  ) || \
                                ((TYPE) == ECAP_DATA_REG_CAP2  ) || \
                                ((TYPE) == ECAP_DATA_REG_CAP3  ) || \
                                ((TYPE) == ECAP_DATA_REG_CAP4  ))




/** @defgroup  ECAP_interrupts_definition ECAP_IT
  * @{
  */
#define ECAP_IT_CEVT1        ECAP_ECEINT_CEVT1
#define ECAP_IT_CEVT2        ECAP_ECEINT_CEVT2
#define ECAP_IT_CEVT3        ECAP_ECEINT_CEVT3
#define ECAP_IT_CEVT4        ECAP_ECEINT_CEVT4
#define ECAP_IT_CTROVF       ECAP_ECEINT_CTROVF
#define ECAP_IT_CTRPRD       ECAP_ECEINT_CTR_EQ_PRD
#define ECAP_IT_CTRCMP       ECAP_ECEINT_CTR_EQ_CMP

#define IS_ECAP_IT(IT) (((IT) == ECAP_IT_CEVT1   ) || \
                        ((IT) == ECAP_IT_CEVT2   ) || \
                        ((IT) == ECAP_IT_CEVT3   ) || \
                        ((IT) == ECAP_IT_CEVT4   ) || \
                        ((IT) == ECAP_IT_CTROVF  ) || \
                        ((IT) == ECAP_IT_CTRPRD  ) || \
                        ((IT) == ECAP_IT_CTRCMP  ) )

/**
  * @}
  */



/** @defgroup ECAP_flags_definition
  * @{
  */
#define ECAP_FLAG_INT         ECAP_ECFLG_INT
#define ECAP_FLAG_CEVT1       ECAP_ECFLG_CEVT1
#define ECAP_FLAG_CEVT2       ECAP_ECFLG_CEVT2
#define ECAP_FLAG_CEVT3       ECAP_ECFLG_CEVT3
#define ECAP_FLAG_CEVT4       ECAP_ECFLG_CEVT4
#define ECAP_FLAG_CTROVF      ECAP_ECFLG_CTROVF
#define ECAP_FLAG_CTRPRD      ECAP_ECFLG_CTR_PRD
#define ECAP_FLAG_CTRCMP      ECAP_ECFLG_CTR_CMP

#define IS_ECAP_FLAG(FLAG) (((FLAG) == ECAP_FLAG_INT   ) || \
                            ((FLAG) == ECAP_FLAG_CEVT1 ) || \
                            ((FLAG) == ECAP_FLAG_CEVT2 ) || \
                            ((FLAG) == ECAP_FLAG_CEVT3 ) || \
                            ((FLAG) == ECAP_FLAG_CEVT4 ) || \
                            ((FLAG) == ECAP_FLAG_CTROVF) || \
                            ((FLAG) == ECAP_FLAG_CTRPRD) || \
                            ((FLAG) == ECAP_FLAG_CTRCMP) )

//#define ECAP_FLAG_MASK    ((uint32_t)(ECAP_FLAG_INT    | \
//                                      ECAP_FLAG_CEVT1  | \
//                                      ECAP_FLAG_CEVT2  | \
//                                      ECAP_FLAG_CEVT3  | \
//                                      ECAP_FLAG_CEVT4  | \
//                                      ECAP_FLAG_CTROVF | \
//                                      ECAP_FLAG_CTRPRD | \
//                                      ECAP_FLAG_CTRCMP ))
/**
  * @}
  */


/** @defgroup  ECAP_mode
  * @{
  */
#define ECAP_MODE_CAPTURE  0U
#define ECAP_MODE_APWM     ECAP_ECCTL2_CAP_APWM

#define IS_ECAP_MODE(MODE) (((MODE) == ECAP_MODE_CAPTURE) || ((MODE) == ECAP_MODE_APWM))

/**
  * @}
  */

/** @defgroup  ECAP_event_prescaler
  * @{
  */
#define ECAP_EVENT_PRESCALER_1   0x00U
#define ECAP_EVENT_PRESCALER_2   0x01U
#define ECAP_EVENT_PRESCALER_4   0x02U
#define ECAP_EVENT_PRESCALER_6   0x03U
#define ECAP_EVENT_PRESCALER_8   0x04U
#define ECAP_EVENT_PRESCALER_10  0x05U
#define ECAP_EVENT_PRESCALER_12  0x06U
#define ECAP_EVENT_PRESCALER_14  0x07U
#define ECAP_EVENT_PRESCALER_16  0x08U
#define ECAP_EVENT_PRESCALER_18  0x09U
#define ECAP_EVENT_PRESCALER_20  0x0AU
#define ECAP_EVENT_PRESCALER_22  0x0BU
#define ECAP_EVENT_PRESCALER_24  0x0CU
#define ECAP_EVENT_PRESCALER_26  0x0DU
#define ECAP_EVENT_PRESCALER_28  0x0EU
#define ECAP_EVENT_PRESCALER_30  0x0FU
#define ECAP_EVENT_PRESCALER_32  0x10U
#define ECAP_EVENT_PRESCALER_34  0x11U
#define ECAP_EVENT_PRESCALER_36  0x12U
#define ECAP_EVENT_PRESCALER_38  0x13U
#define ECAP_EVENT_PRESCALER_40  0x14U
#define ECAP_EVENT_PRESCALER_42  0x15U
#define ECAP_EVENT_PRESCALER_44  0x16U
#define ECAP_EVENT_PRESCALER_46  0x17U
#define ECAP_EVENT_PRESCALER_48  0x18U
#define ECAP_EVENT_PRESCALER_50  0x19U
#define ECAP_EVENT_PRESCALER_52  0x1AU
#define ECAP_EVENT_PRESCALER_54  0x1BU
#define ECAP_EVENT_PRESCALER_56  0x1CU
#define ECAP_EVENT_PRESCALER_58  0x1DU
#define ECAP_EVENT_PRESCALER_60  0x1EU
#define ECAP_EVENT_PRESCALER_62  0x1FU

#define IS_ECAP_EVENT_PRESCALER(PRESCALER) (((PRESCALER) == ECAP_EVENT_PRESCALER_1 ) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_2 ) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_4 ) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_6 ) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_8 ) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_10) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_12) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_14) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_16) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_18) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_20) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_22) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_24) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_26) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_28) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_30) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_32) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_34) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_36) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_38) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_40) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_42) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_44) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_46) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_48) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_50) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_52) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_54) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_56) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_58) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_60) || \
                                            ((PRESCALER) == ECAP_EVENT_PRESCALER_62) )
/**
  * @}
  */


///** @defgroup  ECAP_capture_load
//  * @{
//  */
//#define ECAP_CAPTURE_LOAD_DISABLE 0U
//#define ECAP_CAPTURE_LOAD_ENABLE  1U
//
//#define IS_ECAP_CAPTURE_LOAD(TYPE) (((TYPE) == ECAP_CAPTURE_LOAD_DISABLE) || ((TYPE) == ECAP_CAPTURE_LOAD_ENABLE))
//
///**
//  * @}
//  */


///** @defgroup  ECAP_counter_reset_event
//  * @{
//  */
//#define ECAP_COUNTER_RESET_DISABLE         0U
//#define ECAP_COUNTER_RESET_ENABLE          1U
//
//#define IS_ECAP_COUNTER_RESET(STATE) (((STATE) == ECAP_COUNTER_RESET_DISABLE) || \
//                                      ((STATE) == ECAP_COUNTER_RESET_ENABLE ))

/**
  * @}
  */


/** @defgroup  ECAP_event_polarity
  * @{
  */
#define ECAP_EVENT_POLARITY_RE  0U  //Capture event 4 triggered on a rising edge(RE)
#define ECAP_EVENT_POLARITY_FE  1U  //Capture event 4 triggered on a falling edge(FE)

#define IS_ECAP_EVENT_POLARITY(TYPE) (((TYPE) == ECAP_EVENT_POLARITY_RE) || ((TYPE) == ECAP_EVENT_POLARITY_FE))

/**
  * @}
  */


/** @defgroup  ECAP_apwm_output_polarity
  * @{
  */
#define ECAP_APWM_POLARITY_HIGH  0U
#define ECAP_APWM_POLARITY_LOW   ECAP_ECCTL2_APWMPOL

#define IS_ECAP_APWM_POLARITY(TYPE) (((TYPE) == ECAP_APWM_POLARITY_HIGH) || \
                                            ((TYPE) == ECAP_APWM_POLARITY_LOW ))

/**
  * @}
  */


///** @defgroup  ECAP_counter_syncin_select
//  * @{
//  */
//#define ECAP_COUNTER_SYNCIN_DISABLE  0U
//#define ECAP_COUNTER_SYNCIN_ENABLE   1U
//
//#define IS_ECAP_COUNTER_SYNCIN(STATE) (((STATE) == ECAP_COUNTER_SYNCIN_DISABLE) || \
//                                       ((STATE) == ECAP_COUNTER_SYNCIN_ENABLE ))

/**
  * @}
  */


/** @defgroup  ECAP_mod_counter_stop_wrap
  * @{
  */
#define ECAP_STOP_WRAP_EVENT1  0U
#define ECAP_STOP_WRAP_EVENT2  ECAP_ECCTL2_STOP_WRAP_0
#define ECAP_STOP_WRAP_EVENT3  ECAP_ECCTL2_STOP_WRAP_1
#define ECAP_STOP_WRAP_EVENT4  ECAP_ECCTL2_STOP_WRAP

#define IS_ECAP_MOD_COUNTER_STOP_WRAP(SEL) (((SEL) == ECAP_STOP_WRAP_EVENT1) || \
                                            ((SEL) == ECAP_STOP_WRAP_EVENT2) || \
                                            ((SEL) == ECAP_STOP_WRAP_EVENT3) || \
                                            ((SEL) == ECAP_STOP_WRAP_EVENT4) )

/**
  * @}
  */

/** @defgroup  ECAP_mod_counter_mode
  * @{
  */
#define ECAP_MOD_COUNTER_CONT    0U
#define ECAP_MOD_COUNTER_ONESHOT ECAP_ECCTL2_CONT_ONESHT

#define IS_ECAP_MOD_COUNTER_MODE(MODE) (((MODE) == ECAP_MOD_COUNTER_CONT) || ((MODE) == ECAP_MOD_COUNTER_ONESHOT))


/**
  * @}
  */

/** @defgroup  ECAP_counter_value
  * @{
  */
#define IS_ECAP_COUNTER_VALUE(VALUE) (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */

/** @defgroup  ECAP_counter_phase_value
  * @{
  */
#define IS_ECAP_COUNTER_PHASE_VALUE(VALUE) (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */

/** @defgroup  ECAP_capture1_register_value
  * @{
  */
#define IS_ECAP_CAPTURE1_REGISTER_VALUE(VALUE) (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */

/** @defgroup  ECAP_capture2_register_value
  * @{
  */
#define IS_ECAP_CAPTURE2_REGISTER_VALUE(VALUE) (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the ECAP configuration to the default reset state ******/
void ECAP_DeInit();

/* Initialization and Configuration functions *********************************/
void ECAP_Init(ECAP_InitTypeDef* ECAP_InitStruct);
void ECAP_StructInit(ECAP_InitTypeDef* ECAP_InitStruct);

/* ECAP control functions *********************************/
void ECAP_Cmd(FunctionalState NewState);
void ECAP_ReArm();
void ECAP_SoftwareForceSync();

/* Data register access function***********************************************/
uint32_t ECAP_GetDataRegister(uint8_t ECAP_DATA_REG);
void ECAP_WriteDataRegister(uint8_t ECAP_DATA_REG, uint32_t Value);

/* Interrupts and flags management functions **********************************/
void ECAP_ITConfig(uint8_t ECAP_IT, FunctionalState NewState);
void ECAP_ClearFlag(uint8_t ECAP_FLAG);
void ECAP_ITForce(uint8_t ECAP_IT);
ITStatus ECAP_GetITStatus(uint8_t ECAP_IT);
FlagStatus ECAP_GetFlagStatus(uint8_t ECAP_FLAG);


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_ECAP_H */


/************************ (C) COPYRIGHT FMD *****END OF FILE****/
