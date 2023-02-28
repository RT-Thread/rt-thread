//###########################################################################
//
// FILE:   F2837xD_Ipc_Driver_Util.c
//
// TITLE:  F2837xD Inter-Processor Communication (IPC) API Driver Utility
//         Functions
//
// DESCRIPTION:
//         API functions for inter-processor communications between the
//         Local and Remote CPU system.
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
//
//! \addtogroup ipc_util_api
//! @{
//
//*****************************************************************************
#include "F2837xD_device.h"
#include "F2837xD_GlobalPrototypes.h"
#include "F2837xD_Gpio_defines.h"
#include "F2837xD_Ipc_drivers.h"

//*****************************************************************************
//
//! Local CPU Acknowledges Remote to Local IPC Flag.
//!
//! \param ulFlags specifies the IPC flag mask for flags being acknowledged.
//!
//! This function will allow the Local CPU system to acknowledge/clear the IPC
//! flag set by the Remote CPU system. The \e ulFlags parameter can be any of
//! the IPC flag values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None.
//
//*****************************************************************************
void
IPCRtoLFlagAcknowledge (uint32_t ulFlags)
{
    IpcRegs.IPCACK.all |= ulFlags;
}

//*****************************************************************************
//
//! Determines whether the given Remote to Local IPC flags are busy or not.
//!
//! \param ulFlags specifies Remote to Local IPC Flag number masks to check the
//!        status of.
//!
//! Allows the caller to determine whether the designated IPC flags are
//! pending. The \e ulFlags parameter can be any of the IPC flag
//! values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return Returns \b 1 if the IPC flags are busy or \b 0 if designated
//! IPC flags are free.
//
//*****************************************************************************
Uint16
IPCRtoLFlagBusy (uint32_t ulFlags)
{
    Uint16 returnStatus;

    if ((IpcRegs.IPCSTS.all & ulFlags) == 0)
    {
        returnStatus = 0;
    }
    else
    {
        returnStatus = 1;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Determines whether the given IPC flags are busy or not.
//!
//! \param ulFlags specifies Local to Remote IPC Flag number masks to check the
//!        status of.
//!
//! Allows the caller to determine whether the designated IPC flags are
//! available for further control to master system communication. If \b 0 is
//! returned, then all designated tasks have completed and are available.
//! The \e ulFlags parameter can be any of the IPC flag
//! values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return Returns \b 1 if the IPC flags are busy or \b 0 if designated
//! IPC flags are free.
//
//*****************************************************************************
Uint16
IPCLtoRFlagBusy (uint32_t ulFlags)
{
    Uint16 returnStatus;

    if ((IpcRegs.IPCFLG.all & ulFlags) == 0)
    {
        returnStatus = 0;
    }
    else
    {
        returnStatus = 1;
    }

    return returnStatus;
}

//*****************************************************************************
//
//! Local CPU Sets Local to Remote IPC Flag
//!
//! \param ulFlags specifies the IPC flag mask for flags being set.
//!
//! This function will allow the Local CPU system to set the designated IPC
//! flags to send to the Remote CPU system. The \e ulFlags parameter can be any
//! of the IPC flag values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None.
//
//*****************************************************************************
void
IPCLtoRFlagSet (uint32_t ulFlags)
{
    IpcRegs.IPCSET.all |= ulFlags;
}

//*****************************************************************************
//
//! Local CPU Clears Local to Remote IPC Flag
//!
//! \param ulFlags specifies the IPC flag mask for flags being set.
//!
//! This function will allow the Local CPU system to set the designated IPC
//! flags to send to the Remote CPU system. The \e ulFlags parameter can be any
//! of the IPC flag values: \b IPC_FLAG0 - \b IPC_FLAG31.
//!
//! \return None.
//
//*****************************************************************************
void
IPCLtoRFlagClear (uint32_t ulFlags)
{
    IpcRegs.IPCCLR.all |= ulFlags;
}

//*****************************************************************************
//
//! Local Return CPU02 BOOT status
//!
//! This function returns the value at IPCBOOTSTS register.
//!
//! \return Boot status.
//
//*****************************************************************************
uint32_t
IPCGetBootStatus (void)
{
   return(IpcRegs.IPCBOOTSTS);
}

#if defined (CPU1)
//*****************************************************************************
//! Executes a CPU02 control system bootloader.
//!
//! \param ulBootMode specifies which CPU02 control system boot mode to execute.
//!
//! This function will allow the CPU01 master system to boot the CPU02 control
//! system via the following modes: Boot to RAM, Boot to Flash, Boot via SPI,
//! SCI, I2C, or parallel I/O. Unlike other IPCLite driver functions, this
//! function blocks and waits until the control system boot ROM is configured
//! and ready to receive CPU01 to CPU02 IPC INT0 interrupts. It then blocks and
//! waits until IPC INT0 and IPC FLAG31 are available in the CPU02 boot ROM
//! prior to sending the command to execute the selected bootloader. The \e
//! ulBootMode parameter accepts one of the following values: \b
//! C1C2_BROM_BOOTMODE_BOOT_FROM_PARALLEL, \b
//! C1C2_BROM_BOOTMODE_BOOT_FROM_SCI, \b
//! C1C2_BROM_BOOTMODE_BOOT_FROM_SPI, \b
//! C1C2_BROM_BOOTMODE_BOOT_FROM_I2C, \b C1C2_BROM_BOOTMODE_BOOT_FROM_CAN,
//! \b C1C2_BROM_BOOTMODE_BOOT_FROM_RAM, \b
//! C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH.
//!
//! \return 0 (success) if command is sent, or 1 (failure) if boot mode is
//! invalid and command was not sent.
//
//*****************************************************************************
uint16_t
IPCBootCPU2(uint32_t ulBootMode)
{
    uint32_t bootStatus;
    uint16_t pin;
    uint16_t returnStatus = STATUS_PASS;

    //
    // If CPU2 has already booted, return a fail to let the application
    // know that something is out of the ordinary.
    //
    bootStatus = IPCGetBootStatus() & 0x0000000F;

    if(bootStatus == C2_BOOTROM_BOOTSTS_C2TOC1_BOOT_CMD_ACK)
    {
        //
        // Check if MSB is set as well
        //
        bootStatus = ((uint32_t)(IPCGetBootStatus() & 0x80000000)) >> 31U;
        
        if(bootStatus != 0)
        {
            returnStatus = STATUS_FAIL;

            return returnStatus;
        }
    }

    //
    // Wait until CPU02 control system boot ROM is ready to receive
    // CPU01 to CPU02 INT1 interrupts.
    //
    do
    {
        bootStatus = IPCGetBootStatus() & C2_BOOTROM_BOOTSTS_SYSTEM_READY;
    } while ((bootStatus != C2_BOOTROM_BOOTSTS_SYSTEM_READY));

    //
    // Loop until CPU02 control system IPC flags 1 and 32 are available
    //
    while ((IPCLtoRFlagBusy(IPC_FLAG0) == 1) ||
           (IPCLtoRFlagBusy(IPC_FLAG31) == 1))
    {

    }

    if (ulBootMode >= C1C2_BROM_BOOTMODE_BOOT_COMMAND_MAX_SUPPORT_VALUE)
    {
        returnStatus = STATUS_FAIL;
    }
    else
    {
        //
        // Based on boot mode, enable pull-ups on peripheral pins and
        // give GPIO pin control to CPU02 control system.
        //
        switch (ulBootMode)
        {
            case C1C2_BROM_BOOTMODE_BOOT_FROM_SCI:

                 EALLOW;

                 //
                 //SCIA connected to CPU02
                 //
                 DevCfgRegs.CPUSEL5.bit.SCI_A = 1;

                 //
                 //Allows CPU02 bootrom to take control of clock
                 //configuration registers
                 //
                 ClkCfgRegs.CLKSEM.all = 0xA5A50000;

                 ClkCfgRegs.LOSPCP.all = 0x0002;
                 EDIS;

                 GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(29,GPIO_MUX_CPU2,1);

                 GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(28,GPIO_MUX_CPU2,1);

                break;

            case C1C2_BROM_BOOTMODE_BOOT_FROM_SPI:
                 EALLOW;

                 //
                 //SPI-A connected to CPU02
                 //
                 DevCfgRegs.CPUSEL6.bit.SPI_A = 1;

                 //
                 //Allows CPU02 bootrom to take control of clock configuration
                 // registers
                 //
                 ClkCfgRegs.CLKSEM.all = 0xA5A50000;
                 EDIS;

                 GPIO_SetupPinOptions(16, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(16,GPIO_MUX_CPU2,1);

                 GPIO_SetupPinOptions(17, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(17,GPIO_MUX_CPU2,1);

                 GPIO_SetupPinOptions(18, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(18,GPIO_MUX_CPU2,1);

                 GPIO_SetupPinOptions(19, GPIO_OUTPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(19,GPIO_MUX_CPU2,0);

                break;

            case C1C2_BROM_BOOTMODE_BOOT_FROM_I2C:
                 EALLOW;

                 //
                 //I2CA connected to CPU02
                 //
                 DevCfgRegs.CPUSEL7.bit.I2C_A = 1;

                 //
                 //Allows CPU2 bootrom to take control of clock
                 //configuration registers
                 //
                 ClkCfgRegs.CLKSEM.all = 0xA5A50000;
                 ClkCfgRegs.LOSPCP.all = 0x0002;
                 EDIS;
                 GPIO_SetupPinOptions(32, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(32,GPIO_MUX_CPU2,1);

                 GPIO_SetupPinOptions(33, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(33,GPIO_MUX_CPU2,1);

                break;
            case C1C2_BROM_BOOTMODE_BOOT_FROM_PARALLEL:

                 for(pin=58;pin<=65;pin++)
                 {
                    GPIO_SetupPinOptions(pin, GPIO_INPUT, GPIO_ASYNC);
                    GPIO_SetupPinMux(pin,GPIO_MUX_CPU2,0);
                 }

                 GPIO_SetupPinOptions(69, GPIO_OUTPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(69,GPIO_MUX_CPU2,0);

                 GPIO_SetupPinOptions(70, GPIO_INPUT, GPIO_ASYNC);
                 GPIO_SetupPinMux(70,GPIO_MUX_CPU2,0);
                 break;


            case C1C2_BROM_BOOTMODE_BOOT_FROM_CAN:
                 //
                 //Set up the GPIO mux to bring out CANATX on GPIO71
                 //and CANARX on GPIO70
                 //
                 EALLOW;
                 GpioCtrlRegs.GPCLOCK.all = 0x00000000; //Unlock GPIOs 64-95

                 //
                 //Give CPU2 control just in case
                 //
                 GpioCtrlRegs.GPCCSEL1.bit.GPIO71 = GPIO_MUX_CPU2;

                 //
                 //Set the extended mux to 0x5
                 //
                 GpioCtrlRegs.GPCGMUX1.bit.GPIO71 = 0x1;
                 GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0x1;

                 //
                 //Set qualification to async just in case
                 //
                 GpioCtrlRegs.GPCQSEL1.bit.GPIO71 = 0x3;

                 GpioCtrlRegs.GPCLOCK.all = 0x00000000; //Unlock GPIOs 64-95

                 //
                 //Give CPU2 control just in case
                 //
                 GpioCtrlRegs.GPCCSEL1.bit.GPIO70 = GPIO_MUX_CPU2;

                 //
                 //Set the extended mux to bring out CANATX
                 //
                 GpioCtrlRegs.GPCGMUX1.bit.GPIO70 = 0x1;
                 GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0x1;

                 //
                 //Set qualification to async just in case
                 //
                 GpioCtrlRegs.GPCQSEL1.bit.GPIO70 = 0x3;
                 GpioCtrlRegs.GPCLOCK.all = 0xFFFFFFFF; //Lock GPIOs 64-95
                 ClkCfgRegs.CLKSRCCTL2.bit.CANABCLKSEL = 0x0;
                 CpuSysRegs.PCLKCR10.bit.CAN_A = 1;
                 EDIS;

               break;

         }

        //
        //CPU01 to CPU02 IPC Boot Mode Register
        //
        IpcRegs.IPCBOOTMODE = ulBootMode;

        //
        // CPU01 To CPU02 IPC Command Register
        //
        IpcRegs.IPCSENDCOM  = BROM_IPC_EXECUTE_BOOTMODE_CMD;

        //
        // CPU01 to CPU02 IPC flag register
        //
        IpcRegs.IPCSET.all = 0x80000001;

    }



    return returnStatus;
}


#endif
//*****************************************************************************
// Close the Doxygen group.
//! @}
//*****************************************************************************


