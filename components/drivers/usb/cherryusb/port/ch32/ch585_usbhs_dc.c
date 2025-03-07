#include "usbd_core.h"
#include "ch585_usbhs_reg.h"

/**
 * @brief   Related register macro
 */
#define USB_BASE        0x40009000u
#define CH585_USBHS_DEV ((USBHSD_TypeDef *)USB_BASE)

#ifndef USBD_IRQHandler
#define USBD_IRQHandler USB2_DEVICE_IRQHandler //use actual usb irq name instead
#endif

#define R16_PIN_CONFIG (*((PUINT16V)0x4000101A))
#define R32_PIN_CONFIG (*((PUINT32V)0x40001018)) // RW, I/O pin configuration
#define RB_PIN_USB2_EN 0x20

#define USB_SET_RX_DMA(ep_idx, addr) (*(volatile uint32_t *)((uint32_t)(&CH585_USBHS_DEV->UEP1_RX_DMA) + 4 * (ep_idx - 1)) = addr)
#define USB_SET_TX_DMA(ep_idx, addr) (*(volatile uint32_t *)((uint32_t)(&CH585_USBHS_DEV->UEP1_TX_DMA) + 4 * (ep_idx - 1)) = addr)

#define USB_SET_MAX_LEN(ep_idx, len) (*(volatile uint16_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_MAX_LEN) + 4 * ep_idx) = len)
#define USB_SET_TX_LEN(ep_idx, len)  (*(volatile uint16_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_TX_LEN) + 4 * ep_idx) = len)
#define USB_GET_TX_LEN(ep_idx)       (*(volatile uint16_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_TX_LEN) + 4 * ep_idx))
#define USB_SET_TX_CTRL(ep_idx, val) (*(volatile uint8_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_TX_CTRL) + 4 * ep_idx) = val)
#define USB_GET_TX_CTRL(ep_idx)      (*(volatile uint8_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_TX_CTRL) + 4 * ep_idx))
#define USB_SET_RX_CTRL(ep_idx, val) (*(volatile uint8_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_RX_CTRL) + 4 * ep_idx) = val)
#define USB_GET_RX_CTRL(ep_idx)      (*(volatile uint8_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_RX_CTRL) + 4 * ep_idx))
#define EPn_SET_TX_NAK(ep_idx)       USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_NAK)
#define EPn_SET_TX_VALID(ep_idx)     USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_ACK)
#define EPn_SET_RX_NAK(ep_idx)       USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBHS_UEP_R_RES_MASK) | USBHS_UEP_R_RES_NAK)
#define EPn_SET_RX_VALID(ep_idx)     USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBHS_UEP_R_RES_MASK) | USBHS_UEP_R_RES_ACK)
#define EPn_GET_RX_LEN(ep_idx)       (*(volatile uint16_t *)((uint32_t)(&CH585_USBHS_DEV->USB_EP0_RX_LEN) + 4 * ep_idx))
#define EPn_SET_TX_LEN(ep_idx, len)  (*(volatile uint16_t *)((uint32_t)(&CH585_USBHS_DEV->UEP0_TX_LEN) + 4 * ep_idx) = len)
#define EPn_CLEAR_TX_DONE(ep_idx)    USB_SET_TX_CTRL(ep_idx, USB_GET_TX_CTRL(ep_idx) & ~USBHS_UEP_T_DONE)
#define EPn_CLEAR_RX_DONE(ep_idx)    USB_SET_RX_CTRL(ep_idx, USB_GET_RX_CTRL(ep_idx) & ~USBHS_UEP_R_DONE)
#define EPn_SET_TX_ISO_VALID(ep_idx)
#define EPn_SET_RX_ISO_VALID(ep_idx)

/* ep nums */
#ifndef CONFIG_USBDEV_EP_NUM
#define CONFIG_USBDEV_EP_NUM 8
#endif

/**
 * @brief   Endpoint information structure
 */
typedef struct _usbd_ep_info {
    uint8_t mps;       /* Maximum packet length of endpoint */
    uint8_t eptype;    /* Endpoint Type */
    uint8_t ep_enable; /* Endpoint enable */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
} usbd_ep_info;

/* ch58x usb */
static struct _ch58x_core_prvi {
    uint8_t address; /* Address */
    usbd_ep_info ep_in[CONFIG_USBDEV_EP_NUM];
    usbd_ep_info ep_out[CONFIG_USBDEV_EP_NUM];
    struct usb_setup_packet setup;
} usb_dc_cfg;

__WEAK void usb_dc_low_level_init(void)
{
}

__WEAK void usb_dc_low_level_deinit(void)
{
}

/**
 * @brief            USB initialization
 * @pre              None
 * @param[in]        None
 * @retval           >=0 success otherwise failure
 */
int usb_dc_init(uint8_t busid)
{
    R8_USBHS_PLL_CTRL = USBHS_PLL_EN;
    R16_PIN_CONFIG |= RB_PIN_USB2_EN;
    CH585_USBHS_DEV->CONTROL = USBHS_UD_RST_LINK | USBHS_UD_PHY_SUSPENDM;
    CH585_USBHS_DEV->INT_EN = USBHS_UDIE_BUS_RST | USBHS_UDIE_SUSPEND | USBHS_UDIE_BUS_SLEEP | USBHS_UDIE_LPM_ACT | USBHS_UDIE_TRANSFER | USBHS_UDIE_LINK_RDY;
    /* Enable all end points */
    CH585_USBHS_DEV->UEP_TX_EN = 0xffff;
    CH585_USBHS_DEV->UEP_RX_EN = 0xffff;

    CH585_USBHS_DEV->BASE_MODE = USBHS_UD_SPEED_HIGH;
    CH585_USBHS_DEV->CONTROL = USBHS_UD_DEV_EN | USBHS_UD_DMA_EN | USBHS_UD_LPM_EN | USBHS_UD_PHY_SUSPENDM;

    CH585_USBHS_DEV->UEP_T_TOG_AUTO = 0xfe;
    CH585_USBHS_DEV->UEP_R_TOG_AUTO = 0xfe;
    usb_dc_low_level_init();
    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    R8_USBHS_PLL_CTRL &= ~USBHS_PLL_EN;
    R32_PIN_CONFIG &= ~RB_PIN_USB2_EN;

    CH585_USBHS_DEV->CONTROL |= USBHS_UD_RST_SIE;
    CH585_USBHS_DEV->CONTROL &= ~USBHS_UD_RST_SIE;
    usb_dc_low_level_deinit();
    return 0;
}

/**
 * @brief            Set address
 * @pre              None
 * @param[in]        address ：8-bit valid address
 * @retval           >=0 success otherwise failure
 */
int usbd_set_address(uint8_t busid, const uint8_t address)
{
    if (address == 0) {
        CH585_USBHS_DEV->DEV_AD = (CH585_USBHS_DEV->DEV_AD & 0x80) | address;
    }
    usb_dc_cfg.address = address;
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    return -1;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    return USB_SPEED_HIGH;
}

/**
 * @brief            Open endpoint
 * @pre              None
 * @param[in]        ep_cfg : Endpoint configuration structure pointer
 * @retval           >=0 success otherwise failure
 */
int usbd_ep_open(uint8_t busid, const struct usb_endpoint_descriptor *ep)
{
    uint8_t epid = USB_EP_GET_IDX(ep->bEndpointAddress);
    if (epid > (CONFIG_USBDEV_EP_NUM - 1)) {
        /**
         * If you use ch58x, you can change the CONFIG_USBDEV_EP_NUM set to 8
         */
        USB_LOG_ERR("Ep addr %02x overflow\r\n", ep->bEndpointAddress);
        return -1;
    }

    uint8_t mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
    USB_SET_MAX_LEN(epid, mps);

    if (USB_EP_DIR_IS_IN(ep->bEndpointAddress)) {
        usb_dc_cfg.ep_in[epid].ep_enable = true;
        usb_dc_cfg.ep_in[epid].mps = mps;
        usb_dc_cfg.ep_in[epid].eptype = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        USB_SET_TX_CTRL(epid, USBHS_UEP_T_RES_NAK);
        EPn_CLEAR_TX_DONE(epid);
    } else if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        usb_dc_cfg.ep_out[epid].ep_enable = true;
        usb_dc_cfg.ep_out[epid].mps = mps;
        usb_dc_cfg.ep_out[epid].eptype = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        USB_SET_RX_CTRL(epid, USBHS_UEP_R_RES_NAK);
    }

    return 0;
}

/**
 * @brief            Close endpoint
 * @pre              None
 * @param[in]        ep ： Endpoint address
 * @retval           >=0 success otherwise failure
 */
int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    uint8_t epid = USB_EP_GET_IDX(ep);
    if (USB_EP_DIR_IS_IN(ep)) {
        usb_dc_cfg.ep_in[epid].ep_enable = false;
    } else if (USB_EP_DIR_IS_OUT(ep)) {
        usb_dc_cfg.ep_out[epid].ep_enable = false;
    }
    return 0;
}

/**
 * @brief            Endpoint setting stall
 * @pre              None
 * @param[in]        ep ： Endpoint address
 * @retval           >=0 success otherwise failure
 */
int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);
    if (USB_EP_DIR_IS_OUT(ep)) {
        if (ep_idx == 0) {
            CH585_USBHS_DEV->UEP0_RX_CTRL = USBHS_UEP_R_RES_STALL;
        } else {
            USB_SET_RX_CTRL(ep_idx, (USB_GET_RX_CTRL(ep_idx) & ~USBHS_UEP_R_RES_MASK) | USBHS_UEP_R_RES_STALL);
        }
    } else {
        if (ep_idx == 0) {
            CH585_USBHS_DEV->UEP0_TX_CTRL = USBHS_UEP_T_RES_STALL;
        } else {
            USB_SET_TX_CTRL(ep_idx, (USB_GET_TX_CTRL(ep_idx) & ~USBHS_UEP_T_RES_MASK) | USBHS_UEP_T_RES_STALL);
        }
    }
    return 0;
}

/**
 * @brief            Endpoint clear stall
 * @pre              None
 * @param[in]        ep ： Endpoint address
 * @retval           >=0 success otherwise failure
 */
int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        USB_SET_RX_CTRL(ep_idx, USBHS_UEP_R_RES_ACK | USBHS_UEP_R_TOG_DATA0);
    } else {
        USB_SET_TX_CTRL(ep_idx, USBHS_UEP_T_RES_NAK | USBHS_UEP_T_TOG_DATA0);
    }
    return 0;
}

/**
 * @brief            Check endpoint status
 * @pre              None
 * @param[in]        ep ： Endpoint address
 * @param[out]       stalled ： Outgoing endpoint status
 * @retval           >=0 success otherwise failure
 */
int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    if (USB_EP_DIR_IS_OUT(ep)) {
    } else {
    }
    return 0;
}

/**
 * @brief Setup in ep transfer setting and start transfer.
 *
 * This function is asynchronous.
 * This function is similar to uart with tx dma.
 *
 * This function is called to write data to the specified endpoint. The
 * supplied usbd_endpoint_callback function will be called when data is transmitted
 * out.
 *
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      Pointer to data to write
 * @param[in]  data_len  Length of the data requested to write. This may
 *                       be zero for a zero length status packet.
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!usb_dc_cfg.ep_in[ep_idx].ep_enable) {
        return -2;
    }
    if ((uint32_t)data & 0x03) {
        return -3;
    }

    usb_dc_cfg.ep_in[ep_idx].xfer_buf = (uint8_t *)data;
    usb_dc_cfg.ep_in[ep_idx].xfer_len = data_len;
    usb_dc_cfg.ep_in[ep_idx].actual_xfer_len = 0;

    if (ep_idx == 0) {
        if (data_len == 0) {
            USB_SET_TX_LEN(ep_idx, 0);
        } else {
            data_len = MIN(data_len, usb_dc_cfg.ep_in[ep_idx].mps);
            USB_SET_TX_LEN(ep_idx, data_len);
            CH585_USBHS_DEV->UEP0_DMA = (uint32_t)data;
        }
    } else {
        if (data_len == 0) {
            USB_SET_TX_LEN(ep_idx, 0);
        } else {
            data_len = MIN(data_len, usb_dc_cfg.ep_in[ep_idx].mps);
            USB_SET_TX_LEN(ep_idx, data_len);
            USB_SET_TX_DMA(ep_idx, (uint32_t)data);
        }
    }

    EPn_SET_TX_VALID(ep_idx);
    return 0;
}

/**
 * @brief Setup out ep transfer setting and start transfer.
 *
 * This function is asynchronous.
 * This function is similar to uart with rx dma.
 *
 * This function is called to read data to the specified endpoint. The
 * supplied usbd_endpoint_callback function will be called when data is received
 * in.
 *
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      Pointer to data to read
 * @param[in]  data_len  Max length of the data requested to read.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!usb_dc_cfg.ep_out[ep_idx].ep_enable) {
        return -2;
    }
    if ((uint32_t)data & 0x03) {
        return -3;
    }

    usb_dc_cfg.ep_out[ep_idx].xfer_buf = (uint8_t *)data;
    usb_dc_cfg.ep_out[ep_idx].xfer_len = data_len;
    usb_dc_cfg.ep_out[ep_idx].actual_xfer_len = 0;

    if (ep_idx == 0) {
        if (data_len == 0) {
        } else {
            CH585_USBHS_DEV->UEP0_DMA = (uint32_t)data;
        }
    } else {
        USB_SET_RX_DMA(ep_idx, (uint32_t)data);
    }

    EPn_SET_RX_VALID(ep_idx);
    return 0;
}

static inline void handle_ep0_in(void)
{
    switch (usb_dc_cfg.setup.bmRequestType >> USB_REQUEST_DIR_SHIFT) {
        case 1:
            CH585_USBHS_DEV->UEP0_TX_CTRL ^= USBHS_UEP_T_TOG_DATA1;
            EPn_SET_TX_NAK(0);
            if (usb_dc_cfg.ep_in[0].xfer_len > usb_dc_cfg.ep_in[0].mps) {
                usb_dc_cfg.ep_in[0].xfer_len -= usb_dc_cfg.ep_in[0].mps;
                usb_dc_cfg.ep_in[0].actual_xfer_len += usb_dc_cfg.ep_in[0].mps;
                usbd_event_ep_in_complete_handler(0, 0 | 0x80, usb_dc_cfg.ep_in[0].actual_xfer_len);
            } else {
                usb_dc_cfg.ep_in[0].actual_xfer_len += usb_dc_cfg.ep_in[0].xfer_len;
                usb_dc_cfg.ep_in[0].xfer_len = 0;
                usbd_event_ep_in_complete_handler(0, 0 | 0x80, usb_dc_cfg.ep_in[0].actual_xfer_len);
            }
            break;
        case 0:
            /* Set */
            switch (usb_dc_cfg.setup.bRequest) {
                case USB_REQUEST_SET_ADDRESS:
                    /* Fill in the equipment address */
                    CH585_USBHS_DEV->DEV_AD = usb_dc_cfg.address;
                    CH585_USBHS_DEV->UEP0_DMA = (uint32_t)&usb_dc_cfg.setup;
                    EPn_SET_TX_NAK(0);
                    EPn_SET_RX_VALID(0);
                    break;
                default:
                    /* Normal out state phase */
                    CH585_USBHS_DEV->UEP0_DMA = (uint32_t)&usb_dc_cfg.setup;
                    EPn_SET_TX_NAK(0);
                    EPn_SET_RX_VALID(0);
                    break;
            }
            break;
    }
}

static inline void handle_non_ep0_in(uint8_t epid)
{
    EPn_SET_TX_NAK(epid);
    if (usb_dc_cfg.ep_in[epid].xfer_len > usb_dc_cfg.ep_in[epid].mps) {
        /* Need start in again */
        usb_dc_cfg.ep_in[epid].xfer_buf += usb_dc_cfg.ep_in[epid].mps;
        usb_dc_cfg.ep_in[epid].xfer_len -= usb_dc_cfg.ep_in[epid].mps;
        usb_dc_cfg.ep_in[epid].actual_xfer_len += usb_dc_cfg.ep_in[epid].mps;

        uint32_t write_count = MIN(usb_dc_cfg.ep_in[epid].xfer_len, usb_dc_cfg.ep_in[epid].mps);
        USB_SET_TX_LEN(epid, write_count);
        USB_SET_TX_DMA(epid, (uint32_t)usb_dc_cfg.ep_in[epid].xfer_buf);

        if (usb_dc_cfg.ep_in[epid].eptype != USB_ENDPOINT_TYPE_ISOCHRONOUS) {
            EPn_SET_TX_VALID(epid);
        } else {
            EPn_SET_TX_ISO_VALID(epid);
        }
    } else {
        usb_dc_cfg.ep_in[epid].actual_xfer_len += usb_dc_cfg.ep_in[epid].xfer_len;
        usb_dc_cfg.ep_in[epid].xfer_len = 0;
        usbd_event_ep_in_complete_handler(0, epid | 0x80, usb_dc_cfg.ep_in[epid].actual_xfer_len);
    }
}

static inline void usb_process_ep_in(uint8_t epid)
{
    if (epid == 0) {
        handle_ep0_in();
    } else {
        handle_non_ep0_in(epid);
    }

    EPn_CLEAR_TX_DONE(epid);
}

static inline void usb_process_ep_out(uint8_t epid)
{
    EPn_SET_RX_NAK(epid);
    if (epid == 0) {
        if (CH585_USBHS_DEV->UEP0_RX_CTRL & USBHS_UEP_R_SETUP_IS) {
            CH585_USBHS_DEV->UEP0_RX_CTRL |= USBHS_UEP_R_TOG_DATA1;
            CH585_USBHS_DEV->UEP0_TX_CTRL |= USBHS_UEP_T_TOG_DATA1;
            if (usb_dc_cfg.setup.bmRequestType >> USB_REQUEST_DIR_SHIFT == 0) {
                /**
                 * Ep0 The next in must be the status stage.
                 * The device must reply to the host data 0 length packet.
                 * Here, set the transmission length to 0 and the transmission status to ACK,
                 * and wait for the host to send the in token to retrieve
                 */
                EPn_SET_TX_LEN(0, 0);
                EPn_SET_TX_VALID(0);
            }
            usbd_event_ep0_setup_complete_handler(0, (uint8_t *)&usb_dc_cfg.setup);
        } else {
            CH585_USBHS_DEV->UEP0_RX_CTRL ^= USBHS_UEP_R_TOG_DATA1;
            uint32_t read_count = EPn_GET_RX_LEN(0);
            usb_dc_cfg.ep_out[0].actual_xfer_len += read_count;
            usb_dc_cfg.ep_out[0].xfer_len -= read_count;
            usbd_event_ep_out_complete_handler(0, 0x00, usb_dc_cfg.ep_out[0].actual_xfer_len);
            if (read_count == 0) {
                /* Out status, start reading setup */
                CH585_USBHS_DEV->UEP0_DMA = (uint32_t)&usb_dc_cfg.setup;
                EPn_SET_RX_VALID(0);
            }
        }
    } else {
        if (USB_GET_RX_CTRL(epid) & USBHS_UEP_R_TOG_MATCH) {
            uint32_t read_count = EPn_GET_RX_LEN(epid);
            usb_dc_cfg.ep_out[epid].xfer_buf += read_count;
            usb_dc_cfg.ep_out[epid].actual_xfer_len += read_count;
            usb_dc_cfg.ep_out[epid].xfer_len -= read_count;

            if ((read_count < usb_dc_cfg.ep_out[epid].mps) || (usb_dc_cfg.ep_out[epid].xfer_len == 0)) {
                usbd_event_ep_out_complete_handler(0, ((epid) & 0x7f), usb_dc_cfg.ep_out[epid].actual_xfer_len);
            } else {
                USB_SET_RX_DMA(epid, (uint32_t)usb_dc_cfg.ep_out[epid].xfer_buf);
                if (usb_dc_cfg.ep_out[epid].eptype != USB_ENDPOINT_TYPE_ISOCHRONOUS) {
                    EPn_SET_RX_VALID(epid);
                } else {
                    EPn_SET_RX_ISO_VALID(epid);
                }
            }
        }
    }

    EPn_CLEAR_RX_DONE(epid);
}

static inline void usb_trans_end_process(void)
{
    uint8_t epid = (CH585_USBHS_DEV->INT_ST & USBHS_UDIS_EP_ID_MASK);
    switch (CH585_USBHS_DEV->INT_ST & USBHS_UDIS_EP_DIR) {
        case USBHS_UDIS_EP_DIR: /* in */
            usb_process_ep_in(epid);
            break;
        case 0: /* setup or out */
            usb_process_ep_out(epid);
            break;
        default:
            break;
    }
}

/**
 * @brief            USB interrupt processing function
 * @pre              None
 * @param[in]        None
 * @retval           None
 */
__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode"))) void
USBD_IRQHandler(void)
{
    volatile uint8_t intflag = 0;
    intflag = CH585_USBHS_DEV->INT_FG;

    if (intflag & USBHS_UDIF_TRANSFER) {
        usb_trans_end_process();
    } else if (intflag & USBHS_UDIF_BUS_RST) {
        /* Reset */
        CH585_USBHS_DEV->DEV_AD = 0;
        usbd_event_reset_handler(0);
        /* Set ep0 rx vaild to start receive setup packet */
        CH585_USBHS_DEV->UEP0_DMA = (uint32_t)&usb_dc_cfg.setup;
        // EPn_SET_RX_VALID(0);
        R8_U2EP0_TX_CTRL = USBHS_UEP_T_RES_NAK;
        R8_U2EP0_RX_CTRL = USBHS_UEP_R_RES_ACK;
        CH585_USBHS_DEV->INT_FG = USBHS_UDIF_BUS_RST;
    } else if (intflag & USBHS_UDIF_SUSPEND) {
        if (CH585_USBHS_DEV->MIS_ST & 0x04) {
            /* Suspend */
        } else {
            /* Wake up */
        }
        CH585_USBHS_DEV->INT_FG = USBHS_UDIF_SUSPEND;
    } else {
        CH585_USBHS_DEV->INT_FG = intflag;
    }
}