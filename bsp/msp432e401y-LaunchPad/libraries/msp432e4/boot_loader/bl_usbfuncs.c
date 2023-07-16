//*****************************************************************************
//
// bl_usbfuncs.c - The subset of USB library functions required by the USB DFU
//                 boot loader.
//
// Copyright (c) 2008-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/inc/msp.h"
#include "ti/devices/msp432e4/boot_loader/bl_usbfuncs.h"

//*****************************************************************************
//
//! \addtogroup bl_usb_api
//! @{
//
//*****************************************************************************
#if defined(USB_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
// Local functions prototypes.
//
//*****************************************************************************
static void USBDGetStatus(tUSBRequest *pUSBRequest);
static void USBDClearFeature(tUSBRequest *pUSBRequest);
static void USBDSetFeature(tUSBRequest *pUSBRequest);
static void USBDSetAddress(tUSBRequest *pUSBRequest);
static void USBDGetDescriptor(tUSBRequest *pUSBRequest);
static void USBDSetDescriptor(tUSBRequest *pUSBRequest);
static void USBDGetConfiguration(tUSBRequest *pUSBRequest);
static void USBDSetConfiguration(tUSBRequest *pUSBRequest);
static void USBDGetInterface(tUSBRequest *pUSBRequest);
static void USBDSetInterface(tUSBRequest *pUSBRequest);
static void USBDEP0StateTx(void);
static int32_t USBDStringIndexFromRequest(uint16_t ui16Lang,
                                          uint16_t ui16Index);

//*****************************************************************************
//
// This structure holds the full state for the device enumeration.
//
//*****************************************************************************
typedef struct
{
    //
    // The devices current address, this also has a change pending bit in the
    // MSB of this value specified by DEV_ADDR_PENDING.
    //
    volatile uint32_t ui32DevAddress;

    //
    // This holds the current active configuration for this device.
    //
    uint32_t ui32Configuration;

    //
    // This holds the current alternate interface for this device. We only have
    // 1 interface so only need to hold 1 setting.
    //
    uint8_t ui8AltSetting;

    //
    // This is the pointer to the current data being sent out or received
    // on endpoint zero.
    //
    uint8_t *pui8EP0Data;

    //
    // This is the number of bytes that remain to be sent from or received
    // into the g_sUSBDeviceState.pui8EP0Data data buffer.
    //
    volatile uint32_t ui32EP0DataRemain;

    //
    // The amount of data being sent/received due to a custom request.
    //
    uint32_t ui32OUTDataSize;

    //
    // Holds the current device status.
    //
    uint8_t ui8Status;

    //
    // This flag indicates whether or not remote wakeup signalling is in
    // progress.
    //
    bool bRemoteWakeup;

    //
    // During remote wakeup signalling, this counter is used to track the
    // number of milliseconds since the signalling was initiated.
    //
    uint8_t ui8RemoteWakeupCount;
}
tDeviceState;

//*****************************************************************************
//
// The states for endpoint zero during enumeration.
//
//*****************************************************************************
typedef enum
{
    //
    // The USB device is waiting on a request from the host controller on
    // endpoint zero.
    //
    USB_STATE_IDLE,

    //
    // The USB device is sending data back to the host due to an IN request.
    //
    USB_STATE_TX,

    //
    // The USB device is receiving data from the host due to an OUT
    // request from the host.
    //
    USB_STATE_RX,

    //
    // The USB device has completed the IN or OUT request and is now waiting
    // for the host to acknowledge the end of the IN/OUT transaction.  This
    // is the status phase for a USB control transaction.
    //
    USB_STATE_STATUS,

    //
    // This endpoint has signaled a stall condition and is waiting for the
    // stall to be acknowledged by the host controller.
    //
    USB_STATE_STALL
}
tEP0State;

//*****************************************************************************
//
// Define the max packet size for endpoint zero.
//
//*****************************************************************************
#define EP0_MAX_PACKET_SIZE     64

//*****************************************************************************
//
// This is a flag used with g_sUSBDeviceState.ui32DevAddress to indicate that a
// device address change is pending.
//
//*****************************************************************************
#define DEV_ADDR_PENDING        0x80000000

//*****************************************************************************
//
// This label defines the default configuration number to use after a bus
// reset.
//
//*****************************************************************************
#define DEFAULT_CONFIG_ID       1

//*****************************************************************************
//
// This label defines the number of milliseconds that the remote wakeup signal
// must remain asserted before removing it. Section 7.1.7.7 of the USB 2.0 spec
// states that "the remote wakeup device must hold the resume signaling for at
// least 1ms but for no more than 15ms" so 10mS seems a reasonable choice.
//
//*****************************************************************************
#define REMOTE_WAKEUP_PULSE_MS 10

//*****************************************************************************
//
// This label defines the number of milliseconds between the point where we
// assert the remote wakeup signal and calling the client back to tell it that
// bus operation has been resumed.  This value is based on the timings provided
// in section 7.1.7.7 of the USB 2.0 specification which indicates that the host
// (which takes over resume signalling when the device's initial signal is
// detected) must hold the resume signalling for at least 20mS.
//
//*****************************************************************************
#define REMOTE_WAKEUP_READY_MS 20

//*****************************************************************************
//
// The buffer for reading data coming into EP0
//
//*****************************************************************************
static uint8_t g_pui8DataBufferIn[EP0_MAX_PACKET_SIZE];

//*****************************************************************************
//
// This global holds the current state information for the USB device.
//
//*****************************************************************************
static volatile tDeviceState g_sUSBDeviceState;

//*****************************************************************************
//
// This global holds the current state of endpoint zero.
//
//*****************************************************************************
static volatile tEP0State g_eUSBDEP0State = USB_STATE_IDLE;

//*****************************************************************************
//
// Function table to handle standard requests.
//
//*****************************************************************************
static const tStdRequest g_ppfnUSBDStdRequests[] =
{
    USBDGetStatus,
    USBDClearFeature,
    0,
    USBDSetFeature,
    0,
    USBDSetAddress,
    USBDGetDescriptor,
    USBDSetDescriptor,
    USBDGetConfiguration,
    USBDSetConfiguration,
    USBDGetInterface,
    USBDSetInterface,
};

//*****************************************************************************
//
// Amount to shift the RX interrupt sources by in the flags used in the
// interrupt calls.
//
//*****************************************************************************
#define USB_INT_RX_SHIFT        8

//*****************************************************************************
//
// Amount to shift the status interrupt sources by in the flags used in the
// interrupt calls.
//
//*****************************************************************************
#define USB_INT_STATUS_SHIFT    24

//*****************************************************************************
//
// Amount to shift the RX endpoint status sources by in the flags used in the
// calls.
//
//*****************************************************************************
#define USB_RX_EPSTATUS_SHIFT   16

//*****************************************************************************
//
// Retrieves data from endpoint 0's FIFO.
//
// \param pui8Data is a pointer to the data area used to return the data from
// the FIFO.
// \param pui32Size is initially the size of the buffer passed into this call
// via the \e pui8Data parameter.  It will be set to the amount of data
// returned in the buffer.
//
// This function will return the data from the FIFO for endpoint 0.
// The \e pui32Size parameter should indicate the size of the buffer passed in
// the \e pui32Data parameter.  The data in the \e pui32Size parameter will be
// changed to match the amount of data returned in the \e pui8Data parameter.
// If a zero byte packet was received this call will not return a error but
// will instead just return a zero in the \e pui32Size parameter.  The only
// error case occurs when there is no data packet available.
//
// \return This call will return 0, or -1 if no packet was received.
//
//*****************************************************************************
int32_t
USBEndpoint0DataGet(uint8_t *pui8Data, uint32_t *pui32Size)
{
    uint32_t ui32ByteCount;

    //
    // Don't allow reading of data if the RxPktRdy bit is not set.
    //
    if((USB0->CSRL0 & USB_CSRL0_RXRDY) == 0)
    {
        //
        // Can't read the data because none is available.
        //
        *pui32Size = 0;

        //
        // Return a failure since there is no data to read.
        //
        return(-1);
    }

    //
    // Get the byte count in the FIFO.
    //
    ui32ByteCount = USB0->COUNT0;

    //
    // Determine how many bytes we will actually copy.
    //
    ui32ByteCount = (ui32ByteCount < *pui32Size) ? ui32ByteCount : *pui32Size;

    //
    // Return the number of bytes we are going to read.
    //
    *pui32Size = ui32ByteCount;

    //
    // Read the data out of the FIFO.
    //
    for(; ui32ByteCount > 0; ui32ByteCount--)
    {
        //
        // Read a byte at a time from the FIFO.
        //
        *pui8Data++ = USB0->FIFO0_BYTE;
    }

    //
    // Success.
    //
    return(0);
}

//*****************************************************************************
//
// Acknowledge that data was read from endpoint 0's FIFO.
//
// \param bIsLastPacket indicates if this is the last packet.
//
// This function acknowledges that the data was read from the endpoint 0's
// FIFO.  The \e bIsLastPacket parameter is set to a \b true value if this is
// the last in a series of data packets.  This call can be used if processing
// is required between reading the data and acknowledging that the data has
// been read.
//
// \return None.
//
//*****************************************************************************
void
USBDevEndpoint0DataAck(bool bIsLastPacket)
{
    //
    // Clear RxPktRdy, and optionally DataEnd, on endpoint zero.
    //
    USB0->CSRL0 = USB_CSRL0_RXRDYC | (bIsLastPacket ? USB_CSRL0_DATAEND : 0);
}

//*****************************************************************************
//
// Puts data into endpoint 0's FIFO.
//
// \param pui8Data is a pointer to the data area used as the source for the
// data to put into the FIFO.
// \param ui32Size is the amount of data to put into the FIFO.
//
// This function will put the data from the \e pui8Data parameter into the FIFO
// for endpoint 0.  If a packet is already pending for transmission then
// this call will not put any of the data into the FIFO and will return -1.
//
// \return This call will return 0 on success, or -1 to indicate that the FIFO
// is in use and cannot be written.
//
//*****************************************************************************
int32_t
USBEndpoint0DataPut(uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Don't allow transmit of data if the TxPktRdy bit is already set.
    //
    if(USB0->CSRL0 & USB_CSRL0_TXRDY)
    {
        return(-1);
    }

    //
    // Write the data to the FIFO.
    //
    for(; ui32Size > 0; ui32Size--)
    {
        USB0->FIFO0_BYTE = *pui8Data++;
    }

    //
    // Success.
    //
    return(0);
}

//*****************************************************************************
//
// Starts the transfer of data from endpoint 0's FIFO.
//
// \param ui32TransType is set to indicate what type of data is being sent.
//
// This function will start the transfer of data from the FIFO for
// endpoint 0.  This is necessary if the \b USB_EP_AUTO_SET bit was not enabled
// for the endpoint.  Setting the \e ui32TransType parameter will allow the
// appropriate signaling on the USB bus for the type of transaction being
// requested.  The \e ui32TransType parameter should be one of the following:
//
// - USB_TRANS_OUT for OUT transaction on any endpoint in host mode.
// - USB_TRANS_IN for IN transaction on any endpoint in device mode.
// - USB_TRANS_IN_LAST for the last IN transactions on endpoint zero in a
//   sequence of IN transactions.
// - USB_TRANS_SETUP for setup transactions on endpoint zero.
// - USB_TRANS_STATUS for status results on endpoint zero.
//
// \return This call will return 0 on success, or -1 if a transmission is
// already in progress.
//
//*****************************************************************************
int32_t
USBEndpoint0DataSend(uint32_t ui32TransType)
{
    //
    // Don't allow transmit of data if the TxPktRdy bit is already set.
    //
    if(USB0->CSRL0 & USB_CSRL0_TXRDY)
    {
        return(-1);
    }

    //
    // Set TxPktRdy in order to send the data.
    //
    USB0->CSRL0 = ui32TransType & 0xff;

    //
    // Success.
    //
    return(0);
}

#if defined(USB_VBUS_CONFIG) || defined(USB_ID_CONFIG) || \
    defined(USB_DP_CONFIG) || defined(USB_DM_CONFIG) || defined(DOXYGEN)
//*****************************************************************************
//
//! Initialize the pins used by USB functions.
//!
//! This function configures the pins for USB functions depending on defines
//! from the bl_config.h file.
//!
//! \return None.
//
//*****************************************************************************
void
USBConfigurePins(void)
{
    //
    // Enable the clocks to the GPIOs.
    //
    SYSCTL->RCGCGPIO |=
        (0x0 |
#if defined(USB_VBUS_CONFIG)
         USB_VBUS_PERIPH |
#endif
#if defined(USB_ID_CONFIG)
         USB_ID_PERIPH |
#endif
#if defined(USB_DP_CONFIG)
         USB_DP_PERIPH |
#endif
#if defined(USB_DM_CONFIG)
         USB_DM_PERIPH
#endif
        );

    //
    // Wait for the Peripherals to be Ready before accessing the register
    // address space.
    //
    while((SYSCTL->PRGPIO &
          (0x0 |
#if defined(USB_VBUS_CONFIG)
           USB_VBUS_PERIPH |
#endif
#if defined(USB_ID_CONFIG)
           USB_ID_PERIPH |
#endif
#if defined(USB_DP_CONFIG)
           USB_DP_PERIPH |
#endif
#if defined(USB_DM_CONFIG)
           USB_DM_PERIPH
#endif
        )) !=
            (0x0 |
#if defined(USB_VBUS_CONFIG)
             USB_VBUS_PERIPH |
#endif
#if defined(USB_ID_CONFIG)
             USB_ID_PERIPH |
#endif
#if defined(USB_DP_CONFIG)
             USB_DP_PERIPH |
#endif
#if defined(USB_DM_CONFIG)
             USB_DM_PERIPH
#endif
            ));

    //
    // Setup the pins based on bl_config.h
    //
#if defined(USB_VBUS_CONFIG)
    //
    // Set the VBUS pin to be an analog input.
    //
    USB_VBUS_PORT->DIR   &= ~(1 << USB_VBUS_PIN);
    USB_VBUS_PORT->AMSEL |= (1 << USB_VBUS_PIN);
#endif

#if defined(USB_ID_CONFIG)
    //
    // Set the ID pin to be an analog input.
    //
    USB_ID_PORT->DIR   &= ~(1 << USB_ID_PIN);
    USB_ID_PORT->AMSEL |= (1 << USB_ID_PIN);
#endif

#if defined(USB_DP_CONFIG)
    //
    // Set the DP pin to be an analog input.
    //
    USB_DP_PORT->DIR   &= ~(1 << USB_DP_PIN);
    USB_DP_PORT->AMSEL |= (1 << USB_DP_PIN);
#endif

#if defined(USB_DM_CONFIG)
    //
    // Set the DM pin to be an analog input.
    //
    USB_DM_PORT->DIR   &= ~(1 << USB_DM_PIN);
    USB_DM_PORT->AMSEL |= (1 << USB_DM_PIN);
#endif

}
#endif

//*****************************************************************************
//
//! Initialize the boot loader USB functions.
//!
//! This function initializes the boot loader USB functions and places the DFU
//! device onto the USB bus.
//!
//! \return None.
//
//*****************************************************************************
void
USBBLInit(void)
{
    //
    // Configure the USB Pins based on the bl_config.h settings.
    //
#if defined(USB_VBUS_CONFIG) || defined(USB_ID_CONFIG) || \
    defined(USB_DP_CONFIG) || defined(USB_DM_CONFIG)
    USBConfigurePins();
#endif

    //
    // Initialize a couple of fields in the device state structure.
    //
    g_sUSBDeviceState.ui32Configuration = DEFAULT_CONFIG_ID;

    //
    // Enable the USB controller.
    //
    SYSCTL->RCGCUSB = SYSCTL_RCGCUSB_R0;

    //
    // Wait for the peripheral ready
    //
    while((SYSCTL->PRUSB & SYSCTL_PRUSB_R0) != SYSCTL_PRUSB_R0)
    {
    }

    //
    // Turn on USB Phy clock from PLL VCO
    //
    USB0->CC = (USB_CC_CLKEN | (3 << USB_CC_CLKDIV_S));

    //
    // Clear any pending interrupts.
    //
    USB0->TXIS;
    USB0->IS;

    //
    // Enable USB Interrupts.
    //
    USB0->TXIE = USB_TXIS_EP0;
    USB0->IE   = (USB_IS_DISCON | USB_IS_RESET);

    //
    // Default to the state where remote wakeup is disabled.
    //
    g_sUSBDeviceState.ui8Status = 0;
    g_sUSBDeviceState.bRemoteWakeup = false;

    //
    // Determine the self- or bus-powered state based on bl_config.h setting.
    //
#if USB_BUS_POWERED
    g_sUSBDeviceState.ui8Status &= ~USB_STATUS_SELF_PWR;
#else
    g_sUSBDeviceState.ui8Status |= USB_STATUS_SELF_PWR;
#endif

    //
    // Attach the device using the soft connect.
    //
    USB0->POWER |= USB_POWER_SOFTCONN;

    //
    // Enable the USB interrupt.
    //
    NVIC->ISER[1] = (1 << (USB0_IRQn - 32));
}

//*****************************************************************************
//
// This function starts the request for data from the host on endpoint zero.
//
// \param pui8Data is a pointer to the buffer to fill with data from the USB
// host.
// \param ui32Size is the size of the buffer or data to return from the USB
// host.
//
// This function handles retrieving data from the host when a custom command
// has been issued on endpoint zero.  When the requested data is received,
// the function HandleEP0Data() will be called.
//
// \return None.
//
//*****************************************************************************
void
USBBLRequestDataEP0(uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Enter the RX state on end point 0.
    //
    g_eUSBDEP0State = USB_STATE_RX;

    //
    // Save the pointer to the data.
    //
    g_sUSBDeviceState.pui8EP0Data = pui8Data;

    //
    // Location to save the current number of bytes received.
    //
    g_sUSBDeviceState.ui32OUTDataSize = ui32Size;

    //
    // Bytes remaining to be received.
    //
    g_sUSBDeviceState.ui32EP0DataRemain = ui32Size;
}

//*****************************************************************************
//
//! This function requests transfer of data to the host on endpoint zero.
//!
//! \param pui8Data is a pointer to the buffer to send via endpoint zero.
//! \param ui32Size is the amount of data to send in bytes.
//!
//! This function handles sending data to the host when a custom command is
//! issued or non-standard descriptor has been requested on endpoint zero.
//!
//! \return None.
//
//*****************************************************************************
void
USBBLSendDataEP0(uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Return the externally provided device descriptor.
    //
    g_sUSBDeviceState.pui8EP0Data = pui8Data;

    //
    // The size of the device descriptor is in the first byte.
    //
    g_sUSBDeviceState.ui32EP0DataRemain = ui32Size;

    //
    // Save the total size of the data sent.
    //
    g_sUSBDeviceState.ui32OUTDataSize = ui32Size;

    //
    // Now in the transmit data state.
    //
    USBDEP0StateTx();
}

//*****************************************************************************
//
//! This function generates a stall condition on endpoint zero.
//!
//! This function is typically called to signal an error condition to the host
//! when an unsupported request is received by the device.  It should be
//! called from within the callback itself (in interrupt context) and not
//! deferred until later since it affects the operation of the endpoint zero
//! state machine.
//!
//! \return None.
//
//*****************************************************************************
void
USBBLStallEP0(void)
{
    //
    // Perform a stall on endpoint zero.
    //
    USB0->CSRL0 |= (USB_CSRL0_STALL | USB_CSRL0_RXRDYC);

    //
    // Enter the stalled state.
    //
    g_eUSBDEP0State = USB_STATE_STALL;
}

//*****************************************************************************
//
// This internal function reads a request data packet and dispatches it to
// either a standard request handler or the registered device request
// callback depending upon the request type.
//
// \return None.
//
//*****************************************************************************
static void
USBDReadAndDispatchRequest(void)
{
    uint32_t ui32Size;
    tUSBRequest *pRequest;

    //
    // Cast the buffer to a request structure.
    //
    pRequest = (tUSBRequest *)g_pui8DataBufferIn;

    //
    // Set the buffer size.
    //
    ui32Size = EP0_MAX_PACKET_SIZE;

    //
    // Get the data from the USB controller end point 0.
    //
    USBEndpoint0DataGet(g_pui8DataBufferIn, &ui32Size);

    if(!ui32Size)
    {
        return;
    }

    //
    // See if this is a standard request or not.
    //
    if((pRequest->bmRequestType & USB_RTYPE_TYPE_M) != USB_RTYPE_STANDARD)
    {
        //
        // Pass this non-standard request on to the DFU handler
        //
        HandleRequests(pRequest);
    }
    else
    {
        //
        // Assure that the jump table is not out of bounds.
        //
        if((pRequest->bRequest <
            (sizeof(g_ppfnUSBDStdRequests) / sizeof(tStdRequest))) &&
           (g_ppfnUSBDStdRequests[pRequest->bRequest] != 0))
        {
            //
            // Jump table to the appropriate handler.
            //
            g_ppfnUSBDStdRequests[pRequest->bRequest](pRequest);
        }
        else
        {
            //
            // If there is no handler then stall this request.
            //
            USBBLStallEP0();
        }
    }
}

//*****************************************************************************
//
// This is the low level interrupt handler for endpoint zero.
//
// This function handles all interrupts on endpoint zero in order to maintain
// the state needed for the control endpoint on endpoint zero.  In order to
// successfully enumerate and handle all USB standard requests, all requests
// on endpoint zero must pass through this function.  The endpoint has the
// following states: \b USB_STATE_IDLE, \b USB_STATE_TX, \b USB_STATE_RX,
// \b USB_STATE_STALL, and \b USB_STATE_STATUS.  In the \b USB_STATE_IDLE
// state the USB controller has not received the start of a request, and once
// it does receive the data for the request it will either enter the
// \b USB_STATE_TX, \b USB_STATE_RX, or \b USB_STATE_STALL depending on the
// command.  If the controller enters the \b USB_STATE_TX or \b USB_STATE_RX
// then once all data has been sent or received, it must pass through the
// \b USB_STATE_STATUS state to allow the host to acknowledge completion of
// the request.  The \b USB_STATE_STALL is entered from \b USB_STATE_IDLE in
// the event that the USB request was not valid.  Both the \b USB_STATE_STALL
// and \b USB_STATE_STATUS are transitional states that return to the
// \b USB_STATE_IDLE state.
//
// \return None.
//
// USB_STATE_IDLE -*--> USB_STATE_TX -*-> USB_STATE_STATUS -*->USB_STATE_IDLE
//                 |                  |                     |
//                 |--> USB_STATE_RX -                      |
//                 |                                        |
//                 |--> USB_STATE_STALL ---------->---------
//
//  ----------------------------------------------------------------
// | Current State       | State 0           | State 1              |
// | --------------------|-------------------|----------------------
// | USB_STATE_IDLE      | USB_STATE_TX/RX   | USB_STATE_STALL      |
// | USB_STATE_TX        | USB_STATE_STATUS  |                      |
// | USB_STATE_RX        | USB_STATE_STATUS  |                      |
// | USB_STATE_STATUS    | USB_STATE_IDLE    |                      |
// | USB_STATE_STALL     | USB_STATE_IDLE    |                      |
//  ----------------------------------------------------------------
//
//*****************************************************************************
void
USBDeviceEnumHandler(void)
{
    uint32_t ui32EPStatus;

    //
    // Get the TX and RX portion of the endpoint status.
    //
    ui32EPStatus = (USB0->CSRH0 << 8);
    ui32EPStatus |= (USB0->CSRL0);


    //
    // What state are we currently in?
    //
    switch(g_eUSBDEP0State)
    {
        //
        // Handle the status state, this is a transitory state from
        // USB_STATE_TX or USB_STATE_RX back to USB_STATE_IDLE.
        //
        case USB_STATE_STATUS:
        {
            //
            // Just go back to the idle state.
            //
            g_eUSBDEP0State = USB_STATE_IDLE;

            //
            // If there is a pending address change then set the address.
            //
            if(g_sUSBDeviceState.ui32DevAddress & DEV_ADDR_PENDING)
            {
                //
                // Clear the pending address change and set the address.
                //
                g_sUSBDeviceState.ui32DevAddress &= ~DEV_ADDR_PENDING;
                USB0->FADDR = (uint8_t)g_sUSBDeviceState.ui32DevAddress;
            }

            //
            // If a new packet is already pending, we need to read it
            // and handle whatever request it contains.
            //
            if(ui32EPStatus & USB_DEV_EP0_OUT_PKTRDY)
            {
                //
                // Process the newly arrived packet.
                //
                USBDReadAndDispatchRequest();
            }
            break;
        }

        //
        // In the IDLE state the code is waiting to receive data from the host.
        //
        case USB_STATE_IDLE:
        {
            //
            // Is there a packet waiting for us?
            //
            if(ui32EPStatus & USB_DEV_EP0_OUT_PKTRDY)
            {
                //
                // Yes - process it.
                //
                USBDReadAndDispatchRequest();
            }
            break;
        }

        //
        // Data is still being sent to the host so handle this in the
        // EP0StateTx() function.
        //
        case USB_STATE_TX:
        {
            USBDEP0StateTx();
            break;
        }

        //
        // Handle the receive state for commands that are receiving data on
        // endpoint zero.
        //
        case USB_STATE_RX:
        {
            uint32_t ui32DataSize;

            //
            // Set the number of bytes to get out of this next packet.
            //
            if(g_sUSBDeviceState.ui32EP0DataRemain > EP0_MAX_PACKET_SIZE)
            {
                //
                // Don't send more than EP0_MAX_PACKET_SIZE bytes.
                //
                ui32DataSize = EP0_MAX_PACKET_SIZE;
            }
            else
            {
                //
                // There was space so send the remaining bytes.
                //
                ui32DataSize = g_sUSBDeviceState.ui32EP0DataRemain;
            }

            //
            // Get the data from the USB controller end point 0.
            //
            USBEndpoint0DataGet(g_sUSBDeviceState.pui8EP0Data, &ui32DataSize);

            //
            // If there we not more that EP0_MAX_PACKET_SIZE or more bytes
            // remaining then this transfer is complete.  If there were exactly
            // EP0_MAX_PACKET_SIZE remaining then there still needs to be
            // null packet sent before this is complete.
            //
            if(g_sUSBDeviceState.ui32EP0DataRemain < EP0_MAX_PACKET_SIZE)
            {
                //
                // Need to ack the data on end point 0 in this case
                // without setting data end.
                //
                USBDevEndpoint0DataAck(true);

                //
                // Return to the idle state.
                //
                g_eUSBDEP0State =  USB_STATE_IDLE;

                //
                // If there is a receive callback then call it.
                //
                if(g_sUSBDeviceState.ui32OUTDataSize != 0)
                {
                    //
                    // Call the receive handler to handle the data
                    // that was received.
                    //
                    HandleEP0Data(g_sUSBDeviceState.ui32OUTDataSize);

                    //
                    // Indicate that there is no longer any data being waited
                    // on.
                    //
                    g_sUSBDeviceState.ui32OUTDataSize = 0;
                }
            }
            else
            {
                //
                // Need to ack the data on end point 0 in this case
                // without setting data end.
                //
                USBDevEndpoint0DataAck(false);
            }

            //
            // Advance the pointer.
            //
            g_sUSBDeviceState.pui8EP0Data += ui32DataSize;

            //
            // Decrement the number of bytes that are being waited on.
            //
            g_sUSBDeviceState.ui32EP0DataRemain -= ui32DataSize;

            break;
        }
        //
        // The device stalled endpoint zero so check if the stall needs to be
        // cleared once it has been successfully sent.
        //
        case USB_STATE_STALL:
        {
            //
            // If we sent a stall then acknowledge this interrupt.
            //
            if(ui32EPStatus & USB_DEV_EP0_SENT_STALL)
            {
                //
                // Clear the stall condition.
                //
                USB0->CSRL0 &= ~(USB_DEV_EP0_SENT_STALL);

                //
                // Reset the global end point 0 state to IDLE.
                //
                g_eUSBDEP0State = USB_STATE_IDLE;

            }
            break;
        }
        //
        // Halt on an unknown state, but only in DEBUG mode builds.
        //
        default:
        {
#ifdef DEBUG
            while(1);
#endif
            break;
        }
    }
}

//*****************************************************************************
//
// This function handles bus reset notifications.
//
// This function is called from the low level USB interrupt handler whenever
// a bus reset is detected.  It performs tidy-up as required and resets the
// configuration back to defaults in preparation for descriptor queries from
// the host.
//
// \return None.
//
//*****************************************************************************
void
USBDeviceEnumResetHandler(void)
{
    //
    // Disable remote wakeup signalling (as per USB 2.0 spec 9.1.1.6).
    //
    g_sUSBDeviceState.ui8Status &= ~USB_STATUS_REMOTE_WAKE;
    g_sUSBDeviceState.bRemoteWakeup = false;

    //
    // Call the device dependent code to indicate a bus reset has occurred.
    //
    HandleReset();

    //
    // Reset the default configuration identifier and alternate function
    // selections.
    //
    g_sUSBDeviceState.ui32Configuration = DEFAULT_CONFIG_ID;
    g_sUSBDeviceState.ui8AltSetting = 0;
}

//*****************************************************************************
//
// This function handles the GET_STATUS standard USB request.
//
// \param pUSBRequest holds the request type and endpoint number if endpoint
// status is requested.
//
// This function handles responses to a Get Status request from the host
// controller.  A status request can be for the device, an interface or an
// endpoint.  If any other type of request is made this function will cause
// a stall condition to indicate that the command is not supported.  The
// \e pUSBRequest structure holds the type of the request in the
// bmRequestType field.  If the type indicates that this is a request for an
// endpoint's status, then the wIndex field holds the endpoint number.
//
// \return None.
//
//*****************************************************************************
static void
USBDGetStatus(tUSBRequest *pUSBRequest)
{
    uint16_t ui16Data;

    //
    // Determine what type of status was requested.
    //
    switch(pUSBRequest->bmRequestType & USB_RTYPE_RECIPIENT_M)
    {
        //
        // This was a Device Status request.
        //
        case USB_RTYPE_DEVICE:
        {
            //
            // Return the current status for the device.
            //
            ui16Data = g_sUSBDeviceState.ui8Status;

            break;
        }

        //
        // This was a Interface status request.
        //
        case USB_RTYPE_INTERFACE:
        {
            //
            // Interface status always returns 0.
            //
            ui16Data = 0;

            break;
        }

        //
        // This was an unknown request or a request for an endpoint (of which
        // we have none) so set a stall.
        //
        case USB_RTYPE_ENDPOINT:
        default:
        {
            //
            // Anything else causes a stall condition to indicate that the
            // command was not supported.
            //
            USBBLStallEP0();
            return;
        }
    }

    //
    // Send the two byte status response.
    //
    g_sUSBDeviceState.ui32EP0DataRemain = 2;
    g_sUSBDeviceState.pui8EP0Data = (uint8_t *)&ui16Data;

    //
    // Send the response.
    //
    USBDEP0StateTx();
}

//*****************************************************************************
//
// This function handles the CLEAR_FEATURE standard USB request.
//
// \param pUSBRequest holds the options for the Clear Feature USB request.
//
// This function handles device or endpoint clear feature requests.  The
// \e pUSBRequest structure holds the type of the request in the bmRequestType
// field and the feature is held in the wValue field.  For device, the only
// clearable feature is the Remote Wake feature.  This device request
// should only be made if the descriptor indicates that Remote Wake is
// implemented by the device.  For endpoint requests the only clearable
// feature is the ability to clear a halt on a given endpoint.  If any other
// requests are made, then the device will stall the request to indicate to
// the host that the command was not supported.
//
// \return None.
//
//*****************************************************************************
static void
USBDClearFeature(tUSBRequest *pUSBRequest)
{
    //
    // Determine what type of status was requested.
    //
    switch(pUSBRequest->bmRequestType & USB_RTYPE_RECIPIENT_M)
    {
        //
        // This is a clear feature request at the device level.
        //
        case USB_RTYPE_DEVICE:
        {
            //
            // Only remote wake is clearable by this function.
            //
            if(USB_FEATURE_REMOTE_WAKE & pUSBRequest->wValue)
            {
                //
                // Clear the remote wake up state.
                //
                g_sUSBDeviceState.ui8Status &= ~USB_STATUS_REMOTE_WAKE;

                //
                // Need to ack the data on end point 0.
                //
                USBDevEndpoint0DataAck(true);
            }
            else
            {
                USBBLStallEP0();
            }
            break;
        }

        //
        // This is an unknown request or one destined for an invalid endpoint.
        //
        case USB_RTYPE_ENDPOINT:
        default:
        {
            USBBLStallEP0();
            return;
        }
    }
}

//*****************************************************************************
//
// This function handles the SET_FEATURE standard USB request.
//
// \param pUSBRequest holds the feature in the wValue field of the USB
// request.
//
// This function handles device or endpoint set feature requests.  The
// \e pUSBRequest structure holds the type of the request in the bmRequestType
// field and the feature is held in the wValue field.  For device, the only
// settable feature is the Remote Wake feature.  This device request
// should only be made if the descriptor indicates that Remote Wake is
// implemented by the device.  For endpoint requests the only settable feature
// is the ability to issue a halt on a given endpoint.  If any other requests
// are made, then the device will stall the request to indicate to the host
// that the command was not supported.
//
// \return None.
//
//*****************************************************************************
static void
USBDSetFeature(tUSBRequest *pUSBRequest)
{
    //
    // Determine what type of status was requested.
    //
    switch(pUSBRequest->bmRequestType & USB_RTYPE_RECIPIENT_M)
    {
        //
        // This is a set feature request at the device level.
        //
        case USB_RTYPE_DEVICE:
        {
            //
            // Only remote wake is setable by this function.
            //
            if(USB_FEATURE_REMOTE_WAKE & pUSBRequest->wValue)
            {
                //
                // Set the remote wakeup state.
                //
                g_sUSBDeviceState.ui8Status |= USB_STATUS_REMOTE_WAKE;

                //
                // Need to ack the data on end point 0.
                //
                USBDevEndpoint0DataAck(true);
            }
            else
            {
                USBBLStallEP0();
            }
            break;
        }

        //
        // This is an unknown request or one destined for an invalid endpoint.
        //
        case USB_RTYPE_ENDPOINT:
        default:
        {
            USBBLStallEP0();
            return;
        }
    }
}

//*****************************************************************************
//
// This function handles the SET_ADDRESS standard USB request.
//
// \param pUSBRequest holds the new address to use in the wValue field of the
// USB request.
//
// This function is called to handle the change of address request from the
// host controller.  This can only start the sequence as the host must
// acknowledge that the device has changed address.  Thus this function sets
// the address change as pending until the status phase of the request has
// been completed successfully.  This prevents the devices address from
// changing and not properly responding to the status phase.
//
// \return None.
//
//*****************************************************************************
static void
USBDSetAddress(tUSBRequest *pUSBRequest)
{
    //
    // The data needs to be acknowledged on end point 0 without setting data
    // end because there is no data coming.
    //
    USBDevEndpoint0DataAck(true);

    //
    // Save the device address as we cannot change address until the status
    // phase is complete.
    //
    g_sUSBDeviceState.ui32DevAddress = pUSBRequest->wValue | DEV_ADDR_PENDING;

    //
    // Transition directly to the status state since there is no data phase
    // for this request.
    //
    g_eUSBDEP0State = USB_STATE_STATUS;

    //
    // Clear the DFU status just in case we were in an error state last time
    // the device was accessed and we were unplugged and replugged (for a self-
    // powered implementation, of course).
    //
    HandleSetAddress();
}

//*****************************************************************************
//
// This function handles the GET_DESCRIPTOR standard USB request.
//
// \param pUSBRequest holds the data for this request.
//
// This function will return all configured standard USB descriptors to the
// host - device, config and string descriptors.  Any request for a descriptor
// which is not available will result in endpoint 0 being stalled.
//
// \return None.
//
//*****************************************************************************
static void
USBDGetDescriptor(tUSBRequest *pUSBRequest)
{
    uint32_t ui32Stall;

    //
    // Default to no stall.
    //
    ui32Stall = 0;

    //
    // Which descriptor are we being asked for?
    //
    switch(pUSBRequest->wValue >> 8)
    {
        //
        // This request was for a device descriptor.
        //
        case USB_DTYPE_DEVICE:
        {
            //
            // Return the externally provided device descriptor.
            //
            g_sUSBDeviceState.pui8EP0Data =
                (uint8_t *)g_pui8DFUDeviceDescriptor;

            //
            // The size of the device descriptor is in the first byte.
            //
            g_sUSBDeviceState.ui32EP0DataRemain =
                g_pui8DFUDeviceDescriptor[0];
            break;
        }

        //
        // This request was for a configuration descriptor.
        //
        case USB_DTYPE_CONFIGURATION:
        {
            uint8_t ui8Index;

            //
            // Which configuration are we being asked for?
            //
            ui8Index = (uint8_t)(pUSBRequest->wValue & 0xFF);

            //
            // Is this valid?
            //
            if(ui8Index != 0)
            {
                //
                // This is an invalid configuration index.  Stall EP0 to
                // indicate a request error.
                //
                USBBLStallEP0();
                g_sUSBDeviceState.pui8EP0Data = 0;
                g_sUSBDeviceState.ui32EP0DataRemain = 0;
            }
            else
            {
                //
                // Start by sending data from the beginning of the first
                // descriptor.
                //

                g_sUSBDeviceState.pui8EP0Data =
                    (uint8_t *)g_pui8DFUConfigDescriptor;

                //
                // Get the size of the config descriptor (remembering that in
                // this case, we only have a single section)
                //
                g_sUSBDeviceState.ui32EP0DataRemain =
                    *(uint16_t *)&(g_pui8DFUConfigDescriptor[2]);
            }
            break;
        }

        //
        // This request was for a string descriptor.
        //
        case USB_DTYPE_STRING:
        {
            int32_t i32Index;

            //
            // Determine the correct descriptor index based on the requested
            // language ID and index.
            //
            i32Index = USBDStringIndexFromRequest(pUSBRequest->wIndex,
                                                  pUSBRequest->wValue & 0xFF);

            //
            // If the mapping function returned -1 then stall the request to
            // indicate that the request was not valid.
            //
            if(i32Index == -1)
            {
                USBBLStallEP0();
                break;
            }

            //
            // Return the externally specified configuration descriptor.
            //
            g_sUSBDeviceState.pui8EP0Data =
                (uint8_t *)g_ppui8StringDescriptors[i32Index];

            //
            // The total size of a string descriptor is in byte 0.
            //
            g_sUSBDeviceState.ui32EP0DataRemain =
                g_ppui8StringDescriptors[i32Index][0];

            break;
        }

        //
        // Any other request is not handled by the default enumeration handler
        // so see if it needs to be passed on to another handler.
        //
        default:
        {
            //
            // All other requests are not handled.
            //
            USBBLStallEP0();
            ui32Stall = 1;
            break;
        }
    }

    //
    // If there was no stall, ACK the data and see if data needs to be sent.
    //
    if(ui32Stall == 0)
    {
        //
        // Need to ack the data on end point 0 in this case without
        // setting data end.
        //
        USBDevEndpoint0DataAck(false);

        //
        // If this request has data to send, then send it.
        //
        if(g_sUSBDeviceState.pui8EP0Data)
        {
            //
            // If there is more data to send than is requested then just
            // send the requested amount of data.
            //
            if(g_sUSBDeviceState.ui32EP0DataRemain > pUSBRequest->wLength)
            {
                g_sUSBDeviceState.ui32EP0DataRemain = pUSBRequest->wLength;
            }

            //
            // Now in the transmit data state.  Be careful to call the correct
            // function since we need to handle the config descriptor
            // differently from the others.
            //
            USBDEP0StateTx();
        }
    }
}

//*****************************************************************************
//
// This function determines which string descriptor to send to satisfy a
// request for a given index and language.
//
// \param ui16Lang is the requested string language ID.
// \param ui16Index is the requested string descriptor index.
//
// When a string descriptor is requested, the host provides a language ID and
// index to identify the string ("give me string number 5 in French").  This
// function maps these two parameters to an index within our device's string
// descriptor array which is arranged as multiple groups of strings with
// one group for each language advertised via string descriptor 0.
//
// We assume that there are an equal number of strings per language and
// that the first descriptor is the language descriptor and use this fact to
// perform the mapping.
//
// \return The index of the string descriptor to return or -1 if the string
// could not be found.
//
//*****************************************************************************
static int32_t
USBDStringIndexFromRequest(uint16_t ui16Lang, uint16_t ui16Index)
{
    tString0Descriptor *pLang;
    uint32_t ui32NumLangs;
    uint32_t ui32NumStringsPerLang;
    uint32_t ui32Loop;

    //
    // First look for the trivial case where descriptor 0 is being
    // requested.  This is the special case since descriptor 0 contains the
    // language codes supported by the device.
    //
    if(ui16Index == 0)
    {
        return(0);
    }

    //
    // How many languages does this device support?  This is determined by
    // looking at the length of the first descriptor in the string table,
    // subtracting 2 for the header and dividing by two (the size of each
    // language code).
    //
    ui32NumLangs = (g_ppui8StringDescriptors[0][0] - 2) / 2;

    //
    // We assume that the table includes the same number of strings for each
    // supported language.  We know the number of entries in the string table,
    // so how many are there for each language?  This may seem an odd way to
    // do this (why not just have the application tell us in the device info
    // structure?) but it's needed since we didn't want to change the API
    // after the first release which did not support multiple languages.
    //
    ui32NumStringsPerLang = ((NUM_STRING_DESCRIPTORS - 1) / ui32NumLangs);

    //
    // Just to be sure, make sure that the calculation indicates an equal
    // number of strings per language.  We expect the string table to contain
    // (1 + (strings_per_language * languages)) entries.
    //
    if((1 + (ui32NumStringsPerLang * ui32NumLangs)) != NUM_STRING_DESCRIPTORS)
    {
        return(-1);
    }

    //
    // Now determine which language we are looking for.  It is assumed that
    // the order of the groups of strings per language in the table is the
    // same as the order of the language IDs listed in the first descriptor.
    //
    pLang = (tString0Descriptor *)(g_ppui8StringDescriptors[0]);

    //
    // Look through the supported languages looking for the one we were asked
    // for.
    //
    for(ui32Loop = 0; ui32Loop < ui32NumLangs; ui32Loop++)
    {
        //
        // Have we found the requested language?
        //
        if(pLang->wLANGID[ui32Loop] == ui16Lang)
        {
            //
            // Yes - calculate the index of the descriptor to send.
            //
            return((ui32NumStringsPerLang * ui32Loop) + ui16Index);
        }
    }

    //
    // If we drop out of the loop, the requested language was not found so
    // return -1 to indicate the error.
    //
    return(-1);
}

//*****************************************************************************
//
// This function handles the SET_DESCRIPTOR standard USB request.
//
// \param pUSBRequest holds the data for this request.
//
// This function currently is not supported and will respond with a Stall
// to indicate that this command is not supported by the device.
//
// \return None.
//
//*****************************************************************************
static void
USBDSetDescriptor(tUSBRequest *pUSBRequest)
{
    //
    // This function is not handled by default.
    //
    USBBLStallEP0();
}

//*****************************************************************************
//
// This function handles the GET_CONFIGURATION standard USB request.
//
// \param pUSBRequest holds the data for this request.
//
// This function responds to a host request to return the current
// configuration of the USB device.  The function will send the configuration
// response to the host and return.  This value will either be 0 or the last
// value received from a call to SetConfiguration().
//
// \return None.
//
//*****************************************************************************
static void
USBDGetConfiguration(tUSBRequest *pUSBRequest)
{
    uint8_t ui8Value;

    //
    // If we still have an address pending then the device is still not
    // configured.
    //
    if(g_sUSBDeviceState.ui32DevAddress & DEV_ADDR_PENDING)
    {
        ui8Value = 0;
    }
    else
    {
        ui8Value = (uint8_t)g_sUSBDeviceState.ui32Configuration;
    }

    g_sUSBDeviceState.ui32EP0DataRemain = 1;
    g_sUSBDeviceState.pui8EP0Data = &ui8Value;

    //
    // Send the single byte response.
    //
    USBDEP0StateTx();
}

//*****************************************************************************
//
// This function handles the SET_CONFIGURATION standard USB request.
//
// \param pUSBRequest holds the data for this request.
//
// This function responds to a host request to change the current
// configuration of the USB device.  The actual configuration number is taken
// from the structure passed in via \e pUSBRequest.
//
// \return None.
//
//*****************************************************************************
static void
USBDSetConfiguration(tUSBRequest *pUSBRequest)
{
    //
    // Cannot set the configuration to one that does not exist so check the
    // enumeration structure to see how many valid configurations are present.
    //
    if(pUSBRequest->wValue > 1)
    {
        //
        // The passed configuration number is not valid.  Stall the endpoint to
        // signal the error to the host.
        //
        USBBLStallEP0();
    }
    else
    {
        //
        // Need to ack the data on end point 0.
        //
        USBDevEndpoint0DataAck(true);

        //
        // Save the configuration.
        //
        g_sUSBDeviceState.ui32Configuration = pUSBRequest->wValue;

        //
        // If passed a configuration other than 0 (which tells us that we are
        // not currently configured), configure the endpoints (other than EP0)
        // appropriately.
        //
        if(g_sUSBDeviceState.ui32Configuration)
        {
            //
            // Set the power state
            //
#if USB_BUS_POWERED
            g_sUSBDeviceState.ui8Status &= ~USB_STATUS_SELF_PWR;
#else
            g_sUSBDeviceState.ui8Status |= USB_STATUS_SELF_PWR;
#endif
        }

        //
        // Do whatever needs to be done as a result of the config change.
        //
        HandleConfigChange(g_sUSBDeviceState.ui32Configuration);
    }
}

//*****************************************************************************
//
// This function handles the GET_INTERFACE standard USB request.
//
// \param pUSBRequest holds the data for this request.
//
// This function is called when the host controller request the current
// interface that is in use by the device.  This simply returns the value set
// by the last call to SetInterface().
//
// \return None.
//
//*****************************************************************************
static void
USBDGetInterface(tUSBRequest *pUSBRequest)
{
    uint8_t ui8Value;

    //
    // If we still have an address pending then the device is still not
    // configured.
    //
    if(g_sUSBDeviceState.ui32DevAddress & DEV_ADDR_PENDING)
    {
        ui8Value = 0;
    }
    else
    {
        //
        // Is the interface number valid?
        //
        if(pUSBRequest->wIndex == 0)
        {
            //
            // Read the current alternate setting for the required interface.
            //
            ui8Value = g_sUSBDeviceState.ui8AltSetting;
        }
        else
        {
            //
            // An invalid interface number was specified.
            //
            USBBLStallEP0();
            return;
        }
    }

    //
    // Send the single byte response.
    //
    g_sUSBDeviceState.ui32EP0DataRemain = 1;
    g_sUSBDeviceState.pui8EP0Data = &ui8Value;

    //
    // Send the single byte response.
    //
    USBDEP0StateTx();
}

//*****************************************************************************
//
// This function handles the SET_INTERFACE standard USB request.
//
// \param pUSBRequest holds the data for this request.
//
// The DFU device supports a single interface with no alternate settings so
// this handler is hardcoded assuming this configuration.
//
// \return None.
//
//*****************************************************************************
static void
USBDSetInterface(tUSBRequest *pUSBRequest)
{
    if((pUSBRequest->wIndex == 0) && (pUSBRequest->wValue == 0))
    {
        //
        // We were passed a valid interface number so acknowledge the request.
        //
        USBDevEndpoint0DataAck(true);
    }
    else
    {
        //
        // The values passed were not valid so stall endpoint 0.
        //
        USBBLStallEP0();
    }
}

//*****************************************************************************
//
// This internal function handles sending data on endpoint zero.
//
// \return None.
//
//*****************************************************************************
static void
USBDEP0StateTx(void)
{
    uint32_t ui32NumBytes;
    uint8_t *pui8Data;

    //
    // In the TX state on endpoint zero.
    //
    g_eUSBDEP0State = USB_STATE_TX;

    //
    // Set the number of bytes to send this iteration.
    //
    ui32NumBytes = g_sUSBDeviceState.ui32EP0DataRemain;

    //
    // Limit individual transfers to 64 bytes.
    //
    if(ui32NumBytes > EP0_MAX_PACKET_SIZE)
    {
        ui32NumBytes = EP0_MAX_PACKET_SIZE;
    }

    //
    // Save the pointer so that it can be passed to the USBEndpointDataPut()
    // function.
    //
    pui8Data = g_sUSBDeviceState.pui8EP0Data;

    //
    // Advance the data pointer and counter to the next data to be sent.
    //
    g_sUSBDeviceState.ui32EP0DataRemain -= ui32NumBytes;
    g_sUSBDeviceState.pui8EP0Data += ui32NumBytes;

    //
    // Put the data in the correct FIFO.
    //
    USBEndpoint0DataPut(pui8Data, ui32NumBytes);

    //
    // If this is exactly 64 then don't set the last packet yet.
    //
    if(ui32NumBytes == EP0_MAX_PACKET_SIZE)
    {
        //
        // There is more data to send or exactly 64 bytes were sent, this
        // means that there is either more data coming or a null packet needs
        // to be sent to complete the transaction.
        //
        USBEndpoint0DataSend(USB_TRANS_IN);
    }
    else
    {
        //
        // Now go to the status state and wait for the transmit to complete.
        //
        g_eUSBDEP0State = USB_STATE_STATUS;

        //
        // Send the last bit of data.
        //
        USBEndpoint0DataSend(USB_TRANS_IN_LAST);
        g_sUSBDeviceState.ui32OUTDataSize = 0;
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif // USB_ENABLE_UPDATE
