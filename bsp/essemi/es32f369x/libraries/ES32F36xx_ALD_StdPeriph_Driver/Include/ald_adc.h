/**
  ******************************************************************************
 * @file    ald_adc.h
 * @brief   Header file of ADC Module library.
 *
 * @version V1.0
 * @date    28 Jun 2019
 * @author  AE Team
 * @note
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 ******************************************************************************
 */

#ifndef __ALD_ADC_H__
#define __ALD_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"
#include "ald_dma.h"
#include "ald_pis.h"
#include "ald_timer.h"

/** @addtogroup ES32FXXX_ALD
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
	ADC_STATE_RESET    = 0x0U,	/**< ADC not yet initialized or disabled */
	ADC_STATE_READY    = 0x1U,	/**< ADC peripheral ready for use */
	ADC_STATE_BUSY     = 0x2U,	/**< ADC is busy to internal process */
	ADC_STATE_TIMEOUT  = 0x4U,	/**< TimeOut occurrence */
	ADC_STATE_ERROR    = 0x8U,	/**< Internal error occurrence */
	ADC_STATE_BUSY_N   = 0x10U,	/**< Normal channel busy */
	ADC_STATE_BUSY_I   = 0x20U,	/**< Insert channel busy */
	ADC_STATE_BUSY_WDG = 0x40U,	/**< Insert channel busy */
} adc_state_t;

/**
  *@brief ADC Error Code
  */
typedef enum {
	ADC_ERROR_NONE     = 0x0U,	/**< No error */
	ADC_ERROR_INTERNAL = 0x1U,	/**< ADC IP internal error*/
	ADC_ERROR_OVR      = 0x2U,	/**< Overrun error */
	ADC_ERROR_DMA      = 0x4U, 	/**< DMA transfer error */
} adc_error_t;

/**
  *@brief ADC data alignment
  */
typedef enum {
	ADC_DATAALIGN_RIGHT = 0x0U,	/**< ADC data alignment right */
	ADC_DATAALIGN_LEFT  = 0x1U,	/**< ADC data alignment left */
} adc_align_t;

/**
  *@brief ADC config  hannal trigger the EOC IT mode
  */
typedef enum {
	ADC_NCHESEL_MODE_ALL = 0x0U,	/**< ADC set RCHE after convert sequence finish */
	ADC_NCHESEL_MODE_ONE = 0x1U,	/**< ADC set RCHE after one convert finish */
} adc_nchesel_t;

/**
  *@brief  ADC channels
  */
typedef enum {
	ADC_CHANNEL_0  = 0x0U, 	/**< ADC channel 0 */
	ADC_CHANNEL_1  = 0x1U, 	/**< ADC channel 1 */
	ADC_CHANNEL_2  = 0x2U, 	/**< ADC channel 2 */
	ADC_CHANNEL_3  = 0x3U, 	/**< ADC channel 3 */
	ADC_CHANNEL_4  = 0x4U, 	/**< ADC channel 4 */
	ADC_CHANNEL_5  = 0x5U, 	/**< ADC channel 5 */
	ADC_CHANNEL_6  = 0x6U, 	/**< ADC channel 6 */
	ADC_CHANNEL_7  = 0x7U, 	/**< ADC channel 7 */
	ADC_CHANNEL_8  = 0x8U, 	/**< ADC channel 8 */
	ADC_CHANNEL_9  = 0x9U, 	/**< ADC channel 9 */
	ADC_CHANNEL_10 = 0xAU, 	/**< ADC channel 10 */
	ADC_CHANNEL_11 = 0xBU, 	/**< ADC channel 11 */
	ADC_CHANNEL_12 = 0xCU, 	/**< ADC channel 12 */
	ADC_CHANNEL_13 = 0xDU, 	/**< ADC channel 13 */
	ADC_CHANNEL_14 = 0xEU, 	/**< ADC channel 14 */
	ADC_CHANNEL_15 = 0xFU, 	/**< ADC channel 15 */
	ADC_CHANNEL_16 = 0x10U,	/**< ADC channel 16 */
	ADC_CHANNEL_17 = 0x11U,	/**< ADC channel 17 */
	ADC_CHANNEL_18 = 0x12U,	/**< ADC channel 18 */
} adc_channel_t;

/**
  *@brief  ADC sampling times
  */
typedef enum {
	ADC_SAMPLETIME_1  = 0x0U,	/**< ADC sampling times 1 clk */
	ADC_SAMPLETIME_2  = 0x1U,	/**< ADC sampling times 2 clk */
	ADC_SAMPLETIME_4  = 0x2U,	/**< ADC sampling times 4 clk */
	ADC_SAMPLETIME_15 = 0x3U,	/**< ADC sampling times 15 clk */
} adc_samp_t;

/**
  *@brief   ADC index channel in normal group
  */
typedef enum {
	ADC_NCH_IDX_1  = 0x1U, 	/**< ADC normal channel index 1 */
	ADC_NCH_IDX_2  = 0x2U, 	/**< ADC normal channel index 2 */
	ADC_NCH_IDX_3  = 0x3U, 	/**< ADC normal channel index 3 */
	ADC_NCH_IDX_4  = 0x4U, 	/**< ADC normal channel index 4 */
	ADC_NCH_IDX_5  = 0x5U, 	/**< ADC normal channel index 5 */
	ADC_NCH_IDX_6  = 0x6U, 	/**< ADC normal channel index 6 */
	ADC_NCH_IDX_7  = 0x7U, 	/**< ADC normal channel index 7 */
	ADC_NCH_IDX_8  = 0x8U, 	/**< ADC normal channel index 8 */
	ADC_NCH_IDX_9  = 0x9U, 	/**< ADC normal channel index 9 */
	ADC_NCH_IDX_10 = 0xAU, 	/**< ADC normal channel index 10 */
	ADC_NCH_IDX_11 = 0xBU, 	/**< ADC normal channel index 11 */
	ADC_NCH_IDX_12 = 0xCU, 	/**< ADC normal channel index 12 */
	ADC_NCH_IDX_13 = 0xDU, 	/**< ADC normal channel index 13 */
	ADC_NCH_IDX_14 = 0xEU, 	/**< ADC normal channel index 14 */
	ADC_NCH_IDX_15 = 0xFU, 	/**< ADC normal channel index 15 */
	ADC_NCH_IDX_16 = 0x10U,	/**< ADC normal channel index 16 */
} adc_nch_idx_t;

/**
  * @brief ADC index channel in insert group
  */
typedef enum {
	ADC_ICH_IDX_1 = 0x1U,	/**< ADC insert channel index 1 */
	ADC_ICH_IDX_2 = 0x2U,	/**< ADC insert channel index 2 */
	ADC_ICH_IDX_3 = 0x3U,	/**< ADC insert channel index 3 */
	ADC_ICH_IDX_4 = 0x4U,	/**< ADC insert channel index 4 */
} adc_ich_idx_t;

/**
  * @brief ADC analog watchdog mode
  */
typedef enum {
	ADC_ANAWTD_NONE       = 0x0U,     	/**< No watch dog */
	ADC_ANAWTD_SING_NM    = 0x800200U,	/**< One normal channel watch dog */
	ADC_ANAWTD_SING_IST   = 0x400200U,	/**< One insert channel Injec watch dog */
	ADC_ANAWTD_SING_NMIST = 0xC00200U,	/**< One normal and insert channel watch dog */
	ADC_ANAWTD_ALL_NM     = 0x800000U,	/**< All normal channel watch dog */
	ADC_ANAWTD_ALL_IST    = 0x400000U,	/**< All insert channel watch dog */
	ADC_ANAWTD_ALL_NMIST  = 0xC00000U,	/**< All normal and insert channel watch dog */
} adc_ana_wdg_t;

/**
  * @brief ADC Event type
  */
typedef enum {
	ADC_AWD_EVENT = (1U << 0),	/**< ADC analog watch dog event */
} adc_event_type_t;

/**
  * @brief ADC interrupts definition
  */
typedef enum {
	ADC_IT_NCH = (1U << 5), 	/**< ADC it normal */
	ADC_IT_AWD = (1U << 6), 	/**< ADC it awd */
	ADC_IT_ICH = (1U << 7), 	/**< ADC it insert */
	ADC_IT_OVR = (1U << 26),	/**< ADC it overring */
} adc_it_t;

/**
  * @brief ADC flags definition
  */
typedef enum {
	ADC_FLAG_AWD  = (1U << 0),	/**<ADC flag awd */
	ADC_FLAG_NCH  = (1U << 1),	/**<ADC flag normal mode complete */
	ADC_FLAG_ICH  = (1U << 2),	/**<ADC flag insert mode complete*/
	ADC_FLAG_OVR  = (1U << 3),	/**<ADC flag ovr */
	ADC_FLAG_NCHS = (1U << 8),	/**<ADC flag normal start */
	ADC_FLAG_ICHS = (1U << 9),	/**<ADC flag insert start */
} adc_flag_t;

/**
  * @brief ADC CLD DIV definition
  */
typedef enum {
	ADC_CKDIV_1   = 0x0U,	/**< ADC CLK DIV 1 */
	ADC_CKDIV_2   = 0x1U,	/**< ADC CLK DIV 2 */
	ADC_CKDIV_4   = 0x2U,	/**< ADC CLK DIV 4 */
	ADC_CKDIV_8   = 0x3U,	/**< ADC CLK DIV 8 */
	ADC_CKDIV_16  = 0x4U,	/**< ADC CLK DIV 16 */
	ADC_CKDIV_32  = 0x5U,	/**< ADC CLK DIV 32 */
	ADC_CKDIV_64  = 0x6U,	/**< ADC CLK DIV 64 */
	ADC_CKDIV_128 = 0x7U,	/**< ADC CLK DIV 128 */
} adc_clk_div_t;

/**
  * @brief ADC negative reference voltage definition
  */
typedef enum {
	ADC_NEG_REF_VSS   = 0x0U,	/**< ADC negative regerence voltage vss */
	ADC_NEG_REF_VREFN = 0x1U,	/**< ADC negative regerence voltage vrefn */
} adc_neg_ref_t;

/**
  * @brief ADC positive reference voltage definition
  */
typedef enum {
	ADC_POS_REF_VDD        = 0x0U,	/**< ADC positive reference is VDD */
	ADC_POS_REF_2V         = 0x1U,	/**< ADC positive reference is 2V internal voltage */
	ADC_POS_REF_VREEFP     = 0x2U,	/**< ADC positive reference is VREEFP */
	ADC_POS_REF_VREEFP_BUF = 0x3U,	/**< ADC positive reference is VREEFP BUFFER */
} adc_pos_ref_t;

/**
  * @brief ADC numbers of normal conversion channals
  */
typedef enum {
	ADC_NCH_NR_1  = 0x0U,	/**< ADC number of normal conversion 1 */
	ADC_NCH_NR_2  = 0x1U,	/**< ADC number of normal conversion 2 */
	ADC_NCH_NR_3  = 0x2U,	/**< ADC number of normal conversion 3 */
	ADC_NCH_NR_4  = 0x3U,	/**< ADC number of normal conversion 4 */
	ADC_NCH_NR_5  = 0x4U,	/**< ADC number of normal conversion 5 */
	ADC_NCH_NR_6  = 0x5U,	/**< ADC number of normal conversion 6 */
	ADC_NCH_NR_7  = 0x6U,	/**< ADC number of normal conversion 7 */
	ADC_NCH_NR_8  = 0x7U,	/**< ADC number of normal conversion 8 */
	ADC_NCH_NR_9  = 0x8U,	/**< ADC number of normal conversion 9 */
	ADC_NCH_NR_10 = 0x9U,	/**< ADC number of normal conversion 10 */
	ADC_NCH_NR_11 = 0xAU,	/**< ADC number of normal conversion 11 */
	ADC_NCH_NR_12 = 0xBU,	/**< ADC number of normal conversion 12 */
	ADC_NCH_NR_13 = 0xCU,	/**< ADC number of normal conversion 13 */
	ADC_NCH_NR_14 = 0xDU,	/**< ADC number of normal conversion 14 */
	ADC_NCH_NR_15 = 0xEU,	/**< ADC number of normal conversion 15 */
	ADC_NCH_NR_16 = 0xFU,	/**< ADC number of normal conversion 16 */
} adc_nch_nr_t;

/**
  * @brief ADC numbers of insert conversion channals
  */
typedef enum {
	ADC_ICH_NR_1 = 0x0U,	/**< ADC number of insert conversion 1 */
	ADC_ICH_NR_2 = 0x1U,	/**< ADC number of insert conversion 2 */
	ADC_ICH_NR_3 = 0x2U,	/**< ADC number of insert conversion 3 */
	ADC_ICH_NR_4 = 0x3U,	/**< ADC number of insert conversion 4 */
} adc_ich_nr_t;

/**
  * @brief ADC discontinuous mode choose
  */
typedef enum {
	ADC_ALL_DISABLE = 0x0U,	/**< ADC discontinuous mode all disable */
	ADC_NCH_DISC_EN = 0x1U,	/**< ADC normal channel discontinuous mode enable */
	ADC_ICH_DISC_EN = 0x2U,	/**< ADC insert channel discontinuous mode enable */
} adc_disc_mode_t;

/**
  * @brief ADC numbers of channals in discontinuous conversion mode
  */
typedef enum {
	ADC_DISC_NR_1 = 0x0U,	/**< ADC number of discontinuous conversion 1 */
	ADC_DISC_NR_2 = 0x1U,	/**< ADC number of discontinuous conversion 2 */
	ADC_DISC_NR_3 = 0x2U,	/**< ADC number of discontinuous conversion 3 */
	ADC_DISC_NR_4 = 0x3U,	/**< ADC number of discontinuous conversion 4 */
	ADC_DISC_NR_5 = 0x4U,	/**< ADC number of discontinuous conversion 5 */
	ADC_DISC_NR_6 = 0x5U,	/**< ADC number of discontinuous conversion 6 */
	ADC_DISC_NR_7 = 0x6U,	/**< ADC number of discontinuous conversion 7 */
	ADC_DISC_NR_8 = 0x7U,	/**< ADC number of discontinuous conversion 8 */
} adc_disc_nr_t;

/**
  * @brief ADC resolution of conversion
  */
typedef enum {
	ADC_CONV_BIT_6  = 0x0U,	/**< ADC resolution of conversion 6 */
	ADC_CONV_BIT_8  = 0x1U,	/**< ADC resolution of conversion 8 */
	ADC_CONV_BIT_10 = 0x2U,	/**< ADC resolution of conversion 10 */
	ADC_CONV_BIT_12 = 0x3U,	/**< ADC resolution of conversion 12 */
} adc_conv_bit_t;

/**
  * @brief ADC external trigger mode choose
  */
typedef enum {
	ADC_ETS_DISABLE   = 0x0U,	/**< ADC external trigger function disable */
	ADC_ETS_RISE      = 0x1U,	/**< rise edge trigger ADC */
	ADC_ETS_FALL      = 0x2U,	/**< fall edge trigger ADC */
	ADC_ETS_RISE_FALL = 0x3U,	/**< both rise and fall edge trigger ADC */
} adc_ets_t;

/**
  * @brief ADC trigger conversion mode
  */


/**
  * @brief  Structure definition of ADC and normal group initialization
  */
typedef struct {
	adc_align_t align;		/**< Specifies ADC data alignment */
	type_func_t scan;         	/**< Choose scan mode enable or not */
	type_func_t cont;       	/**< Choose continuous mode enable or not */
	adc_nch_nr_t nch_nr;  		/**< Length of normal ranks will be converted */
	adc_ich_nr_t ich_nr;  		/**< Length of insert ranks will be converted */
	adc_disc_mode_t disc;    	/**< Discontinuous mode enable or not */
	adc_disc_nr_t disc_nr;		/**< Number of discontinuous conversions channel */
	adc_conv_bit_t data_bit;   	/**< The precision of conversion */
	adc_clk_div_t div;		/**< ADCCLK divider */
	adc_nchesel_t nche_sel;		/**< Trigger the NCHE FALG mode */
	adc_neg_ref_t n_ref;    	/**< The negative reference voltage*/
	adc_pos_ref_t p_ref;    	/**< The positive reference voltage*/
} adc_init_t;

/**
  * @brief  Structure definition of ADC channel for normal group
  */
typedef struct {
	adc_channel_t ch;	/**< The channel to configure into ADC normal group */
	adc_nch_idx_t idx;	/**< The rank in the normal group sequencer */
	adc_samp_t samp;	/**< Sampling time value to be set */
} adc_nch_conf_t;

/**
  * @brief  ADC Configuration analog watchdog definition
  */
typedef struct {
	adc_ana_wdg_t mode;	/**< Configures the ADC analog watchdog mode*/
	adc_channel_t ch;	/**< Selects which ADC channel to monitor by analog watchdog */
	type_func_t interrupt;	/**< Whether the analog watchdog is configured in interrupt */
	uint32_t high_thrd;	/**< The ADC analog watchdog High threshold value. */
	uint32_t low_thrd;	/**< The ADC analog watchdog Low threshold value. */
} adc_analog_wdg_conf_t;

/**
  * @brief  ADC Configuration insert Channel structure definition
  */
typedef struct {
	adc_channel_t ch;	/**< Selection of ADC channel to configure */
	adc_ich_idx_t idx;	/**< Rank in the insert group sequencer */
	adc_samp_t samp;	/**< Sampling time value for selected channel */
	uint32_t offset;	/**< The offset about converted data */
	adc_ich_nr_t nr;	/**< The number of insert ranks */
	type_func_t auto_m;	/**< insert sequence's auto function */
} adc_ich_conf_t;

/**
  * @brief  ADC handle Structure definition
  */
typedef struct adc_handle_s {
	ADC_TypeDef *perh;			/**< Register base address */
	adc_init_t init;			/**< ADC required parameters */
#ifdef ALD_DMA
	dma_handle_t hdma;			/**< Pointer DMA Handler */
	pis_handle_t hpis;			/**< Pointer PIS Handler for connect adc and dma */
#endif
	lock_state_t lock;			/**< ADC locking object */
	adc_state_t state;			/**< ADC communication state  */
	adc_error_t error_code;			/**< ADC Error code */

	void (*normal_cplt_cbk)( struct adc_handle_s *arg);  	/**< Regluar Conversion complete callback */
	void (*insert_cplt_cbk)( struct adc_handle_s *arg);  	/**< insert Conversion complete callback */
	void (*wdg_cbk)( struct adc_handle_s *arg);		/**< Level out of window callback */
	void (*error_cbk)(struct adc_handle_s *arg);      	/**< adc error callback */
	void (*ovr_cbk)(struct adc_handle_s *arg);	      	/**< adc ovr callback */
} adc_handle_t;

/**
  * @brief Timer trigger adc config structure definition
  */
typedef struct {
	uint32_t time;		/**< Timer period time uint: us */	
	uint16_t size;		/**< Adc convert times */	
	uint16_t *buf;		/**< Convert data buffer */	
	adc_neg_ref_t n_ref;	/**< The negative reference voltage for adc*/
	adc_pos_ref_t p_ref;	/**< The positive reference voltage for adc*/
	adc_channel_t adc_ch;	/**< Adc channel */	
	uint8_t dma_ch;		/**< Dma channel */	
	TIMER_TypeDef *p_timer;	/**< Timer peripheral */	
	ADC_TypeDef *p_adc;	/**< Adc peripheral */	
	void (*cplt_cbk)( struct adc_handle_s *arg);	/**< Conversion complete callback */

	/* private variable */
	lock_state_t lock;	/**< Locking object */
	pis_handle_t h_pis;	/**< Handle of PIS module */
	dma_handle_t h_dma;	/**< Handle of DMA module */
	timer_handle_t h_timer;	/**< Handle of TIMER module */
	adc_handle_t h_adc;	/**< Handle of ADC module */
	adc_nch_conf_t config;	/**< Struct for chanel configure */
	adc_ich_conf_t i_config;  /**< Struct for insert channel configure */
} adc_timer_config_t;
/**
  * @}
  */

/** @defgroup ADC_Public_Macros ADC Public Macros
  * @{
  */
#define ADC_ENABLE(handle) 		(SET_BIT((handle)->perh->CON1, ADC_CON1_ADCEN_MSK))
#define ADC_DISABLE(handle) 		(CLEAR_BIT((handle)->perh->CON1, ADC_CON1_ADCEN_MSK))
#define ADC_NH_TRIG_BY_SOFT(handle)	(SET_BIT((handle)->perh->CON1, ADC_CON1_NCHTRG_MSK))
#define ADC_IH_TRIG_BY_SOFT(handle)	(SET_BIT((handle)->perh->CON1, ADC_CON1_ICHTRG_MSK))
#define ADC_RESET_HANDLE_STATE(handle)	((handle)->state = ADC_STATE_RESET)
#define ADC_VREF_OUT_ENABLE(handle)	(SET_BIT((handle)->perh->CCR, ADC_CCR_VREFOEN_MSK))
#define ADC_VREF_OUT_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CCR, ADC_CCR_VREFOEN_MSK))
#define ADC_NETS_ENABLE(handle, mode)	(MODIFY_REG((handle)->perh->CON1, ADC_CON1_NETS_MSK, (mode) << ADC_CON1_NETS_POSS))
#define ADC_IETS_ENABLE(handle, mode)	(MODIFY_REG((handle)->perh->CON1, ADC_CON1_IETS_MSK, (mode) << ADC_CON1_IETS_POSS))
#define ADC_NETS_DISABLE(handle)	(MODIFY_REG((handle)->perh->CON1, ADC_CON1_NETS_MSK, 0 << ADC_CON1_NETS_POSS))
#define ADC_IETS_DISABLE(handle)	(MODIFY_REG((handle)->perh->CON1, ADC_CON1_IETS_MSK, 0 << ADC_CON1_IETS_POSS))
#define ADC_SPEED_HIGH_ENABLE(handle)	(SET_BIT((handle)->perh->CCR, ADC_CCR_PWRMODSEL_MSK))
#define ADC_SPEED_HIGH_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CCR, ADC_CCR_PWRMODSEL_MSK))
#define ADC_CALIBRATE_ENABLE(handle)	(SET_BIT((handle)->perh->CCR, ADC_CCR_TRMEN_MSK))
#define ADC_CALIBRATE_DISABLE(handle)	(CLEAR_BIT((handle)->perh->CCR, ADC_CCR_TRMEN_MSK))
/**
  * @}
  */

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
#define IS_ADC_ICH_IDX_TYPE(x)			((x) <= ADC_ICH_IDX_4)
#define IS_ADC_NCH_IDX_TYPE(x)			((x) <= ADC_NCH_IDX_16)
#define IS_ADC_SAMPLING_TIMES_TYPE(x)		(((x) == ADC_SAMPLETIME_1) || \
                                                 ((x) == ADC_SAMPLETIME_2) || \
					         ((x) == ADC_SAMPLETIME_4) || \
					         ((x) == ADC_SAMPLETIME_15))
#define IS_ADC_CHANNELS_TYPE(x)			((x) <= ADC_CHANNEL_18)
#define IS_ADC_DATA_ALIGN_TYPE(x)		(((x) == ADC_DATAALIGN_RIGHT) || \
                                                 ((x) == ADC_DATAALIGN_LEFT))
#define IS_ADC_ANALOG_WTD_MODE_TYPE(x)  	(((x) == ADC_ANAWTD_NONE)       || \
						 ((x) == ADC_ANAWTD_SING_NM)    || \
						 ((x) == ADC_ANAWTD_SING_IST)   || \
						 ((x) == ADC_ANAWTD_SING_NMIST) || \
						 ((x) == ADC_ANAWTD_ALL_NM)     || \
						 ((x) == ADC_ANAWTD_ALL_IST)    || \
						 ((x) == ADC_ANAWTD_ALL_NMIST))
#define IS_ADC_IT_TYPE(x)			(((x) == ADC_IT_NCH) || \
						 ((x) == ADC_IT_AWD) || \
						 ((x) == ADC_IT_ICH) ||  \
						 ((x) == ADC_IT_OVR ))
#define IS_ADC_FLAGS_TYPE(x)			(((x) == ADC_FLAG_AWD)  || \
						 ((x) == ADC_FLAG_NCH)  || \
						 ((x) == ADC_FLAG_ICH)  || \
						 ((x) == ADC_FLAG_OVR)  || \
						 ((x) == ADC_FLAG_NCHS) || \
						 ((x) == ADC_FLAG_ICHS))
#define IS_ADC_CLK_DIV_TYPE(x)			(((x) == ADC_CKDIV_1)   || \
						 ((x) == ADC_CKDIV_2)   || \
						 ((x) == ADC_CKDIV_4)   || \
						 ((x) == ADC_CKDIV_8)   || \
						 ((x) == ADC_CKDIV_16)  || \
						 ((x) == ADC_CKDIV_32)  || \
						 ((x) == ADC_CKDIV_64)  || \
						 ((x) == ADC_CKDIV_128))
#define IS_ADC_NEG_REF_VOLTAGE_TYPE(x)		(((x) == ADC_NEG_REF_VSS ) || \
                                                 ((x) == ADC_NEG_REF_VREFN ))
#define IS_POS_REF_VOLTAGE_TYPE(x)		(((x) == ADC_POS_REF_VDD)    || \
						 ((x) == ADC_POS_REF_2V) || \
						 ((x) == ADC_POS_REF_VREEFP) || \
						 ((x) == ADC_POS_REF_VREEFP_BUF))
#define IS_ADC_NCH_NR_TYPE(x)			((x) <= ADC_NCH_NR_16)
#define IS_ADC_ICH_NR_TYPE(x)			((x) <= ADC_ICH_NR_4)
#define IS_ADC_DISC_NR_TYPE(x)			((x) <= ADC_DISC_NR_8)
#define IS_ADC_CONV_BIT_TYPE(x)			(((x) == ADC_CONV_BIT_12) || \
                                                 ((x) == ADC_CONV_BIT_6)  || \
						 ((x) == ADC_CONV_BIT_8)  || \
						 ((x) == ADC_CONV_BIT_10))
#define IS_ADC_TYPE(x) 				(((x) == ADC0) || \
						 ((x) == ADC1))
#define IS_ADC_NCHESEL_MODE_TYPE(x)		(((x) == ADC_NCHESEL_MODE_ALL) || \
						 ((x) == ADC_NCHESEL_MODE_ONE))
#define IS_ADC_EVENT_TYPE(x)			((x) == ADC_AWD_EVENT)
#define IS_ADC_IST_OFFSET_TYPE(x)		((x) <= 0xfff)
#define IS_HTR_TYPE(x)				((x) <= 0xfff)
#define IS_LTR_TYPE(x)				((x) <= 0xfff)
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions
  * @{
  */

/** @addtogroup ADC_Public_Functions_Group1
  * @{
  */
ald_status_t ald_adc_init(adc_handle_t *hperh);
ald_status_t ald_adc_reset(adc_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions_Group2
  * @{
  */
ald_status_t ald_adc_normal_start(adc_handle_t *hperh);
ald_status_t ald_adc_normal_stop(adc_handle_t *hperh);
ald_status_t ald_adc_normal_poll_for_conversion(adc_handle_t *hperh, uint32_t timeout);
ald_status_t ald_adc_poll_for_event(adc_handle_t *hperh, adc_event_type_t event_type, uint32_t timeout);
ald_status_t ald_adc_normal_start_by_it(adc_handle_t *hperh);
ald_status_t ald_adc_normal_stop_by_it(adc_handle_t *hperh);
#ifdef ALD_DMA
ald_status_t ald_adc_start_by_dma(adc_handle_t *hperh, uint16_t *buf, uint16_t size, uint8_t channel);
ald_status_t ald_adc_stop_by_dma(adc_handle_t *hperh, uint8_t channel);
ald_status_t ald_adc_timer_trigger_adc_by_dma(adc_timer_config_t *config);
ald_status_t ald_adc_timer_trigger_insert(adc_timer_config_t *config);
#endif
uint32_t ald_adc_normal_get_value(adc_handle_t *hperh);
ald_status_t ald_adc_insert_start(adc_handle_t *hperh);
ald_status_t ald_adc_insert_stop(adc_handle_t *hperh);
ald_status_t ald_adc_insert_poll_for_conversion(adc_handle_t *hperh, uint32_t timeout);
ald_status_t ald_adc_insert_start_by_it(adc_handle_t *hperh);
ald_status_t ald_adc_insert_stop_by_it(adc_handle_t *hperh);
uint32_t ald_adc_insert_get_value(adc_handle_t *hperh, adc_ich_idx_t ih_rank);
void ald_adc_irq_handler(adc_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions_Group3
  * @{
  */
ald_status_t ald_adc_normal_channel_config(adc_handle_t *hperh, adc_nch_conf_t *config);
ald_status_t ald_adc_insert_channel_config(adc_handle_t *hperh, adc_ich_conf_t *config);
ald_status_t ald_adc_analog_wdg_config(adc_handle_t *hperh, adc_analog_wdg_conf_t *config);
void ald_adc_interrupt_config(adc_handle_t *hperh, adc_it_t it, type_func_t state);
it_status_t ald_adc_get_it_status(adc_handle_t *hperh, adc_it_t it);
flag_status_t ald_adc_get_flag_status(adc_handle_t *hperh, adc_flag_t flag);
void ald_adc_clear_flag_status(adc_handle_t *hperh, adc_flag_t flag);
/**
  * @}
  */

/** @addtogroup ADC_Public_Functions_Group4
  * @{
  */
uint32_t ald_adc_get_state(adc_handle_t *hperh);
uint32_t ald_adc_get_error(adc_handle_t *hperh);
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

#endif /* __ALD_ADC_H */
