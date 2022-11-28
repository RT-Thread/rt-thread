/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the People's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __UART_I_H__
#define __UART_I_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Register definitions for UART
 */
#define UART_RHB (0x00)
#define UART_RBR (0x00)         /* receive buffer register */
#define UART_THR (0x00)         /* transmit holding register */
#define UART_DLL (0x00)         /* divisor latch low register */
#define UART_DLH (0x04)         /* diviso latch high register */
#define UART_IER (0x04)         /* interrupt enable register */
#define UART_IIR (0x08)         /* interrupt identity register */
#define UART_FCR (0x08)         /* FIFO control register */
#define UART_LCR (0x0c)         /* line control register */
#define UART_MCR (0x10)         /* modem control register */
#define UART_LSR (0x14)         /* line status register */
#define UART_MSR (0x18)         /* modem status register */
#define UART_SCH (0x1c)         /* scratch register */
#define UART_USR (0x7c)         /* status register */
#define UART_TFL (0x80)         /* transmit FIFO level */
#define UART_RFL (0x84)         /* RFL */
#define UART_HALT (0xa4)        /* halt tx register */
#define UART_RS485 (0xc0)       /* RS485 control and status register */

/*
 * register bit field define
 */

/* Interrupt Enable Register */
#define UART_IER_MASK       (0xff)
#define UART_IER_PTIME      (BIT(7))
#define UART_IER_RS485      (BIT(4))
#define UART_IER_MSI        (BIT(3))
#define UART_IER_RLSI       (BIT(2))
#define UART_IER_THRI       (BIT(1))
#define UART_IER_RDI        (BIT(0))
/* Interrupt ID Register */
#define UART_IIR_FEFLAG_MASK    (BIT(6)|BIT(7))
#define UART_IIR_IID_MASK   (BIT(0)|BIT(1)|BIT(2)|BIT(3))
#define UART_IIR_IID_MSTA   (0)
#define UART_IIR_IID_NOIRQ  (1)
#define UART_IIR_IID_THREMP (2)
#define UART_IIR_IID_RXDVAL (4)
#define UART_IIR_IID_LINESTA    (6)
#define UART_IIR_IID_BUSBSY (7)
#define UART_IIR_IID_CHARTO (12)
/* FIFO Control Register */
#define UART_FCR_RXTRG_MASK (BIT(6)|BIT(7))
#define UART_FCR_RXTRG_1CH  (0 << 6)
#define UART_FCR_RXTRG_1_4  (1 << 6)
#define UART_FCR_RXTRG_1_2  (2 << 6)
#define UART_FCR_RXTRG_FULL     (3 << 6)
#define UART_FCR_TXTRG_MASK (BIT(4)|BIT(5))
#define UART_FCR_TXTRG_EMP  (0 << 4)
#define UART_FCR_TXTRG_2CH  (1 << 4)
#define UART_FCR_TXTRG_1_4  (2 << 4)
#define UART_FCR_TXTRG_1_2  (3 << 4)
#define UART_FCR_TXFIFO_RST (BIT(2))
#define UART_FCR_RXFIFO_RST (BIT(1))
#define UART_FCR_FIFO_EN    (BIT(0))
/* Line Control Register */
#define UART_LCR_DLAB       (BIT(7))
#define UART_LCR_SBC        (BIT(6))
#define UART_LCR_PARITY_MASK    (BIT(5)|BIT(4))
#define UART_LCR_EPAR       (1 << 4)
#define UART_LCR_OPAR       (0 << 4)
#define UART_LCR_PARITY     (BIT(3))
#define UART_LCR_STOP       (BIT(2))
#define UART_LCR_DLEN_MASK  (BIT(1)|BIT(0))
#define UART_LCR_WLEN5      (0)
#define UART_LCR_WLEN6      (1)
#define UART_LCR_WLEN7      (2)
#define UART_LCR_WLEN8      (3)
/* Modem Control Register */
#define UART_MCR_MODE_MASK  (BIT(7)|BIT(6))
#define UART_MCR_MODE_RS485 (2 << 6)
#define UART_MCR_MODE_SIRE  (1 << 6)
#define UART_MCR_MODE_UART  (0 << 6)
#define UART_MCR_AFE        (BIT(5))
#define UART_MCR_LOOP       (BIT(4))
#define UART_MCR_RTS        (BIT(1))
#define UART_MCR_DTR        (BIT(0))
/* Line Status Rigster */
#define UART_LSR_RXFIFOE    (BIT(7))
#define UART_LSR_TEMT       (BIT(6))
#define UART_LSR_THRE       (BIT(5))
#define UART_LSR_BI     (BIT(4))
#define UART_LSR_FE     (BIT(3))
#define UART_LSR_PE     (BIT(2))
#define UART_LSR_OE     (BIT(1))
#define UART_LSR_DR     (BIT(0))
#define UART_LSR_BRK_ERROR_BITS (0x1E) /* BI, FE, PE, OE bits */
/* Modem Status Register */
#define UART_MSR_DCD        (BIT(7))
#define UART_MSR_RI     (BIT(6))
#define UART_MSR_DSR        (BIT(5))
#define UART_MSR_CTS        (BIT(4))
#define UART_MSR_DDCD       (BIT(3))
#define UART_MSR_TERI       (BIT(2))
#define UART_MSR_DDSR       (BIT(1))
#define UART_MSR_DCTS       (BIT(0))
#define UART_MSR_ANY_DELTA  (0x0F)
#define MSR_SAVE_FLAGS      (UART_MSR_ANY_DELTA)
/* Status Register */
#define UART_USR_RFF        (BIT(4))
#define UART_USR_RFNE       (BIT(3))
#define UART_USR_TFE        (BIT(2))
#define UART_USR_TFNF       (BIT(1))
#define UART_USR_BUSY       (BIT(0))
/* Halt Register */
#define UART_HALT_LCRUP     (BIT(2))
#define UART_HALT_FORCECFG  (BIT(1))
#define UART_HALT_HTX       (BIT(0))
/* RS485 Control and Status Register */
#define UART_RS485_RXBFA    (BIT(3))
#define UART_RS485_RXAFA    (BIT(2))

#ifdef __cplusplus
}
#endif
#endif /* __UART_I_H__ */
