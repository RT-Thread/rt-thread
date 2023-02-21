/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_EXTI_H__
#define __HAL_EXTI_H__

#include "hal_common.h"

/*!
 * @addtogroup EXTI
 * @{
 */

/*!
 * @brief EXTI driver version number.
 */
#define EXTI_DRIVER_VERSION 0u /*!< exti_0. */

/*!
 * @addtogroup EXTI_LINE
 * @{
 */
#define EXTI_LINE_0  (1u << 0u)   /*!<External Interrupt Line 0  switcher. */
#define EXTI_LINE_1  (1u << 1u)   /*!<External Interrupt Line 1  switcher. */
#define EXTI_LINE_2  (1u << 2u)   /*!<External Interrupt Line 2  switcher. */
#define EXTI_LINE_3  (1u << 3u)   /*!<External Interrupt Line 3  switcher. */
#define EXTI_LINE_4  (1u << 4u)   /*!<External Interrupt Line 4  switcher. */
#define EXTI_LINE_5  (1u << 5u)   /*!<External Interrupt Line 5  switcher. */
#define EXTI_LINE_6  (1u << 6u)   /*!<External Interrupt Line 6  switcher. */
#define EXTI_LINE_7  (1u << 7u)   /*!<External Interrupt Line 7  switcher. */
#define EXTI_LINE_8  (1u << 8u)   /*!<External Interrupt Line 8  switcher. */
#define EXTI_LINE_9  (1u << 9u)   /*!<External Interrupt Line 9  switcher. */
#define EXTI_LINE_10 (1u << 10u)  /*!<External Interrupt Line 10 switcher. */
#define EXTI_LINE_11 (1u << 11u)  /*!<External Interrupt Line 11 switcher. */
#define EXTI_LINE_12 (1u << 12u)  /*!<External Interrupt Line 12 switcher. */
#define EXTI_LINE_13 (1u << 13u)  /*!<External Interrupt Line 13 switcher. */
#define EXTI_LINE_14 (1u << 14u)  /*!<External Interrupt Line 14 switcher. */
#define EXTI_LINE_15 (1u << 15u)  /*!<External Interrupt Line 15 switcher. */
#define EXTI_LINE_16 (1u << 16u)  /*!<External Interrupt Line 16 switcher. */
#define EXTI_LINE_17 (1u << 17u)  /*!<External Interrupt Line 17 switcher. */
#define EXTI_LINE_18 (1u << 18u)  /*!<External Interrupt Line 18 switcher. */
#define EXTI_LINE_19 (1u << 19u)  /*!<External Interrupt Line 19 switcher. */
#define EXTI_LINE_20 (1u << 20u)  /*!<External Interrupt Line 20 switcher. */
#define EXTI_LINE_21 (1u << 21u)  /*!<External Interrupt Line 21 switcher. */
#define EXTI_LINE_22 (1u << 22u)  /*!<External Interrupt Line 22 switcher. */
#define EXTI_LINE_23 (1u << 23u)  /*!<External Interrupt Line 23 switcher. */
#define EXTI_LINE_24 (1u << 24u)  /*!<External Interrupt Line 24 switcher. */
/*!
 * @}
 */

/*!
 * @brief EXTI trigger input detection edge alt.
 */
typedef enum
{
    EXTI_TriggerIn_Disable     = 0u, /*!< Disable the trigger input interrupt. */
    EXTI_TriggerIn_RisingEdge  = 1u, /*!< Trigger input rising edge interrupt.*/
    EXTI_TriggerIn_FallingEdge = 2u, /*!< Trigger input falling edge interrupt.*/
    EXTI_TriggerIn_BothEdges   = 3u, /*!< Both trigger input rising and falling edge interrupt.*/
} EXTI_TriggerIn_Type;

/*!
 * @brief Enable the external interrupt line's interrupts.
 *
 * @param EXTIx EXTI instance.
 * @param lines External interrupt lines. See to @ref EXTI_LINE.
 * @param enable 'true' to unmask the external interrupt lines' interrupt, 'false' to mask the external interrupt lines' interrupt.
 * @return None.
 */
void EXTI_EnableLineInterrupt(EXTI_Type * EXTIx, uint32_t lines, bool enable);

/*!
 * @brief Enable the external interrupt line's events.
 *
 * @param EXTIx EXTI instance.
 * @param lines External interrupt lines. See to @ref EXTI_LINE.
 * @param enable 'true' to unmask the external interrupt lines' event, 'false' to disable the external interrupt lines' event.
 * @return None.
 */
void EXTI_EnableLineEvent(EXTI_Type * EXTIx, uint32_t lines, bool enable);

/*!
 * @brief Set the line input for triggering interrupts.
 *
 * @param EXTIx EXTI instance.
 * @param lines External interrupt lines. See to @ref EXTI_LINE.
 * @param trgin The active signal for triggering interrupts. See to @ref EXTI_TriggerIn_Type;
 * @return None.
 */
void EXTI_SetTriggerIn(EXTI_Type * EXTIx, uint32_t lines, EXTI_TriggerIn_Type trgin);

/*!
 * @brief Do software trigger to trigger interrupts of the indicated lines.
 *
 * @param EXTIx EXTI instance.
 * @param lines External interrupt lines. See to @ref EXTI_LINE.
 * @return None.
 */
void EXTI_DoSwTrigger(EXTI_Type * EXTIx, uint32_t lines);

/*!
 * @brief Get the interrupt status of the indicated EXTI module.
 *
 * @param EXTIx EXTI instance.
 * @return Line status flags. See to @ref EXTI_LINE.
 */
uint32_t EXTI_GetLineStatus(EXTI_Type * EXTIx);

/*!
 * @brief Clear the interrupt status of the indicated EXTI module.
 *
 * @param EXTIx EXTI instance.
 * @param lines Interrupt status flags. See to @ref EXTI_LINE.
 * @return None.
 */
void EXTI_ClearLineStatus(EXTI_Type * EXTIx, uint32_t lines);

/*!
 * @}
 */

#endif /* __HAL_EXTI_H__ */

