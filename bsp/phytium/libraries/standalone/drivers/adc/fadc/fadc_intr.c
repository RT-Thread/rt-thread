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
 * FilePath: fadc_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:28:45
 * Description:  This file is for adc interrupt handler implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/25   init commit
 */

#include "fparameters.h"
#include "fassert.h"
#include "fadc.h"
#include "fadc_hw.h"

#define FADC_DEBUG_TAG "FT_ADC_INTR"
#define FADC_DEBUG(format, ...)     FT_DEBUG_PRINT_D(FADC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FADC_INFO(format, ...)      FT_DEBUG_PRINT_I(FADC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FADC_WARN(format, ...)      FT_DEBUG_PRINT_W(FADC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FADC_ERROR(format, ...)     FT_DEBUG_PRINT_E(FADC_DEBUG_TAG, format, ##__VA_ARGS__)

#define FADC_CALL_INTR_EVENT_HANDLDER(instance_p, event) \
    if (instance_p->event_handler[event])                 \
        instance_p->event_handler[event](instance_p->event_param[event])

/**
 * @name: FAdcRegisterInterruptHandler
 * @msg: register FAdc interrupt handler function
 * @param {FAdc} *instance_p, pointer to the adc instance
 * @param {FAdcIntrEvtType} event_type, interrupt event type
 * @param {FAdcEvtHandler} handler, interrupt event handler
 * @param {void} *param, contains a pointer to the driver instance
 * @return {*}
 */
void FAdcRegisterInterruptHandler(FAdcCtrl *instance_p, FAdcIntrEventType event_type,
                                  FAdcIntrEventHandler handler, void *param)
{
    FASSERT(instance_p);
    FASSERT(event_type < FADC_INTR_EVENT_NUM);
    instance_p->event_handler[event_type] = handler;
    instance_p->event_param[event_type] = param;
}

/**
 * @name: FAdcIntrHandler
 * @msg:  This function is the interrupt handler for the driver.
 *          It must be connected to an interrupt system by the application such that it
 *          can be called when an interrupt occurs.
 * @param vector Irq num ,Don't need attention .
 * @param args  contains a pointer to the driver instance
 */
void FAdcIntrHandler(s32 vector, void *args)
{
    FASSERT(args != NULL);
    FAdcCtrl *pctrl = (FAdcCtrl *)args;
    u32 status = 0;
    u32 intrmask = 0;
    u32 channel = 0;
    uintptr base_addr = pctrl->config.base_addr;

    status = FADC_READ_REG32(base_addr, FADC_INTR_REG_OFFSET);
    /* channel convert complete irq mask */
    intrmask = FADC_READ_REG32(base_addr, FADC_INTRMASK_REG_OFFSET);

    /* adc error interrupt */
    if (status & FADC_INTR_REG_ERR)
    {
        /* clear error interrupt status */
        FADC_SETBIT(base_addr, FADC_INTR_REG_OFFSET, FADC_INTR_REG_ERR);

        /* write error clear register, adc_errclr_reg=0 */
        FADC_WRITE_REG32(base_addr, FADC_ERRCLR_REG_OFFSET, 0);

        FADC_CALL_INTR_EVENT_HANDLDER(pctrl, FADC_INTR_EVENT_ERROR);
    }

    if (status & FADC_INTR_REG_LIMIT_MASK)
    {
        for (channel = 0; channel < FADC_CHANNEL_NUM; channel++)
        {
            if (status & FADC_INTR_REG_DLIMIT(channel))
            {
                /* clear dlimit interrupt status */
                FADC_SETBIT(base_addr, FADC_INTR_REG_OFFSET, FADC_INTR_REG_DLIMIT(channel));
                FADC_CALL_INTR_EVENT_HANDLDER(pctrl, FADC_INTR_EVENT_DLIMIT);
            }
            if (status & FADC_INTR_REG_ULIMIT(channel))
            {
                /* clear ulimit interrupt status */
                FADC_SETBIT(base_addr, FADC_INTR_REG_OFFSET, FADC_INTR_REG_ULIMIT(channel));
                FADC_CALL_INTR_EVENT_HANDLDER(pctrl, FADC_INTR_EVENT_ULIMIT);
            }
        }
    }

    /* 有中断转换完成的情况下，根据adc_intr_reg寄存器的通道转换完成中断标志位bit0~7，读取转换结果 */
    if (status & FADC_INTR_REG_COVFIN_MASK)
    {
        for (channel = 0; channel < FADC_CHANNEL_NUM; channel++)
        {
            if (status & FADC_INTR_REG_COVFIN(channel))
            {
                pctrl->value[channel] = FADC_READ_REG32(base_addr, FADC_COV_RESULT_REG_OFFSET(channel)) & FADC_COV_RESULT_REG_MASK;
                FADC_CONVERT_COMPLETE(pctrl->convert_complete[channel]);
                /* clear convert finish interrupt status */
                FADC_SETBIT(base_addr,  FADC_INTR_REG_OFFSET, FADC_INTR_REG_COVFIN(channel));
            }
        }

        FADC_CALL_INTR_EVENT_HANDLDER(pctrl, FADC_INTR_EVENT_COVFIN);
    }
    else
    {

    }

    return;
}

