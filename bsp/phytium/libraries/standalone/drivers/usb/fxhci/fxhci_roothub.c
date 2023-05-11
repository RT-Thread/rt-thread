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
 * FilePath: fxhci_roothub.c
 * Date: 2022-02-11 13:33:12
 * LastEditTime: 2022-02-18 09:17:02
 * Description:  This files is for implementation of XHCI roothub function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#include "fdebug.h"

#include "fusb.h"
#include "fusb_generic_hub.h"
#include "fxhci_private.h"

#define FUSB_DEBUG_TAG "FXHCI_ROOTHUB"
#define FUSB_ERROR(format, ...)   FT_DEBUG_PRINT_E(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_WARN(format, ...)    FT_DEBUG_PRINT_W(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_INFO(format, ...)    FT_DEBUG_PRINT_I(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)
#define FUSB_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FUSB_DEBUG_TAG, format, ##__VA_ARGS__)

static int FXhciRootHubStatusChanged(FUsbDev *const dev)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 reg_val = FXhciReadOper32(&xhci->mmio, FXHCI_REG_OP_USBSTS);
    const int changed = !!(FXHCI_REG_OP_USBSTS_PCD & reg_val);

    /* clear port change bit */
    if (changed)
    {
        reg_val &= FXHCI_REG_OP_USBSTS_PRSRV_MASK;
        reg_val |= FXHCI_REG_OP_USBSTS_PCD;
        FXhciWriteOper32(&xhci->mmio, FXHCI_REG_OP_USBSTS, reg_val);
    }

    return changed;
}

static int FXhciRootHubPortStatusChanged(FUsbDev *const dev, const int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);
    const int changed = !!(portsc & (FXHCI_REG_OP_PORTS_PORTSC_CSC | FXHCI_REG_OP_PORTS_PORTSC_PRC));

    /* always clear all the status change bits */
    portsc &= FXHCI_REG_OP_PORTS_PORTSC_RW_MASK;
    portsc |= 0x00fe0000;
    FXhciWritePort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC, portsc);

    return changed;
}

static int FXhciRootHubPortConnected(FUsbDev *const dev, const int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);
    return portsc & FXHCI_REG_OP_PORTS_PORTSC_CCS;
}

static int FXhciRootHubPortInReset(FUsbDev *const dev, const int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);
    return !!(portsc & FXHCI_REG_OP_PORTS_PORTSC_PR);
}

static int FXhciRootHubPortEnabled(FUsbDev *const dev, const int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);
    return !!(portsc & FXHCI_REG_OP_PORTS_PORTSC_PED);
}

static FUsbSpeed FXhciRootHubPortSpeed(FUsbDev *const dev, const int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);

    if (portsc & FXHCI_REG_OP_PORTS_PORTSC_PED)
    {
        return FXHCI_REG_OP_PORTS_PORTSC_PORT_SPEED_GET(portsc) - 1;
    }
    else
    {
        return FUSB_UNKNOWN_SPEED;
    }
}

static int FXhciRootHubResetPort(FUsbDev *const dev, const int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);

    /* Trigger port reset. */
    portsc &= FXHCI_REG_OP_PORTS_PORTSC_RW_MASK;
    portsc |= FXHCI_REG_OP_PORTS_PORTSC_PR;
    FXhciWritePort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC, portsc);

    /* Wait for port_in_reset == 0, up to 150 * 1000us = 150ms */
    if (FUsbGenericHubWaitForPort(dev, port, 0, FXhciRootHubPortInReset,
                                  150, 1000) == 0)
    {
        FUSB_INFO("Xhci root hub: Reset timed out at port %d ", port);
    }
    else
    {
        portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);
        portsc &= FXHCI_REG_OP_PORTS_PORTSC_RW_MASK;
        portsc |= FXHCI_REG_OP_PORTS_PORTSC_PRC | FXHCI_REG_OP_PORTS_PORTSC_WRC;
        FXhciWritePort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC, portsc);
    }

    return 0;
}

static int FXhciRootHubEnablePort(FUsbDev *const dev, int port)
{
    FXhci *const xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);
    u32 portsc = FXhciReadPort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC);

    /*
    * Before sending commands to a port, the Port Power in
    * PORTSC register should be enabled.
    */
    portsc &= FXHCI_REG_OP_PORTS_PORTSC_RW_MASK;
    portsc |= FXHCI_REG_OP_PORTS_PORTSC_PP;
    FXhciWritePort32(&xhci->mmio, port - 1, FXHCI_REG_OP_PORTS_PORTSC, portsc);

    return 0;
}

static const FUsbGenericHubOps FXHCI_ROOTHUB_OPS =
{
    .hub_status_changed = FXhciRootHubStatusChanged,
    .port_status_changed    = FXhciRootHubPortStatusChanged,
    .port_connected     = FXhciRootHubPortConnected,
    .port_in_reset      = FXhciRootHubPortInReset,
    .port_enabled       = FXhciRootHubPortEnabled,
    .port_speed         = FXhciRootHubPortSpeed,
    .enable_port        = FXhciRootHubEnablePort,
    .disable_port       = NULL,
    .start_port_reset   = NULL,
    .reset_port     = FXhciRootHubResetPort,
};

/**
 * @name: FXhciRootHubInit
 * @msg: 初始化Roothub
 * @return {*}
 * @param {FUsbDev} *dev, Roothub实例
 */
void FXhciRootHubInit(FUsbDev *dev)
{
    u32 reg_val;
    FXhci *xhci = FXHCI_INST_GET(dev->controller);
    FASSERT(xhci);

    /* we can set them here because a root hub _really_ shouldn't
       appear elsewhere */
    dev->address = 0;
    dev->hub  = FUSB_NO_HUB;
    dev->port = FUSB_NO_PORT;

    reg_val = FXhciReadCap32(&xhci->mmio, FXHCI_REG_CAP_HCSPARAMS1);
    const int num_ports = FXHCI_REG_CAP_HCSPARAMS1_MAX_PORTS_GET(reg_val); /* TODO: maybe we need to read extended caps */

    FUsbGenericHubInit(dev, num_ports, &FXHCI_ROOTHUB_OPS);

    FUSB_INFO("Xhci: root hub init done. ");
}
