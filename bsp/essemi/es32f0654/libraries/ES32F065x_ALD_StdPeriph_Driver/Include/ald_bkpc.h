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
/**
  * @}
  */

/** @defgroup BKPC_Public_Types BKPC Public Types
  * @{
  */
/**
  * @brief BKPC ldo output select
  */
typedef enum
{
    BKPC_LDO_OUTPUT_1_6 = 0x0,	/**< 1.6V */
    BKPC_LDO_OUTPUT_1_3 = 0x1,	/**< 1.3V */
    BKPC_LDO_OUTPUT_1_4 = 0x2,	/**< 1.4V */
    BKPC_LDO_OUTPUT_1_5 = 0x4,	/**< 1.5V */
} bkpc_ldo_output_t;

/**
  * @brief BKPC BOR voltage select
  */
typedef enum
{
    BKPC_BOR_VOL_1_7  = 0x0,	/**< 1.7V */
    BKPC_BOR_VOL_2_0  = 0x1,	/**< 2.0V */
    BKPC_BOR_VOL_2_1  = 0x2,	/**< 2.1V */
    BKPC_BOR_VOL_2_2  = 0x3,	/**< 2.2V */
    BKPC_BOR_VOL_2_3  = 0x4,	/**< 2.3V */
    BKPC_BOR_VOL_2_4  = 0x5,	/**< 2.4V */
    BKPC_BOR_VOL_2_5  = 0x6,	/**< 2.5V */
    BKPC_BOR_VOL_2_6  = 0x7,	/**< 2.6V */
    BKPC_BOR_VOL_2_8  = 0x8,	/**< 2.8V */
    BKPC_BOR_VOL_3_0  = 0x9,	/**< 3.0V */
    BKPC_BOR_VOL_3_1  = 0xA,	/**< 3.1V */
    BKPC_BOR_VOL_3_3  = 0xB,	/**< 3.3V */
    BKPC_BOR_VOL_3_6  = 0xC,	/**< 3.6V */
    BKPC_BOR_VOL_3_7  = 0xD,	/**< 3.7V */
    BKPC_BOR_VOL_4_0  = 0xE,	/**< 4.0V */
    BKPC_BOR_VOL_4_3  = 0xF,	/**< 4.3V */
} bkpc_bor_vol_t;

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
#define IS_BKPC_BOR_VOL(x)	(((x) == BKPC_BOR_VOL_1_7) || \
                             ((x) == BKPC_BOR_VOL_2_0) || \
                             ((x) == BKPC_BOR_VOL_2_1) || \
                             ((x) == BKPC_BOR_VOL_2_2) || \
                             ((x) == BKPC_BOR_VOL_2_3) || \
                             ((x) == BKPC_BOR_VOL_2_4) || \
                             ((x) == BKPC_BOR_VOL_2_5) || \
                             ((x) == BKPC_BOR_VOL_2_6) || \
                             ((x) == BKPC_BOR_VOL_2_8) || \
                             ((x) == BKPC_BOR_VOL_3_0) || \
                             ((x) == BKPC_BOR_VOL_3_1) || \
                             ((x) == BKPC_BOR_VOL_3_3) || \
                             ((x) == BKPC_BOR_VOL_3_6) || \
                             ((x) == BKPC_BOR_VOL_3_7) || \
                             ((x) == BKPC_BOR_VOL_4_0) || \
                             ((x) == BKPC_BOR_VOL_4_3))
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
extern void ald_bkpc_ldo_config(bkpc_ldo_output_t output, type_func_t state);
extern void ald_bkpc_bor_config(bkpc_bor_vol_t vol, type_func_t state);
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
