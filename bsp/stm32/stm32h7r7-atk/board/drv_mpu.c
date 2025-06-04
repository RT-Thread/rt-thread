/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-14     whj4674672   first version
 */
#include <rtthread.h>
#include "stm32h7rsxx.h"
#include "board.h"

int mpu_init(void)
{
    MPU_Region_InitTypeDef mpu_region_init_struct = {0};
    uint32_t region_index = 0;

    /* 关闭MPU */
    HAL_MPU_Disable();

    /* 配置背景域（0x00000000~0xFFFFFFFF，4GB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x00000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_4GB;
    mpu_region_init_struct.SubRegionDisable = 0x87;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL0;
    mpu_region_init_struct.AccessPermission = MPU_REGION_NO_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置ITCM对应区域（0x00000000~0x0000FFFF，64KB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x00000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_64KB;
    mpu_region_init_struct.SubRegionDisable = 0x00;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL1;
    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置DTCM对应区域（0x20000000~0x2000FFFF，64KB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x20000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_64KB;
    mpu_region_init_struct.SubRegionDisable = 0x00;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL1;
    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置AXI-SRAM1~4对应区域（0x24000000~0x24071FFF，456KB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x24000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_512KB;
    mpu_region_init_struct.SubRegionDisable = 0x00;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL1;
    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置AHB-SRAM1~2对应区域（0x30000000~0x30007FFF，32KB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x30000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_32KB;
    mpu_region_init_struct.SubRegionDisable = 0x00;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL1;
    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置FMC LCD对应区域（0x60000000~0x63FFFFFF，64MB） */
//    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
//    mpu_region_init_struct.Number = region_index++;
//    mpu_region_init_struct.BaseAddress = 0x60000000;
//    mpu_region_init_struct.Size = MPU_REGION_SIZE_64MB;
//    mpu_region_init_struct.SubRegionDisable = 0x00;
//    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL0;
//    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
//    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
//    mpu_region_init_struct.IsShareable = MPU_ACCESS_SHAREABLE;
//    mpu_region_init_struct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
//    mpu_region_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
//    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置XSPI NOR Flash对应区域（0x90000000~0x91FFFFFF，32MB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x90000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_32MB;
    mpu_region_init_struct.SubRegionDisable = 0x00;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL1;
    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 配置XSPI HyperRAM对应区域（0x70000000~0x71FFFFFF，32MB） */
    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;
    mpu_region_init_struct.Number = region_index++;
    mpu_region_init_struct.BaseAddress = 0x70000000;
    mpu_region_init_struct.Size = MPU_REGION_SIZE_32MB;
    mpu_region_init_struct.SubRegionDisable = 0x00;
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL1;
    mpu_region_init_struct.AccessPermission = MPU_REGION_FULL_ACCESS;
    mpu_region_init_struct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    mpu_region_init_struct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    mpu_region_init_struct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    mpu_region_init_struct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);

    /* 使能MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

    return RT_EOK;

}
INIT_BOARD_EXPORT(mpu_init);
