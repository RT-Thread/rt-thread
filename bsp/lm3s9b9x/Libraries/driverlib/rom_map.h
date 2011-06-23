//*****************************************************************************
//
// rom_map.h - Macros to facilitate calling functions in the ROM when they are
//             available and in flash otherwise.
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
// This is part of revision 6459 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __ROM_MAP_H__
#define __ROM_MAP_H__

//*****************************************************************************
//
// Macros for the ADC API.
//
//*****************************************************************************
#ifdef ROM_ADCSequenceDataGet
#define MAP_ADCSequenceDataGet \
        ROM_ADCSequenceDataGet
#else
#define MAP_ADCSequenceDataGet \
        ADCSequenceDataGet
#endif
#ifdef ROM_ADCIntDisable
#define MAP_ADCIntDisable \
        ROM_ADCIntDisable
#else
#define MAP_ADCIntDisable \
        ADCIntDisable
#endif
#ifdef ROM_ADCIntEnable
#define MAP_ADCIntEnable \
        ROM_ADCIntEnable
#else
#define MAP_ADCIntEnable \
        ADCIntEnable
#endif
#ifdef ROM_ADCIntStatus
#define MAP_ADCIntStatus \
        ROM_ADCIntStatus
#else
#define MAP_ADCIntStatus \
        ADCIntStatus
#endif
#ifdef ROM_ADCIntClear
#define MAP_ADCIntClear \
        ROM_ADCIntClear
#else
#define MAP_ADCIntClear \
        ADCIntClear
#endif
#ifdef ROM_ADCSequenceEnable
#define MAP_ADCSequenceEnable \
        ROM_ADCSequenceEnable
#else
#define MAP_ADCSequenceEnable \
        ADCSequenceEnable
#endif
#ifdef ROM_ADCSequenceDisable
#define MAP_ADCSequenceDisable \
        ROM_ADCSequenceDisable
#else
#define MAP_ADCSequenceDisable \
        ADCSequenceDisable
#endif
#ifdef ROM_ADCSequenceConfigure
#define MAP_ADCSequenceConfigure \
        ROM_ADCSequenceConfigure
#else
#define MAP_ADCSequenceConfigure \
        ADCSequenceConfigure
#endif
#ifdef ROM_ADCSequenceStepConfigure
#define MAP_ADCSequenceStepConfigure \
        ROM_ADCSequenceStepConfigure
#else
#define MAP_ADCSequenceStepConfigure \
        ADCSequenceStepConfigure
#endif
#ifdef ROM_ADCSequenceOverflow
#define MAP_ADCSequenceOverflow \
        ROM_ADCSequenceOverflow
#else
#define MAP_ADCSequenceOverflow \
        ADCSequenceOverflow
#endif
#ifdef ROM_ADCSequenceOverflowClear
#define MAP_ADCSequenceOverflowClear \
        ROM_ADCSequenceOverflowClear
#else
#define MAP_ADCSequenceOverflowClear \
        ADCSequenceOverflowClear
#endif
#ifdef ROM_ADCSequenceUnderflow
#define MAP_ADCSequenceUnderflow \
        ROM_ADCSequenceUnderflow
#else
#define MAP_ADCSequenceUnderflow \
        ADCSequenceUnderflow
#endif
#ifdef ROM_ADCSequenceUnderflowClear
#define MAP_ADCSequenceUnderflowClear \
        ROM_ADCSequenceUnderflowClear
#else
#define MAP_ADCSequenceUnderflowClear \
        ADCSequenceUnderflowClear
#endif
#ifdef ROM_ADCProcessorTrigger
#define MAP_ADCProcessorTrigger \
        ROM_ADCProcessorTrigger
#else
#define MAP_ADCProcessorTrigger \
        ADCProcessorTrigger
#endif
#ifdef ROM_ADCHardwareOversampleConfigure
#define MAP_ADCHardwareOversampleConfigure \
        ROM_ADCHardwareOversampleConfigure
#else
#define MAP_ADCHardwareOversampleConfigure \
        ADCHardwareOversampleConfigure
#endif
#ifdef ROM_ADCComparatorConfigure
#define MAP_ADCComparatorConfigure \
        ROM_ADCComparatorConfigure
#else
#define MAP_ADCComparatorConfigure \
        ADCComparatorConfigure
#endif
#ifdef ROM_ADCComparatorRegionSet
#define MAP_ADCComparatorRegionSet \
        ROM_ADCComparatorRegionSet
#else
#define MAP_ADCComparatorRegionSet \
        ADCComparatorRegionSet
#endif
#ifdef ROM_ADCComparatorReset
#define MAP_ADCComparatorReset \
        ROM_ADCComparatorReset
#else
#define MAP_ADCComparatorReset \
        ADCComparatorReset
#endif
#ifdef ROM_ADCComparatorIntDisable
#define MAP_ADCComparatorIntDisable \
        ROM_ADCComparatorIntDisable
#else
#define MAP_ADCComparatorIntDisable \
        ADCComparatorIntDisable
#endif
#ifdef ROM_ADCComparatorIntEnable
#define MAP_ADCComparatorIntEnable \
        ROM_ADCComparatorIntEnable
#else
#define MAP_ADCComparatorIntEnable \
        ADCComparatorIntEnable
#endif
#ifdef ROM_ADCComparatorIntStatus
#define MAP_ADCComparatorIntStatus \
        ROM_ADCComparatorIntStatus
#else
#define MAP_ADCComparatorIntStatus \
        ADCComparatorIntStatus
#endif
#ifdef ROM_ADCComparatorIntClear
#define MAP_ADCComparatorIntClear \
        ROM_ADCComparatorIntClear
#else
#define MAP_ADCComparatorIntClear \
        ADCComparatorIntClear
#endif

//*****************************************************************************
//
// Macros for the CAN API.
//
//*****************************************************************************
#ifdef ROM_CANIntClear
#define MAP_CANIntClear \
        ROM_CANIntClear
#else
#define MAP_CANIntClear \
        CANIntClear
#endif
#ifdef ROM_CANInit
#define MAP_CANInit \
        ROM_CANInit
#else
#define MAP_CANInit \
        CANInit
#endif
#ifdef ROM_CANEnable
#define MAP_CANEnable \
        ROM_CANEnable
#else
#define MAP_CANEnable \
        CANEnable
#endif
#ifdef ROM_CANDisable
#define MAP_CANDisable \
        ROM_CANDisable
#else
#define MAP_CANDisable \
        CANDisable
#endif
#ifdef ROM_CANBitTimingSet
#define MAP_CANBitTimingSet \
        ROM_CANBitTimingSet
#else
#define MAP_CANBitTimingSet \
        CANBitTimingSet
#endif
#ifdef ROM_CANBitTimingGet
#define MAP_CANBitTimingGet \
        ROM_CANBitTimingGet
#else
#define MAP_CANBitTimingGet \
        CANBitTimingGet
#endif
#ifdef ROM_CANMessageSet
#define MAP_CANMessageSet \
        ROM_CANMessageSet
#else
#define MAP_CANMessageSet \
        CANMessageSet
#endif
#ifdef ROM_CANMessageGet
#define MAP_CANMessageGet \
        ROM_CANMessageGet
#else
#define MAP_CANMessageGet \
        CANMessageGet
#endif
#ifdef ROM_CANStatusGet
#define MAP_CANStatusGet \
        ROM_CANStatusGet
#else
#define MAP_CANStatusGet \
        CANStatusGet
#endif
#ifdef ROM_CANMessageClear
#define MAP_CANMessageClear \
        ROM_CANMessageClear
#else
#define MAP_CANMessageClear \
        CANMessageClear
#endif
#ifdef ROM_CANIntEnable
#define MAP_CANIntEnable \
        ROM_CANIntEnable
#else
#define MAP_CANIntEnable \
        CANIntEnable
#endif
#ifdef ROM_CANIntDisable
#define MAP_CANIntDisable \
        ROM_CANIntDisable
#else
#define MAP_CANIntDisable \
        CANIntDisable
#endif
#ifdef ROM_CANIntStatus
#define MAP_CANIntStatus \
        ROM_CANIntStatus
#else
#define MAP_CANIntStatus \
        CANIntStatus
#endif
#ifdef ROM_CANRetryGet
#define MAP_CANRetryGet \
        ROM_CANRetryGet
#else
#define MAP_CANRetryGet \
        CANRetryGet
#endif
#ifdef ROM_CANRetrySet
#define MAP_CANRetrySet \
        ROM_CANRetrySet
#else
#define MAP_CANRetrySet \
        CANRetrySet
#endif
#ifdef ROM_CANErrCntrGet
#define MAP_CANErrCntrGet \
        ROM_CANErrCntrGet
#else
#define MAP_CANErrCntrGet \
        CANErrCntrGet
#endif
#ifdef ROM_CANBitRateSet
#define MAP_CANBitRateSet \
        ROM_CANBitRateSet
#else
#define MAP_CANBitRateSet \
        CANBitRateSet
#endif

//*****************************************************************************
//
// Macros for the Comparator API.
//
//*****************************************************************************
#ifdef ROM_ComparatorIntClear
#define MAP_ComparatorIntClear \
        ROM_ComparatorIntClear
#else
#define MAP_ComparatorIntClear \
        ComparatorIntClear
#endif
#ifdef ROM_ComparatorConfigure
#define MAP_ComparatorConfigure \
        ROM_ComparatorConfigure
#else
#define MAP_ComparatorConfigure \
        ComparatorConfigure
#endif
#ifdef ROM_ComparatorRefSet
#define MAP_ComparatorRefSet \
        ROM_ComparatorRefSet
#else
#define MAP_ComparatorRefSet \
        ComparatorRefSet
#endif
#ifdef ROM_ComparatorValueGet
#define MAP_ComparatorValueGet \
        ROM_ComparatorValueGet
#else
#define MAP_ComparatorValueGet \
        ComparatorValueGet
#endif
#ifdef ROM_ComparatorIntEnable
#define MAP_ComparatorIntEnable \
        ROM_ComparatorIntEnable
#else
#define MAP_ComparatorIntEnable \
        ComparatorIntEnable
#endif
#ifdef ROM_ComparatorIntDisable
#define MAP_ComparatorIntDisable \
        ROM_ComparatorIntDisable
#else
#define MAP_ComparatorIntDisable \
        ComparatorIntDisable
#endif
#ifdef ROM_ComparatorIntStatus
#define MAP_ComparatorIntStatus \
        ROM_ComparatorIntStatus
#else
#define MAP_ComparatorIntStatus \
        ComparatorIntStatus
#endif

//*****************************************************************************
//
// Macros for the Ethernet API.
//
//*****************************************************************************
#ifdef ROM_EPIIntStatus
#define MAP_EPIIntStatus \
        ROM_EPIIntStatus
#else
#define MAP_EPIIntStatus \
        EPIIntStatus
#endif
#ifdef ROM_EPIModeSet
#define MAP_EPIModeSet \
        ROM_EPIModeSet
#else
#define MAP_EPIModeSet \
        EPIModeSet
#endif
#ifdef ROM_EPIDividerSet
#define MAP_EPIDividerSet \
        ROM_EPIDividerSet
#else
#define MAP_EPIDividerSet \
        EPIDividerSet
#endif
#ifdef ROM_EPIConfigSDRAMSet
#define MAP_EPIConfigSDRAMSet \
        ROM_EPIConfigSDRAMSet
#else
#define MAP_EPIConfigSDRAMSet \
        EPIConfigSDRAMSet
#endif
#ifdef ROM_EPIConfigGPModeSet
#define MAP_EPIConfigGPModeSet \
        ROM_EPIConfigGPModeSet
#else
#define MAP_EPIConfigGPModeSet \
        EPIConfigGPModeSet
#endif
#ifdef ROM_EPIConfigHB8Set
#define MAP_EPIConfigHB8Set \
        ROM_EPIConfigHB8Set
#else
#define MAP_EPIConfigHB8Set \
        EPIConfigHB8Set
#endif
#ifdef ROM_EPIConfigHB16Set
#define MAP_EPIConfigHB16Set \
        ROM_EPIConfigHB16Set
#else
#define MAP_EPIConfigHB16Set \
        EPIConfigHB16Set
#endif
#ifdef ROM_EPIAddressMapSet
#define MAP_EPIAddressMapSet \
        ROM_EPIAddressMapSet
#else
#define MAP_EPIAddressMapSet \
        EPIAddressMapSet
#endif
#ifdef ROM_EPINonBlockingReadConfigure
#define MAP_EPINonBlockingReadConfigure \
        ROM_EPINonBlockingReadConfigure
#else
#define MAP_EPINonBlockingReadConfigure \
        EPINonBlockingReadConfigure
#endif
#ifdef ROM_EPINonBlockingReadStart
#define MAP_EPINonBlockingReadStart \
        ROM_EPINonBlockingReadStart
#else
#define MAP_EPINonBlockingReadStart \
        EPINonBlockingReadStart
#endif
#ifdef ROM_EPINonBlockingReadStop
#define MAP_EPINonBlockingReadStop \
        ROM_EPINonBlockingReadStop
#else
#define MAP_EPINonBlockingReadStop \
        EPINonBlockingReadStop
#endif
#ifdef ROM_EPINonBlockingReadCount
#define MAP_EPINonBlockingReadCount \
        ROM_EPINonBlockingReadCount
#else
#define MAP_EPINonBlockingReadCount \
        EPINonBlockingReadCount
#endif
#ifdef ROM_EPINonBlockingReadAvail
#define MAP_EPINonBlockingReadAvail \
        ROM_EPINonBlockingReadAvail
#else
#define MAP_EPINonBlockingReadAvail \
        EPINonBlockingReadAvail
#endif
#ifdef ROM_EPINonBlockingReadGet32
#define MAP_EPINonBlockingReadGet32 \
        ROM_EPINonBlockingReadGet32
#else
#define MAP_EPINonBlockingReadGet32 \
        EPINonBlockingReadGet32
#endif
#ifdef ROM_EPINonBlockingReadGet16
#define MAP_EPINonBlockingReadGet16 \
        ROM_EPINonBlockingReadGet16
#else
#define MAP_EPINonBlockingReadGet16 \
        EPINonBlockingReadGet16
#endif
#ifdef ROM_EPINonBlockingReadGet8
#define MAP_EPINonBlockingReadGet8 \
        ROM_EPINonBlockingReadGet8
#else
#define MAP_EPINonBlockingReadGet8 \
        EPINonBlockingReadGet8
#endif
#ifdef ROM_EPIFIFOConfig
#define MAP_EPIFIFOConfig \
        ROM_EPIFIFOConfig
#else
#define MAP_EPIFIFOConfig \
        EPIFIFOConfig
#endif
#ifdef ROM_EPIWriteFIFOCountGet
#define MAP_EPIWriteFIFOCountGet \
        ROM_EPIWriteFIFOCountGet
#else
#define MAP_EPIWriteFIFOCountGet \
        EPIWriteFIFOCountGet
#endif
#ifdef ROM_EPIIntEnable
#define MAP_EPIIntEnable \
        ROM_EPIIntEnable
#else
#define MAP_EPIIntEnable \
        EPIIntEnable
#endif
#ifdef ROM_EPIIntDisable
#define MAP_EPIIntDisable \
        ROM_EPIIntDisable
#else
#define MAP_EPIIntDisable \
        EPIIntDisable
#endif
#ifdef ROM_EPIIntErrorStatus
#define MAP_EPIIntErrorStatus \
        ROM_EPIIntErrorStatus
#else
#define MAP_EPIIntErrorStatus \
        EPIIntErrorStatus
#endif
#ifdef ROM_EPIIntErrorClear
#define MAP_EPIIntErrorClear \
        ROM_EPIIntErrorClear
#else
#define MAP_EPIIntErrorClear \
        EPIIntErrorClear
#endif

//*****************************************************************************
//
// Macros for the Ethernet API.
//
//*****************************************************************************
#ifdef ROM_EthernetIntClear
#define MAP_EthernetIntClear \
        ROM_EthernetIntClear
#else
#define MAP_EthernetIntClear \
        EthernetIntClear
#endif
#ifdef ROM_EthernetInitExpClk
#define MAP_EthernetInitExpClk \
        ROM_EthernetInitExpClk
#else
#define MAP_EthernetInitExpClk \
        EthernetInitExpClk
#endif
#ifdef ROM_EthernetConfigSet
#define MAP_EthernetConfigSet \
        ROM_EthernetConfigSet
#else
#define MAP_EthernetConfigSet \
        EthernetConfigSet
#endif
#ifdef ROM_EthernetConfigGet
#define MAP_EthernetConfigGet \
        ROM_EthernetConfigGet
#else
#define MAP_EthernetConfigGet \
        EthernetConfigGet
#endif
#ifdef ROM_EthernetMACAddrSet
#define MAP_EthernetMACAddrSet \
        ROM_EthernetMACAddrSet
#else
#define MAP_EthernetMACAddrSet \
        EthernetMACAddrSet
#endif
#ifdef ROM_EthernetMACAddrGet
#define MAP_EthernetMACAddrGet \
        ROM_EthernetMACAddrGet
#else
#define MAP_EthernetMACAddrGet \
        EthernetMACAddrGet
#endif
#ifdef ROM_EthernetEnable
#define MAP_EthernetEnable \
        ROM_EthernetEnable
#else
#define MAP_EthernetEnable \
        EthernetEnable
#endif
#ifdef ROM_EthernetDisable
#define MAP_EthernetDisable \
        ROM_EthernetDisable
#else
#define MAP_EthernetDisable \
        EthernetDisable
#endif
#ifdef ROM_EthernetPacketAvail
#define MAP_EthernetPacketAvail \
        ROM_EthernetPacketAvail
#else
#define MAP_EthernetPacketAvail \
        EthernetPacketAvail
#endif
#ifdef ROM_EthernetSpaceAvail
#define MAP_EthernetSpaceAvail \
        ROM_EthernetSpaceAvail
#else
#define MAP_EthernetSpaceAvail \
        EthernetSpaceAvail
#endif
#ifdef ROM_EthernetPacketGetNonBlocking
#define MAP_EthernetPacketGetNonBlocking \
        ROM_EthernetPacketGetNonBlocking
#else
#define MAP_EthernetPacketGetNonBlocking \
        EthernetPacketGetNonBlocking
#endif
#ifdef ROM_EthernetPacketGet
#define MAP_EthernetPacketGet \
        ROM_EthernetPacketGet
#else
#define MAP_EthernetPacketGet \
        EthernetPacketGet
#endif
#ifdef ROM_EthernetPacketPutNonBlocking
#define MAP_EthernetPacketPutNonBlocking \
        ROM_EthernetPacketPutNonBlocking
#else
#define MAP_EthernetPacketPutNonBlocking \
        EthernetPacketPutNonBlocking
#endif
#ifdef ROM_EthernetPacketPut
#define MAP_EthernetPacketPut \
        ROM_EthernetPacketPut
#else
#define MAP_EthernetPacketPut \
        EthernetPacketPut
#endif
#ifdef ROM_EthernetIntEnable
#define MAP_EthernetIntEnable \
        ROM_EthernetIntEnable
#else
#define MAP_EthernetIntEnable \
        EthernetIntEnable
#endif
#ifdef ROM_EthernetIntDisable
#define MAP_EthernetIntDisable \
        ROM_EthernetIntDisable
#else
#define MAP_EthernetIntDisable \
        EthernetIntDisable
#endif
#ifdef ROM_EthernetIntStatus
#define MAP_EthernetIntStatus \
        ROM_EthernetIntStatus
#else
#define MAP_EthernetIntStatus \
        EthernetIntStatus
#endif
#ifdef ROM_EthernetPHYWrite
#define MAP_EthernetPHYWrite \
        ROM_EthernetPHYWrite
#else
#define MAP_EthernetPHYWrite \
        EthernetPHYWrite
#endif
#ifdef ROM_EthernetPHYRead
#define MAP_EthernetPHYRead \
        ROM_EthernetPHYRead
#else
#define MAP_EthernetPHYRead \
        EthernetPHYRead
#endif

//*****************************************************************************
//
// Macros for the Flash API.
//
//*****************************************************************************
#ifdef ROM_FlashProgram
#define MAP_FlashProgram \
        ROM_FlashProgram
#else
#define MAP_FlashProgram \
        FlashProgram
#endif
#ifdef ROM_FlashUsecGet
#define MAP_FlashUsecGet \
        ROM_FlashUsecGet
#else
#define MAP_FlashUsecGet \
        FlashUsecGet
#endif
#ifdef ROM_FlashUsecSet
#define MAP_FlashUsecSet \
        ROM_FlashUsecSet
#else
#define MAP_FlashUsecSet \
        FlashUsecSet
#endif
#ifdef ROM_FlashErase
#define MAP_FlashErase \
        ROM_FlashErase
#else
#define MAP_FlashErase \
        FlashErase
#endif
#ifdef ROM_FlashProtectGet
#define MAP_FlashProtectGet \
        ROM_FlashProtectGet
#else
#define MAP_FlashProtectGet \
        FlashProtectGet
#endif
#ifdef ROM_FlashProtectSet
#define MAP_FlashProtectSet \
        ROM_FlashProtectSet
#else
#define MAP_FlashProtectSet \
        FlashProtectSet
#endif
#ifdef ROM_FlashProtectSave
#define MAP_FlashProtectSave \
        ROM_FlashProtectSave
#else
#define MAP_FlashProtectSave \
        FlashProtectSave
#endif
#ifdef ROM_FlashUserGet
#define MAP_FlashUserGet \
        ROM_FlashUserGet
#else
#define MAP_FlashUserGet \
        FlashUserGet
#endif
#ifdef ROM_FlashUserSet
#define MAP_FlashUserSet \
        ROM_FlashUserSet
#else
#define MAP_FlashUserSet \
        FlashUserSet
#endif
#ifdef ROM_FlashUserSave
#define MAP_FlashUserSave \
        ROM_FlashUserSave
#else
#define MAP_FlashUserSave \
        FlashUserSave
#endif
#ifdef ROM_FlashIntEnable
#define MAP_FlashIntEnable \
        ROM_FlashIntEnable
#else
#define MAP_FlashIntEnable \
        FlashIntEnable
#endif
#ifdef ROM_FlashIntDisable
#define MAP_FlashIntDisable \
        ROM_FlashIntDisable
#else
#define MAP_FlashIntDisable \
        FlashIntDisable
#endif
#ifdef ROM_FlashIntStatus
#define MAP_FlashIntStatus \
        ROM_FlashIntStatus
#else
#define MAP_FlashIntStatus \
        FlashIntStatus
#endif
#ifdef ROM_FlashIntClear
#define MAP_FlashIntClear \
        ROM_FlashIntClear
#else
#define MAP_FlashIntClear \
        FlashIntClear
#endif

//*****************************************************************************
//
// Macros for the GPIO API.
//
//*****************************************************************************
#ifdef ROM_GPIOPinWrite
#define MAP_GPIOPinWrite \
        ROM_GPIOPinWrite
#else
#define MAP_GPIOPinWrite \
        GPIOPinWrite
#endif
#ifdef ROM_GPIODirModeSet
#define MAP_GPIODirModeSet \
        ROM_GPIODirModeSet
#else
#define MAP_GPIODirModeSet \
        GPIODirModeSet
#endif
#ifdef ROM_GPIODirModeGet
#define MAP_GPIODirModeGet \
        ROM_GPIODirModeGet
#else
#define MAP_GPIODirModeGet \
        GPIODirModeGet
#endif
#ifdef ROM_GPIOIntTypeSet
#define MAP_GPIOIntTypeSet \
        ROM_GPIOIntTypeSet
#else
#define MAP_GPIOIntTypeSet \
        GPIOIntTypeSet
#endif
#ifdef ROM_GPIOIntTypeGet
#define MAP_GPIOIntTypeGet \
        ROM_GPIOIntTypeGet
#else
#define MAP_GPIOIntTypeGet \
        GPIOIntTypeGet
#endif
#ifdef ROM_GPIOPadConfigSet
#define MAP_GPIOPadConfigSet \
        ROM_GPIOPadConfigSet
#else
#define MAP_GPIOPadConfigSet \
        GPIOPadConfigSet
#endif
#ifdef ROM_GPIOPadConfigGet
#define MAP_GPIOPadConfigGet \
        ROM_GPIOPadConfigGet
#else
#define MAP_GPIOPadConfigGet \
        GPIOPadConfigGet
#endif
#ifdef ROM_GPIOPinIntEnable
#define MAP_GPIOPinIntEnable \
        ROM_GPIOPinIntEnable
#else
#define MAP_GPIOPinIntEnable \
        GPIOPinIntEnable
#endif
#ifdef ROM_GPIOPinIntDisable
#define MAP_GPIOPinIntDisable \
        ROM_GPIOPinIntDisable
#else
#define MAP_GPIOPinIntDisable \
        GPIOPinIntDisable
#endif
#ifdef ROM_GPIOPinIntStatus
#define MAP_GPIOPinIntStatus \
        ROM_GPIOPinIntStatus
#else
#define MAP_GPIOPinIntStatus \
        GPIOPinIntStatus
#endif
#ifdef ROM_GPIOPinIntClear
#define MAP_GPIOPinIntClear \
        ROM_GPIOPinIntClear
#else
#define MAP_GPIOPinIntClear \
        GPIOPinIntClear
#endif
#ifdef ROM_GPIOPinRead
#define MAP_GPIOPinRead \
        ROM_GPIOPinRead
#else
#define MAP_GPIOPinRead \
        GPIOPinRead
#endif
#ifdef ROM_GPIOPinTypeCAN
#define MAP_GPIOPinTypeCAN \
        ROM_GPIOPinTypeCAN
#else
#define MAP_GPIOPinTypeCAN \
        GPIOPinTypeCAN
#endif
#ifdef ROM_GPIOPinTypeComparator
#define MAP_GPIOPinTypeComparator \
        ROM_GPIOPinTypeComparator
#else
#define MAP_GPIOPinTypeComparator \
        GPIOPinTypeComparator
#endif
#ifdef ROM_GPIOPinTypeGPIOInput
#define MAP_GPIOPinTypeGPIOInput \
        ROM_GPIOPinTypeGPIOInput
#else
#define MAP_GPIOPinTypeGPIOInput \
        GPIOPinTypeGPIOInput
#endif
#ifdef ROM_GPIOPinTypeGPIOOutput
#define MAP_GPIOPinTypeGPIOOutput \
        ROM_GPIOPinTypeGPIOOutput
#else
#define MAP_GPIOPinTypeGPIOOutput \
        GPIOPinTypeGPIOOutput
#endif
#ifdef ROM_GPIOPinTypeI2C
#define MAP_GPIOPinTypeI2C \
        ROM_GPIOPinTypeI2C
#else
#define MAP_GPIOPinTypeI2C \
        GPIOPinTypeI2C
#endif
#ifdef ROM_GPIOPinTypePWM
#define MAP_GPIOPinTypePWM \
        ROM_GPIOPinTypePWM
#else
#define MAP_GPIOPinTypePWM \
        GPIOPinTypePWM
#endif
#ifdef ROM_GPIOPinTypeQEI
#define MAP_GPIOPinTypeQEI \
        ROM_GPIOPinTypeQEI
#else
#define MAP_GPIOPinTypeQEI \
        GPIOPinTypeQEI
#endif
#ifdef ROM_GPIOPinTypeSSI
#define MAP_GPIOPinTypeSSI \
        ROM_GPIOPinTypeSSI
#else
#define MAP_GPIOPinTypeSSI \
        GPIOPinTypeSSI
#endif
#ifdef ROM_GPIOPinTypeTimer
#define MAP_GPIOPinTypeTimer \
        ROM_GPIOPinTypeTimer
#else
#define MAP_GPIOPinTypeTimer \
        GPIOPinTypeTimer
#endif
#ifdef ROM_GPIOPinTypeUART
#define MAP_GPIOPinTypeUART \
        ROM_GPIOPinTypeUART
#else
#define MAP_GPIOPinTypeUART \
        GPIOPinTypeUART
#endif
#ifdef ROM_GPIOPinTypeGPIOOutputOD
#define MAP_GPIOPinTypeGPIOOutputOD \
        ROM_GPIOPinTypeGPIOOutputOD
#else
#define MAP_GPIOPinTypeGPIOOutputOD \
        GPIOPinTypeGPIOOutputOD
#endif
#ifdef ROM_GPIOPinTypeADC
#define MAP_GPIOPinTypeADC \
        ROM_GPIOPinTypeADC
#else
#define MAP_GPIOPinTypeADC \
        GPIOPinTypeADC
#endif
#ifdef ROM_GPIOPinTypeUSBDigital
#define MAP_GPIOPinTypeUSBDigital \
        ROM_GPIOPinTypeUSBDigital
#else
#define MAP_GPIOPinTypeUSBDigital \
        GPIOPinTypeUSBDigital
#endif
#ifdef ROM_GPIOPinTypeI2S
#define MAP_GPIOPinTypeI2S \
        ROM_GPIOPinTypeI2S
#else
#define MAP_GPIOPinTypeI2S \
        GPIOPinTypeI2S
#endif
#ifdef ROM_GPIOPinConfigure
#define MAP_GPIOPinConfigure \
        ROM_GPIOPinConfigure
#else
#define MAP_GPIOPinConfigure \
        GPIOPinConfigure
#endif
#ifdef ROM_GPIOPinTypeEthernetLED
#define MAP_GPIOPinTypeEthernetLED \
        ROM_GPIOPinTypeEthernetLED
#else
#define MAP_GPIOPinTypeEthernetLED \
        GPIOPinTypeEthernetLED
#endif
#ifdef ROM_GPIOPinTypeUSBAnalog
#define MAP_GPIOPinTypeUSBAnalog \
        ROM_GPIOPinTypeUSBAnalog
#else
#define MAP_GPIOPinTypeUSBAnalog \
        GPIOPinTypeUSBAnalog
#endif

//*****************************************************************************
//
// Macros for the Hibernate API.
//
//*****************************************************************************
#ifdef ROM_HibernateIntClear
#define MAP_HibernateIntClear \
        ROM_HibernateIntClear
#else
#define MAP_HibernateIntClear \
        HibernateIntClear
#endif
#ifdef ROM_HibernateEnableExpClk
#define MAP_HibernateEnableExpClk \
        ROM_HibernateEnableExpClk
#else
#define MAP_HibernateEnableExpClk \
        HibernateEnableExpClk
#endif
#ifdef ROM_HibernateDisable
#define MAP_HibernateDisable \
        ROM_HibernateDisable
#else
#define MAP_HibernateDisable \
        HibernateDisable
#endif
#ifdef ROM_HibernateClockSelect
#define MAP_HibernateClockSelect \
        ROM_HibernateClockSelect
#else
#define MAP_HibernateClockSelect \
        HibernateClockSelect
#endif
#ifdef ROM_HibernateRTCEnable
#define MAP_HibernateRTCEnable \
        ROM_HibernateRTCEnable
#else
#define MAP_HibernateRTCEnable \
        HibernateRTCEnable
#endif
#ifdef ROM_HibernateRTCDisable
#define MAP_HibernateRTCDisable \
        ROM_HibernateRTCDisable
#else
#define MAP_HibernateRTCDisable \
        HibernateRTCDisable
#endif
#ifdef ROM_HibernateWakeSet
#define MAP_HibernateWakeSet \
        ROM_HibernateWakeSet
#else
#define MAP_HibernateWakeSet \
        HibernateWakeSet
#endif
#ifdef ROM_HibernateWakeGet
#define MAP_HibernateWakeGet \
        ROM_HibernateWakeGet
#else
#define MAP_HibernateWakeGet \
        HibernateWakeGet
#endif
#ifdef ROM_HibernateLowBatSet
#define MAP_HibernateLowBatSet \
        ROM_HibernateLowBatSet
#else
#define MAP_HibernateLowBatSet \
        HibernateLowBatSet
#endif
#ifdef ROM_HibernateLowBatGet
#define MAP_HibernateLowBatGet \
        ROM_HibernateLowBatGet
#else
#define MAP_HibernateLowBatGet \
        HibernateLowBatGet
#endif
#ifdef ROM_HibernateRTCSet
#define MAP_HibernateRTCSet \
        ROM_HibernateRTCSet
#else
#define MAP_HibernateRTCSet \
        HibernateRTCSet
#endif
#ifdef ROM_HibernateRTCGet
#define MAP_HibernateRTCGet \
        ROM_HibernateRTCGet
#else
#define MAP_HibernateRTCGet \
        HibernateRTCGet
#endif
#ifdef ROM_HibernateRTCMatch0Set
#define MAP_HibernateRTCMatch0Set \
        ROM_HibernateRTCMatch0Set
#else
#define MAP_HibernateRTCMatch0Set \
        HibernateRTCMatch0Set
#endif
#ifdef ROM_HibernateRTCMatch0Get
#define MAP_HibernateRTCMatch0Get \
        ROM_HibernateRTCMatch0Get
#else
#define MAP_HibernateRTCMatch0Get \
        HibernateRTCMatch0Get
#endif
#ifdef ROM_HibernateRTCMatch1Set
#define MAP_HibernateRTCMatch1Set \
        ROM_HibernateRTCMatch1Set
#else
#define MAP_HibernateRTCMatch1Set \
        HibernateRTCMatch1Set
#endif
#ifdef ROM_HibernateRTCMatch1Get
#define MAP_HibernateRTCMatch1Get \
        ROM_HibernateRTCMatch1Get
#else
#define MAP_HibernateRTCMatch1Get \
        HibernateRTCMatch1Get
#endif
#ifdef ROM_HibernateRTCTrimSet
#define MAP_HibernateRTCTrimSet \
        ROM_HibernateRTCTrimSet
#else
#define MAP_HibernateRTCTrimSet \
        HibernateRTCTrimSet
#endif
#ifdef ROM_HibernateRTCTrimGet
#define MAP_HibernateRTCTrimGet \
        ROM_HibernateRTCTrimGet
#else
#define MAP_HibernateRTCTrimGet \
        HibernateRTCTrimGet
#endif
#ifdef ROM_HibernateDataSet
#define MAP_HibernateDataSet \
        ROM_HibernateDataSet
#else
#define MAP_HibernateDataSet \
        HibernateDataSet
#endif
#ifdef ROM_HibernateDataGet
#define MAP_HibernateDataGet \
        ROM_HibernateDataGet
#else
#define MAP_HibernateDataGet \
        HibernateDataGet
#endif
#ifdef ROM_HibernateRequest
#define MAP_HibernateRequest \
        ROM_HibernateRequest
#else
#define MAP_HibernateRequest \
        HibernateRequest
#endif
#ifdef ROM_HibernateIntEnable
#define MAP_HibernateIntEnable \
        ROM_HibernateIntEnable
#else
#define MAP_HibernateIntEnable \
        HibernateIntEnable
#endif
#ifdef ROM_HibernateIntDisable
#define MAP_HibernateIntDisable \
        ROM_HibernateIntDisable
#else
#define MAP_HibernateIntDisable \
        HibernateIntDisable
#endif
#ifdef ROM_HibernateIntStatus
#define MAP_HibernateIntStatus \
        ROM_HibernateIntStatus
#else
#define MAP_HibernateIntStatus \
        HibernateIntStatus
#endif
#ifdef ROM_HibernateIsActive
#define MAP_HibernateIsActive \
        ROM_HibernateIsActive
#else
#define MAP_HibernateIsActive \
        HibernateIsActive
#endif

//*****************************************************************************
//
// Macros for the I2C API.
//
//*****************************************************************************
#ifdef ROM_I2CMasterDataPut
#define MAP_I2CMasterDataPut \
        ROM_I2CMasterDataPut
#else
#define MAP_I2CMasterDataPut \
        I2CMasterDataPut
#endif
#ifdef ROM_I2CMasterInitExpClk
#define MAP_I2CMasterInitExpClk \
        ROM_I2CMasterInitExpClk
#else
#define MAP_I2CMasterInitExpClk \
        I2CMasterInitExpClk
#endif
#ifdef ROM_I2CSlaveInit
#define MAP_I2CSlaveInit \
        ROM_I2CSlaveInit
#else
#define MAP_I2CSlaveInit \
        I2CSlaveInit
#endif
#ifdef ROM_I2CMasterEnable
#define MAP_I2CMasterEnable \
        ROM_I2CMasterEnable
#else
#define MAP_I2CMasterEnable \
        I2CMasterEnable
#endif
#ifdef ROM_I2CSlaveEnable
#define MAP_I2CSlaveEnable \
        ROM_I2CSlaveEnable
#else
#define MAP_I2CSlaveEnable \
        I2CSlaveEnable
#endif
#ifdef ROM_I2CMasterDisable
#define MAP_I2CMasterDisable \
        ROM_I2CMasterDisable
#else
#define MAP_I2CMasterDisable \
        I2CMasterDisable
#endif
#ifdef ROM_I2CSlaveDisable
#define MAP_I2CSlaveDisable \
        ROM_I2CSlaveDisable
#else
#define MAP_I2CSlaveDisable \
        I2CSlaveDisable
#endif
#ifdef ROM_I2CMasterIntEnable
#define MAP_I2CMasterIntEnable \
        ROM_I2CMasterIntEnable
#else
#define MAP_I2CMasterIntEnable \
        I2CMasterIntEnable
#endif
#ifdef ROM_I2CSlaveIntEnable
#define MAP_I2CSlaveIntEnable \
        ROM_I2CSlaveIntEnable
#else
#define MAP_I2CSlaveIntEnable \
        I2CSlaveIntEnable
#endif
#ifdef ROM_I2CMasterIntDisable
#define MAP_I2CMasterIntDisable \
        ROM_I2CMasterIntDisable
#else
#define MAP_I2CMasterIntDisable \
        I2CMasterIntDisable
#endif
#ifdef ROM_I2CSlaveIntDisable
#define MAP_I2CSlaveIntDisable \
        ROM_I2CSlaveIntDisable
#else
#define MAP_I2CSlaveIntDisable \
        I2CSlaveIntDisable
#endif
#ifdef ROM_I2CMasterIntStatus
#define MAP_I2CMasterIntStatus \
        ROM_I2CMasterIntStatus
#else
#define MAP_I2CMasterIntStatus \
        I2CMasterIntStatus
#endif
#ifdef ROM_I2CSlaveIntStatus
#define MAP_I2CSlaveIntStatus \
        ROM_I2CSlaveIntStatus
#else
#define MAP_I2CSlaveIntStatus \
        I2CSlaveIntStatus
#endif
#ifdef ROM_I2CMasterIntClear
#define MAP_I2CMasterIntClear \
        ROM_I2CMasterIntClear
#else
#define MAP_I2CMasterIntClear \
        I2CMasterIntClear
#endif
#ifdef ROM_I2CSlaveIntClear
#define MAP_I2CSlaveIntClear \
        ROM_I2CSlaveIntClear
#else
#define MAP_I2CSlaveIntClear \
        I2CSlaveIntClear
#endif
#ifdef ROM_I2CMasterSlaveAddrSet
#define MAP_I2CMasterSlaveAddrSet \
        ROM_I2CMasterSlaveAddrSet
#else
#define MAP_I2CMasterSlaveAddrSet \
        I2CMasterSlaveAddrSet
#endif
#ifdef ROM_I2CMasterBusy
#define MAP_I2CMasterBusy \
        ROM_I2CMasterBusy
#else
#define MAP_I2CMasterBusy \
        I2CMasterBusy
#endif
#ifdef ROM_I2CMasterBusBusy
#define MAP_I2CMasterBusBusy \
        ROM_I2CMasterBusBusy
#else
#define MAP_I2CMasterBusBusy \
        I2CMasterBusBusy
#endif
#ifdef ROM_I2CMasterControl
#define MAP_I2CMasterControl \
        ROM_I2CMasterControl
#else
#define MAP_I2CMasterControl \
        I2CMasterControl
#endif
#ifdef ROM_I2CMasterErr
#define MAP_I2CMasterErr \
        ROM_I2CMasterErr
#else
#define MAP_I2CMasterErr \
        I2CMasterErr
#endif
#ifdef ROM_I2CMasterDataGet
#define MAP_I2CMasterDataGet \
        ROM_I2CMasterDataGet
#else
#define MAP_I2CMasterDataGet \
        I2CMasterDataGet
#endif
#ifdef ROM_I2CSlaveStatus
#define MAP_I2CSlaveStatus \
        ROM_I2CSlaveStatus
#else
#define MAP_I2CSlaveStatus \
        I2CSlaveStatus
#endif
#ifdef ROM_I2CSlaveDataPut
#define MAP_I2CSlaveDataPut \
        ROM_I2CSlaveDataPut
#else
#define MAP_I2CSlaveDataPut \
        I2CSlaveDataPut
#endif
#ifdef ROM_I2CSlaveDataGet
#define MAP_I2CSlaveDataGet \
        ROM_I2CSlaveDataGet
#else
#define MAP_I2CSlaveDataGet \
        I2CSlaveDataGet
#endif
#ifdef ROM_I2CSlaveIntEnableEx
#define MAP_I2CSlaveIntEnableEx \
        ROM_I2CSlaveIntEnableEx
#else
#define MAP_I2CSlaveIntEnableEx \
        I2CSlaveIntEnableEx
#endif
#ifdef ROM_I2CSlaveIntDisableEx
#define MAP_I2CSlaveIntDisableEx \
        ROM_I2CSlaveIntDisableEx
#else
#define MAP_I2CSlaveIntDisableEx \
        I2CSlaveIntDisableEx
#endif
#ifdef ROM_I2CSlaveIntStatusEx
#define MAP_I2CSlaveIntStatusEx \
        ROM_I2CSlaveIntStatusEx
#else
#define MAP_I2CSlaveIntStatusEx \
        I2CSlaveIntStatusEx
#endif
#ifdef ROM_I2CSlaveIntClearEx
#define MAP_I2CSlaveIntClearEx \
        ROM_I2CSlaveIntClearEx
#else
#define MAP_I2CSlaveIntClearEx \
        I2CSlaveIntClearEx
#endif

//*****************************************************************************
//
// Macros for the I2S API.
//
//*****************************************************************************
#ifdef ROM_I2SIntStatus
#define MAP_I2SIntStatus \
        ROM_I2SIntStatus
#else
#define MAP_I2SIntStatus \
        I2SIntStatus
#endif
#ifdef ROM_I2STxEnable
#define MAP_I2STxEnable \
        ROM_I2STxEnable
#else
#define MAP_I2STxEnable \
        I2STxEnable
#endif
#ifdef ROM_I2STxDisable
#define MAP_I2STxDisable \
        ROM_I2STxDisable
#else
#define MAP_I2STxDisable \
        I2STxDisable
#endif
#ifdef ROM_I2STxDataPut
#define MAP_I2STxDataPut \
        ROM_I2STxDataPut
#else
#define MAP_I2STxDataPut \
        I2STxDataPut
#endif
#ifdef ROM_I2STxDataPutNonBlocking
#define MAP_I2STxDataPutNonBlocking \
        ROM_I2STxDataPutNonBlocking
#else
#define MAP_I2STxDataPutNonBlocking \
        I2STxDataPutNonBlocking
#endif
#ifdef ROM_I2STxConfigSet
#define MAP_I2STxConfigSet \
        ROM_I2STxConfigSet
#else
#define MAP_I2STxConfigSet \
        I2STxConfigSet
#endif
#ifdef ROM_I2STxFIFOLimitSet
#define MAP_I2STxFIFOLimitSet \
        ROM_I2STxFIFOLimitSet
#else
#define MAP_I2STxFIFOLimitSet \
        I2STxFIFOLimitSet
#endif
#ifdef ROM_I2STxFIFOLimitGet
#define MAP_I2STxFIFOLimitGet \
        ROM_I2STxFIFOLimitGet
#else
#define MAP_I2STxFIFOLimitGet \
        I2STxFIFOLimitGet
#endif
#ifdef ROM_I2STxFIFOLevelGet
#define MAP_I2STxFIFOLevelGet \
        ROM_I2STxFIFOLevelGet
#else
#define MAP_I2STxFIFOLevelGet \
        I2STxFIFOLevelGet
#endif
#ifdef ROM_I2SRxEnable
#define MAP_I2SRxEnable \
        ROM_I2SRxEnable
#else
#define MAP_I2SRxEnable \
        I2SRxEnable
#endif
#ifdef ROM_I2SRxDisable
#define MAP_I2SRxDisable \
        ROM_I2SRxDisable
#else
#define MAP_I2SRxDisable \
        I2SRxDisable
#endif
#ifdef ROM_I2SRxDataGet
#define MAP_I2SRxDataGet \
        ROM_I2SRxDataGet
#else
#define MAP_I2SRxDataGet \
        I2SRxDataGet
#endif
#ifdef ROM_I2SRxDataGetNonBlocking
#define MAP_I2SRxDataGetNonBlocking \
        ROM_I2SRxDataGetNonBlocking
#else
#define MAP_I2SRxDataGetNonBlocking \
        I2SRxDataGetNonBlocking
#endif
#ifdef ROM_I2SRxConfigSet
#define MAP_I2SRxConfigSet \
        ROM_I2SRxConfigSet
#else
#define MAP_I2SRxConfigSet \
        I2SRxConfigSet
#endif
#ifdef ROM_I2SRxFIFOLimitSet
#define MAP_I2SRxFIFOLimitSet \
        ROM_I2SRxFIFOLimitSet
#else
#define MAP_I2SRxFIFOLimitSet \
        I2SRxFIFOLimitSet
#endif
#ifdef ROM_I2SRxFIFOLimitGet
#define MAP_I2SRxFIFOLimitGet \
        ROM_I2SRxFIFOLimitGet
#else
#define MAP_I2SRxFIFOLimitGet \
        I2SRxFIFOLimitGet
#endif
#ifdef ROM_I2SRxFIFOLevelGet
#define MAP_I2SRxFIFOLevelGet \
        ROM_I2SRxFIFOLevelGet
#else
#define MAP_I2SRxFIFOLevelGet \
        I2SRxFIFOLevelGet
#endif
#ifdef ROM_I2STxRxEnable
#define MAP_I2STxRxEnable \
        ROM_I2STxRxEnable
#else
#define MAP_I2STxRxEnable \
        I2STxRxEnable
#endif
#ifdef ROM_I2STxRxDisable
#define MAP_I2STxRxDisable \
        ROM_I2STxRxDisable
#else
#define MAP_I2STxRxDisable \
        I2STxRxDisable
#endif
#ifdef ROM_I2STxRxConfigSet
#define MAP_I2STxRxConfigSet \
        ROM_I2STxRxConfigSet
#else
#define MAP_I2STxRxConfigSet \
        I2STxRxConfigSet
#endif
#ifdef ROM_I2SMasterClockSelect
#define MAP_I2SMasterClockSelect \
        ROM_I2SMasterClockSelect
#else
#define MAP_I2SMasterClockSelect \
        I2SMasterClockSelect
#endif
#ifdef ROM_I2SIntEnable
#define MAP_I2SIntEnable \
        ROM_I2SIntEnable
#else
#define MAP_I2SIntEnable \
        I2SIntEnable
#endif
#ifdef ROM_I2SIntDisable
#define MAP_I2SIntDisable \
        ROM_I2SIntDisable
#else
#define MAP_I2SIntDisable \
        I2SIntDisable
#endif
#ifdef ROM_I2SIntClear
#define MAP_I2SIntClear \
        ROM_I2SIntClear
#else
#define MAP_I2SIntClear \
        I2SIntClear
#endif

//*****************************************************************************
//
// Macros for the Interrupt API.
//
//*****************************************************************************
#ifdef ROM_IntEnable
#define MAP_IntEnable \
        ROM_IntEnable
#else
#define MAP_IntEnable \
        IntEnable
#endif
#ifdef ROM_IntMasterEnable
#define MAP_IntMasterEnable \
        ROM_IntMasterEnable
#else
#define MAP_IntMasterEnable \
        IntMasterEnable
#endif
#ifdef ROM_IntMasterDisable
#define MAP_IntMasterDisable \
        ROM_IntMasterDisable
#else
#define MAP_IntMasterDisable \
        IntMasterDisable
#endif
#ifdef ROM_IntDisable
#define MAP_IntDisable \
        ROM_IntDisable
#else
#define MAP_IntDisable \
        IntDisable
#endif
#ifdef ROM_IntPriorityGroupingSet
#define MAP_IntPriorityGroupingSet \
        ROM_IntPriorityGroupingSet
#else
#define MAP_IntPriorityGroupingSet \
        IntPriorityGroupingSet
#endif
#ifdef ROM_IntPriorityGroupingGet
#define MAP_IntPriorityGroupingGet \
        ROM_IntPriorityGroupingGet
#else
#define MAP_IntPriorityGroupingGet \
        IntPriorityGroupingGet
#endif
#ifdef ROM_IntPrioritySet
#define MAP_IntPrioritySet \
        ROM_IntPrioritySet
#else
#define MAP_IntPrioritySet \
        IntPrioritySet
#endif
#ifdef ROM_IntPriorityGet
#define MAP_IntPriorityGet \
        ROM_IntPriorityGet
#else
#define MAP_IntPriorityGet \
        IntPriorityGet
#endif
#ifdef ROM_IntPendSet
#define MAP_IntPendSet \
        ROM_IntPendSet
#else
#define MAP_IntPendSet \
        IntPendSet
#endif
#ifdef ROM_IntPendClear
#define MAP_IntPendClear \
        ROM_IntPendClear
#else
#define MAP_IntPendClear \
        IntPendClear
#endif

//*****************************************************************************
//
// Macros for the MPU API.
//
//*****************************************************************************
#ifdef ROM_MPUEnable
#define MAP_MPUEnable \
        ROM_MPUEnable
#else
#define MAP_MPUEnable \
        MPUEnable
#endif
#ifdef ROM_MPUDisable
#define MAP_MPUDisable \
        ROM_MPUDisable
#else
#define MAP_MPUDisable \
        MPUDisable
#endif
#ifdef ROM_MPURegionCountGet
#define MAP_MPURegionCountGet \
        ROM_MPURegionCountGet
#else
#define MAP_MPURegionCountGet \
        MPURegionCountGet
#endif
#ifdef ROM_MPURegionEnable
#define MAP_MPURegionEnable \
        ROM_MPURegionEnable
#else
#define MAP_MPURegionEnable \
        MPURegionEnable
#endif
#ifdef ROM_MPURegionDisable
#define MAP_MPURegionDisable \
        ROM_MPURegionDisable
#else
#define MAP_MPURegionDisable \
        MPURegionDisable
#endif
#ifdef ROM_MPURegionSet
#define MAP_MPURegionSet \
        ROM_MPURegionSet
#else
#define MAP_MPURegionSet \
        MPURegionSet
#endif
#ifdef ROM_MPURegionGet
#define MAP_MPURegionGet \
        ROM_MPURegionGet
#else
#define MAP_MPURegionGet \
        MPURegionGet
#endif

//*****************************************************************************
//
// Macros for the PWM API.
//
//*****************************************************************************
#ifdef ROM_PWMPulseWidthSet
#define MAP_PWMPulseWidthSet \
        ROM_PWMPulseWidthSet
#else
#define MAP_PWMPulseWidthSet \
        PWMPulseWidthSet
#endif
#ifdef ROM_PWMGenConfigure
#define MAP_PWMGenConfigure \
        ROM_PWMGenConfigure
#else
#define MAP_PWMGenConfigure \
        PWMGenConfigure
#endif
#ifdef ROM_PWMGenPeriodSet
#define MAP_PWMGenPeriodSet \
        ROM_PWMGenPeriodSet
#else
#define MAP_PWMGenPeriodSet \
        PWMGenPeriodSet
#endif
#ifdef ROM_PWMGenPeriodGet
#define MAP_PWMGenPeriodGet \
        ROM_PWMGenPeriodGet
#else
#define MAP_PWMGenPeriodGet \
        PWMGenPeriodGet
#endif
#ifdef ROM_PWMGenEnable
#define MAP_PWMGenEnable \
        ROM_PWMGenEnable
#else
#define MAP_PWMGenEnable \
        PWMGenEnable
#endif
#ifdef ROM_PWMGenDisable
#define MAP_PWMGenDisable \
        ROM_PWMGenDisable
#else
#define MAP_PWMGenDisable \
        PWMGenDisable
#endif
#ifdef ROM_PWMPulseWidthGet
#define MAP_PWMPulseWidthGet \
        ROM_PWMPulseWidthGet
#else
#define MAP_PWMPulseWidthGet \
        PWMPulseWidthGet
#endif
#ifdef ROM_PWMDeadBandEnable
#define MAP_PWMDeadBandEnable \
        ROM_PWMDeadBandEnable
#else
#define MAP_PWMDeadBandEnable \
        PWMDeadBandEnable
#endif
#ifdef ROM_PWMDeadBandDisable
#define MAP_PWMDeadBandDisable \
        ROM_PWMDeadBandDisable
#else
#define MAP_PWMDeadBandDisable \
        PWMDeadBandDisable
#endif
#ifdef ROM_PWMSyncUpdate
#define MAP_PWMSyncUpdate \
        ROM_PWMSyncUpdate
#else
#define MAP_PWMSyncUpdate \
        PWMSyncUpdate
#endif
#ifdef ROM_PWMSyncTimeBase
#define MAP_PWMSyncTimeBase \
        ROM_PWMSyncTimeBase
#else
#define MAP_PWMSyncTimeBase \
        PWMSyncTimeBase
#endif
#ifdef ROM_PWMOutputState
#define MAP_PWMOutputState \
        ROM_PWMOutputState
#else
#define MAP_PWMOutputState \
        PWMOutputState
#endif
#ifdef ROM_PWMOutputInvert
#define MAP_PWMOutputInvert \
        ROM_PWMOutputInvert
#else
#define MAP_PWMOutputInvert \
        PWMOutputInvert
#endif
#ifdef ROM_PWMOutputFault
#define MAP_PWMOutputFault \
        ROM_PWMOutputFault
#else
#define MAP_PWMOutputFault \
        PWMOutputFault
#endif
#ifdef ROM_PWMGenIntTrigEnable
#define MAP_PWMGenIntTrigEnable \
        ROM_PWMGenIntTrigEnable
#else
#define MAP_PWMGenIntTrigEnable \
        PWMGenIntTrigEnable
#endif
#ifdef ROM_PWMGenIntTrigDisable
#define MAP_PWMGenIntTrigDisable \
        ROM_PWMGenIntTrigDisable
#else
#define MAP_PWMGenIntTrigDisable \
        PWMGenIntTrigDisable
#endif
#ifdef ROM_PWMGenIntStatus
#define MAP_PWMGenIntStatus \
        ROM_PWMGenIntStatus
#else
#define MAP_PWMGenIntStatus \
        PWMGenIntStatus
#endif
#ifdef ROM_PWMGenIntClear
#define MAP_PWMGenIntClear \
        ROM_PWMGenIntClear
#else
#define MAP_PWMGenIntClear \
        PWMGenIntClear
#endif
#ifdef ROM_PWMIntEnable
#define MAP_PWMIntEnable \
        ROM_PWMIntEnable
#else
#define MAP_PWMIntEnable \
        PWMIntEnable
#endif
#ifdef ROM_PWMIntDisable
#define MAP_PWMIntDisable \
        ROM_PWMIntDisable
#else
#define MAP_PWMIntDisable \
        PWMIntDisable
#endif
#ifdef ROM_PWMFaultIntClear
#define MAP_PWMFaultIntClear \
        ROM_PWMFaultIntClear
#else
#define MAP_PWMFaultIntClear \
        PWMFaultIntClear
#endif
#ifdef ROM_PWMIntStatus
#define MAP_PWMIntStatus \
        ROM_PWMIntStatus
#else
#define MAP_PWMIntStatus \
        PWMIntStatus
#endif
#ifdef ROM_PWMOutputFaultLevel
#define MAP_PWMOutputFaultLevel \
        ROM_PWMOutputFaultLevel
#else
#define MAP_PWMOutputFaultLevel \
        PWMOutputFaultLevel
#endif
#ifdef ROM_PWMFaultIntClearExt
#define MAP_PWMFaultIntClearExt \
        ROM_PWMFaultIntClearExt
#else
#define MAP_PWMFaultIntClearExt \
        PWMFaultIntClearExt
#endif
#ifdef ROM_PWMGenFaultConfigure
#define MAP_PWMGenFaultConfigure \
        ROM_PWMGenFaultConfigure
#else
#define MAP_PWMGenFaultConfigure \
        PWMGenFaultConfigure
#endif
#ifdef ROM_PWMGenFaultTriggerSet
#define MAP_PWMGenFaultTriggerSet \
        ROM_PWMGenFaultTriggerSet
#else
#define MAP_PWMGenFaultTriggerSet \
        PWMGenFaultTriggerSet
#endif
#ifdef ROM_PWMGenFaultTriggerGet
#define MAP_PWMGenFaultTriggerGet \
        ROM_PWMGenFaultTriggerGet
#else
#define MAP_PWMGenFaultTriggerGet \
        PWMGenFaultTriggerGet
#endif
#ifdef ROM_PWMGenFaultStatus
#define MAP_PWMGenFaultStatus \
        ROM_PWMGenFaultStatus
#else
#define MAP_PWMGenFaultStatus \
        PWMGenFaultStatus
#endif
#ifdef ROM_PWMGenFaultClear
#define MAP_PWMGenFaultClear \
        ROM_PWMGenFaultClear
#else
#define MAP_PWMGenFaultClear \
        PWMGenFaultClear
#endif

//*****************************************************************************
//
// Macros for the QEI API.
//
//*****************************************************************************
#ifdef ROM_QEIPositionGet
#define MAP_QEIPositionGet \
        ROM_QEIPositionGet
#else
#define MAP_QEIPositionGet \
        QEIPositionGet
#endif
#ifdef ROM_QEIEnable
#define MAP_QEIEnable \
        ROM_QEIEnable
#else
#define MAP_QEIEnable \
        QEIEnable
#endif
#ifdef ROM_QEIDisable
#define MAP_QEIDisable \
        ROM_QEIDisable
#else
#define MAP_QEIDisable \
        QEIDisable
#endif
#ifdef ROM_QEIConfigure
#define MAP_QEIConfigure \
        ROM_QEIConfigure
#else
#define MAP_QEIConfigure \
        QEIConfigure
#endif
#ifdef ROM_QEIPositionSet
#define MAP_QEIPositionSet \
        ROM_QEIPositionSet
#else
#define MAP_QEIPositionSet \
        QEIPositionSet
#endif
#ifdef ROM_QEIDirectionGet
#define MAP_QEIDirectionGet \
        ROM_QEIDirectionGet
#else
#define MAP_QEIDirectionGet \
        QEIDirectionGet
#endif
#ifdef ROM_QEIErrorGet
#define MAP_QEIErrorGet \
        ROM_QEIErrorGet
#else
#define MAP_QEIErrorGet \
        QEIErrorGet
#endif
#ifdef ROM_QEIVelocityEnable
#define MAP_QEIVelocityEnable \
        ROM_QEIVelocityEnable
#else
#define MAP_QEIVelocityEnable \
        QEIVelocityEnable
#endif
#ifdef ROM_QEIVelocityDisable
#define MAP_QEIVelocityDisable \
        ROM_QEIVelocityDisable
#else
#define MAP_QEIVelocityDisable \
        QEIVelocityDisable
#endif
#ifdef ROM_QEIVelocityConfigure
#define MAP_QEIVelocityConfigure \
        ROM_QEIVelocityConfigure
#else
#define MAP_QEIVelocityConfigure \
        QEIVelocityConfigure
#endif
#ifdef ROM_QEIVelocityGet
#define MAP_QEIVelocityGet \
        ROM_QEIVelocityGet
#else
#define MAP_QEIVelocityGet \
        QEIVelocityGet
#endif
#ifdef ROM_QEIIntEnable
#define MAP_QEIIntEnable \
        ROM_QEIIntEnable
#else
#define MAP_QEIIntEnable \
        QEIIntEnable
#endif
#ifdef ROM_QEIIntDisable
#define MAP_QEIIntDisable \
        ROM_QEIIntDisable
#else
#define MAP_QEIIntDisable \
        QEIIntDisable
#endif
#ifdef ROM_QEIIntStatus
#define MAP_QEIIntStatus \
        ROM_QEIIntStatus
#else
#define MAP_QEIIntStatus \
        QEIIntStatus
#endif
#ifdef ROM_QEIIntClear
#define MAP_QEIIntClear \
        ROM_QEIIntClear
#else
#define MAP_QEIIntClear \
        QEIIntClear
#endif

//*****************************************************************************
//
// Macros for the SSI API.
//
//*****************************************************************************
#ifdef ROM_SSIDataPut
#define MAP_SSIDataPut \
        ROM_SSIDataPut
#else
#define MAP_SSIDataPut \
        SSIDataPut
#endif
#ifdef ROM_SSIConfigSetExpClk
#define MAP_SSIConfigSetExpClk \
        ROM_SSIConfigSetExpClk
#else
#define MAP_SSIConfigSetExpClk \
        SSIConfigSetExpClk
#endif
#ifdef ROM_SSIEnable
#define MAP_SSIEnable \
        ROM_SSIEnable
#else
#define MAP_SSIEnable \
        SSIEnable
#endif
#ifdef ROM_SSIDisable
#define MAP_SSIDisable \
        ROM_SSIDisable
#else
#define MAP_SSIDisable \
        SSIDisable
#endif
#ifdef ROM_SSIIntEnable
#define MAP_SSIIntEnable \
        ROM_SSIIntEnable
#else
#define MAP_SSIIntEnable \
        SSIIntEnable
#endif
#ifdef ROM_SSIIntDisable
#define MAP_SSIIntDisable \
        ROM_SSIIntDisable
#else
#define MAP_SSIIntDisable \
        SSIIntDisable
#endif
#ifdef ROM_SSIIntStatus
#define MAP_SSIIntStatus \
        ROM_SSIIntStatus
#else
#define MAP_SSIIntStatus \
        SSIIntStatus
#endif
#ifdef ROM_SSIIntClear
#define MAP_SSIIntClear \
        ROM_SSIIntClear
#else
#define MAP_SSIIntClear \
        SSIIntClear
#endif
#ifdef ROM_SSIDataPutNonBlocking
#define MAP_SSIDataPutNonBlocking \
        ROM_SSIDataPutNonBlocking
#else
#define MAP_SSIDataPutNonBlocking \
        SSIDataPutNonBlocking
#endif
#ifdef ROM_SSIDataGet
#define MAP_SSIDataGet \
        ROM_SSIDataGet
#else
#define MAP_SSIDataGet \
        SSIDataGet
#endif
#ifdef ROM_SSIDataGetNonBlocking
#define MAP_SSIDataGetNonBlocking \
        ROM_SSIDataGetNonBlocking
#else
#define MAP_SSIDataGetNonBlocking \
        SSIDataGetNonBlocking
#endif
#ifdef ROM_SSIDMAEnable
#define MAP_SSIDMAEnable \
        ROM_SSIDMAEnable
#else
#define MAP_SSIDMAEnable \
        SSIDMAEnable
#endif
#ifdef ROM_SSIDMADisable
#define MAP_SSIDMADisable \
        ROM_SSIDMADisable
#else
#define MAP_SSIDMADisable \
        SSIDMADisable
#endif
#ifdef ROM_SSIBusy
#define MAP_SSIBusy \
        ROM_SSIBusy
#else
#define MAP_SSIBusy \
        SSIBusy
#endif

//*****************************************************************************
//
// Macros for the SysCtl API.
//
//*****************************************************************************
#ifdef ROM_SysCtlSleep
#define MAP_SysCtlSleep \
        ROM_SysCtlSleep
#else
#define MAP_SysCtlSleep \
        SysCtlSleep
#endif
#ifdef ROM_SysCtlSRAMSizeGet
#define MAP_SysCtlSRAMSizeGet \
        ROM_SysCtlSRAMSizeGet
#else
#define MAP_SysCtlSRAMSizeGet \
        SysCtlSRAMSizeGet
#endif
#ifdef ROM_SysCtlFlashSizeGet
#define MAP_SysCtlFlashSizeGet \
        ROM_SysCtlFlashSizeGet
#else
#define MAP_SysCtlFlashSizeGet \
        SysCtlFlashSizeGet
#endif
#ifdef ROM_SysCtlPinPresent
#define MAP_SysCtlPinPresent \
        ROM_SysCtlPinPresent
#else
#define MAP_SysCtlPinPresent \
        SysCtlPinPresent
#endif
#ifdef ROM_SysCtlPeripheralPresent
#define MAP_SysCtlPeripheralPresent \
        ROM_SysCtlPeripheralPresent
#else
#define MAP_SysCtlPeripheralPresent \
        SysCtlPeripheralPresent
#endif
#ifdef ROM_SysCtlPeripheralReset
#define MAP_SysCtlPeripheralReset \
        ROM_SysCtlPeripheralReset
#else
#define MAP_SysCtlPeripheralReset \
        SysCtlPeripheralReset
#endif
#ifdef ROM_SysCtlPeripheralEnable
#define MAP_SysCtlPeripheralEnable \
        ROM_SysCtlPeripheralEnable
#else
#define MAP_SysCtlPeripheralEnable \
        SysCtlPeripheralEnable
#endif
#ifdef ROM_SysCtlPeripheralDisable
#define MAP_SysCtlPeripheralDisable \
        ROM_SysCtlPeripheralDisable
#else
#define MAP_SysCtlPeripheralDisable \
        SysCtlPeripheralDisable
#endif
#ifdef ROM_SysCtlPeripheralSleepEnable
#define MAP_SysCtlPeripheralSleepEnable \
        ROM_SysCtlPeripheralSleepEnable
#else
#define MAP_SysCtlPeripheralSleepEnable \
        SysCtlPeripheralSleepEnable
#endif
#ifdef ROM_SysCtlPeripheralSleepDisable
#define MAP_SysCtlPeripheralSleepDisable \
        ROM_SysCtlPeripheralSleepDisable
#else
#define MAP_SysCtlPeripheralSleepDisable \
        SysCtlPeripheralSleepDisable
#endif
#ifdef ROM_SysCtlPeripheralDeepSleepEnable
#define MAP_SysCtlPeripheralDeepSleepEnable \
        ROM_SysCtlPeripheralDeepSleepEnable
#else
#define MAP_SysCtlPeripheralDeepSleepEnable \
        SysCtlPeripheralDeepSleepEnable
#endif
#ifdef ROM_SysCtlPeripheralDeepSleepDisable
#define MAP_SysCtlPeripheralDeepSleepDisable \
        ROM_SysCtlPeripheralDeepSleepDisable
#else
#define MAP_SysCtlPeripheralDeepSleepDisable \
        SysCtlPeripheralDeepSleepDisable
#endif
#ifdef ROM_SysCtlPeripheralClockGating
#define MAP_SysCtlPeripheralClockGating \
        ROM_SysCtlPeripheralClockGating
#else
#define MAP_SysCtlPeripheralClockGating \
        SysCtlPeripheralClockGating
#endif
#ifdef ROM_SysCtlIntEnable
#define MAP_SysCtlIntEnable \
        ROM_SysCtlIntEnable
#else
#define MAP_SysCtlIntEnable \
        SysCtlIntEnable
#endif
#ifdef ROM_SysCtlIntDisable
#define MAP_SysCtlIntDisable \
        ROM_SysCtlIntDisable
#else
#define MAP_SysCtlIntDisable \
        SysCtlIntDisable
#endif
#ifdef ROM_SysCtlIntClear
#define MAP_SysCtlIntClear \
        ROM_SysCtlIntClear
#else
#define MAP_SysCtlIntClear \
        SysCtlIntClear
#endif
#ifdef ROM_SysCtlIntStatus
#define MAP_SysCtlIntStatus \
        ROM_SysCtlIntStatus
#else
#define MAP_SysCtlIntStatus \
        SysCtlIntStatus
#endif
#ifdef ROM_SysCtlLDOSet
#define MAP_SysCtlLDOSet \
        ROM_SysCtlLDOSet
#else
#define MAP_SysCtlLDOSet \
        SysCtlLDOSet
#endif
#ifdef ROM_SysCtlLDOGet
#define MAP_SysCtlLDOGet \
        ROM_SysCtlLDOGet
#else
#define MAP_SysCtlLDOGet \
        SysCtlLDOGet
#endif
#ifdef ROM_SysCtlReset
#define MAP_SysCtlReset \
        ROM_SysCtlReset
#else
#define MAP_SysCtlReset \
        SysCtlReset
#endif
#ifdef ROM_SysCtlDeepSleep
#define MAP_SysCtlDeepSleep \
        ROM_SysCtlDeepSleep
#else
#define MAP_SysCtlDeepSleep \
        SysCtlDeepSleep
#endif
#ifdef ROM_SysCtlResetCauseGet
#define MAP_SysCtlResetCauseGet \
        ROM_SysCtlResetCauseGet
#else
#define MAP_SysCtlResetCauseGet \
        SysCtlResetCauseGet
#endif
#ifdef ROM_SysCtlResetCauseClear
#define MAP_SysCtlResetCauseClear \
        ROM_SysCtlResetCauseClear
#else
#define MAP_SysCtlResetCauseClear \
        SysCtlResetCauseClear
#endif
#ifdef ROM_SysCtlClockSet
#define MAP_SysCtlClockSet \
        ROM_SysCtlClockSet
#else
#define MAP_SysCtlClockSet \
        SysCtlClockSet
#endif
#ifdef ROM_SysCtlClockGet
#define MAP_SysCtlClockGet \
        ROM_SysCtlClockGet
#else
#define MAP_SysCtlClockGet \
        SysCtlClockGet
#endif
#ifdef ROM_SysCtlPWMClockSet
#define MAP_SysCtlPWMClockSet \
        ROM_SysCtlPWMClockSet
#else
#define MAP_SysCtlPWMClockSet \
        SysCtlPWMClockSet
#endif
#ifdef ROM_SysCtlPWMClockGet
#define MAP_SysCtlPWMClockGet \
        ROM_SysCtlPWMClockGet
#else
#define MAP_SysCtlPWMClockGet \
        SysCtlPWMClockGet
#endif
#ifdef ROM_SysCtlADCSpeedSet
#define MAP_SysCtlADCSpeedSet \
        ROM_SysCtlADCSpeedSet
#else
#define MAP_SysCtlADCSpeedSet \
        SysCtlADCSpeedSet
#endif
#ifdef ROM_SysCtlADCSpeedGet
#define MAP_SysCtlADCSpeedGet \
        ROM_SysCtlADCSpeedGet
#else
#define MAP_SysCtlADCSpeedGet \
        SysCtlADCSpeedGet
#endif
#ifdef ROM_SysCtlGPIOAHBEnable
#define MAP_SysCtlGPIOAHBEnable \
        ROM_SysCtlGPIOAHBEnable
#else
#define MAP_SysCtlGPIOAHBEnable \
        SysCtlGPIOAHBEnable
#endif
#ifdef ROM_SysCtlGPIOAHBDisable
#define MAP_SysCtlGPIOAHBDisable \
        ROM_SysCtlGPIOAHBDisable
#else
#define MAP_SysCtlGPIOAHBDisable \
        SysCtlGPIOAHBDisable
#endif
#ifdef ROM_SysCtlUSBPLLEnable
#define MAP_SysCtlUSBPLLEnable \
        ROM_SysCtlUSBPLLEnable
#else
#define MAP_SysCtlUSBPLLEnable \
        SysCtlUSBPLLEnable
#endif
#ifdef ROM_SysCtlUSBPLLDisable
#define MAP_SysCtlUSBPLLDisable \
        ROM_SysCtlUSBPLLDisable
#else
#define MAP_SysCtlUSBPLLDisable \
        SysCtlUSBPLLDisable
#endif
#ifdef ROM_SysCtlI2SMClkSet
#define MAP_SysCtlI2SMClkSet \
        ROM_SysCtlI2SMClkSet
#else
#define MAP_SysCtlI2SMClkSet \
        SysCtlI2SMClkSet
#endif
#ifdef ROM_SysCtlDelay
#define MAP_SysCtlDelay \
        ROM_SysCtlDelay
#else
#define MAP_SysCtlDelay \
        SysCtlDelay
#endif

//*****************************************************************************
//
// Macros for the SysTick API.
//
//*****************************************************************************
#ifdef ROM_SysTickValueGet
#define MAP_SysTickValueGet \
        ROM_SysTickValueGet
#else
#define MAP_SysTickValueGet \
        SysTickValueGet
#endif
#ifdef ROM_SysTickEnable
#define MAP_SysTickEnable \
        ROM_SysTickEnable
#else
#define MAP_SysTickEnable \
        SysTickEnable
#endif
#ifdef ROM_SysTickDisable
#define MAP_SysTickDisable \
        ROM_SysTickDisable
#else
#define MAP_SysTickDisable \
        SysTickDisable
#endif
#ifdef ROM_SysTickIntEnable
#define MAP_SysTickIntEnable \
        ROM_SysTickIntEnable
#else
#define MAP_SysTickIntEnable \
        SysTickIntEnable
#endif
#ifdef ROM_SysTickIntDisable
#define MAP_SysTickIntDisable \
        ROM_SysTickIntDisable
#else
#define MAP_SysTickIntDisable \
        SysTickIntDisable
#endif
#ifdef ROM_SysTickPeriodSet
#define MAP_SysTickPeriodSet \
        ROM_SysTickPeriodSet
#else
#define MAP_SysTickPeriodSet \
        SysTickPeriodSet
#endif
#ifdef ROM_SysTickPeriodGet
#define MAP_SysTickPeriodGet \
        ROM_SysTickPeriodGet
#else
#define MAP_SysTickPeriodGet \
        SysTickPeriodGet
#endif

//*****************************************************************************
//
// Macros for the Timer API.
//
//*****************************************************************************
#ifdef ROM_TimerIntClear
#define MAP_TimerIntClear \
        ROM_TimerIntClear
#else
#define MAP_TimerIntClear \
        TimerIntClear
#endif
#ifdef ROM_TimerEnable
#define MAP_TimerEnable \
        ROM_TimerEnable
#else
#define MAP_TimerEnable \
        TimerEnable
#endif
#ifdef ROM_TimerDisable
#define MAP_TimerDisable \
        ROM_TimerDisable
#else
#define MAP_TimerDisable \
        TimerDisable
#endif
#ifdef ROM_TimerConfigure
#define MAP_TimerConfigure \
        ROM_TimerConfigure
#else
#define MAP_TimerConfigure \
        TimerConfigure
#endif
#ifdef ROM_TimerControlLevel
#define MAP_TimerControlLevel \
        ROM_TimerControlLevel
#else
#define MAP_TimerControlLevel \
        TimerControlLevel
#endif
#ifdef ROM_TimerControlTrigger
#define MAP_TimerControlTrigger \
        ROM_TimerControlTrigger
#else
#define MAP_TimerControlTrigger \
        TimerControlTrigger
#endif
#ifdef ROM_TimerControlEvent
#define MAP_TimerControlEvent \
        ROM_TimerControlEvent
#else
#define MAP_TimerControlEvent \
        TimerControlEvent
#endif
#ifdef ROM_TimerControlStall
#define MAP_TimerControlStall \
        ROM_TimerControlStall
#else
#define MAP_TimerControlStall \
        TimerControlStall
#endif
#ifdef ROM_TimerRTCEnable
#define MAP_TimerRTCEnable \
        ROM_TimerRTCEnable
#else
#define MAP_TimerRTCEnable \
        TimerRTCEnable
#endif
#ifdef ROM_TimerRTCDisable
#define MAP_TimerRTCDisable \
        ROM_TimerRTCDisable
#else
#define MAP_TimerRTCDisable \
        TimerRTCDisable
#endif
#ifdef ROM_TimerPrescaleSet
#define MAP_TimerPrescaleSet \
        ROM_TimerPrescaleSet
#else
#define MAP_TimerPrescaleSet \
        TimerPrescaleSet
#endif
#ifdef ROM_TimerPrescaleGet
#define MAP_TimerPrescaleGet \
        ROM_TimerPrescaleGet
#else
#define MAP_TimerPrescaleGet \
        TimerPrescaleGet
#endif
#ifdef ROM_TimerLoadSet
#define MAP_TimerLoadSet \
        ROM_TimerLoadSet
#else
#define MAP_TimerLoadSet \
        TimerLoadSet
#endif
#ifdef ROM_TimerLoadGet
#define MAP_TimerLoadGet \
        ROM_TimerLoadGet
#else
#define MAP_TimerLoadGet \
        TimerLoadGet
#endif
#ifdef ROM_TimerValueGet
#define MAP_TimerValueGet \
        ROM_TimerValueGet
#else
#define MAP_TimerValueGet \
        TimerValueGet
#endif
#ifdef ROM_TimerMatchSet
#define MAP_TimerMatchSet \
        ROM_TimerMatchSet
#else
#define MAP_TimerMatchSet \
        TimerMatchSet
#endif
#ifdef ROM_TimerMatchGet
#define MAP_TimerMatchGet \
        ROM_TimerMatchGet
#else
#define MAP_TimerMatchGet \
        TimerMatchGet
#endif
#ifdef ROM_TimerIntEnable
#define MAP_TimerIntEnable \
        ROM_TimerIntEnable
#else
#define MAP_TimerIntEnable \
        TimerIntEnable
#endif
#ifdef ROM_TimerIntDisable
#define MAP_TimerIntDisable \
        ROM_TimerIntDisable
#else
#define MAP_TimerIntDisable \
        TimerIntDisable
#endif
#ifdef ROM_TimerIntStatus
#define MAP_TimerIntStatus \
        ROM_TimerIntStatus
#else
#define MAP_TimerIntStatus \
        TimerIntStatus
#endif

//*****************************************************************************
//
// Macros for the UART API.
//
//*****************************************************************************
#ifdef ROM_UARTCharPut
#define MAP_UARTCharPut \
        ROM_UARTCharPut
#else
#define MAP_UARTCharPut \
        UARTCharPut
#endif
#ifdef ROM_UARTParityModeSet
#define MAP_UARTParityModeSet \
        ROM_UARTParityModeSet
#else
#define MAP_UARTParityModeSet \
        UARTParityModeSet
#endif
#ifdef ROM_UARTParityModeGet
#define MAP_UARTParityModeGet \
        ROM_UARTParityModeGet
#else
#define MAP_UARTParityModeGet \
        UARTParityModeGet
#endif
#ifdef ROM_UARTFIFOLevelSet
#define MAP_UARTFIFOLevelSet \
        ROM_UARTFIFOLevelSet
#else
#define MAP_UARTFIFOLevelSet \
        UARTFIFOLevelSet
#endif
#ifdef ROM_UARTFIFOLevelGet
#define MAP_UARTFIFOLevelGet \
        ROM_UARTFIFOLevelGet
#else
#define MAP_UARTFIFOLevelGet \
        UARTFIFOLevelGet
#endif
#ifdef ROM_UARTConfigSetExpClk
#define MAP_UARTConfigSetExpClk \
        ROM_UARTConfigSetExpClk
#else
#define MAP_UARTConfigSetExpClk \
        UARTConfigSetExpClk
#endif
#ifdef ROM_UARTConfigGetExpClk
#define MAP_UARTConfigGetExpClk \
        ROM_UARTConfigGetExpClk
#else
#define MAP_UARTConfigGetExpClk \
        UARTConfigGetExpClk
#endif
#ifdef ROM_UARTEnable
#define MAP_UARTEnable \
        ROM_UARTEnable
#else
#define MAP_UARTEnable \
        UARTEnable
#endif
#ifdef ROM_UARTDisable
#define MAP_UARTDisable \
        ROM_UARTDisable
#else
#define MAP_UARTDisable \
        UARTDisable
#endif
#ifdef ROM_UARTEnableSIR
#define MAP_UARTEnableSIR \
        ROM_UARTEnableSIR
#else
#define MAP_UARTEnableSIR \
        UARTEnableSIR
#endif
#ifdef ROM_UARTDisableSIR
#define MAP_UARTDisableSIR \
        ROM_UARTDisableSIR
#else
#define MAP_UARTDisableSIR \
        UARTDisableSIR
#endif
#ifdef ROM_UARTCharsAvail
#define MAP_UARTCharsAvail \
        ROM_UARTCharsAvail
#else
#define MAP_UARTCharsAvail \
        UARTCharsAvail
#endif
#ifdef ROM_UARTSpaceAvail
#define MAP_UARTSpaceAvail \
        ROM_UARTSpaceAvail
#else
#define MAP_UARTSpaceAvail \
        UARTSpaceAvail
#endif
#ifdef ROM_UARTCharGetNonBlocking
#define MAP_UARTCharGetNonBlocking \
        ROM_UARTCharGetNonBlocking
#else
#define MAP_UARTCharGetNonBlocking \
        UARTCharGetNonBlocking
#endif
#ifdef ROM_UARTCharGet
#define MAP_UARTCharGet \
        ROM_UARTCharGet
#else
#define MAP_UARTCharGet \
        UARTCharGet
#endif
#ifdef ROM_UARTCharPutNonBlocking
#define MAP_UARTCharPutNonBlocking \
        ROM_UARTCharPutNonBlocking
#else
#define MAP_UARTCharPutNonBlocking \
        UARTCharPutNonBlocking
#endif
#ifdef ROM_UARTBreakCtl
#define MAP_UARTBreakCtl \
        ROM_UARTBreakCtl
#else
#define MAP_UARTBreakCtl \
        UARTBreakCtl
#endif
#ifdef ROM_UARTIntEnable
#define MAP_UARTIntEnable \
        ROM_UARTIntEnable
#else
#define MAP_UARTIntEnable \
        UARTIntEnable
#endif
#ifdef ROM_UARTIntDisable
#define MAP_UARTIntDisable \
        ROM_UARTIntDisable
#else
#define MAP_UARTIntDisable \
        UARTIntDisable
#endif
#ifdef ROM_UARTIntStatus
#define MAP_UARTIntStatus \
        ROM_UARTIntStatus
#else
#define MAP_UARTIntStatus \
        UARTIntStatus
#endif
#ifdef ROM_UARTIntClear
#define MAP_UARTIntClear \
        ROM_UARTIntClear
#else
#define MAP_UARTIntClear \
        UARTIntClear
#endif
#ifdef ROM_UARTDMAEnable
#define MAP_UARTDMAEnable \
        ROM_UARTDMAEnable
#else
#define MAP_UARTDMAEnable \
        UARTDMAEnable
#endif
#ifdef ROM_UARTDMADisable
#define MAP_UARTDMADisable \
        ROM_UARTDMADisable
#else
#define MAP_UARTDMADisable \
        UARTDMADisable
#endif
#ifdef ROM_UARTFIFOEnable
#define MAP_UARTFIFOEnable \
        ROM_UARTFIFOEnable
#else
#define MAP_UARTFIFOEnable \
        UARTFIFOEnable
#endif
#ifdef ROM_UARTFIFODisable
#define MAP_UARTFIFODisable \
        ROM_UARTFIFODisable
#else
#define MAP_UARTFIFODisable \
        UARTFIFODisable
#endif
#ifdef ROM_UARTBusy
#define MAP_UARTBusy \
        ROM_UARTBusy
#else
#define MAP_UARTBusy \
        UARTBusy
#endif
#ifdef ROM_UARTTxIntModeSet
#define MAP_UARTTxIntModeSet \
        ROM_UARTTxIntModeSet
#else
#define MAP_UARTTxIntModeSet \
        UARTTxIntModeSet
#endif
#ifdef ROM_UARTTxIntModeGet
#define MAP_UARTTxIntModeGet \
        ROM_UARTTxIntModeGet
#else
#define MAP_UARTTxIntModeGet \
        UARTTxIntModeGet
#endif
#ifdef ROM_UARTRxErrorGet
#define MAP_UARTRxErrorGet \
        ROM_UARTRxErrorGet
#else
#define MAP_UARTRxErrorGet \
        UARTRxErrorGet
#endif
#ifdef ROM_UARTRxErrorClear
#define MAP_UARTRxErrorClear \
        ROM_UARTRxErrorClear
#else
#define MAP_UARTRxErrorClear \
        UARTRxErrorClear
#endif

//*****************************************************************************
//
// Macros for the uDMA API.
//
//*****************************************************************************
#ifdef ROM_uDMAChannelTransferSet
#define MAP_uDMAChannelTransferSet \
        ROM_uDMAChannelTransferSet
#else
#define MAP_uDMAChannelTransferSet \
        uDMAChannelTransferSet
#endif
#ifdef ROM_uDMAEnable
#define MAP_uDMAEnable \
        ROM_uDMAEnable
#else
#define MAP_uDMAEnable \
        uDMAEnable
#endif
#ifdef ROM_uDMADisable
#define MAP_uDMADisable \
        ROM_uDMADisable
#else
#define MAP_uDMADisable \
        uDMADisable
#endif
#ifdef ROM_uDMAErrorStatusGet
#define MAP_uDMAErrorStatusGet \
        ROM_uDMAErrorStatusGet
#else
#define MAP_uDMAErrorStatusGet \
        uDMAErrorStatusGet
#endif
#ifdef ROM_uDMAErrorStatusClear
#define MAP_uDMAErrorStatusClear \
        ROM_uDMAErrorStatusClear
#else
#define MAP_uDMAErrorStatusClear \
        uDMAErrorStatusClear
#endif
#ifdef ROM_uDMAChannelEnable
#define MAP_uDMAChannelEnable \
        ROM_uDMAChannelEnable
#else
#define MAP_uDMAChannelEnable \
        uDMAChannelEnable
#endif
#ifdef ROM_uDMAChannelDisable
#define MAP_uDMAChannelDisable \
        ROM_uDMAChannelDisable
#else
#define MAP_uDMAChannelDisable \
        uDMAChannelDisable
#endif
#ifdef ROM_uDMAChannelIsEnabled
#define MAP_uDMAChannelIsEnabled \
        ROM_uDMAChannelIsEnabled
#else
#define MAP_uDMAChannelIsEnabled \
        uDMAChannelIsEnabled
#endif
#ifdef ROM_uDMAControlBaseSet
#define MAP_uDMAControlBaseSet \
        ROM_uDMAControlBaseSet
#else
#define MAP_uDMAControlBaseSet \
        uDMAControlBaseSet
#endif
#ifdef ROM_uDMAControlBaseGet
#define MAP_uDMAControlBaseGet \
        ROM_uDMAControlBaseGet
#else
#define MAP_uDMAControlBaseGet \
        uDMAControlBaseGet
#endif
#ifdef ROM_uDMAChannelRequest
#define MAP_uDMAChannelRequest \
        ROM_uDMAChannelRequest
#else
#define MAP_uDMAChannelRequest \
        uDMAChannelRequest
#endif
#ifdef ROM_uDMAChannelAttributeEnable
#define MAP_uDMAChannelAttributeEnable \
        ROM_uDMAChannelAttributeEnable
#else
#define MAP_uDMAChannelAttributeEnable \
        uDMAChannelAttributeEnable
#endif
#ifdef ROM_uDMAChannelAttributeDisable
#define MAP_uDMAChannelAttributeDisable \
        ROM_uDMAChannelAttributeDisable
#else
#define MAP_uDMAChannelAttributeDisable \
        uDMAChannelAttributeDisable
#endif
#ifdef ROM_uDMAChannelAttributeGet
#define MAP_uDMAChannelAttributeGet \
        ROM_uDMAChannelAttributeGet
#else
#define MAP_uDMAChannelAttributeGet \
        uDMAChannelAttributeGet
#endif
#ifdef ROM_uDMAChannelControlSet
#define MAP_uDMAChannelControlSet \
        ROM_uDMAChannelControlSet
#else
#define MAP_uDMAChannelControlSet \
        uDMAChannelControlSet
#endif
#ifdef ROM_uDMAChannelSizeGet
#define MAP_uDMAChannelSizeGet \
        ROM_uDMAChannelSizeGet
#else
#define MAP_uDMAChannelSizeGet \
        uDMAChannelSizeGet
#endif
#ifdef ROM_uDMAChannelModeGet
#define MAP_uDMAChannelModeGet \
        ROM_uDMAChannelModeGet
#else
#define MAP_uDMAChannelModeGet \
        uDMAChannelModeGet
#endif
#ifdef ROM_uDMAChannelSelectSecondary
#define MAP_uDMAChannelSelectSecondary \
        ROM_uDMAChannelSelectSecondary
#else
#define MAP_uDMAChannelSelectSecondary \
        uDMAChannelSelectSecondary
#endif
#ifdef ROM_uDMAChannelSelectDefault
#define MAP_uDMAChannelSelectDefault \
        ROM_uDMAChannelSelectDefault
#else
#define MAP_uDMAChannelSelectDefault \
        uDMAChannelSelectDefault
#endif

//*****************************************************************************
//
// Macros for the USB API.
//
//*****************************************************************************
#ifdef ROM_USBIntStatus
#define MAP_USBIntStatus \
        ROM_USBIntStatus
#else
#define MAP_USBIntStatus \
        USBIntStatus
#endif
#ifdef ROM_USBDevAddrGet
#define MAP_USBDevAddrGet \
        ROM_USBDevAddrGet
#else
#define MAP_USBDevAddrGet \
        USBDevAddrGet
#endif
#ifdef ROM_USBDevAddrSet
#define MAP_USBDevAddrSet \
        ROM_USBDevAddrSet
#else
#define MAP_USBDevAddrSet \
        USBDevAddrSet
#endif
#ifdef ROM_USBDevConnect
#define MAP_USBDevConnect \
        ROM_USBDevConnect
#else
#define MAP_USBDevConnect \
        USBDevConnect
#endif
#ifdef ROM_USBDevDisconnect
#define MAP_USBDevDisconnect \
        ROM_USBDevDisconnect
#else
#define MAP_USBDevDisconnect \
        USBDevDisconnect
#endif
#ifdef ROM_USBDevEndpointConfigSet
#define MAP_USBDevEndpointConfigSet \
        ROM_USBDevEndpointConfigSet
#else
#define MAP_USBDevEndpointConfigSet \
        USBDevEndpointConfigSet
#endif
#ifdef ROM_USBDevEndpointDataAck
#define MAP_USBDevEndpointDataAck \
        ROM_USBDevEndpointDataAck
#else
#define MAP_USBDevEndpointDataAck \
        USBDevEndpointDataAck
#endif
#ifdef ROM_USBDevEndpointStall
#define MAP_USBDevEndpointStall \
        ROM_USBDevEndpointStall
#else
#define MAP_USBDevEndpointStall \
        USBDevEndpointStall
#endif
#ifdef ROM_USBDevEndpointStallClear
#define MAP_USBDevEndpointStallClear \
        ROM_USBDevEndpointStallClear
#else
#define MAP_USBDevEndpointStallClear \
        USBDevEndpointStallClear
#endif
#ifdef ROM_USBDevEndpointStatusClear
#define MAP_USBDevEndpointStatusClear \
        ROM_USBDevEndpointStatusClear
#else
#define MAP_USBDevEndpointStatusClear \
        USBDevEndpointStatusClear
#endif
#ifdef ROM_USBEndpointDataGet
#define MAP_USBEndpointDataGet \
        ROM_USBEndpointDataGet
#else
#define MAP_USBEndpointDataGet \
        USBEndpointDataGet
#endif
#ifdef ROM_USBEndpointDataPut
#define MAP_USBEndpointDataPut \
        ROM_USBEndpointDataPut
#else
#define MAP_USBEndpointDataPut \
        USBEndpointDataPut
#endif
#ifdef ROM_USBEndpointDataSend
#define MAP_USBEndpointDataSend \
        ROM_USBEndpointDataSend
#else
#define MAP_USBEndpointDataSend \
        USBEndpointDataSend
#endif
#ifdef ROM_USBEndpointDataToggleClear
#define MAP_USBEndpointDataToggleClear \
        ROM_USBEndpointDataToggleClear
#else
#define MAP_USBEndpointDataToggleClear \
        USBEndpointDataToggleClear
#endif
#ifdef ROM_USBEndpointStatus
#define MAP_USBEndpointStatus \
        ROM_USBEndpointStatus
#else
#define MAP_USBEndpointStatus \
        USBEndpointStatus
#endif
#ifdef ROM_USBFIFOAddrGet
#define MAP_USBFIFOAddrGet \
        ROM_USBFIFOAddrGet
#else
#define MAP_USBFIFOAddrGet \
        USBFIFOAddrGet
#endif
#ifdef ROM_USBFIFOConfigGet
#define MAP_USBFIFOConfigGet \
        ROM_USBFIFOConfigGet
#else
#define MAP_USBFIFOConfigGet \
        USBFIFOConfigGet
#endif
#ifdef ROM_USBFIFOConfigSet
#define MAP_USBFIFOConfigSet \
        ROM_USBFIFOConfigSet
#else
#define MAP_USBFIFOConfigSet \
        USBFIFOConfigSet
#endif
#ifdef ROM_USBFIFOFlush
#define MAP_USBFIFOFlush \
        ROM_USBFIFOFlush
#else
#define MAP_USBFIFOFlush \
        USBFIFOFlush
#endif
#ifdef ROM_USBFrameNumberGet
#define MAP_USBFrameNumberGet \
        ROM_USBFrameNumberGet
#else
#define MAP_USBFrameNumberGet \
        USBFrameNumberGet
#endif
#ifdef ROM_USBHostAddrGet
#define MAP_USBHostAddrGet \
        ROM_USBHostAddrGet
#else
#define MAP_USBHostAddrGet \
        USBHostAddrGet
#endif
#ifdef ROM_USBHostAddrSet
#define MAP_USBHostAddrSet \
        ROM_USBHostAddrSet
#else
#define MAP_USBHostAddrSet \
        USBHostAddrSet
#endif
#ifdef ROM_USBHostEndpointConfig
#define MAP_USBHostEndpointConfig \
        ROM_USBHostEndpointConfig
#else
#define MAP_USBHostEndpointConfig \
        USBHostEndpointConfig
#endif
#ifdef ROM_USBHostEndpointDataAck
#define MAP_USBHostEndpointDataAck \
        ROM_USBHostEndpointDataAck
#else
#define MAP_USBHostEndpointDataAck \
        USBHostEndpointDataAck
#endif
#ifdef ROM_USBHostEndpointDataToggle
#define MAP_USBHostEndpointDataToggle \
        ROM_USBHostEndpointDataToggle
#else
#define MAP_USBHostEndpointDataToggle \
        USBHostEndpointDataToggle
#endif
#ifdef ROM_USBHostEndpointStatusClear
#define MAP_USBHostEndpointStatusClear \
        ROM_USBHostEndpointStatusClear
#else
#define MAP_USBHostEndpointStatusClear \
        USBHostEndpointStatusClear
#endif
#ifdef ROM_USBHostHubAddrGet
#define MAP_USBHostHubAddrGet \
        ROM_USBHostHubAddrGet
#else
#define MAP_USBHostHubAddrGet \
        USBHostHubAddrGet
#endif
#ifdef ROM_USBHostHubAddrSet
#define MAP_USBHostHubAddrSet \
        ROM_USBHostHubAddrSet
#else
#define MAP_USBHostHubAddrSet \
        USBHostHubAddrSet
#endif
#ifdef ROM_USBHostPwrDisable
#define MAP_USBHostPwrDisable \
        ROM_USBHostPwrDisable
#else
#define MAP_USBHostPwrDisable \
        USBHostPwrDisable
#endif
#ifdef ROM_USBHostPwrEnable
#define MAP_USBHostPwrEnable \
        ROM_USBHostPwrEnable
#else
#define MAP_USBHostPwrEnable \
        USBHostPwrEnable
#endif
#ifdef ROM_USBHostPwrConfig
#define MAP_USBHostPwrConfig \
        ROM_USBHostPwrConfig
#else
#define MAP_USBHostPwrConfig \
        USBHostPwrConfig
#endif
#ifdef ROM_USBHostPwrFaultDisable
#define MAP_USBHostPwrFaultDisable \
        ROM_USBHostPwrFaultDisable
#else
#define MAP_USBHostPwrFaultDisable \
        USBHostPwrFaultDisable
#endif
#ifdef ROM_USBHostPwrFaultEnable
#define MAP_USBHostPwrFaultEnable \
        ROM_USBHostPwrFaultEnable
#else
#define MAP_USBHostPwrFaultEnable \
        USBHostPwrFaultEnable
#endif
#ifdef ROM_USBHostRequestIN
#define MAP_USBHostRequestIN \
        ROM_USBHostRequestIN
#else
#define MAP_USBHostRequestIN \
        USBHostRequestIN
#endif
#ifdef ROM_USBHostRequestStatus
#define MAP_USBHostRequestStatus \
        ROM_USBHostRequestStatus
#else
#define MAP_USBHostRequestStatus \
        USBHostRequestStatus
#endif
#ifdef ROM_USBHostReset
#define MAP_USBHostReset \
        ROM_USBHostReset
#else
#define MAP_USBHostReset \
        USBHostReset
#endif
#ifdef ROM_USBHostResume
#define MAP_USBHostResume \
        ROM_USBHostResume
#else
#define MAP_USBHostResume \
        USBHostResume
#endif
#ifdef ROM_USBHostSpeedGet
#define MAP_USBHostSpeedGet \
        ROM_USBHostSpeedGet
#else
#define MAP_USBHostSpeedGet \
        USBHostSpeedGet
#endif
#ifdef ROM_USBHostSuspend
#define MAP_USBHostSuspend \
        ROM_USBHostSuspend
#else
#define MAP_USBHostSuspend \
        USBHostSuspend
#endif
#ifdef ROM_USBIntDisable
#define MAP_USBIntDisable \
        ROM_USBIntDisable
#else
#define MAP_USBIntDisable \
        USBIntDisable
#endif
#ifdef ROM_USBIntEnable
#define MAP_USBIntEnable \
        ROM_USBIntEnable
#else
#define MAP_USBIntEnable \
        USBIntEnable
#endif
#ifdef ROM_USBDevEndpointConfigGet
#define MAP_USBDevEndpointConfigGet \
        ROM_USBDevEndpointConfigGet
#else
#define MAP_USBDevEndpointConfigGet \
        USBDevEndpointConfigGet
#endif
#ifdef ROM_USBEndpointDMAEnable
#define MAP_USBEndpointDMAEnable \
        ROM_USBEndpointDMAEnable
#else
#define MAP_USBEndpointDMAEnable \
        USBEndpointDMAEnable
#endif
#ifdef ROM_USBEndpointDMADisable
#define MAP_USBEndpointDMADisable \
        ROM_USBEndpointDMADisable
#else
#define MAP_USBEndpointDMADisable \
        USBEndpointDMADisable
#endif
#ifdef ROM_USBEndpointDataAvail
#define MAP_USBEndpointDataAvail \
        ROM_USBEndpointDataAvail
#else
#define MAP_USBEndpointDataAvail \
        USBEndpointDataAvail
#endif
#ifdef ROM_USBOTGHostRequest
#define MAP_USBOTGHostRequest \
        ROM_USBOTGHostRequest
#else
#define MAP_USBOTGHostRequest \
        USBOTGHostRequest
#endif
#ifdef ROM_USBModeGet
#define MAP_USBModeGet \
        ROM_USBModeGet
#else
#define MAP_USBModeGet \
        USBModeGet
#endif
#ifdef ROM_USBEndpointDMAChannel
#define MAP_USBEndpointDMAChannel \
        ROM_USBEndpointDMAChannel
#else
#define MAP_USBEndpointDMAChannel \
        USBEndpointDMAChannel
#endif
#ifdef ROM_USBIntDisableControl
#define MAP_USBIntDisableControl \
        ROM_USBIntDisableControl
#else
#define MAP_USBIntDisableControl \
        USBIntDisableControl
#endif
#ifdef ROM_USBIntEnableControl
#define MAP_USBIntEnableControl \
        ROM_USBIntEnableControl
#else
#define MAP_USBIntEnableControl \
        USBIntEnableControl
#endif
#ifdef ROM_USBIntStatusControl
#define MAP_USBIntStatusControl \
        ROM_USBIntStatusControl
#else
#define MAP_USBIntStatusControl \
        USBIntStatusControl
#endif
#ifdef ROM_USBIntDisableEndpoint
#define MAP_USBIntDisableEndpoint \
        ROM_USBIntDisableEndpoint
#else
#define MAP_USBIntDisableEndpoint \
        USBIntDisableEndpoint
#endif
#ifdef ROM_USBIntEnableEndpoint
#define MAP_USBIntEnableEndpoint \
        ROM_USBIntEnableEndpoint
#else
#define MAP_USBIntEnableEndpoint \
        USBIntEnableEndpoint
#endif
#ifdef ROM_USBIntStatusEndpoint
#define MAP_USBIntStatusEndpoint \
        ROM_USBIntStatusEndpoint
#else
#define MAP_USBIntStatusEndpoint \
        USBIntStatusEndpoint
#endif
#ifdef ROM_USBHostMode
#define MAP_USBHostMode \
        ROM_USBHostMode
#else
#define MAP_USBHostMode \
        USBHostMode
#endif

//*****************************************************************************
//
// Macros for the Watchdog API.
//
//*****************************************************************************
#ifdef ROM_WatchdogIntClear
#define MAP_WatchdogIntClear \
        ROM_WatchdogIntClear
#else
#define MAP_WatchdogIntClear \
        WatchdogIntClear
#endif
#ifdef ROM_WatchdogRunning
#define MAP_WatchdogRunning \
        ROM_WatchdogRunning
#else
#define MAP_WatchdogRunning \
        WatchdogRunning
#endif
#ifdef ROM_WatchdogEnable
#define MAP_WatchdogEnable \
        ROM_WatchdogEnable
#else
#define MAP_WatchdogEnable \
        WatchdogEnable
#endif
#ifdef ROM_WatchdogResetEnable
#define MAP_WatchdogResetEnable \
        ROM_WatchdogResetEnable
#else
#define MAP_WatchdogResetEnable \
        WatchdogResetEnable
#endif
#ifdef ROM_WatchdogResetDisable
#define MAP_WatchdogResetDisable \
        ROM_WatchdogResetDisable
#else
#define MAP_WatchdogResetDisable \
        WatchdogResetDisable
#endif
#ifdef ROM_WatchdogLock
#define MAP_WatchdogLock \
        ROM_WatchdogLock
#else
#define MAP_WatchdogLock \
        WatchdogLock
#endif
#ifdef ROM_WatchdogUnlock
#define MAP_WatchdogUnlock \
        ROM_WatchdogUnlock
#else
#define MAP_WatchdogUnlock \
        WatchdogUnlock
#endif
#ifdef ROM_WatchdogLockState
#define MAP_WatchdogLockState \
        ROM_WatchdogLockState
#else
#define MAP_WatchdogLockState \
        WatchdogLockState
#endif
#ifdef ROM_WatchdogReloadSet
#define MAP_WatchdogReloadSet \
        ROM_WatchdogReloadSet
#else
#define MAP_WatchdogReloadSet \
        WatchdogReloadSet
#endif
#ifdef ROM_WatchdogReloadGet
#define MAP_WatchdogReloadGet \
        ROM_WatchdogReloadGet
#else
#define MAP_WatchdogReloadGet \
        WatchdogReloadGet
#endif
#ifdef ROM_WatchdogValueGet
#define MAP_WatchdogValueGet \
        ROM_WatchdogValueGet
#else
#define MAP_WatchdogValueGet \
        WatchdogValueGet
#endif
#ifdef ROM_WatchdogIntEnable
#define MAP_WatchdogIntEnable \
        ROM_WatchdogIntEnable
#else
#define MAP_WatchdogIntEnable \
        WatchdogIntEnable
#endif
#ifdef ROM_WatchdogIntStatus
#define MAP_WatchdogIntStatus \
        ROM_WatchdogIntStatus
#else
#define MAP_WatchdogIntStatus \
        WatchdogIntStatus
#endif
#ifdef ROM_WatchdogStallEnable
#define MAP_WatchdogStallEnable \
        ROM_WatchdogStallEnable
#else
#define MAP_WatchdogStallEnable \
        WatchdogStallEnable
#endif
#ifdef ROM_WatchdogStallDisable
#define MAP_WatchdogStallDisable \
        ROM_WatchdogStallDisable
#else
#define MAP_WatchdogStallDisable \
        WatchdogStallDisable
#endif

//*****************************************************************************
//
// Deprecated ROM functions.
//
//*****************************************************************************
#ifndef DEPRECATED
#define MAP_FlashIntGetStatus \
        MAP_FlashIntStatus
#define MAP_USBDevEndpointConfig \
        MAP_USBDevEndpointConfigSet
#define MAP_USBHostPwrFaultConfig \
        MAP_USBHostPwrConfig
#endif

#endif // __ROM_MAP_H__
