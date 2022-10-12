/**************************************************************************//**
 * @file     ehci_0.c
 * @version  V1.10
 * @brief   USB Host library EHCI (USB 2.0) host controller driver.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usb.h"
#include "hub.h"
#include "ehci.h"

#define _ehci           _ehci0
#define ehci_driver     ehci0_driver

#define EHCI_IRQHandler  EHCI0_IRQHandler

//static uint16_t  port_mask = 0x0001;
static ISO_EP_T  *iso_ep_list;          /* list of activated isochronous pipes        */

#include "_ehci.c_"
#include "_ehci_iso.c_"

HC_DRV_T  ehci0_driver =
{
    ehci_init,               /* init               */
    ehci_shutdown,           /* shutdown           */
    ehci_suspend,            /* suspend            */
    ehci_resume,             /* resume             */
    ehci_ctrl_xfer,          /* ctrl_xfer          */
    ehci_bulk_xfer,          /* bulk_xfer          */
    ehci_int_xfer,           /* int_xfer           */
    ehci_iso_xfer,           /* iso_xfer           */
    ehci_quit_xfer,          /* quit_xfer          */
    ehci_rh_port_reset,      /* rthub_port_reset   */
    ehci_rh_polling,         /* rthub_polling      */
};


