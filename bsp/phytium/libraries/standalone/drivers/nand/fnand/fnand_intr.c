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
 * FilePath: fnand_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:56:46
 * Description:  This file contains functions related to fnand interrupt handling.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#include "fnand.h"
#include "fnand_hw.h"
#include "fassert.h"
#include "ferror_code.h"

#include "fdebug.h"
#define FNAND_INTR_DEBUG_TAG "FNAND_INTR"
#define FNAND_INTR_ERROR(format, ...) FT_DEBUG_PRINT_E(FNAND_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_INTR_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_INTR_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_INTR_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_INTR_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_INTR_DEBUG_TAG, format, ##__VA_ARGS__)


/**
 * @name: FNandIsrEnable
 * @msg:  Enable the corresponding interrupt based on the interrupt mask
 * @return {*}
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance
 * @param {u32} int_mask is interrupt mask
 */
void FNandIsrEnable(FNand *instance_p, u32 int_mask)
{
    u32 reg_value;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FNandConfig *config_p;
    config_p = &instance_p->config;

    FNAND_CLEARBIT(config_p->base_address, FNAND_INTRMASK_OFFSET, int_mask);
}

/**
 * @name: FNandIrqDisable
 * @msg:  Disable the corresponding interrupt based on the interrupt mask
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance
 * @param {u32} int_mask is interrupt mask
 * @return {*}
 */
void FNandIrqDisable(FNand *instance_p, u32 int_mask)
{
    u32 reg_value;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    FNandConfig *config_p;
    config_p = &instance_p->config;

    FNAND_SETBIT(config_p->base_address, FNAND_INTRMASK_OFFSET, int_mask);
}


/**
 * @name: FNandSetIsrHandler
 * @msg:  Initializes isr event callback function
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {FnandIrqEventHandler} event_p is callback function used to respond to the interrupt event
 * @param {void} *irq_args  is the arguments of event callback
 * @return {*}
 */
void FNandSetIsrHandler(FNand *instance_p, FnandIrqEventHandler event_p, void *irq_args)
{
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    instance_p->irq_event_fun_p = event_p;
    instance_p->irq_args = irq_args;
}


/**
 * @name: FNandIrqHandler
 * @msg:  Nand driver isr handler
 * @note:
 * @param {s32} vector is interrupt number
 * @param {void} *param is argument
 * @return {*}
 */
void FNandIrqHandler(s32 vector, void *param)
{
    FNand *instance_p = (FNand *)param;
    FNandConfig *config_p;
    u32 status;
    u32 en_irq;
    (void)vector;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;

    status = FNAND_READREG(config_p->base_address, FNAND_INTR_OFFSET);
    en_irq = (~FNAND_READREG(config_p->base_address, FNAND_INTRMASK_OFFSET)) & FNAND_INTRMASK_ALL_INT_MASK;

    if ((status & en_irq) == 0)
    {
        FNAND_INTR_DEBUG_E("No irq exit");
        return;
    }

    FNandIrqDisable(instance_p, status & FNAND_INTRMASK_ALL_INT_MASK);
    FNAND_WRITEREG(config_p->base_address, 0xfd0, 0);
    FNAND_WRITEREG(config_p->base_address, FNAND_INTR_OFFSET, status);

    if (instance_p->irq_event_fun_p)
    {
        if (status & FNAND_INTR_BUSY_MASK)
        {

            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_BUSY_EVENT);
        }

        if (status & FNAND_INTR_DMA_BUSY_MASK)
        {

            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_DMA_BUSY_EVENT);
        }

        if (status & FNAND_INTR_DMA_PGFINISH_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_DMA_PGFINISH_EVENT);
        }

        if (status & FNAND_INTR_DMA_FINISH_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_DMA_FINISH_EVENT);
        }

        if (status & FNAND_INTR_FIFO_EMP_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_FIFO_EMP_EVENT);
        }

        if (status & FNAND_INTR_FIFO_FULL_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_FIFO_FULL_EVENT);
        }

        if (status & FNAND_INTR_FIFO_TIMEOUT_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_FIFO_TIMEOUT_EVENT);
        }

        if (status & FNAND_INTR_CMD_FINISH_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_CMD_FINISH_EVENT);
        }

        if (status & FNAND_INTR_PGFINISH_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_PGFINISH_EVENT);
        }

        if (status & FNAND_INTR_RE_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_RE_EVENT);
        }

        if (status & FNAND_INTR_DQS_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_DQS_EVENT);
        }

        if (status & FNAND_INTR_RB_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_RB_EVENT);
        }

        if (status & FNAND_INTR_ECC_FINISH_MASK)
        {
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_ECC_FINISH_EVENT);
        }

        if (status & FNAND_INTR_ECC_ERR_MASK)
        {
            FNAND_WRITEREG(config_p->base_address, FNAND_ERROR_CLEAR_OFFSET, FNAND_ERROR_CLEAR_ECC_ERR_CLR_MASK);
            FNAND_WRITEREG(config_p->base_address, FNAND_FIFO_FREE_OFFSET, FNAND_FIFO_FREE_MASK);
            instance_p->irq_event_fun_p(instance_p->irq_args, FNAND_IRQ_ECC_ERR_EVENT);
        }
    }
}
