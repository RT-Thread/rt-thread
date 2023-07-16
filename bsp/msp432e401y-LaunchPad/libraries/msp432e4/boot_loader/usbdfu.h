//*****************************************************************************
//
// usbdfu.h - Definitions related to the USB Device Firmware Upgrade class.
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

#ifndef __USBDFU_H__
#define __USBDFU_H__

//*****************************************************************************
//
// DFU attributes as published in the functional descriptor.
//
//*****************************************************************************
#define DFU_ATTR_WILL_DETACH    0x08
#define DFU_ATTR_MANIFEST_TOLERANT                                            \
                                0x04
#define DFU_ATTR_CAN_UPLOAD     0x02
#define DFU_ATTR_CAN_DOWNLOAD   0x01

//*****************************************************************************
//
// The states that the DFU device can be in.  These values are reported to
// the host in response to a USBD_DFU_REQUEST_GETSTATE request.
//
//*****************************************************************************
typedef enum
{
   STATE_APP_IDLE = 0,
   STATE_APP_DETACH,
   STATE_IDLE,
   STATE_DNLOAD_SYNC,
   STATE_DNBUSY,
   STATE_DNLOAD_IDLE,
   STATE_MANIFEST_SYNC,
   STATE_MANIFEST,
   STATE_MANIFEST_WAIT_RESET,
   STATE_UPLOAD_IDLE,
   STATE_ERROR
}
tDFUState;

//*****************************************************************************
//
// The current error status of the DFU device.  These values are reported to
// the host in response to a USBD_DFU_REQUEST_GETSTATUS request.
//
//*****************************************************************************
typedef enum
{
   STATUS_OK = 0,
   STATUS_ERR_TARGET,
   STATUS_ERR_FILE,
   STATUS_ERR_WRITE,
   STATUS_ERR_ERASE,
   STATUS_ERR_CHECK_ERASED,
   STATUS_ERR_PROG,
   STATUS_ERR_VERIFY,
   STATUS_ERR_ADDRESS,
   STATUS_ERR_NOTDONE,
   STATUS_ERR_FIRMWARE,
   STATUS_ERR_VENDOR,
   STATUS_ERR_USBR,
   STATUS_ERR_POR,
   STATUS_ERR_UNKNOWN,
   STATUS_ERR_STALLEDPKT
}
tDFUStatus;

//*****************************************************************************
//
// The descriptor type for the DFU functional descriptor.
//
//*****************************************************************************
#define USB_DFU_FUNC_DESCRIPTOR_TYPE   0x21

//*****************************************************************************
//
// The subclass identifier for DFU as reported to the host in the
// bInterfaceSubClass field of the DFU interface descriptor.
//
//*****************************************************************************
#define USB_DFU_SUBCLASS                0x01

//*****************************************************************************
//
// The protocol identifier for DFU as reported to the host in the
// bInterfaceProtocol field of the DFU interface descriptor.
//
//*****************************************************************************
#define USB_DFU_PROTOCOL                0x02
#define USB_DFU_RUNTIME_PROTOCOL        0x01

//*****************************************************************************
//
// DFU class-specific request identifiers.
//
//*****************************************************************************
#define USBD_DFU_REQUEST_DETACH         0
#define USBD_DFU_REQUEST_DNLOAD         1
#define USBD_DFU_REQUEST_UPLOAD         2
#define USBD_DFU_REQUEST_GETSTATUS      3
#define USBD_DFU_REQUEST_CLRSTATUS      4
#define USBD_DFU_REQUEST_GETSTATE       5
#define USBD_DFU_REQUEST_ABORT          6

//*****************************************************************************
//
// Request 1KB blocks from the host.  This value is published in the USB
// functional descriptor.
//
//*****************************************************************************
#define DFU_TRANSFER_SIZE       1024

//*****************************************************************************
//
// Device-specific request identifier.  This is used to determine whether
// the target device supports our DFU command protocol.  It is expected that
// a device not supporting our extensions will stall this request.  This
// request is only supported while the DFU device is in STATE_IDLE.
//
// An IN request containing the following parameters will result in the device
// sending back a tDFUQueryMSP432E4Protocol structure indicating that
// Device extensions are supported.  The actual values in wValue and wIndex
// have no meaning other than to act as markers in the unlikely event that
// another DFU device also chooses to use request ID 0x42 for some other
// purpose.
//
// wValue        - 0x23(REQUEST_MSP432E4_VALUE)
// wIndex        - Interface number
// wLength       - sizeof(tDFUQueryMSP432E4Protocol)
//
//*****************************************************************************
#define USBD_DFU_REQUEST_MSP432E4 0x42
#define REQUEST_MSP432E4_VALUE    0x23

#define DFU_PROTOCOL_USBLIB_MARKER                                            \
                                  0x4C4D
#define DFU_PROTOCOL_USBLIB_VERSION_1                                         \
                                  0x0001

#ifdef __ICCARM__
#pragma pack(1)
#endif

//*****************************************************************************
//
// The structure sent to the host when a valid USBD_DFU_REQUEST_MSP432E4 is
// received while the DFU device is in idle state.
//
//*****************************************************************************
typedef struct
{
    uint16_t ui16Marker;        // DFU_PROTOCOL_USBLIB_MARKER
    uint16_t ui16Version;       // DFU_PROTOCOL_USBLIB_VERSION_1
}
PACKED tDFUQueryMSP432E4Protocol;

//*****************************************************************************
//
// Structure sent to the host in response to USBD_DFU_REQUEST_GETSTATUS.
//
//*****************************************************************************
typedef struct
{
    uint8_t bStatus;
    uint8_t bwPollTimeout[3];
    uint8_t bState;
    uint8_t iString;
}
PACKED tDFUGetStatusResponse;

//*****************************************************************************
//
// Firmware Download Commands
//
// The data passed on a USBD_DFU_REQUEST_DNLOAD request is comprised of a
// header which instructs the boot loader how to interpret the block and
// block-specific data.  The following definitions relate to the download
// block headers.
//
//*****************************************************************************

//*****************************************************************************
//
// Supported command identifiers
//
//*****************************************************************************
#define DFU_CMD_PROG            0x01
#define DFU_CMD_READ            0x02
#define DFU_CMD_CHECK           0x03
#define DFU_CMD_ERASE           0x04
#define DFU_CMD_INFO            0x05
#define DFU_CMD_BIN             0x06
#define DFU_CMD_RESET           0x07

//*****************************************************************************
//
// Generic download command header.
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8Command;         // Command identifier.
    uint8_t pui8Data[7];        // Command-specific data elements.
}
PACKED tDFUDownloadHeader;

//*****************************************************************************
//
// Header for the DFU_CMD_PROG command.
//
// This command is used to program a section of the flash with the binary data
// which immediately follows the header. The start address of the data is
// expressed as a 1KB block number so 0 would represent the bottom of flash
// (which, incidentally, the USB boot loader will not let you program) and 0x10
// would represent address 16KB or 16384 (0x4000).  The ui32Length field
// contains the total number of bytes of data in the following programming
// operation.  The DFU device will not look for any command header on following
// USBD_DFU_REQUEST_DNLOAD requests until the operation is completed or
// aborted.
//
// By using this protocol, the DFU_CMD_PROG command header may be used as a
// simple header on the binary files to be sent to the DFU device for
// programming.  If we enforce the requirement that the DFU_CMD_PROG header is
// applied to each USBD_DFU_REQUEST_DNLOAD (one per block), this means that the
// host-side DFU application must be aware of the underlying protocol and
// insert these headers dynamically during programming operations.  This could
// be handled by post processing the binary to insert the headers at the
// appropriate points but this would then tie the binary structure to the
// chosen transfer size and break the operation if the transfer size were to
// change in the future.
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8Command;         // DFU_CMD_PROG
    uint8_t ui8Reserved;        // Reserved - set to 0x00.
    uint16_t ui16StartAddr;     // Block start address / 1024
    uint32_t ui32Length;        // Total length, in bytes, of following data
                                // for the complete download operation.
}
PACKED tDFUDownloadProgHeader;

//*****************************************************************************
//
// Header for the DFU_CMD_READ and DFU_CMD_CHECK commands.
//
// This command may be used to set the address range whose content will be
// returned on subsequent USBD_DFU_REQUEST_UPLOAD requests from the host.
//
// To read back a the contents of a region of flash, the host should send
// USBD_DFU_REQUEST_DNLOAD with ui8Command DFU_CMD_READ, ui16StartAddr set to
// the 1KB block start address and ui32Length set to the number of bytes to
// read.  The host should then send one or more USBD_DFU_REQUEST_UPLOAD
// requests to receive the current flash contents from the configured
// addresses.  Data returned will include an 8 byte DFU_CMD_PROG prefix
// structure unless the prefix has been disabled by sending a DFU_CMD_BIN
// command with the bBinary parameter set to 1.
//
// To check that a region of flash is erased, the DFU_CMD_CHECK command should
// be sent with ui16StartAddr and ui32Length set to describe the region to
// check.  The host should then send a USBD_DFU_REQUEST_GETSTATUS.  If the
// erase check was successful, the returned bStatus value will be STATUS_OK,
// otherwise it will be STATUS_ERR_CHECK_ERASED. Note that ui32Length passed
// must be a multiple of 4.  If this is not the case, the value will be
// truncated before the check is performed.
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8Command;         // DFU_CMD_READ or DFU_CMD_CHECK
    uint8_t ui8Reserved;        // Reserved - write to 0
    uint16_t ui16StartAddr;     // Block start address / 1024
    uint32_t ui32Length;        // The number of bytes of data to read back or
                                // check.
}
PACKED tDFUDownloadReadCheckHeader;

//*****************************************************************************
//
// Header for the DFU_CMD_ERASE command.
//
// This command may be used to erase a number of flash blocks.  The address of
// the first block to be erased is passed in ui16StartAddr with ui16NumBlocks
// containing the number of blocks to be erased from this address.  The block
// size of the device may be determined using the DFU_CMD_INFO command.
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8Command;         // DFU_CMD_ERASE
    uint8_t ui8Reserved;        // Reserved - set to 0
    uint16_t ui16StartAddr;     // Block start address / 1024
    uint16_t ui16NumBlocks;     // The number of blocks to erase
    uint8_t pui8Reserved2[2];   // Reserved - set to 0
}
PACKED tDFUDownloadEraseHeader;

//*****************************************************************************
//
// Header for the DFU_CMD_INFO command.
//
// This command may be used to query information about the connected device.
// After sending the command, the information is returned on the next
// USBD_DFU_REQUEST_UPLOAD request.
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8Command;         // DFU_CMD_INFO
    uint8_t pui8Reserved[7];    // Reserved - set to 0
}
PACKED tDFUDownloadInfoHeader;

//*****************************************************************************
//
// Header for the DFU_CMD_BIN command.
//
// This command may be used to set the format of uploaded data.  By default,
// images read using USBD_DFU_REQUEST_UPLOAD are formatted with the appropriate
// header to allow the same image to be flashed back to the device and have it
// located at the address from which it originated.  This is a requirement of
// the DFU class specification (section 6.2 "the uploaded image must be
// usable in a subsequent download") but may not be helpful in some cases where
// the application wishes to receive only the binary image from flash.  To
// instruct the DFU device to omit the position and size header, send this
// command with the bBinary field set to \b true prior to issuing a
// USBD_DFU_REQUEST_UPLOAD for image data.  The format choice remains in effect
// until the command is sent once again with bBinary set to \b false.
//
// Note that the format choice affects only image data sent and not responses
// read via USBD_DFU_REQUEST_UPLOAD following software-specific commands such
// as DFU_CMD_INFO.
//
//*****************************************************************************
typedef struct
{
    uint8_t ui8Command;         // DFU_CMD_BIN
    uint8_t bBinary;            // Set to true to omit image header or false
                                // to include it (the default)
    uint8_t pui8Reserved[6];    // Reserved - set to 0
}
PACKED tDFUDownloadBinHeader;

//*****************************************************************************
//
// The DFU_CMD_RESET command uses a tDFUDownloadHeader structure since
// only the ui8Command field is important.  This command causes an immediate
// reset of the the target board.
//
//*****************************************************************************

//*****************************************************************************
//
//! Payload returned in response to the DFU_CMD_INFO command.
//!
//! This is structure is returned in response to the first
//! USBD_DFU_REQUEST_UPLOAD request following a DFU_CMD_INFO command.
//
//*****************************************************************************
typedef struct
{
    //
    //! The size of a flash block in bytes.
    //
    uint16_t ui16FlashBlockSize;

    //
    //! The number of blocks of flash in the  device.  Total flash size is
    //! ui16NumFlashBlocks * ui16FlashBlockSize.
    //
    uint16_t ui16NumFlashBlocks;

    //
    //! Information on the part number, family, version and package as read
    //! from SYSCTL register DID1.
    //
    uint32_t ui32PartInfo;

    //
    //! Information on the part class and revision as read from SYSCTL DID0.
    //
    uint32_t ui32ClassInfo;

    //
    //! Address 1 byte above the highest location the boot loader can access.
    //
    uint32_t ui32FlashTop;

    //
    //! Lowest address the boot loader can write or erase.
    //
    uint32_t ui32AppStartAddr;
}
PACKED tDFUDeviceInfo;

#ifdef __ICCARM__
#pragma pack()
#endif

#endif // __USBDFU_H__
