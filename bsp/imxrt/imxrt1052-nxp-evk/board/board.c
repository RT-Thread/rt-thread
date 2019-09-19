/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"

#ifdef BSP_USING_DMA
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#endif

#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority
                                                      4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */

/* MPU configuration. */
static void BOARD_ConfigMPU(void)
{
    /* Disable I cache and D cache */
    SCB_DisableICache();
    SCB_DisableDCache();

    /* Disable MPU */
    ARM_MPU_Disable();

    /* Region 0 setting */
    MPU->RBAR = ARM_MPU_RBAR(0, 0xC0000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 1 setting */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    /* Region 2 setting */
    // spi flash: normal type, cacheable, no bufferable, no shareable
    MPU->RBAR = ARM_MPU_RBAR(2, 0x60000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 3 setting */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    /* Region 4 setting */
    MPU->RBAR = ARM_MPU_RBAR(4, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 5 setting */
    MPU->RBAR = ARM_MPU_RBAR(5, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 6 setting */
    MPU->RBAR = ARM_MPU_RBAR(6, 0x20200000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

#if defined(BSP_USING_SDRAM)
    /* Region 7 setting */
    MPU->RBAR = ARM_MPU_RBAR(7, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_32MB);

    /* Region 8 setting */
    MPU->RBAR = ARM_MPU_RBAR(8, 0x81E00000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 1, 0, 0, 0, ARM_MPU_REGION_SIZE_2MB);
#endif

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    /* Enable I cache and D cache */
    SCB_EnableDCache();
    SCB_EnableICache();
}


/* This is the timer interrupt service routine. */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef BSP_USING_DMA
void imxrt_dma_init(void)
{
    edma_config_t config;

    DMAMUX_Init(DMAMUX);
    EDMA_GetDefaultConfig(&config);
    EDMA_Init(DMA0, &config);
}
#endif

#ifdef BSP_USING_LPUART
void imxrt_uart_pins_init(void)
{
#ifdef BSP_USING_LPUART1

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B0_12_LPUART1_TX,        /* GPIO_AD_B0_12 is configured as LPUART1_TX */
            0U);                                    /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B0_13_LPUART1_RX,        /* GPIO_AD_B0_13 is configured as LPUART1_RX */
            0U);                                    /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B0_12_LPUART1_TX,        /* GPIO_AD_B0_12 PAD functional properties : */
            0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                     Drive Strength Field: R0/6
                                                     Speed Field: medium(100MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Keeper
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                     Hyst. Enable Field: Hysteresis Disabled */
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B0_13_LPUART1_RX,        /* GPIO_AD_B0_13 PAD functional properties : */
            0x10B0u);                               /* Slew Rate Field: Slow Slew Rate
                                                     Drive Strength Field: R0/6
                                                     Speed Field: medium(100MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Keeper
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                     Hyst. Enable Field: Hysteresis Disabled */
#endif
#ifdef BSP_USING_LPUART2

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_02_LPUART2_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_03_LPUART2_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_02_LPUART2_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_03_LPUART2_RX,
            0x10B0u);

#endif
#ifdef BSP_USING_LPUART3

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_06_LPUART3_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_07_LPUART3_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_06_LPUART3_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_07_LPUART3_RX,
            0x10B0u);
#endif
#ifdef BSP_USING_LPUART4

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_B1_00_LPUART4_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_B1_01_LPUART4_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_B1_00_LPUART4_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_B1_01_LPUART4_RX,
            0x10B0u);
#endif
#ifdef BSP_USING_LPUART5

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_B1_12_LPUART5_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_B1_13_LPUART5_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_B1_12_LPUART5_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_B1_13_LPUART5_RX,
            0x10B0u);
#endif
#ifdef BSP_USING_LPUART6

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B0_02_LPUART6_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B0_03_LPUART6_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B0_02_LPUART6_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B0_03_LPUART6_RX,
            0x10B0u);
#endif
#ifdef BSP_USING_LPUART7

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_EMC_31_LPUART7_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_EMC_32_LPUART7_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_EMC_31_LPUART7_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_EMC_32_LPUART7_RX,
            0x10B0u);
#endif
#ifdef BSP_USING_LPUART8

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_10_LPUART8_TX,
            0U);
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_B1_11_LPUART8_RX,
            0U);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_10_LPUART8_TX,
            0x10B0u);
        IOMUXC_SetPinConfig(
            IOMUXC_GPIO_AD_B1_11_LPUART8_RX,
            0x10B0u);
#endif
}
#endif /* BSP_USING_LPUART */

/**
 * This function will initial rt1050 board.
 */
void rt_hw_board_init()
{
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

#ifdef BSP_USING_LPUART
    imxrt_uart_pins_init();
#endif

#ifdef BSP_USING_DMA
    imxrt_dma_init();
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

