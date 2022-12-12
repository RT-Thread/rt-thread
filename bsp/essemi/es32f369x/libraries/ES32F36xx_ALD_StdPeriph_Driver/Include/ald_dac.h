/**
  ******************************************************************************
 * @file    ald_dac.h
 * @brief   Header file of DAC Module library.
 *
 * @version V1.0
 * @date    28 Jun 2019
 * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          28 Jun 2019     AE Team         The first version
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

#ifndef __ALD_DAC_H__
#define __ALD_DAC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup DAC
  * @{
  */

/** @defgroup DAC_Pubulic_Types DAC Pubulic Types
  * @{
  */
/**
  * @brief DAC channel
  */
typedef enum {
	DAC_CHANNEL_0    = 1U,	/**< DAC channel 0 */
	DAC_CHANNEL_1    = 2U,	/**< DAC channel 1 */
	DAC_CHANNEL_COMB = 3U,	/**< DAC channel 0 and 1 */
} dac_channel_t;

/**
  * @brief DAC convert mode
  */
typedef enum {
	DAC_CONV_MODE_CONTINUOUS = 0U,	/**< DAC set in continuous mode */
	DAC_CONV_MODE_SAMPLEHOLD = 1U,	/**< DAC set in sample/hold mode */
	DAC_CONV_MODE_SAMPLEOFF  = 2U,	/**< DAC set in sample/shut off mode */
} dac_conv_mode_t;

/**
  * @brief DAC out mode
  */
typedef enum {
	DAC_OUTPUT_DISABLE = 0U,	/**< DAC output disable */
	DAC_OUTPUT_PIN     = 1U,	/**< DAC output to pin enable */
	DAC_OUTPUT_ADC     = 2U,	/**< DAC output to adc and acmp enable */
	DAC_OUTPUT_PIN_ADC = 3U,	/**< DAC output to pin, adc and acmp enable */
} dac_out_mode_t;

/**
  * @brief DAC pis input channel
  */
typedef enum {
	DAC_PIS_CH_0  = 0U,	/**< PIS channel 0 triggers DAC channel conversion */
	DAC_PIS_CH_1  = 1U,	/**< PIS channel 1 triggers DAC channel conversion */
	DAC_PIS_CH_2  = 2U,	/**< PIS channel 2 triggers DAC channel conversion */
	DAC_PIS_CH_3  = 3U,	/**< PIS channel 3 triggers DAC channel conversion */
	DAC_PIS_CH_4  = 4U,	/**< PIS channel 4 triggers DAC channel conversion */
	DAC_PIS_CH_5  = 5U,	/**< PIS channel 5 triggers DAC channel conversion */
	DAC_PIS_CH_6  = 6U,	/**< PIS channel 6 triggers DAC channel conversion */
	DAC_PIS_CH_7  = 7U,	/**< PIS channel 7 triggers DAC channel conversion */
	DAC_PIS_CH_8  = 8U,	/**< PIS channel 8 triggers DAC channel conversion */
	DAC_PIS_CH_9  = 9U,	/**< PIS channel 9 triggers DAC channel conversion */
	DAC_PIS_CH_10 = 10U,	/**< PIS channel 10 triggers DAC channel conversion */
	DAC_PIS_CH_11 = 11U,	/**< PIS channel 11 triggers DAC channel conversion */
} dac_pissel_t;

/**
  * @brief DAC negative reference voltage definition
  */
typedef enum {
	DAC_NEG_REF_VSS   = 0x0U,	/**< DAC negative regerence voltage vss */
	DAC_NEG_REF_VREFN = 0x1U,	/**< DAC negative regerence voltage vrefn */
} dac_neg_ref_t;

/**
  * @brief DAC positive reference voltage definition
  */
typedef enum {
	DAC_POS_REF_VDD        = 0x0U,	/**< DAC posotove reference is VDD */
	DAC_POS_REF_2V         = 0x1U,	/**< DAC posotove reference is internal 2V */
	DAC_POS_REF_VREEFP     = 0x2U,	/**< DAC posotove reference is VREEFP */
	DAC_POS_REF_VREEFP_BUF = 0x3U,	/**< DAC posotove reference is VREEFP BUFFER */
} dac_pos_ref_t;

/**
  * @brief Refresh interval select
  */
typedef enum {
	DAC_REFRESH_8  = 0U,	/**< Channel refreshed every 8 cycles */
	DAC_REFRESH_16 = 1U,	/**< Channel refreshed every 16 cycles */
	DAC_REFRESH_32 = 2U,	/**< Channel refreshed every 32 cycles */
	DAC_REFRESH_64 = 3U,	/**< Channel refreshed every 64 cycles */
} dac_refresh_t;

/**
  * @brief DAC prescale
  */
typedef enum {
	DAC_PRES_DIV_1   = 0U,	/**< No division */
	DAC_PRES_DIV_2   = 1U,	/**< 2 clock division */
	DAC_PRES_DIV_4   = 2U,	/**< 4 clock division */
	DAC_PRES_DIV_8   = 3U,	/**< 8 clock division */
	DAC_PRES_DIV_16  = 4U,	/**< 16 clock division */
	DAC_PRES_DIV_32  = 5U,	/**< 32 clock division */
	DAC_PRES_DIV_64  = 6U,	/**< 64 clock division */
	DAC_PRES_DIV_128 = 7U,	/**< 128 clock division */
} dac_prescale_div_t;

/**
  * @brief DAC output trigger select
  */
typedef enum {
	DAC_TRIGGER_BY_DATA = 0U,	/**< Channel is triggered by CHxDATA or COMBDATA write */
	DAC_TRIGGER_BY_PIS  = 1U,	/**< Channel is triggered by PIS input */
} dac_trigger_t;

/**
  * @brief DAC interrupt type
  */
typedef enum {
	DAC_IT_CH0    = (1U << 0),	/**< Channel 0 conversion complete interrupt */
	DAC_IT_CH1    = (1U << 1),	/**< Channel 1 conversion complete interrupt */
	DAC_IT_CH0_UF = (1U << 4),	/**< Channel 0 data underflow interrupt */
	DAC_IT_CH1_UF = (1U << 5),	/**< Channel 1 data underflow interrupt */
} dac_it_t;

/**
  * @brief DAC interrupt flag type
  */
typedef enum {
	DAC_FLAG_CH0    = (1U << 0),	/**< Channel 0 conversion complete interrupt flag */
	DAC_FLAG_CH1    = (1U << 1),	/**< Channel 1 conversion complete interrupt flag */
	DAC_FLAG_CH0_UF = (1U << 4),	/**< Channel 0 data underflow interrupt flag */
	DAC_FLAG_CH1_UF = (1U << 5),	/**< Channel 1 data underflow interrupt flag */		
} dac_flag_t;

/**
  * @brief DAC state flag
  */
typedef enum {
	DAC_CH0_BSY = (1U << 0),	/**< Channel_0 is BUSY */
	DAC_CH1_BSY = (1U << 1),	/**< Channel_1 is BUSY */
} dac_status_t;

/**
  * @brief DAC init structure definition
  */
typedef struct {
	dac_conv_mode_t conv_mode;	/**< Conversion mode */
	dac_out_mode_t out_mode;	/**< Select output mode */
	dac_refresh_t refresh;		/**< Refresh interval select */
	dac_prescale_div_t div;		/**< Prescaler setting */
	type_func_t ch0_reset;		/**< Select if prescaler is reset on channel 0 start */
	type_func_t o_ctrl_pis;		/**< Enable pis control of dac output enable */
	type_func_t sine;		/**< Sine mode enable/disable */
	type_func_t diff;		/**< Differential mode enable/disable */
	dac_neg_ref_t n_ref;		/**< The negative reference voltage select */
	dac_pos_ref_t p_ref;		/**< The positive reference voltage select */
} dac_init_t;

/**
  * @brief DAC channel initialize structure definition
  */
typedef struct {
	type_func_t enable;	/**< DAC channel output enable/disable */
	dac_trigger_t trigger;	/**< Select channel conversion trigger */
	type_func_t refresh_en;	/**< Set automatic refresh of channel function */
	dac_pissel_t pis_ch;	/**< Select channel pis input channel */
} dac_channel_config_t;

/**
  * @brief  DAC handle Structure definition
  */
typedef struct dac_handle_s {
	DAC_TypeDef *perh;	/**< Register base address */
	dac_init_t init;	/**< DAC initialize parameters */
	lock_state_t lock;	/**< Locking object */

	void (*cbk)(struct dac_handle_s *arg, uint32_t event);	/**< DAC event callback */
} dac_handle_t;
/**
  * @}
  */

/** @defgroup DAC_Public_Macros DAC Public Macros
  * @{
  */
#define DAC_CH0_ENABLE()	(SET_BIT(DAC0->CH0CTRL, DAC_CH0CTRL_EN_MSK))
#define DAC_CH1_ENABLE()	(SET_BIT(DAC0->CH1CTRL, DAC_CH1CTRL_EN_MSK))
#define DAC_CH0_DISABLE()	(CLEAR_BIT(DAC0->CH0CTRL, DAC_CH0CTRL_EN_MSK))
#define DAC_CH1_DISABLE()	(CLEAR_BIT(DAC0->CH1CTRL, DAC_CH1CTRL_EN_MSK))

#define DAC_EVENT_CH0_CPLT	0x0
#define DAC_EVENT_CH1_CPLT	0x1
#define DAC_EVENT_CH0_UF	0x2
#define DAC_EVENT_CH1_UF	0x3
/**
  * @}
  */

/** @defgroup DAC_Private_Macros DAC Private Macros
  * @{
  */
#define IS_DAC_TYPE(x)			((x) == DAC0)
#define IS_DAC_CONVERT_TYPE(x)		(((x) == DAC_CONV_MODE_CONTINUOUS) || \
					 ((x) == DAC_CONV_MODE_SAMPLEHOLD) || \
					 ((x) == DAC_CONV_MODE_SAMPLEOFF))
#define IS_DAC_OUTPUT_TYPE(x)		(((x) == DAC_OUTPUT_DISABLE) || \
					 ((x) == DAC_OUTPUT_PIN)     || \
					 ((x) == DAC_OUTPUT_ADC)     || \
					 ((x) == DAC_OUTPUT_PIN_ADC))
#define IS_DAC_NEG_REFRESH_TYPE(x)	(((x) == DAC_NEG_REF_VSS)  || \
					 ((x) == DAC_NEG_REF_VREFN))
#define IS_DAC_POS_REFRESH_TYPE(x)	(((x) == DAC_POS_REF_VDD)  || \
					 ((x) == DAC_POS_REF_2V) || \
					 ((x) == DAC_POS_REF_VREEFP) || \
					 ((x) == DAC_POS_REF_VREEFP_BUF))
#define IS_DAC_REFRESH_TYPE(x)		(((x) == DAC_REFRESH_8)  || \
					 ((x) == DAC_REFRESH_16) || \
					 ((x) == DAC_REFRESH_32) || \
					 ((x) == DAC_REFRESH_64))
#define IS_DAC_CHANNEL_TYPE(x)		(((x) == DAC_CHANNEL_0) || \
					 ((x) == DAC_CHANNEL_1) || \
					 ((x) == DAC_CHANNEL_COMB))
#define IS_DAC_PRESCALE_TYPE(x)		(((x) == DAC_PRES_DIV_1) || \
					 ((x) == DAC_PRES_DIV_2) || \
					 ((x) == DAC_PRES_DIV_4) || \
					 ((x) == DAC_PRES_DIV_8) || \
					 ((x) == DAC_PRES_DIV_16) || \
					 ((x) == DAC_PRES_DIV_32) || \
					 ((x) == DAC_PRES_DIV_64) || \
					 ((x) == DAC_PRES_DIV_128))
#define IS_DAC_INTERRUPT_TYPE(x)	(((x) == DAC_IT_CH0)    || \
					 ((x) == DAC_IT_CH1)    || \
					 ((x) == DAC_IT_CH0_UF) || \
					 ((x) == DAC_IT_CH1_UF))
#define IS_DAC_FLAG_TYPE(x)		(((x) == DAC_FLAG_CH0)    || \
					 ((x) == DAC_FLAG_CH1)    || \
					 ((x) == DAC_FLAG_CH0_UF) || \
					 ((x) == DAC_FLAG_CH1_UF))
#define IS_DAC_PISSEL_CH_TYPE(x)	(((x) == DAC_PIS_CH_0)  || \
					 ((x) == DAC_PIS_CH_1)  || \
					 ((x) == DAC_PIS_CH_2)  || \
					 ((x) == DAC_PIS_CH_3)  || \
					 ((x) == DAC_PIS_CH_4)  || \
					 ((x) == DAC_PIS_CH_5)  || \
					 ((x) == DAC_PIS_CH_6)  || \
					 ((x) == DAC_PIS_CH_7)  || \
					 ((x) == DAC_PIS_CH_8)  || \
					 ((x) == DAC_PIS_CH_9)  || \
					 ((x) == DAC_PIS_CH_10) || \
					 ((x) == DAC_PIS_CH_11))
#define IS_DAC_STATUS_TYPE(x)		(((x) == DAC_CH0_BSY) || \
					 ((x) == DAC_CH1_BSY))
#define IS_DAC_TRIGGER_TYPE(x)		(((x) == DAC_TRIGGER_BY_DATA) || \
					 ((x) == DAC_TRIGGER_BY_PIS))
/**
  * @}
  */

/** @addtogroup DAC_Public_Functions
  * @{
  */
ald_status_t ald_dac_reset(dac_handle_t *hperh);
ald_status_t ald_dac_init(dac_handle_t *hperh);
ald_status_t ald_dac_channel_config(dac_handle_t *hperh, dac_channel_config_t *config, dac_channel_t ch);
void ald_dac_output_set(dac_handle_t *hperh, dac_channel_t ch, uint32_t value);
flag_status_t ald_dac_get_status(dac_handle_t *hperh, dac_status_t status);
void ald_dac_interrupt_config(dac_handle_t *hperh, dac_it_t it, type_func_t state);
it_status_t ald_dac_get_it_status(dac_handle_t *hperh, dac_it_t it);
flag_status_t ald_dac_get_flag_status(dac_handle_t *hperh, dac_flag_t flag);
flag_status_t ald_dac_get_mask_flag_status(dac_handle_t *hperh, dac_flag_t flag);
void ald_dac_clear_flag_status(dac_handle_t *hperh, dac_flag_t flag);
void ald_dac_irq_handler(dac_handle_t *hperh);
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
#endif

#endif /* __ALD_DAC_H */
