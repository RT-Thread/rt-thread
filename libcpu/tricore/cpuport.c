/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/02/01     BalanceTWK   The unify TriCore porting code.
 */

#include <rthw.h>
#include <rtthread.h>

#include "cpuport.h"

static IfxStm_Timer tricore_timers[2];
static volatile Ifx_STM *const STMs[2] = {&MODULE_STM0, &MODULE_STM1};
static volatile Ifx_SRC_SRCR *const GPSR[2] = {&SRC_GPSR_GPSR0_SR0, &SRC_GPSR_GPSR1_SR0};

static volatile rt_ubase_t current_thread = RT_NULL;
static volatile rt_ubase_t to_thread = RT_NULL;
static volatile rt_ubase_t systick_flag = RT_NULL;

rt_base_t rt_hw_interrupt_disable(void)
{
    rt_base_t level;
    level = IfxCpu_disableInterrupts();
    return level;
}

void rt_hw_interrupt_enable(rt_base_t level)
{
    restoreInterrupts((boolean)level);
}

void rt_hw_systick_init( void )
{
  IfxStm_Timer_Config timer_config;
  IfxStm_Timer_initConfig(&timer_config, STMs[TRICORE_CPU_ID]);

  timer_config.base.frequency = RT_TICK_PER_SECOND;
  timer_config.base.isrPriority = 1;
  IfxStm_Timer_init(&tricore_timers[TRICORE_CPU_ID], &timer_config);
  IfxStm_Timer_run(&tricore_timers[TRICORE_CPU_ID]);
}

inline void trigger_scheduling(void)
{
    rt_ubase_t from, to;
    rt_base_t level;

    unsigned long *current_upper_csa = NULL;

    level = rt_hw_interrupt_disable();
    from = current_thread;
    to = to_thread;
    to_thread = RT_NULL;
    rt_hw_interrupt_enable(level);

    if( to )
    {
        __disable();
        __dsync();

        current_upper_csa = LINKWORD_TO_ADDRESS( __mfcr( CPU_PCXI ) );

        *( (unsigned long *)from ) = current_upper_csa[ 0 ];

        current_upper_csa[ 0 ] = *( (unsigned long *)to );
        GPSR[TRICORE_CPU_ID]->B.SETR = 0;
        __isync();
    }
}

__attribute__((noinline)) static void tricore_systick_handler( void )
{
    IfxStm_Timer_acknowledgeTimerIrq(&tricore_timers[TRICORE_CPU_ID]);

    systick_flag = 1;
    rt_tick_increase();
    systick_flag = 0;

    trigger_scheduling();
}

IFX_INTERRUPT(KERNEL_INTERRUPT, 0, 1)
{
    tricore_systick_handler();
}

void tricore_trap_yield_for_task( int iTrapIdentification )
{
  switch( iTrapIdentification )
  {
    case 0:
        trigger_scheduling();
      break;

    default:
      /* Unimplemented trap called. */
      /* TODO */
      break;
  }
}

__attribute__((noinline)) static void tricore_yield_for_interrupt( void )
{
    trigger_scheduling();
}

IFX_INTERRUPT(KERNEL_YIELD, 0, 2)
{
    tricore_yield_for_interrupt();
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
    /* USART driver initialization is open by default */
#ifdef RT_USING_SERIAL
    rt_hw_usart_init();
#endif

    /* Set the shell console output device */
#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Board underlying hardware initialization */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    current_thread = from;
    to_thread = to;
    rt_hw_interrupt_enable(level);
    if(systick_flag == 0)
    {
        __syscall( 0 );
    }
}

void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    current_thread = from;
    to_thread = to;
    rt_hw_interrupt_enable(level);

    GPSR[TRICORE_CPU_ID]->B.SETR = 1;
    __isync();
}

void rt_hw_context_switch_to(rt_ubase_t to)
{
    unsigned long ulMFCR = 0UL;
    unsigned long *lower_csa = NULL;
    unsigned long *upper_csa = NULL;

    /* Set-up the timer interrupt. */
    rt_hw_systick_init();

    IfxSrc_init(GPSR[TRICORE_CPU_ID], (IfxSrc_Tos)TRICORE_CPU_ID, 1);
    IfxSrc_enable(GPSR[TRICORE_CPU_ID]);

    __disable();

    /* Load the initial SYSCON. */
    __mtcr( CPU_SYSCON, TRICORE_INITIAL_SYSCON );
    __isync();

    ulMFCR = __mfcr( CPU_PSW );
    ulMFCR &= TRICORE_RESTORE_PSW_MASK;
    __dsync();
    __mtcr( CPU_PSW, ulMFCR );
    __isync();

    /* Finally, perform the equivalent of a portRESTORE_CONTEXT() */
    lower_csa = LINKWORD_TO_ADDRESS( *( (unsigned long *)to ) );
    upper_csa = LINKWORD_TO_ADDRESS( lower_csa[0] );
    __dsync();
    __mtcr(CPU_PCXI, (unsigned long)( *( (unsigned long *)to ) ) );
    __isync();
    __nop();
    __rslcx();
    __nop();

    /* Return to the first task selected to execute. */
    __asm volatile( "rfe" );

    /* Will not get here. */
}

/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    unsigned long *lower_csa = NULL;
    unsigned long *upper_csa = NULL;

    rt_hw_interrupt_disable();
    {
        /* DSync to ensure that buffering is not a problem. */
        __dsync();
        /* Consume two free CSAs. */
        lower_csa = LINKWORD_TO_ADDRESS( __mfcr( CPU_FCX ) );
        if( NULL != lower_csa )
        {
            /* The Lower Links to the Upper. */
            upper_csa = LINKWORD_TO_ADDRESS( lower_csa[ 0 ] );
        }
        /* Check that we have successfully reserved two CSAs. */
        if( ( NULL != lower_csa ) && ( NULL != upper_csa ) )
        {
            /* Remove the two consumed CSAs from the free CSA list. */
            __disable();
            __dsync();
            __mtcr( CPU_FCX, upper_csa[ 0 ] );
            __isync();
            __enable();
        }
        else
        {
            /* Simply trigger a context list depletion trap. */
            __svlcx();
        }
    }
    rt_hw_interrupt_enable((rt_base_t)RT_NULL);
    /* Clear the upper CSA. */
    memset( upper_csa, 0, TRICORE_NUM_WORDS_IN_CSA * sizeof( unsigned long ) );
    /* Upper Context. */
    upper_csa[ 2 ] = ( unsigned long )stack_addr;       /* A10; Stack Return aka Stack Pointer */
    upper_csa[ 1 ] = TRICORE_SYSTEM_PROGRAM_STATUS_WORD;      /* PSW  */

    /* Clear the lower CSA. */
    memset( lower_csa, 0, TRICORE_NUM_WORDS_IN_CSA * sizeof( unsigned long ) );
    /* Lower Context. */
    lower_csa[ 8 ] = ( unsigned long ) parameter;      /* A4;  Address Type Parameter Register */
    lower_csa[ 1 ] = ( unsigned long ) tentry;         /* A11; Return Address aka RA */
    /* PCXI pointing to the Upper context. */
    lower_csa[ 0 ] = ( TRICORE_INITIAL_PCXI_UPPER_CONTEXT_WORD | ( unsigned long ) ADDRESS_TO_LINKWORD( upper_csa ) );
    /* Save the link to the CSA in the top of stack. */
    stack_addr = (unsigned long * ) ADDRESS_TO_LINKWORD( lower_csa );
    /* DSync to ensure that buffering is not a problem. */
    __dsync();

    return stack_addr;
}

