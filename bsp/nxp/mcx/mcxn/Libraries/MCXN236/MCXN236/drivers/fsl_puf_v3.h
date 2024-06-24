/*
 * Copyright 2017-2018,2023 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PUF_V3_H_
#define _PUF_V3_H_

#include <stddef.h>
#include <stdint.h>

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @addtogroup puf_v3_driver
 * @{
 */
/*! @name Driver version */
/*@{*/
/*! @brief PUFv3 driver version. Version 2.0.2.
 *
 * Current version: 2.0.2
 *
 * Change log:
 * - 2.0.2
 *   - Fix MISRA issue in driver.
 * - 2.0.1
 *   - Fix PUF initialization issue and update driver to reflect SoC header changes.
 * - 2.0.0
 *   - Initial version.
 */
#define FSL_PUF_V3_DRIVER_VERSION (MAKE_VERSION(2, 0, 2))
/*@}*/

#define kPUF_EndianLittle (0x0u)
#define kPUF_EndianBig    (0x1u)
typedef uint32_t puf_endianness_t;

#define kPUF_KeyDestRegister (0x1u)
#define kPUF_KeyDestKeyBus   (0x2u)
#define kPUF_KeyDestInvalid  (0x3u)
typedef uint32_t puf_key_dest_t;

#define kPUF_KeyAllowRegister (0x1u)
#define kPUF_KeyAllowKeyBus   (0x2u)
#define kPUF_KeyAllowAll      (0x3u)
typedef uint32_t puf_key_scope_t;

#define kPUF_ResultOK                  (0x0u)
#define kPUF_AcNotForThisProductPhase1 (0xf0u)
#define kPUF_AcNotForThisProductPhase2 (0xf1u)
#define kPUF_AcCorruptedPhase1         (0xf2u)
#define kPUF_AcCorruptedPhase2         (0xf3u)
#define kPUF_AcAuthFailedPhase1        (0xf4u)
#define kPUF_AcAuthFailedPhase2        (0xf5u)
#define kPUF_QualityVerificationFail   (0xf6u)
#define kPUF_ContextIncorrect          (0xf7u)
#define kPUF_DestinationNotAllowed     (0xf8u)
#define kPUF_Failure                   (0xFFu)
typedef uint32_t puf_result_code_t;

#define kPUF_NonsecureUser      (0xCu) /* b1100 */
#define kPUF_NonsecurePrivilege (0x9u) /* b1001 */
#define kPUF_SecureUser         (0x6u) /* b0110 */
#define kPUF_SecurePrivilege    (0x3u) /* b0011 */
typedef uint32_t puf_sec_level_t;

typedef struct
{
    puf_endianness_t dataEndianness;
    uint8_t CKGATING;
} puf_config_t;

typedef struct
{
    puf_key_scope_t keyScopeStarted;
    puf_key_scope_t keyScopeEnrolled;
    uint32_t userCtx0;
    uint32_t userCtx1;
} puf_key_ctx_t;

#define PUF_ACTIVATION_CODE_SIZE              (size_t)(FSL_FEATURE_PUF_ACTIVATION_CODE_SIZE)
#define PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(x) ((0x34u + (x)) + 0x10u * ((x) / 0x32u))
#define SEC_LOCK_PATTERN                      0xAC50u

enum
{
    kStatus_PUF_OperationNotAllowed       = MAKE_STATUS(kStatusGroup_PUF, 0xA5),
    kStatus_PUF_AcNotForThisProductPhase1 = MAKE_STATUS(kStatusGroup_PUF, kPUF_AcNotForThisProductPhase1),
    kStatus_PUF_AcNotForThisProductPhase2 = MAKE_STATUS(kStatusGroup_PUF, kPUF_AcNotForThisProductPhase2),
    kStatus_PUF_AcCorruptedPhase1         = MAKE_STATUS(kStatusGroup_PUF, kPUF_AcCorruptedPhase1),
    kStatus_PUF_AcCorruptedPhase2         = MAKE_STATUS(kStatusGroup_PUF, kPUF_AcCorruptedPhase2),
    kStatus_PUF_AcAuthFailedPhase1        = MAKE_STATUS(kStatusGroup_PUF, kPUF_AcAuthFailedPhase1),
    kStatus_PUF_NBOOT_AcAuthFailedPhase2  = MAKE_STATUS(kStatusGroup_PUF, kPUF_AcAuthFailedPhase2),
    kStatus_PUF_QualityVerificationFail   = MAKE_STATUS(kStatusGroup_PUF, kPUF_QualityVerificationFail),
    kStatus_PUF_ContextIncorrect          = MAKE_STATUS(kStatusGroup_PUF, kPUF_ContextIncorrect),
    kStatus_PUF_DestinationNotAllowed     = MAKE_STATUS(kStatusGroup_PUF, kPUF_DestinationNotAllowed),
    kStatus_PUF_Failure                   = MAKE_STATUS(kStatusGroup_PUF, kPUF_Failure),
};

/*******************************************************************************
 * API
 *******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * brief Sets the default configuration of PUF
 *
 * This function initialize PUF config structure to default values.
 *
 * @param conf PUF configuration structure
 */
void PUF_GetDefaultConfig(puf_config_t *conf);

/*!
 * brief Initialize PUF
 *
 * This function enables power to PUF block and waits until the block initializes.
 *
 * @param conf PUF configuration structure
 * @return Status of the init operation
 */
status_t PUF_Init(PUF_Type *base, puf_config_t *conf);

/*!
 * brief Denitialize PUF
 *
 * This function disables power to PUF SRAM and peripheral clock.
 *
 * @param base PUF peripheral base address
 * @param conf PUF configuration structure
 */
void PUF_Deinit(PUF_Type *base, puf_config_t *conf);

/*!
 * brief Enroll PUF
 *
 * This function derives a digital fingerprint, generates the corresponding Activation Code (AC)
 * and returns it to be stored in an NVM or a file. This step needs to be
 * performed only once for each device. This function may be permanently disallowed by a fuse.
 *
 * @param base PUF peripheral base address
 * @param[out] activationCode Word aligned address of the resulting activation code.
 * @param activationCodeSize Size of the activationCode buffer in bytes. Shall be FSL_FEATURE_PUF_ACTIVATION_CODE_SIZE bytes.
 * @param score Value of the PUF Score that was obtained during the enroll operation.
 * @return Status of enroll operation.
 */
status_t PUF_Enroll(PUF_Type *base, uint8_t *activationCode, size_t activationCodeSize, uint8_t *score);

/*!
 * brief Start PUF
 *
 * The Activation Code generated during the Enroll operation is used to
 * reconstruct the digital fingerprint. This needs to be done after every power-up
 * and reset.
 *
 * @param base PUF peripheral base address
 * @param[in] activationCode Word aligned address of the input activation code.
 * @param activationCodeSize Size of the activationCode buffer in bytes. Shall be FSL_FEATURE_PUF_ACTIVATION_CODE_SIZE bytes.
 * @param score Value of the PUF Score that was obtained during the start operation.
 * return Status of start operation.
 */
status_t PUF_Start(PUF_Type *base, const uint8_t *activationCode, size_t activationCodeSize, uint8_t *score);

/*!
 * brief Stop PUF
 *
 * The Stop operation removes all key material from PUF flipflops and PUF SRAM, and sets
 * PUF to the Stopped state.
 *
 * @param base PUF peripheral base address
 * @return Status of stop operation.
 */
status_t PUF_Stop(PUF_Type *base);

/*!
 * brief PUF Get Key
 *
 * The Get Key operation derives a key from the intrinsic PUF key and externally provided context.
 *
 * @param base PUF peripheral base address
 * @param keyCtx PUF key context struct
 * @param keyDest output destination of the derived PUF key
 * @param[out] key Word aligned address of output key (only used when kPUF_KeyDestRegister).
 * @param keySize Size of the derived key in bytes.
 * @return Status of get key operation.
 */
status_t PUF_GetKey(PUF_Type *base, puf_key_ctx_t *keyCtx, puf_key_dest_t keyDest, uint8_t *key, size_t keySize);

/*!
 * brief PUF Wrap generated random
 *
 * The Wrap Generated Random operation wraps a random key into a Key Code (KC).
 *
 * @param base PUF peripheral base address
 * @param keyCtx PUF key context struct
 * @param keySize Size of the key to be generated in bytes.
 * @param[out] keyCode Word aligned address of the resulting key code.
 * @param keyCodeSize Size of the output keycode in bytes.
 * @return Status of wrap generated random operation.
 */
status_t PUF_WrapGeneratedRandom(
    PUF_Type *base, puf_key_ctx_t *keyCtx, size_t keySize, uint8_t *keyCode, size_t keyCodeSize);

/*!
 * brief PUF Wrap user key
 *
 * The Wrap operation wraps a user defined key into a Key Code (KC).
 *
 * @param base PUF peripheral base address
 * @param keyCtx PUF key context struct.
 * @param userKey Word aligned address of input user key.
 * @param userKeySize Size of the key to be wrapped in bytes.
 * @param[out] keyCode Word aligned address of the resulting key code.
 * @param keyCodeSize Size of the output keycode in bytes.
 * @return Status of wrap operation.
 */
status_t PUF_Wrap(
    PUF_Type *base, puf_key_ctx_t *keyCtx, uint8_t *userKey, size_t userKeySize, uint8_t *keyCode, size_t keyCodeSize);

/*!
 * brief PUF Unwrap user key
 *
 * The unwrap operation unwraps the key from a previously created Key Code (KC)
 *
 * @param base PUF peripheral base address
 * @param keyDest output destination of the unwraped PUF key
 * @param[in] keyCode Word aligned address of the input key code.
 * @param keyCodeSize Size of the input keycode in bytes.
 * @param key Word aligned address of output key (only used when kPUF_KeyDestRegister).
 * @param keySize Size of the key to be generated in bytes.
 * @return Status of unwrap operation.
 */
status_t PUF_Unwrap(
    PUF_Type *base, puf_key_dest_t keyDest, uint8_t *keyCode, size_t keyCodeSize, uint8_t *key, size_t keySize);

/*!
 * brief Generate Random
 *
 * The Generate Random operation outputs the requested amount of random data as specified in a
 * provided context.
 *
 * @param base PUF peripheral base address
 * @param size Size of random data to be genarated in bytes.
 * @return Status of generate random operation.
 */
status_t PUF_GenerateRandom(PUF_Type *base, uint8_t *data, size_t size);

/*!
 * brief Zeroize PUF
 *
 * This function clears all PUF internal logic and puts the PUF to zeroized state.
 *
 * @param base PUF peripheral base address
 * @return Status of the zeroize operation.
 */
status_t PUF_Zeroize(PUF_Type *base);

/*!
 * brief Test PUF
 *
 * With the Test PUF operation, diagnostics about the PUF quality is collected and presented in a PUF
 * score.
 *
 * @param base PUF peripheral base address
 * @param score Value of the PUF Score that was obtained during the enroll operation.
 * @return Status of the test operation.
 */
status_t PUF_Test(PUF_Type *base, uint8_t *score);

/*!
 * @brief Blocks specified PUF commands
 *
 * This function blocks PUF commands specified by mask parameter.
 *
 * @param base PUF peripheral base address
 * @param mask Mask of parameters which should be blocked until power-cycle.
 * @return Status of the test operation.
 */
static inline void PUF_BlockCommand(PUF_Type *base, uint32_t mask)
{
    base->CONFIG |= mask;
}

/*!
 * brief Set lock of PUF operation
 *
 * Lock the security level of PUF block until key generate, wrap or unwrap operation is completed.
 * Note: Only security level defined in SEC_LOCK register can use PUFv3 or change its security level.
 *       Default setting after leaving ROM is Secure-Privilege
 *
 * @param base PUF peripheral base address
 * @param securityLevel Security level of PUF block.
 * @return Status of the test operation.
 */
status_t PUF_SetLock(PUF_Type *base, puf_sec_level_t securityLevel);

/*!
 * brief Set App Context mask
 *
 * This function sets Application defined context mask used in conjunction with key user context 2.
 * Whenever bit in this register is 1, corresponding bit in user context 2 provided
 * during key code creation should be zero only.
 *
 * This register is only modifiable by task running at secure-privilege level.
 *
 * @param base PUF peripheral base address
 * @param appCtxMask Value of the Application defined context mask.
 * @return Status of the test operation.
 */
status_t PUF_SetCtxMask(PUF_Type *base, uint32_t appCtxMask);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _PUF_H_ */
