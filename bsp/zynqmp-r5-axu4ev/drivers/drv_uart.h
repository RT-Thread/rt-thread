#ifndef _DRV_UART_H_
#define _DRV_UART_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @name Register Map
 *
 * Registers of the UART.
 * @{
 */
typedef struct
{
    volatile uint32_t CR;            /**< Control Register */
    volatile uint32_t MR;            /**< Mode Register */
    volatile uint32_t IER;           /**< Interrupt Enable */
    volatile uint32_t IDR;           /**< Interrupt Disable */
    volatile uint32_t IMR;           /**< Interrupt Mask */
    volatile uint32_t ISR;           /**< Interrupt Status */
    volatile uint32_t BAUDGEN;       /**< Baud Rate Generator */
    volatile uint32_t RXTOUT;        /**< RX Timeout */
    volatile uint32_t RXWM;          /**< RX FIFO Trigger Level */
    volatile uint32_t MODEMCR;       /**< Modem Control */
    volatile uint32_t MODEMSR;       /**< Modem Status */
    volatile uint32_t SR;            /**< Channel Status */
    volatile uint32_t FIFO;          /**< FIFO */
    volatile uint32_t BAUDDIV;       /**< Baud Rate Divider */
    volatile uint32_t FLOWDEL;       /**< Flow Delay */
    volatile uint32_t RESERVED1;
    volatile uint32_t RESERVED2;
    volatile uint32_t TXWM;            /* TX FIFO Trigger Level */
} UART_Registers;
/* @} */

/** @name Control Register
 *
 * The Control register (CR) controls the major functions of the device.
 *
 * Control Register Bit Definition
 */
#define UART_CR_STOPBRK             0x00000100        /**< Stop transmission of break */
#define UART_CR_STARTBRK            0x00000080        /**< Set break */
#define UART_CR_TORST               0x00000040        /**< RX timeout counter restart */
#define UART_CR_TX_DIS              0x00000020        /**< TX disabled. */
#define UART_CR_TX_EN               0x00000010        /**< TX enabled */
#define UART_CR_RX_DIS              0x00000008        /**< RX disabled. */
#define UART_CR_RX_EN               0x00000004        /**< RX enabled */
#define UART_CR_EN_DIS_MASK         0x0000003C        /**< Enable/disable Mask */
#define UART_CR_TXRST               0x00000002        /**< TX logic reset */
#define UART_CR_RXRST               0x00000001        /**< RX logic reset */
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
#define UART_MR_CCLK                0x00000400        /**< Input clock selection */
#define UART_MR_CHMODE_R_LOOP       0x00000300        /**< Remote loopback mode */
#define UART_MR_CHMODE_L_LOOP       0x00000200        /**< Local loopback mode */
#define UART_MR_CHMODE_ECHO         0x00000100        /**< Auto echo mode */
#define UART_MR_CHMODE_NORM         0x00000000        /**< Normal mode */
#define UART_MR_CHMODE_SHIFT        8                /**< Mode shift */
#define UART_MR_CHMODE_MASK         0x00000300        /**< Mode mask */
#define UART_MR_STOPMODE_2_BIT      0x00000080        /**< 2 stop bits */
#define UART_MR_STOPMODE_1_5_BIT    0x00000040        /**< 1.5 stop bits */
#define UART_MR_STOPMODE_1_BIT      0x00000000        /**< 1 stop bit */
#define UART_MR_STOPMODE_SHIFT      6                /**< Stop bits shift */
#define UART_MR_STOPMODE_MASK       0x000000A0        /**< Stop bits mask */
#define UART_MR_PARITY_NONE         0x00000020        /**< No parity mode */
#define UART_MR_PARITY_MARK         0x00000018        /**< Mark parity mode */
#define UART_MR_PARITY_SPACE        0x00000010        /**< Space parity mode */
#define UART_MR_PARITY_ODD          0x00000008        /**< Odd parity mode */
#define UART_MR_PARITY_EVEN         0x00000000        /**< Even parity mode */
#define UART_MR_PARITY_SHIFT        3                /**< Parity setting shift */
#define UART_MR_PARITY_MASK         0x00000038        /**< Parity mask */
#define UART_MR_CHARLEN_6_BIT       0x00000006        /**< 6 bits data */
#define UART_MR_CHARLEN_7_BIT       0x00000004        /**< 7 bits data */
#define UART_MR_CHARLEN_8_BIT       0x00000000        /**< 8 bits data */
#define UART_MR_CHARLEN_SHIFT       1                /**< Data Length shift */
#define UART_MR_CHARLEN_MASK        0x00000006        /**< Data length mask */
#define UART_MR_CLKSEL              0x00000001        /**< Input clock selection */
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
#define UART_IXR_DMS                0x00000200        /**< Modem status change interrupt */
#define UART_IXR_TOUT               0x00000100        /**< Timeout error interrupt */
#define UART_IXR_PARITY             0x00000080        /**< Parity error interrupt */
#define UART_IXR_FRAMING            0x00000040        /**< Framing error interrupt */
#define UART_IXR_OVER               0x00000020        /**< Overrun error interrupt */
#define UART_IXR_TXFULL             0x00000010        /**< TX FIFO full interrupt. */
#define UART_IXR_TXEMPTY            0x00000008        /**< TX FIFO empty interrupt. */
#define UART_IXR_RXFULL             0x00000004        /**< RX FIFO full interrupt. */
#define UART_IXR_RXEMPTY            0x00000002        /**< RX FIFO empty interrupt. */
#define UART_IXR_RXOVR              0x00000001        /**< RX FIFO trigger interrupt. */
#define UART_IXR_MASK               0x00003FFF        /**< Valid bit mask */
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
#define UART_BAUDGEN_DISABLE        0x00000000        /**< Disable clock */
#define UART_BAUDGEN_MASK           0x0000FFFF        /**< Valid bits mask */
/* @} */

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
#define UART_BAUDDIV_MASK            0x000000FF        /**< 8 bit baud divider mask */
/* @} */


/** @name Receiver Timeout Register
 *
 * Use the receiver timeout register (RTR) to detect an idle condition on
 * the receiver data line.
 *
 * @{
 */
#define UART_RXTOUT_DISABLE          0x00000000        /**< Disable time out */
#define UART_RXTOUT_MASK             0x000000FF        /**< Valid bits mask */
/* @} */

/** @name Receiver FIFO Trigger Level Register
 *
 * Use the Receiver FIFO Trigger Level Register (RTRIG) to set the value at
 * which the RX FIFO triggers an interrupt event.
 * @{
 */
#define UART_RXWM_DISABLE            0x00000000        /**< Disable RX trigger interrupt */
#define UART_RXWM_MASK               0x0000003F        /**< Valid bits mask */
/* @} */

/** @name Modem Control Register
 *
 * This register (MODEMCR) controls the interface with the modem or data set,
 * or a peripheral device emulating a modem.
 *
 * @{
 */
#define UART_MODEMCR_FCM            0x00000010        /**< Flow control mode */
#define UART_MODEMCR_RTS            0x00000002        /**< Request to send */
#define UART_MODEMCR_DTR            0x00000001        /**< Data terminal ready */
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
#define UART_MODEMSR_FCMS           0x00000100        /**< Flow control mode (FCMS) */
#define UART_MODEMSR_DCD            0x00000080        /**< Complement of DCD input */
#define UART_MODEMSR_RI             0x00000040        /**< Complement of RI input */
#define UART_MODEMSR_DSR            0x00000020        /**< Complement of DSR input */
#define UART_MODEMSR_CTS            0x00000010        /**< Complement of CTS input */
#define UART_MEDEMSR_DCDX           0x00000008        /**< Delta DCD indicator */
#define UART_MEDEMSR_RIX            0x00000004        /**< Change of RI */
#define UART_MEDEMSR_DSRX           0x00000002        /**< Change of DSR */
#define UART_MEDEMSR_CTSX           0x00000001        /**< Change of CTS */
/* @} */

/** @name Channel Status Register
 *
 * The channel status register (CSR) is provided to enable the control logic
 * to monitor the status of bits in the channel interrupt status register,
 * even if these are masked out by the interrupt mask register.
 *
 * @{
 */
#define UART_SR_FLOWDEL             0x00001000        /**< RX FIFO fill over flow delay */
#define UART_SR_TACTIVE             0x00000800        /**< TX active */
#define UART_SR_RACTIVE             0x00000400        /**< RX active */
#define UART_SR_DMS                 0x00000200        /**< Delta modem status change */
#define UART_SR_TOUT                0x00000100        /**< RX timeout */
#define UART_SR_PARITY              0x00000080        /**< RX parity error */
#define UART_SR_FRAME               0x00000040        /**< RX frame error */
#define UART_SR_OVER                0x00000020        /**< RX overflow error */
#define UART_SR_TXFULL              0x00000010        /**< TX FIFO full */
#define UART_SR_TXEMPTY             0x00000008        /**< TX FIFO empty */
#define UART_SR_RXFULL              0x00000004        /**< RX FIFO full */
#define UART_SR_RXEMPTY             0x00000002        /**< RX FIFO empty */
#define UART_SR_RXOVR               0x00000001        /**< RX FIFO fill over trigger */
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
#define UART_FLOWDEL_MASK           UART_RXWM_MASK    /**< Valid bit mask */
/* @} */


/****************************************************************************/
/**
* Determine if there is receive data in the receiver and/or FIFO.
*
* @param    BaseAddress contains the base address of the device.
*
* @return    TRUE if there is receive data, FALSE otherwise.
*
* @note        C-Style signature:
*        uint32_t UartDataReceived(uint32_t BaseAddress)
*
******************************************************************************/
#define UartDataReceived(BaseAddress)            \
    !((__REG32((BaseAddress) + UART_SR_OFFSET) & \
    UART_SR_RXEMPTY) == UART_SR_RXEMPTY)

/****************************************************************************/
/**
* Determine if a byte of data can be sent with the transmitter.
*
* @param    BaseAddress contains the base address of the device.
*
* @return    TRUE if the TX FIFO is full, FALSE if a byte can be put in the
*        FIFO.
*
* @note        C-Style signature:
*        uint32_t UartTXFIFOFull(uint32_t BaseAddress)
*
******************************************************************************/
#define UartTXFIFOFull(BaseAddress)             \
    ((__REG32((BaseAddress) + UART_SR_OFFSET) & \
     UART_SR_TXFULL) == UART_SR_TXFULL)

#ifdef __cplusplus
}
#endif

#endif

