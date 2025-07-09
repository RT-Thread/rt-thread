/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_XECC_H_
#define FSL_XECC_H_

#include "fsl_common.h"

/*!
 * @addtogroup xecc
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief Driver version 2.0.0. */
#define FSL_XECC_DRIVER_VERSION (MAKE_VERSION(2U, 0U, 0U))
/*! @} */

/*!
 * @brief XECC interrupt configuration structure, , xecc_interrupt_enable_t.
 *
 * This structure contains the settings for all of the XECC interrupt configurations.
 */
enum
{
    kXECC_SingleErrorInterruptEnable = XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN_MASK, /*!< Single bit error interrupt enable*/
    kXECC_MultiErrorInterruptEnable  = XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN_MASK, /*!< Multiple bit error interrupt enable*/

    kXECC_AllInterruptsEnable =
        XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN_MASK | XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN_MASK, /*!< all interrupts enable */
};

/*!
 * @brief XECC interrupt status configuration structure, xecc_interrupt_status_enable_t.
 *
 * This structure contains the settings for all of the XECC interrupt status configurations.
 */
enum
{
    kXECC_SingleErrorInterruptStatusEnable =
        XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN_MASK, /*!< Single bit error interrupt status enable*/
    kXECC_MultiErrorInterruptStatusEnable =
        XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN_MASK, /*!< Multiple bits error interrupt status enable*/

    kXECC_AllInterruptsStatusEnable = XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN_MASK |
                                      XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN_MASK, /*!< all interrupts enable */
};

/*!
 * @brief XECC status flags, xecc_interrupt_status_t.
 *
 * This provides constants for the XECC status flags for use in the XECC functions.
 */
enum
{
    kXECC_SingleErrorInterruptFlag =
        XECC_ERR_STATUS_SINGLE_ERR_MASK, /*!< Single bit error interrupt happens on read data*/
    kXECC_MultiErrorInterruptFlag =
        XECC_ERR_STATUS_MULTI_ERR_MASK, /*!< Multiple bits error interrupt happens on read data*/

    kXECC_AllInterruptsFlag =
        XECC_ERR_STATUS_SINGLE_ERR_MASK | XECC_ERR_STATUS_MULTI_ERR_MASK, /*!< all interrupts happens on read data*/
};

/*! @brief XECC user configuration.*/
typedef struct _xecc_config
{
    bool enableXECC;     /*!< Enable the XECC function. */
    bool enableWriteECC; /*!< Enable write ECC function. */
    bool enableReadECC;  /*!< Enable read ECC function. */
    bool enableSwap;     /*!< Enable swap function. */

    /*!< The minimum ECC region range is 4k, so the lower 12 bits of this register must be 0.*/
    uint32_t Region0BaseAddress; /*!< ECC region 0 base address. */
    uint32_t Region0EndAddress;  /*!< ECC region 0 end address. */
    uint32_t Region1BaseAddress; /*!< ECC region 1 base address. */
    uint32_t Region1EndAddress;  /*!< ECC region 1 end address. */
    uint32_t Region2BaseAddress; /*!< ECC region 2 base address. */
    uint32_t Region2EndAddress;  /*!< ECC region 2 end address. */
    uint32_t Region3BaseAddress; /*!< ECC region 3 base address. */
    uint32_t Region3EndAddress;  /*!< ECC region 3 end address. */
} xecc_config_t;

/*! @brief XECC single error information, including single error address, ECC code, error data, error bit
 * position and error bit field */
typedef struct _xecc_single_error_info
{
    uint32_t singleErrorAddress;  /*!< Single error address */
    uint32_t singleErrorData;     /*!< Single error read data */
    uint32_t singleErrorEccCode;  /*!< Single error ECC code */
    uint32_t singleErrorBitPos;   /*!< Single error bit postion */
    uint32_t singleErrorBitField; /*!< Single error bit field */
} xecc_single_error_info_t;

/*! @brief XECC multiple error information, including multiple error address, ECC code, error data and error bit field
 */
typedef struct _xecc_multi_error_info
{
    uint32_t multiErrorAddress;  /*!< Multiple error address */
    uint32_t multiErrorData;     /*!< Multiple error read data */
    uint32_t multiErrorEccCode;  /*!< Multiple error ECC code */
    uint32_t multiErrorBitField; /*!< Single error bit field */
} xecc_multi_error_info_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief XECC module initialization function.
 *
 * @param base XECC base address.
 * @param config pointer to the XECC configuration structure.
 */
void XECC_Init(XECC_Type *base, const xecc_config_t *config);

/*!
 * @brief Deinitializes the XECC.
 *
 * @param base XECC base address.
 */
void XECC_Deinit(XECC_Type *base);

/*!
 * @brief Sets the XECC configuration structure to default values.
 *
 * @param config pointer to the XECC configuration structure.
 */
void XECC_GetDefaultConfig(xecc_config_t *config);

/*! @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief Gets XECC status flags.
 *
 * @param base XECC peripheral base address.
 * @return XECC status flags.
 */
static inline uint32_t XECC_GetStatusFlags(XECC_Type *base)
{
    return base->ERR_STATUS & (uint32_t)kXECC_AllInterruptsFlag;
}

/*!
 * @brief XECC module clear interrupt status.
 *
 * @param base XECC base address.
 * @param mask status to clear from xecc_interrupt_status_t.
 */
static inline void XECC_ClearStatusFlags(XECC_Type *base, uint32_t mask)
{
    base->ERR_STATUS = mask;
}

/*!
 * @brief XECC module enable interrupt status.
 *
 * @param base XECC base address.
 * @param mask status to enable from xecc_interrupt_status_enable_t.
 */
static inline void XECC_EnableInterruptStatus(XECC_Type *base, uint32_t mask)
{
    base->ERR_STAT_EN |= mask;
}

/*!
 * @brief XECC module disable interrupt status.
 *
 * @param base XECC base address.
 * @param mask status to disable from xecc_interrupt_status_enable_t.
 */
static inline void XECC_DisableInterruptStatus(XECC_Type *base, uint32_t mask)
{
    base->ERR_STAT_EN &= ~mask;
}

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief XECC module enable interrupt.
 *
 * @param base XECC base address.
 * @param mask The interrupts to enable from xecc_interrupt_enable_t.
 */
static inline void XECC_EnableInterrupts(XECC_Type *base, uint32_t mask)
{
    base->ERR_SIG_EN |= mask;
}

/*!
 * @brief XECC module disable interrupt.
 *
 * @param base XECC base address.
 * @param mask The interrupts to disable from xecc_interrupt_enable_t.
 */
static inline void XECC_DisableInterrupts(XECC_Type *base, uint32_t mask)
{
    base->ERR_SIG_EN &= ~mask;
}
/*! @} */

/*!
 * @name functional
 * @{
 */
/*!
 * @brief XECC module write ECC function enable.
 *
 * @param base XECC base address.
 * @param enable enable or disable.
 */
static inline void XECC_WriteECCEnable(XECC_Type *base, bool enable)
{
    if (enable)
    {
        base->ECC_CTRL |= XECC_ECC_CTRL_WECC_EN(1);
    }
    else
    {
        base->ECC_CTRL |= XECC_ECC_CTRL_WECC_EN(0);
    }
}

/*!
 * @brief XECC module read ECC function enable.
 *
 * @param base XECC base address.
 * @param enable enable or disable.
 */
static inline void XECC_ReadECCEnable(XECC_Type *base, bool enable)
{
    if (enable)
    {
        base->ECC_CTRL |= XECC_ECC_CTRL_RECC_EN(1);
    }
    else
    {
        base->ECC_CTRL |= XECC_ECC_CTRL_RECC_EN(0);
    }
}

/*!
 * @brief XECC module swap data enable.
 *
 * @param base XECC base address.
 * @param enable enable or disable.
 */
static inline void XECC_SwapECCEnable(XECC_Type *base, bool enable)
{
    if (enable)
    {
        base->ECC_CTRL |= XECC_ECC_CTRL_SWAP_EN(1);
    }
    else
    {
        base->ECC_CTRL |= XECC_ECC_CTRL_SWAP_EN(0);
    }
}

/*!
 * @brief XECC module error injection.
 *
 * @param base XECC base address.
 * @param errordata error data.
 * @param erroreccdata ecc code.
 * @retval kStatus_Success.
 */
status_t XECC_ErrorInjection(XECC_Type *base, uint32_t errordata, uint8_t erroreccdata);

/*!
 * @brief XECC module get single error information.
 *
 * @param base XECC base address.
 * @param info single error information.
 */
void XECC_GetSingleErrorInfo(XECC_Type *base, xecc_single_error_info_t *info);

/*!
 * @brief XECC module get multiple error information.
 *
 * @param base XECC base address.
 * @param info multiple error information.
 */
void XECC_GetMultiErrorInfo(XECC_Type *base, xecc_multi_error_info_t *info);

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
