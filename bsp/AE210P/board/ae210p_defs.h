/*****************************************************************************
 *
 *            Copyright Andes Technology Corporation 2014
 *                         All Rights Reserved.
 *
 *  Revision History:
 *
 *    Jan.11.2014     Created.
 ****************************************************************************/

#ifndef __AE210_DEFS_H__
#define __AE210_DEFS_H__

/*****************************************************************************
 * AHB_SLAVE_4_7 - AE210P AHB
 ****************************************************************************/


/*****************************************************************************
 * BMC (APB Decoder)- AE210P AHB
 ****************************************************************************/

/*****************************************************************************
 * OSC - AE210P OSC
 ****************************************************************************/
/* OSC control Register (+0x00) */
#define OSC_CTRL_OVL_SZ_SHIFT			24
#define OSC_CTRL_OVLVALID_SHIFT			31

#define OSC_CTRL_OVL_SZ_MASK			0x07000000
#define OSC_CTRL_OVLVALID_MASK			0x80000000

/* OSC Fixed Region Size Register (+0x04) */
#define OSC_OVLFS_OVL_FSZ_MASK			0x000FFFFF

/* OSC Overlay Region Base Register (+0x08) */
#define OSC_OVLBASE_OVL_BASE_MASK		0x000FFFFF

/* OSC Overlay Region End Register (+0x0C) */
#define OSC_OVLEND_OVL_END_MASK			0x001FFFFF

/*****************************************************************************
 * DMAC - AE210P AHB
 ****************************************************************************/

/*****************************************************************************
 * AHB_SLAVE_0_3 - AE210P AHB
 ****************************************************************************/

//TODO
//finish this table
/*****************************************************************************
 * APBBR(N/A) - AE210P AHB to APB Bridge
 ****************************************************************************/

/*****************************************************************************
 * SMU - AE210P Core APB
 ****************************************************************************/

/*****************************************************************************
 * UARTx - AE210P Core APB
 ****************************************************************************/
/* Macros for specifying which UART to use. */
#define UARTC_NUM_DEVICES               2

/* IER Register (+0x04) */
#define UARTC_IER_RDR                   0x01 /* Data Ready Enable */
#define UARTC_IER_THRE                  0x02 /* THR Empty Enable */
#define UARTC_IER_RLS                   0x04 /* Receive Line Status Enable */
#define UARTC_CIER_MS                   0x08 /* Modem Staus Enable */

/* IIR Register (+0x08) */
#define UARTC_IIR_NONE                  0x01 /* No interrupt pending */
#define UARTC_IIR_RLS                   0x06 /* Receive Line Status */
#define UARTC_IIR_RDR                   0x04 /* Receive Data Ready */
#define UARTC_IIR_RTO                   0x0c /* Receive Time Out */
#define UARTC_IIR_THRE                  0x02 /* THR Empty */
#define UARTC_IIR_MODEM                 0x00 /* Modem Status */
#define UARTC_IIR_INT_MASK              0x0f /* Initerrupt Status Bits Mask */

#define UARTC_IIR_TFIFO_FULL            0x10 /* TX FIFO full */
#define UARTC_IIR_FIFO_EN               0xc0 /* FIFO mode is enabled, set when FCR[0] is 1 */

/* FCR Register (+0x08) */
#define UARTC_FCR_FIFO_EN               0x01 /* FIFO Enable */
#define UARTC_FCR_RFIFO_RESET           0x02 /* Rx FIFO Reset */
#define UARTC_FCR_TFIFO_RESET           0x04 /* Tx FIFO Reset */
#define UARTC_FCR_DMA_EN                0x08 /* Select UART DMA mode */

#define UARTC_FCR_TFIFO16_TRGL1         0x00 /* TX 16-byte FIFO int trigger level - 1 char */
#define UARTC_FCR_TFIFO16_TRGL3         0x10 /* TX 16-byte FIFO int trigger level - 3 char */
#define UARTC_FCR_TFIFO16_TRGL9         0x20 /* TX 16-byte FIFO int trigger level - 9 char */
#define UARTC_FCR_TFIFO16_TRGL13        0x30 /* TX 16-byte FIFO int trigger level - 13 char */

#define UARTC_FCR_RFIFO16_TRGL1         0x00 /* RX 16-byte FIFO int trigger level - 1 char */
#define UARTC_FCR_RFIFO16_TRGL4         0x40 /* RX 16-byte FIFO int trigger level - 4 char */
#define UARTC_FCR_RFIFO16_TRGL8         0x80 /* RX 16-byte FIFO int trigger level - 8 char */
#define UARTC_FCR_RFIFO16_TRGL14        0xc0 /* RX 16-byte FIFO int trigger level - 14 char */

/* FCR Register (+0x08) */
#define UARTC_FCR_FIFO_EN_MASK          0x01 /* FIFO Enable */
#define UARTC_FCR_FIFO_EN_BIT           0
#define UARTC_FCR_RFIFO_RESET_MASK      0x02 /* Rx FIFO Reset */
#define UARTC_FCR_RFIFO_RESET_BIT       1
#define UARTC_FCR_TFIFO_RESET_MASK      0x04 /* Tx FIFO Reset */
#define UARTC_FCR_TFIFO_RESET_BIT       2
#define UARTC_FCR_DMA_EN_MASK           0x08 /* Select UART DMA mode */
#define UARTC_FCR_DMA_EN_BIT            3

#define UARTC_FCR_TXFIFO_TRGL_MASK      0x30 /* TX FIFO int trigger level */
#define UARTC_FCR_TXFIFO_TRGL_SHIFT     4
#define UARTC_FCR_RXFIFO_TRGL_MASK      0xc0 /* RX FIFO int trigger level */
#define UARTC_FCR_RXFIFO_TRGL_SHIFT     6

/* LCR Register (+0x0c) */
#define UARTC_LCR_BITS5                 0x00
#define UARTC_LCR_BITS6                 0x01
#define UARTC_LCR_BITS7                 0x02
#define UARTC_LCR_BITS8                 0x03
#define UARTC_LCR_STOP1                 0x00
#define UARTC_LCR_STOP2                 0x04

#define UARTC_LCR_PARITY_EN             0x08 /* Parity Enable */
#define UARTC_LCR_PARITY_NONE           0x00 /* No Parity Check */
#define UARTC_LCR_PARITY_EVEN           0x18 /* Even Parity */
#define UARTC_LCR_PARITY_ODD            0x08 /* Odd Parity */
#if 0
#define UARTC_LCR_PARITY_1              0x21 /* 1 Parity Bit */
#define UARTC_LCR_PARITY_0              0x31 /* 0 Parity Bit */
#endif
#define UARTC_LCR_SETBREAK              0x40 /* Set Break condition */
#define UARTC_LCR_DLAB                  0x80 /* Divisor Latch Access Bit */

/* MCR Register (+0x10) */
#define UARTC_MCR_DTR                   0x01 /* Data Terminal Ready */
#define UARTC_MCR_RTS                   0x02 /* Request to Send */
#define UARTC_MCR_OUT1                  0x04 /* output1 */
#define UARTC_MCR_OUT2                  0x08 /* output2 or global interrupt enable */
#define UARTC_MCR_LPBK                  0x10 /* loopback mode */
#define UARTC_MCR_DMAMODE2              0x20 /* DMA mode2 */
#define UARTC_MCR_OUT3                  0x40 /* output 3 */

/* LSR Register (+0x14) */
#define UARTC_LSR_RDR                   0x1 /* Data Ready */
#define UARTC_LSR_OE                    0x2 /* Overrun Error */
#define UARTC_LSR_PE                    0x4 /* Parity Error */
#define UARTC_LSR_FE                    0x8 /* Framing Error */
#define UARTC_LSR_BI                    0x10 /* Break Interrupt */
#define UARTC_LSR_THRE                  0x20 /* THR/FIFO Empty */
#define UARTC_LSR_TE                    0x40 /* THR/FIFO and TFR Empty */
#define UARTC_LSR_DE                    0x80 /* FIFO Data Error */

/* MSR Register (+0x18) */
#define UARTC_MSR_DELTACTS              0x1 /* Delta CTS */
#define UARTC_MSR_DELTADSR              0x2 /* Delta DSR */
#define UARTC_MSR_TERI                  0x4 /* Trailing Edge RI */
#define UARTC_MSR_DELTACD               0x8 /* Delta CD */
#define UARTC_MSR_CTS                   0x10 /* Clear To Send */
#define UARTC_MSR_DSR                   0x20 /* Data Set Ready */
#define UARTC_MSR_RI                    0x40 /* Ring Indicator */
#define UARTC_MSR_DCD                   0x80 /* Data Carrier Detect */

/* MDR register (+0x20) */
#define UARTC_MDR_MODE_SEL_SHIFT        0
#define UARTC_MDR_SIP_BYCPU_BIT         2
#define UARTC_MDR_FMEND_MD_BIT          3
#define UARTC_MDR_DMA_EN_BIT            4
#define UARTC_MDR_FIR_INV_RX_BIT        5
#define UARTC_MDR_IR_INV_TX_BIT         6
#define UARTC_MDR_MODE_SEL_MASK         0x03
#define UARTC_MDR_SIP_BYCPU_MASK        0x04 /* 0: 1.6us end pulse; 1: depends on ACR[4] */
#define UARTC_MDR_FMEND_MD_MASK         0x08 /* 0: Frame length counter method; 1: Set end of transmission bit method */
#define UARTC_MDR_DMA_EN_MASK           0x10 /* Enable DMA mode. (PIO int should turn off) */
#define UARTC_MDR_FIR_INV_RX_MASK       0x20 /* (FIR only) Invert receiver input signal */
#define UARTC_MDR_IR_INV_TX_MASK        0x40 /* (FIR/SIR) Invert pulse during transmission */

#define UARTC_MDR_MODE_UART             0
#define UARTC_MDR_MODE_SIR              1
#define UARTC_MDR_MODE_FIR              2

/* ACR register (+0x24) */
#define UARTC_ACR_IR_TX_EN              0x01
#define UARTC_ACR_IR_RX_EN              0x02
#define UARTC_ACR_FIR_SETEOT            0x04

/*****************************************************************************
 * PIT - AG101 Core APB
 ****************************************************************************/

/* Interrupt Enable Register */
#define PIT_CH_NUM_MASK			0x7

/* Channel & Interrupt Enable Reg */
#define PIT_C0_TMR0_EN			0x1
#define PIT_C0_TMR1_EN			0x2
#define PIT_C0_TMR2_EN			0x4
#define PIT_C0_TMR3_EN			0x8

#define PIT_C1_TMR0_EN			0x10
#define PIT_C1_TMR1_EN			0x20
#define PIT_C1_TMR2_EN			0x40
#define PIT_C1_TMR3_EN			0x80

#define PIT_C2_TMR0_EN			0x100
#define PIT_C2_TMR1_EN			0x200
#define PIT_C2_TMR2_EN			0x400
#define PIT_C2_TMR3_EN			0x800

#define PIT_C3_TMR0_EN			0x1000
#define PIT_C3_TMR1_EN			0x2000
#define PIT_C3_TMR2_EN			0x4000
#define PIT_C3_TMR3_EN			0x8000

/* Interrupt Status Register */
/* Clean Timer interrupt pending bit, write 1 clean */
#define PIT_C0_TMR0_PEND_W1C		0x1
#define PIT_C0_TMR1_PEND_W1C		0x2
#define PIT_C0_TMR2_PEND_W1C		0x4
#define PIT_C0_TMR3_PEND_W1C		0x8

#define PIT_C1_TMR0_PEND_W1C		0x10
#define PIT_C1_TMR1_PEND_W1C		0x20
#define PIT_C1_TMR2_PEND_W1C		0x40
#define PIT_C1_TMR3_PEND_W1C		0x80

#define PIT_C2_TMR0_PEND_W1C		0x100
#define PIT_C2_TMR1_PEND_W1C		0x200
#define PIT_C2_TMR2_PEND_W1C		0x400
#define PIT_C2_TMR3_PEND_W1C		0x800

#define PIT_C3_TMR0_PEND_W1C		0x1000
#define PIT_C3_TMR1_PEND_W1C		0x2000
#define PIT_C3_TMR2_PEND_W1C		0x4000
#define PIT_C3_TMR3_PEND_W1C		0x8000

/* channel 0~3 control register */
/* ChClk*/
#define PIT_CH_CTL_APBCLK		0x8 
/* ChMode*/
#define PIT_CH_CTL_TMR32		0x1
#define PIT_CH_CTL_TMR16		0x2
#define PIT_CH_CTL_TMR8			0x3
#define PIT_CH_CTL_PWM			0x4
#define PIT_CH_CTL_MIX16		0x6
#define PIT_CH_CTL_MIX8			0x7


/*****************************************************************************
 * WDT - AG101 Core APB
 ****************************************************************************/

//TODO
//finish this table
/*****************************************************************************
 * RTC - AE210P APB
 ****************************************************************************/


//TODO
//Finish this table
/*****************************************************************************
 * GPIO - AE210P APB
 ****************************************************************************/

/*****************************************************************************
 * I2C - AG101 Core APB
 ****************************************************************************/

/*****************************************************************************
 * SPI1 - AG101 Core APB
 ****************************************************************************/

/*****************************************************************************
 * SPI2 - AG101 Core APB
 ****************************************************************************/

/*****************************************************************************
 * APB_SLAVE_0_4 - AG101 Core APB
 ****************************************************************************/


/*****************************************************************************
 * Interface & Definitions
 ****************************************************************************/

/* TODO: timer-polling method */
#if (defined(CONFIG_CPU_ICACHE_ENABLE) && defined(CONFIG_CPU_DCACHE_ENABLE))

#define _nds_kwait(count)						\
	do {								\
		volatile uint32_t i = 0;				\
		while (i++ < (uint32_t)(count))				\
			;						\
	} while(0)
#else

#define _nds_kwait(count)						\
	do {								\
		volatile uint32_t i = 0;				\
		uint32_t c = (count > 0x10) ? count / 0x10 : 0x10;	\
		while (i++ < (uint32_t)(c))				\
			;						\
	} while(0)
#endif

#endif /* __AE210P_DEFS_H__ */
