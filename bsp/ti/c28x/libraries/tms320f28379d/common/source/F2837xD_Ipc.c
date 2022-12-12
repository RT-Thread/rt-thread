//###########################################################################
//
// FILE:    F2837xD_Ipc.c
//
// TITLE:    Inter-Processor Communication module support functions
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
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include <string.h>

//
// InitIpc - Initialize all IPC registers and clear all flags
//
void InitIpc()
{
    //
    //Clear sent flags. Received flags must not be cleared locally
    //to handle the case where the remote CPU starts executing first.
    //In this case, a remote flag could be sent correctly and be
    //incorrectly cleared by this function. Unfortunately, we're
    //still left with a startup synchronization problem if the
    //remote CPU has flags left over from a previous run. There's
    //probably a better way of handling this.
    //
    IpcRegs.IPCCLR.all = 0xFFFFFFFF;

    //
    //Clear commands
    //
    IpcRegs.IPCSENDCOM = 0;
    IpcRegs.IPCSENDADDR = 0;
    IpcRegs.IPCSENDDATA = 0;
    IpcRegs.IPCLOCALREPLY = 0;

    //
    //Clear boot status and pump semaphore
    //
    #if defined(CPU1)
        IpcRegs.IPCBOOTMODE = 0;
    #elif defined(CPU2)
        IpcRegs.IPCBOOTSTS = 0;
    #endif
    ReleaseFlashPump();
}

//
// ReadIpcTimer - Read the current IPC timer value. The low register must be
//                read first to latch a value in the high register.
//
unsigned long long ReadIpcTimer()
{
    Uint32 low, high;

    low = IpcRegs.IPCCOUNTERL;
    high = IpcRegs.IPCCOUNTERH;
    return ((unsigned long long)high << 32) | (unsigned long long)low;
}

//
// SendIpcData - Copy data into the IPC send message RAM for this CPU and set
//               a flag. If the specified 16-bit word length is greater than
//               the size of the message RAM, the data is truncated.
//
void SendIpcData(void *data, Uint16 word_length, Uint16 flag)
{
    word_length = (word_length < MSG_RAM_SIZE) ? word_length : MSG_RAM_SIZE;

    memcpy(SEND_MSG_RAM, data, word_length);

    if (flag != NO_IPC_FLAG)
    {
        SendIpcFlag(flag);
    }
}

//
// RecvIpcData - Copy data out of the IPC receive message RAM for this CPU. If
//               the specified 16-bit word length is greater than the size of
//               the message RAM, the data is truncated.
//
void RecvIpcData(void *recv_buf, Uint16 word_length)
{
    word_length = (word_length < MSG_RAM_SIZE) ? word_length : MSG_RAM_SIZE;
    memcpy(recv_buf, RECV_MSG_RAM, word_length);
}

//
// FillIpcSendData - Fill the IPC send message RAM for this CPU with a constant
//                   value
//
void FillIpcSendData(Uint16 fill_data)
{
    memset(SEND_MSG_RAM, fill_data, MSG_RAM_SIZE);
}

//
// SendIpcCommand - Write the send command, address, and data registers with
//                  the specified values, then set an IPC flag.
//
void SendIpcCommand(Uint32 command, Uint32 address, Uint32 data, Uint16 flag)
{
    IpcRegs.IPCSENDCOM = command;
    IpcRegs.IPCSENDADDR = address;
    IpcRegs.IPCSENDDATA = data;

    if (flag != NO_IPC_FLAG)
    {
        SendIpcFlag(flag);
    }
}

//
// SendIpcFlag - Set an IPC flag bit for the other CPU. Flags 0-3 will generate
//               PIE interrupts.
//
void SendIpcFlag(Uint16 flag)
{
    IpcRegs.IPCSET.all = 1UL << flag;
}

//
// AckIpcFlag - Acknowledge/clear a received IPC flag
//
void AckIpcFlag(Uint16 flag)
{
    IpcRegs.IPCACK.all = 1UL << flag;
}

//
// CancelIpcFlag - Clear a sent IPC flag bit before the other CPU acknowledges
//                 it. You will normally never use this function. To clear a
//                 received flag, call AckIpcFlag() instead.
//
void CancelIpcFlag(Uint16 flag)
{
    IpcRegs.IPCCLR.all = 1UL << flag;
}

//
// WaitForIpcFlag - Wait for any IPC flag in the specified mask to be set.
//                  WARNING: If you use this function to wait for an IPC
//                  interrupt, you must not clear the IPC flag in the interrupt
//                  handler. Otherwise, this function will never return.
//
void WaitForIpcFlag(Uint16 flag)
{
    //
    //WARNING: Don't use this function to wait for an IPC interrupt!
    //
    while ((IpcRegs.IPCSTS.all & (1UL << flag)) == 0x00000000) {;}
}

//
// WaitForIpcAck - Wait for any IPC flag in the specified mask to be
//                 acknowledged.
//
void WaitForIpcAck(Uint16 flag)
{
    while ((IpcRegs.IPCFLG.all & (1UL << flag)) != 0x00000000) {;}
}

//
// IpcSync - Synchronize the two CPUs. Neither CPU will return from this
//           function call before the other one enters it. Must be called with
//           the same flag number on both CPUs.
//
void IpcSync(Uint16 flag)
{
    SendIpcFlag(flag);
    WaitForIpcFlag(flag);
    AckIpcFlag(flag);
    WaitForIpcAck(flag);
}

//
// End of file
//
