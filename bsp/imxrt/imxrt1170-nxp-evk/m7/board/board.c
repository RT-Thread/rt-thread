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
#include "fsl_gpio.h"

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
#if defined(__USE_SHMEM)
    extern uint32_t __base_rpmsg_sh_mem;
    extern uint32_t __top_rpmsg_sh_mem;
    uint32_t nonCacheStart = (uint32_t)(&__base_rpmsg_sh_mem);
    uint32_t size          = (uint32_t)(&__top_rpmsg_sh_mem) - nonCacheStart;
#else
    extern uint32_t __base_NCACHE_REGION;
    extern uint32_t __top_NCACHE_REGION;
    uint32_t nonCacheStart = (uint32_t)(&__base_NCACHE_REGION);
    uint32_t size          = (uint32_t)(&__top_NCACHE_REGION) - nonCacheStart;
#endif
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __NCACHE_REGION_START[];
    extern uint32_t __NCACHE_REGION_SIZE[];
    uint32_t nonCacheStart = (uint32_t)__NCACHE_REGION_START;
    uint32_t size          = (uint32_t)__NCACHE_REGION_SIZE;
#endif
    volatile uint32_t i = 0;

#if defined(__ICACHE_PRESENT) && __ICACHE_PRESENT
    /* Disable I cache and D cache */
    if (SCB_CCR_IC_Msk == (SCB_CCR_IC_Msk & SCB->CCR))
    {
        SCB_DisableICache();
    }
#endif
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
    if (SCB_CCR_DC_Msk == (SCB_CCR_DC_Msk & SCB->CCR))
    {
        SCB_DisableDCache();
    }
#endif

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

    /* Region 0 setting: Instruction access disabled, No data access permission. */
    MPU->RBAR = ARM_MPU_RBAR(0, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(1, ARM_MPU_AP_NONE, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_4GB);

    /* Region 1 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 2 setting: Memory with Device type, not shareable,  non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(2, 0x60000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 3 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1GB);

    /* Region 4 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(4, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

    /* Region 5 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(5, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

#if defined(CACHE_MODE_WRITE_THROUGH) && CACHE_MODE_WRITE_THROUGH
    /* Region 6 setting: Memory with Normal type, not shareable, write through */
    MPU->RBAR = ARM_MPU_RBAR(6, 0x20200000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_1MB);

    /* Region 7 setting: Memory with Normal type, not shareable, write trough */
    MPU->RBAR = ARM_MPU_RBAR(7, 0x20300000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_512KB);
#else
    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(6, 0x20200000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_1MB);

    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(7, 0x20300000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_512KB);
#endif

#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    /* Region 8 setting: Memory with Normal type, not shareable, outer/inner write back. */
    MPU->RBAR = ARM_MPU_RBAR(8, 0x30000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_RO, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_16MB);
#endif

#ifdef USE_SDRAM
#if defined(CACHE_MODE_WRITE_THROUGH) && CACHE_MODE_WRITE_THROUGH
    /* Region 9 setting: Memory with Normal type, not shareable, write trough */
    MPU->RBAR = ARM_MPU_RBAR(9, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_64MB);
#else
    /* Region 9 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RBAR = ARM_MPU_RBAR(9, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_64MB);
#endif
#endif

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

        /* Region 10 setting: Memory with Normal type, not shareable, non-cacheable */
        MPU->RBAR = ARM_MPU_RBAR(10, nonCacheStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, i - 1);
    }

    /* Region 11 setting: Memory with Device type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(11, 0x40000000);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_16MB);

    /* Region 12 setting: Memory with Device type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(12, 0x41000000);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_2MB);

    /* Region 13 setting: Memory with Device type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(13, 0x41400000);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1MB);

    /* Region 14 setting: Memory with Device type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(14, 0x41800000);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_2MB);

    /* Region 15 setting: Memory with Device type, not shareable, non-cacheable */
    MPU->RBAR = ARM_MPU_RBAR(15, 0x42000000);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1MB);

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    /* Enable I cache and D cache */
#if defined(__DCACHE_PRESENT) && __DCACHE_PRESENT
    SCB_EnableDCache();
#endif
#if defined(__ICACHE_PRESENT) && __ICACHE_PRESENT
    SCB_EnableICache();
#endif
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


#ifdef BSP_USING_LPUART
void imxrt_uart_pins_init(void)
{
#ifdef BSP_USING_LPUART1

        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_24_LPUART1_TXD,        /* GPIO_AD_B0_12 is configured as LPUART1_TX */
            0U);                                    /* Software Input On Field: Input Path is determined by functionality */
        IOMUXC_SetPinMux(
            IOMUXC_GPIO_AD_25_LPUART1_RXD,        /* GPIO_AD_B0_13 is configured as LPUART1_RX */
            0U);                                    /* Software Input On Field: Input Path is determined by functionality */

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
#ifdef BSP_USING_SDIO
void imxrt_SDcard_pins_init(void)
{
  CLOCK_EnableClock(kCLOCK_Iomuxc);           /* LPCG on: LPCG is ON. */

  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_34_USDHC1_VSELECT,       /* GPIO_AD_34 is configured as USDHC1_VSELECT */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_AD_35_GPIO10_IO02,          /* GPIO_AD_35 is configured as GPIO10_IO02 */
      0U);                                    /* Software Input On Field: Input Path is determined by functionality */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_SD_B1_00_USDHC1_CMD,        /* GPIO_SD_B1_00 is configured as USDHC1_CMD */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_SD_B1_00 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_SD_B1_01_USDHC1_CLK,        /* GPIO_SD_B1_01 is configured as USDHC1_CLK */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_SD_B1_01 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_SD_B1_02_USDHC1_DATA0,      /* GPIO_SD_B1_02 is configured as USDHC1_DATA0 */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_SD_B1_02 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_SD_B1_03_USDHC1_DATA1,      /* GPIO_SD_B1_03 is configured as USDHC1_DATA1 */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_SD_B1_03 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_SD_B1_04_USDHC1_DATA2,      /* GPIO_SD_B1_04 is configured as USDHC1_DATA2 */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_SD_B1_04 */
  IOMUXC_SetPinMux(
      IOMUXC_GPIO_SD_B1_05_USDHC1_DATA3,      /* GPIO_SD_B1_05 is configured as USDHC1_DATA3 */
      1U);                                    /* Software Input On Field: Force input path of pad GPIO_SD_B1_05 */
  IOMUXC_GPR->GPR43 = ((IOMUXC_GPR->GPR43 &
    (~(IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH_MASK))) /* Mask bits to zero which are setting */
      | IOMUXC_GPR_GPR43_GPIO_MUX3_GPIO_SEL_HIGH(0x8000U) /* GPIO3 and CM7_GPIO3 share same IO MUX function, GPIO_MUX3 selects one GPIO function: 0x8000U */
    );
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_SD_B1_00_USDHC1_CMD,        /* GPIO_SD_B1_00 PAD functional properties : */
      0x04U);                                 /* PDRV Field: high drive strength
                                                 Pull Down Pull Up Field: Internal pullup resistor enabled
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_SD_B1_01_USDHC1_CLK,        /* GPIO_SD_B1_01 PAD functional properties : */
      0x0CU);                                 /* PDRV Field: high drive strength
                                                 Pull Down Pull Up Field: No Pull
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_SD_B1_02_USDHC1_DATA0,      /* GPIO_SD_B1_02 PAD functional properties : */
      0x04U);                                 /* PDRV Field: high drive strength
                                                 Pull Down Pull Up Field: Internal pullup resistor enabled
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_SD_B1_03_USDHC1_DATA1,      /* GPIO_SD_B1_03 PAD functional properties : */
      0x04U);                                 /* PDRV Field: high drive strength
                                                 Pull Down Pull Up Field: Internal pullup resistor enabled
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_SD_B1_04_USDHC1_DATA2,      /* GPIO_SD_B1_04 PAD functional properties : */
      0x04U);                                 /* PDRV Field: high drive strength
                                                 Pull Down Pull Up Field: Internal pullup resistor enabled
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
  IOMUXC_SetPinConfig(
      IOMUXC_GPIO_SD_B1_05_USDHC1_DATA3,      /* GPIO_SD_B1_05 PAD functional properties : */
      0x04U);                                 /* PDRV Field: high drive strength
                                                 Pull Down Pull Up Field: Internal pullup resistor enabled
                                                 Open Drain Field: Disabled
                                                 Domain write protection: Both cores are allowed
                                                 Domain write protection lock: Neither of DWP bits is locked */
}
#endif
#ifdef BSP_USING_ETH
void imxrt_eth_pins_init(void) {
#ifdef PHY_USING_RTL8211F
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_00_ENET_1G_RX_EN, /* GPIO_DISP_B1_00 is configured as ENET_1G_RX_EN */
        0U);                                  /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_01_ENET_1G_RX_CLK, /* GPIO_DISP_B1_01 is configured as ENET_1G_RX_CLK */
        0U);                                   /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_02_ENET_1G_RX_DATA00, /* GPIO_DISP_B1_02 is configured as ENET_1G_RX_DATA00 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_03_ENET_1G_RX_DATA01, /* GPIO_DISP_B1_03 is configured as ENET_1G_RX_DATA01 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_04_ENET_1G_RX_DATA02, /* GPIO_DISP_B1_04 is configured as ENET_1G_RX_DATA02 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_05_ENET_1G_RX_DATA03, /* GPIO_DISP_B1_05 is configured as ENET_1G_RX_DATA03 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_06_ENET_1G_TX_DATA03, /* GPIO_DISP_B1_06 is configured as ENET_1G_TX_DATA03 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_07_ENET_1G_TX_DATA02, /* GPIO_DISP_B1_07 is configured as ENET_1G_TX_DATA02 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_08_ENET_1G_TX_DATA01, /* GPIO_DISP_B1_08 is configured as ENET_1G_TX_DATA01 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_09_ENET_1G_TX_DATA00, /* GPIO_DISP_B1_09 is configured as ENET_1G_TX_DATA00 */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_10_ENET_1G_TX_EN, /* GPIO_DISP_B1_10 is configured as ENET_1G_TX_EN */
        0U);                                  /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B1_11_ENET_1G_TX_CLK_IO, /* GPIO_DISP_B1_11 is configured as ENET_1G_TX_CLK_IO */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_12_GPIO_MUX5_IO13, /* GPIO_DISP_B2_12 is configured as GPIO_MUX5_IO13 */
        0U);                                   /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_13_GPIO_MUX5_IO14, /* GPIO_DISP_B2_13 is configured as GPIO_MUX5_IO14 */
        0U);                                   /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_19_ENET_1G_MDC, /* GPIO_EMC_B2_19 is configured as ENET_1G_MDC */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_20_ENET_1G_MDIO, /* GPIO_EMC_B2_20 is configured as ENET_1G_MDIO */
        0U);                                /* Software Input On Field: Input Path is determined by functionality */
#else
    CLOCK_EnableClock(kCLOCK_Iomuxc);      /* LPCG on: LPCG is ON. */
    CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_12_GPIO9_IO11, /* GPIO_AD_12 is configured as GPIO9_IO11 */
        0U);                          /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_32_ENET_MDC, /* GPIO_AD_32 is configured as ENET_MDC */
        0U);                        /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_33_ENET_MDIO, /* GPIO_AD_33 is configured as ENET_MDIO */
        0U);                         /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00, /* GPIO_DISP_B2_02 is configured as ENET_TX_DATA00 */
        0U);                                   /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01, /* GPIO_DISP_B2_03 is configured as ENET_TX_DATA01 */
        0U);                                   /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN, /* GPIO_DISP_B2_04 is configured as ENET_TX_EN */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK, /* GPIO_DISP_B2_05 is configured as ENET_REF_CLK */
        1U);                                 /* Software Input On Field: Force input path of pad GPIO_DISP_B2_05 */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00, /* GPIO_DISP_B2_06 is configured as ENET_RX_DATA00 */
        1U);                                   /* Software Input On Field: Force input path of pad GPIO_DISP_B2_06 */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01, /* GPIO_DISP_B2_07 is configured as ENET_RX_DATA01 */
        1U);                                   /* Software Input On Field: Force input path of pad GPIO_DISP_B2_07 */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN, /* GPIO_DISP_B2_08 is configured as ENET_RX_EN */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER, /* GPIO_DISP_B2_09 is configured as ENET_RX_ER */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_GPR->GPR4 = ((IOMUXC_GPR->GPR4 &
                         (~(IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK))) /* Mask bits to zero which are setting */
                        | IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR(0x01U)    /* ENET_REF_CLK direction control: 0x01U */
    );
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_LPSR_12_GPIO_MUX6_IO12, /* GPIO_LPSR_12 is configured as GPIO12_IO12 */
        0U);                                /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AD_12_GPIO9_IO11, /* GPIO_AD_12 PAD functional properties : */
        0x06U);                       /* Slew Rate Field: Slow Slew Rate
                                         Drive Strength Field: high drive strength
                                         Pull / Keep Select Field: Pull Enable
                                         Pull Up / Down Config. Field: Weak pull down
                                         Open Drain Field: Disabled
                                         Domain write protection: Both cores are allowed
                                         Domain write protection lock: Neither of DWP bits is locked */

    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_02_ENET_TX_DATA00, /* GPIO_DISP_B2_02 PAD functional properties : */
        0x02U);                                /* Slew Rate Field: Slow Slew Rate
                                                  Drive Strength Field: high drive strength
                                                  Pull / Keep Select Field: Pull Disable, Highz
                                                  Pull Up / Down Config. Field: Weak pull down
                                                  Open Drain Field: Disabled
                                                  Domain write protection: Both cores are allowed
                                                  Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_03_ENET_TX_DATA01, /* GPIO_DISP_B2_03 PAD functional properties : */
        0x02U);                                /* Slew Rate Field: Slow Slew Rate
                                                  Drive Strength Field: high drive strength
                                                  Pull / Keep Select Field: Pull Disable, Highz
                                                  Pull Up / Down Config. Field: Weak pull down
                                                  Open Drain Field: Disabled
                                                  Domain write protection: Both cores are allowed
                                                  Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_04_ENET_TX_EN, /* GPIO_DISP_B2_04 PAD functional properties : */
        0x02U);                            /* Slew Rate Field: Slow Slew Rate
                                              Drive Strength Field: high drive strength
                                              Pull / Keep Select Field: Pull Disable, Highz
                                              Pull Up / Down Config. Field: Weak pull down
                                              Open Drain Field: Disabled
                                              Domain write protection: Both cores are allowed
                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_05_ENET_REF_CLK, /* GPIO_DISP_B2_05 PAD functional properties : */
        0x03U);                              /* Slew Rate Field: Fast Slew Rate
                                                Drive Strength Field: high drive strength
                                                Pull / Keep Select Field: Pull Disable, Highz
                                                Pull Up / Down Config. Field: Weak pull down
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_06_ENET_RX_DATA00, /* GPIO_DISP_B2_06 PAD functional properties : */
        0x06U);                                /* Slew Rate Field: Slow Slew Rate
                                                  Drive Strength Field: high drive strength
                                                  Pull / Keep Select Field: Pull Enable
                                                  Pull Up / Down Config. Field: Weak pull down
                                                  Open Drain Field: Disabled
                                                  Domain write protection: Both cores are allowed
                                                  Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_07_ENET_RX_DATA01, /* GPIO_DISP_B2_07 PAD functional properties : */
        0x06U);                                /* Slew Rate Field: Slow Slew Rate
                                                  Drive Strength Field: high drive strength
                                                  Pull / Keep Select Field: Pull Enable
                                                  Pull Up / Down Config. Field: Weak pull down
                                                  Open Drain Field: Disabled
                                                  Domain write protection: Both cores are allowed
                                                  Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_08_ENET_RX_EN, /* GPIO_DISP_B2_08 PAD functional properties : */
        0x06U);                            /* Slew Rate Field: Slow Slew Rate
                                              Drive Strength Field: high drive strength
                                              Pull / Keep Select Field: Pull Enable
                                              Pull Up / Down Config. Field: Weak pull down
                                              Open Drain Field: Disabled
                                              Domain write protection: Both cores are allowed
                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_DISP_B2_09_ENET_RX_ER, /* GPIO_DISP_B2_09 PAD functional properties : */
        0x06U);                            /* Slew Rate Field: Slow Slew Rate
                                              Drive Strength Field: high drive strength
                                              Pull / Keep Select Field: Pull Enable
                                              Pull Up / Down Config. Field: Weak pull down
                                              Open Drain Field: Disabled
                                              Domain write protection: Both cores are allowed
                                              Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_LPSR_12_GPIO_MUX6_IO12, /* GPIO_LPSR_12 PAD functional properties : */
        0x0EU);                             /* Slew Rate Field: Slow Slew Rate
                                               Drive Strength Field: high driver
                                               Pull / Keep Select Field: Pull Enable
                                               Pull Up / Down Config. Field: Weak pull up
                                               Open Drain LPSR Field: Disabled
                                               Domain write protection: Both cores are allowed
                                               Domain write protection lock: Neither of DWP bits is locked */

#endif
}
#endif

#ifdef BSP_USING_SDRAM
void imxrt_sdram_pins_init(void)
{
    // SEMC
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_00_SEMC_DATA00, /* GPIO_EMC_B1_00 is configured as SEMC_DATA00 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_01_SEMC_DATA01, /* GPIO_EMC_B1_01 is configured as SEMC_DATA01 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_02_SEMC_DATA02, /* GPIO_EMC_B1_02 is configured as SEMC_DATA02 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_03_SEMC_DATA03, /* GPIO_EMC_B1_03 is configured as SEMC_DATA03 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_04_SEMC_DATA04, /* GPIO_EMC_B1_04 is configured as SEMC_DATA04 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_05_SEMC_DATA05, /* GPIO_EMC_B1_05 is configured as SEMC_DATA05 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_06_SEMC_DATA06, /* GPIO_EMC_B1_06 is configured as SEMC_DATA06 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_07_SEMC_DATA07, /* GPIO_EMC_B1_07 is configured as SEMC_DATA07 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_08_SEMC_DM00, /* GPIO_EMC_B1_08 is configured as SEMC_DM00 */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_09_SEMC_ADDR00, /* GPIO_EMC_B1_09 is configured as SEMC_ADDR00 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_10_SEMC_ADDR01, /* GPIO_EMC_B1_10 is configured as SEMC_ADDR01 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_11_SEMC_ADDR02, /* GPIO_EMC_B1_11 is configured as SEMC_ADDR02 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_12_SEMC_ADDR03, /* GPIO_EMC_B1_12 is configured as SEMC_ADDR03 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_13_SEMC_ADDR04, /* GPIO_EMC_B1_13 is configured as SEMC_ADDR04 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_14_SEMC_ADDR05, /* GPIO_EMC_B1_14 is configured as SEMC_ADDR05 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_15_SEMC_ADDR06, /* GPIO_EMC_B1_15 is configured as SEMC_ADDR06 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_16_SEMC_ADDR07, /* GPIO_EMC_B1_16 is configured as SEMC_ADDR07 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_17_SEMC_ADDR08, /* GPIO_EMC_B1_17 is configured as SEMC_ADDR08 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_18_SEMC_ADDR09, /* GPIO_EMC_B1_18 is configured as SEMC_ADDR09 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_19_SEMC_ADDR11, /* GPIO_EMC_B1_19 is configured as SEMC_ADDR11 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_20_SEMC_ADDR12, /* GPIO_EMC_B1_20 is configured as SEMC_ADDR12 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_21_SEMC_BA0, /* GPIO_EMC_B1_21 is configured as SEMC_BA0 */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_22_SEMC_BA1, /* GPIO_EMC_B1_22 is configured as SEMC_BA1 */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_23_SEMC_ADDR10, /* GPIO_EMC_B1_23 is configured as SEMC_ADDR10 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_24_SEMC_CAS, /* GPIO_EMC_B1_24 is configured as SEMC_CAS */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_25_SEMC_RAS, /* GPIO_EMC_B1_25 is configured as SEMC_RAS */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_26_SEMC_CLK, /* GPIO_EMC_B1_26 is configured as SEMC_CLK */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_27_SEMC_CKE, /* GPIO_EMC_B1_27 is configured as SEMC_CKE */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_28_SEMC_WE, /* GPIO_EMC_B1_28 is configured as SEMC_WE */
        0U);                           /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_29_SEMC_CS0, /* GPIO_EMC_B1_29 is configured as SEMC_CS0 */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_30_SEMC_DATA08, /* GPIO_EMC_B1_30 is configured as SEMC_DATA08 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_31_SEMC_DATA09, /* GPIO_EMC_B1_31 is configured as SEMC_DATA09 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_32_SEMC_DATA10, /* GPIO_EMC_B1_32 is configured as SEMC_DATA10 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_33_SEMC_DATA11, /* GPIO_EMC_B1_33 is configured as SEMC_DATA11 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_34_SEMC_DATA12, /* GPIO_EMC_B1_34 is configured as SEMC_DATA12 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_35_SEMC_DATA13, /* GPIO_EMC_B1_35 is configured as SEMC_DATA13 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_36_SEMC_DATA14, /* GPIO_EMC_B1_36 is configured as SEMC_DATA14 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_37_SEMC_DATA15, /* GPIO_EMC_B1_37 is configured as SEMC_DATA15 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_38_SEMC_DM01, /* GPIO_EMC_B1_38 is configured as SEMC_DM01 */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_39_SEMC_DQS, /* GPIO_EMC_B1_39 is configured as SEMC_DQS */
        1U);                            /* Software Input On Field: Force input path of pad GPIO_EMC_B1_39 */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_40_SEMC_RDY, /* GPIO_EMC_B1_40 is configured as SEMC_RDY */
        0U);                            /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B1_41_SEMC_CSX00, /* GPIO_EMC_B1_41 is configured as SEMC_CSX00 */
        0U);                              /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_00_SEMC_DATA16, /* GPIO_EMC_B2_00 is configured as SEMC_DATA16 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_01_SEMC_DATA17, /* GPIO_EMC_B2_01 is configured as SEMC_DATA17 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_02_SEMC_DATA18, /* GPIO_EMC_B2_02 is configured as SEMC_DATA18 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_03_SEMC_DATA19, /* GPIO_EMC_B2_03 is configured as SEMC_DATA19 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_04_SEMC_DATA20, /* GPIO_EMC_B2_04 is configured as SEMC_DATA20 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_05_SEMC_DATA21, /* GPIO_EMC_B2_05 is configured as SEMC_DATA21 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_06_SEMC_DATA22, /* GPIO_EMC_B2_06 is configured as SEMC_DATA22 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_07_SEMC_DATA23, /* GPIO_EMC_B2_07 is configured as SEMC_DATA23 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_08_SEMC_DM02, /* GPIO_EMC_B2_08 is configured as SEMC_DM02 */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_09_SEMC_DATA24, /* GPIO_EMC_B2_09 is configured as SEMC_DATA24 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_10_SEMC_DATA25, /* GPIO_EMC_B2_10 is configured as SEMC_DATA25 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_11_SEMC_DATA26, /* GPIO_EMC_B2_11 is configured as SEMC_DATA26 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_12_SEMC_DATA27, /* GPIO_EMC_B2_12 is configured as SEMC_DATA27 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_13_SEMC_DATA28, /* GPIO_EMC_B2_13 is configured as SEMC_DATA28 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_14_SEMC_DATA29, /* GPIO_EMC_B2_14 is configured as SEMC_DATA29 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_15_SEMC_DATA30, /* GPIO_EMC_B2_15 is configured as SEMC_DATA30 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_16_SEMC_DATA31, /* GPIO_EMC_B2_16 is configured as SEMC_DATA31 */
        0U);                               /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_17_SEMC_DM03, /* GPIO_EMC_B2_17 is configured as SEMC_DM03 */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_EMC_B2_18_SEMC_DQS4, /* GPIO_EMC_B2_18 is configured as SEMC_DQS4 */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */

    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_00_SEMC_DATA00, /* GPIO_EMC_B1_00 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_01_SEMC_DATA01, /* GPIO_EMC_B1_01 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_02_SEMC_DATA02, /* GPIO_EMC_B1_02 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_03_SEMC_DATA03, /* GPIO_EMC_B1_03 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_04_SEMC_DATA04, /* GPIO_EMC_B1_04 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_05_SEMC_DATA05, /* GPIO_EMC_B1_05 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_06_SEMC_DATA06, /* GPIO_EMC_B1_06 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_07_SEMC_DATA07, /* GPIO_EMC_B1_07 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_08_SEMC_DM00, /* GPIO_EMC_B1_08 PAD functional properties : */
        0x08U);                          /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_09_SEMC_ADDR00, /* GPIO_EMC_B1_09 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_10_SEMC_ADDR01, /* GPIO_EMC_B1_10 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_11_SEMC_ADDR02, /* GPIO_EMC_B1_11 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_12_SEMC_ADDR03, /* GPIO_EMC_B1_12 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_13_SEMC_ADDR04, /* GPIO_EMC_B1_13 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_14_SEMC_ADDR05, /* GPIO_EMC_B1_14 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_15_SEMC_ADDR06, /* GPIO_EMC_B1_15 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_16_SEMC_ADDR07, /* GPIO_EMC_B1_16 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_17_SEMC_ADDR08, /* GPIO_EMC_B1_17 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_18_SEMC_ADDR09, /* GPIO_EMC_B1_18 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_19_SEMC_ADDR11, /* GPIO_EMC_B1_19 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_20_SEMC_ADDR12, /* GPIO_EMC_B1_20 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_21_SEMC_BA0, /* GPIO_EMC_B1_21 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_22_SEMC_BA1, /* GPIO_EMC_B1_22 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_23_SEMC_ADDR10, /* GPIO_EMC_B1_23 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_24_SEMC_CAS, /* GPIO_EMC_B1_24 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_25_SEMC_RAS, /* GPIO_EMC_B1_25 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_26_SEMC_CLK, /* GPIO_EMC_B1_26 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_27_SEMC_CKE, /* GPIO_EMC_B1_27 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_28_SEMC_WE, /* GPIO_EMC_B1_28 PAD functional properties : */
        0x08U);                        /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_29_SEMC_CS0, /* GPIO_EMC_B1_29 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_30_SEMC_DATA08, /* GPIO_EMC_B1_30 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_31_SEMC_DATA09, /* GPIO_EMC_B1_31 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_32_SEMC_DATA10, /* GPIO_EMC_B1_32 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_33_SEMC_DATA11, /* GPIO_EMC_B1_33 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_34_SEMC_DATA12, /* GPIO_EMC_B1_34 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_35_SEMC_DATA13, /* GPIO_EMC_B1_35 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_36_SEMC_DATA14, /* GPIO_EMC_B1_36 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_37_SEMC_DATA15, /* GPIO_EMC_B1_37 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_38_SEMC_DM01, /* GPIO_EMC_B1_38 PAD functional properties : */
        0x08U);                          /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_39_SEMC_DQS, /* GPIO_EMC_B1_39 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_40_SEMC_RDY, /* GPIO_EMC_B1_40 PAD functional properties : */
        0x08U);                         /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B1_41_SEMC_CSX00, /* GPIO_EMC_B1_41 PAD functional properties : */
        0x08U);                           /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_00_SEMC_DATA16, /* GPIO_EMC_B2_00 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_01_SEMC_DATA17, /* GPIO_EMC_B2_01 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_02_SEMC_DATA18, /* GPIO_EMC_B2_02 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_03_SEMC_DATA19, /* GPIO_EMC_B2_03 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_04_SEMC_DATA20, /* GPIO_EMC_B2_04 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_05_SEMC_DATA21, /* GPIO_EMC_B2_05 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_06_SEMC_DATA22, /* GPIO_EMC_B2_06 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_07_SEMC_DATA23, /* GPIO_EMC_B2_07 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_08_SEMC_DM02, /* GPIO_EMC_B2_08 PAD functional properties : */
        0x04U);                          /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pullup resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_09_SEMC_DATA24, /* GPIO_EMC_B2_09 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_10_SEMC_DATA25, /* GPIO_EMC_B2_10 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_11_SEMC_DATA26, /* GPIO_EMC_B2_11 PAD functional properties : */
        0x04U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pullup resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_12_SEMC_DATA27, /* GPIO_EMC_B2_12 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_13_SEMC_DATA28, /* GPIO_EMC_B2_13 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_14_SEMC_DATA29, /* GPIO_EMC_B2_14 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_15_SEMC_DATA30, /* GPIO_EMC_B2_15 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_16_SEMC_DATA31, /* GPIO_EMC_B2_16 PAD functional properties : */
        0x08U);                            /* PDRV Field: high drive strength
                                                Pull Down Pull Up Field: Internal pulldown resistor enabled
                                                Open Drain Field: Disabled
                                                Domain write protection: Both cores are allowed
                                                Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_17_SEMC_DM03, /* GPIO_EMC_B2_17 PAD functional properties : */
        0x08U);                          /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_EMC_B2_18_SEMC_DQS4, /* GPIO_EMC_B2_18 PAD functional properties : */
        0x08U);                          /* PDRV Field: high drive strength
                                            Pull Down Pull Up Field: Internal pulldown resistor enabled
                                            Open Drain Field: Disabled
                                            Domain write protection: Both cores are allowed
                                            Domain write protection lock: Neither of DWP bits is locked */
}
#endif

#ifdef BSP_USING_CAN
void imxrt_can_pins_init(void)
{
#ifdef BSP_USING_CAN3
    CLOCK_EnableClock(kCLOCK_Iomuxc_Lpsr); /* LPCG on: LPCG is ON. */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_LPSR_00_FLEXCAN3_TX, /* GPIO_LPSR_00 is configured as FLEXCAN3_TX */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_LPSR_01_FLEXCAN3_RX, /* GPIO_LPSR_01 is configured as FLEXCAN3_RX */
        0U);                             /* Software Input On Field: Input Path is determined by functionality */
#endif
}
#endif

#ifdef BSP_USING_FLEXSPI
void imxrt_flexspi_pins_init(void)
{
#ifdef BSP_USING_FLEXSPI1
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_00_FLEXSPI1_B_DATA03, /* GPIO_SD_B2_00 is configured as FLEXSPI1_B_DATA03 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_01_FLEXSPI1_B_DATA02, /* GPIO_SD_B2_01 is configured as FLEXSPI1_B_DATA02 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_02_FLEXSPI1_B_DATA01, /* GPIO_SD_B2_02 is configured as FLEXSPI1_B_DATA01 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_03_FLEXSPI1_B_DATA00, /* GPIO_SD_B2_03 is configured as FLEXSPI1_B_DATA00 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_05_FLEXSPI1_A_DQS, /* GPIO_SD_B2_05 is configured as FLEXSPI1_A_DQS */
        0U);                                 /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_06_FLEXSPI1_A_SS0_B, /* GPIO_SD_B2_06 is configured as FLEXSPI1_A_SS0_B */
        0U);                                   /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_07_FLEXSPI1_A_SCLK, /* GPIO_SD_B2_07 is configured as FLEXSPI1_A_SCLK */
        0U);                                  /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_08_FLEXSPI1_A_DATA00, /* GPIO_SD_B2_08 is configured as FLEXSPI1_A_DATA00 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_09_FLEXSPI1_A_DATA01, /* GPIO_SD_B2_09 is configured as FLEXSPI1_A_DATA01 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_10_FLEXSPI1_A_DATA02, /* GPIO_SD_B2_10 is configured as FLEXSPI1_A_DATA02 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_SD_B2_11_FLEXSPI1_A_DATA03, /* GPIO_SD_B2_11 is configured as FLEXSPI1_A_DATA03 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */

#endif
}
#endif

#ifdef BSP_USING_LCD_MIPI
void imxrt_mipi_dsi_pins_init(void)
{
#ifdef BSP_USING_LCD_MIPI
    CLOCK_EnableClock(kCLOCK_Iomuxc); /* LPCG on: LPCG is ON. */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_02_GPIO9_IO01,           /* GPIO_AD_02 is configured as GPIO9_IO01 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AD_30_GPIO9_IO29,           /* GPIO_AD_30 is configured as GPIO9_IO29 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_DISP_B2_15_GPIO11_IO16,     /* GPIO_DISP_B2_15 is configured as GPIO11_IO16 */
        0U);                                    /* Software Input On Field: Input Path is determined by functionality */
#endif
}
#endif

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

#ifdef BSP_USING_LCD_MIPI
    imxrt_mipi_dsi_pins_init();
#endif
}

