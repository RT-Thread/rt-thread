#include "bflb_core.h"
#include "bflb_gpio.h"
#include "usbd_core.h"
#include "hardware/usb_v1_reg.h"

#define BL702_USB_BASE ((uint32_t)0x4000D800)
#define BL702_GLB_BASE ((uint32_t)0x40000000)

#define GLB_USB_XCVR_OFFSET        (0x228) /* usb_xcvr */
#define GLB_USB_XCVR_CONFIG_OFFSET (0x22C) /* usb_xcvr_config */

/* 0x228 : usb_xcvr */
#define GLB_USB_LDO_VFB_SHIFT   (0U)
#define GLB_USB_LDO_VFB_MASK    (0x7 << GLB_USB_LDO_VFB_SHIFT)
#define GLB_PU_USB_LDO          (1 << 3U)
#define GLB_USB_ROUT_NMOS_SHIFT (4U)
#define GLB_USB_ROUT_NMOS_MASK  (0x7 << GLB_USB_ROUT_NMOS_SHIFT)
#define GLB_USB_ROUT_PMOS_SHIFT (8U)
#define GLB_USB_ROUT_PMOS_MASK  (0x7 << GLB_USB_ROUT_PMOS_SHIFT)
#define GLB_USB_OEB_SEL         (1 << 12U)
#define GLB_USB_OEB_REG         (1 << 13U)
#define GLB_USB_OEB             (1 << 14U)
#define GLB_USB_DATA_CONVERT    (1 << 16U)
#define GLB_USB_ENUM            (1 << 20U)
#define GLB_USB_SPD             (1 << 21U)
#define GLB_USB_SUS             (1 << 22U)
#define GLB_PU_USB              (1 << 23U)
#define GLB_USB_BD              (1 << 24U)
#define GLB_USB_VIM             (1 << 25U)
#define GLB_USB_VIP             (1 << 26U)
#define GLB_USB_RCV             (1 << 27U)

/* 0x22C : usb_xcvr_config */
#define GLB_USB_V_HYS_M_SHIFT         (0U)
#define GLB_USB_V_HYS_M_MASK          (0x3 << GLB_USB_V_HYS_M_SHIFT)
#define GLB_USB_V_HYS_P_SHIFT         (2U)
#define GLB_USB_V_HYS_P_MASK          (0x3 << GLB_USB_V_HYS_P_SHIFT)
#define GLB_USB_BD_VTH_SHIFT          (4U)
#define GLB_USB_BD_VTH_MASK           (0x7 << GLB_USB_BD_VTH_SHIFT)
#define GLB_REG_USB_USE_XCVR          (1 << 7U)
#define GLB_USB_STR_DRV_SHIFT         (8U)
#define GLB_USB_STR_DRV_MASK          (0x7 << GLB_USB_STR_DRV_SHIFT)
#define GLB_REG_USB_USE_CTRL          (1 << 11U)
#define GLB_USB_RES_PULLUP_TUNE_SHIFT (12U)
#define GLB_USB_RES_PULLUP_TUNE_MASK  (0x7 << GLB_USB_RES_PULLUP_TUNE_SHIFT)
#define GLB_USB_SLEWRATE_M_FALL_SHIFT (16U)
#define GLB_USB_SLEWRATE_M_FALL_MASK  (0x7 << GLB_USB_SLEWRATE_M_FALL_SHIFT)
#define GLB_USB_SLEWRATE_M_RISE_SHIFT (20U)
#define GLB_USB_SLEWRATE_M_RISE_MASK  (0x7 << GLB_USB_SLEWRATE_M_RISE_SHIFT)
#define GLB_USB_SLEWRATE_P_FALL_SHIFT (24U)
#define GLB_USB_SLEWRATE_P_FALL_MASK  (0x7 << GLB_USB_SLEWRATE_P_FALL_SHIFT)
#define GLB_USB_SLEWRATE_P_RISE_SHIFT (28U)
#define GLB_USB_SLEWRATE_P_RISE_MASK  (0x7 << GLB_USB_SLEWRATE_P_RISE_SHIFT)

#define USB_NUM_BIDIR_ENDPOINTS 9

/* Endpoint state */
struct bl_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t ep_enable;  /* Endpoint enable */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

struct bl_udc {
    struct usb_setup_packet setup;
    struct bl_ep_state in_ep[USB_NUM_BIDIR_ENDPOINTS];  /*!< IN endpoint parameters             */
    struct bl_ep_state out_ep[USB_NUM_BIDIR_ENDPOINTS]; /*!< OUT endpoint parameters            */
} g_bl_udc;

void USBD_IRQHandler(int irq, void *arg);

static void bflb_usb_mem2fifo(uint8_t ep_idx, uint8_t *data, uint32_t length)
{
    uint32_t fifo_addr = BL702_USB_BASE + USB_EP0_TX_FIFO_WDATA_OFFSET + ep_idx * 0x10;

    uint8_t *p = (uint8_t *)fifo_addr;
    uint8_t *q = data;

    while (length--) {
        *p = *q++;
    }
}

static void bflb_usb_fifo2mem(uint8_t ep_idx, uint8_t *data, uint32_t length)
{
    uint32_t fifo_addr = BL702_USB_BASE + USB_EP0_RX_FIFO_RDATA_OFFSET + ep_idx * 0x10;

    uint8_t *p = (uint8_t *)fifo_addr;
    uint8_t *q = data;

    while (length--) {
        *q++ = *p;
    }
}

static void bflb_usb_xcvr_config(void)
{
    uint32_t regval;

    regval = getreg32(BL702_GLB_BASE + GLB_USB_XCVR_OFFSET);
    regval |= GLB_PU_USB;
    putreg32(regval, BL702_GLB_BASE + GLB_USB_XCVR_OFFSET);

    regval = getreg32(BL702_GLB_BASE + GLB_USB_XCVR_OFFSET);
    regval &= ~GLB_USB_SUS;
    regval |= GLB_USB_SPD; /* 0 for 1.1 ls,1 for 1.1 fs */
    regval &= ~GLB_USB_DATA_CONVERT;
    regval &= ~GLB_USB_OEB_SEL;
    regval &= ~GLB_USB_ROUT_PMOS_MASK;
    regval &= ~GLB_USB_ROUT_NMOS_MASK;
    regval |= (3 << GLB_USB_ROUT_PMOS_SHIFT);
    regval |= (3 << GLB_USB_ROUT_NMOS_SHIFT);
    putreg32(regval, BL702_GLB_BASE + GLB_USB_XCVR_OFFSET);

    regval = 0;
    regval |= (2 << GLB_USB_V_HYS_M_SHIFT);
    regval |= (2 << GLB_USB_V_HYS_P_SHIFT);
    regval |= (7 << GLB_USB_BD_VTH_SHIFT);
    regval |= GLB_REG_USB_USE_XCVR;
    regval |= GLB_REG_USB_USE_CTRL;
    regval |= (0 << GLB_USB_STR_DRV_SHIFT);
    regval |= (5 << GLB_USB_RES_PULLUP_TUNE_SHIFT);
    regval |= (2 << GLB_USB_SLEWRATE_M_FALL_SHIFT);
    regval |= (2 << GLB_USB_SLEWRATE_M_RISE_SHIFT);
    regval |= (2 << GLB_USB_SLEWRATE_P_FALL_SHIFT);
    regval |= (2 << GLB_USB_SLEWRATE_P_RISE_SHIFT);
    putreg32(regval, BL702_GLB_BASE + GLB_USB_XCVR_CONFIG_OFFSET);

    regval = getreg32(BL702_GLB_BASE + GLB_USB_XCVR_OFFSET);
    regval |= GLB_USB_ENUM;
    putreg32(regval, BL702_GLB_BASE + GLB_USB_XCVR_OFFSET);
}

static void bflb_usb_ep0_size(uint8_t ep_mps)
{
    uint32_t regval;

    regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
    regval &= ~USB_CR_USB_EP0_SW_SIZE_MASK;
    regval |= (ep_mps << USB_CR_USB_EP0_SW_SIZE_SHIFT);
    putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);
}

static void bflb_usb_ep_config(uint8_t ep_idx, uint8_t ep_type, uint8_t dir, uint16_t ep_mps)
{
    uint32_t regval;

    regval = getreg32(BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
    regval &= ~USB_CR_EP1_SIZE_MASK;
    regval &= ~USB_CR_EP1_TYPE_MASK;
    regval &= ~USB_CR_EP1_DIR_MASK;
    regval |= (ep_mps << USB_CR_EP1_SIZE_SHIFT);
    regval |= (dir << USB_CR_EP1_DIR_SHIFT);
    regval |= (ep_type << USB_CR_EP1_TYPE_SHIFT);
    putreg32(regval, BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
}

static void bflb_usb_ep_set_nak(uint8_t ep_idx)
{
    uint32_t regval;

    if (ep_idx == 0) {
        regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
        regval |= USB_CR_USB_EP0_SW_NACK_OUT;
        regval |= USB_CR_USB_EP0_SW_NACK_IN;
        putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);
    } else {
        regval = getreg32(BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
        regval |= USB_CR_EP1_NACK;
        regval &= ~USB_CR_EP1_STALL;
        putreg32(regval, BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
    }
}

static void bflb_usb_ep_set_ready(uint8_t ep_idx)
{
    uint32_t regval;

    if (ep_idx == 0) {
        regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
        regval |= USB_CR_USB_EP0_SW_RDY;
        regval |= USB_CR_USB_EP0_SW_NACK_OUT;
        regval |= USB_CR_USB_EP0_SW_NACK_IN;
        regval &= ~USB_CR_USB_EP0_SW_STALL;
        putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);
    } else {
        regval = getreg32(BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
        regval |= USB_CR_EP1_RDY;
        regval |= USB_CR_EP1_NACK;
        regval &= ~USB_CR_EP1_STALL;
        putreg32(regval, BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
    }
}

static uint16_t bflb_usb_get_rxcount(uint8_t ep_idx)
{
    return (getreg32(BL702_USB_BASE + USB_EP0_FIFO_STATUS_OFFSET + 0x10 * ep_idx) & USB_EP0_RX_FIFO_CNT_MASK) >> USB_EP0_RX_FIFO_CNT_SHIFT;
}

// static uint16_t bflb_usb_get_txcount(uint8_t ep_idx)
// {
//     return (getreg32(BL702_USB_BASE + USB_EP0_FIFO_STATUS_OFFSET + 0x10 * ep_idx) & USB_EP0_TX_FIFO_CNT_MASK) >> USB_EP0_TX_FIFO_CNT_SHIFT;
// }

static bool bflb_usb_ep_isbusy(uint8_t ep_idx)
{
    uint32_t regval;

    if (ep_idx == 0) {
        regval = (getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET) & USB_STS_USB_EP0_SW_RDY);
    } else {
        regval = (getreg32(BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1)) & USB_STS_EP1_RDY);
    }
    return regval ? true : false;
}

static uint32_t bflb_usb_get_intstatus(void)
{
    uint32_t regval;

    regval = getreg32(BL702_USB_BASE + USB_INT_STS_OFFSET);
    regval &= ~getreg32(BL702_USB_BASE + USB_INT_MASK_OFFSET);
    regval &= getreg32(BL702_USB_BASE + USB_INT_EN_OFFSET);
    return regval;
}

static void bflb_usb_int_clear(uint32_t int_clear)
{
    uint32_t regval;
    regval = getreg32(BL702_USB_BASE + USB_INT_CLEAR_OFFSET);
    regval |= int_clear;
    putreg32(regval, BL702_USB_BASE + USB_INT_CLEAR_OFFSET);
}

int usb_dc_init(void)
{
    uint32_t regval;

    struct bflb_device_s *gpio;

    gpio = bflb_device_get_by_name("gpio");
    bflb_gpio_init(gpio, GPIO_PIN_7, GPIO_ANALOG | GPIO_SMT_EN | GPIO_DRV_0);
    bflb_gpio_init(gpio, GPIO_PIN_8, GPIO_ANALOG | GPIO_SMT_EN | GPIO_DRV_0);

    bflb_usb_xcvr_config();

    /* disable USB first */
    regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
    regval &= ~USB_CR_USB_EN;
    putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);

    /* USB ep0 config */
    regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
    regval |= USB_CR_USB_EP0_SW_CTRL;
    regval &= ~USB_CR_USB_EP0_SW_ADDR_MASK;
    regval &= ~USB_CR_USB_EP0_SW_SIZE_MASK;
    regval |= (64 << USB_CR_USB_EP0_SW_SIZE_SHIFT);
    regval |= USB_CR_USB_EP0_SW_NACK_IN;
    regval |= USB_CR_USB_EP0_SW_NACK_OUT;
    regval &= ~USB_CR_USB_ROM_DCT_EN;
    putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);

    regval = 0;
    regval |= USB_CR_USB_RESET_EN;
    regval |= USB_CR_EP0_SETUP_DONE_EN;
    regval |= USB_CR_EP0_IN_DONE_EN;
    regval |= USB_CR_EP0_OUT_DONE_EN;
    regval |= USB_CR_USB_REND_EN;
    putreg32(regval, BL702_USB_BASE + USB_INT_EN_OFFSET);

    regval = 0xffffffff;
    regval &= ~USB_CR_USB_RESET_MASK;
    regval &= ~USB_CR_EP0_SETUP_DONE_MASK;
    regval &= ~USB_CR_EP0_IN_DONE_MASK;
    regval &= ~USB_CR_EP0_OUT_DONE_MASK;
    regval &= ~USB_CR_USB_REND_MASK;
    putreg32(regval, BL702_USB_BASE + USB_INT_MASK_OFFSET);

    putreg32(0xffffffff, BL702_USB_BASE + USB_INT_CLEAR_OFFSET);

    bflb_irq_attach(37, USBD_IRQHandler, NULL);
    bflb_irq_enable(37);

    /* enable usb */
    regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
    regval |= USB_CR_USB_EN;
    putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);

    return 0;
}

int usbd_set_address(const uint8_t addr)
{
    uint32_t regval;

    regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
    regval &= ~USB_CR_USB_EP0_SW_ADDR_MASK;
    regval |= (addr << USB_CR_USB_EP0_SW_ADDR_SHIFT);
    putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);

    return 0;
}

uint8_t usbd_get_port_speed(const uint8_t port)
{
    return USB_SPEED_FULL;
}

int usbd_ep_open(const struct usbd_endpoint_cfg *ep_cfg)
{
    uint8_t ep;
    uint8_t ep_type;
    uint8_t dir;
    uint32_t regval;

    ep = ep_cfg->ep_addr;

    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx > USB_NUM_BIDIR_ENDPOINTS) {
        return -1;
    }

    if (USB_EP_DIR_IS_OUT(ep)) {
        g_bl_udc.out_ep[ep_idx].ep_mps = ep_cfg->ep_mps;
        g_bl_udc.out_ep[ep_idx].ep_type = ep_cfg->ep_type;
        g_bl_udc.out_ep[ep_idx].ep_enable = 1U;
        dir = 2;
    } else {
        g_bl_udc.in_ep[ep_idx].ep_mps = ep_cfg->ep_mps;
        g_bl_udc.in_ep[ep_idx].ep_type = ep_cfg->ep_type;
        g_bl_udc.in_ep[ep_idx].ep_enable = 1U;
        dir = 1;
    }

    if (ep_idx != 0) {
        switch (ep_cfg->ep_type) {
            case 1:
                ep_type = 2;
                break;
            case 2:
                ep_type = 4;
                break;
            case 3:
                ep_type = 0;
                break;

            default:
                ep_type = 4;
                break;
        }
        bflb_usb_ep_config(ep_idx, ep_type, dir, ep_cfg->ep_mps);

        regval = getreg32(BL702_USB_BASE + USB_INT_EN_OFFSET);
        regval |= (1 << (9 + ep_idx * 2));
        putreg32(regval, BL702_USB_BASE + USB_INT_EN_OFFSET);

        regval = getreg32(BL702_USB_BASE + USB_INT_MASK_OFFSET);
        regval &= ~(1 << (9 + ep_idx * 2));
        putreg32(regval, BL702_USB_BASE + USB_INT_MASK_OFFSET);

        bflb_usb_ep_set_nak(ep_idx);
    }
    return 0;
}

int usbd_ep_close(const uint8_t ep)
{
    return 0;
}

int usbd_ep_set_stall(const uint8_t ep)
{
    uint32_t regval;

    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx == 0) {
        regval = getreg32(BL702_USB_BASE + USB_CONFIG_OFFSET);
        regval |= USB_CR_USB_EP0_SW_RDY;
        regval |= USB_CR_USB_EP0_SW_NACK_OUT;
        regval |= USB_CR_USB_EP0_SW_NACK_IN;
        regval |= USB_CR_USB_EP0_SW_STALL;
        putreg32(regval, BL702_USB_BASE + USB_CONFIG_OFFSET);

    } else {
        regval = getreg32(BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
        regval |= USB_CR_EP1_STALL;
        putreg32(regval, BL702_USB_BASE + USB_EP1_CONFIG_OFFSET + 4 * (ep_idx - 1));
    }

    return 0;
}

int usbd_ep_clear_stall(const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (ep_idx == 0) {
    } else {
        bflb_usb_ep_set_ready(ep_idx);
    }

    return 0;
}

int usbd_ep_is_stalled(const uint8_t ep, uint8_t *stalled)
{
    return 0;
}

int usbd_ep_start_write(const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }

    if (!g_bl_udc.in_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_bl_udc.in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_bl_udc.in_ep[ep_idx].xfer_len = data_len;
    g_bl_udc.in_ep[ep_idx].actual_xfer_len = 0;

    data_len = MIN(data_len, g_bl_udc.in_ep[ep_idx].ep_mps);

    if (ep_idx == 0) {
        if (data_len == 1) {
            bflb_usb_ep0_size(1);
        } else {
            bflb_usb_ep0_size(g_bl_udc.in_ep[ep_idx].ep_mps);
        }
    }

    bflb_usb_mem2fifo(ep_idx, g_bl_udc.in_ep[ep_idx].xfer_buf, data_len);
    bflb_usb_ep_set_ready(ep_idx);

    return 0;
}

int usbd_ep_start_read(const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }

    if (!g_bl_udc.out_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_bl_udc.out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_bl_udc.out_ep[ep_idx].xfer_len = data_len;
    g_bl_udc.out_ep[ep_idx].actual_xfer_len = 0;
    bflb_usb_ep_set_ready(ep_idx);

    return 0;
}

void USBD_IRQHandler(int irq, void *arg)
{
    uint32_t regval;
    uint32_t intstatus;
    uint16_t rx_count;
    uint16_t tx_count;

    intstatus = bflb_usb_get_intstatus();
    bflb_usb_int_clear(intstatus);

    for (uint8_t ep_idx = 1; ep_idx < USB_NUM_BIDIR_ENDPOINTS; ep_idx++) {
        if (intstatus & (1 << (9 + 2 * ep_idx))) {
            if (g_bl_udc.in_ep[ep_idx].ep_enable) {
                tx_count = MIN(g_bl_udc.in_ep[ep_idx].xfer_len, g_bl_udc.in_ep[ep_idx].ep_mps);
                g_bl_udc.in_ep[ep_idx].xfer_buf += tx_count;
                g_bl_udc.in_ep[ep_idx].xfer_len -= tx_count;
                g_bl_udc.in_ep[ep_idx].actual_xfer_len += tx_count;

                if (g_bl_udc.in_ep[ep_idx].xfer_len == 0) {
                    usbd_event_ep_in_complete_handler(ep_idx | 0x80, g_bl_udc.in_ep[ep_idx].actual_xfer_len);
                } else {
                    tx_count = MIN(g_bl_udc.in_ep[ep_idx].xfer_len, g_bl_udc.in_ep[ep_idx].ep_mps);
                    bflb_usb_mem2fifo(ep_idx, g_bl_udc.in_ep[ep_idx].xfer_buf, tx_count);
                    bflb_usb_ep_set_ready(ep_idx);
                }
            } else {
                while (bflb_usb_ep_isbusy(ep_idx)) {
                }

                rx_count = bflb_usb_get_rxcount(ep_idx);
                bflb_usb_fifo2mem(ep_idx, g_bl_udc.out_ep[ep_idx].xfer_buf, rx_count);

                g_bl_udc.out_ep[ep_idx].xfer_buf += rx_count;
                g_bl_udc.out_ep[ep_idx].xfer_len -= rx_count;
                g_bl_udc.out_ep[ep_idx].actual_xfer_len += rx_count;

                if ((rx_count < g_bl_udc.out_ep[ep_idx].ep_mps) ||
                    (g_bl_udc.out_ep[ep_idx].xfer_len == 0)) {
                    usbd_event_ep_out_complete_handler(ep_idx, g_bl_udc.out_ep[ep_idx].actual_xfer_len);
                } else {
                    bflb_usb_ep_set_ready(ep_idx);
                }
            }
        }
    }

    if (intstatus & USB_EP0_SETUP_DONE_INT) {
        while (bflb_usb_ep_isbusy(0)) {
        }

        rx_count = bflb_usb_get_rxcount(0);
        if (rx_count != 8) {
            printf("setup fail\r\n");
            return;
        }
        bflb_usb_fifo2mem(0, (uint8_t *)&g_bl_udc.setup, 8);
        usbd_event_ep0_setup_complete_handler((uint8_t *)&g_bl_udc.setup);
    }
    if (intstatus & USB_EP0_IN_DONE_INT) {
        tx_count = MIN(g_bl_udc.in_ep[0].xfer_len, g_bl_udc.in_ep[0].ep_mps);
        g_bl_udc.in_ep[0].xfer_buf += tx_count;
        g_bl_udc.in_ep[0].xfer_len -= tx_count;
        g_bl_udc.in_ep[0].actual_xfer_len += tx_count;

        usbd_event_ep_in_complete_handler(0 | 0x80, g_bl_udc.in_ep[0].actual_xfer_len);

        if (g_bl_udc.setup.wLength == 0) {
            /* In status, start reading setup */
            bflb_usb_ep_set_ready(0);
        } else if (g_bl_udc.setup.wLength && ((g_bl_udc.setup.bmRequestType & USB_REQUEST_DIR_MASK) == USB_REQUEST_DIR_OUT)) {
            /* In status, start reading setup */
            bflb_usb_ep_set_ready(0);
        }
    }
    if (intstatus & USB_EP0_OUT_DONE_INT) {
        while (bflb_usb_ep_isbusy(0)) {
        }

        rx_count = bflb_usb_get_rxcount(0);

        bflb_usb_fifo2mem(0, g_bl_udc.out_ep[0].xfer_buf, rx_count);
        g_bl_udc.out_ep[0].xfer_buf += rx_count;
        g_bl_udc.out_ep[0].xfer_len -= rx_count;
        g_bl_udc.out_ep[0].actual_xfer_len += rx_count;

        usbd_event_ep_out_complete_handler(0, g_bl_udc.out_ep[0].actual_xfer_len);

        if (rx_count == 0) {
            /* Out status, start reading setup */
            bflb_usb_ep_set_ready(0);
        }
    }

    if (intstatus & USB_RESET_INT) {
        memset(&g_bl_udc, 0, sizeof(g_bl_udc));

        regval = 0;
        regval |= USB_CR_EP0_SETUP_DONE_EN;
        regval |= USB_CR_EP0_IN_DONE_EN;
        regval |= USB_CR_EP0_OUT_DONE_EN;
        regval |= USB_CR_USB_REND_EN;
        putreg32(regval, BL702_USB_BASE + USB_INT_EN_OFFSET);

        regval = 0xffffffff;
        regval &= ~USB_CR_USB_RESET_MASK;
        regval &= ~USB_CR_EP0_SETUP_DONE_MASK;
        regval &= ~USB_CR_EP0_IN_DONE_MASK;
        regval &= ~USB_CR_EP0_OUT_DONE_MASK;
        regval &= ~USB_CR_USB_REND_MASK;
        putreg32(regval, BL702_USB_BASE + USB_INT_MASK_OFFSET);

        usbd_event_reset_handler();
    }
    if (intstatus & USB_REND_INT) {
        bflb_usb_ep_set_ready(0);
    }
}