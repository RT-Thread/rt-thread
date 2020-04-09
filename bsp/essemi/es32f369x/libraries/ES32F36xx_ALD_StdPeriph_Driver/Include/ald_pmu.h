/**
  *********************************************************************************
  *
  * @file    ald_pmu.h
  * @brief   Header file of PMU module driver.
  *
  * @version V1.0
  * @date    04 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_PMU_H__
#define __ALD_PMU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"
#include "ald_syscfg.h"
#include "ald_bkpc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup PMU
  * @{
  */

/** @defgroup PMU_Public_Macros PMU Public Macros
  * @{
  */
#define PMU_LPSTOP_ENABLE()			\
do {						\
	SYSCFG_UNLOCK();			\
	SET_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);	\
	SYSCFG_LOCK();				\
} while (0)
#define PMU_LPSTOP_DISABLE()			\
do {						\
	SYSCFG_UNLOCK();			\
	CLEAR_BIT(PMU->CR, PMU_CR_LPSTOP_MSK);	\
	SYSCFG_LOCK();				\
} while (0)
#define PMU_MTSTOP_ENABLE()			\
do {						\
	SYSCFG_UNLOCK();			\
	SET_BIT(PMU->CR, PMU_CR_MTSTOP_MSK);	\
	SYSCFG_LOCK();				\
} while (0)
#define PMU_MTSTOP_DISABLE()			\
do {						\
	SYSCFG_UNLOCK();			\
	CLEAR_BIT(PMU->CR, PMU_CR_MTSTOP_MSK);	\
	SYSCFG_LOCK();				\
} while (0)
#define PMU_VREF_ENABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	SET_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)
#define PMU_VREF_DISABLE()				\
do {							\
	SYSCFG_UNLOCK();				\
	CLEAR_BIT(PMU->VREFCR, PMU_VREFCR_VREFEN_MSK);	\
	SYSCFG_LOCK();					\
} while (0)

#define PMU_GET_LVD_STATUS()	(READ_BITS(PMU->LVDCR, PMU_LVDCR_LVDO_MSK, PMU_LVDCR_LVDO_POS))
/**
  * @}
  */


/** @defgroup PMU_Public_Types PMU Public Types
  * @{
  */
/**
  * @brief Low power mode
  */
typedef enum {
	PMU_LP_STOP1   = 0x0,	/**< Stop1 */
	PMU_LP_STOP2   = 0x1,	/**< Stop2 */
	PMU_LP_STANDBY = 0x2,	/**< Standby */
} pmu_lp_mode_t;

typedef enum {
	PMU_SR_WUF      = (1U << 0),	/**< WakeUp status */
	PMU_SR_STANDBYF = (1U << 1),	/**< Standby status */
	PMU_SR_USBRDY   = (1U << 2),	/**< USB Readby status */
	PMU_SR_RSTAT    = (1U << 3),	/**< RUN/LPRUAN status */
} pmu_status_t;

/**
  * @brief LVD voltage select
  */
typedef enum {
	PMU_LVD_VOL_SEL_2_2 = 0x0,	/**< 2.2V ~ 2.25V */
	PMU_LVD_VOL_SEL_2_4 = 0x1,	/**< 2.4V ~ 2.45V */
	PMU_LVD_VOL_SEL_2_6 = 0x2,	/**< 2.6V ~ 2.65V */
	PMU_LVD_VOL_SEL_2_8 = 0x3,	/**< 2.8V ~ 2.85V */
	PMU_LVD_VOL_SEL_3_0 = 0x4,	/**< 3.0V ~ 3.05V */
	PMU_LVD_VOL_SEL_3_2 = 0x5,	/**< 3.2V ~ 3.25V */
	PMU_LVD_VOL_SEL_3_4 = 0x6,	/**< 3.4V ~ 3.45V */
	PMU_LVD_VOL_SEL_3_6 = 0x7,	/**< 3.6V ~ 3.65V */
	PMU_LVD_VOL_SEL_3_8 = 0x8,	/**< 3.8V ~ 3.85V */
	PMU_LVD_VOL_SEL_4_0 = 0x9,	/**< 4.0V ~ 4.05V */
	PMU_LVD_VOL_SEL_4_2 = 0x9,	/**< 4.2V ~ 4.25V */
	PMU_LVD_VOL_SEL_4_4 = 0x9,	/**< 4.4V ~ 4.45V */
	PMU_LVD_VOL_SEL_4_6 = 0x9,	/**< 4.6V ~ 4.65V */
	PMU_LVD_VOL_SEL_4_8 = 0x9,	/**< 4.8V ~ 4.85V */
	PMU_LVD_VOL_SEL_EXT = 0xF,	/**< Select external input. It must be 1.2V */
} pmu_lvd_voltage_sel_t;

/**
  * @brief LVD trigger mode
  */
typedef enum {
	PMU_LVD_TRIGGER_RISING_EDGE    = 0x0,	/**< Rising edge */
	PMU_LVD_TRIGGER_FALLING_EDGE   = 0x1,	/**< Falling edge */
	PMU_LVD_TRIGGER_HIGH_LEVEL     = 0x2,	/**< High level */
	PMU_LVD_TRIGGER_LOW_LEVEL      = 0x3,	/**< Low level */
	PMU_LVD_TRIGGER_RISING_FALLING = 0x4,	/**< Rising and falling edge */
} pmu_lvd_trigger_mode_t;

/**
  * @brief LDO output voltage selest in low power mode
  */
typedef enum {
	PMU_LDO_LPMODE_OUTPUT_0_9 = 0x0,	/**< 0.9V */
	PMU_LDO_LPMODE_OUTPUT_1_0 = 0x1,	/**< 1.0V */
	PMU_LDO_LPMODE_OUTPUT_1_1 = 0x2,	/**< 1.1V */
	PMU_LDO_LPMODE_OUTPUT_1_2 = 0x3,	/**< 1.2V */
} pmu_ldo_lpmode_output_t;

typedef enum {
	PMU_POWER_SRAM0 = 0x1,		/**< SRAM0 */
	PMU_POWER_SRAM1 = 0x2,		/**< SRAM1 */
	PMU_POWER_SRAM2 = 0x4,		/**< SRAM2 */
	PMU_POWER_SRAM3 = 0x8,		/**< SRAM3 */
	PMU_POWER_SRAM4 = 0x10,		/**< SRAM4 */
	PMU_POWER_SRAM5 = 0x20,		/**< SRAM5 */
	PMU_POWER_CAN   = 0x100,	/**< CAN */
	PMU_POWER_QSPI  = 0x400,	/**< QSPI */
	PMU_POWER_USB   = 0x800,	/**< USB */
	PMU_POWER_ROM   = 0x1000,	/**< ROM */
} pmu_perh_power_t;

/**
  * @}
  */

/**
  * @defgroup PMU_Private_Macros PMU Private Macros
  * @{
  */
#define IS_PMU_LP_MODE(x)		(((x) == PMU_LP_STOP1) || \
                                         ((x) == PMU_LP_STOP2) || \
                                         ((x) == PMU_LP_STANDBY))
#define IS_PMU_STATUS(x)		(((x) == PMU_SR_WUF) || \
                                         ((x) == PMU_SR_STANDBYF) || \
                                         ((x) == PMU_SR_USBRDY) || \
                                         ((x) == PMU_SR_RSTAT))
#define IS_PMU_LVD_VOL_SEL(x)		(((x) == PMU_LVD_VOL_SEL_2_2) || \
                                         ((x) == PMU_LVD_VOL_SEL_2_4) || \
                                         ((x) == PMU_LVD_VOL_SEL_2_6) || \
                                         ((x) == PMU_LVD_VOL_SEL_2_8) || \
                                         ((x) == PMU_LVD_VOL_SEL_3_0) || \
                                         ((x) == PMU_LVD_VOL_SEL_3_2) || \
                                         ((x) == PMU_LVD_VOL_SEL_3_4) || \
                                         ((x) == PMU_LVD_VOL_SEL_3_6) || \
                                         ((x) == PMU_LVD_VOL_SEL_3_8) || \
                                         ((x) == PMU_LVD_VOL_SEL_4_0) || \
                                         ((x) == PMU_LVD_VOL_SEL_4_2) || \
                                         ((x) == PMU_LVD_VOL_SEL_4_4) || \
                                         ((x) == PMU_LVD_VOL_SEL_4_6) || \
                                         ((x) == PMU_LVD_VOL_SEL_4_8) || \
                                         ((x) == PMU_LVD_VOL_SEL_EXT))
#define IS_PMU_LVD_TRIGGER_MODE(x)	(((x) == PMU_LVD_TRIGGER_RISING_EDGE)  || \
                                         ((x) == PMU_LVD_TRIGGER_FALLING_EDGE) || \
                                         ((x) == PMU_LVD_TRIGGER_HIGH_LEVEL)   || \
                                         ((x) == PMU_LVD_TRIGGER_LOW_LEVEL)    || \
                                         ((x) == PMU_LVD_TRIGGER_RISING_FALLING))
#define IS_PMU_LDO_LPMODE_OUTPUT(x)	(((x) == PMU_LDO_LPMODE_OUTPUT_0_9) || \
                                         ((x) == PMU_LDO_LPMODE_OUTPUT_1_0) || \
                                         ((x) == PMU_LDO_LPMODE_OUTPUT_1_1) || \
                                         ((x) == PMU_LDO_LPMODE_OUTPUT_1_2))
#define IS_PMU_PERH_POWER(x)		(((x) == PMU_POWER_SRAM0) || \
                                         ((x) == PMU_POWER_SRAM1) || \
                                         ((x) == PMU_POWER_SRAM2) || \
					 ((x) == PMU_POWER_SRAM3) || \
					 ((x) == PMU_POWER_SRAM4) || \
					 ((x) == PMU_POWER_SRAM5) || \
					 ((x) == PMU_POWER_CAN)   || \
					 ((x) == PMU_POWER_QSPI)  || \
					 ((x) == PMU_POWER_USB)   || \
                                         ((x) == PMU_POWER_ROM))

/**
  * @}
  */

/** @addtogroup PMU_Public_Functions
  * @{
  */
/** @addtogroup PMU_Public_Functions_Group1
  * @{
  */
/* Low power mode select */
__STATIC_INLINE__ void ald_pmu_sleep()
{
	__WFI();
}

__STATIC_INLINE__ void ald_pmu_sleep_deep()
{
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	__WFI();
}

void ald_pmu_stop1_enter(void);
void ald_pmu_stop2_enter(void);
void ald_pmu_standby_enter(bkpc_wakeup_port_t port, bkpc_wakeup_level_t level);
void ald_pmu_lprun_config(pmu_ldo_lpmode_output_t vol, type_func_t state);
flag_status_t ald_pmu_get_status(pmu_status_t sr);
void ald_pmu_clear_status(pmu_status_t sr);
void ald_pmu_perh_power_config(pmu_perh_power_t perh, type_func_t state);
/**
  * @}
  */
/** @addtogroup PMU_Public_Functions_Group2
  * @{
  */
/* LVD configure */
void ald_pmu_lvd_config(pmu_lvd_voltage_sel_t sel, pmu_lvd_trigger_mode_t mode, type_func_t state);
void ald_lvd_irq_handler(void);
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

#endif /* __ALD_PMU_H__ */
