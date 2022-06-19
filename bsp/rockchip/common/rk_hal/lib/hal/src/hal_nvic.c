/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_NVIC_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup NVIC
 *  @{
 */

/** @defgroup NVIC_How_To_Use How To Use
 *  @{

 The NVIC driver can be used as follows:

 @} */

/** @defgroup NVIC_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup NVIC_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  Set interrupt handler.
 * @param  IRQn: interrupt number.
 * @param  handler: NVIC_IRQHandler.
 * @return HAL_OK.
 */
HAL_Status HAL_NVIC_SetIRQHandler(IRQn_Type IRQn, NVIC_IRQHandler handler)
{
#if __VTOR_PRESENT
    uint32_t *vectors = (uint32_t *)SCB->VTOR;
#else
    /* cortex m0 has no vtor, the vector table alway based 0x0*/
    uint32_t *vectors = (uint32_t *)0x0U;
#endif

    vectors[IRQn + NVIC_PERIPH_IRQ_OFFSET] = (uint32_t)handler;

    return HAL_OK;
}

/**
 * @brief  Get interrupt handler.
 * @param  IRQn: interrupt number
 * @return NVIC_IRQHandler.
 */
NVIC_IRQHandler HAL_NVIC_GetIRQHandler(IRQn_Type IRQn)
{
#if __VTOR_PRESENT
    uint32_t *vectors = (uint32_t *)SCB->VTOR;
#else
    /* cortex m0 has no vtor, the vector table alway based 0x0*/
    uint32_t *vectors = (uint32_t *)0x0U;
#endif

    return (NVIC_IRQHandler)(vectors[IRQn + NVIC_PERIPH_IRQ_OFFSET]);
}

/**
 * @brief  Set interrupt priority group.
 * @return priorityGroup: priority group.
 * @return HAL_OK.
 */
HAL_Status HAL_NVIC_SetPriorityGrouping(eNVIC_PriorityGroup priorityGroup)
{
    NVIC_SetPriorityGrouping(priorityGroup);

    return HAL_OK;
}

/**
 * @brief  Get interrupt priority group.
 * @return uint32_t: priority group.
 */
uint32_t HAL_NVIC_GetPriorityGrouping(void)
{
    return NVIC_GetPriorityGrouping();
}

/**
 * @brief  Set interrupt priority.
 * @param  IRQn: interrupt number.
 * @param  preemptPriority: preemt priority.
 * @param  subPriority: sub priority.
 * @return HAL_OK.
 */
HAL_Status HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t preemptPriority, uint32_t subPriority)
{
    uint32_t prioritygroup = 0x00U;

    /* Check the parameters */
    HAL_ASSERT(IS_NVIC_SUB_PRIORITY(subPriority));
    HAL_ASSERT(IS_NVIC_PREEMPTION_PRIORITY(preemptPriority));

    prioritygroup = NVIC_GetPriorityGrouping();

    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, preemptPriority, subPriority));

    return HAL_OK;
}

/**
 * @brief  Get interrupt priority.
 * @param  IRQn: interrupt number
 * @return HAL_OK.
 */
uint32_t HAL_NVIC_GetPriority(IRQn_Type IRQn)
{
    return NVIC_GetPriority(IRQn);
}

/**
 * @brief  Enabled interrupt.
 * @param  IRQn: interrupt number
 * @return HAL_OK.
 */
HAL_Status HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    NVIC_EnableIRQ(IRQn);

    return HAL_OK;
}

/**
 * @brief  Disable interrupt.
 * @param  IRQn: interrupt number
 * @return HAL_OK.
 */
HAL_Status HAL_NVIC_DisableIRQ(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);

    return HAL_OK;
}

/**
 * @brief  Pending interrupt.
 * @param  IRQn: interrupt number
 * @return HAL_OK.
 */
HAL_Status HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    NVIC_SetPendingIRQ(IRQn);

    return HAL_OK;
}

/**
 * @brief  Check whether the interrupt is suspended.
 * @param  IRQn: interrupt number
 * @return int: if is pending return 1, or 0.
 */
HAL_Check HAL_NVIC_IsPendingIRQ(IRQn_Type IRQn)
{
    return (HAL_Check)(NVIC_GetPendingIRQ(IRQn));
}

/**
 * @brief  Clear pending interrupt.
 * @param  IRQn: interrupt number
 * @return None.
 */
HAL_Status HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    NVIC_ClearPendingIRQ(IRQn);

    return HAL_OK;
}

/**
 * @brief  Register peripheral interrupt handle and priority.
 * @param  IRQn: interrupt number.
 * @param  handler: interrupt handle.
 * @param  preemptPriority: preemt priority.
 * @param  subPriority: sub priority.
 * @return None.
 */
HAL_Status HAL_NVIC_ConfigExtIRQ(IRQn_Type IRQn, NVIC_IRQHandler handler,
                                 uint32_t preemptPriority, uint32_t subPriority)
{
    HAL_NVIC_SetIRQHandler(IRQn, handler);
    HAL_NVIC_SetPriority(IRQn, preemptPriority, subPriority);
    HAL_NVIC_EnableIRQ(IRQn);

    return HAL_OK;
}

/**
 * @brief  Init NVIC Interrupt Controller.
 * @return None.
 */
HAL_Status HAL_NVIC_Init(void)
{
    /* Use HardFault */

    return HAL_OK;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_NVIC_MODULE_ENABLED */
