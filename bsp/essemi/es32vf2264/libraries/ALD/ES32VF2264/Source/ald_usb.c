/**
  *********************************************************************************
  *
  * @file    ald_usb.c
  * @brief   USB module driver.
  *
  * @version V1.0
  * @date    25 Feb 2022
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          25 Feb 2022     AE Team         The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  */

#include "ald_conf.h"
#include "usb_lowlayer_api.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup USB USB
  * @brief USB module driver
  * @{
  */
#ifdef ALD_USB
/**
  * @defgroup USB_Public_Functions USB Public Function
  * @{
  */
/** @defgroup USB_Public_Functions_Group1 Base functions
  * @brief Base functions
  * @{
  */

/**
  * @brief  Gets the number of current frame.
  * @retval Number of the frame.
  */
uint32_t ald_usb_frame_number_get(void)
{
  uint8_t framel = (uint8_t)USB->FRAME1;
  uint8_t frameh = (uint8_t)USB->FRAME2;
    return ((uint32_t)(framel & 0xFF) + ((uint32_t)(frameh & 0xFF) << 8));
}

/**
  * @brief  Request the session.
  * @param  start: true/false.
  * @retval None
  */
void ald_usb_otg_session_request(bool start)
{
    if (start)
        USB->DEVCON |= (uint8_t)ALD_USB_DEVCON_SESSION;
    else
        USB->DEVCON &= (uint8_t)(~(ALD_USB_DEVCON_SESSION));

    return;
}

/**
  * @brief  Gets the mode.
  * @retval Mode
  */
uint32_t ald_usb_mode_get(void)
{
    return (USB->DEVCON & ((uint8_t)(ALD_USB_DEVCON_HOST | ALD_USB_DEVCON_SESSION)));
}

/**
  * @brief  Start host require.
  * @retval Mode
  */
uint32_t ald_usb_mode_host_req(void)
{
    USB->DEVCON |= (uint8_t)ALD_USB_DEVCON_HOSTREQ;
    return 0;
}

/**
  * @brief  Clear host require.
  * @retval Mode
  */
uint32_t ald_usb_mode_host_req_clear(void)
{
    USB->DEVCON &= (uint8_t)(~ALD_USB_DEVCON_HOSTREQ);
    return 0;
}

/**
  * @brief  Enable/Disable the high mode.
  * @param  enable: ENABLE/DISABLE.
  * @retval None
  */
void ald_usb_high_speed_enable(bool enable)
{
    assert_param(enable == DISABLE);

    return;
}

/**
  * @brief  Gets the speed of the device.
  * @retval Type of the speed.
  */
uint32_t ald_usb_device_speed_get(void)
{
    return ALD_USB_FULL_SPEED;
}

/**
  * @brief  Gets the number of the endpoint.
  * @retval Number of the endpoint.
  */
uint32_t ald_usb_num_ep_get( void)
{
    return ALD_NUM_USB_EP;
}

/**
  * @brief  Reset USB Control.
  * @retval None
  */
void ald_usb_control_reset(void)
{
    //ALD_RCU_USB_RESET_ENABLE();

    return;
}

/**
  * @brief  Output USB clock, not support.
  * @retval None
  */
void ald_usb_clock_output(void)
{
    return;
}

/**
  * @brief  Starts eye diagram for high-speed host, not support.
  * @param  buf: Buffer for eye diagram.
  * @param  len: Length of the buffer.
  * @retval Status, 0 means success, other values means failure.
  */
int ald_usb_eye_diagram_start(uint8_t *buf, uint16_t len)
{
    return 0;
}

/**
  * @brief  Pull up or pull down USB dp line.
  * @param  pupd: USB_DPDM_FLOATING/USB_DPDM_PUSH_UP/USB_DPDM_PUSH_DOWN.
  * @retval None
  */
void ald_usb_dppud_set(ald_dpdm_push_t pupd)
{
    USB->DPDMCON  &= (uint8_t)(~USB_DPDMCON_DPPUD_MSK);
    USB->DPDMCON  |= (uint8_t)(pupd << USB_DPDMCON_DPPUD_POSS);
    return;
}

/**
  * @brief  Pull up or pull down USB dm line.
  * @param  pupd: USB_DPDM_FLOATING/USB_DPDM_PUSH_UP/USB_DPDM_PUSH_DOWN.
  * @retval None
  */
void ald_usb_dmpud_set(ald_dpdm_push_t pupd)
{
    USB->DPDMCON  &= (uint8_t)(~USB_DPDMCON_DMPUD_MSK);
    USB->DPDMCON  |= (uint8_t)(pupd << USB_DPDMCON_DMPUD_POSS);
    return;
}

/**
  * @brief  Switch usb mode by software.
  * @param  host: 0, indicates that software force to host
            host: 1, indicates that software force to device.
  * @retval None
  */
void ald_usb_swcid_host(uint8_t host)
{
    if (host)
        USB->SWCID  |= (uint8_t)(USB_SWCID_HOST_MSK);
    else
        USB->SWCID  &= (uint8_t)(~USB_SWCID_HOST_MSK);
    return;
}

/**
  * @brief  Switch the control method of CID.
  * @param  cid: 0, indicates that use the hardware control
            cid: 1, indicates that use the software control.
  * @retval None
  */
void ald_usb_swcid_cidctrl(uint8_t cid)
{
    if (cid)
        USB->SWCID  |= (uint8_t)(ALD_USB_SWCID_CIDCTRL);
    else
        USB->SWCID  &= (uint8_t)(~ALD_USB_SWCID_CIDCTRL);
    return;
}

/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group2 Device functions
  * @brief Device functions
  * @{
  */

/**
  * @brief  Gets the address.
  * @retval Address.
  */
uint8_t ald_usb_dev_get_addr(void)
{
    return (USB->FADDR);
}

/**
  * @brief  Sets the address.
  * @param  addr: The address which will be set.
  * @retval None
  */
void ald_usb_dev_set_addr(uint8_t addr)
{
    USB->FADDR = addr;
    return;
}

/**
  * @brief  Enable connection.
  * @retval None
  */
void ald_usb_dev_connect(void)
{
    USB->DPDMCON |= (uint8_t)(ALD_USB_DPDMCON_PHYPWREN);
    return;
}

/**
  * @brief  Disable connection.
  * @retval None
  */
void ald_usb_dev_disconnect(void)
{
    USB->DPDMCON &= (uint8_t)(~(ALD_USB_DPDMCON_PHYPWREN));
    return;
}

/**
  * @brief  Enable the devices suspend.
  * @retval None
  */
void ald_usb_dev_suspend_enable(void)
{
    USB->POWER |= (uint8_t)USB_POWER_SUSPENDEN_MSK;
    return;
}

/**
  * @brief  Configure the endpoint in device mode.
  * @param  ep_idx: Index of the endpoint
  * @param  p_max: Size of the maximum package.
  * @param  flags: Flags of the endpoint.
  * @retval None
  */
void ald_usb_dev_ep_config(uint32_t ep_idx, uint32_t p_max, uint32_t flags)
{
    uint32_t tmp = 0U;

    USB->INDEX = (uint8_t)ep_idx;

    if (flags & ALD_USB_EP_DEV_IN) {
        USB->TXMAXP = (uint8_t)(p_max);
        if (flags & ALD_USB_EP_AUTO_SET)
            tmp |= USB_TXCSRH_AUTOSET_MSK;
        if ((flags & ALD_USB_EP_MODE_MASK) == ALD_USB_EP_MODE_ISOC)
            tmp |= USB_TXCSRH_ISO_MSK;

        USB->CSR0H_TXCSRH |= (uint8_t)tmp;
        USB->CSR0L_TXCSRL |= (uint8_t)USB_TXCSRL_CLRDT_MSK;
    }
    else {
        USB->RXMAXP = (uint8_t)(p_max);
        if (flags & ALD_USB_EP_AUTO_CLEAR)
            tmp |= USB_RXCSRH_AUTOCLR_MSK;
        if ((flags & ALD_USB_EP_MODE_MASK) == ALD_USB_EP_MODE_ISOC)
            tmp |= USB_TXCSRH_ISO_MSK;

        USB->RXCSRH |= (uint8_t)tmp;
        USB->RXCSRL |= (uint8_t)USB_RXCSRL_CLRDT_MSK;
    }

    return;
}

/**
  * @brief  Gets the parameters of the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @param  p_max: Size of the maximum package.
  * @param  flags: Flags of the endpoint.
  * @retval None
  */
void ald_usb_dev_ep_get_config(uint32_t ep_idx, uint32_t *p_max, uint32_t *flags)
{
    uint32_t tmp;

    USB->INDEX = (uint8_t)ep_idx;

    if (*flags & ALD_USB_EP_DEV_IN) {
        *flags = ALD_USB_EP_DEV_IN;
        *p_max = (uint32_t)USB->TXMAXP;
        tmp    = (uint32_t)USB->CSR0H_TXCSRH;
        if (tmp & USB_TXCSRH_AUTOSET_MSK)
            *flags |= ALD_USB_EP_AUTO_SET;
        if (tmp & USB_TXCSRH_ISO_MSK)
            *flags |= ALD_USB_EP_MODE_ISOC;
        else
            *flags |= ALD_USB_EP_MODE_BULK;
    }
    else {
        *flags = ALD_USB_EP_DEV_OUT;
        *p_max = (uint32_t)USB->RXMAXP;
        tmp    = (uint32_t)USB->RXCSRH;

        if (tmp & USB_RXCSRH_AUTOCLR_MSK)
            *flags |= ALD_USB_EP_AUTO_CLEAR;
        if (tmp & USB_RXCSRH_ISO_MSK)
            *flags |= ALD_USB_EP_MODE_ISOC;
        else
            *flags |= ALD_USB_EP_MODE_BULK;
    }
    return;
}
extern void printf_e(const char *fmt, ...);
/**
  * @brief  Acknowledge the data from host.
  * @param  ep_idx: Index of the endpoint
  * @param  last: true/false
  * @retval None
  */
void ald_usb_dev_ep_data_ack(uint32_t ep_idx, bool last)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0)
        USB->CSR0L_TXCSRL |= (uint8_t)(USB_CSR0L_RXRDYC_MSK | (last ? USB_CSR0L_DATAEND_MSK : 0));
    else
        USB->RXCSRL &= (uint8_t)(~USB_RXCSRL_RXRDY_MSK);

    return;
}

/**
  * @brief  Stall the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_dev_ep_stall(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0)
        USB->CSR0L_TXCSRL |= (uint8_t)(USB_CSR0L_RXRDYC_MSK | USB_CSR0L_STALL_MSK);
    else if (flags == ALD_USB_EP_DEV_IN)
        USB->CSR0L_TXCSRL |= (uint8_t)USB_TXCSRL_STALL_MSK;
    else
        USB->RXCSRL |= (uint8_t)USB_RXCSRL_STALL_MSK;

    return;
}

/**
  * @brief  Cancel the stall status.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_dev_ep_stall_clear(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0)
        USB->CSR0L_TXCSRL &= (uint8_t)(~USB_CSR0L_STALLED_MSK);
    else if (flags == ALD_USB_EP_DEV_IN){
        USB->CSR0L_TXCSRL &= (uint8_t)(~(USB_TXCSRL_STALL_MSK | USB_TXCSRL_STALLED_MSK));
        USB->CSR0L_TXCSRL |= (uint8_t)USB_TXCSRL_CLRDT_MSK;
    }
    else{
        USB->RXCSRL &= (uint8_t)(~(USB_RXCSRL_STALL_MSK | USB_RXCSRL_STALLED_MSK));
        USB->RXCSRL |= (uint8_t)USB_RXCSRL_CLRDT_MSK;
    }

    return;
}

/**
  * @brief  Clear the status of the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_dev_ep_status_clear(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        if (flags & ALD_USB_DEV_EP0_OUT_PKTRDY)
            USB->CSR0L_TXCSRL |= (uint8_t)USB_CSR0L_RXRDYC_MSK;
        if (flags & ALD_USB_DEV_EP0_SETUP_END)
            USB->CSR0L_TXCSRL |= (uint8_t)USB_CSR0L_SETENDC_MSK;
        if (flags & ALD_USB_DEV_EP0_SENT_STALL)
            USB->CSR0L_TXCSRL &= (uint8_t)(~USB_CSR0L_STALLED_MSK);
    }
    else {
        USB->CSR0L_TXCSRL &= (uint8_t)(~(flags & (ALD_USB_DEV_TX_SENT_STALL | ALD_USB_DEV_TX_UNDERRUN)));
        USB->RXCSRL &= (uint8_t)(~((flags & (ALD_USB_DEV_RX_SENT_STALL | ALD_USB_DEV_RX_DATA_ERROR
                         | ALD_USB_DEV_RX_OVERRUN)) >> ALD_USB_RX_EPSTATUS_SHIFT));
    }

    return;
}

/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group3 Host functions
  * @brief Host functions
  * @{
  */
/**
  * @brief  Gets the device's address.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval Address
  */
uint32_t ald_usb_host_addr_get(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    return (USB->FADDR);
}

/**
  * @brief  Sets the device's address.
  * @param  ep_idx: Index of the endpoint.
  * @param  addr: The device's address.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_host_addr_set(uint32_t ep_idx, uint32_t addr, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    USB->FADDR = (uint8_t)addr;

    return;
}

/**
  * @brief  Configure the endpoint in host mode.
  * @param  ep_idx: Index of the endpoint.
  * @param  p_max: Size of the maximum package.
  * @param  nak_val: Value of the nack.
  * @param  t_ep: Target endpoint.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_host_ep_config(uint32_t ep_idx, uint32_t p_max, uint32_t nak_val, uint32_t t_ep, uint32_t flags)
{
    uint32_t tmp = 0U;

    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        USB->NAKLIMIT0_TXINTERVAL = (uint8_t)nak_val;

        if (flags & ALD_USB_EP_SPEED_HIGH)
            ;
        else if (flags & ALD_USB_EP_SPEED_FULL)
            ;
        else
            ;
    }
    else {
        tmp = t_ep;

        if (flags & ALD_USB_EP_SPEED_HIGH)
            ;
        else if (flags & ALD_USB_EP_SPEED_FULL)
            ;
        else
            ;

        switch (flags & ALD_USB_EP_MODE_MASK) {
            case ALD_USB_EP_MODE_BULK:
                tmp |= ALD_USB_TXTYPE1_PROTO_BULK;
                break;

            case ALD_USB_EP_MODE_ISOC:
                tmp |= ALD_USB_TXTYPE1_PROTO_ISOC;
                break;

            case ALD_USB_EP_MODE_INT:
                tmp |= ALD_USB_TXTYPE1_PROTO_INT;
                break;

            case ALD_USB_EP_MODE_CTRL:
                tmp |= ALD_USB_TXTYPE1_PROTO_CTRL;
                break;
        }

        if (flags & ALD_USB_EP_HOST_OUT) {
            USB->TXTYPE = (uint8_t)tmp;
            USB->NAKLIMIT0_TXINTERVAL = (uint8_t)nak_val;
            USB->TXMAXP = (uint8_t)p_max;

            tmp = 0;
            if (flags & ALD_USB_EP_AUTO_SET)
                tmp = (uint8_t)ALD_USB_TXCSRH_AUTOSET;
            USB->CSR0H_TXCSRH |= (uint8_t)tmp;
        }
        else {
            USB->RXTYPE = (uint8_t)tmp;
            USB->RXINTERVAL = (uint8_t)nak_val;
            USB->RXMAXP = (uint8_t)p_max;

            tmp = 0;
            if (flags & ALD_USB_EP_AUTO_CLEAR)
                tmp |= (uint8_t)USB_RXCSRH_AUTOCLR_MSK;
            if (flags & ALD_USB_EP_AUTO_REQUEST)
                tmp |= (uint8_t)USB_RXCSRH_AUTOREQ_MSK;

            USB->RXCSRH |= (uint8_t)tmp;
        }
    }

    return;
}

/**
  * @brief  Acknowledge the data in host mode.
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_ep_data_ack(uint32_t ep_idx)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0)
        USB->CSR0L_TXCSRL &= (uint8_t)(~(USB_CSR0L_RXRDY_MSK));
    else
        USB->RXCSRL &= (uint8_t)(~(USB_RXCSRL_RXRDY_MSK));

    return;
}

/**
  * @brief  Toggle the data in host mode.
  *         The function is used to force the state of the data toggle in host mode.
  *         If the value passed in the bDataToggle parameter is false, then the data
  *         toggle is set to the DATA0 state, and if it is true it is set to the DATA1
  *         state.
  * @param  ep_idx: Index of the endpoint.
  * @param  toggle: true/false.
  * @param  flags: can be USB_EP_HOST_IN or USB_EP_HOST_OUT.
  * @retval None
  */
void ald_usb_host_ep_data_toggle(uint32_t ep_idx, bool toggle, uint32_t flags)
{
    /* not supported by es32f0271. */
    return;
}

/**
  * @brief  Clear the status of endpoint in host mode.
  * @param  ep_idx: Index of the endpoint.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_host_ep_status_clear(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        USB->CSR0L_TXCSRL &= (uint8_t)(~flags & 0xFF);
    }
    else {
        USB->CSR0L_TXCSRL &= (uint8_t)(~flags & 0xFF);
        USB->RXCSRL &= (uint8_t)(~(flags >> 16) & 0xFF);
    }

    return;
}

/**
  * @brief  Gets the HUB's address.
  * @param  ep_idx: Index of the endpoint.
  * @param  flags: Flags.
  * @retval Address
  */
uint32_t ald_usb_host_hub_addr_get(uint32_t ep_idx, uint32_t flags)
{
    /* not supported by es32f0271. */
    return 0;
}

/**
  * @brief  Sets the HUB's address.
  * @param  ep_idx: Index of the endpoint.
  * @param  addr: HUB's address which will be set.
  * @param  flags: Flags.
  * @retval Address
  */
void ald_usb_host_hub_addr_set(uint32_t ep_idx, uint32_t addr, uint32_t flags)
{
    /* not supported by es32f0271. */
    return;
}

/**
  * @brief  Disable power.
  * @retval None
  */
void ald_usb_host_pwr_disable(void)
{
    USB->DPDMCON &= (uint8_t)(~(ALD_USB_DPDMCON_PHYPWREN));
    return;
}

/**
  * @brief  Enable power.
  * @retval None
  */
void ald_usb_host_pwr_enable(void)
{
    USB->DPDMCON |= (uint8_t)(ALD_USB_DPDMCON_PHYPWREN);
    return;
}

/**
  * @brief  Configure power in host mode.
  * @param  flags: Flags
  * @retval None
  */
void ald_usb_host_pwr_config(uint32_t flags)
{
    return;
}

/**
  * @brief  Disable the fault parameters of the power.
  * @retval None
  */
void ald_usb_host_pwr_fault_disable(void)
{
    return;
}

/**
  * @brief  Enable the fault parameters of the power.
  * @retval None
  */
void ald_usb_host_pwr_fault_enable(void)
{
    return;
}

/**
  * @brief  Request data IN(from device to host)
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_request_in(uint32_t ep_idx)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0)
        USB->CSR0L_TXCSRL |= (uint8_t)USB_CSR0L_REQPKT_MSK;
    else
        USB->RXCSRL |= (uint8_t)USB_RXCSRL_REQPKT_MSK;

    return;
}

/**
  * @brief  Clear the status of request IN.
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_request_in_clear(uint32_t ep_idx)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0)
        USB->CSR0L_TXCSRL &= (uint8_t)(~USB_CSR0L_REQPKT_MSK);
    else
        USB->RXCSRL &= (uint8_t)(~USB_RXCSRL_REQPKT_MSK);

    return;
}

/**
  * @brief  Set the request for a status IN transaction.
  * @retval None
  */
void ald_usb_host_request_status(void)
{
    USB->CSR0L_TXCSRL |= (uint8_t)(ALD_USB_CSR0L_REQPKT | ALD_USB_CSR0L_STATUSPKT);

    return;
}

/**
  * @brief  Reset the USB's bus.
  * @param  start: true/false.
  * @retval None
  */
void ald_usb_host_reset(bool start)
{
    if (start)
        USB->POWER |= ALD_USB_POWER_RESET;
    else
        USB->POWER &= ~(ALD_USB_POWER_RESET);

    return;
}

/**
  * @brief  Resume the devices.
  * @param  start: true/false.
  * @retval None
  */
void ald_usb_host_resume(bool start)
{
    if (start)
        USB->POWER |= (uint8_t)USB_POWER_RESUME_MSK;
    else
        USB->POWER &= (uint8_t)(~(ALD_USB_POWER_RESUME));

    return;
}

/**
  * @brief  Suspend the devices.
  * @retval None
  */
void ald_usb_host_suspend(void)
{
    USB->POWER |= (uint8_t)USB_POWER_SUSPEND_MSK;
    return;
}

/**
  * @brief  Gets the device's speed.
  * @retval Type of the speed.
  */
uint32_t ald_usb_host_speed_get(void)
{
    if (USB->DEVCON & ALD_USB_DEVCON_FSDEV)
        return ALD_USB_FULL_SPEED;

    if (USB->DEVCON & ALD_USB_DEVCON_LSDEV)
        return ALD_USB_LOW_SPEED;

    return ALD_USB_UNDEF_SPEED;
}

/**
  * @brief  Sets the endpoint speed.
  * @param  ep_idx: Index of the endpoint.
  * @param  flags: Type of the speed.
  * @retval None
  */
void ald_usb_host_ep_speed_set(uint32_t ep_idx, uint32_t flags)
{
    /* not support in F0271 */
    return;
}

/**
  * @brief  Ping the endpoint.
  * @param  ep_idx: Index of the endpoint.
  * @param  enable: ENABLE/DISABLE.
  * @retval None
  */
void ald_usb_host_ep_ping(uint32_t ep_idx, bool enable)
{
    /* not support in F0271 */
    return;
}

/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group4 Endpoint functions
  * @brief Endpoint functions
  * @{
  */
/**
  * @brief  Gets the size of the available data.
  * @param  ep_idx: Index of the endpoint
  * @retval Size in bytes.
  */
uint32_t ald_usb_ep_data_avail(uint32_t ep_idx)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        if ((USB->CSR0L_TXCSRL & ALD_USB_CSR0L_RXRDY) == 0){
            return 0;
        }

        return USB->COUNT0_RX1;
    }
    else {
        if ((USB->RXCSRL & ALD_USB_CSR0L_RXRDY) == 0)
        {
            return 0;
        }

        return (USB->COUNT0_RX1 + (((uint32_t)USB->RXCOUNT2) << 8));
    }
}

/**
  * @brief  Gets the data from FIFO.
  * @param  ep_idx: Index of the endpoint
  * @param  data: Pointer to the buffer.
  * @param  size: Size of the data.
  * @retval Status.
  */
int32_t ald_usb_ep_data_get(uint32_t ep_idx, uint8_t *data, uint32_t *size)
{
    uint32_t i, rx_fifo_addr;

    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        if ((USB->CSR0L_TXCSRL & ALD_USB_CSR0L_RXRDY) == 0) {
            *size = 0;
            return -1;
        }
        i = USB->COUNT0_RX1;
    }
    else {
        if ((USB->RXCSRL & ALD_USB_CSR0L_RXRDY) == 0) {
            *size = 0;
            return -1;
        }
        i = USB->COUNT0_RX1 + (((uint32_t)USB->RXCOUNT2) << 8);
    }

    i = (i < *size) ? i : *size;
    *size = i;

    rx_fifo_addr = (uint32_t)(&USB->EP0FIFO) + 4 * ep_idx;

    for (; i > 0; i--)
        *data++ = *(volatile uint8_t *)(rx_fifo_addr);

    return 0;
}

/**
  * @brief  Puts data to the FIFO.
  * @param  ep_idx: Index of the endpoint
  * @param  data: Pointer to the data.
  * @param  size: Size of the data.
  * @retval Status.
  */
int32_t ald_usb_ep_data_put(uint32_t ep_idx, uint8_t *data, uint32_t size)
{
    uint32_t tx_fifo_addr;

    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        if (USB->CSR0L_TXCSRL & ALD_USB_CSR0L_TXRDY)
            return -1;
    }
    else {
        if (USB->CSR0L_TXCSRL & ALD_USB_TXCSRL_TXRDY)
            return -1;
    }

    tx_fifo_addr = (uint32_t)(&USB->EP0FIFO) + 4 * ep_idx;

    for (; size > 0; size--)
        *(volatile uint8_t *)tx_fifo_addr = *data++;

    return 0;
}

/**
  * @brief  Send data.
  * @param  ep_idx: Index of the endpoint
  * @param  tx_type: Type.
  * @retval Status.
  */
int32_t ald_usb_ep_data_send(uint32_t ep_idx, uint32_t tx_type)
{
    uint32_t tmp;

    USB->INDEX = (uint8_t)ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        if (USB->CSR0L_TXCSRL & ALD_USB_CSR0L_TXRDY)
            return -1;

        tmp = tx_type & 0xFF;
    }
    else {
        if (USB->CSR0L_TXCSRL & ALD_USB_TXCSRL_TXRDY)
            return -1;

        tmp = (tx_type >> 8) & 0xff;
    }

    USB->CSR0L_TXCSRL = tmp;

    return 0;
}

/**
  * @brief  Clear the status of the toggle.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_ep_data_toggle_clear(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = (uint8_t)ep_idx;

    if (flags & (ALD_USB_EP_HOST_OUT | ALD_USB_EP_DEV_IN))
        USB->CSR0L_TXCSRL |= (uint8_t)ALD_USB_TXCSRL_CLRDT;
    else
        USB->RXCSRL |= (uint8_t)ALD_USB_RXCSRL_CLRDT;

    return;
}

/**
  * @brief  Sets the size of request data IN
  * @param  ep_idx: Index of the endpoint
  * @param  count: Size of request data IN.
  * @retval None
  */
void ald_usb_ep_req_packet_count(uint32_t ep_idx, uint32_t count)
{
    /* not support in f0271 */
    return;
}

/**
  * @brief  Gets the status of the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @retval Status.
  */
uint32_t ald_usb_ep_status(uint32_t ep_idx)
{
    uint32_t status;

    USB->INDEX = (uint8_t)ep_idx;

    status = (ep_idx == ALD_USB_EP_0) ? (USB->CSR0L_TXCSRL): (USB->CSR0L_TXCSRL | (USB->RXCSRL << 16));

    return status;
}

/**
  * @brief  Configure the endpoint in DMA mode.
  * @param  ep_idx: Index of the endpoint
  * @param  flag: Flags.
  * @param  en: ENABLE/DISABLE.
  * @retval None
  */
void ald_usb_ep_dma_config(uint32_t ep_idx, uint32_t flag, type_func_t en)
{
    /* Not supported in F0271 */

    return;
}
/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group5 FIFO functions
  * @brief FIFO functions
  * @{
  */
/**
  * @brief  Gets the address of the FIFO.
  * @param  ep_idx: Index of the endpoint
  * @retval Address
  */
uint32_t ald_usb_fifo_addr_get(uint32_t ep_idx)
{
    /* Not supported in F0271 */

    return 0;
}

/**
  * @brief  Gets the parameters of the FIFO.
  * @param  ep_idx: Index of the endpoint
  * @param  addr: Address.
  * @param  size: Size of FIFO.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_fifo_config_get(uint32_t ep_idx, uint32_t *addr, uint32_t *size, uint32_t flags)
{
    USB->INDEX = ep_idx;

    if (flags & (ALD_USB_EP_HOST_OUT | ALD_USB_EP_DEV_IN)) {
        *addr = ((uint32_t)USB->TXFIFO1 | ((uint32_t)USB->TXFIFO2 & 0x03)) << 3;
        *size = ((USB->TXFIFO2 & ALD_USB_TXFIFO2_DPB) == 0x00) ? (USB->TXFIFO2 & ALD_USB_TXFIFO2_MAXPKTSIZE_1024) : (2 * (USB->TXFIFO2 & ALD_USB_TXFIFO2_MAXPKTSIZE_1024));
    }
    else {
        *addr = ((uint32_t)USB->RXFIFO1 | ((uint32_t)USB->RXFIFO2 & 0x03)) << 3;
        *size = ((USB->RXFIFO2 & ALD_USB_RXFIFO2_DPB) == 0x00) ? (USB->RXFIFO2 & ALD_USB_RXFIFO2_MAXPKTSIZE_1024) : (2 * (USB->RXFIFO2 & ALD_USB_RXFIFO2_MAXPKTSIZE_1024));
    }

    return;
}

/**
  * @brief  Sets the parameters of the FIFO.
  * @param  ep_idx: Index of the endpoint
  * @param  addr: Address.
  * @param  size: Size of FIFO, valid parameter has defined in usb_lowlayer_api.h.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_fifo_config_set(uint32_t ep_idx, uint32_t addr, uint32_t size, uint32_t flags)
{
    USB->INDEX = ep_idx;

    if (flags & (ALD_USB_EP_HOST_OUT | ALD_USB_EP_DEV_IN)) {
        USB->TXFIFO1 = (uint8_t)((addr >> 3) & 0xFF);
        USB->TXFIFO2 |= (uint8_t)(((addr >> 3) >> 8) & 0x0F);

        USB->TXFIFO2 |= (uint8_t)(size << USB_TXFIFO2_MAXPKTSIZE_POSS);

        USB->CSR0L_TXCSRL |= (uint8_t)ALD_USB_TXCSRL_FLUSH;
    }
    else {
        USB->RXFIFO1 = (uint8_t)((addr >> 3) & 0xFF);
        USB->RXFIFO2 |= (uint8_t)(((addr >> 3) >> 8) & 0x0F);

        USB->RXFIFO2 |= (uint8_t)(size << USB_RXFIFO2_MAXPKTSIZE_POSS);

        USB->RXCSRL |= (uint8_t)ALD_USB_RXCSRL_FLUSH;
    }

    return;
}

/**
  * @brief  Flush the FIFO
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_fifo_flush(uint32_t ep_idx, uint32_t flags)
{
    USB->INDEX = ep_idx;

    if (ep_idx == ALD_USB_EP_0) {
        if ((USB->CSR0L_TXCSRL & (ALD_USB_CSR0L_RXRDY | ALD_USB_CSR0L_TXRDY)) != 0)
            USB->CSR0H_TXCSRH |= ALD_USB_CSR0H_FLUSH;
    }
    else {
        if (flags & (ALD_USB_EP_HOST_OUT | ALD_USB_EP_DEV_IN)) {
            if (USB->CSR0L_TXCSRL & ALD_USB_TXCSRL_TXRDY)
                USB->CSR0L_TXCSRL |= ALD_USB_TXCSRL_FLUSH;
        }
        else {
            if (USB->RXCSRL & ALD_USB_RXCSRL_RXRDY)
                USB->RXCSRL |= ALD_USB_RXCSRL_FLUSH;
        }
    }
    return;
}

/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group6 Interrupt functions
  * @brief Interrupt functions
  * @{
  */
/**
  * @brief  Disable interrupt.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_disable(uint32_t flags)
{
    if (flags & ALD_USB_IDR_STATUS)
        USB->IDR |= (uint8_t)(flags & ALD_USB_IDR_STATUS);

    return;
}

/**
  * @brief  Enable interrupt.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_enable(uint32_t flags)
{
    if (flags & ALD_USB_IER_STATUS)
        USB->IER |= (uint8_t)(flags & ALD_USB_IER_STATUS);

    return;
}

/**
  * @brief  Gets the status of the interrupt.
  * @retval Status.
  */
uint32_t ald_usb_int_status_get(void)
{
    uint32_t Status;

    Status = USB->IFM & 0x7F;
    USB->ICR |= Status;

    return Status;
}

/**
  * @brief  Disable interrupt of the endpoint.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_disable_ep(uint32_t flags)
{
    USB->TXIDR |= (uint8_t)(flags & (ALD_USB_INTEP_HOST_OUT | ALD_USB_INTEP_DEV_IN | ALD_USB_INTEP_0));
    USB->RXIDR |= (uint8_t)((flags & (ALD_USB_INTEP_HOST_IN | ALD_USB_INTEP_DEV_OUT)) >> ALD_USB_INTEP_RX_SHIFT);
    return;
}

/**
  * @brief  Enable interrupt of the endpoint.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_enable_ep(uint32_t flags)
{
    USB->TXIER |= (uint8_t)(flags & (ALD_USB_INTEP_HOST_OUT | ALD_USB_INTEP_DEV_IN | ALD_USB_INTEP_0));
    USB->RXIER |= (uint8_t)((flags & (ALD_USB_INTEP_HOST_IN | ALD_USB_INTEP_DEV_OUT)) >> ALD_USB_INTEP_RX_SHIFT);
    return;
}

/**
  * @brief  Gets the ststus of the endpoint interrupt.
  * @retval Status.
  */
uint32_t ald_usb_int_status_ep_get(void)
{
    uint32_t status;

    status = USB->TXIFM;
    status |= (USB->RXIFM << ALD_USB_INTEP_RX_SHIFT);

    USB->TXICR |= (uint8_t)(status & 0xFF);
    USB->RXICR |= (uint8_t)((status >> ALD_USB_INTEP_RX_SHIFT) & 0xFF);

    return status;
}

/**
  * @brief  Register USB's interrupt.
  * @retval None
  */
void ald_usb_int_register(void)
{
    //ald_mcu_irq_config(USB_IRQn, 2, ENABLE);
    csi_vic_set_prio(USB_IRQn, 3);
    csi_vic_enable_sirq(USB_IRQn);
    return;
}

/**
  * @brief  Unregister USB's interrupt.
  * @retval None
  */
void ald_usb_int_unregister(void)
{
    //ald_mcu_irq_config(USB_IRQn, 2, DISABLE);
    csi_vic_disable_sirq(USB_IRQn);
    return;
}

/**
  * @brief  Get USB's interrupt number.
  * @retval None
  */
uint32_t ald_usb_int_num_get(void)
{
    return USB_IRQn;
}
/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group7 DMA functions
  * @brief DMA functions
  * @{
  */
#if defined(__ALD_MDA_H__)
/**
  * @brief  Configure DMA's channel.
  * @param  ch: Channel.
  * @param  addr: Address.
  * @param  count: Size of the data to be moved.
  * @param  ctrl: Parameters of the DMA's controler
  * @retval None
  */
void ald_usb_dma_channel_config(uint8_t ch, uint32_t addr, uint32_t count, uint32_t ctrl)
{
    return;
}

/**
  * @brief  Start multiple receive.
  * @param  ep_idx: Index of the endpoint
  * @retval None
  */
void ald_usb_dma_mult_recv_start(uint32_t ep_idx)
{
    return;
}

/**
  * @brief  Start DMA's machine.
  * @param  ch: Channel.
  * @retval None
  */
void ald_usb_dma_channel_start(uint8_t ch)
{
    return;
}

/**
  * @brief  Stop DMA's machine.
  * @param  ch: Channel.
  * @retval None
  */
void ald_usb_dma_channel_stop(uint8_t ch)
{
    return;
}

/**
  * @brief  Gets flags of the interrupt.
  * @retval Flags of the interrupt.
  */
uint32_t ald_usb_dma_get_interrupt_flag(void)
{
    return;
}

/**
  * @brief  Gets the status of the error.
  * @param  ch: Channel.
  * @retval Status.
  */
uint32_t ald_usb_dma_get_channel_error(uint8_t ch)
{
    return 0;
}

/**
  * @brief  Clear the status of the error.
  * @param  ch: Channel.
  * @retval None
  */
void ald_usb_dma_clear_channel_error(uint8_t ch)
{
    return;
}

#endif
/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group8 LPM functions
  * @brief LPM functions
  * @{
  */
/**
  * @brief  Gets status of remote wakeup.
  * @retval Status.
  */
uint32_t ald_usb_lpm_remote_wake_is_enable(void)
{
    return 1;
}

/**
  * @brief  Gets the link status
  * @retval Status
  */
uint32_t ald_usb_lpm_link_status_get(void)
{
    return 0;
}

/**
  * @brief  Gets the index of the endpoint.
  * @retval Index of the endpoint.
  */
uint32_t ald_usb_lpm_ep_get(void)
{
    return 0;
}

/**
  * @brief  Gets the status of the interrupt.
  * @retval Status.
  */
uint32_t ald_usb_lpm_int_status_get(void)
{
    return 0;
}

/**
  * @brief  Disable the LPM interrupt.
  * @retval None
  */
void ald_usb_lpm_int_disable(uint32_t ints)
{
    return;
}

/**
  * @brief  Enable the LPM interrupt.
  * @retval None
  */
void ald_usb_lpm_int_enable(uint32_t ints)
{
    return;
}

/**
  * @brief  Transmit a LPM transaction in host mode.
  * @param  addr: Address.
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_lpm_send(uint32_t addr, uint32_t ep_idx)
{
    return;
}

/**
  * @brief  Configure the LPM parameters in host mode.
  * @param  resume_time: Resume time.
  * @param  config: Parameters
  * @retval None
  */
void ald_usb_host_lpm_config(uint32_t resume_time, uint32_t config)
{
    return;
}

/**
  * @brief  Initiate a RESUME from the L1 state in host mode.
  * @retval None
  */
void ald_usb_host_lpm_resume(void)
{
    return;
}

/**
  * @brief  Enable remote wakeup in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_remote_wake(void)
{
    return;
}

/**
  * @brief  Enable remote wakeup in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_config(uint32_t config)
{
    return;
}

/**
  * @brief  Enable LPM in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_enable(void)
{
    return;
}

/**
  * @brief  Disable LPM in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_disable(void)
{
    return;
}

/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group10 LPM functions
  * @brief USB SWVBUS control
  * @{
  */
/**
  * @brief  Selet the control mode of VBUS.
  * @param  sigctl: 0, indicates that use the hardware control
  *         sigctl: 1, indicates that use the software control.
  * @retval Status.
  */
void ald_usb_swvbus_sigctl_set(uint8_t sigctl)
{
    if (sigctl == 1)
    {
        USB->SWVBUS |= 0x01 << 0;
    }
    else
    {
        USB->SWVBUS &= ~(0x01 << 0);
    }
    return;
}

/**
  * @brief  Selet the control mode of VBUS.
  * @param  None.
  * @retval Status: 0, indicates that use the hardware control
  *         Status: 1, indicates that use the software control.
  */
uint8_t ald_usb_swvbus_sigctl_get(void)
{
    return (USB->SWVBUS & (0x01 << 0));
}

/**
  * @brief  Set session end threshold.
  * @param  thd: 0, indicates that lower than the session end threshold
  *         thd: 1, indicates that higher than the session end threshold.
  * @retval Status.
  */
void ald_usb_swvbus_sesendth_set(uint8_t thd)
{
    if (thd == 1)
    {
        USB->SWVBUS |= 0x01 << 1;
    }
    else
    {
        USB->SWVBUS &= ~(0x01 << 1);
    }
    return;
}

/**
  * @brief  Set session end threshold.
  * @param  None.
  * @retval Status: 0, indicates that lower than the session end threshold
  *         Status: 1, indicates that higher than the session end threshold.
  */
uint8_t ald_usb_swvbus_sesendth_get(void)
{
    return (USB->SWVBUS & (0x01 << 1));
}

/**
  * @brief  Set session valid threshold.
  * @param  thd: 0, indicates that lower than the session valid threshold
            thd: 1, indicates that higher than the session valid threshold.
  * @retval Status.
  */
void ald_usb_swvbus_sesvalth_set(uint8_t thd)
{
    if (thd == 1)
    {
        USB->SWVBUS |= 0x01 << 2;
    }
    else
    {
        USB->SWVBUS &= ~(0x01 << 2);
    }
    return;
}

/**
  * @brief  Set session valid threshold.
  * @param  None.
  * @retval Status: 0, indicates that lower than the session valid threshold
            Status: 1, indicates that higher than the session valid threshold.
  */
uint8_t ald_usb_swvbus_sesvalth_get(void)
{
    return (USB->SWVBUS & (0x01 << 2));
}

/**
  * @brief  Set VBUS valid threshold.
  * @param  thd: 0, indicates that lower than the vbus valid threshold
            thd: 1, indicates that higher than the vbus valid threshold.
  * @retval Status.
  */
void ald_usb_swvbus_valth_set(uint8_t thd)
{
    if (thd == 1)
    {
        USB->SWVBUS |= 0x01 << 3;
    }
    else
    {
        USB->SWVBUS &= ~(0x01 << 3);
    }
    return;
}

/**
  * @brief  Set VBUS valid threshold.
  * @param  None.
  * @retval Status: 0, indicates that lower than the vbus valid threshold
            Status:thd: 1, indicates that higher than the vbus valid threshold.
  */
uint8_t ald_usb_swvbus_valth_get(void)
{
    return (USB->SWVBUS & (0x01 << 3));
}

/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group11 components initialization functions
  * @brief USB components initialization
  * @{
  */
/**
  * @brief  Initialize usb host components.
  * @retval None
  */
void ald_usb_host_components_init(void)
{
    WRITE_REG(SYSCFG->PROT, 0x55AA6996U);
    RMU->AHB1RSTR |= 0x40;
    RMU->AHB1RSTR &= 0xFFFFFFBF;
    WRITE_REG(SYSCFG->PROT, 0x0);

    /* Config EP0 */
    ald_usb_host_ep_config(ALD_USB_EP_0, 64, 0, 0, (ALD_USB_EP_MODE_CTRL | ALD_USB_EP_SPEED_FULL | ALD_USB_EP_HOST_OUT));

    /* Clear interrupts */


    /* Enable PHY power */
    ald_usb_host_pwr_enable();
    /* clear hnp session */
    ald_usb_otg_session_request(false);

    /* set vbus control mode and threshold value */
    ald_usb_swvbus_sigctl_set(1);
    ald_usb_swvbus_sesendth_set(1);
    ald_usb_swvbus_sesvalth_set(1);
    ald_usb_swvbus_valth_set(1);
    /* Pull down DP and DM */
    ald_usb_dppud_set(ALD_USB_DPDM_PUSH_DOWN);
    ald_usb_dmpud_set(ALD_USB_DPDM_PUSH_DOWN);
    /* software control CID */
    ald_usb_swcid_cidctrl(1);
    /* force to host mode */
    ald_usb_swcid_host(0);
    /* start host request */
    ald_usb_mode_host_req();
    /* Start hnp */
    ald_usb_otg_session_request(true);

    /* Clear interrupts */
    ald_usb_int_status_get();
    /* Init interrupts */
    ald_usb_int_enable(ALD_USB_INTCTRL_SESSION | ALD_USB_INTCTRL_DISCONNECT | ALD_USB_INTCTRL_CONNECT | ALD_USB_INTCTRL_SOF |
                ALD_USB_INTCTRL_BABBLE | ALD_USB_INTCTRL_RESUME);
    ald_usb_int_enable_ep(ALD_USB_INTEP_ALL);
    ald_usb_int_register();

    return;
}

/**
  * @brief  Initialize usb device components.
  * @retval None
  */
void ald_usb_device_components_init(void)
{
    ald_usb_otg_session_request(true);
#if (defined(ES32VF2264))
    ald_usb_dppud_set(ALD_USB_DPDM_FLOATING);/*测试板的USBDP(PA12)，上拉到3.3V。具体情况请参考ReadMe.txt*/
#else
    ald_usb_dppud_set(USB_DPDM_PUSH_UP);
#endif /* ES32VF2264 */
    /* software control CID */
    ald_usb_swcid_cidctrl(1);
    /* force to dev mode */
    ald_usb_swcid_host(1);
    ald_usb_dev_suspend_enable();

    return;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* ALD_USB */
/**
  * @}
  */

/**
  * @}
  */
