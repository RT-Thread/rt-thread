//*****************************************************************************
//
// bl_emac.c - Functions to update via Ethernet.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/driverlib/driverlib.h"
#include "ti/devices/msp432e4/boot_loader/bl_decrypt.h"
#include "ti/devices/msp432e4/boot_loader/bl_flash.h"
#include "ti/devices/msp432e4/boot_loader/bl_hooks.h"

//*****************************************************************************
//
//! \addtogroup bl_emac_api
//! @{
//
//*****************************************************************************

#if defined(ENET_ENABLE_UPDATE) || defined(DOXYGEN)
//*****************************************************************************
//
// Make sure that the crystal frequency is defined.
//
//*****************************************************************************
#if !defined(CRYSTAL_FREQ)
#error ERROR: CRYSTAL_FREQ must be defined for Ethernet update!
#endif

//*****************************************************************************
//
// Make sure that boot loader update is not enabled (it is not supported via
// BOOTP given that there is no way to distinguish between a normal firmware
// image and a boot loader update image).
//
//*****************************************************************************
#if defined(ENABLE_BL_UPDATE)
#error ERROR: Updating the boot loader is not supported over Ethernet!
#endif

//*****************************************************************************
//
// TFTP packets contain 512 bytes of data and a packet shorter than this
// indicates the end of the transfer.
//
//*****************************************************************************
#define TFTP_BLOCK_SIZE         512

//*****************************************************************************
//
// uIP uses memset, so a simple one is provided here.  This is not as efficient
// as the one in the C library (from an execution time perspective), but it is
// much smaller.
//
//*****************************************************************************
void *
my_memset(void *pvDest, int iChar, size_t i32Length)
{
    int8_t *pi8Buf = (int8_t *)pvDest;

    //
    // Fill the buffer with the given character.
    //
    while(i32Length--)
    {
        *pi8Buf++ = iChar;
    }

    //
    // Return a pointer to the beginning of the buffer.
    //
    return(pvDest);
}

//*****************************************************************************
//
// uIP uses memcpy, so a simple one is provided here.  This is not as efficient
// as the one in the C library (from an execution time perspective), but it is
// much smaller.
//
//*****************************************************************************
void *
my_memcpy(void *pvDest, const void *pvSrc, size_t i32Length)
{
    const int8_t *pi8Src = (const int8_t *)pvSrc;
    int8_t *pi8Dest = (int8_t *)pvDest;

    //
    // Copy bytes from the source buffer to the destination buffer.
    //
    while(i32Length--)
    {
        *pi8Dest++ = *pi8Src++;
    }

    //
    // Return a pointer to the beginning of the destination buffer.
    //
    return(pvDest);
}

//*****************************************************************************
//
// Directly include the uIP code if using Ethernet for the update.  This allows
// non-Ethernet boot loader builds to not have to supply the uip-conf.h file
// that would otherwise be required.
//
//*****************************************************************************
#define memcpy my_memcpy
#define memset my_memset
#undef htonl
#undef ntohl
#undef htons
#undef ntohs
#include "uip-1.0/uip/pt.h"
#include "uip-1.0/uip/uip_arp.h"
#undef BUF
#include "uip-1.0/uip/uip.h"

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(uint32_t ui32Count);

//*****************************************************************************
//
// Defines for setting up the system clock.
//
//*****************************************************************************
#define SYSTICKHZ               100
#define SYSTICKMS               (1000 / SYSTICKHZ)

//*****************************************************************************
//
// UIP Timers (in ms)
//
//*****************************************************************************
#define UIP_PERIODIC_TIMER_MS   50
#define UIP_ARP_TIMER_MS        10000

//*****************************************************************************
//
// This structure defines the fields in a BOOTP request/reply packet.
//
//*****************************************************************************
typedef struct
{
    //
    // The operation; 1 is a request, 2 is a reply.
    //
    uint8_t ui8Op;

    //
    // The hardware type; 1 is Ethernet.
    //
    uint8_t ui8HType;

    //
    // The hardware address length; for Ethernet this will be 6, the length of
    // the MAC address.
    //
    uint8_t ui8HLen;

    //
    // Hop count, used by gateways for cross-gateway booting.
    //
    uint8_t ui8Hops;

    //
    // The transaction ID.
    //
    uint32_t ui32XID;

    //
    // The number of seconds elapsed since the client started trying to boot.
    //
    uint16_t ui16Secs;

    //
    // The BOOTP flags.
    //
    uint16_t ui16Flags;

    //
    // The client's IP address, if it knows it.
    //
    uint32_t ui32CIAddr;

    //
    // The client's IP address, as assigned by the BOOTP server.
    //
    uint32_t ui32YIAddr;

    //
    // The TFTP server's IP address.
    //
    uint32_t ui32SIAddr;

    //
    // The gateway IP address, if booting cross-gateway.
    //
    uint32_t ui32GIAddr;

    //
    // The hardware address; for Ethernet this is the MAC address.
    //
    uint8_t pui8CHAddr[16];

    //
    // The name, or nickname, of the server that should handle this BOOTP
    // request.
    //
    char pcSName[64];

    //
    // The name of the boot file to be loaded via TFTP.
    //
    char pcFile[128];

    //
    // Optional vendor-specific area; not used for BOOTP.
    //
    uint8_t pui8Vend[64];
}
tBOOTPPacket;

//*****************************************************************************
//
// The BOOTP commands.
//
//*****************************************************************************
#define BOOTP_REQUEST           1
#define BOOTP_REPLY             2

//*****************************************************************************
//
// The TFTP commands.
//
//*****************************************************************************
#define TFTP_RRQ                1
#define TFTP_WRQ                2
#define TFTP_DATA               3
#define TFTP_ACK                4
#define TFTP_ERROR              5

//*****************************************************************************
//
// The UDP ports used by the BOOTP protocol.
//
//*****************************************************************************
#define BOOTP_SERVER_PORT       67
#define BOOTP_CLIENT_PORT       68

//*****************************************************************************
//
// The UDP port for the TFTP server.
//
//*****************************************************************************
#define TFTP_PORT               69

//*****************************************************************************
//
// The MAC address of the Ethernet interface.
//
//*****************************************************************************
#ifdef ENET_MAC_ADDR0
static struct uip_eth_addr g_sMACAddr =
{
    {
        ENET_MAC_ADDR0,
        ENET_MAC_ADDR1,
        ENET_MAC_ADDR2,
        ENET_MAC_ADDR3,
        ENET_MAC_ADDR4,
        ENET_MAC_ADDR5
    }
};
#else
static struct uip_eth_addr g_sMACAddr;
#endif

//*****************************************************************************
//
// The number of SysTick interrupts since the start of the boot loader.
//
//*****************************************************************************
static uint32_t g_ui32Ticks;

//*****************************************************************************
//
// The seed for the random number generator.
//
//*****************************************************************************
static uint32_t g_ui32RandomSeed;

//*****************************************************************************
//
// The number of milliseconds since the last call to uip_udp_periodic().
//
//*****************************************************************************
static volatile uint32_t g_ui32PeriodicTimer;

//*****************************************************************************
//
// The number of milliseconds since the last call to uip_arp_timer().
//
//*****************************************************************************
static volatile uint32_t g_ui32ARPTimer;

//*****************************************************************************
//
// The transaction ID of the most recently sent out BOOTP request.
//
//*****************************************************************************
static uint32_t g_ui32XID;

//*****************************************************************************
//
// The state for the proto-thread that handles the BOOTP process.
//
//*****************************************************************************
static struct pt g_sThread;

//*****************************************************************************
//
// The amount of time to wait for a BOOTP reply before sending out a new BOOTP
// request.
//
//*****************************************************************************
static uint32_t g_ui32Delay;

//*****************************************************************************
//
// The target time (relative to g_ui32Ticks) when the next timeout occurs.
//
//*****************************************************************************
static uint32_t g_ui32Target;

//*****************************************************************************
//
// The IP address of the TFTP server.
//
//*****************************************************************************
static uip_ipaddr_t g_sServerAddr;

//*****************************************************************************
//
// The name of the file to be read from the TFTP server.
//
//*****************************************************************************
static char g_pcFilename[128];

//*****************************************************************************
//
// The end of flash.  If there is not a reserved block at the end of flash,
// this is the real end of flash.  If there is a reserved block, this is the
// start of the reserved block (i.e. the virtual end of flash).
//
//*****************************************************************************
static uint32_t g_ui32FlashEnd;

//*****************************************************************************
//
// The current block being read from the TFTP server.
//
//*****************************************************************************
static uint32_t g_ui32TFTPBlock;

//*****************************************************************************
//
// The number of TFTP retries.
//
//*****************************************************************************
static uint32_t g_ui32TFTPRetries;

//*****************************************************************************
//
// The UDP socket used to communicate with the BOOTP and TFTP servers (in
// sequence).
//
//*****************************************************************************
struct uip_udp_conn *g_pConn;

//*****************************************************************************
//
// The current link status.
//
//*****************************************************************************
static uint32_t g_ui32Link;

//*****************************************************************************
//
// Ethernet DMA descriptors.
//
// Although uIP uses a single buffer, the MAC hardware needs a minimum of
// 3 receive descriptors to operate.
//
//*****************************************************************************
#define NUM_TX_DESCRIPTORS 3
#define NUM_RX_DESCRIPTORS 3
tEMACDMADescriptor g_psRxDescriptor[NUM_TX_DESCRIPTORS];
tEMACDMADescriptor g_psTxDescriptor[NUM_RX_DESCRIPTORS];
uint32_t g_ui32RxDescIndex;
uint32_t g_ui32TxDescIndex;

//*****************************************************************************
//
// Transmit and receive buffers.
//
//*****************************************************************************
#define RX_BUFFER_SIZE 1536
#define TX_BUFFER_SIZE 1536
uint8_t g_pui8RxBuffer[RX_BUFFER_SIZE];
uint8_t g_pui8TxBuffer[TX_BUFFER_SIZE];

//*****************************************************************************
//
//! Handles the SysTick interrupt.
//!
//! This function is called when the SysTick interrupt occurs.  It simply
//! keeps a running count of interrupts, used as a time basis for the BOOTP and
//! TFTP protocols.
//!
//! \return None.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    //
    // Increment the tick count.
    //
    g_ui32Ticks++;
    g_ui32PeriodicTimer += SYSTICKMS;
    g_ui32ARPTimer += SYSTICKMS;
}

//*****************************************************************************
//
//! Computes a new random number.
//!
//! This function computes a new pseudo-random number, using a linear
//! congruence random number generator.  Note that if the entire 32-bits of the
//! produced random number are not being used, the upper N bits should be used
//! instead of the lower N bits as they are much more random (for example, use
//! ``RandomNumber() >> 28'' instead of ``RandomNumber() & 15'').
//!
//! \return Returns a 32-bit pseudo-random number.
//
//*****************************************************************************
static uint32_t
RandomNumber(void)
{
    //
    // Generate a new pseudo-random number with a linear congruence random
    // number generator.  This new random number becomes the seed for the next
    // random number.
    //
    g_ui32RandomSeed = (g_ui32RandomSeed * 1664525) + 1013904223;

    //
    // Return the new random number.
    //
    return(g_ui32RandomSeed);
}

//*****************************************************************************
//
// Read a packet from the DMA receive buffer into the uIP packet buffer.
//
//*****************************************************************************
static int32_t
PacketReceive(uint8_t *pui8Buf, int32_t i32BufLen)
{
    int_fast32_t i32FrameLen, i32Loop;

    //
    // By default, we assume we got a bad frame.
    //
    i32FrameLen = 0;

    //
    // See if the receive descriptor contains a valid frame.  Look for a
    // descriptor error, indicating that the incoming packet was truncated or,
    // if this is the last frame in a packet, the receive error bit.
    //
    if(!(g_psRxDescriptor[g_ui32RxDescIndex].ui32CtrlStatus &
         DES0_RX_STAT_ERR))
    {
        //
        // We have a valid frame so copy the content to the supplied buffer.
        // First check that the "last descriptor" flag is set.  We sized the
        // receive buffer such that it can always hold a valid frame so this
        // flag should never be clear at this point but...
        //
        if(g_psRxDescriptor[g_ui32RxDescIndex].ui32CtrlStatus &
           DES0_RX_STAT_LAST_DESC)
        {
            i32FrameLen =
                ((g_psRxDescriptor[g_ui32RxDescIndex].ui32CtrlStatus &
                  DES0_RX_STAT_FRAME_LENGTH_M) >>
                 DES0_RX_STAT_FRAME_LENGTH_S);

            //
            // Sanity check.  This shouldn't be required since we sized the uIP
            // buffer such that it's the same size as the DMA receive buffer
            // but, just in case...
            //
            if(i32FrameLen > i32BufLen)
            {
                i32FrameLen = i32BufLen;
            }

            //
            // Copy the data from the DMA receive buffer into the provided
            // frame buffer.
            //
            for(i32Loop = 0; i32Loop < i32FrameLen; i32Loop++)
            {
                pui8Buf[i32Loop] = g_pui8RxBuffer[i32Loop];
            }
        }
    }

    //
    // Move on to the next descriptor in the chain.
    //
    g_ui32RxDescIndex++;
    if(g_ui32RxDescIndex == NUM_RX_DESCRIPTORS)
    {
        g_ui32RxDescIndex = 0;
    }

    //
    // Mark the next descriptor in the ring as available for the receiver to
    // write into.
    //
    g_psRxDescriptor[g_ui32RxDescIndex].ui32CtrlStatus = DES0_RX_CTRL_OWN;

    //
    // Return the Frame Length
    //
    return(i32FrameLen);
}

//*****************************************************************************
//
// Transmit a packet from the supplied buffer.
//
//*****************************************************************************
static int32_t
PacketTransmit(uint8_t *pui8Buf, int32_t i32BufLen)
{
    int_fast32_t i32Loop;

    //
    // Wait for the previous packet to be transmitted.
    //
    while(g_psTxDescriptor[g_ui32TxDescIndex].ui32CtrlStatus &
          DES0_TX_CTRL_OWN)
    {
    }

    //
    // Check that we're not going to overflow the transmit buffer.  This
    // shouldn't be necessary since the uIP buffer is smaller than our DMA
    // transmit buffer but, just in case...
    //
    if(i32BufLen > TX_BUFFER_SIZE)
    {
        i32BufLen = TX_BUFFER_SIZE;
    }

    //
    // Copy the packet data into the transmit buffer.
    //
    for(i32Loop = 0; i32Loop < i32BufLen; i32Loop++)
    {
        g_pui8TxBuffer[i32Loop] = pui8Buf[i32Loop];
    }

    //
    // Move to the next descriptor.
    //
    g_ui32TxDescIndex++;
    if(g_ui32TxDescIndex == NUM_TX_DESCRIPTORS)
    {
        g_ui32TxDescIndex = 0;
    }

    //
    // Fill in the packet size and tell the transmitter to start work.
    //
    g_psTxDescriptor[g_ui32TxDescIndex].ui32Count = (uint32_t)i32BufLen;
    g_psTxDescriptor[g_ui32TxDescIndex].ui32CtrlStatus =
        (DES0_TX_CTRL_LAST_SEG | DES0_TX_CTRL_FIRST_SEG |
         DES0_TX_CTRL_INTERRUPT | DES0_TX_CTRL_IP_ALL_CKHSUMS |
         DES0_TX_CTRL_CHAINED | DES0_TX_CTRL_OWN);

    //
    // Tell the DMA to reacquire the descriptor now that we've filled it in.
    //
    ROM_EMACTxDMAPollDemand(EMAC0_BASE);

    //
    // Return the number of bytes sent.
    //
    return(i32BufLen);
}

//*****************************************************************************
//
//! Constructs and sends a BOOTP request packet.
//!
//! This function constructs a BOOTP request packet and sends it as a broadcast
//! message to the network.
//!
//! \return None.
//
//*****************************************************************************
static void
SendBOOTPRequest(void)
{
    uint8_t *pui8Packet = (uint8_t *)uip_appdata;
    tBOOTPPacket *psBOOTP = (tBOOTPPacket *)uip_appdata;
    uint32_t ui32Idx;

    //
    // Zero fill the BOOTP request packet.
    //
    for(ui32Idx = 0; ui32Idx < sizeof(tBOOTPPacket); ui32Idx++)
    {
        pui8Packet[ui32Idx] = 0;
    }

    //
    // Construct a BOOTP request.
    //
    psBOOTP->ui8Op = BOOTP_REQUEST;

    //
    // Set the hardware type to Ethernet.
    //
    psBOOTP->ui8HType = 0x01;

    //
    // Set the hardware address length to 6.
    //
    psBOOTP->ui8HLen = 0x06;

    //
    // Choose a random number for the transaction ID.
    //
    psBOOTP->ui32XID = g_ui32XID = RandomNumber();

    //
    // Set the number of seconds since we started.
    //
    psBOOTP->ui16Secs = HTONS(g_ui32Ticks / SYSTICKHZ);

    //
    // Fill in the Ethernet MAC address.
    //
    for(ui32Idx = 0; ui32Idx < 6; ui32Idx++)
    {
        psBOOTP->pui8CHAddr[ui32Idx] = g_sMACAddr.addr[ui32Idx];
    }

    //
    // Set the server name if defined.
    //
#ifdef ENET_BOOTP_SERVER
    for(ui32Idx = 0;
        (psBOOTP->pcSName[ui32Idx] = ENET_BOOTP_SERVER[ui32Idx]) != 0;
        ui32Idx++)
    {
    }
#endif

    //
    // Send the BOOTP request packet.
    //
    uip_udp_send(sizeof(tBOOTPPacket));
}

//*****************************************************************************
//
//! Parses a packet checking for a BOOTP reply message.
//!
//! This function parses a packet to determine if it is a BOOTP reply to our
//! currently outstanding BOOTP request.  If a valid reply is found, the
//! appropriate information from the packet is extracted and saved.
//!
//! \return Returns 1 if a valid BOOTP reply message was found and 0 otherwise.
//
//*****************************************************************************
static uint32_t
ParseBOOTPReply(void)
{
    tBOOTPPacket *psBOOTP = (tBOOTPPacket *)uip_appdata;
    uint32_t ui32Idx;

    //
    // See if this is a reply for our current BOOTP request.
    //
    if((psBOOTP->ui8Op != BOOTP_REPLY) ||
       (psBOOTP->ui32XID != g_ui32XID) ||
       (*(uint32_t *)psBOOTP->pui8CHAddr != *(uint32_t *)g_sMACAddr.addr) ||
       (*(uint16_t *)(psBOOTP->pui8CHAddr + 4) !=
        *(uint16_t *)(g_sMACAddr.addr + 4)))
    {
        return(0);
    }

    //
    // Extract our IP address from the response.
    //
    *((uint32_t *)(void *)(&uip_hostaddr)) = psBOOTP->ui32YIAddr;

    //
    // Extract the server address from the response.
    //
    *((uint32_t *)(void *)(&g_sServerAddr)) = psBOOTP->ui32SIAddr;

    //
    // Save the boot file name.
    //
    for(ui32Idx = 0;
        ((g_pcFilename[ui32Idx] = psBOOTP->pcFile[ui32Idx]) != 0) &&
        (ui32Idx < (sizeof(g_pcFilename) - 1));
        ui32Idx++)
    {
    }
    g_pcFilename[ui32Idx] = 0;

    //
    // A valid BOOTP reply was found and decoded.
    //
    return(1);
}


//*****************************************************************************
//
//! Constructs and sends a TFTP error packet.
//!
//! This function constructs a TFTP read request packet (RRQ) and sends it to
//! the server.
//!
//! \return None.
//
//*****************************************************************************
static void
SendTFTPError(uint16_t ui16Error, char *pcString)
{
    uint8_t *pui8Packet = (uint8_t *)uip_appdata;
    int32_t i32Len;

    pui8Packet[0] = (TFTP_ERROR >> 8) & 0xff;
    pui8Packet[1] = TFTP_ERROR & 0xff;
    pui8Packet[2] = (ui16Error >> 8) & 0xFF;
    pui8Packet[3] = ui16Error & 0xFF;

    //
    // Get ready to copy the error string.
    //
    i32Len = 4;
    pui8Packet += 4;

    //
    // Copy as much of the string as we can fit.
    //
    while((i32Len < (UIP_APPDATA_SIZE - 1)) && *pcString)
    {
        *pui8Packet++ = *pcString++;
        i32Len++;
    }

    //
    // Write the terminating 0.
    //
    *pui8Packet = (uint8_t)0;

    //
    // Send the error packet.
    //
    uip_udp_send(i32Len + 1);
}

//*****************************************************************************
//
//! Constructs and sends a TFTP read packet.
//!
//! This function constructs a TFTP read request packet (RRQ) and sends it to
//! the server.
//!
//! \return None.
//
//*****************************************************************************
static void
SendTFTPGet(void)
{
    uint8_t *pui8Packet = (uint8_t *)uip_appdata;
    uint32_t ui32Idx;
    char *pcFilename;

    //
    // The TFTP RRQ packet should be sent to the TFTP server port.
    //
    g_pConn->rport = HTONS(TFTP_PORT);

    //
    // Set the TFTP packet opcode to RRQ.
    //
    pui8Packet[0] = (TFTP_RRQ >> 8) & 0xff;
    pui8Packet[1] = TFTP_RRQ & 0xff;

    //
    // Copy the file name into the RRQ packet.
    //
    for(ui32Idx = 2, pcFilename = g_pcFilename;
        (pui8Packet[ui32Idx++] = *pcFilename++) != 0; )
    {
    }

    //
    // Set the transfer mode to binary.
    //
    for(pcFilename = "octet"; (pui8Packet[ui32Idx++] = *pcFilename++) != 0; )
    {
    }

    //
    // Send the TFTP read packet.
    //
    uip_udp_send(ui32Idx);
}

//*****************************************************************************
//
//! Parses a packet checking for a TFTP data packet.
//!
//! This function parses a packet to determine if it is a TFTP data packet for
//! out current TFTP transfer.  If a valid packet is found, the contents of the
//! packet are programmed into flash.
//!
//! \return Returns 1 if this packet was the last packet of the TFTP data
//! transfer and 0 otherwise.
//
//*****************************************************************************
static uint32_t
ParseTFTPData(void)
{
    uint8_t *pui8Packet = (uint8_t *)uip_appdata;
    uint32_t ui32FlashAddr;
    uint32_t ui32Idx;

    //
    // See if this is a TFTP data packet.
    //
    if((pui8Packet[0] != ((TFTP_DATA >> 8) && 0xff)) ||
       (pui8Packet[1] != (TFTP_DATA & 0xff)))
    {
        return(0);
    }

    //
    // If the remote port on our connection is still the TFTP server port (i.e.
    // this is the first data packet), then copy the transaction ID for the
    // TFTP data connection into our connection.  This will ensure that our
    // response will be sent to the correct port.
    //
    if(g_pConn->rport == HTONS(TFTP_PORT))
    {
        g_pConn->rport =
            ((struct uip_udpip_hdr *)&uip_buf[UIP_LLH_LEN])->srcport;
    }

    //
    // See if this is the correct data packet.
    //
    if((pui8Packet[2] != ((g_ui32TFTPBlock >> 8) & 0xff)) ||
       (pui8Packet[3] != (g_ui32TFTPBlock & 0xff)))
    {
        //
        // Since the wrong data packet was sent, resend the ACK for it since
        // we've already processed it.
        //
        pui8Packet[0] = (TFTP_ACK >> 8) & 0xff;
        pui8Packet[1] = TFTP_ACK & 0xff;
        uip_udp_send(4);

        //
        // Ignore this packet.
        //
        return(0);
    }

    //
    // What address are we about to program to?
    //
    ui32FlashAddr =
        ((g_ui32TFTPBlock - 1) * TFTP_BLOCK_SIZE) + APP_START_ADDRESS;

    //
    // Do not program this data into flash if it is beyond the end of flash.
    //
    if(ui32FlashAddr < g_ui32FlashEnd)
    {
        //
        // If this is the first block and we have been provided with a start
        // hook function, call it here to indicate that we are about to begin
        // flashing a new image.
        //
#ifdef BL_START_FN_HOOK
        if(g_ui32TFTPBlock == 1)
        {
            BL_START_FN_HOOK();
        }
#endif

        //
        // Clear any flash error indicator.
        //
        BL_FLASH_CL_ERR_FN_HOOK();

        //
        // If this is the first data packet and code protection is enabled,
        // then erase the entire flash.
        //
#ifdef FLASH_CODE_PROTECTION
        if(g_ui32TFTPBlock == 1)
        {
            //
            // Loop through the pages in the flash, excluding the pages that
            // contain the boot loader and the optional reserved space.
            //
            for(ui32Idx = APP_START_ADDRESS; ui32Idx < g_ui32FlashEnd;
                ui32Idx += FLASH_PAGE_SIZE)
            {
                //
                // Erase this block of the flash.
                //
                BL_FLASH_ERASE_FN_HOOK((ui32Idx);
            }
        }
#else
        //
        // Flash code protection is not enabled, so see if the data in this
        // packet will be programmed to the beginning of a flash block.  We
        // assume that the flash block size is always a multiple of 1KB so,
        // since each TFTP packet is 512 bytes and that the start must always
        // be on a flash page boundary, we can be sure that we will hit the
        // start of each page as we receive packets.
        //
        if(!(ui32FlashAddr & (FLASH_PAGE_SIZE - 1)))
        {
            //
            // Erase this block of the flash.
            //
            BL_FLASH_ERASE_FN_HOOK(ui32FlashAddr);
        }
#endif

        //
        // Decrypt the data if required.
        //
#ifdef BL_DECRYPT_FN_HOOK
        BL_DECRYPT_FN_HOOK(pui8Packet + 4, uip_len - 4);
#endif

        //
        // Program this block of data into flash.
        //
        BL_FLASH_PROGRAM_FN_HOOK(ui32FlashAddr, (pui8Packet + 4),
                                 (uip_len - 4));

        //
        // If a progress reporting hook function has been provided, call it
        // here.  The TFTP protocol doesn't let us know how large the image is
        // before it starts the transfer so we pass 0 as the ui32Total
        // parameter to indicate this.
        //
#ifdef BL_PROGRESS_FN_HOOK
        BL_PROGRESS_FN_HOOK(((ui32FlashAddr - APP_START_ADDRESS) +
                             (uip_len - 4)), 0);
#endif
    }

    //
    // Increment to the next block.
    //
    g_ui32TFTPBlock++;

    //
    // Save the packet length.
    //
    ui32Idx = uip_len;

    //
    // Did we see any error?
    //
    if(BL_FLASH_ERROR_FN_HOOK())
    {
        //
        // Yes - send back an error packet.
        //
        SendTFTPError(2, "Error programming flash.");
    }
    else
    {
        //
        // No errors reported so construct an ACK packet.  The block number
        // field is already correct, so it does not need to be set.
        //
        pui8Packet[0] = (TFTP_ACK >> 8) & 0xff;
        pui8Packet[1] = TFTP_ACK & 0xff;

        //
        // Send the ACK packet to the TFTP server.
        //
        uip_udp_send(4);
    }

    //
    // If the packet was shorter than TFTP_BLOCK_SIZE bytes then this was the
    // last packet in the file.
    //
    if(ui32Idx != (TFTP_BLOCK_SIZE + 4))
    {
        //
        // If an end signal hook function has been provided, call it here.
        //
#ifdef BL_END_FN_HOOK
        BL_END_FN_HOOK();
#endif
        return(1);
    }
    //
    // There is more data to be read.
    //
    return(0);
}

uint16_t
LOCAL_EMACPHYRead(uint32_t ui32Base, uint8_t ui8PhyAddr, uint8_t ui8RegAddr)
{

    //
    // Make sure the MII is idle.
    //
    while(EMAC0->MIIADDR & EMAC_MIIADDR_MIIB)
    {
    }

    //
    // Tell the MAC to read the given PHY register.
    //
    EMAC0->MIIADDR =
        ((EMAC0->MIIADDR & EMAC_MIIADDR_CR_M) |
         (ui8RegAddr << EMAC_MIIADDR_MII_S) |
         (ui8PhyAddr << EMAC_MIIADDR_PLA_S) | EMAC_MIIADDR_MIIB);

    //
    // Wait for the read to complete.
    //
    while(EMAC0->MIIADDR & EMAC_MIIADDR_MIIB)
    {
    }

    //
    // Return the result.
    //
    return(EMAC0->MIIDATA & EMAC_MIIDATA_DATA_M);
}

//*****************************************************************************
//
//! Handles the NULL process.
//!
//! This function contains the proto-thread for handling the BOOTP process.  It
//! first communicates with the BOOTP server to get its boot parameters (IP
//! address, server address, and file name), then it communicates with the TFTP
//! server on the specified server to read the firmware image file.
//!
//! \return None.
//
//*****************************************************************************
#ifdef DOXYGEN
char
NULLThread(void)
#else
PT_THREAD(NULLThread(void))
#endif
{
    return(0);
}

//*****************************************************************************
//
//! Handles the BOOTP process.
//!
//! This function contains the proto-thread for handling the BOOTP process.  It
//! first communicates with the BOOTP server to get its boot parameters (IP
//! address, server address, and file name), then it communicates with the TFTP
//! server on the specified server to read the firmware image file.
//!
//! \return None.
//
//*****************************************************************************
#ifdef DOXYGEN
char
BOOTPThread(void)
#else
PT_THREAD(BOOTPThread(void))
#endif
{
    //
    // Begin the proto-thread.
    //
    PT_BEGIN(&g_sThread);

wait_for_link:
    PT_WAIT_UNTIL(&g_sThread,
                  (LOCAL_EMACPHYRead(EMAC0_BASE, 0, EPHY_BMSR) &
                   EPHY_BMSR_LINKSTAT) != 0);

    //
    // Reset the host address.
    //
    *((uint32_t *)(void *)(&uip_hostaddr)) = 0;

    //
    // Re-bind the UDP socket for sending requests to the BOOTP server.
    //
    uip_udp_remove(g_pConn);
    *((uint32_t *)(void *)(&g_sServerAddr)) = 0xffffffff;
    uip_udp_new(&g_sServerAddr, HTONS(BOOTP_SERVER_PORT));
    uip_udp_bind(g_pConn, HTONS(BOOTP_CLIENT_PORT));

    //
    // Set the initial delay between BOOTP requests to 1 second.
    //
    g_ui32Delay = SYSTICKHZ;

    //
    // Loop forever.  This loop is explicitly exited when a valid BOOTP reply
    // is received.
    //
    while(1)
    {
        //
        // Send a BOOTP request.
        //
        SendBOOTPRequest();

        //
        // Set the amount of time to wait for the BOOTP reply message.
        //
        g_ui32Target = g_ui32Ticks + g_ui32Delay;

        //
        // Wait until a packet is received or the timeout has occurred.
        //
wait_for_bootp_reply:
        PT_WAIT_UNTIL(&g_sThread,
                      ((g_ui32Link = (LOCAL_EMACPHYRead(EMAC0_BASE, 0, EPHY_BMSR) &
                                      EPHY_BMSR_LINKSTAT)) == 0) ||
                      uip_newdata() || (g_ui32Ticks > g_ui32Target));

        //
        // If the link has been lost, go back to waiting for a link.
        //
        if(g_ui32Link == 0)
        {
            goto wait_for_link;
        }

        //
        // See if a packet has been received.
        //
        if(uip_newdata())
        {
            //
            // Clear the new data flag so that this packet will only be
            // examined one time.
            //
            uip_flags &= ~(UIP_NEWDATA);

            //
            // See if this is a BOOTP reply.
            //
            if(ParseBOOTPReply() == 1)
            {
                break;
            }

            //
            // This was not a BOOTP reply packet, so go back to waiting.
            //
            goto wait_for_bootp_reply;
        }

        //
        // If the delay between BOOTP requests is less than 60 seconds, double
        // the delay time.  This avoids constantly slamming the network with
        // requests.
        //
        if(g_ui32Delay < (60 * SYSTICKHZ))
        {
            g_ui32Delay *= 2;
        }
    }

    //
    // Reconfigure the UDP socket to target the TFTP port on the server.
    //
    uip_ipaddr_copy(&g_pConn->ripaddr, g_sServerAddr);
    uip_udp_bind(g_pConn, HTONS(13633));

    //
    // Send a TFTP read request.
    //
    SendTFTPGet();

    //
    // Since the first TFTP read request will result in an ARP request, delay
    // for just a bit and then re-issue the TFTP read request.
    //
    PT_YIELD(&g_sThread);

    //
    // Resend the TFTP read request.  If the ARP request has already been
    // answered, this will go out as is and avoid the two second timeout below.
    //
    SendTFTPGet();

    //
    // Start the TFTP transfer from block one.
    //
    g_ui32TFTPBlock = 1;

    //
    // Set the number of TFTP retries to zero.
    //
    g_ui32TFTPRetries = 0;

    //
    // Loop forever.  This loop is explicitly exited when the TFTP transfer has
    // completed.
    //
    while(1)
    {
        //
        // Set the amount of time to wait for the TFTP data packet.
        //
        g_ui32Target = g_ui32Ticks + (SYSTICKHZ * 4);

        //
        // Wait until a packet is received or the timeout has occurred.
        //
        PT_WAIT_UNTIL(&g_sThread,
                      ((g_ui32Link = (LOCAL_EMACPHYRead(EMAC0_BASE, 0, EPHY_BMSR) &
                                      EPHY_BMSR_LINKSTAT)) == 0) ||
                      uip_newdata() || (g_ui32Ticks > g_ui32Target));

        //
        // If the link has been lost, go back to waiting for a link.
        //
        if(g_ui32Link == 0)
        {
            goto wait_for_link;
        }

        //
        // See if a packet has been received.
        //
        if(uip_newdata())
        {
            //
            // Clear the new data flag so that this packet will only be
            // examined one time.
            //
            uip_flags &= ~(UIP_NEWDATA);

            //
            // See if this is a TFTP data packet.
            //
            if(ParseTFTPData() == 1)
            {
                break;
            }
        }
        else if(g_ui32TFTPRetries < 3)
        {
            //
            // The transfer timed out, so send a new TFTP read request.
            //
            SendTFTPGet();

            //
            // Start the TFTP transfer from block one.
            //
            g_ui32TFTPBlock = 1;

            //
            // Increment the count of TFTP retries.
            //
            g_ui32TFTPRetries++;
        }
        else
        {
            //
            // The TFTP transfer failed after three retries, so start over.
            //
            goto wait_for_link;
        }
    }
    //
    // Wait for the last packet to be transmitted.
    //
    while(g_psTxDescriptor[g_ui32TxDescIndex].ui32CtrlStatus &
          DES0_TX_CTRL_OWN)
    {
    }

    //
    // Wait for a bit to make sure that the final ACK packet is transmitted.
    //
    g_ui32Target = g_ui32Ticks + (SYSTICKHZ / 4);
    while(g_ui32Ticks < g_ui32Target)
    {
        PT_YIELD(&g_sThread);
    }

    //
    // Perform a software reset request.  This will cause the microcontroller
    // to reset; no further code will be executed.
    //
    SCB->AIRCR = NVIC_APINT_VECTKEY | NVIC_APINT_SYSRESETREQ;

    //
    // The microcontroller should have reset, so this should never be reached.
    // Just in case, loop forever.
    //
    while(1)
    {
    }

    //
    // End the proto-thread.
    //
    PT_END(&g_sThread);
}

static void
LOCAL_EMACPHYConfigSet(uint32_t ui32Base, uint32_t ui32Config)
{
    //
    // Write the Ethernet PHY configuration to the peripheral configuration
    // register.
    //
    EMAC0->PC = ui32Config;

    //
    // If using the internal PHY, reset it to ensure that new configuration is
    // latched there.
    //
    if((ui32Config & EMAC_PHY_TYPE_MASK) == EMAC_PHY_TYPE_INTERNAL)
    {
        ROM_SysCtlPeripheralReset(SYSCTL_PERIPH_EPHY0);
        while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_EPHY0))
        {
            //
            // Wait for the PHY reset to complete.
            //
        }

        //
        // Delay a bit longer to ensure that the PHY reset has completed.
        //
        ROM_SysCtlDelay(1000);
    }

    //
    // If using an external RMII PHY, we must set 2 bits in the Ethernet MAC
    // Clock Configuration Register.
    //
    if((ui32Config & EMAC_PHY_TYPE_MASK) == EMAC_PHY_TYPE_EXTERNAL_RMII)
    {
        //
        // Select and enable the external clock from the RMII PHY.
        //
        EMAC0->CC |= EMAC_CC_CLKEN;
    }
    else
    {
        //
        // Disable the external clock.
        //
        EMAC0->CC &= ~EMAC_CC_CLKEN;
    }

    //
    // Reset the MAC regardless of whether the PHY connection changed or not.
    //
    ROM_EMACReset(EMAC0_BASE);

    ROM_SysCtlDelay(1000);
}

//*****************************************************************************
//
//! Reconfigures the Ethernet controller.
//!
//! \param ui32Clock is the system clock frequency.
//!
//! This function reconfigures the Ethernet controller, preparing it for use by
//! the boot loader.  This performs the steps common between the direct
//! invocation of the boot loader and the application invocation of the boot
//! loader.
//!
//! \return None.
//
//*****************************************************************************
void
EnetReconfig(uint32_t ui32Clock)
{
    uip_ipaddr_t sAddr;
    uint32_t ui32Loop;
    uint32_t ui32User0, ui32User1;

    //
    // Configure for use with the internal PHY.
    //
    LOCAL_EMACPHYConfigSet(EMAC0_BASE,
                           (EMAC_PHY_TYPE_INTERNAL | EMAC_PHY_INT_MDIX_EN |
                            EMAC_PHY_AN_100B_T_FULL_DUPLEX));


    //
    // Reset the MAC.
    //
    ROM_EMACReset(EMAC0_BASE);

    //
    // Initialize the MAC and set the DMA mode.
    //
    ROM_EMACInit(EMAC0_BASE, ui32Clock,
             EMAC_BCONFIG_MIXED_BURST | EMAC_BCONFIG_PRIORITY_FIXED, 4, 4, 0);

    //
    // Get the MAC address from the flash user registers.  If it has not been
    // programmed, then use the boot loader default MAC address.
    //
    ROM_FlashUserGet(&ui32User0, &ui32User1);
    if((ui32User0 == 0xffffffff) || (ui32User1 == 0xffffffff))
    {
        //
        // MAC address has not been programmed, use default.
        //
        g_sMACAddr.addr[0] = 0x00;
        g_sMACAddr.addr[1] = 0x1a;
        g_sMACAddr.addr[2] = 0xb6;
        g_sMACAddr.addr[3] = 0x00;
        g_sMACAddr.addr[4] = 0x64;
        g_sMACAddr.addr[5] = 0x00;
    }
    else
    {
        g_sMACAddr.addr[0] = ui32User0 & 0xff;
        g_sMACAddr.addr[1] = (ui32User0 >> 8) & 0xff;
        g_sMACAddr.addr[2] = (ui32User0 >> 16) & 0xff;
        g_sMACAddr.addr[3] = ui32User1 & 0xff;
        g_sMACAddr.addr[4] = (ui32User1 >> 8) & 0xff;
        g_sMACAddr.addr[5] = (ui32User1 >> 16) & 0xff;
    }

    //
    // Set MAC configuration options.
    //
    ROM_EMACConfigSet(EMAC0_BASE,
                  (EMAC_CONFIG_FULL_DUPLEX | EMAC_CONFIG_CHECKSUM_OFFLOAD |
                   EMAC_CONFIG_7BYTE_PREAMBLE | EMAC_CONFIG_IF_GAP_96BITS |
                   EMAC_CONFIG_USE_MACADDR0 | EMAC_CONFIG_SA_FROM_DESCRIPTOR |
                   EMAC_CONFIG_BO_LIMIT_1024),
                  (EMAC_MODE_RX_STORE_FORWARD | EMAC_MODE_TX_STORE_FORWARD |
                   EMAC_MODE_TX_THRESHOLD_64_BYTES |
                   EMAC_MODE_RX_THRESHOLD_64_BYTES), 0);

    //
    // Initialize each of the transmit descriptors.  Note that we leave the OWN
    // bit clear here since we have not set up any transmissions yet.
    //
    for(ui32Loop = 0; ui32Loop < NUM_TX_DESCRIPTORS; ui32Loop++)
    {
        g_psTxDescriptor[ui32Loop].ui32Count =
            (DES1_TX_CTRL_SADDR_INSERT |
             (TX_BUFFER_SIZE << DES1_TX_CTRL_BUFF1_SIZE_S));
        g_psTxDescriptor[ui32Loop].pvBuffer1 = g_pui8TxBuffer;
        g_psTxDescriptor[ui32Loop].DES3.pLink =
            (ui32Loop == (NUM_TX_DESCRIPTORS - 1)) ?
            g_psTxDescriptor : &g_psTxDescriptor[ui32Loop + 1];
        g_psTxDescriptor[ui32Loop].ui32CtrlStatus =
            (DES0_TX_CTRL_LAST_SEG | DES0_TX_CTRL_FIRST_SEG |
             DES0_TX_CTRL_INTERRUPT | DES0_TX_CTRL_CHAINED |
             DES0_TX_CTRL_IP_ALL_CKHSUMS);
    }

    //
    // Initialize each of the receive descriptors.  We clear the OWN bit here
    // to make sure that the receiver doesn't start writing anything
    // immediately.
    //
    for(ui32Loop = 0; ui32Loop < NUM_RX_DESCRIPTORS; ui32Loop++)
    {
        g_psRxDescriptor[ui32Loop].ui32CtrlStatus = 0;
        g_psRxDescriptor[ui32Loop].ui32Count =
            (DES1_RX_CTRL_CHAINED |
             (RX_BUFFER_SIZE << DES1_RX_CTRL_BUFF1_SIZE_S));
        g_psRxDescriptor[ui32Loop].pvBuffer1 = g_pui8RxBuffer;
        g_psRxDescriptor[ui32Loop].DES3.pLink =
            (ui32Loop == (NUM_RX_DESCRIPTORS - 1)) ?
            g_psRxDescriptor : &g_psRxDescriptor[ui32Loop + 1];
    }

    //
    // Set the descriptor pointers in the hardware.
    //
    ROM_EMACRxDMADescriptorListSet(EMAC0_BASE, g_psRxDescriptor);
    ROM_EMACTxDMADescriptorListSet(EMAC0_BASE, g_psTxDescriptor);

    //
    // Start from the beginning of both descriptor chains.  We actually set
    // the transmit descriptor index to the last descriptor in the chain
    // since it will be incremented before use and this means the first
    // transmission we perform will use the correct descriptor.
    //
    g_ui32RxDescIndex = 0;
    g_ui32TxDescIndex = NUM_TX_DESCRIPTORS - 1;

    //
    // Program the MAC address.
    //
    ROM_EMACAddrSet(EMAC0_BASE, 0, g_sMACAddr.addr);

    //
    // Wait for the link to become active.
    //
    while((ROM_EMACPHYRead(EMAC0_BASE, 0, EPHY_BMSR) &
           EPHY_BMSR_LINKSTAT) == 0)
    {
    }

    //
    // Set MAC filtering options.  We receive all broadcast and multicast
    // packets along with those addressed specifically for us.
    //
    ROM_EMACFrameFilterSet(EMAC0_BASE, (EMAC_FRMFILTER_SADDR |
                                    EMAC_FRMFILTER_PASS_MULTICAST |
                                    EMAC_FRMFILTER_PASS_NO_CTRL));

    //
    // Seed the random number generator from the MAC address.
    //
    g_ui32RandomSeed = *(uint32_t *)(g_sMACAddr.addr + 2);

    //
    // Initialize the uIP stack.
    //
    uip_init();
    uip_arp_init();

    //
    // Set the MAC address.
    //
    uip_setethaddr(g_sMACAddr);

    //
    // Initialize the proto-thread used by the BOOTP protocol handler.
    //
    PT_INIT(&g_sThread);

    //
    // Create a UDP socket for sending requests to the BOOTP server.  After the
    // BOOTP portion of the protocol has been handled, this socket will be
    // reused to communicate with the TFTP server.
    //
    *((uint32_t *)(void *)(&sAddr)) = 0xffffffff;
    g_pConn = uip_udp_new(&sAddr, HTONS(BOOTP_SERVER_PORT));
    uip_udp_bind(g_pConn, HTONS(BOOTP_CLIENT_PORT));

    //
    // Enable the Ethernet MAC transmitter and receiver.
    //
    ROM_EMACTxEnable(EMAC0_BASE);
    ROM_EMACRxEnable(EMAC0_BASE);

    //
    // Mark the first receive descriptor as available to the DMA to start
    // the receive processing.
    //
    g_psRxDescriptor[g_ui32RxDescIndex].ui32CtrlStatus |= DES0_RX_CTRL_OWN;

    //
    // Reset the counters that are incremented by SysTick.
    //
    g_ui32Ticks = 0;
    g_ui32PeriodicTimer = 0;
    g_ui32ARPTimer = 0;

    //
    // Setup SysTick.
    //
    SysTick->LOAD = (ui32Clock / SYSTICKHZ) - 1;
    SysTick->CTRL = (NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN |
                           NVIC_ST_CTRL_ENABLE);
}
//*****************************************************************************
//
//! Configures the Ethernet controller.
//!
//! This function configures the Ethernet controller, preparing it for use by
//! the boot loader.
//!
//! \return None.
//
//*****************************************************************************
void
ConfigureEnet(void)
{
    //
    // Make sure the main oscillator is enabled because this is required by
    // the PHY.  The system must have a 25MHz crystal attached to the OSC
    // pins.  The SYSCTL_MOSC_HIGHFREQ parameter is used when the crystal
    // frequency is 10MHz or higher.
    //
    SYSCTL->MOSCCTL = SYSCTL_MOSC_HIGHFREQ;

    //
    // Delay while the main oscillator starts up.
    //
    Delay(5242880);

    MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                            SYSCTL_OSC_MAIN |
                            SYSCTL_USE_PLL |
                            SYSCTL_CFG_VCO_480), 120000000);


#ifdef ENET_ENABLE_LEDS
    //
    // PF1/PK4/PK6 are used for Ethernet LEDs.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    ROM_GPIOPinConfigure(GPIO_PF1_EN0LED2);
    ROM_GPIOPinConfigure(GPIO_PK4_EN0LED0);
    ROM_GPIOPinConfigure(GPIO_PK6_EN0LED1);

    //
    // Make the pin(s) be peripheral controlled.
    //
    ROM_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_DIR_MODE_HW);
    ROM_GPIODirModeSet(GPIO_PORTK_BASE, GPIO_PIN_4|GPIO_PIN_6, GPIO_DIR_MODE_HW);

    //
    // Set the pad(s) for standard push-pull operation.
    //
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    ROM_GPIOPadConfigSet(GPIO_PORTK_BASE, GPIO_PIN_4|GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
#endif

    //
    // Enable and reset the Ethernet modules.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_EMAC0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_EPHY0);
    ROM_SysCtlPeripheralReset(SYSCTL_PERIPH_EMAC0);
    ROM_SysCtlPeripheralReset(SYSCTL_PERIPH_EPHY0);

    while(!ROM_SysCtlPeripheralReady(SYSCTL_PERIPH_EMAC0))
    {
    }

}

//*****************************************************************************
//
//! Starts the update process via BOOTP.
//!
//! This function starts the Ethernet firmware update process.  The BOOTP
//! (as defined by RFC951 at http://tools.ietf.org/html/rfc951) and TFTP (as
//! defined by RFC1350 at http://tools.ietf.org/html/rfc1350) protocols are
//! used to transfer the firmware image over Ethernet.
//!
//! \return Never returns.
//
//*****************************************************************************
void
UpdateBOOTP(void)
{
    //
    // Get the size of flash.
    //
    g_ui32FlashEnd =  ROM_SysCtlFlashSizeGet();
#ifdef FLASH_RSVD_SPACE
    g_ui32FlashEnd -= FLASH_RSVD_SPACE;
#endif

    //
    // Perform the common Ethernet configuration. The frequency should
    // match whatever the application sets the system clock.
    //
    EnetReconfig(120000000);

    //
    // Main Application Loop.
    //
    while(1)
    {
        uint32_t ui32Temp;

        //
        // See if there is a packet waiting to be read.
        //
        if(!(g_psRxDescriptor[g_ui32RxDescIndex].ui32CtrlStatus &
             DES0_RX_CTRL_OWN))
        {
            //
            // Read the packet from the Ethernet controller.
            //
            uip_len = PacketReceive(uip_buf, UIP_CONF_BUFFER_SIZE);

            //
            // See if this is an IP packet.
            //
            if((uip_len != 0) &&
               (((struct uip_eth_hdr *)&uip_buf[0])->type ==
                HTONS(UIP_ETHTYPE_IP)))
            {
                //
                // Update the ARP tables based on this packet.
                //
                uip_arp_ipin();

                //
                // Process this packet.
                //
                uip_input();

                //
                // See if the processing of this packet resulted in a packet to be
                // sent.
                //
                if(uip_len > 0)
                {
                    //
                    // Update the ARP tables based on the packet to be sent.
                    //
                    uip_arp_out();

                    //
                    // Send the packet.
                    //
                    PacketTransmit(uip_buf, uip_len);

                    //
                    // Indicate that the packet has been sent.
                    //
                    uip_len = 0;
                }
            }

            //
            // See if this is an ARP packet.
            //
            else if((uip_len != 0) &&
                    (((struct uip_eth_hdr *)&uip_buf[0])->type ==
                     HTONS(UIP_ETHTYPE_ARP)))
            {
                //
                // Process this packet.
                //
                uip_arp_arpin();

                //
                // See if the processing of this packet resulted in a packet to be
                // sent.
                //
                if(uip_len > 0)
                {
                    //
                    // Send the packet.
                    //
                    PacketTransmit(uip_buf, uip_len);

                    //
                    // Indicate that the packet has been sent.
                    //
                    uip_len = 0;
                }
            }
        }

        //
        // See if the periodic timer has expired.
        //
        if(g_ui32PeriodicTimer > UIP_PERIODIC_TIMER_MS)
        {
            //
            // Reset the periodic timer.
            //
            g_ui32PeriodicTimer = 0;

            //
            // Loop through the UDP connections.
            //
            for(ui32Temp = 0; ui32Temp < UIP_UDP_CONNS; ui32Temp++)
            {
                //
                // Perform the periodic processing on this UDP connection.
                //
                uip_udp_periodic(ui32Temp);

                //
                // See if the periodic processing of this connection resulted in a
                // packet to be sent.
                //
                if(uip_len > 0)
                {
                    //
                    // Update the ARP tables based on the packet to be sent.
                    //
                    uip_arp_out();

                    //
                    // Send the packet.
                    //
                    PacketTransmit(uip_buf, uip_len);

                    //
                    // Indicate that the packet has been sent.
                    //
                    uip_len = 0;
                }
            }
        }

        //
        // See if the ARP timer has expired.
        //
        if(g_ui32ARPTimer > UIP_ARP_TIMER_MS)
        {
            //
            // Reset the ARP timer.
            //
            g_ui32ARPTimer = 0;

            //
            // Perform periodic processing on the ARP table.
            //
            uip_arp_timer();
        }
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
