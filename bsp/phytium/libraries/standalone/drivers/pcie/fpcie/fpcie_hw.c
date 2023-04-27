/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fpcie_hw.c
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-08-18 08:58:12
 * Description: This file is for pcie register operation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

#include "fpcie_hw.h"
#include "fpcie.h"
#include "fpcie_common.h"
#include "fparameters.h"

/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/
/* Access sizes for PCI reads and writes */
enum FPcieSize
{
    FPCIE_SIZE_8,
    FPCIE_SIZE_16,
    FPCIE_SIZE_32,
};

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/


/**
 * @name: FPcieEcamConfigAddress
 * @msg:   提供一个可用于ECAM 访问机制的地址
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {s32} bdf  {Bus Device function}
 * @param {u32} offset 配置空间中的偏移量
 * @param {void **} addrp   用于存放输出有效访问空间的地址
 * @return FError
 */
static FError FPcieEcamConfigAddress(uintptr addr, s32 bdf, u32 offset, void **addrp)
{
    u32 bus_no = FPCIE_BUS(bdf);
    u32 dev_no = FPCIE_DEV(bdf);
    u32 vendor = 0;
    s32 bdf_parent ;
    uintptr ecam_addr = addr;
    addr += FPCIE_BUS(bdf) << 20;
    addr += FPCIE_DEV(bdf) << 15;
    addr += FPCIE_FUNC(bdf) << 12;


    bdf_parent = FPCIE_BDF(bus_no - 1, 0, 0);
    vendor = FPCIE_READREG(addr, FPCIE_CFG_ID_REG) ;

    if ((bus_no > 0) && (dev_no > 0))
    {
        if ((FPCIE_READREG_BYTE(addr, FPCIE_HEADER_TYPE_REG) & 0x7f) != FPCIE_HEADER_TYPE_BRIDGE)
        {
            if (vendor != 0x1d17)
            {
                return FPCIE_NEED_SKIP;
            }

            if (FPcieSkipDevice(ecam_addr, bdf_parent))
            {
                return FPCIE_NEED_SKIP;
            }
        }
    }

    addr += offset ;
    *addrp = (void *)addr ;
    return FT_SUCCESS;
}



/**
 * @name: FPcieSkipDevice
 * @msg:  跳过部分无效设备
 * @param {FPcie} *instance_p  is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @return FError
 */
FError FPcieSkipDevice(uintptr ecam_addr, s32 bdf)
{
    u8 pos, id;
    u16 capreg;
    u8 port_type;
    uintptr addr ;
    addr = ecam_addr ;
    addr += FPCIE_BUS(bdf) << 20;
    addr += FPCIE_DEV(bdf) << 15;
    addr += FPCIE_FUNC(bdf) << 12;

    pos = 0x34 ; /* Capabilites Pointer */
    while (1)
    {
        pos = FPCIE_READREG_BYTE(addr, pos) ;
        if (pos < 0x40)/* 超过Capability Pointer所代表的空间offset最大范围 */
        {
            break;
        }
        pos &= ~3 ; /* offset 第两位对齐 */
        id = FPCIE_READREG_BYTE(addr, pos) ;  /* PCI Express Cap ID */
        if (id == 0xff)
        {
            break ;
        }

        if (id == 0x10) /* 找到 PCIe设备的cap structure */
        {
            capreg = FPCIE_READREG(addr, pos + 2) ;
            port_type = (capreg >> 4) & 0xf ; /* Device/Port type */
            if ((port_type == 0x5) && (FPCIE_DEV(bdf) != 0))
            {
                return FPCIE_NEED_SKIP ;
            }
            else
            {
                return FT_SUCCESS;
            }

        }
        pos + 1 ;
    }

    return FT_SUCCESS;
}




static s32 FPcieGetFf(enum FPcieSize size)
{
    switch (size)
    {
        case FPCIE_SIZE_8:
            return 0xff;
        case FPCIE_SIZE_16:
            return 0xffff;
        default:
            return 0xffffffff;
    }
}

/**
 * @name: FPcieEcamReadConfig8bit
 * @msg:  基于ECAM机制读取配置空间中偏移量的值
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @param {u32} offset 配置空间中的偏移量
 * @param {u8} *value_p pointer store date available in the offset
 * @return FError
 */

void FPcieEcamReadConfig8bit(uintptr ecam_addr, s32 bdf, u32 offset, u8 *value_p)
{
    uintptr addr ;

    if (FPcieEcamConfigAddress(ecam_addr, bdf, offset, (void *)&addr) != FT_SUCCESS)
    {
        *value_p = FPcieGetFf(FPCIE_SIZE_8) ;
        return ;
    }


    *value_p = FPCIE_READREG_BYTE(addr, 0);

    return ;
}

/**
 * @name: FPcieEcamReadConfig16bit
 * @msg:  基于ECAM机制读取配置空间中偏移量的值
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @param {u32} offset 配置空间中的偏移量
 * @param {u16} *value_p pointer store date available in the offset
 * @return FError
 */

void FPcieEcamReadConfig16bit(uintptr ecam_addr, s32 bdf, u32 offset, u16 *value_p)
{
    uintptr addr ;

    if (FPcieEcamConfigAddress(ecam_addr, bdf, offset, (void *)&addr) != FT_SUCCESS)
    {
        *value_p = FPcieGetFf(FPCIE_SIZE_16) ;
        return ;
    }


    *value_p = FPCIE_READREG_SHORT(addr, 0);

    return ;
}

/**
 * @name: FPcieEcamReadConfig32bit
 * @msg:  基于ECAM机制读取配置空间中偏移量的值
 * @param {FPcie} *instance_p is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @param {u32} offset 配置空间中的偏移量
 * @param {u32} *value_p pointer store date available in the offset
 * @return FError
 */
void FPcieEcamReadConfig32bit(uintptr ecam_addr, s32 bdf, u32 offset, u32 *value_p)
{
    uintptr addr ;

    if (FPcieEcamConfigAddress(ecam_addr, bdf, offset, (void *)&addr) != FT_SUCCESS)
    {
        *value_p = FPcieGetFf(FPCIE_SIZE_32) ;
        return ;
    }


    *value_p = FPCIE_READREG(addr, 0);

    return ;
}


/**
 * @name: FPcieEcamWriteConfig8bit
 * @msg:  基于ECAM机制写入配置空间中偏移量的值
 * @param {FPcie} *instance_p  is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @param {u32} offset  配置空间中的偏移量
 * @param {u8} value to be written on to the offset
* @return FError
 */

void FPcieEcamWriteConfig8bit(uintptr ecam_addr, s32 bdf, u32 offset, u8 value)
{
    uintptr addr ;

    if (FPcieEcamConfigAddress(ecam_addr, bdf, offset, (void *)&addr) != FT_SUCCESS)
    {
        return ;
    }

    FPCIE_WRITEREG_BYTE(addr, 0, value) ;

    return ;
}

/**
 * @name: FPcieEcamWriteConfig16bit
 * @msg:  基于ECAM机制写入配置空间中偏移量的值
 * @param {FPcie} *instance_p  is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @param {u32} offset  配置空间中的偏移量
 * @param {u16} value to be written on to the offset
* @return FError
 */

void FPcieEcamWriteConfig16bit(uintptr ecam_addr, s32 bdf, u32 offset, u16 value)
{
    uintptr addr ;

    if (FPcieEcamConfigAddress(ecam_addr, bdf, offset, (void *)&addr) != FT_SUCCESS)
    {
        return ;
    }

    FPCIE_WRITEREG_SHORT(addr, 0, value) ;

    return ;
}


/**
 * @name: FPcieEcamWriteConfig32bit
 * @msg:  基于ECAM机制写入配置空间中偏移量的值
 * @param {FPcie} *instance_p  is a pointer to the FPcie instance.
 * @param {s32} bdf {Bus Device function}
 * @param {u32} offset  配置空间中的偏移量
 * @param {u32} value to be written on to the offset
* @return FError
 */

void FPcieEcamWriteConfig32bit(uintptr ecam_addr, s32 bdf, u32 offset, u32 value)
{
    uintptr addr ;

    if (FPcieEcamConfigAddress(ecam_addr, bdf, offset, (void *)&addr) != FT_SUCCESS)
    {
        return ;
    }

    FPCIE_WRITEREG(addr, 0, value) ;

    return ;
}
