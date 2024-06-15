/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_ohci_priv.h"
#include "usb_ehci_priv.h"

int ohci_init(struct usbh_bus *bus)
{
    volatile uint32_t timeout = 0;
    uint32_t regval;

    USB_LOG_INFO("OHCI hcrevision:0x%02x\r\n", (unsigned int)OHCI_HCOR->hcrevision);

    OHCI_HCOR->hccontrol = 0;
    OHCI_HCOR->hccontrolheaded = 0;
    OHCI_HCOR->hcbulkheaded = 0;

    OHCI_HCOR->hccmdsts = OHCI_CMDST_HCR;
    while (OHCI_HCOR->hccmdsts & OHCI_CMDST_HCR) {
        usb_osal_msleep(1);
        timeout++;
        if (timeout > 100) {
            return -USB_ERR_TIMEOUT;
        }
    }

    /* Frame Interval / Periodic Start.
    *
    * At 12Mbps, there are 12000 bit time in each 1Msec frame.
    */

#define BITS_PER_FRAME     12000
#define FI                 (BITS_PER_FRAME - 1)
#define FSMPS              ((6 * (FI - 210)) / 7)
#define DEFAULT_FMINTERVAL ((FSMPS << OHCI_FMINT_FSMPS_SHIFT) | FI)
#define DEFAULT_PERSTART   (((9 * BITS_PER_FRAME) / 10) - 1)

    OHCI_HCOR->hcfminterval = DEFAULT_FMINTERVAL;
    OHCI_HCOR->hcperiodicstart = DEFAULT_PERSTART;

    /* Put HC in operational state */
    regval = OHCI_HCOR->hccontrol;
    regval &= ~OHCI_CTRL_HCFS_MASK;
    regval |= OHCI_CTRL_HCFS_OPER;
    OHCI_HCOR->hccontrol = regval;

    /* Set global power in HcRhStatus */
    OHCI_HCOR->hcrhsts = OHCI_RHSTATUS_SGP;

    /* Set HCCA base address */
    OHCI_HCOR->hchcca = 0;

    /* Clear pending interrupts */
    regval = OHCI_HCOR->hcintsts;
    OHCI_HCOR->hcintsts = regval;

    for (uint8_t port = 0; port < g_ehci_hcd[bus->hcd.hcd_id].n_pcc; port++) {
        regval = OHCI_HCOR->hcrhportsts[port];
        regval |= OHCI_RHPORTST_PPS;
        OHCI_HCOR->hcrhportsts[port] = regval;
    }

    /* Enable OHCI interrupts */
    OHCI_HCOR->hcinten = OHCI_INT_SO | OHCI_INT_RD | OHCI_INT_UE | OHCI_INT_OC |
                         OHCI_INT_WDH | OHCI_INT_RHSC | OHCI_INT_MIE;

    return 0;
}

int ohci_deinit(struct usbh_bus *bus)
{
    uint32_t regval;

    /* Disable OHCI interrupts */
    OHCI_HCOR->hcintdis = OHCI_INT_SO | OHCI_INT_RD | OHCI_INT_UE | OHCI_INT_OC |
                          OHCI_INT_WDH | OHCI_INT_RHSC | OHCI_INT_MIE;

    for (uint8_t port = 0; port < g_ehci_hcd[bus->hcd.hcd_id].n_pcc; port++) {
        regval = OHCI_HCOR->hcrhportsts[port];
        regval &= ~OHCI_RHPORTST_PPS;
        OHCI_HCOR->hcrhportsts[port] = regval;
    }

    return 0;
}

uint16_t ohci_get_frame_number(struct usbh_bus *bus)
{
    return OHCI_HCOR->hcfmnumber;
}

int ohci_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf)
{
    uint8_t nports;
    uint8_t port;
    uint32_t temp;

    nports = g_ehci_hcd[bus->hcd.hcd_id].n_pcc;

    port = setup->wIndex;
    if (setup->bmRequestType & USB_REQUEST_RECIPIENT_DEVICE) {
        switch (setup->bRequest) {
            case HUB_REQUEST_CLEAR_FEATURE:
                switch (setup->wValue) {
                    case HUB_FEATURE_HUB_C_LOCALPOWER:
                        break;
                    case HUB_FEATURE_HUB_C_OVERCURRENT:
                        break;
                    default:
                        return -USB_ERR_NOTSUPP;
                }
                break;
            case HUB_REQUEST_SET_FEATURE:
                switch (setup->wValue) {
                    case HUB_FEATURE_HUB_C_LOCALPOWER:
                        break;
                    case HUB_FEATURE_HUB_C_OVERCURRENT:
                        break;
                    default:
                        return -USB_ERR_NOTSUPP;
                }
                break;
            case HUB_REQUEST_GET_DESCRIPTOR:
                break;
            case HUB_REQUEST_GET_STATUS:
                memset(buf, 0, 4);
                break;
            default:
                break;
        }
    } else if (setup->bmRequestType & USB_REQUEST_RECIPIENT_OTHER) {
        switch (setup->bRequest) {
            case HUB_REQUEST_CLEAR_FEATURE:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                switch (setup->wValue) {
                    case HUB_PORT_FEATURE_ENABLE:
                        break;
                    case HUB_PORT_FEATURE_SUSPEND:

                    case HUB_PORT_FEATURE_C_SUSPEND:
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        break;
                    case HUB_PORT_FEATURE_C_CONNECTION:
                        OHCI_HCOR->hcrhportsts[port - 1] |= OHCI_RHPORTST_CSC;
                        break;
                    case HUB_PORT_FEATURE_C_ENABLE:
                        OHCI_HCOR->hcrhportsts[port - 1] |= OHCI_RHPORTST_PESC;
                        break;
                    case HUB_PORT_FEATURE_C_OVER_CURREN:
                        OHCI_HCOR->hcrhportsts[port - 1] |= OHCI_RHPORTST_OCIC;
                        break;
                    case HUB_PORT_FEATURE_C_RESET:
                        OHCI_HCOR->hcrhportsts[port - 1] |= OHCI_RHPORTST_PRSC;
                        break;
                    default:
                        return -USB_ERR_NOTSUPP;
                }
                break;
            case HUB_REQUEST_SET_FEATURE:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                switch (setup->wValue) {
                    case HUB_PORT_FEATURE_SUSPEND:
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        break;
                    case HUB_PORT_FEATURE_RESET:
                        OHCI_HCOR->hcrhportsts[port - 1] |= OHCI_RHPORTST_PRS;

                        while (OHCI_HCOR->hcrhportsts[port - 1] & OHCI_RHPORTST_PRS) {
                        }
                        break;

                    default:
                        return -USB_ERR_NOTSUPP;
                }
                break;
            case HUB_REQUEST_GET_STATUS:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }
                temp = OHCI_HCOR->hcrhportsts[port - 1];

                memcpy(buf, &temp, 4);
                break;
            default:
                break;
        }
    }
    return 0;
}

int ohci_submit_urb(struct usbh_urb *urb)
{
    return -USB_ERR_NOTSUPP;
}

int ohci_kill_urb(struct usbh_urb *urb)
{
    return -USB_ERR_NOTSUPP;
}

void OHCI_IRQHandler(uint8_t busid)
{
    uint32_t usbsts;
    struct usbh_bus *bus;

    bus = &g_usbhost_bus[busid];

    usbsts = OHCI_HCOR->hcintsts & OHCI_HCOR->hcinten;
    OHCI_HCOR->hcintsts = usbsts;

    if (usbsts & OHCI_INT_RHSC) {
        for (int port = 0; port < CONFIG_USBHOST_MAX_RHPORTS; port++) {
            uint32_t portsc = OHCI_HCOR->hcrhportsts[port];

            if (portsc & OHCI_RHPORTST_CSC) {
                if (OHCI_HCOR->hcrhsts & OHCI_RHSTATUS_DRWE) {
                    /* If DRWE is set, Connect Status Change indicates a remote wake-up event */
                } else {
                    if (portsc & OHCI_RHPORTST_CCS) {
                    } else {
                    }
                    bus->hcd.roothub.int_buffer[0] |= (1 << (port + 1));
                    usbh_hub_thread_wakeup(&bus->hcd.roothub);
                }
            }
        }
    }
    if (usbsts & OHCI_INT_WDH) {
    }
}