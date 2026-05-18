/*
 * Copyright (c) 2024 ~ 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_CP210X_H
#define USBH_CP210X_H

#include "usb_cdc.h"

/* Requests */
#define CP210X_IFC_ENABLE      0x00
#define CP210X_SET_BAUDDIV     0x01
#define CP210X_GET_BAUDDIV     0x02
#define CP210X_SET_LINE_CTL    0x03 // Set parity, data bits, stop bits
#define CP210X_GET_LINE_CTL    0x04
#define CP210X_SET_BREAK       0x05
#define CP210X_IMM_CHAR        0x06
#define CP210X_SET_MHS         0x07 // Set DTR, RTS
#define CP210X_GET_MDMSTS      0x08
#define CP210X_SET_XON         0x09
#define CP210X_SET_XOFF        0x0A
#define CP210X_SET_EVENTMASK   0x0B
#define CP210X_GET_EVENTMASK   0x0C
#define CP210X_SET_CHAR        0x0D
#define CP210X_GET_CHARS       0x0E
#define CP210X_GET_PROPS       0x0F
#define CP210X_GET_COMM_STATUS 0x10
#define CP210X_RESET           0x11
#define CP210X_PURGE           0x12
#define CP210X_SET_FLOW        0x13
#define CP210X_GET_FLOW        0x14
#define CP210X_EMBED_EVENTS    0x15
#define CP210X_GET_EVENTSTATE  0x16
#define CP210X_SET_CHARS       0x19
#define CP210X_GET_BAUDRATE    0x1D
#define CP210X_SET_BAUDRATE    0x1E // Set baudrate
#define CP210X_VENDOR_SPECIFIC 0xFF

/* CP210X_VENDOR_SPECIFIC values */
#define CP210X_GET_FW_VER     0x000E
#define CP210X_READ_2NCONFIG  0x000E
#define CP210X_GET_FW_VER_2N  0x0010
#define CP210X_READ_LATCH     0x00C2
#define CP210X_GET_PARTNUM    0x370B
#define CP210X_GET_PORTCONFIG 0x370C
#define CP210X_GET_DEVICEMODE 0x3711
#define CP210X_WRITE_LATCH    0x37E1

/* CP210X_IFC_ENABLE */
#define CP210X_UART_ENABLE  0x0001
#define CP210X_UART_DISABLE 0x0000

/* CP210X_(SET|GET)_BAUDDIV */
#define CP210X_BAUD_RATE_GEN_FREQ 0x384000

/* CP210X_(SET|GET)_LINE_CTL */
#define CP210X_BITS_DATA_MASK 0X0f00
#define CP210X_BITS_DATA_5    0X0500
#define CP210X_BITS_DATA_6    0X0600
#define CP210X_BITS_DATA_7    0X0700
#define CP210X_BITS_DATA_8    0X0800
#define CP210X_BITS_DATA_9    0X0900

#define CP210X_BITS_PARITY_MASK  0x00f0
#define CP210X_BITS_PARITY_NONE  0x0000
#define CP210X_BITS_PARITY_ODD   0x0010
#define CP210X_BITS_PARITY_EVEN  0x0020
#define CP210X_BITS_PARITY_MARK  0x0030
#define CP210X_BITS_PARITY_SPACE 0x0040

#define CP210X_BITS_STOP_MASK 0x000f
#define CP210X_BITS_STOP_1    0x0000
#define CP210X_BITS_STOP_1_5  0x0001
#define CP210X_BITS_STOP_2    0x0002

/* CP210X_SET_BREAK */
#define CP210X_BREAK_ON  0x0001
#define CP210X_BREAK_OFF 0x0000

/* CP210X_(SET_MHS|GET_MDMSTS) */
#define CP210X_CONTROL_DTR       0x0001
#define CP210X_CONTROL_RTS       0x0002
#define CP210X_CONTROL_CTS       0x0010
#define CP210X_CONTROL_DSR       0x0020
#define CP210X_CONTROL_RING      0x0040
#define CP210X_CONTROL_DCD       0x0080
#define CP210X_CONTROL_WRITE_DTR 0x0100
#define CP210X_CONTROL_WRITE_RTS 0x0200

/* CP210X_(GET|SET)_CHARS */
struct cp210x_special_chars {
    uint8_t bEofChar;
    uint8_t bErrorChar;
    uint8_t bBreakChar;
    uint8_t bEventChar;
    uint8_t bXonChar;
    uint8_t bXoffChar;
};

/* CP210X_GET_COMM_STATUS returns these 0x13 bytes */
struct cp210x_comm_status {
    uint32_t ulErrors;
    uint32_t ulHoldReasons;
    uint32_t ulAmountInInQueue;
    uint32_t ulAmountInOutQueue;
    uint8_t bEofReceived;
    uint8_t bWaitForImmediate;
    uint8_t bReserved;
} __PACKED;

/*
 * CP210X_PURGE - 16 bits passed in wValue of USB request.
 * SiLabs app note AN571 gives a strange description of the 4 bits:
 * bit 0 or bit 2 clears the transmit queue and 1 or 3 receive.
 * writing 1 to all, however, purges cp2108 well enough to avoid the hang.
 */
#define PURGE_ALL 0x000f

/* CP210X_EMBED_EVENTS */
#define CP210X_ESCCHAR 0xec

#define CP210X_LSR_OVERRUN BIT(1)
#define CP210X_LSR_PARITY  BIT(2)
#define CP210X_LSR_FRAME   BIT(3)
#define CP210X_LSR_BREAK   BIT(4)

/* CP210X_GET_FLOW/CP210X_SET_FLOW read/write these 0x10 bytes */
struct cp210x_flow_ctl {
    uint32_t lControlHandshake;
    uint32_t lFlowReplace;
    uint32_t lXonLimit;
    uint32_t lXoffLimit;
};

/* cp210x_flow_ctl::ulControlHandshake */
#define CP210X_SERIAL_DTR_MASK        (0x03 << 0)
#define CP210X_SERIAL_DTR_INACTIVE    (0 << 0)
#define CP210X_SERIAL_DTR_ACTIVE      (1 << 0)
#define CP210X_SERIAL_DTR_FLOW_CTL    (2 << 0)
#define CP210X_SERIAL_CTS_HANDSHAKE   BIT(3)
#define CP210X_SERIAL_DSR_HANDSHAKE   BIT(4)
#define CP210X_SERIAL_DCD_HANDSHAKE   BIT(5)
#define CP210X_SERIAL_DSR_SENSITIVITY BIT(6)

/* cp210x_flow_ctl::ulFlowReplace */
#define CP210X_SERIAL_AUTO_TRANSMIT  BIT(0)
#define CP210X_SERIAL_AUTO_RECEIVE   BIT(1)
#define CP210X_SERIAL_ERROR_CHAR     BIT(2)
#define CP210X_SERIAL_NULL_STRIPPING BIT(3)
#define CP210X_SERIAL_BREAK_CHAR     BIT(4)
#define CP210X_SERIAL_RTS_MASK       (0x03 << 6)
#define CP210X_SERIAL_RTS_INACTIVE   (0 << 6)
#define CP210X_SERIAL_RTS_ACTIVE     (1 << 6)
#define CP210X_SERIAL_RTS_FLOW_CTL   (2 << 6)
#define CP210X_SERIAL_XOFF_CONTINUE  BIT(31)

/* CP210X_VENDOR_SPECIFIC, CP210X_GET_DEVICEMODE call reads these 0x2 bytes. */
struct cp210x_pin_mode {
    uint8_t eci;
    uint8_t sci;
};

#define CP210X_PIN_MODE_MODEM 0
#define CP210X_PIN_MODE_GPIO  BIT(0)

/* Part number definitions */
#define CP210X_PARTNUM_CP2101        0x01
#define CP210X_PARTNUM_CP2102        0x02
#define CP210X_PARTNUM_CP2103        0x03
#define CP210X_PARTNUM_CP2104        0x04
#define CP210X_PARTNUM_CP2105        0x05
#define CP210X_PARTNUM_CP2108        0x08
#define CP210X_PARTNUM_CP2102N_QFN28 0x20
#define CP210X_PARTNUM_CP2102N_QFN24 0x21
#define CP210X_PARTNUM_CP2102N_QFN20 0x22
#define CP210X_PARTNUM_UNKNOWN       0xFF

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* USBH_CP210X_H */
