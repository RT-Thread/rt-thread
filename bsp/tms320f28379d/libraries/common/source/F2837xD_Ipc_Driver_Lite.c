//###########################################################################
//
// FILE:   F2837xD_Ipc_Driver_Lite.c
//
// TITLE:  F2837xD Inter-Processor Communication (IPC) Lite API Driver
//         Functions.
//
// DESCRIPTION:
//         API functions for inter-processor communications between
//         CPU1 control system and CPU2 control system (Lite version). The IPC
//         Lite functions only allow for basic functions such as data writes,
//         reads, bit setting, and bit clearing.  The Lite functions do not
//         require the usage of the MSG RAM's or shared memories and can only
//         be used with a single IPC interrupt channel.  Commands can only
//         be processed one at a time without queuing.
//         The driver functions in this file are available only as
//         sample functions for application development.  Due to the generic
//         nature of these functions and the cycle overhead inherent to a
//         function call, the code is not intended to be used in cases where
//         maximum efficiency is required in a system.
//
// NOTE:   This source code is used by both CPUs. That is both CPU1 and CPU2
//         cores use this code.
//         The active debug CPU will be referred to as Local CPU and the other
//         CPU will be referred to as Remote CPU.
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
//! \addtogroup ipc_lite_api IPC-Lite API Drivers
//! @{
//*****************************************************************************
#include "F2837xD_device.h"
#include "F2837xD_Ipc_drivers.h"

//
// Function Prototypes
//
void DelayLoop (void);

//*****************************************************************************
//
//! Reads single word data result of Local to Remote IPC command
//!
//! \param pvData is a pointer to the 16/32-bit variable where the result data
//! will be stored.
//! \param usLength designates 16- or 32-bit read.
//! \param ulStatusFlag indicates the Local to Remote CPU Flag number mask used
//!  to report the status of the command sent back from the Remote CPU. If
//!  a status flag was not used with the command call, set this parameter to 0.
//!
//! Allows the caller to read the 16/32-bit data result of non-blocking IPC
//! functions from the IPCREMOTEREPLY register if the status flag is cleared
//! indicating the IPC command was successfully interpreted. If the status flag
//! is not cleared, the command was not recognized, and the function will
//! return STATUS_FAIL. To determine what data is read from a call to this
//! function, see the descriptions of the non-blocking IPC functions.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The  \e ulStatusFlag parameter
//! accepts any of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//! The function returns \b STATUS_PASS or \b STATUS_FAIL.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRGetResult (void *pvData, uint16_t usLength, uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // If Remote System never acknowledged Status Task, indicates command
    // failure.
    //
    if (IpcRegs.IPCFLG.all & ulStatusFlag)
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        //
        // Read data.
        //
        if (usLength == IPC_LENGTH_16_BITS)
        {
            *(uint16_t *)pvData = IpcRegs.IPCREMOTEREPLY;
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            *(uint32_t *)pvData =  IpcRegs.IPCREMOTEREPLY;
        }

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Reads either a 16- or 32-bit data word from the remote CPU System address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//!        indicate a command is being sent.
//! \param ulAddress specifies the remote address to read from
//! \param usLength designates 16- or 32-bit read (1 = 16-bit, 2 = 32-bit)
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//!  report the status of the command sent back from the remote system.
//!
//! This function will allow the Local CPU System to read 16/32-bit data from
//! the Remote CPU System into the IPCREMOTEREPLY register. After calling this
//! function, a call to \e IPCLiteLtoRGetResult() will read the data value in
//! the IPCREMOTEREPLY register into a 16- or 32-bit variable in the local CPU
//! application.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRDataRead(uint32_t ulFlag, uint32_t ulAddress, uint16_t usLength,
                    uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        //
        // Set up read command, address, and word length.
        //
        if (usLength == IPC_LENGTH_16_BITS)
        {
            IpcRegs.IPCSENDCOM = IPC_DATA_READ_16;
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            IpcRegs.IPCSENDCOM = IPC_DATA_READ_32;
        }
        IpcRegs.IPCSENDADDR = ulAddress;

        //
        // Force IPC event on selected request task and enable status-checking.
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Sets the designated bits in a 16/32-bit data word at the remote CPU system
//! address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//!        indicate a command is being sent.
//! \param ulAddress specifies the Remote address to write to.
//! \param ulMask specifies the 16/32-bit mask for bits which should be set at
//!  remote ulAddress. For 16-bit mask, only the lower 16-bits of ulMask are
//!  considered.
//! \param usLength specifies the length of the \e ulMask (1 = 16-bit, 2 =
//! 32-bit).
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//!        report the status of the command sent back from the Remote system.
//!
//! This function will allow the Local CPU system to set bits specified by the
//! \e usMask variable in a 16/32-bit word on the Remote CPU system. The data
//! word at /e ulAddress after the set bits command is then read into the
//! IPCREMOTEREPLY register. After calling this function, a call to \e
//! IPCLiteLtoRGetResult() will read the data value in the IPCREMOTEREPLY
//! register into a 16/32-bit variable in the Local CPU application.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRSetBits(uint32_t ulFlag, uint32_t ulAddress, uint32_t ulMask,
                   uint16_t usLength, uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        if (usLength == IPC_LENGTH_16_BITS)
        {
            //
            // Set up 16-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_SET_BITS_16;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask & (0x0000FFFF);
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            //
            // Set up 32-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_SET_BITS_32;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask;
        }

        //
        // Force IPC event on selected request task and enable status-checking.
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Sets the designated bits in a 16/32-bit write-protected data word at
//! the Remote CPU system address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//!        indicate a command is being sent.
//! \param ulAddress specifies the Remote CPU write-protected address to write
//!        to.
//! \param ulMask specifies the 16/32-bit mask for bits which should be set at
//!  Remote CPU ulAddress.For 16-bit mask, only the lower 16-bits of ulMask are
//!  considered.
//! \param usLength specifies the length of the \e ulMask (1 = 16-bit, 2 =
//! 32-bit).
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//!        report the status of the command sent back from the Master system.
//!
//! This function will allow the Local CPU system to set bits specified by the
//! \e usMask variable in a write-protected 16/32-bit word on the REmote CPU
//! system.
//! The data word at /e ulAddress after the set bits command is then read into
//! the IPCREMOTEREPLY register. After calling this function, a call to
//! \e IPCLiteLtoRGetResult() will read the data value in the IPCREMOTEREPLY
//! register into a 16/32-bit variable in the Local application.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRSetBits_Protected (uint32_t ulFlag, uint32_t ulAddress,
                              uint32_t ulMask, uint16_t usLength,
                              uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        if (usLength == IPC_LENGTH_16_BITS)
        {
            //
            // Set up 16-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_SET_BITS_16_PROTECTED;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask & (0x0000FFFF);
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            //
            // Set up 32-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_SET_BITS_32_PROTECTED;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask;
        }

        //
        // Force IPC event on selected request task and enable status-checking.
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Sets the designated bits in a 16/32-bit data word at the remote CPU system
//! address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//!        indicate a command is being sent.
//! \param ulAddress specifies the Remote CPU address to write to.
//! \param ulMask specifies the 16/32-bit mask for bits which should be set at
//! the remote CPU ulAddress. (For 16-bit mask, only the lower 16-bits of
//! ulMask are considered.
//! \param usLength specifies the length of the \e ulMask (1 = 16-bit, 2 =
//! 32-bit).
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//! report the status of the command sent back from the Master system.
//!
//! This function will allow the Local CPU system to set bits specified by the
//! \e usMask variable in a 16/32-bit word on the Remote CPU system. The data
//! word at /e ulAddress after the set bits command is then read into the
//! IPCREMOTEREPLY register. After calling this function, a call to \e
//! IPCLiteLtoRGetResult() will read the data value in the IPCREMOTEREPLY
//! register into a 16/32-bit variable in the Local CPU application.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRClearBits(uint32_t ulFlag, uint32_t ulAddress, uint32_t ulMask,
                     uint16_t usLength, uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        if (usLength == IPC_LENGTH_16_BITS)
        {
            //
            // Set up 16-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_CLEAR_BITS_16;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask & (0x0000FFFF);
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            //
            // Set up 32-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_CLEAR_BITS_32;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask;
        }

        //
        // Force IPC event on selected request task and enable status-checking.
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Clears the designated bits in a 16/32-bit write-protected data word at
//! Remote CPU system address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulAddress specifies the Remote CPU write-protected address to write
//! to.
//! \param ulMask specifies the 16/32-bit mask for bits which should be cleared
//! at Remote CPU ulAddress.For 16-bit mask, only the lower 16-bits of ulMask
//! are considered.
//! \param usLength specifies the length of the \e ulMask (1 = 16-bit, 2 =
//! 32-bit).
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//! report the status of the command sent back from the Master system.
//!
//! This function will allow the Local CPU system to clear bits specified by
//! the \e usMask variable in a write-protected 16/32-bit word on the Remote
//! CPU system.
//! The data word at /e ulAddress after the clear bits command is then read
//! into the IPCREMOTEREPLY register. After calling this function, a call to
//! \e IPCLiteLtoRGetResult() will read the data value in the IPCREMOTEREPLY
//! register into a 16/32-bit variable in the Local CPU application.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRClearBits_Protected (uint32_t ulFlag, uint32_t ulAddress,
                                uint32_t ulMask, uint16_t usLength,
                                uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        if (usLength == IPC_LENGTH_16_BITS)
        {
            //
            // Set up 16-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_CLEAR_BITS_16_PROTECTED;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask & (0x0000FFFF);
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            //
            // Set up 32-bit set bits command, address, and mask.
            //
            IpcRegs.IPCSENDCOM = IPC_CLEAR_BITS_32_PROTECTED;
            IpcRegs.IPCSENDADDR = ulAddress;
            IpcRegs.IPCSENDDATA = ulMask;
        }

        //
        // Force IPC event on selected request task and enable status-checking.
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Writes a 16/32-bit data word to Remote CPU System address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulAddress specifies the Remote CPU address to write to
//! \param ulData specifies the 16/32-bit word which will be written.
//! For 16-bit words, only the lower 16-bits of ulData will be considered by
//! the master system.
//! \param usLength is the length of the word to write (0 = 16-bits, 1 =
//! 32-bits)
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//! report the status of the command sent back from the Remote CPU  system.
//!
//! This function will allow the Local CPU System to write a 16/32-bit word
//! via the \e ulData variable to an address on the Remote CPU System.
//! The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRDataWrite(uint32_t ulFlag, uint32_t ulAddress, uint32_t ulData,
                     uint16_t usLength, uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        //
        // Set up data write command, address, and data. For 16-bit write,
        // Master system will look at lower 16-bits only.
        //
        if (usLength == IPC_LENGTH_16_BITS)
        {
            IpcRegs.IPCSENDCOM = IPC_DATA_WRITE_16;
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            IpcRegs.IPCSENDCOM = IPC_DATA_WRITE_32;
        }
        IpcRegs.IPCSENDADDR = ulAddress;
        IpcRegs.IPCSENDDATA = ulData;

        //
        // Force IPC event on selected request task and enable status-checking
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Writes a 16/32-bit data word to a protected Remote CPU System address
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulAddress specifies the Remote CPU address to write to
//! \param ulData specifies the 16/32-bit word which will be written.
//! For 16-bit words, only the lower 16-bits of ulData will be considered by
//! the master system.
//! \param usLength is the length of the word to write (0 = 16-bits, 1 =
//! 32-bits)
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//! report the status of the command sent back from the Master  system.
//!
//! This function will allow the Local CPU System to write a 16/32-bit word
//! via the \e ulData variable to a write-protected address on the Remote CPU
//! System. The \e usLength parameter accepts the following values: \b
//! IPC_LENGTH_16_BITS or \b IPC_LENGTH_32_BITS. The \e ulStatusFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and \b
//! NO_FLAG. The function returns \b STATUS_PASS if the command is successful
//! or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRDataWrite_Protected(uint32_t ulFlag, uint32_t ulAddress,
                               uint32_t ulData, uint16_t usLength,
                               uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Local to Remote request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        //
        // Set up data write command, address, and data. For 16-bit write, Master
        // system will look at lower 16-bits only.
        //
        if (usLength == IPC_LENGTH_16_BITS)
        {
            IpcRegs.IPCSENDCOM = IPC_DATA_WRITE_16_PROTECTED;
        }
        else if (usLength == IPC_LENGTH_32_BITS)
        {
            IpcRegs.IPCSENDCOM = IPC_DATA_WRITE_32_PROTECTED;
        }
        IpcRegs.IPCSENDADDR = ulAddress;
        IpcRegs.IPCSENDDATA = ulData;

        //
        // Force IPC event on selected request task and enable status-checking
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Calls a Remote CPU function with 1 optional parameter and an optional
//! return value.
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulAddress specifies the Remote CPU function address
//! \param ulParam specifies the 32-bit optional parameter value
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//! report the status of the command sent back from the control  system.
//!
//! This function will allow the Local CPU system to call a function on the
//! Remote CPU. The \e ulParam variable is a single optional 32-bit parameter
//! to pass to the function. The \e ulFlag parameter accepts any one of the
//! flag values \b IPC_FLAG1 - \b IPC_FLAG32. The \e ulStatusFlag parameter
//! accepts any other one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32
//! and \b NO_FLAG. The function returns \b STATUS_PASS if the command is
//! successful or \b STATUS_FAIL if the request or status flags are unavailable.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteLtoRFunctionCall(uint32_t ulFlag, uint32_t ulAddress, uint32_t ulParam,
                        uint32_t ulStatusFlag)
{
    uint16_t returnStatus;

    //
    // Return false if IPC Remote to Local request or status flags are not
    // available.
    //
    if (IpcRegs.IPCFLG.all & (ulFlag | ulStatusFlag))
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        //
        // Set up function call command, address, and parameter.
        //
        IpcRegs.IPCSENDCOM = IPC_FUNC_CALL;
        IpcRegs.IPCSENDADDR = ulAddress;
        IpcRegs.IPCSENDDATA = ulParam;

        //
        // Force IPC event on selected request task and enable status-checking
        //
        IpcRegs.IPCSET.all |= (ulFlag | ulStatusFlag);

        returnStatus = STATUS_PASS;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Slave Requests Master R/W/Exe Access to Shared SARAM.
//!
//! \param ulFlag specifies Local to Remote IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulMask specifies the 32-bit mask for the GSxMEMSEL RAM control
//! register to indicate which GSx SARAM blocks the Slave is requesting master
//! access to.
//! \param ulMaster specifies whether CPU1 or CPU2 should be the master of the
//! GSx RAM.
//! \param ulStatusFlag indicates the Local to Remote Flag number mask used to
//! report the status of the command sent back from the Master  system.
//!
//! This function will allow the slave CPU System to request slave or master
//! mastership of any of the GSx Shared SARAM blocks.
//! The \e ulMaster parameter accepts the following values:
//! \b IPC_GSX_CPU2_MASTER or \b IPC_GSX_CPU1_MASTER. The \e ulStatusFlag
//! parameter accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32
//! and \b NO_FLAG. The function returns \b STATUS_PASS if the command is
//! successful or \b STATUS_FAIL if the request or status flags are unavailable.
//! \note This function calls the \e IPCLiteLtoRSetBits_Protected() or the
//! \e IPCLiteLtoRClearBits_Protected function, and therefore in order to
//! process this function, the above 2 functions should be ready to be called
//! on the master system to process this command.
//!
//! \return status of command (0=success, 1=error)
//
//*****************************************************************************
uint16_t
IPCLiteReqMemAccess (uint32_t ulFlag, uint32_t ulMask, uint16_t ulMaster,
                     uint32_t ulStatusFlag)
{
    uint16_t status;
    uint32_t GSxMSEL_REGaddress = (uint32_t)(&MemCfgRegs.GSxMSEL.all);
    if (ulMaster == IPC_GSX_CPU2_MASTER)
    {
        status =
            IPCLiteLtoRSetBits_Protected (ulFlag, GSxMSEL_REGaddress, ulMask,
                                          IPC_LENGTH_32_BITS,
                                          ulStatusFlag);
    }
    else if (ulMaster == IPC_GSX_CPU1_MASTER)
    {
        status =
            IPCLiteLtoRClearBits_Protected (ulFlag, GSxMSEL_REGaddress, ulMask,
                                            IPC_LENGTH_32_BITS,
                                            ulStatusFlag);
    }

    return status;
}

//*****************************************************************************
//
//! Reads either a 16- or 32-bit data word from the Local CPU system address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control  system.
//!
//! This function will allow the Remote CPU system to read 16/32-bit data from
//! the Local CPU system. The \e ulFlag parameter accepts any one of the
//! flag values \b IPC_FLAG1 - \b IPC_FLAG32, and the \e ulStatusFlag parameter
//! accepts any other one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and
//! \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLDataRead(uint32_t ulFlag, uint32_t ulStatusFlag)
{

    uint32_t* pulRAddress;
    uint16_t* pusRAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command and data length are correct for this function:
    // Then read from requested address and write 16/32-bit data
    // to IPCLOCALREPLY. Acknowledge the status flag
    // and the task flag.
    //
    if (IpcRegs.IPCRECVCOM == IPC_DATA_READ_16)
    {
        //
        // Perform 16-bit read.
        //
        pusRAddress = (uint16_t *)IpcRegs.IPCRECVADDR;
        IpcRegs.IPCLOCALREPLY = (uint32_t)(*pusRAddress);
        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_DATA_READ_32)
    {
        pulRAddress = (uint32_t *)IpcRegs.IPCRECVADDR;
        IpcRegs.IPCLOCALREPLY = *pulRAddress;
        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }

    //
    // Otherwise, only acknowledge the task flag.
    //(Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }
}

//*****************************************************************************
//
//! Sets the designated bits in a 16/32-bit data word at the Local CPU system
//! address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to set bits specified by a
//! mask variable in a 16/32-bit word on the Local CPU system, and then read
//! back the word into the IPCLOCALREPLY register. The \e ulFlag parameter
//! accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32, and the
//! \e ulStatusFlag parameter accepts any other one of the flag values \b
//! IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLSetBits(uint32_t ulFlag, uint32_t ulStatusFlag)
{

    uint16_t* pusAddress;
    uint32_t* pulAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then set the mask bits at the requested address
    // and write back the 16/32-bit data to IPCLOCALREPLY.
    // Acknowledge the status flag and the task flag.
    //
    if (IpcRegs.IPCRECVCOM == IPC_SET_BITS_16)
    {
        pusAddress = (uint16_t *)IpcRegs.IPCRECVADDR;;
        *pusAddress |= (uint16_t)IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pusAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_SET_BITS_32)
    {
        pulAddress = (uint32_t *)IpcRegs.IPCRECVADDR;;
        *pulAddress |= (uint32_t)IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = *pulAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }

    //
    // Otherwise, only acknowledge the task flag.
    // (Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }
}

//*****************************************************************************
//
//! Sets the designated bits in a 16-bit data word at the Local CPU system
//! write-protected address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to set bits specified by a
//! mask variable in a write-protected 16/32-bit word on the Local CPU system,
//! and then read back the word into the IPCLOCALREPLY register. The \e ulFlag
//! parameter accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32,
//! and the \e ulStatusFlag parameter accepts any other one of the flag values
//! \b IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLSetBits_Protected (uint32_t ulFlag, uint32_t ulStatusFlag)
{

    uint16_t* pusAddress;
    uint32_t* pulAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then enable write access with EALLOW and
    // set the mask bits at the requested address.
    // Write back the 16-bit data to IPCLOCALREPLY.
    // Restore write-protection with EDIS.
    // Acknowledge the status flag and the task flag.
    //

    EALLOW;

    if (IpcRegs.IPCRECVCOM == IPC_SET_BITS_16_PROTECTED)
    {
        pusAddress = (uint16_t *)IpcRegs.IPCRECVADDR;
        *pusAddress |= (uint16_t)IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pusAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_SET_BITS_32_PROTECTED)
    {
        pulAddress = (uint32_t *)IpcRegs.IPCRECVADDR;
        *pulAddress |= (uint32_t)IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = *pulAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }

    //
    // Otherwise, only acknowledge the task flag.
    //(Indicates to the Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }

    EDIS;
}

//*****************************************************************************
//
//! Clears the designated bits in a 16/32-bit data word at Local CPU system
//! address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to clear bits specified by a
//! mask variable in a 16/32-bit word on the Local CPU system, and then read
//! back the word into the IPCLOCALREPLY register. The \e ulFlag
//! parameter accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32,
//! and the \e ulStatusFlag parameter accepts any other one of the flag values
//! \b IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLClearBits(uint32_t ulFlag, uint32_t ulStatusFlag)
{
    uint16_t* pusAddress;
    uint32_t* pulAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then clear the mask bits at the requested address
    // and write back the 16/32-bit data to IPCLOCALREPLY.
    // Acknowledge the status flag and the task flag.
    //
    if (IpcRegs.IPCRECVCOM == IPC_CLEAR_BITS_16)
    {
        pusAddress = (uint16_t *)IpcRegs.IPCRECVADDR;;
        *pusAddress &= ~((uint16_t)IpcRegs.IPCRECVDATA);
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pusAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_CLEAR_BITS_32)
    {
        pulAddress = (uint32_t *)IpcRegs.IPCRECVADDR;
        *pulAddress &= ~((uint32_t)IpcRegs.IPCRECVDATA);
        IpcRegs.IPCLOCALREPLY = *pulAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }

    //
    // Otherwise, only acknowledge the task flag.
    // (Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }
}

//*****************************************************************************
//
//! Clears the designated bits in a 16/32-bit data word at the Local CPU system
//! write-protected address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to clear bits specified by a
//! mask variable in a 16/32-bit word on the Local CPU system, and then read
//! back the word into the IPCLOCALREPLY register. The \e ulFlag
//! parameter accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32,
//! and the \e ulStatusFlag parameter accepts any other one of the flag values
//! \b IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLClearBits_Protected (uint32_t ulFlag, uint32_t ulStatusFlag)
{
    uint16_t* pusAddress;
    uint32_t* pulAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then enable write access with EALLOW and
    // clear the mask bits at the requested address.
    // Write back the 16/32-bit data to IPCLOCALREPLY.
    // Restore the status of the EALLOW register.
    // Acknowledge the status flag and the task flag.
    //
    EALLOW;

    if (IpcRegs.IPCRECVCOM == IPC_CLEAR_BITS_16_PROTECTED)
    {

        pusAddress = (uint16_t *)IpcRegs.IPCRECVADDR;;
        *pusAddress &= ~((uint16_t)IpcRegs.IPCRECVDATA);
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pusAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_CLEAR_BITS_32_PROTECTED)
    {

        pulAddress = (uint32_t *)IpcRegs.IPCRECVADDR;;
        *pulAddress &= ~((uint32_t)IpcRegs.IPCRECVDATA);
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pulAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }

    //
    // Otherwise, only acknowledge the task flag.
    // (Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }

    EDIS;
}

//*****************************************************************************
//
//! Writes a 16/32-bit data word to Local CPU system address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to write a 16/32-bit word
//! to an address on the Local CPU system. The \e ulFlag
//! parameter accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32,
//! and the \e ulStatusFlag parameter accepts any other one of the flag values
//! \b IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLDataWrite(uint32_t ulFlag, uint32_t ulStatusFlag)
{
    uint32_t* pulAddress;
    uint16_t* pusAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then write the 16/32-bit data to the requested address
    // and write back the 16/32-bit data to IPCLOCALREPLY.
    // Acknowledge the status flag and the task flag.
    //
    if (IpcRegs.IPCRECVCOM == IPC_DATA_WRITE_16)
    {
        pusAddress = (uint16_t *)IpcRegs.IPCRECVADDR;;
        *pusAddress = (uint16_t)IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pusAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_DATA_WRITE_32)
    {
        pulAddress = (uint32_t *)IpcRegs.IPCRECVADDR;;
        *pulAddress = IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = *pulAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);

    }

    //
    // Otherwise, only acknowledge the task flag.
    // (Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }
}

//*****************************************************************************
//
//! Writes a 16/32-bit data word to a write-protected Local CPU system address
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to write a 16/32-bit word
//! to an address on the Local CPU system. The \e ulFlag
//! parameter accepts any one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32,
//! and the \e ulStatusFlag parameter accepts any other one of the flag values
//! \b IPC_FLAG1 - \b IPC_FLAG32 and \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLDataWrite_Protected(uint32_t ulFlag, uint32_t ulStatusFlag)
{
    uint32_t* pulAddress;
    uint16_t* pusAddress;

    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then enable write access with EALLOW and
    // write the 16/32-bit data to the requested address
    // and write back the 16/32-bit data to IPCLOCALREPLY.
    // Acknowledge the status flag and the task flag.
    //
    EALLOW;

    if (IpcRegs.IPCRECVCOM == IPC_DATA_WRITE_16_PROTECTED)
    {
        pusAddress = (uint16_t *)IpcRegs.IPCRECVADDR;;
        *pusAddress = (uint16_t)IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = (uint32_t)*pusAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }
    else if (IpcRegs.IPCRECVCOM == IPC_DATA_WRITE_32_PROTECTED)
    {
        pulAddress = (uint32_t *)IpcRegs.IPCRECVADDR;
        *pulAddress = IpcRegs.IPCRECVDATA;
        IpcRegs.IPCLOCALREPLY = *pulAddress;

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);

    }

    //
    // Otherwise, only acknowledge the task flag.
    // (Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }

    //
    // Restore write-protection status.
    //
    EDIS;
}

//*****************************************************************************
//
//! Calls a Local CPU function with a single optional parameter and return
//! value.
//!
//! \param ulFlag specifies Remote to Local IPC Flag number mask used to
//! indicate a command is being sent.
//! \param ulStatusFlag indicates the Remote to Local Flag number mask used to
//! report the status of the command sent back from the control system.
//!
//! This function will allow the Remote CPU system to call a Local CPU function
//! with a single optional parameter and places an optional return value in the
//! IPCLOCALREPLY register. The \e ulFlag parameter accepts any one of the flag
//! values \b IPC_FLAG1 - \b IPC_FLAG32, and  the \e ulStatusFlag parameter
//! accepts any other one of the flag values \b IPC_FLAG1 - \b IPC_FLAG32 and
//! \b NO_FLAG.
//
//*****************************************************************************
void
IPCLiteRtoLFunctionCall(uint32_t ulFlag, uint32_t ulStatusFlag)
{
    //
    // Wait until IPC Remote to Local request task is flagged
    //
    while (!(IpcRegs.IPCSTS.all & ulFlag))
    {
    }

    //
    // If the command is correct for this function:
    // Then call function at requested address
    // and if there is a return value, insert into
    // IPCLOCALREPLY register.
    // Acknowledge the status flag and the task flag.
    //
    if (IpcRegs.IPCRECVCOM == IPC_FUNC_CALL)
    {
        tfIpcFuncCall func_call = (tfIpcFuncCall)IpcRegs.IPCRECVADDR;
        IpcRegs.IPCLOCALREPLY = func_call(IpcRegs.IPCRECVDATA);

        IpcRegs.IPCACK.all |= (ulStatusFlag | ulFlag);
    }

    //
    // Otherwise, only acknowledge the task flag.
    //(Indicates to Remote CPU there was an error)
    //
    else
    {
        IpcRegs.IPCACK.all |= (ulFlag);
    }
}

void DelayLoop (void)
{
    __asm(" nop");
    __asm(" nop");
    __asm(" nop");
    __asm(" nop");
    __asm(" nop");
}

//*****************************************************************************
// Close the Doxygen group.
//! @}
//*****************************************************************************


