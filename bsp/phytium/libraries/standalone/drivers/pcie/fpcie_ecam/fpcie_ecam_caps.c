/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fpcie_caps.c
 * Created Date: 2023-07-12 17:32:19
 * Last Modified: 2023-08-02 19:33:45
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */

#include "fpcie_ecam.h"
#include "fpcie_ecam_common.h"
#include "fdrivers_port.h"

/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_CAP_DEBUG_TAG "FPCIE_CAP"
#define FPCIE_CAP_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_CAP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_CAP_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_CAP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_CAP_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_CAP_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_CAP_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_CAP_DEBUG_TAG, format, ##__VA_ARGS__)



static u32 FPcieEcamGetBaseCapability(FPcieEcam *instance_p, u8 bus, u8 device, u8 function)
{
    u32 cap_value ;

    if(FPcieEcamReadConfigSpace(instance_p,bus, device, function,FPCIE_CCR_CAPBILITIES_PONINTERS_REGS,&cap_value) != FT_SUCCESS)
    {
        FPCIE_CAP_DEBUG_E("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
        return 0;
    }

    return  FPCIE_CCR_CAP_PONINTERS_MASK(cap_value);
}

/**
 * @name: FPcieEcamHasCapability
 * @msg: This function checks whether a specific capability is present in the PCIe device's capability list.
 * @param {FPcieEcam *} instance_p - Pointer to the FPcieEcam instance.
 * @param {u8} bus - PCIe bus number.
 * @param {u8} device - PCIe device number.
 * @param {u8} function - PCIe function number.
 * @param {u8} capid - ID of the capability to check for.
 * @return {u32} - Returns 1 if the capability is present, 0 otherwise.
 */
u32 FPcieEcamHasCapability(FPcieEcam *instance_p, u8 bus, u8 device, u8 function,u8 capid)
{
    u32 CapaBilityVaild = 0;
    u32 CapBilityBase = FPcieEcamGetBaseCapability(instance_p,bus,device,function) ;
    
    while (CapBilityBase != 0U)
    {
        if(FPcieEcamReadConfigSpace(instance_p,bus, device, function,FPCIE_CAP_ADDRESS_GET(CapBilityBase),&CapBilityBase) != FT_SUCCESS)
        {
            FPCIE_CAP_DEBUG_E("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
            break;
        }

        if(FPCIE_CAP_ID_GET(CapBilityBase) == capid)
        {
            CapaBilityVaild = 1;
            break;
        }

        CapBilityBase = FPCIE_CAP_NEXT_POINTER_GET(CapBilityBase) ;
    }
    
    return CapaBilityVaild ;
}

/**
 * @name: FPcieEcamHasExtendCapability
 * @msg: This function checks whether a specific extended capability is present in the PCIe device's extended capability list.
 * @param {FPcieEcam *} instance_p - Pointer to the FPcieEcam instance.
 * @param {u8} bus - PCIe bus number.
 * @param {u8} device - PCIe device number.
 * @param {u8} function - PCIe function number.
 * @param {u16} capid - ID of the extended capability to check for.
 * @return {u32} - Returns 1 if the extended capability is present, 0 otherwise.
 */
u32 FPcieEcamHasExtendCapability(FPcieEcam *instance_p, u8 bus, u8 device, u8 function,u16 capid)
{
    u32 CapaBilityVaild = 0;
    u32 CapaBilityOffset ,CapaBilityValue;

    CapaBilityOffset = FPCI_EXT_REGS ;

    do
    {
        if(FPcieEcamReadConfigSpace(instance_p,bus, device, function,CapaBilityOffset,&CapaBilityValue) != FT_SUCCESS)
        {
            FPCIE_CAP_DEBUG_E("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
            break;
        }
        if(CapaBilityValue == 0)
        {
            break;
        }

        if(FPCIE_EXT_CAP_ID_GET(CapaBilityValue) == capid)
        {
            CapaBilityVaild = 1;
            break;
        }
        
        CapaBilityOffset = FPCI_EXT_CAP_PONINTERS_MASK(CapaBilityValue) ;
    } while (CapaBilityOffset);
    return CapaBilityVaild ;
}

