/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_NVIC_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup NVIC
 *  @{
 */

#ifndef _HAL_NVIC_H_
#define _HAL_NVIC_H_

#include "hal_def.h"

/***************************** MACRO Definition ******************************/
/** @defgroup NVIC_Exported_Definition_Group1 Basic Definition
 *  @{
 */

typedef enum {
    NVIC_PRIORITYGROUP_0 = (0x7U), /*!< 0 bits pre-emption, 8 bits subpriority*/
    NVIC_PRIORITYGROUP_1 = (0x6U), /*!< 1 bits pre-emption, 7 bits subpriority*/
    NVIC_PRIORITYGROUP_2 = (0x5U), /*!< 2 bits pre-emption, 6 bits subpriority*/
    NVIC_PRIORITYGROUP_3 = (0x4U), /*!< 3 bits pre-emption, 5 bits subpriority*/
    NVIC_PRIORITYGROUP_4 = (0x3U), /*!< 4 bits pre-emption, 4 bits subpriority*/
    NVIC_PRIORITYGROUP_5 = (0x2U), /*!< 5 bits pre-emption, 3 bits subpriority*/
} eNVIC_PriorityGroup;

#ifndef NVIC_PRIORITYGROUP_DEFAULT
#define NVIC_PRIORITYGROUP_DEFAULT NVIC_PRIORITYGROUP_5 /**< Can be redefined in soc.h */
#endif

/* preempt priority */
#define NVIC_PERIPH_PRIO_LOWEST (0xFFU)
#ifndef NVIC_PERIPH_PRIO_DEFAULT
#if (__NVIC_PRIO_BITS == 2U)
#define NVIC_PERIPH_PRIO_DEFAULT (0x2U) /**< Can be redefined in soc.h */
#elif (__NVIC_PRIO_BITS == 3U)
#define NVIC_PERIPH_PRIO_DEFAULT (0x4U) /**< Can be redefined in soc.h */
#else
#define NVIC_PERIPH_PRIO_DEFAULT (0xFFU) /**< Can be redefined in soc.h */
#endif
#endif
#define NVIC_PERIPH_PRIO_HIGHEST (0x0U)

/* sub priority */
#define NVIC_PERIPH_SUB_PRIO_LOWEST  (0xFFU)
#define NVIC_PERIPH_SUB_PRIO_DEFAULT (0xFFU)
#define NVIC_PERIPH_SUB_PRIO_HIGHEST (0x0U)

#define IS_NVIC_PREEMPTION_PRIORITY(PRIORITY) ((PRIORITY) < 0x100U)
#define IS_NVIC_SUB_PRIORITY(PRIORITY)        ((PRIORITY) < 0x100U)

/** @brief Type define of NVIC interrupt handler */
typedef void (*NVIC_IRQHandler)(void);

/***************************** Structure Definition **************************/

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup NVIC_Public_Function_Declare Public Function Declare
 *  @{
 */

HAL_Status HAL_NVIC_SetIRQHandler(IRQn_Type IRQn, NVIC_IRQHandler handler);
NVIC_IRQHandler HAL_NVIC_GetIRQHandler(IRQn_Type IRQn);
HAL_Status HAL_NVIC_SetPriorityGrouping(eNVIC_PriorityGroup priorityGroup);
uint32_t HAL_NVIC_GetPriorityGrouping(void);
HAL_Status HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t preemptPriority, uint32_t subPriority);
uint32_t HAL_NVIC_GetPriority(IRQn_Type IRQn);
HAL_Status HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
HAL_Status HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
HAL_Status HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
HAL_Check HAL_NVIC_IsPendingIRQ(IRQn_Type IRQn);
HAL_Status HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
HAL_Status HAL_NVIC_ConfigExtIRQ(IRQn_Type IRQn, NVIC_IRQHandler handler,
                                 uint32_t preemptPriority, uint32_t subPriority);
HAL_Status HAL_NVIC_Init(void);

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_NVIC_MODULE_ENABLED */
