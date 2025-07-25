/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_hc_ohci.h"

/* Frame Interval / Periodic Start.
 *
 * At 12Mbps, there are 12000 bit time in each 1Msec frame.
 */

#define OHCI_FMINTERVAL_FI    (12000 - 1)
#define OHCI_FMINTERVAL_FSMPS ((6 * (OHCI_FMINTERVAL_FI - 210)) / 7)
#define DEFAULT_FMINTERVAL    ((OHCI_FMINTERVAL_FSMPS << OHCI_FMINT_FSMPS_SHIFT) | OHCI_FMINTERVAL_FI)
#define DEFAULT_PERSTART      ((OHCI_FMINTERVAL_FI * 9) / 10)

struct ohci_hcd g_ohci_hcd[CONFIG_USBHOST_MAX_BUS];

USB_NOCACHE_RAM_SECTION struct ohci_ed_hw g_ohci_ed_pool[CONFIG_USBHOST_MAX_BUS][CONFIG_USB_OHCI_ED_NUM];
USB_NOCACHE_RAM_SECTION struct ohci_hcca ohci_hcca[CONFIG_USBHOST_MAX_BUS];

int ohci_init(struct usbh_bus *bus)
{
    volatile uint32_t timeout = 0;
    uint32_t regval;
    struct ohci_ed_hw *ed;

    memset(&g_ohci_hcd[bus->hcd.hcd_id], 0, sizeof(struct ohci_hcd));
    memset(g_ohci_ed_pool[bus->hcd.hcd_id], 0, sizeof(struct ohci_ed_hw) * CONFIG_USB_OHCI_ED_NUM);

    for (uint32_t i = 0; i < 32; i++) {
        ohci_hcca[bus->hcd.hcd_id].inttbl[i] = 0;
    }

    for (uint8_t index = 0; index < CONFIG_USB_OHCI_ED_NUM; index++) {
        ed = &g_ohci_ed_pool[bus->hcd.hcd_id][index];
        if ((uint32_t)&ed->hw % 32) {
            USB_LOG_ERR("struct ohci_ed_hw is not align 32\r\n");
            return -USB_ERR_INVAL;
        }
        for (uint8_t i = 0; i < CONFIG_USB_OHCI_TD_NUM; i++) {
            if ((uint32_t)&ed->td_pool[i] % 32) {
                USB_LOG_ERR("struct ohci_td_hw is not align 32\r\n");
                return -USB_ERR_INVAL;
            }
        }
    }

    for (uint8_t index = 0; index < CONFIG_USB_OHCI_ED_NUM; index++) {
        ed = &g_ohci_ed_pool[bus->hcd.hcd_id][index];
        ed->waitsem = usb_osal_sem_create(0);
    }

    USB_LOG_INFO("OHCI hcrevision:0x%02x\r\n", (unsigned int)OHCI_HCOR->hcrevision);

    OHCI_HCOR->hcintdis = OHCI_INT_MIE;
    OHCI_HCOR->hccontrol = 0;

    OHCI_HCOR->hccmdsts = OHCI_CMDST_HCR;
    while (OHCI_HCOR->hccmdsts & OHCI_CMDST_HCR) {
        usb_osal_msleep(1);
        timeout++;
        if (timeout > 100) {
            return -USB_ERR_TIMEOUT;
        }
    }

    OHCI_HCOR->hcfminterval = DEFAULT_FMINTERVAL;
    OHCI_HCOR->hcperiodicstart = DEFAULT_PERSTART;
    OHCI_HCOR->hclsthreshold = 0x628;

    OHCI_HCOR->hccontrolheaded = 0;
    OHCI_HCOR->hcbulkheaded = 0;
    OHCI_HCOR->hchcca = (uintptr_t)&ohci_hcca[bus->hcd.hcd_id];

    /* Clear pending interrupts */
    regval = OHCI_HCOR->hcintsts;
    OHCI_HCOR->hcintsts = regval;

    /* Put HC in operational state */
    regval = OHCI_HCOR->hccontrol;
    regval &= ~OHCI_CTRL_CBSR;
    regval &= ~OHCI_CTRL_HCFS_MASK;
    regval |= OHCI_CTRL_HCFS_OPER;
    regval |= OHCI_CTRL_CBSR;
    regval |= OHCI_CTRL_CLE;
    OHCI_HCOR->hccontrol = regval;

    g_ohci_hcd[bus->hcd.hcd_id].n_ports = OHCI_HCOR->hcrhdescriptora & OHCI_RHDESCA_NDP_MASK;
    USB_LOG_INFO("OHCI n_ports:%d\r\n", g_ohci_hcd[bus->hcd.hcd_id].n_ports);

    OHCI_HCOR->hcrhdescriptora &= ~OHCI_RHDESCA_PSM;
    OHCI_HCOR->hcrhdescriptora &= ~OHCI_RHDESCA_NPS;

    /* Set global power in HcRhStatus */
    OHCI_HCOR->hcrhsts = OHCI_RHSTATUS_SGP;
    usb_osal_msleep(20);

    /* Enable OHCI interrupts */
    OHCI_HCOR->hcinten = OHCI_INT_WDH | OHCI_INT_RHSC | OHCI_INT_MIE;

    return 0;
}

int ohci_deinit(struct usbh_bus *bus)
{
    uint32_t regval;
    struct ohci_ed_hw *ed;

    /* Disable OHCI interrupts */
    OHCI_HCOR->hcintdis = OHCI_INT_WDH | OHCI_INT_RHSC | OHCI_INT_MIE;

    /* Clear pending interrupts */
    regval = OHCI_HCOR->hcintsts;
    OHCI_HCOR->hcintsts = regval;

    OHCI_HCOR->hcrhsts &= ~OHCI_RHSTATUS_SGP;

    regval = OHCI_HCOR->hccontrol;
    regval &= ~OHCI_CTRL_HCFS_MASK;
    regval |= OHCI_CTRL_HCFS_SUSPEND;
    OHCI_HCOR->hccontrol = regval;

    for (uint8_t index = 0; index < CONFIG_USB_OHCI_ED_NUM; index++) {
        ed = &g_ohci_ed_pool[bus->hcd.hcd_id][index];
        usb_osal_sem_delete(ed->waitsem);
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

    nports = g_ohci_hcd[bus->hcd.hcd_id].n_ports;

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
                        temp = OHCI_RHPORTST_CCS;
                        break;
                    case HUB_PORT_FEATURE_SUSPEND:
                        temp = OHCI_HCOR->hccontrol;
                        temp &= ~OHCI_CTRL_HCFS_MASK;
                        temp |= OHCI_CTRL_HCFS_RESUME;
                        OHCI_HCOR->hccontrol = temp;

                        usb_osal_msleep(20);

                        temp = OHCI_HCOR->hccontrol;
                        temp &= ~OHCI_CTRL_HCFS_MASK;
                        temp |= OHCI_CTRL_HCFS_OPER;
                        OHCI_HCOR->hccontrol = temp;

                        temp = OHCI_RHPORTST_POCI;
                        break;
                    case HUB_PORT_FEATURE_C_SUSPEND:
                        temp = OHCI_RHPORTST_PSSC;
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        OHCI_HCOR->hcrhsts = OHCI_RHSTATUS_CGP;
                        temp = OHCI_RHPORTST_LSDA;
                        break;
                    case HUB_PORT_FEATURE_C_CONNECTION:
                        temp = OHCI_RHPORTST_CSC;
                        break;
                    case HUB_PORT_FEATURE_C_ENABLE:
                        temp = OHCI_RHPORTST_PESC;
                        break;
                    case HUB_PORT_FEATURE_C_OVER_CURREN:
                        temp = OHCI_RHPORTST_OCIC;
                        break;
                    case HUB_PORT_FEATURE_C_RESET:
                        temp = OHCI_RHPORTST_PRSC;
                        break;
                    default:
                        return -USB_ERR_NOTSUPP;
                }
                OHCI_HCOR->hcrhportsts[port - 1] = temp;
                break;
            case HUB_REQUEST_SET_FEATURE:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                switch (setup->wValue) {
                    case HUB_PORT_FEATURE_SUSPEND:
                        temp = OHCI_HCOR->hccontrol;
                        temp &= ~OHCI_CTRL_HCFS_MASK;
                        temp |= OHCI_CTRL_HCFS_SUSPEND;
                        OHCI_HCOR->hccontrol = temp;

                        break;
                    case HUB_PORT_FEATURE_POWER:
                        OHCI_HCOR->hcrhsts = OHCI_RHSTATUS_SGP;
                        break;
                    case HUB_PORT_FEATURE_RESET:
                        OHCI_HCOR->hcrhportsts[port - 1] = OHCI_RHPORTST_PRS;

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

    if (usbsts & OHCI_INT_RHSC) {
        OHCI_HCOR->hcintsts = OHCI_INT_RHSC;
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
        OHCI_HCOR->hcintsts = OHCI_INT_WDH;
    }
}

#ifndef CONFIG_USB_EHCI_WITH_OHCI
__WEAK void usb_hc_low_level_init(struct usbh_bus *bus)
{
    (void)bus;
}

__WEAK void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    (void)bus;
}

int usb_hc_init(struct usbh_bus *bus)
{
    usb_hc_low_level_init(bus);
    return ohci_init(bus);
}

int usb_hc_deinit(struct usbh_bus *bus)
{
    ohci_deinit(bus);
    usb_hc_low_level_deinit(bus);
    return 0;
}

int usbh_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf)
{
    return ohci_roothub_control(bus, setup, buf);
}

int usbh_submit_urb(struct usbh_urb *urb)
{
    return ohci_submit_urb(urb);
}

int usbh_kill_urb(struct usbh_urb *urb)
{
    return ohci_kill_urb(urb);
}

void USBH_IRQHandler(uint8_t busid)
{
    OHCI_IRQHandler(busid);
}
#endif