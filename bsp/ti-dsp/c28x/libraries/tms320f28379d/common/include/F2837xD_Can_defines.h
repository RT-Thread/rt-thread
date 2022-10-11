//#############################################################################
//
// FILE:   F2837xD_Can_defines.h
//
// TITLE:  Common defines used in CAN Test Cases
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

#ifndef F2837xD_CAN_DEFINES_H
#define F2837xD_CAN_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// Reset Values
//
#define CAN_RESET_VALUE_ZERO			0x00000000
#define CAN_CTL_RESET_VALUE		    	0x00001401
#define CAN_ES_RESET_VALUE				0x00000007
#define CAN_BTR_RESET_VALUE		    	0x00002301
#define CAN_REL_RESET_VALUE		    	0xA3170504
#define CAN_RAM_INIT_RESET_VALUE		0x00000005
#define CAN_IF_CMD_RESET_VALUE			0x00000001
#define CAN_IF_MASK_RESET_VALUE	    	0xFFFFFFFF

//
// Register value when Peripheral Clock is Disabled
//
#define CAN_MODULE_CLK_DISABLE_VALUE	0x00000000

//
// Bit field definition of CAN_CTL register.
//
#define CAN_CTL_INIT		0x00000001  // Initialization
#define CAN_CTL_IE0         0x00000002  // Interrupt Enable 0
#define CAN_CTL_SIE         0x00000004  // Status Interrupt Enable
#define CAN_CTL_EIE         0x00000008  // Error Interrupt Enable
#define CAN_CTL_DAR         0x00000020  // Disable Automatic-Retransmission
#define CAN_CTL_CCE         0x00000040  // Configuration Change Enable
#define CAN_CTL_TEST        0x00000080  // Test Mode Enable
#define CAN_CTL_IDS		    0x00000100	// Interruption Debug Support Enable
#define CAN_CTL_ABO		    0x00000200	// Auto-Bus On Enable
#define CAN_CTL_PMD_S		10
#define CAN_CTL_PMD_M		0x00003C00	// Parity/SECDED Enable
#define CAN_CTL_SWR		    0x00008000	// Software Reset Enable
#define CAN_CTL_INITDBG	    0x00010000	// Debug Mode Status
#define CAN_CTL_IE1		    0x00020000	// Interrupt Enable 1
#define CAN_CTL_PDR		    0x01000000	// Power Down Mode Request
#define CAN_CTL_WUBA		0x02000000	// Wake Up on Bus Activity

//
// Bit field definition of CAN_IF1_CMD register.
//
#define CAN_IF1_CMD_MESSNUM_S		0
#define CAN_IF1_CMD_MESSNUM_M		0x000000FF	// Message Number
#define CAN_IF1_CMD_BUSY			0x00008000	// Busy Flag
#define CAN_IF1_CMD_DATAB			0x00010000	// Access Data B
#define CAN_IF1_CMD_DATAA			0x00020000	// Access Data A
#define CAN_IF1_CMD_TXRQSTNDAT		0x00040000	// Transmission Request Bit
#define CAN_IF1_CMD_CLRINTPND		0x00080000	// Clear Interrupt Pending Bit
#define CAN_IF1_CMD_CONTROL		    0x00100000	// Access Control Bits
#define CAN_IF1_CMD_ARB			    0x00200000	// Access Arbitration Bits
#define CAN_IF1_CMD_MASK			0x00400000	// Access Mask Bits
#define CAN_IF1_CMD_WR_RD			0x00800000	// Write and Read

//
// Bit field definition of CAN_IF2_CMD register.
//
#define CAN_IF2_CMD_MESSNUM_S		0
#define CAN_IF2_CMD_MESSNUM_M		0x000000FF	// Message Number
#define CAN_IF2_CMD_BUSY			0x00008000	// Busy Flag
#define CAN_IF2_CMD_DATAB			0x00010000	// Access Data B
#define CAN_IF2_CMD_DATAA			0x00020000	// Access Data A
#define CAN_IF2_CMD_TXRQSTNDAT		0x00040000	// Transmission Request Bit
#define CAN_IF2_CMD_CLRINTPND		0x00080000	// Clear Interrupt Pending Bit
#define CAN_IF2_CMD_CONTROL		    0x00100000	// Access Control Bits
#define CAN_IF2_CMD_ARB			    0x00200000	// Access Arbitration Bits
#define CAN_IF2_CMD_MASK			0x00400000	// Access Mask Bits
#define CAN_IF2_CMD_WR_RD			0x00800000	// Write and Read

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837xD_CAN_DEFINES_H

//
// End of file
//
