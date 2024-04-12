/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __ZYNQMP_UART_H__
#define __ZYNQMP_UART_H__

#include <zynqmp_reg.h>

/* The following constant defines the amount of error that is allowed for
 * a specified baud rate. This error is the difference between the actual
 * baud rate that will be generated using the specified clock and the
 * desired baud rate.
 */
#define XUARTPS_MAX_BAUD_ERROR_RATE 3U /* max % error allowed */

/*
 * The following constants indicate the max and min baud rates and these
 * numbers are based only on the testing that has been done. The hardware
 * is capable of other baud rates.
 */
#define XUARTPS_MAX_RATE 6240000U
#define XUARTPS_MIN_RATE 110U

/** @name Register Map
 *
 * Register offsets for the UART.
 * @{
 */
#define XUARTPS_CR_OFFSET 0x0000U      /**< Control Register [8:0] */
#define XUARTPS_MR_OFFSET 0x0004U      /**< Mode Register [9:0] */
#define XUARTPS_IER_OFFSET 0x0008U     /**< Interrupt Enable [12:0] */
#define XUARTPS_IDR_OFFSET 0x000CU     /**< Interrupt Disable [12:0] */
#define XUARTPS_IMR_OFFSET 0x0010U     /**< Interrupt Mask [12:0] */
#define XUARTPS_ISR_OFFSET 0x0014U     /**< Interrupt Status [12:0]*/
#define XUARTPS_BAUDGEN_OFFSET 0x0018U /**< Baud Rate Generator [15:0] */
#define XUARTPS_RXTOUT_OFFSET 0x001CU  /**< RX Timeout [7:0] */
#define XUARTPS_RXWM_OFFSET 0x0020U    /**< RX FIFO Trigger Level [5:0] */
#define XUARTPS_MODEMCR_OFFSET 0x0024U /**< Modem Control [5:0] */
#define XUARTPS_MODEMSR_OFFSET 0x0028U /**< Modem Status [8:0] */
#define XUARTPS_SR_OFFSET 0x002CU      /**< Channel Status [14:0] */
#define XUARTPS_FIFO_OFFSET 0x0030U    /**< FIFO [7:0] */
#define XUARTPS_BAUDDIV_OFFSET 0x0034U /**< Baud Rate Divider [7:0] */
#define XUARTPS_FLOWDEL_OFFSET 0x0038U /**< Flow Delay [5:0] */
#define XUARTPS_TXWM_OFFSET 0x0044U    /**< TX FIFO Trigger Level [5:0] */
#define XUARTPS_RXBS_OFFSET 0x0048U    /**< RX FIFO Byte Status [11:0] */
/* @} */

/** @name Control Register
 *
 * The Control register (CR) controls the major functions of the device.
 *
 * Control Register Bit Definition
 */
#define XUARTPS_CR_STOPBRK 0x00000100U     /**< Stop transmission of break */
#define XUARTPS_CR_STARTBRK 0x00000080U    /**< Set break */
#define XUARTPS_CR_TORST 0x00000040U       /**< RX timeout counter restart */
#define XUARTPS_CR_TX_DIS 0x00000020U      /**< TX disabled. */
#define XUARTPS_CR_TX_EN 0x00000010U       /**< TX enabled */
#define XUARTPS_CR_RX_DIS 0x00000008U      /**< RX disabled. */
#define XUARTPS_CR_RX_EN 0x00000004U       /**< RX enabled */
#define XUARTPS_CR_EN_DIS_MASK 0x0000003CU /**< Enable/disable Mask */
#define XUARTPS_CR_TXRST 0x00000002U       /**< TX logic reset */
#define XUARTPS_CR_RXRST 0x00000001U       /**< RX logic reset */
/* @}*/

/** @name Mode Register
 *
 * The mode register (MR) defines the mode of transfer as well as the data
 * format. If this register is modified during transmission or reception,
 * data validity cannot be guaranteed.
 *
 * Mode Register Bit Definition
 * @{
 */
#define XUARTPS_MR_CCLK 0x00000400U             /**< Input clock selection */
#define XUARTPS_MR_CHMODE_R_LOOP 0x00000300U    /**< Remote loopback mode */
#define XUARTPS_MR_CHMODE_L_LOOP 0x00000200U    /**< Local loopback mode */
#define XUARTPS_MR_CHMODE_ECHO 0x00000100U      /**< Auto echo mode */
#define XUARTPS_MR_CHMODE_NORM 0x00000000U      /**< Normal mode */
#define XUARTPS_MR_CHMODE_SHIFT 8U              /**< Mode shift */
#define XUARTPS_MR_CHMODE_MASK 0x00000300U      /**< Mode mask */
#define XUARTPS_MR_STOPMODE_2_BIT 0x00000080U   /**< 2 stop bits */
#define XUARTPS_MR_STOPMODE_1_5_BIT 0x00000040U /**< 1.5 stop bits */
#define XUARTPS_MR_STOPMODE_1_BIT 0x00000000U   /**< 1 stop bit */
#define XUARTPS_MR_STOPMODE_SHIFT 6U            /**< Stop bits shift */
#define XUARTPS_MR_STOPMODE_MASK 0x000000A0U    /**< Stop bits mask */
#define XUARTPS_MR_PARITY_NONE 0x00000020U      /**< No parity mode */
#define XUARTPS_MR_PARITY_MARK 0x00000018U      /**< Mark parity mode */
#define XUARTPS_MR_PARITY_SPACE 0x00000010U     /**< Space parity mode */
#define XUARTPS_MR_PARITY_ODD 0x00000008U       /**< Odd parity mode */
#define XUARTPS_MR_PARITY_EVEN 0x00000000U      /**< Even parity mode */
#define XUARTPS_MR_PARITY_SHIFT 3U              /**< Parity setting shift */
#define XUARTPS_MR_PARITY_MASK 0x00000038U      /**< Parity mask */
#define XUARTPS_MR_CHARLEN_6_BIT 0x00000006U    /**< 6 bits data */
#define XUARTPS_MR_CHARLEN_7_BIT 0x00000004U    /**< 7 bits data */
#define XUARTPS_MR_CHARLEN_8_BIT 0x00000000U    /**< 8 bits data */
#define XUARTPS_MR_CHARLEN_SHIFT 1U             /**< Data Length shift */
#define XUARTPS_MR_CHARLEN_MASK 0x00000006U     /**< Data length mask */
#define XUARTPS_MR_CLKSEL 0x00000001U           /**< Input clock selection */
/* @} */

/** @name Interrupt Registers
 *
 * Interrupt control logic uses the interrupt enable register (IER) and the
 * interrupt disable register (IDR) to set the value of the bits in the
 * interrupt mask register (IMR). The IMR determines whether to pass an
 * interrupt to the interrupt status register (ISR).
 * Writing a 1 to IER Enbables an interrupt, writing a 1 to IDR disables an
 * interrupt. IMR and ISR are read only, and IER and IDR are write only.
 * Reading either IER or IDR returns 0x00.
 *
 * All four registers have the same bit definitions.
 *
 * @{
 */
#define XUARTPS_IXR_RBRK 0x00002000U    /**< Rx FIFO break detect interrupt */
#define XUARTPS_IXR_TOVR 0x00001000U    /**< Tx FIFO Overflow interrupt */
#define XUARTPS_IXR_TNFUL 0x00000800U   /**< Tx FIFO Nearly Full interrupt */
#define XUARTPS_IXR_TTRIG 0x00000400U   /**< Tx Trig interrupt */
#define XUARTPS_IXR_DMS 0x00000200U     /**< Modem status change interrupt */
#define XUARTPS_IXR_TOUT 0x00000100U    /**< Timeout error interrupt */
#define XUARTPS_IXR_PARITY 0x00000080U  /**< Parity error interrupt */
#define XUARTPS_IXR_FRAMING 0x00000040U /**< Framing error interrupt */
#define XUARTPS_IXR_OVER 0x00000020U    /**< Overrun error interrupt */
#define XUARTPS_IXR_TXFULL 0x00000010U  /**< TX FIFO full interrupt. */
#define XUARTPS_IXR_TXEMPTY 0x00000008U /**< TX FIFO empty interrupt. */
#define XUARTPS_IXR_RXFULL 0x00000004U  /**< RX FIFO full interrupt. */
#define XUARTPS_IXR_RXEMPTY 0x00000002U /**< RX FIFO empty interrupt. */
#define XUARTPS_IXR_RXOVR 0x00000001U   /**< RX FIFO trigger interrupt. */
#define XUARTPS_IXR_MASK 0x00003FFFU    /**< Valid bit mask */
/* @} */

/** @name Baud Rate Generator Register
 *
 * The baud rate generator control register (BRGR) is a 16 bit register that
 * controls the receiver bit sample clock and baud rate.
 * Valid values are 1 - 65535.
 *
 * Bit Sample Rate = CCLK / BRGR, where the CCLK is selected by the MR_CCLK bit
 * in the MR register.
 * @{
 */
#define XUARTPS_BAUDGEN_DISABLE 0x00000000U   /**< Disable clock */
#define XUARTPS_BAUDGEN_MASK 0x0000FFFFU      /**< Valid bits mask */
#define XUARTPS_BAUDGEN_RESET_VAL 0x0000028BU /**< Reset value */

/** @name Baud Divisor Rate register
 *
 * The baud rate divider register (BDIV) controls how much the bit sample
 * rate is divided by. It sets the baud rate.
 * Valid values are 0x04 to 0xFF. Writing a value less than 4 will be ignored.
 *
 * Baud rate = CCLK / ((BAUDDIV + 1) x BRGR), where the CCLK is selected by
 * the MR_CCLK bit in the MR register.
 * @{
 */
#define XUARTPS_BAUDDIV_MASK 0x000000FFU      /**< 8 bit baud divider mask */
#define XUARTPS_BAUDDIV_RESET_VAL 0x0000000FU /**< Reset value */
/* @} */

/** @name Receiver Timeout Register
 *
 * Use the receiver timeout register (RTR) to detect an idle condition on
 * the receiver data line.
 *
 * @{
 */
#define XUARTPS_RXTOUT_DISABLE 0x00000000U /**< Disable time out */
#define XUARTPS_RXTOUT_MASK 0x000000FFU    /**< Valid bits mask */

/** @name Receiver FIFO Trigger Level Register
 *
 * Use the Receiver FIFO Trigger Level Register (RTRIG) to set the value at
 * which the RX FIFO triggers an interrupt event.
 * @{
 */
#define XUARTPS_RXWM_DISABLE 0x00000000U   /**< Disable RX trigger interrupt */
#define XUARTPS_RXWM_MASK 0x0000003FU      /**< Valid bits mask */
#define XUARTPS_RXWM_RESET_VAL 0x00000020U /**< Reset value */
/* @} */

/** @name Transmit FIFO Trigger Level Register
 *
 * Use the Transmit FIFO Trigger Level Register (TTRIG) to set the value at
 * which the TX FIFO triggers an interrupt event.
 * @{
 */
#define XUARTPS_TXWM_MASK 0x0000003FU      /**< Valid bits mask */
#define XUARTPS_TXWM_RESET_VAL 0x00000020U /**< Reset value */
/* @} */

/** @name Modem Control Register
 *
 * This register (MODEMCR) controls the interface with the modem or data set,
 * or a peripheral device emulating a modem.
 *
 * @{
 */
#define XUARTPS_MODEMCR_FCM 0x00000020U /**< Flow control mode */
#define XUARTPS_MODEMCR_RTS 0x00000002U /**< Request to send */
#define XUARTPS_MODEMCR_DTR 0x00000001U /**< Data terminal ready */
/* @} */

/** @name Modem Status Register
 *
 * This register (MODEMSR) indicates the current state of the control lines
 * from a modem, or another peripheral device, to the CPU. In addition, four
 * bits of the modem status register provide change information. These bits
 * are set to a logic 1 whenever a control input from the modem changes state.
 *
 * Note: Whenever the DCTS, DDSR, TERI, or DDCD bit is set to logic 1, a modem
 * status interrupt is generated and this is reflected in the modem status
 * register.
 *
 * @{
 */
#define XUARTPS_MODEMSR_FCMS 0x00000100U /**< Flow control mode (FCMS) */
#define XUARTPS_MODEMSR_DCD 0x00000080U  /**< Complement of DCD input */
#define XUARTPS_MODEMSR_RI 0x00000040U   /**< Complement of RI input */
#define XUARTPS_MODEMSR_DSR 0x00000020U  /**< Complement of DSR input */
#define XUARTPS_MODEMSR_CTS 0x00000010U  /**< Complement of CTS input */
#define XUARTPS_MODEMSR_DDCD 0x00000008U /**< Delta DCD indicator */
#define XUARTPS_MODEMSR_TERI 0x00000004U /**< Trailing Edge Ring Indicator */
#define XUARTPS_MODEMSR_DDSR 0x00000002U /**< Change of DSR */
#define XUARTPS_MODEMSR_DCTS 0x00000001U /**< Change of CTS */
/* @} */

/** @name Channel Status Register
 *
 * The channel status register (CSR) is provided to enable the control logic
 * to monitor the status of bits in the channel interrupt status register,
 * even if these are masked out by the interrupt mask register.
 *
 * @{
 */
#define XUARTPS_SR_TNFUL 0x00004000U   /**< TX FIFO Nearly Full Status */
#define XUARTPS_SR_TTRIG 0x00002000U   /**< TX FIFO Trigger Status */
#define XUARTPS_SR_FLOWDEL 0x00001000U /**< RX FIFO fill over flow delay */
#define XUARTPS_SR_TACTIVE 0x00000800U /**< TX active */
#define XUARTPS_SR_RACTIVE 0x00000400U /**< RX active */
#define XUARTPS_SR_TXFULL 0x00000010U  /**< TX FIFO full */
#define XUARTPS_SR_TXEMPTY 0x00000008U /**< TX FIFO empty */
#define XUARTPS_SR_RXFULL 0x00000004U  /**< RX FIFO full */
#define XUARTPS_SR_RXEMPTY 0x00000002U /**< RX FIFO empty */
#define XUARTPS_SR_RXOVR 0x00000001U   /**< RX FIFO fill over trigger */
/* @} */

/** @name Flow Delay Register
 *
 * Operation of the flow delay register (FLOWDEL) is very similar to the
 * receive FIFO trigger register. An internal trigger signal activates when the
 * FIFO is filled to the level set by this register. This trigger will not
 * cause an interrupt, although it can be read through the channel status
 * register. In hardware flow control mode, RTS is deactivated when the trigger
 * becomes active. RTS only resets when the FIFO level is four less than the
 * level of the flow delay trigger and the flow delay trigger is not activated.
 * A value less than 4 disables the flow delay.
 * @{
 */
#define XUARTPS_FLOWDEL_MASK XUARTPS_RXWM_MASK /**< Valid bit mask */
/* @} */

/** @name Receiver FIFO Byte Status Register
 *
 * The Receiver FIFO Status register is used to have a continuous
 * monitoring of the raw unmasked byte status information. The register
 * contains frame, parity and break status information for the top
 * four bytes in the RX FIFO.
 *
 * Receiver FIFO Byte Status Register Bit Definition
 * @{
 */
#define XUARTPS_RXBS_BYTE3_BRKE 0x00000800U /**< Byte3 Break Error */
#define XUARTPS_RXBS_BYTE3_FRME 0x00000400U /**< Byte3 Frame Error */
#define XUARTPS_RXBS_BYTE3_PARE 0x00000200U /**< Byte3 Parity Error */
#define XUARTPS_RXBS_BYTE2_BRKE 0x00000100U /**< Byte2 Break Error */
#define XUARTPS_RXBS_BYTE2_FRME 0x00000080U /**< Byte2 Frame Error */
#define XUARTPS_RXBS_BYTE2_PARE 0x00000040U /**< Byte2 Parity Error */
#define XUARTPS_RXBS_BYTE1_BRKE 0x00000020U /**< Byte1 Break Error */
#define XUARTPS_RXBS_BYTE1_FRME 0x00000010U /**< Byte1 Frame Error */
#define XUARTPS_RXBS_BYTE1_PARE 0x00000008U /**< Byte1 Parity Error */
#define XUARTPS_RXBS_BYTE0_BRKE 0x00000004U /**< Byte0 Break Error */
#define XUARTPS_RXBS_BYTE0_FRME 0x00000002U /**< Byte0 Frame Error */
#define XUARTPS_RXBS_BYTE0_PARE 0x00000001U /**< Byte0 Parity Error */
#define XUARTPS_RXBS_MASK 0x00000007U       /**< 3 bit RX byte status mask */
/* @} */

/*
 * Defines for backwards compatibility, will be removed
 * in the next version of the driver
 */
#define XUARTPS_MEDEMSR_DCDX XUARTPS_MODEMSR_DDCD
#define XUARTPS_MEDEMSR_RIX XUARTPS_MODEMSR_TERI
#define XUARTPS_MEDEMSR_DSRX XUARTPS_MODEMSR_DDSR
#define XUARTPS_MEDEMSR_CTSX XUARTPS_MODEMSR_DCTS

#endif /* __ZYNQMP_UART_H__ */
