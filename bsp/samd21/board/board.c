#include "board.h"
#include <clock.h>
#include <gclk.h>
#include <system.h>
#include <rtthread.h>
/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

void configure_extosc32k(void);
void configure_dfll_open_loop(void);

//! [setup]
//! [config_extosc32k]
void configure_extosc32k(void)
{
//! [config_extosc32k_config]
	struct system_clock_source_xosc32k_config config_ext32k;
//! [config_extosc32k_config]
//! [config_extosc32k_get_defaults]
	system_clock_source_xosc32k_get_config_defaults(&config_ext32k);
//! [config_extosc32k_get_defaults]

//! [config_extosc32k_change_defaults]
	config_ext32k.startup_time = SYSTEM_XOSC32K_STARTUP_4096;
    config_ext32k.on_demand = false;
//! [config_extosc32k_change_defaults]

//! [config_extosc32k_set_config]
	system_clock_source_xosc32k_set_config(&config_ext32k);
//! [config_extosc32k_set_config]
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);
	while(!system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_XOSC32K));
}
//! [config_extosc32k]

#if (!SAMC21)
//! [config_dfll]
void configure_dfll_open_loop(void)
{
//! [config_dfll_config]
	struct system_clock_source_dfll_config config_dfll;
//! [config_dfll_config]
//! [config_dfll_get_defaults]
	system_clock_source_dfll_get_config_defaults(&config_dfll);
//! [config_dfll_get_defaults]
	config_dfll.coarse_value    = (*((uint8_t*)(0x806020 + 7))) >> 2;// 0x1f / 4; /* Midpoint */
	config_dfll.fine_value      = (*((uint32_t*)(0x806020 + 8))) & 0x3FF;//0xff / 4; /* Midpoint */
//! [config_dfll_set_config]
	system_clock_source_dfll_set_config(&config_dfll);
//! [config_dfll_set_config]

//! [enable_dfll_main]
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_DFLL);
	// while(!system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_DFLL));

//! [enable_dfll_main]
	/* Configure flash wait states before switching to high frequency clock */
//! [set_sys_wait_states]
	system_flash_set_waitstates(2);
//! [set_sys_wait_states]

	/* Change system clock to DFLL */
//! [set_sys_clk_src]
	struct system_gclk_gen_config config_gclock_gen;
	system_gclk_gen_get_config_defaults(&config_gclock_gen);
	config_gclock_gen.source_clock    = SYSTEM_CLOCK_SOURCE_DFLL;
	config_gclock_gen.division_factor = 1;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &config_gclock_gen);
//! [set_sys_clk_src]
}
//! [config_dfll]
#endif

void rt_board_init(void)
{
    extern void uart_init(void);

    // configure_extosc32k();

    // configure_dfll_open_loop();
	system_init();

	/* initialize systick */
	SystemCoreClock = system_gclk_gen_get_hz(0);
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

    uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

