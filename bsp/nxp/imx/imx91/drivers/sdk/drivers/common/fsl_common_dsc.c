/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.common_dsc"
#endif

#define COMMON_INTC_TYPE_REG_INDEX(x) (((uint8_t)(x)) >> 3U)
#define COMMON_INTC_TYPE_BIT_INDEX(x) ((((uint8_t)(x)) & 0x7U) << 1U)

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Interrupt priority table. */
static uint16_t s_intPrioTable[(NUMBER_OF_INT_IRQ - 1U) / 8U + 1U] = {0U};

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t EnableIRQWithPriority(IRQn_Type irq, uint8_t priNum)
{
    uint8_t regIndex;
    uint8_t bitIndex;
    uint16_t prioMask;
    uint16_t reg;
    uint16_t intcCtrl;

    regIndex = COMMON_INTC_TYPE_REG_INDEX(irq);
    bitIndex = COMMON_INTC_TYPE_BIT_INDEX(irq);
    prioMask = ((uint16_t)3U << bitIndex);
    /* Valid priority number is 0-3 */
    priNum = priNum & 0x03U;

    if (0U == priNum)
    {
        priNum = SDK_DSC_DEFAULT_INT_PRIO;
    }

    /* Disable global interrupt for atomic change. */
    intcCtrl   = INTC->CTRL;
    INTC->CTRL = intcCtrl | INTC_CTRL_INT_DIS_MASK;

    /* Save the priority in s_intPrioTable */
    reg = s_intPrioTable[regIndex];
    reg = (reg & ~prioMask) | (priNum << bitIndex);

    s_intPrioTable[regIndex] = reg;

    /* Set new priority in interrupt controller register. */
    reg = ((volatile uint16_t *)&(INTC->IPR0))[regIndex];
    reg = (reg & ~prioMask) | (priNum << bitIndex);

    ((volatile uint16_t *)&(INTC->IPR0))[regIndex] = reg;

    INTC->CTRL = intcCtrl;

    return kStatus_Success;
}

status_t DisableIRQ(IRQn_Type irq)
{
    uint8_t regIndex;
    uint8_t bitIndex;
    uint16_t reg;
    uint16_t intcCtrl;

    regIndex = COMMON_INTC_TYPE_REG_INDEX(irq);
    bitIndex = COMMON_INTC_TYPE_BIT_INDEX(irq);

    /* Disable global interrupt for atomic change. */
    intcCtrl   = INTC->CTRL;
    INTC->CTRL = intcCtrl | INTC_CTRL_INT_DIS_MASK;

    reg = ((volatile uint16_t *)&(INTC->IPR0))[regIndex];
    reg = reg & (~((uint16_t)3U << bitIndex));

    ((volatile uint16_t *)&(INTC->IPR0))[regIndex] = reg;

    INTC->CTRL = intcCtrl;

    return kStatus_Success;
}

status_t EnableIRQ(IRQn_Type irq)
{
    uint8_t regIndex;
    uint8_t bitIndex;
    uint16_t prioMask;
    uint16_t reg;
    uint16_t intcCtrl;

    regIndex = COMMON_INTC_TYPE_REG_INDEX(irq);
    bitIndex = COMMON_INTC_TYPE_BIT_INDEX(irq);
    prioMask = ((uint16_t)3U << bitIndex);

    /* Disable global interrupt for atomic change. */
    intcCtrl   = INTC->CTRL;
    INTC->CTRL = intcCtrl | INTC_CTRL_INT_DIS_MASK;

    /* If priority in s_intPrioTable is 0, use SDK_DSC_DEFAULT_INT_PRIO. */
    if (0U == (s_intPrioTable[regIndex] & prioMask))
    {
        s_intPrioTable[regIndex] = (s_intPrioTable[regIndex] & ~prioMask) | (SDK_DSC_DEFAULT_INT_PRIO << bitIndex);
    }

    /* Set the interrupt priority with the priority in s_intPrioTable. */
    reg = ((volatile uint16_t *)&(INTC->IPR0))[regIndex];
    reg = (reg & ~prioMask) | (s_intPrioTable[regIndex] & prioMask);

    ((volatile uint16_t *)&(INTC->IPR0))[regIndex] = reg;

    INTC->CTRL = intcCtrl;

    return kStatus_Success;
}

/*
 * brief Set the IRQ priority.
 *
 * note The parameter priNum is range in 1~3, and its value is **NOT**
 * directly map to interrupt priority.
 *
 * - Some IPs maps 1 to priority 1, 2 to priority 2, 3 to priority 3
 * - Some IPs maps 1 to priority 0, 2 to priority 1, 3 to priority 2
 *
 * User should check chip's RM to get its corresponding interrupt priority
 */
status_t IRQ_SetPriority(IRQn_Type irq, uint8_t priNum)
{
    /*
     * If the interrupt is already enabled, the new priority will be set
     * to the register. If interrupt is not enabled, the new priority is
     * only saved in priority table s_intPrioTable, when interrupt enabled,
     * the priority value is set to register.
     */
    uint8_t regIndex;
    uint8_t bitIndex;
    uint16_t prioMask;
    uint16_t reg;
    uint16_t intcCtrl;

    regIndex = COMMON_INTC_TYPE_REG_INDEX(irq);
    bitIndex = COMMON_INTC_TYPE_BIT_INDEX(irq);
    prioMask = ((uint16_t)3U << bitIndex);

    /* Valid priority number is 0-3 */
    priNum = priNum & 0x03U;

    if (0U == priNum)
    {
        priNum = SDK_DSC_DEFAULT_INT_PRIO;
    }

    /* Disable global interrupt for atomic change. */
    intcCtrl   = INTC->CTRL;
    INTC->CTRL = intcCtrl | INTC_CTRL_INT_DIS_MASK;

    /* Save the priority in s_intPrioTable */
    reg = s_intPrioTable[regIndex];
    reg = (reg & ~prioMask) | (priNum << bitIndex);

    s_intPrioTable[regIndex] = reg;

    /*
     * If interrupt already enabled, set new priority
     * in interrupt controller register.
     */
    reg = ((volatile uint16_t *)&(INTC->IPR0))[regIndex];

    if (0U != (reg & prioMask))
    {
        reg = (reg & (~prioMask)) | (priNum << bitIndex);

        ((volatile uint16_t *)&(INTC->IPR0))[regIndex] = reg;
    }

    INTC->CTRL = intcCtrl;

    return kStatus_Success;
}

/*!
 * brief Delay core cycles.
 *  Please note that, this API uses software loop for delay, the actual delayed
 *  time depends on core clock frequency, where the function is located (ram or flash),
 *  flash clock, possible interrupt.
 *
 * param u32Num  Number of core clock cycle which needs to be delayed.
 */
void SDK_DelayCoreCycles(uint32_t u32Num)
{
    /*
     *  if(u32Num < 22)
     *  {
     *      ActualDelayCycle = 21;
     *  }
     *  else
     *  {
     *      ActualDelayCycle = 35 + ((u32Num-22)/8) * 8 = 13 + u32Num - ((u32Num-22)%8)
     *  }
     */

    /*  JSR - 4 cycles
     *  RTS - 8 cycles
     */

    asm {
       cmp.l #21,A // 2 cycle
       bls   ret // 5 cycles when jump occurs. 3 cycles when jump doesn't occur
       nop // 1 cycle
       nop // 1 cycle
       sub.l  #22, A // 2 cycle
       asrr.l #3, A // 2 cycle
       bra   test // 5 cycle

       loop:
       dec.l A // 1 cycle

       test:
       tst.l A // 1 cycle
       nop // 1 cycle
       bne   loop // 5 cycles when jump occurs. 3 cycles when jump doesn't occur

       ret:
       nop // 1 cycle
       nop // 1 cycle
    }
}

/*!
 * brief Delay at least for some time.
 *  Please note that, this API uses while loop for delay, different run-time environments make the time not precise,
 *  if precise delay count was needed, please implement a new delay function with hardware timer.
 *
 * param delayTime_us Delay time in unit of microsecond.
 * param coreClock_Hz  Core clock frequency with Hz.
 */
void SDK_DelayAtLeastUs(uint32_t delayTime_us, uint32_t coreClock_Hz)
{
    while(delayTime_us > 0)
    {
        uint32_t us, count;

        /* USEC_TO_COUNT(fixed-point) supports maximum 4294us, use 4000UL here */
        if(delayTime_us > 4000UL)
        {
            us = 4000UL;
        }
        else
        {
            us = delayTime_us;
        }
        delayTime_us -= us;

        count = USEC_TO_COUNT(us, coreClock_Hz);
        SDK_DelayCoreCycles(count);
    }
}

/*!
 * brief Covert us to count with fixed-point calculation.
 *
 * note u32Us must not be greater than 4294
 *
 * param u32Us Time in us
 * param u32Hz Clock frequency in Hz
 * return The count value
 */
uint32_t SDK_CovertUsToCount(uint32_t u32Us, uint32_t u32Hz)
{
    /*
     * Hz * us / 1000000UL = (Hz / 1000000UL) * us
     * = (i + r/1000000UL) * us
     * = i * us + r * us / 1000000UL
     */

    assert(u32Us <= 4294UL);
    assert(u32Hz != 0U);

    uint32_t i, r;

    i = u32Hz / 1000000UL;
    r = u32Hz - i * 1000000UL;

    return i * u32Us + (r * u32Us / 1000000UL);
}

/*!
 * brief Covert count to us with fixed-point calculation.
 *
 * note u32Hz must not be greater than 429496729UL(0xFFFFFFFFUL/10UL)
 *
 * param u32Count Count value
 * param u32Hz Clock frequency in Hz
 * return The us value
 */
uint32_t SDK_CovertCountToUs(uint32_t u32Count, uint32_t u32Hz)
{
    /*
     *  count * 1000000UL / hz
     *
     *  i1 = count / hz
     *  r1 = count - i1 * hz
     *  sum = i1 * 1000000UL
     *
     *  count = r1 * 10UL
     *  i2 = count / hz
     *  r2 = count - i2 * hz
     *  sum += i2 * 100000UL
     *
     *  count = r2 * 10UL
     *  i3 = count / hz
     *  r3 = count - i3 * hz
     *  sum += i3 * 10000UL;
     *
     *  count = r3 * 10UL
     *  i4 = count / hz
     *  r4 = count - i4 * hz
     *  sum += i4 * 1000UL;
     *
     *  count = r4 * 10UL
     *  i5 = count / hz
     *  r5 = count - i5 * hz
     *  sum += i5 * 100UL;
     *
     *  count = r5 * 10UL
     *  i6 = count / hz
     *  r6 = count - i6 * hz
     *  sum += i6 * 10UL;
     *
     *  count = r6 * 10UL
     *  i7 = count / hz
     *  r7 = count - i7 * hz
     *  sum += i7 * 1UL;
     *
     */
    assert(u32Hz != 0U);
    assert(u32Hz <= 429496729UL);

    uint32_t j;

    uint32_t i, r, sum = 0UL, c = 1UL;

    for (j = 0U; j < 7U; j++)
    {
        i = u32Count / u32Hz;
        r = u32Count - i * u32Hz;
        sum += i * 1000000UL / c;

        c *= 10UL;
        u32Count = r * 10UL;
    }

    return sum;
}

/*!
 * brief Covert ms to count with fixed-point calculation.
 *
 * note u32Ms must not be greater than 42949UL @ u32Hz = 100M
 *
 * param u32Ms Time in us
 * param u32Hz Clock frequency in Hz
 * return The count value
 */
uint32_t SDK_CovertMsToCount(uint32_t u32Ms, uint32_t u32Hz)
{
    /*
     * Hz * ms / 1000UL = (Hz / 1000UL) * ms
     * = (i + r/1000UL) * ms
     * = i * ms + r * ms / 1000UL
     */

    assert(u32Ms <= 42949UL);
    assert(u32Hz != 0U);

    uint32_t i, r;

    i = u32Hz / 1000UL;
    r = u32Hz - i * 1000UL;

    return i * u32Ms + (r * u32Ms / 1000UL);
}

/*!
 * brief Covert count to ms with fixed-point calculation.
 *
 * note u32Hz must not be greater than 429496729UL(0xFFFFFFFFUL/10UL)
 *
 * param u32Count Count value
 * param u32Hz Clock frequency in Hz
 * return The us value
 */
uint32_t SDK_CovertCountToMs(uint32_t u32Count, uint32_t u32Hz)
{
    /*
     *  count * 1000UL / hz
     *
     *  i1 = count / hz
     *  r1 = count - i1 * hz	 *
     *  sum = i1 * 1000UL
     *
     *  count = r1 * 10UL
     *  i2 = count / hz
     *  r2 = count - i2 * hz
     *  sum += i2 * 100UL
     *
     *  count = r2 * 10UL
     *  i3 = count / hz
     *  r3 = count - i3 * hz
     *  sum += i3 * 10L;
     *
     *  count = r3 * 10UL
     *  i4 = count / hz
     *  r4 = count - i4 * hz
     *  sum += i4 * 1UL;
     *
     */
    assert(u32Hz != 0U);
    assert(u32Hz <= 429496729UL);

    uint32_t j;

    uint32_t i, r, sum = 0UL, c = 1UL;

    for (j = 0U; j < 4U; j++)
    {
        i = u32Count / u32Hz;
        r = u32Count - i * u32Hz;
        sum += i * 1000UL / c;

        c *= 10UL;
        u32Count = r * 10UL;
    }

    return sum;
}

/*!
 * brief Delay at least for some time in millisecond unit.
 *  Please note that, this API uses while loop for delay, different run-time environments make the time not precise,
 *  if precise delay count was needed, please implement a new delay function with hardware timer.
 *
 * param delayTime_ms Delay time in unit of millisecond.
 * param coreClock_Hz  Core clock frequency with Hz.
 */
void SDK_DelayAtLeastMs(uint32_t delayTime_ms, uint32_t coreClock_Hz)
{
    while(delayTime_ms > 0)
    {
        uint32_t ms, count;

        /* MSEC_TO_COUNT(fixed-point) supports maximum 42949ms @ 100MHz, use 1000UL here */
        if(delayTime_ms > 1000UL)
        {
            ms = 1000UL;
        }
        else
        {
            ms = delayTime_ms;
        }
        delayTime_ms -= ms;

        count = MSEC_TO_COUNT(ms, coreClock_Hz);
        SDK_DelayCoreCycles(count);
    }
}
