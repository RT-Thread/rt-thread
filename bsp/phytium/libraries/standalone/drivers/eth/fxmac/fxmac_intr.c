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
 * FilePath: fxmac_intr.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file contains functions related to interrupt handling.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#include "fxmac.h"
#include "fxmac_hw.h"
#include "fassert.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/


/**
 * @name: FXmacSetHandler
 * @msg:  Install an asynchronous handler function for the given handler_type:
 *
 * @param instance_p is a pointer to the instance to be worked on.
 * @param handler_type indicates what interrupt handler type is.
 *        FXMAC_HANDLER_DMASEND, FXMAC_HANDLER_DMARECV and
 *        FXMAC_HANDLER_ERROR.
 * @param func_pointer is the pointer to the callback function
 * @param call_back_ref is the upper layer callback reference passed back when
 *        when the callback function is invoked.
 *
 * @return {FError} FT_SUCCESS set is ok
 */
FError FXmacSetHandler(FXmac *instance_p, u32 handler_type,
                       void *func_pointer, void *call_back_ref)
{
    FError status;
    FASSERT(instance_p != NULL);
    FASSERT(func_pointer != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);
    status = (FError)(FT_SUCCESS);

    switch (handler_type)
    {
        case FXMAC_HANDLER_DMASEND:
            instance_p->send_irq_handler = ((FXmacIrqHandler)(void *)func_pointer);
            instance_p->send_args = call_back_ref;
            break;
        case FXMAC_HANDLER_DMARECV:
            instance_p->recv_irq_handler = ((FXmacIrqHandler)(void *)func_pointer);
            instance_p->recv_args = call_back_ref;
            break;
        case FXMAC_HANDLER_ERROR:
            instance_p->error_irq_handler = ((FXmacErrorIrqHandler)(void *)func_pointer);
            instance_p->error_args = call_back_ref;
            break;
        case FXMAC_HANDLER_LINKCHANGE:
            instance_p->link_change_handler = ((FXmacIrqHandler)(void *)func_pointer);
            instance_p->link_change_args = call_back_ref;
            break;
        case FXMAC_HANDLER_RESTART:
            instance_p->restart_handler = ((FXmacIrqHandler)(void *)func_pointer);
            instance_p->restart_args = call_back_ref;
            break;
        default:
            status = (FError)(FXMAC_ERR_INVALID_PARAM);
            break;
    }
    return status;
}


/**
 * @name: FXmacIntrHandler
 * @msg:  中断处理函数
 * @param {s32} vector is interrrupt num
 * @param {void} *args is a arguments variables
 * @return {*}
 * @note 目前中断只支持单queue的情况
 */

void FXmacIntrHandler(s32 vector, void *args)
{
    u32 reg_isr;
    u32 reg_qx_isr;
    u32 reg_temp;
    u32 reg_ctrl;
    u32 tx_queue_id; /* 0 ~ FXMAC_QUEUE_MAX_NUM ,Index queue number */
    u32 rx_queue_id; /* 0 ~ FXMAC_QUEUE_MAX_NUM ,Index queue number */
    FXmac *instance_p = (FXmac *)args;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);

    tx_queue_id = instance_p->tx_bd_queue.queue_id;
    rx_queue_id = instance_p->rx_bd_queue.queue_id;
    FASSERT((rx_queue_id < FXMAC_QUEUE_MAX_NUM) && (tx_queue_id < FXMAC_QUEUE_MAX_NUM))

    /* This ISR will try to handle as many interrupts as it can in a single
     * call. However, in most of the places where the user's error handler
     * is called, this ISR exits because it is expected that the user will
     * reset the device in nearly all instances.
     */
    reg_isr = FXMAC_READREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET);

    if ((u32)vector == instance_p->config.queue_irq_num[tx_queue_id])
    {
        if (tx_queue_id == 0)
        {
            if ((reg_isr & FXMAC_IXR_TXCOMPL_MASK) != 0x00000000U)
            {
                /* Clear TX status register TX complete indication but preserve
                 * error bits if there is any */
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_TXSR_OFFSET,
                                 ((u32)FXMAC_TXSR_TXCOMPL_MASK |
                                  (u32)FXMAC_TXSR_USEDREAD_MASK));

                if (instance_p->send_irq_handler)
                {
                    /* code */
                    instance_p->send_irq_handler(instance_p->send_args);
                }

                /* add */
                if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                {
                    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_TXCOMPL_MASK);
                }
            }

            /* Transmit error conditions interrupt */
            if (((reg_isr & FXMAC_IXR_TX_ERR_MASK) != 0x00000000U) &&
                (!(reg_isr & FXMAC_IXR_TXCOMPL_MASK) != 0x00000000U))
            {
                /* Clear TX status register */
                reg_temp = FXMAC_READREG32(instance_p->config.base_address, FXMAC_TXSR_OFFSET);
                FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_TXSR_OFFSET, reg_temp);
                if (instance_p->error_irq_handler)
                {
                    instance_p->error_irq_handler(instance_p->error_args, FXMAC_SEND, reg_temp);
                }
                /* add */
                if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                {
                    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_TX_ERR_MASK);
                }
            }

            /* add restart */
            if ((reg_isr & FXMAC_IXR_TXUSED_MASK) != 0x00000000U)
            {
                /* add */
                if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                {
                    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_TXUSED_MASK);
                }

                if (instance_p->restart_handler)
                {
                    instance_p->restart_handler(instance_p->restart_args);
                }
            }
            
            /* link chaged */
            if ((reg_isr & FXMAC_IXR_LINKCHANGE_MASK) != 0x00000000U)
            {
                if (instance_p->link_change_handler)
                {
                    instance_p->link_change_handler(instance_p->link_change_args);
                }

                if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                {
                    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_LINKCHANGE_MASK);
                }
            }
        }
        else /* use queue number more than 0 */
        {
            reg_isr = FXMAC_READREG32(instance_p->config.base_address,
                                      FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_INTQ1_STS_OFFSET, tx_queue_id));

            /* Transmit Q1 complete interrupt */
            if (((reg_isr & FXMAC_INTQUESR_TXCOMPL_MASK) != 0x00000000U))
            {
                /* Clear TX status register TX complete indication but preserve
                 * error bits if there is any */
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_INTQ1_STS_OFFSET, tx_queue_id),
                                 FXMAC_INTQUESR_TXCOMPL_MASK);
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_TXSR_OFFSET,
                                 ((u32)FXMAC_TXSR_TXCOMPL_MASK |
                                  (u32)FXMAC_TXSR_USEDREAD_MASK));
                instance_p->send_irq_handler(instance_p->send_args);
            }

            /* Transmit Q1 error conditions interrupt */
            if (((reg_isr & FXMAC_INTQ1SR_TXERR_MASK) != 0x00000000U) &&
                ((reg_isr & FXMAC_INTQ1SR_TXCOMPL_MASK) != 0x00000000U))
            {
                /* Clear Interrupt Q1 status register */
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_INTQ1_STS_OFFSET, tx_queue_id), reg_isr);
                instance_p->error_irq_handler(instance_p->error_args, FXMAC_SEND,
                                              reg_isr);
            }
        }
    }

    if ((u32)vector == instance_p->config.queue_irq_num[rx_queue_id])
    {
        if (rx_queue_id == 0)
        {
            /* Receive complete interrupt */
            if ((reg_isr & FXMAC_IXR_RXCOMPL_MASK) != 0x00000000U)
            {
                /* Clear RX status register RX complete indication but preserve
                 * error bits if there is any */
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_RXSR_OFFSET,
                                 ((u32)FXMAC_RXSR_FRAMERX_MASK |
                                  (u32)FXMAC_RXSR_BUFFNA_MASK));
                instance_p->recv_irq_handler(instance_p->recv_args);

                /* add */
                if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                {
                    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_RXCOMPL_MASK);
                }
            }

            /* Receive error conditions interrupt */
            if ((reg_isr & FXMAC_IXR_RX_ERR_MASK) != 0x00000000U)
            {
                /* Clear RX status register */
                reg_temp = FXMAC_READREG32(instance_p->config.base_address,
                                           FXMAC_RXSR_OFFSET);
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_RXSR_OFFSET, reg_temp);

                /* Fix for CR # 692702. Write to bit 18 of net_ctrl
                 * register to flush a packet out of Rx SRAM upon
                 * an error for receive buffer not available. */
                if ((reg_isr & FXMAC_IXR_RXUSED_MASK) != 0x00000000U)
                {
                    reg_ctrl = FXMAC_READREG32(instance_p->config.base_address,
                                               FXMAC_NWCTRL_OFFSET);
                    reg_ctrl |= (u32)FXMAC_NWCTRL_FLUSH_DPRAM_MASK;

                    /* add  */
                    reg_ctrl &= (u32)(~FXMAC_NWCTRL_RXEN_MASK);
                    FXMAC_WRITEREG32(instance_p->config.base_address,
                                     FXMAC_NWCTRL_OFFSET, reg_ctrl);

                    /* add  */
                    reg_ctrl |= (u32)FXMAC_NWCTRL_RXEN_MASK;
                    FXMAC_WRITEREG32(instance_p->config.base_address,
                                     FXMAC_NWCTRL_OFFSET, reg_ctrl);
                }

                /* add */
                if ((reg_isr & FXMAC_IXR_RXOVR_MASK) != 0x00000000U)
                {
                    if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                    {
                        FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_RXOVR_MASK);
                    }
                }

                /* add */
                if ((reg_isr & FXMAC_IXR_HRESPNOK_MASK) != 0x00000000U)
                {
                    if(instance_p->caps& FXMAC_CAPS_ISR_CLEAR_ON_WRITE)
                    {
                        FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET, FXMAC_IXR_HRESPNOK_MASK);
                    }
                }

                if (reg_temp != 0)
                {
                    instance_p->error_irq_handler(instance_p->error_args,
                                                  FXMAC_RECV, reg_temp);
                }
            }
        }
        else /* use queue number more than 0 */
        {
            reg_isr = FXMAC_READREG32(instance_p->config.base_address,
                                      FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_INTQ1_STS_OFFSET, rx_queue_id));

            /* Receive complete interrupt */
            if ((reg_isr & FXMAC_INTQUESR_RCOMP_MASK) != 0x00000000U)
            {
                /* Clear RX status register RX complete indication but preserve
                 * error bits if there is any */
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_INTQ1_STS_OFFSET, rx_queue_id),
                                 FXMAC_INTQUESR_RCOMP_MASK);
                instance_p->recv_irq_handler(instance_p->recv_args);
            }

            /* Receive error conditions interrupt */
            if ((reg_isr & FXMAC_IXR_RX_ERR_MASK) != 0x00000000U)
            {

                reg_ctrl =
                    FXMAC_READREG32(instance_p->config.base_address,
                                    FXMAC_NWCTRL_OFFSET);
                reg_ctrl &= ~(u32)FXMAC_NWCTRL_RXEN_MASK;

                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_NWCTRL_OFFSET, reg_ctrl);

                /* Clear RX status register */
                reg_temp = FXMAC_READREG32(instance_p->config.base_address,
                                           FXMAC_RXSR_OFFSET);
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_RXSR_OFFSET, reg_temp);

                /* Fix for CR # 692702. Write to bit 18 of net_ctrl
                 * register to flush a packet out of Rx SRAM upon
                 * an error for receive buffer not available. */
                if ((reg_isr & FXMAC_IXR_RXUSED_MASK) != 0x00000000U)
                {
                    reg_ctrl =
                        FXMAC_READREG32(instance_p->config.base_address,
                                        FXMAC_NWCTRL_OFFSET);
                    reg_ctrl |= (u32)FXMAC_NWCTRL_FLUSH_DPRAM_MASK;

                    FXMAC_WRITEREG32(instance_p->config.base_address,
                                     FXMAC_NWCTRL_OFFSET, reg_ctrl);
                }

                /* Clear RX status register RX complete indication but preserve
                 * error bits if there is any */
                FXMAC_WRITEREG32(instance_p->config.base_address,
                                 FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_INTQ1_STS_OFFSET, rx_queue_id),
                                 FXMAC_INTQUESR_RXUBR_MASK);
                instance_p->recv_irq_handler(instance_p->recv_args);

                if (reg_temp != 0)
                {
                    instance_p->error_irq_handler(instance_p->error_args,
                                                  FXMAC_RECV, reg_temp);
                }
            }
        }
    }
}


/**
 * @name: FXmacQueueIrqDisable
 * @msg:  Disable queue irq
 * @param {FXmac} *instance_p a pointer to the instance to be worked on.
 * @param {u32} queue_num queue number
 * @param {u32} mask is interrupt disable value mask
 */
void FXmacQueueIrqDisable(FXmac *instance_p, u32 queue_num, u32 mask)
{
    FXmacConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);
    FASSERT(instance_p->config.max_queue_num > queue_num);
    config_p = &instance_p->config;

    if (queue_num == 0)
    {
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_IDR_OFFSET, mask & FXMAC_IXR_ALL_MASK);
    }
    else
    {
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_INTQX_IDR_SIZE_OFFSET(queue_num), mask & FXMAC_IXR_ALL_MASK);
    }
}

/**
 * @name: FXmacQueueIrqEnable
 * @msg:  Enable queue irq
 * @param {FXmac} *instance_p a pointer to the instance to be worked on.
 * @param {u32} queue_num is queue number
 * @param {u32} mask is interrupt Enable value mask
 */
void FXmacQueueIrqEnable(FXmac *instance_p, u32 queue_num, u32 mask)
{
    FXmacConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);
    FASSERT(instance_p->config.max_queue_num > queue_num);
    config_p = &instance_p->config;

    if (queue_num == 0)
    {
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_IER_OFFSET, mask & FXMAC_IXR_ALL_MASK);
    }
    else
    {
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_INTQX_IER_SIZE_OFFSET(queue_num), mask & FXMAC_IXR_ALL_MASK);
    }
}