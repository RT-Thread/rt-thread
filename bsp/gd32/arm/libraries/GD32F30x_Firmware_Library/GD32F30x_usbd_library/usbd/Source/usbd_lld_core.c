/*!
    \file    usbd_lld_core.c
    \brief   USB device low level driver core

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "usbd_lld_core.h"
#include "usbd_enum.h"

#define USB_EPTYPE_MASK           0x03U

#if defined (__CC_ARM)         /* ARM Compiler */
static usbd_ep_ram btable_ep[EP_COUNT]__attribute__((at(USBD_RAM + 2 * (BTABLE_OFFSET & 0xFFF8))));
#elif defined (__ICCARM__)     /* IAR Compiler */
    __no_init usbd_ep_ram btable_ep[EP_COUNT] @(USBD_RAM + 2 * (BTABLE_OFFSET & 0xFFF8));
#elif defined (__GNUC__)       /* GNU GCC Compiler  */
    usbd_ep_ram *btable_ep = (usbd_ep_ram *)(USBD_RAM + 2 * (BTABLE_OFFSET & 0xFFF8));
#endif

usb_core_drv usbd_core;

static const uint32_t ep_type[] = {
    [USB_EP_ATTR_CTL]  = EP_CONTROL,
    [USB_EP_ATTR_BULK] = EP_BULK,
    [USB_EP_ATTR_INT]  = EP_INTERRUPT,
    [USB_EP_ATTR_ISO]  = EP_ISO
};

/* local function prototypes ('static') */
static void usbd_dp_pullup (FlagStatus status);
static void usbd_core_reset (void);
static void usbd_core_stop (void);
static void usbd_address_set (usb_dev *udev);
static void usbd_ep_reset (usb_dev *udev);
static void usbd_ep_setup (usb_dev *udev, uint8_t buf_kind, uint32_t buf_addr, const usb_desc_ep *ep_desc);
static void usbd_ep_rx_enable (usb_dev *udev, uint8_t ep_addr);
static void usbd_ep_disable (usb_dev *udev, uint8_t ep_addr);
static void usbd_ep_stall_set (usb_dev *udev, uint8_t ep_addr);
static void usbd_ep_stall_clear (usb_dev *udev, uint8_t ep_addr);
static void usbd_ep_data_write (uint8_t *user_fifo, uint8_t ep_num, uint16_t bytes);
static uint16_t usbd_ep_data_read (uint8_t *user_fifo, uint8_t ep_num, uint8_t buf_kind);
static void usbd_resume (usb_dev *udev);
static void usbd_suspend (void);
static void usbd_leave_suspend (void);
static uint8_t usbd_ep_status (usb_dev *udev, uint8_t ep_addr);

struct _usb_handler usbd_drv_handler = {
    .dp_pullup      = usbd_dp_pullup,
    .init           = usbd_core_reset,
    .deinit         = usbd_core_stop,
    .suspend        = usbd_suspend,
    .suspend_leave  = usbd_leave_suspend,
    .resume         = usbd_resume,
    .set_addr       = usbd_address_set,
    .ep_reset       = usbd_ep_reset,
    .ep_disable     = usbd_ep_disable,
    .ep_setup       = usbd_ep_setup,
    .ep_rx_enable   = usbd_ep_rx_enable,
    .ep_write       = usbd_ep_data_write,
    .ep_read        = usbd_ep_data_read,
    .ep_stall_set   = usbd_ep_stall_set,
    .ep_stall_clear = usbd_ep_stall_clear,
    .ep_status_get  = usbd_ep_status
};

/*!
    \brief      free buffer used from application by toggling the SW_BUF byte
    \param[in]  ep_num: endpoint identifier (0..7)
    \param[in]  dir: endpoint direction which can be OUT(0) or IN(1)
    \param[out] none
    \retval     None
*/
void user_buffer_free (uint8_t ep_num, uint8_t dir)
{
    if ((uint8_t)DBUF_EP_OUT == dir) {
        USBD_TX_DTG_TOGGLE(ep_num);
    } else if ((uint8_t)DBUF_EP_IN == dir) {
        USBD_RX_DTG_TOGGLE(ep_num);
    } else {
        /* no operation */
    }
}

/*!
    \brief      set the status of pull-up pin
    \param[in]  status: SET or RESET
    \param[out] none
    \retval     none
*/
static void usbd_dp_pullup (FlagStatus status)
{
    if (SET == status) {
        gpio_bit_set(USB_PULLUP, USB_PULLUP_PIN);
    } else {
        gpio_bit_reset(USB_PULLUP, USB_PULLUP_PIN);
    }
}

/*!
    \brief      device core register initialization
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void usbd_core_reset (void)
{
    /* reset the CLOSE bit */
    USBD_CTL = CTL_SETRST;

    /* may be need wait some time(tSTARTUP) */

    /* clear SETRST bit in USBD_CTL register */
    USBD_CTL = 0U;

    /* clear all pending interrupts */
    USBD_INTF = 0U;

    /* set descriptors table offset in USB dedicated SRAM */
    USBD_BADDR = BTABLE_OFFSET & 0xFFF8U;

#ifdef LPM_ENABLED
    /* enable L1REQ interrupt */
    USBD_CTL = CTL_L1REQIE;

    USBD_LPMCS = LPMCS_LPMACK | LPMCS_LPMEN;
#endif /* LPM_ENABLED */

    /* enable all interrupts mask bits */
    USBD_CTL |= CTL_STIE | CTL_WKUPIE | CTL_SPSIE | CTL_SOFIE | CTL_ESOFIE | CTL_RSTIE;
}

/*!
    \brief      device core register configure when stop device
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void usbd_core_stop (void)
{
    /* disable all interrupts and set USB reset */
    USBD_CTL = CTL_SETRST;

    /* clear all interrupt flags */
    USBD_INTF = 0U;

    /* close device */
    USBD_CTL = CTL_SETRST | CTL_CLOSE;
}

/*!
    \brief      set device address
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void usbd_address_set (usb_dev *udev)
{
    USBD_DADDR = DADDR_USBEN | udev->dev_addr;
}

/*!
    \brief      handle USB reset event
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static void usbd_ep_reset (usb_dev *udev)
{
    uint8_t i = 0U;

    usb_transc *transc = &udev->transc_in[0];

    btable_ep[0].tx_addr = EP0_TX_ADDR;
    btable_ep[0].tx_count = 0U;

    transc->max_len = USBD_EP0_MAX_SIZE;

    transc = &udev->transc_out[0];

    btable_ep[0].rx_addr = EP0_RX_ADDR;

    transc->max_len = USBD_EP0_MAX_SIZE;

    if (transc->max_len > 62U) {
        btable_ep[0].rx_count = ((uint16_t)((uint16_t)transc->max_len << 5) - 1U) | 0x8000U;
    } else {
        btable_ep[0].rx_count = ((transc->max_len + 1U) & ~1U) << 9U;
    }

    /* reset non-control endpoints */
    for (i = 1U; i < EP_COUNT; i++) {
        USBD_EPxCS(i) = (USBD_EPxCS(i) & EPCS_MASK) | i;
    }

    /* clear endpoint 0 register */
    USBD_EPxCS(0U)= (uint16_t)(USBD_EPxCS(0U));

    USBD_EPxCS(0U) = EP_CONTROL | EPRX_VALID | EPTX_NAK;

    /* set device address as default address 0 */
    USBD_DADDR = DADDR_USBEN;

    udev->cur_status = (uint8_t)USBD_DEFAULT;
}

/*!
    \brief      endpoint initialization
    \param[in]  udev: pointer to USB core instance
    \param[in]  buf_kind: endpoint buffer kind
    \param[in]  buf_addr: endpoint buffer address
    \param[in]  ep_desc: pointer to endpoint descriptor
    \param[out] none
    \retval     none
*/
static void usbd_ep_setup (usb_dev *udev, uint8_t buf_kind, uint32_t buf_addr, const usb_desc_ep *ep_desc)
{
    uint8_t ep_addr = ep_desc->bEndpointAddress;
    uint8_t ep_num = EP_ID(ep_addr);
    uint16_t max_len = ep_desc->wMaxPacketSize;

    usb_transc *transc = NULL;

    /* set the endpoint type */
    USBD_EPxCS(ep_num) = ep_type[ep_desc->bmAttributes & USB_EPTYPE_MASK] | ep_num;

    if (EP_DIR(ep_addr)) {
        transc = &udev->transc_in[ep_num];

        transc->max_len = (uint8_t)max_len;

        if ((uint8_t)EP_BUF_SNG == buf_kind) {
            btable_ep[ep_num].tx_addr = buf_addr;

            /* configure the endpoint status as NAK status */
            USBD_EP_TX_STAT_SET(ep_num, EPTX_NAK);
        } else if ((uint8_t)EP_BUF_DBL == buf_kind) {
            USBD_EP_DBL_BUF_SET(ep_num);

            btable_ep[ep_num].tx_addr = buf_addr & 0xFFFFU;
            btable_ep[ep_num].rx_addr = (buf_addr & 0xFFFF0000U) >> 16U;

            USBD_EP_TX_STAT_SET(ep_num, EPTX_VALID);
            USBD_EP_RX_STAT_SET(ep_num, EPRX_DISABLED);
        } else {
            /* error operation */
        }
    } else {
        transc = &udev->transc_out[ep_num];

        transc->max_len = (uint8_t)max_len;

        if ((uint8_t)EP_BUF_SNG == buf_kind) {
            btable_ep[ep_num].rx_addr = buf_addr;
        } else if ((uint8_t)EP_BUF_DBL == buf_kind) {
            USBD_EP_DBL_BUF_SET(ep_num);

            USBD_TX_DTG_TOGGLE(ep_num);

            btable_ep[ep_num].tx_addr = buf_addr & 0xFFFFU;
            btable_ep[ep_num].rx_addr = (buf_addr & 0xFFFF0000U) >> 16U;

            if (max_len > 62U) {
                btable_ep[ep_num].tx_count = (((uint32_t)max_len << 5) - 1U) | 0x8000U;
            } else {
                btable_ep[ep_num].tx_count = ((max_len + 1U) & ~1U) << 9U;
            }
        } else {
            /* error operation */
        }

        if (max_len > 62U) {
            btable_ep[ep_num].rx_count = (((uint32_t)max_len << 5U) - 1U) | 0x8000U;
        } else {
            btable_ep[ep_num].rx_count = ((max_len + 1U) & ~1U) << 9U;
        }

        if ((uint8_t)EP_BUF_SNG == buf_kind) {
            /* configure the endpoint status as NAK status */
            USBD_EP_RX_STAT_SET(ep_num, EPRX_NAK);
        } else if ((uint8_t)EP_BUF_DBL == buf_kind) {
            USBD_EP_RX_STAT_SET(ep_num, EPRX_DISABLED);
            USBD_EP_TX_STAT_SET(ep_num, EPTX_NAK);
        } else {
            /* error operation */
        }
    }
}

/*!
    \brief      configure the endpoint when it is disabled
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
static void usbd_ep_disable (usb_dev *udev, uint8_t ep_addr)
{
    (void)udev;

    uint8_t ep_num = EP_ID(ep_addr);

    if (EP_DIR(ep_addr)) {
        USBD_TX_DTG_CLEAR(ep_num);

        /* configure the endpoint status as DISABLED */
        USBD_EP_TX_STAT_SET(ep_num, EPTX_DISABLED);
    } else {
        USBD_RX_DTG_CLEAR(ep_num);

        /* configure the endpoint status as DISABLED */
        USBD_EP_RX_STAT_SET(ep_num, EPRX_DISABLED);
    }
}

/*!
    \brief      enable endpoint to receive
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
static void usbd_ep_rx_enable (usb_dev *udev, uint8_t ep_addr)
{
    (void)udev;

    /* enable endpoint to receive */
    USBD_EP_RX_STAT_SET(EP_ID(ep_addr), EPRX_VALID);
}

/*!
    \brief      set an endpoint to STALL status
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
static void usbd_ep_stall_set (usb_dev *udev, uint8_t ep_addr)
{
    uint8_t ep_num = EP_ID(ep_addr);

    if (0U == ep_num) {
        USBD_EP_TX_STAT_SET(0U, EPTX_STALL);
        USBD_EP_RX_STAT_SET(0U, EPRX_STALL);
    } else {
        if (EP_DIR(ep_addr)) {
            udev->transc_in[ep_num].ep_stall = 1U;

            USBD_EP_TX_STAT_SET(ep_num, EPTX_STALL);
        } else {
            udev->transc_out[ep_num].ep_stall = 1U;

            USBD_EP_RX_STAT_SET(ep_num, EPRX_STALL);
        }
    }
}

/*!
    \brief      clear endpoint stalled status
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     none
*/
static void usbd_ep_stall_clear (usb_dev *udev, uint8_t ep_addr)
{
    uint8_t ep_num = EP_ID(ep_addr);

    if (EP_DIR(ep_addr)) {
        /* clear endpoint data toggle bit */
        USBD_TX_DTG_CLEAR(ep_num);

        udev->transc_in[ep_num].ep_stall = 0U;

        /* clear endpoint stall status */
        USBD_EP_TX_STAT_SET(ep_num, EPTX_VALID);
    } else {
        /* clear endpoint data toggle bit */
        USBD_RX_DTG_CLEAR(ep_num);

        udev->transc_out[ep_num].ep_stall = 0U;

        /* clear endpoint stall status */
        USBD_EP_RX_STAT_SET(ep_num, EPRX_VALID);
    }
}

/*!
    \brief      get the endpoint status
    \param[in]  udev: pointer to USB core instance
    \param[in]  ep_addr: endpoint address
                  in this parameter:
                    bit0..bit6: endpoint number (0..7)
                    bit7: endpoint direction which can be IN(1) or OUT(0)
    \param[out] none
    \retval     endpoint status
*/
static uint8_t usbd_ep_status (usb_dev *udev, uint8_t ep_addr)
{
    (void)udev;

    uint32_t epcs = USBD_EPxCS(EP_ID(ep_addr));

    if (EP_DIR(ep_addr)) {
        return (uint8_t)(epcs & EPxCS_TX_STA);
    } else {
        return (uint8_t)(epcs & EPxCS_RX_STA);
    }
}

/*!
    \brief      write data from user FIFO to USB RAM
    \param[in]  user_fifo: pointer to user FIFO
    \param[in]  ep_num: endpoint number
    \param[in]  bytes: the bytes count of the write data
    \param[out] none
    \retval     none
*/
static void usbd_ep_data_write (uint8_t *user_fifo, uint8_t ep_num, uint16_t bytes)
{
    if (0U != bytes) {
        uint32_t n;
        uint32_t *write_addr = (uint32_t *)(btable_ep[ep_num].tx_addr * 2U + USBD_RAM);

        for (n = 0U; n < (bytes + 1U) / 2U; n++) {
            *write_addr++ = *((uint16_t*)user_fifo);
            user_fifo += 2U;
        }
    }

    btable_ep[ep_num].tx_count = bytes;

    USBD_EP_TX_STAT_SET(ep_num, EPTX_VALID);
}

/*!
    \brief      read data from USBRAM to user FIFO
    \param[in]  user_fifo: pointer to user FIFO
    \param[in]  ep_num: endpoint number
    \param[in]  buf_kind: endpoint buffer kind
    \param[out] none
    \retval     none
*/
static uint16_t usbd_ep_data_read (uint8_t *user_fifo, uint8_t ep_num, uint8_t buf_kind)
{
    uint16_t n = 0U, bytes = 0U;
    uint32_t *read_addr = NULL;

    if ((uint8_t)EP_BUF_SNG == buf_kind) {
        bytes = (uint16_t)(btable_ep[ep_num].rx_count & EPRCNT_CNT);

        read_addr = (uint32_t *)(btable_ep[ep_num].rx_addr * 2U + USBD_RAM);
    } else if ((uint8_t)EP_BUF_DBL == buf_kind) {
        if (USBD_EPxCS(ep_num) & EPxCS_TX_DTG) {
            bytes = (uint16_t)(btable_ep[ep_num].tx_count & EPRCNT_CNT);

            read_addr = (uint32_t *)(btable_ep[ep_num].tx_addr * 2U + USBD_RAM);
        } else {
            bytes = (uint16_t)(btable_ep[ep_num].rx_count & EPRCNT_CNT);

            read_addr = (uint32_t *)(btable_ep[ep_num].rx_addr * 2U + USBD_RAM);
        }
    } else {
        return 0U;
    }

    for (n = 0U; n < (bytes + 1U) / 2U; n++) {
        *((uint16_t*)user_fifo) = (uint16_t)*read_addr++;
        user_fifo += 2U;
    }

    return bytes;
}

#ifdef USBD_LOWPWR_MODE_ENABLE

/*!
    \brief      restore system clocks and power while exiting from suspend mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void lowpower_mode_exit (void)
{
    /* restore system clock */

#ifdef LPM_ENABLED
    /* enable IRC8M */
    rcu_osci_on(RCU_IRC8M);

    /* wait till IRC8M is ready */
    while (RESET == rcu_flag_get(RCU_FLAG_IRC8MSTB)) {
    }
#else
    /* enable HXTAL */
    rcu_osci_on(RCU_HXTAL);

    /* wait till HXTAL is ready */
    while(RESET == rcu_flag_get(RCU_FLAG_HXTALSTB)) {
    }
#endif

    /* enable PLL */
    rcu_osci_on(RCU_PLL_CK);

    /* wait till PLL is ready */
    while(RESET == rcu_flag_get(RCU_FLAG_PLLSTB)) {
    }

    /* select PLL as system clock source */
    rcu_system_clock_source_config(RCU_CKSYSSRC_PLL);

    /* wait till PLL is used as system clock source */
    while(0x08U != rcu_system_clock_source_get()) {
    }

    /* low power sleep on exit disabled */
    system_lowpower_reset(SCB_LPM_DEEPSLEEP);

#ifdef USE_IRC48M
    /* enable IRC48M clock */
    rcu_osci_on(RCU_IRC48M);

    /* wait till IRC48M is ready */
    while (SUCCESS != rcu_osci_stab_wait(RCU_IRC48M)) {
    }

    rcu_ck48m_clock_config(RCU_CK48MSRC_IRC48M);
#endif
}

#endif /* USBD_LOWPWR_MODE_ENABLE */

/*!
    \brief      resume the USB device
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void usbd_resume (usb_dev *udev)
{
#ifdef LPM_ENABLED
    if(1 == udev->lpm.L1_remote_wakeup){
        USBD_CTL |= CTL_L1RSREQ;
    }
#endif /* LPM_ENABLED */

    if(1U == usbd_core.dev->pm.remote_wakeup){
        /* make USB resume */
        USBD_CTL |= CTL_RSREQ;
    }
}

/*!
    \brief      set USB device to leave mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void usbd_leave_suspend (void)
{
    /* clear low_power mode bit in USBD_CTL */
   USBD_CTL &= ~CTL_LOWM;

#ifdef USBD_LOWPWR_MODE_ENABLE

    /* restore normal operations */
    lowpower_mode_exit();

#endif /* USBD_LOWPWR_MODE_ENABLE */

    /* clear SETSPS bit */
    USBD_CTL &= ~CTL_SETSPS;
}

/*!
    \brief      set USB device to enter suspend mode
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void usbd_suspend (void)
{
    /* set USB module to suspend and low-power mode */
    USBD_CTL |= CTL_SETSPS | CTL_LOWM;

#ifdef USBD_LOWPWR_MODE_ENABLE

    /* check wakeup flag is set */
    if (0U == (USBD_INTF & INTF_WKUPIF)) {
        /* enter DEEP_SLEEP mode with LDO in low power mode */
        pmu_to_deepsleepmode(PMU_LDO_LOWPOWER, WFI_CMD);
    } else {
        /* clear wakeup interrupt flag */
        CLR(WKUPIF);

        /* clear set_suspend flag */
        USBD_CTL &= ~CTL_SETSPS;
    }

#endif /* USBD_LOWPWR_MODE_ENABLE */
}
