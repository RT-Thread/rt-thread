/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-08     kaidegit     first version
 *
 * 唤醒配置 / Wakeup configuration:
 * - 使用 WFE 和 SEVONPEND 进入 STOP，RTC 闹钟唤醒由本驱动配置。
 *   Use WFE with SEVONPEND for STOP. RTC alarm wakeup is configured by this
 *   driver.
 * - GPIO 可直接通过 rt_pin_irq_enable() 配置 EXTI 中断唤醒和回调，无需额外
 *   配置事件路径。
 *   GPIO wakeup and callbacks can be configured directly with
 *   rt_pin_irq_enable() through EXTI interrupts, without an extra event path.
 */

#include <board.h>
#include <rtdevice.h>
#include <ch32v20x_exti.h>
#include <ch32v20x_gpio.h>
#include <ch32v20x_pwr.h>
#include <ch32v20x_rcc.h>
#include <ch32v20x_rtc.h>
#include <ch32v20x_usart.h>

#ifdef RT_USING_PM

#define PM_RTC_LSE_MILLIHZ     16384000u
#define PM_MAX_STOP_SECONDS    10u
#define PM_WAKE_GUARD_US       3000u
#define PM_MIN_STOP_US         10000u
#define PM_LSI_CAPTURE_CYCLES  128u
#define PM_LSI_COUNTER_MODULUS 16384u
#define PM_LSI_REFRESH_MS      10000u
#define PM_LSI_TIMEOUT_MS      50u

#define PFIC_SLEEP_ON_EXIT    (1u << 1)
#define PFIC_SLEEP_DEEP       (1u << 2)
#define PFIC_EVENT_ON_PENDING (1u << 4)

static struct
{
    struct
    {
        rt_uint32_t rcc_ctlr;
        rt_uint32_t rcc_cfgr0;
        rt_uint32_t exten_ctr;
    } rcc_cfg;
    struct
    {
        rt_uint32_t rtc_millihz;
        rt_uint32_t rtc_cycle_remainder;
        rt_uint32_t rtc_ready;
    } rtc;
    struct
    {
        rt_uint32_t edge_counter;
        rt_uint64_t edge_phase;
        rt_uint64_t tick_cmp;
        rt_uint32_t tick_ctl;
        rt_uint32_t resume_phase;
        rt_tick_t sleep_ticks;
        rt_uint32_t timer_armed;
        rt_uint32_t systick_suspended;
        rt_uint32_t sleeps;
        rt_uint32_t aborts;
        rt_uint32_t slept_rtc_ticks;
        rt_uint32_t calibrations;
        rt_uint32_t calibration_errors;
    } runtime;
} pm_state;

#ifdef BSP_PM_USING_LSI
static rt_tick_t lsi_measure_due;
static rt_tick_t lsi_measure_started;
static rt_uint32_t lsi_measuring;
static rt_uint32_t lsi_discard_first;

static void lsi_measure_begin(void)
{
    OSC->LSI32K_CAL_CTRL &= ~(RB_OSC_CAL_EN | RB_OSC_CAL_INT_EN);
    OSC->LSI32K_CAL_CFG = Level_128;
    OSC->LSI32K_CAL_STATR |= RB_OSC_CAL_IF_END | RB_OSC_CAL_CNT_OV;
    OSC->LSI32K_CAL_CTRL |= RB_OSC_CAL_EN;
    lsi_measuring = 1;
    lsi_discard_first = 1;
    lsi_measure_started = rt_tick_get();
}

static void lsi_measure_poll(void)
{
    rt_tick_t now = rt_tick_get();

    if (!lsi_measuring)
    {
        if ((rt_int32_t)(now - lsi_measure_due) < 0)
        {
            return;
        }
        lsi_measure_begin();
    }

    if (OSC->LSI32K_CAL_STATR & RB_OSC_CAL_IF_END)
    {
        if (lsi_discard_first)
        {
            lsi_discard_first = 0;
            OSC->LSI32K_CAL_CTRL &= ~RB_OSC_CAL_EN;
            OSC->LSI32K_CAL_CTRL |= RB_OSC_CAL_EN;
            OSC->LSI32K_CAL_STATR |= RB_OSC_CAL_IF_END | RB_OSC_CAL_CNT_OV;
            lsi_measure_started = now;
        }
        else
        {
            rt_uint32_t count;
            rt_uint32_t lsi_millihz;

            OSC->LSI32K_CAL_CTRL &= ~RB_OSC_CAL_EN;
            count = (OSC->LSI32K_CAL_STATR & RB_OSC_CAL_CNT) +
                    (rt_uint32_t)OSC->LSI32K_CAL_OV_CNT * PM_LSI_COUNTER_MODULUS;
            lsi_millihz = count ? (rt_uint32_t)((rt_uint64_t)PM_LSI_CAPTURE_CYCLES *
                                                SystemCoreClock * 1000u / count)
                                : 0;
            if (lsi_millihz >= 25000000u && lsi_millihz <= 45000000u)
            {
                rt_uint32_t rtc_millihz = lsi_millihz / 2;

                if (pm_state.rtc.rtc_millihz)
                {
                    pm_state.rtc.rtc_cycle_remainder =
                        (rt_uint32_t)((rt_uint64_t)pm_state.rtc.rtc_cycle_remainder *
                                      rtc_millihz / pm_state.rtc.rtc_millihz);
                }
                pm_state.rtc.rtc_millihz = rtc_millihz;
                pm_state.rtc.rtc_ready = 1;
                pm_state.runtime.calibrations++;
            }
            else
            {
                pm_state.runtime.calibration_errors++;
                pm_state.rtc.rtc_ready = 0;
            }
            lsi_measuring = 0;
            lsi_measure_due = now + rt_tick_from_millisecond(PM_LSI_REFRESH_MS);
        }
    }

    if (lsi_measuring &&
        now - lsi_measure_started >= rt_tick_from_millisecond(PM_LSI_TIMEOUT_MS))
    {
        OSC->LSI32K_CAL_CTRL &= ~RB_OSC_CAL_EN;
        lsi_measuring = 0;
        lsi_measure_due = now + rt_tick_from_millisecond(PM_LSI_REFRESH_MS);
        pm_state.runtime.calibration_errors++;
        pm_state.rtc.rtc_ready = 0;
    }
}
#endif

static rt_uint32_t pending_irq(void)
{
    rt_uint32_t i;

    for (i = 0; i < 4; i++)
    {
        if (NVIC->IPR[i] & NVIC->ISR[i])
        {
            return 1;
        }
    }
    return 0;
}

static rt_uint32_t irq_save(void)
{
    rt_uint32_t previous;

    __asm volatile("csrrc %0, 0x800, %1; fence.i"
                   : "=r"(previous) : "r"(0x88u) : "memory");
    return previous & 0x88u;
}

static void irq_restore(rt_uint32_t previous)
{
    __asm volatile("csrc 0x800, %0; csrs 0x800, %1; fence.i" ::"r"(0x88u), "r"(previous & 0x88u) : "memory");
}

static void short_idle_wfe(void)
{
    rt_uint32_t irq_level = irq_save();
    rt_uint32_t sctlr = NVIC->SCTLR;

    NVIC->SCTLR = (sctlr & ~(PFIC_SLEEP_ON_EXIT | PFIC_SLEEP_DEEP)) |
                  PFIC_EVENT_ON_PENDING;
    _SEV();
    _WFE();
    if (!pending_irq())
    {
        _WFE();
    }
    NVIC->SCTLR = sctlr;
    irq_restore(irq_level);
}

static rt_uint32_t rtc_to_cycles(rt_uint32_t rtc_ticks)
{
    rt_uint64_t scaled = (rt_uint64_t)rtc_ticks * SystemCoreClock * 1000u +
                         pm_state.rtc.rtc_cycle_remainder;

    pm_state.rtc.rtc_cycle_remainder = scaled % pm_state.rtc.rtc_millihz;
    return (rt_uint32_t)(scaled / pm_state.rtc.rtc_millihz);
}

rt_tick_t pm_timer_next_timeout_tick(rt_uint8_t mode)
{
    RT_UNUSED(mode);
#ifdef BSP_PM_USING_LSI
    lsi_measure_poll();
#endif
    return rt_timer_next_timeout_tick();
}

static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    rt_uint32_t limited_ticks;
    rt_uint32_t budget_us;
    rt_uint32_t alarm;
    rt_uint32_t before;
    rt_uint32_t edge;
    rt_uint32_t spins;
    rt_uint64_t cycles;

    RT_UNUSED(pm);
    pm_state.runtime.timer_armed = 0;
    pm_state.runtime.sleep_ticks = 0;

    if (!pm_state.rtc.rtc_ready)
    {
        return;
    }
#ifdef BSP_PM_USING_LSI
    if (lsi_measuring)
    {
        return;
    }
#endif
#ifdef BSP_USING_UART1
    if (!(USART1->STATR & USART_STATR_TC))
    {
        return;
    }
#endif

    limited_ticks = timeout;
    if (limited_ticks > PM_MAX_STOP_SECONDS * RT_TICK_PER_SECOND)
    {
        limited_ticks = PM_MAX_STOP_SECONDS * RT_TICK_PER_SECOND;
    }
    cycles = (rt_uint64_t)limited_ticks * (SystemCoreClock / RT_TICK_PER_SECOND);
    if (SysTick->CNT >= cycles)
    {
        return;
    }
    budget_us = (rt_uint32_t)((cycles - SysTick->CNT) * 1000000u / SystemCoreClock);
    if (budget_us < PM_MIN_STOP_US + PM_WAKE_GUARD_US)
    {
        return;
    }

    RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_WaitForLastTask();
    EXTI_ClearITPendingBit(EXTI_Line17);
    alarm = RTC_GetCounter() +
            (rt_uint32_t)((rt_uint64_t)(budget_us - PM_WAKE_GUARD_US) *
                          pm_state.rtc.rtc_millihz / 1000000000u);
    RTC_SetAlarm(alarm);
    RTC_WaitForLastTask();

    before = RTC_GetCounter();
    spins = SystemCoreClock / 1000u;
    do
    {
        edge = RTC_GetCounter();
        if (!--spins)
        {
            pm_state.runtime.aborts++;
            return;
        }
    } while (edge == before);

    if (pending_irq() || SysTick->SR || (rt_int32_t)(alarm - edge) <= 0)
    {
        pm_state.runtime.aborts++;
        return;
    }

    pm_state.runtime.edge_counter = edge;
    pm_state.runtime.edge_phase = SysTick->CNT;
    pm_state.runtime.timer_armed = 1;
}

static void pm_timer_stop(struct rt_pm *pm)
{
    RT_UNUSED(pm);

    if (pm_state.runtime.timer_armed)
    {
        RTC_ClearITPendingBit(RTC_IT_ALR);
        RTC_WaitForLastTask();
        EXTI_ClearITPendingBit(EXTI_Line17);
    }
    pm_state.runtime.timer_armed = 0;
}

static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    RT_UNUSED(pm);
    return pm_state.runtime.sleep_ticks;
}

static void pm_clock_save(void)
{
    pm_state.rcc_cfg.rcc_ctlr = RCC->CTLR;
    pm_state.rcc_cfg.rcc_cfgr0 = RCC->CFGR0;
    pm_state.rcc_cfg.exten_ctr = EXTEN->EXTEN_CTR;
}

static void pm_clock_restore(void)
{
    rt_uint32_t saved_sws = (pm_state.rcc_cfg.rcc_cfgr0 & RCC_SW) << 2;

    RCC->CTLR |= RCC_HSION;
    while (!(RCC->CTLR & RCC_HSIRDY))
    {
    }
    RCC->CFGR0 &= ~RCC_SW;
    while (RCC->CFGR0 & RCC_SWS)
    {
    }

    RCC->CTLR &= ~RCC_PLLON;
    EXTEN->EXTEN_CTR = pm_state.rcc_cfg.exten_ctr;
    RCC->CFGR0 = pm_state.rcc_cfg.rcc_cfgr0 & ~RCC_SW;
    if (pm_state.rcc_cfg.rcc_ctlr & RCC_HSEON)
    {
        RCC->CTLR |= RCC_HSEON;
        while (!(RCC->CTLR & RCC_HSERDY))
        {
        }
    }
    if (pm_state.rcc_cfg.rcc_ctlr & RCC_PLLON)
    {
        RCC->CTLR |= RCC_PLLON;
        while (!(RCC->CTLR & RCC_PLLRDY))
        {
        }
    }

    RCC->CFGR0 = pm_state.rcc_cfg.rcc_cfgr0;
    while ((RCC->CFGR0 & RCC_SWS) != saved_sws)
    {
    }
    RCC->CTLR = pm_state.rcc_cfg.rcc_ctlr;
}

static void pm_stop(void)
{
    rt_uint32_t before;
    rt_uint32_t wake;
    rt_uint32_t spins;
    rt_uint32_t sctlr;
    rt_uint32_t rtc_ticks;
    rt_uint64_t total;
    rt_uint64_t cycles_per_tick = SystemCoreClock / RT_TICK_PER_SECOND;

    if (pending_irq() || SysTick->SR)
    {
        pm_state.runtime.aborts++;
        return;
    }

    irq_save();
    pm_state.runtime.tick_ctl = SysTick->CTLR;
    pm_state.runtime.tick_cmp = SysTick->CMP;
    SysTick->CTLR = 0;
    if (SysTick->SR || pending_irq())
    {
        SysTick->CTLR = pm_state.runtime.tick_ctl;
        irq_restore(0);
        pm_state.runtime.aborts++;
        return;
    }

    pm_state.runtime.systick_suspended = 1;
    sctlr = NVIC->SCTLR;
    NVIC->SCTLR = (sctlr & ~PFIC_SLEEP_ON_EXIT) | PFIC_EVENT_ON_PENDING;
    PWR_EnterSTOPMode_RAM_LV(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);

    pm_clock_restore();
    before = RTC_GetCounter();
    spins = SystemCoreClock / 1000u;
    do
    {
        wake = RTC_GetCounter();
        if (!--spins)
        {
            wake = before;
            pm_state.runtime.calibration_errors++;
            break;
        }
    } while (wake == before);

    SysTick->CNT = 0;
    SysTick->CMP = ~(rt_uint64_t)0;
    SysTick->CTLR = 5;

    rtc_ticks = wake - pm_state.runtime.edge_counter;
    pm_state.runtime.slept_rtc_ticks += rtc_ticks;
    RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_WaitForLastTask();
    EXTI_ClearITPendingBit(EXTI_Line17);
    NVIC->SCTLR = sctlr;

    total = pm_state.runtime.edge_phase + rtc_to_cycles(rtc_ticks);
    pm_state.runtime.sleep_ticks = total / cycles_per_tick;
    pm_state.runtime.resume_phase = total % cycles_per_tick;
    pm_state.runtime.sleeps++;
}

static void pm_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    RT_UNUSED(pm);

    switch (mode)
    {
    case PM_SLEEP_MODE_IDLE:
    case PM_SLEEP_MODE_LIGHT:
        short_idle_wfe();
        break;
    case PM_SLEEP_MODE_DEEP:
        if (pm_state.runtime.timer_armed)
        {
            pm_stop();
        }
        else
        {
            short_idle_wfe();
        }
        break;
    default:
        break;
    }
}

void rt_pm_exit_critical(rt_uint32_t ctx, rt_uint8_t sleep_mode)
{
    rt_uint64_t cycles_per_tick = SystemCoreClock / RT_TICK_PER_SECOND;
    rt_uint64_t total;
    rt_tick_t recovery_ticks;

    RT_UNUSED(sleep_mode);

    if (pm_state.runtime.systick_suspended)
    {
        SysTick->CTLR = 0;
        total = pm_state.runtime.resume_phase + SysTick->CNT;
        recovery_ticks = total / cycles_per_tick;
        SysTick->CMP = pm_state.runtime.tick_cmp;
        SysTick->CNT = total % cycles_per_tick;
        SysTick->SR = 0;
        SysTick->CTLR = pm_state.runtime.tick_ctl;
        pm_state.runtime.systick_suspended = 0;
        if (recovery_ticks)
        {
            rt_interrupt_enter();
            rt_tick_increase_tick(recovery_ticks);
            rt_interrupt_leave();
        }
    }
    rt_hw_interrupt_enable(ctx);
}

static rt_err_t pm_rtc_init(void)
{
    rt_uint32_t i;

    pm_clock_save();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);

#ifdef BSP_PM_USING_LSE
    RCC_LSEConfig(RCC_LSE_ON);
    for (i = 0; !(RCC->BDCTLR & RCC_LSERDY); i++)
    {
        if (i == 500)
        {
            return -RT_ETIMEOUT;
        }
        rt_thread_mdelay(10);
    }
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_LSICmd(DISABLE);
    pm_state.rtc.rtc_millihz = PM_RTC_LSE_MILLIHZ;
#else
    RCC_LSEConfig(RCC_LSE_OFF);
    RCC_LSICmd(ENABLE);
    for (i = 0; !(RCC->RSTSCKR & RCC_LSIRDY); i++)
    {
        if (i == 100)
        {
            return -RT_ETIMEOUT;
        }
        rt_thread_mdelay(1);
    }
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#endif

    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    RTC_SetPrescaler(1);
    RTC_WaitForLastTask();
    RTC_SetCounter(0);
    RTC_WaitForLastTask();
    RTC_ClearITPendingBit(RTC_IT_ALR);
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT_ALR, ENABLE);
    RTC_WaitForLastTask();
    NVIC_DisableIRQ(RTCAlarm_IRQn);
    NVIC_ClearPendingIRQ(RTCAlarm_IRQn);
    EXTI->INTENR &= ~EXTI_Line17;
    EXTI->EVENR |= EXTI_Line17;
    EXTI->RTENR |= EXTI_Line17;
    EXTI->FTENR &= ~EXTI_Line17;

#ifdef BSP_PM_USING_LSI
    lsi_measure_begin();
    while (lsi_measuring)
    {
        lsi_measure_poll();
        if (lsi_measuring)
        {
            rt_thread_mdelay(1);
        }
    }
    if (!pm_state.rtc.rtc_millihz)
    {
        return -RT_ERROR;
    }
#endif
    pm_state.rtc.rtc_ready = 1;
    return RT_EOK;
}

#ifdef BSP_PM_PARK_UNUSED_GPIO
static void pm_park_unused_gpio(void)
{
    GPIO_InitTypeDef gpio = { 0 };
    rt_uint16_t pa_keep = GPIO_Pin_0; /* PM demo LED. */

#ifdef BSP_USING_UART1
    pa_keep |= GPIO_Pin_9 | GPIO_Pin_10; /* Console TX/RX. */
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                               RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                               RCC_APB2Periph_AFIO,
                           ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);

    /* Pin masks for the PM measurement board. Keep both crystal pairs. */
    gpio.GPIO_Mode = GPIO_Mode_AIN;
    gpio.GPIO_Pin = GPIO_Pin_All & ~pa_keep;
    GPIO_Init(GPIOA, &gpio);
    gpio.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOB, &gpio);
    gpio.GPIO_Pin = GPIO_Pin_All & ~(GPIO_Pin_14 | GPIO_Pin_15);
    GPIO_Init(GPIOC, &gpio);
    gpio.GPIO_Pin = GPIO_Pin_All & ~(GPIO_Pin_0 | GPIO_Pin_1);
    GPIO_Init(GPIOD, &gpio);
}
#endif

static int ch32_pm_init(void)
{
    static const struct rt_pm_ops ops = {
        pm_sleep,
        RT_NULL,
        pm_timer_start,
        pm_timer_stop,
        pm_timer_get_tick,
    };

#if BSP_PM_BOOT_DELAY > 0
    rt_kprintf("PM: STOP enabled after %u s reflash window\n", BSP_PM_BOOT_DELAY);
    rt_thread_mdelay(BSP_PM_BOOT_DELAY * 1000u);
#endif
    if (pm_rtc_init() != RT_EOK)
    {
        rt_kprintf("PM: RTC initialization failed, STOP disabled\n");
        return -RT_ERROR;
    }

#ifdef BSP_PM_PARK_UNUSED_GPIO
    /* Leave SWJ available throughout the reflash window. */
    pm_park_unused_gpio();
#endif
    rt_system_pm_init(&ops, 1u << PM_SLEEP_MODE_DEEP, RT_NULL);
    rt_pm_release(PM_SLEEP_MODE_NONE);
    rt_kprintf("PM: RTC %s/2, %u mHz\n",
#ifdef BSP_PM_USING_LSE
               "LSE",
#else
               "LSI",
#endif
               pm_state.rtc.rtc_millihz);
    return RT_EOK;
}
INIT_APP_EXPORT(ch32_pm_init);

#ifdef RT_USING_FINSH
static void ch32_pm_stats(void)
{
    rt_kprintf("rtc_ready=%u rtc_millihz=%u sleeps=%u aborts=%u slept_rtc_ticks=%u\n",
               pm_state.rtc.rtc_ready, pm_state.rtc.rtc_millihz, pm_state.runtime.sleeps,
               pm_state.runtime.aborts, pm_state.runtime.slept_rtc_ticks);
    rt_kprintf("calibrations=%u calibration_errors=%u\n",
               pm_state.runtime.calibrations, pm_state.runtime.calibration_errors);
}
MSH_CMD_EXPORT(ch32_pm_stats, show CH32V208 PM statistics);
#endif

#endif /* RT_USING_PM */
