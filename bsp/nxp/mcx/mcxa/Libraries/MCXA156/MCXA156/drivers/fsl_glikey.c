/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_glikey.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.glikey"
#endif

#define GLIKEY_SFR_LOCK   0x05u
#define GLIKEY_SFR_UNLOCK 0x0Au

/* Define to select between write to CTRL0_WR_0 or CTRL1_WR_1 */
#define WR_EN0 (0x0Fu)
#define WR_EN1 (0xF0u)

#define WR_EN0_VALUE_SHIFT (0u)
#define WR_EN1_VALUE_SHIFT (16u)

#define CTRL_SEL_CODEWORD_SHIFT (24u)

#define WR_0_INIT (0x2u)
#define WR_1_INIT (0x0u)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static inline void Glikey_Internal_Set_WR_0(GLIKEY_Type *base, uint32_t value);
static inline void Glikey_Internal_Set_WR_1(GLIKEY_Type *base, uint32_t value);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * Weak implementation of GLIKEY IRQ, should be re-defined by user when using GLIKEY IRQ

__WEAK void GLIKEY0_DriverIRQHandler(void)
{
    GLIKEY generates IRQ until corresponding bit in STATUS is cleared by calling
    GLIKEY_ClearStatusFlags();
}
*/

static inline void Glikey_Internal_Set_WR_0(GLIKEY_Type *base, uint32_t value)
{
    uint32_t ctrl0 = ((GLIKEY_Type *)base)->CTRL_0;

    /* Clear WR_0 */
    ctrl0 = ctrl0 & (~GLIKEY_CTRL_0_WR_EN_0_MASK);

    /* Assign value */
    ((GLIKEY_Type *)base)->CTRL_0 = ctrl0 | GLIKEY_CTRL_0_WR_EN_0(value);
}

static inline void Glikey_Internal_Set_WR_1(GLIKEY_Type *base, uint32_t value)
{
    uint32_t ctrl1 = ((GLIKEY_Type *)base)->CTRL_1;

    /* Clear WR_1 */
    ctrl1 = ctrl1 & (~GLIKEY_CTRL_1_WR_EN_1_MASK);

    /* Assign value */
    ((GLIKEY_Type *)base)->CTRL_1 = ctrl1 | GLIKEY_CTRL_1_WR_EN_1(value);
}

uint32_t GLIKEY_GetStatus(GLIKEY_Type *base)
{
    return ((GLIKEY_Type *)base)->STATUS;
}

status_t GLIKEY_IsLocked(GLIKEY_Type *base)
{
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked == retCode)
    {
        return kStatus_GLIKEY_NotLocked;
    }
    else
    {
        return kStatus_GLIKEY_Locked;
    }
}

status_t GLIKEY_CheckLock(GLIKEY_Type *base)
{
    uint32_t sfrLock = (((GLIKEY_Type *)base)->CTRL_1 & GLIKEY_CTRL_1_SFR_LOCK_MASK) >> GLIKEY_CTRL_1_SFR_LOCK_SHIFT;

    if (GLIKEY_SFR_UNLOCK != sfrLock) /* Locked */
    {
        return kStatus_GLIKEY_LockedError;
    }

    return kStatus_GLIKEY_NotLocked;
}

#if defined(GLIKEY_VERSION_FSM_CONFIG)
status_t GLIKEY_GetVersion(GLIKEY_Type *base, uint32_t *result)
{
    *result = ((GLIKEY_Type *)base)->VERSION;

    return kStatus_Success;
}
#endif

status_t GLIKEY_SyncReset(GLIKEY_Type *base)
{
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* Set CTRL_0.SFT_RST = 1 */
    ((GLIKEY_Type *)base)->CTRL_0 |= GLIKEY_CTRL_0_SFT_RST_MASK;

    return kStatus_Success;
}

status_t GLIKEY_SetIntEnable(GLIKEY_Type *base, uint32_t value)
{
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    ((GLIKEY_Type *)base)->INTR_CTRL = GLIKEY_INTR_CTRL_INT_EN(value);

    return kStatus_Success;
}

status_t GLIKEY_GetIntEnable(GLIKEY_Type *base, uint32_t *value)
{
    *value = ((GLIKEY_Type *)base)->INTR_CTRL & GLIKEY_INTR_CTRL_INT_EN_MASK;

    return kStatus_Success;
}

status_t GLIKEY_ClearIntStatus(GLIKEY_Type *base)
{
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    ((GLIKEY_Type *)base)->INTR_CTRL |= GLIKEY_INTR_CTRL_INT_CLR_MASK;

    return kStatus_Success;
}

status_t GLIKEY_SetIntStatus(GLIKEY_Type *base)
{
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    ((GLIKEY_Type *)base)->INTR_CTRL |= GLIKEY_INTR_CTRL_INT_SET_MASK;

    return kStatus_Success;
}

status_t GLIKEY_Lock(GLIKEY_Type *base)
{
    /* Check if SFR_LOCK is locked */
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode) /* Glikey is not locked -> lock */
    {
        uint32_t ctrl1 = ((GLIKEY_Type *)base)->CTRL_1;
        /* Clear SFR_LOCK */
        ctrl1 = ctrl1 & (~GLIKEY_CTRL_1_SFR_LOCK_MASK);
        /* Lock Gliekey */
        ((GLIKEY_Type *)base)->CTRL_1 = ctrl1 | GLIKEY_CTRL_1_SFR_LOCK(GLIKEY_SFR_LOCK);
    }

    return kStatus_Success;
}

status_t GLIKEY_IsIndexLocked(GLIKEY_Type *base, uint32_t index)
{
    /* Set CTRL_1.READ_INDEX = index */
    uint32_t ctr1Val = ((GLIKEY_Type *)base)->CTRL_1;
    /* Clear READ_INDEX */
    ctr1Val = ctr1Val & (~GLIKEY_CTRL_1_READ_INDEX_MASK);
    /* Set index value */
    ((GLIKEY_Type *)base)->CTRL_1 = ctr1Val | GLIKEY_CTRL_1_READ_INDEX(index);

    /* Check ERROR_STATUS */
    if (0u != (GLIKEY_GetStatus(base) & GLIKEY_STATUS_ERROR_STATUS_MASK))
    {
        return kStatus_Fail;
    }

    /* Check if STATUS.LOCK_STATUS is 0 */
    if (0u == (GLIKEY_GetStatus(base) & GLIKEY_STATUS_LOCK_STATUS_MASK))
    {
        return kStatus_GLIKEY_NotLocked;
    }
    else
    {
        return kStatus_GLIKEY_Locked;
    }
}

status_t GLIKEY_LockIndex(GLIKEY_Type *base)
{
    /* Check if Glikey SFR locked */
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* Check if FSM is in WR_EN state */
    uint32_t state = (GLIKEY_GetStatus(base) & GLIKEY_STATUS_FSM_STATE_MASK) >> GLIKEY_STATUS_FSM_STATE_SHIFT;
    if (GLIKEY_FSM_WR_EN == state)
    {
        /* Set WR_EN0 = b11 */
        ((GLIKEY_Type *)base)->CTRL_0 |= GLIKEY_CTRL_0_WR_EN_0(0x3u);
        return kStatus_GLIKEY_Locked;
    }
    else
    {
        return kStatus_GLIKEY_DisabledError;
    }
}

status_t GLIKEY_StartEnable(GLIKEY_Type *base, uint32_t index)
{
    /* Check if Glikey SFR locked */
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* Check if index is locked */
    retCode = GLIKEY_IsIndexLocked(base, index);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* CTRL0 */
    uint32_t ctrl0 = ((GLIKEY_Type *)base)->CTRL_0;
    /* Clear old index */
    ctrl0 = ctrl0 & (~GLIKEY_CTRL_0_WRITE_INDEX_MASK);
    /* Clear old CTRL0.WR_EN_0 */
    ctrl0 = ctrl0 & (~GLIKEY_CTRL_0_WR_EN_0_MASK);
    /* Set new index */
    ctrl0 |= GLIKEY_CTRL_0_WRITE_INDEX(index);

    /* Start the enable process by writting 0x01 to CTRL0.WR_EN_0 */
    ctrl0 = ctrl0 | ((uint32_t)0x01u << GLIKEY_CTRL_0_WR_EN_0_SHIFT);

    /* Write to CTRL0 (new index and WR_EN_0 = 0x01) */
    ((GLIKEY_Type *)base)->CTRL_0 = ctrl0;

    /* CTRL1 */
    uint32_t ctrl1 = ((GLIKEY_Type *)base)->CTRL_1;
    /* Clear CTRL1.WR_EN_1 */
    ctrl1 &= ~GLIKEY_CTRL_1_WR_EN_1_MASK;
    ((GLIKEY_Type*)base)->CTRL_1 = ctrl1;

    return kStatus_Success;
}

status_t GLIKEY_ContinueEnable(GLIKEY_Type *base, uint32_t codeword)
{
    /* Check if Glikey SFR locked */
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* Set correctly we_en0 and wr_en1 according to codeword */
    /* Select between CTRL0/CTRL1 */
    if (WR_EN1 == (codeword >> CTRL_SEL_CODEWORD_SHIFT))
    {
        Glikey_Internal_Set_WR_1(base, codeword >> WR_EN1_VALUE_SHIFT);
    }
    else if (WR_EN0 == (codeword >> CTRL_SEL_CODEWORD_SHIFT))
    {
        Glikey_Internal_Set_WR_0(base, codeword >> WR_EN0_VALUE_SHIFT);
    }
    else
    {
        return kStatus_Fail;
    }

    if (0u != (GLIKEY_GetStatus(base) & GLIKEY_STATUS_ERROR_STATUS_MASK))
    {
        return kStatus_GLIKEY_DisabledError;
    }

    /* Validate codeword - check if XXYZ^UUVW == 0xFFFF */
    if (0xFFFFu != (((codeword) ^ (codeword >> 16u)) & 0xFFFFu))
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}

status_t GLIKEY_EndOperation(GLIKEY_Type *base)
{
    /* Check if Glikey SFR locked */
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    // check state
    uint32_t state = (GLIKEY_GetStatus(base) & GLIKEY_STATUS_FSM_STATE_MASK) >> GLIKEY_STATUS_FSM_STATE_SHIFT;

    switch (state)
    {
        case GLIKEY_FSM_LOCKED:
        {
            /* If locked -> try to go to init with wr_en0 = WR_0_INIT (0x02); wr_en1 = WR_1_INIT (0x00) */
            Glikey_Internal_Set_WR_0(base, WR_0_INIT);
            Glikey_Internal_Set_WR_1(base, WR_1_INIT);

            /* if still locked return locked - need to change index */
            if (GLIKEY_FSM_LOCKED ==
                (GLIKEY_GetStatus(base) & GLIKEY_STATUS_FSM_STATE_MASK) >> GLIKEY_STATUS_FSM_STATE_SHIFT)
            {
                return kStatus_GLIKEY_Locked;
            }

            retCode = kStatus_Success;
            break;
        }

        case GLIKEY_FSM_SSR_RESET:
        case GLIKEY_FSM_WR_EN:
        {
            /* If FSM in RESET -> wr_en0 = WR_0_INIT; wr_en1 = WR_1_INIT */
            /* If FSM in WR_EN -> wr_en0 = WR_0_INIT; wr_en1 = WR_1_INIT */
            Glikey_Internal_Set_WR_0(base, WR_0_INIT);
            Glikey_Internal_Set_WR_1(base, WR_1_INIT);

            retCode = kStatus_Success;
            break;
        }

        default:
            /* Disabled error */
            retCode = kStatus_GLIKEY_DisabledError;
            break;
    }

    return retCode;
}

status_t GLIKEY_ResetIndex(GLIKEY_Type *base, uint32_t index)
{
    /* Check if Glikey SFR locked */
    status_t retCode = GLIKEY_CheckLock(base);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* Check if index is locked */
    retCode = GLIKEY_IsIndexLocked(base, index);
    if (kStatus_GLIKEY_NotLocked != retCode)
    {
        return retCode;
    }

    /* Check if FSM is in INIT state */
    uint32_t state = (GLIKEY_GetStatus(base) & GLIKEY_STATUS_FSM_STATE_MASK) >> GLIKEY_STATUS_FSM_STATE_SHIFT;
    if (GLIKEY_FSM_INIT == state)
    {
        /* CTRL0.WRITE_INDEX = index */
        uint32_t ctrl0 = ((GLIKEY_Type *)base)->CTRL_0;
        /* Clear index */
        ctrl0 = ctrl0 & (~GLIKEY_CTRL_0_WRITE_INDEX_MASK);
        /* Write new value */
        ((GLIKEY_Type *)base)->CTRL_0 = ctrl0 | GLIKEY_CTRL_0_WRITE_INDEX(index);

        return kStatus_Success;
    }
    else
    {
        return kStatus_GLIKEY_DisabledError;
    }
}
