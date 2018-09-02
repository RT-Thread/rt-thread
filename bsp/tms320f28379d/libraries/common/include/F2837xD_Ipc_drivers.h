//###########################################################################
//
// FILE:    F2837xD_Ipc_drivers.h
//
// TITLE:    Defines and Macros for the IPC Controller
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

//
//! \addtogroup ipc_driver_api
//! @{
//

#ifndef F2837xD_IPC_DRIVERS_H
#define F2837xD_IPC_DRIVERS_H

//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
#ifdef __cplusplus
extern "C" {
#endif

//
// Included Files
//
#include "F2837xD_device.h"

//
// Defines
//

//
// The following are values that are used to define the maximum size of the
// global circular buffer variables g_asIPCCPU1toCPU2Buffers and
// g_asIPCCPU2toCPU1Buffers. They are also used in the IpcPut() and IpcGet()
// functions. IPC_BUFFER_SIZE and NUM_IPC_INTERRUPTS are user-configurable.
//
#define IPC_BUFFER_SIZE             4     // # of tIpcMessage messages in
                                          // circular buffer
                                          // (must be interval of 2)
#define NUM_IPC_INTERRUPTS          4     // # of IPC interrupts using circular
                                          // buffer
                                          // (must be same number on both CPUs
#define MAX_BUFFER_INDEX            IPC_BUFFER_SIZE - 1

//
// The following are values that can be passed to IPCInitialize()
// as the usCPU1IpcInterrupt and usCPU2IpcInterrupt parameters
//
#define IPC_INT0                    0x0001
#define IPC_INT1                    0x0002
#define IPC_INT2                    0x0003
#define IPC_INT3                    0x0004

//
// The following are values that are returned from all of the IPCCtoM command
// functions to determine whether the command was successfully sent or not.
//
#define STATUS_FAIL                 0x0001
#define STATUS_PASS                 0x0000

//
// The following are values that can be passed to IPCReqMemAccess() as
// usMaster parameter to determine which processor to give master access to
// GSx blocks.
//
#define IPC_GSX_CPU1_MASTER         0x0001
#define IPC_GSX_CPU2_MASTER         0x0000

//
// The following are values that can be passed to all IPC CPU1 to CPU2 or
// CPU2 to CPU1 command functions as bBlock parameter to determine whether to
// wait/block until a slot in PutBuffer is available if it is full, or to exit
// with a failure status.
//
#define ENABLE_BLOCKING             0x0001
#define DISABLE_BLOCKING            0x0000

//
// The following are values that can be passed to IPCCtoMDataRead(),
// IPCCCtoMSetBits(),IPCCCtoMSetBits_Protected(), IPCCCtoMClearBits(),
// IPCCCtoMClearBits_Protected(), IPCCCtoMDataWrite(),
// IPCCtoMDataWrite_Protected()
// as usLength parameter to determine whether command applies to 16- or 32-bit
// data word.
//
#define IPC_LENGTH_16_BITS          0x00000001
#define IPC_LENGTH_32_BITS          0x00000002

//
// The following are values that can be passed to IPCReqMemAccess() as
// ulMask parameter to configure GSxMSEL_REG register for master access to Sx
// RAM block.
//
#define GS0_ACCESS                  0x00000001   // Master Access to GS0
#define GS1_ACCESS                  0x00000002   // Master Access to GS1
#define GS2_ACCESS                  0x00000004   // Master Access to GS2
#define GS3_ACCESS                  0x00000008   // Master Access to GS3
#define GS4_ACCESS                  0x00000010   // Master Access to GS4
#define GS5_ACCESS                  0x00000020   // Master Access to GS5
#define GS6_ACCESS                  0x00000040   // Master Access to GS6
#define GS7_ACCESS                  0x00000080   // Master Access to GS7
#define GS8_ACCESS                  0x00000100   // Master Access to GS8
#define GS9_ACCESS                  0x00000200   // Master Access to GS9
#define GS10_ACCESS                 0x00000400   // Master Access to GS10
#define GS11_ACCESS                 0x00000800   // Master Access to GS11
#define GS12_ACCESS                 0x00001000   // Master Access to GS12
#define GS13_ACCESS                 0x00002000   // Master Access to GS13
#define GS14_ACCESS                 0x00004000   // Master Access to GS14
#define GS15_ACCESS                 0x00008000   // Master Access to GS15

//
// The following are values that can be passed to IPCCtoMTaskBusy() as the
// ulFlags parameter.
// IPC_FLAG17 - IPC_FLAG32 can also be passed to IPCtoMDataRead() and
// IPCCtoMReadBlock() as the ulResponseFlag parameter.
//
#define NO_FLAG                     0x00000000  // NO FLAG
#define IPC_FLAG0                   0x00000001  // IPC FLAG 0
#define IPC_FLAG1                   0x00000002  // IPC FLAG 1
#define IPC_FLAG2                   0x00000004  // IPC FLAG 2
#define IPC_FLAG3                   0x00000008  // IPC FLAG 3
#define IPC_FLAG4                   0x00000010  // IPC FLAG 4
#define IPC_FLAG5                   0x00000020  // IPC FLAG 5
#define IPC_FLAG6                   0x00000040  // IPC FLAG 6
#define IPC_FLAG7                   0x00000080  // IPC FLAG 7
#define IPC_FLAG8                   0x00000100  // IPC FLAG 8
#define IPC_FLAG9                   0x00000200  // IPC FLAG 9
#define IPC_FLAG10                  0x00000400  // IPC FLAG 10
#define IPC_FLAG11                  0x00000800  // IPC FLAG 11
#define IPC_FLAG12                  0x00001000  // IPC FLAG 12
#define IPC_FLAG13                  0x00002000  // IPC FLAG 13
#define IPC_FLAG14                  0x00004000  // IPC FLAG 14
#define IPC_FLAG15                  0x00008000  // IPC FLAG 15
#define IPC_FLAG16                  0x00010000  // IPC FLAG 16
#define IPC_FLAG17                  0x00020000  // IPC FLAG 17
#define IPC_FLAG18                  0x00040000  // IPC FLAG 18
#define IPC_FLAG19                  0x00080000  // IPC FLAG 19
#define IPC_FLAG20                  0x00100000  // IPC FLAG 20
#define IPC_FLAG21                  0x00200000  // IPC FLAG 21
#define IPC_FLAG22                  0x00400000  // IPC FLAG 22
#define IPC_FLAG23                  0x00800000  // IPC FLAG 23
#define IPC_FLAG24                  0x01000000  // IPC FLAG 24
#define IPC_FLAG25                  0x02000000  // IPC FLAG 25
#define IPC_FLAG26                  0x04000000  // IPC FLAG 26
#define IPC_FLAG27                  0x08000000  // IPC FLAG 27
#define IPC_FLAG28                  0x10000000  // IPC FLAG 28
#define IPC_FLAG29                  0x20000000  // IPC FLAG 29
#define IPC_FLAG30                  0x40000000  // IPC FLAG 30
#define IPC_FLAG31                  0x80000000  // IPC FLAG 31

//
// The following are values that are used by all command functions and passed
// between processors in tIpcMessage.ulmessage or in the xTOyIPCCOM register
// to determine what command is requested by the sending processor.
//
#define IPC_SET_BITS_16                 0x00000001 // Used for IPC-Lite
#define IPC_SET_BITS_32                 0x00000002 // Used for IPC-Lite
#define IPC_CLEAR_BITS_16               0x00000003 // Used for IPC-Lite
#define IPC_CLEAR_BITS_32               0x00000004 // Used for IPC-Lite
#define IPC_DATA_WRITE_16               0x00000005 // Used for IPC-Lite
#define IPC_DATA_WRITE_32               0x00000006 // Used for IPC-Lite
#define IPC_DATA_READ_16                0x00000007 // Used for Boot ROM
#define IPC_DATA_READ_32                0x00000008 // Used for Boot ROM
#define IPC_DATA_READ                   0x00000008
#define IPC_SET_BITS_16_PROTECTED       0x00000009 // Used for IPC-Lite
#define IPC_SET_BITS_32_PROTECTED       0x0000000A // Used for IPC-Lite
#define IPC_CLEAR_BITS_16_PROTECTED     0x0000000B // Used for IPC-Lite
#define IPC_CLEAR_BITS_32_PROTECTED     0x0000000C // Used for IPC-Lite
#define IPC_DATA_WRITE_16_PROTECTED     0x0000000D // Used for IPC-Lite
#define IPC_DATA_WRITE_32_PROTECTED     0x0000000E // Used for IPC-Lite

//
// 0x0000000F and 0x0000010 are reserved by boot ROM
//

#define IPC_BRANCH                      0x00000011
#define IPC_FUNC_CALL                   0x00000012
#define IPC_MTOC_EXECUTE_BOOTMODE_CMD   0x00000013

#define IPC_SET_BITS                    0x00010001
#define IPC_CLEAR_BITS                  0x00010002
#define IPC_DATA_WRITE                  0x00010003
#define IPC_BLOCK_READ                  0x00010004
#define IPC_BLOCK_WRITE                 0x00010005
#define IPC_DATA_READ_PROTECTED         0x00010007
#define IPC_SET_BITS_PROTECTED          0x00010008
#define IPC_CLEAR_BITS_PROTECTED        0x00010009
#define IPC_DATA_WRITE_PROTECTED        0x0001000A
#define IPC_BLOCK_WRITE_PROTECTED       0x0001000B

//
// The following are values that can be passed into the
// IPCBootControlSystem() function in the ulBootMode parameter.
//
#define BROM_IPC_EXECUTE_BOOTMODE_CMD     0x00000013

//
// Below are the values programmed into IPCBOOTMODE register
//
#define C1C2_BROM_BOOTMODE_BOOT_FROM_PARALLEL                  0x00000000
#define C1C2_BROM_BOOTMODE_BOOT_FROM_SCI                       0x00000001
#define C1C2_BROM_BOOTMODE_BOOT_FROM_SPI                       0x00000004
#define C1C2_BROM_BOOTMODE_BOOT_FROM_I2C                       0x00000005
#define C1C2_BROM_BOOTMODE_BOOT_FROM_CAN                       0x00000007
#define C1C2_BROM_BOOTMODE_BOOT_FROM_RAM                       0x0000000A
#define C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH                     0x0000000B

//
// The following value is used by the
// IPCBootControlSystem() function to limit the allowed boot mode values.
//
#define C1C2_BROM_BOOTMODE_BOOT_COMMAND_MAX_SUPPORT_VALUE      0x0000000C

//
// The following values report on the CPU02 boot ROM status at all times while
// the CPU02 is booting, and will reside in IPCBOOTSTS[11:0].
//

//
// CPU02 has not filled in a valid value yet
//
#define C2_BOOTROM_BOOTSTS_C2TOC1_IGNORE                             0x00000000

//
// CPU02 has started to boot, but not completed
// the boot process yet
//
#define C2_BOOTROM_BOOTSTS_SYSTEM_START_BOOT                         0x00000001

//
// CPU02 has completed the boot and is ready for
// CPU01 TO CPU02 IPC commands
//
#define C2_BOOTROM_BOOTSTS_SYSTEM_READY                              0x00000002

//
// CPU02 ACKs the command in CPU01 TO CPU01
// BOOTMODE register
//
#define C2_BOOTROM_BOOTSTS_C2TOC1_BOOT_CMD_ACK                       0x00000003

//
// CPU02 un-supported command in CPU01 TO CPU01
// BOOTMODE register
//
#define C2_BOOTROM_BOOTSTS_C2TOC1_BOOT_CMD_NAK_STATUS_NOT_SUPPORTED  0x00000004

//
// CPU2 NAKs the current boot command in
// CPU01 TO CPU01 BOOTMODE register
//
#define C2_BOOTROM_BOOTSTS_C2TOC1_BOOT_CMD_NAK_STATUS_BUSY_WITH_BOOT 0x00000005

//
//! A structure that defines an IPC message.  These fields are used by the
//! IPC drivers to determine handling of data passed between processors.
//! Although they have a defined naming scheme, they can also be used
//! generically
//! to pass 32-bit data words between processors.
//
typedef struct
{
    //! The command passed between processor systems.
    uint32_t ulcommand;

    //! The receiving processor address the command is requesting action on.
    uint32_t uladdress;

    //! A 32-bit variable, the usage of which is determined by ulcommand.
    //! The most common usage is to pass length requirements
    //! with the upper 16-bits storing a Response Flag for read commands.
    uint32_t uldataw1;

    //! A 32-bit variable, the usage of which is determined by ulcommand.
    //! For block transfers, this variable is generally the address in
    //! shared memory used to pass data between processors.
    uint32_t uldataw2;

} tIpcMessage;

//
//! A structure that defines an IPC control instance.  These
//! fields are used by the IPC drivers, and normally it is not necessary for
//! user software to directly read or write fields in the table.
//
typedef struct
{
    //! The address of the PutBuffer IPC message (in MSGRAM)
    tIpcMessage *psPutBuffer;

    //! The IPC INT flag to set when sending messages
    //! for this IPC controller instance.
    uint32_t ulPutFlag;

   //! The address of the PutBuffer Write index (in MSGRAM)
    uint16_t *pusPutWriteIndex;

    //! The address of the PutBuffer Read index (in MSGRAM)
    uint16_t *pusPutReadIndex;

    //! The address of the GetBuffer IPC message(in MSGRAM)
    tIpcMessage *psGetBuffer;

    //! The address of the GetBuffer Write Index (in MSGRAM)
    uint16_t *pusGetWriteIndex;

    //! The address of the GetBuffer Read Index (in MSGRAM)
    uint16_t *pusGetReadIndex;

} tIpcController;

//
// A type definition for the IPC function call command.
//
typedef uint32_t (*tfIpcFuncCall)(uint32_t ulParam);

//
// Prototypes for Circular Buffers
//
extern tIpcMessage g_asIPCCPU1toCPU2Buffers[NUM_IPC_INTERRUPTS][IPC_BUFFER_SIZE];
extern tIpcMessage g_asIPCCPU2toCPU1Buffers[NUM_IPC_INTERRUPTS][IPC_BUFFER_SIZE];

//
// Function Prototypes
//
extern void IPCInitialize (volatile tIpcController *psController,
                           uint16_t usCPU2IpcInterrupt,
                           uint16_t usCPU1IpcInterrupt);
extern uint16_t IpcPut (volatile tIpcController *psController,
                        tIpcMessage *psMessage,
                        uint16_t bBlock);
extern uint16_t IpcGet (volatile tIpcController *psController,
                        tIpcMessage *psMessage,
                        uint16_t bBlock);
extern uint16_t IPCLtoRDataRead (volatile tIpcController *psController,
                                 uint32_t ulAddress, void *pvData,
                                 uint16_t usLength, uint16_t bBlock,
                                 uint32_t ulResponseFlag);
extern uint16_t IPCLtoRDataRead_Protected (volatile tIpcController *psController,
                                           uint32_t ulAddress, void *pvData,
                                           uint16_t usLength, uint16_t bBlock,
                                           uint32_t ulResponseFlag);
extern uint16_t IPCLtoRSetBits(volatile tIpcController *psController,
                               uint32_t ulAddress, uint32_t ulMask,
                               uint16_t usLength,uint16_t bBlock);
extern uint16_t IPCLtoRSetBits_Protected(volatile tIpcController *psController,
                                         uint32_t ulAddress, uint32_t ulMask,
                                         uint16_t usLength, uint16_t bBlock);
extern uint16_t IPCLtoRClearBits(volatile tIpcController *psController,
                                 uint32_t ulAddress, uint32_t ulMask,
                                 uint16_t usLength,uint16_t bBlock);
extern uint16_t IPCLtoRClearBits_Protected(volatile tIpcController *psController,
                                           uint32_t ulAddress, uint32_t ulMask,
                                           uint16_t usLength, uint16_t bBlock);
extern uint16_t IPCLtoRDataWrite(volatile tIpcController *psController,
                                 uint32_t ulAddress, uint32_t ulData,
                                 uint16_t usLength, uint16_t bBlock,
                                 uint32_t ulResponseFlag);
extern uint16_t IPCLtoRDataWrite_Protected(volatile tIpcController *psController,
                                           uint32_t ulAddress, uint32_t ulData,
                                           uint16_t usLength, uint16_t bBlock,
                                           uint32_t ulResponseFlag);
extern uint16_t IPCLtoRBlockRead(volatile tIpcController *psController,
                                 uint32_t ulAddress, uint32_t ulShareAddress,
                                 uint16_t usLength, uint16_t bBlock,
                                 uint32_t ulResponseFlag);
extern uint16_t IPCLtoRBlockWrite(volatile tIpcController *psController,
                                  uint32_t ulAddress, uint32_t ulShareAddress,
                                  uint16_t usLength, uint16_t usWordLength,
                                  uint16_t bBlock);
extern uint16_t IPCLtoRBlockWrite_Protected(volatile tIpcController *psController,
                                            uint32_t ulAddress,
                                            uint32_t ulShareAddress,
                                            uint16_t usLength,
                                            uint16_t usWordLength,
                                            uint16_t bBlock);
extern uint16_t IPCLtoRFunctionCall(volatile tIpcController *psController,
                                    uint32_t ulAddress, uint32_t ulParam,
                                    uint16_t bBlock);
extern uint16_t IPCLtoRSendMessage(volatile tIpcController *psController,
                                   uint32_t ulCommand, uint32_t ulAddress,
                                   uint32_t ulDataW1, uint32_t ulDataW2,
                                   uint16_t bBlock);
#if defined (CPU2)
uint16_t
IPCReqMemAccess (volatile tIpcController *psController, uint32_t ulMask,
                 uint16_t usMaster, uint16_t bBlock);
#endif

extern void IPCRtoLDataWrite(tIpcMessage *psMessage);
extern void IPCRtoLDataWrite_Protected(tIpcMessage *psMessage);
extern void IPCRtoLDataRead(volatile tIpcController *psController,
                            tIpcMessage *psMessage, uint16_t bBlock);
extern void IPCRtoLDataRead_Protected(volatile tIpcController *psController,
                                      tIpcMessage *psMessage,uint16_t bBlock);
extern void IPCRtoLSetBits(tIpcMessage *psMessage);
extern void IPCRtoLSetBits_Protected(tIpcMessage *psMessage);
extern void IPCRtoLClearBits(tIpcMessage *psMessage);
extern void IPCRtoLClearBits_Protected(tIpcMessage *psMessage);
extern void IPCRtoLBlockRead(tIpcMessage *psMessage);
extern void IPCRtoLBlockWrite(tIpcMessage *psMessage);
extern void IPCRtoLBlockWrite_Protected(tIpcMessage *psMessage);
extern void IPCRtoLFunctionCall(tIpcMessage *psMessage);

//
// IPC Lite Driver Prototype Definitions
//
extern uint16_t IPCLiteLtoRGetResult (void *pvData, uint16_t usLength,
                                      uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRDataRead(uint32_t ulFlag, uint32_t ulAddress,
                                    uint16_t usLength, uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRSetBits(uint32_t ulFlag, uint32_t ulAddress,
                                   uint32_t ulMask, uint16_t usLength,
                                   uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRSetBits_Protected (uint32_t ulFlag,
                                              uint32_t ulAddress,
                                              uint32_t ulMask,
                                              uint16_t usLength,
                                              uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRClearBits(uint32_t ulFlag, uint32_t ulAddress,
                                     uint32_t ulMask, uint16_t usLength,
                                     uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRClearBits_Protected (uint32_t ulFlag,
                                                uint32_t ulAddress,
                                                uint32_t ulMask,
                                                uint16_t usLength,
                                                uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRDataWrite(uint32_t ulFlag, uint32_t ulAddress,
                                     uint32_t ulData, uint16_t usLength,
                                     uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRDataWrite_Protected(uint32_t ulFlag,
                                               uint32_t ulAddress,
                                               uint32_t ulData,
                                               uint16_t usLength,
                                               uint32_t ulStatusFlag);
extern uint16_t IPCLiteLtoRFunctionCall(uint32_t ulFlag, uint32_t ulAddress,
                                        uint32_t ulParam, uint32_t ulStatusFlag);
extern uint16_t IPCLiteReqMemAccess (uint32_t ulFlag, uint32_t ulMask,
                                     uint16_t ulMaster, uint32_t ulStatusFlag);
extern void IPCLiteRtoLDataRead(uint32_t ulFlag, uint32_t ulStatusFlag);
extern void IPCLiteRtoLSetBits(uint32_t ulFlag, uint32_t ulStatusFlag);
extern void IPCLiteRtoLSetBits_Protected (uint32_t ulFlag, uint32_t ulStatusFlag);
extern void IPCLiteRtoLClearBits(uint32_t ulFlag, uint32_t ulStatusFlag);
extern void IPCLiteRtoLClearBits_Protected (uint32_t ulFlag,
                                            uint32_t ulStatusFlag);
extern void IPCLiteRtoLDataWrite(uint32_t ulFlag, uint32_t ulStatusFlag);
extern void IPCLiteRtoLDataWrite_Protected(uint32_t ulFlag,
                                           uint32_t ulStatusFlag);
extern void IPCLiteRtoLFunctionCall(uint32_t ulFlag, uint32_t ulStatusFlag);

//
// IPC Utility Driver Prototype Definitions
//
extern void IPCRtoLFlagAcknowledge (uint32_t ulFlags);
extern Uint16 IPCRtoLFlagBusy (uint32_t ulFlags);
extern Uint16 IPCLtoRFlagBusy (uint32_t ulFlags);
extern void IPCLtoRFlagSet (uint32_t ulFlags);
extern void IPCLtoRFlagClear (uint32_t ulFlags);
extern uint32_t IPCGetBootStatus (void);
extern uint16_t IPCBootCPU2(uint32_t ulBootMode);
#ifdef __cplusplus
}
#endif /* extern "C" */

//
// Close the Doxygen group.
//! @}
//

#endif  // end of F2837xD_IPC_DRIVERS_H definition

//
// End of file
//
