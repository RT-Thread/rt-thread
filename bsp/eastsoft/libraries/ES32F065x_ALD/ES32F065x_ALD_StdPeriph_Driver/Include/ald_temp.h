/**
  *********************************************************************************
  *
  * @file    ald_temp.h
  * @brief   Header file of TEMP module driver.
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

#ifndef __ALD_TEMP_H__
#define __ALD_TEMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup TEMP
  * @{
  */

/** @defgroup TEMP_Public_Macros TEMP Public Macros
  * @{
  */
#define TEMP_LOCK()     (WRITE_REG(TEMP->WPR, 0x0))
#define TEMP_UNLOCK()       (WRITE_REG(TEMP->WPR, 0xA55A9669))
#define TEMP_ENABLE()               \
do {                        \
    TEMP_UNLOCK();              \
    SET_BIT(TEMP->CR, TEMP_CR_EN_MSK);  \
    TEMP_LOCK();                \
} while (0)
#define TEMP_DISABLE()              \
do {                        \
    TEMP_UNLOCK();              \
    CLEAR_BIT(TEMP->CR, TEMP_CR_EN_MSK);    \
    TEMP_LOCK();                \
} while (0)
#define TEMP_REQ_ENABLE()           \
do {                        \
    TEMP_UNLOCK();              \
    SET_BIT(TEMP->CR, TEMP_CR_REQEN_MSK);   \
    TEMP_LOCK();                \
} while (0)
#define TEMP_REQ_DISABLE()          \
do {                        \
    TEMP_UNLOCK();              \
    CLEAR_BIT(TEMP->CR, TEMP_CR_REQEN_MSK); \
    TEMP_LOCK();                \
} while (0)
#define TEMP_CTN_ENABLE()           \
do {                        \
    TEMP_UNLOCK();              \
    SET_BIT(TEMP->CR, TEMP_CR_CTN_MSK); \
    TEMP_LOCK();                \
} while (0)
#define TEMP_CTN_DISABLE()          \
do {                        \
    TEMP_UNLOCK();              \
    CLEAR_BIT(TEMP->CR, TEMP_CR_CTN_MSK);   \
    TEMP_LOCK();                \
} while (0)
#define TEMP_RESET()                \
do {                        \
    TEMP_UNLOCK();              \
    SET_BIT(TEMP->CR, TEMP_CR_RST_MSK); \
    TEMP_LOCK();                \
} while (0)
/**
  * @}
  */

/** @defgroup TEMP_Public_Types TEMP Public Types
  * @{
  */
/**
  * @brief Temperature update time
  */
typedef enum
{
    TEMP_UPDATE_CYCLE_3 = 0x3,  /**< 3 Cycles */
    TEMP_UPDATE_CYCLE_4 = 0x4,  /**< 4 Cycles */
    TEMP_UPDATE_CYCLE_5 = 0x5,  /**< 5 Cycles */
    TEMP_UPDATE_CYCLE_6 = 0x6,  /**< 6 Cycles */
    TEMP_UPDATE_CYCLE_7 = 0x7,  /**< 7 Cycles */
} temp_update_cycle_t;

/**
  * @brief Temperature output mode
  */
typedef enum
{
    TEMP_OUTPUT_MODE_200  = 0x0,    /**< 200 cycles update one temperature */
    TEMP_OUTPUT_MODE_400  = 0x1,    /**< 400 cycles update one temperature */
    TEMP_OUTPUT_MODE_800  = 0x2,    /**< 800 cycles update one temperature */
    TEMP_OUTPUT_MODE_1600 = 0x3,    /**< 1600 cycles update one temperature */
    TEMP_OUTPUT_MODE_3200 = 0x4,    /**< 3200 cycles update one temperature */
} temp_output_mode_t;

/**
  * @brief Source select
  */
typedef enum
{
    TEMP_SOURCE_LOSC        = 0x0,  /**< LOSC */
    TEMP_SOURCE_LRC         = 0x1,  /**< LRC */
    TEMP_SOURCE_HRC_DIV_1M  = 0x2,  /**< HRC divide to 1MHz */
    TEMP_SOURCE_HOSC_DIV_1M = 0x3,  /**< HOSC divide to 1MHz */
} temp_source_sel_t;


/**
  * @brief TEMP init structure definition
  */
typedef struct
{
    temp_update_cycle_t cycle;  /**< Temperature update time */
    temp_output_mode_t mode;    /**< Temperature output mode */
    uint8_t ctn;            /**< Continue mode */
    uint8_t psc;            /**< Perscaler */
} temp_init_t;

/**
  * @brief Define callback function type
  */
typedef void (*temp_cbk)(uint16_t value, ald_status_t status);
/**
  * @}
  */

/**
  * @defgroup TEMP_Private_Macros TEMP Private Macros
  * @{
  */
#define IS_TEMP_UPDATE_CYCLE(x) (((x) == TEMP_UPDATE_CYCLE_3) || \
                                 ((x) == TEMP_UPDATE_CYCLE_4) || \
                                 ((x) == TEMP_UPDATE_CYCLE_5) || \
                                 ((x) == TEMP_UPDATE_CYCLE_6) || \
                                 ((x) == TEMP_UPDATE_CYCLE_7))
#define IS_TEMP_OUTPUT_MODE(x)  (((x) == TEMP_OUTPUT_MODE_200)  || \
                                 ((x) == TEMP_OUTPUT_MODE_400)  || \
                                 ((x) == TEMP_OUTPUT_MODE_800)  || \
                                 ((x) == TEMP_OUTPUT_MODE_1600) || \
                                 ((x) == TEMP_OUTPUT_MODE_3200))
#define IS_TEMP_SOURCE_SEL(x)   (((x) == TEMP_SOURCE_LOSC)        || \
                                 ((x) == TEMP_SOURCE_LRC)         || \
                                 ((x) == TEMP_SOURCE_HRC_DIV_1M ) || \
                                 ((x) == TEMP_SOURCE_HOSC_DIV_1M))
/**
  * @}
  */

/** @addtogroup TEMP_Public_Functions
  * @{
  */
/** @addtogroup TEMP_Public_Functions_Group1
  * @{
  */
/* Initialization functions */
extern void temp_init(temp_init_t *init);
extern void temp_source_selcet(temp_source_sel_t sel);
/**
  * @}
  */
/** @addtogroup TEMP_Public_Functions_Group2
  * @{
  */
/* Control functions */
extern ald_status_t temp_get_value(uint16_t *temp);
extern void temp_get_value_by_it(temp_cbk cbk);
void temp_irq_handle(void);
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

#endif /* __ALD_TEMP_H__ */
