/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usb_hc_ehci.h"
#ifdef CONFIG_USB_EHCI_WITH_OHCI
#include "usb_hc_ohci.h"
#endif

#define EHCI_TUNE_CERR    3 /* 0-3 qtd retries; 0 == don't stop */
#define EHCI_TUNE_RL_HS   4 /* nak throttle; see 4.9 */
#define EHCI_TUNE_RL_TT   0
#define EHCI_TUNE_MULT_HS 1 /* 1-3 transactions/uframe; 4.10.3 */
#define EHCI_TUNE_MULT_TT 1

struct ehci_hcd g_ehci_hcd[CONFIG_USBHOST_MAX_BUS];

USB_NOCACHE_RAM_SECTION struct ehci_qh_hw ehci_qh_pool[CONFIG_USBHOST_MAX_BUS][CONFIG_USB_EHCI_QH_NUM];

/* The head of the asynchronous queue */
USB_NOCACHE_RAM_SECTION struct ehci_qh_hw g_async_qh_head[CONFIG_USBHOST_MAX_BUS];
/* The head of the periodic queue */
USB_NOCACHE_RAM_SECTION struct ehci_qh_hw g_periodic_qh_head[CONFIG_USBHOST_MAX_BUS];

/* The frame list */
USB_NOCACHE_RAM_SECTION uint32_t g_framelist[CONFIG_USBHOST_MAX_BUS][USB_ALIGN_UP(CONFIG_USB_EHCI_FRAME_LIST_SIZE, 1024)] __attribute__((aligned(4096)));

static struct ehci_qh_hw *ehci_qh_alloc(struct usbh_bus *bus)
{
    struct ehci_qh_hw *qh;
    struct ehci_qtd_hw *qtd;
    size_t flags;

    flags = usb_osal_enter_critical_section();
    for (uint32_t i = 0; i < CONFIG_USB_EHCI_QH_NUM; i++) {
        if (!g_ehci_hcd[bus->hcd.hcd_id].ehci_qh_used[i]) {
            g_ehci_hcd[bus->hcd.hcd_id].ehci_qh_used[i] = true;
            usb_osal_leave_critical_section(flags);

            qh = &ehci_qh_pool[bus->hcd.hcd_id][i];
            memset(&qh->hw, 0, sizeof(struct ehci_qh));
            qh->hw.hlp = QTD_LIST_END;
            qh->hw.overlay.next_qtd = QTD_LIST_END;
            qh->hw.overlay.alt_next_qtd = QTD_LIST_END;
            qh->urb = NULL;

            for (uint32_t j = 0; j < CONFIG_USB_EHCI_QTD_NUM; j++) {
                qtd = &qh->qtd_pool[j];
                qtd->hw.next_qtd = QTD_LIST_END;
                qtd->hw.alt_next_qtd = QTD_LIST_END;
                qtd->hw.token = QTD_TOKEN_STATUS_HALTED;
                qtd->urb = NULL;
            }

            return qh;
        }
    }
    usb_osal_leave_critical_section(flags);
    return NULL;
}

static void ehci_qh_free(struct usbh_bus *bus, struct ehci_qh_hw *qh)
{
    size_t flags;

    for (uint32_t i = 0; i < CONFIG_USB_EHCI_QH_NUM; i++) {
        if (&ehci_qh_pool[bus->hcd.hcd_id][i] == qh) {
            flags = usb_osal_enter_critical_section();
            g_ehci_hcd[bus->hcd.hcd_id].ehci_qh_used[i] = false;
            usb_osal_leave_critical_section(flags);

            qh->urb = NULL;
            return;
        }
    }
}

static inline void ehci_qh_add_head(struct ehci_qh_hw *head, struct ehci_qh_hw *n)
{
    n->hw.hlp = head->hw.hlp;
    head->hw.hlp = QH_HLP_QH(n);
}

static inline void ehci_qh_remove(struct ehci_qh_hw *head, struct ehci_qh_hw *n)
{
    struct ehci_qh_hw *tmp = head;

    while (EHCI_ADDR2QH(tmp->hw.hlp) && EHCI_ADDR2QH(tmp->hw.hlp) != n) {
        tmp = EHCI_ADDR2QH(tmp->hw.hlp);
    }

    if (tmp) {
        tmp->hw.hlp = n->hw.hlp;
    }
}

static int ehci_caculate_smask(int binterval)
{
    int order, interval;

    interval = 1;
    while (binterval > 1) {
        interval *= 2;
        binterval--;
    }

    if (interval < 2) /* interval 1 */
        return 0xFF;
    if (interval < 4) /* interval 2 */
        return 0x55;
    if (interval < 8) /* interval 4 */
        return 0x22;
    for (order = 0; (interval > 1); order++) {
        interval >>= 1;
    }
    return (0x1 << (order % 8));
}

static void ehci_qh_fill(struct ehci_qh_hw *qh,
                         uint8_t dev_addr,
                         uint8_t ep_addr,
                         uint8_t ep_type,
                         uint16_t ep_mps,
                         uint8_t ep_mult,
                         uint8_t ep_interval,
                         uint8_t speed,
                         uint8_t hubaddr,
                         uint8_t hubport)
{
    uint32_t epchar = 0;
    uint32_t epcap = 0;

    /* QH endpoint characteristics:
     *
     * FIELD    DESCRIPTION
     * -------- -------------------------------
     * DEVADDR  Device address
     * I        Inactivate on Next Transaction
     * ENDPT    Endpoint number
     * EPS      Endpoint speed
     * DTC      Data toggle control
     * MAXPKT   Max packet size
     * C        Control endpoint
     * RL       NAK count reloaded
    */

    /* QH endpoint capabilities
     *
     * FIELD    DESCRIPTION
     * -------- -------------------------------
     * SSMASK   Interrupt Schedule Mask
     * SCMASK   Split Completion Mask
     * HUBADDR  Hub Address
     * PORT     Port number
     * MULT     High band width multiplier
     */

    epchar |= ((ep_addr & 0xf) << QH_EPCHAR_ENDPT_SHIFT);
    epchar |= (dev_addr << QH_EPCHAR_DEVADDR_SHIFT);
    epchar |= (ep_mps << QH_EPCHAR_MAXPKT_SHIFT);

    if (ep_type == USB_ENDPOINT_TYPE_CONTROL) {
        epchar |= QH_EPCHAR_DTC; /* toggle from qtd */
    }

    switch (speed) {
        case USB_SPEED_LOW:
            epchar |= QH_EPCHAR_EPS_LOW;
            __attribute__((fallthrough));
        case USB_SPEED_FULL:
            if (ep_type == USB_ENDPOINT_TYPE_CONTROL) {
                epchar |= QH_EPCHAR_C; /* for TT */
            }

            if (ep_type != USB_ENDPOINT_TYPE_INTERRUPT) {
                epchar |= (EHCI_TUNE_RL_TT << QH_EPCHAR_RL_SHIFT);
            }

            epcap |= QH_EPCAPS_MULT(EHCI_TUNE_MULT_TT);

            epcap |= QH_EPCAPS_HUBADDR(hubaddr);
            epcap |= QH_EPCAPS_PORT(hubport);

            if (ep_type == USB_ENDPOINT_TYPE_INTERRUPT) {
                epcap |= QH_EPCAPS_SSMASK(2);
                epcap |= QH_EPCAPS_SCMASK(0x78);
            }

            break;
        case USB_SPEED_HIGH:
            epchar |= QH_EPCHAR_EPS_HIGH;
            if (ep_type == USB_ENDPOINT_TYPE_CONTROL) {
                epchar |= (EHCI_TUNE_RL_HS << QH_EPCHAR_RL_SHIFT);

                epcap |= QH_EPCAPS_MULT(EHCI_TUNE_MULT_HS);
            } else if (ep_type == USB_ENDPOINT_TYPE_BULK) {
                epcap |= QH_EPCAPS_MULT(EHCI_TUNE_MULT_HS);
            } else {
                /* only for interrupt ep */
                epcap |= QH_EPCAPS_MULT(ep_mult);
                epcap |= ehci_caculate_smask(ep_interval);
            }
            break;

        default:
            break;
    }

    qh->hw.epchar = epchar;
    qh->hw.epcap = epcap;
}

static void ehci_qtd_bpl_fill(struct ehci_qtd_hw *qtd, uint32_t bufaddr, size_t buflen)
{
    uint32_t rest;

    qtd->hw.bpl[0] = bufaddr;
    rest = 0x1000 - (bufaddr & 0xfff);

    if (buflen < rest) {
        rest = buflen;
    } else {
        bufaddr += 0x1000;
        bufaddr &= ~0x0fff;

        for (int i = 1; rest < buflen && i < 5; i++) {
            qtd->hw.bpl[i] = bufaddr;
            bufaddr += 0x1000;

            if ((rest + 0x1000) < buflen) {
                rest += 0x1000;
            } else {
                rest = buflen;
            }
        }
    }
}

static void ehci_qtd_fill(struct ehci_qtd_hw *qtd, uint32_t bufaddr, size_t buflen, uint32_t token)
{
    /* qTD token
     *
     * FIELD    DESCRIPTION
     * -------- -------------------------------
     * STATUS   Status
     * PID      PID Code
     * CERR     Error Counter
     * CPAGE    Current Page
     * IOC      Interrupt on complete
     * NBYTES   Total Bytes to Transfer
     * TOGGLE   Data Toggle
     */

    qtd->hw.token = token;

    ehci_qtd_bpl_fill(qtd, bufaddr, buflen);
    qtd->length = buflen;
}

static struct ehci_qh_hw *ehci_control_urb_init(struct usbh_bus *bus, struct usbh_urb *urb, struct usb_setup_packet *setup, uint8_t *buffer, uint32_t buflen)
{
    struct ehci_qh_hw *qh = NULL;
    struct ehci_qtd_hw *qtd_setup = NULL;
    struct ehci_qtd_hw *qtd_data = NULL;
    struct ehci_qtd_hw *qtd_status = NULL;
    uint32_t token;
    size_t flags;

    qh = ehci_qh_alloc(bus);
    if (qh == NULL) {
        return NULL;
    }

    qtd_setup = &qh->qtd_pool[0];
    qtd_data = &qh->qtd_pool[1];
    qtd_status = &qh->qtd_pool[2];

    ehci_qh_fill(qh,
                 urb->hport->dev_addr,
                 urb->ep->bEndpointAddress,
                 USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes),
                 USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize),
                 0,
                 0,
                 urb->hport->speed,
                 urb->hport->parent->hub_addr,
                 urb->hport->port);

    /* fill setup qtd */
    token = QTD_TOKEN_STATUS_ACTIVE |
            QTD_TOKEN_PID_SETUP |
            ((uint32_t)EHCI_TUNE_CERR << QTD_TOKEN_CERR_SHIFT) |
            ((uint32_t)8 << QTD_TOKEN_NBYTES_SHIFT);

    ehci_qtd_fill(qtd_setup, (uintptr_t)setup, 8, token);
    qtd_setup->urb = urb;

    /* fill data qtd */
    if (setup->wLength > 0) {
        if ((setup->bmRequestType & 0x80) == 0x80) {
            token = QTD_TOKEN_PID_IN;
        } else {
            token = QTD_TOKEN_PID_OUT;
        }
        token |= QTD_TOKEN_STATUS_ACTIVE |
                 QTD_TOKEN_PID_OUT |
                 QTD_TOKEN_TOGGLE |
                 ((uint32_t)EHCI_TUNE_CERR << QTD_TOKEN_CERR_SHIFT) |
                 ((uint32_t)buflen << QTD_TOKEN_NBYTES_SHIFT);

        ehci_qtd_fill(qtd_data, (uintptr_t)buffer, buflen, token);
        qtd_data->urb = urb;
        qtd_setup->hw.next_qtd = EHCI_PTR2ADDR(qtd_data);
        qtd_data->hw.next_qtd = EHCI_PTR2ADDR(qtd_status);
    } else {
        qtd_setup->hw.next_qtd = EHCI_PTR2ADDR(qtd_status);
    }

    /* fill status qtd */
    if ((setup->bmRequestType & 0x80) == 0x80) {
        token = QTD_TOKEN_PID_OUT;
    } else {
        token = QTD_TOKEN_PID_IN;
    }
    token |= QTD_TOKEN_STATUS_ACTIVE |
             QTD_TOKEN_TOGGLE |
             QTD_TOKEN_IOC |
             ((uint32_t)EHCI_TUNE_CERR << QTD_TOKEN_CERR_SHIFT) |
             ((uint32_t)0 << QTD_TOKEN_NBYTES_SHIFT);

    ehci_qtd_fill(qtd_status, 0, 0, token);
    qtd_status->urb = urb;
    qtd_status->hw.next_qtd = QTD_LIST_END;

    /* update qh first qtd */
    qh->hw.curr_qtd = EHCI_PTR2ADDR(qtd_setup);
    qh->hw.overlay.next_qtd = EHCI_PTR2ADDR(qtd_setup);

    /* record qh first qtd */
    qh->first_qtd = EHCI_PTR2ADDR(qtd_setup);

    flags = usb_osal_enter_critical_section();

    qh->urb = urb;
    urb->hcpriv = qh;
    /* add qh into async list */
    ehci_qh_add_head(&g_async_qh_head[bus->hcd.hcd_id], qh);

    EHCI_HCOR->usbcmd |= EHCI_USBCMD_ASEN;

    usb_osal_leave_critical_section(flags);
    return qh;
}

static struct ehci_qh_hw *ehci_bulk_urb_init(struct usbh_bus *bus, struct usbh_urb *urb, uint8_t *buffer, uint32_t buflen)
{
    struct ehci_qh_hw *qh = NULL;
    struct ehci_qtd_hw *qtd = NULL;
    struct ehci_qtd_hw *first_qtd = NULL;
    struct ehci_qtd_hw *prev_qtd = NULL;
    uint32_t qtd_num = 0;
    uint32_t xfer_len = 0;
    uint32_t token;
    size_t flags;

    qh = ehci_qh_alloc(bus);
    if (qh == NULL) {
        return NULL;
    }

    ehci_qh_fill(qh,
                 urb->hport->dev_addr,
                 urb->ep->bEndpointAddress,
                 USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes),
                 USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize),
                 0,
                 0,
                 urb->hport->speed,
                 urb->hport->parent->hub_addr,
                 urb->hport->port);

    while (1) {
        qtd = &qh->qtd_pool[qtd_num];

        if (buflen > 0x4000) {
            xfer_len = 0x4000;
            buflen -= 0x4000;
        } else {
            xfer_len = buflen;
            buflen = 0;
        }

        if (urb->ep->bEndpointAddress & 0x80) {
            token = QTD_TOKEN_PID_IN;
        } else {
            token = QTD_TOKEN_PID_OUT;
        }

        token |= QTD_TOKEN_STATUS_ACTIVE |
                 ((uint32_t)EHCI_TUNE_CERR << QTD_TOKEN_CERR_SHIFT) |
                 ((uint32_t)xfer_len << QTD_TOKEN_NBYTES_SHIFT);

        if (buflen == 0) {
            token |= QTD_TOKEN_IOC;
        }

        ehci_qtd_fill(qtd, (uintptr_t)buffer, xfer_len, token);
        qtd->urb = urb;
        qtd->hw.next_qtd = QTD_LIST_END;
        buffer += xfer_len;

        if (prev_qtd) {
            prev_qtd->hw.next_qtd = EHCI_PTR2ADDR(qtd);
        } else {
            first_qtd = qtd;
        }
        prev_qtd = qtd;

        if (buflen == 0) {
            break;
        }
        qtd_num++;

        if (qtd_num == CONFIG_USB_EHCI_QTD_NUM) {
            return NULL;
        }
    }

    /* update qh first qtd */
    qh->hw.curr_qtd = EHCI_PTR2ADDR(first_qtd);
    qh->hw.overlay.next_qtd = EHCI_PTR2ADDR(first_qtd);

    /* update data toggle */
    if (urb->data_toggle) {
        qh->hw.overlay.token = QTD_TOKEN_TOGGLE;
    } else {
        qh->hw.overlay.token = 0;
    }

    /* record qh first qtd */
    qh->first_qtd = EHCI_PTR2ADDR(first_qtd);

    flags = usb_osal_enter_critical_section();

    qh->urb = urb;
    urb->hcpriv = qh;
    /* add qh into async list */
    ehci_qh_add_head(&g_async_qh_head[bus->hcd.hcd_id], qh);

    EHCI_HCOR->usbcmd |= EHCI_USBCMD_ASEN;

    usb_osal_leave_critical_section(flags);
    return qh;
}

static struct ehci_qh_hw *ehci_intr_urb_init(struct usbh_bus *bus, struct usbh_urb *urb, uint8_t *buffer, uint32_t buflen)
{
    struct ehci_qh_hw *qh = NULL;
    struct ehci_qtd_hw *qtd = NULL;
    struct ehci_qtd_hw *first_qtd = NULL;
    struct ehci_qtd_hw *prev_qtd = NULL;
    uint32_t qtd_num = 0;
    uint32_t xfer_len = 0;
    uint32_t token;
    size_t flags;

    qh = ehci_qh_alloc(bus);
    if (qh == NULL) {
        return NULL;
    }

    ehci_qh_fill(qh,
                 urb->hport->dev_addr,
                 urb->ep->bEndpointAddress,
                 USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes),
                 USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize),
                 USB_GET_MULT(urb->ep->wMaxPacketSize) + 1,
                 urb->ep->bInterval,
                 urb->hport->speed,
                 urb->hport->parent->hub_addr,
                 urb->hport->port);

    while (1) {
        qtd = &qh->qtd_pool[qtd_num];

        if (buflen > 0x4000) {
            xfer_len = 0x4000;
            buflen -= 0x4000;
        } else {
            xfer_len = buflen;
            buflen = 0;
        }

        if (urb->ep->bEndpointAddress & 0x80) {
            token = QTD_TOKEN_PID_IN;
        } else {
            token = QTD_TOKEN_PID_OUT;
        }

        token |= QTD_TOKEN_STATUS_ACTIVE |
                 ((uint32_t)EHCI_TUNE_CERR << QTD_TOKEN_CERR_SHIFT) |
                 ((uint32_t)xfer_len << QTD_TOKEN_NBYTES_SHIFT);

        if (buflen == 0) {
            token |= QTD_TOKEN_IOC;
        }

        ehci_qtd_fill(qtd, (uintptr_t)buffer, xfer_len, token);
        qtd->urb = urb;
        qtd->hw.next_qtd = QTD_LIST_END;
        buffer += xfer_len;

        if (prev_qtd) {
            prev_qtd->hw.next_qtd = EHCI_PTR2ADDR(qtd);
        } else {
            first_qtd = qtd;
        }
        prev_qtd = qtd;

        if (buflen == 0) {
            break;
        }
        qtd_num++;

        if (qtd_num == CONFIG_USB_EHCI_QTD_NUM) {
            return NULL;
        }
    }

    /* update qh first qtd */
    qh->hw.curr_qtd = EHCI_PTR2ADDR(first_qtd);
    qh->hw.overlay.next_qtd = EHCI_PTR2ADDR(first_qtd);

    /* update data toggle */
    if (urb->data_toggle) {
        qh->hw.overlay.token = QTD_TOKEN_TOGGLE;
    } else {
        qh->hw.overlay.token = 0;
    }

    /* record qh first qtd */
    qh->first_qtd = EHCI_PTR2ADDR(first_qtd);

    flags = usb_osal_enter_critical_section();

    qh->urb = urb;
    urb->hcpriv = qh;
    /* add qh into periodic list */
    ehci_qh_add_head(&g_periodic_qh_head[bus->hcd.hcd_id], qh);

    EHCI_HCOR->usbcmd |= EHCI_USBCMD_PSEN;

    usb_osal_leave_critical_section(flags);
    return qh;
}

static void ehci_urb_waitup(struct usbh_bus *bus, struct usbh_urb *urb)
{
    struct ehci_qh_hw *qh;

    qh = (struct ehci_qh_hw *)urb->hcpriv;
    qh->urb = NULL;
    urb->hcpriv = NULL;

    qh->remove_in_iaad = 0;

    if (urb->timeout) {
        usb_osal_sem_give(qh->waitsem);
    } else {
        ehci_qh_free(bus, qh);
    }

    if (urb->complete) {
        if (urb->errorcode < 0) {
            urb->complete(urb->arg, urb->errorcode);
        } else {
            urb->complete(urb->arg, urb->actual_length);
        }
    }
}

static void ehci_qh_scan_qtds(struct usbh_bus *bus, struct ehci_qh_hw *qhead, struct ehci_qh_hw *qh)
{
    struct ehci_qtd_hw *qtd;

    (void)bus;

    ehci_qh_remove(qhead, qh);

    qtd = EHCI_ADDR2QTD(qh->first_qtd);

    while (qtd) {
        qtd->urb->actual_length += (qtd->length - ((qtd->hw.token & QTD_TOKEN_NBYTES_MASK) >> QTD_TOKEN_NBYTES_SHIFT));

        qh->first_qtd = qtd->hw.next_qtd;
        qtd = EHCI_ADDR2QTD(qh->first_qtd);
    }
}

static void ehci_check_qh(struct usbh_bus *bus, struct ehci_qh_hw *qhead, struct ehci_qh_hw *qh)
{
    struct usbh_urb *urb;
    struct ehci_qtd_hw *qtd;
    uint32_t token;

    qtd = EHCI_ADDR2QTD(qh->first_qtd);

    if (qtd == NULL) {
        return;
    }

    while (qtd) {
        token = qtd->hw.token;

        if (token & QTD_TOKEN_STATUS_ERRORS) {
            break;
        } else if (token & QTD_TOKEN_STATUS_ACTIVE) {
            return;
        }

        qtd = EHCI_ADDR2QTD(qtd->hw.next_qtd);
    }

    urb = qh->urb;

    if ((token & QTD_TOKEN_STATUS_ERRORS) == 0) {
        if (token & QTD_TOKEN_TOGGLE) {
            urb->data_toggle = true;
        } else {
            urb->data_toggle = false;
        }
        urb->errorcode = 0;
    } else {
        if (token & QTD_TOKEN_STATUS_BABBLE) {
            urb->errorcode = -USB_ERR_BABBLE;
            urb->data_toggle = 0;
        } else if (token & QTD_TOKEN_STATUS_HALTED) {
            urb->errorcode = -USB_ERR_STALL;
            urb->data_toggle = 0;
        } else if (token & (QTD_TOKEN_STATUS_DBERR | QTD_TOKEN_STATUS_XACTERR)) {
            urb->errorcode = -USB_ERR_IO;
        }
    }

    ehci_qh_scan_qtds(bus, qhead, qh);

    if (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
        ehci_urb_waitup(bus, urb);
    } else {
        qh->remove_in_iaad = 1;

        EHCI_HCOR->usbcmd |= EHCI_USBCMD_IAAD;
    }
}

static void ehci_kill_qh(struct usbh_bus *bus, struct ehci_qh_hw *qhead, struct ehci_qh_hw *qh)
{
    struct ehci_qtd_hw *qtd;

    (void)bus;

    ehci_qh_remove(qhead, qh);

    qtd = EHCI_ADDR2QTD(qh->first_qtd);

    while (qtd) {
        qh->first_qtd = qtd->hw.next_qtd;
        qtd = EHCI_ADDR2QTD(qh->first_qtd);
    }
}

static int usbh_reset_port(struct usbh_bus *bus, const uint8_t port)
{
    volatile uint32_t timeout = 0;
    uint32_t regval;

#if defined(CONFIG_USB_EHCI_HPMICRO) && CONFIG_USB_EHCI_HPMICRO
    if ((*(volatile uint32_t *)(bus->hcd.reg_base + 0x224) & 0xc0) == (2 << 6)) { /* Hardcode for hpm */
        EHCI_HCOR->portsc[port - 1] |= (1 << 29);
    } else {
        EHCI_HCOR->portsc[port - 1] &= ~(1 << 29);
    }
#endif
    regval = EHCI_HCOR->portsc[port - 1];
    regval &= ~EHCI_PORTSC_PE;
    regval |= EHCI_PORTSC_RESET;
    EHCI_HCOR->portsc[port - 1] = regval;
    usb_osal_msleep(55);

    EHCI_HCOR->portsc[port - 1] &= ~EHCI_PORTSC_RESET;
    while ((EHCI_HCOR->portsc[port - 1] & EHCI_PORTSC_RESET) != 0) {
        usb_osal_msleep(1);
        timeout++;
        if (timeout > 100) {
            return -USB_ERR_TIMEOUT;
        }
    }

    return 0;
}

__WEAK void usb_hc_low_level_init(struct usbh_bus *bus)
{
    (void)bus;
}

__WEAK void usb_hc_low_level2_init(struct usbh_bus *bus)
{
    (void)bus;
}

__WEAK void usb_hc_low_level_deinit(struct usbh_bus *bus)
{
    (void)bus;
}

int usb_hc_init(struct usbh_bus *bus)
{
    struct ehci_qh_hw *qh;

    volatile uint32_t timeout = 0;
    uint32_t regval;

    memset(&g_ehci_hcd[bus->hcd.hcd_id], 0, sizeof(struct ehci_hcd));
    memset(ehci_qh_pool[bus->hcd.hcd_id], 0, sizeof(struct ehci_qh_hw) * CONFIG_USB_EHCI_QH_NUM);

    for (uint8_t index = 0; index < CONFIG_USB_EHCI_QH_NUM; index++) {
        qh = &ehci_qh_pool[bus->hcd.hcd_id][index];
        if ((uint32_t)&qh->hw % 32) {
            USB_LOG_ERR("struct ehci_qh_hw is not align 32\r\n");
            return -USB_ERR_INVAL;
        }
        for (uint8_t i = 0; i < CONFIG_USB_EHCI_QTD_NUM; i++) {
            if ((uint32_t)&qh->qtd_pool[i] % 32) {
                USB_LOG_ERR("struct ehci_qtd_hw is not align 32\r\n");
                return -USB_ERR_INVAL;
            }
        }
    }

    for (uint8_t index = 0; index < CONFIG_USB_EHCI_QH_NUM; index++) {
        qh = &ehci_qh_pool[bus->hcd.hcd_id][index];
        qh->waitsem = usb_osal_sem_create(0);
    }

    memset(&g_async_qh_head[bus->hcd.hcd_id], 0, sizeof(struct ehci_qh_hw));
    g_async_qh_head[bus->hcd.hcd_id].hw.hlp = QH_HLP_QH(&g_async_qh_head[bus->hcd.hcd_id]);
    g_async_qh_head[bus->hcd.hcd_id].hw.epchar = QH_EPCHAR_H;
    g_async_qh_head[bus->hcd.hcd_id].hw.overlay.next_qtd = QTD_LIST_END;
    g_async_qh_head[bus->hcd.hcd_id].hw.overlay.alt_next_qtd = QTD_LIST_END;
    g_async_qh_head[bus->hcd.hcd_id].hw.overlay.token = QTD_TOKEN_STATUS_HALTED;
    g_async_qh_head[bus->hcd.hcd_id].first_qtd = QTD_LIST_END;

    memset(g_framelist[bus->hcd.hcd_id], 0, sizeof(uint32_t) * CONFIG_USB_EHCI_FRAME_LIST_SIZE);

    memset(&g_periodic_qh_head[bus->hcd.hcd_id], 0, sizeof(struct ehci_qh_hw));
    g_periodic_qh_head[bus->hcd.hcd_id].hw.hlp = QH_HLP_END;
    g_periodic_qh_head[bus->hcd.hcd_id].hw.epchar = QH_EPCAPS_SSMASK(1);
    g_periodic_qh_head[bus->hcd.hcd_id].hw.overlay.next_qtd = QTD_LIST_END;
    g_periodic_qh_head[bus->hcd.hcd_id].hw.overlay.alt_next_qtd = QTD_LIST_END;
    g_periodic_qh_head[bus->hcd.hcd_id].hw.overlay.token = QTD_TOKEN_STATUS_HALTED;
    g_periodic_qh_head[bus->hcd.hcd_id].first_qtd = QTD_LIST_END;

    for (uint32_t i = 0; i < CONFIG_USB_EHCI_FRAME_LIST_SIZE; i++) {
        g_framelist[bus->hcd.hcd_id][i] = QH_HLP_QH(&g_periodic_qh_head[bus->hcd.hcd_id]);
    }

    usb_hc_low_level_init(bus);

    USB_LOG_INFO("EHCI HCIVERSION:0x%04x\r\n", (unsigned int)EHCI_HCCR->hciversion);
    USB_LOG_INFO("EHCI HCSPARAMS:0x%06x\r\n", (unsigned int)EHCI_HCCR->hcsparams);
    USB_LOG_INFO("EHCI HCCPARAMS:0x%04x\r\n", (unsigned int)EHCI_HCCR->hccparams);

    g_ehci_hcd[bus->hcd.hcd_id].ppc = (EHCI_HCCR->hcsparams & EHCI_HCSPARAMS_PPC) ? true : false;
    g_ehci_hcd[bus->hcd.hcd_id].n_ports = (EHCI_HCCR->hcsparams & EHCI_HCSPARAMS_NPORTS_MASK) >> EHCI_HCSPARAMS_NPORTS_SHIFT;
    g_ehci_hcd[bus->hcd.hcd_id].n_cc = (EHCI_HCCR->hcsparams & EHCI_HCSPARAMS_NCC_MASK) >> EHCI_HCSPARAMS_NCC_SHIFT;
    g_ehci_hcd[bus->hcd.hcd_id].n_pcc = (EHCI_HCCR->hcsparams & EHCI_HCSPARAMS_NPCC_MASK) >> EHCI_HCSPARAMS_NPCC_SHIFT;
    g_ehci_hcd[bus->hcd.hcd_id].has_tt = g_ehci_hcd[bus->hcd.hcd_id].n_cc ? false : true;
    g_ehci_hcd[bus->hcd.hcd_id].hcor_offset = EHCI_HCCR->caplength;

    USB_LOG_INFO("EHCI ppc:%u, n_ports:%u, n_cc:%u, n_pcc:%u\r\n",
                 g_ehci_hcd[bus->hcd.hcd_id].ppc,
                 g_ehci_hcd[bus->hcd.hcd_id].n_ports,
                 g_ehci_hcd[bus->hcd.hcd_id].n_cc,
                 g_ehci_hcd[bus->hcd.hcd_id].n_pcc);

    EHCI_HCOR->usbcmd &= ~EHCI_USBCMD_RUN;
    usb_osal_msleep(2);
    EHCI_HCOR->usbcmd |= EHCI_USBCMD_HCRESET;
    while (EHCI_HCOR->usbcmd & EHCI_USBCMD_HCRESET) {
        usb_osal_msleep(1);
        timeout++;
        if (timeout > 100) {
            return -USB_ERR_TIMEOUT;
        }
    }

    usb_hc_low_level2_init(bus);

    EHCI_HCOR->usbintr = 0;
    EHCI_HCOR->usbsts = EHCI_HCOR->usbsts;

    /* Set the Current Asynchronous List Address. */
    EHCI_HCOR->asynclistaddr = EHCI_PTR2ADDR(&g_async_qh_head[bus->hcd.hcd_id]);
    /* Set the Periodic Frame List Base Address. */
    EHCI_HCOR->periodiclistbase = EHCI_PTR2ADDR(g_framelist[bus->hcd.hcd_id]);

    regval = 0;
#if CONFIG_USB_EHCI_FRAME_LIST_SIZE == 1024
    regval |= EHCI_USBCMD_FLSIZE_1024;
#elif CONFIG_USB_EHCI_FRAME_LIST_SIZE == 512
    regval |= EHCI_USBCMD_FLSIZE_512;
#elif CONFIG_USB_EHCI_FRAME_LIST_SIZE == 256
    regval |= EHCI_USBCMD_FLSIZE_256;
#else
#error Unsupported frame size list size
#endif

    regval |= EHCI_USBCMD_ITHRE_1MF;
    regval |= EHCI_USBCMD_ASEN;
    regval |= EHCI_USBCMD_PSEN;
    regval |= EHCI_USBCMD_RUN;
    EHCI_HCOR->usbcmd = regval;

#ifdef CONFIG_USB_EHCI_CONFIGFLAG
    EHCI_HCOR->configflag = EHCI_CONFIGFLAG;
#endif
    /* Wait for the EHCI to run (no longer report halted) */
    timeout = 0;
    while (EHCI_HCOR->usbsts & EHCI_USBSTS_HALTED) {
        usb_osal_msleep(1);
        timeout++;
        if (timeout > 100) {
            return -USB_ERR_TIMEOUT;
        }
    }

    if (g_ehci_hcd[bus->hcd.hcd_id].ppc) {
        for (uint8_t port = 0; port < g_ehci_hcd[bus->hcd.hcd_id].n_ports; port++) {
            regval = EHCI_HCOR->portsc[port];
            regval |= EHCI_PORTSC_PP;
            regval &= ~(EHCI_PORTSC_CSC | EHCI_PORTSC_PEC | EHCI_PORTSC_OCC);
            EHCI_HCOR->portsc[port] = regval;
        }
    }

    if (g_ehci_hcd[bus->hcd.hcd_id].has_tt) {
#ifdef CONFIG_USB_EHCI_WITH_OHCI
        USB_LOG_INFO("EHCI uses tt for ls/fs device, so cannot enable this macro\r\n");
        return -USB_ERR_INVAL;
#endif
    }

    if (g_ehci_hcd[bus->hcd.hcd_id].has_tt) {
        USB_LOG_INFO("EHCI uses tt for ls/fs device\r\n");
    } else {
#ifdef CONFIG_USB_EHCI_WITH_OHCI
        USB_LOG_INFO("EHCI uses companion controller for ls/fs device\r\n");
        ohci_init(bus);
#else
        USB_LOG_WRN("Do not enable companion controller, you should use a hub to support ls/fs device\r\n");
#endif
    }

    /* Enable EHCI interrupts. */
    EHCI_HCOR->usbintr = EHCI_USBIE_INT | EHCI_USBIE_ERR | EHCI_USBIE_PCD | EHCI_USBIE_FATAL | EHCI_USBIE_IAA;
    return 0;
}

int usb_hc_deinit(struct usbh_bus *bus)
{
    struct ehci_qh_hw *qh;

    volatile uint32_t timeout = 0;
    uint32_t regval;

    EHCI_HCOR->usbintr = 0;

    regval = EHCI_HCOR->usbcmd;
    regval &= ~EHCI_USBCMD_ASEN;
    regval &= ~EHCI_USBCMD_PSEN;
    regval &= ~EHCI_USBCMD_RUN;
    EHCI_HCOR->usbcmd = regval;

    while ((EHCI_HCOR->usbsts & (EHCI_USBSTS_PSS | EHCI_USBSTS_ASS)) || ((EHCI_HCOR->usbsts & EHCI_USBSTS_HALTED) == 0)) {
        usb_osal_msleep(1);
        timeout++;
        if (timeout > 100) {
            return -USB_ERR_TIMEOUT;
        }
    }

    if (g_ehci_hcd[bus->hcd.hcd_id].ppc) {
        for (uint8_t port = 0; port < g_ehci_hcd[bus->hcd.hcd_id].n_ports; port++) {
            regval = EHCI_HCOR->portsc[port];
            regval &= ~EHCI_PORTSC_PP;
            EHCI_HCOR->portsc[port] = regval;
        }
    }

#ifdef CONFIG_USB_EHCI_CONFIGFLAG
    EHCI_HCOR->configflag = 0;
#endif

    EHCI_HCOR->usbsts = EHCI_HCOR->usbsts;
    EHCI_HCOR->usbcmd |= EHCI_USBCMD_HCRESET;

    for (uint8_t index = 0; index < CONFIG_USB_EHCI_QH_NUM; index++) {
        qh = &ehci_qh_pool[bus->hcd.hcd_id][index];
        usb_osal_sem_delete(qh->waitsem);
    }

#ifdef CONFIG_USB_EHCI_WITH_OHCI
    ohci_deinit(bus);
#endif

    usb_hc_low_level_deinit(bus);
    return 0;
}

uint16_t usbh_get_frame_number(struct usbh_bus *bus)
{
#ifdef CONFIG_USB_EHCI_WITH_OHCI
    if (EHCI_HCOR->portsc[0] & EHCI_PORTSC_OWNER) {
        return ohci_get_frame_number(bus);
    }
#endif

    return (((EHCI_HCOR->frindex & EHCI_FRINDEX_MASK) >> 3) & 0x3ff);
}

int usbh_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf)
{
    uint8_t nports;
    uint8_t port;
    uint32_t temp, status;

    nports = g_ehci_hcd[bus->hcd.hcd_id].n_ports;

    port = setup->wIndex;

    temp = EHCI_HCOR->portsc[port - 1];

#ifdef CONFIG_USB_EHCI_WITH_OHCI
    if (temp & EHCI_PORTSC_OWNER) {
        return ohci_roothub_control(bus, setup, buf);
    }

    if ((temp & EHCI_PORTSC_LSTATUS_MASK) == EHCI_PORTSC_LSTATUS_KSTATE) {
        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_OWNER;

        while (!(EHCI_HCOR->portsc[port - 1] & EHCI_PORTSC_OWNER)) {
        }
        return ohci_roothub_control(bus, setup, buf);
    }
#endif
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
                        EHCI_HCOR->portsc[port - 1] &= ~EHCI_PORTSC_PE;
                        break;
                    case HUB_PORT_FEATURE_SUSPEND:
                        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_RESUME;
                        usb_osal_msleep(20);
                        EHCI_HCOR->portsc[port - 1] &= ~EHCI_PORTSC_RESUME;
                        while (EHCI_HCOR->portsc[port - 1] & EHCI_PORTSC_RESUME) {
                        }

                        temp = EHCI_HCOR->usbcmd;
                        temp |= EHCI_USBCMD_ASEN;
                        temp |= EHCI_USBCMD_PSEN;
                        temp |= EHCI_USBCMD_RUN;
                        EHCI_HCOR->usbcmd = temp;

                        while ((EHCI_HCOR->usbcmd & EHCI_USBCMD_RUN) == 0) {
                        }

                    case HUB_PORT_FEATURE_C_SUSPEND:
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        EHCI_HCOR->portsc[port - 1] &= ~EHCI_PORTSC_PP;
                        break;
                    case HUB_PORT_FEATURE_C_CONNECTION:
                        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_CSC;
                        break;
                    case HUB_PORT_FEATURE_C_ENABLE:
                        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_PEC;
                        break;
                    case HUB_PORT_FEATURE_C_OVER_CURREN:
                        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_OCC;
                        break;
                    case HUB_PORT_FEATURE_C_RESET:
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
                        temp = EHCI_HCOR->usbcmd;
                        temp &= ~EHCI_USBCMD_ASEN;
                        temp &= ~EHCI_USBCMD_PSEN;
                        temp &= ~EHCI_USBCMD_RUN;
                        EHCI_HCOR->usbcmd = temp;

                        while (EHCI_HCOR->usbcmd & EHCI_USBCMD_RUN) {
                        }

                        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_SUSPEND;
                        while ((EHCI_HCOR->portsc[port - 1] & EHCI_PORTSC_SUSPEND) == 0) {
                        }
                        break;
                    case HUB_PORT_FEATURE_POWER:
                        EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_PP;
                        break;
                    case HUB_PORT_FEATURE_RESET:
                        usbh_reset_port(bus, port);
#ifdef CONFIG_USB_EHCI_WITH_OHCI
                        if (!(EHCI_HCOR->portsc[port - 1] & EHCI_PORTSC_PE)) {
                            EHCI_HCOR->portsc[port - 1] |= EHCI_PORTSC_OWNER;

                            while (!(EHCI_HCOR->portsc[port - 1] & EHCI_PORTSC_OWNER)) {
                            }
                            return ohci_roothub_control(bus, setup, buf);
                        }
#endif
                        break;

                    default:
                        return -USB_ERR_NOTSUPP;
                }
                break;
            case HUB_REQUEST_GET_STATUS:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }
                temp = EHCI_HCOR->portsc[port - 1];

                status = 0;
                if (temp & EHCI_PORTSC_CSC) {
                    status |= (1 << HUB_PORT_FEATURE_C_CONNECTION);
                }
                if (temp & EHCI_PORTSC_PEC) {
                    status |= (1 << HUB_PORT_FEATURE_C_ENABLE);
                }
                if (temp & EHCI_PORTSC_OCC) {
                    status |= (1 << HUB_PORT_FEATURE_C_OVER_CURREN);
                }

                if (temp & EHCI_PORTSC_CCS) {
                    status |= (1 << HUB_PORT_FEATURE_CONNECTION);
                }
                if (temp & EHCI_PORTSC_PE) {
                    status |= (1 << HUB_PORT_FEATURE_ENABLE);

                    if (usbh_get_port_speed(bus, port) == USB_SPEED_LOW) {
                        status |= (1 << HUB_PORT_FEATURE_LOWSPEED);
                    } else if (usbh_get_port_speed(bus, port) == USB_SPEED_HIGH) {
                        status |= (1 << HUB_PORT_FEATURE_HIGHSPEED);
                    }
                }
                if (temp & EHCI_PORTSC_SUSPEND) {
                    status |= (1 << HUB_PORT_FEATURE_SUSPEND);
                }
                if (temp & EHCI_PORTSC_OCA) {
                    status |= (1 << HUB_PORT_FEATURE_OVERCURRENT);
                }
                if (temp & EHCI_PORTSC_RESET) {
                    status |= (1 << HUB_PORT_FEATURE_RESET);
                }
                if (temp & EHCI_PORTSC_PP || !(EHCI_HCCR->hcsparams & EHCI_HCSPARAMS_PPC)) {
                    status |= (1 << HUB_PORT_FEATURE_POWER);
                }
                memcpy(buf, &status, 4);
                break;
            default:
                break;
        }
    }
    return 0;
}

int usbh_submit_urb(struct usbh_urb *urb)
{
    struct ehci_qh_hw *qh = NULL;
    size_t flags;
    int ret = 0;
    struct usbh_hub *hub;
    struct usbh_hubport *hport;
    struct usbh_bus *bus;

    if (!urb || !urb->hport || !urb->ep || !urb->hport->bus) {
        return -USB_ERR_INVAL;
    }

    bus = urb->hport->bus;

    /* find active hubport in roothub */
    hport = urb->hport;
    hub = urb->hport->parent;
    while (!hub->is_roothub) {
        hport = hub->parent;
        hub = hub->parent->parent;
    }

#ifdef CONFIG_USB_EHCI_WITH_OHCI
    if (EHCI_HCOR->portsc[hport->port - 1] & EHCI_PORTSC_OWNER) {
        return ohci_submit_urb(urb);
    }
#endif

    if (!urb->hport->connected || !(EHCI_HCOR->portsc[hport->port - 1] & EHCI_PORTSC_CCS)) {
        return -USB_ERR_NOTCONN;
    }

    if (urb->errorcode == -USB_ERR_BUSY) {
        return -USB_ERR_BUSY;
    }

    flags = usb_osal_enter_critical_section();

    urb->hcpriv = NULL;
    urb->errorcode = -USB_ERR_BUSY;
    urb->actual_length = 0;

    usb_osal_leave_critical_section(flags);

    switch (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes)) {
        case USB_ENDPOINT_TYPE_CONTROL:
            qh = ehci_control_urb_init(bus, urb, urb->setup, urb->transfer_buffer, urb->transfer_buffer_length);
            if (qh == NULL) {
                return -USB_ERR_NOMEM;
            }
            break;
        case USB_ENDPOINT_TYPE_BULK:
            qh = ehci_bulk_urb_init(bus, urb, urb->transfer_buffer, urb->transfer_buffer_length);
            if (qh == NULL) {
                return -USB_ERR_NOMEM;
            }
            break;
        case USB_ENDPOINT_TYPE_INTERRUPT:
            qh = ehci_intr_urb_init(bus, urb, urb->transfer_buffer, urb->transfer_buffer_length);
            if (qh == NULL) {
                return -USB_ERR_NOMEM;
            }
            break;
        case USB_ENDPOINT_TYPE_ISOCHRONOUS:
#ifdef CONFIG_USB_EHCI_ISO
            ret = ehci_iso_urb_init(bus, urb);
#endif
            break;
        default:
            break;
    }

    if (urb->timeout > 0) {
        /* wait until timeout or sem give */
        ret = usb_osal_sem_take(qh->waitsem, urb->timeout);
        if (ret < 0) {
            goto errout_timeout;
        }
        urb->timeout = 0;
        ret = urb->errorcode;
        /* we can free qh when waitsem is done */
        ehci_qh_free(bus, qh);
    }
    return ret;
errout_timeout:
    urb->timeout = 0;
    usbh_kill_urb(urb);
    return ret;
}

int usbh_kill_urb(struct usbh_urb *urb)
{
    struct ehci_qh_hw *qh;
    struct usbh_bus *bus;
    size_t flags;
    bool remove_in_iaad = false;

    if (!urb || !urb->hport || !urb->hcpriv || !urb->hport->bus) {
        return -USB_ERR_INVAL;
    }

    bus = urb->hport->bus;

#ifdef CONFIG_USB_EHCI_WITH_OHCI
    if (EHCI_HCOR->portsc[urb->hport->port - 1] & EHCI_PORTSC_OWNER) {
        return ohci_kill_urb(urb);
    }
#endif

    flags = usb_osal_enter_critical_section();

    EHCI_HCOR->usbcmd &= ~(EHCI_USBCMD_PSEN | EHCI_USBCMD_ASEN);

    if ((USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) == USB_ENDPOINT_TYPE_CONTROL) || (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) == USB_ENDPOINT_TYPE_BULK)) {
        qh = EHCI_ADDR2QH(g_async_qh_head[bus->hcd.hcd_id].hw.hlp);
        while ((qh != &g_async_qh_head[bus->hcd.hcd_id]) && qh) {
            if (qh->urb == urb) {
                remove_in_iaad = true;
                ehci_kill_qh(bus, &g_async_qh_head[bus->hcd.hcd_id], qh);
            }
            qh = EHCI_ADDR2QH(qh->hw.hlp);
        }
    } else if (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) == USB_ENDPOINT_TYPE_INTERRUPT) {
        qh = EHCI_ADDR2QH(g_periodic_qh_head[bus->hcd.hcd_id].hw.hlp);
        while (qh) {
            if (qh->urb == urb) {
                ehci_kill_qh(bus, &g_periodic_qh_head[bus->hcd.hcd_id], qh);
            }
            qh = EHCI_ADDR2QH(qh->hw.hlp);
        }
    } else {
#ifdef CONFIG_USB_EHCI_ISO
        ehci_kill_iso_urb(bus, urb);
        EHCI_HCOR->usbcmd |= (EHCI_USBCMD_PSEN | EHCI_USBCMD_ASEN);
        usb_osal_leave_critical_section(flags);
        return 0;
#endif
    }

    EHCI_HCOR->usbcmd |= (EHCI_USBCMD_PSEN | EHCI_USBCMD_ASEN);

    qh = (struct ehci_qh_hw *)urb->hcpriv;
    urb->hcpriv = NULL;
    urb->errorcode = -USB_ERR_SHUTDOWN;
    qh->urb = NULL;

    if (urb->timeout) {
        usb_osal_sem_give(qh->waitsem);
    } else {
        ehci_qh_free(bus, qh);
    }

    if (remove_in_iaad) {
        volatile uint32_t timeout = 0;
        EHCI_HCOR->usbcmd |= EHCI_USBCMD_IAAD;
        while (!(EHCI_HCOR->usbsts & EHCI_USBSTS_IAA)) {
            usb_osal_msleep(1);
            timeout++;
            if (timeout > 100) {
                usb_osal_leave_critical_section(flags);
                return -USB_ERR_TIMEOUT;
            }
        }
        EHCI_HCOR->usbsts = EHCI_USBSTS_IAA;
    }

    usb_osal_leave_critical_section(flags);

    return 0;
}

static void ehci_scan_async_list(struct usbh_bus *bus)
{
    struct ehci_qh_hw *qh;

    qh = EHCI_ADDR2QH(g_async_qh_head[bus->hcd.hcd_id].hw.hlp);
    while ((qh != &g_async_qh_head[bus->hcd.hcd_id]) && qh) {
        if (qh->urb) {
            ehci_check_qh(bus, &g_async_qh_head[bus->hcd.hcd_id], qh);
        }
        qh = EHCI_ADDR2QH(qh->hw.hlp);
    }
}

static void ehci_scan_periodic_list(struct usbh_bus *bus)
{
    struct ehci_qh_hw *qh;

    qh = EHCI_ADDR2QH(g_periodic_qh_head[bus->hcd.hcd_id].hw.hlp);
    while (qh) {
        if (qh->urb) {
            ehci_check_qh(bus, &g_periodic_qh_head[bus->hcd.hcd_id], qh);
        }
        qh = EHCI_ADDR2QH(qh->hw.hlp);
    }
}

void USBH_IRQHandler(uint8_t busid)
{
    uint32_t usbsts;
    struct usbh_bus *bus;

    bus = &g_usbhost_bus[busid];

    usbsts = EHCI_HCOR->usbsts & EHCI_HCOR->usbintr;
    EHCI_HCOR->usbsts = usbsts;

    if (usbsts & EHCI_USBSTS_INT) {
        ehci_scan_async_list(bus);
        ehci_scan_periodic_list(bus);
#ifdef CONFIG_USB_EHCI_ISO
        ehci_scan_isochronous_list(bus);
#endif
    }

    if (usbsts & EHCI_USBSTS_ERR) {
        ehci_scan_async_list(bus);
        ehci_scan_periodic_list(bus);
#ifdef CONFIG_USB_EHCI_ISO
        ehci_scan_isochronous_list(bus);
#endif
    }

    if (usbsts & EHCI_USBSTS_PCD) {
        for (int port = 0; port < g_ehci_hcd[bus->hcd.hcd_id].n_ports; port++) {
            uint32_t portsc = EHCI_HCOR->portsc[port];

            if (portsc & EHCI_PORTSC_CSC) {
                if ((portsc & EHCI_PORTSC_CCS) == EHCI_PORTSC_CCS) {
                } else {
#if defined(CONFIG_USB_EHCI_NXP)
                    /* kUSB_ControllerEhci0 and kUSB_ControllerEhci1*/
                    extern void USB_EhcihostPhyDisconnectDetectCmd(uint8_t controllerId, uint8_t enable);
                    USB_EhcihostPhyDisconnectDetectCmd(2 + busid, 0);
#endif
                    for (uint8_t index = 0; index < CONFIG_USB_EHCI_QH_NUM; index++) {
                        g_ehci_hcd[bus->hcd.hcd_id].ehci_qh_used[index] = false;
                    }
                    for (uint8_t index = 0; index < CONFIG_USB_EHCI_ISO_NUM; index++) {
                        g_ehci_hcd[bus->hcd.hcd_id].ehci_iso_used[index] = false;
                    }
                }

                bus->hcd.roothub.int_buffer[0] |= (1 << (port + 1));
                usbh_hub_thread_wakeup(&bus->hcd.roothub);
            }
        }
    }

    if (usbsts & EHCI_USBSTS_IAA) {
        for (uint8_t index = 0; index < CONFIG_USB_EHCI_QH_NUM; index++) {
            struct ehci_qh_hw *qh = &ehci_qh_pool[bus->hcd.hcd_id][index];
            if (g_ehci_hcd[bus->hcd.hcd_id].ehci_qh_used[index] && qh->remove_in_iaad) {
                ehci_urb_waitup(bus, qh->urb);
            }
        }
    }

    if (usbsts & EHCI_USBSTS_FATAL) {
    }
}
