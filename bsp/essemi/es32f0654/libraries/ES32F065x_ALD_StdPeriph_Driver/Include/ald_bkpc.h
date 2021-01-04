/**
  *********************************************************************************
  *
  * @file    ald_bkpc.h
  * @brief   Header file of BKPC module driver.
  *
  * @version V1.0
  * @date    15 Dec 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_BKPC_H__
#define __ALD_BKPC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup BKPC
  * @{
  */

/** @defgroup BKPC_Public_Macros BKPC Public Macros
  * @{
  */
#define BKPC_LOCK()		(WRITE_REG(BKPC->PROT, 0U))
#define BKPC_UNLOCK()		(WRITE_REG(BKPC->PROT, 0x9669AA55U))
#define BKPC_LRC_ENABLE()			\
do {						\
	BKPC_UNLOCK();				\
	SET_BIT(BKPC->CR, BKPC_CR_LRCEN_MSK);	\
	BKPC_LOCK();				\
} while (0)
#define BKPC_LRC_DISABLE()			\
do {						\
	BKPC_UNLOCK();				\
	CLEAR_BIT(BKPC->CR, BKPC_CR_LRCEN_MSK);	\
	BKPC_LOCK();				\
} while (0)
#define BKPC_LOSM_ENABLE()			\
do {						\
	BKPC_UNLOCK();				\
	SET_BIT(BKPC->CR, BKPC_CR_LOSMEN_MSK);	\
	BKPC_LOCK();				\
} while (0)
#define BKPC_LOSM_DISABLE()			\
do {						\
	BKPC_UNLOCK();				\
	CLEAR_BIT(BKPC->CR, BKPC_CR_LOSMEN_MSK);\
	BKPC_LOCK();				\
} while (0)
#define BKPC_LOSC_ENABLE()			\
do {						\
	BKPC_UNLOCK();				\
	SET_BIT(BKPC->CR, BKPC_CR_LOSCEN_MSK);	\
	BKPC_LOCK();				\
} while (0)
#define BKPC_LOSC_DISABLE()			\
do {						\
	BKPC_UNLOCK();				\
	CLEAR_BIT(BKPC->CR, BKPC_CR_LOSCEN_MSK);\
	BKPC_LOCK();				\
} while (0)
/**
  * @}
  */

/** @defgroup BKPC_Public_Types BKPC Public Types
  * @{
  */
/**
  * @brief BKPC ldo output select
  */
typedef enum {
	BKPC_LDO_OUTPUT_1_6 = 0x0U,	/**< 1.6V */
	BKPC_LDO_OUTPUT_1_3 = 0x1U,	/**< 1.3V */
	BKPC_LDO_OUTPUT_1_4 = 0x2U,	/**< 1.4V */
	BKPC_LDO_OUTPUT_1_5 = 0x4U,	/**< 1.5V */
} bkpc_ldo_output_t;

/**
  * @brief Standby wakeup port select
  */
typedef enum {
	PMU_STANDBY_PORT_SEL_PA0  = 0x0U,	/**< Wakeup by PA0 */
	PMU_STANDBY_PORT_SEL_PA1  = 0x1U,	/**< Wakeup by PA1 */
	PMU_STANDBY_PORT_SEL_PA2  = 0x2U,	/**< Wakeup by PA2 */
	PMU_STANDBY_PORT_SEL_PA3  = 0x3U,	/**< Wakeup by PA3 */
	PMU_STANDBY_PORT_SEL_NONE = 0xFU,	/**< Wakeup by other source */
} bkpc_wakeup_port_t;

/**
  * @brief Standby wakeup level
  */
typedef enum {
	PMU_STANDBY_LEVEL_HIGH = 0x0U,	/**< High level */
	PMU_STANDBY_LEVEL_LOW  = 0x1U,	/**< Low level */
} bkpc_wakeup_level_t;
/**
  * @}
  */

/**
  * @defgroup BKPC_Private_Macros BKPC Private Macros
  * @{
  */
#define IS_BKPC_LDO_OUTPUT(x)	(((x) == BKPC_LDO_OUTPUT_1_6) || \
                                 ((x) == BKPC_LDO_OUTPUT_1_3) || \
                                 ((x) == BKPC_LDO_OUTPUT_1_4) || \
                                 ((x) == BKPC_LDO_OUTPUT_1_5))
#define IS_BKPC_WAKEUP_PORT(x)	(((x) == PMU_STANDBY_PORT_SEL_PA0) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA1) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA2) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA3) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_NONE))
#define IS_BKPC_WAKEUP_LEVEL(x)	(((x) == PMU_STANDBY_LEVEL_HIGH) || \
                                 ((x) == PMU_STANDBY_LEVEL_LOW))
#define IS_BKPC_RAM_IDX(x)	((x) < 32)
/**
  * @}
  */

/** @addtogroup BKPC_Public_Functions
  * @{
  */
/** @addtogroup BKPC_Public_Functions_Group1
  * @{
  */
/* control functions */
extern void ald_bkpc_standby_wakeup_config(bkpc_wakeup_port_t port, bkpc_wakeup_level_t level);
extern void ald_bkpc_ldo_config(bkpc_ldo_output_t output, type_func_t state);
/**
  * @}
  */
/** @addtogroup BKPC_Public_Functions_Group2
  * @{
  */
/* IO operation functions */
extern void ald_bkpc_write_ram(uint8_t idx, uint32_t value);
extern uint32_t ald_bkpc_read_ram(uint8_t idx);
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

#endif /* __ALD_BKPC_H__ */
