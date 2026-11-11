/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#ifndef __CH56X_UART_H__
#define __CH56X_UART_H__

#include "soc.h"
#include "ch56x_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UART_RXD0_ALT       GET_PIN(A, 5)
#define UART_TXD0_ALT       GET_PIN(A, 6)

#define UART_RXD0_PIN       GET_PIN(B, 5)
#define UART_TXD0_PIN       GET_PIN(B, 6)
#define UART_RXD1_PIN       GET_PIN(A, 7)
#define UART_TXD1_PIN       GET_PIN(A, 8)
#define UART_RXD2_PIN       GET_PIN(A, 2)
#define UART_TXD2_PIN       GET_PIN(A, 3)
#define UART_RXD3_PIN       GET_PIN(B, 3)
#define UART_TXD3_PIN       GET_PIN(B, 4)

#ifndef UART_FIFO_SIZE
#define UART_FIFO_SIZE      8
#endif

#ifndef UART_RECV_RDY_SZ
#define UART_RECV_RDY_SZ    7    // FIFO trigger level for rx data available
#endif

union _uart_mcr
{
    uint8_t reg;
    struct
    {
        uint8_t dtr         : 1;  // B.0 : RW, DTR output (UART0 only)
        uint8_t rts         : 1;  // B.1 : RW, RTS output (UART0 only)
        uint8_t out1        : 1;  // B.2 : RW, user defined modem control (UART0 only)
        uint8_t int_oe      : 1;  // B.3 : RW, interrupt output enable / OUT2
        uint8_t loop        : 1;  // B.4 : RW, enable internal loop test (UART0 only)
        uint8_t au_flow_en  : 1;  // B.5 : RW, enable CTS/RTS autoflow control
        uint8_t tnow        : 1;  // B.6 : RW, enable DTR TNOW output (UART0 only)
        uint8_t half        : 1;  // B.7 : RW, enable half-duplex mode (UART0 only)
    };
};
#define RB_MCR_DTR          0x01
#define RB_MCR_RTS          0x02
#define RB_MCR_OUT1         0x04
#define RB_MCR_OUT2         0x08
#define RB_MCR_INT_OE       0x08
#define RB_MCR_LOOP         0x10
#define RB_MCR_AU_FLOW_EN   0x20
#define RB_MCR_TNOW         0x40
#define RB_MCR_HALF         0x80

union _uart_ier
{
    uint8_t reg;
    struct
    {
        uint8_t recv_rdy    : 1;  // B.0 : RW, enable rx data ready intr
        uint8_t thr_empty   : 1;  // B.1 : RW, enable THR empty intr
        uint8_t line_stat   : 1;  // B.2 : RW, enable rx line status intr
        uint8_t modem_chg   : 1;  // B.3 : RW, enable modem status change intr (UART0 only)
        uint8_t dtr_en      : 1;  // B.4 : RW, DTR/TNOW output pin enable (UART0 only)
        uint8_t rts_en      : 1;  // B.5 : RW, RTS output pin enable (UART0 only)
        uint8_t txd_en      : 1;  // B.6 : RW, TXD pin enable
        uint8_t reset       : 1;  // B.7 : WZ, software reset control, active high, auto clear
    };
};
#define RB_IER_RECV_RDY     0x01
#define RB_IER_THR_EMPTY    0x02
#define RB_IER_LINE_STAT    0x04
#define RB_IER_MODEM_CHG    0x08
#define RB_IER_DTR_EN       0x10
#define RB_IER_RTS_EN       0x20
#define RB_IER_TXD_EN       0x40
#define RB_IER_RESET        0x80

union _uart_fcr
{
    uint8_t reg;
    struct
    {
        uint8_t fifo_en     : 1;  // B.0   : RW, FIFO enable
        uint8_t rx_fifo_clr : 1;  // B.1   : WZ, write 1 to clear rx FIFO, auto clear
        uint8_t tx_fifo_clr : 1;  // B.2   : WZ, write 1 to clear tx FIFO, auto clear
        uint8_t resv_3      : 3;
        uint8_t fifo_trig   : 2;  // B.7-6 : RW, rx FIFO trigger level, 1/2/4/7 bytes
    };
};
#define RB_FCR_FIFO_EN      0x01
#define RB_FCR_RX_FIFO_CLR  0x02
#define RB_FCR_TX_FIFO_CLR  0x04
#define RB_FCR_FIFO_TRIG    0xc0

#define UART_1BYTE_TRIG     0
#define UART_2BYTE_TRIG     1
#define UART_4BYTE_TRIG     2
#define UART_7BYTE_TRIG     3

union _uart_lcr
{
    uint8_t reg;
    struct
    {
        uint8_t word_sz     : 2;  // B.1-0 : RW, word bit length, 5/6/7/8 bits
        uint8_t stop_bit    : 1;  // B.2   : RW, stop bit length, 1/2 bits
        uint8_t par_en      : 1;  // B.3   : RW, parity enable
        uint8_t par_mod     : 2;  // B.5-4 : RW, parity mode, odd/even/mark/space
        uint8_t break_en    : 1;  // B.6   : RW, force BREAK line condition
        uint8_t dlab        : 1;  // B.7   : RW, user defined general purpose bit
    };
};
#define RB_LCR_WORD_SZ      0x03
#define RB_LCR_STOP_BIT     0x04
#define RB_LCR_PAR_EN       0x08
#define RB_LCR_PAR_MOD      0x30
#define RB_LCR_BREAK_EN     0x40
#define RB_LCR_DLAB         0x80
#define RB_LCR_GP_BIT       0x80

#define LCR_DATA_BITS_5     0
#define LCR_DATA_BITS_6     1
#define LCR_DATA_BITS_7     2
#define LCR_DATA_BITS_8     3

#define LCR_STOP_BITS_1     0
#define LCR_STOP_BITS_2     1

#define LCR_PARITY_ODD      0
#define LCR_PARITY_EVEN     1
#define LCR_PARITY_MARK     2
#define LCR_PARITY_SPACE    3

union _uart_iir
{
    uint8_t reg;
    struct
    {
        uint8_t int_mask    : 4;  // B.3-0 : RO, interrupt mask (intr if B.0 is 0)
        uint8_t resv_4      : 2;
        uint8_t fifo_id     : 2;  // B.7-6 : RO, FIFO enabled flag
    };
};
#define RB_IIR_NO_INT       0x01
#define RB_IIR_INT_MASK     0x0f
#define RB_IIR_FIFO_ID      0xc0

/* RB_IIR_INT_MASK (IIR bits 3:0) definition
*/
#define UART_II_SLV_ADDR    0x0e  // UART0 slave address match interrupt
#define UART_II_LINE_STAT   0x06  // rx line status interrupt
#define UART_II_RECV_RDY    0x04  // rx data available interrupt
#define UART_II_RECV_TOUT   0x0c  // rx fifo timeout interrupt
#define UART_II_THR_EMPTY   0x02  // THR empty interrupt
#define UART_II_MODEM_CHG   0x00  // UART0 modem status change interrupt
#define UART_II_NO_INTER    0x01  // no interrupt pending

union _uart_lsr
{
    uint8_t reg;
    struct
    {
        uint8_t data_rdy    : 1;  // B.0 : RO, rx FIFO data ready
        uint8_t over_err    : 1;  // B.1 : RZ, rx FIFO data overrun
        uint8_t par_err     : 1;  // B.2 : RZ, rx parity error
        uint8_t frame_err   : 1;  // B.3 : RZ, rx frame error
        uint8_t break_err   : 1;  // B.4 : RZ, rx BREAK detected
        uint8_t tx_fifo_emp : 1;  // B.5 : RO, tx FIFO empty
        uint8_t tx_all_emp  : 1;  // B.6 : RO, THR/TSR all empty
        uint8_t err_rx_fifo : 1;  // B.7 : RO, PAR/FRAME/BREAK ERR in rx FIFO
    };
};
#define RB_LSR_DATA_RDY     0x01
#define RB_LSR_OVER_ERR     0x02
#define RB_LSR_PAR_ERR      0x04
#define RB_LSR_FRAME_ERR    0x08
#define RB_LSR_BREAK_ERR    0x10
#define RB_LSR_TX_FIFO_EMP  0x20
#define RB_LSR_TX_ALL_EMP   0x40
#define RB_LSR_ERR_RX_FIFO  0x80

union _uart_msr
{
    uint8_t reg;
    struct
    {
        uint8_t cts_chg     : 1;  // B.0 : RZ, CTS input changed
        uint8_t dsr_chg     : 1;  // B.1 : RZ, DSR input changed
        uint8_t ri_chg      : 1;  // B.2 : RZ, RI  input changed
        uint8_t dcd_chg     : 1;  // B.3 : RZ, DCD input changed
        uint8_t cts         : 1;  // B.4 : RO, CTS action status
        uint8_t dsr         : 1;  // B.5 : RO, DSR action status
        uint8_t ri          : 1;  // B.6 : RO, RI  action status
        uint8_t dcd         : 1;  // B.7 : RO, DCD action status
    };
};
#define RB_MSR_CTS_CHG      0x01
#define RB_MSR_DSR_CHG      0x02
#define RB_MSR_RI_CHG       0x04
#define RB_MSR_DCD_CHG      0x08
#define RB_MSR_CTS          0x10
#define RB_MSR_DSR          0x20
#define RB_MSR_RI           0x40
#define RB_MSR_DCD          0x80

/*
 * 0x00  R8_UARTx_MCR:  Modem Control Register
 * 0x01  R8_UARTx_IER:  Interrupt Enable Register
 * 0x02  R8_UARTx_FCR:  FIFO Control Register
 * 0x03  R8_UARTx_LCR:  Line Control Register
 * 0x04  R8_UARTx_IIR:  Interrupt Identification Register
 * 0x05  R8_UARTx_LSR:  Line Status Register
 * 0x06  R8_UARTx_MSR:  Modem Status Register (UART0 only)
 * 0x08  R8_UARTx_RBR:  Rx Buffer Register
 * 0x08  R8_UARTx_THR:  Tx Hold Register
 * 0x0a  R8_UARTx_RFC:  Rx FIFO count register
 * 0x0b  R8_UARTx_TFC:  Tx FIFO count register
 * 0x0c  R16_UARTx_DL:  Divisor Latch
 * 0x0e  R8_UARTx_DIV:  frequency pre divider
 * 0x0f  R8_UARTx_ADR:  Address Register (UART0 only)
 *
 * CAVEAT: gcc (as of 8.2.0) tends to read 32-bit word for bit field test.
 * Be careful for those with side effect for read (e.g. RBR, IIR).
 */
struct uart_registers
{
    union _uart_mcr MCR;
    union _uart_ier IER;
    union _uart_fcr FCR;
    union _uart_lcr LCR;
    union _uart_iir IIR;
    union _uart_lsr LSR;
    union _uart_lsr MSR;
    uint8_t         resv_7;
    union
    {
        uint8_t     RBR;
        uint8_t     THR;
    };
    uint8_t         resv_9;
    uint8_t         RFC;
    uint8_t         TFC;
    uint16_t        DL;
    uint8_t         DIV;
    uint8_t         ADR;
} __packed;

CHECK_STRUCT_SIZE(struct uart_registers, 0x10);

int rt_hw_uart_init(void);

#ifdef __cplusplus
}
#endif

#endif
