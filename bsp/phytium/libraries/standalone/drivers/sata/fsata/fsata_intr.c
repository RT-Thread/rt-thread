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
 * FilePath: fsata_intr.c
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 09:03:57
 * Description:  This file is for intrrupt function of Sata ctrl
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/2/10    first release
 * 1.1   wangxiaodong  2022/10/21   improve functions
 */

#include "fassert.h"
#include "fdebug.h"
#include "fsata.h"
#include "fsata_hw.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

#define FSATA_DEBUG_TAG "FSATA_INTR"
#define FSATA_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSATA_WARN(format, ...)    FT_DEBUG_PRINT_W(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSATA_INFO(format, ...)    FT_DEBUG_PRINT_I(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSATA_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSATA_DEBUG_TAG, format, ##__VA_ARGS__)

/**
 * @name: FSataIrqEnable
 * @msg: enable sata interrupt mask
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u32} int_mask, interrupt enable mask
 * @return {void}
 */
void FSataIrqEnable(FSataCtrl *instance_p, u32 int_mask)
{
    u32 reg_value;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    u32 port = instance_p->private_data;
    u32 i;
    for (i = 0; i < instance_p->n_ports; i++)
    {
        if (!(port & BIT(i)))
        {
            continue;
        }

        uintptr port_base_addr = instance_p->port[i].port_base_addr;
        FSATA_SETBIT(port_base_addr, FSATA_PORT_IRQ_MASK, int_mask);
    }
}

/**
 * @name: FSataIrqDisable
 * @msg: disable sata interrupt mask
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u32} int_mask, interrupt disable mask
 * @return {void}
 */
void FSataIrqDisable(FSataCtrl *instance_p, u32 int_mask)
{
    u32 reg_value;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    u32 port = instance_p->private_data;
    u32 i;
    for (i = 0; i < instance_p->n_ports; i++)
    {
        if (!(port & BIT(i)))
        {
            continue;
        }

        uintptr port_base_addr = instance_p->port[i].port_base_addr;

        FSATA_CLEARBIT(port_base_addr, FSATA_PORT_IRQ_MASK, int_mask);
    }
}

/**
 * @name: FSataSetHandler
 * @msg: set sata interrupt handler function
 * @param {FSataCtrl} *instance_p, pointer to the FSataCtrl instance
 * @param {u32} irq_type, interrupt type
 * @param {void} *func_pointer, interrupt handler function
 * @param {void} *call_back_ref, interrupt handler function argument
 * @return {FError} return FSATA_SUCCESS if successful, return others if failed
 */
FError FSataSetHandler(FSataCtrl *instance_p, u32 irq_type, void *func_pointer, void *call_back_ref)
{
    FError status = FT_SUCCESS;
    FASSERT(instance_p != NULL);
    FASSERT(func_pointer != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);

    switch (irq_type)
    {
        case FSATA_PORT_IRQ_D2H_REG_FIS:
            instance_p->fsata_dhrs_cb = ((FSataIrqCallBack)(void *)func_pointer);
            instance_p->dhrs_args = call_back_ref;
            break;

        case FSATA_PORT_IRQ_SDB_FIS:
            instance_p->fsata_sdbs_cb = ((FSataIrqCallBack)(void *)func_pointer);
            instance_p->sdbs_args = call_back_ref;
            break;

        case FSATA_PORT_IRQ_CONNECT:
            instance_p->fsata_pcs_cb = ((FSataIrqCallBack)(void *)func_pointer);
            instance_p->pcs_args = call_back_ref;
            break;

        case FSATA_PORT_IRQ_PIOS_FIS:
            instance_p->fsata_pss_cb = ((FSataIrqCallBack)(void *)func_pointer);
            instance_p->pss_args = call_back_ref;
            break;

        default:
            status = (FSATA_ERR_OPERATION);
            break;
    }
    return status;
}

/**
 * @name: FSataIrqHandler
 * @msg: sata interrupt handler entry
 * @param {void} *param, function parameters, users can set
 * @return {void}
 */
void FSataIrqHandler(s32 vector, void *param)
{
    FSataCtrl *instance_p = (FSataCtrl *)param;
    FSataConfig *config_p;

    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    u32 port = instance_p->private_data;
    u32 status;
    u32 mask_status = 0;
    uintptr base_addr = instance_p->config.base_addr;
    u32 irq_state = 0;
    u32 i = 0;

    uintptr port_base_addr = 0;

    for (i = 0; i < instance_p->n_ports; i++)
    {
        if (!(port & BIT(i)))
        {
            continue;
        }

        port_base_addr = instance_p->port[i].port_base_addr;
        irq_state = FSATA_READ_REG32(base_addr, FSATA_HOST_IRQ_STAT);
        status = FSATA_READ_REG32(port_base_addr, FSATA_PORT_IRQ_STAT);
        mask_status = FSATA_READ_REG32(port_base_addr, FSATA_PORT_IRQ_MASK);

        /* clear port first, host second */
        FSATA_WRITE_REG32(port_base_addr, FSATA_PORT_IRQ_STAT, status);
        FSATA_WRITE_REG32(base_addr, FSATA_HOST_IRQ_STAT, irq_state);

        if (status & mask_status & FSATA_PORT_IRQ_D2H_REG_FIS)
        {
            if (instance_p->fsata_dhrs_cb)
            {
                instance_p->fsata_dhrs_cb(instance_p->dhrs_args);
            }
        }

        if (status & mask_status & FSATA_PORT_IRQ_PIOS_FIS)
        {
            if (instance_p->fsata_pss_cb)
            {
                instance_p->fsata_pss_cb(instance_p->pss_args);
            }
        }

        if (status & mask_status & FSATA_PORT_IRQ_SDB_FIS)
        {
            if (instance_p->fsata_sdbs_cb)
            {
                instance_p->fsata_sdbs_cb(instance_p->sdbs_args);
            }
        }

        if (status & mask_status & FSATA_PORT_IRQ_DMAS_FIS)
        {
            if (instance_p->fsata_dss_cb)
            {
                instance_p->fsata_dss_cb(instance_p->dss_args);
            }
        }

        if (status & mask_status & FSATA_PORT_IRQ_CONNECT)
        {
            if (instance_p->fsata_pcs_cb)
            {
                instance_p->fsata_pcs_cb(instance_p->pcs_args);
            }

            /* reset hba */
            FSATA_WRITE_REG32(base_addr, FSATA_HOST_CTL, FSATA_HOST_RESET);
            FSataAhciInit(instance_p);
            FSataIrqEnable(instance_p, FSATA_PORT_IRQ_FREEZE);
        }

    }
}

