#include <rtthread.h>
#include <rthw.h>

#include "board.h"

#include "port.h"
#include "extint.h"

#include "sleep_timer.h"

void LED_Init(void)
{
    struct port_config config_port_pin;

    port_get_config_defaults(&config_port_pin);
    config_port_pin.direction  = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_UP;
    port_pin_set_config(PIN_PA15, &config_port_pin);

    config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(PIN_PB30, &config_port_pin);
}

void LED_ON(void)
{
    port_pin_set_output_level(PIN_PB30, false);
}

void LED_OFF(void)
{
    port_pin_set_output_level(PIN_PB30, true);
}

void extint_detection_callback(void);

void configure_extint_channel(void)
{
//! [setup_1]
    struct extint_chan_conf config_extint_chan;
//! [setup_1]
//! [setup_2]
    extint_chan_get_config_defaults(&config_extint_chan);
//! [setup_2]

//! [setup_3]
    config_extint_chan.gpio_pin           = PIN_PA15A_EIC_EXTINT15;
    config_extint_chan.gpio_pin_mux       = MUX_PA15A_EIC_EXTINT15;
    config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
    config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
//! [setup_3]
//! [setup_4]
    extint_chan_set_config(15, &config_extint_chan);
//! [setup_4]
}

void configure_extint_callbacks(void)
{
//! [setup_5]
    extint_register_callback(extint_detection_callback, 15, EXTINT_CALLBACK_TYPE_DETECT);
//! [setup_5]
//! [setup_6]
    extint_chan_enable_callback(15, EXTINT_CALLBACK_TYPE_DETECT);
//! [setup_6]
}

//! [setup_7]
void extint_detection_callback(void)
{
    bool pin_state = port_pin_get_input_level(PIN_PA15);
    port_pin_set_output_level(PIN_PB30, pin_state);
}

static struct rt_semaphore _rx_sem;

static rt_err_t _rx_ind(rt_device_t dev, rt_size_t size)
{
    return rt_sem_release(&_rx_sem);
}

void rt_init_thread_entry(void* parameter)
{
    rt_thread_t thread;
    rt_device_t dev;

    rt_kprintf("SYSTEM running at %uhz\n", SystemCoreClock);

#ifdef RT_USING_FINSH
    /* init finsh */
    finsh_system_init();
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    finsh_set_device("uart1");
#endif
#endif

    LED_Init();
    configure_extint_channel();
    configure_extint_callbacks();

    sleep_timer_init();
    // sleep_timer_start(1500);

    while (1)
    {
        rt_kprintf("init thread running tick:%u\n", rt_tick_get());
        rt_thread_delay(2*RT_TICK_PER_SECOND);
    }
}

int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init", rt_init_thread_entry, RT_NULL,
                            512, RT_THREAD_PRIORITY_MAX / 3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

