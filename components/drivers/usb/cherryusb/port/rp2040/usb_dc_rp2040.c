/*
 * Copyright (c) 2022, HaiMianBBao
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "hardware/resets.h"
#include "hardware/irq.h"
#include "hardware/structs/usb.h"
#if CHERRYUSB_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX
#include "pico/fix/rp2040_usb_device_enumeration.h"
#endif

#define usb_hw_set   hw_set_alias(usb_hw)
#define usb_hw_clear hw_clear_alias(usb_hw)

#ifndef CONFIG_USBDEV_EP_NUM
#define CONFIG_USBDEV_EP_NUM 16
#endif

#ifndef FORCE_VBUS_DETECT
#define FORCE_VBUS_DETECT 1
#endif

/* Endpoint state */
struct rp2040_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t ep_enable;  /* Endpoint enable */
    uint8_t ep_addr;    /* Endpoint address */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;

    volatile uint32_t *endpoint_control; /*!< Endpoint control register */
    volatile uint32_t *buffer_control;   /*!< Buffer control register */
    uint8_t *data_buffer;                /*!< Buffer pointer in usb dpram */
    uint8_t next_pid;                    /*!< Toggle after each packet (unless replying to a SETUP) */
};

/* Driver state */
struct rp2040_udc {
    volatile uint8_t dev_addr;
    struct rp2040_ep_state in_ep[CONFIG_USBDEV_EP_NUM];  /*!< IN endpoint parameters*/
    struct rp2040_ep_state out_ep[CONFIG_USBDEV_EP_NUM]; /*!< OUT endpoint parameters */
    struct usb_setup_packet setup;                       /*!< Setup package that may be used in interrupt processing (outside the protocol stack) */
} g_rp2040_udc;

void rp2040_usbd_irq(void);

/**
 * @brief Take a buffer pointer located in the USB RAM and return as an offset of the RAM.
 *
 * @param buf
 * @return uint32_t
 */
static inline uint32_t usb_buffer_offset(volatile uint8_t *buf)
{
    return (uint32_t)buf ^ (uint32_t)usb_dpram;
}

/**
 * @brief Set up the endpoint control register for an endpoint (if applicable. Not valid for EP0).
 *
 * @param ep
 */
void usb_setup_endpoint(const struct rp2040_ep_state *ep)
{
    // EP0 doesn't have one so return if that is the case
    if (!ep->endpoint_control) {
        return;
    }

    // Get the data buffer as an offset of the USB controller's DPRAM
    uint32_t dpram_offset = usb_buffer_offset(ep->data_buffer);
    uint32_t reg = EP_CTRL_ENABLE_BITS |
                   EP_CTRL_INTERRUPT_PER_BUFFER |
                   (ep->ep_type << EP_CTRL_BUFFER_TYPE_LSB) |
                   dpram_offset;
    *ep->endpoint_control = reg;
}

/**
 * @brief Starts a transfer on a given endpoint.
 *
 * @param ep, the endpoint configuration.
 * @param buf, the data buffer to send. Only applicable if the endpoint is TX
 * @param len, the length of the data in buf (this example limits max len to one packet - 64 bytes)
 */
static void usb_start_transfer(struct rp2040_ep_state *ep, uint8_t *buf, uint16_t len)
{
    /*!< Prepare buffer control register value */
    uint32_t val = len | USB_BUF_CTRL_AVAIL;

    if (len < ep->ep_mps) {
        val |= USB_BUF_CTRL_LAST;
    }

    if (USB_EP_DIR_IS_IN(ep->ep_addr)) {
        /*!< Need to copy the data from the user buffer to the usb memory */
        if (buf != NULL) {
            memcpy((void *)ep->data_buffer, (void *)buf, len);
        }
        /*!< Mark as full */
        val |= USB_BUF_CTRL_FULL;
    }

    /*!< Set pid and flip for next transfer */
    val |= ep->next_pid ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;
    ep->next_pid ^= 1u;

    *ep->buffer_control = val;
}

int usb_dc_init(uint8_t busid)
{
    uint8_t *next_buffer_ptr;

    memset(&g_rp2040_udc, 0, sizeof(struct rp2040_udc));

    g_rp2040_udc.in_ep[0].endpoint_control = NULL;
    g_rp2040_udc.in_ep[0].data_buffer = &usb_dpram->ep0_buf_a[0];
    g_rp2040_udc.out_ep[0].endpoint_control = NULL;
    g_rp2040_udc.out_ep[0].data_buffer = &usb_dpram->ep0_buf_a[0];

    for (uint32_t i = 0; i < CONFIG_USBDEV_EP_NUM; i++) {
        g_rp2040_udc.in_ep[i].buffer_control = &usb_dpram->ep_buf_ctrl[i].in;
        g_rp2040_udc.out_ep[i].buffer_control = &usb_dpram->ep_buf_ctrl[i].out;

        if (i != 0) {
            g_rp2040_udc.in_ep[i].endpoint_control = &usb_dpram->ep_ctrl[i - 1].in;
            g_rp2040_udc.out_ep[i].endpoint_control = &usb_dpram->ep_ctrl[i - 1].out;
        }
    }

    next_buffer_ptr = &usb_dpram->epx_data[0];

    for (uint32_t i = 1; i < CONFIG_USBDEV_EP_NUM; i++) {
        g_rp2040_udc.in_ep[i].data_buffer = next_buffer_ptr;
        if (i == 1) {
            next_buffer_ptr += 1024; /* for iso video */
        } else {
            next_buffer_ptr += 64;
        }

        g_rp2040_udc.out_ep[i].data_buffer = next_buffer_ptr;
        next_buffer_ptr += 64;
    }

    // Remove shared irq if it was previously added so as not to fill up shared irq slots
    irq_remove_handler(USBCTRL_IRQ, rp2040_usbd_irq);

    irq_add_shared_handler(USBCTRL_IRQ, rp2040_usbd_irq, PICO_SHARED_IRQ_HANDLER_HIGHEST_ORDER_PRIORITY);

    // Reset usb controller
    reset_unreset_block_num_wait_blocking(RESET_USBCTRL);

    /*!< Clear any previous state just in case */
    memset(usb_hw, 0, sizeof(*usb_hw));
    memset(usb_dpram, 0, sizeof(*usb_dpram));

    /*!< Mux the controller to the onboard usb phy */
    usb_hw->muxing = USB_USB_MUXING_TO_PHY_BITS | USB_USB_MUXING_SOFTCON_BITS;

#if FORCE_VBUS_DETECT
    // Force VBUS detect so the device thinks it is plugged into a host
    usb_hw->pwr = USB_USB_PWR_VBUS_DETECT_BITS | USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_BITS;
#endif

    // Enable the USB controller in device mode.
    usb_hw->main_ctrl = USB_MAIN_CTRL_CONTROLLER_EN_BITS;

    // Enable an interrupt per EP0 transaction
    usb_hw->sie_ctrl = USB_SIE_CTRL_EP0_INT_1BUF_BITS; // <2>

    // Enable interrupts for when a buffer is done, when the bus is reset,
    // and when a setup packet is received
    usb_hw->inte = USB_INTS_BUFF_STATUS_BITS | USB_INTS_BUS_RESET_BITS | USB_INTS_SETUP_REQ_BITS |
                   USB_INTS_DEV_SUSPEND_BITS | USB_INTS_DEV_RESUME_FROM_HOST_BITS |
                   (FORCE_VBUS_DETECT ? 0 : USB_INTS_DEV_CONN_DIS_BITS);

#ifdef CONFIG_USBDEV_SOF_ENABLE
    usb_hw->inte |= USB_INTS_DEV_SOF_BITS;
#endif

    // Enable USB interrupt at processor
    irq_set_enabled(USBCTRL_IRQ, true);

    usb_hw_set->sie_ctrl = USB_SIE_CTRL_PULLUP_EN_BITS;
    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    irq_set_enabled(USBCTRL_IRQ, false);
    // Remove shared irq if it was previously added so as not to fill up shared irq slots
    irq_remove_handler(USBCTRL_IRQ, rp2040_usbd_irq);

    usb_hw_clear->sie_ctrl = USB_SIE_CTRL_PULLUP_EN_BITS;
    memset(&g_rp2040_udc, 0, sizeof(struct rp2040_udc));

    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    g_rp2040_udc.dev_addr = addr;
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    return -1;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    return USB_SPEED_FULL;
}

int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);

    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_rp2040_udc.out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_rp2040_udc.out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_rp2040_udc.out_ep[ep_idx].ep_addr = ep->bEndpointAddress;
        g_rp2040_udc.out_ep[ep_idx].ep_enable = true;
        /*!< Clear control reg */
        *(g_rp2040_udc.out_ep[ep_idx].buffer_control) = 0;

        usb_setup_endpoint(&g_rp2040_udc.out_ep[ep_idx]);
    } else {
        g_rp2040_udc.in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_rp2040_udc.in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_rp2040_udc.in_ep[ep_idx].ep_addr = ep->bEndpointAddress;
        g_rp2040_udc.in_ep[ep_idx].ep_enable = true;
        /*!< Clear control reg */
        *(g_rp2040_udc.in_ep[ep_idx].buffer_control) = 0;

        usb_setup_endpoint(&g_rp2040_udc.in_ep[ep_idx]);
    }
    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    if (USB_EP_DIR_IS_IN(ep)) {
    } else if (USB_EP_DIR_IS_OUT(ep)) {
    }
    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    if (USB_EP_GET_IDX(ep) == 0) {
        /**
         * A stall on EP0 has to be armed so it can be cleared on the next setup packet
         */
        usb_hw_set->ep_stall_arm = (USB_EP_DIR_IS_IN(ep)) ? USB_EP_STALL_ARM_EP0_IN_BITS : USB_EP_STALL_ARM_EP0_OUT_BITS;
    }

    if (USB_EP_DIR_IS_OUT(ep)) {
        *(g_rp2040_udc.out_ep[USB_EP_GET_IDX(ep)].buffer_control) = USB_BUF_CTRL_STALL;
    } else {
        *(g_rp2040_udc.in_ep[USB_EP_GET_IDX(ep)].buffer_control) = USB_BUF_CTRL_STALL;
    }

    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx != 0) {
        if (USB_EP_DIR_IS_OUT(ep)) {
            g_rp2040_udc.out_ep[USB_EP_GET_IDX(ep)].next_pid = 0;
            *(g_rp2040_udc.out_ep[USB_EP_GET_IDX(ep)].buffer_control) = ~USB_BUF_CTRL_STALL;
        } else {
            g_rp2040_udc.in_ep[USB_EP_GET_IDX(ep)].next_pid = 0;
            *(g_rp2040_udc.in_ep[USB_EP_GET_IDX(ep)].buffer_control) = ~USB_BUF_CTRL_STALL;
        }
    }
    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    if (USB_EP_DIR_IS_OUT(ep)) {
        if (*(g_rp2040_udc.out_ep[USB_EP_GET_IDX(ep)].buffer_control) & USB_BUF_CTRL_STALL) {
            *stalled = 1;
        } else {
            *stalled = 0;
        }
    } else {
        if (*(g_rp2040_udc.in_ep[USB_EP_GET_IDX(ep)].buffer_control) & USB_BUF_CTRL_STALL) {
            *stalled = 1;
        } else {
            *stalled = 0;
        }
    }
    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_rp2040_udc.in_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_rp2040_udc.in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_rp2040_udc.in_ep[ep_idx].xfer_len = data_len;
    g_rp2040_udc.in_ep[ep_idx].actual_xfer_len = 0;

    if (data_len == 0) {
        usb_start_transfer(&g_rp2040_udc.in_ep[ep_idx], NULL, 0);
    } else {
        data_len = MIN(data_len, g_rp2040_udc.in_ep[ep_idx].ep_mps);
        usb_start_transfer(&g_rp2040_udc.in_ep[ep_idx], g_rp2040_udc.in_ep[ep_idx].xfer_buf, data_len);
    }

    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_rp2040_udc.out_ep[ep_idx].ep_enable) {
        return -2;
    }
    g_rp2040_udc.out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_rp2040_udc.out_ep[ep_idx].xfer_len = data_len;
    g_rp2040_udc.out_ep[ep_idx].actual_xfer_len = 0;

    if (data_len == 0) {
        usb_start_transfer(&g_rp2040_udc.out_ep[ep_idx], NULL, 0);
    } else {
        /*!< Not zlp */
        data_len = MIN(data_len, g_rp2040_udc.out_ep[ep_idx].ep_mps);
        usb_start_transfer(&g_rp2040_udc.out_ep[ep_idx], g_rp2040_udc.out_ep[ep_idx].xfer_buf, data_len);
    }
    return 0;
}

/**
 * @brief Notify an endpoint that a transfer has completed.
 *
 * @param ep, the endpoint to notify.
 */
static void usb_handle_ep_buff_done(struct rp2040_ep_state *ep)
{
    uint32_t buffer_control = *ep->buffer_control;
    /*!< Get the transfer length for this endpoint */
    uint16_t read_count = buffer_control & USB_BUF_CTRL_LEN_MASK;
    /*!< Call that endpoints buffer done handler */
    if (ep->ep_addr == 0x80) {
        /*!< EP0 In */
        /**
         * Determine the current setup direction
         */
        switch (g_rp2040_udc.setup.bmRequestType >> USB_REQUEST_DIR_SHIFT) {
            case 1:
                /*!< Get */
                if (g_rp2040_udc.in_ep[0].xfer_len > g_rp2040_udc.in_ep[0].ep_mps) {
                    g_rp2040_udc.in_ep[0].xfer_len -= g_rp2040_udc.in_ep[0].ep_mps;
                    g_rp2040_udc.in_ep[0].actual_xfer_len += g_rp2040_udc.in_ep[0].ep_mps;
                    usbd_event_ep_in_complete_handler(0, 0 | 0x80, g_rp2040_udc.in_ep[0].actual_xfer_len);
                } else {
                    g_rp2040_udc.in_ep[0].actual_xfer_len += g_rp2040_udc.in_ep[0].xfer_len;
                    g_rp2040_udc.in_ep[0].xfer_len = 0;
                    /**
                     * EP0 In complete and host will send a out token to get 0 length packet
                     * In the next usbd_event_ep_in_complete_handler, stack will start read 0 length packet
                     * and host must send data1 packet.We resest the ep0 next_pid = 1 in setup interrupt head.
                     */
                    usbd_event_ep_in_complete_handler(0, 0 | 0x80, g_rp2040_udc.in_ep[0].actual_xfer_len);
                }
                break;
            case 0:
                /*!< Set */
                if (g_rp2040_udc.dev_addr > 0) {
                    usb_hw->dev_addr_ctrl = g_rp2040_udc.dev_addr;
                    g_rp2040_udc.dev_addr = 0;
                } else {
                    /*!< Normal status stage // Setup  out...out  in  */
                    /**
                     * Perpar for next setup
                     */
                }
                break;
        }

    } else if (ep->ep_addr == 0x00) {
        /*!< EP0 Out */
        memcpy(g_rp2040_udc.out_ep[0].xfer_buf, g_rp2040_udc.out_ep[0].data_buffer, read_count);
        if (read_count == 0) {
            /*!< Normal status stage // Setup  in...in  out  */
            /**
              * Perpar for next setup
              */
        }

        g_rp2040_udc.out_ep[0].actual_xfer_len += read_count;
        g_rp2040_udc.out_ep[0].xfer_len -= read_count;

        usbd_event_ep_out_complete_handler(0, 0x00, g_rp2040_udc.out_ep[0].actual_xfer_len);
    } else {
        /*!< Others ep */
        uint16_t data_len = 0;
        if (USB_EP_DIR_IS_OUT(ep->ep_addr)) {
            /*!< flip the pid */
            memcpy(g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].xfer_buf, g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].data_buffer, read_count);
            g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].xfer_buf += read_count;
            g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].actual_xfer_len += read_count;
            g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].xfer_len -= read_count;

            if (read_count < g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].ep_mps || g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].xfer_len == 0) {
                /*!< Out complete */
                usbd_event_ep_out_complete_handler(0, ep->ep_addr, g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].actual_xfer_len);
            } else {
                /*!< Need read again */
                data_len = MIN(g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].xfer_len, g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f].ep_mps);
                usb_start_transfer(&g_rp2040_udc.out_ep[(ep->ep_addr) & 0x0f], NULL, data_len);
            }
        } else {
            if (g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_len > g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].ep_mps) {
                /*!< Need tx again */
                g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_len -= g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].ep_mps;
                g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_buf += g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].ep_mps;
                g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].actual_xfer_len += g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].ep_mps;
                data_len = MIN(g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_len, g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].ep_mps);
                usb_start_transfer(&g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f], g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_buf, data_len);
            } else {
                /*!< In complete */
                g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].actual_xfer_len += g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_len;
                g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].xfer_len = 0;
                usbd_event_ep_in_complete_handler(0, ep->ep_addr, g_rp2040_udc.in_ep[(ep->ep_addr) & 0x0f].actual_xfer_len);
            }
        }
    }
}

/**
 * @brief Find the endpoint configuration for a specified endpoint number and
 * direction and notify it that a transfer has completed.
 *
 * @param ep_num
 * @param in
 */
static void usb_handle_buff_done(uint8_t ep_num, bool in)
{
    uint8_t ep_addr = ep_num | (in ? USB_EP_DIR_IN : 0);
    if (USB_EP_DIR_IS_OUT(ep_addr)) {
        usb_handle_ep_buff_done(&g_rp2040_udc.out_ep[ep_num]);
    } else {
        usb_handle_ep_buff_done(&g_rp2040_udc.in_ep[ep_num]);
    }
}

/**
 * @brief Handle a "buffer status" irq. This means that one or more
 * buffers have been sent / received. Notify each endpoint where this
 * is the case.
 */
static void usb_handle_buff_status(void)
{
    uint32_t remaining_buffers = usb_hw->buf_status;

    uint32_t bit = 1u;
    for (uint8_t i = 0; remaining_buffers && i < USB_NUM_ENDPOINTS * 2; i++) {
        if (remaining_buffers & bit) {
            /*!< clear this in advance */
            usb_hw_clear->buf_status = bit;
            /*!< IN transfer for even i, OUT transfer for odd i */
            usb_handle_buff_done(i >> 1u, !(i & 1u));
            remaining_buffers &= ~bit;
        }
        bit <<= 1u;
    }
}

void USBD_IRQHandler(uint8_t busid)
{
    uint32_t const status = usb_hw->ints;
    uint32_t handled = 0;

    if (status & USB_INTS_BUFF_STATUS_BITS) {
        handled |= USB_INTS_BUFF_STATUS_BITS;
        usb_handle_buff_status();
    }

    if (status & USB_INTS_SETUP_REQ_BITS) {
        handled |= USB_INTS_SETUP_REQ_BITS;
        memcpy((uint8_t *)&g_rp2040_udc.setup, (uint8_t const *)&usb_dpram->setup_packet, 8);
        /**
         * reset pid to both 1 (data and ack)
         */
        g_rp2040_udc.in_ep[0].next_pid = 1;
        g_rp2040_udc.out_ep[0].next_pid = 1;
        usbd_event_ep0_setup_complete_handler(0, (uint8_t *)&g_rp2040_udc.setup);
        usb_hw_clear->sie_status = USB_SIE_STATUS_SETUP_REC_BITS;
    }

#if FORCE_VBUS_DETECT == 0
    /**
     * Since we force VBUS detect On, device will always think it is connected and
     * couldn't distinguish between disconnect and suspend
     */
    if (status & USB_INTS_DEV_CONN_DIS_BITS) {
        handled |= USB_INTS_DEV_CONN_DIS_BITS;
        if (usb_hw->sie_status & USB_SIE_STATUS_CONNECTED_BITS) {
            /*!< Connected: nothing to do */
            usbd_event_connect_handler(0);
        } else {
            /*!< Disconnected */
            usbd_event_disconnect_handler(0);
        }
        usb_hw_clear->sie_status = USB_SIE_STATUS_CONNECTED_BITS;
    }
#endif

    /**
     * SE0 for 2.5 us or more (will last at least 10ms)
     */
    if (status & USB_INTS_BUS_RESET_BITS) {
        handled |= USB_INTS_BUS_RESET_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_BUS_RESET_BITS;

        usb_hw->dev_addr_ctrl = 0;

        for (uint8_t i = 0; i < CONFIG_USBDEV_EP_NUM - 1; i++) {
            /*!< Start at ep1 */
            usb_dpram->ep_ctrl[i].in = 0;
            usb_dpram->ep_ctrl[i].out = 0;
        }

        usbd_event_reset_handler(0);

#if CHERRYUSB_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX
        /**
         * Only run enumeration walk-around if pull up is enabled
         */
        if (usb_hw->sie_ctrl & USB_SIE_CTRL_PULLUP_EN_BITS)
            rp2040_usb_device_enumeration_fix();
#endif
    }

    /**
     * Note from pico datasheet 4.1.2.6.4 (v1.2)
     * If you enable the suspend interrupt, it is likely you will see a suspend interrupt when
     * the device is first connected but the bus is idle. The bus can be idle for a few ms before
     * the host begins sending start of frame packets. You will also see a suspend interrupt
     * when the device is disconnected if you do not have a VBUS detect circuit connected. This is
     * because without VBUS detection, it is impossible to tell the difference between
     * being disconnected and suspended.
     */
    if (status & USB_INTS_DEV_SUSPEND_BITS) {
        handled |= USB_INTS_DEV_SUSPEND_BITS;
        /*!< Suspend */
        usb_hw_clear->sie_status = USB_SIE_STATUS_SUSPENDED_BITS;
        usbd_event_suspend_handler(0);
    }

    if (status & USB_INTS_DEV_RESUME_FROM_HOST_BITS) {
        handled |= USB_INTS_DEV_RESUME_FROM_HOST_BITS;
        /*!< Resume */
        usb_hw_clear->sie_status = USB_SIE_STATUS_RESUME_BITS;
        usbd_event_resume_handler(0);
    }

#ifdef CONFIG_USBDEV_SOF_ENABLE
    if (status & USB_INTS_DEV_SOF_BITS) {
        handled |= USB_INTS_DEV_SOF_BITS;
        usbd_event_sof_handler(0);
    }
#endif

    if (status ^ handled) {
        USB_LOG_INFO("Unhandled IRQ 0x%x\n", (uint32_t)(status ^ handled));
    }
}

void rp2040_usbd_irq(void)
{
    USBD_IRQHandler(0);
}