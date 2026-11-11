/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_COMMON_DSC_H_
#define FSL_COMMON_DSC_H_

#include "fsl_device_registers.h"
#include "Cpu.h"

/*!
 * @addtogroup ksdk_common
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#ifndef bool
typedef uint8_t bool;
#define true 1
#define false 0
#endif

/*! @name Timer utilities */
/*! @{ */
#if FSL_FEATURE_SOC_HAS_FPU
/*! Macro to convert a microsecond period to raw count value */
#define USEC_TO_COUNT(us, clockFreqInHz) ((float)clockFreqInHz * ((float))us / 1000000UL)
/*! Macro to convert a raw count value to microsecond */
#define COUNT_TO_USEC(count, clockFreqInHz) ((float)count * 1000000UL / (float)clockFreqInHz)
/*! Macro to convert a millisecond period to raw count value */
#define MSEC_TO_COUNT(ms, clockFreqInHz) ((float)clockFreqInHz * ((float))ms / 1000UL)
/*! Macro to convert a raw count value to millisecond */
#define COUNT_TO_MSEC(count, clockFreqInHz) ((float)count * 1000UL / (float)clockFreqInHz)

#else
/*! Macro to convert a microsecond period to raw count value */
/* To avoid overflow, us is maximum to 4294us */
#define USEC_TO_COUNT(us, clockFreqInHz) SDK_CovertUsToCount(us, clockFreqInHz)
/*! Macro to convert a raw count value to microsecond */
#define COUNT_TO_USEC(count, clockFreqInHz) SDK_CovertCountToUs(count, clockFreqInHz)
/*! Macro to convert a millisecond period to raw count value */
/* To avoid overflow, ms is maximum to 42949ms @ clockFreqInHz = 100MHz */
#define MSEC_TO_COUNT(ms, clockFreqInHz) SDK_CovertMsToCount(ms, clockFreqInHz)
/*! Macro to convert a raw count value to millisecond */
#define COUNT_TO_MSEC(count, clockFreqInHz) SDK_CovertCountToMs(count, clockFreqInHz)
#endif
/*! @} */

#define SDK_ISR_EXIT_BARRIER

/*! @name Alignment variable definition macros */
/*! @{ */
/*! Macro to define a variable with alignbytes alignment */
#define SDK_ALIGN(var, alignbytes) var __attribute__((aligned(alignbytes)))

#define AT_NONCACHEABLE_SECTION(var)                        var
#define AT_NONCACHEABLE_SECTION_ALIGN(var, alignbytes)      var __attribute__((aligned(alignbytes)))
#define AT_NONCACHEABLE_SECTION_INIT(var)                   var
#define AT_NONCACHEABLE_SECTION_ALIGN_INIT(var, alignbytes) var __attribute__((aligned(alignbytes)))
/*! @} */

/*! @brief Default DSC interrupt priority number. */
#define SDK_DSC_DEFAULT_INT_PRIO 1U

/*! @brief Set base core IRQ priority, that core will response the interrupt request with priority >= base IRQ priority.
 */
#define SetIRQBasePriority(x) __EI##x()

/*!
 * @brief Read register value.
 *
 * Example:
 *    val = PeriphReadReg(OCCS->OSCTL2);
 *
 * @param reg Register name.
 *
 * @return The value of register.
 */
#define PeriphReadReg(reg) (reg)

/*!
 * @brief Write data to register.
 *
 * Example:
 *    PeriphWriteReg(OCCS->OSCTL2, 0x278U);
 *
 * @param reg Register name.
 * @param data Data wrote to register.
 */
#define PeriphWriteReg(reg, data) (reg) = (data)

/*!
 * @brief Set specified bits in register.
 *
 * Example:
 *    PeriphSetBits(OCCS->OSCTL2, 0x12U);
 *
 * @param reg Register name.
 * @param bitMask Bits mask, set bits will be set in the register.
 */
#define PeriphSetBits(reg, bitMask) (reg) |= (bitMask)

/*!
 * @brief Clear specified bits in register.
 *
 * Example:
 *    PeriphClearBits(OCCS->OSCTL2, 0x12U);
 *
 * @param reg Register name.
 * @param bitMask Bits mask, set bits will be cleared in the register.
 */
#define PeriphClearBits(reg, bitMask) (reg) &= (~(bitMask))

/*!
 * @brief Invert specified bits in register.
 *
 * Example:
 *    PeriphInvertBits(OCCS->OSCTL2, 0x12U);
 *
 * @param reg Register name.
 * @param bitMask Bits mask, set bits will be inverted in the register.
 */
#define PeriphInvertBits(reg, bitMask) (reg) ^= (bitMask)

/*!
 * @brief Get specified bits in register.
 *
 * Example:
 *    val = PeriphGetBits(OCCS->OSCTL2, 0x23U);
 *
 * @param reg Register name.
 * @param bitMask Bits mask, specify the getting bits.
 *
 * @return The value of specified bits.
 */
#define PeriphGetBits(reg, bitMask) ((reg) & (bitMask))

/*!
 * @brief Write group of bits to register.
 *
 * Example:
 *    PeriphWriteBitGroup(OCCS->DIVBY, OCCS_DIVBY_COD_MASK, OCCS_DIVBY_COD(23U));
 *    PeriphWriteBitGroup(OCCS->DIVBY, OCCS_DIVBY_COD_MASK | OCCS_DIVBY_PLLDB_MASK, \
 *        OCCS_DIVBY_COD(23U) | OCCS_DIVBY_PLLDB(49U));
 *
 * @param reg Register name.
 * @param bitMask Bits mask, mask of the group of bits.
 * @param bitValue This value will be written into the bit group specified by parameter bitMask.
 */
#define PeriphWriteBitGroup(reg, bitMask, bitValue) (reg) = ((reg) & ~(bitMask)) | ((bitValue) & (bitMask))

/*!
 * @brief Clear (acknowledge) flags which are active-high and are cleared-by-write-one.
 *
 * This macro is useful when a register is comprised by normal read-write bits and cleared-by-write-one bits.
 * Example:
 *    PeriphSafeClearFlags(PWMA->FAULT[0].FSTS, PWM_FSTS_FFLAG_MASK, PWM_FSTS_FFLAG(2));
 *
 * @param reg Register name.
 * @param allFlagsMask Mask for all flags which are active-high and are cleared-by-write-one.
 * @param flagMask The selected flags(cleared-by-write-one) which are supposed to be cleared.
 */
#define PeriphSafeClearFlags(reg, allFlagsMask, flagMask) \
    (reg) = ((reg) & (~(allFlagsMask))) | ((flagMask) & (allFlagsMask))

/*!
 * @brief  Clear selected bits without modifying (acknowledge) bit flags which are active-high and are
 * cleared-by-write-one.
 *
 * This macro is useful when a register is comprised by normal read-write bits and cleared-by-write-one bits.
 * Example:
 *    PeriphSafeClearBits(PWMA->FAULT[0].FSTS, PWM_FSTS_FFLAG_MASK, PWM_FSTS_FHALF(2));
 *
 * @param reg Register name.
 * @param allFlagsMask Mask for all flags which are active-high and are cleared-by-write-one.
 * @param bitMask The selected bits which are supposed to be cleared.
 */
#define PeriphSafeClearBits(reg, allFlagsMask, bitMask) (reg) = ((reg) & (~((allFlagsMask) | (bitMask))))

/*!
 * @brief  Set selected bits without modifying (acknowledge) bit flags which are active-high and are
 * cleared-by-write-one.
 *
 * This macro is useful when a register is comprised by normal read-write bits and cleared-by-write-one bits.
 * Example:
 *    PeriphSafeSetBits(PWMA->FAULT[0].FSTS, PWM_FSTS_FFLAG_MASK, PWM_FSTS_FHALF(2));
 *
 * @param reg Register name.
 * @param allFlagsMask Mask for all flags which are active-high and are cleared-by-write-one.
 * @param bitMask The selected bits which are supposed to be set.
 */
#define PeriphSafeSetBits(reg, allFlagsMask, bitMask) \
    (reg) = ((reg) & (~(allFlagsMask))) | ((bitMask) & (~(allFlagsMask)))

/*!
 * @brief  Write group of bits without modifying (acknowledge) bit flags which are active-high and are
 * cleared-by-write-one.
 *
 * This macro is useful when a register is comprised by normal read-write bits and cleared-by-write-one bits.
 * Example:
 *    PeriphSafeWriteBitGroup(PWMA->FAULT[0].FSTS, PWM_FSTS_FFLAG_MASK, PWM_FSTS_FHALF_MASK, PWM_FSTS_FHALF(3U));
 *    PeriphSafeWriteBitGroup(PWMA->FAULT[0].FSTS, PWM_FSTS_FFLAG_MASK, PWM_FSTS_FHALF_MASK | PWM_FSTS_FFULL_MASK, \
 *        PWM_FSTS_FHALF(3U) | PWM_FSTS_FFULL(2U));
 *
 * @param reg Register name.
 * @param allFlagsMask Mask for all flags which are active-high and are cleared-by-write-one.
 * @param bitMask Bits mask, mask of the group of bits.
 * @param bitValue This value will be written into the bit group specified by parameter bitMask.
 */
#define PeriphSafeWriteBitGroup(reg, allFlagsMask, bitMask, bitValue) \
    (reg) = ((reg) & (~((allFlagsMask) | (bitMask)))) | ((bitValue) & (bitMask) & (~(allFlagsMask)))

/*!
 * @brief  Get IP register byte address with uint32_t type.
 *
 * This macro is useful when a register byte address is required, especially in SDM mode.
 * Example:
 *    SDK_GET_REGISTER_BYTE_ADDR(ADC_Type, ADC, RSLT[0]);
 *
 * @param ipType IP register mapping struct type.
 * @param ipBase IP instance base pointer, WORD address.
 * @param regName Member register name of IP register mapping struct.
 */
#define SDK_GET_REGISTER_BYTE_ADDR(ipType, ipBase, regName) \
    ((2UL * ((uint32_t)(ipBase))) + ((uint32_t)(uint8_t *)&(((ipType *)0)->regName)))

/* Macros for compatibility. */
#define MSDK_REG_SECURE_ADDR(x) (x)
#define MSDK_REG_NONSECURE_ADDR(x) (x)

/*
 * The fsl_clock.h is included here because it needs MAKE_VERSION/MAKE_STATUS/status_t.
 */
#include "fsl_clock.h"

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Disable the global IRQ
 */
static inline uint32_t DisableGlobalIRQ(void)
{
    uint32_t ret;
    if ((INTC->CTRL & INTC_CTRL_INT_DIS_MASK) != 0U)
    {
        ret = 0U;
    }
    else
    {
        INTC->CTRL |= INTC_CTRL_INT_DIS_MASK;
        ret = 1U;
    }
    return ret;
}

/*!
 * @brief Enable the global IRQ
 */
static inline void EnableGlobalIRQ(uint32_t irqSts)
{
    if (irqSts != 0U)
    {
        INTC->CTRL &= ~INTC_CTRL_INT_DIS_MASK;
    }
    else
    {
        INTC->CTRL |= INTC_CTRL_INT_DIS_MASK;
    }
}

/*!
 * @brief Check if currently core is able to response IRQ
 */
static inline bool isIRQAllowed(void)
{
    bool ret = true;
    uint16_t srReg;

    if (0U != (INTC->CTRL | INTC_CTRL_INT_DIS_MASK))
    {
        ret = false;
    }

    asm {move.w SR, srReg}
    ;
    if (0U != (srReg & 0x300U))
    {
        ret = false;
    }
    return ret;
}

/*!
 * @name Interrupt
 *
 * DSC interrupt controller uses the same bit-filed to control interrupt enable
 * status and priority, to provide compatible APIs, SDK uses a interrupt priority
 * table, thus application could control the interrupt
 * enable/disable, and interrupt priority independently. Also, the API
 * @ref EnableIRQWithPriority could be used to enable the interrupt and set the priority
 * at the same time.
 *
 * API implementation:
 *
 * 1. When calling @ref EnableIRQ, if the interrupt priority in priority table is
 * valid, then set the interrupt priority level to the value in priority table
 * If interrupt priority in priority table is invalid, then set the interrupt
 * priority level to @ref SDK_DSC_DEFAULT_INT_PRIO.
 *
 * 2. When calling @ref IRQ_SetPriority, if the interrupt is already enabled, new
 * priority is set to interrupt controller, meanwhile the priority table is
 * updated accordingly. If the interrupt is not enabled, new priority value is
 * saved to priority table , and takes effect when calling @ref EnableIRQ.
 *
 * The interrupt functions configure INTC module, application could call the
 * INTC driver directly for the same purpose.
 *
 * @{
 */

/*!
 * @brief Enable the IRQ, and also set the interrupt priority.
 *
 * @note The parameter @p priNum is range in 1~3, and its value is **NOT**
 * directly map to interrupt priority.
 *
 * - Some IPs maps 1 to priority 1, 2 to priority 2, 3 to priority 3
 * - Some IPs maps 1 to priority 0, 2 to priority 1, 3 to priority 2
 *
 * User should check chip's RM to get its corresponding interrupt priority.
 *
 * When @p priNum set as 0, then @ref SDK_DSC_DEFAULT_INT_PRIO is set instead.
 * When @p priNum set as number larger than 3, then only the 2 LSB take effect,
 * for example, setting @p priNum to 5 is the same with setting it to 1.
 *
 * This function configures INTC module, application could call the
 * INTC driver directly for the same purpose.
 *
 * @param irq The IRQ to enable.
 * @param priNum Priority number set to interrupt controller register.
 * Larger number means higher priority.
 * The allowed range is 1~3, and its value is **NOT** directly map to interrupt priority.
 * In other words, the same priority number means different interrupt priority levels
 * for different IRQ, please check reference manual for the relationship.
 * When pass in 0, then @ref SDK_DSC_DEFAULT_INT_PRIO is set to priority register.
 *
 * @return Currently only returns kStatus_Success, will enhance in the future.
 */
status_t EnableIRQWithPriority(IRQn_Type irq, uint8_t priNum);

/*!
 * @brief Disable specific interrupt.
 *
 * This function configures INTC module, application could call the
 * INTC driver directly for the same purpose.
 *
 * @param irq The IRQ to disable.
 *
 * @return Currently only returns kStatus_Success, will enhance in the future.
 */
status_t DisableIRQ(IRQn_Type irq);

/*!
 * @brief Enable specific interrupt.
 *
 * The recommended workflow is calling @ref IRQ_SetPriority first, then call
 * @ref EnableIRQ. If @ref IRQ_SetPriority is not called first, then the interrupt
 * is enabled with default priority value @ref SDK_DSC_DEFAULT_INT_PRIO.
 *
 * Another recommended workflow is calling @ref EnableIRQWithPriority directly,
 * it is the same with calling @ref IRQ_SetPriority + @ref EnableIRQ.
 *
 * This function configures INTC module, application could call the
 * INTC driver directly for the same purpose.
 *
 * @param irq The IRQ to enable.
 *
 * @return Currently only returns kStatus_Success, will enhance in the future.
 */
status_t EnableIRQ(IRQn_Type irq);

/*!
 * @brief Set the IRQ priority.
 *
 * @note The parameter @p priNum is range in 1~3, and its value is **NOT**
 * directly map to interrupt priority.
 *
 * - Some IPs maps 1 to priority 1, 2 to priority 2, 3 to priority 3
 * - Some IPs maps 1 to priority 0, 2 to priority 1, 3 to priority 2
 *
 * User should check chip's RM to get its corresponding interrupt priority
 *
 * When @p priNum set as 0, then @ref SDK_DSC_DEFAULT_INT_PRIO is set instead.
 * When @p priNum set as number larger than 3, then only the 2 LSB take effect,
 * for example, setting @p priNum to 5 is the same with setting it to 1.
 *
 * This function configures INTC module, application could call the
 * INTC driver directly for the same purpose.
 *
 * @param irq The IRQ to set.
 * @param priNum Priority number set to interrupt controller register.
 * Larger number means higher priority, 0 means disable the interrupt.
 * The allowed range is 0~3, and its value is **NOT** directly map to interrupt priority.
 * In other words, the same priority number means different interrupt priority levels
 * for different IRQ, please check reference manual for the relationship.
 *
 * @return Currently only returns kStatus_Success, will enhance in the future.
 */
status_t IRQ_SetPriority(IRQn_Type irq, uint8_t priNum);

/*! @} */

/*!
 * @brief Delay core cycles.
 *  Please note that, this API uses software loop for delay, the actual delayed
 *  time depends on core clock frequency, where the function is located (ram or flash),
 *  flash clock, possible interrupt.
 *
 * @param u32Num  Number of core clock cycle which needs to be delayed.
 */
void SDK_DelayCoreCycles(uint32_t u32Num);

/*!
 * @brief Covert us to count with fixed-point calculation.
 *
 * @note u32Us must not be greater than 4294
 *
 * @param u32Us Time in us
 * @param u32Hz Clock frequency in Hz
 * @return The count value
 */
uint32_t SDK_CovertUsToCount(uint32_t u32Us, uint32_t u32Hz);

/*!
 * @brief Covert count to us with fixed-point calculation.
 *
 * @note u32Hz must not be greater than 429496729UL(0xFFFFFFFFUL/10UL)
 *
 * @param u32Count Count value
 * @param u32Hz Clock frequency in Hz
 * @return The us value
 */
uint32_t SDK_CovertCountToUs(uint32_t u32Count, uint32_t u32Hz);

/*!
 * @brief Covert ms to count with fixed-point calculation.
 *
 * @note u32Ms must not be greater than 42949UL @ u32Hz = 100M
 *
 * @param u32Ms Time in us
 * @param u32Hz Clock frequency in Hz
 * @return The count value
 */
uint32_t SDK_CovertMsToCount(uint32_t u32Ms, uint32_t u32Hz);

/*!
 * @brief Covert count to ms with fixed-point calculation.
 *
 * @note u32Hz must not be greater than 429496729UL(0xFFFFFFFFUL/10UL)
 *
 * @param u32Count Count value
 * @param u32Hz Clock frequency in Hz
 * @return The us value
 */
uint32_t SDK_CovertCountToMs(uint32_t u32Count, uint32_t u32Hz);

/*!
 * @brief Delay at least for some time in millisecond unit.
 *  Please note that, this API uses while loop for delay, different run-time environments make the time not precise,
 *  if precise delay count was needed, please implement a new delay function with hardware timer.
 *
 * @param delayTime_ms Delay time in unit of millisecond.
 * @param coreClock_Hz  Core clock frequency with Hz.
 */
void SDK_DelayAtLeastMs(uint32_t delayTime_ms, uint32_t coreClock_Hz);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_COMMON_DSC_H_ */
