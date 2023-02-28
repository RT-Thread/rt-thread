//#############################################################################
//
// File:   F2837xD_sci_io.c
//
// Description:  Contains the various functions related to the serial
//               communications interface (SCI) object
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include <stdio.h>
#include <file.h>
#include "F28x_Project.h"
#include "F2837xD_sci_io.h"

//
// Globals
//
uint16_t deviceOpen = 0;

//
// SCI_open - Initialize and setup SCI
//
int SCI_open(const char * path, unsigned flags, int llv_fd)
{
    if(deviceOpen)
    {
        return (-1);
    }
    else
    {
        EALLOW;
        CpuSysRegs.PCLKCR7.bit.SCI_A = 1;
        SciaRegs.SCIFFTX.all=0xE040;
        SciaRegs.SCIFFRX.all=0x2044;
        SciaRegs.SCIFFCT.all=0x0;
        SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                       // No parity,8 char bits,
                                       // async mode, idle-line protocol
        SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                       // Disable RX ERR, SLEEP, TXWAKE
        SciaRegs.SCICTL2.all =0x0003;
        SciaRegs.SCICTL2.bit.TXINTENA =1;
        SciaRegs.SCICTL2.bit.RXBKINTENA =1;

        SciaRegs.SCIHBAUD.bit.BAUD =0x0000;  // 9600 baud @LSPCLK = 10MHz
                                             //(40 MHz SYSCLK).
        SciaRegs.SCILBAUD.bit.BAUD =0x0081;

        SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
        EDIS;

        deviceOpen = 1;
        return (1);
    }
}

//
// SCI_close - Set SCI to closed
//
int SCI_close(int dev_fd)
{
    if((dev_fd != 1) || (!deviceOpen))
    {
        return (-1);
    }
    else
    {
        deviceOpen = 0;
        return (0);
    }
}

//
// SCI_read - Read from the SCI RX buffer
//
int SCI_read(int dev_fd, char * buf, unsigned count)
{
    uint16_t readCount = 0;
    uint16_t * bufPtr = (uint16_t *) buf;

    if(count == 0)
    {
        return (0);
    }

    while((readCount < count) && SciaRegs.SCIRXST.bit.RXRDY)
    {
        *bufPtr = SciaRegs.SCIRXBUF.bit.SAR;
        readCount++;
        bufPtr++;
    }

    return (readCount);
}

//
// SCI_write - Write to the SCI TX buffer
//
int SCI_write(int dev_fd, char * buf, unsigned count)
{
    uint16_t writeCount = 0;
    uint16_t * bufPtr = (uint16_t *) buf;

    if(count == 0)
    {
        return (0);
    }

    while(writeCount < count)
    {
        while(SciaRegs.SCICTL2.bit.TXRDY != 1)
        {
        }
        SciaRegs.SCITXBUF.bit.TXDT = *bufPtr;
        writeCount++;
        bufPtr++;
    }

    return (writeCount);
}

//
// SCI_lseek - Do nothing
//
off_t SCI_lseek(int dev_fd, off_t offset, int origin)
{
    return (0);
}

//
// SCI_unlink - Do nothing
//
int SCI_unlink(const char * path)
{
    return (0);
}

//
// SCI_rename - Do nothing
//
int SCI_rename(const char * old_name, const char * new_name)
{
    return (0);
}

//
// End of file
//
