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
 * FilePath: fpcie_intx.c
 * Created Date: 2023-07-13 11:14:04
 * Last Modified: 2023-08-07 20:28:17
 * Description:  This file is for pcie interrupt handler implementation. (only surrport single function device)
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */
#include "fpcie_ecam.h"
#include "fpcie_ecam_common.h"
#include "fparameters.h"
#include "fio.h"
#include "fdrivers_port.h"

/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_INTX_DEBUG_TAG "FPCIE_INTX"
#define FPCIE_INTX_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTX_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTX_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTX_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FPcieEcamIntxRegister
 * @msg: This function registers an INTx interrupt handler for a specific PCIe device function.
 * @param {FPcieEcam *} instance_p - Pointer to the FPcieEcam instance.
 * @param {u8} bus - PCIe bus number.
 * @param {u8} device - PCIe device number.
 * @param {u8} function - PCIe function number.
 * @param {FPcieIntxFun *} func_p - Pointer to the interrupt handler function and its associated arguments.
 * @return {FError} - Error code indicating the success or failure of the operation.
 */
FError FPcieEcamIntxRegister(FPcieEcam *instance_p,u8 bus, u8 device, u8 function,FPcieIntxFun *func_p)
{
    u8 interrupt_pin, interrupt_line;
    u8 header_type;
    u32 config_data ;
    int i ;

    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    

    if(FPcieEcamReadConfigSpace(instance_p,bus, device, function,FPCIE_CCR_CLS_LT_HT_REGS,&config_data) != FT_SUCCESS) 
    {
        FPCIE_INTX_ERROR("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
        return FPCIE_READCONFIG_ERROR;
    }
    
    /* check head type */
    header_type = FPCIE_CCR_HEAD_TYPE_MASK(config_data) ;

    if(header_type == FPCIE_CCR_HEAD_TYPE0)
    {

        for (i = 0; i < instance_p->scans_bdf_count; i++)
        {
            if(instance_p->scans_bdf[i].bus == bus  && 
                instance_p->scans_bdf[i].device == device && 
                instance_p->scans_bdf[i].function == function )
            {
                break;
            }
        }
        
        if(i == instance_p->scans_bdf_count)
        {
            return FPCIE_DEVICE_NOT_FOUND ;
        }
        
        if(FPcieEcamReadConfigSpace(instance_p,bus, device, function,FPCIE_CCR_INTX_LAT_GNT_REGS,&config_data) != FT_SUCCESS) 
        {
            FPCIE_INTX_ERROR("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
            return FPCIE_READCONFIG_ERROR;
        }
        
        interrupt_pin = FPCIE_CCR_INTX_PIN_MASK(config_data) ;
        switch (interrupt_pin)
        {
        case 1:
            interrupt_line = instance_p->config.inta_irq_num ;
            instance_p->inta_fun[i] = *func_p;  
            instance_p->inta_fun[i].bus = bus;
            instance_p->inta_fun[i].device = device;
            instance_p->inta_fun[i].function = function;
            break;
        default:
            FPCIE_INTX_DEBUG_E("The current code does not support interrupts outside of INTA") ;
            return FPCIE_INTX_OVER_RANGE;
        }

        config_data &= ~FPCIE_CCR_INTX_LINE_MASK(0xff) ;
        config_data |= FPCIE_CCR_INTX_LINE_MASK(interrupt_line) ;
        
        
        FPcieEcamWriteConfigSpace(instance_p,bus, device, function,FPCIE_CCR_INTX_LAT_GNT_REGS,config_data) ;

        FPcieEcamInfoPrint(instance_p) ;
    }
    else
    {
        FPCIE_INTX_DEBUG_E("Pcie intx not match header type.") ;
        return FPCIE_TYPE_NOT_FIT ;
    }
    return FT_SUCCESS;
}

static void FPcieEcamIntxEoi(FPcieEcam *instance,u32 intx)
{
    FASSERT(instance != NULL);

/* controler intx need clean status */
#ifdef FPCI_ECAM_INTX_NEED_EOI
    u32 status = 0 ;
    u32 istatus = 0, imask = 0 ;
    int i ;
    status = FtIn32(instance->config.control_intx_base[0]) + (FtIn32(instance->config.control_intx_base[1]) << 12);

    imask = 1 << (3 - intx);
    istatus = (1 << intx) << 24;
    for (i = 0; i < FPCI_ECAM_INTX_CONFIG_ISTATUS_NUM; i++, status >>= 4)
    {
        if (imask & status)
        {
            FtOut32(instance->config.config_intx_base[i], istatus) ;
        }
    }
#else 
    (void) instance ;
    (void) intx ;
#endif
}


/**
 * @name: FPcieEcamIntxIrqHandler
 * @msg: This function is the interrupt handler for the INTx interrupts in PCIe ECAM driver.
 * @param {s32} vector - The interrupt vector number.
 * @param {void *} args - A pointer to the FPcieEcam instance.
 */
void FPcieEcamIntxIrqHandler(s32 vector, void *args) 
{
    FPcieEcam *instance_p = (FPcieEcam *)args;
    FASSERT(instance_p != NULL);
    u32 config_data = 0;
    u8 bus ;
    u8 device ;
    u8 function ;

    if(vector == instance_p->config.inta_irq_num)
    {
        /* code */
        for(int i = 0; i < instance_p->scans_bdf_count;i++)
        {
            bus = instance_p->scans_bdf[i].bus ;
            device = instance_p->scans_bdf[i].device ;
            function = instance_p->scans_bdf[i].function ;

            if(FPcieEcamReadConfigSpace(instance_p,bus, device, function,FPCIE_CCR_CMD_STATUS_REGS,&config_data) != FT_SUCCESS) 
            {
                FPCIE_INTX_ERROR("%s:%d,Failed to read config space", __FUNCTION__, __LINE__) ;
                return ;
            }
            
            if(config_data & FPCIE_CCR_STATUS_INTERRUT)
            {
                instance_p->inta_fun[i].IntxCallBack(instance_p->inta_fun[i].args);
            }
        }   
        /* eoi */
        FPcieEcamIntxEoi(instance_p,0) ;

    }

}