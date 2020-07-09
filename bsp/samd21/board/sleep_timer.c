// From module: RTC - Real Time Counter in Count Mode (Polled APIs)
#include <rtc_count.h>
#include <rtc_count_interrupt.h>
// #include <rtc_tamper.h>
#include <power.h>
#include <port.h>

#include <rtthread.h>

/* RTC module instance */
static struct rtc_module rtc_instance;

static void _rtc_timer_int_cb(void)
{
	port_pin_toggle_output_level(PIN_PB30);
}

/* Init RTC as ADC sample timer */
static void _rtc_timer_init(void)
{
	struct rtc_count_config conf;

	rtc_count_get_config_defaults(&conf);

	conf.prescaler         = RTC_COUNT_PRESCALER_DIV_1;
	conf.mode              = RTC_COUNT_MODE_32BIT;
	conf.clear_on_match    = false;
	conf.compare_values[0] = 0;

	// struct rtc_count_events evconfig;
	// evconfig.generate_event_on_compare[0] = true;

	rtc_count_init(&rtc_instance, RTC, &conf);
	// rtc_count_enable_events(&rtc_instance, &evconfig);
    // rtc_count_enable(&rtc_instance);
	rtc_count_set_count(&rtc_instance, 0);
	rtc_count_register_callback(&rtc_instance, _rtc_timer_int_cb, RTC_COUNT_CALLBACK_COMPARE_0);
	// rtc_count_enable_callback(&rtc_instance, RTC_COUNT_CALLBACK_COMPARE_0);
}

static void _rtc_timer_start(uint32_t ms)
{
	uint32_t compare = 0;

	compare = (uint32_t)(32.768 * ms);

	// rtc_count_register_callback(&rtc_instance, _rtc_timer_int_cb, RTC_COUNT_CALLBACK_COMPARE_0);
	rtc_count_enable_callback(&rtc_instance, RTC_COUNT_CALLBACK_COMPARE_0);

	rtc_count_set_count(&rtc_instance, 0);
	rtc_count_set_compare(&rtc_instance, compare, RTC_COUNT_COMPARE_0);
	rtc_count_enable(&rtc_instance);
}

static void sleep_tick_adjust(uint32_t ms)
{
	uint32_t diff;

	diff = rt_tick_from_millisecond(ms);

	rt_tick_set(rt_tick_get() + diff);
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
}

static void _sleep_entry(void)
{
	rt_tick_t timeout;
	rt_uint32_t ms;
	rt_uint32_t count;

	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	timeout = rt_timer_next_timeout_tick() - rt_tick_get();

	ms = timeout * (1000 / RT_TICK_PER_SECOND);
	rt_kprintf("os tick:%u entry sleep:%u tick\r\n", rt_tick_get(), timeout);

	_rtc_timer_start(ms);

	system_sleep();

	rt_enter_critical();
	count = rtc_count_get_count(&rtc_instance);
	ms = (count + 32) / 32.768;
	rtc_count_disable(&rtc_instance);
	sleep_tick_adjust(ms);
	timeout = rt_tick_get();
	rt_exit_critical();
	rt_kprintf("sleep exited, os tick:%u\n", timeout);
}

void sleep_timer_init(void)
{
	_rtc_timer_init();
	rt_thread_idle_sethook(_sleep_entry);
}

void sleep_timer_start(uint32_t ms)
{
	_rtc_timer_start(ms);
}

void sleep_timer_stop(void)
{
	rtc_count_disable(&rtc_instance);
}
