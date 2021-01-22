#include "board.h"
#include "drv_uart.h"
#include "app_util_platform.h"
#include "nrf_drv_common.h"
#include "nrf_systick.h"
#include "nrf_rtc.h"
#include "nrf_drv_clock.h"
#include "softdevice_handler.h"
#include "nrf_drv_uart.h"
#include "nrf_gpio.h"

#include <rtthread.h>
#include <rthw.h>

#define TICK_RATE_HZ  RT_TICK_PER_SECOND
#define SYSTICK_CLOCK_HZ  ( 32768UL )

#define NRF_RTC_REG        NRF_RTC1
    /* IRQn used by the selected RTC */
#define NRF_RTC_IRQn       RTC1_IRQn
    /* Constants required to manipulate the NVIC. */
#define NRF_RTC_PRESCALER  ( (uint32_t) (ROUNDED_DIV(SYSTICK_CLOCK_HZ, TICK_RATE_HZ) - 1) )
    /* Maximum RTC ticks */
#define NRF_RTC_MAXTICKS   ((1U<<24)-1U)

static volatile uint32_t m_tick_overflow_count = 0;
#define NRF_RTC_BITWIDTH 24
#define OSTick_Handler     RTC1_IRQHandler
#define EXPECTED_IDLE_TIME_BEFORE_SLEEP   2

void SysTick_Configuration(void)
{
    nrf_drv_clock_lfclk_request(NULL);

    /* Configure SysTick to interrupt at the requested rate. */
    nrf_rtc_prescaler_set(NRF_RTC_REG, NRF_RTC_PRESCALER);
    nrf_rtc_int_enable   (NRF_RTC_REG, RTC_INTENSET_TICK_Msk);
    nrf_rtc_task_trigger (NRF_RTC_REG, NRF_RTC_TASK_CLEAR);
    nrf_rtc_task_trigger (NRF_RTC_REG, NRF_RTC_TASK_START);
    nrf_rtc_event_enable(NRF_RTC_REG, RTC_EVTEN_OVRFLW_Msk);

    NVIC_SetPriority(NRF_RTC_IRQn, 0xF);
    NVIC_EnableIRQ(NRF_RTC_IRQn);
}

static rt_tick_t _tick_distance(void)
{
    nrf_rtc_event_clear(NRF_RTC_REG, NRF_RTC_EVENT_COMPARE_0);

    uint32_t systick_counter = nrf_rtc_counter_get(NRF_RTC_REG);
    nrf_rtc_event_clear(NRF_RTC_REG, NRF_RTC_EVENT_TICK);

    /* check for overflow in TICK counter */
    if(nrf_rtc_event_pending(NRF_RTC_REG, NRF_RTC_EVENT_OVERFLOW))
    {
        nrf_rtc_event_clear(NRF_RTC_REG, NRF_RTC_EVENT_OVERFLOW);
        m_tick_overflow_count++;
    }

    return ((m_tick_overflow_count << NRF_RTC_BITWIDTH) + systick_counter) - rt_tick_get();
}

void OSTick_Handler( void )
{
    uint32_t diff;

	/* enter interrupt */
    rt_interrupt_enter();
    diff = _tick_distance();

    while((diff--) > 0)
    {
        if (rt_thread_self() != RT_NULL)
        {
          rt_tick_increase();
        }
    }
    /* leave interrupt */
    rt_interrupt_leave();
}

static void _wakeup_tick_adjust(void)
{
    uint32_t diff;
    uint32_t level;

    level = rt_hw_interrupt_disable();

    diff = _tick_distance();

    rt_tick_set(rt_tick_get() + diff);

    if (rt_thread_self() != RT_NULL)
    {
    	struct rt_thread *thread;

        /* check time slice */
        thread = rt_thread_self();

        if (thread->remaining_tick <= diff)
        {
            /* change to initialized tick */
            thread->remaining_tick = thread->init_tick;

            /* yield */
            rt_thread_yield();
        }
        else
        {
            thread->remaining_tick -= diff;
        }

        /* check timer */
        rt_timer_check();
    }

    rt_hw_interrupt_enable(level);
}

static void _sleep_ongo( uint32_t sleep_tick )
{
    uint32_t enterTime;
    uint32_t entry_tick;

    /* Make sure the SysTick reload value does not overflow the counter. */
    if ( sleep_tick > NRF_RTC_MAXTICKS - EXPECTED_IDLE_TIME_BEFORE_SLEEP )
    {
        sleep_tick = NRF_RTC_MAXTICKS - EXPECTED_IDLE_TIME_BEFORE_SLEEP;
    }

    rt_enter_critical();

    enterTime = nrf_rtc_counter_get(NRF_RTC_REG);

    {
        uint32_t wakeupTime = (enterTime + sleep_tick) & NRF_RTC_MAXTICKS;

        /* Stop tick events */
        nrf_rtc_int_disable(NRF_RTC_REG, NRF_RTC_INT_TICK_MASK);

        /* Configure CTC interrupt */
        nrf_rtc_cc_set(NRF_RTC_REG, 0, wakeupTime);
        nrf_rtc_event_clear(NRF_RTC_REG, NRF_RTC_EVENT_COMPARE_0);
        nrf_rtc_int_enable(NRF_RTC_REG, NRF_RTC_INT_COMPARE0_MASK);

        entry_tick = rt_tick_get();

        __DSB();

        if ( sleep_tick > 0 )
        {
#ifdef SOFTDEVICE_PRESENT
            if (softdevice_handler_is_enabled())
            {
                uint32_t err_code = sd_app_evt_wait();
                APP_ERROR_CHECK(err_code);
            }
            else
#endif
            {
                /* No SD -  we would just block interrupts globally.
                * BASEPRI cannot be used for that because it would prevent WFE from wake up.
                */
                do{
                    __WFE();
                } while (0 == (NVIC->ISPR[0] | NVIC->ISPR[1]));
            }
        }

        nrf_rtc_int_disable(NRF_RTC_REG, NRF_RTC_INT_COMPARE0_MASK);
        nrf_rtc_event_clear(NRF_RTC_REG, NRF_RTC_EVENT_COMPARE_0);

        _wakeup_tick_adjust();

        /* Correct the system ticks */
        {

            nrf_rtc_event_clear(NRF_RTC_REG, NRF_RTC_EVENT_TICK);
            nrf_rtc_int_enable (NRF_RTC_REG, NRF_RTC_INT_TICK_MASK);
            /* It is important that we clear pending here so that our corrections are latest and in sync with tick_interrupt handler */
            NVIC_ClearPendingIRQ(NRF_RTC_IRQn);
        }

        // rt_kprintf("entry tick:%u, expected:%u, current tick:%u\n", entry_tick, sleep_tick, rt_tick_get());
    }

    rt_exit_critical();
}


void rt_hw_system_powersave(void)
{
    uint32_t sleep_tick;

    sleep_tick = rt_timer_next_timeout_tick() - rt_tick_get();

    if ( sleep_tick >= EXPECTED_IDLE_TIME_BEFORE_SLEEP)
    {
        // rt_kprintf("sleep entry:%u\n", rt_tick_get());
        _sleep_ongo( sleep_tick );
    }
}

void rt_hw_board_init(void)
{
    // sd_power_dcdc_mode_set(NRF_POWER_DCDC_ENABLE);
    /* Activate deep sleep mode */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    nrf_drv_clock_init();
    // nrf_drv_clock_hfclk_request(0);

    SysTick_Configuration();

    rt_thread_idle_sethook(rt_hw_system_powersave);

    rt_hw_uart_init();

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

