/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/*---------------------------------------------------------------------
 * Include
 *---------------------------------------------------------------------
 */
#include "hpm_usb_drv.h"
#include "hpm_misc.h"
#include "hpm_soc_feature.h"
#include "hpm_common.h"
/*---------------------------------------------------------------------
 * Macro Enum Declaration
 *---------------------------------------------------------------------
 */

/* ENDPTCTRL */
enum {
    ENDPTCTRL_STALL          = HPM_BITSMASK(1, 0),
    ENDPTCTRL_TYPE           = HPM_BITSMASK(3, 2),
    ENDPTCTRL_TOGGLE_INHIBIT = HPM_BITSMASK(1, 5),
    ENDPTCTRL_TOGGLE_RESET   = HPM_BITSMASK(1, 6),
    ENDPTCTRL_ENABLE         = HPM_BITSMASK(1, 7),
};

/*---------------------------------------------------------------------
 * Internal API
 *---------------------------------------------------------------------
 */

/* De-initialize USB phy */
static void usb_phy_deinit(USB_Type *ptr)
{
    ptr->OTG_CTRL0 |= USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_MASK;     /* set otg_utmi_suspend_m for naneng usbphy */

    ptr->OTG_CTRL0 &= ~USB_OTG_CTRL0_OTG_UTMI_RESET_SW_MASK;       /* clear otg_utmi_reset_sw for naneng usbphy */

    ptr->PHY_CTRL1 &= ~USB_PHY_CTRL1_UTMI_CFG_RST_N_MASK;          /* clear cfg_rst_n */

    ptr->PHY_CTRL1 &= ~USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_MASK;       /* clear otg_suspendm */
}

static uint8_t usb_phy_get_line_state(USB_Type *ptr)
{
    return USB_PHY_STATUS_LINE_STATE_GET(ptr->PHY_STATUS);
}

/*---------------------------------------------------------------------
 * Driver API
 *---------------------------------------------------------------------
 */
/* Initialize USB phy */
void usb_phy_init(USB_Type *ptr)
{
    uint32_t status;

    ptr->OTG_CTRL0 |= USB_OTG_CTRL0_OTG_UTMI_RESET_SW_MASK;           /* set otg_utmi_reset_sw for naneng usbphy */
    ptr->OTG_CTRL0 &= ~USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_MASK;       /* clr otg_utmi_suspend_m for naneng usbphy */
    ptr->PHY_CTRL1 &= ~USB_PHY_CTRL1_UTMI_CFG_RST_N_MASK;             /* clr cfg_rst_n */

    do {
        status = USB_OTG_CTRL0_OTG_UTMI_RESET_SW_GET(ptr->OTG_CTRL0); /* wait for reset status */
    } while (status == 0);

    ptr->OTG_CTRL0 |= USB_OTG_CTRL0_OTG_UTMI_SUSPENDM_SW_MASK;        /* set otg_utmi_suspend_m for naneng usbphy */

    for (int i = 0; i < USB_PHY_INIT_DELAY_COUNT; i++) {
        ptr->PHY_CTRL0 = USB_PHY_CTRL0_GPIO_ID_SEL_N_SET(0);          /* used for delay */
    }

    ptr->OTG_CTRL0 &= ~USB_OTG_CTRL0_OTG_UTMI_RESET_SW_MASK;          /* clear otg_utmi_reset_sw for naneng usbphy */

    /* otg utmi clock detection */
    ptr->PHY_STATUS |= USB_PHY_STATUS_UTMI_CLK_VALID_MASK;            /* write 1 to clear valid status */
    do {
        status = USB_PHY_STATUS_UTMI_CLK_VALID_GET(ptr->PHY_STATUS);  /* get utmi clock status */
    } while (status == 0);

    ptr->PHY_CTRL1 |= USB_PHY_CTRL1_UTMI_CFG_RST_N_MASK;              /* set cfg_rst_n */

    ptr->PHY_CTRL1 |= USB_PHY_CTRL1_UTMI_OTG_SUSPENDM_MASK;           /* set otg_suspendm */
}

void usb_dcd_bus_reset(USB_Type *ptr, uint16_t ep0_max_packet_size)
{
    /* The reset value for all endpoint types is the control endpoint. If one endpoint
     * direction is enabled and the paired endpoint of opposite direction is disabled, then the
     * endpoint type of the unused direction must be changed from the control type to any other
     * type (e.g. bulk). Leaving an un-configured endpoint control will cause undefined behavior
     * for the data PID tracking on the active endpoint.
     */

    for (int i = 1; i < USB_SOC_DCD_MAX_ENDPOINT_COUNT; i++) {
        ptr->ENDPTCTRL[i] = USB_ENDPTCTRL_TXT_SET(usb_xfer_bulk) | USB_ENDPTCTRL_RXT_SET(usb_xfer_bulk);
    }

    /* Clear All Registers */
    ptr->ENDPTNAK       = ptr->ENDPTNAK;
    ptr->ENDPTNAKEN     = 0;
    ptr->USBSTS         = ptr->USBSTS;
    ptr->ENDPTSETUPSTAT = ptr->ENDPTSETUPSTAT;
    ptr->ENDPTCOMPLETE  = ptr->ENDPTCOMPLETE;

    while (ptr->ENDPTPRIME) {
    }
    ptr->ENDPTFLUSH = 0xFFFFFFFF;
    while (ptr->ENDPTFLUSH) {
    }
}

void usb_dcd_init(USB_Type *ptr)
{
    /* Initialize USB phy */
    usb_phy_init(ptr);

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

    /* TODO Force fullspeed on non-highspeed port */
    /* ptr->PORTSC1 |= USB_PORTSC1_PFSC_MASK; */

    /* Set parallel interface signal */
    ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;

    /* Set parallel transceiver width */
    ptr->PORTSC1 &= ~USB_PORTSC1_PTW_MASK;

#ifdef CONFIG_USB_DEVICE_FS
    /* Set usb forced to full speed mode */
    ptr->PORTSC1 |= USB_PORTSC1_PFSC_MASK;
#endif

    /* Not use interrupt threshold. */
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;

    /* Enable VBUS discharge */
    ptr->OTGSC |= USB_OTGSC_VD_MASK;
}

void usb_dcd_deinit(USB_Type *ptr)
{
    /* Stop */
    ptr->USBCMD &= ~USB_USBCMD_RS_MASK;

    /* Reset controller */
    ptr->USBCMD |= USB_USBCMD_RST_MASK;
    while (USB_USBCMD_RST_GET(ptr->USBCMD)) {
    }

    /* De-initialize USB phy */
    usb_phy_deinit(ptr);

    /* Reset endpoint list address register */
    ptr->ENDPTLISTADDR = 0;

    /* Reset status register */
    ptr->USBSTS = ptr->USBSTS;

    /* Reset interrupt enable register */
    ptr->USBINTR = 0;
}

/* Connect by enabling internal pull-up resistor on D+/D- */
void usb_dcd_connect(USB_Type *ptr)
{
    ptr->USBCMD |= USB_USBCMD_RS_MASK;
}

/* Disconnect by disabling internal pull-up resistor on D+/D- */
void usb_dcd_disconnect(USB_Type *ptr)
{
    /* Stop */
    ptr->USBCMD &= ~USB_USBCMD_RS_MASK;

    /* Pullup DP to make the phy switch into full speed mode */
    ptr->USBCMD |= USB_USBCMD_RS_MASK;

    /* Clear the sof flag */
    ptr->USBSTS |= USB_USBSTS_SRI_MASK;

    /* Wait a SOF (It will not be a dead loop even usb cable is not connected.) */
    while (USB_USBSTS_SRI_GET(ptr->USBSTS) == 0) {
    }

    /* Disconnect */
    ptr->USBCMD &= ~USB_USBCMD_RS_MASK;
}

/*---------------------------------------------------------------------
 * Endpoint API
 *---------------------------------------------------------------------
 */
void usb_dcd_edpt_open(USB_Type *ptr, usb_endpoint_config_t *config)
{
    uint8_t const epnum  = config->ep_addr & 0x0f;
    uint8_t const dir = (config->ep_addr & 0x80) >> 7;

    /* Enable EP Control */
    uint32_t temp = ptr->ENDPTCTRL[epnum];
    temp &= ~((0x03 << 2) << (dir ? 16 : 0));
    temp |= ((config->xfer << 2) | ENDPTCTRL_ENABLE | ENDPTCTRL_TOGGLE_RESET) << (dir ? 16 : 0);
    ptr->ENDPTCTRL[epnum] = temp;
}

uint8_t usb_dcd_edpt_get_type(USB_Type *ptr, uint8_t ep_addr)
{
    uint8_t const epnum  = ep_addr & 0x0f;
    uint8_t const dir = (ep_addr & 0x80) >> 7;
    uint32_t temp =  ptr->ENDPTCTRL[epnum];

    return dir ?  USB_ENDPTCTRL_TXT_GET(temp) : USB_ENDPTCTRL_RXT_GET(temp);
}

void usb_dcd_edpt_xfer(USB_Type *ptr, uint8_t ep_idx)
{
    uint32_t offset = ep_idx / 2 + ((ep_idx % 2) ? 16 : 0);

    /* Start transfer */
    ptr->ENDPTPRIME = 1 << offset;
}

void usb_dcd_edpt_stall(USB_Type *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir   = (ep_addr & 0x80) >> 7;

    ptr->ENDPTCTRL[epnum] |= ENDPTCTRL_STALL << (dir ? 16 : 0);
}

void usb_dcd_edpt_clear_stall(USB_Type *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir   = (ep_addr & 0x80) >> 7;

    /* data toggle also need to be reset */
    ptr->ENDPTCTRL[epnum] |= ENDPTCTRL_TOGGLE_RESET << (dir ? 16 : 0);
    ptr->ENDPTCTRL[epnum] &= ~(ENDPTCTRL_STALL << (dir  ? 16 : 0));
}

void usb_dcd_edpt_close(USB_Type *ptr, uint8_t ep_addr)
{
    uint8_t const epnum = ep_addr & 0x0f;
    uint8_t const dir   = (ep_addr & 0x80) >> 7;

    uint32_t primebit = HPM_BITSMASK(1, epnum) << (dir ? 16 : 0);

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
    ptr->ENDPTCTRL[epnum] |= (usb_xfer_bulk << 2) << (dir ? 16 : 0);
}

void usb_dcd_remote_wakeup(USB_Type *ptr)
{
    (void) ptr;
}

bool usb_hcd_init(USB_Type *ptr, uint32_t int_mask, uint16_t framelist_size)
{
    uint8_t framelist_size_bf = 0;

    if (framelist_size > USB_SOC_HCD_FRAMELIST_MAX_ELEMENTS || framelist_size == 0) {
        return false;
    }

    framelist_size_bf = 10 - get_first_set_bit_from_lsb(framelist_size);

    if (framelist_size != (1 << get_first_set_bit_from_lsb(framelist_size))) {
        return false;
    }

    usb_phy_init(ptr);

    /* Reset controller */
    ptr->USBCMD |= USB_USBCMD_RST_MASK;
    while (USB_USBCMD_RST_GET(ptr->USBCMD)) {
    }

    /* Set mode to host, must be set immediately after reset */
    ptr->USBMODE &= ~USB_USBMODE_CM_MASK;
    ptr->USBMODE |= USB_USBMODE_CM_SET(usb_ctrl_mode_host);

    /* Set the endian */
    ptr->USBMODE &= ~USB_USBMODE_ES_MASK;

    /* Set parallel interface signal */
    ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;

    /* Set parallel transceiver width */
    ptr->PORTSC1 &= ~USB_PORTSC1_PTW_MASK;

    /* Not use interrupt threshold. */
    ptr->USBCMD &= ~USB_USBCMD_ITC_MASK;

    /* USB INT Register */
    ptr->USBSTS = ptr->USBSTS;
    ptr->USBINTR |= int_mask;

    /* USB CMD Register */
    ptr->USBCMD = USB_USBCMD_ASE_MASK | USB_USBCMD_PSE_MASK
                | USB_USBCMD_FS_2_SET(framelist_size_bf >> 2)
                | USB_USBCMD_FS_1_SET(framelist_size_bf);

    return true;
}

void usb_hcd_port_reset(USB_Type *ptr)
{
    if (usb_phy_get_line_state(ptr) == usb_line_state2) {
        ptr->PORTSC1 |= USB_PORTSC1_STS_MASK;
    } else {
        ptr->PORTSC1 &= ~USB_PORTSC1_STS_MASK;
    }

    ptr->PORTSC1 &= ~USB_PORTSC1_PE_MASK;
    ptr->PORTSC1 |=  USB_PORTSC1_PR_MASK;

    /* wait until port reset sequence is completed */
    while (USB_PORTSC1_PR_GET(ptr->PORTSC1)) {
    }
}
