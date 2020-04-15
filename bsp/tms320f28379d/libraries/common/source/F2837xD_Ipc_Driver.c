//###########################################################################
//
// FILE:   F2837xD_Ipc_Driver.c
//
// TITLE:  F2837xD Inter-Processor Communication (IPC) API Driver Functions.
//
// DESCRIPTION:
//         28x API functions for inter-processor communications between the
//         two CPUs. The IPC functions require the usage of the CPU1 to CPU2
//         and CPU2 to CPU1 MSG RAM's to store the circular ring
//         buffer and indexes. Commands can be queued up in order on a single
//         IPC interrupt channel.  For those IPC commands which are not
//         interdependent, multiple IPC interrupt channels may be used.
//         The driver functions in this file are available only as
//         sample functions for application development.  Due to the generic
//         nature of these functions and the cycle overhead inherent to a
//         function call, the code is not intended to be used in cases where
//         maximum efficiency is required in a system.
// NOTE:   This source code is used by both CPUs. That is both CPU1 and CPU2
//         Cores use this code.
//         The active debug CPU will be referred to as Local CPU.
//         When using this source code in CPU1, the term "local"
//         will mean CPU1 and the term "remote" CPU will be mean CPU2.
//         When using this source code in CPU2, the term "local"
//         will mean CPU2 and the term "remote" CPU will be mean CPU1.
//
//         The abbreviations LtoR and RtoL  within the function names mean
//         Local to Remote and Remote to Local respectively.
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

//*****************************************************************************
//! \addtogroup ipc_driver_api
//! @{
//*****************************************************************************
#include "F2837xD_device.h"
#include "F2837xD_Ipc_drivers.h"

#if defined(CPU1)
#pragma DATA_SECTION(g_asIPCCPU1toCPU2Buffers, "PUTBUFFER");
#pragma DATA_SECTION(g_usPutWriteIndexes, "PUTWRITEIDX");
#pragma DATA_SECTION(g_usGetReadIndexes, "GETREADIDX");

#pragma DATA_SECTION(g_asIPCCPU2toCPU1Buffers, "GETBUFFER");
#pragma DATA_SECTION(g_usGetWriteIndexes, "GETWRITEIDX");
#pragma DATA_SECTION(g_usPutReadIndexes, "PUTREADIDX");

#elif defined(CPU2)

#pragma DATA_SECTION(g_asIPCCPU2toCPU1Buffers, "PUTBUFFER");
#pragma DATA_SECTION(g_usPutWriteIndexes, "PUTWRITEIDX");
#pragma DATA_SECTION(g_usGetReadIndexes, "GETREADIDX");

#pragma DATA_SECTION(g_asIPCCPU1toCPU2Buffers, "GETBUFFER");
#pragma DATA_SECTION(g_usGetWriteIndexes, "GETWRITEIDX");
#pragma DATA_SECTION(g_usPutReadIndexes, "PUTREADIDX");

#endif

//
// Global Circular Buffer Definitions
//
tIpcMessage g_asIPCCPU1toCPU2Buffers[NUM_IPC_INTERRUPTS][IPC_BUFFER_SIZE];
tIpcMessage g_asIPCCPU2toCPU1Buffers[NUM_IPC_INTERRUPTS][IPC_BUFFER_SIZE];

//
// Global Circular Buffer Index Definitions
//
uint16_t g_usPutWriteIndexes[NUM_IPC_INTERRUPTS];
uint16_t g_usPutReadIndexes[NUM_IPC_INTERRUPTS];
uint16_t g_usGetWriteIndexes[NUM_IPC_INTERRUPTS];
uint16_t g_usGetReadIndexes[NUM_IPC_INTERRUPTS];

//*****************************************************************************
//
//! Initializes System IPC driver controller
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param usCPU2IpcInterrupt specifies the CPU2 IPC interrupt number used by
//! psController.
//! \param usCPU1IpcInterrupt specifies the CPU1 IPC interrupt number used by
//! psController.
//!
//! This function initializes the IPC driver controller with circular buffer
//! and index addresses for an IPC interrupt pair. The
//! \e usCPU2IpcInterrupt and \e usCPU1IpcInterrupt parameters can be one of
//! the following values:
//! \b IPC_INT0, \b IPC_INT1, \b IPC_INT2, \b IPC_INT3.
//!
//! \note If an interrupt is currently in use by an \e tIpcController instance,
//! that particular interrupt should not be tied to a second \e tIpcController
//! instance.
//!
//! \note For a particular usCPU2IpcInterrupt - usCPU1IpcInterrupt pair, there
//! must be an instance of tIpcController defined and initialized on both the
//! CPU1 and CPU2 systems.
//!
//! \return None.
//
//*****************************************************************************
void
IPCInitialize (volatile tIpcController *psController,
               uint16_t usCPU2IpcInterrupt, uint16_t usCPU1IpcInterrupt)
{
#if defined(CPU1)
    // CPU1toCPU2PutBuffer and Index Initialization
    psController->psPutBuffer = &g_asIPCCPU1toCPU2Buffers[usCPU2IpcInterrupt-1][0];
    psController->pusPutWriteIndex = &g_usPutWriteIndexes[usCPU2IpcInterrupt-1];
    psController->pusGetReadIndex = &g_usGetReadIndexes[usCPU1IpcInterrupt-1];
    psController->ulPutFlag = (uint32_t)(1 << (usCPU2IpcInterrupt - 1));

    // CPU1toCPU2GetBuffer and Index Initialization
    psController->psGetBuffer = &g_asIPCCPU2toCPU1Buffers[usCPU1IpcInterrupt-1][0];
    psController->pusGetWriteIndex = &g_usGetWriteIndexes[usCPU1IpcInterrupt-1];
    psController->pusPutReadIndex = &g_usPutReadIndexes[usCPU2IpcInterrupt-1];
#elif defined(CPU2)
    // CPU2toCPU1PutBuffer and Index Initialization
    psController->psPutBuffer = &g_asIPCCPU2toCPU1Buffers[usCPU1IpcInterrupt-1][0];
    psController->pusPutWriteIndex = &g_usPutWriteIndexes[usCPU1IpcInterrupt-1];
    psController->pusGetReadIndex = &g_usGetReadIndexes[usCPU2IpcInterrupt-1];
    psController->ulPutFlag = (uint32_t)(1 << (usCPU1IpcInterrupt - 1));

    // CPU1toCPU2GetBuffer and Index Initialization
    psController->psGetBuffer = &g_asIPCCPU1toCPU2Buffers[usCPU2IpcInterrupt-1][0];
    psController->pusGetWriteIndex = &g_usGetWriteIndexes[usCPU2IpcInterrupt-1];
    psController->pusPutReadIndex = &g_usPutReadIndexes[usCPU1IpcInterrupt-1];
#endif
    // Initialize PutBuffer WriteIndex = 0 and GetBuffer ReadIndex = 0
    *(psController->pusPutWriteIndex) = 0;
    *(psController->pusGetReadIndex) = 0;
}

//*****************************************************************************
//
//! Writes a message into the PutBuffer.
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param psMessage specifies the address of the \e tIpcMessage instance to be
//! written to PutBuffer.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a free slot (1= wait until free spot available, 0 = exit with
//! STATUS_FAIL if no free slot).
//!
//! This function checks if there is a free slot in the PutBuffer. If so, it
//! puts the message pointed to by \e psMessage into the free slot and
//! increments the WriteIndex. Then it sets the appropriate IPC interrupt flag
//! specified by \e psController->usPutFlag.  The \e bBlock parameter can be
//! one of the following values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return \b STATUS_FAIL if PutBuffer is full. \b STATUS_PASS if Put occurs
//! successfully.
//
//*****************************************************************************
uint16_t
IpcPut (volatile tIpcController *psController, tIpcMessage *psMessage,
        uint16_t bBlock)
{
    uint16_t writeIndex;
    uint16_t readIndex;
    uint16_t returnStatus = STATUS_PASS;

    writeIndex = *(psController->pusPutWriteIndex);
    readIndex = *(psController->pusPutReadIndex);

    //
    // Wait until Put Buffer slot is free
    //
    while (((writeIndex + 1) & MAX_BUFFER_INDEX) == readIndex)
    {
        //
        // If designated as a "Blocking" function, and Put buffer is full,
        // return immediately with fail status.
        //
        if (!bBlock)
        {
            returnStatus = STATUS_FAIL;
            break;
        }

        readIndex = *(psController->pusPutReadIndex);
    }

    if (returnStatus != STATUS_FAIL)
    {
        //
        // When slot is free, Write Message to PutBuffer, update PutWriteIndex,
        // and set the CPU IPC INT Flag
        //
        psController->psPutBuffer[writeIndex] = *psMessage;

        writeIndex = (writeIndex + 1) & MAX_BUFFER_INDEX;
        *(psController->pusPutWriteIndex) = writeIndex;

        IpcRegs.IPCSET.all |= psController->ulPutFlag;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Reads a message from the GetBuffer.
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param psMessage specifies the address of the \e tIpcMessage instance where
//! the message from GetBuffer should be written to.
//! \param bBlock specifies whether to allow function to block until GetBuffer
//! has a message (1= wait until message available, 0 = exit with STATUS_FAIL
//! if no message).
//!
//! This function checks if there is a message in the GetBuffer. If so, it gets
//! the message in the GetBuffer pointed to by the ReadIndex and writes it to
//! the address pointed to by \e psMessage. The \e bBlock parameter can be one
//! of the following
//! values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return \b STATUS_PASS if GetBuffer is empty. \b STATUS_FAIL if Get occurs
//! successfully.
//
//*****************************************************************************
uint16_t
IpcGet (volatile tIpcController *psController, tIpcMessage *psMessage,
        uint16_t bBlock)
{
    uint16_t writeIndex;
    uint16_t readIndex;
    uint16_t returnStatus = STATUS_PASS;

    writeIndex = *(psController->pusGetWriteIndex);
    readIndex = *(psController->pusGetReadIndex);

    //
    // Loop while GetBuffer is empty
    //
    while (writeIndex == readIndex)
    {
        //
        // If designated as a "Blocking" function, and Get buffer is empty,
        // return immediately with fail status.
        //
        if (!bBlock)
        {
            returnStatus = STATUS_FAIL;
            break;
        }

        writeIndex = *(psController->pusGetWriteIndex);
    }

    if (returnStatus != STATUS_FAIL)
    {
        //
        // If there is a message in GetBuffer, Read Message and update
        // the ReadIndex
        //
        *psMessage = psController->psGetBuffer[readIndex];

        readIndex = (readIndex + 1) & MAX_BUFFER_INDEX;
        *(psController->pusGetReadIndex) = readIndex;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Sends a command to read either a 16- or 32-bit data word from the remote
//! CPU
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU address to read from
//! \param pvData is a pointer to the 16/32-bit variable where read data will
//! be stored.
//! \param usLength designates 16- or 32-bit read (1 = 16-bit, 2 = 32-bit)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//! \param ulResponseFlag indicates the remote CPU to the local CPU Flag
//! number mask used to report when the read data is available at pvData.
//! (\e ulResponseFlag MUST use IPC flags 17-32, and not 1-16)
//!
//! This function will allow the local CPU system to send a 16/32-bit data
//! read command to the remote CPU system and set a ResponseFlag to track the
//! status of the read.
//! The remote CPU will respond with a DataWrite command which will place
//! the data in the local CPU address pointed to by \e pvData. When the local
//! CPU receives the DataWrite command and writes the read data into \e *pvData location,
//! it will clear the ResponseFlag, indicating to the rest of the system that
//! the data is ready. The \e usLength parameter can be one of the
//! following values: \b IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e
//! bBlock parameter can be one of the following values: \b ENABLE_BLOCKING or
//! \b DISABLE_BLOCKING.
//! The \e ulResponseFlag parameter can be any single one of the flags \b
//! IPC_FLAG16 - \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRDataRead (volatile tIpcController *psController, uint32_t ulAddress,
                 void *pvData, uint16_t usLength, uint16_t bBlock,
                 uint32_t ulResponseFlag)
{

    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up read command, address, dataw1 = ResponseFlag | word length,
    // dataw2 = address where word
    // should be written to when returned.
    //
    sMessage.ulcommand = IPC_DATA_READ;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (ulResponseFlag & 0xFFFF0000)|(uint32_t)usLength;
    sMessage.uldataw2 = (uint32_t)pvData;

    //
    // Set ResponseFlag (cleared once data is read into address at pvData)
    // Put Message into PutBuffer and set IPC INT flag
    //
    IpcRegs.IPCSET.all |= (ulResponseFlag & 0xFFFF0000);
    status = IpcPut (psController, &sMessage, bBlock);

    return status;

    //
    //Note: Read Response will have sMessage.ulcommand = IPC_DATA_WRITE
    //                              sMessage.uladdress = (uint32_t) pvData
    //                              sMessage.uldataw1  = ulStatusFlag |
    //                                                   (uint32_t) usLength;
    //                              sMessage.uldataw2  = word to be read into
    //                                                   pvData address.
    //
}

//*****************************************************************************
//
//! Sends the command to read either a 16- or 32-bit data word from remote
//! CPU system address to a write-protected local CPU address.
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU address to read from
//! \param pvData is a pointer to the 16/32-bit variable where read data will
//! be stored.
//! \param usLength designates 16- or 32-bit read (1 = 16-bit, 2 = 32-bit)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//! \param ulResponseFlag indicates the local CPU to remote CPU Flag number
//! mask used to report when the read data is available at pvData.
//! (\e ulResponseFlag MUST use IPC flags 17-32, and not 1-16)
//!
//! This function will allow the local CPU system to send a 16/32-bit data
//! read command to the remote CPU system and set a ResponseFlag to track the
//! status of the read.
//! The remote CPU system will respond with a DataWrite command which will
//! place the data in the local CPU address pointed to by \e pvData.
//! When the local CPU receives the DataWrite command and writes the read data
//! into \e *pvData location, it will clear the ResponseFlag, indicating to
//! the rest of the system that the data is ready. The \e usLength parameter
//! can be one of the following values: \b IPC_LENGTH_16_BITS or
//! \b IPC_LENGTH_32_BITS. The \e bBlock parameter can be one of the following
//! values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//! The \e ulResponseFlag parameter can be any single one of the flags \b
//! IPC_FLAG16 - \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRDataRead_Protected (volatile tIpcController *psController,
                           uint32_t ulAddress, void *pvData, uint16_t usLength,
                           uint16_t bBlock,
                           uint32_t ulResponseFlag)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up read command, address, dataw1 = ResponseFlag | word length, dataw2
    // = address where word should be written to when returned.
    //
    sMessage.ulcommand = IPC_DATA_READ_PROTECTED;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (ulResponseFlag & 0xFFFF0000)|(uint32_t)usLength;
    sMessage.uldataw2 = (uint32_t)pvData;

    //
    // Set ResponseFlag (cleared once data is read into address at pvData)
    // Put Message into PutBuffer and set IPC INT flag
    //
    IpcRegs.IPCSET.all |= (ulResponseFlag & 0xFFFF0000);
    status = IpcPut (psController, &sMessage, bBlock);

    return status;
    //
    // Note: Read Response will have sMessage.ulcommand = IPC_DATA_WRITE
    //                               sMessage.uladdress = (uint32_t) pvData
    //                               sMessage.uldataw1  = ulStatusFlag |
    //                                                    (uint32_t) usLength;
    //                               sMessage.uldataw2  = word to be read into
    //                                                    pvData address.
    //
}

//*****************************************************************************
//
//! Sets the designated bits in a 16-bit data word at the remote CPU system
//! address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU address to write to
//! \param ulMask specifies the 16/32-bit mask for bits which should be set at
//! \e ulAddress.
//! 16-bit masks should fill the lower 16-bits (upper 16-bits will be all
//! 0x0000).
//! \param usLength specifies the length of the bit mask (1=16-bits, 2=32-bits)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to set bits specified by the
//! \e ulMask variable in a 16/32-bit word on the remote CPU system. The \e
//! usLength parameter can be one of the following values: \b IPC_LENGTH_16_BITS
//! or \b IPC_LENGTH_32_BITS. The \e bBlock parameter can be one of the
//! following values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRSetBits(volatile tIpcController *psController, uint32_t ulAddress,
               uint32_t ulMask, uint16_t usLength,
               uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up set bits command, address, dataw1 = word length, dataw2 =
    // 16/32-bit mask
    //
    sMessage.ulcommand = IPC_SET_BITS;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (uint32_t)usLength;
    sMessage.uldataw2 = ulMask;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}
//*****************************************************************************
//
//! Sets the designated bits in a 16-bit write-protected data word at the
//! remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU address to write to
//! \param ulMask specifies the 16/32-bit mask for bits which should be set at
//! \e ulAddress. 16-bit masks should fill the lower 16-bits (upper 16-bits
//! will be all 0x0000).
//! \param usLength specifies the length of the bit mask (1=16-bits, 2=32-bits)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to set bits specified by the
//! \e ulMask variable in a write-protected 16/32-bit word on the remote CPU
//! system. The \e usLength parameter can be one of the  following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter can be
//! one of the following values:
//! \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRSetBits_Protected(volatile tIpcController *psController,
                         uint32_t ulAddress, uint32_t ulMask, uint16_t usLength,
                         uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up set bits command, address, dataw1 = word length, dataw2 =
    // 16/32-bit mask
    //
    sMessage.ulcommand = IPC_SET_BITS_PROTECTED;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (uint32_t)usLength;
    sMessage.uldataw2 = ulMask;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Clears the designated bits in a 16-bit data word at the remote CPU system
//! address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU address to write to
//! \param ulMask specifies the 16/32-bit mask for bits which should be cleared
//! at \e ulAddress. 16-bit masks should fill the lower 16-bits (upper 16-bits
//! will be all 0x0000).
//! \param usLength specifies the length of the bit mask (1=16-bits, 2=32-bits)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to clear bits specified by
//! the \e ulMask variable in a 16/32-bit word on the remote CPU system. The \e
//! usLength parameter can be one of the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter can be
//! one of the following values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRClearBits(volatile tIpcController *psController, uint32_t ulAddress,
                 uint32_t ulMask, uint16_t usLength,
                 uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up clear bits command, address, dataw1 = word length, dataw2 =
    // 16/32-bit mask
    //
    sMessage.ulcommand = IPC_CLEAR_BITS;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (uint32_t)usLength;
    sMessage.uldataw2 = ulMask;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Clears the designated bits in a 16-bit write-protected data word at
//! remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the secondary CPU address to write to
//! \param ulMask specifies the 16/32-bit mask for bits which should be cleared
//! at \e ulAddress. 16-bit masks should fill the lower 16-bits (upper 16-bits
//! will be all 0x0000).
//! \param usLength specifies the length of the bit mask (1=16-bits, 2=32-bits)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to set bits specified by the
//! \e ulMask variable in a write-protected 16/32-bit word on the remote CPU
//! system. The \e usLength parameter can be  one of the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter can be
//! one of the following values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRClearBits_Protected(volatile tIpcController *psController,
                           uint32_t ulAddress, uint32_t ulMask,
                           uint16_t usLength, uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up clear bits command, address, dataw1 = word length, dataw2 =
    // 16/32-bit mask
    //
    sMessage.ulcommand = IPC_CLEAR_BITS_PROTECTED;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (uint32_t)usLength;
    sMessage.uldataw2 = ulMask;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Writes a 16/32-bit data word to the remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote cpu address to write to
//! \param ulData specifies the 16/32-bit word which will be written.
//! For 16-bit words, only the lower 16-bits of ulData will be considered by
//! the master system.
//! \param usLength is the length of the word to write (1 = 16-bits, 2 =
//! 32-bits)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//! \param ulResponseFlag is used to pass the \e ulResponseFlag back to the
//! remote cpu only when this function is called in response to \e
//! IPCMtoCDataRead(). Otherwise, set to 0.
//!
//! This function will allow the local CPU system to write a 16/32-bit word
//! via the \e ulData variable to an address on the remote CPU system.
//! The \e usLength parameter can be one of the following values:
//! \b IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter
//! can be one of the following values: \b ENABLE_BLOCKING or \b
//! DISABLE_BLOCKING.
//! The \e ulResponseFlag parameter can be any single one of the flags \b
//! IPC_FLAG16 - \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRDataWrite(volatile tIpcController *psController, uint32_t ulAddress,
                 uint32_t ulData, uint16_t usLength, uint16_t bBlock,
                 uint32_t ulResponseFlag)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up write command, address, dataw1 = ResponseFlag | word length,
    // dataw2 = data to write
    //
    sMessage.ulcommand = IPC_DATA_WRITE;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = ulResponseFlag |(uint32_t)usLength;
    sMessage.uldataw2 = ulData;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Writes a 16/32-bit data word to a write-protected remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the write-protected remote CPU address to
//! write to
//! \param ulData specifies the 16/32-bit word which will be written. For
//! 16-bit words, only the lower 16-bits of ulData will be considered by the
//! master system.
//! \param usLength is the length of the word to write (1 = 16-bits, 2 =
//! 32-bits)
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//! \param ulResponseFlag is used to pass the \e ulResponseFlag back to the
//! remote CPU only when this function is called in response to \e
//! IPCMtoCDataRead(). Otherwise, set to 0.
//!
//! This function will allow the local CPU system to write a 16/32-bit word
//! via the \e ulData variable to a write-protected address on the remote CPU
//! system. The \e usLength parameter can be one of the following values:
//!  \b IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter
//! can be one of the following values: \b ENABLE_BLOCKING or \b
//! DISABLE_BLOCKING.
//! The \e ulResponseFlag parameter can be any single one of the flags \b
//! IPC_FLAG16 -
//! \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRDataWrite_Protected(volatile tIpcController *psController,
                           uint32_t ulAddress, uint32_t ulData,
                           uint16_t usLength, uint16_t bBlock,
                           uint32_t ulResponseFlag)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up write command, address, dataw1 = ResponseFlag | word length,
    // dataw2 = data to write
    //
    sMessage.ulcommand = IPC_DATA_WRITE_PROTECTED;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = ulResponseFlag |(uint32_t)usLength;
    sMessage.uldataw2 = ulData;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Sends the command to read a block of data from remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU memory block starting address
//! to read from.
//! \param ulShareAddress specifies the local CPU shared memory address the
//! read block will read to.
//! \param usLength designates the block size in 16-bit words.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//! \param ulResponseFlag indicates the local CPU to remote CPU Flag number
//!  mask used to report when the read block data is available starting at
//!  /e ulShareAddress. (\e ulResponseFlag MUST use IPC flags 17-32, and not
//! 1-16)
//!
//! This function will allow the local CPU system to send a read block
//! command to the remote CPU system and set a ResponseFlag to track the status
//! of the read. The remote CPU system will process the read and place the data
//! in shared memory at the location specified in the \e ulShareAddress
//! parameter and then clear the ResponseFlag, indicating that the block is
//! ready. The \e bBlock parameter can be one of the following values: \b
//! ENABLE_BLOCKING or \b DISABLE_BLOCKING. The \e ulResponseFlag parameter can
//! be any single one of the flags \b IPC_FLAG16 - \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRBlockRead(volatile tIpcController *psController, uint32_t ulAddress,
                 uint32_t ulShareAddress, uint16_t usLength, uint16_t bBlock,
                 uint32_t ulResponseFlag)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up block read command, address, dataw1 = ResponseFlag | block length,
    // dataw2 = remote CPU address in shared memory
    // where block data should be read to
    // (corresponding to local CPU ulShareAddress).
    //
    sMessage.ulcommand = IPC_BLOCK_READ;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = (ulResponseFlag & 0xFFFF0000) |(uint32_t)usLength;
    sMessage.uldataw2 = ulShareAddress;

    //
    // Set ResponseFlag (cleared once data is read into Share Address location)
    // Put Message into PutBuffer and set IPC INT flag
    //
    IpcRegs.IPCSET.all |= (ulResponseFlag & 0xFFFF0000);
    status = IpcPut (psController, &sMessage, bBlock);

    return status;
    //
    // Note: Read Block Response will occur in processing of ReadBlock (since
    // remote CPU has access to shared memory)
    //
}

//*****************************************************************************
//
//! Writes a block of data to remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU memory block starting address
//!  to write to.
//! \param ulShareAddress specifies the local CPU shared memory address where
//! data to write from resides.
//! \param usLength designates the block size in 16- or 32-bit words (depends
//! on \e usWordLength).
//! \param usWordLength designates the word size (16-bits = 1 or 32-bits = 2).
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to write a block of data to
//! the remote CPU system starting from the location specified by the
//! \e ulAdress parameter. Prior to calling this function, the local CPU
//! system code should place the data to write in shared memory starting at /e
//! ulShareAddress.
//! The \e usWordLength parameter can be one of the following values:
//! \b IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter
//! can be one of the following values: \b ENABLE_BLOCKING or \b
//! DISABLE_BLOCKING.
//! The \e ulResponseFlag parameter can be any single one of the flags \b
//! IPC_FLAG16 - \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \note If the shared SARAM blocks are used to pass the RAM block between the
//! processors, the IPCReqMemAccess() function must be called first in order to
//! give the slave CPU write access to the shared memory block(s).
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRBlockWrite(volatile tIpcController *psController, uint32_t ulAddress,
                  uint32_t ulShareAddress, uint16_t usLength,
                  uint16_t usWordLength, uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up block write command, address, dataw1 = block length,
    // dataw2 = remote CPU shared mem address
    // where write data resides
    //
    sMessage.ulcommand = IPC_BLOCK_WRITE;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = ((uint32_t)(usWordLength)<<16) + (uint32_t)usLength;
    sMessage.uldataw2 = ulShareAddress;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Writes a block of data to a write-protected remote CPU system address
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the write-protected remote CPU block starting
//! address to write to.
//! \param ulShareAddress specifies the local CPU shared memory address where
//!  data to write from resides.
//! \param usLength designates the block size in 16- or 32-bit words (depends
//! on \e usWordLength).
//! \param usWordLength designates the word size (16-bits = 1 or 32-bits = 2).
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to write a block of data to
//! a write-protected region on the remote CPU system starting from the
//! location specified by the \e ulAdress parameter. Prior to calling this
//! function, the local CPU system code should place the data to write in
//! shared memory starting at /e ulShareAddress.
//! The \e usWordLength parameter can be one of the following values:
//! \b IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e bBlock parameter
//! can be one of the following values: \b ENABLE_BLOCKING or \b
//! DISABLE_BLOCKING.
//! The \e ulResponseFlag parameter can be any single one of the flags \b
//! IPC_FLAG16 - \b IPC_FLAG31 or \b NO_FLAG.
//!
//! \note If the shared SARAM blocks are used to pass the RAM block between the
//! processors, the IPCReqMemAccess() function must be called first in order to
//! give the the slave CPU write access to the shared memory block(s).
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRBlockWrite_Protected(volatile tIpcController *psController,
                            uint32_t ulAddress, uint32_t ulShareAddress,
                            uint16_t usLength, uint16_t usWordLength,
                            uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up block write command, address, dataw1 = block length,
    // dataw2 = remote CPU shared mem address
    // where write data resides
    //
    sMessage.ulcommand = IPC_BLOCK_WRITE_PROTECTED;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = ((uint32_t)(usWordLength)<<16) + (uint32_t)usLength;
    sMessage.uldataw2 = ulShareAddress;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Calls remote CPU function with 1 optional parameter .
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulAddress specifies the remote CPU function address
//! \param ulParam specifies the 32-bit optional parameter value. If not used,
//! this can be a dummy value.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to call a function on the
//! remote CPU. The \e ulParam variable is a single optional 32-bit parameter
//! to pass to the function. The \e bBlock parameter can be one of the
//! following values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRFunctionCall(volatile tIpcController *psController, uint32_t ulAddress,
                    uint32_t ulParam,
                    uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Set up function call command, address, dataw1 = 32-bit parameter
    //
    sMessage.ulcommand = IPC_FUNC_CALL;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = ulParam;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

//*****************************************************************************
//
//! Sends generic message to remote CPU system
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulCommand specifies 32-bit command word to insert into message.
//! \param ulAddress specifies 32-bit address word to insert into message.
//! \param ulDataW1 specifies 1st 32-bit data word to insert into message.
//! \param ulDataW2 specifies 2nd 32-bit data word to insert into message.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the local CPU system to send a generic message to
//! the remote CPU system. Note that the user should create a corresponding
//! function on the remote CPU side to interpret/use the message or fill
//! parameters in such a way that the existing IPC drivers can recognize the
//! command and properly process the message.
//! The \e bBlock parameter can be one of the following values: \b
//! ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCLtoRSendMessage(volatile tIpcController *psController, uint32_t ulCommand,
                   uint32_t ulAddress, uint32_t ulDataW1, uint32_t ulDataW2,
                   uint16_t bBlock)
{
    uint16_t status;
    tIpcMessage sMessage;

    //
    // Package message to send
    //
    sMessage.ulcommand = ulCommand;
    sMessage.uladdress = ulAddress;
    sMessage.uldataw1 = ulDataW1;
    sMessage.uldataw2 = ulDataW2;

    //
    // Put Message into PutBuffer and set IPC INT flag
    //
    status = IpcPut (psController, &sMessage, bBlock);
    return status;
}

#if defined (CPU2)
//*****************************************************************************
//
//! Slave CPU Configures master R/W/Exe Access to Shared SARAM.
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param ulMask specifies the 32-bit mask for the GSxMSEL RAM control
//! register to indicate which GSx SARAM blocks the slave CPU is requesting
//! master access to.
//! \param usMaster specifies whether the CPU1 or CPU2 are given
//!  master access to the GSx blocks.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the slave CPU system to configure master R/W/Exe
//! access to the GSx SARAM blocks specified by the /e ulMask parameter.  The
//! function calls the \e IPCSetBits_Protected() or \e
//! IPCClearBits_Protected() functions, and therefore in the master CPU
//! application code, the corresponding functions should be called.
//! The \e bBlock parameter can be one of the following values: \b
//! ENABLE_BLOCKING or \b DISABLE_BLOCKING. The \e usMaster parameter can be
//! either: \b IPC_GSX_CPU2_MASTER or \b IPC_GSX_CPU1_MASTER. The \e ulMask
//! parameter can be any of the options: \b S0_ACCESS - \b S7_ACCESS.
//!
//! \return status of command (\b STATUS_PASS =success, \b STATUS_FAIL = error
//! because PutBuffer was full, command was not sent)
//
//*****************************************************************************
uint16_t
IPCReqMemAccess (volatile tIpcController *psController, uint32_t ulMask,
                     uint16_t usMaster, uint16_t bBlock)
{
    uint16_t status = STATUS_PASS;
    uint32_t GSxMSEL_REGaddress = (uint32_t)(&MemCfgRegs.GSxMSEL.all);

    if (usMaster == IPC_GSX_CPU2_MASTER)
    {
        if ((MemCfgRegs.GSxMSEL.all & ulMask) != ulMask)
        {
            status =
                IPCLtoRSetBits_Protected (psController, GSxMSEL_REGaddress,
                                          ulMask, IPC_LENGTH_32_BITS,
                                          bBlock);
        }
    }
    else if (usMaster == IPC_GSX_CPU1_MASTER)
    {
        if ((MemCfgRegs.GSxMSEL.all & ulMask) != 0)
        {
            status =
                IPCLtoRClearBits_Protected (psController, GSxMSEL_REGaddress,
                                            ulMask, IPC_LENGTH_32_BITS,
                                            bBlock);
        }
    }

    return status;
}
#endif

//*****************************************************************************
//
//! Responds to 16/32-bit data word write command the remote CPU system
//!
//! \param psMessage specifies the pointer to the message received from remote
//! CPU system which includes the 16/32-bit data word to write to the local CPU
//! address.
//!
//! This function will allow the local CPU system to write a 16/32-bit word
//! received from the remote CPU system to the address indicated in \e
//! *psMessage. In the event that the IPC_DATA_WRITE command was received as a
//! result of an IPC_DATA_READ command, this function will also clear the IPC
//! response flag tracking the read so other threads in the local CPU system
//! will be aware that the data is ready.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLDataWrite(tIpcMessage *psMessage)
{
    //
    // Data word length = dataw1 (15:0), responseFlag = valid only for IPC
    // flags 17-32
    //
    uint16_t length = (uint16_t) psMessage->uldataw1;
    uint32_t responseFlag = (psMessage->uldataw1) & 0xFFFF0000;

    //
    // Write 16/32-bit word to address
    //
    if (length == IPC_LENGTH_16_BITS)
    {
        *(uint16_t *)(psMessage->uladdress) = (uint16_t)psMessage->uldataw2;
    }
    else if (length == IPC_LENGTH_32_BITS)
    {
        *(uint32_t *)(psMessage->uladdress) = psMessage->uldataw2;
    }

    //
    // If data write command is in response to a data read command from remote
    // CPU to local CPU clear ResponseFlag, indicating read data from remote
    // CPU is ready.
    //
    IpcRegs.IPCCLR.all |= responseFlag;
}

//*****************************************************************************
//
//! Responds to 16/32-bit write-protected data word write command from
//! secondary CPU system
//!
//! \param psMessage specifies the pointer to the message received from the
//! secondary CPU system which includes the 16/32-bit data word to write to the
//! local CPU address.
//!
//! This function will allow the local CPU system to write a 16/32-bit word
//! received from the secondary CPU system to the write-protected address
//! indicated in \e *psMessage.
//! In the event that the IPC_DATA_WRITE_PROTECTED command was received as a
//! result of an IPC_DATA_READ_PROTECTED command, this function will also clear
//! the IPC response flag tracking the read so other threads in the local CPU
//! will be aware that the data is ready.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLDataWrite_Protected(tIpcMessage *psMessage)
{
    //
    // Data word length = dataw1 (15:0), responseFlag = valid only for IPC
    // flags 17-32
    //
    uint16_t length = (uint16_t) psMessage->uldataw1;
    uint32_t responseFlag = (psMessage->uldataw1) & 0xFFFF0000;

    //
    // Allow access to EALLOW-protected registers.
    //
    EALLOW;

    //
    // Write 16/32-bit word to EALLOW-protected address
    //
    if (length == IPC_LENGTH_16_BITS)
    {
        *(uint16_t *)(psMessage->uladdress) = (uint16_t)psMessage->uldataw2;
    }
    else if (length == IPC_LENGTH_32_BITS)
    {
        *(uint32_t *)(psMessage->uladdress) = psMessage->uldataw2;
    }

    //
    // Disable access to EALLOW-protected registers.
    //
    EDIS;

    //
    // If data write command is in response to a data read command from local
    // CPU to remote CPU, clear ResponseFlag, indicating read data from
    // secondary CPU is ready
    //
    IpcRegs.IPCCLR.all |= responseFlag;
}

//*****************************************************************************
//
//! Responds to 16/32-bit data word read command from remote CPU system.
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the remote CPU system to read a 16/32-bit data
//! word at the local CPU address specified in /e psMessage, and send a Write
//! command with the read data back to the local CPU system. It will also send
//! the Response Flag used to track the read back to the remote CPU.
//! The \e bBlock parameter can be one of the following values: \b
//! ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLDataRead(volatile tIpcController *psController, tIpcMessage *psMessage,
                uint16_t bBlock)
{
    unsigned long ulReaddata;
    uint16_t usLength;

    //
    // If data word length = 16-bits, read the 16-bit value at the given
    // address and cast as 32-bit word to send back to remote CPU.
    // If data word length = 32-bits, read the 32-bit value at the given
    // address.
    //
    usLength = (uint16_t)psMessage->uldataw1;

    if (usLength == IPC_LENGTH_16_BITS)
    {
        ulReaddata = (unsigned long)(*(volatile uint16_t *)psMessage->uladdress);
    }
    else if (usLength == IPC_LENGTH_32_BITS)
    {
        ulReaddata = *(unsigned long *)psMessage->uladdress;
    }

    //
    // Send a Write command to write the requested data to the remote CPU read
    // into address.
    // psMessage->uldataw2 contains remote CPU address where readdata will be
    // written.
    // psMessage->uldataw1 contains the read response flag in IPC flag 17-32.
    //
    IPCLtoRDataWrite(psController, psMessage->uldataw2, ulReaddata, usLength,
                     bBlock,(psMessage->uldataw1 & 0xFFFF0000));
}

//*****************************************************************************
//
//! Responds to 16/32-bit data word read command from remote CPU system.
//! to read into a write-protected word on the remote CPU system.
//!
//! \param psController specifies the address of a \e tIpcController instance
//! used to store information about the "Put" and "Get" circular buffers and
//! their respective indexes.
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//! \param bBlock specifies whether to allow function to block until PutBuffer
//! has a slot (1= wait until slot free, 0 = exit with STATUS_FAIL if no slot).
//!
//! This function will allow the remote CPU system to read a 16/32-bit data
//! word at the local CPU address specified in /e psMessage, and send a Write
//! Protected command with the read data back to the remote CPU system at a
//! write protected address. It will also send the Response Flag used to track
//! the read back to the remote CPU. The \e bBlock parameter can be one of the
//! following values: \b ENABLE_BLOCKING or \b DISABLE_BLOCKING.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLDataRead_Protected(volatile tIpcController *psController,
                          tIpcMessage *psMessage, uint16_t bBlock)
{
    unsigned long ulReaddata;
    uint16_t usLength;

    //
    // If data word length = 16-bits, read the 16-bit value at the given
    // address and cast as 32-bit word to send back to remote CPU.
    // If data word length = 32-bits, read the 32-bit value at the given
    // address.
    //
    usLength = (uint16_t)psMessage->uldataw1;

    if (usLength == IPC_LENGTH_16_BITS)
    {
        ulReaddata = (unsigned long)(*(volatile uint16_t *)psMessage->uladdress);
    }
    else if (usLength == IPC_LENGTH_32_BITS)
    {
        ulReaddata = *(unsigned long *)psMessage->uladdress;
    }

    //
    // Send a Write command to write the requested data to the remote CPU read
    // into address.
    // psMessage->uldataw2 contains remote CPU address where readdata will be
    // written.
    // psMessage->uldataw1 contains the read response flag in IPC flag 17-32.
    //
    IPCLtoRDataWrite_Protected(psController, psMessage->uldataw2, ulReaddata,
                               usLength, bBlock,
                               (psMessage->uldataw1 & 0xFFFF0000));
}

//*****************************************************************************
//
//! Sets the designated bits in a 16/32-bit data word at a local CPU system
//! address
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will allow the remote CPU system to set the bits in a
//! 16/32-bit word on the local CPU system via a local CPU address and mask
//! passed in via the \e psMessage.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLSetBits(tIpcMessage *psMessage)
{
    uint16_t usLength;

    //
    // Determine length of word at psMessage->uladdress and then set bits based
    // on either the 16-bit or 32-bit bit-mask in psMessage->uldataw2.
    // (16-bit length ignores upper 16-bits of psMessage->uldataw2)
    //
    usLength = (uint16_t)psMessage->uldataw1;

    if (usLength == IPC_LENGTH_16_BITS)
    {
        *(volatile uint16_t*)psMessage->uladdress |=
                                                (uint16_t) psMessage->uldataw2;
    }
    else if (usLength == IPC_LENGTH_32_BITS)
    {
        *(volatile unsigned long *)psMessage->uladdress |=  psMessage->uldataw2;
    }
}

//*****************************************************************************
//
//! Sets the designated bits in a 16/32-bit write-protected data word at a
//! local CPU system address
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will allow the remote CPU system to set the bits in a write-
//! protected 16/32-bit word on the local CPU system via a local CPU address
//! and mask passed in via the \e psMessage.
//!
//! \return None
//
//*****************************************************************************
void
IPCRtoLSetBits_Protected(tIpcMessage *psMessage)
{
    uint16_t usLength;

    //
    // Allow access to EALLOW-protected registers.
    //
    EALLOW;

    //
    // Determine length of word at psMessage->uladdress and then set bits based
    // on either the 16-bit or 32-bit bit-mask in psMessage->uldataw2.
    // (16-bit length ignores upper 16-bits of psMessage->uldataw2)
    //
    usLength = (uint16_t)psMessage->uldataw1;

    if (usLength == IPC_LENGTH_16_BITS)
    {
        *(volatile uint16_t*)psMessage->uladdress |=
                                                (uint16_t) psMessage->uldataw2;
    }
    else if (usLength == IPC_LENGTH_32_BITS)
    {
        *(volatile unsigned long *)psMessage->uladdress |= psMessage->uldataw2;
    }

    //
    // Disable access to EALLOW-protected registers.
    //
    EDIS;
}

//*****************************************************************************
//
//! Clears the designated bits in a 32-bit data word at a local CPU system
//! address
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will allow the remote CPU system to clear the bits in a
//! 16/32-bit word on the local CPU system via a local CPU address and mask
//! passed in via the \e psMessage.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLClearBits(tIpcMessage *psMessage)
{
    uint16_t usLength;

    //
    // Determine length of word at psMessage->uladdress and then clear bits
    // based on
    // either the 16-bit or 32-bit bit-mask in psMessage->uldataw2.
    // (16-bit length ignores upper 16-bits of psMessage->uldataw2)
    //
    usLength = (uint16_t)psMessage->uldataw1;

    if (usLength == IPC_LENGTH_16_BITS)
    {
        *(volatile uint16_t*)psMessage->uladdress &=
            ~((uint16_t) psMessage->uldataw2);
    }
    else if (usLength == IPC_LENGTH_32_BITS)
    {
        *(volatile unsigned long *)psMessage->uladdress &=
            ~(psMessage->uldataw2);
    }
}

//*****************************************************************************
//
//! Clears the designated bits in a write-protected 16/32-bit data word at a
//! local CPU system address
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will allow the secondary CPU system to clear the bits in a
//! 16/32-bit write-protected  word on the local CPU system via a local
//! CPU address and mask passed in via the \e psMessage.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLClearBits_Protected(tIpcMessage *psMessage)
{
    uint16_t usLength;

    //
    // Allow access to EALLOW-protected registers.
    //
    EALLOW;

    //
    // Determine length of word at psMessage->uladdress and then clear bits
    // based on
    // either the 16-bit or 32-bit bit-mask in psMessage->uldataw2.
    // (16-bit length ignores upper 16-bits of psMessage->uldataw2)
    //
    usLength = (uint16_t)psMessage->uldataw1;

    if (usLength == IPC_LENGTH_16_BITS)
    {
        *(volatile uint16_t*)psMessage->uladdress &=
            ~((uint16_t) psMessage->uldataw2);
    }
    else if (usLength == IPC_LENGTH_32_BITS)
    {
        *(volatile unsigned long *)psMessage->uladdress &=
            ~(psMessage->uldataw2);
    }

    //
    // Disable access to EALLOW-protected registers.
    //
    EDIS;
}

//*****************************************************************************
//
//! Reads a block of data from a remote CPU system address and stores into
//! shared RAM
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will respond to the remote CPU system request to read a block
//! of data from the local control system, by reading the data and placing that
//! data into the shared RAM location specified in \e psMessage.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLBlockRead(tIpcMessage *psMessage)
{

    uint16_t usLength;
    volatile uint16_t* pusRAddress;
    volatile uint16_t* pusWAddress;
    uint16_t usIndex;

    pusRAddress = (volatile uint16_t *)psMessage->uladdress;
    pusWAddress = (volatile uint16_t *)psMessage->uldataw2;
    usLength = (uint16_t)psMessage->uldataw1;

    for (usIndex=0; usIndex<usLength; usIndex++)
    {
        *pusWAddress = *pusRAddress;
        pusWAddress += 1;
        pusRAddress += 1;
    }

    IpcRegs.IPCACK.all |= (psMessage->uldataw1 & 0xFFFF0000);
}

//*****************************************************************************
//
//! Writes a block of data to a local CPU system address from shared RAM
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will write a block of data to an address on the local CPU
//! system.
//! The data is first written by the remote CPU to shared RAM. This function
//! reads the shared RAM location, word size (16- or 32-bit), and block size
//! from \e psMessage and writes the block to the local address specified
//! in \e psMessage.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLBlockWrite(tIpcMessage *psMessage)
{
    uint16_t usLength;
    uint16_t usWLength;
    uint16_t usIndex;

    usLength = (uint16_t)psMessage->uldataw1;
    usWLength = (uint16_t)((psMessage->uldataw1)>>16);

    //
    // Determine data word access size to write to data block.
    //
    if (usWLength == IPC_LENGTH_16_BITS)
    {
        volatile uint16_t *pusWAddress = (volatile uint16_t *)psMessage->uladdress;
        volatile uint16_t *pusRAddress = (volatile uint16_t *)psMessage->uldataw2;
        for (usIndex=0; usIndex<usLength; usIndex++)
        {
            *pusWAddress = *pusRAddress;
            pusWAddress += 1;
            pusRAddress += 1;
        }
    } else if (usWLength == IPC_LENGTH_32_BITS)
    {
        volatile unsigned long *pulWAddress =
            (volatile unsigned long *)psMessage->uladdress;
        volatile unsigned long *pulRAddress =
            (volatile unsigned long *)psMessage->uldataw2;

        for (usIndex=0; usIndex<usLength; usIndex++)
        {
            *pulWAddress = *pulRAddress;
            pulWAddress += 1;
            pulRAddress += 1;
        }
    }
}

//*****************************************************************************
//
//! Writes a block of data to a local CPU system write-protected address from
//! shared RAM
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will write a block of data to a write-protected group of
//! addresses on the local CPU system. The data is first written by the
//! remote CPU to shared RAM. This function reads the shared RAM location,
//! word size (16- or 32-bit), and block size from \e psMessage  and writes the
//! block to the local address specified in \e psMessage.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLBlockWrite_Protected(tIpcMessage *psMessage)
{
    uint16_t usLength;
    uint16_t usWLength;
    uint16_t usIndex;

    //
    // Allow access to EALLOW-protected registers.
    //
    EALLOW;

    usLength = (uint16_t)psMessage->uldataw1;
    usWLength = (uint16_t)((psMessage->uldataw1)>>16);

    //
    // Determine data word access size to write to data block.
    // (Writes registers accessible via APB bus must be 32-bits wide)
    //
    if (usWLength == IPC_LENGTH_16_BITS)
    {
        volatile uint16_t *pusWAddress = (volatile uint16_t *)psMessage->uladdress;
        volatile uint16_t *pusRAddress = (volatile uint16_t *)psMessage->uldataw2;
        for (usIndex=0; usIndex<usLength; usIndex++)
        {
            *pusWAddress = *pusRAddress;
            pusWAddress += 1;
            pusRAddress += 1;
        }
    } else if (usWLength == IPC_LENGTH_32_BITS)
    {
        volatile unsigned long *pulWAddress =
            (volatile unsigned long *)psMessage->uladdress;
        volatile unsigned long *pulRAddress =
            (volatile unsigned long *)psMessage->uldataw2;

        for (usIndex=0; usIndex<usLength; usIndex++)
        {
            *pulWAddress = *pulRAddress;
            pulWAddress += 1;
            pulRAddress += 1;
        }
    }

    //
    // Disable access to EALLOW-protected registers.
    //
    EDIS;
}

//*****************************************************************************
//
//! Calls a local function with a single optional parameter.
//!
//! \param psMessage specifies the pointer to the message received from the
//! remote CPU system.
//!
//! This function will allow the remote CPU system to call a local CPU function
//! with a single optional parameter. There is no return value from the
//! executed function.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLFunctionCall(tIpcMessage *psMessage)
{
    //
    // Executes function call with parameter at given address.
    //
    tfIpcFuncCall func_call = (tfIpcFuncCall)psMessage->uladdress;
    func_call(psMessage->uldataw1);
}

//*****************************************************************************
// Close the Doxygen group.
//! @}
//*****************************************************************************


