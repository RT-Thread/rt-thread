/**
  *********************************************************************************
  *
  * @file    ald_acmp.h
  * @brief   Header file of ACMP module driver.
  *
  * @version V1.0
  * @date    26 Jun 2019
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          26 Jun 2019     AE Team         The first version
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

#ifndef __ALD_ACMP_H__
#define __ALD_ACMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"

/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup ACMP
  * @{
  */

/** @defgroup ACMP_Public_Types ACMP Public Types
  * @{
  */

/**
  * @brief ACMP interrupt
  */
typedef enum {
	ACMP_IT_EDGE   = (1U << 0),	/**< Edge interrupt bit */
	ACMP_IT_WARMUP = (1U << 1),	/**< Warm up interrupt bit */
} acmp_it_t;

/**
  * @brief ACMP interrupt flag
  */
typedef enum {
	ACMP_FLAG_EDGE   = (1U << 0),	/**< Edge interrupt flag */
	ACMP_FLAG_WARMUP = (1U << 1),	/**< Warm up interrupt flag */	
} acmp_flag_t;

/**
  * @brief ACMP status flag
  */
typedef enum {
	ACMP_STATUS_ACT = (1U << 0),	/**< Edge status flag */
	ACMP_STATUS_OUT = (1U << 1),	/**< Warm up status flag */
} acmp_status_t;

/**
  * @brief ACMP positive input
  */
typedef enum {
	ACMP_POS_CH0 = 0x0U,	/**< Channel 0 as positive input */
	ACMP_POS_CH1 = 0x1U,	/**< Channel 1 as positive input */
	ACMP_POS_CH2 = 0x2U,	/**< Channel 2 as positive input */
	ACMP_POS_CH3 = 0x3U,	/**< Channel 3 as positive input */
	ACMP_POS_CH4 = 0x4U,	/**< Channel 4 as positive input */
	ACMP_POS_CH5 = 0x5U,	/**< Channel 5 as positive input */
	ACMP_POS_CH6 = 0x6U,	/**< Channel 6 as positive input */
	ACMP_POS_CH7 = 0x7U,	/**< Channel 7 as positive input */
} acmp_pos_input_t;

/**
  * @brief ACMP negative input
  */
typedef enum {
	ACMP_NEG_CH0  = 0x0U, 	/**< Channel 0 as negative input */
	ACMP_NEG_CH1  = 0x1U, 	/**< Channel 1 as negative input */
	ACMP_NEG_CH2  = 0x2U, 	/**< Channel 2 as negative input */
	ACMP_NEG_CH3  = 0x3U, 	/**< Channel 3 as negative input */
	ACMP_NEG_CH4  = 0x4U, 	/**< Channel 4 as negative input */
	ACMP_NEG_CH5  = 0x5U, 	/**< Channel 5 as negative input */
	ACMP_NEG_CH6  = 0x6U, 	/**< Channel 6 as negative input */
	ACMP_NEG_CH7  = 0x7U, 	/**< Channel 7 as negative input */
	ACMP_NEG_1V25 = 0x8U, 	/**< 1.25v as negative input */
	ACMP_NEG_2V5  = 0x9U, 	/**< 2.5v as negative input */
	ACMP_NEG_VDD  = 0xAU,	/**< VDD as negative input */
} acmp_neg_input_t;

/**
  * @brief ACMP mode
  */
typedef enum {
	ACMP_ULTRA_LOW_POWER = 0x0U,	/**< Ultra low power mode */
	ACMP_LOW_POWER       = 0x1U,	/**< Low power mode */
	ACMP_MIDDLE_POWER    = 0x2U,	/**< Middle power mode */
	ACMP_HIGH_POWER      = 0x3U,	/**< High power mode */
} acmp_mode_t;

/**
  * @brief ACMP warm-up time
  */
typedef enum {
	ACMP_4_PCLK   = 0x0U,	/**< 4 hfperclk cycles */
	ACMP_8_PCLK   = 0x1U,	/**< 4 hfperclk cycles */
	ACMP_16_PCLK  = 0x2U,	/**< 4 hfperclk cycles */
	ACMP_32_PCLK  = 0x3U,	/**< 4 hfperclk cycles */
	ACMP_64_PCLK  = 0x4U,	/**< 4 hfperclk cycles */
	ACMP_128_PCLK = 0x5U,	/**< 4 hfperclk cycles */
	ACMP_256_PCLK = 0x6U,	/**< 4 hfperclk cycles */
	ACMP_512_PCLK = 0x7U,	/**< 4 hfperclk cycles */
} acmp_warm_time_t;

/**
  * @brief ACMP hysteresis level
  */
typedef enum {
	ACMP_HYST_0  = 0x0U,	/**< No hysteresis */
	ACMP_HYST_15 = 0x1U,	/**< 15mV hysteresis */
	ACMP_HYST_22 = 0x2U,	/**< 22mV hysteresis */
	ACMP_HYST_29 = 0x3U,	/**< 29mV hysteresis */
	ACMP_HYST_36 = 0x4U,	/**< 36mV hysteresis */
	ACMP_HYST_43 = 0x5U,	/**< 43mV hysteresis */
	ACMP_HYST_50 = 0x6U,	/**< 50mV hysteresis */
	ACMP_HYST_57 = 0x7U,	/**< 57mV hysteresis */
} acmp_hystsel_t;

/**
  * @brief ACMP inactive state
  */
typedef enum {
	ACMP_INACTVAL_LOW  = 0x0U,	/**< The inactive value is 0 */
	ACMP_INACTVAL_HIGH = 0x1U,	/**< The inactive value is 1 */
} acmp_inactval_t;

/**
  * @brief which edges set up interrupt
  */
typedef enum {
	ACMP_EDGE_NONE = 0x0U,	/**< Disable EDGE interrupt */
	ACMP_EDGE_FALL = 0x1U,	/**< Falling edges set EDGE interrupt */
	ACMP_EDGE_RISE = 0x2U,	/**< rise edges set EDGE interrupt */
	ACMP_EDGE_ALL  = 0x3U,	/**< Falling edges and rise edges set EDGE interrupt */
} acmp_edge_t;

/**
  * @brief ACMP output function
  */
typedef enum {
	ACMP_OUT_DISABLE = 0x0U,	/**< Disable acmp output */
	ACMP_OUT_ENABLE  = 0x1U,	/**< Enable acmp output */
} acmp_out_func_t;

/**
  * @brief ACMP init structure definition
  */
typedef struct {
	acmp_mode_t mode;           	/**< ACMP operation mode */
	acmp_warm_time_t warm_time; 	/**< ACMP warm up time */
	acmp_hystsel_t hystsel;     	/**< ACMP hysteresis level */
	acmp_pos_input_t p_port;  	/**< ACMP positive port select */
	acmp_neg_input_t n_port;  	/**< ACMP negative port select */
	acmp_inactval_t inactval;   	/**< ACMP inavtive output value */
	type_func_t out_inv;		/**< ACMP output inverse */
	acmp_edge_t edge;           	/**< Select edges to set interrupt flag */
	uint8_t vdd_level;          	/**< Select scaling factor for CDD reference level, MAX is 63 */
} acmp_init_t;

/**
  * @brief  ACMP Handle Structure definition
  */
typedef struct acmp_handle_s {
	ACMP_TypeDef *perh;	/**< Register base address */
	acmp_init_t init;  	/**< ACMP required parameters */
	lock_state_t lock; 	/**< Locking object */

	void (*acmp_warmup_cplt_cbk)(struct acmp_handle_s *arg);	/**< ACMP warm-up complete callback */
	void (*acmp_edge_cplt_cbk)(struct acmp_handle_s *arg);  	/**< ACMP edge trigger callback */
} acmp_handle_t;
/**
  * @}
  */

/** @defgroup ACMP_Public_Macros ACMP Public Macros
  * @{
  */
#define ACMP_ENABLE(handle) 	(SET_BIT((handle)->perh->CON, ACMP_CON_EN_MSK))
#define ACMP_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CON, ACMP_CON_EN_MSK))
/**
  * @}
  */

/** @defgroup ACMP_Private_Macros   ACMP Private Macros
  * @{
  */
#define IS_ACMP_TYPE(x) 		(((x) == ACMP0) || \
                                         ((x) == ACMP1) || \
				         ((x) == ACMP2))
#define IS_ACMP_MODE_TYPE(x)		(((x) == ACMP_ULTRA_LOW_POWER) || \
					 ((x) == ACMP_LOW_POWER)       || \
					 ((x) == ACMP_MIDDLE_POWER)    || \
					 ((x) == ACMP_HIGH_POWER))
#define IS_ACMP_IT_TYPE(x) 		(((x) == ACMP_IT_EDGE)  || \
				         ((x) == ACMP_IT_WARMUP))
#define IS_ACMP_FLAG_TYPE(x) 		(((x) == ACMP_FLAG_EDGE) || \
				         ((x) == ACMP_FLAG_WARMUP))
#define IS_ACMP_STATUS_TYPE(x) 	        (((x) == ACMP_STATUS_ACT) || \
				         ((x) == ACMP_STATUS_OUT))
#define IS_ACMP_POS_INPUT_TYPE(x) 	(((x) == ACMP_POS_CH0) || \
				         ((x) == ACMP_POS_CH1) || \
				         ((x) == ACMP_POS_CH2) || \
				         ((x) == ACMP_POS_CH3) || \
				         ((x) == ACMP_POS_CH4) || \
				         ((x) == ACMP_POS_CH5) || \
				         ((x) == ACMP_POS_CH6) || \
				         ((x) == ACMP_POS_CH7))
#define IS_ACMP_NEG_INPUT_TYPE(x) 	(((x) == ACMP_NEG_CH0)  || \
				         ((x) == ACMP_NEG_CH1)  || \
				         ((x) == ACMP_NEG_CH2)  || \
				         ((x) == ACMP_NEG_CH3)  || \
				         ((x) == ACMP_NEG_CH4)  || \
				         ((x) == ACMP_NEG_CH5)  || \
				         ((x) == ACMP_NEG_CH6)  || \
				         ((x) == ACMP_NEG_CH7)  || \
				         ((x) == ACMP_NEG_1V25) || \
				         ((x) == ACMP_NEG_2V5)  || \
				         ((x) == ACMP_NEG_VDD))
#define IS_ACMP_WARM_UP_TIME_TYPE(x)    (((x) == ACMP_4_PCLK)   || \
				         ((x) == ACMP_8_PCLK)   || \
				         ((x) == ACMP_16_PCLK)  || \
				         ((x) == ACMP_32_PCLK)  || \
				         ((x) == ACMP_64_PCLK)  || \
				         ((x) == ACMP_128_PCLK) || \
				         ((x) == ACMP_256_PCLK) || \
				         ((x) == ACMP_512_PCLK))
#define IS_ACMP_HYSTSEL_TYPE(x)         (((x) == ACMP_HYST_0)  || \
				         ((x) == ACMP_HYST_15) || \
				         ((x) == ACMP_HYST_22) || \
				         ((x) == ACMP_HYST_29) || \
				         ((x) == ACMP_HYST_36) || \
				         ((x) == ACMP_HYST_43) || \
				         ((x) == ACMP_HYST_50) || \
				         ((x) == ACMP_HYST_57))
#define IS_ACMP_INACTVAL_TYPE(x) 	(((x) == ACMP_INACTVAL_LOW) || \
				         ((x) == ACMP_INACTVAL_HIGH))
#define IS_ACMP_EDGE_TYPE(x) 	        (((x) == ACMP_EDGE_NONE) || \
					 ((x) == ACMP_EDGE_FALL) || \
				         ((x) == ACMP_EDGE_RISE) || \
					 ((x) == ACMP_EDGE_ALL))
/**
  * @}
  */

/** @addtogroup ACMP_Public_Functions
  * @{
  */

/** @addtogroup ACMP_Public_Functions_Group1
  * @{
  */
ald_status_t ald_acmp_init(acmp_handle_t *hperh);
/**
  * @}
  */
/** @addtogroup ACMP_Public_Functions_Group2
  * @{
  */
void ald_acmp_interrupt_config(acmp_handle_t *hperh, acmp_it_t it, type_func_t state);
it_status_t ald_acmp_get_it_status(acmp_handle_t *hperh, acmp_it_t it);
flag_status_t ald_acmp_get_flag_status(acmp_handle_t *hperh, acmp_flag_t flag);
flag_status_t ald_acmp_get_mask_flag_status(acmp_handle_t *hperh, acmp_flag_t flag);
void ald_acmp_clear_flag_status(acmp_handle_t *hperh, acmp_flag_t flag);
/**
  * @}
  */
/** @addtogroup ACMP_Public_Functions_Group3
  * @{
  */
void ald_acmp_irq_handler(acmp_handle_t *hperh);
void ald_acmp_out_config(acmp_handle_t *hperh, type_func_t state);
uint8_t ald_acmp_out_result(acmp_handle_t *hperh);
flag_status_t ald_acmp_get_status(acmp_handle_t *hperh, acmp_status_t status);
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
#endif
#endif
