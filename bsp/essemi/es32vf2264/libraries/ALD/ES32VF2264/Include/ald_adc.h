/**
  ******************************************************************************
  * @file    ald_adc.h
  * @brief   Header file of ADC Module library.
  *
  * @version V1.0
  * @date    06 Mar. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          06 Mar. 2023    Lisq            The first version
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

#ifndef __ALD_ADC_H__
#define __ALD_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"
#include "ald_dma.h"
#include "ald_pis.h"
#include "ald_timer.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/** @defgroup ADC_Pubulic_Types ADC Pubulic Types
  * @{
  */

/**
  * @brief ADC  State structures definition
  */
typedef enum {
    ALD_ADC_STATE_RESET    = 0x0U,  /**< ADC not yet initialized or disabled */
    ALD_ADC_STATE_READY    = 0x1U,  /**< ADC peripheral ready for use */
    ALD_ADC_STATE_BUSY     = 0x2U,  /**< ADC is busy to internal process */
    ALD_ADC_STATE_TIMEOUT  = 0x4U,  /**< TimeOut occurrence */
    ALD_ADC_STATE_ERROR    = 0x8U,  /**< Internal error occurrence */
    ALD_ADC_STATE_BUSY_N   = 0x10U, /**< Normal channel busy */
    ALD_ADC_STATE_BUSY_I   = 0x20U, /**< Insert channel busy */
    ALD_ADC_STATE_BUSY_WDG = 0x40U, /**< Insert channel busy */
} ald_adc_state_t;

/**
  *@brief ADC Error Code
  */
typedef enum {
    ALD_ADC_ERROR_NONE     = 0x0U,  /**< No error */
    ALD_ADC_ERROR_INTERNAL = 0x1U,  /**< ADC IP internal error*/
    ALD_ADC_ERROR_OVR      = 0x2U,  /**< Overrun error */
    ALD_ADC_ERROR_DMA      = 0x4U,  /**< DMA transfer error */
} ald_adc_error_t;

/**
  *@brief ADC data alignment
  */
typedef enum {
    ALD_ADC_DATAALIGN_RIGHT = 0x0U, /**< ADC data alignment right */
    ALD_ADC_DATAALIGN_LEFT  = 0x1U, /**< ADC data alignment left */
} ald_adc_align_t;

/**
  *@brief ADC config  hannal trigger the EOC IT mode
  */
typedef enum {
    ALD_ADC_NCHESEL_MODE_ALL = 0x0U,    /**< ADC set RCHE after convert sequence finish */
    ALD_ADC_NCHESEL_MODE_ONE = 0x1U,    /**< ADC set RCHE after one convert finish */
} ald_adc_nchesel_t;

/**
  *@brief  ADC channels
  */
typedef enum {
    ALD_ADC_CHANNEL_0  = 0x0U,  /**< ADC channel 0 */
    ALD_ADC_CHANNEL_1  = 0x1U,  /**< ADC channel 1 */
    ALD_ADC_CHANNEL_2  = 0x2U,  /**< ADC channel 2 */
    ALD_ADC_CHANNEL_3  = 0x3U,  /**< ADC channel 3 */
    ALD_ADC_CHANNEL_4  = 0x4U,  /**< ADC channel 4 */
    ALD_ADC_CHANNEL_5  = 0x5U,  /**< ADC channel 5 */
    ALD_ADC_CHANNEL_6  = 0x6U,  /**< ADC channel 6 */
    ALD_ADC_CHANNEL_7  = 0x7U,  /**< ADC channel 7 */
    ALD_ADC_CHANNEL_8  = 0x8U,  /**< ADC channel 8 */
    ALD_ADC_CHANNEL_9  = 0x9U,  /**< ADC channel 9 */
    ALD_ADC_CHANNEL_10 = 0xAU,  /**< ADC channel 10 */
    ALD_ADC_CHANNEL_11 = 0xBU,  /**< ADC channel 11 */
    ALD_ADC_CHANNEL_12 = 0xCU,  /**< ADC channel 12 */
    ALD_ADC_CHANNEL_13 = 0xDU,  /**< ADC channel 13 */
    ALD_ADC_CHANNEL_14 = 0xEU,  /**< ADC channel 14 */
    ALD_ADC_CHANNEL_15 = 0xFU,  /**< ADC channel 15 */
    ALD_ADC_CHANNEL_16 = 0x10U, /**< ADC channel 16 */
    ALD_ADC_CHANNEL_17 = 0x11U, /**< ADC channel 17 */
    ALD_ADC_CHANNEL_18 = 0x12U, /**< ADC channel 18 */
    ALD_ADC_CHANNEL_19 = 0x13U, /**< ADC channel 19 */
} ald_adc_channel_t;

/**
  *@brief  ADC sampling times
  */
typedef enum {
    ALD_ADC_SAMPLETIME_4  = 0x0U,   /**< ADC sampling times 4 clk */
    ALD_ADC_SAMPLETIME_6  = 0x1U,   /**< ADC sampling times 6 clk */
    ALD_ADC_SAMPLETIME_10 = 0x2U,   /**< ADC sampling times 10 clk */
    ALD_ADC_SAMPLETIME_18 = 0x3U,   /**< ADC sampling times 18 clk */
} ald_adc_samp_t;

/**
  *@brief   ADC index channel in normal group
  */
typedef enum {
    ALD_ADC_NCH_IDX_1  = 0x1U,  /**< ADC normal channel index 1 */
    ALD_ADC_NCH_IDX_2  = 0x2U,  /**< ADC normal channel index 2 */
    ALD_ADC_NCH_IDX_3  = 0x3U,  /**< ADC normal channel index 3 */
    ALD_ADC_NCH_IDX_4  = 0x4U,  /**< ADC normal channel index 4 */
    ALD_ADC_NCH_IDX_5  = 0x5U,  /**< ADC normal channel index 5 */
    ALD_ADC_NCH_IDX_6  = 0x6U,  /**< ADC normal channel index 6 */
    ALD_ADC_NCH_IDX_7  = 0x7U,  /**< ADC normal channel index 7 */
    ALD_ADC_NCH_IDX_8  = 0x8U,  /**< ADC normal channel index 8 */
    ALD_ADC_NCH_IDX_9  = 0x9U,  /**< ADC normal channel index 9 */
    ALD_ADC_NCH_IDX_10 = 0xAU,  /**< ADC normal channel index 10 */
    ALD_ADC_NCH_IDX_11 = 0xBU,  /**< ADC normal channel index 11 */
    ALD_ADC_NCH_IDX_12 = 0xCU,  /**< ADC normal channel index 12 */
    ALD_ADC_NCH_IDX_13 = 0xDU,  /**< ADC normal channel index 13 */
    ALD_ADC_NCH_IDX_14 = 0xEU,  /**< ADC normal channel index 14 */
    ALD_ADC_NCH_IDX_15 = 0xFU,  /**< ADC normal channel index 15 */
    ALD_ADC_NCH_IDX_16 = 0x10U, /**< ADC normal channel index 16 */
} ald_adc_nch_idx_t;

/**
  * @brief ADC index channel in insert group
  */
typedef enum {
    ALD_ADC_ICH_IDX_1 = 0x1U,   /**< ADC insert channel index 1 */
    ALD_ADC_ICH_IDX_2 = 0x2U,   /**< ADC insert channel index 2 */
    ALD_ADC_ICH_IDX_3 = 0x3U,   /**< ADC insert channel index 3 */
    ALD_ADC_ICH_IDX_4 = 0x4U,   /**< ADC insert channel index 4 */
} ald_adc_ich_idx_t;

/**
  * @brief ADC analog watchdog mode
  */
typedef enum {
    ALD_ADC_ANAWTD_NONE       = 0x0U,       /**< No watch dog */
    ALD_ADC_ANAWTD_SING_NM    = 0x800200U,  /**< One normal channel watch dog */
    ALD_ADC_ANAWTD_SING_IST   = 0x400200U,  /**< One insert channel Injec watch dog */
    ALD_ADC_ANAWTD_SING_NMIST = 0xC00200U,  /**< One normal and insert channel watch dog */
    ALD_ADC_ANAWTD_ALL_NM     = 0x800000U,  /**< All normal channel watch dog */
    ALD_ADC_ANAWTD_ALL_IST    = 0x400000U,  /**< All insert channel watch dog */
    ALD_ADC_ANAWTD_ALL_NMIST  = 0xC00000U,  /**< All normal and insert channel watch dog */
} ald_adc_ana_wdg_t;

/**
  * @brief ADC Event type
  */
typedef enum {
    ALD_ADC_AWD_EVENT = (1U << 0),  /**< ADC analog watch dog event */
} ald_adc_event_type_t;

/**
  * @brief ADC interrupts definition
  */
typedef enum {
    ALD_ADC_IT_NCH = (1U << 5),     /**< ADC it normal */
    ALD_ADC_IT_AWD = (1U << 6),     /**< ADC it awd */
    ALD_ADC_IT_ICH = (1U << 7),     /**< ADC it insert */
    ALD_ADC_IT_OVR = (1U << 26),    /**< ADC it overring */
} ald_adc_it_t;

/**
  * @brief ADC flags definition
  */
typedef enum {
    ALD_ADC_FLAG_AWD  = (1U << 0),  /**<ADC flag awd */
    ALD_ADC_FLAG_NCH  = (1U << 1),  /**<ADC flag normal mode complete */
    ALD_ADC_FLAG_ICH  = (1U << 2),  /**<ADC flag insert mode complete */
    ALD_ADC_FLAG_OVR  = (1U << 3),  /**<ADC flag ovr */
    ALD_ADC_FLAG_NCHS = (1U << 8),  /**<ADC flag normal start */
    ALD_ADC_FLAG_ICHS = (1U << 9),  /**<ADC flag insert start */
} ald_adc_flag_t;

/**
  * @brief ADC CLK DIV definition
  */
typedef enum {
    ALD_ADC_CKDIV_2   = 0x0U,   /**< ADC CLK DIV 2 */
    ALD_ADC_CKDIV_4   = 0x1U,   /**< ADC CLK DIV 4 */
    ALD_ADC_CKDIV_8   = 0x2U,   /**< ADC CLK DIV 8 */
    ALD_ADC_CKDIV_16  = 0x3U,   /**< ADC CLK DIV 16 */
    ALD_ADC_CKDIV_32  = 0x4U,   /**< ADC CLK DIV 32 */
    ALD_ADC_CKDIV_64  = 0x5U,   /**< ADC CLK DIV 64 */
    ALD_ADC_CKDIV_128 = 0x6U,   /**< ADC CLK DIV 128 */
    ALD_ADC_CKDIV_256 = 0x7U,   /**< ADC CLK DIV 256 */
} ald_adc_clk_div_t;

/**
  * @brief ADC negative reference voltage definition
  */
typedef enum {
    ALD_ADC_NEG_REF_VREFN = 0x0U,   /**< ADC negative regerence voltage vrefn */
    ALD_ADC_NEG_REF_VSS   = 0x1U,   /**< ADC negative regerence voltage vss */
} ald_adc_neg_ref_t;

/**
  * @brief ADC positive reference voltage definition
  */
typedef enum {
    ALD_ADC_POS_REF_VDD        = 0x0U,  /**< ADC positive reference is VDD */
    ALD_ADC_POS_REF_VREEFP     = 0x1U,  /**< ADC positive reference is VREEFP */
} ald_adc_pos_ref_t;

/**
  * @brief ADC numbers of normal conversion channals
  */
typedef enum {
    ALD_ADC_NCH_NR_1  = 0x0U,   /**< ADC number of normal conversion 1 */
    ALD_ADC_NCH_NR_2  = 0x1U,   /**< ADC number of normal conversion 2 */
    ALD_ADC_NCH_NR_3  = 0x2U,   /**< ADC number of normal conversion 3 */
    ALD_ADC_NCH_NR_4  = 0x3U,   /**< ADC number of normal conversion 4 */
    ALD_ADC_NCH_NR_5  = 0x4U,   /**< ADC number of normal conversion 5 */
    ALD_ADC_NCH_NR_6  = 0x5U,   /**< ADC number of normal conversion 6 */
    ALD_ADC_NCH_NR_7  = 0x6U,   /**< ADC number of normal conversion 7 */
    ALD_ADC_NCH_NR_8  = 0x7U,   /**< ADC number of normal conversion 8 */
    ALD_ADC_NCH_NR_9  = 0x8U,   /**< ADC number of normal conversion 9 */
    ALD_ADC_NCH_NR_10 = 0x9U,   /**< ADC number of normal conversion 10 */
    ALD_ADC_NCH_NR_11 = 0xAU,   /**< ADC number of normal conversion 11 */
    ALD_ADC_NCH_NR_12 = 0xBU,   /**< ADC number of normal conversion 12 */
    ALD_ADC_NCH_NR_13 = 0xCU,   /**< ADC number of normal conversion 13 */
    ALD_ADC_NCH_NR_14 = 0xDU,   /**< ADC number of normal conversion 14 */
    ALD_ADC_NCH_NR_15 = 0xEU,   /**< ADC number of normal conversion 15 */
    ALD_ADC_NCH_NR_16 = 0xFU,   /**< ADC number of normal conversion 16 */
} ald_adc_nch_nr_t;

/**
  * @brief ADC numbers of insert conversion channals
  */
typedef enum {
    ALD_ADC_ICH_NR_1 = 0x0U,    /**< ADC number of insert conversion 1 */
    ALD_ADC_ICH_NR_2 = 0x1U,    /**< ADC number of insert conversion 2 */
    ALD_ADC_ICH_NR_3 = 0x2U,    /**< ADC number of insert conversion 3 */
    ALD_ADC_ICH_NR_4 = 0x3U,    /**< ADC number of insert conversion 4 */
} ald_adc_ich_nr_t;

/**
  * @brief ADC discontinuous mode choose
  */
typedef enum {
    ALD_ADC_ALL_DISABLE = 0x0U, /**< ADC discontinuous mode all disable */
    ALD_ADC_NCH_DISC_EN = 0x1U, /**< ADC normal channel discontinuous mode enable */
    ALD_ADC_ICH_DISC_EN = 0x2U, /**< ADC insert channel discontinuous mode enable */
} ald_adc_disc_mode_t;

/**
  * @brief ADC numbers of channals in discontinuous conversion mode
  */
typedef enum {
    ALD_ADC_DISC_NR_1 = 0x0U,   /**< ADC number of discontinuous conversion 1 */
    ALD_ADC_DISC_NR_2 = 0x1U,   /**< ADC number of discontinuous conversion 2 */
    ALD_ADC_DISC_NR_3 = 0x2U,   /**< ADC number of discontinuous conversion 3 */
    ALD_ADC_DISC_NR_4 = 0x3U,   /**< ADC number of discontinuous conversion 4 */
    ALD_ADC_DISC_NR_5 = 0x4U,   /**< ADC number of discontinuous conversion 5 */
    ALD_ADC_DISC_NR_6 = 0x5U,   /**< ADC number of discontinuous conversion 6 */
    ALD_ADC_DISC_NR_7 = 0x6U,   /**< ADC number of discontinuous conversion 7 */
    ALD_ADC_DISC_NR_8 = 0x7U,   /**< ADC number of discontinuous conversion 8 */
} ald_adc_disc_nr_t;

/**
  * @brief ADC resolution of conversion
  */
typedef enum {
    ALD_ADC_CONV_BIT_6  = 0x0U, /**< ADC resolution of conversion 6 */
    ALD_ADC_CONV_BIT_8  = 0x1U, /**< ADC resolution of conversion 8 */
    ALD_ADC_CONV_BIT_10 = 0x2U, /**< ADC resolution of conversion 10 */
    ALD_ADC_CONV_BIT_12 = 0x3U, /**< ADC resolution of conversion 12 */
} ald_adc_conv_bit_t;

/**
  * @brief ADC external trigger mode choose
  */
typedef enum {
    ALD_ADC_ETS_DISABLE   = 0x0U,   /**< ADC external trigger function disable */
    ALD_ADC_ETS_RISE      = 0x1U,   /**< rise edge trigger ADC */
    ALD_ADC_ETS_FALL      = 0x2U,   /**< fall edge trigger ADC */
    ALD_ADC_ETS_RISE_FALL = 0x3U,   /**< both rise and fall edge trigger ADC */
} ald_adc_ets_t;

/**
  * @brief ADC trigger conversion mode
  */


/**
  * @brief  Structure definition of ADC and normal group initialization
  */
typedef struct {
    ald_adc_align_t align;          /**< Specifies ADC data alignment */
    type_func_t scan;               /**< Choose scan mode enable or not */
    type_func_t cont;               /**< Choose continuous mode enable or not */
    ald_adc_nch_nr_t nch_nr;        /**< Length of normal ranks will be converted */
    ald_adc_ich_nr_t ich_nr;        /**< Length of insert ranks will be converted */
    ald_adc_disc_mode_t disc;       /**< Discontinuous mode enable or not */
    ald_adc_disc_nr_t disc_nr;      /**< Number of discontinuous conversions channel */
    ald_adc_conv_bit_t data_bit;    /**< The precision of conversion */
    ald_adc_clk_div_t div;          /**< ADCCLK divider */
    ald_adc_nchesel_t nche_sel;     /**< Trigger the NCHE FALG mode */
    ald_adc_neg_ref_t n_ref;        /**< The negative reference voltage*/
    ald_adc_pos_ref_t p_ref;        /**< The positive reference voltage*/
} ald_adc_init_t;

/**
  * @brief  Structure definition of ADC channel for normal group
  */
typedef struct {
    ald_adc_channel_t ch;   /**< The channel to configure into ADC normal group */
    ald_adc_nch_idx_t idx;  /**< The rank in the normal group sequencer */
    ald_adc_samp_t samp;    /**< Sampling time value to be set */
} ald_adc_nch_conf_t;

/**
  * @brief  ADC Configuration analog watchdog definition
  */
typedef struct {
    ald_adc_ana_wdg_t mode; /**< Configures the ADC analog watchdog mode*/
    ald_adc_channel_t ch;   /**< Selects which ADC channel to monitor by analog watchdog */
    type_func_t interrupt;  /**< Whether the analog watchdog is configured in interrupt */
    uint32_t high_thrd;     /**< The ADC analog watchdog High threshold value. */
    uint32_t low_thrd;      /**< The ADC analog watchdog Low threshold value. */
} ald_adc_analog_wdg_conf_t;

/**
  * @brief  ADC Configuration insert Channel structure definition
  */
typedef struct {
    ald_adc_channel_t ch;   /**< Selection of ADC channel to configure */
    ald_adc_ich_idx_t idx;  /**< Rank in the insert group sequencer */
    ald_adc_samp_t samp;    /**< Sampling time value for selected channel */
    uint32_t offset;        /**< The offset about converted data */
    ald_adc_ich_nr_t nr;    /**< The number of insert ranks */
    type_func_t auto_m;     /**< insert sequence's auto function */
} ald_adc_ich_conf_t;

/**
  * @brief  ADC handle Structure definition
  */
typedef struct ald_adc_handle_s {
    ADC_TypeDef *perh;              /**< Register base address */
    ald_adc_init_t init;            /**< ADC required parameters */

    ald_dma_handle_t hdma;          /**< Pointer DMA Handler */
    ald_pis_handle_t hpis;          /**< Pointer PIS Handler for connect adc and dma */

    lock_state_t lock;              /**< ADC locking object */
    ald_adc_state_t state;          /**< ADC communication state  */
    ald_adc_error_t error_code;     /**< ADC Error code */

    void (*normal_cplt_cbk)(struct ald_adc_handle_s *arg);      /**< Regluar Conversion complete callback */
    void (*insert_cplt_cbk)(struct ald_adc_handle_s *arg);      /**< insert Conversion complete callback */
    void (*wdg_cbk)(struct ald_adc_handle_s *arg);          /**< Level out of window callback */
    void (*error_cbk)(struct ald_adc_handle_s *arg);        /**< adc error callback */
    void (*ovr_cbk)(struct ald_adc_handle_s *arg);          /**< adc ovr callback */
} ald_adc_handle_t;

/**
  * @brief Timer trigger adc config structure definition
  */
typedef struct {
    uint32_t time;      /**< Timer period time uint: us */
    uint16_t size;      /**< ADC convert times */
    uint16_t *buf;      /**< Convert data buffer */
    ald_adc_neg_ref_t n_ref;    /**< The negative reference voltage for adc*/
    ald_adc_pos_ref_t p_ref;    /**< The positive reference voltage for adc*/
    ald_adc_channel_t adc_ch;   /**< ADC channel */
    uint8_t dma_ch;     /**< DMA channel */
    TIMER_TypeDef *p_timer; /**< Timer peripheral */
    ADC_TypeDef *p_adc; /**< ADC peripheral */
    void (*cplt_cbk)( struct ald_adc_handle_s *arg);    /**< Conversion complete callback */

    /* private variable */
    lock_state_t lock;  /**< Locking object */
    ald_pis_handle_t h_pis; /**< Handle of PIS module */
    ald_dma_handle_t h_dma; /**< Handle of DMA module */
    ald_timer_handle_t h_timer; /**< Handle of TIMER module */
    ald_adc_handle_t h_adc; /**< Handle of ADC module */
    ald_adc_nch_conf_t config;  /**< Struct for chanel configure */
    ald_adc_ich_conf_t i_config;/**< Struct for insert channel configuration */
} ald_adc_timer_config_t;
/**
  * @}
  */

/** @defgroup ADC_Public_Macros ADC Public Macros
  * @{
  */
#define ALD_ADC_ENABLE(handle)      (SET_BIT((handle)->perh->CON1, ADC_CON1_ADCEN_MSK))
#define ALD_ADC_DISABLE(handle)         (CLEAR_BIT((handle)->perh->CON1, ADC_CON1_ADCEN_MSK))
#define ALD_ADC_NH_TRIG_BY_SOFT(handle) (SET_BIT((handle)->perh->CON1, ADC_CON1_NCHTRG_MSK))
#define ALD_ADC_IH_TRIG_BY_SOFT(handle) (SET_BIT((handle)->perh->CON1, ADC_CON1_ICHTRG_MSK))
#define ALD_ADC_RESET_HANDLE_STATE(handle)  ((handle)->state = ADC_STATE_RESET)
#define ALD_ADC_VREF_OUT_ENABLE(handle) (SET_BIT((handle)->perh->CCR, ADC_CCR_VREFOEN_MSK))
#define ALD_ADC_VREF_OUT_DISABLE(handle)    (CLEAR_BIT((handle)->perh->CCR, ADC_CCR_VREFOEN_MSK))
#define ALD_ADC_NETS_ENABLE(handle, mode)   (MODIFY_REG((handle)->perh->CON1, ADC_CON1_NETS_MSK, (mode) << ADC_CON1_NETS_POSS))
#define ALD_ADC_IETS_ENABLE(handle, mode)   (MODIFY_REG((handle)->perh->CON1, ADC_CON1_IETS_MSK, (mode) << ADC_CON1_IETS_POSS))
#define ALD_ADC_NETS_DISABLE(handle)    (MODIFY_REG((handle)->perh->CON1, ADC_CON1_NETS_MSK, 0 << ADC_CON1_NETS_POSS))
#define ALD_ADC_IETS_DISABLE(handle)    (MODIFY_REG((handle)->perh->CON1, ADC_CON1_IETS_MSK, 0 << ADC_CON1_IETS_POSS))
#define ALD_ADC_SPEED_HIGH_DISABLE(handle)  (SET_BIT((handle)->perh->CCR, ADC_CCR_PWRMODSEL_MSK))
#define ALD_ADC_SPEED_HIGH_ENABLE(handle)   (CLEAR_BIT((handle)->perh->CCR, ADC_CCR_PWRMODSEL_MSK))
#define ALD_ADC_TEMP_SENSE_ENABLE(x)  (SET_BIT((x)->CCR, ADC_CCR_TSEN_MSK))
#define ALD_ADC_TEMP_SENSE_DISABLE(x) (CLEAR_BIT((x)->CCR, ADC_CCR_TSEN_MSK))
#define ALD_ADC_PREDIV_ENABLE(x)      (SET_BIT((x)->CCR, ADC_CCR_PREDIV_MSK))
#define ALD_ADC_PREDIV_DISABLE(x)     (CLEAR_BIT((x)->CCR, ADC_CCR_PREDIV_MSK))
/**
  * @}
  */

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
#define IS_ADC_ICH_IDX_TYPE(x)          ((x) <= ALD_ADC_ICH_IDX_4)
#define IS_ADC_NCH_IDX_TYPE(x)          ((x) <= ALD_ADC_NCH_IDX_16)
#define IS_ADC_SAMPLING_TIMES_TYPE(x)       (((x) == ALD_ADC_SAMPLETIME_4) || \
                                                 ((x) == ALD_ADC_SAMPLETIME_6) || \
                             ((x) == ALD_ADC_SAMPLETIME_10) || \
                             ((x) == ALD_ADC_SAMPLETIME_18))
#define IS_ADC_CHANNELS_TYPE(x)         ((x) <= ALD_ADC_CHANNEL_19)
#define IS_ADC_DATA_ALIGN_TYPE(x)       (((x) == ALD_ADC_DATAALIGN_RIGHT) || \
                                                 ((x) == ALD_ADC_DATAALIGN_LEFT))
#define IS_ADC_ANALOG_WTD_MODE_TYPE(x)      (((x) == ALD_ADC_ANAWTD_NONE)       || \
                         ((x) == ALD_ADC_ANAWTD_SING_NM)    || \
                         ((x) == ALD_ADC_ANAWTD_SING_IST)   || \
                         ((x) == ALD_ADC_ANAWTD_SING_NMIST) || \
                         ((x) == ALD_ADC_ANAWTD_ALL_NM)     || \
                         ((x) == ALD_ADC_ANAWTD_ALL_IST)    || \
                         ((x) == ALD_ADC_ANAWTD_ALL_NMIST))
#define IS_ADC_IT_TYPE(x)           (((x) == ALD_ADC_IT_NCH) || \
                         ((x) == ALD_ADC_IT_AWD) || \
                         ((x) == ALD_ADC_IT_ICH) ||  \
                         ((x) == ALD_ADC_IT_OVR ))
#define IS_ADC_FLAGS_TYPE(x)            (((x) == ALD_ADC_FLAG_AWD)  || \
                         ((x) == ALD_ADC_FLAG_NCH)  || \
                         ((x) == ALD_ADC_FLAG_ICH)  || \
                         ((x) == ALD_ADC_FLAG_OVR)  || \
                         ((x) == ALD_ADC_FLAG_NCHS) || \
                         ((x) == ALD_ADC_FLAG_ICHS))
#define IS_ADC_CLK_DIV_TYPE(x)          (((x) == ALD_ADC_CKDIV_2)   || \
                         ((x) == ALD_ADC_CKDIV_4)   || \
                         ((x) == ALD_ADC_CKDIV_8)   || \
                         ((x) == ALD_ADC_CKDIV_16)   || \
                         ((x) == ALD_ADC_CKDIV_32)  || \
                         ((x) == ALD_ADC_CKDIV_64)  || \
                         ((x) == ALD_ADC_CKDIV_128)  || \
                         ((x) == ALD_ADC_CKDIV_256))
#define IS_ADC_NEG_REF_VOLTAGE_TYPE(x)      (((x) == ALD_ADC_NEG_REF_VSS ) || \
                                                 ((x) == ALD_ADC_NEG_REF_VREFN ))
#define IS_POS_REF_VOLTAGE_TYPE(x)      (((x) == ALD_ADC_POS_REF_VDD)    || \
                         ((x) == ALD_ADC_POS_REF_VREEFP))
#define IS_ADC_NCH_NR_TYPE(x)           ((x) <= ALD_ADC_NCH_NR_16)
#define IS_ADC_ICH_NR_TYPE(x)           ((x) <= ALD_ADC_ICH_NR_4)
#define IS_ADC_DISC_NR_TYPE(x)          ((x) <= ALD_ADC_DISC_NR_8)
#define IS_ADC_CONV_BIT_TYPE(x)         (((x) == ALD_ADC_CONV_BIT_6) || \
                                                 ((x) == ALD_ADC_CONV_BIT_8)  || \
                         ((x) == ALD_ADC_CONV_BIT_10)  || \
                         ((x) == ALD_ADC_CONV_BIT_12))
#define IS_ADC_TYPE(x)              (((x) == ADC))
#define IS_ADC_NCHESEL_MODE_TYPE(x)     (((x) == ALD_ADC_NCHESEL_MODE_ALL) || \
                         ((x) == ALD_ADC_NCHESEL_MODE_ONE))
#define IS_ADC_EVENT_TYPE(x)            ((x) == ALD_ADC_AWD_EVENT)
#define IS_ADC_NCH_OFFSET_TYPE(x)       ((x) <= 0xfff)
#define IS_ADC_IST_OFFSET_TYPE(x)       ((x) <= 0xfff)
#define IS_HTR_TYPE(x)              ((x) <= 0xfff)
#define IS_LTR_TYPE(x)              ((x) <= 0xfff)
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions
  * @{
  */

/** @addtogroup ADC_Public_Functions_Group1
  * @{
  */
ald_status_t ald_adc_init(ald_adc_handle_t *hperh);
ald_status_t ald_adc_reset(ald_adc_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions_Group2
  * @{
  */
ald_status_t ald_adc_normal_start(ald_adc_handle_t *hperh);
ald_status_t ald_adc_normal_stop(ald_adc_handle_t *hperh);
ald_status_t ald_adc_normal_poll_for_conversion(ald_adc_handle_t *hperh, uint32_t timeout);
ald_status_t ald_adc_poll_for_event(ald_adc_handle_t *hperh, ald_adc_event_type_t event_type, uint32_t timeout);
ald_status_t ald_adc_normal_start_by_it(ald_adc_handle_t *hperh);
ald_status_t ald_adc_normal_stop_by_it(ald_adc_handle_t *hperh);

ald_status_t ald_adc_start_by_dma(ald_adc_handle_t *hperh, uint16_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_adc_stop_by_dma(ald_adc_handle_t *hperh, uint8_t channel);
ald_status_t ald_adc_timer_trigger_adc_by_dma(ald_adc_timer_config_t *config);
ald_status_t ald_adc_timer_trigger_insert(ald_adc_timer_config_t *config);

uint32_t ald_adc_normal_get_value(ald_adc_handle_t *hperh);
ald_status_t ald_adc_insert_start(ald_adc_handle_t *hperh);
ald_status_t ald_adc_insert_stop(ald_adc_handle_t *hperh);
ald_status_t ald_adc_insert_poll_for_conversion(ald_adc_handle_t *hperh, uint32_t timeout);
ald_status_t ald_adc_insert_start_by_it(ald_adc_handle_t *hperh);
ald_status_t ald_adc_insert_stop_by_it(ald_adc_handle_t *hperh);
uint32_t ald_adc_insert_get_value(ald_adc_handle_t *hperh, ald_adc_ich_idx_t ih_rank);
void ald_adc_irq_handler(ald_adc_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions_Group3
  * @{
  */
ald_status_t ald_adc_normal_channel_config(ald_adc_handle_t *hperh, ald_adc_nch_conf_t *config);
ald_status_t ald_adc_insert_channel_config(ald_adc_handle_t *hperh, ald_adc_ich_conf_t *config);
ald_status_t ald_adc_analog_wdg_config(ald_adc_handle_t *hperh, ald_adc_analog_wdg_conf_t *config);
void ald_adc_interrupt_config(ald_adc_handle_t *hperh, ald_adc_it_t it, type_func_t state);
it_status_t ald_adc_get_it_status(ald_adc_handle_t *hperh, ald_adc_it_t it);
flag_status_t ald_adc_get_flag_status(ald_adc_handle_t *hperh, ald_adc_flag_t flag);
void ald_adc_clear_flag_status(ald_adc_handle_t *hperh, ald_adc_flag_t flag);
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions_Group4
  * @{
  */
uint32_t ald_adc_get_state(ald_adc_handle_t *hperh);
uint32_t ald_adc_get_error(ald_adc_handle_t *hperh);
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
 extern "C" }
#endif /* __cplusplus */

#endif /* __ALD_ADC_H */
