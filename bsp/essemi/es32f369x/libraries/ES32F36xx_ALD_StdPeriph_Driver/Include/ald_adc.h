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
	ADC_STATE_RESET         = 0x0,    	/**< ADC not yet initialized or disabled */
	ADC_STATE_READY         = 0x1,    	/**< ADC peripheral ready for use */
	ADC_STATE_BUSY_INTERNAL = 0x2,    	/**< ADC is busy to internal process */
	ADC_STATE_TIMEOUT       = 0x4,    	/**< TimeOut occurrence */
	ADC_STATE_ERROR         = 0x10,   	/**< Internal error occurrence */
	ADC_STATE_NM_BUSY       = 0x100,  	/**< Conversion on group normal is ongoing or can occur */
	ADC_STATE_NM_EOC        = 0x200,  	/**< Conversion data available on group normal */
	ADC_STATE_IST_BUSY      = 0x1000, 	/**< Conversion on group insert is ongoing or can occur */
	ADC_STATE_IST_EOC       = 0x2000, 	/**< Conversion data available on group insert */
	ADC_STATE_AWD           = 0x10000,	/**< Out-of-window occurrence of analog watchdog */
} adc_state_t;

/**
  *@brief ADC Error Code
  */
typedef enum {
	ADC_ERROR_NONE     = 0x0,	/**< No error */
	ADC_ERROR_INTERNAL = 0x1,	/**< ADC IP internal error*/
	ADC_ERROR_OVR      = 0x2,	/**< Overrun error */
	ADC_ERROR_DMA      = 0x4, 	/**< DMA transfer error */
} adc_error_t;

/**
  *@brief ADC data alignment
  */
typedef enum {
	ADC_DATAALIGN_RIGHT = 0x0,	/**< ADC data alignment right */
	ADC_DATAALIGN_LEFT  = 0x1,	/**< ADC data alignment left */
} adc_align_t;

/**
  *@brief ADC config  hannal trigger the EOC IT mode
  */
typedef enum {
	ADC_NCHESEL_MODE_ALL = 0x0,	/**< ADC set RCHE after convert sequence finish */
	ADC_NCHESEL_MODE_ONE = 0x1,	/**< ADC set RCHE after one convert finish */
} adc_nchesel_t;

/**
  *@brief  ADC channels
  */
typedef enum {
	ADC_CHANNEL_0  = 0x0, 	/**< ADC channel 0 */
	ADC_CHANNEL_1  = 0x1, 	/**< ADC channel 1 */
	ADC_CHANNEL_2  = 0x2, 	/**< ADC channel 2 */
	ADC_CHANNEL_3  = 0x3, 	/**< ADC channel 3 */
	ADC_CHANNEL_4  = 0x4, 	/**< ADC channel 4 */
	ADC_CHANNEL_5  = 0x5, 	/**< ADC channel 5 */
	ADC_CHANNEL_6  = 0x6, 	/**< ADC channel 6 */
	ADC_CHANNEL_7  = 0x7, 	/**< ADC channel 7 */
	ADC_CHANNEL_8  = 0x8, 	/**< ADC channel 8 */
	ADC_CHANNEL_9  = 0x9, 	/**< ADC channel 9 */
	ADC_CHANNEL_10 = 0xA, 	/**< ADC channel 10 */
	ADC_CHANNEL_11 = 0xB, 	/**< ADC channel 11 */
	ADC_CHANNEL_12 = 0xC, 	/**< ADC channel 12 */
	ADC_CHANNEL_13 = 0xD, 	/**< ADC channel 13 */
	ADC_CHANNEL_14 = 0xE, 	/**< ADC channel 14 */
	ADC_CHANNEL_15 = 0xF, 	/**< ADC channel 15 */
	ADC_CHANNEL_16 = 0x10,	/**< ADC channel 16 */
	ADC_CHANNEL_17 = 0x11,	/**< ADC channel 17 */
	ADC_CHANNEL_18 = 0x12,	/**< ADC channel 18 */
} adc_channel_t;

/**
  *@brief  ADC sampling times
  */
typedef enum {
	ADC_SAMPLETIME_1  = 0x0,	/**< ADC sampling times 1 clk */
	ADC_SAMPLETIME_2  = 0x1,	/**< ADC sampling times 2 clk */
	ADC_SAMPLETIME_4  = 0x2,	/**< ADC sampling times 4 clk */
	ADC_SAMPLETIME_15 = 0x3,	/**< ADC sampling times 15 clk */
} adc_samp_t;

/**
  *@brief   ADC rank into normal group
  */
typedef enum {
	ADC_NCH_RANK_1  = 0x1, 	/**< ADC normal channel rank 1 */
	ADC_NCH_RANK_2  = 0x2, 	/**< ADC normal channel rank 2 */
	ADC_NCH_RANK_3  = 0x3, 	/**< ADC normal channel rank 3 */
	ADC_NCH_RANK_4  = 0x4, 	/**< ADC normal channel rank 4 */
	ADC_NCH_RANK_5  = 0x5, 	/**< ADC normal channel rank 5 */
	ADC_NCH_RANK_6  = 0x6, 	/**< ADC normal channel rank 6 */
	ADC_NCH_RANK_7  = 0x7, 	/**< ADC normal channel rank 7 */
	ADC_NCH_RANK_8  = 0x8, 	/**< ADC normal channel rank 8 */
	ADC_NCH_RANK_9  = 0x9, 	/**< ADC normal channel rank 9 */
	ADC_NCH_RANK_10 = 0xA, 	/**< ADC normal channel rank 10 */
	ADC_NCH_RANK_11 = 0xB, 	/**< ADC normal channel rank 11 */
	ADC_NCH_RANK_12 = 0xC, 	/**< ADC normal channel rank 12 */
	ADC_NCH_RANK_13 = 0xD, 	/**< ADC normal channel rank 13 */
	ADC_NCH_RANK_14 = 0xE, 	/**< ADC normal channel rank 14 */
	ADC_NCH_RANK_15 = 0xF, 	/**< ADC normal channel rank 15 */
	ADC_NCH_RANK_16 = 0x10,	/**< ADC normal channel rank 16 */
} adc_nch_rank_t;

/**
  * @brief ADC rank into insert group
  */
typedef enum {
	ADC_ICH_RANK_1 = 0x1,	/**< ADC insert channel rank 1 */
	ADC_ICH_RANK_2 = 0x2,	/**< ADC insert channel rank 2 */
	ADC_ICH_RANK_3 = 0x3,	/**< ADC insert channel rank 3 */
	ADC_ICH_RANK_4 = 0x4,	/**< ADC insert channel rank 4 */
} adc_ich_rank_t;

/**
  * @brief ADC analog watchdog mode
  */
typedef enum {
	ADC_ANAWTD_NONE       = 0x0,     	/**< No watch dog */
	ADC_ANAWTD_SING_NM    = 0x800200,	/**< One normal channel watch dog */
	ADC_ANAWTD_SING_IST   = 0x400200,	/**< One inset channel Injec watch dog */
	ADC_ANAWTD_SING_NMIST = 0xC00200,	/**< One normal and inset channel watch dog */
	ADC_ANAWTD_ALL_NM     = 0x800000,	/**< All normal channel watch dog */
	ADC_ANAWTD_ALL_IST    = 0x400000,	/**< All inset channel watch dog */
	ADC_ANAWTD_ALL_NMIST  = 0xC00000,	/**< All normal and inset channel watch dog */
} adc_ana_wtd_t;

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
	ADC_IT_NCH  = (1U << 5), 	/**< ADC it normal */
	ADC_IT_AWD = (1U << 6), 	/**< ADC it awd */
	ADC_IT_ICH  = (1U << 7), 	/**< ADC it insert */
	ADC_IT_OVR = (1U << 26),	/**< ADC it overring */
} adc_it_t;

/**
  * @brief ADC flags definition
  */
typedef enum {
	ADC_FLAG_AWD  = (1U << 0),	/**<ADC flag awd */
	ADC_FLAG_NCH  = (1U << 1),	/**<ADC flag normal mode complete */
	ADC_FLAG_ICH  = (1U << 2),	/**<ADC flag inset mode complete*/
	ADC_FLAG_OVR  = (1U << 3),	/**<ADC flag ovr */
	ADC_FLAG_NCHS = (1U << 8),	/**<ADC flag normal start */
	ADC_FLAG_ICHS = (1U << 9),	/**<ADC flag inset start */
} adc_flag_t;

/**
  * @brief ADC CLD DIV definition
  */
typedef enum {
	ADC_CKDIV_1   = 0x0,	/**< ADC CLK DIV 1 */
	ADC_CKDIV_2   = 0x1,	/**< ADC CLK DIV 2 */
	ADC_CKDIV_4   = 0x2,	/**< ADC CLK DIV 4 */
	ADC_CKDIV_8   = 0x3,	/**< ADC CLK DIV 8 */
	ADC_CKDIV_16  = 0x4,	/**< ADC CLK DIV 16 */
	ADC_CKDIV_32  = 0x5,	/**< ADC CLK DIV 32 */
	ADC_CKDIV_64  = 0x6,	/**< ADC CLK DIV 64 */
	ADC_CKDIV_128 = 0x7,	/**< ADC CLK DIV 128 */
} adc_clk_div_t;

/**
  * @brief ADC negative reference voltage definition
  */
typedef enum {
	ADC_NEG_REF_VSS   = 0x0,	/**< ADC negative regerence voltage vss */
	ADC_NEG_REF_VREFN = 0x1,	/**< ADC negative regerence voltage vrefn */
} adc_neg_ref_t;

/**
  * @brief ADC positive reference voltage definition
  */
typedef enum {
	ADC_POS_REF_VDD        = 0x0,	/**< ADC positive reference is VDD */
	ADC_POS_REF_2_V        = 0x1,	/**< ADC positive reference is 2V internal voltage */
	ADC_POS_REF_VREEFP     = 0x2,	/**< ADC positive reference is VREEFP */
	ADC_POS_REF_VREEFP_BUF = 0x3,	/**< ADC positive reference is VREEFP BUFFER */
} adc_pos_ref_t;

/**
  * @brief ADC numbers of normal conversion channals
  */
typedef enum {
	ADC_NCH_LEN_1  = 0x0,	/**< ADC length of normal conversion 1 */
	ADC_NCH_LEN_2  = 0x1,	/**< ADC length of normal conversion 2 */
	ADC_NCH_LEN_3  = 0x2,	/**< ADC length of normal conversion 3 */
	ADC_NCH_LEN_4  = 0x3,	/**< ADC length of normal conversion 4 */
	ADC_NCH_LEN_5  = 0x4,	/**< ADC length of normal conversion 5 */
	ADC_NCH_LEN_6  = 0x5,	/**< ADC length of normal conversion 6 */
	ADC_NCH_LEN_7  = 0x6,	/**< ADC length of normal conversion 7 */
	ADC_NCH_LEN_8  = 0x7,	/**< ADC length of normal conversion 8 */
	ADC_NCH_LEN_9  = 0x8,	/**< ADC length of normal conversion 9 */
	ADC_NCH_LEN_10 = 0x9,	/**< ADC length of normal conversion 10 */
	ADC_NCH_LEN_11 = 0xA,	/**< ADC length of normal conversion 11 */
	ADC_NCH_LEN_12 = 0xB,	/**< ADC length of normal conversion 12 */
	ADC_NCH_LEN_13 = 0xC,	/**< ADC length of normal conversion 13 */
	ADC_NCH_LEN_14 = 0xD,	/**< ADC length of normal conversion 14 */
	ADC_NCH_LEN_15 = 0xE,	/**< ADC length of normal conversion 15 */
	ADC_NCH_LEN_16 = 0xF,	/**< ADC length of normal conversion 16 */
} adc_nch_len_t;

/**
  * @brief ADC numbers of insert conversion channals
  */
typedef enum {
	ADC_ICH_LEN_1 = 0x0,	/**< ADC number of insert conversion 1 */
	ADC_ICH_LEN_2 = 0x1,	/**< ADC number of insert conversion 2 */
	ADC_ICH_LEN_3 = 0x2,	/**< ADC number of insert conversion 3 */
	ADC_ICH_LEN_4 = 0x3,	/**< ADC number of insert conversion 4 */
} adc_ich_len_t;

/**
  * @brief ADC discontinuous mode choose
  */
typedef enum {
	ADC_ALL_DISABLE = 0x0,	/**< ADC discontinuous mode all disable */
	ADC_NCH_DISC_EN = 0x1,	/**< ADC normal channel discontinuous mode enable */
	ADC_ICH_DISC_EN = 0x2,	/**< ADC insert channel discontinuous mode enable */
} adc_disc_mode_t;

/**
  * @brief ADC numbers of channals in discontinuous conversion mode
  */
typedef enum {
	ADC_DISC_NBR_1 = 0x0,	/**< ADC number of discontinuous conversion 1 */
	ADC_DISC_NBR_2 = 0x1,	/**< ADC number of discontinuous conversion 2 */
	ADC_DISC_NBR_3 = 0x2,	/**< ADC number of discontinuous conversion 3 */
	ADC_DISC_NBR_4 = 0x3,	/**< ADC number of discontinuous conversion 4 */
	ADC_DISC_NBR_5 = 0x4,	/**< ADC number of discontinuous conversion 5 */
	ADC_DISC_NBR_6 = 0x5,	/**< ADC number of discontinuous conversion 6 */
	ADC_DISC_NBR_7 = 0x6,	/**< ADC number of discontinuous conversion 7 */
	ADC_DISC_NBR_8 = 0x7,	/**< ADC number of discontinuous conversion 8 */
} adc_disc_nbr_t;

/**
  * @brief ADC resolution of conversion
  */
typedef enum {
	ADC_CONV_RES_6  = 0x0,	/**< ADC resolution of conversion 6 */
	ADC_CONV_RES_8  = 0x1,	/**< ADC resolution of conversion 8 */
	ADC_CONV_RES_10 = 0x2,	/**< ADC resolution of conversion 10 */
	ADC_CONV_RES_12 = 0x3,	/**< ADC resolution of conversion 12 */
} adc_conv_res_t;

/**
  * @brief ADC external trigger mode choose
  */
typedef enum {
	ADC_ETS_DISABLE		= 0x0,	/**< ADC external trigger function disable */
	ADC_ETS_RISE		= 0x1,	/**< rise edge trigger ADC */
	ADC_ETS_FALL		= 0x2,	/**< fall edge trigger ADC */
	ADC_ETS_RISE_FALL	= 0x3,	/**< both rise and fall edge trigger ADC */
} adc_ets_mode_t;

/**
  * @brief ADC trigger conversion mode
  */


/**
  * @brief  Structure definition of ADC and normal group initialization
  */
typedef struct {
	adc_align_t data_align;		/**< Specifies ADC data alignment */
	type_func_t scan_mode;         	/**< Choose scan mode enable or not */
	type_func_t cont_mode;       	/**< Choose continuous mode enable or not */
	adc_nch_len_t nch_len;  	/**< Length of normal ranks will be converted */
	adc_disc_mode_t disc_mode;    	/**< Discontinuous mode enable or not */
	adc_disc_nbr_t disc_nbr;	/**< Number of discontinuous conversions channel */
	adc_conv_res_t conv_res;   	/**< The precision of conversion */
	adc_clk_div_t clk_div;		/**< ADCCLK divider */
	adc_nchesel_t nche_sel;		/**< Trigger the NCHE FALG mode */
	adc_neg_ref_t neg_ref;    	/**< The negative reference voltage*/
	adc_pos_ref_t pos_ref;    	/**< The positive reference voltage*/
} adc_init_t;

/**
  * @brief  Structure definition of ADC channel for normal group
  */
typedef struct {
	adc_channel_t channel;        	/**< The channel to configure into ADC normal group */
	adc_nch_rank_t rank;       	/**< The rank in the normal group sequencer */
	adc_samp_t samp_time;	    /**< Sampling time value to be set */
} adc_nch_conf_t;

/**
  * @brief  ADC Configuration analog watchdog definition
  */
typedef struct {
	adc_ana_wtd_t watchdog_mode;		/**< Configures the ADC analog watchdog mode*/
	adc_channel_t channel;			/**< Selects which ADC channel to monitor by analog watchdog */
	type_func_t it_mode;             	/**< Whether the analog watchdog is configured in interrupt */
	uint32_t high_threshold;     	 	/**< The ADC analog watchdog High threshold value. */
	uint32_t low_threshold;      	 	/**< The ADC analog watchdog Low threshold value. */
} adc_analog_wdg_conf_t;

/**
  * @brief  ADC Configuration insert Channel structure definition
  */
typedef struct {
	adc_channel_t channel;	/**< Selection of ADC channel to configure */
	adc_ich_rank_t rank;	/**< Rank in the insert group sequencer */
	adc_samp_t samp_time;	/**< Sampling time value for selected channel */
	uint32_t offset;	/**< The offset about converted data */
	adc_ich_len_t ich_len;	/**< The number of insert ranks */
	type_func_t auto_inj;	/**< insert sequence's auto function */
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

	void (*adc_reg_cplt_cbk)( struct adc_handle_s *arg);  	/**< Regluar Conversion complete callback */
	void (*adc_inj_cplt_cbk)( struct adc_handle_s *arg);  	/**< insert Conversion complete callback */
	void (*adc_out_of_win_cbk)( struct adc_handle_s *arg);	/**< Level out of window callback */
	void (*adc_error_cbk)(struct adc_handle_s *arg);      	/**< adc error callback */
	void (*adc_ovr_cbk)(struct adc_handle_s *arg);	      	/**< adc ovr callback */
} adc_handle_t;

/**
  * @brief Timer trigger adc config structure definition
  */
typedef struct {
	uint32_t time;						/**< Timer period time uint: us */	
	uint16_t size;						/**< Adc convert times */	
	uint16_t *buf;						/**< Convert data buffer */	
	adc_neg_ref_t n_ref;					/**< The negative reference voltage for adc*/
	adc_pos_ref_t p_ref;					/**< The positive reference voltage for adc*/
	adc_channel_t adc_ch;					/**< Adc channel */	
	uint8_t dma_ch;						/**< Dma channel */	
	TIMER_TypeDef *p_timer;					/**< Adc peripheral */	
	ADC_TypeDef *p_adc;					/**< Dma peripheral */	
	void (*adc_cplt_cbk)( struct adc_handle_s *arg);	/**< Conversion complete callback */

	/* private variable */
	lock_state_t lock;		/**< Locking object */
	pis_handle_t lh_pis;		/**< Handle of PIS module */
	dma_handle_t lh_dma;		/**< Handle of DMA module */
	timer_handle_t lh_timer;	/**< Handle of TIMER module */
	adc_handle_t lh_adc;		/**< Handle of ADC module */
	adc_nch_conf_t lnm_config;	/**< Struct for chanel configure */
} adc_timer_config_t;
/**
  * @}
  */

/** @defgroup ADC_Public_Macros ADC Public Macros
  * @{
  */
#define ADC_ENABLE(handle) 			(SET_BIT((handle)->perh->CON1, ADC_CON1_ADCEN_MSK))
#define ADC_DISABLE(handle) 			(CLEAR_BIT((handle)->perh->CON1, ADC_CON1_ADCEN_MSK))
#define ADC_NH_TRIG_BY_SOFT(handle)		(SET_BIT((handle)->perh->CON1, ADC_CON1_NCHTRG_MSK))
#define ADC_IH_TRIG_BY_SOFT(handle)		(SET_BIT((handle)->perh->CON1, ADC_CON1_ICHTRG_MSK))
#define ADC_RESET_HANDLE_STATE(handle)		((handle)->state = ADC_STATE_RESET)
#define ADC_VREF_OUT_ENABLE(handle)		(SET_BIT((handle)->perh->CCR, ADC_CCR_VREFOEN_MSK))
#define ADC_VREF_OUT_DISABLE(handle)		(CLEAR_BIT((handle)->perh->CCR, ADC_CCR_VREFOEN_MSK))
#define ADC_NETS_ENABLE(handle, mode)		(MODIFY_REG((handle)->perh->CON1, ADC_CON1_NETS_MSK, (mode) << ADC_CON1_NETS_POSS))
#define ADC_IETS_ENABLE(handle, mode)		(MODIFY_REG((handle)->perh->CON1, ADC_CON1_IETS_MSK, (mode) << ADC_CON1_IETS_POSS))
#define ADC_NETS_DISABLE(handle)		(MODIFY_REG((handle)->perh->CON1, ADC_CON1_NETS_MSK, 0 << ADC_CON1_NETS_POSS))
#define ADC_IETS_DISABLE(handle)		(MODIFY_REG((handle)->perh->CON1, ADC_CON1_IETS_MSK, 0 << ADC_CON1_IETS_POSS))
/**
  * @}
  */

/** @defgroup ADC_Private_Macros ADC Private Macros
  * @{
  */
#define IS_ADC_ICH_RANK_TYPE(x)			((x) <= ADC_ICH_RANK_4)
#define IS_ADC_NCH_RANK_TYPE(x)			((x) <= ADC_NCH_RANK_16)
#define IS_ADC_SAMPLING_TIMES_TYPE(x)		(((x) == ADC_SAMPLETIME_1) || \
                                                 ((x) == ADC_SAMPLETIME_2) || \
					         ((x) == ADC_SAMPLETIME_4) || \
					         ((x) == ADC_SAMPLETIME_15))
#define IS_ADC_CHANNELS_TYPE(x)			((x) <= ADC_CHANNEL_18)
#define IS_ADC_SCAN_MODE_TYPE(x)		(((x) == DISABLE) || \
                                                 ((x) == ENABLE))
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
						 ((x) == ADC_POS_REF_2_V) || \
						 ((x) == ADC_POS_REF_VREEFP) || \
						 ((x) == ADC_POS_REF_VREEFP_BUF))
#define IS_ADC_NCH_LEN_TYPE(x)			((x) <= ADC_NCH_LEN_16)
#define IS_ADC_NBR_OF_IST_TYPE(x)		((x) <= ADC_ICH_LEN_4)
#define IS_ADC_DISC_NBR_TYPE(x)			((x) <= ADC_DISC_NBR_8)
#define IS_ADC_CONV_RES_TYPE(x)			(((x) == ADC_CONV_RES_12) || \
                                                 ((x) == ADC_CONV_RES_6)  || \
						 ((x) == ADC_CONV_RES_8)  || \
						 ((x) == ADC_CONV_RES_10))
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
ald_status_t ald_adc_stop_by_dma(adc_handle_t *hperh);
ald_status_t ald_adc_timer_trigger_adc_by_dma(adc_timer_config_t *config);
#endif
uint32_t ald_adc_normal_get_value(adc_handle_t *hperh);
ald_status_t ald_adc_insert_start(adc_handle_t *hperh);
ald_status_t ald_adc_insert_stop(adc_handle_t *hperh);
ald_status_t ald_adc_insert_poll_for_conversion(adc_handle_t *hperh, uint32_t timeout);
ald_status_t ald_adc_insert_start_by_it(adc_handle_t *hperh);
ald_status_t ald_adc_insert_stop_by_it(adc_handle_t *hperh);
uint32_t ald_adc_insert_get_value(adc_handle_t *hperh, adc_ich_rank_t ih_rank);
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
