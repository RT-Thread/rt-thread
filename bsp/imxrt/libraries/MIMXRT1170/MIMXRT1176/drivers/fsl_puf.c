/*
 * Copyright 2018-2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_puf.h"
#include "fsl_clock.h"
#include "fsl_common.h"

#if !(defined(FSL_FEATURE_PUF_HAS_NO_RESET) && (FSL_FEATURE_PUF_HAS_NO_RESET > 0))
#include "fsl_reset.h"
#endif /* FSL_FEATURE_PUF_HAS_NO_RESET */

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.puf"
#endif

/* RT6xx POWER CONTROL bit masks */
#if defined(FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL) && (FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL > 0)
#define PUF_PWRCTRL_CKDIS_MASK         (0x4U)
#define PUF_PWRCTRL_RAMINIT_MASK       (0x8U)
#define PUF_PWRCTRL_RAMPSWLARGEMA_MASK (0x10U)
#define PUF_PWRCTRL_RAMPSWLARGEMP_MASK (0x20U)
#define PUF_PWRCTRL_RAMPSWSMALLMA_MASK (0x40U)
#define PUF_PWRCTRL_RAMPSWSMALLMP_MASK (0x80U)
#endif

#if defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
#define DEFAULT_CKGATING 0x0u
#define PUF_ENABLE_MASK  0xFFFFFFFEu
#define PUF_ENABLE_CTRL  0x1u

#else
static void puf_wait_usec(volatile uint32_t usec, uint32_t coreClockFrequencyMHz)
{
    SDK_DelayAtLeastUs(usec, coreClockFrequencyMHz * 1000000U);

    /* Instead of calling SDK_DelayAtLeastUs() implement delay loop here */
    // while (usec > 0U)
    // {
    //     usec--;

    //     number of MHz is directly number of core clocks to wait 1 usec.
    //     the while loop below is actually 4 clocks so divide by 4 for ~1 usec
    //     volatile uint32_t ticksCount = coreClockFrequencyMHz / 4u + 1u;
    //     while (0U != ticksCount--)
    //     {
    //     }
    // }
}
#endif /* defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0) */

static status_t puf_waitForInit(PUF_Type *base)
{
    status_t status = kStatus_Fail;

    /* wait until status register reads non-zero. All zero is not valid. It should be BUSY or OK or ERROR */
    while (0U == base->STAT)
    {
    }

    /* wait if busy */
    while ((base->STAT & PUF_STAT_BUSY_MASK) != 0U)
    {
    }

    /* return status */
    if (0U != (base->STAT & (PUF_STAT_SUCCESS_MASK | PUF_STAT_ERROR_MASK)))
    {
        status = kStatus_Success;
    }

    return status;
}

static void puf_powerOn(PUF_Type *base, puf_config_t *conf)
{
#if defined(FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL) && (FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL > 0)
    /* RT6xxs */
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK);
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK);
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_RAMINIT_MASK);
#elif defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
    /* LPCXpresso55s16 */
    conf->puf_sram_base->CFG |= PUF_ENABLE_CTRL;
    while (0U == (PUF_SRAM_CTRL_STATUS_READY_MASK & conf->puf_sram_base->STATUS))
    {
    }
#else  /* !FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL */
    /* LPCXpresso55s69 & LPCXpresso54S018 */
    base->PWRCTRL = PUF_PWRCTRL_RAMON_MASK;
    while (0U == (PUF_PWRCTRL_RAMSTAT_MASK & base->PWRCTRL))
    {
    }
#endif /* FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL */
}
/*!
 * brief Powercycle PUF
 *
 * This function make powercycle of PUF.
 *
 * param base PUF peripheral base address
 * param conf PUF configuration structure
 * return Status of the powercycle operation.
 */
status_t PUF_PowerCycle(PUF_Type *base, puf_config_t *conf)
{
#if defined(FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL) && (FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL > 0)
    /* RT6xxs */
    uint32_t coreClockFrequencyMHz = conf->coreClockFrequencyHz / 1000000u;

    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK); /* disable RAM CK */

    /* enter ASPS mode */
    base->PWRCTRL = (PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK); /* SLEEP = 1 */
    base->PWRCTRL = (PUF_PWRCTRL_RAMINIT_MASK);                           /* enable RAM CK */
    base->PWRCTRL = (PUF_PWRCTRL_RAMINIT_MASK | PUF_PWRCTRL_RAMPSWLARGEMA_MASK | PUF_PWRCTRL_RAMPSWLARGEMP_MASK |
                     PUF_PWRCTRL_RAMPSWSMALLMA_MASK | PUF_PWRCTRL_RAMPSWSMALLMP_MASK); /* SLEEP=1, PSW*=1 */

    /* Wait enough time to discharge fully */
    puf_wait_usec(conf->dischargeTimeMsec * 1000u, conf->coreClockFrequencyHz / 1000000u);

    /* write PWRCTRL=0x38. wait time > 1 us */
    base->PWRCTRL = (PUF_PWRCTRL_RAMINIT_MASK | PUF_PWRCTRL_RAMPSWLARGEMA_MASK |
                     PUF_PWRCTRL_RAMPSWLARGEMP_MASK); /* SLEEP=1. PSWSMALL*=0. PSWLARGE*=1. */
    puf_wait_usec(1, coreClockFrequencyMHz);

    /* write PWRCTRL=0x8. wait time > 1 us */
    base->PWRCTRL = PUF_PWRCTRL_RAMINIT_MASK; /* SLEEP=1. PSWSMALL*=0. PSWLARGE*=0 */
    puf_wait_usec(1, coreClockFrequencyMHz);

    base->PWRCTRL = (PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK);
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK);
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_RAMINIT_MASK);

    /* Generate INITN low pulse */
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK);
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK);
    base->PWRCTRL = PUF_PWRCTRL_RAM_ON_MASK;
#elif defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
    /* LPCXpresso55s16 */
    conf->puf_sram_base->CFG &= PUF_ENABLE_MASK;
#else
    /* LPCXpresso55s69 & LPCXpresso54S018 */
    base->PWRCTRL = 0x0u;
    while (0U != (PUF_PWRCTRL_RAMSTAT_MASK & base->PWRCTRL))
    {
    }

    /* Wait enough time to discharge fully */
    puf_wait_usec(conf->dischargeTimeMsec * 1000u, conf->coreClockFrequencyHz / 1000000u);
#endif

#if !(defined(FSL_FEATURE_PUF_HAS_NO_RESET) && (FSL_FEATURE_PUF_HAS_NO_RESET > 0))
    /* Reset PUF and reenable power to PUF SRAM */
    RESET_PeripheralReset(kPUF_RST_SHIFT_RSTn);
#endif /* FSL_TEATURE_PUF_HAS_NO_RESET */
    puf_powerOn(base, conf);

    return kStatus_Success;
}

/*!
 * brief Sets the default configuration of PUF
 *
 * This function initialize PUF config structure to default values.
 *
 * param conf PUF configuration structure
 */
void PUF_GetDefaultConfig(puf_config_t *conf)
{
#if defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
    /* LPCXpresso55s16 */
    conf->puf_sram_base = PUF_SRAM_CTRL;

    /* Default configuration after reset */
    conf->CKGATING = DEFAULT_CKGATING; /* PUF SRAM Clock Gating */
#endif                                 /* FSL_FEATURE_PUF_HAS_SRAM_CTRL */

    conf->dischargeTimeMsec    = KEYSTORE_PUF_DISCHARGE_TIME_FIRST_TRY_MS;
    conf->coreClockFrequencyHz = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    return;
}

/*!
 * brief Initialize PUF
 *
 * This function enables power to PUF block and waits until the block initializes.
 *
 * param base PUF peripheral base address
 * param conf PUF configuration structure
 * return Status of the init operation
 */
status_t PUF_Init(PUF_Type *base, puf_config_t *conf)
{
    status_t status = kStatus_Fail;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Puf);
#endif
#if !(defined(FSL_FEATURE_PUF_HAS_NO_RESET) && (FSL_FEATURE_PUF_HAS_NO_RESET > 0))
    /* Reset PUF */
    RESET_PeripheralReset(kPUF_RST_SHIFT_RSTn);
#endif /* FSL_FEATURE_PUF_HAS_NO_RESET */

#if defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
    /* Set configuration for SRAM */
    conf->puf_sram_base->CFG |= PUF_SRAM_CTRL_CFG_CKGATING(conf->CKGATING);

#endif /* FSL_FEATURE_PUF_HAS_SRAM_CTRL */

    /* Enable power to PUF SRAM */
    puf_powerOn(base, conf);

    /* Wait for peripheral to become ready */
    status = puf_waitForInit(base);

    /* In case of error or enroll or start not allowed, do power-cycle */
    /* First try with shorter discharge time, if then it also fails try with longer time */
    /* conf->dischargeTimeMsec    = KEYSTORE_PUF_DISCHARGE_TIME_FIRST_TRY_MS; */
    if ((status != kStatus_Success) || (0U == (base->ALLOW & (PUF_ALLOW_ALLOWENROLL_MASK | PUF_ALLOW_ALLOWSTART_MASK))))
    {
        (void)PUF_PowerCycle(base, conf);
        status = puf_waitForInit(base);
    }

    /* In case of error or enroll or start not allowed, do power-cycle with worst discharge timing */
    if ((status != kStatus_Success) || (0U == (base->ALLOW & (PUF_ALLOW_ALLOWENROLL_MASK | PUF_ALLOW_ALLOWSTART_MASK))))
    {
        conf->dischargeTimeMsec = KEYSTORE_PUF_DISCHARGE_TIME_MAX_MS;
        (void)PUF_PowerCycle(base, conf);
        status = puf_waitForInit(base);
    }

    return status;
}

/*!
 * brief Denitialize PUF
 *
 * This function disables power to PUF SRAM and peripheral clock.
 *
 * param base PUF peripheral base address
 * param conf PUF configuration structure
 */
void PUF_Deinit(PUF_Type *base, puf_config_t *conf)
{
#if defined(FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL) && (FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL > 0)
    /* RT6xxs */
    base->PWRCTRL = (PUF_PWRCTRL_RAM_ON_MASK | PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK); /* disable RAM CK */

    /* enter ASPS mode */
    base->PWRCTRL = (PUF_PWRCTRL_CK_DIS_MASK | PUF_PWRCTRL_RAMINIT_MASK); /* SLEEP = 1 */
    base->PWRCTRL = PUF_PWRCTRL_RAMINIT_MASK;                             /* enable RAM CK */
    base->PWRCTRL = (PUF_PWRCTRL_RAMINIT_MASK | PUF_PWRCTRL_RAMPSWLARGEMA_MASK | PUF_PWRCTRL_RAMPSWLARGEMP_MASK |
                     PUF_PWRCTRL_RAMPSWSMALLMA_MASK | PUF_PWRCTRL_RAMPSWSMALLMP_MASK); /* SLEEP=1, PSW*=1 */
    puf_wait_usec(conf->dischargeTimeMsec * 1000u, conf->coreClockFrequencyHz / 1000000u);
#elif defined(FSL_FEATURE_PUF_HAS_SRAM_CTRL) && (FSL_FEATURE_PUF_HAS_SRAM_CTRL > 0)
    /* LPCXpresso55s16 */
    conf->puf_sram_base = PUF_SRAM_CTRL;
    conf->puf_sram_base->CFG &= PUF_ENABLE_MASK;
#else /* !FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL */
    /* LPCXpresso55s69 & LPCXpresso54S018 */
    base->PWRCTRL = 0x00u;
    puf_wait_usec(conf->dischargeTimeMsec * 1000u, conf->coreClockFrequencyHz / 1000000u);
#endif

#if !(defined(FSL_FEATURE_PUF_HAS_NO_RESET) && (FSL_FEATURE_PUF_HAS_NO_RESET > 0))
    RESET_SetPeripheralReset(kPUF_RST_SHIFT_RSTn);
#endif /* FSL_FEATURE_PUF_HAS_NO_RESET */

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Puf);
#endif
}

/*!
 * brief Enroll PUF
 *
 * This function derives a digital fingerprint, generates the corresponding Activation Code (AC)
 * and returns it to be stored in an NVM or a file. This step needs to be
 * performed only once for each device. This function may be permanently disallowed by a fuse.
 *
 * param base PUF peripheral base address
 * param[out] activationCode Word aligned address of the resulting activation code.
 * param activationCodeSize Size of the activationCode buffer in bytes. Shall be 1192 bytes.
 * return Status of enroll operation.
 */
status_t PUF_Enroll(PUF_Type *base, uint8_t *activationCode, size_t activationCodeSize)
{
    status_t status                 = kStatus_Fail;
    uint32_t *activationCodeAligned = NULL;
    register uint32_t temp32        = 0;

    /* check that activation code buffer size is at least 1192 bytes */
    if (activationCodeSize < PUF_ACTIVATION_CODE_SIZE)
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned activationCode */
    if (0U != (0x3u & (uintptr_t)activationCode))
    {
        return kStatus_InvalidArgument;
    }

    activationCodeAligned = (uint32_t *)(uintptr_t)activationCode;

    /* check if ENROLL is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWENROLL_MASK))
    {
        return kStatus_EnrollNotAllowed;
    }

    /* begin */
    base->CTRL = PUF_CTRL_ENROLL_MASK;

    /* check status */
    while (0U == (base->STAT & (PUF_STAT_BUSY_MASK | PUF_STAT_ERROR_MASK)))
    {
    }

    /* read out AC */
    while (0U != (base->STAT & PUF_STAT_BUSY_MASK))
    {
        if (0U != (PUF_STAT_CODEOUTAVAIL_MASK & base->STAT))
        {
            temp32 = base->CODEOUTPUT;
            if (activationCodeSize >= sizeof(uint32_t))
            {
                *activationCodeAligned = temp32;
                activationCodeAligned++;
                activationCodeSize -= sizeof(uint32_t);
            }
        }
    }

    if (((base->STAT & PUF_STAT_SUCCESS_MASK) != 0U) && (activationCodeSize == 0U))
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Start PUF
 *
 * The Activation Code generated during the Enroll operation is used to
 * reconstruct the digital fingerprint. This needs to be done after every power-up
 * and reset.
 *
 * param base PUF peripheral base address
 * param activationCode Word aligned address of the input activation code.
 * param activationCodeSize Size of the activationCode buffer in bytes. Shall be 1192 bytes.
 * return Status of start operation.
 */
status_t PUF_Start(PUF_Type *base, const uint8_t *activationCode, size_t activationCodeSize)
{
    status_t status                       = kStatus_Fail;
    const uint32_t *activationCodeAligned = NULL;
    register uint32_t temp32              = 0;

    /* check that activation code size is at least 1192 bytes */
    if (activationCodeSize < 1192U)
    {
        return kStatus_InvalidArgument;
    }

    /* only work with aligned activationCode */
    if (0U != (0x3u & (uintptr_t)activationCode))
    {
        return kStatus_InvalidArgument;
    }

    activationCodeAligned = (const uint32_t *)(uintptr_t)activationCode;

    /* check if START is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWSTART_MASK))
    {
        return kStatus_StartNotAllowed;
    }

    /* begin */
    base->CTRL = PUF_CTRL_START_MASK;

    /* check status */
    while (0U == (base->STAT & (PUF_STAT_BUSY_MASK | PUF_STAT_ERROR_MASK)))
    {
    }

    /* while busy send AC */
    while (0U != (base->STAT & PUF_STAT_BUSY_MASK))
    {
        if (0U != (PUF_STAT_CODEINREQ_MASK & base->STAT))
        {
            if (activationCodeSize >= sizeof(uint32_t))
            {
                temp32 = *activationCodeAligned;
                activationCodeAligned++;
                activationCodeSize -= sizeof(uint32_t);
            }
            base->CODEINPUT = temp32;
        }
    }

    /* get status */
    if (0U != (base->STAT & PUF_STAT_SUCCESS_MASK))
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Set intrinsic key
 *
 * The digital fingerprint generated during the Enroll/Start
 * operations is used to generate a Key Code (KC) that defines a unique intrinsic
 * key. This KC is returned to be stored in an NVM or a file. This operation
 * needs to be done only once for each intrinsic key.
 * Each time a Set Intrinsic Key operation is executed a new unique key is
 * generated.
 *
 * param base PUF peripheral base address
 * param keyIndex PUF key index register
 * param keySize Size of the intrinsic key to generate in bytes.
 * param[out] keyCode Word aligned address of the resulting key code.
 * param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize).
 * return Status of set intrinsic key operation.
 */
status_t PUF_SetIntrinsicKey(
    PUF_Type *base, puf_key_index_register_t keyIndex, size_t keySize, uint8_t *keyCode, size_t keyCodeSize)
{
    status_t status          = kStatus_Fail;
    uint32_t *keyCodeAligned = NULL;
    register uint32_t temp32 = 0;

    /* check if SET KEY is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWSETKEY_MASK))
    {
        return kStatus_Fail;
    }

    /* only work with aligned keyCode */
    if (0U != (0x3u & (uintptr_t)keyCode))
    {
        return kStatus_InvalidArgument;
    }

    /* Check that keySize is in the correct range and that it is multiple of 8 */
    if ((keySize < (uint32_t)kPUF_KeySizeMin) || (keySize > (uint32_t)kPUF_KeySizeMax) || (0U != (keySize & 0x7U)))
    {
        return kStatus_InvalidArgument;
    }

    /* check that keyCodeSize is correct for given keySize */
    if (keyCodeSize < PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize))
    {
        return kStatus_InvalidArgument;
    }

    if ((uint32_t)keyIndex > (uint32_t)kPUF_KeyIndexMax)
    {
        return kStatus_InvalidArgument;
    }

    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;

    /* program the key size and index */
    base->KEYSIZE  = keySize >> 3;
    base->KEYINDEX = (uint32_t)keyIndex;

    /* begin */
    base->CTRL = PUF_CTRL_GENERATEKEY_MASK;

    /* wait till command is accepted */
    while (0U == (base->STAT & (PUF_STAT_BUSY_MASK | PUF_STAT_ERROR_MASK)))
    {
    }

    /* while busy read KC */
    while (0U != (base->STAT & PUF_STAT_BUSY_MASK))
    {
        if (0U != (PUF_STAT_CODEOUTAVAIL_MASK & base->STAT))
        {
            temp32 = base->CODEOUTPUT;
            if (keyCodeSize >= sizeof(uint32_t))
            {
                *keyCodeAligned = temp32;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    if (0U != (base->STAT & PUF_STAT_SUCCESS_MASK))
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Set user key
 *
 * The digital fingerprint generated during the Enroll/Start
 * operations and a user key (UK) provided as input are used to
 * generate a Key Code (KC). This KC is sent returned to be stored
 * in an NVM or a file. This operation needs to be done only once for each user key.
 *
 * param base PUF peripheral base address
 * param keyIndex PUF key index register
 * param userKey Word aligned address of input user key.
 * param userKeySize Size of the input user key in bytes.
 * param[out] keyCode Word aligned address of the resulting key code.
 * param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(userKeySize).
 * return Status of set user key operation.
 */
status_t PUF_SetUserKey(PUF_Type *base,
                        puf_key_index_register_t keyIndex,
                        const uint8_t *userKey,
                        size_t userKeySize,
                        uint8_t *keyCode,
                        size_t keyCodeSize)
{
    status_t status                = kStatus_Fail;
    uint32_t *keyCodeAligned       = NULL;
    const uint32_t *userKeyAligned = NULL;
    register uint32_t temp32       = 0;

    /* check if SET KEY is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWSETKEY_MASK))
    {
        return kStatus_Fail;
    }

    /* only work with aligned keyCode */
    if (0U != (0x3u & (uintptr_t)keyCode))
    {
        return kStatus_InvalidArgument;
    }

    /* Check that userKeySize is in the correct range and that it is multiple of 8 */
    if ((userKeySize < (uint32_t)kPUF_KeySizeMin) || (userKeySize > (uint32_t)kPUF_KeySizeMax) ||
        (0U != (userKeySize & 0x7U)))
    {
        return kStatus_InvalidArgument;
    }

    /* check that keyCodeSize is correct for given userKeySize */
    if (keyCodeSize < PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(userKeySize))
    {
        return kStatus_InvalidArgument;
    }

    if ((uint32_t)keyIndex > (uint32_t)kPUF_KeyIndexMax)
    {
        return kStatus_InvalidArgument;
    }

    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;
    userKeyAligned = (const uint32_t *)(uintptr_t)userKey;

    /* program the key size and index */
    base->KEYSIZE  = userKeySize >> 3; /* convert to 64-bit blocks */
    base->KEYINDEX = (uint32_t)keyIndex;

    /* We have to store the user key on index 0 swaped for HW bus */
    if (keyIndex == kPUF_KeyIndex_00)
    {
        userKeyAligned = userKeyAligned + (userKeySize / sizeof(uint32_t));
    }

    /* begin */
    base->CTRL = PUF_CTRL_SETKEY_MASK;

    /* wait till command is accepted */
    while (0U == (base->STAT & (PUF_STAT_BUSY_MASK | PUF_STAT_ERROR_MASK)))
    {
    }

    /* while busy write UK and read KC */
    while (0U != (base->STAT & PUF_STAT_BUSY_MASK))
    {
        if (0U != (PUF_STAT_KEYINREQ_MASK & base->STAT))
        {
            if (userKeySize >= sizeof(uint32_t))
            {
#if defined(LPC54S018_SERIES)
                if (keyIndex == kPUF_KeyIndex_00)
                {
                    userKeyAligned--;
                    temp32 = *userKeyAligned;
                    userKeySize -= sizeof(uint32_t);
                }
#else
                if (keyIndex == kPUF_KeyIndex_00)
                {
                    userKeyAligned--;
                    temp32 = __REV(*userKeyAligned);
                    userKeySize--;
                }
#endif /* defined(LPC54S018_SERIES) */
                else if (keyIndex != kPUF_KeyIndex_00)
                {
                    temp32 = *userKeyAligned;
                    userKeyAligned++;
                    userKeySize -= sizeof(uint32_t);
                }
                else
                {
                    /* Intentional empty */
                }
            }
            base->KEYINPUT = temp32;
        }

        if (0U != (PUF_STAT_CODEOUTAVAIL_MASK & base->STAT))
        {
            temp32 = base->CODEOUTPUT;
            if (keyCodeSize >= sizeof(uint32_t))
            {
                *keyCodeAligned = temp32;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    if (0U != (base->STAT & PUF_STAT_SUCCESS_MASK))
    {
        status = kStatus_Success;
    }

    return status;
}

static status_t puf_getHwKey(PUF_Type *base, const uint8_t *keyCode, size_t keyCodeSize)
{
    status_t status          = kStatus_Fail;
    uint32_t *keyCodeAligned = NULL;
    register uint32_t temp32 = 0;

    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;

    /* begin */
    base->CTRL = PUF_CTRL_GETKEY_MASK;

    /* wait till command is accepted */
    while (0U == (base->STAT & (PUF_STAT_BUSY_MASK | PUF_STAT_ERROR_MASK)))
    {
    }

    /* while busy send KC, key is reconstructed to HW bus */
    while (0U != (base->STAT & PUF_STAT_BUSY_MASK))
    {
        if (0U != (PUF_STAT_CODEINREQ_MASK & base->STAT))
        {
            if (keyCodeSize >= sizeof(uint32_t))
            {
                temp32 = *keyCodeAligned;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
            base->CODEINPUT = temp32;
        }
    }

    /* get status */
    if (0U != (base->STAT & PUF_STAT_SUCCESS_MASK))
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Reconstruct hw bus key from a key code
 *
 * The digital fingerprint generated during the Start operation and the KC
 * generated during a Set Key operation (Set intrinsic key or Set user key) are used to retrieve a stored key. This
 * operation needs to be done every time a key is needed.
 * This function accepts only Key Codes created for PUF index register kPUF_KeyIndex_00.
 * Such a key is output directly to a dedicated hardware bus. The reconstructed key is not exposed to system memory.
 *
 * param base PUF peripheral base address
 * param keyCode Word aligned address of the input key code.
 * param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize).
 * param keySlot key slot to output on hw bus. Parameter is ignored on devices with less than two key slots.
 * param keyMask key masking value. Shall be random for each POR/reset. Value does not have to be cryptographicaly
 * secure.
 * return Status of get key operation.
 */
status_t PUF_GetHwKey(
    PUF_Type *base, const uint8_t *keyCode, size_t keyCodeSize, puf_key_slot_t keySlot, uint32_t keyMask)
{
    status_t status = kStatus_Fail;
    uint32_t keyIndex;

    /* check if GET KEY is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWGETKEY_MASK))
    {
        return kStatus_Fail;
    }

    /* only work with aligned keyCode */
    if (0U != (0x3u & (uintptr_t)keyCode))
    {
        return kStatus_Fail;
    }

    /* check that keyCodeSize is at least PUF_MIN_KEY_CODE_SIZE */
    if (keyCodeSize < PUF_MIN_KEY_CODE_SIZE)
    {
        return kStatus_InvalidArgument;
    }

    keyIndex = (uint32_t)(0x0Fu & (uint32_t)keyCode[1]);

    /* check the Key Code header byte 1. index must be zero for the hw key. */
    if (kPUF_KeyIndex_00 != (puf_key_index_register_t)keyIndex)
    {
        return kStatus_Fail;
    }

#if defined(PUF_KEYMASK_COUNT) && (PUF_KEYMASK_COUNT > 0)
    volatile uint32_t *keyMask_reg = NULL;
    uint32_t regVal                = ((uint32_t)2U << ((uint32_t)2U * (uint32_t)keySlot));

    switch (keySlot)
    {
        case kPUF_KeySlot0:
            keyMask_reg = &base->KEYMASK[0];
            break;

        case kPUF_KeySlot1:
            keyMask_reg = &base->KEYMASK[1];
            break;
#if (PUF_KEYMASK_COUNT > 2)
        case kPUF_KeySlot2:
            keyMask_reg = &base->KEYMASK[2];
            break;

        case kPUF_KeySlot3:
            keyMask_reg = &base->KEYMASK[3];
            break;
#endif /* PUF_KEYMASK_COUNT > 2 */
        default:
            status = kStatus_InvalidArgument;
            break;
    }
#endif /* PUF_KEYMASK_COUNT */

    if (status != kStatus_InvalidArgument)
    {
#if defined(PUF_KEYMASK_COUNT) && (PUF_KEYMASK_COUNT > 0)
        base->KEYRESET  = regVal;
        base->KEYENABLE = regVal;
        *keyMask_reg    = keyMask;
#endif /* FSL_FEATURE_PUF_HAS_KEYSLOTS */

        status = puf_getHwKey(base, keyCode, keyCodeSize);

#if defined(FSL_FEATURE_PUF_HAS_SHIFT_STATUS) && (FSL_FEATURE_PUF_HAS_SHIFT_STATUS > 0)
        size_t keyWords = 0;

        if (status == kStatus_Success)
        {
            /* if the corresponding shift count does not match, return fail anyway */
            keyWords = ((((size_t)keyCode[3]) * 2U) - 1u) << ((size_t)keySlot << 2U);
            if (keyWords != ((0x0FUL << ((uint32_t)keySlot << 2U)) & base->SHIFT_STATUS))
            {
                status = kStatus_Fail;
            }
        }
#elif defined(PUF_IDXBLK_SHIFT_IND_KEY0_MASK) && PUF_IDXBLK_SHIFT_IND_KEY0_MASK
        size_t keyWords = 0;

        if (status == kStatus_Success)
        {
            /* if the corresponding shift count does not match, return fail anyway */
            keyWords = ((((size_t)keyCode[3]) * 2U) - 1u) << ((size_t)keySlot << 2U);
            if (keyWords != ((0x0FUL << ((uint32_t)keySlot << 2U)) & base->IDXBLK_SHIFT))
            {
                status = kStatus_Fail;
            }
        }
#endif /* FSL_FEATURE_PUF_HAS_SHIFT_STATUS || PUF_IDXBLK_SHIFT_IND_KEY0_MASK */
    }

    return status;
}

/*!
 * brief Checks if Get Key operation is allowed.
 *
 * This function returns true if get key operation is allowed.
 *
 * param base PUF peripheral base address
 * return true if get key operation is allowed
 */
bool PUF_IsGetKeyAllowed(PUF_Type *base)
{
    /* check if GET KEY is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWGETKEY_MASK))
    {
        return false;
    }

    return true;
}

/*!
 * brief Reconstruct key from a key code
 *
 * The digital fingerprint generated during the Start operation and the KC
 * generated during a Set Key operation (Set intrinsic key or Set user key) are used to retrieve a stored key. This
 * operation needs to be done every time a key is needed.
 * This function accepts only Key Codes created for PUF index registers kPUF_KeyIndex_01 to kPUF_KeyIndex_15.
 *
 * param base PUF peripheral base address
 * param keyCode Word aligned address of the input key code.
 * param keyCodeSize Size of the keyCode buffer in bytes. Shall be PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize).
 * param[out] key Word aligned address of output key.
 * param keySize Size of the output key in bytes.
 * return Status of get key operation.
 */
status_t PUF_GetKey(PUF_Type *base, const uint8_t *keyCode, size_t keyCodeSize, uint8_t *key, size_t keySize)
{
    status_t status          = kStatus_Fail;
    uint32_t *keyCodeAligned = NULL;
    uint32_t *keyAligned     = NULL;
    uint32_t keyIndex;
    register uint32_t temp32 = 0;

    /* check if GET KEY is allowed */
    if (0x0u == (base->ALLOW & PUF_ALLOW_ALLOWGETKEY_MASK))
    {
        return kStatus_Fail;
    }

    /* only work with aligned keyCode */
    if (0U != (0x3u & (uintptr_t)keyCode))
    {
        return kStatus_Fail;
    }

    /* only work with aligned key */
    if (0U != (0x3u & (uintptr_t)key))
    {
        return kStatus_Fail;
    }

    /* check that keyCodeSize is correct for given keySize */
    if (keyCodeSize < PUF_GET_KEY_CODE_SIZE_FOR_KEY_SIZE(keySize))
    {
        return kStatus_InvalidArgument;
    }

    keyIndex = (0x0Fu & (uint32_t)keyCode[1]);

    /* check the Key Code header byte 1. index must be non-zero for the register key. */
    if (kPUF_KeyIndex_00 == (puf_key_index_register_t)keyIndex)
    {
        return kStatus_Fail;
    }

    keyCodeAligned = (uint32_t *)(uintptr_t)keyCode;
    keyAligned     = (uint32_t *)(uintptr_t)key;

    /* begin */
    base->CTRL = PUF_CTRL_GETKEY_MASK;

    /* wait till command is accepted */
    while (0U == (base->STAT & (PUF_STAT_BUSY_MASK | PUF_STAT_ERROR_MASK)))
    {
    }

    /* while busy send KC, read key */
    while (0U != (base->STAT & PUF_STAT_BUSY_MASK))
    {
        if (0U != (PUF_STAT_CODEINREQ_MASK & base->STAT))
        {
            temp32 = 0;
            if (keyCodeSize >= sizeof(uint32_t))
            {
                temp32 = *keyCodeAligned;
                keyCodeAligned++;
                keyCodeSize -= sizeof(uint32_t);
            }
            base->CODEINPUT = temp32;
        }

        if (0U != (PUF_STAT_KEYOUTAVAIL_MASK & base->STAT))
        {
            keyIndex = base->KEYOUTINDEX;
            temp32   = base->KEYOUTPUT;
            if (keySize >= sizeof(uint32_t))
            {
                *keyAligned = temp32;
                keyAligned++;
                keySize -= sizeof(uint32_t);
            }
        }
    }

    /* get status */
    if ((keyIndex != 0U) && (0U != (base->STAT & PUF_STAT_SUCCESS_MASK)))
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Zeroize PUF
 *
 * This function clears all PUF internal logic and puts the PUF to error state.
 *
 * param base PUF peripheral base address
 * return Status of the zeroize operation.
 */
status_t PUF_Zeroize(PUF_Type *base)
{
    status_t status = kStatus_Fail;

    /* zeroize command is always allowed */
    base->CTRL = PUF_CTRL_ZEROIZE_MASK;

    /* check that command is accepted */
    if ((0U != (base->STAT & PUF_STAT_ERROR_MASK)) && (0U == base->ALLOW))
    {
        status = kStatus_Success;
    }

    return status;
}
