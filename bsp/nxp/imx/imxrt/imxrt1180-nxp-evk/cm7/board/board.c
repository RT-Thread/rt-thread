/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2022-08-15     xjy198903    add sdram pin config
 * 2022-08-17     xjy198903    add rgmii pins
 * 2022-09-01     xjy198903    add can pins
 * 2022-09-07     xjy198903    add sdio pins
 * 2022-09-14     xjy198903    add flexspi pins
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"
#include "fsl_rgpio.h"
#include "fsl_cache.h"

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
    /* RW_m_ncache_aux is a auxiliary region which is used to get the whole size of noncache section */
    extern uint32_t Image$$RW_m_ncache_aux$$Base[];
    uint32_t nonCacheStart = (uint32_t)Image$$RW_m_ncache$$Base;
    uint32_t nonCacheSize  = ((uint32_t)Image$$RW_m_ncache_aux$$Base) - nonCacheStart;
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_NCACHE_REGION;
    extern uint32_t __top_NCACHE_REGION;
    uint32_t nonCacheStart = (uint32_t)(&__base_NCACHE_REGION);
    uint32_t nonCacheSize  = (uint32_t)(&__top_NCACHE_REGION) - nonCacheStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __NCACHE_REGION_START[];
    extern uint32_t __NCACHE_REGION_SIZE[];
    uint32_t nonCacheStart = (uint32_t)__NCACHE_REGION_START;
    uint32_t nonCacheSize  = (uint32_t)__NCACHE_REGION_SIZE;
#endif
#if defined(__USE_SHMEM)
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$RPMSG_SH_MEM$$Base[];
    /* RPMSG_SH_MEM_aux is a auxiliary region which is used to get the whole size of RPMSG_SH_MEM section */
    extern uint32_t Image$$RPMSG_SH_MEM_aux$$Base[];
    uint32_t rpmsgShmemStart = (uint32_t)Image$$RPMSG_SH_MEM$$Base;
    uint32_t rpmsgShmemSize  = ((uint32_t)Image$$RPMSG_SH_MEM_aux$$Base) - rpmsgShmemStart;
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_SHMEM_REGION;
    extern uint32_t __top_SHMEM_REGION;
    uint32_t rpmsgShmemStart = (uint32_t)(&__base_SHMEM_REGION);
    uint32_t rpmsgShmemSize  = (uint32_t)(&__top_SHMEM_REGION) - rpmsgShmemStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __RPMSG_SH_MEM_START[];
    extern uint32_t __RPMSG_SH_MEM_SIZE[];
    uint32_t rpmsgShmemStart = (uint32_t)__RPMSG_SH_MEM_START;
    uint32_t rpmsgShmemSize  = (uint32_t)__RPMSG_SH_MEM_SIZE;
#endif
#endif
    volatile uint32_t i;

    /* Disable I cache and D cache */
    L1CACHE_DisableICache();
    L1CACHE_DisableDCache();

    /* Disable MPU */
    ARM_MPU_Disable();

    /* clang-format off */

    /* MPU configure:
     * Use ARM_MPU_RASR(DisableExec, AccessPermission, TypeExtField, IsShareable, IsCacheable, IsBufferable, SubRegionDisable, Size)
     * API in mpu_armv7.h.
     * param DisableExec       Instruction access (XN) disable bit,0=instruction fetches enabled, 1=instruction fetches disabled.
     * param AccessPermission  Data access permissions, allows you to configure read/write access for User and Privileged mode.
     *                         Use MACROS defined in mpu_armv7.h:
     *                         ARM_MPU_AP_NONE/ARM_MPU_AP_PRIV/ARM_MPU_AP_URO/ARM_MPU_AP_FULL/ARM_MPU_AP_PRO/ARM_MPU_AP_RO
     *
     * Combine TypeExtField/IsShareable/IsCacheable/IsBufferable to configure MPU memory access attributes.
     *  TypeExtField  IsShareable  IsCacheable  IsBufferable   Memory Attribute    Shareability        Cache
     *     0             x           0           0             Strongly Ordered    shareable
     *     0             x           0           1              Device             shareable
     *     0             0           1           0              Normal             not shareable   Outer and inner write
     *                                                                                             through no write allocate
     *     0             0           1           1              Normal             not shareable   Outer and inner write
     *                                                                                             back no write allocate
     *     0             1           1           0              Normal             shareable       Outer and inner write
     *                                                                                             through no write allocate
     *     0             1           1           1              Normal             shareable       Outer and inner write
     *                                                                                             back no write allocate
     *     1             0           0           0              Normal             not shareable   outer and inner
     *                                                                                             noncache
     *     1             1           0           0              Normal             shareable       outer and inner
     *                                                                                             noncache
     *     1             0           1           1              Normal             not shareable   outer and inner write
     *                                                                                             back write/read acllocate
     *     1             1           1           1              Normal             shareable       outer and inner write
     *                                                                                             back write/read acllocate
     *     2             x           0           0              Device             not shareable
     *   Above are normal use settings, if your want to see more details or want to config different inner/outer cache
     * policy, please refer to Table 4-55 /4-56 in arm cortex-M7 generic user guide <dui0646b_cortex_m7_dgug.pdf>
     *
     * param SubRegionDisable  Sub-region disable field. 0=sub-region is enabled, 1=sub-region is disabled.
     * param Size              Region size of the region to be configured. use ARM_MPU_REGION_SIZE_xxx MACRO in mpu_armv7.h.
     */

    /* clang-format on */

    /*
     * Add default region to deny access to whole address space to workaround speculative prefetch.
     * Refer to Arm errata 1013783-B for more details.
     */

    /* Region 0 setting: Instruction access disabled, No data access permission. */
    MPU->RBAR = ARM_MPU_RBAR(0, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(1, ARM_MPU_AP_NONE, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_4GB);

    /* Region 1 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 3 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_2GB);

    /* Region 4 setting: Memory with Normal type, not shareable, outer/inner write back */ /*ITCM*/
    MPU->RBAR = ARM_MPU_RBAR(4, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

    /* Region 5 setting: Memory with Normal type, not shareable, outer/inner write back */ /*DTCM*/
    MPU->RBAR = ARM_MPU_RBAR(5, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

    MPU->RBAR = ARM_MPU_RBAR(6, 0x20480000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write through */ /*OCRAM1*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_512KB);
#else
    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write back */ /*OCRAM1*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_512KB);
#endif

    MPU->RBAR = ARM_MPU_RBAR(7, 0x20500000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write through */ /*OCRAM2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_256KB);
#else
    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write back */ /*OCRAM2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);
#endif

#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    /* Region 8 setting: Memory with Normal type, not shareable, outer/inner write back. */ /*FSPI1*/
    MPU->RBAR = ARM_MPU_RBAR(8, 0x28000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_RO, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_16MB);
#endif

#if defined(USE_HYPERRAM)
    MPU->RBAR = ARM_MPU_RBAR(9, 0x04000000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 9 setting: Memory with Normal type, not shareable, outer/inner write through. */ /*FSPI2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_8MB);
#else
    /* Region 9 setting: Memory with Normal type, not shareable, outer/inner write back. */ /*FSPI2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_8MB);
#endif
#endif

#if defined(USE_SDRAM)
    MPU->RBAR = ARM_MPU_RBAR(10, 0x80000000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 10 setting: Memory with Normal type, not shareable, outer/inner write through */
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_64MB);
#else
    /* Region 10 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_64MB);
#endif
#endif

    i = 0;
    while ((nonCacheSize >> i) > 0x1U)
    {
        i++;
    }

    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert(!(nonCacheStart % nonCacheSize));
        assert(nonCacheSize == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Region 11 setting: Memory with Normal type, not shareable, non-cacheable */
        MPU->RBAR = ARM_MPU_RBAR(11, nonCacheStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, i - 1);
    }

#if defined(__USE_SHMEM)
    i = 0;
    while ((rpmsgShmemSize >> i) > 0x1U)
    {
        i++;
    }

    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert(!(rpmsgShmemStart % rpmsgShmemSize));
        assert(rpmsgShmemSize == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Region 12 setting: Memory with Normal type, not shareable, non-cacheable */
        MPU->RBAR = ARM_MPU_RBAR(12, rpmsgShmemStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, i - 1);
    }
#endif

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk);

    /* Enable I cache and D cache */
    L1CACHE_EnableDCache();
    L1CACHE_EnableICache();
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



void imxrt_uart_pins_init(void)
{
#ifdef BSP_USING_LPUART1

  CLOCK_EnableClock(kCLOCK_Iomuxc2);          /* Turn on LPCG: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AON_08_LPUART1_TX,          /* GPIO_AON_08 is configured as LPUART1_TX */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AON_09_LPUART1_RX,          /* GPIO_AON_09 is configured as LPUART1_RX */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AON_08_LPUART1_TX,          /* GPIO_AON_08 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: high driver
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_AON_09_LPUART1_RX,          /* GPIO_AON_09 PAD functional properties : */
      0x02U);                                 /* Slew Rate Field: Fast Slew Rate
                                                 Drive Strength Field: high driver
                                                 Pull / Keep Select Field: Pull Disable, Highz
                                                 Pull Up / Down Config. Field: Weak pull down
                                                 Open Drain Field: Disabled */

#endif
}
	
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

#ifdef BSP_USING_SDRAM
   imxrt_sdram_pins_init();
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

#ifdef BSP_USING_SDIO
    imxrt_SDcard_pins_init();
#endif

#ifdef BSP_USING_ETH
    imxrt_eth_pins_init();
#endif

#ifdef BSP_USING_CAN
    imxrt_can_pins_init();
#endif

#ifdef BSP_USING_FLEXSPI
    imxrt_flexspi_pins_init();
#endif


}

