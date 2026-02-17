/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_FTDI_H
#define USBH_FTDI_H

#include "usb_cdc.h"

#define FTDI_VID 0x0403 /* Vendor Id */

/* FTDI device PIDs */
#define FTDI_8U232AM_PID     0x6001 /* Similar device to SIO above */
#define FTDI_8U232AM_ALT_PID 0x6006 /* FTDI's alternate PID for above */
#define FTDI_8U2232C_PID     0x6010 /* Dual channel device */
#define FTDI_4232H_PID       0x6011 /* Quad channel hi-speed device */
#define FTDI_232H_PID        0x6014 /* Single channel hi-speed device */
#define FTDI_FTX_PID         0x6015 /* FT-X series (FT201X, FT230X, FT231X, etc) */
#define FTDI_FT2233HP_PID    0x6040 /* Dual channel hi-speed device with PD */
#define FTDI_FT4233HP_PID    0x6041 /* Quad channel hi-speed device with PD */
#define FTDI_FT2232HP_PID    0x6042 /* Dual channel hi-speed device with PD */
#define FTDI_FT4232HP_PID    0x6043 /* Quad channel hi-speed device with PD */
#define FTDI_FT233HP_PID     0x6044 /* Dual channel hi-speed device with PD */
#define FTDI_FT232HP_PID     0x6045 /* Dual channel hi-speed device with PD */
#define FTDI_FT4232HA_PID    0x6048 /* Quad channel automotive grade hi-speed device */
#define FTDI_SIO_PID         0x8372 /* Product Id SIO application of 8U100AX */
#define FTDI_232RL_PID       0xFBFA /* Product ID for FT232RL */

/* Requests */
#define FTDI_SIO_RESET             0x00 /* Reset the port */
#define FTDI_SIO_SET_MODEM_CTRL    0x01 /* Set the modem control register */
#define FTDI_SIO_SET_FLOW_CTRL     0x02 /* Set flow control register */
#define FTDI_SIO_SET_BAUDRATE      0x03 /* Set baud rate */
#define FTDI_SIO_SET_DATA          0x04 /* Set the data characteristics of the port */
#define FTDI_SIO_GET_MODEM_STATUS  0x05
#define FTDI_SIO_SET_EVENT_CHAR    0x06
#define FTDI_SIO_SET_ERROR_CHAR    0x07
#define FTDI_SIO_SET_LATENCY_TIMER 0x09
#define FTDI_SIO_GET_LATENCY_TIMER 0x0A
#define FTDI_SIO_SET_BITMODE       0x0B
#define FTDI_SIO_READ_PINS         0x0C
#define FTDI_SIO_READ_EEPROM       0x90
#define FTDI_SIO_WRITE_EEPROM      0x91
#define FTDI_SIO_ERASE_EEPROM      0x92

/* Channel indices for FT2232, FT2232H and FT4232H devices */
#define FTDI_SIO_CHANNEL_A 1
#define FTDI_SIO_CHANNEL_B 2
#define FTDI_SIO_CHANNEL_C 3
#define FTDI_SIO_CHANNEL_D 4

/*
 * BmRequestType:  0100 0000B
 * bRequest:       FTDI_SIO_RESET
 * wValue:         Control Value
 *                   0 = Reset SIO
 *                   1 = Purge RX buffer
 *                   2 = Purge TX buffer
 * wIndex:         Port
 * wLength:        0
 * Data:           None
 *
 * The Reset SIO command has this effect:
 *
 *    Sets flow control set to 'none'
 *    Event char = $0D
 *    Event trigger = disabled
 *    Purge RX buffer
 *    Purge TX buffer
 *    Clear DTR
 *    Clear RTS
 *    baud and data format not reset
 *
 * The Purge RX and TX buffer commands affect nothing except the buffers
 *
   */

#define FTDI_SIO_RESET_SIO      0
#define FTDI_SIO_RESET_PURGE_RX 1
#define FTDI_SIO_RESET_PURGE_TX 2

/*
 * BmRequestType:  0100 0000B
 * bRequest:       FTDI_SIO_SET_BAUDRATE
 * wValue:         BaudDivisor value - see below
 * wIndex:         Port
 * wLength:        0
 * Data:           None
 * The BaudDivisor values are calculated as follows:
 * - BaseClock is either 12000000 or 48000000 depending on the device.
 *   FIXME: I wish I knew how to detect old chips to select proper base clock!
 * - BaudDivisor is a fixed point number encoded in a funny way.
 *   (--WRONG WAY OF THINKING--)
 *   BaudDivisor is a fixed point number encoded with following bit weighs:
 *   (-2)(-1)(13..0). It is a radical with a denominator of 4, so values
 *   end with 0.0 (00...), 0.25 (10...), 0.5 (01...), and 0.75 (11...).
 *   (--THE REALITY--)
 *   The both-bits-set has quite different meaning from 0.75 - the chip
 *   designers have decided it to mean 0.125 instead of 0.75.
 *   This info looked up in FTDI application note "FT8U232 DEVICES \ Data Rates
 *   and Flow Control Consideration for USB to RS232".
 * - BaudDivisor = (BaseClock / 16) / BaudRate, where the (=) operation should
 *   automagically re-encode the resulting value to take fractions into
 *   consideration.
 * As all values are integers, some bit twiddling is in order:
 *   BaudDivisor = (BaseClock / 16 / BaudRate) |
 *   (((BaseClock / 2 / BaudRate) & 4) ? 0x4000    // 0.5
 *    : ((BaseClock / 2 / BaudRate) & 2) ? 0x8000  // 0.25
 *    : ((BaseClock / 2 / BaudRate) & 1) ? 0xc000  // 0.125
 *    : 0)
 *
 * For the FT232BM, a 17th divisor bit was introduced to encode the multiples
 * of 0.125 missing from the FT8U232AM.  Bits 16 to 14 are coded as follows
 * (the first four codes are the same as for the FT8U232AM, where bit 16 is
 * always 0):
 *   000 - add .000 to divisor
 *   001 - add .500 to divisor
 *   010 - add .250 to divisor
 *   011 - add .125 to divisor
 *   100 - add .375 to divisor
 *   101 - add .625 to divisor
 *   110 - add .750 to divisor
 *   111 - add .875 to divisor
 * Bits 15 to 0 of the 17-bit divisor are placed in the urb value.  Bit 16 is
 * placed in bit 0 of the urb index.
 *
 * Note that there are a couple of special cases to support the highest baud
 * rates.  If the calculated divisor value is 1, this needs to be replaced with
 * 0.  Additionally for the FT232BM, if the calculated divisor value is 0x4001
 * (1.5), this needs to be replaced with 0x0001 (1) (but this divisor value is
 * not supported by the FT8U232AM).
 */

enum ftdi_sio_baudrate {
    ftdi_sio_b300 = 0,
    ftdi_sio_b600 = 1,
    ftdi_sio_b1200 = 2,
    ftdi_sio_b2400 = 3,
    ftdi_sio_b4800 = 4,
    ftdi_sio_b9600 = 5,
    ftdi_sio_b19200 = 6,
    ftdi_sio_b38400 = 7,
    ftdi_sio_b57600 = 8,
    ftdi_sio_b115200 = 9
};

/*
 * BmRequestType:  0100 0000B
 * bRequest:       FTDI_SIO_SET_DATA
 * wValue:         Data characteristics (see below)
 * wIndex:         Port
 * wLength:        0
 * Data:           No
 *
 * Data characteristics
 *
 *   B0..7   Number of data bits
 *   B8..10  Parity
 *           0 = None
 *           1 = Odd
 *           2 = Even
 *           3 = Mark
 *           4 = Space
 *   B11..13 Stop Bits
 *           0 = 1
 *           1 = 1.5
 *           2 = 2
 *   B14
 *           1 = TX ON (break)
 *           0 = TX OFF (normal state)
 *   B15 Reserved
 *
 */

#define FTDI_SIO_SET_DATA_PARITY_NONE  (0x0 << 8)
#define FTDI_SIO_SET_DATA_PARITY_ODD   (0x1 << 8)
#define FTDI_SIO_SET_DATA_PARITY_EVEN  (0x2 << 8)
#define FTDI_SIO_SET_DATA_PARITY_MARK  (0x3 << 8)
#define FTDI_SIO_SET_DATA_PARITY_SPACE (0x4 << 8)
#define FTDI_SIO_SET_DATA_STOP_BITS_1  (0x0 << 11)
#define FTDI_SIO_SET_DATA_STOP_BITS_15 (0x1 << 11)
#define FTDI_SIO_SET_DATA_STOP_BITS_2  (0x2 << 11)
#define FTDI_SIO_SET_BREAK             (0x1 << 14)

/*
 * BmRequestType:   0100 0000B
 * bRequest:        FTDI_SIO_MODEM_CTRL
 * wValue:          ControlValue (see below)
 * wIndex:          Port
 * wLength:         0
 * Data:            None
 *
 * NOTE: If the device is in RTS/CTS flow control, the RTS set by this
 * command will be IGNORED without an error being returned
 * Also - you can not set DTR and RTS with one control message
 *
 * ControlValue
 * B0    DTR state
 *          0 = reset
 *          1 = set
 * B1    RTS state
 *          0 = reset
 *          1 = set
 * B2..7 Reserved
 * B8    DTR state enable
 *          0 = ignore
 *          1 = use DTR state
 * B9    RTS state enable
 *          0 = ignore
 *          1 = use RTS state
 * B10..15 Reserved
 *
 */

#define FTDI_SIO_SET_DTR_MASK 0x1
#define FTDI_SIO_SET_DTR_HIGH ((FTDI_SIO_SET_DTR_MASK << 8) | 1)
#define FTDI_SIO_SET_DTR_LOW  ((FTDI_SIO_SET_DTR_MASK << 8) | 0)
#define FTDI_SIO_SET_RTS_MASK 0x2
#define FTDI_SIO_SET_RTS_HIGH ((FTDI_SIO_SET_RTS_MASK << 8) | 2)
#define FTDI_SIO_SET_RTS_LOW  ((FTDI_SIO_SET_RTS_MASK << 8) | 0)

/*
 *   BmRequestType:  0100 0000b
 *   bRequest:       FTDI_SIO_SET_FLOW_CTRL
 *   wValue:         Xoff/Xon
 *   wIndex:         Protocol/Port - hIndex is protocol / lIndex is port
 *   wLength:        0
 *   Data:           None
 *
 * hIndex protocol is:
 *   B0 Output handshaking using RTS/CTS
 *       0 = disabled
 *       1 = enabled
 *   B1 Output handshaking using DTR/DSR
 *       0 = disabled
 *       1 = enabled
 *   B2 Xon/Xoff handshaking
 *       0 = disabled
 *       1 = enabled
 *
 * A value of zero in the hIndex field disables handshaking
 *
 * If Xon/Xoff handshaking is specified, the hValue field should contain the
 * XOFF character and the lValue field contains the XON character.
 */

#define FTDI_SIO_DISABLE_FLOW_CTRL 0x0
#define FTDI_SIO_RTS_CTS_HS        (0x1 << 8)
#define FTDI_SIO_DTR_DSR_HS        (0x2 << 8)
#define FTDI_SIO_XON_XOFF_HS       (0x4 << 8)

/*
 *   BmRequestType:   1100 0000b
 *   bRequest:        FTDI_SIO_GET_MODEM_STATUS
 *   wValue:          zero
 *   wIndex:          Port
 *   wLength:         1
 *   Data:            Status
 *
 * One byte of data is returned
 * B0..3 0
 * B4    CTS
 *         0 = inactive
 *         1 = active
 * B5    DSR
 *         0 = inactive
 *         1 = active
 * B6    Ring Indicator (RI)
 *         0 = inactive
 *         1 = active
 * B7    Receive Line Signal Detect (RLSD)
 *         0 = inactive
 *         1 = active
 */

#define FTDI_SIO_CTS_MASK  0x10
#define FTDI_SIO_DSR_MASK  0x20
#define FTDI_SIO_RI_MASK   0x40
#define FTDI_SIO_RLSD_MASK 0x80

/* Possible bitmodes for FTDI_SIO_SET_BITMODE_REQUEST */
#define FTDI_SIO_BITMODE_RESET 0x00
#define FTDI_SIO_BITMODE_CBUS  0x20

/*
 * IN Endpoint
 *
 * The device reserves the first two bytes of data on this endpoint to contain
 * the current values of the modem and line status registers. In the absence of
 * data, the device generates a message consisting of these two status bytes
 * every 40 ms
 *
 * Byte 0: Modem Status
 *
 * Offset	Description
 * B0	Reserved - must be 1
 * B1	Reserved - must be 0
 * B2	Reserved - must be 0
 * B3	Reserved - must be 0
 * B4	Clear to Send (CTS)
 * B5	Data Set Ready (DSR)
 * B6	Ring Indicator (RI)
 * B7	Receive Line Signal Detect (RLSD)
 *
 * Byte 1: Line Status
 *
 * Offset	Description
 * B0	Data Ready (DR)
 * B1	Overrun Error (OE)
 * B2	Parity Error (PE)
 * B3	Framing Error (FE)
 * B4	Break Interrupt (BI)
 * B5	Transmitter Holding Register (THRE)
 * B6	Transmitter Empty (TEMT)
 * B7	Error in RCVR FIFO
 *
 */
#define FTDI_RS0_CTS  (1 << 4)
#define FTDI_RS0_DSR  (1 << 5)
#define FTDI_RS0_RI   (1 << 6)
#define FTDI_RS0_RLSD (1 << 7)

#define FTDI_RS_DR   1
#define FTDI_RS_OE   (1 << 1)
#define FTDI_RS_PE   (1 << 2)
#define FTDI_RS_FE   (1 << 3)
#define FTDI_RS_BI   (1 << 4)
#define FTDI_RS_THRE (1 << 5)
#define FTDI_RS_TEMT (1 << 6)
#define FTDI_RS_FIFO (1 << 7)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* USBH_FTDI_H */
