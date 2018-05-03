//*****************************************************************************
//
// usbdevice.h - types and definitions used during USB enumeration.
//
// Copyright (c) 2008-2010 Texas Instruments Incorporated.  All rights reserved.
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
//
//*****************************************************************************

#ifndef __USBDEVICE_H__
#define __USBDEVICE_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup device_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The maximum number of independent interfaces that any single device
//! implementation can support.  Independent interfaces means interface
//! descriptors with different bInterfaceNumber values - several interface
//! descriptors offering different alternative settings but the same interface
//! number count as a single interface.
//
//*****************************************************************************
#define USB_MAX_INTERFACES_PER_DEVICE 8

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// The default USB endpoint FIFO configuration structure.  This structure
// contains definitions to set all USB FIFOs into single buffered mode with
// no DMA use.  Each endpoint's FIFO is sized to hold the largest maximum
// packet size for any interface alternate setting in the current config
// descriptor.  A pointer to this structure may be passed in the psFIFOConfig
// field of the tDeviceInfo structure passed to USBCDCInit if the application
// does not require any special handling of the USB controller FIFO.
//
//*****************************************************************************
extern const tFIFOConfig g_sUSBDefaultFIFOConfig;

//*****************************************************************************
//
// Public APIs offered by the USB library device control driver.
//
//*****************************************************************************
extern void USBDCDInit(uint32 ulIndex, tDeviceInfo *psDevice);
extern void USBDCDTerm(uint32 ulIndex);
extern void USBDCDStallEP0(uint32 ulIndex);
extern void USBDCDRequestDataEP0(uint32 ulIndex, uint8 *pucData,
                                 uint32 ulSize);
extern void USBDCDSendDataEP0(uint32 ulIndex, uint8 *pucData,
                              uint32 ulSize);
extern void USBDCDSetDefaultConfiguration(uint32 ulIndex,
                                          uint32 ulDefaultConfig);
extern uint32 USBDCDConfigDescGetSize(const tConfigHeader *psConfig);
extern uint32 USBDCDConfigDescGetNum(const tConfigHeader *psConfig,
                                            uint32 ulType);
extern tDescriptorHeader *USBDCDConfigDescGet(const tConfigHeader *psConfig,
                                              uint32 ulType,
                                              uint32 ulIndex,
                                              uint32 *pulSection);
extern uint32
       USBDCDConfigGetNumAlternateInterfaces(const tConfigHeader *psConfig,
                                             uint8 ucInterfaceNumber);
extern tInterfaceDescriptor *
       USBDCDConfigGetInterface(const tConfigHeader *psConfig,
                                uint32 ulIndex, uint32 ulAltCfg,
                                uint32 *pulSection);
extern tEndpointDescriptor *
       USBDCDConfigGetInterfaceEndpoint(const tConfigHeader *psConfig,
                                        uint32 ulInterfaceNumber,
                                        uint32 ulAltCfg,
                                        uint32 ulIndex);
extern void USBDCDPowerStatusSet(uint32 ulIndex, uint8 ucPower);
extern tBoolean USBDCDRemoteWakeupRequest(uint32 ulIndex);

//*****************************************************************************
//
// Early releases of the USB library had the following function named
// incorrectly.  This macro ensures that any code which used the previous name
// will still operate as expected.
//
//*****************************************************************************
#ifndef DEPRECATED
#define USBCDCConfigGetInterfaceEndpoint(a, b, c, d)                          \
            USBDCDConfigGetInterfaceEndpoint((a), (b), (c), (d))
#endif

//*****************************************************************************
//
// Device mode interrupt handler for controller index 0.
//
//*****************************************************************************
extern void USB0DeviceIntHandler(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBENUM_H__
