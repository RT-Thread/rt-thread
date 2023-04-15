/***************************************************************************//**
* \file cy_crypto_core_trng.h
* \version 2.70
*
* \brief
*  This file provides provides constant and parameters
*  for the API of the TRNG in the Crypto block driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#if !defined (CY_CRYPTO_CORE_TRNG_H)
#define CY_CRYPTO_CORE_TRNG_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 14.3', 2, \
'Since value of CY_CRYPTO_V1 is decided by PDL device agnostic / hardware specific model, controlling expression will not have an invariant value.');

#if (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C)

#include "cy_crypto_core_hw.h"


typedef cy_en_crypto_status_t (*cy_crypto_trng_func_t)(CRYPTO_Type *base,
                                             uint32_t  GAROPol,
                                             uint32_t  FIROPol,
                                             uint32_t  max,
                                             uint32_t *randomNum);

/**
* \addtogroup group_crypto_lld_rng_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng
****************************************************************************//**
*
* Generates a True Random Number.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param GAROPol
* The polynomial for the programmable Galois ring oscillator.
*
* \param FIROPol
* The polynomial for the programmable Fibonacci ring oscillator.
*
* \param max
* The maximum length of a random number, in the range of [0, 32] bits.
*
* \param randomNum
* The pointer to a generated true random number. Must be 4-byte aligned.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_Trng(CRYPTO_Type *base,
                                             uint32_t  GAROPol,
                                             uint32_t  FIROPol,
                                             uint32_t  max,
                                             uint32_t *randomNum);

/** \} group_crypto_lld_rng_functions */



/** \cond INTERNAL */

/* Macros for conditions used by CY_ASSERT calls */
#define CY_CRYPTO_IS_SMPL_CLK_DIV_VALID(clkDiv)     ((clkDiv) <= 255U)
#define CY_CRYPTO_IS_RED_CLK_DIV_VALID(clkDiv)      ((clkDiv) <= 255U)
#define CY_CRYPTO_IS_INIT_DELAY_VALID(delay)        ((delay) <= 255U)
#define CY_CRYPTO_IS_VONN_CORR_VALID(val)           ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_AP_DETECT_VALID(val)           ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_RC_DETECT_VALID(val)           ((uint32_t)(val) <= 1U)

#define CY_CRYPTO_IS_RO11_EN_VALID(val)             ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_RO15_EN_VALID(val)             ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_GARO15_EN_VALID(val)           ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_GARO31_EN_VALID(val)           ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_FIRO15_EN_VALID(val)           ((uint32_t)(val) <= 1U)
#define CY_CRYPTO_IS_FIRO31_EN_VALID(val)           ((uint32_t)(val) <= 1U)

#define CY_CRYPTO_IS_GARO_POLY_VALID(val)           ((val) <= 0x7FFFFFFFUL)
#define CY_CRYPTO_IS_FIRO_POLY_VALID(val)           ((val) <= 0x7FFFFFFFUL)

#define CY_CRYPTO_IS_BS_SELECT_VALID(val)           (((val) == CY_CRYPTO_TRMON_BS_DAS) || \
                                                     ((val) == CY_CRYPTO_TRMON_BS_RED) || \
                                                     ((val) == CY_CRYPTO_TRMON_BS_TR))

#define CY_CRYPTO_IS_CCOUNT8_VALID(val)             ((val) <= 255U)
#define CY_CRYPTO_IS_CCOUNT16_VALID(val)            ((val) <= 65535U)
#define CY_CRYPTO_IS_WINSIZE_VALID(val)             ((val) <= 65535U)

#define CY_CRYPTO_TRNG_AP_DETECT_ERROR_BIT          (0U)
#define CY_CRYPTO_TRNG_RC_DETECT_ERROR_BIT          (1U)
#define CY_CRYPTO_TRNG_AP_DETECT_ERROR              (1U << 0U)
#define CY_CRYPTO_TRNG_RC_DETECT_ERROR              (1U << 1U)

#define CY_CRYPTO_TRNG_RO_ALL_MASK                  (uint32_t)(CRYPTO_TR_CTL1_RO11_EN_Msk | \
                                                     CRYPTO_TR_CTL1_RO15_EN_Msk | \
                                                     CRYPTO_TR_CTL1_GARO15_EN_Msk | CRYPTO_TR_CTL1_GARO31_EN_Msk | \
                                                     CRYPTO_TR_CTL1_FIRO15_EN_Msk | CRYPTO_TR_CTL1_FIRO31_EN_Msk)

extern const cy_stc_crypto_trng_config_t     cy_trngDefaultConfig;

/** \endcond */

void Cy_Crypto_Core_Trng_Init(CRYPTO_Type *base, cy_stc_crypto_trng_config_t *config);
void     Cy_Crypto_Core_Trng_DeInit(CRYPTO_Type *base);

cy_en_crypto_status_t Cy_Crypto_Core_Trng_Start(CRYPTO_Type *base, uint32_t dataSize);
cy_en_crypto_status_t Cy_Crypto_Core_Trng_ReadData(CRYPTO_Type *base, uint32_t *randomData);

__STATIC_INLINE bool Cy_Crypto_Core_Trng_IsInitialized(CRYPTO_Type *base);

__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_GetRoStatus(CRYPTO_Type *base, cy_en_crypto_trng_ro_sel_t roSelector);
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetRoStatus(CRYPTO_Type *base,
                                                     cy_en_crypto_trng_ro_sel_t roSelector, uint8_t roStatus);
__STATIC_INLINE bool Cy_Crypto_Core_Trng_IsRoEnabled(CRYPTO_Type *base, cy_en_crypto_trng_ro_sel_t roSelector);
__STATIC_INLINE bool Cy_Crypto_Core_Trng_AnyRoEnabled(CRYPTO_Type *base);

__STATIC_INLINE uint32_t Cy_Crypto_Core_Trng_GetData(CRYPTO_Type *base);
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetData(CRYPTO_Type *base, uint32_t randomData);

__STATIC_INLINE void Cy_Crypto_Core_Trng_SetGaroPoly(CRYPTO_Type *base, uint32_t poly);
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetFiroPoly(CRYPTO_Type *base, uint32_t poly);
__STATIC_INLINE uint32_t Cy_Crypto_Core_Trng_GetGaroPoly(CRYPTO_Type *base);
__STATIC_INLINE uint32_t Cy_Crypto_Core_Trng_GetFiroPoly(CRYPTO_Type *base);

__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetHealthStatus(CRYPTO_Type *base);

__STATIC_INLINE uint8_t  Cy_Crypto_Core_Trng_MonGetRcRepCount(CRYPTO_Type *base);
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApOccCount(CRYPTO_Type *base);
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApWindowIndex(CRYPTO_Type *base);

__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetRcCurrentBit(CRYPTO_Type *base);
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetApCurrentBit(CRYPTO_Type *base);

__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Trng_MonSetBSSelector(CRYPTO_Type *base, cy_en_crypto_trng_bs_sel_t bitStreamSelector);
__STATIC_INLINE cy_en_crypto_trng_bs_sel_t Cy_Crypto_Core_Trng_MonGetBSSelector(CRYPTO_Type *base);

__STATIC_INLINE void Cy_Crypto_Core_Trng_MonEnableApTest(CRYPTO_Type *base);
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonDisableApTest(CRYPTO_Type *base);
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonEnableRcTest(CRYPTO_Type *base);
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonDisableRcTest(CRYPTO_Type *base);

__STATIC_INLINE void Cy_Crypto_Core_Trng_MonSetRcCC8(CRYPTO_Type *base, uint8_t ccCount);
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetRcCC8(CRYPTO_Type *base);

__STATIC_INLINE void Cy_Crypto_Core_Trng_MonSetApCC16(CRYPTO_Type *base, uint16_t ccCount);
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApCC16(CRYPTO_Type *base);

__STATIC_INLINE void Cy_Crypto_Core_Trng_MonSetApWinSize(CRYPTO_Type *base, uint16_t windowSize);
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApWinSize(CRYPTO_Type *base);

__STATIC_INLINE void Cy_Crypto_Core_Trng_WaitForReady(CRYPTO_Type *base);
__STATIC_INLINE void Cy_Crypto_Core_Trng_WaitForComplete(CRYPTO_Type *base);

/*
 * API Implementations
 */

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_IsReady
****************************************************************************//**
*
* Checks for TRNG hardware is ready.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* true when TRNG hardware is ready, otherwise false.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_Crypto_Core_Trng_IsReady(CRYPTO_Type *base)
{
    bool status = false;

    /* Check for TRNG instruction is complete */
    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        status = (0uL == (REG_CRYPTO_STATUS(base) & CRYPTO_STATUS_TR_BUSY_Msk));
        #endif
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        status = (0uL == _FLD2VAL(CRYPTO_V2_STATUS_BUSY, REG_CRYPTO_STATUS(base)));
        #endif
    }

    return status;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_IsRandomComplete
****************************************************************************//**
*
* Checks for TRNG random number generation is complete.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* true when TRNG random number generation is complete, otherwise false.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_Crypto_Core_Trng_IsRandomComplete(CRYPTO_Type *base)
{
    uint32_t status;

    /* Check for TRNG instruction is complete */
    status = Cy_Crypto_Core_GetInterruptStatus(base) & (CRYPTO_INTR_TR_DATA_AVAILABLE_Msk | CRYPTO_INTR_TR_AP_DETECT_ERROR_Msk | CRYPTO_INTR_TR_RC_DETECT_ERROR_Msk);

    return (status != 0UL);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_IsInitialized
****************************************************************************//**
*
* Checks for TRNG hardware is initialized.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* true when TRNG hardware is initialized, otherwise false.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_Crypto_Core_Trng_IsInitialized(CRYPTO_Type *base)
{
    return ((Cy_Crypto_Core_GetInterruptStatus(base) & CRYPTO_INTR_TR_INITIALIZED_Msk) != 0U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_WaitForComplete
****************************************************************************//**
*
* Waits for TRNG random generation is complete.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \note
* After this call the Health Monitor status should be checked to ensure that
* random data is healthy.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_WaitForComplete(CRYPTO_Type *base)
{
    uint32_t status;
    /* Wait until the TRNG random generation is complete */
    do
    {
        status = Cy_Crypto_Core_GetInterruptStatus(base) & (CRYPTO_INTR_TR_DATA_AVAILABLE_Msk  |
                                                            CRYPTO_INTR_TR_AP_DETECT_ERROR_Msk |
                                                            CRYPTO_INTR_TR_RC_DETECT_ERROR_Msk);
    }
    while (status == 0U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_WaitForReady
****************************************************************************//**
*
* Waits for TRNG operation is ready.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_WaitForReady(CRYPTO_Type *base)
{
    /* Wait until the TRNG instruction is complete */
    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        while (0uL != (REG_CRYPTO_STATUS(base) & CRYPTO_STATUS_TR_BUSY_Msk))
        {
        }
        #endif
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        while (0uL != REG_CRYPTO_STATUS(base))
        {
        }
        #endif
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_GetRoStatus
****************************************************************************//**
*
* Reads the ring oscillator enable status.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param roSelector
* The ring oscillator selector (see \ref cy_en_crypto_trng_ro_sel_t).
*
* \return
* The ring oscillator enabled status (0 or 1).
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_GetRoStatus(CRYPTO_Type *base, cy_en_crypto_trng_ro_sel_t roSelector)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to wider 32bit.');
    return (REG_CRYPTO_TR_CTL1(base) & (uint32_t)(1U << ((uint32_t)roSelector))) != 0U ? 1U : 0U;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_SetRoStatus
****************************************************************************//**
*
* Sets the ring oscillator enable status.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param roSelector
* The ring oscillator selector (see \ref cy_en_crypto_trng_ro_sel_t).
*
* \param roStatus
* The new ring oscillator status value (0 or 1).
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetRoStatus(CRYPTO_Type *base,
                                                        cy_en_crypto_trng_ro_sel_t roSelector, uint8_t roStatus)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.6','enum cy_en_crypto_trng_ro_sel_t to uint32_t conversion intentional.');
    uint32_t roMask = 1U << (uint32_t)roSelector;
    uint32_t roData = (REG_CRYPTO_TR_CTL1(base) & ~roMask) | (((uint32_t)roStatus != 0U) ? roMask : 0U);
    REG_CRYPTO_TR_CTL1(base) = roData;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_IsRoEnabled
****************************************************************************//**
*
* Checks if the specified ring oscillator is enabled.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param roSelector
* The ring oscillator selector (see \ref cy_en_crypto_trng_ro_sel_t).
*
* \return
* true - if the ring oscillator is enabled otherwise false.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_Crypto_Core_Trng_IsRoEnabled(CRYPTO_Type *base, cy_en_crypto_trng_ro_sel_t roSelector)
{
    return (Cy_Crypto_Core_Trng_GetRoStatus(base, roSelector) != 0U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_AnyRoEnabled
****************************************************************************//**
*
* Checks if any ring oscillator is enabled.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param roSelector
* The ring oscillator selector (see \ref cy_en_crypto_trng_ro_sel_t).
*
* \return
* true - if at least one ring oscillator is enabled otherwise false.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_Crypto_Core_Trng_AnyRoEnabled(CRYPTO_Type *base)
{
    return ((REG_CRYPTO_TR_CTL1(base) & CY_CRYPTO_TRNG_RO_ALL_MASK) != 0U);
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_GetData
****************************************************************************//**
*
* Reads the generated random number in non-blocking mode.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The generated random number.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_Crypto_Core_Trng_GetData(CRYPTO_Type *base)
{
    return REG_CRYPTO_TR_RESULT(base);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_SetData
****************************************************************************//**
*
* Sets the random number value.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param randomData
* The new random number value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetData(CRYPTO_Type *base, uint32_t randomData)
{
    REG_CRYPTO_TR_RESULT(base) = randomData;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_SetGaroPoly
****************************************************************************//**
*
* Sets the polynomial value for the Galois ring oscillator.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param poly
* The polynomial for the programmable Galois ring oscillator.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetGaroPoly(CRYPTO_Type *base, uint32_t poly)
{
    REG_CRYPTO_TR_GARO_CTL(base) = poly & CRYPTO_TR_GARO_CTL_POLYNOMIAL31_Msk;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_SetFiroPoly
****************************************************************************//**
*
* Sets the polynomial value for the Fibonacci ring oscillator.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param poly
* The polynomial for the programmable Fibonacci ring oscillator.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_SetFiroPoly(CRYPTO_Type *base, uint32_t poly)
{
    REG_CRYPTO_TR_FIRO_CTL(base) = poly & CRYPTO_TR_FIRO_CTL_POLYNOMIAL31_Msk;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_GetGaroPoly
****************************************************************************//**
*
* Reads the polynomial value of the Galois ring oscillator.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The polynomial of the programmable Galois ring oscillator.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_Crypto_Core_Trng_GetGaroPoly(CRYPTO_Type *base)
{
    return REG_CRYPTO_TR_GARO_CTL(base);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_GetFiroPoly
****************************************************************************//**
*
* Reads the polynomial value of the Fibonacci ring oscillator.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The polynomial of the programmable Fibonacci ring oscillator.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_Crypto_Core_Trng_GetFiroPoly(CRYPTO_Type *base)
{
    return REG_CRYPTO_TR_FIRO_CTL(base);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetHealthStatus
****************************************************************************//**
*
* Returns the health status of the random number health monitor in two bits.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The health status:
*  - ZERO  - if data is healthy
*  - bit 0 - Adaptive Proportion (AP) error is detected
*  - bit 1 - Repetition Count (RC) error is detected
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetHealthStatus(CRYPTO_Type *base)
{
    return (uint8_t)((REG_CRYPTO_INTR(base) \
                      & (CRYPTO_INTR_TR_AP_DETECT_ERROR_Msk | CRYPTO_INTR_TR_RC_DETECT_ERROR_Msk)) \
                      >> CRYPTO_INTR_TR_AP_DETECT_ERROR_Pos);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonClearHealthStatus
****************************************************************************//**
*
* Clears the health status of the random number health monitor
* in the interrupts register
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonClearHealthStatus(CRYPTO_Type *base)
{
    Cy_Crypto_Core_ClearInterrupt(base, CRYPTO_INTR_TR_AP_DETECT_ERROR_Msk | CRYPTO_INTR_TR_RC_DETECT_ERROR_Msk);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetRcRepCount
****************************************************************************//**
*
* Reads the current number of repetitions from the repetition counter
* test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The number of repetitions of the current active bit counter.
*
*******************************************************************************/
__STATIC_INLINE uint8_t  Cy_Crypto_Core_Trng_MonGetRcRepCount(CRYPTO_Type *base)
{
    return ((uint8_t)_FLD2VAL(CRYPTO_TR_MON_RC_STATUS1_REP_COUNT, REG_CRYPTO_TR_MON_RC_STATUS1(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetApOccCount
****************************************************************************//**
*
* Reads the current Cutoff count number from the adaptive proportion
* test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The Cutoff count number of the adaptive proportion test.
*
*******************************************************************************/
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApOccCount(CRYPTO_Type *base)
{
    return ((uint16_t)_FLD2VAL(CRYPTO_TR_MON_AP_STATUS1_OCC_COUNT, REG_CRYPTO_TR_MON_AP_STATUS1(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetApWindowIndex
****************************************************************************//**
*
* Reads the current window index from the adaptive proportion test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The window index of the adaptive proportion test.
*
*******************************************************************************/
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApWindowIndex(CRYPTO_Type *base)
{
    return ((uint16_t)_FLD2VAL(CRYPTO_TR_MON_AP_STATUS1_WINDOW_INDEX, REG_CRYPTO_TR_MON_AP_STATUS1(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetRcCurrentBit
****************************************************************************//**
*
* Reads the active bit value from the adaptive proportion test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The active bit value.
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetRcCurrentBit(CRYPTO_Type *base)
{
    return ((uint8_t)_FLD2VAL(CRYPTO_TR_MON_RC_STATUS0_BIT, REG_CRYPTO_TR_MON_RC_STATUS0(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetApCurrentBit
****************************************************************************//**
*
* Reads the active bit value from the repetition counter test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The active bit value.
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetApCurrentBit(CRYPTO_Type *base)
{
    return ((uint8_t)_FLD2VAL(CRYPTO_TR_MON_AP_STATUS0_BIT, REG_CRYPTO_TR_MON_AP_STATUS0(base)));
}


/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonSetBSSelector
****************************************************************************//**
*
* Sets the BitStream selector value of the TRNG monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param bitStreamSelector
* The BitStream selector value (see \ref cy_en_crypto_trng_bs_sel_t).
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Trng_MonSetBSSelector(CRYPTO_Type *base,
                                                                           cy_en_crypto_trng_bs_sel_t bitStreamSelector)
{
    cy_en_crypto_status_t status = CY_CRYPTO_SUCCESS;

    CY_ASSERT_L3(CY_CRYPTO_IS_BS_SELECT_VALID(bitStreamSelector));

    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_CTL(base), CRYPTO_TR_MON_CTL_BITSTREAM_SEL, bitStreamSelector);

    return status;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetBSSelector
****************************************************************************//**
*
* Reads the BitStream selector value of the TRNG monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The BitStream selector value (see \ref cy_en_crypto_trng_bs_sel_t).
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_trng_bs_sel_t Cy_Crypto_Core_Trng_MonGetBSSelector(CRYPTO_Type *base)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_crypto_trng_bs_sel_t enum.');
    return ((cy_en_crypto_trng_bs_sel_t)_FLD2VAL(CRYPTO_TR_MON_CTL_BITSTREAM_SEL, REG_CRYPTO_TR_MON_CTL(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonEnableApTest
****************************************************************************//**
*
* Enables the Adaptive proportion (AP) test.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonEnableApTest(CRYPTO_Type *base)
{
    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_CMD(base), CRYPTO_TR_MON_CMD_START_AP, 1U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonDisableApTest
****************************************************************************//**
*
* Disables the Adaptive proportion (AP) test.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonDisableApTest(CRYPTO_Type *base)
{
    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_CMD(base), CRYPTO_TR_MON_CMD_START_AP, 0U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonEnableRcTest
****************************************************************************//**
*
* Enables the Repetition count (RC) test.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonEnableRcTest(CRYPTO_Type *base)
{
    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_CMD(base), CRYPTO_TR_MON_CMD_START_RC, 1U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonDisableRcTest
****************************************************************************//**
*
* Disables the Repetition count (RC) test.
*
* \param base
* The pointer to the CRYPTO instance.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonDisableRcTest(CRYPTO_Type *base)
{
    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_CMD(base), CRYPTO_TR_MON_CMD_START_RC, 0U);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonSetRcCC8
****************************************************************************//**
*
* Sets the Cutoff counter value of the repetition counter test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param ccCount
* The new Cutoff counter value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonSetRcCC8(CRYPTO_Type *base, uint8_t ccCount)
{
    REG_CRYPTO_TR_MON_RC_CTL(base) = (uint32_t)_VAL2FLD(CRYPTO_TR_MON_RC_CTL_CUTOFF_COUNT8, ccCount);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetRcCC8
****************************************************************************//**
*
* Reads the Cutoff counter value of the repetition counter test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The Cutoff counter value.
*
*******************************************************************************/
__STATIC_INLINE uint8_t Cy_Crypto_Core_Trng_MonGetRcCC8(CRYPTO_Type *base)
{
    return ((uint8_t)_FLD2VAL(CRYPTO_TR_MON_RC_CTL_CUTOFF_COUNT8, REG_CRYPTO_TR_MON_RC_CTL(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonSetApCC16
****************************************************************************//**
*
* Sets the Cutoff counter value of the adaptive proportion test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param ccCount
* The new Cutoff counter value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonSetApCC16(CRYPTO_Type *base, uint16_t ccCount)
{
    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_AP_CTL(base), CRYPTO_TR_MON_AP_CTL_CUTOFF_COUNT16, ccCount);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetApCC16
****************************************************************************//**
*
* Reads the Cutoff counter value of the adaptive proportion test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The Cutoff counter value.
*
*******************************************************************************/
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApCC16(CRYPTO_Type *base)
{
    return ((uint16_t)_FLD2VAL(CRYPTO_TR_MON_AP_CTL_CUTOFF_COUNT16, REG_CRYPTO_TR_MON_AP_CTL(base)));
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonSetApWinSize
****************************************************************************//**
*
* Sets the window size value of the adaptive proportion test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param windowSize
* The new windows size value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_Crypto_Core_Trng_MonSetApWinSize(CRYPTO_Type *base, uint16_t windowSize)
{
    CY_REG32_CLR_SET(REG_CRYPTO_TR_MON_AP_CTL(base), CRYPTO_TR_MON_AP_CTL_WINDOW_SIZE, windowSize);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Trng_MonGetApWinSize
****************************************************************************//**
*
* Reads the window size value of the adaptive proportion test monitor.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \return
* The windows size value.
*
*******************************************************************************/
__STATIC_INLINE uint16_t Cy_Crypto_Core_Trng_MonGetApWinSize(CRYPTO_Type *base)
{
    return ((uint16_t)_FLD2VAL(CRYPTO_TR_MON_AP_CTL_WINDOW_SIZE, REG_CRYPTO_TR_MON_AP_CTL(base)));
}





#endif /* #if (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C) */

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 14.3');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_TRNG_H) */


/* [] END OF FILE */
