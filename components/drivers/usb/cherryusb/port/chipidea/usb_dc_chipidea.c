#include "usbd_core.h"
#include "usb_chipidea_reg.h"

#define USB_OTG_DEV ((CHIPIDEA_TypeDef *)g_usbdev_bus[busid].reg_base)

#define CHIPIDEA_BITSMASK(val, offset) ((uint32_t)(val) << (offset))
#define QTD_COUNT_EACH_ENDPOINT        (8U)

/* ENDPTCTRL */
enum {
    ENDPTCTRL_STALL = CHIPIDEA_BITSMASK(1, 0),
    ENDPTCTRL_TYPE = CHIPIDEA_BITSMASK(3, 2),
    ENDPTCTRL_TOGGLE_INHIBIT = CHIPIDEA_BITSMASK(1, 5),
    ENDPTCTRL_TOGGLE_RESET = CHIPIDEA_BITSMASK(1, 6),
    ENDPTCTRL_ENABLE = CHIPIDEA_BITSMASK(1, 7),
};

/* USBSTS, USBINTR */
enum {
    intr_usb = CHIPIDEA_BITSMASK(1, 0),
    intr_error = CHIPIDEA_BITSMASK(1, 1),
    intr_port_change = CHIPIDEA_BITSMASK(1, 2),
    intr_reset = CHIPIDEA_BITSMASK(1, 6),
    intr_sof = CHIPIDEA_BITSMASK(1, 7),
    intr_suspend = CHIPIDEA_BITSMASK(1, 8),
    intr_nak = CHIPIDEA_BITSMASK(1, 16)
};

/* Queue Transfer Descriptor */
typedef struct {
    /* Word 0: Next QTD Pointer */
    volatile uint32_t next; /* Next link pointer This field contains the physical memory address of the next dTD to be processed */

    /* Word 1: qTQ Token */
    volatile uint32_t                   : 3;
    volatile uint32_t xact_err          : 1;
    volatile uint32_t                   : 1;
    volatile uint32_t buffer_err        : 1;
    volatile uint32_t halted            : 1;
    volatile uint32_t active            : 1;
    volatile uint32_t                   : 2;
    volatile uint32_t iso_mult_override : 2; /* This field can be used for transmit ISOs to override the MULT field in the dQH. This field must be zero for all packet types that are not transmit-ISO. */
    volatile uint32_t                   : 3;
    volatile uint32_t int_on_complete   : 1;
    volatile uint32_t total_bytes       : 15;
    volatile uint32_t                   : 0;

    /* Word 2-6: Buffer Page Pointer List, Each element in the list is a 4K page aligned, physical memory address. The lower 12 bits in each pointer are reserved (except for the first one) as each memory pointer must reference the start of a 4K page */
    volatile uint32_t buffer[5];

    /*------------- DCD Area -------------*/
    volatile uint16_t expected_bytes;
    volatile uint8_t reserved[2];
} dcd_qtd_t;

/* Queue Head */
typedef struct {
    /* Word 0: Capabilities and Characteristics */

    volatile uint32_t                         : 15; /* Number of packets executed per transaction descriptor 00 - Execute N transactions as demonstrated by the USB variable length protocol where N is computed using Max_packet_length and the Total_bytes field in the dTD. 01 - Execute one transaction 10 - Execute two transactions 11 - Execute three transactions Remark: Non-isochronous endpoints must set MULT = 00. Remark: Isochronous endpoints must set MULT = 01, 10, or 11 as needed. */
    volatile uint32_t int_on_setup            : 1;  /* Interrupt on setup This bit is used on control type endpoints to indicate if USBINT is set in response to a setup being received. */
    volatile uint32_t max_packet_size         : 11; /* This directly corresponds to the maximum packet size of the associated endpoint (wMaxPacketSize) */
    volatile uint32_t                         : 2;
    volatile uint32_t zero_length_termination : 1; /* This bit is used for non-isochronous endpoints to indicate when a zero-length packet is received to terminate transfers in case the total transfer length is “multiple”. 0 - Enable zero-length packet to terminate transfers equal to a multiple of Max_packet_length (default). 1 - Disable zero-length packet on transfers that are equal in length to a multiple Max_packet_length. */
    volatile uint32_t iso_mult                : 2;
    volatile uint32_t                         : 0;

    /* Word 1: Current qTD Pointer */
    volatile uint32_t qtd_addr;

    /* Word 2-9: Transfer Overlay */
    volatile dcd_qtd_t qtd_overlay;

    /* Word 10-11: Setup request (control OUT only) */
    volatile struct usb_setup_packet setup_request;

    /*--------------------------------------------------------------------
     * Due to the fact QHD is 64 bytes aligned but occupies only 48 bytes
     * thus there are 16 bytes padding free that we can make use of.
     *--------------------------------------------------------------------
     */
    volatile uint8_t reserved[16];
} dcd_qhd_t;

typedef struct {
    dcd_qhd_t qhd[CONFIG_USBDEV_EP_NUM * 2];
    dcd_qtd_t qtd[CONFIG_USBDEV_EP_NUM * 2 * QTD_COUNT_EACH_ENDPOINT];
} dcd_data_t;

/* Endpoint state */
struct chipidea_ep_state {
    uint16_t ep_mps;    /* Endpoint max packet size */
    uint8_t ep_type;    /* Endpoint type */
    uint8_t ep_stalled; /* Endpoint stall flag */
    uint8_t ep_enable;  /* Endpoint enable */
    uint8_t *xfer_buf;
    uint32_t xfer_len;
    uint32_t actual_xfer_len;
};

/* Driver state */
struct chipidea_udc {
    dcd_data_t *dcd_data;
    bool is_suspend;
    struct chipidea_ep_state in_ep[CONFIG_USBDEV_EP_NUM];  /*!< IN endpoint parameters*/
    struct chipidea_ep_state out_ep[CONFIG_USBDEV_EP_NUM]; /*!< OUT endpoint parameters */
} g_chipidea_udc[CONFIG_USBDEV_MAX_BUS];

static USB_NOCACHE_RAM_SECTION __attribute__((aligned(2048))) dcd_data_t _dcd_data0;
#if CONFIG_USBDEV_MAX_BUS == 2
static USB_NOCACHE_RAM_SECTION __attribute__((aligned(2048))) dcd_data_t _dcd_data1;
#endif

static dcd_data_t *g_dcd_data[CONFIG_USBDEV_MAX_BUS] = {
    &_dcd_data0,
#if CONFIG_USBDEV_MAX_BUS == 2
    &_dcd_data1
#endif
};

/* Index to bit position in register */
static inline uint8_t ep_idx2bit(uint8_t ep_idx)
{
    return ep_idx / 2 + ((ep_idx % 2) ? 16 : 0);
}

static void __chipidea_bus_reset(CHIPIDEA_TypeDef *ptr)
{
    /* The reset value for all endpoint types is the control endpoint. If one endpoint
     * direction is enabled and the paired endpoint of opposite direction is disabled, then the
     * endpoint type of the unused direction must be changed from the control type to any other
     * type (e.g. bulk). Leaving an un-configured endpoint control will cause undefined behavior
     * for the data PID tracking on the active endpoint.
     */

    for (uint32_t i = 1; i < CONFIG_USBDEV_EP_NUM; i++) {
        ptr->ENDPTCTRL[i] = USB_ENDPTCTRL_TXT_SET(USB_ENDPOINT_TYPE_BULK) | USB_ENDPTCTRL_RXT_SET(USB_ENDPOINT_TYPE_BULK);
    }

    /* Clear All Registers */
    ptr->ENDPTNAK = ptr->ENDPTNAK;
    ptr->ENDPTNAKEN = 0;
    ptr->USBSTS = ptr->USBSTS;
    ptr->ENDPTSETUPSTAT = ptr->ENDPTSETUPSTAT;
    ptr->ENDPTCOMPLETE = ptr->ENDPTCOMPLETE;

    while (ptr->ENDPTPRIME) {
    }
    ptr->ENDPTFLUSH = 0xFFFFFFFF;
    while (ptr->ENDPTFLUSH) {
    }
}

static void chipidea_init(CHIPIDEA_TypeDef *ptr)
{
    /* Reset controller */
    ptr->USBCMD |= USB_USBCMD_RST_MASK;
    while (USB_USBCMD_RST_GET(ptr->USBCMD)) {
    }

    /* Set mode to device, must be set immediately after reset */
    ptr->USBMODE &= ~USB_USBMODE_CM_MASK;
    ptr->USBMODE |= USB_USBMODE_CM_SET(2);

    /* Disable setup lockout, please refer to "Control Endpoint Operation" section in RM. */
    ptr->USBMODE &= ~USB_USBMODE_SLOM_MASK;

    /* Set the endian */
    ptr->USBMODE &= ~USB_USBMODE_ES_MASK;

    /* Set parallel interface signal */
    ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;

    /* Set parallel transceiver width */
    ptr->PORTSC1 &= ~USB_PORTSC1_PTW_MASK;

    /* Set usb forced to full speed mode */
    //ptr->PORTSC1 |= USB_PORTSC1_PFSC_MASK;

    /* Not use interrupt threshold. */
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;

    /* Enable VBUS discharge */
    ptr->OTGSC |= USB_OTGSC_VD_MASK;
}

static void chipidea_deinit(CHIPIDEA_TypeDef *ptr)
{
    /* Stop */
    ptr->USBCMD &= ~USB_USBCMD_RS_MASK;

    /* Reset controller */
    ptr->USBCMD |= USB_USBCMD_RST_MASK;
    while (USB_USBCMD_RST_GET(ptr->USBCMD)) {
    }

    /* Reset endpoint list address register */
    ptr->ENDPTLISTADDR = 0;

    /* Reset status register */
    ptr->USBSTS = ptr->USBSTS;

    /* Reset interrupt enable register */
    ptr->USBINTR = 0;
}

/*---------------------------------------------------------------------
 * Endpoint API
 *---------------------------------------------------------------------
 */
static void __chipidea_edpt_open(CHIPIDEA_TypeDef *ptr, uint8_t ep_addr, uint8_t ep_type)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;

    /* Enable EP Control */
    uint32_t temp = ptr->ENDPTCTRL[epnum];
    temp &= ~((0x03 << 2) << (dir ? 16 : 0));
    temp |= ((ep_type << 2) | ENDPTCTRL_ENABLE | ENDPTCTRL_TOGGLE_RESET) << (dir ? 16 : 0);
    ptr->ENDPTCTRL[epnum] = temp;
}

static void chipidea_edpt_xfer(CHIPIDEA_TypeDef *ptr, uint8_t ep_idx)
{
    uint32_t offset = ep_idx / 2 + ((ep_idx % 2) ? 16 : 0);

    /* Start transfer */
    ptr->ENDPTPRIME = 1 << offset;
}

static void chipidea_edpt_stall(CHIPIDEA_TypeDef *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;

    ptr->ENDPTCTRL[epnum] |= ENDPTCTRL_STALL << (dir ? 16 : 0);
}

static void chipidea_edpt_clear_stall(CHIPIDEA_TypeDef *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;

    /* data toggle also need to be reset */
    ptr->ENDPTCTRL[epnum] |= ENDPTCTRL_TOGGLE_RESET << (dir ? 16 : 0);
    ptr->ENDPTCTRL[epnum] &= ~(ENDPTCTRL_STALL << (dir ? 16 : 0));
}

static bool chipidea_edpt_check_stall(CHIPIDEA_TypeDef *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;

    return (ptr->ENDPTCTRL[epnum] & (ENDPTCTRL_STALL << (dir ? 16 : 0))) ? true : false;
}

static void chipidea_edpt_close(CHIPIDEA_TypeDef *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;

    uint32_t primebit = CHIPIDEA_BITSMASK(1, epnum) << (dir ? 16 : 0);

    /* Flush the endpoint to stop a transfer. */
    do {
        /* Set the corresponding bit(s) in the ENDPTFLUSH register */
        ptr->ENDPTFLUSH |= primebit;

        /* Wait until all bits in the ENDPTFLUSH register are cleared. */
        while (0U != (ptr->ENDPTFLUSH & primebit)) {
        }
        /*
         * Read the ENDPTSTAT register to ensure that for all endpoints
         * commanded to be flushed, that the corresponding bits
         * are now cleared.
         */
    } while (0U != (ptr->ENDPTSTAT & primebit));

    /* Disable the endpoint */
    ptr->ENDPTCTRL[epnum] &= ~((ENDPTCTRL_TYPE | ENDPTCTRL_ENABLE | ENDPTCTRL_STALL) << (dir ? 16 : 0));
    ptr->ENDPTCTRL[epnum] |= (USB_ENDPOINT_TYPE_BULK << 2) << (dir ? 16 : 0);
}

/* Initialize qtd */
static void usb_qtd_init(dcd_qtd_t *p_qtd, void *data_ptr, uint16_t total_bytes)
{
    memset(p_qtd, 0, sizeof(dcd_qtd_t));

    p_qtd->next = 1;
    p_qtd->active = 1;
    p_qtd->total_bytes = p_qtd->expected_bytes = total_bytes;

    if (data_ptr != NULL) {
        p_qtd->buffer[0] = (uint32_t)data_ptr;
        for (uint8_t i = 1; i < 5; i++) {
            p_qtd->buffer[i] |= ((p_qtd->buffer[i - 1]) & 0xFFFFF000UL) + 4096U;
        }
    }
}

static dcd_qhd_t *chipidea_qhd_get(uint8_t busid, uint8_t ep_idx)
{
    dcd_data_t *dcd_data;

    dcd_data = g_chipidea_udc[busid].dcd_data;
    return &dcd_data->qhd[ep_idx];
}

static dcd_qtd_t *chipidea_qtd_get(uint8_t busid, uint8_t ep_idx)
{
    dcd_data_t *dcd_data;

    dcd_data = g_chipidea_udc[busid].dcd_data;
    return &dcd_data->qtd[ep_idx * QTD_COUNT_EACH_ENDPOINT];
}

static void chipidea_bus_reset(uint8_t busid, uint16_t ep0_max_packet_size)
{
    dcd_data_t *dcd_data;

    dcd_data = g_chipidea_udc[busid].dcd_data;
    __chipidea_bus_reset(USB_OTG_DEV);

    /* Queue Head & Queue TD */
    memset(dcd_data, 0, sizeof(dcd_data_t));

    /* Set up Control Endpoints (0 OUT, 1 IN) */
    dcd_data->qhd[0].zero_length_termination = dcd_data->qhd[1].zero_length_termination = 1;
    dcd_data->qhd[0].max_packet_size = dcd_data->qhd[1].max_packet_size = ep0_max_packet_size;
    dcd_data->qhd[0].qtd_overlay.next = dcd_data->qhd[1].qtd_overlay.next = 1;

    /* OUT only */
    dcd_data->qhd[0].int_on_setup = 1;
}

static void chipidea_edpt_open(uint8_t busid, uint8_t ep_addr, uint8_t ep_type, uint16_t ep_mps)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;
    uint8_t const ep_idx = 2 * epnum + dir;
    dcd_data_t *dcd_data;
    dcd_qhd_t *p_qhd;

    /* Prepare Queue Head */
    dcd_data = g_chipidea_udc[busid].dcd_data;
    p_qhd = &dcd_data->qhd[ep_idx];
    memset(p_qhd, 0, sizeof(dcd_qhd_t));

    p_qhd->zero_length_termination = 1;
    p_qhd->max_packet_size = ep_mps & 0x7FFu;
    p_qhd->qtd_overlay.next = 1;
    if (ep_type == USB_ENDPOINT_TYPE_ISOCHRONOUS) {
        p_qhd->iso_mult = ((ep_mps >> 11u) & 0x3u) + 1u;
    }

    __chipidea_edpt_open(USB_OTG_DEV, ep_addr, ep_type);
}

static bool chipidea_start_xfer(uint8_t busid, uint8_t ep_addr, uint8_t *buffer, uint32_t total_bytes)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;
    uint8_t const ep_idx = 2 * epnum + dir;
    uint8_t qtd_num;
    uint8_t i;
    uint32_t xfer_len;
    dcd_qhd_t *p_qhd;
    dcd_qtd_t *p_qtd;
    dcd_qtd_t *first_p_qtd = NULL;
    dcd_qtd_t *prev_p_qtd = NULL;
    dcd_data_t *dcd_data;

    dcd_data = g_chipidea_udc[busid].dcd_data;

    if (epnum == 0) {
        /* follows UM Setup packet handling using setup lockout mechanism
         * wait until ENDPTSETUPSTAT before priming data/status in response TODO add time out
         */
        while (USB_OTG_DEV->ENDPTSETUPSTAT & CHIPIDEA_BITSMASK(1, 0)) {
        }
    }

    qtd_num = (total_bytes + 0x3fff) / 0x4000;
    if (qtd_num > QTD_COUNT_EACH_ENDPOINT) {
        return false;
    }

    if (buffer != NULL) {
        buffer = (uint8_t *)buffer;
    }
    p_qhd = &dcd_data->qhd[ep_idx];
    i = 0;
    do {
        p_qtd = &dcd_data->qtd[ep_idx * QTD_COUNT_EACH_ENDPOINT + i];
        i++;

        if (total_bytes > 0x4000) {
            xfer_len = 0x4000;
            total_bytes -= 0x4000;
        } else {
            xfer_len = total_bytes;
            total_bytes = 0;
        }

        usb_qtd_init(p_qtd, (void *)buffer, xfer_len);
        if (total_bytes == 0) {
            p_qtd->int_on_complete = true;
        }
        buffer += xfer_len;

        if (prev_p_qtd) {
            prev_p_qtd->next = (uint32_t)p_qtd;
        } else {
            first_p_qtd = p_qtd;
        }
        prev_p_qtd = p_qtd;
    } while (total_bytes > 0);

    p_qhd->qtd_overlay.next = (uint32_t)first_p_qtd; /* link qtd to qhd */

    chipidea_edpt_xfer(USB_OTG_DEV, ep_idx);

    return true;
}

__WEAK void usb_dc_low_level_init(uint8_t busid)
{
}

__WEAK void usb_dc_low_level_deinit(uint8_t busid)
{
}

int usb_dc_init(uint8_t busid)
{
    uint32_t int_mask;
    int_mask = (USB_USBINTR_UE_MASK | USB_USBINTR_UEE_MASK | USB_USBINTR_SLE_MASK |
                USB_USBINTR_PCE_MASK | USB_USBINTR_URE_MASK);

    usb_dc_low_level_init(busid);

    memset(&g_chipidea_udc[busid], 0, sizeof(struct chipidea_udc));
    g_chipidea_udc[busid].dcd_data = g_dcd_data[busid];
    memset(g_chipidea_udc[busid].dcd_data, 0, sizeof(dcd_data_t));

    chipidea_init(USB_OTG_DEV);

    /* Set endpoint list address */
    USB_OTG_DEV->ENDPTLISTADDR = ((uint32_t)g_chipidea_udc[busid].dcd_data->qhd) & USB_ENDPTLISTADDR_EPBASE_MASK;

    /* Clear status */
    USB_OTG_DEV->USBSTS = USB_OTG_DEV->USBSTS;

    /* Enable interrupt mask */
    USB_OTG_DEV->USBINTR |= int_mask;

    /* Connect by enabling internal pull-up resistor on D+/D- */
    USB_OTG_DEV->USBCMD |= USB_USBCMD_RS_MASK;
    return 0;
}

int usb_dc_deinit(uint8_t busid)
{
    chipidea_deinit(USB_OTG_DEV);

    for (uint32_t i = 0; i < CONFIG_USBDEV_EP_NUM; i++) {
        chipidea_edpt_close(USB_OTG_DEV, (i | 0x80));
        chipidea_edpt_close(USB_OTG_DEV, (i | 0x00));
    }

    usb_dc_low_level_deinit(busid);
    return 0;
}

int usbd_set_address(uint8_t busid, const uint8_t addr)
{
    USB_OTG_DEV->DEVICEADDR = USB_DEVICEADDR_USBADR_SET(addr) | USB_DEVICEADDR_USBADRA_MASK;
    return 0;
}

int usbd_set_remote_wakeup(uint8_t busid)
{
    if (!USB_PORTSC1_SUSP_GET(USB_OTG_DEV->PORTSC1)) {
        return -1;
    }

    USB_OTG_DEV->PORTSC1 |= USB_PORTSC1_FPR_MASK;
    while (USB_OTG_DEV->PORTSC1 & USB_PORTSC1_FPR_MASK) {
    }

    return 0;
}

uint8_t usbd_get_port_speed(uint8_t busid)
{
    uint8_t speed;

    speed = USB_PORTSC1_PSPD_GET(USB_OTG_DEV->PORTSC1);

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
    uint8_t ep_idx = USB_EP_GET_IDX(ep->bEndpointAddress);

    /* Must not exceed max endpoint number */
    if (ep_idx >= CONFIG_USBDEV_EP_NUM) {
        return -1;
    }

    chipidea_edpt_open(busid, ep->bEndpointAddress, USB_GET_ENDPOINT_TYPE(ep->bmAttributes), ep->wMaxPacketSize);

    if (USB_EP_DIR_IS_OUT(ep->bEndpointAddress)) {
        g_chipidea_udc[busid].out_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_chipidea_udc[busid].out_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_chipidea_udc[busid].out_ep[ep_idx].ep_enable = true;
    } else {
        g_chipidea_udc[busid].in_ep[ep_idx].ep_mps = USB_GET_MAXPACKETSIZE(ep->wMaxPacketSize);
        g_chipidea_udc[busid].in_ep[ep_idx].ep_type = USB_GET_ENDPOINT_TYPE(ep->bmAttributes);
        g_chipidea_udc[busid].in_ep[ep_idx].ep_enable = true;
    }

    return 0;
}

int usbd_ep_close(uint8_t busid, const uint8_t ep)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (USB_EP_DIR_IS_OUT(ep)) {
        g_chipidea_udc[busid].out_ep[ep_idx].ep_enable = false;
    } else {
        g_chipidea_udc[busid].in_ep[ep_idx].ep_enable = false;
    }

    chipidea_edpt_close(USB_OTG_DEV, ep);

    return 0;
}

int usbd_ep_set_stall(uint8_t busid, const uint8_t ep)
{
    chipidea_edpt_stall(USB_OTG_DEV, ep);
    return 0;
}

int usbd_ep_clear_stall(uint8_t busid, const uint8_t ep)
{
    chipidea_edpt_clear_stall(USB_OTG_DEV, ep);
    return 0;
}

int usbd_ep_is_stalled(uint8_t busid, const uint8_t ep, uint8_t *stalled)
{
    *stalled = chipidea_edpt_check_stall(USB_OTG_DEV, ep);
    return 0;
}

int usbd_ep_start_write(uint8_t busid, const uint8_t ep, const uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_chipidea_udc[busid].in_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_chipidea_udc[busid].in_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_chipidea_udc[busid].in_ep[ep_idx].xfer_len = data_len;
    g_chipidea_udc[busid].in_ep[ep_idx].actual_xfer_len = 0;

    chipidea_start_xfer(busid, ep, (uint8_t *)data, data_len);

    return 0;
}

int usbd_ep_start_read(uint8_t busid, const uint8_t ep, uint8_t *data, uint32_t data_len)
{
    uint8_t ep_idx = USB_EP_GET_IDX(ep);

    if (!data && data_len) {
        return -1;
    }
    if (!g_chipidea_udc[busid].out_ep[ep_idx].ep_enable) {
        return -2;
    }

    g_chipidea_udc[busid].out_ep[ep_idx].xfer_buf = (uint8_t *)data;
    g_chipidea_udc[busid].out_ep[ep_idx].xfer_len = data_len;
    g_chipidea_udc[busid].out_ep[ep_idx].actual_xfer_len = 0;

    chipidea_start_xfer(busid, ep, data, data_len);

    return 0;
}

void USBD_IRQHandler(uint8_t busid)
{
    uint32_t int_status;
    uint32_t transfer_len;
    bool ep_cb_req;

    /* Acknowledge handled interrupt */
    int_status = USB_OTG_DEV->USBSTS;
    int_status &= USB_OTG_DEV->USBINTR;
    USB_OTG_DEV->USBSTS = int_status;

    if (int_status & intr_error) {
        USB_LOG_ERR("usbd intr error!\r\n");
    }

    if (int_status & intr_reset) {
        g_chipidea_udc[busid].is_suspend = false;
        memset(g_chipidea_udc[busid].in_ep, 0, sizeof(struct chipidea_ep_state) * CONFIG_USBDEV_EP_NUM);
        memset(g_chipidea_udc[busid].out_ep, 0, sizeof(struct chipidea_ep_state) * CONFIG_USBDEV_EP_NUM);
        usbd_event_reset_handler(busid);
        chipidea_bus_reset(busid, 64);
    }

    if (int_status & intr_suspend) {
        if (USB_PORTSC1_SUSP_GET(USB_OTG_DEV->PORTSC1)) {
            /* Note: Host may delay more than 3 ms before and/or after bus reset before doing enumeration. */
            if (USB_DEVICEADDR_USBADR_GET(USB_OTG_DEV->DEVICEADDR)) {
                g_chipidea_udc[busid].is_suspend = true;
                usbd_event_suspend_handler(busid);
            }
        } else {
        }
    }

    if (int_status & intr_port_change) {
        if (!USB_PORTSC1_CCS_GET(USB_OTG_DEV->PORTSC1)) {
            usbd_event_disconnect_handler(busid);
        } else {
            if (g_chipidea_udc[busid].is_suspend) {
                g_chipidea_udc[busid].is_suspend = false;
                usbd_event_resume_handler(busid);
            }
            usbd_event_connect_handler(busid);
        }
    }

    if (int_status & intr_usb) {
        uint32_t const edpt_complete = USB_OTG_DEV->ENDPTCOMPLETE;
        USB_OTG_DEV->ENDPTCOMPLETE = edpt_complete;
        uint32_t edpt_setup_status = USB_OTG_DEV->ENDPTSETUPSTAT;

        if (edpt_setup_status) {
            /*------------- Set up Received -------------*/
            USB_OTG_DEV->ENDPTSETUPSTAT = edpt_setup_status;
            dcd_qhd_t *qhd0 = chipidea_qhd_get(busid, 0);
            usbd_event_ep0_setup_complete_handler(busid, (uint8_t *)&qhd0->setup_request);
        }

        if (edpt_complete) {
            for (uint8_t ep_idx = 0; ep_idx < (CONFIG_USBDEV_EP_NUM * 2); ep_idx++) {
                if (edpt_complete & (1 << ep_idx2bit(ep_idx))) {
                    transfer_len = 0;
                    ep_cb_req = true;

                    /* Failed QTD also get ENDPTCOMPLETE set */
                    dcd_qtd_t *p_qtd = chipidea_qtd_get(busid, ep_idx);
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

                        if (p_qtd->next == 1) {
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