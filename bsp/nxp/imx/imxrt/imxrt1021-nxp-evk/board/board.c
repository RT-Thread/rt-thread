/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
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
void BOARD_ConfigMPU(void)
{
 #if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$RW_m_ncache$$Base[];
    /* RW_m_ncache_unused is a auxiliary region which is used to get the whole size of noncache section */
    extern uint32_t Image$$RW_m_ncache_unused$$Base[];
    extern uint32_t Image$$RW_m_ncache_unused$$ZI$$Limit[];
    uint32_t nonCacheStart = (uint32_t)Image$$RW_m_ncache$$Base;
    uint32_t size          = ((uint32_t)Image$$RW_m_ncache_unused$$Base == nonCacheStart) ?
                        0 :
                        ((uint32_t)Image$$RW_m_ncache_unused$$ZI$$Limit - nonCacheStart);
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_NCACHE_REGION;
    extern uint32_t __top_NCACHE_REGION;
    uint32_t nonCacheStart = (uint32_t)(&__base_NCACHE_REGION);
    uint32_t size          = (uint32_t)(&__top_NCACHE_REGION) - nonCacheStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __NCACHE_REGION_START[];
    extern uint32_t __NCACHE_REGION_SIZE[];
    uint32_t nonCacheStart = (uint32_t)__NCACHE_REGION_START;
    uint32_t size          = (uint32_t)__NCACHE_REGION_SIZE;
#endif
    volatile uint32_t i = 0;

    /* Disable I cache and D cache */
    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
    {
        SCB_DisableICache();
    }
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR))
    {
        SCB_DisableDCache();
    }

    /* Disable MPU */
    ARM_MPU_Disable();

    /* MPU configure:
     * Use ARM_MPU_RASR(DisableExec, AccessPermission, TypeExtField, IsShareable, IsCacheable, IsBufferable,
     * SubRegionDisable, Size)
     * API in mpu_armv7.h.
     * param DisableExec       Instruction access (XN) disable bit,0=instruction fetches enabled, 1=instruction fetches
     * disabled.
     * param AccessPermission  Data access permissions, allows you to configure read/write access for User and
     * Privileged mode.
     *      Use MACROS defined in mpu_armv7.h:
     * ARM_MPU_AP_NONE/ARM_MPU_AP_PRIV/ARM_MPU_AP_URO/ARM_MPU_AP_FULL/ARM_MPU_AP_PRO/ARM_MPU_AP_RO
     * Combine TypeExtField/IsShareable/IsCacheable/IsBufferable to configure MPU memory access attributes.
     *  TypeExtField  IsShareable  IsCacheable  IsBufferable   Memory Attribtue    Shareability        Cache
     *     0             x           0           0             Strongly Ordered    shareable
     *     0             x           0           1              Device             shareable
     *     0             0           1           0              Normal             not shareable   Outer and inner write
     * through no write allocate
     *     0             0           1           1              Normal             not shareable   Outer and inner write
     * back no write allocate
     *     0             1           1           0              Normal             shareable       Outer and inner write
     * through no write allocate
     *     0             1           1           1              Normal             shareable       Outer and inner write
     * back no write allocate
     *     1             0           0           0              Normal             not shareable   outer and inner
     * noncache
     *     1             1           0           0              Normal             shareable       outer and inner
     * noncache
     *     1             0           1           1              Normal             not shareable   outer and inner write
     * back write/read acllocate
     *     1             1           1           1              Normal             shareable       outer and inner write
     * back write/read acllocate
     *     2             x           0           0              Device              not shareable
     *  Above are normal use settings, if your want to see more details or want to config different inner/outter cache
     * policy.
     *  please refer to Table 4-55 /4-56 in arm cortex-M7 generic user guide <dui0646b_cortex_m7_dgug.pdf>
     * param SubRegionDisable  Sub-region disable field. 0=sub-region is enabled, 1=sub-region is disabled.
     * param Size              Region size of the region to be configured. use ARM_MPU_REGION_SIZE_xxx MACRO in
     * mpu_armv7.h.
     */

    /*
     * Add default region to deny access to whole address space to workaround speculative prefetch.
     * Refer to Arm errata 1013783-B for more details.
     *
     */
    /* Region 0 setting: Instruction access disabled, No data access permission. */
    MPU->RBAR = ARM_MPU_RBAR(0, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(1, ARM_MPU_AP_NONE, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_4GB);

    /* Region 1 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 2 setting: Memory with Device type, not shareable,  non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(2, 0x60000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    /* Region 3 setting: Memory with Normal type, not shareable, outer/inner write back. */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x60000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_RO, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_8MB);
#endif

    /* Region 4 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(4, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    /* Region 5 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(5, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_64KB);

    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(6, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_64KB);

    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(7, 0x20200000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_128KB);

    /* Region 8 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(8, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_32MB);

    while ((size >> i) > 0x1U)
    {
        i++;
    }

    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert(!(nonCacheStart % size));
        assert(size == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Region 9 setting: Memory with Normal type, not shareable, non-cacheable */
        MPU->RBAR = ARM_MPU_RBAR(9, nonCacheStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, i - 1);
    }

    /* Region 10 setting: Memory with Device type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(10, 0x40000000);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_4MB);

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
#ifdef BSP_USING_ETH
void imxrt_enet_pins_init(void)
{
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,        /* GPIO_AD_B0_04 is configured as GPIO1_IO04 */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
                                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_08_ENET_REF_CLK1,     /* GPIO_AD_B0_08 is configured as ENET_REF_CLK1 */
          1U);                                    /* Software Input On Field: Force input path of pad GPIO_AD_B0_08 */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_09_ENET_RDATA01,      /* GPIO_AD_B0_09 is configured as ENET_RDATA01 */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_10_ENET_RDATA00,      /* GPIO_AD_B0_10 is configured as ENET_RDATA00 */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_11_ENET_RX_EN,        /* GPIO_AD_B0_11 is configured as ENET_RX_EN */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_12_ENET_RX_ER,        /* GPIO_AD_B0_12 is configured as ENET_RX_ER */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_13_ENET_TX_EN,        /* GPIO_AD_B0_13 is configured as ENET_TX_EN */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_14_ENET_TDATA00,      /* GPIO_AD_B0_14 is configured as ENET_TDATA00 */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B0_15_ENET_TDATA01,      /* GPIO_AD_B0_15 is configured as ENET_TDATA01 */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_AD_B1_06_GPIO1_IO22,        /* GPIO_AD_B1_06 is configured as GPIO1_IO22 */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_EMC_40_ENET_MDIO,           /* GPIO_EMC_40 is configured as ENET_MDIO */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
          IOMUXC_GPIO_EMC_41_ENET_MDC,            /* GPIO_EMC_41 is configured as ENET_MDC */
          0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_04_GPIO1_IO04,        /* GPIO_AD_B0_04 PAD functional properties : */
          0xB0A9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: medium(100MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_08_ENET_REF_CLK1,     /* GPIO_AD_B0_08 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_09_ENET_RDATA01,      /* GPIO_AD_B0_09 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_10_ENET_RDATA00,      /* GPIO_AD_B0_10 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_11_ENET_RX_EN,        /* GPIO_AD_B0_11 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_12_ENET_RX_ER,        /* GPIO_AD_B0_12 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_13_ENET_TX_EN,        /* GPIO_AD_B0_13 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_14_ENET_TDATA00,      /* GPIO_AD_B0_14 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B0_15_ENET_TDATA01,      /* GPIO_AD_B0_15 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_AD_B1_06_GPIO1_IO22,        /* GPIO_AD_B1_06 PAD functional properties : */
          0xB0A9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: medium(100MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_EMC_40_ENET_MDIO,           /* GPIO_EMC_40 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
    IOMUXC_SetPinConfig(
          IOMUXC_GPIO_EMC_41_ENET_MDC,            /* GPIO_EMC_41 PAD functional properties : */
          0xB0E9U);                               /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: R0/5
                                                     Speed Field: max(200MHz)
                                                     Open Drain Enable Field: Open Drain Disabled
                                                     Pull / Keep Enable Field: Pull/Keeper Enabled
                                                     Pull / Keep Select Field: Pull
                                                     Pull Up / Down Config. Field: 100K Ohm Pull Up
                                                     Hyst. Enable Field: Hysteresis Disabled */
}

#ifndef BSP_USING_PHY
void imxrt_enet_phy_reset_by_gpio(void)
{
    gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    GPIO_PinInit(GPIO1, 9, &gpio_config);
    GPIO_PinInit(GPIO1, 10, &gpio_config);
    /* pull up the ENET_INT before RESET. */
    GPIO_WritePinOutput(GPIO1, 10, 1);
    GPIO_WritePinOutput(GPIO1, 9, 0);
    rt_thread_delay(100);
    GPIO_WritePinOutput(GPIO1, 9, 1);
}
#endif /* BSP_USING_PHY */

#endif /* BSP_USING_ETH */

#ifdef BSP_USING_PHY
void imxrt_phy_pins_init( void )
{
//    IOMUXC_SetPinMux(
//        IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, /* GPIO_AD_B0_09 is configured as GPIO1_IO09 */
//        0U);                             /* Software Input On Field: Input Path is determined by functionality */
//    IOMUXC_SetPinConfig(
//        IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, /* GPIO_B0_00 PAD functional properties : */
//        0x10B0u);                        /* Slew Rate Field: Slow Slew Rate
//                                                 Drive Strength Field: R0/6
//                                                 Speed Field: medium(100MHz)
//                                                 Open Drain Enable Field: Open Drain Disabled
//                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
//                                                 Pull / Keep Select Field: Keeper
//                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
//                                                 Hyst. Enable Field: Hysteresis Disabled */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_B0_04_GPIO1_IO04, /* GPIO_AD_B0_09 is configured as GPIO1_IO09 */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AD_B0_04_GPIO1_IO04, /* GPIO_B0_00 PAD functional properties : */
        0x10B0u);                        /* Slew Rate Field: Slow Slew Rate
                                                 Drive Strength Field: R0/6
                                                 Speed Field: medium(100MHz)
                                                 Open Drain Enable Field: Open Drain Disabled
                                                 Pull / Keep Enable Field: Pull/Keeper Enabled
                                                 Pull / Keep Select Field: Keeper
                                                 Pull Up / Down Config. Field: 100K Ohm Pull Down
                                                 Hyst. Enable Field: Hysteresis Disabled */
}
#endif /* BSP_USING_PHY */




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

#ifdef BSP_USING_DMA
    imxrt_dma_init();
#endif

#ifdef BSP_USING_ETH
    imxrt_enet_pins_init();
#endif

#ifdef BSP_USING_PHY
    imxrt_phy_pins_init();
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




