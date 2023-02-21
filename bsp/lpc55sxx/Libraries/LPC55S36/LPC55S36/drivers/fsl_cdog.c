/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_cdog.h"

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.cdog"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Sets the default configuration of CDOG
 *
 * This function initialize CDOG config structure to default values.
 *
 * param conf CDOG configuration structure
 */
void CDOG_GetDefaultConfig(cdog_config_t *conf)
{
    /* Default configuration after reset */
    conf->lock       = (uint8_t)kCDOG_LockCtrl_Unlock;    /* Lock control */
    conf->timeout    = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Timeout control */
    conf->miscompare = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Miscompare control */
    conf->sequence   = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Sequence control */
    conf->state      = (uint8_t)kCDOG_FaultCtrl_NoAction; /* State control */
    conf->address    = (uint8_t)kCDOG_FaultCtrl_NoAction; /* Address control */
    conf->irq_pause  = (uint8_t)kCDOG_IrqPauseCtrl_Run;   /* IRQ pause control */
    conf->debug_halt = (uint8_t)kCDOG_DebugHaltCtrl_Run;  /* Debug halt control */
    return;
}

/*!
 * brief Sets secure counter and instruction timer values
 *
 * This function sets value in RELOAD and START registers for instruction timer.
 *
 * param base CDOG peripheral base address
 * param reload reload value
 * param start start value
 */
void CDOG_Start(CDOG_Type *base, uint32_t reload, uint32_t start)
{
    base->RELOAD = reload;
    base->START  = start;
}

/*!
 * brief Stops secure counter and instruction timer
 *
 * This function stops instruction timer and secure counter.
 * This also change state of CDOG to IDLE.
 *
 * param base CDOG peripheral base address
 * param stop expected value which will be compared with value of secure counter
 */
void CDOG_Stop(CDOG_Type *base, uint32_t stop)
{
    base->STOP = stop;
}

/*!
 * brief Sets secure counter and instruction timer values
 *
 * This function sets value in STOP, RELOAD and START registers
 * for instruction timer and secure counter.
 *
 * param base CDOG peripheral base address
 * param stop expected value which will be compared with value of secure counter
 * param reload reload value for instruction timer
 * param start start value for secure timer
 */
void CDOG_Set(CDOG_Type *base, uint32_t stop, uint32_t reload, uint32_t start)
{
    base->STOP   = stop;
    base->RELOAD = reload;
    base->START  = start;
}

/*!
 * brief Add value to secure counter
 *
 * This function add specified value to secure counter.
 *
 * param base CDOG peripheral base address.
 * param add Value to be added.
 */
void CDOG_Add(CDOG_Type *base, uint32_t add)
{
    base->ADD = (secure_counter_t)add;
}

/*!
 * brief Add 1 to secure counter
 *
 * This function add 1 to secure counter.
 *
 * param base CDOG peripheral base address.
 * param add Value to be added.
 */
void CDOG_Add1(CDOG_Type *base)
{
    base->ADD1 = (secure_counter_t)0x1U;
}

/*!
 * brief Add 16 to secure counter
 *
 * This function add 16 to secure counter.
 *
 * param base CDOG peripheral base address.
 * param add Value to be added.
 */
void CDOG_Add16(CDOG_Type *base)
{
    base->ADD16 = (secure_counter_t)0x1U;
}

/*!
 * brief Add 256 to secure counter
 *
 * This function add 256 to secure counter.
 *
 * param base CDOG peripheral base address.
 * param add Value to be added.
 */
void CDOG_Add256(CDOG_Type *base)
{
    base->ADD256 = (secure_counter_t)0x1U;
}

/*!
 * brief Substract value to secure counter
 *
 * This function substract specified value to secure counter.
 *
 * param base CDOG peripheral base address.
 * param sub Value to be substracted.
 */
void CDOG_Sub(CDOG_Type *base, uint32_t sub)
{
    base->SUB = (secure_counter_t)sub;
}

/*!
 * brief Substract 1 from secure counter
 *
 * This function substract specified 1 from secure counter.
 *
 * param base CDOG peripheral base address.
 */
void CDOG_Sub1(CDOG_Type *base)
{
    base->SUB1 = (secure_counter_t)0x1U;
}

/*!
 * brief Substract 16 from secure counter
 *
 * This function substract specified 16 from secure counter.
 *
 * param base CDOG peripheral base address.
 */
void CDOG_Sub16(CDOG_Type *base)
{
    base->SUB16 = (secure_counter_t)0x1U;
}

/*!
 * brief Substract 256 from secure counter
 *
 * This function substract specified 256 from secure counter.
 *
 * param base CDOG peripheral base address.
 */
void CDOG_Sub256(CDOG_Type *base)
{
    base->SUB256 = (secure_counter_t)0x1U;
}

/*!
 * brief Checks secure counter.
 *
 * This function compares stop value with secure counter value
 * by writting to RELOAD refister.
 *
 * param base CDOG peripheral base address
 * param check expected (stop) value.
 */
void CDOG_Check(CDOG_Type *base, uint32_t check)
{
    base->RESTART = check;
}

/*!
 * brief Set the CDOG persistent word.
 *
 * param base CDOG peripheral base address.
 * param value The value to be written.
 */
void CDOG_WritePersistent(CDOG_Type *base, uint32_t value)
{
    base->PERSISTENT = value;
}

/*!
 * brief Get the CDOG persistent word.
 *
 * param base CDOG peripheral base address.
 * return The persistent word.
 */
uint32_t CDOG_ReadPersistent(CDOG_Type *base)
{
    return base->PERSISTENT;
}

/*!
 * brief Initialize CDOG
 *
 * This function initializes CDOG block and setting.
 *
 * param base CDOG peripheral base address
 * param conf CDOG configuration structure
 * return Status of the init operation
 */
status_t CDOG_Init(CDOG_Type *base, cdog_config_t *conf)
{
    /* Ungate clock to CDOG engine and reset it */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Cdog);
#endif /* !FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_FEATURE_CDOG_HAS_NO_RESET) && FSL_FEATURE_CDOG_HAS_NO_RESET)
    RESET_PeripheralReset(kCDOG_RST_SHIFT_RSTn);
#endif /* !FSL_FEATURE_CDOG_HAS_NO_RESET */

    if (base->CONTROL == 0x0U)
    {
        /* CDOG is not in IDLE mode, which may be cause after SW reset. */
        /* Writing to CONTROL register will trigger fault. */
        return kStatus_Fail;
    }

    /* Clear pending errors, otherwise the device will reset */
    /* itself immediately after enable Code Watchdog */
    if ((uint32_t)kCDOG_LockCtrl_Lock ==
        ((base->CONTROL & CDOG_CONTROL_LOCK_CTRL_MASK) >> CDOG_CONTROL_LOCK_CTRL_SHIFT))

    {
        CDOG->FLAGS = CDOG_FLAGS_TO_FLAG(1U) | CDOG_FLAGS_MISCOM_FLAG(1U) | CDOG_FLAGS_SEQ_FLAG(1U) |
                      CDOG_FLAGS_CNT_FLAG(1U) | CDOG_FLAGS_STATE_FLAG(1U) | CDOG_FLAGS_ADDR_FLAG(1U) |
                      CDOG_FLAGS_POR_FLAG(1U);
    }
    else
    {
        CDOG->FLAGS = CDOG_FLAGS_TO_FLAG(0U) | CDOG_FLAGS_MISCOM_FLAG(0U) | CDOG_FLAGS_SEQ_FLAG(0U) |
                      CDOG_FLAGS_CNT_FLAG(0U) | CDOG_FLAGS_STATE_FLAG(0U) | CDOG_FLAGS_ADDR_FLAG(0U) |
                      CDOG_FLAGS_POR_FLAG(0U);
    }

    base->CONTROL =
        CDOG_CONTROL_TIMEOUT_CTRL(conf->timeout) |       /* Action if the timeout event is triggered  */
        CDOG_CONTROL_MISCOMPARE_CTRL(conf->miscompare) | /* Action if the miscompare error event is triggered  */
        CDOG_CONTROL_SEQUENCE_CTRL(conf->sequence) |     /* Action if the sequence error event is triggered  */
        CDOG_CONTROL_STATE_CTRL(conf->state) |           /* Action if the state error event is triggered  */
        CDOG_CONTROL_ADDRESS_CTRL(conf->address) |       /* Action if the address error event is triggered */
        CDOG_CONTROL_IRQ_PAUSE(conf->irq_pause) |        /* Pause running during interrupts setup */
        CDOG_CONTROL_DEBUG_HALT_CTRL(
            conf->debug_halt) |             /* Halt CDOG timer during debug so we have chance to debug code */
        CDOG_CONTROL_LOCK_CTRL(conf->lock); /* Lock control register */

    NVIC_EnableIRQ(CDOG_IRQn);

    return kStatus_Success;
}

/*!
 * brief Deinitialize CDOG
 *
 * This function stops CDOG secure counter.
 *
 * param base CDOG peripheral base address
 */
void CDOG_Deinit(CDOG_Type *base)
{
    NVIC_DisableIRQ(CDOG_IRQn);

#if !(defined(FSL_FEATURE_CDOG_HAS_NO_RESET) && FSL_FEATURE_CDOG_HAS_NO_RESET)
    RESET_SetPeripheralReset(kCDOG_RST_SHIFT_RSTn);
#endif /* !FSL_FEATURE_CDOG_HAS_NO_RESET */

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Cdog);
#endif /* !FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
