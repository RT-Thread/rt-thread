//*****************************************************************************
//
// bl_usb.c - Functions to transfer data via the USB port.
//
// Copyright (c) 2009-2017 Texas Instruments Incorporated.  All rights reserved.
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
#include "ti/devices/msp432e4/boot_loader/bl_crystal.h"
#include "ti/devices/msp432e4/boot_loader/bl_flash.h"
#include "ti/devices/msp432e4/boot_loader/bl_hooks.h"
#include "ti/devices/msp432e4/boot_loader/bl_usbfuncs.h"
#include "ti/devices/msp432e4/boot_loader/usbdfu.h"

//*****************************************************************************
//
// DFU Notes:
//
// 1. This implementation is manifestation-tolerant and doesn't time out
//    waiting for a reset after a download completes.  As a result, the detach
//    timeout in the DFU functional descriptor is set to the maximum possible
//    value representing a timeout of 65.536 seconds.
//
// 2. This implementation does not support the BUSY state.  By skipping this
//    and remaining in DNLOAD_SYNC when we are waiting for a programming or
//    erase operation to complete, we save the overhead of having to support a
//    timeout mechanism.  Host-side implementations don't seem to rely upon
//    the busy state so this does not appear to be a problem.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup bl_usb_api
//! @{
//
//*****************************************************************************
#if defined(USB_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
// Make sure that the crystal frequency is defined.
//
//*****************************************************************************
#if !defined(CRYSTAL_FREQ)
#error ERROR: CRYSTAL_FREQ must be defined for USB update!
#endif

//*****************************************************************************
//
// Make sure that the crystal frequency is one of the ones that support USB
// operation.
//
//*****************************************************************************
#if CRYSTAL_FREQ != 5000000 &&                                                \
    CRYSTAL_FREQ != 6000000 &&                                                \
    CRYSTAL_FREQ != 8000000 &&                                                \
    CRYSTAL_FREQ != 10000000 &&                                               \
    CRYSTAL_FREQ != 12000000 &&                                               \
    CRYSTAL_FREQ != 16000000 &&                                               \
    CRYSTAL_FREQ != 25000000
#error ERROR: Invalid CRYSTAL_FREQ specified for USB update!
#endif

//*****************************************************************************
//
// The DFU device information structure was developed assuming flash block
// sizes in the 1KB to 32KB range but large external flash devices may have
// 64KB or larger blocks.  If the configuration options indicate a target
// device with large pages, we fake the size at 32KB to keep the client happy.
// The other option would be to redefine this field as an uint32_t but that
// would break existing applications using the interface.
//
// For normal operation, this is unlikely to cause a problem since we will not
// allow a flash operation to start anywhere other than at APP_START_ADDRESS
// (which must fall on a real flash page boundary) or the start of the
// reserved
//
//*****************************************************************************
#if (FLASH_PAGE_SIZE > 0x10000)
#define DFU_REPORTED_PAGE_SIZE  0x8000
#else
#define DFU_REPORTED_PAGE_SIZE  FLASH_PAGE_SIZE
#endif

//*****************************************************************************
//
// This holds the total size of the firmware image being downloaded (which is
// needed if we have a progress reporting hook function provided).
//
//*****************************************************************************
#ifdef BL_PROGRESS_FN_HOOK
uint32_t g_ui32ImageSize;
#endif

//*****************************************************************************
//
// The structure used to define a block of memory.
//
//*****************************************************************************
typedef struct
{
    uint8_t *pui8Start;
    uint32_t ui32Length;
}
tMemoryBlock;

//*****************************************************************************
//
// The block of memory that is to be sent back in response to the next upload
// request.
//
//*****************************************************************************
tMemoryBlock g_sNextUpload;

//*****************************************************************************
//
// The block of memory into which the next programming operation will write.
//
//*****************************************************************************
volatile tMemoryBlock g_sNextDownload;

//*****************************************************************************
//
// The block of flash to be erased.
//
//*****************************************************************************
volatile tMemoryBlock g_sErase;

//*****************************************************************************
//
// Information on the device we are running on.  This will be returned to the
// host after a download request containing command DFU_CMD_INFO.
//
//*****************************************************************************
tDFUDeviceInfo g_sDFUDeviceInfo;

//*****************************************************************************
//
// This variable keeps track of the last software-specific command received
// from the host via a download request.
//
//*****************************************************************************
uint8_t g_ui8LastCommand;

//*****************************************************************************
//
// The current status of the DFU device as reported to the host in response to
// USBD_DFU_REQUEST_GETSTATUS.
//
//*****************************************************************************
tDFUGetStatusResponse g_sDFUStatus =
{
    0, { 5, 0, 0 }, (uint8_t)STATE_IDLE, 0
};

//*****************************************************************************
//
// The structure sent in response to a valid USBD_DFU_REQUEST_MSP432E4.
//
//*****************************************************************************
tDFUQueryMSP432E4Protocol g_sDFUProtocol =
{
    DFU_PROTOCOL_USBLIB_MARKER,
    DFU_PROTOCOL_USBLIB_VERSION_1
};

//*****************************************************************************
//
// The current state of the device.
//
//*****************************************************************************
volatile tDFUState g_eDFUState = STATE_IDLE;

//*****************************************************************************
//
// The current status of the device.
//
//*****************************************************************************
volatile tDFUStatus g_eDFUStatus = STATUS_OK;

//*****************************************************************************
//
// The buffer used to hold download data from the host prior to writing it to
// flash or image data in the process of being uploaded to the host.
//
//*****************************************************************************
uint8_t g_pui8DFUBuffer[DFU_TRANSFER_SIZE];

//*****************************************************************************
//
// The start of the image data within g_pui8DFUBuffer.
//
//*****************************************************************************
uint8_t *g_pui8DFUWrite;

//*****************************************************************************
//
// The number of bytes of valid data in the DFU buffer.
//
//*****************************************************************************
volatile uint16_t g_ui16DFUBufferUsed;

//*****************************************************************************
//
// Flags used to indicate that the main thread is being asked to do something.
//
//*****************************************************************************
volatile uint32_t g_ui32CommandFlags;
#define CMD_FLAG_ERASE          0
#define CMD_FLAG_WRITE          1
#define CMD_FLAG_RESET          2

//*****************************************************************************
//
// This global determines whether or not we add a DFU header to any uploaded
// image data.  If true, the binary image is sent without the header.  If false
// the header is included.  This is a DFU requirement since uploaded images
// must be able to be downloaded again and hence must have the header in place
// so that the destination address is available.
//
//*****************************************************************************
bool g_bUploadBinary = false;

//*****************************************************************************
//
// If the upload format includes the header, we need to be able to suppress
// this when replying to device-specific commands such as CMD_DFU_INFO.  This
// global determines whether we need to suppress the header that would
// otherwise be send in response to the first USBD_DFU_REQUEST_UPLOAD received
// while in STATE_IDLE.
//
//*****************************************************************************
bool g_bSuppressUploadHeader = false;

//*****************************************************************************
//
// A flag we use to indicate when the device has been enumerated.
//
//*****************************************************************************
bool g_bAddressSet = false;

//*****************************************************************************
//
// The languages supported by this device.
//
//*****************************************************************************
const uint8_t g_pui8LangDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

//*****************************************************************************
//
// The jump table used to implement request handling in the DFU state machine.
//
//*****************************************************************************
typedef void (* tHandleRequests)(tUSBRequest *psUSBRequest);

extern void HandleRequestIdle(tUSBRequest *psUSBRequest);
extern void HandleRequestDnloadSync(tUSBRequest *psUSBRequest);
extern void HandleRequestDnloadIdle(tUSBRequest *psUSBRequest);
extern void HandleRequestManifestSync(tUSBRequest *psUSBRequest);
extern void HandleRequestUploadIdle(tUSBRequest *psUSBRequest);
extern void HandleRequestError(tUSBRequest *psUSBRequest);

tHandleRequests g_pfnRequestHandlers[] =
{
    0,                          // STATE_APP_IDLE
    0,                          // STATE_APP_DETACH
    HandleRequestIdle,          // STATE_IDLE
    HandleRequestDnloadSync,    // STATE_DNLOAD_SYNC
    HandleRequestDnloadSync,    // STATE_DNBUSY
    HandleRequestDnloadIdle,    // STATE_DNLOAD_IDLE
    HandleRequestManifestSync,  // STATE_MANIFEST_SYNC
    0,                          // STATE_MANIFEST
    0,                          // STATE_MANIFEST_WAIT_RESET
    HandleRequestUploadIdle,    // STATE_UPLOAD_IDLE
    HandleRequestError          // STATE_ERROR
};

//*****************************************************************************
//
// The manufacturer string.
//
//*****************************************************************************
const uint8_t g_pui8ManufacturerString[] =
{
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0,
    's', 0, 't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0,
    's', 0
};

//*****************************************************************************
//
// The product string.
//
//*****************************************************************************
const uint8_t g_pui8ProductString[] =
{
    (23 + 1) * 2,
    USB_DTYPE_STRING,
    'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, ' ', 0, 'F', 0, 'i', 0,
    'r', 0, 'm', 0, 'w', 0, 'a', 0, 'r', 0, 'e', 0, ' ', 0, 'U', 0, 'p', 0,
    'g', 0, 'r', 0, 'a', 0, 'd', 0, 'e', 0
};

//*****************************************************************************
//
// The serial number string.
//
//*****************************************************************************
const uint8_t g_pui8SerialNumberString[] =
{
    (3 + 1) * 2,
    USB_DTYPE_STRING,
    '0', 0, '.', 0, '1', 0
};

//*****************************************************************************
//
// The descriptor string table.
//
//*****************************************************************************
const uint8_t *const g_ppui8StringDescriptors[] =
{
    g_pui8LangDescriptor,
    g_pui8ManufacturerString,
    g_pui8ProductString,
    g_pui8SerialNumberString
};

//*****************************************************************************
//
// DFU Device Descriptor.
//
//*****************************************************************************
const uint8_t g_pui8DFUDeviceDescriptor[] =
{
    18,                         // Size of this structure.
    USB_DTYPE_DEVICE,           // Type of this structure.
    USBShort(0x110),            // USB version 1.1 (if we say 2.0, hosts assume
                                // high-speed - see USB 2.0 spec 9.2.6.6)
    USB_CLASS_VEND_SPECIFIC,    // USB Device Class
    0,                          // USB Device Sub-class
    0,                          // USB Device protocol
    64,                         // Maximum packet size for default pipe.
    USBShort(USB_VENDOR_ID),    // Vendor ID (VID).
    USBShort(USB_PRODUCT_ID),   // Product ID (PID).
    USBShort(USB_DEVICE_ID),    // Device Release Number BCD.
    1,                          // Manufacturer string identifier.
    2,                          // Product string identifier.
    3,                          // Product serial number.
    1                           // Number of configurations.
};

//*****************************************************************************
//
// DFU device configuration descriptor.
//
//*****************************************************************************
const uint8_t g_pui8DFUConfigDescriptor[] =
{
    //
    // Configuration descriptor header.
    //
    9,                          // Size of the configuration descriptor.
    USB_DTYPE_CONFIGURATION,    // Type of this descriptor.
    USBShort(27),               // The total size of this full structure.
    1,                          // The number of interfaces in this
                                // configuration.
    1,                          // The unique value for this configuration.
    0,                          // The string identifier that describes this
                                // configuration.
#if USB_BUS_POWERED
    USB_CONF_ATTR_BUS_PWR,      // Bus Powered
#else
    USB_CONF_ATTR_SELF_PWR,     // Self Powered
#endif
    (USB_MAX_POWER / 2),        // The maximum power in 2mA increments.

    //
    // Interface descriptor.
    //
    9,                          // Length of this descriptor.
    USB_DTYPE_INTERFACE,        // This is an interface descriptor.
    0,                          // Interface number .
    0,                          // Alternate setting number.
    0,                          // Number of endpoints (only endpoint 0 used)
    USB_CLASS_APP_SPECIFIC,     // Application specific interface class
    USB_DFU_SUBCLASS,           // Device Firmware Upgrade subclass
    USB_DFU_PROTOCOL,           // DFU protocol
    0,                          // No interface description string present.

    //
    // Device Firmware Upgrade functional descriptor.
    //
    9,                          // Length of this descriptor.
    0x21,                       // DFU Functional descriptor type
    (DFU_ATTR_CAN_DOWNLOAD |    // DFU attributes.
     DFU_ATTR_CAN_UPLOAD |
     DFU_ATTR_MANIFEST_TOLERANT),
    USBShort(0xFFFF),           // Detach timeout (set to maximum).
    USBShort(DFU_TRANSFER_SIZE),// Transfer size 1KB.
    USBShort(0x0110)            // DFU Version 1.1
};

//*****************************************************************************
//
// The USB device interrupt handler.
//
// This function is called to process USB interrupts when in device mode.
// This handler will branch the interrupt off to the appropriate application or
// stack handlers depending on the current status of the USB controller.
//
// \return None.
//
//*****************************************************************************
void
USB0DeviceIntHandler(void)
{
    uint32_t ui32TxStatus, ui32GenStatus;

    //
    // Get the current full USB interrupt status.
    //
    ui32TxStatus = USB0->TXIS;
    ui32GenStatus = USB0->IS;

    //
    // Received a reset from the host.
    //
    if(ui32GenStatus & USB_IS_RESET)
    {
        USBDeviceEnumResetHandler();
    }

    //
    // USB device was disconnected.
    //
    if(ui32GenStatus & USB_IS_DISCON)
    {
        HandleDisconnect();
    }

    //
    // Handle end point 0 interrupts.
    //
    if(ui32TxStatus & USB_TXIE_EP0)
    {
        USBDeviceEnumHandler();
    }
}

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(uint32_t ui32Count);

//*****************************************************************************
//
// Send the current state or status structure back to the host.  This function
// also acknowledges the request which causes us to send back this data.
//
//*****************************************************************************
void
SendDFUStatus(void)
{
    //
    // Acknowledge the original request.
    //
    USBDevEndpoint0DataAck(false);

    //
    // Copy the current state into the status structure we will return.
    //
    g_sDFUStatus.bState = (uint8_t)g_eDFUState;
    g_sDFUStatus.bStatus = (uint8_t)g_eDFUStatus;

    //
    // Send the status structure back to the host.
    //
    USBBLSendDataEP0((uint8_t *)&g_sDFUStatus, sizeof(tDFUGetStatusResponse));
}

//*****************************************************************************
//
// Send the next block of upload data back to the host assuming data remains
// to be sent.
//
// \param ui16Length is the requested amount of data.
// \param bAppendHeader is \b true to append a tDFUDownloadProgHeader at the
// start of the uploaded data or \b false if no header is required.
//
// Returns \b true if a full packet containing DFU_TRANSFER_SIZE bytes
// was sent and data remains to be sent following this transaction, or \b
// false if no more data remains to be sent following this transaction.
//
//*****************************************************************************
bool
SendUploadData(uint16_t ui16Length, bool bAppendHeader)
{
    uint16_t ui16ToSend;
    uint32_t ui32Available;

    //
    // Acknowledge the original request.
    //
    USBDevEndpoint0DataAck(false);

    //
    // How much data is available to be sent?
    //
    ui32Available = (g_sNextUpload.ui32Length +
                     (bAppendHeader ? sizeof(tDFUDownloadProgHeader) : 0));

    //
    // How much data can we send? This is the smallest of the maximum transfer
    // size, the requested length or the available data.
    //
    ui16ToSend =
        (ui16Length > DFU_TRANSFER_SIZE) ? DFU_TRANSFER_SIZE : ui16Length;
    ui16ToSend =
        ((uint32_t)ui16ToSend > ui32Available) ? ui32Available : ui16ToSend;

    //
    // If we have been asked to send a header, we need to copy some of the data
    // into a buffer and send from there.  If we don't do this, we run the risk
    // of sending a long packet prematurely and ending the upload before it is
    // complete.
    //
    if(bAppendHeader)
    {
        tDFUDownloadProgHeader *psHdr;
        uint8_t *pui8From;
        uint8_t *pui8To;
        uint32_t ui32Loop;

        //
        // We are appending a header so write the header information into a
        // buffer then copy the first chunk of data from its original position
        // into the same buffer.
        //
        psHdr = (tDFUDownloadProgHeader *)g_pui8DFUBuffer;

        //
        // Build the header.
        //
        psHdr->ui8Command = DFU_CMD_PROG;
        psHdr->ui8Reserved = 0;
        psHdr->ui16StartAddr = ((uint32_t)(g_sNextUpload.pui8Start) / 1024);
        psHdr->ui32Length = g_sNextUpload.ui32Length;

        //
        // Copy the remainder of the first transfer's data from its original
        // position.
        //
        pui8From = g_sNextUpload.pui8Start;
        pui8To = (uint8_t *)(psHdr + 1);
        for(ui32Loop = (ui16ToSend - sizeof(tDFUDownloadProgHeader)); ui32Loop;
            ui32Loop--)
        {
            *pui8To++ = *pui8From++;
        }

        //
        // Send the data.
        //
        USBBLSendDataEP0((uint8_t *)psHdr, ui16ToSend);

        //
        // Update our upload pointer and length.
        //
        g_sNextUpload.pui8Start += ui16ToSend - sizeof(tDFUDownloadProgHeader);
        g_sNextUpload.ui32Length -=
            ui16ToSend - sizeof(tDFUDownloadProgHeader);
    }
    else
    {
        //
        // We are not sending a header so send the requested upload data back
        // to the host directly from its original position.
        //
        USBBLSendDataEP0(g_sNextUpload.pui8Start, ui16ToSend);

        //
        // Update our upload pointer and length.
        //
        g_sNextUpload.pui8Start += ui16ToSend;
        g_sNextUpload.ui32Length -= ui16ToSend;
    }

    //
    // We return true if we sent a full packet (containing the maximum transfer
    // size bytes) or false to indicate that a long packet was sent or no more
    // data remains.
    //
    return(((ui16ToSend == DFU_TRANSFER_SIZE) && g_sNextUpload.ui32Length) ?
           true : false);
}

//*****************************************************************************
//
// Send the current state back to the host.
//
//*****************************************************************************
void
SendDFUState(void)
{
    //
    // Acknowledge the original request.
    //
    USBDevEndpoint0DataAck(false);

    //
    // Update the status structure with the current state.
    //
    g_sDFUStatus.bState = (uint8_t)g_eDFUState;

    //
    // Send the state from the status structure back to the host.
    //
    USBBLSendDataEP0((uint8_t *)&g_sDFUStatus.bState, 1);
}

//*****************************************************************************
//
//! Handle USB requests sent to the DFU device.
//!
//! \param psUSBRequest is a pointer to the USB request that the device has
//! been sent.
//!
//! This function is called to handle all non-standard requests received
//! by the device.  This will include all the DFU endpoint 0 commands along
//! with the device-specific request we use to query whether the device
//! supports our flavor of the DFU binary format.  Incoming DFU requests are
//! processed by request handlers specific to the particular state of the DFU
//! connection.  This state machine implementation is chosen to keep the
//! software as close as possible to the USB DFU class documentation.
//!
//! \return None.
//
//*****************************************************************************
void
HandleRequests(tUSBRequest *psUSBRequest)
{
    //
    // This request is used by the host to determine whether the connected
    // device supports the Device specific protocol extensions to DFU (our
    // DFU_CMD_xxxx command headers passed alongside DNLOAD requests).  We
    // check the parameters and, if they are as expected, we respond with
    // a 4 byte structure providing a marker and the protocol version
    // number.
    //
    if(psUSBRequest->bRequest == USBD_DFU_REQUEST_MSP432E4)
    {
        //
        // Check that the request parameters are all as expected.  We are
        // using the wValue value merely as a way of making it less likely
        // that we respond to another vendor's device-specific request.
        //
        if((psUSBRequest->wLength == sizeof(tDFUQueryMSP432E4Protocol)) &&
           (psUSBRequest->wValue == REQUEST_MSP432E4_VALUE))
        {
            //
            // Acknowledge the original request.
            //
            USBDevEndpoint0DataAck(false);

            //
            // Send the status structure back to the host.
            //
            USBBLSendDataEP0((uint8_t *)&g_sDFUProtocol,
                             sizeof(tDFUQueryMSP432E4Protocol));
        }
        else
        {
            //
            // The request parameters were not as expected so we assume
            // that this is not our request and stall the endpoint to
            // indicate an error.
            //
            USBBLStallEP0();
        }

        return;
    }

    //
    // Pass the request to the relevant handler depending upon our current
    // state.  If no handler is configured, we stall the endpoint since this
    // implies that requests can't be handled in this state.
    //
    if(g_pfnRequestHandlers[g_eDFUState])
    {
        //
        // Dispatch the request to the relevant handler depending upon the
        // current state.
        //
        (g_pfnRequestHandlers[g_eDFUState])(psUSBRequest);
    }
    else
    {
        USBBLStallEP0();
    }
}

//*****************************************************************************
//
// Handle all incoming DFU requests while in state STATE_IDLE.
//
//*****************************************************************************
void
HandleRequestIdle(tUSBRequest *psUSBRequest)
{
    switch(psUSBRequest->bRequest)
    {
        //
        // This is a download request.  We need to request the transaction
        // payload unless this is a zero length request in which case we mark
        // the error by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_DNLOAD:
        {
            if(psUSBRequest->wLength)
            {
                USBBLRequestDataEP0(g_pui8DFUBuffer, psUSBRequest->wLength);
            }
            else
            {
                USBBLStallEP0();
                return;
            }
            break;
        }

        //
        // This is an upload request.  We send back a block of data
        // corresponding to the current upload pointer as held in
        // g_sNextUpload.
        //
        case USBD_DFU_REQUEST_UPLOAD:
        {
            //
            // If we have any upload data to send, send it.  Make sure we append
            // a header if required.
            //
            if(SendUploadData(psUSBRequest->wLength,
                              g_bSuppressUploadHeader ? false :
                              !g_bUploadBinary))
            {
                //
                // We sent a full (max packet size) frame to the host so
                // transition to UPLOAD_IDLE state since we expect another
                // upload request to continue the process.
                //
                g_eDFUState = STATE_UPLOAD_IDLE;
            }

            //
            // Clear the flag we use to suppress sending the DFU header.
            //
            g_bSuppressUploadHeader = false;

            return;
        }

        //
        // Return the current device status structure.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            return;
        }

        //
        // Return the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            return;
        }

        //
        // Ignore the ABORT request.  This returns us to IDLE state but we're
        // there already.
        //
        case USBD_DFU_REQUEST_ABORT:
        {
            break;
        }

        //
        // All other requests are illegal in this state so signal the error
        // by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_CLRSTATUS:
        case USBD_DFU_REQUEST_DETACH:
        default:
        {
            USBBLStallEP0();
            return;
        }
    }

    //
    // If we drop out of the switch, we need to ACK the received request.
    //
    USBDevEndpoint0DataAck(false);
}

//*****************************************************************************
//
// Handle all incoming DFU requests while in state STATE_DNLOAD_SYNC or
// STATE_DNBUSY.
//
//*****************************************************************************
void
HandleRequestDnloadSync(tUSBRequest *psUSBRequest)
{
    //
    // In this state, we have received a block of the download and are waiting
    // for a USBD_DFU_REQUEST_GETSTATUS which will trigger a return
    // to STATE_DNLOAD_IDLE assuming we have finished programming the block.
    // If the last command we received was not DFU_CMD_PROG, we transition
    // directly from this state back to STATE_IDLE once the last operation has
    // completed since we need to be able to accept a new command.
    //
    switch(psUSBRequest->bRequest)
    {
        //
        // The host is requesting the current device status.  Return this and
        // revert to STATE_IDLE.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            //
            // Are we finished processing whatever the last flash-operation
            // was?  Note that we don't support DNLOAD_BUSY state in this
            // implementation, we merely continue to report DNLOAD_SYNC state
            // until we are finished with the command.
            //
            if(!g_ui32CommandFlags)
            {
                //
                // If we are in the middle of a programming operation,
                // transition back to DNLOAD_IDLE state to wait for the
                // next block.  If not, go back to idle since we expect a
                // new command.
                //
                g_eDFUState = ((g_ui8LastCommand == DFU_CMD_PROG) ?
                               STATE_DNLOAD_IDLE : STATE_IDLE);
            }

            //
            // Send the latest status back to the host.
            //
            SendDFUStatus();

            //
            // Return here since we've already ACKed the request.
            //
            return;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            //
            // Are we currently in DNLOAD_SYNC state?
            //
            if(g_eDFUState == STATE_DNLOAD_SYNC)
            {
                //
                // Yes - send back the state.
                //
                SendDFUState();
            }
            else
            {
                //
                // In STATE_BUSY, we can't respond to any requests so stall
                // the endpoint.
                //
                USBBLStallEP0();
            }

            //
            // Return here since the incoming request has already been either
            // ACKed or stalled by the processing above.
            //
            return;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_ERROR.
        //
        default:
        {
            USBBLStallEP0();
            return;
        }
    }
}

//*****************************************************************************
//
// Handle all incoming DFU requests while in state STATE_DNLOAD_IDLE.
//
//*****************************************************************************
void
HandleRequestDnloadIdle(tUSBRequest *psUSBRequest)
{
    switch(psUSBRequest->bRequest)
    {
        //
        // This is a download request.  We need to request the transaction
        // payload unless this is a zero length request in which case we mark
        // the error by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_DNLOAD:
        {
            //
            // Are we being passed data to program?
            //
            if(psUSBRequest->wLength)
            {
                //
                // Yes - request the data.
                //
                USBBLRequestDataEP0(g_pui8DFUBuffer, psUSBRequest->wLength);
            }
            else
            {
                //
                // No - this is the signal that a download operation is
                // complete.  Do we agree?
                //
                if(g_sNextDownload.ui32Length)
                {
                    //
                    // We think there should still be some data to be received
                    // so mark this as an error.
                    //
                    g_eDFUState = STATE_ERROR;
                    g_eDFUStatus = STATUS_ERR_NOTDONE;
                }
                else
                {
                    //
                    // We agree that the download has completed.  Enter state
                    // STATE_MANIFEST_SYNC.
                    //
                    g_eDFUState = STATE_MANIFEST_SYNC;
                }
             }
            break;
        }

        //
        // Return the current device status structure.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            return;
        }

        //
        // Return the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            return;
        }

        //
        // An ABORT request causes us to abort the current transfer and
        // return the the idle state regardless of the state of the previous
        // programming operation.
        //
        case USBD_DFU_REQUEST_ABORT:
        {
            //
            // Default to downloading the main code image.
            //
            g_sNextDownload.pui8Start =
                (uint8_t *)g_sDFUDeviceInfo.ui32AppStartAddr;
            g_sNextDownload.ui32Length = (g_sDFUDeviceInfo.ui32FlashTop -
                                          g_sDFUDeviceInfo.ui32AppStartAddr);
            g_eDFUState = STATE_IDLE;
            break;
        }

        //
        // All other requests are illegal in this state so signal the error
        // by stalling the endpoint.
        //
        case USBD_DFU_REQUEST_CLRSTATUS:
        case USBD_DFU_REQUEST_DETACH:
        case USBD_DFU_REQUEST_UPLOAD:
        default:
        {
            USBBLStallEP0();
            return;
        }
    }

    //
    // If we drop out of the switch, we need to ACK the received request.
    //
    USBDevEndpoint0DataAck(false);
}

//*****************************************************************************
//
// Handle all incoming DFU requests while in state STATE_MANIFEST_SYNC.
//
//*****************************************************************************
void
HandleRequestManifestSync(tUSBRequest *psUSBRequest)
{
    //
    // In this state, we have received the last block of a download and are
    // waiting for a USBD_DFU_REQUEST_GETSTATUS which will trigger a return
    // to STATE_IDLE.
    //
    switch(psUSBRequest->bRequest)
    {
        //
        // The host is requesting the current device status.  Return this and
        // revert to STATE_IDLE.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            g_eDFUState = STATE_IDLE;
            SendDFUStatus();
            break;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            break;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_MANIFEST_SYNC.
        //
        default:
        {
            USBBLStallEP0();
            break;
        }
    }
}

//*****************************************************************************
//
// Handle all incoming DFU requests while in state STATE_UPLOAD_IDLE.
//
//*****************************************************************************
void
HandleRequestUploadIdle(tUSBRequest *psUSBRequest)
{
    //
    // In this state, we have already received the first upload request.  What
    // are we being asked to do now?
    //
    switch(psUSBRequest->bRequest)
    {
        //
        // The host is requesting more upload data.
        //
        case USBD_DFU_REQUEST_UPLOAD:
        {
            //
            // See if there is any more data to transfer and, if there is,
            // send it back to the host.
            //
            if(!SendUploadData(psUSBRequest->wLength, false))
            {
                //
                // We sent less than a full packet of data so the transfer is
                // complete.  Revert to idle state and ensure that we reset
                // our upload pointer and size to the default flash region.
                //
                g_eDFUState = STATE_IDLE;
                g_sNextUpload.pui8Start =
                    (uint8_t *)g_sDFUDeviceInfo.ui32AppStartAddr;
                g_sNextUpload.ui32Length = (g_sDFUDeviceInfo.ui32FlashTop -
                                            g_sDFUDeviceInfo.ui32AppStartAddr);
            }
            break;
        }

        //
        // The host is requesting the current device status.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            break;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            break;
        }

        //
        // The host is requesting that we abort the current upload.
        //
        case USBD_DFU_REQUEST_ABORT:
        {
            //
            // Default to sending the main application image for the next
            // upload.
            //
            g_sNextUpload.pui8Start =
                (uint8_t *)g_sDFUDeviceInfo.ui32AppStartAddr;
            g_sNextUpload.ui32Length = (g_sDFUDeviceInfo.ui32FlashTop -
                                        g_sDFUDeviceInfo.ui32AppStartAddr);
            g_eDFUState = STATE_IDLE;
            break;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_ERROR.
        //
        default:
        {
            USBBLStallEP0();
            break;
        }
    }
}

//*****************************************************************************
//
// Handle all incoming DFU requests while in state STATE_ERROR.
//
//*****************************************************************************
void
HandleRequestError(tUSBRequest *psUSBRequest)
{
    //
    // In this state, we respond to state and status requests and also to
    // USBD_DFU_REQUEST_CLRSTATUS which clears the previous error condition.
    //
    switch(psUSBRequest->bRequest)
    {
        //
        // The host is requesting the current device status.
        //
        case USBD_DFU_REQUEST_GETSTATUS:
        {
            SendDFUStatus();
            break;
        }

        //
        // The host is requesting the current device state.
        //
        case USBD_DFU_REQUEST_GETSTATE:
        {
            SendDFUState();
            break;
        }

        //
        // The host is asking us to clear our previous error condition and
        // revert to idle state in preparation to receive new commands.
        //
        case USBD_DFU_REQUEST_CLRSTATUS:
        {
            g_eDFUState = STATE_IDLE;
            g_eDFUStatus = STATUS_OK;
            USBDevEndpoint0DataAck(false);
            break;
        }

        //
        // Any other request is ignored and causes us to stall the control
        // endpoint and remain in STATE_ERROR.
        //
        default:
        {
            USBBLStallEP0();
            break;
        }
    }
}

//*****************************************************************************
//
// Handle cases where the host sets a new USB configuration.
//
//*****************************************************************************
void
HandleConfigChange(uint32_t ui32Info)
{
    //
    // Revert to idle state.
    //
    g_eDFUState = STATE_IDLE;
    g_eDFUStatus = STATUS_OK;
}

//*****************************************************************************
//
// Setting the device address indicates that we are now connected to the host
// and can expect some DFU communication so we use this opportunity to clean
// out our state just in case we were not idle last time the host disconnected.
//
//*****************************************************************************
void
HandleSetAddress(void)
{
    g_eDFUState = STATE_IDLE;
    g_eDFUStatus = STATUS_OK;
    g_bAddressSet = true;

    //
    // Default the download address to the app start address and valid length
    // to the whole of the programmable flash area.
    //
    g_sNextDownload.pui8Start =
        (uint8_t *)g_sDFUDeviceInfo.ui32AppStartAddr;
    g_sNextDownload.ui32Length = (g_sDFUDeviceInfo.ui32FlashTop -
                                  g_sDFUDeviceInfo.ui32AppStartAddr);

    //
    // Default the upload address to the app start address and valid length
    // to the whole of the programmable flash area.
    //
    g_sNextUpload.pui8Start =
        (uint8_t *)g_sDFUDeviceInfo.ui32AppStartAddr;
    g_sNextUpload.ui32Length = (g_sDFUDeviceInfo.ui32FlashTop -
                                g_sDFUDeviceInfo.ui32AppStartAddr);
}

//*****************************************************************************
//
// Check that a range of addresses passed is within the region of flash that
// the boot loader is allowed to access.
//
// Returns true if the address range is accessible or false otherwise.
//
//*****************************************************************************
bool
FlashRangeCheck(uint32_t ui32Start, uint32_t ui32Length)
{
#ifdef ENABLE_BL_UPDATE
    if((ui32Length <=
        (g_sDFUDeviceInfo.ui32FlashTop - g_sDFUDeviceInfo.ui32AppStartAddr)) &&
       ((ui32Start + ui32Length) <= g_sDFUDeviceInfo.ui32FlashTop))
#else
    if((ui32Start >= g_sDFUDeviceInfo.ui32AppStartAddr) &&
       (ui32Length <=
        (g_sDFUDeviceInfo.ui32FlashTop - g_sDFUDeviceInfo.ui32AppStartAddr)) &&
       ((ui32Start + ui32Length) <= g_sDFUDeviceInfo.ui32FlashTop))
#endif
    {
        //
        // The block passed lies wholly within the flash address range of
        // this device.
        //
        return(true);
    }
    else
    {
        //
        // We were passed an address that is out of range so set the
        // appropriate status code.
        //
        g_eDFUStatus = STATUS_ERR_ADDRESS;
        return(false);
    }
}

//*****************************************************************************
//
//! Process device-specific commands passed via DFU download requests.
//!
//! \param psCmd is a pointer to the first byte of the \b DFU_DNLOAD payload
//! that is expected to hold a command.
//! \param ui32Size is the number of bytes of data pointed to by \e psCmd.
//! This function is called when a DFU download command is received while in
//! \b STATE_IDLE.  New downloads are assumed to contain a prefix structure
//! containing one of several device-specific commands and this function
//! is responsible for parsing the download data and processing whichever
//! command is contained within it.
//!
//! \return Returns \b true on success or \b false on failure.
//
//*****************************************************************************
bool
ProcessDFUDnloadCommand(tDFUDownloadHeader *psCmd, uint32_t ui32Size)
{
    //
    // Make sure we got enough data to contain a valid command header.
    //
    if(ui32Size < sizeof(tDFUDownloadHeader))
    {
        return(false);
    }

    //
    // Remember the command that we have been passed since we will need thi
    // to determine which state to transition to on exit from STATE_DNLOAD_SYNC.
    //
    g_ui8LastCommand = psCmd->ui8Command;

    //
    // Which command have we been passed?
    //
    switch(psCmd->ui8Command)
    {
        //
        // We are being asked to start a programming operation.
        //
        case DFU_CMD_PROG:
        {
            tDFUDownloadProgHeader *psHdr;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadProgHeader *)psCmd;

            //
            // Is the passed address range valid?
            //
            if(BL_FLASH_AD_CHECK_FN_HOOK(psHdr->ui16StartAddr * 1024,
                                         psHdr->ui32Length))
            {
                //
                // Yes - remember the range passed so that we will write the
                // passed data to the correct place.
                //
                g_sNextDownload.pui8Start =
                    (uint8_t *)(psHdr->ui16StartAddr * 1024);
                g_sNextDownload.ui32Length = psHdr->ui32Length;

                //
                // If we have been provided with a progress reporting hook
                // function, remember the total length of the image so that
                // we can report this later.
                //
#ifdef BL_PROGRESS_FN_HOOK
                g_ui32ImageSize = psHdr->ui32Length;
#endif

                //
                // Also set the upload address and size to match this download
                // so that, by default, the host will get back what it just
                // wrote if it performs an upload without an intermediate
                // DFU_CMD_READ to set the address and size.
                //
                g_sNextUpload.pui8Start =
                    (uint8_t *)(psHdr->ui16StartAddr * 1024);
                g_sNextUpload.ui32Length = psHdr->ui32Length;

                //
                // Also remember that we have data in this packet to write.
                //
                g_pui8DFUWrite = (uint8_t *)(psHdr + 1);
                g_ui16DFUBufferUsed = ui32Size - sizeof(tDFUDownloadHeader);

                //
                // If a start signal hook function has been provided, call it
                // here since we are about to start a new download.
                //
#ifdef BL_START_FN_HOOK
                BL_START_FN_HOOK();
#endif

                //
                // If FLASH_CODE_PROTECTION is defined in bl_config.h we
                // erase the whole application area at this point before we
                // start to flash the new image.
                //
#ifdef FLASH_CODE_PROTECTION
                g_sErase.pui8Start =
                    (uint8_t *)g_sDFUDeviceInfo.ui32AppStartAddr;

                g_sErase.ui32Length = (g_sDFUDeviceInfo.ui32FlashTop -
                                       g_sDFUDeviceInfo.ui32AppStartAddr);
                HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_ERASE) = 1;
#endif

                //
                // Tell the main thread to write the data we just received it.
                //
                HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_WRITE) = 1;
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }

        //
        // We are being passed the position and size of a block of flash to
        // return in a following upload operation.
        //
        case DFU_CMD_READ:
        {
            tDFUDownloadReadCheckHeader *psHdr;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadReadCheckHeader *)psCmd;

            //
            // Is the passed address range valid?
            //
            if(FlashRangeCheck(psHdr->ui16StartAddr * 1024, psHdr->ui32Length))
            {
                //
                // Yes - remember the range passed so that we will return
                // this block of flash on the next upload request.
                //
                g_sNextUpload.pui8Start =
                    (uint8_t *)(psHdr->ui16StartAddr * 1024);
                g_sNextUpload.ui32Length = psHdr->ui32Length;
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }

        //
        // We are being passed the position and size of a block of flash which
        // we will check to ensure that it is erased.
        //
        case DFU_CMD_CHECK:
        {
            tDFUDownloadReadCheckHeader *psHdr;
            uint32_t *pui32Check;
            uint32_t ui32Loop;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadReadCheckHeader *)psCmd;

            //
            // Make sure the range we have been passed is within the area of
            // flash that we are allowed to look at.
            //
            if(FlashRangeCheck(psHdr->ui16StartAddr * 1024, psHdr->ui32Length))
            {
                //
                // The range is valid so perform the check here.
                //
                pui32Check = (uint32_t *)(psHdr->ui16StartAddr * 1024);

                //
                // Check each word in the range to ensure that it is erased.  If
                // not, set the error status and return.
                //
                for(ui32Loop = 0; ui32Loop < (psHdr->ui32Length / 4);
                    ui32Loop++)
                {
                    if(*pui32Check != 0xFFFFFFFF)
                    {
                        g_eDFUStatus = STATUS_ERR_CHECK_ERASED;
                        return(false);
                    }
                    pui32Check++;
                }

                //
                // If we get here, the check passed so set the status to
                // indicate this.
                //
                g_eDFUStatus = STATUS_OK;
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }

        //
        // We are being asked to erase a block of flash.
        //
        case DFU_CMD_ERASE:
        {
            tDFUDownloadEraseHeader *psHdr;

            //
            // Extract the address and size from the command header.
            //
            psHdr = (tDFUDownloadEraseHeader *)psCmd;

            //
            // Make sure the range we have been passed is within the area of
            // flash that we are allowed to look at.
            //
            if(FlashRangeCheck((uint32_t)psHdr->ui16StartAddr * 1024,
                               ((uint32_t)psHdr->ui16NumBlocks *
                                DFU_REPORTED_PAGE_SIZE )))
            {
                //
                // The range is valid so tell the main loop to erase the
                // block.
                //
                g_sErase.pui8Start = (uint8_t *)
                    ((uint32_t)psHdr->ui16StartAddr * 1024);
                g_sErase.ui32Length = ((uint32_t)psHdr->ui16NumBlocks *
                                       DFU_REPORTED_PAGE_SIZE);
                HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_ERASE) = 1;
            }
            else
            {
                //
                // The flash range was invalid so switch to error state.
                //
                return(false);
            }
            break;
        }

        //
        // We are being asked to send back device information on the next
        // upload request.
        //
        case DFU_CMD_INFO:
        {
            //
            // Register that we need to send the device info structure on the
            // next upload request.
            //
            g_sNextUpload.pui8Start = (uint8_t *)&g_sDFUDeviceInfo;
            g_sNextUpload.ui32Length = sizeof(tDFUDeviceInfo);

            //
            // Make sure we don't append the DFU_CMD_PROG header when we send
            // back the data.
            //
            g_bSuppressUploadHeader = true;
            break;
        }

        //
        // We are being asked to set the format of uploaded images.
        //
        case DFU_CMD_BIN:
        {
            tDFUDownloadBinHeader *psHdr;

            //
            // Extract the required format the command header.
            //
            psHdr = (tDFUDownloadBinHeader *)psCmd;

            //
            // Set the global format appropriately.
            //
            g_bUploadBinary = psHdr->bBinary ? true : false;
            break;
        }

        //
        // We are being asked to prepare to reset the board and, as a result,
        // run the main application image.
        //
        case DFU_CMD_RESET:
        {
            //
            // Tell the main thread that it's time to go bye-bye...
            //
            HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_RESET) = 1;

            break;
        }

        //
        // We have been passed an unrecognized command identifier so report an
        // error.
        //
        default:
        {
            g_eDFUStatus = STATUS_ERR_VENDOR;
            return(false);
        }
    }

    return(true);
}

//*****************************************************************************
//
// This callback function is called when data is received for the DATA phase
// of an EP0 OUT transaction.  This data will either be a block of download
// data (if we are in STATE_DNLOAD_IDLE) or a new command (if we are in
// STATE_IDLE).
//
//*****************************************************************************
void
HandleEP0Data(uint32_t ui32Size)
{
    bool bRetcode;

    if(g_eDFUState == STATE_IDLE)
    {
        //
        // This must be a new DFU download command header so parse it and
        // determine what to do next.
        //
        bRetcode =
            ProcessDFUDnloadCommand((tDFUDownloadHeader *)g_pui8DFUBuffer,
                                    ui32Size);

        //
        // Did we receive a recognized and valid command?
        //
        if(!bRetcode)
        {
            //
            // No - set the error state.  The status is set within the
            // ProcessDFUDnloadCommand() function.
            //
            g_eDFUState = STATE_ERROR;
            return;
        }
    }
    else
    {
        //
        // If we are not in STATE_IDLE, this must be a block of data for an
        // ongoing download so signal the main thread to write it to flash.
        //
        g_ui16DFUBufferUsed = (uint16_t)ui32Size;
        g_pui8DFUWrite = g_pui8DFUBuffer;

        //
        // Tell the main thread to write the new data.
        //
        HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_WRITE) = 1;
    }

    //
    // Move to STATE_DNLOAD_SYNC since we now expect USBD_DFU_REQUEST_GETSTATUS
    // before the next USBD_DFU_REQUEST_DNLOAD.
    //
    g_eDFUState = STATE_DNLOAD_SYNC;
}

//*****************************************************************************
//
// Handle bus resets
//
// This function is called if the USB controller detects a reset condition on
// the bus.  If we are not in the process of downloading a new image, we use
// this as a signal to reboot and run the main application image.
//
//*****************************************************************************
void
HandleReset(void)
{
    //
    // Are we currently in the middle of a download operation?
    //
    if((g_eDFUState != STATE_DNLOAD_IDLE) &&
       (g_eDFUState != STATE_DNLOAD_SYNC) && (g_eDFUState != STATE_IDLE))
    {
        //
        // No - tell the main thread that it should reboot the system assuming
        // that we are already configured.  If we don't check that we are
        // already configured, this will cause a reset during initial
        // enumeration and that wouldn't be very helpful.
        //
        if(g_bAddressSet)
        {
            HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_RESET) = 1;
        }
    }
}

//*****************************************************************************
//
// Handle cases where the USB host disconnects.
//
//*****************************************************************************
void
HandleDisconnect(void)
{
    //
    // For error resilience, it may be desireable to note if the host
    // disconnects and, if partway through a main image download, clear the
    // first block of the flash to ensure that the image is not considered
    // valid on the next boot.  For now, however, we merely wait for the host
    // to connect again, remaining in DFU mode.
    //

    //
    // Remember that we are waiting for enumeration.
    //
    g_bAddressSet = false;
}

//*****************************************************************************
//
// Erase a single block of flash
//
// This function erases a single, 1KB block of flash, returning once the
// operation has completed.
//
// \return None.
//
//*****************************************************************************
static void
EraseFlashBlock(uint32_t ui32Addr)
{
    BL_FLASH_ERASE_FN_HOOK(ui32Addr);
}

//*****************************************************************************
//
//! This is the main routine for handling updating over USB.
//!
//! This function forms the main loop of the USB DFU updater.  It polls for
//! commands sent from the USB request handlers and is responsible for
//! erasing flash blocks, programming data into erased blocks and resetting
//! the device.
//!
//! \return None.
//
//*****************************************************************************
void
UpdaterUSB(void)
{
    uint32_t ui32Idx, ui32Start, ui32Temp;
    uint16_t ui16Used;
#ifndef FLASH_CODE_PROTECTION
    uint32_t ui32End;
#endif

    //
    // Loop forever waiting for the USB interrupt handlers to tell us to do
    // something.
    //
    while(1)
    {
        while(g_ui32CommandFlags == 0)
        {
            //
            // Wait for something to do.
            //
        }

        //
        // Are we being asked to perform a system reset?
        //
        if(HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_RESET))
        {
            //
            // Time to go bye-bye...  This will cause the microcontroller
            // to reset; no further code will be executed.
            //
            SCB->AIRCR = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

            //
            // The microcontroller should have reset, so this should never be
            // reached.  Just in case, loop forever.
            //
            while(1)
            {
            }
        }

        //
        // Are we being asked to erase a range of blocks in flash?
        //
        if(HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_ERASE))
        {
            //
            // Loop through the pages in the block of flash we have been asked
            // to erase and clear each one.
            //
            ui32Temp = g_sErase.ui32Length;
            for(ui32Idx = (uint32_t)g_sErase.pui8Start;
                ui32Idx < (uint32_t)(g_sErase.pui8Start + ui32Temp);
                ui32Idx += FLASH_PAGE_SIZE)
            {
                EraseFlashBlock(ui32Idx);
            }

            //
            // Clear the command flag to indicate that we are done.
            //
            HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_ERASE) = 0;
        }

        //
        // Are we being asked to program a block of flash?
        //
        if(HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_WRITE))
        {
            //
            // Decrypt the data if required.
            //
#ifdef BL_DECRYPT_FN_HOOK
            BL_DECRYPT_FN_HOOK(g_pui8DFUWrite, g_ui16DFUBufferUsed);
#endif

            //
            // Where will the new block be written?
            //
            ui32Start = (uint32_t)(g_sNextDownload.pui8Start);

#ifndef FLASH_CODE_PROTECTION
            //
            // What is the address of the last byte we will write in this
            // block of data?  We copy g_ui16DFUBufferUsed to prevent warnings
            // about "undefined order of volatile accesses" from some
            // compilers.
            //
            ui16Used = g_ui16DFUBufferUsed;

            ui32End = (uint32_t)g_sNextDownload.pui8Start + ui16Used - 1;

            //
            // Are we writing data at the start of a new flash block?  If so,
            // we need to erase the content of the block first.
            //
            if((ui32Start & (FLASH_PAGE_SIZE - 1)) == 0)
            {
                //
                // We are writing to the start of a block so erase it.
                //
                EraseFlashBlock(ui32Start & ~(FLASH_PAGE_SIZE - 1));
            }
            else
            {
                //
                // Will this block of data straddle two flash blocks?  If so,
                // we need to erase the following block.
                //
                if((ui32Start & ~(FLASH_PAGE_SIZE - 1)) !=
                   (ui32End & ~(FLASH_PAGE_SIZE - 1)))
                {
                    EraseFlashBlock(ui32End & ~(FLASH_PAGE_SIZE - 1));
                }
            }
#endif

            //
            // Write the new block of data to the flash
            //
            BL_FLASH_PROGRAM_FN_HOOK(ui32Start, g_pui8DFUWrite, ui16Used);

            //
            // Update our position and remaining size.
            //
            g_sNextDownload.pui8Start += ui16Used;
            g_sNextDownload.ui32Length -= ui16Used;

            //
            // Clear the command flag to indicate that we are done.
            //
            HWREGBITW(&g_ui32CommandFlags, CMD_FLAG_WRITE) = 0;

            //
            // If a progress hook function has been provided, call
            // it here.
            //
#ifdef BL_PROGRESS_FN_HOOK
            BL_PROGRESS_FN_HOOK(g_ui32ImageSize - g_sNextDownload.ui32Length,
                                g_ui32ImageSize);
#endif

            //
            // If we just finished the download and an end signal hook function
            // has been provided, call it too.
            //
#ifdef BL_END_FN_HOOK
            if(g_sNextDownload.ui32Length == 0)
            {
                BL_END_FN_HOOK();
            }
#endif
        }
    }
}

//*****************************************************************************
//
//! Configure the USB controller and place the DFU device on the bus.
//!
//! This function configures the USB controller for DFU device operation,
//! initializes the state machines required to control the firmware update and
//! places the device on the bus in preparation for requests from the host.  It
//! is assumed that the main system clock has been configured at this point.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureUSBInterface(void)
{
    uint32_t ui32FlashSize;

    //
    // Initialize our device information structure.
    //
    ui32FlashSize = BL_FLASH_SIZE_FN_HOOK();

    g_sDFUDeviceInfo.ui16FlashBlockSize = DFU_REPORTED_PAGE_SIZE;
    g_sDFUDeviceInfo.ui16NumFlashBlocks =
        ui32FlashSize / DFU_REPORTED_PAGE_SIZE;
    g_sDFUDeviceInfo.ui32ClassInfo = SYSCTL->DID0;
    g_sDFUDeviceInfo.ui32PartInfo = SYSCTL->DID1;
    g_sDFUDeviceInfo.ui32AppStartAddr = APP_START_ADDRESS;
#ifdef FLASH_RSVD_SPACE
    g_sDFUDeviceInfo.ui32FlashTop = ui32FlashSize - FLASH_RSVD_SPACE;
#else
    g_sDFUDeviceInfo.ui32FlashTop = ui32FlashSize;
#endif

    //
    // Publish our DFU device descriptors and place the device on the bus.
    //
    USBBLInit();
}

#if (defined USB_HAS_MUX) || (defined DOXYGEN)
//*****************************************************************************
//
//! Configures and set the mux selecting USB device-mode operation.
//!
//! On target boards which use a multiplexer to switch between USB host and
//! device operation, this function is used to configure the relevant GPIO
//! pin and drive it such that the mux selects USB device-mode operation.
//! If \b USB_HAS_MUX is not defined in bl_config.h, this function is compiled
//! out.
//!
//! \return None.
//
//*****************************************************************************
static void
SetUSBMux(void)
{
    //
    // Enable the GPIO peripheral that contains the mux control pin.
    //
    SYSCTL->RCGCGPIO |= USB_MUX_PERIPH;

    //
    // Delay a very short period before we access the newly-enabled peripheral.
    //
    Delay(1);

    //
    // Make the pin be an output.
    //
    USB_MUX_PORT->DIR   |= (1 << USB_MUX_PIN);
    USB_MUX_PORT->AFSEL &= ~(1 << USB_MUX_PIN);

    //
    // Set the output drive strength to 2mA.
    //
    USB_MUX_PORT->DR2R |= (1 << USB_MUX_PIN);
    USB_MUX_PORT->DR4R &= ~(1 << USB_MUX_PIN);
    USB_MUX_PORT->DR8R &= ~(1 << USB_MUX_PIN);
    USB_MUX_PORT->SLR  &=  ~(1 << USB_MUX_PIN);

    //
    // Set the pin type to a normal, GPIO output.
    //
    USB_MUX_PORT->ODR &= ~(1 << USB_MUX_PIN);
    USB_MUX_PORT->PUR &= ~(1 << USB_MUX_PIN);
    USB_MUX_PORT->PDR &= ~(1 << USB_MUX_PIN);
    USB_MUX_PORT->DEN |= (1 << USB_MUX_PIN);

    //
    // Clear this pin's bit in the analog mode select register.
    //
    USB_MUX_PORT->AMSEL &=  ~(1 << USB_MUX_PIN);

    //
    // Write the pin to the appropriate level to select USB device mode.
    //
    if(USB_MUX_DEVICE)
    {
        USB_MUX_PORT->DATA |= (1 << USB_MUX_PIN);
    }
    else
    {
        USB_MUX_PORT->DATA &= ~(1 << USB_MUX_PIN);
    }

}
#endif

//*****************************************************************************
//
//! Generic configuration is handled in this function.
//!
//! This function is called by the start up code to perform any configuration
//! necessary before calling the update routine.  It is responsible for setting
//! the system clock to the expected rate and setting flash programming
//! parameters prior to calling ConfigureUSBInterface() to set up the USB
//! hardware and place the DFU device on the bus.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureUSB(void)
{
    //
    // Since the crystal frequency was specified, enable the main oscillator
    // and clock the processor from it. Check for whether the Oscillator range
    // has to be set and wait states need to be updated
    //
    if(CRYSTAL_FREQ >= 10000000)
    {
        SYSCTL->MOSCCTL |= (SYSCTL_MOSCCTL_OSCRNG);
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN |
                             SYSCTL_MOSCCTL_NOXTAL);
    }
    else
    {
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN |
                             SYSCTL_MOSCCTL_NOXTAL);
    }

    //
    // Wait for the Oscillator to Stabilize
    //
    Delay(524288);

    if(CRYSTAL_FREQ > 16000000)
    {
        SYSCTL->MEMTIM0  = (SYSCTL_MEMTIM0_FBCHT_1_5 |
                            (1 << SYSCTL_MEMTIM0_FWS_S) |
                            SYSCTL_MEMTIM0_EBCHT_1_5 |
                            (1 << SYSCTL_MEMTIM0_EWS_S) |
                             SYSCTL_MEMTIM0_MB1);
        SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_MEMTIMU |
                            SYSCTL_RSCLKCFG_PLLSRC_MOSC |
                            SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }
    else
    {
        SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_PLLSRC_MOSC |
                            SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }

    //
    // Program the PLLFREQ0 and PLLFREQ1 registers for 480MHz
    // VCO Clock from the PLL and output clock of 240MHz using the Q divider.
    // Enable the PLL Power Up.
    //
    SYSCTL->PLLFREQ1 = (1 << SYSCTL_PLLFREQ1_Q_S |
                        4 << SYSCTL_PLLFREQ1_N_S);
    SYSCTL->PLLFREQ0 = (SYSCTL_PLLFREQ0_PLLPWR |
                        (96 << SYSCTL_PLLFREQ0_MINT_S));

    //
    // Wait for the PLL to Lock
    //
    while((SYSCTL->PLLSTAT & SYSCTL_PLLSTAT_LOCK) != SYSCTL_PLLSTAT_LOCK)
    {
    }

    //
    // Program the MEMTIM0 for 120MHz System Clock
    //
    SYSCTL->MEMTIM0  = (SYSCTL_MEMTIM0_FBCHT_3_5 |
                        (5 << SYSCTL_MEMTIM0_FWS_S) |
                         SYSCTL_MEMTIM0_EBCHT_3_5 |
                        (5 << SYSCTL_MEMTIM0_EWS_S) |
                         SYSCTL_MEMTIM0_MB1);

    //
    // Program the RSCLKCFG to switch to the PLL
    // with System Clock as 120MHz
    //
    SYSCTL->RSCLKCFG |= (SYSCTL_RSCLKCFG_MEMTIMU |
                         SYSCTL_RSCLKCFG_USEPLL |
                         0x1);

    //
    // If the target device has a mux to allow selection of USB host or
    // device mode, make sure this is set to device mode.
    //
#ifdef USB_HAS_MUX
    SetUSBMux();
#endif

    //
    // Configure the USB interface and put the device on the bus.
    //
    ConfigureUSBInterface();
}

//*****************************************************************************
//
//! This is the application entry point to the USB updater.
//!
//! This function should only be entered from a running application and not
//! when running the boot loader with no application present.  If the
//! calling application supports any USB device function, it must remove
//! itself from the USB bus prior to calling this function.  This function
//! assumes that the calling application has already configured the system
//! clock to run from the PLL.
//!
//! \return None.
//
//*****************************************************************************
void
AppUpdaterUSB(void)
{
    //
    // Since the crystal frequency was specified, enable the main oscillator
    // and clock the processor from it. Check for whether the Oscillator range
    // has to be set and wait states need to be updated
    //
    if(CRYSTAL_FREQ >= 10000000)
    {
        SYSCTL->MOSCCTL |= (SYSCTL_MOSCCTL_OSCRNG);
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN |
                             SYSCTL_MOSCCTL_NOXTAL);
    }
    else
    {
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN |
                             SYSCTL_MOSCCTL_NOXTAL);
    }

    //
    // Wait for the Oscillator to Stabilize
    //
    Delay(524288);

    if(CRYSTAL_FREQ > 16000000)
    {
        SYSCTL->MEMTIM0  = (SYSCTL_MEMTIM0_FBCHT_1_5 |
                            (1 << SYSCTL_MEMTIM0_FWS_S) |
                            SYSCTL_MEMTIM0_EBCHT_1_5 |
                            (1 << SYSCTL_MEMTIM0_EWS_S) |
                             SYSCTL_MEMTIM0_MB1);
        SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_MEMTIMU |
                            SYSCTL_RSCLKCFG_PLLSRC_MOSC |
                            SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }
    else
    {
        SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_PLLSRC_MOSC |
                            SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }

    //
    // Program the PLLFREQ0 and PLLFREQ1 registers for 480MHz
    // VCO Clock from the PLL. Enable the PLL Power Up.
    //
    SYSCTL->PLLFREQ1 = (1 << SYSCTL_PLLFREQ1_Q_S |
                        4 << SYSCTL_PLLFREQ1_N_S);
    SYSCTL->PLLFREQ0 = (SYSCTL_PLLFREQ0_PLLPWR |
                        (96 << SYSCTL_PLLFREQ0_MINT_S));

    //
    // Wait for the PLL to Lock
    //
    while((SYSCTL->PLLSTAT & SYSCTL_PLLSTAT_LOCK) != SYSCTL_PLLSTAT_LOCK)
    {
    }

    //
    // Program the MEMTIM0 for 120MHz System Clock
    //
    SYSCTL->MEMTIM0  = (SYSCTL_MEMTIM0_FBCHT_3_5 |
                        (5 << SYSCTL_MEMTIM0_FWS_S) |
                         SYSCTL_MEMTIM0_EBCHT_3_5 |
                        (5 << SYSCTL_MEMTIM0_EWS_S) |
                         SYSCTL_MEMTIM0_MB1);

    //
    // Program the RSCLKCFG to switch to the PLL
    // with System Clock as 120MHz
    //
    SYSCTL->RSCLKCFG |= (SYSCTL_RSCLKCFG_MEMTIMU |
                         SYSCTL_RSCLKCFG_USEPLL |
                         0x1);

    //
    // If the target device has a mux to allow selection of USB host or
    // device mode, make sure this is set to device mode.
    //
#ifdef USB_HAS_MUX
    SetUSBMux();
#endif

    //
    // Configure the USB interface and put the device on the bus.
    //
    ConfigureUSBInterface();

    //
    // Call the main update routine.
    //
    UpdaterUSB();
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
