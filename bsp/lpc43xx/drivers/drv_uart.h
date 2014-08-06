#ifndef __UART_H__
#define __UART_H__


/* Accepted Error baud rate value (in percent unit) */
#define UART_ACCEPTED_BAUDRATE_ERROR    (3)         /*!< Acceptable UART baudrate error */


/* --------------------- BIT DEFINITIONS -------------------------------------- */
/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Receiver Buffer Register
 **********************************************************************/
#define UART_RBR_MASKBIT    ((uint8_t)0xFF)         /*!< UART Received Buffer mask bit (8 bits) */

/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Transmit Holding Register
 **********************************************************************/
#define UART_THR_MASKBIT    ((uint8_t)0xFF)         /*!< UART Transmit Holding mask bit (8 bits) */

/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Divisor Latch LSB register
 **********************************************************************/
#define UART_LOAD_DLL(div)  ((div) & 0xFF)  /**< Macro for loading least significant halfs of divisors */
#define UART_DLL_MASKBIT    ((uint8_t)0xFF) /*!< Divisor latch LSB bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UARTn Divisor Latch MSB register
 **********************************************************************/
#define UART_DLM_MASKBIT    ((uint8_t)0xFF)         /*!< Divisor latch MSB bit mask */
#define UART_LOAD_DLM(div)  (((div) >> 8) & 0xFF)   /**< Macro for loading most significant halfs of divisors */

/*********************************************************************//**
 * Macro defines for Macro defines for UART interrupt enable register
 **********************************************************************/
#define UART_IER_RBRINT_EN      ((uint32_t)(1<<0))  /*!< RBR Interrupt enable*/
#define UART_IER_THREINT_EN     ((uint32_t)(1<<1))  /*!< THR Interrupt enable*/
#define UART_IER_RLSINT_EN      ((uint32_t)(1<<2))  /*!< RX line status interrupt enable*/
#define UART1_IER_MSINT_EN      ((uint32_t)(1<<3))  /*!< Modem status interrupt enable */
#define UART1_IER_CTSINT_EN     ((uint32_t)(1<<7))  /*!< CTS1 signal transition interrupt enable */
#define UART_IER_ABEOINT_EN     ((uint32_t)(1<<8))  /*!< Enables the end of auto-baud interrupt */
#define UART_IER_ABTOINT_EN     ((uint32_t)(1<<9))  /*!< Enables the auto-baud time-out interrupt */
#define UART_IER_BITMASK        ((uint32_t)(0x307)) /*!< UART interrupt enable register bit mask */
#define UART1_IER_BITMASK       ((uint32_t)(0x38F)) /*!< UART1 interrupt enable register bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART interrupt identification register
 **********************************************************************/
#define UART_IIR_INTSTAT_PEND   ((uint32_t)(1<<0))  /*!<Interrupt Status - Active low */
#define UART_IIR_INTID_RLS      ((uint32_t)(3<<1))  /*!<Interrupt identification: Receive line status*/
#define UART_IIR_INTID_RDA      ((uint32_t)(2<<1))  /*!<Interrupt identification: Receive data available*/
#define UART_IIR_INTID_CTI      ((uint32_t)(6<<1))  /*!<Interrupt identification: Character time-out indicator*/
#define UART_IIR_INTID_THRE     ((uint32_t)(1<<1))  /*!<Interrupt identification: THRE interrupt*/
#define UART1_IIR_INTID_MODEM   ((uint32_t)(0<<1))  /*!<Interrupt identification: Modem interrupt*/
#define UART_IIR_INTID_MASK     ((uint32_t)(7<<1))  /*!<Interrupt identification: Interrupt ID mask */
#define UART_IIR_FIFO_EN        ((uint32_t)(3<<6))  /*!<These bits are equivalent to UnFCR[0] */
#define UART_IIR_ABEO_INT       ((uint32_t)(1<<8))  /*!< End of auto-baud interrupt */
#define UART_IIR_ABTO_INT       ((uint32_t)(1<<9))  /*!< Auto-baud time-out interrupt */
#define UART_IIR_BITMASK        ((uint32_t)(0x3CF)) /*!< UART interrupt identification register bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART FIFO control register
 **********************************************************************/
#define UART_FCR_FIFO_EN        ((uint8_t)(1<<0))   /*!< UART FIFO enable */
#define UART_FCR_RX_RS          ((uint8_t)(1<<1))   /*!< UART FIFO RX reset */
#define UART_FCR_TX_RS          ((uint8_t)(1<<2))   /*!< UART FIFO TX reset */
#define UART_FCR_DMAMODE_SEL    ((uint8_t)(1<<3))   /*!< UART DMA mode selection */
#define UART_FCR_TRG_LEV0       ((uint8_t)(0))      /*!< UART FIFO trigger level 0: 1 character */
#define UART_FCR_TRG_LEV1       ((uint8_t)(1<<6))   /*!< UART FIFO trigger level 1: 4 character */
#define UART_FCR_TRG_LEV2       ((uint8_t)(2<<6))   /*!< UART FIFO trigger level 2: 8 character */
#define UART_FCR_TRG_LEV3       ((uint8_t)(3<<6))   /*!< UART FIFO trigger level 3: 14 character */
#define UART_FCR_BITMASK        ((uint8_t)(0xCF))   /*!< UART FIFO control bit mask */
#define UART_TX_FIFO_SIZE       (16)

/*********************************************************************//**
 * Macro defines for Macro defines for UART line control register
 **********************************************************************/
#define UART_LCR_WLEN5          ((uint8_t)(0))          /*!< UART 5 bit data mode */
#define UART_LCR_WLEN6          ((uint8_t)(1<<0))       /*!< UART 6 bit data mode */
#define UART_LCR_WLEN7          ((uint8_t)(2<<0))       /*!< UART 7 bit data mode */
#define UART_LCR_WLEN8          ((uint8_t)(3<<0))       /*!< UART 8 bit data mode */
#define UART_LCR_STOPBIT_SEL    ((uint8_t)(1<<2))       /*!< UART Two Stop Bits Select */
#define UART_LCR_PARITY_EN      ((uint8_t)(1<<3))       /*!< UART Parity Enable */
#define UART_LCR_PARITY_ODD     ((uint8_t)(0))          /*!< UART Odd Parity Select */
#define UART_LCR_PARITY_EVEN    ((uint8_t)(1<<4))       /*!< UART Even Parity Select */
#define UART_LCR_PARITY_F_1     ((uint8_t)(2<<4))       /*!< UART force 1 stick parity */
#define UART_LCR_PARITY_F_0     ((uint8_t)(3<<4))       /*!< UART force 0 stick parity */
#define UART_LCR_BREAK_EN       ((uint8_t)(1<<6))       /*!< UART Transmission Break enable */
#define UART_LCR_DLAB_EN        ((uint8_t)(1<<7))       /*!< UART Divisor Latches Access bit enable */
#define UART_LCR_BITMASK        ((uint8_t)(0xFF))       /*!< UART line control bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART1 Modem Control Register
 **********************************************************************/
#define UART1_MCR_DTR_CTRL      ((uint8_t)(1<<0))       /*!< Source for modem output pin DTR */
#define UART1_MCR_RTS_CTRL      ((uint8_t)(1<<1))       /*!< Source for modem output pin RTS */
#define UART1_MCR_LOOPB_EN      ((uint8_t)(1<<4))       /*!< Loop back mode select */
#define UART1_MCR_AUTO_RTS_EN   ((uint8_t)(1<<6))       /*!< Enable Auto RTS flow-control */
#define UART1_MCR_AUTO_CTS_EN   ((uint8_t)(1<<7))       /*!< Enable Auto CTS flow-control */
#define UART1_MCR_BITMASK       ((uint8_t)(0x0F3))      /*!< UART1 bit mask value */

/*********************************************************************//**
 * Macro defines for Macro defines for UART line status register
 **********************************************************************/
#define UART_LSR_RDR        ((uint8_t)(1<<0))   /*!<Line status register: Receive data ready*/
#define UART_LSR_OE         ((uint8_t)(1<<1))   /*!<Line status register: Overrun error*/
#define UART_LSR_PE         ((uint8_t)(1<<2))   /*!<Line status register: Parity error*/
#define UART_LSR_FE         ((uint8_t)(1<<3))   /*!<Line status register: Framing error*/
#define UART_LSR_BI         ((uint8_t)(1<<4))   /*!<Line status register: Break interrupt*/
#define UART_LSR_THRE       ((uint8_t)(1<<5))   /*!<Line status register: Transmit holding register empty*/
#define UART_LSR_TEMT       ((uint8_t)(1<<6))   /*!<Line status register: Transmitter empty*/
#define UART_LSR_RXFE       ((uint8_t)(1<<7))   /*!<Error in RX FIFO*/
#define UART_LSR_BITMASK    ((uint8_t)(0xFF))   /*!<UART Line status bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART Modem (UART1 only) status register
 **********************************************************************/
#define UART1_MSR_DELTA_CTS     ((uint8_t)(1<<0))   /*!< Set upon state change of input CTS */
#define UART1_MSR_DELTA_DSR     ((uint8_t)(1<<1))   /*!< Set upon state change of input DSR */
#define UART1_MSR_LO2HI_RI      ((uint8_t)(1<<2))   /*!< Set upon low to high transition of input RI */
#define UART1_MSR_DELTA_DCD     ((uint8_t)(1<<3))   /*!< Set upon state change of input DCD */
#define UART1_MSR_CTS           ((uint8_t)(1<<4))   /*!< Clear To Send State */
#define UART1_MSR_DSR           ((uint8_t)(1<<5))   /*!< Data Set Ready State */
#define UART1_MSR_RI            ((uint8_t)(1<<6))   /*!< Ring Indicator State */
#define UART1_MSR_DCD           ((uint8_t)(1<<7))   /*!< Data Carrier Detect State */
#define UART1_MSR_BITMASK       ((uint8_t)(0xFF))   /*!< MSR register bit-mask value */

/*********************************************************************//**
 * Macro defines for Macro defines for UART Scratch Pad Register
 **********************************************************************/
#define UART_SCR_BIMASK     ((uint8_t)(0xFF))   /*!< UART Scratch Pad bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART Auto baudrate control register
 **********************************************************************/
#define UART_ACR_START              ((uint32_t)(1<<0))  /**< UART Auto-baud start */
#define UART_ACR_MODE               ((uint32_t)(1<<1))  /**< UART Auto baudrate Mode 1 */
#define UART_ACR_AUTO_RESTART       ((uint32_t)(1<<2))  /**< UART Auto baudrate restart */
#define UART_ACR_ABEOINT_CLR        ((uint32_t)(1<<8))  /**< UART End of auto-baud interrupt clear */
#define UART_ACR_ABTOINT_CLR        ((uint32_t)(1<<9))  /**< UART Auto-baud time-out interrupt clear */
#define UART_ACR_BITMASK            ((uint32_t)(0x307)) /**< UART Auto Baudrate register bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART IrDA control register
 **********************************************************************/
#define UART_ICR_IRDAEN         ((uint32_t)(1<<0))          /**< IrDA mode enable */
#define UART_ICR_IRDAINV        ((uint32_t)(1<<1))          /**< IrDA serial input inverted */
#define UART_ICR_FIXPULSE_EN    ((uint32_t)(1<<2))          /**< IrDA fixed pulse width mode */
#define UART_ICR_PULSEDIV(n)    ((uint32_t)((n&0x07)<<3))   /**< PulseDiv - Configures the pulse when FixPulseEn = 1 */
#define UART_ICR_BITMASK        ((uint32_t)(0x3F))          /*!< UART IRDA bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART half duplex register
 **********************************************************************/
#define UART_HDEN_HDEN          ((uint32_t)(1<<0))          /**< enable half-duplex mode*/

/*********************************************************************//**
 * Macro defines for Macro defines for UART smart card interface control register
 **********************************************************************/
#define UART_SCICTRL_SCIEN      ((uint32_t)(1<<0))          /**< enable asynchronous half-duplex smart card interface*/
#define UART_SCICTRL_NACKDIS    ((uint32_t)(1<<1))          /**< NACK response is inhibited*/
#define UART_SCICTRL_PROTSEL_T1 ((uint32_t)(1<<2))          /**< ISO7816-3 protocol T1 is selected*/
#define UART_SCICTRL_TXRETRY(n) ((uint32_t)((n&0x07)<<5))   /**< number of retransmission*/
#define UART_SCICTRL_GUARDTIME(n)   ((uint32_t)((n&0xFF)<<8))   /**< Extra guard time*/

/*********************************************************************//**
 * Macro defines for Macro defines for UART synchronous control register
 **********************************************************************/
#define UART_SYNCCTRL_SYNC      ((uint32_t)(1<<0))          /**< enable synchronous mode*/
#define UART_SYNCCTRL_CSRC_MASTER   ((uint32_t)(1<<1))      /**< synchronous master mode*/
#define UART_SYNCCTRL_FES       ((uint32_t)(1<<2))          /**< sample on falling edge*/
#define UART_SYNCCTRL_TSBYPASS  ((uint32_t)(1<<3))          /**< to be defined*/
#define UART_SYNCCTRL_CSCEN     ((uint32_t)(1<<4))          /**< continuous running clock enable (master mode only)*/
#define UART_SYNCCTRL_STARTSTOPDISABLE  ((uint32_t)(1<<5))  /**< do not send start/stop bit*/
#define UART_SYNCCTRL_CCCLR     ((uint32_t)(1<<6))          /**< stop continuous clock*/

/*********************************************************************//**
 * Macro defines for Macro defines for UART Fractional divider register
 **********************************************************************/
#define UART_FDR_DIVADDVAL(n)   ((uint32_t)(n&0x0F))        /**< Baud-rate generation pre-scaler divisor */
#define UART_FDR_MULVAL(n)      ((uint32_t)((n<<4)&0xF0))   /**< Baud-rate pre-scaler multiplier value */
#define UART_FDR_BITMASK        ((uint32_t)(0xFF))          /**< UART Fractional Divider register bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART Tx Enable register
 **********************************************************************/
#define UART1_TER_TXEN          ((uint8_t)(1<<7))       /*!< Transmit enable bit */
#define UART1_TER_BITMASK       ((uint8_t)(0x80))       /**< UART Transmit Enable Register bit mask */
#define UART0_2_3_TER_TXEN      ((uint8_t)(1<<0))       /*!< Transmit enable bit */
#define UART0_2_3_TER_BITMASK   ((uint8_t)(0x01))       /**< UART Transmit Enable Register bit mask */

/*********************************************************************//**
 * Macro defines for Macro defines for UART1 RS485 Control register
 **********************************************************************/
#define UART_RS485CTRL_NMM_EN       ((uint32_t)(1<<0))  /*!< RS-485/EIA-485 Normal Multi-drop Mode (NMM)
is disabled */
#define UART_RS485CTRL_RX_DIS       ((uint32_t)(1<<1))  /*!< The receiver is disabled */
#define UART_RS485CTRL_AADEN        ((uint32_t)(1<<2))  /*!< Auto Address Detect (AAD) is enabled */
#define UART_RS485CTRL_SEL_DTR      ((uint32_t)(1<<3))  /*!< If direction control is enabled
(bit DCTRL = 1), pin DTR is used for direction control */
#define UART_RS485CTRL_DCTRL_EN ((uint32_t)(1<<4))  /*!< Enable Auto Direction Control */
#define UART_RS485CTRL_OINV_1       ((uint32_t)(1<<5))  /*!< This bit reverses the polarity of the direction
control signal on the RTS (or DTR) pin. The direction control pin
    will be driven to logic "1" when the transmitter has data to be sent */
#define UART_RS485CTRL_BITMASK      ((uint32_t)(0x3F))  /**< RS485 control bit-mask value */

    /*********************************************************************//**
     * Macro defines for Macro defines for UART1 RS-485 Address Match register
     **********************************************************************/
#define UART_RS485ADRMATCH_BITMASK ((uint8_t)(0xFF))    /**< Bit mask value */

    /*********************************************************************//**
     * Macro defines for Macro defines for UART1 RS-485 Delay value register
     **********************************************************************/
    /* Macro defines for UART1 RS-485 Delay value register */
#define UART_RS485DLY_BITMASK       ((uint8_t)(0xFF))   /** Bit mask value */

    /*********************************************************************//**
     * Macro defines for Macro defines for UART FIFO Level register
     **********************************************************************/
#define UART_FIFOLVL_RXFIFOLVL(n)   ((uint32_t)(n&0x0F))        /**< Reflects the current level of the UART receiver FIFO */
#define UART_FIFOLVL_TXFIFOLVL(n)   ((uint32_t)((n>>8)&0x0F))   /**< Reflects the current level of the UART transmitter FIFO */
#define UART_FIFOLVL_BITMASK        ((uint32_t)(0x0F0F))        /**< UART FIFO Level Register bit mask */



    void rt_hw_uart_init(void);

#endif
