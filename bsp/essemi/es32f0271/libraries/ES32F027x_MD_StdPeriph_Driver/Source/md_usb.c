/**
  **************************************************************************************
  * @file    md_usb.c
  * @brief   USB Source File of MD Library.
  * @data    03/12/2018
  * @author  Eastsoft AE Team
  * @note
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *
  **************************************************************************************
  */

/* Incudes -------------------------------------------------------------------*/
#include "es32f0271.h"
#include "stdint.h"
#include <stdbool.h>
#include "usblib\drivers\usb_lowlayer_api.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (USB)

/** @defgroup USB USB
  * @brief USB micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
#define INTERRUPT_MASK_HOST  0x7e
#define INTERRUPT_MASK_DEV   0x6f

/* Private macros -------------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------*/

/* Public functions -----------------------------------------------------------*/
/** @addtogroup USB_MD_Public_Functions USB Public Functions
  * @{
  */

/** @addtogroup USB_MD_PF_SYS USB Public System Functions
  * @{
  */

/**
  * @brief  Mask all interrupts except NMI and Hardfault.
  * @param  None.
  * @retval None.
  */
void md_usb_system_int_disable(void)
{
  __set_PRIMASK(1);
}

/**
  * @brief  Enable all interrupts.
  * @param  None.
  * @retval None.
  */
void md_usb_system_int_enable(void)
{
  __set_PRIMASK(0);
}

/**
  * @brief  Reconfig USB.
  *
  *         This config USB clock to xx MHz as the default configuration.
  *         If user want to change the clock,just redefine the
  *         md_usb_re_config() function.
  * @param  Device Chose device is in device mode or host mode.
  * @retval None.
  */
__weak void md_usb_re_config(bool Device)
{
  //
  // Config FIFO size of endpoint 0.
  // No configuration required for ES32F0271.
  //

  //
  // For ES32F0271,full-speed is supported in device mode,
  // Both full-speeed and low-speed is supported in host mode.
  //
  if (Device == true)
  {
    //
    // DP pin pull up, in full-speed mode.
    //
    USB->DPDMCTRL |= (0X01 << USB_DPDMCTL_DPPUD_POSS);

    //
    // Enable CID hardware control.
    //
    USB->SWCID &= ~USB_SWCID_CIDCTRL_MSK;
  }
  else
  {
    //
    // DM\DP pin pull down, in host mode.
    // Connect USN PHY power.
    //
    USB->DPDMCTRL = (0X02 << USB_DPDMCTL_DPPUD_POSS) |
                    (0X02 << USB_DPDMCTL_DMPUD_POSS) |
                    (USB_DPDMCTL_PHYPWREN_MSK);
    //
    // Enable CID hardware control.
    //
    USB->SWCID &= ~USB_SWCID_HOST_MSK;

    //
    // Enable CID hardware control.
    //
    USB->SWCID &= ~USB_SWCID_CIDCTRL_MSK;
  }
}

/**
  * @brief  Delay ticks ms.
  * @param  ticks The delay ticks.
  * @retval None.
  */
__weak void md_usb_system_delayms(uint32_t ticks)
{

}

/**
  * @brief  Disable systic.
  * @param  None.
  * @retval None.
  */
void md_usb_systic_disable(void)
{
  SysTick->CTRL &= (~SysTick_CTRL_ENABLE_Msk);
}

/**
  * @brief  Reset colck of USB controller.
  * @param  None.
  * @retval None.
  */
void md_usb_controller_reset(void)
{
  RCU->AHBRST |= RCU_AHBRST_USBEN_MSK;
  RCU->AHBRST &= ~RCU_AHBRST_USBEN_MSK;
}

/**
  * @brief  Enable colck of USB controller.
  * @param  None.
  * @retval None.
  */
void md_usb_controller_enable(void)
{
  RCU->AHBEN |= RCU_AHBEN_USBEN_MSK;
}

/**
  * @brief  Disable colck of USB controller.
  * @param  None.
  * @retval None.
  */
void md_usb_controller_disable(void)
{
  RCU->AHBEN &= ~RCU_AHBEN_USBEN_MSK;
}

/**
  * @brief  Enable phy colck of USB controller.
  *
  *         This function enables clock of USB.To use USB,first,
  *         open its clock,then enable USB peripheral by clock
  *         clock manage peripheral.
  *
  * @param  None.
  * @retval None.
  */
void md_usb_clk_phy_enable(void)
{
  //
  // Make sure the PLL1 has not been enabled.
  //
  if ((RCU->CON & RCU_CON_PLL1RDY_MSK)
      && (RCU->CON & RCU_CON_PLL1ON_MSK))
  {
    return;
  }

  //
  //Open PLL1 and wait it is ready.
  //
  RCU->CON |= RCU_CON_PLL1ON_MSK;

  while ((RCU->CON & RCU_CON_PLL1RDY_MSK) == 0);
}

/**
  * @brief  Disable phy colck of USB controller.
  * @param  None.
  * @retval None.
  */
void md_usb_clk_phy_disable(void)
{
  //
  // Close PLL1.
  //
  RCU->CON &= ~RCU_CON_PLL1ON_MSK;
}

/**
  * @brief  Get the USB interrupt number of NVIC.
  * @param  None.
  * @retval None.
  */
uint32_t md_usb_nvic_number_get(void)
{
  return (uint32_t)USB_IRQn;
}

/**
  * @brief  Config the USB interrupt of NVIC.
  * @note   The default priority is 1.
  * @param  None.
  * @retval None.
  */
__weak void md_usb_nvic_config(uint32_t NvicNum)
{
  NVIC_SetPriority((IRQn_Type)NvicNum, 1);
}

/**
  * @brief  Enable the USB interrupt of NVIC.
  * @param  None.
  * @retval None.
  */
void md_usb_nvic_enable(void)
{
  NVIC_EnableIRQ((IRQn_Type)USB_IRQn);
}

/**
  * @brief  Disable the USB interrupt of NVIC.
  * @param  None.
  * @retval None.
  */
void md_usb_nvic_disable(void)
{
  NVIC_DisableIRQ((IRQn_Type)USB_IRQn);
}

/**
  * @} USB_MD_PF_SYS
  */

/** @addtogroup USB_MD_PF_BASIC USB Public Basic Functions
  * @{
  */

/**
  * @brief  Handles the USB bus reset condition.
  *
  *         When this function is called with the \e bStart parameter set to \b true,
  *         this function causes the start of a reset condition on the USB bus.
  *         The caller must then delay at least 20ms before calling this function
  *         again with the \e bStart parameter set to \b false.
  *
  * @param  bStart specifies whether to start or stop signaling reset on the USB
  *         bus.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_reset(bool bStart)
{
  //
  // Send a reset signal to the bus.
  //
  if (bStart)
  {
    USB->POWER |= USB_POWER_RESET_MSK;
  }
  else
  {
    USB->POWER &= ~USB_POWER_RESET_MSK;
  }
}

/**
  * @brief  Handles the USB bus resume condition.
  *
  *         When in device mode, this function brings the USB controller out of the
  *         suspend state.  This call must first be made with the \e bStart parameter
  *         set to \b true to start resume signaling.  The device application must
  *         then delay at least 10ms but not more than 15ms before calling this
  *         function with the \e bStart parameter set to \b false.
  *
  *         When in host mode, this function signals devices to leave the suspend
  *         state.  This call must first be made with the \e bStart parameter set to
  *         \b true to start resume signaling.  The host application must then delay
  *         at least 20ms before calling this function with the \e bStart parameter set
  *         to \b false.  This action causes the controller to complete the resume
  *         signaling on the USB bus.
  *
  * @param  bStart specifies if the USB controller is entering or leaving the
  *         resume signaling state.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_resume(bool bStart)
{
  //
  // Send a resume signal to the bus.
  //
  if (bStart)
  {
    USB->POWER |= USB_POWER_RESUME_MSK;
  }
  else
  {
    USB->POWER &= ~USB_POWER_RESUME_MSK;
  }
}

/**
  * @brief  Puts the USB bus in a suspended state.
  *
  *         When used in host mode, this function puts the USB bus in the suspended
  *         state.
  *
  * @note   This function must only be called in host mode.
  * @retval Returns one of the following: \b USB_LOW_SPEED, \b USB_FULL_SPEED,
  *         \b USB_HIGH_SPEED, or \b USB_UNDEF_SPEED.
  */
void md_usb_hos_suspend(void)
{
  //
  // Send the suspend signaling to the USB bus.
  //
  USB->POWER |= USB_POWER_SUSPEND_MSK;
}

/**
  * @brief  Issues a request for a status IN transaction on endpoint zero.
  *
  *         This function is used to cause a request for a status IN transaction from
  *         a device on endpoint zero.  This function can only be used with endpoint
  *         zero as that is the only control endpoint that supports this ability.  This
  *         function is used to complete the last phase of a control transaction to a
  *         device and an interrupt is signaled when the status packet has been
  *         received.
  *
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_request_status(void)
{
  //
  // Set the request for a status IN transaction.
  //
  USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_REQPKT_MSK | USB_CSR0L_TXCSRL_STATUSPKT_MSK;
}

/**
  * @brief  Schedules a request for an IN transaction on an endpoint in host mode.
  *
  *         This function schedules a request for an IN transaction.  When the USB
  *         device being communicated with responds with the data, the data can be
  *         retrieved by calling md_usb_hosdev_endpoint_data_get() or via a DMA
  *         transfer.
  *
  * @note   This function must only be called in host mode and only for IN
  *         endpoints.
  * @param  ui32Endpoint is the endpoint to access.
  * @retval None.
  */
void md_usb_hos_request_in(uint32_t ui32Endpoint)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Set the request for an IN transaction.
    //
    USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_REQPKT_MSK;
  }
  else
  {
    //
    // Set the request for an IN transaction.
    //
    USB->RXCSR1 |= USB_RXCSRL_REQPKT_MSK;
  }
}

/**
  * @brief  Clears a scheduled IN transaction for an endpoint in host mode.
  *
  *         This function clears a previously scheduled IN transaction if it is still
  *         pending.  This function is used to safely disable any scheduled IN
  *         transactions if the endpoint specified by \e ui32Endpoint is reconfigured
  *         for communications with other devices.
  *
  * @note   This function must only be called in host mode and only for IN
  *         endpoints.
  * @param  ui32Endpoint is the endpoint to access.
  * @retval None.
  */
void md_usb_hos_request_in_clear(uint32_t ui32Endpoint)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Set the request for an IN transaction.
  // For es32f0271,setup packet is only supported by endpoint0.
  //
  USB->CSR0L_TXCSRL &= ~USB_CSR0L_TXCSRL_REQPKT_MSK;
}

/**
  * @brief  Returns the current speed of the USB device connected.
  *
  *         This function returns the current speed of the USB bus in host mode.
  *
  * @note   This function must only be called in host mode.
  * @retval Returns one of the following: \b USB_LOW_SPEED, \b USB_FULL_SPEED,
  *         \b USB_HIGH_SPEED, or \b USB_UNDEF_SPEED.
  */
uint32_t md_usb_hos_speed_get(void)
{
  //
  // If the Full Speed device bit is set, then this is a full speed device.
  //
  if (USB->DEVCTRL & USB_DEVCTRL_FSDEV_MSK)
  {
    return (USB_FULL_SPEED);
  }

  //
  // If the Low Speed device bit is set, then this is a low speed device.
  //
  if (USB->DEVCTRL & USB_DEVCTRL_LSDEV_MSK)
  {
    return (USB_LOW_SPEED);
  }

  //
  // The device speed is not known.
  //
  return (USB_UNDEF_SPEED);
}

/**
  * @brief  Gets the current functional device address for an endpoint.
  *
  *         This function returns the current functional address that an endpoint is
  *         using to communicate with a device.  The \e ui32Flags parameter determines
  *         if the IN or OUT endpoint's device address is returned.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags determines if this is an IN or an OUT endpoint.
  * @note   This function must only be called in host mode.
  * @retval Returns the current function address being used by an endpoint.
  */
uint32_t md_usb_hos_addr_get(uint32_t ui32Endpoint, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Because es32f0271 can not read device function address,
  // the return value can always be 0.
  //

  //
  // See if the transmit or receive address is returned.
  //
  if (ui32Flags & USB_EP_HOST_OUT)
  {
    //
    // Return this endpoint's transmit address.
    //
    return (USB->FADDR);
  }
  else
  {
    //
    // Return this endpoint's receive address.
    //
    return (USB->FADDR);
  }
}

/**
  * @brief  Sets the functional address for the device that is connected to an
  *         endpoint in host mode.
  *
  *         This function configures the functional address for a device that is using
  *         this endpoint for communication.  This \e ui32Addr parameter is the address
  *         of the target device that this endpoint is communicating with.  The
  *         \e ui32Flags parameter indicates if the IN or OUT endpoint is set.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags determines if this is an IN or an OUT endpoint.
  * @param  ui32Addr is the functional address for the controller to use for
  *         this endpoint.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_addr_set(uint32_t ui32Endpoint,
                         uint32_t ui32Addr, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //

//  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // See if the transmit or receive address is set.
  //
  if (ui32Flags & USB_EP_HOST_OUT)
  {
    //
    // Set the transmit address.
    //
    USB->FADDR = ui32Addr;
  }
  else
  {
    //
    // Set the receive address.
    //
    USB->FADDR = ui32Addr;
  }
}

/**
  * @brief  Gets the current device hub address for this endpoint.
  *
  *         This function returns the current hub address that an endpoint is using
  *         to communicate with a device.  The \e ui32Flags parameter determines if the
  *         device address for the IN or OUT endpoint is returned.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags determines if this is an IN or an OUT endpoint.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
uint32_t md_usb_hos_hub_addr_get(uint32_t ui32Endpoint, uint32_t ui32Flags)
{
  //
  // es32f0271 does not support
  //
  return 0;
}

/**
  * @brief  Sets the hub address for the device that is connected to an endpoint.
  *
  *         This function configures the hub address for a device that is using this
  *         endpoint for communication.  The \e ui32Flags parameter determines if the
  *         device address for the IN or the OUT endpoint is configured by this call
  *         and sets the speed of the downstream device.  Valid values are one of
  *         \b USB_EP_HOST_OUT or \b USB_EP_HOST_IN optionally ORed with
  *         \b USB_EP_SPEED_LOW.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags determines if this is an IN or an OUT endpoint.
  * @param  ui32Addr is the hub address and port for the device using this
  *         endpoint.  The hub address must be defined in bits 0 through 6 with the
  *         port number in bits 8 through 14.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_hub_addr_set(uint32_t ui32Endpoint,
                             uint32_t ui32Addr, uint32_t ui32Flags)
{
  //
  // es32f0271 does not support
  //
}

/**
  * @brief  Get USB address.
  * @param  None.
  * @retval USB address.
  */
uint8_t md_usb_dev_addr_get(void)
{
  return (USB->FADDR);
}

/**
  * @brief  Set USB address.
  * @param  ui8Address USB address.
  * @retval None.
  */
void md_usb_dev_addr_set(uint8_t ui8Address)
{
  USB->FADDR = ui8Address;
}

/**
  * @brief  USB soft connect.
  * @param  None.
  * @retval None.
  */
void md_usb_dev_connect(void)
{
  //
  // Enable connection to the USB bus.
  //
  USB->DPDMCTRL |= USB_DPDMCTL_PHYPWREN_MSK;
}

/**
  * @brief  USB soft disconnect.
  * @param  None.
  * @retval None.
  */
void md_usb_dev_disconnect(void)
{
  //
  // Disable connection to the USB bus.
  //
  USB->DPDMCTRL &= ~USB_DPDMCTL_PHYPWREN_MSK;
}

/**
  * @brief  Returns the current speed of the USB device connected.
  *
  *         This function returns the current speed of the USB bus in device mode.
  *
  * @note   This function must only be called in device mode.
  * @retval Returns one of the following: \b USB_LOW_SPEED, \b USB_FULL_SPEED,
  *         \b USB_HIGH_SPEED, or \b USB_UNDEF_SPEED.
  */
uint32_t md_usb_dev_speed_get(void)
{
  if (USB->DPDMCTRL & USB_DPDMCTL_DPPUD_MSK)
    return USB_FULL_SPEED;
  else if (USB->DPDMCTRL & USB_DPDMCTL_DMPUD_MSK)
    return USB_LOW_SPEED;

  return USB_UNDEF_SPEED;
}

/**
  * @brief  Gets the current frame number.
  *
  *       This function returns the last frame number received.
  *
  * @param  None.
  * @retval The last frame number received.
  */
uint32_t md_usb_hosdev_frame_get(void)
{
  uint8_t temp = USB->FRAME1 & 0xff;
  return (temp | (uint32_t)((USB->FRAME2 & 0x07) << 8));
}

/**
  * @brief  Disables control interrupts on a specified USB controller.
  *
  *         This function disables the control interrupts for the USB controller
  *         specified by the \e ui32Base parameter.  The \e ui32Flags parameter
  *         specifies which control interrupts to disable.  The flags passed in the
  *         \e ui32Flags parameters must be the definitions that start with
  *         \b USB_INTCTRL_* and not any other \b USB_INT flags.
  *
  * @param  ui32IntFlags specifies which control interrupts to disable.
  * @retval None.
  */
void md_usb_hosdev_int_disable(uint32_t ui32IntFlags)
{
  //
  // Check the arguments.
  //
  assert_param((ui32IntFlags & ~(USB_INTCTRL_ALL)) == 0);

  //
  // If any general interrupts were disabled then write the general interrupt
  // settings out to the hardware.
  //
  if (ui32IntFlags & USB_INTCTRL_STATUS)
  {
    USB->IDR &= ~(ui32IntFlags & USB_INTCTRL_STATUS);
  }
}

/**
  * @brief  Enables control interrupts on a specified USB controller.
  *
  *         This function Enables the control interrupts for the USB controller
  *         specified by the \e ui32Base parameter.  The \e ui32Flags parameter
  *         specifies which control interrupts to disable.  The flags passed in the
  *         \e ui32Flags parameters must be the definitions that start with
  *         \b USB_INTCTRL_* and not any other \b USB_INT flags.
  *
  * @param  ui32IntFlags specifies which control interrupts to Enable.
  * @retval None.
  */
void md_usb_hosdev_int_enable(uint32_t ui32IntFlags)
{
  //
  // Check the arguments.
  //
  assert_param((ui32IntFlags & ~(USB_INTCTRL_ALL)) == 0);

  //
  // If any general interrupts were disabled then write the general interrupt
  // settings out to the hardware.
  //
  if (ui32IntFlags & USB_INTCTRL_STATUS)
  {
    USB->IER |= ui32IntFlags & USB_INTCTRL_STATUS;
  }
}

/**
  * @brief  Returns the control interrupt status on a specified USB controller.
  *
  *         This function reads control interrupt status for a USB controller.  This
  *         call returns the current status for control interrupts only, the endpoint
  *         interrupt status is retrieved by calling md_usb_hosdev_endpoint_int_status().
  *         The bit values returned are compared against the \b USB_INTCTRL_* values.
  *
  *         The following are the meanings of all \b USB_INCTRL_ flags and the modes
  *         for which they are valid.  These values apply to any calls to
  *         md_usb_hosdev_int_status(), md_usb_hosdev_int_enable(),
  *         and md_usb_hosdev_int_disable().
  *         Some of these flags are only valid in the following modes as indicated in
  *         the parentheses:  Host, Device, and OTG.
  *
  *         - \b USB_INTCTRL_ALL - A full mask of all control interrupt sources.
  *         - \b USB_INTCTRL_VBUS_ERR - A VBUS error has occurred (Host Only).
  *         - \b USB_INTCTRL_SESSION - Session Start Detected on A-side of cable
  *                                    (OTG Only).
  *         - \b USB_INTCTRL_SESSION_END - Session End Detected (Device Only)
  *         - \b USB_INTCTRL_DISCONNECT - Device Disconnect Detected (Host Only)
  *         - \b USB_INTCTRL_CONNECT - Device Connect Detected (Host Only)
  *         - \b USB_INTCTRL_SOF - Start of Frame Detected.
  *         - \b USB_INTCTRL_BABBLE - USB controller detected a device signaling past
  *                                   the end of a frame (Host Only)
  *         - \b USB_INTCTRL_RESET - Reset signaling detected by device (Device Only)
  *         - \b USB_INTCTRL_RESUME - Resume signaling detected.
  *         - \b USB_INTCTRL_SUSPEND - Suspend signaling detected by device (Device
  *                                    Only)
  *         - \b USB_INTCTRL_MODE_DETECT - OTG cable mode detection has completed
  *                                        (OTG Only)
  *         - \b USB_INTCTRL_POWER_FAULT - Power Fault detected (Host Only)
  *
  * @param  ui32IntFlags specifies which control interrupts to Enable.
  * @note   This call clears the source of all of the control status interrupts.
  * @retval Returns the status of the control interrupts for a USB controller.
  */
uint32_t md_usb_hosdev_int_status(void)
{
  uint32_t ui32Status;

  //
  // Get the general interrupt status, these bits go into the upper 8 bits
  // of the returned value.
  //
  ui32Status = USB->RIF & 0x7F;

  //
  // Clear all the general interrupt status.
  //
  USB->ICR = 0xff;

  //
  // Return the combined interrupt status.
  //
  return (ui32Status);
}

/**
  * @brief  Returns the current operating mode of the controller.
  *
  *         This function returns the current operating mode on USB controllers with
  *         OTG or Dual mode functionality.
  *
  *         For OTG controllers:
  *
  *         The function returns one of the following values on OTG controllers:
  *
  *         \b USB_OTG_MODE_ASIDE_HOST indicates that the controller is in host mode
  *         on the A-side of the cable.
  *
  *         \b USB_OTG_MODE_ASIDE_DEV indicates that the controller is in device mode
  *         on the A-side of the cable.
  *
  *         \b USB_OTG_MODE_BSIDE_HOST indicates that the controller is in host mode
  *         on the B-side of the cable.
  *
  *         \b USB_OTG_MODE_BSIDE_DEV indicates that the controller is in device mode
  *         on the B-side of the cable.  If an OTG session request is started with no
  *         cable in place, this mode is the default.
  *
  *         \b USB_OTG_MODE_NONE indicates that the controller is not attempting to
  *         determine its role in the system.
  *
  *         For Dual Mode controllers:
  *
  *         The function returns one of the following values:
  *
  *         \b USB_DUAL_MODE_HOST indicates that the controller is acting as a host.
  *
  *         \b USB_DUAL_MODE_DEVICE indicates that the controller acting as a device.
  *
  *         \b USB_DUAL_MODE_NONE indicates that the controller is not active as
  *         either a host or device.
  *
  * @param  None.
  * @retval Returns \b USB_OTG_MODE_ASIDE_HOST, \b USB_OTG_MODE_ASIDE_DEV,
  *         \b USB_OTG_MODE_BSIDE_HOST, \b USB_OTG_MODE_BSIDE_DEV,
  *         \b USB_OTG_MODE_NONE, \b USB_DUAL_MODE_HOST, \b USB_DUAL_MODE_DEVICE, or
  *         \b USB_DUAL_MODE_NONE.
  */
uint32_t md_usb_hosdev_mode_get(void)
{
  //
  // It will not be called for es32f0271,because OTG is not supported.
  //
  // Checks the current mode in the USB_O_DEVCTL and returns the current
  // mode.
  //
  // USB_OTG_MODE_ASIDE_HOST:  USB_DEVCTL_HOST | USB_DEVCTL_SESSION
  // USB_OTG_MODE_ASIDE_DEV:   USB_DEVCTL_SESSION
  // USB_OTG_MODE_BSIDE_HOST:  USB_DEVCTL_DEV | USB_DEVCTL_SESSION |
  //                           USB_DEVCTL_HOST
  // USB_OTG_MODE_BSIDE_DEV:   USB_DEVCTL_DEV | USB_DEVCTL_SESSION
  // USB_OTG_MODE_NONE:        USB_DEVCTL_DEV
  //
  return (USB->DEVCTRL & (USB_DEVCTRL_HOST_MSK | USB_DEVCTRL_SESSION_MSK));
}

/**
  * @brief  Starts or ends a session.
  *
  *         This function is used in OTG mode to start a session request or end a
  *         session.  If the \e bStart parameter is set to \b true, then this function
  *         starts a session and if it is \b false it ends a session.
  *
  * @param  bStart specifies if this call starts or ends a session.
  * @retval None.
  */
void md_usb_otg_session_request(bool bStart)
{
  //
  // Start or end the session as directed.
  //
  if (bStart)
  {
    USB->DEVCTRL |= USB_DEVCTRL_SESSION_MSK;
  }
  else
  {
    USB->DEVCTRL &= ~USB_DEVCTRL_SESSION_MSK;
  }
}

/**
  * @brief  Change the mode of the USB controller to host.
  *
  *         This function changes the mode of the USB controller to host mode.
  *
  * @note   This function must only be called on microcontrollers that support
  *         OTG operation.
  * @param  None.
  * @retval None.
  */
void md_usb_force_host_mode(void)
{
  unsigned int i;
  //
  // Force host mode.
  //
  USB->SWCID &= ~USB_SWCID_HOST_MSK;
  USB->SWCID |= USB_SWCID_CIDCTRL_MSK;
  USB->DEVCTRL = USB_DEVCTRL_HOSTREQ_MSK;

  i = 20;

  while ((!(USB->DEVCTRL & USB_DEVCTRL_HOST_MSK)) && (i != 0))
  {
    i--;
  }
}

/**
  * @brief  Change the mode of the USB controller to device.
  *
  *         This function changes the mode of the USB controller to device mode.
  *
  * @note   This function must only be called on microcontrollers that support
  *         OTG operation.
  * @param  None.
  * @retval None.
  */
void md_usb_force_device_mode(void)
{
  //
  // Force mode in OTG parts that support forcing USB controller mode.
  // This bit is not writable in USB controllers that do not support
  // forcing the mode.  Not setting the USB_GPCS_DEVMOD bit makes this a
  // force of device mode.
  //
  USB->SWCID   |= USB_SWCID_HOST_MSK;
  USB->SWCID   |= USB_SWCID_CIDCTRL_MSK;
}

/**
  * @brief  Change the mode of the USB controller to OTG.
  *
  *         This function changes the mode of the USB controller to OTG mode.
  *
  * @note   This function must only be called on microcontrollers that support
  *         OTG operation.
  * @param  None.
  * @retval None.
  */
void md_usb_force_otg_mode(void)
{
  //
  // Force mode in OTG parts that support forcing USB controller mode.
  // This bit is not writable in USB controllers that do not support
  // forcing the mode.  Not setting the USB_GPCS_DEVMOD bit makes this a
  // force of OTG mode.
  //
  USB->SWCID |= USB_SWCID_HOST_MSK;
  USB->SWCID &= ~USB_SWCID_CIDCTRL_MSK;
}

/**
  * @brief  Change the operating mode of the USB controller.
  *
  *         This function changes the operating modes of the USB controller.  When
  *         operating in full OTG mode, the USB controller uses the VBUS and ID pins to
  *         detect mode and voltage changes.  While these pins are primarily used in
  *         OTG mode, they can also affect the operation of host and device modes.  In
  *         device mode, the USB controller can be configured to monitor or ignore
  *         VBUS. Monitoring VBUS allows the controller to determine if it has been
  *         disconnected from the host.  In host mode, the USB controller uses the
  *         VBUS pin to detect loss of VBUS caused by excessive power draw due to a
  *         drop in the VBUS voltage.  This call takes the place of
  *         md_usb_force_host_mode(),md_usb_force_device_mode(),
  *         and md_usb_force_otg_mode().
  *         The \e ui32Mode value should be one of the following values:
  *
  *         - \b USB_MODE_OTG enables operating in full OTG mode, VBUS and ID are
  *           used by the controller.
  *         - \b USB_MODE_HOST enables operating only as a host with no monitoring of
  *           VBUS or ID pins.
  *         - \b USB_MODE_HOST_VBUS enables operating only as a host with monitoring of
  *           VBUS pin.  This configuration enables detection of VBUS droop while still
  *           forcing host mode.
  *         - \b USB_MODE_DEVICE enables operating only as a device with no monitoring
  *           of VBUS or ID pins.
  *         - \b USB_MODE_DEVICE_VBUS enables operating only as a device with
  *           monitoring of VBUS pin.  This configuration enables disconnect detection
  *           while still forcing device mode.
  *
  * @note   Some of the options above are not available on some ES32 devices.
  *         Please check the data sheet to determine if the USB controller supports a
  *         particular mode.
  * @param  ui32Mode specifies the operating mode of the USB OTG pins.
  * @retval None.
  */
void md_usb_mode_config(uint32_t ui32Mode)
{
  //
  // It is not supported by es32f0271.
  //
}

/**
  * @} USB_MD_PF_BASIC
  */

/** @addtogroup USB_MD_PF_ENDPOINT USB Public Endpoint Functions
  * @{
  */

/**
  * @brief  Sets the base configuration for a host endpoint.
  *
  *         This function sets the basic configuration for the transmit or receive
  *         portion of an endpoint in host mode.  The \e ui32Flags parameter determines
  *         some of the configuration while the other parameters provide the rest.  The
  *         \e ui32Flags parameter determines whether this is an IN endpoint
  *         (\b USB_EP_HOST_IN or \b USB_EP_DEV_IN) or an OUT endpoint
  *         (\b USB_EP_HOST_OUT or \b USB_EP_DEV_OUT), whether this is a Full speed
  *         endpoint (\b USB_EP_SPEED_FULL) or a Low speed endpoint
  *         (\b USB_EP_SPEED_LOW).
  *
  *         The \b USB_EP_MODE_ flags control the type of the endpoint.
  *         - \b USB_EP_MODE_CTRL is a control endpoint.
  *         - \b USB_EP_MODE_ISOC is an isochronous endpoint.
  *         - \b USB_EP_MODE_BULK is a bulk endpoint.
  *         - \b USB_EP_MODE_INT is an interrupt endpoint.
  *
  *         The \e ui32NAKPollInterval parameter has different meanings based on the
  *         \b USB_EP_MODE value and whether or not this call is being made for
  *         endpoint zero or another endpoint.  For endpoint zero or any Bulk
  *         endpoints, this value always indicates the number of frames to allow a
  *         device to NAK before considering it a timeout.  If this endpoint is an
  *         isochronous or interrupt endpoint, this value is the polling interval for
  *         this endpoint.
  *
  *         For interrupt endpoints, the polling interval is the number of frames
  *         between interrupt IN requests to an endpoint and has a range of 1 to 255.
  *         For isochronous endpoints this value represents a polling interval of
  *         2 ^ (\e ui32NAKPollInterval - 1) frames.  When used as a NAK timeout, the
  *         \e ui32NAKPollInterval value specifies 2 ^ (\e ui32NAKPollInterval - 1)
  *         frames before issuing a time out.
  *
  *         There are two special time out values that can be specified when setting
  *         the \e ui32NAKPollInterval value.  The first is \b MAX_NAK_LIMIT, which is
  *         the maximum value that can be passed in this variable.  The other is
  *         \b DISABLE_NAK_LIMIT, which indicates that there is no limit on the
  *         number of NAKs.
  *
  *         The \b USB_EP_DMA_MODE_ flags determine the type of DMA access to the
  *         endpoint data FIFOs.  The choice of the DMA mode depends on how the DMA
  *         controller is configured and how it is being used.  See the ``Using USB
  *         with the DMA Controller'' or the ''Using the integrated USB DMA
  *         Controller'' section for more information on DMA configuration depending
  *         on the type of DMA that is supported by the USB controller.
  *
  *         When configuring the OUT portion of an endpoint, the \b USB_EP_AUTO_SET bit
  *         is specified to cause the transmission of data on the USB bus to start
  *         as soon as the number of bytes specified by \e ui32MaxPayload has been
  *         written into the OUT FIFO for this endpoint.
  *
  *         When configuring the IN portion of an endpoint, the \b USB_EP_AUTO_REQUEST
  *         bit can be specified to trigger the request for more data once the FIFO has
  *         been drained enough to fit \e ui32MaxPayload bytes.  The
  *         \b USB_EP_AUTO_CLEAR bit can be used to clear the data packet ready flag
  *         automatically once the data has been read from the FIFO.  If this option is
  *         not used, this flag must be manually cleared via a call to
  *         md_usb_dev_endpoint_status_clear() or md_usb_hos_endpoint_status_clear().
  *
  *         For interrupt endpoints in low or full speed mode, the polling interval
  *         (\e ui32NAKPollInterval) is the number of frames between interrupt IN
  *         requests to an endpoint and has a range of 1 to 255.  For interrupt
  *         endpoints in high speed mode the polling interval is
  *         2 ^ (\e ui32NAKPollInterval - 1) microframes between interrupt IN requests
  *         to an endpoint and has a range of 1 to 16.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags are the status bits that are cleared.
  * @param  ui32MaxPacketSize is the maximum payload for this endpoint.
  * @param  ui32NAKPollInterval is the either the NAK timeout limit or the
  *         polling interval, depending on the type of endpoint.
  * @param  ui32TargetEndpoint is the endpoint that the host endpoint is
  *         targeting.
  * @param  ui32Flags are used to configure other endpoint settings.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_endpoint_config_set(uint32_t ui32Endpoint,
                                    uint32_t ui32MaxPacketSize,
                                    uint32_t ui32NAKPollInterval,
                                    uint32_t ui32TargetEndpoint,
                                    uint32_t ui32Flags)
{
  uint32_t ui32Register;

  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Endpoint zero is configured differently than the other endpoints, so see
  // if this is endpoint zero.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Set the NAK timeout.
    //
    USB->NAKLIMIT0_TXINTERVAL = (uint8_t)ui32NAKPollInterval;

    //
    // Set the transfer type information.
    //

    //
    // Set the speed of this endpoint.
    //
    if (ui32Flags & USB_EP_SPEED_HIGH)
    {
      //
      // es32f0271 does not support high sepeed
      //
    }
    else if (ui32Flags & USB_EP_SPEED_FULL)
    {
    }
    else
    {
    }
  }
  else
  {
    //
    // Start with the target endpoint.
    //
    ui32Register = ui32TargetEndpoint;

    //
    // Set the speed for the device using this endpoint.
    //
    if (ui32Flags & USB_EP_SPEED_HIGH)
    {
      //
      // es32f0271 does not support high sepeed
      //
    }
    else if (ui32Flags & USB_EP_SPEED_FULL)
    {

    }
    else
    {

    }

    //
    // Set the protocol for the device using this endpoint.
    //
    switch (ui32Flags & USB_EP_MODE_MASK)
    {
      //
      // The bulk protocol is being used.
      //
      case USB_EP_MODE_BULK:
      {
        ui32Register |= 0x20;
        break;
      }

      //
      // The isochronous protocol is being used.
      //
      case USB_EP_MODE_ISOC:
      {
        ui32Register |= 0x10;
        break;
      }

      //
      // The interrupt protocol is being used.
      //
      case USB_EP_MODE_INT:
      {
        ui32Register |= 0x30;
        break;
      }

      //
      // The control protocol is being used.
      //
      case USB_EP_MODE_CTRL:
      {
        ui32Register |= 0x00;
        break;
      }
    }

    //
    // See if the transmit or receive endpoint is being configured.
    //
    if (ui32Flags & USB_EP_HOST_OUT)
    {
      //
      // Set the transfer type information.
      //
      USB->TXTYPE = ui32Register;

      //
      // Set the NAK timeout or polling interval.
      //
      USB->NAKLIMIT0_TXINTERVAL = ui32NAKPollInterval;

      //
      // Set the Maximum Payload per transaction.
      //
      USB->TXMAXP = ui32MaxPacketSize;

      //
      // Set the transmit control value to zero.
      //
      ui32Register = 0;

      //
      // Allow auto setting of TxPktRdy when max packet size has been
      // loaded into the FIFO.
      //
      if (ui32Flags & USB_EP_AUTO_SET)
      {
        ui32Register |= USB_CSR0H_TXCSRH_AUTOSET_MSK;
      }

//      //
//      // Configure the DMA Mode.
//      //
//      if(ui32Flags & USB_EP_DMA_MODE_1)
//      {
//        ui32Register |= USB_TXCSRH1_DMAEN | USB_TXCSRH1_DMAMOD;
//      }
//      else if(ui32Flags & USB_EP_DMA_MODE_0)
//      {
//        ui32Register |= USB_TXCSRH1_DMAEN;
//      }

      //
      // Write out the transmit control value.
      //
      USB->CSR0H_TXCSRH = (uint8_t)ui32Register;
    }
    else
    {
      //
      // Set the transfer type information.
      //
      USB->RXTYPE = ui32Register;

      //
      // Set the NAK timeout or polling interval.
      //
      USB->RXINTERVAL = ui32NAKPollInterval;

      //
      // Set the Maximum Payload per transaction.
      //
      USB->RXMAXP = ui32MaxPacketSize;

      //
      // Set the receive control value to zero.
      //
      ui32Register = 0;

      //
      // Allow auto clearing of RxPktRdy when packet of size max packet
      // has been unloaded from the FIFO.
      //
      if (ui32Flags & USB_EP_AUTO_CLEAR)
      {
        ui32Register |= USB_RXCSRH_AUTOCLR_MSK;
      }

      //
      // Allow auto generation of DMA requests.
      //
      if (ui32Flags & USB_EP_AUTO_REQUEST)
      {
        ui32Register |= USB_RXCSRH_AUTOREQ_MSK;
      }

//      //
//      // Configure the DMA Mode.
//      //
//      if(ui32Flags & USB_EP_DMA_MODE_1)
//      {
//        ui32Register |= USB_RXCSRH1_DMAEN | USB_RXCSRH1_DMAMOD;
//      }
//      else if(ui32Flags & USB_EP_DMA_MODE_0)
//      {
//        ui32Register |= USB_RXCSRH1_DMAEN;
//      }

      //
      // Write out the receive control value.
      //
      USB->RXCSR2 = (uint8_t)ui32Register;


//      USB->RXFIFO1=0x18;          //Start Address=0x18
//      USB->RXFIFO2=(3<<5);        //Size=64, No Double-Packet Buffering
//      USB->RXCSR1|=USB_RXCSRL_FLUSH_MSK; //Flush FIFO
    }
  }
}

/**
  * @brief  Acknowledge that data was read from the specified endpoint's FIFO in host mode.
  *
  *         This function acknowledges that the data was read from the endpoint's FIFO.
  *         This call is used if processing is required between reading the data and
  *         acknowledging that the data has been read.
  * @param  ui32Endpoint is the endpoint to access.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_endpoint_data_ack(uint32_t ui32Endpoint)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Clear RxPktRdy.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    USB->CSR0L_TXCSRL &= ~USB_CSR0L_TXCSRL_RXRDY_MSK;
  }
  else
  {
    USB->RXCSR1 &= ~(USB_RXCSRL_RXRDY_MSK);
  }
}

/**
  * @brief  Sets the value data toggle on an endpoint in host mode.
  *
  *         This function is used to force the state of the data toggle in host mode.
  *         If the value passed in the \e bDataToggle parameter is \b false, then the
  *         data toggle is set to the DATA0 state, and if it is \b true it is set to
  *         the DATA1 state.  The \e ui32Flags parameter can be \b USB_EP_HOST_IN or
  *         \b USB_EP_HOST_OUT to access the desired portion of this endpoint.  The
  *         \e ui32Flags parameter is ignored for endpoint zero.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  bDataToggle specifies whether to set the state to DATA0 or DATA1.
  * @param  ui32Flags specifies whether to set the IN or OUT endpoint.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_endpoint_data_toggle(uint32_t ui32Endpoint,
                                     bool bDataToggle, uint32_t ui32Flags)
{
  //
  // It is not supported by es32f0271.
  //
  UNUSED(ui32Endpoint);
  UNUSED(bDataToggle);
  UNUSED(ui32Flags);
}

/**
  * @brief  Clears the status bits in this endpoint in host mode.
  *
  *         This function clears the status of any bits that are passed in the
  *         \e ui32Flags parameter.  The \e ui32Flags parameter can take the value
  *         returned from the md_usb_hosdev_endpoint_status() call.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags are the status bits that are cleared.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_endpoint_status_clear(uint32_t ui32Endpoint,
                                      uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Clear the specified flags for the endpoint.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    USB->CSR0L_TXCSRL &= ~(ui32Flags & 0xff);
  }
  else
  {
    USB->CSR0L_TXCSRL &= ~(ui32Flags & 0xff);
    USB->RXCSR1 &= ~((ui32Flags >> 16) & 0xff);
  }
}

/**
  * @brief  Changes the speed of the connection for a host endpoint.
  *
  *         This function sets the USB speed for an IN or OUT endpoint in host mode.
  *         The \e ui32Flags parameter specifies the speed using one of the following
  *         values: \b USB_EP_SPEED_LOW, \b USB_EP_SPEED_FULL, or \b USB_EP_SPEED_HIGH.
  *         The \e ui32Flags parameter also specifies which direction is set by
  *         adding the logical OR in either \b USB_EP_HOST_IN or \b USB_EP_HOST_OUT.
  *         All other flags are ignored.  This function is typically only used for
  *         endpoint 0, but could be used with other endpoints as well.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags are used to configure other endpoint settings.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_endpoint_speed(uint32_t ui32Endpoint,
                               uint32_t ui32Flags)
{
  //
  // For es32f0271,we can not config endpoint speed.
  //
  UNUSED(ui32Endpoint);
  UNUSED(ui32Flags);
}

/**
  * @brief  Enables or disables ping tokens for an endpoint using high-speed control
  *         transfers in host mode.
  *
  *         This function configures the USB controller to either send or not send ping
  *         tokens during the data and status phase of high speed control transfers.
  *         The only supported value for \e ui32Endpoint is \b USB_EP_0 because all
  *         control transfers are handled using this endpoint.  If the \e bEnable is
  *         \b true then ping tokens are enabled, if \b false then ping tokens are
  *         disabled.  This must be used if the controller must support
  *         communications with devices that do not support ping tokens in high speed
  *         mode.
  * @param  ui32Endpoint specifies the endpoint to enable/disable ping tokens.
  * @param  bEnable specifies whether enable or disable ping tokens.
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_endpoint_ping(uint32_t ui32Endpoint,
                              bool bEnable)
{
  //
  // It is not supported by es32f0271.
  //
  UNUSED(ui32Endpoint);
  UNUSED(bEnable);
}

/**
  * @brief  USB endpoint configuration.
  *
  *         This function sets the basic configuration for an endpoint in device mode.
  *         Endpoint zero does not have a dynamic configuration, so this function
  *         must not be called for endpoint zero.  The \e ui32Flags parameter
  *         determines some of the configuration while the other parameters provide the
  *         rest.
  *
  *         When configuring an IN endpoint, the \b USB_EP_AUTO_SET bit can be
  *         specified to cause the automatic transmission of data on the USB bus as
  *         soon as \e ui32MaxPacketSize bytes of data are written into the FIFO for
  *         this endpoint.  This option is commonly used with DMA as no interaction
  *         is required to start the transmission of data.
  *
  *         The \b USB_EP_MODE_ flags define what the type is for the specified endpoint.
  *           USB_EP_MODE_CTRL is a control endpoint.
  *           USB_EP_MODE_ISOC is an isochronous endpoint.
  *           USB_EP_MODE_BULK is a bulk endpoint.
  *           USB_EP_MODE_INT is an interrupt endpoint.
  *
  *         When configuring an OUT endpoint, the \b USB_EP_AUTO_REQUEST bit is
  *         specified to trigger the request for more data once the FIFO has been
  *         drained enough to receive \e ui32MaxPacketSize more bytes of data.  Also
  *         for OUT endpoints, the \b USB_EP_AUTO_CLEAR bit can be used to clear the
  *         data packet ready flag automatically once the data has been read from the
  *         FIFO.  If this option is not used, this flag must be manually cleared via a
  *         call to md_usb_dev_endpoint_status_clear().  Both of these settings can be
  *         used to remove the need for extra calls when using the controller with DMA.
  *
  * @param  ui32Endpoint The USB endpoint.
  * @param  ui32MaxPacketSize is the maximum packet size for this endpoint.
  * @param  ui32Flags are used to configure other endpoint settings.
  * @retval None.
  */
void md_usb_dev_endpoint_config_set(uint32_t ui32Endpoint,
                                    uint32_t ui32MaxPacketSize,
                                    uint32_t ui32Flags)
{
  uint32_t ui32Register;

  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Determine if a transmit or receive endpoint is being configured.
  //
  if (ui32Flags & USB_EP_DEV_IN)  /*IN*/
  {
    //
    // Set the max packet size.
    //
    USB->TXMAXP = ui32MaxPacketSize;

    //
    // The transmit control value is zero unless options are enabled.
    //
    ui32Register = 0;

    //
    // Allow auto setting of TxPktRdy when max packet size has been loaded
    // into the FIFO.
    //
    if (ui32Flags & USB_EP_AUTO_SET)
    {
      ui32Register |= USB_CSR0H_TXCSRH_AUTOSET_MSK;
    }

    //
    // Configure the DMA mode.
    //
    /* es32f0271 does not support DMA */

    //
    // Enable isochronous mode if requested.
    //
    if ((ui32Flags & USB_EP_MODE_MASK) == USB_EP_MODE_ISOC)
    {
      ui32Register |= USB_CSR0H_TXCSRH_ISO_MSK;
    }

    //
    // Write the transmit control value.
    //
    USB->CSR0H_TXCSRH = (uint8_t)ui32Register;

    //
    // Reset the Data toggle to zero.
    //
    USB->CSR0L_TXCSRL = USB_CSR0L_TXCSRL_CLRDATAT_MSK;
  }
  else    /*OUT*/
  {
    //
    // Set the MaxPacketSize.
    //
    USB->RXMAXP = ui32MaxPacketSize;

    //
    // The receive control value is zero unless options are enabled.
    //
    ui32Register = 0;

    //
    // Allow auto clearing of RxPktRdy when packet of size max packet
    // has been unloaded from the FIFO.
    //
    if (ui32Flags & USB_EP_AUTO_CLEAR)
    {
      ui32Register = USB_RXCSRH_AUTOCLR_MSK;
    }

//    //
//    // Configure the DMA mode.
//    //

//    //
//    // If requested, disable NYET responses for high-speed bulk and
//    // interrupt endpoints.
//    //
    /*es32f0271 does not support*/

    //
    // Enable isochronous mode if requested.
    //
    if ((ui32Flags & USB_EP_MODE_MASK) == USB_EP_MODE_ISOC)
    {
      ui32Register |= USB_RXCSRH_ISO_MSK;
    }

    //
    // Write the receive control value.
    //
    USB->RXCSR2 = ui32Register;

    //
    // Reset the Data toggle to zero.
    //
    USB->RXCSR1 = USB_RXCSRL_CLRDT_MSK;
  }
}

/**
  * @brief  Gets the current configuration for an endpoint.
  *
  *         This function returns the basic configuration for an endpoint in device
  *         mode.  The values returned in \e *pui32MaxPacketSize and \e *pui32Flags are
  *         equivalent to the \e ui32MaxPacketSize and \e ui32Flags previously passed
  *         to md_usb_dev_endpoint_config_get() for this endpoint.
  *
  * @note   This function must only be called in device mode.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  pui32MaxPacketSize is a pointer which is written with the maximum
  *         packet size for this endpoint.
  * @param  pui32Flags is a pointer which is written with the current endpoint
  *         settings.  On entry to the function, this pointer must contain either
  *         \b USB_EP_DEV_IN or \b USB_EP_DEV_OUT to indicate whether the IN or OUT
  *         endpoint is to be queried.
  * @retval None.
  */
void md_usb_dev_endpoint_config_get(uint32_t ui32Endpoint,
                                    uint32_t *pui32MaxPacketSize,
                                    uint32_t *pui32Flags)
{
  uint32_t ui32Register;

  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Determine if a transmit or receive endpoint is being queried.
  //
  if (*pui32Flags & USB_EP_DEV_IN)
  {
    //
    // Clear the flags other than the direction bit.
    //
    *pui32Flags = USB_EP_DEV_IN;

    //
    // Get the maximum packet size.
    //
    *pui32MaxPacketSize = (uint32_t)USB->TXMAXP;

    //
    // Get the current transmit control register value.`
    //
    ui32Register = (uint32_t)(USB->CSR0H_TXCSRH);

    //
    // Are we allowing auto setting of TxPktRdy when max packet size has
    // been loaded into the FIFO?
    //
    if (ui32Register & USB_CSR0H_TXCSRH_AUTOSET_MSK)
    {
      *pui32Flags |= USB_EP_AUTO_SET;
    }

    //
    // Get the DMA mode.
    //

    //
    // Are we in isochronous mode?
    //
    if (ui32Register & USB_CSR0H_TXCSRH_ISO_MSK)
    {
      *pui32Flags |= USB_EP_MODE_ISOC;
    }
    else
    {
      //
      // The hardware doesn't differentiate between bulk, interrupt
      // and control mode for the endpoint so we just set something
      // that isn't isochronous.  This protocol ensures that anyone
      // modifying the returned flags in preparation for a call to
      // USBDevEndpointConfigSet do not see an unexpected mode change.
      // If they decode the returned mode, however, they may be in for
      // a surprise.
      //
      *pui32Flags |= USB_EP_MODE_BULK;
    }
  }
  else
  {
    //
    // Clear the flags other than the direction bit.
    //
    *pui32Flags = USB_EP_DEV_OUT;

    //
    // Get the MaxPacketSize.
    //
    *pui32MaxPacketSize = (uint32_t)USB->RXMAXP;

    //
    // Get the current receive control register value.
    //
    ui32Register = (uint32_t)(USB->RXCSR2);

    //
    // Are we allowing auto clearing of RxPktRdy when packet of size max
    // packet has been unloaded from the FIFO?
    //
    if (ui32Register & USB_RXCSRH_AUTOCLR_MSK)
    {
      *pui32Flags |= USB_EP_AUTO_CLEAR;
    }

    //
    // Get the DMA mode.
    //

    //
    // Are we in isochronous mode?
    //
    if (ui32Register & USB_RXCSRH_ISO_MSK)
    {
      *pui32Flags |= USB_EP_MODE_ISOC;
    }
    else
    {
      //
      // The hardware doesn't differentiate between bulk, interrupt
      // and control mode for the endpoint so we just set something
      // that isn't isochronous.  This protocol ensures that anyone
      // modifying the returned flags in preparation for a call to
      // USBDevEndpointConfigSet do not see an unexpected mode change.
      // If they decode the returned mode, however, they may be in for
      // a surprise.
      //
      *pui32Flags |= USB_EP_MODE_BULK;
    }
  }
}

/**
  * @brief  Acknowledge that data was read from the specified endpoint's FIFO in device
  *         mode.
  *
  *         This function acknowledges that the data was read from the endpoint's FIFO.
  *         The \e bIsLastPacket parameter is set to a \b true value if this is the
  *         last in a series of data packets on endpoint zero.  The \e bIsLastPacket
  *         parameter is not used for endpoints other than endpoint zero.  This call
  *         can be used if processing is required between reading the data and
  *         acknowledging that the data has been read.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  bIsLastPacket indicates if this packet is the last one.
  * @note   This function must only be called in device mode.
  * @retval None.
  */
void md_usb_dev_endpoint_ack(uint32_t ui32Endpoint,
                             bool bIsLastPacket)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Determine which endpoint is being acked.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Clear RxPktRdy, and optionally DataEnd, on endpoint zero.
    //
    USB->CSR0L_TXCSRL = USB_CSR0L_TXCSRL_RXRDYC_MSK | (bIsLastPacket ? USB_CSR0L_TXCSRL_DATAEND_MSK : 0);
  }
  else
  {
    //
    // Clear RxPktRdy on all other endpoints.
    //
    USB->RXCSR1 &= ~USB_RXCSRL_RXRDY_MSK;
  }
}

/**
  * @brief  Stalls the specified endpoint in device mode.
  *
  *         This function causes the endpoint number passed in to go into a stall
  *         condition.  If the \e ui32Flags parameter is \b USB_EP_DEV_IN, then the
  *         stall is issued on the IN portion of this endpoint.  If the \e ui32Flags
  *         parameter is \b USB_EP_DEV_OUT, then the stall is issued on the OUT portion
  *         of this endpoint.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags specifies whether to stall the IN or OUT endpoint.
  * @note   This function must only be called in device mode.
  * @retval None.
  */
void md_usb_dev_endpoint_stall(uint32_t ui32Endpoint, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Determine how to stall this endpoint.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Perform a stall on endpoint zero.
    //
    USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_RXRDYC_MSK | USB_CSR0L_TXCSRL_STALL_MSK;
  }
  else if (ui32Flags == USB_EP_DEV_IN)
  {
    //
    // Perform a stall on an IN endpoint.
    //
    USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_STALL_MSK;
  }
  else
  {
    //
    // Perform a stall on an OUT endpoint.
    //
    USB->RXCSR1 |= USB_RXCSRL_STALL_MSK;
  }
}

/**
  * @brief  Clears the stall condition on the specified endpoint in device mode.
  *
  *         This function causes the endpoint number passed in to exit the stall
  *         condition.  If the \e ui32Flags parameter is \b USB_EP_DEV_IN, then the
  *         stall is cleared on the IN portion of this endpoint.  If the \e ui32Flags
  *         parameter is \b USB_EP_DEV_OUT, then the stall is cleared on the OUT
  *         portion of this endpoint.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags specifies whether to stall the IN or OUT endpoint.
  * @note   This function must only be called in device mode.
  * @retval None.
  */
void md_usb_dev_endpoint_stall_clear(uint32_t ui32Endpoint, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Determine how to clear the stall on this endpoint.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Clear the stall on endpoint zero.
    //
    USB->CSR0L_TXCSRL &= ~USB_CSR0L_TXCSRL_STALLED_MSK;
  }
  else if (ui32Flags == USB_EP_DEV_IN)
  {
    //
    // Clear the stall on an IN endpoint.
    //
    USB->CSR0L_TXCSRL &= ~(USB_CSR0L_TXCSRL_SENTSTALL_MSK | USB_CSR0L_TXCSRL_SENDSTALL_MSK);

    //
    // Reset the data toggle.
    //
    /* @yuzr es32f0271 can not realize */
    USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_CLRDATAT_MSK;
  }
  else
  {
    //
    // Clear the stall on an OUT endpoint.
    //
//    HWREGB(ui32Base + USB_O_RXCSRL1 + EP_OFFSET(ui32Endpoint)) &=
//      ~(USB_RXCSRL1_STALL | USB_RXCSRL1_STALLED);
    USB->RXCSR1 &= ~(USB_RXCSRL_STALL_MSK | USB_RXCSRL_STALLED_MSK);

    //
    // Reset the data toggle.
    //
    USB->RXCSR1 |= USB_RXCSRL_CLRDT_MSK;
  }
}

/**
  * @brief  Clears the status bits in this endpoint in device mode.
  *
  *         This function clears the status of any bits that are passed in the
  *         \e ui32Flags parameter.  The \e ui32Flags parameter can take the value
  *         returned from the USBEndpointStatus() call.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags are the status bits that are cleared.
  * @note   This function must only be called in device mode.
  * @retval None.
  */
void md_usb_dev_endpoint_status_clear(uint32_t ui32Endpoint, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // If this is endpoint 0, then the bits have different meaning and map
  // into the TX memory location.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Set the Serviced RxPktRdy bit to clear the RxPktRdy.
    //
    if (ui32Flags & USB_DEV_EP0_OUT_PKTRDY)
    {
      USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_RXRDYC_MSK;
    }

    //
    // Set the serviced Setup End bit to clear the SetupEnd status.
    //
    if (ui32Flags & USB_DEV_EP0_SETUP_END)
    {
      USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_SETENDC_MSK;
    }

    //
    // Clear the Sent Stall status flag.
    //
    if (ui32Flags & USB_DEV_EP0_SENT_STALL)
    {
      USB->CSR0L_TXCSRL &= ~(USB_CSR0L_TXCSRL_STALLED_MSK);
    }
  }
  else
  {
    //
    // Clear out any TX flags that were passed in.  Only
    // USB_DEV_TX_SENT_STALL and USB_DEV_TX_UNDERRUN must be cleared.
    //
    USB->CSR0L_TXCSRL &= ~(ui32Flags & (USB_CSR0L_TXCSRL_STALL_MSK | USB_DEV_TX_UNDERRUN));

    //
    // Clear out valid RX flags that were passed in.  Only
    // USB_DEV_RX_SENT_STALL, USB_DEV_RX_DATA_ERROR, and USB_DEV_RX_OVERRUN
    // must be cleared.
    //
    USB->RXCSR1 &= ~((ui32Flags & (USB_DEV_RX_SENT_STALL | USB_DEV_RX_DATA_ERROR |
                                   USB_DEV_RX_OVERRUN)) >> 16);
  }
}

/**
  * @brief  Determines the number of bytes of data available in a specified endpoint's
  *         FIFO.
  *
  *         This function returns the number of bytes of data currently available in the
  *         FIFO for the specified receive (OUT) endpoint.  It may be used prior to calling
  *         md_usb_hosdev_endpoint_data_get() to determine the size of buffer required to
  *         hold the newly-received packet.
  * @param  ui32Endpoint is the endpoint to access.
  * @retval This call returns the number of bytes available in a specified endpoint
  *         FIFO.
  */
uint32_t md_usb_hosdev_endpoint_datavai(uint32_t ui32Endpoint)
{
  uint8_t temp;        //use to clear warning in IAR system
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Get the address of the receive status register to use, based on the
  // endpoint.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Is there a packet ready in the FIFO?
    //
    if (USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_RXRDY_MSK)
    {
      //
      // Return the byte count in the FIFO.
      //
      return (uint32_t)(USB->RXCOUNT1);
    }

    return (0);
  }
  else
  {
    //
    // Is there a packet ready in the FIFO?
    //
    if (USB->RXCSR1 & USB_RXCSRL_RXRDY_MSK)
    {
      //
      // Return the byte count in the FIFO.
      //
      temp = USB->RXCOUNT1;
      return (uint32_t)(temp | USB->RXCOUNT2 << 8);
    }

    return (0);
  }
}

/**
  * @brief  Retrieves data from the specified endpoint's FIFO.
  *
  *         This function returns the data from the FIFO for the specified endpoint.
  *         The \e pui32Size parameter indicates the size of the buffer passed in
  *         the \e pui32Data parameter.  The data in the \e pui32Size parameter is
  *         changed to match the amount of data returned in the \e pui8Data parameter.
  *         If a zero-byte packet is received, this call does not return an error but
  *         instead just returns a zero in the \e pui32Size parameter.  The only error
  *         case occurs when there is no data packet available.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  pui8Data is a pointer to the data area used to return the data from
  *         the FIFO.
  * @param  pui32Size is initially the size of the buffer passed into this call
  *         via the \e pui8Data parameter.  It is set to the amount of data returned in
  *         the buffer.
  * @retval This call returns 0, or -1 if no packet was received.
  */
int32_t md_usb_hosdev_endpoint_data_get(uint32_t ui32Endpoint,
                                        uint8_t  *pui8Data,
                                        uint32_t *pui32Size)
{
  uint32_t ui32ByteCount, ui32FIFO;
  uint8_t temp;         //use to clear warning in IAR system
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Don't allow reading of data if the RxPktRdy bit is not set.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    if ((USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_RXRDY_MSK) == 0)
    {
      //
      // Can't read the data because none is available.
      //
      *pui32Size = 0;

      //
      // Return a failure since there is no data to read.
      //
      return (-1);
    }
  }
  else
  {
    if ((USB->RXCSR1 & USB_RXCSRL_RXRDY_MSK) == 0)
    {
      //
      // Can't read the data because none is available.
      //
      *pui32Size = 0;

      //
      // Return a failure since there is no data to read.
      //
      return (-1);
    }
  }

  //
  // Get the byte count in the FIFO.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    ui32ByteCount = (uint32_t)(USB->RXCOUNT1);
  }
  else
  {
    temp = USB->RXCOUNT1;
    ui32ByteCount = (uint32_t)(temp | (USB->RXCOUNT2 << 8));
  }

  //
  // Determine how many bytes are copied.
  //
  ui32ByteCount = (ui32ByteCount < *pui32Size) ? ui32ByteCount : *pui32Size;

  //
  // Return the number of bytes we are going to read.
  //
  *pui32Size = ui32ByteCount;

  //
  // Calculate the FIFO address.
  //
  ui32FIFO = (uint32_t)(&USB->EP0FIFO) + 4 * (uint32_t)USBEPToIndex(ui32Endpoint);

  //
  // Read the data out of the FIFO.
  //
  for (; ui32ByteCount > 0; ui32ByteCount--)
  {
    //
    // Read a byte at a time from the FIFO.
    //
    *pui8Data++ = *((volatile uint8_t *)(ui32FIFO));
  }

  //
  // Success.
  //
  return (0);
}

/**
  * @brief  Puts data into the specified endpoint's FIFO.
  *
  *         This function puts the data from the \e pui8Data parameter into the FIFO
  *         for this endpoint.  If a packet is already pending for transmission, then
  *         this call does not put any of the data into the FIFO and returns -1.  Care
  *         must be taken to not write more data than can fit into the FIFO
  *         allocated by the call to md_usb_dev_endpoint_config_set().
  * @param  ui32Endpoint is the endpoint to access.
  * @param  pui8Data is a pointer to the data area used as the source for the
  *         data to put into the FIFO.
  * @param  ui32Size is the amount of data to put into the FIFO.
  * @retval This call returns 0 on success, or -1 to indicate that the FIFO
  *         is in use and cannot be written.
  */
int32_t md_usb_hosdev_endpoint_data_put(uint32_t ui32Endpoint,
                                        uint8_t *pui8Data, uint32_t ui32Size)
{
  uint32_t ui32FIFO;

  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Don't allow transmit of data if the TxPktRdy bit is already set.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    if (USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_TXRDY_MSK)
      return (-1);
  }
  else
  {
    if (USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_TXPKTRDY_MSK)
      return (-1);
  }

  //
  // Calculate the FIFO address.
  //
  ui32FIFO = (uint32_t)(&USB->EP0FIFO) + 4 * (uint32_t)USBEPToIndex(ui32Endpoint);

  //
  // Write the data to the FIFO.
  //
  for (; ui32Size > 0; ui32Size--)
  {
    *((volatile uint8_t *)(ui32FIFO)) = *pui8Data++;
  }

  //
  // Success.
  //
  return (0);
}

/**
  * @brief  Starts the transfer of data from an endpoint's FIFO.
  *
  *         This function starts the transfer of data from the FIFO for a specified
  *         endpoint.  This function is called if the \b USB_EP_AUTO_SET bit was
  *         not enabled for the endpoint.  Setting the \e ui32TransType parameter
  *         allows the appropriate signaling on the USB bus for the type of transaction
  *         being requested.  The \e ui32TransType parameter must be one of the
  *         following:
  *
  *         - \b USB_TRANS_OUT for OUT transaction on any endpoint in host mode.
  *         - \b USB_TRANS_IN for IN transaction on any endpoint in device mode.
  *         - \b USB_TRANS_IN_LAST for the last IN transaction on endpoint zero in a
  *              sequence of IN transactions.
  *           \b USB_TRANS_SETUP for setup transactions on endpoint zero.
  *           \b USB_TRANS_STATUS for status results on endpoint zero.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32TransType is set to indicate what type of data is being sent.
  * @retval This call returns 0 on success, or -1 if a transmission is already
  *         in progress.
  */
int32_t md_usb_hosdev_endpoint_data_send(uint32_t ui32Endpoint,
    uint32_t ui32TransType)
{
  uint32_t ui32TxPktRdy;

  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Get the bit position of TxPktRdy based on the endpoint.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Don't allow transmit of data if the TxPktRdy bit is already set.
    //
    if (USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_TXRDY_MSK)
    {
      return (-1);
    }

    ui32TxPktRdy = ui32TransType & 0xff;
  }
  else
  {
    //
    // Don't allow transmit of data if the TxPktRdy bit is already set.
    //
    if (USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_TXPKTRDY_MSK)
    {
      return (-1);
    }

    ui32TxPktRdy = (ui32TransType >> 8) & 0xff;
  }

  //
  // Set TxPktRdy in order to send the data.
  //
  USB->CSR0L_TXCSRL = ui32TxPktRdy;

  //
  // Success.
  //
  return (0);
}

/**
  * @brief  Forces a flush of an endpoint's FIFO.
  *
  *         This function forces the USB controller to flush out the data in the FIFO.
  *         The function can be called with either host or device controllers and
  *         requires the \e ui32Flags parameter be one of \b USB_EP_HOST_OUT,
  *         \b USB_EP_HOST_IN, \b USB_EP_DEV_OUT, or \b USB_EP_DEV_IN.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags specifies if the IN or OUT endpoint is accessed.
  * @retval None.
  */
void md_usb_hosdev_endpoint_data_togglec(uint32_t ui32Endpoint,
    uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  if (ui32Flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN))
  {
    USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_CLRDATAT_MSK;
  }
  else
  {
    USB->RXCSR1 |= USB_RXCSRL_CLRDT_MSK;
  }
}

/**
  * @brief  Sets the number of packets to request when transferring multiple bulk
  *         packets.
  *
  *         This function sets the number of consecutive bulk packets to request
  *         when transferring multiple bulk packets with DMA.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Count is the number of packets to request.
  * @retval None.
  */
void md_usb_hosdev_endpoint_pkcount_set(uint32_t ui32Endpoint,
                                        uint32_t ui32Count)
{
  /* It's not supported by es32f0271 */
}

/**
  * @brief  Returns the current status of an endpoint.
  *
  *         This function returns the status of a specified endpoint.  If any of these
  *         status bits must be cleared, then the md_usb_dev_endpoint_status_clear() or the
  *         md_usb_hos_endpoint_status_clear() functions must be called.
  *
  *         The following are the status flags for host mode:
  *
  *         - \b USB_HOST_IN_PID_ERROR - PID error on the specified endpoint.
  *         - \b USB_HOST_IN_NOT_COMP - The device failed to respond to an IN request.
  *         - \b USB_HOST_IN_STALL - A stall was received on an IN endpoint.
  *         - \b USB_HOST_IN_DATA_ERROR - There was a CRC or bit-stuff error on an IN
  *           endpoint in Isochronous mode.
  *         - \b USB_HOST_IN_NAK_TO - NAKs received on this IN endpoint for more than
  *           the specified timeout period.
  *         - \b USB_HOST_IN_ERROR - Failed to communicate with a device using this IN
  *           endpoint.
  *         - \b USB_HOST_IN_FIFO_FULL - This IN endpoint's FIFO is full.
  *         - \b USB_HOST_IN_PKTRDY - Data packet ready on this IN endpoint.
  *         - \b USB_HOST_OUT_NAK_TO - NAKs received on this OUT endpoint for more than
  *           the specified timeout period.
  *         - \b USB_HOST_OUT_NOT_COMP - The device failed to respond to an OUT
  *           request.
  *         - \b USB_HOST_OUT_STALL - A stall was received on this OUT endpoint.
  *         - \b USB_HOST_OUT_ERROR - Failed to communicate with a device using this
  *           OUT endpoint.
  *         - \b USB_HOST_OUT_FIFO_NE - This endpoint's OUT FIFO is not empty.
  *         - \b USB_HOST_OUT_PKTPEND - The data transfer on this OUT endpoint has not
  *           completed.
  *         - \b USB_HOST_EP0_NAK_TO - NAKs received on endpoint zero for more than the
  *           specified timeout period.
  *         - \b USB_HOST_EP0_ERROR - The device failed to respond to a request on
  *           endpoint zero.
  *         - \b USB_HOST_EP0_IN_STALL - A stall was received on endpoint zero for an
  *           IN transaction.
  *         - \b USB_HOST_EP0_IN_PKTRDY - Data packet ready on endpoint zero for an IN
  *           transaction.
  *
  *         The following are the status flags for device mode:
  *
  *         - \b USB_DEV_OUT_SENT_STALL - A stall was sent on this OUT endpoint.
  *         - \b USB_DEV_OUT_DATA_ERROR - There was a CRC or bit-stuff error on an OUT
  *           endpoint.
  *         - \b USB_DEV_OUT_OVERRUN - An OUT packet was not loaded due to a full FIFO.
  *         - \b USB_DEV_OUT_FIFO_FULL - The OUT endpoint's FIFO is full.
  *         - \b USB_DEV_OUT_PKTRDY - There is a data packet ready in the OUT
  *           endpoint's FIFO.
  *         - \b USB_DEV_IN_NOT_COMP - A larger packet was split up, more data to come.
  *         - \b USB_DEV_IN_SENT_STALL - A stall was sent on this IN endpoint.
  *         - \b USB_DEV_IN_UNDERRUN - Data was requested on the IN endpoint and no
  *           data was ready.
  *         - \b USB_DEV_IN_FIFO_NE - The IN endpoint's FIFO is not empty.
  *         - \b USB_DEV_IN_PKTPEND - The data transfer on this IN endpoint has not
  *           completed.
  *         - \b USB_DEV_EP0_SETUP_END - A control transaction ended before Data End
  *           condition was sent.
  *         - \b USB_DEV_EP0_SENT_STALL - A stall was sent on endpoint zero.
  *         - \b USB_DEV_EP0_IN_PKTPEND - The data transfer on endpoint zero has not
  *           completed.
  *         - \b USB_DEV_EP0_OUT_PKTRDY - There is a data packet ready in endpoint
  *           zero's OUT FIFO.
  *
  * @param  The current status flags for the endpoint depending on mode.
  * @retval None.
  */
uint32_t md_usb_hosdev_endpoint_status(uint32_t ui32Endpoint)
{
  uint32_t ui32Status;

  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Get the TX portion of the endpoint status.
  //
  ui32Status = USB->CSR0L_TXCSRL;

  //
  // Get the RX portion of the endpoint status.
  // Return zero if ui32Endpoint is equal to USB_EP_0.
  //
  ui32Status |= (((ui32Endpoint == USB_EP_0) ? 0x00 : USB->RXCSR1) << 16);

  //
  // Return the endpoint status.
  //
  return (ui32Status);
}

/**
  * @brief  Disables endpoint interrupts on a specified USB controller.
  *
  *         This function disables endpoint interrupts for the USB controller specified
  *         by the \e ui32Base parameter.  The \e ui32Flags parameter specifies which
  *         endpoint interrupts to disable.  The flags passed in the \e ui32Flags
  *         parameters must be the definitions that start with \b USB_INTEP_* and not
  *         any other \b USB_INT flags.
  * @param  ui32IntFlags specifies which endpoint interrupts to disable.
  * @retval None.
  */
void md_usb_hosdev_endpoint_int_disable(uint32_t ui32IntFlags)
{
  //
  // If any transmit interrupts were disabled, then write the transmit
  // interrupt settings out to the hardware.
  //
  USB->TXIER &=
    ~(ui32IntFlags & (USB_INTEP_HOST_OUT | USB_INTEP_DEV_IN | USB_INTEP_0));

  //
  // If any receive interrupts were disabled, then write the receive
  // interrupt settings out to the hardware.
  //
  USB->RXIER &=
    ~((ui32IntFlags & (USB_INTEP_HOST_IN | USB_INTEP_DEV_OUT)) >> 16);
}

/**
  * @brief  Enable endpoint interrupts on a specified USB controller.
  *
  *         This function Enable endpoint interrupts for the USB controller specified
  *         by the \e ui32Base parameter.  The \e ui32Flags parameter specifies which
  *         endpoint interrupts to disable.  The flags passed in the \e ui32Flags
  *         parameters must be the definitions that start with \b USB_INTEP_* and not
  *         any other \b USB_INT flags.
  * @param  ui32IntFlags specifies which endpoint interrupts to Enable.
  * @retval None.
  */
void md_usb_hosdev_endpoint_int_enable(uint32_t ui32IntFlags)
{
  //
  // If any transmit interrupts were disabled, then write the transmit
  // interrupt settings out to the hardware.
  //
  USB->TXIER |=
    ui32IntFlags & (USB_INTEP_HOST_OUT | USB_INTEP_DEV_IN | USB_INTEP_0);

  //
  // If any receive interrupts were disabled, then write the receive
  // interrupt settings out to the hardware.
  //
  USB->RXIER |=
    ((ui32IntFlags & (USB_INTEP_HOST_IN | USB_INTEP_DEV_OUT)) >> 16);
}

/**
  * @brief  Returns the endpoint interrupt status on a specified USB controller.
  *
  *         This function reads endpoint interrupt status for a USB controller.  This
  *         call returns the current status for endpoint interrupts only, the control
  *         interrupt status is retrieved by calling md_usb_hosdev_int_status().  The bit
  *         values returned are compared against the \b USB_INTEP_* values.
  *         These values are grouped into classes for \b USB_INTEP_HOST_* and
  *         \b USB_INTEP_DEV_* values to handle both host and device modes with all
  *         endpoints.
  * @param  None.
  * @note   This call clears the source of all of the endpoint interrupts.
  * @retval Returns the status of the endpoint interrupts for a USB controller.
  */
uint32_t md_usb_hosdev_endpoint_int_status(void)
{
  uint32_t ui32Status;

  //
  // Get the transmit interrupt status.
  //
  ui32Status = USB->TXRIF;
  ui32Status |= (USB->RXRIF << 16);

  //
  // Clear the transmit interrupt status.
  //
  USB->TXICR = 0xff;
  USB->RXICR = 0xff;

  //
  // Return the combined interrupt status.
  //
  return (ui32Status);
}

/**
  * @brief  Change the mode of the USB controller to OTG.
  *
  *         This function changes the mode of the USB controller to OTG mode.
  *
  * @note   This function must only be called on microcontrollers that support
  *         OTG operation.
  * @param  None.
  * @retval None.
  */
uint32_t md_usb_endpoint_number_get(void)
{
  return 13;
}

/**
  * @} USB_MD_PF_ENDPOINT
  */

/** @addtogroup USB_MD_PF_FIFO USB Public FIFO Functions
  * @{
  */

/**
  * @brief  Returns the absolute FIFO address for a specified endpoint.
  *
  *         This function returns the actual physical address of the FIFO.  This
  *         address is needed when the USB is going to be used with the DMA
  *         controller and the source or destination address must be set to the
  *         physical FIFO address for a specified endpoint. This function can also be
  *         used to provide the physical address to manually read data from an
  *         endpoints FIFO.
  *
  * @param  ui32Endpoint specifies which endpoint's FIFO address to return.
  * @retval None.
  */
uint32_t md_usb_hosdev_fifo_addr_get(uint32_t ui32Endpoint)
{
  return (uint32_t)((uint32_t)(&USB->EP0FIFO) + ((uint32_t)USBEPToIndex(ui32Endpoint) << 2));
}

/**
  * @brief  Returns the FIFO configuration for an endpoint.
  *
  *         This function returns the starting address and size of the FIFO for a
  *         specified endpoint.  Endpoint zero does not have a dynamically configurable
  *         FIFO, so this function must not be called for endpoint zero.  The
  *         \e ui32Flags parameter specifies whether the endpoint's OUT or IN FIFO must
  *         be read.  If in host mode, the \e ui32Flags parameter must be
  *         \b USB_EP_HOST_OUT or \b USB_EP_HOST_IN, and if in device mode, the
  *         \e ui32Flags parameter must be either \b USB_EP_DEV_OUT or
  *         \b USB_EP_DEV_IN.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32FIFOAddress is the starting address for the FIFO.
  * @param  ui32FIFOSize is the size of the FIFO specified by one of the
  *         USB_FIFO_SZ_ values.
  * @param  ui32Flags specifies what information to set in the FIFO
  *         configuration.
  * @retval None.
  */
void md_usb_hosdev_fifo_config_get(uint32_t ui32Endpoint, uint32_t *pui32FIFOAddress,
                                   uint32_t *pui32FIFOSize, uint32_t ui32Flags)
{
  uint8_t temp;         //use to clear warning in IAR system
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // See if the transmit or receive FIFO is being configured.
  //
  if (ui32Flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN))
  {
    temp = USB->TXFIFO1 & 0xff;
    //
    // Get the transmit FIFO location and size for this endpoint.
    //
    *pui32FIFOAddress = (temp | ((USB->TXFIFO2 & 0x0f) << 8)) << 3;
    *pui32FIFOSize = (USB->TXFIFO2 & 0xe0) >> USB_TXFIFO2_MAXPKTSIZE_POSS;
  }
  else
  {
    temp = USB->RXFIFO1 & 0xff;
    //
    // Get the receive FIFO location and size for this endpoint.
    //
    *pui32FIFOAddress = (temp | ((USB->TXFIFO2 & 0x0f) << 8)) << 3;

    *pui32FIFOSize = (USB->RXFIFO2 & 0xe0) >> USB_RXFIFO2_MAXPKTSIZE_POSS;
  }
}

/**
  * @brief  Sets the FIFO configuration for an endpoint.
  *
  *         This function configures the starting FIFO RAM address and size of the FIFO
  *         for a specified endpoint.  Endpoint zero does not have a dynamically
  *         configurable FIFO, so this function must not be called for endpoint zero.
  *         The \e ui32FIFOSize parameter must be one of the values in the
  *         \b USB_FIFO_SZ_ values.
  *
  *         The \e ui32FIFOAddress value must be a multiple of 8 bytes and directly
  *         indicates the starting address in the USB controller's FIFO RAM.  For
  *         example, a value of 64 indicates that the FIFO starts 64 bytes into
  *         the USB controller's FIFO memory.  The \e ui32Flags value specifies whether
  *         the endpoint's OUT or IN FIFO must be configured.  If in host mode, use
  *         \b USB_EP_HOST_OUT or \b USB_EP_HOST_IN, and if in device mode, use
  *         \b USB_EP_DEV_OUT or \b USB_EP_DEV_IN.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32FIFOAddress is the starting address for the FIFO.
  * @param  ui32FIFOSize is the size of the FIFO specified by one of the
  *         USB_FIFO_SZ_ values.
  * @param  ui32Flags specifies what information to set in the FIFO
  *         configuration.
  * @retval None.
  */
void md_usb_hosdev_fifo_config_set(uint32_t ui32Endpoint, uint32_t ui32FIFOAddress,
                                   uint32_t ui32FIFOSize, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // See if the transmit or receive FIFO is being configured.
  //
  if (ui32Flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN))
  {
    //
    // Set the transmit FIFO location and size for this endpoint.
    //
    USB->TXFIFO1 = (uint8_t)((ui32FIFOAddress & 0xffff) >> 3);

    USB->TXFIFO2 = (uint8_t)((((ui32FIFOAddress & 0xffff) >> 3 >> 8) & 0x0f)
                             | (ui32FIFOSize) << USB_TXFIFO2_MAXPKTSIZE_POSS);
    USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_FLUSHFIFO_MSK;
  }
  else
  {
    //
    // Set the receive FIFO location and size for this endpoint.
    //
    USB->RXFIFO1 = (uint8_t)((ui32FIFOAddress & 0xffff) >> 3);

    USB->RXFIFO2 = (uint8_t)((((ui32FIFOAddress & 0xffff) >> 3 >> 8) & 0x0f)
                             | (ui32FIFOSize) << USB_RXFIFO2_MAXPKTSIZE_POSS);
    USB->RXCSR1 |= USB_RXCSRL_FLUSH_MSK;
  }
}

/**
  * @brief  Forces a flush of an endpoint's FIFO.
  *
  *         This function forces the USB controller to flush out the data in the FIFO.
  *         The function can be called with either host or device controllers and
  *         requires the \e ui32Flags parameter be one of \b USB_EP_HOST_OUT,
  *         \b USB_EP_HOST_IN, \b USB_EP_DEV_OUT, or \b USB_EP_DEV_IN.
  *
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags specifies if the IN or OUT endpoint is accessed.
  * @retval None.
  */
void md_usb_hosdev_fifo_flush(uint32_t ui32Endpoint, uint32_t ui32Flags)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Endpoint zero has a different register set for FIFO flushing.
  //
  if (ui32Endpoint == USB_EP_0)
  {
    //
    // Nothing in the FIFO if neither of these bits are set.
    //
    if ((USB->CSR0L_TXCSRL
         & (USB_CSR0L_TXCSRL_TXRDY_MSK | USB_CSR0L_TXCSRL_RXRDY_MSK)) != 0)
    {
      //
      // Hit the Flush FIFO bit.
      //
      USB->CSR0H_TXCSRH |= USB_CSR0H_TXCSRH_FLUSH_MSK;
    }
  }
  else
  {
    //
    // Only reset the IN or OUT FIFO.
    //
    if (ui32Flags & (USB_EP_HOST_OUT | USB_EP_DEV_IN))
    {
      //
      // Make sure the FIFO is not empty.
      //
      if (USB->CSR0L_TXCSRL & USB_CSR0L_TXCSRL_TXPKTRDY_MSK)
      {
        //
        // Hit the Flush FIFO bit.
        //
        USB->CSR0L_TXCSRL |= USB_CSR0L_TXCSRL_FLUSHFIFO_MSK;
      }
    }
    else
    {
      //
      // Make sure that the FIFO is not empty.
      //
      if (USB->RXCSR1 & USB_RXCSRL_RXRDY_MSK)
      {
        //
        // Hit the Flush FIFO bit.
        //
        USB->RXCSR1 |= USB_RXCSRL_FLUSH_MSK;
      }
    }
  }
}

/**
  * @} USB_MD_PF_FIFO
  */


/** @addtogroup USB_MD_PF_EXPWR USB Public External Power Functions
  * @{
  */

//
// The following pwr function is not supported by es32f0271
//
/**
  * @brief  Disables the external power pin.
  *
  *         This function disables the USBnEPEN signal, which disables an external
  *         power supply in host mode operation.
  *
  * @note   This function must only be called in host mode.
  * @retval None.
  */
__weak void md_usb_hos_pwr_disable(void)
{
}

/**
  * @brief  Enable the external power pin.
  *
  *         This function disables the USBnEPEN signal, which disables an external
  *         power supply in host mode operation.
  *
  * @note   This function must only be called in host mode.
  * @retval None.
  */
__weak void md_usb_hos_pwr_enable(void)
{
  //
  // Although Vbus is not supported by es32f0271,we provide Vbus
  // from outside.
  //

}

/**
  * @brief  Sets the configuration for USB power fault.
  *
  *         This function controls how the USB controller uses its external power
  *         control pins (USBnPFLT and USBnEPEN).  The flags specify the power
  *         fault level sensitivity, the power fault action, and the power enable level
  *         and source.
  *
  *         One of the following can be selected as the power fault level sensitivity:
  *
  *         - \b USB_HOST_PWRFLT_LOW - An external power fault is indicated by the pin
  *                                    being driven low.
  *         - \b USB_HOST_PWRFLT_HIGH - An external power fault is indicated by the pin
  *                                     being driven high.
  *
  *         One of the following can be selected as the power fault action:
  *
  *         - \b USB_HOST_PWRFLT_EP_NONE - No automatic action when power fault
  *           detected.
  *         - \b USB_HOST_PWRFLT_EP_TRI - Automatically tri-state the USBnEPEN pin on a
  *                                       power fault.
  *         - \b USB_HOST_PWRFLT_EP_LOW - Automatically drive USBnEPEN pin low on a
  *                                       power fault.
  *         - \b USB_HOST_PWRFLT_EP_HIGH - Automatically drive USBnEPEN pin high on a
  *                                        power fault.
  *
  *         One of the following can be selected as the power enable level and source:
  *
  *         - \b USB_HOST_PWREN_MAN_LOW - USBnEPEN is driven low by the USB controller
  *                                       when USBHostPwrEnable() is called.
  *         - \b USB_HOST_PWREN_MAN_HIGH - USBnEPEN is driven high by the USB
  *                                        controller when USBHostPwrEnable() is
  *                                        called.
  *         - \b USB_HOST_PWREN_AUTOLOW - USBnEPEN is driven low by the USB controller
  *                                       automatically if USBOTGSessionRequest() has
  *                                       enabled a session.
  *         - \b USB_HOST_PWREN_AUTOHIGH - USBnEPEN is driven high by the USB
  *                                        controller automatically if
  *                                        USBOTGSessionRequest() has enabled a
  *                                        session.
  *
  *         When using the VBUS glitch filter, the \b USB_HOST_PWREN_FILTER can be
  *         addded to ignore small, short drops in VBUS level caused by high power
  *         consumption.  This feature is mainly used to avoid causing VBUS errors
  *         caused by devices with high in-rush current.
  *
  * @note   This function must only be called on microcontrollers that support
  *         host mode or OTG operation. The \b USB_HOST_PWREN_AUTOLOW and
  *         \b USB_HOST_PWREN_AUTOHIGH parameters can only be specified on devices that
  *         support OTG operation.
  * @retval None.
  */
void md_usb_hos_pwr_config(uint32_t ui32Flags)
{
}

/**
  * @brief  Disable power fault detection.
  *
  *         This function enables power fault detection in the USB controller.  If the
  *         USBnPFLT pin is not in use, this function must not be used.
  *
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_pwrfault_disable(void)
{
}

/**
  * @brief  Enable power fault detection.
  *
  *         This function enables power fault detection in the USB controller.  If the
  *         USBnPFLT pin is not in use, this function must not be used.
  *
  * @note   This function must only be called in host mode.
  * @retval None.
  */
void md_usb_hos_pwrfault_enable(void)
{
}

/**
  * @} USB_MD_PF_EXPWR
  */

/** @addtogroup USB_MD_PF_LPM USB Public LPM Functions
  * @{
  */

//
// LPM is not supported by es32f0271
//

/**
  * @brief  Sends an LPM request to a device at a specified address and endpoint number.
  *
  *         This function sends an LPM request to a connected device in host mode.
  *         The \e ui32Address parameter specifies the device address and has a range
  *         of values from 1 to 127.   The \e ui32Endpoint parameter specifies the
  *         endpoint on the device to which to send the LPM request and must be one of
  *         the \b USB_EP_* values. The function returns before the LPM request is
  *         sent, requiring the caller to poll the md_usb_lpm_status() function or wait
  *         for an interrupt to signal completion of the LPM transaction.  This
  *         function must only be called after the md_usb_hos_lpm_config() has configured
  *         the LPM transaction settings.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  ui32Address is the target device address for the LPM request.
  * @param  ui32Endpoint is the target endpoint for the LPM request.
  * @retval None.
  */
void md_usb_hos_lpm_send(uint32_t ui32Address,
                         uint32_t uiEndpoint)
{
}

/**
  * @brief  Sets the global configuration for all LPM requests.
  *
  *         This function sets the global configuration options for LPM transactions
  *         and must be called at least once before ever calling md_usb_hos_lpm_send().  The
  *         \e ui32ResumeTime specifies the length of time that the host drives resume
  *         signaling on the bus in microseconds.  The valid values
  *         for \e ui32ResumeTime are from 50us to 1175us in 75us increments.  The
  *         remaining configuration is specified by the \e ui32Config parameter and
  *         includes the following options:
  *
  *         - \b USB_HOST_LPM_RMTWAKE allows the device to signal a remote wake from
  *           the LPM state.
  *         - \b USB_HOST_LPM_L1 is the LPM mode to enter and must always be included
  *           in the configuration.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  ui32Address is the target device address for the LPM request.
  * @param  ui32Endpoint is the target endpoint for the LPM request.
  * @retval None.
  */
void md_usb_hos_lpm_config(uint32_t ui32ResumeTime,
                           uint32_t ui32Config)
{
}

/**
  * @brief  Returns if remote wake is currently enabled.
  *
  *         This function returns the current state of the remote wake setting for host
  *         or device mode operation.  If the controller is acting as a host this
  *         returns the current setting that is sent to devices when LPM requests are
  *         sent to a device.  If the controller is in device mode, this function
  *         returns the state of the last LPM request sent from the host and indicates
  *         if the host enabled remote wakeup.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval The \b true if remote wake is enabled or \b false if it is not.
  */
bool md_usb_lpm_remotewake_is_enabled(void)
{
  return 0;
}

/**
  * @brief  Initiates resume signaling to wake a device from LPM suspend mode.
  *
  *         In host mode, this function initiates resume signaling to wake a device
  *         that has entered an LPM-triggered low power mode.  This LPM-triggered low
  *         power mode is entered when the md_usb_hos_lpm_send() is called to put a specific
  *         device into a low power state.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval None.
  */
void md_usb_hos_lpm_resume(void)
{
}

/**
  * @brief  Initiates remote wake signaling to request the device to leave LPM
  *         suspend mode.
  *
  *         This function initiates remote wake signaling to request that the host
  *         wake a device that has entered an LPM-triggered low power mode.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval None.
  */
void md_usb_dev_lpm_remotewake(void)
{
}

/**
  * @brief  Configures the USB device mode response to LPM requests.
  *
  *         This function sets the global configuration options for LPM
  *         transactions in device mode and must be called before ever calling
  *         md_usb_dev_lpm_enable() to set the configuration for LPM transactions.  The
  *         configuration options in device mode are specified in the \e ui32Config
  *         parameter and include one of the following:
  *
  *         - \b USB_DEV_LPM_NONE disables the USB controller from responding to LPM
  *           transactions.
  *         - \b USB_DEV_LPM_EN enables the USB controller to respond to LPM
  *           and extended transactions.
  *         - \b USB_DEV_LPM_EXTONLY enables the USB controller to respond to
  *           extended transactions, but not LPM transactions.
  *
  *         The \e ui32Config option can also optionally include the
  *         \b USB_DEV_LPM_NAK value to cause the USB controller to NAK all
  *         transactions other than an LPM transaction once the USB controller is in
  *         LPM suspend mode.  If this value is not included in the \e ui32Config
  *         parameter, the USB controller does not respond in suspend mode.
  *
  *         The USB controller does not enter LPM suspend mode until the application
  *         calls the md_usb_dev_lpm_enable() function.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  ui32Config is the combination of configuration options for LPM
  *         transactions in device mode.
  * @retval None.
  */
void md_usb_dev_lpm_config(uint32_t ui32Config)
{
}

/**
  * @brief  Enables the USB controller to respond to LPM suspend requests.
  *
  *         This function is used to automatically respond to an LPM sleep request from
  *         the USB host controller.  If there is no data pending in any transmit
  *         FIFOs, then the USB controller acknowledges the packet and enters the
  *         LPM L1 state and generates the \b USB_INTLPM_ACK interrupt.  If the USB
  *         controller has pending transmit data in at least one FIFO, then the USB
  *         controller responds with NYET and signals the \b USB_INTLPM_INCOMPLETE or
  *         \b USB_INTLPM_NYET depending on if data is pending in receive or transmit
  *         FIFOs.  A call to md_usb_dev_lpm_enable() is required after every
  *         LPM resume event to re-enable LPM mode.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval None.
  */
void md_usb_dev_lpm_enable(void)
{
}

/**
  * @brief  Disables the USB controller to respond to LPM suspend requests.
  *
  *         This function disables the USB controller from responding to LPM
  *         transactions.  When the device enters LPM L1 mode, the USB controller
  *         automatically disables responding to further LPM transactions.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval None.
  */
void md_usb_dev_lpm_disable(void)
{
}

/**
  * @brief  Returns the current link state setting.
  *
  *         This function returns the current link state setting for the USB
  *         controller.  When the controller is operating as a host, this link
  *         state is sent with an LPM request.  When the controller is acting
  *         as a device, this link state was received by the last LPM transaction
  *         whether it was acknowledged or stalled because the requested
  *         LPM mode is not supported.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval The current LPM link state.
  */
uint32_t md_usb_lpm_link_state_get(void)
{
  return 0;
}

/**
  * @brief  Returns the current LPM endpoint value.
  *
  *         This function returns the current LPM endpoint value.  The meaning of the
  *         value depends on the mode of operation of the USB controller.  When in
  *         device mode, the value returned is the endpoint that received the last
  *         LPM transaction.  When in host mode this is the endpoint that was last
  *         sent an LPM transaction, or the endpoint that is configured to be sent when
  *         the LPM transaction is triggered.  The value returned is in the
  *         \b USB_EP_[0-7] value and a direct endpoint index.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval The last endpoint to receive an LPM request in device mode or the
  *         endpoint that the host sends an LPM request as one of the \b USB_EP_[0-7]
  *         values.
  */
uint32_t md_usb_lpm_endpoint_get(void)
{
  return 0;
}

/**
  * @brief  Returns the current LPM interrupt status.
  *
  *         This function returns the current LPM interrupt status for the USB
  *         controller.
  *
  *         The valid interrupt status bits when the USB controller is acting as a host
  *         are the following:
  *
  *         - \b USB_INTLPM_ERROR a bus error occurred in the transmission of an LPM
  *           transaction.
  *         - \b USB_INTLPM_RESUME the USB controller has resumed from the LPM low
  *           power state.
  *         - \b USB_INTLPM_INCOMPLETE the LPM transaction failed because a timeout
  *           occurred or there were bit errors in the response for three attempts.
  *         - \b USB_INTLPM_ACK the device has acknowledged an LPM transaction.
  *         - \b USB_INTLPM_NYET the device has responded with a NYET to an LPM
  *           transaction.
  *         - \b USB_INTLPM_STALL the device has stalled an LPM transaction.
  *
  *         The valid interrupt status bits when the USB controller is acting as a
  *         device are the following:
  *
  *         - \b USB_INTLPM_ERROR an LPM transaction was received that has an
  *           unsupported link state field.  The transaction was stalled, but the
  *           requested link state can still be read using the md_usb_lpm_link_state_get()
  *           function.
  *         - \b USB_INTLPM_RESUME the USB controller has resumed from the LPM low
  *           power state.
  *         - \b USB_INTLPM_INCOMPLETE the USB controller responded to an LPM
  *           transaction with a NYET because data was still in the transmit FIFOs.
  *         - \b USB_INTLPM_ACK the USB controller acknowledged an LPM transaction and
  *           is now in the LPM suspend mode.
  *         - \b USB_INTLPM_NYET the USB controller responded to an LPM transaction
  *           with a NYET because LPM transactions are not yet enabled by a call to
  *           md_usb_dev_lpm_enable().
  *         - \b USB_INTLPM_STALL the USB controller has stalled an incoming LPM
  *           transaction.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  None.
  * @retval The \b true if remote wake is enabled or \b false if it is not.
  */
uint32_t md_usb_lpm_status(void)
{
  return 0;
}

/**
  * @brief  Enables LPM interrupts.
  *
  *         This function enables a set of LPM interrupts so that they can trigger a
  *         USB interrupt.  The \e ui32Ints parameter specifies which of the
  *         \b USB_INTLPM_* to enable.
  *
  *         The valid interrupt status bits when the USB controller is acting as a host
  *         are the following:
  *
  *         - \b USB_INTLPM_ERROR a bus error occurred in the transmission of an LPM
  *           transaction.
  *         - \b USB_INTLPM_RESUME the USB controller has resumed from LPM low power
  *           state.
  *         - \b USB_INTLPM_INCOMPLETE the LPM transaction failed because a timeout
  *           occurred or there were bit errors in the response for three attempts.
  *         - \b USB_INTLPM_ACK the device has acknowledged an LPM transaction.
  *         - \b USB_INTLPM_NYET the device has responded with a NYET to an LPM
  *           transaction.
  *         - \b USB_INTLPM_STALL the device has stalled an LPM transaction.
  *
  *         The valid interrupt status bits when the USB controller is acting as a
  *         device are the following:
  *
  *         - \b USB_INTLPM_ERROR an LPM transaction was received that has an
  *           unsupported link state field.  The transaction was stalled, but the
  *           requested link state can still be read using the md_usb_lpm_link_state_get()
  *           function.
  *         - \b USB_INTLPM_RESUME the USB controller has resumed from the LPM low
  *           power state.
  *         - \b USB_INTLPM_INCOMPLETE the USB controller responded to an LPM
  *           transaction with a NYET because data was still in the transmit FIFOs.
  *         - \b USB_INTLPM_ACK the USB controller acknowledged an LPM transaction and
  *           is now in the LPM suspend mode.
  *         - \b USB_INTLPM_NYET the USB controller responded to an LPM transaction
  *           with a NYET because LPM transactions are not yet enabled by a call to
  *           md_usb_dev_lpm_enable().
  *         - \b USB_INTLPM_STALL the USB controller has stalled an incoming LPM
  *           transaction.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  ui32Ints specifies which LPM interrupts to enable.
  * @retval None.
  */
void md_usb_lpm_int_enable(uint32_t ui32Ints)
{
}

/**
  * @brief  Disables LPM interrupts.
  *
  *         This function disables the LPM interrupts specified in the \e ui32Ints
  *         parameter, preventing them from triggering a USB interrupt.
  *
  *         The valid interrupt status bits when the USB controller is acting as a host
  *         are the following:
  *
  *         - \b USB_INTLPM_ERROR a bus error occurred in the transmission of an LPM
  *           transaction.
  *         - \b USB_INTLPM_RESUME the USB controller has resumed from LPM low power
  *           state.
  *         - \b USB_INTLPM_INCOMPLETE the LPM transaction failed because a timeout
  *           occurred or there were bit errors in the response for three attempts.
  *         - \b USB_INTLPM_ACK the device has acknowledged an LPM transaction.
  *         - \b USB_INTLPM_NYET the device has responded with a NYET to an LPM
  *           transaction.
  *         - \b USB_INTLPM_STALL the device has stalled an LPM transaction.
  *
  *         The valid interrupt status bits when the USB controller is acting as a
  *         device are the following:
  *
  *         - \b USB_INTLPM_ERROR an LPM transaction was received that has an
  *           unsupported link state field.  The transaction was stalled, but the
  *           requested link state can still be read using the md_usb_lpm_link_state_get()
  *           function.
  *         - \b USB_INTLPM_RESUME the USB controller has resumed from the LPM low
  *           power state.
  *         - \b USB_INTLPM_INCOMPLETE the USB controller responded to an LPM
  *           transaction with a NYET because data was still in the transmit FIFOs.
  *         - \b USB_INTLPM_ACK the USB controller acknowledged an LPM transaction and
  *           is now in the LPM suspend mode.
  *         - \b USB_INTLPM_NYET the USB controller responded to an LPM transaction
  *           with a NYET because LPM transactions are not yet enabled by a call to
  *           md_usb_dev_lpm_enable().
  *         - \b USB_INTLPM_STALL the USB controller has stalled an incoming LPM
  *           transaction.
  *
  * @note   This function must only be called in host mode. The USB LPM feature
  *         is not available on all ES32 devices. Please consult the data sheet for
  *         the ES32 device that you are using to determine if this feature is
  *         available.
  * @param  ui32Ints specifies which LPM interrupts to disable.
  * @retval None.
  */
void md_usb_lpm_int_disable(uint32_t ui32Ints)
{
}

/**
  * @} USB_MD_PF_LPM
  */

/** @addtogroup USB_MD_PF_ULPI USB Public ULPI Functions
  * @{
  */

//
// ULPI is not supported by es32f0271
//

/**
  * @brief  Configures the USB controller's ULPI function.
  *
  *         This function is used to configure the USB controller's ULPI function.
  *         The configuration options are set in the \e ui32Config parameter and are a
  *         logical OR of the following values:
  *
  *         - \b USB_ULPI_EXTVBUS enables the external ULPI PHY as the source for VBUS
  *           signaling.
  *         - \b USB_ULPI_EXTVBUS_IND enables the external ULPI PHY to detect external
  *           VBUS over-current condition.
  *
  * @note   The USB ULPI feature is not available on all Tiva devices.
  *         Please consult the data sheet for the Tiva device that you
  *         are using to determine if this feature is available.
  * @param  ui32Config contains the configuration options.
  * @retval None.
  */
void md_usb_ulpi_config(uint32_t ui32Config)
{
}

/**
  * @brief  Enables the USB controller's ULPI function.
  *
  *         This function enables the USB controller's ULPI function and must be
  *         called before attempting to access an external ULPI-connected USB PHY.
  *
  * @note   The USB ULPI feature is not available on all Tiva devices.
  *         Please consult the data sheet for the Tiva device that you
  *         are using to determine if this feature is available.
  * @param  None.
  * @retval None.
  */
void md_usb_ulpi_enable(void)
{
}

/**
  * @brief  Disables the USB controller's ULPI function.
  *
  *         This function Disables the USB controller's ULPI function and must be
  *         called before attempting to access an external ULPI-connected USB PHY.
  *
  * @note   The USB ULPI feature is not available on all Tiva devices.
  *         Please consult the data sheet for the Tiva device that you
  *         are using to determine if this feature is available.
  * @param  None.
  * @retval None.
  */
void md_usb_ulpi_disable(void)
{
}

/**
  * @brief  Disables the USB controller's ULPI function.
  *
  *         This function Disables the USB controller's ULPI function and must be
  *         called before attempting to access an external ULPI-connected USB PHY.
  *
  * @note   The USB ULPI feature is not available on all Tiva devices.
  *         Please consult the data sheet for the Tiva device that you
  *         are using to determine if this feature is available.
  * @param  None.
  * @retval None.
  */
uint8_t md_usb_ulpi_reg_read(uint8_t ui8Reg)
{
  return 0;
}

/**
  * @brief  Writes a value to a register on an external ULPI-connected USB PHY.
  *
  *         This function writes the register address specified in the \e ui8Reg
  *         parameter with the value specified in the \e ui8Data parameter using the
  *         ULPI function.  This function is blocking and only returns when the
  *         write access completes.  The function does not return if there is not a
  *         ULPI-connected USB PHY present.
  *
  * @note   The USB ULPI feature is not available on all Tiva devices.
  *         Please consult the data sheet for the Tiva device that you
  *         are using to determine if this feature is available.
  * @param  ui8Reg specifies the register address to write.
  * @param  ui8Data specifies the data to write.
  * @retval None.
  */
void md_usb_ulpi_reg_write(uint8_t ui8Reg,
                           uint8_t ui8Data)
{
}

/**
  * @} USB_MD_PF_ULPI
  */

/** @addtogroup USB_MD_PF_DMA USB Public DMA Functions
  * @{
  */

//
// USB DMA is not supported by es32f0271
//

/**
  * @brief  Sets the DMA channel to use for a specified endpoint.
  *
  *         This function is used to configure which DMA channel to use with a specified
  *         endpoint.  Receive DMA channels can only be used with receive endpoints
  *         and transmit DMA channels can only be used with transmit endpoints.
  *
  * @note   This function only has an effect on microcontrollers that have the
  *         ability to change the DMA channel for an endpoint.  Calling this function
  *         on other devices has no effect.
  * @param  ui32Endpoint specifies which endpoint's FIFO address to return.
  * @param  ui32Channel specifies which DMA channel to use for which endpoint.
  * @retval None.
  */
void md_usb_dma_endpoint_channel_set(uint32_t ui32Endpoint,
                                     uint32_t ui32Channel)
{
  //
  // It is not supported by es32f0271
  //
  return;
}

/**
  * @brief  Enable DMA on a specified endpoint.
  *
  *         This function enables DMA on a specified endpoint and configures the mode
  *         according to the values in the \e ui32Flags parameter.  The \e ui32Flags
  *         parameter must have \b USB_EP_DEV_IN or \b USB_EP_DEV_OUT set.  Once this
  *         function is called the only DMA or error interrupts are generated by the
  *         USB controller.
  *
  * @note   This function only has an effect on microcontrollers that have the
  *         ability to change the DMA channel for an endpoint.  Calling this function
  *         on other devices has no effect.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags specifies which direction and what mode to use when
  *         enabling DMA.
  * @retval None.
  */
void md_usb_dma_endpoint_enable(uint32_t ui32Endpoint,
                                uint32_t ui32Flags)
{
  //
  // It is not supported by es32f0271
  //
  return;
}

/**
  * @brief  Disable DMA on a specified endpoint.
  *
  *         This function disables DMA on a specified endpoint to allow non-DMA USB
  *         transactions to generate interrupts normally.  The \e ui32Flags parameter
  *         must be \b USB_EP_DEV_IN or \b USB_EP_DEV_OUT; all other bits are ignored.
  *
  * @note   This function only has an effect on microcontrollers that have the
  *         ability to change the DMA channel for an endpoint.  Calling this function
  *         on other devices has no effect.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Flags specifies which direction to disable.
  * @retval None.
  */
void md_usb_dma_endpoint_disable(uint32_t ui32Endpoint,
                                 uint32_t ui32Flags)
{
  //
  // It is not supported by es32f0271
  //
  return;
}

/**
  * @brief  Configure the DMA settings for an endpoint.
  *
  *         This function configures the DMA settings for a specified endpoint without
  *         changing other options that may already be configured.  In order for the
  *         DMA transfer to be enabled, the md_usb_dma_endpoint_enable() function must be
  *         called before starting the DMA transfer.  The configuration
  *         options are passed in the \e ui32Config parameter and can have the values
  *         described below.
  *
  *         One of the following values to specify direction:
  *         - \b USB_EP_HOST_OUT or \b USB_EP_DEV_IN - This setting is used with
  *           DMA transfers from memory to the USB controller.
  *         - \b USB_EP_HOST_IN or \b USB_EP_DEV_OUT - This setting is used with
  *           DMA transfers from the USB controller to memory.
  *
  *         One of the following values:
  *         - \b USB_EP_DMA_MODE_0(default) - This setting is typically used for
  *           transfers that do not span multiple packets or when interrupts are
  *           required for each packet.
  *         - \b USB_EP_DMA_MODE_1 - This setting is typically used for
  *           transfers that span multiple packets and do not require interrupts
  *           between packets.
  *
  *         Values only used with \b USB_EP_HOST_OUT or \b USB_EP_DEV_IN:
  *         - \b USB_EP_AUTO_SET - This setting is used to allow transmit DMA transfers
  *           to automatically be sent when a full packet is loaded into a FIFO.
  *           This is needed with \b USB_EP_DMA_MODE_1 to ensure that packets go
  *           out when the FIFO becomes full and the DMA has more data to send.
  *
  *         Values only used with \b USB_EP_HOST_IN or \b USB_EP_DEV_OUT:
  *         - \b USB_EP_AUTO_CLEAR - This setting is used to allow receive DMA
  *           transfers to automatically be acknowledged as they are received.  This is
  *           needed with \b USB_EP_DMA_MODE_1 to ensure that packets continue to
  *           be received and acknowledged when the FIFO is emptied by the DMA
  *           transfer.
  *
  *         Values only used with \b USB_EP_HOST_IN:
  *         - \b USB_EP_AUTO_REQUEST - This setting is used to allow receive DMA
  *           transfers to automatically request a new IN transaction when the
  *           previous transfer has emptied the FIFO.  This is typically used in
  *           conjunction with \b USB_EP_AUTO_CLEAR so that receive DMA transfers
  *           can continue without interrupting the main processor.
  *
  * @note   This function only has an effect on microcontrollers that have the
  *         ability to change the DMA channel for an endpoint.  Calling this function
  *         on other devices has no effect.
  * @param  ui32Endpoint is the endpoint to access.
  * @param  ui32Config specifies the configuration options for an endpoint.
  * @retval None.
  */
void md_usb_dma_endpoint_config(uint32_t ui32Endpoint, uint32_t ui32Config)
{
  //
  //Chose endpoint.
  //
  USB->INDEX = (uint8_t)USBEPToIndex(ui32Endpoint);

  //
  // Host out or device in.
  //
  if ((ui32Config & USB_EP_HOST_OUT) && (ui32Config & USB_EP_AUTO_SET))
  {
    USB->CSR0H_TXCSRH |= USB_CSR0H_TXCSRH_AUTOSET_MSK;
  }
  else
  {
    if (ui32Config & USB_EP_AUTO_REQUEST)
    {
      USB->RXCSR2 |= USB_RXCSRH_AUTOREQ_MSK;
    }

    if (ui32Config & USB_EP_AUTO_CLEAR)
    {
      USB->RXCSR2 |= USB_RXCSRH_AUTOCLR_MSK;
    }
  }
}

/**
  * @brief  Assigns and configures an endpoint to a specified integrated USB DMA
  *         channel.
  *
  *         This function assigns an endpoint and configures the settings for a
  *         USB DMA channel.  The \e ui32Endpoint parameter is one of the
  *         \b USB_EP_* values and the \e ui32Channel value is a zero-based index of
  *         the DMA channel to configure.  The \e ui32Config parameter is a combination
  *         of the \b USB_DMA_CFG_* values using the following guidelines.
  *
  *         Use one of the following to set the DMA burst mode:
  *         - \b USB_DMA_CFG_BURST_NONE disables bursting.
  *         - \b USB_DMA_CFG_BURST_4 sets the DMA burst size to 4 words.
  *         - \b USB_DMA_CFG_BURST_8 sets the DMA burst size to 8 words.
  *         - \b USB_DMA_CFG_BURST_16 sets the DMA burst size to 16 words.
  *
  *         Use one of the following to set the DMA mode:
  *         - \b USB_DMA_CFG_MODE_0 is typically used when only a single packet is
  *           being sent via DMA and triggers one completion interrupt per packet.
  *         - \b USB_DMA_CFG_MODE_1 is typically used when multiple packets are being
  *           sent via DMA and triggers one completion interrupt per transfer.
  *
  *         Use one of the following to set the direction of the transfer:
  *         - \b USB_DMA_CFG_DIR_RX selects a DMA transfer from the endpoint to a
  *           memory location.
  *         - \b USB_DMA_CFG_DIR_TX selects a DMA transfer to the endpoint from a
  *           memory location.
  *
  *         The following two optional settings allow an application to immediately
  *         enable the DMA transfer and/or DMA interrupts when configuring the DMA
  *         channel:
  *         - \b USB_DMA_CFG_INT_EN enables interrupts for this channel immediately so
  *           that an added call to md_usb_dma_channel_int_enable() is not necessary.
  *         - \b USB_DMA_CFG_EN enables the DMA channel immediately so that an added
  *           call to md_usb_dma_channel_enable() is not necessary.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller or if it must use the DMA controller for DMA transfers.
  * @param  ui32Channel specifies which DMA channel to access.
  * @param  ui32Endpoint is the endpoint to assign to the USB DMA channel.
  * @param  ui32Config is used to specify the configuration of the USB DMA channel.
  * @retval None.
  */
void md_usb_dma_channel_config(uint32_t ui32Channel,
                               uint32_t ui32Endpoint, uint32_t ui32Config)
{
  //
  // It is not supported by es32f0271
  //
}

/**
  * @brief  Sets the source or destination address for an integrated USB DMA transfer
  *         on a specified channel.
  *
  *         This function sets the source or destination address for the USB DMA
  *         channel number specified in the \e ui32Channel parameter.  The
  *         \e ui32Channel value is a zero-based index of the USB DMA channel.  The
  *         \e pvAddress parameter is a source address if the transfer type for the DMA
  *         channel is transmit and a destination address if the transfer type is
  *         receive.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller or if it must use the DMA controller for DMA transfers.
  * @param  ui32Channel specifies which DMA channel to access.
  * @param  pvAddress specifies the source or destination address for the USB
  *         DMA transfer.
  * @retval None.
  */
void md_usb_dma_channel_address_set(uint32_t ui32Channel,
                                    void *pvAddress)
{
  //
  // It is not supported by es32f0271
  //
  return;
}

/**
  * @brief  Returns the source or destination address for the specified integrated USB
  *         DMA channel.
  *
  *         This function returns the DMA address for the channel number specified
  *         in the \e ui32Channel parameter.  The \e ui32Channel value is a zero-based
  *         index of the DMA channel to query.  This function must not be used on
  *         devices that return \b USB_CONTROLLER_VER_0 from the USBControllerVersion()
  *         function.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller or if it must use the DMA controller for DMA transfers.
  * @param  ui32Channel specifies which DMA channel to access.
  * @retval The current DMA address for a USB DMA channel.
  */
void *md_usb_dma_channel_address_get(uint32_t ui32Channel)
{
  //
  // It is not supported by es32f0271
  //
  return 0;
}

/**
  * @brief  Sets the transfer count for an integrated USB DMA channel.
  *
  *         This function sets the USB DMA transfer count in bytes for the channel
  *         number specified in the \e ui32Channel parameter.  The \e ui32Channel
  *         value is a zero-based index of the DMA channel.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller or if it must use the DMA controller for DMA transfers.
  * @param  ui32Count specifies the number of bytes to transfer.
  * @param  ui32Channel specifies which DMA channel to access.
  * @retval None.
  */
void md_usb_dma_channel_count_set(uint32_t ui32Count,
                                  uint32_t ui32Channel)
{
  //
  // It is not supported by es32f0271
  //
  return;
}

/**
  * @brief  Returns the transfer count for an integrated USB DMA channel.
  *
  *         This function returns the USB DMA transfer count in bytes for the channel
  *         number specified in the \e ui32Channel parameter.  The \e ui32Channel value
  *         is a zero-based index of the DMA channel to query.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller or if it must use the DMA controller for DMA transfers.
  * @param  ui32Channel specifies which DMA channel to access.
  * @retval The current count for a USB DMA channel.
  */
uint32_t md_usb_dma_channel_count_get(uint32_t ui32Channel)
{
  //
  // It is not supported by es32f0271
  //
  return 0;
}

/**
  * @brief  Returns the available number of integrated USB DMA channels.
  *
  *         This function returns the total number of DMA channels available when using
  *         the integrated USB DMA controller.  This function returns 0 if the
  *         integrated controller is not present.
  *
  * @note   The number of integrated USB DMA channels or zero if the
  *         integrated USB DMA controller is not present.
  * @param  None.
  * @retval The number of integrated USB DMA channels or zero if the
  *         integrated USB DMA controller is not present.
  */
uint32_t md_usb_dma_channel_number(void)
{
  //
  // It is not supported by es32f0271
  //
  return 0;
}

/**
 * @brief  Enable interrupts for a specified integrated USB DMA channel.
 *
 *         This function enables the USB DMA channel interrupt based on the
 *         \e ui32Channel parameter.  The \e ui32Channel value is a zero-based
 *         index of the USB DMA channel.  Once enabled, the md_usb_dma_channel_int_status()
 *         function returns if a DMA channel has generated an interrupt.
 *
 * @note   The number of integrated USB DMA channels or zero if the
 *         integrated USB DMA controller is not present.
 * @param  ui32Channel specifies which DMA channel interrupt to enable.
 * @retval None.
 */
void md_usb_dma_channel_int_enable(uint32_t ui32Channel)
{
  //
  // It is not supported by es32f0271
  //
}

/**
  * @brief  Return the current status of the integrated USB DMA interrupts.
  *
  *         This function returns the current bit-mapped interrupt status for all USB
  *         DMA channel interrupt sources.  Calling this function automatically clears
  *         all currently pending USB DMA interrupts.
  *
  * @param  None.
  * @retval None.
  */
uint32_t md_usb_dma_channel_int_status(void)
{
  return 0;
}

/**
  * @brief  Enables USB DMA for a specified channel.
  *
  *         This function enables the USB DMA channel passed in the \e ui32Channel
  *         parameter.  The \e ui32Channel value is a zero-based index of the USB DMA
  *         channel.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller.
  * @param  ui32Channel specifies the USB DMA channel to enable.
  * @retval None.
  */
void md_usb_dma_channel_enable(uint32_t ui32Channel)
{
  //
  // DMA1 will be used by es32f0271
  //
  SET_BIT(*(&DMA1->CSR0 + 4 * ui32Channel), DMA_CSR0_CHEN_MSK);
}

/**
 * @brief  Disables USB DMA for a specified channel.
 *
 *         This function Disables the USB DMA channel passed in the \e ui32Channel
 *         parameter.  The \e ui32Channel value is a zero-based index of the USB DMA
 *         channel.
 *
 * @note   This feature is not available on all ES32 devices.  Please
 *         check the data sheet to determine if the USB controller has a DMA
 *         controller.
 * @param  ui32Channel specifies the USB DMA channel to Disable.
 * @retval None.
 */
void md_usb_dma_channel_disable(uint32_t ui32Channel)
{
  //
  // DMA1 will be used by es32f0271
  //
  CLEAR_BIT(*(&DMA1->CSR0 + 4 * ui32Channel), DMA_CSR0_CHEN_MSK);
}

/**
  * @brief  Check if the USB channel is enabled.
  *
  * @note   This feature is not available on all ES32 devices.  Please
  *         check the data sheet to determine if the USB controller has a DMA
  *         controller.
  * @param  ui32Channel specifies the USB DMA channel.
  * @retval Return 1 if the channel is enabled.
  */
uint32_t md_usb_dma_channel_isenabled(uint32_t ui32Channel)
{
  if (*((uint32_t *)(&DMA1->CSR0 + ui32Channel * 4)) & DMA_CSR0_CHEN_MSK)
    return 1;

  return 0;
}

/**
 * @brief  Returns the current status for an integrated USB DMA channel.
 *
 *         This function returns the current status for the USB DMA channel specified
 *         by the \e ui32Channel parameter.  The \e ui32Channel value is a zero-based
 *         index of the USB DMA channel to query.
 *
 * @note   This feature is not available on all ES32 devices.  Please
 *         check the data sheet to determine if the USB controller has a DMA
 *         controller or if it must use the DMA controller for DMA transfers.
 * @param  ui32Channel specifies the USB DMA channel to Disable.
 * @retval Returns zero or \b USB_DMACTL0_ERR if there is a pending error
 *         condition on a DMA channel.
 */
uint32_t md_usb_dma_channel_status(uint32_t ui32Channel)
{
  //
  // It is not supported by es32f0271
  //
  return 0;
}

/**
 * @brief  Clears the integrated USB DMA status for a specified channel.
 *
 *         This function clears the USB DMA channel status for the channel specified
 *         by the \e ui32Channel parameter.  The \e ui32Channel value is a zero-based
 *         index of the USB DMA channel to query.  The \e ui32Status parameter
 *         specifies the status bits to clear and must be the valid values that are
 *         returned from a call to the md_usb_dma_channel_status() function.
 *
 * @note   This feature is not available on all ES32 devices.  Please
 *         check the data sheet to determine if the USB controller has a DMA
 *         controller or if it must use the DMA controller for DMA transfers.
 * @param  ui32Channel specifies the USB DMA channel to Disable.
 * @retval None.
 */
void md_usb_dma_channel_status_clear(uint32_t ui32Channel,
                                     uint32_t ui32Status)
{
  //
  // It is not supported by es32f0271
  //
}

/**
  * @} USB_MD_PF_DMA
  */

/**
  * @} USB_MD_Public_Functions
  */

/**
  * @} USB
  */

#endif

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics END OF MAIN.C****/
