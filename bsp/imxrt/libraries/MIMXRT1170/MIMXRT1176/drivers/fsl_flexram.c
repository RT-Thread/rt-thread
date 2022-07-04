/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexram.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexram"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Gets the instance from the base address to be used to gate or ungate the module clock
 *
 * @param base FLEXRAM base address
 *
 * @return The FLEXRAM instance
 */
static uint32_t FLEXRAM_GetInstance(FLEXRAM_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Pointers to FLEXRAM bases for each instance. */
static FLEXRAM_Type *const s_flexramBases[] = FLEXRAM_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to FLEXRAM clocks for each instance. */
static const clock_ip_name_t s_flexramClocks[] = FLEXRAM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
/*! Look-up table to calculate single-bit error bit position for ITCM. */
static const uint8_t ItcmLookUpTable[64] = {
    0xC1, 0x43, 0x9E, 0x83, 0x15, 0x4C, 0x4A, 0x8C, 0x31, 0x1C, 0xA2, 0xE0, 0x51, 0x2C, 0xC2, 0xD0,
    0x19, 0x1A, 0x26, 0xEA, 0x29, 0x94, 0x16, 0x64, 0x37, 0xA4, 0x0D, 0xC4, 0x75, 0x38, 0x4F, 0x58,
    0x46, 0x91, 0x86, 0x61, 0x49, 0x98, 0x89, 0x68, 0x32, 0x34, 0x07, 0xC8, 0x92, 0xA8, 0xA7, 0x54,
    0xA1, 0xD9, 0x25, 0xF8, 0x0E, 0x0B, 0x8A, 0x2A, 0x52, 0x45, 0x13, 0x85, 0x62, 0x70, 0x23, 0xB0};
/*! Look-up table to calculate single-bit error bit position for DTCM. */
static const uint8_t DtcmLookUpTable[32] = {0x61, 0x51, 0x19, 0x45, 0x43, 0x31, 0x29, 0x13, 0x62, 0x52, 0x4A,
                                            0x46, 0x32, 0x2A, 0x23, 0x1A, 0x2C, 0x64, 0x26, 0x25, 0x34, 0x16,
                                            0x15, 0x54, 0x0B, 0x58, 0x1C, 0x4C, 0x38, 0x0E, 0x0D, 0x49};
#endif /* FLEXRAM_ECC_ERROR_DETAILED_INFO */

/*******************************************************************************
 * Code
 ******************************************************************************/
static uint32_t FLEXRAM_GetInstance(FLEXRAM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_flexramBases); instance++)
    {
        if (s_flexramBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_flexramBases));

    return instance;
}

/*!
 * brief FLEXRAM module initialization function.
 *
 * param base FLEXRAM base address.
 */
void FLEXRAM_Init(FLEXRAM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate ENET clock. */
    CLOCK_EnableClock(s_flexramClocks[FLEXRAM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* enable all the interrupt status */
    base->INT_STAT_EN |= (uint32_t)kFLEXRAM_InterruptStatusAll;
    /* clear all the interrupt status */
    base->INT_STATUS |= (uint32_t)kFLEXRAM_InterruptStatusAll;
    /* disable all the interrpt */
    base->INT_SIG_EN = 0U;
}

/*!
 * brief Deinitializes the FLEXRAM.
 *
 */
void FLEXRAM_Deinit(FLEXRAM_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate ENET clock. */
    CLOCK_DisableClock(s_flexramClocks[FLEXRAM_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

#if (defined(FSL_FEATURE_FLEXRAM_HAS_ECC) && FSL_FEATURE_FLEXRAM_HAS_ECC)
void FLEXRAM_EnableECC(FLEXRAM_Type *base, bool OcramECCEnable, bool TcmECCEnable)
{
    if (true == OcramECCEnable)
    {
        base->FLEXRAM_CTRL |= FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN_MASK;
    }
    else
    {
        base->FLEXRAM_CTRL &= ~FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN_MASK;
    }

    if (true == TcmECCEnable)
    {
        base->FLEXRAM_CTRL |= FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN_MASK;
    }
    else
    {
        base->FLEXRAM_CTRL &= ~FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN_MASK;
    }
}

void FLEXRAM_GetOcramSingleErroInfo(FLEXRAM_Type *base, flexram_ocram_ecc_single_error_info_t *info)
{
    assert(NULL != info);

#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    info->OcramSingleErrorECCCipher =
        (uint8_t)((base->OCRAM_ECC_SINGLE_ERROR_INFO & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC_MASK) >>
                  FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC_SHIFT);
    info->OcramSingleErrorECCSyndrome =
        (uint8_t)((base->OCRAM_ECC_SINGLE_ERROR_INFO & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN_MASK) >>
                  FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN_SHIFT);
#else
    info->OcramSingleErrorInfo = base->OCRAM_ECC_SINGLE_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

    info->OcramSingleErrorAddr    = base->OCRAM_ECC_SINGLE_ERROR_ADDR;
    info->OcramSingleErrorDataLSB = base->OCRAM_ECC_SINGLE_ERROR_DATA_LSB;
    info->OcramSingleErrorDataMSB = base->OCRAM_ECC_SINGLE_ERROR_DATA_MSB;
}

void FLEXRAM_GetOcramMultiErroInfo(FLEXRAM_Type *base, flexram_ocram_ecc_multi_error_info_t *info)
{
    assert(NULL != info);

#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    info->OcramMultiErrorECCCipher =
        (uint8_t)((base->OCRAM_ECC_MULTI_ERROR_INFO & FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC_MASK) >>
                  FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC_SHIFT);
#else
    info->OcramMultiErrorInfo  = base->OCRAM_ECC_MULTI_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    info->OcramMultiErrorAddr    = base->OCRAM_ECC_MULTI_ERROR_ADDR;
    info->OcramMultiErrorDataLSB = base->OCRAM_ECC_MULTI_ERROR_DATA_LSB;
    info->OcramMultiErrorDataMSB = base->OCRAM_ECC_MULTI_ERROR_DATA_MSB;
}

void FLEXRAM_GetItcmSingleErroInfo(FLEXRAM_Type *base, flexram_itcm_ecc_single_error_info_t *info)
{
    assert(NULL != info);

#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    /* ECC error corresponding syndrome, which can be used to locate the Error bit using a look-up table. */
    uint8_t singleErrorECCSyndrome = 0x00U;

    info->ItcmSingleErrorTCMWriteRead =
        (uint8_t)((base->ITCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW_MASK) >>
                  FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW_SHIFT);
    info->ItcmSingleErrorTCMAccessSize =
        (uint8_t)((base->ITCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ_MASK) >>
                  FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ_SHIFT);
    info->ItcmSingleErrorTCMMaster =
        (uint8_t)((base->ITCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST_MASK) >>
                  FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST_SHIFT);
    info->ItcmSingleErrorTCMPrivilege =
        (uint8_t)((base->ITCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT_MASK) >>
                  FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT_SHIFT);
    singleErrorECCSyndrome =
        (uint8_t)((base->ITCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN_MASK) >>
                  FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN_SHIFT);

    for (uint8_t i = 0x00U; i < sizeof(ItcmLookUpTable) / sizeof(ItcmLookUpTable[0]); i++)
    {
        if (singleErrorECCSyndrome == ItcmLookUpTable[i])
        {
            info->ItcmSingleErrorBitPostion = i;
            break;
        }
    }
#else
    info->ItcmSingleErrorInfo  = base->ITCM_ECC_SINGLE_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

    info->ItcmSingleErrorAddr    = base->ITCM_ECC_SINGLE_ERROR_ADDR;
    info->ItcmSingleErrorDataLSB = base->ITCM_ECC_SINGLE_ERROR_DATA_LSB;
    info->ItcmSingleErrorDataMSB = base->ITCM_ECC_SINGLE_ERROR_DATA_MSB;
}

void FLEXRAM_GetItcmMultiErroInfo(FLEXRAM_Type *base, flexram_itcm_ecc_multi_error_info_t *info)
{
    assert(NULL != info);

#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    info->ItcmMultiErrorTCMWriteRead =
        (uint8_t)((base->ITCM_ECC_MULTI_ERROR_INFO & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFW_MASK) >>
                  FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFW_SHIFT);
    info->ItcmMultiErrorTCMAccessSize =
        (uint8_t)((base->ITCM_ECC_MULTI_ERROR_INFO & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFSIZ_MASK) >>
                  FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFSIZ_SHIFT);
    info->ItcmMultiErrorTCMMaster =
        (uint8_t)((base->ITCM_ECC_MULTI_ERROR_INFO & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFMST_MASK) >>
                  FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFMST_SHIFT);
    info->ItcmMultiErrorTCMPrivilege =
        (uint8_t)((base->ITCM_ECC_MULTI_ERROR_INFO & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFPRT_MASK) >>
                  FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFPRT_SHIFT);
    info->ItcmMultiErrorECCSyndrome =
        (uint8_t)((base->ITCM_ECC_MULTI_ERROR_INFO & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFSYN_MASK) >>
                  FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFSYN_SHIFT);
#else
    info->ItcmMultiErrorInfo   = base->ITCM_ECC_MULTI_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

    info->ItcmMultiErrorAddr    = base->ITCM_ECC_MULTI_ERROR_ADDR;
    info->ItcmMultiErrorDataLSB = base->ITCM_ECC_MULTI_ERROR_DATA_LSB;
    info->ItcmMultiErrorDataMSB = base->ITCM_ECC_MULTI_ERROR_DATA_MSB;
}

void FLEXRAM_GetDtcmSingleErroInfo(FLEXRAM_Type *base, flexram_dtcm_ecc_single_error_info_t *info, uint8_t bank)
{
    assert(NULL != info);
    assert((0x00U == bank) || (0x01U == bank));

    if (0x00U == bank)
    {
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
        /* ECC error corresponding syndrome, which can be used to locate the Error bit using a look-up table. */
        uint8_t singleErrorECCSyndrome = 0x00U;

        info->DtcmSingleErrorTCMWriteRead =
            (uint8_t)((base->D0TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW_MASK) >>
                      FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW_SHIFT);
        info->DtcmSingleErrorTCMAccessSize =
            (uint8_t)((base->D0TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ_MASK) >>
                      FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ_SHIFT);
        info->DtcmSingleErrorTCMMaster =
            (uint8_t)((base->D0TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST_MASK) >>
                      FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST_SHIFT);
        info->DtcmSingleErrorTCMPrivilege =
            (uint8_t)((base->D0TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT_MASK) >>
                      FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT_SHIFT);
        singleErrorECCSyndrome =
            (uint8_t)((base->D0TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN_MASK) >>
                      FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN_SHIFT);

        for (uint8_t i = 0x00U; i < sizeof(ItcmLookUpTable) / sizeof(ItcmLookUpTable[0]); i++)
        {
            if (singleErrorECCSyndrome == ItcmLookUpTable[i])
            {
                info->DtcmSingleErrorBitPostion = i;
                break;
            }
        }
#else
        info->DtcmSingleErrorInfo = base->D0TCM_ECC_SINGLE_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

        info->DtcmSingleErrorAddr = base->D0TCM_ECC_SINGLE_ERROR_ADDR;
        info->DtcmSingleErrorData = base->D0TCM_ECC_SINGLE_ERROR_DATA;
    }
    else
    {
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
        /* ECC error corresponding syndrome, which can be used to locate the Error bit using a look-up table. */
        uint8_t singleErrorECCSyndrome = 0x00U;

        info->DtcmSingleErrorTCMWriteRead =
            (uint8_t)((base->D1TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW_MASK) >>
                      FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW_SHIFT);
        info->DtcmSingleErrorTCMAccessSize =
            (uint8_t)((base->D1TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ_MASK) >>
                      FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ_SHIFT);
        info->DtcmSingleErrorTCMMaster =
            (uint8_t)((base->D1TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST_MASK) >>
                      FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST_SHIFT);
        info->DtcmSingleErrorTCMPrivilege =
            (uint8_t)((base->D1TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT_MASK) >>
                      FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT_SHIFT);
        singleErrorECCSyndrome =
            (uint8_t)((base->D1TCM_ECC_SINGLE_ERROR_INFO & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN_MASK) >>
                      FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN_SHIFT);

        for (uint8_t i = 0x00U; i < sizeof(DtcmLookUpTable) / sizeof(DtcmLookUpTable[0]); i++)
        {
            if (singleErrorECCSyndrome == DtcmLookUpTable[i])
            {
                info->DtcmSingleErrorBitPostion = i;
                break;
            }
        }
#else
        info->DtcmSingleErrorInfo = base->D1TCM_ECC_SINGLE_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

        info->DtcmSingleErrorAddr = base->D1TCM_ECC_SINGLE_ERROR_ADDR;
        info->DtcmSingleErrorData = base->D1TCM_ECC_SINGLE_ERROR_DATA;
    }
}

void FLEXRAM_GetDtcmMultiErroInfo(FLEXRAM_Type *base, flexram_dtcm_ecc_multi_error_info_t *info, uint8_t bank)
{
    assert(NULL != info);
    assert((0x00U == bank) || (0x01U == bank));

    if (0x00U == bank)
    {
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
        info->DtcmMultiErrorTCMWriteRead =
            (uint8_t)((base->D0TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFW_MASK) >>
                      FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFW_SHIFT);
        info->DtcmMultiErrorTCMAccessSize =
            (uint8_t)((base->D0TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFSIZ_MASK) >>
                      FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFSIZ_SHIFT);
        info->DtcmMultiErrorTCMMaster =
            (uint8_t)((base->D0TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFMST_MASK) >>
                      FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFMST_SHIFT);
        info->DtcmMultiErrorTCMPrivilege =
            (uint8_t)((base->D0TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFPRT_MASK) >>
                      FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFPRT_SHIFT);
        info->DtcmMultiErrorECCSyndrome =
            (uint8_t)((base->D0TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFSYN_MASK) >>
                      FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCS_EFSYN_SHIFT);
#else
        info->DtcmMultiErrorInfo  = base->D0TCM_ECC_MULTI_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

        info->DtcmMultiErrorAddr = base->D0TCM_ECC_MULTI_ERROR_ADDR;
        info->DtcmMultiErrorData = base->D0TCM_ECC_MULTI_ERROR_DATA;
    }
    else
    {
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
        info->DtcmMultiErrorTCMWriteRead =
            (uint8_t)((base->D1TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFW_MASK) >>
                      FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCS_EFW_SHIFT);
        info->DtcmMultiErrorTCMAccessSize =
            (uint8_t)((base->D1TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFSIZ_MASK) >>
                      FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCS_EFSIZ_SHIFT);
        info->DtcmMultiErrorTCMMaster =
            (uint8_t)((base->D1TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFMST_MASK) >>
                      FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCS_EFMST_SHIFT);
        info->DtcmMultiErrorTCMPrivilege =
            (uint8_t)((base->D1TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFPRT_MASK) >>
                      FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCS_EFPRT_SHIFT);
        info->DtcmMultiErrorECCSyndrome =
            (uint8_t)((base->D1TCM_ECC_MULTI_ERROR_INFO & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_ITCM_ECCS_EFSYN_MASK) >>
                      FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCS_EFSYN_SHIFT);
#else
        info->DtcmMultiErrorInfo  = base->D1TCM_ECC_MULTI_ERROR_INFO;
#endif /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/

        info->DtcmMultiErrorAddr = base->D1TCM_ECC_MULTI_ERROR_ADDR;
        info->DtcmMultiErrorData = base->D1TCM_ECC_MULTI_ERROR_DATA;
    }
}
#endif /* FSL_FEATURE_FLEXRAM_HAS_ECC */
