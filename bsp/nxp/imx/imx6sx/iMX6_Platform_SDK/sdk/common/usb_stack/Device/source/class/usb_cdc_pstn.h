/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file usb_cdc_pstn.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains USB CDC_PSTN Sub Class API header function
 *
 *****************************************************************************/

#ifndef _USB_CDC_PSTN_H
#define _USB_CDC_PSTN_H

/******************************************************************************
 * Includes
 *****************************************************************************/
 #include "usb_cdc.h" /* USB CDC Class Header File */
/******************************************************************************
 * Constants - None
 *****************************************************************************/
#ifdef __MCF52xxx_H__
#pragma reverse_bitfields on
#endif
typedef struct _BITMAP_UART
{
    uint_8 bRxCarrier   : 1;    /* Receive Carrier Activation Flag */
    uint_8 bTxCarrier   : 1;    /* Transmit Carrier Activation Flag */
    uint_8 bBreak       : 1;    /* Break Flag */
    uint_8 bRingSignal  : 1;    /* Ring Signal Flag */
    uint_8 bFraming     : 1;    /* Frame Flag */
    uint_8 bParity      : 1;    /* Parity Flag */
    uint_8 bOverRun     : 1;    /* OverRun Flag */
    uint_8 reserved1    : 1;    /* Reserved */
}BITMAP_UART;
#ifdef __MCF52xxx_H__
#pragma reverse_bitfields off
#endif


typedef union _UART_BITMAP
{
    uint_8 _byte;
    BITMAP_UART Bitmap_Uart;
}UART_BITMAP;   /* UART STATE BITMAP */


/******************************************************************************
 * Macro's
 *****************************************************************************/
#define UART_BITMAP_SIZE           (0x02)
#define ABSTRACT_STATE_FEATURE     (0x01)
#define COUNTRY_SETTING_FEATURE    (0x02)
#define CARRIER_ACTIVATION_CHECK   (0x02)
#define DTE_PRESENCE_CHECK         (0x01)

extern uint_8 USB_Class_CDC_Pstn_Init (
    uint_8    controller_ID,
    USB_CLASS_CALLBACK callback
);

extern uint_8 USB_Class_CDC_PSTN_Get_Line_Coding (
    uint_8    controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);

extern uint_8 USB_Class_CDC_PSTN_Set_Line_Coding (
    uint_8    controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);

extern uint_8 USB_Class_CDC_PSTN_Set_Ctrl_Line_State (
    uint_8    controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);

extern uint_8 USB_Class_CDC_PSTN_Send_Break (
    uint_8    controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);

extern uint_8 USB_Class_CDC_PSTN_Get_Comm_Feature (
    uint_8    controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);

extern uint_8 USB_Class_CDC_PSTN_Set_Comm_Feature (
    uint_8    controller_ID,
    USB_SETUP_STRUCT * setup_packet,
    uint_8_ptr *data,
    USB_PACKET_SIZE *size);

#if CIC_NOTIF_ELEM_SUPPORT
extern void USB_Class_CDC_PSTN_Send_Serial_State (uint_8 controller_ID);
#endif
#endif
