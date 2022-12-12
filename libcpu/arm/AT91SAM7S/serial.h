/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RT_SERIAL_H__
#define __RT_SERIAL_H__

#ifndef AT91C_BASE_US0
#define AT91C_BASE_US0            (0xFFFC0000) // (US0) Base Address
#endif

#ifndef AT91C_BASE_US1
#define AT91C_BASE_US1            (0xFFFC4000) // (US1) Base Address
#endif

#define AT91C_US_RXRDY          ((unsigned int) 0x1 <<  0)  /* US RXRDY Interrupt */
#define AT91C_US_TXRDY          ((unsigned int) 0x1 <<  1)  /* US TXRDY Interrupt */
#define AT91C_US_RSTRX          ((unsigned int) 0x1 <<  2)  /* US Reset Receiver */
#define AT91C_US_RSTTX          ((unsigned int) 0x1 <<  3)  /* US Reset Transmitter */
#define AT91C_US_RXEN           ((unsigned int) 0x1 <<  4)  /* US Receiver Enable */
#define AT91C_US_RXDIS          ((unsigned int) 0x1 <<  5)  /* US Receiver Disable */
#define AT91C_US_TXEN           ((unsigned int) 0x1 <<  6)  /* US Transmitter Enable */
#define AT91C_US_TXDIS          ((unsigned int) 0x1 <<  7)  /* US Transmitter Disable */
#define AT91C_US_RSTSTA         ((unsigned int) 0x1 <<  8)  /* US Reset Status Bits */

#define AT91C_US_USMODE_NORMAL  ((unsigned int) 0x0)        /* USAR) Normal */
#define AT91C_US_USMODE_RS485   ((unsigned int) 0x1)        /* USAR) RS485 */
#define AT91C_US_USMODE_HWHSH   ((unsigned int) 0x2)        /* USAR) Hardware Handshaking */
#define AT91C_US_USMODE_MODEM   ((unsigned int) 0x3)        /* USAR) Modem */
#define AT91C_US_USMODE_ISO7816_0   ((unsigned int) 0x4)    /* USAR) ISO7816 protocol: T = 0 */
#define AT91C_US_USMODE_ISO7816_1   ((unsigned int) 0x6)    /* USAR) ISO7816 protocol: T = 1 */
#define AT91C_US_USMODE_IRDA    ((unsigned int) 0x8)        /* USAR) IrDA */
#define AT91C_US_USMODE_SWHSH   ((unsigned int) 0xC)        /* USAR) Software Handshaking */

#define AT91C_US_CLKS_CLOCK     ((unsigned int) 0x0 <<  4)  /* USAR) Clock */
#define AT91C_US_CLKS_FDIV1     ((unsigned int) 0x1 <<  4)  /* USAR) fdiv1 */
#define AT91C_US_CLKS_SLOW      ((unsigned int) 0x2 <<  4)  /* USAR) slow_clock (ARM) */
#define AT91C_US_CLKS_EXT       ((unsigned int) 0x3 <<  4)  /* USAR) External (SCK) */

#define AT91C_US_CHRL_5_BITS    ((unsigned int) 0x0 <<  6)  /* USAR) Character Length: 5 bits */
#define AT91C_US_CHRL_6_BITS    ((unsigned int) 0x1 <<  6)  /* USAR) Character Length: 6 bits */
#define AT91C_US_CHRL_7_BITS    ((unsigned int) 0x2 <<  6)  /* USAR) Character Length: 7 bits */
#define AT91C_US_CHRL_8_BITS    ((unsigned int) 0x3 <<  6)  /* USAR) Character Length: 8 bits */

#define AT91C_US_PAR_EVEN       ((unsigned int) 0x0 <<  9)  /* DBGU Even Parity */
#define AT91C_US_PAR_ODD        ((unsigned int) 0x1 <<  9)  /* DBGU Odd Parity */
#define AT91C_US_PAR_SPACE      ((unsigned int) 0x2 <<  9)  /* DBGU Parity forced to 0 (Space) */
#define AT91C_US_PAR_MARK       ((unsigned int) 0x3 <<  9)  /* DBGU Parity forced to 1 (Mark) */
#define AT91C_US_PAR_NONE       ((unsigned int) 0x4 <<  9)  /* DBGU No Parity */
#define AT91C_US_PAR_MULTI_DROP ((unsigned int) 0x6 <<  9)  /* DBGU Multi-drop mode */

#define AT91C_US_NBSTOP_1_BIT   ((unsigned int) 0x0 << 12)  /* USART 1 stop bit */
#define AT91C_US_NBSTOP_15_BIT  ((unsigned int) 0x1 << 12)  /* USART Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits */
#define AT91C_US_NBSTOP_2_BIT   ((unsigned int) 0x2 << 12)  /* USART 2 stop bits */

#define MCK     48054857
#define BR      115200          /* Baud Rate */
#define BRD     (MCK/16/BR)     /* Baud Rate Divisor */

#endif
