/**
  ******************************************************************************
  * @file         ft32f4xx_eqep.h
  * @author       FMD AE
  * @brief        This file contains all the functions prototypes for the eQEP firmware
  *               library.
  * @version      V1.0.0
  * @date         2025-04-17
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_EQEP_H
#define __FT32F4XX_EQEP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"


/** @addtogroup EQEP
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  EQEP quadrature decoder unit structures definition
  */
typedef struct
{
    uint32_t PosCounterSource;      /*!< Specifies position counter srource selection.
                                       This parameter can be a value of @ref EQEP_position_counter_source_select */

    FunctionalState SyncOutput;     /*!< Specifies whether synchronous output is enabled.
                                       This parameter can be a value of @ref EQEP_sync_output_select
                                       This parameter can be set to ENABLE or DISABLE. */

    uint32_t SyncOutputPin;         /*!< Specifies which pin is used for synchronous output.
                                       This parameter can be a value of @ref EQEP_sync_output_pin_select */

    uint32_t ExternalClockRate;     /*!< Specifies the external clock rate.
                                       This parameter can be a value of @ref EQEP_external_clock_rate_select */

    FunctionalState ClockDirSwap;   /*!< Specifies whether the quadrature clock inputs are swapped.
                                       This parameter can be a value of @ref EQEP_clock_dir_swap
                                       This parameter can be set to ENABLE or DISABLE. */

    FunctionalState IndexGate;      /*!< Specifies the index pulse gating option.
                                       This parameter can be a value of @ref EQEP_index_gate_option
                                       This parameter can be set to ENABLE or DISABLE. */

    uint32_t QEPAPolarity;          /*!< Specifies the input polarity of QEPA.
                                       This parameter can be a value of @ref EQEP_qepa_polarity */

    uint32_t QEPBPolarity;          /*!< Specifies the input polarity of QEPB.
                                       This parameter can be a value of @ref EQEP_qepb_polarity */

    uint32_t QEPIPolarity;          /*!< Specifies the input polarity of QEPI.
                                       This parameter can be a value of @ref EQEP_qepi_polarity */

    uint32_t QEPSPolarity;          /*!< Specifies the input polarity of QEPS.
                                       This parameter can be a value of @ref EQEP_qeps_polarity */

} EQEP_QDUInitTypeDef;


/**
  * @brief  EQEP position counter control structures definition
  */
typedef struct
{
    uint32_t PosCounterResetSrc;    /*!< Specifies the reset source for the position counter.
                                       This parameter can be a value of @ref EQEP_postion_counter_reset_source */

    uint32_t SEInitPosCounter;      /*!< Specifies the strobe event initialization of position counter.
                                       This parameter can be a value of @ref EQEP_strobe_event_init_position_counter */

    uint32_t IEInitPosCounter;      /*!< Specifies the index event initialization of position counter.
                                       This parameter can be a value of @ref EQEP_index_event_init_position_counter */

    //uint32_t SWInitPosCounter;      /*!< Specifies the software initialization of position counter.
    //                                     This parameter can be a value of @ref EQEP_software_init_position_counter */

    uint32_t SELatchPosCounter;     /*!< Specifies the strobe event latch of position counter.
                                       This parameter can be a value of @ref EQEP_strobe_event_latch_position_counter */

    uint32_t IELatchPosCounter;     /*!< Specifies the index event latch of position counter.
                                       This parameter can be a value of @ref EQEP_index_event_latch_position_counter */

    //uint32_t PosCounter;            /*!< Specifies the position counter enable or software reset.
    //                                     This parameter can be a value of @ref EQEP_position_counter_enable */

    uint32_t CaptureLatchMode;      /*!< Specifies the QEP capture latch mode.
                                       This parameter can be a value of @ref EQEP_capture_latch_mode */

    //uint32_t UnitTimer;             /*!< Specifies the QEP unit timer enable.
    //                                     This parameter can be a value of @ref EQEP_unit_timer_enable */

    //uint32_t WatchDog;              /*!< Specifies the QEP watchdog enable.
    //                                     This parameter can be a value of @ref EQEP_watchdog_enable */

    uint32_t PosCounterValue;      /*!< Specifies the value of the position counter.
                                      This parameter can be a value of @ref EQEP_position_counter_value */

    uint32_t PosCounterInitValue;  /*!< Specifies the initialization value of the position counter.
                                      The value is used to initialize the position counter based on external strobe or
                                      index event. The position counter can be initialized through software(QEPCTL.SWI).
                                      This parameter can be a value of @ref EQEP_position_counter_init_value */

    uint32_t PosCounterMaxValue;   /*!< Specifies the maximum value of the position counter.
                                      This parameter can be a value of @ref EQEP_position_counter_max_value */

    uint32_t PosCounterCmpValue;   /*!< Specifies the compare value of the position counter.
                                      The position compare value in this register is compared with the position
                                      counter(QPOSCNT) to generate sync output and/or interrupt on compare match.
                                      This parameter can be a value of @ref EQEP_position_counter_cmp_value */

    uint32_t UnitTimerPeriodValue; /*!< Specifies the period value of the unit timer.
                                      The period value for the unit timer to generate periodic unit time events.
                                      This parameter can be a value of @ref EQEP_unit_timer_period_value */

    uint32_t WdgTimerPeriodValue;  /*!< Specifies the period value of the watch dog timer.
                                      This parameter can be a value of @ref EQEP_wdg_timer_period_value */


} EQEP_InitTypeDef;


/**
  * @brief  EQEP capture control structures definition
  */
typedef struct
{
    //uint32_t Capture;               /*!< Specifies the QEP capture enable.
    //                                     This parameter can be a value of @ref EQEP_capture_enable */

    uint32_t CaptureClockPrescaler; /*!< Specifies the QEP capture timer clock prescaler.
                                       This parameter can be a value of @ref EQEP_capture_timer_clock_prescaler */

    uint32_t UnitPosEventPrescaler; /*!< Specifies the unit position event prescaler.
                                       This parameter can be a value of @ref EQEP_unit_position_event_prescaler */

    uint32_t CapturePeriodValue;    /*!< Specifies the period value of the capture timer.
                                       This parameter can be a value of @ref EQEP_capture_period_value */

} EQEP_CAPInitTypeDef;


/**
  * @brief  EQEP position compare structures definition
  */
typedef struct
{
    FunctionalState PosCompareShadow; /*!< Specifies the position compare of shadow enable.
                                         This parameter can be a value of @ref EQEP_position_compare_shadow_enable
                                         This parameter can be set to ENABLE or DISABLE. */

    uint32_t PosCompareShadowLoad;  /*!< Specifies the position compare of shadow load.
                                       This parameter can be a value of @ref EQEP_position_compare_shadow_load */

    uint32_t SyncOutPolarity;       /*!< Specifies the polarity of the position compare sync output.
                                       This parameter can be a value of @ref EQEP_sync_out_polarity */

    FunctionalState PosCompare;     /*!< Specifies the position compare enable.
                                       This parameter can be a value of @ref EQEP_position_compare_enable
                                       This parameter can be set to ENABLE or DISABLE. */

    uint32_t SyncOutPulseWidth;     /*!< Specifies the pulse width of the position compare sync output.
                                       This parameter can be a value of @ref EQEP_sync_out_pulse_width */

} EQEP_PosCmpInitTypeDef;





/** @defgroup  EQEP_position_counter_source_select
  * @{
  */
#define EQEP_POSCNTSRC_QUADRATURE_COUNT  0x00000000U
#define EQEP_POSCNTSRC_DIRECTION_COUNT   EQEP_QDECCTL_QSRC_0
#define EQEP_POSCNTSRC_UP_COUNT          EQEP_QDECCTL_QSRC_1
#define EQEP_POSCNTSRC_DOWN_COUNT        EQEP_QDECCTL_QSRC

#define IS_EQEP_POSCNTSRC_MODE(MODE) (((MODE) == EQEP_POSCNTSRC_QUADRATURE_COUNT) || \
                                      ((MODE) == EQEP_POSCNTSRC_DIRECTION_COUNT ) || \
                                      ((MODE) == EQEP_POSCNTSRC_UP_COUNT        ) || \
                                      ((MODE) == EQEP_POSCNTSRC_DOWN_COUNT      ) )

/**
  * @}
  */


///** @defgroup  EQEP_sync_output_select
//  * @{
//  */
//#define EQEP_SYNC_OUTPUT_DISABLE  0x00000000U
//#define EQEP_SYNC_OUTPUT_ENABLE   EQEP_QDECCTL_SOEN
//
//#define IS_EQEP_SYNC_OUTPUT_STATE(STATE) (((STATE) == EQEP_SYNC_OUTPUT_DISABLE) || \
//                                          ((STATE) == EQEP_SYNC_OUTPUT_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_sync_output_pin_select
  * @{
  */
#define EQEP_PIN_INDEX   0x00000000U
#define EQEP_PIN_STROBE  EQEP_QDECCTL_SPSEL

#define IS_EQEP_SYNC_OUTPUT_PIN(PIN) (((PIN) == EQEP_PIN_INDEX ) || \
                                      ((PIN) == EQEP_PIN_STROBE) )

/**
  * @}
  */


/** @defgroup  EQEP_external_clock_rate_select
  * @{
  */
#define EQEP_EXTERNAL_CLOCK_RATE_2x  0x00000000U
#define EQEP_EXTERNAL_CLOCK_RATE_1x  EQEP_QDECCTL_XCR

#define IS_EQEP_EXTERNAL_CLOCK_RATE(RATE) (((RATE) == EQEP_EXTERNAL_CLOCK_RATE_2x) || \
                                           ((RATE) == EQEP_EXTERNAL_CLOCK_RATE_1x) )

/**
  * @}
  */


///** @defgroup  EQEP_clock_dir_swap
//  * @{
//  */
//#define EQEP_CLOCK_DIR_SWAP_DISABLE  0x00000000U
//#define EQEP_CLOCK_DIR_SWAP_ENABLE   EQEP_QDECCTL_SWAP
//
//#define IS_EQEP_CLOCK_DIR_SWAP_STATE(STATE) (((STATE) == EQEP_CLOCK_DIR_SWAP_DISABLE) || \
//                                             ((STATE) == EQEP_CLOCK_DIR_SWAP_ENABLE ) )
//
///**
//  * @}
//  */


///** @defgroup  EQEP_index_gate_option
//  * @{
//  */
//#define EQEP_INDEX_GATE_DISABLE  0x00000000U
//#define EQEP_INDEX_GATE_ENABLE   EQEP_QDECCTL_IGATE
//
//#define IS_EQEP_INDEX_GATE_STATE(STATE) (((STATE) == EQEP_INDEX_GATE_DISABLE) || \
//                                         ((STATE) == EQEP_INDEX_GATE_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_qepa_polarity
  * @{
  */
#define EQEP_QEPA_INPUT_NO_EFFECT  0x00000000U
#define EQEP_QEPA_INPUT_NEGATE     EQEP_QDECCTL_QAP

#define IS_EQEP_QEPA_POLARITY(STATE) (((STATE) == EQEP_QEPA_INPUT_NO_EFFECT) || \
                                      ((STATE) == EQEP_QEPA_INPUT_NEGATE   ) )

/**
  * @}
  */


/** @defgroup  EQEP_qepb_polarity
  * @{
  */
#define EQEP_QEPB_INPUT_NO_EFFECT  0x00000000U
#define EQEP_QEPB_INPUT_NEGATE     EQEP_QDECCTL_QBP

#define IS_EQEP_QEPB_POLARITY(STATE) (((STATE) == EQEP_QEPB_INPUT_NO_EFFECT) || \
                                      ((STATE) == EQEP_QEPB_INPUT_NEGATE   ) )

/**
  * @}
  */


/** @defgroup  EQEP_qepi_polarity
  * @{
  */
#define EQEP_QEPI_INPUT_NO_EFFECT  0x00000000U
#define EQEP_QEPI_INPUT_NEGATE     EQEP_QDECCTL_QIP

#define IS_EQEP_QEPI_POLARITY(STATE) (((STATE) == EQEP_QEPI_INPUT_NO_EFFECT) || \
                                      ((STATE) == EQEP_QEPI_INPUT_NEGATE   ) )

/**
  * @}
  */


/** @defgroup  EQEP_qeps_polarity
  * @{
  */
#define EQEP_QEPS_INPUT_NO_EFFECT  0x00000000U
#define EQEP_QEPS_INPUT_NEGATE     EQEP_QDECCTL_QSP

#define IS_EQEP_QEPS_POLARITY(STATE) (((STATE) == EQEP_QEPS_INPUT_NO_EFFECT) || \
                                      ((STATE) == EQEP_QEPS_INPUT_NEGATE   ) )

/**
  * @}
  */








/** @defgroup  EQEP_postion_counter_reset_source
  * @{
  */
#define EQEP_RESET_SOURCE_INDEX  0x00000000U
#define EQEP_RESET_SOURCE_MAX    EQEP_QEPCTL_PCRM_0
#define EQEP_RESET_SOURCE_FIRST  EQEP_QEPCTL_PCRM_1
#define EQEP_RESET_SOURCE_UNIT   EQEP_QEPCTL_PCRM

#define IS_EQEP_RESET_SOURCE(SEL) (((SEL) == EQEP_RESET_SOURCE_INDEX) || \
                                   ((SEL) == EQEP_RESET_SOURCE_MAX  ) || \
                                   ((SEL) == EQEP_RESET_SOURCE_FIRST) || \
                                   ((SEL) == EQEP_RESET_SOURCE_UNIT ) )

/**
  * @}
  */


/** @defgroup  EQEP_strobe_event_init_position_counter
  * @{
  */
#define EQEP_SE_INIT_DISABLE      0x00000000U
#define EQEP_SE_INIT_RISING_EDGE  EQEP_QEPCTL_SEI_1
#define EQEP_SE_INIT_DOUBLE_EDGE  EQEP_QEPCTL_SEI

#define IS_EQEP_SE_INIT(MODE) (((MODE) == EQEP_SE_INIT_DISABLE    ) || \
                               ((MODE) == EQEP_SE_INIT_RISING_EDGE) || \
                               ((MODE) == EQEP_SE_INIT_DOUBLE_EDGE) )

/**
  * @}
  */


/** @defgroup  EQEP_index_event_init_position_counter
  * @{
  */
#define EQEP_IE_INIT_DISABLE      0x00000000U
#define EQEP_IE_INIT_RISING_EDGE  EQEP_QEPCTL_IEI_1
#define EQEP_IE_INIT_DOUBLE_EDGE  EQEP_QEPCTL_IEI

#define IS_EQEP_IE_INIT(MODE) (((MODE) == EQEP_IE_INIT_DISABLE    ) || \
                               ((MODE) == EQEP_IE_INIT_RISING_EDGE) || \
                               ((MODE) == EQEP_IE_INIT_DOUBLE_EDGE) )

/**
  * @}
  */


///** @defgroup  EQEP_software_init_position_counter
//  * @{
//  */
//#define EQEP_SW_INIT_DISABLE  0x00000000U
//#define EQEP_SW_INIT_ENABLE   EQEP_QEPCTL_SWI
//
//#define IS_EQEP_SW_INIT(MODE) (((MODE) == EQEP_SW_INIT_DISABLE) || \
//                               ((MODE) == EQEP_SW_INIT_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_strobe_event_latch_position_counter
  * @{
  */
#define EQEP_SE_LATCH_RISING_EDGE  0x00000000U
#define EQEP_SE_LATCH_DOUBLE_EDGE  EQEP_QEPCTL_SEL

#define IS_EQEP_SE_LATCH(MODE) (((MODE) == EQEP_SE_LATCH_RISING_EDGE) || \
                                ((MODE) == EQEP_SE_LATCH_DOUBLE_EDGE) )

/**
  * @}
  */


/** @defgroup  EQEP_index_event_latch_position_counter
  * @{
  */
#define EQEP_IE_LATCH_DISABLE         0x00000000U
#define EQEP_IE_LATCH_RISING_EDGE     EQEP_QEPCTL_IEL_0
#define EQEP_IE_LATCH_FALLING_EDGE    EQEP_QEPCTL_IEL_1
#define EQEP_IE_LATCH_SOFTWAREMARKER  EQEP_QEPCTL_IEL

#define IS_EQEP_IE_LATCH(MODE) (((MODE) == EQEP_IE_LATCH_DISABLE       ) || \
                                ((MODE) == EQEP_IE_LATCH_RISING_EDGE   ) || \
                                ((MODE) == EQEP_IE_LATCH_FALLING_EDGE  ) || \
                                ((MODE) == EQEP_IE_LATCH_SOFTWAREMARKER) )

/**
  * @}
  */


///** @defgroup  EQEP_position_counter_enable
//  * @{
//  */
//#define EQEP_POSCOUNTER_DISABLE  0x00000000U
//#define EQEP_POSCOUNTER_ENABLE   EQEP_QEPCTL_QPEN
//
//#define IS_EQEP_POSCOUNTER(STATE) (((STATE) == EQEP_POSCOUNTER_DISABLE) || \
//                                   ((STATE) == EQEP_POSCOUNTER_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_capture_latch_mode
  * @{
  */
#define EQEP_CAPTURELATCH_CPU      0x00000000U
#define EQEP_CAPTURELATCH_TIMEOUT  EQEP_QEPCTL_QCLM

#define IS_EQEP_CAPTURELATCH_MODE(MODE) (((MODE) == EQEP_CAPTURELATCH_CPU    ) || \
                                         ((MODE) == EQEP_CAPTURELATCH_TIMEOUT) )

/**
  * @}
  */


/** @defgroup  EQEP_position_counter_value
  * @{
  */
#define IS_EQEP_POS_COUNTER_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */


/** @defgroup  EQEP_position_counter_init_value
  * @{
  */
#define IS_EQEP_POS_COUNTER_INIT_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */


/** @defgroup  EQEP_position_counter_max_value
  * @{
  */
#define IS_EQEP_POS_COUNTER_MAX_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */


/** @defgroup  EQEP_position_counter_cmp_value
  * @{
  */
#define IS_EQEP_POS_COUNTER_CMP_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */


/** @defgroup  EQEP_unit_timer_period_value
  * @{
  */
#define IS_EQEP_UNIT_TIMER_PERIOD_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFFFFFU))

/**
  * @}
  */


/** @defgroup  EQEP_wdg_timer_period_value
  * @{
  */
#define IS_EQEP_WDG_TIMER_PERIOD_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFU))

/**
  * @}
  */





///** @defgroup  EQEP_unit_timer_enable
//  * @{
//  */
//#define EQEP_UNITTIMER_DISABLE  0x00000000U
//#define EQEP_UNITTIMER_ENABLE   EQEP_QEPCTL_UTE
//
//#define IS_EQEP_UNITTIMER(STATE) (((STATE) == EQEP_UNITTIMER_DISABLE) || \
//                                  ((STATE) == EQEP_UNITTIMER_ENABLE ) )
//
///**
//  * @}
//  */
//
//
///** @defgroup  EQEP_watchdog_enable
//  * @{
//  */
//#define EQEP_WATCHDOG_DISABLE  0x00000000U
//#define EQEP_WATCHDOG_ENABLE   EQEP_QEPCTL_WDE
//
//#define IS_EQEP_WATCHDOG(STATE) (((STATE) == EQEP_WATCHDOG_DISABLE) || \
//                                 ((STATE) == EQEP_WATCHDOG_ENABLE ) )
//
///**
//  * @}
//  */






///** @defgroup  EQEP_capture_enable
//  * @{
//  */
//#define EQEP_CAPTURE_DISABLE  0x00000000U
//#define EQEP_CAPTURE_ENABLE   EQEP_QCAPCTL_CEN
//
//#define IS_EQEP_CAPTURE(STATE) (((STATE) == EQEP_CAPTURE_DISABLE) || \
//                                ((STATE) == EQEP_CAPTURE_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_capture_timer_clock_prescaler
  * @{
  */
#define EQEP_CLOCKPRESCALER_1    0x00000000U
#define EQEP_CLOCKPRESCALER_2    EQEP_QCAPCTL_CCPS_0
#define EQEP_CLOCKPRESCALER_4    EQEP_QCAPCTL_CCPS_1
#define EQEP_CLOCKPRESCALER_8   (EQEP_QCAPCTL_CCPS_0 | EQEP_QCAPCTL_CCPS_1)
#define EQEP_CLOCKPRESCALER_16   EQEP_QCAPCTL_CCPS_2
#define EQEP_CLOCKPRESCALER_32  (EQEP_QCAPCTL_CCPS_0 | EQEP_QCAPCTL_CCPS_2)
#define EQEP_CLOCKPRESCALER_64  (EQEP_QCAPCTL_CCPS_1 | EQEP_QCAPCTL_CCPS_2)
#define EQEP_CLOCKPRESCALER_128  EQEP_QCAPCTL_CCPS

#define IS_EQEP_CLOCKPRESCALER(PRE) (((PRE) == EQEP_CLOCKPRESCALER_1  ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_2  ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_4  ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_8  ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_16 ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_32 ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_64 ) || \
                                     ((PRE) == EQEP_CLOCKPRESCALER_128) )

/**
  * @}
  */


/** @defgroup  EQEP_unit_position_event_prescaler
  * @{
  */
#define EQEP_EVENTPRESCALER_1    0x00000000U
#define EQEP_EVENTPRESCALER_2    0x00000001U
#define EQEP_EVENTPRESCALER_4    0x00000002U
#define EQEP_EVENTPRESCALER_8    0x00000003U
#define EQEP_EVENTPRESCALER_16   0x00000004U
#define EQEP_EVENTPRESCALER_32   0x00000005U
#define EQEP_EVENTPRESCALER_64   0x00000006U
#define EQEP_EVENTPRESCALER_128  0x00000007U
#define EQEP_EVENTPRESCALER_256  0x00000008U
#define EQEP_EVENTPRESCALER_512  0x00000009U
#define EQEP_EVENTPRESCALER_1024 0x0000000AU
#define EQEP_EVENTPRESCALER_2048 0x0000000BU

#define IS_EQEP_EVENTPRESCALER(PRE) (((PRE) == EQEP_EVENTPRESCALER_1   ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_2   ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_4   ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_8   ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_16  ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_32  ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_64  ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_128 ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_256 ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_512 ) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_1024) || \
                                     ((PRE) == EQEP_EVENTPRESCALER_2048) )

/**
  * @}
  */


/** @defgroup  EQEP_capture_period_value
  * @{
  */
#define IS_EQEP_CAPTURE_PERIOD_VALUE(VALUE)  (((VALUE) >= 0x0U) && ((VALUE) <= 0xFFFFU))

/**
  * @}
  */



///** @defgroup  EQEP_position_compare_shadow_enable
//  * @{
//  */
//#define EQEP_POSCMP_SHADOW_DISABLE  0x00000000U
//#define EQEP_POSCMP_SHADOW_ENABLE   EQEP_QPOSCTL_PCSHDW
//
//#define IS_EQEP_POSCMP_SHADOW(STATE) (((STATE) == EQEP_POSCMP_SHADOW_DISABLE) || \
//                                      ((STATE) == EQEP_POSCMP_SHADOW_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_position_compare_shadow_load
  * @{
  */
#define EQEP_POSCMP_LOAD_CNTZERO  0x00000000U
#define EQEP_POSCMP_LOAD_CNTCMP   EQEP_QPOSCTL_PCLOAD

#define IS_EQEP_POSCMP_LOAD(STATE) (((STATE) == EQEP_POSCMP_LOAD_CNTZERO) || \
                                    ((STATE) == EQEP_POSCMP_LOAD_CNTCMP ) )

/**
  * @}
  */


/** @defgroup  EQEP_sync_out_polarity
  * @{
  */
#define EQEP_SYNCOUT_POLARITY_HIGH  0x00000000U
#define EQEP_SYNCOUT_POLARITY_LOW   EQEP_QPOSCTL_PCPOL

#define IS_EQEP_SYNCOUT_POLARITY(POLARITY) (((POLARITY) == EQEP_SYNCOUT_POLARITY_HIGH) || \
                                            ((POLARITY) == EQEP_SYNCOUT_POLARITY_LOW ) )

/**
  * @}
  */


///** @defgroup  EQEP_position_compare_enable
//  * @{
//  */
//#define EQEP_POSCOMPARE_DISABLE  0x00000000U
//#define EQEP_POSCOMPARE_ENABLE   EQEP_QPOSCTL_PCMPE
//
//#define IS_EQEP_POSCOMPARE(STATE) (((STATE) == EQEP_POSCOMPARE_DISABLE) || \
//                                   ((STATE) == EQEP_POSCOMPARE_ENABLE ) )
//
///**
//  * @}
//  */


/** @defgroup  EQEP_sync_out_pulse_width
  * @{
  */
#define IS_EQEP_SYNCOUT_PULSE_WIDTH(WIDTH) (((WIDTH) >= 0x0U) && ((WIDTH) <= 0xFFFU))

/**
  * @}
  */



/** @defgroup EQEP_interrupt_definition EQEP_IT
  * @{
  */
#define EQEP_IT_PCE         EQEP_QEINT_PCE
#define EQEP_IT_PHE         EQEP_QEINT_PHE
#define EQEP_IT_QDC         EQEP_QEINT_QDC
#define EQEP_IT_WTO         EQEP_QEINT_WTO
#define EQEP_IT_PCU         EQEP_QEINT_PCU
#define EQEP_IT_PCO         EQEP_QEINT_PCO
#define EQEP_IT_PCR         EQEP_QEINT_PCR
#define EQEP_IT_PCM         EQEP_QEINT_PCM
#define EQEP_IT_SEL         EQEP_QEINT_SEL
#define EQEP_IT_IEL         EQEP_QEINT_IEL
#define EQEP_IT_UTO         EQEP_QEINT_UTO

#define IS_EQEP_IT(TYPE) (((TYPE) == EQEP_IT_PCE) || \
                          ((TYPE) == EQEP_IT_PHE) || \
                          ((TYPE) == EQEP_IT_QDC) || \
                          ((TYPE) == EQEP_IT_WTO) || \
                          ((TYPE) == EQEP_IT_PCU) || \
                          ((TYPE) == EQEP_IT_PCO) || \
                          ((TYPE) == EQEP_IT_PCR) || \
                          ((TYPE) == EQEP_IT_PCM) || \
                          ((TYPE) == EQEP_IT_SEL) || \
                          ((TYPE) == EQEP_IT_IEL) || \
                          ((TYPE) == EQEP_IT_UTO) )
/**
  * @}
  */



/** @defgroup EQEP_flags_definition EQEP_FLAG
  * @{
  */
#define EQEP_FLAG_INT         EQEP_QFLG_INT
#define EQEP_FLAG_PCE         EQEP_QFLG_PCE
#define EQEP_FLAG_PHE         EQEP_QFLG_PHE
#define EQEP_FLAG_QDC         EQEP_QFLG_QDC
#define EQEP_FLAG_WTO         EQEP_QFLG_WTO
#define EQEP_FLAG_PCU         EQEP_QFLG_PCU
#define EQEP_FLAG_PCO         EQEP_QFLG_PCO
#define EQEP_FLAG_PCR         EQEP_QFLG_PCR
#define EQEP_FLAG_PCM         EQEP_QFLG_PCM
#define EQEP_FLAG_SEL         EQEP_QFLG_SEL
#define EQEP_FLAG_IEL         EQEP_QFLG_IEL
#define EQEP_FLAG_UTO         EQEP_QFLG_UTO

#define IS_EQEP_FLAG(TYPE) (((TYPE) == EQEP_FLAG_INT   ) || \
                            ((TYPE) == EQEP_FLAG_PCE) || \
                            ((TYPE) == EQEP_FLAG_PHE) || \
                            ((TYPE) == EQEP_FLAG_QDC) || \
                            ((TYPE) == EQEP_FLAG_WTO) || \
                            ((TYPE) == EQEP_FLAG_PCU) || \
                            ((TYPE) == EQEP_FLAG_PCO) || \
                            ((TYPE) == EQEP_FLAG_PCR) || \
                            ((TYPE) == EQEP_FLAG_PCM) || \
                            ((TYPE) == EQEP_FLAG_SEL) || \
                            ((TYPE) == EQEP_FLAG_IEL) || \
                            ((TYPE) == EQEP_FLAG_UTO) )

#define EQEP_IT_MASK    0x00000FFFU
/**
  * @}
  */


/** @defgroup EQEP_status_definition EQEP_STATUS
  * @{
  */
#define EQEP_STATUS_UPEVNT  EQEP_QEPSTS_UPEVNT
#define EQEP_STATUS_FIDF    EQEP_QEPSTS_FIDF
#define EQEP_STATUS_QDF     EQEP_QEPSTS_QDF
#define EQEP_STATUS_QDLF    EQEP_QEPSTS_QDLF
#define EQEP_STATUS_COEF    EQEP_QEPSTS_COEF
#define EQEP_STATUS_CDEF    EQEP_QEPSTS_CDEF
#define EQEP_STATUS_FIMF    EQEP_QEPSTS_FIMF
#define EQEP_STATUS_PCEF    EQEP_QEPSTS_PCEF

#define IS_EQEP_STATUS(STATUS) (((STATUS) == EQEP_STATUS_UPEVNT) || \
                                ((STATUS) == EQEP_STATUS_FIDF  ) || \
                                ((STATUS) == EQEP_STATUS_QDF   ) || \
                                ((STATUS) == EQEP_STATUS_QDLF  ) || \
                                ((STATUS) == EQEP_STATUS_COEF  ) || \
                                ((STATUS) == EQEP_STATUS_CDEF  ) || \
                                ((STATUS) == EQEP_STATUS_FIMF  ) || \
                                ((STATUS) == EQEP_STATUS_PCEF  ) )
/**
  * @}
  */


/**
  * @brief  EQEP_register_type_definition EQEP_REG_TYPE
  */
#define  EQEP_QPOSCNT   ((uint16_t)0x0001U)
#define  EQEP_QUTMR     ((uint16_t)0x0002U)
#define  EQEP_QWDTMR    ((uint16_t)0x0004U)
#define  EQEP_QCTMR     ((uint16_t)0x0008U)
#define  EQEP_QPOSINIT  ((uint16_t)0x0010U)
#define  EQEP_QPOSMAX   ((uint16_t)0x0020U)
#define  EQEP_QPOSCMP   ((uint16_t)0x0040U)
#define  EQEP_QPOSILAT  ((uint16_t)0x0080U)
#define  EQEP_QPOSSLAT  ((uint16_t)0x0100U)
#define  EQEP_QPOSLAT   ((uint16_t)0x0200U)
#define  EQEP_QUPRD     ((uint16_t)0x0400U)
#define  EQEP_QWDPRD    ((uint16_t)0x0800U)
#define  EQEP_QCPRD     ((uint16_t)0x1000U)
#define  EQEP_QCTMRLAT  ((uint16_t)0x2000U)
#define  EQEP_QCPRDLAT  ((uint16_t)0x4000U)

#define IS_EQEP_REG_TYPE(TYPE) (((TYPE) == EQEP_QPOSCNT  ) || \
                                ((TYPE) == EQEP_QUTMR    ) || \
                                ((TYPE) == EQEP_QWDTMR   ) || \
                                ((TYPE) == EQEP_QCTMR    ) || \
                                ((TYPE) == EQEP_QPOSINIT ) || \
                                ((TYPE) == EQEP_QPOSMAX  ) || \
                                ((TYPE) == EQEP_QPOSCMP  ) || \
                                ((TYPE) == EQEP_QPOSILAT ) || \
                                ((TYPE) == EQEP_QPOSSLAT ) || \
                                ((TYPE) == EQEP_QPOSLAT  ) || \
                                ((TYPE) == EQEP_QUPRD    ) || \
                                ((TYPE) == EQEP_QWDPRD   ) || \
                                ((TYPE) == EQEP_QCPRD    ) || \
                                ((TYPE) == EQEP_QCTMRLAT ) || \
                                ((TYPE) == EQEP_QCPRDLAT ))


/**
  * @brief  EQEP_submodule_definition EQEP_SUBMDU_TYPE
  */
#define  EQEP_POS_CNT   ((uint8_t)0x01U)
#define  EQEP_UNIT_TMR  ((uint8_t)0x02U)
#define  EQEP_WTD_TMR   ((uint8_t)0x04U)
#define  EQEP_CAP_TMR   ((uint8_t)0x08U)

#define IS_EQEP_SUBMDU_TYPE(TYPE) (((TYPE) == EQEP_POS_CNT ) || \
                                   ((TYPE) == EQEP_UNIT_TMR) || \
                                   ((TYPE) == EQEP_WTD_TMR ) || \
                                   ((TYPE) == EQEP_CAP_TMR ))




/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the EQEP configuration to the default reset state ******/
void EQEP_DeInit();

/* Initialization and Configuration functions *********************************/
void EQEP_Init(EQEP_InitTypeDef* EQEP_InitStruct);
void EQEP_QDUInit(EQEP_QDUInitTypeDef* EQEP_QDUInitStruct);
void EQEP_CAPInit(EQEP_CAPInitTypeDef* EQEP_CAPInitStruct);
void EQEP_POSCMPInit(EQEP_PosCmpInitTypeDef* EQEP_PosCmpInitStruct);

void EQEP_StructInit(EQEP_InitTypeDef* EQEP_InitStruct);
void EQEP_QDUStructInit(EQEP_QDUInitTypeDef* EQEP_QDUInitStruct);
void EQEP_CAPStructInit(EQEP_CAPInitTypeDef* EQEP_CAPInitStruct);
void EQEP_POSCMPStructInit(EQEP_PosCmpInitTypeDef* EQEP_PosCmpInitStruct);

/* EQEP control functions *********************************/
void EQEP_Cmd(uint16_t EQEP_REG_TYPE, FunctionalState NewState);           //QEPCTL.QPEN
//void EQEP_UnitTimerCmd(FunctionalState NewState);  //QEPCTL.UTE
//void EQEP_WdgTimerCmd(FunctionalState NewState);   //QEPCTL.WDE
//void EQEP_CaptureCmd(FunctionalState NewState);    //QCAPCTL.CEN
////void EQEP_PosCmpCmd(FunctionalState NewState);     //QPOSCTL.PCMPE
void EQEP_SoftwareInitPositionCounter(FunctionalState NewState);           //QEPCTL.SWI

/* Data register access function***********************************************/
void EQEP_WriteDataRegister(uint16_t EQEP_REG_TYPE, uint32_t Value);
uint32_t EQEP_GetDataRegister(uint16_t EQEP_REG_TYPE);

/* Interrupts and flags management functions **********************************/
void EQEP_ITConfig(uint16_t EQEP_IT, FunctionalState NewState);
void EQEP_ClearFlag(uint16_t EQEP_FLAG);
void EQEP_ITForce(uint16_t EQEP_IT);
ITStatus EQEP_GetITStatus(uint16_t EQEP_IT);
FlagStatus EQEP_GetFlagStatus(uint16_t EQEP_FLAG);
FlagStatus EQEP_GetStatus(uint8_t EQEP_STATUS);


/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /*__FT32F4XX_EQEP_H */


/************************ (C) COPYRIGHT FMD *****END OF FILE****/
