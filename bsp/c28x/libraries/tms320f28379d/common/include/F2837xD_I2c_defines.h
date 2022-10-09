//###########################################################################
//
// FILE:     F2837xD_I2c_defines.h
//
// TITLE:    F2837xD I2C Common Definitions.
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

#ifndef F2837xD_I2C_DEFINES_H
#define F2837xD_I2C_DEFINES_H

//
// Defines
//

//
// Error Messages
//
#define I2C_ERROR               0xFFFF
#define I2C_ARB_LOST_ERROR      0x0001
#define I2C_NACK_ERROR          0x0002
#define I2C_BUS_BUSY_ERROR      0x1000
#define I2C_STP_NOT_READY_ERROR 0x5555
#define I2C_NO_FLAGS            0xAAAA
#define I2C_SUCCESS             0x0000

//
// Clear Status Flags
//
#define I2C_CLR_AL_BIT          0x0001
#define I2C_CLR_NACK_BIT        0x0002
#define I2C_CLR_ARDY_BIT        0x0004
#define I2C_CLR_RRDY_BIT        0x0008
#define I2C_CLR_SCD_BIT         0x0020

//
// Interrupt Source Messages
//
#define I2C_NO_ISRC             0x0000
#define I2C_ARB_ISRC            0x0001
#define I2C_NACK_ISRC           0x0002
#define I2C_ARDY_ISRC           0x0003
#define I2C_RX_ISRC             0x0004
#define I2C_TX_ISRC             0x0005
#define I2C_SCD_ISRC            0x0006
#define I2C_AAS_ISRC            0x0007

//
// I2CMSG structure defines
//
#define I2C_NO_STOP             0
#define I2C_YES_STOP            1
#define I2C_RECEIVE             0
#define I2C_TRANSMIT            1
#define I2C_MAX_BUFFER_SIZE     16

//
// I2C Slave State defines
//
#define I2C_NOTSLAVE            0
#define I2C_ADDR_AS_SLAVE       1
#define I2C_ST_MSG_READY        2

//
// I2C Slave Receiver messages defines
//
#define I2C_SND_MSG1            1
#define I2C_SND_MSG2            2

//
// I2C State defines
//
#define I2C_IDLE                0
#define I2C_SLAVE_RECEIVER      1
#define I2C_SLAVE_TRANSMITTER   2
#define I2C_MASTER_RECEIVER     3
#define I2C_MASTER_TRANSMITTER  4

//
// I2C  Message Commands for I2CMSG struct
//
#define I2C_MSGSTAT_INACTIVE          0x0000
#define I2C_MSGSTAT_SEND_WITHSTOP     0x0010
#define I2C_MSGSTAT_WRITE_BUSY        0x0011
#define I2C_MSGSTAT_SEND_NOSTOP       0x0020
#define I2C_MSGSTAT_SEND_NOSTOP_BUSY  0x0021
#define I2C_MSGSTAT_RESTART           0x0022
#define I2C_MSGSTAT_READ_BUSY         0x0023

//
// Generic defines
//
#define I2C_TRUE  1
#define I2C_FALSE 0
#define I2C_YES   1
#define I2C_NO    0
#define I2C_DUMMY_BYTE 0


//
//  These are the Defines to select I2C pin muxing when calling the functions
//  I2cAGpioConfig() & I2cBGpioConfig() in F2837xD_I2C.c
//
#define I2C_A_GPIO0_GPIO1            1    //switch case 1
#define I2C_A_GPIO32_GPIO33          2    //switch case 2
#define I2C_A_GPIO42_GPIO43          3    //switch case 3
#define I2C_A_GPIO91_GPIO92          4    //switch case 4
#define I2C_A_GPIO63104_GPIO105      5    //switch case 5

#define I2C_B_GPIO2_GPIO3            1    //switch case 1
#define I2C_B_GPIO134_GPIO35         2    //switch case 2
#define I2C_B_GPIO40_GPIO41          3    //switch case 3
#define I2C_B_GPIO66_GPIO69          4    //switch case 4

//
// Globals
//

//
// I2C Message Structure
//
struct I2CMSG {
  Uint16 MsgStatus;             // Word stating what state msg is in:
                                //  I2C_MSGCMD_INACTIVE = do not send msg
                                //  I2C_MSGCMD_BUSY = msg start has been sent,
                                //                    awaiting stop
                                //  I2C_MSGCMD_SEND_WITHSTOP = command to send
                                //    master trans msg complete with a stop bit
                                //  I2C_MSGCMD_SEND_NOSTOP = command to send
                                //    master trans msg without the stop bit
                                //  I2C_MSGCMD_RESTART = command to send a
                                //    restart as a master receiver with a
                                //    stop bit
  Uint16 SlaveAddress;          // I2C address of slave msg is intended for
  Uint16 NumOfBytes;            // Num of valid bytes in (or to be put
                                // in MsgBuffer)
  Uint16 MemoryHighAddr;        // EEPROM address of data associated with
                                // msg (high byte)
  Uint16 MemoryLowAddr;         // EEPROM address of data associated with
                                // msg (low byte)
  Uint16 MsgBuffer[I2C_MAX_BUFFER_SIZE];  // Array holding msg data - max that
                                          // MAX_BUFFER_SIZE can be is 16 due
                                          // to the FIFO's
};

#endif  // end of F2837xD_I2C_DEFINES_H definition

//
// End of file
//
