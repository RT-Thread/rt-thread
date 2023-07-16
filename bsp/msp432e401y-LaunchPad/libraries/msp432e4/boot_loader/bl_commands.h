//*****************************************************************************
//
// bl_commands.h - The list of commands and return messages supported by the
//                 boot loader.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
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

#ifndef __BL_COMMANDS_H__
#define __BL_COMMANDS_H__

//*****************************************************************************
//
// This command is used to receive an acknowledge from the the boot loader
// proving that communication has been established.  This command is a single
// byte.
//
// The format of the command is as follows:
//
//     uint8_t ui8Command[1];
//
//     ui8Command[0] = COMMAND_PING;
//
//*****************************************************************************
#define COMMAND_PING            0x20

//*****************************************************************************
//
// This command is sent to the boot loader to indicate where to store data and
// how many bytes will be sent by the COMMAND_SEND_DATA commands that follow.
// The command consists of two 32-bit values that are both transferred MSB
// first.  The first 32-bit value is the address to start programming data
// into, while the second is the 32-bit size of the data that will be sent.
// This command also triggers an erasure of the full application area in the
// flash or possibly the entire flash depending on the address used.  This
// causes the command to take longer to send the ACK/NAK in response to the
// command.  This command should be followed by a COMMAND_GET_STATUS to ensure
// that the program address and program size were valid for the microcontroller
// running the boot loader.
//
// The format of the command is as follows:
//
//     uint8_t ui8Command[9];
//
//     ui8Command[0] = COMMAND_DOWNLOAD;
//     ui8Command[1] = Program Address [31:24];
//     ui8Command[2] = Program Address [23:16];
//     ui8Command[3] = Program Address [15:8];
//     ui8Command[4] = Program Address [7:0];
//     ui8Command[5] = Program Size [31:24];
//     ui8Command[6] = Program Size [23:16];
//     ui8Command[7] = Program Size [15:8];
//     ui8Command[8] = Program Size [7:0];
//
//*****************************************************************************
#define COMMAND_DOWNLOAD        0x21

//*****************************************************************************
//
// This command is sent to the boot loader to transfer execution control to the
// specified address.  The command is followed by a 32-bit value, transferred
// MSB first, that is the address to which execution control is transferred.
//
// The format of the command is as follows:
//
//     uint8_t ui8Command[5];
//
//     ui8Command[0] = COMMAND_RUN;
//     ui8Command[1] = Run Address [31:24];
//     ui8Command[2] = Run Address [23:16];
//     ui8Command[3] = Run Address [15:8];
//     ui8Command[4] = Run Address [7:0];
//
//*****************************************************************************
#define COMMAND_RUN             0x22

//*****************************************************************************
//
// This command returns the status of the last command that was issued.
// Typically this command should be received after every command is sent to
// ensure that the previous command was successful or, if unsuccessful, to
// properly respond to a failure.  The command requires one byte in the data of
// the packet and the boot loader should respond by sending a packet with one
// byte of data that contains the current status code.
//
// The format of the command is as follows:
//
//     uint8_t ui8Command[1];
//
//     ui8Command[0] = COMMAND_GET_STATUS;
//
// The following are the definitions for the possible status values that can be
// returned from the boot loader when <tt>COMMAND_GET_STATUS</tt> is sent to
// the microcontroller.
//
//     COMMAND_RET_SUCCESS
//     COMMAND_RET_UNKNOWN_CMD
//     COMMAND_RET_INVALID_CMD
//     COMMAND_RET_INVALID_ADD
//     COMMAND_RET_FLASH_FAIL
//     COMMAND_RET_CRC_FAIL
//
//*****************************************************************************
#define COMMAND_GET_STATUS      0x23

//*****************************************************************************
//
// This command should only follow a COMMAND_DOWNLOAD command or another
// COMMAND_SEND_DATA command, if more data is needed.  Consecutive send data
// commands automatically increment the address and continue programming from
// the previous location.  The transfer size is limited by the size of the
// receive buffer in the boot loader (as configured by the BUFFER_SIZE
// parameter).  The command terminates programming once the number of bytes
// indicated by the COMMAND_DOWNLOAD command has been received.  Each time this
// function is called, it should be followed by a COMMAND_GET_STATUS command to
// ensure that the data was successfully programmed into the flash.  If the
// boot loader sends a NAK to this command, the boot loader will not increment
// the current address to allow retransmission of the previous data.
//
// The format of the command is as follows:
//
//     uint8_t ui8Command[9];
//
//     ui8Command[0] = COMMAND_SEND_DATA;
//     ui8Command[1] = Data[0];
//     ui8Command[2] = Data[1];
//     ui8Command[3] = Data[2];
//     ui8Command[4] = Data[3];
//     ui8Command[5] = Data[4];
//     ui8Command[6] = Data[5];
//     ui8Command[7] = Data[6];
//     ui8Command[8] = Data[7];
//
//*****************************************************************************
#define COMMAND_SEND_DATA       0x24

//*****************************************************************************
//
// This command is used to tell the boot loader to reset.  This is used after
// downloading a new image to the microcontroller to cause the new application
// or the new boot loader to start from a reset.  The normal boot sequence
// occurs and the image runs as if from a hardware reset.  It can also be used
// to reset the boot loader if a critical error occurs and the host device
// wants to restart communication with the boot loader.
//
// The format of the command is as follows:
//
//     uint8_t ui8Command[1];
//
//     ui8Command[0] = COMMAND_RESET;
//
// The boot loader responds with an ACK signal to the host device before
// actually executing the software reset on the microcontroller running the
// boot loader.  This informs the updater application that the command was
// received successfully and the part will be reset.
//
//*****************************************************************************
#define COMMAND_RESET           0x25

//*****************************************************************************
//
// This is returned in response to a COMMAND_GET_STATUS command and indicates
// that the previous command completed successful.
//
//*****************************************************************************
#define COMMAND_RET_SUCCESS     0x40

//*****************************************************************************
//
// This is returned in response to a COMMAND_GET_STATUS command and indicates
// that the command sent was an unknown command.
//
//*****************************************************************************
#define COMMAND_RET_UNKNOWN_CMD 0x41

//*****************************************************************************
//
// This is returned in response to a COMMAND_GET_STATUS command and indicates
// that the previous command was formatted incorrectly.
//
//*****************************************************************************
#define COMMAND_RET_INVALID_CMD 0x42

//*****************************************************************************
//
// This is returned in response to a COMMAND_GET_STATUS command and indicates
// that the previous download command contained an invalid address value.
//
//*****************************************************************************
#define COMMAND_RET_INVALID_ADR 0x43

//*****************************************************************************
//
// This is returned in response to a COMMAND_GET_STATUS command and indicates
// that an attempt to program or erase the flash has failed.
//
//*****************************************************************************
#define COMMAND_RET_FLASH_FAIL  0x44

//*****************************************************************************
//
// This is returned in response to a COMMAND_GET_STATUS command and indicates
// that the boot loader is configured to check the embedded CRC32 in the
// downloaded image but the check failed.  This status can only be returned
// after the last COMMAND_SEND_DATA has been received and processed, and only
// if CHECK_CRC is defined in the boot loader configuration.
//
//*****************************************************************************
#define COMMAND_RET_CRC_FAIL    0x45

//*****************************************************************************
//
// This is the value that is sent to acknowledge a packet.
//
//*****************************************************************************
#define COMMAND_ACK             0xcc

//*****************************************************************************
//
// This is the value that is sent to not-acknowledge a packet.
//
//*****************************************************************************
#define COMMAND_NAK             0x33

#endif // __BL_COMMANDS_H__
