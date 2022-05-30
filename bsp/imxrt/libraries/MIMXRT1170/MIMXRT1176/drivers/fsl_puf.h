/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PUF_H_
#define _PUF_H_

#include <stddef.h>
#include <stdint.h>

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*!
 * @addtogroup puf_driver
 * @{
 */
/*! @name Driver version */
/*@{*/
/*! @brief PUF driver version. Version 2.1.6.
 *
 * Current version: 2.1.6
 *
 * Change log:
 * - 2.0.0
 *   - Initial version.
 * - 2.0.1
 *   - Fixed puf_wait_usec function optimization issue.
 * - 2.0.2
 *   - Add PUF configuration structure and support for PUF SRAM controller.
 *     Remove magic constants.
 * - 2.0.3
 *   - Fix MISRA C-2012 issue.
 * - 2.1.0
 *   - Align driver with PUF SRAM controller registers on LPCXpresso55s16.
 *   - Update initizalition logic .
 * - 2.1.1
 *   - Fix ARMGCC build warning .
 * - 2.1.2
 *   - Update: Add automatic big to little endian swap for user
 *     (pre-shared) keys destinated to secret hardware bus (PUF key index 0).
 * - 2.1.3
 *   - Fix MISRA C-2012 issue.
 * - 2.1.4
 *   - Replace register uint32_t ticksCount with volatile uint32_t ticksCount in puf_wait_usec() to prevent optimization
 * out delay loop.
 * - 2.1.5
 *   - Use common SDK delay in puf_wait_usec()
 * - 2.1.6
 *   - Changed wait time in PUF_Init(), when initialization fails it will try PUF_Powercycle() with shorter time. If
 * this shorter time will also fail, initialization will be tried with worst case time as before.
 */
#define FSL_PUF_DRIVER_VERSION (MAKE_VERSION(2, 1, 6))
/*@}*/

typedef enum _puf_key_index_register
{
    kPUF_KeyIndex_00 = 0x00U,
    kPUF_KeyIndex_01 = 0x01U,
    kPUF_KeyIndex_02 = 0x02U,
    kPUF_KeyIndex_03 = 0x03U,
    kPUF_KeyIndex_04 = 0x04U,
    kPUF_KeyIndex_05 = 0x05U,
    kPUF_KeyIndex_06 = 0x06U,
    kPUF_KeyIndex_07 = 0x07U,
    kPUF_KeyIndex_08 = 0x08U,
    kPUF_KeyIndex_09 = 0x09U,
    kPUF_KeyIndex_10 = 0x0AU,
    kPUF_KeyIndex_11 = 0x0BU,
    kPUF_KeyIndex_12 = 0x0CU,
    kPUF_KeyIndex_13 = 0x0DU,
    kPUF_KeyIndex_14 = 0x0EU,
    kPUF_KeyIndex_15 = 0x0FU,
} puf_key_index_register_t;

typedef enum _puf_min_max
{
    kPUF_KeySizeMin  = 8u,
    kPUF_KeySizeMax  = 512u,
    kPUF_KeyIndexMax = kPUF_KeyIndex_15,
} puf_min_max_t;

/*! @brief PUF key slot. */
typedef enum _puf_key_slot
{
    kPUF_KeySlot0 = 0U, /*!< PUF key slot 0 */
    kPUF_KeySlot1 = 1U, /*!< PUF key slot 1 */
#if defined(PUF_KEYMASK_COUNT) && (PUF_KEYMASK_COUNT > 2)
    kPUF_KeySlot2 = 2U, /*!< PUF key slot 2 */
    kPUF_KeySlot3 = 3U, /*!< PUF key slot 3 */
#endif
} puf_key_slot_t;

typedef struct
{
    uint32_t dischargeTimeMsec;
    uint32_t coreClockFrequencyHz;
#if defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
    /* LPCXpresso55s16 */
    PUF_SRAM_CTRL_Type *puf_sram_base;
    uint8_t CKGATING;
#endif /* FSL_FEATURE_PUF_HAS_SRAM_CTRL */
} puf_config_t;
/*! @brief Get Key Code size in bytes from key size in bytes at compile time. */
#define PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(x)    ((160u + (((((x) << 3) + 255u) >> 8) << 8)) >> 3)
#define PUF_MIN_KEY_CODE_SIZE                    PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(8UL)
#define PUF_ACTIVATION_CODE_SIZE                 1192U
#define KEYSTORE_PUF_DISCHARGE_TIME_FIRST_TRY_MS 50
#define KEYSTORE_PUF_DISCHARGE_TIME_MAX_MS       400

/*! PUF status return codes. */
enum
{
    kStatus_EnrollNotAllowed = MAKE_STATUS(kStatusGroup_PUF, 1),
    kStatus_StartNotAllowed  = MAKE_STATUS(kStatusGroup_PUF, 2)
};

/*! @} */
/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Sets the default configuration of PUF
 *
 * This function initialize PUF config structure to default values.
 *
 * @param conf PUF configuration structure
 */
void PUF_GetDefaultConfig(puf_config_t *conf);

/*!
 * @brief Initialize PUF
 *
 * This function enables power to PUF block and waits until the block initializes.
 *
 * @param base PUF peripheral base address
 * @param conf PUF configuration structure
 * @return Status of the init operation
 */
status_t PUF_Init(PUF_Type *base, puf_config_t *conf);

/*!
 * @brief Denitialize PUF
 *
 * This function disables power to PUF SRAM and peripheral clock.
 *
 * @param base PUF peripheral base address
 * @param conf PUF configuration structure
 */
void PUF_Deinit(PUF_Type *base, puf_config_t *conf);

/*!
 * @brief Enroll PUF
 *
 * This function derives a digital fingerprint, generates the corresponding Activation Code (AC)
 * and returns it to be stored in an NVM or a file. This step needs to be
 * performed only once for each device. This function may be permanently disallowed by a fuse.
 *
 * @param base PUF peripheral base address
 * @param[out] activationCode Word aligned address of the resulting activation code.
 * @param activationCodeSize Size of the activationCode buffer in bytes. Shall be 1192 bytes.
 * @return Status of enroll operation.
 */
status_t PUF_Enroll(PUF_Type *base, uint8_t *activationCode, size_t activationCodeSize);

/*!
 * @brief Start PUF
 *
 * The Activation Code generated during the Enroll operation is used to
 * reconstruct the digital fingerprint. This needs to be done after every power-up
 * and reset.
 *
 * @param base PUF peripheral base address
 * @param activationCode Word aligned address of the input activation code.
 * @param activationCodeSize Size of the activationCode buffer in bytes. Shall be 1192 bytes.
 * @return Status of start operation.
 */
status_t PUF_Start(PUF_Type *base, const uint8_t *activationCode, size_t activationCodeSize);

/*!
 * @brief Set intrinsic key
 *
 * The digital fingerprint generated during the Enroll/Start
 * operations is used to generate a Key Code (KC) that defines a unique intrinsic
 * key. This KC is returned to be stored in an NVM or a file. This operation
 * needs to be done only once for each intrinsic key.
 * Each time a Set Intrinsic Key operation is executed a new unique key is
 * generated.
 *
 * @param base PUF peripheral base address
 * @param keyIndex PUF key index register
 * @param keySize Size of the intrinsic key to generate in bytes.
 * @param[out] keyCode Word aligned address of the resulting key code.
 * @param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize).
 * @return Status of set intrinsic key operation.
 */
status_t PUF_SetIntrinsicKey(
    PUF_Type *base, puf_key_index_register_t keyIndex, size_t keySize, uint8_t *keyCode, size_t keyCodeSize);

/*!
 * @brief Set user key
 *
 * The digital fingerprint generated during the Enroll/Start
 * operations and a user key (UK) provided as input are used to
 * generate a Key Code (KC). This KC is sent returned to be stored
 * in an NVM or a file. This operation needs to be done only once for each user key.
 *
 * @param base PUF peripheral base address
 * @param keyIndex PUF key index register
 * @param userKey Word aligned address of input user key.
 * @param userKeySize Size of the input user key in bytes.
 * @param[out] keyCode Word aligned address of the resulting key code.
 * @param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(userKeySize).
 * @return Status of set user key operation.
 */
status_t PUF_SetUserKey(PUF_Type *base,
                        puf_key_index_register_t keyIndex,
                        const uint8_t *userKey,
                        size_t userKeySize,
                        uint8_t *keyCode,
                        size_t keyCodeSize);

/*!
 * @brief Reconstruct key from a key code
 *
 * The digital fingerprint generated during the Start operation and the KC
 * generated during a Set Key operation (Set intrinsic key or Set user key) are used to retrieve a stored key. This
 * operation needs to be done every time a key is needed.
 * This function accepts only Key Codes created for PUF index registers kPUF_KeyIndex_01 to kPUF_KeyIndex_15.
 *
 * @param base PUF peripheral base address
 * @param keyCode Word aligned address of the input key code.
 * @param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize).
 * @param[out] key Word aligned address of output key.
 * @param keySize Size of the output key in bytes.
 * @return Status of get key operation.
 */
status_t PUF_GetKey(PUF_Type *base, const uint8_t *keyCode, size_t keyCodeSize, uint8_t *key, size_t keySize);

/*!
 * @brief Reconstruct hw bus key from a key code
 *
 * The digital fingerprint generated during the Start operation and the KC
 * generated during a Set Key operation (Set intrinsic key or Set user key) are used to retrieve a stored key. This
 * operation needs to be done every time a key is needed.
 * This function accepts only Key Codes created for PUF index register kPUF_KeyIndex_00.
 * Such a key is output directly to a dedicated hardware bus. The reconstructed key is not exposed to system memory.
 *
 * @param base PUF peripheral base address
 * @param keyCode Word aligned address of the input key code.
 * @param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize).
 * @param keySlot key slot to output on hw bus. Parameter is ignored on devices with less than two key slots.
 * @param keyMask key masking value. Shall be random for each POR/reset. Value does not have to be cryptographicaly
 * secure.
 * @return Status of get key operation.
 */
status_t PUF_GetHwKey(
    PUF_Type *base, const uint8_t *keyCode, size_t keyCodeSize, puf_key_slot_t keySlot, uint32_t keyMask);

/*!
 * @brief Zeroize PUF
 *
 * This function clears all PUF internal logic and puts the PUF to error state.
 *
 * @param base PUF peripheral base address
 * @return Status of the zeroize operation.
 */
status_t PUF_Zeroize(PUF_Type *base);

/*!
 * @brief Checks if Get Key operation is allowed.
 *
 * This function returns true if get key operation is allowed.
 *
 * @param base PUF peripheral base address
 * @return true if get key operation is allowed
 */
bool PUF_IsGetKeyAllowed(PUF_Type *base);

#if defined(PUF_CFG_BLOCKKEYOUTPUT_MASK) && PUF_CFG_BLOCKKEYOUTPUT_MASK
static inline void PUF_BlockSetKey(PUF_Type *base)
{
    base->CFG |= PUF_CFG_BLOCKKEYOUTPUT_MASK; /* block set key */
}
#endif /* PUF_CFG_BLOCKKEYOUTPUT_MASK */

#if defined(PUF_CFG_PUF_BLOCK_SET_KEY_MASK) && PUF_CFG_PUF_BLOCK_SET_KEY_MASK
static inline void PUF_BlockSetKey(PUF_Type *base)
{
    base->CFG |= PUF_CFG_PUF_BLOCK_SET_KEY_MASK; /* block set key */
}
#endif /* PUF_CFG_PUF_BLOCK_SET_KEY_MASK */

#if defined(PUF_CFG_BLOCKENROLL_SETKEY_MASK) && PUF_CFG_BLOCKENROLL_SETKEY_MASK
static inline void PUF_BlockEnroll(PUF_Type *base)
{
    base->CFG |= PUF_CFG_BLOCKENROLL_SETKEY_MASK; /* block enroll */
}
#endif /* PUF_CFG_BLOCKENROLL_SETKEY_MASK */

#if defined(PUF_CFG_PUF_BLOCK_ENROLL_MASK) && PUF_CFG_PUF_BLOCK_ENROLL_MASK
static inline void PUF_BlockEnroll(PUF_Type *base)
{
    base->CFG |= PUF_CFG_PUF_BLOCK_ENROLL_MASK; /* block enroll */
}
#endif /* PUF_CFG_PUF_BLOCK_ENROLL_MASK */

/*!
 * @brief Powercycle PUF
 *
 * This function make powercycle.
 *
 * @param base PUF peripheral base address
 * @param conf PUF configuration structure
 * @return Status of the powercycle operation.
 */
status_t PUF_PowerCycle(PUF_Type *base, puf_config_t *conf);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _PUF_H_ */
