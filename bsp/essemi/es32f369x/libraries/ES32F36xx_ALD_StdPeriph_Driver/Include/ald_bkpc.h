/**
  *********************************************************************************
  *
  * @file    ald_bkpc.h
  * @brief   Header file of BKPC module driver.
  *
  * @version V1.0
  * @date    15 Dec 2019
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
#define BKPC_LOCK()		(WRITE_REG(BKPC->PROT, 0))
#define BKPC_UNLOCK()		(WRITE_REG(BKPC->PROT, 0x9669AA55))
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


#define BKPC_MRST_WAKEUP_ENABLE()			\
do {							\
	BKPC_UNLOCK();					\
	SET_BIT(BKPC->CR, BKPC_CR_MRST_WKPEN_MSK);	\
	BKPC_LOCK();					\
} while (0)
#define BKPC_MRST_WAKEUP_DISABLE()			\
do {							\
	BKPC_UNLOCK();					\
	CLEAR_BIT(BKPC->CR, BKPC_CR_MRST_WKPEN_MSK);	\
	BKPC_LOCK();					\
} while (0)

/**
  * @}
  */

/** @defgroup BKPC_Public_Types BKPC Public Types
  * @{
  */
/**
  * @brief BKPC preipheral clock select.
  */
typedef enum {
	BKPC_PREH_CLK_LOSM    = 0x0,	/**< LOSM */
	BKPC_PREH_CLK_LRC     = 0x1,	/**< LRC */
	BKPC_PREH_CLK_HRC_1M  = 0x2,	/**< HRC down to 1MHz */
	BKPC_PREH_CLK_HOSC_1M = 0x3,	/**< HOSC down to 1MHz */
} bkpc_preh_clk_t;

/**
  * @brief Standby wakeup port select
  */
typedef enum {
	PMU_STANDBY_PORT_SEL_PA0 = 0x0,	/**< PA0 */
	PMU_STANDBY_PORT_SEL_PA1 = 0x1,	/**< PA1 */
	PMU_STANDBY_PORT_SEL_PA2 = 0x2,	/**< PA2 */
	PMU_STANDBY_PORT_SEL_PA3 = 0x3,	/**< PA3 */
	PMU_STANDBY_PORT_SEL_PA4 = 0x4,	/**< PA4 */
	PMU_STANDBY_PORT_SEL_PA5 = 0x5,	/**< PA5 */
	PMU_STANDBY_PORT_SEL_PA6 = 0x6,	/**< PA6 */
	PMU_STANDBY_PORT_SEL_PA7 = 0x7,	/**< PA7 */
} bkpc_wakeup_port_t;

/**
  * @brief Standby wakeup level
  */
typedef enum {
	PMU_STANDBY_LEVEL_HIGH = 0x0,	/**< PA0 */
	PMU_STANDBY_LEVEL_LOW  = 0x1,	/**< PA1 */
} bkpc_wakeup_level_t;

/**
  * @}
  */

/**
  * @defgroup BKPC_Private_Macros BKPC Private Macros
  * @{
  */
#define IS_BKPC_WAKEUP_PORT(x)	(((x) == PMU_STANDBY_PORT_SEL_PA0) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA1) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA2) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA3) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA4) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA5) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA6) || \
                                 ((x) == PMU_STANDBY_PORT_SEL_PA7))
#define IS_BKPC_WAKEUP_LEVEL(x)	(((x) == PMU_STANDBY_LEVEL_HIGH) || \
                                 ((x) == PMU_STANDBY_LEVEL_LOW))
#define IS_BKPC_PREH_CLOCK(x)	(((x) == BKPC_PREH_CLK_LOSM) || \
                                 ((x) == BKPC_PREH_CLK_LRC) || \
                                 ((x) == BKPC_PREH_CLK_HRC_1M) || \
                                 ((x) == BKPC_PREH_CLK_HOSC_1M))
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
extern void ald_bkpc_rtc_clock_config(bkpc_preh_clk_t clock);
extern void ald_bkpc_tsense_clock_config(bkpc_preh_clk_t clock);
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
