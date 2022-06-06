/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup HAL_BASE
 *  @{
 */

/** @defgroup HAL_BASE_How_To_Use How To Use
 *  @{

 HAL system support is including delay system, HAL tick system and global system clock,

 HAL system tick setting:

 - Attach HAL_IncTick() to system tick interrupt handler;
 - Notify the HAL system the system's tick frequency by calling HAL_SetTickFreq() unless
    it is the same as default value HAL_TICK_FREQ_1KHZ;
 - If you need a more accurate delay system, specify SYS_TIMER in hal_conf.h.

 Init HAL system:

 - Initialize the HAL system by calling HAL_Init():

 Reset when SOC system is changed:

 - Update system with new core clock and new SysTick clock source by calling HAL_SystemCoreClockUpdate();

 APIs:

 - Get system time by calling HAL_GetTick();
 - Delay for a certain length of time, HAL_DelayMs(), HAL_DelayUs(), and HAL_CPUDelayUs().
 - Blocking for a certain period of time to continuously query HW status, use HAL_GetTick()
 to do timeout, this will be more accurate.

 @} */

/** @defgroup HAL_BASE_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

#define HAL_TICK_FREQ_DEFAULT HAL_TICK_FREQ_1KHZ

/********************* Private Structure Definition **************************/

/********************* Private Variable Definition ***************************/

static __IO uint32_t uwTick;
static eHAL_tickFreq uwTickFreq = HAL_TICK_FREQ_DEFAULT;

/********************* Private Function Definition ***************************/
#if defined(__CORTEX_A) || defined(__CORTEX_M)
#if __CORTEX_M == 0U || !defined(__GNUC__)
static void CPUCycleLoop(uint32_t cycles)
{
    uint32_t count;

    if (cycles < 100U) {
        return;
    }

    count = cycles / 3;
    while (count-- > 0) {
        __asm volatile ("nop");
    }
}
#else
static void CPUCycleLoop(uint32_t cycles)
{
    __ASM volatile (
        "mov  r0, %0\n\t"
        "adds r0, r0, #2\n\t"   //    1    2    Round to the nearest multiple of 4.
        "lsrs r0, r0, #2\n\t"   //    1    2    Divide by 4 and set flags.
        "beq  2f\n\t"           //    2    2    Skip if 0.
        ".align 4\n\t"
        "1:\n\t"
        "adds r0, r0, #1\n\t"   //    1    2    Increment the counter.
        "subs r0, r0, #2\n\t"   //    1    2    Decrement the counter by 2.
        "bne  1b\n\t"           //   (1)2  2    2 CPU cycles (if branch is taken).
        "nop\n\t"               //    1    2    Loop alignment padding.
        "2:"
        : : "r" (cycles)
        );
}
#endif
#elif defined(__RISC_V)
static void CPUCycleLoop(uint32_t cycles)
{
    asm volatile (
        "mv   a0, %0\n\t"
        "addi a0, a0, 2\n\t"   //    1    2    Round to the nearest multiple of 4.
        "li   a1, 4\n\t"
        "div  a0, a0, a1\n\t"  //    1    2    Divide by 4 and set flags.
        "li   a1, 2\n\t"
        "bnez a0, 1f\n\t"      //    2    2    Skip if 0.
        "j    2f\n\t"
        ".align 6\n\t"
        "1:\n\t"
        "addi a0, a0, 1\n\t"   //    1    2    Increment the counter.
        "sub  a0, a0, a1\n\t"  //    1    2    Decrement the counter by 2.
        "bnez a0, 1b\n\t"      //   (1)2  2    2 CPU cycles (if branch is taken).
        "nop\n\t"              //    1    2    Loop alignment padding.
        "2:"
        : : "r" (cycles)
        );
}
#endif

#if defined(SYS_TIMER) && defined(HAL_TIMER_MODULE_ENABLED)
__STATIC_FORCEINLINE HAL_Status TimerDelayUs(uint32_t us)
{
    uint64_t count, from, now, pass;

    from = HAL_TIMER_GetCount(SYS_TIMER);
    count = PLL_INPUT_OSC_RATE / 1000000 * us;

    do {
        now = HAL_TIMER_GetCount(SYS_TIMER);
        pass = now > from ? now - from : from - now;
    } while (pass < count);

    return HAL_OK;
}
#endif

/** @} */
/********************* Public Function Definition ***************************/
/** @defgroup HAL_BASE_Exported_Functions_Group4 Init and DeInit Functions

 This section provides functions allowing to init and deinit the module:

 *  @{
 */

/**
 * @brief  Init HAL driver basic code.
 * @return HAL_OK.
 */
HAL_Status HAL_Init(void)
{
#ifdef __CORTEX_M
#ifdef HAL_NVIC_MODULE_ENABLED
    /* Set Interrupt Group Priority */
    HAL_NVIC_Init();

    /* Set Interrupt Group Priority */
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_DEFAULT);
#endif
#endif

#if defined(SYS_TIMER) && defined(HAL_TIMER_MODULE_ENABLED)
    HAL_TIMER_SysTimerInit(SYS_TIMER);
#endif

#ifdef RK_BSP_TEMP
#ifdef HAL_PINCTRL_MODULE_ENABLED
    HAL_PINCTRL_Init();
#endif
#endif

    return HAL_OK;
}

/**
 * @brief  HAL system update with new core clock and systick clock source.
 * @param  hz: new core clock.
 * @param  clkSource: new systick clock source.
 * @return HAL_OK.
 */
HAL_Status HAL_SystemCoreClockUpdate(uint32_t hz, eHAL_systickClkSource clkSource)
{
    uint32_t rate = hz;
    HAL_Status ret = HAL_OK;

#if defined(__CORTEX_M) && defined(HAL_SYSTICK_MODULE_ENABLED)
    ret = HAL_SYSTICK_CLKSourceConfig(clkSource);
    if (ret == HAL_OK && clkSource == HAL_SYSTICK_CLKSRC_EXT) {
        rate = PLL_INPUT_OSC_RATE;
    }
    HAL_SYSTICK_Config(rate / (1000 / HAL_GetTickFreq()));
    ret = HAL_OK;
#endif

    if (ret == HAL_OK) {
        SystemCoreClock = rate;   /* Update global SystemCoreClock */
    }

    return ret;
}

/**
 * @brief  HAL deinit.
 * @return HAL_Status: HAL_OK.
 */
HAL_Status HAL_DeInit(void)
{
    /* TO-DO */

    return HAL_OK;
}

/** @} */

/** @defgroup HAL_BASE_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  Count plus tickFreq when interrupt occurs.
 * @return HAL_Status: HAL_OK.
 */
HAL_Status HAL_IncTick(void)
{
    uwTick += uwTickFreq;

    return HAL_OK;
}

/**
 * @brief  Provides tick value in millisecond.
 * @return uint32_t: tick value in millisecond.
 * @attention this API allow direct use in the HAL layer.
 */
uint32_t HAL_GetTick(void)
{
#if defined(SYS_TIMER) && defined(HAL_TIMER_MODULE_ENABLED)
    uint64_t tick = HAL_TIMER_GetCount(SYS_TIMER);
    uint32_t base = PLL_INPUT_OSC_RATE / 1000;

    if (tick >> 62) {
        tick = ~tick;
    }

    return (uint32_t)HAL_DivU64(tick, base);
#else

    return uwTick;
#endif
}

/**
 * @brief  Provides system timer count.
 * @return uint64_t: timer count.
 * @attention this API allow direct use in the HAL layer.
 */
uint64_t HAL_GetSysTimerCount(void)
{
#if defined(SYS_TIMER) && defined(HAL_TIMER_MODULE_ENABLED)
    uint64_t count = HAL_TIMER_GetCount(SYS_TIMER);
    if (count >> 62) {
        count = ~count;
    }

    return count;
#else

    return 0LLU;
#endif
}

/**
  * @brief Set new tick frequency.
  * @return HAL_Status.
  */
HAL_Status HAL_SetTickFreq(eHAL_tickFreq freq)
{
    HAL_ASSERT(IS_TICKFREQ(freq));

    uwTickFreq = freq;

    return HAL_OK;
}

/**
  * @brief Return tick frequency.
  * @return uint32_t: tick period in Hz.
  * @attention this API allow direct use in the HAL layer.
  */
eHAL_tickFreq HAL_GetTickFreq(void)
{
    return uwTickFreq;
}

/**
 * @brief  SysTick mdelay.
 * @param  ms: mdelay count.
 * @return HAL_Status: HAL_OK.
 * @attention this API allow direct use in the HAL layer. Blocking for a
 *  certain period of time to continuously query HW status, use HAL_GetTick
 *  to do timeout, that will be more accurate.
 */
__WEAK HAL_Status HAL_DelayMs(uint32_t ms)
{
    for (uint32_t i = 0; i < ms; i++) {
        HAL_DelayUs(1000);
    }

    return HAL_OK;
}

/**
 * @brief  SysTick udelay.
 * @param  us: udelay count.
 * @return HAL_Status: HAL_OK.
 * @attention this API allow direct use in the HAL layer. The longer the delay,
 *  the more accurate. Actual delay is greater than the parameter.
 */
HAL_Status HAL_DelayUs(uint32_t us)
{
#if defined(SYS_TIMER) && defined(HAL_TIMER_MODULE_ENABLED)

    return TimerDelayUs(us);
#else

    return HAL_CPUDelayUs(us);
#endif
}

/**
 * @brief  CPU loop udelay.
 * @param  us: udelay count.
 * @return HAL_Status: HAL_OK.
 * @attention this API allow direct use in the HAL layer. The longer the delay,
 *  the more accurate. Actual delay is greater than the parameter.
 *  During delay, CPU rate change result in delay imprecise, so call it in
 *  following case:
 *    1.IRQ disable
 *    2.CRU code
 */
HAL_Status HAL_CPUDelayUs(uint32_t us)
{
    volatile uint32_t cycles;

#if (__CORTEX_M == 0)
    cycles = (uint32_t)HAL_DivU64((uint64_t)SystemCoreClock, 1000000) * us; /* Add few cycles penalty */
#else
    cycles = SystemCoreClock / 1000000 * us; /* Add few cycles penalty */
#endif

    CPUCycleLoop(cycles);

    return HAL_OK;
}

/** @} */

/** @} */

/** @} */
