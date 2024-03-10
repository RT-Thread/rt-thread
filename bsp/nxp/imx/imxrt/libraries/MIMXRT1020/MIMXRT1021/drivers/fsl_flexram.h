/*
 * Copyright 2017-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_FLEXRAM_H_
#define _FSL_FLEXRAM_H_

#include "fsl_common.h"
#include "fsl_flexram_allocate.h"

/*!
 * @addtogroup flexram
 * @{
 */

/******************************************************************************
 * Definitions.
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief Driver version 2.1.0. */
#define FSL_FLEXRAM_DRIVER_VERSION (MAKE_VERSION(2U, 1U, 0U))
/*@}*/

/*! @brief Get ECC error detailed information. */
#ifndef FLEXRAM_ECC_ERROR_DETAILED_INFO
#define FLEXRAM_ECC_ERROR_DETAILED_INFO \
    0U /* Define to zero means get raw ECC error information, which needs parse it by user. */
#endif

/*! @brief Flexram write/read selection. */
enum
{
    kFLEXRAM_Read  = 0U, /*!< read */
    kFLEXRAM_Write = 1U, /*!< write */
};

/*! @brief Interrupt status flag mask */
enum
{
    kFLEXRAM_OCRAMAccessError = FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_MASK, /*!< OCRAM accesses unallocated address */
    kFLEXRAM_DTCMAccessError  = FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_MASK,  /*!< DTCM accesses unallocated address */
    kFLEXRAM_ITCMAccessError  = FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_MASK,  /*!< ITCM accesses unallocated address */

#if defined(FSL_FEATURE_FLEXRAM_HAS_MAGIC_ADDR) && FSL_FEATURE_FLEXRAM_HAS_MAGIC_ADDR
    kFLEXRAM_OCRAMMagicAddrMatch = FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_MASK, /*!< OCRAM magic address match */
    kFLEXRAM_DTCMMagicAddrMatch  = FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_MASK,  /*!< DTCM magic address match */
    kFLEXRAM_ITCMMagicAddrMatch  = FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_MASK,  /*!< ITCM magic address match */

#if defined(FSL_FEATURE_FLEXRAM_HAS_ECC) && FSL_FEATURE_FLEXRAM_HAS_ECC
    kFLEXRAM_OCRAMECCMultiError  = FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT_MASK,
    kFLEXRAM_OCRAMECCSingleError = FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT_MASK,
    kFLEXRAM_ITCMECCMultiError   = FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT_MASK,
    kFLEXRAM_ITCMECCSingleError  = FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT_MASK,
    kFLEXRAM_D0TCMECCMultiError  = FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT_MASK,
    kFLEXRAM_D0TCMECCSingleError = FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT_MASK,
    kFLEXRAM_D1TCMECCMultiError  = FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT_MASK,
    kFLEXRAM_D1TCMECCSingleError = FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT_MASK,

    kFLEXRAM_InterruptStatusAll =
        FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_MASK | FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_MASK |
        FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_MASK | FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_MASK |
        FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_MASK | FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_MASK |
        FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT_MASK | FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT_MASK |
        FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT_MASK | FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT_MASK |
        FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT_MASK | FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT_MASK |
        FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT_MASK | FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT_MASK,
#else
    kFLEXRAM_InterruptStatusAll = FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_MASK | FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_MASK |
                                  FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_MASK | FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_MASK |
                                  FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_MASK | FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_MASK,
#endif /* FSL_FEATURE_FLEXRAM_HAS_ECC */

/*!< all the interrupt status mask */
#else
    kFLEXRAM_InterruptStatusAll = FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_MASK | FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_MASK |
                                  FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_MASK, /*!< all the interrupt status mask */
#endif /* FSL_FEATURE_FLEXRAM_HAS_MAGIC_ADDR */

};

/*! @brief FLEXRAM TCM access mode.
 * Fast access mode expected to be finished in 1-cycle;
 * Wait access mode expected to be finished in 2-cycle.
 * Wait access mode is a feature of the flexram and it should be used when
 * the CPU clock is too fast to finish TCM access in 1-cycle.
 * Normally, fast mode is the default mode, the efficiency of the TCM access will better.
 */
typedef enum _flexram_tcm_access_mode
{
    kFLEXRAM_TCMAccessFastMode = 0U, /*!< fast access mode */
    kFLEXRAM_TCMAccessWaitMode = 1U, /*!< wait access mode */
} flexram_tcm_access_mode_t;

/*! @brief FLEXRAM TCM support size */
enum
{
    kFLEXRAM_TCMSize32KB  = 32 * 1024U,  /*!< TCM total size be 32KB */
    kFLEXRAM_TCMSize64KB  = 64 * 1024U,  /*!< TCM total size be 64KB */
    kFLEXRAM_TCMSize128KB = 128 * 1024U, /*!< TCM total size be 128KB */
    kFLEXRAM_TCMSize256KB = 256 * 1024U, /*!< TCM total size be 256KB */
    kFLEXRAM_TCMSize512KB = 512 * 1024U, /*!< TCM total size be 512KB */
};

#if (defined(FSL_FEATURE_FLEXRAM_HAS_ECC) && FSL_FEATURE_FLEXRAM_HAS_ECC)
/*! @brief FLEXRAM ocram ecc single error information, including single error information, error address, error data */
typedef struct _flexram_ocram_ecc_single_error_info
{
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    uint8_t OcramSingleErrorECCCipher;   /*!< OCRAM corresponding ECC cipher of OCRAM single-bit ECC error. */
    uint8_t OcramSingleErrorECCSyndrome; /*!< OCRAM corresponding ECC syndrome of OCRAM single-bit ECC error,
                                              which can be used to locate the Error bit using a look-up table. */
#else
    uint32_t OcramSingleErrorInfo; /*!< Ocram single error information, user should parse it by themself. */
#endif                                /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    uint32_t OcramSingleErrorAddr;    /*!< Ocram single error address */
    uint32_t OcramSingleErrorDataLSB; /*!< Ocram single error data LSB */
    uint32_t OcramSingleErrorDataMSB; /*!< Ocram single error data MSB */
} flexram_ocram_ecc_single_error_info_t;

/*! @brief FLEXRAM ocram ecc multiple error information, including multiple error information, error address, error data
 */
typedef struct _flexram_ocram_ecc_multi_error_info
{
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    uint8_t OcramMultiErrorECCCipher; /*!< OCRAM corresponding ECC cipher of OCRAM multi-bit ECC error. */
#else
    uint32_t OcramMultiErrorInfo;  /*!< Ocram single error information, user should parse it by themself. */
#endif                               /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    uint32_t OcramMultiErrorAddr;    /*!< Ocram multiple error address */
    uint32_t OcramMultiErrorDataLSB; /*!< Ocram multiple error data LSB */
    uint32_t OcramMultiErrorDataMSB; /*!< Ocram multiple error data MSB */
} flexram_ocram_ecc_multi_error_info_t;

/*! @brief FLEXRAM itcm ecc single error information, including single error information, error address, error data */
typedef struct _flexram_itcm_ecc_single_error_info
{
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    uint8_t ItcmSingleErrorTCMWriteRead;  /*!< itcm single-bit ECC error corresponding tcm_wr value, which is to tell
                                               whether it is a write access(0x01) or a read access(0x00). */
    uint8_t ItcmSingleErrorTCMAccessSize; /*!< itcm single-bit ECC error corresponding tcm access size,
                                               which should be 3 (64bit). */
    uint8_t ItcmSingleErrorTCMMaster;     /*!< itcm single-bit ECC error corresponding tcm_master,
                                               which is to tell the requester of the current access. */
    uint8_t ItcmSingleErrorTCMPrivilege;  /*!< itcm single-bit ECC error corresponding tcm_priv,
                                               which is to tell the privilege level of access. */
    uint8_t ItcmSingleErrorBitPostion;    /*!< itcm single-bit ECC error corresponding bit postion. */
#else
    uint32_t ItcmSingleErrorInfo;  /*!< itcm single error information, user should parse it by themself. */
#endif                               /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    uint32_t ItcmSingleErrorAddr;    /*!< itcm single error address */
    uint32_t ItcmSingleErrorDataLSB; /*!< itcm single error data LSB */
    uint32_t ItcmSingleErrorDataMSB; /*!< itcm single error data MSB */
} flexram_itcm_ecc_single_error_info_t;

/*! @brief FLEXRAM itcm ecc multiple error information, including multiple error information, error address, error data
 */
typedef struct _flexram_itcm_ecc_multi_error_info
{
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    uint8_t ItcmMultiErrorTCMWriteRead;  /*!< itcm multiple-bit ECC error corresponding tcm_wr value, which is to tell
                                              whether it is a write access(0x01) or a read access(0x00). */
    uint8_t ItcmMultiErrorTCMAccessSize; /*!< itcm multiple-bit ECC error corresponding tcm access size,
                                              which should be 3 (64bit). */
    uint8_t ItcmMultiErrorTCMMaster;     /*!< itcm multiple-bit ECC error corresponding tcm_master,
                                              which is to tell the requester of the current access. */
    uint8_t ItcmMultiErrorTCMPrivilege;  /*!< itcm multiple-bit ECC error corresponding tcm_priv,
                                              which is to tell the privilege level of access. */
    uint8_t ItcmMultiErrorECCSyndrome;   /*!< itcm multiple-bit ECC error corresponding syndrome,
                                              which can not be used to locate the Error bit using a look-up table. */
#else
    uint32_t ItcmMultiErrorInfo;   /*!< itcm multiple error information, user should parse it by themself. */
#endif                              /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    uint32_t ItcmMultiErrorAddr;    /*!< itcm multiple error address */
    uint32_t ItcmMultiErrorDataLSB; /*!< itcm multiple error data LSB */
    uint32_t ItcmMultiErrorDataMSB; /*!< itcm multiple error data MSB */
} flexram_itcm_ecc_multi_error_info_t;

/*! @brief FLEXRAM dtcm ecc single error information, including single error information, error address, error data */
typedef struct _flexram_dtcm_ecc_single_error_info
{
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    uint8_t DtcmSingleErrorTCMWriteRead;  /*!< dtcm single-bit ECC error corresponding tcm_wr value, which is to tell
                                               whether it is a write access(0x01) or a read access(0x00). */
    uint8_t DtcmSingleErrorTCMAccessSize; /*!< dtcm single-bit ECC error corresponding tcm access size,
                                               which should be 2 (32bit). */
    uint8_t DtcmSingleErrorTCMMaster;     /*!< dtcm single-bit ECC error corresponding tcm_master,
                                               which is to tell the requester of the current access. */
    uint8_t DtcmSingleErrorTCMPrivilege;  /*!< dtcm single-bit ECC error corresponding tcm_priv,
                                               which is to tell the privilege level of access. */
    uint8_t DtcmSingleErrorBitPostion;    /*!< dtcm single-bit ECC error corresponding bit postion. */
#else
    uint32_t DtcmSingleErrorInfo;  /*!< dtcm single error information, user should parse it by themself. */
#endif                            /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    uint32_t DtcmSingleErrorAddr; /*!< dtcm single error address */
    uint32_t DtcmSingleErrorData; /*!< dtcm single error data */
} flexram_dtcm_ecc_single_error_info_t;

/*! @brief FLEXRAM dtcm ecc multiple error information, including multiple error information, error address, error data
 */
typedef struct _flexram_dtcm_ecc_multi_error_info
{
#if defined(FLEXRAM_ECC_ERROR_DETAILED_INFO) && FLEXRAM_ECC_ERROR_DETAILED_INFO
    uint8_t DtcmMultiErrorTCMWriteRead;  /*!< dtcm multiple-bit ECC error corresponding tcm_wr value, which is to tell
                                              whether it is a write access(0x01) or a read access(0x00). */
    uint8_t DtcmMultiErrorTCMAccessSize; /*!< dtcm multiple-bit ECC error corresponding tcm access size,
                                              which should be 3 (64bit). */
    uint8_t DtcmMultiErrorTCMMaster;     /*!< dtcm multiple-bit ECC error corresponding tcm_master,
                                              which is to tell the requester of the current access. */
    uint8_t DtcmMultiErrorTCMPrivilege;  /*!< dtcm multiple-bit ECC error corresponding tcm_priv,
                                              which is to tell the privilege level of access. */
    uint8_t DtcmMultiErrorECCSyndrome;   /*!< dtcm multiple-bit ECC error corresponding syndrome,
                                              which can not be used to locate the Error bit using a look-up table. */
#else
    uint32_t DtcmMultiErrorInfo;   /*!< dtcm multiple error information, user should parse it by themself. */
#endif                           /*FLEXRAM_ECC_ERROR_DETAILED_INFO*/
    uint32_t DtcmMultiErrorAddr; /*!< dtcm multiple error address */
    uint32_t DtcmMultiErrorData; /*!< dtcm multiple error data */
} flexram_dtcm_ecc_multi_error_info_t;

#endif /* FSL_FEATURE_FLEXRAM_HAS_ECC */

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
 * @brief FLEXRAM module initialization function.
 *
 * @param base FLEXRAM base address.
 */
void FLEXRAM_Init(FLEXRAM_Type *base);

/*!
 * @brief De-initializes the FLEXRAM.
 *
 */
void FLEXRAM_Deinit(FLEXRAM_Type *base);

/* @} */

/*!
 * @name Status
 * @{
 */
/*!
 * @brief FLEXRAM module gets interrupt status.
 *
 * @param base FLEXRAM base address.
 */
static inline uint32_t FLEXRAM_GetInterruptStatus(FLEXRAM_Type *base)
{
    return base->INT_STATUS & (uint32_t)kFLEXRAM_InterruptStatusAll;
}

/*!
 * @brief FLEXRAM module clears interrupt status.
 *
 * @param base FLEXRAM base address.
 * @param status Status to be cleared.
 */
static inline void FLEXRAM_ClearInterruptStatus(FLEXRAM_Type *base, uint32_t status)
{
    base->INT_STATUS |= status;
}

/*!
 * @brief FLEXRAM module enables interrupt status.
 *
 * @param base FLEXRAM base address.
 * @param status Status to be enabled.
 */
static inline void FLEXRAM_EnableInterruptStatus(FLEXRAM_Type *base, uint32_t status)
{
    base->INT_STAT_EN |= status;
}

/*!
 * @brief FLEXRAM module disable interrupt status.
 *
 * @param base FLEXRAM base address.
 * @param status Status to be disabled.
 */
static inline void FLEXRAM_DisableInterruptStatus(FLEXRAM_Type *base, uint32_t status)
{
    base->INT_STAT_EN &= ~status;
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief FLEXRAM module enables interrupt.
 *
 * @param base FLEXRAM base address.
 * @param status Status interrupt to be enabled.
 */
static inline void FLEXRAM_EnableInterruptSignal(FLEXRAM_Type *base, uint32_t status)
{
    base->INT_SIG_EN |= status;
}

/*!
 * @brief FLEXRAM module disables interrupt.
 *
 * @param base FLEXRAM base address.
 * @param status Status interrupt to be disabled.
 */
static inline void FLEXRAM_DisableInterruptSignal(FLEXRAM_Type *base, uint32_t status)
{
    base->INT_SIG_EN &= ~status;
}
/* @} */

/*!
 * @brief FLEXRAM module sets TCM read access mode
 *
 * @param base  FLEXRAM base address.
 * @param mode  Access mode.
 */
static inline void FLEXRAM_SetTCMReadAccessMode(FLEXRAM_Type *base, flexram_tcm_access_mode_t mode)
{
    base->TCM_CTRL &= ~FLEXRAM_TCM_CTRL_TCM_RWAIT_EN_MASK;
    base->TCM_CTRL |= (uint32_t)mode;
}

/*!
 * @brief FLEXRAM module set TCM write access mode
 *
 * @param base  FLEXRAM base address.
 * @param mode  Access mode.
 */
static inline void FLEXRAM_SetTCMWriteAccessMode(FLEXRAM_Type *base, flexram_tcm_access_mode_t mode)
{
    base->TCM_CTRL &= ~FLEXRAM_TCM_CTRL_TCM_WWAIT_EN_MASK;
    base->TCM_CTRL |= (uint32_t)mode;
}

/*!
 * @brief FLEXRAM module force ram clock on
 *
 * @param base  FLEXRAM base address.
 * @param enable Enable or disable clock force on.
 */
static inline void FLEXRAM_EnableForceRamClockOn(FLEXRAM_Type *base, bool enable)
{
    if (enable)
    {
        base->TCM_CTRL |= FLEXRAM_TCM_CTRL_FORCE_CLK_ON_MASK;
    }
    else
    {
        base->TCM_CTRL &= ~FLEXRAM_TCM_CTRL_FORCE_CLK_ON_MASK;
    }
}

#if defined(FSL_FEATURE_FLEXRAM_HAS_MAGIC_ADDR) && FSL_FEATURE_FLEXRAM_HAS_MAGIC_ADDR
/*!
 * @brief FLEXRAM OCRAM magic addr configuration.
 * When read/write access hit magic address, it will generate interrupt.
 * @param base  FLEXRAM base address.
 * @param magicAddr Magic address, the actual address bits [18:3] is corresponding to the register field [16:1].
 * @param rwSel Read/write selection. 0 for read access while 1 for write access.
 */
static inline void FLEXRAM_SetOCRAMMagicAddr(FLEXRAM_Type *base, uint16_t magicAddr, uint32_t rwSel)
{
    base->OCRAM_MAGIC_ADDR = FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_WR_RD_SEL(rwSel) |
                             FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_MAGIC_ADDR((uint32_t)magicAddr >> 3);
}

/*!
 * @brief FLEXRAM DTCM magic addr configuration.
 * When read/write access hits magic address, it will generate interrupt.
 * @param base  FLEXRAM base address.
 * @param magicAddr Magic address, the actual address bits [18:3] is corresponding to the register field [16:1].
 * @param rwSel Read/write selection. 0 for read access while 1 write access.
 */
static inline void FLEXRAM_SetDTCMMagicAddr(FLEXRAM_Type *base, uint16_t magicAddr, uint32_t rwSel)
{
    base->DTCM_MAGIC_ADDR = FLEXRAM_DTCM_MAGIC_ADDR_DTCM_WR_RD_SEL(rwSel) |
                            FLEXRAM_DTCM_MAGIC_ADDR_DTCM_MAGIC_ADDR((uint32_t)magicAddr >> 3);
}

/*!
 * @brief FLEXRAM ITCM magic addr configuration.
 * When read/write access hits magic address, it will generate interrupt.
 * @param base  FLEXRAM base address.
 * @param magicAddr Magic address, the actual address bits [18:3] is corresponding to the register field [16:1].
 * @param rwSel Read/write selection. 0 for read access while 1 for write access.
 */
static inline void FLEXRAM_SetITCMMagicAddr(FLEXRAM_Type *base, uint16_t magicAddr, uint32_t rwSel)
{
    base->ITCM_MAGIC_ADDR = FLEXRAM_ITCM_MAGIC_ADDR_ITCM_WR_RD_SEL(rwSel) |
                            FLEXRAM_ITCM_MAGIC_ADDR_ITCM_MAGIC_ADDR((uint32_t)magicAddr >> 3);
}
#endif /* FSL_FEATURE_FLEXRAM_HAS_MAGIC_ADDR */

#if (defined(FSL_FEATURE_FLEXRAM_HAS_ECC) && FSL_FEATURE_FLEXRAM_HAS_ECC)
/*!
 * @brief FLEXRAM get ocram ecc single error information.
 * @param base  FLEXRAM base address.
 * @param OcramECCEnable ocram ecc enablement.
 * @param TcmECCEnable tcm(itcm/d0tcm/d1tcm) ecc enablement.
 */
void FLEXRAM_EnableECC(FLEXRAM_Type *base, bool OcramECCEnable, bool TcmECCEnable);

/*!
 * @brief FLEXRAM get ocram ecc single error information.
 * @param base  FLEXRAM base address.
 * @param info ecc error information.
 */
void FLEXRAM_GetOcramSingleErroInfo(FLEXRAM_Type *base, flexram_ocram_ecc_single_error_info_t *info);

/*!
 * @brief FLEXRAM get ocram ecc multiple error information.
 * @param base  FLEXRAM base address.
 * @param info ecc error information.
 */
void FLEXRAM_GetOcramMultiErroInfo(FLEXRAM_Type *base, flexram_ocram_ecc_multi_error_info_t *info);

/*!
 * @brief FLEXRAM get itcm ecc single error information.
 * @param base  FLEXRAM base address.
 * @param info ecc error information.
 */
void FLEXRAM_GetItcmSingleErroInfo(FLEXRAM_Type *base, flexram_itcm_ecc_single_error_info_t *info);

/*!
 * @brief FLEXRAM get itcm ecc multiple error information.
 * @param base  FLEXRAM base address.
 * @param info ecc error information.
 */
void FLEXRAM_GetItcmMultiErroInfo(FLEXRAM_Type *base, flexram_itcm_ecc_multi_error_info_t *info);

/*!
 * @brief FLEXRAM get d0tcm ecc single error information.
 * @param base  FLEXRAM base address.
 * @param info ecc error information.
 * @param bank DTCM bank, 0 is D0TCM, 1 is D1TCM.
 */
void FLEXRAM_GetDtcmSingleErroInfo(FLEXRAM_Type *base, flexram_dtcm_ecc_single_error_info_t *info, uint8_t bank);

/*!
 * @brief FLEXRAM get d0tcm ecc multiple error information.
 * @param base  FLEXRAM base address.
 * @param info ecc error information.
 * @param bank DTCM bank, 0 is D0TCM, 1 is D1TCM.
 */
void FLEXRAM_GetDtcmMultiErroInfo(FLEXRAM_Type *base, flexram_dtcm_ecc_multi_error_info_t *info, uint8_t bank);

#endif /* FSL_FEATURE_FLEXRAM_HAS_ECC */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
