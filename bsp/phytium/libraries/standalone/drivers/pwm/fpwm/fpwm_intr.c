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
 * FilePath: fpwm_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-25 11:45:05
 * Description:  This file is for pwm interrupt handler implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/25   init commit
 */

#include "fparameters.h"
#include "fassert.h"
#include "fpwm.h"
#include "fpwm_hw.h"

#define FT_PWM_DEBUG_TAG "FT_PWM_INTR"
#define FPWM_DEBUG(format, ...) FT_DEBUG_PRINT_D(FT_PWM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPWM_INFO(format, ...) FT_DEBUG_PRINT_I(FT_PWM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPWM_WARN(format, ...) FT_DEBUG_PRINT_W(FT_PWM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FPWM_ERROR(format, ...) FT_DEBUG_PRINT_E(FT_PWM_DEBUG_TAG, format, ##__VA_ARGS__)

#define FPWM_CALL_INTR_EVENT_HANDLDER(instance_p, event) \
    if (instance_p->event_handler[event])                 \
        instance_p->event_handler[event](instance_p->event_param[event])

/**
 * @name: FPwmRegisterInterruptHandler
 * @msg: register FPwm interrupt handler function
 * @param {FPwm} *instance_p, pointer to the pwm instance
 * @param {FPwmIntrEvtType} event_type, interrupt event type
 * @param {FPwmEvtHandler} handler, interrupt event handler
 * @param {void} *param, contains a pointer to the driver instance
 * @return {*}
 */
void FPwmRegisterInterruptHandler(FPwmCtrl *instance_p, FPwmIntrEventType event_type, FPwmIntrEventHandler handler, void *param)
{
    FASSERT(instance_p);
    FASSERT(event_type < FPWM_INTR_EVENT_NUM);
    instance_p->event_handler[event_type] = handler;
    instance_p->event_param[event_type] = param;
}

/**
 * @name: FPwmIntrHandler
 * @msg:  This function is the interrupt handler for the driver.
 *          It must be connected to an interrupt system by the application such that it
 *          can be called when an interrupt occurs.
 * @param vector Irq num ,Don't need attention .
 * @param args  contains a pointer to the driver instance
 */
void FPwmIntrHandler(s32 vector, void *args)
{
    u32 status;
    static int i = 0;
    FPwmCtrl *pctrl = (FPwmCtrl *)args;

    FASSERT(pctrl != NULL);
    FASSERT(pctrl->is_ready == FT_COMPONENT_IS_READY);
    uintptr pwm_base_addr = 0;
    u8 channel = 0;

    for (channel = 0; channel < FPWM_MODE_CHANNEL; channel++)
    {
        pwm_base_addr = pctrl->config.pwm_base_addr + FPWM_N(channel);

        status = FPWM_READ_REG32(pwm_base_addr, FPWM_CTRL_OFFSET);
        if (!(status & (FPWM_CTRL_INTR_COUNTER_ENABLE | FPWM_CTRL_INTR_FIFO_EMPTY_ENABLE)))
        {
            continue;
        }

        status = FPWM_READ_REG32(pwm_base_addr, FPWM_STATE_OFFSET);
        if (0 == status)
        {
            continue;
        }

        /* Check for the type of error interrupt and Processing it */
        if (status & FPWM_STATE_OVFIF_COUNTER)
        {
            status &= (~FPWM_STATE_OVFIF_COUNTER);
            FPWM_SETBIT(pwm_base_addr, FPWM_STATE_OFFSET, FPWM_STATE_COUNTER_CLEAR);
            FPWM_CALL_INTR_EVENT_HANDLDER(pctrl, FPWM_INTR_EVENT_COUNTER);
        }

        if (status & FPWM_STATE_FIFO_EMPTY)
        {
            FPWM_SETBIT(pwm_base_addr, FPWM_STATE_OFFSET, FPWM_STATE_FIFO_EMPTY);
            FPWM_CALL_INTR_EVENT_HANDLDER(pctrl, FPWM_INTR_EVENT_FIFO_EMPTY);
        }
    }

}

