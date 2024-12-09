/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_EIM_H_
#define FSL_EIM_H_

#include "fsl_common.h"

/*!
 * @addtogroup eim
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Driver version. */
#define FSL_ERM_DRIVER_VERSION (MAKE_VERSION(2U, 0U, 1U))
/*@}*/

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief EIM module initialization function.
 *
 * @param base EIM base address.
 */
void EIM_Init(EIM_Type *base);

/*!
 * @brief De-initializes the EIM.
 *
 */
void EIM_Deinit(EIM_Type *base);

/* @} */

/*!
 * @name functional
 * @{
 */

/*!
 * @brief EIM module enable global error injection.
 *
 * @param base EIM base address.
 * @param mask The interrupts to enable.
 */
static inline void EIM_EnableGlobalErrorInjection(EIM_Type *base, bool enable)
{
    if (enable)
    {
        base->EIMCR = EIM_EIMCR_GEIEN_MASK;
    }
    else
    {
        base->EIMCR = ~EIM_EIMCR_GEIEN_MASK;
    }
}

/*!
 * @brief EIM module enable error injection for memory channel n, this function enables the corresponding error
 * injection channel. The Global Error Injection Enable function must also be called to enable error injection.
 *
 * @param base EIM base address.
 * @param mask The interrupts to enable. Refer to "_eim_error_injection_channel_enable" enumeration.
 */
static inline void EIM_EnableErrorInjectionChannels(EIM_Type *base, uint32_t mask)
{
    base->EICHEN |= mask;
}

/*!
 * @brief EIM module disable error injection for memory channel n.
 *
 * @param base EIM base address.
 * @param mask The interrupts to enable. Refer to "_eim_error_injection_channel_enable" enumeration.
 */
static inline void EIM_DisableErrorInjectionChannels(EIM_Type *base, uint32_t mask)
{
    base->EICHEN &= ~mask;
}

/*!
 * @brief EIM module inject checkbit error for memory channel n, an attempt to invert more than 2 bits in one operation
 * might result in undefined behavior.
 *
 * @param base EIM base address.
 * @param channel memory channel.
 * @param mask The interrupts to enable.
 */
void EIM_InjectCheckBitError(EIM_Type *base, eim_memory_channel_t channel, uint8_t mask);

/*!
 * @brief EIM module get checkbit mask for memory channel n.
 *
 * @param base EIM base address.
 * @param channel memory channel.
 * @retval return checkbit mask.
 */
uint8_t EIM_GetCheckBitMask(EIM_Type *base, eim_memory_channel_t channel);

/*!
 * @brief EIM module inject databit error for memory channel n, an attempt to invert more than 2 bits in one operation
 * might result in undefined behavior.
 *
 * @param base EIM base address.
 * @param channel memory channel.
 * @param mask The interrupts to enable.
 */
void EIM_InjectDataBitError(EIM_Type *base, eim_memory_channel_t channel, uint8_t mask);

/*!
 * @brief EIM module get databit mask for memory channel n.
 *
 * @param base EIM base address.
 * @param channel memory channel.
 * @retval return checkbit mask.
 */
uint32_t EIM_GetDataBitMask(EIM_Type *base, eim_memory_channel_t channel);

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
