/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_ERM_H_
#define FSL_ERM_H_

#include "fsl_common.h"

/*!
 * @addtogroup erm
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

/*!
 * @brief ERM interrupt configuration structure, default settings all disabled, _erm_interrupt_enable.
 *
 * This structure contains the settings for all of the ERM interrupt configurations.
 */
enum
{
    kERM_SingleCorrectionIntEnable = 0x08U, /*!< Single Correction Interrupt Notification enable.*/
    kERM_NonCorrectableIntEnable   = 0x04U, /*!< Non-Correction Interrupt Notification enable.*/

    kERM_AllInterruptsEnable = 0xFFFFFFFFUL, /*!< All Interrupts enable */
};

/*!
 * @brief ERM interrupt status, _erm_interrupt_flag.
 *
 * This provides constants for the ERM event status for use in the ERM functions.
 */
enum
{
    kERM_SingleBitCorrectionIntFlag = 0x08U, /*!< Single-Bit Correction Event.*/
    kERM_NonCorrectableErrorIntFlag = 0x04U, /*!< Non-Correctable Error Event.*/

    kERM_AllIntsFlag = 0xFFFFFFFFUL, /*!< All Events. */
};

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and de-initialization
 * @{
 */

/*!
 * @brief ERM module initialization function.
 *
 * @param base ERM base address.
 */
void ERM_Init(ERM_Type *base);

/*!
 * @brief De-initializes the ERM.
 *
 */
void ERM_Deinit(ERM_Type *base);

/* @} */

/*!
 * @name Interrupt
 * @{
 */
/*!
 * @brief ERM enable interrupts.
 *
 * @param base ERM peripheral base address.
 * @param channel memory channel.
 * @param mask single correction interrupt or non-correction interrupt enable to disable for one specific memory region.
 * Refer to "_erm_interrupt_enable" enumeration.
 */
static inline void ERM_EnableInterrupts(ERM_Type *base, erm_memory_channel_t channel, uint32_t mask)
{
    uint32_t temp = 0x00U;
    if ((uint32_t)channel <= 0x07U)
    {
        temp = base->CR0;
        base->CR0 =
            (temp & ~(0x0CUL << ((0x07U - (uint32_t)channel) * 4U))) | (mask << ((0x07U - (uint32_t)channel) * 4U));
    }
#ifdef ERM_CR1_ESCIE8_MASK
    else
    {
        temp      = base->CR1;
        base->CR1 = (temp & ~(0x0CUL << ((0x07U + 0x08U - (uint32_t)channel) * 4U))) |
                    (mask << ((0x07U + 0x08U - (uint32_t)channel) * 4U));
    }
#endif
}

/*!
 * @brief ERM module disable interrupts.
 *
 * @param base ERM base address.
 * @param channel memory channel.
 * @param mask single correction interrupt or non-correction interrupt enable to disable for one specific memory region.
 * Refer to "_erm_interrupt_enable" enumeration.
 */
static inline void ERM_DisableInterrupts(ERM_Type *base, erm_memory_channel_t channel, uint32_t mask)
{
    if ((uint32_t)channel <= 0x07U)
    {
        base->CR0 &= ~(mask << ((0x07U - (uint32_t)channel) * 4U));
    }
#ifdef ERM_CR1_ESCIE8_MASK
    else
    {
        base->CR1 &= ~(mask << ((0x07U + 0x08U - (uint32_t)channel) * 4U));
    }
#endif
}

/*!
 * @brief Gets ERM interrupt flags.
 *
 * @param base ERM peripheral base address.
 * @return ERM event flags.
 */
static inline uint32_t ERM_GetInterruptStatus(ERM_Type *base, erm_memory_channel_t channel)
{
    if ((uint32_t)channel <= 0x07U)
    {
        return ((base->SR0 & (uint32_t)kERM_AllIntsFlag) >> (0x07U - (uint32_t)channel) * 4U);
    }
#ifdef ERM_SR1_SBC8_MASK
    else
    {
        return ((base->SR1 & (uint32_t)kERM_AllIntsFlag) >> ((0x07U + 0x08U - (uint32_t)channel) * 4U));
    }
#else
    {
        return 0;
    }
#endif
}

/*!
 * @brief ERM module clear interrupt status flag.
 *
 * @param base ERM base address.
 * @param mask event flag to clear. Refer to "_erm_interrupt_flag" enumeration.
 */
static inline void ERM_ClearInterruptStatus(ERM_Type *base, erm_memory_channel_t channel, uint32_t mask)
{
    if ((uint32_t)channel <= 0x07U)
    {
        base->SR0 = mask << ((0x07U - (uint32_t)channel) * 4U);
    }
#ifdef ERM_SR1_SBC8_MASK
    else
    {
        base->SR1 = mask << ((0x07U + 0x08U - (uint32_t)channel) * 4U);
    }
#endif
}

/* @} */

/*!
 * @name functional
 * @{
 */

/*!
 * @brief ERM get memory error absolute address, which capturing the address of the last ECC event in Memory n.
 *
 * @param base ERM base address.
 * @param channel memory channel.
 * @retval memory error absolute address.
 */

uint32_t ERM_GetMemoryErrorAddr(ERM_Type *base, erm_memory_channel_t channel);

/*!
 * @brief ERM get syndrome, which identifies the pertinent bit position on a correctable, single-bit data inversion or a
 * non-correctable, single-bit address inversion. The syndrome value does not provide any additional diagnostic
 * information on non-correctable, multi-bit inversions.
 *
 * @param base ERM base address.
 * @param channel memory channel.
 * @retval syndrome value.
 */
uint32_t ERM_GetSyndrome(ERM_Type *base, erm_memory_channel_t channel);

/*!
 * @brief ERM get error count, which  records the count value of the number of correctable ECC error events for Memory
 * n. Non-correctable errors are considered a serious fault, so the ERM does not provide any mechanism to count
 * non-correctable errors. Only correctable errors are counted.
 *
 * @param base ERM base address.
 * @param channel memory channel.
 * @retval error count.
 */
uint32_t ERM_GetErrorCount(ERM_Type *base, erm_memory_channel_t channel);

/*!
 * @brief ERM reset error count.
 *
 * @param base ERM base address.
 * @param channel memory channel.
 */
void ERM_ResetErrorCount(ERM_Type *base, erm_memory_channel_t channel);

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
