/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FLEXRAM_ALLOCATE_H_
#define _FSL_FLEXRAM_ALLOCATE_H_

#include "fsl_common.h"

/*!
 * @addtogroup flexram
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief SOC_FLEXRAM_ALLOCATE driver version 2.0.2. */
#define FSL_SOC_FLEXRAM_ALLOCATE_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

/*! @brief FLEXRAM bank type */
enum
{
    kFLEXRAM_BankNotUsed = 0U, /*!< bank is not used */
    kFLEXRAM_BankOCRAM   = 1U, /*!< bank is OCRAM */
    kFLEXRAM_BankDTCM    = 2U, /*!< bank is DTCM */
    kFLEXRAM_BankITCM    = 3U, /*!< bank is ITCM */
};

/*! @brief FLEXRAM bank allocate source */
typedef enum _flexram_bank_allocate_src
{
    kFLEXRAM_BankAllocateThroughHardwareFuse = 0U, /*!< allocate ram through hardware fuse value */
    kFLEXRAM_BankAllocateThroughBankCfg      = 1U, /*!< allocate ram through FLEXRAM_BANK_CFG */
} flexram_bank_allocate_src_t;

/*! @brief FLEXRAM allocate ocram, itcm, dtcm size */
typedef struct _flexram_allocate_ram
{
    const uint8_t ocramBankNum; /*!< ocram banknumber which the SOC support */
    const uint8_t dtcmBankNum;  /*!< dtcm bank number to allocate, the number should be power of 2 */
    const uint8_t itcmBankNum;  /*!< itcm bank number to allocate, the number should be power of 2 */
} flexram_allocate_ram_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief FLEXRAM allocate on-chip ram for OCRAM,ITCM,DTCM
 * This function is independent of FLEXRAM_Init, it can be called directly if ram re-allocate
 * is needed.
 * @param config allocate configuration.
 * @retval kStatus_InvalidArgument the argument is invalid
 *         kStatus_Success allocate success
 */
status_t FLEXRAM_AllocateRam(flexram_allocate_ram_t *config);

/*!
 * @brief FLEXRAM set allocate on-chip ram source
 * @param src bank config source select value.
 */
static inline void FLEXRAM_SetAllocateRamSrc(flexram_bank_allocate_src_t src)
{
    IOMUXC_GPR->GPR16 &= ~IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL_MASK;
    IOMUXC_GPR->GPR16 |= IOMUXC_GPR_GPR16_FLEXRAM_BANK_CFG_SEL(src);
}

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
