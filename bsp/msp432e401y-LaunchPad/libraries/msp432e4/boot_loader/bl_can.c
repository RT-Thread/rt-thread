//*****************************************************************************
//
// bl_can.c - Functions to transfer data via the CAN port.
//
// Copyright (c) 2008-2017 Texas Instruments Incorporated.  All rights reserved.
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

#include <stdint.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/inc/msp.h"
#include "ti/devices/msp432e4/boot_loader/bl_can.h"
#include "ti/devices/msp432e4/boot_loader/bl_can_timing.h"
#include "ti/devices/msp432e4/boot_loader/bl_check.h"
#include "ti/devices/msp432e4/boot_loader/bl_crystal.h"
#include "ti/devices/msp432e4/boot_loader/bl_flash.h"
#include "ti/devices/msp432e4/boot_loader/bl_hooks.h"
#include "ti/devices/msp432e4/boot_loader/bl_uart.h"

//*****************************************************************************
//
//! \addtogroup bl_can_api
//! @{
//
//*****************************************************************************
#if defined(CAN_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
// The results that can be returned by the CAN APIs.
//
//*****************************************************************************
#define CAN_CMD_SUCCESS         0x00
#define CAN_CMD_FAIL            0x01

//*****************************************************************************
//
// Macros used to generate correct pin definitions.
//
//*****************************************************************************
#define CAN_RX_PIN_M            (1 << CAN_RX_PIN)
#define CAN_TX_PIN_M            (1 << CAN_TX_PIN)
#define CAN_RX_PIN_PCTL_M       (CAN_RX_PIN_PCTL << (CAN_RX_PIN*4))
#define CAN_TX_PIN_PCTL_M       (CAN_TX_PIN_PCTL << (CAN_TX_PIN*4))

//*****************************************************************************
//
// The message object number and index to the local message object memory to
// use when accessing the messages.
//
//*****************************************************************************
#define MSG_OBJ_BCAST_RX_ID     1
#define MSG_OBJ_BCAST_TX_ID     2

//*****************************************************************************
//
// A prototype for the function (in the startup code) for calling the
// application.
//
//*****************************************************************************
extern void StartApplication(void);

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(uint32_t ui32Count);

//*****************************************************************************
//
// Holds the current address to write to when data is received via the Send
// Data Command.
//
//*****************************************************************************
static uint32_t g_ui32TransferAddress;

//*****************************************************************************
//
// Holds the remaining bytes expected to be received.
//
//*****************************************************************************
static uint32_t g_ui32TransferSize;

//*****************************************************************************
//
// The buffer used to receive data from the update.
//
//*****************************************************************************
static uint8_t g_pui8CommandBuffer[8];

//*****************************************************************************
//
// These globals are used to store the first two words to prevent a partial
// image from being booted.
//
//*****************************************************************************
static uint32_t g_ui32StartValues[2];
static uint32_t g_ui32StartSize;
static uint32_t g_ui32StartAddress;

//*****************************************************************************
//
// The active interface when the UART bridge is enabled.
//
//*****************************************************************************
#ifdef CAN_UART_BRIDGE
static uint32_t g_ui32Interface;
#define IFACE_UNKNOWN           0
#define IFACE_CAN               1
#define IFACE_UART              2
#endif

//*****************************************************************************
//
//! Initializes the CAN controller after reset.
//!
//! After reset, the CAN controller is left in the disabled state.  However,
//! the memory used for message objects contains undefined values and must be
//! cleared prior to enabling the CAN controller the first time.  This prevents
//! unwanted transmission or reception of data before the message objects are
//! configured.  This function must be called before enabling the controller
//! the first time.
//!
//! \return None.
//
//*****************************************************************************
static void
BL_CANInit(void)
{
    int iMsg;

    //
    // Place CAN controller in init state, regardless of previous state.  This
    // will put the controller in idle, and allow the message object RAM to be
    // programmed.
    //
    CAN0->CTL = CAN_CTL_INIT | CAN_CTL_CCE;

    //
    // Loop through to program all 32 message objects
    //
    for(iMsg = 1; iMsg <= 32; iMsg++)
    {
        //
        // Wait for busy bit to clear.
        //
        while(CAN0->IF1CRQ & CAN_IF1CRQ_BUSY)
        {
        }

        //
        // Clear the message value bit in the arbitration register.  This
        // indicates the message is not valid and is a "safe" condition to
        // leave the message object.
        //
        CAN0->IF1CMSK =
                    CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_ARB | CAN_IF1CMSK_CONTROL;
        CAN0->IF1ARB2 = 0;
        CAN0->IF1MCTL = 0;

        //
        // Initiate programming of the message object
        //
        CAN0->IF1CRQ = iMsg;
    }

    //
    // Acknowledge any pending status interrupts.
    //
    CAN0->STS;
}

//*****************************************************************************
//
//! This function configures the message object used to receive commands.
//!
//! This function configures the message object used to receive all firmware
//! update messages.  This will not actually read the data from the message it
//! is used to prepare the message object to receive the data when it is sent.
//!
//! \return None.
//
//*****************************************************************************
static void
CANMessageSetRx(void)
{
    uint16_t ui16CmdMaskReg;
    uint16_t ui16MaskReg[2];
    uint16_t ui16ArbReg[2];
    uint16_t ui16MsgCtrl;

    //
    // Wait for busy bit to clear
    //
    while(CAN0->IF1CRQ & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // This is always a write to the Message object as this call is setting a
    // message object.  This call will also always set all size bits so it sets
    // both data bits.  The call will use the CONTROL register to set control
    // bits so this bit needs to be set as well.
    //
    // Set the MASK bit so that this gets transferred to the Message Object.
    // Set the Arb bit so that this gets transferred to the Message object.
    //
    ui16CmdMaskReg = (CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_DATAA |
                      CAN_IF1CMSK_DATAB | CAN_IF1CMSK_CONTROL |
                      CAN_IF1CMSK_MASK | CAN_IF1CMSK_ARB);

    //
    // Set the UMASK bit to enable using the mask register.
    // Set the data length since this is set for all transfers.  This is also a
    // single transfer and not a FIFO transfer so set EOB bit.
    //
    ui16MsgCtrl = CAN_IF1MCTL_UMASK | CAN_IF1MCTL_EOB;

    //
    // Configure the Mask Registers.
    //
    //
    // Set the 29 bits of Identifier mask that were requested.
    //
    ui16MaskReg[0] = (uint16_t)SL_API_UPD;

    //
    // If the caller wants to filter on the extended ID bit then set it.
    //
    ui16MaskReg[1] =
        (uint16_t)(CAN_IF1MSK2_MXTD | (SL_API_UPD >> 16));

    //
    // Set the 29 bit version of the Identifier for this message object.
    // Mark the message as valid and set the extended ID bit.
    //
    ui16ArbReg[0] = SL_API_UPD & CAN_IF1ARB1_ID_M;
    ui16ArbReg[1] = (((SL_API_UPD >> 16) & CAN_IF1ARB2_ID_M) |
                     (CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD));

    //
    // Write out the registers to program the message object.
    //
    CAN0->IF1CMSK = ui16CmdMaskReg;
    CAN0->IF1MSK1 = ui16MaskReg[0];
    CAN0->IF1MSK2 = ui16MaskReg[1];
    CAN0->IF1ARB1 = ui16ArbReg[0];
    CAN0->IF1ARB2 = ui16ArbReg[1];
    CAN0->IF1MCTL = ui16MsgCtrl;

    //
    // Transfer the message object to the message object specific by
    // MSG_OBJ_BCAST_RX_ID.
    //
    CAN0->IF1CRQ = MSG_OBJ_BCAST_RX_ID & CAN_IF1CRQ_MNUM_M;
}

//*****************************************************************************
//
//! This function reads data from the receive message object.
//!
//! \param pui8Data is a pointer to the buffer to store the data read from the
//! CAN controller.
//! \param pui32MsgID is a pointer to the ID that was received with the data.
//!
//! This function will reads and acknowledges the data read from the message
//! object used to receive all CAN firmware update messages.  It will also
//! return the message identifier as this holds the API number that was
//! attached to the data.  This message identifier should be one of the
//! SL_API_UPD_* definitions.
//!
//! \return The number of valid bytes returned in the \e pui8Data buffer or
//! 0xffffffff if data was overwritten in the buffer.
//
//*****************************************************************************
static uint32_t
CANMessageGetRx(uint8_t *pui8Data, uint32_t *pui32MsgID)
{
    uint16_t ui16CmdMaskReg;
    uint16_t ui16ArbReg0, ui16ArbReg1;
    uint16_t ui16MsgCtrl;
    uint32_t ui32Bytes;
    uint16_t *pui16Data;

    //
    // This is always a read to the Message object as this call is setting a
    // message object.
    // Clear a pending interrupt and new data in a message object.
    //
    ui16CmdMaskReg = (CAN_IF2CMSK_DATAA | CAN_IF2CMSK_DATAB |
                      CAN_IF2CMSK_CONTROL | CAN_IF2CMSK_CLRINTPND |
                      CAN_IF2CMSK_ARB);

    //
    // Set up the request for data from the message object.
    //
    CAN0->IF2CMSK = ui16CmdMaskReg;

    //
    // Transfer the message object to the message object specific by
    // MSG_OBJ_BCAST_RX_ID.
    //
    CAN0->IF2CRQ = MSG_OBJ_BCAST_RX_ID & CAN_IF1CRQ_MNUM_M;

    //
    // Wait for busy bit to clear
    //
    while(CAN0->IF2CRQ & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // Read out the IF Registers.
    //
    ui16ArbReg0 = CAN0->IF2ARB1;
    ui16ArbReg1 = CAN0->IF2ARB2;
    ui16MsgCtrl = CAN0->IF2MCTL;

    //
    // Set the 29 bit version of the Identifier for this message object.
    //
    *pui32MsgID = ((ui16ArbReg1 & CAN_IF1ARB2_ID_M) << 16) | ui16ArbReg0;

    //
    // See if there is new data available.
    //
    if((ui16MsgCtrl & (CAN_IF1MCTL_NEWDAT | CAN_IF1MCTL_MSGLST)) ==
       CAN_IF1MCTL_NEWDAT)
    {
        //
        // Get the amount of data needed to be read.
        //
        ui32Bytes = ui16MsgCtrl & CAN_IF1MCTL_DLC_M;

        //
        // Read out the data from the CAN registers 16 bits at a time.
        //
        pui16Data = (uint16_t *)pui8Data;

        pui16Data[0] = CAN0->IF2DA1;
        pui16Data[1] = CAN0->IF2DA2;
        pui16Data[2] = CAN0->IF2DB1;
        pui16Data[3] = CAN0->IF2DB2;

        //
        // Now clear out the new data flag.
        //
        CAN0->IF2CMSK = CAN_IF1CMSK_NEWDAT;

        //
        // Transfer the message object to the message object specific by
        // MSG_OBJ_BCAST_RX_ID.
        //
        CAN0->IF2CRQ = MSG_OBJ_BCAST_RX_ID;

        //
        // Wait for busy bit to clear
        //
        while(CAN0->IF2CRQ & CAN_IF2CRQ_BUSY)
        {
        }
    }
    else
    {
        //
        // Data was lost so inform the caller.
        //
        ui32Bytes = 0xffffffff;
    }
    return(ui32Bytes);
}

//*****************************************************************************
//
//! This function sends data using the transmit message object.
//!
//! \param ui32Id is the ID to use with this message.
//! \param pui8Data is a pointer to the buffer with the data to be sent.
//! \param ui32Size is the number of bytes to send and should not be more than
//! 8 bytes.
//!
//! This function will reads and acknowledges the data read from the message
//! object used to receive all CAN firmware update messages.  It will also
//! return the message identifier as this holds the API number that was
//! attached to the data.  This message identifier should be one of the
//! SL_API_UPD_* definitions.
//!
//! \return None.
//
//*****************************************************************************
static void
CANMessageSetTx(uint32_t ui32Id, const uint8_t *pui8Data, uint32_t ui32Size)
{
    uint16_t ui16CmdMaskReg;
    uint16_t ui16ArbReg0, ui16ArbReg1;
    uint16_t ui16MsgCtrl;
    uint16_t *pui16Data;

    //
    // Wait for busy bit to clear
    //
    while(CAN0->IF1CRQ & CAN_IF1CRQ_BUSY)
    {
    }

    //
    // This is always a write to the Message object as this call is setting a
    // message object.  This call will also always set all size bits so it sets
    // both data bits.  The call will use the CONTROL register to set control
    // bits so this bit needs to be set as well.
    //
    ui16CmdMaskReg = (CAN_IF1CMSK_WRNRD | CAN_IF1CMSK_DATAA |
                      CAN_IF1CMSK_DATAB | CAN_IF1CMSK_CONTROL |
                      CAN_IF1CMSK_ARB);

    //
    // Set the 29 bit version of the Identifier for this message object.
    //
    ui16ArbReg0 = ui32Id & CAN_IF1ARB1_ID_M;

    //
    // Mark the message as valid and set the extended ID bit.
    //
    ui16ArbReg1 = (((ui32Id >> 16) & CAN_IF1ARB2_ID_M) |
                   (CAN_IF1ARB2_DIR | CAN_IF1ARB2_MSGVAL | CAN_IF1ARB2_XTD));

    //
    // Set the TXRQST bit and the reset the rest of the register.
    // Set the data length since this is set for all transfers.  This is also a
    // single transfer and not a FIFO transfer so set EOB bit.
    //
    //
    ui16MsgCtrl = (CAN_IF1MCTL_TXRQST | CAN_IF1MCTL_EOB |
                   (ui32Size & CAN_IF1MCTL_DLC_M));

    pui16Data = (uint16_t *)pui8Data;

    //
    // Write the data out to the CAN Data registers if needed.
    //
    CAN0->IF1DA1 = pui16Data[0];
    CAN0->IF1DA2 = pui16Data[1];
    CAN0->IF1DB1 = pui16Data[2];
    CAN0->IF1DB2 = pui16Data[3];

    //
    // Write out the registers to program the message object.
    //
    CAN0->IF1CMSK = ui16CmdMaskReg;
    CAN0->IF1ARB1 = ui16ArbReg0;
    CAN0->IF1ARB2 = ui16ArbReg1;
    CAN0->IF1MCTL = ui16MsgCtrl;

    //
    // Transfer the message object to the message object specifiec by
    // MSG_OBJ_BCAST_RX_ID.
    //
    CAN0->IF1CRQ = MSG_OBJ_BCAST_TX_ID & CAN_IF1CRQ_MNUM_M;
}

//*****************************************************************************
//
//! Configures the CAN interface.
//!
//! \param ui32SetTiming determines if the CAN bit timing should be configured.
//!
//! This function configures the CAN controller, preparing it for use by
//! the boot loader.   If the \e ui32SetTiming parameter is 0, the bit timing
//! for the CAN bus will be left alone.  This occurs when the boot loader was
//! entered from a running application that already has configured the timing
//! for the system.  When \e ui32SetTiming is non-zero the bit timing will be
//! set to the defaults defined in the <tt>bl_config.h</tt> file in the
//! project.
//!
//! \return None.
//
//*****************************************************************************
static void
ConfigureCANInterface(uint32_t ui32SetTiming)
{
    //
    // Reset the state of all the message object and the state of the CAN
    // module to a known state.
    //
    BL_CANInit();

    //
    // If a device identifier was specified then this was due to an update from
    // a running CAN application so don't change the CAN bit timing.
    //
    if(ui32SetTiming != 0)
    {
        //
        // Set the bit fields of the bit timing register according to the
        // parms.
        //
        CAN0->BIT = CAN_BIT_TIMING;

        //
        // Set the divider upper bits in the extension register.
        //
        CAN0->BRPE = 0;
    }

    //
    // Take the CAN0 device out of INIT state.
    //
    CAN0->CTL = 0;

    //
    // Configure the broadcast receive message object.
    //
    CANMessageSetRx();
}

//*****************************************************************************
//
// Reads the next packet that is sent to the boot loader.
//
//*****************************************************************************
static uint32_t
PacketRead(uint8_t *pui8Data, uint32_t *pui32Size)
{
    uint32_t ui32MsgID;

#ifdef CAN_UART_BRIDGE
    uint32_t ui32Size, ui32Length, ui32Mode, ui32Char;
    uint8_t pui8Buffer[12];

    //
    // Initialize the size and length of the packet.
    //
    ui32Length = 0;
    ui32Size = 0;

    //
    // If no interface has been determined then wait for either CAN or UART
    // data until either responds.
    //
    if(g_ui32Interface == IFACE_UNKNOWN)
    {
        //
        // Wait for CAN or UART data.
        //
        while((CAN0->NWDA1 == 0) &&
              ((UART0->FR & UART_FR_RXFE) == UART_FR_RXFE))
        {
        }

        //
        // If the UART FIFO was empty then the loop exited due to a CAN
        // message.
        //
        if((UART0->FR & UART_FR_RXFE) == UART_FR_RXFE)
        {
            g_ui32Interface = IFACE_CAN;
        }
        else
        {
            //
            // The UART FIFO was not empty so the UART interface was used.
            //
            g_ui32Interface = IFACE_UART;
        }
    }

    //
    // Read a data packet from the CAN controller.
    //
    if(g_ui32Interface == IFACE_CAN)
    {
#endif
        //
        // Wait until a packet has been received.
        //
        while(CAN0->NWDA1 == 0)
        {
        }

        //
        // Read the packet.
        //
        *pui32Size = CANMessageGetRx(pui8Data, &ui32MsgID);
#ifdef CAN_UART_BRIDGE
    }
    else
    {
        //
        // Read a data packet from the UART controller.
        //
        ui32Mode = 0;

        while(1)
        {
            //
            // Wait until a char is available.
            //
            while(UART0->FR & UART_FR_RXFE)
            {
            }

            //
            // Now get the char.
            //
            ui32Char = UART0->DR;

            if(ui32Char == 0xff)
            {
                ui32Mode = 1;
                ui32Length = 0;
            }
            else if(ui32Mode == 1)
            {
                if(ui32Char > 12)
                {
                    ui32Mode = 0;
                }
                else
                {
                    ui32Size = ui32Char;
                    ui32Mode = 2;
                }
            }
            else if(ui32Mode == 3)
            {
                if(ui32Char == 0xfe)
                {
                    pui8Buffer[ui32Length++] = 0xff;
                    ui32Mode = 2;
                }
                else if(ui32Char == 0xfd)
                {
                    pui8Buffer[ui32Length++] = 0xfe;
                    ui32Mode = 2;
                }
                else
                {
                    ui32Mode = 0;
                }
            }
            else if(ui32Mode == 2)
            {
                if(ui32Char == 0xfe)
                {
                    ui32Mode = 3;
                }
                else
                {
                    pui8Buffer[ui32Length++] = ui32Char;
                }
            }

            if((ui32Length == ui32Size) && (ui32Mode == 2))
            {
                ui32MsgID = *(uint32_t *)pui8Buffer;

                if((ui32MsgID & (CAN_MSGID_MFR_M | CAN_MSGID_DTYPE_M)) ==
                   SL_API_UPD)
                {
                    *(uint32_t *)pui8Data =
                        *(uint32_t *)(pui8Buffer + 4);
                    *(uint32_t *)(pui8Data + 4) =
                        *(uint32_t *)(pui8Buffer + 8);
                    *pui32Size = ui32Size - 4;
                    break;
                }
            }
        }
    }
#endif

    //
    // Return the message ID of the packet that was received.
    //
    return(ui32MsgID);
}

//*****************************************************************************
//
// This function writes out an individual character over the UART and
// handles sending out special sequences for handling 0xff and 0xfe values.
//
//*****************************************************************************
#ifdef CAN_UART_BRIDGE
static void
UARTBridgeWrite(uint32_t ui32Char)
{
    //
    // See if the character being sent is 0xff.
    //
    if(ui32Char == 0xff)
    {
        //
        // Send 0xfe 0xfe, the escaped version of 0xff.  A sign extended
        // version of 0xfe is used to avoid the check below for 0xfe, thereby
        // avoiding an infinite loop.  Only the lower 8 bits are actually sent,
        // so 0xfe is what is actually transmitted.
        //
        UARTBridgeWrite(0xfffffffe);
        UARTBridgeWrite(0xfffffffe);
    }

    //
    // Otherwise, see if the character being sent is 0xfe.
    //
    else if(ui32Char == 0xfe)
    {
        //
        // Send 0xfe 0xfd, the escaped version of 0xfe.  A sign extended
        // version of 0xfe is used to avoid the check above for 0xfe, thereby
        // avoiding an infinite loop.  Only the lower 8 bits are actually sent,
        // so 0xfe is what is actually transmitted.
        //
        UARTBridgeWrite(0xfffffffe);
        UARTBridgeWrite(0xfd);
    }

    //
    // Otherwise, simply send this character.
    //
    else
    {
        //
        // Wait until space is available in the UART transmit FIFO.
        //
        while(UART0->FR & UART_FR_TXFF)
        {
        }

        //
        // Send the char.
        //
        UART0->DR = ui32Char & 0xff;
    }
}
#endif

//*****************************************************************************
//
// Sends a packet to the controller that is communicating with the boot loader.
//
//*****************************************************************************
static void
PacketWrite(uint32_t ui32Id, const uint8_t *pui8Data, uint32_t ui32Size)
{
    uint32_t ui32Idx;

#ifdef CAN_UART_BRIDGE
    //
    // Check if the boot loader is in CAN mode.
    //
    if(g_ui32Interface == IFACE_CAN)
    {
#endif
        //
        // Wait until the previous packet has been sent, providing a time out so
        // that the boot loader does not hang here.
        //
        for(ui32Idx = 1000;
            (ui32Idx != 0) && (CAN0->TXRQ1 != 0);
            ui32Idx--)
        {
        }

        //
        // If the previous packet was sent, then send this packet.
        //
        if(ui32Idx != 0)
        {
            CANMessageSetTx(ui32Id, pui8Data, ui32Size);
        }
#ifdef CAN_UART_BRIDGE
    }
    else
    {
        //
        // The boot loader is in UART modes so write the packet using the UART
        // functions.  Write the start pattern followed by the size, and the ID.
        //
        UARTBridgeWrite(0xffffffff);
        UARTBridgeWrite(ui32Size + 4);
        UARTBridgeWrite(ui32Id & 0xff);
        UARTBridgeWrite((ui32Id >> 8) & 0xff);
        UARTBridgeWrite((ui32Id >> 16) & 0xff);
        UARTBridgeWrite((ui32Id >> 24) & 0xff);

        //
        // Now write out the remaining data bytes.
        //
        while(ui32Size--)
        {
            UARTBridgeWrite(*pui8Data++);
        }
    }
#endif
}

//*****************************************************************************
//
//! This is the main routine for handling updating over CAN.
//!
//! This function accepts boot loader commands over CAN to perform a firmware
//! update over the CAN bus.  This function assumes that the CAN bus timing
//! and message objects have been configured elsewhere.
//!
//! \return None.
//
//*****************************************************************************
void
UpdaterCAN(void)
{
    uint32_t ui32Bytes;
    uint32_t ui32Cmd;
    uint32_t ui32FlashSize;
    uint32_t ui32Temp;
    uint8_t ui8Status;

#ifdef ENABLE_UPDATE_CHECK
    //
    // Check the application is valid and check the pin to see if an update is
    // being requested.
    //
    if(g_ui32Forced == 1)
    {
        //
        // Send out the CAN request.
        //
#ifdef CAN_UART_BRIDGE
        g_ui32Interface = IFACE_CAN;
#endif
        PacketWrite(SL_API_UPD_REQUEST, 0, 0);

        //
        // Send out the UART request.
        //
#ifdef CAN_UART_BRIDGE
        g_ui32Interface = IFACE_UART;
        PacketWrite(SL_API_UPD_REQUEST, 0, 0);
        g_ui32Interface = IFACE_UNKNOWN;
#endif

        //
        // Wait only 50ms for the response and move on otherwise.
        //
        Delay(CRYSTAL_FREQ / 20);

        //
        // Wait until a packet has been received.
        //
#ifdef CAN_UART_BRIDGE
        if((CAN0->NWDA1 == 0) &&
           (UART0->FR & UART_FR_RXFE == UART_FR_RXFE))
#else
        if(CAN0->NWDA1 == 0)
#endif
        {
            //
            // Call the application.
            //
            StartApplication();
        }
    }
#endif

    //
    // Loop forever processing packets.
    //
    while(1)
    {
        //
        // Read the next packet.
        //
        ui32Bytes = 0;
        ui32Cmd = PacketRead(g_pui8CommandBuffer, &ui32Bytes);

        //
        // Handle this packet.
        //
        ui8Status = CAN_CMD_SUCCESS;
        switch(ui32Cmd)
        {
            //
            // This is an update request packet.
            //
            case SL_API_UPD_REQUEST:
            {
                //
                // This packet is ignored (other than generating an ACK).
                //
                break;
            }

            //
            // This is a ping packet.
            //
            case SL_API_UPD_PING:
            {
                //
                // This packet is ignored (other than generating an ACK).
                //
                break;
            }

            //
            // This is a reset packet.
            //
            case SL_API_UPD_RESET:
            {
                //
                // Perform a software reset request.  This will cause the
                // microcontroller to reset; no further code will be executed.
                //
                SCB->AIRCR = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

                //
                // The microcontroller should have reset, so this should never
                // be reached.  Just in case, loop forever.
                //
                while(1)
                {
                }
            }

            //
            // This is a data packet.
            //
            case SL_API_UPD_SEND_DATA:
            {
                //
                // If this is overwriting the boot loader then the application
                // has already been erased so now erase the boot loader.
                //
                if(g_ui32TransferAddress == 0)
                {
                    //
                    // Clear the flash access interrupt.
                    //
                    BL_FLASH_CL_ERR_FN_HOOK();

                    //
                    // Erase the application before the boot loader.
                    //
                    for(ui32Temp = 0; ui32Temp < APP_START_ADDRESS;
                        ui32Temp += FLASH_PAGE_SIZE)
                    {
                        //
                        // Erase this block.
                        //
                        BL_FLASH_ERASE_FN_HOOK(ui32Temp);
                    }

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        //
                        // Setting g_ui32TransferSize to zero makes
                        // COMMAND_SEND_DATA fail to accept any more data.
                        //
                        g_ui32TransferSize = 0;

                        //
                        // Indicate that the flash erase failed.
                        //
                        ui8Status = CAN_CMD_FAIL;
                    }
                }

                //
                // Check if there are any more bytes to receive.
                //
                if(g_ui32TransferSize >= ui32Bytes)
                {
                    //
                    // Decrypt the data if required.
                    //
#ifdef BL_DECRYPT_FN_HOOK
                    BL_DECRYPT_FN_HOOK(g_pui8CommandBuffer, ui32Bytes);
#endif

                    //
                    // Clear the flash access interrupt.
                    //
                    BL_FLASH_CL_ERR_FN_HOOK();

                    //
                    // Skip the first transfer.
                    //
                    if(g_ui32StartSize == g_ui32TransferSize)
                    {
                        g_ui32StartValues[0] =
                            *((uint32_t *)&g_pui8CommandBuffer[0]);
                        g_ui32StartValues[1] =
                            *((uint32_t *)&g_pui8CommandBuffer[4]);
                    }
                    else
                    {
                        //
                        // Loop over the words to program.
                        //
                        BL_FLASH_PROGRAM_FN_HOOK(g_ui32TransferAddress,
                                                 g_pui8CommandBuffer,
                                                 ui32Bytes);
                    }

                    //
                    // Return an error if an access violation occurred.
                    //
                    if(BL_FLASH_ERROR_FN_HOOK())
                    {
                        //
                        // Indicate that the flash programming failed.
                        //
                        ui8Status = CAN_CMD_FAIL;
                    }
                    else
                    {
                        //
                        // Now update the address to program.
                        //
                        g_ui32TransferSize -= ui32Bytes;
                        g_ui32TransferAddress += ui32Bytes;

                        //
                        // If a progress hook function has been provided, call
                        // it here.
                        //
#ifdef BL_PROGRESS_FN_HOOK
                        BL_PROGRESS_FN_HOOK(g_ui32StartSize -
                                            g_ui32TransferSize,
                                            g_ui32StartSize);
#endif
                    }
                }
                else
                {
                    //
                    // This indicates that too much data is being sent to the
                    // device.
                    //
                    ui8Status = CAN_CMD_FAIL;
                }

                //
                // If the last expected bytes were received then write out the
                // first two words of the image to allow it to boot.
                //
                if(g_ui32TransferSize == 0)
                {
                    //
                    // Loop over the words to program.
                    //
                    BL_FLASH_PROGRAM_FN_HOOK(g_ui32StartAddress,
                                             (uint8_t *)&g_ui32StartValues,
                                             8);

                    //
                    // If an end signal hook function has been provided, call
                    // it here since we have finished a download.
                    //
#ifdef BL_END_FN_HOOK
                    BL_END_FN_HOOK();
#endif
                }
                break;
            }

            //
            // This is a start download packet.
            //
            case SL_API_UPD_DOWNLOAD:
            {
                //
                // Get the application address and size from the packet data.
                //
                g_ui32TransferAddress =
                    *((uint32_t *)&g_pui8CommandBuffer[0]);
                g_ui32TransferSize = *((uint32_t *)&g_pui8CommandBuffer[4]);
                g_ui32StartSize = g_ui32TransferSize;
                g_ui32StartAddress = g_ui32TransferAddress;

                //
                // Check for a valid starting address and image size.
                //
                if(!BL_FLASH_AD_CHECK_FN_HOOK(g_ui32TransferAddress,
                                              g_ui32TransferSize))
                {
                    //
                    // Set the code to an error to indicate that the last
                    // command failed.  This informs the updater program
                    // that the download command failed.
                    //
                    ui8Status = CAN_CMD_FAIL;

                    //
                    // This packet has been handled.
                    //
                    break;
                }

                //
                // Only erase the space that we need if we are not protecting
                // the code, otherwise erase the entire flash.
                //
#ifdef FLASH_CODE_PROTECTION
                ui32FlashSize = BL_FLASH_SIZE_FN_HOOK();
#ifdef FLASH_RSVD_SPACE
                if((ui32FlashSize - FLASH_RSVD_SPACE) != g_ui32TransferAddress)
                {
                    ui32FlashSize -= FLASH_RSVD_SPACE;
                }
#endif
#else
                ui32FlashSize = g_ui32TransferAddress + g_ui32TransferSize;
#endif

                //
                // Clear the flash access interrupt.
                //
                BL_FLASH_CL_ERR_FN_HOOK();

                //
                // Leave the boot loader present until we start getting an
                // image.
                //
                for(ui32Temp = g_ui32TransferAddress; ui32Temp < ui32FlashSize;
                    ui32Temp += FLASH_PAGE_SIZE)
                {
                    //
                    // Erase this block.
                    //
                    BL_FLASH_ERASE_FN_HOOK(ui32Temp);
                }

                //
                // Return an error if an access violation occurred.
                //
                if(BL_FLASH_ERROR_FN_HOOK())
                {
                    ui8Status = CAN_CMD_FAIL;
                }

                //
                // See if the command was successful.
                //
                if(ui8Status != CAN_CMD_SUCCESS)
                {
                    //
                    // Setting g_ui32TransferSize to zero makes
                    // COMMAND_SEND_DATA fail to accept any data.
                    //
                    g_ui32TransferSize = 0;
                }
#ifdef BL_START_FN_HOOK
                else
                {
                    //
                    // If a start signal hook function has been provided, call
                    // it here since we are about to start a new download.
                    //
                    BL_START_FN_HOOK();
                }
#endif

                break;
            }

            //
            // This is an unknown packet.
            //
            default:
            {
                //
                // Set the status to indicate a failure.
                //
                ui8Status = CAN_CMD_FAIL;
                break;
            }
        }

        //
        // Send an ACK packet in response to indicate that the packet was
        // received.  The status in the ACK data indicates if the command was
        // successfully processed.
        //
        PacketWrite(SL_API_UPD_ACK, &ui8Status, 1);
    }
}

//*****************************************************************************
//
// Configures the UART used for CAN traffic bridging.
//
//*****************************************************************************
#ifdef CAN_UART_BRIDGE
void
ConfigureBridge(void)
{
    //
    // Enable the GPIO module if necessary.
    //
#if (CAN_RX_PERIPH != SYSCTL_RCGCGPIO_R0) && \
    (CAN_TX_PERIPH != SYSCTL_RCGCGPIO_R0)
    SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R0;
#endif

    //
    // Enable the UART module.
    //
    SYSCTL->RCGCUART |= SYSCTL_RCGCUART_R0;

    //
    // Enable the GPIO pins used for the UART.
    //
    GPIOA->DEN  |= (UART_TX | UART_RX);
    GPIOA->PCTL |= (UART_TX_PCTL | UART_RX_PCTL);

    //
    // Configure the UART.
    //
    UART0->IBRD = UART_BAUD_RATIO(115200) >> 6;
    UART0->FBRD = (UART_BAUD_RATIO(115200) &
                   UART_FBRD_DIVFRAC_M);
    UART0->LCRH = UART_LCRH_WLEN_8 | UART_LCRH_FEN;
    UART0->UART = (UART_CTL_UARTEN | UART_CTL_TXE |
                         UART_CTL_RXE);
}
#endif

//*****************************************************************************
//
//! This is the application entry point to the CAN updater.
//!
//! This function should only be entered from a running application and not
//! when running the boot loader with no application present.
//!
//! \return None.
//
//*****************************************************************************
void
AppUpdaterCAN(void)
{
    //
    // If the boot loader is being called from the application the UART needs
    // to be configured.
    //
#ifdef CAN_UART_BRIDGE
    ConfigureBridge();
#endif

    //
    // Configure the CAN controller but don't change the bit timing.
    //
    ConfigureCANInterface(0);

    //
    // Call the main update routine.
    //
    UpdaterCAN();
}

//*****************************************************************************
//
//! Generic configuration is handled in this function.
//!
//! This function is called by the start up code to perform any configuration
//! necessary before calling the update routine.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureCAN(void)
{
#ifdef CRYSTAL_FREQ
    //
    // Since the crystal frequency was specified, enable the main oscillator
    // and clock the processor from it. Check for whether the Oscillator range
    // has to be set and wait states need to be updated
    //
    if(CRYSTAL_FREQ >= 10000000)
    {
        SYSCTL->MOSCCTL |= (SYSCTL_MOSCCTL_OSCRNG);
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN | SYSCTL_MOSCCTL_NOXTAL);
    }
    else
    {
        SYSCTL->MOSCCTL &= ~(SYSCTL_MOSCCTL_PWRDN | SYSCTL_MOSCCTL_NOXTAL);
    }

    //
    // Wait for the Oscillator to Stabilize
    //
    Delay(524288);

    if(CRYSTAL_FREQ > 16000000)
    {
    	SYSCTL->MEMTIM0  = (SYSCTL_MEMTIM0_FBCHT_1_5 | (1 << SYSCTL_MEMTIM0_FWS_S) |
                		    SYSCTL_MEMTIM0_EBCHT_1_5 | (1 << SYSCTL_MEMTIM0_EWS_S) |
                			SYSCTL_MEMTIM0_MB1);
    	SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_MEMTIMU | SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }
    else
    {
    	SYSCTL->RSCLKCFG = (SYSCTL_RSCLKCFG_OSCSRC_MOSC);
    }
#endif

    //
    // Enable the CAN controller.
    //
    SYSCTL->RCGCCAN |= SYSCTL_RCGCCAN_R0;

#if CAN_RX_PERIPH == CAN_TX_PERIPH
    //
    // Enable the GPIO associated with CAN0
    //
    SYSCTL->RCGCGPIO |= CAN_RX_PERIPH;

    //
    // Wait a while before accessing the peripheral.
    //
    Delay(3);

    //
    // Set the alternate function selects.
    //
    CAN_RX_PORT->AFSEL |= CAN_RX_PIN_M | CAN_TX_PIN_M;

    //
    // Set the port control selects.
    //
    CAN_RX_PORT->PCTL |= CAN_RX_PIN_PCTL_M | CAN_TX_PIN_PCTL_M;

    //
    // Set the pin type to it's digital function.
    //
    CAN_RX_PORT->DEN |= CAN_RX_PIN_M | CAN_TX_PIN_M;

#else
    //
    // Enable the GPIO associated with CAN0
    //
    SYSCTL->RCGCGPIO |= CAN_RX_PERIPH | CAN_TX_PERIPH;

    //
    // Wait a while before accessing the peripheral.
    //
    Delay(3);

    //
    // Set the alternate function selects.
    //
    CAN_RX_PORT->AFSEL |= CAN_RX_PIN_M;
    CAN_TX_PORT->AFSEL |= CAN_TX_PIN_M;

    //
    // Set the port control selects.
    //
    CAN_RX_PORT->PCTL  |= CAN_RX_PIN_PCTL_M;
    CAN_TX_PORT->PCTL  |= CAN_TX_PIN_PCTL_M;

    //
    // Set the pin type to it's digital function.
    //
    CAN_RX_PORT->DEN   |= CAN_RX_PIN_M;
    CAN_TX_PORT->DEN   |= CAN_TX_PIN_M;
#endif

    //
    // Configure the UART used for bridging.
    //
#ifdef CAN_UART_BRIDGE
    ConfigureBridge();
#endif

    //
    // Configure the CAN interface.
    //
    ConfigureCANInterface(1);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
