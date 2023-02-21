/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_puf_v3.h"
#include "fsl_clock.h"
#include "fsl_reset.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.puf_v3"
#endif

#define kPUF_OperationInProgress (0x0u)
#define kPUF_Enroll              (0x1u)
#define kPUF_Start               (0x2u)
#define kPUF_Stop                (0x5u)
#define kPUF_GetKey              (0x6u)
#define kPUF_Unwrap              (0x7u)
#define kPUF_WrapGeneratedRandom (0x8u)
#define kPUF_Wrap                (0x9u)
#define kPUF_GenerateRandom      (0xfu)
#define kPUF_Test                (0x1fu)
#define kPUF_Init                (0x20u)
#define kPUF_Zeroize             (0x2fu)
typedef uint32_t puf_last_operation_t;

#define PUF_KEY_OPERATION_CONTEXT_TYPE (0x10 << 16)
#define PUF_CONTEXT_GENERIC_KEY_TYPE   (0x0u)
#define PUF_CONTEXT_KEY_LEN_MASK       (0x1fffu)

/*******************************************************************************
 * Code
 ******************************************************************************/

static status_t puf_waitForInit(PUF_Type *base)
{
    status_t status = kStatus_Fail;

    /* wait until status register reads non-zero. All zero is not valid. It should be BUSY or OK or ERROR */
    while (0u == base->SR)
    {
    }

    /* wait if busy */
    while ((base->SR & PUF_SR_BUSY_MASK) != 0u)
    {
    }

    /* return status */
    if (base->SR & (PUF_SR_OK_MASK | PUF_SR_ERROR_MASK))
    {
        status = kStatus_Success;
    }

    return status;
}

static void puf_powerOn(PUF_Type *base, puf_config_t *conf)
{
    /* Power On PUF SRAM */
    base->SRAM_CFG = 0x1u;
    while (0u == (PUF_SRAM_STATUS_READY_MASK & base->SRAM_STATUS))
    {
    }
}

static status_t puf_powerCycle(PUF_Type *base, puf_config_t *conf)
{
    /* Power off */
    base->SRAM_CFG = 0x0u;

    /* Reset PUF and reenable power to PUF SRAM */
    RESET_PeripheralReset(kPUF_RST_SHIFT_RSTn);
    puf_powerOn(base, conf);

    return kStatus_Success;
}

static status_t puf_makeStatus(PUF_Type *base, puf_last_operation_t operation)
{
    uint32_t result;
    status_t status = kStatus_Fail;

    if (((base->ORR & PUF_ORR_LAST_OPERATION_MASK) >> PUF_ORR_LAST_OPERATION_SHIFT) == operation)
    {
        result = (base->ORR & PUF_ORR_RESULT_CODE_MASK);
        if ((result == kPUF_ResultOK) && (0u == (base->SR & PUF_SR_ERROR_MASK)))
        {
            status = kStatus_Success;
        }
        else
        {
            status = MAKE_STATUS(kStatusGroup_PUF, result);
        }
    }

    return status;
}

/*!
 * brief Sets the default configuration of PUF
 *
 * This function initialize PUF config structure to default values.
 *
 * @param conf PUF configuration structure
 */
void PUF_GetDefaultConfig(puf_config_t *conf)
{
    /* Default configuration after reset */
    conf->dataEndianness = kPUF_EndianBig;
    conf->CKGATING       = 0U;
}

/*!
 * brief Initialize PUF
 *
 * This function enables power to PUF block and waits until the block initializes.
 *
 * @param conf PUF configuration structure
 * @return Status of the init operation
 */
status_t PUF_Init(PUF_Type *base, puf_config_t *conf)
{
    status_t status = kStatus_Fail;

    /* Enable PUF clock */
    CLOCK_EnableClock(kCLOCK_Puf);
    /* Reset PUF */
    RESET_PeripheralReset(kPUF_RST_SHIFT_RSTn);

    /* Set configuration from SRAM */
    base->SRAM_CFG |= PUF_SRAM_CFG_CKGATING(conf->CKGATING);

    /* Enable power to PUF SRAM */
    puf_powerOn(base, conf);

    /* Wait for peripheral to become ready */
    status = puf_waitForInit(base);

    /* In case of error or enroll & start not allowed, do power-cycle */
    if ((status != kStatus_Success) || ((PUF_AR_ALLOW_ENROLL_MASK | PUF_AR_ALLOW_START_MASK) !=
                                        (base->AR & (PUF_AR_ALLOW_ENROLL_MASK | PUF_AR_ALLOW_START_MASK))))
    {
        puf_powerCycle(base, conf);
        status = puf_waitForInit(base);
    }

    if (kStatus_Success == status)
    {
        /* Set data endianness */
        base->MISC = PUF_MISC_DATA_ENDIANNESS(conf->dataEndianness);

        /* get status */
        status = puf_makeStatus(base, kPUF_Init);
    }

    return status;
}

/*!
 * brief Denitialize PUF
 *
 * This function disables power to PUF SRAM and peripheral clock.
 *
 * @param base PUF peripheral base address
 * @param conf PUF configuration structure
 */
void PUF_Deinit(PUF_Type *base, puf_config_t *conf)
{
    base->SRAM_CFG = 0x0u;

    RESET_SetPeripheralReset(kPUF_RST_SHIFT_RSTn);
    CLOCK_DisableClock(kCLOCK_Puf);
}

/*!
 * brief Enroll PUF
 *
 * This function derives a digital fingerprint, generates the corresponding Activation Code (AC)
 * and returns it to be stored in an NVM or a file. This step needs to be
 * performed only once for each device. This function may be permanently disallowed by a fuse.
 *
 * @param base PUF peripheral base address
 * @param[out] activationCode Word aligned address of the resulting activation code.
 * @param activationCodeSize Size of the activationCode buffer in bytes. Shall be 996 bytes.
 * @param score Value of the PUF Score that was obtained during the enroll operation.
 * @return Status of enroll operation.
 */
status_t PUF_Enroll(PUF_Type *base, uint8_t *activationCode, size_t activationCodeSize, uint8_t *score)
{
    status_t status                 = kStatus_Fail;
    uint32_t *activationCodeAligned = NULL;
    register uint32_t temp32        = 0;

    /* check that activation code buffer size is at least 996 bytes */
    if (activationCodeSize < PUF_ACTIVATION_CODE_SIZE)
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned and valid activationCode */
    if ((0x3u & (uintptr_t)activationCode) || (activationCode == NULL))
    {
        return kStatus_InvalidArgument;
    }

    activationCodeAligned = (uint32_t *)(uintptr_t)activationCode;

    /* check if ENROLL is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_ENROLL_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* begin */
    base->CR = PUF_CR_ENROLL_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_ENROLL_MASK))
    {
    }

    /* read out AC */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
        if (0u != (PUF_SR_DO_REQUEST_MASK & base->SR))
        {
            temp32 = base->DOR;
            if (activationCodeSize >= sizeof(uint32_t))
            {
                *activationCodeAligned = temp32;
                activationCodeAligned++;
                activationCodeSize -= sizeof(uint32_t);
            }
        }
    }

    /* In case of success fill in score */
    if ((0u != (base->SR & PUF_SR_OK_MASK)) && (score != NULL))
    {
        *score = (uint8_t)(base->PSR & PUF_PSR_PUF_SCORE_MASK);
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_Enroll);

    return status;
}

/*!
 * brief Start PUF
 *
 * The Activation Code generated during the Enroll operation is used to
 * reconstruct the digital fingerprint. This needs to be done after every power-up
 * and reset.
 *
 * @param base PUF peripheral base address
 * @param[in] activationCode Word aligned address of the input activation code.
 * @param activationCodeSize Size of the activationCode buffer in bytes. Shall be 996 bytes.
 * @param score Value of the PUF Score that was obtained during the start operation.
 * return Status of start operation.
 */
status_t PUF_Start(PUF_Type *base, const uint8_t *activationCode, size_t activationCodeSize, uint8_t *score)
{
    status_t status                       = kStatus_Fail;
    const uint32_t *activationCodeAligned = NULL;
    register uint32_t temp32              = 0;

    /* check that activation code size is at least 996 bytes */
    if (activationCodeSize < PUF_ACTIVATION_CODE_SIZE)
    {
        return kStatus_InvalidArgument;
    }

    /* Set activationCodeSize to 996 bytes */
    activationCodeSize = PUF_ACTIVATION_CODE_SIZE;

    /* only work with aligned activationCode */
    if (0x3u & (uintptr_t)activationCode)
    {
        return kStatus_InvalidArgument;
    }

    activationCodeAligned = (const uint32_t *)(uintptr_t)activationCode;

    /* check if START is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_START_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* begin */
    base->CR = PUF_CR_START_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_START_MASK))
    {
    }

    /* while busy send AC */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
        if (0u != (PUF_SR_DI_REQUEST_MASK & base->SR))
        {
            if (activationCodeSize >= sizeof(uint32_t))
            {
                temp32 = *activationCodeAligned;
                activationCodeAligned++;
                activationCodeSize -= sizeof(uint32_t);
            }
            /* Send AC again */
            else
            {
                activationCodeAligned = (const uint32_t *)(uintptr_t)activationCode;
                temp32                = *activationCodeAligned;
                activationCodeAligned++;
                activationCodeSize = PUF_ACTIVATION_CODE_SIZE - sizeof(uint32_t);
            }
            base->DIR = temp32;
        }
    }

    /* In case of success fill in score */
    if ((0u != (base->SR & PUF_SR_OK_MASK)) && (score != NULL))
    {
        *score = (uint8_t)(base->PSR & PUF_PSR_PUF_SCORE_MASK);
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_Start);

    return status;
}

/*!
 * brief Stop PUF
 *
 * The Stop operation removes all key material from PUF flipflops and PUF SRAM, and sets
 * PUF to the Stopped state.
 *
 * @param base PUF peripheral base address
 * @return Status of stop operation.
 */
status_t PUF_Stop(PUF_Type *base)
{
    status_t status = kStatus_Fail;

    /* check if STOP is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_STOP_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* begin */
    base->CR = PUF_CR_STOP_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_STOP_MASK))
    {
    }

    /* wait while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_Stop);

    return status;
}

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
status_t PUF_GetKey(PUF_Type *base, puf_key_ctx_t *keyCtx, puf_key_dest_t keyDest, uint8_t *key, size_t keySize)
{
    uint8_t idx          = 0;
    uint32_t *keyAligned = NULL;
    uint32_t context[4]  = {0};
    status_t status      = kStatus_Fail;

    /* check if GET KEY is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_GET_KEY_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* check for key context */
    if (keyCtx == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* check for valid key destination */
    if (((keyDest == kPUF_KeyDestRegister) && (key == NULL)) || (keyDest == kPUF_KeyDestInvalid))
    {
        return kStatus_InvalidArgument;
    }

    /* check for valid key size. */
    /* must be 8byte multiple */
    if (keySize & 0x7u)
    {
        return kStatus_InvalidArgument;
    }
    /* if keySize > 128bytes, it must be equal to 256bytes or 384bytes or 512bytes */
    else if ((keySize > 128u) && !((keySize == 256u) || (keySize == 384u) || (keySize == 512u)))
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned key */
    if (0x3u & (uintptr_t)key)
    {
        return kStatus_InvalidArgument;
    }

    keyAligned = (uint32_t *)(uintptr_t)key;

    /* fill in key context */
    context[0] = PUF_KEY_OPERATION_CONTEXT_TYPE | ((keySize * 8u) & PUF_CONTEXT_KEY_LEN_MASK);
    context[1] = PUF_CONTEXT_GENERIC_KEY_TYPE | (keyCtx->keyScopeStarted << 8u) | keyCtx->keyScopeEnrolled;
    context[2] = keyCtx->userCtx0;
    context[3] = keyCtx->userCtx1;

    /* set key destination */
    base->KEY_DEST = keyDest;

    /* begin */
    base->CR = PUF_CR_GET_KEY_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_GET_KEY_MASK))
    {
    }

    /* send context and read output data while busy */
    while (0 != (base->SR & PUF_SR_BUSY_MASK))
    {
        if ((0 != (PUF_SR_DI_REQUEST_MASK & base->SR)) && (idx < 4u))
        {
            base->DIR = context[idx];
            idx++;
        }

        if ((0 != (PUF_SR_DO_REQUEST_MASK & base->SR)) && (kPUF_KeyDestRegister == keyDest))
        {
            if (keySize >= sizeof(uint32_t))
            {
                *keyAligned = base->DOR;
                keyAligned++;
                keySize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_GetKey);

    return status;
}

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
    PUF_Type *base, puf_key_ctx_t *keyCtx, size_t keySize, uint8_t *keyCode, size_t keyCodeSize)
{
    uint8_t idx              = 0;
    uint32_t *keyCodeAligned = NULL;
    uint32_t context[4]      = {0};
    status_t status          = kStatus_Fail;

    /* check if WRAP GENERATED RANDOM is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_WRAP_GENERATED_RANDOM_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* check for valid key context and keyCode buffer */
    if ((keyCtx == NULL) || (keyCode == NULL))
    {
        return kStatus_InvalidArgument;
    }

    /* check for valid key size. */
    /* must be 8byte multiple */
    if (keySize & 0x7u)
    {
        return kStatus_InvalidArgument;
    }
    /* if keySize > 128bytes, it must be equal to 256bytes or 384bytes or 512bytes */
    else if ((keySize > 128u) && !((keySize == 256u) || (keySize == 384u) || (keySize == 512u)))
    {
        return kStatus_InvalidArgument;
    }

    /* check that keyCodeSize is correct for given keySize */
    if (keyCodeSize < PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize))
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned key code */
    if (0x3u & (uintptr_t)keyCode)
    {
        return kStatus_InvalidArgument;
    }

    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;

    /* fill in key context */
    context[0] = PUF_KEY_OPERATION_CONTEXT_TYPE | ((keySize * 8u) & 0x1FFF);
    context[1] = PUF_CONTEXT_GENERIC_KEY_TYPE | (keyCtx->keyScopeStarted << 8u) | keyCtx->keyScopeEnrolled;
    context[2] = keyCtx->userCtx0;
    context[3] = keyCtx->userCtx1;

    /* begin */
    base->CR = PUF_CR_WRAP_GENERATED_RANDOM_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_WRAP_GENERATED_RANDOM_MASK))
    {
    }

    /* send context and read output data while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
        if ((0u != (PUF_SR_DI_REQUEST_MASK & base->SR)) && (idx < 4u))
        {
            base->DIR = context[idx];
            idx++;
        }

        if (0u != (PUF_SR_DO_REQUEST_MASK & base->SR))
        {
            if (keyCodeSize >= sizeof(uint32_t))
            {
                *keyCodeAligned = base->DOR;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_WrapGeneratedRandom);

    return status;
}

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
    PUF_Type *base, puf_key_ctx_t *keyCtx, uint8_t *userKey, size_t userKeySize, uint8_t *keyCode, size_t keyCodeSize)
{
    uint8_t ctxIdx           = 0;
    uint32_t *userKeyAligned = NULL;
    uint32_t *keyCodeAligned = NULL;
    uint32_t context[4]      = {0};
    status_t status          = kStatus_Fail;

    /* check if WRAP is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_WRAP_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* check for valid keyCtx and keyCode pointers */
    if ((keyCtx == NULL) || (keyCode == NULL))
    {
        return kStatus_InvalidArgument;
    }

    /* check for valid userKey size. */
    /* must be 8byte multiple */
    if (userKeySize & 0x7u)
    {
        return kStatus_InvalidArgument;
    }
    /* if userKeySize > 128bytes, it must be equal to 256bytes or 384bytes or 512bytes */
    else if ((userKeySize > 128u) && !((userKeySize == 256u) || (userKeySize == 384u) || (userKeySize == 512u)))
    {
        return kStatus_InvalidArgument;
    }

    /* check that keyCodeSize is correct for given userKeySize */
    if (keyCodeSize < PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(userKeySize))
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned userKey and key code */
    if ((0x3u & (uintptr_t)userKey) || (0x3u & (uintptr_t)keyCode))
    {
        return kStatus_InvalidArgument;
    }

    userKeyAligned = (uint32_t *)(uintptr_t)userKey;
    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;

    /* fill in key context */
    context[0] = PUF_KEY_OPERATION_CONTEXT_TYPE | ((userKeySize * 8u) & 0x1FFF);
    context[1] = PUF_CONTEXT_GENERIC_KEY_TYPE | (keyCtx->keyScopeStarted << 8u) | keyCtx->keyScopeEnrolled;
    context[2] = keyCtx->userCtx0;
    context[3] = keyCtx->userCtx1;

    /* begin */
    base->CR = PUF_CR_WRAP_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_WRAP_MASK))
    {
    }

    /* send context and read output data while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
        if (0u != (PUF_SR_DI_REQUEST_MASK & base->SR))
        {
            /* send context first */
            if (ctxIdx < 4u)
            {
                base->DIR = context[ctxIdx];
                ctxIdx++;
            }
            /* send userKey */
            else
            {
                base->DIR = *userKeyAligned;
                userKeyAligned++;
            }
        }

        if (0u != (PUF_SR_DO_REQUEST_MASK & base->SR))
        {
            if (keyCodeSize >= sizeof(uint32_t))
            {
                *keyCodeAligned = base->DOR;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_Wrap);

    return status;
}

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
    PUF_Type *base, puf_key_dest_t keyDest, uint8_t *keyCode, size_t keyCodeSize, uint8_t *key, size_t keySize)
{
    uint32_t *keyAligned     = NULL;
    uint32_t *keyCodeAligned = NULL;
    status_t status          = kStatus_Fail;

    /* check if UNWRAP is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_UNWRAP_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* check for valid key destination */
    if (((keyDest == kPUF_KeyDestRegister) && (key == NULL)) || (keyDest == kPUF_KeyDestInvalid))
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned key and key code */
    if ((0x3u & (uintptr_t)key) || (0x3u & (uintptr_t)keyCode))
    {
        return kStatus_InvalidArgument;
    }

    keyAligned     = (uint32_t *)(uintptr_t)key;
    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;

    /* set key destination */
    base->KEY_DEST = keyDest;

    /* begin */
    base->CR = PUF_CR_UNWRAP_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_UNWRAP_MASK))
    {
    }

    /* send context and read output data while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
        if (0u != (PUF_SR_DI_REQUEST_MASK & base->SR))
        {
            if (keyCodeSize >= sizeof(uint32_t))
            {
                base->DIR = *keyCodeAligned;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
        }

        if (0u != (PUF_SR_DO_REQUEST_MASK & base->SR))
        {
            if (keySize >= sizeof(uint32_t))
            {
                *keyAligned = base->DOR;
                keyAligned++;
                keySize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_Unwrap);

    return status;
}

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
status_t PUF_GenerateRandom(PUF_Type *base, uint8_t *data, size_t size)
{
    uint32_t context;
    uint32_t *dataAligned = NULL;
    status_t status       = kStatus_Fail;

    if (data == NULL)
    {
        return kStatus_InvalidArgument;
    }

    /* check if Generate random is allowed */
    if (0u == (base->AR & PUF_AR_ALLOW_GENERATE_RANDOM_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* check for valid size. */
    /* must be 8byte multiple */
    if (size & 0x7u)
    {
        return kStatus_InvalidArgument;
    }
    /* if size > 128bytes, it must be equal to 256bytes or 384bytes or 512bytes */
    else if ((size > 128u) && !((size == 256u) || (size == 384u) || (size == 512u)))
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned data buffer */
    if (0x3u & (uintptr_t)data)
    {
        return kStatus_InvalidArgument;
    }

    /* Configure context */
    context = ((size * 8u) & 0x1FFFu);

    dataAligned = (uint32_t *)(uintptr_t)data;

    /* begin */
    base->CR = PUF_CR_GENERATE_RANDOM_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_GENERATE_RANDOM_MASK))
    {
    }

    /* send context and read output data while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
        if (0u != (PUF_SR_DI_REQUEST_MASK & base->SR))
        {
            base->DIR = context;
        }

        if (0u != (PUF_SR_DO_REQUEST_MASK & base->SR))
        {
            *dataAligned = base->DOR;
            dataAligned++;
        }
    }

    /* get status */
    status = puf_makeStatus(base, kPUF_GenerateRandom);

    return status;
}

/*!
 * brief Zeroize PUF
 *
 * This function clears all PUF internal logic and puts the PUF to zeroized state.
 *
 * @param base PUF peripheral base address
 * @return Status of the zeroize operation.
 */
status_t PUF_Zeroize(PUF_Type *base)
{
    status_t status = kStatus_Fail;

    /* zeroize command is always allowed */
    base->CR = PUF_CR_ZEROIZE_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_ZEROIZE_MASK))
    {
    }

    /* wait while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
    }

    /* check status */
    if (((PUF_SR_ZEROIZED_MASK | PUF_SR_OK_MASK) == base->SR) && (0u == base->AR))
    {
        status = puf_makeStatus(base, kPUF_Zeroize);
    }

    return status;
}

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
status_t PUF_Test(PUF_Type *base, uint8_t *score)
{
    status_t status = kStatus_Fail;

    /* check if TEST is allowed */
    if (0x0u == (base->AR & PUF_AR_ALLOW_TEST_PUF_MASK))
    {
        return kStatus_PUF_OperationNotAllowed;
    }

    /* begin */
    base->CR = PUF_CR_TEST_PUF_MASK;

    /* wait till command is accepted */
    while (0u != (base->CR & PUF_CR_TEST_PUF_MASK))
    {
    }

    /* wait while busy */
    while (0u != (base->SR & PUF_SR_BUSY_MASK))
    {
    }

    /* In case of success fill in score */
    if ((0u != (base->SR & PUF_SR_OK_MASK)) && (score != NULL))
    {
        *score = (uint8_t)(base->PSR & PUF_PSR_PUF_SCORE_MASK);
    }

    /* Check status */
    status = puf_makeStatus(base, kPUF_Test);

    return status;
}
