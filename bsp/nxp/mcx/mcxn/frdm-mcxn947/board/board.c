/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * Copyright (c) 2019-2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-29     yandld      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "clock_config.h"
#include "pin_mux.h"
#include "drv_uart.h"
#include "fsl_port.h"
#include "fsl_cache_lpcac.h"

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

/**
 * This function will initial the FlexComm mode.
 * +--------+----------------+--------+--------+--------------+
 * | Signal | LPSPI          | LPUART | LPI2C  | LPUART+LPI2C |
 * +--------+----------------+--------+--------+--------------+
 * |  FC_P0 | SDO/DATA[0]    | RXD    | SDA    | SDA          |
 * |  FC_P1 | SCK            | TXD    | SCL    | SCL          |
 * |  FC_P2 | SDI/DATA[1]    | RTS_b  | SCLS   | TXD          |
 * |  FC_P3 | PCS[0]         | CTS_b  | SDAS   | RXD          |
 * |  FC_P4 | PCS[3]/DATA[3] | DSR_b  | HREQ_b | CTS_b        |
 * |  FC_P5 | PCS[2]/DATA[2] | DTR_b  | —      | RTS_b        |
 * |  FC_P6 | PCS[1]/HREQ    | DCD_b  | —      | HREQ_b       |
 * +--------+----------------+--------+--------+--------------+
 */
void rt_hw_flexcomm_mode_init(void)
{
#ifdef BSP_USING_UART2
    LP_FLEXCOMM_Init(2, LP_FLEXCOMM_PERIPH_LPI2CAndLPUART); /* FLEXCOMM2 used for LPI2C and LPUART */
#endif
#ifdef BSP_USING_UART4
    LP_FLEXCOMM_Init(4, LP_FLEXCOMM_PERIPH_LPUART); /* FLEXCOMM4 used for LPUART */
#endif
#ifdef BSP_USING_UART5
    LP_FLEXCOMM_Init(5, LP_FLEXCOMM_PERIPH_LPUART); /* FLEXCOMM5 used for LPUART */
#endif
#ifdef BSP_USING_UART6
    LP_FLEXCOMM_Init(6, LP_FLEXCOMM_PERIPH_LPUART); /* FLEXCOMM6 used for LPUART */
    #endif
#ifdef BSP_USING_SPI1
    LP_FLEXCOMM_Init(2, LP_FLEXCOMM_PERIPH_LPSPI); /* FLEXCOMM2 used for LPI2C and LPUART */
#endif
#ifdef BSP_USING_SPI3
    LP_FLEXCOMM_Init(3, LP_FLEXCOMM_PERIPH_LPSPI); /* FLEXCOMM3 used for LPSPI */
#endif
#ifdef BSP_USING_SPI6
    LP_FLEXCOMM_Init(6, LP_FLEXCOMM_PERIPH_LPSPI); /* FLEXCOMM6 used for LPSPI */
#endif
#ifdef BSP_USING_SPI7
    LP_FLEXCOMM_Init(7, LP_FLEXCOMM_PERIPH_LPSPI); /* FLEXCOMM7 used for LPSPI */
#endif
#ifdef BSP_USING_I2C0
    LP_FLEXCOMM_Init(0, LP_FLEXCOMM_PERIPH_LPI2C); /* FLEXCOMM0 used for LPI2C */
#endif
#ifdef BSP_USING_I2C1
    LP_FLEXCOMM_Init(1, LP_FLEXCOMM_PERIPH_LPI2C); /* FLEXCOMM1 used for LPI2C */
#endif
#ifdef BSP_USING_I2C2
    LP_FLEXCOMM_Init(2, LP_FLEXCOMM_PERIPH_LPI2C); /* FLEXCOMM2 used for LPI2C */
#endif
}

/**
 * This function will initial board.
 */
void rt_hw_board_init()
{
    /* Hardware Initialization */
    BOARD_InitBootPins();
    L1CACHE_EnableCodeCache();

    CLOCK_EnableClock(kCLOCK_Freqme);
    CLOCK_EnableClock(kCLOCK_InputMux);

    CLOCK_EnableClock(kCLOCK_Port0);
    CLOCK_EnableClock(kCLOCK_Port1);
    CLOCK_EnableClock(kCLOCK_Port2);
    CLOCK_EnableClock(kCLOCK_Port3);
    CLOCK_EnableClock(kCLOCK_Port4);

    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    CLOCK_EnableClock(kCLOCK_Gpio2);
    CLOCK_EnableClock(kCLOCK_Gpio3);
    CLOCK_EnableClock(kCLOCK_Gpio4);

    CLOCK_EnableClock(kCLOCK_Pint);
    CLOCK_EnableClock(kCLOCK_Flexcan0);
    CLOCK_EnableClock(kCLOCK_Flexcan1);

    CLOCK_AttachClk(kFRO_HF_to_ADC0);
    CLOCK_SetClkDiv(kCLOCK_DivAdc0Clk, 1u);

    /* enable VREF */
    SPC0->ACTIVE_CFG1 |= 0xFFFFFFFF;

    CLOCK_EnableClock(kCLOCK_Dma0);
    CLOCK_EnableClock(kCLOCK_Dma1);

    edma_config_t userConfig = {0};
    EDMA_GetDefaultConfig(&userConfig);
    EDMA_Init(DMA0, &userConfig);
    EDMA_Init(DMA1, &userConfig);

    /* This init has finished in secure side of TF-M  */
    BOARD_InitBootClocks();

    CLOCK_SetupClk16KClocking(kCLOCK_Clk16KToAll);

    CLOCK_AttachClk(kPLL0_to_CTIMER0);
    CLOCK_AttachClk(kPLL0_to_CTIMER1);
    CLOCK_AttachClk(kPLL0_to_CTIMER2);
    CLOCK_AttachClk(kPLL0_to_CTIMER3);
    CLOCK_AttachClk(kPLL0_to_CTIMER4);
    CLOCK_SetClkDiv(kCLOCK_DivCtimer0Clk, 1u);
    CLOCK_SetClkDiv(kCLOCK_DivCtimer1Clk, 1u);
    CLOCK_SetClkDiv(kCLOCK_DivCtimer2Clk, 1u);
    CLOCK_SetClkDiv(kCLOCK_DivCtimer3Clk, 1u);
    CLOCK_SetClkDiv(kCLOCK_DivCtimer4Clk, 1u);

    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    /* set pend exception priority */
    NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    /*init uart device*/
    rt_hw_uart_init();

#if defined(BSP_USING_LEDG_PWM) && defined(BSP_USING_PWM)
    PORT_SetPinMux(PORT0, 27, kPORT_MuxAlt4);
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization board with RT-Thread Components */
    rt_components_board_init();
#endif

#ifdef RT_USING_HEAP
    rt_kprintf("sram heap, begin: 0x%p, end: 0x%p\n", HEAP_BEGIN, HEAP_END);
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)(HEAP_END));
#endif
}

/**
 * This function will called when memory fault.
 */
void MemManage_Handler(void)
{
    extern void HardFault_Handler(void);

    rt_kprintf("Memory Fault!\n");
    HardFault_Handler();
}

void rt_hw_us_delay(rt_uint32_t us)
{
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
}
