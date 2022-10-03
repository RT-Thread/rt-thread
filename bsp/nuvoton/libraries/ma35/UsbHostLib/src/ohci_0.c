/**************************************************************************//**
 * @file     ohci.c
 * @version  V1.10
 * @brief   USB Host library OHCI (USB 1.1) host controller driver.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usb.h"
#include "hub.h"
#include "ohci.h"

/// @cond HIDDEN_SYMBOLS

#define _ohci           _ohci0
#define ohci_driver     ohci0_driver

#define OHCI_IRQHandler   OHCI0_IRQHandler

#include "_ohci.c_"

HC_DRV_T  ohci0_driver =
{
    ohci_init,               /* init               */
    ohci_shutdown,           /* shutdown           */
    ohci_suspend,            /* suspend            */
    ohci_resume,             /* resume             */
    ohci_ctrl_xfer,          /* ctrl_xfer          */
    ohci_bulk_xfer,          /* bulk_xfer          */
    ohci_int_xfer,           /* int_xfer           */
    ohci_iso_xfer,           /* iso_xfer           */
    ohci_quit_xfer,          /* quit_xfer          */
    ohci_rh_port_reset,      /* rthub_port_reset   */
    ohci_rh_polling,         /* rthub_polling      */
};


