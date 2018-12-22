#include <rtthread.h>
#include <rthw.h>

#include "gd_int.h"
#include "gd_gpio.h"
#include "gd_timer.h"
#include "drv_uart.h"
#include "gpio_cfg.h"
#include "board.h"
#include "drv_flash.h"
#include "gh_debug_rct.h"

#ifdef RT_USING_I2C
#include "drv_i2c.h"
#endif

#ifdef RT_USING_SPI
#include "drv_ssi.h"
#endif

#ifdef RT_USING_WDT
#include "drv_wdt.h"
#endif

#ifdef RT_USING_GK_DMA
#include "drv_dma.h"
#endif

#ifdef RT_USING_ADC
#include "drv_adc.h"
#endif

#ifdef RT_USING_PWM
#include "drv_pwm.h"
#endif
#include "rtos_lib.h"

extern unsigned char __heap_start__[];
extern unsigned char __heap_end__[];
extern unsigned char __nocache_buffer_start__[];

/**
 * This function will init goke board
 */
void rt_hw_board_init(void)
{
    rt_uint32_t code_seg_size = 0;
    rt_uint32_t heap_seg_size = 0;
    rt_uint32_t os_end_address=0;

    GD_TIMER_INIT_PARAMS_S gdTimerParams;
    GD_GPIO_XREF_S gdGpioXrefTable[] = { SYSTEM_GPIO_XREF_TABLE };
    GD_GPIO_INIT_PARAMS_S gdGpioInitParam =
    {
        .irqPriority = GD_INT_MID_PRIORITY,
        .phyType = 0,
        .xrefTableCount = sizeof(gdGpioXrefTable)/sizeof(gdGpioXrefTable[0]),
        .xrefTable = gdGpioXrefTable,
    };

    gdTimerParams.softTimerReg      = GD_REG_TIMER1;
    gdTimerParams.hardTimerReg      = GD_REG_TIMER2;
    gdTimerParams.gpregTimerReg     = GD_REG_TIMER3;
    gdTimerParams.softTimerpriority  = GD_INT_MID_PRIORITY;
    gdTimerParams.hardTimerpriority  = GD_INT_MID_PRIORITY;
    gdTimerParams.gpregTimerpriority = GD_INT_MID_PRIORITY;

    GD_INT_DisableAllInterrupts();

    // Sensor ioctrl
    GH_PLL_set_IOCTRL_SENSOR(0x00000012);

    GD_INT_Init(NULL);
    GD_TIMER_Init(&gdTimerParams);
    GD_GPIO_Init(&gdGpioInitParam);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize heap memory system */
    code_seg_size = __heap_end__ - __nocache_buffer_start__;
    heap_seg_size = DDR_MEMORY_OS_SIZE - code_seg_size;
    os_end_address= (rt_uint32_t)__heap_end__+heap_seg_size;
    rt_system_heap_init((void*)__heap_end__, (void*)os_end_address);

    /* initialize uart */
    rt_hw_uart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    /* initalize sflash */
    rt_flash_init();

    RTOS_HwTickInit();
}

int rt_board_driver_init(void)
{
#ifdef RT_USING_I2C
    rt_hw_i2c_init();
#endif

#ifdef RT_USING_SPI
    rt_hw_spi_init();
#endif

#ifdef RT_USING_WDT
    rt_hw_wdt_init();
#endif

#ifdef RT_USING_GK_DMA
    rt_gk_dma_init();
#endif

#ifdef RT_USING_ADC
    rt_hw_adc_init();
#endif

#ifdef RT_USING_PWM
    rt_hw_pwm_init();
#endif

    return 0;
}

//static unsigned long nticks = 0;
unsigned long gkosGetTicks(void)
{
    return rt_tick_get();
}

/*@}*/
