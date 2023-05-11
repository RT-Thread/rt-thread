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
 * FilePath: fusb_generic_hub.h
 * Date: 2022-02-11 13:33:11
 * LastEditTime: 2022-02-18 09:20:23
 * Description:  This files is for definition of generic hub function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/2/7    init commit
 */

#ifndef  FUSB_GENERIC_HUB_H
#define  FUSB_GENERIC_HUB_H

#include "fusb_private.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    /* negative results denote an error */

    /* returns 1 if the hub's status changed since the last call (optional) */
    FUsbTransCode(*hub_status_changed)(FUsbDev *);
    /* returns 1 if the port's status changed since the last call */
    FUsbTransCode(*port_status_changed)(FUsbDev *, int port);
    /* returns 1 if something is connected to the port */
    FUsbTransCode(*port_connected)(FUsbDev *, int port);
    /* returns 1 if port is currently resetting */
    FUsbTransCode(*port_in_reset)(FUsbDev *, int port);
    /* returns 1 if the port is enabled */
    FUsbTransCode(*port_enabled)(FUsbDev *, int port);
    /* returns speed if port is enabled, negative value if not */
    FUsbSpeed(*port_speed)(FUsbDev *, int port);

    /* enables (powers up) a port (optional) */
    FUsbTransCode(*enable_port)(FUsbDev *, int port);
    /* disables (powers down) a port (optional) */
    FUsbTransCode(*disable_port)(FUsbDev *, int port);
    /* starts a port reset (required if reset_port is set to a generic one from below) */
    FUsbTransCode(*start_port_reset)(FUsbDev *, int port);

    /* performs a port reset (optional, generic implementations below) */
    FUsbTransCode(*reset_port)(FUsbDev *, int port);
} FUsbGenericHubOps;

typedef struct
{
    int num_ports;
    /* port numbers are always 1 based,
       so we waste one int for convenience */
    int *ports; /* allocated to sizeof(*ports)*(num_ports+1) */
#define FUSB_NO_DEV_ADDR -1

    const FUsbGenericHubOps *ops;

    void *data;
} FUsbGenericHub;

void FUsbGenericHubDestory(FUsbDev *);
int FUsbGenericHubWaitForPort(FUsbDev *const dev, const int port,
                              const int wait_for,
                              int (*const port_op)(FUsbDev *, int),
                              int timeout_steps, const int step_us);
int  FUsbGenericHubResetPort(FUsbDev *, int port);
int  FUsbGenericHubScanPort(FUsbDev *, int port);
/* the provided generic_hub_ops struct has to be static */
int FUsbGenericHubInit(FUsbDev *, int num_ports, const FUsbGenericHubOps *);

#define FUSB_GEN_HUB_GET(FUsbDev) ((FUsbGenericHub *)(FUsbDev)->data)

#ifdef __cplusplus
}
#endif


#endif
