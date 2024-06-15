/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-7      SummerGift   first version
 */

#include <drv_common.h>
#include <bsp_api.h>
#include "board.h"

#ifdef RT_USING_PIN
    #include <drv_gpio.h>
#endif

#ifdef RT_USING_SERIAL
    #ifdef RT_USING_SERIAL_V2
        #include <drv_usart_v2.h>
    #else
    #error "Serial-v1 has been obsoleted, and please select serial-v2 as the default option"
    #endif
#endif

#ifdef SOC_SERIES_R9A07G0
#include "gicv3.h"
static uint64_t rtt_timer_delay;
extern fsp_vector_t g_sgi_ppi_vector_table[BSP_CORTEX_VECTOR_TABLE_ENTRIES];
static void SysTimerInterrupt(void);
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
#ifdef SOC_SERIES_R9A07G0
    return;
#else
    NVIC_SystemReset();
#endif
}
MSH_CMD_EXPORT(reboot, Reboot System);
#endif /* RT_USING_FINSH */

/* SysTick configuration */
void rt_hw_systick_init(void)
{
#ifdef SOC_SERIES_R9A07G0
    SysTimerInterrupt();
#else
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    NVIC_SetPriority(SysTick_IRQn, 0xFF);
#endif
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

#ifdef SOC_SERIES_R9A07G0
    __set_CNTP_CVAL(__get_CNTP_CVAL() + rtt_timer_delay);
#endif

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char *s, int num)
{
    /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while (1)
    {
    }
    /* USER CODE END Error_Handler */
}

/**
 * This function will delay for some us.
 *
 * @param us the delay time of us
 */
void rt_hw_us_delay(rt_uint32_t us)
{
#ifdef ARCH_ARM_CORTEX_M
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
#endif
}

#ifdef SOC_SERIES_R9A07G0
static void SysTimerInterrupt(void)
{
    uint64_t tempCNTPCT = __get_CNTPCT();

    /* Wait for counter supply */
    while (__get_CNTPCT() == tempCNTPCT)
    {
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
    }

    /* generic timer initialize */
    /* set interrupt handler */
    g_sgi_ppi_vector_table[(int32_t) BSP_VECTOR_NUM_OFFSET +
                           NonSecurePhysicalTimerInt] = SysTick_Handler;

    rtt_timer_delay = R_GSC->CNTFID0 / RT_TICK_PER_SECOND;

    /* set timer expiration from current counter value */
    __set_CNTP_CVAL(__get_CNTPCT() + rtt_timer_delay);

    /* configure CNTP_CTL to enable timer interrupts */
    __set_CNTP_CTL(1);
    R_BSP_IrqCfgEnable(NonSecurePhysicalTimerInt, (int32_t) BSP_VECTOR_NUM_OFFSET +
                           NonSecurePhysicalTimerInt, RT_NULL);
}
#endif

/**
 * This function will initial board.
 */
rt_weak void rt_hw_board_init()
{
#ifdef SOC_SERIES_R9A07G0
    /* initialize hardware interrupt */
    rt_uint32_t redis_gic_base = platform_get_gic_dist_base();
    rt_int32_t cpu_id = rt_hw_cpu_id();
    arm_gic_redist_address_set(0, redis_gic_base, cpu_id);
    rt_hw_interrupt_init();
#endif

    rt_hw_systick_init();

    /* Heap initialization */
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* Pin driver initialization is open by default */
#ifdef RT_USING_PIN
    rt_hw_pin_init();
#endif

    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

FSP_CPP_HEADER
#ifdef SOC_SERIES_R9A07G0
void R_BSP_WarmStart(bsp_warm_start_event_t event) BSP_PLACE_IN_SECTION(".warm_start");
#else
void R_BSP_WarmStart(bsp_warm_start_event_t event);
#endif
FSP_CPP_FOOTER

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart (bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
#endif
