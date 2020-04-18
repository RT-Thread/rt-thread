/**
  *********************************************************************************
  *
  * @file    ald_usb.c
  * @brief   USB module driver.
  *
  * @version V1.0
  * @date    25 Dec 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_usb.h"
#include "ald_syscfg.h"

/** @addtogroup ES32FXXX_ALD
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
	return USB0->FRAME;
}

/**
  * @brief  Request the session.
  * @param  start: true/false.
  * @retval None
  */
void ald_usb_otg_session_request(bool start)
{
	if (start)
		USB0->DEVCTL |= USB_DEVCTL_SESSION;
	else
		USB0->DEVCTL &= ~(USB_DEVCTL_SESSION);
}

/**
  * @brief  Gets the mode.
  * @retval Mode
  */
uint32_t ald_usb_mode_get(void)
{
	return USB0->DEVCTL & (USB_DEVCTL_DEV | USB_DEVCTL_HOST
			 | USB_DEVCTL_SESSION | USB_DEVCTL_VBUS_M);
}

/**
  * @brief  Enable/Disable the high mode.
  * @param  enable: ENABLE/DISABLE.
  * @retval None
  */
void ald_usb_high_speed_enable(bool enable)
{
	if (enable)
		USB0->POWER |= USB_POWER_HS_EN;
	else
		USB0->POWER &= ~(USB_POWER_HS_EN);
}

/**
  * @brief  Gets the speed of the device.
  * @retval Type of the speed.
  */
uint32_t ald_usb_device_speed_get(void)
{
	if (USB0->POWER & USB_POWER_HS_EN)
		return USB_HIGH_SPEED;

	return USB_FULL_SPEED;
}

/**
  * @brief  Gets the number of the endpoint.
  * @retval Number of the endpoint.
  */
uint32_t ald_usb_num_ep_get( void)
{
	return NUM_USB_EP;
}

/**
  * @brief  Reset USB Control.
  * @retval None
  */
void ald_usb_control_reset(void)
{
	ald_rmu_reset_periperal(RMU_PERH_USB);
}

/**
  * @brief  Output USB clock via PA15, 60MHz/256=234.375KHz.
  * @retval None
  */
void ald_usb_clock_output(void)
{
	SYSCFG_UNLOCK();
	SYSCFG->TESTKEY = 0x5A962814;
	SYSCFG->TESTKEY = 0xE7CB69A5;
	SYSCFG->USBTEST = 0x43;

	return;
}

/**
  * @brief  Starts eye diagram for high-speed host.
  * @param  buf: Buffer for eye diagram.
  * @param  len: Length of the buffer.
  * @retval Status, 0 means success, other values means failure.
  */
int ald_usb_eye_diagram_start(uint8_t *buf, uint16_t len)
{
	if (len < 53)
		return -1;

	ald_usb_ep_data_put(0, buf, 53);
	USB0->TEST = 0x08 | 0x90;
	ald_delay_ms(20);
	USB0->CSR0L = USB_CSRL0_TXRDY;

	return 0;
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
	return USB0->FADDR;
}

/**
  * @brief  Sets the address.
  * @param  addr: The address which will be set.
  * @retval None
  */
void ald_usb_dev_set_addr(uint8_t addr)
{
	USB0->FADDR = addr;
}

/**
  * @brief  Enable connection.
  * @retval None
  */
void ald_usb_dev_connect(void)
{
	USB0->POWER |= USB_POWER_SOFTCONN;
}

/**
  * @brief  Disable connection.
  * @retval None
  */
void ald_usb_dev_disconnect(void)
{
	USB0->POWER &= ~(USB_POWER_SOFTCONN);
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
	uint32_t tmp = 0;

	if (flags & USB_EP_DEV_IN) {
		USB0->CSR[ep_idx - 1].TXxMAXP = p_max;
		if (flags & USB_EP_AUTO_SET)
			tmp |= USB_TXCSRH1_AUTOSET;
		if ((flags & USB_EP_MODE_MASK) == USB_EP_MODE_ISOC)
			tmp |= USB_TXCSRH1_ISO;

		USB0->CSR[ep_idx - 1].TXxCSRH = (uint8_t)tmp;
		USB0->CSR[ep_idx - 1].TXxCSRL = USB_TXCSRL1_CLRDT;
	}
	else {
		USB0->CSR[ep_idx - 1].RXxMAXP = p_max;
		if (flags & USB_EP_AUTO_CLEAR)
			tmp = USB_RXCSRH1_AUTOCL;
		if (flags & USB_EP_DIS_NYET)
			tmp |= USB_RXCSRH1_DISNYET;

		if ((flags & USB_EP_MODE_MASK) == USB_EP_MODE_ISOC)
			tmp |= USB_RXCSRH1_ISO;

		USB0->CSR[ep_idx - 1].RXxCSRH = (uint8_t)tmp;
		USB0->CSR[ep_idx - 1].RXxCSRL = USB_RXCSRL1_CLRDT;
	}
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

	if (*flags & USB_EP_DEV_IN) {
		*flags = USB_EP_DEV_IN;
		*p_max = (uint32_t)USB0->CSR[ep_idx - 1].TXxMAXP;
		tmp    = (uint32_t)USB0->CSR[ep_idx - 1].TXxCSRH;

		if (tmp & USB_TXCSRH1_AUTOSET)
			*flags |= USB_EP_AUTO_SET;
		if (tmp & USB_TXCSRH1_ISO)
			*flags |= USB_EP_MODE_ISOC;
		else
			*flags |= USB_EP_MODE_BULK;
	}
	else {
		*flags = USB_EP_DEV_OUT;
		*p_max = (uint32_t)USB0->CSR[ep_idx - 1].RXxMAXP;
		tmp    = (uint32_t)USB0->CSR[ep_idx - 1].RXxCSRH;

		if (tmp & USB_RXCSRH1_AUTOCL)
			*flags |= USB_EP_AUTO_CLEAR;
		if (tmp & USB_RXCSRH1_ISO)
			*flags |= USB_EP_MODE_ISOC;
		else
			*flags |= USB_EP_MODE_BULK;
	}
}

/**
  * @brief  Acknowledge the data from the host.
  * @param  ep_idx: Index of the endpoint
  * @param  last: true/false
  * @retval None
  */
void ald_usb_dev_ep_data_ack(uint32_t ep_idx, bool last)
{
	if (ep_idx == USB_EP_0)
		USB0->CSR0L = USB_CSRL0_RXRDYC | (last ? USB_CSRL0_DATAEND : 0);
	else
		USB0->CSR[ep_idx - 1].RXxCSRL &= ~(USB_RXCSRL1_RXRDY);
}

/**
  * @brief  Stall the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_dev_ep_stall(uint32_t ep_idx, uint32_t flags)
{
	if (ep_idx == USB_EP_0)
		USB0->CSR0L |= (USB_CSRL0_STALL | USB_CSRL0_RXRDYC);
	else if (flags == USB_EP_DEV_IN)
		USB0->CSR[ep_idx - 1].TXxCSRL |= USB_TXCSRL1_STALL;
	else
		USB0->CSR[ep_idx - 1].RXxCSRL |= USB_RXCSRL1_STALL;
}

/**
  * @brief  Cancel the stall status.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_dev_ep_stall_clear(uint32_t ep_idx, uint32_t flags)
{
	if (ep_idx == USB_EP_0)
		USB0->CSR0L &= ~USB_CSRL0_STALLED;
	else if (flags == USB_EP_DEV_IN) {
		USB0->CSR[ep_idx - 1].TXxCSRL &= ~(USB_TXCSRL1_STALL | USB_TXCSRL1_STALLED);
		USB0->CSR[ep_idx - 1].TXxCSRL |= USB_TXCSRL1_CLRDT;
	}
	else {
		USB0->CSR[ep_idx - 1].RXxCSRL &= ~(USB_RXCSRL1_STALL | USB_RXCSRL1_STALLED);
		USB0->CSR[ep_idx - 1].RXxCSRL |= USB_RXCSRL1_CLRDT;
	}
}

/**
  * @brief  Clear the status of the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_dev_ep_status_clear(uint32_t ep_idx, uint32_t flags)
{
	if (ep_idx == USB_EP_0) {
		if (flags & USB_DEV_EP0_OUT_PKTRDY)
			USB0->CSR0L |= USB_CSRL0_RXRDYC;
		if (flags & USB_DEV_EP0_SETUP_END)
			USB0->CSR0L |= USB_CSRL0_SETENDC;
		if (flags & USB_DEV_EP0_SENT_STALL)
			USB0->CSR0L &= ~(USB_DEV_EP0_SENT_STALL);
	}
	else {
		USB0->CSR[ep_idx - 1].TXxCSRL &= ~(flags & (USB_DEV_TX_SENT_STALL | USB_DEV_TX_UNDERRUN));
		USB0->CSR[ep_idx - 1].RXxCSRL &= ~((flags & (USB_DEV_RX_SENT_STALL | USB_DEV_RX_DATA_ERROR
						 | USB_DEV_RX_OVERRUN)) >> USB_RX_EPSTATUS_SHIFT);
	}
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
	if (flags & USB_EP_HOST_OUT)
		return USB0->ADDR[ep_idx].TXxFUNCADDR;
	else
		return USB0->ADDR[ep_idx].RXxFUNCADDR;
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
	if (flags & USB_EP_HOST_OUT)
		USB0->ADDR[ep_idx].TXxFUNCADDR = addr;
	else
		USB0->ADDR[ep_idx].RXxFUNCADDR = addr;
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
	uint32_t tmp;

	if (ep_idx == USB_EP_0) {
		USB0->NACK = nak_val;

		if (flags & USB_EP_SPEED_HIGH)
			USB0->TYPE0 = USB_TYPE0_SPEED_HIGH;
		else if (flags & USB_EP_SPEED_FULL)
			USB0->TYPE0 = USB_TYPE0_SPEED_FULL;
		else
			USB0->TYPE0 = USB_TYPE0_SPEED_LOW;
	}
	else {
		tmp = t_ep;

		if (flags & USB_EP_SPEED_HIGH)
			tmp |= USB_TXTYPE1_SPEED_HIGH;
		else if (flags & USB_EP_SPEED_FULL)
			tmp |= USB_TXTYPE1_SPEED_FULL;
		else
			tmp |= USB_TXTYPE1_SPEED_LOW;

		switch (flags & USB_EP_MODE_MASK) {
		case USB_EP_MODE_BULK:
			tmp |= USB_TXTYPE1_PROTO_BULK;
			break;

		case USB_EP_MODE_ISOC:
			tmp |= USB_TXTYPE1_PROTO_ISOC;
			break;

		case USB_EP_MODE_INT:
			tmp |= USB_TXTYPE1_PROTO_INT;
			break;

		case USB_EP_MODE_CTRL:
			tmp |= USB_TXTYPE1_PROTO_CTRL;
			break;
		}

		if (flags & USB_EP_HOST_OUT) {
			USB0->CSR[ep_idx - 1].TXxTYPE     = tmp;
			USB0->CSR[ep_idx - 1].TXxINTERVAL = nak_val;
			USB0->CSR[ep_idx - 1].TXxMAXP     = p_max;

			tmp = 0;
			if (flags & USB_EP_AUTO_SET)
				tmp |= USB_TXCSRH1_AUTOSET;
			USB0->CSR[ep_idx - 1].TXxCSRH = (uint8_t)tmp;
		}
		else {
			USB0->CSR[ep_idx - 1].RXxTYPE     = tmp;
			USB0->CSR[ep_idx - 1].RXxINTERVAL = nak_val;
			USB0->CSR[ep_idx - 1].RXxMAXP     = p_max;

			tmp = 0;
			if (flags & USB_EP_AUTO_CLEAR)
				tmp |= USB_RXCSRH1_AUTOCL;
			if (flags & USB_EP_AUTO_REQUEST)
				tmp |= USB_RXCSRH1_AUTORQ;

			USB0->CSR[ep_idx - 1].RXxCSRH = (uint8_t)tmp;
		}
	}
}

/**
  * @brief  Acknowledge the data in host mode.
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_ep_data_ack(uint32_t ep_idx)
{
	if (ep_idx == USB_EP_0)
		USB0->CSR0L &= ~(USB_CSRL0_RXRDY);
	else
		USB0->CSR[ep_idx - 1].RXxCSRL &= ~(USB_RXCSRL1_RXRDY);
}

/**
  * @brief  Toggle the data in host mode.
  * @param  ep_idx: Index of the endpoint.
  * @param  toggle: true/false.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_host_ep_data_toggle(uint32_t ep_idx, bool toggle, uint32_t flags)
{
	uint32_t tmp = 0;

	if (toggle) {
		if (ep_idx == USB_EP_0)
			tmp = USB_CSRH0_DT;
		else if (flags == USB_EP_HOST_IN)
			tmp = USB_RXCSRH1_DT;
		else
			tmp = USB_TXCSRH1_DT;
	}

	if (ep_idx == USB_EP_0) {
		USB0->CSR0H = ((USB0->CSR0H  & ~(USB_CSRH0_DTWE | USB_CSRH0_DT)) |
						(tmp | USB_CSRH0_DTWE));
	}
	else if (flags == USB_EP_HOST_IN) {
		USB0->CSR[ep_idx - 1].RXxCSRH = ((USB0->CSR[ep_idx - 1].RXxCSRH &
							~(USB_RXCSRH1_DTWE | USB_RXCSRH1_DT)) |
							(tmp | USB_RXCSRH1_DTWE));
	}
	else {
		USB0->CSR[ep_idx - 1].TXxCSRH = ((USB0->CSR[ep_idx - 1].TXxCSRH &
							~(USB_TXCSRH1_DTWE | USB_TXCSRH1_DT)) |
							(tmp | USB_TXCSRH1_DTWE));
	}
}

/**
  * @brief  Clear the status of endpoint in host mode.
  * @param  ep_idx: Index of the endpoint.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_host_ep_status_clear(uint32_t ep_idx, uint32_t flags)
{
	if (ep_idx == USB_EP_0) {
		USB0->CSR0L &= ~flags;
	}
	else {
		USB0->CSR[ep_idx - 1].TXxCSRL &= ~flags;
		USB0->CSR[ep_idx - 1].RXxCSRL &= ~flags;
	}
}

/**
  * @brief  Gets the HUB's address.
  * @param  ep_idx: Index of the endpoint.
  * @param  flags: Flags.
  * @retval Address
  */
uint32_t ald_usb_host_hub_addr_get(uint32_t ep_idx, uint32_t flags)
{
	if (flags & USB_EP_HOST_OUT)
		return USB0->ADDR[ep_idx].TXxHUBADDR;
	else
		return USB0->ADDR[ep_idx].RXxHUBADDR;
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
	if (flags & USB_EP_HOST_OUT)
		USB0->ADDR[ep_idx].TXxHUBADDR = addr;
	else
		USB0->ADDR[ep_idx].RXxHUBADDR = addr;

	if (ep_idx == USB_EP_0) {
		if (flags & USB_EP_SPEED_FULL)
			USB0->TYPE0 |= USB_TYPE0_SPEED_FULL;
		else if (flags & USB_EP_SPEED_HIGH)
			USB0->TYPE0 |= USB_TYPE0_SPEED_HIGH;
		else
			USB0->TYPE0 |= USB_TYPE0_SPEED_LOW;
	}
}

/**
  * @brief  Disable power.
  * @retval None
  */
void ald_usb_host_pwr_disable(void)
{
	return;
}

/**
  * @brief  Enable power.
  * @retval None
  */
void ald_usb_host_pwr_enable(void)
{
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
	if (ep_idx == USB_EP_0)
		USB0->CSR0L = USB_RXCSRL1_REQPKT;
	else
		USB0->CSR[ep_idx - 1].RXxCSRL = USB_RXCSRL1_REQPKT;
}

/**
  * @brief  Clear the status of request IN.
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_request_in_clear(uint32_t ep_idx)
{
	if (ep_idx == USB_EP_0)
		USB0->CSR0L &= ~(USB_RXCSRL1_REQPKT);
	else
		USB0->CSR[ep_idx - 1].RXxCSRL &= ~(USB_RXCSRL1_REQPKT);
}

/**
  * @brief  Request data IN at endpoint 0.
  * @retval None
  */
void ald_usb_host_request_status(void)
{
	USB0->CSR0L = USB_CSRL0_REQPKT | USB_CSRL0_STATUS;
}

/**
  * @brief  Reset the USB's bus.
  * @param  start: true/false.
  * @retval None
  */
void ald_usb_host_reset(bool start)
{
	if (start)
		USB0->POWER |= USB_POWER_RESET;
	else
		USB0->POWER &= ~(USB_POWER_RESET);
}

/**
  * @brief  Resume the devices.
  * @param  start: true/false.
  * @retval None
  */
void ald_usb_host_resume(bool start)
{
	if (start)
		USB0->POWER |= USB_POWER_RESUME;
	else
		USB0->POWER &= ~(USB_POWER_RESUME);
}

/**
  * @brief  Suspend the devices.
  * @retval None
  */
void ald_usb_host_suspend(void)
{
	USB0->POWER |= USB_POWER_SUSPEND;
}

/**
  * @brief  Gets the device's speed.
  * @retval Type of the speed.
  */
uint32_t ald_usb_host_speed_get(void)
{
	if (USB0->POWER & USB_POWER_HS_M)
		return USB_HIGH_SPEED;

	if (USB0->DEVCTL & USB_DEVCTL_FSDEV)
		return USB_FULL_SPEED;

	if (USB0->DEVCTL & USB_DEVCTL_LSDEV)
		return USB_LOW_SPEED;

	return USB_UNDEF_SPEED;
}

/**
  * @brief  Sets the endpoint speed.
  * @param  ep_idx: Index of the endpoint.
  * @param  flags: Type of the speed.
  * @retval None
  */
void ald_usb_host_ep_speed_set(uint32_t ep_idx, uint32_t flags)
{
	uint32_t tmp;

	if (flags & USB_EP_SPEED_HIGH)
		tmp = USB_TYPE0_SPEED_HIGH;
	else if (flags & USB_EP_SPEED_FULL)
		tmp = USB_TYPE0_SPEED_FULL;
	else
		tmp = USB_TYPE0_SPEED_LOW;

	if (ep_idx == USB_EP_0)
		USB0->TYPE0 |= tmp;
	else if (flags & USB_EP_HOST_OUT)
		USB0->CSR[ep_idx - 1].TXxTYPE |= tmp;
	else
		USB0->CSR[ep_idx - 1].RXxTYPE |= tmp;
}

/**
  * @brief  Ping the endpoint.
  * @param  ep_idx: Index of the endpoint.
  * @param  enable: ENABLE/DISABLE.
  * @retval None
  */
void ald_usb_host_ep_ping(uint32_t ep_idx, bool enable)
{
	if (enable)
		USB0->CSR0H &= ~(USB_CSRH0_DISPING);
	else
		USB0->CSR0H |= USB_CSRH0_DISPING;
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
	if (ep_idx == USB_EP_0) {
		if ((USB0->CSR0L & USB_CSRL0_RXRDY) == 0)
			return 0;

		return USB0->COUNT0;
	}
	else {
		if ((USB0->CSR[ep_idx - 1].RXxCSRL & USB_CSRL0_RXRDY) == 0)
			return 0;

		return USB0->CSR[ep_idx - 1].RXxCOUNT;
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
	uint32_t i;

	if (ep_idx == USB_EP_0) {
		if ((USB0->CSR0L & USB_CSRL0_RXRDY) == 0) {
			*size = 0;
			return -1;
		}
		i = USB0->COUNT0;
	}
	else {
		if ((USB0->CSR[ep_idx - 1].RXxCSRL & USB_CSRL0_RXRDY) == 0) {
			*size = 0;
			return -1;
		}
		i = USB0->CSR[ep_idx - 1].RXxCOUNT;
	}

	i     = (i < *size) ? i : *size;
	*size = i;

	for (; i > 0; i--)
		*data++ = USB0->FIFO[ep_idx].Byte[0];

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
	if (ep_idx == USB_EP_0) {
		if (USB0->CSR0L & USB_CSRL0_TXRDY)
			return -1;
	}
	else {
		if (USB0->CSR[ep_idx - 1].TXxCSRL & USB_TXCSRL1_TXRDY)
			return -1;
	}

	for (; size > 0; size--)
		USB0->FIFO[ep_idx].Byte[0] = *data++;

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

	if (ep_idx == USB_EP_0) {
		if (USB0->CSR0L & USB_CSRL0_TXRDY)
			return -1;

		tmp = tx_type & 0xff;
		USB0->CSR0L = tmp;
	}
	else {
		if (USB0->CSR[ep_idx - 1].TXxCSRL & USB_TXCSRL1_TXRDY)
			return -1;

		tmp = (tx_type >> 8) & 0xff;
		USB0->CSR[ep_idx - 1].TXxCSRL = tmp;
	}

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
	if (flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN))
		USB0->CSR[ep_idx - 1].TXxCSRL |= USB_TXCSRL1_CLRDT;
	else
		USB0->CSR[ep_idx - 1].RXxCSRL |= USB_RXCSRL1_CLRDT;
}

/**
  * @brief  Sets the size of request data IN
  * @param  ep_idx: Index of the endpoint
  * @param  count: Size of request data IN.
  * @retval None
  */
void ald_usb_ep_req_packet_count(uint32_t ep_idx, uint32_t count)
{
	USB0->EP_RQPKTCOUNT[ep_idx - 1] = count;
}

/**
  * @brief  Gets the status of the endpoint.
  * @param  ep_idx: Index of the endpoint
  * @retval Status.
  */
uint32_t ald_usb_ep_status(uint32_t ep_idx)
{
	uint32_t status;

	if (ep_idx == USB_EP_0) {
		status  = USB0->CSR0L;
		status |= (USB0->CSR0H) << USB_RX_EPSTATUS_SHIFT;
	}
	else {
		status  = USB0->CSR[ep_idx - 1].TXxCSRL;
		status |= USB0->CSR[ep_idx - 1].TXxCSRH << 8;
		status |= USB0->CSR[ep_idx - 1].RXxCSRL << 16;
		status |= USB0->CSR[ep_idx - 1].RXxCSRH << 24;
	}

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
	if (ep_idx == USB_EP_0)
		return;

	if (en) {
		switch (flag) {
		case USB_DMA_EP_CFG_TX:
			USB0->CSR[ep_idx - 1].TXxCSRH |= USB_DMA_EP_TX_MSK;
			break;
		case USB_DMA_EP_CFG_RX_DEV:
			USB0->CSR[ep_idx - 1].RXxCSRH |= USB_DMA_EP_RX_DEV_MSK;
			break;
		case USB_DMA_EP_CFG_RX_HOST:
			USB0->CSR[ep_idx - 1].RXxCSRH |= USB_DMA_EP_RX_HOST_MSK;
			break;
		default:
			break;
		}
	}
	else {
		switch (flag) {
		case USB_DMA_EP_CFG_TX:
			USB0->CSR[ep_idx - 1].TXxCSRH &= ~(USB_DMA_EP_TX_MSK);
			break;
		case USB_DMA_EP_CFG_RX_DEV:
			USB0->CSR[ep_idx - 1].RXxCSRH &= ~(USB_DMA_EP_RX_DEV_MSK);
			break;
		case USB_DMA_EP_CFG_RX_HOST:
			USB0->CSR[ep_idx - 1].RXxCSRH &= ~(USB_DMA_EP_RX_HOST_MSK);
			break;
		default:
			break;
		}
	}

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
	return (uint32_t)&USB0->FIFO[ep_idx].Word;
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
	uint32_t tmp = USB0->INDEX;

	USB0->INDEX = ep_idx;

	if (flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN)) {
		*addr = (USB0->TXFIFOADD << 3);
		*size = (USB0->TXFIFOSIZE & 0xF);
	}
	else {
		*addr = (USB0->RXFIFOADD << 3);
		*size = (USB0->RXFIFOSIZE & 0xF);
	}

	USB0->INDEX = tmp;
	return;
}

/**
  * @brief  Sets the parameters of the FIFO.
  * @param  ep_idx: Index of the endpoint
  * @param  addr: Address.
  * @param  size: Size of FIFO.
  * @param  flags: Flags.
  * @retval None
  */
void ald_usb_fifo_config_set(uint32_t ep_idx, uint32_t addr, uint32_t size, uint32_t flags)
{
	uint32_t tmp = USB0->INDEX;

	USB0->INDEX = ep_idx;

	if (flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN)) {
		USB0->TXFIFOADD  = (addr >> 3);
		USB0->TXFIFOSIZE = (size & 0xF);
	}
	else {
		USB0->RXFIFOADD  = (addr >> 3);
		USB0->RXFIFOSIZE = (size & 0xF);
	}

	USB0->INDEX = tmp;
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
	if (ep_idx == USB_EP_0) {
		if ((USB0->CSR0L & (USB_CSRL0_RXRDY | USB_CSRL0_TXRDY)) != 0)
			USB0->CSR0H |= USB_CSRH0_FLUSH;
	}
	else {
		if (flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN)) {
			if (USB0->CSR[ep_idx - 1].TXxCSRL & USB_TXCSRL1_TXRDY)
				USB0->CSR[ep_idx - 1].TXxCSRL |= USB_TXCSRL1_FLUSH;
		}
		else {
			if (USB0->CSR[ep_idx - 1].RXxCSRL & USB_RXCSRL1_RXRDY)
				USB0->CSR[ep_idx - 1].RXxCSRL |= USB_RXCSRL1_FLUSH;
		}
	}
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
	if (flags & USB_INTCTRL_STATUS)
		USB0->USBIE &= ~(flags & USB_INTCTRL_STATUS);
}

/**
  * @brief  Enable interrupt.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_enable(uint32_t flags)
{
	if (flags & USB_INTCTRL_STATUS)
		USB0->USBIE |= flags ;
}

/**
  * @brief  Gets the status of the interrupt.
  * @retval Status.
  */
uint32_t ald_usb_int_status_get(void)
{
	return USB0->USBIS;
}

/**
  * @brief  Disable interrupt of the endpoint.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_disable_ep(uint32_t flags)
{
	USB0->TXIE &= ~(flags & (USB_INTEP_HOST_OUT | USB_INTEP_DEV_IN | USB_INTEP_0));
	USB0->RXIE &= ~((flags & (USB_INTEP_HOST_IN | USB_INTEP_DEV_OUT)) >> USB_INTEP_RX_SHIFT);
}

/**
  * @brief  Enable interrupt of the endpoint.
  * @param  flags: Type of the interrupt.
  * @retval None
  */
void ald_usb_int_enable_ep(uint32_t flags)
{

	USB0->TXIE |= flags & (USB_INTEP_HOST_OUT | USB_INTEP_DEV_IN | USB_INTEP_0);
	USB0->RXIE |= ((flags & (USB_INTEP_HOST_IN | USB_INTEP_DEV_OUT)) >> USB_INTEP_RX_SHIFT);
}

/**
  * @brief  Gets the ststus of the endpoint interrupt.
  * @retval Status.
  */
uint32_t ald_usb_int_status_ep_get(void)
{
	uint32_t status;

	status = USB0->TXIS;
	status |= (USB0->RXIS << USB_INTEP_RX_SHIFT);

	return status;
}

/**
  * @brief  Register USB's interrupt.
  * @retval None
  */
void ald_usb_int_register(void)
{
	ald_mcu_irq_config(USB_INT_IRQn, 2, 2, ENABLE);

}

/**
  * @brief  Unregister USB's interrupt.
  * @retval None
  */
void ald_usb_int_unregister(void)
{
	ald_mcu_irq_config(USB_INT_IRQn, 2, 2, DISABLE);
}

/**
  * @brief  Get USB's interrupt number.
  * @retval None
  */
uint32_t ald_usb_int_num_get(void)
{
	return USB_INT_IRQn;
}
/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group7 DMA functions
  * @brief DMA functions
  * @{
  */
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
	USB0->DMA_CH[ch].DMA_ADDR  = addr;
	USB0->DMA_CH[ch].DMA_COUNT = count;
	USB0->DMA_CH[ch].DMA_CNTL  = ctrl;
	return;
}

/**
  * @brief  Start multiple receive.
  * @param  ep_idx: Index of the endpoint
  * @retval None
  */
void ald_usb_dma_mult_recv_start(uint32_t ep_idx)
{
	USB0->CSR[ep_idx - 1].RXxCSRH &= ~(USB_RXCSRH1_DMAMOD);
	return;
}


/**
  * @brief  Start DMA's machine.
  * @param  ch: Channel.
  * @retval None
  */
void ald_usb_dma_channel_start(uint8_t ch)
{
	USB0->DMA_CH[ch].DMA_CNTL |= 0x1;
	return;
}

/**
  * @brief  Stop DMA's machine.
  * @param  ch: Channel.
  * @retval None
  */
void ald_usb_dma_channel_stop(uint8_t ch)
{
	USB0->DMA_CH[ch].DMA_CNTL &= ~0x1;
	return;
}

/**
  * @brief  Gets flags of the interrupt.
  * @retval Flags of the interrupt.
  */
uint32_t ald_usb_dma_get_interrupt_flag(void)
{
	return USB0->DMA_INTR;
}

/**
  * @brief  Gets the status of the error.
  * @param  ch: Channel.
  * @retval Status.
  */
uint32_t ald_usb_dma_get_channel_error(uint8_t ch)
{
	if (USB0->DMA_CH[ch].DMA_CNTL & USB_DMA_CH_ERR_MSK)
		return 1;

	return 0;
}

/**
  * @brief  Clear the status of the error.
  * @param  ch: Channel.
  * @retval None
  */
void ald_usb_dma_clear_channel_error(uint8_t ch)
{
	USB0->DMA_CH[ch].DMA_CNTL &= ~(USB_DMA_CH_ERR_MSK);
}
/**
  * @}
  */

/** @defgroup USB_Public_Functions_Group8 LPM functions
  * @brief LPM functions
  * @{
  */
/**
  * @brief  Transmit a LPM transaction in host mode.
  * @param  addr: Address.
  * @param  ep_idx: Index of the endpoint.
  * @retval None
  */
void ald_usb_host_lpm_send(uint32_t addr, uint32_t ep_idx)
{
	uint32_t tmp;

	USB0->LPM_FADDR = addr;

	tmp = USB0->LPM_ATTR & ~(USB_LPMATTR_ENDPT_M);
	tmp |= ep_idx << USB_LPMATTR_ENDPT_S;

	USB0->LPM_ATTR = tmp;
	USB0->LPM_CNTRL |= USB_LPMCNTRL_LPMXMT;
}

/**
  * @brief  Configure the LPM parameters in host mode.
  * @param  resume_time: Resume time.
  * @param  config: Parameters
  * @retval None
  */
void ald_usb_host_lpm_config(uint32_t resume_time, uint32_t config)
{
	uint32_t tmp;

	tmp  = USB0->LPM_ATTR;
	tmp &= ~(USB_LPMATTR_HIRD_M);
	tmp |= ((((resume_time - 50) / 75) & 0xF) << USB_LPMATTR_HIRD_S);
	tmp |= config;
	USB0->LPM_ATTR = tmp;
}

/**
  * @brief  Gets status of remote wakeup.
  * @retval Status.
  */
uint32_t ald_usb_lpm_remote_wake_is_enable(void)
{
	if (USB0->LPM_ATTR & USB_LPMATTR_RMTWAK)
		return 1;

	return 0;
}

/**
  * @brief  Initiate a RESUME from the L1 state in host mode.
  * @retval None
  */
void ald_usb_host_lpm_resume(void)
{
	USB0->LPM_CNTRL |= USB_LPMCNTRL_LPMRES;
}

/**
  * @brief  Enable remote wakeup in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_remote_wake(void)
{
	USB0->LPM_CNTRL |= USB_LPMCNTRL_LPMRES;
}

/**
  * @brief  Enable remote wakeup in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_config(uint32_t config)
{
	USB0->LPM_CNTRL = config;
}

/**
  * @brief  Enable LPM in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_enable(void)
{
	USB0->LPM_CNTRL |= (USB_LPMCNTRL_LPMXMT | USB_LPMCNTRL_ENABLE);
}

/**
  * @brief  Disable LPM in device mode.
  * @retval None
  */
void ald_usb_dev_lpm_disable(void)
{
	USB0->LPM_CNTRL &= ~(USB_LPMCNTRL_LPMXMT);
}

/**
  * @brief  Gets the link status
  * @retval Status
  */
uint32_t ald_usb_lpm_link_status_get(void)
{
	return (USB0->LPM_ATTR & USB_LPMATTR_LS_M);
}

/**
  * @brief  Gets the index of the endpoint.
  * @retval Index of the endpoint.
  */
uint32_t ald_usb_lpm_ep_get(void)
{
	uint32_t tmp;

	tmp  = USB0->LPM_ATTR;
	tmp &= USB_LPMATTR_ENDPT_M;
	tmp  = tmp >> USB_LPMATTR_ENDPT_S;

	return tmp;
}

/**
  * @brief  Gets the status of the interrupt.
  * @retval Status.
  */
uint32_t ald_usb_lpm_int_status_get(void)
{
	return USB0->LPM_INTR;
}

/**
  * @brief  Disable the LPM interrupt.
  * @retval None
  */
void ald_usb_lpm_int_disable(uint32_t ints)
{
	USB0->LPM_INTREN &= ~ints;
}

/**
  * @brief  Enable the LPM interrupt.
  * @retval None
  */
void ald_usb_lpm_int_enable(uint32_t ints)
{
	USB0->LPM_INTREN |= ints;
}
/**
  * @}
  */

/**
  * @}
  */
#endif
/**
  * @}
  */

/**
  * @}
  */
