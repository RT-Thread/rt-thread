/**
  *********************************************************************************
  *
  * @file    ald_lptim.c
  * @brief   LPTIM module driver.
  *	     This is the common part of the LPTIM initialization
  *
  * @version V1.0
  * @date    09 Nov 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_LPTIM_H__
#define __ALD_LPTIM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"
#include "ald_cmu.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup LPTIM
  * @{
  */

/** @defgroup LPTIM_Public_Types LPTIM Public Types
  * @{
  */

/**
  * @brief LPTIM clock select
  */
typedef enum {
	LPTIM_CKSEL_INTERNAL = 0U,	/**< Select internal clock */
	LPTIM_CKSEL_EXTERNAL = 1U,	/**< Select external clock */
} lptim_cksel_t;

/**
  * @brief LPTIM clock pol
  */
typedef enum {
	LPTIM_CKPOL_RISING  = 0U,	/**< using rising edge */
	LPTIM_CKPOL_FALLING = 1U,	/**< using falling edge */
} lptim_ckpol_t;

/**
  * @brief LPTIM clock fliter
  */
typedef enum {
	LPTIM_CKFLT_0 = 0U,	/**< not clock filter */
	LPTIM_CKFLT_2 = 1U,	/**< 2 cycle filter */
	LPTIM_CKFLT_4 = 2U,	/**< 4 cycle filter */
	LPTIM_CKFLT_8 = 3U,	/**< 8 cycle filter */
} lptim_ckflt_t;

/**
  * @brief LPTIM trigger fliter
  */
typedef enum {
	LPTIM_TRGFLT_0 = 0U,	/**< not clock filter */
	LPTIM_TRGFLT_2 = 1U,	/**< 2 cycle filter */
	LPTIM_TRGFLT_4 = 2U,	/**< 4 cycle filter */
	LPTIM_TRGFLT_8 = 3U,	/**< 8 cycle filter */
} lptim_trgflt_t;

/**
  * @brief LPTIM prescaler
  */
typedef enum {
	LPTIM_PRESC_1   = 0U,	/**< No prescaler is used */
	LPTIM_PRESC_2   = 1U,	/**< Clock is divided by 2 */
	LPTIM_PRESC_4   = 2U,	/**< Clock is divided by 4 */
	LPTIM_PRESC_8   = 3U,	/**< Clock is divided by 8 */
	LPTIM_PRESC_16  = 4U,	/**< Clock is divided by 16 */
	LPTIM_PRESC_32  = 5U,	/**< Clock is divided by 32 */
	LPTIM_PRESC_64  = 6U,	/**< Clock is divided by 64 */
	LPTIM_PRESC_128 = 7U,	/**< Clock is divided by 128 */
} lptim_presc_t;

/**
  * @brief LPTIM trig select
  */
typedef enum {
	LPTIM_TRIGSEL_EXT0 = 0U,	/**< Trigger select external channel 0 */
	LPTIM_TRIGSEL_EXT1 = 1U,	/**< Trigger select external channel 1 */
	LPTIM_TRIGSEL_EXT2 = 2U,	/**< Trigger select external channel 2 */
	LPTIM_TRIGSEL_EXT3 = 3U,	/**< Trigger select external channel 3 */
	LPTIM_TRIGSEL_EXT4 = 4U,	/**< Trigger select external channel 4 */
	LPTIM_TRIGSEL_EXT5 = 5U,	/**< Trigger select external channel 5 */
	LPTIM_TRIGSEL_EXT6 = 6U,	/**< Trigger select external channel 6 */
	LPTIM_TRIGSEL_EXT7 = 7U,	/**< Trigger select external channel 7 */
} lptim_trigsel_t;

/**
  * @brief LPTIM start mode select
  */
typedef enum {
	LPTIM_MODE_SINGLE     = 0U,	/**< Start single mode */
	LPTIM_MODE_CONTINUOUS = 1U,	/**< Start continuous mode */
} lptim_mode_t;

/**
  * @brief LPTIM trig en
  */
typedef enum {
	LPTIM_TRIGEN_SW      = 0U,	/**< software trigger */
	LPTIM_TRIGEN_RISING  = 1U,	/**< rising edge trigger */
	LPTIM_TRIGEN_FALLING = 2U,	/**< falling edge trigger */
	LPTIM_TRIGEN_BOTH    = 3U,	/**< rising and falling edge trigger */
} lptim_trigen_t;

/**
  * @brief LPTIM wave
  */
typedef enum {
	LPTIM_WAVE_NONE   = 0U,	/**< Output close */
	LPTIM_WAVE_TOGGLE = 1U,	/**< Output toggle */
	LPTIM_WAVE_PULSE  = 2U,	/**< Output pulse */
	LPTIM_WAVE_PWM    = 3U,	/**< Output PWM */
} lptim_wave_t;

/**
  * @brief LPTIM interrupt
  */
typedef enum {
	LPTIM_IT_CMPMAT  = 1U,	/**< Compare interrupt bit */
	LPTIM_IT_ARRMAT  = 2U,	/**< Update interrupt bit */
	LPTIM_IT_EXTTRIG = 4U,	/**< external trigger interrupt bit */
} lptim_it_t;

/**
  * @brief LPTIM Interrupt flag
  */
typedef enum {
	LPTIM_FLAG_CMPMAT  = 1U,	/**< Compare interrupt flag */
	LPTIM_FLAG_ARRMAT  = 2U,	/**< Update interrupt flag */
	LPTIM_FLAG_EXTTRIG = 4U,	/**< Update interrupt flag */
} lptim_flag_t;

/**
  * @brief LPTIM state structures definition
  */
typedef enum {
	LPTIM_STATE_RESET   = 0x00U,	/**< Peripheral not yet initialized or disabled */
	LPTIM_STATE_READY   = 0x01U,	/**< Peripheral Initialized and ready for use */
	LPTIM_STATE_BUSY    = 0x02U,	/**< An internal process is ongoing */
	LPTIM_STATE_TIMEOUT = 0x03U,	/**< Timeout state */
	LPTIM_STATE_ERROR   = 0x04U,	/**< Reception process is ongoing */
} lptim_state_t;

/**
  * @brief LPTIM Init Structure definition
  */
typedef struct {
	lptim_presc_t psc;		/**< Specifies the prescaler value */
	uint16_t arr;			/**< Specifies the update value */
	uint16_t cmp;			/**< Specifies the compare value */
	cmu_lp_perh_clock_sel_t clock;	/**< Specifies the clock choose */
	lptim_mode_t mode;		/**< Specifies the start mode */
} lptim_init_t;

/**
  * @brief LPTIM trigger Structure definition
  */
typedef struct {
	lptim_trigen_t mode;	/**< Specifies the trigger mode */
	lptim_trigsel_t sel;	/**< Specifies the trigger source select */
} lptim_trigger_init_t;

/**
  * @brief LPTIM trigger Structure definition
  */
typedef struct {
	lptim_cksel_t sel;	/**< Specifies the clock select */
	lptim_ckpol_t polarity;	/**< Specifies the clock polarity */
} lptim_clock_source_init_t;

/**
  * @brief  LPTIM Handle Structure definition
  */
typedef struct lptim_handle_s {
	LPTIM_TypeDef *perh;	/**< Register base address */
	lptim_init_t init;	/**< LPTIM Time required parameters */
	lock_state_t lock;	/**< Locking object */
	lptim_state_t state;	/**< LPTIM operation state */

	void (*trig_cbk)(struct lptim_handle_s *arg);	/**< Trigger callback */
	void (*update_cbk)(struct lptim_handle_s *arg);	/**< Update callback */
	void (*cmp_cbk)(struct lptim_handle_s *arg);	/**< Compare callback */
} lptim_handle_t;
/**
  * @}
  */

/** @defgroup LPTIM_Public_Macros LPTIM Public Macros
  * @{
  */
#define LPTIM_ENABLE(x)			(SET_BIT((x)->perh->CON1, LP16T_CON1_ENABLE_MSK))
#define LPTIM_DISABLE(x)		(CLEAR_BIT((x)->perh->CON1, LP16T_CON1_ENABLE_MSK))
#define LPTIM_CNTSTART(x)		(SET_BIT((x)->perh->CON1, LP16T_CON1_CNTSTRT_MSK))
#define LPTIM_SNGSTART(x)		(SET_BIT((x)->perh->CON1, LP16T_CON1_SNGSTRT_MSK))
#define LPTIM_UPDATE_ENABLE(x)		(SET_BIT((x)->perh->UPDATE, LP16T_UPDATE_UDIS_MSK))
#define LPTIM_UPDATE_DISABLE(x)		(CLEAR_BIT((x)->perh->UPDATE, LP16T_UPDATE_UDIS_MSK))
#define LPTIM_PRELOAD_IMM(x)		(SET_BIT((x)->perh->CR0, LP16T_CON0_PRELOAD_MSK))
#define LPTIM_PRELOAD_WAIT(x)		(CLEAR_BIT((x)->perh->CR0, LP16T_CON0_PRELOAD_MSK))
#define LPTIM_WAVEPOL_NORMAL(x)		(MODIFY_REG((x)->perh->CR0, LP16T_CON0_WAVE_MSK, 0 << LP16T_CON0_WAVE_POSS))
#define LPTIM_WAVEPOL_INVERSE(x)	(MODIFY_REG((x)->perh->CR0, LP16T_CON0_WAVE_MSK, 1 << LP16T_CON0_WAVE_POSS))
/**
  * @}
  */

/** @defgroup LPTIM_Private_Macros   LPTIM Private Macros
  * @{
  */
#define IS_LPTIM(x)		((x) == LPTIM0)
#define IS_LPTIM_CKSEL(x)	(((x) == LPTIM_CKSEL_INTERNAL) || \
                                 ((x) == LPTIM_CKSEL_EXTERNAL))
#define IS_LPTIM_CKPOL(x)	(((x) == LPTIM_CKPOL_RISING) || \
                                 ((x) == LPTIM_CKPOL_FALLING))
#define IS_LPTIM_MODE(x)	(((x) == LPTIM_MODE_SINGLE) || \
                                 ((x) == LPTIM_MODE_CONTINUOUS))
#define IS_LPTIM_CKFLT(x)	(((x) == LPTIM_CKFLT_0) || \
                                 ((x) == LPTIM_CKFLT_2) || \
                                 ((x) == LPTIM_CKFLT_4) || \
                                 ((x) == LPTIM_CKFLT_8))
#define IS_LPTIM_TRGFLT(x)	(((x) == LPTIM_TRGFLT_0) || \
                                 ((x) == LPTIM_TRGFLT_2) || \
                                 ((x) == LPTIM_TRGFLT_4) || \
                                 ((x) == LPTIM_TRGFLT_8))
#define IS_LPTIM_PRESC(x)	(((x) == LPTIM_PRESC_1)  || \
                                 ((x) == LPTIM_PRESC_2)  || \
                                 ((x) == LPTIM_PRESC_4)  || \
                                 ((x) == LPTIM_PRESC_8)  || \
                                 ((x) == LPTIM_PRESC_16) || \
                                 ((x) == LPTIM_PRESC_32) || \
                                 ((x) == LPTIM_PRESC_64) || \
                                 ((x) == LPTIM_PRESC_128))
#define IS_LPTIM_TRIGSEL(x)	(((x) == LPTIM_TRIGSEL_EXT0) || \
                                 ((x) == LPTIM_TRIGSEL_EXT1) || \
                                 ((x) == LPTIM_TRIGSEL_EXT2) || \
                                 ((x) == LPTIM_TRIGSEL_EXT3) || \
                                 ((x) == LPTIM_TRIGSEL_EXT4) || \
                                 ((x) == LPTIM_TRIGSEL_EXT5) || \
                                 ((x) == LPTIM_TRIGSEL_EXT6) || \
                                 ((x) == LPTIM_TRIGSEL_EXT7))
#define IS_LPTIM_TRIGEN(x)	(((x) == LPTIM_TRIGEN_SW)      || \
                                 ((x) == LPTIM_TRIGEN_RISING)  || \
                                 ((x) == LPTIM_TRIGEN_FALLING) || \
                                 ((x) == LPTIM_TRIGEN_BOTH))
#define IS_LPTIM_IT(x)		(((x) == LPTIM_IT_CMPMAT) || \
                                 ((x) == LPTIM_IT_ARRMAT) || \
                                 ((x) == LPTIM_IT_EXTTRIG))
#define IS_LPTIM_FLAG(x)	(((x) == LPTIM_FLAG_CMPMAT) || \
                                 ((x) == LPTIM_FLAG_ARRMAT) || \
                                 ((x) == LPTIM_FLAG_EXTTRIG))
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions
  * @{
  */

/** @addtogroup LPTIM_Public_Functions_Group1
  * @{
  */
void ald_lptim_reset(lptim_handle_t *hperh);
void ald_lptim_trigger_config(lptim_handle_t *hperh, lptim_trigger_init_t *config);
void ald_lptim_clock_source_config(lptim_handle_t *hperh, lptim_clock_source_init_t *config);
void ald_lptim_trigger_filter_config(lptim_handle_t *hperh, lptim_trgflt_t flt);
void ald_lptim_clock_filter_config(lptim_handle_t *hperh, lptim_ckflt_t flt);
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions_Group2
  * @{
  */
ald_status_t ald_lptim_base_init(lptim_handle_t *hperh);
void ald_lptim_base_start(lptim_handle_t *hperh);
void ald_lptim_base_stop(lptim_handle_t *hperh);
void ald_lptim_base_start_by_it(lptim_handle_t *hperh);
void ald_lptim_base_stop_by_it(lptim_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions_Group3
  * @{
  */
ald_status_t ald_lptim_toggle_init(lptim_handle_t *hperh);
void ald_lptim_toggle_start(lptim_handle_t *hperh);
void ald_lptim_toggle_stop(lptim_handle_t *hperh);
void ald_lptim_toggle_start_by_it(lptim_handle_t *hperh);
void ald_lptim_toggle_stop_by_it(lptim_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions_Group4
  * @{
  */
ald_status_t ald_lptim_pulse_init(lptim_handle_t *hperh);
void ald_lptim_pulse_start(lptim_handle_t *hperh);
void ald_lptim_pulse_stop(lptim_handle_t *hperh);
void ald_lptim_pulse_start_by_it(lptim_handle_t *hperh);
void ald_lptim_pulse_stop_by_it(lptim_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions_Group5
  * @{
  */
ald_status_t ald_lptim_pwm_init(lptim_handle_t *hperh);
void ald_lptim_pwm_start(lptim_handle_t *hperh);
void ald_lptim_pwm_stop(lptim_handle_t *hperh);
void ald_lptim_pwm_start_by_it(lptim_handle_t *hperh);
void ald_lptim_pwm_stop_by_it(lptim_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions_Group6
  * @{
  */
void ald_lptim_irq_handler(lptim_handle_t *hperh);
void ald_lptim_interrupt_config(lptim_handle_t *hperh, lptim_it_t it, type_func_t state);
it_status_t ald_lptim_get_it_status(lptim_handle_t *hperh, lptim_it_t it);
flag_status_t ald_lptim_get_flag_status(lptim_handle_t *hperh, lptim_flag_t flag);
void ald_lptim_clear_flag_status(lptim_handle_t *hperh, lptim_flag_t flag);
/**
  * @}
  */

/** @addtogroup LPTIM_Public_Functions_Group7
  * @{
  */
lptim_state_t ald_lptim_get_state(lptim_handle_t *hperh);
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
#endif

#endif /* __ALD_LPTIM_H__ */
