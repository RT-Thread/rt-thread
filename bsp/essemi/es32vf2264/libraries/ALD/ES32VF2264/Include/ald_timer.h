/**
  *********************************************************************************
  *
  * @file    ald_timer.h
  * @brief   TIMER module driver.
  *          This is the common part of the TIMER initialization
  *
  * @version V1.0
  * @date    03 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          03 Mar. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#ifndef __ALD_TIMER_H__
#define __ALD_TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"
#include "ald_cmu.h"
#include "ald_dma.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/** @defgroup TIMER_Public_Types TIMER Public Types
  * @{
  */

/**
  * @brief TIMER counter mode
  */
typedef enum {
    ALD_TIMER_CNT_MODE_UP      = 0U,    /**< Counter mode up */
    ALD_TIMER_CNT_MODE_DOWN    = 1U,    /**< Counter mode down */
    ALD_TIMER_CNT_MODE_CENTER1 = 2U,    /**< Counter mode center1 */
    ALD_TIMER_CNT_MODE_CENTER2 = 3U,    /**< Counter mode center2 */
    ALD_TIMER_CNT_MODE_CENTER3 = 4U,    /**< Counter mode center3 */
} ald_timer_cnt_mode_t;

/**
  * @brief TIMER clock division
  */
typedef enum {
    ALD_TIMER_CLOCK_DIV1 = 0U,  /**< No prescaler is used */
    ALD_TIMER_CLOCK_DIV2 = 1U,  /** Clock is divided by 2 */
    ALD_TIMER_CLOCK_DIV4 = 2U,  /** Clock is divided by 4 */
} ald_timer_clock_division_t;

/**
  * @brief TIMER output compare and PWM modes
  */
typedef enum {
    ALD_TIMER_OC_MODE_TIMERING       = 0U,  /**< Output compare mode is timering */
    ALD_TIMER_OC_MODE_ACTIVE         = 1U,  /**< Output compare mode is active */
    ALD_TIMER_OC_MODE_INACTIVE       = 2U,  /**< Output compare mode is inactive */
    ALD_TIMER_OC_MODE_TOGGLE         = 3U,  /**< Output compare mode is toggle */
    ALD_TIMER_OC_MODE_FORCE_INACTIVE = 4U,  /**< Output compare mode is force inactive */
    ALD_TIMER_OC_MODE_FORCE_ACTIVE   = 5U,  /**< Output compare mode is force active */
    ALD_TIMER_OC_MODE_PWM1           = 6U,  /**< Output compare mode is pwm1 */
    ALD_TIMER_OC_MODE_PWM2           = 7U,  /**< Output compare mode is pwm2 */
} ald_timer_oc_mode_t;

/**
  * @brief TIMER output compare polarity
  */
typedef enum {
    ALD_TIMER_OC_POLARITY_HIGH = 0U,    /**< Output compare polarity is high */
    ALD_TIMER_OC_POLARITY_LOW  = 1U,    /**< Output compare polarity is low */
} ald_timer_oc_polarity_t;

/**
  * @brief TIMER complementary output compare polarity
  */
typedef enum {
    ALD_TIMER_OCN_POLARITY_HIGH = 0U,   /**< Complementary output compare polarity is high */
    ALD_TIMER_OCN_POLARITY_LOW  = 1U,   /**< Complementary output compare polarity is low */
} ald_timer_ocn_polarity_t;

/**
  * @brief TIMER output compare idle state
  */
typedef enum {
    ALD_TIMER_OC_IDLE_RESET = 0U,   /**< Output compare idle state is reset */
    ALD_TIMER_OC_IDLE_SET   = 1U,   /**< Output compare idle state is set */
} ald_timer_oc_idle_t;

/**
  * @brief TIMER complementary output compare idle state
  */
typedef enum {
    ALD_TIMER_OCN_IDLE_RESET = 0U,  /**< Complementary output compare idle state is reset */
    ALD_TIMER_OCN_IDLE_SET   = 1U,  /**< Complementary output compare idle state is set */
} ald_timer_ocn_idle_t;

/**
  * @brief TIMER channel
  */
typedef enum {
    ALD_TIMER_CHANNEL_1   = 0U,     /**< Channel 1 */
    ALD_TIMER_CHANNEL_2   = 1U,     /**< Channel 2 */
    ALD_TIMER_CHANNEL_3   = 2U,     /**< Channel 3 */
    ALD_TIMER_CHANNEL_4   = 3U,     /**< Channel 4 */
    ALD_TIMER_CHANNEL_ALL = 0xFU,   /**< All channel */
} ald_timer_channel_t;

/**
  * @brief TIMER one pulse mode
  */
typedef enum {
    ALD_TIMER_OP_MODE_REPEAT = 0U,  /**< Repetitive */
    ALD_TIMER_OP_MODE_SINGLE = 1U,  /**< single */
} ald_timer_op_mode_t;

/**
  * @brief TIMER one pulse output channel
  */
typedef enum {
    ALD_TIMER_OP_OUTPUT_CHANNEL_1 = 0U, /**< One pulse output channal 1 */
    ALD_TIMER_OP_OUTPUT_CHANNEL_2 = 1U, /**< One pulse output channal 2 */
} ald_timer_op_output_channel_t;

/**
  * @brief  TIMER time base configuration structure definition
  */
typedef struct {
    uint32_t prescaler;     /**< Specifies the prescaler value used to divide the TIMER clock. */
    ald_timer_cnt_mode_t mode;      /**< Specifies the counter mode. */
    uint32_t period;        /**< Specifies the period value to be loaded into ARR at the next update event. */
    ald_timer_clock_division_t clk_div; /**< Specifies the clock division.*/
    uint32_t re_cnt;        /**< Specifies the repetition counter value. */
} ald_timer_base_init_t;

/**
  * @brief  TIMER output compare configuration structure definition
  */
typedef struct {
    ald_timer_oc_mode_t oc_mode;        /**< Specifies the TIMER mode. */
    uint32_t pulse;             /**< Specifies the pulse value to be loaded into the Capture Compare Register. */
    ald_timer_oc_polarity_t oc_polarity;    /**< Specifies the output polarity. */
    ald_timer_ocn_polarity_t ocn_polarity;  /**< Specifies the complementary output polarity. */
    type_func_t oc_fast_en;         /**< Specifies the Fast mode state. */
    ald_timer_oc_idle_t oc_idle;        /**< Specifies the TIMER Output Compare pin state during Idle state. */
    ald_timer_ocn_idle_t ocn_idle;      /**< Specifies the TIMER Output Compare pin state during Idle state. */
} ald_timer_oc_init_t;

/**
  * @brief State structures definition
  */
typedef enum {
    ALD_TIMER_STATE_RESET     = 0x00U,  /**< Peripheral not yet initialized or disabled */
    ALD_TIMER_STATE_READY     = 0x01U,  /**< Peripheral Initialized and ready for use */
    ALD_TIMER_STATE_BUSY      = 0x02U,  /**< An internal process is ongoing */
    ALD_TIMER_STATE_TIMEREOUT = 0x03U,  /**< Timeout state */
    ALD_TIMER_STATE_ERROR     = 0x04U,  /**< Reception process is ongoing */
} ald_timer_state_t;

/**
  * @brief Active channel structures definition
  */
typedef enum {
    ALD_TIMER_ACTIVE_CHANNEL_1       = 0x01U,   /**< The active channel is 1 */
    ALD_TIMER_ACTIVE_CHANNEL_2       = 0x02U,   /**< The active channel is 2 */
    ALD_TIMER_ACTIVE_CHANNEL_3       = 0x04U,   /**< The active channel is 3 */
    ALD_TIMER_ACTIVE_CHANNEL_4       = 0x08U,   /**< The active channel is 4 */
    ALD_TIMER_ACTIVE_CHANNEL_CLEARED = 0x00U,   /**< All active channels cleared */
} ald_timer_active_channel_t;

/**
  * @brief  TIMER time base handle structure definition
  */
typedef struct ald_timer_handle_s {
    TIMER_TypeDef *perh;        /**< Register base address */
    ald_timer_base_init_t init;     /**< TIMER Time Base required parameters */
    ald_timer_active_channel_t ch;  /**< Active channel */
    lock_state_t lock;      /**< Locking object */
    ald_timer_state_t state;        /**< TIMER operation state */

    ald_dma_handle_t hdma1;              /**< Timer DMA handle parameters */
    ald_dma_handle_t hdma2;

    void (*period_elapse_cbk)(struct ald_timer_handle_s *arg);      /**< Period elapse callback */
    void (*delay_elapse_cbk)(struct ald_timer_handle_s *arg);       /**< Delay_elapse callback */
    void (*capture_cbk)(struct ald_timer_handle_s *arg);        /**< Capture callback */
    void (*pwm_pulse_finish_cbk)(struct ald_timer_handle_s *arg);   /**< PWM_pulse_finish callback */
    void (*trigger_cbk)(struct ald_timer_handle_s *arg);        /**< Trigger callback */
    void (*break_cbk)(struct ald_timer_handle_s *arg);          /**< Break callback */
    void (*com_cbk)(struct ald_timer_handle_s *arg);            /**< commutation callback */
    void (*error_cbk)(struct ald_timer_handle_s *arg);          /**< Error callback */
} ald_timer_handle_t;


/**
  * @brief TIMER encoder mode
  */
typedef enum {
    ALD_TIMER_ENC_MODE_TI1  = 1U,   /**< encoder mode 1 */
    ALD_TIMER_ENC_MODE_TI2  = 2U,   /**< encoder mode 2 */
    ALD_TIMER_ENC_MODE_TI12 = 3U,   /**< encoder mode 3 */
} ald_timer_encoder_mode_t;

/**
  * @brief TIMER input capture polarity
  */
typedef enum {
    ALD_TIMER_IC_POLARITY_RISE = 0U,    /**< Input capture polarity rising */
    ALD_TIMER_IC_POLARITY_FALL = 1U,    /**< Input capture polarity falling */
} ald_timer_ic_polarity_t;

/**
  *@brief TIMER input capture selection
  */
typedef enum {
    ALD_TIMER_IC_SEL_DIRECT   = 1U, /**< IC1 -- TI1 */
    ALD_TIMER_IC_SEL_INDIRECT = 2U, /**< IC1 -- TI2 */
    ALD_TIMER_IC_SEL_TRC      = 3U, /**< IC1 -- TRC */
} ald_timer_ic_select_t;

/**
  * @brief TIMER input capture prescaler
  */
typedef enum {
    ALD_TIMER_IC_PSC_DIV1 = 0U, /**< Capture performed once every 1 events */
    ALD_TIMER_IC_PSC_DIV2 = 1U, /**< Capture performed once every 2 events */
    ALD_TIMER_IC_PSC_DIV4 = 2U, /**< Capture performed once every 4 events */
    ALD_TIMER_IC_PSC_DIV8 = 3U, /**< Capture performed once every 4 events */
} ald_timer_ic_prescaler_t;

/**
  * @brief TIMER encoder configuration structure definition
  */
typedef struct {
    ald_timer_encoder_mode_t mode;      /**< Specifies the encoder mode */
    ald_timer_ic_polarity_t ic1_polarity;   /**< Specifies the active edge of the input signal */
    ald_timer_ic_select_t ic1_sel;      /**< Specifies the input */
    ald_timer_ic_prescaler_t ic1_psc;       /**< Specifies the Input Capture Prescaler */
    uint32_t ic1_filter;            /**< Specifies the input capture filter */
    ald_timer_ic_polarity_t ic2_polarity;   /**< Specifies the active edge of the input signal */
    ald_timer_ic_select_t ic2_sel;      /**< Specifies the input */
    ald_timer_ic_prescaler_t ic2_psc;       /**< Specifies the Input Capture Prescaler */
    uint32_t ic2_filter;            /**< Specifies the input capture filter */
} ald_timer_encoder_init_t;

/**
  * @brief  TIMER input capture configuration structure definition
  */
typedef struct {
    ald_timer_ic_polarity_t polarity;   /**< Specifies the active edge of the input signal */
    ald_timer_ic_select_t sel;      /**< Specifies the input */
    ald_timer_ic_prescaler_t psc;   /**< Specifies the Input Capture Prescaler */
    uint32_t filter;        /**< Specifies the input capture filter */
} ald_timer_ic_init_t;

/**
  * @brief  TIMER one pulse mode configuration structure definition
  */
typedef struct {
    ald_timer_oc_mode_t mode;           /**< Specifies the TIMER mode */
    uint16_t pulse;             /**< Specifies the pulse value */
    ald_timer_oc_polarity_t oc_polarity;    /**< Specifies the output polarity */
    ald_timer_ocn_polarity_t ocn_polarity;  /**< Specifies the complementary output polarity */
    ald_timer_oc_idle_t oc_idle;        /**< Specifies the TIMER Output Compare pin state during Idle state */
    ald_timer_ocn_idle_t ocn_idle;      /**< Specifies the TIMER Output Compare pin state during Idle state */
    ald_timer_ic_polarity_t polarity;       /**< Specifies the active edge of the input signal */
    ald_timer_ic_select_t sel;          /**< Specifies the input */
    uint32_t filter;            /**< Specifies the input capture filter */
} ald_timer_one_pulse_init_t;

/** @brief TIMER clear input source
  */
typedef enum {
    ALD_TIMER_INPUT_NONE  = 0U, /**< Clear input none */
    ALD_TIMER_INPUT_ETR   = 1U, /**< Clear input etr */
} ald_timer_clear_input_source_t;

/** @brief TIMER clear input polarity
  */
typedef enum {
    ALD_TIMER_POLARITY_NO_INV = 0U, /**< Polarity for ETRx pin */
    ALD_TIMER_POLARITY_INV    = 1U, /**< Polarity for ETRx pin */
} ald_timer_clear_input_polarity_t;

/** @brief TIMER clear input polarity
  */
typedef enum {
    ALD_TIMER_ETR_PSC_DIV1 = 0U,    /**< No prescaler is used */
    ALD_TIMER_ETR_PSC_DIV2 = 1U,    /**< ETR input source is divided by 2 */
    ALD_TIMER_ETR_PSC_DIV4 = 2U,    /**< ETR input source is divided by 4 */
    ALD_TIMER_ETR_PSC_DIV8 = 3U,    /**< ETR input source is divided by 8 */
} ald_timer_etr_psc_t;

/** @brief TIMER CHnREF Clear Select
  */
typedef enum {
    ALD_TIMER_CHNREF_CLR_CMP_IN = 0U, /**< Comparator CMP_IN */
    ALD_TIMER_CHNREF_CLR_ETF    = 1U, /**< External Trigger Signal ETF */
} ald_timer_chnref_clr_sel_t;

/** @brief  TIMER clear input configuration handle structure definition
  */
typedef struct {
    type_func_t state;          /**< TIMER clear Input state */
    ald_timer_clear_input_source_t source;  /**< TIMER clear Input sources */
    ald_timer_clear_input_polarity_t polarity;  /**< TIMER Clear Input polarity */
    ald_timer_etr_psc_t psc;            /**< TIMER Clear Input prescaler */
    ald_timer_chnref_clr_sel_t clrsel;      /**<TIMER CHnREF_Clear */
    uint32_t filter;            /**< TIMER Clear Input filter */
} ald_timer_clear_input_config_t;

/** @brief TIMER clock source
  */
typedef enum {
    ALD_TIMER_SRC_ETRMODE2 = 0U,    /**< Clock source is etr mode2 */
    ALD_TIMER_SRC_INTER    = 1U,    /**< Clock source is etr internal */
    ALD_TIMER_SRC_ITR0     = 2U,    /**< Clock source is etr itr0 */
    ALD_TIMER_SRC_ITR1     = 3U,    /**< Clock source is etr itr1 */
    ALD_TIMER_SRC_ITR2     = 4U,    /**< Clock source is etr itr2 */
    ALD_TIMER_SRC_ITR3     = 5U,    /**< Clock source is etr itr3 */
    ALD_TIMER_SRC_TI1ED    = 6U,    /**< Clock source is etr ti1ed */
    ALD_TIMER_SRC_TI1      = 7U,    /**< Clock source is etr ti1 */
    ALD_TIMER_SRC_TI2      = 8U,    /**< Clock source is etr ti2 */
    ALD_TIMER_SRC_ETRMODE1 = 9U,    /**< Clock source is etr mode1 */
} ald_timer_clock_source_t;

/** @brief TIMER clock polarity
  */
typedef enum {
    ALD_TIMER_CLK_POLARITY_INV    = 1U, /**< Polarity for ETRx clock sources */
    ALD_TIMER_CLK_POLARITY_NO_INV = 0U, /**< Polarity for ETRx clock sources */
    ALD_TIMER_CLK_POLARITY_RISE   = 0U, /**< Polarity for TIx clock sources */
    ALD_TIMER_CLK_POLARITY_FALL   = 1U, /**< Polarity for TIx clock sources */
    ALD_TIMER_CLK_POLARITY_BOTH   = 3U, /**< Polarity for TIx clock sources */
} ald_timer_clock_polarity_t;

/**
  * @brief  TIMER clock config structure definition
  */
typedef struct {
    ald_timer_clock_source_t source;        /**< TIMER clock sources */
    ald_timer_clock_polarity_t polarity;    /**< TIMER clock polarity */
    ald_timer_etr_psc_t psc;            /**< TIMER clock prescaler */
    uint32_t filter;            /**< TIMER clock filter */
} ald_timer_clock_config_t;

/**
  * @brief TIMER slave mode
  */
typedef enum {
    ALD_TIMER_MODE_DISABLE   = 0U,  /**< Slave mode is disable */
    ALD_TIMER_MODE_ENC1      = 1U,  /**< Slave mode is encoder1 */
    ALD_TIMER_MODE_ENC2      = 2U,  /**< Slave mode is encoder2 */
    ALD_TIMER_MODE_ENC3      = 3U,  /**< Slave mode is encoder3 */
    ALD_TIMER_MODE_RESET     = 4U,  /**< Slave mode is reset */
    ALD_TIMER_MODE_GATED     = 5U,  /**< Slave mode is gated */
    ALD_TIMER_MODE_TRIG      = 6U,  /**< Slave mode is trigger */
    ALD_TIMER_MODE_EXTERNAL1 = 7U,  /**< Slave mode is external1 */
} ald_timer_slave_mode_t;

/**
  * @brief TIMER ts definition
  */
typedef enum {
    ALD_TIMER_TS_ITR0    = 0U,  /**< ITR0 */
    ALD_TIMER_TS_ITR1    = 1U,  /**< ITR1 */
    ALD_TIMER_TS_ITR2    = 2U,  /**< ITR2 */
    ALD_TIMER_TS_ITR3    = 3U,  /**< ITR3 */
    ALD_TIMER_TS_TI1F_ED = 4U,  /**< TI1F_ED */
    ALD_TIMER_TS_TI1FP1  = 5U,  /**< TI1FP1 */
    ALD_TIMER_TS_TI2FP2  = 6U,  /**< TI2FP2 */
    ALD_TIMER_TS_ETRF    = 7U,  /**< ETRF */
} ald_timer_ts_t;

/**
  * @brief  TIMER slave configuration structure definition
  */
typedef struct {
    ald_timer_slave_mode_t mode;        /**< Slave mode selection */
    ald_timer_ts_t input;           /**< Input Trigger source */
    ald_timer_clock_polarity_t polarity;    /**< Input Trigger polarity */
    ald_timer_etr_psc_t psc;        /**< Input trigger prescaler */
    uint32_t filter;        /**< Input trigger filter */
} ald_timer_slave_config_t;

/**
  * @brief  TIMER hall sensor configuretion structure definition
  */
typedef struct {
    ald_timer_ic_polarity_t polarity;   /**< Specifies the active edge of the input signal */
    ald_timer_ic_prescaler_t psc;       /**< Specifies the Input Capture Prescaler */
    uint32_t filter;        /**< Specifies the input capture filter [0x0, 0xF] */
    uint32_t delay;         /**< Specifies the pulse value to be loaded into the register [0x0, 0xFFFF] */
} ald_timer_hall_sensor_init_t;

/**
  * @brief TIMER lock level
  */
typedef enum {
    ALD_TIMER_LOCK_LEVEL_OFF = 0U,  /**< Lock off */
    ALD_TIMER_LOCK_LEVEL_1   = 1U,  /**< Lock level 1 */
    ALD_TIMER_LOCK_LEVEL_2   = 2U,  /**< Lock level 2 */
    ALD_TIMER_LOCK_LEVEL_3   = 3U,  /**< Lock level 3 */
} ald_timer_lock_level_t;

/**
  * @brief TIMER break polarity
  */
typedef enum {
    ALD_TIMER_BREAK_POLARITY_LOW  = 0U, /**< LOW */
    ALD_TIMER_BREAK_POLARITY_HIGH = 1U, /**< HIGH */
} ald_timer_break_polarity_t;

/**
  * @brief  TIMER break and dead time configuretion structure definition
  */
typedef struct {
    type_func_t off_run;        /**< Enalbe/Disable off state in run mode */
    type_func_t off_idle;       /**< Enalbe/Disable off state in idle mode */
    ald_timer_lock_level_t lock_level;  /**< Lock level */
    uint32_t dead_time;     /**< Dead time, [0x0, 0xFF] */
    type_func_t break_state;    /**< Break state */
    ald_timer_break_polarity_t polarity;    /**< Break input polarity */
    type_func_t auto_out;       /**< Enalbe/Disable automatic output */
} ald_timer_break_dead_time_t;

/**
  * @brief  TIMER commutation event channel configuretion structure definition
  */
typedef struct {
    type_func_t en;     /**< Enalbe/Disable the channel */
    type_func_t n_en;   /**< Enalbe/Disable the complementary channel */
    ald_timer_oc_mode_t mode;   /**< Mode of the channel */
} ald_timer_channel_config_t;

/**
  * @brief  TIMER commutation event configuretion structure definition
  */
typedef struct {
    ald_timer_channel_config_t ch[3];   /**< Configure of channel */
} ald_timer_com_channel_config_t;

/**
  * @brief TIMER master mode selection
  */
typedef enum {
    ALD_TIMER_TRGO_RESET  = 0U, /**< RESET */
    ALD_TIMER_TRGO_ENABLE = 1U, /**< ENABLE */
    ALD_TIMER_TRGO_UPDATE = 2U, /**< UPDATE */
    ALD_TIMER_TRGO_OC1    = 3U, /**< OC1 */
    ALD_TIMER_TRGO_OC1REF = 4U, /**< OC1REF */
    ALD_TIMER_TRGO_OC2REF = 5U, /**< OC2REF */
    ALD_TIMER_TRGO_OC3REF = 6U, /**< OC3REF */
    ALD_TIMER_TRGO_OC4REF = 7U, /**< OC4REF */
} ald_timer_master_mode_sel_t;

/**
  * @brief  TIMER master configuretion structure definition
  */
typedef struct {
    ald_timer_master_mode_sel_t sel;    /**< Specifies the active edge of the input signal */
    type_func_t master_en;      /**< Master/Slave mode selection */
} ald_timer_master_config_t;

/**
  * @brief Specifies the event source
  */
typedef enum {
    ALD_TIMER_SRC_UPDATE = (1U << 0),   /**< Event source is update */
    ALD_TIMER_SRC_CC1    = (1U << 1),   /**< Event source is channel1 */
    ALD_TIMER_SRC_CC2    = (1U << 2),   /**< Event source is channel2 */
    ALD_TIMER_SRC_CC3    = (1U << 3),   /**< Event source is channel3 */
    ALD_TIMER_SRC_CC4    = (1U << 4),   /**< Event source is channel4 */
    ALD_TIMER_SRC_COM    = (1U << 5),   /**< Event source is compare */
    ALD_TIMER_SRC_TRIG   = (1U << 6),   /**< Event source is trigger */
    ALD_TIMER_SRC_BREAK  = (1U << 7),   /**< Event source is break */
} ald_timer_event_source_t;

/**
  * @brief TIMER interrupt definition
  */
typedef enum {
    ALD_TIMER_IT_UPDATE  = (1U << 0),   /**< Update interrupt bit */
    ALD_TIMER_IT_CC1     = (1U << 1),   /**< Channel1 interrupt bit */
    ALD_TIMER_IT_CC2     = (1U << 2),   /**< Channel2 interrupt bit */
    ALD_TIMER_IT_CC3     = (1U << 3),   /**< Channel3 interrupt bit */
    ALD_TIMER_IT_CC4     = (1U << 4),   /**< Channel4 interrupt bit */
    ALD_TIMER_IT_COM     = (1U << 5),   /**< compare interrupt bit */
    ALD_TIMER_IT_TRIGGER = (1U << 6),   /**< Trigger interrupt bit */
    ALD_TIMER_IT_BREAK   = (1U << 7),   /**< Break interrupt bit */
} ald_timer_it_t;

/**
  * @brief TIMER DMA request
  */
typedef enum {
    ALD_TIMER_DMA_UPDATE  = (1U << 0),  /**< DMA request from update */
    ALD_TIMER_DMA_CC1     = (1U << 1),  /**< DMA request from channel1 */
    ALD_TIMER_DMA_CC2     = (1U << 2),  /**< DMA request from channel2 */
    ALD_TIMER_DMA_CC3     = (1U << 3),  /**< DMA request from channel3 */
    ALD_TIMER_DMA_CC4     = (1U << 4),  /**< DMA request from channel4 */
    ALD_TIMER_DMA_COM     = (1U << 5),  /**< DMA request from compare */
    ALD_TIMER_DMA_TRIGGER = (1U << 6),  /**< DMA request from trigger */
} ald_timer_dma_req_t;

/**
  * @brief TIMER flag definition
  */
typedef enum {
    ALD_TIMER_FLAG_UPDATE  = (1U << 0), /**< Update interrupt flag */
    ALD_TIMER_FLAG_CC1     = (1U << 1), /**< Channel1 interrupt flag */
    ALD_TIMER_FLAG_CC2     = (1U << 2), /**< Channel2 interrupt flag */
    ALD_TIMER_FLAG_CC3     = (1U << 3), /**< Channel3 interrupt flag */
    ALD_TIMER_FLAG_CC4     = (1U << 4), /**< Channel4 interrupt flag */
    ALD_TIMER_FLAG_COM     = (1U << 5), /**< Compare interrupt flag */
    ALD_TIMER_FLAG_TRIGGER = (1U << 6), /**< Trigger interrupt flag */
    ALD_TIMER_FLAG_BREAK   = (1U << 7), /**< Break interrupt flag */
    ALD_TIMER_FLAG_CC1OF   = (1U << 9), /**< Channel1 override state flag */
    ALD_TIMER_FLAG_CC2OF   = (1U << 10),    /**< Channel2 override state flag */
    ALD_TIMER_FLAG_CC3OF   = (1U << 11),    /**< Channel3 override state flag */
    ALD_TIMER_FLAG_CC4OF   = (1U << 12),    /**< Channel4 override state flag */
} ald_timer_flag_t;
/**
  * @}
  */

/** @defgroup TIMER_Public_Macros   TIMER Public Macros
  * @{
  */
#define ALD_CCER_CCxE_MASK      ((1U << 0) | (1U << 4) | (1U << 8) | (1U << 12))
#define ALD_CCER_CCxNE_MASK     ((1U << 2) | (1U << 6) | (1U << 10))

/**
  * @brief  Reset TIMER handle state
  */
#define ALD_TIMER_RESET_HANDLE_STATE(hperh) ((hperh)->state = TIMER_STATE_RESET)

/**
  * @brief  Enable the TIMER peripheral.
 */
#define ALD_TIMER_ENABLE(hperh) (SET_BIT((hperh)->perh->CON1, TIMER_CON1_CNTEN_MSK))

/**
  * @brief  Enable the TIMER main output.
  */
#define ALD_TIMER_MOE_ENABLE(hperh) (SET_BIT((hperh)->perh->BDCFG, TIMER_BDCFG_GOEN_MSK))

/**
  * @brief  Disable the TIMER peripheral.
  */
#define ALD_TIMER_DISABLE(hperh)                                              \
do {                                                                    \
    if ((((hperh)->perh->CCEP & ALD_CCER_CCxE_MASK) == 0)       \
           && (((hperh)->perh->CCEP & ALD_CCER_CCxNE_MASK) == 0))       \
        CLEAR_BIT((hperh)->perh->CON1, TIMER_CON1_CNTEN_MSK);   \
} while (0)

/**
  * @brief  Disable the TIMER main output.
  * @note The Main Output Enable of a timer instance is disabled only if
  *       all the CCx and CCxN channels have been disabled
  */
#define ALD_TIMER_MOE_DISABLE(hperh)                        \
do {                                                                    \
    if ((((hperh)->perh->CCEP & ALD_CCER_CCxE_MASK) == 0)       \
           && (((hperh)->perh->CCEP & ALD_CCER_CCxNE_MASK) == 0))       \
        CLEAR_BIT((hperh)->perh->BDCFG, TIMER_BDCFG_GOEN_MSK);  \
} while (0)

/**
  * @brief  Sets the TIMER autoreload register value on runtime without calling
  *         another time any Init function.
  */
#define ALD_TIMER_SET_AUTORELOAD(handle, AUTORELOAD)    \
do {                        \
    (handle)->perh->AR    = (AUTORELOAD);   \
    (handle)->init.period = (AUTORELOAD);   \
} while (0)

/**
  * @brief  Gets the TIMER autoreload register value on runtime
  */
#define ALD_TIMER_GET_AUTORELOAD(handle)    ((handle)->perh->AR)

/**
  * @brief  Gets the TIMER count register value on runtime
  */
#define ALD_TIMER_GET_CNT(handle)   ((handle)->perh->COUNT)

/**
  * @brief  Gets the TIMER count direction value on runtime
  */
#define ALD_TIMER_GET_DIR(handle)   (READ_BITS((handle)->perh->CON1, TIMER_CON1_DIRSEL_MSK, TIMER_CON1_DIRSEL_POS))

/**
  * @brief  CCx DMA request sent when CCx event occurs
  */
#define ALD_TIMER_CCx_DMA_REQ_CCx(handle)   (CLEAR_BIT((handle)->perh->CON2, TIMER_CON2_CCDMASEL_MSK))

/**
  * @brief  CCx DMA request sent when update event occurs
  */
#define ALD_TIMER_CCx_DMA_REQ_UPDATE(handle)    (SET_BIT((handle)->perh->CON2, TIMER_CON2_CCDMASEL_MSK))

/**
  * @brief  Enable channel
  * @param  handle: TIMER handle
  * @param  ch: Must be one of this:
  *           TIMER_CHANNEL_1
  *           TIMER_CHANNEL_2
  *           TIMER_CHANNEL_3
  *           TIMER_CHANNEL_4
  */
#define ALD_TIMER_CCx_ENABLE(handle, ch)    (((ch) == ALD_TIMER_CHANNEL_4) ? \
(SET_BIT((handle)->perh->CCEP, TIMER_CCEP_CC4POL_MSK)) : (WRITE_REG(((handle)->perh->CCEP), (((handle)->perh->CCEP) | (1 << ((ch) << 2))))))

/**
  * @brief  Disable channel
  * @param  handle: TIMER handle
  * @param  ch: Must be one of this:
  *           TIMER_CHANNEL_1
  *           TIMER_CHANNEL_2
  *           TIMER_CHANNEL_3
  *           TIMER_CHANNEL_4
  */
#define ALD_TIMER_CCx_DISABLE(handle, ch)   (((ch) == ALD_TIMER_CHANNEL_4) ? \
(CLEAR_BIT((handle)->perh->CCEP, TIMER_CCEP_CC4EN_MSK)) : ((handle)->perh->CCEP &= ~(1 << ((ch) << 2))))

/**
  * @brief  Enable complementary channel
  * @param  handle: TIMER handle
  * @param  ch: Must be one of this:
  *           TIMER_CHANNEL_1
  *           TIMER_CHANNEL_2
  *           TIMER_CHANNEL_3
  */
#define ALD_TIMER_CCxN_ENABLE(handle, ch)   ((handle)->perh->CCEP |= (1 << (((ch) << 2) + 2)))

/**
  * @brief  Disable complementary channel
  * @param  handle: TIMER handle
  * @param  ch: Must be one of this:
  *           TIMER_CHANNEL_1
  *           TIMER_CHANNEL_2
  *           TIMER_CHANNEL_3
  */
#define ALD_TIMER_CCxN_DISABLE(handle, ch)  ((handle)->perh->CCEP &= ~(1 << (((ch) << 2) + 2)))
/**
  * @}
  */

/** @defgroup TIMER_Private_Macros TIMER Private Macros
  * @{
  */

#define IS_TIMER_INSTANCE(x)    (((x) == AD16C4T) || \
                                 ((x) == BS16T)   || \
                                 ((x) == GP16C4T0) || \
                                 ((x) == GP16C4T1) || \
                                 ((x) == GP16C4T2))
#define IS_ADTIMER_INSTANCE(x)  ((x) == AD16C4T)
#define IS_TIMER_XOR_INSTANCE(x)    (((x) == AD16C4T) || \
                     ((x) == GP16C4T2) || \
                     ((x) == GP16C4T1) || \
                     ((x) == GP16C4T0))
#define IS_TIMER_COM_EVENT_INSTANCE(x)  (((x) == AD16C4T) || \
                     ((x) == GP16C4T2) || \
                     ((x) == GP16C4T1) || \
                     ((x) == GP16C4T0))
#define IS_TIMER_CC2_INSTANCE(x)    (((x) == AD16C4T) || \
                     ((x) == GP16C4T0) || \
                     ((x) == GP16C4T1) || \
                     ((x) == GP16C4T2))
#define IS_TIMER_CC4_INSTANCE(x)    (((x) == AD16C4T) || \
                     ((x) == GP16C4T0) || \
                     ((x) == GP16C4T1) || \
                     ((x) == GP16C4T2))
#define IS_TIMER_BREAK_INSTANCE(x) ((x) == AD16C4T)
#define IS_TIMER_PWM_INPUT_INSTANCE(x, y) ((((x) == AD16C4T)           && \
                       (((y) == ALD_TIMER_CHANNEL_1)  || \
                       ((y) == ALD_TIMER_CHANNEL_2))) || \
                       (((x) == GP16C4T0)           && \
                       (((y) == ALD_TIMER_CHANNEL_1)  || \
                       ((y) == ALD_TIMER_CHANNEL_2))) || \
                       (((x) == GP16C4T1)           && \
                       (((y) == ALD_TIMER_CHANNEL_1)  || \
                       ((y) == ALD_TIMER_CHANNEL_2))) || \
                       (((x) == GP16C4T2)           && \
                       (((y) == ALD_TIMER_CHANNEL_1)  || \
                       ((y) == ALD_TIMER_CHANNEL_2))))
#define IS_TIMER_CCX_INSTANCE(x, y) ((((x) == AD16C4T)           && \
                     (((y) == ALD_TIMER_CHANNEL_1)  || \
                     ((y) == ALD_TIMER_CHANNEL_2)   || \
                     ((y) == ALD_TIMER_CHANNEL_3)   || \
                     ((y) == ALD_TIMER_CHANNEL_4))) || \
                     (((x) == GP16C4T0)           && \
                     (((y) == ALD_TIMER_CHANNEL_1)  || \
                     ((y) == ALD_TIMER_CHANNEL_2)   || \
                     ((y) == ALD_TIMER_CHANNEL_3)   || \
                     ((y) == ALD_TIMER_CHANNEL_4))) || \
                     (((x) == GP16C4T1)           && \
                     (((y) == ALD_TIMER_CHANNEL_1)  || \
                     ((y) == ALD_TIMER_CHANNEL_2)   || \
                     ((y) == ALD_TIMER_CHANNEL_3)   || \
                     ((y) == ALD_TIMER_CHANNEL_4))) || \
                      (((x) == GP16C4T2)           && \
                     (((y) == ALD_TIMER_CHANNEL_1)  || \
                     ((y) == ALD_TIMER_CHANNEL_2)   || \
                     ((y) == ALD_TIMER_CHANNEL_3)   || \
                     ((y) == ALD_TIMER_CHANNEL_4))))
#define IS_TIMER_CCXN_INSTANCE(x, y)    (((x) == AD16C4T)   && \
                                         (((y) == ALD_TIMER_CHANNEL_1) || \
                                         ((y) == ALD_TIMER_CHANNEL_2)  || \
                                         ((y) == ALD_TIMER_CHANNEL_3)  || \
                                         ((y) == ALD_TIMER_CHANNEL_4)))
#define IS_TIMER_REPETITION_COUNTER_INSTANCE(x) ((x) == AD16C4T)
#define IS_TIMER_CLOCK_DIVISION_INSTANCE(x) IS_TIMER_CC2_INSTANCE(x)

#define IS_TIMER_COUNTER_MODE(x)        (((x) == ALD_TIMER_CNT_MODE_UP)      || \
                                         ((x) == ALD_TIMER_CNT_MODE_DOWN)    || \
                                         ((x) == ALD_TIMER_CNT_MODE_CENTER1) || \
                                         ((x) == ALD_TIMER_CNT_MODE_CENTER2) || \
                                         ((x) == ALD_TIMER_CNT_MODE_CENTER3))
#define IS_TIMER_CLOCK_DIVISION(x)  (((x) == ALD_TIMER_CLOCK_DIV1) || \
                                         ((x) == ALD_TIMER_CLOCK_DIV2) || \
                                         ((x) == ALD_TIMER_CLOCK_DIV4))
#define IS_TIMER_PWM_MODE(x)        (((x) == ALD_TIMER_OC_MODE_PWM1) || \
                                         ((x) == ALD_TIMER_OC_MODE_PWM2))
#define IS_TIMER_OC_MODE(x)         (((x) == ALD_TIMER_OC_MODE_TIMERING)         || \
                                         ((x) == ALD_TIMER_OC_MODE_ACTIVE)         || \
                                         ((x) == ALD_TIMER_OC_MODE_INACTIVE)       || \
                                         ((x) == ALD_TIMER_OC_MODE_TOGGLE)         || \
                                         ((x) == ALD_TIMER_OC_MODE_FORCE_ACTIVE)   || \
                                         ((x) == ALD_TIMER_OC_MODE_FORCE_INACTIVE) || \
                                         ((x) == ALD_TIMER_OC_MODE_PWM1) || \
                                         ((x) == ALD_TIMER_OC_MODE_PWM2))
#define IS_TIMER_OC_POLARITY(x)         (((x) == ALD_TIMER_OC_POLARITY_HIGH) || \
                                         ((x) == ALD_TIMER_OC_POLARITY_LOW))
#define IS_TIMER_OCN_POLARITY(x)        (((x) == ALD_TIMER_OCN_POLARITY_HIGH) || \
                                         ((x) == ALD_TIMER_OCN_POLARITY_LOW))
#define IS_TIMER_OCIDLE_STATE(x)        (((x) == ALD_TIMER_OC_IDLE_RESET) || \
                                         ((x) == ALD_TIMER_OC_IDLE_SET))
#define IS_TIMER_OCNIDLE_STATE(x)   (((x) == ALD_TIMER_OCN_IDLE_RESET) || \
                                         ((x) == ALD_TIMER_OCN_IDLE_SET))
#define IS_TIMER_CHANNELS(x)        (((x) == ALD_TIMER_CHANNEL_1) || \
                                         ((x) == ALD_TIMER_CHANNEL_2) || \
                                         ((x) == ALD_TIMER_CHANNEL_3) || \
                                         ((x) == ALD_TIMER_CHANNEL_4) || \
                                         ((x) == ALD_TIMER_CHANNEL_ALL))
#define IS_TIMER_OP_MODE(x)         (((x) == ALD_TIMER_OP_MODE_REPEAT) || \
                                         ((x) == ALD_TIMER_OP_MODE_SINGLE))
#define IS_TIMER_OP_OUTPUT_CH(x)        (((x) == ALD_TIMER_OP_OUTPUT_CHANNEL_1) || \
                                         ((x) == ALD_TIMER_OP_OUTPUT_CHANNEL_2))
#define IS_TIMER_ENCODER_MODE(x)        (((x) == ALD_TIMER_ENC_MODE_TI1) || \
                                         ((x) == ALD_TIMER_ENC_MODE_TI2) || \
                                         ((x) == ALD_TIMER_ENC_MODE_TI12))
#define IS_TIMER_IC_POLARITY(x)         (((x) == ALD_TIMER_IC_POLARITY_RISE)  || \
                                         ((x) == ALD_TIMER_IC_POLARITY_FALL))
#define IS_TIMER_IC_SELECT(x)       (((x) == ALD_TIMER_IC_SEL_DIRECT)   || \
                                         ((x) == ALD_TIMER_IC_SEL_INDIRECT) || \
                                         ((x) == ALD_TIMER_IC_SEL_TRC))
#define IS_TIMER_IC_PSC(x)      (((x) == ALD_TIMER_IC_PSC_DIV1) || \
                                         ((x) == ALD_TIMER_IC_PSC_DIV2) || \
                                         ((x) == ALD_TIMER_IC_PSC_DIV4) || \
                                         ((x) == ALD_TIMER_IC_PSC_DIV8))
#define IS_TIMER_IC_FILTER(x)       ((x) <= 0xF)
#define IS_TIMER_DEAD_TIMERE(x)     ((x) <= 0xFF)
#define IS_TIMER_CLEAR_INPUT_SOURCE(x)  (((x) == ALD_TIMER_INPUT_NONE) || \
                                         ((x) == ALD_TIMER_INPUT_ETR))
#define IS_TIMER_CLEAR_INPUT_POLARITY(x)    (((x) == ALD_TIMER_POLARITY_NO_INV) || \
                                         ((x) == ALD_TIMER_POLARITY_INV))
#define IS_TIMER_ETR_PSC(x)         (((x) == ALD_TIMER_ETR_PSC_DIV1) || \
                                         ((x) == ALD_TIMER_ETR_PSC_DIV2) || \
                                         ((x) == ALD_TIMER_ETR_PSC_DIV4) || \
                                         ((x) == ALD_TIMER_ETR_PSC_DIV8))
#define IS_TIMER_CHNREF_CLEAR(X)    (((X) == ALD_TIMER_CHNREF_CLR_CMP_IN) || \
                     ((X) == ALD_TIMER_CHNREF_CLR_ETF))
#define IS_TIMER_CLOCK_SOURCE(x)    (((x) == ALD_TIMER_SRC_ETRMODE2) || \
                                         ((x) == ALD_TIMER_SRC_INTER)    || \
                                         ((x) == ALD_TIMER_SRC_ITR0)     || \
                                         ((x) == ALD_TIMER_SRC_ITR1)     || \
                                         ((x) == ALD_TIMER_SRC_ITR2)     || \
                                         ((x) == ALD_TIMER_SRC_ITR3)     || \
                                         ((x) == ALD_TIMER_SRC_TI1ED)    || \
                                         ((x) == ALD_TIMER_SRC_TI1)      || \
                                         ((x) == ALD_TIMER_SRC_TI2)      || \
                                         ((x) == ALD_TIMER_SRC_ETRMODE1))
#define IS_TIMER_CLOCK_POLARITY(x)  (((x) == ALD_TIMER_CLK_POLARITY_INV)    || \
                                         ((x) == ALD_TIMER_CLK_POLARITY_NO_INV) || \
                                         ((x) == ALD_TIMER_CLK_POLARITY_RISE)   || \
                                         ((x) == ALD_TIMER_CLK_POLARITY_FALL)   || \
                                         ((x) == ALD_TIMER_CLK_POLARITY_BOTH))
#define IS_TIMER_SLAVE_MODE(x)  (((x) == ALD_TIMER_MODE_DISABLE)  || \
                                 ((x) == ALD_TIMER_MODE_ENC1) || \
                                 ((x) == ALD_TIMER_MODE_ENC2) || \
                                 ((x) == ALD_TIMER_MODE_ENC3) || \
                                 ((x) == ALD_TIMER_MODE_RESET)    || \
                                 ((x) == ALD_TIMER_MODE_GATED)    || \
                                 ((x) == ALD_TIMER_MODE_TRIG)  || \
                                 ((x) == ALD_TIMER_MODE_EXTERNAL1))
#define IS_TIMER_EVENT_SOURCE(x)    (((x) == ALD_TIMER_SRC_UPDATE)  || \
                                 ((x) == ALD_TIMER_SRC_CC1)     || \
                                 ((x) == ALD_TIMER_SRC_CC2)     || \
                                 ((x) == ALD_TIMER_SRC_CC3)     || \
                                 ((x) == ALD_TIMER_SRC_CC4)     || \
                                 ((x) == ALD_TIMER_SRC_COM)     || \
                                 ((x) == ALD_TIMER_SRC_TRIG) || \
                                 ((x) == ALD_TIMER_SRC_BREAK))
#define IS_TIMER_TS(x)      (((x) == ALD_TIMER_TS_ITR0)    || \
                                 ((x) == ALD_TIMER_TS_ITR1)    || \
                                 ((x) == ALD_TIMER_TS_ITR2)    || \
                                 ((x) == ALD_TIMER_TS_ITR3)    || \
                                 ((x) == ALD_TIMER_TS_TI1F_ED) || \
                                 ((x) == ALD_TIMER_TS_TI1FP1)  || \
                                 ((x) == ALD_TIMER_TS_TI2FP2)  || \
                                 ((x) == ALD_TIMER_TS_ETRF))
#define IS_TIMER_CLOCK_LEVEL(x) (((x) == ALD_TIMER_LOCK_LEVEL_OFF) || \
                                 ((x) == ALD_TIMER_LOCK_LEVEL_1)   || \
                                 ((x) == ALD_TIMER_LOCK_LEVEL_2)   || \
                                 ((x) == ALD_TIMER_LOCK_LEVEL_3))
#define IS_TIMER_BREAK_POLARITY(x)  (((x) == ALD_TIMER_BREAK_POLARITY_LOW) || \
                                         ((x) == ALD_TIMER_BREAK_POLARITY_HIGH))
#define IS_TIMER_MASTER_MODE_SEL(x) (((x) == ALD_TIMER_TRGO_RESET)  || \
                                         ((x) == ALD_TIMER_TRGO_ENABLE) || \
                                         ((x) == ALD_TIMER_TRGO_UPDATE) || \
                                         ((x) == ALD_TIMER_TRGO_OC1)    || \
                                         ((x) == ALD_TIMER_TRGO_OC1REF) || \
                                         ((x) == ALD_TIMER_TRGO_OC2REF) || \
                                         ((x) == ALD_TIMER_TRGO_OC3REF) || \
                                         ((x) == ALD_TIMER_TRGO_OC4REF))
#define IS_TIMER_IT(x)  (((x) == ALD_TIMER_IT_UPDATE)  || \
                         ((x) == ALD_TIMER_IT_CC1)     || \
                         ((x) == ALD_TIMER_IT_CC2)     || \
                         ((x) == ALD_TIMER_IT_CC3)     || \
                         ((x) == ALD_TIMER_IT_CC4)     || \
                         ((x) == ALD_TIMER_IT_COM)     || \
                         ((x) == ALD_TIMER_IT_TRIGGER) || \
                         ((x) == ALD_TIMER_IT_BREAK))
#define IS_TIMER_DMA_REQ(x) (((x) == ALD_TIMER_DMA_UPDATE) || \
                                 ((x) == ALD_TIMER_DMA_CC1)    || \
                                 ((x) == ALD_TIMER_DMA_CC2)    || \
                                 ((x) == ALD_TIMER_DMA_CC3)    || \
                                 ((x) == ALD_TIMER_DMA_CC4)    || \
                                 ((x) == ALD_TIMER_DMA_COM)    || \
                                 ((x) == ALD_TIMER_DMA_TRIGGER))
#define IS_TIMER_FLAG(x)    (((x) == ALD_TIMER_FLAG_UPDATE)  || \
                         ((x) == ALD_TIMER_FLAG_CC1)     || \
                         ((x) == ALD_TIMER_FLAG_CC2)     || \
                         ((x) == ALD_TIMER_FLAG_CC3)     || \
                         ((x) == ALD_TIMER_FLAG_CC4)     || \
                         ((x) == ALD_TIMER_FLAG_COM)     || \
                         ((x) == ALD_TIMER_FLAG_TRIGGER) || \
                         ((x) == ALD_TIMER_FLAG_BREAK)   || \
                         ((x) == ALD_TIMER_FLAG_CC1OF)   || \
                         ((x) == ALD_TIMER_FLAG_CC2OF)   || \
                         ((x) == ALD_TIMER_FLAG_CC3OF)   || \
                         ((x) == ALD_TIMER_FLAG_CC4OF))
/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions
  * @{
  */
/** @addtogroup TIMER_Public_Functions_Group1
  * @{
  */
/* Time Base functions */
ald_status_t ald_timer_base_init(ald_timer_handle_t *hperh);
void ald_timer_base_reset(ald_timer_handle_t *hperh);
void ald_timer_base_start(ald_timer_handle_t *hperh);
void ald_timer_base_stop(ald_timer_handle_t *hperh);
void ald_timer_base_start_by_it(ald_timer_handle_t *hperh);
void ald_timer_base_stop_by_it(ald_timer_handle_t *hperh);

ald_status_t ald_timer_base_start_by_dma(ald_timer_handle_t *hperh,
                                  uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_base_stop_by_dma(ald_timer_handle_t *hperh);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group2
  * @{
  */
/* Timer Output Compare functions */
ald_status_t ald_timer_oc_init(ald_timer_handle_t *hperh);
void ald_timer_oc_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_oc_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_oc_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_oc_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

ald_status_t ald_timer_oc_start_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch,
                      uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_oc_stop_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group3
  * @{
  */
/* Timer PWM functions */
ald_status_t ald_timer_pwm_init(ald_timer_handle_t *hperh);
void ald_timer_pwm_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwm_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwm_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwm_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwm_set_freq(ald_timer_handle_t *hperh, uint32_t freq);
void ald_timer_pwm_set_duty(ald_timer_handle_t *hperh, ald_timer_channel_t ch, uint16_t duty);
void ald_timer_pwm_set_input(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

ald_status_t ald_timer_pwm_start_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch,
                      uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_pwm_stop_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group4
  * @{
  */
/* Timer Input Capture functions */
ald_status_t ald_timer_ic_init(ald_timer_handle_t *hperh);
void ald_timer_ic_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_ic_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_ic_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_ic_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

ald_status_t ald_timer_ic_start_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch,
                     uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_ic_stop_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group5
  * @{
  */
/* Timer One Pulse functions */
ald_status_t ald_timer_one_pulse_init(ald_timer_handle_t *hperh, ald_timer_op_mode_t mode);
void ald_timer_one_pulse_start(ald_timer_handle_t *hperh, ald_timer_op_output_channel_t ch);
void ald_timer_one_pulse_stop(ald_timer_handle_t *hperh, ald_timer_op_output_channel_t ch);
void ald_timer_one_pulse_start_by_it(ald_timer_handle_t *hperh, ald_timer_op_output_channel_t ch);
void ald_timer_one_pulse_stop_by_it(ald_timer_handle_t *hperh, ald_timer_op_output_channel_t ch);
/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group6
  * @{
  */
/* Timer encoder functions */
ald_status_t ald_timer_encoder_init(ald_timer_handle_t *hperh, ald_timer_encoder_init_t *config);
void ald_timer_encoder_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_encoder_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_encoder_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_encoder_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

ald_status_t ald_timer_encoder_start_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch,
                           uint16_t *buf1, uint16_t *buf2, uint32_t len,
               uint8_t dma_ch1, uint8_t dma_ch2);
void ald_timer_encoder_stop_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group7
  * @{
  */
/* Timer hall sensor functions */
ald_status_t ald_timer_hall_sensor_init(ald_timer_handle_t *hperh, ald_timer_hall_sensor_init_t *config);
void ald_timer_hall_sensor_start(ald_timer_handle_t *hperh);
void ald_timer_hall_sensor_stop(ald_timer_handle_t *hperh);
void ald_timer_hall_sensor_start_by_it(ald_timer_handle_t *hperh);
void ald_timer_hall_sensor_stop_by_it(ald_timer_handle_t *hperh);

ald_status_t ald_timer_hall_sensor_start_by_dma(ald_timer_handle_t *hperh,
                               uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_hall_sensor_stop_by_dma(ald_timer_handle_t *hperh);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group8
  * @{
  */
/* Timer complementary output compare functions */
void ald_timer_ocn_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_ocn_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_ocn_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_ocn_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

ald_status_t ald_timer_ocn_start_by_dma(ald_timer_handle_t *hperh,
                  ald_timer_channel_t ch, uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_ocn_stop_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group9
  * @{
  */
/* Timer complementary PWM functions */
void ald_timer_pwmn_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwmn_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwmn_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_pwmn_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

ald_status_t ald_timer_pwmn_start_by_dma(ald_timer_handle_t *hperh,
                  ald_timer_channel_t ch, uint16_t *buf, uint32_t len, uint8_t dma_ch);
void ald_timer_pwmn_stop_by_dma(ald_timer_handle_t *hperh, ald_timer_channel_t ch);

/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group10
  * @{
  */
/* Timer complementary one pulse functions */
void ald_timer_one_pulse_n_start(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_one_pulse_n_stop(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_one_pulse_n_start_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_one_pulse_n_stop_by_it(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group11
  * @{
  */
/* Control functions */
ald_status_t ald_timer_oc_config_channel(ald_timer_handle_t *hperh, ald_timer_oc_init_t* config, ald_timer_channel_t ch);
ald_status_t ald_timer_ic_config_channel(ald_timer_handle_t *hperh, ald_timer_ic_init_t* config, ald_timer_channel_t ch);
ald_status_t ald_timer_one_pulse_config_channel(ald_timer_handle_t *hperh, ald_timer_one_pulse_init_t *config, ald_timer_channel_t ch_out, ald_timer_channel_t ch_in);
ald_status_t ald_timer_config_oc_ref_clear(ald_timer_handle_t *hperh, ald_timer_clear_input_config_t *config, ald_timer_channel_t ch);
ald_status_t ald_timer_config_clock_source(ald_timer_handle_t *hperh, ald_timer_clock_config_t *config);
ald_status_t ald_timer_config_ti1_input(ald_timer_handle_t *hperh, uint32_t ti1_select);
ald_status_t ald_timer_slave_config_sync(ald_timer_handle_t *hperh, ald_timer_slave_config_t *config);
ald_status_t ald_timer_slave_config_sync_by_it(ald_timer_handle_t *hperh, ald_timer_slave_config_t *config);
ald_status_t ald_timer_generate_event(ald_timer_handle_t *hperh, ald_timer_event_source_t event);
uint32_t ald_timer_read_capture_value(ald_timer_handle_t *hperh, ald_timer_channel_t ch);
void ald_timer_set_output_mode(ald_timer_handle_t *hperh, ald_timer_oc_mode_t mode, ald_timer_channel_t ch);
void ald_timer_com_change_config(ald_timer_handle_t *hperh, ald_timer_com_channel_config_t *config);
void ald_timer_com_event_config(ald_timer_handle_t *hperh, ald_timer_ts_t ts, type_func_t trgi);
void ald_timer_com_event_config_it(ald_timer_handle_t *hperh, ald_timer_ts_t ts, type_func_t trgi);
void ald_timer_break_dead_time_config(ald_timer_handle_t *hperh, ald_timer_break_dead_time_t *config);
void ald_timer_master_sync_config(ald_timer_handle_t *hperh, ald_timer_master_config_t *config);
void ald_timer_irq_handler(ald_timer_handle_t *hperh);
void ald_timer_dma_req_config(ald_timer_handle_t *hperh, ald_timer_dma_req_t req, type_func_t state);
void ald_timer_interrupt_config(ald_timer_handle_t *hperh, ald_timer_it_t it, type_func_t state);
it_status_t ald_timer_get_it_status(ald_timer_handle_t *hperh, ald_timer_it_t it);
flag_status_t ald_timer_get_flag_status(ald_timer_handle_t *hperh, ald_timer_flag_t flag);
void ald_timer_clear_flag_status(ald_timer_handle_t *hperh, ald_timer_flag_t flag);
/**
  * @}
  */

/** @addtogroup TIMER_Public_Functions_Group12
  * @{
  */
/* State functions */
ald_timer_state_t ald_timer_get_state(ald_timer_handle_t *hperh);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ALD_TIMER_H__ */
