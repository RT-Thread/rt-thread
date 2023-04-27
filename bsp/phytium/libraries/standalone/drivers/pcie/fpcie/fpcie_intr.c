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
 * FilePath: fpcie_intr.c
 * Date: 2022-08-10 14:55:11
 * LastEditTime: 2022-08-18 08:59:42
 * Description: This file is for pcie interrupt handler implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe  2022/8/18   init commit
 */

/***************************** Include Files *********************************/
#include "fpcie.h"
#include "fpcie_common.h"
#include "fpcie_hw.h"
#include "fparameters.h"
#include "fdebug.h"

/***************** Macros (Inline Functions) Definitions *********************/

#define FPCIE_INTX_DEBUG_TAG "FPCIE_INTX"
#define FPCIE_INTX_ERROR(format, ...) FT_DEBUG_PRINT_E(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTX_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTX_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPCIE_INTX_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FPCIE_INTX_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Constant Definitions *****************************/
#define INTA 0
#define INTB 1
#define INTC 2
#define INTD 3

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/


/**
 * @name: FPcieIntxRegiterIrqHandler
 * @msg:  Use bus, device, and function to register interrupt response functions with INTX
 * @param {FPcie *} instance_p is a pointer to the FPcie instance.
 * @param {u32} bus is the number of the bus on which you want to register the funtion
 * @param {u32} device is the number of the device on which you want to register the funtion
 * @param {u32} function is the number of the function on which you want to register the funtion
 * @param {FPcieIntxFun *} intx_fun_p is the pointer the user uses to register the callback function
 * @return {FError}
 */
FError FPcieIntxRegiterIrqHandler(FPcie *instance_p,
                                  u32 bdf,
                                  FPcieIntxFun *intx_fun_p)
{
    int i;
    u8 interrupt_pin, interrupt_line;
    u8 header_type;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    /* 通过ecm 直接访问 控制寄存器 */
    FPcieEcamReadConfig8bit(instance_p->config.ecam, bdf, FPCIE_HEADER_TYPE_REG, &header_type) ;

    if (header_type == 0)
    {
        for (i = 0; i < instance_p->scaned_bdf_count; i++)
        {
            if (instance_p->scaned_bdf_array[i] == (s32)bdf)
            {
                break;          //获取到i的值，直接跳出循环
            }
        }

        /* 读出 Interrupt Pin*/
        FPcieEcamReadConfig8bit(instance_p->config.ecam, bdf, FPCIE_INTERRUPT_PIN_REG, &interrupt_pin) ;
        switch (interrupt_pin)
        {
            case 0x1: /* INTA# */
                interrupt_line = instance_p->config.inta_irq_num ;
                instance_p->inta_fun[i] = *intx_fun_p;  //中断函数，写入的是pcie instance的成员，一个pcie rc只有一个中断处理函数？
                instance_p->inta_fun[i].bdf  = bdf; //一个中断函数对应一个bdf号
                break ;
            case 0x2: /* INTB# */
                interrupt_line = instance_p->config.intb_irq_num ;
                instance_p->intb_fun[i] = *intx_fun_p;
                instance_p->intb_fun[i].bdf  = bdf;
                break ;
            case 0x3: /* INTC# */
                interrupt_line = instance_p->config.intc_irq_num ;
                instance_p->intc_fun[i] = *intx_fun_p;
                instance_p->intc_fun[i].bdf  = bdf;
                break ;
            case 0x4: /* INTD# */
                interrupt_line = instance_p->config.intd_irq_num ;
                instance_p->intd_fun[i] = *intx_fun_p;
                instance_p->intd_fun[i].bdf  = bdf;
                break ;
            default:
                FPCIE_INTX_DEBUG_E("Error interrupt pin.") ;
                return FPCIE_NOT_FOUND;
        }

        FPcieEcamWriteConfig8bit(instance_p->config.ecam, bdf, FPCIE_INTERRUPT_LINE_REG, interrupt_line) ;
    }
    else
    {
        FPCIE_INTX_DEBUG_E("Pcie intx not match header type.") ;
        return FPCIE_NOT_FOUND;
    }

    return FT_SUCCESS;
}


static void FPcieIntxCallback(FPcie *instance_p, u8 INTx_NUM)
{
    int i;
    u16 status ;
    /* 读取对应bdf 的status  */
    for (i = 0; i < instance_p->scaned_bdf_count; i++)  //轮询所有扫描到的pcie节点的interrupt status
    {
        FPcieEcamReadConfig16bit(instance_p->config.ecam, instance_p->scaned_bdf_array[i], FPCIE_STATUS_REG, &status) ;
        if (status & 0x8) /* check intrrupt status */
        {
            switch (INTx_NUM)
            {
                case INTA:
                    instance_p->inta_fun[i].IntxCallBack(instance_p->inta_fun[i].args);
                    break;
                case INTB:
                    instance_p->intb_fun[i].IntxCallBack(instance_p->intb_fun[i].args);
                    break;
                case INTC:
                    instance_p->intc_fun[i].IntxCallBack(instance_p->intc_fun[i].args);
                    break;
                case INTD:
                    instance_p->intd_fun[i].IntxCallBack(instance_p->intd_fun[i].args);
                    break;
                default:
                    FPCIE_INTX_DEBUG_E("%s: error intx num.", __func__);
                    break;

            }
        }
    }
}



static void FPcieIntxIrqEoi(FPcie *instance_p, u32 intx_idx)
{
#ifdef FPCI_INTX_EOI
    u32 status = 0 ;
    u32 istatus = 0, imask = 0 ;
    int i ;
    status = FPCIE_READREG(instance_p->config.intx_peux_stat_address[0], 0) + (FPCIE_READREG(instance_p->config.intx_peux_stat_address[1], 0) << 12);

    imask = 1 << (3 - intx_idx);
    istatus = (1 << intx_idx) << 24;
    for (i = 0; i < FPCI_INTX_CONTROL_NUM; i++, status >>= 4)
    {
        if (imask & status)
        {
            FPCIE_WRITEREG(instance_p->config.intx_control_eux_cx_address[i], 0, istatus) ;
        }
    }
#else
    (void) instance_p;
    (void) intx_idx ;
#endif
    return ;

}

/**
 * @name: FPcieIntxIrqHandler
 * @msg:  Intx interrupt service function of pcie
 * @param {s32} vector is interrupt vector number
 * @param {void} *args is Pass in a pointer to be processed
 */
void FPcieIntxIrqHandler(s32 vector, void *args)        //中断响应函数
{
    FPcie *instance_p = (FPcie *)args;
    FASSERT(instance_p != NULL);
    u32 *reg_data = 0;

    switch (vector)
    {
        case FPCI_INTA_IRQ_NUM:     //如果响应的是INTA中断，则调用pcie_obj中INTA的中断处理函数
            FPcieIntxCallback(instance_p, INTA) ;
            FPcieIntxIrqEoi(instance_p, 0) ;
            break;
        case FPCI_INTB_IRQ_NUM:
            FPcieIntxCallback(instance_p, INTA) ;
            FPcieIntxIrqEoi(instance_p, 1) ;
            break;
        case FPCI_INTC_IRQ_NUM:
            FPcieIntxCallback(instance_p, INTA) ;
            FPcieIntxIrqEoi(instance_p, 2) ;
            break;
        case FPCI_INTD_IRQ_NUM:
            FPcieIntxCallback(instance_p, INTA) ;
            FPcieIntxIrqEoi(instance_p, 3) ;
            break;
        default:
            break;
    }
}
