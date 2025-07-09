/*
 * Copyright 2019-2020, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_ocotp.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.ocotp"
#endif

#if defined(FSL_FEATURE_OCOTP_HAS_STATUS) && FSL_FEATURE_OCOTP_HAS_STATUS
#define OCOTP_STATUS_READ_DED_MASK                                                             \
    (OCOTP_OUT_STATUS0_DED0_MASK | OCOTP_OUT_STATUS0_DED1_MASK | OCOTP_OUT_STATUS0_DED2_MASK | \
     OCOTP_OUT_STATUS0_DED3_MASK)
#endif

/* Wait time should be not less than 150ns . */
#define OCOTP_TIMING_WAIT_NS (uint64_t)150
/* Relex time should be not less than 100ns . */
#define OCOTP_TIMING_RELEX_NS (uint64_t)100
/* Program time should be rang from 9000ns~11000ns. */
#define OCOTP_TIMING_PROGRAM_NS (uint64_t)10000
/* Read time should be less than 40ns. */
#define OCOTP_TIMING_READ_NS (uint64_t)40

/* Unlock key is 0x3E77. */
#define OCOTP_WRITE_UNLOCK_KEY (0x3E77)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
/*!
 * @brief Set read timing configuration.
 *
 * @param base          OCOTP peripheral base addess.
 * @param timingConfig  configuration of timing.
 */
static void OCOTP_SetReadTiming(OCOTP_Type *base, ocotp_timing_t timingConfig);

/*!
 * @brief Set write timing configuration.
 *
 * @param base          OCOTP peripheral base addess.
 * @param timingConfig  configuration of timing.
 */
static void OCOTP_SetWriteTiming(OCOTP_Type *base, ocotp_timing_t timingConfig);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
/* Timing configuration for OCOTP controller. */
static ocotp_timing_t s_timingConfig;
#endif

/*******************************************************************************
 * Code
 *******************************************************************************/
/* Reload the shadow register. */
status_t OCOTP_ReloadShadowRegister(OCOTP_Type *base)
{
    assert(NULL != base);

    status_t status = kStatus_Success;

    /* Make sure the OCOTP is ready, Overlapped accesses are not supported by the controller. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* Clear access error status bit. */
    OCOTP_ClearErrorStatus(base);

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    /* Set the read timing. */
    OCOTP_SetReadTiming(base, s_timingConfig);

    /* Wait for the OCOTP controller not busy. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }
#endif

#if defined(OCOTP_OUT_STATUS0_DED_RELOAD_MASK)
    /* Clear reload error status. */
    base->OUT_STATUS0_CLR = OCOTP_OUT_STATUS0_DED_RELOAD_MASK;
#endif

    /* Set reload bit. */
    base->CTRL_SET = OCOTP_CTRL_RELOAD_SHADOWS(1);

    /* Wait for the OCOTP controller not busy. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }
    /* Wait for shadow register reload complete. this bit will be auto clear by OCOTP once operation is complete. */
    while (OCOTP_CTRL_RELOAD_SHADOWS_MASK == (base->CTRL & OCOTP_CTRL_RELOAD_SHADOWS_MASK))
    {
    }

#if defined(OCOTP_OUT_STATUS0_DED_RELOAD_MASK)
    if ((base->OUT_STATUS0 & OCOTP_OUT_STATUS0_DED_RELOAD_MASK) != 0U)
    {
        status = kStatus_OCOTP_ReloadError;
    }
#endif

    return status;
}

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
static void OCOTP_SetReadTiming(OCOTP_Type *base, ocotp_timing_t timingConfig)
{
    uint32_t timingValue = base->TIMING;

    timingValue &= ~(OCOTP_TIMING_RELAX_MASK | OCOTP_TIMING_STROBE_READ_MASK | OCOTP_TIMING_WAIT_MASK);
    timingValue |= OCOTP_TIMING_RELAX(timingConfig.relax) | OCOTP_TIMING_STROBE_READ(timingConfig.strobe_read) |
                   OCOTP_TIMING_WAIT(timingConfig.wait);
    base->TIMING = timingValue;
}

static void OCOTP_SetWriteTiming(OCOTP_Type *base, ocotp_timing_t timingConfig)
{
    uint32_t timingValue = base->TIMING;

    timingValue &= ~(OCOTP_TIMING_RELAX_MASK | OCOTP_TIMING_STROBE_PROG_MASK | OCOTP_TIMING_WAIT_MASK);
    timingValue |= OCOTP_TIMING_RELAX(timingConfig.relax) | OCOTP_TIMING_STROBE_PROG(timingConfig.strobe_prog) |
                   OCOTP_TIMING_WAIT(timingConfig.wait);

    base->TIMING = timingValue;
}
#endif

/* Initializes OCOTP controller. */
void OCOTP_Init(OCOTP_Type *base, uint32_t srcClock_Hz)
{
    assert(NULL != base);
#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    assert(0UL != srcClock_Hz);
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable OCOTP clock */
    CLOCK_EnableClock(kCLOCK_Ocotp);
#endif

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    /* tWait time shoule be higher than OCOTP_TIMING_WAIT_NS. */
    s_timingConfig.wait = (uint32_t)((OCOTP_TIMING_WAIT_NS * srcClock_Hz + 1000000000U) / 1000000000U - 1U);

    /* tRelax time shoule be higher than OCOTP_TIMING_RELEX_NS. */
    s_timingConfig.relax = (uint32_t)((OCOTP_TIMING_RELEX_NS * srcClock_Hz + 1000000000U) / 1000000000U - 1U);

    /* tStrobe_prog time should be close to OCOTP_TIMING_PROGRAM_NS, only add half of 1000000000. */
    s_timingConfig.strobe_prog = (uint32_t)((OCOTP_TIMING_PROGRAM_NS * srcClock_Hz + 500000000U) / 1000000000U) +
                                 2U * (s_timingConfig.relax + 1U) - 1U;

    /* tStrobe_read time should be higher than OCOTP_TIMING_READ_NS. */
    s_timingConfig.strobe_read = (uint32_t)((OCOTP_TIMING_READ_NS * srcClock_Hz + 1000000000U) / 1000000000U) +
                                 2U * (s_timingConfig.relax + 1U) - 1U;
#endif
}

/* De-init OCOTP controller. */
void OCOTP_Deinit(OCOTP_Type *base)
{
    assert(NULL != base);

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    s_timingConfig.wait        = 0UL;
    s_timingConfig.relax       = 0UL;
    s_timingConfig.strobe_prog = 0UL;
    s_timingConfig.strobe_read = 0UL;
#endif

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable OCOTP clock */
    CLOCK_DisableClock(kCLOCK_Ocotp);
#endif
}

/* Read the fuse shadow register. */
uint32_t OCOTP_ReadFuseShadowRegister(OCOTP_Type *base, uint32_t address)
{
    assert(NULL != base);

    uint32_t data = 0U;

    (void)OCOTP_ReadFuseShadowRegisterExt(base, address, &data, 1);

    return data;
}

status_t OCOTP_ReadFuseShadowRegisterExt(OCOTP_Type *base, uint32_t address, uint32_t *data, uint8_t fuseWords)
{
    assert((fuseWords > 0U) && (fuseWords <= OCOTP_READ_FUSE_DATA_COUNT));
    assert(NULL != data);

    status_t status = kStatus_Success;

#if (OCOTP_READ_FUSE_DATA_COUNT > 1U)
    uint32_t i;
#endif

    /* Make sure the OCOTP is ready, Overlapped accesses are not supported by the controller. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* If ERROR bit was set, clear access error status bit. */
    if (OCOTP_CheckErrorStatus(base))
    {
        OCOTP_ClearErrorStatus(base);
    }

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    /* Set the read timing. */
    OCOTP_SetReadTiming(base, s_timingConfig);

    /* Wait for busy bit is cleared. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* Clear access error status bit. */
    if (OCOTP_CheckErrorStatus(base))
    {
        OCOTP_ClearErrorStatus(base);
    }
#endif

#if defined(OCOTP_STATUS_READ_DED_MASK)
    /* Clear error flags. */
    base->OUT_STATUS0_CLR = OCOTP_STATUS_READ_DED_MASK;
#endif

    /* Write requested address to register. */
    base->CTRL_CLR = OCOTP_CTRL_CLR_ADDR_MASK;
    base->CTRL_SET = OCOTP_CTRL_SET_ADDR(address);

    /* Set OCOTP auto read enable. */
#if defined(OCOTP_READ_CTRL_READ_NUM_MASK)
    base->READ_CTRL = (base->READ_CTRL & ~(OCOTP_READ_CTRL_READ_NUM_MASK)) |
                      OCOTP_READ_CTRL_READ_NUM((uint32_t)fuseWords - 1U) | OCOTP_READ_CTRL_READ_FUSE_MASK;
#elif defined(OCOTP_READ_CTRL_READ_FUSE_CNTR_MASK)
    base->READ_CTRL = (base->READ_CTRL & ~(OCOTP_READ_CTRL_READ_FUSE_CNTR_MASK)) |
                      OCOTP_READ_CTRL_READ_FUSE_CNTR((uint32_t)fuseWords - 1U) | OCOTP_READ_CTRL_READ_FUSE_MASK;
#else
    base->READ_CTRL |= OCOTP_READ_CTRL_READ_FUSE_MASK;
#endif

    /* Wait for busy bit is cleared, and no error occurred on controller. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* If ERROR bit was set, this may be mean that the accsee to the register was wrong. */
    if (OCOTP_CheckErrorStatus(base))
    {
        /* Clear access error status bit. */
        OCOTP_ClearErrorStatus(base);

        status = kStatus_OCOTP_AccessError;
    }

#if defined(OCOTP_STATUS_READ_DED_MASK)
    if ((base->OUT_STATUS0 & OCOTP_STATUS_READ_DED_MASK) != 0U)
    {
        status = kStatus_Fail;
    }
#endif

#if (OCOTP_READ_FUSE_DATA_COUNT == 1U)
    *data = base->READ_FUSE_DATA;
#else
    for (i = 0; i < fuseWords; i++)
    {
        data[i] = base->READ_FUSE_DATAS[i].READ_FUSE_DATA;
    }
#endif

    return status;
}

/* Write the fuse shadow register. */
status_t OCOTP_WriteFuseShadowRegister(OCOTP_Type *base, uint32_t address, uint32_t data)
{
    return OCOTP_WriteFuseShadowRegisterWithLock(base, address, data, false);
}

status_t OCOTP_WriteFuseShadowRegisterWithLock(OCOTP_Type *base, uint32_t address, uint32_t data, bool lock)
{
    assert(NULL != base);

    status_t status = kStatus_Success;

#if defined(FSL_FEATURE_OCOTP_HAS_STATUS) && FSL_FEATURE_OCOTP_HAS_STATUS
    uint32_t regStatus;
#endif

#if !(defined(FSL_FEATURE_OCOTP_HAS_WORDLOCK) && FSL_FEATURE_OCOTP_HAS_WORDLOCK)
    if (lock)
    {
        return kStatus_InvalidArgument;
    }
#endif

    /* Make sure the OCOTP is ready, Overlapped accesses are not supported by the controller. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* Clear access error status bit. */
    if (OCOTP_CheckErrorStatus(base))
    {
        OCOTP_ClearErrorStatus(base);
    }

#if (defined(FSL_FEATURE_OCOTP_HAS_TIMING_CTRL) && FSL_FEATURE_OCOTP_HAS_TIMING_CTRL)
    /* Set write timing for OCOTP controller. */
    OCOTP_SetWriteTiming(base, s_timingConfig);

    /* Wait for busy bit is cleared. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* Clear access error status bit. */
    if (OCOTP_CheckErrorStatus(base))
    {
        OCOTP_ClearErrorStatus(base);
    }
#endif

#if defined(FSL_FEATURE_OCOTP_HAS_STATUS) && FSL_FEATURE_OCOTP_HAS_STATUS
    /* Clear errors. */
    base->OUT_STATUS0_CLR = (OCOTP_OUT_STATUS0_PROGFAIL_MASK | OCOTP_OUT_STATUS0_LOCKED_MASK);
#endif

    /* Write requested address and unlock key to register. */
#if (defined(FSL_FEATURE_OCOTP_HAS_WORDLOCK) && FSL_FEATURE_OCOTP_HAS_WORDLOCK)
    base->CTRL_CLR = OCOTP_CTRL_CLR_ADDR_MASK | OCOTP_CTRL_WR_UNLOCK_MASK | OCOTP_CTRL_WORDLOCK_MASK;
#else
    base->CTRL_CLR = OCOTP_CTRL_CLR_ADDR_MASK | OCOTP_CTRL_WR_UNLOCK_MASK;
#endif

#if (defined(FSL_FEATURE_OCOTP_HAS_WORDLOCK) && FSL_FEATURE_OCOTP_HAS_WORDLOCK)
    if (lock)
    {
        base->CTRL_SET =
            OCOTP_CTRL_SET_ADDR(address) | OCOTP_CTRL_WR_UNLOCK(OCOTP_WRITE_UNLOCK_KEY) | OCOTP_CTRL_WORDLOCK_MASK;
    }
    else
#endif
    {
        base->CTRL_SET = OCOTP_CTRL_SET_ADDR(address) | OCOTP_CTRL_WR_UNLOCK(OCOTP_WRITE_UNLOCK_KEY);
    }

    /* Write data to register. */
    base->DATA = data;

    /* Wait for busy bit is cleared, and no error occurred on controller. */
    while (OCOTP_CheckBusyStatus(base))
    {
    }

    /* If ERROR bit was set, this may be mean that the accsee to the register was wrong. */
    if (OCOTP_CheckErrorStatus(base))
    {
        /* Clear access error status bit. */
        OCOTP_ClearErrorStatus(base);

        status = kStatus_OCOTP_AccessError;
    }

#if defined(FSL_FEATURE_OCOTP_HAS_STATUS) && FSL_FEATURE_OCOTP_HAS_STATUS
    regStatus = base->OUT_STATUS0;

    if ((regStatus & OCOTP_OUT_STATUS0_PROGFAIL_MASK) != 0U)
    {
        status = kStatus_OCOTP_ProgramFail;
    }
    else if ((regStatus & OCOTP_OUT_STATUS0_LOCKED_MASK) != 0U)
    {
        status = kStatus_OCOTP_Locked;
    }
    else
    {
        /* For MISRA rules. */
    }
#endif

    if (kStatus_Success == status)
    {
        /* Reload the fuse register. */
        status = OCOTP_ReloadShadowRegister(base);
    }

    return status;
}
