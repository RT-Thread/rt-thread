/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-14     Tanek        porting from stm32f429-apollo
 */

#include <rthw.h>
#include <rtthread.h>

#include <LPC54608.h>

#define DEBUG

#ifdef DEBUG
#define MPU_PRINT(...)      rt_kprintf(__VA_ARGS__)
#else
#define MPU_PRINT((...))
#endif

/* initialize for gui driver */
int rt_hw_mpu_init(void)
{
    uint32_t rbar;
    uint32_t rasr;

    MPU_PRINT("\nnumber of regions: %d\n", (MPU->TYPE & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos);

    /* Disable MPU */
    ARM_MPU_Disable();

    /* - Region 0: 0x00000000 - 0x0007FFFF --- on-chip non-volatile memory
    *      + Size: 512kB
    *      + Acess permission: full access
    */
    rbar = ARM_MPU_RBAR(0, 0x00000000);
    rasr = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512KB);
    ARM_MPU_SetRegion(rbar, rasr);

    /* - Region 1:0x20000000 - 0x20027FFF --- on chip SRAM
    *      + Size: 160kB
    *      + Access permission: full access
    */
    rbar = ARM_MPU_RBAR(1, 0x20000000);
    rasr = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_256KB);
    ARM_MPU_SetRegion(rbar, rasr);

    /* - Region 2: 0x40000000 - 0x43FFFFFF --- APB peripheral
    *      + Size: 64MB
    *      + Access permission: full access
    */
    rbar = ARM_MPU_RBAR(2, 0x40000000);
    rasr = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_64MB);
    ARM_MPU_SetRegion(rbar, rasr);

    /* - Region 3: 0xA0000000 - 0xA0800000 --- External SDRAM
    *      + Size: 8MB
    *      + AP=b011: full access
    */
    rbar = ARM_MPU_RBAR(3, 0xA0000000);
    rasr = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_8MB);
    ARM_MPU_SetRegion(rbar, rasr);

    /* - Region 4: 0xE0000000 - 0xE00FFFFF --- System control
    *      + Size: 1MB
    *      + Access permission: full access
    */
    rbar = ARM_MPU_RBAR(4, 0xE0000000);
    rasr = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_1MB);
    ARM_MPU_SetRegion(rbar, rasr);

    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_mpu_init);

