/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_MECC_H_
#define _FSL_MECC_H_

#include "fsl_common.h"

/*!
 * @addtogroup mecc
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.0.2. */
#define FSL_MECC_DRIVER_VERSION (MAKE_VERSION(2U, 0U, 2U))
/*@}*/
/*! @brief Error codes for the MECC driver. */
enum
{
    kStatus_MECC_BankMiss = MAKE_STATUS(kStatusGroup_MECC, 0), /*!< Ocram bank miss */
};

/*!
 * @brief MECC interrupt configuration structure, default settings all disabled.
 *
 * This structure contains the settings for all of the MECC interrupt configurations.
 */
enum
{
    kMECC_SingleError0InterruptEnable =
        MECC_ERR_SIG_EN_SINGLE_ERR0_SIG_EN_MASK, /*!< Single Bit Error On Ocram Bank0 interrupt enable.*/
    kMECC_SingleError1InterruptEnable =
        MECC_ERR_SIG_EN_SINGLE_ERR1_SIG_EN_MASK, /*!< Single Bit Error On Ocram Bank1 interrupt enable*/
    kMECC_SingleError2InterruptEnable =
        MECC_ERR_SIG_EN_SINGLE_ERR2_SIG_EN_MASK, /*!< Single Bit Error On Ocram Bank2 interrupt enable*/
    kMECC_SingleError3InterruptEnable =
        MECC_ERR_SIG_EN_SINGLE_ERR3_SIG_EN_MASK, /*!< Single Bit Error On Ocram Bank3 interrupt enable*/

    kMECC_MultiError0InterruptEnable =
        MECC_ERR_SIG_EN_MULTI_ERR0_SIG_EN_MASK, /*!< Multiple Bits Error On Ocram Bank0 interrupt enable*/
    kMECC_MultiError1InterruptEnable =
        MECC_ERR_SIG_EN_MULTI_ERR1_SIG_EN_MASK, /*!< Multiple Bits Error On Ocram Bank1 interrupt enable*/
    kMECC_MultiError2InterruptEnable =
        MECC_ERR_SIG_EN_MULTI_ERR2_SIG_EN_MASK, /*!< Multiple Bits Error On Ocram Bank2 interrupt enable*/
    kMECC_MultiError3InterruptEnable =
        MECC_ERR_SIG_EN_MULTI_ERR3_SIG_EN_MASK, /*!< Multiple Bits Error On Ocram Bank3 interrupt enable*/

    kMECC_StrobeError0InterruptEnable =
        MECC_ERR_SIG_EN_STRB_ERR0_SIG_EN_MASK, /*!< AXI Strobe Error On Ocram Bank0 interrupt enable*/
    kMECC_StrobeError1InterruptEnable =
        MECC_ERR_SIG_EN_STRB_ERR1_SIG_EN_MASK, /*!< AXI Strobe Error On Ocram Bank1 interrupt enable*/
    kMECC_StrobeError2InterruptEnable =
        MECC_ERR_SIG_EN_STRB_ERR2_SIG_EN_MASK, /*!< AXI Strobe Error On Ocram Bank2 interrupt enable*/
    kMECC_StrobeError3InterruptEnable =
        MECC_ERR_SIG_EN_STRB_ERR3_SIG_EN_MASK, /*!< AXI Strobe Error On Ocram Bank3 interrupt enable*/

    kMECC_AccessError0InterruptEnable =
        MECC_ERR_SIG_EN_ADDR_ERR0_SIG_EN_MASK, /*!< Ocram Access Error On Bank0 interrupt enable*/
    kMECC_AccessError1InterruptEnable =
        MECC_ERR_SIG_EN_ADDR_ERR1_SIG_EN_MASK, /*!< Ocram Access Error On Bank1 interrupt enable*/
    kMECC_AccessError2InterruptEnable =
        MECC_ERR_SIG_EN_ADDR_ERR2_SIG_EN_MASK, /*!< Ocram Access Error On Bank2 interrupt enable*/
    kMECC_AccessError3InterruptEnable =
        MECC_ERR_SIG_EN_ADDR_ERR3_SIG_EN_MASK, /*!< Ocram Access Error On Bank3 interrupt enable*/

    kMECC_AllInterruptsEnable = 0xFFFF, /*!< all  interrupts enable */
};

/*!
 * @brief MECC interrupt status configuration structure, default settings all disabled.
 *
 * This structure contains the settings for all of the MECC interrupt status configurations.
 */
enum
{
    kMECC_SingleError0InterruptStatusEnable =
        MECC_ERR_STAT_EN_SINGLE_ERR0_STAT_EN_MASK, /*!< Single Bit Error On Ocram Bank0 interrupt status enable.*/
    kMECC_SingleError1InterruptStatusEnable =
        MECC_ERR_STAT_EN_SINGLE_ERR1_STAT_EN_MASK, /*!< Single Bit Error On Ocram Bank1 interrupt status enable*/
    kMECC_SingleError2InterruptStatusEnable =
        MECC_ERR_STAT_EN_SINGLE_ERR2_STAT_EN_MASK, /*!< Single Bit Error On Ocram Bank2 interrupt status enable*/
    kMECC_SingleError3InterruptStatusEnable =
        MECC_ERR_STAT_EN_SINGLE_ERR3_STAT_EN_MASK, /*!< Single Bit Error On Ocram Bank3 interrupt status enable*/

    kMECC_MultiError0InterruptStatusEnable =
        MECC_ERR_STAT_EN_MULTI_ERR0_STAT_EN_MASK, /*!< Multiple Bits Error On Ocram Bank0 interrupt status enable*/
    kMECC_MultiError1InterruptStatusEnable =
        MECC_ERR_STAT_EN_MULTI_ERR1_STAT_EN_MASK, /*!< Multiple Bits Error On Ocram Bank1 interrupt status enable*/
    kMECC_MultiError2InterruptStatusEnable =
        MECC_ERR_STAT_EN_MULTI_ERR2_STAT_EN_MASK, /*!< Multiple Bits Error On Ocram Bank2 interrupt status enable*/
    kMECC_MultiError3InterruptStatusEnable =
        MECC_ERR_STAT_EN_MULTI_ERR3_STAT_EN_MASK, /*!< Multiple Bits Error On Ocram Bank3 interrupt status enable*/

    kMECC_StrobeError0InterruptStatusEnable =
        MECC_ERR_STAT_EN_STRB_ERR0_STAT_EN_MASK, /*!< AXI Strobe Error On Ocram Bank0 interrupt status enable*/
    kMECC_StrobeError1InterruptStatusEnable =
        MECC_ERR_STAT_EN_STRB_ERR1_STAT_EN_MASK, /*!< AXI Strobe Error On Ocram Bank1 interrupt status enable*/
    kMECC_StrobeError2InterruptStatusEnable =
        MECC_ERR_STAT_EN_STRB_ERR2_STAT_EN_MASK, /*!< AXI Strobe Error On Ocram Bank2 interrupt status enable*/
    kMECC_StrobeError3InterruptStatusEnable =
        MECC_ERR_STAT_EN_STRB_ERR3_STAT_EN_MASK, /*!< AXI Strobe Error On Ocram Bank3 interrupt status enable*/

    kMECC_AccessError0InterruptStatusEnable =
        MECC_ERR_STAT_EN_ADDR_ERR0_STAT_EN_MASK, /*!< Ocram Access Error On Bank0 interrupt status enable*/
    kMECC_AccessError1InterruptStatusEnable =
        MECC_ERR_STAT_EN_ADDR_ERR1_STAT_EN_MASK, /*!< Ocram Access Error On Bank1 interrupt status enable*/
    kMECC_AccessError2InterruptStatusEnable =
        MECC_ERR_STAT_EN_ADDR_ERR2_STAT_EN_MASK, /*!< Ocram Access Error On Bank2 interrupt status enable*/
    kMECC_AccessError3InterruptStatusEnable =
        MECC_ERR_STAT_EN_ADDR_ERR3_STAT_EN_MASK, /*!< Ocram Access Error On Bank3 interrupt status enable*/

    kMECC_AllInterruptsStatusEnable = 0xFFFF, /*!< all  interrupts enable */
};

/*!
 * @brief MECC status flags.
 *
 * This provides constants for the MECC status flags for use in the MECC functions.
 */
enum
{
    kMECC_SingleError0InterruptFlag =
        MECC_ERR_STATUS_SINGLE_ERR0_MASK, /*!< Single Bit Error On Ocram Bank0 interrupt flag*/
    kMECC_SingleError1InterruptFlag =
        MECC_ERR_STATUS_SINGLE_ERR1_MASK, /*!< Single Bit Error On Ocram Bank1 interrupt flag*/
    kMECC_SingleError2InterruptFlag =
        MECC_ERR_STATUS_SINGLE_ERR2_MASK, /*!< Single Bit Error On Ocram Bank2 interrupt flag*/
    kMECC_SingleError3InterruptFlag =
        MECC_ERR_STATUS_SINGLE_ERR3_MASK, /*!< Single Bit Error On Ocram Bank3 interrupt flag*/

    kMECC_MultiError0InterruptFlag =
        MECC_ERR_STATUS_MULTI_ERR0_MASK, /*!< Multiple Bits Error On Ocram Bank0 interrupt flag*/
    kMECC_MultiError1InterruptFlag =
        MECC_ERR_STATUS_MULTI_ERR1_MASK, /*!< Multiple Bits Error On Ocram Bank1 interrupt flag*/
    kMECC_MultiError2InterruptFlag =
        MECC_ERR_STATUS_MULTI_ERR2_MASK, /*!< Multiple Bits Error On Ocram Bank2 interrupt flag*/
    kMECC_MultiError3InterruptFlag =
        MECC_ERR_STATUS_MULTI_ERR3_MASK, /*!< Multiple Bits Error On Ocram Bank3 interrupt flag*/

    kMECC_StrobeError0InterruptFlag =
        MECC_ERR_STATUS_STRB_ERR0_MASK, /*!< AXI Strobe Error On Ocram Bank0 interrupt flag*/
    kMECC_StrobeError1InterruptFlag =
        MECC_ERR_STATUS_STRB_ERR1_MASK, /*!< AXI Strobe Error On Ocram Bank1 interrupt flag*/
    kMECC_StrobeError2InterruptFlag =
        MECC_ERR_STATUS_STRB_ERR2_MASK, /*!< AXI Strobe Error On Ocram Bank2 interrupt flag*/
    kMECC_StrobeError3InterruptFlag =
        MECC_ERR_STATUS_STRB_ERR3_MASK, /*!< AXI Strobe Error On Ocram Bank3 interrupt flag*/

    kMECC_AccessError0InterruptFlag = MECC_ERR_STATUS_ADDR_ERR0_MASK, /*!< Ocram Access Error On Bank0 interrupt flag*/
    kMECC_AccessError1InterruptFlag = MECC_ERR_STATUS_ADDR_ERR1_MASK, /*!< Ocram Access Error On Bank1 interrupt flag*/
    kMECC_AccessError2InterruptFlag = MECC_ERR_STATUS_ADDR_ERR2_MASK, /*!< Ocram Access Error On Bank2 interrupt flag*/
    kMECC_AccessError3InterruptFlag = MECC_ERR_STATUS_ADDR_ERR3_MASK, /*!< Ocram Access Error On Bank3 interrupt flag*/

    kMECC_AllInterruptsFlag = 0xFFFF, /*!< all interrupts interrupt flag */
};

/*! @brief MECC ocram bank number */
enum
{
    kMECC_OcramBank0 = 0U, /*!< ocram bank number 0: ocram_base_address+0x20*i */
    kMECC_OcramBank1 = 1U, /*!< ocram bank number 1: ocram_base_address+0x20*i+0x8 */
    kMECC_OcramBank2 = 2U, /*!< ocram bank number 2: ocram_base_address+0x20*i+0x10 */
    kMECC_OcramBank3 = 3U, /*!< ocram bank number 3: ocram_base_address+0x20*i+0x18 */
};

/*! @brief MECC instance */
enum
{
    kMECC_Instance0 = 0U, /*!< Peripheral MECC1 base */
    kMECC_Instance1 = 1U, /*!< Peripheral MECC2 base */
};

/*! @brief MECC user configuration.*/
typedef struct _mecc_config
{
    bool enableMecc;             /*!< Enable the MECC function. */
    uint32_t Ocram1StartAddress; /*!< Ocram 1 start address. */
    uint32_t Ocram1EndAddress;   /*!< Ocram 1 end address. */
    uint32_t Ocram2StartAddress; /*!< Ocram 2 start address. */
    uint32_t Ocram2EndAddress;   /*!< Ocram 2 end address. */
} mecc_config_t;

/*! @brief MECC ocram single error information, including single error address, ECC code, error data and error bit
 * position */
typedef struct _mecc_single_error_info
{
    uint32_t singleErrorAddress;  /*!< Single error address on Ocram bank n */
    uint32_t singleErrorDataLow;  /*!< Single error low 32 bits uncorrected read data on Ocram bank n */
    uint32_t singleErrorDataHigh; /*!< Single error high 32 bits uncorrected read data on Ocram bank n */
    uint32_t singleErrorPosLow;   /*!< Single error bit postion of low 32 bits read data on Ocram bank n */
    uint32_t singleErrorPosHigh;  /*!< Single error bit postion of high 32 bits read data on Ocram bank n */
    uint8_t singleErrorEccCode;   /*!< Single error ECC code on Ocram bank n */
} mecc_single_error_info_t;

/*! @brief MECC ocram multiple error information, including multiple error address, ECC code, error data */
typedef struct _mecc_multi_error_info
{
    uint32_t multiErrorAddress;  /*!< Multiple error address on Ocram bank n */
    uint32_t multiErrorDataLow;  /*!< Multiple error low 32 bits read data on Ocram bank n */
    uint32_t multiErrorDataHigh; /*!< Multiple error high 32 bits read data on Ocram bank n */
    uint8_t multiErrorEccCode;   /*!< Multiple error ECC code on Ocram bank n */
} mecc_multi_error_info_t;

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
 * @brief MECC module initialization function.
 *
 * @param base MECC base address.
 * @param config pointer to the MECC configuration structure.
 */
void MECC_Init(MECC_Type *base, mecc_config_t *config);

/*!
 * @brief Deinitializes the MECC.
 *
 * @param base MECC base address.
 */
void MECC_Deinit(MECC_Type *base);

/*!
 * @brief Sets the MECC configuration structure to default values.
 *
 * @param config pointer to the MECC configuration structure.
 */
void MECC_GetDefaultConfig(mecc_config_t *config);

/* @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief Gets MECC status flags.
 *
 * @param base MECC peripheral base address.
 * @return MECC status flags.
 */
static inline uint32_t MECC_GetStatusFlags(MECC_Type *base)
{
    return base->ERR_STATUS & (uint32_t)kMECC_AllInterruptsFlag;
}

/*!
 * @brief MECC module clear interrupt status.
 *
 * @param base MECC base address.
 * @param mask status to clear.
 */
static inline void MECC_ClearStatusFlags(MECC_Type *base, uint32_t mask)
{
    base->ERR_STATUS = mask;
}

/*!
 * @brief MECC module enable interrupt status.
 *
 * @param base MECC base address.
 * @param mask status to enable.
 */
static inline void MECC_EnableInterruptStatus(MECC_Type *base, uint32_t mask)
{
    base->ERR_STAT_EN |= mask;
}

/*!
 * @brief MECC module disable interrupt status.
 *
 * @param base MECC base address.
 * @param mask status to disable.
 */
static inline void MECC_DisableInterruptStatus(MECC_Type *base, uint32_t mask)
{
    base->ERR_STAT_EN &= ~mask;
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief MECC module enable interrupt.
 *
 * @param base MECC base address.
 * @param mask The interrupts to enable.
 */
static inline void MECC_EnableInterrupts(MECC_Type *base, uint32_t mask)
{
    base->ERR_SIG_EN |= mask;
}

/*!
 * @brief MECC module disable interrupt.
 *
 * @param base MECC base address.
 * @param mask The interrupts to disable.
 */
static inline void MECC_DisableInterrupts(MECC_Type *base, uint32_t mask)
{
    base->ERR_SIG_EN &= ~mask;
}
/* @} */

/*!
 * @name functional
 * @{
 */

/*!
 * @brief MECC module error injection.
 *
 * @param base MECC base address.
 * @param lowerrordata low 32 bits data.
 * @param higherrordata high 32 bits data.
 * @param eccdata ecc code.
 * @param banknumber ocram bank number.
 * @retval kStatus_Success.
 *
 *   Bank0: ocram_base_address+0x20*i
 *   Bank1: ocram_base_address+0x20*i+0x8
 *   Bank2: ocram_base_address+0x20*i+0x10
 *   Bank3: ocram_base_address+0x20*i+0x18
 *   i = 0,1,2,3,4.....
 */
status_t MECC_ErrorInjection(
    MECC_Type *base, uint32_t lowerrordata, uint32_t higherrordata, uint8_t eccdata, uint8_t banknumber);

/*!
 * @brief MECC module get single error information.
 *
 * @param base MECC base address.
 * @param info single error information.
 * @param banknumber ocram bank number.
 * @retval kStatus_Success.
 * @retval kStatus_MECC_BankMiss.
 *
 *   Bank0: ocram_base_address+0x20*i
 *   Bank1: ocram_base_address+0x20*i+0x8
 *   Bank2: ocram_base_address+0x20*i+0x10
 *   Bank3: ocram_base_address+0x20*i+0x18
 *   i = 0,1,2,3,4.....
 */
status_t MECC_GetSingleErrorInfo(MECC_Type *base, mecc_single_error_info_t *info, uint8_t banknumber);

/*!
 * @brief MECC module get multiple error information.
 *
 * @param base MECC base address.
 * @param info multiple error information.
 * @param banknumber ocram bank number.
 * @retval kStatus_Success.
 * @retval kStatus_MECC_BankMiss.
 *
 *   Bank0: ocram_base_address+0x20*i
 *   Bank1: ocram_base_address+0x20*i+0x8
 *   Bank2: ocram_base_address+0x20*i+0x10
 *   Bank3: ocram_base_address+0x20*i+0x18
 *   i = 0,1,2,3,4.....
 */
status_t MECC_GetMultiErrorInfo(MECC_Type *base, mecc_multi_error_info_t *info, uint8_t banknumber);

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
