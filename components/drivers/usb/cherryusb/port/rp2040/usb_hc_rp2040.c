/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbh_core.h"
#include "usbh_hub.h"
#include "hardware/resets.h"
#include "hardware/irq.h"
#include "hardware/structs/usb.h"

#define usb_hw_set   hw_set_alias(usb_hw)
#define usb_hw_clear hw_clear_alias(usb_hw)

#define SIE_CTRL_COMMON (USB_SIE_CTRL_SOF_EN_BITS |        \
                         USB_SIE_CTRL_KEEP_ALIVE_EN_BITS | \
                         USB_SIE_CTRL_PULLDOWN_EN_BITS |   \
                         USB_SIE_CTRL_EP0_INT_1BUF_BITS)

typedef enum {
    USB_EP0_STATE_SETUP = 0x0, /**< SETUP DATA */
    USB_EP0_STATE_IN_DATA,     /**< IN DATA */
    USB_EP0_STATE_IN_STATUS,   /**< IN status*/
    USB_EP0_STATE_OUT_DATA,    /**< OUT DATA */
    USB_EP0_STATE_OUT_STATUS,  /**< OUT status */
} ep0_state_t;

struct rp2040_pipe {
    uint8_t chidx;
    bool inuse;
    volatile uint8_t ep0_state;
    volatile uint32_t *endpoint_control; /*!< Endpoint control register */
    volatile uint32_t *buffer_control;   /*!< Buffer control register */
    uint8_t *data_buffer;                /*!< Buffer pointer in usb dpram */
    uint32_t buffer_size;                /*!< Buffer size */
    usb_osal_sem_t waitsem;
    struct usbh_urb *urb;
};

struct rp2040_hcd {
    volatile bool port_csc;
    volatile bool port_pec;
    volatile bool port_pe;
    usb_osal_mutex_t ep0_mutex;
    struct rp2040_pipe pipe_pool[1 + CONFIG_USBHOST_PIPE_NUM];
} g_rp2040_hcd[CONFIG_USBHOST_MAX_BUS];

void rp2040_usbh_irq(void);

static int rp2040_pipe_alloc(struct usbh_bus *bus)
{
    size_t flags;
    int chidx;

    flags = usb_osal_enter_critical_section();
    for (chidx = 1; chidx <= CONFIG_USBHOST_PIPE_NUM; chidx++) {
        if (!g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx].inuse) {
            g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx].inuse = true;
            usb_osal_leave_critical_section(flags);
            return chidx;
        }
    }
    usb_osal_leave_critical_section(flags);
    return -1;
}

static void rp2040_pipe_free(struct rp2040_pipe *pipe)
{
    size_t flags;

    flags = usb_osal_enter_critical_section();
    pipe->inuse = false;
    usb_osal_leave_critical_section(flags);
}

/**
 * @brief Take a buffer pointer located in the USB RAM and return as an offset of the RAM.
 *
 * @param buf
 * @return uint32_t
 */
static inline uint32_t usb_buffer_offset(volatile uint8_t *buf)
{
    return (uint32_t)buf ^ (uint32_t)usbh_dpram;
}

static inline uint8_t usbh_get_port_speed(void)
{
    return (usb_hw->sie_status & USB_SIE_STATUS_SPEED_BITS) >> USB_SIE_STATUS_SPEED_LSB;
}

static inline void rp2040_init_endpoint(struct usbh_bus *bus,
                                        uint8_t chidx,
                                        uint8_t dev_addr,
                                        uint8_t ep_addr,
                                        uint8_t ep_type,
                                        uint8_t ep_interval,
                                        uint8_t speed)
{
    struct rp2040_pipe *pipe;
    uint32_t regval;

    pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx];

    // Get the data buffer as an offset of the USB controller's DPRAM
    uint32_t dpram_offset = usb_buffer_offset(pipe->data_buffer);
    regval = EP_CTRL_ENABLE_BITS |
             EP_CTRL_INTERRUPT_PER_BUFFER |
             (ep_type << EP_CTRL_BUFFER_TYPE_LSB) |
             dpram_offset;

    if (ep_interval) {
        regval |= (uint32_t)((ep_interval - 1) << EP_CTRL_HOST_INTERRUPT_INTERVAL_LSB);
    }

    *pipe->endpoint_control = regval;

    if (chidx != 0) {
        regval = (uint32_t)(dev_addr | ((ep_addr & 0x0f) << USB_ADDR_ENDP1_ENDPOINT_LSB));

        if (!(ep_addr & 0x80)) {
            regval |= USB_ADDR_ENDP1_INTEP_DIR_BITS;
        }

        // ls device plugged to hub
        if ((usbh_get_port_speed() == USB_SPEED_FULL) && (speed == USB_SPEED_LOW)) {
            regval |= USB_ADDR_ENDP1_INTEP_PREAMBLE_BITS;
        }

        usb_hw->int_ep_addr_ctrl[(chidx - 1)] = regval;

        // Finally, enable interrupt that endpoint
        usb_hw_set->int_ep_ctrl = 1 << chidx;
    } else {
        usb_hw->dev_addr_ctrl = dev_addr;
    }
}

static inline uint32_t usb_buf_ctrl_fill(struct usbh_bus *bus, uint8_t chidx, uint8_t ep_addr, uint8_t buf_id)
{
    struct rp2040_pipe *pipe;
    struct usbh_urb *urb;
    uint32_t len;
    uint32_t buf_ctrl;

    pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx];
    urb = pipe->urb;

    len = MIN(urb->transfer_buffer_length, USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize));
    urb->transfer_buffer_length -= len;

    buf_ctrl = len | USB_BUF_CTRL_AVAIL;
    buf_ctrl |= urb->data_toggle ? USB_BUF_CTRL_DATA1_PID : USB_BUF_CTRL_DATA0_PID;

    if (USB_EP_DIR_IS_OUT(ep_addr)) {
        /*!< Need to copy the data from the user buffer to the usb memory */
        if (urb->transfer_buffer != NULL) {
            memcpy((void *)pipe->data_buffer + buf_id * 64, (void *)urb->transfer_buffer, len);
            urb->transfer_buffer += len;
        }
        /*!< Mark as full */
        buf_ctrl |= USB_BUF_CTRL_FULL;
    }

    if (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) != USB_ENDPOINT_TYPE_ISOCHRONOUS) {
        if (urb->transfer_buffer_length == 0) {
            buf_ctrl |= USB_BUF_CTRL_LAST;
        }
    } else {
        //TODO: handle isochronous transfer
    }

    if (buf_id)
        buf_ctrl = buf_ctrl << 16;

    return buf_ctrl;
}

/**
 * @brief Starts a transfer on a given endpoint.
 *
 * @param ep, the endpoint configuration.
 * @param buf, the data buffer to send. Only applicable if the endpoint is TX
 * @param len, the length of the data in buf (this example limits max len to one packet - 64 bytes)
 */
static void usb_start_transfer(struct usbh_bus *bus, uint8_t chidx, uint8_t ep_addr)
{
    struct rp2040_pipe *pipe;
    struct usbh_urb *urb;
    uint32_t buf_ctrl;
    uint32_t ep_ctrl;

    pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx];
    urb = pipe->urb;

    ep_ctrl = *pipe->endpoint_control;
    buf_ctrl = usb_buf_ctrl_fill(bus, chidx, ep_addr, 0);

    if (urb->transfer_buffer_length && (ep_addr & 0x0f) == 0x00) {
        urb->data_toggle ^= 1;
        buf_ctrl |= usb_buf_ctrl_fill(bus, chidx, ep_addr, 1);

        // Set endpoint control double buffered bit if needed
        ep_ctrl &= ~EP_CTRL_INTERRUPT_PER_BUFFER;
        ep_ctrl |= EP_CTRL_DOUBLE_BUFFERED_BITS | EP_CTRL_INTERRUPT_PER_DOUBLE_BUFFER;
    } else {
        // Single buffered since 1 is enough
        ep_ctrl &= ~(EP_CTRL_DOUBLE_BUFFERED_BITS | EP_CTRL_INTERRUPT_PER_DOUBLE_BUFFER);
        ep_ctrl |= EP_CTRL_INTERRUPT_PER_BUFFER;
    }
    *pipe->endpoint_control = ep_ctrl;
    *pipe->buffer_control = buf_ctrl;
}

static inline void rp2040_control_transfer_start(bool dir_in, bool isetup, uint8_t speed)
{
    uint32_t regval;

    regval = SIE_CTRL_COMMON | USB_SIE_CTRL_START_TRANS_BITS;

    if ((usbh_get_port_speed() == USB_SPEED_FULL) && (speed == USB_SPEED_LOW)) {
        regval |= USB_SIE_CTRL_PREAMBLE_EN_BITS;
    }

    if (isetup) {
        regval |= USB_SIE_CTRL_SEND_SETUP_BITS;
    } else {
        if (dir_in) {
            regval |= USB_SIE_CTRL_RECEIVE_DATA_BITS;
        } else {
            regval |= USB_SIE_CTRL_SEND_DATA_BITS;
        }
    }

    usb_hw->sie_ctrl = regval & ~USB_SIE_CTRL_START_TRANS_BITS;
    busy_wait_at_least_cycles(12);
    usb_hw->sie_ctrl = regval;
}

static void rp2040_control_urb_init(struct usbh_bus *bus, uint8_t chidx, struct usbh_urb *urb, struct usb_setup_packet *setup, uint8_t *buffer, uint32_t buflen)
{
    struct rp2040_pipe *pipe;

    pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx];

    if (pipe->ep0_state == USB_EP0_STATE_SETUP) /* fill setup */
    {
        pipe->urb->data_toggle = 1;
        memcpy((uint8_t *)usbh_dpram->setup_packet, (uint8_t *)setup, 8);
        rp2040_init_endpoint(bus, chidx, urb->hport->dev_addr, 0x00, USB_ENDPOINT_TYPE_CONTROL, 0, urb->hport->speed);
        rp2040_control_transfer_start(false, true, urb->hport->speed);
    } else if (pipe->ep0_state == USB_EP0_STATE_IN_DATA) /* fill in data */
    {
        rp2040_init_endpoint(bus, chidx, urb->hport->dev_addr, 0x80, USB_ENDPOINT_TYPE_CONTROL, 0, urb->hport->speed);
        usb_start_transfer(bus, chidx, 0x80);
        rp2040_control_transfer_start(true, false, urb->hport->speed);
    } else if (pipe->ep0_state == USB_EP0_STATE_OUT_DATA) /* fill out data */
    {
        rp2040_init_endpoint(bus, chidx, urb->hport->dev_addr, 0x00, USB_ENDPOINT_TYPE_CONTROL, 0, urb->hport->speed);
        usb_start_transfer(bus, chidx, 0x00);
        rp2040_control_transfer_start(false, false, urb->hport->speed);
    } else if (pipe->ep0_state == USB_EP0_STATE_IN_STATUS) /* fill in status */
    {
        urb->data_toggle = 1;
        rp2040_init_endpoint(bus, chidx, urb->hport->dev_addr, 0x80, USB_ENDPOINT_TYPE_CONTROL, 0, urb->hport->speed);
        usb_start_transfer(bus, chidx, 0x80);
        rp2040_control_transfer_start(true, false, urb->hport->speed);
    } else if (pipe->ep0_state == USB_EP0_STATE_OUT_STATUS) /* fill out status */
    {
        urb->data_toggle = 1;
        rp2040_init_endpoint(bus, chidx, urb->hport->dev_addr, 0x00, USB_ENDPOINT_TYPE_CONTROL, 0, urb->hport->speed);
        usb_start_transfer(bus, chidx, 0x00);
        rp2040_control_transfer_start(false, false, urb->hport->speed);
    }
}

static void rp2040_bulk_int_urb_init(struct usbh_bus *bus, uint8_t chidx, struct usbh_urb *urb, uint8_t *buffer, uint32_t buflen)
{
    rp2040_init_endpoint(bus, chidx, urb->hport->dev_addr, urb->ep->bEndpointAddress, USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes), urb->ep->bInterval, urb->hport->speed);
    usb_start_transfer(bus, chidx, urb->ep->bEndpointAddress);
}

int usb_hc_init(struct usbh_bus *bus)
{
    uint8_t *next_buffer_ptr;

    memset(&g_rp2040_hcd[bus->hcd.hcd_id], 0, sizeof(struct rp2040_hcd));

    for (uint8_t i = 0; i <= CONFIG_USBHOST_PIPE_NUM; i++) {
        g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].waitsem = usb_osal_sem_create(0);
        if (g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].waitsem == NULL) {
            USB_LOG_ERR("Failed to create waitsem\r\n");
            return -USB_ERR_NOMEM;
        }
    }

    g_rp2040_hcd[bus->hcd.hcd_id].ep0_mutex = usb_osal_mutex_create();
    if (g_rp2040_hcd[bus->hcd.hcd_id].ep0_mutex == NULL) {
        USB_LOG_ERR("Failed to create ep0_mutex\r\n");
        return -USB_ERR_NOMEM;
    }

    g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[0].endpoint_control = &usbh_dpram->epx_ctrl;
    g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[0].buffer_control = &usbh_dpram->epx_buf_ctrl;
    g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[0].data_buffer = &usbh_dpram->epx_data[0];
    g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[0].buffer_size = (64 * 2);

    next_buffer_ptr = &usb_dpram->epx_data[64 * 2];

    for (uint8_t i = 1; i <= CONFIG_USBHOST_PIPE_NUM; i++) {
        g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].chidx = i;
        g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].endpoint_control = &usbh_dpram->int_ep_ctrl[i - 1].ctrl;
        g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].buffer_control = &usbh_dpram->int_ep_buffer_ctrl[i - 1].ctrl;
        g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].data_buffer = next_buffer_ptr;
        g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].buffer_size = (64 * 2);
        next_buffer_ptr += (64 * 2);
    }

    // Reset usb controller
    reset_unreset_block_num_wait_blocking(RESET_USBCTRL);

    // Remove shared irq if it was previously added so as not to fill up shared irq slots
    irq_remove_handler(USBCTRL_IRQ, rp2040_usbh_irq);

    irq_add_shared_handler(USBCTRL_IRQ, rp2040_usbh_irq, PICO_SHARED_IRQ_HANDLER_HIGHEST_ORDER_PRIORITY);

    /*!< Clear any previous state just in case */
    memset(usb_hw, 0, sizeof(*usb_hw));
    memset(usbh_dpram, 0, sizeof(*usbh_dpram));

    /*!< Mux the controller to the onboard usb phy */
    usb_hw->muxing = USB_USB_MUXING_TO_PHY_BITS | USB_USB_MUXING_SOFTCON_BITS;

    // Force VBUS detect so the device thinks it is plugged into a host
    usb_hw->pwr = USB_USB_PWR_VBUS_DETECT_BITS | USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_BITS;

    // Enable the USB controller in device mode.
    usb_hw->main_ctrl = USB_MAIN_CTRL_CONTROLLER_EN_BITS | USB_MAIN_CTRL_HOST_NDEVICE_BITS;

    usb_hw->sie_ctrl = SIE_CTRL_COMMON;

    // Enable USB interrupt at processor
    irq_set_enabled(USBCTRL_IRQ, true);

    usb_hw->inte = USB_INTE_BUFF_STATUS_BITS |
                   USB_INTE_HOST_CONN_DIS_BITS |
                   USB_INTE_STALL_BITS |
                   USB_INTE_TRANS_COMPLETE_BITS |
                   USB_INTE_ERROR_RX_TIMEOUT_BITS |
                   USB_INTE_ERROR_DATA_SEQ_BITS;
    return 0;
}

int usb_hc_deinit(struct usbh_bus *bus)
{
    // Enable USB interrupt at processor
    irq_set_enabled(USBCTRL_IRQ, false);

    // Remove shared irq if it was previously added so as not to fill up shared irq slots
    irq_remove_handler(USBCTRL_IRQ, rp2040_usbh_irq);

    for (uint8_t i = 0; i <= CONFIG_USBHOST_PIPE_NUM; i++) {
        usb_osal_sem_delete(g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i].waitsem);
    }

    usb_osal_mutex_delete(g_rp2040_hcd[bus->hcd.hcd_id].ep0_mutex);

    return 0;
}

uint16_t usbh_get_frame_number(struct usbh_bus *bus)
{
    return usb_hw->sof_rd;
}

int usbh_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf)
{
    uint8_t nports;
    uint8_t port;
    uint32_t status;

    nports = CONFIG_USBHOST_MAX_RHPORTS;
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
                        return -USB_ERR_INVAL;
                }
                break;
            case HUB_REQUEST_SET_FEATURE:
                switch (setup->wValue) {
                    case HUB_FEATURE_HUB_C_LOCALPOWER:
                        break;
                    case HUB_FEATURE_HUB_C_OVERCURRENT:
                        break;
                    default:
                        return -USB_ERR_INVAL;
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
                        g_rp2040_hcd[bus->hcd.hcd_id].port_csc = 0;
                        break;
                    case HUB_PORT_FEATURE_C_ENABLE:
                        g_rp2040_hcd[bus->hcd.hcd_id].port_pec = 0;
                        break;
                    case HUB_PORT_FEATURE_C_OVER_CURREN:
                        break;
                    case HUB_PORT_FEATURE_C_RESET:
                        break;
                    default:
                        return -USB_ERR_INVAL;
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
                        break;

                    default:
                        return -USB_ERR_INVAL;
                }
                break;
            case HUB_REQUEST_GET_STATUS:
                if (!port || port > nports) {
                    return -USB_ERR_INVAL;
                }

                status = 0;
                if (g_rp2040_hcd[bus->hcd.hcd_id].port_csc) {
                    status |= (1 << HUB_PORT_FEATURE_C_CONNECTION);
                }
                if (g_rp2040_hcd[bus->hcd.hcd_id].port_pec) {
                    status |= (1 << HUB_PORT_FEATURE_C_ENABLE);
                }

                if (g_rp2040_hcd[bus->hcd.hcd_id].port_pe) {
                    status |= (1 << HUB_PORT_FEATURE_CONNECTION);
                    status |= (1 << HUB_PORT_FEATURE_ENABLE);
                    if (usbh_get_port_speed() == USB_SPEED_LOW) {
                        status |= (1 << HUB_PORT_FEATURE_LOWSPEED);
                    }
                }

                status |= (1 << HUB_PORT_FEATURE_POWER);
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
    struct rp2040_pipe *pipe;
    struct usbh_bus *bus;
    int chidx;
    size_t flags;
    int ret = 0;

    if (!urb || !urb->hport || !urb->ep || !urb->hport->bus) {
        return -USB_ERR_INVAL;
    }

    if (!urb->hport->connected || !(usb_hw->sie_status & USB_SIE_STATUS_SPEED_BITS)) {
        return -USB_ERR_NOTCONN;
    }

    if (urb->errorcode == -USB_ERR_BUSY) {
        return -USB_ERR_BUSY;
    }

    bus = urb->hport->bus;

    if (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes) == USB_ENDPOINT_TYPE_CONTROL) {
        chidx = 0;
        /* all the control transfers use the only one ep0 register, we need to lock */
        usb_osal_mutex_take(g_rp2040_hcd[bus->hcd.hcd_id].ep0_mutex);
    } else {
        chidx = rp2040_pipe_alloc(bus);
        if (chidx == -1) {
            return -USB_ERR_NOMEM;
        }
    }

    flags = usb_osal_enter_critical_section();

    pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[chidx];
    pipe->chidx = chidx;
    pipe->urb = urb;

    urb->hcpriv = pipe;
    urb->errorcode = -USB_ERR_BUSY;
    urb->actual_length = 0;
    usb_osal_leave_critical_section(flags);

    switch (USB_GET_ENDPOINT_TYPE(urb->ep->bmAttributes)) {
        case USB_ENDPOINT_TYPE_CONTROL:
            pipe->ep0_state = USB_EP0_STATE_SETUP;
            rp2040_control_urb_init(bus, 0, urb, urb->setup, urb->transfer_buffer, urb->transfer_buffer_length);
            break;
        case USB_ENDPOINT_TYPE_BULK:
        case USB_ENDPOINT_TYPE_INTERRUPT:
            rp2040_bulk_int_urb_init(bus, chidx, urb, urb->transfer_buffer, urb->transfer_buffer_length);
            break;
        default:
            break;
    }

    if (urb->timeout > 0) {
        /* wait until timeout or sem give */
        ret = usb_osal_sem_take(pipe->waitsem, urb->timeout);
        if (ret < 0) {
            goto errout_timeout;
        }
        urb->timeout = 0;
        ret = urb->errorcode;
        /* we can free pipe when waitsem is done */
        rp2040_pipe_free(pipe);

        if (chidx == 0) {
            usb_osal_mutex_give(g_rp2040_hcd[bus->hcd.hcd_id].ep0_mutex);
        }
    }
    return ret;
errout_timeout:
    if (chidx == 0) {
        usb_osal_mutex_give(g_rp2040_hcd[bus->hcd.hcd_id].ep0_mutex);
    }
    urb->timeout = 0;
    usbh_kill_urb(urb);
    return ret;
}

int usbh_kill_urb(struct usbh_urb *urb)
{
    struct rp2040_pipe *pipe;
    struct usbh_bus *bus;
    size_t flags;

    if (!urb || !urb->hcpriv || !urb->hport->bus) {
        return -USB_ERR_INVAL;
    }

    bus = urb->hport->bus;

    ARG_UNUSED(bus);

    flags = usb_osal_enter_critical_section();

    pipe = (struct rp2040_pipe *)urb->hcpriv;
    urb->hcpriv = NULL;
    urb->errorcode = -USB_ERR_SHUTDOWN;
    pipe->urb = NULL;
    usb_hw_clear->int_ep_ctrl = 1 << pipe->chidx;
    usb_hw_clear->buf_status = 1 << (pipe->chidx * 2 + 0);
    usb_hw_clear->buf_status = 1 << (pipe->chidx * 2 + 1);
    *pipe->endpoint_control = 0;
    *pipe->buffer_control = 0;

    if (urb->timeout) {
        usb_osal_sem_give(pipe->waitsem);
    } else {
        rp2040_pipe_free(pipe);
    }

    usb_osal_leave_critical_section(flags);

    return 0;
}

static void rp2040_urb_waitup(struct usbh_urb *urb)
{
    struct rp2040_pipe *pipe;

    pipe = (struct rp2040_pipe *)urb->hcpriv;
    pipe->urb = NULL;
    urb->hcpriv = NULL;

    if (urb->timeout) {
        usb_osal_sem_give(pipe->waitsem);
    } else {
        rp2040_pipe_free(pipe);
    }

    if (urb->complete) {
        if (urb->errorcode < 0) {
            urb->complete(urb->arg, urb->errorcode);
        } else {
            urb->complete(urb->arg, urb->actual_length);
        }
    }
}

static void rp2040_handle_buffer_status(struct usbh_bus *bus)
{
    struct rp2040_pipe *pipe;
    struct usbh_urb *urb;
    uint32_t remaining_buffers;
    uint32_t size;

    remaining_buffers = usb_hw->buf_status;

    uint32_t bit = 1u;
    if (remaining_buffers & bit) {
        remaining_buffers &= ~bit;
        usb_hw_clear->buf_status = bit;

        pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[0];
        urb = pipe->urb;
        switch (pipe->ep0_state) {
            case USB_EP0_STATE_IN_DATA:
                size = *pipe->buffer_control & USB_BUF_CTRL_LEN_MASK;
                memcpy(urb->transfer_buffer, (uint8_t *)pipe->data_buffer, size);

                urb->transfer_buffer += size;
                urb->actual_length += size;

                if (*pipe->endpoint_control & EP_CTRL_DOUBLE_BUFFERED_BITS) {
                    if (size == USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) {
                        size = (*pipe->buffer_control >> 16) & USB_BUF_CTRL_LEN_MASK;
                        memcpy(urb->transfer_buffer, (uint8_t *)pipe->data_buffer + 64, size);

                        urb->transfer_buffer += size;
                        urb->actual_length += size;
                    }
                }

                if ((size < USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize)) || (urb->transfer_buffer_length == 0)) {
                    pipe->ep0_state = USB_EP0_STATE_OUT_STATUS;
                    rp2040_control_urb_init(bus, 0, urb, urb->setup, urb->transfer_buffer, urb->transfer_buffer_length);
                } else {
                    urb->data_toggle ^= 1;
                    usb_start_transfer(bus, 0, 0x80);
                }
                break;
            case USB_EP0_STATE_OUT_DATA:
                urb->actual_length += *pipe->buffer_control & USB_BUF_CTRL_LEN_MASK;

                if (*pipe->endpoint_control & EP_CTRL_DOUBLE_BUFFERED_BITS) {
                    urb->actual_length += (*pipe->buffer_control >> 16) & USB_BUF_CTRL_LEN_MASK;
                }

                if (urb->transfer_buffer_length == 0) {
                    pipe->ep0_state = USB_EP0_STATE_IN_STATUS;
                    rp2040_control_urb_init(bus, 0, urb, urb->setup, urb->transfer_buffer, urb->transfer_buffer_length);
                } else {
                    urb->data_toggle ^= 1;
                    usb_start_transfer(bus, 0, 0x00);
                }
                break;
            case USB_EP0_STATE_IN_STATUS:
            case USB_EP0_STATE_OUT_STATUS:
                urb->errorcode = 0;
                rp2040_urb_waitup(urb);
                break;
            default:
                break;
        }
    }

    for (uint8_t i = 1; remaining_buffers && i <= CONFIG_USBHOST_PIPE_NUM; i++) {
        for (uint8_t j = 0; j < 2; j++) {
            bit = 1 << (i * 2 + j);
            if (remaining_buffers & bit) {
                remaining_buffers &= ~bit;
                usb_hw_clear->buf_status = bit;

                pipe = &g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[i];
                urb = pipe->urb;
                if (urb == NULL) {
                    continue;
                }

                if (j == 0) { //IN
                    size = *pipe->buffer_control & USB_BUF_CTRL_LEN_MASK;
                    memcpy(urb->transfer_buffer, (uint8_t *)pipe->data_buffer, size);

                    urb->transfer_buffer += size;
                    urb->actual_length += size;

                    urb->data_toggle ^= 1;
                    if (size < USB_GET_MAXPACKETSIZE(urb->ep->wMaxPacketSize) || urb->transfer_buffer_length == 0) {
                        urb->errorcode = 0;
                        rp2040_urb_waitup(urb);
                    } else {
                        usb_start_transfer(bus, i, urb->ep->bEndpointAddress);
                    }
                } else { //OUT
                    urb->data_toggle ^= 1;

                    urb->actual_length += *pipe->buffer_control & USB_BUF_CTRL_LEN_MASK;

                    if (urb->transfer_buffer_length == 0) {
                        urb->errorcode = 0;
                        rp2040_urb_waitup(urb);
                    } else {
                        usb_start_transfer(bus, i, urb->ep->bEndpointAddress);
                    }
                }
            }
        }
    }
}

void USBH_IRQHandler(uint8_t busid)
{
    uint32_t status;
    uint32_t handled = 0;
    struct usbh_bus *bus;
    struct rp2040_pipe *pipe;
    struct usbh_urb *urb;

    bus = &g_usbhost_bus[busid];
    status = usb_hw->ints;

    if (status & USB_INTS_HOST_CONN_DIS_BITS) {
        handled |= USB_INTS_HOST_CONN_DIS_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_SPEED_BITS;
        if (usbh_get_port_speed()) {
            g_rp2040_hcd[bus->hcd.hcd_id].port_csc = 1;
            g_rp2040_hcd[bus->hcd.hcd_id].port_pec = 1;
            g_rp2040_hcd[bus->hcd.hcd_id].port_pe = 1;
            bus->hcd.roothub.int_buffer[0] = (1 << 1);
            usbh_hub_thread_wakeup(&bus->hcd.roothub);
        } else {
            g_rp2040_hcd[bus->hcd.hcd_id].port_csc = 1;
            g_rp2040_hcd[bus->hcd.hcd_id].port_pec = 1;
            g_rp2040_hcd[bus->hcd.hcd_id].port_pe = 0;
            bus->hcd.roothub.int_buffer[0] = (1 << 1);
            usbh_hub_thread_wakeup(&bus->hcd.roothub);
        }
    }

    if (status & USB_INTS_STALL_BITS) {
        handled |= USB_INTS_STALL_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_STALL_REC_BITS;
    }

    if (status & USB_INTS_BUFF_STATUS_BITS) {
        handled |= USB_INTS_BUFF_STATUS_BITS;
        rp2040_handle_buffer_status(bus);
    }

    if (status & USB_INTS_TRANS_COMPLETE_BITS) {
        handled |= USB_INTS_TRANS_COMPLETE_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_TRANS_COMPLETE_BITS;
        if (usb_hw->sie_ctrl & USB_SIE_CTRL_SEND_SETUP_BITS) {
            pipe = (struct rp2040_pipe *)&g_rp2040_hcd[bus->hcd.hcd_id].pipe_pool[0];
            urb = pipe->urb;
            if (urb) {
                if (urb->setup->wLength) {
                    if (urb->setup->bmRequestType & 0x80) {
                        pipe->ep0_state = USB_EP0_STATE_IN_DATA;
                    } else {
                        pipe->ep0_state = USB_EP0_STATE_OUT_DATA;
                    }
                } else {
                    pipe->ep0_state = USB_EP0_STATE_IN_STATUS;
                }
                urb->actual_length = 8;
                rp2040_control_urb_init(bus, 0, urb, urb->setup, urb->transfer_buffer, urb->transfer_buffer_length);
            }
        } else {
        }
    }

    if (status & USB_INTS_ERROR_RX_TIMEOUT_BITS) {
        handled |= USB_INTS_ERROR_RX_TIMEOUT_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_RX_TIMEOUT_BITS;
    }

    if (status & USB_INTS_ERROR_DATA_SEQ_BITS) {
        handled |= USB_INTS_ERROR_DATA_SEQ_BITS;
        usb_hw_clear->sie_status = USB_SIE_STATUS_DATA_SEQ_ERROR_BITS;
    }

    if (status ^ handled) {
        USB_LOG_ERR("Unhandled IRQ 0x%x\n", (uint)(status ^ handled));
    }
}

void rp2040_usbh_irq(void)
{
    USBH_IRQHandler(0);
}