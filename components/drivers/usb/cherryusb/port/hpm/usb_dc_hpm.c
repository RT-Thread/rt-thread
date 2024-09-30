/*
 * Copyright (c) 2022-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "usbd_core.h"
#include "hpm_usb_device.h"

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS CONFIG_USBDEV_EP_NUM
#endif

/* USBSTS, USBINTR */
enum {
    intr_usb = HPM_BITSMASK(1, 0),
    intr_error = HPM_BITSMASK(1, 1),
    intr_port_change = HPM_BITSMASK(1, 2),
    intr_reset = HPM_BITSMASK(1, 6),
    intr_sof = HPM_BITSMASK(1, 7),
    intr_suspend = HPM_BITSMASK(1, 8),
    intr_nak = HPM_BITSMASK(1, 16)
};

/* Endpoint state */
struct hpm_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t ep_enable;  /* Endpoint enable */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

/*---------------------------------------------------------------------*
 * Variable Definitions
 *---------------------------------------------------------------------*/
/* Driver state */
struct hpm_udc {
    usb_device_handle_t *handle;
    bool is_suspend;
    struct hpm_ep_state in_ep[USB_NUM_BIDIR_ENDPOINTS];  /*!< IN endpoint parameters*/
    struct hpm_ep_state out_ep[USB_NUM_BIDIR_ENDPOINTS]; /*!< OUT endpoint parameters */
} g_hpm_udc[CONFIG_USBDEV_MAX_BUS];

static ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(USB_SOC_DCD_DATA_RAM_ADDRESS_ALIGNMENT) dcd_data_t _dcd_data0;
#ifdef HPM_USB1_BASE
static ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(USB_SOC_DCD_DATA_RAM_ADDRESS_ALIGNMENT) dcd_data_t _dcd_data1;
#endif
static ATTR_PLACE_AT_NONCACHEABLE usb_device_handle_t usb_device_handle[CONFIG_USBDEV_MAX_BUS];
static uint32_t _dcd_irqnum[CONFIG_USBDEV_MAX_BUS];
static uint8_t _dcd_busid[CONFIG_USBDEV_MAX_BUS];

/* Index to bit position in register */
static inline uint8_t ep_idx2bit(uint8_t ep_idx)
{
    return ep_idx / 2 + ((ep_idx % 2) ? 16 : 0);
}

void usbd_execute_test_mode(uint8_t busid, uint8_t test_mode)
{
    usb_set_port_test_mode(g_hpm_udc[busid].handle->regs, test_mode);
}

int usb_dc_init(uint8_t busid)
{
    memset(&g_hpm_udc[busid], 0, sizeof(struct hpm_udc));
    g_hpm_udc[busid].handle = &usb_device_handle[busid];
    g_hpm_udc[busid].handle->regs = (USB_Type *)g_usbdev_bus[busid].reg_base;

    if (g_usbdev_bus[busid].reg_base == HPM_USB0_BASE) {
        _dcd_irqnum[busid] = IRQn_USB0;
        _dcd_busid[0] = busid;
    } else {
#ifdef HPM_USB1_BASE
        if (g_usbdev_bus[busid].reg_base == HPM_USB1_BASE) {
            _dcd_irqnum[busid] = IRQn_USB1;
            _dcd_busid[1] = busid;
        }
#endif
    }

    if (busid == 0) {
        g_hpm_udc[busid].handle->dcd_data = &_dcd_data0;
    } else if (busid == 1) {
#ifdef HPM_USB1_BASE
        g_hpm_udc[busid].handle->dcd_data = &_dcd_data1;
#endif
    } else {
        ;
    }

    uint32_t int_mask;
    int_mask = (USB_USBINTR_UE_MASK | USB_USBINTR_UEE_MASK | USB_USBINTR_SLE_MASK |
                USB_USBINTR_PCE_MASK | USB_USBINTR_URE_MASK);

    usb_device_init(g_hpm_udc[busid].handle, int_mask);

    intc_m_enable_irq(_dcd_irqnum[busid]);
    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    intc_m_disable_irq(_dcd_irqnum[busid]);

    usb_device_deinit(g_hpm_udc[busid].handle);

    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;
    usb_dcd_set_address(handle->regs, addr);
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    USB_Type *ptr;

    ptr = g_hpm_udc[busid].handle->regs;

    if (!usb_get_suspend_status(ptr)) {
        return -1;
    }

    usb_force_port_resume(ptr);
    while (ptr->PORTSC1 & USB_PORTSC1_FPR_MASK) {
    }

    return 0;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    uint8_t speed;

    speed = usb_get_port_speed(g_hpm_udc[busid].handle->regs);

    if (speed == 0x00) {
        return USB_SPEED_FULL;
    }
    if (speed == 0x01) {
        return USB_SPEED_LOW;
    }
    if (speed == 0x02) {
        return USB_SPEED_HIGH;
    }

    return 0;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    usb_endpoint_config_t tmp_ep_cfg;
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);

    tmp_ep_cfg.xfer = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
    tmp_ep_cfg.ep_addr = ep->bEndpointAddress;
    tmp_ep_cfg.max_packet_size = ep->wMaxPacketSize;

    usb_device_edpt_open(handle, &tmp_ep_cfg);

    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_hpm_udc[busid].out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_hpm_udc[busid].out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_hpm_udc[busid].out_ep[ep_idx].ep_enable = true;
    } else {
        g_hpm_udc[busid].in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_hpm_udc[busid].in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_hpm_udc[busid].in_ep[ep_idx].ep_enable = true;
    }

    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        g_hpm_udc[busid].out_ep[ep_idx].ep_enable = false;
    } else {
        g_hpm_udc[busid].in_ep[ep_idx].ep_enable = false;
    }

    usb_device_edpt_close(handle, ep);

    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;

    usb_device_edpt_stall(handle, ep);
    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;

    usb_device_edpt_clear_stall(handle, ep);
    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;

    *stalled = usb_device_edpt_check_stall(handle, ep);
    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;

    if (!data && data_len) {
        return -1;
    }
    if (!g_hpm_udc[busid].in_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_hpm_udc[busid].in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_hpm_udc[busid].in_ep[ep_idx].xfer_len = data_len;
    g_hpm_udc[busid].in_ep[ep_idx].actual_xfer_len = 0;

    usb_device_edpt_xfer(handle, ep, (uint8_t *)data, data_len);

    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;

    if (!data && data_len) {
        return -1;
    }
    if (!g_hpm_udc[busid].out_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_hpm_udc[busid].out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_hpm_udc[busid].out_ep[ep_idx].xfer_len = data_len;
    g_hpm_udc[busid].out_ep[ep_idx].actual_xfer_len = 0;

    usb_device_edpt_xfer(handle, ep, data, data_len);

    return 0;
}

void USBD_IRQHandler(uint8_t busid)
{
    uint32_t int_status;
    usb_device_handle_t *handle = g_hpm_udc[busid].handle;
    uint32_t transfer_len;
    bool ep_cb_req;

    /* Acknowledge handled interrupt */
    int_status = usb_device_status_flags(handle);
    int_status &= usb_device_interrupts(handle);
    usb_device_clear_status_flags(handle, int_status);

    if (int_status & intr_error) {
        USB_LOG_ERR("usbd intr error!\r\n");
    }

    if (int_status & intr_reset) {
        g_hpm_udc[busid].is_suspend = false;
        memset(g_hpm_udc[busid].in_ep, 0, sizeof(struct hpm_ep_state) * USB_NUM_BIDIR_ENDPOINTS);
        memset(g_hpm_udc[busid].out_ep, 0, sizeof(struct hpm_ep_state) * USB_NUM_BIDIR_ENDPOINTS);
        usbd_event_reset_handler(busid);
        usb_device_bus_reset(handle, 64);
    }

    if (int_status & intr_suspend) {
        if (usb_device_get_suspend_status(handle)) {
            /* Note: Host may delay more than 3 ms before and/or after bus reset before doing enumeration. */
            if (usb_device_get_address(handle)) {
                g_hpm_udc[busid].is_suspend = true;
                usbd_event_suspend_handler(busid);
            }
        } else {
        }
    }

    if (int_status & intr_port_change) {
        if (!usb_device_get_port_ccs(handle)) {
            usbd_event_disconnect_handler(busid);
        } else {
            if (g_hpm_udc[busid].is_suspend) {
                g_hpm_udc[busid].is_suspend = false;
                usbd_event_resume_handler(busid);
            }
            usbd_event_connect_handler(busid);
        }
    }

    if (int_status & intr_usb) {
        uint32_t const edpt_complete = usb_device_get_edpt_complete_status(handle);
        usb_device_clear_edpt_complete_status(handle, edpt_complete);
        uint32_t edpt_setup_status = usb_device_get_setup_status(handle);

        if (edpt_setup_status) {
            /*------------- Set up Received -------------*/
            usb_device_clear_setup_status(handle, edpt_setup_status);
            dcd_qhd_t *qhd0 = usb_device_qhd_get(handle, 0);
            usbd_event_ep0_setup_complete_handler(busid, (uint8_t *)&qhd0->setup_request);
        }

        if (edpt_complete) {
            for (uint8_t ep_idx = 0; ep_idx < USB_SOS_DCD_MAX_QHD_COUNT; ep_idx++) {
                if (edpt_complete & (1 << ep_idx2bit(ep_idx))) {
                    transfer_len = 0;
                    ep_cb_req = true;

                    /* Failed QTD also get ENDPTCOMPLETE set */
                    dcd_qtd_t *p_qtd = usb_device_qtd_get(handle, ep_idx);
                    while (1) {
                        if (p_qtd->halted || p_qtd->xact_err || p_qtd->buffer_err) {
                            USB_LOG_ERR("usbd transfer error!\r\n");
                            ep_cb_req = false;
                            break;
                        } else if (p_qtd->active) {
                            ep_cb_req = false;
                            break;
                        } else {
                            transfer_len += p_qtd->expected_bytes - p_qtd->total_bytes;
                        }

                        if (p_qtd->next == USB_SOC_DCD_QTD_NEXT_INVALID) {
                            break;
                        } else {
                            p_qtd = (dcd_qtd_t *)p_qtd->next;
                        }
                    }

                    if (ep_cb_req) {
                        uint8_t const ep_addr = (ep_idx / 2) | ((ep_idx & 0x01) ? 0x80 : 0);
                        if (ep_addr & 0x80) {
                            usbd_event_ep_in_complete_handler(busid, ep_addr, transfer_len);
                        } else {
                            usbd_event_ep_out_complete_handler(busid, ep_addr, transfer_len);
                        }
                    }
                }
            }
        }
    }
}

#if !defined(USBD_USE_CUSTOM_ISR) || !USBD_USE_CUSTOM_ISR

void isr_usbd0(void)
{
    USBD_IRQHandler(_dcd_busid[0]);
}
SDK_DECLARE_EXT_ISR_M(IRQn_USB0, isr_usbd0)

#ifdef HPM_USB1_BASE
void isr_usbd1(void)
{
    USBD_IRQHandler(_dcd_busid[1]);
}
SDK_DECLARE_EXT_ISR_M(IRQn_USB1, isr_usbd1)
#endif

#endif
